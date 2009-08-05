// GUI_Help_ByFrame - 
// Copyright (C) 2009-2009 Jerome Martinez, Zen@MediaArea.net
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef GUI_Help_ByFrameH
#define GUI_Help_ByFrameH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "wx/dialog.h"
class wxTextCtrl;
//---------------------------------------------------------------------------

//***************************************************************************
// GUI_Help_ByFrame
//***************************************************************************

class GUI_Help_ByFrame : public wxDialog
{
public:
    //Constructor/Destructor
    GUI_Help_ByFrame(wxWindow *parent);
    
private:
    //GUI
    wxTextCtrl* Text;

    //Events
    void OnSize (wxSizeEvent &event);

    //wxWidgets
    DECLARE_EVENT_TABLE() //Any class wishing to process wxWindows events must use this macro
};

#endif
