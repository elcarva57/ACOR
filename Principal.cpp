//------------------------------------------------------------------------------
// $SAVE $EDNAME --style=ansi -S --indent-preprocessor -p -L -H -Y
// Montura Version 4.19 (V --> 04 13 23)
// Montura Modelo    14 (m --> 0E 23)
//
// Utilities, Version:
// HC: GEM 4.19
// MC: 6.12 6.12
// Mount Model: CGEM
//------------------------------------------------------------------------------
// includes generales
#include <vcl.h>
#include <IniFiles.hpp>
#pragma hdrstop
#include <stdio.h>
#include <stdlib.h>
#include "Principal.h"
#include <iostream>
#include <ios>
#include <sstream>
#include <ostream>

//---------------------------------------------------------------------------
// includes proyecto
#include "socket.h"
#include "rueda.h"
#include "ConfiFiltro.h"
#include "Programacion.h"
#include "fitsio.h"
#include "VerInfo.h"
#include <dateutils.hpp>

#include "visualizar.h"
#include "math.h"
#include "Unit3.h"
#include "conf_meteo.h"
#include "Enfoque.h"
#pragma package(smart_init)

#pragma link "ema_OCX"
#include "ema_OCX.h"
#pragma link "Test_OCX"
#pragma link "ema_OCX"
#pragma link "Test_OCX"
#pragma resource "*.dfm"
#include "ntofocus.h"
#include "Historia.h"

// defines
#define min(a, b)  (((a) < (b)) ? (a) : (b))

#define foco_proximo 500
#define foco_extremo 3000
#define FotosEnfoque 24
#define BUF_LX 500

//#define EsperaCFSsg 15


// variables
int margen_enfoque = foco_proximo * 2;
int periodo_x = 20;
int pasos_x = 50;
int pasos_enviados;
int contador_pasos;
int pos_inicio;
char sentido = '+';
FitResult result;
int retornoBFP;
bool FinX = 1, EsperandoFinX = 0;
double spizer;
bool Guardarjpg;

int FotoActual = 1;
int nfotos = 0;
int PerRefrescoTel = 1;

bool StopLX = true; // en true indica que el telescopio esta parado
double dRAMinAntes, nDecMinAntes;
bool pedidaRaDe = false;

//int segalm;
double tRa = 0, tDe = 0; //AR y Dec del mensaje del telescopio
double tAlt = 0, tAz = 0; //Altura y Azimut del mensaje del telescopio
extern char carecta[100], cdeclinacion[100];
double nRAHour = 0, dRAMin = 0, nDecDeg = 0, nDecMin = 0;
bool negativo = false;
AnsiString coordARE, coordDEC;
AnsiString coordAZM, coordALT;

float CuentaGuiaAR, CuentaGuiaDec;
float TiempoGuiaAR;   //tiempo antes de parar guiado AR
float TiempoGuiaDec;   //tiempo antes de parar guiado AR
float dY, dX; // desvio entre fotos Dec y AR
int nEstrellas; // numero de estrellas usadas para calcular desvio entre fotos


WideString NombreFichero;
extern int numeroOrdenAnterior;
extern bool FinFoto, A_FinFoto, B_FinFoto;
extern DWORD A_T_Ini_Exp, A_T_Ini_Lect, A_T_Fin_Lect;
extern DWORD B_T_Ini_Exp, B_T_Ini_Lect, B_T_Fin_Lect;
bool PintarRectAnt = true;
int X1T, X2T, Y1T, Y2T;
int X1F, X2F, Y1F, Y2F;
int X1FS, X2FS, Y1FS, Y2FS;
TFConfigMeteo *fp = NULL;
//TFrtml *prtml = NULL;
int cuentita; //para simular posicion del enfoque.
int fallos_hfd;


AnsiString HoraSideral_hms;

enum Commands {GetRAS_DEC, GetPreRAS_DEC, GetAZM_ALT, GetPreAZM_ALT,
               GotoRAS_DEC, GotoPreRAS_DEC, GotoAZM_ALT, GotoPreAZM_ALT,
               SyncRAS_DEC, SyncPreRAS_DEC,
               GetTrackMode, SetTrackMode,
               VarRASPos, VarRASNeg, VarDECPos, VarDECNeg,
               FixRASPos, FixRASNeg, FixDECPos, FixDECNeg,
               GetLoc, SetLoc, GetTime, SetTime,
               GetVer, GetDevVer, GetModel, Echo, AlignComplete,
               GotoProg, GotoCancel,
               None
              };

Commands command = None;

/*******************************************************************************
Para configurar la estructura del fichero INI hay que crear primero las
estructuras de las secciones y después la estructura de todo el INI:
a) Cree una estructura struct para cada sección del INI y nómbrela con el nombre
   de la sección todo en mayúsculas. Ej: LOCATION;
b) Añada en cada estructura el nombre de las variables del INI con su tipo
   tal y como aparezcan en el fichero. Ej: unsigned short degLatA;
c) Cree una estructura para todo el fichero INI compuesta por las estructuras
   de cada una de sus secciones. Ej: CONF_INI;
d) Dentro de CONF_INI añada una variable con cada sección del fichero INI
   tal y como aparezcan en el fichero. Ej: LOCATION Location;
e) Cree una variable del tipo CONF_INI y llámela ini. Ej: CONF_INI ini;
f) De esta manera, para usar una determinada variable de configuración
   habrá que usar: ini.Section.Variable
   Ejemplos:
   ini.Location.Name            Es el nombre del lugar de observación
   ini.Observation.Telescope    Es el nombre del telescopio usado
   ini.CamA.RowIni              Es el número de fila inicial de la cámara A
*******************************************************************************/

typedef struct //LOCATION
{
    AnsiString Name;
    unsigned short degLatA; // A is the number of degrees of latitude.
    unsigned short minLatB; // B is the number of minutes of latitude.
    unsigned short secLatC; // C is the number of seconds of latitude.
    unsigned short nosLatD; // D is 0 for north and 1 for south.
    unsigned short degLonE; // E is the number of degrees of longitude.
    unsigned short minLonF; // F is the number of minutes of longitude.
    unsigned short secLonG; // G is the number of seconds of longitude.
    unsigned short eowLonH; // H is 0 for east and 1 for west.
} LOCATION;

// Posición telescopio El Cerro:
//                  40º25'5"N 3h33m11sW
//SCOPE_POS telPos = {40, 25, 5, 0, 3, 33, 11, 1};

typedef struct //OBSERVATION
{
    AnsiString Observer;
    AnsiString Telescope;
    AnsiString Focal;
    AnsiString Aperture;
    AnsiString Camera;
    AnsiString Comment;
    AnsiString IP;
    AnsiString Retraso;
    AnsiString Limpiado;
} OBSERVATION;

typedef struct //CAMERA
{
    AnsiString Name;
    int Index;
    int RowIni;
    int RowFin;
    int ColIni;
    int ColFin;
} CAMERA;

typedef struct //IMAGE
{
    bool FlipVert;
    bool FlipHori;
    AnsiString FotoDir;
    AnsiString NameDir;
    AnsiString ElbrusFile;
} IMAGE;

typedef struct     //configuracion del programa ({appname}.ini)
{
    LOCATION    Location;
    OBSERVATION Observation;
    CAMERA      CamA;
    CAMERA      CamB;
    IMAGE       Image;
} CONF_INI;

CONF_INI ini;

//******************************************************************************

typedef struct    // almacena lecturas promediadas de un minuto
{
    TDateTime Dia;
    TDateTime Hora;
    float LeturasTemp;
    float LeturasHumedad;
    float LeturasRocio;
    float LeturasNubes;
    float LeturasLluvia;
    float LeturasAnem;
    float LeturasAnemT;
    float LeturasAnemT2;
    float LeturasDireccion;
    float LeturasPluvio;
    float LeturasBarometro;
    float LeturasLuzR;
    float LeturasLuzUV;
    float LeturasBarometroAbs;
} METEODATOS;

METEODATOS grafico24h[1440];
METEODATOS meteosuma;


typedef struct     //configuracion de la estacion
{
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
} CONF_METEO;

CONF_METEO confEMA;

typedef struct     //Fecha y hora del telescopio
{
    unsigned short horQ; // Q is the hour (24 hour clock).
    unsigned short minR; // R is the minutes.
    unsigned short secS; // S is the seconds.
    unsigned short monT; // T is the month.
    unsigned short dayU; // U is the day.
    unsigned short yerV; // V is the year (century assumed as 20).
    unsigned short offW; // W is the offset from GMT for the time zone. Note: if zone is negative, use 256-zone.
    unsigned short dstX; // X is 1 to enable Daylight Savings and 0 for Standard Time.
} SCOPE_DAT;

SCOPE_DAT telDat;

int CuentaMensMeteo;
TDateTime Fecha;

int Temp_x10, Rocio_x10, Humedad_x10, slluvia, snubes, VFuente;
extern int TccdA, TcajaA, VpeltierA, TccdB, TcajaB, VpeltierB;
float TccdA_grados, TcajaA_grados, VpeltierA_volt, TccdB_grados, TcajaB_grados, VpeltierB_volt;
int VccdA = 50;
int VccdB = 50;

bool OrdenCalibrar;
bool PedidoNiveles;
bool meteo_resp = true;
bool cfs_resp = true;
bool LinkEnabled_flag, DisableAutoShutdown_flag;

bool AvisoFalloCor, AvisoCorOK, AvisoFalloMeteo;
//bool errorcfs;

int EsperaLX, EsperaMeteo, EsperaCfs = 0;


// int Referencia[] = {0, 0, 0, 0, 0, 0, 0, 0}; // en caliente a 25ºC
//int Referencia[] = {49, 23, 28, 29, 24, 26}; // en caliente a 25ºC

char Meteo[2000];
char BufTess[2000];

extern char bmp_ane[100], bmp_tem[100], bmp_plu[100], bmp_llu[100], bmp_bar[100];
extern char jpg_ane[100], jpg_tem[100], jpg_plu[100], jpg_llu[100], jpg_bar[100];
extern char jpg2_ane[100], jpg2_tem[100], jpg2_plu[100], jpg2_llu[100], jpg2_bar[100];

AnsiString mPath;

TDateTime FechaFoto, FechaFoto_fin;
extern int numeroOrden;
extern int numeroLinea;

extern unsigned short *Pixeles;
extern Graphics::TBitmap *BM;

float hfd;

TDateTime TimeRxLX200;
AnsiString CoordCal;
bool LXresponde = false;
bool test;
bool cancel;
int mseg, seg;
//int col, fil;
unsigned int obturetraso, numlimpiados, ObtuIndex, segEntreFotos;
int DogFoto;

char dir_trab[300];

TCustomWinSocket *Socket1 = NULL;
DWORD TimeRead;

char sec_1x1[] =
{
    0x09, 0x09, 0x0A, 0x08, 0x08, 0x08, 0x08,
    0x0C, 0x1C, 0x28, 0x38, 0x48, 0x58, 0x68, 0x79, 0x09, 0x09, 0x09,
    0x09, 0x09, 0x09, 0x01, 0x89, 0x09
};

char sec_2x2[] =
{
    0x09, 0x09, 0x0A, 0x08, 0x08, 0x08, 0x08,
    0x0C, 0x1C, 0x28, 0x38, 0x48, 0x58, 0x69, 0x78, 0x09, 0x09, 0x09,
    0x09, 0x09, 0x09, 0x01, 0x89, 0x09
};

char sec_3x3[] =
{
    0x09, 0x09, 0x0A, 0x08, 0x08, 0x08, 0x08,
    0x0C, 0x1C, 0x28, 0x38, 0x48, 0x58, 0x69, 0x78, 0x09, 0x08, 0x09,
    0x09, 0x09, 0x09, 0x01, 0x89, 0x09
};

char sec_4x4[] =
{
    0x09, 0x09, 0x0A, 0x08, 0x08, 0x08, 0x08,
    0x0C, 0x1C, 0x28, 0x38, 0x49, 0x58, 0x69, 0x78, 0x09, 0x08, 0x09,
    0x09, 0x09, 0x09, 0x01, 0x89, 0x09
};



char sec_limpiado[] =
{
    0x09, 0x09, 0x0A, 0x08, 0x09, 0x08, 0x0A, 0x08,
    0x09, 0x09, 0x0A, 0x08, 0x09, 0x09, 0x0A, 0x08,
    0x09, 0x09, 0x0A, 0x08, 0x89
};

char sec_vertical[] =
{0x01, 0x02, 0x01, 0x00};


char Buf_Cfs[500][16];
int indice_cfs;
char Buf_Meteo[500][16];
int indice_meteo;

char buf_LX[BUF_LX][16];
int len_buf_LX[BUF_LX];
int ind_wrLX, ind_rdLX, cont_mensLX;

bool arde = true; // Flag para pedir Ascensión Recta/Declinación o Azimut/Altura

int Puerto = 1;
int AutoEnfoque = 0;

WORD Valores[7][7]; //para la lupa
TColor Colores[7][7];

DWORD TiempoInicio = 0, IniciaAR = 0;

typedef struct
{
    char* Nombre;
    int ColumnasFisicas;
    int FilasFisicas;
    int ColumnaInicio;
    int FilaInicio;
    int ColumnaFin;
    int FilaFin;
} stCCD;
//Tamaño fisico y util de los posibles sensores.
// {"KAFxxxx (zona usable)", long buf salida, total filas, x1,y1, x2,y2}
stCCD CCDs[3] =
{
    {"KAF400",     796, 520, 14, 4, 782, 516},
    {"KAF1600", 1552, 1032, 14, 4, 1538, 1026},
    {"KAF3000", 2080, 1544, 44, 18, 2060, 1530}
};
stCCD CCDsB[3] =
{
    {"KAF400",     796, 520, 14, 4, 782, 516},
    {"KAF1600", 1552, 1032, 14, 4, 1538, 1026},
    {"KAF3000", 2080, 1544, 44, 18, 2060, 1530}
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




//char cuenta[8];
bool Sincronizando = false;
bool Timer60sg = false;
char SelCamara;
int Binin = 1;
TForm1 *Form1;
TForm2 *FActivo = NULL;
int ejex, ejey;
extern double x0, y0;
CRueda * Filtro = NULL;
CRueda * Shuter = NULL;

bool first = true;
TPoint points[5];

AnsiString EstadoRabbit = "", EstadoAnterior = "";
CSocket *S1 = NULL;
TColor ColorEstado = clBlack;
int celdaX = 0, celdaY = 0;

bool CGEM = false;
bool LX200 = false;
bool HPREC = false;

int SlewSpeed = 480; // Centrado ==> Botón centrado down=True

//----------------------- Prototipos de funciones ------------------------------
// Prototipos de funciones
extern void LeerConfMeteo();
void Slew_F(double Ra, double De);
void Slew_F(char *comando);
void GetRaDe_F(double *Ra, double *De);
void barra_horas(void);
void RegularTccdA(void);
void RegularTccdB(void);

void ACOR_SetImage(short*, int width, int height);
void Enfoque();
void FicheroEma();
void DibujaGraficas();
void QuitaRectangulo();
void MueveEnfoque();
void HacerFoto( short x1, short y1, short x2, short y2, unsigned char binin,
                short seg, short mseg, short NumCol, short NumFil,
                unsigned char test, unsigned char cancel, short nfotos,
                short limpiado, short obturador, short retraso, WideString nomb
              );
void Lupa(int X, int Y, cFoto *Foto, bool actualizar);
void printerror( int status);
void actualizar_datos(void);
void RellenarBitmap(int x1, int y1, int x2, int y2);
void AnalizarCFS(char c);
void EMAv2COM();

void ProcesarLX200();
void ProcesarCGEM();
void ProcesarGetPreRAS_DEC(AnsiString CadCgem);
void ProcesarGetRAS_DEC(AnsiString CadCgem);
void ProcesarGetPreAZM_ALT(AnsiString CadCgem);
AnsiString formatARE(double dARE);
AnsiString formatDEC(double dDEC);
AnsiString formatAZM(double dAZM);
AnsiString formatALT(double dALT);
AnsiString ArDecToOrden(long ARe_Hor, long ARe_Min, long ARe_Sec, long ARe_CSec,
                        long Dec_Gra, long Dec_Min, long Dec_Sec, long Dec_CSec, char Dec_Sgn);

AnsiString ArDecToTeles(AnsiString AReHor, AnsiString AReMin,
                        AnsiString AReSec, AnsiString AReCSec,
                        AnsiString DecGra, AnsiString DecMin,
                        AnsiString DecSec, AnsiString DecCSec, char DecSgn);

AnsiString ArDecPrecToOrden(long ARe_Hor, long ARe_Min, long ARe_Sec, long ARe_CSec,
                            long Dec_Gra, long Dec_Min, long Dec_Sec, long Dec_CSec, char Dec_Sgn);

AnsiString ArDecPrecToTeles(AnsiString AReHor, AnsiString AReMin,
                            AnsiString AReSec, AnsiString AReCSec,
                            AnsiString DecGra, AnsiString DecMin,
                            AnsiString DecSec, AnsiString DecCSec, char DecSgn);

extern double CalAltura(double ARec, double DEC);
extern double CalAzimut(double ALT, double ARec, double DEC);

void WriteHistory (AnsiString cadena);

void EnviaLX(char *orden);
void EnviaLX(char *orden, int long_orden);

int readSpeedValues(TSpeedButton* sb);

AnsiString CmdToStr(Commands cmd);
void setTimers (bool valEnabled);
void readINI();
void writeINI();

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

//------------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
//------------------------------------------------------------------------------
{
    char *ptr;
    char aux[100];
    FILE *in;

    char config[100][50];
    //char ConfMeteo[100];
    char filtro[200], shuter[200];

    char loc[10] = {0};
    char nos = 'N';
    char eow = 'E';

    readINI();

    GetCurrentDirectory( 100, dir_trab);
    strcat(dir_trab, "\\");
    Memo1->Lines->Add(dir_trab);

    if (CBCGEM->Checked == true)
    {
        CGEM = true;
        LX200 = false;
        HPREC = cbPrecision->Checked;
        cbPrecision->Visible = true;
    }
    else
    {
        LX200 = true;
        CGEM = false;
        HPREC = false;
        cbPrecision->Visible = false;
    }


    FotoPrincipal = new cFoto(NumeroFilas, NumeroColumnas, x0, y0);
    S1 = new CSocket();
    wsprintf(aux, "     %s  %s", S1->NombreHostLocal, S1->cadenaIP);
    PHOST->Caption = aux;

    LeyendoFoto = false;


    strcpy(filtro,  dir_trab);
    strcat(filtro, "Filtro1.cfr");
    Filtro = new CRueda(PFiltro, 0, 0, 100, 7, filtro, 'y');
    PFiltro->Width = Filtro->Width - 2;
    PFiltro->Height = Filtro->Height - 1;
    Filtro->S1 = S1;
    //  Filtro->enviarReset();

    Filtro->enviarPrincipio();

    indice_cfs++;
    strcpy(Buf_Cfs[indice_cfs],  "<xp>");    // primero xo es LIFO

    //  indice_cfs++;
    //  strcpy(Buf_Cfs[indice_cfs],  "<tf>");    // primero xo es LIFO

    strcpy(shuter,  dir_trab);
    strcat(shuter, "Filtro2.cfr");
    Shuter = new CRueda(PShuter, 0, 0, 100, 3, shuter, 'z');
    PShuter->Width = Shuter->Width - 2;
    PShuter->Height = Shuter->Height - 1;
    Shuter->S1 = S1;
    //   Shuter->enviarReset();
    //Shuter->enviarPrincipio();

    CBCCD_A->Items->Add(CCDs[0].Nombre);
    CBCCD_A->Items->Add(CCDs[1].Nombre);
    CBCCD_A->Items->Add(CCDs[2].Nombre);
    CBCCD_A->ItemIndex = 0;
    Binin = 1;
    //PBinin->Caption = (int)Binin;
    TBBinin->Position = (int)Binin;
    //--   TBBininChange(TBBinin);

    EFilaInicioA->Text = CCDs[0].FilaInicio;// / Binin;
    EFilaFinA->Text = CCDs[0].FilaFin;// / Binin;
    EColumnaInicioA->Text = CCDs[0].ColumnaInicio;// / Binin;
    EColumnaFinA->Text = CCDs[0].ColumnaFin;// / Binin;

    Y1T = CCDs[CBCCD_A->ItemIndex ].FilaInicio / Binin;
    X1T = CCDs[CBCCD_A->ItemIndex].ColumnaInicio / Binin;
    Y2T = CCDs[CBCCD_A->ItemIndex].FilaFin / Binin;
    X2T = CCDs[CBCCD_A->ItemIndex].ColumnaFin / Binin;


    CBCCD_B->Items->Add(CCDsB[0].Nombre);
    CBCCD_B->Items->Add(CCDsB[1].Nombre);
    CBCCD_B->Items->Add(CCDsB[2].Nombre);
    CBCCD_B->ItemIndex = 0;

    EFilaInicioB->Text = CCDsB[0].FilaInicio;// / Binin;
    EFilaFinB->Text = CCDsB[0].FilaFin;// / Binin;
    EColumnaInicioB->Text = CCDsB[0].ColumnaInicio;// / Binin;
    EColumnaFinB->Text = CCDsB[0].ColumnaFin;// / Binin;

    Form1->EPasosEnfoque->Text = pasos_x;
    Form1->EVelocidadEnfoque->Text = periodo_x;

    // La lectura de cor.cfg se sustituye por los datos de Acor.ini
    ELocation->Text = ini.Location.Name;
    EObserver->Text = ini.Observation.Observer;
    ETelescop->Text = ini.Observation.Telescope;
    EFocal->Text = ini.Observation.Focal;
    EApert->Text = ini.Observation.Aperture;
    EInstrument->Text = ini.Observation.Camera;
    EComent->Text = ini.Observation.Comment;
    Edit_IP->Text = ini.Observation.IP;
    ERetraso->Text = ini.Observation.Retraso;
    ELimpiado->Text = ini.Observation.Limpiado;

    CBCCD_A->ItemIndex                     = ini.CamA.Index;
    CCDs[CBCCD_A->ItemIndex].FilaInicio    = ini.CamA.RowIni;
    CCDs[CBCCD_A->ItemIndex].FilaFin       = ini.CamA.RowFin;
    CCDs[CBCCD_A->ItemIndex].ColumnaInicio = ini.CamA.ColIni;
    CCDs[CBCCD_A->ItemIndex].ColumnaFin    = ini.CamA.ColFin;

    EFilaInicioA->Text = CCDs[CBCCD_A->ItemIndex].FilaInicio;//config[12];
    EFilaFinA->Text = CCDs[CBCCD_A->ItemIndex].FilaFin;//config[13];
    EColumnaInicioA->Text = CCDs[CBCCD_A->ItemIndex].ColumnaInicio;//config[14];
    EColumnaFinA->Text = CCDs[CBCCD_A->ItemIndex].ColumnaFin;//config[15];

    // PBinin->Caption = ((TTrackBar*)Sender)->Position;
    Binin = PBinin->Caption.ToInt();
    NumeroFilas = CCDs[CBCCD_A->ItemIndex].FilasFisicas / Binin;
    NumeroColumnas = CCDs[CBCCD_A->ItemIndex].ColumnasFisicas / Binin;
    Y1F = CCDs[CBCCD_A->ItemIndex].FilaInicio / Binin;
    X1F = CCDs[CBCCD_A->ItemIndex].ColumnaInicio / Binin;
    Y2F = CCDs[CBCCD_A->ItemIndex].FilaFin / Binin;
    X2F = CCDs[CBCCD_A->ItemIndex].ColumnaFin / Binin;

    PX1->Caption = X1F;
    PY1->Caption = Y1F;
    PX2->Caption = X2F;
    PY2->Caption = Y2F;
    PB1->Width = NumeroColumnas;
    PB1->Height = NumeroFilas;
    PBF->Position = 0;
    FotoPrincipal->Resizear(NumeroColumnas, NumeroFilas);
    RellenarBitmap(0, 0, NumeroColumnas, NumeroFilas);

    CBCCD_B->ItemIndex                     = ini.CamB.Index;
    CCDs[CBCCD_B->ItemIndex].FilaInicio    = ini.CamB.RowIni;
    CCDs[CBCCD_B->ItemIndex].FilaFin       = ini.CamB.RowFin;
    CCDs[CBCCD_B->ItemIndex].ColumnaInicio = ini.CamB.ColIni;
    CCDs[CBCCD_B->ItemIndex].ColumnaFin    = ini.CamB.ColFin;

    EFilaInicioB->Text = CCDsB[CBCCD_B->ItemIndex].FilaInicio;//config[23];
    EFilaFinB->Text = CCDsB[CBCCD_B->ItemIndex].FilaFin;//config[24];
    EColumnaInicioB->Text = CCDsB[CBCCD_B->ItemIndex].ColumnaInicio;//config[25];
    EColumnaFinB->Text = CCDsB[CBCCD_B->ItemIndex].ColumnaFin;//config[26];

    if (ini.Location.nosLatD == 1) nos = 'S';
    sprintf(loc, "%02dº%02d'%02d\" %c",
            ini.Location.degLatA, ini.Location.minLatB, ini.Location.secLatC, nos);
    ELatitud->Text = loc;

    if (ini.Location.eowLonH == 1) eow = 'W';
    sprintf(loc, "%02dº%02d'%02d\" %c ",
            ini.Location.degLonE, ini.Location.minLonF, ini.Location.secLonG, eow);
    ELongitud->Text = loc;

    CBFlipVertical->Checked   = ini.Image.FlipVert;
    CBFlipHorizontal->Checked = ini.Image.FlipHori;

    LeerConfMeteo();  //Lee valores del fichero ema.cfg a la estructura


//    TimeRead = ::GetTickCount();

//    memset(config, ' ', sizeof(config));
//
//    if ((in = fopen("cor.cfg", "rt")) != NULL)
//    {
//        // GetCurrentDirectory( strlen(dir_trab), dir_trab);
//
//        fread(config, sizeof(config), 1, in);
//        fclose(in);
//
//        ELocation->Text = config[0];
//        EObserver->Text = config[1];
//        ETelescop->Text = config[2];
//        EFocal->Text = config[3];
//        EApert->Text = config[4];
//        EInstrument->Text = config[5];
//        EComent->Text = config[6];
//        Edit_IP->Text = config[7];
//        ERetraso->Text = config[8];
//        ELimpiado->Text = config[9];

//        CBCCD_A->ItemIndex = atoi(config[11]);
//        CCDs[CBCCD_A->ItemIndex].FilaInicio =  atoi(config[12]);
//        CCDs[CBCCD_A->ItemIndex].FilaFin = atoi(config[13]);
//        CCDs[CBCCD_A->ItemIndex].ColumnaInicio = atoi(config[14]);
//        CCDs[CBCCD_A->ItemIndex].ColumnaFin = atoi(config[15]);
//        EFilaInicioA->Text = CCDs[CBCCD_A->ItemIndex].FilaInicio;//config[12];
//        EFilaFinA->Text = CCDs[CBCCD_A->ItemIndex].FilaFin;//config[13];
//        EColumnaInicioA->Text = CCDs[CBCCD_A->ItemIndex].ColumnaInicio;//config[14];
//        EColumnaFinA->Text = CCDs[CBCCD_A->ItemIndex].ColumnaFin;//config[15];

//        // PBinin->Caption = ((TTrackBar*)Sender)->Position;
//        Binin = PBinin->Caption.ToInt();
//        NumeroFilas = CCDs[CBCCD_A->ItemIndex].FilasFisicas / Binin;
//        NumeroColumnas = CCDs[CBCCD_A->ItemIndex].ColumnasFisicas / Binin;
//        Y1F = CCDs[CBCCD_A->ItemIndex].FilaInicio / Binin;
//        X1F = CCDs[CBCCD_A->ItemIndex].ColumnaInicio / Binin;
//        Y2F = CCDs[CBCCD_A->ItemIndex].FilaFin / Binin;
//        X2F = CCDs[CBCCD_A->ItemIndex].ColumnaFin / Binin;

//        PX1->Caption = X1F;
//        PY1->Caption = Y1F;
//        PX2->Caption = X2F;
//        PY2->Caption = Y2F;
//        PB1->Width = NumeroColumnas;
//        PB1->Height = NumeroFilas;
//        PBF->Position = 0;
//        FotoPrincipal->Resizear(NumeroColumnas, NumeroFilas);
//        RellenarBitmap(0, 0, NumeroColumnas, NumeroFilas);

//        CBCCD_B->ItemIndex = atoi(config[22]);
//        CCDsB[CBCCD_B->ItemIndex].FilaInicio =  atoi(config[23]);
//        CCDsB[CBCCD_B->ItemIndex].FilaFin = atoi(config[24]);
//        CCDsB[CBCCD_B->ItemIndex].ColumnaInicio = atoi(config[25]);
//        CCDsB[CBCCD_B->ItemIndex].ColumnaFin = atoi(config[26]);
//        EFilaInicioB->Text = CCDsB[CBCCD_B->ItemIndex].FilaInicio;//config[12];
//        EFilaFinB->Text = CCDsB[CBCCD_B->ItemIndex].FilaFin;//config[13];
//        EColumnaInicioB->Text = CCDsB[CBCCD_B->ItemIndex].ColumnaInicio;//config[14];
//        EColumnaFinB->Text = CCDsB[CBCCD_B->ItemIndex].ColumnaFin;//config[15];
//
//        ELatitud->Text = config[16];
//        ELongitud->Text = config[17];
//
//        if ( strcmp(&config[18][0], "F") == 0 )
//            CBFlipVertical->State = cbChecked;
//        else  CBFlipVertical->State = cbUnchecked;
//        if ( strcmp(&config[19][0], "F") == 0 )
//            CBFlipHorizontal->State = cbChecked;
//        else  CBFlipHorizontal->State = cbUnchecked;
//
//        Edit_IP->Text = config[20];
//    }
//    LeerConfMeteo();  //pasa valores del fichero de configuracion a la estructura

    // Historico->Mhistory->Lines->Add(" Leo : " + AnsiString(confEMA.direc_datos));
    //   Form1->Timer2->Interval = confEMA.DiasGrafico * 60000;  // ajusta tiempo entre muestras
}

//==============================================================================
int _matherr(struct _exception *except)
//==============================================================================
{
    return 1;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::TBBininChange(TObject *Sender)
//------------------------------------------------------------------------------
{
    PBinin->Caption = ((TTrackBar*)Sender)->Position;
    Binin = PBinin->Caption.ToInt();

    if (CBSelCamara->ItemIndex == 0)
    {
        NumeroFilas = CCDs[CBCCD_A->ItemIndex].FilasFisicas / Binin;
        NumeroColumnas = CCDs[CBCCD_A->ItemIndex].ColumnasFisicas / Binin;
        Y1F =  CCDs[CBCCD_A->ItemIndex].FilaInicio / Binin;
        X1F = CCDs[CBCCD_A->ItemIndex].ColumnaInicio / Binin;
        Y2F =  CCDs[CBCCD_A->ItemIndex].FilaFin / Binin;
        X2F = CCDs[CBCCD_A->ItemIndex].ColumnaFin / Binin;
    }
    else if (CBSelCamara->ItemIndex == 1)
    {
        NumeroFilas = CCDsB[CBCCD_B->ItemIndex].FilasFisicas / Binin;
        NumeroColumnas = CCDsB[CBCCD_B->ItemIndex].ColumnasFisicas / Binin;
        Y1F =  CCDsB[CBCCD_B->ItemIndex].FilaInicio / Binin;
        X1F = CCDsB[CBCCD_B->ItemIndex].ColumnaInicio / Binin;
        Y2F =  CCDsB[CBCCD_B->ItemIndex].FilaFin / Binin;
        X2F = CCDsB[CBCCD_B->ItemIndex].ColumnaFin / Binin;
    }
    PX1->Caption = X1F;
    PY1->Caption = Y1F;
    PX2->Caption = X2F;
    PY2->Caption = Y2F;
    PB1->Width = NumeroColumnas;
    PB1->Height = NumeroFilas;
    PBF->Position = 0;
    FotoPrincipal->Resizear(NumeroColumnas, NumeroFilas);
    RellenarBitmap(0, 0, NumeroColumnas, NumeroFilas);
}

//==============================================================================
void AnalizarCFS(char c)
//==============================================================================
{
    if (Filtro != NULL)
        Filtro->Analizar(c);
    if (Shuter != NULL)
        Shuter->Analizar(c);
}

//==============================================================================
// Analiza cadena recibida
void ProcesarTESs(void)
//==============================================================================
{
    char Aux[3000];
    char cad[20];
    static int longbuf;//, pos, posTESs, inimens, posbuf, posmeteo;
    static char bufin[1000];
    float RAtes, DECtes, hTes, mTes, gTes, mgTes, AltTes, AzTes;

    longbuf = min(S1->nDatosTESs, 200);   //como maximo se leen 200 caracteres
    S1->LeerTESs(bufin, longbuf);
    bufin[longbuf] = 0;
    if (longbuf > 180)
    {
        Historico->Mhistory->Lines->Add ("Exceso datos de TESs: " + AnsiString(longbuf));
        return;
    }
    else
    {
        //Leo datos del envio anterior
        Form1->LARtes->Caption = "RA: " + FloatToStrF(Form1->Skysensor1->AR, ffNumber, 3, 2);
        Form1->LDECtes->Caption = "DEC: " + FloatToStrF(Form1->Skysensor1->DEC, ffNumber, 3, 2);
        Form1->LAltTess->Caption = "Alt: " + FloatToStrF(Form1->Skysensor1->Pitch, ffNumber, 3, 2);
        Form1->LAzTess->Caption = "Az: " + FloatToStrF(Form1->Skysensor1->Roll, ffNumber, 3, 2);

        Form1->LmvTess->Caption = "mv: " + FloatToStrF(Form1->Skysensor1->Brillo, ffNumber, 3, 2);
        Form1->LTcieloTess->Caption = "Tcie: " + FloatToStrF(Form1->Skysensor1->TempCielo, ffNumber, 3, 2);
        Form1->LTambTess->Caption = "Tamb " + FloatToStrF(Form1->Skysensor1->TempAmbiente, ffNumber, 3, 2);
        //Envio cadena actual
        WideString ctes = bufin;
        Form1->Skysensor1->cadtess(ctes);

        //     Historico->Mhistory->Lines->Add (ctes + Form1->LARtes->Caption);

        /*
        //      Historico->Mhistory->Lines->Add (bufin);
        	if(longbuf == 15) { //Cadena solo con AR y DEC.
        //AR y Dec del telescopio en decimal
        		Aux[0] = bufin[0];
        		Aux[1] = bufin[1];
        		Aux[2] = 0;
        		hTes  = atof(Aux);  //Hora RA
        		Aux[0] = bufin[3];
        		Aux[1] = bufin[4];
        		Aux[2] = bufin[5];
        		Aux[3] = bufin[6];
        		Aux[4] = 0;
        		mTes  = atof(Aux);  //Minutos RA
        		RAtes = 15.0 * ( hTes + mTes / 60.0);
        	//    RAtes =  hTes + mTes / 60.0;

        		sprintf(cad,"%003.2f",RAtes);
        		Form1->LARtes->Caption = "RA " + AnsiString(cad) + "º";

        		Aux[0] = bufin[8];
        		Aux[1] = bufin[9];
        		Aux[2] = bufin[10];
        		Aux[3] = 0;
        		gTes = atof(Aux);
        		Aux[0] = bufin[12];
        		Aux[1] = bufin[13];
        		Aux[2] = 0;
        		mgTes = atof(Aux);
        		if(bufin[8]=='+')
        		DECtes = gTes + (mgTes / 60.0);
        		else {
        		DECtes = gTes - (mgTes / 60.0);
        		}
        	//  CoordCal = cad;
        		sprintf(cad,"%003.2f",DECtes);
        		Form1->LDECtes->Caption = "DEC " + AnsiString(cad) + "º";   //sale -10.32 en vez de -11º41'
        	//   CoordCal = ";" + CoordCal +";" + (AnsiString)(cad);

        //Altura y Azimut Calculada partir de AR y Dec del telescopio en decimal
        		AltTes = CalAltura(RAtes, DECtes); //(double ARec, double DEC)
        		sprintf(cad,"%003.2f",AltTes);
        		Form1->LAltTess->Caption = "Alt: " + AnsiString(cad) + "º";
        		CoordCal = CoordCal + ";"+ (AnsiString)(cad);

        		AzTes = CalAzimut(AltTes, RAtes, DECtes); //(double ARec, double DEC)
        		sprintf(cad,"%003.2f",AzTes);
        		Form1->LAzTess->Caption = "Az: " + AnsiString(cad) + "º";
        		CoordCal = CoordCal + ";" + (AnsiString)(cad);
        	}
        */
    }
}
/*
void ProcesarTESs()  //atiende datos puerto serie A TESs
{
static int longbuf, pos, posTESs, inimens;
static char bufin[10000];
char aTess[100];
static bool primer_check;

longbuf = min(S1->nDatosTESs, 200);   //como maximo se leen 200 caracteres
S1->LeerTESs(bufin, longbuf);
bufin[longbuf] = 0;
if (longbuf > 180){
	Historico->Mhistory->Lines->Add ("Exceso datos de TESs: " + AnsiString(longbuf));
	return;
}

for( pos = 0; pos < longbuf; pos++)
{
	if ((bufin[pos] == '<') && (inimens == 0))
	{
		inimens = 1;
		posTESs = 0;
		//  Historico->Mhistory->Lines->Add (bufin[pos]);
	}
	if (inimens >= 1)
	{
		if ((bufin[pos]< ' ' )||(bufin[pos]>'{'))
			BufTess[posTESs] = '_';//caracter " "  indicando fuera de lo esperado
		else
			BufTess[posTESs] = bufin[pos];

		if ( BufTess[posTESs]=='X') {
			inimens = 2;
			strcpy(BufTess, "<accX");
			posTESs = 4;
		}
		else if ( BufTess[posTESs]=='Y')
			inimens = 3;

		else if ( BufTess[posTESs]=='Z'){
			inimens = 4;
		}
		else if ((BufTess[posTESs] == '>') && (inimens == 4)) //cierre mensaje Z
		{
			BufTess[posTESs+1]= 0;
//             if(Form1->CBTess->Checked==true)
//                Historico->Mhistory->Lines->Add (AnsiString(BufTess) + " Cal: " + Form1->LAltura->Caption + " "
//                + Form1->LAzimut->Caption + " LX: " + Form1->LAlturaRx->Caption + " " + Form1->LAzimutRx->Caption + " "
//                + Form1->LHoraSideral->Caption );

			inimens = 0;

			if(Form1->CBTess->Checked==true){
				TimeRxLX200 = Fecha.CurrentTime();
				for (int cc =0; cc < strlen(BufTess); cc++) //quita letras y pone ;
				{
				if(((BufTess[cc]<0x30) || BufTess[cc]>0x39) && BufTess[cc]!= '>' && BufTess[cc]!= '-' && BufTess[cc]!= '+')
					BufTess[cc]= ' ';
				else if(BufTess[cc] == '>')
					BufTess[cc]= ';';
				}
				//Historico->Mhistory->Lines->Add (aTess);

				if (primer_check == TRUE) {
						Historico->Mhistory->Lines->Add(" HL; HS; lxRA; lxDec; lxAlt; lxAz; Alt; Az; X; Y; Z;");
						primer_check = FALSE;
				}
				else
				;
				Historico->Mhistory->Lines->Add((AnsiString)(TimeRxLX200)+ "; "+ HoraSideral_hms + CoordCal
					+ "; " + AnsiString(BufTess));
			}
			else primer_check = TRUE;

			return;
		}
		posTESs++;
		if (posTESs > 50)
			posTESs = 0;
	}
}
}
*/

//==============================================================================
void ProcesarCFS()
//==============================================================================
{
    static char bufcfs[50];
    static int longbuf, pos, poscfs, inimens;
    static char buf[300];
    static char txtcfs[30] = "                             ";
    static char txtcfs2[30] = "                             ";

    longbuf = min(S1->nDatosCFS, 200);   //como maximo se leen 200 caracteres
    S1->LeerCFS(buf, longbuf);
    buf[longbuf] = 0;

    if (longbuf > 60)
    {
        Historico->Mhistory->Lines->Add ("Exceso datos del CFS: " + AnsiString(longbuf));
        return;
    }

    for ( pos = 0; pos < longbuf; pos++)
    {
        if (buf[pos] == '<' )
        {
            inimens = 1;
            poscfs = 0;
        }
        if (inimens == 1)
        {
            if ((buf[pos] < ' ' ) || (buf[pos] > '{'))
                bufcfs[poscfs] = '_';//caracter " "  indicando fuera de lo esperado
            else
                bufcfs[poscfs] = buf[pos];
            poscfs++;
            if (poscfs > 40)
                poscfs = 0;
        }


        if (buf[pos] == '>' )  //terminado el mensaje comandos
        {
            bufcfs[poscfs] = 0;
            cfs_resp = true;

            //        if (bufcfs[4] == ' ')
            //         Historico->Mhistory->Lines->Add("CFS OK");
            //-----------------------------
            if (bufcfs[1] == 'X')
            {

                //      FinX = 1;
                if (bufcfs[2] == '>')
                {
                    FinX = 1;
                    indice_cfs++;
                    strcpy(Buf_Cfs[indice_cfs],  "<xp>");
                }
                else if ((bufcfs[2] == '+') || (bufcfs[2] == '-'))
                {
                    char pas[6];
                    for (int pp = 0; pp < 6; pp++)
                        pas[pp] = bufcfs[2 + pp];
                    pas[6] = 0;
                    contador_pasos =  atoi(pas);
                    Form1->PContador->Caption = contador_pasos;
                    //   FinX = 1;
                }
            }
            else if (bufcfs[3] == '/')
                Historico->Mhistory->Lines->Add("Reset CFS.");


            for (int kk = 0; kk < (int)strlen(bufcfs); kk++) //analisis ruedas filtro
            {
                if ((bufcfs[1] == 'y') || (bufcfs[1] == 'Y'))
                {
                    if (Filtro != NULL)
                        Filtro->Analizar(bufcfs[kk]);
                }
                if ((bufcfs[1] == 'z') || (bufcfs[1] == 'Z'))
                {
                    if (Shuter != NULL)
                        Shuter->Analizar(bufcfs[kk]);
                }
                // AnalizarCFS(bufcfs[kk]);
            }


            if ((bufcfs[1] == 'x') || (bufcfs[1] == 'X') || (bufcfs[1] == 'y')
                    || (bufcfs[1] == 'Y') || (bufcfs[1] == 'z') || (bufcfs[1] == 'Z')
                    || (bufcfs[1] == 'k') || (bufcfs[1] == 'K'))
            {
                for (int kk = 0; kk < (int)strlen(bufcfs); kk++)  // cadena informativa motores
                {
                    int pp;
                    for ( pp = 0; pp < (int)strlen(txtcfs); pp++)
                        txtcfs[pp] = txtcfs[pp + 1];
                    txtcfs[pp] = 0;
                }
                strcat (txtcfs, bufcfs);
                Form1->PCFS->Caption = txtcfs;

                if (Form1->CBcfs_log->State == cbChecked)
                    Historico->Mhistory->Lines->Add(bufcfs);
            }
            else
            {
                for (int kk = 0; kk < (int)strlen(bufcfs); kk++)  // cadena informativa resto
                {
                    int pp;
                    for ( pp = 0; pp < (int)strlen(txtcfs2); pp++)
                        txtcfs2[pp] = txtcfs2[pp + 1];
                    txtcfs2[pp] = 0;
                }
                strcat (txtcfs2, bufcfs);
                Form1->PCFS2->Caption = txtcfs2;
                //           Historico->Mhistory->Lines->Add(txtcfs2);
            }


            //------------------------------
            inimens = 0;
            poscfs = 0;   //fin analisis comando
        }
    }
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
----- Mensaje PC -> estacion: --------------------------------

	R : peticion datos crudos, una vez por cada (R)
	r : peticion datos calibrados, una vez por cada (r)
	S : lecturas continuas, cada 5 seg
	I : Pone a cero contador de anemometro movil.
	K : pone a cero contador del pluviometro
	H : reset software del sensor de humedad
		Q : reset de la estacion

		---  PARA CERRAR/ABRIR/CALENTAR ---
		N : nivel nublado para  cerrar 		 (N125), (N255) para desactivar
		L : nivel lluvia para cerrar 		 (L001), (L255)  "      "
		C : (Tamb - Trocio) para calentar, 0 para calentar forzado  (C005)
		V : velocidad viento para cerrar 	 (V020)
		F : nivel fuente ali. para cerrar 	 (F011)
		T : tiempo sin lecturas para cerrar  (T020), bloques de 5sg, (T255) para desactivar
		X : abrir 1 cerrar 0 abrir forzado 7 (X001)

		Las mismas letras pero en minuscula responden el valor actual configurado


		--- CALIBRACION ----
		A : constante anemometro mecanico para dar Km/h
		G : constante K1 anemometro termico para  Km/h
		D :     "     K2     "         "
		E : tomar offset zeners anemometro
		O : offset IR
		U : offset UV
		B : ofset barometro en mbar
		M : metros sobre nivel del mar
		P : constante pluviometro para dar litros ?

		------ AYUDA ------
		? : cadena con las iniciales de las variables

----- Mensaje estacion -> PC: respuesta a (r) -----------
(TCF Llu Nub Bar Plu Vel Dir lUV lIR Tem Hum Roc Anemome)
(TCF %   %  HPa  cl Km/h  º  %   %   ºC  %  ºC  Km/h)
(CA2 80 00 1020 040 112 278 101 078 113 138 112 1128)
---------------------------------------------------------

----- Mensaje estacion -> PC respuesta a (R): -----------

(0@0 010 020 112 040 112 088 101 078 113 138 112 112 -239 426 +074 1234567) <- ej. mensaje de la estacion
pos.5^  9^ 13^ 17^ 21^ 25^ 29^ 33^ 37^ 41^ 45^ 49^ 53^  58^ 62^  67^        <- posiciones en la cadena
1   2   3   4   5   6   7   8   9   10  11  12  13   14  15   16   17     <- bloques

bloque 1 - tres caracteres independientes, TECHO, CALENTADOR y ALIMENTACION
pos.0 ( : empieza el mensaje
pos.1   Salida Apertura Observatorio
		C : observatorio cerrado
		A : observatoro abrierto

pos.2   Salida Calentadores
		E : calentador encendido
		A : calentador apagado
		! : error de lectura del Sensor de humedad

pos.3 NIVEL ALIMENTACION: unidades de voltios, 0,1,2,3,4...
			0 <11v, 11v =< 1 <12v, 12 =< 2 < 13v, 13 =< 3 < 14v etc

bloque 2 - indicador lluvia o rocio (ch0 del conversor AD)
bloque 3 - indicador de nubes, (ch1 del conversor AD)
bloque 4 - barometro, (ch3 del conversor AD)
bloque 5 - contador del pluviometro de 000 a 999. Se pone a cero con "K"

bloque 6  -  veleta 1
bloque 7  -  veleta 2
bloque 8  -  veleta 3
bloque 9  -  veleta 4
bloque 10 -  veleta 5
bloque 11 -  veleta 6
bloque 12 -  sensor de luz IR
bloque 13 -  sensor de luz UV

bloque 14: ej. +239 : temperatura ºC x10
bloque 15:  "  426  : humedad relativa en % x10
bloque 16:  "  -012 : punto de rocio ºC x10
bloque 17:  " 1234567 : contador anemometro movil. Se pone a cero con "I"

pos. 74: )   Fin de mensaje
				---------------------------
*/

//==============================================================================
void ProcesarMeteo()
//==============================================================================
{
    // static char Meteo[200];
    static int  Dif_LX, Dif_LY;
    static double ValorX, ValorY;
    static int pluvio, pluvio_rel, pluvio_prev;
    static int AnemometroT,  SAnemometroT,  SDireccion;
    static float  AnemometroT2, SAnemometroT2;
    static int STemperatura_x10, SHumedad_x10, SRocio_x10;
    static float Presion_Kp, Presion_Bar, SPresion_Bar, Presion_BarAbs , SPresion_BarAbs;
    static int Direccion;
    static int sluzR, SsluzR;
    static int sluzUV, SsluzUV;
    static int Sslluvia, Ssnubes;
    static int sens;
    static int L[6];
    static int Dif_L[6];
    // static long VelVientoRelativa, AnemTotal, AnemTotalPrevio;
    static int AnemMec;
    static float AnemMecKmh, SAnemMecKmh;
    static bool abreparen;
    static int posmeteo, CuentasEma;
    int LongBuff, pos, kk;

    char Buff[2000];
    char aux2[6];
    char bufa[100];
    float t, h;

    // FILE *out;

    LongBuff = min(S1->nDatosMeteo, 500);
    S1->LeerMeteo(Buff, LongBuff);
    Buff[LongBuff] = 0;

    for (pos = 0; pos < LongBuff; pos++)
    {
        if (Buff[pos] == '(' )
        {
            abreparen = 1;
            posmeteo = 0;
        }
        if (abreparen == 1)
        {
            if ((Buff[pos] < ' ' ) || (Buff[pos] > '{'))
                Meteo[posmeteo] = '_';//caracter " "  indicando fuera de lo esperado
            else
                Meteo[posmeteo] = Buff[pos];
            posmeteo++;
            if (posmeteo > 200)
                posmeteo = 0;
        }

        if ((Buff[pos] == ')' ) && (posmeteo < 75)  )  // ha terminado el mensaje comandos
        {
            //          meteo_resp = true;
            if (EsperaMeteo > 2)
            {
                TDateTime FalloMeteo;
                FalloMeteo = Fecha.CurrentDateTime();
                Historico->Mhistory->Lines->Add("METEO responde OK  " + FalloMeteo);
            }
            EsperaMeteo = 0;

            Meteo[posmeteo] = 0;

            if (Meteo[1] != 'R')
            {
                if (fp != NULL)
                {
                    if (Form1->CBHistoriaMeteo->Checked == true)
                    {
                        Historico->Visible = true;
                        Historico->Mhistory->Lines->Add(Meteo);
                    }

                    strcpy(bufa, &Meteo[2]);
                    bufa[3] = 0;
                    int lim;
                    if (atoi(bufa) < 3)
                        lim = 1;
                    else
                        lim = (atoi(bufa) * 100) / 255;

                    if (Meteo[1] == 'L')
                        fp->ELimiteLluvia->Text = lim;// bufa;
                    else if (Meteo[1] == 'N')
                        fp->ELimiteNubes->Text = lim;//bufa;
                    else if (Meteo[1] == 'V')
                        fp->ELimiteKmh->Text = bufa;
                    else if (Meteo[1] == 'T')
                        fp->ELimiteEspera->Text = bufa;
                    else if (Meteo[1] == 'F')
                        fp->ELimiteFuente->Text = bufa;
                    else if (Meteo[1] == 'C')
                        fp->ELimiteRocio->Text = bufa;
                }
            }
            posmeteo = 0;
            abreparen = 0;
        }
        else if ((Buff[pos] == ')' ) && (posmeteo == 83)  )  // ha terminado el mensaje datos
        {
            Meteo[posmeteo] = 0;
            posmeteo = 0;
            abreparen = 0;
            Form1->Lemav2->Visible = true;
            CuentaMensMeteo++;
            //     Form1->Weather1->MensajeCor =(BSTR)(Meteo);
        }
        else if ((Buff[pos] == ')' ) && (posmeteo == 75)  )  // ha terminado el mensaje datos
        {
            if (EsperaMeteo > 2)
            {
                TDateTime FalloMeteo;
                FalloMeteo = Fecha.CurrentDateTime();
                Historico->Mhistory->Lines->Add("METEO responde OK  " + FalloMeteo);
            }
            EsperaMeteo = 0;

            //          meteo_resp = true;
            Meteo[posmeteo] = 0;
            posmeteo = 0;
            abreparen = 0;

            CuentaMensMeteo++;

            if (Meteo[3] >= 0x39)
            {
                //            Form1->Memo1->Lines->Add(Meteo);
                Historico->Mhistory->Lines->Add(Meteo);
                return;           //no se hace nada porque es un mensaje de ayuda
            }

            //          Form1->Paux->Caption = Meteo;
            if (Form1->CBHistoriaMeteo->Checked == true)
                Historico->Mhistory->Lines->Add(Meteo);

            if (Meteo[2] == 'E') //calentador activo
            {
                Form1->PCalentar->Caption = " Calentador ON";
                Form1->PCalentar->Color = clYellow;
            }
            else
            {
                Form1->PCalentar->Caption = " Calentador OFF";
                Form1->PCalentar->Color = clBtnFace;
            }

            if (Meteo[1] == 'A') //Techo abierto
            {
                Form1->PTecho->Caption = "Obs. Abierto";
                Form1->PTecho->Color = clSkyBlue;
                Form1->BBAbrirObs->Caption = "Cerrar";
                //            Form1->Sbit3->Brush->Color = clRed;
            }
            else
            {
                Form1->PTecho->Caption = "Obs. Cerrado";
                Form1->PTecho->Color = clBtnFace;
                Form1->BBAbrirObs->Caption = "Abrir";
            }


            if (Meteo[2] == '!') //el sensor de humead temperatura no responde
            {
                Form1->PTempAmbiente->Caption = "  --";
                Form1->PHumedad->Caption = "  --";
                Form1->PPuntoRocio->Caption = "  --";
            }
            else
            {
                // temperatura
                aux2[0] = Meteo[53];
                aux2[1] = Meteo[54];
                aux2[2] = Meteo[55];
                aux2[3] = Meteo[56];
                aux2[4] = 0;
                Temp_x10 = atoi(aux2);
                aux2[4] = Meteo[56];
                aux2[3] = '.';
                aux2[5] = 0;
                Form1->PTempAmbiente->Caption = aux2;
                STemperatura_x10 +=  Temp_x10;

                //Humedad relativa
                aux2[0] = Meteo[58];
                aux2[1] = Meteo[59];
                aux2[2] = Meteo[60];
                aux2[3] = 0;
                Humedad_x10 = atoi(aux2);
                //       h = AnsiString(aux2).ToInt() / 10.0;
                if (h <= 0) h = 1;
                aux2[2] = '.';
                aux2[3] = Meteo[60];
                aux2[4] = '%';
                aux2[5] = 0;
                Form1->PHumedad->Caption = aux2;
                SHumedad_x10 += Humedad_x10;

                //punto de rocio
                aux2[0] = Meteo[62];
                aux2[1] = Meteo[63];
                aux2[2] = Meteo[64];
                aux2[3] = Meteo[65];
                aux2[4] = 0;
                Rocio_x10 = atoi(aux2);
                aux2[4] = Meteo[65];
                aux2[3] = '.';
                aux2[5] = 0;
                Form1->PPuntoRocio->Caption = aux2;
                SRocio_x10 += Rocio_x10;
            }

            //Sensor de lluvia
            aux2[0] = Meteo[5];
            aux2[1] = Meteo[6];
            aux2[2] = Meteo[7];
            aux2[3] = 0;
            //        slluvia = atoi(aux2);
            //        Form1->PLluvia->Caption = (slluvia*100)/255;
            slluvia = 255 - atoi(aux2);
            sprintf(aux2, "%03.1f", (slluvia * 100) / 255.0);
            Form1->PLluvia->Caption = aux2;
            Sslluvia += slluvia;

            //Pluviometro
            aux2[0] = Meteo[17];
            aux2[1] = Meteo[18];
            aux2[2] = Meteo[19];
            aux2[3] = 0;
            pluvio_rel = atoi(aux2);
            if ( pluvio_rel > pluvio_prev )
                pluvio += pluvio_rel - pluvio_prev;
            pluvio_prev = pluvio_rel;
            //          sprintf(aux2,"%04.2f",pluvio*0.0842);  //0.421 pluviometro antiguo
            sprintf(aux2, "%04.2f", pluvio * (confEMA.kpluvio / 1000.0)); //0.421 pluviometro antiguo
            Form1->PPluviometro->Caption = aux2;

            //Sensor de nubes
            aux2[0] = Meteo[9];
            aux2[1] = Meteo[10];
            aux2[2] = Meteo[11];
            aux2[3] = 0;
            snubes = 255 - atoi(aux2);
            //         snubes = atoi(aux2);
            sprintf(aux2, "%03.1f", (snubes * 100) / 255.0);
            Form1->PNublados->Caption = aux2;
            //          Form1->PNublados->Caption = (snubes*100)/255;
            Ssnubes += snubes;

            //Nivel alimentacion
            aux2[0] = Meteo[3];
            aux2[1] = 0;
            VFuente = ((int)Meteo[3] - 0x30) + 10; //
            if (VFuente < 11) Form1->PVFuente->Color = clRed;
            else Form1->PVFuente->Color = clBtnFace;
            Form1->PVFuente->Caption = IntToStr(VFuente) + " v";
            /*
            if (VFuente/9.13 < 9.6) Form1->PVFuente->Color = clRed; //9.13 ajusta la lectura
            else Form1->PVFuente->Color = clBtnFace;
            Form1->PVFuente->Caption = FloatToStrF(VFuente/9.13, ffNumber, 3,1 ) + " v";
            */

            //Sensor de luz IR
            aux2[0] = Meteo[45];
            aux2[1] = Meteo[46];
            aux2[2] = Meteo[47];
            aux2[3] = 0;
            sluzR = atoi(aux2);
            sluzR = sluzR + (confEMA.luzIR_ofset * 255 / 100);
            Form1->PLuzR->Caption = ((sluzR * 100) / 255);
            SsluzR += sluzR;

            //Sensor de luz UV
            aux2[0] = Meteo[49];
            aux2[1] = Meteo[50];
            aux2[2] = Meteo[51];
            aux2[3] = 0;
            //          int slluvia = (aux2[0]-0x30)*100 + (aux2[1]-0x30)*10 + (aux2[2]-0x30);
            sluzUV = atoi(aux2);
            sluzUV = sluzUV + (confEMA.luzUV_ofset * 255 / 100);
            Form1->PLuzUV->Caption = (sluzUV * 100) / 255 ;
            SsluzUV += sluzUV;

            //Barometro
            aux2[0] = Meteo[13];
            aux2[1] = Meteo[14];
            aux2[2] = Meteo[15];
            aux2[3] = 0;
            Presion_Kp = atoi(aux2) * 0.216 + 66.11;  //presion en Kpascales
            /* Calculo de la presion normalizada al nivel del mar:
            		P = (P0) e^[-(g/(RT)) * (Z — Z0)
            	P = pressure at an unknown altitude,
            	P0 = pressure at a known altitude,
            	e = a constant,
            	g = gravitational constant 9.8 (m/s^2),
            	R = dry air constant 287 J/(kg*K),
            	T = temperature at unknown elevation in Kelvin,
            	Z = unknown altitude in meters,
            	Z0 = known altitude also in meters. */
            //          float KT = (9.8/(287*273)) * confEMA.bar_altura;
            float KTok = (9.8 / (287 * (273 + Temp_x10 / 10))) * confEMA.bar_altura;

            Presion_Bar = (Presion_Kp * exp(KTok) * 10) + confEMA.bar_ofset; //6´presion en hectopascales menos offset
            SPresion_Bar += Presion_Bar;
            //Form1->PBarometro->Caption = FloatToStrF(Presion_Bar, ffNumber, 4,1);
            Presion_BarAbs = Presion_Kp * 10 + confEMA.bar_ofset;
            SPresion_BarAbs += Presion_BarAbs;//Presion_BarAbs;

            //Anemometro mecanico
            aux2[0] = Meteo[67];
            aux2[1] = Meteo[68];
            aux2[2] = Meteo[69];
            aux2[3] = Meteo[70];
            aux2[4] = Meteo[71];
            aux2[5] = Meteo[72];
            aux2[6] = Meteo[73];
            aux2[7] = 0;
            AnemMec = atoi(aux2);
            AnemMecKmh = (AnemMec * (60 / 5) * confEMA.kmecanico) / 1000.0;
            sprintf(aux2, "%03.1f", AnemMecKmh);  //0.421 pluviometro antiguo
            Form1->PVelViento->Caption = aux2;

            SAnemMecKmh += AnemMecKmh;
            /*          if (AnemTotal < AnemTotalPrevio)
            			AnemTotalPrevio = 0;
            		VelVientoRelativa = AnemTotal - AnemTotalPrevio;
            		if (VelVientoRelativa > 1000)
            			VelVientoRelativa =0;
            		AnemTotalPrevio = AnemTotal;
            		VelVientoRelativa =  VelVientoRelativa * (confEMA.kmecanico/1000.0); //0.2; // conversion a Km/h
            		Form1->PVelViento->Caption = VelVientoRelativa;
            */

            //-----------------------------------------------------------------
            //----------Temperatura-velocidad del viento sumatorio-------------
            //-----------------------------------------------------------------

            //extraccion de lecturas desde la cadena
            kk = 21; //posicion donde empiezan las lecturas en la cadena
            for (sens = 0; sens < 6; sens++)
            {
                aux2[0] = Meteo[kk];
                kk++;
                aux2[1] = Meteo[kk];
                kk++;
                aux2[2] = Meteo[kk];
                kk++;
                aux2[3] = 0;
                L[sens] = atoi(aux2);
                kk++;
            }

            // extraccion de diferencias de lecturas
            for (sens = 0; sens < 6; sens++)
                //Dif_L[sens] = L[sens] - Referencia[sens];
                Dif_L[sens] = L[sens] - confEMA.RefZener[sens];

            Dif_LX = int(Dif_L[0] * 1 + Dif_L[1] * 0.866 - Dif_L[2] * 0.866 //cos
                         - Dif_L[3] * 1 - Dif_L[4] * 0.866 + Dif_L[5] * 0.866);
            Dif_LY = int(Dif_L[0] * 0 + Dif_L[1] * 0.5 + Dif_L[2] * 0.5 //sen
                         + Dif_L[3] * 0 - Dif_L[4] * 0.5 - Dif_L[5] * 0.5);


            // se resta a la lectura la referencia u ofset.
            ValorX = Dif_LX;
            ValorY = Dif_LY;

            AnemometroT = int(sqrt(pow(ValorX, 2) + pow(ValorY, 2))); // amplitud de la medida

            //Anemometro termico suma vectorial
            //          Form1->PVelVientoT->Caption = AnemometroT;
            SAnemometroT = SAnemometroT + AnemometroT;

            //Anemometro termico suma modulos
            AnemometroT2 = int(Dif_L[0] + Dif_L[1] + Dif_L[2] + Dif_L[3] * 1 + Dif_L[4] + Dif_L[5]);
            //  AnemometroT2 = AnemometroT2/2; //para que normalmente entre en la grafica normalizada a 100

            //          Form1->PvelOmni->Caption = FloatToStrF( exp(0.012*AnemometroT2 + 0.1345), ffNumber, 3,1); // conversion a Km/h
            //          AnemometroT2 = ( Form1->PvelOmni->Caption);

            //        AnemometroT2 =  exp(0.012*AnemometroT2 + 0.1345); // conversion a Km/h
            AnemometroT2 =  exp((confEMA.k1termico / 10000.0) * AnemometroT2 + confEMA.k2termico / 10000.0); // conversion a Km/h
            //        Form1->PvelOmni->Caption = FloatToStrF(AnemometroT2, ffNumber, 3,1);
            sprintf(aux2, "%03.1f", AnemometroT2);  //0.421 pluviometro antiguo
            Form1->PvelOmni->Caption = aux2;

            SAnemometroT2 += AnemometroT2;
            //Veleta
            if (AnemometroT2 > 5)
            {

                if ((ValorX != 0) || (ValorY != 0))  // angulo de 0 a 180 y de 0 a -180
                    Direccion = (atan2(ValorY, ValorX)) * (180 / 3.1416);
                if (Direccion < 0)
                    Direccion = 360 + Direccion;   // angulo de 0 a 360

                Form1->PDirViento->Caption = Direccion;

                if ((Direccion > 337) || (Direccion <= 22))
                {
                    Form1->PDirNSEO->Caption = " N";
                    Direccion = 1;
                }
                else if ((Direccion > 22) && (Direccion <= 67))
                    Form1->PDirNSEO->Caption = "NE";
                else if ((Direccion > 67) && (Direccion <= 112))
                    Form1->PDirNSEO->Caption = " E";
                else if ((Direccion > 112) && (Direccion <= 157))
                    Form1->PDirNSEO->Caption = "SE";
                else if ((Direccion > 157) && (Direccion <= 202))
                    Form1->PDirNSEO->Caption = " S";
                else if ((Direccion > 202) && (Direccion <= 247))
                    Form1->PDirNSEO->Caption = "SO";
                else if ((Direccion > 247) && (Direccion <= 292))
                    Form1->PDirNSEO->Caption = " O";
                else if ((Direccion > 292) && (Direccion <= 337))
                    Form1->PDirNSEO->Caption = "NO";
            }
            SDireccion = SDireccion + Direccion;

            if (Timer60sg)
            {
                Timer60sg = false;
                //
                /*             aux2[0]= Meteo[67];
                			aux2[1]= Meteo[68];
                			aux2[2]= Meteo[69];
                			aux2[3]= Meteo[70];
                			aux2[4]= Meteo[71];
                			aux2[5]= Meteo[72];
                			aux2[6]= Meteo[73];
                			aux2[7]= 0;
                			AnemTotal = atoi(aux2);
                			if (AnemTotal < AnemTotalPrevio)
                				AnemTotalPrevio = 0;
                			VelVientoRelativa = AnemTotal - AnemTotalPrevio;
                			if (VelVientoRelativa > 1000)
                				VelVientoRelativa =0;
                			AnemTotalPrevio = AnemTotal;
                			VelVientoRelativa =  VelVientoRelativa * (confEMA.kmecanico/1000.0); //0.2; // conversion a Km/h
                			Form1->PVelViento->Caption = VelVientoRelativa;
                */
                if (CuentaMensMeteo > 0)
                {
                    Form1->PBarometro->Caption = FloatToStrF((SPresion_Bar / CuentaMensMeteo), ffNumber, 5, 1);
                    Form1->PBarometroAbs->Caption = FloatToStrF(SPresion_BarAbs / CuentaMensMeteo, ffNumber, 4, 1);

                    for (kk = 0; kk < 1439; kk++)  //desplazamiento de los datos
                    {
                        grafico24h[kk].Dia = grafico24h[kk + 1].Dia;
                        grafico24h[kk].Hora = grafico24h[kk + 1].Hora;
                        grafico24h[kk].LeturasAnem = grafico24h[kk + 1].LeturasAnem;
                        grafico24h[kk].LeturasAnemT2 = grafico24h[kk + 1].LeturasAnemT2;
                        grafico24h[kk].LeturasAnemT = grafico24h[kk + 1].LeturasAnemT;
                        grafico24h[kk].LeturasDireccion = grafico24h[kk + 1].LeturasDireccion;
                        grafico24h[kk].LeturasTemp = grafico24h[kk + 1].LeturasTemp;
                        grafico24h[kk].LeturasRocio = grafico24h[kk + 1].LeturasRocio;
                        grafico24h[kk].LeturasPluvio = grafico24h[kk + 1].LeturasPluvio;
                        grafico24h[kk].LeturasNubes = grafico24h[kk + 1].LeturasNubes;
                        grafico24h[kk].LeturasLluvia = grafico24h[kk + 1].LeturasLluvia;
                        grafico24h[kk].LeturasHumedad = grafico24h[kk + 1].LeturasHumedad;
                        grafico24h[kk].LeturasBarometro = grafico24h[kk + 1].LeturasBarometro;
                        grafico24h[kk].LeturasBarometroAbs = grafico24h[kk + 1].LeturasBarometroAbs;
                        grafico24h[kk].LeturasLuzUV = grafico24h[kk + 1].LeturasLuzUV;
                        grafico24h[kk].LeturasLuzR = grafico24h[kk + 1].LeturasLuzR;
                    }

                    //lectura de nuevos valores
                    //              if(CuentaMensMeteo >0)
                    //            {
                    //                grafico24h[1439].Dia = DateToStr(Date());
                    //                grafico24h[1439].Hora = TimeToStr(Time());
                    grafico24h[1439].Dia = Date();
                    grafico24h[1439].Hora = Time();
                    //               grafico24h[1439].LeturasAnem = VelVientoRelativa;
                    grafico24h[1439].LeturasAnem = SAnemMecKmh / CuentaMensMeteo;
                    grafico24h[1439].LeturasAnemT2 = SAnemometroT2 / CuentaMensMeteo;
                    if (grafico24h[1439].LeturasAnemT2 > 700 ) grafico24h[1439].LeturasAnemT2 = 0;
                    if (grafico24h[1439].LeturasAnemT2 < 0 ) grafico24h[1439].LeturasAnemT2 = 0;
                    grafico24h[1439].LeturasAnemT = SAnemometroT / CuentaMensMeteo;
                    grafico24h[1439].LeturasDireccion = ((SDireccion / CuentaMensMeteo) / 360.0) * 100;
                    grafico24h[1439].LeturasTemp = (STemperatura_x10 / CuentaMensMeteo) / 10.0;
                    grafico24h[1439].LeturasRocio = (SRocio_x10 / CuentaMensMeteo) / 10.0;
                    grafico24h[1439].LeturasPluvio = (pluvio * (confEMA.kpluvio / 1000.0)); // en litros
                    grafico24h[1439].LeturasNubes = ((Ssnubes / CuentaMensMeteo) * 100) / 255.0;
                    grafico24h[1439].LeturasLluvia = ((Sslluvia / CuentaMensMeteo) * 100) / 255.0;
                    grafico24h[1439].LeturasHumedad = (SHumedad_x10 / CuentaMensMeteo) / 10.0;
                    grafico24h[1439].LeturasBarometro = SPresion_Bar / CuentaMensMeteo;
                    grafico24h[1439].LeturasBarometroAbs = SPresion_BarAbs / CuentaMensMeteo;
                    grafico24h[1439].LeturasLuzUV = ((SsluzUV / CuentaMensMeteo) * 100) / 255.0;
                    grafico24h[1439].LeturasLuzR = ((SsluzR / CuentaMensMeteo) * 100) / 255.0;
                    // }
                    //reset contadores
                    STemperatura_x10 = 0;
                    SHumedad_x10 = 0;
                    SRocio_x10 = 0;
                    SAnemMecKmh = 0;
                    SAnemometroT2 = 0;
                    SAnemometroT = 0;
                    SDireccion = 0;
                    SPresion_Bar = 0;
                    SPresion_BarAbs = 0;
                    Sslluvia = 0;
                    SsluzR = 0;
                    SsluzUV = 0;
                    Ssnubes = 0;
                    CuentaMensMeteo = 0;

                    DibujaGraficas();
                    CuentasEma++;
                    if (CuentasEma >= 60) //si se han guardado 60 apuntes se guardan a fichero .txt
                    {
                        CuentasEma = 0;
                        FicheroEma();
                    }
                } //fin if CuentaMensMeteo > 0
            } //fin if 60sg
        }  // fin del if posmeteo == 75
    } // fin del for
}

//-------------------------------------------------------------------
//Se va guardando fichero mensual con los datos leidos de la estacion
//-------------------------------------------------------------------

//==============================================================================
// Leer datos EMAv2 via COM del programa EMA
void EMAv2COM()
//==============================================================================
{
    char aux[100];
    AnsiString cadEma;

    //   Form1->Weather1->Connected() = 1;
    //    if(Form1->Weather1->Connected){  }


    //   Historico->Mhistory->Lines->Add (Form1->Weather1->Name);
    cadEma = Form1->Weather1->MensajeEma;
    if (cadEma.Length() > 0)
        try
        {
            cadEma =  cadEma.SubString(2, 1) ;
            if (cadEma == 'A')       //Techo abierto
            {
                Form1->PTecho->Caption = "Obs. Abierto";
                Form1->PTecho->Color = clSkyBlue;
                Form1->BBAbrirObs->Caption = "Cerrar";
            }
            else if (cadEma == 'C')
            {
                Form1->PTecho->Caption = "Obs. Cerrado";
                Form1->PTecho->Color = clBtnFace;
                Form1->BBAbrirObs->Caption = "Abrir";
            }
        }
        catch (...)
        {
            Form1->Lemav2->Caption = "Fallo EMA";
            return;
        }
    Form1->Lemav2->Caption = "EMAv2COM";
    Form1->Lemav2->Visible = true;
    Form1->BCalibrarMeteo->Visible = false;

    Temp_x10 = 10 * Form1->Weather1->AmbientTemperature;
    //   Form1->PTempAmbiente->Caption = FloatToStrF(Form1->Weather1->AmbientTemperature, ffNumber, 4,1);
    Form1->PTempAmbiente->Caption = Temp_x10 / 10.0;
    Form1->PVelViento->Caption = Form1->Weather1->WindVelocity;
    Form1->PDirViento->Caption = Form1->Weather1->WindDirection;
    Form1->PLuzR->Caption = FloatToStrF(Form1->Weather1->SkyMagnitude, ffNumber, 4, 2);
    sprintf(aux, "%03.1f", 100 * Form1->Weather1->Clouds);
    Form1->PNublados->Caption = aux;
    Rocio_x10 = 10 * Form1->Weather1->DewPoint;
    //   Form1->PPuntoRocio->Caption = FloatToStrF(Form1->Weather1->DewPoint, ffNumber, 4,1);
    Form1->PPuntoRocio->Caption = Rocio_x10 / 10.0;
    Humedad_x10 = 10 * Form1->Weather1->RelativeHumidity;
    // Form1->PHumedad->Caption = FloatToStrF(Form1->Weather1->RelativeHumidity, ffNumber, 4,1);
    Form1->PHumedad->Caption = Humedad_x10 / 10.0;
    // Form1->PPluviometro->Caption = Weather1->;
    if (Form1->Weather1->Precipitation)
        Form1->PLluvia->Caption = 50;
    else
        Form1->PLluvia->Caption = 0;
    Form1->PBarometro->Caption =   FloatToStrF(Form1->Weather1->BarometricPressure, ffNumber, 5, 1);
    if (Form1->Weather1->Safe)
    {
        Form1->BBAbrirObs->Font->Color =  clBlack;
        Fprog->LmeteoSafe->Font->Color =  clBlue;
        Fprog->LmeteoSafe->Caption = "Meteo SEGURA";
    }
    else
    {
        Form1->BBAbrirObs->Font->Color = clRed;
        Fprog->LmeteoSafe->Font->Color =  clRed;
        Fprog->LmeteoSafe->Caption = "Meteo ADVERSA";
    }
    Form1->PDirViento->Caption = Form1->Weather1->WindDirection;
    //Form1->PVFuente->Caption = (int)(Form1->Weather1->MensajeEma[3])/10.0;
    Form1->PVFuente->Caption = (int)(0);

    //    Historico->Mhistory->Lines->Add(Form1->Weather1->BarometricPressure);
}

//==============================================================================
// Creacion fichero de datos EMA
void FicheroEma()
//==============================================================================
{
    int k, sens;
    int cuenta = 0;
    unsigned int p;
    char auxi[300], aux[100], nombre[100], fecha[32];
    FILE *fich;

    strcpy(nombre, confEMA.direc_datos);
    strcat(nombre, "_");
    strcpy(fecha, &(DateToStr(Date()).c_str())[3]);
    strcat(nombre, fecha);
    strcat(nombre, ".txt");

    for ( p = 0; p < strlen(nombre); p++)
    {
        if ((nombre[p] == '/') || ( nombre[p] == '-' ))
            nombre[p] = '_';
    }

    // si no existe el fichero se crea poniendo primero la cabecera.
    if ((FileExists(nombre)) == 0)
    {
        if ((fich = fopen(nombre, "at")) != NULL)
        {
            //memset(auxi, 0, sizeof(auxi));
            strcpy(auxi, "Dia\t Hora\t Temp\t H rel.\t Rocio\t Nubes\t Lluvia\t Anem\t Anem T\t Dir\t Pluvio\t Pres\t P.Abs\t LuzIR\t LuzUV\r");

            fwrite(auxi, strlen(auxi), 1, fich);
            fclose(fich);
            Historico->Mhistory->Lines->Add("Creado: " + AnsiString(nombre));
        }
    }

    //  Historico->Mhistory->Lines->Add(nombre);

    if ((fich = fopen(nombre, "at")) != NULL)
    {
        for (k = (1439 - 59); k <= 1439; k++) // lee ultimos 60 apuntes, una hora si T2 esta a 60sg
        {
            meteosuma.LeturasTemp += grafico24h[k].LeturasTemp;
            meteosuma.LeturasHumedad += grafico24h[k].LeturasHumedad;
            meteosuma.LeturasRocio += grafico24h[k].LeturasRocio;
            meteosuma.LeturasNubes += grafico24h[k].LeturasNubes;
            meteosuma.LeturasLluvia += grafico24h[k].LeturasLluvia;
            meteosuma.LeturasAnem += grafico24h[k].LeturasAnem;
            meteosuma.LeturasAnemT += grafico24h[k].LeturasAnemT;
            meteosuma.LeturasDireccion += grafico24h[k].LeturasDireccion * 360 / 100;
            meteosuma.LeturasPluvio += grafico24h[k].LeturasPluvio;
            meteosuma.LeturasBarometro += grafico24h[k].LeturasBarometro;
            meteosuma.LeturasBarometroAbs += grafico24h[k].LeturasBarometroAbs;
            meteosuma.LeturasLuzR += grafico24h[k].LeturasLuzR;
            meteosuma.LeturasLuzUV += grafico24h[k].LeturasLuzUV;

            cuenta++;
            if (cuenta >= 5 )   //se guardan datos cada 5 minutos, promediando 5 muestras
            {

                auxi[0] = 0;

                strcpy(auxi, DateToStr(grafico24h[k].Dia).c_str());
                strcat(auxi, "\t");

                strcat(auxi, TimeToStr(grafico24h[k].Hora).c_str());
                strcat(auxi, "\t");

                sprintf(aux, "%04.1f\t", meteosuma.LeturasTemp / 5);
                strcat(auxi, aux);

                sprintf(aux, "%04.1f\t", meteosuma.LeturasHumedad / 5);
                strcat(auxi, aux);

                sprintf(aux, "%04.1f\t", meteosuma.LeturasRocio / 5);
                strcat(auxi, aux);

                sprintf(aux, "%04.1f\t", meteosuma.LeturasNubes / 5);
                strcat(auxi, aux);

                sprintf(aux, "%04.1f\t", meteosuma.LeturasLluvia / 5);
                strcat(auxi, aux);

                sprintf(aux, "%04.1f\t", meteosuma.LeturasAnem / 5);
                strcat(auxi, aux);

                sprintf(aux, "%04.1f\t", meteosuma.LeturasAnemT / 5);
                strcat(auxi, aux);

                sprintf(aux, "%04.1f\t", meteosuma.LeturasDireccion / 5);
                strcat(auxi, aux);

                sprintf(aux, "%04.1f\t", meteosuma.LeturasPluvio / 5);
                strcat(auxi, aux);

                sprintf(aux, "%04.1f\t", meteosuma.LeturasBarometro / 5);
                strcat(auxi, aux);
                sprintf(aux, "%04.1f\t", meteosuma.LeturasBarometroAbs / 5);
                strcat(auxi, aux);

                sprintf(aux, "%04.1f\t", meteosuma.LeturasLuzR / 5);
                strcat(auxi, aux);

                sprintf(aux, "%04.1f\r", meteosuma.LeturasLuzUV / 5);
                strcat(auxi, aux);

                cuenta = 0;
                meteosuma.LeturasTemp = 0;
                meteosuma.LeturasHumedad = 0;
                meteosuma.LeturasRocio = 0;
                meteosuma.LeturasNubes = 0;
                meteosuma.LeturasLluvia = 0;
                meteosuma.LeturasAnem = 0;
                meteosuma.LeturasAnemT = 0;
                meteosuma.LeturasDireccion = 0;
                meteosuma.LeturasPluvio = 0;
                meteosuma.LeturasBarometro = 0;
                meteosuma.LeturasBarometroAbs = 0;
                meteosuma.LeturasLuzR = 0;
                meteosuma.LeturasLuzUV = 0;


                for ( p = 0; p < strlen(auxi); p++) // cambia puntos por comas para que excel lo entienda
                {
                    if (auxi[p] == '.')
                        auxi[p] = ',';
                }
                fwrite(auxi, strlen(auxi), 1, fich);
            }
        }
        fclose(fich);
    }
    //  CopyFile(nombre, "mes_actual.txt",  NULL);
    //  CopyFile(nombre, "c:\\inetpub\\wwwroot\\mes_actual.txt",  NULL);
    //  CopyFile(nombre, "mes_actual.txt",  NULL);
}

//==============================================================================
// Crea o actualiza las graficas meteorologicas
void DibujaGraficas()
//==============================================================================
{
    int kk;

    //borrado de la grafica anterior
    FGraficas->AreaSeries1->Clear();
    FGraficas->Series2->Clear();

    FGraficas->Series1->Clear();
    FGraficas->Series7->Clear();
    FGraficas->Series3->Clear();
    FGraficas->Series8->Clear();

    FGraficas->AreaSeries2->Clear();

    FGraficas->Series5->Clear();
    FGraficas->Series4->Clear();
    FGraficas->Series6->Clear();
    FGraficas->Series9->Clear();
    FGraficas->Series10->Clear();

    FGraficas->SeriesBarometro->Clear();
    FGraficas->Series11->Clear();

    //creacion grafica actual
    for (kk = 0; kk <= 1439; kk++)
    {
        FGraficas->AreaSeries1->AddXY(kk, grafico24h[1439 - kk].LeturasTemp, grafico24h[1439 - kk].Hora, clRed);
        FGraficas->Series2->AddXY(kk, grafico24h[1439 - kk].LeturasRocio, grafico24h[1439 - kk].Hora, clGreen);

        FGraficas->Series1->AddXY(kk, grafico24h[1439 - kk].LeturasAnem, grafico24h[1439 - kk].Hora, clBlue);
        FGraficas->Series7->AddXY(kk, grafico24h[1439 - kk].LeturasAnemT2, grafico24h[1439 - kk].Hora , clGreen);
        FGraficas->Series3->AddXY(kk, grafico24h[1439 - kk].LeturasAnemT, grafico24h[1439 - kk].Hora, clRed);
        FGraficas->Series8->AddXY(kk, grafico24h[1439 - kk].LeturasDireccion, grafico24h[1439 - kk].Hora, clYellow);

        FGraficas->AreaSeries2->AddXY(kk, grafico24h[1439 - kk].LeturasPluvio, grafico24h[1439 - kk].Hora, clRed);

        FGraficas->Series5->AddXY(kk, grafico24h[1439 - kk].LeturasNubes, grafico24h[1439 - kk].Hora, clGray);
        FGraficas->Series4->AddXY(kk, grafico24h[1439 - kk].LeturasLluvia, grafico24h[1439 - kk].Hora, clRed);
        FGraficas->Series6->AddXY(kk, grafico24h[1439 - kk].LeturasHumedad, grafico24h[1439 - kk].Hora, clBlue);
        FGraficas->Series9->AddXY(kk, grafico24h[1439 - kk].LeturasLuzUV, grafico24h[1439 - kk].Hora, clGreen);
        FGraficas->Series10->AddXY(kk, grafico24h[1439 - kk].LeturasLuzR, grafico24h[1439 - kk].Hora, clGreen);

        FGraficas->SeriesBarometro->AddXY(kk, grafico24h[1439 - kk].LeturasBarometro, grafico24h[1439 - kk].Hora, clBlue);
        FGraficas->Series11->AddXY(kk, grafico24h[1439 - kk].LeturasBarometroAbs, grafico24h[1439 - kk].Hora, clBlue);
    }
}
/*
EnvioLX #:Mn#  18:13:49
EnvioLX #:Qn#  18:13:52
EnvioLX #:GR##:GD#  18:13:57
LXdice: 19:30.2#+01ß02#
EnvioLX #:GR##:GD#  18:14:02
LXdice: 19:30.2#+01ß02#
EnvioLX #:GR##:GD#  18:14:07

// pedir AR DEC     #:GR#:GD#
// pedir Alt Azimut #:GZ#:GA#
*/

//==============================================================================
void ProcesarLX200()
//==============================================================================
{
    char Aux[20];
    //int nRa = 0, nDe = 0;
    char BuffLX[2000];
    char aux[300], cad[10];
    int Long, pos;

    Long = min(S1->nDatosLX200, 500);
    S1->LeerLX200(BuffLX, Long);
    BuffLX[Long] = 0;

    if (Long > 3)
    {
        if ( Form1->CBver_envio_lx->Checked == true)
        {
            TimeRxLX200 = Fecha.CurrentTime();
            Historico->Mhistory->Lines->Add( AnsiString(TimeRxLX200) + "->" + AnsiString(BuffLX) );
        }
    }

    if (Long == 29)  //Espera una cadena completa con AR, DEC, Alt y Az.
    {
        LXresponde = true;   //las fragmentadas por el momento no se usan
        //AR y Dec del telescopio en decimal
        Aux[0] = BuffLX[0];
        Aux[1] = BuffLX[1];
        Aux[2] = 0;
        nRAHour  = atof(Aux);  //Hora RA
        Aux[0] = BuffLX[3];
        Aux[1] = BuffLX[4];
        Aux[2] = BuffLX[5];
        Aux[3] = BuffLX[6];
        Aux[4] = 0;
        dRAMin  = atof(Aux);  //Minutos RA
        tRa = 15.0 * ( nRAHour + dRAMin / 60.0);

        Aux[0] = BuffLX[8];
        Aux[1] = BuffLX[9];
        Aux[2] = BuffLX[10];
        Aux[3] = 0;
        nDecDeg = atof(Aux);
        Aux[0] = BuffLX[12];
        Aux[1] = BuffLX[13];
        Aux[2] = 0;
        nDecMin = atof(Aux);
        if (BuffLX[8] == '+')
            tDe = nDecDeg + (nDecMin / 60.0);
        else
        {
            tDe = nDecDeg - (nDecMin / 60.0);
            // nDecMin = -nDecMin;
        }
        sprintf(cad, "%003.2f", tRa);
        Form1->LRAgrados->Caption =  AnsiString(cad) + "º";
        CoordCal = cad;
        sprintf(cad, "%003.2f", tDe);
        Form1->LDecgrados->Caption = AnsiString(cad);   //sale -10.32 en vez de -11º41'
        CoordCal = ";" + CoordCal + ";" + (AnsiString)(cad);
        //Alt y Azimut del Telescopio en decimal
        Aux[0] = BuffLX[15];
        Aux[1] = BuffLX[16];
        Aux[2] = BuffLX[17];
        Aux[3] = 'º';
        tAlt = atof(Aux);
        Aux[0] = BuffLX[19];
        Aux[1] = BuffLX[20];
        Aux[2] = 0;
        if (BuffLX[15] == '+')
            tAlt =  tAlt + atof(Aux) / 60.0;
        else
            tAlt =  -(tAlt + atof(Aux) / 60.0);
        sprintf(cad, "%003.2f", tAlt);
        CoordCal = CoordCal + ";" + (AnsiString)(cad);

        Aux[0] = BuffLX[22];
        Aux[1] = BuffLX[23];
        Aux[2] = BuffLX[24];
        Aux[3] = 0;
        float AzGrados = atof(Aux);
        Aux[0] = BuffLX[26];
        Aux[1] = BuffLX[27];
        Aux[2] = 0;
        float AzMin = atof(Aux);
        float Azi = AzGrados + (AzMin / 60.0);
        if (Azi >= 180) Azi = Azi - 180;        //El LX200 tiene origen de
        else Azi = Azi + 180;
        sprintf(cad, "%003.2f", Azi);

        Form1->LAzimutRx->Caption = "Az: " + AnsiString(cad);
        sprintf(cad, "%003.2f", Azi);
        CoordCal = CoordCal + ";" + (AnsiString)(cad);

        //Altura y Azimut Calculada partir de AR y Dec del telescopio en decimal
        double Altura = CalAltura(tRa, tDe); //(double ARec, double DEC)
        sprintf(cad, "%003.2f", Altura);
        Form1->LAltura->Caption = "Alt: " + AnsiString(cad);
        CoordCal = CoordCal + ";" + (AnsiString)(cad);
        double Azt = CalAzimut(Altura, tRa, tDe); //(double ARec, double DEC)
        sprintf(cad, "%003.2f", Azt);
        Form1->LAzimut->Caption = "Az: " + AnsiString(cad);
        CoordCal = CoordCal + ";" + (AnsiString)(cad);

        //Atura y Azimut del Telescopio en grados-minutos.
        Aux[0] = BuffLX[15];
        Aux[1] = BuffLX[16];
        Aux[2] = BuffLX[17];
        Aux[3] = 'º';
        //        float AltGrados = atof(Aux);
        Aux[4] = BuffLX[19];
        Aux[5] = BuffLX[20];
        Aux[6] = '´';
        Aux[7] = 0;
        //        float AltMin = atof(Aux);
        //        float Altu = AltGrados + (AltMin / 60.0);
        //sprintf(cad,"%003.003f",Altu);
        Form1->LAlturaRx->Caption = "Alt: " + AnsiString(Aux);
    }
    //   else Historico->Mhistory->Lines->Add("Rec.LX: " + AnsiString(BuffLX)+ " len " + AnsiString(strlen(BuffLX)));

    if (Long == 15)  //Cadena solo con AR y DEC. Probablemente de TESS
    {
        LXresponde = true;
        //AR y Dec del telescopio en decimal
        Aux[0] = BuffLX[0];
        Aux[1] = BuffLX[1];
        Aux[2] = 0;
        nRAHour  = atof(Aux);  //Hora RA
        Aux[0] = BuffLX[3];
        Aux[1] = BuffLX[4];
        Aux[2] = BuffLX[5];
        Aux[3] = BuffLX[6];
        Aux[4] = 0;
        dRAMin  = atof(Aux);  //Minutos RA
        tRa = 15.0 * ( nRAHour + dRAMin / 60.0);

        Aux[0] = BuffLX[8];
        Aux[1] = BuffLX[9];
        Aux[2] = BuffLX[10];
        Aux[3] = 0;
        nDecDeg = atof(Aux);
        Aux[0] = BuffLX[12];
        Aux[1] = BuffLX[13];
        Aux[2] = 0;
        nDecMin = atof(Aux);
        if (BuffLX[8] == '+')
            tDe = nDecDeg + (nDecMin / 60.0);
        else
        {
            tDe = nDecDeg - (nDecMin / 60.0);
            // nDecMin = -nDecMin;
        }
        sprintf(cad, "%003.2f", tRa);
        Form1->LRAgrados->Caption =  AnsiString(cad) + "º";
        CoordCal = cad;
        sprintf(cad, "%003.02f", tDe);
        Form1->LDecgrados->Caption = AnsiString(cad) + "º";   //sale -10.32 en vez de -11º41'
        CoordCal = ";" + CoordCal + ";" + (AnsiString)(cad);

        //Altura y Azimut Calculada partir de AR y Dec del telescopio en decimal
        double Altura = CalAltura(tRa, tDe); //(double ARec, double DEC)
        sprintf(cad, "%003.2f", Altura);
        Form1->LAltura->Caption = "Alt: " + AnsiString(cad);
        CoordCal = CoordCal + ";" + (AnsiString)(cad);
        double Azt = CalAzimut(Altura, tRa, tDe); //(double ARec, double DEC)
        sprintf(cad, "%003.2f", Azt);
        Form1->LAzimut->Caption = "Az: " + AnsiString(cad);
        CoordCal = CoordCal + ";" + (AnsiString)(cad);
    }
}

//==============================================================================
void ProcesarCGEM()
//==============================================================================
{
    char Aux[20];

    char BuffLX[2000];
    char aux[300], cad[10];
    char * pEnd;
    int Long, pos;

    AnsiString    are_s, dec_s, CadCgem;
    int           are_i, dec_i;
    unsigned long are_l, dec_l;
    double        are_f, dec_f;

    Long = min(S1->nDatosLX200, 500);
    S1->LeerLX200(BuffLX, Long);
    BuffLX[Long] = 0;

    /**************************
    Simulación envío telescopio
    **************************/
    //strcpy(BuffLX,"34AB,12CE#");         // RA=04h 56m 15.44s DEC=+26º 26' 38.73"
    //Long = 10;
    //strcpy(BuffLX,"F25F,FB60#");         // RA=22 43m 20.24s DEC=-06º 30' 14.06"
    //Long = 10;
    //strcpy(BuffLX, "34AB0500,12CE0500#"); // RA=04h 56m 15.47s DEC=+26º 26' 39.12"
    //Long = 18;
    //strcpy(BuffLX,"F25F2F00,FB605B00#"); // RA=22h 43m 20.49s DEC=-06º 30' 07.03"
    //Long = 18;
    /*************************/

    int buff0 = BuffLX[0];
    AnsiString name = "";
    char tim[10] = {0};
    char loc[10] = {0};
    char off = BuffLX[6];
    char dst = BuffLX[7];
    char nos = 'N';
    char eow = 'E';

    switch (command)
    {
        case GetPreRAS_DEC:
            ProcesarGetPreRAS_DEC(BuffLX);
            break;
        case GetRAS_DEC:
            ProcesarGetRAS_DEC(BuffLX);
            break;
        case GetPreAZM_ALT:
            ProcesarGetPreAZM_ALT(BuffLX);
            break;
        case GetVer:
            // Form1->eDeviceVer->Text = AnsiString(int(BuffLX[0]) + "." + int(BuffLX[1]));
            sprintf(Aux, "%d.%d", BuffLX[0] , BuffLX[1]);
            Form1->eDeviceVer->Text = AnsiString(Aux);
            break;
        case GetDevVer:
            sprintf(Aux, "%d.%d", BuffLX[0] , BuffLX[1]);
            Form1->eDeviceVer->Text = AnsiString(Aux);
            break;
        case GetModel:

            switch (buff0)
            {
                case 1:
                    name = "GPS Series" ;
                    break;
                case 3:
                    name = "i-Series";
                    break;
                case 4:
                    name = "i-Series SE";
                    break;
                case 5:
                    name = "CGE";
                    break;
                case 6:
                    name = "Advanced GT";
                    break;
                case 7:
                    name = "SLT";
                    break;
                case 9:
                    name = "CPC";
                    break;
                case 10:
                    name = "GT";
                    break;
                case 11:
                    name = "4/5 SE";
                    break;
                case 12:
                    name = "6/8 SE";
                    break;
                case 14:
                    name = "CGEM";
                    break;
                default:
                    name = "Unknown";
                    break;
            }

            Form1->eModel->Text = name;
            break;
        case Echo:
            Form1->eEcho->Text = AnsiString(buff0) + "<-";
            break;
        case GetTrackMode:
            Form1->rgTracking->ItemIndex = buff0;
            break;
        case AlignComplete:
            Form1->cbAligned->Checked = (buff0 == 1);
            break;
        case GotoProg:
            Form1->cbGotoProg->Checked = (buff0 == '1');
            break;
        case GotoCancel:
            if (buff0 == '#')
            {
                Form1->eCancelGoto->Text = "Cancelled";
            }
            break;
        case GetLoc:
            ini.Location.degLatA = BuffLX[0];
            ini.Location.minLatB = BuffLX[1];
            ini.Location.secLatC = BuffLX[2];
            ini.Location.nosLatD = BuffLX[3];
            ini.Location.degLonE = BuffLX[4];
            ini.Location.minLonF = BuffLX[5];
            ini.Location.secLonG = BuffLX[6];
            ini.Location.eowLonH = BuffLX[7];

            if (ini.Location.nosLatD == 1) nos = 'S';
            if (ini.Location.eowLonH == 1) eow = 'W';

            sprintf(loc, "%02dº%02d'%02d\" %c %02dh%02dm%02ds %c ",
                    ini.Location.degLatA, ini.Location.minLatB, ini.Location.secLatC, nos,
                    ini.Location.degLonE, ini.Location.minLonF, ini.Location.secLonG, eow);

            Form1->eGetPosition->Text = loc;
            break;
        case GetTime:
            sprintf(tim, "%04d-%02d-%02d %02d:%02d:%02d (%01d)", BuffLX[5] + 2000,
                    BuffLX[3], BuffLX[4], BuffLX[0], BuffLX[1], BuffLX[2], off);

            Form1->eGetTime->Text = tim;
            Form1->cbDST->Checked = (dst == '1');
            break;
        default:
            break;
    }


    if (Long > 3)
    {
        if ( Form1->CBver_envio_lx->Checked == true)
        {
            TimeRxLX200 = Fecha.CurrentTime();
            //Historico->Mhistory->Lines->Add( AnsiString(TimeRxLX200) + "->" + AnsiString(BuffLX) );
        }
    }
    else
        //Historico->Mhistory->Lines->Add( "->" + AnsiString(BuffLX) );

    /*
    if (Long == 10)  //Espera una cadena completa con AR, DEC, Alt y Az.  //8BD0,3F35# -> AR,DEC
    {
        CadCgem =  BuffLX;
        are_s = "0x" + CadCgem.SubString(1, 4);
        dec_s = "0x" + CadCgem.SubString(6, 4);
        are_l = strtoul(are_s.c_str(), &pEnd, 16);
        dec_l = strtoul(dec_s.c_str(), &pEnd, 16);
     */
    /*
    if ( TryStrToInt(ar_s, ar_i) )
    	;//     Historico->Mhistory->Lines->Add( ar_i );
    if ( TryStrToInt(dec_s, dec_i) )
    	;//    Historico->Mhistory->Lines->Add( dec_i );
    */
    /*
      are_f = (((double)are_l / 65536.0) * 360) / 15.0; // grados AR para Skymap
      dec_f =  ((double)dec_l / 65536.0) * 360; // grados DEC para Skymap

      if (dec_f > 90)
      {
          dec_f = dec_f - 360;
      }

      tRa = are_f * 15;
      tDe = dec_f;

      coordARE = formatARE(are_f);
      coordDEC = formatDEC(dec_f);

      //   Historico->Mhistory->Lines->Add("AR:" + AnsiString(ar_f) + "     Dec:"  + AnsiString(dec_f));

      // Eduardo discovered bug
      // tRa = 15.0 * ( nRAHour + dRAMin / 60.0);

      nRAHour = (int)are_f;  //Hora RA
      dRAMin  = (int)((are_f - nRAHour) * 100 * 0.6);
      nDecDeg = (int)dec_f;
      nDecMin = (int)((dec_f - nDecDeg) * 100 * 0.6);

      LXresponde = true;   //las fragmentadas por el momento no se usan
    }
    */
    /*
    if (Long == 18)  // Espera una cadena alta precisión  //34AB0500,12CE0500# -> AR,DEC
    {
    	CadCgem =  BuffLX;
    	are_s = "0x" + CadCgem.SubString( 1, 8);
    	dec_s = "0x" + CadCgem.SubString(10, 8);
    	are_l = strtoul(are_s.c_str(), &pEnd, 16);
    	dec_l = strtoul(dec_s.c_str(), &pEnd, 16);
    */
    /*
    if ( TryStrToInt(ar_s, ar_i) )
    	;//     Historico->Mhistory->Lines->Add( ar_i );
    if ( TryStrToInt(dec_s, dec_i) )
    	;//    Historico->Mhistory->Lines->Add( dec_i );
    */
    /*
    are_f = (((double)are_l / 4294967296.0) * 360) / 15.0; // grados AR para Skymap
    dec_f =  ((double)dec_l / 4294967296.0) * 360; // grados DEC para Skymap

    if (dec_f > 90)
    {
    	dec_f = dec_f - 360;
    }

    tRa = are_f * 15;
    tDe = dec_f;

    coordARE = formatARE(are_f);
    coordDEC = formatDEC(dec_f);

    //   Historico->Mhistory->Lines->Add("AR:" + AnsiString(ar_f) + "     Dec:"  + AnsiString(dec_f));

    // Eduardo discovered bug
    // tRa = 15.0 * ( nRAHour + dRAMin / 60.0);

    nRAHour = (int)are_f;  //Hora RA
    dRAMin  = (int)((are_f - nRAHour) * 100 * 0.6);
    nDecDeg = (int)dec_f;
    nDecMin = (int)((dec_f - nDecDeg) * 100 * 0.6);

    LXresponde = true;   //las fragmentadas por el momento no se usan
    }
    */

    if (Long == 9)  // Prueba get time
    {
        AnsiString cmd = Form1->ELXsend->Text;
        if (cmd == "h")
        {
            sprintf(aux, " %02d:%02d:%02d  %04d-%02d-%02d %d Off %dDST %c",
                    BuffLX[0], BuffLX[1], BuffLX[2],
                    BuffLX[5] + 2000, BuffLX[3], BuffLX[4],
                    BuffLX[6], BuffLX[7], BuffLX[8]);
        }
        else if (cmd == "w")
        {
            AnsiString Lat = "N", Lon = "E";
            if (BuffLX[3] == 1) Lat = "S";
            if (BuffLX[7] == 1) Lon = "W";

            sprintf(aux, " %02dº %02d' %02d\" %s %02dh %02dm %02ds %s %c",
                    BuffLX[0], BuffLX[1], BuffLX[2], Lat, BuffLX[4], BuffLX[5], BuffLX[6], Lon, BuffLX[8]);
        }
        TimeRxLX200 = Fecha.CurrentTime();
        Historico->Mhistory->Lines->Add( AnsiString(TimeRxLX200) + "->" + AnsiString(aux) );
    }
}

//==============================================================================
void ProcesarGetPreRAS_DEC(AnsiString CadCgem)
//==============================================================================
{
    char * pEnd;

    AnsiString    are_s, dec_s;
    unsigned long are_l, dec_l;
    double        arg_f, arh_f, dec_f, alt_f, azm_f;

    are_s = "0x" + CadCgem.SubString( 1, 8);
    dec_s = "0x" + CadCgem.SubString(10, 8);
    are_l = strtoul(are_s.c_str(), &pEnd, 16);
    dec_l = strtoul(dec_s.c_str(), &pEnd, 16);

    arg_f = ((double)are_l / 4294967296.0) * 360; // grados AR para Skymap
    arh_f = arg_f / 15.0;                         // horas  AR para formatear
    dec_f = ((double)dec_l / 4294967296.0) * 360; // grados DEC para Skymap

    if (dec_f > 90)
    {
        dec_f = dec_f - 360;
    }

    tRa = arg_f;
    tDe = dec_f;

    coordARE = formatARE(arh_f);
    coordDEC = formatDEC(dec_f);

    alt_f = CalAltura(arg_f, dec_f);
    azm_f = CalAzimut(alt_f, arg_f, dec_f);

    coordAZM = formatAZM(azm_f);
    coordALT = formatALT(alt_f);

    //   Historico->Mhistory->Lines->Add("AR:" + AnsiString(ar_f) + "     Dec:"  + AnsiString(dec_f));

    // Eduardo discovered bug
    // tRa = 15.0 * ( nRAHour + dRAMin / 60.0);

    // INIBLOQUE Se podría eliminar este bloque? ***********************
    /*
    nRAHour = (int)are_f;  //Hora RA
    dRAMin  = (int)((are_f - nRAHour) * 100 * 0.6);
    nDecDeg = (int)dec_f;
    nDecMin = (int)((dec_f - nDecDeg) * 100 * 0.6);
    */
    // FINBLOQUE *******************************************************

    LXresponde = true;   //las fragmentadas por el momento no se usan
}

//==============================================================================
void ProcesarGetRAS_DEC(AnsiString CadCgem)
//==============================================================================
{
    char * pEnd;

    AnsiString    are_s, dec_s;
    unsigned long are_l, dec_l;
    double        arg_f, arh_f, dec_f, alt_f, azm_f;

    are_s = "0x" + CadCgem.SubString(1, 4);
    dec_s = "0x" + CadCgem.SubString(6, 4);
    are_l = strtoul(are_s.c_str(), &pEnd, 16);
    dec_l = strtoul(dec_s.c_str(), &pEnd, 16);

    arg_f = ((double)are_l / 4294967296.0) * 360; // grados AR para Skymap
    arh_f = arg_f / 15.0;                         // horas  AR para formatear
    dec_f = ((double)dec_l / 4294967296.0) * 360; // grados DEC para Skymap

    if (dec_f > 90)
    {
        dec_f = dec_f - 360;
    }

    tRa = arg_f;
    tDe = dec_f;

    coordARE = formatARE(arh_f);
    coordDEC = formatDEC(dec_f);

    alt_f = CalAltura(arg_f, dec_f);
    azm_f = CalAzimut(alt_f, arg_f, dec_f);

    coordAZM = formatAZM(azm_f);
    coordALT = formatALT(alt_f);

    //   Historico->Mhistory->Lines->Add("AR:" + AnsiString(ar_f) + "     Dec:"  + AnsiString(dec_f));

    // Eduardo discovered bug
    // tRa = 15.0 * ( nRAHour + dRAMin / 60.0);

    // INIBLOQUE Se podría eliminar este bloque? ***********************
    /*
    nRAHour = (int)are_f;  //Hora RA
    dRAMin  = (int)((are_f - nRAHour) * 100 * 0.6);
    nDecDeg = (int)dec_f;
    nDecMin = (int)((dec_f - nDecDeg) * 100 * 0.6);
    */
    // FINBLOQUE *******************************************************

    LXresponde = true;   //las fragmentadas por el momento no se usan
}

//==============================================================================
void ProcesarGetPreAZM_ALT(AnsiString CadCgem)
//==============================================================================
{
    char * pEnd;

    AnsiString    azm_s, alt_s;
    unsigned long azm_l, alt_l;
    double        azm_f, alt_f;

    azm_s = "0x" + CadCgem.SubString( 1, 8);
    alt_s = "0x" + CadCgem.SubString(10, 8);
    azm_l = strtoul(azm_s.c_str(), &pEnd, 16);
    alt_l = strtoul(alt_s.c_str(), &pEnd, 16);

    azm_f = (double)azm_l / 4294967296.0 * 360; // grados AZM
    alt_f = (double)alt_l / 4294967296.0 * 360; // grados ALT
    /*
    if (alt_f > 90)
    {
        alt_f = alt_f - 360;
    }
    */
    coordAZM = formatAZM(azm_f);
    coordALT = formatALT(alt_f);

    LXresponde = true;
}

//==============================================================================
AnsiString formatARE(double dARE)
//==============================================================================
{
    char aux[300];

    double dValue;			 			// temporary storage
    //char cSign;	                        // declination sign

    long RAHor;                         // RA,  hours
    long RAMin;                         // RA,  minutes
    long RASec;                         // RA,  seconds
    long RACse;                         // RA,  cents of second

    //dValue = dARE / 360 * 24;
    dValue = dARE;
    RAHor = dValue;

    dValue = (dValue - RAHor) * 60;
    RAMin = dValue;

    dValue = (dValue - RAMin) * 60;
    RASec = dValue;

    dValue = (dValue - RASec) * 100 + 0.5;
    RACse = dValue;

    if (RACse > 99) RACse = 99;

    sprintf(aux, " %02dh %02dm %02d.%02ds", RAHor, RAMin, RASec, RACse);

    return AnsiString(aux);
}

//==============================================================================
AnsiString formatDEC(double dDEC)
//==============================================================================
{
    char aux[300];

    double dValue;			 			// temporary storage
    char cSign;	                        // declination sign

    long DECGra;                        // DEC, degrees
    long DECMin;                        // DEC, minutes
    long DECSec;                        // DEC, seconds
    long DECCse;                        // DEC, cents of second

    if (dDEC < 0.0)
    {
        dValue = -dDEC;
        cSign = '-';
    }
    else
    {
        dValue = dDEC;
        cSign = '+';
    }

    DECGra = dValue;

    dValue = (dValue - DECGra) * 60;
    DECMin = dValue;

    dValue = (dValue - DECMin) * 60;
    DECSec = dValue;

    dValue = (dValue - DECSec) * 100 + 0.5;
    DECCse = dValue;

    if (DECCse > 99) DECCse = 99;

    sprintf(aux, "%c%02dº %02d' %02d.%02d\"", cSign, DECGra, DECMin, DECSec, DECCse);

    return AnsiString(aux);
}

//==============================================================================
AnsiString formatAZM(double dAZM)
//==============================================================================
{
    char aux[300];

    double dValue;			 			// temporary storage

    long AZDeg;                         // Azimut, degrees
    long AZMin;                         // Azimut, minutes
    long AZSec;                         // Azimut, seconds
    long AZCse;                         // Azimut, cents of second

    dValue = dAZM;
    AZDeg = dValue;

    dValue = (dValue - AZDeg) * 60;
    AZMin = dValue;

    dValue = (dValue - AZMin) * 60;
    AZSec = dValue;

    dValue = (dValue - AZSec) * 100 + 0.5;
    AZCse = dValue;

    if (AZCse > 99) AZCse = 99;

    // Formato grados y minutos
    sprintf(aux, "%02dº%02dm", AZDeg, AZMin);
    //sprintf(aux, " %02dº %02dm %02d.%02ds", AZDeg, AZMin, AZSec, AZCse);

    return AnsiString(aux);
}

//==============================================================================
AnsiString formatALT(double dALT)
//==============================================================================
{
    char aux[300];

    double dValue;			 			// temporary storage
    char cSign;	                        // ALT sign

    long ALTGra;                        // ALT, degrees
    long ALTMin;                        // ALT, minutes
    long ALTSec;                        // ALT, seconds
    long ALTCse;                        // ALT, cents of second

    if (dALT < 0.0)
    {
        dValue = -dALT;
        cSign = '-';
    }
    else
    {
        dValue = dALT;
        cSign = '+';
    }

    ALTGra = dValue;

    dValue = (dValue - ALTGra) * 60;
    ALTMin = dValue;

    dValue = (dValue - ALTMin) * 60;
    ALTSec = dValue;

    dValue = (dValue - ALTSec) * 100 + 0.5;
    ALTCse = dValue;

    if (ALTCse > 99) ALTCse = 99;

    // Formato grados y minutos
    sprintf(aux, "%c%02dº%02dm", cSign, ALTGra, ALTMin);
    //sprintf(aux, "%c%02dº %02d' %02d.%02d\"", cSign, ALTGra, ALTMin, ALTSec, ALTCse);

    return AnsiString(aux);
}

//==============================================================================
AnsiString ArDecToOrden(long ARe_Hor, long ARe_Min, long ARe_Sec, long ARe_CSec,
                        long Dec_Gra, long Dec_Min, long Dec_Sec, long Dec_CSec, char Dec_Sgn)
//==============================================================================
{
    double d_aux;
    unsigned short us_aux_dec;
    unsigned short us_aux_are;

    // Tengo Cent de seg
    d_aux = ARe_CSec;
    // Obtengo seg
    d_aux = (d_aux / 100.0) + ARe_Sec;
    // Obtengo min
    d_aux = (d_aux /  60.0) + ARe_Min;
    // Obtengo horas
    d_aux = (d_aux /  60.0) + ARe_Hor;
    // obtengo el short equivalente
    us_aux_are = (unsigned short)(d_aux * 65536.0 / 24.0);

    // Tengo Cent de seg
    d_aux = Dec_CSec;
    // Obtengo seg
    d_aux = (d_aux / 100.0) + Dec_Sec;
    // Obtengo min
    d_aux = (d_aux /  60.0) + Dec_Min;
    // Obtengo grados
    d_aux = (d_aux /  60.0) + Dec_Gra;

    if (Dec_Sgn != '+')
    {
        // Negative declination
        d_aux = 360 - d_aux;
    }

    // obtengo el short equivalente
    us_aux_dec = (unsigned short)(d_aux * 65536.0 / 360.0);

    // Creo la cadena que contiene la orden
    char cadena_orden[20];
    sprintf(cadena_orden, "R%04X,%04X", us_aux_are, us_aux_dec);

    // *retorno = EnviarOrden(MNT_CEL_ORDEN_GOTO, (BYTE*)(cadena_orden), 10);
    return AnsiString(cadena_orden);
}

//==============================================================================
AnsiString ArDecToTeles(AnsiString AReHor, AnsiString AReMin,
                        AnsiString AReSec, AnsiString AReCSec,
                        AnsiString DecGra, AnsiString DecMin,
                        AnsiString DecSec, AnsiString DecCSec, char DecSgn)
//==============================================================================
{
    double d_aux;
    unsigned short us_aux_dec;
    unsigned short us_aux_are;

    // strtoul((char*)EHra ->EditText.c_str()

    // Tengo Cent de seg
    d_aux = AReCSec.ToInt();
    // Obtengo seg
    d_aux = (d_aux / 100.0) + AReSec.ToInt();
    // Obtengo min
    d_aux = (d_aux /  60.0) + AReMin.ToInt();
    // Obtengo horas
    d_aux = (d_aux /  60.0) + AReHor.ToInt();
    // obtengo el short equivalente
    us_aux_are = (unsigned short)(d_aux * 65536.0 / 24.0);

    // Tengo Cent de seg
    d_aux = DecCSec.ToInt();
    // Obtengo seg
    d_aux = (d_aux / 100.0) + DecSec.ToInt();
    // Obtengo min
    d_aux = (d_aux /  60.0) + DecMin.ToInt();
    // Obtengo grados
    d_aux = (d_aux /  60.0) + DecGra.ToInt();

    if (DecSgn != '+')
    {
        // Negative declination
        d_aux = 360 - d_aux;
    }

    // obtengo el short equivalente
    us_aux_dec = (unsigned short)(d_aux * 65536.0 / 360.0);

    // Creo la cadena que contiene la orden
    char cadena_orden[20];
    sprintf(cadena_orden, "R%04X,%04X", us_aux_are, us_aux_dec);

    // *retorno = EnviarOrden(MNT_CEL_ORDEN_GOTO, (BYTE*)(cadena_orden), 10);
    return AnsiString(cadena_orden);
}

//==============================================================================
AnsiString ArDecPrecToOrden(long ARe_Hor, long ARe_Min, long ARe_Sec, long ARe_CSec,
                            long Dec_Gra, long Dec_Min, long Dec_Sec, long Dec_CSec, char Dec_Sgn)
//==============================================================================
{
    double d_aux;
    unsigned long ul_aux_are;
    unsigned long ul_aux_dec;

    // Tengo Cent de seg
    d_aux = ARe_CSec;
    // Obtengo seg
    d_aux = (d_aux / 100.0) + ARe_Sec;
    // Obtengo min
    d_aux = (d_aux /  60.0) + ARe_Min;
    // Obtengo horas
    d_aux = (d_aux /  60.0) + ARe_Hor;
    // obtengo el long equivalente
    ul_aux_are = (unsigned long)(d_aux * 4294967296.0 / 24.0);

    // Tengo Cent de seg
    d_aux = Dec_CSec;
    // Obtengo seg
    d_aux = (d_aux / 100.0) + Dec_Sec;
    // Obtengo min
    d_aux = (d_aux /  60.0) + Dec_Min;
    // Obtengo grados
    d_aux = (d_aux /  60.0) + Dec_Gra;

    if (Dec_Sgn != '+')
    {
        // Negative declination
        d_aux = 360 - d_aux;
    }

    // obtengo el long equivalente
    ul_aux_dec = (unsigned long)(d_aux * 4294967296.0 / 360.0);

    // Creo la cadena que contiene la orden
    char cadena_orden[30];
    sprintf(cadena_orden, "r%08X,%08X", ul_aux_are, ul_aux_dec);

    // *retorno = EnviarOrden(MNT_CEL_ORDEN_GOTO_PREC, (BYTE*)(cadena_orden), 18);
    return AnsiString(cadena_orden);
}

//==============================================================================
AnsiString ArDecPrecToTeles(AnsiString AReHor, AnsiString AReMin,
                            AnsiString AReSec, AnsiString AReCSec,
                            AnsiString DecGra, AnsiString DecMin,
                            AnsiString DecSec, AnsiString DecCSec, char DecSgn)
//==============================================================================
{
    double d_aux;
    unsigned long ul_aux_are;
    unsigned long ul_aux_dec;

    // Tengo Cent de seg
    d_aux = AReCSec.ToInt();
    // Obtengo seg
    d_aux = (d_aux / 100.0) + AReSec.ToInt();
    // Obtengo min
    d_aux = (d_aux /  60.0) + AReMin.ToInt();
    // Obtengo horas
    d_aux = (d_aux /  60.0) + AReHor.ToInt();

    // obtengo el long equivalente
    ul_aux_are = (unsigned long)(d_aux * 4294967296.0 / 24.0);

    // Tengo Cent de seg
    d_aux = DecCSec.ToInt();
    // Obtengo seg
    d_aux = (d_aux / 100.0) + DecSec.ToInt();
    // Obtengo min
    d_aux = (d_aux /  60.0) + DecMin.ToInt();
    // Obtengo grados
    d_aux = (d_aux /  60.0) + DecGra.ToInt();

    if (DecSgn != '+')
    {
        // Negative declination
        d_aux = 360 - d_aux;
    }

    // obtengo el long equivalente
    ul_aux_dec = (unsigned long)(d_aux * 4294967296.0 / 360.0);

    // Creo la cadena que contiene la orden
    char cadena_orden[30];
    sprintf(cadena_orden, "r%08X,%08X", ul_aux_are, ul_aux_dec);

    // *retorno = EnviarOrden(MNT_CEL_ORDEN_GOTO_PREC, (BYTE*)(cadena_orden), 18);
    return AnsiString(cadena_orden);
}

//==============================================================================
AnsiString OrdenToArDec(char* ptr_buffer_in)
//==============================================================================
{
    unsigned short us_aux;
    char* stopstring;
    double DatosCoordEqAr;
    double DatosCoordEqDec;
    double d_aux;
    BYTE DatosCoordEqRaDecAr_Hora;
    BYTE DatosCoordEqRaDecAr_Minuto;
    BYTE DatosCoordEqRaDecAr_Segundo;
    BYTE DatosCoordEqRaDecAr_CentSegundo;
    BYTE DatosCoordEqRaDecDec_Grado;
    BYTE DatosCoordEqRaDecDec_Minuto;
    BYTE DatosCoordEqRaDecDec_Segundo;
    BYTE DatosCoordEqRaDecDec_CentSegundo;
    AnsiString DatosCoordEqchrAr;
    AnsiString DatosCoordEqchrDec;

    us_aux = (unsigned short)strtoul( (char*)ptr_buffer_in, &stopstring, 16);
    DatosCoordEqAr = (double)(us_aux) * 24.0 / 65536.0;

    d_aux = DatosCoordEqAr;
    DatosCoordEqRaDecAr_Hora = (BYTE)((int)d_aux);
    d_aux =  60.0 * (d_aux - DatosCoordEqRaDecAr_Hora);
    DatosCoordEqRaDecAr_Minuto = (BYTE)((int)d_aux);
    d_aux =  60.0 * (d_aux - DatosCoordEqRaDecAr_Minuto);
    DatosCoordEqRaDecAr_Segundo = (BYTE)((int)d_aux);
    d_aux = 100.0 * (d_aux - DatosCoordEqRaDecAr_Segundo);
    DatosCoordEqRaDecAr_CentSegundo = (BYTE)((int)d_aux);

    sprintf(DatosCoordEqchrAr.c_str(),
            "%02ih %02im %02i.%01is",
            DatosCoordEqRaDecAr_Hora,
            DatosCoordEqRaDecAr_Minuto,
            DatosCoordEqRaDecAr_Segundo,
            (int)((DatosCoordEqRaDecAr_CentSegundo + 5) / 10));

    us_aux = (unsigned short)strtoul( (char*)(ptr_buffer_in + 5), &stopstring, 16);
    DatosCoordEqDec = (double)(us_aux) * 360.0 / 65536.0;

    if (DatosCoordEqDec < 180.0)
        d_aux = DatosCoordEqDec;
    else
        d_aux = 360.0 - DatosCoordEqDec;
    DatosCoordEqRaDecDec_Grado = (BYTE)((int)d_aux);
    d_aux =  60.0 * (d_aux - DatosCoordEqRaDecDec_Grado);
    DatosCoordEqRaDecDec_Minuto = (BYTE)((int)d_aux);
    d_aux =  60.0 * (d_aux - DatosCoordEqRaDecDec_Minuto);
    DatosCoordEqRaDecDec_Segundo = (BYTE)((int)d_aux);
    d_aux = 100.0 * (d_aux - DatosCoordEqRaDecDec_Segundo);
    //DatosCoordEqRaDecDec_CentSegundo = (BYTE)((int)d_aux);

    if (DatosCoordEqDec < 180.0)
    {
        sprintf(DatosCoordEqchrDec.c_str(), "+%02iº %02i%c %02i%c",
                DatosCoordEqRaDecDec_Grado,
                DatosCoordEqRaDecDec_Minuto, 39,
                DatosCoordEqRaDecDec_Segundo, 34);
    }
    else
    {
        sprintf(DatosCoordEqchrDec.c_str(), "-%02iº %02i%c %02i%c",
                DatosCoordEqRaDecDec_Grado,
                DatosCoordEqRaDecDec_Minuto, 39,
                DatosCoordEqRaDecDec_Segundo, 34);
    }
    return DatosCoordEqchrDec;
}

//==============================================================================
// Refresca informacion del panel de control
// Es llamada desde el timer100 de 100ms
void actualizar_datos(void)
//==============================================================================
{
    TColor col[2] = {clGray, clRed};
    TColor col1[2] = {clGray, clLime};
    float pp;

    if (Form1->CBSelCamara->ItemIndex == 0) // Camara principal
    {
        pp = TccdA;
        pp *= 10.0 / 32767.0;
        pp = (pp / 0.01) - 273;
        TccdA_grados = pp;
        if ((TccdA_grados < 100) & (TccdA_grados > -100))
        {
            Form1->PTccdA->Caption = FloatToStrF(TccdA_grados, ffFixed, 15, 1);
        }
        else Form1->PTccdA->Caption = "---";

        pp = TcajaA;
        pp *= 10.0 / 32767.0;
        pp = (pp / 0.01) - 273;
        if ((pp < 100) & (pp > -100))
            Form1->PTcajaA->Caption = FloatToStrF(pp, ffFixed, 15, 1);
        else Form1->PTcajaA->Caption = "---";

        pp = VpeltierA;
        pp *= 10.0 / 32767.0;
        pp = pp * 2; //porque hay un divisor de tension
        if ((pp < 15) & (pp >= 0))
            Form1->PVpeltierA->Caption = FloatToStrF(pp, ffFixed, 15, 1);
        else Form1->PVpeltierA->Caption = "---";
    }
    else  if (Form1->CBSelCamara->ItemIndex == 1)   // Camara Auxiliar
    {
        pp = TccdB;
        pp *= 10.0 / 32767.0;
        pp = (pp / 0.01) - 273;
        TccdB_grados = pp;
        if (( TccdB_grados < 100 ) & (TccdB_grados > -100))
        {
            Form1->PTccdB->Caption = FloatToStrF(TccdB_grados, ffFixed, 15, 1);
        }
        else Form1->PTccdB->Caption = "---";

        pp = TcajaB;
        pp *= 10.0 / 32767.0;
        pp = (pp / 0.01) - 273;
        if ((pp < 100) & (pp > -100))
            Form1->PTcajaB->Caption = FloatToStrF(pp, ffFixed, 15, 1);
        else Form1->PTcajaB->Caption = "---";

        pp = VpeltierB;
        pp *= 10.0 / 32767.0;
        pp = pp * 2; //porque hay un divisor de tension
        if ((pp < 15) & (pp >= 0))
            Form1->PVpeltierB->Caption = FloatToStrF(pp, ffFixed, 15, 1);
        else Form1->PVpeltierB->Caption = "---";
    }
    /*
    float pp = Tccd;
    pp *= 10.0/32767.0;
    pp = (pp/0.01)-273;

    if((pp<100)&(pp>-100))
    {
    	if (Form1->CBSelCamara->ItemIndex == 0)
    		Form1->PTccdA->Caption = FloatToStrF(pp, ffFixed, 15, 1);
    	else
    		Form1->PTccdB->Caption = FloatToStrF(pp, ffFixed, 15, 1);
    }
    else
    {
    	if (Form1->CBSelCamara->ItemIndex == 0)
    		Form1->PTccdA->Caption = "---";
    	else
    		Form1->PTccdB->Caption = "---";
    }

    pp = Tcaja;
    pp *= 10.0/32767.0;
    pp = (pp/0.01)-273;
    if((pp<100)&(pp>-100))
    {
    	if (Form1->CBSelCamara->ItemIndex == 0)
    	Form1->PTcajaA->Caption = FloatToStrF(pp, ffFixed, 15, 1);
    	else
    	Form1->PTcajaB->Caption = FloatToStrF(pp, ffFixed, 15, 1);
    }
    else
    {
    	if (Form1->CBSelCamara->ItemIndex == 0)
    		Form1->PTcajaA->Caption = "---";
    	else
    		Form1->PTcajaB->Caption = "---";
    }

    pp = Vpeltier;
    pp *= 10.0/32767.0;
    pp = pp*2; //porque hay un divisor de tension
    if((pp<15)&(pp>=0))
    {
    	Form1->PVpeltier->Caption = FloatToStrF(pp, ffFixed, 15, 1);
    }
    	else Form1->PVpeltier->Caption = "---";
    */
    if (Salidas & 0x01)
        Form1->Panel11->Enabled = true; //permite mover motores
    else Form1->Panel11->Enabled = false;

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

//------------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
//------------------------------------------------------------------------------
{
    Timer50->Enabled = false;
    delete Filtro;
    delete Shuter;
    delete S1;
}

//------------------------------------------------------------------------------
// Print out cfitsio error messages and exit program
void __fastcall TForm1::printerror( int status)
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
void __fastcall TForm1::BEnviarClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    char aux[300];

    aux[0] = 50;
    strcpy(&aux[2], CBEnviar->Text.c_str());
    if (CBEnviar->Text == "reset")
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

//==============================================================================
void RellenarBitmap(int x1, int y1, int x2, int y2)
//==============================================================================
{
    FotoPrincipal->Pintar(x1, y1, x2, y2);

    BitBlt(Form1->PB1->Canvas->Handle, x1, y1, x2, y2, FotoPrincipal->BM->Canvas->Handle, x1, y1, SRCCOPY);
    if (first == false)
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

//------------------------------------------------------------------------------
// Timer1 50ms Gestion Fotos
void __fastcall TForm1::Timer50Timer(TObject *Sender)
//------------------------------------------------------------------------------
{
    char aux[300];
    char Name[80];
    char *punteroX;
    static  int retardo1s;
    static int FocoEstable; //enfocando se usa para esperar un tiempo estabilizacion del foco.
    TJPEGImage *jp;
    static bool sonido;

    if (LeyendoFoto == true)
    {
        if (LineaNueva == true)
        {

            LineaNueva = false;
            if (CBPintar->State == cbChecked)
            {
                RellenarBitmap(X1FS, Y1FS, X2FS, Y2FS);
            }
            int p = numeroLinea * 100 / (Y2F - Y1F);
            if (p <= 100)
            {
                PBF->Position = p;   //barra de progreso de lectura
                if ((sonido == false) && (CBAutoEnfoque->State == cbUnchecked))
                {
                    Beep();
                    sonido = true;
                }
            }
            else
                PBF->Position = 100;
        }
        if (FinFoto == true)    // se ha terminado una foto
        {
            sonido = false;
            FechaFoto =  FechaFoto.CurrentDateTime();
            //    if(FotoActual > nfotos)
            //    Beep();

            TNFotos->Caption = 1;
            RellenarBitmap(X1FS, Y1FS, X2FS, Y2FS);
            LeyendoFoto = false;

            PCancel->Visible = true;
            if (FotoActual > nfotos)
                Panel5->Enabled = true;

            SLedFoto->Brush->Color = clGray;
            if (PFoto->BevelOuter == bvLowered)
            {
                PFoto->BevelOuter = bvRaised;
                PFoto->Color = clSilver;
                SLedFoto->Brush->Color = clGray;
                SLedFoto->Repaint();
                PBF->Position = 0;
            }

            if (CBAutoEnfoque->State == cbChecked)//(ObtuIndex == 3)  //estamos enfocando
            {
                Enfoque();
            }

            if (A_FinFoto == true)
            {
                A_FinFoto = false;
                //       Historico->Mhistory->Lines->Add("Exp: " + AnsiString(A_T_Ini_Lect - A_T_Ini_Exp)
                //      +" Lectura: "+ AnsiString(A_T_Fin_Lect - A_T_Ini_Lect + obturetraso*100) );
            }
            double pos_x, pos_y;
            if (Form1->CBautostrech->Checked == true) ///explota
            {
                // [C++ Warning] Principal.cpp(2464): W8004 'media' is assigned a value that is never used
                //long media =  FotoPrincipal->media(); //para tener el fondo cielo  //estaba comentada ¿?
                FotoPrincipal->media(); //para tener el fondo cielo  //estaba comentada ¿?
                pos_x = FotoPrincipal->fondocielo - atoi(Form1->estirar_bajo->Text.c_str());
                pos_y = FotoPrincipal->fondocielo + atoi(Form1->estirar_alto->Text.c_str());
                TBx0->Position = pos_x;
                TBy0->Position = pos_y;
                PB1->Repaint();
            }

            try
            {
                jp = new TJPEGImage();
            }     // creacion del fichero jpg
            catch (...)
            {
                return;
            }

            try
            {
                jp->Assign(FotoPrincipal->BM);
                //        jp->SaveToFile("c:\\inetpub\\wwwroot\\pp.jpg");
                strcpy(aux, confEMA.direc_jpg);
                strcat(aux, "pp.jpg");
                jp->SaveToFile(aux);
            }
            __finally
            {
                delete jp;
            }
            Form1->TiempoPasado->Caption = 0;

            //      SetCurrentDirectory( mPath.c_str());

            // TODO Revisar con Cristobal
            // TODO Crear directorio ini.Image.FotoDir + ini.Image.NameDir
            if ((CBGuardar->Checked == true) && (paquetesperdidos == 0))
            {
                if (ENFotos->Text.ToInt() > 1)
                {
                    sprintf( aux, "%003d", (FotoActual - 1));
                    sprintf(Name, (ENombreFichero->Text + AnsiString("_") + AnsiString(aux) + AnsiString(".fit")).c_str());
                    //Historico->Mhistory->Lines->Add(" Nombre Fotos: " + AnsiString(Name));
                }
                else
                {
                    sprintf(Name, (ENombreFichero->Text + AnsiString(".fit")).c_str());
                    //Historico->Mhistory->Lines->Add(" Nombre Foto: " + AnsiString(Name));
                }

                if (FileExists(Name))
                    DeleteFile(Name);
                GuardarFoto(Name);


                // Este directorio se saca de EMA.CFG (binario) y direc_jpg es C://inetpub//wwwroot//
                strcpy(aux, confEMA.direc_jpg);
                if ((FotoActual - 1) > 1)
                    strcat(aux, "aux_1.fit");
                else
                    strcat(aux, "referen.fit");

                // if (FileExists(aux) )
                //     DeleteFile(aux);
                // CopyFile(Name, aux, NULL);

                // El parámetro FALSE indica sobreescribir si fichero existe
                CopyFile(Name, aux, FALSE);

                if (CBrecentrar->Checked == true)
                {
                    DWORD esperoaqui = ::GetTickCount();
                    while ((::GetTickCount() - esperoaqui) < 4000) //espera calculos elbrus
                    {
                        PBF->Position = (::GetTickCount() - esperoaqui) * 100 / 4000;
                    }
                    PBF->Position = 0;
                    BDerivaAquiClick(NULL);
                    BrecentrarARClick(NULL);
                    BrecentrarDECClick(NULL);
                }

                // if (FileExists( "c:\\inetpub\\aux_1.fit") )
                //     DeleteFile("c:\\inetpub\\aux_1.fit");
                // CopyFile(Name, "c:\\inetpub\\aux_1.fit",  NULL);

                // El parámetro FALSE indica sobreescribir si fichero existe
                CopyFile(Name, "c:\\inetpub\\aux_1.fit", FALSE);

                //        if(FileExists( "aux_1.fit") )
                //            DeleteFile("aux_1.fit");
                //        CopyFile(Name, "aux_1.fit",  NULL);
            }
        }
    }

    else if (FotoActual <= nfotos)
    {
        numeroOrden = 0;
        SLedFoto->Brush->Color = clRed;
        PCancel->Visible = true;

        if (S1 != NULL)
        {
            if (abs(Y2F - Y1F) < 10 || abs(X2F - X1F) < 10)
            {
                Timer50->Enabled = false;
                Application->MessageBox("Rectangulo demasiado pequeño", "Atención", MB_OK);
                Timer50->Enabled = true;
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
                retardo1s = 0;
                TiempoPasado->Alignment = taRightJustify;
                TiempoPasado->Caption = (::GetTickCount() - TiempoInicio) / 1000;
                //  DogFoto = 0;
            }

            if (((::GetTickCount() - TiempoInicio) / 1000 >= segEntreFotos) || (FotoActual == 1))
            {
                if ((ObtuIndex == 3) || (ObtuIndex == 0)) //estamos enfocando o foto normal
                {
                    if ((CBAutoEnfoque->State == cbChecked) && (pasos_x > 100))
                    {
                        pasos_x = 50;
                        Form1->EPasosEnfoque->Text = "50"; // limita mover demasiado el enfoque
                    }
                    if (FinX == 1 )
                    {
                        FocoEstable++;
                        DogFoto = 0;
                    }
                    obturetraso = 0;
                    if ((FotoActual > 1) && (ObtuIndex == 3))
                        numlimpiados = 1; //no se limpian siguientes lecturas
                    else
                    {
                        numlimpiados = ELimpiado->Text.ToInt(); //limpiado primera vez
                    }
                    //mover motor de enfoque
                    if (FotoActual >= 1 && FinX == 1 && EsperandoFinX == 0 && CBAutoEnfoque->State == cbChecked)
                    {
                        sentido = '-';
                        MueveEnfoque();
                        EsperandoFinX = 1;
                        FocoEstable = 0;
                    }
                    // else
                    //   FocoEstable = MEEstabilizar->Text.ToInt();
                }
                else
                {
                    FocoEstable = MEEstabilizar->Text.ToInt();
                }

                if ((CuentaGuiaAR == 0) && (FinX == 1) && (FocoEstable >= MEEstabilizar->Text.ToInt() / 50)) //si el motor de enfoque esta parado podemos pedir Foto
                {
                    FotoPrincipal->maximo = 0;
                    FotoPrincipal->minimo = 0xFFFF;                               //
                    EsperandoFinX = 0;
                    DogFoto = 0;
                    FocoEstable = 0;

                    TiempoInicio =  ::GetTickCount();
                    //Historico->Mhistory->Lines->Add("Mover -> Foto:  " + AnsiString(TiempoInicio - IniciaAR));

                    TNFotos->Caption = FotoActual;//nfotos - m_numfotos;
                    //            if (CBAutoEnfoque->State == cbChecked)//(ObtuIndex == 3)
                    //               Historico->Mhistory->Lines->Add("-> Pos: " + PContador->Caption );
                    //          if (ObtuIndex != 3)
                    //             Historico->Mhistory->Lines->Add("Fotos pendientes: " + AnsiString(nfotos - FotoActual + 1));
                    HacerFoto( X1F, Y1F, X2F, Y2F, Binin, seg, mseg, CCDs[CBCCD_A->ItemIndex].ColumnasFisicas,
                               CCDs[CBCCD_A->ItemIndex].FilasFisicas, test, cancel, nfotos, numlimpiados, ObtuIndex, obturetraso, "");
                    PFoto->BevelOuter = bvLowered;
                    PFoto->Color = (TColor)0x00DEDEDE;
                    SLedFoto->Brush->Color = clRed;
                    Panel5->Enabled = false;
                    FotoActual++;
                    LeyendoFoto = true;
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
//-------------------- Termina Funcion del Timer 1 -----------------------------

//------------------------------------------------------------------------------
// timer 2 de 60sg para la gestion de los graficos meteorologicos
// Interval de T2 debe ser divisible por T3
void __fastcall TForm1::Timer60000Timer(TObject *Sender)
//------------------------------------------------------------------------------
{
    char aux[300];
    static int refres_jpg;

    Timer60sg = true;
    if (Guardarjpg)
        if (refres_jpg >= 3 && CuentaMensMeteo > 0) //los ficheros graficos se van a actualizar cada 3 minutos.
        {
            TJPEGImage *jp;
            Graphics::TBitmap *Bitmap1 = new Graphics::TBitmap();
            FGraficas->Chart1->SaveToBitmapFile(bmp_ane);
            FGraficas->Chart2->SaveToBitmapFile(bmp_tem);
            FGraficas->Chart3->SaveToBitmapFile(bmp_plu);
            FGraficas->Chart4->SaveToBitmapFile(bmp_llu);
            FGraficas->Chart5->SaveToBitmapFile(bmp_bar);

            try
            {
                jp = new TJPEGImage();
            }
            catch (...)
            {
                return;
            }
            if (Guardarjpg)
                try
                {
                    Bitmap1 = new Graphics::TBitmap();
                    Bitmap1->LoadFromFile(bmp_ane);
                    jp->Assign(Bitmap1);
                    jp->SaveToFile(jpg_ane);
                    delete Bitmap1;

                    Bitmap1 = new Graphics::TBitmap();
                    Bitmap1->LoadFromFile(bmp_tem);
                    jp->Assign(Bitmap1);
                    jp->SaveToFile(jpg_tem);
                    delete Bitmap1;

                    Bitmap1 = new Graphics::TBitmap();
                    Bitmap1->LoadFromFile(bmp_plu);
                    jp->Assign(Bitmap1);
                    jp->SaveToFile(jpg_plu);
                    delete Bitmap1;

                    Bitmap1 = new Graphics::TBitmap();
                    Bitmap1->LoadFromFile(bmp_llu);
                    jp->Assign(Bitmap1);
                    jp->SaveToFile(jpg_llu);
                    delete Bitmap1;

                    Bitmap1 = new Graphics::TBitmap();
                    Bitmap1->LoadFromFile(bmp_bar);
                    jp->Assign(Bitmap1);
                    jp->SaveToFile(jpg_bar);
                    delete Bitmap1;
                }
            __finally
            {
                delete jp;
            }
            refres_jpg = 0;

            CopyFile(jpg_ane, jpg2_ane,  NULL);
            CopyFile(jpg_tem, jpg2_tem,  NULL);
            CopyFile(jpg_plu, jpg2_plu,  NULL);
            CopyFile(jpg_llu, jpg2_llu,  NULL);
            CopyFile(jpg_bar, jpg2_bar,  NULL);

        }  //fin de refres_jpg >3
    refres_jpg++;
}

//------------------------------------------------------------------------------
// Timer de 5 sg
// Peticion de informacion de meteo cada 5 segundos
void __fastcall TForm1::Timer5000Timer(TObject *Sender)
//------------------------------------------------------------------------------
{
    /**************************
    Simulación envío telescopio
    **************************/
    //ProcesarCGEM();
    /*************************/

    if ((PBF->Position == 0) && (Lemav2->Visible == false))
    {
        indice_meteo++;
        strcpy(Buf_Meteo[indice_meteo],  "(R)");
    }
}

//------------------------------------------------------------------------------
// Timer de 3 sg
// Abortar espera de foto
// Regular temperatura.
void __fastcall TForm1::Timer3000Timer(TObject *Sender)
//------------------------------------------------------------------------------
{
    // necesario que T2/T3 = entero
    char aux[300];
    static int TiempoLectura;

    // EMAv2COM(); //llama a datos estacion

    // regular temperatura camaras
    if (PBF->Position == 0)
    {
        if (Form1->CBSelCamara->ItemIndex == 0)
        {
            if (CBregularTA->Checked == true)
                RegularTccdA();
        }
        else if (Form1->CBSelCamara->ItemIndex == 1)
        {
            if (CBregularTB->Checked == true)
                RegularTccdB();
        }
    }

    //limites del periodo de refresco coordenadas telescopio
    PerRefrescoTel = atoi(PerRefresco->Text.c_str()); //limita refresco coordenadas
    if (PerRefrescoTel > 10 || PerRefrescoTel < 1)
        PerRefresco->Text = 1;

    // Abortar epera de foto
    if ((FinFoto == false) && (nfotos > 0))
    {
        TiempoLectura = (CBCCD_A->ItemIndex + 1) * (CBCCD_A->ItemIndex + 1) * (32 / (PBinin->Caption * PBinin->Caption));
        int tiemp = atoi(Esg->Text.c_str()) + TiempoLectura;
        if ( DogFoto >  tiemp )
        {
            Historico->Mhistory->Lines->Add("Agotada espera foto " + AnsiString(nfotos - 1));
            DogFoto = 0;
            Form1->PCancelMouseUp(NULL, (TMouseButton)NULL, TShiftState(), 0, 0);
            Form1->BResetFocoClick(NULL);
        }
        DogFoto = DogFoto + 3;
    }

}

//------------------------------------------------------------------------------
// Timer de 100ms
// Gestion mensajes de red con el cor.
// Gestion mensajes CFS y Meteo
// Coordenadas Telescopio
void __fastcall TForm1::Timer100Timer(TObject *Sender)
//------------------------------------------------------------------------------
{
    char aux[3000];
    TJPEGImage *jp;
    TDateTime FalloCFS, FalloMeteo, Fech, DTenvio;

    AnsiString buffer;
    char temp[50];

    if (indice_cfs > 100)
    {
        Historico->Mhistory->Lines->Add("Indice CFS desbordado");
        indice_cfs = 0;
    }
    if (indice_meteo > 100)
    {
        Historico->Mhistory->Lines->Add("Indice Meteo desbordado");
        indice_meteo = 0;
    }

    //Envio de mensajes al CFS
    if (( indice_cfs > 0) && (PBF->Position == 0)) //si hay mensajes pendientes y no se lee foto
    {
        EsperaCfs++;
        if (cfs_resp)
        {
            EsperaCfs = 0;
            cfs_resp = false;
            aux[0] = 3;   //mensaje al CFS
            aux[1] = 0;
            strcpy(&aux[2], Buf_Cfs[indice_cfs]);
            if (S1 != NULL)
                S1->Escribir(aux, strlen(Buf_Cfs[indice_cfs]) + 2, S1->IPRabbit);
            indice_cfs--;
        }
        else if (EsperaCfs > 20)
        {
            cfs_resp = true;
            EsperaCfs = 0;
            Historico->Mhistory->Lines->Add("CFS NO RESPONDE");
        }

        /*
        if(cfs_resp && (EsperaCfs == 0))
        {
        	EsperaCfs = 1;
        	cfs_resp = false;
        	aux[0] = 3;   //mensaje al CFS
        	aux[1] = 0;
        	strcpy(&aux[2], Buf_Cfs[indice_cfs]);
        	if(S1 != NULL)
        	S1->Escribir(aux, strlen(Buf_Cfs[indice_cfs]) + 2, S1->IPRabbit);
        }
        else if((EsperaCfs >= 1) && (EsperaCfs < 20)) {
        	EsperaCfs ++;
        	if (cfs_resp) {
        	indice_cfs--;
        	EsperaCfs = 0;
        	}
        	else if (EsperaCfs == 20){

        	FalloCFS = Fecha.CurrentDateTime();
        	Historico->Mhistory->Lines->Add("CFS NO RESPONDE " + AnsiString(FalloCFS));
        	EsperaCfs = 21;
        	aux[0] = 3;   //mensaje al CFS
        	aux[1] = 0;
        	strcpy(&aux[2], "<rd>");
        	if(S1 != NULL)
        		S1->Escribir(aux, 4 + 2, S1->IPRabbit);
        	}
        }
        else if ((EsperaCfs >= 21) && (EsperaCfs <50)){
        	if (cfs_resp) {
        	EsperaCfs = 0;
        	indice_cfs = 0;
        	FalloCFS = Fecha.CurrentDateTime();
        	Historico->Mhistory->Lines->Add("CFS OK " + AnsiString(FalloCFS));
        	}
        	else {
        	EsperaCfs++;
        	aux[0] = 3;   //mensaje al CFS
        	aux[1] = 0;
        	strcpy(&aux[2], "<rd>");
        	if(S1 != NULL)
        		S1->Escribir(aux, 4 + 2, S1->IPRabbit);
        	}
        }

        else if (EsperaCfs == 50){
        	EsperaCfs = 21;
        }
        else EsperaCfs = 0;
        */
    }

    //Envio de mensajes Meteo
    if (( indice_meteo > 0) && (PBF->Position == 0)) //si hay que enviar y no se lee foto
    {
        if (EsperaMeteo < 2)
        {
            EsperaMeteo++;
        }
        else if (EsperaMeteo == 2) // 4 seg de espera
        {
            EsperaMeteo ++;
            TDateTime FalloMeteo;
            FalloMeteo = Fecha.CurrentDateTime();
            Historico->Mhistory->Lines->Add("METEO NO responde  " + AnsiString(FalloMeteo));
        }
        else if ((EsperaMeteo > 2) && (EsperaMeteo < 5))
        {
            EsperaMeteo ++;
        }
        aux[0] = 4;   //mensaje a Meteo
        aux[1] = 0;
        strcpy(&aux[2], Buf_Meteo[indice_meteo]);
        if (S1 != NULL)
            S1->Escribir(aux, strlen(Buf_Meteo[indice_meteo]) + 2, S1->IPRabbit);
        indice_meteo--;
    }

    //salida de mensajes para LX200
    if ((cont_mensLX > 0 && (PBF->Position == 0)))
    {
        if (CBver_envio_lx->Checked == true)
        {
            DTenvio = Fecha.CurrentTime();
            // Historico->Mhistory->Lines->Add ("EnvioLX " + AnsiString(buf_LX[ind_rdLX])+ " pend  " + AnsiString(cont_mensLX) + "  " + AnsiString(DTenvio));
            // Historico->Mhistory->Lines->Add (AnsiString(DTenvio) + "  EnvioLX " + AnsiString(buf_LX[ind_rdLX]) );
        }
        aux[0] = 2;  //mensaje para LX
        aux[1] = 0;
        // strcpy(&aux[2], buf_LX[ind_rdLX]); <== Está en el else

        if (S1 != NULL)
        {
            if (CGEM)
            {

                memcpy(&aux[2], buf_LX[ind_rdLX], len_buf_LX[ind_rdLX]);
                S1->Escribir(aux, len_buf_LX[ind_rdLX] + 2, S1->IPRabbit);

                sprintf(temp, "cont_mensLX: %d ", cont_mensLX);
                buffer = buffer + temp;
                sprintf(temp, ", ind_rdLX %d ", ind_rdLX);
                buffer = buffer + temp;

                if (len_buf_LX[ind_rdLX] > 2)
                {
                    aux[1] = 0;
                }

                for (int i = 0; i < len_buf_LX[ind_rdLX]; i++)
                {
                    sprintf(temp, "%02X ", buf_LX[ind_rdLX][i]);
                    //temp[i] = buf_LX[ind_rdLX + i][i];
                    //temp[i+1] = 0;
                    buffer = buffer + temp;
                }

                //WriteHistory("Escribir: " + AnsiString(buffer));

                /*
                // strcpy(&aux[2], buf_LX[ind_rdLX]);
                memcpy(&aux[2], buf_LX[ind_rdLX], len_buf_LX[ind_rdLX]);
                S1->Escribir(aux, strlen(buf_LX[ind_rdLX]) + 2, S1->IPRabbit);
                WriteHistory("Escribir: " + AnsiString(&aux[2]));
                */
            }
            else
            {
                strcpy(&aux[2], buf_LX[ind_rdLX]);
                S1->Escribir(aux, strlen(buf_LX[ind_rdLX]) + 2, S1->IPRabbit);
            }
        }
        cont_mensLX--;
        ind_rdLX++;
        if (ind_rdLX >= BUF_LX )
            ind_rdLX = 0;
    }

    //Recentrado AR Telescopio
    if (TiempoGuiaAR != 0.0)
    {
        CuentaGuiaAR++;
        if (CuentaGuiaAR > fabs(TiempoGuiaAR))
        {
            if (TiempoGuiaAR < 0.0)
            {
                EnviaLX("#:Qe#");
                // Historico->Mhistory->Lines->Add ("Qe " + AnsiString(::GetTickCount() - IniciaAR));
            }
            else
            {
                EnviaLX("#:Qw#");
                // Historico->Mhistory->Lines->Add ("Qw " + AnsiString(::GetTickCount() - IniciaAR));
            }
            CuentaGuiaAR = 0;
            TiempoGuiaAR = 0;
        }
        TimeRead = ::GetTickCount(); //para retrasar pedir coordenadas
    }


    //Recentrado Dec Telescopio
    if (TiempoGuiaDec != 0.0)
    {
        CuentaGuiaDec++;
        if (CuentaGuiaDec > fabs(TiempoGuiaDec))
        {
            if (TiempoGuiaDec < 0.0)
            {
                EnviaLX("#:Qs#");
                Historico->Mhistory->Lines->Add ("Qs " );
            }
            else
            {
                EnviaLX("#:Qn#");
                Historico->Mhistory->Lines->Add ("Qn " );
            }
            CuentaGuiaDec = 0;
            TiempoGuiaDec = 0;
        }
        TimeRead = ::GetTickCount(); //para retrasar pedir coordenadas
    }
    //cada tiempo se piden coordenadas
    if ((::GetTickCount() > (TimeRead + PerRefrescoTel * 1000)) && (LeyendoFoto == false))
    {
        TimeRead = ::GetTickCount();
        pedidaRaDe = true;
        //if (CBCGEM->Checked == false)   //es LX200
        if (LX200)   //es LX200
        {
            if ( cont_mensLX == 0)
            {
                EnviaLX("#:GR#:GD##:GA#:GZ#");
            }
            EsperaLX++;
        }
        else   //es montura CGEM
        {
            if ( cont_mensLX == 0)
            {
                if (HPREC)
                {
                    if (arde)
                    {
                        command = GetPreRAS_DEC;
                        EnviaLX("e");
                    }
                    else
                    {
                        command = GetPreAZM_ALT;
                        EnviaLX("z");
                    }
                }
                else
                {
                    if (arde)
                    {
                        command = GetRAS_DEC;
                        EnviaLX("E");
                    }
                    else
                    {
                        command = GetAZM_ALT;
                        EnviaLX("Z");
                    }
                }
                // arde = !arde; // Comentado siempre pide RAS_DEC nunca AZM_ALT
            }
            EsperaLX++;
        }
    }

    // Vigilar conexion Telescopio
    if (EsperaLX > 2) // despues de 2 sg
    {
        EsperaLX = 0;
        if (LXresponde)
        {
            LXresponde = false;

            Fech = Fecha.CurrentDateTime();
            if ( Form1->STPerdido->Caption == "DESCONECTADO")
            {
                Historico->Mhistory->Lines->Add( "LX200 Conectado     " + AnsiString(Fech) );
            }

            Form1->STPerdido->Caption = "CONECTADO";
            // Form1->STRa->Caption = AnsiString(nRAHour) + AnsiString("h") + AnsiString(dRAMin) + AnsiString("m");
            Form1->STRa->Caption = coordARE;
            //Form1->LAzimutRx->Caption = coordAZM;
            Form1->LAzimut->Caption = coordAZM;

            /*
            if (tDe > 0)
            	Form1->STDe->Caption = AnsiString("+") + AnsiString(nDecDeg) + AnsiString("º") + AnsiString(nDecMin) + AnsiString("'") ;
            else
            {
            	if (nDecDeg == 0)
            		Form1->STDe->Caption = AnsiString("-") + AnsiString(nDecDeg) + AnsiString("º") + AnsiString(nDecMin) + AnsiString("'") ;
            	else
            		Form1->STDe->Caption = AnsiString(nDecDeg) + AnsiString("º") + AnsiString(nDecMin) + AnsiString("'") ;
            }
            */
            Form1->STDe->Caption = coordDEC;
            //Form1->LAlturaRx->Caption = coordALT;
            Form1->LAltura->Caption = coordALT;

            Form1->arecta->Caption = carecta;
            Form1->declinacion->Caption = cdeclinacion;
        }
        else
        {
            Fech = Fecha.CurrentDateTime();
            if ( Form1->STPerdido->Caption == "CONECTADO")
            {
                Historico->Mhistory->Lines->Add( "LX200 Desconectado  " + AnsiString(Fech) );
            }
            STPerdido->Caption = "DESCONECTADO";

            // Form1->STRa->Caption = AnsiString(nRAHour) + AnsiString("h") + AnsiString(dRAMin) + AnsiString("m");
            Form1->STRa->Caption = coordARE;

            /*
            negativo = (nDecDeg < 0);
            if (negativo == 0)
            	Form1->STDe->Caption = AnsiString("+") + AnsiString(nDecDeg) + AnsiString("º") + AnsiString(nDecMin) + AnsiString("'") ;
            else
            	//Form1->STDe->Caption = AnsiString("-") + AnsiString(nDecDeg) + AnsiString("º") + AnsiString(nDecMin) + AnsiString("'") ;
            	Form1->STDe->Caption = AnsiString(nDecDeg) + AnsiString("º") + AnsiString(nDecMin) + AnsiString("'") ;
            */
            Form1->STDe->Caption = coordDEC;

            Form1->arecta->Caption = carecta;
            Form1->declinacion->Caption = cdeclinacion;
        }
    }


    if (LeyendoFoto == false)
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
    if (S1->PerdidaConexion == true)
    {
        EstadoRabbit = "    COR no responde";
        ColorEstado = clRed;

        TDateTime DTFalloCOR;
        AvisoCorOK = false;
        if (AvisoFalloCor == false)
        {
            AvisoFalloCor = true;
            DTFalloCOR = Fecha.CurrentDateTime();
            Historico->Mhistory->Lines->Add("COR NO Conectado " + DTFalloCOR);
        }
    }
    else
    {
        EstadoRabbit = AnsiString("    COR ") + AnsiString(S1->cadenaIPRabbit);
        ColorEstado = clLime;

        TDateTime DTConexionOK;
        AvisoFalloCor = false;
        if (AvisoCorOK == false)
        {
            AvisoCorOK = true;
            DTConexionOK = Fecha.CurrentDateTime();
            Historico->Mhistory->Lines->Add("COR Conectado OK " + DTConexionOK);
        }

        if (S1->nDatosRabbit >= 17)
        {
            S1->LeerRabbit(aux, 100);
            aux[18] = 0;
        }
        if (S1->nDatosCFS > 0)
        {
            ProcesarCFS();
        }
        if (S1->nDatosLX200 > 0)
        {
            if (CGEM)
                ProcesarCGEM();
            else
                ProcesarLX200();

        }
        if (S1->nDatosMeteo > 0)
        {
            ProcesarMeteo();
        }
        if (S1->nDatosTESs > 10)
        {
            ProcesarTESs();
        }

        actualizar_datos(); // refresca la informacion del panel de control
    }

    EstadoAnterior = EstadoRabbit;
    // PStatus->Font->Color = ColorEstado;
    SC->Brush->Color = ColorEstado;

}

//==============================================================================
void HacerFoto( short x1, short y1, short x2, short y2, unsigned char binin,
                short seg, short mseg, short NumCol, short NumFil,
                unsigned char test, unsigned char cancel, short nfotos,
                short limpiado, short obturador, short retraso, WideString nombppp)
//==============================================================================
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

    if (test != 0)
        *(BYTE*)&aux[6] = (char)binin + 10;
    else
        *(BYTE*)&aux[6] = (char)binin;

    *(WORD*)&aux[7] = (WORD)mseg;
    *(WORD*)&aux[9] = (WORD)seg;
    *(WORD*)&aux[11] = x1 * binin;
    *(WORD*)&aux[13] = y1 * binin;
    *(WORD*)&aux[15] = x2 * binin;
    *(WORD*)&aux[17] = y2 * binin;
    if (cancel != 0)
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
    else if (binin == 2)
    {
        *(BYTE*)&aux[23] = (BYTE)(sizeof(sec_2x2) / sizeof(char));
        memcpy(&aux[24],  sec_2x2, sizeof(sec_2x2));
    }
    else if (binin == 3)
    {
        *(BYTE*)&aux[23] = (BYTE)(sizeof(sec_3x3) / sizeof(char));
        memcpy(&aux[24],  sec_3x3, sizeof(sec_3x3));
    }
    else if (binin == 4)
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

//------------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
//------------------------------------------------------------------------------
{
    char aux[300];
    char sal = Salidas;


    if (bit1->Down == true)
    {
        sal ^= 0x01;
        bit1->Down = false;

        if (sal & 0x01)   // activa bit 1 del CFS
        {
            Panel11->Enabled = true; //permite mover motores
            indice_cfs++;
            strcpy(Buf_Cfs[indice_cfs],  "<yi>");
            //       indice_cfs++;
            //     strcpy(Buf_Cfs[indice_cfs],  "<zi>");

            indice_cfs++;
            strcpy(Buf_Cfs[indice_cfs],  "<mo>");
            indice_cfs++;
            strcpy(Buf_Cfs[indice_cfs],  "<eo>");  //activa bit dar tension
        }
        else
        {
            Panel11->Enabled = false;
            indice_cfs++;
            strcpy(Buf_Cfs[indice_cfs],  "<mf>");
            indice_cfs++;
            strcpy(Buf_Cfs[indice_cfs],  "<ef>");
        }
    }
    if (bit2->Down == true)
    {
        sal ^= 0x02;
        bit2->Down = false;

        indice_cfs++;
        if (sal & 0x02)  // activa bit 2 del CFS
            strcpy(Buf_Cfs[indice_cfs],  "<fo>");
        else
            strcpy(Buf_Cfs[indice_cfs],  "<ff>");
        //   S1->Escribir(aux, strlen("<fo>") + 2, S1->IPRabbit);
    }
    if (bit3->Down == true)
    {
        sal ^= 0x04;
        bit3->Down = false;

        if (sal & 0x04 )   // activa salida Meteo
        {
            indice_meteo++;
            strcpy(Buf_Meteo[indice_meteo],  "(X001)");
        }
        else
        {
            indice_meteo++;
            strcpy(Buf_Meteo[indice_meteo],  "(X000)");
        }

    }
    if (bit4->Down == true)
    {
        sal ^= 0x08;
        bit4->Down = false;
    }
    if (bit5->Down == true)
    {
        sal ^= 0x10;
        bit5->Down = false;
    }
    if (bit6->Down == true)
    {
        sal ^= 0x20;
        bit6->Down = false;
    }
    if (bit7->Down == true)
    {
        sal ^= 0x40;
        bit7->Down = false;
    }
    if (bit8->Down == true)
    {
        sal ^= 0x80;
        bit8->Down = false;
    }
    aux[0] = 10;
    aux[1] = 0;
    aux[2] = sal;
    S1->Escribir(aux, 8, S1->IPRabbit);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::LConfigurarClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    TFConfiguracion *F;

    F = new TFConfiguracion(this);
    F->ShowModal();
    delete F;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BAbrirClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    fitsfile *fptr;                          // pointer to the FITS file, defined in fitsio.h
    int status, nkeys, keypos, hdutype, ii, jj;
    char filename[FLEN_FILENAME];                // input FITS file
    char card[FLEN_CARD];                        // standard string lengths defined in fitsioc.h

    char aux[300];
    int ejes;
    long ajes[4];
    int tipo;

    if (OD1->Execute())
    {
        if ((fptr = AbrirFoto(OD1->FileName.c_str())) == NULL)
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

//------------------------------------------------------------------------------
void __fastcall TForm1::BGuardarClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    AnsiString N;

    if (SD1->Execute())
    {
        if (!SD1->FileName.AnsiPos(".fit") && !SD1->FileName.AnsiPos(".FIT"))
            N = SD1->FileName + ".fit";
        else
            N = SD1->FileName;

        if (FileExists(N))
        {
            if (Application->MessageBox("El Fichero ya existe. ¿Sobrescribir?", "OJO", MB_OKCANCEL	) == IDOK	)
            {
                DeleteFile(N);
            }
        }

        GuardarFoto(N.c_str());
    }
    else
        return;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::TBx0Change(TObject *Sender)
//------------------------------------------------------------------------------
{
    double x, y;

    x = TBx0->Position;
    y = TBy0->Position;

    if (y != x)
    {
        x0 = (-255.0 * x) / (y - x);
        y0 = 255.0 / (y - x);
    }
    else
    {
        x0 = 0.0;
        y0 = 1.0;
    }


    Ex0->Text = TBx0->Position;
    Ey0->Text = TBy0->Position;
    if (FActivo != NULL)
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

//------------------------------------------------------------------------------
void __fastcall TForm1::PCancelMouseDown(TObject *Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
//------------------------------------------------------------------------------
{
    ((TPanel*)Sender)->BevelOuter = bvLowered;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::PCancelMouseUp(TObject *Sender,
                                       TMouseButton Button, TShiftState Shift, int X, int Y)
//------------------------------------------------------------------------------
{
    LeyendoFoto = false;
    FinFoto = true;
    FotoActual = 1;
    nfotos = 0;
    PFoto->BevelOuter = bvRaised;
    PFoto->Color = clSilver;
    SLedFoto->Brush->Color = clGray;
    Panel5->Enabled = true;
    if (Sender != NULL)
        ((TPanel*)Sender)->BevelOuter = bvRaised;
    TiempoPasado->Caption = 0;
    TNFotos->Caption = 1;
    PBF->Position = 0;
    Form1->CBAutoEnfoque->State = cbUnchecked;

    //  indice_cfs++;
    //   strcpy(Buf_Cfs[indice_cfs],  "<xf>"); // primero xo es LIFO
    //    FinX = 1;

    if (AutoEnfoque > 1)
        AutoEnfoque = 5;


    /*
    	if (AutoEnfoque >1) {
    		AutoEnfoque = 0;
    		Form4->PDatosV->Caption =  " Curva Invalida. Retornando al Punto Inicial";
    		pasos_x = abs(contador_pasos) + pos_inicio;
    	sentido = '-';
    	MueveEnfoque();
    }
    */

}

//------------------------------------------------------------------------------
void __fastcall TForm1::PB1Paint(TObject *Sender)
//------------------------------------------------------------------------------
{
    RellenarBitmap(0, 0, FotoPrincipal->BM->Width, FotoPrincipal->BM->Height);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::RBHClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    Lupa(celdaX, celdaY, FotoPrincipal, true);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::CBSelCamaraChange(TObject *Sender)
//------------------------------------------------------------------------------
{
    if (CBSelCamara->ItemIndex == 0)
    {
        NumeroFilas = CCDs[CBCCD_A->ItemIndex].FilasFisicas / Binin;
        NumeroColumnas = CCDs[CBCCD_A->ItemIndex].ColumnasFisicas / Binin;
        Y1F =  CCDs[CBCCD_A->ItemIndex].FilaInicio / Binin;;
        X1F = CCDs[CBCCD_A->ItemIndex].ColumnaInicio / Binin;;
        Y2F =  CCDs[CBCCD_A->ItemIndex].FilaFin / Binin;;
        X2F = CCDs[CBCCD_A->ItemIndex].ColumnaFin / Binin;;
    }
    else
    {
        NumeroFilas = CCDsB[CBCCD_B->ItemIndex].FilasFisicas / Binin;
        NumeroColumnas = CCDsB[CBCCD_B->ItemIndex].ColumnasFisicas / Binin;
        Y1F = CCDsB[CBCCD_B->ItemIndex].FilaInicio / Binin;;
        X1F = CCDsB[CBCCD_B->ItemIndex].ColumnaInicio / Binin;;
        Y2F = CCDsB[CBCCD_B->ItemIndex].FilaFin / Binin;;
        X2F = CCDsB[CBCCD_B->ItemIndex].ColumnaFin / Binin;;
    }
    PX1->Caption = X1F;
    PY1->Caption = Y1F;
    PX2->Caption = X2F;
    PY2->Caption = Y2F;
    PB1->Width = NumeroColumnas;
    PB1->Height = NumeroFilas;
    PBinin->Caption = (int)Binin;
    TBBinin->Position = (int)Binin;
    PBF->Position = 0;
    FotoPrincipal->Resizear(NumeroColumnas, NumeroFilas);
    RellenarBitmap(0, 0, NumeroColumnas, NumeroFilas);
    //   Memo1->Lines->Add("change cam Y1F: " + AnsiString(Y1F) + "  Y2F: " + AnsiString(Y2F));
}

//------------------------------------------------------------------------------
void __fastcall TForm1::CBCCD_A_Change(TObject *Sender)
//------------------------------------------------------------------------------
{

    EFilaInicioA->Text = CCDs[CBCCD_A->ItemIndex].FilaInicio;// / Binin;
    EFilaFinA->Text = CCDs[CBCCD_A->ItemIndex].FilaFin;// / Binin;
    EColumnaInicioA->Text = CCDs[CBCCD_A->ItemIndex].ColumnaInicio;// / Binin;
    EColumnaFinA->Text = CCDs[CBCCD_A->ItemIndex].ColumnaFin;// / Binin;


    CCDs[CBCCD_A->ItemIndex].FilaInicio = EFilaInicioA->Text.ToInt();
    CCDs[CBCCD_A->ItemIndex].FilaFin = EFilaFinA->Text.ToInt();
    CCDs[CBCCD_A->ItemIndex].ColumnaInicio = EColumnaInicioA->Text.ToInt();
    CCDs[CBCCD_A->ItemIndex].ColumnaFin =  EColumnaFinA->Text.ToInt();
    TForm1::CBSelCamaraChange(NULL);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::CBCCD_B_Change(TObject *Sender)
//------------------------------------------------------------------------------
{
    EFilaInicioB->Text = CCDsB[CBCCD_B->ItemIndex].FilaInicio;// / Binin;
    EFilaFinB->Text = CCDsB[CBCCD_B->ItemIndex].FilaFin;// / Binin;
    EColumnaInicioB->Text = CCDsB[CBCCD_B->ItemIndex].ColumnaInicio;// / Binin;
    EColumnaFinB->Text = CCDsB[CBCCD_B->ItemIndex].ColumnaFin;// / Binin;

    CCDsB[CBCCD_B->ItemIndex].FilaInicio =  EFilaInicioB->Text.ToInt();
    CCDsB[CBCCD_B->ItemIndex].FilaFin = EFilaFinB->Text.ToInt();
    CCDsB[CBCCD_B->ItemIndex].ColumnaInicio = EColumnaInicioB->Text.ToInt();
    CCDsB[CBCCD_B->ItemIndex].ColumnaFin = EColumnaFinB->Text.ToInt();

    TForm1::CBSelCamaraChange(NULL);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::CBGuardarClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    if (((TCheckBox*)Sender)->State == cbChecked)
    {
        ENombreFichero->Enabled = true;
    }
    else
    {
        // ENombreFichero->Enabled = false;
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::EFilaFinAChange(TObject *Sender)
//------------------------------------------------------------------------------
{
    /*
    if(EFU->Text.ToInt() > CCDs[CBCCD_A->ItemIndex].FilasFisicas)
    	EFU->Text = CCDs[CBCCD_A->ItemIndex].FilasFisicas;
    CCDs[CBCCD_A->ItemIndex].FilasUtiles = EFU->Text.ToInt();
    NumeroColumnas = ECU->Text.ToInt() / Binin;
    NumeroFilas = EFU->Text.ToInt() / Binin;
    offsetx = (CCDs[CBCCD_A->ItemIndex].ColumnasFisicas - CCDs[CBCCD_A->ItemIndex].ColumnasUtiles)/2;
    offsety = (CCDs[CBCCD_A->ItemIndex].FilasFisicas - CCDs[CBCCD_A->ItemIndex].FilasUtiles)/2;
    if(CBR->State == cbUnchecked)
    {
    	PX1->Caption = 0;
    	PX2->Caption = ECU->Text;
    	PY1->Caption = 0;
    	PY2->Caption = EFU->Text;
    }
    */
}

//==============================================================================
// Envia orden de moverse al motor de enfoque
void MueveEnfoque()
//==============================================================================
{
    char pasos[10];
    char periodox[4];
    AnsiString A;

    sprintf(pasos, "%0005d", pasos_x);
    sprintf(periodox, "%02d", periodo_x);

    FinX = 0;

    A = AnsiString("<x") +
        pasos +
        sentido +
        periodox +
        AnsiString(">");

    pasos_enviados = pasos_x;

    indice_cfs++;
    strcpy(Buf_Cfs[indice_cfs],  "<xo>");         // primero xo es LIFO

    if ((AutoEnfoque != 4) || (FotoActual < 3))   // para no repetir configuracion enfocando
    {
        indice_cfs++;
        strcpy(Buf_Cfs[indice_cfs],  A.c_str());
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::subirClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    if (FinX == 1)
    {
        pasos_x = Form1->EPasosEnfoque->Text.ToInt();
        sentido = '-';
        MueveEnfoque();
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::bajarClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    if (FinX == 1)
    {
        pasos_x = Form1->EPasosEnfoque->Text.ToInt();
        sentido = '+';
        MueveEnfoque();
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BResetFocoClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    indice_cfs++;
    strcpy(Buf_Cfs[indice_cfs],  "<tf>");    // primero xo es LIFO
    //  errorcfs = 0; //desbloquea recepcion cfs
    FinX = 1;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
//------------------------------------------------------------------------------
{
    indice_cfs++;
    strcpy(Buf_Cfs[indice_cfs],  "<xf>"); // primero xo es LIFO

    FinX = 1;
}

//==============================================================================
void Lupa(int X, int Y, cFoto *Foto, bool actualizar)
//==============================================================================
{
    float auxf;
    char aux[300];
    TRect R, R2;
    int cx, cy;

    celdaX = X - 3;
    celdaY = Y - 3;

    for (int c1 = 0; c1 < 7; c1++)
    {
        for (int c2 = 0; c2 < 7; c2++)
        {
            R = Form1->DG1->CellRect(c2, c1);
            R2 = Form1->DG2->CellRect(c2, c1);
            cx = X - 3 + c2;
            cy = Y - 3 + c1;
            if ((cx == X) && (cy == Y))
                Form1->DG1->Canvas->Font->Color = clRed;
            else
                Form1->DG1->Canvas->Font->Color = clBlack;
            if (actualizar == true)
            {
                Form1->DG2->Canvas->Brush->Color = Colores[c1][c2];
                Form1->DG2->Canvas->FillRect(R2);
                if (Form1->RBH->Checked == true)
                    wsprintf(aux, "%04X", Valores[c1][c2]);
                else
                    wsprintf(aux, "%05u", Valores[c1][c2]);
                Form1->DG1->Canvas->TextRect(R, R.left + 1, R.top + 1, aux);
            }
            else
            {
                if ((cx >= 0) && (cx < Foto->BM->Width) && (cy >= 0) && (cy < Foto->BM->Height))
                {
                    Valores[c1][c2] = Foto->Pixeles[cy * Foto->BM->Width + cx];
                    auxf = Foto->xm0 + Valores[c1][c2] * Foto->ym0;
                    if (auxf >= 256)
                        Form1->DG2->Canvas->Brush->Color = (TColor)0x00FFFFFF;
                    else
                        Form1->DG2->Canvas->Brush->Color = (TColor)(0x00000000 | ((ULONG)auxf) & 0x000000FF |
                                                           (((ULONG)auxf) << 8) & 0x0000FF00 |
                                                           (((ULONG)auxf) << 16) & 0x00FF0000);
                    if (Form1->RBH->Checked == true)
                        wsprintf(aux, "%04X", Valores[c1][c2]);
                    else
                        wsprintf(aux, "%05u", Valores[c1][c2]);
                    Form1->DG1->Canvas->TextRect(R, R.left + 1, R.top + 1, aux);
                }
                else
                {
                    strcpy(aux, " ");
                    Form1->DG2->Canvas->Brush->Color = (TColor)0x00000000;
                    Valores[c1][c2] = 0;
                }
                Form1->DG1->Canvas->TextRect(R, R.left + 1, R.top + 1, aux);
                Form1->DG2->Canvas->FillRect(R2);
                Colores[c1][c2] = Form1->DG2->Canvas->Brush->Color;
            }
        }
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::PB1Click(TObject *Sender)
//------------------------------------------------------------------------------
{
    FActivo = NULL;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BFlipxClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    if (FActivo != NULL)
    {
        FActivo->Foto->flipx();
        FActivo->Pintar();

    }
    else if (LeyendoFoto == false)
    {
        FotoPrincipal->flipx();
        RellenarBitmap(0, 0, NumeroColumnas, NumeroFilas);
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::DG2DrawCell(TObject *Sender, int ACol, int ARow,
                                    TRect &Rect, TGridDrawState State)
//------------------------------------------------------------------------------
{
    Lupa(celdaX, celdaY, FotoPrincipal, true);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BFlipyClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    if (FActivo != NULL)
    {
        FActivo->Foto->flipy();
        FActivo->Pintar();
    }
    else if (LeyendoFoto == false)
    {
        FotoPrincipal->flipy();
        RellenarBitmap(0, 0, NumeroColumnas, NumeroFilas);
    }
}

//==============================================================================
// Actualiza la barra de horas
void barra_horas(void)
//==============================================================================
{
}

//==============================================================================
fitsfile * AbrirFoto(char *nombre)
//==============================================================================
{
    TForm2 *Form2;
    long primer_elemento = 1;
    long numelem;
    int cualquiernull = 0;
    Byte *ptr;
    short sust = 0;
    long ajes[4] = {0, 0, 0, 0};
    int ejex, ejey;
    fitsfile *fptr = 0;       // pointer to the FITS file, defined in fitsio.h
    int status;

    int ejes = 0;
    int tipo;

    double xc, yc, hf;
    int xi, yi, hfdi;

    Form1->PFicheroAbierto->Caption = nombre;
    status = 0;
    if ( fits_open_file(&fptr, nombre, READWRITE, &status) )
    {
        return NULL;
    }
    status = 0;
    if (ffgipr(fptr,  2, &tipo, &ejes, ajes, &status))
    {
        return NULL;
    }
    ejex = ajes[0];
    ejey = ajes[1];
    numelem = ejex * ejey;
    Form2 = new TForm2(Form1->PFotoO);
    Form2->Caption = nombre;
    Form2->Crear(ejex, ejey);
    status = 0;

    if (fits_read_img(fptr, TSHORT, primer_elemento, numelem,
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

    if (y != x)
    {
        x0 = (-255.0 * x) / (y - x);
        y0 = 255.0 / (y - x);
    }
    else
    {
        x0 = 0.0;
        y0 = 1.0;
    }

    Form2->Foto->xm0 = x0;
    Form2->Foto->ym0 = y0;
    Form2->PMax->Caption = Form2->Foto->maximo;
    Form2->PMin->Caption = Form2->Foto->minimo;
    Form2->Edit1->Text = media;
    Form2->Edit2->Text = Form2->Foto->fondocielo;
    Form2->Edit3->Text = Form2->Foto->fullhalfwide();

    Form2->Pintar();
    Form2->Show();

    //  AF_SetLogLevel(AF_LOG_DEBUG);  /* subimos el nivel de log por defecto */

    if ((Form1->CBAutoEnfoque->State == cbChecked) )
    {
        if (Form1->CBhfd->State == cbChecked)
        {
            int height = Form2->Foto->BM->Height;
            int width = Form2->Foto->BM->Width;

            if ((height < 200) && (width < 300) && (Form1->CBAutoEnfoque->State == cbChecked) )
            {
                ACOR_SetImage((short*)Form2->Foto->Pixeles, width, height);
                AF_SetSkyRegion(1, 1, width - 2, height - 2);
                AF_SetCentroidRegion(1, 1, width - 2, height - 2);
                hfd = AF_HFD(NULL);
            }
            else
                Historico->Mhistory->Lines->Add("Foto muy grande para hfd ");

            // float xc,yc;

            hf = hfd;
            if (Form1->CBhfd->State == cbChecked)
                AF_GetCentroid(&xc, &yc);
            hfdi = hf * 10;
            hf = hfdi / 10.0;
            xi = xc * 10;
            xc = xi / 10.0;
            yi = yc * 10;
            yc = yi / 10.0;
            Historico->Mhistory->Lines->Add("hfd " + AnsiString(hf) + "  X " + AnsiString(xc) + " Y " + AnsiString(yc) );
        }
        else
            hfd = (float)spizer / 100;
        // No se puede pedir el centroide sin haber llamado a AF_HFD primero
        cuentita += 100;
        AF_AddMeasurement(cuentita, hfd);


        Form4->Series1->AddXY(cuentita, hf, cuentita , clRed);
    }
    return fptr;
}

//==============================================================================
// Funcioncilla auxiliar para reconvertir coordenadas
// AR para que las lea Astrometrica de la cabecera FITS
AnsiString ReconvShortAR(AnsiString arin)
//==============================================================================
{
    /*
    sprintf(aux.c_str(), " %02dh %02dm %02d.%02ds", RAHor, RAMin, RASec, RACse);
    */

    int res, myhh, myintmin, myfracmin, mysec, mycsec;
    char buf[16];
    /*
    res = sscanf(arin.c_str(), "%dh%d,%d", &myhh, &myintmin, &myfracmin);
    if (res == 2)
    	myfracmin = 0;

    mysec = myfracmin * 6;
    */
    sscanf(arin.c_str(), "%dh %dm %d.%ds", &myhh, &myintmin, &mysec, &mycsec);

    // FITS OBJCTRA value
    //sprintf(buf, "%02d:%02d:%02d", myhh, myintmin, mysec);
    sprintf(buf, "%02d %02d %02d", myhh, myintmin, mysec);
    return (AnsiString(buf));
}

//==============================================================================
// Funcioncilla auxiliar para reconvertir coordenadas
// DEC para que las lea Astrometrica de la cabecera FITS
AnsiString ReconvShortDEC(AnsiString decin)
//==============================================================================
{

    //sprintf(aux, "%c%02dº %02d' %02d.%02d\"", cSign, DECGra, DECMin, DECSec, DECCse);



    // int res, myhh, myintmin, myfracmin, mysec, mycsec;
    char buf[16];
    char cSign;
    int DECGra, DECMin, DECSec, DECCse;

    sscanf(decin.c_str(), "%c%02dº %02d' %02d.%02d\"", &cSign, &DECGra, &DECMin, &DECSec, &DECCse);

    /*
    res = sscanf(arin.c_str(), "%dh%d,%d", &myhh, &myintmin, &myfracmin);
    if (res == 2)
    	myfracmin = 0;

    mysec = myfracmin * 6;
    */

    //FITS OBJCTDEC value
    //sprintf(buf, "%c%02d:%02d:%02d", cSign, DECGra, DECMin, DECSec);
    sprintf(buf, "%c%02d %02d %02d", cSign, DECGra, DECMin, DECSec);
    return (AnsiString(buf));
}

//==============================================================================
// FUNCION MODIFICADA POR RAFA (17/10/2004)
// La metainformación se graba como FITS keywords siguiendo el "Amateur FITS
// Standard" v1.0, del 19 de Marzo de 2003 en lo que me ha parecido conveniente

// ATENCION: El comporamiento de la CFITSIO de la NASA es que si se incluyen
// en la cabecera BZERO y BSCALE, la grabación de los datos de la imagen se
// realiza con un reescalado previo. En nuestro caso BSCALE=1.0 y BZERO=0.0,
// esto es una absoluta perdida de tiempo. Por ello no se incluyen en la
// cabecera y en este sentido no siguen el "Amateur FITS Standard"
void GuardarFoto(char* nombre)
//==============================================================================
{
    fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */
    int status;
    int ejexg, ejeyg;
    //AnsiString NC;
    ejexg = X2F - X1F;
    ejeyg = Y2F - Y1F;
    long npixel = (X2F - X1F) * (Y2F - Y1F); // - 1;

    status = 0;

    Historico->Mhistory->Lines->Add("Guardando Fichero: " + (AnsiString)(nombre));


    if (fits_create_file(&fptr, nombre, &status))
    {
        status = 0;

        if ( fits_open_file(&fptr, nombre, READWRITE, &status) )
        {
            Historico->Mhistory->Lines->Add("Fallo en GuardarFoto");
            return;
        }
    }

    long axes[2];
    axes[0] = ejexg;
    axes[1] = ejeyg;
    if (fits_create_img(fptr, SHORT_IMG, 2, axes, &status))
    {
        Application->MessageBox("Error creando imagen", "Alert!", MB_OK);
        return;
    }

    unsigned short *datos;
    datos = new unsigned short [npixel + 1];
    memset(datos, 0, npixel * 2);

    // controla como se guarda la imagen, flip vertical - horizontal
    if (Form1->CBFlipVertical->State == cbChecked)
    {
        for (int py = Y1F; py <= Y2F - 1; py++)
        {
            if (Form1->CBFlipHorizontal->State == cbChecked)
                for (int px = X1F; px < X2F; px++)      //haria un flip horizontal
                    datos[npixel--] = FotoPrincipal->Pixeles[py * FotoPrincipal->BM->Width + px];
            else
                for (int px = (X2F - 1); px >= X1F; px--)
                    datos[npixel--] = FotoPrincipal->Pixeles[py * FotoPrincipal->BM->Width + px];
        }
    }
    else
    {
        for (int py = Y2F - 1; py >= Y1F; py--)
        {
            if (Form1->CBFlipHorizontal->State == cbChecked)
                for (int px = X1F; px < X2F; px++)      //haria un flip horizontal
                    datos[npixel--] = FotoPrincipal->Pixeles[py * FotoPrincipal->BM->Width + px];
            else
                for (int px = (X2F - 1); px >= X1F; px--)
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

    fits_write_key(fptr, TSTRING, "SITELONG",  Form1->ELongitud->Text.c_str() , "Site Longitude", &status);
    fits_write_key(fptr, TSTRING, "SITELAT", Form1->ELatitud->Text.c_str() , "Site Latitude", &status);

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

    //  float aptdiam = 203;
    //  float aptarea = 0;

    if (Form1->CBSelCamara->ItemIndex == 0)
    {
        //    fits_write_key(fptr, TSTRING, "OBSERVER", Form1->EObserver->Text.c_str(), NULL, &status);
        fits_write_key(fptr, TSTRING, "TELESCOP", Form1->ETelescop->Text.c_str(), NULL, &status);

        fits_write_key(fptr, TSTRING, "FOCALLEN", Form1->EFocal->Text.c_str(), "Distancia focal", &status);
        fits_write_key_unit(fptr, "FOCALLEN", "mm", &status);

        fits_write_key(fptr, TSTRING, "APTDIA", Form1->EApert->Text.c_str(), "Apertura", &status);
        fits_write_key_unit(fptr, "APTDIA", "mm", &status);

        //  fits_write_key(fptr, TSTRING, "APTAREA", &aptarea, "Effective collecting area", &status);
        //  fits_write_key_unit(fptr, "APTAREA", "mm^2", &status);

        fits_write_key(fptr, TSTRING, "INSTRUME", Form1->EInstrument->Text.c_str(), NULL, &status);
    }

    float pixsz = 9 * Binin; /* valido para x e y */

    fits_write_key(fptr, TSTRING, "OBSERVER", Form1->EObserver->Text.c_str(), NULL, &status);
    fits_write_key(fptr, TFLOAT, "XPIXSZ", &pixsz, "Effective pixel width", &status);
    fits_write_key_unit(fptr, "XPIXSZ", "um", &status);
    fits_write_key(fptr, TFLOAT, "YPIXSZ", &pixsz, "Effective pixel height", &status);
    fits_write_key_unit(fptr, "YPIXSZ", "um", &status);
    fits_write_key(fptr, TBYTE, "XBINNING", &Binin, Form1->PBinin->Caption.c_str(), &status);
    fits_write_key(fptr, TBYTE, "YBINNING", &Binin, "Binning factor in height", &status);

    //Form1->Memo1->Lines->Add("guardar Y1F: " + AnsiString(Y1F) + "  Y2F: " + AnsiString(Y2F));


    float temperatura[3];

    if (Form1->CBSelCamara->ItemIndex == 0)  //camara principal
    {
        if (Form1->PTccdA->Caption == "---")
            temperatura[0] = 9999.0;
        else
            temperatura[0] = TccdA_grados;//StrToFloat(Form1->PTccdA->Caption);

        if (Form1->PTcajaA->Caption == "---")
            temperatura[1] = 9999.0;
        else
            temperatura[1] = StrToFloat(Form1->PTcajaA->Caption);

        if (Form1->PVpeltierA->Caption == "---")
            temperatura[2] = 9999.0;
        else
            temperatura[2] = StrToFloat(Form1->PVpeltierA->Caption);
    }
    else              //camara auxiliar
    {
        if (Form1->PTccdB->Caption == "---")
            temperatura[0] = 9999.0;
        else
            temperatura[0] = StrToFloat(Form1->PTccdB->Caption);

        if (Form1->PTcajaB->Caption == "---")
            temperatura[1] = 9999.0;
        else
            temperatura[1] = StrToFloat(Form1->PTcajaB->Caption);

        if (Form1->PVpeltierB->Caption == "---")
            temperatura[2] = 9999.0;
        else
            temperatura[2] = StrToFloat(Form1->PVpeltierB->Caption);
    }

    fits_write_key(fptr, TFLOAT, "CCD-TEMP", &temperatura[0] , "CCD temp. when exposure finished", &status);
    fits_write_key_unit(fptr, "CCD-TEMP", "C", &status);

    fits_write_key(fptr, TFLOAT, "AMB-TEMP", &temperatura[1] , "Ambient temp. when exposure finished", &status);
    fits_write_key_unit(fptr, "AMB-TEMP", "C", &status);

    fits_write_key(fptr, TFLOAT, "VOLTPELT", &temperatura[2] , "Peltier voltage when exposure finished", &status);
    fits_write_key_unit(fptr, "VOLTPELT", "V", &status);

    fits_write_key(fptr, TSTRING, "OBJECT", Form1->EObjeto->Text.c_str(), "Object name", &status);
    if (status)
    {
        fits_get_errstatus(status, fitserrmsg);
        Application->MessageBox(fitserrmsg, "ERROR fit!", MB_OK);
    }


    if (Form1->STPerdido->Caption == "CONECTADO") // Probar esto
    {
        /*
        AnsiString dec = Form1->STDe->Caption;
        int ps;

        if ((ps = dec.Pos("º")) != 0)
        	dec[ps] = ':';
        if ((ps = dec.Pos("'")) != 0)
        	dec[ps] = ':';
        dec += AnsiString("00"); // Segundos?
        */
        AnsiString ar  = ReconvShortAR( Form1->STRa->Caption);
        AnsiString dec = ReconvShortDEC(Form1->STDe->Caption);
        fits_write_key(fptr, TSTRING, "OBJCTRA",  ar.c_str() , "Aproximate image center", &status);
        fits_write_key(fptr, TSTRING, "OBJCTDEC", dec.c_str() , "Aproximate image center", &status);
    }

    DateSeparator = '-';
    //  FechaFoto_fin =  FechaFoto_fin.CurrentDateTime();
    //  FechaFoto_fin -= ((A_T_Fin_Lect - A_T_Ini_Exp) / (24.0 * 60.0 * 60.0 * 1000.0));
    FechaFoto_fin = FechaFoto - ( ((A_T_Fin_Lect - A_T_Ini_Exp) / (24.0 * 60.0 * 60.0 * 1000.0)));
    //  FechaFoto += (7000.0 / (24.0 * 60.0 * 60.0 * 1000.0));
    fits_write_key(fptr, TSTRING, "DATE-OBS", FechaFoto_fin.FormatString("yyyy/mm/dd'T'hh:mm:ss").c_str(), "Exposure starts, Local Time", &status);


    float exptime; //= atof(Form1->Esg->Text.c_str()) + atof(Form1->Emsg->Text.c_str())/1000 + float(Form1->ERetraso->Text.ToInt())/10;
    float darktime;// = exptime;
    exptime = (A_T_Ini_Lect - A_T_Ini_Exp) / 1000.0;
    //  darktime =  A_T_Fin_Lect - A_T_Ini_Lect + atoi(Form1->ERetraso->Text.c_str()) *100;
    darktime =  A_T_Fin_Lect - A_T_Ini_Exp;
    darktime =  darktime / 1000.0 ;

    fits_write_key(fptr, TFLOAT, "EXPTIME", &exptime , "Exposure time", &status);
    fits_write_key_unit(fptr, "EXPTIME", "sg", &status);

    fits_write_key(fptr, TFLOAT, "DARKTIME", &darktime , "Exposure time + readout time", &status);
    fits_write_key_unit(fptr, "DARKTIME", "sg", &status);

    fits_write_date(fptr, &status);  /* fecha de creacion del fichero */

    fits_write_comment (fptr, Form1->EComent->Text.c_str(), &status);

    fits_write_img(fptr, TSHORT, 1, ejexg * ejeyg, datos, &status);
    fits_close_file(fptr, &status);
    delete datos;
    return;
}

//------------------------------------------------------------------------------
// FUNCIONES LX200
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void __fastcall TForm1::BstopClick(TObject *Sender)
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
void __fastcall TForm1::BOClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    if (((TSpeedButton*)Sender)->Down == true)
        ((TSpeedButton*)Sender)->Down = false;
    else
        ((TSpeedButton*)Sender)->Down = true;
}

//==============================================================================
// Bufer de salida al Telescopio para LX200
void EnviaLX(char *orden)
//==============================================================================
{
    // WriteHistory("EnviaLX: " + AnsiString(orden));

    strcpy(buf_LX[ind_wrLX], orden);
    len_buf_LX[ind_wrLX] = strlen(orden);

    ind_wrLX++;
    if (ind_wrLX >= BUF_LX)
        ind_wrLX = 0;

    cont_mensLX++;
}

//==============================================================================
// Bufer de salida al Telescopio para CGEM
void EnviaLX(char *orden, int long_orden)
//==============================================================================
{
    AnsiString buffer;
    AnsiString bufConta;
    char aux[50];
    char temp[50];
    short ordenByte;

    memcpy(buf_LX[ind_wrLX], orden, long_orden);
    len_buf_LX[ind_wrLX] = long_orden;

    for (int i = 0; i < long_orden; i++)
    {
        ordenByte = (orden[i] < 0) ? (orden[i] + 256) : orden[i];
        //sprintf(aux, "%02X ", orden[i]);
        sprintf(aux, "%02X ", ordenByte);
        buffer = buffer + aux;
    }

    sprintf(temp, "cont_mensLX: %d ", cont_mensLX);
    bufConta = bufConta + temp;
    sprintf(temp, ", ind_wrLX %d ", ind_wrLX);
    bufConta = bufConta + temp;

    WriteHistory(CmdToStr(command) + " EnviaLX: " + AnsiString(buffer) + " " + AnsiString(bufConta));

    ind_wrLX++;
    if (ind_wrLX >= BUF_LX)
        ind_wrLX = 0;

    cont_mensLX++;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BSMouseDown(TObject *Sender, TMouseButton Button,
                                    TShiftState Shift, int X, int Y)
//------------------------------------------------------------------------------
{

    /* Velocidades de LX200:
       SLW: Slew       8º/sec a 6º/sec
       FND: Find       2º/sec
       CEN: Centrado 480 arcsec/sec
       GUI: Guiado    30 arcsec/sec

       Velocidades CGEM:
       1 = .5x                   8 arcsec/sec
       2 = 1x (sidereal)        15 arcsec/sec
       3 = 4x   60 arcsec/sec =  1 arcmin/sec
       4 = 8x  120 arcsec/sec =  2 arcmin/sec
       5 = 16x 240 arcsec/sec =  4 arcmin/sec
       6 = 64x 960 arcsec/sec = 16 arcmin/sec
       7 =    3600 arcsec/sec =  1 º/sec
       8 =    7200 arcsec/sec =  2 º/sec
       9 =   18000 arcsec/sec =  5 º/sec
    */

    /* int arcsecBySec = 36000; // 1º/s
       Esta es la velocidad que probamos primero, como 1º/s, pero según el
       manual de CGEM este valor rate=7 es de 3600 arcsec/sec. El valor máximo
       no puede superar 16383, para que multiplicando por 4 y dividiendo
       por 256 de 255 y resto 252 ambos valores entre 0 y 255.
       Según este algoritmo, la velocidad máxima será de 16383 arcsec/sec
       que equivale a ~ 4,6 º/sec
    */

    /* Según todo lo anterior las velocidades asignadas a cada botón tipo LX200
       serán:
       SLW: Slew     Rate=9 16383 arcsec/sec ~  5 º/sec
       FND: Find     Rate=7  3600 arcsec/sec =  1 º/sec
       CEN: Centrado Rate~5   480 arcsec/sec =  4 arcmin/sec
       GUI: Guiado   Rate=2-3  30 arcsec/sec = 30 arcsec/sec

    */

    int arcsecBySec = SlewSpeed;

    int TrackRateAltHigh = (arcsecBySec * 4) / 256;
    int TrackRateAltLow = (arcsecBySec * 4) % 256;

    char stopTrk[] = {'T', 0};  // Set tracking mode to 0 (Off)
    //char starTrk[] = {'T', 2};  // Set tracking mode to 2 (EQ North)


    // Var=3
    // Fix=2

    // RAS=16
    // DEC=17

    // Pos=6 (Var)
    // Neg=7 (Var)

    // Pos=36 (Fix)
    // Neg=37 (Fix)

    // Variable rate Azm (or RA) slew in positive direction
    char slewCmdVarRASPos[] = {80, 3, 16,  6, 0, 0, 0, 0};
    // Variable rate Azm (or RA) slew in negative direction
    char slewCmdVarRASNeg[] = {80, 3, 16,  7, 0, 0, 0, 0};
    // Variable rate Alt (or DEC) slew in positive direction
    char slewCmdVarDECPos[] = {80, 3, 17,  6, 0, 0, 0, 0};
    // Variable rate Alt (or DEC) slew in negative direction
    char slewCmdVarDECNeg[] = {80, 3, 17,  7, 0, 0, 0, 0};
    // Fixed rate Azm (or RA) slew in positive direction
    //char slewCmdFixRASPos[] = {80, 2, 16, 36, 0, 0, 0, 0};
    // Fixed rate Azm (or RA) slew in negative direction
    char slewCmdFixRASNeg[] = {80, 2, 16, 37, 0, 0, 0, 0};
    // Fixed rate Alt (or DEC) slew in positive direction
    //char slewCmdFixDECPos[] = {80, 2, 17, 36, 0, 0, 0, 0};
    // Fixed rate Alt (or DEC) slew in negative direction
    char slewCmdFixDECNeg[] = {80, 2, 17, 37, 0, 0, 0, 0};

    //  slewCmd[4] = slewRate;

    /*
    Lógica del programa de VB functions.bas que mueve el telescopio conectado por RS-232

    Stop Tracking. "T0" strScopeResponse = ScopeComm("T" & Chr(0), 1, 500)

    If slew RIGHT

    	Stop DEC motor. Fixed rate ALT (or DEC) slew in negative direction
    	strCoord = Chr(80) & Chr(2) & Chr(17) & Chr(37) & Chr(0) & Chr(0) & Chr(0) & Chr(0)
    	strScopeResponse = ScopeComm(strCoord, 1, 500)

    	Slew RA positive. Variable rate Azm (or RA) slew in positive direction
    	strCoord = Chr(80) & Chr(3) & Chr(16) & Chr(6) & Chr(TrackRateAzHigh) & Chr(TrackRateAzLow) & Chr(0) & Chr(0)
    	strScopeResponse = ScopeComm(strCoord, 1, 500)

    If slew UP

    	Stop RA motor. Fixed rate Azm (or RA) slew in negative direction
    	strCoord = Chr(80) & Chr(2) & Chr(16) & Chr(37) & Chr(0) & Chr(0) & Chr(0) & Chr(0)
    	strScopeResponse = ScopeComm(strCoord, 1, 500)

    	Slew DEC negative. Variable rate Alt (or Dec) slew in negative direction
    	strCoord = Chr(80) & Chr(3) & Chr(17) & Chr(7) & Chr(TrackRateAltHigh) & Chr(TrackRateAltLow) & Chr(0) & Chr(0)
    	strScopeResponse = ScopeComm(strCoord, 1, 500)

    If slew LEFT

    	Stop DEC motor. Fixed rate ALT (or DEC) slew in negative direction
    	strCoord = Chr(80) & Chr(2) & Chr(17) & Chr(37) & Chr(0) & Chr(0) & Chr(0) & Chr(0)
    	strScopeResponse = ScopeComm(strCoord, 1, 500)

    	Slew RA negative. Variable rate Azm (or RA) slew in negative direction
    	strCoord = Chr(80) & Chr(3) & Chr(16) & Chr(7) & Chr(TrackRateAzHigh) & Chr(TrackRateAzLow) & Chr(0) & Chr(0)
    	strScopeResponse = ScopeComm(strCoord, 1, 500)

    If slew DOWN

    	Stop RA motor. Fixed rate Azm (or RA) slew in negative direction
    	strCoord = Chr(80) & Chr(2) & Chr(16) & Chr(37) & Chr(0) & Chr(0) & Chr(0) & Chr(0)
    	strScopeResponse = ScopeComm(strCoord, 1, 500)

    	Slew DEC positive. Variable rate Alt (or Dec) slew in positive direction
    	strCoord = Chr(80) & Chr(3) & Chr(17) & Chr(6) & Chr(TrackRateAltHigh) & Chr(TrackRateAltLow) & Chr(0) & Chr(0)
    	strScopeResponse = ScopeComm(strCoord, 1, 500)


    */

    if (CGEM)
    {
        command = SetTrackMode;
        EnviaLX(stopTrk, 2);
        if (Sender == BN)   // slew up
        {
            // Stop (rate = 0) Fixed rate Azm (or RA) slew in negative direction
            // char slewCmdFixRASNeg[] = {80, 2, 16, 37, 0, 0, 0, 0};
            command = FixRASNeg;
            EnviaLX(slewCmdFixRASNeg, 8);

            // Variable rate Alt (or Dec) slew in negative direction
            // char slewCmdVarDECNeg[] = {80, 3, 17,  7, trHig, trLow, 0, 0};
            slewCmdVarDECNeg[4] = TrackRateAltHigh;
            slewCmdVarDECNeg[5] = TrackRateAltLow;
            command = VarDECNeg;
            EnviaLX(slewCmdVarDECNeg, 8);
        }
        else if (Sender == BO)   // slew Left
        {
            // Stop (rate = 0) Fixed rate ALT (or DEC) slew in negative direction
            // char slewCmdFixDECNeg[] = {80, 2, 17, 37, 0, 0, 0, 0};
            command = FixDECNeg;
            EnviaLX(slewCmdFixDECNeg, 8);

            // Variable rate Azm (or RA) slew in negative direction
            // char slewCmdVarRASNeg[] = {80, 3, 16,  7, trHig, trLow, 0, 0};
            slewCmdVarRASNeg[4] = TrackRateAltHigh;
            slewCmdVarRASNeg[5] = TrackRateAltLow;
            command = VarRASNeg;
            EnviaLX(slewCmdVarRASNeg, 8);
        }
        else if (Sender == BS)   // slew down
        {
            // Stop (rate = 0) Fixed rate Azm (or RA) slew in negative direction
            // char slewCmdFixRASNeg[] = {80, 2, 16, 37, 0, 0, 0, 0};
            command = FixRASNeg;
            EnviaLX(slewCmdFixRASNeg, 8);

            // Variable rate Alt (or Dec) slew in positive direction
            // char slewCmdVarDECPos[] = {80, 3, 17,  6, trHig, trLow, 0, 0};
            slewCmdVarDECPos[4] = TrackRateAltHigh;
            slewCmdVarDECPos[5] = TrackRateAltLow;
            command = VarDECPos;
            EnviaLX(slewCmdVarDECPos, 8);
        }
        else if (Sender == BE)  // slew Right
        {
            // Stop (rate = 0) Fixed rate ALT (or DEC) slew in negative direction
            // char slewCmdFixDECNeg[] = {80, 2, 17, 37, 0, 0, 0, 0};
            command = FixDECNeg;
            EnviaLX(slewCmdFixDECNeg, 8);

            // Variable rate Azm (or RA) slew in positive direction
            // char slewCmdVarRASPos[] = {80, 3, 16,  6, trHig, trLow, 0, 0};
            slewCmdVarRASPos[4] = TrackRateAltHigh;
            slewCmdVarRASPos[5] = TrackRateAltLow;
            command = VarRASPos;
            EnviaLX(slewCmdVarRASPos, 8);
        }

        // O bien se guarda cada dirección para pararla, o bien se hace un evento BSMouseUp
        // ¿Qué pasa si se da Norte y sin parar se da Sur. Por ejemplo?


        // Stop (rate = 0) Fixed rate ALT (or DEC) slew in negative direction
        // char slewCmdFixDECNeg[] = {80, 2, 17, 37, 0, 0, 0, 0};
        //EnviaLX(slewCmdFixDECNeg, 8);

        // Stop (rate = 0) Fixed rate Azm (or RA) slew in negative direction
        // char slewCmdFixRASNeg[] = {80, 2, 16, 37, 0, 0, 0, 0};
        //EnviaLX(slewCmdFixRASNeg, 8);

        // Set tracking mode to 2 (EQ North)
        //EnviaLX(starTrk, 2);

        // Historico->Mhistory->Lines->Add("star");
        // Historico->Mhistory->Lines->Add(strlen(rate7));

    }
    else                             //LX200
    {
        if (sbSLW->Down == true)
            EnviaLX("#:RS#");
        else if (sbFND->Down == true)
            EnviaLX("#:RM#");
        else if (sbCEN->Down == true)
            EnviaLX("#:RC#");
        else if (sbGUI->Down == true)
            EnviaLX("#:RG#");

        if (Sender == BN)
            EnviaLX("#:Mn#");
        else if (Sender == BNO)
            EnviaLX(":Mn#:Me#");
        else if (Sender == BO)
            EnviaLX("#:Mw#");
        else if (Sender == BSO)
            EnviaLX("#:Mw#:Ms#");
        else if (Sender == BS)
            EnviaLX("#:Ms#");
        else if (Sender == BSE)
            EnviaLX("#:Ms#:Me#");
        else if (Sender == BE)
            EnviaLX("#:Me#");
        else if (Sender == BNE)
            EnviaLX("#:Mn#:Me#");
        else if (Sender == SBstop)
            EnviaLX("#:Q#");
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BNOMouseUp(TObject *Sender, TMouseButton Button,
                                   TShiftState Shift, int X, int Y)
//------------------------------------------------------------------------------
{
    //char stopTrk[] = {'T', 0};  // Set tracking mode to 0 (Off)
    char starTrk[] = {'T', 2};  // Set tracking mode to 2 (EQ North)

    // Any of these two stop motor in Azm or RAS we'll use the negative one
    // Fixed rate Azm (or RA) slew in positive direction
    //char slewCmdFixRASPos[] = {80, 2, 16, 36, 0, 0, 0, 0};
    // Fixed rate Azm (or RA) slew in negative direction
    char slewCmdFixRASNeg[] = {80, 2, 16, 37, 0, 0, 0, 0};

    // Any of these two stop motor in Alt or DEC we'll use the negative one
    // Fixed rate Alt (or DEC) slew in positive direction
    //char slewCmdFixDECPos[] = {80, 2, 17, 36, 0, 0, 0, 0};
    // Fixed rate Alt (or DEC) slew in negative direction
    char slewCmdFixDECNeg[] = {80, 2, 17, 37, 0, 0, 0, 0};

    //if (CBCGEM->Checked == false)   //es LX200
    if (CGEM) //es CGEM
    {
        // No hace falta parar el seguimiento, puesto que se ha parado
        // en el evento BSMouseDown
        //command = SetTrackMode;
        //EnviaLX(stopTrk, 2);
        command = FixRASNeg;
        EnviaLX(slewCmdFixRASNeg, 8);
        command = FixDECNeg;
        EnviaLX(slewCmdFixDECNeg, 8);
        command = SetTrackMode;
        EnviaLX(starTrk, 2);
        /*
        EnviaLX(rate7Stop);

        Historico->Mhistory->Lines->Add("stop");
        Historico->Mhistory->Lines->Add(strlen(rate7Stop));

        EnviaLX(rate7Stop);
        */
    }
    else // es LX200
    {
        if (Sender == BN)
            EnviaLX("#:Qn#");
        else if (Sender == BNO)
            EnviaLX("#:Qn##:Qw#");
        else if (Sender == BO)
            EnviaLX("#:Qw#");
        else if (Sender == BSO)
            EnviaLX("#:Qs##:Qw#");
        else if (Sender == BS)
            EnviaLX("#:Qs#");
        else if (Sender == BSE)
            EnviaLX("#:Qs##:Qe#");
        else if (Sender == BE)
            EnviaLX("#:Qe#");
        else if (Sender == BNE)
            EnviaLX("#:Qn##:Qe#");
    }
}

//==============================================================================
int readSpeedValues(TSpeedButton* sb)
//==============================================================================
{
    return sb->Tag;
}

//==============================================================================
void readINI()
//==============================================================================
{
    // Válidos para usar el mismo nombre que el programa y
    // un fichero en el mismo directorio que el ejecutable
    TIniFile *INI = new TIniFile(ChangeFileExt(Application->ExeName, ".ini"));
    //TIniFile *StartUp = new TIniFile(".\\Ini01.INI");

    ini.Location.Name = INI->ReadString("Location", "Name", "Casa");

    ini.Location.degLatA = INI->ReadInteger("Location", "degLatA", 0);
    ini.Location.minLatB = INI->ReadInteger("Location", "minLatB", 0);
    ini.Location.secLatC = INI->ReadInteger("Location", "secLatC", 0);
    ini.Location.nosLatD = INI->ReadInteger("Location", "nosLatD", 0);
    ini.Location.degLonE = INI->ReadInteger("Location", "degLonE", 0);
    ini.Location.minLonF = INI->ReadInteger("Location", "minLonF", 0);
    ini.Location.secLonG = INI->ReadInteger("Location", "secLonG", 0);
    ini.Location.eowLonH = INI->ReadInteger("Location", "eowLonH", 0);

    ini.Observation.Observer  = INI->ReadString("Observation", "Observer" , "");
    ini.Observation.Telescope = INI->ReadString("Observation", "Telescope", "");
    ini.Observation.Focal     = INI->ReadString("Observation", "Focal"    , "");
    ini.Observation.Aperture  = INI->ReadString("Observation", "Aperture" , "");
    ini.Observation.Camera    = INI->ReadString("Observation", "Camera"   , "");
    ini.Observation.Comment   = INI->ReadString("Observation", "Comment"  , "");
    ini.Observation.IP        = INI->ReadString("Observation", "IP"       , "");
    ini.Observation.Retraso   = INI->ReadString("Observation", "Retraso"  , "");
    ini.Observation.Limpiado  = INI->ReadString("Observation", "Limpiado" , "");

    ini.CamA.Name   = INI->ReadString ("CamA", "Name"  ,"");
    ini.CamA.Index  = INI->ReadInteger("CamA", "Index" , 0);
    ini.CamA.RowIni = INI->ReadInteger("CamA", "RowIni", 0);
    ini.CamA.RowFin = INI->ReadInteger("CamA", "RowFin", 0);
    ini.CamA.ColIni = INI->ReadInteger("CamA", "ColIni", 0);
    ini.CamA.ColFin = INI->ReadInteger("CamA", "ColFin", 0);

    ini.CamB.Name   = INI->ReadString ("CamB", "Name"  ,"");
    ini.CamB.Index  = INI->ReadInteger("CamB", "Index" , 0);
    ini.CamB.RowIni = INI->ReadInteger("CamB", "RowIni", 0);
    ini.CamB.RowFin = INI->ReadInteger("CamB", "RowFin", 0);
    ini.CamB.ColIni = INI->ReadInteger("CamB", "ColIni", 0);
    ini.CamB.ColFin = INI->ReadInteger("CamB", "ColFin", 0);

    ini.Image.FlipVert    = INI->ReadBool  ("Image", "FlipVert", false);
    ini.Image.FlipHori    = INI->ReadBool  ("Image", "FlipHori", false);
    ini.Image.FotoDir     = INI->ReadString("Image", "FotoDir"    , "");
    ini.Image.NameDir     = INI->ReadString("Image", "NameDir"    , "");
    ini.Image.ElbrusFile  = INI->ReadString("Image", "ElbrusFile" , "");

    delete INI;
}

//==============================================================================
void writeINI()
//==============================================================================
{
    char c;
    int ret;

    // Válidos para usar el mismo nombre que el programa y
    // un fichero en el mismo directorio que el ejecutable
    TIniFile *INI = new TIniFile(ChangeFileExt(Application->ExeName, ".ini"));
    //TIniFile *StartUp = new TIniFile(".\\Ini01.INI");

    INI->WriteString("Location", "Name", Form1->ELocation->Text);
    ret = sscanf(Form1->ELatitud->Text.c_str(),"%2dº%2d'%2d\" %c",
                                               &ini.Location.degLatA,
                                               &ini.Location.minLatB,
                                               &ini.Location.secLatC,
                                               &c);
    if (ret != 4)
    {
        WriteHistory("Error en Latitud: " + Form1->ELatitud->Text);
    }
    else
    {
        INI->WriteInteger("Location", "degLatA", ini.Location.degLatA);
        INI->WriteInteger("Location", "minLatB", ini.Location.minLatB);
        INI->WriteInteger("Location", "secLatC", ini.Location.secLatC);
        ini.Location.nosLatD = 0;
        if (c == 'S' || c == 's') ini.Location.nosLatD = 1;
        INI->WriteInteger("Location", "nosLatD", ini.Location.nosLatD);
    }

    ret = sscanf(Form1->ELongitud->Text.c_str(),"%2dº%2d'%2d\" %c",
                                                &ini.Location.degLonE,
                                                &ini.Location.minLonF,
                                                &ini.Location.secLonG,
                                                &c);
    if (ret != 4)
    {
        WriteHistory("Error en Longitud: " + Form1->ELongitud->Text);
    }
    else
    {
        INI->WriteInteger("Location", "degLonE", ini.Location.degLonE);
        INI->WriteInteger("Location", "minLonF", ini.Location.minLonF);
        INI->WriteInteger("Location", "secLonG", ini.Location.secLonG);
        ini.Location.eowLonH = 0;
        if (c == 'W' || c == 'w') ini.Location.eowLonH = 1;
        INI->WriteInteger("Location", "eowLonH", ini.Location.eowLonH);
    }

    INI->WriteString("Observation", "Observer",  Form1->EObserver->Text);
    INI->WriteString("Observation", "Telescope", Form1->ETelescop->Text);
    INI->WriteString("Observation", "Focal",     Form1->EFocal->Text);
    INI->WriteString("Observation", "Aperture",  Form1->EApert->Text);
    INI->WriteString("Observation", "Camera",    Form1->EInstrument->Text);
    INI->WriteString("Observation", "Comment",   Form1->EComent->Text);
    INI->WriteString("Observation", "IP",        Form1->Edit_IP->Text);
    INI->WriteString("Observation", "Retraso",   Form1->ERetraso->Text);
    INI->WriteString("Observation", "Limpiado",  Form1->ELimpiado->Text);

    INI->WriteString ("CamA", "Name",   Form1->CBCCD_A->Text);
    INI->WriteInteger("CamA", "Index",  Form1->CBCCD_A->ItemIndex);
    INI->WriteInteger("CamA", "RowIni", atoi(Form1->EFilaInicioA   ->Text.c_str()));
    INI->WriteInteger("CamA", "RowFin", atoi(Form1->EFilaFinA      ->Text.c_str()));
    INI->WriteInteger("CamA", "ColIni", atoi(Form1->EColumnaInicioA->Text.c_str()));
    INI->WriteInteger("CamA", "ColFin", atoi(Form1->EColumnaFinA   ->Text.c_str()));

    INI->WriteString ("CamB", "Name",   Form1->CBCCD_B->Text);
    INI->WriteInteger("CamB", "Index",  Form1->CBCCD_B->ItemIndex);
    INI->WriteInteger("CamB", "RowIni", atoi(Form1->EFilaInicioB   ->Text.c_str()));
    INI->WriteInteger("CamB", "RowFin", atoi(Form1->EFilaFinB      ->Text.c_str()));
    INI->WriteInteger("CamB", "ColIni", atoi(Form1->EColumnaInicioB->Text.c_str()));
    INI->WriteInteger("CamB", "ColFin", atoi(Form1->EColumnaFinB   ->Text.c_str()));

    INI->WriteBool("Image", "FlipVert", Form1->CBFlipVertical->Checked);
    INI->WriteBool("Image", "FlipHori", Form1->CBFlipHorizontal->Checked);

    delete INI;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::stSignClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    if (stSign->Caption == "+")
        stSign->Caption = "-" ;
    else
        stSign->Caption = "+";
}

//------------------------------------------------------------------------------
void __fastcall TForm1::bbGoClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    char DecSgn = '+';
    DecSgn = (char)stSign->Caption.c_str()[0];

    AnsiString orden;
    AnsiString coord;

    AnsiString sAreHor = EHra ->EditText;
    AnsiString sAreMin = EMra ->EditText;
    AnsiString sAreSec = ESra ->EditText;

    AnsiString sDecDeg = EDdec->EditText;
    AnsiString sDecMin = EMdec->EditText;
    AnsiString sDecSec = ESdec->EditText;

    /*
    if (Application->MessageBox("¿Confirma Movimiento del Telescopio ?", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
    {
    	return;
    }
    */

    if (CGEM)
    {
        if (HPREC)
        {
            orden = ArDecPrecToTeles(sAreHor, sAreMin, sAreSec, 0,
                                     sDecDeg, sDecMin, sDecSec, 0, DecSgn);
        }
        else
        {
            orden = ArDecToTeles(sAreHor, sAreMin, sAreSec, 0,
                                 sDecDeg, sDecMin, sDecSec, 0, DecSgn);
        }

        coord = sAreHor + AnsiString("h:")  +
                sAreMin + AnsiString("m:")  +
                sAreSec + AnsiString("s, ") +
                AnsiString(DecSgn)          +
                sDecDeg + AnsiString("°")   +
                sDecMin + AnsiString("'")   +
                sDecSec + AnsiString("\"")  ;

        WriteHistory("Orden: " + coord + " " + orden);

        // From sendClick()
        pedidaRaDe = false;
        EnviaLX(orden.c_str());
    }
    else
    {
        char aux[100];
        aux[0] = 2;   //mensaje al LX200
        aux[1] = 0;

        orden = AnsiString("#:Sr ")              +
                sAreHor + AnsiString(":")        +
                sAreMin + AnsiString("#")        +
                AnsiString("#:Sd ")              +
                AnsiString(DecSgn)               +
                sDecDeg + AnsiString((char)0xDF) +
                sDecMin + AnsiString("##:MS#")   ;

        strcpy(&aux[2], orden.c_str());
        S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);
    }
}

//==============================================================================
void WriteHistory (AnsiString cadena)
//==============================================================================
{
    if (Form1->CBver_envio_lx->Checked == true)
    {
        Historico->Mhistory->Lines->Add(cadena);
    }
}

//==============================================================================
void GetRaDe_F(double *Ra, double *De)
//==============================================================================
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

//==============================================================================
void Slew_F(char *comando)
//==============================================================================
{
    int HoraSlew;				   	// RA, hours
    double dRAMin;				   	// RA, minutes
    int nDecDeg;				   	// declination, degrees
    int nDecMin;				   	// declination, minutes
    char cSign;				   	// declination sign
    char aux[300], auxi[10];

    strncpy(&aux[2], comando, 15);
    strncpy(carecta, comando, 7);
    carecta[7] = 0;
    strncpy(cdeclinacion, &comando[7], 6);
    cdeclinacion[6] = 0;
    //  aux[0] = 2;
    //  aux[1] = 0;

    strncpy(auxi, carecta, 2);
    HoraSlew = atoi(auxi);
    strncpy(auxi, &carecta[3], 4);
    dRAMin = atof(auxi);
    strncpy(auxi, &cdeclinacion[1], 2);
    nDecDeg = atoi(auxi);
    strncpy(auxi, &cdeclinacion[4], 2);
    nDecMin = atoi(auxi);
    cSign = cdeclinacion[0];
    //  sprintf( &aux[2], ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d##:MS#",
    sprintf( aux, ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d##:MS#",
             HoraSlew, dRAMin, cSign, nDecDeg, nDecMin );
    sprintf( carecta, "%02dh%04.1lfm", HoraSlew, dRAMin);
    sprintf( cdeclinacion, "%c%02dº%02d'", cSign, nDecDeg, nDecMin );

    // if(S1 != NULL)
    // S1->Escribir(aux, strlen(&aux[2])+2, S1->IPRabbit);
    EnviaLX(aux);
}

//==============================================================================
// @param dRA: recibe AR en horas decimales
// @param dDec: DEC en grados decimales
// envia cadena tipo LX200 o CGEM
void Slew_F(double dRA, double dDec)
//==============================================================================
{
    //char *ptr;
    //char aux[300];
    AnsiString aux;

    double dValue;			 			// temporary storage
    char cSign;	                        // declination sign
    /*
    	int HoraSlew;			 			// RA, hours
    	double dRAMin;			 			// RA, minutes
    	int nDecDeg;			 			// declination, degrees
    	int nDecMin;			 			// declination, minutes
    	char szCommand[128];				// command string
    */
    // New variables
    long RAHor;                         // RA,  hours
    long RAMin;                         // RA,  minutes
    long RASec;                         // RA,  seconds
    long RACse;                         // RA,  cents of second
    long DECGra;                        // DEC, degrees
    long DECMin;                        // DEC, minutes
    long DECSec;                        // DEC, seconds
    long DECCse;                        // DEC, cents of second

    dValue = dRA / 360 * 24;
    RAHor = dValue;

    dValue = (dValue - RAHor) * 60;
    RAMin = dValue;

    dValue = (dValue - RAMin) * 60;
    RASec = dValue;

    dValue = (dValue - RASec) * 100 + 0.5;
    RACse = dValue;

    if (RACse > 99) RACse = 99;

    if (dDec < 0.0)
    {
        dValue = -dDec;
        cSign = '-';
    }
    else
    {
        dValue = dDec;
        cSign = '+';
    }

    DECGra = dValue;

    dValue = (dValue - DECGra) * 60;
    DECMin = dValue;

    dValue = (dValue - DECMin) * 60;
    DECSec = dValue;

    dValue = (dValue - DECSec) * 100 + 0.5;
    DECCse = dValue;

    if (DECCse > 99) DECCse = 99;

    sprintf(carecta, " %02dh %02dm %02d.%02ds", RAHor, RAMin, RASec, RACse);
    sprintf(cdeclinacion, "%c%02dº %02d' %02d.%02d\"", cSign, DECGra, DECMin, DECSec, DECCse);

    if (CGEM)
    {
        if (Sincronizando)
        {
            // Change from GOTO to SYNC
            if (HPREC)
            {
                aux = ArDecPrecToOrden(RAHor , RAMin , RASec , RACse,
                                       DECGra, DECMin, DECSec, DECCse, cSign);
                aux = StringReplace(aux, "r", "s", TReplaceFlags() << rfReplaceAll);
            }
            else
            {
                aux = ArDecToOrden(RAHor , RAMin , RASec , RACse,
                                   DECGra, DECMin, DECSec, DECCse, cSign);
                aux = StringReplace(aux, "R", "S", TReplaceFlags() << rfReplaceAll);
            }

            Sincronizando = false;
            Form1->CBSincronizar->State = cbUnchecked;

            // From sendClick()
            pedidaRaDe = false;
            WriteHistory("Sync: " + AnsiString(carecta) + " " +
                         cdeclinacion + " (" + aux + ")");
        }
        else
        {
            if (HPREC)
            {
                aux = ArDecPrecToOrden(RAHor , RAMin , RASec , RACse,
                                       DECGra, DECMin, DECSec, DECCse, cSign);
            }
            else
            {
                aux = ArDecToOrden(RAHor , RAMin , RASec , RACse,
                                   DECGra, DECMin, DECSec, DECCse, cSign);
            }
            WriteHistory("Slew: " + AnsiString(carecta) + " " +
                         cdeclinacion + " (" + aux + ")");
        }
    }
    else // LX200
    {

        if (Sincronizando == true)
        {
            //           sprintf( &aux[2], ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:CM#",
            sprintf( aux.c_str(), ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:CM#",
                     RAHor, RAMin, cSign, DECGra, DECMin );
            Sincronizando = false;
            Form1->CBSincronizar->State = cbUnchecked;
        }
        else
            //           sprintf( &aux[2], ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:MS#",
            sprintf( aux.c_str(), ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:MS#",
                     RAHor, RAMin, cSign, DECGra, DECMin );
    }

    // Set up the command string to set the telescope's slew target as
    // the specified RA/Dec coordinates.

    /*
    	dValue = dRA / 15.0 + 1 / 1200.0;
    	WriteHistory("dValue = " + AnsiString(dValue));

    	HoraSlew = int(dValue);
    	dRAMin = (dValue - HoraSlew) * 60.0;

    	dValue = dDec;
    	if (dValue < 0.0)
    	{
    		dValue = -dValue;
    		cSign = '-';
    	}
    	else
    		cSign = '+';

    	dValue += 1 / 120.0;
    	nDecDeg = int(dValue);
    	nDecMin = int((dValue - nDecDeg) * 60.0);

    	sprintf(carecta, "%02dh%04.1lfm", HoraSlew, dRAMin);
    	sprintf(cdeclinacion, "%c%02dº%02d'", cSign, nDecDeg, nDecMin );

    	if (CGEM)
    	{
    		if (Sincronizando)
    		{
    			//ArDecToOrden(long Ar_Hora  , long Ar_Minuto , long Ar_Segundo , long Ar_CentSegundo,
    			//             long Dec_Grado, long Dec_Minuto, long Dec_Segundo, long Dec_CentSegundo, char Dec_Sign)
    			//strcpy(aux, ArDecToOrden(HoraSlew, dRAMin, 0, 0,
    			//                         nDecDeg, nDecMin, 0, 0, cSign));

    			// Change from GOTO to SYNC
    			if (HPREC)
    			{
    				strcpy(aux, ArDecPrecToOrden(HoraSlew, dRAMin, 0, 0,
    											nDecDeg, nDecMin, 0, 0, cSign));
    				aux[0] = 's';
    			}
    			else
    			{
    				strcpy(aux, ArDecToOrden(HoraSlew, dRAMin, 0, 0,
    										nDecDeg, nDecMin, 0, 0, cSign));
    				aux[0] = 'S';
    			}

    			Historico->Mhistory->Lines->Add ("Orden Sync: " + AnsiString(carecta) + " " +
    											+ cdeclinacion + " "
    											+ AnsiString(aux));

    			// From sendClick()
    			pedidaRaDe = false;
    		}
    		else
    		{
    			//ArDecToOrden(long Ar_Hora  , long Ar_Minuto , long Ar_Segundo , long Ar_CentSegundo,
    			//             long Dec_Grado, long Dec_Minuto, long Dec_Segundo, long Dec_CentSegundo, char Dec_Sign)
    			if (HPREC)
    			{
    				strcpy(aux, ArDecPrecToOrden(HoraSlew, dRAMin, 0, 0,
    											nDecDeg, nDecMin, 0, 0, cSign));
    			}
    			else
    			{
    				strcpy(aux, ArDecToOrden(HoraSlew, dRAMin, 0, 0,
    										nDecDeg, nDecMin, 0, 0, cSign));
    			}
    			Historico->Mhistory->Lines->Add ("Orden Slew: " + AnsiString(carecta) + " " +
    											+ cdeclinacion + " "
    											+ AnsiString(aux));

    			// From sendClick()
    		}

    	}
    	else
    	{

    		if (Sincronizando == true)
    		{
    			//           sprintf( &aux[2], ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:CM#",
    			sprintf( aux, ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:CM#",
    					HoraSlew, dRAMin, cSign, nDecDeg, nDecMin );
    			Sincronizando = false;
    			Form1->CBSincronizar->State = cbUnchecked;
    		}
    		else
    			//           sprintf( &aux[2], ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:MS#",
    			sprintf( aux, ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:MS#",
    					HoraSlew, dRAMin, cSign, nDecDeg, nDecMin );
    	}
    */


    //      aux[0] = 2;
    //    aux[1] = 0;
    //  if(S1 != NULL)
    //S1->Escribir(aux, strlen(&aux[2])+2, S1->IPRabbit);
    EnviaLX(aux.c_str());
}

//------------------------------------------------------------------------------
// Sincronizar telescopio con ELBRUS
void __fastcall TForm1::BElbrusClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    FILE *in;
    char aqui[1000], cad[60];
    double dec, ar;
    int res;
    AnsiString aa;

    if ((in = fopen("c:\\inetpub\\elbrus.aqi", "rb")) != NULL)
    {
        fseek(in, 0, SEEK_END);
        long tam = ftell(in);
        fseek(in, 0, SEEK_SET);
        if (tam < (long)sizeof(aqui))
            fread(aqui, tam, 1, in);
        fclose(in);

        //      strncpy(&cad[0], &aqui[14], 7);    //  AR
        strncpy(&cad[0], &aqui[104], 7);    //  AR
        cad[8] = 0;
        ar = atof(cad);

        //      strncpy(&cad[0], &aqui[26], 7);    //  DEC
        strncpy(&cad[0], &aqui[116], 7);    //  DEC
        cad[8] = 0;
        dec = atof(cad);

        //      strncpy(&cad[0], &aqui[34], 24);
        strncpy(&cad[0], &aqui[123], 24);
        cad[24] = 0;
//        aa = "¿Sincronizar Telescopio en:  " + AnsiString(cad) + " ?";
        aa = "¿Sincronizar Telescopio en: \n\n\tAR =  " + formatARE(ar/15.0) +
                                           "\n\tDE = "  + formatDEC(dec) + "\n?";

        if (Application->MessageBox(aa.c_str(), "SINCRONIZACIÓN ELBRUS", MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
        {
            Historico->Mhistory->Lines->Add ("Sinc AR: " + formatARE(ar/15.0) + " DEC: " + formatDEC(dec));
            Sincronizando = true;
            Slew_F(ar, dec);       //manda las nuevas coordenadas
            //BSincronizarClick(NULL);  //envia el comando de cambio de coordenadas
        }
    }
    else
    {
        Application->MessageBox(aa.c_str(), " No se encuentra el fichero elbrus.aqi  ", MB_OKCANCEL	);
    }
}

//------------------------------------------------------------------------------
// Ver deriva con la foto anterior
void __fastcall TForm1::BDerivaAquiClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    FILE *in;
    char aqui[1000], cad[60], cad1[5], cad2[5];
    AnsiString aa;

    if ((in = fopen("c:\\inetpub\\elbrus.aqi", "rb")) != NULL)
    {
        fseek(in, 0, SEEK_END);
        long tam = ftell(in);
        fseek(in, 0, SEEK_SET);
        if (tam < (long)sizeof(aqui))
            fread(aqui, tam, 1, in);
        fclose(in);

        strncpy(&cad[0], &aqui[218], 2);    //  Numero de Estrellas
        cad[3] = 0;
        nEstrellas = atoi(cad);
        strncpy(&cad[0], &aqui[236], 7);    //  Deriva X en pixeles
        cad[8] = 0;
        dX = atof(cad);
        strncpy(&cad[0], &aqui[260], 7);    //  Deriva Y en pixeles
        cad[8] = 0;
        dY = atof(cad);
        sprintf(cad1, "%003.02f", dX);
        sprintf(cad2, "%003.02f", dY);
        aa = "N: " + AnsiString(nEstrellas) + " dX: " + AnsiString(cad1) + " dY: " + AnsiString(cad2);
        Form1->PLDeriva->Caption = aa;
        if (FileExists( "c:\\inetpub\\elbrus.aqi"))
        {
            DeleteFile("c:\\inetpub\\elbrus.aqi");
        }
    }
    else
    {
        Historico->Mhistory->Lines->Add ("c:\\inetpub\\elbrus.aqi no existe. ");
        dX = 0;
        dY = 0;
        CuentaGuiaAR = 0;
        TiempoGuiaAR = 0;
        return;
    }

    if (nEstrellas < 5)
    {
        Historico->Mhistory->Lines->Add ("Estrellas recentrar <5 ");
        dX = 0;
        dY = 0;
        CuentaGuiaAR = 0;
        TiempoGuiaAR = 0;
    }
}

//------------------------------------------------------------------------------
// pruebas de guiado
void __fastcall TForm1::BrecentrarARClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    char cad1[5], cad2[5];

    if (CBProporcional->Checked == false)    // ajuste proporcional al error.
    {
        if (dX > 0.5)   //mas de medio pixel
        {
            TiempoGuiaAR = dX * ( 100 / float(Form1->EGuiadoDecWest->Text.ToInt()) );
            if (TiempoGuiaAR > 1)
            {
                sprintf(cad1, "%003.02f", dX);
                sprintf(cad2, "%003.02f", fabs(TiempoGuiaAR));
                Historico->Mhistory->Lines->Add ("Mw  " + AnsiString(cad2) + " dec.seg,  " + AnsiString(cad1) + "  pix");
                EnviaLX("#:RG#:Mw#");
                IniciaAR = ::GetTickCount();
            }
            else TiempoGuiaAR = 0.0;
        }
        else if (dX < -0.5)
        {
            TiempoGuiaAR = dX * ( 100 / float(Form1->EGuiadoDecWest->Text.ToInt()) );
            if (TiempoGuiaAR < -1)
            {
                sprintf(cad1, "%003.02f", dX);
                sprintf(cad2, "%003.02f", fabs(TiempoGuiaAR));
                Historico->Mhistory->Lines->Add ("Me  " + AnsiString(cad2) + " dec.seg,  "  + AnsiString(cad1) + "  pix");
                EnviaLX("#:RG#:Me#");
                IniciaAR = ::GetTickCount();
            }
            else TiempoGuiaAR = 0.0;
        }
    }
    else                        // ajuste Fijo independiente del error
    {
        if (dX > 4.0)   //mas de 1 pixel
        {
            TiempoGuiaAR = 1.0 * EFijo->Text.ToInt();
            if (TiempoGuiaAR >= 1)
            {
                sprintf(cad1, "%003.02f", dX);
                sprintf(cad2, "%003.02f", fabs(TiempoGuiaAR));
                Historico->Mhistory->Lines->Add ("Mw  " + AnsiString(cad2) + " dec.seg,  " + AnsiString(cad1) + "  pix");
                EnviaLX("#:RG#:Mw#");
                IniciaAR = ::GetTickCount();
            }
            else TiempoGuiaAR = 0.0;
        }
        else if (dX < -4.0)
        {
            TiempoGuiaAR = -1.0 * EFijo->Text.ToInt();
            if (TiempoGuiaAR <= -1)
            {
                sprintf(cad1, "%003.02f", dX);
                sprintf(cad2, "%003.02f", fabs(TiempoGuiaAR));
                Historico->Mhistory->Lines->Add ("Me  " + AnsiString(cad2) + " dec.seg,  "  + AnsiString(cad1) + "  pix");
                EnviaLX("#:RG#:Me#");
                IniciaAR = ::GetTickCount();
            }
            else TiempoGuiaAR = 0.0;
        }

    }

    if (CBcalibrar->Checked == true)
    {
        TiempoGuiaDec =  float(Form1->EGuiadoCalDec->Text.ToInt() );
        EnviaLX("#:RG#:Me#");
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BrecentrarDECClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    char cad1[5], cad2[5];

    if ((dY > 0.5) && (CBnorte->Checked == true))
    {
        TiempoGuiaDec = dY * ( 100 / float(Form1->EGuiadoDecimasSgDec->Text.ToInt()) );
        if (TiempoGuiaDec > 1)
        {
            sprintf(cad1, "%003.02f", dY);
            sprintf(cad2, "%003.02f", fabs(TiempoGuiaDec));
            Historico->Mhistory->Lines->Add ("Mn  " + AnsiString(cad2) + " dec.seg,  " + AnsiString(cad1) + "  pix");
            EnviaLX("#:RG#:Mn#");
        }
        else TiempoGuiaDec = 0;
    }
    else if ((dY < -0.5) && (CBsur->Checked == true))
    {
        TiempoGuiaDec = dY * ( 100 / float(Form1->EGuiadoDecimasSgDec->Text.ToInt()) );
        if (TiempoGuiaDec < -1)
        {
            sprintf(cad1, "%003.02f", dY);
            sprintf(cad2, "%003.02f", fabs(TiempoGuiaDec));
            Historico->Mhistory->Lines->Add ("Ms  " + AnsiString(cad2) + " dec.seg,  "  + AnsiString(cad1) + "  pix");
            EnviaLX("#:RG#:Ms#");
        }
        else TiempoGuiaDec = 0;
    }

    if (CBcalibrar->Checked == true)
    {
        TiempoGuiaDec =  float(Form1->EGuiadoCalDec->Text.ToInt() );
        EnviaLX("#:RG#:Ms#");
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BGraficasClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    FGraficas->ShowModal();
}

//------------------------------------------------------------------------------
void __fastcall TForm1::ServerSocket1Accept(TObject *Sender,
        TCustomWinSocket *Socket)
//------------------------------------------------------------------------------
{
    Socket1 = Socket;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::ServerSocket1ClientDisconnect(TObject *Sender,
        TCustomWinSocket *Socket)
//------------------------------------------------------------------------------
{
    Socket1 = NULL;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::ServerSocket1ClientError(TObject *Sender,
        TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
//------------------------------------------------------------------------------
{
    Socket1 = NULL;
}

//------------------------------------------------------------------------------
// Lo que viene por el PUERTO SERIE VIRTUAL es enviado al telescopio
void __fastcall TForm1::ServerSocket1ClientRead(TObject *Sender,
        TCustomWinSocket *Socket)
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
void __fastcall TForm1::BcambiaIPClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    S1->IniciarRabbit();
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BGuardaConfigClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    writeINI();
    readINI();
    WriteHistory("Fichero " + ChangeFileExt(Application->ExeName, ".ini") + " grabado.");
//    FILE *out;
//
//    char config[100][50];
//    char auxi[+50];
//    char temp[300];
//
//    memset(config, ' ', sizeof(config));
//    strcpy(config[0],  ELocation->Text.c_str());
//    strcpy(config[1],  EObserver->Text.c_str());
//    strcpy(config[2],  ETelescop->Text.c_str());
//    strcpy(config[3],  EFocal->Text.c_str());
//    strcpy(config[4],  EApert->Text.c_str());
//    strcpy(config[5],  EInstrument->Text.c_str());
//    strcpy(config[6],  EComent->Text.c_str());
//    strcpy(config[7],  Edit_IP->Text.c_str());
//    strcpy(config[8],  ERetraso->Text.c_str());
//    strcpy(config[9],  ELimpiado->Text.c_str());
//    strcpy(config[10], CBCCD_A->Text.c_str());
//    strcpy(config[11], AnsiString(CBCCD_A->ItemIndex).c_str());
//    strcpy(config[12], EFilaInicioA->Text.c_str());
//    strcpy(config[13], EFilaFinA->Text.c_str());
//    strcpy(config[14], EColumnaInicioA->Text.c_str());
//    strcpy(config[15],  EColumnaFinA->Text.c_str());
//
//    strcpy(config[21], CBCCD_B->Text.c_str());
//    strcpy(config[22], AnsiString(CBCCD_B->ItemIndex).c_str());
//    strcpy(config[23], EFilaInicioB->Text.c_str());
//    strcpy(config[24], EFilaFinB->Text.c_str());
//    strcpy(config[25], EColumnaInicioB->Text.c_str());
//    strcpy(config[26],  EColumnaFinB->Text.c_str());
//
//    strcpy(config[16],  ELatitud->Text.c_str());
//    strcpy(config[17],  ELongitud->Text.c_str());
//
//    if (CBFlipVertical->State == cbChecked)
//        strcpy(config[18], "F");
//    else strcpy(config[18], "N");
//    if (CBFlipHorizontal->State == cbChecked)
//        strcpy(config[19], "F");
//    else strcpy(config[19], "N");
//    strcpy(config[20],  Edit_IP->Text.c_str());
//
//    strcpy(temp,  dir_trab);
//    strcat(temp, "cor.cfg");
//    out = fopen(temp, "wt");
//    fwrite(config, sizeof(config), 1, out); /* write struct s to file */
//
//    //      out = fopen("config.txt", "wt");
//    //      fwrite(config, sizeof(config), 1, out); /* write struct s to file */
//
//    fclose(out); /* close file */
}

//------------------------------------------------------------------------------
void __fastcall TForm1::EColumnaFinAChange(TObject *Sender)
//------------------------------------------------------------------------------
{
    /*
    if(ECU->Text.ToInt() > CCDs[CBCCD_A->ItemIndex].ColumnasFisicas)
    	ECU->Text = CCDs[CBCCD_A->ItemIndex].ColumnasFisicas;
    CCDs[CBCCD_A->ItemIndex].ColumnasUtiles = ECU->Text.ToInt();
    NumeroColumnas = ECU->Text.ToInt() / Binin;
    NumeroFilas = EFU->Text.ToInt() / Binin;
    offsetx = (CCDs[CBCCD_A->ItemIndex].ColumnasFisicas - CCDs[CBCCD_A->ItemIndex].ColumnasUtiles)/2;
    offsety = (CCDs[CBCCD_A->ItemIndex].FilasFisicas - CCDs[CBCCD_A->ItemIndex].FilasUtiles)/2;
    if(CBR->State == cbUnchecked)
    {
    	PX1->Caption = 0;
    	PX2->Caption = ECU->Text;
    	PY1->Caption = 0;
    	PY2->Caption = EFU->Text;
    }
    */
}

//------------------------------------------------------------------------------
void __fastcall TForm1::UpDown1ChangingEx(TObject *Sender,
        bool &AllowChange, short NewValue, TUpDownDirection Direction)
//------------------------------------------------------------------------------
{
    if (Direction  == updUp)
    {
        if (NewValue >= 30)
            UpDown1->Increment = 30;
        else if (NewValue >= 5)
            UpDown1->Increment = 5;
    }
    else
    {
        if (NewValue < 31)
            UpDown1->Increment = 5;
        if (NewValue < 6)
            UpDown1->Increment = 1;
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::CBimagenChange(TObject *Sender)
//------------------------------------------------------------------------------
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

    if (CBimagen->ItemIndex == 3)
    {
        indice_cfs++;
        strcpy(Buf_Cfs[indice_cfs],  "<mx>");    // primero xo es LIFO
    }
    /*   else
    {
    	indice_cfs++;
    	strcpy(Buf_Cfs[indice_cfs],  "<mf>");    // primero xo es LIFO
    }
    */
}

//------------------------------------------------------------------------------
void __fastcall TForm1::DirectoryListBox1Change(TObject *Sender)
//------------------------------------------------------------------------------
{
    mPath =  DirectoryListBox1->Directory;
}

//------------------------------------------------------------------------------

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
Historico->Mhistory->Lines->Add("media = " + AnsiString(m));
Historico->Mhistory->Lines->Add("fondo = " + AnsiString(fondocielo));

return (m);
}
*/


//==============================================================================
// FUNCION ADAPTADORA
//
// Esta funciona adaptadora hace que tanto la region de fondo de cielo
// como la region de calculo de centroide de la estrella sea toda la imagen
// Si el puntero a la imagen cambia con cada toma, pues hay que llamarla
// una vez por cada toma.
// Si se reutiliza el mismo buffer una y otra vez, se llama una vez al principio
//
// Asume que la imagen es un buffer todo seguido de pixeles
//
void ACOR_SetImage(pixel_t* img, int width, int height)
//==============================================================================
{
    AF_SetImage(img, width, height);
    AF_SetSkyRegion(0, 0, width - 1, height - 1);
    AF_SetCentroidRegion(0, 0, width - 1, height - 1);
}

//==============================================================================
// Terminada una foto de enfoque, se procede a su analisis
void Enfoque()
//==============================================================================
{
    int width, height;
    long npixel;// - 1;
    short *datos;
    char aux[300];
    char Name[80];
    npixel = (X2F - X1F) * (Y2F - Y1F);
    static float hfd_pos[10000];
    static float auxi;
    double med = 0;
    int cont_med = 0;
    datos = new short [npixel + 1];
    memset(datos, 0, npixel * 2);
    /*
    for(int py = Y2F-1; py >= Y1F; py--)
    {
    	for (int px = (X2F-1); px >= X1F; px--)
    		datos[npixel--] = FotoPrincipal->Pixeles[py * FotoPrincipal->BM->Width + px];
    }
    height = Y2F-1 - Y1F;
    width = X2F-1-X1F;
    */
    for (int py = Y2F - 1; py >= Y1F; py--)
    {
        for (int px = (X2F - 1); px >= X1F; px--)
        {
            datos[npixel--] = FotoPrincipal->Pixeles[py * FotoPrincipal->BM->Width + px];
            med += FotoPrincipal->Pixeles[py * FotoPrincipal->BM->Width + px];
            cont_med++;
        }
    }
    med = med / cont_med;

    if (Form1->CBhfd->State == cbChecked)
    {
        height = Y2F - Y1F;
        width = X2F - X1F;
        AF_SetImage(datos, width, height);
        AF_SetSkyRegion(1, 1, width - 2, height - 2);
        AF_SetCentroidRegion(1, 1, width - 2, height - 2);
        hfd = AF_HFD(Name);    // No se puede pedir el centroide sin haber llamado a AF_HFD primero
    }
    else
    {
        double Bi = 0, Bi1 = 0, Bi2 = 0;
        for (int py = Y2F - 1; py >= Y1F; py--)
        {
            for (int px = (X2F - 1); px >= X1F; px--)
            {
                Bi = FotoPrincipal->Pixeles[py * FotoPrincipal->BM->Width + px] - med;
                if (Bi < 0) Bi = 0;
                Bi1 += Bi;
                Bi2 += Bi * Bi;
            }
        }
        spizer = (Bi1 * Bi1) / Bi2;
        char au[10], ae[10];
        sprintf(au, "%07.1f", spizer);
        sprintf(ae, "%07.1f", med);
        Historico->Mhistory->Lines->Add("spizer = " + AnsiString(au) + ", media = " + AnsiString(ae));
        hfd = (float)spizer / 100;
    }

    sprintf( aux, "%003d", (FotoActual - 1));
    sprintf(Name, (Form1->ENombreFichero->Text + AnsiString("_") + AnsiString(aux) + AnsiString(".fit")).c_str());

    AF_AddMeasurement(contador_pasos, hfd);

    double xc, yc, hf;
    int xi, yi, hfdi;

    hf = hfd;
    AF_GetCentroid(&xc, &yc);

    hfdi = hf * 10;
    hf = hfdi / 10.0;
    xi = xc * 10;
    xc = xi / 10.0;
    yi = yc * 10;
    yc = yi / 10.0;

    if (hf == -1)  fallos_hfd++;

    hfd_pos[contador_pasos] = hf;
    auxi = abs(contador_pasos / 10) + 1;

    Form4->Series1->AddXY(contador_pasos, hf, contador_pasos , clRed);
    Historico->Mhistory->Lines->Add("-> Pos: " + AnsiString(contador_pasos) + "  X: " + AnsiString(xc) + "  Y: " + AnsiString(yc) + "  hfd "  + AnsiString(hf));//+ " act " + AnsiString(FotoActual));
    //  Historico->Mhistory->Lines->Add(" X: " + AnsiString(xc) + " Y: " + AnsiString(yc) + "  hfd " + AnsiString(hf));
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BIniCalClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    AF_InitCalibration();
    AF_SetImage((short*)FotoPrincipal->Pixeles, FotoPrincipal->BM->Width, FotoPrincipal->BM->Height);
    Memo1->Lines->Add("Width =" + AnsiString(FotoPrincipal->BM->Width) + "  Height =" + AnsiString(FotoPrincipal->BM->Height));

}

//------------------------------------------------------------------------------
void __fastcall TForm1::BFotoEnfocarClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    nfotos = FotoActual;   //lanza una toma
    // AF_SetImage(imagen, width, height);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::IFotoMouseDown(TObject *Sender,
                                       TMouseButton Button, TShiftState Shift, int X, int Y)
//------------------------------------------------------------------------------
{
    char *ptr;
    char aux[300];

    // Simulación foto
    if (ColorEstado == clRed)
    {
        Application->MessageBox("COR Desconectado.", "ATENCION", MB_OKCANCEL );
        return;
    }

    if (S1 != NULL)
    {
        if (PFoto->BevelOuter == bvRaised)
        {
            if ((CBGuardar->Checked == true))
            {

                //        SetCurrentDirectory( mPath.c_str());
                //        GetCurrentDirectory( 100, dir_trab);
                //        strcat(dir_trab, "\\");
                //  Historico->Mhistory->Lines->Add(dir_trab);

                if (CBWeb->State == cbChecked)
                {
                    if (FileExists(dir_trab + ENombreFichero->Text + AnsiString("_001.fit")))
                    {
                        if (Application->MessageBox("El Fichero ya existe. ¿Sobrescribir?", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
                        {
                            return;
                        }
                    }
                }
            }
            nfotos = UDNFotos->Position;
            FotoActual = 1;
            numeroLineaanterior = 0;
            if (CBT->State == cbChecked)
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

            if (ObtuIndex == 1) // se trata de un bias.
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

            // IniciaAR = ::GetTickCount();
        }
    }
}

//==============================================================================
void QuitaRectangulo(void)
//==============================================================================
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
    Y1F = CCDs[Form1->CBCCD_A->ItemIndex ].FilaInicio / Binin;
    X1F = CCDs[Form1->CBCCD_A->ItemIndex].ColumnaInicio / Binin;
    Y2F = CCDs[Form1->CBCCD_A->ItemIndex].FilaFin / Binin;
    X2F = CCDs[Form1->CBCCD_A->ItemIndex].ColumnaFin / Binin;

    X1T = X1F;
    Y1T = Y1F;
    X2T = X2F;
    Y2T = Y2F;

    points[0] = Point(X1F, Y1F);
    points[1] = Point(X2F, Y1F);
    points[2] = Point(X2F, Y2F);
    points[3] = Point(X1F, Y2F);
    points[4] = Point(X1F, Y1F);
    Form1->PB1->Canvas->Pen->Color = clWhite;
    Form1->PB1->Canvas->Pen->Mode = pmXor;
    Form1->PB1->Canvas->Polyline(points, 4);
    PintarRectAnt = true;
    Form1->PX1->Caption = X1T;
    Form1->PX2->Caption = X2T;
    Form1->PY1->Caption = Y1T;
    Form1->PY2->Caption = Y2T;
    //  PRecuadro->Caption = AnsiString(X2T-X1T) + " x " + AnsiString(Y2T-Y1T);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::PB1MouseDown(TObject *Sender, TMouseButton Button,
                                     TShiftState Shift, int X, int Y)
//------------------------------------------------------------------------------
{
    TPoint p, p2;

    if (PageControl1->ActivePage == VISUALIZACION)
    {
        Lupa(X, Y, FotoPrincipal, false);
    }
    else
    {
        if (Shift.Contains(ssRight) && CBRectangulo->State == cbChecked)
        {
            QuitaRectangulo();  //fin boton derecho
        }
        else if ((Shift.Contains(ssLeft)) && CBRectangulo->State == cbChecked)
        {

            if (first == true)
            {
                first = false;
                if (PintarRectAnt == true)
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
                X1T = (X / 5) * 5;
                Y1T = (Y / 5) * 5;
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
            PRecuadro->Caption = AnsiString(X2T - X1T) + " x " + AnsiString(Y2T - Y1T);
        }//fin boton izquierdo
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::PB1MouseMove(TObject *Sender, TShiftState Shift,
                                     int X, int Y)
//------------------------------------------------------------------------------
{
    if ((X >= FotoPrincipal->BM->Width) || (Y >= FotoPrincipal->BM->Height) || (X < 0) || (Y < 0))
    {
        return;
    }

    if (PageControl1->ActivePage == VISUALIZACION)
    {
        Lupa(X, Y, FotoPrincipal, false);
    }
    else if (Shift.Contains(ssLeft) && CBRectangulo->State == cbChecked)
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
        PRecuadro->Caption = AnsiString(X2T - X1T) + " x " + AnsiString(Y2T - Y1T);
        //    PRecuadro->Caption = AnsiString(X2T-X1T) + " x " + AnsiString(Y2T-Y1T);
    }
    else
    {
        PX->Caption = X;
        PY->Caption = Y;
        //  PP->Caption = FotoPrincipal->Pixeles[Y * NumeroColumnas + X];   //valor del pixel
        PP->Caption = FotoPrincipal->Pixeles[Y * NumeroColumnas + X];   //valor del pixel
        //PRecuadro->Caption = AnsiString(X2T-X1T) + " x " + AnsiString(Y2T-Y1T);
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::PB1MouseUp(TObject *Sender, TMouseButton Button,
                                   TShiftState Shift, int X, int Y)
//------------------------------------------------------------------------------
{
    if ( CBRectangulo->State == cbChecked)
    {

        //  Memo1->Lines->Add("MouseUp" );
        first = true;
        if (X1T > X2T)
        {
            X1F = X2T;
            X2F = X1T;
        }
        else
        {
            X1F = X1T;
            X2F = X2T;
        }
        if (Y1T > Y2T)
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

//------------------------------------------------------------------------------
void __fastcall TForm1::BPeltierAClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    char aux[20], aux2[20];

    if (Form1->EVpelt_manA->Text > 254)
        Form1->EVpelt_manA->Text = "254";

    strcpy( &aux2[0], Form1->EVpelt_manA->Text.c_str());

    strcpy(&aux[0], "<a00");
    strcat(aux, aux2);
    strcat(aux, "-00>");
    aux[11] = 0;
    indice_cfs++;
    strcpy(Buf_Cfs[indice_cfs],  aux);
    VccdA = Form1->EVpelt_manA->Text.ToInt();
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BPeltierBClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    char aux[20], aux2[20];

    if (Form1->EVpelt_manB->Text > 254)
        Form1->EVpelt_manB->Text = "254";

    strcpy( &aux2[0], Form1->EVpelt_manB->Text.c_str());

    strcpy(&aux[0], "<b00");
    strcat(aux, aux2);
    strcat(aux, "-00>");
    aux[11] = 0;
    indice_cfs++;
    strcpy(Buf_Cfs[indice_cfs],  aux);
}

//==============================================================================
void RegularTccdA(void)
//==============================================================================
{
    char aux[60], aux2[60];
    AnsiString A;
    //  static int TccdA;
    static int TccdA_Adj;
    static DWORD TiempoRegularA = 0;
    //  static float Tccd;

    if (::GetTickCount() > (TiempoRegularA + atoi(Form1->ESegAdj->Text.c_str()) * 1000))
    {
        TiempoRegularA = ::GetTickCount();

        TccdA_Adj = atoi(Form1->EAdj_ccdA->Text.c_str());
        if ( TccdA_grados > TccdA_Adj )
            VccdA += 1;
        else VccdA -= 1; //Form1->MEpwmA->EditText = VccdA -5;

        if ( VccdA > 255) VccdA = 255;
        else if ( VccdA < 0) VccdA = 0;

        sprintf( aux2, "%003d", VccdA);
        Form1->EVpelt_manA->Text = aux2;

        strcpy(&aux[0], "<a00");
        strcat(aux, aux2);
        strcat(aux, "-00>");
        aux[11] = 0;
        indice_cfs++;
        strcpy(Buf_Cfs[indice_cfs],  aux);
    }
}

//==============================================================================
void RegularTccdB(void)
//==============================================================================
{
    char aux[60], aux2[60];
    static int TccdB_Adj;
    static DWORD TiempoRegularB = 0;

    if (::GetTickCount() > (TiempoRegularB + atoi(Form1->ESegAdj->Text.c_str()) * 1000))
    {
        TiempoRegularB = ::GetTickCount();

        TccdB_Adj = atoi(Form1->EAdj_ccdB->Text.c_str());

        if ( TccdB_grados > TccdB_Adj )
            VccdB += 1;
        else VccdB -= 1; //Form1->MEpwmA->EditText = VccdA -5;

        if ( VccdB > 255) VccdB = 255;
        else if ( VccdB < 0) VccdB = 0;

        sprintf( aux2, "%003d", VccdB);
        Form1->EVpelt_manB->Text = aux2;

        strcpy(&aux[0], "<b00");
        strcat(aux, aux2);
        strcat(aux, "-00>");
        aux[11] = 0;
        indice_cfs++;
        strcpy(Buf_Cfs[indice_cfs],  aux);
    }
}

//==============================================================================
AnsiString CmdToStr(Commands cmd)
//==============================================================================
{
    AnsiString str;

    switch (cmd)
    {
        case GetRAS_DEC:
            str = "GetRAS_DEC";
            break;
        case GetPreRAS_DEC:
            str = "GetPreRAS_DEC";
            break;
        case GetAZM_ALT:
            str = "GetAZM_ALT";
            break;
        case GetPreAZM_ALT:
            str = "GetPreAZM_ALT";
            break;
        case GotoRAS_DEC:
            str = "GotoRAS_DEC";
            break;
        case GotoPreRAS_DEC:
            str = "GotoPreRAS_DEC";
            break;
        case GotoAZM_ALT:
            str = "GotoAZM_ALT";
            break;
        case GotoPreAZM_ALT:
            str = "GotoPreAZM_ALT";
            break;
        case SyncRAS_DEC:
            str = "SyncRAS_DEC";
            break;
        case SyncPreRAS_DEC:
            str = "SyncPreRAS_DEC";
            break;
        case GetTrackMode:
            str = "GetTrackMode";
            break;
        case SetTrackMode:
            str = "SetTrackMode";
            break;
        case VarRASPos:
            str = "VarRASPos";
            break;
        case VarRASNeg:
            str = "VarRASNeg";
            break;
        case VarDECPos:
            str = "VarDECPos";
            break;
        case VarDECNeg:
            str = "VarDECNeg";
            break;
        case FixRASPos:
            str = "FixRASPos";
            break;
        case FixRASNeg:
            str = "FixRASNeg";
            break;
        case FixDECPos:
            str = "FixDECPos";
            break;
        case FixDECNeg:
            str = "FixDECNeg";
            break;
        case GetLoc:
            str = "GetLoc";
            break;
        case SetLoc:
            str = "SetLoc";
            break;
        case GetTime:
            str = "GetTime";
            break;
        case SetTime:
            str = "SetTime";
            break;
        case GetVer:
            str = "GetVer";
            break;
        case GetDevVer:
            str = "GetDevVer";
            break;
        case GetModel:
            str = "GetModel";
            break;
        case Echo:
            str = "Echo";
            break;
        case AlignComplete:
            str = "AlignComplete";
            break;
        case GotoProg:
            str = "GotoProg";
            break;
        case GotoCancel:
            str = "GotoCancel";
            break;
        case None:
            str = "None";
            break;
        default:
            str = "Unknown";
            break;
    }

    return str;

}

//------------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
//------------------------------------------------------------------------------
{
    indice_cfs++;
    strcpy(Buf_Cfs[indice_cfs],  Form1->EEnviar_cfs->Text.c_str());

    //   errorcfs = 0;  //desbloquea recepcion cfs.
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BCalibrarMeteoClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    fp = new TFConfigMeteo(NULL);  //para que la ventana se cree cada vez que se abra

    fp->ShowModal();
    delete fp;
    fp = NULL;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BHistoriaClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    Historico->Visible = !Historico->Visible;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
//------------------------------------------------------------------------------
{
    Filtro->mover_rueda(3);   //prueba de mover_rueda
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BVergrafClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    //Form4->Series1->Clear();
    Form4->Visible = true;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BGetBFPClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    //  int retornoBFP;
    char aux2[12];
    char aux3[12];
    char aux4[12];
    char aux5[12];
    int contador_pasos_v, hfdv;

    //  FitResult result;

    AF_SetMaxRSE(25); /* opcional, 0.5 es el valor por defecto */
    //  AF_SetMaxOutliers(3); /* opcional, 3 es el valor por defecto */
    //  AF_SetNearFocusHFD(600); /* opcional, es autom´atico por defecto */

    Form1->CBAutoEnfoque->State = cbUnchecked;

    if (fallos_hfd < FotosEnfoque / 4)
        retornoBFP = AF_FitParams();
    else retornoBFP = -1;

    if (retornoBFP != -1)
    {
        AF_Save("ejemplo");
        AF_GetFitResult(&result);

        Historico->Mhistory->Lines->Add(" -- RESULTADO: --");
        Historico->Mhistory->Lines->Add("BFP: " + AnsiString(result.bfp));
        Historico->Mhistory->Lines->Add("pid: " + AnsiString(result.pid));
        Historico->Mhistory->Lines->Add("nfHFD: " + AnsiString(result.nfHFD));

        sprintf(aux2, "%05.2f", result.pid);
        sprintf(aux3, "%05.2f", result.nfHFD);
        sprintf(aux4, "%06.3f", result.left.slope);
        sprintf(aux5, "%06.3f", result.right.slope);
        Form4->PDatosV->Caption =  "BFP: " + AnsiString(result.bfp) + "   pid: " + aux2
                                   + "   slope L: " + aux4 + "   slope R: " + aux5 + "   nfHFD: " + aux3 ;


        hfdv = - (margen_enfoque) * result.left.slope;
        contador_pasos_v =  result.left.x0 - margen_enfoque;
        Form4->Series2->AddXY(contador_pasos_v, hfdv, contador_pasos_v , clGreen);
        contador_pasos_v =  (int)result.left.x0;
        hfdv = 0;
        Form4->Series2->AddXY(contador_pasos_v, hfdv, contador_pasos_v , clGreen);

        contador_pasos_v =  (int)result.right.x0;
        hfdv = 0;
        Form4->Series3->AddXY(contador_pasos_v, hfdv, contador_pasos_v , clGreen);
        contador_pasos_v =  result.right.x0 + margen_enfoque;
        hfdv = margen_enfoque * result.right.slope;
        Form4->Series3->AddXY(contador_pasos_v, hfdv, contador_pasos_v , clGreen);

        Historico->Mhistory->Lines->Add(" -- LEFT --");
        Historico->Mhistory->Lines->Add("slope: " + AnsiString(result.left.slope));
        Historico->Mhistory->Lines->Add("slope_dev: " + AnsiString(result.left.slope_dev));
        Historico->Mhistory->Lines->Add("x0: " + AnsiString(result.left.x0));
        Historico->Mhistory->Lines->Add("x0_dev: " + AnsiString(result.left.x0_dev));
        Historico->Mhistory->Lines->Add("rse: " + AnsiString(result.left.rse));
        Historico->Mhistory->Lines->Add("npoints: " + AnsiString(result.left.npoints));
        Historico->Mhistory->Lines->Add("nrejects: " + AnsiString(result.left.nreject));

        Historico->Mhistory->Lines->Add(" -- RIGHT -- ");
        Historico->Mhistory->Lines->Add("slope: " + AnsiString(result.right.slope));
        Historico->Mhistory->Lines->Add("slope_dev: " + AnsiString(result.right.slope_dev));
        Historico->Mhistory->Lines->Add("x0: " + AnsiString(result.right.x0));
        Historico->Mhistory->Lines->Add("x0_dev: " + AnsiString(result.right.x0_dev));
        Historico->Mhistory->Lines->Add("rse: " + AnsiString(result.right.rse));
        Historico->Mhistory->Lines->Add("npoints: " + AnsiString(result.right.npoints));
        Historico->Mhistory->Lines->Add("nrejects: " + AnsiString(result.right.nreject));
    }
    else
    {
        Historico->Mhistory->Lines->Add("Datos invalidos. ");
        Form4->PDatosV->Caption =  " DATOS INVALIDOS ";
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BInitCalibrationClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    if (Application->MessageBox("¿Confirma autoenfoque SEMIAUTOMATICO?", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
    {
        return;
    }
    Form1->CBAutoEnfoque->State = cbChecked;

    Form4->Series1->Clear();
    Form4->Series2->Clear();
    Form4->Series3->Clear();
    Form4->Visible = true;
    cuentita = 0;

    AF_SetLogLevel(0);
    //  AF_EnableDataSets(1);    //para que genere ficheros R, 0 nada
    AF_InitCalibration();

    Form1->BGetBFP->Enabled = true;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BAutoEnfoqueClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    indice_cfs++;
    strcpy(Buf_Cfs[indice_cfs],  "<xp>");    // por si las moscas

    if (Application->MessageBox("¿Confirma enfoque AUTOMATICO? Necesario recuadro en estrella", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
    {
        return;
    }
    retornoBFP = -1;
    AutoEnfoque = 1;
    CBRectangulo->State = cbChecked;
    Form1->CBGuardar->Checked = false;// cbUnchecked;
    Form1->CBWeb->Checked = false;
    Form1->CBAutoEnfoque->State = cbChecked;

    Form4->Series1->Clear();
    Form4->Series2->Clear();
    Form4->Series3->Clear();
    Form4->Visible = true;
    cuentita = 0;
    fallos_hfd = 0;

    AF_SetLogLevel(0);
    AF_InitCalibration();
    Form1->BGetBFP->Enabled = true; // cambiar
    Form1->CBautostrech->Checked = false;

    if (Form1->ENFotos->Text.ToInt() < 10)
        Form1->ENFotos->Text = FotosEnfoque;// - 1;
    if (Form1->EPasosEnfoque->Text.ToInt() > 100 )
        Form1->EPasosEnfoque->Text = "50";

    if (((X2F - X1F) > 300 || (Y2F - Y1F) > 300 ) && CBhfd->State == cbChecked) // para evitar fotos muy grandes
    {
        X1F = X2F - 80;
        Y1F = Y2F - 80;
    }
}

//------------------------------------------------------------------------------
// Timer de 1sg para gestion del autoenfoque
void __fastcall TForm1::Timer1000Timer(TObject *Sender)
//------------------------------------------------------------------------------
{
    char aux2[12];
    char aux3[12];
    char aux4[12];
    char aux5[12];

    if ((AutoEnfoque == 1) && (FinX == 1)) // Moviendo a desenfoque Extremo
    {
        AutoEnfoque = 2;
        pos_inicio = contador_pasos;
        pasos_x = foco_extremo;
        Form4->PDatosV->Caption =  " Desenfocando al Extremo ";
        sentido = '+';
        MueveEnfoque();
    }

    else if ((AutoEnfoque == 2) && (FinX == 1)) // Moviendo a desenfoque proximo
    {
        AutoEnfoque = 3;
        Form4->PDatosV->Caption =  " Moviendo a Foco Proximo ";
        //      pasos_x = foco_extremo - foco_proximo;
        pasos_x = foco_extremo - (Form1->EPasosEnfoque->Text.ToInt() * Form1->ENFotos->Text.ToInt()) / 2;
        sentido = '-';
        MueveEnfoque();
    }

    else if ((AutoEnfoque == 3) && (FinX == 1))
    {
        AutoEnfoque = 4;
        Form4->PDatosV->Caption =  " Realizando Tomas ";
        pasos_x = Form1->EPasosEnfoque->Text.ToInt();
        Form1->IFotoMouseDown(NULL, (TMouseButton)NULL, TShiftState(), 0, 0);
    }
    else if ( (AutoEnfoque == 4) && (FinX == 1) && (FinFoto) && (FotoActual  > Form1->ENFotos->Text.ToInt()) )
    {
        AutoEnfoque = 5;
        Form1->ENFotos->Text = 1;
        Form4->PDatosV->Caption =  " Ajustando Cuva ";
        Form1->BGetBFPClick(NULL);
    }

    else if ((AutoEnfoque == 5) && (FinX == 1))
    {
        AutoEnfoque = 6;
        pasos_x = foco_extremo;
        Form4->PDatosV->Caption =  " Desenfocando al Extremo ";
        sentido = '+';
        MueveEnfoque();
    }

    else if (AutoEnfoque == 6 && FinX == 1)
    {
        if ( retornoBFP != -1)
        {
            AutoEnfoque = 7;
            Form4->PDatosV->Caption =  " Moviendo a Enfoque Final";
            pasos_x = abs(contador_pasos) + result.bfp;
            sentido = '-';
        }
        else
        {
            AutoEnfoque = 8;
            //         AutoEnfoque = 0;
            Form4->PDatosV->Caption =  " Curva Invalida. Retornando al Punto Inicial";
            pasos_x = abs(contador_pasos - pos_inicio);
            sentido = '-';
        }
        MueveEnfoque();
    }

    else if (AutoEnfoque == 7 && FinX == 1)
    {
        AutoEnfoque = 0;
        sprintf(aux2, "%05.2f", result.pid);
        sprintf(aux3, "%05.2f", result.nfHFD);
        sprintf(aux4, "%06.3f", result.left.slope);
        sprintf(aux5, "%06.3f", result.right.slope);
        Form4->PDatosV->Caption =  "BFP: " + AnsiString(result.bfp) + "   pid: " + aux2
                                   + "   slope L: " + aux4 + "   slope R: " + aux5 + "   nfHFD: " + aux3 ;
        indice_cfs++;
        strcpy(Buf_Cfs[indice_cfs],  "<xg>");  // guarda en flash del cfs posicion alcanzada
        indice_cfs++;
        strcpy(Buf_Cfs[indice_cfs],  "<xp>");  //
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::EPasosEnfoqueChange(TObject *Sender)
//------------------------------------------------------------------------------
{
    if ( Form1->EPasosEnfoque->Text.Trim() == "")
    {
        pasos_x = 0;
        Form1->EPasosEnfoque->Text = pasos_x;
        return;
    }
    try
    {
        pasos_x = Form1->EPasosEnfoque->Text.ToInt();
        if (pasos_x > 30000)
            pasos_x = 50;
        Form1->EPasosEnfoque->Text = pasos_x;
    }
    catch (...)
    {
        Form1->EPasosEnfoque->Text = pasos_x;
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::EVelocidadEnfoqueChange(TObject *Sender)
//------------------------------------------------------------------------------
{
    if ( Form1->EVelocidadEnfoque->Text.Trim() == "")
    {
        periodo_x = 20;
        Form1->EVelocidadEnfoque->Text = periodo_x;
        return;
    }
    try
    {
        periodo_x = Form1->EVelocidadEnfoque->Text.ToInt();
        if (periodo_x > 99)
            periodo_x = 20;
        Form1->EVelocidadEnfoque->Text = periodo_x;
    }
    catch (...)
    {
        Form1->EVelocidadEnfoque->Text = periodo_x;
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BrtmlClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    Fprog->Visible = true;
}

/*
Time/Location Commands (Hand Control)
The following commands set the time and location in the hand control.
The format of the location commands is: ABCDEFGH, where:

A is the number of degrees of latitude.
B is the number of minutes of latitude.
C is the number of seconds of latitude.
D is 0 for north and 1 for south.
E is the number of degrees of longitude.
F is the number of minutes of longitude.
G is the number of seconds of longitude.
H is 0 for east and 1 for west.

For example, to set (W) the location to
118°20’17" W, 33°50’41" N
you would send (note that latitude is before longitude):

"W" & chr(33) & chr(50) & chr(41) & chr(0) & chr(118) & chr(20) & chr(17) & chr(1)

The format of the time commands is: QRSTUVWX, where:

Q is the hour (24 hour clock).
R is the minutes.
S is the seconds.
T is the month.
U is the day.
V is the year (century assumed as 20).
W is the offset from GMT for the time zone. Note: if zone is negative, use 256-zone.
X is 1 to enable Daylight Savings and 0 for Standard Time.

For example, to set (H) the time to
3:26:00PM on April 6, 2005
in the Eastern time zone (-5 UTC: 256-5 = 251) you would send:

"H" & chr(15) & chr(26) & chr(0) & chr(4) & chr(6) & chr(5) & chr(251) & chr(1)

Note: All values are sent in binary format, not ASCII.
Note: The Get commands do not retrieve the time and location from the GPS unit (if one is present). The time and
location are retrieved from the hand control. You must first enter the View Time/Site menu to update the hand control
time if you want the time from the GPS or, use the GPS Commands in the next section.

Function: Get Location
Command : "w"
Response: chr(A) & chr(B) & chr(C) & chr(D) & chr(E) & chr(F) & chr(G) & chr(H) & "#"

Function: Set Location
Command : "W" & chr(A)  & chr(B)  & chr(C)  & chr(D) & chr(E)   & chr(F)  & chr(G)  & chr(H)
Example : "W" & chr(33) & chr(50) & chr(41) & chr(0) & chr(118) & chr(20) & chr(17) & chr(1)
Example : 118°20'17" W, 33°50'41" N
Response: "#"

Function: Get Time
Command : "h"
Response: chr(Q) & chr(R) & chr(S) & chr(T) & chr(U) & chr(V) & chr(W) & chr(X) & "#"

Function: Set Time
Command : "H" & chr(Q)  & chr(R)  & chr(S) & chr(T) & chr(U) & chr(V) & chr(W)   & chr(X)
Example : "H" & chr(15) & chr(26) & chr(0) & chr(4) & chr(6) & chr(5) & chr(251) & chr(1)
Example : 3:26:00PM on April 6, 2005 in the Eastern time zone (-5 UTC: 256-5 = 251)
Response: "#"

*/

//------------------------------------------------------------------------------
void __fastcall TForm1::BSendLXClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    EnviaLX(Form1->ELXsend->Text.c_str());
    //EnviaLX(":GT#");
}

//------------------------------------------------------------------------------
void __fastcall TForm1::BBAbrirObsClick(TObject *Sender)
//------------------------------------------------------------------------------
{

    if (Lemav2->Visible)
    {
        if (Form1->PTecho->Color == clSkyBlue)
        {
            if (Application->MessageBox("¿Confirma Cierre del Observatorio?", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
            {
                return;
            }
            Form1->Weather1->CloseShutter();
            Form1->PTecho->Caption = "Cerrando";
        }
        else
        {
            if (Application->MessageBox("¿Confirma Apertura del Observatorio?", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
            {
                return;
            }
            Form1->Weather1->OpenShutter();
            Form1->PTecho->Caption = "Abriendo";
        }
    }
    else
    {
        if (Application->MessageBox("¿Confirma Apertura/Cierre?", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
        {
            return;
        }
        indice_meteo++;
        if (Form1->PTecho->Color == clSkyBlue)
        {
            strcpy(Buf_Meteo[indice_meteo],  "(X000)");
            Form1->PTecho->Caption = "Cerrando";
        }
        else
        {
            strcpy(Buf_Meteo[indice_meteo],  "(X001)");
            Form1->PTecho->Caption = "Abriendo";
        }
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::CBCGEMClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    if (CBCGEM->Checked == true)
    {
        CGEM = true;
        LX200 = false;
        HPREC = cbPrecision->Checked;
        cbPrecision->Visible = true;
    }
    else
    {
        LX200 = true;
        CGEM = false;
        HPREC = false;
        cbPrecision->Visible = false;
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::MaskEditChange(TObject *Sender)
//------------------------------------------------------------------------------
{
    int valor = 0;
    if (TryStrToInt(((TMaskEdit*)(Sender))->Text, valor));

    if (valor > 59)
        ((TMaskEdit*)(Sender))->Text = "59";
}

//------------------------------------------------------------------------------
void __fastcall TForm1::EHraChange(TObject *Sender)
//------------------------------------------------------------------------------
{
    int valor = 0;
    if (TryStrToInt(((TMaskEdit*)(Sender))->Text, valor));

    if (valor > 23)
        ((TMaskEdit*)(Sender))->Text = "23";
}

//------------------------------------------------------------------------------
void __fastcall TForm1::EDdecChange(TObject *Sender)
//------------------------------------------------------------------------------
{
    int valor = 0;
    if (TryStrToInt(((TMaskEdit*)(Sender))->Text, valor));

    if (valor > 90)
        ((TMaskEdit*)(Sender))->Text = "90";
}

//------------------------------------------------------------------------------
void __fastcall TForm1::CBSincronizarClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    Sincronizando = ((TCheckBox*)Sender)->State;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::tsCGEMShow(TObject *Sender)
//------------------------------------------------------------------------------
{
    pedidaRaDe = false;

    char timeUTC[9];
    char timeLOC[9];

    SYSTEMTIME SysTime;
    GetSystemTime(&SysTime);

    TimeRxLX200 = Now();
    unsigned short msc;
    TimeRxLX200.DecodeTime(&telDat.horQ, &telDat.minR, &telDat.secS, &msc);
    TimeRxLX200.DecodeDate(&telDat.yerV, &telDat.monT, &telDat.dayU);

    sprintf(timeUTC, "%02d:%02d:%02d", SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
    sprintf(timeLOC, "%02d:%02d:%02d", telDat.horQ, telDat.minR, telDat.secS);

    Form1->eUTC->Text = timeUTC;
    Form1->eLocal->Text = timeLOC;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::bUTCClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    pedidaRaDe = false;

    unsigned short off, dst;

    off = 0;
    dst = Form1->cbDST->Checked;

    SYSTEMTIME SysTime;
    GetSystemTime(&SysTime);

    char tim[10] = {'H', SysTime.wHour, SysTime.wMinute, SysTime.wSecond, SysTime.wMonth,
                    SysTime.wDay, SysTime.wYear - 2000, off, dst
                   };

    EnviaLX(tim, 9);

    sprintf(tim, "%02d:%02d:%02d", SysTime.wHour, SysTime.wMinute, SysTime.wSecond);

    Form1->eUTC->Text = tim;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::bLocalClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    pedidaRaDe = false;

    TimeRxLX200 = Now();
    unsigned short msc;
    TimeRxLX200.DecodeTime(&telDat.horQ, &telDat.minR, &telDat.secS, &msc);
    TimeRxLX200.DecodeDate(&telDat.yerV, &telDat.monT, &telDat.dayU);

    telDat.yerV = telDat.yerV - 2000;

    telDat.offW = Form1->eOffset->Text.ToInt();
    telDat.dstX = Form1->cbDST->Checked;

    char tim[10] = {'H', telDat.horQ, telDat.minR, telDat.secS, telDat.monT,
                    telDat.dayU, telDat.yerV, telDat.offW, telDat.dstX
                   };
    EnviaLX(tim, 9);

    sprintf(tim, "%02d:%02d:%02d", telDat.horQ, telDat.minR, telDat.secS);

    Form1->eLocal->Text = tim;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::bPosClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    pedidaRaDe = false;
    char pos[10] = {'W', ini.Location.degLatA, ini.Location.minLatB, ini.Location.secLatC, ini.Location.nosLatD,
                         ini.Location.degLonE, ini.Location.minLonF, ini.Location.secLonG, ini.Location.eowLonH
                   };

    EnviaLX(pos, 9);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::rgTrackingClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    int option = Form1->rgTracking->ItemIndex;
    char track[3] = {'T', 0};

    track[1] = option;
    /*
    	switch (option)
    	{
    	case 0:
    		track[1] = 0;
    	break;
    	case 1:
    		char track[3] = {'H', 2};
    	break;
    	}
    */
    EnviaLX(track, 2);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::bGetDeviceVerClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    int device = Form1->rgDevice->ItemIndex;
    short dvCode = 0;
    char cmdV[2] = {'V'};

    switch (device)
    {
        case 0:
            dvCode = 0;
            command = GetVer;
            EnviaLX(cmdV, 1);
            break;
        case 1:
            dvCode = 16;
            break;
        case 2:
            dvCode = 17;
            break;
        case 3:
            dvCode = 176;
            break;
        case 4:
            dvCode = 178;
            break;
    }

    if (dvCode > 0)
    {
        char cmd[9] = {'P', 1, dvCode, 254, 0, 0, 0, 2};
        //short cmu[9] = {'P', 1, dvCode, 254, 0, 0, 0, 2};
        command = GetDevVer;
        EnviaLX(cmd, 8);
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::bSendSingleCommandClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    char cmd[2] = {0};

    if (Sender == bGetTrack)
    {
        cmd[0] = 't';
        command = GetTrackMode;
    }
    else if (Sender == bAlign)
    {
        cmd[0] = 'J';
        command = AlignComplete;
    }
    else if (Sender == bGotoProg)
    {
        cmd[0] = 'L';
        command = GotoProg;
    }
    else if (Sender == bCancelGoto)
    {
        cmd[0] = 'M';
        command = GotoCancel;
    }
    else if (Sender == bGetPosition)
    {
        cmd[0] = 'w';
        command = GetLoc;
    }
    else if (Sender == bGetTime)
    {
        cmd[0] = 'h';
        command = GetTime;
    }
    else if (Sender == bGetModel)
    {
        cmd[0] = 'm';
        command = GetModel;
    }

    EnviaLX(cmd, 1);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::rgDeviceClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    eDeviceVer->Text = "";
}

//------------------------------------------------------------------------------
void __fastcall TForm1::bEchoClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    char eco = Form1->eEcho->Text.c_str()[0];
    char cmd[3] = {'K', eco};

    EnviaLX(cmd, 2);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
//------------------------------------------------------------------------------
{
    VerInfo myVerInfo;

    Form1->Caption = myVerInfo.FileDescription + " v" +
                     myVerInfo.FileVersion + " " +
                     myVerInfo.LegalCopyright;
}

//------------------------------------------------------------------------------
void __fastcall TForm1::bTestClick(TObject *Sender)
//------------------------------------------------------------------------------
{
//    char aux[300];
//    char Name[80];
//
//    strcpy(aux,  "Test.fit");
//    strcpy(Name, "M57_1.fit");
//
//    //    if (FileExists(aux) )
//    //        DeleteFile(aux);
//
//    // CopyFile (ExistingFileName, NewFileName, FailIfExists);
//    // Parameter 3: FailIfExists [TRUE/FALSE] (uppercase)
//    // If this parameter is TRUE  and the new file specified by NewFileName already exists, the function fails.
//    // If this parameter is FALSE and the new file already exists, the function overwrites the existing file and succeeds.
//
//    bool b = CopyFile(Name, aux, FALSE);
//    int error = 0;
//
//    if (!b)
//    {
//        error = GetLastError();
//        WriteHistory("Error: " + error);
//    }
//    else
//    {
//        WriteHistory("OK");
//    }

    TDateTime* myTime = new TDateTime(Now());
    AnsiString S = myTime->FormatString(ini.Image.NameDir);
    WriteHistory(ini.Image.FotoDir + S);

}

//------------------------------------------------------------------------------
void __fastcall TForm1::cbDisableAllTimersClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    AnsiString strCaption;
    TCheckBox* cb = (TCheckBox*)Sender;

    cb->Checked ? strCaption = "Disable ALL Timers" :
                  strCaption = "Enable ALL Timers";

    cb->Caption = strCaption;
    setTimers(cb->Checked);
}

//==============================================================================
void setTimers (bool valEnabled)
//==============================================================================
{
    typedef TTimer* TTimers;
    TTimers Timers[6] = {Form1->Timer50,
                         Form1->Timer100,
                         Form1->Timer1000,
                         Form1->Timer3000,
                         Form1->Timer5000,
                         Form1->Timer60000};
    int index;
    AnsiString strEnabled;

    valEnabled ? strEnabled = " Enabled" : strEnabled = " Disabled";

    for (index = 0; index < 6; index++)
    {
        Timers[index]->Enabled = valEnabled;
        WriteHistory(Timers[index]->Name + strEnabled);
    }
}

//------------------------------------------------------------------------------
void __fastcall TForm1::sbCENClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    TSpeedButton* sb = (TSpeedButton*)Sender;

    SlewSpeed = readSpeedValues(sb);
}

//------------------------------------------------------------------------------
void __fastcall TForm1::SBstopClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    char cmd[2] = {0};

    cmd[0] = 'M';
    command = GotoCancel;

    EnviaLX(cmd, 1);

    if (((TSpeedButton*)Sender)->Down == true)
        ((TSpeedButton*)Sender)->Down = false;
    else
        ((TSpeedButton*)Sender)->Down = true;
}
//------------------------------------------------------------------------------



