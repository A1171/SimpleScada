//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SetStat.h"
#include "DataUnit.h"
#include "MainUnut.h"
#include "ReportFo.h"
#include <ComObj.hpp>
#include "SendThre.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cdiroutl"
#pragma resource "*.dfm"
TSetBDForm *SetBDForm;
//---------------------------------------------------------------------------
__fastcall TSetBDForm::TSetBDForm(TComponent* Owner)
        : TForm(Owner)
{
DiffEdit->Text=IntToStr(DiffUpDown->Position);
//DiffUpDown->Enabled=true;
LastIndex=0;
dTimeComboBox->ItemIndex=0;
ParamComboBox->Enabled=CheckBox1->Checked;
MaskEdit->Text=Date();//.FormatString("mm:dd:yy");
TDateTime b=TDateTime(MaskEdit->Text);
DateSort="";//"(Date='"+b.DateString()+"')";

switch(MainForm->SaveFrequenty)
 {
 case 30:dTimeComboBox->ItemIndex=0;
 break;
 case 60:dTimeComboBox->ItemIndex=1;
 break;
 case 300:dTimeComboBox->ItemIndex=2;
 break;
 case 600:dTimeComboBox->ItemIndex=3;
 break;
 case 1800:dTimeComboBox->ItemIndex=4;
 break;
 /*case 3600:dTimeComboBox->ItemIndex=5;
 break;
 case 7200:dTimeComboBox->ItemIndex=6;
 break;
 case 10800:dTimeComboBox->ItemIndex=7;
 break;
 case 14400:dTimeComboBox->ItemIndex=8;*/
 default:dTimeComboBox->ItemIndex=0;
 }
switch(MainForm->SaveAlarmFreq)
 {
 /*case 1:dAlarComboBox->ItemIndex=0;
 break;*/
 case 5:dAlarComboBox->ItemIndex=0;
 break;
 case 10:dAlarComboBox->ItemIndex=1;
 break;
 case 30:dAlarComboBox->ItemIndex=2;
 break;
 default:dAlarComboBox->ItemIndex=0;
 }
DataModule1->KanalsTable->First();
int i=0;
//ParamComboBox->Items="";
/*TObject *Prom=new TObject();
do
 {
 AnsiString Param=DataModule1->KanalsTable->FieldValues["Parametr"];
 bool Pai=DataModule1->KanalsTable->FieldValues["SaveData"];
 if(Pai)  ParamComboBox->Items->AddObject(Param,Prom);
 i++;
 }
while(DataModule1->KanalsTable->FindNext());
delete Prom;*/
for(int i=0;i<maxsignal;i++)
if((defPointerToSignals[i])&&(defPointerToSignals[i]->SaveData))
 ParamComboBox->Items->AddObject(defPointerToSignals[i]->Name,defPointerToSignals[i]);
ParamComboBox->ItemIndex=0;
ParamSort="";
DataModule1->StatistTable->IndexName="";//"ByParam";
AlarmName=DataModule1->AlarmTable->TableName;
StatistName=DataModule1->StatistTable->TableName;
ReservStatName=DataModule1->ReservStatTable->TableName;
DataModule1->AlarmTable->Filtered=false;
DataModule1->StatistTable->Filtered=false;
}
//---------------------------------------------------------------------------
void __fastcall TSetBDForm::EnablCheckBoxClick(TObject *Sender)
{
/*if(EnablCheckBox->Checked)
 {
 dTimeComboBox->Enabled=true;
 }
else
 {
 dTimeComboBox->Enabled=false;
 }*/
}
//---------------------------------------------------------------------------
void __fastcall TSetBDForm::dTimeComboBoxChange(TObject *Sender)
{
switch(dTimeComboBox->ItemIndex)
 {
 case 0:dTime=30;
 break;
 case 1:dTime=60;
 break;
 case 2:dTime=300;
 break;
 case 3:dTime=600;
 break;
 case 4:dTime=1800;
 break;
 /*case 5:dTime=3600;
 break;
 case 6:dTime=7200;
 break;
 case 7:dTime=10800;
 break;
 case 8:dTime=14400;
 break;*/
 default:dTime=30;
 }
switch(dAlarComboBox->ItemIndex)
 {
 /*case 0:dAlarmTime=1;
 break;*/
 case 0:dAlarmTime=5;
 break;
 case 1:dAlarmTime=10;
 break;
 case 2:dAlarmTime=30;
 break;
 default:dAlarmTime=5;
 }
}
void __fastcall TSetBDForm::dAlarComboBoxChange(TObject *Sender)
{
switch(dAlarComboBox->ItemIndex)
 {
 case 0:dAlarmTime=5;
 break;
 case 1:dAlarmTime=10;
 break;
 case 2:dAlarmTime=30;
 break;
 default:dAlarmTime=5;
 }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TSetBDForm::TimeCheckBoxClick(TObject *Sender)
{

TDateTime b=TDateTime(MaskEdit->Text);
if(TimeCheckBox->Checked)
 {
 //MaskEdit->Enabled=true;
 DateSort="(Date>='"+b.DateString()+"')and(Date<='"+b.DateString()+"')";
 NewMask();
 }
else
 {
 //MaskEdit->Enabled=false;
 if(!CheckBox1->Checked)
  {
  DataModule1->StatistTable->Filtered=false;
  }
 DateSort="";
 NewMask();
 }
}
//---------------------------------------------------------------------------


void __fastcall TSetBDForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
DataModule1->StatistTable->Active=false;
DataModule1->AlarmTable->Active=false;
DataModule1->ReservStatTable->Active=false;
DataModule1->StatistTable->TableName=StatistName;
DataModule1->AlarmTable->TableName=AlarmName;
DataModule1->ReservStatTable->TableName=ReservStatName;
DataModule1->StatistTable->Active=true;
DataModule1->AlarmTable->Active=true;
DataModule1->ReservStatTable->Active=true;
DataModule1->StatistTable->Filtered=false;
switch(TabControl->TabIndex)
 {
 case 0:
 MainForm->DataDiff=StrToInt(DiffEdit->Text);
 break;
 case 1:
 MainForm->AlarmDiff=StrToInt(DiffEdit->Text);
 }

}
//---------------------------------------------------------------------------

void __fastcall TSetBDForm::PreviewSButtonClick(TObject *Sender)
{
//MainForm->EnablSaveData=MainForm->DataBaseTimer->Enabled;
//MainForm->DataBaseTimer->Enabled=false;
if(ParamSort!="")
MainForm->PromCaption="Распечатка "+DataModule1->StatistTable->FieldValues["Parametr"];
else MainForm->PromCaption="Распечатка всех параметров";
TRepForm *Form12=new TRepForm(this);
DataModule1->StatistTable->DisableControls();
try
{
Form12->QuickRep->PreviewModal();
DataModule1->StatistTable->EnableControls();
}
catch(...)
{
DataModule1->StatistTable->EnableControls();
}
delete Form12;
//MainForm->DataBaseTimer->Enabled=MainForm->EnablSaveData;
}                                             
//---------------------------------------------------------------------------

void __fastcall TSetBDForm::PrintSButtonClick(TObject *Sender)
{
//MainForm->EnablSaveData=MainForm->DataBaseTimer->Enabled;
//MainForm->DataBaseTimer->Enabled=false;
if(ParamSort!="")
MainForm->PromCaption="Распечатка "+DataModule1->StatistTable->FieldValues["Parametr"];
else MainForm->PromCaption="Распечатка всех параметров";
DataModule1->StatistTable->DisableControls();
TRepForm *Form13=new TRepForm(this);
Form13->QuickRep->Print();
DataModule1->StatistTable->EnableControls();
delete Form13;
//MainForm->DataBaseTimer->Enabled=MainForm->EnablSaveData;
}
//---------------------------------------------------------------------------

void __fastcall TSetBDForm::CheckBox1Click(TObject *Sender)
{
if(CheckBox1->Checked)
 {
 ParamComboBox->Enabled=true;
 SetParamMask();
 DataModule1->StatistTable->IndexName="";
 NewMask();
 }
else
 {
 ParamComboBox->Enabled=false;
 //CheckBox1->Checked=true;
 if(!TimeCheckBox->Checked)
  {
  DataModule1->StatistTable->Filtered=false;
  }
 ParamSort="";
 DataModule1->StatistTable->IndexName="ByParam";
 NewMask();
 }
}
//---------------------------------------------------------------------------

void __fastcall TSetBDForm::ParamComboBoxChange(TObject *Sender)
{
SetParamMask();
NewMask();
}
//---------------------------------------------------------------------------
void TSetBDForm::NewMask(void)
{
AnsiString And="and";
DataModule1->StatistTable->Filtered=false;
if((ParamSort=="")||(DateSort==""))
 {
 DataModule1->StatistTable->Filter=ParamSort+DateSort;
 }
else
 {
 DataModule1->StatistTable->Filter=ParamSort+"and"+DateSort;
 }
DataModule1->StatistTable->Filtered=true;
}
//----------------------------------------------------------------------------
void TSetBDForm::SetParamMask(void)
{
int Number=-1;
 for(unsigned int i=0;i<maxsignal;i++)            //DataModule1->Signal
 // for(int j=0;j<maxchannel;j++)
  if(defPointerToSignals[i])
   {
   if(defPointerToSignals[i]->Name==ParamComboBox->Text)
    Number=i;
   }
 if(Number!=-1)
 ParamSort="(Numb='"+IntToStr(Number)+"')";
 else ParamSort="";
}
//----------------------------------------------------------------------------
void __fastcall TSetBDForm::TabControlChange(TObject *Sender)
{
if(LastIndex==0)
  {
  MainForm->DataDiff=StrToInt(DiffEdit->Text);
  }
 else if(LastIndex==1)
  {
  MainForm->AlarmDiff=StrToInt(DiffEdit->Text);
  }
switch(TabControl->TabIndex)
 {
 case 0:
 DiffEdit->Text=IntToStr(MainForm->DataDiff);
 break;
 case 1:
 DiffEdit->Text=IntToStr(MainForm->AlarmDiff);
 break;
 case 2:;

 }
if(TabControl->TabIndex==0)
 {//Select Statist
 DiffEdit->Visible=true;
 DiffLabel->Visible=true;
 DiffUpDown->Visible=true;
 dAlarComboBox->Visible=false;
 dTimeComboBox->Visible=false;//true;
 EnablCheckBox->Visible=false;
 Label1->Visible=false;//true;
 Label2->Visible=false;//true;
 dTimeComboBox->Visible=true;
 DataModule1->StatistTable->Active=false;
 DataModule1->AlarmTable->Active=false;
 //AlarmName=AlarmTable->TableName;
 DataModule1->StatistTable->TableName=StatistName;
 DataModule1->StatistTable->Active=true;
 }
if(TabControl->TabIndex==1)
 {//Select Alarm
 DiffEdit->Visible=true;
 DiffLabel->Visible=true;
 DiffUpDown->Visible=true;

 dAlarComboBox->Visible=false;//true;
 dTimeComboBox->Visible=false;
 EnablCheckBox->Visible=false;
 Label1->Visible=false;//true;
 Label2->Visible=false;//true;
 dTimeComboBox->Visible=false;
 DataModule1->StatistTable->Active=false;
 DataModule1->AlarmTable->Active=false;
 //AlarmName=AlarmTable->TableName;
 DataModule1->StatistTable->TableName=AlarmName;
 DataModule1->StatistTable->Active=true;
 }
if(TabControl->TabIndex==2)
 {//Select Alarm
 DiffEdit->Visible=false;
 DiffLabel->Visible=false;
 DiffUpDown->Visible=false;
  dAlarComboBox->Visible=false;
 dTimeComboBox->Visible=false;
 EnablCheckBox->Visible=false;
 Label1->Visible=false;
 Label2->Visible=false;
 dTimeComboBox->Visible=false;
 DataModule1->StatistTable->Active=false;
 DataModule1->ReservStatTable->Active=false;
 //AlarmName=AlarmTable->TableName;
 DataModule1->StatistTable->TableName=ReservStatName;
 DataModule1->StatistTable->Active=true;
 }
LastIndex=TabControl->TabIndex;
}
//---------------------------------------------------------------------------





void __fastcall TSetBDForm::SpeedButton1Click(TObject *Sender)
{
AnsiString DateFilter="",ParamFilter="",Filter="";
if((TimeCheckBox->Checked)&&(MaskEdit->Text!=""))
 DateFilter="(Date='"+MaskEdit->Text+"')";
else DateFilter="";
if(CheckBox1->Checked)
 ParamFilter="(Numb='"+IntToStr(static_cast<TDataConteiner*>(ParamComboBox->Items->Objects[ParamComboBox->ItemIndex])->Number)
 +"')";
else ParamFilter="";
if((DateFilter!="")&&(ParamFilter!="")) Filter=DateFilter+"and"+ParamFilter;
else if(DateFilter!="") Filter=DateFilter;
else if(ParamFilter!="") Filter=ParamFilter;
{
int Result;
Result=Application->MessageBox("Передача данных в Excel может занять много времени. Вы действительно хотите передать данные с текущими настройками?",
"Сообщение",MB_OKCANCEL|MB_ICONQUESTION|MB_DEFBUTTON1|MB_APPLMODAL);
if(Result!=IDOK)return;
}
TTable* Table;
switch(TabControl->TabIndex)
{
case 0:Table=DataModule1->StatistTable;
break;
case 1:Table=DataModule1->AlarmTable;
break;
case 2:Table=DataModule1->ReservStatTable;
}
Table->DisableControls();
Variant XL,v0,v1,v2;
XL=CreateOleObject("Excel.Application.8");
XL.OlePropertySet("Visible",true);
v0=XL.OlePropertyGet("Workbooks");
v0.OleProcedure("Add");
v1=v0.OlePropertyGet("Item",1);
v0=v1.OlePropertyGet("Worksheets") ;
//TDateTime CurDate=Date();

if(ParamFilter=="")
{
 unsigned int Counter=1;
 for(unsigned int i=0;i<maxsignal;i++)
 if((defPointerToSignals[i])&&(defPointerToSignals[i]->SaveData))
 {
 ParamFilter="(Numb='"+IntToStr(defPointerToSignals[i]->Number)+"')";
 if(DateFilter!="")Filter=ParamFilter+"and"+DateFilter;
 else Filter=ParamFilter;
 Table->Filter=Filter;
 if(!Table->Filtered)Table->Filtered=true;
 if(Table->RecordCount)
  {
  v0.OleProcedure("Add");
  Table->FindFirst();
  v1=v0.OlePropertyGet("Item",1);//Counter);
  v1.OlePropertySet("Name",defPointerToSignals[i]->Name.c_str());
  v2=v1.OlePropertyGet("Cells");
  //new TSendThread(Table,v2,false);
  FillSheet(Table,v2);
  //Table
  Counter++;
  }
 }
}
else
 {
 if(DateFilter!="")Filter=ParamFilter+"and"+DateFilter;
 else Filter=ParamFilter;
 Table->Filter=Filter;
 if(!Table->Filtered)Table->Filtered=true;
 if(Table->RecordCount)
  {
  v0.OleProcedure("Add");
  Table->FindFirst();
  v1=v0.OlePropertyGet("Item",1);//Counter);
  v1.OlePropertySet("Name",ParamComboBox->Text.c_str());
  v2=v1.OlePropertyGet("Cells");

  FillSheet(Table,v2);
  }
 }//*/
//v0.OlePropertyGet("Item",2).OlePropertySet("Name","Бухгалтерия красная");
//XL.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OleProcedure("SaveAs","test.xls");
//XL.OleProcedure("Quit");
//new TSendThread(Table,DateFilter,ParamFilter,ParamComboBox->Text,false);
//Table->EnableControls();
}
//---------------------------------------------------------------------------
void TSetBDForm::FillSheet(TTable* Table,Variant& Cells)
{
 Cells.OlePropertyGet("Item",1,1).OlePropertySet("Value","Дата");
 Cells.OlePropertyGet("Item",1,2).OlePropertySet("Value","Час");
 Cells.OlePropertyGet("Item",1,3).OlePropertySet("Value","Минута");
 Cells.OlePropertyGet("Item",1,4).OlePropertySet("Value","Секунда");
 Cells.OlePropertyGet("Item",1,5).OlePropertySet("Value","Значение");
 bool a;
 unsigned int Counter1=2;
 do
  {
  Cells.OlePropertyGet("Item",Counter1,1).OlePropertySet("Value",Table->FieldByName("Date")->AsDateTime);
  Cells.OlePropertyGet("Item",Counter1,2).OlePropertySet("Value",Table->FieldByName("Hours")->AsInteger);
  Cells.OlePropertyGet("Item",Counter1,3).OlePropertySet("Value",Table->FieldByName("Minuts")->AsInteger);
  Cells.OlePropertyGet("Item",Counter1,4).OlePropertySet("Value",Table->FieldByName("Seconds")->AsInteger);
  Cells.OlePropertyGet("Item",Counter1,5).OlePropertySet("Value",Table->FieldByName("Value")->AsFloat);
  a=Table->FindNext();
  Counter1++;
  }
 while((a)&&(!Table->Eof));
}


