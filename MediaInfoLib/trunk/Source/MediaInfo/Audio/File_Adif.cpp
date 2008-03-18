// File_Aac_Adif - Info for AAC (ADIF) files
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
#if defined(MEDIAINFO_ADIF_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Audio/File_Adif.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//---------------------------------------------------------------------------
const int32u ADIF_sampling_frequency[]=
{96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050,
 16000, 12000, 11025,  8000,  7350,     0,     0,     0,};

const char* ADIF_object_type[]=
{
    "A_AAC/MPEG4/MAIN",
    "A_AAC/MPEG4/LC",
    "A_AAC/MPEG4/SSR",
    "A_AAC/MPEG4/LTP",
};

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
File_Adif::File_Adif()
:File__Analyze(), File__Tags_Helper()
{
    //File__Tags_Helper
    Base=this;
}

//***************************************************************************
// Format
//***************************************************************************

//---------------------------------------------------------------------------
void File_Adif::Read_Buffer_Continue ()
{
    //Tags
    if (!File__Tags_Helper::Read_Buffer_Continue())
        return;

    if (Buffer_Size-Buffer_Offset<4)
        return;

    //Test
    if (CC4(Buffer+Buffer_Offset)!=CC4("ADIF"))
    {
        Finnished();
        return;
    }
}

//---------------------------------------------------------------------------
bool File_Adif::Header_Begin()
{
    if (!File__Tags_Helper::Header_Begin())
        return false;

    return true;
}

//---------------------------------------------------------------------------
void File_Adif::Header_Parse()
{
    //Parsing
    int8u  num_program_config_elements;
    Skip_C4(                                                    "adif_id");
    BS_Begin();
    TEST_SB_SKIP(                                               "copyright_id_present");
        Skip_S4(32,                                             "copyright_id");
        Skip_S4(32,                                             "copyright_id");
        Skip_S4( 8,                                             "copyright_id");
    TEST_SB_END();
    Skip_SB(                                                    "original_copy");
    Skip_SB(                                                    "home");
    Get_SB (    bitstream_type,                                 "bitstream_type"); Param_Info(bitstream_type?"VBR":"CBR");
    Get_S3 (23, bitrate,                                        "bitrate");
    Get_S1 ( 4, num_program_config_elements,                    "num_program_config_elements");
    if (!bitstream_type)
        Skip_S3(20,                                             "adif_buffer_fullness");
    for (int8u Pos=0; Pos<num_program_config_elements+1; Pos++)
    {
        Element_Begin("program_config_element");
        int8u comment_field_bytes;
        Skip_S1(4,                                              "element_instance_tag");
        Get_S1 (2, object_type,                                 "object_type"); Param_Info(ADIF_object_type[object_type]);
        Get_S1 (4, sampling_frequency_index,                    "sampling_frequency_index"); Param_Info(ADIF_sampling_frequency[sampling_frequency_index]);
        Get_S1 (4, num_front_channel_elements,                  "num_front_channel_elements");
        Get_S1 (4, num_side_channel_elements,                   "num_side_channel_elements");
        Get_S1 (4, num_back_channel_elements,                   "num_back_channel_elements");
        Get_S1 (2, num_lfe_channel_elements,                    "num_lfe_channel_elements");
        Get_S1 (3, num_assoc_data_elements,                     "num_assoc_data_elements");
        Get_S1 (4, num_valid_cc_elements,                       "num_valid_cc_elements");
        TEST_SB_SKIP(                                           "mono_mixdown_present");
            Skip_S1(4,                                          "mono_mixdown_element_number");
        TEST_SB_END();
        TEST_SB_SKIP(                                           "stereo_mixdown_present");
            Skip_S1(4,                                          "stereo_mixdown_element_number");
        TEST_SB_END();
        TEST_SB_SKIP(                                           "matrix_mixdown_idx_present");
            Skip_S1(2,                                          "matrix_mixdown_idx");
            Skip_S1(2,                                          "pseudo_surround_enable");
        TEST_SB_END();
        for (int8u Pos2=0; Pos2<num_front_channel_elements; Pos2++)
        {
            Element_Begin("front_channel_element");
            Skip_SB(                                            "front_element_is_cpe");
            Skip_S1(4,                                          "front_element_tag_select");
            Element_End();
        }
        for (int8u Pos2=0; Pos2<num_side_channel_elements; Pos2++)
        {
            Element_Begin("side_channel_element");
            Skip_SB(                                            "back_element_is_cpe");
            Skip_S1(4,                                          "back_element_tag_select");
            Element_End();
        }
        for (int8u Pos2=0; Pos2<num_back_channel_elements; Pos2++)
        {
            Element_Begin("back_channel_element");
            Skip_SB(                                            "back_element_is_cpe");
            Skip_S1(4,                                          "back_element_tag_select");
            Element_End();
        }
        for (int8u Pos2=0; Pos2<num_lfe_channel_elements; Pos2++)
        {
            Element_Begin("lfe_channel_element");
            Skip_S1(4,                                          "lfe_element_tag_select");
            Element_End();
        }
        for (int8u Pos2=0; Pos2<num_assoc_data_elements; Pos2++)
        {
            Element_Begin("assoc_data_element");
            Skip_S1(4,                                          "assoc_data_element_tag_select");
            Element_End();
        }
        for (int8u Pos2=0; Pos2<num_valid_cc_elements; Pos2++)
        {
            Element_Begin("valid_cc_element");
            Skip_SB(                                            "cc_element_is_ind_sw");
            Skip_S1(4,                                          "valid_cc_element_tag_select");
            Element_End();
        }
        BS_End();
        Get_B1 (comment_field_bytes,                            "comment_field_bytes");
        if (comment_field_bytes>0)
            Get_Local(comment_field_bytes, comment_field_data,  "comment_field_data");
        BS_Begin();
        Element_End();

        //We only support 1 element in ADIF
        Pos=num_program_config_elements;
    }
    BS_End();

    //Filling
    Header_Fill_Size(Element_Offset);
    Header_Fill_Code(0, "Audio Data Interchange Format");
}

//***************************************************************************
// Elements
//***************************************************************************

//---------------------------------------------------------------------------
void File_Adif::Data_Parse()
{
    FILLING_BEGIN();
        //Filling
        if (Count_Get(Stream_Audio)==0)
            Data_Parse_Fill();
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Adif::Data_Parse_Fill()
{
    Stream_Prepare(Stream_General);
    Fill ("Format", "AAC");
    if (!comment_field_data.empty())
        Fill("Comment", comment_field_data);
    Stream_Prepare(Stream_Audio);
    Fill ("Codec", ADIF_object_type[object_type]);
    Fill("BitRate_Mode", bitstream_type?"VBR":"CBR");
    if (bitrate>0) Fill(bitstream_type?"BitRate_Maximum":"BitRate", bitrate);
    Fill("SamplingRate", ADIF_sampling_frequency[sampling_frequency_index]);
    Fill("Channel(s)", num_front_channel_elements+num_side_channel_elements+num_back_channel_elements+num_lfe_channel_elements);
    Fill("Resolution", 16);

    //Jumping if needed
    File__Tags_Helper::Data_GoTo(File_Size, "ADIF");
}

//***************************************************************************
// Information
//***************************************************************************

//---------------------------------------------------------------------------
void File_Adif::HowTo(stream_t StreamKind)
{
        if (StreamKind==Stream_General)
    {
        General[0](_T("Format"), Info_HowTo)=_T("R");
        General[0](_T("BitRate"), Info_HowTo)=_T("R");
        General[0](_T("PlayTime"), Info_HowTo)=_T("R");
    }
    else if (StreamKind==Stream_Audio)
    {
        Audio[0](_T("Codec"), Info_HowTo)=_T("R");
        Audio[0](_T("BitRate"), Info_HowTo)=_T("R");
        Audio[0](_T("Channel(s)"), Info_HowTo)=_T("R");
        Audio[0](_T("SamplingRate"), Info_HowTo)=_T("R");
        Audio[0](_T("Resolution"), Info_HowTo)=_T("R");
    }
}

} //NameSpace

#endif //MEDIAINFO_ADIF_YES

