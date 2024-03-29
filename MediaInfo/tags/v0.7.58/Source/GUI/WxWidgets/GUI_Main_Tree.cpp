// GUI_Main_Tree - WxWidgets GUI for MediaInfo
// Copyright (C) 2002-2012 MediaArea.net SARL, Info@MediaArea.net
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
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
#include "GUI/WxWidgets/GUI_Main_Tree.h"
#include "Common/Core.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
BEGIN_EVENT_TABLE(GUI_Main_Tree, wxTreeCtrl)
    EVT_TREE_ITEM_EXPANDING (26983, GUI_Main_Tree::OnItemExpanding)
    EVT_TREE_ITEM_COLLAPSING(26983, GUI_Main_Tree::OnItemCollapsing)
END_EVENT_TABLE()
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
GUI_Main_Tree::GUI_Main_Tree(Core* _C, wxWindow* parent)
        : wxTreeCtrl(parent, 26983, wxPoint(0, 0), wxSize(parent->GetClientSize().GetWidth()-0, parent->GetClientSize().GetHeight()-0)),
        GUI_Main_Common_Core(_C)
{
    //Update
    GUI_Refresh();
}

//---------------------------------------------------------------------------
GUI_Main_Tree::~GUI_Main_Tree()
{
    Hide();

    DeleteAllItems();
    TextPos.clear();
}

//***************************************************************************
// Actions
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main_Tree::GUI_Refresh()
{
    Hide();

    //Retrieving info
    Text=C->Inform_Get();

    //Clear
    DeleteAllItems();
    TextPos.clear();

    //Showing
    if (!Text.empty())
    {
        SetWindowStyle(wxTR_HIDE_ROOT);
        wxTreeItemId RootID=AddRoot(wxT("Root"));
        TextPos[RootID.m_pItem]=(size_t)-1;
        Item_Show(RootID);
    }

    Show();
}

void GUI_Main_Tree::GUI_Resize()
{
    SetSize(0, 0, GetParent()->GetClientSize().GetWidth()-0, GetParent()->GetClientSize().GetHeight()-0);
}

//---------------------------------------------------------------------------
void GUI_Main_Tree::Item_Show(const wxTreeItemId &Item)
{
    wxTreeItemId ItemID;
    //wxFont Font(8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    //wxFont Font(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    size_t Level=0;
    size_t Pos1=TextPos[Item.m_pItem];
    size_t Pos2=0;
    size_t LevelBase;
    if (Pos1!=(size_t)-1)
    {
        //Not the root level
        LevelBase=Text.find_first_not_of(_T(' '), Pos1+9)-(Pos1+9);
        Pos1=Text.find(_T('\n'), Pos1)+1;
    }
    else
    {
        //Root level
        LevelBase=(size_t)-1;
        Pos1=0;
    }
    while (Pos2!=(size_t)-1)
    {
        Pos2=Text.find(_T('\n'), Pos1); //Pos to the next line
        #ifdef WIN32
            #define SIZE 1
        #else
            #define SIZE 0
        #endif
        Level=Text.find_first_not_of(_T(' '), Pos1+9)-(Pos1+9);
        if (Level==LevelBase+1)
        {
            //Showing line
            String Line=Text.substr(Pos1, Pos2-Pos1-SIZE);
            if (Line.size()>10 && Line[9]==_T(' '))
            {
                Line.erase(9, Level);
            }
            if (!Line.empty())
            {
                ItemID=AppendItem(Item, Line.c_str());
                TextPos[ItemID.m_pItem]=Pos1;
                //SetItemFont(ItemID, Font);
            }
        }
        else if (Level==LevelBase+2)
            SetItemHasChildren(ItemID); //SubLevel elements detected, we are showing the availability of childrens
        else if (Level<=LevelBase && LevelBase!=(size_t)-1) //This is an upper level, finnished (except for root level, there is no upper level)
            Pos2=(size_t)-1;
        Pos1=Pos2+1;
    }
}

//***************************************************************************
// Events
//***************************************************************************

void GUI_Main_Tree::OnItemExpanding(wxTreeEvent& event)
{
    Item_Show(event.GetItem());
}

void GUI_Main_Tree::OnItemCollapsing(wxTreeEvent& event)
{
    CollapseAndReset(event.GetItem());
    SetItemHasChildren(event.GetItem());
}
