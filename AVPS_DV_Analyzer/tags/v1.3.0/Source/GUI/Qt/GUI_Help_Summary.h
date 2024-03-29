// GUI_Help_Summary - WxWidgets GUI for MediaInfo
// Copyright (C) 2002-2009 Jerome Martinez, Zen@MediaArea.net
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
// WxWidgets GUI for MediaInfo
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef GUI_Help_SummaryH
#define GUI_Help_SummaryH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <QtGui/QDialog>
class QTextBrowser;
class QPushButton;
//---------------------------------------------------------------------------

//***************************************************************************
// GUI_Main
//***************************************************************************

class GUI_Help_Summary : public QDialog
{
    Q_OBJECT

public:
    GUI_Help_Summary (QWidget * parent);

private:
    //GUI
    QTextBrowser* Text;
    QPushButton*  Close;
};

#endif
