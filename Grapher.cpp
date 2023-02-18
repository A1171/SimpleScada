//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Grapher.h"
#include "MainUnut.h"
#include "DataUnit.h"
#include "Connect.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TGrapherForm *GrapherForm;
//---------------------------------------------------------------------------
__fastcall TGrapherForm::TGrapherForm(TComponent* Owner)
        : TForm(Owner)
{
if(MainForm->MDIChildCount>0)
Number=MainForm->MDIChildCount;
else Number=0;
//Adam=1;
//Channel=0;
SignalNumber=-1;
Max=100;
for(int i=0;i<maxStore;i++)Value[i]=0;
ComboBox->ItemIndex=1;
Delenie=20;
Color=clWindow;
Type=2;
MainForm->MDIChildType[MainForm->MDIChildCount-1]=Type;
}
//---------------------------------------------------------------------------

void __fastcall TGrapherForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
Action=caFree;        
}
//---------------------------------------------------------------------------

void __fastcall TGrapherForm::PaintBoxPaint(TObject *Sender)
{
int StepX=30;
int StepY=30;
if(StepX<20)StepX=20;
int dBottom=15;
int dLeft=40;
int h=PaintBox->Height;
int w=PaintBox->Width;
PaintBox->Canvas->Pen->Color=clBlack;
PaintBox->Canvas->Pen->Width=2;
PaintBox->Canvas->MoveTo(0,h-dBottom);
PaintBox->Canvas->LineTo(w,h-dBottom);
PaintBox->Canvas->MoveTo(w-dLeft,0);
PaintBox->Canvas->LineTo(w-dLeft,h);
PaintBox->Canvas->Pen->Color=clBlack;
PaintBox->Canvas->Pen->Width=1;
for(int i=dLeft+StepX;i<=w;i+=StepX)
 {
 PaintBox->Canvas->MoveTo(w-i,0);
 PaintBox->Canvas->LineTo(w-i,h);
 }
for(int i=h-dBottom;i>=0;i-=StepY)
 {
 PaintBox->Canvas->MoveTo(0,i);
 PaintBox->Canvas->LineTo(w,i);
 }
for(int i=1;i<=(w-dLeft)/StepX;i+=1)
 {
 //Out Time Scales
 PaintBox->Canvas->TextOut(w-dLeft-i*StepX+2,h-dBottom+2,i*20);
 }
for(int i=1;i<=(h-dBottom)/StepY;i+=1)
 {
 //Out Value Scales
 PaintBox->Canvas->TextOut(w-dLeft+1,h-dBottom-i*StepY+2,FloatToStrF(
 float(i)*float(StepY)/float(h-dBottom)*Max,ffFixed,6,4));
 }
PaintBox->Canvas->TextOut(w-dLeft+1,h-dBottom+1,"X"+FloatToStrF(float(Delenie)/20,ffFixed,3,2));
float hdBM=(h-dBottom)/Max;
//int
PaintBox->Canvas->Pen->Color=clRed;
for(int i=1;i<maxStore;i++)
 {
 if((i*float(StepX)/Delenie<(w-dLeft))&&(true))
  {
  PaintBox->Canvas->MoveTo(w-dLeft-(i-1)*float(StepX)/20,float(h)-Value[i-1]*hdBM-float(dBottom));
  PaintBox->Canvas->LineTo(w-dLeft-(i-1)*float(StepX)/20,float(h)-Value[i]*hdBM-float(dBottom));
  PaintBox->Canvas->LineTo(w-dLeft-(i)*float(StepX)/20,float(h)-Value[i]*hdBM-float(dBottom));
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrapherForm::Timer1Timer(TObject *Sender)
{
for(int i=maxStore-1;i>0;i--)
 {
 Value[i]=Value[i-1];
 }
if((SignalNumber!=-1)&&(defPointerToSignals[SignalNumber]))
 Value[0]=defPointerToSignals[SignalNumber]->OutValue;//MainForm->Signal[Adam][Channel];
PaintBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TGrapherForm::ConnectItemClick(TObject *Sender)
{
AdConnThread->Suspended=true;
TFormOfConnect *Form7;
Form7=new TFormOfConnect(this);
Form7->FieldComboBox->Visible=false;
Form7->ComboBox2->Visible=false;
Form7->Signal=SignalNumber;
//for(unsigned int i=0;i<
//Form7->StringGird
//DataModule1->FindRecord1(Adam,Channel);
if(Form7->ShowModal()==mrOk)
 {
 //Adam=int(DataModule1->KanalsTable->FieldValues["Adam"]);
 //Channel=int(DataModule1->KanalsTable->FieldValues["Kanal"]);
 if(defPointerToSignals[SignalNumber])
  {
  SignalNumber=Form7->Signal;
  Max=defPointerToSignals[SignalNumber]->Limits.Max;//float(DataModule1->KanalsTable->FieldValues["Max"]);
  Caption=defPointerToSignals[SignalNumber]->Name;//DataModule1->KanalsTable->FieldValues["Parametr"];
  }
 }
delete Form7;
AdConnThread->Suspended=false;

}
//---------------------------------------------------------------------------

void __fastcall TGrapherForm::ScalesItemClick(TObject *Sender)
{
switch(Delenie)
{
 case 20:
 {
 ComboBox->ItemIndex=0;
 }
 break;
 case 200:
 {
 ComboBox->ItemIndex=1;
 }
 break;
 case 1000:
 {
 ComboBox->ItemIndex=2;
 }
 break;
 case 2000:
 {
 ComboBox->ItemIndex=3;
 }
 break;
 default:
 {
 ComboBox->Text=IntToStr(Delenie);
 }
}
OkButton->Visible=true;
Label1->Visible=true;
ComboBox->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TGrapherForm::OkButtonClick(TObject *Sender)
{
switch(ComboBox->ItemIndex)
{
 case 0:
 {
 Delenie=20;
 }
 break;
 case 1:
 {
 Delenie=200;
 }
 break;
 case 2:
 {
 Delenie=1000;
 }
 break;
 case 3:
 {
 Delenie=2000;
 }
 break;
 default:
 {
 Delenie=StrToInt(ComboBox->Text);
 }
}
if(Delenie<20)Delenie=20;
for(int i=0;i<maxStore;i++)
 {
 Value[i]=0;
 }
Timer1->Interval=Delenie*50;
OkButton->Visible=false;
Label1->Visible=false;
ComboBox->Visible=false;
}
//---------------------------------------------------------------------------
void TGrapherForm::SaveToIniFile(TIniFile *IniFile,AnsiString Section)
{
IniFile->WriteInteger(Section,"Top",Top);
IniFile->WriteInteger(Section,"Left",Left);
IniFile->WriteInteger(Section,"Width",Width);
IniFile->WriteInteger(Section,"Height",Height);
IniFile->WriteInteger(Section,"SignalNumber",SignalNumber);
//IniFile->WriteInteger(Section,"Channel",Channel);
IniFile->WriteInteger(Section,"Max",Max);
IniFile->WriteInteger(Section,"Delenie",Delenie);
IniFile->WriteString(Section,"Caption",Caption);
}//End of save
//---------------------------------------------------------------------------
void TGrapherForm::LoadFromIniFile(TIniFile *IniFile,AnsiString Section)
{
Top=IniFile->ReadInteger(Section,"Top",0);
Left=IniFile->ReadInteger(Section,"Left",0);
Width=IniFile->ReadInteger(Section,"Width",205);
Height=IniFile->ReadInteger(Section,"Height",138);
SignalNumber=IniFile->ReadInteger(Section,"SignalNumber",1);
//Channel=IniFile->ReadInteger(Section,"Channel",1);
Max=IniFile->ReadInteger(Section,"Max",100);
Delenie=IniFile->ReadInteger(Section,"Delenie",20);
Caption=IniFile->ReadString(Section,"Caption","Самописец");
Timer1->Interval=Delenie*50;
OkButton->Visible=false;
Label1->Visible=false;
ComboBox->Visible=false;
}//End of load*/
