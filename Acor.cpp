//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <atl\atlmod.h>
#include <atl\atlmod.h>
#include <atl\atlmod.h>
#include <atl\atlmod.h>
#include "cRocPcServidorImpl.h"
#include "FocuserImpl.h"
#include "CCD1Impl.h"
USEFORM("ConfiFiltro.cpp", FConfiguracion);
USEFORM("Principal.cpp", Form1);
USEFORM("visualizar.cpp", Form2);
USEFORM("Unit3.cpp", FGraficas);
USEFORM("conf_meteo.cpp", FConfigMeteo);
USEFORM("Historia.cpp", Historico);
USEFORM("Enfoque.cpp", Form4);
USEFORM("Programacion.cpp", Fprog);
//---------------------------------------------------------------------------
TComModule _ProjectModule(0 /*InitATLServer*/);
TComModule &_Module = _ProjectModule;

// The ATL Object map holds an array of _ATL_OBJMAP_ENTRY structures that
// described the objects of your OLE server. The MAP is handed to your
// project's CComModule-derived _Module object via the Init method.
//
BEGIN_OBJECT_MAP(ObjectMap)
  OBJECT_ENTRY(CLSID_cRocPcServidor, TcRocPcServidorImpl)
  OBJECT_ENTRY(CLSID_Focuser, TFocuserImpl)
  OBJECT_ENTRY(CLSID_CCD1, TCCD1Impl)
END_OBJECT_MAP()
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        using Forms::Application;
  try
  {
    Application->Initialize();
    Application->CreateForm(__classid(TForm1), &Form1);
         Application->CreateForm(__classid(TFConfiguracion), &FConfiguracion);
         Application->CreateForm(__classid(TFGraficas), &FGraficas);
         Application->CreateForm(__classid(THistorico), &Historico);
         Application->CreateForm(__classid(TForm4), &Form4);
         Application->CreateForm(__classid(TFprog), &Fprog);
         Application->Run();
  }
  catch (Exception &exception)
  {
    Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
