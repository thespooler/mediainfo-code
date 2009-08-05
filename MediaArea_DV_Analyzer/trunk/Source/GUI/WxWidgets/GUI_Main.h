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
#include "GUI/Common/GUI_Main_Common_Core.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// the application icon (under Windows and OS/2 it is in resources)
#if defined(__WXGTK__) || defined(__WXMOTIF__) || defined(__WXMAC__) || defined(__WXMGL__) || defined(__WXX11__)
    //#include "mondrian.xpm"
#endif
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
class GUI_Main_Common_Core;
//---------------------------------------------------------------------------

//***************************************************************************
// GUI_Main
//***************************************************************************

class GUI_Main : public wxFrame
{
public:
    GUI_Main (Core* _C, const wxPoint& pos, const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);
    ~GUI_Main ();

    //Menu - List
    wxMenuBar*  Menu;
    wxMenu*     Menu_File;
    wxMenu*     Menu_File_Open;
    wxMenuItem* Menu_File_Open_Files;
    wxMenuItem* Menu_File_Open_Directory;
    wxMenuItem* Menu_File_Quit;
    wxMenu*     Menu_View;
    wxMenuItem* Menu_View_Summary;
    wxMenuItem* Menu_View_ByFrame;
    wxMenuItem* Menu_View_MediaInfo;
    wxMenu*     Menu_Verbosity;
    wxMenuItem* Menu_Verbosity_03;
    wxMenuItem* Menu_Verbosity_05;
    wxMenuItem* Menu_Verbosity_10;
    wxMenu*     Menu_Help;
    wxMenuItem* Menu_Help_Summary;
    wxMenuItem* Menu_Help_ByFrame;
    wxMenuItem* Menu_Help_About;

    //Menu - Actions
    void Menu_Create();
    void OnMenu_File_Open_Files         (wxCommandEvent &event);
    void OnMenu_File_Open_Directory     (wxCommandEvent &event);
    void OnMenu_File_Quit               (wxCommandEvent &event);
    void OnMenu_View_Summary            (wxCommandEvent &event);
    void OnMenu_View_ByFrame            (wxCommandEvent &event);
    void OnMenu_View_MediaInfo          (wxCommandEvent &event);
    void OnMenu_Verbosity_03            (wxCommandEvent &event);
    void OnMenu_Verbosity_05            (wxCommandEvent &event);
    void OnMenu_Verbosity_10            (wxCommandEvent &event);
    void OnMenu_Help_Summary            (wxCommandEvent &event);
    void OnMenu_Help_ByFrame            (wxCommandEvent &event);
    void OnMenu_Help_About              (wxCommandEvent &event);
    void OnSize                         (wxSizeEvent    &event);

    //ToolBar - List
    wxToolBar*  ToolBar;

    //ToolBar - Actions
    void ToolBar_Create();

    //Helpers
    enum view
    {
        View_None,
        View_Summary,
        View_ByFrame,
        View_MediaInfo,
    };
    void View_Refresh(view View_New=View_None);

private:
    //Non-GUI Elements
    #if wxUSE_DRAG_AND_DROP
        FileDrop* FD;
    #endif //wxUSE_DRAG_AND_DROP
    Core* C;

    //GUI
    GUI_Main_Common_Core* View;
    view View_Current;
    bool MustCreate;

    //wxWidgets
    DECLARE_EVENT_TABLE() //Any class wishing to process wxWindows events must use this macro
};

#endif
