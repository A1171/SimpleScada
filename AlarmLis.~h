//---------------------------------------------------------------------------
#ifndef AlarmLisH
#define AlarmLisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include "MainUnut.h"
//---------------------------------------------------------------------------
class TAlarmListForm : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *AlarmGrid;
        TTimer *Timer1;
        TLabel *Label1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall AlarmGridMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
private:
struct TConnectCell
{
unsigned int Signal;
bool Present;
};	// User declarations
TConnectCell ConnectCell[maxsignal];
public:		// User declarations
        __fastcall TAlarmListForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAlarmListForm *AlarmListForm;
//---------------------------------------------------------------------------
#endif
