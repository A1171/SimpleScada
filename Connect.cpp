//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Connect.h"
#include "DataUnit.h"
#include "MainUnut.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormOfConnect *FormOfConnect;
//---------------------------------------------------------------------------
__fastcall TFormOfConnect::TFormOfConnect(TComponent* Owner)
        : TForm(Owner)
{
FOnlyPhisic=false;
FOnlySaved=true;
RefreshForm();
/*for(int i=0;i<maxsignal;i++)
 if((defPointerToSignals[i])&&((defPointerToSignals[i]->Type==TDataConteiner::stInp)||
 (defPointerToSignals[i]->Type==TDataConteiner::stCalc)))
 {
 AnsiString Name=defPointerToSignals[i]->Name;
 ListBox->Items->AddObject(Name,defPointerToSignals[i]);
 }*/
 ///
}
//---------------------------------------------------------------------------
void TFormOfConnect::RefreshForm()
{
ParamGrid->Cells[0][0]="����� ����.";
ParamGrid->Cells[1][0]="�������� ���������";
ParamGrid->Cells[1][0]="��� ������";
DataModule1->WhoreTable->Active=false;
DataModule1->WhoreTable->DatabaseName=MainForm->ProgramDir;
DataModule1->WhoreTable->TableName=MainForm->ProgramDir+"\\Captions.db";
DataModule1->WhoreTable->Active=true;
unsigned int RowNumber=1;
for(unsigned int i=0;i<maxsignal;i++)
 if((defPointerToSignals[i])&&((!FOnlySaved)||(defPointerToSignals[i]->SaveData))
 &&((!FOnlyPhisic)||(defPointerToSignals[i]->Type==stInp)||(defPointerToSignals[i]->Type==stOut)))
 //((((!FOnlyPhisic)&&(/!(FOnlySaved)&&/(defPointerToSignals[i]->SaveData))
 //&&((defPointerToSignals[i]->Type==stInp)||
 //(defPointerToSignals[i]->Type==stOut)))||(defPointerToSignals[i]->Type==stCalc)))
 //||((FOnlyPhisic)&&((defPointerToSignals[i]->Type==stOut)||(defPointerToSignals[i]->Type==stInp))))
  {                                          //DataModule1->Signal[i]
  RowNumber++;
  ParamGrid->RowCount=RowNumber;
  ParamGrid->Cells[0][RowNumber-1]=IntToStr(i);
  ParamGrid->Cells[1][RowNumber-1]=defPointerToSignals[i]->Name;
  DataModule1->WhoreTable->EditKey();
  DataModule1->WhoreTable->FieldByName("Value")->AsInteger = defPointerToSignals[i]->Type;
  DataModule1->WhoreTable->GotoKey();
  ParamGrid->Cells[2][RowNumber-1]=DataModule1->WhoreTable->FieldByName("SignalType")->AsString;
  /*switch(defPointerToSignals[i]->Type)
   {
   case TDataConteiner::stInp:ParamGrid->Cells[2][RowNumber-1]="������� ������";
   break;
   case TDataConteiner::stCalc:ParamGrid->Cells[2][RowNumber-1]="��������� ������";
   break;
   case TDataConteiner::stOut:ParamGrid->Cells[2][RowNumber-1]="�������� ������";
   }*/
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormOfConnect::ParamGridClick(TObject *Sender)
{
//int Top,Bottom,Left,Right;
TGridRect Sel=ParamGrid->Selection;
Sel.Bottom=ParamGrid->Selection.Top;
Sel.Left=0;
Sel.Right=ParamGrid->ColCount-1;
ParamGrid->Selection=Sel;
}
//---------------------------------------------------------------------------
void __fastcall TFormOfConnect::FindParametr(unsigned int Num)
{
for(int i=ParamGrid->FixedRows;i<ParamGrid->RowCount;i++)
 if(StrToInt(ParamGrid->Cells[0][i])==Num)
 {
 TGridRect Sel;
 Sel.Bottom=i;Sel.Top=i;Sel.Left=0;Sel.Right=ParamGrid->ColCount-1;
 ParamGrid->Selection=Sel;
 }
}
//---------------------------------------------------------------------------
unsigned int __fastcall TFormOfConnect::GetParametr()
{
TGridRect Sel=ParamGrid->Selection;
return StrToInt(ParamGrid->Cells[0][Sel.Top]);
}
//---------------------------------------------------------------------------
void __fastcall TFormOfConnect::FindField(const TInpType& Inp)
{
switch(Inp)
 {
 case itInp:FieldComboBox->ItemIndex=0;
 break;
 case itCalc:FieldComboBox->ItemIndex=1;
 break;
 case itOut:FieldComboBox->ItemIndex=2;
 }
}
//---------------------------------------------------------------------------
TInpType __fastcall TFormOfConnect::GetField()
{
switch(FieldComboBox->ItemIndex)
 {
 case 0:return itInp;
 //break;
 case 1:return itCalc;
 //break;
 case 2:return itOut;
 }
}
