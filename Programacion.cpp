//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Programacion.h"
#include "Principal.h"
#include "Historia.h"
#include "rueda.h"
#include "ConfiFiltro.h"
#include "DateUtils.hpp"
#include <fcntl.h>
#include <io.h>
#include <math.h>
#include <dstring.h>
#include <systdate.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define HayTarget  10
#define Inicio 15
#define EsperoDiaHora  20
#define EsperaStopLX 21
#define EsperaHorizonte 22
#define HacerSeries 30
#define InicioSerie 40
#define EsperaFinSerie 50
#define Enespera 1
#define Atrasado 2
#define Activo 3
#define Completo 4
#define Stop 999

TFprog *Fprog;

extern CRueda * Filtro;
extern int Binin;
extern int FotoActual;
extern bool FinFoto;
extern bool FinY;    //motor filtros
extern char dir_trab[250];
extern double tDe, tRa;
extern AnsiString HoraSideral_hms;
extern bool StopLX;

typedef struct
{
    int Count;
    char Name[100];
    int ExposureTime;
    int Bining;
    int Filter;
} Picture;

typedef struct
{
    char ID[100];
    char Name[100];
    double RightAscension;
    double Declination;
    TDateTime DateTime; //double DateTime;//
    int Series;
    Picture Foto[100];
    int Estado; // 1 pendiente, 0 acabado
} Target;

bool Repesca;
float HSLgrados;

Target Destino[100];
//Target DestOrden[100];

int nTarget, nPicture;
int destinos, cont_dest, series, cont_series, esp_horizon;
int AutoRun;
extern TDateTime Fecha;

// Definición de funciones
int GenerarFecha(AnsiString s, TDateTime *f);

extern void Slew_F(double dRA, double dDec);
extern void WriteHistory (AnsiString cadena);
double DiaJulianoPC();
double DiaJuliano(int anno, int mes, int dia, int hora, int min, int seg );

//------------------------------------------------------------------------------
__fastcall TFprog::TFprog(TComponent* Owner): TForm(Owner)
    //------------------------------------------------------------------------------
{
    //  Destino[1].DateTime = DiaJulianoPC() + 10/(24*3600.0);
    destinos = 0;
}

//==============================================================================
double DiaJuliano(int anno, int mes, int dia, int hora, int min, int seg )
//==============================================================================
{
    double JUL = 2400000.0 - 678987.0 + 367 * anno + 275 * mes / 9.0 + dia - 7 *
                 (anno + (mes + 9) / 12.0) / 4.0 + (hora * 3600 + min * 60 + seg) / 86400.0 ;
    return (JUL);
}

//==============================================================================
double DiaJulianoPC()
//==============================================================================
{
    double diaj;
    TDateTime Fe;
    diaj = 2415018.5 + Fe.CurrentDateTime();
    return (diaj);
}

//==============================================================================
double DiaJ2000PC()
//==============================================================================
{
    double diaj;
    TDateTime Fe, JD;
    //  TDateTime *J2000 = new TDateTime(2000,1,1);
    GenerarFecha("2000-01-01T12:00:00", &JD);
    //diaj = Fe.CurrentDateTime() + 0.5 - JD; // Porque se suma medio día aquí?
    diaj = Fe.CurrentDateTime() - JD;
    //  diaj = diaj - JD;
    return (diaj);
}

#define LON_CERRO 3.553056
//==============================================================================
double CalHSLgrados()
//==============================================================================
{
    //    HSLgrados = 100.46 + 0.985647 * DiaJ2000PC() - 3.68 + 15 * 24 * (double)Fecha.CurrentTime();
    HSLgrados = 100.46 + 0.985647 * DiaJ2000PC() - LON_CERRO + 15 * 24 * (double)Fecha.CurrentTime();
    while (HSLgrados > 360.0)
        HSLgrados = HSLgrados - 360;
    return (HSLgrados);
}

//#define KRAD (3.1416/180.0)
#define KRAD (M_PI/180.0)
#define LAT 40.416666
#define LAT_CERRO 40.418056
//==============================================================================
// Calcula la altura actual del objeto
// sin(ALT) = sin(DEC)*sin(LAT)+cos(DEC)*cos(LAT)*cos(HA)
double CalAltura(double ARec, double DEC)
//==============================================================================
{
    double HA, ALT;
    HA = CalHSLgrados() -  ARec;
    if (HA < 0) HA = HA + 360;

    // ALT = asin( sin(DEC * KRAD) * sin(LAT * KRAD) + cos(DEC * KRAD) * cos(LAT * KRAD) * cos(HA * KRAD) );
    ALT = asin( sin(DEC * KRAD) * sin(LAT_CERRO * KRAD) +
                cos(DEC * KRAD) * cos(LAT_CERRO * KRAD) * cos(HA * KRAD) );
    return (ALT / KRAD);
}

//==============================================================================
//               sin(DEC) - sin(ALT)*sin(LAT)
// cos(A)   =   ---------------------------------
//                   cos(ALT)*cos(LAT)
// If sin(HA) is negative, then AZ = A, otherwise AZ = 360 - A
double CalAzimut(double ALT, double ARec, double DEC)
//==============================================================================
{
    double HA, AZ, hside;
    hside = CalHSLgrados();
    HA = hside -  ARec;
    //WriteHistory("HSid: " + AnsiString(hside) + " ARec: " + AnsiString(ARec) );
    AZ = acos( (sin(DEC * KRAD) - sin(ALT * KRAD) * sin(LAT * KRAD)) / (cos(ALT * KRAD) * cos(LAT * KRAD)  ) ) / KRAD;
    if (sin(HA * KRAD) < 0) //??? al pasar de 360 el azimut sale mal
        // AZ = 360 - AZ;
        AZ = AZ;
    else              //con Dec negativa sale bien
        AZ = 360 - AZ;
    // if (ALT < 0)
    //     AZ = 360 - AZ;

    return (AZ);
}

//==============================================================================
AnsiString ConvRtml(AnsiString cab, int dat)
//==============================================================================
{
    char aux[1000];
    sprintf(aux, "<%s>%d</%s>", cab.c_str(), dat, cab.c_str());
    return (AnsiString(aux));
}

//==============================================================================
AnsiString ConvRtml(AnsiString cab, float dat)
//==============================================================================
{
    char aux[1000];
    sprintf(aux, "<%s>%f</%s>", cab.c_str(), dat, cab.c_str());
    return (AnsiString(aux));
}

//==============================================================================
AnsiString ConvRtml(AnsiString cab, char *dat)
//==============================================================================
{
    char aux[1000];
    sprintf(aux, "<%s>%s</%s>", cab.c_str(), dat, cab.c_str());
    return (AnsiString(aux));
}

//==============================================================================
AnsiString ConvRtml(AnsiString cab, double *dat)
//==============================================================================
{
    char aux[1000];
    sprintf(aux, "<%s>%s</%s>", cab.c_str(), dat, cab.c_str());
    return (AnsiString(aux));
}

//==============================================================================
// Genera un DateTime a partir de cadenas con formato rxml: 2007-06-01T09:00:00
int GenerarFecha(AnsiString s, TDateTime *f)
//==============================================================================
{
    int anno, mes, dia, hora, min, seg;
    if (s.Length() > 0)
        try
        {
            anno = s.SubString(0, s.Pos("-") - 1).ToInt();
            s = s.SubString( s.Pos("-") + 1, s.Length() - s.Pos("-"));
            mes = s.SubString(0, s.Pos("-") - 1).ToInt();
            s = s.SubString(s.Pos("-") + 1, s.Length() - s.Pos("-"));
            dia = s.SubString(0, s.Pos("T") - 1).ToInt();
            s = s.SubString(s.Pos("T") + 1, s.Length() - s.Pos("T"));
            hora = s.SubString(0, s.Pos(":") - 1).ToInt();
            s = s.SubString(s.Pos(":") + 1, s.Length() - s.Pos(":"));
            min = s.SubString(0, s.Pos(":") - 1).ToInt();
            s = s.SubString(s.Pos(":") + 1, s.Length() - s.Pos(":"));
            seg = s.ToInt();
            *f = RecodeDateTime(*f, anno, mes, dia, hora, min, seg, 0);
        }
        catch (...)
        {
            return -1;
        }
    return 0;
}

//==============================================================================
int BuscarXML(AnsiString cab, AnsiString buf, AnsiString *dato, AnsiString *resto)
//==============================================================================
{
    AnsiString inicab = "<"  + cab + ">";
    AnsiString endcab = "</" + cab + ">";
    int ind1 = 0, ind2 = 0;

    ind1 = buf.Pos( inicab );
    if (ind1 == 0)
    {
        *dato = "";
        return -1;
    }
    ind2 = buf.Pos( endcab );
    *dato = buf.SubString( ind1 + inicab.Length(), ind2 - (ind1 + inicab.Length()) ).Trim();
    *resto = buf.SubString(ind2 + endcab.Length(), buf.Length() + 1 - (ind2 + endcab.Length() ));
    return 0;
}

//==============================================================================
void ProcesarPicture(AnsiString sPicture)
//==============================================================================
{
    AnsiString dato, resto;

    nPicture++;
    if (BuscarXML("Filter",       sPicture, &dato, &resto) == 0)
        Destino[nTarget].Foto[nPicture].Filter       = dato.ToInt();
    if (BuscarXML("Count",        sPicture, &dato, &resto) == 0)
        Destino[nTarget].Foto[nPicture].Count        = dato.ToInt();
    if (BuscarXML("Binning",      sPicture, &dato, &resto) == 0)
        Destino[nTarget].Foto[nPicture].Bining       = dato.ToInt();
    if (BuscarXML("ExposureTime", sPicture, &dato, &resto) == 0)
        Destino[nTarget].Foto[nPicture].ExposureTime = dato.ToInt();
}

//==============================================================================
void ProcesarTarget(AnsiString sTarget)
//==============================================================================
{
    AnsiString dato, resto, sf, aux;
    TDateTime fecha;
    resto = sTarget;
    int x, y;

    BuscarXML("Name", sTarget, &dato, &resto);
    strcpy(Destino[nTarget].Name, dato.c_str());
    BuscarXML("ID", sTarget, &dato, &resto);
    if (dato.UpperCase() == "AUTO")
    {
        TDateTime* myTime = new TDateTime(Now());
        String S = myTime->FormatString("yyyy-mm-dd");

        strcpy(Destino[nTarget].ID, S.c_str());
    }
    else
    {
        strcpy(Destino[nTarget].ID, dato.c_str());
    }

    if (BuscarXML("RightAscension", sTarget, &dato, &resto) == 0)
    {
        y = strlen(dato.c_str());
        for (x = 0; x < y; x++)
        {
            if (dato.c_str()[x] == '.') dato.c_str()[x] = ',';
        }
        Destino[nTarget].RightAscension = dato.ToDouble();  //pasa ar a horas para LX
    }
    else
        Destino[nTarget].RightAscension = -1;
    if (BuscarXML("Declination", sTarget, &dato, &resto) == 0)
    {
        y = strlen(dato.c_str());
        for (x = 0; x < y; x++)
        {
            if (dato.c_str()[x] == '.') dato.c_str()[x] = ',';
        }
        Destino[nTarget].Declination = dato.ToDouble();
    }
    else
        Destino[nTarget].Declination = -101;

    BuscarXML("DateTime", sTarget, &dato, &resto);
    if (GenerarFecha(dato, &fecha) == 0)
        Destino[nTarget].DateTime =  fecha;
    else
        Fprog->Mver_rtml->Lines->Add("Error Fecha" );

    nPicture = 0;
    while (BuscarXML("Picture", resto, &dato, &resto) != -1)
    {
        ProcesarPicture(dato);
    }

    Destino[nTarget].Series = nPicture;
    Destino[nTarget].Estado = Enespera;

    nTarget++;
}

//==============================================================================
void ProcesarFichero(AnsiString s)
//==============================================================================
{
    AnsiString dato, resto;
    resto = s;
    while (BuscarXML("Target", resto, &dato, &resto) != -1)
    {
        ProcesarTarget(dato);
    }
}

//==============================================================================
void  OrdenaTarget(void)
//==============================================================================
{
    int i, j;
    Target a;

    //  for ( i = 0; i < nTarget; i++)
    //    DestOrden[i] = Destino[i];

    for ( j = 1; j < nTarget; j++)
    {
        a =  Destino[j];
        i = j - 1;
        while ( i >= 0 && Destino[i].DateTime > a.DateTime)
        {
            Destino[i + 1] = Destino[i];
            i--;
        }
        Destino[i + 1] = a;
    }
}

//==============================================================================
void PresentarFichero()
//==============================================================================
{
    int d, s;
    char cad1[32], cad2[32];
    for ( d = 0; d < nTarget; d++)
    {
        Fprog->Mver_rtml->Lines->Add("  ");
        Fprog->Mver_rtml->Lines->Add("Destino " + AnsiString(d + 1) + "    " + AnsiString(Destino[d].Name)
                                     + "    Directorio: " +  AnsiString(Destino[d].ID));
        Fprog->Mver_rtml->Lines->Add("  DateTime " + AnsiString(Destino[d].DateTime));

        if (fabs(Destino[d].Declination) < 101 && Destino[d].RightAscension >= 0 )
        {
            sprintf(cad1, "%003.0004f", Destino[d].RightAscension / 15);
            sprintf(cad2, "%003.0004f", Destino[d].Declination);
            Fprog->Mver_rtml->Lines->Add("  AR " + AnsiString(cad1)  + "h Dec " + AnsiString(cad2)  );

            double altura, azimut;
            altura = CalAltura(Destino[d].RightAscension,  Destino[d].Declination);
            azimut = CalAzimut(altura, Destino[d].RightAscension,  Destino[d].Declination);
            sprintf(cad1, "%003.02f", altura);
            sprintf(cad2, "%003.02f", azimut);
            Fprog->Mver_rtml->Lines->Add("  Alt: " + AnsiString(cad1) + ("  Az: ") + AnsiString(cad2));
        }
        for (s = 0; s < Destino[d].Series; s++)
        {
            Fprog->Mver_rtml->Lines->Add("    Picture " + AnsiString(s + 1) + " Filter " + AnsiString(Destino[d].Foto[s + 1].Filter)
                                         + "  Count  " + AnsiString(Destino[d].Foto[s + 1].Count)
                                         + "  Binning " + AnsiString(Destino[d].Foto[s + 1].Bining)
                                         + "  Exp sg " + AnsiString(Destino[d].Foto[s + 1].ExposureTime));
        }
    }
}

//------------------------------------------------------------------------------
void __fastcall TFprog::BGuardaXMLClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    AnsiString ss = "", ss1, ss2 = "";

    for (int ct = 0; ct <  2; ct++)
    {
        for (int cs = 0; cs <  Destino[ct].Series; cs++)
        {
            ss2 += ConvRtml("Picture",
                            (ConvRtml("Filter", Destino[ct].Foto[cs + 1].Filter).c_str() +
                             ConvRtml("Binning", Destino[ct].Foto[cs + 1].Bining) +
                             ConvRtml("Count", Destino[ct].Foto[cs + 1].Count) +
                             ConvRtml("ExposureTime", Destino[ct].Foto[cs + 1].ExposureTime)).c_str());
        }
        ss1 = ConvRtml("Name", Destino[ct].Name) +  ConvRtml("DateTime", Destino[ct].DateTime.FormatString("yyyy-mm-dd'T'hh:mm:ss").c_str() ) +
              ConvRtml("Series", Destino[ct].Series) +  ss2;
        ss += ConvRtml("Target",   ss1.c_str() );
        ss1 = "";
        ss2 = "";
    }
    Mver_rtml->Lines->Add(ss);
    ProcesarFichero(ss);
}

//------------------------------------------------------------------------------
void __fastcall TFprog::BLeerFichXmlClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    char cadxml[100000]; // 10000 son 7 objetos máximo
    long kk;
    int handle;

    if (ODxml->Execute())
    {
        Fprog->Mver_rtml->Lines->Add("  ");
        Fprog->Mver_rtml->Lines->Add(" ------------------------------------ ");
        Mver_rtml->Lines->Add(ODxml->FileName);

        if ((handle = open(ODxml->FileName.c_str(), O_RDONLY  )) != NULL)
        {
            kk = filelength(handle);
            if (kk < 100000) //StrLen(cadxml))
            {
                read(handle, cadxml, kk);
                cadxml[kk] = 0;
                close(handle);
            }
            else
                Application->MessageBox("Fichero Demasiado Largo.", "", 0);
        }
        else
            Application->MessageBox("Fichero xml no existe.", "", 0);
    }

    nTarget = 0;
    ProcesarFichero(cadxml);
    // PresentarFichero();
    OrdenaTarget();
    PresentarFichero();
    //  PresentarOrdenado();
}

//------------------------------------------------------------------------------
void __fastcall TFprog::BFicheroXmlClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    /*  FILE *pfxml;                          // pointer to the FITS file, defined in fitsio.h

      if(ODxml->Execute())
      {
        if((pfxml = AbrirFoto(ODxml->FileName.c_str())) == NULL)
          return;
      }
      else
        return;
    */
}

//------------------------------------------------------------------------------
// Lanza la adquisicion
void __fastcall TFprog::BCargaClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    static int estado;
    TDateTime Fecha1;

    if (AutoRun == 0)
    {
        destinos = nTarget;
        cont_dest = 0;
        esp_horizon = 0;
        cont_series = 0;
        Repesca = false;
        AutoRun = HayTarget;
        FinFoto = true;
        Timer1->Enabled = true;
        BCarga->Caption = "Pausar";
    }
    else
    {
        Fecha1 = Fecha.CurrentTime();
        if (AutoRun != Stop )
        {
            estado = AutoRun;
            AutoRun = Stop;
            BCarga->Font->Size = 10;
            BCarga->Caption = "Reiniciar";
            WriteHistory(AnsiString(Fecha1) + "  PAUSA Manual" );
        }
        else
        {
            if ( AutoRun == Stop)
            {
                BCarga->Font->Size = 8;
                BCarga->Caption = "Pausar";
                AutoRun = estado;
                WriteHistory(AnsiString(Fecha1) + "  REINICIO Manual" );
            }
        }
    }
}

//------------------------------------------------------------------------------
void __fastcall TFprog::BParaAutoClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    AutoRun = 0;
    WriteHistory("STOP Manual Adquisicion Automatica" );
    // Timer1->Enabled = false;
    SetCurrentDirectory(dir_trab);
}

//==============================================================================
AnsiString FormatAutoRun(int AutoRun)
//==============================================================================
{
    AnsiString cad;

    switch (AutoRun)
    {
        case HayTarget:
            cad = "HayTarget";
            break;
        case Inicio:
            cad = "Inicio";
            break;
        case EsperoDiaHora:
            cad = "EsperoDiaHora";
            break;
        case EsperaStopLX:
            cad = "EsperaStopLX";
            break;
        case EsperaHorizonte:
            cad = "EsperaHorizonte";
            break;
        case HacerSeries:
            cad = "HacerSeries";
            break;
        case InicioSerie:
            cad = "InicioSerie";
            break;
        case EsperaFinSerie:
            cad = "EsperaFinSerie";
            break;
        case Enespera:
            cad = "Enespera";
            break;
        case Atrasado:
            cad = "Atrasado";
            break;
        case Activo:
            cad = "Activo";
            break;
        case Completo:
            cad = "Completo";
            break;
        case Stop:
            cad = "Stop";
            break;
        default:
            cad = AnsiString(AutoRun);
    }

    return "Estado: " + cad;

}

//------------------------------------------------------------------------------
void __fastcall TFprog::Timer1Timer(TObject *Sender)
//------------------------------------------------------------------------------
{
    char DirTarget[300], cad1[32], cad2[32];
    static int DogEsperaStopLX;
    float alt, azi;
    static double dde, dar, dde_ant, dar_ant;
    static bool Repesca;
    TDateTime Fecha1;

    sprintf(cad1, "%003.0004f", (tDe - Destino[cont_dest].Declination));
    sprintf(cad2, "%003.0004f", (tRa - Destino[cont_dest].RightAscension));
    Form1->LDifCoord->Caption = (AnsiString(cad2) + " _ " + AnsiString(cad1));

    if (AutoRun == HayTarget)
    {
        AutoRun = Inicio;
        Repesca = 0;
        Fecha1 = Fecha.CurrentDateTime();
        WriteHistory(" ");
        WriteHistory(" ------------------------------------ ");
        WriteHistory(ODxml->FileName);
        WriteHistory(AnsiString(Fecha1) + " Lanzado Fichero con " + AnsiString(nTarget) + "  Objetos");
        Form1->CBGuardar->Checked = true;
    }
    else if (AutoRun == Inicio)
    {
        if (Repesca == 0)
        {
            if (cont_dest < destinos)
            {
                AutoRun = EsperoDiaHora;
                WriteHistory(" " );
                WriteHistory("Esperando Hora " +  Destino[cont_dest].DateTime );
                strcpy(DirTarget, dir_trab);
                strcat(DirTarget, Destino[cont_dest].ID);
                CreateDirectory(DirTarget, NULL);
                SetCurrentDirectory(DirTarget);
            }
            else
            {
                if  (cont_dest >= destinos)
                {
                    if (esp_horizon > 0)
                    {
                        Repesca = 1;
                        //                 AutoRun = EsperaHorizonte;
                        WriteHistory("Esperando Horizonte " + AnsiString(esp_horizon) + " destinos. " );
                        WriteHistory(" ");
                        esp_horizon = 0;
                        cont_dest = 0;
                    }
                    else
                    {
                        AutoRun = 0;
                        Repesca = 0;
                        Fecha1 = Fecha.CurrentDateTime();
                        WriteHistory(" " );
                        WriteHistory(AnsiString(Fecha1) + "   Fin del Script.");
                        WriteHistory(" " );
                        Form1->ENombreFichero->Text = "aux";
                        SetCurrentDirectory(dir_trab);
                        cont_dest = 0;
                        cont_series = 0;
                    }
                }
            }
        }
        else if (Repesca == 1)
        {
            if (cont_dest < destinos)
            {
                AutoRun = EsperaHorizonte;
                if (Destino[cont_dest].Estado == Atrasado)
                {
                    //          WriteHistory("Espero Horizonte Destino " +  AnsiString(cont_dest+1));
                    alt = CalAltura(Destino[cont_dest].RightAscension,  Destino[cont_dest].Declination);
                    azi = CalAzimut(alt, Destino[cont_dest].RightAscension,  Destino[cont_dest].Declination);
                    sprintf(cad1, "%003.002f", alt);
                    sprintf(cad2, "%003.002f", azi);
                    LRestante->Caption = ( "Des. " + AnsiString(cont_dest + 1)
                                           + "  ALT: "  + AnsiString(cad1) + "   AZ: " + AnsiString(cad2));
                    strcpy(DirTarget, dir_trab);
                    strcat(DirTarget, Destino[cont_dest].ID);
                    CreateDirectory(DirTarget, NULL);
                    SetCurrentDirectory(DirTarget);
                }
            }
            else
            {
                if  (cont_dest >= destinos)   // ha terminado un repaso
                {
                    if (esp_horizon > 0)
                    {
                        Repesca = 1;
                        AutoRun = Inicio;
                        //            WriteHistory("Esperando Horizonte " + AnsiString(esp_horizon) + " destinos. " );
                        LPending->Caption = ( "Pend: " + AnsiString(esp_horizon));

                        //            WriteHistory(" ");
                        esp_horizon = 0;
                        cont_dest = 0;
                    }
                    else
                    {
                        AutoRun = 0;
                        Repesca = 0;
                        Fecha1 = Fecha.CurrentDateTime();
                        WriteHistory(" " );
                        WriteHistory(AnsiString(Fecha1) + "   Fin del Script.");
                        WriteHistory(" " );
                        Form1->ENombreFichero->Text = "aux";
                        SetCurrentDirectory(dir_trab);
                        cont_dest = 0;
                        cont_series = 0;
                        LRestante->Caption = ( "   " );
                        LPending->Caption = ( "   "  );
                    }
                }
            }
        }
    }
    else if (AutoRun == EsperaHorizonte)
    {
        if (Destino[cont_dest].Estado == Atrasado )
        {
            alt = CalAltura(Destino[cont_dest].RightAscension,  Destino[cont_dest].Declination);
            azi = CalAzimut(alt, Destino[cont_dest].RightAscension,  Destino[cont_dest].Declination);
            sprintf(cad1, "%003.002f", alt);
            sprintf(cad2, "%003.002f", azi);
            //      LRestante->Caption = ( "Destino " + AnsiString(cont_dest+1) +"  ALT: " + AnsiString(cad1) + "   AZ: " +AnsiString(cad2));
            if ( alt > EAlturaInf->Text && alt < EAlturaSup->Text  && azi > EAzimut1->Text && azi < EAzimut2->Text )
            {
                AutoRun = EsperaStopLX;
                Destino[cont_dest].Estado = Activo;
                WriteHistory("Horizonte Destino " + AnsiString( cont_dest + 1) + " Alcanzado.");
                WriteHistory("Colocando Filtro " + AnsiString( Destino[cont_dest].Foto[cont_series + 1].Filter) );
                Filtro->mover_rueda( Destino[cont_dest].Foto[cont_series + 1].Filter);
                sprintf(cad1, "%003.0004f", Destino[cont_dest].Declination);
                sprintf(cad2, "%003.0004f", Destino[cont_dest].RightAscension / 15);
                WriteHistory("Moviendo Telescopio  AR: " + AnsiString(cad2) + "h  Dec: " + AnsiString(cad1) + "º");
                MessageBeep(MB_ICONEXCLAMATION);
                Form1->SBstop->Font->Color = clRed;
                Slew_F(Destino[cont_dest].RightAscension,  Destino[cont_dest].Declination);
                DogEsperaStopLX = 0;
            }
            else             // aun no cumple horizonte
            {
                cont_dest++;   // pasa al siguiente
                esp_horizon++;
                AutoRun = Inicio;
            }
        }
        else    // pasa al siguiente, este no es Atrasado
        {
            AutoRun = Inicio;
            cont_dest++;
        }
    }
    else if (AutoRun == EsperoDiaHora)
    {
        if (Fecha.CurrentDateTime() >= Destino[cont_dest].DateTime )
        {
            alt = CalAltura(Destino[cont_dest].RightAscension,  Destino[cont_dest].Declination);
            azi = CalAzimut(alt, Destino[cont_dest].RightAscension,  Destino[cont_dest].Declination);
            if ( alt > EAlturaInf->Text && alt < EAlturaSup->Text  && azi > EAzimut1->Text && azi < EAzimut2->Text )
            {
                AutoRun = EsperaStopLX;
                Destino[cont_dest].Estado = Activo;
                sprintf(cad1, "%003.0004f", Destino[cont_dest].Declination);
                sprintf(cad2, "%003.0004f", Destino[cont_dest].RightAscension / 15);
                Filtro->mover_rueda( Destino[cont_dest].Foto[cont_series + 1].Filter);
                WriteHistory("Colocando Filtro " +
                                                AnsiString( Destino[cont_dest].Foto[cont_series + 1].Filter) );
                WriteHistory("Moviendo Telescopio  AR: " + AnsiString(cad2) + "h  Dec: " + AnsiString(cad1) + "º");
                MessageBeep(MB_ICONEXCLAMATION);
                Form1->SBstop->Font->Color = clRed;
                Slew_F(Destino[cont_dest].RightAscension,  Destino[cont_dest].Declination);
                DogEsperaStopLX = 0;
            }
            else  //no cumple ALT y AZIMUT
            {
                //        if (cont_dest < destinos) {
                AutoRun = Inicio;
                Destino[cont_dest].Estado = Atrasado; //foto en espera de horizonte
                WriteHistory("Alt " +  AnsiString(alt) + "   Azi " + AnsiString(azi));
                cont_dest++;
                esp_horizon++;
                WriteHistory("Destino " + AnsiString(cont_dest) + "  Bajo el Horizonte. " );
                WriteHistory("Retrasados " + AnsiString(esp_horizon) + "  destinos. " );
            }
        }
    }
    else if (AutoRun == EsperaStopLX)
    {

        dde = 100 * (tDe - Destino[cont_dest].Declination);
        dar = 100 * (tRa - Destino[cont_dest].RightAscension);

        if ( (abs(dde) < 5) && (abs(dar) < 3) )
        {
            AutoRun = HacerSeries;
            Form1->SBstop->Font->Color = clWindowText;
            sprintf(cad1, "%003.0004f", (tDe - Destino[cont_dest].Declination));
            sprintf(cad2, "%003.0004f", (tRa - Destino[cont_dest].RightAscension));
            WriteHistory("Coordenadas Alcanzadas: dif DEC " + AnsiString(cad1)
                                             + "   dif RA " + AnsiString(cad2));
        }
        if (dde_ant == dde && dar_ant == dar)
            DogEsperaStopLX++;
        dde_ant = dde;
        dar_ant = dar;
        if ( DogEsperaStopLX > 20)
        {
            cont_series = Destino[cont_dest].Series;  //da por concluida la serie
            AutoRun = HacerSeries;
            WriteHistory(" Coordenadas No Alcanzadas " );
        }
    }
    else if (AutoRun == HacerSeries)
    {
        if (cont_series < Destino[cont_dest].Series)
        {
            AutoRun = InicioSerie;
            Fecha1 = Fecha.CurrentTime();
            WriteHistory( AnsiString(Fecha1) + "  Inicio Serie" );
            cont_series++;
        }
        else     //acabo una serie
        {
            cont_series = 0;
            Fecha1 = Fecha.CurrentTime();
            if ( DogEsperaStopLX > 20)
            {
                Destino[cont_dest].Estado = Atrasado; // marca destino como completado
                WriteHistory( AnsiString(Fecha1) + "  Destino " + AnsiString(cont_dest + 1)
                                                 + " Atrasado");
                esp_horizon++;
            }
            else
            {
                Destino[cont_dest].Estado = Completo; // marca destino como completado
                WriteHistory( AnsiString(Fecha1) + "  Destino " + AnsiString(cont_dest + 1)
                                                 + " Completo");
            }
            WriteHistory(" ");
            cont_dest++;
            AutoRun = Inicio;
        }
    }
    else if (AutoRun == InicioSerie)
    {
        AutoRun = EsperaFinSerie;
        Binin = Destino[cont_dest].Foto[cont_series].Bining;
        Form1->TBBinin->Position = Binin;
        Form1->ENFotos->Text = Destino[cont_dest].Foto[cont_series].Count;
        Form1->Esg->Text =  Destino[cont_dest].Foto[cont_series].ExposureTime;
        Form1->ENombreFichero->Text = Destino[cont_dest].Name + AnsiString("_") + AnsiString(cont_series);
        Form1->IFotoMouseDown(NULL, (TMouseButton)NULL, TShiftState(), 0, 0);
    }
    else if (AutoRun == EsperaFinSerie)
    {
        if ((FinFoto) && (FotoActual  > Form1->ENFotos->Text.ToInt()))
        {
            AutoRun = HacerSeries;
            Destino[cont_dest].Estado = Completo;
        }
    }

    LTdateTime->Caption = ( "H Local :  " + Fecha.CurrentTime());

    //Label1->Caption = ("Estado :" + AnsiString(AutoRun));
    lEstado->Caption = FormatAutoRun(AutoRun);

    sprintf(cad1, "%003.0005f", DiaJulianoPC());
    Label3->Caption = ( "DJ: " + AnsiString(cad1));

    sprintf(cad1, "%003.0005f", DiaJ2000PC());
    LJ2000->Caption = ( "J2000: " + AnsiString( cad1) );

    float hs = CalHSLgrados() / 15.0;
    float ms = (hs - abs(hs)) * 60;
    float ss = (ms - abs(ms)) * 60;
    sprintf(cad1, "%02i", abs(hs));
    strcat(cad1, ":");
    sprintf(cad2, "%02i", abs(ms));
    strcat(cad1, cad2);
    strcat(cad1, ":");
    sprintf(cad2, "%02i", abs(ss));
    strcat(cad1, cad2);

    //  sprintf(cad1,"%003.0004f", CalHSLgrados()/15.0);
    LHSideral->Caption = ( "H Sideral: " +  AnsiString(cad1));
    Form1->LHoraSideral->Caption = ( "HS: " +  AnsiString(cad1));
    HoraSideral_hms = AnsiString(cad1);
    //  Lhms_sid->Caption = ( "HS: " +  AnsiString(cad1));

}

//------------------------------------------------------------------------------
void __fastcall TFprog::BClearClick(TObject *Sender)
//------------------------------------------------------------------------------
{
    Fprog->Mver_rtml->Lines->Clear();
}

