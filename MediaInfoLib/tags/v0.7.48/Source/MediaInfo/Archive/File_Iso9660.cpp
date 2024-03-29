// File_Iso9660 - Info for Iso9660 files
// Copyright (C) 2005-2011 MediaArea.net SARL, Info@MediaArea.net
//
// This library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
// Pre-compilation
#include "MediaInfo/PreComp.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Setup.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_7Z_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Archive/File_Iso9660.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// File header
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Iso9660::FileHeader_Begin()
{
    //Element_Size
    if (Buffer_Size<65536)
        return false; //Must wait for more data

    if (CC6(Buffer+32768)!=0x014344303031LL) //"Iso9660...."
    {
        Reject("ISO 9660");
        return false;
    }

    //All should be OK...
    Accept("ISO 9660");
    return true;
}

//***************************************************************************
// Buffer - Global
//***************************************************************************

//---------------------------------------------------------------------------
void File_Iso9660::Read_Buffer_Continue()
{
    Skip_XX(32768,                                              "System Area");
    Primary_Volume_Descriptor();

    FILLING_BEGIN();
        Fill(Stream_General, 0, General_Format, "ISO 9660");

        Finish("ISO 9660");
    FILLING_END();
}

//***************************************************************************
// Elements
//***************************************************************************

//---------------------------------------------------------------------------
void File_Iso9660::Primary_Volume_Descriptor()
{
    int32u Volume_Space_Size;
    Element_Begin("Volume_Descriptor");
    Skip_B1("Volume Descriptor Type");
    Skip_Local(5,"Standard Identifier");
    Skip_B1("Volume Descriptor Version");
    Skip_B1("Unused field");
    Skip_Local(32,"System Identifier");
    Skip_Local(32,"Volume Identifier");
    Skip_XX(8,"Unused field");
    Get_D4(Volume_Space_Size,                                   "Volume Space Size"); Param_Info(Volume_Space_Size*(int64u)2048, " bytes");
    Skip_XX(32,"Unused field");
    Skip_B4("Volume Set Size");
    Skip_B4("Volume Sequence Number");
    Skip_B4("Logical Block Size");
    Skip_B8("Path Table Size");
    Skip_B4("Location of Occurrence of Type L Path Table");
    Skip_B4("Location of Optional Occurrence of Type L Path Table");
    Skip_B4("Location of Occurrence of Type M Path Table");
    Skip_B4("Location of Optional Occurrence of Type M Path Table");
    Skip_Local(34,"Directory Record for Root Directory");
    Skip_Local(128,"Volume Set Identifier");
    Skip_Local(128,"Publisher Identifier");
    Skip_Local(128,"Data Preparer Identifier");
    Skip_Local(128,"Application Identifier");
    Skip_Local(37,"Copyright File Identifier");
    Skip_Local(37,"Abstract File Identifier");
    Skip_Local(37,"Bibliographic File Identifier");
    Skip_XX(17,"Volume Creation Date and Time");
    Element_End();
}

} //NameSpace

#endif //MEDIAINFO_7Z_YES
