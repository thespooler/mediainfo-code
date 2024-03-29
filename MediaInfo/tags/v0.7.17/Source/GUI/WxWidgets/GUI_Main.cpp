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
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#include "GUI/WxWidgets/GUI_Main.h"
#include "GUI/WxWidgets/GUI_Main_FileDrop.h"
#include "Common/Core.h"
#include "CLI/CommandLine_Parser.h"
#include <vector>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef __WXMSW__
    #include "Ressource/Image/MediaInfo.xpm"
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//Get command line args in main()
#ifdef UNICODE
    #ifdef _WIN32
        #include <windows.h>
        #define GETCOMMANDLINE() \
            MediaInfoNameSpace::Char** argv=CommandLineToArgvW(GetCommandLineW(), &argc); \

    #else //WIN32
        #define GETCOMMANDLINE() \
            MediaInfoNameSpace::Char** argv=argv_ansi; \

    #endif //WIN32
#else //UNICODE
    #define GETCOMMANDLINE() \
        MediaInfoNameSpace::Char** argv=argv_ansi; \

#endif //UNICODE

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
// Constructor
GUI_Main::GUI_Main(int argc, MediaInfoNameSpace::Char** argv_ansi, const wxPoint& pos, const wxSize& size, long style)
:wxFrame(NULL, -1, _T("MediaInfo"), pos, size, style)
{
    //Set the frame icon
    #ifdef WIN32 //Win32 use the first icon as file icon
        SetIcon(wxICON(aaaaaaaa));
    #else
        SetIcon(wxICON(MediaInfo));
    #endif

    //Core
    C=new Core;

    //Menu and ToolBar
    Menu_Create();
    ToolBar_Create();

    //Status bar
    CreateStatusBar();

    //GUI
    View=NULL;
    CenterOnScreen();

    //Drag n drop
    #if wxUSE_DRAG_AND_DROP
        FD=new FileDrop(C, this);
        SetDropTarget(FD);
    #endif //wxUSE_DRAG_AND_DROP

    //Defaults
    Menu_View_Sheet->Enable(false); //Not yet available
    Menu_View_Tree->Enable (false); //Not yet available
    Menu_View_Easy->Check(); //Default to HTML with GUI.
    wxCommandEvent* EventTemp=new wxCommandEvent();
    OnMenu_View_Easy(*EventTemp);
    delete EventTemp; //This is done to be GCC-compatible...
    Menu_Debug_Demux_None->Check(); //Default to no Debug Demux

    //Command line
    GETCOMMANDLINE();
    vector<String> List;
    for (int Pos=1; Pos<argc; Pos++)
    {
        //First part of argument (before "=") should be case insensitive
        String Argument(argv[Pos]);
        size_t Egal_Pos=Argument.find(_T('='));
        if (Egal_Pos==string::npos)
            Egal_Pos=Argument.size();
        transform(Argument.begin(), Argument.begin()+Egal_Pos, Argument.begin(), (int(*)(int))tolower); //(int(*)(int)) is a patch for unix
        int Return=Parse (*C, Argument);
        if (Return<0)
            return; //no more tasks to do
        if (Return>0)
            List.push_back(argv[Pos]); //Append the filename to the list of filenames to parse
    }

    //Parse files
    C->Menu_File_Open_Files_Begin();
    size_t Files_Count=0;
    for (size_t Pos=0; Pos<List.size(); Pos++)
        Files_Count+=C->Menu_File_Open_Files_Continue(List[Pos]);
    View_Refresh();
}

//---------------------------------------------------------------------------
GUI_Main::~GUI_Main()
{
    delete C; //C=NULL;
    #if wxUSE_DRAG_AND_DROP
        SetDropTarget(NULL);
    #endif //wxUSE_DRAG_AND_DROP
    delete View; //View=NULL;
}

//***************************************************************************
// Events
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::OnSize(wxSizeEvent& WXUNUSED(event))
{
    if (View && IsShown())
        View->GUI_Resize();
}
