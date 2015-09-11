//---------------------------------------------------------------------------
#ifndef rueda_kkH
#define rueda_kkH
#include "socket.h"

//---------------------------------------------------------------------------
typedef struct
{
  TColor color;
  char texto[3];
}cc;

typedef struct
{
  int n;
  cc circulos[8];
}dr;

typedef struct
{
  char motor;
  char pasos[5];
  char sentido;
  char periodo[2];
}sConfiguracion;

typedef struct
{
  char motor;
  char accion;
}sEjecucion;

class CRueda
{
  int estado;
  int posicion;
  char aux[20];
  int n;

  int VentanaShuter;
  char Nombre[80];
  bool EnviadaEjecucion;
  double Rad, RadG, rcc, grados, paso;
  int X, Y, Tam, TamPan;
  int NumColores;
  TColor ColorRueda;
  TColor ColorCaja;
  int Pos, ProximaPos;
  Graphics::TBitmap *b;
  HANDLE Hnd;
  TPoint Esquinas[5];
  TWinControl *Padre;
  TPanel *PContenedor;
  TStaticText *LCabecera;
  TStaticText *LConf;
  TPanel *PColores;
  TWndMethod WProc;
  TPanel *PRueda;
  TPanel *PB;
  TPanel *PI;
  TPanel *PR;
  void __fastcall Circulo(double xc, double yc, double r, TColor color);
  void __fastcall Circunferencia(double xc, double yc, double r, TColor color);
  void __fastcall ShapeMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall PanlMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall PAMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall Pintar();
  void __fastcall GuardarConf();
  void __fastcall P(dr DR);
public:
  int Pasos, Marca/*, PasosPorVentana*/;
  sEjecucion Orden;
  sConfiguracion Configuracion;
  TPanel **Panls;
  TColor* Colores;
  int Left;
  int Top;
  int Width;
  int Height;
  int NumPos;
  CSocket *S1;
  char Motor;
  CRueda(TWinControl *Padre, int x = 10, int y = 10, int tam = 125, int NPos = 7, char *mNombre = "", char Mot = 'y');
  ~CRueda();
  void __fastcall AvanzarRueda(int n);
  void __fastcall AvanzarPaso();
  void __fastcall AsignarColor(int pos, TColor color);
  void __fastcall FF(Messages::TMessage &Message);
  void __fastcall crear(dr DR);
  void __fastcall enviarReset();
  void __fastcall enviarPrincipio();
  void __fastcall enviarIniciarMovimiento();
  void __fastcall enviarAvanzarRueda(int n);
  void __fastcall Analizar(char c);
};


#endif
