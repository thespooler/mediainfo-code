// File_DvbSubtitle - Info for DVB Subtitle streams
// Copyright (C) 2011-2011 MediaArea.net SARL, Info@MediaArea.net
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
#if defined(MEDIAINFO_DVBSUBTITLE_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Text/File_DvbSubtitle.h"
#include "MediaInfo/MediaInfo_Config_MediaInfo.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Info
//***************************************************************************

const int8u DvbSubtitle_region_depth[8]=
{
    0,
    2,
    4,
    8,
    0,
    0,
    0,
    0,
};

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
File_DvbSubtitle::File_DvbSubtitle()
:File__Analyze()
{
    //Configuration
    ParserName=_T("DVB Subtitle");
    #if MEDIAINFO_EVENTS
        ParserIDs[0]=MediaInfo_Parser_DvbSubtitle;
    #endif //MEDIAINFO_EVENTS
    #if MEDIAINFO_TRACE
        Trace_Layers_Update(8); //Stream
    #endif //MEDIAINFO_TRACE
    PTS_DTS_Needed=true;
    IsRawStream=true;
    MustSynchronize=true;

    //In
    Frame_Count_Valid=MediaInfoLib::Config.ParseSpeed_Get()>=0.3?32:2;

    //Temp
    MustFindDvbHeader=true;
}

//---------------------------------------------------------------------------
File_DvbSubtitle::~File_DvbSubtitle()
{
}

//***************************************************************************
// Streams management
//***************************************************************************

//---------------------------------------------------------------------------
void File_DvbSubtitle::Streams_Fill()
{
    Stream_Prepare(Stream_Text);
    Fill(Stream_Text, 0, Text_Format, "DVB Subtitle");

    for (std::map<int8u, subtitle_stream_data>::iterator subtitle_stream=subtitle_streams.begin(); subtitle_stream!=subtitle_streams.end(); subtitle_stream++)
        for (std::map<int16u, page_data>::iterator page=subtitle_stream->second.pages.begin(); page!=subtitle_stream->second.pages.end(); page++)
            for (std::map<int8u, region_data>::iterator region=page->second.regions.begin(); region!=page->second.regions.end(); region++)
            {
                Fill(Stream_Text, 0, "subtitle_stream_id", subtitle_stream->first);
                (*Stream_More)[Stream_Text][0](Ztring().From_Local("subtitle_stream_id"), Info_Options)=_T("N NI");
                Fill(Stream_Text, 0, "page_id", page->first);
                (*Stream_More)[Stream_Text][0](Ztring().From_Local("page_id"), Info_Options)=_T("N NI");
                Fill(Stream_Text, 0, "region_id", region->first);
                (*Stream_More)[Stream_Text][0](Ztring().From_Local("region_id"), Info_Options)=_T("N NI");
                Fill(Stream_Text, 0, "region_horizontal_address", region->second.region_horizontal_address);
                (*Stream_More)[Stream_Text][0](Ztring().From_Local("region_horizontal_address"), Info_Options)=_T("N NI");
                Fill(Stream_Text, 0, "region_vertical_address", region->second.region_vertical_address);
                (*Stream_More)[Stream_Text][0](Ztring().From_Local("region_vertical_address"), Info_Options)=_T("N NI");
                Fill(Stream_Text, 0, "region_width", region->second.region_width);
                (*Stream_More)[Stream_Text][0](Ztring().From_Local("region_width"), Info_Options)=_T("N NI");
                Fill(Stream_Text, 0, "region_height", region->second.region_height);
                (*Stream_More)[Stream_Text][0](Ztring().From_Local("region_height"), Info_Options)=_T("N NI");
                Fill(Stream_Text, 0, "region_depth", DvbSubtitle_region_depth[region->second.region_depth]);
                (*Stream_More)[Stream_Text][0](Ztring().From_Local("region_depth"), Info_Options)=_T("N NI");
            }
}

//---------------------------------------------------------------------------
void File_DvbSubtitle::Streams_Finish()
{
}

//***************************************************************************
// Buffer - Synchro
//***************************************************************************

//---------------------------------------------------------------------------
bool File_DvbSubtitle::Synchronize()
{
    //Synchronizing
    if (MustFindDvbHeader)
    {
        while(Buffer_Offset+3<=Buffer_Size)
        {
            if (Buffer[Buffer_Offset]==0x20
             && Buffer[Buffer_Offset+1]==0x00
             && (Buffer[Buffer_Offset+2]==0x0F
              || Buffer[Buffer_Offset+1]==0xFF))
                break;
            Buffer_Offset++;
        }

        if (Buffer_Offset+3>Buffer_Size)
            return false;

        Accept();
    }
    else
    {
        while(Buffer_Offset<Buffer_Size)
        {
            if (Buffer[Buffer_Offset]==0x0F
             || Buffer[Buffer_Offset]==0xFF)
                break;
            Buffer_Offset++;
        }

        if (Buffer_Offset>=Buffer_Size)
            return false;
    }

    //Synched is OK
    Synched=true;
    return true;
}

//---------------------------------------------------------------------------
bool File_DvbSubtitle::Synched_Test()
{
    if (MustFindDvbHeader)
    {
        //Must have enough buffer for having header
        if (Buffer_Offset+1>Buffer_Size)
            return false;

        if (CC2(Buffer+Buffer_Offset)!=0x2000)
        {
            Synched=false;
            return true;
        }

        //Displaying it
        Element_Size=2;
        Skip_B1(                                                "data_identifier");
        Get_B1 (subtitle_stream_id,                             "subtitle_stream_id");
        Buffer_Offset+=2;
        MustFindDvbHeader=false;
    }

    //Must have enough buffer for having header
    if (Buffer_Offset+1>Buffer_Size)
        return false;

    //Quick test of synchro
    if (Buffer[Buffer_Offset]!=0x0F
     && Buffer[Buffer_Offset]!=0xFF)
    {
        Synched=false;
        return true;
    }

    //We continue
    return true;
}

//---------------------------------------------------------------------------
void File_DvbSubtitle::Read_Buffer_Unsynched()
{
    MustParseTheHeaderFile=true;
    Synched=false;
}

//***************************************************************************
// Buffer - Demux
//***************************************************************************

//---------------------------------------------------------------------------
#if MEDIAINFO_DEMUX
bool File_DvbSubtitle::Demux_UnpacketizeContainer_Test()
{
    if (Demux_Offset==0)
    {
        Demux_Offset=Buffer_Offset;
    }
    while (Demux_Offset<Buffer_Size)
    {
        bool MustBreak;
        switch (Buffer[Demux_Offset])
        {
            case 0xFF :
                        MustBreak=true; break; //0xFF is not in the demuxed frame
            default   : MustBreak=false;
        }
        if (MustBreak)
            break; //while() loop

        if (Demux_Offset+6>Buffer_Size)
            return false; //No complete frame

        int16u segment_length=BigEndian2int16u(Buffer+Demux_Offset+4);
        Demux_Offset+=6+segment_length;

        if (Demux_Offset>=Buffer_Size)
            return false; //No complete frame
    }

    if (Demux_Offset>=Buffer_Size)
        return false; //No complete frame

    Demux_UnpacketizeContainer_Demux();

    Demux_TotalBytes++; //0xFF is not demuxed

    return true;
}
#endif //MEDIAINFO_DEMUX

//***************************************************************************
// Buffer - Per element
//***************************************************************************

//---------------------------------------------------------------------------
void File_DvbSubtitle::Header_Parse()
{
    //Parsing
    int8u sync_byte;
    Get_B1 (sync_byte,                                          "sync_byte");
    switch (sync_byte)
    {
        case 0xFF : //Stuffing
                    MustFindDvbHeader=true;

                    //Filling
                    Header_Fill_Code(0xFF, "end_of_PES_data_field_marker");
                    Header_Fill_Size(1);
                    return;
        default   : ; //Normal (0x0F)
    }

    int16u segment_length;
    int8u  segment_type;
    Get_B1 (segment_type,                                       "segment_type");
    Get_B2 (page_id,                                            "page_id");
    Get_B2 (segment_length,                                     "segment_length");

    //Filling
    Header_Fill_Code(segment_type);
    Header_Fill_Size(Element_Offset+segment_length);
}

//---------------------------------------------------------------------------
void File_DvbSubtitle::Data_Parse()
{
    switch (Element_Code)
    {
        case 0x10 : page_composition_segment(); break;
        case 0x11 : region_composition_segment(); break;
        case 0xFF : //end_of_PES_data_field_marker
                    Frame_Count++;
                    if (!Status[IsFilled] && Frame_Count>Frame_Count_Valid)
                    {
                        Fill();
                        Finish();
                    }
                    return;
        default   :
                    if (Element_Size)
                        Skip_XX(Element_Size,                   "Unknown");
    }
}

//***************************************************************************
// Elements
//***************************************************************************

//---------------------------------------------------------------------------
void File_DvbSubtitle::page_composition_segment()
{
    Element_Name("page_composition_segment");

    //Parsing
    Skip_B1(                                                    "page_time_out");
    BS_Begin();
    Skip_S1(4,                                                  "page_version_number");
    Skip_S1(2,                                                  "page_state");
    Skip_S1(2,                                                  "reserved");
    BS_End();
    while(Element_Offset<Element_Size)
    {
        Element_Begin("Region");
        int16u region_horizontal_address, region_vertical_address;
        int8u region_id;
        Get_B1 (region_id,                                      "region_id");
        Skip_B1(                                                "reserved");
        Get_B2 (region_horizontal_address,                      "region_horizontal_address");
        Get_B2 (region_vertical_address,                        "region_vertical_address");
        Element_End();

        FILLING_BEGIN();
            subtitle_streams[subtitle_stream_id].pages[page_id].regions[region_id].region_horizontal_address=region_horizontal_address;
            subtitle_streams[subtitle_stream_id].pages[page_id].regions[region_id].region_vertical_address=region_vertical_address;
        FILLING_END();
    }
}

//---------------------------------------------------------------------------
void File_DvbSubtitle::region_composition_segment()
{
    Element_Name("region_composition_segment");

    //Parsing
    int16u region_width, region_height;
    int8u  region_id, region_depth;
    Get_B1 (   region_id,                                       "region_id");
    BS_Begin();
    Skip_S1(4,                                                  "region_version_number");
    Skip_S1(1,                                                  "region_fill_flag");
    Skip_S1(3,                                                  "reserved");
    BS_End();
    Get_B2 (   region_width,                                    "region_width");
    Get_B2 (   region_height,                                   "region_height");
    BS_Begin();
    Skip_S1(3,                                                  "region_level_of_compatibility");
    Get_S1 (3, region_depth,                                    "region_depth"); Param_Info(DvbSubtitle_region_depth[region_depth], " bits");
    Skip_S1(2,                                                  "reserved");
    BS_End();
    Skip_B1(                                                    "CLUT_id");
    Skip_B1(                                                    "region_8-bit_pixel_code");
    BS_Begin();
    Skip_S1(4,                                                  "region_4-bit_pixel-code");
    Skip_S1(2,                                                  "region_2-bit_pixel-code");
    Skip_S1(2,                                                  "reserved");
    BS_End();
    while(Element_Offset<Element_Size)
    {
        Element_Begin("Object");
        int8u object_type;
        Skip_B2(                                                "object_id");
        BS_Begin();
        Get_S1 ( 2, object_type,                                "object_type");
        Skip_S1( 2,                                             "object_provider_flag");
        Skip_S1(12,                                             "object_horizontal_position");
        Skip_S1( 4,                                             "reserved");
        Skip_S1(12,                                             "object_vertical_position");
        BS_End();
        switch (object_type)
        {
            case 0x01 :
            case 0x02 :
                        Skip_B2(                                 "foreground_pixel_code");
                        Skip_B2(                                 "background_pixel_code");
                        break;
            default   : ;
        }
    }
    Element_End();

    FILLING_BEGIN();
        subtitle_streams[subtitle_stream_id].pages[page_id].regions[region_id].region_width=region_width;
        subtitle_streams[subtitle_stream_id].pages[page_id].regions[region_id].region_height=region_height;
        subtitle_streams[subtitle_stream_id].pages[page_id].regions[region_id].region_depth=region_depth;
    FILLING_END();
}

//***************************************************************************
// C++
//***************************************************************************

} //NameSpace

#endif //MEDIAINFO_DVBSUBTITLE_YES

