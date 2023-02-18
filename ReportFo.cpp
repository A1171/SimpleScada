//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ReportFo.h"
#include "DataUnit.h"
#include "MainUnut.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRepForm *RepForm;
//---------------------------------------------------------------------------
__fastcall TRepForm::TRepForm(TComponent* Owner)
        : TForm(Owner)
{
KindLabel->Caption=MainForm->PromCaption;
if(MainForm->PromCaption!="Распечатка всех параметров")
 {
 QRLabel7->Caption="";
 QRLabel14->Caption="";
 QRDBText5->Enabled=false;
 QRShape11->Visible=false;
 QRShape5->Visible=false;
 QRShape17->Visible=false;
 QRLabel4->Left+=24;
 QRLabel11->Left+=24;
 QRDBText2->Left+=24;
 QRShape8->Left+=24;
 QRShape2->Left+=24;
 QRShape14->Left+=24;
 QRLabel5->Left+=56;
 QRLabel12->Left+=56;
 QRDBText3->Left+=56;
 QRShape9->Left+=56;
 QRShape3->Left+=56;
 QRShape15->Left+=56;
 QRLabel6->Left+=88;
 QRLabel13->Left+=88;
 QRDBText4->Left+=88;
 QRShape10->Left+=88;
 QRShape4->Left+=88;
 QRShape16->Left+=88;
 QRLabel8->Left-=44;
 QRLabel15->Left-=44;
 QRDBText6->Left-=44;
 QRShape12->Left-=44;
 QRShape6->Left-=44;
 QRShape18->Left-=44;
 }
}
//---------------------------------------------------------------------------



