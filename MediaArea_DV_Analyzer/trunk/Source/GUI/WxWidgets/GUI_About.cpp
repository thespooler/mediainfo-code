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

//---------------------------------------------------------------------------
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#include "GUI/WxWidgets/GUI_About.h"
#include "Ressource/Image/AVPS_logo_sign_alpha.xpm"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef __WXMSW__
    #include "Ressource/Image/MediaInfo.xpm"
#endif
//---------------------------------------------------------------------------

BEGIN_EVENT_TABLE(GUI_About, wxDialog)
    EVT_PAINT(GUI_About::OnPaint)
    EVT_SIZE(GUI_About::OnSize)

    //Button
    EVT_BUTTON(28002, GUI_About::Button_Description_OnClick)
    EVT_BUTTON(28003, GUI_About::Button_TechnicalSynopsis_OnClick)
    EVT_BUTTON(28004, GUI_About::Button_AuthorLicense_OnClick)
    EVT_BUTTON(28005, GUI_About::Button_Close_OnClick)
END_EVENT_TABLE()

const char* Description_Text=
"DESCRIPTION\n"
"\n"
"DV Analyzer provide two primary services simultaneously:\n"
"\n"
"Error Detection and Quality Control\n"
"\n"
"The digitization of DV tapes (such as miniDV, DVCam, and DVCPro) to file-based DV content for preservation is a fixed point in the content's lifespan when the introduction of errors is particularly high. Most digitization tools for DV content only report on errors if they are significant, such as a lost frame, whereas other documented errors are not reviewed. This tool, dvanalyzer, is meant to provide a way to analyze the resulting files from digitization in order to evaluate the accuracy of the transfer and verify the work.\n"
"\n"
"Temporal Metadata Reporting\n"
"\n"
"The DV format is rich is temporal metadata, every frame contains a timecode, recording date and time information, recording markers, etc. dvanalyzer reports on these values file so that recording info and timecode can be summarized throughout the file. This is particularly useful in documenting source material of edited DV content.\n"
;
const char* TechnicalSynopsis_Text=
"TECHNICAL SYNOPSIS\n"
"\n"
"DV Analyzer is a technical quality control tool that examines dv streams in order to detect errors in the tape-to-file transfer process, such as video error concealment, invalid audio samples, timecode inconsistancy, inconsistant use of arbitrary bits in video DIF blocks, and DIF structural problems.\n"
"\n"
"DV Analyzer also reports on patterns within dv streams such as changes in dv timecode, changes in recording date and time markers, first and last frame markers within individual recordings, and\n"
;
const char* AuthorLicense_Text=
"AUTHOR and LICENSE\n"
"\n"
"DV Analyzer was developed for AudioVisual Preservation Solutions (AVPS).\n"
"Copyright (C) 2009 AudioVisual Preservation Solutions. All rights reserved.\n"
"\n"
"Please report bugs and suggestions to <info@avpreserve.com>\n"
"\n"
"This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n"
"\n"
"This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.\n"
"\n"
"You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.\n"
;
const char* Websites_Text=
"Developed for AVPS http://www.avpreserve.com\n"
"by MediaArea.net http://mediainfo.sourceforge.net"
;

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
// Constructor
GUI_About::GUI_About(wxWindow* parent, const wxString& NameVersion_)
:wxDialog(parent, 28001, wxString(), wxPoint(100, 100), wxSize(550, 460), wxBORDER_RAISED)
{
    //Set the frame icon
    #ifdef WIN32 //Win32 use the first icon as file icon
        SetIcon(wxICON(aaaaaaaa));
    #else
        SetIcon(wxICON(MediaInfo));
    #endif

    //GUI
    CenterOnScreen();

    //Logo
    Logo_Bitmap=new wxBitmap(AVPS_logo_sign_alpha_xpm);

    //Button
    Button_Description=new wxButton (this, 28002, wxString::FromAscii("Description"));
    Button_TechnicalSynopsis=new wxButton (this, 28003, wxString::FromAscii("Technical Synopsis"));
    Button_AuthorLicense=new wxButton (this, 28004, wxString::FromAscii("Author and License"));
    Button_Close=new wxButton (this, 28005, wxString::FromAscii("Close"));
    Button_Description->SetSize      (  5,  10, 110, 30);
    Button_TechnicalSynopsis->SetSize(  5,  50, 110, 30);
    Button_AuthorLicense->SetSize    (  5,  90, 110, 30);
    Button_Close->SetSize    (GetClientSize().GetWidth()-110, GetClientSize().GetHeight()-40, 100, 30);

    //Text
    NameVersion=new wxTextCtrl(this, -1, NameVersion_, wxPoint(120, 0), wxSize(GetClientSize().GetWidth()-120, 20), wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH2|wxTE_AUTO_URL);
    NameVersion->SetBackgroundColour(GetBackgroundColour());
    Text=new wxTextCtrl(this, -1, wxString::FromAscii(Description_Text), wxPoint(120, 30), wxSize(GetClientSize().GetWidth()-120, GetClientSize().GetHeight()-30-50), wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH2|wxTE_AUTO_URL);
    Text->SetBackgroundColour(GetBackgroundColour());
    Websites=new wxTextCtrl(this, -1, _T(""), wxPoint(120, GetClientSize().GetHeight()-40), wxSize(GetClientSize().GetWidth()-120-120, 30), wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH2|wxTE_AUTO_URL);
    Websites->AppendText(wxString::FromAscii(Websites_Text));
    Websites->SetBackgroundColour(GetBackgroundColour());

    //Initial config
    Button_Description->Disable();

    //Font
    #ifdef __WXMAC__
        wxFont Font;
        Font.SetFamily(wxFONTFAMILY_MODERN);
        Button_Description->SetFont(Font);
        Button_TechnicalSynopsis->SetFont(Font);
        Button_AuthorLicense->SetFont(Font);
        Button_Close->SetFont(Font);
        NameVersion->SetFont(Font);
        Text->SetFont(Font);
        Websites->SetFont(Font);
    #endif //__WXMAC__
}

//---------------------------------------------------------------------------
GUI_About::~GUI_About()
{
    delete Logo_Bitmap;
}

//***************************************************************************
// Events
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_About::OnSize(wxSizeEvent& WXUNUSED(event))
{
}

//---------------------------------------------------------------------------
void GUI_About::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    dc.DrawBitmap(*Logo_Bitmap, 0, 140, true);
}

//---------------------------------------------------------------------------
void GUI_About::Button_Description_OnClick(wxCommandEvent& WXUNUSED(event))
{
    Text->Clear();
    Text->AppendText(wxString::FromAscii(Description_Text));
    Button_Description->Disable();
    Button_TechnicalSynopsis->Enable();
    Button_AuthorLicense->Enable();
}

//---------------------------------------------------------------------------
void GUI_About::Button_TechnicalSynopsis_OnClick(wxCommandEvent&WXUNUSED(event))
{
    Text->Clear();
    Text->AppendText(wxString::FromAscii(TechnicalSynopsis_Text));
    Button_Description->Enable();
    Button_TechnicalSynopsis->Disable();
    Button_AuthorLicense->Enable();
}

//---------------------------------------------------------------------------
void GUI_About::Button_AuthorLicense_OnClick(wxCommandEvent&WXUNUSED(event))
{
    Text->Clear();
    Text->AppendText(wxString::FromAscii(AuthorLicense_Text));
    Button_Description->Enable();
    Button_TechnicalSynopsis->Enable();
    Button_AuthorLicense->Disable();
}

//---------------------------------------------------------------------------
void GUI_About::Button_Close_OnClick(wxCommandEvent&WXUNUSED(event))
{
    Close();
}
