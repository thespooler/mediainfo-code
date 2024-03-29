// File_Ogg_SubElement - Info for OGG files
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
#if defined(MEDIAINFO_OGG_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Multiple/File_Ogg_SubElement.h"
#include "MediaInfo/Audio/File_Vorbis.h"
#include "MediaInfo/Tag/File_VorbisCom.h"
#include <ZenLib/ZtringListList.h>
#include <ZenLib/BitStream.h>
#include <ZenLib/Utils.h>
#include <cmath>
#include <memory>
using namespace ZenLib;
using namespace std;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
File_Ogg_SubElement::File_Ogg_SubElement()
: File__Analyze()
{
    SetupFinnished=false;

    //Internal
    Setup_Vorbis=NULL;
}

//---------------------------------------------------------------------------
File_Ogg_SubElement::~File_Ogg_SubElement()
{
    delete Setup_Vorbis; //Setup_Vorbis=NULL;
}

//***************************************************************************
// Format
//***************************************************************************

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Read_Buffer_Init()
{
    OldSize=0;
    Setup_Vorbis=NULL;
    absolute_granule_position_Resolution=0;
    StreamKind=Stream_Max;
}

//***************************************************************************
// Buffer
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Ogg_SubElement::Header_Begin()
{
    //Already parsed (there is only one pass)
    if (Buffer_Offset!=0)
        return false;

    //We are waiting for the end of the stream, signaled by a empty buffer adding
    if (Buffer_Size!=OldSize)
    {
        OldSize=Buffer_Size;
        return false;
    }
    else
    {
        OldSize=0;
        return true;
    }
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Header_Parse()
{
    //Parsing
    int64u SamplesCount;
    int32u SamplesCount4;
    int16u SamplesCount2;
    int8u  SamplesCount1, Type;
    bool lenbytes0, lenbytes1, lenbytes2;
    Get_L1 (Type,                                               "Type");
    if ((Type&0x01)==0 && Type!=0x80) //TODO : find a better algo
    {
        Skip_Flags(Type, 0,                                     "Indicates data packet");
        Get_Flags (Type, 1, lenbytes2,                          "Bit 2 of lenbytes");
        Skip_Flags(Type, 2,                                     "unused");
        Skip_Flags(Type, 3,                                     "Keyframe");
        Skip_Flags(Type, 4,                                     "unused");
        Skip_Flags(Type, 5,                                     "unused");
        Get_Flags (Type, 6, lenbytes0,                          "Bit 0 of lenbytes");
        Get_Flags (Type, 7, lenbytes1,                          "Bit 1 of lenbytes");
        if (lenbytes2)
        {
            if (lenbytes1)
            {
                if (lenbytes0)
                    //Get_L7 (SamplesCount,                   "SamplesCount");
                    Element_Offset+=7;
                else
                    //Get_L6 (SamplesCount,                   "SamplesCount");
                    Element_Offset+=6;
            }
            else
            {
                if (lenbytes0)
                    //Get_L5 (SamplesCount,                   "SamplesCount");
                    Element_Offset+=5;
                else
                {
                    Get_L4 (SamplesCount4,                  "SamplesCount");
                    SamplesCount=SamplesCount4;
                }
            }
        }
        else
        {
            if (lenbytes1)
            {
                if (lenbytes0)
                {
                    Get_L3 (SamplesCount4,                  "SamplesCount");
                    SamplesCount=SamplesCount4;
                }
                else
                {
                    Get_L2 (SamplesCount2,                  "SamplesCount");
                    SamplesCount=SamplesCount2;
                }
            }
            else
            {
                if (lenbytes0)
                {
                    Get_L1 (SamplesCount1,                  "SamplesCount");
                    SamplesCount=SamplesCount1;
                }
                //else
                //    Get_L0 (SamplesCount,                   "SamplesCount");
            }
        }
    }

    //Filling
    Header_Fill_Code(Type, Ztring::ToZtring(Type, 16));
    Header_Fill_Size(Element_Size);

    if (Count_Get(Stream_General)==0)
        Stream_Prepare(Stream_General);
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Data_Parse()
{
    //Parsing
    switch (Element_Code)
    {
        case 0x01 : Identification(); break;
        case 0x03 : Comment(); break;
        case 0x05 : Setup(); break;
        case 0x80 : Identification(); break;
        case 0x81 : Comment(); break;
        case 0x82 : Setup(); break;
        default   : Skip_XX(Element_Size,                       "Data");
                    SetupFinnished=true;
    }
}

//---------------------------------------------------------------------------
// Identification chunk, video
// StreamKind                       8 bytes, Pos=0
// Datas                            X bytes, Pos=4
//
void File_Ogg_SubElement::Identification()
{
    Element_Name("Identification");

    //Parsing
    Get_C6 (ID_Identification,                                  "ID");

    //Filling
    #undef ELEMENT_CASE
    #ifdef __BORLANDC__ //Borland converts int64u to int32u
        #define ELEMENT_CASE(_NAME) \
            else if (ID_Identification==Ogg::_NAME##1*0x100000000LL+Ogg::_NAME##2) Identification_##_NAME();

    #else //__BORLANDC__
        #define ELEMENT_CASE(_NAME) \
            else if (ID_Identification==Ogg::_NAME) Identification_##_NAME();

    #endif //__BORLANDC__

    if (0) ;
    ELEMENT_CASE(vorbis)
    ELEMENT_CASE(theora)
    ELEMENT_CASE(video)
    ELEMENT_CASE(audio)
    ELEMENT_CASE(text)
    else
    {
        SetupFinnished=true;
        return;
    }

    //Filling
    StreamKind=StreamKind_Last;
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Identification_vorbis()
{
    Element_Info("Vorbis");

    //Parsing
    int32u Version, SamplingRate, BitRate_Maximum, BitRate_Nominal, BitRate_Minimum;
    int8u Channels;
    Get_L4 (Version,                                            "Version");
    if (Version>0)
        return; //Not supported
    Get_L1 (Channels,                                           "Channels");
    Get_L4 (SamplingRate,                                       "SamplingRate");
    Get_L4 (BitRate_Maximum,                                    "BitRate_Maximum");
    Get_L4 (BitRate_Nominal,                                    "BitRate_Nominal");
    Get_L4 (BitRate_Minimum,                                    "BitRate_Minimum");
    BS_Begin();
    Skip_BS(4,                                                  "BlockSize_0"); //2^Value
    Skip_BS(4,                                                  "BlockSize_1"); //2^Value
    BS_End();
    Skip_L1(                                                    "Framing");

    //Filling
    Stream_Prepare(Stream_Audio);
    Fill("Codec", "Vorbis");
    if (BitRate_Maximum!=0 && BitRate_Maximum<0x80000000) //This is a signed value, and negative values are not OK
        Fill("BitRate_Maximum", BitRate_Maximum);
    if (BitRate_Nominal!=0 && BitRate_Nominal<0x80000000) //This is a signed value, and negative values are not OK
        Fill("BitRate", BitRate_Nominal);
    if (BitRate_Minimum!=0 && BitRate_Minimum<0x80000000) //This is a signed value, and negative values are not OK
        Fill("BitRate_Minimum", BitRate_Minimum);
    Fill("Channel(s)", Channels);
    Fill("SamplingRate", SamplingRate);
    absolute_granule_position_Resolution=SamplingRate;
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Identification_theora()
{
    Element_Info("Theora");

    //Parsing
    int32u Version, PICW=0, PICH=0, FRN=0, FRD=0, PARN=0, PARD=0, NOMBR=0;
    Get_B3 (Version,                                        "Version");
    if (Version==0x030200) //Version 3.2.x
    {
        Skip_B2(                                            "FMBW");
        Skip_B2(                                            "FMBH");
        Get_B3 (PICW,                                       "PICW");
        Get_B3 (PICH,                                       "PICH");
        Skip_B1(                                            "PICX");
        Skip_B1(                                            "PICY");
        Get_B4 (FRN,                                        "FRN");
        Get_B4 (FRD,                                        "FRD");
        Get_B3 (PARN,                                       "PARN");
        Get_B3 (PARD,                                       "PARD");
        Skip_B1(                                            "CS"); // //0=4:2:0, 2=4:2:2, 3=4:4:4
        Get_B3 (NOMBR,                                      "NOMBR"); //The nominal bitrate of the stream
        BS_Begin();
        Skip_BS( 6,                                         "QUAL"); //The quality hint.
        Skip_BS( 5,                                         "KFGSHIFT");
        Skip_BS( 2,                                         "PF"); //The Pixel Format
        Skip_BS( 3,                                         "Reserved");
        BS_End();
    }

    //Filling
    Stream_Prepare(Stream_Video);
    Fill("Codec", "Theora");
    if (Version!=0x030200) //Version 3.2.x
        return;
    Fill("FrameRate", ((float)FRN)/FRD, 3);
    float PixelRatio=1;
    if (PARN && PARN)
        PixelRatio=((float)PARN)/(float)PARN;
    Fill("Width", PICW);
    Fill("Height", PICH);
    Fill("DisplayAspectRatio", ((float)PICW)/((float)PICH)*PixelRatio, 3);
    if (NOMBR)
        Fill("BitRate_Nominal", NOMBR);
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Identification_video()
{
    Element_Info("Video");

    //Parsing
    int64u TimeUnit;
    int32u fccHandler, Width, Height;
    Skip_L2(                                                    "Reserved");
    Get_C4 (fccHandler,                                         "fccHandler");
    Skip_L4(                                                    "SizeOfStructure");
    Get_L8 (TimeUnit,                                           "TimeUnit"); //10000000/TimeUnit is stream tick rate in ticks/sec
    Skip_L4(                                                    "SamplesPerUnit");
    Skip_L8(                                                    "DefaultLengh"); //in media time
    Skip_L4(                                                    "BufferSize");
    Skip_L2(                                                    "BitsPerSample");
    Skip_L2(                                                    "Reserved");
    Get_L4 (Width,                                              "Width");
    Get_L4 (Height,                                             "Height");

    //Filling
    Stream_Prepare(Stream_Video);
    Fill("Codec", Ztring().From_CC4(fccHandler));
    Fill("FrameRate", (float)10000000/(float)TimeUnit, 3);
    Fill("Width", Width);
    Fill("Height", Height);
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Identification_audio()
{
    Element_Info("Audio");

    //Parsing
    int64u TimeUnit, SamplesPerUnit;
    int32u fccHandler, AvgBytesPerSec;
    int16u Channels;
    Skip_L2(                                                    "Reserved");
    Get_C4 (fccHandler,                                         "fccHandler");
    Skip_L4(                                                    "SizeOfStructure");
    Get_L8 (TimeUnit,                                           "TimeUnit"); //10000000/TimeUnit is stream tick rate in ticks/sec
    Get_L8 (SamplesPerUnit,                                     "SamplesPerUnit");
    Skip_L4(                                                    "DefaultLengh"); //in media time
    Skip_L4(                                                    "BufferSize");
    Skip_L2(                                                    "BitsPerSample");
    Skip_L2(                                                    "Reserved");
    Get_L2 (Channels,                                           "Channels");
    Skip_L2(                                                    "BlockAlign");
    Get_L4 (AvgBytesPerSec,                                     "AvgBytesPerSec");

    //Filling
    Stream_Prepare(Stream_Audio);
    Fill("Codec", Ztring().From_CC4(fccHandler));
    if (AvgBytesPerSec<0x80000000) //This is a signed value, and negative values are not OK
        Fill("BitRate", AvgBytesPerSec*8);
    Fill("Channel(s)", Channels==5?6:Channels); //5 channels are 5.1
    Fill("SamplingRate", SamplesPerUnit);
    absolute_granule_position_Resolution=SamplesPerUnit;
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Identification_text()
{
    Element_Info("Text");

    //Parsing
    Skip_L2(                                                    "Reserved");

    //Filling
    Stream_Prepare(Stream_Text);
    Fill("Codec", "Subrip");
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Comment()
{
    Element_Name("Comment");

    //Parsing
    int64u ID;
    Get_C6 (ID,                                                 "ID");

    //Filling
    #undef ELEMENT_CASE
    #ifdef __BORLANDC__ //Borland converts int64u to int32u
        #define ELEMENT_CASE(_NAME) \
            else if (ID==Ogg::_NAME##1*0x100000000LL+Ogg::_NAME##2) Comment_##_NAME();

    #else //__BORLANDC__
        #define ELEMENT_CASE(_NAME) \
            else if (ID==Ogg::_NAME) Comment_##_NAME();

    #endif //__BORLANDC__

    if (0) ;
    ELEMENT_CASE(vorbis)
    ELEMENT_CASE(theora)
    ELEMENT_CASE(video)
    ELEMENT_CASE(audio)
    ELEMENT_CASE(text)
    else
        SetupFinnished=true;

    //Must finnish?
    #undef ELEMENT_CASE
    #ifdef __BORLANDC__ //Borland converts int64u to int32u
        #define ELEMENT_CASE(_NAME) \
            else if (ID_Identification==Ogg::_NAME##1*0x100000000LL+Ogg::_NAME##2) SetupFinnished=true;

    #else //__BORLANDC__
        #define ELEMENT_CASE(_NAME) \
            else if (ID_Identification==Ogg::_NAME) SetupFinnished=true;

    #endif //__BORLANDC__

    if (0) ;
    ELEMENT_CASE(video)
    ELEMENT_CASE(audio)
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Comment_vorbis()
{
    Element_Info("Vorbis");

    //Integrity
    if (Element_Size<6)
        return;

    File_VorbisCom* Vorbis=new File_VorbisCom;
    Vorbis->StreamKind=StreamKind;

    //Open
    Open_Buffer_Init(Vorbis, File_Size, File_Offset+Buffer_Offset+6);
    Open_Buffer_Continue(Vorbis, Buffer+Buffer_Offset+6, (size_t)(Element_Size-6));
    Merge(*Vorbis, Stream_General, 0, 0);
    Merge(*Vorbis, StreamKind, 0, 0);
    Merge(*Vorbis, Stream_Chapters, 0, 0);

    //int32u Element_Offset=Vorbis->Comment_Size;
    delete Vorbis; //Vorbis=NULL;
    /*if (CC1(Buffer+Buffer_Offset+Element_Offset)==0x01) //End bit
        Element_Offset++;

    if (Element_Offset==Element_Size)
        Finnished();

    //Parsing Setup
    while (CC1(Buffer+Buffer_Offset+Element_Offset)==0x00)
        Element_Offset++;

    Buffer_Offset+=Element_Offset;
    Element_Size-=Element_Offset;
    Buffer_Parse();*/
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Comment_theora()
{
    Comment_vorbis();
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Comment_video()
{
    Comment_vorbis();
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Comment_audio()
{
    Comment_vorbis();
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Comment_text()
{
    Comment_vorbis();
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Setup()
{
    Element_Name("Setup");

    //Parsing
    int64u ID;
    Get_C6 (ID,                                                 "ID");

    //Filling
    #undef ELEMENT_CASE
    #ifdef __BORLANDC__ //Borland converts int64u to int32u
        #define ELEMENT_CASE(_NAME) \
            else if (ID==Ogg::_NAME##1*0x100000000LL+Ogg::_NAME##2) Setup_##_NAME();

    #else //__BORLANDC__
        #define ELEMENT_CASE(_NAME) \
            else if (ID==Ogg::_NAME) Setup_##_NAME();

    #endif //__BORLANDC__

    if (0) ;
    ELEMENT_CASE(vorbis)
    //ELEMENT_CASE(theora)
    //ELEMENT_CASE(video)
    //ELEMENT_CASE(audio)
    //ELEMENT_CASE(text)
    SetupFinnished=true;
}

//---------------------------------------------------------------------------
void File_Ogg_SubElement::Setup_vorbis()
{
    Element_Info("Vorbis");

    //Integrity
    if (Element_Size<6)
        return;

    if (Setup_Vorbis==NULL)
        Setup_Vorbis=new File_Vorbis;

    //Open
    Open_Buffer_Init(Setup_Vorbis, File_Size, File_Offset+Buffer_Offset+6);
    Open_Buffer_Continue(Setup_Vorbis, Buffer+Buffer_Offset+6, (size_t)(Element_Size-6));
    Merge(*Setup_Vorbis, Stream_Audio, 0, 0);
}

//***************************************************************************
// C++
//***************************************************************************

} //NameSpace

#endif //MEDIAINFO_OGG_YES
