//---------------------------------------------------------------------------
#ifndef ReportFoH
#define ReportFoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TRepForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *QuickRep;
        TQRBand *QRBand2;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        TQRLabel *QRLabel6;
        TQRLabel *QRLabel7;
        TQRLabel *QRLabel8;
        TQRLabel *QRLabel9;
        TQRShape *QRShape9;
        TQRShape *QRShape10;
        TQRShape *QRShape11;
        TQRShape *QRShape12;
        TQRShape *QRShape13;
        TQRShape *QRShape8;
        TQRBand *QRBand1;
        TQRSysData *QRSysData1;
        TQRSysData *QRSysData3;
        TQRLabel *QRLabel2;
        TQRSysData *QRSysData2;
        TQRLabel *QRLabel1;
        TQRLabel *KindLabel;
        TQRLabel *QRLabel10;
        TQRLabel *QRLabel11;
        TQRLabel *QRLabel12;
        TQRLabel *QRLabel13;
        TQRLabel *QRLabel14;
        TQRLabel *QRLabel15;
        TQRLabel *QRLabel16;
        TQRShape *QRShape1;
        TQRShape *QRShape3;
        TQRShape *QRShape4;
        TQRShape *QRShape5;
        TQRShape *QRShape6;
        TQRShape *QRShape7;
        TQRShape *QRShape2;
        TQRBand *QRBand4;
        TQRSysData *QRSysData4;
        TQRBand *QRBand5;
        TQRDBText *QRDBText1;
        TQRShape *QRShape14;
        TQRDBText *QRDBText2;
        TQRShape *QRShape15;
        TQRDBText *QRDBText3;
        TQRShape *QRShape16;
        TQRDBText *QRDBText4;
        TQRShape *QRShape17;
        TQRDBText *QRDBText5;
        TQRShape *QRShape18;
        TQRDBText *QRDBText6;
        TQRShape *QRShape19;
        TQRDBText *QRDBText7;
private:	// User declarations
public:
//AnsiString KindOfBase;		// User declarations
        __fastcall TRepForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRepForm *RepForm;
//---------------------------------------------------------------------------
#endif
