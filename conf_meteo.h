//---------------------------------------------------------------------------

#ifndef conf_meteoH
#define conf_meteoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TFConfigMeteo : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel3;
  TPanel *PFechaConf;
  TButton *BAjustes_Meteo;
  TPanel *Panel2;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
  TLabel *Label13;
  TEdit *EKPluvio;
  TEdit *EOffset_Bar;
  TEdit *EAltura_Bar;
  TEdit *EOffset_IR;
  TEdit *EOffset_UV;
  TEdit *EKAnem_mec;
  TPanel *Panel1;
  TLabel *Label7;
  TLabel *Label8;
  TLabel *Label9;
  TLabel *Label10;
  TLabel *Label11;
  TLabel *Label12;
  TLabel *Label14;
  TLabel *Label15;
  TButton *BCalAnemT;
  TEdit *Ezener1;
  TEdit *Ezener2;
  TEdit *Ezener3;
  TEdit *Ezener4;
  TEdit *Ezener5;
  TEdit *Ezener6;
  TEdit *EK1Anem_term;
  TEdit *EK2Anem_term;
  TPanel *Panel4;
  TEdit *EDirectorio;
  TButton *BOkDirectorio;
  TLabel *Label17;
  TLabel *Label18;
  TEdit *Ejpg;
  TPanel *Panel5;
  TButton *BSendMeteo;
  TEdit *EEnvMeteo;
  TPanel *Panel6;
  TLabel *Label6;
  TEdit *ELimiteLluvia;
  TLabel *Label20;
  TEdit *ELimiteNubes;
  TLabel *Label21;
  TEdit *ELimiteFuente;
  TLabel *Label22;
  TEdit *ELimiteEspera;
  TLabel *Label23;
  TEdit *ELimiteRocio;
  TLabel *Label24;
  TEdit *ELimiteKmh;
  TLabel *Label25;
  TLabel *Label26;
  TLabel *Label27;
  TButton *BGrabar;
  TButton *BLeer;
  TButton *BAjuste_Meteo_Flash;
  TEdit *EPuerto;
  TLabel *Label16;
  TButton *BSalir;
  TLabel *Label19;
  TCheckBox *CBGuardarJPG;
  void __fastcall BCalAnemTClick(TObject *Sender);
  void __fastcall BAjustes_MeteoClick(TObject *Sender);
  void __fastcall BOkDirectorioClick(TObject *Sender);
  void __fastcall BSalirClick(TObject *Sender);
  void __fastcall BSendMeteoClick(TObject *Sender);
  void __fastcall BGrabarClick(TObject *Sender);
  void __fastcall BLeerClick(TObject *Sender);
  void __fastcall BAjuste_Meteo_FlashClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFConfigMeteo(TComponent* Owner);
};

void LeerNivelesMeteo(void);
//---------------------------------------------------------------------------
//extern PACKAGE TFConfigMeteo *FConfigMeteo;
//---------------------------------------------------------------------------
#endif
