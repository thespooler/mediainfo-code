// File_Tak - Info for Tak files
// Copyright (C) 2003-2009 Jerome Martinez, zen@mediaarea.net
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
// Specifications : http://linuxstb.cream.org/tak_format.html
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
// Compilation conditions
#include "MediaInfo/Setup.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_TAK_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Audio/File_Tak.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Const
//***************************************************************************

namespace Elements
{
    const int16u ENDOFMETADATA      =0x00;
    const int16u STREAMINFO         =0x01;
    const int16u SEEKTABLE          =0x02;
    const int16u WAVEMETADATA       =0x03;
    const int16u ENCODERINFO        =0x04;
    const int16u PADDING            =0x05;
}

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
File_Tak::File_Tak()
:File__Analyze(), File__Tags_Helper()
{
    //File__Tags_Helper
    Base=this;
}

//***************************************************************************
// Buffer - File header
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Tak::FileHeader_Begin()
{
    if (!File__Tags_Helper::FileHeader_Begin())
        return false;

    //Synchro
    if (Buffer_Offset+4>Buffer_Size)
        return false;
    if (CC4(Buffer+Buffer_Offset)!=0x7442614B) //"tBaK"
    {
        File__Tags_Helper::Reject("TAK");
        return false;
    }

    return true;
}

//***************************************************************************
// Buffer - File header
//***************************************************************************

//---------------------------------------------------------------------------
void File_Tak::FileHeader_Parse()
{
    Skip_C4(                                                    "Signature");
}

//***************************************************************************
// Buffer - Per element
//***************************************************************************

//---------------------------------------------------------------------------
void File_Tak::Header_Parse()
{
    //Parsing
    int32u block_length;
    int8u block_type;
    Get_L1 (block_type,                                         "Block Type");
    Get_L3 (block_length,                                       "Block Length");

    //Filling
    Header_Fill_Code(block_type, Ztring().From_CC1(block_type));
    Header_Fill_Size(Element_Offset+block_length);
}

//---------------------------------------------------------------------------
void File_Tak::Data_Parse()
{
    #define CASE_INFO(_NAME) \
        case Elements::_NAME : Element_Info(#_NAME); _NAME(); break;

    //Parsing
    switch (Element_Code)
    {
        CASE_INFO(ENDOFMETADATA);
        CASE_INFO(STREAMINFO);
        CASE_INFO(SEEKTABLE);
        CASE_INFO(WAVEMETADATA);
        CASE_INFO(ENCODERINFO);
        CASE_INFO(PADDING);
        default : Skip_XX(Element_Size,                         "Data");
    }
}

//***************************************************************************
// Elements
//***************************************************************************

//---------------------------------------------------------------------------
void File_Tak::ENDOFMETADATA()
{
    File__Tags_Helper::Finish("TAK");
}

//---------------------------------------------------------------------------
void File_Tak::STREAMINFO()
{
    //Parsing
    int32u num_samples_lo, samplerate;
    int8u  num_samples_hi, framesizecode, channels, samplesize;

    Skip_L1 (                                                   "unknown");
    BS_Begin();
    Get_S1 ( 2, num_samples_hi,                                 "num_samples");
    Get_S1 ( 3, framesizecode,                                  "framesizecode");
    Skip_S1( 2,                                                 "unknown");
    BS_End();
    Get_L4 (num_samples_lo,                                     "num_samples");
    Get_L3 (samplerate,                                         "samplerate");
    BS_Begin();
    Skip_S1( 3,                                                 "unknown");
    Get_S1 ( 2, samplesize,                                     "samplesize"); // (00 = 8-bit, 01 = 16-bit and 10 = 24-bit)
    Get_S1 ( 2, channels,                                       "channels");  // # of channels - (0 = mono , 1 = stereo)
    BS_End();
    Skip_L3 (                                                   "crc");

    FILLING_BEGIN()
        //Coherency
        if (samplerate==0)
            return;

        //Computing
        int8u BitPerSample;
        switch (samplesize)
        {
            case  0 : BitPerSample =  8; break;
            case  1 : BitPerSample = 16; break;
            case  2 : BitPerSample = 24; break;
            default : BitPerSample =  0;
        }
        int64u Samples=((int64u)num_samples_hi)<<32 | num_samples_lo;
        int32u SamplingRate=(samplerate/16)+6000;

        //Filling
        File__Tags_Helper::Stream_Prepare(Stream_General);
        Fill(Stream_General, 0, General_Format, "TAK");
        File__Tags_Helper::Stream_Prepare(Stream_Audio);
        Fill(Stream_Audio, 0, Audio_Format, "TAK");
        Fill(Stream_Audio, 0, Audio_Codec, "TAK");
        Fill(Stream_Audio, 0, Audio_SamplingRate, SamplingRate);
        Fill(Stream_Audio, 0, Audio_Channel_s_, channels?2:1);
        if (BitPerSample)
            Fill(Stream_Audio, 0, Audio_Resolution, BitPerSample);
        Fill(Stream_Audio, 0, Audio_Duration, Samples*1000/SamplingRate);

        File__Tags_Helper::Accept("TAK");
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Tak::ENCODERINFO()
{
    //
}

//***************************************************************************
// C++
//***************************************************************************

} //NameSpace

#endif //MEDIAINFO_TAK_YES
