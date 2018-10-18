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

class interop_ConnectedPlayer : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal interop_ConnectedPlayer(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(interop_ConnectedPlayer obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~interop_ConnectedPlayer() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          interop_gsdkPINVOKE.delete_interop_ConnectedPlayer(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public string m_playerId {
    set {
      interop_gsdkPINVOKE.interop_ConnectedPlayer_m_playerId_set(swigCPtr, value);
      if (interop_gsdkPINVOKE.SWIGPendingException.Pending) throw interop_gsdkPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      string ret = interop_gsdkPINVOKE.interop_ConnectedPlayer_m_playerId_get(swigCPtr);
      if (interop_gsdkPINVOKE.SWIGPendingException.Pending) throw interop_gsdkPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public interop_ConnectedPlayer(string playerId) : this(interop_gsdkPINVOKE.new_interop_ConnectedPlayer(playerId), true) {
    if (interop_gsdkPINVOKE.SWIGPendingException.Pending) throw interop_gsdkPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
