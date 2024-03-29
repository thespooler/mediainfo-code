// File_Mpeg_Psi - Info for MPEG Stream files
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
// Information about MPEG files, Program Map Section
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef MediaInfo_Mpeg_PsiH
#define MediaInfo_Mpeg_PsiH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
#include <map>
using namespace ZenLib;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_Mpeg_Psi
//***************************************************************************

class File_Mpeg_Psi : public File__Analyze
{
public :
    //Configuration
    bool   From_TS;

    enum ts_kind
    {
        //MPEG
        unknown,
        program_association_table,
        program_map_table,
        network_information_table,
        conditional_access_table,
        transport_stream_description_table,
        reserved,
        pes,
        null,
        PCR,
        
        //Other
        dvb_nit_st,
        dvb_sdt_bat_st,
        dvb_eit,
        dvb_rst_st,
        dvb_tdt_tot_st,
        dvb_mip,
        dvb_reserved,
        dvb_inband,
        dvb_measurement,
        dvb_dit,
        dvb_sit,
        arib,
        cea_osd,
        atsc_pate,
        atsc_stt_pide,
        atsc_op,
        atsc_psip,
        atsc_scte,
        atsc_reserved,
        docsis
    };

    //About streams
    struct stream
    {
        std::map<std::string, ZenLib::Ztring>       Infos;
        int32u                                      format_identifier;
        int16u                                      program_number;
        ts_kind                                     Kind;
        int8u                                       stream_type;
        int8u                                       descriptor_tag;
        int16u                                      CA_PID;

        stream()
        {
            format_identifier=0x00000000;
            program_number=0xFFFF;
            Kind=unknown;
            stream_type=0x00;
            descriptor_tag=0x00;
            CA_PID=0x0000;
        }
    };
    std::map<int16u, stream> Streams;
    int16u                   Stream_Current;

    //About Programs
    struct program
    {
        int16u                                      pid;

        program()
        {
            pid=0;
        }

        ~program()
        {
        }
    };
    std::map<int16u, program>   Programs;

    //About program
    int16u transport_stream_id; //Unique ID of the stream

public :
    File_Mpeg_Psi();
    ~File_Mpeg_Psi();

private :
    //Buffer
    void Header_Parse();
    void Data_Parse();


private :
    //Elements - Base
    void Table_reserved();
    void Table_iso13818_6();
    void Table_user_private();
    void Table_forbidden();

    //Elements - MPEG
    void program_stream_map(); //From PS
    void Table_00();
    void Table_01();
    void Table_02();
    void Table_03();
    void Table_04() {Skip_XX(Element_Size, "Data");};
    void Table_05() {Skip_XX(Element_Size, "Data");};
    void Table_06() {Skip_XX(Element_Size, "Data");};
    //Elements - DVB
    void Table_38() {Skip_XX(Element_Size, "Data");};
    void Table_39() {Skip_XX(Element_Size, "Data");};
    void Table_3A() {Skip_XX(Element_Size, "Data");};
    void Table_3B() {Skip_XX(Element_Size, "Data");};
    void Table_3C() {Skip_XX(Element_Size, "Data");};
    void Table_3D() {Skip_XX(Element_Size, "Data");};
    void Table_3E() {Skip_XX(Element_Size, "Data");};
    void Table_3F() {Skip_XX(Element_Size, "Data");};
    void Table_40() {Skip_XX(Element_Size, "Data");};
    void Table_41() {Skip_XX(Element_Size, "Data");};
    void Table_42();
    void Table_46();
    void Table_4A() {Skip_XX(Element_Size, "Data");};
    void Table_4E();
    void Table_4F();
    void Table_5F(); //50 --> 5F
    void Table_6F(); //60 --> 6F
    void Table_70() {Skip_XX(Element_Size, "Data");};
    void Table_71() {Skip_XX(Element_Size, "Data");};
    void Table_72() {Skip_XX(Element_Size, "Data");};
    void Table_73() {Skip_XX(Element_Size, "Data");};
    void Table_74() {Skip_XX(Element_Size, "Data");};
    void Table_75() {Skip_XX(Element_Size, "Data");};
    void Table_76() {Skip_XX(Element_Size, "Data");};
    void Table_77() {Skip_XX(Element_Size, "Data");};
    void Table_78() {Skip_XX(Element_Size, "Data");};
    void Table_79() {Skip_XX(Element_Size, "Data");};
    void Table_7E() {Skip_XX(Element_Size, "Data");};
    void Table_7F();
    //Elements - ASTC
    void Table_C0() {Skip_XX(Element_Size, "Data");};
    void Table_C1() {Skip_XX(Element_Size, "Data");};
    void Table_C2() {Skip_XX(Element_Size, "Data");};
    void Table_C3() {Skip_XX(Element_Size, "Data");};
    void Table_C4() {Skip_XX(Element_Size, "Data");};
    void Table_C5() {Skip_XX(Element_Size, "Data");};
    void Table_C6() {Skip_XX(Element_Size, "Data");};
    void Table_C7();
    void Table_C8();
    void Table_C9() {Skip_XX(Element_Size, "Data");};
    void Table_CA() {Skip_XX(Element_Size, "Data");};
    void Table_CB() {Skip_XX(Element_Size, "Data");};
    void Table_CC() {Skip_XX(Element_Size, "Data");};
    void Table_CD() {Skip_XX(Element_Size, "Data");};
    void Table_CE() {Skip_XX(Element_Size, "Data");};
    void Table_CF() {Skip_XX(Element_Size, "Data");};
    void Table_D0() {Skip_XX(Element_Size, "Data");};
    void Table_D1() {Skip_XX(Element_Size, "Data");};
    void Table_D2() {Skip_XX(Element_Size, "Data");};
    void Table_D3() {Skip_XX(Element_Size, "Data");};
    void Table_D4() {Skip_XX(Element_Size, "Data");};
    void Table_D5() {Skip_XX(Element_Size, "Data");};
    void Table_D6() {Skip_XX(Element_Size, "Data");};
    void Table_D7() {Skip_XX(Element_Size, "Data");};
    void Table_D8() {Skip_XX(Element_Size, "Data");};
    void Table_D9() {Skip_XX(Element_Size, "Data");};
    void Table_DA() {Skip_XX(Element_Size, "Data");};

    //Helpers
    int16u Descriptors_Size;
    void Descriptors();
    Ztring Date_MJD(int16u Date);
    Ztring Time_BCD(int32u Time);

    //Data
    int8u pointer_field;
    int8u table_id;
    int32u CRC_32;
};

} //NameSpace

#endif
