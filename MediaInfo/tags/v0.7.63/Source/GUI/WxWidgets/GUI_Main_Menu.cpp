/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license that can
 *  be found in the License.html file in the root of the source tree.
 */

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
#include "GUI/WxWidgets/GUI_Main_Easy.h"
#include "GUI/WxWidgets/GUI_Main_Sheet.h"
#include "GUI/WxWidgets/GUI_Main_Tree.h"
#include "GUI/WxWidgets/GUI_Main_HTML.h"
#include "GUI/WxWidgets/GUI_Main_Text.h"
#include "Common/Core.h"
#include <wx/image.h>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//Old Wx
#ifndef wxFD_OPEN
    #define wxFD_OPEN wxOPEN
#endif
#ifndef wxFD_FILE_MUST_EXIST
    #define wxFD_FILE_MUST_EXIST wxFILE_MUST_EXIST
#endif
#ifndef wxFD_MULTIPLE
    #define wxFD_MULTIPLE wxMULTIPLE
#endif
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
    ID_Menu_View_Easy,
    ID_Menu_View_Sheet,
    ID_Menu_View_Tree,
    ID_Menu_View_HTML,
    ID_Menu_View_Text,
    ID_Menu_Debug_Complete,
    ID_Menu_Debug_Details,
    ID_Menu_Debug_Demux,
    ID_Menu_Debug_Demux_None,
    ID_Menu_Debug_Demux_Elementary,
    ID_Menu_Debug_Demux_All,
    ID_Menu_Help_Info_Formats,
    ID_Menu_Help_Info_Codecs,
    ID_Menu_Help_Info_Parameters,
};

//---------------------------------------------------------------------------
BEGIN_EVENT_TABLE(GUI_Main, wxFrame)
    //Menu
    EVT_MENU(ID_Menu_File_Open_Files,       GUI_Main::OnMenu_File_Open_Files)
    EVT_MENU(ID_Menu_File_Open_Directory,   GUI_Main::OnMenu_File_Open_Directory)
    EVT_MENU(wxID_EXIT,                     GUI_Main::OnMenu_File_Quit)
    EVT_MENU(ID_Menu_View_Easy,             GUI_Main::OnMenu_View_Easy)
    EVT_MENU(ID_Menu_View_Sheet,            GUI_Main::OnMenu_View_Sheet)
    EVT_MENU(ID_Menu_View_Tree,             GUI_Main::OnMenu_View_Tree)
    EVT_MENU(ID_Menu_View_HTML,             GUI_Main::OnMenu_View_HTML)
    EVT_MENU(ID_Menu_View_Text,             GUI_Main::OnMenu_View_Text)
    EVT_MENU(ID_Menu_Debug_Complete,        GUI_Main::OnMenu_Debug_Complete)
    EVT_MENU(ID_Menu_Debug_Details,         GUI_Main::OnMenu_Debug_Details)
    EVT_MENU(ID_Menu_Debug_Demux_None,      GUI_Main::OnMenu_Debug_Demux_None)
    EVT_MENU(ID_Menu_Debug_Demux_Elementary,GUI_Main::OnMenu_Debug_Demux_Elementary)
    EVT_MENU(ID_Menu_Debug_Demux_All,       GUI_Main::OnMenu_Debug_Demux_All)
    EVT_MENU(wxID_ABOUT,                    GUI_Main::OnMenu_Help_About)
    EVT_MENU(ID_Menu_Help_Info_Formats,     GUI_Main::OnMenu_Help_Info_Formats)
    EVT_MENU(ID_Menu_Help_Info_Codecs,      GUI_Main::OnMenu_Help_Info_Codecs)
    EVT_MENU(ID_Menu_Help_Info_Parameters,  GUI_Main::OnMenu_Help_Info_Parameters)

    //GUI
    EVT_SIZE(                               GUI_Main::OnSize)
END_EVENT_TABLE()

//---------------------------------------------------------------------------
#ifndef __WXMSW__
    #include "Resource/Image/Menu/K20/File_Open_File.xpm"
    #include "Resource/Image/Menu/K20/File_Open_Directory.xpm"
    #include "Resource/Image/Menu/K20/Help_About.xpm"
#endif

//***************************************************************************
// Menu creation
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::Menu_Create()
{
    //File - Open
    Menu_File_Open              =new wxMenu;
    Menu_File_Open_Files        =Menu_File_Open->Append(ID_Menu_File_Open_Files, __T("Open &file(s)"));
    Menu_File_Open_Directory    =Menu_File_Open->Append(ID_Menu_File_Open_Directory, __T("Open &directory"));

    //File
    Menu_File=new wxMenu;
                                 Menu_File->Append(ID_Menu_File_Open, __T("Open"), Menu_File_Open);
                                 Menu_File->AppendSeparator();
    Menu_File_Quit              =Menu_File->Append(wxID_EXIT, __T("E&xit\tAlt-X"), __T("Quit this program"));

    //View
    Menu_View                   =new wxMenu;
    Menu_View_Easy              =Menu_View->AppendRadioItem(ID_Menu_View_Easy, __T("Easy"), __T("Easy view"));
    Menu_View_Sheet             =Menu_View->AppendRadioItem(ID_Menu_View_Sheet, __T("Sheet"), __T("Sheet view"));
    Menu_View_Tree              =Menu_View->AppendRadioItem(ID_Menu_View_Tree, __T("Tree"), __T("Tree view"));
    Menu_View_HTML              =Menu_View->AppendRadioItem(ID_Menu_View_HTML, __T("HTML"), __T("HTML view"));
    Menu_View_Text              =Menu_View->AppendRadioItem(ID_Menu_View_Text, __T("Text"), __T("Text view"));

    //Debug - Demux
    Menu_Debug_Demux            =new wxMenu;
    Menu_Debug_Demux_None       =Menu_Debug_Demux->AppendRadioItem(ID_Menu_Debug_Demux_None, __T("No demux"));
    Menu_Debug_Demux_Elementary =Menu_Debug_Demux->AppendRadioItem(ID_Menu_Debug_Demux_Elementary, __T("Elementary streams only"));
    Menu_Debug_Demux_All        =Menu_Debug_Demux->AppendRadioItem(ID_Menu_Debug_Demux_All, __T("All streams"));

    //Debug
    Menu_Debug                  =new wxMenu;
    Menu_Debug_Complete         =Menu_Debug->AppendCheckItem(ID_Menu_Debug_Complete, __T("Complete"), __T("Complete"));
    Menu_Debug_Details          =Menu_Debug->AppendCheckItem(ID_Menu_Debug_Details, __T("Details"), __T("Details text view"));
                                 Menu_Debug->Append(ID_Menu_Debug_Demux, __T("Demux"), Menu_Debug_Demux);

    //Help
    Menu_Help                   =new wxMenu;
    Menu_Help_About             =Menu_Help->Append(wxID_ABOUT, __T("&About...\tF1"), __T("Show about dialog"));
                                 Menu_Help->AppendSeparator();
    Menu_Help_Info_Formats      =Menu_Help->Append(ID_Menu_Help_Info_Formats, __T("Known formats"));
    Menu_Help_Info_Codecs       =Menu_Help->Append(ID_Menu_Help_Info_Codecs, __T("Known codecs"));
    Menu_Help_Info_Parameters   =Menu_Help->Append(ID_Menu_Help_Info_Parameters, __T("Known parameters"));

    //Main
    Menu=new wxMenuBar();
    Menu->Append(Menu_File,     __T("&File"));
    Menu->Append(Menu_View,     __T("&View"));
    Menu->Append(Menu_Debug,    __T("&Debug"));
    Menu->Append(Menu_Help,     __T("&Help"));
    SetMenuBar(Menu);
}

//***************************************************************************
// Menu actions
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_File_Open_Files(wxCommandEvent& WXUNUSED(event))
{
    //User interaction
    wxFileDialog* Dialog=new wxFileDialog(this, __T("Choose a file"), __T(""), __T(""), __T("*.*"), wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);
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
        C->Menu_File_Open_Files_Continue(String(FileNames[Pos].c_str()));

    //Showing
    View->GUI_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_File_Open_Directory(wxCommandEvent& WXUNUSED(event))
{
    //User interaction
    wxDirDialog* Dialog=new wxDirDialog(this, __T("Choose a directory"));
    if (Dialog->ShowModal()!=wxID_OK)
        return;
    wxString DirName=Dialog->GetPath();
    delete Dialog;

    //Configuring
    C->Menu_File_Open_Files_Begin();
    C->Menu_File_Open_Files_Continue(String(DirName.c_str()));

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
void GUI_Main::OnMenu_View_Easy(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_View_Easy();

    //Showing
    GUI_Main_Common_Core* View_New=new GUI_Main_Easy(C, this);
    delete View; View=View_New;
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_Sheet(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_View_Sheet();

    //Showing
    GUI_Main_Common_Core* View_New=new GUI_Main_Sheet(C, this);
    delete View; View=View_New;
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_Tree(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_View_Tree();

    //Showing
    GUI_Main_Common_Core* View_New=new GUI_Main_Tree(C, this);
    delete View; View=View_New;
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_HTML(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_View_HTML();

    //Showing
    GUI_Main_Common_Core* View_New=new GUI_Main_HTML(C, this);
    delete View; View=View_New;
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_View_Text(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_View_Text();

    //Showing
    GUI_Main_Common_Core* View_New=new GUI_Main_Text(C, this);
    delete View; View=View_New;
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Debug_Complete(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_Debug_Complete(Menu_Debug_Complete->IsChecked());

    //Showing
    View->GUI_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Debug_Details(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    if (Menu_Debug_Details->IsChecked())
        C->Menu_Debug_Details(1);
    else
        C->Menu_Debug_Details(0);

    //Showing - Menu
    Menu_View_Easy->Enable (!Menu_Debug_Details->IsChecked());
    Menu_View_Sheet->Enable(false);//!Menu_Debug_Details->IsChecked());
    Menu_View_Tree->Enable (Menu_Debug_Details->IsChecked());
    Menu_View_HTML->Enable (!Menu_Debug_Details->IsChecked());
    Menu_View_Text->Enable (true);

    //Showing - View
    if (Menu_Debug_Details->IsChecked() && (!Menu_View_Tree->IsChecked() && !Menu_View_Text->IsChecked()))
    {
        Menu_View_Tree->Check();
        OnMenu_View_Tree(*((wxCommandEvent*)NULL));
    }
    if (!Menu_Debug_Details->IsChecked() && (!Menu_View_HTML->IsChecked() && !Menu_View_Text->IsChecked()))
    {
        Menu_View_HTML->Check();
        OnMenu_View_HTML(*((wxCommandEvent*)NULL));
    }
    else
        View->GUI_Refresh();
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Debug_Demux_None(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_Debug_Demux(__T(""));
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Debug_Demux_Elementary(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_Debug_Demux(__T("1"));
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Debug_Demux_All(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_Debug_Demux(__T("All"));
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_About(wxCommandEvent& WXUNUSED(event))
{
    //Showing
    wxString Version=C->Menu_Option_Preferences_Option(__T("Info_Version"), __T("")).c_str();
    wxMessageBox(__T("This is the About dialog of the minimal MediaInfo sample.\n")+Version+__T("\nMediaInfo supplies technical and tag information about \na video or audio file.\nTo get more info's visit \nhttp://mediainfo.sourceforge.net"), __T("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_Info_Formats(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_Help_Info_Formats();

    //Showing
    OnMenu_View_Text(*((wxCommandEvent*)NULL));
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_Info_Codecs(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_Help_Info_Codecs();

    //Showing
    OnMenu_View_Text(*((wxCommandEvent*)NULL));
}

//---------------------------------------------------------------------------
void GUI_Main::OnMenu_Help_Info_Parameters(wxCommandEvent& WXUNUSED(event))
{
    //Configuring
    C->Menu_Help_Info_Parameters();

    //Showing
    OnMenu_View_Text(*((wxCommandEvent*)NULL));
}

//***************************************************************************
// ToolBar creation
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main::ToolBar_Create()
{
    //ToolBar
    wxToolBar* ToolBar=CreateToolBar(wxTB_VERTICAL);
    #if wxUSE_DRAG_AND_DROP && defined(__WXMAC__)
        ToolBar->SetDropTarget(new FileDrop(C));
    #endif //wxUSE_DRAG_AND_DROP
    ToolBar->SetToolBitmapSize(wxSize(32, 32));
    ToolBar->AddTool(ID_Menu_File_Open_Files, __T("Open &file(s)"), wxICON(File_Open_File));
    ToolBar->AddTool(ID_Menu_File_Open_Directory, __T("Open &directory"), wxICON(File_Open_Directory));
    ToolBar->AddSeparator();
    ToolBar->AddTool(wxID_ABOUT, __T("About"), wxICON(Help_About));
    ToolBar->Realize();
}
