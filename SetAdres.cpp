//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SetAdres.h"
#include "MainUnut.h"
#include "Constant.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAdrForm *AdrForm;
//---------------------------------------------------------------------------
__fastcall TAdrForm::TAdrForm(TComponent* Owner)
        : TForm(Owner)
{
AdrUpDown->Position=0;
AdrUpDown->Max=maxadam-1;
IndUpDown->Position=0;
//if(AdConnThread)AdrEdit->Text=AdConnThread->ComName[AdrUpDown->Position][3];//AnsiString(MainForm->Adres[0][0])+AnsiString(MainForm->Adres[0][1]);
char a,b;
a=AdConnThread->ComName[AdrUpDown->Position][3];//MainForm->Adres[AdrUpDown->Position][0];
b=AdConnThread->ComName[AdrUpDown->Position][4];
if((a>=48)&&(a<=57))
AdrEdit->Text=AnsiString(a);
else
 {
 AdrEdit->Text="nn";
 return;
 }
if((b>=48)&&(b<=57))
AdrEdit->Text+=AnsiString(b);
MessageEdit->Text=MainForm->MessageByIndex[0];
}
//---------------------------------------------------------------------------
void __fastcall TAdrForm::AdrUpDownClick(TObject *Sender,
      TUDBtnType Button)
{
int LastPosition;
if(Button==0)            //btNext
 {
 LastPosition=(AdrUpDown->Position)-1;
 /*if((AdrEdit->Text!="")&&(((AdrEdit->Text[1]>=48)&&(AdrEdit->Text[1]<=57))||
 ((AdrEdit->Text[1]>=65)&&(AdrEdit->Text[1]<=70)))&&
 (((AdrEdit->Text[2]>=48)&&(AdrEdit->Text[2]<=57))||
 ((AdrEdit->Text[2]>=65)&&(AdrEdit->Text[2]<=70))))
  {
  MainForm->Adres[(AdrUpDown->Position)-1][0]=AdrEdit->Text[1];
  MainForm->Adres[(AdrUpDown->Position)-1][1]=AdrEdit->Text[2];
  }
 else
  {
  MainForm->Adres[(AdrUpDown->Position)-1][0]='n';
  MainForm->Adres[(AdrUpDown->Position)-1][1]='n';
  }*/
 }
else
 {
 LastPosition=(AdrUpDown->Position)+1;
 /*if((AdrEdit->Text!="")&&(((AdrEdit->Text[1]>=48)&&(AdrEdit->Text[1]<=57))||
 ((AdrEdit->Text[1]>=65)&&(AdrEdit->Text[1]<=70)))&&
 (((AdrEdit->Text[2]>=48)&&(AdrEdit->Text[2]<=57))||
 ((AdrEdit->Text[2]>=65)&&(AdrEdit->Text[2]<=70))))
  {
  MainForm->Adres[(AdrUpDown->Position)+1][0]=AdrEdit->Text[1];
  MainForm->Adres[(AdrUpDown->Position)+1][1]=AdrEdit->Text[2];
  }
 else
  {
  MainForm->Adres[(AdrUpDown->Position)+1][0]='n';
  MainForm->Adres[(AdrUpDown->Position)+1][1]='n';
  }*/
 }
CheckAndSave(LastPosition);
char a,b;
a=AdConnThread->ComName[AdrUpDown->Position][3];//MainForm->Adres[AdrUpDown->Position][0];
b=AdConnThread->ComName[AdrUpDown->Position][4];
if((a>=48)&&(a<=57))
AdrEdit->Text=AnsiString(a);
else
 {
 AdrEdit->Text="nn";
 return;
 }
if((b>=48)&&(b<=57))
 {
 AdrEdit->Text=AdrEdit->Text+"0";
 AdrEdit->Text[2]=b;
 }
}
//---------------------------------------------------------------------------


void __fastcall TAdrForm::IndUpDownClick(TObject *Sender,
      TUDBtnType Button)
{
if(Button==0)//btNext
 {
 MainForm->MessageByIndex[(IndUpDown->Position)-1]=MessageEdit->Text;
 MainForm->MessageByIndex[(IndUpDown->Position)-1]=MessageEdit->Text;
 }
else
 {
 MainForm->MessageByIndex[(IndUpDown->Position)+1]=MessageEdit->Text;
 MainForm->MessageByIndex[(IndUpDown->Position)+1]=MessageEdit->Text;
 }
MessageEdit->Text=MainForm->MessageByIndex[IndUpDown->Position];
}
//---------------------------------------------------------------------------
bool TAdrForm::CheckAndSave(int Pos)
{
char a,b;
if(AdrEdit->Text.Length()>=1)
a=AdrEdit->Text[1];
else a=0;//AdConnThread->ComName[AdrUpDown->Position][3];
if(AdrEdit->Text.Length()>=2)
b=AdrEdit->Text[2];//AdConnThread->ComName[AdrUpDown->Position][4];
else b=0;
if((a>=48)&&(a<=57))
AdConnThread->ComName[Pos][3]=a;
else
 {
 MessageBox(NULL,"Недопустимый номер порта","Ошибка",MB_OK|MB_ICONSTOP);
 return 0;
 }
if((b>=48)&&(b<=57))
 {
 AdConnThread->ComName[Pos][4]=b;
 AdConnThread->ComName[Pos][5]=0;
 return 1;
 }
else
 {
 AdConnThread->ComName[Pos][4]=0;
 return 1;
 }
/*
if((AdrEdit->Text!="")&&(AdrEdit->Text[1]>=48)&&(AdrEdit->Text[1]<=57))
 {
 AdConnThread->ComName[Pos][3]=AdrEdit->Text;
 return 1;
 }
else
 {
 MessageBox(NULL,"Недопустимый номер порта","Ошибка",MB_OK|MB_ICONSTOP);
 return 0
 }*/
}

void __fastcall TAdrForm::FormClose(TObject *Sender, TCloseAction &Action)
{
CheckAndSave(AdrUpDown->Position);
}
//---------------------------------------------------------------------------

