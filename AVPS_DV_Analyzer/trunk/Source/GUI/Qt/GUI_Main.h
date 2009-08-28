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
//
// WxWidgets GUI for MediaInfo
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef GUI_MainH
#define GUI_MainH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QActionGroup>
#include <QtGui/QToolBar>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifdef MEDIAINFO_DLL
    #include "MediaInfoDLL/MediaInfoDLL.h"
    #define MediaInfoNameSpace MediaInfoDLL
#elif defined MEDIAINFO_STATIC
    #include "MediaInfoDLL/MediaInfoDLL_Static.h"
    #define MediaInfoNameSpace MediaInfoDLL
#else
    #include "MediaInfo/MediaInfoList.h"
    #define MediaInfoNameSpace MediaInfoLib
#endif
using namespace MediaInfoNameSpace;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class Core;
class FileDrop;
class QWidget;
class QDropEvent;
class QDragEnterEvent;
//---------------------------------------------------------------------------

//***************************************************************************
// GUI_Main
//***************************************************************************

class GUI_Main : public QMainWindow
{
     Q_OBJECT

public:
    GUI_Main (Core* _C);
    ~GUI_Main ();

 private:
    //Menu - List
    void Menu_Create();
    QMenu*          Menu_File;
    QAction*        Menu_File_Open_Files;
    QAction*        Menu_File_Open_Directory;
    QAction*        Menu_File_Quit;
    QMenu*          Menu_View;
    QAction*        Menu_View_Summary;
    QAction*        Menu_View_ByFrame;
    QAction*        Menu_View_XML;
    QAction*        Menu_View_MediaInfo;
    QActionGroup*   Menu_View_Group;
    QMenu*          Menu_Verbosity;
    QAction*        Menu_Verbosity_03;
    QAction*        Menu_Verbosity_05;
    QAction*        Menu_Verbosity_10;
    QActionGroup*   Menu_Verbosity_Group;
    QMenu*          Menu_Debug;
    QMenu*          Menu_Debug_MediaInfo;
    QAction*        Menu_Debug_MediaInfo_InternalFields;
    QAction*        Menu_Debug_MediaInfo_RawFieldsNames;
    QMenu*          Menu_Help;
    QAction*        Menu_Help_Summary;
    QAction*        Menu_Help_ByFrame;
    QAction*        Menu_Help_About;
    QAction*        Menu_Help_AVPS_Website;

 private slots:
    //Menu - Actions
    void OnMenu_File_Open_Files                 ();
    void OnMenu_File_Open_Directory             ();
    void OnMenu_View_Summary                    ();
    void OnMenu_View_ByFrame                    ();
    void OnMenu_View_XML                        ();
    void OnMenu_View_MediaInfo                  ();
    void OnMenu_Verbosity_03                    ();
    void OnMenu_Verbosity_05                    ();
    void OnMenu_Verbosity_10                    ();
    void OnMenu_Debug_MediaInfo_InternalFields  ();
    void OnMenu_Debug_MediaInfo_RawFieldsNames  ();
    void OnMenu_Help_Summary                    ();
    void OnMenu_Help_ByFrame                    ();
    void OnMenu_Help_About                      ();
    void OnMenu_Help_AVPS_Website               ();

private:
    //ToolBar - List
    QToolBar*  ToolBar;

    //ToolBar - Actions
    void ToolBar_Create();

private:
    //Non-GUI Elements
    Core* C;

    //GUI
    QWidget* View;
    enum view
    {
        View_None,
        View_Summary,
        View_ByFrame,
        View_XML,
        View_MediaInfo,
    };
    view View_Current;
    bool MustCreate;

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

    //Helpers
    void View_Refresh(view View_New=View_None);
};

#endif
