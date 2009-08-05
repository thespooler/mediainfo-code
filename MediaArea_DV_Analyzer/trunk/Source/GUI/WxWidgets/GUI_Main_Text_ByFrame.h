// GUI_Main_Text_ByFrame - 
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
#ifndef GUI_Main_Text_ByFrameH
#define GUI_Main_Text_ByFrameH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "GUI/WxWidgets/GUI_Main_Text.h"
//---------------------------------------------------------------------------

//***************************************************************************
// GUI_Main_Text_ByFrame
//***************************************************************************

class GUI_Main_Text_ByFrame : public GUI_Main_Text
{
public:
    //Constructor/Destructor
    GUI_Main_Text_ByFrame(Core* C, wxWindow *parent);

    //Actions
    void GUI_Refresh();
};

#endif
