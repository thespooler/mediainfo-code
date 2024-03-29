// File_Mpeg_Descriptors - Info for MPEG files
// Copyright (C) 2007-2009 Jerome Martinez, Zen@MediaArea.net
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
// Information about MPEG files, Descriptors
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef MediaInfo_Mpeg_DescriptorsH
#define MediaInfo_Mpeg_DescriptorsH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
#include "MediaInfo/Duplicate/File__Duplicate_MpegTs.h"
#include <map>
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Global object
//***************************************************************************

struct complete_stream
{
    //Global
    int16u transport_stream_id; //The processed transport_stream_id
    bool   transport_stream_id_IsValid; //The processed transport_stream_id
    Ztring original_network_name;
    Ztring network_name;
    Ztring Start_Time;
    Ztring End_Time;
    std::map<Ztring, Ztring> TimeZones; //Key is country code

    //Per transport_stream
    struct transport_stream
    {
        bool HasChanged;
        std::map<std::string, Ztring> Infos;
        struct program
        {
            bool HasChanged;
            std::map<std::string, Ztring> Infos;
            std::vector<int16u> elementary_PIDs;
            int32u registration_format_identifier;
            int16u pid;
            int16u PCR_PID;
            int16u program_number;
            int16u source_id; //ATSC
            bool   IsParsed;
            bool   IsRegistered;

            //DVB
            struct dvb_epg_block
            {
                struct event
                {
                    Ztring  start_time;
                    Ztring  duration;
                    struct short_event_
                    {
                        Ztring  event_name;
                        Ztring  text;
                    };
                    short_event_ short_event;
                    Ztring  content;
                    Ztring  running_status;
                };

                typedef std::map<int16u, event> events; //Key is event_id
                events Events; //Key is event_id
            };
            typedef std::map<int8u, dvb_epg_block> dvb_epg_blocks; //Key is table_id
            dvb_epg_blocks DVB_EPG_Blocks; //Key is table_id

            //Constructor/Destructor
            program()
            {
                HasChanged=false;
                registration_format_identifier=0x00000000;
                pid=0x00000;
                PCR_PID=0x0000;
                program_number=0x0000;
                source_id=0x0000;
                IsParsed=false;
                IsRegistered=false;
            }
        };
        typedef std::map<int16u, program> programs; //Key is program_number
        programs Programs; //Key is program_number
        size_t   Programs_NotParsedCount;

        //Per IOD
        struct iod_es
        {
            File__Analyze*                              Parser;

            //Constructor/Destructor
            iod_es()
            {
                Parser=NULL;
            }

            ~iod_es()
            {
                delete Parser; //Parser=NULL;
            }
        };
        typedef std::map<int16u, iod_es> iod_ess; //Key is ES_ID
        std::map<int16u, iod_es> IOD_ESs; //Key is ES_ID

        //ATSC
        int16u source_id; //Global

        transport_stream()
        {
            HasChanged=false;
            source_id=0;
            Programs_NotParsedCount=(size_t)-1;
        }
    };
    typedef std::map<int16u, transport_stream> transport_streams; //Key is transport_stream_id
    transport_streams Transport_Streams; //Key is transport_stream_id

    //Per PID
    struct stream
    {
        File__Analyze*                              Parser;

        enum ts_kind
        {
            //MPEG
            unknown,
            pes,
            pcr,
            psi,
        };
        std::vector<int16u>                         program_numbers;
        struct version
        {
            int8u version_number;
            std::map<int8u, bool> section_numbers; //Key is section_number, true when parsed
        };
        std::map<int8u, std::map<int16u, version> > Versions; //Key are table_id and table_id_extension
        std::map<std::string, Ztring>               Infos;
        #ifndef MEDIAINFO_MINIMIZESIZE
            Ztring Element_Info;
        #endif //MEDIAINFO_MINIMIZESIZE
        stream_t                                    StreamKind;
        size_t                                      StreamPos;
        ts_kind                                     Kind;
        int64u                                      TimeStamp_Start;
        int64u                                      TimeStamp_End;
        int32u                                      registration_format_identifier;
        int32u                                      FMC_ES_ID;
        int16u                                      table_type; //ATSC
        int8u                                       stream_type;
        bool                                        FMC_ES_ID_IsValid;
        bool                                        Searching;
        bool                                        Searching_Payload_Start;
        bool                                        Searching_Payload_Continue;
        bool                                        Searching_TimeStamp_Start;
        bool                                        Searching_TimeStamp_End;
        bool                                        Searching_ParserTimeStamp_Start;
        bool                                        Searching_ParserTimeStamp_End;
        bool                                        EndTimeStampMoreThanxSeconds;
        bool                                        ShouldDuplicate;
        bool                                        IsRegistered;
        bool                                        IsScrambled;

        //Constructor/Destructor
        stream()
        {
            Parser=NULL;
            StreamKind=Stream_Max;
            StreamPos=0;
            Kind=unknown;
            TimeStamp_Start=(int64u)-1;
            TimeStamp_End=(int64u)-1;
            registration_format_identifier=0x00000000;
            FMC_ES_ID=0x0000;
            table_type=0x0000;
            stream_type=0x00;
            FMC_ES_ID_IsValid=false;
            Searching=false;
            Searching_Payload_Start=false;
            Searching_Payload_Continue=false;
            Searching_TimeStamp_Start=false;
            Searching_TimeStamp_End=false;
            Searching_ParserTimeStamp_Start=false;
            Searching_ParserTimeStamp_End=false;
            EndTimeStampMoreThanxSeconds=false;
            ShouldDuplicate=false;
            IsRegistered=false;
            IsScrambled=false;
        }

        ~stream()
        {
            delete Parser; //Parser=NULL;
        }

        //Helpers
        void Searching_Payload_Start_Set(bool ToSet)
        {
            Searching_Payload_Start=ToSet;
            Searching_Test();
        }
        void Searching_Payload_Continue_Set(bool ToSet)
        {
            Searching_Payload_Continue=ToSet;
            Searching_Test();
        }
        void Searching_TimeStamp_Start_Set(bool ToSet)
        {
            Searching_TimeStamp_Start=ToSet;
            Searching_Test();
        }
        void Searching_TimeStamp_End_Set(bool ToSet)
        {
            Searching_TimeStamp_End=ToSet;
            Searching_Test();
        }
        void Searching_ParserTimeStamp_Start_Set(bool ToSet)
        {
            Searching_ParserTimeStamp_Start=ToSet;
            Searching_Test();
        }
        void Searching_ParserTimeStamp_End_Set(bool ToSet)
        {
            Searching_ParserTimeStamp_End=ToSet;
            Searching_Test();
        }
        void Searching_Test()
        {
            Searching=Searching_Payload_Start
                    | Searching_Payload_Continue
                    | Searching_TimeStamp_Start
                    | Searching_TimeStamp_End
                    | Searching_ParserTimeStamp_Start
                    | Searching_ParserTimeStamp_End;
        }
    };
    std::vector<stream> Streams; //Key is PID
    size_t Streams_NotParsedCount;
    size_t Streams_With_StartTimeStampCount;
    size_t Streams_With_EndTimeStampMoreThanxSecondsCount;

    //ATSC
    int8u GPS_UTC_offset;
    struct source
    {
        std::map<int16u, Ztring> texts;
        struct atsc_epg_block
        {
            struct event
            {
                int32u  start_time;
                Ztring  duration;
                Ztring  title;
                std::map<int16u, Ztring> texts;
            };

            typedef std::map<int16u, event> events; //Key is event_id
            events Events; //Key is event_id
        };
        typedef std::map<int16u, atsc_epg_block> atsc_epg_blocks; //Key is table_id
        atsc_epg_blocks ATSC_EPG_Blocks; //Key is table_id
    };
    typedef std::map<int16u, source> sources; //Key is source_id
    sources Sources; //Key is source_id

    //File__Duplicate
    bool                                                File__Duplicate_HasChanged_;
    size_t                                              Config_File_Duplicate_Get_AlwaysNeeded_Count;
    std::vector<File__Duplicate_MpegTs*>                Duplicates_Speed;
    std::vector<std::vector<File__Duplicate_MpegTs*> >  Duplicates_Speed_FromPID;
    std::map<const String, File__Duplicate_MpegTs*>     Duplicates;
    bool File__Duplicate_Get_From_PID (int16u PID)
    {
        if (Duplicates_Speed_FromPID.empty())
            return false;
        return !Duplicates_Speed_FromPID[PID].empty();
    }

    //Constructor/Destructor
    complete_stream()
    {
        transport_stream_id=0;
        transport_stream_id_IsValid=false;
        Streams_NotParsedCount=0;
        Streams_With_StartTimeStampCount=0;
        Streams_With_EndTimeStampMoreThanxSecondsCount=0;
        GPS_UTC_offset=0;
    }
};

//***************************************************************************
// Class File_Mpeg_Descriptors
//***************************************************************************

class File_Mpeg_Descriptors : public File__Analyze
{
public :
    //In
    complete_stream* Complete_Stream;
    int16u   transport_stream_id;
    int8u    table_id;
    int16u   table_id_extension;
    int16u   xxx_id;
    bool     xxx_id_IsValid;

    //Constructor/Destructor
    File_Mpeg_Descriptors();

private :
    //Buffer - Per element
    void Header_Parse();
    void Data_Parse();

    //Elements
    void Descriptors();
    void Descriptor();
    void Descriptor_00() {Skip_XX(Element_Size, "Data");};
    void Descriptor_01() {Skip_XX(Element_Size, "Data");};
    void Descriptor_02();
    void Descriptor_03();
    void Descriptor_04() {Skip_XX(Element_Size, "Data");};
    void Descriptor_05();
    void Descriptor_06();
    void Descriptor_07();
    void Descriptor_08();
    void Descriptor_09();
    void Descriptor_0A();
    void Descriptor_0B() {Skip_XX(Element_Size, "Data");};
    void Descriptor_0C() {Skip_XX(Element_Size, "Data");};
    void Descriptor_0D() {Skip_XX(Element_Size, "Data");};
    void Descriptor_0E();
    void Descriptor_0F();
    void Descriptor_10();
    void Descriptor_11();
    void Descriptor_12() {Skip_XX(Element_Size, "Data");};
    void Descriptor_13() {Skip_XX(Element_Size, "Data");};
    void Descriptor_14() {Skip_XX(Element_Size, "Data");};
    void Descriptor_15() {Skip_XX(Element_Size, "Data");};
    void Descriptor_16() {Skip_XX(Element_Size, "Data");};
    void Descriptor_17() {Skip_XX(Element_Size, "Data");};
    void Descriptor_18() {Skip_XX(Element_Size, "Data");};
    void Descriptor_19() {Skip_XX(Element_Size, "Data");};
    void Descriptor_1A() {Skip_XX(Element_Size, "Data");};
    void Descriptor_1B() {Skip_XX(Element_Size, "Data");};
    void Descriptor_1C() {Skip_XX(Element_Size, "Data");};
    void Descriptor_1D();
    void Descriptor_1E() {Skip_XX(Element_Size, "Data");};
    void Descriptor_1F();
    void Descriptor_20() {Skip_XX(Element_Size, "Data");};
    void Descriptor_21() {Skip_XX(Element_Size, "Data");};
    void Descriptor_22() {Skip_XX(Element_Size, "Data");};
    void Descriptor_23() {Skip_XX(Element_Size, "Data");};
    void Descriptor_24() {Skip_XX(Element_Size, "Data");};
    void Descriptor_25() {Skip_XX(Element_Size, "Data");};
    void Descriptor_26() {Skip_XX(Element_Size, "Data");};
    void Descriptor_27() {Skip_XX(Element_Size, "Data");};
    void Descriptor_28();
    void Descriptor_29() {Skip_XX(Element_Size, "Data");};
    void Descriptor_2A() {Skip_XX(Element_Size, "Data");};
    void Descriptor_2B() {Skip_XX(Element_Size, "Data");};
    void Descriptor_2C() {Skip_XX(Element_Size, "Data");};
    void Descriptor_2D() {Skip_XX(Element_Size, "Data");};
    void Descriptor_2E() {Skip_XX(Element_Size, "Data");};
    void Descriptor_2F();
    void Descriptor_40();
    void Descriptor_41();
    void Descriptor_42() {Skip_XX(Element_Size, "Data");};
    void Descriptor_43();
    void Descriptor_44() {Skip_XX(Element_Size, "Data");};
    void Descriptor_45() {Skip_XX(Element_Size, "Data");};
    void Descriptor_46() {Skip_XX(Element_Size, "Data");};
    void Descriptor_47() {Skip_XX(Element_Size, "Data");};
    void Descriptor_48();
    void Descriptor_49() {Skip_XX(Element_Size, "Data");};
    void Descriptor_4A();
    void Descriptor_4B() {Skip_XX(Element_Size, "Data");};
    void Descriptor_4C() {Skip_XX(Element_Size, "Data");};
    void Descriptor_4D();
    void Descriptor_4E() {Skip_XX(Element_Size, "Data");};
    void Descriptor_4F() {Skip_XX(Element_Size, "Data");};
    void Descriptor_50();
    void Descriptor_51() {Skip_XX(Element_Size, "Data");};
    void Descriptor_52();
    void Descriptor_53() {Skip_XX(Element_Size, "Data");};
    void Descriptor_54();
    void Descriptor_55();
    void Descriptor_56();
    void Descriptor_57() {Skip_XX(Element_Size, "Data");};
    void Descriptor_58();
    void Descriptor_59();
    void Descriptor_5A();
    void Descriptor_5B() {Skip_XX(Element_Size, "Data");};
    void Descriptor_5C() {Skip_XX(Element_Size, "Data");};
    void Descriptor_5D();
    void Descriptor_5E() {Skip_XX(Element_Size, "Data");};
    void Descriptor_5F();
    void Descriptor_60() {Skip_XX(Element_Size, "Data");};
    void Descriptor_61() {Skip_XX(Element_Size, "Data");};
    void Descriptor_62() {Skip_XX(Element_Size, "Data");};
    void Descriptor_63();
    void Descriptor_64() {Skip_XX(Element_Size, "Data");};
    void Descriptor_65() {Skip_XX(Element_Size, "Data");};
    void Descriptor_66();
    void Descriptor_67() {Skip_XX(Element_Size, "Data");};
    void Descriptor_68() {Skip_XX(Element_Size, "Data");};
    void Descriptor_69() {Skip_XX(Element_Size, "Data");};
    void Descriptor_6A();
    void Descriptor_6B() {Skip_XX(Element_Size, "Data");};
    void Descriptor_6C() {Skip_XX(Element_Size, "Data");};
    void Descriptor_6D() {Skip_XX(Element_Size, "Data");};
    void Descriptor_6E() {Skip_XX(Element_Size, "Data");};
    void Descriptor_6F() {Skip_XX(Element_Size, "Data");};
    void Descriptor_70() {Skip_XX(Element_Size, "Data");};
    void Descriptor_71() {Skip_XX(Element_Size, "Data");};
    void Descriptor_72() {Skip_XX(Element_Size, "Data");};
    void Descriptor_73() {Skip_XX(Element_Size, "Data");};
    void Descriptor_74() {Skip_XX(Element_Size, "Data");};
    void Descriptor_75() {Skip_XX(Element_Size, "Data");};
    void Descriptor_76() {Skip_XX(Element_Size, "Data");};
    void Descriptor_77() {Skip_XX(Element_Size, "Data");};
    void Descriptor_78() {Skip_XX(Element_Size, "Data");};
    void Descriptor_79() {Skip_XX(Element_Size, "Data");};
    void Descriptor_7A();
    void Descriptor_7B();
    void Descriptor_7C();
    void Descriptor_7D() {Skip_XX(Element_Size, "Data");};
    void Descriptor_7E() {Skip_XX(Element_Size, "Data");};
    void Descriptor_7F() {Skip_XX(Element_Size, "Data");};
    void Descriptor_80() {Skip_XX(Element_Size, "Data");};
    void Descriptor_81();
    void Descriptor_86();
    void Descriptor_87();
    void Descriptor_A0();
    void Descriptor_A1();
    void Descriptor_A2() {Skip_XX(Element_Size, "Data");};
    void Descriptor_A3();
    void Descriptor_A8() {Skip_XX(Element_Size, "Data");};
    void Descriptor_A9() {Skip_XX(Element_Size, "Data");};
    void Descriptor_AA();
    void Descriptor_AB() {Skip_XX(Element_Size, "Data");};

    //Helpers
    void ATSC_multiple_string_structure(Ztring &Value, const char* Info);
    void Get_DVB_Text(int64u Size, Ztring &Value, const char* Info);
    void Skip_DVB_Text(int64u Size, const char* Info) {Ztring Temp; Get_DVB_Text(Size, Temp, Info);};
    Ztring Date_MJD(int16u Date);
    Ztring Time_BCD(int32u Time);
    Ztring TimeHHMM_BCD(int16u Time);
    Ztring Frequency_DVB__BCD(int32u Frequency);
    Ztring OrbitalPosition_DVB__BCD(int32u OrbitalPosition);
};

} //NameSpace

#endif
