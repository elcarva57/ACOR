//---------------------------------------------------------------------------

#ifndef aplicH
#define aplicH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <Grids.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TTimer *Timer1;
  TPageControl *PageControl1;
  TTabSheet *CAMARA;
  TPanel *PCFS;
  TTabSheet *CUPULA;
  TPanel *Panel12;
  TLabel *Label18;
  TSpeedButton *SpeedButton1;
  TPanel *P1;
  TShape *Sbit8;
  TSpeedButton *bit8;
  TPanel *Panel14;
  TShape *Sbit7;
  TSpeedButton *bit7;
  TPanel *Panel15;
  TShape *Sbit6;
  TSpeedButton *bit6;
  TPanel *Panel16;
  TShape *Sbit5;
  TSpeedButton *bit5;
  TPanel *Panel17;
  TShape *Sbit4;
  TSpeedButton *bit4;
  TPanel *Panel18;
  TShape *Sbit3;
  TSpeedButton *bit3;
  TPanel *Panel19;
  TShape *Sbit2;
  TSpeedButton *bit2;
  TPanel *Panel20;
  TShape *Sbit1;
  TSpeedButton *bit1;
  TPanel *Panel21;
  TLabel *Label20;
  TPanel *Panel3;
  TPanel *Panel44;
  TShape *ss24;
  TLabel *Label43;
  TPanel *Panel43;
  TShape *ss23;
  TLabel *Label42;
  TPanel *Panel42;
  TShape *ss22;
  TLabel *Label41;
  TPanel *Panel41;
  TShape *ss21;
  TLabel *Label40;
  TPanel *Panel40;
  TShape *ss20;
  TLabel *Label39;
  TPanel *Panel39;
  TShape *ss19;
  TLabel *Label38;
  TPanel *Panel45;
  TPanel *Panel32;
  TShape *ss18;
  TLabel *Label32;
  TPanel *Panel38;
  TShape *ss17;
  TLabel *Label37;
  TPanel *Panel37;
  TShape *ss16;
  TLabel *Label36;
  TPanel *Panel36;
  TShape *ss15;
  TLabel *Label35;
  TPanel *Panel35;
  TShape *ss14;
  TLabel *Label34;
  TPanel *Panel34;
  TShape *ss13;
  TLabel *Label33;
  TPanel *Panel46;
  TPanel *Panel31;
  TShape *ss12;
  TLabel *Label31;
  TPanel *Panel30;
  TShape *ss11;
  TLabel *Label30;
  TPanel *Panel29;
  TShape *ss10;
  TLabel *Label29;
  TPanel *Panel28;
  TShape *ss9;
  TLabel *Label28;
  TPanel *Panel27;
  TShape *ss8;
  TLabel *Label27;
  TPanel *Panel26;
  TShape *ss7;
  TLabel *Label26;
  TPanel *Panel47;
  TPanel *Panel25;
  TShape *ss6;
  TLabel *Label25;
  TPanel *Panel24;
  TShape *ss5;
  TLabel *Label24;
  TPanel *Panel23;
  TShape *ss4;
  TLabel *Label23;
  TPanel *Panel22;
  TShape *ss3;
  TLabel *Label22;
  TPanel *Panel13;
  TShape *ss2;
  TLabel *Label21;
  TPanel *Panel33;
  TShape *ss1;
  TLabel *Label19;
  TPanel *Panel2;
  TComboBox *CBEnviar;
  TBitBtn *BEnviar;
  TPanel *Panel1;
  TTabSheet *TELESCOPIO;
  TTabSheet *CONFIGURACION;
  TTabSheet *VISUALIZACION;
  TPanel *Panel6;
  TLabel *Label12;
  TLabel *Label13;
  TEdit *EOffset;
  TEdit *EStretch;
  TPanel *Panel7;
  TScrollBox *PFotoO;
  TPaintBox *PB1;
  TToolBar *ToolBar1;
  TPanel *Panel48;
  TLabel *Label14;
  TLabel *Label15;
  TPanel *PMax;
  TPanel *PMin;
  TPanel *Panel4;
  TLabel *Label6;
  TLabel *Label7;
  TLabel *Label4;
  TLabel *Label5;
  TCheckBox *CBR;
  TCheckBox *CBT;
  TPanel *PX1;
  TPanel *PY1;
  TPanel *PX2;
  TPanel *PY2;
  TPanel *Panel10;
  TLabel *Label16;
  TLabel *Label17;
  TEdit *Esg;
  TEdit *Emsg;
  TPanel *Panel49;
  TLabel *Label1;
  TLabel *Label44;
  TLabel *Label45;
  TPanel *PP;
  TPanel *PY;
  TPanel *PX;
  TPanel *PStatus;
  TPanel *PRABBIT;
  TPanel *PHOST;
  TToolButton *ToolButton1;
  TPanel *Panel9;
  TLabel *Label9;
  TLabel *Label11;
  TPanel *PFil;
  TPanel *PCol;
  TPanel *Panel50;
  TLabel *Label8;
  TPanel *Panel5;
  TPanel *Panel8;
  TRadioButton *RBK400;
  TRadioButton *RBK1600;
  TPanel *Panel51;
  TLabel *Label3;
  TPanel *PColumnas;
  TLabel *Label2;
  TPanel *PFilas;
  TTrackBar *TBBinin;
  TPanel *PBinin;
  TPanel *Panel11;
  TPanel *PShuter;
  TPanel *PFiltro;
  TImageList *ImageList1;
  TPanel *Panel52;
  TDrawGrid *DG1;
  TPanel *Panel53;
  TDrawGrid *DG2;
  TPanel *Panel54;
  TBitBtn *BAbrir;
  TBitBtn *BGuardar;
  TOpenDialog *OD1;
  TSaveDialog *SD1;
  TMemo *Memo1;
  TTrackBar *TBSt;
  TTrackBar *TBOff;
  TPanel *PFoto;
  TShape *SLedFoto;
  TImage *IFoto;
  TPanel *PCancel;
  TPanel *Panel55;
  TRadioButton *RBH;
  TRadioButton *RBD;
  TShape *SC;
  void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall BEnviarClick(TObject *Sender);
  void __fastcall BFotoClick(TObject *Sender);
  void __fastcall EBininChange(TObject *Sender);
  void __fastcall CBRClick(TObject *Sender);
  void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
  void __fastcall IFotoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall RBK400Click(TObject *Sender);
  void __fastcall RBK1600Click(TObject *Sender);
  void __fastcall EOffsetChange(TObject *Sender);
  void __fastcall EStretchChange(TObject *Sender);
  void __fastcall SpeedButton1Click(TObject *Sender);
  void __fastcall TBBininChange(TObject *Sender);
  void __fastcall LConfigurarClick(TObject *Sender);
  void __fastcall BAbrirClick(TObject *Sender);
  void __fastcall TBStChange(TObject *Sender);
  void __fastcall BGuardarClick(TObject *Sender);
  void __fastcall TBOffChange(TObject *Sender);
  void __fastcall PFotoMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall PCancelMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall PCancelMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
  void __fastcall Repintar();
  void __fastcall pb1Repintar();
  void __fastcall printerror( int status);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
