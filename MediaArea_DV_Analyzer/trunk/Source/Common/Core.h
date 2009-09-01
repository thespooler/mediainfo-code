// Core - Main functions
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
// Core functions
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef CoreH
#define CoreH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifdef MEDIAINFO_DLL
    #include "MediaInfoDLL/MediaInfoDLL.h"
    #define MediaInfoNameSpace MediaInfoDLL
#elif defined MEDIAINFO_STATIC
    #include "MediaInfoDLL/MediaInfoDLL_Static.h"
    #define MediaInfoNameSpace MediaInfoDLL
#else
    #include "MediaInfo/MediaInfoList.h"
    #define MediaInfoNameSpace MediaInfoLib
#endif
using namespace MediaInfoNameSpace;
//---------------------------------------------------------------------------

//***************************************************************************
// Class Core
//***************************************************************************

class Core
{
public:
    //Constructor/Destructor
    Core();
    ~Core();

    //Menu
    size_t                      Menu_File_Open_File             (const MediaInfoNameSpace::String &FileName);
    void                        Menu_File_Open_Files_Begin      ();
    size_t                      Menu_File_Open_Files_Continue   (const MediaInfoNameSpace::String &FileName);
    void                        Menu_File_Open_Directory        (const MediaInfoNameSpace::String &DirectoryName);
    void                        Menu_Option_Preferences_Option  (const MediaInfoNameSpace::String &Param, const MediaInfoNameSpace::String &Value);
    MediaInfoNameSpace::String &Menu_Help_Version               ();

    //Datas
    MediaInfoNameSpace::String &MediaInfo();
    MediaInfoNameSpace::String &ByFrame();
    MediaInfoNameSpace::String &Summary();
    bool Errors_Stats_WithHeader;
    bool Errors_Stats_WithFooter;

    //Temp
    void    Data_Prepare();
    MediaInfoNameSpace::String &Text_Get() {return Text;};
    void* GUI_Main_Handler;

protected:
    MediaInfoNameSpace::MediaInfoList* MI;
    MediaInfoNameSpace::String  Text;

    //Internal
    void Common_Footer(size_t Pos, size_t Count);
    void Common();
};

#endif
