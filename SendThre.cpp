//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SendThre.h"
#include "DataUnit.h"
#include <ComObj.hpp>
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TSendThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TSendThread::TSendThread(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
__fastcall TSendThread::TSendThread(TTable* Table,AnsiString DateFilter,AnsiString ParamFilter,AnsiString ParamName,
bool CreateSuspended)
        : TThread(CreateSuspended)
{
FTable=Table;
//FCells=Cells;
FDateFilter=DateFilter;
FParamFilter=ParamFilter;
FParamName=ParamName;
FreeOnTerminate=true;
}
//---------------------------------------------------------------------------
void __fastcall TSendThread::Execute()
{
if(Terminated)
{
FTable->EnableControls();
return;
}
Variant XL,v0,v1,v2;
XL=CreateOleObject("Excel.Application.8");
XL.OlePropertySet("Visible",true);
v0=XL.OlePropertyGet("Workbooks");
v0.OleProcedure("Add");
v1=v0.OlePropertyGet("Item",1);
v0=v1.OlePropertyGet("Worksheets") ;
//TDateTime CurDate=Date();
AnsiString Filter;
if(FParamFilter=="")
{
 unsigned int Counter=1;
 for(unsigned int i=0;i<maxsignal;i++)
 if((defPointerToSignals[i])&&(defPointerToSignals[i]->SaveData))
 {
 FParamFilter="(Numb='"+IntToStr(defPointerToSignals[i]->Number)+"')";
 if(FDateFilter!="")Filter=FParamFilter+"and"+FDateFilter;
 else Filter=FParamFilter;
 FTable->Filter=Filter;
 if(!FTable->Filtered)FTable->Filtered=true;
 if(FTable->RecordCount)
  {
  v0.OleProcedure("Add");
  FTable->FindFirst();
  v1=v0.OlePropertyGet("Item",1/*Counter*/);
  v1.OlePropertySet("Name",defPointerToSignals[i]->Name.c_str());
  /*v2*/FCells=v1.OlePropertyGet("Cells");
  Synchronize(SendCaption);
  bool a;
  Counter1=2;
  do
   {
   if(Terminated)
    {
    FTable->EnableControls();
    return;
    }
   Synchronize(Send);
   a=FTable->FindNext();
   Counter1++;
   }
  while((a)&&(!FTable->Eof));
  //FillSheet(Table,v2);
  Counter++;
  }
 }
}
else
 {
 if(FDateFilter!="")Filter=FParamFilter+"and"+FDateFilter;
 else Filter=FParamFilter;
 FTable->Filter=Filter;
 if(!FTable->Filtered)FTable->Filtered=true;
 if(FTable->RecordCount)
  {
  v0.OleProcedure("Add");
  FTable->FindFirst();
  v1=v0.OlePropertyGet("Item",1/*Counter*/);
  v1.OlePropertySet("Name",FParamName.c_str());
  /*v2*/FCells=v1.OlePropertyGet("Cells");
  Synchronize(SendCaption);
  bool a;
  Counter1=2;
  do
   {
   if(Terminated)
    {
    FTable->EnableControls();
    return;
    }
   Synchronize(Send);
   a=FTable->FindNext();
   Counter1++;
   }
  while((a)&&(!FTable->Eof));
  //FillSheet(Table,v2);
  }
 }
//v0.OlePropertyGet("Item",2).OlePropertySet("Name","Бухгалтерия красная");
//XL.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OleProcedure("SaveAs","test.xls");
//XL.OleProcedure("Quit");
FTable->EnableControls();

/*if(Terminated)return;
Synchronize(SendCaption);
bool a;
Counter1=2;
do
 {
 if(Terminated)return;
 Synchronize(Send);
 a=FTable->FindNext();
 Counter1++;
 }
while((a)&&(!FTable->Eof));*/
        //---- Place thread code here ----
}
//---------------------------------------------------------------------------
void __fastcall TSendThread::Send()
{
  FCells.OlePropertyGet("Item",Counter1,1).OlePropertySet("Value",FTable->FieldByName("Date")->AsDateTime);
  FCells.OlePropertyGet("Item",Counter1,2).OlePropertySet("Value",FTable->FieldByName("Hours")->AsInteger);
  FCells.OlePropertyGet("Item",Counter1,3).OlePropertySet("Value",FTable->FieldByName("Minuts")->AsInteger);
  FCells.OlePropertyGet("Item",Counter1,4).OlePropertySet("Value",FTable->FieldByName("Seconds")->AsInteger);
  FCells.OlePropertyGet("Item",Counter1,5).OlePropertySet("Value",FTable->FieldByName("Value")->AsFloat);
}
void __fastcall TSendThread::SendCaption()
{
FCells.OlePropertyGet("Item",1,1).OlePropertySet("Value","Дата");
 FCells.OlePropertyGet("Item",1,2).OlePropertySet("Value","Час");
 FCells.OlePropertyGet("Item",1,3).OlePropertySet("Value","Минута");
 FCells.OlePropertyGet("Item",1,4).OlePropertySet("Value","Секунда");
 FCells.OlePropertyGet("Item",1,5).OlePropertySet("Value","Значение");
}//---------------------------------------------------------------------------
