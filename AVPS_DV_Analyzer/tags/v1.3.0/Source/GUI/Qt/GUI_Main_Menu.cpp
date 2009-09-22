// GUI_Main_Menu - WxWidgets GUI for MediaInfo, Menu
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
//#include "GUI/WxWidgets/GUI_About.h"
#include "GUI/Qt/GUI_Main.h"
#include "Common/Core.h"
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QFileDialog>
#include <QtGui/QDesktopServices>
#include <QtCore/QUrl>
#include "GUI/Qt/GUI_About.h"
#include "ZenLib/ZtringList.h"
#include "GUI/Qt/GUI_Help_ByFrame.h"
#include "GUI/Qt/GUI_Help_Summary.h"
//---------------------------------------------------------------------------

//***************************************************************************
// Events
//***************************************************************************

//***************************************************************************
// Menu creation
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::Menu_Create()
{
    Menu_File_Open_Files = new QAction(QIcon(":/Image/Menu/File_Open_File.png"), tr("Open file(s)..."), this);
    Menu_File_Open_Files->setShortcut(tr("Ctrl+F"));
    Menu_File_Open_Files->setStatusTip(tr("Open file(s)"));
    connect(Menu_File_Open_Files, SIGNAL(triggered()), this, SLOT(OnMenu_File_Open_Files()));

    Menu_File_Open_Directory = new QAction(QIcon(":/Image/Menu/File_Open_Directory.png"), tr("Open Directory..."), this);
    Menu_File_Open_Directory->setShortcut(tr("Ctrl+D"));
    Menu_File_Open_Directory->setStatusTip(tr("Open directory"));
    connect(Menu_File_Open_Directory, SIGNAL(triggered()), this, SLOT(OnMenu_File_Open_Directory()));

    Menu_File_Quit = new QAction(tr("Q&uit"), this);
    Menu_File_Quit->setShortcut(tr("Ctrl+Q"));
    Menu_File_Quit->setStatusTip(tr("Quit the application"));
    connect(Menu_File_Quit, SIGNAL(triggered()), this, SLOT(close()));

    Menu_File = menuBar()->addMenu(tr("&File"));
    Menu_File->addAction(Menu_File_Open_Files);
    Menu_File->addAction(Menu_File_Open_Directory);
    Menu_File->addSeparator();
    Menu_File->addAction(Menu_File_Quit);

    Menu_View_Summary = new QAction(tr("DV analysis summary"), this);
    Menu_View_Summary->setShortcut(tr(""));
    Menu_View_Summary->setCheckable(true);
    Menu_View_Summary->setStatusTip(tr(""));
    connect(Menu_View_Summary, SIGNAL(triggered()), this, SLOT(OnMenu_View_Summary()));

    Menu_View_ByFrame = new QAction(tr("DV analysis by frame"), this);
    Menu_View_ByFrame->setShortcut(tr(""));
    Menu_View_ByFrame->setCheckable(true);
    Menu_View_ByFrame->setStatusTip(tr(""));
    connect(Menu_View_ByFrame, SIGNAL(triggered()), this, SLOT(OnMenu_View_ByFrame()));

    Menu_View_XML = new QAction(tr("XML output"), this);
    Menu_View_XML->setShortcut(tr(""));
    Menu_View_XML->setCheckable(true);
    Menu_View_XML->setStatusTip(tr(""));
    connect(Menu_View_XML, SIGNAL(triggered()), this, SLOT(OnMenu_View_XML()));

    Menu_View_MediaInfo = new QAction(tr("Technical metadata"), this);
    Menu_View_MediaInfo->setShortcut(tr(""));
    Menu_View_MediaInfo->setCheckable(true);
    Menu_View_MediaInfo->setStatusTip(tr(""));
    connect(Menu_View_MediaInfo, SIGNAL(triggered()), this, SLOT(OnMenu_View_MediaInfo()));

    Menu_View_Group = new QActionGroup(this);
    Menu_View_Group->addAction(Menu_View_Summary);
    Menu_View_Group->addAction(Menu_View_ByFrame);
    Menu_View_Group->addAction(Menu_View_XML);
    Menu_View_Group->addAction(Menu_View_MediaInfo);
    Menu_View = menuBar()->addMenu(tr("&View"));
    Menu_View->addAction(Menu_View_Summary);
    Menu_View->addAction(Menu_View_ByFrame);
    Menu_View->addAction(Menu_View_XML);
    Menu_View->addAction(Menu_View_MediaInfo);
    Menu_View_Group = new QActionGroup(this);

    Menu_Verbosity_03 = new QAction(tr("Errors only"), this);
    Menu_Verbosity_03->setShortcut(tr(""));
    Menu_Verbosity_03->setCheckable(true);
    Menu_Verbosity_03->setStatusTip(tr("DV analysis by frame, Errors only"));
    connect(Menu_Verbosity_03, SIGNAL(triggered()), this, SLOT(OnMenu_Verbosity_03()));

    Menu_Verbosity_05 = new QAction(tr("Errors and information"), this);
    Menu_Verbosity_05->setShortcut(tr(""));
    Menu_Verbosity_05->setCheckable(true);
    Menu_Verbosity_05->setStatusTip(tr("DV analysis by frame, Errors and information"));
    connect(Menu_Verbosity_05, SIGNAL(triggered()), this, SLOT(OnMenu_Verbosity_05()));

    Menu_Verbosity_10 = new QAction(tr("All"), this);
    Menu_Verbosity_10->setShortcut(tr(""));
    Menu_Verbosity_10->setCheckable(true);
    Menu_Verbosity_10->setStatusTip(tr("DV analysis by frame, All"));
    connect(Menu_Verbosity_10, SIGNAL(triggered()), this, SLOT(OnMenu_Verbosity_10()));

    Menu_Verbosity_Group = new QActionGroup(this);
    Menu_Verbosity_Group->addAction(Menu_Verbosity_03);
    Menu_Verbosity_Group->addAction(Menu_Verbosity_05);
    Menu_Verbosity_Group->addAction(Menu_Verbosity_10);
    Menu_Verbosity = menuBar()->addMenu(tr("V&erbosity"));
    Menu_Verbosity->addAction(Menu_Verbosity_03);
    Menu_Verbosity->addAction(Menu_Verbosity_05);
    Menu_Verbosity->addAction(Menu_Verbosity_10);

    Menu_Debug_MediaInfo_InternalFields = new QAction(tr("Internal fields"), this);
    Menu_Debug_MediaInfo_InternalFields->setShortcut(tr(""));
    Menu_Debug_MediaInfo_InternalFields->setCheckable(true);
    Menu_Debug_MediaInfo_InternalFields->setStatusTip(tr(""));
    connect(Menu_Debug_MediaInfo_InternalFields, SIGNAL(triggered()), this, SLOT(OnMenu_Debug_MediaInfo_InternalFields()));

    Menu_Debug_MediaInfo_RawFieldsNames = new QAction(tr("Raw field names"), this);
    Menu_Debug_MediaInfo_RawFieldsNames->setShortcut(tr(""));
    Menu_Debug_MediaInfo_RawFieldsNames->setCheckable(true);
    Menu_Debug_MediaInfo_RawFieldsNames->setStatusTip(tr(""));
    connect(Menu_Debug_MediaInfo_RawFieldsNames, SIGNAL(triggered()), this, SLOT(OnMenu_Debug_MediaInfo_RawFieldsNames()));

    Menu_Debug=menuBar()->addMenu(tr("&Debug"));
    Menu_Debug_MediaInfo = Menu_Debug->addMenu(tr("&Technical Metadata"));
    Menu_Debug_MediaInfo->addAction(Menu_Debug_MediaInfo_InternalFields);
    Menu_Debug_MediaInfo->addAction(Menu_Debug_MediaInfo_RawFieldsNames);

    Menu_Help_Summary = new QAction(tr("\"Summary\" format"), this);
    Menu_Help_Summary->setShortcut(tr(""));
    Menu_Help_Summary->setStatusTip(tr(""));
    connect(Menu_Help_Summary, SIGNAL(triggered()), this, SLOT(OnMenu_Help_Summary()));

    Menu_Help_ByFrame = new QAction(tr("\"By frame\" format"), this);
    Menu_Help_ByFrame->setShortcut(tr(""));
    Menu_Help_ByFrame->setStatusTip(tr(""));
    connect(Menu_Help_ByFrame, SIGNAL(triggered()), this, SLOT(OnMenu_Help_ByFrame()));

    Menu_Help_About = new QAction(QIcon(":/Image/Menu/Help_About.png"), tr("About..."), this);
    Menu_Help_About->setShortcut(tr(""));
    Menu_Help_About->setStatusTip(tr(""));
    connect(Menu_Help_About, SIGNAL(triggered()), this, SLOT(OnMenu_Help_About()));

    Menu_Help_AVPS_Website = new QAction(QIcon(":/Image/AVPS/logo_sign_alpha.png"), tr("AVPS website"), this);
    Menu_Help_AVPS_Website->setShortcut(tr(""));
    Menu_Help_AVPS_Website->setStatusTip(tr(""));
    connect(Menu_Help_AVPS_Website, SIGNAL(triggered()), this, SLOT(OnMenu_Help_AVPS_Website()));

    Menu_Help = menuBar()->addMenu(tr("&Help"));
    Menu_Help->addAction(Menu_Help_Summary);
    Menu_Help->addAction(Menu_Help_ByFrame);
    Menu_Help->addSeparator();
    Menu_Help->addAction(Menu_Help_About);
    Menu_Help->addAction(Menu_Help_AVPS_Website);
}

//***************************************************************************
// Menu actions
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_File_Open_Files()
{
    //User interaction
    QStringList FileNamesQ = QFileDialog::getOpenFileNames(this, "", "", "");
    if (FileNamesQ.empty())
        return;

    ZenLib::ZtringList FileNames;
    for (int Pos=0; Pos<FileNamesQ.size(); Pos++)
        FileNames.push_back(ZenLib::Ztring().From_UTF8(FileNamesQ[Pos].toUtf8().data()));

    //Configuring
    C->Menu_File_Open_Files_Begin();
    for (size_t Pos=0; Pos<FileNames.size(); Pos++)
        C->Menu_File_Open_Files_Continue(FileNames[Pos]);

    //Showing
    View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_File_Open_Directory()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if (FileNamesQ.isEmpty())
        return;

    //Configuring
    C->Menu_File_Open_Files_Begin();
    C->Menu_File_Open_Files_Continue(ZenLib::Ztring().From_UTF8(FileNamesQ.toUtf8().data()));

    //Showing
    View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_Summary()
{
    //Configuring
    C->Errors_Stats_WithHeader=true;
    C->Errors_Stats_WithFooter=false;

    //Showing
    View_Refresh(View_Summary);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_ByFrame()
{
    //Configuring
    C->Errors_Stats_WithHeader=true;
    C->Errors_Stats_WithFooter=false;

    //Showing
    View_Refresh(View_ByFrame);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_MediaInfo()
{
    //Showing
    View_Refresh(View_MediaInfo);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_XML()
{
    //Showing
    View_Refresh(View_XML);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Verbosity_03()
{
    //Configuring
    C->Menu_Verbosity_03();

    //Showing
    if (View_Current==View_Summary || View_Current==View_ByFrame || View_Current==View_XML)
        View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Verbosity_05()
{
    //Configuring
    C->Menu_Verbosity_05();

    //Showing
    if (View_Current==View_Summary || View_Current==View_ByFrame || View_Current==View_XML)
        View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Verbosity_10()
{
    //Configuring
    C->Menu_Verbosity_10();

    //Showing
    if (View_Current==View_Summary || View_Current==View_ByFrame || View_Current==View_XML)
        View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Debug_MediaInfo_InternalFields()
{
    //Configuring
    C->Menu_Option_Preferences_Option(_T("Complete"), Menu_Debug_MediaInfo_InternalFields->isChecked()?_T("1"):_T("0"));

    //Showing
    if (View_Current==View_MediaInfo)
        View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Debug_MediaInfo_RawFieldsNames()
{
    //Configuring
    C->Menu_Option_Preferences_Option(_T("Language"), Menu_Debug_MediaInfo_RawFieldsNames->isChecked()?_T("raw"):_T(""));

    //Showing
    if (View_Current==View_MediaInfo)
        View_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_Summary()
{
    //Showing
    GUI_Help_Summary* Frame=new GUI_Help_Summary(this);
    Frame->show();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_ByFrame()
{
    //Showing
    GUI_Help_ByFrame* Frame=new GUI_Help_ByFrame(this);
    Frame->show();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_About()
{
    //Showing
    GUI_About *About = new GUI_About(this);
    About->exec();
    delete About;
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_AVPS_Website()
{
    //Showing
    QDesktopServices::openUrl(QUrl("http://avpreserve.com/blog/dvanalyzer", QUrl::TolerantMode));
}

//***************************************************************************
// ToolBar creation
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::ToolBar_Create()
{
    ToolBar=new QToolBar(tr("ToolBar"));
    ToolBar->setIconSize(QSize(32, 32));
        
    ToolBar->addAction(Menu_File_Open_Files);
    ToolBar->addAction(Menu_File_Open_Directory);
    ToolBar->addSeparator();
    ToolBar->addAction(Menu_Help_About);
    ToolBar->addAction(Menu_Help_AVPS_Website);

    #ifndef __APPLE__
        addToolBar(Qt::LeftToolBarArea, ToolBar);
    #else //__APPLE__
        addToolBar(ToolBar);
    #endif //__APPLE__
}
