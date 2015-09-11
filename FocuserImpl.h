// FOCUSERIMPL.H : Declaration of the TFocuserImpl

#ifndef FocuserImplH
#define FocuserImplH

#define ATL_APARTMENT_THREADED

#include "RocPcServidor_TLB.H"


/////////////////////////////////////////////////////////////////////////////
// TFocuserImpl     Implements IFocuser, default interface of Focuser
// ThreadingModel : Apartment
// Dual Interface : TRUE
// Event Support  : FALSE
// Default ProgID : RocPcServidor.Focuser
// Description    : Enfocador CFS
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TFocuserImpl : 
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<TFocuserImpl, &CLSID_Focuser>,
  public IDispatchImpl<IFocuser, &IID_IFocuser, &LIBID_RocPcServidor>
{
public:
  TFocuserImpl()
  {
  }

  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otApartment);
  DECLARE_PROGID("RocPcServidor.Focuser");
  DECLARE_DESCRIPTION("Enfocador CFS");

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TFocuserImpl> 
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }


BEGIN_COM_MAP(TFocuserImpl)
  COM_INTERFACE_ENTRY(IFocuser)
  COM_INTERFACE_ENTRY2(IDispatch, IFocuser)
END_COM_MAP()

// IFocuser
public:
 
  STDMETHOD(get_Position(double* Value));
  STDMETHOD(Move(double destino));
  STDMETHOD(get_Absolute(double* absoluto));
  STDMETHOD(get_IsMoving(VARIANT_BOOL* Value));
  STDMETHOD(get_MaxIncrement(long* Value));
  STDMETHOD(get_MaxStep(long* Value));
  STDMETHOD(get_StepSize(long* Value));
  STDMETHOD(Halt());
  STDMETHOD(get_TempComp(VARIANT_BOOL* Value));
  STDMETHOD(get_TempCompAvailable(VARIANT_BOOL* Value));
  STDMETHOD(get_Temperature(long* Value));
  STDMETHOD(set_TempComp(VARIANT_BOOL Value));
};

#endif //FocuserImplH
