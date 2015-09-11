// CCD1IMPL : Implementation of TCCD1Impl (CoClass: CCD1, Interface: ICCD1)

#include <vcl.h>
#pragma hdrstop

#include "CCD1IMPL.H"
#include "Principal.h"
#include "Historia.h"
#include "rueda.h"
#include "ConfiFiltro.h"

extern CRueda * Filtro;
extern LinkEnabled_flag, DisableAutoShutdown_flag;
extern void QuitaRectangulo(void);
extern bool FinFoto;
/////////////////////////////////////////////////////////////////////////////
// TCCD1Impl

STDMETHODIMP TCCD1Impl::Foto()
{
 Historico->Mhistory->Lines->Add(" Foto CCD1");
 Form1->IFotoMouseDown(NULL, (TMouseButton)NULL, TShiftState(), 0, 0);
}

STDMETHODIMP TCCD1Impl::get_FinFoto(VARIANT_BOOL* Value)
{
};


STDMETHODIMP TCCD1Impl::NumFotos(double Numero)
{ 
   Form1->ENFotos->Text = Numero;
}


STDMETHODIMP TCCD1Impl::get_Estado(double* Value)
{
  try
  {
      *Value = Form1->PBF->Position;
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ICCD1);
  }
  return S_OK;
};



STDMETHODIMP TCCD1Impl::get_FotoActual(double* Value)
{
  try
  {

         *Value = Form1->TNFotos->Caption.ToDouble();

  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ICCD1);
  }
  return S_OK;
};



STDMETHODIMP TCCD1Impl::Exposicion(double Exposg)
{ 
    Form1->Esg->Text = Exposg;
}


STDMETHODIMP TCCD1Impl::Binin(double Binin)
{ 
  Form1->TBBinin->Position = Binin;
}


STDMETHODIMP TCCD1Impl::TipoFoto(double tipo)
{ 
   Form1->TBBinin->Position = tipo;
}


STDMETHODIMP TCCD1Impl::nombre(BSTR nombre)
{ 
   Form1->ENombreFichero->Text = AnsiString(nombre);
}


STDMETHODIMP TCCD1Impl::_set_LinkEnabled(VARIANT_BOOL* Value)
{
  try
  {
      LinkEnabled_flag = *Value;
     Historico->Mhistory->Lines->Add ("set_Link 1 " );
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ICCD1);
  }
  return S_OK;
};


 //Controls the link between MaxIm CCD and the camera.
STDMETHODIMP TCCD1Impl::get_LinkEnabled(VARIANT_BOOL* Value)
{
  try
  {
       *Value = LinkEnabled_flag;
       if(LinkEnabled_flag)
     Historico->Mhistory->Lines->Add ("get_Link on" );
       else
       Historico->Mhistory->Lines->Add ("get_Link oFF" );
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ICCD1);
  }
  return S_OK;
};

STDMETHODIMP TCCD1Impl::set_LinkEnabled(VARIANT_BOOL Value)
{
  try
  {
       LinkEnabled_flag = Value;
       if (Value)
     Historico->Mhistory->Lines->Add ("set_Link 2 ON" );
     else
          Historico->Mhistory->Lines->Add ("set_Link 2 OFF" );
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ICCD1);
  }
  return S_OK;
};


//When true, the camera will not be automatically shut down when the object is
//destroyed (i.e. when the script exits). Default value is false.
STDMETHODIMP TCCD1Impl::get_DisableAutoShutdown(VARIANT_BOOL* Value)
{
  try
  {
       *Value = DisableAutoShutdown_flag;
       Historico->Mhistory->Lines->Add ("get DisableAuto" );
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ICCD1);
  }
  return S_OK;
};

STDMETHODIMP TCCD1Impl::set_DisableAutoShutdown(VARIANT_BOOL Value)
{
  try
  {
    DisableAutoShutdown_flag = Value;
    Historico->Mhistory->Lines->Add ("Set DisableAuto" );
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ICCD1);
  }
  return S_OK;
};


/*
Starts an exposure. Use ImageReady to check when the exposure is complete.
An error occurs if the exposure cannot be started.
If no filter is specified, or if a negative number is specified,
the filter wheel remains at its previous position.
- Double Duration – Duration of exposure in seconds
- Short Light  1 for light frame, 0 for dark frame (ignored if no shutter)
- Short Filter  (optional) Index of filter to use; first filter is 0 (ignored if no filter wheel)
Returns: Boolean  True if successful */
STDMETHODIMP TCCD1Impl::Expose(double Duration, int Light, int Filter)
{
     Historico->Mhistory->Lines->Add ("Exponiendo " + (AnsiString)(Duration) + "sg, Filtro " + (AnsiString)(Filter));

    Form1->Esg->Text = (int)(Duration);
    Form1->CBimagen->ItemIndex = Light;
    Filtro->mover_rueda(Filter);
    Form1->IFotoMouseDown(NULL, (TMouseButton)NULL, TShiftState(), 0, 0);

     return S_OK;
}


STDMETHODIMP TCCD1Impl::SetFullFrame()
{
   QuitaRectangulo();
}


STDMETHODIMP TCCD1Impl::set_BinX(short Param1)
{
  try
  {
      Form1->TBBinin->Position = Param1;
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ICCD1);
  }
  return S_OK;
};


STDMETHODIMP TCCD1Impl::set_BinY(short Param1)
{
  try
  {
     Form1->TBBinin->Position = Param1;
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ICCD1);
  }
  return S_OK;
};



STDMETHODIMP TCCD1Impl::get_ImageReady(int* Value)
{
  try
  {
     if (FinFoto == 1)
       *Value = 1;
     else
       *Value = 0;  
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_ICCD1);
  }
  return S_OK;
};



STDMETHODIMP TCCD1Impl::SaveImage(BSTR path)
{
  Form1->ENombreFichero->Text = path;
//  Historico->Mhistory->Lines->Add (path);
}


