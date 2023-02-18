//---------------------------------------------------------------------------
#ifndef SelectGrH
#define SelectGrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include "MainUnut.h"
#include "Graph.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSelGraphForm : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox;
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *AllBitBtn;
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall ListBoxDrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State);
private:	// User declarations
public:		// User declarations
int Graphics[maxgraph];
//int maxgraph
int GraphToList[maxgraph];//номера графиков соответствующие индексам ListBox
TColor GraphColor[maxgraph];
Graphics::TBitmap *Bitmap[maxgraph];
bool PresentBit[maxgraph];
        __fastcall TSelGraphForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelGraphForm *SelGraphForm;
//---------------------------------------------------------------------------
#endif
