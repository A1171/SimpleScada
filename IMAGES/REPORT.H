//---------------------------------------------------------------------------
#ifndef ReportH
#define ReportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TReportForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *QuickReport;
        TQRBand *HeaderBand;
        TQRSysData *QRSysData1;
        TQRSysData *QRSysData2;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRSysData *QRSysData3;
        TQRBand *Band;
        TQRBand *QRBand1;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        TQRLabel *QRLabel6;
        TQRLabel *QRLabel7;
        TQRLabel *QRLabel8;
        TQRDBText *QRDBText1;
        TQRDBText *QRDBText2;
        TQRDBText *QRDBText3;
        TQRDBText *QRDBText4;
        TQRDBText *QRDBText5;
        TQRDBText *QRDBText6;
        TQRLabel *QRLabel9;
        TQRDBText *QRDBText7;
        TQRBand *QRBand2;
        TQRSysData *QRSysData4;
private:	// User declarations
public:		// User declarations
        __fastcall TReportForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReportForm *ReportForm;
//---------------------------------------------------------------------------
#endif
