//---------------------------------------------------------------------------

#ifndef EnfoqueH
#define EnfoqueH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
  TChart *HFD;
  TPanel *PDatosV;
  TFastLineSeries *Series2;
  TFastLineSeries *Series1;
        TFastLineSeries *Series3;
private:	// User declarations
public:		// User declarations
  __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
