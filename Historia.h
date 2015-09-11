//---------------------------------------------------------------------------

#ifndef HistoriaH
#define HistoriaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class THistorico : public TForm
{
__published:	// IDE-managed Components
  TMemo *Mhistory;
  TPanel *Panel1;
  TButton *BClearHistory;
  void __fastcall BClearHistoryClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall THistorico(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THistorico *Historico;
//---------------------------------------------------------------------------
#endif
