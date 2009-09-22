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
    #ifdef __WXMAC__
        ProcessSerialNumber PSN;
        GetCurrentProcess(&PSN);
        TransformProcessType(&PSN, kProcessTransformToForegroundApplication);
    #endif //__WXMAC__

    setlocale(LC_ALL, "");

    QApplication App(argc, argv);
    Core C;

    GUI_Main Window(&C);
    Window.show();
    return App.exec();
}
