// File_Ac3 - Info for AC3 files
// Copyright (C) 2004-2008 Jerome Martinez, Zen@MediaArea.net
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
#ifndef MediaInfo_Ac3H
#define MediaInfo_Ac3H
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_Ac3
//***************************************************************************

class File_Ac3 : public File__Analyze
{
public :
    //Configuration
    size_t Frame_Count_Valid;

    //External info
    size_t Delay;

protected :
    //Information
    void HowTo (stream_t StreamKind);

public :
    File_Ac3();

private :
    //Buffer
    bool Header_Begin();
    void Header_Parse();
    void Data_Parse();
    void Data_Parse_Fill();

    //Temp - Global
    size_t Frame_Count;

    //Temp - Technical info
    int16u chanmap;
    int16u frmsiz;
    int8u  fscod;
    int8u  fscod2;
    int8u  frmsizecod;
    int8u  bsid;
    int8u  bsmod;
    int8u  acmod;
    int8u  dsurmod;
    int8u  numblks;
    bool   lfeon;

    //Helpers
    bool Synchronize();
};

} //NameSpace

#endif
