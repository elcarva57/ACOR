//---------------------------------------------------------------------------

#ifndef visualizarH
#define visualizarH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "Foto.h"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel2;
        TEdit *Edit2;
//        TEdit *Edit3;
        TLabel *Label5;
        TEdit *Edit1;
        TLabel *Label4;
        TLabel *Label14;
        TStaticText *PMax;
        TLabel *Label15;
        TStaticText *PMin;
        TLabel *Label1;
        TStaticText *PX;
        TLabel *Label2;
        TStaticText *PY;
        TLabel *Label3;
        TStaticText *PP;
  TEdit *Edit3;
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
/*
  unsigned short *Foto;
  double xm0, ym0;
  WORD maximo, minimo;
  int xmax, ymax, xmin, ymin;
  Graphics::TBitmap *BM;
*/
  cFoto *Foto;
public:		// User declarations
  __fastcall TForm2(TComponent* Owner);
  void __fastcall Pintar();
  void __fastcall Crear(int x, int y);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
