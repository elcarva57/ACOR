//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Historia.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THistorico *Historico;

//------------------------------------------------------------------------------
__fastcall THistorico::THistorico(TComponent* Owner)
  : TForm(Owner)
//------------------------------------------------------------------------------
{
}

//------------------------------------------------------------------------------
void __fastcall THistorico::BClearHistoryClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    Historico->Mhistory->Lines->Clear();
}

//------------------------------------------------------------------------------
void __fastcall THistorico::bGrabarHistoriaClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    TDateTime Fecha;

    Fecha = Now();
    SaveDialog1->FileName = "Historia" + Fecha.FormatString("yyyy-MM-dd HH.mm");

    if (SaveDialog1->Execute())
        Historico->Mhistory->Lines->SaveToFile(SaveDialog1->FileName);
}

