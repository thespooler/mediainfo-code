// File_Mpegts - Info for MPEG Transport Stream files
// Copyright (C) 2006-2008 Jerome Martinez, Zen@MediaArea.net
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
// Information about MPEG Transport Stream files
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef MediaInfo_MpegTsH
#define MediaInfo_MpegTsH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Duplicate.h"
#include "MediaInfo/Multiple/File_Mpeg_Psi.h"
#include <map>
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_MpegTs
//***************************************************************************

class File_MpegTs : public File__Duplicate
{
public :
    File_MpegTs();

protected :
    //Formats
    void Read_Buffer_Continue ();
    virtual void Read_Buffer_Finalize (); //virtual for BDAV

    //Information
    void HowTo (stream_t StreamKind);

private :
    //Buffer
    bool Header_Begin();
    void Header_Parse();
    void Header_Parse_AdaptationField();
    void Data_Parse();

    //Data
    struct ts_stream
    {
        File__Analyze*          Parser;
        int8u                   stream_type;
        File_Mpeg_Psi::ts_kind  TS_Kind;
        int16u                  program_number;
        int64u                  TimeStamp_Start;
        int64u                  TimeStamp_End;
        bool                    StreamIsRegistred;
        bool                    Scrambled;
        bool                    Searching_Payload_Start;
        bool                    Searching_Payload_Continue;
        bool                    Searching_TimeStamp_Start;
        bool                    Searching_TimeStamp_End;
        bool                    ShouldDuplicate;

        ts_stream()
        {
            Parser=NULL;
            stream_type=0;
            TS_Kind=File_Mpeg_Psi::unknown;
            program_number=0;
            TimeStamp_Start=(int64u)-1;
            TimeStamp_End=(int64u)-1;
            StreamIsRegistred=false;
            Scrambled=false;
            Searching_Payload_Start=false;
            Searching_Payload_Continue=false;
            Searching_TimeStamp_Start=false;
            Searching_TimeStamp_End=false;
            ShouldDuplicate=false;
        }

        ~ts_stream()
        {
            delete Parser; //Parser=NULL;
        }
    };
    std::map<int64u, ts_stream> Stream;
    int16u                      pid;
    bool                        payload_unit_start_indicator;


    //Elements
    void PSI();
    void PSI_program_association_table();
    void PSI_program_map_table();
    void Reserved();
    void PES();
    void Null();

    //Helpers
    bool Synchronize();
    bool Header_Parser_QuickSearch();
    void Detect_EOF();

    //Temp
    bool Parsing_End;
    size_t BDAV_Size;
    int64u MpegTs_JumpTo_Begin;
    int64u MpegTs_JumpTo_End;

    //File_Duplicate
    void   File__Duplicate_HasChanged_Modify();
    std::map<Ztring, File_Mpeg_Psi::file_duplicate_info> PSI_Table_00_File_Duplicate_Info;

    //Friends
    friend class File_Bdav;
};

} //NameSpace

#endif
