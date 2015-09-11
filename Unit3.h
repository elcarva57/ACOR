//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
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
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFGraficas : public TForm
{
__published:	// IDE-managed Components
  TChart *Chart1;
  TChart *Chart2;
  TChart *Chart3;
  TChart *Chart4;
        TFastLineSeries *Series4;
        TFastLineSeries *Series6;
        TPanel *Panel2;
        TButton *Button1;
        TFastLineSeries *Series7;
        TFastLineSeries *Series2;
        TFastLineSeries *AreaSeries1;
        TFastLineSeries *Series1;
  TFastLineSeries *Series3;
  TFastLineSeries *Series8;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
        TFastLineSeries *AreaSeries2;
  TChart *Chart5;
  TFastLineSeries *Series5;
  TFastLineSeries *Series9;
  TFastLineSeries *SeriesBarometro;
  TFastLineSeries *Series10;
  TFastLineSeries *Series11;
  void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFGraficas(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFGraficas *FGraficas;
//---------------------------------------------------------------------------
#endif
