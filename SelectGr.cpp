//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SelectGr.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSelGraphForm *SelGraphForm;
//---------------------------------------------------------------------------
__fastcall TSelGraphForm::TSelGraphForm(TComponent* Owner)
        : TForm(Owner)
{
ZeroMemory(PresentBit,sizeof(PresentBit));
}
//---------------------------------------------------------------------------
          //TDrawGird
void __fastcall TSelGraphForm::FormDestroy(TObject *Sender)
{
for(int i=0;i<maxgraph;i++)
if(PresentBit[i]) delete Bitmap[i];
}
//---------------------------------------------------------------------------
void __fastcall TSelGraphForm::FormActivate(TObject *Sender)
{
int a=0;
for(int k=0;k<maxgraph;k++)
 if(Graphics[k]!=-1)
 {
 AnsiString GraphName="";
 //for(unsigned int i=0;i<maxsignal;i++)
  //for(int j=0;j<maxchannel;j++)
  if((defPointerToSignals[Graphics[k]])&&(!PresentBit[k]))
   {
   /*Graphics::TBitmap*/ Bitmap[k]=new Graphics::TBitmap();
   PresentBit[k]=true;
   GraphName=defPointerToSignals[Graphics[k]]->Name;
   }
 //Bitmap[k]=new HBITMAP;
 if(defPointerToSignals[Graphics[k]])
 {
 Bitmap[k]->Height=14;
 Bitmap[k]->Width=16;
 Bitmap[k]->Canvas->Pen->Color=clBlack;
 Bitmap[k]->Canvas->Brush->Color=GraphColor[k];
 Bitmap[k]->Canvas->Rectangle(0,0,14,16);
 ListBox->Items->AddObject(GraphName,Bitmap[k]);
 GraphToList[a]=k;
 }
 a++;
 }
}
//---------------------------------------------------------------------------

void __fastcall TSelGraphForm::ListBoxDrawItem(TWinControl *Control,
      int Index, TRect &Rect, TOwnerDrawState State)
{
Graphics::TBitmap *Bitm;
int TextWidth;
static_cast<TListBox*>(Control)->Canvas->FillRect(Rect);
Bitm=static_cast<Graphics::TBitmap*>(ListBox->Items->Objects[Index]);
if(Bitm!=NULL)
 {
 static_cast<TListBox*>(Control)->Canvas->BrushCopy(Bounds(Rect.Left+2,
 Rect.Top+2,Bitm->Width,Bitm->Height),Bitm,Bounds(0,0,Bitm->Width,Bitm->Height),clWindow);
 TextWidth=Bitm->Width+8;
 }
static_cast<TListBox*>(Control)->Canvas->TextOut(Rect.Left+TextWidth,Rect.Top,
ListBox->Items->Strings[Index]);
}
//---------------------------------------------------------------------------



