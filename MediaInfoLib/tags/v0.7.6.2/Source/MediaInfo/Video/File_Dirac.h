// File_Dirac - Info for Dirac files
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
//
// Information about Dirac files
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef MediaInfo_File_DiracH
#define MediaInfo_File_DiracH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_Dirac
//***************************************************************************

class File_Dirac : public File__Analyze
{
public :
    //In
    size_t Frame_Count_Valid;

protected :
    //Format
    void Read_Buffer_Continue ();
    void Read_Buffer_Finalize ();

    //Information
    void HowTo (stream_t StreamKind);

public :
    File_Dirac();

private :
    //Buffer
    bool Header_Begin();
    void Header_Parse();
    bool Header_Parse_Fill_Size();
    void Data_Parse();

    //Packets
    void Sequence_header();
    void End_of_Sequence();
    void Auxiliary_data();
    void Padding_data();
    void Intra_Reference_Picture();
    void Intra_Non_Reference_Picture();
    void Intra_Reference_Picture_No();
    void Intra_Non_Reference_Picture_No();
    void Inter_Reference_Picture_1();
    void Inter_Reference_Picture_2();
    void Inter_Non_Reference_Picture_1();
    void Inter_Non_Reference_Picture_2();
    void Reference_Picture_Low();
    void Intra_Non_Reference_Picture_Low();
    void Reserved();
    void picture();
    void picture_Fill();

    //Streams
    struct stream
    {
        bool   Searching_Payload;

        stream()
        {
            Searching_Payload=false;
        }
    };
    std::map<int8u, stream> Stream;

    //Count of a Packets
    size_t Frame_Count;

    //Temp
    int32u frame_width;
    int32u frame_height;
    int32u chroma_format;
    int32u source_sampling;
    int32u clean_width;
    int32u clean_height;
    int32u clean_left_offset;
    int32u clean_top_offset;
    float32 frame_rate;
    float32 pixel_aspect_ratio;

    //Helpers
    bool Synchronize();
    bool Header_Parser_QuickSearch();
    bool Detect_NonDirac();
};

} //NameSpace

#endif
