//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Report.h"
#include "DataUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TReportForm *ReportForm;
//---------------------------------------------------------------------------
__fastcall TReportForm::TReportForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
