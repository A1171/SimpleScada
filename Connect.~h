//---------------------------------------------------------------------------
#ifndef ConnectH
#define ConnectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "Function.h"
//---------------------------------------------------------------------------
class TFormOfConnect : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TStringGrid *ParamGrid;
        TPanel *Panel2;
        TComboBox *FieldComboBox;
        TComboBox *ComboBox2;
        void __fastcall ParamGridClick(TObject *Sender);
private:	// User declarations
bool FOnlyPhisic,FOnlySaved;
void __fastcall SetOnlyPhisic(bool Value){FOnlyPhisic=Value;RefreshForm();}
void __fastcall SetOnlySaved(bool Value){FOnlySaved=Value;RefreshForm();}
void __fastcall FindParametr(unsigned int);
void __fastcall FindField(const TInpType&);
unsigned int __fastcall GetParametr();
TInpType __fastcall GetField();
public:		// User declarations
void RefreshForm();
        __fastcall TFormOfConnect(TComponent* Owner);
__published:
__property unsigned int Signal={read=GetParametr,write=FindParametr};
__property TInpType SignalField={read=GetField,write=FindField};
__property bool OnlyPhisic={read=FOnlyPhisic,write=SetOnlyPhisic};
__property bool OnlySaved={read=FOnlySaved,write=SetOnlySaved};
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOfConnect *FormOfConnect;
//---------------------------------------------------------------------------
#endif
