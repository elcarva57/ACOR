//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <stdlib.h>
#include "Principal.h"
//---------------------------------------------------------------------------
#include "socket.h"
#include "rueda.h"
#include "ConfiFiltro.h"
#include "fitsio.h"
#include <dateutils.hpp>

#include "visualizar.h"
#include "math.h"
#include "Unit3.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "ntofocus.h"

#define min(a, b)  (((a) < (b)) ? (a) : (b))

int FotoActual=1;
int nfotos = 0;
int PerRefrescoTel = 1;
WideString NombreFichero;
extern int numeroOrdenAnterior;
extern bool FinFoto, A_FinFoto, B_FinFoto;
extern DWORD A_T_Ini_Exp, A_T_Ini_Lect, A_T_Fin_Lect;
extern DWORD B_T_Ini_Exp, B_T_Ini_Lect, B_T_Fin_Lect;
bool PintarRectAnt = true;
int X1T, X2T, Y1T, Y2T;
int X1F, X2F, Y1F, Y2F;
int X1FS, X2FS, Y1FS, Y2FS;

typedef struct {
  TDateTime Hora;
  float LeturasTemp;
  int LeturasHumedad;
  float LeturasRocio;
  int LeturasNubes;
  int LeturasLluvia;
  int LeturasAnem;
  int LeturasAnemT;
  int LeturasAnemT2;
  int LeturasDireccion;
  float LeturasPluvio;
}METEODATOS;

METEODATOS grafico24h[1440];
bool OrdenCalibrar;
// int Referencia[] = {0, 0, 0, 0, 0, 0, 0, 0}; // en caliente a 25ºC
int Referencia[] = {49, 23, 28, 29, 24, 26}; // en caliente a 25ºC


AnsiString mPath;

TDateTime FechaFoto, FechaFoto_fin;
extern int numeroOrden;
extern int numeroLinea;

extern unsigned short *Pixeles;
extern Graphics::TBitmap *BM;

int Temp_x10, Rocio_x10, pluvio,PluvioTotalPrevio,PluvioRelativa, slluvia, snubes, VFuente, humedad;
extern int Tccd, Tcaja, Vpeltier;
int VccdA = 100;

bool LXresponde = false;
bool test;
bool cancel;
int mseg, seg;
  //int col, fil;
int obturetraso, numlimpiados, ObtuIndex, segEntreFotos;
int DogFoto;



void Slew_F(double Ra, double De);
void Slew_F(char *comando);
void GetRaDe_F(double *Ra, double *De);
void barra_horas(void);
void RegularTccdA(void);
void ACOR_SetImage(short*, int width, int height);

TCustomWinSocket *Socket1 = NULL;
DWORD TimeRead;

char sec_1x1[]=
{
	0x09,0x09,0x0A,0x08,0x08,0x08,0x08,
	0x0C,0x1C,0x28,0x38,0x48,0x58,0x68,0x79,0x09,0x09,0x09,
	0x09,0x09,0x09,0x01,0x89,0x09
};

char sec_2x2[]=
{
	0x09,0x09,0x0A,0x08,0x08,0x08,0x08,
	0x0C,0x1C,0x28,0x38,0x48,0x58,0x69,0x78,0x09,0x09,0x09,
	0x09,0x09,0x09,0x01,0x89,0x09
};

char sec_3x3[]=
{
	0x09,0x09,0x0A,0x08,0x08,0x08,0x08,
	0x0C,0x1C,0x28,0x38,0x48,0x58,0x69,0x78,0x09,0x08,0x09,
	0x09,0x09,0x09,0x01,0x89,0x09
};

char sec_4x4[]=
{
	0x09,0x09,0x0A,0x08,0x08,0x08,0x08,
	0x0C,0x1C,0x28,0x38,0x49,0x58,0x69,0x78,0x09,0x08,0x09,
	0x09,0x09,0x09,0x01,0x89,0x09
};



char sec_limpiado[]=
{
	0x09,0x09,0x0A,0x08,0x09,0x08,0x0A,0x08,
	0x09,0x09,0x0A,0x08,0x09,0x09,0x0A,0x08,
	0x09,0x09,0x0A,0x08,0x89
};

char sec_vertical[]=
{0x01, 0x02, 0x01,0x00};


void HacerFoto( short x1, short y1, short x2, short y2, unsigned char binin,
                short seg, short mseg, short NumCol, short NumFil,
                unsigned char test, unsigned char cancel, short nfotos,
                short limpiado, short obturador, short retraso, WideString nomb
              );
void Lupa(int X, int Y, cFoto *Foto, bool actualizar);
//extern int nfotos;
void MueveEnfoque();

WORD Valores[7][7]; //para la lupa
TColor Colores[7][7];

DWORD TiempoInicio = 0;

typedef struct  {
  char* Nombre;
  int ColumnasFisicas;
  int FilasFisicas;
  int ColumnaInicio;
  int FilaInicio;
  int ColumnaFin;
  int FilaFin;
}stCCD;


        //Tamaño fisico y util de los posibles sensores.
        // {"KAFxxxx (zona usable)", long buf salida, total filas, x1,y1, x2,y2}
stCCD CCDs[3] = {
                  {"KAF400 (768x512)",     796, 520,14,4, 782, 516},
                  {"KAF1600 (1536x1024)", 1552,1032,14,4,1538,1026},
                  {"KAF3000 (2016x1512)", 2080,1544,44,18,2060,1530}
                };
//---------------------------------------------------------------------------
extern bool LineaNueva;
extern bool LeyendoFoto;
extern char Salidas, Grupos[4];
extern int paquetesperdidos;
extern DWORD TUltimoEnvio, TRabbit;

//---------------------------------------------------------------------------
int NumeroFilas;
int NumeroColumnas;
int numeroLineaanterior;
cFoto *FotoPrincipal;
double x0 = 0.0 , y0 = (255.0) / (32767.0);

int contador_pasos;
int esbajar, essubir;
bool FinX= 1, EsperandoFinX=0;
char cuenta[8];

bool Sincronizando = false;
bool Timer60sg = false;

char SelCamara;

char Binin = 1;
TForm2 *FActivo = NULL;
//---------------------------------------------------------------------------

void printerror( int status);
//---------------------------------------------------------------------------
int ejex, ejey;
//---------------------------------------------------------------------------
extern double x0, y0;

void AnalizarCFS(char c);
CRueda * Filtro = NULL;
CRueda * Shuter = NULL;

void actualizar_datos(void);

bool first = true;
TPoint points[5];
//////////////////////////////////
//////////////////////////////////
AnsiString EstadoRabbit = "", EstadoAnterior = "";
CSocket *S1 = NULL;
TColor ColorEstado = clBlack;
int celdaX = 0, celdaY = 0;
TForm1 *Form1;
//---------------------------------------------------------------------------
void RellenarBitmap(int x1, int y1, int x2, int y2);
//---------------------------------------------------------------------------


__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
  char *ptr;
  char aux[100];
  FILE *in;

   char config[100][50];
   char ConfMeteo[100];


  FotoPrincipal = new cFoto(NumeroFilas, NumeroColumnas, x0, y0);
  S1 = new CSocket();
  wsprintf(aux, "     %s  %s", S1->NombreHostLocal, S1->cadenaIP);
  PHOST->Caption = aux;

  LeyendoFoto = false;
  Filtro = new CRueda(PFiltro, 0, 0, 100, 7, "Filtro", 'z');
  PFiltro->Width = Filtro->Width-2;
  PFiltro->Height = Filtro->Height-1;
  Filtro->S1 = S1;
  Filtro->enviarReset();

   Shuter = new CRueda(PShuter, 0, 0, 100, 3, "Shuter", 'y');
   PShuter->Width = Shuter->Width-2;
   PShuter->Height = Shuter->Height-1;
   Shuter->S1 = S1;
   Shuter->enviarReset();

   CBCCD->Items->Add(CCDs[0].Nombre);
   CBCCD->Items->Add(CCDs[1].Nombre);
   CBCCD->Items->Add(CCDs[2].Nombre);
   CBCCD->ItemIndex = 0;
   Binin = 2;
  //PBinin->Caption = (int)Binin;
   TBBinin->Position = (int)Binin;
   TBBininChange(TBBinin);

   EFilaInicio->Text = CCDs[0].FilaInicio;// / Binin;
   EFilaFin->Text = CCDs[0].FilaFin;// / Binin;
   EColumnaInicio->Text = CCDs[0].ColumnaInicio;// / Binin;
   EColumnaFin->Text = CCDs[0].ColumnaFin;// / Binin;
   Y1T = CCDs[CBCCD->ItemIndex ].FilaInicio / Binin;
   X1T = CCDs[CBCCD->ItemIndex].ColumnaInicio / Binin;
   Y2T = CCDs[CBCCD->ItemIndex].FilaFin / Binin;
   X2T = CCDs[CBCCD->ItemIndex].ColumnaFin / Binin;

   TimeRead = ::GetTickCount();

   memset(config, ' ', sizeof(config));

   if((in = fopen("config.txt", "rt")) != NULL)
   {
      fread(config, sizeof(config), 1, in);
      fclose(in);

      ELocation->Text = config[0];
      EObserver->Text =config[1];
      ETelescop->Text = config[2];
      EFocal->Text = config[3];
      EApert->Text = config[4];
      EInstrument->Text = config[5];
      EComent->Text = config[6];
      Edit_IP->Text = config[7];
      ERetraso->Text = config[8];
      ELimpiado->Text = config[9];

      CBCCD->ItemIndex = atoi(config[11]);

      CCDs[CBCCD->ItemIndex].FilaInicio =  atoi(config[12]);
      CCDs[CBCCD->ItemIndex].FilaFin = atoi(config[13]);
      CCDs[CBCCD->ItemIndex].ColumnaInicio = atoi(config[14]);
      CCDs[CBCCD->ItemIndex].ColumnaFin = atoi(config[15]);

//        CCDs[CBCCD->ItemIndex].ColumnaFin = atoi(config[15] + 6);
//Edit3->Text = config[15];
      EFilaInicio->Text = CCDs[CBCCD->ItemIndex].FilaInicio;//config[12];
      EFilaFin->Text = CCDs[CBCCD->ItemIndex].FilaFin;//config[13];
      EColumnaInicio->Text = CCDs[CBCCD->ItemIndex].ColumnaInicio;//config[14];
      EColumnaFin->Text = CCDs[CBCCD->ItemIndex].ColumnaFin;//config[15];
      ELatitud->Text = config[16];
      ELongitud->Text =config[17];


     if( strcmp(&config[18][0], "F") == 0 )
          CBFlipVertical->State = cbChecked;
     else  CBFlipVertical->State = cbUnchecked;
     if( strcmp(&config[19][0], "F") == 0 )
          CBFlipHorizontal->State = cbChecked;
     else  CBFlipHorizontal->State = cbUnchecked;



 // PBinin->Caption = ((TTrackBar*)Sender)->Position;
      Binin = PBinin->Caption.ToInt();
      NumeroFilas = CCDs[CBCCD->ItemIndex].FilasFisicas / Binin;
      NumeroColumnas = CCDs[CBCCD->ItemIndex].ColumnasFisicas / Binin;
      Y1F =  CCDs[CBCCD->ItemIndex].FilaInicio / Binin;;
      X1F = CCDs[CBCCD->ItemIndex].ColumnaInicio / Binin;;
      Y2F =  CCDs[CBCCD->ItemIndex].FilaFin / Binin;;
      X2F = CCDs[CBCCD->ItemIndex].ColumnaFin / Binin;;
      PX1->Caption = X1F;
      PY1->Caption = Y1F;
      PX2->Caption = X2F;
      PY2->Caption = Y2F;
      PFil->Caption = NumeroFilas;
      PCol->Caption = NumeroColumnas;
      PB1->Width = NumeroColumnas;;
      PB1->Height = NumeroFilas;;
      PBF->Position = 0;
      FotoPrincipal->Resizear(NumeroColumnas, NumeroFilas);
      RellenarBitmap(0, 0, NumeroColumnas, NumeroFilas);
   }


   if((in = fopen("meteo.txt", "rt")) != NULL)
   {
      fread(ConfMeteo, 75, 1, in);
      fclose(in);

      int k1, sens;
      char auxi[4];

      k1 = 21; //posicion donde empiezan las lecturas en la cadena
      for (sens = 0; sens<6; sens++)
      {
        auxi[0]= ConfMeteo[k1];
        k1++;
        auxi[1]= ConfMeteo[k1];
        k1++;
        auxi[2]= ConfMeteo[k1];
        k1++;
        auxi[3]= 0;
        Referencia[sens] = atoi(auxi);  // Se recupera la Referencia guardada
        k1++;
      }
   }


}



//---------------------------------------------------------------------------

void __fastcall TForm1::TBBininChange(TObject *Sender)
{
  PBinin->Caption = ((TTrackBar*)Sender)->Position;
  Binin = PBinin->Caption.ToInt();
  NumeroFilas = CCDs[CBCCD->ItemIndex].FilasFisicas / Binin;
  NumeroColumnas = CCDs[CBCCD->ItemIndex].ColumnasFisicas / Binin;
  Y1F =  CCDs[CBCCD->ItemIndex].FilaInicio / Binin;;
  X1F = CCDs[CBCCD->ItemIndex].ColumnaInicio / Binin;;
  Y2F =  CCDs[CBCCD->ItemIndex].FilaFin / Binin;;
  X2F = CCDs[CBCCD->ItemIndex].ColumnaFin / Binin;;
  PX1->Caption = X1F;
  PY1->Caption = Y1F;
  PX2->Caption = X2F;
  PY2->Caption = Y2F;
  PFil->Caption = NumeroFilas;
  PCol->Caption = NumeroColumnas;
  PB1->Width = NumeroColumnas;;
  PB1->Height = NumeroFilas;;
  PBF->Position = 0;
  FotoPrincipal->Resizear(NumeroColumnas, NumeroFilas);
  RellenarBitmap(0, 0, NumeroColumnas, NumeroFilas);
//  EFilaInicio->Text = CCDs[CBCCD->ItemIndex].FilaInicio;// / Binin;
//  EFilaFin->Text = CCDs[CBCCD->ItemIndex].FilaFin / Binin;
//  EColumnaInicio->Text = CCDs[CBCCD->ItemIndex].ColumnaInicio / Binin;
//  EColumnaFin->Text = CCDs[CBCCD->ItemIndex].ColumnaFin / Binin;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void AnalizarCFS(char c)
{
  if(Filtro != NULL)
    Filtro->Analizar(c);
  if(Shuter != NULL)
    Shuter->Analizar(c);
}



void ProcesarCFS()
{
  static char cfs[50] = "                                                 ";
  int aa;
  char aux[300];
  aa = min(S1->nDatosCFS, 200);   //como maximo se leen 200 caracteres
  S1->LeerCFS(aux, aa);

  for(int kk = 0; kk < aa; kk++)
  {
      if (aux[kk] == 'X')
      {
        FinX = 1;
        if (esbajar==1)
        {
          esbajar = 0;
          contador_pasos = contador_pasos - atoi(&cuenta[1]);
          Form1->PContador->Caption = contador_pasos;
        }
        else if (essubir == 1)
        {
          essubir = 0;
          contador_pasos = contador_pasos + atoi(&cuenta[1]);
          Form1->PContador->Caption = contador_pasos;
        }
      }

    for(int pp = 0; pp < 48; pp++)
    {
      cfs[pp] = cfs[pp + 1];
    }
    cfs[48] = aux[kk];
    AnalizarCFS(aux[kk]);
  }
  cfs[49] = 0;
  Form1->PCFS->Caption = cfs;
}

/*
      -----------------------------------
      		FUNCIONAMIENTO DE LA ESTACION
             -----------------------------------
Comunicacion serie a 9600 baudios.
Los mensajes de control generados por el pc constan de un solo caracter.
El mensaje generado por la estacion tiene longitud total fija de 75 caracteres,
 empieza por "(" y termina con ")".
                  ----------------------

Mensaje PC -> estacion:
        @ : calentadores apagados, situacion por defecto al arrancar
        A : calentador A encendido
        B : calentador B encendido
        C : calentador A on y B encendidos
        R : lecturas bajo peticion, una vez por cada R
        S : send lecturas continuamente, cada 2 seg aproximadamente
        I : Pone a cero contador de anemometro movil.
        K : pone a cero contador del pluviometro
        H : reset software del sensor de humedad
                 -----------------------

Mensaje estacion -> PC:

(0@0 010 020 112 040 112 088 101 078 113 138 112 112 -239 426 +074 1234567) <- ej. mensaje de la estacion
pos.5^  9^ 13^ 17^ 21^ 25^ 29^ 33^ 37^ 41^ 45^ 49^ 53^  58^ 62^  67^        <- posiciones en la cadena
  1   2   3   4   5   6   7   8   9   10  11  12  13   14  15   16   17     <- bloques

bloque 1 - tres caracteres independientes, ESTATUS, CONTROL y PLUVIOMETRO
  pos.0 ( : empieza el mensaje
  pos.1 ESTATUS: indica errores
        * : arranque de un reset (tambien se genera un /r/n)
        ! : error de lectura del Sensor de humedad
        0 : no hay errores
  pos.2 CONTROL: eco del ultimo caracteres de control recibido.
  pos.3 SALIDAS: estado de las salidas de potencia @,A,B o C

bloque 2 - ch0 del conversor AD, indicador lluvia o rocio
bloque 3 - ch1 del conversor AD, indicador de nubes
bloque 4 - ch3 del conversor AD, reservado barometro
bloque 5 - contador del pluviometro de 000 a 999. Se pone a cero con "K"

bloque 6  -  veleta 1
bloque 7  -  veleta 2
bloque 8  -  veleta 3
bloque 9  -  veleta 4
bloque 10 -  veleta 5
bloque 11 -  veleta 6
bloque 12 -  Tension de alimentacion de la estacion -
bloque 13 -  sonda omnidireccional de temperatura  -

bloque 14: ej. +239 : temperatura ºC x10
bloque 15:  "  426  : humedad relativa en % x10
bloque 16:  "  -012 : punto de rocio ºC x10
bloque 17:  " 1234567 : contador anemometro movil. Se pone a cero con "I"

pos. 74: )   Fin de mensaje
                ---------------------------
*/

void ProcesarMeteo()
{
 static char Meteo[200];
 static int DifRefX, DifRefY, Dif_LX, Dif_LY;
 static double ValorX, ValorY;
 static int AnemometroT, AnemometroT2, SAnemometroT, SAnemometroT2, SDireccion;
 static int Direccion, CuentaMensMeteo;
 static int sens;
 static int L[6];
 static int Dif_L[6];
 static long VelVientoRelativa, AnemTotal, AnemTotalPrevio;
 static bool abreparen;
 static int posmeteo;
 int LongBuff, pos, kk;
 char Buff[2000];
 char aux2[6];
 float t,h;

 FILE *out;


    LongBuff = min(S1->nDatosMeteo,500);
    S1->LeerMeteo(Buff, LongBuff);
    Buff[LongBuff]= 0;


    for(pos = 0; pos < LongBuff; pos++)
    {
       if (Buff[pos] == '(' )
       {
          abreparen = 1;
          posmeteo = 0;
       }
       if (abreparen == 1)
       {
          if ((Buff[pos]< ' ' )||(Buff[pos]>'}'))
            Meteo[posmeteo] = ' ';//caracter " "  indicando fuera de lo esperado
          else
            Meteo[posmeteo]= Buff[pos];
          posmeteo++;
          if (posmeteo > 200)
            posmeteo = 0;
       }
       if ((Buff[pos] == ')' ) && (posmeteo == 75)  )  // ha terminado el mensaje
       {
          CuentaMensMeteo++;
          Meteo[posmeteo]= 0;
          posmeteo = 0;
          abreparen = 0;
          Form1->Paux->Caption = Meteo;

          if(OrdenCalibrar)     //se guarda la cadena meteo en el fichero meteo.txt
          {
            OrdenCalibrar = false;
            out = fopen("meteo.txt", "wt");
            fwrite(Meteo, sizeof(Meteo), 1, out); /* write struct s to file */
            fclose(out); /* close file */
            kk = 21; //posicion donde empiezan las lecturas en la cadena
            for (sens = 0; sens<6; sens++) // se saca nueva Referencia del fichero
            {
              aux2[0]= Meteo[kk];
              kk++;
              aux2[1]= Meteo[kk];
              kk++;
              aux2[2]= Meteo[kk];
              kk++;
              aux2[3]= 0;
              Referencia[sens] = atoi(aux2);
              kk++;
            }
          }

//Signo de la temperatura
          aux2[0]= Meteo[53];
          aux2[1]= Meteo[54];
          aux2[2]= Meteo[55];
          aux2[3]= Meteo[56];
          aux2[4]= 0;
          Temp_x10 = atoi(aux2);
          aux2[4]= Meteo[56];
          aux2[3]= '.';
          aux2[5]= 0;
          Form1->PTempAmbiente->Caption = aux2;

//Humedad relativa
          aux2[0]= Meteo[58];
          aux2[1]= Meteo[59];
          aux2[2]= Meteo[60];
          aux2[3]= 0;
   //       h = AnsiString(aux2).ToInt() / 10.0;
          if (h<=0) h =1;

          aux2[2]= '.';
          aux2[3]= Meteo[60];
          aux2[4]= '%';
          aux2[5]= 0;
          Form1->PHumedad->Caption = aux2;
          aux2[0]= Meteo[58];
          aux2[1]= Meteo[59];
          aux2[2]= 0;
          humedad = atoi(aux2);

//Signo del  punto de rocio
          aux2[0]= Meteo[62];
          aux2[1]= Meteo[63];
          aux2[2]= Meteo[64];
          aux2[3]= Meteo[65];
          aux2[4]= 0;
          Rocio_x10 = atoi(aux2);
      //   Form1->PTempAmbiente->Caption = aux2;
      //    aux2[0]='-';
   //       t = AnsiString(aux2).ToInt() / 10.0;
         // Form1->PTempAmbiente->Caption = t;
          aux2[4]= Meteo[65];
          aux2[3]= '.';
          aux2[5]= 0;
          Form1->PPuntoRocio->Caption = aux2;


//Sensor de lluvia
          aux2[0]= Meteo[5];
          aux2[1]= Meteo[6];
          aux2[2]= Meteo[7];
          aux2[3]= 0;
//          int slluvia = (aux2[0]-0x30)*100 + (aux2[1]-0x30)*10 + (aux2[2]-0x30);
          slluvia = 255 - atoi(aux2);
          Form1->PLluvia->Caption = slluvia;

//Pluviometro
          aux2[0]= Meteo[17];
          aux2[1]= Meteo[18];
          aux2[2]= Meteo[19];
          aux2[3]= 0;
          pluvio = atoi(aux2);
          PluvioRelativa = pluvio - PluvioTotalPrevio;
          sprintf(aux2,"%04.1f",pluvio*0.421);
//          sprintf(aux2,"%04.1f",PluvioRelativa* 0.421);
          Form1->PPluviometro->Caption = aux2;

//Sensor de nubes
          aux2[0]= Meteo[9];
          aux2[1]= Meteo[10];
          aux2[2]= Meteo[11];
          aux2[3]= 0;
          snubes = 255 - atoi(aux2);
          Form1->PNublados->Caption = snubes;

//Fuente de alimentacion
          aux2[0]= Meteo[45];
          aux2[1]= Meteo[46];
          aux2[2]= Meteo[47];
          aux2[3]= 0;
          VFuente = atoi(aux2);
          if (VFuente/9.13 < 9.6) Form1->PVFuente->Color = clRed; //9.13 ajusta la lectura
            else Form1->PVFuente->Color = clBtnFace;
          Form1->PVFuente->Caption = FloatToStrF(VFuente/9.13, ffNumber, 3,1 ) + " v";


//-----------------------------------------------------------------
//----------Temperatura-velocidad del viento sumatorio-------------
//-----------------------------------------------------------------

          //extraccion de lecturas desde la cadena
          kk = 21; //posicion donde empiezan las lecturas en la cadena
          for (sens = 0; sens<6; sens++)
          {
              aux2[0]= Meteo[kk];
              kk++;
              aux2[1]= Meteo[kk];
              kk++;
              aux2[2]= Meteo[kk];
              kk++;
              aux2[3]= 0;
              L[sens] = atoi(aux2);
              kk++;
          }

          // extraccion de diferencias de lecturas
          for (sens = 0; sens <6; sens++)
              Dif_L[sens] = L[sens] - Referencia[sens];

          Dif_LX =int(Dif_L[0]*1 + Dif_L[1]*0.866 -Dif_L[2]*0.866  //cos
                     -Dif_L[3]*1 -Dif_L[4]*0.866 +Dif_L[5]*0.866);
          Dif_LY = int(Dif_L[0]*0 + Dif_L[1]*0.5 + Dif_L[2]*0.5      //sen
                     + Dif_L[3]*0 - Dif_L[4]*0.5 - Dif_L[5]*0.5);

// Lecturas 0-2-4 -> zener 1-3-5
/*          Dif_LX =int(Dif_L[0]*1  - Dif_L[2]*0.866 - Dif_L[4]*0.866 );
          Dif_LY = int(Dif_L[0]*0  + Dif_L[2]*0.5 - Dif_L[4]*0.5 );
*/
// Lecturas 1-3-5 -> zener 2-4-6
/*          Dif_LX = int( Dif_L[1]*0.866 - Dif_L[3]*1 + Dif_L[5]*0.866);
          Dif_LY = int( Dif_L[1]*0.5 + Dif_L[3]*0  - Dif_L[5]*0.5);
*/

          // se resta a la lectura la referencia u ofset.
          ValorX = Dif_LX;
          ValorY = Dif_LY;

          AnemometroT = int(sqrt(pow(ValorX,2) + pow(ValorY,2))); // amplitud de la medida

//Anemometro termico suma vectorial
          Form1->PVelVientoT->Caption = AnemometroT;
          SAnemometroT = SAnemometroT + AnemometroT;

//Anemometro termico suma modulos
          AnemometroT2 = int(Dif_L[0] + Dif_L[1] + Dif_L[2] +Dif_L[3]*1 +Dif_L[4] +Dif_L[5]);
        //  AnemometroT2 = AnemometroT2/2; //para que normalmente entre en la grafica normalizada a 100


          AnemometroT2 = int( exp(0.012*AnemometroT2 + 0.1345)); // conversion a Km/h
          Form1->PvelOmni->Caption = AnemometroT2;
          SAnemometroT2 += AnemometroT2;

//Veleta
          if(AnemometroT > 15)
          {

            if ((ValorX !=0) || (ValorY !=0))    // angulo de 0 a 180 y de 0 a -180
                Direccion = (atan2(ValorY,ValorX))*(180/3.1416);
            if (Direccion < 0)
                Direccion = 360 + Direccion;   // angulo de 0 a 360

            Form1->PDirViento->Caption = Direccion;
            
            if ((Direccion >337) || (Direccion <= 22))
            {
              Form1->PDirNSEO->Caption = " N";
              Direccion = 1;
            }
            else if ((Direccion >22) && (Direccion <= 67))
              Form1->PDirNSEO->Caption = "NE";
            else if ((Direccion >67) && (Direccion <= 112))
              Form1->PDirNSEO->Caption = " E";
            else if ((Direccion >112) && (Direccion <= 157))
              Form1->PDirNSEO->Caption = "SE";
            else if ((Direccion >157) && (Direccion <= 202))
              Form1->PDirNSEO->Caption = " S";
            else if ((Direccion >202) && (Direccion <= 247))
              Form1->PDirNSEO->Caption = "SO";
            else if ((Direccion >247) && (Direccion <= 292))
              Form1->PDirNSEO->Caption = " O";
            else if ((Direccion >292) && (Direccion <= 337))
              Form1->PDirNSEO->Caption = "NO";
          }


//        SDireccion = SDireccion + Direccion;
//        Form1->Memo1->Lines->Add("Dir: " + AnsiString(SDireccion));

//Anemometro termico Omnidireccional
//        AnemometroT2 = (L[7]-Referencia[7]);
//        Form1->PvelOmni->Caption = AnemometroT2;
//        SAnemometroT2 = SAnemometroT2 + AnemometroT2;

//----------------------------------------------------------------------

          if (Timer60sg)
          {
             Timer60sg =false;
                                //
             aux2[0]= Meteo[67];
             aux2[1]= Meteo[68];
             aux2[2]= Meteo[69];
             aux2[3]= Meteo[70];
             aux2[4]= Meteo[71];
             aux2[5]= Meteo[72];
             aux2[6]= Meteo[73];
             aux2[7]= 0;
             AnemTotal = atoi(aux2);
             if (AnemTotal < AnemTotalPrevio) AnemTotalPrevio = 0;
             VelVientoRelativa = AnemTotal - AnemTotalPrevio;
             if (VelVientoRelativa > 1000) VelVientoRelativa =0;

             AnemTotalPrevio = AnemTotal;
             VelVientoRelativa =  VelVientoRelativa * 0.2; // conversion a Km/h
             Form1->PVelViento->Caption = VelVientoRelativa;


             for (kk = 0; kk < 1439; kk++)  //desplazamiento de los datos
             {
                grafico24h[kk].Hora = grafico24h[kk + 1].Hora;
                grafico24h[kk].LeturasAnem = grafico24h[kk+1].LeturasAnem;
                grafico24h[kk].LeturasAnemT2 = grafico24h[kk+1].LeturasAnemT2;
                grafico24h[kk].LeturasAnemT = grafico24h[kk + 1].LeturasAnemT;
                grafico24h[kk].LeturasDireccion = grafico24h[kk + 1].LeturasDireccion;
                grafico24h[kk].LeturasTemp = grafico24h[kk + 1].LeturasTemp;
                grafico24h[kk].LeturasRocio = grafico24h[kk + 1].LeturasRocio;
                grafico24h[kk].LeturasPluvio = grafico24h[kk + 1].LeturasPluvio;
                grafico24h[kk].LeturasNubes = grafico24h[kk+1].LeturasNubes;
                grafico24h[kk].LeturasLluvia = grafico24h[kk + 1].LeturasLluvia;
                grafico24h[kk].LeturasHumedad = grafico24h[kk + 1].LeturasHumedad;
             }

 //lectura de nuevos valores
             grafico24h[1439].Hora=TimeToStr(Time());
             grafico24h[1439].LeturasAnem = VelVientoRelativa;
             grafico24h[1439].LeturasAnemT2 = (SAnemometroT2)/CuentaMensMeteo;
               if  (grafico24h[1439].LeturasAnemT2 > 600 ) grafico24h[1439].LeturasAnemT2 = 0;
               if  (grafico24h[1439].LeturasAnemT2 < 0 ) grafico24h[1439].LeturasAnemT2 = 0;
             grafico24h[1439].LeturasAnemT = SAnemometroT/CuentaMensMeteo;
         //     Form1->Memo1->Lines->Add("AnemometroT 60sg : " + AnsiString(SAnemometroT) +" Div: " + AnsiString(Form1->Timer2->Interval/Form1->Timer3->Interval));
             if(grafico24h[1439].LeturasAnemT > 5)  // solo cambia veleta si velocidad apreciable
               grafico24h[1439].LeturasDireccion = (Direccion/360.0)*100;
             else
               grafico24h[1439].LeturasDireccion = grafico24h[1438].LeturasDireccion;

             SAnemometroT2 = 0;
             SAnemometroT = 0;
             CuentaMensMeteo = 0;

             grafico24h[1439].LeturasTemp = Temp_x10/10.0;
             grafico24h[1439].LeturasRocio = Rocio_x10/10.0;
             grafico24h[1439].LeturasPluvio = (pluvio*0.421); // en litros
             grafico24h[1439].LeturasNubes = (snubes*100)/255;
             grafico24h[1439].LeturasLluvia = (slluvia*100)/255;
             grafico24h[1439].LeturasHumedad = humedad;


 //borrado de la grafica anterior
             FGraficas->Series1->Clear();
             FGraficas->Series7->Clear();
             FGraficas->Series3->Clear();
             FGraficas->Series8->Clear();
             FGraficas->AreaSeries1->Clear();
             FGraficas->Series2->Clear();

             FGraficas->AreaSeries2->Clear();
             FGraficas->Series5->Clear();
             FGraficas->Series4->Clear();
             FGraficas->Series6->Clear();

//creacion grafica actual
             for (kk = 0; kk < 1439; kk++)
             {
                FGraficas->AreaSeries1->AddXY(kk, grafico24h[1439-kk].LeturasTemp, grafico24h[1439-kk].Hora, clRed);
                FGraficas->Series2->AddXY(kk, grafico24h[1439-kk].LeturasRocio, grafico24h[1439-kk].Hora, clGreen);

                FGraficas->Series1->AddXY(kk, grafico24h[1439-kk].LeturasAnem, grafico24h[1439-kk].Hora, clBlue);
                FGraficas->Series7->AddXY(kk, grafico24h[1439-kk].LeturasAnemT2,grafico24h[1439-kk].Hora , clGreen);
                FGraficas->Series3->AddXY(kk, grafico24h[1439-kk].LeturasAnemT, grafico24h[1439-kk].Hora, clRed);
                FGraficas->Series8->AddXY(kk, grafico24h[1439-kk].LeturasDireccion, grafico24h[1439-kk].Hora, clYellow);

                FGraficas->AreaSeries2->AddXY(kk, grafico24h[1439-kk].LeturasPluvio, grafico24h[1439-kk].Hora, clRed);

                FGraficas->Series5->AddXY(kk, grafico24h[1439-kk].LeturasNubes, grafico24h[1439-kk].Hora, clGray);
                FGraficas->Series4->AddXY(kk, grafico24h[1439-kk].LeturasLluvia, grafico24h[1439-kk].Hora, clRed);
                FGraficas->Series6->AddXY(kk, grafico24h[1439-kk].LeturasHumedad, grafico24h[1439-kk].Hora, clBlue);
             }
          }
        }
    }
}




bool pedidaRaDe = false;
char cRa[20], cDe[20];
int nRa = 0, nDe = 0;
bool segalm = false;
double tRa = 0, tDe = 0;
extern char carecta[100], cdeclinacion[100];
double nRAHour = 0, dRAMin = 0, nDecDeg = 0, nDecMin = 0 ;
bool negativo = false;

void ProcesarLX200()
{
  char aux[300];

  if(pedidaRaDe == true)
  {
    while(S1->nDatosLX200 > 0)
    {

      S1->LeerLX200(aux, 1);
      if(segalm == false)     // primera vez, Cadena RA
      {
        if(aux[0] == '#')
        {
          LXresponde = true;
          cRa[nRa] = 0;
          dRAMin  = atof(cRa);
          nRa = 0;
          segalm = true;
        }
        else if(aux[0] == ':')
        {
          cRa[nRa] = 0;
          if (atof(cRa) < 25)
            nRAHour = atof(cRa);
          else
            Form1->Mhistory->Lines->Add("slew ");
          nRa = 0;
        }
        else
        {
          if(nRa < 7)
            cRa[nRa++] = aux[0];
          else
          {
            pedidaRaDe = false;
            nRa = 0;
          }
        }
      }
      else                  // segunda vez, cadena DEC
      {
        if(aux[0] == '#')
        {
          cDe[nDe] = 0;
          nDecMin = atof(cDe);
          tDe = nDecDeg + (nDecMin / 60.0);
          if(negativo == true)
          {
            tDe = -tDe;
          }
          tRa = 15.0 * ( nRAHour + dRAMin / 60.0);
          nDe = 0;
          segalm = false;
          pedidaRaDe = false;
        }
        else if(aux[0] == (char)0xDF)
        {
          if(cDe[0] == '-')
            negativo = true;
          else
            negativo = false;
          cDe[nDe] = 0;
          nDecDeg = atof(&cDe[1]);
          nDe = 0;
        }
        else
        {
          if(nDe < 7)
            cDe[nDe++] = aux[0];
          else
          {
            pedidaRaDe = false;
            nDe = 0;
          }
        }
      }
    }
  }
}



//---------------------------------------------------------------------------
void actualizar_datos(void)
{
  TColor col[2] = {clGray, clRed};
  TColor col1[2] = {clGray, clLime};

  float pp = Tccd;
  pp *= 10.0/32767.0;
  pp = (pp/0.01)-273;
  if((pp<100)&(pp>-100))
    {
      Form1->PTccd->Caption = FloatToStrF(pp, ffFixed, 15, 1);
    }
    else Form1->PTccd->Caption = "---";

  pp = Tcaja;
  pp *= 10.0/32767.0;
  pp = (pp/0.01)-273;
  if((pp<100)&(pp>-100))
    Form1->PTcaja->Caption = FloatToStrF(pp, ffFixed, 15, 1);
      else Form1->PTcaja->Caption = "---";

  pp = Vpeltier;
  pp *= 10.0/32767.0;
  pp = pp*2; //porque hay un divisor de tension
  if((pp<15)&(pp>=0))
    Form1->PVpeltier->Caption = FloatToStrF(pp, ffFixed, 15, 1);
      else Form1->PVpeltier->Caption = "---";

  Form1->Sbit1->Brush->Color = col[Salidas & 0x01];
  Form1->Sbit2->Brush->Color = col[(Salidas & 0x02) >> 1];
  Form1->Sbit3->Brush->Color = col[(Salidas & 0x04) >> 2];
  Form1->Sbit4->Brush->Color = col[(Salidas & 0x08) >> 3];
  Form1->Sbit5->Brush->Color = col[(Salidas & 0x10) >> 4];
  Form1->Sbit6->Brush->Color = col[(Salidas & 0x20) >> 5];
  Form1->Sbit7->Brush->Color = col[(Salidas & 0x40) >> 6];
  Form1->Sbit8->Brush->Color = col[(Salidas & 0x80) >> 7];

  Form1->ss1->Brush->Color = col1[Grupos[0] & 0x01];
  Form1->ss2->Brush->Color = col1[(Grupos[0] & 0x02) >> 1];
  Form1->ss3->Brush->Color = col1[(Grupos[0] & 0x04) >> 2];
  Form1->ss4->Brush->Color = col1[(Grupos[0] & 0x08) >> 3];
  Form1->ss5->Brush->Color = col1[(Grupos[0] & 0x10) >> 4];
  Form1->ss6->Brush->Color = col1[(Grupos[0] & 0x20) >> 5];
 /*
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
 */


}


//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  Timer1->Enabled = false;
  delete Filtro;
  delete Shuter;
  delete S1;
}
//---------------------------------------------------------------------------


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
	fits_get_errstatus(status, status_str);   // get the error description  wsprintf(aux, "\nstatus = %d: %s\n", status, status_str);
  Memo1->Lines->Add(aux);

  if ( fits_read_errmsg(errmsg) )//get first message; null if stack is empty
  {
    Memo1->Lines->Add( "\nError message stack:\n");
    Memo1->Lines->Add( errmsg);
    while ( fits_read_errmsg(errmsg) )  // get remaining messages
      Memo1->Lines->Add( errmsg);
  }
}


//---------------------------------------------------------------------------

void __fastcall TForm1::BEnviarClick(TObject *Sender)
{
  char aux[300];

  aux[0] = 50;
  strcpy(&aux[2], CBEnviar->Text.c_str());
  if(CBEnviar->Text == "reset")
      aux[0] = 60; //para hacer reset al cor
  S1->Escribir(aux, CBEnviar->Text.Length() + 2, S1->IPRabbit);
}
//-----------------------------------------------------------------------

/*
void __fastcall TForm1::BPonerHcorClick(TObject *Sender)
{
  char aux[300];

  aux[0] = 60;
  strcpy(&aux[2], EPonerHcor->Text.c_str());
  S1->Escribir(aux, CBEnviar->Text.Length() + 2, S1->IPRabbit);
}
*/


//-----------------------------------------------------------------------

void RellenarBitmap(int x1, int y1, int x2, int y2)
{
  FotoPrincipal->Pintar(x1, y1, x2, y2);

  BitBlt(Form1->PB1->Canvas->Handle, x1, y1, x2, y2, FotoPrincipal->BM->Canvas->Handle, x1, y1, SRCCOPY);
  if(first == false)
  {
    points[0] = Point(X1T, Y1T);
    points[1] = Point(X2T, Y1T);
    points[2] = Point(X2T, Y2T);
    points[3] = Point(X1T, Y2T);
    points[4] = Point(X1T, Y1T);
    Form1->PB1->Canvas->Pen->Color = clWhite;
    Form1->PB1->Canvas->Pen->Mode = pmXor;
    Form1->PB1->Canvas->Polyline(points, 4);
  }
  Form1->PMax->Caption = FotoPrincipal->maximo;
  Form1->PMin->Caption = FotoPrincipal->minimo;
}



//------------ Timer gestion de conexion y peticion de coordenadas -------------
//int c1 = 0, c2 = 0;



//---------------------------------------------------------------
//--------------------  Timer1 50ms Gestion Fotos  --------------------
//---------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  char aux[300];
  char Name[80];
  char *punteroX;
  static  int retardo1s;
  static int FocoEstable; //enfocando se usa para esperar un tiempo estabilizacion del foco. 
  TJPEGImage *jp;
  static bool sonido;
  if(LeyendoFoto == true)
  {
    if(LineaNueva == true)
    {

      LineaNueva = false;
      if(CBPintar->State == cbChecked)
      {
        RellenarBitmap(X1FS, Y1FS, X2FS, Y2FS);
      }
 //     if(CBimagen->ItemIndex != 3)
   //     PCancel->Visible = false;
      int p = numeroLinea*100/(Y2F-Y1F);
      if(p <= 100)
      {
        PBF->Position = p;   //barra de progreso de lectura
        if(sonido == false)
        {
          Beep();
          sonido = true;
        }
        //  if((FotoActual > nfotos) && (p < 5))
         //   Beep();

      }
      else
        PBF->Position = 100;
    }
    if(FinFoto == true)     // se ha terminado una foto
    {
      sonido = false;
      FechaFoto =  FechaFoto.CurrentDateTime();
  //    if(FotoActual > nfotos)
    //    Beep();


      RellenarBitmap(X1FS, Y1FS, X2FS, Y2FS);
      LeyendoFoto = false;

      PCancel->Visible = true;
      if(FotoActual > nfotos)
          Panel5->Enabled = true;

      SLedFoto->Brush->Color = clGray;
      if(PFoto->BevelOuter == bvLowered)
      {
        PFoto->BevelOuter = bvRaised;
        PFoto->Color = clSilver;
        SLedFoto->Brush->Color = clGray;
        SLedFoto->Repaint();
        PBF->Position = 0;
      }
      long media =  FotoPrincipal->media();

      if(ObtuIndex == 3)  //estamos enfocando
      {

//        ACOR_SetImage((short*)FotoPrincipal->Pixeles, NumeroFilas, NumeroColumnas);
          ACOR_SetImage((short*)FotoPrincipal->Pixeles, X2F-X1F, Y2F-Y1F);                                        
        float hfd;
        int result = AF_HFD(&hfd);

  // No se puede pedir el centroide sin haber llamado a AF_HFD primero

        float xc,yc;
        AF_GetCentroid(&xc, &yc);
        Form1->Mhistory->Lines->Add("Centroid: X =" + AnsiString(xc) + " Y =" + AnsiString(yc));
        Form1->Mhistory->Lines->Add("hfd =" + AnsiString(hfd));
        Form1->Mhistory->Lines->Add("res AF_HFD =" + AnsiString(result));
      }

      if (A_FinFoto == true)
      {
        A_FinFoto = false;
//       Form1->Mhistory->Lines->Add("Exp: " + AnsiString(A_T_Ini_Lect - A_T_Ini_Exp)
  //      +" Lectura: "+ AnsiString(A_T_Fin_Lect - A_T_Ini_Lect + obturetraso*100) );
      }
      double pos_x, pos_y;
      if(Form1->CBautostrech->Checked == true)
      {
        pos_x = FotoPrincipal->fondocielo - atoi(Form1->estirar_bajo->Text.c_str());
        pos_y = FotoPrincipal->fondocielo + atoi(Form1->estirar_alto->Text.c_str());
        TBx0->Position = pos_x;
        TBy0->Position = pos_y;
        PB1->Repaint();
      }
      jp = new TJPEGImage();     // creacion del fichero jpg
      try
      {
        jp->Assign(FotoPrincipal->BM);
        jp->SaveToFile("c:\\inetpub\\wwwroot\\pp.jpg");
      }
      __finally
      {
        delete jp;
      }
      Form1->TiempoPasado->Caption = 0;

       SetCurrentDirectory( mPath.c_str());
      if((CBGuardar->Checked == true) && (paquetesperdidos == 0))
      {
        sprintf( aux, "%003d", (FotoActual-1));
        sprintf(Name, (ENombreFichero->Text + AnsiString("_") + AnsiString(aux) + AnsiString(".fit")).c_str());

        if(FileExists(Name))
          DeleteFile(Name);
        GuardarFoto(Name);

        if(FileExists( "c:\\inetpub\\wwwroot\\aux_1.fit") )
            DeleteFile("c:\\inetpub\\wwwroot\\aux_1.fit");
        CopyFile(Name, "c:\\inetpub\\wwwroot\\aux_1.fit",  NULL);
      }

    }
  }

  else if(FotoActual<=nfotos)
  {
    numeroOrden = 0;
    SLedFoto->Brush->Color = clRed;
    PCancel->Visible = true;
    {
      if(S1 != NULL)
      {
        if(abs(Y2F-Y1F)<10 || abs(X2F-X1F)<10)
        {
           Timer1->Enabled = false;
           Application->MessageBox("Rectangulo demasiado pequeño", "Atención", MB_OK);
           Timer1->Enabled = true;
           FotoActual = 1;
           nfotos = 0;
           LeyendoFoto = false;
           FinFoto = true;
           PFoto->BevelOuter = bvRaised;
           PFoto->Color = clSilver;
           SLedFoto->Brush->Color = clGray;

           return;
        }

        retardo1s++;    //
        if (retardo1s > 10)    //retardo de 10 * 50ms del timer para actualizar el contador
        {
          retardo1s=0;
          TiempoPasado->Alignment = taRightJustify;
          TiempoPasado->Caption = (::GetTickCount() - TiempoInicio) / 1000;
          DogFoto = 0;
        }


        if (((::GetTickCount() - TiempoInicio) / 1000 >= segEntreFotos) ||(FotoActual == 1))
        {

          if(ObtuIndex == 3)  //estamos enfocando
          {
             if (FinX == 1 )
                FocoEstable++;
             obturetraso = 0;
             if(FotoActual > 1)
                numlimpiados = 1; //no se limpian siguientes lecturas
             else
             {
                numlimpiados = ELimpiado->Text.ToInt(); //limpiado primera vez
                if((ObtuIndex == 3) && (Form1->MEPasosEnfoque->EditText.ToInt() >100))
                  Form1->MEPasosEnfoque->EditText = "00050"; // limita mover demasiado el enfoque
             }
                    //mover motor de enfoque
             if (FotoActual > 1 && FinX==1 && EsperandoFinX==0 && CBAutoEnfoque->State == cbChecked )
             {
               MueveEnfoque();
               EsperandoFinX = 1;
               FocoEstable = 0;
             }
             else
               FocoEstable = MEEstabilizar->Text.ToInt();
          }
          else
          {
            FocoEstable = MEEstabilizar->Text.ToInt();
          }

          if ((FinX ==1)&&(FocoEstable >= MEEstabilizar->Text.ToInt()/50)) //si el motor de enfoque esta parado podemos pedir Foto
          {
            FotoPrincipal->maximo = 0;
            FotoPrincipal->minimo = 0xFFFF;                               //
            EsperandoFinX = 0;
            DogFoto = 0;

            TiempoInicio =  ::GetTickCount();
            TNFotos->Caption = FotoActual;//nfotos - m_numfotos;
            if(ObtuIndex == 3)
               Form1->Mhistory->Lines->Add("-> Cont. Enfoque: " + PContador->Caption );
//          if (ObtuIndex != 3)
//             Form1->Mhistory->Lines->Add("Fotos pendientes: " + AnsiString(nfotos - FotoActual + 1));
            HacerFoto( X1F, Y1F, X2F, Y2F, Binin, seg, mseg, CCDs[CBCCD->ItemIndex].ColumnasFisicas, CCDs[CBCCD->ItemIndex].FilasFisicas, test, cancel, nfotos, numlimpiados, ObtuIndex, obturetraso, "");
            PFoto->BevelOuter = bvLowered;
            PFoto->Color = (TColor)0x00DEDEDE;
            SLedFoto->Brush->Color = clRed;
            Panel5->Enabled = false;
            FotoActual++;
            LeyendoFoto = true;
          }
        }

      }
    }
  }  //fin del if(LeyendoFoto == true)
     //PASAR TODO LOS QUE SIGUE AL TIMER2
  else
  {
    PB1->Enabled = true; //permite redimensionar los rectangulos.
  }
}
//----------------- Termina Funcion del Timer 1 -------------------------


// timer 2 de 60sg para la genstion de los graficos meteorologicos
//-----------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{   // Interval de T2 debe ser divisible por T3
    char aux[300];
    static int refres_jpg;

    //   static float LeturasPluvio[1440];

//   static char   LeturasLluvia[1440];
//   static char LeturasNubes[1440];
//    static int micuenta;
//    static int sens;
//    static int DifRefX, DifRefY, Dif_LX, Dif_LY;
//    static double ValorX, ValorY, Modulo;
//    static int Direccion;
//   static int Referencia[] = {100, 80, 91, 73, 101, 122, 100, 100};
//    static int L[] = {140, 119, 132, 111, 142, 177, 162, 150};   //L1
//    static int DifRef[8];
//    static int Dif_L[8];


  Timer60sg = true;


/*  aux[0] = 4;   //mensaje al puerto auxiliar (D) del COR
  aux[1] = 0;
  strcpy(&aux[2],"R");
  S1->Escribir(aux, 1 + 2, S1->IPRabbit);   //peticion de informacion de meteo
  */
  //  kk(4);  //para sacar mensaje de test

  if (refres_jpg >5)     //los ficheros se van a actualizar cada 5 minutos
  {

 
  TJPEGImage *jp;
  Graphics::TBitmap *Bitmap1 = new Graphics::TBitmap();


    FGraficas->Chart1->SaveToBitmapFile("c:\\inetpub\\wwwroot\\Anemometro.bmp");
    FGraficas->Chart2->SaveToBitmapFile("c:\\inetpub\\wwwroot\\temperatura.bmp");
    FGraficas->Chart3->SaveToBitmapFile("c:\\inetpub\\wwwroot\\pluviometria.bmp");
    FGraficas->Chart4->SaveToBitmapFile("c:\\inetpub\\wwwroot\\lluvia_nubes.bmp");

  jp = new TJPEGImage();
  try
  {
 //     FGraficas->Visible = true;
 //     FGraficas->Update();

    Bitmap1 = new Graphics::TBitmap();
    Bitmap1->LoadFromFile("c:\\inetpub\\wwwroot\\Anemometro.bmp");
    jp->Assign(Bitmap1);
    jp->SaveToFile("c:\\inetpub\\wwwroot\\anemometro.jpg");
    delete Bitmap1;

    Bitmap1 = new Graphics::TBitmap();
    Bitmap1->LoadFromFile("c:\\inetpub\\wwwroot\\temperatura.bmp");
    jp->Assign(Bitmap1);
    jp->SaveToFile("c:\\inetpub\\wwwroot\\temperatura.jpg");
    delete Bitmap1;

    Bitmap1 = new Graphics::TBitmap();
    Bitmap1->LoadFromFile("c:\\inetpub\\wwwroot\\pluviometria.bmp");
    jp->Assign(Bitmap1);
    jp->SaveToFile("c:\\inetpub\\wwwroot\\pluviometria.jpg");
    delete Bitmap1;

    Bitmap1 = new Graphics::TBitmap();
    Bitmap1->LoadFromFile("c:\\inetpub\\wwwroot\\lluvia_nubes.bmp");
    jp->Assign(Bitmap1);
    jp->SaveToFile("c:\\inetpub\\wwwroot\\lluvia_nubes.jpg");
    delete Bitmap1;

  }
  __finally
  {
    delete jp;
  }

 
    refres_jpg = 0;

  }  //fin de refres_jpg >5
  refres_jpg++;
}




//---------------------------------------------------------------------------
// ****** Timer de 3 sg  ********
// peticiones a la meteo.
// Abortar espera de foto
// Regular temperatura.
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{   // necesario que T2/T3 = entero
    char aux[300];
    static int TiempoLectura;
    static int Tem_Fijada_ccdA;
//peticion de informacion de meteo
  aux[0] = 4;   //mensaje al puerto auxiliar (D) del COR
  aux[1] = 0;
  strcpy(&aux[2],"(R)");
  S1->Escribir(aux, 3 + 2, S1->IPRabbit);


  if(CBonof->Checked== true)
    Timer4->Enabled = true;
  else Timer4->Enabled = false;


  // regular temperatura camara A
  if(CBregularT->Checked == true)
     RegularTccdA();

  //limites del periodo de refresco coordenadas telescopio
  PerRefrescoTel = atoi(PerRefresco->Text.c_str()); //limita refresco coordenadas
  if (PerRefrescoTel>10 || PerRefrescoTel <1)
   PerRefresco->Text = 1;

// Abortar epera de foto
  if((FinFoto == false)&&(nfotos>0))
  {
//    Mhistory->Lines->Add("nfotos " + AnsiString(nfotos) + "FotoActual  " + AnsiString(FotoActual));
    TiempoLectura = (CBCCD->ItemIndex + 1)*(CBCCD->ItemIndex + 1)*(32/(PBinin->Caption*PBinin->Caption));

//  if  (((::GetTickCount() - TiempoUltimoPaquete) > 2000) &&  atoi(TiempoPasado->Caption.c_str()) >  (atoi(Esg->Text.c_str())+5)  )
//  if  (((::GetTickCount() - TiempoUltimoPaquete) > 2000) &&  LeyendoFoto   )
    if( DogFoto >  (atoi(Esg->Text.c_str()) + TiempoLectura) )
    {
      Mhistory->Lines->Add("Agotada espera foto " + AnsiString(nfotos - 1));
      DogFoto = 0;
      LeyendoFoto = false;
      FinFoto = true;
//      FotoActual=1;
//      nfotos = 0;
      PFoto->BevelOuter = bvRaised;
      PFoto->Color = clSilver;
      SLedFoto->Brush->Color = clGray;
      Panel5->Enabled = true;
      PCancel->Visible = true;
      TiempoPasado->Caption = 0;
//      TNFotos->Caption = 1;
      PBF->Position = 0;
     //  Beep();
    }
        DogFoto = DogFoto+3;
  }
}




//---------------------------------------------------------------------------
// Timer de 100ms
// gestion mensajes de red con el cor.
// Coordenadas Telescopio
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer4Timer(TObject *Sender)
{
  char aux[300];
  char *punteroX;
  TJPEGImage *jp;
  static int EsperaLX;

//Gestion conexion Telescopio
  if((::GetTickCount() > (TimeRead + PerRefrescoTel*1000)) &&(LeyendoFoto == false))
  {
       TimeRead = ::GetTickCount();

       aux[0] = 2;
       aux[1] = 0;
       strncpy(&aux[2], ":GR#:GD#", 8);
     // strncpy(&aux[2], "#:GR#:GD#", 9);
       pedidaRaDe = true;
       segalm = false;    //intentar quitar
       nRa = nDe = 0;

       S1->LimpiarBufferLX200();
       S1->Escribir(aux, strlen(":GR#:GD#")+2, S1->IPRabbit);
       EsperaLX++;
  }
  // Vigilar conexion Telescopio
  if (EsperaLX > 2) // despues de 2 sg
  {
     EsperaLX = 0;
     if(LXresponde)
     {
       LXresponde = false;
       Form1->STPerdido->Caption = "CONECTADO";
       Form1->STRa->Caption = AnsiString(nRAHour) + AnsiString("h") + AnsiString(dRAMin)+ AnsiString("m");

       if(negativo == 0)
         Form1->STDe->Caption = AnsiString("+") + AnsiString(nDecDeg) + AnsiString("º") + AnsiString(nDecMin)+ AnsiString("'") ;
       else
          Form1->STDe->Caption = AnsiString("-") + AnsiString(nDecDeg) + AnsiString("º") + AnsiString(nDecMin)+ AnsiString("'") ;
       Form1->arecta->Caption = carecta;
       Form1->declinacion->Caption = cdeclinacion;
     }
     else STPerdido->Caption = "DESCONECTADO";
  }


  if(LeyendoFoto == false)
  {
    S1->ComprobarConexion(::GetTickCount());
  }
  else
  {
    TRabbit = ::GetTickCount();
    TiempoPasado->Alignment = taLeftJustify;
    TiempoPasado->Caption = (::GetTickCount() - TiempoInicio) / 1000;
  }

  PMax->Hint = AnsiString("X: ") + AnsiString(FotoPrincipal->xmax) + AnsiString("  ;Y: ") + AnsiString(FotoPrincipal->ymax);
  PMin->Hint = AnsiString("X: ") + AnsiString(FotoPrincipal->xmin) + AnsiString("  ;Y: ") + AnsiString(FotoPrincipal->ymin);
  PPerdidos->Caption = paquetesperdidos;
  PRABBIT->Caption = "    COR: " + AnsiString(S1->cadenaIPRabbit);

// Gestion conexion COR
  if(S1->PerdidaConexion == true)
  {
    EstadoRabbit = "    COR no responde";
    ColorEstado = clRed;
  }
  else
  {
    EstadoRabbit = AnsiString("    COR ") + AnsiString(S1->cadenaIPRabbit);
    ColorEstado = clLime;
    if(S1->nDatosRabbit >= 17)
    {
      S1->LeerRabbit(aux, 100);
      aux[18] = 0;
      Panel1->Caption = aux;
    }
    if(S1->nDatosCFS > 0)
    {
      ProcesarCFS();
    }
    if(S1->nDatosLX200 > 0)
    {
      ProcesarLX200();
    }
    if(S1->nDatosMeteo > 0)
    {
     ProcesarMeteo();
    }
    actualizar_datos(); // refresca la informacion del panel de control
  }

  EstadoAnterior = EstadoRabbit;
  PStatus->Font->Color = ColorEstado;
  SC->Brush->Color = ColorEstado;

}
//---------------------------------------------------------------------------




void HacerFoto( short x1, short y1, short x2, short y2, unsigned char binin,
                short seg, short mseg, short NumCol, short NumFil,
                unsigned char test, unsigned char cancel, short nfotos,
                short limpiado, short obturador, short retraso, WideString nombppp
              )
{
  char *ptr;
  char aux[300];

  LeyendoFoto = true;

  X1FS = x1;
  X2FS = x2;
  Y1FS = y1;
  Y2FS = y2;
  numeroLinea = 0;
  paquetesperdidos = 0;
  numeroOrdenAnterior = 0;
  if (Form1->CBSelCamara->ItemIndex == 0)
    aux[0] = 30;         //indica camra A
  else if (Form1->CBSelCamara->ItemIndex == 1)
    aux[0] = 32;         //indica camra B
  aux[1] = 0;
  *(WORD*)&aux[2] = NumCol;//NumeroColumnas;
  *(WORD*)&aux[4] = NumFil;//NumeroFilas;

  if(test != 0)
    *(BYTE*)&aux[6] = (char)binin + 10;
  else
    *(BYTE*)&aux[6] = (char)binin;

  *(WORD*)&aux[7] = (WORD)mseg;
  *(WORD*)&aux[9] = (WORD)seg;
  *(WORD*)&aux[11] = x1*binin;
  *(WORD*)&aux[13] = y1*binin;
  *(WORD*)&aux[15] = x2*binin;
  *(WORD*)&aux[17] = y2*binin;
  if(cancel != 0)
    *(BYTE*)&aux[19] = 1;
  else
    *(BYTE*)&aux[19] = 0;
  *(BYTE*)&aux[20] = limpiado;
  *(BYTE*)&aux[21] = obturador;
  *(BYTE*)&aux[22] = retraso;

  if (binin == 1)
    {
      *(BYTE*)&aux[23] = (BYTE)(sizeof(sec_1x1) / sizeof(char));
      memcpy(&aux[24],  sec_1x1, sizeof(sec_1x1));
    }
    else if(binin == 2)
    {
      *(BYTE*)&aux[23] = (BYTE)(sizeof(sec_2x2) / sizeof(char));
      memcpy(&aux[24],  sec_2x2, sizeof(sec_2x2));
    }
    else if(binin == 3)
    {
      *(BYTE*)&aux[23] = (BYTE)(sizeof(sec_3x3) / sizeof(char));
      memcpy(&aux[24],  sec_3x3, sizeof(sec_3x3));
    }
    else if(binin == 4)
    {
      *(BYTE*)&aux[23] = (BYTE)(sizeof(sec_4x4) / sizeof(char));
      memcpy(&aux[24],  sec_4x4, sizeof(sec_4x4));
    }

  *(BYTE*)&aux[88] = (BYTE)(sizeof(sec_limpiado) / sizeof(char));
  memcpy(&aux[89],  sec_limpiado, sizeof(sec_limpiado));

  *(BYTE*)&aux[153] = (BYTE)(sizeof(sec_vertical) / sizeof(char));
  memcpy(&aux[154],  sec_vertical, sizeof(sec_vertical));
  FinFoto = false;
  S1->Escribir(aux, 170, S1->IPRabbit);
//  FechaFoto = FechaFoto.CurrentDateTime();
//  FechaFoto += (7000.0 / (24.0 * 60.0 * 60.0 * 1000.0));
}




//---------------------------------------------------------------------------




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
  fitsfile *fptr;                          // pointer to the FITS file, defined in fitsio.h
  int status, nkeys, keypos, hdutype, ii, jj;
  char filename[FLEN_FILENAME];                // input FITS file
  char card[FLEN_CARD];                        // standard string lengths defined in fitsioc.h

  char aux[300];
  int ejes;
  long ajes[4];
  int tipo;

  if(OD1->Execute())
  {
    if((fptr = AbrirFoto(OD1->FileName.c_str())) == NULL)
      return;
  }
  else
    return;
/*
  if(ffgipr(fptr,  2, &tipo, &ejes, ajes, &status))
  {
    return ;
  }
  ejex = ajes[0];
  ejey = ajes[1];
  Memo1->Lines->Add("------");
  Memo1->Lines->Add("Tipo : " + AnsiString(tipo));
  Memo1->Lines->Add("EJES : " + AnsiString(ejes));
  Memo1->Lines->Add("AJES0: " + AnsiString(ajes[0]));
  Memo1->Lines->Add("AJES1: " + AnsiString(ajes[1]));
  Memo1->Lines->Add("HDU NUMBER: " + AnsiString(ii));
*/
    // attempt to move to next HDU, until we get an EOF error
  fits_get_hdu_num(fptr, &ii); // get the current HDU number
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
  Memo1->Lines->Clear();
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
    printf("END\n\n");  // terminate listing with END
  }
  if (status == END_OF_FILE)   // status values are defined in fitsio.h
    status = 0;              // got the expected EOF error; reset = 0
  else
  {
    printerror( status );     // got an unexpected error
    return;
  }
  status = 0;
  fits_close_file(fptr, &status);
}


void __fastcall TForm1::BGuardarClick(TObject *Sender)
{
  AnsiString N;

  if(SD1->Execute())
  {
    if(!SD1->FileName.AnsiPos(".fit") && !SD1->FileName.AnsiPos(".FIT"))
      N = SD1->FileName + ".fit";
    else
      N = SD1->FileName;

    if(FileExists(N))
    {
      if(Application->MessageBox("El Fichero ya existe. ¿Sobrescribir?", "OJO", MB_OKCANCEL	) == IDOK	)
      {
        DeleteFile(N);
      }
    }

    GuardarFoto(N.c_str());
  }
  else
    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TBx0Change(TObject *Sender)
{
  double x, y;

  x = TBx0->Position;
  y = TBy0->Position;

  if(y != x)
  {
    x0 = (-255.0 * x)/ (y - x);
    y0 = 255.0 / (y - x);
  }
  else
  {
    x0 = 0.0;
    y0 = 1.0;
  }


  Ex0->Text = TBx0->Position;
  Ey0->Text = TBy0->Position;
  if(FActivo != NULL)
  {
    FActivo->Foto->xm0 = x0;
    FActivo->Foto->ym0 = y0;
    FActivo->Pintar();
  }
  else
  {
    FotoPrincipal->xm0 = x0;
    FotoPrincipal->ym0 = y0;
    RellenarBitmap(X1F, Y1F, X2F, Y2F);
  }
      // RellenarBitmap(X1F, Y1F, X2F, Y2F);
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
    LeyendoFoto = false;
    FinFoto = true;
    FotoActual=1;
    nfotos = 0;
    PFoto->BevelOuter = bvRaised;
    PFoto->Color = clSilver;
    SLedFoto->Brush->Color = clGray;
    Panel5->Enabled = true;
    ((TPanel*)Sender)->BevelOuter = bvRaised;
    TiempoPasado->Caption = 0;
    TNFotos->Caption = 1;
    PBF->Position = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PB1Paint(TObject *Sender)
{
  RellenarBitmap(0, 0, FotoPrincipal->BM->Width, FotoPrincipal->BM->Height);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RBHClick(TObject *Sender)
{
    Lupa(celdaX, celdaY, FotoPrincipal, true);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CBCCDChange(TObject *Sender)
{
  if(CBSelCamara->ItemIndex == 0)
    Binin = 2;
    else   Binin = 1;
  NumeroFilas = CCDs[CBCCD->ItemIndex].FilasFisicas / Binin;
  NumeroColumnas = CCDs[CBCCD->ItemIndex].ColumnasFisicas / Binin;
  Y1F =  CCDs[CBCCD->ItemIndex].FilaInicio / Binin;;
  X1F = CCDs[CBCCD->ItemIndex].ColumnaInicio / Binin;;
  Y2F =  CCDs[CBCCD->ItemIndex].FilaFin / Binin;;
  X2F = CCDs[CBCCD->ItemIndex].ColumnaFin / Binin;;
  PX1->Caption = X1F;
  PY1->Caption = Y1F;
  PX2->Caption = X2F;
  PY2->Caption = Y2F;
  PFil->Caption = NumeroFilas;
  PCol->Caption = NumeroColumnas;
  PB1->Width = NumeroColumnas;
  PB1->Height = NumeroFilas;
//  Binin = 2;
  PBinin->Caption = (int)Binin;
  TBBinin->Position = (int)Binin;
  PBF->Position = 0;
  FotoPrincipal->Resizear(NumeroColumnas, NumeroFilas);
  RellenarBitmap(0, 0, NumeroColumnas, NumeroFilas);

  EFilaInicio->Text = CCDs[CBCCD->ItemIndex].FilaInicio;// / Binin;
  EFilaFin->Text = CCDs[CBCCD->ItemIndex].FilaFin;// / Binin;
  EColumnaInicio->Text = CCDs[CBCCD->ItemIndex].ColumnaInicio;// / Binin;
  EColumnaFin->Text = CCDs[CBCCD->ItemIndex].ColumnaFin;// / Binin;

}
//---------------------------------------------------------------------------
     //IFoto->Picture->Bitmap->LoadFromResourceName((int)HInstance,"CLICK");

void __fastcall TForm1::CBGuardarClick(TObject *Sender)
{
  if(((TCheckBox*)Sender)->State == cbChecked)
  {
    ENombreFichero->Enabled = true;
  }
  else
  {
   // ENombreFichero->Enabled = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EFilaFinChange(TObject *Sender)
{
/*
  if(EFU->Text.ToInt() > CCDs[CBCCD->ItemIndex].FilasFisicas)
     EFU->Text = CCDs[CBCCD->ItemIndex].FilasFisicas;
  CCDs[CBCCD->ItemIndex].FilasUtiles = EFU->Text.ToInt();
  NumeroColumnas = ECU->Text.ToInt() / Binin;
  NumeroFilas = EFU->Text.ToInt() / Binin;
  offsetx = (CCDs[CBCCD->ItemIndex].ColumnasFisicas - CCDs[CBCCD->ItemIndex].ColumnasUtiles)/2;
  offsety = (CCDs[CBCCD->ItemIndex].FilasFisicas - CCDs[CBCCD->ItemIndex].FilasUtiles)/2;
  if(CBR->State == cbUnchecked)
  {
    PX1->Caption = 0;
    PX2->Caption = ECU->Text;
    PY1->Caption = 0;
    PY2->Caption = EFU->Text;
  }
*/  
}
//---------------------------------------------------------------------------



//--------------Envia orden de moverse al motor de enfoque ------------------
void MueveEnfoque()
{
  char aux[300];
  DWORD Tms;
  AnsiString A;

  aux[0] = 3;   //mensaje al CFS
  aux[1] = 0;
  essubir =1;
  FinX = 0;

  A = AnsiString("<x") +
                Form1->MEPasosEnfoque->EditText +
                AnsiString("-") +
                Form1->MEVelocidadEnfoque->EditText +
                AnsiString(">");
  strcpy(&aux[2], A.c_str());

  S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);

  Tms = ::GetTickCount();

  cuenta[1]= aux[4];
  cuenta[2]= aux[5];
  cuenta[3]= aux[6];
  cuenta[4]= aux[7];
  cuenta[5]= aux[8];
  cuenta[6]= 0;

  while (::GetTickCount() <= (Tms +100)) // para dar tiempo al cfs
  ;
  strcpy(&aux[2], "<xo>");
  S1->Escribir(aux, strlen("<xo>") + 2, S1->IPRabbit);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::subirClick(TObject *Sender)
{
  if (FinX==1)
    MueveEnfoque();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::bajarClick(TObject *Sender)
{
  char aux[300];
  DWORD Tms;
  AnsiString A;

  if (FinX==1)
  {
     Tms = ::GetTickCount();
     aux[0] = 3;   //mensaje al CFS
     aux[1] = 0;
     esbajar =1;
     FinX = 0;

     A = AnsiString("<x") +
                MEPasosEnfoque->EditText +
                AnsiString("+") +
                MEVelocidadEnfoque->EditText +
                AnsiString(">");
     strcpy(&aux[2], A.c_str());

     S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);

     cuenta[1]= aux[4];
     cuenta[2]= aux[5];
     cuenta[3]= aux[6];
     cuenta[4]= aux[7];
     cuenta[5]= aux[8];
     cuenta[6]= 0;

     while (::GetTickCount() <= (Tms +100))
     ;

     strcpy(&aux[2], "<xo>");
     S1->Escribir(aux, strlen("<xo>") + 2, S1->IPRabbit);
  }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::BResetFocoClick(TObject *Sender)
{
  char aux[300];

  aux[0] = 3;   //mensaje al CFS
  aux[1] = 0;

  strcpy(&aux[2], "<tf>");
  S1->Escribir(aux, strlen("<tf>") + 2, S1->IPRabbit);

  FinX = 1;

}


//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 char aux[300];

  aux[0] = 3;   //mensaje al CFS
  aux[1] = 0;

  strcpy(&aux[2], "<xf>");
  S1->Escribir(aux, strlen("<xf>") + 2, S1->IPRabbit);

  FinX = 1;
}
//---------------------------------------------------------------------------




void Lupa(int X, int Y, cFoto *Foto, bool actualizar)
{
  float auxf;
  char aux[300];
  TRect R, R2;
  int cx, cy;

  celdaX = X - 3;
  celdaY = Y - 3;

  for(int c1 = 0; c1 < 7; c1++)
  {
    for(int c2 = 0; c2 < 7; c2++)
    {
      R = Form1->DG1->CellRect(c2,c1);
      R2 = Form1->DG2->CellRect(c2,c1);
      cx = X - 3 + c2;
      cy = Y - 3 + c1;
      if((cx == X) && (cy == Y))
        Form1->DG1->Canvas->Font->Color = clRed;
      else
        Form1->DG1->Canvas->Font->Color = clBlack;
      if(actualizar == true)
      {
        Form1->DG2->Canvas->Brush->Color = Colores[c1][c2];
        Form1->DG2->Canvas->FillRect(R2);
        if(Form1->RBH->Checked == true)
          wsprintf(aux, "%04X", Valores[c1][c2]);
        else
          wsprintf(aux, "%05u", Valores[c1][c2]);
        Form1->DG1->Canvas->TextRect(R, R.left + 1, R.top+1, aux);
      }
      else
      {
        if((cx >= 0) && (cx < Foto->BM->Width) && (cy >= 0) && (cy < Foto->BM->Height))
        {
          Valores[c1][c2] = Foto->Pixeles[cy * Foto->BM->Width + cx];
          auxf = Foto->xm0 + Valores[c1][c2] * Foto->ym0;
          if(auxf >= 256)
            Form1->DG2->Canvas->Brush->Color = (TColor)0x00FFFFFF;
          else
            Form1->DG2->Canvas->Brush->Color = (TColor)(0x00000000 | ((ULONG)auxf)&0x000000FF |
                                                              (((ULONG)auxf) << 8)&0x0000FF00 |
                                                              (((ULONG)auxf) << 16)&0x00FF0000);
          if(Form1->RBH->Checked == true)
            wsprintf(aux, "%04X", Valores[c1][c2]);
          else
            wsprintf(aux, "%05u", Valores[c1][c2]);
          Form1->DG1->Canvas->TextRect(R, R.left + 1, R.top+1, aux);
        }
        else
        {
          strcpy(aux, " ");
          Form1->DG2->Canvas->Brush->Color = (TColor)0x00000000;
          Valores[c1][c2] = 0;
        }
        Form1->DG1->Canvas->TextRect(R, R.left + 1, R.top+1, aux);
        Form1->DG2->Canvas->FillRect(R2);
        Colores[c1][c2] = Form1->DG2->Canvas->Brush->Color;
      }
    }
  }
}




void __fastcall TForm1::PB1Click(TObject *Sender)
{
  FActivo = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BFlipxClick(TObject *Sender)
{
  if(FActivo != NULL)
  {
    FActivo->Foto->flipx();
    FActivo->Pintar();

  }
  else if(LeyendoFoto == false)
  {
    FotoPrincipal->flipx();
    RellenarBitmap(0, 0, NumeroColumnas, NumeroFilas);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DG2DrawCell(TObject *Sender, int ACol, int ARow,
      TRect &Rect, TGridDrawState State)
{
  Lupa(celdaX, celdaY, FotoPrincipal, true);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::BFlipyClick(TObject *Sender)
{
  if(FActivo != NULL)
  {
    FActivo->Foto->flipy();
    FActivo->Pintar();
  }
  else if(LeyendoFoto == false)
  {
    FotoPrincipal->flipy();
    RellenarBitmap(0, 0, NumeroColumnas, NumeroFilas);
  }
}
//---------------------------------------------------------------------------
/*
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   char aux[300];

  aux[0] = 4;   //mensaje al puerto auxiliar (D) del COR
  aux[1] = 0;

  strcpy(&aux[2], ESendMeteo->Text.c_str());
   S1->Escribir(aux, 1 + 2, S1->IPRabbit);
   //strcpy(&aux[], Form1->IntervaloT2->Text.c_str());
  Form1->Timer2->Interval = (Form1->IntervaloT2->Text.ToInt()*1000);
}
//---------------------------------------------------------------------------
 */


void __fastcall TForm1::BClearHistoryClick(TObject *Sender)
{
Mhistory->Lines->Clear();
}
//---------------------------------------------------------------------------

/*
void kk(int teta)
{
  teta = teta + 1;
  Form1->Mhistory->Lines->Add("test = " + Form1->PTcaja->Caption + teta);
}
  */

/********    Actualiza la barra de horas ********/
void barra_horas(void)
{
}


fitsfile * AbrirFoto(char *nombre)
{
  TForm2 *Form2;
  long primer_elemento = 1;
  long numelem;
  int cualquiernull = 0;
  Byte *ptr;
  short sust = 0;
  long ajes[4] = {0,0,0,0};
  int ejex, ejey;
  fitsfile *fptr = 0;       // pointer to the FITS file, defined in fitsio.h
  int status;

  int ejes = 0;
  int tipo;
  Form1->PFicheroAbierto->Caption = nombre;
  status = 0;
  if ( fits_open_file(&fptr, nombre, READWRITE, &status) )
  {
     return NULL;
  }
  status = 0;
  if(ffgipr(fptr,  2, &tipo, &ejes, ajes, &status))
  {
    return NULL;
  }
  ejex = ajes[0];
  ejey = ajes[1];
  numelem = ejex*ejey;
  Form2 = new TForm2(Form1->PFotoO);
  Form2->Caption = nombre;
  Form2->Crear(ejex, ejey);
  status = 0;

  if(fits_read_img(fptr, TSHORT, primer_elemento, numelem,
                   &sust, //valor por el que se sustituira los indefinidos
                   Form2->Foto->Pixeles,
                   &cualquiernull, // 1 si hay alguna sustitucion
                   &status))
  {
  }

  //Form2->Foto->flipy();
  long media =  Form2->Foto->media();  //Una vez abierta la imagen se calcula la media.

  double x, y, x0, y0;

  x = Form2->Foto->fondocielo - 100;
  y = Form2->Foto->fondocielo + 300;

  if(y != x)
  {
    x0 = (-255.0 * x)/ (y - x);
    y0 = 255.0 / (y - x);
  }
  else
  {
    x0 = 0.0;
    y0 = 1.0;
  }

  Form2->Foto->xm0 = x0;
  Form2->Foto->ym0 = y0;
  Form2->Pintar();
  Form2->Show();
 /*
  int ancho, alto;
  ancho = ejex;//Form2->Foto->BM->Width;
  alto = ejey;//Form2->Foto->BM->Height;
  Form1->Mhistory->Lines->Add("ejeX = " + AnsiString(ejex) + " ejeY = " + AnsiString(ejey));
 */

 // AF_SetLogLevel(AF_LOG_DEBUG);  /* subimos el nivel de log por defecto */

 ACOR_SetImage((short*)Form2->Foto->Pixeles, Form2->Foto->BM->Width, Form2->Foto->BM->Height);

  float hfd;
  int result = AF_HFD(&hfd);

  // No se puede pedir el centroide sin haber llamado a AF_HFD primero

  float xc,yc;
  AF_GetCentroid(&xc, &yc);
   Form1->Mhistory->Lines->Add("Centroid: X =" + AnsiString(xc) + " Y =" + AnsiString(yc));
   Form1->Mhistory->Lines->Add("hfd =" + AnsiString(hfd));
   Form1->Mhistory->Lines->Add("res AF_HFD =" + AnsiString(result));
   //Form2->Edit2->Text = Form2->Foto->fullhalfwide(); //clave llamada a la funcion cuando se abre un fichero
  return fptr;
}

/* Funcioncilla auxiliar para reconvertir coordenadas
AR para que las lea Astrometrica de la cabecera FITS */
AnsiString ReconvShortAR(AnsiString arin)
{    
int res, myhh, myintmin, myfracmin, mysec;
char buf[16];

  res = sscanf(arin.c_str(), "%dh%d,%d", &myhh,&myintmin,&myfracmin);
  if(res == 2)
    myfracmin = 0;

  mysec = myfracmin * 6;
  sprintf(buf,"%02d:%02d:%02d",myhh, myintmin, mysec);
  return(AnsiString(buf));
}



/* FUNCION MODIFICADA POR RAFA (17/10/2004) */
/* La metainformación se graba como FITS keywords siguiendo el "Amateur
FITS Standard v1.0, del 19 de Marzo de 2003 en lo que me ha parecido conveniente */

/* ATENCION: El comporamiento de la CFITSIO de la NASA es que si se incluyen
en la cabecera  BZERO y BSCALE, la grabación de los datos de la imagen se realiza
con un reescalado previo. En nuestro caso BSCALE=1.0 y BZERO=0.0, esto es una
absoluta perdida de tiempo. Por ello no se incluyen en la cabecera y en este
sentido no siguen el Amateur FITS Standard */

void GuardarFoto(char* nombre)
{
  fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */
  int status;
  int ejexg, ejeyg;
  //AnsiString NC;
  ejexg = X2F-X1F;
  ejeyg = Y2F-Y1F;
  long npixel = (X2F-X1F)*(Y2F-Y1F);// - 1;

  status = 0;

  Form1->Mhistory->Lines->Add(nombre);
//  Form1->Mhistory->Lines->Add("----------");

  if(fits_create_file(&fptr, nombre, &status))
  {
    status = 0;
    if ( fits_open_file(&fptr, nombre, READWRITE, &status) )
    {
      Form1->Mhistory->Lines->Add("Fallo en GuardarFoto");
     return;
    }
  }
  long axes[2];
  axes[0] = ejexg;
  axes[1] = ejeyg;
  if(fits_create_img(fptr, SHORT_IMG, 2, axes, &status))
  {
    Application->MessageBox("Error creando imagen", "Alert!", MB_OK);
    return;
  }

  unsigned short *datos;
  datos = new unsigned short [npixel+1];
  memset(datos, 0, npixel*2);

  // controla como se guarda la imagen, flip vertical - horizontal
  if (Form1->CBFlipVertical->State == cbChecked)
  {
    for(int py = Y1F; py <= Y2F-1; py++)
    {
      if (Form1->CBFlipHorizontal->State == cbChecked)
        for (int px = X1F; px < X2F; px++)      //haria un flip horizontal
          datos[npixel--] = FotoPrincipal->Pixeles[py * FotoPrincipal->BM->Width + px];
      else
        for (int px = (X2F-1); px >= X1F; px--)
          datos[npixel--] = FotoPrincipal->Pixeles[py * FotoPrincipal->BM->Width + px];
    }
  }
  else
  {
    for(int py = Y2F-1; py >= Y1F; py--)
    {
      if (Form1->CBFlipHorizontal->State == cbChecked)
        for (int px = X1F; px < X2F; px++)      //haria un flip horizontal
          datos[npixel--] = FotoPrincipal->Pixeles[py * FotoPrincipal->BM->Width + px];
      else
        for (int px = (X2F-1); px >= X1F; px--)
          datos[npixel--] = FotoPrincipal->Pixeles[py * FotoPrincipal->BM->Width + px];
    }
  }

  status = 0;
  char aux1[100];
  char fitserrmsg[32];
  AnsiString A;

  /* CRISTOBAL: Aqui tienes un bug. Al utilizar el caracter º para los grados
  de tu localidad, a esta librería FITS no le gustan esos caracteres y da un
  error de "caracter ilegal" y status <>0,
  por lo que no se graba esta keyword */

  fits_write_key(fptr, TSTRING, "LOCATION", Form1->ELocation->Text.c_str(), NULL, &status);
  status = 0;  /* quitar cuando se corrija el error comentado */

  /* Estas keywords estan vacias a la espera de poner cajas de texto para
  introducir datos */

  fits_write_key(fptr, TSTRING, "SITELONG",  Form1->ELongitud->Text.c_str() , "Site Longitude",&status);
  fits_write_key(fptr, TSTRING, "SITELAT", Form1->ELatitud->Text.c_str() , "Site Latitude",&status);

  /* Las valores definidos por el Amateur FITS standard para IMAGETYP son:
  Light Frame para los objetos de interes
  Dark Frame
  Bias Frame
  Flat Field
  Habría que poner el valor adecuado a la keyword cuando se selecciona el tipo
  de imagen con los radiobuttons. Ahora va a piñon fijo.
  */
  // fits_write_key(fptr, TSTRING, "IMAGETYP", "Light Frame" , "image type (dark, flat, bias, object)",&status);

  /* Los valores de TELESCOP, INSTRUME, APTDIA y  deberían ser metidos
  por el usuario en cajas de texto . La apertura efectiva APTDIA debería
  calcularse quitando la obstrucción central. Por ahora va con valor absurdo */

  float aptdiam = 203;
  float aptarea = 0;

  fits_write_key(fptr, TSTRING, "OBSERVER", Form1->EObserver->Text.c_str(), NULL, &status);
  fits_write_key(fptr, TSTRING, "TELESCOP", Form1->ETelescop->Text.c_str(), NULL, &status);

  fits_write_key(fptr, TSTRING, "FOCALLEN", Form1->EFocal->Text.c_str(), "Distancia focal", &status);
  fits_write_key_unit(fptr, "FOCALLEN", "mm", &status);

  fits_write_key(fptr, TSTRING, "APTDIA", Form1->EApert->Text.c_str(), "Apertura", &status);
  fits_write_key_unit(fptr, "APTDIA", "mm", &status);

//  fits_write_key(fptr, TSTRING, "APTAREA", &aptarea, "Effective collecting area", &status);
//  fits_write_key_unit(fptr, "APTAREA", "mm^2", &status);

  float pixsz = 9*Binin;  /* valido para x e y */

  fits_write_key(fptr, TSTRING, "INSTRUME", Form1->EInstrument->Text.c_str(), NULL, &status);
  fits_write_key(fptr, TFLOAT, "XPIXSZ", &pixsz, "Effective pixel width", &status);
  fits_write_key_unit(fptr, "XPIXSZ", "um", &status);
  fits_write_key(fptr, TFLOAT, "YPIXSZ", &pixsz, "Effective pixel height", &status);
  fits_write_key_unit(fptr, "YPIXSZ", "um", &status);
  fits_write_key(fptr, TBYTE, "XBINNING", &Binin, Form1->PBinin->Caption.c_str(), &status);
  fits_write_key(fptr, TBYTE, "YBINNING", &Binin, "Binning factor in height", &status);

  float temperatura[3];
  if(Form1->PTccd->Caption == "---")
	  temperatura[0] = 9999.0;
  else
    temperatura[0] = StrToFloat(Form1->PTccd->Caption);

  if(Form1->PTcaja->Caption == "---")
	  temperatura[1] = 9999.0;
  else
    temperatura[1] = StrToFloat(Form1->PTcaja->Caption);

  if(Form1->PVpeltier->Caption == "---")
    	temperatura[2] = 9999.0;
  else
     temperatura[2] = StrToFloat(Form1->PVpeltier->Caption);

  fits_write_key(fptr, TFLOAT, "CCD-TEMP", &temperatura[0] , "CCD temp. when exposure finished",&status);
  fits_write_key_unit(fptr, "CCD-TEMP", "C", &status);

  fits_write_key(fptr, TFLOAT, "AMB-TEMP", &temperatura[1] , "Ambient temp. when exposure finished",&status);
  fits_write_key_unit(fptr, "AMB-TEMP", "C", &status);

  fits_write_key(fptr, TFLOAT, "VOLTPELT", &temperatura[2] , "Peltier voltage when exposure finished",&status);
  fits_write_key_unit(fptr, "VOLTPELT", "V", &status);

  fits_write_key(fptr, TSTRING, "OBJECT", Form1->EObjeto->Text.c_str(), "Object name", &status);
  if(status) {
     fits_get_errstatus(status, fitserrmsg);
    Application->MessageBox(fitserrmsg, "ERROR fit!", MB_OK);
  }


  if (Form1->STPerdido->Caption == "CONECTADO")
  {
    AnsiString dec = Form1->STDe->Caption;
    int ps;

    if((ps = dec.Pos("º")) != 0)
    dec[ps] = ':';
    if((ps = dec.Pos("'")) != 0)
    dec[ps] = ':';
    dec += AnsiString("00");
    AnsiString ar = ReconvShortAR( Form1->STRa->Caption );
    fits_write_key(fptr, TSTRING, "OBJCTRA",  ar.c_str() , "Aproximate image center",&status);
    fits_write_key(fptr, TSTRING, "OBJCTDEC", dec.c_str() , "Aproximate image center",&status);
  }

  DateSeparator = '-';
//  FechaFoto_fin =  FechaFoto_fin.CurrentDateTime();
//  FechaFoto_fin -= ((A_T_Fin_Lect - A_T_Ini_Exp) / (24.0 * 60.0 * 60.0 * 1000.0));
  FechaFoto_fin = FechaFoto -( ((A_T_Fin_Lect - A_T_Ini_Exp) / (24.0 * 60.0 * 60.0 * 1000.0)));
 //  FechaFoto += (7000.0 / (24.0 * 60.0 * 60.0 * 1000.0));
  fits_write_key(fptr, TSTRING, "DATE-OBS", FechaFoto_fin.FormatString("yyyy/mm/dd'T'hh:mm:ss").c_str(), "Exposure starts, Local Time", &status);


  float exptime; //= atof(Form1->Esg->Text.c_str()) + atof(Form1->Emsg->Text.c_str())/1000 + float(Form1->ERetraso->Text.ToInt())/10;
  float darktime;// = exptime;
  exptime = (A_T_Ini_Lect - A_T_Ini_Exp)/1000.0;
//  darktime =  A_T_Fin_Lect - A_T_Ini_Lect + atoi(Form1->ERetraso->Text.c_str()) *100;
  darktime =  A_T_Fin_Lect - A_T_Ini_Exp;
  darktime =  darktime /1000.0 ;

  fits_write_key(fptr, TFLOAT, "EXPTIME", &exptime , "Exposure time",&status);
  fits_write_key_unit(fptr, "EXPTIME", "sg", &status);

  fits_write_key(fptr, TFLOAT, "DARKTIME", &darktime , "Exposure time + readout time",&status);
  fits_write_key_unit(fptr, "DARKTIME", "sg", &status);

  fits_write_date(fptr, &status);  /* fecha de creacion del fichero */

    fits_write_comment (fptr, Form1->EComent->Text.c_str(), &status);

  fits_write_img(fptr, TSHORT, 1, ejexg*ejeyg, datos, &status);
  fits_close_file(fptr, &status);
  delete datos;
  return;
}







/****************FUNCIONES LX200 *******************/
/****************FUNCIONES LX200 *******************/
/****************FUNCIONES LX200 *******************/

void __fastcall TForm1::BstopClick(TObject *Sender)
{
 char aux[300];

 aux[0] = 2;   //mensaje al LX200
 aux[1] = 0;

  BN->Down = false;
  BS->Down = false;
  BE->Down = false;
  BO->Down = false;
 strcpy(&aux[2], "#:Q#");
 S1->Escribir(aux, strlen("#:Q#") + 2, S1->IPRabbit);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBSincronizarClick(TObject *Sender)
{
        if(CBSincronizar->State == cbUnchecked)
        {
                Sincronizando = false;
               // BSincronizar->Enabled = false;
        }
        else if(CBSincronizar->State == cbChecked)
        {
                Sincronizando = true;
             //   BSincronizar->Enabled = true;
        }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::BOClick(TObject *Sender)
{

if(((TSpeedButton*)Sender)->Down == true)
  ((TSpeedButton*)Sender)->Down = false;
else
  ((TSpeedButton*)Sender)->Down = true;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::BSMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  char aux[300];

  aux[0] = 2;   //mensaje al LX200
  aux[1] = 0;

  if(BSLW->Down == true)
  {
   strcpy(&aux[2], "#:RS#");
  }
  else if(BMOV->Down == true)
  {
    strcpy(&aux[2], "#:RM#");
  }
  else if(BCEN->Down == true)
  {
    strcpy(&aux[2], "#:RC#");
  }
  else if(BGUI->Down == true)
  {
    strcpy(&aux[2], "#:RG#");
  }
  S1->Escribir(aux, strlen("#:RC#") + 2, S1->IPRabbit);

  if(Sender == BN)
  {
        strcpy(&aux[2], "#:Mn#");
        S1->Escribir(aux, strlen("#:Mn#") + 2, S1->IPRabbit);
  }
  else if(Sender == BNO)
  {
        strcpy(&aux[2], "#:Mn##:Me#");
        S1->Escribir(aux, strlen("#:Mn##:Me#") + 2, S1->IPRabbit);
  }
    else if(Sender == BO)
  {
        strcpy(&aux[2], "#:Mw#");
        S1->Escribir(aux, strlen("#:Mw#") + 2, S1->IPRabbit);
  }
  else if(Sender == BSO)
  {
        strcpy(&aux[2], "#:Mw##:Ms#");
        S1->Escribir(aux, strlen("#:Mw##:Ms#") + 2, S1->IPRabbit);
  }
  else if(Sender == BS)
  {
        strcpy(&aux[2], "#:Ms#");
        S1->Escribir(aux, strlen("#:Ms#") + 2, S1->IPRabbit);
  }
  else if(Sender == BSE)
  {
        strcpy(&aux[2], "#:Ms##:Me#");
        S1->Escribir(aux, strlen("#:Me##:Ms#") + 2, S1->IPRabbit);
  }
  else if(Sender == BE)
  {
        strcpy(&aux[2], "#:Me#");
        S1->Escribir(aux, strlen("#:Me#") + 2, S1->IPRabbit);
  }
  else if(Sender == BNE)
  {
        strcpy(&aux[2], "#:Mn##:Me#");
        S1->Escribir(aux, strlen("#:Me##:Ms#") + 2, S1->IPRabbit);
  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BNOMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  char aux[300];

  aux[0] = 2;   //mensaje al LX200
  aux[1] = 0;
  if(Sender == BN)
  {
    strcpy(&aux[2], "#:Qn#");
    S1->Escribir(aux, strlen("#:Qn#") + 2, S1->IPRabbit);
  }
  else if(Sender == BNO)
  {
    strcpy(&aux[2], "#:Qn##:Qw#");
    S1->Escribir(aux, strlen("#:Qn##:Qw#") + 2, S1->IPRabbit);
  }
  else if(Sender == BO)
  {
    strcpy(&aux[2], "#:Qw#");
    S1->Escribir(aux, strlen("#:Qw#") + 2, S1->IPRabbit);
  }
  else if(Sender == BSO)
  {
    strcpy(&aux[2], "#:Qs##:Qw#");
    S1->Escribir(aux, strlen("#:Qs##:Qw#") + 2, S1->IPRabbit);
  }
  else if(Sender == BS)
  {
    strcpy(&aux[2], "#:Qs#");
    S1->Escribir(aux, strlen("#:Qn#") + 2, S1->IPRabbit);
  }
  else if(Sender == BSE)
  {
    strcpy(&aux[2], "#:Qs##:Qe#");
    S1->Escribir(aux, strlen("#:Qs##:Qe#") + 2, S1->IPRabbit);
  }
  else if(Sender == BE)
  {
    strcpy(&aux[2], "#:Qe#");
    S1->Escribir(aux, strlen("#:Qe#") + 2, S1->IPRabbit);
  }
  else if(Sender == BNE)
  {
    strcpy(&aux[2], "#:Qn##:Qe#");
    S1->Escribir(aux, strlen("#:Qn##:Qe#") + 2, S1->IPRabbit);
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::StaticText1Click(TObject *Sender)
{
        if(StaticText1->Caption == "+")
          StaticText1->Caption = "-" ;
        else
          StaticText1->Caption = "+";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
  char aux[300];
  AnsiString A;
  aux[0] = 2;   //mensaje al LX200
  aux[1] = 0;

        A = AnsiString("#:Sr ") +
                      EHra->EditText +
                      AnsiString(":") +
                      EMra->EditText +
                      AnsiString("#") +
                      AnsiString("#:Sd ") +
                      StaticText1->Caption +
                      EDdec->EditText +
                      AnsiString((char)0xDF)+
                      EMdec->EditText +
                      AnsiString("##:MS#") ;
        strcpy(&aux[2], A.c_str());
    S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);
}
//---------------------------------------------------------------------------


void GetRaDe_F(double *Ra, double *De)
{
/*
  char aux[300];

  aux[0] = 2;
  strncpy(&aux[2], "#:GR#:GD#", 9);
  if(S1 != NULL)
    S1->Escribir(aux, strlen(&aux[2])+2, IPRabbit);
*/
  *Ra = tRa;    //son los valores recibidos en ProcesarLX200
  *De = tDe;
}


void Slew_F(char *comando)
{
	int HoraSlew;							// RA, hours
	double dRAMin;							// RA, minutes
	int nDecDeg;							// declination, degrees
	int nDecMin;							// declination, minutes
	char cSign;								// declination sign
  char aux[300], auxi[10];

  strncpy(&aux[2], comando, 15);
  strncpy(carecta, comando, 7);
  carecta[7] = 0;
  strncpy(cdeclinacion, &comando[7], 6);
  cdeclinacion[6] = 0;
  aux[0] = 2;
  aux[1] = 0;

  strncpy(auxi, carecta, 2);
  HoraSlew = atoi(auxi);
  strncpy(auxi, &carecta[3], 4);
  dRAMin = atof(auxi);
  strncpy(auxi, &cdeclinacion[1], 2);
  nDecDeg = atoi(auxi);
  strncpy(auxi, &cdeclinacion[4], 2);
  nDecMin = atoi(auxi);
  cSign = cdeclinacion[0];
 	sprintf( &aux[2], ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d##:MS#",
     	     HoraSlew, dRAMin, cSign, nDecDeg, nDecMin );

	sprintf( carecta, "%02dh%04.1lfm", HoraSlew, dRAMin);
	sprintf( cdeclinacion, "%c%02dº%02d'", cSign, nDecDeg, nDecMin );

//  Form1->Edit1->Text = &aux[2];
  if(S1 != NULL)
    S1->Escribir(aux, strlen(&aux[2])+2, S1->IPRabbit);
}


void Slew_F(double dRA, double dDec)
{
        char *ptr;
        char aux[300];

	double dValue;							// temporary storage
	int HoraSlew;							// RA, hours
	double dRAMin;							// RA, minutes
	int nDecDeg;							// declination, degrees
	int nDecMin;							// declination, minutes
	char cSign;								// declination sign
	char szCommand[128];					// command string

	// Set up the command string to set the telescope's slew target as
	// the specified RA/Dec coordinates.

	dValue = dRA/15.0 + 1/1200.0;
	HoraSlew = int(dValue);
	dRAMin = (dValue - HoraSlew)*60.0;

	dValue = dDec;
	if (dValue<0.0)
	{
	    dValue = -dValue;
	    cSign = '-';
	}
	else
            cSign = '+';

	dValue += 1/120.0;
	nDecDeg = int(dValue);
	nDecMin = int((dValue - nDecDeg)*60.0);

        if(Sincronizando == true)
        {
         //sprintf( &aux[2], ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#",
           sprintf( &aux[2], ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:CM#",
	            HoraSlew, dRAMin, cSign, nDecDeg, nDecMin );
          // Form1->CBSincronizar->State = cbUnchecked;
           Sincronizando = false;
           Form1->CBSincronizar->State = cbUnchecked;
          // Form1->BSincronizar->Enabled = false;
        }
        else
           sprintf( &aux[2], ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:MS#",
	      	     HoraSlew, dRAMin, cSign, nDecDeg, nDecMin );

        sprintf(carecta, "%02dh%04.1lfm", HoraSlew, dRAMin);
        sprintf(cdeclinacion, "%c%02dº%02d'", cSign, nDecDeg, nDecMin );

        aux[0] = 2;
        aux[1] = 0;
        if(S1 != NULL)
        S1->Escribir(aux, strlen(&aux[2])+2, S1->IPRabbit);
}



void __fastcall TForm1::BSincronizarClick(TObject *Sender)
{
 char aux[300];
 AnsiString aa; // = "#";

 aux[0] = 2;   //mensaje al LX200
 aux[1] = 0;

// aa += arecta->Caption;
/* aa = arecta->Caption;
 strcpy(&aux[2], aa.c_str());

 S1->Escribir(aux, strlen(aa.c_str()) + 2, S1->IPRabbit);

 aa = "#" +  declinacion->Caption;
 strcpy(&aux[2], aa.c_str());
 S1->Escribir(aux, strlen(aa.c_str()) + 2, S1->IPRabbit);

 strcpy(&aux[2], "#:CM#");
 S1->Escribir(aux, strlen("#:CM#") + 2, S1->IPRabbit);

 CBSincronizar->State = cbUnchecked;
 Sincronizando = false;
 BSincronizar->Enabled = false;
*/
}
//---------------------------------------------------------------------------



void __fastcall TForm1::BElbrusClick(TObject *Sender)
{
FILE *in;
char aqui[200], cad[60], aux[60];
//int entero_dec, frac_dec, min_dec;
//int entero_ar, frac_ar , ar_horas;
double dec, ar;
int res;

AnsiString aa;

 aux[0] = 2;   //mensaje al LX200
 aux[1] = 0;

  if((in = fopen("c:\\inetpub\\wwwroot\\elbrus.aqi", "rt")) != NULL)
   {

      fread(aqui, sizeof(aqui), 1, in);
      fclose(in);

      strncpy(&cad[0], &aqui[14], 7);    //  AR
      cad[8] = 0;
      ar = atof(cad);

      strncpy(&cad[0], &aqui[26], 7);    //  DEC
      cad[8] = 0;
      dec = atof(cad);
      strncpy(&cad[0], &aqui[34], 24);
      cad[24] = 0;
      aa = "¿Sincronizar Telescopio en:  " + AnsiString(cad) + " ?";


      if(Application->MessageBox(aa.c_str(), "   ATENCION", MB_OKCANCEL	) == IDOK	)
      {

        Sincronizando = true;
        Slew_F(ar, dec);       //manda las nuevas coordenadas
        BSincronizarClick(NULL);  //envia el comando de cambio de coordenadas
      }
   }
}



//---------------------------------------------------------------------------

void __fastcall TForm1::BGraficasClick(TObject *Sender)
{
FGraficas->ShowModal();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------




void __fastcall TForm1::ServerSocket1Accept(TObject *Sender,
      TCustomWinSocket *Socket)
{
           Socket1 = Socket;
    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        Socket1 = NULL;
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
         Socket1 = NULL;
       
}
//---------------------------------------------------------------------------
// Lo que viene por el PUERTO SERIE VIRTUAL es enviado al telescopio
void __fastcall TForm1::ServerSocket1ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
  char aux[300];
  AnsiString A;

//  TimeRead = ::GetTickCount();
  A = Socket->ReceiveText();
//  Memo2->Lines->Add(A);
  aux[0] = 2;   //mensaje al LX200
  aux[1] = 0;
  strcpy(&aux[2], A.c_str());
  S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BcambiaIPClick(TObject *Sender)
{
 S1->IniciarRabbit();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BGuardaConfigClick(TObject *Sender)
{
   FILE *out;

   char config[100][50];
   char auxi[+50];

        memset(config, ' ', sizeof(config));
        strcpy(config[0],  ELocation->Text.c_str());
        strcpy(config[1],  EObserver->Text.c_str());
        strcpy(config[2],  ETelescop->Text.c_str());
        strcpy(config[3],  EFocal->Text.c_str());
        strcpy(config[4],  EApert->Text.c_str());
        strcpy(config[5],  EInstrument->Text.c_str());
        strcpy(config[6],  EComent->Text.c_str());
        strcpy(config[7],  Edit_IP->Text.c_str());
        strcpy(config[8],  ERetraso->Text.c_str());
        strcpy(config[9],  ELimpiado->Text.c_str());
        strcpy(config[10], CBCCD->Text.c_str());
        strcpy(config[11], AnsiString(CBCCD->ItemIndex).c_str());

//        strcpy(config[12], itoa(CCDs[0].FilaInicio, auxi, 10));
        strcpy(config[12], EFilaInicio->Text.c_str());
//        strcpy(config[13], itoa(CCDs[0].FilaFin, auxi, 10));
        strcpy(config[13], EFilaFin->Text.c_str());
//        strcpy(config[14], itoa(CCDs[0].ColumnaInicio, auxi, 10));
        strcpy(config[14], EColumnaInicio->Text.c_str());
//        strcpy(config[15], itoa(CCDs[0].ColumnaFin, auxi, 10));
        strcpy(config[15],  EColumnaFin->Text.c_str());

        strcpy(config[16],  ELatitud->Text.c_str());
        strcpy(config[17],  ELongitud->Text.c_str());

        if(CBFlipVertical->State == cbChecked)
                strcpy(config[18], "F");
        else strcpy(config[18], "N");
        if(CBFlipHorizontal->State == cbChecked)
                strcpy(config[19], "F");
        else strcpy(config[19], "N");

        out = fopen("config.txt", "wt");
        fwrite(config, sizeof(config), 1, out); /* write struct s to file */
        fclose(out); /* close file */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EColumnaFinChange(TObject *Sender)
{
/*
  if(ECU->Text.ToInt() > CCDs[CBCCD->ItemIndex].ColumnasFisicas)
     ECU->Text = CCDs[CBCCD->ItemIndex].ColumnasFisicas;
  CCDs[CBCCD->ItemIndex].ColumnasUtiles = ECU->Text.ToInt();
  NumeroColumnas = ECU->Text.ToInt() / Binin;
  NumeroFilas = EFU->Text.ToInt() / Binin;
  offsetx = (CCDs[CBCCD->ItemIndex].ColumnasFisicas - CCDs[CBCCD->ItemIndex].ColumnasUtiles)/2;
  offsety = (CCDs[CBCCD->ItemIndex].FilasFisicas - CCDs[CBCCD->ItemIndex].FilasUtiles)/2;
  if(CBR->State == cbUnchecked)
  {
    PX1->Caption = 0;
    PX2->Caption = ECU->Text;
    PY1->Caption = 0;
    PY2->Caption = EFU->Text;
  }
*/
}
//---------------------------------------------------------------------------




void __fastcall TForm1::UpDown1ChangingEx(TObject *Sender,
      bool &AllowChange, short NewValue, TUpDownDirection Direction)
{
   if(Direction  == updUp)
   {
     if(NewValue >= 30)
        UpDown1->Increment = 30;
     else if(NewValue >= 5)
        UpDown1->Increment = 5;
   }
   else
   {
     if(NewValue < 31)
       UpDown1->Increment = 5;
     if(NewValue < 6)
       UpDown1->Increment = 1;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CBimagenChange(TObject *Sender)
{
   CBGuardar->Checked = true;

   if (CBimagen->ItemIndex == 0) ENombreFichero->Text = "img";
   else if (CBimagen->ItemIndex == 1) ENombreFichero->Text = "bias";
   else if (CBimagen->ItemIndex == 2) ENombreFichero->Text = "dark";
   else if (CBimagen->ItemIndex == 3)
   {
      ENombreFichero->Text = "foco";
     // CBGuardar->Enabled = false;
      CBGuardar->Checked = false;
   }
   else if (CBimagen->ItemIndex == 4) ENombreFichero->Text = "flat";

}
//---------------------------------------------------------------------------



void __fastcall TForm1::DirectoryListBox1Change(TObject *Sender)
{
  mPath =  DirectoryListBox1->Directory;
}
//---------------------------------------------------------------------------



/*
void Estadistica()  //calcula la media y el histograma
{
  unsigned short Histograma[0x7FFF];
  long m = 0;
  int xcf;

  for(int cf = 0; cf < 0x7FFF; cf++)
  {
    histo[cf] = 0;
  }
//  for (int cy = 10; cy < BM->Height - 10; cy++)
  for (int cy = 10; cy < BM->Height - 10; cy++)
  {
//    for (int cx = 10; cx < BM->Width - 10; cx++)
    for (int cx = 10; cx < BM->Width - 10; cx++)
    {
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

  m = m / ((BM->Height-20) * (BM->Width-20));
 // if(fondocielo > m)
 //     fondocielo = m;
  Form1->Mhistory->Lines->Add("media = " + AnsiString(m));
  Form1->Mhistory->Lines->Add("fondo = " + AnsiString(fondocielo));

  return (m);
}
 */


/** FUNCION ADAPTADORA *
 * 
 * Esta funciona adaptadora hace que tanto la region de fondo de cielo
 * como la region de calculo de centroide de la estrella sea toda la imagen 
 * Si el punteio a la imagen cambia con cada toma, pues hay que llamarla
 * una vez por cada toma.
 * Si se reutiliza el mismo buffer una y otra vez, pues se lama una vez al principio
 *
 * Asume que la imagen es un buffer todo seguido de pixeles
 */
void ACOR_SetImage(pixel_t* img, int width, int height)
{
  AF_SetImage(img, width, height);
  AF_SetSkyRegion(0, 0, width-1, height-1);
  AF_SetCentroidRegion(0, 0, width-1, height-1);
}



/* Esta función hace todo lo necesario para calcular el HFD de una imagen */
int pos_index = 0;
int pos_motor[100];// = {2000, 1800, 1600, 1400, 1200, 1000, 800, 600};

void Calcula_Imagen(pixel_t* imagen, int width, int height, int pos_index)
{
  float_t hfd;
  float_t xc, yc;
  int i, j, result;
  float_t difFoco;
  int pos;

  pos = pos_motor[pos_index];
//  pos = pos_index;
   Form1->Memo1->Lines->Add("set_imagen");
   AF_SetImage(imagen, width, height);
   Form1->Memo1->Lines->Add("HFD");
   /* si res == -1 ha habido algun problema. Mirar el log "autofocus.txt" */
  result = AF_HFD(&hfd);
   Form1->Memo1->Lines->Add("result =" + result);
   /* despues de calcular el hfd, se puede llamar a esta rutina */
  /* lo suyo es pintar una cruz en el centro del pixel */
   Form1->Memo1->Lines->Add("GetCentroid");
  AF_GetCentroid(&xc, &yc);
  i = floor(xc + 0.5);  /* redondea coordenadas a pixel mas cercano */
  j = floor(yc + 0.5);

  /* añadir la medida al vector de medidas */

  AF_AddMeasurement(pos, hfd);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::BIniCalClick(TObject *Sender)
{
  AF_InitCalibration();
  AF_SetImage((short*)FotoPrincipal->Pixeles, FotoPrincipal->BM->Width, FotoPrincipal->BM->Height);
  Memo1->Lines->Add("Width =" + AnsiString(FotoPrincipal->BM->Width) + "  Height =" + AnsiString(FotoPrincipal->BM->Height));

}


//---------------------------------------------------------------------------
void __fastcall TForm1::BFotoEnfocarClick(TObject *Sender)
{
   nfotos = FotoActual;   //lanza una toma
// AF_SetImage(imagen, width, height);

}






void __fastcall TForm1::IFotoMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  char *ptr;
  char aux[300];

  if(S1 != NULL)
  {
    if(PFoto->BevelOuter == bvRaised)
    {
      if((CBGuardar->Checked==true))
      {
        SetCurrentDirectory( mPath.c_str());
        if(CBWeb->State == cbChecked)
        {
          if(FileExists(ENombreFichero->Text + AnsiString("_001.fit")))
          {
            if(Application->MessageBox("El Fichero ya existe. ¿Sobrescribir?", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
            {
              return;
            }
          }
        }
      }
      nfotos = UDNFotos->Position;
      FotoActual = 1;
      numeroLineaanterior = 0;
      if(CBT->State == cbChecked)
        test = true;
      else
        test = false;

      ObtuIndex = CBimagen->ItemIndex;
      mseg = Emsg->Text.ToInt();
      seg = Esg->Text.ToInt();

      segEntreFotos = ETiempoEntreFotos->Text.ToInt();
      TiempoInicio =  ::GetTickCount();

      obturetraso =  ERetraso->Text.ToInt();
      numlimpiados = ELimpiado->Text.ToInt();

      if(ObtuIndex == 1) // se trata de un bias.
      {
        mseg = 0;
        seg = 0;
        obturetraso = 0;
        ObtuIndex = 2;  // dark a efectos del cor para que no abra shuter
      }
//      if(ObtuIndex != 3) //impide cambiar el tamaño del recuadro mientras adquiere
  //      PB1recuadroNo = false;

      LeyendoFoto = false;
      FinFoto = false;
      PFoto->BevelOuter = bvLowered;
      PFoto->Color = (TColor)0x00DEDEDE;
      SLedFoto->Brush->Color = clRed;
      Panel5->Enabled = false;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PB1MouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
   TPoint p, p2;

  if(PageControl1->ActivePage == VISUALIZACION)
  {
    Lupa(X, Y, FotoPrincipal, false);
  }
  else
  {
    if(Shift.Contains(ssRight) && CBRectangulo->State == cbChecked)
    {
   /*   points[0] = Point(X1F,Y1F);
      points[1] = Point(X2F,Y1F);
      points[2] = Point(X2F,Y2F);
      points[3] = Point(X1F,Y2F);
      points[4] = Point(X1F,Y1F);
      PB1->Canvas->Pen->Color = clWhite;
      PB1->Canvas->Pen->Mode = pmXor;
      PB1->Canvas->Polyline(points, 4);
     */ 
      Y1F = CCDs[CBCCD->ItemIndex ].FilaInicio / Binin;
      X1F = CCDs[CBCCD->ItemIndex].ColumnaInicio / Binin;
      Y2F = CCDs[CBCCD->ItemIndex].FilaFin / Binin;
      X2F = CCDs[CBCCD->ItemIndex].ColumnaFin / Binin;

      X1T = X1F;
      Y1T = Y1F;
      X2T = X2F;
      Y2T = Y2F;

      points[0] = Point(X1F,Y1F);
      points[1] = Point(X2F,Y1F);
      points[2] = Point(X2F,Y2F);
      points[3] = Point(X1F,Y2F);
      points[4] = Point(X1F,Y1F);
      PB1->Canvas->Pen->Color = clWhite;
      PB1->Canvas->Pen->Mode = pmXor;
      PB1->Canvas->Polyline(points, 4);
      PintarRectAnt = true;
      PX1->Caption = X1T;
      PX2->Caption = X2T;
      PY1->Caption = Y1T;
      PY2->Caption = Y2T;
    //  PRecuadro->Caption = AnsiString(X2T-X1T) + " x " + AnsiString(Y2T-Y1T);
    } //fin boton derecho
    else if ((Shift.Contains(ssLeft)) && CBRectangulo->State == cbChecked)
    {

      if(first == true)
      {
        first = false;
        if(PintarRectAnt == true)
        {
          points[0] = Point(X1T, Y1T);
          points[1] = Point(X2T, Y1T);
          points[2] = Point(X2T, Y2T);
          points[3] = Point(X1T, Y2T);
          points[4] = Point(X1T, Y1T);
          PB1->Canvas->Pen->Color = clWhite;
          PB1->Canvas->Pen->Mode = pmXor;
          PB1->Canvas->Polyline(points, 4);
        }
        X1T = (X/5)*5;
        Y1T = (Y/5)*5;
        X2T = X1T + 40;
        if (X2T > NumeroColumnas)
          X2T = X1T - 40;
        Y2T = Y1T + 40;
        if (Y2T > NumeroFilas)
          Y2T = Y1T - 40;
        p.x = X2T;
        p.y = Y2T;
        p2 = PB1->ClientToScreen(p);
        SetCursorPos(p2.x, p2.y );
      }
      else
      {
        X2T = X;
        Y2T = Y;
      }

      points[0] = Point(X1T, Y1T);
      points[1] = Point(X2T, Y1T);
      points[2] = Point(X2T, Y2T);
      points[3] = Point(X1T, Y2T);
      points[4] = Point(X1T, Y1T);
      PB1->Canvas->Pen->Color = clWhite;
      PB1->Canvas->Pen->Mode = pmXor;
      PB1->Canvas->Polyline(points, 4);
      PintarRectAnt = true;
      PX1->Caption = X1T;
      PX2->Caption = X2T;
      PY1->Caption = Y1T;
      PY2->Caption = Y2T;
      PBF->Position = 0;
      PRecuadro->Caption = AnsiString(X2T-X1T) + " x " + AnsiString(Y2T-Y1T);
    }//fin boton izquierdo
  }
 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PB1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
   if((X >= FotoPrincipal->BM->Width) || (Y >= FotoPrincipal->BM->Height) || (X < 0) || (Y < 0))
  {
    return;
  }

  if(PageControl1->ActivePage == VISUALIZACION)
  {
    Lupa(X, Y, FotoPrincipal, false);
  }
  else if (Shift.Contains(ssLeft)&& CBRectangulo->State == cbChecked)
  {
    points[0] = Point(X1T, Y1T);
    points[1] = Point(X2T, Y1T);
    points[2] = Point(X2T, Y2T);
    points[3] = Point(X1T, Y2T);
    points[4] = Point(X1T, Y1T);
    PB1->Canvas->Pen->Color = clWhite;
    PB1->Canvas->Pen->Mode = pmXor;
    PB1->Canvas->Polyline(points, 4);
    X2T = X;
    Y2T = Y;
    PX2->Caption = X2T;
    PY2->Caption = Y2T;
    PBF->Position = 0;
    points[0] = Point(X1T, Y1T);
    points[1] = Point(X2T, Y1T);
    points[2] = Point(X2T, Y2T);
    points[3] = Point(X1T, Y2T);
    points[4] = Point(X1T, Y1T);
    PB1->Canvas->Pen->Color = clWhite;
    PB1->Canvas->Pen->Mode = pmXor;
    PB1->Canvas->Polyline(points, 4);
     PRecuadro->Caption = AnsiString(X2T-X1T) + " x " + AnsiString(Y2T-Y1T);
//    PRecuadro->Caption = AnsiString(X2T-X1T) + " x " + AnsiString(Y2T-Y1T);
  }
  PX->Caption = X;
  PY->Caption = Y;
  PP->Caption = FotoPrincipal->Pixeles[Y * NumeroColumnas + X];   //valor del pixel
  //PRecuadro->Caption = AnsiString(X2T-X1T) + " x " + AnsiString(Y2T-Y1T);
 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PB1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  if ( CBRectangulo->State == cbChecked)
  {

  //  Memo1->Lines->Add("MouseUp" );
    first = true;
    if(X1T > X2T)
    {
      X1F = X2T;
      X2F = X1T;
    }
    else
    {
      X1F = X1T;
      X2F = X2T;
    }
    if(Y1T > Y2T)
    {
      Y1F = Y2T;
      Y2F = Y1T;
    }
    else
    {
      Y1F = Y1T;
      Y2F = Y2T;
    }
  }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::BCalibrarClick(TObject *Sender)
{
   if(Application->MessageBox("Va a calibrar el anemometro termico. ¿Esta el aire en reposo?", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
   {
     return;
   }
   OrdenCalibrar = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BPeltierAClick(TObject *Sender)
{
  char aux[60];

  AnsiString A;

  aux[0] = 3;   //mensaje al CFS
  aux[1] = 0;

  if (Form1->EVpelt_man->Text > 254)
    Form1->EVpelt_man->Text = "254";

  VccdA = atoi(Form1->EVpelt_man->Text.c_str());
  
  A = "<a00" + Form1->EVpelt_man->Text + "-00>";
  strcpy(&aux[2], A.c_str());

  S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::BPeltierBClick(TObject *Sender)
{
  char aux[60];

  AnsiString A;

  aux[0] = 3;   //mensaje al CFS
  aux[1] = 0;

  if (Form1->EVpelt_man->Text > 254)
    Form1->EVpelt_man->Text = "254";

  A = "<b00" + Form1->EVpelt_man->Text + "-00>";
  strcpy(&aux[2], A.c_str());

  S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);
}
//---------------------------------------------------------------------------


void RegularTccdA(void)
{
   char aux[60], aux2[60];
  AnsiString A,B;
  static int TccdA, TccdA_Adj;
  static DWORD TiempoRegularA = 0;
//  static float Tccd;

  if(::GetTickCount() > (TiempoRegularA + atoi(Form1->ESegAdj->Text.c_str())*1000))
  {
     TiempoRegularA = ::GetTickCount();

     TccdA = atoi(Form1->PTccd->Caption.c_str());
      TccdA_Adj = atoi(Form1->EAdj_ccdA->Text.c_str());

//      Tccd = atof(Form1->PTccd->Caption.c_str());
//      Form1->Mhistory->Lines->Add("Tccd" + AnsiString(Tccd));
      if ( TccdA > TccdA_Adj )
        VccdA += 1;
      else VccdA -= 1; //Form1->MEpwmA->EditText = VccdA -5;

      if( VccdA > 255) VccdA = 255;
        else if ( VccdA < 0) VccdA = 0;

      sprintf( aux2, "%003d", VccdA);
      Form1->EVpelt_man->Text = aux2;
      aux[0] = 3;   //mensaje al CFS
      aux[1] = 0;
      A = "<a00" + AnsiString(aux2) + "-00>";
      strcpy(&aux[2], A.c_str());
      S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);

      A = "<b00" + AnsiString(aux2) + "-00>";
      strcpy(&aux[2], A.c_str());
      S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);

  }
}

//---------------------------------------------------------------------------


void __fastcall TForm1::CBSelCamaraChange(TObject *Sender)
{
   if(CBSelCamara->ItemIndex == 0)
    CBCCD->ItemIndex = 1;
    else CBCCD->ItemIndex = 0;

   TForm1::CBCCDChange(NULL); //actualiza parametros de adquisicion
}
//---------------------------------------------------------------------------





