// FOCUSERIMPL : Implementation of TFocuserImpl (CoClass: Focuser, Interface: IFocuser)

#include <vcl.h>
#pragma hdrstop

#include "FOCUSERIMPL.H"
#include "Principal.h"
#include "Historia.h"

extern bool FinX, EsperandoFinX;
/////////////////////////////////////////////////////////////////////////////
// TFocuserImpl

STDMETHODIMP TFocuserImpl::get_Position(double* Value)
{
  try
  {
      *Value = Form1->PContador->Caption.ToDouble();
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_IFocuser);
  }
  return S_OK;
};


STDMETHODIMP TFocuserImpl::Move(double destino)
{
int PosActual, PosFinal, pasos;

  HRESULT hr = S_OK;

Historico->Mhistory->Lines->Add(" Pasos in: " + AnsiString(destino) );
  PosFinal = (int)destino;
  PosActual = Form1->PContador->Caption.ToInt();
  pasos = PosFinal -  PosActual;
  Form1->EPasosEnfoque->Text = (abs)(pasos);
  if (pasos > 0)
     Form1->subirClick(NULL);
  else
     Form1->bajarClick(NULL);

  return hr;
}

STDMETHODIMP TFocuserImpl::get_Absolute(double* absoluto)
{
  try
  {
      *absoluto = 1;
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_IFocuser);
  }
  return S_OK;
};



STDMETHODIMP TFocuserImpl::get_IsMoving(VARIANT_BOOL* Value)
{
  try
  {
     if (FinX == 1) {
      *Value = 0;
     }
     else if (FinX == 0){
       *Value = 1;
     }

  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_IFocuser);
  }
  return S_OK;
};



STDMETHODIMP TFocuserImpl::get_MaxIncrement(long* Value)
{
  try
  {
     *Value = 10000;
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_IFocuser);
  }
  return S_OK;
};


STDMETHODIMP TFocuserImpl::get_MaxStep(long* Value)
{
  try
  {
      *Value = 32000;
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_IFocuser);
  }
  return S_OK;
};


STDMETHODIMP TFocuserImpl::get_StepSize(long* Value)
{
  try
  {

  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_IFocuser);
  }
  return S_OK;
};


STDMETHODIMP TFocuserImpl::Halt()
{
    Form1->Button1Click(NULL);
    return S_OK;
}

STDMETHODIMP TFocuserImpl::get_TempComp(VARIANT_BOOL* Value)
{
  try
  {
      *Value = 0;
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_IFocuser);
  }
  return S_OK;
};


STDMETHODIMP TFocuserImpl::get_TempCompAvailable(VARIANT_BOOL* Value)
{
  try
  {
     *Value = 0;
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_IFocuser);
  }
  return S_OK;
};


STDMETHODIMP TFocuserImpl::get_Temperature(long* Value)
{
  try
  {

  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_IFocuser);
  }
  return S_OK;
};

STDMETHODIMP TFocuserImpl::set_TempComp(VARIANT_BOOL Value)
{
  try
  {

  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_IFocuser);
  }
  return S_OK;
};



