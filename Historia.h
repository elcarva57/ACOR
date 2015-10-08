//---------------------------------------------------------------------------

#ifndef HistoriaH
#define HistoriaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class THistorico : public TForm
{
__published:	// IDE-managed Components
  TMemo *Mhistory;
  TPanel *Panel1;
  TButton *BClearHistory;
    TButton *bGrabarHistoria;
    TSaveDialog *SaveDialog1;
  void __fastcall BClearHistoryClick(TObject *Sender);
    void __fastcall bGrabarHistoriaClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall THistorico(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THistorico *Historico;
//---------------------------------------------------------------------------
#endif
