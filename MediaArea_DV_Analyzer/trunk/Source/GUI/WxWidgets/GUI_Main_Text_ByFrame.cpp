// GUI_Main_Text_ByFrame - 
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
#include "GUI/WxWidgets/GUI_Main_Text_ByFrame.h"
#include "Common/Core.h"
#include "Common/Core.h"
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
GUI_Main_Text_ByFrame::GUI_Main_Text_ByFrame(Core* _C, wxWindow* parent)
: GUI_Main_Text(_C, parent)
{
    //Update
    GUI_Refresh();
}

//***************************************************************************
// Actions
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main_Text_ByFrame::GUI_Refresh()
{
    //Showing
    Clear();
    WriteText(C->ByFrame().c_str());
}
