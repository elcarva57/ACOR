//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "aplic.h"
#include "socket.h"
#include "rueda.h"
#include "ConfiFiltro.h"
#include "fitsio.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
typedef struct {
  TLogPalette lpal;
  TPaletteEntry dummy[256];
} LogPal;
LogPal SysPal;
//---------------------------------------------------------------------------
DWORD TFoto;
BYTE nFoto = 0;
//---------------------------------------------------------------------------
void printerror( int status);
int ejex, ejey;

void AnalizarCFS(char c);
CRueda * Filtro = NULL;
CRueda * Shuter = NULL;

//////////////////////////////////
char Salidas, Grupos[4];
//////////////////////////////////

char Binin = 1;
CSocket *S1 = NULL;
AnsiString EstadoRabbit = "", EstadoAnterior = "";
TColor ColorEstado = clBlack;
Graphics::TBitmap *BM1;
int tamano;
unsigned short Foto[2000][2000];
BYTE Linea[2000];
int x0 = 0 , y0 = 256;
WORD maximo = 0, minimo = 0;
extern bool LineaNueva;
extern int numeroLinea;
int numeroLineaanterior = 0;
int nl = 0;
int NumeroFilas = 0;
int NumeroColumnas = 0;
int X1, X2, Y1, Y2;
TForm1 *Form1;
int X1F = 0, X2F = 0, Y1F = 0, Y2F = 0;
bool LeyendoFoto = false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner):TForm(Owner)
{
  char *ptr;
  char aux[100];
  S1 = new CSocket();
  wsprintf(aux, "     %s  %s", S1->NombreHostLocal, S1->cadenaIP);
  PHOST->Caption = aux;

  LeyendoFoto = false;

  PBinin->Caption = (int)Binin;
  TBBinin->Position = (int)Binin;

  NumeroFilas = PFilas->Caption.ToInt() / Binin;
  NumeroColumnas = PColumnas->Caption.ToInt() / Binin;
  PB1->Width = NumeroColumnas + 4;
  PB1->Height = NumeroFilas + 4;
  X1F = X1 = PX1->Caption.ToInt();
  X2F = X2 = PX2->Caption.ToInt();
  Y1F = Y1 = PY1->Caption.ToInt();
  Y2F = Y2 = PY2->Caption.ToInt();
  SysPal.lpal.palVersion = 0x300;
  SysPal.lpal.palNumEntries = 256;
  for(int c = 0; c < 256; c++)
  {
    SysPal.dummy[c].peRed = c;
    SysPal.dummy[c].peGreen = c;
    SysPal.dummy[c].peBlue = c;
    SysPal.dummy[c].peFlags = PC_NOCOLLAPSE;
  }

  BM1 = new Graphics::TBitmap();
  BM1->Height = NumeroFilas;
  BM1->Width = NumeroColumnas;
  BM1->PixelFormat = pf8bit;
  BM1->Palette = CreatePalette(&SysPal.lpal);

  Filtro = new CRueda(PFiltro, 0, 0, 130, 7, "Filtro", 'z');
  //PFiltro->Left = 20;
  PFiltro->Width = Filtro->Width;
  PFiltro->Height = Filtro->Height;
  Filtro->S1 = S1;
  Filtro->enviarReset();

  Shuter = new CRueda(PShuter, 0, 0, 130, 3, "Shuter", 'y');
  //PShuter->Left = 20;
  PShuter->Width = Shuter->Width;
  PShuter->Height = Shuter->Height;
  Shuter->S1 = S1;
  Shuter->enviarReset();
}


//---------------------------------------------------------------------------
void AnalizarCFS(char c)
{
  if(Filtro != NULL)
    Filtro->Analizar(c);
  if(Shuter != NULL)
    Shuter->Analizar(c);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  char *ptr;
  char aux[300];
  static char cfs[50] = "                                                 ";
  int aa;
  TColor col[2] = {clGray, clRed};
  TColor col1[2] = {clGray, clLime};

  PRABBIT->Caption = "    Rabbit: " + AnsiString(S1->cadenaIPRabbit);
  if(S1->PerdidaConexion == true)
  {
    EstadoRabbit = "    Rabbit no responde";
    ColorEstado = clRed;
  }
  else
  {
    EstadoRabbit = AnsiString("    Rabbit ") + AnsiString(S1->cadenaIPRabbit);
    ColorEstado = clLime;//clBlack;
    if(S1->nDatosRabbit >= 17)
    {
      S1->LeerRabbit(aux, 100);
      aux[18] = 0;
      Panel1->Caption = aux;
    }
    if(S1->nDatosCFS > 0)
    {
      aa = S1->nDatosCFS;
      S1->LeerCFS(aux, 50);
      for(int kk = 0; kk < aa; kk++)
      {
        for(int pp = 0; pp < 48; pp++)
        {
          cfs[pp] = cfs[pp + 1];
        }
        cfs[48] = aux[kk];
        AnalizarCFS(aux[kk]);
      }
      cfs[49] = 0;
      PCFS->Caption = cfs;
    }
    if(S1->nDatosLX200 > 0)
    {
    }
  }
  if(EstadoRabbit != EstadoAnterior)
  {
    EstadoAnterior = EstadoRabbit;
    PStatus->Font->Color = ColorEstado;
    //PStatus->Caption = EstadoRabbit;
    SC->Brush->Color = ColorEstado;
  }
//  if(numeroLinea < 0)
//    return;
  if(LeyendoFoto == true)
  {
    if(LineaNueva == true)
    {
      LineaNueva = false;
      SLedFoto->Brush->Color = clLime;
      SLedFoto->Repaint();
      nl = numeroLinea;
      Repintar();
    }
    else
    {
      if(PFoto->BevelOuter == bvLowered)
      {
        if(SLedFoto->Brush->Color != clRed)
        {
          SLedFoto->Brush->Color = clRed;
          SLedFoto->Repaint();
        }
      }
    }
    if((nl >= Y2F))/* ||
       (GetTickCount() >= TFoto + Esg->Text.ToInt() * 1000 + Emsg->Text.ToInt() + 5000))*/
    {
      if(PFoto->BevelOuter == bvLowered)
      {
        PFoto->BevelOuter = bvRaised;
        PFoto->Color = clSilver;
        SLedFoto->Brush->Color = clGray;
        SLedFoto->Repaint();
        IFoto->Picture->Bitmap->LoadFromResourceName((int)HInstance, "FOTO");
        LeyendoFoto = false;
      }
    }
  }
  Sbit1->Brush->Color = col[Salidas & 0x01];
  Sbit2->Brush->Color = col[(Salidas & 0x02) >> 1];
  Sbit3->Brush->Color = col[(Salidas & 0x04) >> 2];
  Sbit4->Brush->Color = col[(Salidas & 0x08) >> 3];
  Sbit5->Brush->Color = col[(Salidas & 0x10) >> 4];
  Sbit6->Brush->Color = col[(Salidas & 0x20) >> 5];
  Sbit7->Brush->Color = col[(Salidas & 0x40) >> 6];
  Sbit8->Brush->Color = col[(Salidas & 0x80) >> 7];

  ss1->Brush->Color = col1[Grupos[0] & 0x01];
  ss2->Brush->Color = col1[(Grupos[0] & 0x02) >> 1];
  ss3->Brush->Color = col1[(Grupos[0] & 0x04) >> 2];
  ss4->Brush->Color = col1[(Grupos[0] & 0x08) >> 3];
  ss5->Brush->Color = col1[(Grupos[0] & 0x10) >> 4];
  ss6->Brush->Color = col1[(Grupos[0] & 0x20) >> 5];

  ss7->Brush->Color = col1[Grupos[1] & 0x01];
  ss8->Brush->Color = col1[(Grupos[1] & 0x02) >> 1];
  ss9->Brush->Color = col1[(Grupos[1] & 0x04) >> 2];
  ss10->Brush->Color = col1[(Grupos[1] & 0x08) >> 3];
  ss11->Brush->Color = col1[(Grupos[1] & 0x10) >> 4];
  ss12->Brush->Color = col1[(Grupos[1] & 0x20) >> 5];

  ss13->Brush->Color = col1[Grupos[2] & 0x01];
  ss14->Brush->Color = col1[(Grupos[2] & 0x02) >> 1];
  ss15->Brush->Color = col1[(Grupos[2] & 0x04) >> 2];
  ss16->Brush->Color = col1[(Grupos[2] & 0x08) >> 3];
  ss17->Brush->Color = col1[(Grupos[2] & 0x10) >> 4];
  ss18->Brush->Color = col1[(Grupos[2] & 0x20) >> 5];

  ss19->Brush->Color = col1[Grupos[3] & 0x01];
  ss20->Brush->Color = col1[(Grupos[3] & 0x02) >> 1];
  ss21->Brush->Color = col1[(Grupos[3] & 0x04) >> 2];
  ss22->Brush->Color = col1[(Grupos[3] & 0x08) >> 3];
  ss23->Brush->Color = col1[(Grupos[3] & 0x10) >> 4];
  ss24->Brush->Color = col1[(Grupos[3] & 0x20) >> 5];
}


//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  Timer1->Enabled = false;
  delete Filtro;
  delete Shuter;
  delete S1;
  delete BM1;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::BEnviarClick(TObject *Sender)
{
  char aux[300];

  aux[0] = 50;
  strcpy(&aux[2], CBEnviar->Text.c_str());
  S1->Escribir(aux, CBEnviar->Text.Length() + 2, S1->IPRabbit);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::BFotoClick(TObject *Sender)
{
  char *ptr;
  char aux[300];

  X1 = atoi(PX1->Caption.c_str());
  X2 = atoi(PX2->Caption.c_str());
  Y1 = atoi(PY1->Caption.c_str());
  Y2 = atoi(PY2->Caption.c_str());
  if(X1 > X2)
  {
    X1F = X2;
    X2F = X1;
  }
  else
  {
    X1F = X1;
    X2F = X2;
  }
  if(Y1 > Y2)
  {
    Y1F = Y2;
    Y2F = Y1;
  }
  else
  {
    Y1F = Y1;
    Y2F = Y2;
  }

  PB1->Width = NumeroColumnas + 4;
  PB1->Height = NumeroFilas + 4;
  for (int y = 0; y < NumeroFilas; y++)
  {
    for (int x = 0; x < NumeroColumnas; x++)
    {
      Foto[y][x] = 0;
    }
  }
  delete BM1;
  BM1 = new Graphics::TBitmap();
  BM1->Height = NumeroFilas;
  BM1->Width = NumeroColumnas;
  BM1->PixelFormat = pf8bit;
  BM1->Palette = CreatePalette(&SysPal.lpal);
  nl = BM1->Height;
  numeroLineaanterior = 0;
  Binin = PBinin->Caption.ToInt();
  Repintar();

  numeroLineaanterior = 0;
  numeroLinea = 0;
  nl = numeroLinea;
  aux[0] = 30;

  nFoto++;
  if(nFoto >= 16)
    nFoto = 0;
  aux[1] = (nFoto << 4) & 0xF0;
  *(WORD*)&aux[2] = NumeroColumnas;
  *(WORD*)&aux[4] = NumeroFilas;
  if(CBT->State == cbChecked)
    *(BYTE*)&aux[6] = (char)Binin + 10;
  else
    *(BYTE*)&aux[6] = (char)Binin;
  *(WORD*)&aux[7] = (WORD)Emsg->Text.ToInt();
  *(WORD*)&aux[9] = (WORD)Esg->Text.ToInt();
  *(WORD*)&aux[11] = X1F;
  *(WORD*)&aux[13] = Y1F;
  *(WORD*)&aux[15] = X2F;
  *(WORD*)&aux[17] = Y2F;
  if(Sender == PCancel)
    *(BYTE*)&aux[19] = 1;
  else
    *(BYTE*)&aux[19] = 0;
  S1->Escribir(aux, 20, S1->IPRabbit);
  TFoto = GetTickCount();

  if(Sender == PCancel)
  {
    LeyendoFoto = false;
    PFoto->BevelOuter = bvRaised;
    PFoto->Color = clSilver;
    IFoto->Picture->Bitmap->LoadFromResourceName((int)HInstance, "FOTO");
    SLedFoto->Brush->Color = clGray;
    TBBinin->Enabled = true;
  }
  else if(Sender == PFoto)
  {
    LeyendoFoto = true;
    PFoto->BevelOuter = bvLowered;
    PFoto->Color = (TColor)0x00DEDEDE;
    IFoto->Picture->Bitmap->LoadFromResourceName((int)HInstance,"CLICK");
    SLedFoto->Brush->Color = clRed;
    TBBinin->Enabled = false;
  }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::EBininChange(TObject *Sender)
{
  Binin = PBinin->Caption.ToInt();
  NumeroColumnas = PColumnas->Caption.ToInt() / Binin;
  NumeroFilas = PFilas->Caption.ToInt() / Binin;
  X1 = X1F = 0;
  Y1 = Y1F = 0;
  X2 = X2F = NumeroColumnas;
  Y2 = Y2F = NumeroFilas;
  PB1->Width = X2 + 4;
  PB1->Height = Y2 + 4;
  PX1->Caption = X1;
  PX2->Caption = X2;
  PY1->Caption = Y1;
  PY2->Caption = Y2;
  PFil->Caption = NumeroFilas;
  PCol->Caption = NumeroColumnas;

  delete BM1;
  BM1 = new Graphics::TBitmap();
  BM1->Height = NumeroFilas;
  BM1->Width = NumeroColumnas;
  BM1->PixelFormat = pf8bit;
  BM1->Palette = CreatePalette(&SysPal.lpal);
  for (int y = 0; y < NumeroFilas; y++)
  {
    for (int x = 0; x < NumeroColumnas; x++)
    {
      Foto[y][x] = 0;
    }
  }
  BitBlt(PB1->Canvas->Handle, 0, numeroLineaanterior, BM1->Width, nl - numeroLineaanterior,
         BM1->Canvas->Handle, 0, numeroLineaanterior, SRCCOPY);
}
//---------------------------------------------------------------------------

bool rect = false, first = true;
Windows::TPoint points[5];

void __fastcall TForm1::CBRClick(TObject *Sender)
{
  if(first == false)
  {
    if(CBR->Checked == false)
    {
      points[0] = Point(X1,Y1);
      points[1] = Point(X2,Y1);
      points[2] = Point(X2,Y2);
      points[3] = Point(X1,Y2);
      points[4] = Point(X1,Y1);
      PB1->Canvas->Pen->Color = clWhite;
      PB1->Canvas->Pen->Mode = pmXor;
      PB1->Canvas->Polyline(points, 4);
      X1 = X1F = 0;
      Y1 = Y1F = 0;
      X2 = X2F = NumeroColumnas;
      Y2 = Y2F = NumeroFilas;
      PX1->Caption = X1;
      PX2->Caption = X2;
      PY1->Caption = Y1;
      PY2->Caption = Y2;
      PFil->Caption = NumeroFilas;
      PCol->Caption = NumeroColumnas;
      rect = false;
      first = true;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(TObject *Sender,
             TMouseButton Button, TShiftState Shift, int X, int Y)
{
  float auxf;
  TColor C;
  char aux[20];

  if(Shift.Contains(ssRight	))
  {
    TRect R, R2;
    for(int c1 = 0; c1 < 7; c1++)
    {
      for(int c2 = 0; c2 < 7; c2++)
      {
        int cx, cy;
        cx = X - 3 + c2;
        cy = Y - 3 + c1;
        R = DG1->CellRect(c2,c1);
        R2 = DG2->CellRect(c2,c1);

        auxf = (float)x0 + (float)Foto[cy][cx] / (float)y0;
        if(auxf >= 256)
          DG2->Canvas->Brush->Color = (TColor)0x00FFFFFF;
        else
          DG2->Canvas->Brush->Color =  (TColor)( 0x00000000 |((ULONG)auxf)&0x000000FF |
                                                             (((ULONG)auxf) << 8)&0x0000FF00 |
                                                             (((ULONG)auxf) << 16)&0x00FF0000);

        DG2->Canvas->FillRect(R2);
        if((cx == X) && (cy == Y))
          DG1->Canvas->Font->Color = clRed;
        else
          DG1->Canvas->Font->Color = clBlack;
        if(RBH->Checked == true)
          wsprintf(aux, "%04X", Foto[cy][cx]);
        else
          wsprintf(aux, "%05u", Foto[cy][cx]);
        if((cx >= 0) && (cx < BM1->Width) && (cy >= 0) && (cy < BM1->Height))
        {
          DG1->Canvas->TextRect(R, R.left + 1, R.top+1, aux);
        }
        else
        {
          DG1->Canvas->TextRect(DG1->CellRect(c2,c1),1,1, 0);
        }
      }
    }
  }
  if(CBR->Checked == true)
  {
    rect = true;
    if(first == true)
    {
      first = false;
    }
    else
    {
      points[0] = Point(X1,Y1);
      points[1] = Point(X2,Y1);
      points[2] = Point(X2,Y2);
      points[3] = Point(X1,Y2);
      points[4] = Point(X1,Y1);
      PB1->Canvas->Pen->Color = clWhite;
      PB1->Canvas->Pen->Mode = pmXor;
      PB1->Canvas->Polyline(points, 4);
    }
    X1 = X2 = X2F = X1F = X;
    Y1 = Y2 = Y2F = Y1F = Y;
    PX1->Caption = X1;
    PX2->Caption = X2;
    PY1->Caption = Y1;
    PY2->Caption = Y2;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
  float auxf;
  TColor C;
  char aux[20];

  if((X >= BM1->Width) || (Y >= BM1->Height) || (X < 0) || (Y < 0))
  {
    return;
  }
  if(Shift.Contains(ssRight	))
  {
    TRect R, R2;
    for(int c1 = 0; c1 < 7; c1++)
    {
      for(int c2 = 0; c2 < 7; c2++)
      {
        int cx, cy;
        cx = X - 3 + c2;
        cy = Y - 3 + c1;
        R = DG1->CellRect(c2,c1);
        R2 = DG2->CellRect(c2,c1);

        auxf = (float)x0 + (float)Foto[cy][cx] / (float)y0;
        if(auxf >= 256)
          DG2->Canvas->Brush->Color = (TColor)0x00FFFFFF;
        else
          DG2->Canvas->Brush->Color = (TColor)(0x00000000 | ((ULONG)auxf)&0x000000FF |
                                                            (((ULONG)auxf) << 8)&0x0000FF00 |
                                                            (((ULONG)auxf) << 16)&0x00FF0000);

        DG2->Canvas->FillRect(R2);
        if((cx == X) && (cy == Y))
          DG1->Canvas->Font->Color = clRed;
        else
          DG1->Canvas->Font->Color = clBlack;
        if(RBH->Checked == true)
          wsprintf(aux, "%04X", Foto[cy][cx]);
        else
          wsprintf(aux, "%05u", Foto[cy][cx]);
        if((cx >= 0) && (cx < BM1->Width) && (cy >= 0) && (cy < BM1->Height))
        {
          DG1->Canvas->TextRect(R, R.left + 1, R.top+1, aux);
        }
        else
        {
          DG1->Canvas->TextRect(DG1->CellRect(c2,c1),1,1, 0);
        }
      }
    }
  }
  PX->Caption = X;
  PY->Caption = Y;
  PP->Caption = Foto[Y][X];
  if(rect == true)
  {
    points[0] = Point(X1,Y1);
    points[1] = Point(X2,Y1);
    points[2] = Point(X2,Y2);
    points[3] = Point(X1,Y2);
    points[4] = Point(X1,Y1);
    PB1->Canvas->Pen->Color = clWhite;
    PB1->Canvas->Pen->Mode = pmXor;
    PB1->Canvas->Polyline(points, 4);
    X2 = X2F = X;
    Y2 = Y2F = Y;
    PX2->Caption = X2;
    PY2->Caption = Y2;
    points[0] = Point(X1,Y1);
    points[1] = Point(X2,Y1);
    points[2] = Point(X2,Y2);
    points[3] = Point(X1,Y2);
    points[4] = Point(X1,Y1);
    PB1->Canvas->Pen->Color = clWhite;
    PB1->Canvas->Pen->Mode = pmXor;
    PB1->Canvas->Polyline(points, 4);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IFotoMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  if(CBR->Checked == true)
  {
    rect = false;
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::RBK400Click(TObject *Sender)
{
  if(RBK400->Checked == true)
  {
    RBK1600->Checked == false;
    NumeroColumnas = 768;
    NumeroFilas = 512;
  }
  else
  {
    RBK1600->Checked == true;
    NumeroColumnas = 768*2;
    NumeroFilas = 512*2;
  }
  PFilas->Caption = NumeroFilas;
  PColumnas->Caption = NumeroColumnas;
  X1 = Y1 = 0;
  X1F = Y1F = 0;
  X2 = X2F = NumeroColumnas;
  Y2 = Y2F = NumeroFilas;
  PX1->Caption = X1;
  PY1->Caption = Y1;
  PX2->Caption = X2;
  PY2->Caption = Y2;
  PFil->Caption = NumeroFilas;
  PCol->Caption = NumeroColumnas;
  PB1->Width = X2 + 4;
  PB1->Height = Y2 + 4;
  delete BM1;
  BM1 = new Graphics::TBitmap();
  BM1->Height = NumeroFilas;
  BM1->Width = NumeroColumnas;
  BM1->PixelFormat = pf8bit;
  BM1->Palette = CreatePalette(&SysPal.lpal);
  TBBinin->Position = 1;
  for (int y = 0; y < NumeroFilas; y++)
  {
    for (int x = 0; x < NumeroColumnas; x++)
    {
      Foto[y][x] = 0;
    }
  }
  BitBlt(PB1->Canvas->Handle, 0, numeroLineaanterior, BM1->Width, nl - numeroLineaanterior,
         BM1->Canvas->Handle, 0, numeroLineaanterior, SRCCOPY);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RBK1600Click(TObject *Sender)
{
  if(RBK1600->Checked == true)
  {
    RBK400->Checked == false;
    NumeroColumnas = 768*2;
    NumeroFilas = 512*2;
  }
  else
  {
    RBK400->Checked == true;
    NumeroColumnas = 768;
    NumeroFilas = 512;
  }
  PFilas->Caption = NumeroFilas;
  PColumnas->Caption = NumeroColumnas;
  X1 = Y1 = 0;
  X1F = Y1F = 0;
  X2 = X2F = NumeroColumnas;
  Y2 = Y2F = NumeroFilas;
  PX2->Caption = X2;
  PY2->Caption = Y2;
  PFil->Caption = NumeroFilas;
  PCol->Caption = NumeroColumnas;
  PB1->Width = X2 + 4;
  PB1->Height = Y2 + 4;
  delete BM1;
  BM1 = new Graphics::TBitmap();
  BM1->Height = NumeroFilas;
  BM1->Width = NumeroColumnas;
  BM1->PixelFormat = pf8bit;
  BM1->Palette = CreatePalette(&SysPal.lpal);
  for (int y = 0; y < NumeroFilas; y++)
  {
    for (int x = 0; x < NumeroColumnas; x++)
    {
      Foto[y][x] = 0;
    }
  }
  BitBlt(PB1->Canvas->Handle, 0, numeroLineaanterior, BM1->Width, nl - numeroLineaanterior,
         BM1->Canvas->Handle, 0, numeroLineaanterior, SRCCOPY);
  TBBinin->Position = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EOffsetChange(TObject *Sender)
{
  try
  {
    x0 = EOffset->Text.ToInt();
  }
  catch(EConvertError &e)
  {
    EOffset->Text = "0";
    return;
  }
  if(x0 < 0)
  {
    x0 = 0;
    EOffset->Text = "0";
  }
  if(x0 > 255)
  {
    x0 = 255;
    EOffset->Text = "255";
  }
//  PB1->Repaint();
  pb1Repintar();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EStretchChange(TObject *Sender)
{
  try
  {
    y0 = EStretch->Text.ToInt();
  }
  catch(EConvertError &e)
  {
    EStretch->Text = "256";
    return;
  }
  if( y0 <= 0)
  {
    y0 = 1;
    EStretch->Text = y0;
  }
  if( y0 > 255)
  {
    y0 = 255;
    EStretch->Text = y0;
  }
  //PB1->Repaint();
  pb1Repintar();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Repintar()
{
  char *ptr;
  float auf;

  for (int y = Y1F; y < Y2F; y++)
  {
    for (int x = X1F; x < X2F; x++)
    {
      if(Foto[y][x] > maximo)
        maximo = Foto[y][x];
      if(Foto[y][x] < minimo)
        minimo = Foto[y][x];
      auf = (float)x0 + (float)Foto[y][x] / (float)y0;
      if(auf >= 255)
        ((char*)BM1->ScanLine[y])[x] = 255;
      else
        ((char*)BM1->ScanLine[y])[x] = auf;
    }
  }
  BitBlt(PB1->Canvas->Handle, 0, numeroLineaanterior, BM1->Width, nl - numeroLineaanterior,
         BM1->Canvas->Handle, 0, numeroLineaanterior, SRCCOPY);
  PMax->Caption = maximo;
  PMin->Caption = minimo;
  numeroLineaanterior = nl;
}

//------------------------------------------------------------
void __fastcall TForm1::pb1Repintar()
{
  char *ptr;
  float auf;

  for (int y = 0; y < BM1->Height; y++)
  {
    for (int x = 0; x < BM1->Width; x++)
    {
      if(Foto[y][x] > maximo)
        maximo = Foto[y][x];
      if(Foto[y][x] < minimo)
        minimo = Foto[y][x];
      auf = (float)x0 + (float)Foto[y][x] / (float)y0;
      if(auf >= 255)
        Linea[x] = 255;
      else
        Linea[x] = auf;
    }
    memmove(((char*)BM1->ScanLine[y]), Linea, BM1->Width);
  }
  BitBlt(PB1->Canvas->Handle, 0, 0, BM1->Width, BM1->Height, BM1->Canvas->Handle, 0, 0, SRCCOPY);

  if(CBR->Checked == true)
  {
    if(first == false)
    {
      points[0] = Point(X1,Y1);
      points[1] = Point(X2,Y1);
      points[2] = Point(X2,Y2);
      points[3] = Point(X1,Y2);
      points[4] = Point(X1,Y1);
      PB1->Canvas->Pen->Color = clWhite;
      PB1->Canvas->Pen->Mode = pmXor;
      PB1->Canvas->Polyline(points, 4);
    }
  }
}


void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
  char aux[300];
  char sal = Salidas;

  if(bit1->Down == true)
  {
    sal ^= 0x01;
    bit1->Down = false;
  }
  if(bit2->Down == true)
  {
    sal ^= 0x02;
    bit2->Down = false;
  }
  if(bit3->Down == true)
  {
    sal ^= 0x04;
    bit3->Down = false;
  }
  if(bit4->Down == true)
  {
    sal ^= 0x08;
    bit4->Down = false;
  }
  if(bit5->Down == true)
  {
    sal ^= 0x10;
    bit5->Down = false;
  }
  if(bit6->Down == true)
  {
    sal ^= 0x20;
    bit6->Down = false;
  }
  if(bit7->Down == true)
  {
    sal ^= 0x40;
    bit7->Down = false;
  }
  if(bit8->Down == true)
  {
    sal ^= 0x80;
    bit8->Down = false;
  }
  aux[0] = 10;
  aux[1] = 0;
  aux[2] = sal;
  S1->Escribir(aux, 8, S1->IPRabbit);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TBBininChange(TObject *Sender)
{
  PBinin->Caption = ((TTrackBar*)Sender)->Position;
  Binin = PBinin->Caption.ToInt();
  NumeroColumnas = PColumnas->Caption.ToInt() / Binin;
  NumeroFilas = PFilas->Caption.ToInt() / Binin;
  X1 = X1F = 0;
  Y1 = Y1F = 0;
  X2 = X2F = NumeroColumnas;
  Y2 = Y2F = NumeroFilas;
  PB1->Width = X2 + 4;
  PB1->Height = Y2 + 4;
  PX1->Caption = X1;
  PX2->Caption = X2;
  PY1->Caption = Y1;
  PY2->Caption = Y2;
  PFil->Caption = NumeroFilas;
  PCol->Caption = NumeroColumnas;

  delete BM1;
  BM1 = new Graphics::TBitmap();
  BM1->Height = Y2;
  BM1->Width = X2;
  BM1->PixelFormat = pf8bit;
  BM1->Palette = CreatePalette(&SysPal.lpal);
  for (int y = 0; y < NumeroFilas; y++)
  {
    for (int x = 0; x < NumeroColumnas; x++)
    {
      Foto[y][x] = 0;
    }
  }
  BitBlt(PB1->Canvas->Handle, 0, numeroLineaanterior, BM1->Width, nl - numeroLineaanterior,
         BM1->Canvas->Handle, 0, numeroLineaanterior, SRCCOPY);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::LConfigurarClick(TObject *Sender)
{
  TFConfiguracion *F;

  F = new TFConfiguracion(this);
  F->ShowModal();
  delete F;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::BAbrirClick(TObject *Sender)
{
  fitsfile *fptr = 0;       /* pointer to the FITS file, defined in fitsio.h */
  int status, nkeys, keypos, hdutype, ii, jj;
  char filename[FLEN_FILENAME];    /* input FITS file */
  char card[FLEN_CARD];   /* standard string lengths defined in fitsioc.h */

  char aux[300];
  int ejes = 0;
  long ajes[4] = {0,0,0,0};
  int tipo;

  if(fptr != 0)
  {
    status = 0;
    if ( fits_close_file(fptr, &status) )
    {
      printerror( status );
      return;
    }
  }
  if(OD1->Execute())
  {
    status = 0;
    if ( fits_open_file(&fptr, OD1->FileName.c_str(), READWRITE, &status) )
    {
       printerror(status);
       return;
    }
  }
  else
    return;
  fits_get_hdu_num(fptr, &ii); // get the current HDU number
  Memo1->Lines->Add("HDU NUMBER: " + AnsiString(ii));
    // attempt to move to next HDU, until we get an EOF error
  status = 0;
  for (; !(fits_movabs_hdu(fptr, ii, &hdutype, &status) ); ii++)
  {
    status = 0;
    if (fits_get_hdrpos(fptr, &nkeys, &keypos, &status) )// get no. of keywords
    {
      printerror( status );
      return;
    }
    wsprintf(aux, "Header listing for HDU #%d:", ii);
    Memo1->Lines->Add(aux);
    for (jj = 1; jj <= nkeys; jj++)
    {
      status = 0;
      if ( fits_read_record(fptr, jj, card, &status) )
      {
        printerror( status );
        return;
      }
      Memo1->Lines->Add(card); // print the keyword card
    }
    printf("END\n\n");  /* terminate listing with END */
  }
  if (status == END_OF_FILE)   /* status values are defined in fitsio.h */
    status = 0;              /* got the expected EOF error; reset = 0  */
  else
  {
    printerror( status );     /* got an unexpected error                */
    return;
  }
  status = 0;
  if(ffgipr(fptr,  2, &tipo, &ejes, ajes, &status))
  {
    printerror( status );
    return;
  }

  Memo1->Lines->Add("------");
  Memo1->Lines->Add("Tipo : " + AnsiString(tipo));
  Memo1->Lines->Add("EJES : " + AnsiString(ejes));
  Memo1->Lines->Add("AJES0: " + AnsiString(ajes[0]));
  Memo1->Lines->Add("AJES1: " + AnsiString(ajes[1]));

  ejex = ajes[0];
  ejey = ajes[1];
  //////////////////////////////////////////////////////

  NumeroColumnas = ejex/* / Binin*/;
  NumeroFilas = ejey /*/ Binin*/;
  X1 = X1F = 0;
  Y1 = Y1F = 0;
  X2 = X2F = NumeroColumnas;
  Y2 = Y2F = NumeroFilas;
  PB1->Width = X2 + 4;
  PB1->Height = Y2 + 4;
  PX1->Caption = X1;
  PX2->Caption = X2;
  PY1->Caption = Y1;
  PY2->Caption = Y2;
  PFil->Caption = NumeroFilas;
  PCol->Caption = NumeroColumnas;

  delete BM1;
  BM1 = new Graphics::TBitmap();
  BM1->Height = NumeroFilas;
  BM1->Width = NumeroColumnas;
  BM1->PixelFormat = pf8bit;
  BM1->Palette = CreatePalette(&SysPal.lpal);
  for (int y = 0; y < NumeroFilas; y++)
  {
    for (int x = 0; x < NumeroColumnas; x++)
    {
      Foto[y][x] = 0;
    }
  }

  long primer_elemento = 1;
  long numelem = ejex*ejey;
  int cualquiernull = 0;
  Byte *ptr;
  short sust = 0;
  unsigned short *datos;

  datos = new unsigned short [ejex*ejey];
  memset(datos, 0, ejex*ejey*2);
  status = 0;
  if(fits_read_img(fptr, TSHORT, primer_elemento, numelem,
                   &sust, //valor por el que se sustituira los indefinidos
                   &datos[primer_elemento],
                   &cualquiernull, // 1 si hay alguna sustitucion
                   &status))
  {
    printerror( status );
  }
  long n = numelem;
  for(int py = 0; py < ejey; py++)
  {
    for (int px = ejex; px > 0; px--)
    {
      Foto[py][px] = datos[n--];
    }
  }
  delete datos;
  PB1->Repaint();

}
//---------------------------------------------------------------------------
    /*****************************************************/
    /* Print out cfitsio error messages and exit program */
    /*****************************************************/
void __fastcall TForm1::printerror( int status)
{
  char status_str[FLEN_STATUS], errmsg[FLEN_ERRMSG];
  char aux[300];

  if (status)
    Memo1->Lines->Add("\n*** Error occurred during program execution ***\n");

  fits_get_errstatus(status, status_str);   // get the error description
  wsprintf(aux, "\nstatus = %d: %s\n", status, status_str);
  Memo1->Lines->Add(aux);

  if ( fits_read_errmsg(errmsg) )//get first message; null if stack is empty
  {
    Memo1->Lines->Add( "\nError message stack:\n");
    Memo1->Lines->Add( errmsg);
    while ( fits_read_errmsg(errmsg) )  // get remaining messages
      Memo1->Lines->Add( errmsg);
  }
}

void __fastcall TForm1::TBStChange(TObject *Sender)
{
  EStretch->Text = TBSt->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BGuardarClick(TObject *Sender)
{
  fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */
  int status;
  AnsiString N;

  ejex = X2;
  ejey = Y2;
  long n = X2*Y2;
  if(SD1->Execute())
  {
    status = 0;
    N = SD1->FileName + ".fit";
    if(ffinit(&fptr, N.c_str(), &status))
    {
      printerror( status );
      status = 0;
      if ( fits_open_file(&fptr, N.c_str(), READWRITE, &status) )
      {
         printerror(status);
        return;
      }
    }
  }
  else
    return;

  long axes[2];
  axes[0] = ejex;
  axes[1] = ejey;
  if(ffcrim(fptr, 16, 2, axes, &status))
  {
    printerror(status);
    return;
  }

  unsigned short *datos;

  datos = new unsigned short [ejex*ejey];
  memset(datos, 0, ejex*ejey*2);
  for(int py = 0; py < ejey; py++)
  {
    for (int px = ejex; px > 0; px--)
    {
      datos[n--] = Foto[py][px];
    }
  }

  status = 0;
  if(fits_write_img(fptr, TSHORT, 1, ejex*ejey, datos, &status))
  {
    printerror( status );
  }
  delete datos;
  return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TBOffChange(TObject *Sender)
{
  EOffset->Text = TBOff->Position;
//  PB1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PFotoMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if(Shift.Contains(ssLeft))
  {
    if(PFoto->BevelOuter == bvRaised)
    {
      BFotoClick(PFoto);
/*
      PFoto->BevelOuter = bvLowered;
      PFoto->Color = (TColor)0x00DEDEDE;
      IFoto->Picture->Bitmap->LoadFromFile("Click.bmp");
      SLedFoto->Brush->Color = clRed;
      TBBinin->Enabled = false;
*/
    }
  }
  else if(Shift.Contains(ssRight))
  {
    BFotoClick(PCancel);
/*
    PFoto->BevelOuter = bvRaised;
    PFoto->Color = clSilver;
    IFoto->Picture->Bitmap->LoadFromFile("Foto.bmp");
    SLedFoto->Brush->Color = clGray;
    TBBinin->Enabled = true;
*/
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PCancelMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  ((TPanel*)Sender)->BevelOuter = bvLowered;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PCancelMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  BFotoClick(PCancel);
  ((TPanel*)Sender)->BevelOuter = bvRaised;
}
//---------------------------------------------------------------------------

