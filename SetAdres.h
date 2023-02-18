//---------------------------------------------------------------------------
#ifndef SetAdresH
#define SetAdresH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAdrForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TEdit *AdNoEdit;
        TUpDown *AdrUpDown;
        TLabel *Label2;
        TEdit *AdrEdit;
        TGroupBox *GroupBox2;
        TLabel *Label3;
        TEdit *IndNoEdit;
        TUpDown *IndUpDown;
        TLabel *Label4;
        TEdit *MessageEdit;
        void __fastcall AdrUpDownClick(TObject *Sender, TUDBtnType Button);
        void __fastcall IndUpDownClick(TObject *Sender, TUDBtnType Button);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
bool CheckAndSave(int);
public:		// User declarations
        __fastcall TAdrForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAdrForm *AdrForm;
//---------------------------------------------------------------------------
#endif
