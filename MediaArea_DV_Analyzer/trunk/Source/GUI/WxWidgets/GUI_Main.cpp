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
#include "GUI/WxWidgets/GUI_Main_Text_Summary.h"
#include "GUI/WxWidgets/GUI_Main_Text_ByFrame.h"
#include "GUI/WxWidgets/GUI_Main_Text_MediaInfo.h"
#include <vector>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef __WXMSW__
    #include "Ressource/Image/MediaInfo.xpm"
#endif
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
// Constructor
GUI_Main::GUI_Main(Core* _C, const wxPoint& pos, const wxSize& size, long style)
:wxFrame(NULL, -1, _T("DV Analyzer"), pos, size, style)
{
    //Set the frame icon
    #ifdef WIN32 //Win32 use the first icon as file icon
        SetIcon(wxICON(aaaaaaaa));
    #else
        SetIcon(wxICON(MediaInfo));
    #endif

    //Internal
    C=_C;
    C->GUI_Main_Handler=this;

    //Configure
    View_Current=View_Summary;
    MustCreate=true;

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
        FD=new FileDrop(C);
        SetDropTarget(FD);
    #endif //wxUSE_DRAG_AND_DROP

    //Defaults
    Menu_View_Summary->Check(); //Default to Footer with GUI.
    wxCommandEvent* EventTemp=new wxCommandEvent();
    OnMenu_View_Summary(*EventTemp);
    delete EventTemp; //This is done to be GCC-compatible...

    //GUI
    View_Refresh();
}

//---------------------------------------------------------------------------
GUI_Main::~GUI_Main()
{
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
        delete View; //View=NULL
        switch (View_Current)
        {
            case View_Summary      : View=new GUI_Main_Text_Summary     (C, this); MustCreate=false; break;
            case View_ByFrame      : View=new GUI_Main_Text_ByFrame     (C, this); MustCreate=false; break;
            case View_MediaInfo    : View=new GUI_Main_Text_MediaInfo   (C, this); MustCreate=false; break;
            default                : View=NULL;
        }
    }
    
    if (View)
        View->GUI_Refresh();
}
