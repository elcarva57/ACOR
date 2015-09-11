// TEMPERATURAIMPL.H : Declaration of the TTemperaturaImpl

#ifndef TemperaturaImplH
#define TemperaturaImplH

#define ATL_APARTMENT_THREADED

#include "RocPcServidor_TLB.H"
#include <asphlpr.h>

/////////////////////////////////////////////////////////////////////////////
// TTemperaturaImpl     Implements ITemperatura, default interface of Temperatura
// ThreadingModel : Apartment
// Dual Interface : TRUE
// Default ProgID : RocPcServidor.Temperatura
// Description    : 
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TTemperaturaImpl : 
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<TTemperaturaImpl, &CLSID_Temperatura>,
  public IDispatchImpl<ITemperatura, &IID_ITemperatura, &LIBID_RocPcServidor>,
  public TASPObject
{
public:
  TTemperaturaImpl()
  {
  }

  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otApartment);
  DECLARE_PROGID(_T("RocPcServidor.Temperatura"));
  DECLARE_DESCRIPTION(_T(""));

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TTemperaturaImpl> 
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }

DECLARE_NOT_AGGREGATABLE(TTemperaturaImpl)

BEGIN_COM_MAP(TTemperaturaImpl)
  COM_INTERFACE_ENTRY(ITemperatura)
  COM_INTERFACE_ENTRY2(IDispatch, ITemperatura)
END_COM_MAP()

// ITemperatura
public:
 
  STDMETHOD(OnEndPage());
  STDMETHOD(OnStartPage(LPUNKNOWN AScriptingContext));
  STDMETHOD(test());
};

#endif //[IDEHeaderName]
