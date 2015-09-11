//---------------------------------------------------------------------------


#pragma hdrstop

#include "Foto.h"
 #include "Principal.h"
#include <jpeg.hpp>
#include "ntofocus.h"
#include "Historia.h"
//---------------------------------------------------------------------------
extern int X1F, X2F, Y1F, Y2F;
extern int ObtuIndex;
extern double spizer;
//extern void ACOR_SetImage(pixel_t* img, int width, int height);

cFoto::cFoto(int width, int height, double x0, double y0)
{
  SysPal.lpal.palVersion = 0x300;
  SysPal.lpal.palNumEntries = 256;
  for(int c = 0; c < 256; c++)
  {
    SysPal.dummy[c].peRed = c;
    SysPal.dummy[c].peGreen = c;
    SysPal.dummy[c].peBlue = c;
    SysPal.dummy[c].peFlags = PC_NOCOLLAPSE;
  }
  Pixeles = new unsigned short [width * height];
  Linea = new unsigned char [width];

  BM = new Graphics::TBitmap();
  BM->Height = height;
  BM->Width = width;
  BM->PixelFormat = pf8bit;
  BM->Palette = CreatePalette(&SysPal.lpal);
  for (int cy = 0; cy < height; cy++)
  {
    for (int cx = 0; cx < width; cx++)
    {
      Pixeles[cy * width + cx] = 0x0000;

    }
  }
  xm0 = x0;
  ym0 = y0;

  //  Form1->Mhistory->Lines->Add(" Pinto BMP , h: " + AnsiString(height) + " w: " + AnsiString(width));
}


void cFoto::Resizear(int width, int height)
{
  delete Pixeles;
  delete BM;
  delete Linea;
  Pixeles = new unsigned short [width * height];
  Linea = new unsigned char [width];
  BM = new Graphics::TBitmap();
  BM->Height = height;
  BM->Width = width;
  BM->PixelFormat = pf8bit;
  BM->Palette = CreatePalette(&SysPal.lpal);
  for (int cy = 0; cy < height; cy++)
  {
    for (int cx = 0; cx < width; cx++)
    {
      Pixeles[cy * width + cx] = 0x0000;
    }
  }
//  Form1->Mhistory->Lines->Add(" Pinto BMP , h: " + AnsiString(height) + " w: " + AnsiString(width));
}


cFoto::~cFoto()    //destructor
{
  delete Pixeles;
  delete Linea;
  delete BM;
}

int cFoto::media()  //calcula la media y el histograma
{
  double m = 0;
  int xcf, contar;

  for(int cf = 0; cf < 0x7FFF; cf++)
  {
    histo[cf] = 0;
  }
  contar = 0;
  for (int cy = 10; cy < BM->Height - 10; cy++)
//  for (int cy = Y1F; cy < Y2F; cy++)
  {
    for (int cx = 10; cx < BM->Width - 10; cx++)
//    for (int cx = X1F; cx < X2F; cx++)
    {
    contar++;
      //m = m + Pixeles[cy * BM->Width + cx];
      //histo[Pixeles[cy * BM->Width + cx]/10]++;     //clave, histograma
      m = m + Pixeles[cy * BM->Width + cx];
      histo[Pixeles[cy * BM->Width + cx]/10]++;     //clave, histograma
    }
  }
  fondocielo = 0;
  for(int cf = 0; cf < 0x7FFF; cf++)
  {
    if(histo[cf] > fondocielo)
    {
      fondocielo = histo[cf];
      xcf = cf;
    }
  }
  fondocielo = xcf*10;  //clave , valor del fondo de cielo
   m =  m/contar;
//  m = m / ((X2F-X1F) * (Y2F-Y1F));
  m =(int)m;

 /*
  double Bi=0, Bi1=0, Bi2=0;
  for (int cy = 10; cy < BM->Height - 10; cy++)
  {
    for (int cx = 10; cx < BM->Width - 10; cx++)
    {
      Bi = Pixeles[cy * BM->Width + cx] - m;
      if (Bi < 0) Bi = 0;
      Bi1 += Bi;
      Bi2 += Bi*Bi;
    }
  }
  spizer = (int)(10*(Bi1*Bi1)/Bi2);
  spizer = spizer/10.0;
  char au[10];
  sprintf(au, "%06.1f", spizer);
  Historico->Mhistory->Lines->Add("Spizer = " +AnsiString(spizer)+", media = " + AnsiString(m));
 */
//**************
 if(Form1->CBAutoEnfoque->State == cbChecked)
 if(Form1->CBhfd->State == cbChecked)
  {
/*    height = Y2F - Y1F;
    width = X2F-X1F;
    AF_SetImage(datos, width, height);
    AF_SetSkyRegion(1, 1, width-2, height-2);
    AF_SetCentroidRegion(1, 1, width-2, height-2);
    hfd = AF_HFD(Name);    // No se puede pedir el centroide sin haber llamado a AF_HFD primero
*/  }
  else
  {
    double Bi=0, Bi1=0, Bi2=0;
    for (int cy = 10; cy < BM->Height - 10; cy++)
    {
      for (int cx = 10; cx < BM->Width - 10; cx++)
      {
        Bi = Pixeles[cy * BM->Width + cx] - m;
        if (Bi < 0) Bi = 0;
        Bi1 += Bi;
        Bi2 += Bi*Bi;
      }
    }
    spizer = (Bi1*Bi1)/Bi2;
    char au[10], ae[10];
    sprintf(au, "%07.1f", spizer);
    sprintf(ae, "%07.1f", m);
    Historico->Mhistory->Lines->Add("Spizer = " + AnsiString(au) +", Media = " + AnsiString(ae));
//    hfd = (float)spizer/100;
  }

//*************


  return (m);
}


int  cFoto::fullhalfwide() //clave funcion para calcular la fhw, el resultado sale en el Mhistory
{
  pixel_t* imagen;
  int width, height;
//  CalibrationParams intrafoco;
 // CalibrationParams extrafoco;

// ACOR_SetImage((short*)Form2->Foto->Pixeles, Form2->Foto->BM->Width, Form2->Foto->BM->Height);

/* ACOR_SetImage((short*)Pixeles, BM->Width, BM->Height);
  float hfd;
  int result = AF_HFD(&hfd);

  // No se puede pedir el centroide sin haber llamado a AF_HFD primero

  float xc,yc;
  AF_GetCentroid(&xc, &yc);
   Form1->Mhistory->Lines->Add("Centroid: X =" + AnsiString(xc) + " Y =" + AnsiString(yc));
   Form1->Mhistory->Lines->Add("hfd =" + AnsiString(hfd));
   Form1->Mhistory->Lines->Add("res AF_HFD =" + AnsiString(result));

 */

 // AF_InitCalibration();
          /* Esta es la caja cuadrada inicial para el calculo del fondo de cielo */
  /* lo tendría que seleccionar el usuario de la pantalla */
  return 5;
}


void cFoto::Pintar()
{

  float auf;
  unsigned short v;
  int yy;

  if((Pixeles == NULL) || (BM == NULL))
    return;
  minimo = 0xFFFF;
  maximo = 0;
  for (int cy = 0; cy < BM->Height; cy++)
  {
    yy = cy * BM->Width;
    for (int cx = 0; cx < BM->Width; cx++)
    {
      v = Pixeles[yy + cx];

 //----------
/*      if(v > maximo)
      {
        maximo = v;
        xmax = cx;
        ymax = cy;
      }
      if(v < minimo)
      {
        minimo = v;
        xmin = cx;
        ymin = cy;
      }
*/
//----------
      auf = xm0 + v * ym0;
      if(auf >= 255)
        Linea[cx] = 255;
      else if (auf < 0)
        Linea[cx] = 0;
      else
       Linea[cx] = auf;
    }
    memmove((char*)(BM->ScanLine[cy]), Linea, BM->Width);
  }
}


void cFoto::Pintar(int x1, int y1, int x2, int y2)
{
  float auf;
  int yy;

  for (int cy = y1; cy < y2; cy++)
  {
    yy = cy * BM->Width;
    for (int cx = x1; cx < x2; cx++)
    {
      auf = xm0 + (float)Pixeles[yy + cx] * ym0;
      if(auf >= 255)
        Linea[cx] = 255;
      else if (auf < 0)
        Linea[cx] = 0;
      else
       Linea[cx] = auf;
    }
    memmove(((char*)(BM->ScanLine[cy]) + x1), &Linea[x1], x2-x1);
  }
}

void cFoto::flipx()
{
  unsigned short v, *nfoto;

  if((Pixeles == NULL) || (BM == NULL))
    return;
  nfoto = new unsigned short [BM->Width * BM->Height];
  for (int cy = 0; cy < BM->Height; cy++)
  {
    for (int cx = 0; cx < BM->Width; cx++)
    {
      nfoto[cy * BM->Width + (BM->Width-cx)] = Pixeles[cy * BM->Width + cx];
    }
  }
  for (int cy = 0; cy < BM->Height; cy++)
  {
    for (int cx = 0; cx < BM->Width; cx++)
    {
      Pixeles[cy * BM->Width + cx] = nfoto[cy * BM->Width + cx];
    }
  }
  delete nfoto;
}


void cFoto::flipy()
{
  unsigned short v, *nfoto;

  if((Pixeles == NULL) || (BM == NULL))
    return;
  nfoto = new unsigned short [BM->Width * BM->Height];
  for (int cy = 0; cy < BM->Height; cy++)
  {
    for (int cx = 0; cx < BM->Width; cx++)
    {
      nfoto[(BM->Height - cy) * BM->Width + cx] = Pixeles[cy * BM->Width + cx];
    }
  }
  for (int cy = 0; cy < BM->Height; cy++)
  {
    for (int cx = 0; cx < BM->Width; cx++)
    {
      Pixeles[cy * BM->Width + cx] = nfoto[cy * BM->Width + cx];
    }
  }
  delete nfoto;
}


#pragma package(smart_init)
