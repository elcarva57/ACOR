//---------------------------------------------------------------------------

#ifndef FotoH
#define FotoH
#include <vcl.h>
//---------------------------------------------------------------------------
typedef struct {
  TLogPalette lpal;
  TPaletteEntry dummy[256];
} LogPal;

class cFoto
{
  unsigned char *Linea;
  public :
    unsigned short *Pixeles;        // clave puntero a la imagen de 16 bits
    unsigned long histo[0x7FFF];
    unsigned long fondocielo;
    double xm0, ym0;
    WORD maximo, minimo;
    int xmax, ymax, xmin, ymin;
    Graphics::TBitmap *BM;          // clave bitmap con tamaño de la imagen
    LogPal SysPal;
  public :
    cFoto(int width, int height, double x0, double y0);
    ~cFoto();
    void Pintar();
    void Pintar(int x1, int y1, int x2, int y2);
    void Resizear(int width, int height);
    void flipx();
    void flipy();
    int media();
    int fullhalfwide();
};
#endif
 