// GUI_Main - WxWidgets GUI for MediaInfo
// Copyright (C) 2002-2009 Jerome Martinez, Zen@MediaArea.net
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#include "GUI/Qt/GUI_Main.h"
#include "Common/Core.h"
#include <vector>
#include <algorithm>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include "GUI/Qt/GUI_Main_ByFrame.h"
#include "GUI/Qt/GUI_Main_MediaInfo.h"
#include "GUI/Qt/GUI_Main_Summary.h"
#include "GUI/Qt/GUI_Main_XML.h"
#include <QtCore/QEvent>
#include <QtCore/QMimeData>
#include <QtCore/QUrl>
#include <QtGui/QApplication>
#include <QtGui/QDropEvent>
#include <QtGui/QDragEnterEvent>
#include "ZenLib/Ztring.h"
using namespace std;
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
// Constructor
GUI_Main::GUI_Main(Core* _C)
{
    //Internal
    C=_C;

    //Configure
    View_Current=View_Summary;
    MustCreate=true;

    //Menu and ToolBar
    Menu_Create();
    ToolBar_Create();

    //GUI
    View=NULL;
    //CenterOnScreen();
    setStatusBar(new QStatusBar());
    resize(620, 440);

    //Drag n drop
    setAcceptDrops(true);

    //Defaults
    Menu_View_Summary->setChecked(true);
    emit OnMenu_View_Summary();
    Menu_Verbosity_05->setChecked(true);
    emit OnMenu_Verbosity_05();

    //GUI
    setWindowTitle("DV Analyzer - AudioVisual Preservation Solutions, Inc.");
    setWindowIcon (QIcon(":/Image/AVPS/logo_sign_alpha_square.png"));
}

//---------------------------------------------------------------------------
GUI_Main::~GUI_Main()
{
}

//***************************************************************************
// View_Refresh
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::View_Refresh(view View_New)
{
    if (View_New!=View_None)
    {
        View_Current=View_New;
        MustCreate=true;
    }
        
    if (MustCreate)
    {
        delete View;
        switch (View_Current)
        {
            case View_Summary       : View=new GUI_Main_Text_Summary    (C, this); MustCreate=false; break;
            case View_ByFrame       : View=new GUI_Main_Text_ByFrame    (C, this); MustCreate=false; break;
            case View_XML           : View=new GUI_Main_Text_XML        (C, this); MustCreate=false; break;
            case View_MediaInfo     : View=new GUI_Main_Text_MediaInfo  (C, this); MustCreate=false; break;
            default                 : View=NULL;
        }

        setCentralWidget(View);
    }

    QEvent event(QEvent::User);
    QApplication::sendEvent(View, &event);
}

void GUI_Main::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}
 
void GUI_Main::dropEvent(QDropEvent *event)
{
    C->Menu_File_Open_Files_Begin();

    const QMimeData* Data=event->mimeData ();
    if (event->mimeData()->hasUrls())
    {
         foreach (QUrl url, event->mimeData()->urls())
            C->Menu_File_Open_Files_Continue(ZenLib::Ztring().From_UTF8(url.toLocalFile().toUtf8().data()));
    }

    //Showing
    View_Refresh();
}
