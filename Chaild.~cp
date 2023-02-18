#include "Constant.h"
#include "SelFrame.h"
#include "SetOutPa.h"
#include "DataUnit.h"
#include "DataUnit.h"
#include "Connect.h"
#include "MainUnut.h"
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Chaild.h"
            
#include "Math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TFanForm *FanForm;
//---------------------------------------------------------------------------
void __fastcall TChildForm::SetPictur(AnsiString Value)
 {
 FPictur=Value;
 if(Value!="")Image->Picture->LoadFromFile(MainForm->ProgramDir+"\\Images\\"+FPictur);
 }
void __fastcall TChildForm::SetFileName(AnsiString Value)
{
FFileName=Value;
}
__fastcall TChildForm::TChildForm(TComponent* Owner)
        : TForm(Owner)
{
#ifdef Debug
AddObjectItem->Visible=true;
N2->Visible=true;
AddWindowItem->Visible=true;
AddIndicatItem->Visible=true;
AddImageItem->Visible=true;
AddLevel->Visible=true;
AddClip->Visible=true;
AddButtonItem->Visible=true;
StartItem->Visible=true;
PrepareItem->Visible=true;
#endif
FPictur="";
if(MainForm->MDIChildCount>0)
Number=MainForm->MDIChildCount;
else
Number=0;
AddObjectItem->Visible=MainForm->N5->Checked;
Resize=false;
for(int i=0;i<maxparam;i++)
 {
 EditsPresent[i]=false;
 IndicatPresent[i]=false;
 LevelPresent[i]=false;
 PicturiePresent[i]=false;
 ClipPresent[i]=false;
 ButtonPresent[i]=false;
 Edits[i]=0;
 Indicators[i]=0;
 Picturies[i]=0;
 Levels[i]=0;
 Clip[i]=0;
 Buttons[i]=0;
 }
Type=1;
MainForm->MDIChildType[MainForm->MDIChildCount-1]=Type;
DragObject=0;
}
//---------------------------------------------------------------------------
void TChildForm::SaveToIniFile(TIniFile *IniFile)
{
IniFile->WriteInteger("GlobalSettings","Top",Top);
IniFile->WriteInteger("GlobalSettings","Left",Left);
IniFile->WriteInteger("GlobalSettings","Width",Width);
IniFile->WriteInteger("GlobalSettings","Height",Height);
IniFile->WriteString("GlobalSettings","Picturie",FPictur);
IniFile->WriteString("GlobalSettings","Caption",Caption);
FFileName=IniFile->FileName;
for(int i=0;i<maxparam;i++)
 {
 if(IndicatPresent[i]) Indicators[i]->SaveToIniFile(IniFile,"Indicator"+
 IntToStr(i));
 if(LevelPresent[i]) Levels[i]->SaveToIniFile(IniFile,"Level"+
 IntToStr(i));
 if(PicturiePresent[i]) Picturies[i]->SaveToIniFile(IniFile,"Picturie"+
 IntToStr(i));
 if(EditsPresent[i]) Edits[i]->SaveToIniFile(IniFile,"Edit"+
 IntToStr(i));
 if(ClipPresent[i]) Clip[i]->SaveToIniFile(IniFile,"Clip"+
 IntToStr(i));
 if(ButtonPresent[i]) Buttons[i]->SaveToIniFile(IniFile,"Button"+
 IntToStr(i));
 }
}//End of save
//---------------------------------------------------------------------------
void TChildForm::LoadFromIniFile(TIniFile *IniFile)
{
Top=IniFile->ReadInteger("GlobalSettings","Top",0);
Left=IniFile->ReadInteger("GlobalSettings","Left",0);
Width=IniFile->ReadInteger("GlobalSettings","Width",600);
Height=IniFile->ReadInteger("GlobalSettings","Height",400);
Pictur=IniFile->ReadString("GlobalSettings","Picturie","");
Caption=IniFile->ReadString("GlobalSettings","Caption","Структурная схема котельной");
FFileName=IniFile->FileName;
for(int i=0;i<maxparam;i++)
 {
 if(IniFile->ReadInteger("Indicator"+IntToStr(i),"Number",-1)==i)
  {
  Indicators[i]=new TIndicat(this);
  this->InsertControl(Indicators[i]);
  IndicatPresent[i]=true;
  Indicators[i]->LoadFromIniFile(IniFile,"Indicator"+IntToStr(i));
  #ifdef Debug
  Indicators[i]->OnMouseDown=Edit1MouseDown;
  #endif
  }
 if(IniFile->ReadInteger("Level"+IntToStr(i),"Number",-1)==i)
  {
  Levels[i]=new TLevel(this);
  this->InsertControl(Levels[i]);
  LevelPresent[i]=true;
  Levels[i]->LoadFromIniFile(IniFile,"Level"+IntToStr(i));
  #ifdef Debug
  Levels[i]->OnMouseDown=Edit1MouseDown;
  #endif
  }
 if(IniFile->ReadInteger("Picturie"+IntToStr(i),"Number",-1)==i)
  {
  Picturies[i]=new TImage1(this);
  this->InsertControl(Picturies[i]);
  PicturiePresent[i]=true;
  AnsiString Name=MainForm->ProgramDir+"\\Images\\Label.bmp";
  Picturies[i]->Picture->LoadFromFile(Name);
  Picturies[i]->Stretch=true;
  Picturies[i]->LoadFromIniFile(IniFile,"Picturie"+IntToStr(i));
  Picturies[i]->Picture->LoadFromFile(Picturies[i]->Imag/*MainForm->ProgramDir+"\\Images\\Label.bmp"*/);
  #ifdef Debug
  Picturies[i]->OnMouseDown=Edit1MouseDown;
  #endif
  }
 if(IniFile->ReadInteger("Edit"+IntToStr(i),"Number",-1)==i)
  {
  Edits[i]=new TEdit1(this);
  this->InsertControl(Edits[i]);
  Edits[i]->Text="";
  EditsPresent[i]=true;
  Edits[i]->LoadFromIniFile(IniFile,"Edit"+IntToStr(i));
  #ifdef Debug
  Edits[i]->OnMouseDown=Edit1MouseDown;
  #endif
  }
 if(IniFile->ReadInteger("Button"+IntToStr(i),"Number",-1)==i)
  {
  Buttons[i]=new TMyButton(this);
  this->InsertControl(Buttons[i]);
  Buttons[i]->Caption="";
  ButtonPresent[i]=true;
  Buttons[i]->LoadFromIniFile(IniFile,"Button"+IntToStr(i));
  #ifdef Debug
  Buttons[i]->OnMouseDown=Edit1MouseDown;
  #endif
  }
 if(IniFile->ReadInteger("Clip"+IntToStr(i),"Number",-1)==i)
  {
  Clip[i]=new TClip(this);
  this->InsertControl(Clip[i]);
  ClipPresent[i]=true;
  //Clip[i]->Picture->LoadFromFile(MainForm->ProgramDir+"\\Images\\Label.bmp");
  Clip[i]->Stretch=true;
  Clip[i]->LoadFromIniFile(IniFile,"Clip"+IntToStr(i));
  Clip[i]->Picture->LoadFromFile(Clip[i]->Imag[0]/*MainForm->ProgramDir+"\\Images\\Label.bmp"*/);
  #ifdef Debug
  Clip[i]->OnMouseDown=Edit1MouseDown;
  #endif
  }
 }
}//End of load

//---------------------------------------------------------------------------
void __fastcall TChildForm::FormClose(TObject *Sender, TCloseAction &Action)
{
MainForm->ShaxtMenu->Enabled=true;
Timer1->Enabled=false;
Action=caFree;
Pause(5);
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::FormDestroy(TObject *Sender)
{
if(MainForm->ActiveMDIChild==NULL)return;
if(Timer1->Enabled)Timer1->Enabled=false;
for(int i=0;i<maxparam;i++)
 {
 if((EditsPresent[i])&&(Edits[i]))
  {
  delete Edits[i];
  EditsPresent[i]=false;
  Edits[i]=0;
  }
 if((IndicatPresent[i])&&(Indicators[i]))
  {
  delete Indicators[i];
  IndicatPresent[i]=false;
  Indicators[i]=0;
  }
 if((PicturiePresent[i])&&(Picturies[i]))
  {
  delete Picturies[i];
  PicturiePresent[i]=false;
  Picturies[i]=0;
  }
 if((LevelPresent[i])&&(Levels[i]))
  {
  delete Levels[i];
  LevelPresent[i]=false;
  Levels[i]=0;
  }
 if((ButtonPresent[i])&&(Buttons[i]))
  {
  delete Buttons[i];
  ButtonPresent[i]=false;
  Buttons[i]=0;
  }
 if((ClipPresent[i])&&(Clip[i]))
  {
  delete Clip[i];
  ClipPresent[i]=false;
  Clip[i]=0;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::AddWindowItemClick(TObject *Sender)
{
int i=0;
while(EditsPresent[i]) i++;
Edits[i]=new TEdit1(this);
this->InsertControl(Edits[i]);
Edits[i]->Left=50;
Edits[i]->Top=50;
Edits[i]->Text="jhkghj";
EditsPresent[i]=true;
Edits[i]->Number=i;
Edits[i]->OnMouseDown=Edit1MouseDown;
//Edits[i]->OnDblClick=Edit1DblClick;
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::AddIndicatItemClick(TObject *Sender)
{
int i=0;
while(IndicatPresent[i]) i++;
Indicators[i]=new TIndicat(this);
this->InsertControl(Indicators[i]);
Indicators[i]->Left=50;
Indicators[i]->Top=50;
IndicatPresent[i]=true;
Indicators[i]->Number=i;
Indicators[i]->OnMouseDown=Edit1MouseDown;
//Edits[i]->OnDblClick=Edit1DblClick;
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::AddImageItemClick(TObject *Sender)
{
int i=0;
while(PicturiePresent[i]) i++;
Picturies[i]=new TImage1(this);
this->InsertControl(Picturies[i]);
Picturies[i]->Left=50;
Picturies[i]->Top=50;
PicturiePresent[i]=true;
Picturies[i]->Picture->LoadFromFile(MainForm->ProgramDir+"\\Images\\Label.bmp");
Picturies[i]->Stretch=true;
Picturies[i]->Number=i;
Picturies[i]->OnMouseDown=Edit1MouseDown;
//Edits[i]->OnDblClick=Edit1DblClick;
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::AddLevelClick(TObject *Sender)
{
int i=0;
while(LevelPresent[i]) i++;
Levels[i]=new TLevel(this);
this->InsertControl(Levels[i]);
Levels[i]->Left=50;
Levels[i]->Top=50;
LevelPresent[i]=true;
Levels[i]->Number=i;
//Le[i]->Picture->LoadFromFile(MainForm->ProgramDir+"\\Images\\Label.bmp");
//Picturies[i]->Stretch=true;
Levels[i]->OnMouseDown=Edit1MouseDown;
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::AddButtonItemClick(TObject *Sender)
{
int i=0;
while(ButtonPresent[i]) i++;
Buttons[i]=new TMyButton(this);
this->InsertControl(Buttons[i]);
//Buttons[i]->Left=50;
//Buttons[i]->Top=50;
Buttons[i]->Caption="";
ButtonPresent[i]=true;
Buttons[i]->Number=i;
Buttons[i]->OnMouseDown=Edit1MouseDown;
//Edits[i]->OnDblClick=Edit1DblClick;
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::AddClipClick(TObject *Sender)
{
int i=0;
while(ClipPresent[i]) i++;
Clip[i]=new TClip(this);
this->InsertControl(Clip[i]);
Clip[i]->Left=50;
Clip[i]->Top=50;
ClipPresent[i]=true;
Clip[i]->Picture->LoadFromFile(MainForm->ProgramDir+"\\Images\\Label.bmp");
Clip[i]->Stretch=true;
Clip[i]->Number=i;
Clip[i]->OnMouseDown=Edit1MouseDown;
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::Edit1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
MainForm->StatusBar->Panels->Items[3]->Text=IntToStr(static_cast <TControl*> (Sender)->Width)+
" X "+IntToStr(static_cast <TControl*> (Sender)->Height);
MainForm->StatusBar->Panels->Items[1]->Text="Сверху "+
IntToStr(static_cast <TControl*> (Sender)->Top);
MainForm->StatusBar->Panels->Items[2]->Text="Слева "+
IntToStr(static_cast <TControl*> (Sender)->Left);
if(Button==mbLeft)
 {
  if(Shift.Contains(ssShift))   Resize=true;
  else Resize=false;
  if(MainForm->EnablDrag)
  {
  Ramka->BeginDrag(false,1);
  Ramka->Left=static_cast <TControl*> (Sender)->Left;
  Ramka->Top=static_cast <TControl*> (Sender)->Top;
  Ramka->Width=static_cast <TControl*> (Sender)->Width;
  Ramka->Height=static_cast <TControl*> (Sender)->Height;
  static_cast <TControl*> (Sender)->Visible=false;
  DragX=X;
  DragY=Y;
  Ramka->Visible=true;
  //Edit1->Text="Down";
  DragObject=static_cast <TControl*> (Sender);
  }
 }
if(Button==mbRight)
  {
  AnsiString TypeClass=Sender->ClassName();
  DragObject=static_cast <TControl*> (Sender);
  for(int i=0;i<PopupMenu->Items->Count;i++)
   {
   PopupMenu->Items->Items[i]->Visible=false;
   }
   if(TypeClass=="TEdit1"/*static_cast<TEdit1*>(Sender)->Type==otEdit*/)
    {
    ObjType=otEdit;
    SelectObj=static_cast<TEdit1*>(Sender)->Number;
    DeletePopItem->Visible=true;
    ConnectPopItem->Visible=true;
    N1->Visible=true;
    SwitchingPopItem->Visible=false;
    FullItem->Visible=false;
    AroundItem->Visible=false;
    FontItem->Visible=true;
    OutParamItem->Visible=true;
    SelectImageItem->Visible=false;
    InvisibleItem->Visible=false;
    LoadImageItem->Visible=false;
    ShowFrameItem->Visible=false;
    }
   if(TypeClass=="TLevel"/*static_cast<TLevel*>(Sender)->Type==otLevel*/)
    {
    ObjType=otLevel;
    SelectObj=static_cast<TLevel*>(Sender)->Number;
    SwitchingPopItem->Visible=false;
    DeletePopItem->Visible=true;
    ConnectPopItem->Visible=true;
    N1->Visible=true;
    FullItem->Visible=true;
    AroundItem->Visible=true;
    FontItem->Visible=false;
    OutParamItem->Visible=false;
    SelectImageItem->Visible=false;
    InvisibleItem->Visible=false;
    LoadImageItem->Visible=false;
    ShowFrameItem->Visible=false;
    }
   if(TypeClass=="TImage1"/*static_cast<TImage1*>(Sender)->Type==otPict*/)
    {
    ObjType=otPict;
    SelectObj=static_cast<TImage1*>(Sender)->Number;
    SwitchingPopItem->Visible=true;
    bool Test=CheckMax(Picturies[SelectObj]->Signal);
    Test&=CheckMax(Picturies[SelectObj]->Signal);
    SwitchingPopItem->Enabled=!Test;
    DeletePopItem->Visible=true;
    ConnectPopItem->Visible=true;
    N1->Visible=true;
    FullItem->Visible=false;
    AroundItem->Visible=false;
    FontItem->Visible=false;
    OutParamItem->Visible=false;
    SelectImageItem->Visible=true;
    InvisibleItem->Visible=true;
    LoadImageItem->Visible=true;
    ShowFrameItem->Visible=false;
    StretchItem->Visible=true;
    StretchItem->Checked=static_cast<TImage1*>(Sender)->Stretch;
    }
   if(TypeClass=="TIndicat"/*static_cast<TIndicat*>(Sender)->Type==otIndicat*/)
    {
    ObjType=otIndicat;
    SelectObj=static_cast<TIndicat*>(Sender)->Number;
    SwitchingPopItem->Visible=false;
    DeletePopItem->Visible=true;
    ConnectPopItem->Visible=true;
    N1->Visible=true;
    FullItem->Visible=false;
    AroundItem->Visible=true;
    FontItem->Visible=false;
    OutParamItem->Visible=false;
    SelectImageItem->Visible=false;
    InvisibleItem->Visible=false;
    LoadImageItem->Visible=false;
    ShowFrameItem->Visible=false;
    }
   if(TypeClass=="TMyButton"/*static_cast<TIndicat*>(Sender)->Type==otIndicat*/)
    {
    ObjType=otMyButton;
    SelectObj=static_cast<TMyButton*>(Sender)->Number;
    //SwitchingPopItem->Visible=false;
    DeletePopItem->Visible=true;
    N1->Visible=true;
    FullItem->Visible=true;
    //AroundItem->Visible=false;
    FontItem->Visible=true;
    N3->Visible=true;//Caption
    //OutParamItem->Visible=false;
    //SelectImageItem->Visible=false;
    //InvisibleItem->Visible=false;
    //LoadImageItem->Visible=false;
    //ShowFrameItem->Visible=false;
    CalledFormItem->Visible=true;
    }

   if(TypeClass=="TClip"/*static_cast<TImage1*>(Sender)->Type==otPict*/)
    {
    ObjType=otClip;
    SelectObj=static_cast<TClip*>(Sender)->Number;
    SwitchingPopItem->Visible=true;
    bool Test=CheckMax(Picturies[SelectObj]->Signal);
    Test&=CheckMax(Picturies[SelectObj]->Signal);
    SwitchingPopItem->Enabled=!Test;
    SwitchingPopItem->Enabled=!Test;
    DeletePopItem->Visible=true;
    ConnectPopItem->Visible=true;
    N1->Visible=true;
    FullItem->Visible=false;
    AroundItem->Visible=false;
    FontItem->Visible=false;
    OutParamItem->Visible=false;
    SelectImageItem->Visible=true;
    InvisibleItem->Visible=true;
    LoadImageItem->Visible=true;
    ShowFrameItem->Visible=true;
    }
  int x=static_cast<TControl*>(Sender)->Left;
  int y=static_cast<TControl*>(Sender)->Top;
  PopupMenu->Popup(x,y+50);
  }
}
//---------------------------------------------------------------------------


void __fastcall TChildForm::RamkaDragOver(TObject *Sender, TObject *Source,
      int X, int Y, TDragState State, bool &Accept)
{
Accept=true;
        int x,y;
        if(!Resize)
        {
        x=(Ramka->Left)+X;y=(Ramka->Top)+Y;
        Ramka->Left=x-DragX;
        //Edit1->Text="Ramka";
        Ramka->Top=y-DragY;
        }
        else
        {
        //x=Ramka->Left;
        //y=Ramka->Top;
        //Ramka->Top=(Ramka->Top)+Y-DragY;
        //Ramka->Left=(Ramka->Left)+X-DragX;
        Ramka->Width=abs(DragObject->Width+X-DragX);
        Ramka->Height=abs(DragObject->Height+Y-DragY);
        }
MainForm->StatusBar->Panels->Items[3]->Text=IntToStr(Ramka->Width)+
" X "+IntToStr(Ramka->Height);
MainForm->StatusBar->Panels->Items[1]->Text="Сверху "+
IntToStr(Ramka->Top);
MainForm->StatusBar->Panels->Items[2]->Text="Слева "+
IntToStr(Ramka->Left);
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormDragOver(TObject *Sender, TObject *Source,
      int X, int Y, TDragState State, bool &Accept)
{
Accept=true;
//Ramka->Visible=true;
//TControl* Name=(static_cast <TControl*> (Source)->Name);
if(!Resize)
{
Ramka->Left=X-DragX+Image->Left;
Ramka->Top=Y-DragY+Image->Top;
//Edit1->Text="Form";
}
else
{
Ramka->Width=abs(DragObject->Width+X-Ramka->Left-DragX);
Ramka->Height=abs(DragObject->Height+Y-Ramka->Top-DragY);
}
MainForm->StatusBar->Color=clBtnFace;
MainForm->StatusBar->SimplePanel=false;
MainForm->StatusBar->Panels->Items[3]->Text=IntToStr(Ramka->Width)+
" X "+IntToStr(Ramka->Height);
MainForm->StatusBar->Panels->Items[1]->Text="Сверху "+
IntToStr(Ramka->Top);
MainForm->StatusBar->Panels->Items[2]->Text="Слева "+
IntToStr(Ramka->Left);
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::RamkaEndDrag(TObject *Sender, TObject *Target,
      int X, int Y)
{
DragObject->Left=Ramka->Left;
DragObject->Top=Ramka->Top;
DragObject->Width=Ramka->Width;
DragObject->Height=Ramka->Height;
DragObject->Visible=true;
Ramka->Visible=false;
//MainForm->StatusBar->Panels->Items[2]->Text=DragObject->Width+" X "+
//DragObject->Height;
MainForm->StatusBar->Panels->Items[3]->Text=IntToStr(Ramka->Width)+
" X "+IntToStr(Ramka->Height);
MainForm->StatusBar->Panels->Items[1]->Text="Сверху "+
IntToStr(Ramka->Top);
MainForm->StatusBar->Panels->Items[2]->Text="Слева "+
IntToStr(Ramka->Left);
}
//---------------------------------------------------------------------------


void __fastcall TChildForm::Edit1DblClick(TObject *Sender)
{
/*Ramka->Left=static_cast <TControl*> (Sender)->Left-1;
Ramka->Top=static_cast <TControl*> (Sender)->Top-1;
Ramka->Width=static_cast <TControl*> (Sender)->Width+2;
Ramka->Height=static_cast <TControl*> (Sender)->Height+2;
//static_cast <TControl*> (Sender)->Visible=false;
//DragX=X;
//DragY=Y;
if(Ramka->Visible)Ramka->Visible=false;
else Ramka->Visible=true;
DragObject=static_cast <TControl*> (Sender);*/
}
//---------------------------------------------------------------------------




void __fastcall TChildForm::FullItemClick(TObject *Sender)
{
if(ColorDialog->Execute())
 {
 if(ObjType==otLevel)
  {
  Levels[SelectObj]->LevelColor=ColorDialog->Color;
  }
 if(ObjType==otMyButton)if((Buttons[SelectObj])&&(ButtonPresent[SelectObj]))
  {
  Buttons[SelectObj]->Brush->Color=ColorDialog->Color;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::AroundItemClick(TObject *Sender)
{
if(ColorDialog->Execute())
{
if(ObjType==otLevel)
 {
 Levels[SelectObj]->AroundColor=ColorDialog->Color;
 }
if(ObjType==otIndicat)
 {
 Indicators[SelectObj]->AroundColor=ColorDialog->Color;
 }
}
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FontItemClick(TObject *Sender)
{
if((ObjType==otEdit)&&(EditsPresent[SelectObj])&&(Edits[SelectObj]))
 {
 FontDialog->Font=Edits[SelectObj]->Font;
 if(!FontDialog->Execute())return;
 Edits[SelectObj]->Font=FontDialog->Font;
 }
if((ObjType==otMyButton)&&(ButtonPresent[SelectObj])&&(Buttons[SelectObj]))
 {
 FontDialog->Font=Buttons[SelectObj]->Font;
 if(!FontDialog->Execute())return;
 Buttons[SelectObj]->Font=FontDialog->Font;
 }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormActivate(TObject *Sender)
{
#ifdef Debug
AddObjectItem->Visible=true;
N2->Visible=true;
#endif
MainForm->StatusBar->Panels->Items[0]->Text=MainForm->ActiveMDIChild->Caption;
OpenDialog->InitialDir=MainForm->ProgramDir+"\\Images";
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::ConnectPopItemClick(TObject *Sender)
{
AdConnThread->Suspended=true;
TFormOfConnect *Form;
Form=new TFormOfConnect(this);
Form->FieldComboBox->Visible=true;
Form->OnlySaved=false;
Form->RefreshForm();
//int SelAdam,SelChannel;
unsigned int Signal,SignalField;
switch(ObjType)
 {
 case otEdit:{Signal=Edits[SelectObj]->Signal;SignalField=Edits[SelectObj]->SignalField;}
 break;
 case otLevel:{Signal=Levels[SelectObj]->Signal;SignalField=Levels[SelectObj]->SignalField;}
 break;
 case otPict:{Signal=Picturies[SelectObj]->Signal;SignalField=Picturies[SelectObj]->SignalField;}
 break;
 case otIndicat:{Signal=Indicators[SelectObj]->Signal;SignalField=Indicators[SelectObj]->SignalField;}
 break;
 case otClip:{Signal=Clip[SelectObj]->Signal;SignalField=Clip[SelectObj]->SignalField;}
 }

/*TLocateOptions Flags;
Flags.Clear();
DataModule1->KanalsTable->Locate("Adam;Kanal",VarArrayOf(OPENARRAY(Variant,
(SelAdam,SelChannel))),Flags);*/

if(!(CheckMax(Signal)&&CheckMax(SignalField)))
{
Form->Signal=Signal;
Form->SignalField=SignalField;
}
//DataModule1->FindRecord1(SelAdam,SelChannel);
if(Form->ShowModal()==mrOk)
switch(ObjType)
 {
 case otEdit:
  {
  Edits[SelectObj]->Signal=Form->Signal;
  Edits[SelectObj]->SignalField=Form->SignalField;
  }
 break;
 case otLevel:
  {
  Levels[SelectObj]->Signal=Form->Signal;
  Levels[SelectObj]->SignalField=Form->SignalField;
  Levels[SelectObj]->Max=defPointerToSignals[Form->Signal]->Limits.Max;
  }
 break;
 case otPict:
  {
  Picturies[SelectObj]->Signal=Form->Signal;
  Picturies[SelectObj]->SignalField=Form->SignalField;
  }
 break;
 case otIndicat:
  {
  Indicators[SelectObj]->Signal=Form->Signal;
  Indicators[SelectObj]->SignalField=Form->SignalField;
  Indicators[SelectObj]->Max=defPointerToSignals[Form->Signal]->Limits.Max;
  }
 break;
 case otClip:
  {
  Clip[SelectObj]->Signal=Form->Signal;
  Clip[SelectObj]->SignalField=Form->SignalField;
  }
 }
delete Form;
AdConnThread->Suspended=false;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::DeletePopItemClick(TObject *Sender)
{
if(Application->MessageBox("Вы действительно хотите удалить объект", "Сообщение", MB_OKCANCEL +
    MB_ICONQUESTION)==IDCANCEL)return;

switch(ObjType)
 {
 case otEdit:
  {
  delete Edits[SelectObj];
  EditsPresent[SelectObj]=false;
  }
 break;
 case otLevel:
  {
  delete Levels[SelectObj];
  LevelPresent[SelectObj]=false;
  }
 break;
 case otPict:
  {
  delete Picturies[SelectObj];
  PicturiePresent[SelectObj]=false;
  }
 break;
 case otIndicat:
  {
  delete Indicators[SelectObj];
  IndicatPresent[SelectObj]=false;
  }
 break;
 case otClip:
  {
  delete Clip[SelectObj];
  ClipPresent[SelectObj]=false;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::SwitchingPopItemClick(TObject *Sender)
{
TSetOutParamForm *Forma;
Forma=new TSetOutParamForm(this);
float SwitchingMore1,SwitchingLess1;
/*TLocateOptions Flags;
Flags.Clear();
DataModule1->KanalsTable->Locate("Adam;Kanal",VarArrayOf(OPENARRAY(Variant,
(Picturies[SelectObj]->Adam,Picturies[SelectObj]->Channel))),Flags);*/
unsigned int Signal;
switch(ObjType)
 {
 case otPict:
  {
  //DataModule1->FindRecord1(Picturies[SelectObj]->Adam,Picturies[SelectObj]->Channel);
  Signal=Picturies[SelectObj]->Signal;
  SwitchingMore1=Picturies[SelectObj]->SwitchingMore;
  SwitchingLess1=Picturies[SelectObj]->SwitchingLess;
  }
 break;
 case otClip:
  {
  //DataModule1->FindRecord1(Clip[SelectObj]->Adam,Clip[SelectObj]->Channel);
  Signal=Clip[SelectObj]->Signal;
  SwitchingMore1=Clip[SelectObj]->SwitchingMore;
  SwitchingLess1=Clip[SelectObj]->SwitchingLess;
  }
 }
float min,max;
min=defPointerToSignals[Signal]->Limits.Min;//DataModule1->KanalsTable->FieldValues["Min"];
max=defPointerToSignals[Signal]->Limits.Max;//DataModule1->KanalsTable->FieldValues["Max"];
Forma->MinLabel1->Caption=FloatToStrF(min,ffFixed,5,6);
Forma->MaxLabel1->Caption=FloatToStrF(max,ffFixed,5,6);
Forma->MinLabel2->Caption=FloatToStrF(min,ffFixed,5,6);
Forma->MaxLabel2->Caption=FloatToStrF(max,ffFixed,5,6);
if((max-min)<1)
 {
 Forma->Scale=1000;
 Forma->TrackBar1->Min=min*1000;
 Forma->TrackBar1->Max=max*1000;
 Forma->TrackBar1->Position=SwitchingMore1*1000;
 Forma->TrackBar2->Min=min*1000;
 Forma->TrackBar2->Max=max*1000;
 Forma->TrackBar2->Position=SwitchingLess1*1000;
 //Forma->ScaleLabel->Caption="/1000";
 Forma->ValueLabel1->Caption=FloatToStr(SwitchingMore1);
 Forma->ValueLabel2->Caption=FloatToStr(SwitchingLess1);
 Forma->Scale=1000;
 if(Forma->ShowModal()==mrOk)
  {
  switch(ObjType)
   {
   case otPict:
    {
    Picturies[SelectObj]->SwitchingMore=float(Forma->TrackBar1->Position)/1000;
    Picturies[SelectObj]->SwitchingLess=float(Forma->TrackBar2->Position)/1000;
    }
   break;
   case otClip:
    {
    Clip[SelectObj]->SwitchingMore=float(Forma->TrackBar1->Position)/1000;
    Clip[SelectObj]->SwitchingLess=float(Forma->TrackBar2->Position)/1000;
    }
   }
  }
 }
if(((max-min)<100)&&((max-min)>=1))
 {
 Forma->Scale=10;
 Forma->TrackBar1->Min=min*10;
 Forma->TrackBar1->Max=max*10;
 Forma->TrackBar1->Position=SwitchingMore1*10;
 Forma->TrackBar2->Min=min*10;
 Forma->TrackBar2->Max=max*10;
 Forma->TrackBar2->Position=SwitchingLess1*10;
 //Forma->ScaleLabel->Caption="/10";
 Forma->ValueLabel1->Caption=FloatToStr(SwitchingMore1);
 Forma->ValueLabel2->Caption=FloatToStr(SwitchingLess1);
 Forma->Scale=10;

 if(Forma->ShowModal()==mrOk)
  {
  switch(ObjType)
   {
   case otPict:
    {
    Picturies[SelectObj]->SwitchingMore=float(Forma->TrackBar1->Position)/10;
    Picturies[SelectObj]->SwitchingLess=float(Forma->TrackBar2->Position)/10;

    }
   break;
   case otClip:
    {
    Clip[SelectObj]->SwitchingMore=float(Forma->TrackBar1->Position)/10;
    Clip[SelectObj]->SwitchingLess=float(Forma->TrackBar2->Position)/10;

    }
   }
  }
 }
if(((max-min)<10000)&&((max-min)>=100))
 {
 Forma->Scale=0.1;
 Forma->TrackBar1->Min=min*0.1;
 Forma->TrackBar1->Max=max*0.1;
 Forma->TrackBar1->Position=SwitchingMore1*0.1;
 Forma->TrackBar2->Min=min*0.1;
 Forma->TrackBar2->Max=max*0.1;
 Forma->TrackBar2->Position=SwitchingLess1*0.1;
 //Forma->ScaleLabel->Caption="*10";
 Forma->ValueLabel1->Caption=FloatToStr(SwitchingMore1);
 Forma->ValueLabel2->Caption=FloatToStr(SwitchingLess1);
 Forma->Scale=0.1;
 if(Forma->ShowModal()==mrOk)
  {
  switch(ObjType)
   {
   case otPict:
    {
    Picturies[SelectObj]->SwitchingMore=float(Forma->TrackBar1->Position)/0.1;
    Picturies[SelectObj]->SwitchingLess=float(Forma->TrackBar2->Position)/0.1;
    }
   break;
   case otClip:
    {
    Clip[SelectObj]->SwitchingMore=float(Forma->TrackBar1->Position)/0.1;
    Clip[SelectObj]->SwitchingLess=float(Forma->TrackBar2->Position)/0.1;
    }
   }
  }
 }
if(((max-min)<100000)&&((max-min)>=10000))
 {
 Forma->Scale=0.01;
 Forma->TrackBar1->Min=min*0.01;
 Forma->TrackBar1->Max=max*0.01;
 Forma->TrackBar1->Position=SwitchingMore1*0.01;
 Forma->TrackBar2->Min=min*0.01;
 Forma->TrackBar2->Max=max*0.01;
 Forma->TrackBar2->Position=SwitchingLess1*0.01;
 //Forma->ScaleLabel->Caption="*100";
 Forma->ValueLabel1->Caption=FloatToStr(SwitchingMore1);
 Forma->ValueLabel2->Caption=FloatToStr(SwitchingLess1);
 Forma->Scale=0.01;
 if(Forma->ShowModal()==mrOk)
  {
   switch(ObjType)
   {
   case otPict:
    {
    Picturies[SelectObj]->SwitchingMore=float(Forma->TrackBar1->Position)/0.01;
    Picturies[SelectObj]->SwitchingLess=float(Forma->TrackBar2->Position)/0.01;
    }
   break;
   case otClip:
    {
    Clip[SelectObj]->SwitchingMore=float(Forma->TrackBar1->Position)/0.01;
    Clip[SelectObj]->SwitchingLess=float(Forma->TrackBar2->Position)/0.01;
    }
   }
  }
 }
 /*Form->TrackBar->Frequency=(max-min)/1000;
Form->TrackBar->LineSize=(max-min)/1000;
Form->TrackBar->Min=min;
Form->TrackBar->Max=max;
Form->TrackBar->Position=Picturies[SelectObj]->Switching;
Form->MinLabel->Caption=min;
Form->MaxLabel->Caption=max;
Form->ValueLabel->Caption=FloatToStr(Picturies[SelectObj]->Switching);
if(Form->ShowModal()==mrOk)
{
Picturies[SelectObj]->Switching=Form->TrackBar->Position;
}*/
delete Forma;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::OutParamItemClick(TObject *Sender)
{
if((ObjType==otMyButton)&&(ButtonPresent[SelectObj])&&(Buttons[SelectObj]))
 {
 TForm* Form=new TForm(this);
 Form->Width=300;
 Form->Height=200;
 Form->Left=(Width-300)/2;
 Form->Top=(Height-200)/2;
 TEdit* Edit=new TEdit(Form);Edit->Width=250;
 Edit->Left=25;
 Edit->Top=30;
 Form->InsertControl(Edit);
 TBitBtn* Button=new TBitBtn(Form);
 Button->Left=(Form->Width-Button->Width)/2;
 Button->Top=100;
 Button->Kind=bkOK;
 Form->InsertControl(Button);
 Edit->Text=Buttons[SelectObj]->Caption;
 if(Form->ShowModal()==mrOk)
 Buttons[SelectObj]->Caption=Edit->Text;
 delete Button;delete Edit;delete Form;
 N3->Visible=false;
 }
else if(ObjType==otEdit)
{
TSetOutParamForm *Form;
Form=new TSetOutParamForm(this);
Form->IntEdit->Text=IntToStr(Edits[SelectObj]->Int);
Form->FactionalEdit->Text=IntToStr(Edits[SelectObj]->Factional);
if(Form->ShowModal()==mrOk)
 {
 Edits[SelectObj]->Int=StrToInt(Form->IntEdit->Text);
 Edits[SelectObj]->Factional=StrToInt(Form->FactionalEdit->Text);
 }
delete Form;
}
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::Timer1Timer(TObject *Sender)
{
for(int i=0;i<maxparam;i++)
 {
 if(IndicatPresent[i]) Indicators[i]->Operate();
 if(EditsPresent[i])
  {
  Edits[i]->Operate();
  }
 if(LevelPresent[i]) Levels[i]->Operate();
 if(PicturiePresent[i]) Picturies[i]->Operate();
 if(ClipPresent[i])
 Clip[i]->Operate();
 }
}
//---------------------------------------------------------------------------


void __fastcall TChildForm::N2Click(TObject *Sender)
{
StartItem->Checked=true;
if(MainForm->MoveItem->Checked)MainForm->MoveItemClick(this);
for(int i=0;i<maxparam;i++)
 {
 if(IndicatPresent[i]) Indicators[i]->Prepare();
 //if(EditsPresent[i]) Edits[i]->Operate();
 if(LevelPresent[i]) Levels[i]->Prepare();
 if(PicturiePresent[i]) Picturies[i]->Prepare();
 if(ClipPresent[i]) Clip[i]->Prepare();
 if(ButtonPresent[i])
 Buttons[i]->Prepare();
 }
Timer1->Enabled=true;
if(AdConnThread->Suspended==true)AdConnThread->Suspended=false;//Start Request
//if(LevelPresent[0])Edit1->Text=int(Levels[0]->LevelColor);
/*if(StartItem->Tag==1)
{
StartItem->Tag=0;
Timer1->Enabled=false;
}
else
{
StartItem->Tag=1;
Timer1->Enabled=true;
} */
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::PrepareItemClick(TObject *Sender)
{
if(!MainForm->MoveItem->Checked)MainForm->MoveItemClick(this);
MainForm->MoveItem->Checked=true;
Timer1->Enabled=false;
AdConnThread->Suspended=true;//Stoping request
for(int i=0;i<maxparam;i++)
 {
 //if(IndicatPresent[i]) Indicators[i]->Prepare();
 //if(EditsPresent[i]) Edits[i]->Operate();
 //if(LevelPresent[i]) Levels[i]->Prepare();
 if(PicturiePresent[i]) Picturies[i]->Visible=true;
 if(PicturiePresent[i]) Picturies[i]->Retur();
 if(ClipPresent[i]) Clip[i]->Visible=true;
 if(ClipPresent[i]) Clip[i]->Retur();
 if(ButtonPresent[i]) Buttons[i]->Retur();
 }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::SelectImageItemClick(TObject *Sender)
{
switch(ObjType)
 {
 case otOwner:
  {
  if(OpenDialog->Execute())
   {
   Pictur=ExtractFileName(OpenDialog->FileName);
   }
  }
 case otPict:
  {
  if(OpenDialog->Execute())
   {
   Picturies[SelectObj]->Imag=OpenDialog->FileName;
   Picturies[SelectObj]->Prepare();
   Picturies[SelectObj]->Stretch=false;
   Picturies[SelectObj]->AutoSize=true;
   Picturies[SelectObj]->AutoSize=false;
   }
  }
 break;
 case otClip:
  {
  TSelFrameForm *Form16=new TSelFrameForm(this);
  Form16->AddBitBtn->Visible=true;
  Form16->DelBitBtn->Visible=true;
  Form16->CanselBitBtn->Visible=true;
  Form16->ShowBitBtn->Visible=false;
  int Frame;
  int ModalResult=Form16->ShowModal();
  if(ModalResult==mrOk)
   {
   Frame=StrToInt(Form16->FrameEdit->Text);
   if(OpenDialog->Execute())
    {
    Clip[SelectObj]->Imag[Frame]=OpenDialog->FileName;
    Clip[SelectObj]->Prepare();
    Clip[SelectObj]->Stretch=false;
    Clip[SelectObj]->AutoSize=true;
    Clip[SelectObj]->AutoSize=false;
    if(Frame>=Clip[SelectObj]->MaxFrame) Clip[SelectObj]->MaxFrame=Frame;
    }
   }
  else if(ModalResult==mrAbort)
   {
   Frame=StrToInt(Form16->FrameEdit->Text);
   Clip[SelectObj]->Imag[Frame]="NULL";
   }
  delete Form16;
  }
 }
}
//---------------------------------------------------------------------------


void __fastcall TChildForm::InvisibleItemClick(TObject *Sender)
{
DragObject->Visible=false;
/*switch(ObjType)
 {
 case otEdit:
  {

  }
 break;
 case otLevel:
  {

  }
 break;
 case otPict:
  {
  Picturies[SelectObj]->Visible=false;
  }
 break;
 case otIndicat:
  {
  DragObject->Visible=true;
  }
 break;
 }*/                                 //OnKeyDown

}
//---------------------------------------------------------------------------

void __fastcall TChildForm::LoadImageItemClick(TObject *Sender)
{

 if(ObjType==otPict)
  {
  Picturies[SelectObj]->Picture->LoadFromFile(MainForm->ProgramDir+"\\Images\\Label.bmp");
  Picturies[SelectObj]->Stretch=true;
  }
 if(ObjType==otClip)
  {
  Clip[SelectObj]->Picture->LoadFromFile(MainForm->ProgramDir+"\\Images\\Label.bmp");
  Clip[SelectObj]->Stretch=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if((MainForm->EnablDrag)&&(DragObject!=NULL))
{
 if(Shift.Contains(ssShift))
  {
  switch(Key)
   {
   case 0x27:      //Left
    {
    DragObject->Width++;
    RefreshStateBar();
    }
   break;
   case 0x25://Right
    {
    DragObject->Width--;
    RefreshStateBar();
    }
   break;
   case 0x26://Up
    {
    DragObject->Height--;
    RefreshStateBar();
    }
   break;
   case 0x28://Down
    {
    DragObject->Height++;
    RefreshStateBar();
    }
   break;
   }
  }
 if(Shift.Contains(ssCtrl))
  {
  switch(Key)
   {
   case 0x27://Left
    {
    DragObject->Left++;
    RefreshStateBar();
    }
   break;
   case 0x25://Right
    {
    DragObject->Left--;
    RefreshStateBar();
    }
   break;
   case 0x26://Up
    {
    DragObject->Top--;
    RefreshStateBar();
    }
   break;
   case 0x28://Down
    {
    DragObject->Top++;
    RefreshStateBar();
    }
   break;
   }
  }
 }
}
//---------------------------------------------------------------------------
inline void TChildForm::RefreshStateBar()
 {
 MainForm->StatusBar->Panels->Items[3]->Text=IntToStr(DragObject->Width)+
 " X "+IntToStr(DragObject->Height);
 MainForm->StatusBar->Panels->Items[1]->Text="Сверху "+
 IntToStr(DragObject->Top);
 MainForm->StatusBar->Panels->Items[2]->Text="Слева "+
 IntToStr(DragObject->Left);
 }
//---------------------------------------------------------------------------
void __fastcall TChildForm::ShowFrameItemClick(TObject *Sender)
{
TSelFrameForm *Form17=new TSelFrameForm(this);
Form17->AddBitBtn->Visible=false;
Form17->DelBitBtn->Visible=false;
Form17->CanselBitBtn->Visible=true;
Form17->ShowBitBtn->Visible=true;
int ModalResult1=Form17->ShowModal();
int Frame=StrToInt(Form17->FrameEdit->Text);
switch(ObjType)
 {
  case otClip:
  {
  if(ModalResult1==mrOk)
   Clip[SelectObj]->SetFrame(Frame);
  }
 break;
 }
}
//---------------------------------------------------------------------------


void __fastcall TChildForm::ImageMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(Button==mbRight)
 {
 ObjType=otOwner;
 SelectObj=-1;
 for(int i=0;i<PopupMenu->Items->Count;i++)
  {
  PopupMenu->Items->Items[i]->Visible=false;
  }
 SelectImageItem->Visible=true;
 N3->Visible=true;
 PopupMenu->Popup(X+Left,Y+Top+30);
 }
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::N3Click(TObject *Sender)
{
TForm* Form=new TForm(this);
 Form->Width=300;
 Form->Height=200;
 Form->Left=(Width-300)/2;
 Form->Top=(Height-200)/2;
 Form->Caption="Напишите название";
 TEdit* Edit=new TEdit(Form);
 Edit->Width=250;Edit->Left=25;
 Edit->Top=30;
 Form->InsertControl(Edit);
 TBitBtn* Button=new TBitBtn(Form);
 Button->Left=(Form->Width-Button->Width)/2;
 Button->Top=100;
 Button->Kind=bkOK;
 Form->InsertControl(Button);
 if(ObjType==otOwner)
 {
 Edit->Text=Caption;
 if(Form->ShowModal()==mrOk)
 Caption=Edit->Text;
 }
if((ObjType==otMyButton)&&(ButtonPresent[SelectObj])&&(Buttons[SelectObj]))
 {
 Edit->Text=Buttons[SelectObj]->Caption;
 if(Form->ShowModal()==mrOk)
 Buttons[SelectObj]->Caption=Edit->Text;
 }
delete Button;delete Edit;delete Form;
N3->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::CalledFormItemClick(TObject *Sender)
{
/*TForm* Form=new TForm(this);
 Form->Width=300;
 Form->Height=200;
 Form->Left=(Width-300)/2;
 Form->Top=(Height-200)/2;
 Form->Caption="Напишите название";
 TEdit* Edit=new TEdit(Form);
 Edit->Width=250;Edit->Left=25;
 Edit->Top=30;
 Form->InsertControl(Edit);
 TBitBtn* Button=new TBitBtn(Form);
 Button->Left=(Form->Width-Button->Width)/2;
 Button->Top=100;
 Button->Kind=bkOK;
 Form->InsertControl(Button);*/
if((ObjType==otMyButton)&&(ButtonPresent[SelectObj])&&(Buttons[SelectObj]))
 {
 if(MainForm->OpenDialog->Execute())
  {
  Buttons[SelectObj]->AssociateForm=ExtractFileName(MainForm->OpenDialog->FileName);
  Buttons[SelectObj]->Action=baCallForm;
  }
 //Edit->Text=Buttons[SelectObj]->Caption;
 //if(Form->ShowModal()==mrOk)
 //Buttons[SelectObj]->Caption=Edit->Text;
 }
//delete Button;delete Edit;delete Form;
}
//---------------------------------------------------------------------------



void __fastcall TChildForm::StretchItemClick(TObject *Sender)
{
StretchItem->Checked=!StretchItem->Checked;
if((ObjType==otPict)&&(PicturiePresent[SelectObj])&&(Picturies[SelectObj]))
 {
 Picturies[SelectObj]->Stretch=StretchItem->Checked;
 }
}
//---------------------------------------------------------------------------

