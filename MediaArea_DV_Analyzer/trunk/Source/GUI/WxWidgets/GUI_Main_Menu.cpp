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
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#include "GUI/WxWidgets/GUI_About.h"
#include "GUI/WxWidgets/GUI_Main.h"
#include "Common/Core.h"
#include <wx/image.h>
#include "GUI/WxWidgets/GUI_Help_Summary.h"
#include "GUI/WxWidgets/GUI_Help_ByFrame.h"
//---------------------------------------------------------------------------

//***************************************************************************
// Events
//***************************************************************************

//---------------------------------------------------------------------------
enum
{
    ID_Menu_File_Open,
    ID_Menu_File_Open_Files,
    ID_Menu_File_Open_Directory,
    ID_Menu_File_Quit,
    ID_Menu_View_Summary,
    ID_Menu_View_ByFrame,
    ID_Menu_View_MediaInfo,
    ID_Menu_Verbosity_03,
    ID_Menu_Verbosity_05,
    ID_Menu_Verbosity_10,
    ID_Menu_Help_Summary,
    ID_Menu_Help_ByFrame,
};

//---------------------------------------------------------------------------
BEGIN_EVENT_TABLE(GUI_Main, wxFrame)
    //Menu
    EVT_MENU(ID_Menu_File_Open_Files,       GUI_Main::OnMenu_File_Open_Files)
    EVT_MENU(ID_Menu_File_Open_Directory,   GUI_Main::OnMenu_File_Open_Directory)
    EVT_MENU(wxID_EXIT,                     GUI_Main::OnMenu_File_Quit)
    EVT_MENU(ID_Menu_View_Summary,          GUI_Main::OnMenu_View_Summary)
    EVT_MENU(ID_Menu_View_ByFrame,          GUI_Main::OnMenu_View_ByFrame)
    EVT_MENU(ID_Menu_View_MediaInfo,        GUI_Main::OnMenu_View_MediaInfo)
    EVT_MENU(ID_Menu_Verbosity_03,          GUI_Main::OnMenu_Verbosity_03)
    EVT_MENU(ID_Menu_Verbosity_05,          GUI_Main::OnMenu_Verbosity_05)
    EVT_MENU(ID_Menu_Verbosity_10,          GUI_Main::OnMenu_Verbosity_10)
    EVT_MENU(ID_Menu_Help_Summary,          GUI_Main::OnMenu_Help_Summary)
    EVT_MENU(ID_Menu_Help_ByFrame,          GUI_Main::OnMenu_Help_ByFrame)
    EVT_MENU(wxID_ABOUT,                    GUI_Main::OnMenu_Help_About)

    //GUI
    EVT_SIZE(                               GUI_Main::OnSize)
END_EVENT_TABLE()

//---------------------------------------------------------------------------
#ifndef __WXMSW__
    #include "Ressource/Image/Menu/File_Open_File.xpm"
    #include "Ressource/Image/Menu/File_Open_Directory.xpm"
    #include "Ressource/Image/Menu/Help_About.xpm"
#endif

//***************************************************************************
// Menu creation
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::Menu_Create()
{
    //File - Open
    Menu_File_Open              =new wxMenu;
    Menu_File_Open_Files        =Menu_File_Open->Append(ID_Menu_File_Open_Files, _T("Open &file(s)"));
    Menu_File_Open_Directory    =Menu_File_Open->Append(ID_Menu_File_Open_Directory, _T("Open &directory"));

    //File
    Menu_File=new wxMenu;
                                 Menu_File->Append(ID_Menu_File_Open, _T("Open"), Menu_File_Open);
                                 Menu_File->AppendSeparator();
    Menu_File_Quit              =Menu_File->Append(wxID_EXIT, _T("E&xit\tAlt-X"), _T("Quit this program"));

    //View
    Menu_View                   =new wxMenu;
    Menu_View_Summary           =Menu_View->AppendRadioItem(ID_Menu_View_Summary, _T("Summary"), _T("Summary"));
    Menu_View_ByFrame           =Menu_View->AppendRadioItem(ID_Menu_View_ByFrame, _T("By frame"), _T("Analyze by frame"));
    Menu_View_MediaInfo         =Menu_View->AppendRadioItem(ID_Menu_View_MediaInfo, _T("MediaInfo"), _T("MediaInfo"));

    //View
    Menu_Verbosity              =new wxMenu;
    Menu_Verbosity_03           =Menu_Verbosity->AppendRadioItem(ID_Menu_Verbosity_03, _T("Errors only"), _T("Display only frames wigh errors"));
    Menu_Verbosity_05           =Menu_Verbosity->AppendRadioItem(ID_Menu_Verbosity_05, _T("Errors and information"), _T("Display frames with errors and information"));
    Menu_Verbosity_05->Check();
    Menu_Verbosity_10           =Menu_Verbosity->AppendRadioItem(ID_Menu_Verbosity_10, _T("All"), _T("Display all frames"));

    //Help
    Menu_Help                   =new wxMenu;
    Menu_Help_About             =Menu_Help->Append(ID_Menu_Help_Summary, _T("\"Summary\" format"), _T("Show the format description of the \"Summary\" page"));
    Menu_Help_About             =Menu_Help->Append(ID_Menu_Help_ByFrame, _T("\"By frame\" format"), _T("Show the format description of the \"By frame\" page"));
                                 Menu_Help->AppendSeparator();
    Menu_Help_About             =Menu_Help->Append(wxID_ABOUT, _T("&About...\tF1"), _T("Show about dialog"));

    //Main
    Menu=new wxMenuBar();
    Menu->Append(Menu_File,      _T("&File"));
    Menu->Append(Menu_View,      _T("&View"));
    Menu->Append(Menu_Verbosity, _T("V&erbosity"));
    Menu->Append(Menu_Help,      _T("&Help"));
    SetMenuBar(Menu);
}

//***************************************************************************
// Menu actions
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_File_Open_Files(wxCommandEvent& WXUNUSED(event))
{
    //User interaction
    wxFileDialog* Dialog=new wxFileDialog(this, _T("Choose a file"), _T(""), _T(""), _T("*.*"), wxOPEN|wxFILE_MUST_EXIST|wxMULTIPLE);
    if (Dialog->ShowModal()!=wxID_OK)
    {
        delete Dialog;
        return;
    }
    wxArrayString FileNames;
    Dialog->GetPaths(FileNames);
    delete Dialog;

    //Configuring
    C->Menu_File_Open_Files_Begin();
    for (size_t Pos=0; Pos<FileNames.size(); Pos++)
        C->Menu_File_Open_Files_Continue(FileNames[Pos].c_str());

    //Showing
    View->GUI_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_File_Open_Directory(wxCommandEvent& WXUNUSED(event))
{
    //User interaction
    wxDirDialog* Dialog=new wxDirDialog(this, _T("Choose a directory"));
    if (Dialog->ShowModal()!=wxID_OK)
        return;
    wxString DirName=Dialog->GetPath();
    delete Dialog;

    //Configuring
    C->Menu_File_Open_Files_Begin();
    C->Menu_File_Open_Files_Continue(DirName.c_str());

    //Showing
    View->GUI_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_File_Quit(wxCommandEvent& WXUNUSED(event))
{
    //User interaction
    Close(true);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_Summary(wxCommandEvent& WXUNUSED(event))
{
    //Showing
    View_Refresh(View_Summary);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_ByFrame(wxCommandEvent& WXUNUSED(event))
{
    //Showing
    View_Refresh(View_ByFrame);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_MediaInfo(wxCommandEvent& WXUNUSED(event))
{
    //Showing
    View_Refresh(View_MediaInfo);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Verbosity_03(wxCommandEvent& WXUNUSED(event))
{
    //Showing
    C->Menu_Option_Preferences_Option (_T("Verbosity"), _T("0.3"));
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Verbosity_05(wxCommandEvent& WXUNUSED(event))
{
    //Showing
    C->Menu_Option_Preferences_Option (_T("Verbosity"), _T("0.5"));
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Verbosity_10(wxCommandEvent& WXUNUSED(event))
{
    //Showing
    C->Menu_Option_Preferences_Option (_T("Verbosity"), _T("1"));
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_Summary(wxCommandEvent& WXUNUSED(event))
{
    //Showing
    GUI_Help_Summary* Frame=new GUI_Help_Summary(this);
    Frame->Show();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_ByFrame(wxCommandEvent& WXUNUSED(event))
{
    //Showing
    GUI_Help_ByFrame* Frame=new GUI_Help_ByFrame(this);
    Frame->Show();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_About(wxCommandEvent& WXUNUSED(event))
{
    //Showing
    GUI_About *About = new GUI_About(this, C->Menu_Help_Version().c_str());
    About->ShowModal();
    delete About;
}

//***************************************************************************
// ToolBar creation
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::ToolBar_Create()
{
    //ToolBar
    wxToolBar* ToolBar=CreateToolBar(wxTB_VERTICAL);
    ToolBar->SetToolBitmapSize(wxSize(32, 32));
    ToolBar->AddTool(ID_Menu_File_Open_Files, _T("Open &file(s)"), wxICON(File_Open_File));
    ToolBar->AddTool(ID_Menu_File_Open_Directory, _T("Open &directory"), wxICON(File_Open_Directory));
    ToolBar->AddSeparator();
    ToolBar->AddTool(wxID_ABOUT, _T("About"), wxICON(Help_About));
    ToolBar->Realize();
}
