//---------------------------------------------------------------------------
#ifndef ChaildfoH
#define ChaildfoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "Functions.h"
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#define maxparam 30
#include "Inifiles.hpp"
//---------------------------------------------------------------------------
class TChildForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image;
        TPopupMenu *PopupMenu;
        TMainMenu *MainMenu1;
        TMenuItem *AddObjectItem;
        TMenuItem *AddWindowItem;
        TMenuItem *AddIndicatItem;
        TShape *Ramka;
        TMenuItem *AddImageItem;
        TMenuItem *AddLevel;
        TMenuItem *ConnectPopItem;
        TMenuItem *SwitchingPopItem;
        TMenuItem *N1;
        TMenuItem *DeletePopItem;
        TMenuItem *FullItem;
        TMenuItem *AroundItem;
        TMenuItem *FontItem;
        TColorDialog *ColorDialog;
        TFontDialog *FontDialog;
        TMenuItem *OutParamItem;
        TTimer *Timer1;
        TMenuItem *N2;
        TMenuItem *StartItem;
        TMenuItem *PrepareItem;
        TMenuItem *SelectImageItem;
        TOpenDialog *OpenDialog;
        TMenuItem *InvisibleItem;
        TMenuItem *LoadImageItem;
        TMenuItem *AddClip;
        TMenuItem *ShowFrameItem;
        TMenuItem *N3;
        TMenuItem *AddButtonItem;
        TMenuItem *CalledFormItem;
        TMenuItem *StretchItem;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall AddWindowItemClick(TObject *Sender);
        void __fastcall Edit1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall RamkaDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
        void __fastcall FormDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
        void __fastcall RamkaEndDrag(TObject *Sender, TObject *Target,
          int X, int Y);
        void __fastcall AddIndicatItemClick(TObject *Sender);
        void __fastcall Edit1DblClick(TObject *Sender);
        void __fastcall AddImageItemClick(TObject *Sender);
        void __fastcall AddLevelClick(TObject *Sender);
        void __fastcall FullItemClick(TObject *Sender);
        void __fastcall AroundItemClick(TObject *Sender);
        void __fastcall FontItemClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall ConnectPopItemClick(TObject *Sender);
        void __fastcall DeletePopItemClick(TObject *Sender);
        void __fastcall SwitchingPopItemClick(TObject *Sender);
        void __fastcall OutParamItemClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall PrepareItemClick(TObject *Sender);
        void __fastcall SelectImageItemClick(TObject *Sender);
        void __fastcall InvisibleItemClick(TObject *Sender);
        void __fastcall LoadImageItemClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall AddClipClick(TObject *Sender);
        void __fastcall ShowFrameItemClick(TObject *Sender);
        void __fastcall ImageMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall AddButtonItemClick(TObject *Sender);
        void __fastcall CalledFormItemClick(TObject *Sender);
        void __fastcall StretchItemClick(TObject *Sender);
        //__property int Type={read=FType,write=FType};
private:	// User declarations
inline void RefreshStateBar();
int Number;
AnsiString FPictur,FFileName;
void __fastcall SetPictur(AnsiString Value);
void __fastcall SetFileName(AnsiString Value);
//int FType;
public:	// User declarations
        __fastcall TChildForm(TComponent* Owner);
TEdit1 *Edits[maxparam];
bool EditsPresent[maxparam];
//int Adam[maxparam];
//int Kanal[maxparam];
TIndicat *Indicators[maxparam];
bool IndicatPresent[maxparam];
int AdamInd[maxparam];
int KanalInd[maxparam];
TImage1 *Picturies[maxparam];
bool PicturiePresent[maxparam];
TLevel *Levels[maxparam];
bool LevelPresent[maxparam];
TMyButton* Buttons[maxparam];
bool ButtonPresent[maxparam];
TClip *Clip[maxparam];
bool ClipPresent[maxparam];
int DragX,DragY;
TControl *DragObject;
bool Resize;
int SelectObj;
TObjectType ObjType;
void SaveToIniFile(TIniFile*);
void LoadFromIniFile(TIniFile*);
int Type;
__published:
__property AnsiString Pictur={read=FPictur,write=SetPictur};
__property AnsiString FileName={read=FFileName,write=SetFileName};
};
//---------------------------------------------------------------------------
extern PACKAGE TChildForm *ChildForm;
//---------------------------------------------------------------------------
#endif
