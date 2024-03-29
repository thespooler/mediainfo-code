// File_Ogg - Info for ogg files
// Copyright (C) 2002-2008 Jerome Martinez, Zen@MediaArea.net
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
//
// Information about Ogg files
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef MediaInfo_File_OggH
#define MediaInfo_File_OggH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
#include <map>
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_Ogg
//***************************************************************************

class File_Ogg : public File__Analyze
{
protected :
    //Formats
    void Read_Buffer_Finalize ();

    //Information
    void HowTo (stream_t StreamKind);

public :
    File_Ogg();

private :
    //Buffer
    bool Header_Begin();
    void Header_Parse();
    void Header_Parse_AdaptationField();
    void Data_Parse();

    //Temp - Global
    int32u StreamsToDo;
    bool   Parsing_End;

    //Temp - Stream
    struct stream
    {
        File__Analyze* Parser;
        stream_t StreamKind;
        size_t StreamPos;
        int64u absolute_granule_position;
        int64u absolute_granule_position_Resolution;

        stream()
        {
            Parser=NULL;
            StreamKind=Stream_Max;
            StreamPos=(size_t)-1;
            absolute_granule_position=0;
            absolute_granule_position_Resolution=0;
        }
        ~stream()
        {
            delete Parser; //Parser=NULL
        }
    };

    int8u packet_type;
    bool continued;
    bool continued_NextFrame;
    std::map<int64u, stream> Stream;
    std::vector<size_t>      Chunk_Sizes;
    bool                     Chunk_Sizes_Finnished;

    //Helpers
    bool   Synchronize();
};

} //NameSpace

#endif
