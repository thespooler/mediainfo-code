// File_Swf - Info for SWF files
// Copyright (C) 2005-2009 Jerome Martinez, Zen@MediaArea.net
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
#include "MediaInfo/Setup.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_SWF_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Multiple/File_Swf.h"
#include <zlib.h>
using namespace ZenLib;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Infos
//***************************************************************************

//---------------------------------------------------------------------------
const int8u  Swf_SoundType[]=
{
    1,
    2,
};

//---------------------------------------------------------------------------
const int8u  Swf_SoundSize[]=
{
     8,
    16,
};

//---------------------------------------------------------------------------
const int16u Swf_SoundRate[]=
{
     5500,
    11025,
    22050,
    44100,
};

//---------------------------------------------------------------------------
const char* Swf_Format_Audio[]=
{
    "PCM",
    "ADPCM",
    "MPEG Audio",
    "PCM",
    "Nellymoser",
    "Nellymoser",
    "Nellymoser",
    "",
    "",
    "",
    "",
    "Speex",
    "",
    "",
    "",
    "",
};

//---------------------------------------------------------------------------
const char* Swf_Format_Version_Audio[]=
{
    "",
    "",
    "Version 1",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

//---------------------------------------------------------------------------
const char* Swf_Format_Profile_Audio[]=
{
    "",
    "",
    "Layer 3",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

//---------------------------------------------------------------------------
const char* Swf_SoundFormat[]=
{
    "Uncompressed",
    "SWF ADPCM",
    "MPEG-1L3",
    "Uncompressed Little Endian",
    "",
    "",
    "Nellymoser",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

//---------------------------------------------------------------------------
const char* Swf_Format_Video[]=
{
    "",
    "",
    "H.263",
    "Screen video",
    "VP6",
    "VP6",
    "Screen video 2",
    "AVC",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

//---------------------------------------------------------------------------
const char* Swf_Format_Profile_Video[]=
{
    "",
    "",
    "",
    "",
    "",
    "Alpha channel",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

//---------------------------------------------------------------------------
const char* Swf_Codec_Video[]=
{
    "",
    "",
    "Sorenson H263",
    "Screen video",
    "On2 VP6",
    "On2 VP6 with alpha channel",
    "Screen video 2",
    "AVC",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

//***************************************************************************
// Constants
//***************************************************************************

namespace Elements
{
    const int16u End                            =  0; //V1+
    const int16u ShowFrame                      =  1; //V1+
    const int16u DefineShape                    =  2; //V1+
    const int16u PlaceObject                    =  4; //V1+
    const int16u RemoveObject                   =  5; //V1+
    const int16u DefineBits                     =  6; //V1+
    const int16u DefineButton                   =  7; //V1+
    const int16u JPEGTables                     =  8; //V1+
    const int16u SetBackgroundColor             =  9; //V1+
    const int16u DefineFont                     = 10; //V1+
    const int16u DefineText                     = 11; //V1+
    const int16u DoAction                       = 12; //V3+
    const int16u DefineFontInfo                 = 13; //V1+
    const int16u DefineSound                    = 14; //V1+
    const int16u StartSound                     = 15; //V1+
    const int16u DefineButtonSound              = 17; //V2+
    const int16u SoundStreamHead                = 18; //V1+
    const int16u SoundStreamBlock               = 19; //V1+
    const int16u DefineBitsLossless             = 20; //V2+
    const int16u DefineBitsJPEG2                = 21; //V2+
    const int16u DefineShape2                   = 22; //V2+
    const int16u DefineCxform                   = 23; //V2+
    const int16u Protect                        = 24; //V2+
    const int16u PlaceObject2                   = 26; //V3+
    const int16u RemoveObject2                  = 28; //V3+
    const int16u DefineShape3                   = 32; //V3+
    const int16u DefineText2                    = 33; //V3+
    const int16u DefineButton2                  = 34; //V3+
    const int16u DefineBitsJPEG3                = 35; //V3+
    const int16u DefineBitsLossless2            = 36; //V3+
    const int16u DefineEditText                 = 37; //V4+
    const int16u DefineSprite                   = 39; //V3+
    const int16u FrameLabel                     = 43; //V3+
    const int16u SoundStreamHead2               = 45; //V3+
    const int16u DefineMorphShape               = 46; //V3+
    const int16u DefineFont2                    = 48; //V3+
    const int16u ExportAssets                   = 56; //V5+
    const int16u ImportAssets                   = 57; //V5+
    const int16u EnableDebugger                 = 58; //V5
    const int16u DoInitAction                   = 59; //V6+
    const int16u DefineVideoStream              = 60; //V6+
    const int16u DefineVideoFrame               = 61; //V6+
    const int16u DefineFontInfo2                = 62; //V6+
    const int16u EnableDebugger2                = 64; //V6+
    const int16u ScriptLimits                   = 65; //V6+
    const int16u SetTabIndex                    = 66; //V7+
    const int16u FileAttributes                 = 69; //V1+
    const int16u PlaceObject3                   = 70; //V8+
    const int16u ImportAssets2                  = 71; //V8+
    const int16u DefineFontAlignZones           = 73; //V8+
    const int16u CSMTextSettings                = 74; //V8+
    const int16u DefineFont3                    = 75; //V8+
    const int16u SymbolClass                    = 76; //V9+
    const int16u Metadata                       = 77; //V1+
    const int16u DefineScalingGrid              = 78; //V8+
    const int16u DoABC                          = 82; //V9+
    const int16u DefineShape4                   = 83; //V8+
    const int16u DefineMorphShape2              = 84; //V8+
    const int16u DefineSceneAndFrameLabelData   = 86; //V9+
    const int16u DefineBinaryData               = 87; //V9+
    const int16u DefineFontName                 = 88; //V9+
    const int16u StartSound2                    = 89; //V9+
}

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
File_Swf::File_Swf()
:File__Analyze()
{
    //In
    Frame_Count_Valid=1024;
    FileLength=0;
    Version=0;

    //Temp
    Frame_Count=0;
}

//***************************************************************************
// Format
//***************************************************************************

//---------------------------------------------------------------------------
void File_Swf::Read_Buffer_Finalize()
{
    if (Count_Get(Stream_General)==0)
        return;
    if (!IsAccepted)
        Accept("SWF");
}

//***************************************************************************
// Buffer
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Swf::FileHeader_Begin()
{
    //Parsing
    if (Buffer_Size<8)
        return false;

    if (CC3(Buffer)!=0x435753) //CWS
        return true;

    //Compressed file
    if (File_Size>16*1024*1024)
        return true; //The file is too big, we will not parse all, only say this is SWF
    if (CC4(Buffer+4)<4*16*1024*1024) //FileLength
        return true; //The file is too big, we will not parse all, only say this is SWF
    Buffer_MaximumSize=(size_t)File_Size;
    if (Buffer_Size!=File_Size)
        return false;
    return true;
}

//---------------------------------------------------------------------------
void File_Swf::FileHeader_Parse()
{
    //Parsing
    int32u Signature;
    if (FileLength==0 && Version==0)
    {
        Element_Begin("SWF header", 8);
            Get_C3 (Signature,                                  "Signature");
            Get_L1 (Version,                                    "Version");
            Get_L4 (FileLength,                                 "FileLength");
        Element_End();
    }
    else
    {
        //Was already done by compressed file handling
        Signature=0x465753;
    }

    //Compressed file handling
    if (Signature==0x435753) //CWS
    {
        Decompress();
        return;
    }

    //Parsing
    //Parsing - BitStream
    float32 FrameRate;
    int32u Nbits, Xmin, Xmax, Ymin, Ymax;
    int16u FrameCount;
    BS_Begin();
    Get_BS (5, Nbits,                                           "Nbits");
    Get_BS (Nbits, Xmin,                                        "Xmin");
    Get_BS (Nbits, Xmax,                                        "Xmax"); Param_Info((Xmax-Xmin)/20, " pixels");
    Get_BS (Nbits, Ymin,                                        "Ymin");
    Get_BS (Nbits, Ymax,                                        "Ymax"); Param_Info((Ymax-Ymin)/20, " pixels");
    BS_End();
    if (Version<=7)
    {
        int8u FrameRate_8;
        Skip_L1(                                                "Ignored");
        Get_L1 (FrameRate_8,                                    "FrameRate");
        FrameRate=FrameRate_8;
    }
    else
    {
        int16u FrameRate_8_8;
        Get_L2(FrameRate_8_8,                                   "FrameRate");
        FrameRate=FrameRate_8_8/0x0100+(((float32)(FrameRate_8_8&0x00FF))/0x0100); //8.8 format
        Param_Info(FrameRate);
    }
    Get_L2 (FrameCount,                                         "FrameCount");

    FILLING_BEGIN();
        //Integrity
        if (Signature!=0x465753 && Signature!=0x435753) //FWS or CWS
        {
            Reject("SWF");
            return;
        }
        Accept("SWF");

        //Filling
        Stream_Prepare(Stream_General);
        Fill(Stream_General, 0, General_Format, "ShockWave");
        Stream_Prepare(Stream_Video);
        Fill(Stream_Video, 0, Video_Width, (Xmax-Xmin)/20);
        Fill(Stream_Video, 0, Video_Height, (Ymax-Ymin)/20);
        if (FrameRate)
            Fill(Stream_Video, 0, Video_FrameRate, FrameRate);
        if (FrameCount)
            Fill(Stream_Video, 0, Video_FrameCount, FrameCount);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Swf::Header_Parse()
{
    //Parsing
    int16u TagCodeAndLength;
    Get_L2 (TagCodeAndLength,                                   "TagCodeAndLength");

    //Filling
    int16u Tag=(TagCodeAndLength&0xFFC0)>>6; Param_Info(Tag);
    Header_Fill_Code(Tag, Ztring().From_Number(Tag, 16));

    //Size
    int16u Length=TagCodeAndLength&0x003F;
    if (Length<0x003F)
    {
        Param_Info(Length, " bytes");

        //Filling
        Header_Fill_Size(Element_Offset+Length);
    }
    else
    {
        int32u Length;
        Get_L4(Length,                                          "Length"); Param_Info(Length, " bytes");

        //Filling
        Header_Fill_Size(Element_Offset+Length);
    }
}

//---------------------------------------------------------------------------
void File_Swf::Data_Parse()
{
    #define LIS2(_ATOM, _NAME) \
        case Elements::_ATOM : \
                if (Level==Element_Level) \
                { \
                    Element_Name(_NAME); \
                    _ATOM(); \
                    Element_ThisIsAList(); \
                } \

    #define ATO2(_ATOM, _NAME) \
                case Elements::_ATOM : \
                        if (Level==Element_Level) \
                        { \
                            if (Element_IsComplete_Get()) \
                            { \
                                Element_Name(_NAME); \
                                _ATOM(); \
                            } \
                            else \
                            { \
                                Element_WaitForMoreData(); \
                                return; \
                            } \
                        } \
                        break; \

    //Parsing
    DATA_BEGIN
    ATO2(End,                           "End");
    ATO2(ShowFrame,                     "ShowFrame");
    ATO2(DefineShape,                   "DefineShape");
    ATO2(PlaceObject,                   "PlaceObject");
    ATO2(RemoveObject,                  "RemoveObject");
    ATO2(DefineBits,                    "DefineBits");
    ATO2(DefineButton,                  "DefineButton");
    ATO2(JPEGTables,                    "JPEGTables");
    ATO2(SetBackgroundColor,            "SetBackgroundColor");
    ATO2(DefineFont,                    "DefineFont");
    ATO2(DefineText,                    "DefineText");
    ATO2(DoAction,                      "DoAction");
    ATO2(DefineFontInfo,                "DefineFontInfo");
    ATO2(DefineSound,                   "DefineSound");
    ATO2(StartSound,                    "StartSound");
    ATO2(DefineButtonSound,             "DefineButtonSound");
    ATO2(SoundStreamHead,               "SoundStreamHead");
    ATO2(SoundStreamBlock,              "SoundStreamBlock");
    ATO2(DefineBitsLossless,            "DefineBitsLossless");
    ATO2(DefineBitsJPEG2,               "DefineBitsJPEG2");
    ATO2(DefineShape2,                  "DefineShape2");
    ATO2(DefineCxform,                  "DefineCxform");
    ATO2(Protect,                       "Protect");
    ATO2(PlaceObject2,                  "PlaceObject2");
    ATO2(RemoveObject2,                 "RemoveObject2");
    ATO2(DefineShape3,                  "DefineShape3");
    ATO2(DefineText2,                   "DefineText2");
    ATO2(DefineButton2,                 "DefineButton2");
    ATO2(DefineBitsJPEG3,               "DefineBitsJPEG3");
    ATO2(DefineBitsLossless2,           "DefineBitsLossless2");
    ATO2(DefineEditText,                "DefineEditText");
    LIS2(DefineSprite,                  "DefineSprite");
        ATOM_BEGIN
        ATO2(ShowFrame,                     "ShowFrame");
        ATO2(PlaceObject,                   "PlaceObject");
        ATO2(RemoveObject,                  "RemoveObject");
        ATO2(StartSound,                    "StartSound");
        ATO2(SoundStreamHead,               "SoundStreamHead");
        ATO2(SoundStreamBlock,              "SoundStreamBlock");
        ATO2(PlaceObject2,                  "PlaceObject2");
        ATO2(RemoveObject2,                 "RemoveObject2");
        ATO2(FrameLabel,                    "FrameLabel");
        ATO2(SoundStreamHead2,              "SoundStreamHead2");
        ATO2(End,                           "End");
        ATOM_END
    ATO2(FrameLabel,                    "FrameLabel");
    ATO2(DefineMorphShape,              "DefineMorphShape");
    ATO2(SoundStreamHead2,              "SoundStreamHead2");
    ATO2(DefineFont2,                   "DefineFont2");
    ATO2(ExportAssets,                  "ExportAssets");
    ATO2(ImportAssets,                  "ImportAssets");
    ATO2(EnableDebugger,                "EnableDebugger");
    ATO2(DoInitAction,                  "DoInitAction");
    ATO2(DefineVideoStream,             "DefineVideoStream");
    ATO2(DefineVideoFrame,              "DefineVideoFrame");
    ATO2(DefineFontInfo2,               "DefineFontInfo2");
    ATO2(EnableDebugger2,               "EnableDebugger2");
    ATO2(ScriptLimits,                  "ScriptLimits");
    ATO2(SetTabIndex,                   "SetTabIndex");
    ATO2(FileAttributes,                "FileAttributes");
    ATO2(PlaceObject3,                  "PlaceObject3");
    ATO2(ImportAssets2,                 "ImportAssets2");
    ATO2(DefineFontAlignZones,          "DefineFontAlignZones");
    ATO2(CSMTextSettings,               "CSMTextSettings");
    ATO2(DefineFont3,                   "DefineFont3");
    ATO2(SymbolClass,                   "SymbolClass");
    ATO2(Metadata,                      "Metadata");
    ATO2(DefineScalingGrid,             "DefineScalingGrid");
    ATO2(DoABC,                         "DoABC");
    ATO2(DefineShape4,                  "DefineShape4");
    ATO2(DefineMorphShape2,             "DefineMorphShape2");
    ATO2(DefineSceneAndFrameLabelData,  "DefineSceneAndFrameLabelData");
    ATO2(DefineBinaryData,              "DefineBinaryData");
    ATO2(DefineFontName,                "DefineFontName");
    ATO2(StartSound2,                   "StartSound2");
    DATA_END

    Frame_Count++;
    if (Frame_Count>=Frame_Count_Valid)
        Data_Finish("SWF");
}

//***************************************************************************
// Elements
//***************************************************************************

//---------------------------------------------------------------------------
void File_Swf::DefineSound()
{
    //Parsing
    int16u SoundId;
    int8u  SoundFormat, SoundRate, SoundSize, SoundType;
    Get_L2 (SoundId,                                            "SoundId");
    BS_Begin();
    Get_S1 (4, SoundFormat,                                     "SoundFormat"); Param_Info(Swf_SoundFormat[SoundFormat]);
    Get_S1 (2, SoundRate,                                       "SoundRate"); Param_Info(Swf_SoundRate[SoundRate], " Hz");
    Get_S1 (1, SoundSize,                                       "SoundSize"); Param_Info(Swf_SoundSize[SoundSize], " bits");
    Get_S1 (1, SoundType,                                       "SoundType"); Param_Info(Swf_SoundType[SoundType], " channel(s)");
    BS_End();
    Skip_L4(                                                    "SoundSampleCount");
    Skip_XX(Element_Size-Element_Offset,                        "SoundData");

    Stream_Prepare(Stream_Audio);
    Fill(Stream_Audio, StreamPos_Last, Audio_ID, SoundId);
    Fill(Stream_Audio, StreamPos_Last, Audio_Format, Swf_Format_Audio[SoundFormat]);
    Fill(Stream_Audio, StreamPos_Last, Audio_Format_Version, Swf_Format_Version_Audio[SoundFormat]);
    Fill(Stream_Audio, StreamPos_Last, Audio_Format_Profile, Swf_Format_Profile_Audio[SoundFormat]);
    Fill(Stream_Audio, StreamPos_Last, Audio_Codec, Swf_SoundFormat[SoundFormat]);
    Fill(Stream_Audio, StreamPos_Last, Audio_SamplingRate, Swf_SoundRate[SoundRate]);
    Fill(Stream_Audio, StreamPos_Last, Audio_Resolution, Swf_SoundSize[SoundSize]);
    Fill(Stream_Audio, StreamPos_Last, Audio_Channel_s_, Swf_SoundType[SoundType]);
}

//---------------------------------------------------------------------------
void File_Swf::SoundStreamHead()
{
    //Parsing
    int16u StreamSoundSampleCount;
    int8u  StreamSoundCompression, StreamSoundRate, StreamSoundType, StreamSoundSize;
    BS_Begin();
    Skip_S1(4,                                                  "Reserved");
    Info_S1(2, PlaybackSoundRate,                               "PlaybackSoundRate"); Param_Info(Swf_SoundRate[PlaybackSoundRate], " Hz");
    Info_S1(1, PlaybackSoundSize,                               "PlaybackSoundSize"); Param_Info(Swf_SoundSize[PlaybackSoundSize], " bits");
    Info_S1(1, PlaybackSoundType,                               "PlaybackSoundType"); Param_Info(Swf_SoundType[PlaybackSoundType], " channel(s)");
    Get_S1 (4, StreamSoundCompression,                          "StreamSoundCompression"); Param_Info(Swf_SoundFormat[StreamSoundCompression]);
    Get_S1 (2, StreamSoundRate,                                 "StreamSoundRate"); Param_Info(Swf_SoundRate[StreamSoundRate], " Hz");
    Get_S1 (1, StreamSoundSize,                                 "StreamSoundSize"); Param_Info(Swf_SoundSize[StreamSoundSize], " bits");
    Get_S1 (1, StreamSoundType,                                 "StreamSoundType"); Param_Info(Swf_SoundType[StreamSoundType], " channel(s)");
    BS_End();
    Get_L2 (StreamSoundSampleCount,                             "StreamSoundSampleCount");
    if (StreamSoundCompression==2)
        Skip_L2(                                                "LatencySeek");

    if (StreamSoundSampleCount>0)
    {
        Stream_Prepare(Stream_Audio);
        Fill(Stream_Audio, StreamPos_Last, Audio_Format, Swf_Format_Audio[StreamSoundCompression]);
        Fill(Stream_Audio, StreamPos_Last, Audio_Format_Version, Swf_Format_Version_Audio[StreamSoundCompression]);
        Fill(Stream_Audio, StreamPos_Last, Audio_Format_Profile, Swf_Format_Profile_Audio[StreamSoundCompression]);
        Fill(Stream_Audio, StreamPos_Last, Audio_Codec, Swf_SoundFormat[StreamSoundCompression]);
        Fill(Stream_Audio, StreamPos_Last, Audio_SamplingRate, Swf_SoundRate[StreamSoundRate]);
        Fill(Stream_Audio, StreamPos_Last, Audio_Resolution, Swf_SoundSize[StreamSoundSize]);
        Fill(Stream_Audio, StreamPos_Last, Audio_Channel_s_, Swf_SoundType[StreamSoundType]);
    }
}

//---------------------------------------------------------------------------
void File_Swf::DefineSprite()
{
    //Parsing
    Skip_B2(                                                    "Character ID of sprite");
    Skip_B2(                                                    "Number of frames in sprite");
}

//---------------------------------------------------------------------------
void File_Swf::DefineVideoStream()
{
    //Parsing
    int16u CharacterID, NumFrames, Width, Height;
    int8u  CodecID;
    Get_L2 (CharacterID,                                        "CharacterID");
    Get_L2 (NumFrames,                                          "NumFrames");
    Get_L2 (Width,                                              "Width");
    Get_L2 (Height,                                             "Height");
    BS_Begin();
    Skip_BS(4,                                                  "VideoFlagsReserved");
    Skip_BS(3,                                                  "VideoFlagsDeblocking");
    Skip_BS(1,                                                  "VideoFlagsSmoothing");
    BS_End();
    Get_L1 (CodecID,                                            "CodecID"); Param_Info(Swf_Format_Video[CodecID]);
    if (CodecID>=16)
        CodecID=0; //Should never happen (FLV is only 4-bit sized)

    Stream_Prepare(Stream_Video);
    Fill(Stream_Video, StreamPos_Last, Video_ID, CharacterID);
    Fill(Stream_Video, StreamPos_Last, Video_Width, Width);
    Fill(Stream_Video, StreamPos_Last, Video_Height, Height);
    Fill(Stream_Video, StreamPos_Last, Video_Format, Swf_Format_Video[CodecID]);
    Fill(Stream_Video, StreamPos_Last, Video_Format_Profile, Swf_Format_Profile_Video[CodecID]);
    Fill(Stream_Video, StreamPos_Last, Video_Codec, Swf_Codec_Video[CodecID]);
    Fill(Stream_Video, StreamPos_Last, Video_FrameCount, NumFrames);
}

//***************************************************************************
// Helpers
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Swf::Decompress()
{
    if (Buffer_Size!=File_Size)
    {
        //We must have the complete file in memory, but this is too big (not handled by FileHeader_Begin()), only saying this is SWF
        Stream_Prepare(Stream_General);
        Fill(Stream_General, 0, General_Format, "ShockWave");
        Stream_Prepare(Stream_Video);
        Finish("SWF");
        return true;
    }

    //Sizes
    unsigned long Source_Size=(unsigned long)(File_Size-8);
    unsigned long Dest_Size=(unsigned long)(FileLength-8);

    //Uncompressing
    int8u* Dest=new int8u[Dest_Size];
    if (uncompress((Bytef*)Dest, &Dest_Size, (const Bytef*)Buffer+Buffer_Offset+8, Source_Size)<0)
    {
        delete[] Dest; //Dest=NULL
        Trusted_IsNot("Error while decompressing");
        Reject("SWF");
        return false;
    }

    Accept("SWF");

    Stream_Prepare(Stream_General);

    File_Swf MI;
    MI.FileLength=FileLength;
    MI.Version=Version;
    Open_Buffer_Init(&MI);
    Open_Buffer_Continue(&MI, Dest, FileLength-8);
    Open_Buffer_Finalize(&MI);
    Merge(MI, Stream_General, 0, 0);
    Merge(MI);
    delete[] Dest; //Dest=NULL;

    Finish("SWF");
    return true;
}

} //NameSpace

#endif //MEDIAINFO_SWF_*

