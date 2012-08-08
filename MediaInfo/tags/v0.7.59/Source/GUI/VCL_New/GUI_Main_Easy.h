// GUI_Main_Easy - VCL GUI for MediaInfo
// Copyright (C) 2002-2012 MediaArea.net SARL, Info@MediaArea.net
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU Library General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Borland VCL GUI for MediaInfo, Text Part
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef GUI_Main_Easy_H
#define GUI_Main_Easy_H
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "GUI/Common/GUI_Main_Common_Core.h"
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <OleCtrls.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
#include <vector>
//---------------------------------------------------------------------------

//***************************************************************************
// GUI_Main_Easy
//***************************************************************************

class GUI_Main_Easy : public GUI_Main_Common_Core
{
public:
    //Constructor/Destructor
    GUI_Main_Easy(Core* C, TWinControl* Owner);
    ~GUI_Main_Easy();

    //Actions
    void GUI_Refresh();
    void GUI_Refresh_Partial();
    void GUI_Resize();
    void GUI_Resize_Partial();

private:
    //GUI
    TComboBox* Select;
    //std::vector<std::vector<GUI_Main_Easy_Box*> > Boxes;

    //Events
    //void OnChoice(wxCommandEvent& event);

private:
    TPanel* VCL;
};

#endif
