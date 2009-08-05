// GUI_Main_Text - WxWidgets GUI for MediaInfo
// Copyright (C) 2007-2009 Jerome Martinez, Zen@MediaArea.net
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
#include "GUI/WxWidgets/GUI_Main_Text.h"
#include "Common/Core.h"
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
GUI_Main_Text::GUI_Main_Text(Core* _C, wxWindow* parent)
    : wxTextCtrl(parent, -1, _T(""), wxPoint(0, 0), wxSize(parent->GetClientSize().GetWidth()-0, parent->GetClientSize().GetHeight()-0), wxTE_READONLY|wxTE_MULTILINE|wxTE_RICH|wxTE_RICH2|wxTE_DONTWRAP),
    GUI_Main_Common_Core(_C)
{
    wxFont Font;
    Font.SetFamily(wxFONTFAMILY_MODERN);
    wxTextAttr Attr;
    Attr.SetFont(Font);
    SetDefaultStyle(Attr);
}

//---------------------------------------------------------------------------
GUI_Main_Text::~GUI_Main_Text()
{
}

//***************************************************************************
// Actions
//***************************************************************************

void GUI_Main_Text::GUI_Resize()
{
    SetSize(0, 0, GetParent()->GetClientSize().GetWidth()-0, GetParent()->GetClientSize().GetHeight()-0);
}
