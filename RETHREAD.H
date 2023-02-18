//---------------------------------------------------------------------------
#ifndef ReThreadH
#define ReThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TRefreshThread : public TThread
{
private:
void __fastcall CopyReserv();
void __fastcall RefreshStat1();
void __fastcall RefreshAlarm1();
protected:
        void __fastcall Execute();
public:
        __fastcall TRefreshThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
