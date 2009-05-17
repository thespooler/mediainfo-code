// Main - Main functions
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
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "Common/Core.h"
#include "ZenLib/Ztring.h"
#include "ZenLib/File.h"
#include <sstream>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
ZenLib::Ztring Text_Temp;
using namespace ZenLib;
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
Core::Core()
{
    MI=new MediaInfoNameSpace::MediaInfoList;
    MI->Option(_T("ParseSpeed"), _T("1.000"));
    Errors_Stats_WithHeader=false;
    Errors_Stats_WithFooter=false;
}

Core::~Core()
{
    delete MI;
}

//---------------------------------------------------------------------------
void Core::Data_Prepare()
{
    //Inform
    Text=MI->Inform((size_t)-1).c_str();
}

//***************************************************************************
// Menu
//***************************************************************************

//---------------------------------------------------------------------------
size_t Core::Menu_File_Open_File (const String& FileName)
{
    Menu_File_Open_Files_Begin();
    return Menu_File_Open_Files_Continue(FileName);
}

//---------------------------------------------------------------------------
void Core::Menu_File_Open_Files_Begin ()
{
    MI->Close();
}

//---------------------------------------------------------------------------
size_t Core::Menu_File_Open_Files_Continue (const String &FileName)
{
    return MI->Open(FileName);
}

//---------------------------------------------------------------------------
void Core::Menu_File_Open_Directory (const String &DirectoryName)
{
    MI->Open(DirectoryName);
}

//---------------------------------------------------------------------------
void Core::Menu_Option_Preferences_Inform (const String& Inform)
{
    MI->Option(_T("Inform"), Inform);
}

//---------------------------------------------------------------------------
void Core::Menu_Option_Preferences_Option (const String& Param, const String& Value)
{
    MI->Option(Param, Value);
}

//---------------------------------------------------------------------------
void Core::Menu_Help_Version ()
{
    Text=MI->Option(_T("Info_Version"));
}

//***************************************************************************
// Helpers
//***************************************************************************

//---------------------------------------------------------------------------
String& Core::Inform_Get ()
{
    if (Text_Temp.empty())
        Text=MI->Inform();
    else
        Text=Text_Temp;
    return Text;
}

//---------------------------------------------------------------------------
String& Core::Errors_Stats_Get ()
{
    if (Text_Temp.empty())
    {
        Text.clear();
        
        size_t Count=MI->Count_Get();
        for (size_t Pos=0; Pos<Count; Pos++)
        {
            if (Errors_Stats_WithHeader)
            {
                Text+=MI->Get(Pos, Stream_General, 0, _T("CompleteName"))+_T('\n');
                Text+=_T('\n');
                Text+=MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_Begin"))+_T('\n');
            }
            
            Text+=MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats"));
            
            if (Errors_Stats_WithFooter)
            {
                Text+=_T('\n');
                Text+=MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_End"))+_T('\n');
            }

            if (!MI->Get(Pos, Stream_Video, 0, _T("FrameCount")).empty() && MI->Get(Pos, Stream_Video, 0, _T("FrameCount"))!=MI->Get(Pos, Stream_Video, 0, _T("FrameCount_Speed")))
            {
                Text+=_T('\n');
                Text+=_T("Warning, frame count is maybe incoherant (reported by MediaInfo: ")+MI->Get(Pos, Stream_Video, 0, _T("FrameCount"))+_T(")\n");
            }
            if (Pos+1<Count)
            {
                Text+=_T('\n');
                Text+=_T("***************************************************************************\n");
                Text+=_T('\n');
            }
        }
        for (size_t Pos=0; Pos<Text.size(); Pos++)
            if (Text[Pos]==_T('&'))
                Text[Pos]=_T('\n');
    }
    else
        Text=Text_Temp;
    return Text;
}
