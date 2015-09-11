//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "ConfiFiltro.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TFConfiguracion *FConfiguracion;


__fastcall TFConfiguracion::TFConfiguracion(TComponent* Owner) : TForm(Owner)
{
  pSh[0] = Shape1;
  pSh[1] = Shape2;
  pSh[2] = Shape3;
  pSh[3] = Shape4;
  pSh[4] = Shape5;
  pSh[5] = Shape6;
  pSh[6] = Shape7;
  pSh[7] = Shape8;
  pEd[0] = Edit2;
  pEd[1] = Edit3;
  pEd[2] = Edit4;
  pEd[3] = Edit5;
  pEd[4] = Edit6;
  pEd[5] = Edit7;
  pEd[6] = Edit8;
  pEd[7] = Edit9;
  pP[0] = P1;
  pP[1] = P2;
  pP[2] = P3;
  pP[3] = P4;
  pP[4] = P5;
  pP[5] = P6;
  pP[6] = P7;
  pP[7] = P8;
}
//---------------------------------------------------------------------------
void __fastcall TFConfiguracion::Shape1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  TColorDialog* dlg;

  dlg = new TColorDialog(this);
  if(dlg->Execute())
  {
    ((TShape*)Sender)->Brush->Color = dlg->Color;
  }
  delete dlg;
}
//---------------------------------------------------------------------------


void __fastcall TFConfiguracion::Vis(int n)
{
  if((n < 1) || (n > 8))
  {
    TV->Caption = 8;
    TBV->Position = n;
  }
  if((n >= 1) && (n <= 8))
  {
    TV->Caption = n;
    TBV->Position = n;
    for(int c = 0; c < 8; c++)
    {
      if(n >= c+1)
        pP[c]->Visible = true;
      else
      pP[c]->Visible = false;
    }
  }
}


void __fastcall TFConfiguracion::TBVChange(TObject *Sender)
{
  int n = TBV->Position;

  Vis(n);
}
//---------------------------------------------------------------------------

void __fastcall TFConfiguracion::FormShow(TObject *Sender)
{
  int n = R->NumPos;

  if((n < 1) || (n > 8))
  {
    TV->Caption = 8;
    TBV->Position = n;
  }
  if((n >= 1) && (n <= 8))
  {
    TV->Caption = n;
    TBV->Position = n;
    pSh[0]->Brush->Color = R->Colores[0];
    pEd[0]->Text = R->Panls[0]->Caption;

    for(int c = 1; c < 8; c++)
    {
      if(n >= c + 1)
      {
        pP[c]->Visible = true;
        pSh[c]->Brush->Color = R->Colores[c];
        pEd[c]->Text = R->Panls[c]->Caption;
      }
      else
      {
        pP[c]->Visible = false;
      }
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TFConfiguracion::BGuardarClick(TObject *Sender)
{
  FILE *out;

  DR.n = TBV->Position;

  for(int c = 0; c < DR.n; c++)
  {
    DR.circulos[c].color = pSh[c]->Brush->Color;
    strncpy(DR.circulos[c].texto, pEd[c]->Text.c_str(), 2);
    DR.circulos[c].texto[2] = 0;
  }
//  SD1->DefaultExt = "cfr";
  SD1->FileName = "filtro1.cfr";
  if(SD1->Execute())
  {
    if ((out = fopen(SD1->FileName.c_str(), "wb+")) != NULL)
    {
      fwrite(&DR, sizeof(DR), 1, out);
      fwrite(&R->Marca, sizeof(R->Marca), 1, out);
      fwrite(&R->Pasos, sizeof(R->Pasos), 1, out);
      fclose(out);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFConfiguracion::BCargarClick(TObject *Sender)
{
  FILE *in;
  int n;

  OD1->DefaultExt = "cfr";
  OD1->FileName = "*.cfr";
  if(OD1->Execute())
  {
    if ((in = fopen(OD1->FileName.c_str(), "rb")) != NULL)
    {
      fread(&DR, sizeof(DR), 1, in);
      fread(&R->Marca, sizeof(R->Marca), 1, in);
      fread(&R->Pasos, sizeof(R->Pasos), 1, in);
      fclose(in);
      n = DR.n;

      if((n < 1) || (n > 8))
      {
        TV->Caption = 8;
        TBV->Position = n;
      }
      if((n >= 1) && (n <= 8))
      {
        TV->Caption = n;
        TBV->Position = n;
        pSh[0]->Brush->Color = DR.circulos[0].color;
        pEd[0]->Text = DR.circulos[0].texto;

        for(int c = 1; c < 8; c++)
        {
          if(n >= c + 1)
          {
            pP[c]->Visible = true;
            pSh[c]->Brush->Color = DR.circulos[c].color;
            pEd[c]->Text = DR.circulos[c].texto;
          }
          else
          {
            pP[c]->Visible = false;
          }
        }
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFConfiguracion::BitBtn1Click(TObject *Sender)
{
  DR.n = TBV->Position;
  for(int cc = 0; cc < DR.n; cc++)
  {
    DR.circulos[cc].color = pSh[cc]->Brush->Color;
    strcpy(DR.circulos[cc].texto, pEd[cc]->Text.c_str());
  }

  FILE *out;

  DR.n = TBV->Position;

  for(int c = 0; c < DR.n; c++)
  {
    DR.circulos[c].color = pSh[c]->Brush->Color;
    strncpy(DR.circulos[c].texto, pEd[c]->Text.c_str(), 2);
    DR.circulos[c].texto[2] = 0;
  }
//  SD1->DefaultExt = "cfr";
  SD1->FileName = "filtro1.cfr";
  if(SD1->Execute())
  {
    if ((out = fopen(SD1->FileName.c_str(), "wb+")) != NULL)
    {
      fwrite(&DR, sizeof(DR), 1, out);
      fwrite(&R->Marca, sizeof(R->Marca), 1, out);
      fwrite(&R->Pasos, sizeof(R->Pasos), 1, out);
      fclose(out);
    }
  }  

}
//---------------------------------------------------------------------------

void __fastcall TFConfiguracion::RSTClick(TObject *Sender)
{
  R->enviarReset();
}
//---------------------------------------------------------------------------


