//---------------------------------------------------------------------------

#ifndef PrincipalH
#define PrincipalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <ImgList.hpp>
#include <Mask.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPServer.hpp>
#include <ScktComp.hpp>
#include <FileCtrl.hpp>

#include <OleServer.hpp>
#include "ema_OCX.h"
#include "Test_OCX.h"
//#include "ema_OCX.h"
//#include "Test_OCX.h"


//---------------------------------------------------------------------------

class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel7;
    TScrollBox *PFotoO;
    TPaintBox *PB1;
    TOpenDialog *OD1;
    TSaveDialog *SD1;
    TImageList *ImageList1;
    TTimer *Timer50;
    TPanel *Panel56;
    TPanel *Panel49;
    TLabel *Label1;
    TLabel *Label44;
    TLabel *Label45;
    TPanel *PP;
    TPanel *PY;
    TPanel *PX;
    TPanel *Panel59;
    TLabel *Label4;
    TLabel *Label6;
    TLabel *Label5;
    TLabel *Label7;
    TLabel *Label57;
    TPanel *PX1;
    TPanel *PX2;
    TPanel *PY1;
    TPanel *PY2;
    TLabel *Label61;
    TMemo *Memo1;
    TTimer *Timer60000;
    TServerSocket *ServerSocket1;
    TTimer *Timer3000;
    TTimer *Timer100;
    TPanel *Panel27;
    TPanel *PPerdidos;
    TLabel *Label59;
    TLabel *Label58;
    TLabel *Label14;
    TPanel *PMax;
    TLabel *Label15;
    TPanel *PMin;
    TPanel *PRecuadro;
    TPanel *Panel6;
    TLabel *Label12;
    TLabel *Label13;
    TEdit *Ex0;
    TEdit *Ey0;
    TTrackBar *TBy0;
    TTrackBar *TBx0;
    TEdit *estirar_alto;
    TCheckBox *CBautostrech;
    TEdit *estirar_bajo;
    TButton *BHistoria;
    TButton *Button3;
    TTimer *Timer5000;
    TTimer *Timer1000;
    TWeather *Weather1;
    TLabel *LHoraSideral;
    TShape *SC;
    TPanel *PStatus;
    TSkysensor *Skysensor1;
    TPageControl *PageControl1;
    TTabSheet *CAMARA;
    TPanel *Panel11;
    TLabel *Label62;
    TLabel *Label60;
    TLabel *Label43;
    TPanel *PShuter;
    TPanel *PFiltro;
    TPanel *PCFS;
    TButton *BResetFoco;
    TButton *Button2;
    TEdit *EEnviar_cfs;
    TButton *Button1;
    TPanel *Panel61;
    TLabel *Label48;
    TLabel *Label49;
    TLabel *Label35;
    TLabel *Label36;
    TLabel *Label88;
    TButton *subir;
    TButton *bajar;
    TPanel *PContador;
    TMaskEdit *MEEstabilizar;
    TButton *BInitCalibration;
    TCheckBox *CBAutoEnfoque;
    TButton *BVergraf;
    TButton *BGetBFP;
    TButton *BAutoEnfoque;
    TEdit *EVelocidadEnfoque;
    TEdit *EPasosEnfoque;
    TCheckBox *CBhfd;
    TCheckBox *CBcfs_log;
    TPanel *Panel63;
    TPanel *Panel5;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label56;
    TLabel *Label17;
    TLabel *Label16;
    TLabel *Label39;
    TLabel *Label8;
    TLabel *Label77;
    TLabel *Label80;
    TEdit *ENombreFichero;
    TStaticText *TNFotos;
    TCheckBox *CBGuardar;
    TEdit *EObjeto;
    TEdit *Esg;
    TEdit *Emsg;
    TPanel *TiempoPasado;
    TUpDown *UDNFotos;
    TEdit *ENFotos;
    TComboBox *CBimagen;
    TUpDown *UpDown1;
    TTrackBar *TBBinin;
    TPanel *PBinin;
    TCheckBox *CBT;
    TComboBox *CBSelCamara;
    TEdit *ETiempoEntreFotos;
    TCheckBox *CBRectangulo;
    TCheckBox *CBWeb;
    TPanel *Panel51;
    TPanel *PFoto;
    TImage *IFoto;
    TShape *SLedFoto;
    TPanel *PCancel;
    TProgressBar *PBF;
    TButton *Brtml;
    TTabSheet *TELESCOPIO;
    TPanel *Panel4;
    TPanel *Panel64;
    TLabel *Label86;
    TLabel *Label87;
    TLabel *LAzimut;
    TLabel *LAltura;
    TLabel *LAlturaRx;
    TLabel *LAzimutRx;
    TLabel *Label83;
    TLabel *LRAgrados;
    TLabel *LDecgrados;
    TLabel *Label106;
    TStaticText *STRa;
    TStaticText *STDe;
    TPanel *Panel65;
    TLabel *Label46;
    TLabel *Label10;
    TLabel *Label82;
    TStaticText *arecta;
    TStaticText *declinacion;
    TPanel *Panel70;
    TPanel *Panel29;
    TLabel *LDECtes;
    TLabel *LARtes;
    TLabel *Label104;
    TLabel *LAltTess;
    TLabel *LAzTess;
    TLabel *LmvTess;
    TLabel *LTcieloTess;
    TLabel *LTambTess;
    TPanel *Panel10;
    TLabel *Label84;
    TLabel *PerRefreco;
    TLabel *Label105;
    TPanel *Panel66;
    TLabel *Label89;
    TLabel *Label100;
    TLabel *Label101;
    TButton *Bstop;
    TMaskEdit *EHra;
    TMaskEdit *EMra;
    TMaskEdit *EDdec;
    TMaskEdit *EMdec;
    TStaticText *stSign;
    TBitBtn *bbGo;
    TMaskEdit *ESra;
    TMaskEdit *ESdec;
    TPanel *Panel68;
    TSpeedButton *BNO;
    TSpeedButton *BN;
    TSpeedButton *BNE;
    TSpeedButton *BE;
    TSpeedButton *BSE;
    TSpeedButton *BS;
    TSpeedButton *BSO;
    TSpeedButton *BO;
    TSpeedButton *SBstop;
    TPanel *Panel69;
    TSpeedButton *BSLW;
    TSpeedButton *BMOV;
    TSpeedButton *BCEN;
    TSpeedButton *BGUI;
    TEdit *ELXsend;
    TButton *BSendLX;
    TCheckBox *CBver_envio_lx;
    TEdit *PerRefresco;
    TPanel *Panel58;
    TLabel *Label85;
    TCheckBox *CBSincronizar;
    TButton *BElbrus;
    TPanel *Panel67;
    TLabel *Label90;
    TStaticText *STPerdido;
    TCheckBox *CBCGEM;
    TCheckBox *cbPrecision;
    TTabSheet *CUPULA;
    TPanel *Panel12;
    TLabel *Label18;
    TSpeedButton *SpeedButton1;
    TPanel *P1;
    TLabel *Label72;
    TShape *Sbit8;
    TSpeedButton *bit8;
    TPanel *Panel14;
    TLabel *Label71;
    TShape *Sbit7;
    TSpeedButton *bit7;
    TPanel *Panel15;
    TLabel *Label70;
    TShape *Sbit6;
    TSpeedButton *bit6;
    TPanel *Panel16;
    TLabel *Label69;
    TShape *Sbit5;
    TSpeedButton *bit5;
    TPanel *Panel17;
    TLabel *Label68;
    TShape *Sbit4;
    TSpeedButton *bit4;
    TPanel *Panel18;
    TLabel *Label67;
    TShape *Sbit3;
    TSpeedButton *bit3;
    TLabel *Label66;
    TPanel *Panel19;
    TLabel *Label65;
    TShape *Sbit2;
    TSpeedButton *bit2;
    TPanel *Panel20;
    TLabel *Label64;
    TShape *Sbit1;
    TSpeedButton *bit1;
    TPanel *Panel21;
    TLabel *Label20;
    TPanel *Panel47;
    TPanel *Panel25;
    TShape *ss6;
    TLabel *LSensor6;
    TPanel *Panel24;
    TShape *ss5;
    TLabel *LSensor5;
    TPanel *Panel23;
    TShape *ss4;
    TLabel *LSensor4;
    TPanel *Panel22;
    TShape *ss3;
    TLabel *LSensor3;
    TPanel *Panel13;
    TShape *ss2;
    TLabel *LSensor2;
    TPanel *Panel33;
    TShape *ss1;
    TLabel *LSensor1;
    TPanel *Panel8;
    TLabel *Label63;
    TLabel *Label96;
    TEdit *ESegAdj;
    TPanel *Panel1;
    TLabel *Label53;
    TLabel *Label54;
    TLabel *Label81;
    TLabel *Label51;
    TLabel *Label22;
    TPanel *PTcajaA;
    TPanel *PVpeltierA;
    TButton *BPeltierA;
    TEdit *EVpelt_manA;
    TEdit *EAdj_ccdA;
    TUpDown *UpDadj_ccdA;
    TCheckBox *CBregularTA;
    TPanel *PTccdA;
    TPanel *Panel26;
    TLabel *Label21;
    TLabel *Label23;
    TLabel *Label24;
    TLabel *Label25;
    TLabel *Label74;
    TButton *BPeltierB;
    TEdit *EVpelt_manB;
    TEdit *EAdj_ccdB;
    TUpDown *UpDadj_ccdB;
    TCheckBox *CBregularTB;
    TPanel *PTccdB;
    TPanel *PTcajaB;
    TPanel *PVpeltierB;
    TPanel *PCFS2;
    TTabSheet *VISUALIZACION;
    TPanel *Panel53;
    TDrawGrid *DG2;
    TDrawGrid *DG1;
    TPanel *Panel55;
    TLabel *Label9;
    TLabel *Label75;
    TRadioButton *RBH;
    TRadioButton *RBD;
    TButton *BFlipx;
    TButton *BFlipy;
    TRadioButton *RBStreching;
    TPanel *Panel54;
    TLabel *Label55;
    TBitBtn *BAbrir;
    TBitBtn *BGuardar;
    TPanel *PFicheroAbierto;
    TTabSheet *CONFIGURACION;
    TPanel *Panel60;
    TLabel *Label52;
    TLabel *Label47;
    TEdit *ELimpiado;
    TEdit *ERetraso;
    TCheckBox *CBPintar;
    TPanel *Panel62;
    TPanel *Panel57;
    TLabel *Label78;
    TLabel *Label79;
    TLabel *Label73;
    TLabel *Label34;
    TLabel *Label50;
    TLabel *Label11;
    TLabel *Label42;
    TLabel *Label92;
    TLabel *Label97;
    TLabel *Label98;
    TEdit *EFilaInicioA;
    TEdit *EColumnaInicioA;
    TEdit *EFilaFinA;
    TEdit *EColumnaFinA;
    TComboBox *CBCCD_A;
    TComboBox *CBCCD_B;
    TEdit *EColumnaInicioB;
    TEdit *EFilaInicioB;
    TEdit *EFilaFinB;
    TEdit *EColumnaFinB;
    TPanel *Panel52;
    TLabel *Label76;
    TEdit *ELocation;
    TEdit *EObserver;
    TEdit *EComent;
    TEdit *ETelescop;
    TEdit *EFocal;
    TEdit *EInstrument;
    TEdit *EApert;
    TEdit *ELatitud;
    TEdit *ELongitud;
    TCheckBox *CBFlipHorizontal;
    TCheckBox *CBFlipVertical;
    TDirectoryListBox *DirectoryListBox1;
    TPanel *Panel2;
    TLabel *Label41;
    TLabel *Label91;
    TComboBox *CBEnviar;
    TBitBtn *BEnviar;
    TEdit *Edit_IP;
    TButton *BcambiaIP;
    TPanel *PHOST;
    TPanel *PRABBIT;
    TCheckBox *CBonof;
    TButton *BGuardaConfig;
    TTabSheet *TSEnfoque;
    TPanel *Panel3;
    TLabel *Label26;
    TLabel *Label27;
    TLabel *Label28;
    TLabel *Label29;
    TLabel *Label30;
    TLabel *Label31;
    TLabel *Label32;
    TLabel *Label33;
    TLabel *Label37;
    TLabel *Label38;
    TLabel *Label93;
    TLabel *Label94;
    TLabel *Label95;
    TLabel *Label19;
    TLabel *Label99;
    TLabel *Lemav2;
    TPanel *PTempAmbiente;
    TPanel *PHumedad;
    TPanel *PPuntoRocio;
    TPanel *PDirViento;
    TPanel *PVelViento;
    TPanel *PLluvia;
    TPanel *PNublados;
    TPanel *PPluviometro;
    TButton *BGraficas;
    TPanel *PvelOmni;
    TPanel *PVFuente;
    TPanel *PDirNSEO;
    TPanel *PLuzR;
    TPanel *PBarometro;
    TPanel *PLuzUV;
    TButton *BCalibrarMeteo;
    TCheckBox *CBHistoriaMeteo;
    TPanel *Panel9;
    TLabel *Label40;
    TPanel *PTecho;
    TPanel *PCalentar;
    TBitBtn *BBAbrirObs;
    TPanel *PBarometroAbs;
    TTabSheet *tsElbrus;
    TPanel *Panel28;
    TLabel *PLDeriva;
    TLabel *LDifCoord;
    TLabel *Label102;
    TLabel *Label103;
    TButton *BDerivaAqui;
    TButton *BrecentrarAR;
    TButton *BrecentrarDEC;
    TEdit *EGuiadoDecWest;
    TEdit *EGuiadoDecimasSgDec;
    TCheckBox *CBrecentrar;
    TCheckBox *CBcalibrar;
    TEdit *EGuiadoCalAR;
    TEdit *EGuiadoCalDec;
    TCheckBox *CBnorte;
    TCheckBox *CBsur;
    TEdit *EGuiadoDecEste;
    TCheckBox *CBProporcional;
    TEdit *EFijo;
    TPanel *Panel30;
    TTabSheet *tsCGEM;
    TGroupBox *gbTimePos;
    TEdit *eUTC;
    TEdit *eLocal;
    TCheckBox *cbDST;
    TEdit *eOffset;
    TButton *bLocal;
    TButton *bUTC;
    TButton *bPos;
    TUpDown *upOffset;
    TGroupBox *gbTracking;
    TRadioGroup *rgTracking;
    TGroupBox *gbMisc;
    TRadioGroup *rgDevice;
    TButton *bEcho;
    TEdit *eEcho;
    TButton *bAlign;
    TButton *bGotoProg;
    TButton *bCancelGoto;
    TButton *bGetModel;
    TEdit *eModel;
    TButton *bGetDeviceVer;
    TEdit *eDeviceVer;
    TButton *bGetTrack;
    TCheckBox *cbAligned;
    TCheckBox *cbGotoProg;
    TEdit *eCancelGoto;
    TButton *bGetPosition;
    TEdit *eGetPosition;
    TButton *bGetTime;
    TEdit *eGetTime;
    TButton *bTest;
    TCheckBox *cbDisableAllTimers;
    TTimer *t100Slew;
    void __fastcall Timer50Timer(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall BEnviarClick(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall TBBininChange(TObject *Sender);
    void __fastcall LConfigurarClick(TObject *Sender);
    void __fastcall BAbrirClick(TObject *Sender);
    void __fastcall BGuardarClick(TObject *Sender);
    void __fastcall TBx0Change(TObject *Sender);
    void __fastcall PCancelMouseDown(TObject *Sender, TMouseButton Button,
                                     TShiftState Shift, int X, int Y);
    void __fastcall PCancelMouseUp(TObject *Sender, TMouseButton Button,
                                   TShiftState Shift, int X, int Y);
    void __fastcall PB1Paint(TObject *Sender);
    void __fastcall RBHClick(TObject *Sender);
    void __fastcall CBCCD_A_Change(TObject *Sender);
    void __fastcall CBCCD_B_Change(TObject *Sender);
    void __fastcall CBGuardarClick(TObject *Sender);
    void __fastcall EFilaFinAChange(TObject *Sender);
    void __fastcall subirClick(TObject *Sender);
    void __fastcall bajarClick(TObject *Sender);
    void __fastcall BstopClick(TObject *Sender);
    void __fastcall BOClick(TObject *Sender);
    void __fastcall BSMouseDown(TObject *Sender, TMouseButton Button,
                                TShiftState Shift, int X, int Y);
    void __fastcall BNOMouseUp(TObject *Sender, TMouseButton Button,
                               TShiftState Shift, int X, int Y);
    void __fastcall stSignClick(TObject *Sender);
    void __fastcall bbGoClick(TObject *Sender);
    void __fastcall PB1Click(TObject *Sender);
    void __fastcall BFlipxClick(TObject *Sender);
    void __fastcall DG2DrawCell(TObject *Sender, int ACol, int ARow,
                                TRect &Rect, TGridDrawState State);
    void __fastcall BFlipyClick(TObject *Sender);
    //  void __fastcall Button1Click(TObject *Sender);
    void __fastcall BResetFocoClick(TObject *Sender);
    void __fastcall Timer60000Timer(TObject *Sender);
    void __fastcall BGraficasClick(TObject *Sender);
    //       void __fastcall BPonerHcorClick(TObject *Sender);
    void __fastcall ServerSocket1Accept(TObject *Sender,
                                        TCustomWinSocket *Socket);
    void __fastcall ServerSocket1ClientDisconnect(TObject *Sender,
            TCustomWinSocket *Socket);
    void __fastcall ServerSocket1ClientError(TObject *Sender,
            TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
            int &ErrorCode);
    void __fastcall ServerSocket1ClientRead(TObject *Sender,
                                            TCustomWinSocket *Socket);
    void __fastcall BcambiaIPClick(TObject *Sender);
    void __fastcall BGuardaConfigClick(TObject *Sender);
    void __fastcall EColumnaFinAChange(TObject *Sender);
    void __fastcall Timer3000Timer(TObject *Sender);
    void __fastcall UpDown1ChangingEx(TObject *Sender,
                                      bool &AllowChange, short NewValue, TUpDownDirection Direction);
    void __fastcall CBimagenChange(TObject *Sender);
    void __fastcall Timer100Timer(TObject *Sender);
    void __fastcall DirectoryListBox1Change(TObject *Sender);

    void __fastcall BFotoEnfocarClick(TObject *Sender);

    void __fastcall BIniCalClick(TObject *Sender);

    void __fastcall IFotoMouseDown(TObject *Sender, TMouseButton Button,
                                   TShiftState Shift, int X, int Y);
    void __fastcall PB1MouseDown(TObject *Sender, TMouseButton Button,
                                 TShiftState Shift, int X, int Y);
    void __fastcall PB1MouseMove(TObject *Sender, TShiftState Shift, int X,
                                 int Y);
    void __fastcall PB1MouseUp(TObject *Sender, TMouseButton Button,
                               TShiftState Shift, int X, int Y);
    void __fastcall BPeltierAClick(TObject *Sender);
    void __fastcall BPeltierBClick(TObject *Sender);
    void __fastcall BElbrusClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall CBSelCamaraChange(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall BInitCalibrationClick(TObject *Sender);
    void __fastcall BCalibrarMeteoClick(TObject *Sender);
    void __fastcall BHistoriaClick(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Timer5000Timer(TObject *Sender);
    void __fastcall BVergrafClick(TObject *Sender);
    void __fastcall BGetBFPClick(TObject *Sender);
    void __fastcall BAutoEnfoqueClick(TObject *Sender);
    void __fastcall Timer1000Timer(TObject *Sender);
    void __fastcall BDerivaAquiClick(TObject *Sender);
    void __fastcall EPasosEnfoqueChange(TObject *Sender);
    void __fastcall EVelocidadEnfoqueChange(TObject *Sender);
    void __fastcall BrecentrarARClick(TObject *Sender);
    void __fastcall BrtmlClick(TObject *Sender);
    void __fastcall BrecentrarDECClick(TObject *Sender);
    void __fastcall BSendLXClick(TObject *Sender);
    void __fastcall BBAbrirObsClick(TObject *Sender);
    void __fastcall CBCGEMClick(TObject *Sender);
    void __fastcall MaskEditChange(TObject *Sender);
    void __fastcall EHraChange(TObject *Sender);
    void __fastcall EDdecChange(TObject *Sender);
    void __fastcall CBSincronizarClick(TObject *Sender);
    void __fastcall tsCGEMShow(TObject *Sender);
    void __fastcall bUTCClick(TObject *Sender);
    void __fastcall bLocalClick(TObject *Sender);
    void __fastcall bPosClick(TObject *Sender);
    void __fastcall rgTrackingClick(TObject *Sender);
    void __fastcall bGetDeviceVerClick(TObject *Sender);
    void __fastcall bSendSingleCommandClick(TObject *Sender);
    void __fastcall rgDeviceClick(TObject *Sender);
    void __fastcall bEchoClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall bTestClick(TObject *Sender);
    void __fastcall cbDisableAllTimersClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
    //  void __fastcall Repintar();
    //  void __fastcall pb1Repintar();
    void __fastcall printerror( int status);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------

extern char SalidaCom[];
#endif
