//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MainUnut.h"
#include "SetBD.h"


#include "SetStat.h"
#include "StdLib.h"
#include "SetGraph.h"
#include "Grapher.h"
#include "AlarmLis.h"
#include "SetAdres.h"
#include "Math.h"
#include "IOThread.h"
#include "InteForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//TDataModule1* DataModule1;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
//Initial all properties                     //TForm
#ifdef Debug
MoveItem->Visible=true;
N4->Visible=true;
N5->Visible=true;
AllVisible->Visible=true;
SavaAsItem->Visible=true;
LoadItem->Visible=true;
NewItem->Visible=true;
#endif
for(int i=0;i<ChCount;i++)MDIChildType[i]=0;
//for(i=0;i<maxform+1;i++) ExistForm[i]=false;
ProgramDir=GetCurrentDir();
//ProgDir= ProgramDir;
SaveFrequenty=600;
EnablDrag=MoveItem->Checked;
/*for(int i=0;i<maxadam;i++)
for(int j=0;j<maxchannel;j++)
 {
 Signal[i][j]=0;
 MaxAlarm[i][j]=false;
 MinAlarm[i][j]=false;
 TopAlarm[i][j]=false;
 BottomAlarm[i][j]=false;
 PresentParam[maxadam][maxchannel]=false;
 OnSignal[i][j]=true;
 ParamCaptions[i][j]="";
 //Alarm[i][j]=false;
 Max[i][j]=0;
 Min[i][j]=0;
 CritSignals[i][j]=false;
 EdIzm[maxadam][maxchannel];//EdIzm field
 SoundMin[i][j]="";
 SoundMax[i][j]="";
 SoundTop[i][j]="";
 SoundBottom[i][j]="";
 Number[i][j]=-1;
 GroupIndex[i][j]=-1;
 SmoothObject[i][j]=0;
 EnablSmooth[i][j]=false;
 PresentSmooth[i][j]=false;
 }*/
//SetsAd.Clear();
//SetsChan.Clear();

//FanPresent=false;
GraphPresent=false;
SaveDialog->InitialDir=ProgramDir;
SaveAlarm=true;
OnlyOperate=false;
//-----------------
for(int i=0;i<SoundBuffer;i++)OrderOfPlay[i]="";
EnableAddSound=true;
//SomeAlarm=false;
MaxSoundNumber=0;
//----------------
//Construct all modules
//DataModule1->InitialDataBases();
DataModule1=new TDataModule1(this);
//Make other actions
MainForm->InitialAlarmArray();
/*
TDataConteiner** Signals=defPointerToSignals;
for(int i=0;i<maxsignal;i++)if(Signals[i]){delete Signals[i];Signals[i]=0;}
//*/
for(int i=0;i<maxgraph;i++)PrintedAxis[i]=-1;
}
//-----------------------------------------------------------------------------
void __fastcall TMainForm::InitialAlarmArray(void)
{
//*
TDataConteiner** Signals=defPointerToSignals;
for(int i=0;i<maxsignal;i++)if(Signals[i])
 {
 delete Signals[i];Signals[i]=0;
 }
//*/
/*ZeroMemory(PreviousSignal,maxadam*maxchannel*sizeof(PreviousSignal[0][0]));
ZeroMemory(PreviousTime,sizeof(PreviousTime));
ZeroMemory(PrevCritSignal,sizeof(PrevCritSignal));
ZeroMemory(PrevCritTime,sizeof(PrevCritTime));*/
DataModule1->KanalsTable->DisableControls();
//int Ad,Kan;
unsigned int MinSaveFrequency=-1;
try
{
DataModule1->KanalsTable->First();
//DataModule1->KanalsTable->Next();
//AnsiString a=DataModule1->KanalsTable->FieldByName("SoundMax")->AsString;
//KanalsTable->Prior();
if(!DataModule1->KanalsTable->Eof)
do
 {
 //*
 //TDataConteiner** Signals=defPointerToSignals;
 int Numb=DataModule1->KanalsTable->FieldByName("Number")->AsInteger;
 if(Numb<maxsignal)
  {
  if(Signals[Numb]){delete Signals[Numb];Signals[Numb]=0;}
  Signals[Numb]=new TDataConteiner(Numb);
  Signals[Numb]->Type=stInp;
  Signals[Numb]->InputDevice.Port=DataModule1->KanalsTable->FieldValues["Adam"];
  Signals[Numb]->InputDevice.Channel=DataModule1->KanalsTable->FieldValues["Kanal"];
  Signals[Numb]->InputDevice.SingleDevice=true;
  defExtDev[Signals[Numb]->InputDevice.Port][0][Signals[Numb]->InputDevice.Channel]=Numb;
  defSingleDevice[Signals[Numb]->InputDevice.Port]=true;
  Signals[Numb]->Name=DataModule1->KanalsTable->FieldByName("Parametr")->AsString;
  Signals[Numb]->EdIzm=DataModule1->KanalsTable->FieldByName("EdIzm")->AsString;//EdIzm field
  Signals[Numb]->Limits.Min=DataModule1->KanalsTable->FieldByName("Min")->AsFloat;
  Signals[Numb]->Limits.Max=DataModule1->KanalsTable->FieldByName("Max")->AsFloat;
  Signals[Numb]->Limits.MinAlarm=DataModule1->KanalsTable->FieldByName("MinAlarm")->AsFloat;
  Signals[Numb]->Limits.MaxAlarm=DataModule1->KanalsTable->FieldByName("MaxAlarm")->AsFloat;
  Signals[Numb]->SoundMin=DataModule1->KanalsTable->FieldByName("SoundMin")->AsString;
  Signals[Numb]->SoundMax=DataModule1->KanalsTable->FieldByName("SoundMax")->AsString;
  Signals[Numb]->SoundTop=DataModule1->KanalsTable->FieldByName("SoundTop")->AsString;
  Signals[Numb]->SoundBottom=DataModule1->KanalsTable->FieldByName("SoundBottom")->AsString;
  Signals[Numb]->GroupIndex=DataModule1->KanalsTable->FieldByName("GroupInd")->AsInteger;
  Signals[Numb]->SaveData=DataModule1->KanalsTable->FieldByName("SaveData")->AsBoolean;
  {
  int PromInt=0;
  PromInt=DataModule1->KanalsTable->FieldByName("SaveFrequency")->AsInteger;
  if((PromInt>0)&&(PromInt<20000))Signals[Numb]->SaveFrequency=double(PromInt)/86400;
  else
   {
   Signals[Numb]->SaveFrequency=60/86400;
   PromInt=60/86400;
   }
  if(MinSaveFrequency>PromInt)MinSaveFrequency=PromInt;
  }
 //
 if(DataModule1->KanalsTable->FieldByName("Scale")->AsString=="")
  Signals[Numb]->Scale=1;
 else
  Signals[Numb]->Scale=DataModule1->KanalsTable->FieldByName("Scale")->AsFloat;

 if(DataModule1->KanalsTable->FieldByName("OffSet")->AsString=="")
  Signals[Numb]->OffSet=0;
 else
  Signals[Numb]->OffSet=DataModule1->KanalsTable->FieldByName("OffSet")->AsFloat;
  Signals[Numb]->Smoothing=(DataModule1->KanalsTable->FieldByName("Smoothing")->AsBoolean);
  if(Signals[Numb]->Smoothing)
   {
   Signals[Numb]->ArraySize=DataModule1->KanalsTable->FieldByName("ArraySize")->AsInteger;
   }/**////////////////////////////////////////
  }
 else
  {
  Application->MessageBox("���������� ����������� ������ �������","Warning",MB_OK|MB_ICONSTOP);
  }
  //*/
 AnsiString a;// float b; float c;
 ///Ad=DataModule1->KanalsTable->FieldValues["Adam"];
 ///Kan=DataModule1->KanalsTable->FieldValues["Kanal"];
 //Load database in memory
 //ParamCaptions[Ad][Kan]=DataModule1->KanalsTable->FieldByName("Parametr")->AsString;
 //EdIzm[Ad][Kan]=DataModule1->KanalsTable->FieldByName("EdIzm")->AsString;//EdIzm field
 //Min[Ad][Kan]=DataModule1->KanalsTable->FieldByName("Min")->AsFloat;
 //Max[Ad][Kan]=DataModule1->KanalsTable->FieldByName("Max")->AsFloat;
 //MinAl[Ad][Kan]=DataModule1->KanalsTable->FieldByName("MinAlarm")->AsFloat;
 //MaxAl[Ad][Kan]=DataModule1->KanalsTable->FieldByName("MaxAlarm")->AsFloat;
 //SoundMin[Ad][Kan]=DataModule1->KanalsTable->FieldByName("SoundMin")->AsString;
 //SoundMax[Ad][Kan]=DataModule1->KanalsTable->FieldByName("SoundMax")->AsString;
 //SoundTop[Ad][Kan]=DataModule1->KanalsTable->FieldByName("SoundTop")->AsString;
 //SoundBottom[Ad][Kan]=DataModule1->KanalsTable->FieldByName("SoundBottom")->AsString;
 //Number[Ad][Kan]=DataModule1->KanalsTable->FieldByName("Number")->AsInteger;//Number field(order number)
 //GroupIndex[Ad][Kan]=DataModule1->KanalsTable->FieldByName("GroupInd")->AsInteger;
 //SaveData[Ad][Kan]=DataModule1->KanalsTable->FieldByName("SaveData")->AsBoolean;
 //PresentParam[Ad][Kan]=true;
 //
 /*a=DataModule1->KanalsTable->FieldByName("SoundMin")->AsString;
 b=DataModule1->KanalsTable->FieldByName("Min")->AsFloat;
 c=DataModule1->KanalsTable->FieldByName("MinAlarm")->AsFloat;
  if((a!="")&&(b<c))
  MinAlarm[Ad][Kan]=true;
 a=DataModule1->KanalsTable->FieldByName("SoundMax")->AsString;
 b=DataModule1->KanalsTable->FieldByName("Max")->AsFloat;
 c=DataModule1->KanalsTable->FieldByName("MaxAlarm")->AsFloat;
 if((a!="")&&(b>c)) MaxAlarm[Ad][Kan]=true;
 a=DataModule1->KanalsTable->FieldByName("SoundBottom")->AsString;
 if(a!="")  BottomAlarm[Ad][Kan]=true;
 a=DataModule1->KanalsTable->FieldByName("SoundTop")->AsString;
 if(a!="") TopAlarm[Ad][Kan]=true;
  //DataModule1->KanalsTable->FindNext();

 if(DataModule1->KanalsTable->FieldByName("Scale")->AsString=="")
  Scales[Ad][Kan]=1;
 else
  Scales[Ad][Kan]=DataModule1->KanalsTable->FieldByName("Scale")->AsFloat;

 if(DataModule1->KanalsTable->FieldByName("OffSet")->AsString=="")
  OffSet[Ad][Kan]=0;
 else
 OffSet[Ad][Kan]=DataModule1->KanalsTable->FieldByName("OffSet")->AsFloat;
 EnablSmooth[Ad][Kan]=DataModule1->KanalsTable->FieldByName("Smoothing")->AsBoolean;
 if(PresentSmooth[Ad][Kan]) delete SmoothObject[Ad][Kan];
 SmoothObject[Ad][Kan]=0;
 //Construct Smooth objects
 if(DataModule1->KanalsTable->FieldByName("Smoothing")->AsBoolean)
  {
  PresentSmooth[Ad][Kan]=true;
  SmoothObject[Ad][Kan]=new TSmooth(DataModule1->KanalsTable->FieldByName("ArraySize")->AsInteger);
  }*/
 }
while(DataModule1->KanalsTable->FindNext());
 DataModule1->KanalsTable->EnableControls();
 DataModule1->KanalsTable->CancelUpdates();
 }
catch(...)
 {
 DataModule1->KanalsTable->EnableControls();
 DataModule1->KanalsTable->CancelUpdates();
 }
//Initial calculate signals
DataModule1->CalcSignTable->DisableControls();
try
{
DataModule1->CalcSignTable->First();
//DataModule1->KanalsTable->Next();
//AnsiString a=DataModule1->KanalsTable->FieldByName("SoundMax")->AsString;
//KanalsTable->Prior();
if(!DataModule1->CalcSignTable->Eof)
do
 {
 //*
 TDataConteiner** Signals=defPointerToSignals;
 int Numb=DataModule1->CalcSignTable->FieldByName("Number")->AsInteger;
 if(Numb<maxsignal)
  {
  if(Signals[Numb]){delete Signals[Numb];Signals[Numb]=0;}
  Signals[Numb]=new TDataConteiner(Numb);
  Signals[Numb]->Type=stCalc;
  for(int i=0;i<numbofsignal;i++)
   {
   if(DataModule1->CalcSignTable->FieldByName("Signal"+IntToStr(i+1))->AsFloat!=0)
    Signals[Numb]->InpSignal[i]=DataModule1->CalcSignTable->FieldByName("Signal"+IntToStr(i+1))->AsFloat;
   else Signals[Numb]->InpSignal[i]=0;
   if(DataModule1->CalcSignTable->FieldByName("SignalType"+IntToStr(i+1))->AsString!="")
    Signals[Numb]->InpType[i]=DataModule1->CalcSignTable->FieldByName("SignalType"+IntToStr(i+1))->AsInteger;
   else Signals[Numb]->InpType[i]=itNotDefine;
   }
  for(int i=0;i<numbofsignal-1;i++)
   {
   if(DataModule1->CalcSignTable->FieldByName("Action"+IntToStr(i+1))->AsString!="")
    Signals[Numb]->Action[i]=DataModule1->CalcSignTable->FieldByName("Action"+IntToStr(i+1))->AsFloat;
   else Signals[Numb]->Action[i]=atNotDefine;
   }
  /*Signals[Numb]->InputDevice.Port=DataModule1->CalcSignTable->FieldValues["Adam"];
  Signals[Numb]->InputDevice.Channel=Kan=DataModule1->CalcSignTable->FieldValues["Kanal"];
  Signals[Numb]->InputDevice.SingleDevice=true;
  defExtDev[Signals[Numb]->InputDevice.Port][0][Signals[Numb]->InputDevice.Channel]=Numb;
  defSingleDevice[Signals[Numb]->InputDevice.Port]=true;*/
  Signals[Numb]->Name=DataModule1->CalcSignTable->FieldByName("Parametr")->AsString;
  Signals[Numb]->EdIzm=DataModule1->CalcSignTable->FieldByName("EdIzm")->AsString;//EdIzm field
  Signals[Numb]->Limits.Min=DataModule1->CalcSignTable->FieldByName("Min")->AsFloat;
  Signals[Numb]->Limits.Max=DataModule1->CalcSignTable->FieldByName("Max")->AsFloat;
  Signals[Numb]->Limits.MinAlarm=DataModule1->CalcSignTable->FieldByName("MinAlarm")->AsFloat;
  Signals[Numb]->Limits.MaxAlarm=DataModule1->CalcSignTable->FieldByName("MaxAlarm")->AsFloat;
  Signals[Numb]->SoundMin=DataModule1->CalcSignTable->FieldByName("SoundMin")->AsString;
  Signals[Numb]->SoundMax=DataModule1->CalcSignTable->FieldByName("SoundMax")->AsString;
  Signals[Numb]->SoundTop=DataModule1->CalcSignTable->FieldByName("SoundTop")->AsString;
  Signals[Numb]->SoundBottom=DataModule1->CalcSignTable->FieldByName("SoundBottom")->AsString;
  Signals[Numb]->GroupIndex=DataModule1->CalcSignTable->FieldByName("GroupInd")->AsInteger;
  Signals[Numb]->SaveData=DataModule1->CalcSignTable->FieldByName("SaveData")->AsBoolean;
  {
  int PromInt=0;
  PromInt=DataModule1->CalcSignTable->FieldByName("SaveFrequency")->AsInteger;
  if((PromInt>0)&&(PromInt<20000))Signals[Numb]->SaveFrequency=double(PromInt)/86400;
  else
   {
   Signals[Numb]->SaveFrequency=60/86400;
   PromInt=60/86400;
   }
  if(MinSaveFrequency>PromInt)MinSaveFrequency=PromInt;
  }
  //
  if(DataModule1->CalcSignTable->FieldByName("Scale")->AsString=="")
   Signals[Numb]->Scale=1;
  else
   Signals[Numb]->Scale=DataModule1->CalcSignTable->FieldByName("Scale")->AsFloat;

  if(DataModule1->CalcSignTable->FieldByName("OffSet")->AsString=="")
   Signals[Numb]->OffSet=0;
  else
   Signals[Numb]->OffSet=DataModule1->CalcSignTable->FieldByName("OffSet")->AsFloat;
   Signals[Numb]->Smoothing=(DataModule1->CalcSignTable->FieldByName("Smoothing")->AsBoolean);
   if(Signals[Numb]->Smoothing)
    {
    Signals[Numb]->ArraySize=DataModule1->CalcSignTable->FieldByName("ArraySize")->AsInteger;
    }
   }
  else
   {
   Application->MessageBox("���������� ����������� ������ �������","Warning",MB_OK|MB_ICONSTOP);
   }
  }while(DataModule1->CalcSignTable->FindNext());
 DataModule1->CalcSignTable->EnableControls();
 DataModule1->CalcSignTable->CancelUpdates();
 }
catch(...)
 {
 DataModule1->CalcSignTable->EnableControls();
 DataModule1->CalcSignTable->CancelUpdates();
 }
DataBaseTimer->Interval=MinSaveFrequency;
SaveFrequenty=MinSaveFrequency;
AlarmTimer->Interval=MinSaveFrequency/10;
SaveAlarmFreq=MinSaveFrequency/10;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckSignals()
{
bool Alar=false;
//DataModule1->KanalsTable->DatabaseName=MainForm->ProgramDir;
//DataModule1->KanalsTable->TableName=MainForm->ProgramDir+DataModule1->KanName;
//DataModule1->KanalsTable->Active=true;
//void AddSound(AnsiString);
AnsiString FileName1="";
AlarmMessage="";
TDataConteiner** Signal=defPointerToSignals;
SetGroupIndex.Clear();
if(MaxSoundNumber==0)
 {
 for(int i=0;i<SoundBuffer;i++)OrderOfPlay[i]="";
 EnableAddSound=true;
 MaxSoundNumber=0;
 }
else if(MaxSoundNumber<SoundBuffer-1)
 {
 //for(int i=MaxSoundNumber+1;i<SoundBuffer;i++)OrderOfPlay[i]="";
 EnableAddSound=true;
 }
else
 {
 EnableAddSound=false;
 MaxSoundNumber=SoundBuffer-1;
 }
for(unsigned  int i=0;i<maxsignal;i++)
if(Signal[i])
 {
 Signal[i]->CheckSignal();
 if(Signal[i]->CritSignal)
  {
  Alar=true;
  if(!CheckMax(Signal[i]->GroupIndex))
   {
   SetGroupIndex<<Signal[i]->GroupIndex;
   AddSound(Signal[i]->AlarmSound);
   }
  else
   {
   AlarmMessage+=(AlarmMessage=="")?"":" ";
   AlarmMessage+=Signal[i]->Message;
   AddSound(Signal[i]->AlarmSound);
   }
  }
 }
//End for
 if(!Alar)
  {
  MaxSoundNumber=0;
  MainForm->MediaPlayer->Stop();
  MainForm->MediaPlayer->Position=0;
  //MainForm->MediaPlayer->Close();
  EnableAddSound=true;
  for(int i=0;i<SoundBuffer;i++)OrderOfPlay[i]="";
  }
 if(MaxSoundNumber>0)
  {
  if(MainForm->MediaPlayer->Mode==mpNotReady)
   {
   MainForm->MediaPlayer->FileName=MainForm->ProgramDir+"\\Wav\\"+OrderOfPlay[0];
   MainForm->MediaPlayer->Open();
   }
  if(((MainForm->MediaPlayer->Position==0)||
  (MainForm->MediaPlayer->Position==MainForm->MediaPlayer->Length)))
   {
   FileName1=OrderOfPlay[0];
   MaxSoundNumber--;
   EnableAddSound=true;
   if(MaxSoundNumber<=0)
    {
    MaxSoundNumber=0;
    }
   for(int i=1;i<SoundBuffer;i++)OrderOfPlay[i-1]=OrderOfPlay[i];
   try
    {
     MainForm->MediaPlayer->Stop();
     MainForm->MediaPlayer->Position=0;
     MainForm->MediaPlayer->FileName=MainForm->ProgramDir+"\\Wav\\"+FileName1;
     MainForm->MediaPlayer->Open();
     MainForm->MediaPlayer->Play();
    }
   catch(...)
    {
    Application->MessageBox("�� ������ ���-�� �� ��.","Warning",MB_OK|MB_ICONWARNING);
    }
   }
  //MainForm->StatusBar->SimpleText=ParamName;
  //MainForm->StatusBar->SimplePanel=true;
  //MainForm->StatusBar->Color=clRed;                                 TForm
  }
 /*else
  {
  MainForm->StatusBar->SimplePanel=false;
  MainForm->StatusBar->Color=clBtnFace;
  }
 /*if(ParamName!="")
  {
  MainForm->StatusBar->SimpleText=ParamName;
  MainForm->StatusBar->SimplePanel=true;
  MainForm->StatusBar->Color=clRed;
  }
 else
  {
  MainForm->StatusBar->SimplePanel=false;
  MainForm->StatusBar->Color=clBtnFace;
  }*/
//DataModule1->KanalsTable->EnableControls();

}//End Check
//-----------------------------------------------------------------------------
void TMainForm::AddSound(AnsiString A)
 {
 for(int i=0;i<SoundBuffer;i++)
  if(OrderOfPlay[i]=="")
   for(int j=i+1;j<SoundBuffer;j++)
    if(OrderOfPlay[j]!="")
     {
     OrderOfPlay[i]=OrderOfPlay[j];
     OrderOfPlay[j]="";
     break;
     }
 MaxSoundNumber=0;
 for(int i=0;((i<SoundBuffer)&&(OrderOfPlay[i]!=""));i++)MaxSoundNumber=i+1;
 bool APresent=false;
 for(int i=0;i<SoundBuffer;i++)
  if(OrderOfPlay[i]==A)
   {
   APresent=true;
   break;
   }
 if((EnableAddSound)&&(MaxSoundNumber<SoundBuffer-1)&&(A!="")&&(!APresent))
  {
  OrderOfPlay[MaxSoundNumber]=A;
  MaxSoundNumber++;
  if(MaxSoundNumber>=SoundBuffer-1)
   {
   EnableAddSound=false;
   MaxSoundNumber=SoundBuffer-1;
   }
  }
 }
//----------------------------------------------------------------------------
void __fastcall TMainForm::ViewAlarm()
{
//if(Terminated)return;
AnsiString CommError="";
if(AdConnThread->CommErrorInfo.Error)
 {
 CommError+="��� ������ �";
 for(int i=0;i<maxadam;i++)
  if(AdConnThread->CommErrorInfo.FailsPorts[i])
   {
   CommError+=" :���� "+IntToStr(i)+" ������";
   bool Flag=0;
   for(int j=0;j<maxchannel;j++)
    if(AdConnThread->CommErrorInfo.Fails[i][j])
     {
     if(Flag)CommError+=",";
     else CommError+=" ";
     CommError+=IntToStr(j);
     Flag=1;
     }
   }
 }
Set<int,0,maxgroup>Test;
Test.Clear();
ParamName="";
if(SetGroupIndex!=Test)
 {
 for(int i=0;i<maxgroup;i++)
  {
  if(SetGroupIndex.Contains(i))
   {
   ParamName+=(ParamName=="")?MainForm->MessageByIndex[i]:" "+MainForm->MessageByIndex[i];
   }
  }
 }
if((ParamName!="")||(AlarmMessage!="")||(CommError!=""))
  {
  MainForm->StatusBar->SimpleText=ParamName+" "+AlarmMessage+" "+CommError;
  MainForm->StatusBar->SimplePanel=true;
  MainForm->StatusBar->Color=clRed;
  if(MainForm->SaveAlarm)
  MainForm->AlarmTimer->Enabled=true;
  //MainForm->Alarm[ad][chan]=true;
  //MainForm->DataBaseTimer->Interval=1000;
  }
 else
  {
  MainForm->StatusBar->SimplePanel=false;
  MainForm->StatusBar->Color=clBtnFace;
  MainForm->AlarmTimer->Enabled=false;
  //MainForm->Alarm[ad][chan]=false;
  //MainForm->DataBaseTimer->Interval=MainForm->SaveFrequenty*1000;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{

TIniFile *IniFile;
IniFile=new TIniFile(ProgramDir+"\\Settings.ini");
DataBaseTimer->Enabled=IniFile->ReadBool("GlobalSettings","SaveData",true);
//SaveFrequenty=IniFile->ReadInteger("GlobalSettings","SaveFrequenty",30);
DataDiff=IniFile->ReadInteger("GlobalSettings","DataDiff",5);
State.SaveData=DataBaseTimer->Enabled;
//SaveAlarmFreq=IniFile->ReadInteger("GlobalSettings","SaveAlarmFreq",1);
AlarmDiff=IniFile->ReadInteger("GlobalSettings","AlarmDiff",3);
SaveAlarm=IniFile->ReadBool("GlobalSettings","SaveAlarm",false);
AlarmTimer->Interval=SaveAlarmFreq*1000;
DataBaseTimer->Interval=SaveFrequenty*1000;
//
ListWidth=IniFile->ReadInteger("GraphSettings","ListWidth",250);
ListHeight=IniFile->ReadInteger("GraphSettings","ListHeight",160);
ListTop=IniFile->ReadInteger("GraphSettings","ListTop",10);
ListLeft=IniFile->ReadInteger("GraphSettings","ListLeft",15);
DPI=IniFile->ReadInteger("GraphSettings","DPI",600);
GraphWidth=IniFile->ReadInteger("GraphSettings","GraphWidth",6);
AxisWidth=IniFile->ReadInteger("GraphSettings","AxisWidth",3);
GirdWidth=IniFile->ReadInteger("GraphSettings","GirdWidth",1);
StepX=IniFile->ReadInteger("GraphSettings","StepX",80);
StepY=IniFile->ReadInteger("GraphSettings","StepY",40);
AllBlack=IniFile->ReadBool("GraphSettings","AllBlack",1);
for(int  i=0;i<maxgraph;i++)
 {
 int Axis1=IniFile->ReadInteger("GraphSettings","Graphic"+IntToStr(i),-1);
 if(defPointerToSignals[Axis1])PrintedAxis[i]=Axis1;else PrintedAxis[i]=-1;
 }
PrintAllAxis=IniFile->ReadBool("GraphSettings","PrintAllAxis",1);
//---------------
//Create Graphers
/*for(int i=0;i<maxform;i++)
{
AnsiString Test;
//TGrapherForm *Form11;
Test=IniFile->ReadInteger("Grapher"+IntToStr(i),"Adam",-1);
 if(Test!=-1)
   {
   TGrapherForm *Form11=new TGrapherForm(this);
   Form11->LoadFromIniFile(IniFile,"Grapher"+IntToStr(i));
   }
}//*/
delete IniFile;
//
AnsiString Adr;
IniFile=new TIniFile(ProgramDir+"\\SetAdres.ini");
for(int i=0;i<maxadam;i++)
 {
 Adr=IniFile->ReadString("Adres","Adam"+IntToStr(i),"nn");
 if(Adr!="")
  {
  Adres[i][0]=Adr[1];
  Adres[i][1]=Adr[2];
  }
 else
  {
  Adres[i][0]='n';
  Adres[i][1]='n';
  }
 }
for(int i=0;i<maxgroup;i++)
 {
 MessageByIndex[i]=IniFile->ReadString("IndexMessage","Index"+IntToStr(i),"");
 }
delete IniFile;
//MediaPlayer->Wait=true;
MediaPlayer->FileName=ProgramDir+"\\Wav\\logoff.wav";
MediaPlayer->Open();
MediaPlayer->Play();
//MediaPlayer->Close();
//-------------
/*TDateTime Tim;
Tim=Date();//.FormatString("dd");
TDateTime Message=36856,BreackPr=36871;//36811 12 Octobe 36856 36871
if(Tim>=BreackPr)
 {
 Application->Terminate();
 return;
 }
AnsiString MesAn="��������� � �������������� ��� ����� "+
IntToStr(int(BreackPr-Message))+" ���� ��������� ���������� ��������";
int Length=MesAn.Length();
char Mes[85];
for(int i=0;i<85;i++)
 {
 if(i<Length)Mes[i]=MesAn[i+1];else Mes[i]=0;
 }
if(Tim>=Message) Application->MessageBox(&Mes[0],"���������",
MB_OK|MB_ICONWARNING|MB_DEFBUTTON1|MB_APPLMODAL);*/
//-----------
//Thread=new TAdConnThread(true);
//Thread->Suspended=false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormActivate(TObject *Sender)
{
//Create Graphers
TIniFile *IniFile;
IniFile=new TIniFile(MainForm->ProgramDir+"\\Graphers.ini");
for(int i=0;i<maxform;i++)
{
AnsiString Test;
//TGrapherForm *Form11;
Test=IniFile->ReadInteger("Grapher"+IntToStr(i),"Adam",-1);
 if(Test!=-1)
   {
   TGrapherForm *Form14=new TGrapherForm(MainForm);
   Form14->LoadFromIniFile(IniFile,"Grapher"+IntToStr(i));
   }
}
delete IniFile; //*/
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
bool EnableSavData=DataBaseTimer->Enabled;
if(CheckSignalTimer->Enabled)CheckSignalTimer->Enabled=false;
if(Timer1->Enabled)Timer1->Enabled=false;
if(DataBaseTimer->Enabled)DataBaseTimer->Enabled=false;
if(AlarmTimer->Enabled)AlarmTimer->Enabled=false;
for(int i=0;i<MDIChildCount;i++)
{
if(MDIChildren[i])MDIChildren[i]->Release();
}
Pause(10);
TIniFile *IniFile;
/*if(Thread!=NULL)
Thread->Terminate();*/
//MediaPlayer->Close();
//DeleteFile(ProgramDir+"\\Settings.ini");
IniFile=new TIniFile(ProgramDir+"\\Settings.ini");
IniFile->WriteBool("GlobalSettings","SaveData",EnableSavData);
IniFile->WriteInteger("GlobalSettings","SaveFrequenty",SaveFrequenty);
IniFile->WriteInteger("GlobalSettings","DataDiff",DataDiff);
IniFile->WriteBool("GlobalSettings","SaveAlarm",SaveAlarm);
IniFile->WriteInteger("GlobalSettings","SaveAlarmFreq",SaveAlarmFreq);
IniFile->WriteInteger("GlobalSettings","AlarmDiff",AlarmDiff);
//
IniFile->WriteInteger("GraphSettings","ListWidth",ListWidth);
IniFile->WriteInteger("GraphSettings","ListHeight",ListHeight);
IniFile->WriteInteger("GraphSettings","ListTop",ListTop);
IniFile->WriteInteger("GraphSettings","ListLeft",ListLeft);
IniFile->WriteInteger("GraphSettings","DPI",DPI);
IniFile->WriteInteger("GraphSettings","GraphWidth",GraphWidth);
IniFile->WriteInteger("GraphSettings","AxisWidth",AxisWidth);
IniFile->WriteInteger("GraphSettings","GirdWidth",GirdWidth);
IniFile->WriteInteger("GraphSettings","StepX",StepX);
IniFile->WriteInteger("GraphSettings","StepY",StepY);
IniFile->WriteBool("GraphSettings","AllBlack",AllBlack);
for(int i=0;i<maxgraph;i++)
IniFile->WriteInteger("GraphSettings","Graphic"+IntToStr(i),PrintedAxis[i]);
IniFile->WriteBool("GraphSettings","PrintAllAxis",PrintAllAxis);
delete IniFile;
//
DeleteFile(ProgramDir+"\\Graphers.ini");
IniFile=new TIniFile(ProgramDir+"\\Graphers.ini");
if(MDIChildCount>0)
 {
 for(int i=0;i<MDIChildCount;i++)
  if((static_cast<TChildForm*>(MDIChildren[i])->Type!=1)&&
  (static_cast<TGrapherForm*>(MDIChildren[i])->Type==2))
   static_cast<TGrapherForm*>(MDIChildren[i])->SaveToIniFile(IniFile,"Grapher"+IntToStr(i));
 }//*/
//
delete IniFile;
MediaPlayer->Close();
//DeleteFile(ProgramDir+"\\SetAdres.ini");
IniFile=new TIniFile(ProgramDir+"\\SetAdres.ini");
for(int i=0;i<maxgroup;i++)
 {
 if(MessageByIndex[i]!="")
  {
  IniFile->WriteString("IndexMessage","Index"+IntToStr(i),MessageByIndex[i]);
  }
 }
delete IniFile;
/*for(int i=0;i<maxadam;i++)
 for(int j=0;j<maxchannel;j++)
  if(PresentSmooth[i][j])
   {
   delete SmoothObject[i][j];
   PresentSmooth[i][j]=false;
   SmoothObject[i][j]=0;
   }*/
//
if(DataModule1){delete DataModule1;DataModule1=0;}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShaxtMenuClick(TObject *Sender)
{
//TChildForm *FanForm=new TChildForm(this);
//if(!OpenDialog->Execute()) return;
TIniFile *IniFile;
IniFile=new TIniFile(ProgramDir+"\\Koteln.frm");
TChildForm *Forma2;
Forma2=new TChildForm(this);
static_cast<TChildForm*>(ActiveMDIChild)->LoadFromIniFile(IniFile);
delete IniFile;
//FanForm->Show();
ShaxtMenu->Enabled=false;
static_cast<TChildForm*>(ActiveMDIChild)->N2Click(this);
//FanPresent=true;
//ChildForm->Caption="����������";
//ChildForm->PaintBox->Picture->LoadFromFile(ProgramDir+"\\Images\\Fans.bmp");
/*Forms[MDIChildCount]=new TCildForm;
ExistForm[MDIChildCount]=true;
Form[MDIChildCount]->PaintBox->Picturie->LoadFronFile(CurrentDir+"\\Images\\
Fans.dfg");*/
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TileItemClick(TObject *Sender)
{
Tile();
TIniFile *IniFile;
for(int i=0;i<MDIChildCount;i++)
 if(MDIChildType[i]==1)
 {
 TChildForm* Form12=static_cast<TChildForm*>(MDIChildren[i]);
 AnsiString FileName=Form12->FileName;
 IniFile=new TIniFile(ProgramDir+"\\"+ExtractFileName(FileName));
 Form12->Width=IniFile->ReadInteger("GlobalSettings","Width",600);
 Form12->Height=IniFile->ReadInteger("GlobalSettings","Height",400);
 delete IniFile;
 }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CascadeItemClick(TObject *Sender)
{
Cascade();
TIniFile *IniFile;
for(int i=0;i<MDIChildCount;i++)
 if(MDIChildType[i]==1)
 {
 TChildForm* Form12=static_cast<TChildForm*>(MDIChildren[i]);
 AnsiString FileName=Form12->FileName;
 IniFile=new TIniFile(ProgramDir+"\\"+ExtractFileName(FileName));
 Form12->Width=IniFile->ReadInteger("GlobalSettings","Width",600);
 Form12->Height=IniFile->ReadInteger("GlobalSettings","Height",400);
 delete IniFile;
 }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ArrangeIItemClick(TObject *Sender)
{
for(int i=0;i<MDIChildCount;i++)
 static_cast<TForm*>(MDIChildren[i])->WindowState=wsMinimized;
 /*if(MDIChildType[i]==1)
 {
 TChildForm* Form12=static_cast<TChildForm*>(MDIChildren[i]);
 Form12->WindowState=wsMinimazed;
 } */
ArrangeIcons();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetItemClick(TObject *Sender)
{
AdConnThread->Suspended=true;//Terminate();//=true;
EnablSaveData=DataBaseTimer->Enabled;
DataBaseTimer->Enabled=false;
TSetParamForm *Form=new TSetParamForm(this);
DataModule1->KanalsTable->Refresh();
Form->ShowModal();
delete Form;
InitialAlarmArray();
DataBaseTimer->Enabled=EnablSaveData;
AdConnThread->Suspended=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GraphItemClick(TObject *Sender)
{
//EnablSaveData=DataBaseTimer->Enabled;
//DataBaseTimer->Enabled=false;
//DataBaseTimer->Enabled=EnablSaveData;
//AnsiString a=ExtractFileName("c:\Progs\asdrt.*");
/*TGraphForm */Graph=new TGraphForm(this);
GraphPresent=true;
Graph->ShowModal();
GraphPresent=false;
delete Graph;
//DataBaseTimer->Enabled=EnablSaveData;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N2Click(TObject *Sender)
{
EnablSaveData=DataBaseTimer->Enabled;
DataBaseTimer->Enabled=false;
EnableSaveAlarm=SaveAlarm;
AlarmTimer->Enabled=false;
SaveAlarm=false;
//DataModule->StatistTable->ReadOnly=true;
TSetBDForm *Form=new TSetBDForm(this);
//Form->EnablCheckBox->Checked=EnablSaveData;
Form->DiffUpDown->Position=DataDiff;
Form->dTime=SaveFrequenty;
Form->dAlarmTime=SaveAlarmFreq;
if(Form->ShowModal()==mrOk)
 {
 //EnablSaveData=Form->EnablCheckBox->Checked;
 SaveFrequenty=Form->dTime;
 DataBaseTimer->Interval=SaveFrequenty*1000;
 SaveAlarmFreq=Form->dAlarmTime;
 AlarmTimer->Interval=SaveAlarmFreq*1000;
 }
delete Form;
//DataModule->StatistTable->ReadOnly=false;
DataModule1->StatistTable->Filtered=false;
DataBaseTimer->Enabled=EnablSaveData;
SaveAlarm=EnableSaveAlarm;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N4Click(TObject *Sender)
{
TChildForm *Forma=new TChildForm(this);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MoveItemClick(TObject *Sender)
{
if(MoveItem->Checked)
{
MoveItem->Checked=false;
EnablDrag=false;
}
else
{
MoveItem->Checked=true;
EnablDrag=true;
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N5Click(TObject *Sender)
{
if(N5->Checked)
{
N5->Checked=false;
EnablPopUp=false;
for(int i=0;i<MDIChildCount;i++)
static_cast<TChildForm*>(MDIChildren[i])->AddObjectItem->Visible=false;
}
else
{
N5->Checked=true;
EnablPopUp=true;
for(int i=0;i<MDIChildCount;i++)
static_cast<TChildForm*>(MDIChildren[i])->AddObjectItem->Visible=true;
}
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
DataModule1->CurDateTime=DataModule1->CurDateTime.CurrentDateTime();
for(int i=0;i<1000;i++)
if(defPointerToSignals[i])
{
float delta=defPointerToSignals[i]->Limits.Max-defPointerToSignals[i]->Limits.Min;
float inp=defPointerToSignals[i]->CalcValue;
float a=random(delta);a=a-defPointerToSignals[i]->Limits.Min-inp;a/=10;
int b=random(100);
if(b>90)
 if((inp+a<defPointerToSignals[i]->Limits.Max)&&(inp+a>defPointerToSignals[i]->Limits.Min))
  defPointerToSignals[i]->InpValue=(inp+a-defPointerToSignals[i]->OffSet)/defPointerToSignals[i]->Scale;;//defPointerToSignals[i]->Limits.Max/3+a*2/3;//random(a/3*100)/100+a*2/6;
}
//if(defPointerToSignals[15])if((random(100)>60)&&(defPointerToSignals[15]->LastSaved==5))defPointerToSignals[15]->CalcValue=0;
//*else*/ if(defPointerToSignals[15])defPointerToSignals[15]->CalcValue=5;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SavaAsItemClick(TObject *Sender)
{
bool Flag=false;
do
{
 if(!SaveDialog->Execute()) return;
 //SaveDialog->FileName
 if(FileExists(SaveDialog->FileName))
  {
  AnsiString Mes="���� "+SaveDialog->FileName+" ��� ����������. �������� ������������  ����?";
  char* Mes1=Mes.c_str();
  if(MessageBox(NULL,Mes1,"��������� ���",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
   {
   DeleteFile(SaveDialog->FileName);
   Flag=true;
   }
  }
 else Flag=true;
}while(!Flag);

  TIniFile *IniFile;
  IniFile=new TIniFile(SaveDialog->FileName);
static_cast<TChildForm*>(ActiveMDIChild)->SaveToIniFile(IniFile);
delete IniFile;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LoadItemClick(TObject *Sender)
{
if(!OpenDialog->Execute()) return;
TIniFile *IniFile;
IniFile=new TIniFile(OpenDialog->FileName);
TChildForm *Forma2;
Forma2=new TChildForm(this);
static_cast<TChildForm*>(ActiveMDIChild)->LoadFromIniFile(IniFile);
delete IniFile;
}
//---------------------------------------------------------------------------   Violation


void __fastcall TMainForm::DataBaseTimerTimer(TObject *Sender)
{
//Bug
#ifdef Bugswitchedon
{
 TDateTime MaxDate=maxworkday;
 TDateTime Now=Date();
 if(Now>MaxDate)
  {
  MainForm->Paused=true;
  ShowMessage("���� �� ������ ��� ���� ��������� ���� �� ���� ������� �� �� ��������� ������ �� ��������� ��� � ����� ������ �����. ���� ������ ��������� ��������� � ����� � ������ � ��� ������, � ���� ��� �� ���������.");
  MainForm->Close();
 }
}//*/
#endif
//DataBaseTimer->Enabled=false;
//for(int i=0;i<MDIChildCount;i++)
//static_cast<TChildForm*>(MDIChildren[i])->Timer1->Enabled=false;
TDataConteiner** Signal=defPointerToSignals;
TDateTime dat;
TDateTime CurTime=TDateTime::CurrentDateTime();
//int ParamNumb;
//float const Diff=(float)DataDiff/100;//{Differences between last and present value of signals.
//Then differences encrees this value signal will be saved in database}
//int CurrentAdam,CurrentChannel;
float CurrentValue;
MainForm->StatusBar->SimpleText="������ ���� ������";
MainForm->StatusBar->SimplePanel=true;
try
{
//DataModule1->KanalsTable->DisableControls();
DataModule1->StatistTable->DisableControls();
DataModule1->KanalsTable->First();
//while(!DataModule1->KanalsTable->Eof)
for(unsigned int i=0;i<maxsignal;i++)
//if((Signal[i])&&(Signal[i]->SaveData)/*&&(Signal[i]->OutValue!=0)*/&&
//((Signal[i]->LastSaved*(1-Diff)>Signal[i]->OutValue)|(Signal[i]->LastSaved*(1+Diff)<Signal[i]->OutValue)|
//(CurTime-Signal[i]->LastSaveTime>=(TDateTime)(0.5/24))))
if((Signal[i])&&(Signal[i]->SaveOrNo(CurTime,0)))
 {
 CurrentValue=Signal[i]->OutValue;
 dat=Date();
 DataModule1->StatistTable->Append();
 DataModule1->StatistTable->FieldValues["Date"]=dat;
 DataModule1->StatistTable->FieldValues["Hours"]=StrToInt(Time().FormatString("hh"));
 DataModule1->StatistTable->FieldValues["Minuts"]=StrToInt(Time().FormatString("nn"));
 DataModule1->StatistTable->FieldValues["Seconds"]=StrToInt(Time().FormatString("ss"));
 DataModule1->StatistTable->FieldValues["Numb"]=i;
 DataModule1->StatistTable->FieldValues["Value"]=CurrentValue;
 DataModule1->StatistTable->Post();
 Signal[i]->LastSaved=CurrentValue;
 //Signal[i]->PreviousTime=CurTime;
 }
 //DataModule1->KanalsTable->EnableControls();
 DataModule1->StatistTable->EnableControls();
 //DataModule1->StatistTable->Post();
//if(GraphPresent)static_cast<TGraphForm*>(Graph)->PaintBox->Invalidate();
MainForm->StatusBar->SimplePanel=false;
}
catch(...)
{
//DataModule1->KanalsTable->EnableControls();
DataModule1->StatistTable->EnableControls();
//for(int i=0;i<MDIChildCount;i++)
//static_cast<TChildForm*>(MDIChildren[i])->Timer1->Enabled=true;
MainForm->StatusBar->SimplePanel=false;
}
//for(int i=0;i<MDIChildCount;i++)
//static_cast<TChildForm*>(MDIChildren[i])->Timer1->Enabled=true;
TDateTime RefreshTime1(14,0,0,0);
TDateTime RefreshTime2(15,0,0,0);
TDateTime Now=Time();
if(((Now>=RefreshTime1)&(Now<=RefreshTime2))&&(!OnlyOperate))
 {
 DataBaseTimer->Enabled=false;
 OnlyOperate=true;
 ReThread=new TRefreshThread(true);
 StatusBar->Color=clWindow;
 StatusBar->SimpleText="���������� ���� ������ � ��������� �����������";
 StatusBar->SimplePanel=true;
 ReThread->Suspended=false;

 }
if((Now<RefreshTime1)|(Now>RefreshTime2))
 {
 OnlyOperate=false;
 }
}
//---------------------------------------------------------------------------
                                                                  //TDataTime
void __fastcall TMainForm::SetGraphItemClick(TObject *Sender)
{
//TIniFile IniFile=new TIniFile(ProgramDir+"\\Setgraph.ini");
//IniFile->ReadBool("GlobalSettings","SaveData",true);
TSetPrnFo *Form6;
Form6=new TSetPrnFo(this);
Form6->WidthEdit->Text=IntToStr(ListWidth);
Form6->HeightEdit->Text=IntToStr(ListHeight);
Form6->LeftEdit->Text=IntToStr(ListLeft);
Form6->TopEdit->Text=IntToStr(ListTop);
Form6->DPIEdit->Text=IntToStr(DPI);
Form6->GirdUpDown->Position=GirdWidth;
Form6->AxisUpDown->Position=AxisWidth;
Form6->GraphUpDown->Position=GraphWidth;
Form6->StepXEdit->Text=IntToStr(StepX);
Form6->StepYEdit->Text=IntToStr(StepY);
Form6->SetEdit();
Form6->ColorCheckBox->Checked=AllBlack;
Form6->PrintAllAxisCheckBox->Checked=PrintAllAxis;
for(int i=0;i<maxgraph;i++)
 {
 Form6->PrintedAxis[i]=PrintedAxis[i];
 }
if(Form6->ShowModal()==mrOk)
{
ListWidth=StrToInt(Form6->WidthEdit->Text);
ListHeight=StrToInt(Form6->HeightEdit->Text);
ListLeft=StrToInt(Form6->LeftEdit->Text);
ListTop=StrToInt(Form6->TopEdit->Text);
DPI=StrToInt(Form6->DPIEdit->Text);
GirdWidth=StrToInt(Form6->GirdEdit->Text);
AxisWidth=StrToInt(Form6->AxisEdit->Text);
GraphWidth=StrToInt(Form6->GraphEdit->Text);
AllBlack=Form6->ColorCheckBox->Checked;
PrintAllAxis=Form6->PrintAllAxisCheckBox->Checked;
int a=StrToInt(Form6->StepXEdit->Text);
if(a<10) StepX=10;
else if(a>200)StepX=200;
else StepX=a;
a=StrToInt(Form6->StepYEdit->Text);
if(a<20) StepY=20;
else if(a>200)StepY=200;
else StepY=a;
for(int i=0;i<maxgraph;i++)
 {
 PrintedAxis[i]=Form6->PrintedAxis[i];
 }
//StepX=StrToInt(Form6->StepXEdit->Text);
//StepY=StrToInt(Form6->StepYEdit->Text);
}
delete Form6;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::GrapherItemClick(TObject *Sender)
{
//if(MDIChildCount<=0) return;
TGrapherForm *Form8=new TGrapherForm(this);
Form8->Width=210;
Form8->Height=140;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OffSignalsClick(TObject *Sender)
{
TAlarmListForm *Form11=new TAlarmListForm(this);
 Form11->ShowModal();
delete Form11;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AllVisibleClick(TObject *Sender)
{
if(static_cast<TChildForm*>(ActiveMDIChild)->Type==1)
 {
 for(int i=0;i<maxparam;i++)
  {
  if(static_cast<TChildForm*>(ActiveMDIChild)->PicturiePresent[i])
   static_cast<TChildForm*>(ActiveMDIChild)->Picturies[i]->Visible=true;
  if(static_cast<TChildForm*>(ActiveMDIChild)->ClipPresent[i])
   static_cast<TChildForm*>(ActiveMDIChild)->Clip[i]->Visible=true;
  }
 }
}
//---------------------------------------------------------------------------

void TMainForm::SaveAlarmFunc()
{
TDateTime dat;
TDataConteiner** Signal=defPointerToSignals;
TDateTime CurTime=TDateTime::CurrentDateTime();
//float const Diff=(float)AlarmDiff/100;//{Differences between last and present value of signals. 5%
//int ParamNumb;
//int CurrentAdam,CurrentChannel;
float CurrentValue;
//MainForm->StatusBar->SimpleText="������ ���� ������";
//MainForm->StatusBar->SimplePanel=true;
DataModule1->AlarmTable->Active=true;
try
{
//DataModule1->KanalsTable->DisableControls();
DataModule1->AlarmTable->DisableControls();
//DataModule1->KanalsTable->First();
for(unsigned int i=0;i<maxsignal;i++)
if(Signal[i])
if(Signal[i]->CritSignal)
{
//if((Signal[i]->SaveAlarm)&&/*(Signal[i]->OutValue!=0)&&*/
//((Signal[i]->LastAlarm*(1-Diff)>Signal[i]->OutValue)|(Signal[i]->LastAlarm*(1+Diff)<Signal[i]->OutValue)|
//(CurTime-Signal[i]->LastAlarmTime>(TDateTime)(0.2/24))))
if((Signal[i])&&(Signal[i]->SaveOrNo(CurTime,1)))
  {
  CurrentValue=Signal[i]->OutValue;
  dat=Date();
  DataModule1->AlarmTable->Append();
  DataModule1->AlarmTable->FieldValues["Date"]=dat;
  DataModule1->AlarmTable->FieldValues["Hours"]=StrToInt(Time().FormatString("hh"));
  DataModule1->AlarmTable->FieldValues["Minuts"]=StrToInt(Time().FormatString("nn"));
  DataModule1->AlarmTable->FieldValues["Seconds"]=StrToInt(Time().FormatString("ss"));
  DataModule1->AlarmTable->FieldValues["Numb"]=i;
  DataModule1->AlarmTable->FieldValues["Value"]=CurrentValue;
  DataModule1->AlarmTable->Post();
  Signal[i]->LastAlarm=CurrentValue;
  //Signal[i]->LastAlarmTime=CurTime;
  }
}
DataModule1->AlarmTable->EnableControls();
}
catch(...)
{
//DataModule1->KanalsTable->EnableControls();
DataModule1->AlarmTable->EnableControls();
//for(int i=0;i<MDIChildCount;i++)
//static_cast<TChildForm*>(MDIChildren[i])->Timer1->Enabled=true;
//MainForm->StatusBar->SimplePanel=false;
}
}
void __fastcall TMainForm::AlarmTimerTimer(TObject *Sender)
{
SaveAlarmFunc();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N7Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SatAdrItemClick(TObject *Sender)
{
TAdrForm *Form18=new TAdrForm(this);
Form18->ShowModal();
delete Form18;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::CheckSignalTimerTimer(TObject *Sender)
{
 /*int ad,chan;
 ParamName="";
 SetGroupIndex.Clear();
 for(ad=0;ad<maxadam;ad++)
 for(chan=0;chan<maxchannel;chan++)
  {
  if(MainForm->PresentParam[ad][chan]);//Synchronize(ScanStep);
  else MainForm->CritSignals[ad][chan]=false;
  }*/
 //MainForm->SetsAd.Clear();
 //MainForm->SetsChan.Clear();
 //SomeAlarm=false;
 unsigned int Numb;
 for(Numb=0;Numb<maxsignal;Numb++)if(defPointerToSignals[Numb])defPointerToSignals[Numb]->CheckSignal();
   CheckSignals();
   ViewAlarm();

 if(MaxSoundNumber<=0)
   {
   MaxSoundNumber=0;
   EnableAddSound=true;
   }
 //else EnableAddSound=false;
/*if((TerminateMy)&&(PresentThread))Thread->Terminate();
if((!TerminateMy)&&(!PresentThread))
{
MainForm->Thread=new TAdConnThread(true);
MainForm->Thread->Suspended=false;
}*/
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Button1Click(TObject *Sender)
{
//MainForm->Thread->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button2Click(TObject *Sender)
{
/*ComName[0]='C';
ComName[1]='O';
ComName[2]='M';
ComName[3]='3';
ComName[4]=0;
PComName=ComName;
PortHandle=CreateFile(PComName,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,
FILE_ATTRIBUTE_NORMAL,NULL);
//int c=GetLastError();
SetupComm(PortHandle,100,10);
//c=GetLastError();
//DCBState=new TDCB;
DCB.BaudRate=9600;
DCB.ByteSize=8;
DCB.Parity=EVENPARITY;
DCB.StopBits=ONESTOPBIT;
SetCommState(PortHandle,&DCB);
TimeOutSt.ReadIntervalTimeout=250;
TimeOutSt.ReadTotalTimeoutMultiplier=100;
TimeOutSt.ReadTotalTimeoutConstant=100;
TimeOutSt.WriteTotalTimeoutMultiplier=100;
TimeOutSt.WriteTotalTimeoutConstant=100;
SetCommTimeouts(PortHandle,&TimeOutSt);//*/
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button3Click(TObject *Sender)
{
//CloseHandle(PortHandle);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button4Click(TObject *Sender)
{
/*AnsiString asd;
asd=Edit1->Text;
for(int i=1;i<5;i++)
Message[i-1]=asd[i];
Message[4]=13;
Message[5]=0;
PMessage=Message;
int ButesNumb=6;
 WriteFile(PortHandle,PMessage,ButesNumb,&BytesWritten,NULL);
 for(int i=0;i<10;i++)Respond[i]=0;
 PRespond=Respond;
 ClearCommError(PortHandle,&Errors,&Stat);
ButesNumb=9;
  bool h=ReadFile(PortHandle,PRespond,9,&BytesReaden,NULL);
asd="";
for(int i=2;i<8;i++)asd+=Respond[i];
Edit2->Text=asd;                       */
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button5Click(TObject *Sender)
{
/*MainForm->Thread=new TAdConnThread(true);
MainForm->Thread->Suspended=false;*/
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N9Click(TObject *Sender)
{
try
{
DataModule1->StatistTable->Active=false;
DataModule1->StatistTable->Exclusive=true;
//DataModule1->StatistTable->Active=true;
DataModule1->StatistTable->
AddIndex("","Date;Hours;Minuts;Seconds;Numb",TIndexOptions()<<ixUnique<<ixPrimary,"");
//DataModule1->StatistTable->Active=true;
//DataModule1->StatistTable->DeleteIndex("ByParam");
/*DataModule1->StatistTable->
AddIndex("ByParam","Numb",TIndexOptions()<<ixUnique<<ixCaseInsensitive,"");*/
DataModule1->StatistTable->Exclusive=false;
DataModule1->StatistTable->Active=true;
Application->MessageBox("������� ������� �������",
"���������",MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL);
}
catch(...)
{
DataModule1->StatistTable->Active=false;
DataModule1->StatistTable->Exclusive=false;
DataModule1->StatistTable->Active=true;
Application->MessageBox("��� �������� ����� �������� ���������� ������� ������� ������",
"���������",MB_OK|MB_ICONERROR|MB_APPLMODAL);
}
//*/
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N10Click(TObject *Sender)
{
try
{
DataModule1->ReservStatTable->Active=false;
DataModule1->ReservStatTable->Exclusive=true;
//DataModule1->StatistTable->Active=true;
DataModule1->ReservStatTable->
AddIndex("","Date;Hours;Minuts;Seconds;Numb",TIndexOptions()<<ixUnique<<ixPrimary,"");
//DataModule1->StatistTable->Active=true;
//DataModule1->StatistTable->DeleteIndex("ByParam");
/*DataModule1->StatistTable->
AddIndex("ByParam","Numb",TIndexOptions()<<ixUnique<<ixCaseInsensitive,"");*/
DataModule1->ReservStatTable->Exclusive=false;
DataModule1->ReservStatTable->Active=true;
Application->MessageBox("������� ������� �������",
"���������",MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL);
}
catch(...)
{
DataModule1->ReservStatTable->Active=false;
DataModule1->ReservStatTable->Exclusive=false;
DataModule1->ReservStatTable->Active=true;
Application->MessageBox("��� �������� ����� �������� ���������� ������� ������� ������",
"���������",MB_OK|MB_ICONERROR|MB_APPLMODAL);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N12Click(TObject *Sender)
{
try
{
DataModule1->AlarmTable->Active=false;
DataModule1->AlarmTable->Exclusive=true;
//DataModule1->StatistTable->Active=true;
DataModule1->AlarmTable->
AddIndex("","Date;Hours;Minuts;Seconds;Numb",TIndexOptions()<<ixUnique<<ixPrimary,"");
//DataModule1->StatistTable->Active=true;
//DataModule1->StatistTable->DeleteIndex("ByParam");
/*DataModule1->StatistTable->
AddIndex("ByParam","Numb",TIndexOptions()<<ixUnique<<ixCaseInsensitive,"");*/
DataModule1->AlarmTable->Exclusive=false;
DataModule1->AlarmTable->Active=true;
Application->MessageBox("������� ������� �������",
"���������",MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL);
}
catch(...)
{
DataModule1->AlarmTable->Active=false;
DataModule1->AlarmTable->Exclusive=false;
DataModule1->AlarmTable->Active=true;
Application->MessageBox("��� �������� ����� �������� ���������� ������� ������� ������",
"���������",MB_OK|MB_ICONERROR|MB_APPLMODAL);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetRtsBtnClick(TObject *Sender)
{
EscapeCommFunction(AdConnThread->PortHandle[0],SETRTS);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClrRtsBtnClick(TObject *Sender)
{
EscapeCommFunction(AdConnThread->PortHandle[0],CLRRTS);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetDtrBtnClick(TObject *Sender)
{
EscapeCommFunction(AdConnThread->PortHandle[0],SETDTR);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClrDtrBtnClick(TObject *Sender)
{
EscapeCommFunction(AdConnThread->PortHandle[0],CLRDTR);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::NewItemClick(TObject *Sender)
{
TChildForm *Forma2;
Forma2=new TChildForm(this);
//FanForm->Show();
ShaxtMenu->Enabled=false;
static_cast<TChildForm*>(ActiveMDIChild)->PrepareItemClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveDataButtonClick(TObject *Sender)
{
DataBaseTimerTimer(DataBaseTimer);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetPaused(bool Value)
{
FPaused=Value;
if(Value)
 {
 State.CheckSignal=CheckSignalTimer->Enabled;
 CheckSignalTimer->Enabled=false;
 State.SaveData=DataBaseTimer->Enabled;
 DataBaseTimer->Enabled=false;
 State.SaveAlarm=AlarmTimer->Enabled;
 AlarmTimer->Enabled=false;
 AdConnThread->Suspended=true;
 for(int i=0;((i<ChCount)&&(i<MDIChildCount));i++)
  {
  if(MDIChildType[i]==1)
   {
   State.ChForm[i]=static_cast<TChildForm*>(MDIChildren[i])->Timer1->Enabled;
   static_cast<TChildForm*>(MDIChildren[i])->Timer1->Enabled=false;
   }
  else if(MDIChildType[i]==2)
   {
   State.ChForm[i]=static_cast<TGrapherForm*>(MDIChildren[i])->Timer1->Enabled;
   static_cast<TGrapherForm*>(MDIChildren[i])->Timer1->Enabled=false;
   }
  }
 }
else
 {
 CheckSignalTimer->Enabled=State.CheckSignal;
 DataBaseTimer->Enabled=State.SaveData;
 AlarmTimer->Enabled=State.SaveAlarm;
 AdConnThread->Suspended=false;
 for(int i=0;((i<ChCount)&&(i<MDIChildCount));i++)
  {
  if(MDIChildType[i]==1)
   {
  static_cast<TChildForm*>(MDIChildren[i])->Timer1->Enabled=State.ChForm[i];
   }
  else if(MDIChildType[i]==2)
   {
   static_cast<TGrapherForm*>(MDIChildren[i])->Timer1->Enabled=State.ChForm[i];
   }
  }
 }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::IntegItemClick(TObject *Sender)
{
TIntegrForm* Form1=new TIntegrForm(this);
Form1->ShowModal();
delete Form1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WorkTimeItemClick(TObject *Sender)
{
TIntegrForm* Form1=new TIntegrForm(this);
Form1->ShowModal();
delete Form1;
}
//---------------------------------------------------------------------------




