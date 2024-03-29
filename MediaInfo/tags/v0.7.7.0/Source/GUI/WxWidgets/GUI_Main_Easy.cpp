// GUI_Main_Easy - WxWidgets GUI for MediaInfo
// Copyright (C) 2007-2008 Jerome Martinez, Zen@MediaArea.net
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
#include "GUI/WxWidgets/GUI_Main_Easy.h"
#include "GUI/WxWidgets/GUI_Main_Easy_Box.h"
#include "Common/Core.h"
#include <wx/choice.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/button.h>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
BEGIN_EVENT_TABLE(GUI_Main_Easy, wxChoice)
    EVT_CHOICE (26981, GUI_Main_Easy::OnChoice)
END_EVENT_TABLE()
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
GUI_Main_Easy::GUI_Main_Easy(Core* _C, wxWindow* parent)
    : wxPanel(parent, 26981, wxPoint(0, 0), wxSize(parent->GetClientSize().GetWidth()-0, parent->GetClientSize().GetHeight()-0)),
    GUI_Main_Easy_Core(_C)
{
    //Creation - Select
    Select=new wxChoice(this, 26981);

    //Creation - Other
    Boxes.resize(Stream_Max);
    for (size_t StreamPos=0; StreamPos<Stream_Max; StreamPos++)
    {
        Boxes[StreamPos].resize(Boxes_Count_Get(StreamPos));
        for (size_t Pos=0; Pos<Boxes[StreamPos].size(); Pos++)
            Boxes[StreamPos][Pos]=new GUI_Main_Easy_Box(C, this, Pos==0?NULL:Boxes[StreamPos][Pos-1], StreamPos==0?(wxWindow*)Select:(wxWindow*)Boxes[StreamPos-1][0], (stream_t)StreamPos, Pos);
    }

    //Update
    GUI_Resize();
    GUI_Refresh();
}

//---------------------------------------------------------------------------
GUI_Main_Easy::~GUI_Main_Easy()
{
    for (size_t StreamPos=0; StreamPos<Stream_Max; StreamPos++)
    {
        Boxes[StreamPos].resize(Boxes_Count_Get(StreamPos));
        for (size_t Pos=0; Pos<Boxes[StreamPos].size(); Pos++)
            delete Boxes[StreamPos][Pos]; //Boxes[StreamPos][Pos]=NULL;
    }
}

//***************************************************************************
// Actions
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main_Easy::GUI_Refresh()
{
    //The choice list
    Select->Clear();
    size_t FilesCount=FilesCount_Get();
    for (File_Pos=0; File_Pos<FilesCount; File_Pos++)
        Select->Append(FileName_Get().c_str());
    File_Pos=0;
    Select->SetSelection((int)File_Pos);

    GUI_Refresh_Partial();
}

//---------------------------------------------------------------------------
void GUI_Main_Easy::GUI_Refresh_Partial()
{
    //For each box
    for (size_t StreamPos=0; StreamPos<Stream_Max; StreamPos++)
        for (size_t Pos=0; Pos<Boxes[StreamPos].size(); Pos++)
            Boxes[StreamPos][Pos]->GUI_Refresh();

    //Resize some boxes if needed
    GUI_Resize_Partial();
}

//---------------------------------------------------------------------------
void GUI_Main_Easy::GUI_Resize()
{
    //Global and Select
    SetSize(0, 0, GetParent()->GetClientSize().GetWidth()-0, GetParent()->GetClientSize().GetHeight()-0);
    Select->SetSize(0, 0, GetClientSize().GetWidth(), Select->GetBestSize().GetHeight());

    //Other
    GUI_Resize_Partial();
}

//---------------------------------------------------------------------------
void GUI_Main_Easy::GUI_Resize_Partial()
{
    //For each box
    for (size_t StreamPos=0; StreamPos<Stream_Max; StreamPos++)
        for (size_t Pos=0; Pos<Boxes[StreamPos].size(); Pos++)
            Boxes[StreamPos][Pos]->GUI_Resize();
}

//***************************************************************************
// Events
//***************************************************************************

void GUI_Main_Easy::OnChoice(wxCommandEvent& event)
{
    File_Pos=Select->GetSelection();
    GUI_Refresh_Partial();
}

