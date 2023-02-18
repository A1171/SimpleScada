//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DataUnit.h"
#include "MainUnut.h"
#include "Function.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDataModule1 *DataModule1;
//---------------------------------------------------------------------------
__fastcall TDataModule1::TDataModule1(TComponent* Owner)
        : TDataModule(Owner)
{
for(int i=0;i<maxsignal;i++)Signal[i]=0;
InitialDataBases();
Proc2Var1=0;Proc2Var2=0;AlreadyCalled=0;
}
//---------------------------------------------------------------------------
void TDataModule1::InitialDataBases()
{
KanalsTable->Active=false;
StatistTable->Active=false;
CalcSignTable->Active=false;
AlarmTable->Active=false;
WhoreTable->Active=false;
CaptionsTable->Active=false;
KanalsTable->DatabaseName=MainForm->ProgramDir;
KanalsTable->TableName=MainForm->ProgramDir+"\\adams3.db";
StatistTable->DatabaseName=MainForm->ProgramDir;
StatistTable->TableName=MainForm->ProgramDir+"\\Data1.db";
CalcSignTable->DatabaseName=MainForm->ProgramDir;
CalcSignTable->TableName=MainForm->ProgramDir+"\\CalcSign.db";
AlarmTable->DatabaseName=MainForm->ProgramDir;
AlarmTable->TableName=MainForm->ProgramDir+"\\Alarm.db";
CaptionsTable->DatabaseName=MainForm->ProgramDir;
CaptionsTable->TableName=MainForm->ProgramDir+"\\Captions.db";
WhoreTable->DatabaseName=MainForm->ProgramDir;
CaptionsTable->Active=true;
KanalsTable->Active=true;
StatistTable->Active=true;
CalcSignTable->Active=true;
AlarmTable->Active=true;
KanName="\\adams3.db";
StatistTable->Active=true;
ReservKanTable->DatabaseName=MainForm->ProgramDir+"\\ReservDB";
ReservKanTable->TableName="Adams3.DB";
ReservKanTable->Active=true;
/*for(int i=0;i<maxsignal;i++)
 {
 Signal[i]=0;
 }*/
FillMemory(ExternalDevices,sizeof(ExternalDevices),0xFF);
}
//---------------------------------------------------------------------------
bool TDataModule1::FindRecord1(int Adam,int Channel)
{
int Ad,Kan;
KanalsTable->Active=true;
KanalsTable->First();
//KanalsTable->Prior();
if(!DataModule1->KanalsTable->Eof)
do
 {
 Ad=KanalsTable->FieldValues["Adam"];
 Kan=KanalsTable->FieldValues["Kanal"];
 if((Ad==Adam)&&(Kan==Channel)) return true;
 }
while(DataModule1->KanalsTable->FindNext());
if((Ad==Adam)&&(Kan==Channel)) return true;
return false;
}



void __fastcall TDataModule1::DataModule1Destroy(TObject *Sender)
{
for(int i=0;i<maxsignal;i++)if(Signal[i]){delete Signal[i];Signal[i]=0;}
KanalsTable->CancelUpdates();
CalcSignTable->CancelUpdates();
//CopyToReserve();
//RefreshStat();
//RefreshAlarm();
}
//---------------------------------------------------------------------------
float TDataModule1::GetIntProc(unsigned short Numb,float Par1,float Par2)
{
switch(Numb)
 {
 case 1:return IntProc1(Par1,Par2);
 case 2:return IntProc2(Par1,Par2);
 case 3:return IntProc3(Par1,Par2);
 case 4:return IntProc4(Par1,Par2);
 case 5:return IntProc5(Par1,Par2);

 }
}
//---------------------------------------------------------------------------
float TDataModule1::IntProc1(float Par1,float Par2)//temperature graphic
{
if(Par1>10)return 33.2;
else if(Par1>5)return 40.6-Par1*7.4/5;
else if(Par1>0)return 47.6-Par1*7/5;
else if(Par1>-5)return 54.2-Par1*6.6/5;
else if(Par1>-10)return 60.7-Par1*6.5/5;
else if(Par1>-15)return 66.9-Par1*6.2/5;
else if(Par1>-20)return 73-Par1*6.1/5;
else if(Par1>-25)return 78.9-Par1*5.9/5;
else if(Par1>-30)return 84.8-Par1*5.9/5;
else if(Par1>-35)return 90.5-Par1*5.7/5;
else return 90.5;
/*if(Par1>10)return 0;
else if((Par1<=10)&&(Par1>=-15))return 70;
else if((Par1<-15)&&(Par1>=-40))return (70-(15+Par1)*25/25);
else return 95;*/
}
float TDataModule1::IntProc2(float Par1,float Par2)//hour integral. Par1- val, Par2- size in seconds
{
if(!AlreadyCalled)CurDateTime=CurDateTime.CurrentDateTime();
if(double(CurDateTime)-double(int(CurDateTime))<double(3.0/24.0/60.0))Proc2Var1=0;
float CurVal=Proc2Var1;
if(double(CurDateTime)>Proc2Var2)CurVal=Proc2Var1+Par1*(CurDateTime-Proc2Var2)*24*3600/Par2;
Proc2Var1=CurVal;Proc2Var2=CurDateTime;
AlreadyCalled=true;
return CurVal;
}
//---------------------------------------------------------------------------
float TDataModule1::IntProc3(float Par1,float Par2)
{
return 0;
}
//---------------------------------------------------------------------------
float TDataModule1::IntProc4(float Par1,float Par2)
{
return 0;
}
//---------------------------------------------------------------------------
float TDataModule1::IntProc5(float Par1,float Par2)
{
return 0;
}


  