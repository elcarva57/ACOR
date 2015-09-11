//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>

#include "socket.h"
#include "Principal.h"
#include "visualizar.h"
#include "Foto.h"
#include "Historia.h"

int numeroOrden;
bool FinFoto = false;
bool A_FinFoto = false;
bool B_FinFoto = false;

DWORD A_T_Ini_Exp, A_T_Ini_Lect, A_T_Fin_Lect;
DWORD B_T_Ini_Exp, B_T_Ini_Lect, B_T_Fin_Lect;

extern cFoto *FotoPrincipal;
extern int X1FS, X2FS, Y1FS, Y2FS;

bool LeyendoFoto = false;
int numeroLinea;
char Salidas, Grupos[4];
int paquetesperdidos = 0;
int numeroOrdenAnterior = 0;
extern DWORD TiempoUltimoPaquete;
int Tccd;
int TccdA, TcajaA, VpeltierA, TccdB, TcajaB, VpeltierB;
char carecta[100], cdeclinacion[100];
//---------------------------------------------------------------------------


char CadenaIdentificacion[50]  = "Solicitando conexion COR";  // PC -> COR para empezar la conexion
char CadenaPresencia[50]       = "Continuar conexion COR";    // PC -> COR para mantener conexion
char CadenaPresenciaRabbit[50] = "COR conectado";             // COR-> PC para mantener conexion
char CadenaPresenciaRabbitInicio[50] = "COR presente";        // COR-> PC para empezar conexion


//---------------------------------------------------------------------------
DWORD TUltimoEnvio, TRabbit;
//---------------------------------------------------------------------------
bool LineaNueva = false;

extern DWORD TiempoInicio;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void RellenarBitmap(int x1, int y1, int x2, int y2);
void InicializarBitmap();


/****************************************************************************/
/****************************************************************************/
//
//    FUNCTION:  CSocket::Execute()
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
void __fastcall CSocket::Execute()
{
    int status, len = sizeof(SOCKADDR_IN);
    SOCKADDR_IN from;
    char buff[9000];

    while (!Terminated)
    {
        if (limpiarBuffer == false)
        {
            if (limpiarBufferRabbit == true)
            {
                limpiarBufferRabbit = false;
                nDatosRabbit = 0;
                pEscribirRabbit = 0;
                pLeerRabbit = 0;
            }
            if (limpiarBufferLX200 == true)
            {
                limpiarBufferLX200 = false;
                nDatosLX200 = 0;
                pEscribirLX200 = 0;
                pLeerLX200 = 0;
            }
            if (sock != INVALID_SOCKET)
            {
                status = recvfrom(sock, buff, 9000, NO_FLAGS_SET, (PSOCKADDR)&from, &len );
                if (status != SOCKET_ERROR)
                {
                    if (status > 0)
                    {
                        if (from.sin_addr.s_addr == inet_addr(cadenaIPRabbit))
                        {
                            ProcesarMensaje(buff, status);
                        }
                    }
                }
            }
        }
        else
        {
            nDatos = 0;
            pEscribir = 0;
            pLeer = 0;
            limpiarBuffer = false;
            nDatosRabbit = 0;
            pEscribirRabbit = 0;
            pLeerRabbit = 0;
            limpiarBufferRabbit = false;
            nDatosLX200 = 0;
            pEscribirLX200 = 0;
            pLeerLX200 = 0;
            limpiarBufferLX200 = false;
        }
    }
}

/****************************************************************************/
//
//    FUNCTION:  void __fastcall CSocket::ProcesarMensaje(char *buff, int tam)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
void __fastcall CSocket::ProcesarMensaje(char *buff, int tam)
{
    for (int cont = 0; cont < tam; cont++)
    {
        Datos[pEscribir] = buff[cont];
        nDatos++;
        pEscribir++;
        if (pEscribir >= TAMBUFF)
            pEscribir = 0;
    }
    if (buff[0] == M_Rabbit)      // Mensajes propios del Rabbit
    {
        MensajeRabbit(buff, tam);
    }
    else if (buff[0] == M_LX200) // Mensajes del LX200
    {
        MensajeLX200(buff, tam);
    }
    else if (buff[0] == M_CFS) // Mensajes del CFS
    {
        MensajeCFS(buff, tam);
    }

    else if (buff[0] == M_Camara) // Mensaje de la camara A
    {
        MensajeCamara(buff, tam);
    }
    else if (buff[0] == M_F_CamaraA) // Mensaje Fin Foto y tiempos camara A
    {
        MensajeF_CamaraA(buff, tam);
    }
    else if (buff[0] == M_CamaraB) // Mensaje de la camara B
    {
        MensajeCamara(buff, tam);    //falta separar la B
    }
    else if (buff[0] == M_F_CamaraB) // Mensaje Fin Foto y tiempos camara B
    {
        MensajeF_CamaraB(buff, tam);
    }
    else if (buff[0] == M_Terminal) // Mensajes de: Telescope Encoder & Sky Sensor   ????????
    {
        MensajeTESs(buff, tam);
    }
    else if (buff[0] == M_Meteo) // Mensajes de ??????????
    {
        MensajeMeteo(buff, tam);
    }
}

/****************************************************************************/
//
//    FUNCTION:  void __fastcall CSocket::MensajeRabbit(char *buff, int tam)
//
//    PURPOSE:   Atender el mensaje de presencia y status del COR
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
void __fastcall CSocket::MensajeRabbit(char *buff, int tam)
{
    if (strncmp(&buff[2], CadenaPresenciaRabbitInicio, strlen(CadenaPresenciaRabbitInicio)) == 0)
    {
        PerdidaConexion = true;
    }

    if (strncmp(&buff[2], CadenaPresenciaRabbit, strlen(CadenaPresenciaRabbit)) == 0)
    {
        TRabbit = ::GetTickCount();
        PerdidaConexion = false;
    }
    for (int cont = 2; cont < tam; cont++)
    {
        DatosRabbit[pEscribirRabbit] = buff[cont];
        nDatosRabbit++;
        pEscribirRabbit++;
        if (pEscribirRabbit >= TAMBUFF)
            pEscribirRabbit = 0;
    }

    Salidas   = buff[32];
    Grupos[0] = buff[33];
    Grupos[1] = buff[34];
    Grupos[2] = buff[35];
    Grupos[3] = buff[36];



    if (Form1->CBSelCamara->ItemIndex == 0)
    {
        TccdA = *(WORD*)&buff[37];
        TcajaA = *(WORD*)&buff[39];
        VpeltierA = *(WORD*)&buff[41];
    }
    else if (Form1->CBSelCamara->ItemIndex == 1)
    {
        TccdB = *(WORD*)&buff[37];
        TcajaB = *(WORD*)&buff[39];
        VpeltierB = *(WORD*)&buff[41];
    }

    Tccd = TccdA; // Tccd provisionalmente se usa en el objeto COM

}

/****************************************************************************/
//
//    FUNCTION:  void __fastcall CSocket::MensajeLX200(char *buff, int tam)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
extern TCustomWinSocket *Socket1;
void __fastcall CSocket::MensajeLX200(char *buff, int tam)
{

    AnsiString A;
    char *aux;

    aux = new char[tam];
    strncpy(aux, &buff[2], tam - 2);
    aux[tam - 2] = 0;
    if (Socket1 != NULL)
        Socket1->SendText(aux);  //Envio al puerto serie VIRTUAL
    //   Form1->Memo3->Lines->Add(aux);
    delete aux;
    for (int cont = 2; cont < tam; cont++)
    {
        DatosLX200[pEscribirLX200] = buff[cont];
        nDatosLX200++;
        pEscribirLX200++;
        if (pEscribirLX200 >= TAMBUFF)
            pEscribirLX200 = 0;
    }
}

/****************************************************************************/
//
//    FUNCTION:  void __fastcall CSocket::MensajeCFS(char *buff, int tam)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
void __fastcall CSocket::MensajeCFS(char *buff, int tam)
{
    for (int cont = 2; cont < tam; cont++)
    {
        DatosCFS[pEscribirCFS] = buff[cont];
        nDatosCFS++;
        pEscribirCFS++;
        if (pEscribirCFS >= TAMBUFF)
            pEscribirCFS = 0;
    }
}

/****************************************************************************/
//
//    FUNCTION:  void __fastcall CSocket::MensajeMeteo(char *buff, int tam)
//
//    PURPOSE:    Ir guardando lo recibido desde Meteo.
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
void __fastcall CSocket::MensajeMeteo(char *buff, int tam)
{
    for (int cont = 2; cont < tam; cont++)
    {
        DatosMeteo[pEscribirMeteo] = buff[cont];
        nDatosMeteo++;
        pEscribirMeteo++;
        if (pEscribirMeteo >= TAMBUFF)
            pEscribirMeteo = 0;

        //    Form1->PMeteo->Caption = buff;
    }
}


/****************************************************************************/
//
//    FUNCTION:  void __fastcall CSocket::MensajeTESs(char *buff, int tam)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
void __fastcall CSocket::MensajeTESs(char *buff, int tam)
{
    for (int cont = 2; cont < tam; cont++)
    {
        DatosTESs[pEscribirTESs] = buff[cont];
        nDatosTESs++;
        pEscribirTESs++;
        if (pEscribirTESs >= TAMBUFF)
            pEscribirTESs = 0;
    }
}



/****************************************************************************/
//    FUNCTION:  void __fastcall CSocket::MensajeCamara(char *buff, int tam)
//    PURPOSE:
//    COMMENTS:
//   ASSUMPTION:
/***************************************************************************/
/***************************************************************************/

void __fastcall CSocket::MensajeCamara(char *buff, int tam)
{
    int numeroLineas;
    int yy;
    unsigned short * ptr = (unsigned short*)&buff[8];
    int naux;

    numeroOrden  = *(WORD*)&buff[2] & 0x7FFF;


    numeroLineas = *(WORD*)&buff[4];
    if (numeroOrden < 2000)
    {
        naux = numeroOrden * numeroLineas;
        if (naux < 2000 - numeroLineas)
        {
            if ( LeyendoFoto == true)
            {
                if (Form1->CBimagen->ItemIndex != 3)
                    Form1->PCancel->Visible = false;

                for (int cl = 0; cl < numeroLineas; cl++)
                {
                    yy = (naux + cl + Y1FS) * FotoPrincipal->BM->Width;
                    for (int cw = X1FS; cw < X2FS; cw++)
                    {
                        if ((naux + cl + Y1FS) < Y2FS)
                        {
                            if (*ptr > 0x7FFF)
                                FotoPrincipal->Pixeles[yy + cw] = 0x7FFF;
                            else
                                FotoPrincipal->Pixeles[yy + cw] = *ptr;
                            if (cw > (X1FS + 2)) //evita la primera lectura que es invalida, y la segunda porsi acaso
                            {
                                if (*ptr > FotoPrincipal->maximo)
                                {
                                    FotoPrincipal->maximo = *ptr;
                                    FotoPrincipal->xmax = naux + cl + Y1FS;
                                    FotoPrincipal->ymax = cw;
                                }
                                if (*ptr < FotoPrincipal->minimo)
                                {
                                    FotoPrincipal->minimo = *ptr;
                                    FotoPrincipal->xmin = naux + cl + Y1FS;
                                    FotoPrincipal->ymin = cw;
                                }
                            }
                            ptr++;
                        }
                    }
                }
                numeroLinea = naux + numeroLineas + Y1FS;
                LineaNueva = true;

                //          TiempoUltimoPaquete = ::GetTickCount();
            }//if( LeyendoFoto == true)
        } // fin de  if(naux < 2000 - numeroLineas)
    } // fin de if(numeroOrden < 2000)

    if (numeroOrden != numeroOrdenAnterior)
        paquetesperdidos += (numeroOrden - numeroOrdenAnterior - 1);
    numeroOrdenAnterior = numeroOrden;

}


/****************************************************************************/
//    FUNCTION:  void __fastcall CSocket::MensajeF_CamaraA(char *buff, int tam)
//    PURPOSE:
/***************************************************************************/
void __fastcall CSocket::MensajeF_CamaraA(char *buff, int tam)
{
    FinFoto = true;
    A_FinFoto = true;
    A_T_Ini_Exp  = *(DWORD*)&buff[2];
    A_T_Ini_Lect = *(DWORD*)&buff[6];
    A_T_Fin_Lect = *(DWORD*)&buff[10];
    Form1->PCancel->Visible = true;
}

/****************************************************************************/
//    FUNCTION:  void __fastcall CSocket::MensajeF_CamaraB(char *buff, int tam)
//    PURPOSE:
/***************************************************************************/
void __fastcall CSocket::MensajeF_CamaraB(char *buff, int tam)
{
    FinFoto = true;
    B_FinFoto = true;
    B_T_Ini_Exp  = *(DWORD*)&buff[2];
    B_T_Ini_Lect = *(DWORD*)&buff[6];
    B_T_Fin_Lect = *(DWORD*)&buff[10];
    Form1->PCancel->Visible = true;
}





/****************************************************************************/
//
//    FUNCTION:  void __fastcall CSocket::ComprobarConexion(DWORD T)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
void __fastcall CSocket::ComprobarConexion(DWORD T)
{
    char aux[300];
    //  static DWORD kk = 0;

    if (PerdidaConexion == true)
    {
        if (T > TRabbit + 2000)
        {
            IniciarRabbit();
        }
    }
    else
    {
        if (T > TRabbit + 6000)
        {
            TRabbit = T;
            PerdidaConexion = True;
            IniciarRabbit();
        }
        if (T > TUltimoEnvio + 1000)
        {
            TUltimoEnvio = T;
            aux[0] = 0;
            strcpy(&aux[2], CadenaPresencia);
            Escribir(aux, strlen(CadenaPresencia) + 4, IPRabbit);
        }
    }
}

/****************************************************************************/
//
//    FUNCTION:  int __fastcall CSocket::Escribir(char *datos, int num, u_long direccion)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
int __fastcall CSocket::Escribir(char *datos, int num, u_long direccion)
{
    SOCKADDR_IN To;

    To.sin_family      = AF_INET;
    To.sin_addr.s_addr = direccion;
    To.sin_port        = htons(NumeroPuerto);

    return (Escribir(datos, num, To));
}

/****************************************************************************/
//
//    FUNCTION:  int __fastcall CSocket::Escribir(char *datos, int num, SOCKADDR_IN to)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
int __fastcall CSocket::Escribir(char *datos, int num, SOCKADDR_IN to)
{
    if (sock != INVALID_SOCKET)
    {
        if (Form1->CBonof->Checked == true)
            return (sendto( sock, datos, num, 0, (struct sockaddr FAR*)&to, sizeof(to)));
        else return 0;
    }
    else
        return SOCKET_ERROR;
}



/****************************************************************************/
//
//    FUNCTION:  int __fastcall CSocket::Escribir(char *datos, int num)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
int __fastcall CSocket::Escribir(char *datos, int num)
{
    SOCKADDR_IN To;

    To.sin_family      = AF_INET;
    To.sin_addr.s_addr = INADDR_BROADCAST;
    To.sin_port        = htons(NumeroPuerto);

    return (Escribir(datos, num, To));
}


/****************************************************************************/
/****************************************************************************/
//
//    FUNCTION:  CSocket:LimpiarBuffer()
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
/*void __fastcall CSocket::LimpiarBuffer()
{
  limpiarBuffer = true;
}
  */
/****************************************************************************/
/****************************************************************************/
//
//    FUNCTION:  CSocket:LimpiarBufferRabbit()
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
/*
void __fastcall CSocket::LimpiarBufferRabbit()
{
  limpiarBufferRabbit = true;
}
*/
/****************************************************************************/
/****************************************************************************/
//
//    FUNCTION:  CSocket:LimpiarBufferLX200()
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
void __fastcall CSocket::LimpiarBufferLX200()
{
    limpiarBufferLX200 = true;
}

/****************************************************************************/
/****************************************************************************/
//
//    FUNCTION:  CSocket:IniciarRabbit()
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
void __fastcall CSocket::IniciarRabbit()
{
    unsigned int cont1 = 0, cont2 = 0;
    char a[200];
    memset(a, 0x00, 200);

    a[0] = 0;
    a[1] = '\006';
    strcpy(cadenaIPRabbit, cadenaIP);
    while ((cont1 < strlen(cadenaIPRabbit)) && (cont2 < 3))
    {
        if (cadenaIPRabbit[cont1] == '.')
            cont2++;
        cont1++;
    }
    strcpy(&cadenaIPRabbit[cont1], Form1->Edit_IP->Text.c_str());
    //  strcpy(&cadenaIPRabbit[cont1], "99");
    strcpy(&a[2], cadenaIPRabbit);
    //  strcpy(&a[2], Form1->Edit_IP->Text.c_str());
    strcpy(&a[18], cadenaIP);
    strcpy(&a[34], Mascara);
    strcpy(&a[50], CadenaIdentificacion);

    IPRabbit = inet_addr (cadenaIPRabbit);

    Escribir(a, 102 + strlen(CadenaIdentificacion));
    TRabbit = ::GetTickCount();
}


/****************************************************************************/
/****************************************************************************/
//
//    FUNCTION:  CSocket:CSocket(u_short NPuerto, bool CreateSuspended )
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
__fastcall CSocket::CSocket(u_short NPuerto, bool CreateSuspended ): TThread(CreateSuspended)
{
    hostent *ph;
    int error;
    SOCKADDR_IN local_sin;
    int  status;
    unsigned long block = 1;
    int opt;
    char aux[3000];
    struct in_addr in;


    //  FotoPrincipal = new cFoto(NumeroFilas, NumeroColumnas, x0, y0);
    Priority = tpHigher;
    limpiarBuffer = limpiarBufferRabbit = limpiarBufferLX200 = false;
    pLeer = pEscribir = nDatos = 0;
    PerdidaConexion = true;
    strcpy(cadenaIPRabbit, "XXX.XXX.XXX.99");
    strcpy(Mascara, "255.255.255.0");
    if ((status = WSAStartup(0x0101, &WSAData)) != 0)
    {
        sprintf(aux, "%d is the err", status);
        Application->MessageBox( aux, "Error en inicialización de socket", MB_OK );
        exit(0);
    }
    NumeroPuerto = NPuerto;
    sock = INVALID_SOCKET;
    sock = socket( AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET)
    {
        Application->MessageBox("socket() failed", "Error", MB_OK);
        exit(0);
    }
    block = 0;
    if (ioctlsocket(sock, FIONBIO, &block))
    {
        sprintf(aux, "%d is the error", WSAGetLastError());
        Application->MessageBox(aux, "ioctl(sock) failed", MB_OK);
        closesocket( sock );
        exit(0);
    }
    opt = TRUE;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(int));
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(int));
    opt = 1000000;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF , (char*)&opt, sizeof(int)) != 0)
    {
        sprintf(aux, "%d is the error", WSAGetLastError());
        Application->MessageBox(aux, "setsockopt(sock) failed", MB_OK);
        closesocket( sock );
        exit(0);
    }
    error = gethostname(NombreHostLocal, 80);
    if (!error)
    {
        ph = gethostbyname(NombreHostLocal);
        if (ph != NULL)
        {
            IP = *(long*)ph->h_addr_list[0];
            in.s_addr = IP;
            //     Historico->Mhistory->Lines->Add("IP Acor: " + AnsiString(inet_ntoa(in)));
            strcpy(cadenaIP, inet_ntoa(in));
            if (ph->h_addr_list[1] != 0)
            {
                IP = *(long*)ph->h_addr_list[1];
                in.s_addr = IP;
                //     Historico->Mhistory->Lines->Add(inet_ntoa(in));
            }
        }
        else
        {
            IP = 0;
        }
    }
    else
    {
        IP = 0;
        strcpy(NombreHostLocal, "");
    }


    local_sin.sin_family      = AF_INET;
    local_sin.sin_addr.s_addr = INADDR_ANY;
    //  local_sin.sin_addr.s_addr = inet_addr("150.100.200.3");
    //  local_sin.sin_addr.s_addr = inet_addr("192.168.100.104");
    local_sin.sin_port        = htons(NumeroPuerto);

    if (bind( sock, (struct sockaddr FAR *) &local_sin, sizeof(local_sin)) == SOCKET_ERROR)
    {
        sprintf(aux, "%d is the error", WSAGetLastError());
        //Application->MessageBox(aux, "bind(sock) failed", MB_OK);
        closesocket( sock );
        exit(0);
    }
    Resume();
    IniciarRabbit();
}

/****************************************************************************/
/****************************************************************************/
//
//    FUNCTION:  CSocketTerminal::~CSocketTerminal
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
__fastcall CSocket::~CSocket()
{
    Terminate();
    closesocket(sock);
    delete FotoPrincipal;
}






/****************************************************************************/
//
//    FUNCTION:  int __fastcall CSocket::LeerRabbit(char *dat, int num)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
int __fastcall CSocket::LeerRabbit(char *dat, int num)
{
    if (nDatosRabbit > 0)
    {
        for (int cont = 0; cont < num; cont++)
        {
            dat[cont] = DatosRabbit[pLeerRabbit];
            pLeerRabbit++;
            if (pLeerRabbit >= TAMBUFF)
                pLeerRabbit = 0;
            nDatosRabbit--;
            if (nDatosRabbit == 0)
                return cont;
        }
        return num;
    }
    else
        return 0;
}


/****************************************************************************/
//
//    FUNCTION:  int __fastcall CSocket::LeerLX200(char *dat, int num)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
int __fastcall CSocket::LeerLX200(char *dat, int num)
{

    if (nDatosLX200 > 0)
    {
        for (int cont = 0; cont < num; cont++)
        {
            dat[cont] = DatosLX200[pLeerLX200];
            pLeerLX200++;
            if (pLeerLX200 >= TAMBUFF)
                pLeerLX200 = 0;
            nDatosLX200--;
            if (nDatosLX200 == 0)
                return cont;
        }
        return num;
    }
    else
        return 0;
}


/****************************************************************************/
//
//    FUNCTION:  int __fastcall CSocket::LeerTESs(char *dat, int num)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
int __fastcall CSocket::LeerTESs(char *dat, int num)
{

    if (nDatosTESs > 0)
    {
        for (int cont = 0; cont < num; cont++)
        {
            dat[cont] = DatosTESs[pLeerTESs];
            pLeerTESs++;
            if (pLeerTESs >= TAMBUFF)
                pLeerTESs = 0;
            nDatosTESs--;
            if (nDatosTESs == 0)
                return cont;
        }
        return num;
    }
    else
        return 0;
}



/****************************************************************************/
//
//    FUNCTION:  int __fastcall CSocket::LeerCFS(char *dat, int num)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
int __fastcall CSocket::LeerCFS(char *dat, int num)
{
    if (nDatosCFS > 0)
    {
        for (int cont = 0; cont < num; cont++)
        {
            dat[cont] = DatosCFS[pLeerCFS];
            pLeerCFS++;
            if (pLeerCFS >= TAMBUFF)
                pLeerCFS = 0;
            nDatosCFS--;
            if (nDatosCFS == 0)
                return cont;
        }
        return num;
    }
    else
        return 0;
}


int __fastcall CSocket::LeerMeteo(char *dat, int num)
{
    if (nDatosMeteo > 0)
    {
        for (int cont = 0; cont < num; cont++)
        {
            dat[cont] = DatosMeteo[pLeerMeteo];
            pLeerMeteo++;
            if (pLeerMeteo >= TAMBUFF)
                pLeerMeteo = 0;
            nDatosMeteo--;
            if (nDatosMeteo == 0)
                return cont;
        }
        return num;
    }
    else
        return 0;
}





/****************************************************************************/
//
//    FUNCTION:  int __fastcall CSocket::Leer(char *dat, int num)
//
//    PURPOSE:
//
//    COMMENTS:
//   ASSUMPTION:
//
//
/***************************************************************************/
/***************************************************************************/
int __fastcall CSocket::Leer(char *dat, int num)
{
    if (nDatos > 0)
    {
        for (int cont = 0; cont < num; cont++)
        {
            dat[cont] = Datos[pLeer];
            pLeer++;
            if (pLeer >= TAMBUFF)
                pLeer = 0;
            nDatos--;
            if (nDatos == 0)
                return cont;
        }
        return num;
    }
    else
        return 0;
}








