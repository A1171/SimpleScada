//---------------------------------------------------------------------------
#ifndef MainUnutH
#define MainUnutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <MPlayer.hpp>
//#include <Assert.h>
#include "Chaild.h"
#include "Functions.h"
#include "IOThread.h"
#include "ReThread.h"
#include "Constant.h"
#include "DataUnit.h"
#include "Graph.h"
#include <MPlayer.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
//AnsiString ProgramDir;
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *ShaxtMenu;
        TOpenDialog *OpenDialog;
        TMenuItem *N11;
        TMenuItem *N21;
        TMenuItem *Window;
        TMenuItem *TileItem;
        TMenuItem *CascadeItem;
        TMenuItem *ArrangeIItem;
        TMenuItem *SetItem;
        TMenuItem *MoveItem;
        TMenuItem *GraphItem;
        TMenuItem *N2;
        TMenuItem *N4;
        TMenuItem *N5;
        TStatusBar *StatusBar;
        TTimer *Timer1;
        TMenuItem *SavaAsItem;
        TMenuItem *LoadItem;
        TMenuItem *N6;
        TSaveDialog *SaveDialog;
        TTimer *DataBaseTimer;
        TMediaPlayer *MediaPlayer;
        TPrintDialog *PrintDialog;
        TMenuItem *SetGraphItem;
        TMenuItem *GrapherItem;
        TMenuItem *OffSignals;
        TMenuItem *AllVisible;
        TTimer *AlarmTimer;
        TMenuItem *N7;
        TMenuItem *SatAdrItem;
        TTimer *CheckSignalTimer;
        TButton *Button1;
        TEdit *Edit1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TEdit *Edit2;
        TButton *Button5;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *N10;
        TMenuItem *N12;
        TButton *SetRtsBtn;
        TButton *ClrRtsBtn;
        TButton *SetDtrBtn;
        TButton *ClrDtrBtn;
        TMenuItem *NewItem;
        TButton *SaveDataButton;
        TMenuItem *WorkTimeItem;
        void __fastcall ShaxtMenuClick(TObject *Sender);
        void __fastcall TileItemClick(TObject *Sender);
        void __fastcall CascadeItemClick(TObject *Sender);
        void __fastcall ArrangeIItemClick(TObject *Sender);
        void __fastcall SetItemClick(TObject *Sender);
        void __fastcall GraphItemClick(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall MoveItemClick(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall SavaAsItemClick(TObject *Sender);
        void __fastcall LoadItemClick(TObject *Sender);
        void __fastcall DataBaseTimerTimer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall SetGraphItemClick(TObject *Sender);
        void __fastcall GrapherItemClick(TObject *Sender);
        void __fastcall OffSignalsClick(TObject *Sender);
        void __fastcall AllVisibleClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall AlarmTimerTimer(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        void __fastcall SatAdrItemClick(TObject *Sender);
        void __fastcall CheckSignalTimerTimer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall N9Click(TObject *Sender);
        void __fastcall N10Click(TObject *Sender);
        void __fastcall N12Click(TObject *Sender);
        void __fastcall SetRtsBtnClick(TObject *Sender);
        void __fastcall ClrRtsBtnClick(TObject *Sender);
        void __fastcall SetDtrBtnClick(TObject *Sender);
        void __fastcall ClrDtrBtnClick(TObject *Sender);
        void __fastcall NewItemClick(TObject *Sender);
        void __fastcall SaveDataButtonClick(TObject *Sender);
        void __fastcall IntegItemClick(TObject *Sender);
        void __fastcall WorkTimeItemClick(TObject *Sender);
private:	// User declarations
bool FPaused;
void __fastcall SetPaused(bool);
struct TState
{
bool SaveData,SaveAlarm,CheckSignal;
bool ChForm[ChCount];
TState(){SaveData=false;SaveAlarm=false;CheckSignal=false;}
}State;
//AnsiString FCaption[maxadam][maxchannel];
//AnsiString __fastcall GetCaption(unsigned int Ind1,unsigned int Ind2){return FCaption[Ind1][Ind2];}
//void __fastcall SetCaption(unsigned int Ind1,unsigned int Ind2,AnsiString Value){FCaption[Ind1][Ind2]=Value;}
//This function compare argument to different means of writing Yes word
//bool CompareToYes(AnsiString);
void __fastcall ViewAlarm();
void AddSound(AnsiString A);
//void Sound();
void __fastcall CheckSignals();//‘ункци€ сравнени€ сигналов с допу-
//стимыми в параметры передаютс€ номер адама и канала. ¬ ответ она заполн€ет массив
//критических сигналов CritSignal дл€ адама и канала, ƒописывает аварийную строку
//ParamName и запускает звук
//char ComName[6];
//char *PComName;
//char Message[6];
//char *PMessage;
//char Respond[10];
//char *PRespond;
//unsigned long BytesWritten,BytesReaden,Errors;
//HANDLE PortHandle;
//TDCB DCB;
//COMSTAT Stat;
//_COMMTIMEOUTS TimeOutSt;
public:
unsigned short MDIChildType[ChCount];//1-ChildForm
//bool TerminateMy;//This flag from TAdConnThread as quest to terminate it
//bool PresentThread;
//TAdConnThread *Thread;
//----------------------------------------------------------------------------
Set<int,0,maxgroup>SetGroupIndex;
AnsiString ParamName;
AnsiString AlarmMessage;//Current file name
AnsiString OrderOfPlay[SoundBuffer];//Buffer of file to play
bool EnableAddSound;//Indicate add or not file to buffer
//bool SomeAlarm;
int MaxSoundNumber;//Indicate fine element of buffer
int Counter[maxadam][maxchannel];//Counter used for wating for normal signal
//bool CritSignals[maxadam][maxchannel];//Array of crytic signals
//----------------------------------------------------------------------------

TRefreshThread *ReThread;
bool OnlyOperate;//Show operate or no ReThread Today

void __fastcall InitialAlarmArray();//initialisation of MinAlarm,,, arrays
void SaveAlarmFunc();
AnsiString ProgramDir;
int SaveFrequenty;//Save Stat
int SaveAlarmFreq;//Save Alarm
int AlarmDiff;
int DataDiff;//When differences between past and present value increase this value parametr saved
//in database
bool EnablDrag;
bool EnablPopUp;
bool EnablSaveData;//Enable save data Stat to Stat database
int PrintedAxis[maxgraph];
bool PrintAllAxis;
//bool EnablSmooth[maxadam][maxchannel];//Enable smoothing input values
//bool PresentSmooth[maxadam][maxchannel];//Indicate present of smooth object
//short int SmoothArraySize;
//TSmooth *SmoothObject[maxadam][maxchannel];

bool SaveAlarm;//Enable Save data to Alarm database
bool EnableSaveAlarm;//Save alarm(prom flag)
bool GraphPresent;//Present of Graf form
TForm  *Graph;
//float Signal[maxadam][maxchannel];//Signals in each moment of time
//float PreviousSignal[maxadam][maxchannel];//{Value of signals at the last moment when
//each signal hase been saved in database}
//TDateTime PreviousTime[maxadam][maxchannel];//Last time when signal hase been saved
//float PrevCritSignal[maxadam][maxchannel];//{Value of signals at the last moment when
//each signal hase been saved in alarm database}
//TDateTime PrevCritTime[maxadam][maxchannel];//{Last time when signal hase been saved
//in alarm database}
//Indicate or no about parametr
//bool MaxAlarm[maxadam][maxchannel];
//bool MinAlarm[maxadam][maxchannel];
//bool TopAlarm[maxadam][maxchannel];
//bool BottomAlarm[maxadam][maxchannel];
//bool Alarm[maxadam][maxchannel];//Indicated present of alarm for all channels;
//DataBase in memory
//float Min[maxadam][maxchannel];//Min value of all param
//float Max[maxadam][maxchannel];//Max value of all param
//float MinAl[maxadam][maxchannel];//Value of min alarm
//float MaxAl[maxadam][maxchannel];//Value of max alarm
//float Scales[maxadam][maxchannel];//Scale factor for all channels
//float OffSet[maxadam][maxchannel];//Offset for all channels
//bool SaveData[maxadam][maxchannel];//Indicate save or no data about this channel in database
//AnsiString EdIzm[maxadam][maxchannel];//EdIzm field
//AnsiString SoundMin[maxadam][maxchannel];
//AnsiString SoundMax[maxadam][maxchannel];
//AnsiString SoundTop[maxadam][maxchannel];
//AnsiString SoundBottom[maxadam][maxchannel];
//Ќазвани€ параметров
AnsiString MessageByIndex[maxgroup];//Messages for each of index
//int Number[maxadam][maxchannel];//Number field(order number)
//int GroupIndex[maxadam][maxchannel];//Index for select by group
//bool PresentParam[maxadam][maxchannel];//Indicate present or no parametr
//
char Adres[maxadam][2];//Adres of Adams from ini file
//Set<int,0,maxadam>SetsAd;//ћножество критич адамов
//Set<int,0,maxadam>SetsChan;//ћножество критич каналов
bool OnSignal[maxadam][maxchannel];//¬ременно приостановленные сигналы
int GirdWidth,AxisWidth,GraphWidth;//Width of lines for print
int ListLeft,ListTop,ListWidth,ListHeight;//Print parametr
int DPI,StepX,StepY;
bool AllBlack;//Paint all grafics as black
AnsiString PromCaption;
//TFanForm *FanForm;
//bool FanPresent;
//bool ExistForm[maxform];
//ChildForm *      Forms[maxform];
		// User declarations
        __fastcall TMainForm(TComponent* Owner);
__published:
//__property AnsiString ParamCaptions[unsigned int Ind1][unsigned int Ind2]=
//{read=GetCaption,write=SetCaption};
__property bool Paused={read=FPaused,write=SetPaused};
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//extern PACKAGE TDataModule1* DataModule1;
//extern PACKAGE AnsiString ProgDir;
//---------------------------------------------------------------------------
#endif
 