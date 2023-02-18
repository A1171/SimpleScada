//---------------------------------------------------------------------------
#ifndef GraphH
#define GraphH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "MainUnut.h"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Menus.hpp>
#include "Function.h"
//#define maxpoint 12000
//---------------------------------------------------------------------------
class TGraphForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TColorDialog *ColorDialog;
        TTrackBar *TrackBar;
        TLabel *MinLabel;
        TLabel *MaxLabel;
        TLabel *ValueLabel;
        TMaskEdit *MaskEdit1;
        TLabel *Label1;
        TBitBtn *BitBtn1;
        TMaskEdit *MaskEdit;
        TLabel *Label2;
        TUpDown *UpDown1;
        TUpDown *UpDown2;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *AddItem;
        TMenuItem *DelItem;
        TMenuItem *SetupItem;
        TMenuItem *N5;
        TMenuItem *N2;
        TMenuItem *AllOnOneItem;
        TMenuItem *EachOnSingleItem;
        TMenuItem *SelectedGroupItem;
        TMenuItem *EachInGroupOnSingleItem;
        TMenuItem *AddGroupItem;
        TMenuItem *DeleteGroupItem;
        TMenuItem *RenameGroupItem;
        TMenuItem *EachGroupOnSingleItem;
        TTabControl *TabControl;
        TScrollBox *ScrollBox1;
        TPaintBox *PaintBox;
        TPanel *Panel2;
        TPaintBox *PaintBox1;
        TPanel *TypePanel;
        TSpeedButton *StandartSButton;
        TSpeedButton *AlarmSButton;
        void __fastcall PaintBoxPaint(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall AddBitBtnClick(TObject *Sender);
        void __fastcall TrackBarChange(TObject *Sender);
        void __fastcall TrackBarExit(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall DelBitBtnClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        //void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall Panel2MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall PaintBox1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PaintBox1Paint(TObject *Sender);
        void __fastcall StandartSButtonClick(TObject *Sender);
        void __fastcall SetupItemClick(TObject *Sender);
        void __fastcall AllOnOneItemClick(TObject *Sender);
        void __fastcall UpDown2Click(TObject *Sender, TUDBtnType Button);
        void __fastcall DeleteGroupItemClick(TObject *Sender);
        void __fastcall AddGroupItemClick(TObject *Sender);
        void __fastcall RenameGroupItemClick(TObject *Sender);
        void __fastcall TabControlChange(TObject *Sender);
private:	// User declarations
bool SettingsChanged;
//Function read values from database and filled array elements
public:		// User declarations
void SaveToIniFile(TIniFile*);
void ReadFromIniFile(TIniFile*);
//TPaintBox* Printer(void);
//If TabNumb==-1 will be selected active tab 
void InitialPoints(short);
inline void Act(float& Value1,float& Value2,TActionType& Action);
int StepX,StepY;
//float Min[maxadam][maxchannel];
class TGraphicInfo
{
public:
float Max;
unsigned int Signal;
TColor Color;
void Clear(){Max=0;Signal=-1;Color=0;}
TGraphicInfo(){Clear();}
void ReadFile(TIniFile*,AnsiString,unsigned short);
void WriteFile(TIniFile*,AnsiString,unsigned short);
bool PresentInFile(TIniFile*,AnsiString,unsigned short);
TGraphicInfo& operator=(const TGraphicInfo& Res){Max=Res.Max;Signal=Res.Signal;Color=Res.Color;}

};
//-------------------------------------------------------------------------------
TGraphicInfo Graphics[maxgraphgroup][maxgraph];
//float Max[maxgraph][maxgraphgroup];
//int Graphics[maxgraph][maxgraphgroup];
int PrintedAxis[maxgraph];
//TColor GraphColor[maxgraph][maxgraphgroup];
struct TArrayPointer
{
TArrayPointer(){Array=0;Size=0;Max=1;}
~TArrayPointer(){if(Array)delete[]Array;Array=0;}
short* Array;
unsigned int Size;
short Max;//MaxValue of each element
};
struct TFloatArrayPointer
{
TFloatArrayPointer(){Array=0;Size=0;Max=1;}
~TFloatArrayPointer(){if(Array)delete[]Array;Array=0;}
float* Array;
unsigned int Size;
float Max;//MaxValue of each element
};
//function taked values from Table and filled array for parametr
inline bool CheckAndFilter(TTable *Table,unsigned short Parametr);
void FillArray(TArrayPointer* Array,TTable *Table,unsigned short Parametr);
void FillArray(TFloatArrayPointer* Array,TTable *Table,unsigned short Parametr);
void PaintGraphI(const TRect* Rect,TCanvas* Canv,unsigned int Numb,TColor Color,int& EndPoint);
void FillAxisArray(TArrayPointer &Array,TArrayPointer &Axis);
void PaintGird(const TRect* Rect,TCanvas* Canv,TArrayPointer* Array,int BetweenAxis,int StepXP,int StepYP,int RealWidth);
TArrayPointer GraphPoint[maxgraph];
//TArrayPointer TimePoint[maxgraph];
//TDifArray<short int>* GraphPoint;//[maxgraph];
//TDifArray<short int>* TimePoint;//[maxgraph];
//short int* GraphPoint[maxgraph];
//unsigned
//short int* TimePoint[maxgraph];
//short int MaxPoint[maxgraph];
int TimeScale;
TDateTime SelectMinDate,SelectMaxDate;
AnsiString DateFilter;
bool EnablSaveData;
int DPI,GirdWidth,AxisWidth,GraphWidth;
int PListLeft,PListTop,PListWidth,PListHeight;
bool PanelVis;
bool AllBlack;
int ViewScale;
        __fastcall TGraphForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGraphForm *GraphForm;
//---------------------------------------------------------------------------
#endif
