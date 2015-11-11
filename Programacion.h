//---------------------------------------------------------------------------

#ifndef ProgramacionH
#define ProgramacionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFprog : public TForm
{
__published:	// IDE-managed Components
        TButton *BCarga;
        TLabel *LTdateTime;
    TLabel *lEstado;
        TTimer *Timer1;
        TButton *BParaAuto;
        TLabel *Label3;
        TButton *BGuardaXML;
        TMemo *Mver_rtml;
        TButton *BLeerFichXml;
        TOpenDialog *ODxml;
        TButton *BClear;
        TLabel *LJ2000;
        TLabel *LHSideral;
        TLabel *LAlturaInf;
        TLabel *LAlturaSup;
        TLabel *LAzimut1;
        TLabel *LAzimut2;
        TLabel *Label2;
        TEdit *EAlturaInf;
        TEdit *EAzimut1;
        TEdit *EAlturaSup;
        TEdit *EAzimut2;
        TLabel *LRestante;
        TLabel *LPending;
        TLabel *LmeteoSafe;
        void __fastcall BCargaClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall BParaAutoClick(TObject *Sender);
        void __fastcall BGuardaXMLClick(TObject *Sender);
        void __fastcall BLeerFichXmlClick(TObject *Sender);
        void __fastcall BFicheroXmlClick(TObject *Sender);
        void __fastcall BClearClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFprog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFprog *Fprog;
//---------------------------------------------------------------------------
#endif
