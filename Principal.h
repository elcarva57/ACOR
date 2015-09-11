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
    TPageControl *PageControl1;
    TTabSheet *CAMARA;
    TPanel *Panel11;
    TPanel *PShuter;
    TPanel *PFiltro;
    TTabSheet *CUPULA;
    TPanel *Panel12;
    TLabel *Label18;
    TSpeedButton *SpeedButton1;
    TPanel *P1;
    TShape *Sbit8;
    TSpeedButton *bit8;
    TPanel *Panel14;
    TShape *Sbit7;
    TSpeedButton *bit7;
    TPanel *Panel15;
    TShape *Sbit6;
    TSpeedButton *bit6;
    TPanel *Panel16;
    TShape *Sbit5;
    TSpeedButton *bit5;
    TPanel *Panel17;
    TShape *Sbit4;
    TSpeedButton *bit4;
    TPanel *Panel18;
    TShape *Sbit3;
    TSpeedButton *bit3;
    TPanel *Panel19;
    TShape *Sbit2;
    TSpeedButton *bit2;
    TPanel *Panel20;
    TShape *Sbit1;
    TSpeedButton *bit1;
    TPanel *Panel21;
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
    TTabSheet *TELESCOPIO;
    TTabSheet *CONFIGURACION;
    TTabSheet *VISUALIZACION;
    TPanel *Panel53;
    TDrawGrid *DG2;
    TPanel *Panel54;
    TBitBtn *BAbrir;
    TBitBtn *BGuardar;
    TPanel *Panel7;
    TScrollBox *PFotoO;
    TPaintBox *PB1;
    TOpenDialog *OD1;
    TSaveDialog *SD1;
    TImageList *ImageList1;
    TTimer *Timer1;
    TPanel *Panel60;
    TLabel *Label52;
    TEdit *ELimpiado;
    TLabel *Label47;
    TEdit *ERetraso;
    TPanel *Panel8;
    TLabel *Label55;
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
    TCheckBox *CBPintar;
    TLabel *Label62;
    TLabel *Label63;
    TLabel *Label64;
    TLabel *Label65;
    TLabel *Label66;
    TLabel *Label67;
    TLabel *Label68;
    TLabel *Label69;
    TLabel *Label70;
    TLabel *Label71;
    TLabel *Label72;
    TPanel *Panel62;
    TPanel *Panel57;
    TEdit *EFilaInicioA;
    TEdit *EColumnaInicioA;
    TEdit *EFilaFinA;
    TEdit *EColumnaFinA;
    TLabel *Label20;
    TDrawGrid *DG1;
    TPanel *Panel52;
    TEdit *ELocation;
    TEdit *EObserver;
    TLabel *Label76;
    TPanel *Panel55;
    TLabel *Label9;
    TLabel *Label75;
    TRadioButton *RBH;
    TRadioButton *RBD;
    TPanel *PFicheroAbierto;
    TPanel *Panel63;
    TPanel *Panel5;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label56;
    TEdit *ENombreFichero;
    TStaticText *TNFotos;
    TCheckBox *CBGuardar;
    TEdit *EObjeto;
    TPanel *Panel51;
    TPanel *PFoto;
    TImage *IFoto;
    TShape *SLedFoto;
    TPanel *PCancel;
    TProgressBar *PBF;
    TLabel *Label17;
    TEdit *Esg;
    TEdit *Emsg;
    TLabel *Label16;
    TPanel *TiempoPasado;
    TLabel *Label78;
    TLabel *Label79;
    TComboBox *CBCCD_A;
    TPanel *Panel4;
    TPanel *Panel10;
    TLabel *Label84;
    TPanel *Panel64;
    TStaticText *STRa;
    TStaticText *STDe;
    TPanel *Panel65;
    TLabel *Label46;
    TLabel *Label10;
    TLabel *Label82;
    TLabel *Label86;
    TLabel *Label87;
    TPanel *Panel66;
    TButton *Bstop;
    TMaskEdit *EHra;
    TMaskEdit *EMra;
    TMaskEdit *EDdec;
    TMaskEdit *EMdec;
    TStaticText *stSign;
    TBitBtn *bbGo;
    TLabel *Label89;
    TStaticText *arecta;
    TStaticText *declinacion;
    TPanel *Panel68;
    TSpeedButton *BNO;
    TSpeedButton *BN;
    TSpeedButton *BNE;
    TSpeedButton *BE;
    TSpeedButton *BSE;
    TSpeedButton *BS;
    TSpeedButton *BSO;
    TSpeedButton *BO;
    TPanel *Panel69;
    TSpeedButton *BSLW;
    TSpeedButton *BMOV;
    TSpeedButton *BCEN;
    TSpeedButton *BGUI;
    TPanel *Panel70;
    TTabSheet *TSEnfoque;
    TLabel *Label61;
    TMemo *Memo1;
    TUpDown *UDNFotos;
    TEdit *ENFotos;
    TPanel *PCFS;
    TLabel *Label60;
    TButton *BFlipx;
    TButton *BFlipy;
    TPanel *Panel2;
    TComboBox *CBEnviar;
    TBitBtn *BEnviar;
    TLabel *Label73;
    TEdit *EComent;
    TButton *BResetFoco;
    TRadioButton *RBStreching;
    TTimer *Timer2;
    TPanel *Panel67;
    TLabel *Label90;
    TStaticText *STPerdido;
    TServerSocket *ServerSocket1;
    TTimer *Timer3;
    TEdit *ETelescop;
    TEdit *EFocal;
    TEdit *EInstrument;
    TEdit *EApert;
    TEdit *ELatitud;
    TEdit *ELongitud;
    TComboBox *CBimagen;
    TUpDown *UpDown1;
    TLabel *Label43;
    TLabel *Label39;
    TLabel *Label8;
    TTrackBar *TBBinin;
    TPanel *PBinin;
    TCheckBox *CBT;
    TComboBox *CBSelCamara;
    TLabel *Label77;
    TTimer *Timer4;
    TPanel *Panel27;
    TPanel *PPerdidos;
    TLabel *Label59;
    TLabel *Label58;
    TButton *BGuardaConfig;
    TLabel *Label41;
    TEdit *Edit_IP;
    TButton *BcambiaIP;
    TPanel *PHOST;
    TPanel *PRABBIT;
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
    TLabel *Label80;
    TEdit *ETiempoEntreFotos;
    TCheckBox *CBRectangulo;
    TLabel *Label34;
    TLabel *Label50;
    TCheckBox *CBFlipHorizontal;
    TCheckBox *CBFlipVertical;
    TEdit *ESegAdj;
    TCheckBox *CBonof;
    TLabel *Label91;
    TDirectoryListBox *DirectoryListBox1;
    TButton *Button2;
    TEdit *EEnviar_cfs;
    TButton *Button1;
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
    TLabel *Label93;
    TPanel *PLuzR;
    TLabel *Label94;
    TPanel *PBarometro;
    TLabel *Label95;
    TLabel *Label96;
    TCheckBox *CBWeb;
    TLabel *Label19;
    TPanel *PLuzUV;
    TButton *BCalibrarMeteo;
    TPanel *Panel1;
    TPanel *PTcajaA;
    TLabel *Label53;
    TLabel *Label54;
    TPanel *PVpeltierA;
    TButton *BPeltierA;
    TEdit *EVpelt_manA;
    TLabel *Label81;
    TEdit *EAdj_ccdA;
    TUpDown *UpDadj_ccdA;
    TCheckBox *CBregularTA;
    TLabel *Label51;
    TPanel *PTccdA;
    TLabel *Label22;
    TPanel *Panel26;
    TButton *BPeltierB;
    TEdit *EVpelt_manB;
    TLabel *Label21;
    TEdit *EAdj_ccdB;
    TUpDown *UpDadj_ccdB;
    TCheckBox *CBregularTB;
    TLabel *Label23;
    TLabel *Label24;
    TPanel *PTccdB;
    TLabel *Label25;
    TPanel *PTcajaB;
    TLabel *Label74;
    TPanel *PVpeltierB;
    TButton *BHistoria;
    TCheckBox *CBHistoriaMeteo;
    TLabel *Label11;
    TComboBox *CBCCD_B;
    TLabel *Label42;
    TLabel *Label92;
    TEdit *EColumnaInicioB;
    TEdit *EFilaInicioB;
    TLabel *Label97;
    TEdit *EFilaFinB;
    TEdit *EColumnaFinB;
    TLabel *Label98;
    TSpeedButton *SBstop;
    TPanel *Panel9;
    TPanel *PTecho;
    TPanel *PCalentar;
    TLabel *Label40;
    TButton *Button3;
    TLabel *Label99;
    TPanel *PBarometroAbs;
    TTimer *Timer5;
    TLabel *Label100;
    TLabel *Label101;
    TPanel *PCFS2;
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
    TTimer *Timer6;
    TCheckBox *CBcfs_log;
    TEdit *EVelocidadEnfoque;
    TEdit *EPasosEnfoque;
    TCheckBox *CBhfd;
    TButton *Brtml;
    TEdit *ELXsend;
    TButton *BSendLX;
    TCheckBox *CBver_envio_lx;
    TLabel *LAzimut;
    TLabel *LAltura;
    TLabel *LAlturaRx;
    TLabel *LAzimutRx;
    TLabel *Label83;
    TLabel *PerRefreco;
    TEdit *PerRefresco;
    TLabel *Label105;
    TLabel *LRAgrados;
    TLabel *LDecgrados;
    TBitBtn *BBAbrirObs;
    TLabel *Lemav2;
    TWeather *Weather1;
    TPanel *Panel29;
    TLabel *LDECtes;
    TLabel *LARtes;
    TLabel *Label104;
    TLabel *LAltTess;
    TLabel *LAzTess;
    TLabel *Label106;
    TPanel *Panel58;
    TLabel *Label85;
    TCheckBox *CBSincronizar;
    TButton *BElbrus;
    TTabSheet *TabSheet1;
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
    TLabel *LHoraSideral;
    TPanel *Panel30;
    TShape *SC;
    TPanel *PStatus;
    TSkysensor *Skysensor1;
    TLabel *LmvTess;
    TLabel *LTcieloTess;
    TLabel *LTambTess;
    TCheckBox *CBCGEM;
    TCheckBox *cbPrecision;
    TMaskEdit *ESra;
    TMaskEdit *ESdec;
    void __fastcall Timer1Timer(TObject *Sender);
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
    void __fastcall Timer2Timer(TObject *Sender);
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
    void __fastcall Timer3Timer(TObject *Sender);
    void __fastcall UpDown1ChangingEx(TObject *Sender,
                                      bool &AllowChange, short NewValue, TUpDownDirection Direction);
    void __fastcall CBimagenChange(TObject *Sender);
    void __fastcall Timer4Timer(TObject *Sender);
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
    void __fastcall Timer5Timer(TObject *Sender);
    void __fastcall BVergrafClick(TObject *Sender);
    void __fastcall BGetBFPClick(TObject *Sender);
    void __fastcall BAutoEnfoqueClick(TObject *Sender);
    void __fastcall Timer6Timer(TObject *Sender);
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
