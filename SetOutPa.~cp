//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SetOutPa.h"
#include "Chaild.h"
#include "MainUnut.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSetOutParamForm *SetOutParamForm;
//---------------------------------------------------------------------------
__fastcall TSetOutParamForm::TSetOutParamForm(TComponent* Owner)
        : TForm(Owner)
{
Scale=0.0001;
}
//---------------------------------------------------------------------------


void __fastcall TSetOutParamForm::FormActivate(TObject *Sender)
{
if((static_cast<TChildForm*>(MainForm->ActiveMDIChild)->ObjType==otPict)||
(static_cast<TChildForm*>(MainForm->ActiveMDIChild)->ObjType==otClip))
 {
 Label1->Visible=false;
 Label2->Visible=false;
 IntEdit->Visible=false;
 FactionalEdit->Visible=false;
 //TrackBar->Top+=30;
 //ValueLabel->Top+=30;
 //MinLabel->Top+=30;
 //MaxLabel->Top+=30;
 //ScaleLabel->Top+=30;
 }
else if(static_cast<TChildForm*>(MainForm->ActiveMDIChild)->ObjType==otEdit)
 {
 TrackBar1->Visible=false;
 MinLabel1->Visible=false;
 MaxLabel1->Visible=false;
 ValueLabel1->Visible=false;
 Label3->Visible=false;
 //ScaleLabel->Visible=false;
 TrackBar2->Visible=false;
 MinLabel2->Visible=false;
 MaxLabel2->Visible=false;
 ValueLabel2->Visible=false;
 Label4->Visible=false;
 Label1->Top-=30;
 Label2->Top-=30;
 IntEdit->Top-=30;
 FactionalEdit->Top-=30;
 }
else
 {
 TrackBar1->Visible=false;
 MinLabel1->Visible=false;
 MaxLabel1->Visible=false;
 TrackBar2->Visible=false;
 MinLabel2->Visible=false;
 MaxLabel2->Visible=false;
 Label1->Visible=false;
 Label2->Visible=false;
 Label3->Visible=false;
 Label4->Visible=false;
 IntEdit->Visible=false;
 FactionalEdit->Visible=false;
 ValueLabel1->Visible=false;
 ValueLabel2->Visible=false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TSetOutParamForm::TrackBar1Change(TObject *Sender)
{
if(Sender==TrackBar1)
ValueLabel1->Caption=FloatToStrF((TrackBar1->Position)/Scale,ffFixed,5,6);
else
ValueLabel2->Caption=FloatToStrF((TrackBar2->Position)/Scale,ffFixed,5,6);
}
//---------------------------------------------------------------------------


void __fastcall TSetOutParamForm::BitBtn1Click(TObject *Sender)
{
/*if(static_cast<TChildForm*>(MainForm->ActiveMDIChild)->ObjType==otEdit)
{
 try
  {
  int a;
  a=StrToInt(IntEdit->Text);
  a=StrToInt(FactionalEdit->Text);
  }
 catch(...)
  {
  Application->MessageBox("Вветите целочисленные значения",
  "Предупреждение",MB_OK|MB_ICONWARNING);
  }
}*/
}
//---------------------------------------------------------------------------









