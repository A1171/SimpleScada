//---------------------------------------------------------------------------
#ifndef GrapherH
#define GrapherH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "Inifiles.hpp"
#define maxStore 1200
//---------------------------------------------------------------------------
class TGrapherForm : public TForm
{
__published:	// IDE-managed Components
        TPaintBox *PaintBox;
        TButton *AddObjectItem;
        TTimer *Timer1;
        TPopupMenu *PopupMenu;
        TMenuItem *ConnectItem;
        TMenuItem *ScalesItem;
        TComboBox *ComboBox;
        TButton *OkButton;
        TLabel *Label1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall PaintBoxPaint(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall ConnectItemClick(TObject *Sender);
        void __fastcall ScalesItemClick(TObject *Sender);
        void __fastcall OkButtonClick(TObject *Sender);
        //__property int Type={read=FType,write=FType};
private:	// User declarations
//int FType;
public:
void SaveToIniFile(TIniFile*,AnsiString);
void LoadFromIniFile(TIniFile*,AnsiString);
int Type;		// User declarations
int SignalNumber;//Adam,Channel;
float Max;
float Value[maxStore];
int Delenie;
int Number;
        __fastcall TGrapherForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGrapherForm *GrapherForm;
//---------------------------------------------------------------------------
#endif
