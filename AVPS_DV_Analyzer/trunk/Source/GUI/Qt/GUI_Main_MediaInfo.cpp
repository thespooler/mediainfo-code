// GUI_Main_Text_MediaInfo - 
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
#include "GUI/Qt/GUI_Main_MediaInfo.h"
#include "Common/Core.h"
#include "ZenLib/Ztring.h"
#include <QtGui/QLabel>
#include <QtCore/QEvent>
#include <QtGui/QFont>
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
GUI_Main_Text_MediaInfo::GUI_Main_Text_MediaInfo(Core* _C, QWidget* parent)
: QTextEdit(parent)
{
    //Internal
    C=_C;

    //Configuration
    setLineWrapMode(QTextEdit::NoWrap);
    setReadOnly(true);
}

//***************************************************************************
// Actions
//***************************************************************************

//---------------------------------------------------------------------------
bool GUI_Main_Text_MediaInfo::event (QEvent *Event) 
{
    if (Event->type()==QEvent::User)
    {
        //Showing
        clear();
        C->Menu_Option_Preferences_Option (_T("Inform"), _T("HTML"));
        //setPlainText(QString().fromUtf8(ZenLib::Ztring(C->MediaInfo()).To_UTF8().c_str()));
        setHtml (QString().fromUtf8(ZenLib::Ztring(C->MediaInfo()).To_UTF8().c_str()));
        C->Menu_Option_Preferences_Option (_T("Inform"), _T(""));

        Event->accept();
        return true;
    }

    return QTextEdit::event(Event);
}
