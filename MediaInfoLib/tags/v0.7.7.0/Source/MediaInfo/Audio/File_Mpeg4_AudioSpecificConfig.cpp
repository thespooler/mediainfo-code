// File_Aac - Info for AAC files
// Copyright (C) 2002-2008 Jerome Martinez, Zen@MediaArea.net
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
#if defined(MEDIAINFO_MPEG4_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Audio/File_Mpeg4_AudioSpecificConfig.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//---------------------------------------------------------------------------
const int32u MP4_SamplingRate[]=
{96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050,
 16000, 12000, 11025,  8000,  7350,     0,     0,     0,};

const char* MP4_ID[]=
{
    "MPEG-4",
    "MPEG-2",
};

const char* MP4_Format[]=
{
    "",
    "AAC",                                                      // 1
    "AAC",
    "AAC",
    "AAC",
    "SBR",                                                      // 5
    "AAC Scalable",
    "TwinVQ",
    "CELP",
    "HVXC",
    "",                                                         //10
    ""
    "TTSI",
    "Main synthetic",
    "Wavetable synthesis",
    "General MIDI",
    "Algorithmic Synthesis and Audio FX",                       //15
    "AAC",
    "",
    "ER AAC",
    "ER AAC",
    "ER TwinVQ",                                                //20
    "ER BSAC",
    "ER AAC LD",
    "ER CELP",
    "ER HVXC",
    "ER HILN",
    "ER Parametric",
    "SSC",
    "",
    "",
    "(escape)",
    "Layer-1",
    "Layer-2",
    "Layer-3",
    "DST",
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
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

const char* MP4_Format_Profile[]=
{
    "",
    "Main",                                                     // 1
    "LC",
    "SSR",
    "LTP",
    "",                                                         // 5
    "",
    "",
    "",
    "",
    "",                                                         //10
    ""
    "",
    "",
    "",
    "",                                                         //15
    "",
    "LC",
    "",
    "LTP",
    "",                                                         //20
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

const char* MP4_Profile[]=
{
    "Reserved",
    "A_AAC/MPEG4/MAIN",
    "A_AAC/MPEG4/LC",
    "A_AAC/MPEG4/SSR",
    "A_AAC/MPEG4/LTP",
    "SBR",
    "AAC Scalable",
    "TwinVQ",
    "CELP",
    "HVXC",
    "",
    ""
    "TTSI",
    "Main synthetic",
    "Wavetable synthesis",
    "General MIDI",
    "Algorithmic Synthesis and Audio FX",
    "ER AAC LC",
    "",
    "ER AAC LTP",
    "ER AAC scalable",
    "ER TwinVQ",
    "ER BSAC",
    "ER AAC LD",
    "ER CELP",
    "ER HVXC",
    "ER HILN",
    "ER Parametric",
    "SSC",
    "",
    "",
    "(escape)",
    "Layer-1",
    "Layer-2",
    "Layer-3",
    "DST",
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
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

const int8u MP4_Channels[]=
{
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    8,
};

const char* MP4_ChannelConfiguration[]=
{
    "",
    "C",
    "L R",
    "L C R",
    "Front: L C R, Rear: C",
    "Front: L C R, Rear: L R",
    "Front: L C R, Rear: L R, LFE",
    "Front: L C R, Middle: L C R, Surround: L R, LFE",
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

//***************************************************************************
// Format
//***************************************************************************

//---------------------------------------------------------------------------
void File_Mpeg4_AudioSpecificConfig::Header_Parse()
{
    //Filling
    Header_Fill_Size(Buffer_Size);
    Header_Fill_Code(0, "audioSpecificConfig");
}

//---------------------------------------------------------------------------
void File_Mpeg4_AudioSpecificConfig::Data_Parse()
{
    audioSpecificConfig();
}

//---------------------------------------------------------------------------
// AAC in ES, 2+ bytes
void File_Mpeg4_AudioSpecificConfig::audioSpecificConfig ()
{
    Element_Begin("audioSpecificConfig");

    //Parsing
    int8u samplingFrequencyIndex;
    BS_Begin();
    Get_S1 (5, audioObjectType,                                 "audioObjectType"); Param_Info(MP4_Profile[audioObjectType]);
    if (audioObjectType==31)
    {
        int8u audioObjectTypeExt;
        Get_S1 (6, audioObjectTypeExt,                          "audioObjectTypeExt");
        audioObjectType=32+audioObjectTypeExt; Param_Info(MP4_Profile[audioObjectType]);
    }
    Get_S1 (4, samplingFrequencyIndex,                          "samplingFrequencyIndex"); Param_Info(MP4_SamplingRate[samplingFrequencyIndex]);
    if (samplingFrequencyIndex==0xF)
    {
        Get_S3 (24, samplingFrequency,                          "samplingFrequency");
    }
    else
        samplingFrequency=MP4_SamplingRate[samplingFrequencyIndex];
    Get_S1 (4, channelConfiguration,                            "channelConfiguration"); Param_Info(MP4_ChannelConfiguration[channelConfiguration]);

    sbrPresentFlag=false;
    if (audioObjectType==0x05)
    {
        extensionAudioObjectType=audioObjectType;
        sbrPresentFlag=true;
        Get_S1 (4, samplingFrequencyIndex,                      "extensionSamplingFrequencyIndex"); Param_Info(MP4_SamplingRate[samplingFrequencyIndex]);
        if (samplingFrequencyIndex==0xF)
        {
            Get_S3 (24, samplingFrequency,                      "extensionSamplingFrequency");
        }
        else
            samplingFrequency=MP4_SamplingRate[samplingFrequencyIndex];
        Get_S1 (5, audioObjectType,                             "audioObjectType"); Param_Info(MP4_Profile[audioObjectType]);
        if (audioObjectType==31)
        {
            int8u audioObjectTypeExt;
            Get_S1 (6, audioObjectTypeExt,                      "audioObjectTypeExt");
            audioObjectType=32+audioObjectTypeExt; Param_Info(MP4_Profile[audioObjectType]);
        }
    }
    else
        extensionAudioObjectType=0x00;

    switch(audioObjectType)
    {
        case  1:
        case  2:
        case  3:
        case  4:
        case  6:
        case  7:
        case 17:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23: GASpecificConfig();  break;
        case 8:
        //CelpSpecificConfig();
        break;
        case 9:
        //HvxcSpecificConfig();
        break;
        case 12:
        //TTSSpecificConfig();
        break;
        case 13:
        case 14:
        case 15:
        case 16:
        //StructuredAudioSpecificConfig();
        break;
        case 24:
        //ErrorResilientCelpSpecificConfig();
        break;
        case 25:
        //ErrorResilientHvxcSpecificConfig();
        break;
        case 26:
        case 27:
        //ParametricSpecificConfig();
        break;
        case 28:
        //SSCSpecificConfig();
        break;
        case 32:
        case 33:
        case 34:
        //MPEG_1_2_SpecificConfig();
        break;
        case 35:
        //DSTSpecificConfig();
        break;
        default: ;
    }

    switch (audioObjectType)
    {
        case 17:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
            {
                int8u epConfig;
                Get_S1 (2, epConfig,                            "epConfig");
                if (epConfig==2 || epConfig==3)
                {
                    //ErrorProtectionSpecificConfig();
                }
                if (epConfig==3)
                {
                    bool directMapping;
                    Get_SB (directMapping,                      "directMapping");
                    if (directMapping)
                    {
                        //tbd
                    }
                }
            }
        default : ;
    }
    Element_End();

    FILLING_BEGIN();
        //Filling
        Stream_Prepare(Stream_General);
        Fill(Stream_General, 0, General_Format, "AAC");
        Stream_Prepare(Stream_Audio);
        Fill(Stream_Audio, StreamPos_Last, Audio_Format, MP4_Format[audioObjectType]);
        Fill(Stream_Audio, StreamPos_Last, Audio_Format_Version, "Version 4");
        Fill(Stream_Audio, StreamPos_Last, Audio_Format_Profile, MP4_Format_Profile[audioObjectType]);
        if (audioObjectType==2) //LC
            Fill(Stream_Audio, StreamPos_Last, Audio_Format_Settings_SBR, "No");
        Fill(Stream_Audio, StreamPos_Last, Audio_Codec, MP4_Profile[audioObjectType]);
        Fill(Stream_Audio, StreamPos_Last, Audio_SamplingRate, samplingFrequency);
        if (channelConfiguration)
        {
            Fill(Stream_Audio, StreamPos_Last, Audio_Channel_s_, MP4_Channels[channelConfiguration]);
            Fill(Stream_Audio, StreamPos_Last, Audio_ChannelPositions, MP4_ChannelConfiguration[channelConfiguration]);
        }
        Fill(Stream_Audio, StreamPos_Last, Audio_Resolution, 16);

        //SBR stuff
        if (Data_Remain()>=2 && extensionAudioObjectType!=0x05)
            SBR();
    FILLING_END();

    BS_End();
    Finnished();
}

//---------------------------------------------------------------------------
// GASpecificConfig
void File_Mpeg4_AudioSpecificConfig::GASpecificConfig ()
{
    Element_Begin("GASpecificConfig");
    bool dependsOnCoreCoder, extensionFlag;
    Info_SB(   frameLengthFlag,                                 "frameLengthFlag"); Param_Info(frameLengthFlag==0?1024:960, " bytes");
    Get_SB (   dependsOnCoreCoder,                              "dependsOnCoreCoder");
    if (dependsOnCoreCoder)
        Skip_S2(14,                                             "coreCoderDelay");
    Get_SB (   extensionFlag,                                   "extensionFlag");
    if (channelConfiguration==0)
    {
        //TODO...
    }
    if (audioObjectType==06 || audioObjectType==20)
        Skip_S1(3,                                              "layerNr");
    if (extensionFlag)
    {
        bool extensionFlag3;
        if (audioObjectType==22)
        {
            Skip_S1( 5,                                         "numOfSubFrame");
            Skip_S2(11,                                         "layer_length");
        }
        if (audioObjectType==17
         || audioObjectType==19
         || audioObjectType==20
         || audioObjectType==23)
        {
            Skip_SB(                                            "aacSectionDataResilienceFlag");
            Skip_SB(                                            "aacScalefactorDataResilienceFlag");
            Skip_SB(                                            "aacSpectralDataResilienceFlag");
        }
        Get_SB (   extensionFlag3,                              "extensionFlag3");
        if (extensionFlag3)
        {
            //TODO...
        }
    }
    Element_End();
}

//---------------------------------------------------------------------------
// AAC in ES, SBR part, 3+ bytes
void File_Mpeg4_AudioSpecificConfig::SBR ()
{
    //Parsing
    int16u syncExtensionType;
    int8u  samplingFrequencyIndex;
    Element_Begin("SBR");
    Get_S2 (11, syncExtensionType,                             "syncExtensionType");
    if (syncExtensionType!=0x2B7)
    {
        Element_End();
        return;
    }
    Get_S1 (5, extensionAudioObjectType,                        "extensionAudioObjectType");
    if (extensionAudioObjectType==0x05)
    {
        Get_SB (   sbrPresentFlag,                              "sbrPresentFlag");
        if (sbrPresentFlag)
        {
            Get_S1 (4, samplingFrequencyIndex,                  "extensionSamplingFrequencyIndex"); Param_Info(MP4_SamplingRate[samplingFrequencyIndex]);
            if (samplingFrequencyIndex==0xF)
            {
                Get_S3 (24, samplingFrequency,                  "extensionSamplingFrequency");
            }
            else
                samplingFrequency=MP4_SamplingRate[samplingFrequencyIndex];
        }
    }
    Element_End();

    FILLING_BEGIN();
        //Filling
        if (sbrPresentFlag)
        {
            Fill(Stream_Audio, StreamPos_Last, Audio_Format_Settings, "SBR");
            Fill(Stream_Audio, StreamPos_Last, Audio_Format_Settings_SBR, "Yes", Unlimited, true, true);
            Fill(Stream_Audio, StreamPos_Last, Audio_Format_Settings_PS, "No");
            Ztring Codec=Retrieve(Stream_Audio, StreamPos_Last, Audio_Codec);
            Fill(Stream_Audio, StreamPos_Last, Audio_Codec, Codec+_T("/SBR"), true);
            Fill(Stream_Audio, StreamPos_Last, Audio_SamplingRate, samplingFrequency, 10, true);
        }

        //PS stuff
        if (Data_Remain())
            PS();
    FILLING_END();
}

//---------------------------------------------------------------------------
// AAC in ES, SBR part, 2 bytes?
// Format is unknown
void File_Mpeg4_AudioSpecificConfig::PS ()
{
    //Parsing
    Element_Begin("PS");
    bool PS;
    Skip_S1(11,                                                 "Unknown");
    Get_SB (    PS,                                             "PS present");
    Skip_S1( 4,                                                 "Unknown");
    Element_End();

    FILLING_BEGIN();
        if (PS)
        {
            Fill(Stream_Audio, StreamPos_Last, Audio_Channel_s_, 2, 10, true);
            Fill(Stream_Audio, StreamPos_Last, Audio_Format_Settings, "PS");
            Fill(Stream_Audio, StreamPos_Last, Audio_Format_Settings_PS, "Yes", Unlimited, true, true);
            Ztring Codec=Retrieve(Stream_Audio, StreamPos_Last, Audio_Codec);
            Fill(Stream_Audio, StreamPos_Last, Audio_Codec, Codec+_T("/PS"), true);
            Fill(Stream_Audio, StreamPos_Last, Audio_ChannelPositions, "", Unlimited, true, true);
        }
    FILLING_END();
}

//***************************************************************************
// Information
//***************************************************************************

//---------------------------------------------------------------------------
void File_Mpeg4_AudioSpecificConfig::HowTo(stream_t StreamKind)
{
        if (StreamKind==Stream_General)
    {
        Fill_HowTo("Format", "R");
        Fill_HowTo("BitRate", "R");
        Fill_HowTo("Duration", "R");
    }
    else if (StreamKind==Stream_Audio)
    {
        Fill_HowTo("Codec", "R");
        Fill_HowTo("BitRate", "R");
        Fill_HowTo("Channel(s)", "R");
        Fill_HowTo("SamplingRate", "R");
        Fill_HowTo("Resolution", "R");
    }
}

} //NameSpace

#endif //MEDIAINFO_MPEG4_YES

