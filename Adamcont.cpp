//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Adamcont.res");
USEFORM("MainUnut.cpp", MainForm);
USEFORM("Chaild.cpp", ChildForm);
USEFORM("SetBD.cpp", SetParamForm);
USEFORM("DataUnit.cpp", DataModule1); /* TDataModule: DesignClass */
USEFORM("Graph.cpp", GraphForm);
USEFORM("SetStat.cpp", SetBDForm);
USEFORM("Connect.cpp", FormOfConnect);
USEFORM("SetOutPa.cpp", SetOutParamForm);
USEFORM("SetGraph.cpp", SetPrnFo);
USEFORM("Grapher.cpp", GrapherForm);
USEUNIT("Function.cpp");
USEFORM("AlarmLis.cpp", AlarmListForm);
USEFORM("ReportFo.cpp", RepForm);
USEFORM("SelectGr.cpp", SelGraphForm);
USEFORM("SetAdres.cpp", AdrForm);
USEUNIT("ReThread.cpp");
USEFORM("SelFrame.cpp", SelFrameForm);
USEFORM("IOThread.cpp", AdConnThread); /* TDataModule: DesignClass */
USEUNIT("Constant.cpp");
USEUNIT("SendThre.cpp");
USEFORM("InteForm.cpp", IntegrForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->HelpFile = "C:\\Мои документы\\Sasha\\Builder\\Project2\\Help.hlp";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TAdConnThread), &AdConnThread);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
