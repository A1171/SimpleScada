//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SetGraph.h"
#include "SelectGr.h"
#include "Connect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSetPrnFo *SetPrnFo;
//---------------------------------------------------------------------------
__fastcall TSetPrnFo::TSetPrnFo(TComponent* Owner)
        : TForm(Owner)
{

}
//--------------------------------------
void TSetPrnFo::SetEdit()
{
AxisEdit->Text=IntToStr(AxisUpDown->Position);
GirdEdit->Text=IntToStr(GirdUpDown->Position);
GraphEdit->Text=IntToStr(GraphUpDown->Position);
}
//---------------------------------------------------------------------------
void __fastcall TSetPrnFo::AxisUpDownChanging(TObject *Sender,
      bool &AllowChange)
{
AxisEdit->Text=IntToStr(AxisUpDown->Position);        
}
//---------------------------------------------------------------------------
void __fastcall TSetPrnFo::GirdUpDownChanging(TObject *Sender,
      bool &AllowChange)
{
GirdEdit->Text=IntToStr(GirdUpDown->Position);
}
//---------------------------------------------------------------------------
void __fastcall TSetPrnFo::GraphUpDownChanging(TObject *Sender,
      bool &AllowChange)
{
GraphEdit->Text=IntToStr(GraphUpDown->Position);        
}
//---------------------------------------------------------------------------

void __fastcall TSetPrnFo::ShowAxisButtonClick(TObject *Sender)
{
TSelGraphForm* Form=new TSelGraphForm(this);
Form->Caption="????????? ???";
Form->AllBitBtn->Visible=false;
Form->BitBtn2->Visible=false;
for(int i=0;i<maxgraph;i++)
 {
 Form->Graphics[i]=PrintedAxis[i];
 Form->GraphColor[i]=clBlack;
 }
Form->ShowModal();
delete Form;
}
//---------------------------------------------------------------------------
void __fastcall TSetPrnFo::AddAxisButtonClick(TObject *Sender)
{
TFormOfConnect* Form=new TFormOfConnect(this);
Form->FieldComboBox->Visible=false;
Form->ComboBox2->Visible=false;
if(Form->ShowModal()==mrOk)
 {
 int i=0;
 while((PrintedAxis[i]>=0)&&(i<=maxgraph))i++;
 if(i==maxgraph)
  {
  Application->MessageBox("???????????? ?????????? ????","?????????",MB_OK|MB_ICONSTOP);
  delete Form;
  return;
  }
 for(int j=0;j<i;j++)
 if(PrintedAxis[j]==Form->Signal)
  {
  Application->MessageBox("????? ??? ??? ????????????","?????????",MB_OK|MB_ICONSTOP);
  delete Form;
  return;
  }
 PrintedAxis[i]=Form->Signal;
 }
delete Form;
}
//---------------------------------------------------------------------------


void __fastcall TSetPrnFo::DelAxisButtonClick(TObject *Sender)
{
//TSelGraphForm* Form=new TSelGraphForm(this);

/*Form->AllBitBtn->Visible=true;
Form->BitBtn2->Visible=true;
for(int i=0;i<maxgraph;i++)
 {
 Form->Graphics[i]=MainForm->PrintedAxis[i];
 Form->GraphColor[i]=clBlack;
 }
Form->ShowModal();
delete Form;*/
TSelGraphForm *Form16=new TSelGraphForm(this);
Form16->Caption="????????? ???";
 for(int i=0;i<maxgraph;i++)
  {
  Form16->Graphics[i]=PrintedAxis[i];
  Form16->GraphColor[i]=clBlack;
  }
  Form16->AllBitBtn->Visible=true;
  TModalResult mod;
  mod=Form16->ShowModal();
  if(mod==mrOk)
  {
  if(Form16->ListBox->ItemIndex!=-1)
   {
   /*if(MainForm->ParamCaptions[Form16->ListBox->ItemIndex]==
   Form16->ListBox->Items->Strings[Form16->ListBox->ItemIndex])*/
   PrintedAxis[Form16->GraphToList[Form16->ListBox->ItemIndex]]=-1;
   //PaintBox1->Invalidate();
   }
  }
  else if(mod==mrAll)
   {
   for(int i=0;i<maxgraph;i++)
    {
    PrintedAxis[i]=-1;
    //GraphPoint[i].Size=0;
    //delete []GraphPoint[i].Array;
    //GraphPoint[i].Array=0;
    }
   }
 delete Form16;
}
//---------------------------------------------------------------------------

