//---------------------------------------------------------------------------
#ifndef socketH
#define socketH

#include <winsock.h>
#include "fitsio.h"

#define  NO_FLAGS_SET         0      /* Used with recv()/send()*/
//#define  NUMERO_PUERTO 1235
#define  NUMERO_PUERTO 1236
#define  M_Rabbit    0  // Mensajes propios del Rabbit
#define  M_Terminal  1  // Mensajes propios del Terminal
#define  M_LX200     2  // Mensajes del LX200
#define  M_CFS       3  // Mensajes del CFS
#define  M_Meteo     4  // Mensajes meteorologia
#define  M_Camara   30  // Mensajes de la camara1
#define  M_F_CamaraA  31 // Mensajes Tiempos camaraA
#define  M_CamaraB  32  // Mensajes de la camara2
#define  M_F_CamaraB   33  // Mensaje Tiempos de la camaraB

#define MaxX 2000
#define MaxY 2000
//---------------------------------------------------------------------------

fitsfile * AbrirFoto(char *nombre);
void GuardarFoto(char* nombre);

#define TAMBUFF 50000
class CSocket : public TThread
{
protected:
    void __fastcall Execute();
public:
    WSADATA     WSAData;
    u_short     NumeroPuerto;
    bool        limpiarBuffer, limpiarBufferRabbit, limpiarBufferLX200;
    int         pLeer, pEscribir;
    int         pLeerRabbit, pEscribirRabbit;
    int         pLeerLX200, pEscribirLX200;
    int         pLeerCFS, pEscribirCFS;
    int         pLeerMeteo, pEscribirMeteo;
    int         pLeerTESs, pEscribirTESs;
    char        Datos[TAMBUFF];
    char        DatosRabbit[TAMBUFF];
    char        DatosLX200[TAMBUFF];
    char        DatosCFS[TAMBUFF];
    char        DatosMeteo[TAMBUFF];
    char        DatosTESs[TAMBUFF];
    /*
        short m_x1;
        short m_y1;
        short m_x2;
        short m_y2;
        unsigned char m_binin;
        short m_seg;
        short m_mseg;
        short m_NumCol;
        short m_NumFil;
        short m_limpiado;
        short m_obturador;
        short m_retraso;
        unsigned char m_test;
        unsigned char m_cancel;
        WideString NombreFichero;
    */
private:
    void __fastcall ProcesarMensaje(char *buff, int tam);
    void __fastcall MensajeRabbit(char *buff, int tam);
    void __fastcall MensajeLX200(char *buff, int tam);
    void __fastcall MensajeCFS(char *buff, int tam);
    void __fastcall MensajeMeteo(char *buff, int tam);
    void __fastcall MensajeTESs(char *buff, int tam);
    void __fastcall MensajeCamara(char *buff, int tam);
    void __fastcall MensajeF_CamaraA(char *buff, int tam);
    void __fastcall MensajeF_CamaraB(char *buff, int tam);
    void __fastcall MensajeCupula(char *buff, int tam);
    //void __fastcall F();
public:
    //    short m_numfotos;
    void __fastcall IniciarRabbit();
    bool PerdidaConexion;
    char          Mascara[20];
    char          cadenaIP[50];
    unsigned long IP;
    char          cadenaIPRabbit[20];
    unsigned long IPRabbit;
    char          NombreHostLocal[80];
    int           nDatos;
    int           nDatosRabbit;
    int           nDatosLX200;
    int           nDatosCFS;
    int           nDatosTESs;
    int           nDatosMeteo;
    SOCKET        sock;
public:
    __fastcall CSocket(u_short NPuerto = NUMERO_PUERTO, bool CreateSuspended = true);
    __fastcall ~CSocket();
    void __fastcall ComprobarConexion(DWORD T);
    int __fastcall Escribir(char *datos, int num, u_long direccion);
    int __fastcall Escribir(char *datos, int num, SOCKADDR_IN to);
    int __fastcall Escribir(char *datos, int num);
    int __fastcall Leer(char *datos, int num);
    int __fastcall LeerRabbit(char *datos, int num);
    int __fastcall LeerLX200(char *datos, int num);
    int __fastcall LeerCFS(char *datos, int num);
    int __fastcall LeerTESs(char *datos, int num);
    int __fastcall LeerMeteo(char *datos, int num);
    //    void __fastcall LimpiarBuffer();
    //    void __fastcall LimpiarBufferRabbit();
    void __fastcall LimpiarBufferLX200();
    //    void __fastcall LimpiarBufferMeteo();
    /*
        void __fastcall HacerFoto( short x1, short y1, short x2, short y2, unsigned char binin,
                                   short seg, short mseg, short NumCol, short NumFil,
                                   unsigned char test, unsigned char cancel, short nfotos,
                                   short limpiado, short obturador, short retraso, WideString nomb
                                 );
    */
};
#endif
