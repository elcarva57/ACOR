// CCD1IMPL.H : Declaration of the TCCD1Impl

#ifndef CCD1ImplH
#define CCD1ImplH

#define ATL_APARTMENT_THREADED

#include "RocPcServidor_TLB.H"


/////////////////////////////////////////////////////////////////////////////
// TCCD1Impl     Implements ICCD1, default interface of CCD1
// ThreadingModel : Apartment
// Dual Interface : TRUE
// Event Support  : FALSE
// Default ProgID : RocPcServidor.CCD1
// Description    : Camara CCD principal
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TCCD1Impl : 
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<TCCD1Impl, &CLSID_CCD1>,
  public IDispatchImpl<ICCD1, &IID_ICCD1, &LIBID_RocPcServidor>
{
public:
  TCCD1Impl()
  {
  }

  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otApartment);
  DECLARE_PROGID("RocPcServidor.CCD1");
  DECLARE_DESCRIPTION("Camara CCD principal");

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TCCD1Impl> 
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }


BEGIN_COM_MAP(TCCD1Impl)
  COM_INTERFACE_ENTRY(ICCD1)
  COM_INTERFACE_ENTRY2(IDispatch, ICCD1)
END_COM_MAP()

// ICCD1
public:
 
  STDMETHOD(Foto());
  STDMETHOD(get_FinFoto(VARIANT_BOOL* Value));
  STDMETHOD(NumFotos(double Numero));
  STDMETHOD(get_Estado(double* Value));
  STDMETHOD(get_FotoActual(double* Value));
  STDMETHOD(Exposicion(double Exposg));
  STDMETHOD(Binin(double Binin));
  STDMETHOD(TipoFoto(double tipo));
  STDMETHOD(nombre(BSTR nombre));
  STDMETHOD(_set_LinkEnabled(VARIANT_BOOL* Value));
  STDMETHOD(get_LinkEnabled(VARIANT_BOOL* Value));
  STDMETHOD(set_LinkEnabled(VARIANT_BOOL Value));
  STDMETHOD(get_DisableAutoShutdown(VARIANT_BOOL* Value));
  STDMETHOD(set_DisableAutoShutdown(VARIANT_BOOL Value));
  STDMETHOD(Expose(double Duration, int Light, int Filter));
  STDMETHOD(SetFullFrame());
  STDMETHOD(set_BinX(short Param1));
  STDMETHOD(set_BinY(short Param1));
  STDMETHOD(get_ImageReady(int* Value));
  STDMETHOD(SaveImage(BSTR path));
};

#endif //CCD1ImplH
