// TEMPERATURAIMPL : Implementation of TTemperaturaImpl

#include <vcl.h>
#pragma hdrstop

#include "TEMPERATURAIMPL.H"

#include "Principal.h"
extern TForm1 *Form1;
void kk(int teta);

/////////////////////////////////////////////////////////////////////////////
// TTemperaturaImpl
STDMETHODIMP TTemperaturaImpl::OnEndPage()
{
  HRESULT hr = E_FAIL;
  try
  {
    hr = TASPObject::OnEndPage();
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ITemperatura);
  }

  return hr;
}


STDMETHODIMP TTemperaturaImpl::OnStartPage(LPUNKNOWN AScriptingContext)
{
  HRESULT hr = E_FAIL;
  try
  {
    hr = TASPObject::OnStartPage(AScriptingContext);
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ITemperatura);
  }

  return hr;
}



STDMETHODIMP TTemperaturaImpl::test()
{
  HRESULT hr = S_OK;
  kk(6);
 // TForm1->BClearHistoryClick();

  return hr;

}

