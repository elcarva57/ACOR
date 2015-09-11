// CROCPCSERVIDORIMPL.H : Declaration of the TcRocPcServidorImpl

#ifndef cRocPcServidorImplH
#define cRocPcServidorImplH

#define ATL_APARTMENT_THREADED

#include "RocPcServidor_TLB.H"
#include <asphlpr.h>

/////////////////////////////////////////////////////////////////////////////
// TcRocPcServidorImpl     Implements IcRocPcServidor, default interface of cRocPcServidor
// ThreadingModel : Apartment
// Dual Interface : TRUE
// Default ProgID : RocPcServidor.cRocPcServidor
// Description    : 
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TcRocPcServidorImpl : 
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<TcRocPcServidorImpl, &CLSID_cRocPcServidor>,
  public IDispatchImpl<IcRocPcServidor, &IID_IcRocPcServidor, &LIBID_RocPcServidor>,
  public TASPObject
{
public:
  TcRocPcServidorImpl()
  {
  }

  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otApartment);
  DECLARE_PROGID(_T("RocPcServidor.cRocPcServidor"));
  DECLARE_DESCRIPTION(_T(""));

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TcRocPcServidorImpl> 
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }

DECLARE_NOT_AGGREGATABLE(TcRocPcServidorImpl)

BEGIN_COM_MAP(TcRocPcServidorImpl)
  COM_INTERFACE_ENTRY(IcRocPcServidor)
  COM_INTERFACE_ENTRY2(IDispatch, IcRocPcServidor)
END_COM_MAP()

// IcRocPcServidor
public:
 
  STDMETHOD(OnEndPage());
  STDMETHOD(OnStartPage(LPUNKNOWN AScriptingContext));
  STDMETHOD(Foto(BSTR nombre));
  STDMETHOD(Slew(BSTR com));
  STDMETHOD(Slewd(double Ra, double De));
  STDMETHOD(GetRaDe(double* Ra, double* De));
  STDMETHOD(get_Dec(double* Value));
  STDMETHOD(get_Ra(double* Value));

  STDMETHOD(get_Tambiente(double* Value));
  STDMETHOD(get_pTccd(double* Value));
 // STDMETHOD(get_Hrelativa(int* Value));
  STDMETHOD(get_humedadR(double* Value));
  STDMETHOD(get_Nubes(long* Value));

  STDMETHOD(get_EstadoCor(long* Value));
  STDMETHOD(get_MensEMAv2(BSTR* Value));
  STDMETHOD(FocusMove(double Pasos));
  STDMETHOD(get_FocusPosition(double* Value));
  STDMETHOD(get_FocusAbsolute(long* Value));
};

#endif //[IDEHeaderName]
