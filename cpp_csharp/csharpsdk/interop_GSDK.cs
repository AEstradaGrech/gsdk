//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.12
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace Microsoft.Playfab.Gaming {

class interop_gsdk {
  public static bool readyForPlayers() {
    bool ret = interop_gsdkPINVOKE.readyForPlayers();
    return ret;
  }

  public static interop_ConfigSettingMap getConfigSettings() {
    interop_ConfigSettingMap ret = new interop_ConfigSettingMap(interop_gsdkPINVOKE.getConfigSettings(), true);
    return ret;
  }

  public static void start() {
    interop_gsdkPINVOKE.start();
  }

  public static void updateConnectedPlayers(interop_ConnectedPlayerVector currentlyConnectedPlayers) {
    interop_gsdkPINVOKE.updateConnectedPlayers(interop_ConnectedPlayerVector.getCPtr(currentlyConnectedPlayers));
    if (interop_gsdkPINVOKE.SWIGPendingException.Pending) throw interop_gsdkPINVOKE.SWIGPendingException.Retrieve();
  }

  public static void registerShutdownCallback(interop_ShutdownCallback callback) {
    interop_gsdkPINVOKE.registerShutdownCallback(interop_ShutdownCallback.getCPtr(callback));
  }

  public static void registerHealthCallback(interop_HealthCallback callback) {
    interop_gsdkPINVOKE.registerHealthCallback(interop_HealthCallback.getCPtr(callback));
  }

  public static void registerMaintenanceCallback(interop_MaintenanceCallback callback) {
    interop_gsdkPINVOKE.registerMaintenanceCallback(interop_MaintenanceCallback.getCPtr(callback));
  }

  public static void logMessage(string message) {
    interop_gsdkPINVOKE.logMessage(message);
    if (interop_gsdkPINVOKE.SWIGPendingException.Pending) throw interop_gsdkPINVOKE.SWIGPendingException.Retrieve();
  }

  public static string getLogsDirectory() {
    string ret = interop_gsdkPINVOKE.getLogsDirectory();
    return ret;
  }

}

}
