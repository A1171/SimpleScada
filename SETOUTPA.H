//---------------------------------------------------------------------------
#ifndef SetOutPaH
#define SetOutPaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TSetOutParamForm : public TForm
{
__published:	// IDE-managed Components
        TTrackBar *TrackBar1;
        TEdit *IntEdit;
        TEdit *FactionalEdit;
        TLabel *MinLabel1;
        TLabel *MaxLabel1;
        TLabel *Label1;
        TLabel *Label2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TLabel *ValueLabel1;
        TTrackBar *TrackBar2;
        TLabel *MinLabel2;
        TLabel *MaxLabel2;
        TLabel *ValueLabel2;
        TLabel *Label3;
        TLabel *Label4;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:
float Scale;		// User declarations
        __fastcall TSetOutParamForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSetOutParamForm *SetOutParamForm;
//---------------------------------------------------------------------------
#endif
