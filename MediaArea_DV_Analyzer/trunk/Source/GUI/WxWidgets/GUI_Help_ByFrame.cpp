// GUI_Help_ByFrame - 
// Copyright (C) 2009-2009 Jerome Martinez, Zen@MediaArea.net
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
#include "GUI/WxWidgets/GUI_Help_ByFrame.h"
#include "Common/Core.h"
#include "Common/Help.h"
#include <wx/textctrl.h>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
BEGIN_EVENT_TABLE(GUI_Help_ByFrame, wxDialog)
    //GUI
    EVT_SIZE(                               GUI_Help_ByFrame::OnSize)
END_EVENT_TABLE()

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
GUI_Help_ByFrame::GUI_Help_ByFrame(wxWindow* parent)
:wxDialog(parent, -1, _T("DV Analyzer - Help - \"By frame\" format"), wxPoint(10, 10), wxSize(300, 400))
{
    //Update
    Text=new wxTextCtrl(this, -1, wxString::FromAscii(Help_ByFrame_Format().c_str()), wxPoint(0, 0), wxSize(GetClientSize().GetWidth(), GetClientSize().GetHeight()), wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH2|wxTE_AUTO_URL);
}

//***************************************************************************
// Events
//***************************************************************************

void GUI_Help_ByFrame::OnSize(wxSizeEvent& WXUNUSED(event))
{
    Text->SetSize(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight());
}
