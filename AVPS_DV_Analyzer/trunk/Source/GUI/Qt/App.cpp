#include <QtGui/QApplication>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#include "GUI/Qt/App.h"
#include "GUI/Qt/GUI_Main.h"
#include "Common/Core.h"
#include <vector>
using namespace std;

#ifdef __WXMAC__
    #include <ApplicationServices/ApplicationServices.h>
#endif //__WXMAC__

int main (int argc, char** argv)
{
    /*int argc=1;
    char* argv[]=
    {
        "xxx",
    };*/

    #ifdef __WXMAC__
        ProcessSerialNumber PSN;
        GetCurrentProcess(&PSN);
        TransformProcessType(&PSN, kProcessTransformToForegroundApplication);
    #endif //__WXMAC__

    setlocale(LC_ALL, "");

    //Command line
    //vector<String> List;
    //for (int Pos=1; Pos<argc; Pos++)
    //    List.push_back(argv[Pos]); //Append the filename to the list of filenames to parse

    //Parse files
    //C->Menu_File_Open_Files_Begin();
    //size_t Files_Count=0;
    //for (size_t Pos=0; Pos<List.size(); Pos++)
    //    Files_Count+=C->Menu_File_Open_Files_Continue(List[Pos]);

    //GUI_Main
    //GUI_Main *frame = new GUI_Main(C, wxPoint(50, 50), wxSize(800-100, 600-100));
    //frame->Show(TRUE);
    //return true;


    //Q_INIT_RESOURCE(GUI_Main);

    QApplication App(argc, argv);
    Core C;

    GUI_Main Window(&C);
    Window.show();
    return App.exec();
}
