//---------------------------------------------------------------------------
#ifndef InteFormH
#define InteFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TIntegrForm : public TForm
{
__published:	// IDE-managed Components
        TMaskEdit *StartDateMEdit;
        TMaskEdit *StartTimeMEdit;
        TMaskEdit *EndDateMEdit;
        TMaskEdit *EndTimeMEdit;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TComboBox *ParamComboBox;
        TLabel *Label5;
        TButton *Button1;
        TUpDown *StartDateUpDown;
        TUpDown *EndDateUpDown;
        TUpDown *StartTimeUpDown;
        TUpDown *EndTimeUpDown;
        TLabel *ScaleLabel;
        TComboBox *ScaleComboBox;
        TRichEdit *RezRichEdit;
        TProgressBar *ProgressBar;
        TEdit *MinValEdit;
        TEdit *MaxValEdit;
        TLabel *Label6;
        TLabel *Label7;
        void __fastcall StartDateUpDownClick(TObject *Sender, TUDBtnType Button);
        void __fastcall StartTimeUpDownClick(TObject *Sender,
          TUDBtnType Button);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall MaxValEditDblClick(TObject *Sender);
        void __fastcall MinValEditDblClick(TObject *Sender);
private:	// User declarations
AnsiString Absent;
//unsigned short FMode;
//void __fastcall SetMode(unsigned  short Value);
public:		// User declarations
        __fastcall TIntegrForm(TComponent* Owner);
//__published:
//__property unsigned short Mode=(read=FMode,write=SetMode);
};
//---------------------------------------------------------------------------
extern PACKAGE TIntegrForm *IntegrForm;
//---------------------------------------------------------------------------
#endif
