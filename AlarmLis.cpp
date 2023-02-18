//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AlarmLis.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAlarmListForm *AlarmListForm;
//---------------------------------------------------------------------------
__fastcall TAlarmListForm::TAlarmListForm(TComponent* Owner)
        : TForm(Owner)
{
for(int i=0;i<maxsignal;i++)
 {
 ConnectCell[i].Present=false;
 }
int NumbRow=1;
AlarmGrid->Cells[0][0]="Параметр";
AlarmGrid->Cells[1][0]="Сост. сигнала";
for(unsigned int i=0;i<maxsignal;i++)
  if((defPointerToSignals[i])&&(defPointerToSignals[i]->CritSignal)&&((!defPointerToSignals[i]->OnlyMessage)||(
  (defPointerToSignals[i]->OnlyMessage)&&(!defPointerToSignals[i]->OnSignal))))
   /*(MainForm->SetsAd.Contains(i))&&(MainForm->SetsChan.Contains(j))*/
  {
  AlarmGrid->RowCount=NumbRow+1;
  AlarmGrid->Cells[0][NumbRow]=defPointerToSignals[i]->Name;//Параметр
   if(defPointerToSignals[i]->OnSignal==true)
    AlarmGrid->Cells[1][NumbRow]="Включен";
   else
    AlarmGrid->Cells[1][NumbRow]="Выключен";//Включен/Выключен.
  ConnectCell[NumbRow].Signal=i;
  ConnectCell[NumbRow].Present=true;
  NumbRow++;
  }
if(AlarmGrid->Cells[0][1]!="")
 {
 AlarmGrid->Visible=true;
 Label1->Visible=false;
 }
else
 {
 AlarmGrid->Visible=false;
 Label1->Visible=true;
 }
if(AlarmGrid->Cells[0][1]!="")
Timer1->Enabled=true;
else Timer1->Enabled=false;
/*for(int i=0;i<maxsignal;i++)
 {
 ConnectCell[i].Present=true;
 }*/
}
//---------------------------------------------------------------------------
void __fastcall TAlarmListForm::Timer1Timer(TObject *Sender)
{
if(AlarmGrid->Color==clRed)
AlarmGrid->Color=clWindow;
else AlarmGrid->Color=clRed;
}
//---------------------------------------------------------------------------
void __fastcall TAlarmListForm::AlarmGridMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TGridCoord CellAtPos;
CellAtPos=AlarmGrid->MouseCoord(X,Y);
if((CellAtPos.X==1)&&(CellAtPos.Y>0)
&&(AlarmGrid->Cells[CellAtPos.X][CellAtPos.Y]!=""))
 {
 //int Ad,Chan;
 /*for(int i=0;i<maxadam;i++)
  for(int j=0;j<maxchannel;j++)
   for(int k=0;k<maxadam*maxchannel;k++)*/
 if(AlarmGrid->Cells[CellAtPos.X][CellAtPos.Y]=="Включен")
  {
  AlarmGrid->Cells[CellAtPos.X][CellAtPos.Y]="Выключен";
  /*if((MainForm->SetsAd.Contains(ConnectCell[CellAtPos.Y].Adam))&&
  (MainForm->SetsChan.Contains(ConnectCell[CellAtPos.Y].Channel)))*/
  defPointerToSignals[ConnectCell[CellAtPos.Y].Signal]->OnSignal=false;
  }                                                                //Set
 else
  {
  AlarmGrid->Cells[CellAtPos.X][CellAtPos.Y]="Включен";
  defPointerToSignals[ConnectCell[CellAtPos.Y].Signal]->OnSignal=true;
  }
 }
}
//---------------------------------------------------------------------------
