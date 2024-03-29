// File_Latm - Info for LATM files
// Copyright (C) 2007-2008 Jerome Martinez, Zen@MediaArea.net
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
#ifndef MediaInfo_LatmH
#define MediaInfo_LatmH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_Latm
//***************************************************************************

class File_Latm : public File__Analyze
{
protected :
    //In
    bool audioMuxVersionA;

    //Information
    void HowTo (stream_t StreamKind);

public :
    File_Latm();

private :
    //Buffer
    bool Header_Begin();
    void Header_Parse();
    void Data_Parse();

    //Elements
    void AudioMuxElement(bool muxConfigPresent);
    void StreamMuxConfig();

    //Temp - Technical info

    //Helpers
    bool Synchronize();
};

} //NameSpace

#endif
