// File_Rar - Info for RAR files
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

//---------------------------------------------------------------------------
// Compilation conditions
#include <MediaInfo/Setup.h>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_RAR_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Archive/File_Rar.h"
#include "ZenLib/Utils.h"
using namespace ZenLib;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Format
//***************************************************************************

//---------------------------------------------------------------------------
void File_Rar::Read_Buffer_Continue()
{
    //Integrity
    if (Buffer_Size<=4)
        return;

    //Header
    if (CC4(Buffer)!=CC4("RAR!"))
    {
        Finnished();
        return;
    }

    //Filling
    Stream_Prepare(Stream_General);
    Fill(Stream_General, 0, General_Format, "RAR");

    //No need of more
    Finnished();
}

} //NameSpace

#endif //MEDIAINFO_RAR_YES
