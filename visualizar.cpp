//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "visualizar.h"
#include "Principal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
void RellenarBitmap(int x1, int y1, int x2, int y2);
void Lupa(int X, int Y, cFoto *Foto, bool actualizar);
extern WORD Valores[7][7];
extern TColor Colores[7][7];

extern TForm2 *FActivo;
extern double x0, y0;
extern int X1F, X2F, Y1F, Y2F;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Crear(int x, int y)
{
  Foto = new cFoto(x, y, x0, y0);
  ClientWidth = x;
  ClientHeight = y + Panel2->Height;
}

void __fastcall TForm2::Pintar()
{
  Foto->Pintar();
  BitBlt(Canvas->Handle, 0, 0, Foto->BM->Width, Foto->BM->Height, Foto->BM->Canvas->Handle, 0, 0, SRCCOPY);
  PMax->Caption = Foto->maximo;
  PMin->Caption = Foto->minimo;
  Show();
}


void __fastcall TForm2::FormPaint(TObject *Sender)
{
  Foto->Pintar();
  BitBlt(Canvas->Handle, 0, 0, Foto->BM->Width, Foto->BM->Height, Foto->BM->Canvas->Handle, 0, 0, SRCCOPY);
  /*
  PMax->Caption = Foto->maximo;
  PMin->Caption = Foto->minimo;
  Edit1->Text = Foto->media();
  Edit2->Text = Foto->fondocielo;
  Edit3->Text = Foto->fullhalfwide();
  */

}
//---------------------------------------------------------------------------


void __fastcall TForm2::FormActivate(TObject *Sender)
{
/*
  char aux[300];
  HWND oHandle = GetFocus();

  wsprintf(aux, "%X", oHandle);
  Edit1->Text = aux;
  wsprintf(aux, "%X", Handle);
  Edit2->Text = aux;
*/
  FActivo = this;
}
//---------------------------------------------------------------------------



extern int celdaX, celdaY;


void __fastcall TForm2::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  if(Shift.Contains(ssRight	))
  {
    Lupa(X, Y, Foto, false);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
  if((X>=Foto->BM->Width)||(Y>=Foto->BM->Height))
        return;
  if(Shift.Contains(ssRight	))
  {
    Lupa(X, Y, Foto, false);
  }
  PX->Caption = X;
  PY->Caption = Y;
  PP->Caption = Foto->Pixeles[Y * Foto->BM->Width + X];
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
  if(FActivo == this)
  {
    FActivo = NULL;
  }
  delete Foto;
  Foto = NULL;
  RellenarBitmap(X1F, Y1F, X2F, Y2F);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{
  if(WheelDelta > 0)
  {
    if(AlphaBlendValue < 250)
      AlphaBlendValue += 5;
  }
  else
  {
    if(AlphaBlendValue > 5)
      AlphaBlendValue -= 5;
  }
  Handled = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
  switch(Key)
  {
    case VK_DOWN:
    case VK_LEFT:
      if(Shift.Contains(ssShift))
      {
        if(Form1->TBx0->Position >= 10)
          Form1->TBx0->Position -= 10;
      }
      else
        if(Form1->TBy0->Position >= 10)
          Form1->TBy0->Position -= 10;
      break;
    case VK_UP:
    case VK_RIGHT:
      if(Shift.Contains(ssShift))
      {
        if(Form1->TBx0->Position <= (0x7FFF-0x000A))
          Form1->TBx0->Position += 10;
      }
      else
        if(Form1->TBy0->Position <= (0x7FFF-0x000A))
          Form1->TBy0->Position += 10;
      break;
    case VK_NEXT:
      if(Shift.Contains(ssShift))
      {
        if(Form1->TBx0->Position <= (0x7FFF-50))
          Form1->TBx0->Position += 50;
      }
      else
        if(Form1->TBy0->Position <= (0x7FFF-50))
          Form1->TBy0->Position += 50;
      break;
    case VK_PRIOR:
      if(Shift.Contains(ssShift))
      {
        if(Form1->TBx0->Position >= 50)
          Form1->TBx0->Position -= 50;
      }
      else
        if(Form1->TBy0->Position >= 50)
          Form1->TBy0->Position -= 50;
      break;
    case VK_HOME:
      if(Shift.Contains(ssShift))
        Form1->TBx0->Position = 0;
      else
        Form1->TBy0->Position = 0;
      break;
    case VK_END:
      if(Shift.Contains(ssShift))
        Form1->TBx0->Position = 0x07FFF;
      else
        Form1->TBy0->Position = 0x07FFF;
      break;
  }
}
//---------------------------------------------------------------------------

