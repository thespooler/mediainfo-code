// File_ChannelGrouping - Regrouping PCM streams
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
#if defined(MEDIAINFO_AES3_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Audio/File_ChannelGrouping.h"
#if defined(MEDIAINFO_AES3_YES)
    #include "MediaInfo/Audio/File_Aes3.h"
#endif
#if MEDIAINFO_EVENTS
    #include "MediaInfo/MediaInfo_Events.h"
#endif //MEDIAINFO_EVENTS
#include "MediaInfo/MediaInfo_Config_MediaInfo.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

File_ChannelGrouping::File_ChannelGrouping()
{
    //Configuration
    #if MEDIAINFO_EVENTS
        ParserIDs[0]=MediaInfo_Parser_ChannelGrouping;
    #endif //MEDIAINFO_EVENTS
    #if MEDIAINFO_DEMUX
        Demux_Level=2; //Container
    #endif //MEDIAINFO_DEMUX
    #if MEDIAINFO_TRACE
        Trace_Layers_Update(0); //Container1
    #endif //MEDIAINFO_TRACE

    //In
    ByteDepth=0;
    Common=NULL;
    Channel_Pos=0;
    Channel_Total=1;
    SampleRate=0;
    Endianess=0;

    //Temp
    Buffer_Offset_AlreadyInCommon=0;
    IsPcm_Frame_Count=0;
}

File_ChannelGrouping::~File_ChannelGrouping()
{
    if (Channel_Pos==0)
        delete Common; //Common=NULL;
}

//***************************************************************************
// Streams management
//***************************************************************************

//---------------------------------------------------------------------------
void File_ChannelGrouping::Streams_Fill()
{
    if (Common->Parser->Count_Get(Stream_Audio)==0 || Common->Parser->Get(Stream_Audio, 0, Audio_Format)==_T("PCM"))
    {
        Fill(Stream_General, 0, General_Format, "PCM");
        Stream_Prepare(Stream_Audio);
        Fill(Stream_Audio, 0, Audio_Format, "PCM");
        Fill(Stream_Audio, 0, Audio_Codec, "PCM");
        Fill(Stream_Audio, 0, Audio_BitRate_Mode, "CBR");
        switch (Endianess)
        {
            case 'B' : Fill(Stream_Audio, 0, Audio_Format_Settings_Endianness, "Big"); break;
            case 'L' : Fill(Stream_Audio, 0, Audio_Format_Settings_Endianness, "Little"); break;
            default  : ;
        }
        return;
    }

    if (!Common->IsAes3)
        return; //Nothing to do

    Fill(Stream_General, 0, General_Format, "ChannelGrouping");

    if (Common->Channel_Master!=Channel_Pos)
        return;
    Fill(Common->Parser);
    Merge(*Common->Parser);
}

//---------------------------------------------------------------------------
void File_ChannelGrouping::Streams_Finish()
{
    if (!Common->IsAes3)
        return; //Nothing to do

    if (Common->Channel_Master!=Channel_Pos)
        return;
    Finish(Common->Parser);
    //Merge(*Common->Parser);
}

//***************************************************************************
// Buffer - Global
//***************************************************************************

//---------------------------------------------------------------------------
void File_ChannelGrouping::Read_Buffer_Init()
{
    if (Common==NULL)
    {
        Common=new common;
        Common->Parser=new File_Aes3;
        ((File_Aes3*)Common->Parser)->SampleRate=SampleRate;
        ((File_Aes3*)Common->Parser)->ByteSize=ByteDepth*Channel_Total;
        Common->Channels.resize(Channel_Total);
        for (size_t Pos=0; Pos<Common->Channels.size(); Pos++)
            Common->Channels[Pos]=new common::channel;
        Open_Buffer_Init(Common->Parser);
    }

    Accept(); //Forcing acceptance, no possibility to choose something else or detect PCM
    #if MEDIAINFO_DEMUX
         Demux_UnpacketizeContainer=Config->Demux_Unpacketize_Get();
    #endif //MEDIAINFO_DEMUX
}

//---------------------------------------------------------------------------
void File_ChannelGrouping::Read_Buffer_Continue()
{
    //Handling of multiple frames in one block
    if (Buffer_Size-Buffer_Offset_AlreadyInCommon==0)
    {
        if (Common->Parser && Common->Parser->Buffer_Size)
            Open_Buffer_Continue(Common->Parser, Common->MergedChannel.Buffer+Common->MergedChannel.Buffer_Offset, 0);
        Element_WaitForMoreData();
        return;
    }

    //If basic PCM is already detected
    if (Common->IsPcm)
    {
        if (Buffer_Size==Buffer_Offset_AlreadyInCommon)
        {
            Element_WaitForMoreData();
            return;
        }
        Buffer_Offset_AlreadyInCommon=0;

        #if MEDIAINFO_DEMUX
            Demux_Level=2; //Container
            Demux_Offset=Buffer_Size;
            FrameInfo.PTS=FrameInfo.DTS;
            if (IsPcm_Frame_Count)
                FrameInfo.DUR*=IsPcm_Frame_Count+1;
            Demux_UnpacketizeContainer_Demux();
        #endif //MEDIAINFO_DEMUX

        Skip_XX(Element_Size,                                   "Data");

        if (IsPcm_Frame_Count)
        {
            Frame_Count+=IsPcm_Frame_Count;
            IsPcm_Frame_Count=0;
        }
        Frame_Count++;

        if (!Status[IsFilled])
        {
            Finish();
        }

        return;
    }
    else if (Buffer_Size && Buffer_Size>Buffer_Offset_AlreadyInCommon && !Common->IsAes3)
        IsPcm_Frame_Count++;

    //Demux
    #if MEDIAINFO_DEMUX
        if (Demux_UnpacketizeContainer)
        {
            Common->Parser->Demux_UnpacketizeContainer=true;
            Demux_Level=4; //Intermediate
        }
        Demux(Common->MergedChannel.Buffer+Common->MergedChannel.Buffer_Offset, Common->MergedChannel.Buffer_Size-Common->MergedChannel.Buffer_Offset, ContentType_MainStream);
    #endif //MEDIAINFO_EVENTS

    //Copying to Channel buffer
    if (Common->Channels[Channel_Pos]->Buffer_Size+Buffer_Size-Buffer_Offset_AlreadyInCommon>Common->Channels[Channel_Pos]->Buffer_Size_Max)
        Common->Channels[Channel_Pos]->resize(Common->Channels[Channel_Pos]->Buffer_Size+Buffer_Size-Buffer_Offset_AlreadyInCommon);
    memcpy(Common->Channels[Channel_Pos]->Buffer+Common->Channels[Channel_Pos]->Buffer_Size, Buffer+Buffer_Offset_AlreadyInCommon, Buffer_Size-Buffer_Offset_AlreadyInCommon);
    Common->Channels[Channel_Pos]->Buffer_Size+=Buffer_Size-Buffer_Offset_AlreadyInCommon;
    if (!Common->IsAes3)
        Buffer_Offset_AlreadyInCommon=Buffer_Size;
    else
        Buffer_Offset_AlreadyInCommon=0;
    Common->Channel_Current++;
    if (Common->Channel_Current>=Channel_Total)
        Common->Channel_Current=0;

    //Copying to merged channel
    size_t Minimum=(size_t)-1;
    for (size_t Pos=0; Pos<Common->Channels.size(); Pos++)
        if (Minimum>Common->Channels[Pos]->Buffer_Size-Common->Channels[Pos]->Buffer_Offset)
            Minimum=Common->Channels[Pos]->Buffer_Size-Common->Channels[Pos]->Buffer_Offset;
    while (Minimum>=ByteDepth)
    {
        for (size_t Pos=0; Pos<Common->Channels.size(); Pos++)
        {
            if (Common->MergedChannel.Buffer_Size+Minimum>Common->MergedChannel.Buffer_Size_Max)
                Common->MergedChannel.resize(Common->MergedChannel.Buffer_Size+Minimum);
            memcpy(Common->MergedChannel.Buffer+Common->MergedChannel.Buffer_Size, Common->Channels[Pos]->Buffer+Common->Channels[Pos]->Buffer_Offset, ByteDepth);
            Common->Channels[Pos]->Buffer_Offset+=ByteDepth;
            Common->MergedChannel.Buffer_Size+=ByteDepth;
        }
        Minimum-=ByteDepth;
    }

    if (Common->MergedChannel.Buffer_Size-Common->MergedChannel.Buffer_Offset)
    {
        if (FrameInfo_Next.DTS!=(int64u)-1)
            Common->Parser->FrameInfo=FrameInfo_Next; //AES3 parse has its own buffer management
        else
            Common->Parser->FrameInfo=FrameInfo;
        Open_Buffer_Continue(Common->Parser, Common->MergedChannel.Buffer+Common->MergedChannel.Buffer_Offset, Common->MergedChannel.Buffer_Size-Common->MergedChannel.Buffer_Offset);
        Common->MergedChannel.Buffer_Offset=Common->MergedChannel.Buffer_Size;
    }

    if (!Common->IsAes3 && !Status[IsFilled] && Common->Parser->Status[IsAccepted])
    {
        if (Common->Parser->Get(Stream_Audio, 0, Audio_Format)==_T("PCM"))
            Common->IsPcm=true;
        else
        {
            Common->IsAes3=true;
            if (Common->Channel_Master==(size_t)-1)
                Common->Channel_Master=Channel_Pos;
            Buffer_Offset_AlreadyInCommon=0;
            Fill();
        }
    }

    if (Common->IsAes3)
        Buffer_Offset=Buffer_Size;
    else
        Element_WaitForMoreData();

    if (Common->Parser->Status[IsFinished])
        Finish();

    //Optimize buffer
    for (size_t Pos=0; Pos<Common->Channels.size(); Pos++)
        Common->Channels[Pos]->optimize();
    Common->MergedChannel.optimize();
}

//---------------------------------------------------------------------------
void File_ChannelGrouping::Read_Buffer_Unsynched()
{
    if (Common->Parser)
        Common->Parser->Open_Buffer_Unsynch();

    Buffer_Offset_AlreadyInCommon=0;
}

//***************************************************************************
// C++
//***************************************************************************

} //NameSpace

#endif //MEDIAINFO_AES3_YES

