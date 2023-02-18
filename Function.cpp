//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Functions.h"
#include "MainUnut.h"
#include "DataUnit.h"
//#include "windows.h"
#include "windowsx.h"

#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------
//bool CheckMax(
void CopyToReserve()
{
/*DataModule1->ReservStatTable->Active=false;
DataModule1->ReservStatTable->Exclusive=true;
DataModule1->ReservStatTable->Active=true;
DataModule1->ReservStatTable->EmptyTable();
DataModule1->ReservStatTable->Active=false;
DataModule1->ReservStatTable->Exclusive=false;
DataModule1->ReservStatTable->Active=true;*/
DataModule1->ReservStatTable->Active=true;
DataModule1->ReservStatTable->Filtered=false;
DataModule1->ReservStatTable->First();
while((!DataModule1->ReservStatTable->Eof)&&(DataModule1->ReservStatTable->RecordCount))
  DataModule1->ReservStatTable->Delete();
TDateTime a=Date();
a-=reservestoredays;//два предыдущих дня
AnsiString DateSort="(Date>'"+a.DateString()+"')";
DataModule1->StatistTable->Filtered=false;
DataModule1->StatistTable->Filter=DateSort;
DataModule1->StatistTable->Filtered=true;
DataModule1->StatistTable->RecordCount;
do
 {
 DataModule1->ReservStatTable->Append();
 DataModule1->ReservStatTable->FieldValues["Date"]=
 DataModule1->StatistTable->FieldValues["Date"];
 DataModule1->ReservStatTable->FieldValues["Hours"]=
 DataModule1->StatistTable->FieldValues["Hours"];
 DataModule1->ReservStatTable->FieldValues["Minuts"]=
 DataModule1->StatistTable->FieldValues["Minuts"];
 DataModule1->ReservStatTable->FieldValues["Seconds"]=
 DataModule1->StatistTable->FieldValues["Seconds"];
 DataModule1->ReservStatTable->FieldValues["Numb"]=
 DataModule1->StatistTable->FieldValues["Numb"];
 DataModule1->ReservStatTable->FieldValues["Value"]=
 DataModule1->StatistTable->FieldValues["Value"];
 DataModule1->ReservStatTable->Post();
 }
while(DataModule1->StatistTable->FindNext());
DataModule1->StatistTable->Filtered=false;
}
//----------------------------------------------------------------------------
void RefreshStat()
{
//int Counter=0;
DataModule1->StatistTable->Active=true;
TDateTime a=Date();
a-=datastoredays;//шестьдесят предыдущих дней
AnsiString DateSort="(Date<'"+a.DateString()+"')";
DataModule1->StatistTable->First();
DataModule1->StatistTable->Filtered=false;
DataModule1->StatistTable->Filter=DateSort;
DataModule1->StatistTable->Filtered=true;
DataModule1->StatistTable->First();
//DataModule1->StatistTable->RecordCount;
if((!DataModule1->StatistTable->Eof)&&(DataModule1->StatistTable->RecordCount))
for(int i=0;((i<10000)&(!DataModule1->StatistTable->Eof));i++)
{
DataModule1->StatistTable->Delete();
}
/*do
 {
 TDateTime b=DataModule1->StatistTable->FieldByName("Date")->AsDateTime;
 if(b<a)
  {
  DataModule1->StatistTable->Delete();
  Counter=0;
  }
 else
  {
  //if(!DataModule1->StatistTable->FindNext())return;
  Counter++;
  if(Counter>=10)return;
  }
 }
while(DataModule1->StatistTable->FindNext());*/
}
//----------------------------------------------------------------------------
void RefreshAlarm()
{
TDateTime a=Date();
a-=30;//шестьдесят предыдущих дней
AnsiString DateSort="(Date<'"+a.DateString()+"')";
DataModule1->AlarmTable->Active=true;
if(DataModule1->AlarmTable->RecordCount)
 {
 DataModule1->AlarmTable->First();
 DataModule1->AlarmTable->Filtered=false;
 DataModule1->AlarmTable->Filter=DateSort;
 DataModule1->AlarmTable->Filtered=true;
 DataModule1->AlarmTable->First();
 if(!DataModule1->AlarmTable->Eof)
 for(int i=0;((i<10000)&(!DataModule1->AlarmTable->Eof));i++)
  {
  DataModule1->AlarmTable->Delete();
  }
 }
/*int Counter=0;
TDateTime a=Date();
a-=60;//шестьдесят предыдущих дней
AnsiString DateSort="(Date>'"+a.DateString()+"')";
DataModule1->AlarmTable->Active=true;
DataModule1->AlarmTable->First();
DataModule1->AlarmTable->Filtered=false;
DataModule1->AlarmTable->Filter=DateSort;
DataModule1->AlarmTable->Filtered=true;
while(!DataModule1->AlarmTable->Eof)
 {
 TDateTime b=DataModule1->AlarmTable->FieldByName("Date")->AsDateTime;
 if(b<a)
  {
  DataModule1->AlarmTable->Delete();
  Counter=0;
  }
 else
  {
  if(!DataModule1->AlarmTable->FindNext())return;
  Counter++;
  if(Counter>=10)
    {
    DataModule1->AlarmTable->Filtered=false;
    DataModule1->StatistTable->Filtered=false;
    return;
    }
  }
 }
DataModule1->AlarmTable->Filtered=false;
DataModule1->StatistTable->Filtered=false;*/
}
//----------------------------------------------------------------------------
float TransformStr(AnsiString Str,bool& Fail)
{
AnsiString Str1="";
char Sel;
if((Str=="")||(Str==" ")||(Str=="0"))
{
Fail=true;
return 0;
}
for(int i=1;i<(Str.Length()+1);i++)
  {
  Sel=Str[i];
  if((Sel!='.')&&(Sel!=',')&&(Sel>=47)&&(Sel<=57)) Str1=Str1+Str[i];
  else if((Sel=='.')||(Sel==',')) Str1=Str1+",";
  else
   {
   Fail=true;
   return 0;
   }
  }

 {
 Fail=false;
 return(StrToFloat(Str1));
 }
}
//-----------------------------------------------------------------------------
AnsiString TransformFloat(float var)
{
AnsiString Str;
Char Sel;
//int Zn=0;
Str=FloatToStrF(var,ffFixed,10,9);
if(var==0) return "0";
/*for(int i=1;i<(Str.Length()+1);i++)
  {
  Sel=Str[i];
  if(Sel==',')Zn=i;
  }*/
//if(Zn==0)return Str;
int i=(Str.Length()),fine;
bool flag=true;
while(flag)
  {
  Sel=Str[i];
  if(Sel!='0')
   {
   fine=i;
   flag=false;
   }
  i--;
  }
if(Str[fine]==',')fine--;
AnsiString OutString="";
for(i=1;i<fine+1;i++)
  {
  Sel=Str[i];
  OutString+=Sel;
  }
return OutString;
}
//----------------------------------------------------------------------------
void Pause(int num)
{
int Max=num*speed;
for(int i=0;i<Max;i++)
 {
 int a=0;
 a++;
 //if(a>num)return;
 }
}
//----------------------------------------------------------------------------
bool GetName(TControl* AOwner,AnsiString& Str)
{
TForm* Form=new TForm(AOwner);
 Form->Width=300;
 Form->Height=170;
 Form->Left=(AOwner->Width-300)/2;
 Form->Top=(AOwner->Height-200)/2;
 Form->Caption="Напишите название группы";
 TEdit* Edit=new TEdit(Form);
 Edit->Width=250;Edit->Left=25;
 Edit->Top=30;
 Form->InsertControl(Edit);
 TBitBtn* Button=new TBitBtn(Form);
 Button->Left=(Form->Width-Button->Width)/2;
 Button->Top=100;
 Button->Kind=bkOK;
 Form->InsertControl(Button);
bool Flag=0;
if(Form->ShowModal()==mrOk)
 {
 Flag=true;
 Str=Edit->Text;
 }
else Flag=false;
delete Button;delete Edit;delete Form;
return Flag;
}
//----------------------------------------------------------------------------
//Класс Индикаторов
__fastcall TIndicat::TIndicat(TComponent* Owner)
            : TPaintBox(Owner)
{
FMax=100;
FInput=0;
Height=100;
Width=20;
FType=otIndicat;
//FAdam=1000;
//FChannel=1000;
Signal=-1;
SignalField=itOut;
}

void __fastcall TIndicat::SetInput(float a)
{
if(a>FMax) FInput=FMax;
else FInput=a;
Invalidate();
}

void __fastcall TIndicat::SetMax(float m)
{
FMax=m;
Invalidate();
}

void __fastcall TIndicat::Paint()
{
//float w=Width;
//float h=Height;
float scale=float(Height)/Max;
char c;
Canvas->Pen->Color=AroundColor;
Canvas->MoveTo(0,0);
Canvas->LineTo(Width-1,0);
Canvas->LineTo(Width-1,Height-1);
Canvas->LineTo(0,Height-1);
Canvas->LineTo(0,0);
if(Signal==-1)return;
if(Input<=Max/2)
for(float i=0;i<Input*scale;i++)
 {
 c=255.0*i/scale/Max*2;
 Canvas->Pen->Color=TColor(RGB(c,255,0));
 Canvas->MoveTo(1,Height-i);
 Canvas->LineTo(Width-1,Height-i);
 }
else
 {
 for(float i=0;i<Height/2;i++)
  {
  c=255.0*i/scale/Max*2;
  Canvas->Pen->Color=TColor(RGB(c,255,0));
  Canvas->MoveTo(1,Height-i);
  Canvas->LineTo(Width-1,Height-i);
  }
 for(float i=float(Height)/2;i<Input*scale;i++)
  {
  c=255-255.0*(i-Height/2)/scale/Max*2;
  Canvas->Pen->Color=TColor(RGB(255,c,0));
  Canvas->MoveTo(1,Height-i);
  Canvas->LineTo(Width-1,Height-i);
  }
 }
Canvas->Pen->Color=AroundColor;
Canvas->MoveTo(0,Height/2);
Canvas->LineTo(Width,Height/2);
}

void TIndicat::Operate(void)
{
//unsigned int CurrentNumb=defExtDev[
float InpSignal;//=MainForm->Signal[Adam][Channel];
if((Signal!=-1)&&(defPointerToSignals[Signal]))
 {
 switch(SignalField)
  {
  case itInp:InpSignal=defPointerToSignals[Signal]->InpValue;
  break;
  case itCalc:InpSignal=defPointerToSignals[Signal]->CalcValue;
  break;
  case itOut:InpSignal=defPointerToSignals[Signal]->OutValue;
  break;
  default:InpSignal=0;
  }
 }
else InpSignal=0;
if((Input==0)||(fabs(Input-InpSignal)/Input>0.005))Input=InpSignal;
}//Fine of Operate for Indicat

void TIndicat::Prepare(void)
{
//DataModule1->FindRecord1(Adam,Channel);
//float min,max;
//min=DataModule1->KanalsTable->FieldValues["Min"];
//Max=DataModule1->KanalsTable->FieldValues["Max"];
if(defPointerToSignals[Signal])
 {
 Max=defPointerToSignals[Signal]->Limits.Max;
 }
}//Fine of Prepare for Indicat

void TIndicat::SaveToIniFile(TIniFile *IniFile,AnsiString Section)
{
IniFile->WriteInteger(Section,"Left",Left);
IniFile->WriteInteger(Section,"Top",Top);
IniFile->WriteInteger(Section,"Height",Height);
IniFile->WriteInteger(Section,"Width",Width);
IniFile->WriteInteger(Section,"Signal",Signal);
IniFile->WriteInteger(Section,"SignalField",SignalField);
IniFile->WriteInteger(Section,"AroundColor",int(AroundColor));
IniFile->WriteInteger(Section,"Number",Number);
IniFile->WriteInteger(Section,"Type",int(Type));
IniFile->WriteString (Section,"Max",FloatToStr(Max));
}//Fine of SaveToFile for Indicat

void TIndicat::LoadFromIniFile(TIniFile *IniFile,AnsiString Section)
{
Left=IniFile->ReadInteger(Section,"Left",50);
Top=IniFile->ReadInteger(Section,"Top",50);
Height=IniFile->ReadInteger(Section,"Height",50);
Width=IniFile->ReadInteger(Section,"Width",50);
Signal=IniFile->ReadInteger(Section,"Signal",-1);
SignalField=IniFile->ReadInteger(Section,"SignalField",itOut);
FAroundColor=TColor(IniFile->ReadInteger(Section,"AroundColor",0));
FNumber=IniFile->ReadInteger(Section,"Number",0);
FType=TObjectType(IniFile->ReadInteger(Section,"Type",1));
FMax=StrToFloat(IniFile->ReadString(Section,"Max",100));
}
//--------------------------------
//Класс Уровней
__fastcall TLevel::TLevel(TComponent* Owner)
            : TPaintBox(Owner)
{
FMax=100;
FInput=0;
Height=100;
Width=20;
LevelColor=clGreen;
FType=otLevel;
//FAdam=1000;
//FChannel=1000;
Signal=-1;
SignalField=itOut;
}
void __fastcall TLevel::SetAround(TColor a)
{
FAroundColor=a;
Invalidate();
}
void __fastcall TLevel::SetFull(TColor a)
{
FLevelColor=a;
Invalidate();
}
void __fastcall TLevel::SetInput(float a)
{
if((abs(a-FInput)/FMax<0.005))return;
if(a>FMax) FInput=FMax;
else FInput=a;
Invalidate();
}
void __fastcall TLevel::SetMax(float m)
{
FMax=m;
Invalidate();
}
void __fastcall TLevel::Paint()
{
if(Signal==-1)return;
float w=Width;
float h=Height;
if(FMax<1E-20)FMax=1E-20;
float scale=h/Max;
//char c;
Canvas->Pen->Color=AroundColor;
Canvas->MoveTo(0,0);
Canvas->LineTo(w-1,0);
Canvas->LineTo(w-1,h-1);
Canvas->LineTo(0,h-1);
Canvas->LineTo(0,0);
Canvas->Pen->Color=LevelColor;
if(Input!=0)
{
for(float i=0;i<Input*scale;i++)
 {
 Canvas->MoveTo(1,h-i);
 Canvas->LineTo(w-1,h-i);
 }
}
Canvas->Pen->Color=AroundColor;
Canvas->MoveTo(0,h/2);
Canvas->LineTo(w,h/2);
}
void TLevel::Operate(void)
{
float InpSignal;//=MainForm->Signal[Adam][Channel];
if((Signal!=-1)&&(defPointerToSignals[Signal]))
 {
 switch(SignalField)
  {
  case itInp:InpSignal=defPointerToSignals[Signal]->InpValue;
  break;
  case itCalc:InpSignal=defPointerToSignals[Signal]->CalcValue;
  break;
  case itOut:InpSignal=defPointerToSignals[Signal]->OutValue;
  break;
  default:InpSignal=0;
  }
 }
else InpSignal=0;
if((Input==0)||(fabs(Input-InpSignal)/Input>0.005))
Input=InpSignal;
}//Fine of Operate for Level
void TLevel::Prepare(void)
{
if(defPointerToSignals[Signal])
 {
 Max=defPointerToSignals[Signal]->Limits.Max;
 }
/*TLocateOptions Flags;
Flags.Clear();
DataModule1->KanalsTable->Locate("Adam;Kanal",VarArrayOf(OPENARRAY(Variant,
(Adam,Channel))),Flags);
Max=DataModule1->KanalsTable->FieldValues["Max"];*/
}//Fine of Prepare for Level

void TLevel::SaveToIniFile(TIniFile *IniFile,AnsiString Section)
{
IniFile->WriteInteger(Section,"Left",Left);
IniFile->WriteInteger(Section,"Top",Top);
IniFile->WriteInteger(Section,"Height",Height);
IniFile->WriteInteger(Section,"Width",Width);
IniFile->WriteInteger(Section,"Signal",Signal);
IniFile->WriteInteger(Section,"SignalField",SignalField);
IniFile->WriteInteger(Section,"AroundColor",int(AroundColor));
IniFile->WriteInteger(Section,"FillColor",int(LevelColor));
IniFile->WriteInteger(Section,"Number",FNumber);
IniFile->WriteInteger(Section,"Type",int(FType));
IniFile->WriteString (Section,"Max",FloatToStr(Max));
}//Fine of SaveToFile for Level

void TLevel::LoadFromIniFile(TIniFile *IniFile,AnsiString Section)
{
Left=IniFile->ReadInteger(Section,"Left",50);
Top=IniFile->ReadInteger(Section,"Top",50);
Height=IniFile->ReadInteger(Section,"Height",50);
Width=IniFile->ReadInteger(Section,"Width",50);
Signal=IniFile->ReadInteger(Section,"Signal",-1);
SignalField=IniFile->ReadInteger(Section,"SignalField",itOut);
FAroundColor=TColor(IniFile->ReadInteger(Section,"AroundColor",0));
FLevelColor=TColor(IniFile->ReadInteger(Section,"FillColor",8421376));
FNumber=IniFile->ReadInteger(Section,"Number",0);
FType=TObjectType(IniFile->ReadInteger(Section,"Type",1));
FMax=StrToFloat(IniFile->ReadString(Section,"Max",100));
}
//-----------------------------------------------
//Класс Окон.
__fastcall TEdit1::TEdit1(TComponent* Owner)
            : TEdit(Owner)
{
FType=otEdit;
AutoSize=false;
FFactional=2;
FInt=5;
//FAdam=1000;
//FChannel=1000;
ReadOnly=true;
Width=37;
Height=17;
//Alarm=false;
FBackGroundColor=clWindow;
FRed=false;
TabStop=false;
Signal=-1;
SignalField=itOut;
}

void TEdit1::Operate(void)
{
if(Signal==-1)
 {
 Color=FBackGroundColor;
  return;
 }
float InpSignal;//=MainForm->Signal[Adam][Channel];
if((Signal!=-1)&&(defPointerToSignals[Signal]))
 {
 switch(SignalField)                      //DataModule1->Signal
  {
  case itInp:InpSignal=defPointerToSignals[Signal]->InpValue;
  break;
  case itCalc:InpSignal=defPointerToSignals[Signal]->CalcValue;
  break;
  case itOut:InpSignal=defPointerToSignals[Signal]->OutValue;
  break;
  default:InpSignal=0;
  }
 }
else InpSignal=0;
if((defPointerToSignals[Signal])&&(defPointerToSignals[Signal]->CritSignal))
 {
 if(FRed==true)
  {
  Color=FBackGroundColor;
  FRed=false;
  }
 else
  {
  Color=clRed;
  FRed=true;
  }
 }
else Color=FBackGroundColor;
Text=FloatToStrF(InpSignal,ffFixed,FInt,FFactional);
}//Fine of Operate for Edit1

void TEdit1::SaveToIniFile(TIniFile *IniFile,AnsiString Section)
{
IniFile->WriteInteger(Section,"Left",Left);
IniFile->WriteInteger(Section,"Top",Top);
IniFile->WriteInteger(Section,"Height",Height);
IniFile->WriteInteger(Section,"Width",Width);
IniFile->WriteInteger(Section,"Signal",Signal);
IniFile->WriteInteger(Section,"SignalField",SignalField);
IniFile->WriteInteger(Section,"Int",FInt);
IniFile->WriteInteger(Section,"Factional",FFactional);
IniFile->WriteInteger(Section,"FontSize",Font->Size);
IniFile->WriteInteger(Section,"FontColor",Font->Color);
IniFile->WriteBool(Section,"FontItalic",Font->Style.Contains(fsItalic));
IniFile->WriteBool(Section,"FontBold",Font->Style.Contains(fsBold));
IniFile->WriteBool(Section,"FontUnderLine",Font->Style.Contains(fsUnderline));
IniFile->WriteBool(Section,"FontStrike",Font->Style.Contains(fsStrikeOut));
IniFile->WriteString(Section,"FontName",Font->Name);
IniFile->WriteInteger(Section,"Number",FNumber);
IniFile->WriteInteger(Section,"Type",int(FType));
}//Fine of SaveToFile for Edits

void TEdit1::LoadFromIniFile(TIniFile *IniFile,AnsiString Section)
{
Left=IniFile->ReadInteger(Section,"Left",50);
Top=IniFile->ReadInteger(Section,"Top",50);
Height=IniFile->ReadInteger(Section,"Height",50);
Width=IniFile->ReadInteger(Section,"Width",50);
Signal=IniFile->ReadInteger(Section,"Signal",-1);
SignalField=IniFile->ReadInteger(Section,"SignalField",itOut);
FInt=IniFile->ReadInteger(Section,"Int",5);
FFactional=IniFile->ReadInteger(Section,"Factional",2);
Font->Size=IniFile->ReadInteger(Section,"FontSize",8);
Font->Color=IniFile->ReadInteger(Section,"FontColor",clBlack);
TFontStyles a;
if(IniFile->ReadBool(Section,"FontItalic",false))a<<fsItalic;
if(IniFile->ReadBool(Section,"FontBold",false))a<<fsBold;
if(IniFile->ReadBool(Section,"FontUnderLine",false))a<<fsUnderline;
if(IniFile->ReadBool(Section,"FontStrike",false))a<<fsStrikeOut;
Font->Style=a;
Font->Name=IniFile->ReadString(Section,"FontName","MS Sans Serf");
FNumber=IniFile->ReadInteger(Section,"Number",0);
FType=TObjectType(IniFile->ReadInteger(Section,"Type",0));
}
//------------------------------------------------
//Класс картинок
__fastcall TImage1::TImage1(TComponent* Owner)
            : TImage(Owner)
{
//FAdam=1000;
//FChannel=1000;
Stretch=true;
Signal=-1;
SignalField=itOut;
FType=otPict;
FImag=MainForm->ProgramDir+"\\Images\\Label.bmp";
//FCurrentFrame=0;
}


void TImage1::Prepare(void)
{
//TLocateOptions Flags;
//Flags.Clear();
//DataModule1->KanalsTable->Locate("Adam;Kanal",VarArrayOf(OPENARRAY(Variant,
//(Adam,Channel))),Flags);
Picture->LoadFromFile(FImag);
//Stretch=false;
}

void TImage1::Operate(void)
{
if(Signal==-1)return;

float InpSignal;//=MainForm->Signal[Adam][Channel];
if((Signal!=-1)&&(defPointerToSignals[Signal]))
 {
 switch(SignalField)
  {
  case itInp:InpSignal=defPointerToSignals[Signal]->InpValue;
  break;
  case itCalc:InpSignal=defPointerToSignals[Signal]->CalcValue;
  break;
  case itOut:InpSignal=defPointerToSignals[Signal]->OutValue;
  break;
  default:InpSignal=0;
  }
 }
else InpSignal=0;
if((InpSignal>=FSwitchMore)&&(InpSignal<FSwitchLess))  Visible=true;
else  Visible=false;
//int a=0;
}//Fine of Operate for Image1
void TImage1::Retur(void)
{
if(FImag==MainForm->ProgramDir+"\\Images\\Label.bmp")
Picture->LoadFromFile(MainForm->ProgramDir+"\\Images\\Label.bmp");
else
Picture->LoadFromFile(FImag);
//Stretch=true;
}

void TImage1::SaveToIniFile(TIniFile *IniFile,AnsiString Section)
{
IniFile->WriteInteger(Section,"Left",Left);
IniFile->WriteInteger(Section,"Top",Top);
IniFile->WriteInteger(Section,"Height",Height);
IniFile->WriteInteger(Section,"Width",Width);
IniFile->WriteInteger(Section,"Signal",Signal);
IniFile->WriteInteger(Section,"SignalField",SignalField);
IniFile->WriteString(Section,"SwitchLess",FloatToStr(FSwitchLess));
IniFile->WriteString(Section,"SwitchMore",FloatToStr(FSwitchMore));
IniFile->WriteString(Section,"Image",ExtractFileName(FImag));
IniFile->WriteInteger(Section,"Number",FNumber);
IniFile->WriteInteger(Section,"Type",int(FType));
IniFile->WriteBool(Section,"Stretch",Stretch);
}//Fine of SaveToFile for Images

void TImage1::LoadFromIniFile(TIniFile *IniFile,AnsiString Section)
{
Signal=IniFile->ReadInteger(Section,"Signal",-1);
SignalField=IniFile->ReadInteger(Section,"SignalField",itOut);
FSwitchLess=StrToFloat(IniFile->ReadString(Section,"SwitchLess",0));
FSwitchMore=StrToFloat(IniFile->ReadString(Section,"SwitchMore",0));
FImag=MainForm->ProgramDir+"\\Images\\"+IniFile->ReadString(Section,"Image","Label.bmp");
FNumber=IniFile->ReadInteger(Section,"Number",0);
FType=TObjectType(IniFile->ReadInteger(Section,"Type",3));
Stretch=IniFile->ReadBool(Section,"Stretch",1);
Left=IniFile->ReadInteger(Section,"Left",50);
Top=IniFile->ReadInteger(Section,"Top",50);
Height=IniFile->ReadInteger(Section,"Height",50);
Width=IniFile->ReadInteger(Section,"Width",50);
}
//----------------------End TImage1
//-----------------------------------------------------------------------------
//----------------------TMyButton
__fastcall TMyButton::TMyButton(TComponent* Owner)
            : TBitBtn(Owner)
{
FType=otMyButton;
Signal=-1;
SignalField=itOut;
int FNumber;
FAction=baNotDefine;
FAssociateForm="";
OnClick=0;
}
void __fastcall TMyButton::BitBtn1Click(TObject *Sender)
{
if(FAction==baNotDefine)return;
switch(FAction)
 {
 case baCallForm:
 bool Test=false;
 for(int i=0;i<MainForm->MDIChildCount;i++)
  if((MainForm->MDIChildren[i])&&(MainForm->MDIChildType[i]==1)&&
  (ExtractFileName(static_cast<TChildForm*>(MainForm->MDIChildren[i])->FileName)==FAssociateForm))Test=true;
 if((!Test)&&(FAssociateForm!=""))
  {
  TIniFile *IniFile;
  IniFile=new TIniFile(MainForm->ProgramDir+"\\"+ExtractFileName(FAssociateForm));
  TChildForm *Forma2;
  Forma2=new TChildForm(MainForm);
  static_cast<TChildForm*>(MainForm->ActiveMDIChild)->LoadFromIniFile(IniFile);
  delete IniFile;
  //ShaxtMenu->Enabled=false;
  static_cast<TChildForm*>(MainForm->ActiveMDIChild)->N2Click(this);//Start work
  }
 break;
 }
}
void TMyButton::SaveToIniFile(TIniFile* IniFile,AnsiString Section)
{
IniFile->WriteInteger(Section,"Left",Left);
IniFile->WriteInteger(Section,"Top",Top);
IniFile->WriteInteger(Section,"Height",Height);
IniFile->WriteInteger(Section,"Width",Width);
IniFile->WriteInteger(Section,"Signal",Signal);
IniFile->WriteInteger(Section,"SignalField",SignalField);
//IniFile->WriteInteger(Section,"Int",FInt);
//IniFile->WriteInteger(Section,"Factional",FFactional);
IniFile->WriteInteger(Section,"FontSize",Font->Size);
IniFile->WriteInteger(Section,"FontColor",Font->Color);
IniFile->WriteBool(Section,"FontItalic",Font->Style.Contains(fsItalic));
IniFile->WriteBool(Section,"FontBold",Font->Style.Contains(fsBold));
IniFile->WriteBool(Section,"FontUnderLine",Font->Style.Contains(fsUnderline));
IniFile->WriteBool(Section,"FontStrike",Font->Style.Contains(fsStrikeOut));
IniFile->WriteString(Section,"FontName",Font->Name);
IniFile->WriteInteger(Section,"Number",FNumber);
IniFile->WriteInteger(Section,"Type",int(FType));
IniFile->WriteInteger(Section,"Action",int(FAction));
IniFile->WriteString(Section,"AssociateForm",FAssociateForm);
IniFile->WriteString(Section,"Caption",Caption);
}
void TMyButton::LoadFromIniFile(TIniFile* IniFile,AnsiString Section)
{
Left=IniFile->ReadInteger(Section,"Left",50);
Top=IniFile->ReadInteger(Section,"Top",50);
Height=IniFile->ReadInteger(Section,"Height",50);
Width=IniFile->ReadInteger(Section,"Width",50);
Signal=IniFile->ReadInteger(Section,"Signal",-1);
SignalField=IniFile->ReadInteger(Section,"SignalField",itOut);
//FInt=IniFile->ReadInteger(Section,"Int",5);
//FFactional=IniFile->ReadInteger(Section,"Factional",2);
Font->Size=IniFile->ReadInteger(Section,"FontSize",8);
Font->Color=IniFile->ReadInteger(Section,"FontColor",clBlack);
TFontStyles a;
if(IniFile->ReadBool(Section,"FontItalic",false))a<<fsItalic;
if(IniFile->ReadBool(Section,"FontBold",false))a<<fsBold;
if(IniFile->ReadBool(Section,"FontUnderLine",false))a<<fsUnderline;
if(IniFile->ReadBool(Section,"FontStrike",false))a<<fsStrikeOut;
Font->Style=a;
Font->Name=IniFile->ReadString(Section,"FontName","MS Sans Serf");
FNumber=IniFile->ReadInteger(Section,"Number",0);
FType=TObjectType(IniFile->ReadInteger(Section,"Type",0));
Action=IniFile->ReadInteger(Section,"Action",baNotDefine);
AssociateForm=IniFile->ReadString(Section,"AssociateForm","");
Caption=IniFile->ReadString(Section,"Caption","");
}
void TMyButton::Prepare(void)
{
OnClick=BitBtn1Click;
}
void TMyButton::Retur(void)
{
OnClick=0;
}
//----------------------End TMyByttom
//-----------------------------------------------------------------------------
//----------------------Класс многокадровых картинок
__fastcall TClip::TClip(TComponent* Owner)
            : TImage(Owner)
{
for(int i=0;i<maxframe;i++)
PresentFrame[i]=false;
//FAdam=1000;
//FChannel=1000;
Signal=-1;
SignalField=itOut;
FType=otClip;
LastHandle=CreateCompatibleDC(Canvas->Handle);
Canvas->Handle=LastHandle;
Bitm=new Graphics::TBitmap();
Bitm->LoadFromFile(MainForm->ProgramDir+"\\Images\\Label.bmp");
Picture->Bitmap=Bitm;
hdcFrame[0]=CreateCompatibleDC(Canvas->Handle);
SelectBitmap(hdcFrame[0],Bitm->Handle);
FImag[0]=MainForm->ProgramDir+"\\Images\\Label.bmp";

Width=Picture->Bitmap->Width;
Height=Picture->Bitmap->Height;

PresentFrame[0]=true;
FMaxFrame=0;
FCurrentFrame=0;
}
//----------------------------------------------------------------------------
__fastcall TClip::~TClip(/*TComponent* Owner*/)//: ~TImage(Owner)
{
Canvas->Handle=LastHandle;
DeleteDC(LastHandle);
for(int i=1;i<maxframe;i++)
 if(PresentFrame)DeleteDC(hdcFrame[i]);
delete Bitm;
}
//-------------------------
void TClip::SetFrame(int Index)
{
if(Index<=FMaxFrame)
FCurrentFrame=Index;
Canvas->Handle=hdcFrame[Index];
Invalidate();
}
//----------------------------------------------------------------------------
void __fastcall TClip::SetImag(int Index,AnsiString Value)
{
bool a;
if(Index<maxframe)
 {
 if(Value!="NULL")
  {
  FImag[Index]=Value;
  if(!PresentFrame[Index])
   {
   hdcFrame[Index]=CreateCompatibleDC(LastHandle);
   PresentFrame[Index]=true;
   if(MaxFrame<Index)MaxFrame=Index;
   }//*/
  /*else
   {
   Frame[Index]->ReleaseHandle();
   }*/
  Bitm->LoadFromFile(FImag[Index]);
  a=SelectBitmap(hdcFrame[Index],Bitm->Handle);
  Canvas->Handle=hdcFrame[0];
  Invalidate();
  }
 else//Value=="NULL"
  {
  if((PresentFrame[Index])&&(Index>0))
   {
   DeleteDC(hdcFrame[Index]);
   PresentFrame[Index]=false;
   if(PresentFrame[0])Canvas->Handle=hdcFrame[0];
   else Canvas->Handle=LastHandle;
   Invalidate();
   if(Index>=MaxFrame)//> для запаса главное =
    {
    for(int i=MaxFrame;i>=0;i--)
     if(PresentFrame[i])
      {
      MaxFrame=i;
      return;
      }
    }
   }
  else
   {
    if(PresentFrame[0])
    Canvas->Handle=hdcFrame[0];
    else Canvas->Handle=LastHandle;
    Invalidate();
   for(int i=MaxFrame;i>=0;i--)
    if(PresentFrame[i])
      {
      MaxFrame=i;
      return;
      }
   }
  }
 }
}
//--------------------
AnsiString __fastcall TClip::GetImag(int Index)
{
return FImag[Index];
}

void TClip::Prepare(void)
{
//TLocateOptions Flags;
//Flags.Clear();
//DataModule1->KanalsTable->Locate("Adam;Kanal",VarArrayOf(OPENARRAY(Variant,
//(Adam,Channel))),Flags);
if(PresentFrame[0])Bitm->LoadFromFile(FImag[0]);
Picture->Bitmap=Bitm;
Width=Picture->Bitmap->Width;
Height=Picture->Bitmap->Height;
for(int i=0;i<=MaxFrame;i++)
 {
 if(FImag[i]!=MainForm->ProgramDir+"\\Images\\"+"Label.bmp")
  {
  if(!PresentFrame[i])
   {
   hdcFrame[i]=CreateCompatibleDC(Canvas->Handle);//new Graphics::TBitmap();
   PresentFrame[i]=true;
   }
  Bitm->LoadFromFile(FImag[i]);
  SelectBitmap(hdcFrame[i],Bitm->Handle);
  }
 }
CurrentFrame=0;
Canvas->Handle=hdcFrame[0];
//Stretch=false;
Invalidate();
}

void TClip::Operate(void)
{
if(Signal==-1)return;
float InpSignal;//=MainForm->Signal[Adam][Channel];
if((Signal!=-1)&&(defPointerToSignals[Signal]))
 {
 switch(SignalField)
  {
  case itInp:InpSignal=defPointerToSignals[Signal]->InpValue;
  break;
  case itCalc:InpSignal=defPointerToSignals[Signal]->CalcValue;
  break;
  case itOut:InpSignal=defPointerToSignals[Signal]->OutValue;
  break;
  default:InpSignal=0;
  }
 }
else InpSignal=0;
if((InpSignal>=FSwitchMore)&&(InpSignal<FSwitchLess))
{
if(Visible==false) Visible=true;
Canvas->Handle=hdcFrame[CurrentFrame];
Invalidate();
CurrentFrame++;
CurrentFrame%=MaxFrame+1;
 /*if(CurrentFrame>MaxFrame)
  {
  CurrentFrame=0;
  }
Picture->Bitmap=Frame[CurrentFrame];
CurrentFrame++;*/
}
else  Visible=false;
//int a=0;
}//Fine of Operate for clip

void TClip::Retur(void)
{
if((FImag[0]==MainForm->ProgramDir+"\\Images\\Label.bmp")&&(MaxFrame==0))
Picture->LoadFromFile(MainForm->ProgramDir+"\\Images\\Label.bmp");
else
Picture->LoadFromFile(MainForm->ProgramDir+"\\Images\\Label.bmp");//FImag[0]);
Stretch=true;
}

void TClip::SaveToIniFile(TIniFile *IniFile,AnsiString Section)
{
IniFile->WriteInteger(Section,"Left",Left);
IniFile->WriteInteger(Section,"Top",Top);
IniFile->WriteInteger(Section,"Height",Height);
IniFile->WriteInteger(Section,"Width",Width);
IniFile->WriteInteger(Section,"Signal",Signal);
IniFile->WriteInteger(Section,"SignalField",SignalField);
IniFile->WriteInteger(Section,"SwitchLess",FSwitchLess);
IniFile->WriteInteger(Section,"SwitchMore",FSwitchMore);
for(int i=0;i<maxframe;i++)
if(PresentFrame[i])
IniFile->WriteString(Section,"Image"+IntToStr(i),ExtractFileName(FImag[i]));
IniFile->WriteInteger(Section,"Number",FNumber);
IniFile->WriteInteger(Section,"Type",int(FType));
IniFile->WriteInteger(Section,"MaxFrame",FMaxFrame);
}//Fine of SaveToFile for Images

void TClip::LoadFromIniFile(TIniFile *IniFile,AnsiString Section)
{
Left=IniFile->ReadInteger(Section,"Left",50);
Top=IniFile->ReadInteger(Section,"Top",50);
Height=IniFile->ReadInteger(Section,"Height",50);
Width=IniFile->ReadInteger(Section,"Width",50);
Signal=IniFile->ReadInteger(Section,"Signal",-1);
SignalField=IniFile->ReadInteger(Section,"SignalField",itOut);
FSwitchLess=IniFile->ReadInteger(Section,"SwitchLess",0);
FSwitchMore=IniFile->ReadInteger(Section,"SwitchMore",0);
FMaxFrame=IniFile->ReadInteger(Section,"MaxFrame",0);
for(int i=0;i<=MaxFrame;i++)
 {
 FImag[i]=MainForm->ProgramDir+"\\Images\\"+
 IniFile->ReadString(Section,"Image"+IntToStr(i),"Label.bmp");
 if(FImag[i]!=MainForm->ProgramDir+"\\Images\\"+"Label.bmp")
  {
  if(!PresentFrame[i])
   {
   hdcFrame[i]=CreateCompatibleDC(Canvas->Handle);//new Graphics::TBitmap();
   PresentFrame[i]=true;
   }
  Bitm->LoadFromFile(FImag[i]);
  SelectBitmap(hdcFrame[i],Bitm->Handle);
  }
 }
FNumber=IniFile->ReadInteger(Section,"Number",0);
FType=TObjectType(IniFile->ReadInteger(Section,"Type",3));

}
//---------------------------------------------------------------TSmooth
__fastcall TSmooth::TSmooth(int StartMax=10)
{
OnlyRecorded=false;
FPointer=-1;
FValue=0;
FArray=0;
FArraySize=abs(StartMax);
if(FArraySize>0)
 {
 FArray=new float[FArraySize];
 FPointer=0;
 for(int i=0;i<FArraySize;i++)
  FArray[i]=0;
 }
}//Fine of construct. for TSmooth

__fastcall TSmooth::~TSmooth()
{
if((FArray)&&(FArraySize>0)) delete []FArray;
}//Fine of destruct. for TSmooth

void __fastcall TSmooth::SetValue(float Val)
{
if((FArray)&&(FArraySize>0)&&(FPointer>=0))
 if(++FPointer<FArraySize)
  FArray[FPointer]=Val;
  else
   {
   FPointer=0;
   FArray[0]=Val;
   }
if(!OnlyRecorded)
 {
 for(int i=0;i<FArraySize;i++)
  FArray[i]=Val;
 FValue=Val;
 OnlyRecorded=true;
 return;
 }
float Summ=0;
for(short int i=0;i<ArraySize;i++)
 Summ+=FArray[i];
FValue=Summ/FArraySize;
}//Fine of SetValue

void __fastcall TSmooth::SetArraySize(int MaxSz)
{
if(MaxSz==ArraySize) return;
delete []FArray;
FArray=0;
FArraySize=abs(MaxSz);
FArray=new float[FArraySize];
for (int i=0;i<FArraySize;i++)
 FArray[i]=0;
FPointer=0;
OnlyRecorded=false;
}//Fine of SetMaxArray
//------------------------------------------------------------------------
//---------TDataConteiner----------------
//------------------------------------------------------------------------
/**/__fastcall TDataConteiner::TDataConteiner(int Numb)
{
Number=Numb;
Name="";EdIzm=="";SoundMin="";SoundMax="";SoundTop="";SoundBottom="";
Limits.Min=0;Limits.Max=100;Limits.MinAlarm=0;Limits.MaxAlarm=100;OffSet=0;Scale=1;
GroupIndex=-1;//ArraySize=-1;
//Smoothing=false;
FInpValue=0;FCalcValue=0;FOutValue=0;
FInpChanged=false;FCalcChanged=false;
FSignalNumber=-1;//,FTakedFrom=-1;
Type=stInp;
//FPassiveCalcSignal=false;
FMaxAlarm=false;
FMinAlarm=false;
FTopAlarm=false;
FBottomAlarm=false;
FCritSignal=false;
FOnSignal=true;
SaveData=false;
SaveAlarm=SaveData;
FSaveFrequency=60;
FAlarmFrequency=TDateTime(double(FSaveFrequency)/10);
FOnlyMessage=true;
AlarmSound="";
CritCounter=maxcritnumber;
for(int i=0;i<numbofsignal;i++)Action[Numb]=atNotDefine;
for(int i=0;i<numbofsignal;i++)
 {
 InpSignal[i]=0;
 InpType[i]=itNotDefine;
 //InpSubType[i]=sstNotDefine;
 }
}
void TDataConteiner::CheckSignal()
{
float Value=OutValue;
FCritSignal=false;
if(Value<=Limits.MinAlarm)
 {
 if(CheckToYes(SoundMin))
  {FMinAlarm=true;FCritSignal=true;AlarmSound="";FOnlyMessage=true;Message=Name+" ниже нормы";}
 else if(SoundMin!="")
  {
  FMinAlarm=true;FCritSignal=true;Message=Name+" ниже нормы";
  if(FOnSignal){AlarmSound=SoundMin;FOnlyMessage=false;}
  else {AlarmSound="";FOnlyMessage=true;}
  }
 else{FMinAlarm=false;FCritSignal=false;AlarmSound="";FOnlyMessage=true;Message="";}
 }
else
 {
 FMinAlarm=false;FCritSignal=false;AlarmSound="";FOnlyMessage=true;
 if(Value<=Limits.Min)
  {
  if(CheckToYes(SoundBottom))
   {FBottomAlarm=true;FCritSignal=true;AlarmSound="";FOnlyMessage=true;Message=Name+" отсутствует";}
  else if(SoundBottom!="")
   {
   FBottomAlarm=true;FCritSignal=true;Message=Name+" отсутствует";
   if(FOnSignal){AlarmSound=SoundBottom;FOnlyMessage=false;}
   else {AlarmSound="";FOnlyMessage=true;}
   }
  else{FBottomAlarm=false;FCritSignal=false;AlarmSound="";FOnlyMessage=true;Message="";}
  }
 else {FBottomAlarm=false;FCritSignal=false;AlarmSound="";FOnlyMessage=true;Message="";}
 }

if(Value>=Limits.MaxAlarm)
 {
 if(CheckToYes(SoundMax))
  {FMaxAlarm=true;FCritSignal=true;AlarmSound="";FOnlyMessage=true;Message=Name+" выше нормы";}
 else if(SoundMax!="")
  {
  FMaxAlarm=true;FCritSignal=true;Message=Name+" выше нормы";
  if(FOnSignal){AlarmSound=SoundMax;FOnlyMessage=false;}
  else {AlarmSound="";FOnlyMessage=true;}
  }
 else{FMinAlarm=false;FCritSignal=false;AlarmSound="";FOnlyMessage=true;Message="";}
 }
else
 {
 FMaxAlarm=false;FCritSignal=false;AlarmSound="";FOnlyMessage=true;
 if(Value>=Limits.Max)
  {
  if(CheckToYes(SoundTop))
   {FTopAlarm=true;FCritSignal=true;AlarmSound="";FOnlyMessage=true;Message=Name+" зашкалил";}
  else if(SoundTop!="")
   {
   if(FOnSignal){FTopAlarm=true;FCritSignal=true;Message=Name+" зашкалил";}
   else{AlarmSound=SoundTop;FOnlyMessage=false;}
   }
  else{FTopAlarm=false;FCritSignal=false;AlarmSound="";FOnlyMessage=true;Message="";}
  }
 else {FTopAlarm=false;FCritSignal=false;AlarmSound="";FOnlyMessage=true;Message="";}
 }
if(FCritSignal)
 {
 if((CritCounter>0)&&(CritCounter<=maxcritnumber))
  {
  CritCounter-=1;
  FTopAlarm=false;FBottomAlarm=false;FMaxAlarm=false;FMinAlarm=false;
  FCritSignal=false;AlarmSound="";FOnlyMessage=true;Message="";
  }
 else if(CritCounter>maxcritnumber)CritCounter=maxcritnumber;
 else CritCounter=0;
 }
else
 {
 CritCounter=maxcritnumber;
 FOnSignal=true;
 }
}

inline bool TDataConteiner::CheckToYes(const AnsiString& Str)
{
if((Str=="Yes")||(Str=="yes")||(Str=="YES"))return true;
return false;
}

void TDataConteiner::SendToDevice()
{
if((InputDevice.Port!=-1)&&(InputDevice.Device!=-1)&&(InputDevice.Channel!=-1))
DataModule1->ExternalDevices[InputDevice.Port][InputDevice.Device][InputDevice.Channel]=Number;
}

float TDataConteiner::GetSignal(const int& Numb)//,const TSignalType& Type)
{
//if(InpType=stFloat
//if(FPassiveCalcSignal)
switch(InpType[Numb])
 {
 case itFloat:
 return InpSignal[Numb];
 //break;
 case itInp:
 return DataModule1->Signal[(int)InpSignal[Numb]]->InpValue;
 //break;
 case itCalc:
 return DataModule1->Signal[(int)InpSignal[Numb]]->CalcValue;
 //break;
 case itOut:
 return DataModule1->Signal[(int)InpSignal[Numb]]->OutValue;
 //break;
 }
/*else
 switch(InpType[Numb])
 {
 case itFloat:
 return InpSignal[Numb];
 //break;
 case itInp:
 return DataModule1->Signal[(int)InpSignal[Numb]]->InpValue;
 //break;
 case itCalc:
 return DataModule1->Signal[(int)InpSignal[Numb]]->CalcValue;
 //break;
 case itOut:
 return DataModule1->Signal[(int)InpSignal[Numb]]->OutValue;
 //break;
 }*/
}
void TDataConteiner::CalculateCalc()
{
 /*{
 bool Flag=0;
 for(int i =0;i<numbofsignal-1;i++)if(Action[i]!=numbofsignal-1)Flag=1;
 if(Flag=0)return;
 } */

float Value;
switch(Type)
 {
 case stInp:
 case stOut:
 if(!FInpChanged)return;
  Value=FInpValue*Scale+OffSet;
 break;
 case stCalc:
  {
  if(InpType[0]==itIntPtoc)
   {
   float Values[numbofsignal-1];
   for(int i=0;i<numbofsignal-1;i++)
    {                                  //DataModule1->Signal[6]->OutValue
    //if(defPointerToSignals[int(InpSignal[i+1])])
    Values[i]=GetSignal(i+1);
    //else Values[i]=0;
    }
   Value=defGetIntProc(InpSignal[0],Values[0],Values[1]);
   //if(InpSignal[0]==1)Value=defGetIntProc(1,Values[0],Values[1]);
   //if(InpSignal[0]==2)Value=defGetIntProc(2,Values[0],Values[1]);
   Value=Value*Scale+OffSet;
   break;
   }
  Value=GetSignal(0);
  for(int i=0;((i<numbofsignal-1)&&(Action[i]!=atNotDefine));i++)
   {
   switch(Action[i])
    {
    case atAdd:Value+=GetSignal(i+1);
    break;
    case atSub:Value-=GetSignal(i+1);
    break;
    case atMul:Value*=GetSignal(i+1);
    break;
    case atDiv:
     {
     float  Val2=GetSignal(i+1);
     if(!Val2)Val2=1e-15;
     Value/=Val2;
     }
    break;
    case atAnd:Value=Value&&GetSignal(i+1);
    break;
    case atOr:Value=Value||GetSignal(i+1);
    break;
    case atAndNot:Value=!(Value&&GetSignal(i+1));
    break;
    case atOrNot:Value=!(Value||GetSignal(i+1));
    break;
    }
   }//end for
  Value=Value*Scale+OffSet;
  }
 break;
 }                                  ///Number
if(Smoothing)
   {
   float dVal=(Value)?(Value-SmoothObject.Value)/Value:1;
   if(fabs(dVal)>0.005)
   SetValue(Value);
   FCalcValue=SmoothObject.Value;
   }
else FCalcValue=Value;
FCalcChanged=true;
FInpChanged=false;
}

void TDataConteiner::CalculateOut()
{
if(FCalcChanged)
 {
 FCalcChanged=false;
 FOutValue=CalcValue;
 }
}

float __fastcall TDataConteiner::GetCalcValue(void)
{
switch(Type)
 {
 case stInp:
  if(FInpChanged)CalculateCalc();
  return FCalcValue;
 //break;
 case stCalc:
  CalculateCalc();
  return FCalcValue;
 //break;
 case stOut:

 break;
 }
}


float __fastcall TDataConteiner::GetOutValue(void)
{
switch(Type)
 {                       //this->Number
 case stInp:
  if(FInpChanged)CalculateCalc();
  if(FCalcChanged)CalculateOut();
  return FOutValue;
 //break;
 case stCalc:
  CalculateCalc();
  CalculateOut();
  return FOutValue;
 //break;
 case stOut:
 return  0;
 //break;
 }
return 0;
}
/*TSmoothObject&*/ TDataConteiner::TSmoothObject::operator=(const TSmoothObject& Src)
 {
  if(this==&Src)return 0;//*this;
  if((Src.Smoothing)&&(Src.ArraySize)&&(Src.Array))
   {
   delete []Array;
   ArraySize=Src.ArraySize;
   Array=new float[ArraySize];
   for(int i=0;i<ArraySize;i++) Array[i]=Src.Array[i];
   CurrentElement=Src.CurrentElement;
   }
  Value=Src.Value;
  OnlyRecorded=Src.OnlyRecorded;
  //float* Array;
 return 0;// *this;
 }
//---------------------------------------------------------------------------
void __fastcall TDataConteiner::SetArraySize(unsigned int Val)
 {
 float* OldPointer=SmoothObject.Array;
 if((SmoothObject.Smoothing)&&(Val))
  {
  SmoothObject.Array=new float[Val];
  if(OldPointer)
   {
   unsigned int MinSize=SmoothObject.ArraySize<Val?SmoothObject.ArraySize:Val;
   //unsigned int MaxSize=ArraySize>Val?ArraySize:Val;
   if(MinSize>0)
    for(int i=0;i<MinSize;i++)
     SmoothObject.Array[i]=OldPointer[i];
   if(Val>SmoothObject.ArraySize)
    for(int i=SmoothObject.ArraySize;i<Val;i++)SmoothObject.Array[i]=OldPointer[SmoothObject.ArraySize-1];
   }
  }
 delete []OldPointer;
 SmoothObject.ArraySize=Val;
 }
//---------------------------------------------------------------------------
void __fastcall TDataConteiner::SetValue(float Val)
 {
if(!SmoothObject.Smoothing) {SmoothObject.Value=Val;return;}
if((SmoothObject.Array)&&(SmoothObject.ArraySize>0)/*&&(SmoothObject.CurrentElement>=0)*/)
 {
 if(++SmoothObject.CurrentElement<SmoothObject.ArraySize)        //Number
  SmoothObject.Array[SmoothObject.CurrentElement]=Val;
 else
  {
  SmoothObject.CurrentElement=0;
  SmoothObject.Array[0]=Val;
  }
 if(!SmoothObject.OnlyRecorded)
  {
  for(int i=0;i<SmoothObject.ArraySize;i++)
  SmoothObject.Array[i]=Val;
  SmoothObject.Value=Val;
  SmoothObject.OnlyRecorded=true;
  return;
  }
 float Summ=0;
 for(short int i=0;i<SmoothObject.ArraySize;i++)
 Summ+=SmoothObject.Array[i];
 SmoothObject.Value=Summ/SmoothObject.ArraySize;
 }
}

void __fastcall TDataConteiner::SetSmoothing(bool Val)
 {
 SmoothObject.Smoothing=Val;
 //ArraySize=ArraySize;
 //if((SmoothObject.ArraySize)&&(SmoothObject.Smoothing))
  //if(!SmoothObject.Array)SmoothObject.Array=new float[SmoothObject.ArraySize];
 //Smoothing=t
 }
bool TDataConteiner::SaveOrNo(const TDateTime& CurTime,unsigned short StdAl)
{
float Diff;
switch(StdAl)
 {
 case 0://StandartDatabase
  if(CurTime<LastSaveTime+SaveFrequency)return false;
  if(!SaveData)return false;
  Diff=(float)MainForm->DataDiff/100;
  if((LastSaved*(1-Diff)>OutValue)|(LastSaved*(1+Diff)<OutValue)|
  (CurTime-LastSaveTime>=(TDateTime)(0.5/24)))return true;
  else return false;
 break;
 case 1://AlarmDatabase
  if(CurTime<LastAlarmTime+SaveFrequency)return false;
  if(!SaveAlarm)return false;
  Diff=(float)MainForm->AlarmDiff/100;
  if((LastAlarm*(1-Diff)>OutValue)|(LastAlarm*(1+Diff)<OutValue)|
  (CurTime-LastAlarmTime>(TDateTime)(0.2/24)))return true;
  else return false;
 }
return false; 
}
//*/
//----------------------------------------------------------------------------
//----------TArray---------------
//----------------------------------------------------------------------------
/*template<class T>
TArray::SetArraySize(unsigned long Val)
 {
 T* OldPointer=Array;
  Array=new T[Val];
  if(OldPointer)
   {
   unsigned long MinSize=FArraySize<Val?FArraySize:Val;
   if(MinSize>0)
    for(unsigned long i=0;i<MinSize;i++)
     Array[i]=OldPointer[i];
   }
  }
 delete []OldPointer;
 }*/
