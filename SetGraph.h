//---------------------------------------------------------------------------
#ifndef SetGraphH
#define SetGraphH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include "Constant.h"
//---------------------------------------------------------------------------
class TSetPrnFo : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TEdit *AxisEdit;
        TLabel *Label1;
        TUpDown *AxisUpDown;
        TLabel *Label2;
        TEdit *GirdEdit;
        TUpDown *GirdUpDown;
        TLabel *Label3;
        TEdit *GraphEdit;
        TUpDown *GraphUpDown;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *LeftEdit;
        TEdit *TopEdit;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *WidthEdit;
        TEdit *HeightEdit;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TEdit *DPIEdit;
        TLabel *Label15;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TGroupBox *GroupBox3;
        TEdit *StepXEdit;
        TEdit *StepYEdit;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label19;
        TCheckBox *ColorCheckBox;
        TButton *ShowAxisButton;
        TButton *AddAxisButton;
        TButton *DelAxisButton;
        TCheckBox *PrintAllAxisCheckBox;
        void __fastcall AxisUpDownChanging(TObject *Sender,
          bool &AllowChange);
        void __fastcall GirdUpDownChanging(TObject *Sender,
          bool &AllowChange);
        void __fastcall GraphUpDownChanging(TObject *Sender,
          bool &AllowChange);
        void __fastcall ShowAxisButtonClick(TObject *Sender);
        void __fastcall AddAxisButtonClick(TObject *Sender);
        void __fastcall DelAxisButtonClick(TObject *Sender);
private:	// User declarations
public:
void SetEdit();		// User declarations
        __fastcall TSetPrnFo(TComponent* Owner);
int PrintedAxis[maxgraph];
};
//---------------------------------------------------------------------------
extern PACKAGE TSetPrnFo *SetPrnFo;
//---------------------------------------------------------------------------
#endif
