//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
 
#include "Unit3.h"
#include <jpeg.hpp>                 
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFGraficas *FGraficas;



typedef struct {
  int kpluvio;
  int alerta_nube;
  int bar_ofset;
  int bar_altura;
  int RefZener[6];
//  int MinFichero;
  int luzIR_ofset;
  int luzUV_ofset;
  int kmecanico;
  int k1termico;
  int k2termico;
  char direc_datos[100];
  char direc_jpg[100];
}CONF_METEO;

extern CONF_METEO confEMA;


//---------------------------------------------------------------------------
__fastcall TFGraficas::TFGraficas(TComponent* Owner)
  : TForm(Owner)
{
}


//---------------------------------------------------------------------------
void __fastcall TFGraficas::Button1Click(TObject *Sender)
{
char aux[100];

  TJPEGImage *jp;
  Graphics::TBitmap *Bitmap1 = new Graphics::TBitmap();
/*
  strcpy(aux, confEMA.direc_jpg);
  strcat(aux, "Anemometro.bmp");
  FGraficas->Chart1->SaveToBitmapFile(aux);

  strcpy(aux, confEMA.direc_jpg);
  strcat(aux, "temperatura.bmp");
  FGraficas->Chart1->SaveToBitmapFile(aux);

  strcpy(aux, confEMA.direc_jpg);
  strcat(aux, "pluviometria.bmp");
  FGraficas->Chart1->SaveToBitmapFile(aux);

  strcpy(aux, confEMA.direc_jpg);
  strcat(aux, "lluvia_nubes.bmp");
  FGraficas->Chart1->SaveToBitmapFile(aux);

  strcpy(aux, confEMA.direc_jpg);
  strcat(aux, "barometro.bmp");
  FGraficas->Chart1->SaveToBitmapFile(aux);
*/
  Chart1->SaveToBitmapFile("Anemometro.bmp");
  Chart2->SaveToBitmapFile("temperatura.bmp");
  Chart3->SaveToBitmapFile("pluviometria.bmp");
  Chart4->SaveToBitmapFile("lluvia_nubes.bmp");
  Chart5->SaveToBitmapFile("barometro.bmp");

  try
  {
    jp = new TJPEGImage();
  }
  catch(...)
  {
    return;
  }

  try
  {
 //     FGraficas->Visible = true;
 //     FGraficas->Update();
/*
      Bitmap1 = new Graphics::TBitmap();
      Bitmap1->Width = FGraficas->ClientWidth;
      Bitmap1->Height = FGraficas->ClientHeight;
      Bitmap1->Canvas->CopyRect(TRect(0,0, FGraficas->ClientWidth, FGraficas->ClientHeight), FGraficas->Canvas,TRect(0,0, FGraficas->ClientWidth, FGraficas->ClientHeight));
      jp->Assign(Bitmap1);
      jp->SaveToFile("Form.jpg");
      delete Bitmap1;
*/
    Bitmap1 = new Graphics::TBitmap();
    Bitmap1->LoadFromFile("Anemometro.bmp");
    jp->Assign(Bitmap1);
    jp->SaveToFile("Anemometro.jpg");
    delete Bitmap1;

    Bitmap1 = new Graphics::TBitmap();
    Bitmap1->LoadFromFile("temperatura.bmp");
    jp->Assign(Bitmap1);
    jp->SaveToFile("temperatura.jpg");
    delete Bitmap1;

    Bitmap1 = new Graphics::TBitmap();
    Bitmap1->LoadFromFile("pluviometria.bmp");
    jp->Assign(Bitmap1);
    jp->SaveToFile("pluviometria.jpg");
    delete Bitmap1;

    Bitmap1 = new Graphics::TBitmap();
    Bitmap1->LoadFromFile("lluvia_nubes.bmp");
    jp->Assign(Bitmap1);
    jp->SaveToFile("lluvia_nubes.jpg");
    delete Bitmap1;

    Bitmap1 = new Graphics::TBitmap();
    Bitmap1->LoadFromFile("barometro.bmp");
    jp->Assign(Bitmap1);
    jp->SaveToFile("barometro.jpg");
    delete Bitmap1;
  }
  __finally
  {
    delete jp;
  }

}
//---------------------------------------------------------------------------

