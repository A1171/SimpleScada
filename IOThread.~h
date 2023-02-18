//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*#ifndef maxadam
#define maxadam 10
#endif
#ifndef maxchannel
#define maxchannel 8
#endif
#ifndef maxgroup
#define maxgroup 50
#endif*/

//---------------------------------------------------------------------------

#ifndef IOThreadH
#define IOThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "Constant.h"
//---------------------------------------------------------------------------
class TAdConnThread : public TDataModule
{
__published:	// IDE-managed Components
        TTimer *COM1Timer;
        TTimer *COM2Timer;
        TTimer *COM3Timer;
        void __fastcall COM1TimerTimer(TObject *Sender);
        void __fastcall AdConnThreadDestroy(TObject *Sender);
private:	// User declarations
short Counter[maxadam];
char *PComName;
//int Counter;
unsigned char Message[4];
//unsigned char *PMessage;
unsigned char Respond[15];
//unsigned char *PRespond;
unsigned long BytesWritten,BytesReaden,Errors;
enum{BytesToRead=7,BytesToWrite=3};
TDCB DCB;
COMSTAT Stat[maxadam];
_COMMTIMEOUTS TimeOutSt;
bool FSuspended;
void __fastcall SetSuspended(bool);

public:		// User declarations
        __fastcall TAdConnThread(TComponent* Owner);
struct TCommErrorInfo
 {
 bool Error;
 bool FailsPorts[maxadam];
 bool Fails[maxadam][maxchannel];
 char FailsCounter[maxadam][maxchannel];
 TCommErrorInfo()
   {Error=0;
   ZeroMemory(Fails,sizeof(Fails));
   ZeroMemory(FailsPorts,sizeof(FailsPorts));
   ZeroMemory(FailsCounter,sizeof(FailsCounter));}
 } CommErrorInfo;
void Terminate();
HANDLE PortHandle[maxadam];
char ComName[maxadam][6];
__published:
__property bool Suspended={read=FSuspended,write=SetSuspended,default=false};
};
//---------------------------------------------------------------------------
extern PACKAGE TAdConnThread *AdConnThread;
//---------------------------------------------------------------------------
#endif
