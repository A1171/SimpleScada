//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "InteForm.h"
#include "Constant.h"
#include "DataUnit.h"
#include "MainUnut.h"
#include "Function.h"
//#include <SysUtils.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TIntegrForm *IntegrForm;
//---------------------------------------------------------------------------
__fastcall TIntegrForm::TIntegrForm(TComponent* Owner)
        : TForm(Owner)
{
Absent="?????";
MinValEdit->Text=Absent;
MaxValEdit->Text=Absent;
StartDateMEdit->Text=Date();
EndDateMEdit->Text=Date();
StartTimeMEdit->Text="00:00";                    //TDateTime
EndTimeMEdit->Text=Time();
ScaleComboBox->ItemIndex=2;
for(int i=0;i<maxsignal;i++)
if((defPointerToSignals[i])&&(defPointerToSignals[i]->SaveData))
 ParamComboBox->Items->AddObject(defPointerToSignals[i]->Name,defPointerToSignals[i]);
}
//---------------------------------------------------------------------------
void __fastcall TIntegrForm::StartDateUpDownClick(TObject *Sender,
      TUDBtnType Button)
{
TUpDown* Sender1=static_cast<TUpDown*>(Sender);
TDateTime Dat1=StartDateMEdit->Text;//min
TDateTime Dat2=EndDateMEdit->Text;//max
if(Sender1==StartDateUpDown)
 {
 if(Button==0)
  {
  if((Dat1+1>Date())||(Dat1+1>Dat2))return;
  else
   {
   Dat1+=1;
   StartDateMEdit->Text=Dat1;
   }
  }
 else
  {
  Dat1-=1;
  StartDateMEdit->Text=Dat1;
  }//*/
 }
else if(Sender1==EndDateUpDown)
 {
 if(Button==0)
  {
  if((Dat2+1)>Date())return;
  else
   {
   Dat2+=1;
   EndDateMEdit->Text=Dat2;
   }
  }
 else
  {
  if(Dat2-1<Dat1)return;
  else
   {
   Dat2-=1;
   EndDateMEdit->Text=Dat2;
   }
  }//*/
 }
}
//---------------------------------------------------------------------------
void __fastcall TIntegrForm::StartTimeUpDownClick(TObject *Sender,
      TUDBtnType Button)
{
/*TUpDown* Sender1=static_cast<TUpDown*>(Sender);
TDateTime Dat1=StartTimeMEdit->Text;//min
TDateTime Dat2=EndTimeMEdit->Text;//max
if(Sender1==StartTimeUpDown)
 {
 if(Button==0)
  {
  if((Dat1>=Date())||(Dat1>=Dat2))return;
  else
   {
   Dat1+=1/24;
   StartTimeMEdit->Text=Dat1;
   }
  }
 else
  {
  if(Dat1<=Dat1.operator double(0))return;
  else if(Dat1<=1/24)Dat1=0;
  else Dat1-=1/24;
  StartTimeMEdit->Text=Dat1;
  }
 }
else if(Sender1==EndTimeUpDown)
 {
 if(Button==0)
  {
  if((Dat2)>1)return;
  else
   {
   Dat2+=1/24;
   EndTimeMEdit->Text=Dat2;
   }
  }
 else
  {
  if(Dat2<=Dat1)return;
  else
   {
   if(Dat2<=Dat1+1/24)Dat2=Dat1;
   else Dat2-=1/24;
   EndTimeMEdit->Text=Dat2;
   }
  }
 }*/
}
//---------------------------------------------------------------------------
void __fastcall TIntegrForm::Button1Click(TObject *Sender)
{
if(ParamComboBox->Text=="???????? ????????")
 {
 ShowMessage("???????? ????????");
 return;
 }
TTable *Table=DataModule1->StatistTable;
AnsiString Filter="";
{
TDateTime SelectMinDate=StartDateMEdit->Text;
TDateTime SelectMaxDate=EndDateMEdit->Text;
//TDateTime SelectMinTime=StartTimeMEdit->Text;
//TDateTime SelectMaxTime=EndTimeMEdit->Text;
 if(SelectMinDate>SelectMaxDate)
  {
  SelectMaxDate=SelectMinDate;
  StartDateMEdit->Text=EndDateMEdit->Text;
  }
if(SelectMinDate==SelectMaxDate)
 {
Filter+="(Date>='"+SelectMinDate.DateString()+"')and(Date<='"+SelectMaxDate.DateString()+"')";
Filter+="and(Hours>='"+StartTimeMEdit->Text.SubString(1,2)+"')and(Hours<='"+EndTimeMEdit->Text.SubString(1,2)+"')";
Filter+="and(Minuts>='"+StartTimeMEdit->Text.SubString(4,2)+"')and(Minuts<='"+EndTimeMEdit->Text.SubString(4,2)+"')";
Filter+="and(Numb='"+IntToStr(static_cast<TDataConteiner*>(ParamComboBox->Items->Objects[ParamComboBox->ItemIndex])->Number)+"')";
 }
else
 {
Filter+="((Date='"+SelectMinDate.DateString()+"')and(Hours>='"+StartTimeMEdit->Text.SubString(1,2)
+"')and(Minuts>='"+StartTimeMEdit->Text.SubString(4,2)+"')";
Filter+="or(Date='"+SelectMaxDate.DateString()+"')and(Hours<='"+EndTimeMEdit->Text.SubString(1,2)
+"')and(Minuts<='"+EndTimeMEdit->Text.SubString(4,2)+"')";
Filter+="or(Date>'"+SelectMinDate.DateString()+"')and(Date<'"+SelectMaxDate.DateString()+"'))";
Filter+="and(Numb='"+IntToStr(static_cast<TDataConteiner*>(ParamComboBox->Items->Objects[ParamComboBox->ItemIndex])->Number)+"')";
 }
}
bool SaveData=MainForm->DataBaseTimer->Enabled;
MainForm->DataBaseTimer->Enabled=false;
DataModule1->StatistTable->Filter=Filter;
if(!Table->Filtered)
 Table->Filtered=true;
Table->FindFirst();
unsigned int RecordCount=Table->RecordCount,DataBasePoint=0;
if(RecordCount<2)
 {
 MainForm->DataBaseTimer->Enabled=SaveData;
 Table->Filtered=false;
 ShowMessage("? ???? ?????? ??????????? ??????");
 return;
 }
bool Flag=false;
float Value=0,LastValue=0,LastValue1=0;
double Summa=0;
unsigned short Ho,Min,Sec,MSec;
TDateTime Date,LastDate=StartDateMEdit->Text,SwitchedOff=0,Worked=0,Wait=0;
{
Ho=StrToInt(StartTimeMEdit->Text.SubString(1,2));
Min=StrToInt(StartTimeMEdit->Text.SubString(4,2));
TDateTime time1(Ho,Min,0,0);
LastDate+=time1;
}
float LowLimit=0,HighLimit=0;
bool LowPresent=true,HighPresent=true;
{
bool Fail=false;
LowLimit=TransformStr(MinValEdit->Text,Fail);
if(Fail)
 {
 if(MinValEdit->Text==Absent)LowPresent=false;
 else
  {
  ShowMessage("??????????? ?????? ????? ???????? ????????? ????????");
  return;
  }
 }
HighLimit=TransformStr(MaxValEdit->Text,Fail);
if(Fail)
 {
 if(MaxValEdit->Text==Absent)HighPresent=false;
 else
  {
  ShowMessage("???????????? ?????? ????? ???????? ????????? ????????");
  return;
  }
 }
}
//All limits present
//Low limit is absent
//High limit is absent
//All limits absent
do
 {
 Date=Table->FieldByName("Date")->AsDateTime;
 Ho=Table->FieldByName("Hours")->AsInteger;
 Min=Table->FieldByName("Minuts")->AsInteger;
 Sec=Table->FieldByName("Seconds")->AsInteger;
 TDateTime time1(Ho,Min,Sec,0);
 Date+=time1;
 Value=Table->FieldByName("Value")->AsFloat;
 if(static_cast<TDataConteiner*>(ParamComboBox->Items->Objects[ParamComboBox->ItemIndex])->Number!=15)
 {
 if((((Date-LastDate)<(TDateTime)(0.8/24))&&(Value!=0)&&(Date>LastDate))&&
 ((LowPresent&&(Value>=LowLimit))||!LowPresent)&&
 ((HighPresent&&(Value<=HighLimit))||!HighPresent))
  {
  Summa+=((Value+LastValue)*(double)(Date-LastDate))/2;
  Worked+=(double)(Date-LastDate);
  }
 else //if(Date>LastDate)
  {
  SwitchedOff+=Date-LastDate;
  if((Date-LastDate)<(TDateTime)(0.8/24))Wait+=(double)(Date-LastDate);
  }
 }
 else
 {
 if((((Date-LastDate)<(TDateTime)(0.8/24))&&((Value!=0)||(LastValue!=0))&&(Date>LastDate))&&
 ((LowPresent&&(Value>=LowLimit))||!LowPresent)&&
 ((HighPresent&&(Value<=HighLimit))||!HighPresent))
  {
  if(LastValue!=0)
   {
   Summa+=((Value+LastValue)*(double)(Date-LastDate))/2;
   Worked+=(double)(Date-LastDate);
   }
  }
 else //if(Date>LastDate)
  {
  SwitchedOff+=Date-LastDate;
  if((Date-LastDate)<(TDateTime)(0.8/24))Wait+=(double)(Date-LastDate);
  }
 }
 LastValue1=LastValue;
 LastValue=Value;
 LastDate=Date;
 Flag=Table->FindNext();
 ProgressBar->Position=(DataBasePoint++)*ProgressBar->Max/RecordCount;
 }
while((Flag)&&(!Table->Eof));
LastDate=StartDateMEdit->Text;
if(Date<LastDate)SwitchedOff+=Date-LastDate;
MainForm->DataBaseTimer->Enabled=SaveData;
Table->Filtered=false;
float Summa1=0;
switch(ScaleComboBox->ItemIndex)
{
case 0:
break;
case 1:Summa1=Summa*24;
break;
case 2:Summa1=Summa*1440;
break;
case 3:Summa1=Summa*86400;
}
//unsigned short Ho,Min,Sec,MSec;
Worked.DecodeTime(&Ho,&Min,&Sec,&MSec);
RezRichEdit->Clear();
RezRichEdit->Lines->Add("?????????");
AnsiString  Line="";
Line="??????????? ???????? "+FloatToStr(Summa1);
RezRichEdit->Lines->Add(Line);
//bool Days,Hours;
//if(int(Worked)>=1)Days=true;if(Worked)
Line="????? ?????? ";
if(int(Worked)>=1){Line+=IntToStr(Worked);Line+=" ???? ";}
if(Ho>=1){Line+=IntToStr(Ho);Line+=" ????? ";}
if(Min>=1){Line+=IntToStr(Min);Line+=" ?????.";}
RezRichEdit->Lines->Add(Line);
Line="????? ?????????? ";
SwitchedOff.DecodeTime(&Ho,&Min,&Sec,&MSec);
if(int(SwitchedOff)>=1){Line+=IntToStr(SwitchedOff);Line+=" ???? ";}
if(Ho>=1){Line+=IntToStr(Ho);Line+=" ????? ";}
if(Min>=1){Line+=IntToStr(Min);Line+=" ?????.";}
RezRichEdit->Lines->Add(Line);
Line="??????? ???????? ????????? ?? ????? ?????? "+FloatToStr(Summa/double(Worked));
RezRichEdit->Lines->Add(Line);
ProgressBar->Position=0;
}
//---------------------------------------------------------------------------
/*TIntegrForm::SetMode(unsigned  short Value)
{
switch(Value)
 {
 case 0:
 break;
 case 1:
  Caption="?????? ??????? ??????";
  ScaleLabel->Caption="??????????? ???????? ????????? ??? ??????? ?????????? ????????? ???????";

 break;
 }
} */
void __fastcall TIntegrForm::MaxValEditDblClick(TObject *Sender)
{
MaxValEdit->Text=Absent;
}
//---------------------------------------------------------------------------

void __fastcall TIntegrForm::MinValEditDblClick(TObject *Sender)
{
MinValEdit->Text=Absent;
}
//---------------------------------------------------------------------------




