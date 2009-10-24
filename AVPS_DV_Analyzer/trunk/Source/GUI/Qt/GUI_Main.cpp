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
#include "GUI/Qt/GUI_Main_ByFrame_Table.h"
#include "GUI/Qt/GUI_Main_ByFrame_Text.h"
#include "GUI/Qt/GUI_Main_MediaInfo.h"
#include "GUI/Qt/GUI_Main_Summary.h"
#include "GUI/Qt/GUI_Main_XML.h"
#include "GUI/Qt/GUI_Main_FCPv4.h"
#include "GUI/Qt/GUI_Main_FCPv5.h"
#include <QtCore/QEvent>
#include <QtCore/QMimeData>
#include <QtCore/QUrl>
#include <QtGui/QApplication>
#include <QtGui/QDropEvent>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDesktopWidget>
#include <QtGui/QTabWidget>
#include "ZenLib/Ztring.h"
using namespace std;
using namespace ZenLib;
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
    move(40, y());
    resize(QApplication::desktop()->screenGeometry().width()-80, 440);

    //Central
    Central=new QTabWidget(this);
    Central->addTab(new GUI_Main_Text_Summary      (C, this), tr("DV analysis summary"));
    Central->addTab(new GUI_Main_ByFrame_Table     (C, this), tr("DV analysis by frame (Table)"));
    Central->addTab(new GUI_Main_ByFrame_Text      (C, this), tr("DV analysis by frame (Text)"));
    Central->addTab(new GUI_Main_XML               (C, this), tr("XML"));
    Central->addTab(new GUI_Main_FCPv4             (C, this), tr("Final Cut Pro XML v4"));
    Central->addTab(new GUI_Main_FCPv5             (C, this), tr("Final Cut Pro XML v5"));
    Central->addTab(new GUI_Main_MediaInfo         (C, this), tr("Technical metadata"));
    setCentralWidget(Central);
    connect(Central, SIGNAL(currentChanged (int)), this, SLOT(OnCurrentChanged(int)));

    //Drag n drop
    setAcceptDrops(true);

    //Defaults
    Menu_View_Summary->setChecked(true);
    emit OnMenu_View_Summary();
    Menu_Options_Verbosity_05->setChecked(true);
    emit OnMenu_Options_Verbosity_05();

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
        Central->setCurrentIndex(View_New);
        View=Central->currentWidget();
    }

    /*
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
            case View_ByFrame_Table : View=new GUI_Main_ByFrame_Table   (C, this); MustCreate=false; break;
            case View_ByFrame_Text  : View=new GUI_Main_ByFrame_Text    (C, this); MustCreate=false; break;
            case View_XML           : View=new GUI_Main_XML             (C, this); MustCreate=false; break;
            case View_MediaInfo     : View=new GUI_Main_MediaInfo       (C, this); MustCreate=false; break;
            default                 : View=NULL;
        }

        setCentralWidget(View);
    }*/

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
        {
            Ztring FileName; FileName.From_UTF8(url.toLocalFile().toUtf8().data());
            #ifdef __WINDOWS__
                FileName.FindAndReplace(Ztring("/"), Ztring("\\"), 0, Ztring_Recursive);
            #endif //__WINDOWS__
            C->Menu_File_Open_Files_Continue(FileName);
        }
    }

    //Showing
    View_Refresh();
}

void GUI_Main::OnCurrentChanged (int Index)
{
    //Showing
    switch (Index)
    {
        case 0  : Menu_View_Summary->setChecked(true); OnMenu_View_Summary(); break;
        case 1  : Menu_View_ByFrame_Table->setChecked(true); OnMenu_View_ByFrame_Table(); break;
        case 2  : Menu_View_ByFrame_Text->setChecked(true); OnMenu_View_ByFrame_Text(); break;
        case 3  : Menu_View_XML->setChecked(true); OnMenu_View_XML(); break;
        case 4  : Menu_View_FCPv4->setChecked(true); OnMenu_View_FCPv4(); break;
        case 5  : Menu_View_FCPv5->setChecked(true); OnMenu_View_FCPv5(); break;
        case 6  : Menu_View_MediaInfo->setChecked(true); OnMenu_View_MediaInfo(); break;
        default : ;
    }

    //Options
    switch (Index)
    {
        case 1                              : Menu_Options_ResetFieldSizes->setVisible(true); break;
        default                             : Menu_Options_ResetFieldSizes->setVisible(false);
    }

}
