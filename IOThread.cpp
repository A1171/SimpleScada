//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "IOThread.h"
#include "MainUnut.h"
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAdConnThread *AdConnThread;
//---------------------------------------------------------------------------
__fastcall TAdConnThread::TAdConnThread(TComponent* Owner)
        : TDataModule(Owner)
{
ZeroMemory(Counter,sizeof(Counter[0])*maxadam);
TIniFile *IniFile;
IniFile=new TIniFile(MainForm->ProgramDir+"\\SetAdres.ini");
//Connect
for(int i=0;i<maxadam;i++)
 {
 ComName[i][0]='C';
 ComName[i][1]='O';
 ComName[i][2]='M';
 ComName[i][3]=IniFile->ReadInteger("Port",IntToStr(i)+"Port1",'3');
 ComName[i][4]=IniFile->ReadInteger("Port",IntToStr(i)+"Port2",0);
 ComName[i][5]=0;
 }
delete IniFile;//*/
AnsiString ErrorMessage;
for(int i=0;i<maxadam;i++)
 {
 PComName=ComName[i];
 PortHandle[i]=CreateFile(PComName,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,
 FILE_ATTRIBUTE_NORMAL,NULL);
 if(PortHandle[i]==INVALID_HANDLE_VALUE)
  {
  ErrorMessage+=" ";
  for(int j=0;j<6;j++)if(ComName[i][j])ErrorMessage+=ComName[i][j];
  }
 }//*/
//Bug
#ifdef Bugswitchedon
{
 TDateTime MaxDate=maxworkday;
 TDateTime Now=Date();
 if(Now>MaxDate)
  {
  ShowMessage("???? ?? ?????? ??? ???? ????????? ???? ?? ???? ??????? ?? ?? ????????? ?????? ?? ????????? ??? ? ????? ?????? ?????. ???? ?????? ????????? ????????? ? ????? ? ?????? ? ??? ??????, ? ???? ??? ?? ?????????.");
  MainForm->Close();
  }
}
#endif//*/
if(ErrorMessage!="")
 {
 AnsiString ErrMes="?????????? ??????? ???? "+ErrorMessage+
 ". ?????? ? ?????? ?????? ????????? ?? ?????.";
 //ErrMes=;
 //ErrMes=;
 char a[200];
 ZeroMemory(a,200);
 strcpy(a,ErrMes.c_str());
 Application->MessageBox(a,"?????? ?????????????",MB_OK|MB_ICONWARNING);
 }
/*ComName[0]='C';
ComName[1]='O';
ComName[2]='M';
ComName[3]='3';
ComName[4]=0;
PComName=ComName;
PortHandle[1]=CreateFile(PComName,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,
FILE_ATTRIBUTE_NORMAL,NULL);

ComName[0]='C';
ComName[1]='O';
ComName[2]='M';
ComName[3]='4';
ComName[4]=0;
PComName=ComName;
PortHandle[2]=CreateFile(PComName,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,
FILE_ATTRIBUTE_NORMAL,NULL);

//int c=GetLastError();*/

 DCB.BaudRate=1200;
 DCB.ByteSize=8;
 DCB.Parity=NOPARITY;
 DCB.StopBits=ONESTOPBIT;
 TimeOutSt.ReadIntervalTimeout=300;
 TimeOutSt.ReadTotalTimeoutMultiplier=50;
 TimeOutSt.ReadTotalTimeoutConstant=50;
 TimeOutSt.WriteTotalTimeoutMultiplier=50;
 TimeOutSt.WriteTotalTimeoutConstant=50;
for(int i=0;i<maxadam;i++)
 {
 SetupComm(PortHandle[i],20,20);
 //c=GetLastError();
 //DCBState=new TDCB;
 SetCommState(PortHandle[i],&DCB);
 SetCommTimeouts(PortHandle[i],&TimeOutSt);
 EscapeCommFunction(PortHandle[i],CLRRTS);
 Pause(1);
 EscapeCommFunction(PortHandle[i],SETRTS);
 }//*/
//Counter1=0;Counter2=0;Counter3=0;
Message[0]=0x46;
Message[1]=0xE3;
Message[2]=0x02;
Message[3]=0;
Suspended=false;
#ifdef Debug
Suspended=true;
#endif
}
//---------------------------------------------------------------------------
void __fastcall TAdConnThread::SetSuspended(bool Sus)
{
COM1Timer->Enabled=!Sus;
COM2Timer->Enabled=!Sus;
COM3Timer->Enabled=!Sus;
FSuspended=Sus;
}
//----------------------------------------------------------------------------
void TAdConnThread::Terminate()
{
for(int i=0;i<maxadam;i++)
 {
 CloseHandle(PortHandle[i]);
 }
delete this;
}
//----------------------------------------------------------------------------
void __fastcall TAdConnThread::COM1TimerTimer(TObject *Sender)
{
//return;
DataModule1->CurDateTime=DataModule1->CurDateTime.CurrentDateTime();
unsigned long ButesNumb=3;
//PMessage=Message;
for(int i=0;i<maxadam;i++)
 {
 unsigned int CurrentNumb=defExtDev[i][0][Counter[i]];
 if((!CheckMax(CurrentNumb))&&(CurrentNumb<maxsignal)&&(defPointerToSignals[CurrentNumb])&&
 (defSingleDevice[i])&&(PortHandle[i]!=INVALID_HANDLE_VALUE))
  {
  ClearCommError(PortHandle[i],&Errors,&Stat[i]);
  if(Stat[i].cbInQue>0)
  ReadFile(PortHandle[i],Respond,Stat[i].cbInQue,&BytesReaden,NULL);
  /*for(int j=0;j<15;j++)*/ZeroMemory(Respond,sizeof(Respond[0])*15);
  WriteFile(PortHandle[i],Message,BytesToWrite,&BytesWritten,NULL);
  ClearCommError(PortHandle[i],&Errors,&Stat[i]);
  ButesNumb=BytesToRead;
  if(Stat[i].cbInQue>=BytesToRead) ButesNumb=Stat[i].cbInQue;
  ReadFile(PortHandle[i],Respond,ButesNumb,&BytesReaden,NULL);
  if(BytesReaden<7)
   {
   ClearCommError(PortHandle[i],&Errors,&Stat[i]);
   if(Stat[i].cbInQue>0)ReadFile(PortHandle[i],Respond,Stat[i].cbInQue,&BytesReaden,NULL);
   //ButesNumb=3;
   WriteFile(PortHandle[i],Message,BytesToWrite,&BytesWritten,NULL);
   ClearCommError(PortHandle[i],&Errors,&Stat[i]);
   //ButesNumb=7;
   ButesNumb=BytesToRead;
   if(Stat[i].cbInQue>ButesNumb) ButesNumb=Stat[i].cbInQue;
   ReadFile(PortHandle[i],Respond,ButesNumb,&BytesReaden,NULL);
   }
  //Edits[Counter1]->Text="";
  //Edit9->Text=IntToStr(Counter1);
  if(BytesReaden>=7)
   {
   unsigned short Val=(Respond[4]*256+Respond[3]);
   float Val1;
   if(Respond[4]&0X80){Val-=1;Val=~Val;Val1=-float(Val);}
   else Val1=float(Val);
   defPointerToSignals[CurrentNumb]->InpValue=Val1;//float(Respond[4]*256+Respond[3]);
   //MainForm->Signal[i][Counter[i]]=float(Respond[4]*256+Respond[3])*
   //MainForm->Scales[i][Counter[i]]-MainForm->OffSet[i][Counter[i]];    //isp
   //----{reset fail
   CommErrorInfo.FailsCounter[i][Counter[i]]=0;
   CommErrorInfo.Fails[i][Counter[i]]=0;
   //----}
   }
  else
   {//----{SetFail
   if(CommErrorInfo.FailsCounter[i][Counter[i]]<maxconnfail)
    {
    CommErrorInfo.FailsCounter[i][Counter[i]]++;
    //MainForm->Signal[1][Counter1]=0;    //isp
    }
   else
    {
    CommErrorInfo.Error=true;
    CommErrorInfo.FailsPorts[i]=true;
    CommErrorInfo.Fails[i][Counter[i]]=true;
    }
   if(CommErrorInfo.Fails[i][Counter[i]])
    defPointerToSignals[defExtDev[i][0][Counter[i]]]->InpValue=0;//MainForm->Signal[i][Counter[i]]=0;
   }//----}
  }//End if presentparam
 if(Counter[i]>=maxchannel-1)
  {
  EscapeCommFunction(PortHandle[i],CLRRTS);
  Pause(5);
  //MainForm->Refresh();
  EscapeCommFunction(PortHandle[i],SETRTS);
  Counter[i]=0;
  //check failport one times in cycle for each port
  ZeroMemory(CommErrorInfo.FailsPorts,sizeof(CommErrorInfo.FailsPorts));
  for(int n=0;n<maxadam;n++)
   for(int j=0;j<maxchannel;j++)
    {
  //  if(!CheckMax(defExtDev[n][0][j]))
  //  if(defPointerToSignals[defExtDev[n][0][j]])
  //  if(/*(defExtDev[n][0][j]!=-1)&&(defPointerToSignals[defExtDev[n][0][j]])&&*/
  //  (defPointerToSignals[defExtDev[n][0][j]]->Type==stInp)&&(defSingleDevice[n]))
  //   {
  //   CommErrorInfo.Fails[n][j]=false;
  //   CommErrorInfo.FailsCounter[n][j]=0;
  //   }
    if(!CheckMax(defExtDev[n][0][j]))
    if(defPointerToSignals[defExtDev[n][0][j]])
    if(/*(defExtDev[n][0][j]!=-1)&&(defPointerToSignals[defExtDev[n][0][j]])&&*/(CommErrorInfo.Fails[n][j])&&
    (defPointerToSignals[defExtDev[n][0][j]]->Type==stInp)&&(defSingleDevice[n]))
     CommErrorInfo.FailsPorts[n]=true;
    }
  CommErrorInfo.Error=false;
  for(int j=0;j<maxadam;j++)
   if(CommErrorInfo.FailsPorts[j])CommErrorInfo.Error=true;
  }
 else
  {
  EscapeCommFunction(PortHandle[i],CLRDTR);
  Pause(1);
  EscapeCommFunction(PortHandle[i],SETDTR);
  Counter[i]++;
  }
 }//End For
}
//---------------------------------------------------------------------------

void __fastcall TAdConnThread::AdConnThreadDestroy(TObject *Sender)
{
TIniFile *IniFile;
IniFile=new TIniFile(MainForm->ProgramDir+"\\SetAdres.ini");
for(int i=0;i<maxadam;i++)
 {
 if((ComName[i][3]>=48)&&(ComName[i][3]<=57)&&(ComName[i][4]==0))
 {
 IniFile->WriteInteger("Port",IntToStr(i)+"Port1",ComName[i][3]);
  IniFile->WriteInteger("Port",IntToStr(i)+"Port2",0);
 }
 if((ComName[i][3]>=48)&&(ComName[i][3]<=57)&&(ComName[i][4]>=48)&&(ComName[i][4]<=57))
 {
 IniFile->WriteInteger("Port",IntToStr(i)+"Port1",ComName[i][3]);
 IniFile->WriteInteger("Port",IntToStr(i)+"Port2",ComName[i][4]);
 }
 /*if(((AnsiString(Adres[i][0])+AnsiString(Adres[i][1]))!="")&&
 (Adres[i][0]!='n')&&(Adres[i][1]!='n'))
  IniFile->WriteString("Adres","Adam"+IntToStr(i),AnsiString(Adres[i][0])+AnsiString(Adres[i][1]));*/
 }
delete IniFile;//*/
}
//---------------------------------------------------------------------------



