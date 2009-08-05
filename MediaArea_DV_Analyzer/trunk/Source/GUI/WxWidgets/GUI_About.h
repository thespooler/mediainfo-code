// GUI_About - WxWidgets About box
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
//
// WxWidgets About box
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef GUI_AboutH
#define GUI_AboutH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "wx/dialog.h"
#include "wx/image.h"
#include "wx/textctrl.h"
#include <wx/button.h>
//---------------------------------------------------------------------------

//***************************************************************************
// GUI_About
//***************************************************************************

class GUI_About : public wxDialog
{
public:
    GUI_About (wxWindow* parent, const wxString& NameVersion);
    ~GUI_About ();

private:
    //
    wxBitmap* Logo_Bitmap;
    wxTextCtrl* NameVersion;
    wxTextCtrl* Text;
    wxTextCtrl* Websites;
    wxButton*   Button_Description;
    wxButton*   Button_TechnicalSynopsis;
    wxButton*   Button_AuthorLicense;
    wxButton*   Button_Close;

    //Events
    void OnPaint(wxPaintEvent &event);
    void OnSize (wxSizeEvent  &event);
    void Button_Description_OnClick(wxCommandEvent &event);
    void Button_TechnicalSynopsis_OnClick(wxCommandEvent &event);
    void Button_AuthorLicense_OnClick(wxCommandEvent &event);
    void Button_Close_OnClick(wxCommandEvent &event);

    //wxWidgets
    DECLARE_EVENT_TABLE() //Any class wishing to process wxWindows events must use this macro
};

#endif
