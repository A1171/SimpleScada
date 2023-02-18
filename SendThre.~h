//---------------------------------------------------------------------------
#ifndef SendThreH
#define SendThreH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//#include "SetStat.h"
//---------------------------------------------------------------------------
class TSendThread : public TThread
{
private:
TTable* FTable;
Variant FCells;
AnsiString FDateFilter;
AnsiString FParamFilter;
AnsiString FParamName;
unsigned int Counter1;
protected:
        void __fastcall Execute();
        void __fastcall Send();
        void __fastcall SendCaption();
public:
        __fastcall TSendThread(bool CreateSuspended);
        __fastcall TSendThread(TTable*,AnsiString,AnsiString,AnsiString,bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
