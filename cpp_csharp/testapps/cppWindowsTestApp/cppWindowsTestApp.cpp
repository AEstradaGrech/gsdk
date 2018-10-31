
// Copyright (C) Microsoft Corporation. All rights reserved.

#include "cppWindowsTestAppPch.h"
#include <chrono>
#include <thread>

#ifndef DISABLE_PLAYFABCLIENT_API
#include <playfab/PlayFabClientApi.h>
#include <playfab/PlayFabClientDataModels.h>
#include <playfab/PlayFabSettings.h>
#endif

void inShutdown()
{
    printf("GSDK is shutting me down!!!\n");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::exit(0);
}

bool isHealthy()
{
    return false;
}

void maintenanceScheduled(tm t)
{
    time_t local = _mkgmtime(&t);
    double delta = difftime(local, time(NULL));
    struct tm buf;
    char str[26];
    gmtime_s(&buf, &local);
    asctime_s(str, sizeof str, &buf);
    printf("UTC:   %s", str);
    localtime_s(&buf, &local);
    asctime_s(str, sizeof str, &buf);
    printf("local: %s", str);
    printf("delta: %f", delta);
}

#ifndef DISABLE_PLAYFABCLIENT_API
void OnPlayFabFail(const PlayFab::PlayFabError& error, void*)
{
    printf(("========== PlayFab call Failed: " + error.GenerateReport() + "\n").c_str());
}

void OnProfile(const PlayFab::ClientModels::GetPlayerProfileResult& result, void*)
{
    printf(("========== PlayFab Profile Success: " + result.PlayerProfile->DisplayName + "\n").c_str());
}

void OnLoginSuccess(const PlayFab::ClientModels::LoginResult& result, void*)
{
    printf(("========== PlayFab Login Success: " + result.PlayFabId + "\n").c_str());

    printf("========== Starting PlayFab GetProfile API call.\n");
    PlayFab::ClientModels::GetPlayerProfileRequest request;
    PlayFab::PlayFabClientAPI::GetPlayerProfile(request, OnProfile, OnPlayFabFail);
}
#endif

int main()
{
    printf("Starting!\n");
    try 
    {

#ifndef DISABLE_PLAYFABCLIENT_API
        // Super hacky short-term functionality PlayFab Test - TODO: Put the regular set of tests into proper Unit Test project
        printf("========== Starting PlayFab Login API call.\n");
        PlayFab::PlayFabSettings::titleId = "6195";
        PlayFab::PlayFabSettings::threadedCallbacks = true;
        PlayFab::ClientModels::LoginWithCustomIDRequest request;
        request.CustomId = "test_GSDK";
        request.CreateAccount = true;
        PlayFab::PlayFabClientAPI::LoginWithCustomID(request, OnLoginSuccess, OnPlayFabFail);
#endif

        Microsoft::Azure::Gaming::GSDK::start();
        Microsoft::Azure::Gaming::GSDK::registerShutdownCallback(&inShutdown);
        Microsoft::Azure::Gaming::GSDK::registerHealthCallback(&isHealthy);
        Microsoft::Azure::Gaming::GSDK::registerMaintenanceCallback(&maintenanceScheduled);

        // Test grabbing config
        printf(" Config before Active.\n");
        for (auto config : Microsoft::Azure::Gaming::GSDK::getConfigSettings())
        {
            printf("%s: %s\n",config.first.c_str(), config.second.c_str());
        }

        printf("\tStanding by!\n");
        if (Microsoft::Azure::Gaming::GSDK::readyForPlayers())
        {
            printf("Game on!\n");
            printf(" Config after Active.\n");
            for (auto config : Microsoft::Azure::Gaming::GSDK::getConfigSettings())
            {
                printf("%s: %s\n", config.first.c_str(), config.second.c_str());
            }

            std::vector<Microsoft::Azure::Gaming::ConnectedPlayer> players;
            players.push_back(Microsoft::Azure::Gaming::ConnectedPlayer("player1"));
            players.push_back(Microsoft::Azure::Gaming::ConnectedPlayer("player2"));
            Microsoft::Azure::Gaming::GSDK::updateConnectedPlayers(players);

            printf("Logs directory is: %s\n", Microsoft::Azure::Gaming::GSDK::getLogsDirectory().c_str());
        }
        else 
        {
            printf("Not allocated. Server is being shut down.\n");
        }
    }
    catch (const std::exception &ex)
    {
        printf("Problem initializing GSDK: %s\n", ex.what());
    }

    printf("Press enter to exit the program.\n");
    getchar();
    
    return 0;
}
