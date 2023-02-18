//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl\Printers.hpp>
#pragma hdrstop

#include "Graph.h"
#include "DataUnit.h"
#include "Connect.h"
#include "SelectGr.h"
#include "Constant.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGraphForm *GraphForm;
//---------------------------------------------------------------------------
__fastcall TGraphForm::TGraphForm(TComponent* Owner)
        : TForm(Owner)
{
SettingsChanged=false;
//for(int i=0;i<maxadam*maxchannel;i++)Graphics[i]=-1;
PaintBox->Height=Height-Panel1->Height-50;
//TDateTime Dat;
//TimeScale=20000;
MinLabel->Caption=IntToStr(TrackBar->Min);
//TrackBar->Min=300;
MaxLabel->Caption=IntToStr(TrackBar->Max);
//TrackBar->Max=100000;
//TrackBar->Position=TimeScale;
PaintBox->Width=TrackBar->Position;
//Dat=Date();
//UpDown1->Position=double(Dat);
//UpDown2->Position=double(Dat);
MaskEdit->Text=Date();
MaskEdit1->Text=Date();
SelectMaxDate=MaskEdit->Text;
SelectMinDate=MaskEdit1->Text;
//AnsiString a="";
DataModule1->StatistTable->Filtered=false;
DateFilter="(Date>='"+SelectMinDate.DateString()+
"')and(Date<='"+SelectMaxDate.DateString()+"')";

//DataModule1->StatistTable->Filter=DateFilter;
//DataModule1->StatistTable->Filtered=true;
StepX=MainForm->StepX;StepY=MainForm->StepY;
DPI=MainForm->DPI;
PListWidth=MainForm->ListWidth;
PListHeight=MainForm->ListHeight;
PListLeft=MainForm->ListLeft;
PListTop=MainForm->ListTop;
AxisWidth=MainForm->AxisWidth;
GirdWidth=MainForm->GirdWidth;
GraphWidth=MainForm->GraphWidth;
AllBlack=MainForm->AllBlack;
for(int i=0;i<maxgraph;i++)
{
GraphPoint[i].Array=0;
GraphPoint[i].Size=0;
}
for(int i=0;i<maxgraph;i++)PrintedAxis[i]=MainForm->PrintedAxis[i];
/*for(int i=0;i<maxgraph;i++)
for(int j=0;j<maxpoint;j++)
 {

 GraphPoint[i][j]=0;
 TimePoint[i][j]=0;
 }*/
//GraphPoint=new TDifArray<short int>[maxgraph];//for(int i=0;i<maxgraph;i++)
PanelVis=false;
ViewScale=0;
 }
//---------------------------------------------------------------------------
void TGraphForm::InitialPoints(short TabNumb=-1)
{
if(TabNumb+1>TabControl->Tabs->Count)return;
if(TabNumb<0)TabNumb=TabControl->TabIndex;
//----Подстановка в StatistTable стандартной бд или аварийной и остановка таймеров
/*bool fSaveData=MainForm->DataBaseTimer->Enabled;
bool fSaveAlarm=MainForm->AlarmTimer->Enabled;
 MainForm->DataBaseTimer->Enabled=false;
 MainForm->AlarmTimer->Enabled=false;*/
MainForm->Paused=true;
TTable* Table;
if(StandartSButton->Down)
 {
 Table=DataModule1->StatistTable;
 }
else
 {//Select Alarm
 Table=DataModule1->AlarmTable;
 }
//----}
int w=PaintBox->Width-10;
int h=PaintBox->Height-10;
for(int i=0;i<maxgraph;i++)
 {
 if(GraphPoint[i].Array){delete []GraphPoint[i].Array;GraphPoint[i].Array=0;}
 //delete []TimePoint[i].Array;
 }
for(int i=0;i<maxgraph;i++)//Start for each graph
 if((Graphics[TabNumb][i].Signal!=-1)&&(defPointerToSignals[Graphics[TabNumb][i].Signal]))
 {
 Graphics[TabNumb][i].Max=defPointerToSignals[Graphics[TabNumb][i].Signal]->Limits.Max;
 int Counter=0;
 if(ViewScale==-1)
  {
  ViewScale=i;
  PaintBox1->Invalidate();
  }
 GraphPoint[i].Array=new short[w+3];
 GraphPoint[i].Size=w;
 GraphPoint[i].Max=h;
 for(unsigned int j=0;j<GraphPoint[i].Size;j++)
  GraphPoint[i].Array[j]=0;
 if(!GraphPoint[i].Max)GraphPoint[i].Max=1;
 //TimePoint[i].Array=new short[w];
 //GraphPoint[i].ArraySize=w;
 if((defPointerToSignals[Graphics[TabNumb][i].Signal]->Type==stInp)||(defPointerToSignals[Graphics[TabNumb][i].Signal]->Type==stOut)||
 ((defPointerToSignals[Graphics[TabNumb][i].Signal]->Type==stCalc)&&(defPointerToSignals[Graphics[TabNumb][i].Signal]->SaveData)))
   {
   FillArray(&(GraphPoint[i]),Table,Graphics[TabNumb][i].Signal);
   }                //DataModule1->Signal[Graphics[i]]->InpSignal[0]
 else if((defPointerToSignals[Graphics[TabNumb][i].Signal]->Type==stCalc)&&
  (defPointerToSignals[Graphics[TabNumb][i].Signal]->InpType[0]!=itIntPtoc))
   {
   TFloatArrayPointer PromArray[numbofsignal];
   float Maxes[numbofsignal];
   TInpType InpType[numbofsignal];
   float InpSignal[numbofsignal];
   TActionType Action[numbofsignal-1];
   for(unsigned short j=0;j<numbofsignal;j++)
    {
    InpSignal[j]=defPointerToSignals[Graphics[TabNumb][i].Signal]->InpSignal[j];
    InpType[j]=defPointerToSignals[Graphics[TabNumb][i].Signal]->InpType[j];
    if(j<numbofsignal-1)Action[j]=defPointerToSignals[Graphics[TabNumb][i].Signal]->Action[j];
    if((InpType[j]!=itNotDefine)&&(InpType[j]!=itFloat))
     {
     Maxes[j]=defPointerToSignals[(unsigned short)(defPointerToSignals[Graphics[TabNumb][i].Signal]->InpSignal[j])]->Limits.Max;
     if(PromArray[j].Array){delete []PromArray[j].Array;PromArray[j].Array=0;}
     PromArray[j].Array=new float[w+3];
     PromArray[j].Size=w;
     PromArray[j].Max=defPointerToSignals[Graphics[TabNumb][i].Signal]->Limits.Max;
     if(!PromArray[j].Max)PromArray[j].Max=1;
     FillArray(&(PromArray[j]),Table,(unsigned short)(defPointerToSignals[Graphics[TabNumb][i].Signal]
     ->InpSignal[j]));
     }
    }
   //-----
   if(InpType[0]==itNotDefine)return;
   int PrevOut=0;
   float LimitOut=Graphics[TabNumb][i].Max/defPointerToSignals[Graphics[TabNumb][i].Signal]->Scale-defPointerToSignals[Graphics[TabNumb][i].Signal]->OffSet;
   for(unsigned int j=0;j<GraphPoint[i].Size;j++)
    {
    float OutVal;
    if(InpType[0]==itFloat)OutVal=InpSignal[j];
    else OutVal=PromArray[0].Array[j];
    for(unsigned int k=0;((k<numbofsignal-1)&&(Action[k]!=atNotDefine));k++)     //DataModule1->Signal
     {
     if (InpType[k+1]!=itFloat)
      {
      Act(OutVal,PromArray[k+1].Array[j],Action[k]);
      }
     else Act(OutVal,InpSignal[k+1],Action[k]);
     }
    if(OutVal>LimitOut) OutVal=PrevOut;
    else PrevOut=OutVal;
    GraphPoint[i].Array[j]=(OutVal*defPointerToSignals[Graphics[TabNumb][i].Signal]->Scale+
    defPointerToSignals[Graphics[TabNumb][i].Signal]->OffSet)*GraphPoint[i].Max/Graphics[TabNumb][i].Max;
    }
   //---------------
   }
  else if((defPointerToSignals[Graphics[TabNumb][i].Signal]->Type==stCalc)&&
  (defPointerToSignals[Graphics[TabNumb][i].Signal]->InpType[0]==itIntPtoc))
   {
   TFloatArrayPointer PromArray[numbofsignal-1];
   float Maxes[numbofsignal-1];
   TInpType InpType[numbofsignal-1];
   float InpSignal[numbofsignal-1];
   //TActionType Action[numbofsignal-1];
   for(unsigned short j=0;j<numbofsignal-1;j++)
    {
    InpSignal[j]=defPointerToSignals[Graphics[TabNumb][i].Signal]->InpSignal[j+1];
    InpType[j]=defPointerToSignals[Graphics[TabNumb][i].Signal]->InpType[j+1];
    //if(j<numbofsignal-1)Action[j]=defPointerToSignals[Graphics[i]]->Action[j];
    if((InpType[j]!=itNotDefine)&&(InpType[j]!=itFloat))
     {
     Maxes[j]=defPointerToSignals[(unsigned short)(defPointerToSignals[Graphics[TabNumb][i].Signal]->InpSignal[j+1])]->Limits.Max;
     if(PromArray[j].Array){delete []PromArray[j].Array;PromArray[j].Array=0;}
     PromArray[j].Array=new float[w+3];
     PromArray[j].Size=w;
     PromArray[j].Max=defPointerToSignals[Graphics[TabNumb][i].Signal]->Limits.Max;
     if(!PromArray[j].Max)PromArray[j].Max=1;
     FillArray(&(PromArray[j]),Table,(unsigned short)(defPointerToSignals[Graphics[TabNumb][i].Signal]->InpSignal[j+1]));
     }
    }
   //-----
   if(InpType[0]==itNotDefine)return;
   for(unsigned int j=0;j<GraphPoint[i].Size;j++)
    {
    float Param[numbofsignal-1];
    for(unsigned  int k=0;k<numbofsignal-1;k++)
     {
     if(InpType[k]==itFloat) Param[k]=InpSignal[j];
     else if((InpType[k]==itInp)||(InpType[k]==itCalc)||(InpType[k]==itOut))
      Param[k]=PromArray[0].Array[j];
     else  Param[k]=0;
     //if(Param[k]!=0)int l=0;
     }
    float OutVal=defGetIntProc((unsigned  short)(defPointerToSignals[Graphics[TabNumb][i].Signal]->InpSignal[0]),Param[0],Param[1]);
    /*if(InpType[0]==itFloat)OutVal=InpSignal[j];
    else OutVal=PromArray[0].Array[j];
    for(unsigned int k=0;((k<numbofsignal-1)&&(Action[k]!=atNotDefine));k++)     //DataModule1->Signal
     {
     if (InpType[k+1]!=itFloat)
      {
      Act(OutVal,PromArray[k+1].Array[j],Action[k]);
      }
     else Act(OutVal,InpSignal[k+1],Action[k]);
     }*/
    /*if(defPointerToSignals[Graphics[TabNumb][i].Signal]->Limits.Min>=0)
     {
     GraphPoint[i].Array[j]=(OutVal*defPointerToSignals[Graphics[TabNumb][i].Signal]->Scale+
     defPointerToSignals[Graphics[TabNumb][i].Signal]->OffSet)*GraphPoint[i].Max/Graphics[TabNumb][i].Max;
     }
    else
     {
     float RealMax;
      {
      float Max1=fabs(defPointerToSignals[Graphics[TabNumb][i].Signal]->Limits.Min),
            Max2=fabs(defPointerToSignals[Graphics[TabNumb][i].Signal]->Limits.Max);
      RealMax=(Max1>Max2)?Max1:Max2;
      }
     GraphPoint[i].Array[j]=(OutVal*defPointerToSignals[Graphics[TabNumb][i].Signal]->Scale+
     defPointerToSignals[Graphics[TabNumb][i].Signal]->OffSet)*GraphPoint[i].Max/Graphics[TabNumb][i].Max;
     }*/
    GraphPoint[i].Array[j]=(OutVal*defPointerToSignals[Graphics[TabNumb][i].Signal]->Scale+
    defPointerToSignals[Graphics[TabNumb][i].Signal]->OffSet)*GraphPoint[i].Max/Graphics[TabNumb][i].Max;
    }
   }//end if InpProc*/
 //Коррекция для отрицательных  сигналов
   if(defPointerToSignals[Graphics[TabNumb][i].Signal]->Limits.Min<0)
    {
    float Min1=defPointerToSignals[Graphics[TabNumb][i].Signal]->Limits.Min,
    Max1=defPointerToSignals[Graphics[TabNumb][i].Signal]->Limits.Max;
    Max1=(Max1>-Min1)?Max1:-Min1;
    float Delta=2*Max1;
    for(unsigned int j=0;j<GraphPoint[i].Size;j++)
     GraphPoint[i].Array[j]=float(GraphPoint[i].Array[j])*defPointerToSignals[Graphics[TabNumb][i].Signal]->Limits.Max/Delta+
     GraphPoint[i].Max/2;
    }
 }//end (for i,if)
DataModule1->StatistTable->Filtered=false;
DataModule1->StatistTable->Last();
MainForm->Paused=false;
//----}
}
//---------------------------------------------------------------------------
inline void TGraphForm::Act(float& Value1,float& Value2,TActionType& Action)
{
switch(Action)
    {
    case atAdd:Value1+=Value2;
    break;
    case atSub:Value1-=Value2;
    break;
    case atMul:Value1*=Value2;
    break;
    case atDiv:
     {
     float  Val2=Value2;
     if(!Val2)Val2=1e-30;
     Value1/=Val2;
     }
    break;
    case atAnd:Value1=Value1&&Value2;
    break;
    case atOr:Value1=Value1||Value2;
    break;
    case atAndNot:Value1=!(Value1&&Value2);
    break;
    case atOrNot:Value1=!(Value1||Value2);
    break;
    }
}
//---------------------------------------------------------------------------
inline bool TGraphForm::CheckAndFilter(TTable *Table,unsigned short Parametr)
{
if(!Table)return false;
AnsiString ParamSort="(Numb='"+IntToStr(Parametr)+"')";
Table->Active=false;
Table->Filter=ParamSort+"and"+DateFilter;
Table->IndexName="";
Table->Active=true;
if(!Table->Filtered)Table->Filtered=true;
if(Table->RecordCount<=0)return false;
Table->FindFirst();
if(Table->Eof)return false;
return true;
}
//---------------------------------------------------------------------------
void TGraphForm::FillArray(TArrayPointer* Array,TTable *Table,unsigned short Parametr)
{
{
 bool b=CheckAndFilter(Table,Parametr);
 if(!b)
 {
 for(unsigned int i=0;i<Array->Size;i++)Array->Array[i]=0;
 return;
 }
}
if((!Array->Array)||(!Array->Size))return;
float Max=defPointerToSignals[Parametr]->Limits.Max;
if(!Max)Max=1;                                       //DataModule1->Signal
if(!Array->Max)Array->Max=1;
unsigned short Ho,Mi,Sec;
bool a,First=true;
float OldValue=0;
TDateTime OldTime=Table->FieldByName("Date")->AsDateTime;
int OldIndex=0;
do
  {
  TDateTime date1=Table->FieldByName("Date")->AsDateTime;
  Ho=Table->FieldByName("Hours")->AsInteger;
  Mi=Table->FieldByName("Minuts")->AsInteger;
  Sec=Table->FieldByName("Seconds")->AsInteger;
  TDateTime time1(Ho,Mi,Sec,0);
  TDateTime CurDB=date1+time1;
  double Ind=double(Array->Size)*double(CurDB-SelectMinDate)/(double(SelectMaxDate-SelectMinDate+1));
  unsigned int Index=Ind;
  float Val1=Table->FieldByName("Value")->AsFloat;
  int Value=(Val1*Array->Max)/Max;
  //if(First)for(unsigned int i=0;i<Index;i++)Array->Array[i]=;
  Array->Array[Index]=Value;//h-10-Table->FieldByName("Value")->AsFloat*(h-10)/Max[i];
  if((24*(CurDB-OldTime)>=0.8)||(First))
   {
   for(unsigned int i=OldIndex;i<Index;i++)Array->Array[i]=0;
   First=false;
   }
  else
   for(unsigned int i=OldIndex;i<Index;i++)
   Array->Array[i]=OldValue+(Value-OldValue)*(i-OldIndex)/(Index-OldIndex);
  a=Table->FindNext();
  if(!a)for(unsigned int i=Index+1;i<Array->Size;i++)Array->Array[i]=0;
  OldValue=Value;
  OldTime=CurDB;
  OldIndex=Index;
  }
 while(a);
}
//---------------------------------------------------------------------------
void TGraphForm::FillArray(TFloatArrayPointer* Array,TTable *Table,unsigned short Parametr)
{
{
bool b=CheckAndFilter(Table,Parametr);
 if(!b)
 {
 for(unsigned int i=0;i<Array->Size;i++)Array->Array[i]=0;
 return;
 }
}
if((!Array->Array)||(!Array->Size))return;
unsigned short Ho,Mi,Sec;
bool a,First=true;
float OldValue=0;
TDateTime OldTime=Table->FieldByName("Date")->AsDateTime;
int OldIndex=0;
do
  {
  TDateTime date1=Table->FieldByName("Date")->AsDateTime;
  Ho=Table->FieldByName("Hours")->AsInteger;
  Mi=Table->FieldByName("Minuts")->AsInteger;
  Sec=Table->FieldByName("Seconds")->AsInteger;
  TDateTime time1(Ho,Mi,Sec,0);
  TDateTime CurDB=date1+time1;
  double Ind=double(Array->Size)*double(CurDB-SelectMinDate)/(double(SelectMaxDate-SelectMinDate+1));
  unsigned int Index=Ind;
  float Value/*1*/=Table->FieldByName("Value")->AsFloat;
  //int Value=(Val1*Array->Max)/Max;
  Array->Array[Index]=Value;//h-10-Table->FieldByName("Value")->AsFloat*(h-10)/Max[i];
  if((24*(CurDB-OldTime)>=0.8)||(First))
   {
   for(unsigned int i=OldIndex;i<Index;i++)Array->Array[i]=0;
   First=false;
   }
  else
   for(unsigned int i=OldIndex;i<Index;i++)
   Array->Array[i]=OldValue+(Value-OldValue)*(float)((float)(i-OldIndex)/(float)(Index-OldIndex));
  a=Table->FindNext();
  if(!a)for(unsigned int i=Index+1;i<Array->Size;i++)Array->Array[i]=0;
  OldValue=Value;
  OldTime=CurDB;
  OldIndex=Index;
  }
 while(a);
}
//---------------------------------------------------------------------------
void __fastcall TGraphForm::PaintBoxPaint(TObject *Sender)
{
short TabNumb=TabControl->TabIndex;
int w=PaintBox->Width;
int h=PaintBox->Height;
PaintBox->Canvas->Pen->Color=clBlack;
PaintBox->Canvas->Pen->Width=1;
/*TrackBar->Max=32000/(EndDB-StartDB);
//AnsiString a=SelectDate.DateString()*/
TDateTime dTime=double(StepX)/(w-10)*double(SelectMaxDate-SelectMinDate+1);
for(int i=10+StepX;i<=w;i+=StepX)
 {
 PaintBox->Canvas->MoveTo(i,0);
 PaintBox->Canvas->LineTo(i,h);
 }
for(int i=1;i<w/StepX;i+=2)
 {
 //Out Time Scales
 PaintBox->Canvas->TextOut(i*StepX-9,h-39,TDateTime(double(dTime)*i+
 double(SelectMinDate)).DateString());
 PaintBox->Canvas->TextOut(i*StepX-9,h-25,TDateTime(double(dTime)*i+
 double(SelectMinDate)).TimeString());
 }
for(int i=h-10-StepY;i>=0;i-=StepY)
 {
 PaintBox->Canvas->MoveTo(0,i);
 PaintBox->Canvas->LineTo(w,i);
 }
TDateTime CurDB,date1;
for(int i=0;i<maxgraph/*(maxadam*maxchannel)*/;i++)
 if((Graphics[TabNumb][i].Signal!=-1)&&(GraphPoint[i].Array))
  {
  PaintBox->Canvas->Pen->Color=Graphics[TabNumb][i].Color;
  PaintBox->Canvas->Pen->Width=2;
  for(unsigned int j=1;j<GraphPoint[i].Size;j++)
   {
   int Current=GraphPoint[i].Array[j],Prev=GraphPoint[i].Array[j-1];
   if(Current&&Prev)
    {
    PaintBox->Canvas->MoveTo(j+10-1,h-10-Prev);
    PaintBox->Canvas->LineTo(j+10,h-10-Current);
    }
   else
    {
    PaintBox->Canvas->Pixels[j+10][h-10-Current]=Graphics[TabNumb][i].Color;
    }
   }
  PaintBox->Canvas->Pen->Width=1; 
  /*int x1=10,y1=h-10;
  x1=TimePoint[i][0];
  y1=GraphPoint[i][0];
  for(int j=0;j<MaxPoint[i];j++)
   {
   int x=TimePoint[i][j];//10+double(CurDB-SelectMinDate)*(w-10)/(SelectMaxDate-SelectMinDate+1);
   int y=GraphPoint[i][j];//h-10-DataModule1->StatistTable->FieldByName("Value")->AsFloat*h/Max[i];
   if(((x-x1)>=0)&((x-x1)<(w*1/24)))//1- max time in hour then line paint
    {
    PaintBox->Canvas->MoveTo(x1,y1);
    PaintBox->Canvas->LineTo(x,y);//=GraphColor[i];
    }
   else
    {
    PaintBox->Canvas->Pixels[x][y]=GraphColor[i];
    PaintBox->Canvas->Pixels[x1][y1]=GraphColor[i];
    }
   x1=x;y1=y;
   }
  */
  PaintBox->Canvas->Font->Size=5;
  PaintBox->Canvas->Font->Color=Graphics[TabNumb][i].Color;
  }
PaintBox->Canvas->Pen->Color=clBlack;
for(int i=10+StepX;i<=w;i+=StepX)
 {
 PaintBox->Canvas->MoveTo(i,0);
 PaintBox->Canvas->LineTo(i,h);
 }
PaintBox->Canvas->Pen->Color=clBlack;
PaintBox->Canvas->Pen->Width=2;
PaintBox->Canvas->MoveTo(10,0);
PaintBox->Canvas->LineTo(10,h);
PaintBox->Canvas->MoveTo(0,h-10);
PaintBox->Canvas->LineTo(w,h-10);
TypePanel->Left=ScrollBox1->Width-TypePanel->Width-25;
}
//---------------------------------------------------------------------------
void __fastcall TGraphForm::FormCreate(TObject *Sender)
{
//DeleteFile(ProgramDir+"\\Setgraph.ini");
  TIniFile *IniFile;
  IniFile=new TIniFile(MainForm->ProgramDir+"\\Setgraph.ini");
ReadFromIniFile(IniFile);
/*for(int i=0;i<maxgraphgroup;i++)
for(int j=0;j<maxgraph;j++)
 {
 Graphics[i][j]
 Graphics[i]=IniFile->ReadInteger("Graph"+IntToStr(i),"Param",-1);
 if((Graphics[i]!=-1)&&(defPointerToSignals[Graphics[i]]))
 {
 //PrintAxis[i]=IniFile->ReadInteger
 GraphColor[i]=IniFile->ReadInteger("Graph"+IntToStr(i),"Color",0);
 Max[i]=defPointerToSignals[Graphics[i]]->Limits.Max;//StrToFloat(IniFile->ReadString("Graph"+IntToStr(i),"Max",1));
 }
 else Graphics[i]=-1;
 }
delete IniFile;
InitialPoints();*/
}
//---------------------------------------------------------------------------
void TGraphForm::TGraphicInfo::ReadFile(TIniFile* IniFile,AnsiString Section,unsigned short Numb)
{
Max=IniFile->ReadInteger(Section,"Max"+IntToStr(Numb),0);
Color=IniFile->ReadInteger(Section,"Color"+IntToStr(Numb),0);
Signal=IniFile->ReadInteger(Section,"Signal"+IntToStr(Numb),-1);
}
//---------------------------------------------------------------------------
void TGraphForm::TGraphicInfo::WriteFile(TIniFile* IniFile,AnsiString Section,unsigned short Numb)
{
IniFile->WriteInteger(Section,"Max"+IntToStr(Numb),Max);
IniFile->WriteInteger(Section,"Color"+IntToStr(Numb),Color);
IniFile->WriteInteger(Section,"Signal"+IntToStr(Numb),Signal);
}
//---------------------------------------------------------------------------
bool TGraphForm::TGraphicInfo::PresentInFile(TIniFile* IniFile,AnsiString Section,unsigned short Numb)
{
int Signal1=IniFile->ReadInteger(Section,"Signal"+IntToStr(Numb),-1);
return (Signal1!=-1);
}
//---------------------------------------------------------------------------
void TGraphForm::SaveToIniFile(TIniFile* IniFile)
{
IniFile->WriteInteger("GlobalGraph","GroupCount",TabControl->Tabs->Count);
for(unsigned short i=0;i<TabControl->Tabs->Count;i++)
 {
 if(TabControl->Tabs)
  IniFile->WriteString("GlobalGraph","Name"+IntToStr(i),TabControl->Tabs->Strings[i]);
 unsigned short GraphCount=0;
 for(unsigned short j=0;j<maxgraph;j++)
  if(Graphics[i][j].Signal!=-1)
   {
   Graphics[i][j].WriteFile(IniFile,"Group"+IntToStr(i),GraphCount);
   GraphCount++;
   }//EndFor Graphics
 IniFile->WriteInteger("GlobalGraph","GraphCount"+IntToStr(i),GraphCount);
 }//EndFor Tabs
}
//---------------------------------------------------------------------------
void TGraphForm::ReadFromIniFile(TIniFile* IniFile)
{
unsigned short TabsCount=IniFile->ReadInteger("GlobalGraph","GroupCount",1);
for(unsigned short i=0;i<TabsCount;i++)
 {
 AnsiString TabName=IniFile->ReadString("GlobalGraph","Name"+IntToStr(i),"");
 if(TabControl->Tabs->Count<TabsCount)
  TabControl->Tabs->Add(TabName);
 else TabControl->Tabs->Strings[i]=TabName;
 unsigned short GraphCount=0;
 for(unsigned short j=0;j<maxgraph;j++)
  {
  if(Graphics[i][GraphCount].PresentInFile(IniFile,"Group"+IntToStr(i),j))
   {
   Graphics[i][GraphCount].ReadFile(IniFile,"Group"+IntToStr(i),j);
   GraphCount++;
   }
  else Graphics[i][j].Clear();
  }//EndFor Graphics
 }
}
//---------------------------------------------------------------------------
void __fastcall TGraphForm::FormDestroy(TObject *Sender)
{
//for(int i=0;i<maxgraph;i++){delete []GraphPoint[i];delete []TimePoint[i];}
if(SettingsChanged)
{
DeleteFile(MainForm->ProgramDir+"\\Setgraph.ini");
  TIniFile *IniFile;
  IniFile=new TIniFile(MainForm->ProgramDir+"\\Setgraph.ini");
SaveToIniFile(IniFile);
}
/*for(int i=0;i<maxgraph;i++)
 if(Graphics[i]!=-1)
 {
 IniFile->WriteInteger("Graph"+IntToStr(i),"Param",Graphics[i]);
 IniFile->WriteInteger("Graph"+IntToStr(i),"Color",GraphColor[i]);
 IniFile->WriteString("Graph"+IntToStr(i),"Max",FloatToStr(Max[i]));
 }
delete IniFile;*/
}
//---------------------------------------------------------------------------

void __fastcall TGraphForm::AddBitBtnClick(TObject *Sender)
{
short TabIndex=TabControl->TabIndex;
if(Graphics[TabIndex][maxgraph-1].Signal!=-1)
 {
 Application->MessageBox("Максимум 8 графиков","Сообщение",MB_OK|MB_ICONSTOP);
 return;
 }
AdConnThread->Suspended=true;
TFormOfConnect *Form4;
EnablSaveData=MainForm->DataBaseTimer->Enabled;
MainForm->DataBaseTimer->Enabled=false;
//Фильтрация записей которые нельзя записывать
DataModule1->KanalsTable->Filter="(SaveData='True')";
DataModule1->KanalsTable->Filtered=true;
Form4=new TFormOfConnect(this);
Form4->OnlyPhisic=false;
Form4->OnlySaved=false;
Form4->FieldComboBox->Visible=false;
Form4->ComboBox2->Visible=false;
if(Form4->ShowModal()==mrOk)
 {
 if(ColorDialog->Execute())
  {
  SettingsChanged=true;
  int i=0;
  while(Graphics[TabIndex][i].Signal!=-1) i++;
  for(int j=0;j<i;j++)if(Graphics[TabIndex][j].Signal==Form4->Signal)
   {
   Application->MessageBox("Такой график уже присутствует","Сообщение",MB_OK|MB_ICONSTOP);
   return;
   }
  Graphics[TabIndex][i].Signal=Form4->Signal;//DataModule1->KanalsTable->FieldValues["Number"];
  Graphics[TabIndex][i].Max=defPointerToSignals[Graphics[TabIndex][i].Signal]->Limits.Max;//DataModule1->KanalsTable->FieldValues["Max"];
  Graphics[TabIndex][i].Color=ColorDialog->Color;
  }
 }
delete Form4;
DataModule1->KanalsTable->Filter="";
DataModule1->KanalsTable->Filtered=false;
InitialPoints();
PaintBox->Invalidate();
MainForm->DataBaseTimer->Enabled=EnablSaveData;
AdConnThread->Suspended=false;
}
//---------------------------------------------------------------------------

void __fastcall TGraphForm::TrackBarChange(TObject *Sender)
{
TimeScale=TrackBar->Position;
ValueLabel->Caption=IntToStr(TrackBar->Position);
//PaintBox->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TGraphForm::TrackBarExit(TObject *Sender)
{
PaintBox->Refresh();//Invalidate();
ScrollBox1->Refresh();//Invalidate();

}
//---------------------------------------------------------------------------



void __fastcall TGraphForm::BitBtn2Click(TObject *Sender)
{
 PaintBox->Width=TrackBar->Position;
 SelectMinDate=MaskEdit1->Text;
 SelectMaxDate=MaskEdit->Text;
 //SelectMaxDate=SelectMinDate;
 if(SelectMinDate>SelectMaxDate)
  {
  SelectMaxDate=SelectMinDate;
  MaskEdit->Text=MaskEdit1->Text;
  }
 DateFilter="(Date>='"+SelectMinDate.DateString()+"')and(Date<='"+SelectMaxDate.DateString()+"')";/*and(Date<='"+
 SelectMaxDate.DateString()+"')";                        */
 InitialPoints();
 //DataModule1->StatistTable->Filtered=true;
 PaintBox->Refresh();
 //ScrollBox->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TGraphForm::BitBtn1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------


void __fastcall TGraphForm::FormResize(TObject *Sender)
{
PaintBox->Height=Height-Panel1->Height-50;
}
//---------------------------------------------------------------------------

void __fastcall TGraphForm::DelBitBtnClick(TObject *Sender)
{
short TabIndex=TabControl->TabIndex;
PaintBox->Invalidate();
 TSelGraphForm *Form16=new TSelGraphForm(this);
 for(int i=0;i<maxgraph;i++)
  {
  Form16->Graphics[i]=Graphics[TabIndex][i].Signal;
  Form16->GraphColor[i]=Graphics[TabIndex][i].Color;
  }
  Form16->AllBitBtn->Visible=true;
  TModalResult mod;
  mod=Form16->ShowModal();
  if(mod==mrOk)
  {
  if(Form16->ListBox->ItemIndex!=-1)
   {
   SettingsChanged=true;
   /*if(MainForm->ParamCaptions[Form16->ListBox->ItemIndex]==
   Form16->ListBox->Items->Strings[Form16->ListBox->ItemIndex])*/
   Graphics[TabIndex][Form16->GraphToList[Form16->ListBox->ItemIndex]].Signal=-1;
   //PaintBox1->Invalidate();
   }
  }
  else if(mod==mrAll)
   {
   for(int i=0;i<maxgraph;i++)
    {
    Graphics[TabIndex][i].Signal=-1;
    GraphPoint[i].Size=0;
    delete []GraphPoint[i].Array;
    GraphPoint[i].Array=0;
    }
   }
 delete Form16;
ViewScale=-1;
InitialPoints();
PaintBox->Invalidate();
PaintBox1->Invalidate();
}
//---------------------------------------------------------------------------
/*void __fastcall TGraphForm::SpeedButton1Click(TObject *Sender)
{
short TabIndex=TabControl->TabIndex;
//Print
//New Printing
TDataConteiner** Signal=defPointerToSignals;
if(MainForm->PrintDialog->Execute())
 {
 MainForm->EnablSaveData=MainForm->DataBaseTimer->Enabled;
 MainForm->DataBaseTimer->Enabled=false;
 DataModule1->StatistTable->DisableControls();
 int DLeft=DPI*PListLeft/2.54/10;//MainForm->DLeft*Dpi/2.54,
 int DTop=PListTop*DPI/2.54/10;//MainForm->DTop*Dpi/2.54;//Отступ с лева и с верху
 int ListWidth=PListWidth*DPI/2.54/10;//MainForm->ListWidth*Dpi/2.54;
 int ListHeight=PListHeight*DPI/2.54/10;//MainForm->ListHeight*Dpi/2.54;//ListWidth*PaintBox->Height/PaintBox->Width;
 int StepXP=StepX*ListWidth/1200;//PaintBox->Width;Изменяет величину делений
 int StepYP=StepY*(ListHeight-DPI/5)/(PaintBox->Height-10);
 int ScaleX=StepXP/StepX,ScaleY=StepYP/StepY;
 int BetweenAxis=0.47*DPI;//Between Vert Axis
 int ParamAmount=5;//Amount of Scales
 int ForCaption=0.8*DPI;
 int RealWidth=ListWidth-DPI/5-BetweenAxis*ParamAmount-ForCaption;//DPI/5=0.5*DPI/2.54
 int RealHeight=ListHeight-DPI/5;
 int EndPointsY[maxgraph];
 int IntPartScale=5;
 int FloatPartScale=2;
 Printer()->BeginDoc();
//Рисование осей
Printer()->Canvas->Pen->Width=AxisWidth;
Printer()->Canvas->Pen->Style=psSolid;
Printer()->Canvas->Pen->Color=clBlack;
Printer()->Canvas->Brush->Color=clBlack;
short int ArrowBase=DPI/18;
short int ArrowLength=DPI/6;
//Vert
for(int i=1;i<(ParamAmount+1);i++)
{
TPoint ArrowPoint[3];
ArrowPoint[0]=Point(DLeft+DPI/5+BetweenAxis*i,DTop);
ArrowPoint[1]=Point(DLeft+DPI/5+BetweenAxis*i+ArrowBase/2,DTop+ArrowLength);
ArrowPoint[2]=Point(DLeft+DPI/5+BetweenAxis*i-ArrowBase/2,DTop+ArrowLength);
Printer()->Canvas->MoveTo(DLeft+DPI/5+BetweenAxis*i,DTop);//DPI/5=0.5*DPI/2.54
Printer()->Canvas->LineTo(DLeft+DPI/5+BetweenAxis*i,ListHeight+DTop);
Printer()->Canvas->Polygon(ArrowPoint,2);
}
//Horz
{
TPoint ArrowPoint[3];
ArrowPoint[0]=Point(ListWidth+DLeft,ListHeight+DTop-DPI/5);
ArrowPoint[1]=Point(ListWidth+DLeft-ArrowLength,ListHeight+DTop-DPI/5-ArrowBase/2);
ArrowPoint[2]=Point(ListWidth+DLeft-ArrowLength,ListHeight+DTop-DPI/5+ArrowBase/2);
Printer()->Canvas->MoveTo(DLeft,ListHeight+DTop-DPI/5);
Printer()->Canvas->LineTo(ListWidth+DLeft,ListHeight+DTop-DPI/5);
Printer()->Canvas->Polygon(ArrowPoint,2);
}
Printer()->Canvas->Brush->Color=clWhite;
 //Рисование сетки
Printer()->Canvas->Pen->Width=GirdWidth;
Printer()->Canvas->Pen->Style=psSolid;
Printer()->Canvas->Pen->Color=clBlack;//Gray;
Printer()->Canvas->Font->Size=7;
//Vert
for(int i=DLeft+DPI/5+ParamAmount*BetweenAxis+StepXP;i<ListWidth+DLeft-ForCaption;i=i+StepXP)
  {
  Printer()->Canvas->MoveTo(i,DTop);
  Printer()->Canvas->LineTo(i,ListHeight+DTop-DPI/5);
  }
//Horz
for(int j=ListHeight+DTop-StepYP-DPI/5;j>DTop;j=j-StepYP)
  {
  Printer()->Canvas->MoveTo(DLeft+DPI/5,j);
  Printer()->Canvas->LineTo(ListWidth+DLeft-ForCaption,j);
  }
//Paint Graphics

Printer()->Canvas->Pen->Width=GraphWidth;
DataModule1->StatistTable->First();
//
int Ho,Mi,Sec;
Printer()->Canvas->Pen->Color=clBlack;
TDateTime dTime=double(StepXP)*double(SelectMaxDate-SelectMinDate+1)/(RealWidth);
for(int i=1;i<(RealWidth)/StepXP;i+=2)
 {
 //Out Date Scales
 //Printer()->Canvas->TextOut(DLeft+i*StepXP+ParamAmount*BetweenAxis-9*ScaleX,ListHeight+DTop-49*ScaleY,TDateTime(double(dTime)*i+
 //double(SelectMinDate)).DateString());
 //Out Time Scales
 Printer()->Canvas->TextOut(DLeft+i*StepXP+ParamAmount*BetweenAxis-7*ScaleX,ListHeight+DTop-15*ScaleY,
 TDateTime(double(dTime)*i+double(SelectMinDate)).TimeString());
 }
{//Visibility area 1
TDateTime CurDB,date1;
 int Graphics1[maxgraph];
 float Max1[maxgraph];
 TColor GraphColor1[maxgraph];
 //------------------Если надо печатать все графики необходимо открыть след блок{
//*Запись в массив графиков всех параметров которые пишутся в базу данных
 for(int n=0;n<maxgraph;n++)
  Graphics1[n]=-1;
 for(int n=0;n<maxgraph;n++)
  {
  Graphics1[n]=Graphics[n];
  Max1[n]=Max[n];
  GraphColor1[n]=GraphColor[n];
  GraphColor[n]=n*10;
  }
 AnsiString GraphName="";
 //int k=0;
 for(unsigned int n=0,k=0;n<maxsignal;n++)
  if((Signal[n]->SaveData)&&(k<maxsavedsignal))
   {
   Graphics[k]=n;
   Max[k]=Signal[n]->Limits.Max;
   k++;
   }
  //
 //------------------}
for(int i=0;i<(maxsavedsignal);i++)
{
 if(Graphics[i]!=-1)
  {
  DataModule1->StatistTable->First();
  if(!AllBlack)Printer()->Canvas->Pen->Color=GraphColor[i];
  else Printer()->Canvas->Pen->Color=clBlack;
  DataModule1->StatistTable->Filter="(Numb='"+IntToStr(Graphics[i])+"')and"+DateFilter;
  DataModule1->StatistTable->Filtered=true;
       //DataModule1->StatistTable->FieldCount
  Ho=DataModule1->StatistTable->FieldByName("Hours")->AsInteger;
  Mi=DataModule1->StatistTable->FieldByName("Minuts")->AsInteger;
  Sec=DataModule1->StatistTable->FieldByName("Seconds")->AsInteger;
  int x1=10,y1=ListHeight-10;
  TDateTime time3(Ho,Mi,Sec,0);
  x1=DLeft+ParamAmount*BetweenAxis+DPI/5+double(time3+DataModule1->StatistTable->FieldByName("Date")->AsDateTime-
  SelectMinDate)*(RealWidth)/(SelectMaxDate-SelectMinDate+1);
  y1=RealHeight+DTop-DataModule1->StatistTable->FieldByName("Value")->AsFloat
  *RealHeight/Max[i];
  while(!DataModule1->StatistTable->Eof)
   {
   date1=DataModule1->StatistTable->FieldByName("Date")->AsDateTime;
   Ho=DataModule1->StatistTable->FieldByName("Hours")->AsInteger;
   Mi=DataModule1->StatistTable->FieldByName("Minuts")->AsInteger;
   Sec=DataModule1->StatistTable->FieldByName("Seconds")->AsInteger;
   TDateTime time1(Ho,Mi,Sec,0);
   CurDB=date1+time1;
   int x=DLeft+ParamAmount*BetweenAxis+DPI/5+double(CurDB-SelectMinDate)*(RealWidth)/
   (SelectMaxDate-SelectMinDate+1);
   int y=RealHeight+DTop-DataModule1->StatistTable->FieldByName("Value")->AsFloat*
   RealHeight/Max[i];
   if(((x-x1)>=0)&((x-x1)<(RealWidth*0.6/24)))
    {
    Printer()->Canvas->MoveTo(x1,y1);
    Printer()->Canvas->LineTo(x,y);//=GraphColor[i];
    }
   else
    {
    if(!AllBlack)
     {
     Printer()->Canvas->Pixels[x][y]=GraphColor[i];
     Printer()->Canvas->Pixels[x1][y1]=GraphColor[i];
     }
    else
     {
     Printer()->Canvas->Pixels[x][y]=clBlack;
     Printer()->Canvas->Pixels[x1][y1]=clBlack;
     }
    }

   DataModule1->StatistTable->Next();
   x1=x;y1=y;
   }
  EndPointsY[i]=y1;
  Printer()->Canvas->Font->Size=7;
  if(!AllBlack)Printer()->Canvas->Font->Color=GraphColor[i];
  else Printer()->Canvas->Font->Color=clBlack;
  DataModule1->StatistTable->Filtered=false;
  }
 }

//------------Распечатка масштабов по выбору{
//*
{
const unsigned int NumberOfSignals=5;
unsigned int NumberInArray[NumberOfSignals]={16,17,18,19,20};
for(unsigned int k=0;k<NumberOfSignals;k++)
 {
 int i=NumberInArray[k],pos=k;
 float max=1;
 //for(int n=0;n<maxadam;n++)
 //for(int j=0;j<maxchannel;j++)
  //if(MainForm->Number[n][j]==i)
  //{
  Printer()->Canvas->TextOut(DLeft+DPI/5+pos*BetweenAxis+12*ScaleX,DTop+0.1*DPI,
  Signal[i]->EdIzm);
  max=Signal[i]->Limits.Max;
  //}
 if(!AllBlack)Printer()->Canvas->Font->Color=GraphColor[i];
 else Printer()->Canvas->Font->Color=clBlack;
 for(int j=1;j<(ListHeight-DPI/5)/StepYP;j++)
   {
   Printer()->Canvas->TextOut(DLeft+DPI/5+pos*BetweenAxis+12*ScaleX,ListHeight+DTop-DPI/5-
   15*ScaleY-j*StepYP,FloatToStrF(max/(ListHeight-DPI/5)*j*StepYP,ffFixed,IntPartScale,FloatPartScale));
   }
 }
}

//
//------------}*/
//Signatures
/*//Printer()->Canvas->Font->Size=7;
for(int i=0;i<maxgraph;i++)
 if(Graphics[i]!=-1)
 {
 //for(int n=0;n<maxadam;n++)
  //for(int j=0;j<maxchannel;j++)
   //if(MainForm->Number[n][j]==Graphics[i])
    //{
    if(AllBlack)Printer()->Canvas->Font->Color=GraphColor[i];
    else Printer()->Canvas->Font->Color=clBlack;
    Printer()->Canvas->TextOut(DLeft+ListWidth-ForCaption+2*ScaleX,EndPointsY[i]-5*ScaleY,
    Signal[Graphics[i]]->Name);
    //}
 }
//Main Caption
Printer()->Canvas->Font->Size=16;
AnsiString Capt="Параметры работы вентиляторов ВЦ-15 за ";
Capt+=SelectMinDate.DateString();
Printer()->Canvas->TextOut(ListWidth/3.5+DLeft,DTop-DPI/5,Capt);
Printer()->EndDoc();
//
for(int i=0;i<maxgraph;i++)
  {
  Graphics[i]=Graphics1[i];
  GraphColor[i]=GraphColor1[i];
  Max[i]=Max1[i];
  }
}//End Visibility area 1
 MainForm->DataBaseTimer->Enabled=MainForm->EnablSaveData;
 }//end if
DataModule1->StatistTable->EnableControls();
//End of new printing
//------
//------
//------
//Print
//Old Printing
/*if(MainForm->PrintDialog->Execute())
 {
 MainForm->EnablSaveData=MainForm->DataBaseTimer->Enabled;
 MainForm->DataBaseTimer->Enabled=false;
 DataModule1->StatistTable->DisableControls();
 int DLeft=DPI*PListLeft/2.54/10;//MainForm->DLeft*Dpi/2.54,
 int DTop=PListTop*DPI/2.54/10;//MainForm->DTop*Dpi/2.54;//Отступ с лева и с верху
 int ListWidth=PListWidth*DPI/2.54/10;//MainForm->ListWidth*Dpi/2.54;
 int ListHeight=PListHeight*DPI/2.54/10;//MainForm->ListHeight*Dpi/2.54;//ListWidth*PaintBox->Height/PaintBox->Width;
 int StepXP=StepX*ListWidth/1200;//PaintBox->Width;Изменяет величину делений
 int StepYP=StepY*ListHeight/PaintBox->Height;
 int ScaleX=StepXP/StepX,ScaleY=StepYP/StepY;
 Printer()->BeginDoc();
 //Рисование сетки
Printer()->Canvas->Pen->Width=GirdWidth;
Printer()->Canvas->Pen->Style=psSolid;
Printer()->Canvas->Pen->Color=clBlack;//Gray;
Printer()->Canvas->Font->Size=7;
//Vert
for(int i=DLeft+StepXP+10*ScaleY;i<ListWidth+DLeft;i=i+StepXP)
  {
  Printer()->Canvas->MoveTo(i,DTop);
  Printer()->Canvas->LineTo(i,ListHeight+DTop-10*ScaleY);
  }
//Horz
for(int j=ListHeight+DTop-StepYP-10*ScaleY;j>DTop;j=j-StepYP)
  {
  Printer()->Canvas->MoveTo(DLeft+10*ScaleX,j);
  Printer()->Canvas->LineTo(ListWidth+DLeft,j);
  }
//Рисование осей
Printer()->Canvas->Pen->Width=AxisWidth;
Printer()->Canvas->Pen->Style=psSolid;
Printer()->Canvas->Pen->Color=clBlack;
Printer()->Canvas->MoveTo(DLeft,ListHeight+DTop-10*ScaleY);
Printer()->Canvas->LineTo(ListWidth+DLeft,ListHeight+DTop-10*ScaleY);
Printer()->Canvas->MoveTo(10*ScaleX+DLeft,DTop);
Printer()->Canvas->LineTo(10*ScaleX+DLeft,ListHeight+DTop);
//Paint Graphics
Printer()->Canvas->Pen->Width=GraphWidth;
DataModule1->StatistTable->First();
//
int Ho,Mi,Sec;
Printer()->Canvas->Pen->Color=clBlack;
TDateTime dTime=double(StepXP)*double(SelectMaxDate-SelectMinDate+1)/(ListWidth-10*ScaleX);
for(int i=1;i<(ListWidth-10*ScaleX)/StepXP;i+=2)
 {
 //Out Time Scales
 Printer()->Canvas->TextOut(i*StepXP-9*ScaleX+DLeft,ListHeight+DTop-39*ScaleY,TDateTime(double(dTime)*i+
 double(SelectMinDate)).DateString());
 Printer()->Canvas->TextOut(i*StepXP-9*ScaleX+DLeft,ListHeight+DTop-25*ScaleY,TDateTime(double(dTime)*i+
 double(SelectMinDate)).TimeString());
 }

TDateTime CurDB,date1;
 int Graphics1[maxgraph];
 TColor GraphColor1[maxgraph];
 //------------------Если надо печатать все графики необходимо открыть след блок{
//*Запись в массив графиков всех параметров которые пишутся в базу данных
 for(int n=0;n<maxgraph;n++)
  Graphics1[n]=-1;
 for(int n=0;n<maxgraph;n++)
  {
  Graphics1[n]=Graphics[n];
  GraphColor1[n]=GraphColor[n];
  GraphColor[n]=n*10;
  }

 AnsiString GraphName="";
 int k=0;
 for(int n=0;n<maxadam;n++)
  for(int j=0;j<maxchannel;j++)
  if(MainForm->SaveData[n][j])
   {
   Graphics[k]=MainForm->Number[n][j];
   k++;
   }
  //
 //------------------}
for(int i=0;i<(maxadam*maxchannel);i++)
{

 if(Graphics[i]!=-1)
  {
  DataModule1->StatistTable->First();
  if(!AllBlack)Printer()->Canvas->Pen->Color=GraphColor[i];
  else Printer()->Canvas->Pen->Color=clBlack;
  DataModule1->StatistTable->Filter="(Numb='"+IntToStr(Graphics[i])+"')and"+DateFilter;
  DataModule1->StatistTable->Filtered=true;
       //DataModule1->StatistTable->FieldCount
  Ho=DataModule1->StatistTable->FieldByName("Hours")->AsInteger;
  Mi=DataModule1->StatistTable->FieldByName("Minuts")->AsInteger;
  Sec=DataModule1->StatistTable->FieldByName("Seconds")->AsInteger;
  int x1=10,y1=ListHeight-10;
  TDateTime time3(Ho,Mi,Sec,0);
  x1=10*ScaleX+double(time3+DataModule1->StatistTable->FieldByName("Date")->AsDateTime-
  SelectMinDate)*(ListWidth-10*ScaleY)/(SelectMaxDate-SelectMinDate+1);
  y1=ListHeight-10*ScaleY-DataModule1->StatistTable->FieldByName("Value")->AsFloat
  *ListHeight/Max[i];
  while(!DataModule1->StatistTable->Eof)
   {
   date1=DataModule1->StatistTable->FieldByName("Date")->AsDateTime;
   Ho=DataModule1->StatistTable->FieldByName("Hours")->AsInteger;
   Mi=DataModule1->StatistTable->FieldByName("Minuts")->AsInteger;
   Sec=DataModule1->StatistTable->FieldByName("Seconds")->AsInteger;
   TDateTime time1(Ho,Mi,Sec,0);
   CurDB=date1+time1;
   int x=10*ScaleX+DLeft+double(CurDB-SelectMinDate)*(ListWidth-10*ScaleX)/
   (SelectMaxDate-SelectMinDate+1);
   int y=ListHeight+DTop-10*ScaleY-DataModule1->StatistTable->FieldByName("Value")->AsFloat*
   ListHeight/Max[i];
   if(((x-x1)>=0)&((x-x1)<(ListWidth*0.6/24)))
    {
    Printer()->Canvas->MoveTo(x1,y1);
    Printer()->Canvas->LineTo(x,y);//=GraphColor[i];
    }
   else
    {
    if(!AllBlack)
     {
     Printer()->Canvas->Pixels[x][y]=GraphColor[i];
     Printer()->Canvas->Pixels[x1][y1]=GraphColor[i];
     }
    else
     {
     Printer()->Canvas->Pixels[x][y]=clBlack;
     Printer()->Canvas->Pixels[x1][y1]=clBlack;
     }
    }

   DataModule1->StatistTable->Next();
   x1=x;y1=y;
   }
  Printer()->Canvas->Font->Size=7;
  if(!AllBlack)Printer()->Canvas->Font->Color=GraphColor[i];
  else Printer()->Canvas->Font->Color=clBlack;
//------------Если нет необходимости печатать все графики откройте след. блок{

//  for(int j=1;j<(ListHeight-10*ScaleX)/StepYP;j++)
//   {
//   //Out Value Scales
//   Printer()->Canvas->TextOut(i*StepXP*1+12*ScaleX+DLeft
//   ,ListHeight+DTop-23*ScaleY-j*StepYP,
//   FloatToStrF(Max[i]/ListHeight*j*StepYP,ffFixed,5,4));
//   }//
//------------}
  DataModule1->StatistTable->Filtered=false;
  }
 }
//------------Распечатка масштабов по выбору{
//*
int i=16,pos=0;
float max=1;
for(int n=0;n<maxadam;n++)
 for(int j=0;j<maxchannel;j++)
  if(MainForm->Number[n][j]==i)
  {
  Printer()->Canvas->TextOut(pos*StepXP*1+12*ScaleX+DLeft,0.1*DPI,
  MainForm->EdIzm[n][j]);
  max=MainForm->Max[n][j];
  }
if(!AllBlack)Printer()->Canvas->Font->Color=GraphColor[i];
else Printer()->Canvas->Font->Color=clBlack;
for(int j=1;j<(ListHeight-10*ScaleX)/StepYP;j++)
   {
   Printer()->Canvas->TextOut(pos*StepXP*1+12*ScaleX+DLeft,ListHeight+DTop-23*ScaleY-j*StepYP,
   FloatToStrF(max/ListHeight*j*StepYP,ffFixed,5,4));
   }
//--------------------
i=17;pos=1;
for(int n=0;n<maxadam;n++)
 for(int j=0;j<maxchannel;j++)
  if(MainForm->Number[n][j]==i)
  {
  Printer()->Canvas->TextOut(pos*StepXP*1+12*ScaleX+DLeft,0.1*DPI,
  MainForm->EdIzm[n][j]);
  max=MainForm->Max[n][j];
  }
if(!AllBlack)Printer()->Canvas->Font->Color=GraphColor[i];
else Printer()->Canvas->Font->Color=clBlack;
for(int j=1;j<(ListHeight-10*ScaleX)/StepYP;j++)
   {
   Printer()->Canvas->TextOut(pos*StepXP*1+12*ScaleX+DLeft,ListHeight+DTop-23*ScaleY-j*StepYP,
   FloatToStrF(max/ListHeight*j*StepYP,ffFixed,5,4));
   }
//--------------------
i=18;pos=2;
for(int n=0;n<maxadam;n++)
 for(int j=0;j<maxchannel;j++)
  if(MainForm->Number[n][j]==i)
  {
  Printer()->Canvas->TextOut(pos*StepXP*1+12*ScaleX+DLeft,0.1*DPI,
  MainForm->EdIzm[n][j]);
  max=MainForm->Max[n][j];
  }
if(!AllBlack)Printer()->Canvas->Font->Color=GraphColor[i];
else Printer()->Canvas->Font->Color=clBlack;
for(int j=1;j<(ListHeight-10*ScaleX)/StepYP;j++)
   {
   Printer()->Canvas->TextOut(pos*StepXP*1+12*ScaleX+DLeft,ListHeight+DTop-23*ScaleY-j*StepYP,
   FloatToStrF(max/ListHeight*j*StepYP,ffFixed,5,4));
   }
//--------------------
i=19;pos=3;
for(int n=0;n<maxadam;n++)
 for(int j=0;j<maxchannel;j++)
  if(MainForm->Number[n][j]==i)
  {
  Printer()->Canvas->TextOut(pos*StepXP*1+12*ScaleX+DLeft,0.1*DPI,
  MainForm->EdIzm[n][j]);
  max=MainForm->Max[n][j];
  }
if(!AllBlack)Printer()->Canvas->Font->Color=GraphColor[i];
else Printer()->Canvas->Font->Color=clBlack;
for(int j=1;j<(ListHeight-10*ScaleX)/StepYP;j++)
   {
   Printer()->Canvas->TextOut(pos*StepXP*1+12*ScaleX+DLeft,ListHeight+DTop-23*ScaleY-j*StepYP,
   FloatToStrF(max/ListHeight*j*StepYP,ffFixed,5,4));
   }
//--------------------
i=20;pos=4;
for(int n=0;n<maxadam;n++)
 for(int j=0;j<maxchannel;j++)
  if(MainForm->Number[n][j]==i)
  {
  Printer()->Canvas->TextOut(pos*StepXP*1+12*ScaleX+DLeft,0.1*DPI,
  MainForm->EdIzm[n][j]);
  max=MainForm->Max[n][j];
  }
if(!AllBlack)Printer()->Canvas->Font->Color=GraphColor[i];
else Printer()->Canvas->Font->Color=clBlack;
for(int j=1;j<(ListHeight-10*ScaleX)/StepYP;j++)
   {
   Printer()->Canvas->TextOut(pos*StepXP*1+12*ScaleX+DLeft,ListHeight+DTop-23*ScaleY-j*StepYP,
   FloatToStrF(max/ListHeight*j*StepYP,ffFixed,5,4));
   }
//
//------------}
Printer()->EndDoc();
//
for(int i=0;i<maxgraph;i++)
  {
  Graphics[i]=Graphics1[i];
  GraphColor[i]=GraphColor1[i];
  }
 MainForm->DataBaseTimer->Enabled=MainForm->EnablSaveData;
 }//end if
DataModule1->StatistTable->EnableControls();*///End of old printing
//}
//---------------------------------------------------------------------------
void __fastcall TGraphForm::Panel2MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
//if(Panel2->Width<20)
//{
//PanelWidth=50;
Panel2->Width=50;//PanelWidth;
PanelVis=true;
PaintBox1->Invalidate();
//}
}
//---------------------------------------------------------------------------
void __fastcall TGraphForm::PaintBox1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
short TabIndex=TabControl->TabIndex;
if(Button==mbLeft)
Panel2->Width=5;
else
 {
 TSelGraphForm *Form16=new TSelGraphForm(this);
 for(int i=0;i<maxgraph;i++)
  {
  Form16->Graphics[i]=Graphics[TabIndex][i].Signal;
  Form16->GraphColor[i]=Graphics[TabIndex][i].Color;
  }
  if(Form16->ShowModal()==mrOk)
  if(Form16->ListBox->ItemIndex!=-1)
   {
   /*if(MainForm->ParamCaptions[Form16->ListBox->ItemIndex]==
   Form16->ListBox->Items->Strings[Form16->ListBox->ItemIndex])*/
   ViewScale=Form16->GraphToList[Form16->ListBox->ItemIndex];
   PaintBox1->Invalidate();
   }
 delete Form16;
 }
}
//---------------------------------------------------------------------------


void __fastcall TGraphForm::PaintBox1Paint(TObject *Sender)
{
if(PaintBox1->Width<10)return;
unsigned short TabIndex=TabControl->TabIndex;
//int w=PaintBox->Width;
int h=PaintBox->Height;
int w1=PaintBox1->Width;
//int h1=PaintBox1->Height;
if(Graphics[TabIndex][ViewScale].Signal>=0)
 {
 PaintBox1->Canvas->Font->Color=Graphics[TabIndex][ViewScale].Color;
 //for(unsigned int i=0;i<maxsignal;i++)
 //for(int j=0;j<maxchannel;j++)
  //{
  PaintBox1->Canvas->Font->Size=6;       //DataModule1->Signal[0]
  if(defPointerToSignals[Graphics[TabIndex][ViewScale].Signal])
   {
   PaintBox1->Canvas->TextOut(1,2,defPointerToSignals[Graphics[TabIndex][ViewScale].Signal]->Name);
   PaintBox1->Canvas->Font->Size=7;
   PaintBox1->Canvas->TextOut(1,PaintBox1->Height-23,defPointerToSignals[Graphics[TabIndex][ViewScale].Signal]->EdIzm);
   //--------
   float Min1=defPointerToSignals[Graphics[TabIndex][ViewScale].Signal]->Limits.Min,
   Max1=defPointerToSignals[Graphics[TabIndex][ViewScale].Signal]->Limits.Max;
   Max1=(Max1>-Min1)?Max1:-Min1;
   float Delta=2*Max1;
   for(int i=1;i<h/StepY-1;i++)
    {
    //Out Value Scales
    if(defPointerToSignals[Graphics[TabIndex][ViewScale].Signal]->Limits.Min>=0)
     {
     PaintBox1->Canvas->TextOut(1/*+ScrollBox->HorzScrollBar->Position*/,
     h-23-i*StepY,FloatToStrF(Graphics[TabIndex][ViewScale].Max/float(h-10)*i*StepY,ffFixed,5,4));
     }
    else
     {
     //float a=
     PaintBox1->Canvas->TextOut(1/*+ScrollBox->HorzScrollBar->Position*/,
     h-23-i*StepY,FloatToStrF(-Max1+Delta/float(h-10)*(float(i)/*-float(h)/float(StepY)/2.0*/)*StepY,ffFixed,5,4));
     }
    }
   }
  }
PaintBox1->Canvas->Pen->Color=clBlack;
for(int i=h-10-StepY;i>=0;i-=StepY)
 {
 PaintBox1->Canvas->MoveTo(0,i);
 PaintBox1->Canvas->LineTo(w1,i);
 }
if(ViewScale<0)
 {
 ViewScale=0;
 for(unsigned  short i=0;i<maxgraph;i++)
  if(Graphics[TabIndex][i].Signal>0)
   {
   ViewScale=i;
   break;
   }
 }

}
//---------------------------------------------------------------------------




void __fastcall TGraphForm::StandartSButtonClick(TObject *Sender)
{
InitialPoints();
PaintBox->Invalidate();
}
//---------------------------------------------------------------------------




void __fastcall TGraphForm::SetupItemClick(TObject *Sender)
{
/*TIniFile IniFile=new TIniFile(ProgramDir+"\\Setgraph.ini");
IniFile->ReadBool("GlobalSettings","SaveData",true);
TSetPrnFo *Form6;
Form6=new TSetPrnFo(this);
Form6->WidthEdit->Text=IntToStr(ListWidth);
Form6->HeightEdit->Text=IntToStr(ListHeight);
Form6->LeftEdit->Text=IntToStr(ListLeft);
Form6->TopEdit->Text=IntToStr(ListTop);
Form6->DPIEdit->Text=IntToStr(DPI);
Form6->GirdUpDown->Position=GirdWidth;
Form6->AxisUpDown->Position=AxisWidth;
Form6->GraphUpDown->Position=GraphWidth;
Form6->StepXEdit->Text=IntToStr(StepX);
Form6->StepYEdit->Text=IntToStr(StepY);
Form6->SetEdit();
Form6->ColorCheckBox->Checked=AllBlack;
if(Form6->ShowModal()==mrOk)
{
ListWidth=StrToInt(Form6->WidthEdit->Text);
ListHeight=StrToInt(Form6->HeightEdit->Text);
ListLeft=StrToInt(Form6->LeftEdit->Text);
ListTop=StrToInt(Form6->TopEdit->Text);
DPI=StrToInt(Form6->DPIEdit->Text);
GirdWidth=StrToInt(Form6->GirdEdit->Text);
AxisWidth=StrToInt(Form6->AxisEdit->Text);
GraphWidth=StrToInt(Form6->GraphEdit->Text);
AllBlack=Form6->ColorCheckBox->Checked;
int a=StrToInt(Form6->StepXEdit->Text);
if(a<10) StepX=10;
else if(a>200)StepX=200;
else StepX=a;
a=StrToInt(Form6->StepYEdit->Text);
if(a<20) StepY=20;
else if(a>200)StepY=200;
else StepY=a;
//StepX=StrToInt(Form6->StepXEdit->Text);
//StepY=StrToInt(Form6->StepYEdit->Text);
}
delete Form6;  */
}
//---------------------------------------------------------------------------

void __fastcall TGraphForm::AllOnOneItemClick(TObject *Sender)
{
//short Type=-1;
unsigned short TabIndex=TabControl->TabIndex;
TTable* Table=DataModule1->KanalsTable;
Table->Filter="(SaveData='True')";
if(!Table->Filtered)Table->Filtered=true;
int RecCount=Table->RecordCount;
int SelRecCount=0;
for(int i=0;i<maxgraph;i++)if(Graphics[TabIndex][i].Signal!=-1)SelRecCount++;
int AllInGroup=0;
for(int i=0;i<TabControl->Tabs->Count;i++)
 for(int j=0;j<maxgraph;j++)
  if(Graphics[i][j].Signal!=-1)AllInGroup++;
Table->Filtered=false;
AnsiString Message;//="Сейчас будут напечатаны все ";
int DLeft=DPI*PListLeft/2.54/10;//MainForm->DLeft*Dpi/2.54,
int DTop=PListTop*DPI/2.54/10;//MainForm->DTop*Dpi/2.54;//Отступ с лева и с верху
int ListWidth=PListWidth*DPI/2.54/10;//MainForm->ListWidth*Dpi/2.54;
int ListHeight=PListHeight*DPI/2.54/10;//MainForm->ListHeight*Dpi/2.54;//ListWidth*PaintBox->Height/PaintBox->Width;
int StepXP=StepX*ListWidth/1200;//PaintBox->Width;Изменяет величину делений
int StepYP=StepY*(ListHeight-DPI/5)/(PaintBox->Height-10);
int ScaleX=StepXP/StepX,ScaleY=StepYP/StepY;
int BetweenAxis=0.47*DPI;//Between Vert Axis
int ParamAmount=5;//Amount of Scales
int ForCaption=0.8*DPI;//Place for signatures of  each graphik
int RealWidth;//=ListWidth-DPI/5-BetweenAxis*ParamAmount-ForCaption;//DPI/5=0.5*DPI/2.54
int RealHeight=ListHeight-DPI/5;
int EndPointsY[maxgraph];
//TArrayPointer Array;//Array.Size=0;
//Maike and send message
//if(MainForm->PrintDialog->Execute())
//{
if(Sender==AllOnOneItem)
  {
  Message=IntToStr(RecCount)+" графиков из базы  данных на одном листе оси с масштабами которые будут напечатаны зависят от настроек в параметрах печати";
  ParamAmount=RecCount;
  RealWidth=ListWidth-DPI/5-BetweenAxis*ParamAmount-ForCaption;
  //Array.Size=RecCount;
  }
else if (Sender==EachOnSingleItem)
  {
  Message=IntToStr(RecCount)+" графиков  из базы  данных каждый на отдельном листе";
  ParamAmount=RecCount;
  RealWidth=ListWidth-DPI/5-BetweenAxis/**ParamAmount*/-ForCaption;
  //Array.Size=RecCount;
  }
else if(Sender==SelectedGroupItem)//
  {
  Message=IntToStr(SelRecCount)+" графиков в выбранной группе на одном листе";
  ParamAmount=SelRecCount;
  RealWidth=ListWidth-DPI/5-BetweenAxis*ParamAmount-ForCaption;
  //Array.Size=SelRecCount;
  }
else if(Sender==EachInGroupOnSingleItem)
  {
  Message=IntToStr(SelRecCount)+" графиков в выбранной группе каждый на отдельном листе";
  ParamAmount=SelRecCount;
  RealWidth=ListWidth-DPI/5-BetweenAxis/**ParamAmount*/-ForCaption;
  //Array.Size=SelRecCount;
  }
else if(Sender==EachGroupOnSingleItem)
  {
  Message=IntToStr(AllInGroup)+" графиков из "+IntToStr(TabControl->Tabs->Count)+
   " групп каждая группа на  отдельном листе";
  ParamAmount=SelRecCount;
  RealWidth=ListWidth-DPI/5-BetweenAxis/**ParamAmount*/-ForCaption;
  }
else {MainForm->DataBaseTimer->Enabled=MainForm->EnablSaveData;return;}
//Array.Array=new short[Array->Size];
 {
 AnsiString Message1="Сейчас будут напечатаны все "+Message;
 Message=Message1;
 }
 {
 //char Mes[]=;
 if(Application->MessageBox(Message.c_str(),"Сообщение",MB_OKCANCEL|MB_ICONWARNING|MB_DEFBUTTON1|MB_APPLMODAL)==ID_CANCEL)
     {MainForm->DataBaseTimer->Enabled=MainForm->EnablSaveData;return;}
 }
if(!MainForm->PrintDialog->Execute()){MainForm->DataBaseTimer->Enabled=MainForm->EnablSaveData;return;}
//Printing graphics
MainForm->EnablSaveData=MainForm->DataBaseTimer->Enabled;
 MainForm->DataBaseTimer->Enabled=false;
 DataModule1->StatistTable->DisableControls();
 //}//end if
DataModule1->StatistTable->EnableControls();
Table->Filter="(SaveData='True')";
if(!Table->Filtered)Table->Filtered=true;
Table->FindFirst();
if(Sender==AllOnOneItem)
   {
   if(!Table->RecordCount)return;
   TArrayPointer Array;Array.Size=Table->RecordCount;Array.Array=new short[Table->RecordCount];
   TArrayPointer Axis;Axis.Size=0;
   for(int i=0;i<maxgraph;i++)if(PrintedAxis[i]>-1)Axis.Size++;
   Axis.Array=new short[Axis.Size];
   for(int i=0,j=0;i<maxgraph;i++)if(PrintedAxis[i]>-1){Axis.Array[j]=PrintedAxis[i];j++;}
   //TFloatArrayPointer Maxes;Maxes.Size=Table->RecordCount;Maxes.Array=new float[Table->RecordCount];
   int Counter=0;
   bool a;
   do
    {
    int Numb=Table->FieldByName("Number")->AsInteger;
    if(defPointerToSignals[Numb])Array.Array[Counter]=Numb;
    else Array.Array[Counter]=-1;
    //Maxes.Array[Counter]=Table->FieldByName("Max")->AsFloat;
    a=Table->FindNext();
    if(a)Counter++;
    }
   while(a);
   int* EndPoints;
   //EndPoints=new int[Counter];
   Printer()->BeginDoc();
   TRect Rect;Rect.Left=DLeft/*+ForCaption*/;Rect.Top=DTop;
   Rect.Bottom=Rect.Top+ListHeight;Rect.Right=Rect.Left+ListWidth-ForCaption;
   PaintGird(&Rect,Printer()->Canvas,&Axis,BetweenAxis,StepXP,StepYP,RealWidth);
   Rect.Left=DLeft+DPI/5+Axis.Size*BetweenAxis;Rect.Right=ListWidth+DLeft-ForCaption;
   Rect.Top=DTop;Rect.Bottom=ListHeight+DTop-DPI/5;
   for(unsigned int i=0;i<Array.Size;i++)
    {
    int EndPoint;
    Printer()->Canvas->Font->Size=printnumfontsize;
    PaintGraphI(&Rect,Printer()->Canvas,Array.Array[i],clBlack,EndPoint);
    Printer()->Canvas->TextOut(DLeft+ListWidth-ForCaption+2*ScaleX,EndPoint-5*ScaleY,
    defPointerToSignals[Array.Array[i]]->Name);
    }
   //Main Caption
   Printer()->Canvas->Font->Size=16;
   AnsiString Capt="Параметры работы котельной с ";
   Capt+=SelectMinDate.DateString();Capt+=" по ";Capt+=SelectMaxDate.DateString();
   Printer()->Canvas->TextOut(ListWidth/3.5+DLeft,DTop-DPI/5,Capt);
   //delete []EndPoints;
   Printer()->EndDoc();
   }
else if(Sender==EachOnSingleItem)
   {
   if(!Table->RecordCount)return;
   TArrayPointer Array;Array.Size=Table->RecordCount;Array.Array=new short[Table->RecordCount];
   TArrayPointer Axis;Axis.Size=0;
     //for(int i=0;i<maxgraph;i++)if(PrintedAxis[i]>-1)Axis.Size++;
     //Axis.Array=new short[Axis.Size];
     //for(int i=0,j=0;i<maxgraph;i++)if(PrintedAxis[i]>-1){Axis.Array[j]=PrintedAxis[i];j++;}
   Axis.Array=new short[1];Axis.Size=1;
   //TFloatArrayPointer Maxes;Maxes.Size=Table->RecordCount;Maxes.Array=new float[Table->RecordCount];
   int Counter=0;
   bool a;
   do
    {
    int Numb=Table->FieldByName("Number")->AsInteger;
    if(defPointerToSignals[Numb])Array.Array[Counter]=Numb;
    else Array.Array[Counter]=-1;
    //Maxes.Array[Counter]=Table->FieldByName("Max")->AsFloat;
    a=Table->FindNext();
    if(a)Counter++;
    }
   while(a);
   int* EndPoints;
   //EndPoints=new int[Counter];
  for(unsigned int j=0;j<Array.Size;j++)
   {
   Axis.Array[0]=Array.Array[j];
   Printer()->BeginDoc();
   TRect Rect;Rect.Left=DLeft/*+ForCaption*/;Rect.Top=DTop;
   Rect.Bottom=Rect.Top+ListHeight;Rect.Right=Rect.Left+ListWidth;
   PaintGird(&Rect,Printer()->Canvas,&Axis,BetweenAxis,StepXP,StepYP,RealWidth);
   Rect.Left=DLeft+DPI/5+Axis.Size*BetweenAxis;Rect.Right=ListWidth+DLeft;
   Rect.Top=DTop;Rect.Bottom=ListHeight+DTop-DPI/5;
   //for(int i=0;i<Array.Size;i++)
    //{
    int EndPoint;
    Printer()->Canvas->Font->Size=printnumfontsize;
    PaintGraphI(&Rect,Printer()->Canvas,Array.Array[j],clBlack,EndPoint);
   // Printer()->Canvas->TextOut(DLeft+ListWidth-ForCaption+2*ScaleX,EndPoint-5*ScaleY,
    //defPointerToSignals[Array.Array[i]]->Name);
   //Main Caption
   Printer()->Canvas->Font->Size=16;
   AnsiString Capt="Параметр ";Capt+=defPointerToSignals[Array.Array[j]]->Name;
   Capt+=" за период с ";
   Capt+=SelectMinDate.DateString();Capt+=" по ";Capt+=SelectMaxDate.DateString();
   Printer()->Canvas->TextOut(ListWidth/3.5+DLeft,DTop-DPI/5,Capt);
   //delete []EndPoints;
   Printer()->EndDoc();
   }
}
else if(Sender==SelectedGroupItem)
   {
   //if(!Table->RecordCount)return;
   TArrayPointer Array;//Array.Size=Table->RecordCount;Array.Array=new short[Table->RecordCount];
   TArrayPointer Axis;Axis.Size=0;
   for(int i=0;i<maxgraph;i++)if(Graphics[TabIndex][i].Signal<4000000000)Array.Size++;
   Array.Array=new short[Array.Size];
   for(int i=0,j=0;i<maxgraph;i++)if(Graphics[TabIndex][i].Signal<4000000000)
     {Array.Array[j]=Graphics[TabIndex][i].Signal;j++;}
   //Select Axis to paint
   FillAxisArray(Array,Axis);
   //TFloatArrayPointer Maxes;Maxes.Size=Table->RecordCount;Maxes.Array=new float[Table->RecordCount];
   //int Counter=0;for(int i=0;i<maxgraph;i++)if(Graphics[TabIndex][i].Signal!=-1)Counter++;
   //Array.Size=Counter;Array.Array=new short[Array.Size];
   //Counter=0;
   //for(int i=0;i<maxgraph;i++)if(Graphics[TabIndex][i].Signal!=-1)
    //{
    //Array.Array[Counter]=Graphics[TabIndex][i].Signal;
    //Counter++;
    //}
   Printer()->BeginDoc();
   TRect Rect;Rect.Left=DLeft/*+ForCaption*/;Rect.Top=DTop;
   Rect.Bottom=Rect.Top+ListHeight;Rect.Right=Rect.Left+ListWidth-ForCaption;
   PaintGird(&Rect,Printer()->Canvas,&Axis,BetweenAxis,StepXP,StepYP,RealWidth);
   Rect.Left=DLeft+DPI/5+Axis.Size*BetweenAxis;Rect.Right=ListWidth+DLeft-ForCaption;
   Rect.Top=DTop;Rect.Bottom=ListHeight+DTop-DPI/5;
   int EndPoints[maxgraph];
   for(unsigned int i=0;i<Array.Size;i++)
    {
    //int EndPoint=0;
    Printer()->Canvas->Font->Size=printnumfontsize;
    PaintGraphI(&Rect,Printer()->Canvas,Array.Array[i],clBlack,EndPoints[i]/*EndPoint*/);
    /*Printer()->Canvas->TextOut(DLeft+ListWidth-ForCaption+2*ScaleX,EndPoint-5*ScaleY,
    defPointerToSignals[Array.Array[i]]->Name);*/
    }
   unsigned short Delta1=10;
   for(unsigned short i=0;i<Array.Size;i++)
    {
    int EndPoint=EndPoints[i];
    unsigned short Counter=0;
    bool Ok=true;
    do
    {
    Ok=true;
    for(unsigned short j=0;j<i;j++)
     {
     //if(Counter>5)
     if((EndPoints[j]>EndPoint-Delta1*ScaleY)&&(EndPoints[j]<=EndPoint))
      {
      Ok=false;
      EndPoint=EndPoints[j]+Delta1*ScaleY+2;
      Counter++;
      }
     else if((EndPoints[j]<EndPoint+Delta1*ScaleY)&&(EndPoints[j]>=EndPoint))
      {
      Ok=false;
      EndPoint=EndPoints[j]-Delta1*ScaleY-2;
      Counter++;
      //break;
      }
     //else break;
     }
    }while((!Ok)&&(Counter<10));
    EndPoints[i]=EndPoint;
    }
   for (unsigned int i=0;i<Array.Size;i++)
    {
    Printer()->Canvas->TextOut(DLeft+ListWidth-ForCaption+2*ScaleX,EndPoints[i]-5*ScaleY,
    defPointerToSignals[Array.Array[i]]->Name);
    }
   //Main Caption
   Printer()->Canvas->Font->Size=16;
   AnsiString Capt="Параметры "+TabControl->Tabs->Strings[TabIndex]+" с ";
   Capt+=SelectMinDate.DateString();Capt+=" по ";Capt+=SelectMaxDate.DateString();
   Printer()->Canvas->TextOut(ListWidth/3.5+DLeft,DTop-DPI/5,Capt);
   //delete []EndPoints;
   Printer()->EndDoc();
   }
else if(Sender==EachInGroupOnSingleItem)
   {
   //TArrayPointer Array;//Array.Size=Table->RecordCount;Array.Array=new short[Table->RecordCount];
   TArrayPointer Axis;Axis.Size=0;
   Axis.Array=new short[1];Axis.Size=1;

   //for(int i=0;i<maxgraph;i++)if(PrintedAxis[i]>-1)Axis.Size++;
   //Axis.Array=new short[Axis.Size];
   //for(int i=0,j=0;i<maxgraph;i++)if(PrintedAxis[i]>-1){Axis.Array[j]=PrintedAxis[i];j++;}
   //TFloatArrayPointer Maxes;Maxes.Size=Table->RecordCount;Maxes.Array=new float[Table->RecordCount];
   //int Counter=0;for(int i=0;i<maxgraph;i++)if(Graphics[i]!=-1)Counter++;
   //Array.Size=Counter;Array.Array=new short[Array.Size];
   //Counter=0;
   //for(int i=0;i<maxgraph;i++)if(Graphics[i]!=-1)
   // {
  //  Array.Array[Counter]=Graphics[i];
  //  Counter++;
   // }

   for(int i=0;i<maxgraph;i++)
   if((Graphics[TabIndex][i].Signal!=-1)&&(defPointerToSignals[Graphics[TabIndex][i].Signal]))
    {
    Axis.Array[0]=Graphics[TabIndex][i].Signal;
    Printer()->BeginDoc();
    TRect Rect;Rect.Left=DLeft/*+ForCaption*/;Rect.Top=DTop;
    Rect.Bottom=Rect.Top+ListHeight;Rect.Right=Rect.Left+ListWidth;
    PaintGird(&Rect,Printer()->Canvas,&Axis,BetweenAxis,StepXP,StepYP,RealWidth);
    Rect.Left=DLeft+DPI/5+Axis.Size*BetweenAxis;Rect.Right=ListWidth+DLeft;
    Rect.Top=DTop;Rect.Bottom=ListHeight+DTop-DPI/5;
    int EndPoint=0;
    Printer()->Canvas->Font->Size=printnumfontsize;
    PaintGraphI(&Rect,Printer()->Canvas,Graphics[TabIndex][i].Signal,clBlack,EndPoint);
    //Printer()->Canvas->TextOut(DLeft+ListWidth-ForCaption+2*ScaleX,EndPoint-5*ScaleY,
    //defPointerToSignals[Array.Array[i]]->Name);
    Printer()->Canvas->Font->Size=16;
    AnsiString Capt="Параметр ";Capt+=defPointerToSignals[Graphics[TabIndex][i].Signal]->Name;
    Capt+=" за период с ";
    Capt+=SelectMinDate.DateString();Capt+=" по ";Capt+=SelectMaxDate.DateString();
    Printer()->Canvas->TextOut(ListWidth/3.5+DLeft,DTop-DPI/5,Capt);
    //delete []EndPoints;
    Printer()->EndDoc();
    }
   //Main Caption

   }
else if(Sender==EachGroupOnSingleItem)
   {
  for(TabIndex=0;TabIndex<TabControl->Tabs->Count;TabIndex++)
   {
   TArrayPointer Array;//Array.Size=Table->RecordCount;Array.Array=new short[Table->RecordCount];
   TArrayPointer Axis;Axis.Size=0;
   for(int i=0;i<maxgraph;i++)if(Graphics[TabIndex][i].Signal>-1)Array.Size++;
   Array.Array=new short[Array.Size];
   for(int i=0,j=0;i<maxgraph;i++)if(Graphics[TabIndex][i].Signal>-1)
     {Array.Array[j]=Graphics[TabIndex][i].Signal;j++;}
   //Select Axis to paint
   FillAxisArray(Array,Axis);
   //TFloatArrayPointer Maxes;Maxes.Size=Table->RecordCount;Maxes.Array=new float[Table->RecordCount];
   //int Counter=0;for(int i=0;i<maxgraph;i++)if(Graphics[TabIndex][i].Signal!=-1)Counter++;
   //Array.Size=Counter;Array.Array=new short[Array.Size];
   //Counter=0;
   //for(int i=0;i<maxgraph;i++)if(Graphics[TabIndex][i].Signal!=-1)
    //{
    //Array.Array[Counter]=Graphics[TabIndex][i].Signal;
    //Counter++;
    //}
   Printer()->BeginDoc();
   TRect Rect;Rect.Left=DLeft/*+ForCaption*/;Rect.Top=DTop;
   Rect.Bottom=Rect.Top+ListHeight;Rect.Right=Rect.Left+ListWidth-ForCaption;
   PaintGird(&Rect,Printer()->Canvas,&Axis,BetweenAxis,StepXP,StepYP,RealWidth);
   Rect.Left=DLeft+DPI/5+Axis.Size*BetweenAxis;Rect.Right=ListWidth+DLeft-ForCaption;
   Rect.Top=DTop;Rect.Bottom=ListHeight+DTop-DPI/5;
   int EndPoints[maxgraph];
   for(unsigned int i=0;i<Array.Size;i++)
    {
    //int EndPoint=0;
    Printer()->Canvas->Font->Size=printnumfontsize;
    PaintGraphI(&Rect,Printer()->Canvas,Array.Array[i],clBlack,EndPoints[i]/*EndPoint*/);
    /*Printer()->Canvas->TextOut(DLeft+ListWidth-ForCaption+2*ScaleX,EndPoint-5*ScaleY,
    defPointerToSignals[Array.Array[i]]->Name);*/
    }
   unsigned short Delta1=10;
   for(unsigned short i=0;i<Array.Size;i++)
    {
    int EndPoint=EndPoints[i];
    unsigned short Counter=0;
    bool Ok=true;
    do
    {
    Ok=true;
    for(unsigned short j=0;j<i;j++)
     {
     //if(Counter>5)
     if((EndPoints[j]>EndPoint-Delta1*ScaleY)&&(EndPoints[j]<=EndPoint))
      {
      Ok=false;
      EndPoint=EndPoints[j]+Delta1*ScaleY+2;
      Counter++;
      }
     else if((EndPoints[j]<EndPoint+Delta1*ScaleY)&&(EndPoints[j]>=EndPoint))
      {
      Ok=false;
      EndPoint=EndPoints[j]-Delta1*ScaleY-2;
      Counter++;
      //break;
      }
     //else break;
     }
    }while((!Ok)&&(Counter<10));
    EndPoints[i]=EndPoint;
    }
   for (unsigned int i=0;i<Array.Size;i++)
    {
    Printer()->Canvas->TextOut(DLeft+ListWidth-ForCaption+2*ScaleX,EndPoints[i]-5*ScaleY,
    defPointerToSignals[Array.Array[i]]->Name);
    }
   //Main Caption
   Printer()->Canvas->Font->Size=16;
   AnsiString Capt="Параметры "+TabControl->Tabs->Strings[TabIndex]+" с ";
   Capt+=SelectMinDate.DateString();Capt+=" по ";Capt+=SelectMaxDate.DateString();
   Printer()->Canvas->TextOut(ListWidth/3.5+DLeft,DTop-DPI/5,Capt);
   //delete []EndPoints;
   Printer()->EndDoc();

   }//End for TabIndex
   }
else {MainForm->DataBaseTimer->Enabled=MainForm->EnablSaveData;return;}
MainForm->DataBaseTimer->Enabled=MainForm->EnablSaveData;
}
//---------------------------------------------------------------------------
void TGraphForm::FillAxisArray(TArrayPointer &Array,TArrayPointer &Axis)
{
if((Axis.Array)&&(Axis.Size)){delete []Axis.Array;Axis.Size=0;}
int Axis1[maxgraph];for(unsigned short i=0;i<maxgraph;i++)Axis1[i]=-1;
   for(unsigned short i=0;i<Array.Size;i++)
    {
    bool Present=false;
    for(unsigned short j=0;j<maxgraph;j++)       //DataModule1->Signal
     {
     if((Axis1[j]!=-1)&&(defPointerToSignals[Array.Array[i]]->EdIzm==
     defPointerToSignals[Axis1[j]]->EdIzm)&&(defPointerToSignals[Array.Array[i]]->Limits.Max==
     defPointerToSignals[Axis1[j]]->Limits.Max)&&(defPointerToSignals[Array.Array[i]]->Limits.Min==
     defPointerToSignals[Axis1[j]]->Limits.Min)) Present=true;
     }
    if(!Present)
     {
     unsigned short j=0;
     while((Axis1[j]!=-1)&&(j<maxgraph))j++;
     Axis1[j]=Array.Array[i];
     }
    }
   {
   unsigned int MaxElem=0;
   while((Axis1[MaxElem]!=-1)&&(MaxElem<maxgraph))MaxElem++;
   Axis.Array=new short[MaxElem];
   Axis.Size=MaxElem;
   for(unsigned int i=0;i<MaxElem;i++)Axis.Array[i]=Axis1[i];
   }
}
//---------------------------------------------------------------------------
void TGraphForm::PaintGird(const TRect* Rect,TCanvas* Canv,TArrayPointer* Array,int BetweenAxis,int StepXP,
               int StepYP,int RealWidth)
{
//Рисование осей
int ParamAmount=Array->Size;
int DLeft=Rect->Left;                                     //AnsiString
int DTop=Rect->Top;
int ListHeight=Rect->Bottom-Rect->Top;
int ListWidth=Rect->Right-Rect->Left;
int ScaleX=StepXP/StepX,ScaleY=StepYP/StepY;
Canv->Pen->Width=AxisWidth;
Canv->Pen->Style=psSolid;
Canv->Pen->Color=clBlack;
Canv->Brush->Color=clBlack;
short int ArrowBase=DPI/18;
short int ArrowLength=DPI/6;
int IntPartScale=5;
int FloatPartScale=2;
//Vert
for(int i=1;i<(ParamAmount+1);i++)
{
TPoint ArrowPoint[3];
ArrowPoint[0]=Point(DLeft+DPI/5+BetweenAxis*i,DTop);
ArrowPoint[1]=Point(DLeft+DPI/5+BetweenAxis*i+ArrowBase/2,DTop+ArrowLength);
ArrowPoint[2]=Point(DLeft+DPI/5+BetweenAxis*i-ArrowBase/2,DTop+ArrowLength);
Canv->MoveTo(DLeft+DPI/5+BetweenAxis*i,DTop);//DPI/5=0.5*DPI/2.54
Canv->LineTo(DLeft+DPI/5+BetweenAxis*i,ListHeight+DTop);
Canv->Polygon(ArrowPoint,2);
}
//Horz
{
TPoint ArrowPoint[3];
ArrowPoint[0]=Point(ListWidth+DLeft,ListHeight+DTop-DPI/5);
ArrowPoint[1]=Point(ListWidth+DLeft-ArrowLength,ListHeight+DTop-DPI/5-ArrowBase/2);
ArrowPoint[2]=Point(ListWidth+DLeft-ArrowLength,ListHeight+DTop-DPI/5+ArrowBase/2);
Printer()->Canvas->MoveTo(DLeft,ListHeight+DTop-DPI/5);
Printer()->Canvas->LineTo(ListWidth+DLeft,ListHeight+DTop-DPI/5);
Printer()->Canvas->Polygon(ArrowPoint,2);
}
Printer()->Canvas->Brush->Color=clWhite;
 //Рисование сетки
Printer()->Canvas->Pen->Width=GirdWidth;
Printer()->Canvas->Pen->Style=psSolid;
Printer()->Canvas->Pen->Color=clBlack;//Gray;
Printer()->Canvas->Font->Size=printnumfontsize;
//Vert
for(int i=DLeft+DPI/5+ParamAmount*BetweenAxis+StepXP;i<ListWidth+DLeft;i=i+StepXP)
  {
  Printer()->Canvas->MoveTo(i,DTop);
  Printer()->Canvas->LineTo(i,ListHeight+DTop-DPI/5);
  }
//Horz
for(int j=ListHeight+DTop-StepYP-DPI/5;j>DTop;j=j-StepYP)
  {
  Printer()->Canvas->MoveTo(DLeft+DPI/5,j);
  Printer()->Canvas->LineTo(ListWidth+DLeft,j);
  }
Printer()->Canvas->Pen->Width=GraphWidth;
DataModule1->StatistTable->First();
//
//int Ho,Mi,Sec;
Printer()->Canvas->Pen->Color=clBlack;
TDateTime dTime=double(StepXP)*double(SelectMaxDate-SelectMinDate+1)/double(ListWidth-ParamAmount*BetweenAxis-DPI/5);
for(int i=1;i<(ListWidth-ParamAmount*BetweenAxis-DPI/5)/StepXP;i+=2)
 {
 //Out Date Scales
 if(int(SelectMaxDate)-int(SelectMinDate))
  {
  Printer()->Canvas->TextOut(DLeft+i*StepXP+ParamAmount*BetweenAxis-9*ScaleX,ListHeight+DTop-49*ScaleY,
  TDateTime(double(dTime)*i+double(SelectMinDate)).DateString());
  }
 //Out Time Scales
 Printer()->Canvas->TextOut(DLeft+i*StepXP+ParamAmount*BetweenAxis-7*ScaleX,ListHeight+DTop-15*ScaleY,
 TDateTime(double(dTime)*i+double(SelectMinDate)).TimeString());
 }
//const unsigned int NumberOfSignals=5;
//unsigned int NumberInArray[NumberOfSignals]={16,17,18,19,20};
for(unsigned int k=0;k<Array->Size;k++)
 if(defPointerToSignals[Array->Array[k]])
 {
 int i=Array->Array[k],pos=k;
// else break;
 float max=1;
 //for(int n=0;n<maxadam;n++)
 //for(int j=0;j<maxchannel;j++)
  //if(MainForm->Number[n][j]==i)
  //{
  Printer()->Canvas->TextOut(DLeft+DPI/5+pos*BetweenAxis+12*ScaleX,DTop/*+0.1*DPI*/,
  defPointerToSignals[i]->EdIzm);
  max=(fabs(defPointerToSignals[i]->Limits.Min)<fabs(defPointerToSignals[i]->Limits.Max))?
    fabs(defPointerToSignals[i]->Limits.Max):fabs(defPointerToSignals[i]->Limits.Min);
  //}
 Printer()->Canvas->Font->Color=clBlack;
 if((defPointerToSignals[i])&&(defPointerToSignals[i]->Limits.Min>=0))
  {
  for(int j=1;j<(ListHeight-DPI/5)/StepYP;j++)
   {
   Printer()->Canvas->TextOut(DLeft+DPI/5+pos*BetweenAxis+12*ScaleX,ListHeight+DTop-DPI/5-
   15*ScaleY-j*StepYP,FloatToStrF(max/(ListHeight-DPI/5)*j*StepYP,ffFixed,IntPartScale,FloatPartScale));
   }
  }
 else
  {
  for(int j=1;j<(ListHeight-DPI/5)/StepYP;j++)
   {
   Printer()->Canvas->TextOut(DLeft+DPI/5+pos*BetweenAxis+12*ScaleX,ListHeight+DTop-DPI/5-
   15*ScaleY-j*StepYP,FloatToStrF(-max+float(max*2)/float(ListHeight-DPI/5)*float(j)*float(StepYP),ffFixed,IntPartScale,FloatPartScale));
   }
  }
 }
}
//---------------------------------------------------------------------------
void TGraphForm::PaintGraphI(const TRect* Rect,TCanvas* Canv,unsigned int Numb,TColor Color,int& EndPoint)
{
if(!defPointerToSignals[Numb])return;
MainForm->Paused=true;
TTable* Table=DataModule1->StatistTable;
/*if(StandartSButton->Down)
 {
 Table=DataModule1->StatistTable;
 }
else
 {//Select Alarm
 Table=DataModule1->AlarmTable;
 }*/
//----}
if((Numb==-1)||(!defPointerToSignals[Numb]))return;
int w=Rect->Right-Rect->Left;
int h=Rect->Bottom-Rect->Top;
float MaxVal=(fabs(defPointerToSignals[Numb]->Limits.Min)<fabs(defPointerToSignals[Numb]->Limits.Max))?
    fabs(defPointerToSignals[Numb]->Limits.Max):fabs(defPointerToSignals[Numb]->Limits.Min);
 if((defPointerToSignals[Numb]->Type==stInp)||(defPointerToSignals[Numb]->Type==stOut)||
 ((defPointerToSignals[Numb]->Type==stCalc)&&(defPointerToSignals[Numb]->SaveData)))
   {
    DataModule1->StatistTable->First();
    if(!AllBlack)Printer()->Canvas->Pen->Color=Color;
    else Printer()->Canvas->Pen->Color=clBlack;
    DataModule1->StatistTable->Filter="(Numb='"+IntToStr(Numb)+"')and"+DateFilter;
    DataModule1->StatistTable->Filtered=true;
       //DataModule1->StatistTable->FieldCount
    TDateTime date1,CurDB;
    short Ho,Mi,Sec;
    Ho=DataModule1->StatistTable->FieldByName("Hours")->AsInteger;
    Mi=DataModule1->StatistTable->FieldByName("Minuts")->AsInteger;
    Sec=DataModule1->StatistTable->FieldByName("Seconds")->AsInteger;
    int x1=Rect->Left,y1=Rect->Bottom;
    TDateTime time3(Ho,Mi,Sec,0);
    x1=Rect->Left/*DPI/5*/+int(double(time3+DataModule1->StatistTable->FieldByName("Date")->AsDateTime-
    SelectMinDate)*w/(SelectMaxDate-SelectMinDate+1));
    if(defPointerToSignals[Numb]->Limits.Min>=0)
     y1=Rect->Bottom-DataModule1->StatistTable->FieldByName("Value")->AsFloat*float(h)/MaxVal;
    else
     y1=h/2+Rect->Top-DataModule1->StatistTable->FieldByName("Value")->AsFloat*float(h)/MaxVal/2.0;
    //int RealMax
    while(!DataModule1->StatistTable->Eof)
      {
      date1=DataModule1->StatistTable->FieldByName("Date")->AsDateTime;
      Ho=DataModule1->StatistTable->FieldByName("Hours")->AsInteger;
      Mi=DataModule1->StatistTable->FieldByName("Minuts")->AsInteger;
      Sec=DataModule1->StatistTable->FieldByName("Seconds")->AsInteger;
      TDateTime time1(Ho,Mi,Sec,0);
      CurDB=date1+time1;
      int x=Rect->Left+int(double(CurDB-SelectMinDate)*(w)/(SelectMaxDate-SelectMinDate+1));
      int y;
      if(defPointerToSignals[Numb]->Limits.Min>=0)
       y=Rect->Bottom-DataModule1->StatistTable->FieldByName("Value")->AsFloat*float(h)/MaxVal;
      else
       y=h/2+Rect->Top-DataModule1->StatistTable->FieldByName("Value")->AsFloat*float(h)/MaxVal/2.0;
      if(((x-x1)>=0)&&((x-x1)<(w*0.8/24)))
       {
       Canv->MoveTo(x1,y1);
       Canv->LineTo(x,y);//=GraphColor[i];
       }
      else
       {
       if(!AllBlack)
        {
        Canv->Pixels[x][y]=Color;
        Canv->Pixels[x1][y1]=Color;
        }
       else
        {
        Canv->Pixels[x][y]=clBlack;
        Canv->Pixels[x1][y1]=clBlack;
        }
       }
      DataModule1->StatistTable->Next();
      x1=x;y1=y;
      }//end while
    EndPoint=y1;
    //Canvas->Font->Size=7;
    //if(!AllBlack)Printer()->Canvas->Font->Color=GraphColor[i];
    //else Printer()->Canvas->Font->Color=clBlack;
    DataModule1->StatistTable->Filtered=false;
   }
  else if((defPointerToSignals[Numb]->Type==stCalc)/*&&(defPointerToSignals[Numb]->InpType[0]!=itIntPtoc)*/)
   {
   TFloatArrayPointer PromArray[numbofsignal];
   float Maxes[numbofsignal];
   TInpType InpType[numbofsignal];
   float InpSignal[numbofsignal];
   TActionType Action[numbofsignal-1];
   unsigned short j;
   if(defPointerToSignals[Numb]->InpType[0]!=itIntPtoc) j=0;
   else j=1;
   for(/*unsigned short j=0*/;j<numbofsignal;j++)
    {
    InpSignal[j]=defPointerToSignals[Numb]->InpSignal[j];
    InpType[j]=defPointerToSignals[Numb]->InpType[j];
    if(j<numbofsignal-1)Action[j]=defPointerToSignals[Numb]->Action[j];
    if((InpType[j]!=itNotDefine)&&(InpType[j]!=itFloat))
     {
     Maxes[j]=defPointerToSignals[(unsigned short)(defPointerToSignals[Numb]->InpSignal[j])]->Limits.Max;
     if(PromArray[j].Array){delete []PromArray[j].Array;PromArray[j].Array=0;}
     PromArray[j].Array=new float[w+3];
     PromArray[j].Size=w;
     PromArray[j].Max=defPointerToSignals[Numb]->Limits.Max;
     if(!PromArray[j].Max)PromArray[j].Max=1;
     FillArray(&(PromArray[j]),Table,(unsigned short)(defPointerToSignals[Numb]->InpSignal[j]));
     }
    }
   //-----
   if(defPointerToSignals[Numb]->InpType[0]==itNotDefine)return;
   //TPoint Current,Previous;
   //Previous.x=Rect->Left;//Rect->Left+/*DPI/5*/+double(time3+DataModule1->StatistTable->FieldByName("Date")->AsDateTime-SelectMinDate)*(RealWidth)/(SelectMaxDate-SelectMinDate+1);
   //Previous.y=Rect->Bottom;
   TArrayPointer Array;Array.Size=w+3;Array.Array=new short[Array.Size];
   unsigned int Limit=PromArray[0].Size;
   for(unsigned short j=1;j<numbofsignal;j++)if(Limit<PromArray[j].Size)Limit=PromArray[j].Size;
   for(unsigned int j=0;j<Limit;j++)
    {
    float OutVal;
    if(defPointerToSignals[Numb]->InpType[0]!=itIntPtoc)
    {
    if(InpType[0]==itFloat)OutVal=InpSignal[j];
    else OutVal=PromArray[0].Array[j];
    for(unsigned int k=0;((k<numbofsignal-1)&&(Action[k]!=atNotDefine));k++)     //DataModule1->Signal
     {
     if (InpType[k+1]!=itFloat)
      {
      Act(OutVal,PromArray[k+1].Array[j],Action[k]);
      }
     else Act(OutVal,InpSignal[k+1],Action[k]);
     }
    }//end !IntProc
    else
    {
    OutVal=defGetIntProc((unsigned  short)(defPointerToSignals[Numb]->InpSignal[0]),PromArray[1].Array[j],PromArray[2].Array[j]);
    }
    if(defPointerToSignals[Numb]->Limits.Min>=0)
     Array.Array[j]=Rect->Bottom-(OutVal*defPointerToSignals[Numb]->Scale+defPointerToSignals[Numb]->OffSet)
     *h/MaxVal;
    else
     Array.Array[j]=h/2+Rect->Top-(OutVal*defPointerToSignals[Numb]->Scale+defPointerToSignals[Numb]->OffSet)
     *float(h)/MaxVal/2.0;
     //Array.Array[j]=Rect->Bottom-(OutVal*defPointerToSignals[Numb]->Scale+defPointerToSignals[Numb]->OffSet)
     //*h/MaxVal;
    }
    for(unsigned int i=0;i<numbofsignal;i++)if(PromArray[i].Array){delete PromArray[i].Array;PromArray[i].Array=0;}
    unsigned int LastPointIndex=0;
    for(unsigned int i=0;i<Array.Size-1;i++)
     {
     int Delta,PrevDelta=Array.Array[i+1]-Array.Array[i];
     unsigned int LastI=i;
     do
      {
      Delta=Array.Array[i+1]-Array.Array[i];
      i++;
      }
     while((Delta==PrevDelta)&&(i<Array.Size));
     i--;
     if((Array.Array[LastI]!=Rect->Bottom)&&(Array.Array[i]!=Rect->Bottom)&&(Array.Array[i])&&
     (Array.Array[LastI]>0)&&(Array.Array[i]>0))
      {
      Canv->MoveTo(Rect->Left+LastI,Array.Array[LastI]);
      Canv->LineTo(Rect->Left+i,Array.Array[i]);
      LastPointIndex=i;
      }
     if(i>LastI)i--;
     }
    EndPoint=Array.Array[LastPointIndex];
   //---------------
   }

 //}//end (for i,if)
DataModule1->StatistTable->Filtered=false;
DataModule1->StatistTable->Last();
MainForm->Paused=false;
}
//---------------------------------------------------------------------------
void __fastcall TGraphForm::UpDown1Click(TObject *Sender,
      TUDBtnType Button)
{
TDateTime Dat1=MaskEdit1->Text;//min
TDateTime Dat2=MaskEdit->Text;//max
if(Button==0)
 {
 if((Dat1+1>Date())||(Dat1+1>Dat2))return;
 else
  {
  Dat1+=1;
  MaskEdit1->Text=Dat1;
  }
 }
else
 {
 Dat1-=1;
 MaskEdit1->Text=Dat1;
 }//*/
}
//---------------------------------------------------------------------------
void __fastcall TGraphForm::UpDown2Click(TObject *Sender,
      TUDBtnType Button)
{
TDateTime Dat1=MaskEdit1->Text;//min
TDateTime Dat2=MaskEdit->Text;//max
if(Button==0)
 {
 if((Dat2+1)>Date())return;
 else
  {
  Dat2+=1;
  MaskEdit->Text=Dat2;
  }
 }
else
 {
 if(Dat2-1<Dat1)return;
 else
  {
  Dat2-=1;
  MaskEdit->Text=Dat2;
  }
 }//*/
}
//---------------------------------------------------------------------------





void __fastcall TGraphForm::DeleteGroupItemClick(TObject *Sender)
{
if(Application->MessageBox("Вы действительно хотите удалить группу", "Сообщение", MB_OKCANCEL +
    MB_ICONQUESTION)==IDCANCEL)return;
unsigned short TabIndex=TabControl->TabIndex;
unsigned short TabCount=TabControl->Tabs->Count;
for(unsigned short i=TabIndex;i<TabCount-1;i++)
 {
 TabControl->Tabs->Strings[i]=TabControl->Tabs->Strings[i+1];
 for(unsigned short j=0;j<maxgraph;j++)
  {
  Graphics[i][j]=Graphics[i+1][j];
  }
 }
TabControl->Tabs->Delete(TabCount-1);
TabControl->TabIndex=TabIndex-1;
SettingsChanged=true;
InitialPoints();
PaintBox->Invalidate();
PaintBox1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TGraphForm::AddGroupItemClick(TObject *Sender)
{
if(TabControl->Tabs->Count>=maxgraphgroup)
 {
 AnsiString Mes="Максимум "+IntToStr(maxgraphgroup)+" групп";
 Application->MessageBox(Mes.c_str(), "Сообщение", MB_OK + MB_ICONWARNING);
 return;
 }
AnsiString Name="";
if(GetName(this,Name))
 {
 SettingsChanged=true;
 TabControl->Tabs->Add(Name);
 }
}
//---------------------------------------------------------------------------

void __fastcall TGraphForm::RenameGroupItemClick(TObject *Sender)
{
AnsiString Name="";
if(GetName(this,Name))
{
SettingsChanged=true;
TabControl->Tabs->Strings[TabControl->TabIndex]=Name;
}
}
//---------------------------------------------------------------------------

void __fastcall TGraphForm::TabControlChange(TObject *Sender)
{
 PaintBox->Width=TrackBar->Position;
 SelectMinDate=MaskEdit1->Text;
 SelectMaxDate=MaskEdit->Text;
 //SelectMaxDate=SelectMinDate;
 if(SelectMinDate>SelectMaxDate)
  {
  SelectMaxDate=SelectMinDate;
  MaskEdit->Text=MaskEdit1->Text;
  }
 DateFilter="(Date>='"+SelectMinDate.DateString()+"')and(Date<='"+SelectMaxDate.DateString()+"')";/*and(Date<='"+
 SelectMaxDate.DateString()+"')";                        */
 InitialPoints();
 //DataModule1->StatistTable->Filtered=true;
 PaintBox->Refresh();
 PaintBox1->Invalidate();
 //ScrollBox->Refresh();{
}
//---------------------------------------------------------------------------


