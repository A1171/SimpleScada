//---------------------------------------------------------------------------
#ifndef FunctionsH
#define FunctionsH
#include <Extctrls.hpp>
#include "Constant.h"
#include "Inifiles.hpp"
#define maxframe 10
//--------------------------------------------------------------------------
template <class T>
inline bool CheckMax(const T& Value){T Value1=Value+1;return Value1==0;}
void CopyToReserve();
void RefreshStat();
void RefreshAlarm();
float TransformStr(AnsiString,bool&);
AnsiString TransformFloat(float);
void Pause(int);
bool GetName(TControl*,AnsiString&);
enum TObjectType {otOwner,otEdit,otLevel,otIndicat,otPict,otClip,otMyButton};
enum TBtnAction {baNotDefine,baCallForm};
//Type of signal represented by object of this class Inp- it is an input signal object
//that resive signal from external device, Calc - it is a calculated signal that calculated
//on the basis of other signals, Out -it is a out signal that out to external device
enum TSignalType{stInp=0,stCalc=1,stOut=2};
//for calc (and out) type of signals it is a type of fewnumbofsignal) input signals on what basis calculating
//this signal.
enum TInpType{itNotDefine=0,itFloat=1,itInp=2,itCalc=3,itOut=4,itIntPtoc=5};
//subtype of few(numbofsignal) input signals characterizes from what field of input signal taked value
//enum TInpSubType{sstNotDefine=0,sstInpField=1,sstCalcField=2,sstOutField=3};
//characterizes ariphmetic action between input signals that should be doing between input signals
enum TActionType{atNotDefine=0,atAdd=1,atSub=2,atMul=3,atDiv=4,atAnd=5,atOr=6,atAndNot=7,atOrNot=8};
//---------------------------------------------------------------------------

class TIndicat: public TPaintBox
{
private:
TObjectType FType;
//int FAdam,FChannel;
TColor FAroundColor;
float FMax,FInput;
int FNumber;
void __fastcall SetMax(float);
void __fastcall SetInput(float);
void __fastcall SetAround(TColor a){FAroundColor=a;Invalidate();}
void __fastcall Paint();
protected:
public:
unsigned int Signal;
TInpType SignalField;
void Operate(void);
void Prepare(void);
void SaveToIniFile(TIniFile*,AnsiString);
void LoadFromIniFile(TIniFile*,AnsiString);
        __fastcall TIndicat(TComponent* Owner);
__published:
__property float Max={read=FMax,write=SetMax,default=100};
__property float Input={read=FInput,write=SetInput,default=0};
__property TColor AroundColor={read=FAroundColor,write=SetAround,default=clBlack};
__property TObjectType Type={read=FType};
__property int Number={read=FNumber,write=FNumber,default=0};
//__property int Adam={read=FAdam,write=FAdam,default=1};
//__property int Channel={read=FChannel,write=FChannel};
};
AnsiString TransformFloat(float var);
float TransformStr(AnsiString Str);
class TLevel: public TPaintBox
{
private:
TObjectType FType;
TColor FAroundColor;
TColor FLevelColor;
//int FAdam,FChannel;
float FMax,FInput;
int FNumber;
void __fastcall SetMax(float);
void __fastcall SetInput(float);
void __fastcall SetAround(TColor);
void __fastcall SetFull(TColor);
void __fastcall Paint();
protected:
public:
unsigned int Signal;
TInpType SignalField;
void Operate(void);
void Prepare(void);
void SaveToIniFile(TIniFile*,AnsiString);
void LoadFromIniFile(TIniFile*,AnsiString);
        __fastcall TLevel(TComponent* Owner);
__published:
__property float Max={read=FMax,write=SetMax,default=100};
__property float Input={read=FInput,write=SetInput,default=0};
__property TColor AroundColor={read=FAroundColor,write=SetAround,default=clBlack};
__property TColor LevelColor={read=FLevelColor,write=SetFull,default=clGreen};
__property TObjectType Type={read=FType};
__property int Number={read=FNumber,write=FNumber,default=0};
//__property int Adam={read=FAdam,write=FAdam,default=1};
//__property int Channel={read=FChannel,write=FChannel};
};
class TEdit1:public TEdit
{
private:
TObjectType FType;
//int FAdam,FChannel;
int FNumber;
int FInt,FFactional;
TColor FBackGroundColor;
//bool FAlarm;
bool FRed;
protected:
public:
unsigned int Signal;
TInpType SignalField;
void SaveToIniFile(TIniFile*,AnsiString);
void LoadFromIniFile(TIniFile*,AnsiString);
void Operate(void);
        __fastcall TEdit1(TComponent* Owner);
__published:
__property TObjectType Type={read=FType};
__property int Number={read=FNumber,write=FNumber};
//__property int Adam={read=FAdam,write=FAdam,default=1};
//__property int Channel={read=FChannel,write=FChannel};
__property int Int={read=FInt,write=FInt};
__property int Factional={read=FFactional,write=FFactional,default=1};
//__property bool Alarm={read=FAlarm,write=FAlarm,default=false};
};
class TImage1:public TImage
{
private:
TObjectType FType;
//int FAdam,FChannel;
int FNumber;
float FSwitchLess,FSwitchMore;
AnsiString FImag;
//bool FSterch;
protected:
public:
unsigned int Signal;
TInpType SignalField;
void SaveToIniFile(TIniFile*,AnsiString);
void LoadFromIniFile(TIniFile*,AnsiString);
void Operate(void);
void Prepare(void);
void Retur(void);
        __fastcall TImage1(TComponent* Owner);
__published:
__property TObjectType Type={read=FType};
__property int Number={read=FNumber,write=FNumber};
//__property int Adam={read=FAdam,write=FAdam,default=1};
//__property int Channel={read=FChannel,write=FChannel};
__property float SwitchingLess={read=FSwitchLess,write=FSwitchLess};
__property float SwitchingMore={read=FSwitchMore,write=FSwitchMore};
__property AnsiString Imag={read=FImag,write=FImag};
//__property bool Sterch={read=FSterch,write=FSterch};
};
//----------------------------------------------------------------------------
class TMyButton:public TBitBtn
{
private:
TObjectType FType;
//int FAdam,FChannel;
int FNumber;
TBtnAction FAction;
AnsiString FAssociateForm;
void __fastcall BitBtn1Click(TObject *Sender);
protected:
public:
unsigned int Signal;
TInpType SignalField;
void SaveToIniFile(TIniFile*,AnsiString);
void LoadFromIniFile(TIniFile*,AnsiString);
//void Operate(void);
void Prepare(void);
void Retur(void);
        __fastcall TMyButton(TComponent* Owner);
__published:
__property TObjectType Type={read=FType};
__property int Number={read=FNumber,write=FNumber};
//__property int Adam={read=FAdam,write=FAdam,default=1};
//__property int Channel={read=FChannel,write=FChannel};
__property TBtnAction Action={read=FAction,write=FAction};
__property AnsiString AssociateForm={read=FAssociateForm,write=FAssociateForm};
};
//----------------------------------------------------------------------------
class TClip:public TImage
{
private:
TObjectType FType;
//int FAdam,FChannel;
int FNumber;
float FSwitchLess,FSwitchMore;
AnsiString FImag[maxframe];//Whole paths stored in this array 
int FMaxFrame;
Graphics::TBitmap *Bitm;
HDC hdcFrame[maxframe];
HDC LastHandle;
//TImage *Frame[maxframe];
bool PresentFrame[maxframe];
void __fastcall SetImag(int Index,AnsiString Value);
AnsiString __fastcall GetImag(int Index);
int FCurrentFrame;
protected:
public:
unsigned int Signal;
TInpType SignalField;
void SaveToIniFile(TIniFile*,AnsiString);
void LoadFromIniFile(TIniFile*,AnsiString);
void Operate(void);
void Prepare(void);
void Retur(void);
void SetFrame(int);
        __fastcall TClip(TComponent* Owner);
        __fastcall ~TClip(/*TComponent* Owner*/);

__published:
__property TObjectType Type={read=FType};
__property int Number={read=FNumber,write=FNumber};
//__property int Adam={read=FAdam,write=FAdam,default=1};
//__property int Channel={read=FChannel,write=FChannel};
__property float SwitchingLess={read=FSwitchLess,write=FSwitchLess};
__property float SwitchingMore={read=FSwitchMore,write=FSwitchMore};
__property int MaxFrame={read=FMaxFrame,write=FMaxFrame};
__property AnsiString Imag[int Index]={read=GetImag,write=SetImag};
__property int CurrentFrame={read=FCurrentFrame,write=FCurrentFrame};
};
//--------------------------------------------------------------------
class TSmooth:public TObject
{
private:
bool OnlyRecorded;
short int FPointer;
float FValue;
float *FArray;
int FArraySize;
void __fastcall SetValue(float);
void __fastcall SetArraySize(int);
protected:
public:
__fastcall TSmooth(int StartMax);//:TObject();
__fastcall ~TSmooth();
__published:
__property float Value={read=FValue,write=SetValue};
__property int ArraySize={read=FArraySize,write=SetArraySize};
};
//--------------------------------------------------------------------

class TDataConteiner:public TObject
{
public:
struct TInputDevice
 {
 TInputDevice(){Port=-1;Device-1;Channel=-1;SingleDevice=true;}
 unsigned int Port:8;
 unsigned int Device:8;
 unsigned int Channel:8;
 bool SingleDevice;
 }InputDevice;
struct TLimits
 {
 float Min,Max,MinAlarm,MaxAlarm;
 }Limits;

unsigned int Number;
AnsiString Name,EdIzm,SoundMin,SoundMax,SoundTop,SoundBottom;
float OffSet,Scale;
unsigned short GroupIndex;
//Information about input signals
TInpType InpType[numbofsignal];
//TInpSubType InpSubType[numbofsignal];
TActionType Action[numbofsignal-1];
TSignalType Type;
//static int DataDiff;
//static int AlarmDiff;
bool SaveAlarm;
__fastcall TDataConteiner(int);
void CheckSignal();
bool SaveOrNo(const TDateTime& CurTime,unsigned short StdAl);
class TSmoothObject
 {
 public:
 unsigned int ArraySize:12;//ArraySize CurrentElement bit field should have equivalent size
 unsigned int CurrentElement:11;
 bool Smoothing,OnlyRecorded;
 //???? ???? ?? ?????????? Calc ?????? ??? ???????? ??????? ???? ?????????? ?? ????? ??????? ?? ??????? ????????
 //bool FPassiveCalcSignal;
 float Value,Reserved1,Reserved2;
 float* Array;
 TSmoothObject(){OnlyRecorded=false;Array=0;ArraySize=0;CurrentElement=0;Smoothing=false;}
 ~TSmoothObject(){delete []Array;}
 //TSmoothObject&
 operator=(const TSmoothObject& Src);
 TSmoothObject(const TSmoothObject& Src){*this=Src;}

 }SmoothObject;
void __fastcall SetArraySize(unsigned int);
 void __fastcall SetValue(float);
 void __fastcall SetSmoothing(bool);
AnsiString AlarmSound,Message;
protected:
private:
enum{maxcritnumber=2}
unsigned short CritCounter;
TDateTime FSaveFrequency,FAlarmFrequency;
bool FSaveData;
float FInpSignal[numbofsignal];
//unsigned short FArraySize,FPointer;
//bool FSmoothing;
inline bool CheckToYes(const AnsiString&);
bool FMaxAlarm,FMinAlarm,FTopAlarm,FBottomAlarm,FCritSignal,FOnSignal,FOnlyMessage;
bool __fastcall GetMaxAlarm(){/*CheckSignal();*/return FMaxAlarm;}
bool __fastcall GetMinAlarm(){/*CheckSignal();*/return FMinAlarm;}
bool __fastcall GetTopAlarm(){/*CheckSignal();*/return FTopAlarm;}
bool __fastcall GetBottomAlarm(){/*CheckSignal();*/return FBottomAlarm;}
bool __fastcall GetCritSignal(){/*CheckSignal();*/return FCritSignal;}
bool __fastcall GetMessage(){/*CheckSignal();*/return FOnlyMessage;}
void SendToDevice();
//void __fastcall SetInputDevice(TInputDevice&);
float FLastSaved,FLastAlarm,FInpValue,FCalcValue,FOutValue;
TDateTime FLastSaveTime,FLastAlarmTime;
bool FInpChanged,FCalcChanged;
unsigned int FSignalNumber;//,FTakedFrom;

void CalculateCalc();
void CalculateOut();
float GetSignal(const int&);//,const TSignalType&);
void __fastcall SetInpValue(float Value){FInpValue=Value;FInpChanged=true;}
void __fastcall SetCalcValue(float Value){FCalcValue=Value;FCalcChanged=true;}
void __fastcall SetLastSaved(float Value){FLastSaved=Value;FLastSaveTime=TDateTime::CurrentDateTime();}
void __fastcall SetLastAlarm(float Value){FLastAlarm=Value;FLastAlarmTime=TDateTime::CurrentDateTime();}
void __fastcall SetSaveData(bool Value){FSaveData=Value;SaveAlarm=Value;}
void __fastcall SetInpSignal(unsigned int Index,float Value){FInpSignal[Index]=Value;FInpChanged=true;}
float __fastcall GetInpSignal(unsigned int Index){return FInpSignal[Index];}
void __fastcall SetSaveFrequency(TDateTime Value){FSaveFrequency=Value;AlarmFrequency=TDateTime(double(Value)/10);}
//void __fastcall SetArraySize(unsigned int Val){SmoothObject.SetArraySize(Val);}
//unsigned int __fastcall GetArraySize(){return SmoothObject.ArraySize;}
//void __fastcall SetSmoothing(bool Val){SmoothObject.SetSmoothing(Val);}
//bool __fastcall GetSmoothing(){return SmoothObject.Smoothing;}
//void __fastcall SetValue(float Val);//{SmoothObject.SetValue(Val);}
//float __fastcall GetValue(){return SmoothObject.Value;}
float __fastcall GetCalcValue(void);
float __fastcall GetOutValue(void);
__published:
__property float InpValue={read=FInpValue,write=SetInpValue};
__property float CalcValue={read=GetCalcValue,write=SetCalcValue};
__property float OutValue={read=GetOutValue};
__property float LastSaved={read=FLastSaved,write=SetLastSaved};
__property float LastAlarm={read=FLastAlarm,write=SetLastAlarm};
__property TDateTime LastSaveTime={read=FLastSaveTime};
__property TDateTime LastAlarmTime={read=FLastAlarmTime};
__property unsigned int SignalNumber={read=FSignalNumber,write=FSignalNumber};
__property bool MaxAlarm={read=GetMaxAlarm};
__property bool MinAlarm={read=GetMinAlarm};
__property bool TopAlarm={read=GetTopAlarm};
__property bool BottomAlarm={read=GetBottomAlarm};
__property bool CritSignal={read=GetCritSignal};
__property bool OnlyMessage={read=GetMessage};
__property bool OnSignal={read=FOnSignal,write=FOnSignal};
__property unsigned int ArraySize={read=SmoothObject.ArraySize,write=SetArraySize};//SmoothObject.ArraySize,write=SmoothObject.SetArraySize);
__property bool Smoothing={read=SmoothObject.Smoothing,write=SetSmoothing};
__property float SmValue={read=SmoothObject.Value,write=SetValue};///**/
__property bool SaveData={read=FSaveData,write=SetSaveData};
__property float InpSignal[unsigned int Index]={read=GetInpSignal,write=SetInpSignal};
__property TDateTime SaveFrequency={read=FSaveFrequency,write=SetSaveFrequency};
__property TDateTime AlarmFrequency={read=FAlarmFrequency,write=FAlarmFrequency};
//__property TInputDevice* InputDevice={read=&FInputDevice,write=SetInputDevice};
//__property TSignalType Type={read=FType,write=FType};
//__property TSubType SubType={read=FSubType,write=FSubType};/*
//__property int TakedFrom={read=FTakedFrom,write=FTakedFrom};//*/
};
/*template <class T>//,unsigned long Size>
class TDifArray:public TObject
{
private:
unsigned long FArraySize;
T* OldPointer;
protected:
public:
T* Array;
TDifArray(){FArraySize=0;Array=0;OldPointer=0;}
//~TDifArray(){if(OldPointer)delete []OldPointer;if(Array)delete[]Array;}
void __fastcall SetArraySize(unsigned long)
 {
 if(OldPointer)delete []OldPointer;
 OldPointer=Array;
  Array=new T[Val];
  if(OldPointer)
   {
   unsigned long MinSize=FArraySize<Val?FArraySize:Val;
   if(MinSize>0)
    for(unsigned long i=0;i<MinSize;i++)
     Array[i]=OldPointer[i];
   }
 delete []OldPointer;
 }
//unsigned long __fastcall GetArraySize();
void __fastcall SetValue(unsigned long Index,T Value);
T __fastcall GetValue(unsigned long Index);
__published:
__property unsigned long Size={read=FArraySize,write=SetArraySize};
//__property T Element[unsigned long Index]={read=GetValue,write=SetValue};
};*/
#endif
