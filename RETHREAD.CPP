//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ReThread.h"
#include "Function.h"
#include "MainUnut.h"
#include "DataUnit.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TRefreshThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TRefreshThread::TRefreshThread(bool CreateSuspended)
        : TThread(CreateSuspended)
{

Priority=tpLowest;
FreeOnTerminate=true;

}
//---------------------------------------------------------------------------
void __fastcall TRefreshThread::Execute()
{
try
{
Synchronize(CopyReserv);
Synchronize(RefreshStat1);
Synchronize(RefreshAlarm1);
MainForm->DataBaseTimer->Enabled=true;
}
catch(...)
{
MainForm->DataBaseTimer->Enabled=true;
}
Terminate();
        //---- Place thread code here ----
}
//---------------------------------------------------------------------------
void __fastcall TRefreshThread::CopyReserv()
{
DataModule1->StatistTable->IndexName="";
DataModule1->ReservStatTable->IndexName="";
CopyToReserve();
}
//---------------------------------------------------------------------------
void __fastcall TRefreshThread::RefreshStat1()
{
RefreshStat();
}
//---------------------------------------------------------------------------
void __fastcall TRefreshThread::RefreshAlarm1()
{
RefreshAlarm();
MainForm->StatusBar->SimplePanel=false;
}