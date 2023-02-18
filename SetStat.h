//---------------------------------------------------------------------------
#ifndef SetStatH
#define SetStatH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cdiroutl.h"

#include <Grids.hpp>
#include <Outline.hpp>
#include <Mask.hpp>
#include <DBGrids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TSetBDForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TTabControl *TabControl;
        TLabel *Label1;
        TCheckBox *EnablCheckBox;
        TComboBox *dTimeComboBox;
        TCheckBox *TimeCheckBox;
        TMaskEdit *MaskEdit;
        TDBGrid *DBGrid;
        TPanel *Panel2;
        TSpeedButton *PreviewSButton;
        TCheckBox *CheckBox1;
        TComboBox *ParamComboBox;
        TBitBtn *OK;
        TBitBtn *Cansel;
        TComboBox *dAlarComboBox;
        TEdit *DiffEdit;
        TUpDown *DiffUpDown;
        TLabel *DiffLabel;
        TLabel *Label2;
        TSpeedButton *SpeedButton1;
        void __fastcall EnablCheckBoxClick(TObject *Sender);
        void __fastcall dTimeComboBoxChange(TObject *Sender);
        void __fastcall TimeCheckBoxClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall PreviewSButtonClick(TObject *Sender);
        void __fastcall PrintSButtonClick(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall ParamComboBoxChange(TObject *Sender);
        void __fastcall TabControlChange(TObject *Sender);
        void __fastcall dAlarComboBoxChange(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
float dTime;
float dAlarmTime;
AnsiString ParamSort,DateSort;
void NewMask(void);
void SetParamMask(void);
AnsiString AlarmName;
AnsiString ReservStatName;
AnsiString StatistName;
void FillSheet(TTable* Table,Variant& Cells);
int LastIndex;
        __fastcall TSetBDForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSetBDForm *SetBDForm;
//---------------------------------------------------------------------------
#endif
