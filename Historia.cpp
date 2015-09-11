//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Historia.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THistorico *Historico;
//---------------------------------------------------------------------------
__fastcall THistorico::THistorico(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THistorico::BClearHistoryClick(TObject *Sender)
{
  Historico->Mhistory->Lines->Clear();
}
//---------------------------------------------------------------------------

