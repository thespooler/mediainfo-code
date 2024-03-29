// File_Lxf - Info for LXF files
// Copyright (C) 2006-2011 MediaArea.net SARL, Info@MediaArea.net
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
// Compilation conditions
#include "MediaInfo/Setup.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_LXF_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Multiple/File_Lxf.h"
#if defined(MEDIAINFO_DVDIF_YES)
    #include "MediaInfo/Multiple/File_DvDif.h"
#endif
#if defined(MEDIAINFO_MPEGV_YES)
    #include "MediaInfo/Video/File_Mpegv.h"
#endif
#if MEDIAINFO_EVENTS
    #include "MediaInfo/MediaInfo_Events.h"
#endif //MEDIAINFO_EVENTS
#include "MediaInfo/MediaInfo_Config_MediaInfo.h"
#include <bitset>
#include <MediaInfo/MediaInfo_Internal.h>
using namespace std;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

const char* Lxf_Format_Video[16]=
{
    "JPEG",
    "MPEG Video", //Version 1
    "MPEG Video", //Version 2, 4:2:0
    "MPEG Video", //Version 2, 4:2:2
    "DV", //25 Mbps 4:1:1 or 4:2:0
    "DV", //DVCPRO
    "DV", //DVCPRO 50
    "RGB", //RGB uncompressed
    "Gray", //Gray uncompressed
    "MPEG Video", //Version 2, 4:2:2, GOP=9
    "",
    "",
    "",
    "",
    "",
    "",
};

const char* Lxf_PictureType[4]=
{
    "I", //Closed
    "I", //Open
    "P",
    "B",
};

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
File_Lxf::File_Lxf()
:File__Analyze()
{
    //Configuration
    ParserName=_T("LXF");
    #if MEDIAINFO_EVENTS
        ParserIDs[0]=MediaInfo_Parser_Lxf;
        StreamIDs_Width[0]=4; //2 numbers for Code, 2 numbers for subcode
    #endif //MEDIAINFO_EVENTS
    #if MEDIAINFO_DEMUX
        Demux_Level=2; //Container
    #endif //MEDIAINFO_DEMUX
    MustSynchronize=true;
    Buffer_TotalBytes_Fill_Max=(int64u)-1; //Disabling this feature for this format, this is done in the parser
    #if MEDIAINFO_DEMUX
        Demux_EventWasSent_Accept_Specific=true;
    #endif //MEDIAINFO_DEMUX

    //Temp
    LookingForLastFrame=false;
    Stream_Count=0;
    Info_General_StreamSize=0;
    Video_Sizes_Pos=(size_t)-1;
    Audio_Sizes_Pos=(size_t)-1;

    //Seek
    #if MEDIAINFO_SEEK
        SeekRequest=(int64u)-1;
    #endif //MEDIAINFO_SEEK
    Duration_Detected=false;
    LastAudio_BufferOffset=(int64u)-1;
}

//***************************************************************************
// Streams management
//***************************************************************************

//---------------------------------------------------------------------------
void File_Lxf::Streams_Fill()
{
    for (size_t Pos=0; Pos<Videos.size(); Pos++)
        Streams_Fill_PerStream(Videos[Pos].Parser);
    for (size_t Pos=0; Pos<Audios.size(); Pos++)
        Streams_Fill_PerStream(Audios[Pos].Parser);
}

//---------------------------------------------------------------------------
void File_Lxf::Streams_Fill_PerStream(File__Analyze* Parser)
{
    if (Parser==NULL)
        return;

    if (Parser->Count_Get(Stream_Audio) && Config->File_Audio_MergeMonoStreams_Get())
    {
        if (Count_Get(Stream_Audio)==0)
        {
            Merge(*Parser);
            Fill(Stream_Audio, 0, Audio_Channel_s_, Audio_Sizes.size(), 10, true);
            int64u BitRate=Retrieve(Stream_Audio, 0, Audio_BitRate).To_int64u();
            Fill(Stream_Audio, 0, Audio_BitRate, BitRate*Audio_Sizes.size(), 10, true);
            #if MEDIAINFO_DEMUX
                if (Config->Demux_ForceIds_Get())
                {
                    for (size_t Pos=0; Pos<Audio_Sizes.size(); Pos++)
                        Fill(StreamKind_Last, StreamPos_Last, General_ID, 0x200+Pos); //only 1 video stream or only 1 audio stream but with separated channels, artificial id
                }
            #endif //MEDIAINFO_DEMUX
        }
    }
    else
    {
        Merge(*Parser);
        #if MEDIAINFO_DEMUX
            if (Config->Demux_ForceIds_Get())
                Fill(StreamKind_Last, StreamPos_Last, General_ID, 0x100*StreamKind_Last+StreamPos_Last); //only 1 video stream or only 1 audio stream but with separated channels, artificial id
        #endif //MEDIAINFO_DEMUX
    }
}

//---------------------------------------------------------------------------
void File_Lxf::Streams_Finish()
{
    if (Audios_Header.TimeStamp_Begin!=(int64u)-1)
    {
        int64u Duration=float64_int64s(((float64)(Audios_Header.TimeStamp_End-Audios_Header.TimeStamp_Begin))/720);
        int64u FrameCount=float64_int64s(((float64)(Audios_Header.TimeStamp_End-Audios_Header.TimeStamp_Begin))/Audios_Header.Duration);
        for (size_t Pos=0; Pos<Count_Get(Stream_Audio); Pos++)
        {
            Fill(Stream_Audio, Pos, Audio_Duration, Duration);
            Fill(Stream_Audio, Pos, Audio_FrameCount, FrameCount);
        }
        Info_General_StreamSize+=FrameCount*0x48;
    }
    if (Videos_Header.TimeStamp_Begin!=(int64u)-1)
    {
        int64u Duration=float64_int64s(((float64)(Videos_Header.TimeStamp_End-Videos_Header.TimeStamp_Begin))/720);
        int64u FrameCount=float64_int64s(((float64)(Videos_Header.TimeStamp_End-Videos_Header.TimeStamp_Begin))/Videos_Header.Duration);
        for (size_t Pos=0; Pos<Count_Get(Stream_Video); Pos++)
            Fill(Stream_Video, Pos, Video_Duration, Duration);
        Info_General_StreamSize+=FrameCount*0x48;

        if (Count_Get(Stream_Video)==1 && Retrieve(Stream_Video, 0, Video_BitRate).empty())
        {
            for (size_t Pos=0; Pos<Videos.size(); Pos++)
                if (Videos[Pos].BytesPerFrame!=(int64u)-1)
                    Info_General_StreamSize+=Videos[Pos].BytesPerFrame*FrameCount;
            for (size_t Pos=0; Pos<Audios.size(); Pos++)
                if (Audios[Pos].BytesPerFrame!=(int64u)-1)
                    Info_General_StreamSize+=Audios[Pos].BytesPerFrame*Retrieve(Stream_Audio, Pos, Audio_FrameCount).To_int64u();
            Fill(Stream_General, 0, General_StreamSize, Info_General_StreamSize);
            Fill(Stream_Video, 0, Video_StreamSize, File_Size-Info_General_StreamSize);
        }
    }
}

//***************************************************************************
// Buffer - Synchro
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Lxf::Synchronize()
{
    //Synchronizing
    while (Buffer_Offset+8<=Buffer_Size
        && CC8(Buffer+Buffer_Offset)!=0x4C45495443480000LL)
        Buffer_Offset++;

    //Parsing last bytes if needed
    if (Buffer_Offset+8>Buffer_Size)
    {
        if (Buffer_Offset+8==Buffer_Size && CC8(Buffer+Buffer_Offset)!=0x4C45495443480000LL)
            Buffer_Offset++;
        if (Buffer_Offset+7==Buffer_Size && CC7(Buffer+Buffer_Offset)!=0x4C454954434800LL)
            Buffer_Offset++;
        if (Buffer_Offset+6==Buffer_Size && CC6(Buffer+Buffer_Offset)!=0x4C4549544348LL)
            Buffer_Offset++;
        if (Buffer_Offset+5==Buffer_Size && CC5(Buffer+Buffer_Offset)!=0x4C45495443LL)
            Buffer_Offset++;
        if (Buffer_Offset+4==Buffer_Size && CC4(Buffer+Buffer_Offset)!=0x4C454954)
            Buffer_Offset++;
        if (Buffer_Offset+3==Buffer_Size && CC3(Buffer+Buffer_Offset)!=0x4C4549)
            Buffer_Offset++;
        if (Buffer_Offset+2==Buffer_Size && CC2(Buffer+Buffer_Offset)!=0x4C45)
            Buffer_Offset++;
        if (Buffer_Offset+1==Buffer_Size && CC1(Buffer+Buffer_Offset)!=0x4C)
            Buffer_Offset++;
        return false;
    }

    if (!Status[IsAccepted])
    {
        Accept();

        Fill(Stream_General, 0, General_Format, "LXF");
    }

    #if MEDIAINFO_SEEK
        //TimeStamp
        if (SeekRequest!=(int64u)-1)
        {
            if (TimeOffsets.find(File_Offset+Buffer_Offset)==TimeOffsets.end()) //Not already saved
            {
                if (Buffer_Offset+0x48>=Buffer_Size)
                    return false;
                int32u Type       =LittleEndian2int32u(Buffer+Buffer_Offset+16);
                if (Type==0) //Video
                {
                    //Filling with the new frame
                    int64u TimeStamp  =LittleEndian2int64u(Buffer+Buffer_Offset+24);
                    int64u Duration   =LittleEndian2int64u(Buffer+Buffer_Offset+32);
                    int8u  PictureType=(LittleEndian2int8u (Buffer+Buffer_Offset+42)&0xC0)>>6;
                    TimeOffsets[File_Offset+Buffer_Offset]=stream_header(TimeStamp, TimeStamp+Duration, Duration, PictureType);
                    SeekRequest_Divider=2;
                }
            }
            if (Read_Buffer_Seek(2, (int64u)-1, (int64u)-1))
                return false;
        }
    #endif //MEDIAINFO_SEEK

    //Synched is OK
    return true;
}

//---------------------------------------------------------------------------
bool File_Lxf::Synched_Test()
{
    if (Video_Sizes_Pos<Video_Sizes.size())
        return true;
    if (Audio_Sizes_Pos<Audio_Sizes.size())
        return true;

    //Must have enough buffer for having header
    if (Buffer_Offset+16>Buffer_Size)
        return false;

    //Quick test of synchro
    if (CC8(Buffer+Buffer_Offset)!=0x4C45495443480000LL)
        Synched=false;

    //We continue
    return true;
}

//***************************************************************************
// Buffer - Global
//***************************************************************************

//---------------------------------------------------------------------------
void File_Lxf::Read_Buffer_Unsynched()
{
    Video_Sizes.clear();
    Audio_Sizes.clear();
    LastAudio_BufferOffset=(int64u)-1;
    LastAudio_TimeOffset=stream_header();
    Video_Sizes_Pos=(size_t)-1;
    Audio_Sizes_Pos=(size_t)-1;

    for (size_t Pos=0; Pos<Audios.size(); Pos++)
        if (Audios[Pos].Parser)
            Audios[Pos].Parser->Open_Buffer_Unsynch();
    for (size_t Pos=0; Pos<Videos.size(); Pos++)
        if (Videos[Pos].Parser)
            Videos[Pos].Parser->Open_Buffer_Unsynch();
}

//---------------------------------------------------------------------------
#if MEDIAINFO_SEEK
size_t File_Lxf::Read_Buffer_Seek (size_t Method, int64u Value, int64u)
{
    //Parsing
    switch (Method)
    {
        case 0  :   Open_Buffer_Unsynch(); GoTo(Value); return 1;
        case 1  :   Open_Buffer_Unsynch(); GoTo(File_Size*Value/10000); return 1;
        case 2  :   //Timestamp
                    {
                    //Init
                    if (!Duration_Detected)
                    {
                        MediaInfo_Internal MI;
                        MI.Option(_T("File_KeepInfo"), _T("1"));
                        Ztring ParseSpeed_Save=MI.Option(_T("ParseSpeed_Get"), _T(""));
                        Ztring Demux_Save=MI.Option(_T("Demux_Get"), _T(""));
                        MI.Option(_T("ParseSpeed"), _T("0"));
                        MI.Option(_T("Demux"), Ztring());
                        size_t MiOpenResult=MI.Open(File_Name);
                        MI.Option(_T("ParseSpeed"), ParseSpeed_Save); //This is a global value, need to reset it. TODO: local value
                        MI.Option(_T("Demux"), Demux_Save); //This is a global value, need to reset it. TODO: local value
                        if (!MiOpenResult || MI.Get(Stream_General, 0, General_Format)!=_T("LXF"))
                            return 0;
                        for (time_offsets::iterator TimeOffset=((File_Lxf*)MI.Info)->TimeOffsets.begin(); TimeOffset!=((File_Lxf*)MI.Info)->TimeOffsets.end(); TimeOffset++)
                            TimeOffsets[TimeOffset->first]=TimeOffset->second;
                        int64u Duration=float64_int64s(Ztring(MI.Get(Stream_General, 0, _T("Duration"))).To_float64()*720);
                        TimeOffsets[File_Size]=stream_header(Duration, Duration, 0, (int8u)-1);
                        SeekRequest_Divider=2;
                        Duration_Detected=true;
                    }
                    if (Value!=(int64u)-1)
                    {
                        Value=float64_int64s((float64)Value*720/1000000); //Convert in LXF unit (1/720000)
                        time_offsets::iterator End=TimeOffsets.end();
                        End--;
                        if (Value>=End->second.TimeStamp_End)
                            return 2; //Higher than total size
                        SeekRequest=Value;
                    }

                    //Looking if we already have the timestamp
                    int64u SeekRequest_Mini=SeekRequest; if (SeekRequest_Mini>1000000) SeekRequest_Mini-=720; //-1ms
                    int64u SeekRequest_Maxi=SeekRequest+720; //+1ms
                    for (time_offsets::iterator TimeOffset=TimeOffsets.begin(); TimeOffset!=TimeOffsets.end(); TimeOffset++)
                    {
                        if (TimeOffset->second.TimeStamp_Begin<=SeekRequest_Maxi && TimeOffset->second.TimeStamp_End>=SeekRequest_Mini) //If it is found in a frame we know
                        {
                            //Looking for the corresponding I-Frame
                            while (TimeOffset->second.PictureType&0x2 && TimeOffset!=TimeOffsets.begin()) //Not an I-Frame (and not fisrt frame)
                            {
                                time_offsets::iterator Previous=TimeOffset;
                                Previous--;
                                if (Previous->second.TimeStamp_End!=TimeOffset->second.TimeStamp_Begin) //Testing if the previous frame is not known.
                                {
                                    SeekRequest=TimeOffset->second.TimeStamp_Begin-(720+1); //1ms+1, so we are sure to not synch on the current frame again
                                    Open_Buffer_Unsynch();
                                    GoTo((Previous->first+TimeOffset->first)/2);
                                    return 1; //Looking for previous frame

                                }
                                TimeOffset=Previous;
                            }

                            //We got the right I-Frame
                            if (Value==0)
                            {
                                for (size_t Pos=0; Pos<Videos.size(); Pos++)
                                    if (Videos[Pos].Parser)
                                        Videos[Pos].Parser->Unsynch_Frame_Count=0;
                            }
                            Open_Buffer_Unsynch();
                            GoTo(TimeOffset->first);
                            SeekRequest=(int64u)-1;
                            return 1;
                        }

                        if (TimeOffset->second.TimeStamp_Begin>SeekRequest_Maxi) //Testing if too far
                        {
                            time_offsets::iterator Previous=TimeOffset; Previous--;
                            int64u ReferenceOffset;
                            if (File_Offset+Buffer_Offset==TimeOffset->first && TimeOffset->second.TimeStamp_Begin>SeekRequest) //If current frame is already too far
                                ReferenceOffset=File_Offset+Buffer_Offset;
                            else
                                ReferenceOffset=TimeOffset->first;
                            if (SeekRequest_Divider==0)
                            {
                                SeekRequest=Previous->second.TimeStamp_Begin-(720+1); //1ms+1, so we are sure to not synch on the current frame again
                                ReferenceOffset=Previous->first;
                                Previous--;
                                SeekRequest_Divider=2;
                            }
                            Open_Buffer_Unsynch();
                            GoTo(Previous->first+(ReferenceOffset-Previous->first)/SeekRequest_Divider);
                            SeekRequest_Divider*=2;
                            return 1;
                        }
                    }
                    }
                    return 0;
        default :   return (size_t)-1;
    }
}
#endif //MEDIAINFO_SEEK

//***************************************************************************
// Buffer - Per element
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Lxf::Header_Begin()
{
    if (Buffer_Offset+0x48>Buffer_Size)
        return false;

    return true;
}

//---------------------------------------------------------------------------
void File_Lxf::Header_Parse()
{
    if (Video_Sizes_Pos<Video_Sizes.size())
    {
        //Filling
        Header_Fill_Code(0x010100+Video_Sizes_Pos, _T("Stream"));
        Header_Fill_Size(Video_Sizes[Video_Sizes_Pos]);
        Video_Sizes_Pos++;
        return;
    }
    if (Audio_Sizes_Pos<Audio_Sizes.size())
    {
        //Filling
        Header_Fill_Code(0x010200+Audio_Sizes_Pos, _T("Stream"));
        Header_Fill_Size(Audio_Sizes[Audio_Sizes_Pos]);
        Audio_Sizes_Pos++;
        return;
    }

    //Parsing
    int64u BlockSize;
    int32u Type;
    Skip_C8(                                                    "Signature");
    Skip_L4(                                                    "Version"); //0=start and duration are in field, 1=in 27 MHz values
    Skip_L4(                                                    "Header size");
    Get_L4 (Type,                                               "Type");
    Skip_L4(                                                    "Stream ID");
    switch(Type)
    {
        case 0  :   //Video
                    {
                    Video_Sizes.resize(2);
                    int64u Size;
                    int8u Format, GOP_M;
                    BlockSize=0;

                    Info_L8(TimeStamp,                          "TimeStamp"); Param_Info(((float64)TimeStamp)/720, 3, " ms"); FrameInfo.DTS=float64_int64s(((float64)TimeStamp)*1000000/720);
                    Info_L8(Duration,                           "Duration"); Param_Info(((float64)Duration)/720, 3, " ms"); FrameInfo.DUR=float64_int64s(((float64)Duration)*1000000/720);
                    BS_Begin_LE();
                    Get_S1 (4, Format,                          "Format"); Param_Info(Lxf_Format_Video[Format]);
                    Skip_S1(7,                                  "GOP (N)");
                    Get_S1 (3, GOP_M,                           "GOP (M)");
                    Info_S1(8, BitRate,                         "Bit rate"); Param_Info(BitRate*1000000, " bps");
                    Info_S1(2, PictureType,                     "Picture type"); Param_Info(Lxf_PictureType[PictureType]);
                    BS_End_LE();
                    Skip_L1(                                    "Reserved");
                    Get_L8(Size,                                "Video data size");
                    Video_Sizes[1]=Size;
                    BlockSize+=Size;
                    Get_L8(Size,                                "VBI data size");
                    Video_Sizes[0]=Size;
                    BlockSize+=Size;
                    Skip_L4(                                    "? (Always 0x00000000)");
                    Info_L8(Reverse,                            "Reverse TimeStamp"); Param_Info(((float64)Reverse)/720, 3, " ms");
                    if (Videos_Header.TimeStamp_Begin==(int64u)-1)
                        Videos_Header.TimeStamp_Begin=TimeStamp;
                    Videos_Header.TimeStamp_End=TimeStamp+Duration;
                    Videos_Header.Duration=Duration;
                    if (TimeStamp==LastAudio_TimeOffset.TimeStamp_Begin)
                        TimeOffsets[LastAudio_BufferOffset]=stream_header(TimeStamp, TimeStamp+Duration, Duration, PictureType);
                    else
                        TimeOffsets[File_Offset+Buffer_Offset]=stream_header(TimeStamp, TimeStamp+Duration, Duration, PictureType);
                    int64u PTS_Computing=TimeStamp;
                    #if MEDIAINFO_DEMUX
                        switch (PictureType)
                        {
                            case 2 :
                            case 3 : Demux_random_access=false; break; //P-Frame, B-Frame
                            default: Demux_random_access=true ;        //I-Frame
                        }
                    #endif //MEDIAINFO_DEMUX
                    if (GOP_M>1) //With B-frames
                    {
                        switch (PictureType)
                        {
                            case 2 : PTS_Computing+=GOP_M*Duration; break; //P-Frame
                            case 3 :                                break; //B-Frame
                            default: PTS_Computing+=Duration;              //I-Frame
                        }
                    }
                    FrameInfo.PTS=float64_int64s(((float64)PTS_Computing)*1000000/720);
                    }
                    break;
        case 1  :   //Audio
                    {
                    int32u Size;
                    int8u Channels_Count=0;
                    bitset<32> Channels;

                    Info_L8(TimeStamp,                          "TimeStamp"); Param_Info(((float64)TimeStamp)/720, 3, " ms"); FrameInfo.PTS=FrameInfo.DTS=float64_int64s(((float64)TimeStamp)*1000000/720);
                    Info_L8(Duration,                           "Duration"); Param_Info(((float64)Duration)/720, 3, " ms"); FrameInfo.DUR=float64_int64s(((float64)Duration)*1000000/720);
                    BS_Begin_LE();
                    Get_S1 ( 6, SampleSize,                     "Sample size");
                    Skip_S1( 6,                                 "Sample precision");
                    Skip_S1(20,                                 "Reserved");
                    BS_End_LE();
                    Element_Begin("Channels mask");
                        BS_Begin_LE();
                        for (size_t Pos=0; Pos<32; Pos++)
                        {
                            bool Channel;
                            Get_SB(Channel,                     "Channel");
                            Channels[Pos]=Channel;
                            if (Channel)
                                Channels_Count++;
                        }
                        BS_End_LE();
                    Element_End();
                    Get_L4(Size,                                "Block size (divided by ?)");
                    Skip_L4(                                    "Reserved");
                    Skip_L4(                                    "Reserved");
                    Skip_L4(                                    "Reserved");
                    Info_L8(Reverse,                            "Reverse TimeStamp"); Param_Info(((float64)Reverse)/720, 3, " ms");
                    Audio_Sizes.resize(Channels_Count);
                    for (size_t Pos=0; Pos<Audio_Sizes.size(); Pos++)
                        Audio_Sizes[Pos]=Size;
                    BlockSize=Size*Channels_Count;
                    if (Audios_Header.TimeStamp_Begin==(int64u)-1)
                        Audios_Header.TimeStamp_Begin=TimeStamp;
                    Audios_Header.TimeStamp_End=TimeStamp+Duration;
                    Audios_Header.Duration=Duration;
                    LastAudio_BufferOffset=File_Offset+Buffer_Offset;
                    LastAudio_TimeOffset=stream_header(TimeStamp, TimeStamp+Duration, Duration, (int8u)-1);
                    #if MEDIAINFO_DEMUX
                        Demux_random_access=true;
                    #endif //MEDIAINFO_DEMUX
                    }
                    break;
        case 2  :   //Header
                    {
                    Header_Sizes.resize(2);
                    int32u Size;
                    BlockSize=0;

                    Skip_L8(                                    "? (Always 0x00000000)");
                    Skip_L8(                                    "?");
                    Skip_L4(                                    "? (Always 0x00000001)");
                    Get_L4(Size,                                "Block size");
                    Header_Sizes[0]=Size;
                    BlockSize+=Size;
                    Get_L4(Size,                                "Block size");
                    Header_Sizes[1]=Size;
                    BlockSize+=Size;
                    Skip_L4(                                    "? (Always 0x00000000)");
                    Skip_L4(                                    "? (Always 0x00000000)");
                    Skip_L4(                                    "? (Always 0x00000000)");
                    Info_L8(Reverse,                            "Reverse TimeStamp?"); Param_Info(((float64)Reverse)/720, 3, " ms");
                    }
                    break;
        default :   BlockSize=0;
    }

    //Filling
    Header_Fill_Code(Type, Ztring::ToZtring(Type));
    Header_Fill_Size(0x48+BlockSize);
}

//---------------------------------------------------------------------------
void File_Lxf::Data_Parse()
{
    switch(Element_Code)
    {
        case 0  : Video(); break;
        case 1  : Audio(); break;
        case 2  : Header(); break;
        default :
                    if (Element_Code&0x000100)
                        Video_Stream(Element_Code&0xFF);
                    else if (Element_Code&0x000200)
                        Audio_Stream(Element_Code&0xFF);
                    else
                        Skip_XX(Element_Size,                   "Unknown");
    }
}

//***************************************************************************
// Elements
//***************************************************************************

//---------------------------------------------------------------------------
void File_Lxf::Header()
{
    Element_Name("Header");

    for (size_t Pos=0; Pos<Header_Sizes.size(); Pos++)
    {
        switch(Pos)
        {
            case  0 : Header_Info(); break;
            case  1 : Header_Meta(); break;
            default : Skip_XX(Header_Sizes[Pos],                       "Data");
        }
    }
    Header_Sizes.clear();

    Info_General_StreamSize=0x48+Element_Size;

    #if MEDIAINFO_DEMUX
        if (Config->NextPacket_Get() && Config->Event_CallBackFunction_IsSet())
            Config->Demux_EventWasSent=true; //First set is to indicate the user that header is parsed
    #endif //MEDIAINFO_DEMUX
}

//---------------------------------------------------------------------------
void File_Lxf::Header_Info()
{
    Element_Begin("Info?");

    //Parsing
    if (Element_Size==120)
    {
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_C8(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L8(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
        Skip_L4(                                                "Unknown");
    }
    else
        Skip_XX(120,                                            "Unknown");
    Element_End();
}

//---------------------------------------------------------------------------
void File_Lxf::Header_Meta()
{
    Element_Begin("Tags?");

    int64u Offset=0;
    int64u Pos=0;

    while (Offset<Header_Sizes[1])
    {
        int8u Size;
        Get_L1 (Size,                                           "Size");
        if (Size)
        {
            switch (Pos)
            {
                case  0 :   //?
                            {
                            Skip_XX(Size,                         "? (8 opaque bytes)");
                            }
                            break;
                case  1 :   //Library
                            {
                            Ztring Library;
                            Get_UTF8(Size, Library,             "Library?");
                            Fill(Stream_General, 0, General_Encoded_Library, Library);
                            }
                            break;
                case  4 :   //?
                            {
                                if (Size==0x10)
                                {
                                    Skip_L4(                    "0x00000008");
                                    Skip_L4(                    "0x00000000");
                                    Skip_L4(                    "0x00000000");
                                    Skip_L4(                    "0x00000092");
                                }
                                else
                                    Skip_XX(Size,               "Data");
                            }
                            break;
                case  7 :   //Channel?
                            {
                            Ztring Channel;
                            Get_UTF16L(Size, Channel,          "Channel?");
                            Fill(Stream_General, 0, General_ServiceName, Channel);
                            }
                            break;
                case 12 :   //Title
                            {
                            Ztring Title;
                            Get_UTF16L(Size, Title,             "Title");
                            Fill(Stream_General, 0, General_Title, Title);
                            }
                            break;
                case 13 :   //?
                            {
                            Skip_UTF16L(Size,                   "? (in UTF-16)");
                            }
                            break;
                case 20 :   //?
                            {
                            Skip_XX(Size,                         "? (8 opaque bytes)");
                            }
                            break;
                default : Skip_XX(Size,                         "Data");
            }
        }
        Offset+=1+Size;
        Pos++;
    }

    Element_End();
}

//---------------------------------------------------------------------------
void File_Lxf::Audio()
{
    Element_Name("Audio");

    Audio_Sizes_Pos=0;
    Element_ThisIsAList();
}

//---------------------------------------------------------------------------
void File_Lxf::Audio_Stream(size_t Pos)
{
    Element_Begin("Stream");

    #if MEDIAINFO_DEMUX
        #if MEDIAINFO_SEEK
            if (SeekRequest==(int64u)-1)
        #endif //MEDIAINFO_SEEK
        {
            Element_Code=0x0200+Pos;
            if (SampleSize==20 && Config->Demux_PCM_20bitTo16bit_Get())
            {
                //Removing bits 3-0 (Little endian)
                int8u* SixteenBit=new int8u[(size_t)Audio_Sizes[Pos]];
                size_t SixteenBit_Pos=0;
                size_t Buffer_Pos=Buffer_Offset+(size_t)Element_Offset;
                size_t Buffer_Max=Buffer_Offset+(size_t)(Element_Offset+Audio_Sizes[Pos]);

                while (Buffer_Pos+5<=Buffer_Max)
                {
                    int64u Temp=LittleEndian2int40u(Buffer+Buffer_Pos);
                    Temp=((Temp&0xFFFF000000LL)>>8)|((Temp&0xFFFF0LL)>>4);
                    int32s2LittleEndian(SixteenBit+SixteenBit_Pos, (int32s)Temp);
                    SixteenBit_Pos+=4;
                    Buffer_Pos+=5;
                }

                Demux(SixteenBit, SixteenBit_Pos, ContentType_MainStream);
            }
            else
                Demux(Buffer+Buffer_Offset+(size_t)Element_Offset, (size_t)Audio_Sizes[Pos], ContentType_MainStream);
        }
    #endif //MEDIAINFO_DEMUX

    Skip_XX(Audio_Sizes[Pos],                                   Audio_Sizes.size()==2?"PCM":"Unknown format");

    if (Pos>=Audios.size())
        Audios.resize(Pos+1);
    if (Audios[Pos].Parser==NULL)
    {
        //Trying to detect if this is PCM
        int64u BitRate=Audio_Sizes[Pos]*720000*8/(Audios_Header.TimeStamp_End-Audios_Header.TimeStamp_Begin);
        Audios[Pos].BytesPerFrame=Audio_Sizes[Pos];

        Audios[Pos].Parser=new File__Analyze;
        Open_Buffer_Init(Audios[Pos].Parser);
        Audios[Pos].Parser->Accept();
        Audios[Pos].Parser->Stream_Prepare(Stream_Audio);
        Audios[Pos].Parser->Fill(Stream_Audio, StreamPos_Last, Audio_BitRate, BitRate);
        Audios[Pos].Parser->Fill(Stream_Audio, 0, Audio_BitRate_Mode, "CBR");
        Audios[Pos].Parser->Fill(Stream_Audio, StreamPos_Last, Audio_Format, "PCM");
        Audios[Pos].Parser->Fill(Stream_Audio, StreamPos_Last, Audio_SamplingRate, 48000);
        Audios[Pos].Parser->Fill(Stream_Audio, StreamPos_Last, Audio_Channel_s_, 1);
        Audios[Pos].Parser->Fill(Stream_Audio, StreamPos_Last, Audio_BitDepth, SampleSize);
        Audios[Pos].Parser->Fill();
    }

    Element_End();
}

//---------------------------------------------------------------------------
void File_Lxf::Video()
{
    Element_Name("Video");

    Video_Sizes_Pos=Video_Sizes[0]?0:1;
    Element_ThisIsAList();
}

//---------------------------------------------------------------------------
void File_Lxf::Video_Stream(size_t Pos)
{
    if (LookingForLastFrame)
    {
        Skip_XX(Element_Size,                                   "Data");
        return;
    }

    Element_Begin("Stream");

    #if MEDIAINFO_DEMUX
        #if MEDIAINFO_SEEK
            if (SeekRequest==(int64u)-1)
        #endif //MEDIAINFO_SEEK
        {
            if (Pos==1)
            {
                Element_Code=0x0100; //+Pos (no Pos until we know what is the other stream)
                Demux(Buffer+Buffer_Offset+(size_t)Element_Offset, (size_t)Video_Sizes[Pos], ContentType_MainStream);
            }
        }
    #endif //MEDIAINFO_DEMUX

    if (Video_Sizes[Pos]==120000 || Video_Sizes[Pos]==144000)
    {
        #if defined(MEDIAINFO_DVDIF_YES)
            if (Pos>=Videos.size())
                Videos.resize(Pos+1);
            if (Videos[Pos].Parser==NULL)
            {
                Videos[Pos].Parser=new File_DvDif;
                ((File_DvDif*)Videos[Pos].Parser)->IgnoreAudio=true;
                Open_Buffer_Init(Videos[Pos].Parser);
                Stream_Count++;
            }
            Open_Buffer_Continue(Videos[Pos].Parser, Buffer+Buffer_Offset+(size_t)Element_Offset, (size_t)Video_Sizes[Pos]);
            if (Videos[Pos].Parser->Status[IsFilled])
            {
                if (Stream_Count>0)
                    Stream_Count--;
            }
        #else
            Skip_XX(Sizes[Pos],                                     "DV");

            if (Pos>=Videos.size())
                Videos.resize(Pos+1);
            if (Videos[Pos].Parser==NULL)
            {
                int64u BitRate=float64_int64s(((float64)Sizes[Pos])*720000*8/(Videos_Header.TimeStamp_End-Videos_Header.TimeStamp_Begin));
                float64 FrameRate=((float64)1)*720000/(Videos_Header.TimeStamp_End-Videos_Header.TimeStamp_Begin);

                Videos[Pos].Parser=new File__Analyze;
                Open_Buffer_Init(Videos[Pos].Parser);
                Videos[Pos].Parser->Accept();
                Videos[Pos].Parser->Stream_Prepare(Stream_Video);
                Videos[Pos].Parser->Fill(Stream_Video, 0, Video_Format, "DV");
                Videos[Pos].Parser->Fill(Stream_Video, 0, Video_BitRate, BitRate);
                Videos[Pos].Parser->Fill(Stream_Video, 0, Video_BitRate_Mode, "CBR");
                Videos[Pos].Parser->Fill(Stream_Video, 0, Video_FrameRate, FrameRate);
                Videos[Pos].Parser->Fill();
            }
        #endif
    }
    else
    {
        if (Pos==0)
        {
            Skip_XX(Video_Sizes[Pos],                           "VBI data");
            if (Pos>=Videos.size())
                Videos.resize(Pos+1);
            Videos[Pos].BytesPerFrame=Video_Sizes[Pos];
        }
        else
        {
            #if defined(MEDIAINFO_MPEGV_YES)
                if (Pos>=Videos.size())
                    Videos.resize(Pos+1);
                if (Videos[Pos].Parser==NULL)
                {
                    Videos[Pos].Parser=new File_Mpegv;
                    ((File_Mpegv*)Videos[Pos].Parser)->FrameIsAlwaysComplete=true;
                    Open_Buffer_Init(Videos[Pos].Parser);
                    Stream_Count++;
                }
                Open_Buffer_Continue(Videos[Pos].Parser, Buffer+Buffer_Offset+(size_t)Element_Offset, (size_t)Video_Sizes[Pos]);
                if (Videos[Pos].Parser->Status[IsFilled])
                {
                    if (Stream_Count>0)
                        Stream_Count--;
                }
            #else
                Skip_XX(Sizes[Pos],                             "MPEG Video");

                if (Pos>=Videos.size())
                    Videos.resize(Pos+1);
                if (Videos[Pos].Parser==NULL)
                {
                    float64 FrameRate=((float64)1)*720000/(Videos_Header.TimeStamp_End-Videos_Header.TimeStamp_Begin);

                    Videos[Pos].Parser=new File__Analyze;
                    Open_Buffer_Init(Videos[Pos].Parser);
                    Videos[Pos].Parser->Stream_Prepare(Stream_Video);
                    Videos[Pos].Parser->Fill(Stream_Video, 0, Video_Format, "MPEG Video");
                    Videos[Pos].Parser->Fill(Stream_Video, 0, Video_FrameRate, FrameRate);
                }
            #endif
        }
    }

    Element_End();

    FILLING_BEGIN();
        if (Pos==1)
        {
            Frame_Count++;
            if (Frame_Count>6 && Stream_Count==0 && !Status[IsFilled]) //5 video frames for 1 Audio frame
            {
                Fill("LXF");
                if (MediaInfoLib::Config.ParseSpeed_Get()<1)
                {
                    LookingForLastFrame=true;
                    if (2*(File_Offset+Buffer_Offset)<=File_Size)
                        GoToFromEnd(File_Offset+Buffer_Offset);
                }
            }
        }
    FILLING_END();
}

} //NameSpace

#endif //MEDIAINFO_LXF_*


