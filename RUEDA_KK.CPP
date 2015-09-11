//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <string.h>

#include "rueda_kk.h"
#include "math.h"
#include "ConfiFiltro.h"
#include "aplic.h"

//---------------------------------------------------------------------------
#define NColores 8

TColor MisColores[NColores] = {clRed, clLime, clBlue, clYellow, clGreen, clGray, (TColor)0x00EEEEEE, (TColor)0x00AAAAAA};
static dr DRa;

CRueda::CRueda(TWinControl *mPadre, int x, int y, int tam, int NPos, char * mNombre, char Mot)
{
  FILE *in;
  int hnd;
  int auxi;

  estado = 0;
  posicion = 0;
  strcpy(aux, "         ");
  n = 0;


  EnviadaEjecucion = false;
  VentanaShuter = 0;
//  Motor = Mot;
  if((Mot) == 'Y')
    Motor = 'Z';
else if ((Mot) == 'Z')
    Motor = 'Y';
  Pasos = Marca = 0;
  Orden.accion = ' ';
  S1 = NULL;
  if ((in = fopen(mNombre, "rb")) != NULL)
  {
    fread(&DRa, sizeof(DRa), 1, in);
    if (DRa.n < 2)
      DRa.n = 2;
    if (DRa.n > 8)
      DRa.n = 8;
    NumColores = DRa.n;
    NumPos = DRa.n;
    fclose(in);
  }
  else
  {
    if (NPos < 2)
      NPos = 2;
    if (NPos > 8)
      NPos = 8;
    NumColores = NPos;
    NumPos = NPos;
    DRa.n = NumPos;
    for(int cc = 0; cc < NumPos; cc++)
    {
      DRa.circulos[cc].color = MisColores[cc];
      strcpy(DRa.circulos[cc].texto, "  ");
    }
  }
  strncpy(Nombre, mNombre, 79);
  Nombre[79] = 0;
  Padre = mPadre;
  X = x;
  Y = y;
  Tam = tam * 0.75;
  TamPan = tam;
  P(DRa);
}


void __fastcall CRueda::crear(dr DR1)
{
  int hnd;
  int auxi;

  PRueda->WindowProc = WProc;
  delete b;
  delete Panls;
  delete PColores;
  delete PRueda;
  delete PContenedor;

  if (DR1.n < 2)
    DR1.n = 2;
  if (DR1.n > 8)
    DR1.n = 8;
  NumColores = DR1.n;
  NumPos = DR1.n;

  Tam += 4;

  P(DR1);
  enviarReset();
}

void __fastcall CRueda::P(dr DR1)
{
  Colores = new TColor[NumPos];
  for(int cc = 0; cc < NumPos; cc++)
  {
    Colores[cc] = DR1.circulos[cc].color;
  }
  Pos = 0;
  RadG = Tam - 10.0;
  Rad = (RadG * 0.9 / 2.0) / (4/2);
  rcc = ((RadG - Rad)/2.0)*0.9;
  grados = 0.0;
  paso = 10.0;
  ColorRueda = clBlack;
  ColorCaja = clSilver;
  b = new Graphics::TBitmap;
  b->Width = Tam;
  b->Height = Tam;
  b->PixelFormat = pf32bit;
  TamPan -= 2;
  PContenedor = new TPanel(Padre);
  PContenedor->Parent = Padre;
  PContenedor->Color = clSilver;
  PContenedor->Width = TamPan;
  PContenedor->Height = TamPan*0.75+10+15+2;
  PContenedor->Left = X-1;
  PContenedor->Top = Y-1;
  PContenedor->BevelInner = bvNone;
  PContenedor->BevelOuter = bvLowered;
  PContenedor->BevelWidth = 1;

  PB = new TPanel(Padre);
  PB->Parent = Padre;
  PB->Color = clSilver;
  PB->Width = TamPan-2;
  PB->Height = 20;
  PB->Left = X-1;
  PB->Top = PContenedor->Top + PContenedor->Height ;
  PB->BevelInner = bvNone;
  PB->BevelOuter = bvLowered;
  PB->BevelWidth = 1;

  PI = new TPanel(PB);
  PI->Parent = PB;
  PI->Color = clSilver;
  PI->Width = 35;
  PI->Height = PB->Height-2;
  PI->Left = 2;
  PI->Top = 1;
  PI->Caption = "<<>>";
  PI->BevelInner = bvNone;
  PI->BevelOuter = bvRaised;
  PI->BevelWidth = 2;
  PI->OnMouseDown = PAMouseDown;

  PR = new TPanel(PB);
  PR->Parent = PB;
  PR->Color = clSilver;
  PR->Width = 35;
  PR->Height = PB->Height-2;
  PR->Left = PB->Width-PR->Width-2;
  PR->Top = 1;
  PR->Font->Name = "Arial";
  PR->Font->Size = 6;
  PR->Font->Height = -9;
  PR->Caption = "Reset";
  PR->BevelInner = bvNone;
  PR->BevelOuter = bvRaised;
  PR->BevelWidth = 2;
  PR->OnMouseDown = PAMouseDown;

  LCabecera = new TStaticText(PContenedor);
  LCabecera->Parent = PContenedor;
  LCabecera->BorderStyle = sbsSunken;
  LCabecera->Height = 16;
  LCabecera->Align = alTop;
  LCabecera->Alignment = taCenter;
  LCabecera->AutoSize = false;
  LCabecera->Color = clSilver;
  LCabecera->Font->Name = "Arial";
  LCabecera->Font->Height = -9;
  LCabecera->Font->Size = 7;
  LCabecera->Font->Color = clBlack;
  LCabecera->Caption = Nombre;

  PRueda = new TPanel(PContenedor);
  PRueda->Parent = PContenedor;
  PRueda->Width = TamPan*0.75;
  PRueda->Height = TamPan*0.75+10;
  PRueda->Left = 1;
  PRueda->Top = 1 + LCabecera->Height;
  PRueda->Color = clSilver;
  PRueda->BevelInner = bvNone;
  PRueda->BevelOuter = bvRaised;
  PRueda->BevelWidth = 1;
  PRueda->OnMouseDown = PanlMouseDown;
  PRueda->ShowHint = true;
  PRueda->Hint = "";

  PColores = new TPanel(PContenedor);
  PColores->Parent = PContenedor;
  PColores->Width = TamPan* 0.25 - 1;
  PColores->Height = TamPan*0.75 + 10;
  PColores->Left = TamPan * 0.75 + 1;
  PColores->Top =  1 + LCabecera->Height;
  PColores->BevelInner = bvNone;
  PColores->BevelOuter = bvNone;
  PColores->BevelWidth = 1;
  Tam -= 4;
  b->Width = Tam-2;
  b->Height = Tam-2;


  Hnd = PRueda->Handle;
  PRueda->Update();
  WProc = PRueda->WindowProc;
  PRueda->WindowProc = FF;
  Left = X;
  Top = Y;
  Width = PColores->Width + PRueda->Width + 2;
  Height = PColores->Height + LCabecera->Height + PB->Height + 2;

  Panls = new TPanel* [NumPos];
  for(int c = 0; c < NumPos; c++)
  {
    Panls[c] = new TPanel(PColores);
    Panls[c]->Parent = PColores;
    Panls[c]->BevelInner = bvNone;
    Panls[c]->BevelOuter = bvRaised;
    Panls[c]->BevelWidth = 1;
    Panls[c]->AutoSize = false;
    Panls[c]->Left = 2;
    Panls[c]->Width = PColores->Width - 4;
    Panls[c]->Height = (PColores->Height-0) / NumPos ;
    Panls[c]->Top = 1 + c * (Panls[c]->Height+0);
    Panls[c]->Color = Colores[c];
    Panls[c]->Tag = c + 1;
    Panls[c]->OnMouseDown = ShapeMouseDown;
    Panls[c]->Font->Name = "Arial";
    Panls[c]->Font->Height = -9;
    Panls[c]->Font->Size = 6;
    Panls[c]->Font->Color = (TColor)0x00080808;
    Panls[c]->Caption = DR1.circulos[c].texto;
  }
  Pos = 1;
}



void __fastcall CRueda::AsignarColor(int pos, TColor color)
{
  Colores[pos] = color;
  Panls[pos]->Color = Colores[pos];
}

void __fastcall CRueda::GuardarConf()
{
  FILE *in;

  DRa.n = NumPos;
  for(int cc = 0; cc < NumPos; cc++)
  {
    DRa.circulos[cc].color = Colores[cc];
    strcpy(DRa.circulos[cc].texto, Panls[cc]->Caption.c_str());
  }
  if ((in = fopen(Nombre, "wb+")) != NULL)
  {
    fwrite(&DRa, sizeof(DRa), 1, in);
  }
}

void __fastcall CRueda::PAMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (Sender == PI)
  {
    if(Button == mbLeft)
    {
      enviarPrincipio();
      ((TPanel*)Sender)->BevelOuter = bvLowered;
      ((TPanel*)Sender)->Font->Size = 6;
      ((TPanel*)Sender)->Font->Height = -10;
    }
    else if(Button == mbRight)
    {
      PI->Font->Size = 7;
      PI->Font->Height = -11;
      PI->BevelOuter = bvRaised;
    }
  }
  else if (Sender == PR)
  {
    if(Button == mbLeft)
    {
      enviarReset();
      ((TPanel*)Sender)->BevelOuter = bvLowered;
      ((TPanel*)Sender)->Font->Size = 6;
      ((TPanel*)Sender)->Font->Height = -10;
    }
    else if(Button == mbRight)
    {
      PR->Font->Size = 7;
      PR->Font->Height = -11;
      PR->BevelOuter = bvRaised;
    }
  }
}

void __fastcall CRueda::ShapeMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  TFConfiguracion *F;
  int p = ((TPanel*)Sender)->Tag-1;

  if(Button == mbLeft)
  {
    if(toupper(Motor) == 'Y')
      enviarAvanzarRueda(p);
    else if(toupper(Motor) == 'Z')
    {
      if((p == 1) || (p == 3) || (p == 5))
      {
        p--;
        VentanaShuter = p/2;
        enviarAvanzarRueda(p);
      }
    }
  }
  else if(Button == mbRight)
  {
    F = new TFConfiguracion(NULL);
    F->R = this;
    if(F->ShowModal() == mrOk	)
    {
      crear(F->DR);
      Pintar();
      enviarReset();
    }
    delete F;
  }
}

void __fastcall CRueda::PanlMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  TFConfiguracion *F;

  if(Button == mbLeft)
  {
    //enviarAvanzarPaso();
  }
  else if(Button == mbRight)
  {
    F = new TFConfiguracion(NULL);
    F->R = this;
    if(F->ShowModal() == mrOk	)
    {
      crear(F->DR);
      Pintar();
      enviarReset();
    }
    delete F;
  }
}


void __fastcall CRueda::FF(Messages::TMessage &Message)
{
  //if(Message.Msg == WM_PAINT)
    Pintar();
  WProc(Message);
}

CRueda::~CRueda()
{
  PRueda->WindowProc = WProc;
  if(strcmp(Nombre, ""))
  {
    GuardarConf();
  }
  delete b;
  delete Panls;
  delete PColores;
  delete PRueda;
  delete PContenedor;
}

void __fastcall CRueda::Circulo(double rc , double ac, double r, TColor color)
{
  double xc = (double(b->Width) / 2.0) + rc * sin(ac * 2.0 * M_PI / 360.0 );
  double yc = (double(b->Width) / 2.0) + rc * cos(ac * 2.0 * M_PI / 360.0 );

  b->Canvas->Pen->Mode = pmCopy;
  b->Canvas->Brush->Color = color;
  b->Canvas->Brush->Style = bsSolid;
  b->Canvas->Ellipse(xc - r / 2.0, yc - r / 2.0, xc + r / 2.0, yc + r / 2.0);
}

void __fastcall CRueda::Circunferencia(double rc , double ac, double r, TColor color)
{
  double xc = (double(b->Width) / 2.0) + rc * sin(ac * 2.0 * M_PI / 360.0 );
  double yc = (double(b->Width) / 2.0) + rc * cos(ac * 2.0 * M_PI / 360.0 );

  b->Canvas->Pen->Mode = pmCopy;
  b->Canvas->Pen->Color = color;
  b->Canvas->Brush->Color = color;
  b->Canvas->Brush->Style = bsClear;
  b->Canvas->Pen->Width = 2;
  b->Canvas->Ellipse(xc - r / 2.0, yc - r / 2.0, xc + r / 2.0, yc + r / 2.0);
}

void __fastcall CRueda::Pintar()
{
  HDC hdc;
  double inc = 360.0 / double(NumPos);
  int p;

  b->Canvas->Pen->Color = clBlack;
  b->Canvas->Pen->Mode = pmCopy;
  b->Canvas->Pen->Width = 1;
  b->Canvas->Brush->Color = ColorCaja;
  b->Canvas->Brush->Style = bsSolid;
  b->Canvas->FillRect(Rect(0,0,b->Width,b->Height));

  Circulo(0, 0, RadG, ColorRueda);
  p = Pos;
    p--;
    if(p < 0)
      p = NumColores-1;

  for(double cc = 0.0; cc < NumPos; cc++)
  {
    b->Canvas->Pen->Color = clBlack;
    Circulo(rcc, grados+inc*cc, Rad, Colores[p]);
    b->Canvas->Font->Name = "Arial";
    b->Canvas->Font->Height = -8;
    b->Canvas->Font->Size = 5;

    b->Canvas->TextOut((double(b->Width) / 2.0) + rcc * sin((grados+inc*cc) * 2.0 * M_PI / 360.0 )- Panls[p]->Caption.Length()-3,
                       (double(b->Width) / 2.0) + rcc * cos((grados+inc*cc) * 2.0 * M_PI / 360.0 ) - 5,
                       Panls[p]->Caption);
    p--;
    if(p < 0)
      p = NumColores-1;
  }
  Circunferencia(rcc - 1, 0, Rad*1.4, clSilver);
  hdc = GetDC(PRueda->Handle);
  BitBlt( hdc, 2, 5, Tam, Tam, b->Canvas->Handle, 0, 0, SRCCOPY );
  ReleaseDC(PRueda->Handle, hdc);
}

void __fastcall CRueda::AvanzarPaso()
{
  double inc = 360.0 / double(NumPos);

  Pos++;
  if(Pos >= NumPos)
    Pos = 0;
  grados = 0.0;
  for(double k = 0.0; k < paso; k++)
  {
    grados = grados + inc / paso;
    Pintar();
  }
}


void __fastcall CRueda::AvanzarRueda(int n)
{
  if(n >= NumPos)
    return;
  while(Pos != n)
  {
    AvanzarPaso();
  }
  if(toupper(Motor) == 'Y')
  {
    for(int kk = 0; kk < NumPos; kk++)
    {
      Panls[kk]->BevelInner = bvNone;
      Panls[kk]->BevelOuter = bvRaised;
      Panls[kk]->BevelWidth = 1;
    }
    Panls[Pos]->BevelInner = bvNone;
    Panls[Pos]->BevelOuter = bvLowered;
    Panls[Pos]->BevelWidth = 2;
  }
  else if(toupper(Motor) == 'Z')
  {
    for(int kk = 0; kk < NumPos; kk++)
    {
      Panls[kk]->BevelInner = bvNone;
      Panls[kk]->BevelOuter = bvRaised;
      Panls[kk]->BevelWidth = 1;
    }
    if((Pos == 0) || (Pos == 2) || (Pos == 4))
    {
      if((Pos+1) >= NumPos)
      {
        Panls[0]->BevelInner = bvNone;
        Panls[0]->BevelOuter = bvLowered;
        Panls[0]->BevelWidth = 2;
      }
      else
      {
        Panls[Pos+1]->BevelInner = bvNone;
        Panls[Pos+1]->BevelOuter = bvLowered;
        Panls[Pos+1]->BevelWidth = 2;
      }
    }
    else
    {
      Panls[Pos]->BevelInner = bvNone;
      Panls[Pos]->BevelOuter = bvLowered;
      Panls[Pos]->BevelWidth = 2;
    }
  }

}

void __fastcall CRueda::enviarReset()
{
  char aux[300];

  aux[0] = 3;
  aux[1] = 0;
  aux[2] = '<';
  aux[3] = Motor;
  aux[4] = 'r';
  aux[5] = '>';
  aux[6] = 0;
  if(S1 != NULL)
  {
    Orden.accion = 'r';
    S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);
    EnviadaEjecucion = true;
  }
}

void __fastcall CRueda::enviarAvanzarRueda(int n)
{
  char aux[300];
  int pasos, periodo_z, periodo_y;
periodo_z = 12;
periodo_y = 12;

  if(toupper(Motor) == 'Y')
  {
    if(n >= Pos)
    {
      pasos = ((Pasos + Marca) / NumPos) * (n - Pos);
    }
    else
    {
      pasos = ((Pasos + Marca) / NumPos) * (NumPos - n);
    }

    aux[0] = 3;
    aux[1] = 0;
    aux[2] = '<';
    aux[3] = Motor;

    ProximaPos = n;

    wsprintf(&aux[4], "%05u+%02u>", pasos, periodo_z);
    if(S1 != NULL)
    {
      Configuracion.motor = Motor;
      strncpy(Configuracion.pasos, &aux[4], 5);
      Configuracion.sentido = '+';
      strncpy(Configuracion.periodo, "05", 2);
      S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);
      EnviadaEjecucion = false;
    }
  }
  else if(toupper(Motor) == 'Z')
  {
    if(n >= Pos)
    {
      pasos = ((Pasos + Marca) / NumPos) * (n - Pos);
    }
    else
    {
      pasos = ((Pasos + Marca) / NumPos) * (NumPos - n);
    }

    aux[0] = 3;
    aux[1] = 0;
    aux[2] = '<';
    aux[3] = Motor;

    ProximaPos = n;
//    wsprintf(&aux[4], "%05u+%02u>", pasos, VentanaShuter);
    wsprintf(&aux[4], "%05u+%02u>", pasos, periodo_y);
    if(S1 != NULL)
    {
      Configuracion.motor = Motor;
      strncpy(Configuracion.pasos, &aux[4], 5);
      Configuracion.sentido = 's';
      strncpy(Configuracion.periodo, &aux[10], 2);
      S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);
      EnviadaEjecucion = false;
    }
  }

}

void __fastcall CRueda::enviarPrincipio()
{
  char aux[300];

  aux[0] = 3;
  aux[1] = 0;
  aux[2] = '<';
  aux[3] = Motor;
  aux[4] = 'i';
  aux[5] = '>';
  aux[6] = 0;
  if(S1 != NULL)
  {
    Orden.accion = 'i';
    S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);
    EnviadaEjecucion = true;
  }
}

void __fastcall CRueda::enviarIniciarMovimiento()
{
  char aux[300];

  aux[0] = 3;
  aux[1] = 0;
  aux[2] = '<';
  aux[3] = Motor;
  aux[4] = 'o';
  aux[5] = '>';
  aux[6] = 0;
  if(S1 != NULL)
  {
    Orden.accion = 'o';
    S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);
    EnviadaEjecucion = true;
  }
}

void __fastcall CRueda::Analizar(char c)
{

  if(estado == 0)
  {
    if(c == '<')
    {
      estado = 1;
    }
  }
  else if(estado == 1)
  {
    if(c == toupper(Motor))    //RESPUESTA
    {
      estado = 2;
    }
    else if(c == tolower(Motor))  //ECO
    {
      estado = 5;
    }
    else
      estado = 0;
  }
  else if(estado == 2)   //RESPUESTA
  {
    if(toupper(Motor) == 'Z')
    {
      if((c >= '0') && (c <= '9'))
      {
        aux[n++] = c;
        if(EnviadaEjecucion == true) // se ha enviado una orden
        {
          if(Orden.accion == 'r')
          {
            if(n == 6)
            {
              aux[5] = 0;
              Pasos = atoi(aux);
            }
            else if(n == 10)
            {
              aux[n] = 0;
              Marca = atoi(&aux[6]);
              LCabecera->Caption = AnsiString(Nombre) + " " + AnsiString(Pasos + Marca) + " " + AnsiString((Pasos + Marca)/NumPos);
              n = 0;
            }
          }
        }
      }
      else if(c == ' ')
      {
      }
      else if(c == '>')
      {
        if(EnviadaEjecucion == true)
        {
          if(Orden.accion == '+')  // Avanzar paso
          {
            aux[n] = 0;
            posicion = atoi(aux);
            AvanzarRueda(posicion);
          }
          else if(Orden.accion == 'r') // Reset
          {
            posicion = 0;
            AvanzarRueda(posicion);
            PR->Font->Size = 7;
            PR->Font->Height = -11;
            PR->BevelOuter = bvRaised;
          }
          else if(Orden.accion == 'i') // Ir al principio
          {
            posicion = 0;
            AvanzarRueda(posicion);
            PI->Font->Size = 7;
            PI->Font->Height = -11;
            PI->BevelOuter = bvRaised;
          }
          else if(Orden.accion == 'o') // Ir al principio
          {
            AvanzarRueda(ProximaPos);
            PI->Font->Size = 7;
            PI->Font->Height = -11;
            PI->BevelOuter = bvRaised;
          }
        }
        n = 0;
        estado = 0;
      }
    }
    else if(toupper(Motor) == 'Z')
    {
      if((c >= '0') && (c <= ';'))
      {
        aux[n++] = c;
        if(EnviadaEjecucion == true) // se ha enviado una orden
        {
          if(Orden.accion == 'r')
          {
            if(n == 6)
            {
              aux[5] = 0;
              Pasos = atoi(aux);
            }
            else if(n == 10)
            {
              aux[n] = 0;
              Marca = atoi(&aux[6]);
              LCabecera->Caption = AnsiString(Nombre) + " " + AnsiString(Pasos + Marca) + " " + AnsiString((Pasos + Marca)/NumPos);
              n = 0;
            }
          }
        }
      }
      else if(c == ' ')
      {
      }
      else if(c == '>')
      {
        if(EnviadaEjecucion == true)
        {
          EnviadaEjecucion = false;
          if(Orden.accion == '+')  // Avanzar paso
          {
            aux[n] = 0;
            posicion = atoi(aux);
            AvanzarRueda(posicion);
          }
          else if(Orden.accion == 'r') // Reset
          {
            posicion = 0;
            AvanzarRueda(posicion);
            PR->Font->Size = 7;
            PR->Font->Height = -11;
            PR->BevelOuter = bvRaised;
          }
          else if(Orden.accion == 'i') // Ir al principio
          {
            posicion = 0;
            AvanzarRueda(posicion);
            PI->Font->Size = 7;
            PI->Font->Height = -11;
            PI->BevelOuter = bvRaised;
          }
          else if(Orden.accion == 'o') // Ir al principio
          {
            AvanzarRueda(ProximaPos);
          }
        }
        else    // '>'
        {
          aux[n] = 0;
          if (n == 1)
          {
            if((aux[0] >= '0') && (aux[0] <= '9'))
            {
              posicion = atoi(aux);
            }
          }
          if((posicion == 3) || (posicion == 9))
          {
            if(VentanaShuter == 0)
              AvanzarRueda(1);
            else if(VentanaShuter == 1)
              AvanzarRueda(3);
            else if(VentanaShuter == 2)
              AvanzarRueda(5);
          }
          else if(posicion == 0)
          {
            if(VentanaShuter == 0)
              AvanzarRueda(0);
            else if(VentanaShuter == 1)
              AvanzarRueda(2);
            else if(VentanaShuter == 2)
              AvanzarRueda(4);
          }
          else if(posicion == 6)
          {
            if(VentanaShuter == 0)
              AvanzarRueda(0);
            else if(VentanaShuter == 1)
              AvanzarRueda(2);
            else if(VentanaShuter == 2)
              AvanzarRueda(4);
          }
        }
        n = 0;
        estado = 0;
      }
    }
  }
  else if (estado == 5)  // ECO
  {
    if(toupper(Motor) == 'Y')
    {
      if(c == '>')
      {
        if(EnviadaEjecucion == false)  // enviada configuracion
        {
          enviarIniciarMovimiento();
        }
        estado = 0;
      }
    }
    else if(toupper(Motor) == 'Z')
    {
      if(c == '>')
      {
        if(EnviadaEjecucion == false)  // enviada configuracion
        {
            AvanzarRueda(ProximaPos);
          //enviarIniciarMovimiento();
        }
        estado = 0;
      }
    }
  }
}


#pragma package(smart_init)
