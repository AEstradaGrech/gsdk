
// Copyright (C) Microsoft Corporation. All rights reserved.

#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <exception>
#include <vector>

namespace Microsoft
{
    namespace Azure
    {
        namespace Gaming
        {
            class ConnectedPlayer // need to link this to the C# version
            {
            public:
                std::string m_playerId;

                ConnectedPlayer(std::string playerId)
                {
                    m_playerId = playerId;
                }
            };

            class GSDKInitializationException : public std::runtime_error
            {
                using std::runtime_error::runtime_error;
            };

            class GSDK
            {
            public:
                /// <summary>Renamed from WaitForSessionAssignment. Called when the game server is ready to accept clients.  If Start() hasn't been called by this point, it will be called implicitly here.</summary>
                /// <remarks>Required. This is a blocking call and will only return when this server is either allocated (a player is about to connect) or terminated.</remarks>
                /// <returns>True if the server is allocated (will receive players shortly). False if the server is terminated. </returns>
                static bool readyForPlayers();

                /// <summary>Returns all configuration settings</summary>
                /// <returns>unordered map of string key:value configuration setting values</returns>
                static const std::unordered_map<std::string, std::string> &getConfigSettings();

                /// <summary>Kicks off communication threads, heartbeats, etc.  Called implicitly by ReadyForPlayers if not called beforehand.</summary>
                /// <param name="debugLogs">Enables outputting additional logs to the GSDK log file.</param>
                static void start(bool debugLogs = false);

                /// <summary>Tells the Xcloud service information on who is connected.</summary>
                /// <param name="currentlyConnectedPlayers"></param>
                static void updateConnectedPlayers(const std::vector<ConnectedPlayer> &currentlyConnectedPlayers);

                /// <summary>Gets called if the server is shutting us down</summary>
                static void registerShutdownCallback(std::function<void()> callback);

                /// <summary>Gets called when the agent needs to check on the game's health</summary>
                static void registerHealthCallback(std::function<bool()> callback);

                /// <summary>Gets called if the server is getting a scheduled maintenance, it will get the UTC time of the maintenance event as an argument.</summary>
                static void registerMaintenanceCallback(std::function<void(const tm &)> callback);

                /// <summary>outputs a message to the log</summary>
                static unsigned int logMessage(const std::string &message);

                /// <summary>Returns a path to the directory where logs will be mapped to the VM host</summary>
                static const std::string &getLogsDirectory();

                // Keys for the map returned by getConfigSettings

                static constexpr const char* HEARTBEAT_ENDPOINT_KEY = "gsmsBaseUrl";
                static constexpr const char* SERVER_ID_KEY = "instanceId";
                static constexpr const char* LOG_FOLDER_KEY = "logFolder";
                static constexpr const char* CERTIFICATE_FOLDER_KEY = "certificateFolder";
                static constexpr const char* TITLE_ID_KEY = "titleId";
                static constexpr const char* BUILD_ID_KEY = "buildId";
                static constexpr const char* REGION_KEY = "region";

                // These two keys are only available after allocation (once readyForPlayers returns true)
                static constexpr const char* SESSION_COOKIE_KEY = "sessionCookie";
                static constexpr const char* SESSION_ID_KEY = "sessionId";
            };
        }
    }
}
