// File_Dirac - Info for DIRAC  files
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
// Compilation conditions
#include <MediaInfo/Setup.h>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_DIRAC_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Video/File_Dirac.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//---------------------------------------------------------------------------
const char* Dirac_base_video_format(int8u base_video_format)
{
    switch (base_video_format)
    {
        case   1 : return "QSIF525";
        case   2 : return "QCIF";
        case   3 : return "SIF525";
        case   4 : return "CIF";
        case   5 : return "4SIF525";
        case   6 : return "4CIF";
        case   7 : return "480i60";
        case   8 : return "576i50";
        case   9 : return "720p50";
        case  10 : return "720p60";
        case  11 : return "1080i60";
        case  12 : return "1080i50";
        case  13 : return "1080p60";
        case  14 : return "1080p60";
        case  15 : return "2K-24";
        case  16 : return "4K-24";
        default  : return "";
    }
}

//---------------------------------------------------------------------------
float32 Dirac_frame_rate(int32u frame_rate_index)
{
    switch (frame_rate_index)
    {
        case  0 : return (float32)0; //Reserved
        case  1 : return (float32)24000/(float32)1001;
        case  2 : return (float32)24;
        case  3 : return (float32)25;
        case  4 : return (float32)30000/(float32)1001;
        case  5 : return (float32)30;
        case  6 : return (float32)50;
        case  7 : return (float32)60000/(float32)1001;
        case  8 : return (float32)60;
        case  9 : return (float32)15000/(float32)1001;
        case 10 : return (float32)12.5;
        default : return (float32)0; //Unknown
    }
}

//---------------------------------------------------------------------------
float32 Dirac_pixel_aspect_ratio(int32u pixel_aspect_ratio_index)
{
    switch (pixel_aspect_ratio_index)
    {
        case  0 : return (float32)0; //Reserved
        case  1 : return (float32)1; //Reserved
        case  2 : return (float32)10/(float32)11;
        case  3 : return (float32)12/(float32)11;
        case  4 : return (float32)40/(float32)33;
        case  5 : return (float32)16/(float32)11;
        case  6 : return (float32) 4/(float32) 3;
        default : return (float32)0; //Unknown
    }
}

//---------------------------------------------------------------------------
const char* Dirac_picture_coding_mode(int32u picture_coding_mode)
{
    switch (picture_coding_mode)
    {
        case 0 : return "PPF";
        case 1 : return "Interlaced";
        default: return "";
    }
}

//---------------------------------------------------------------------------
const char* Dirac_source_sampling(int32u source_sampling)
{
    switch (source_sampling)
    {
        case 0 : return "PPF";
        case 1 : return "Interlaced";
        default: return "";
    }
}

//---------------------------------------------------------------------------
const char* Dirac_chroma_format(int32u chroma_format)
{
    switch (chroma_format)
    {
        case 0 : return "4:4:4";
        case 1 : return "4:2:2";
        case 2 : return "4:2:0";
        default: return "";
    }
}

//---------------------------------------------------------------------------
void Dirac_base_video_format(int8u base_video_format,
                            int32u &frame_width,
                            int32u &frame_height,
                            int32u &chroma_format,
                            int32u &source_sampling,
                            int32u &clean_width,
                            int32u &clean_height,
                            int32u &clean_left_offset,
                            int32u &clean_top_offset,
                            float32 &frame_rate,
                            float32 &pixel_aspect_ratio)
{
    switch (base_video_format)
    {
        case   0 :  frame_width=640;
                    frame_height=480;
                    chroma_format=2;
                    source_sampling=0;
                    clean_width=640;
                    clean_height=480;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(1);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(1);
                    return;
        case   1 :  frame_width=176;
                    frame_height=120;
                    chroma_format=2;
                    source_sampling=0;
                    clean_width=176;
                    clean_height=144;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(9);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(2);
                    return;
        case   2 :  frame_width=176;
                    frame_height=144;
                    chroma_format=2;
                    source_sampling=0;
                    clean_width=176;
                    clean_height=144;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(10);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(3);
                    return;
        case   3 :  frame_width=352;
                    frame_height=240;
                    chroma_format=2;
                    source_sampling=0;
                    clean_width=352;
                    clean_height=240;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(9);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(2);
                    return;
        case   4 :  frame_width=352;
                    frame_height=288;
                    chroma_format=2;
                    source_sampling=0;
                    clean_width=352;
                    clean_height=288;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(10);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(3);
                    return;
        case   5 :  frame_width=704;
                    frame_height=480;
                    chroma_format=2;
                    source_sampling=0;
                    clean_width=704;
                    clean_height=480;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(9);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(2);
                    return;
        case   6 :  frame_width=704;
                    frame_height=576;
                    chroma_format=2;
                    source_sampling=0;
                    clean_width=704;
                    clean_height=576;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(10);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(3);
                    return;
        case   7 :  frame_width=720;
                    frame_height=480;
                    chroma_format=1;
                    source_sampling=1;
                    clean_width=704;
                    clean_height=480;
                    clean_left_offset=8;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(4);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(2);
                    return;
        case   8 :  frame_width=720;
                    frame_height=576;
                    chroma_format=1;
                    source_sampling=1;
                    clean_width=704;
                    clean_height=576;
                    clean_left_offset=8;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(3);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(3);
                    return;
        case   9 :  frame_width=1280;
                    frame_height=720;
                    chroma_format=1;
                    source_sampling=0;
                    clean_width=1280;
                    clean_height=720;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(7);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(1);
                    return;
        case  10 :  frame_width=1280;
                    frame_height=720;
                    chroma_format=1;
                    source_sampling=0;
                    clean_width=1280;
                    clean_height=720;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(6);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(1);
                    return;
        case  11 :  frame_width=1920;
                    frame_height=1080;
                    chroma_format=1;
                    source_sampling=1;
                    clean_width=1920;
                    clean_height=1080;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(4);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(1);
                    return;
        case  12 :  frame_width=1920;
                    frame_height=1080;
                    chroma_format=1;
                    source_sampling=1;
                    clean_width=1920;
                    clean_height=1080;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(3);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(1);
                    return;
        case  13 :  frame_width=1920;
                    frame_height=1080;
                    chroma_format=1;
                    source_sampling=0;
                    clean_width=1920;
                    clean_height=1080;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(7);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(1);
                    return;
        case  14 :  frame_width=1920;
                    frame_height=1080;
                    chroma_format=1;
                    source_sampling=0;
                    clean_width=1920;
                    clean_height=1080;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(6);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(1);
                    return;
        case  15 :  frame_width=2048;
                    frame_height=1080;
                    chroma_format=0;
                    source_sampling=0;
                    clean_width=2048;
                    clean_height=1080;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(2);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(1);
                    return;
        case  16 :  frame_width=4096;
                    frame_height=2160;
                    chroma_format=0;
                    source_sampling=0;
                    clean_width=4096;
                    clean_height=2160;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate(2);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio(1);
                    return;
        default  :  frame_width=0;
                    frame_height=0;
                    chroma_format=(int32u)-1;
                    source_sampling=(int32u)-1;
                    clean_width=0;
                    clean_height=0;
                    clean_left_offset=0;
                    clean_top_offset=0;
                    frame_rate=Dirac_frame_rate((int32u)-1);
                    pixel_aspect_ratio=Dirac_pixel_aspect_ratio((int32u)-1);
                    return;
    }
}

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
File_Dirac::File_Dirac()
:File__Analyze()
{
    //In
    Frame_Count_Valid=1;
}

//***************************************************************************
// Format
//***************************************************************************

//---------------------------------------------------------------------------
void File_Dirac::Read_Buffer_Continue()
{
    //Integrity
    if (File_Offset==0 && Detect_NonDirac())
        return;
}

//---------------------------------------------------------------------------
void File_Dirac::Read_Buffer_Finalize()
{
    if (Streams.empty())
        return; //Not initialized

    //In case of partial data, and finalizing is forced (example: DecConfig in .mp4), but with at least one frame
    if (Count_Get(Stream_General)==0 && Frame_Count>0)
        picture_Fill();

    //Purge what is not needed anymore
    if (!File_Name.empty()) //Only if this is not a buffer, with buffer we can have more data
        Streams.clear();
}

//***************************************************************************
// Buffer
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Dirac::Header_Begin()
{
    //Must have enough buffer for having header
    if (Buffer_Offset+5>Buffer_Size)
        return false;

    //Quick test of synchro
    if (Synched && CC4(Buffer+Buffer_Offset)!=0x42424344) //"BBCD"
    {
        Trusted_IsNot("Dirac, Synchronisation lost");
        Synched=false;
    }

    //Synchro
    if (!Synched && !Synchronize())
        return false;

    //Quick search
    if (!Header_Parser_QuickSearch())
        return false;

    //All should be OK...
    return true;
}

//---------------------------------------------------------------------------
void File_Dirac::Header_Parse()
{
    //Parsing
    int32u Next_Parse_Offset, Previous_Parse_Offset;
    int8u  Parse_Code;
    Skip_C4(                                                    "Parse Info Prefix");
    Get_B1 (Parse_Code,                                         "Parse Code");
    Get_B4 (Next_Parse_Offset,                                  "Next Parse Offset");
    Get_B4 (Previous_Parse_Offset,                              "Previous Parse Offset");

    //Filling
    Header_Fill_Code(Parse_Code, Ztring().From_CC1(Parse_Code));
    Header_Fill_Size(Next_Parse_Offset);
}

//---------------------------------------------------------------------------
void File_Dirac::Data_Parse()
{
    //Parsing
    switch (Element_Code)
    {
        case 0x00 : Sequence_header(); break;
        case 0x10 : End_of_Sequence(); break;
        case 0x20 : Auxiliary_data(); break;
        case 0x30 : Padding_data(); break;
        case 0x0C : Intra_Reference_Picture(); break;
        case 0x08 : Intra_Non_Reference_Picture(); break;
        case 0x4C : Intra_Reference_Picture_No(); break;
        case 0x48 : Intra_Non_Reference_Picture_No(); break;
        case 0x0D : Inter_Reference_Picture_1(); break;
        case 0x0E : Inter_Reference_Picture_2(); break;
        case 0x09 : Inter_Non_Reference_Picture_1(); break;
        case 0x0A : Inter_Non_Reference_Picture_2(); break;
        case 0xCC : Reference_Picture_Low(); break;
        case 0xC8 : Intra_Non_Reference_Picture_Low(); break;
        default   : Reserved();
    }
}

//***************************************************************************
// Elements
//***************************************************************************

//---------------------------------------------------------------------------
// Packet "00"
void File_Dirac::Sequence_header()
{
    Element_Name("Sequence header");

    //Parsing
    int32u version_major, version_minor, profile, level, base_video_format;
    BS_Begin();
    Get_UI(version_major,                                       "version major");
    Get_UI(version_minor,                                       "version minor");
    Get_UI(profile,                                             "profile");
    Get_UI(level,                                               "level");

    if (version_major<=2)
    {
        Get_UI(base_video_format,                               "base video format"); //Param_Info(Dirac_base_video_format(base_video_format));
        Dirac_base_video_format(base_video_format, frame_width, frame_height, chroma_format, source_sampling,
                                clean_width, clean_height, clean_left_offset, clean_top_offset,
                                frame_rate, pixel_aspect_ratio);
        TEST_SB_SKIP(                                           "custom dimensions flag");
            Get_UI (frame_width,                                "frame width");
            Get_UI (frame_height,                               "frame height");
        TEST_SB_END();
        TEST_SB_SKIP(                                           "custom chroma format flag");
            Get_UI (chroma_format,                              "chroma format"); Param_Info(Dirac_chroma_format(chroma_format));
        TEST_SB_END();
        TEST_SB_SKIP(                                           "custom scan format flag");
            Get_UI (source_sampling,                            "source sampling"); Param_Info(Dirac_source_sampling(source_sampling));
        TEST_SB_END();
        TEST_SB_SKIP(                                           "frame rate flag");
            int32u frame_rate_index;
            Get_UI (frame_rate_index,                           "index"); Param_Info(Dirac_frame_rate(frame_rate_index));
            if (frame_rate_index==0)
            {
                int32u frame_rate_numer, frame_rate_denom;
                Get_UI (frame_rate_numer,                       "frame rate numer");
                Get_UI (frame_rate_denom,                       "frame rate denom");
                frame_rate=((float32)frame_rate_numer)/((float32)frame_rate_denom);
            }
            else
                frame_rate=Dirac_frame_rate(frame_rate_index);
        TEST_SB_END();
        TEST_SB_SKIP(                                           "pixel aspect ratio flag");
            int32u pixel_aspect_ratio_index;
            Get_UI (pixel_aspect_ratio_index,                   "index"); Param_Info(Dirac_pixel_aspect_ratio(pixel_aspect_ratio_index));
            if (pixel_aspect_ratio_index==0)
            {
                int32u pixel_aspect_ratio_numer, pixel_aspect_ratio_denom;
                Get_UI (pixel_aspect_ratio_numer,               "pixel aspect ratio numer");
                Get_UI (pixel_aspect_ratio_denom,               "pixel aspect ratio denom");
                pixel_aspect_ratio=((float32)pixel_aspect_ratio_numer)/((float32)pixel_aspect_ratio_denom);
            }
            else
                pixel_aspect_ratio=Dirac_pixel_aspect_ratio(pixel_aspect_ratio_index);
        TEST_SB_END();
        TESTELSE_SB_SKIP(                                       "custom clean area flag");
            Get_UI (clean_width,                                "clean width");
            Get_UI (clean_height,                               "clean height");
            Get_UI (clean_left_offset,                          "clean left offset");
            Get_UI (clean_top_offset,                           "clean top offset");
        TESTELSE_SB_ELSE(                                       "custom clean area flag");
            clean_width=frame_width;
            clean_height=frame_height;
        TESTELSE_SB_END();
        TEST_SB_SKIP(                                           "custom signal range flag");
            int32u custom_signal_range_index;
            Get_UI(custom_signal_range_index,                   "index");
            if (custom_signal_range_index==0)
            {
                Skip_UI(                                        "luma offset");
                Skip_UI(                                        "luma excursion");
                Skip_UI(                                        "chroma offset");
                Skip_UI(                                        "chroma excursion");
            }
        TEST_SB_END();
        TEST_SB_SKIP(                                           "custom colour spec flag");
            int32u custom_colour_spec_index;
            Get_UI(custom_colour_spec_index,                    "index");
            if (custom_colour_spec_index==0)
            {
                TEST_SB_SKIP(                                   "custom colour primaries flag");
                    Skip_UI(                                    "custom colour primaries index");
                TEST_SB_END();
                TEST_SB_SKIP(                                   "colour matrix flag");
                    Skip_UI(                                    "colour matrix index");
                TEST_SB_END();
                TEST_SB_SKIP(                                   "custom transfer function flag");
                    Skip_UI(                                    "custom transfer function index");
                TEST_SB_END();
            }
        TEST_SB_END();
        Info_UI(picture_coding_mode,                            "picture coding mode"); Param_Info(Dirac_picture_coding_mode(picture_coding_mode));
    }
    else
    {
        Skip_XX(Element_Size-Element_Offset,                    "Unknown");
    }

    FILLING_BEGIN();
        //Autorisation of other streams
        Streams[0x10].Searching_Payload=true; //End_of_Sequence
        Streams[0x20].Searching_Payload=true; //Auxiliary_data
        Streams[0x30].Searching_Payload=true; //Padding_data
        Streams[0x0C].Searching_Payload=true; //Intra_Reference_Picture
        Streams[0x08].Searching_Payload=true; //Intra_Non_Reference_Picture
        Streams[0x4C].Searching_Payload=true; //Intra_Reference_Picture_No
        Streams[0x48].Searching_Payload=true; //Intra_Non_Reference_Picture_No
        Streams[0x0D].Searching_Payload=true; //Inter_Reference_Picture_1
        Streams[0x0E].Searching_Payload=true; //Inter_Reference_Picture_2
        Streams[0x09].Searching_Payload=true; //Inter_Non_Reference_Picture_1
        Streams[0x0A].Searching_Payload=true; //Inter_Non_Reference_Picture_2
        Streams[0xCC].Searching_Payload=true; //Reference_Picture_Low
        Streams[0xC8].Searching_Payload=true; //Intra_Non_Reference_Picture_Low
    FILLING_END();
}

//---------------------------------------------------------------------------
// Packet "10"
void File_Dirac::End_of_Sequence()
{
    Element_Name("End of Sequence");

    //Parsing
    picture_Fill();
}

//---------------------------------------------------------------------------
// Packet "20"
void File_Dirac::Auxiliary_data()
{
    Element_Name("Auxiliary data");

    //Parsing
    Skip_XX(Element_Size,                                       "Auxiliary data");
}

//---------------------------------------------------------------------------
// Packet "30"
void File_Dirac::Padding_data()
{
    Element_Name("Padding data");

    //Parsing
    Skip_XX(Element_Size,                                       "Padding data");
}

//---------------------------------------------------------------------------
// Packet "0C"
void File_Dirac::Intra_Reference_Picture()
{
    Element_Name("Intra Reference Picture");

    //Parsing
    picture();
}

//---------------------------------------------------------------------------
// Packet "08"
void File_Dirac::Intra_Non_Reference_Picture()
{
    Element_Name("Intra Non Reference Picture");

    //Parsing
    picture();
}

//---------------------------------------------------------------------------
// Packet "4C"
void File_Dirac::Intra_Reference_Picture_No()
{
    Element_Name("Intra Reference Picture (no arithmetic coding)");

    //Parsing
    picture();
}

//---------------------------------------------------------------------------
// Packet "48"
void File_Dirac::Intra_Non_Reference_Picture_No()
{
    Element_Name("Intra Non Reference Picture (no arithmetic coding)");

    //Parsing
    picture();
}

//---------------------------------------------------------------------------
// Packet "0D"
void File_Dirac::Inter_Reference_Picture_1()
{
    Element_Name("Inter Reference Picture (1 picture)");

    //Parsing
    picture();
}

//---------------------------------------------------------------------------
// Packet "0E"
void File_Dirac::Inter_Reference_Picture_2()
{
    Element_Name("Inter Reference Picture (2 pictures)");

    //Parsing
    picture();
}

//---------------------------------------------------------------------------
// Packet "09"
void File_Dirac::Inter_Non_Reference_Picture_1()
{
    Element_Name("Inter Non Reference Picture (1 picture)");

    //Parsing
    picture();
}

//---------------------------------------------------------------------------
// Packet "0A"
void File_Dirac::Inter_Non_Reference_Picture_2()
{
    Element_Name("Inter Non Reference Picture (2 pictures)");

    //Parsing
    picture();
}

//---------------------------------------------------------------------------
// Packet "CC"
void File_Dirac::Reference_Picture_Low()
{
    Element_Name("Reference Picture (low-delay)");

    //Parsing
    picture();
}

//---------------------------------------------------------------------------
// Packet "C8"
void File_Dirac::Intra_Non_Reference_Picture_Low()
{
    Element_Name("Intra Non Reference Picture (low-delay)");

    //Parsing
    picture();
}

//---------------------------------------------------------------------------
void File_Dirac::Reserved()
{
    Element_Name("Reserved");

    Skip_XX(Element_Size,                                       "Unknown");
}

//---------------------------------------------------------------------------
void File_Dirac::picture()
{
    //Parsing
    Skip_XX(Element_Size,                                       "Data");

    FILLING_BEGIN();
        //Counting
        if (File_Offset+Buffer_Offset+Element_Size==File_Size)
            Frame_Count_Valid=Frame_Count; //Finalize frames in case of there are less than Frame_Count_Valid frames

        //Name
        Element_Info(Ztring::ToZtring(Frame_Count));

        //Filling only if not already done
        Frame_Count++;
        if (Frame_Count>=Frame_Count_Valid && Count_Get(Stream_Video)==0)
            picture_Fill();
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Dirac::picture_Fill()
{
    Stream_Prepare(Stream_General);
    Fill(Stream_General, 0, General_Format, "Dirac");
    Stream_Prepare(Stream_Video);
    Fill(Stream_Video, 0, Video_Codec, "Dirac");

    Fill(Stream_Video, StreamPos_Last, Video_Width, clean_width);
    Fill(Stream_Video, StreamPos_Last, Video_Height, clean_height);
    if (pixel_aspect_ratio)
    {
        Fill(Stream_Video, 0, Video_PixelAspectRatio, pixel_aspect_ratio);
        if (clean_height!=0)
            Fill(Stream_Video, StreamPos_Last, Video_DisplayAspectRatio, ((float)clean_width)/clean_height*pixel_aspect_ratio);
    }
    if (frame_rate)
        Fill(Stream_Video, StreamPos_Last, Video_FrameRate, frame_rate);
    Fill(Stream_Video, 0, Video_Chroma, Dirac_chroma_format(chroma_format));
    Fill(Stream_Video, 0, Video_Interlacement, Dirac_source_sampling(source_sampling));

    if (File_Offset+Buffer_Size<File_Size)
    {
        NextCode_Clear();

        Info("Dirac, Jumping to end of file");
        Finnished();
    }
}

//***************************************************************************
// Helpers
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Dirac::Synchronize()
{
    //Synchronizing
    while (Buffer_Offset+5<=Buffer_Size
        && CC4(Buffer+Buffer_Offset)!=0x42424344)  //"BBCD"
        Buffer_Offset++;
    if (Buffer_Offset+5>Buffer_Size)
    {
        //Parsing last bytes
        if (Buffer_Offset+4==Buffer_Size)
        {
            if (CC4(Buffer+Buffer_Offset)!=0x42424344)
            {
                Buffer_Offset++;
                if (CC3(Buffer+Buffer_Offset)!=0x424243)
                {
                    Buffer_Offset++;
                    if (CC2(Buffer+Buffer_Offset)!=0x4242)
                    {
                        Buffer_Offset++;
                        if (CC1(Buffer+Buffer_Offset)!=0x42)
                            Buffer_Offset++;
                    }
                }
            }
        }

        return false;
    }

    //Synched is OK
    Synched=true;
    if (Streams.empty())
    {
        //Count of a Packets
        Frame_Count=0;

        //Temp
        Dirac_base_video_format((int8u)-1, frame_width, frame_height, chroma_format, source_sampling,
                                clean_width, clean_height, clean_left_offset, clean_top_offset,
                                frame_rate, pixel_aspect_ratio);

        //Default stream values
        Streams.resize(0x100);
        Streams[0x00].Searching_Payload=true; //Sequence header
    }
    return true;
}

//---------------------------------------------------------------------------
bool File_Dirac::Header_Parser_QuickSearch()
{
    while (           Buffer_Offset+13<=Buffer_Size
      &&   CC4(Buffer+Buffer_Offset)==0x42424344) //"BBCD"
    {
        //Getting start_code
        int8u start_code=CC1(Buffer+Buffer_Offset+4);

        //Searching start
        if (Streams[start_code].Searching_Payload)
            return true;

        //Getting size
        Buffer_Offset+=BigEndian2int32u(Buffer+Buffer_Offset+5);
    }

    if (Buffer_Offset+13<=Buffer_Size)
        Trusted_IsNot("Dirac, Synchronisation lost");
    Synched=false;
    return Synchronize();
}

//---------------------------------------------------------------------------
bool File_Dirac::Detect_NonDirac ()
{
    //File_Size
    if (File_Size<188*4)
        return false; //We can't do detection

    //Element_Size
    if (Buffer_Size<188*4)
        return true; //Must wait for more data

    //Detect mainly DAT files, and the parser is not enough precise to detect them later
    if (CC4(Buffer)==CC4("RIFF"))
    {
        Finnished();
        return true;
    }

    //Detect TS files, and the parser is not enough precise to detect them later
    while (Buffer_Offset<188 && CC1(Buffer+Buffer_Offset)!=0x47) //Look for first Sync word
        Buffer_Offset++;
    if (Buffer_Offset<188 && CC1(Buffer+Buffer_Offset+188)==0x47 && CC1(Buffer+Buffer_Offset+188*2)==0x47 && CC1(Buffer+Buffer_Offset+188*3)==0x47)
    {
        Finnished();
        return true;
    }
    Buffer_Offset=0;

    //Seems OK
    return false;
}

//***************************************************************************
// Information
//***************************************************************************

//---------------------------------------------------------------------------
void File_Dirac::HowTo(stream_t StreamKind)
{
    switch (StreamKind)
    {
        case (Stream_General) :
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

//***************************************************************************
// C++
//***************************************************************************

} //NameSpace

#endif //MEDIAINFO_DIRAC_YES
