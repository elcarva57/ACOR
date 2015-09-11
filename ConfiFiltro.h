//---------------------------------------------------------------------------

#ifndef ConfiFiltroH
#define ConfiFiltroH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "rueda.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

class TFConfiguracion : public TForm
{
__published:	// IDE-managed Components
//  TPanel *Panel1;
  TPanel *Panel2;
  TPanel *P1;
  TShape *Shape1;
  TStaticText *StaticText1;
  TPanel *Panel3;
  TEdit *Edit2;
  TPanel *P2;
  TShape *Shape2;
  TStaticText *StaticText2;
  TPanel *Panel4;
  TEdit *Edit3;
  TPanel *P3;
  TShape *Shape3;
  TStaticText *StaticText3;
  TPanel *Panel6;
  TEdit *Edit4;
  TPanel *P4;
  TShape *Shape4;
  TStaticText *StaticText4;
  TPanel *Panel8;
  TEdit *Edit5;
  TPanel *P5;
  TShape *Shape5;
  TStaticText *StaticText5;
  TPanel *Panel10;
  TEdit *Edit6;
  TPanel *P6;
  TShape *Shape6;
  TStaticText *StaticText6;
  TPanel *Panel12;
  TEdit *Edit7;
  TPanel *P7;
  TShape *Shape7;
  TStaticText *StaticText7;
  TPanel *Panel14;
  TEdit *Edit8;
  TPanel *P8;
  TShape *Shape8;
  TStaticText *StaticText8;
  TPanel *Panel16;
  TEdit *Edit9;
  TPanel *Panel5;
  TLabel *Label1;
  TPanel *Panel7;
  TTrackBar *TBV;
  TStaticText *TV;
  TSaveDialog *SD1;
  TOpenDialog *OD1;
  TButton *RST;
  TBitBtn *BitBtn2;
  TBitBtn *BitBtn1;
  TBitBtn *BCargar;
  TBitBtn *BGuardar;
  void __fastcall Shape1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall TBVChange(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall BGuardarClick(TObject *Sender);
  void __fastcall BCargarClick(TObject *Sender);
  void __fastcall BitBtn1Click(TObject *Sender);
  void __fastcall RSTClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  TShape *pSh[9];
  TEdit  *pEd[9];
  TPanel *pP[9];
  CRueda *R;
  dr DR;
public:		// User declarations
  __fastcall TFConfiguracion(TComponent* Owner);
  void __fastcall Vis(int n);
};
//---------------------------------------------------------------------------


extern PACKAGE TFConfiguracion *FConfiguracion;
//---------------------------------------------------------------------------


#endif
