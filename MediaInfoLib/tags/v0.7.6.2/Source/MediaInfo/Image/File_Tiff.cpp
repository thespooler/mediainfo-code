// File_Tiff - Info for TIFF files
// Copyright (C) 2005-2008 Jerome Martinez, Zen@MediaArea.net
//
// This library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// TIFF - Format
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// From http://www.fileformat.info/format/tiff/
//
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
// Compilation conditions
#include <MediaInfo/Setup.h>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_TIFF_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Image/File_Tiff.h"
#include "ZenLib/Utils.h"
using namespace ZenLib;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Format
//***************************************************************************

//---------------------------------------------------------------------------
void File_Tiff::Read_Buffer_Continue()
{
    //Integrity
    if (Buffer_Size<4)
        return;

    //Header
    if (CC4(Buffer)!=0x49492A00 && CC4(Buffer)!=0x4D4D002A)
    {
        Finnished();
        return;
    }

    //Filling
    Stream_Prepare(Stream_General);
    Fill("Format", "TIFF");
    Stream_Prepare(Stream_Image);
    Fill("Codec", "TIFF");

    //No need of more
    Finnished();
}

//***************************************************************************
// Information
//***************************************************************************

//---------------------------------------------------------------------------
void File_Tiff::HowTo(stream_t StreamKind)
{
    switch (StreamKind)
    {
        case (Stream_General) :
            Fill_HowTo("Format", "R");
            break;
        case (Stream_Video) :
            break;
        case (Stream_Audio) :
            break;
        case (Stream_Text) :
            break;
        case (Stream_Chapters) :
            break;
        case (Stream_Image) :
            break;
        case (Stream_Menu) :
            break;
        case (Stream_Max) :
            break;
    }
}

} //NameSpace

#endif
