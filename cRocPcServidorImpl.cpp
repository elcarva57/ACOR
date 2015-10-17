// CROCPCSERVIDORIMPL : Implementation of TcRocPcServidorImpl

#include <vcl.h>
#pragma hdrstop

#include "CROCPCSERVIDORIMPL.H"
#include "Principal.h"
#include "Historia.h"
#include "rueda.h"
#include "ConfiFiltro.h"
//char SalidaCom[]={"  411100110-20.5+30.509.5+24.620.5+05.600000005601518008640000N200010000114h23.1m+14º32'NGC3115B_25.fts00000000038002400000011"};

extern int Temp_x10, Rocio_x10, pluvio, PluvioTotalPrevio, PluvioRelativa, slluvia, snubes, Humedad_x10;
extern int Tccd, Tcaja, Vpeltier, snubes;

extern double tRa, tDe;
void Slew_F(double Ra, double De);
void Slew_F(char *comando);
void GetRaDe_F(double *Ra, double *De);

extern CRueda * Filtro;
extern char Meteo[2000];
//extern void  mover_rueda(int posicion);

/////////////////////////////////////////////////////////////////////////////
// TcRocPcServidorImpl
STDMETHODIMP TcRocPcServidorImpl::OnEndPage()
{
    HRESULT hr;
    try
    {
        hr = TASPObject::OnEndPage();
    }
    catch (Exception &e)
    {
        return Error(e.Message.c_str(), IID_IcRocPcServidor);
    }

    return hr;
}


STDMETHODIMP TcRocPcServidorImpl::OnStartPage(LPUNKNOWN AScriptingContext)
{
    HRESULT hr;
    try
    {
        hr = TASPObject::OnStartPage(AScriptingContext);
    }
    catch (Exception &e)
    {
        return Error(e.Message.c_str(), IID_IcRocPcServidor);
    }

    return hr;
}



STDMETHODIMP TcRocPcServidorImpl::Foto(BSTR nombre)
{
    HRESULT hr = S_OK;
    AnsiString As = nombre;
    char aux[20];

    strncpy(aux, As.c_str(), 1);
    aux[1] = 0;
    if (atoi(aux) == 0)
        Form1->TBBinin->Position = 2;
    else
        Form1->TBBinin->Position = atoi(aux);

    strncpy(aux, &As.c_str()[2], 4);
    aux[4] = 0;
    if (atoi(aux) == 0)
        Form1->Esg->Text = "0001";
    else
        Form1->Esg->Text = aux;

    strncpy(aux, &As.c_str()[7], 1);
    aux[1] = 0;
    Form1->CBimagen->ItemIndex = atoi(aux);
    Historico->Mhistory->Lines->Add(" Tipo Foto: " + AnsiString(atoi(aux)));

    strncpy(aux, &As.c_str()[9], 3);
    aux[3] = 0;
    Form1->ENFotos->Text = atoi(aux);
    Historico->Mhistory->Lines->Add(" N Fotos: " + AnsiString(atoi(aux)));

    strncpy(aux, &As.c_str()[13], 1);
    aux[1] = 0;
    Filtro->mover_rueda(3);   //prueba de mover_rueda
    Historico->Mhistory->Lines->Add(" Filtro: " + AnsiString(atoi(aux)));

    strncpy(aux, &As.c_str()[15], 10);
    aux[11] = 0;
    Form1->ENombreFichero->Text = AnsiString(aux);
    Historico->Mhistory->Lines->Add(" Fichero: " + AnsiString(aux));



    //Form1->BFotoClick(NULL);
    Form1->IFotoMouseDown(NULL, (TMouseButton)NULL, TShiftState(), 0, 0);
    return hr;
}


STDMETHODIMP TcRocPcServidorImpl::Slew(BSTR com)
{
    HRESULT hr = S_OK;
    char comm[300];

    strncpy(comm, &AnsiString(com).c_str()[3], 25);
    Slew_F(comm);
    return hr;
}

STDMETHODIMP TcRocPcServidorImpl::Slewd(double Ra, double De)
{
    HRESULT hr = S_OK;

    Historico->Mhistory->Lines->Add("Slewd Ra: " + AnsiString(Ra) + " De: " + AnsiString(De));
    Form1->arecta->Caption = Ra;
    Form1->declinacion->Caption = De;
    Slew_F(Ra, De);
    return hr;
}


STDMETHODIMP TcRocPcServidorImpl::GetRaDe(double* Ra, double* De) // del SkyMap
{
    HRESULT hr = S_OK;

    GetRaDe_F(Ra, De);
    return hr;
}


STDMETHODIMP TcRocPcServidorImpl::get_Dec(double* Value) //para la aplicacion cliente
{
    try
    {
        *Value = tDe;
    }
    catch (Exception &e)
    {
        return Error(e.Message.c_str(), IID_IcRocPcServidor);
    }
    return S_OK;
};


STDMETHODIMP TcRocPcServidorImpl::get_Ra(double* Value)  //para la aplicacion cliente
{
    try
    {
        *Value = tRa;
    }
    catch (Exception &e)
    {
        return Error(e.Message.c_str(), IID_IcRocPcServidor);
    }
    return S_OK;
};




STDMETHODIMP TcRocPcServidorImpl::get_Tambiente(double* Value)
{
    try
    {
        *Value = Temp_x10 / 10.0;
    }
    catch (Exception &e)
    {
        return Error(e.Message.c_str(), IID_IcRocPcServidor);
    }
    return S_OK;
};



STDMETHODIMP TcRocPcServidorImpl::get_pTccd(double* Value)
{
    int kk;
    try
    {
        float pp = Tccd;
        pp *= 10.0 / 32767.0;
        pp = (pp / 0.01) - 273;

        if ((pp < 100) & (pp > -100))
        {
            kk = pp * 10;
            pp = kk / 10.0;
            *Value = pp;
        }
        else
        {
            *Value = 00;
        }

    }
    catch (Exception &e)
    {
        return Error(e.Message.c_str(), IID_IcRocPcServidor);
    }
    return S_OK;
};


/*
STDMETHODIMP TcRocPcServidorImpl::get_Hrelativa(int* Value)
{
 try
 {
   *Value = 9;//
 }
 catch(Exception &e)
 {
   return Error(e.Message.c_str(), IID_IcRocPcServidor);
 }
 return S_OK;
};

*/

STDMETHODIMP TcRocPcServidorImpl::get_humedadR(double* Value)
{
    try
    {
        *Value =  Humedad_x10;
    }
    catch (Exception &e)
    {
        return Error(e.Message.c_str(), IID_IcRocPcServidor);
    }
    return S_OK;
};



STDMETHODIMP TcRocPcServidorImpl::get_Nubes(long* Value)
{
    try
    {
        *Value = snubes;
    }
    catch (Exception &e)
    {
        return Error(e.Message.c_str(), IID_IcRocPcServidor);
    }
    return S_OK;
};



STDMETHODIMP TcRocPcServidorImpl::get_EstadoCor(long* Value)
{
    try
    {
        if (  Form1->SC->Brush->Color == clLime)
            *Value = 1;
        else
            *Value = 0;
    }
    catch (Exception &e)
    {
        return Error(e.Message.c_str(), IID_IcRocPcServidor);
    }
    return S_OK;
};



STDMETHODIMP TcRocPcServidorImpl::get_MensEMAv2(BSTR* Value)
{
    AnsiString cadena;


    try
    {
        cadena = Meteo;
        *Value = WideString(cadena).Copy();
    }
    catch (Exception &e)
    {
        return Error(e.Message.c_str(), IID_IcRocPcServidor);
    }
    return S_OK;
};



STDMETHODIMP TcRocPcServidorImpl::FocusMove(double Pasos)
{

}


STDMETHODIMP TcRocPcServidorImpl::get_FocusPosition(double* Value)
{

};



STDMETHODIMP TcRocPcServidorImpl::get_FocusAbsolute(long* Value)
{
    try
    {

    }
    catch (Exception &e)
    {
        return Error(e.Message.c_str(), IID_IcRocPcServidor);
    }
    return S_OK;
};



