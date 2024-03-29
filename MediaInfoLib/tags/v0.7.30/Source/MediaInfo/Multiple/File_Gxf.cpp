// File_Gxf - Info for GXF (SMPTE 360M) files
// Copyright (C) 2010-2010 MediaArea.net SARL, Info@MediaArea.net
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
#if defined(MEDIAINFO_GXF_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Multiple/File_Gxf.h"
#if defined(MEDIAINFO_RIFF_YES)
    #include "MediaInfo/Multiple/File_Riff.h"
#endif
#if defined(MEDIAINFO_GXF_YES)
    #include "MediaInfo/Multiple/File_Umf.h"
#endif
#if defined(MEDIAINFO_MPEGV_YES)
    #include "MediaInfo/Video/File_Mpegv.h"
#endif
#if defined(MEDIAINFO_AC3_YES)
    #include "MediaInfo/Audio/File_Ac3.h"
#endif
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Constants
//***************************************************************************

//---------------------------------------------------------------------------
const char* Gxf_Tag_Name(int8u Tag)
{
    switch (Tag)
    {
        case 0x40 : return "Media file name of material";
        case 0x41 : return "First field of material in stream";
        case 0x42 : return "Last field of material in stream";
        case 0x43 : return "Mark in for the stream";
        case 0x44 : return "Mark out for the stream";
        case 0x45 : return "Estimated size of stream in 1024 byte units";
        case 0x46 :
        case 0x47 :
        case 0x48 :
        case 0x49 :
        case 0x4A :
        case 0x4B : return "Reserved";
        case 0x4C : return "Media file name";
        case 0x4D : return "Auxiliary Information";
        case 0x4E : return "Media file system version";
        case 0x4F : return "MPEG auxiliary information";
        case 0x50 : return "Frame rate";
        case 0x51 : return "Lines per frame";
        case 0x52 : return "Fields per frame";
        default   : return "Unknown";
    }
}

//---------------------------------------------------------------------------
const char* Gxf_MediaTypes(int8u Type)
{
    switch (Type)
    {
        case  3 : return "M-JPEG"; //525 lines
        case  4 : return "M-JPEG"; //625 lines
        case  7 : return "SMPTE 12M"; //525 lines
        case  8 : return "SMPTE 12M"; //625 lines
        case  9 : return "PCM"; //24-bit
        case 10 : return "PCM"; //16-bit
        case 11 : return "MPEG-2 Video"; //525 lines
        case 12 : return "MPEG-2 Video"; //625 lines
        case 13 : return "DV"; //25 Mbps, 525 lines
        case 14 : return "DV"; //25 Mbps, 625 lines
        case 15 : return "DV"; //50 Mbps, 525 lines
        case 16 : return "DV"; //50 Mbps, 625 lines
        case 17 : return "AC-3"; //16-bit
        case 18 : return "AES"; //non-PCM
        case 19 : return "Reserved";
        case 20 : return "MPEG-2 Video"; //HD, Main Profile at High Level
        case 21 : return "Ancillary data"; //SMPTE 291M 10-bit type 2 component ancillary data
        case 22 : return "MPEG-1 Video"; //525 lines
        case 23 : return "MPEG-1 Video"; //625 lines
        case 24 : return "SMPTE 12M"; //HD
        default : return "Unknown";
    }
}

//---------------------------------------------------------------------------
stream_t Gxf_MediaTypes_StreamKind(int8u Type)
{
    switch (Type)
    {
        case  3 : return Stream_Video;
        case  4 : return Stream_Video;
        case  7 : return Stream_Max;
        case  8 : return Stream_Max;
        case  9 : return Stream_Audio;
        case 10 : return Stream_Audio;
        case 11 : return Stream_Video;
        case 12 : return Stream_Video;
        case 13 : return Stream_Video;
        case 14 : return Stream_Video;
        case 15 : return Stream_Video;
        case 16 : return Stream_Video;
        case 17 : return Stream_Audio;
        case 18 : return Stream_Audio;
        case 19 : return Stream_Max;
        case 20 : return Stream_Video;
        case 21 : return Stream_Max;
        case 22 : return Stream_Video;
        case 23 : return Stream_Video;
        case 24 : return Stream_Max;
        default : return Stream_Max;
    }
}

//---------------------------------------------------------------------------
const char* Gxf_MediaTypes_Format(int8u Type)
{
    switch (Type)
    {
        case  3 : return "JPEG"; //525 lines
        case  4 : return "JPEG"; //625 lines
        case  9 : return "PCM"; //24-bit
        case 10 : return "PCM"; //16-bit
        case 11 : return "MPEG Video"; //525 lines
        case 12 : return "MPEG Video"; //625 lines
        case 13 : return "Digital Video"; //25 Mbps, 525 lines
        case 14 : return "Digital Video"; //25 Mbps, 625 lines
        case 15 : return "Digital Video"; //50 Mbps, 525 lines
        case 16 : return "Digital Video"; //50 Mbps, 625 lines
        case 17 : return "AC-3"; //16-bit
        case 18 : return "SMPTE 338M, table 1, data type 28"; //SMPTE 338M, table 1, data type 28
        case 20 : return "MPEG Video"; //HD, Main Profile at High Level
        case 22 : return "MPEG Video"; //525 lines
        case 23 : return "MPEG Video"; //625 lines
        default : return "";
    }
}

//---------------------------------------------------------------------------
double Gxf_FrameRate(int32u Content)
{
    switch (Content)
    {
        case 1 : return 60.000;
        case 2 : return 59.940;
        case 3 : return 50.000;
        case 4 : return 30.000;
        case 5 : return 29.970;
        case 6 : return 25.000;
        case 7 : return 24.000;
        case 8 : return 23.976;
        default: return  0.000;
    }
}

//---------------------------------------------------------------------------
int32u Gxf_LinesPerFrame_Height(int32u Content)
{
    switch (Content)
    {
        case 1 : return  480;
        case 2 : return  576;
        case 4 : return 1080;
        case 6 : return  720;
        default: return    0;
    }
}

//---------------------------------------------------------------------------
int32u Gxf_LinesPerFrame_Width(int32u Content)
{
    switch (Content)
    {
        case 1 : return  720;
        case 2 : return  720;
        case 4 : return 1920;
        case 6 : return 1080;
        default: return    0;
    }
}

//---------------------------------------------------------------------------
const char* Gxf_FieldsPerFrame(int32u Tag)
{
    switch (Tag)
    {
        case 1 : return "Progressive";
        case 2 : return "Interlaced";
        default: return "";
    }
}

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
File_Gxf::File_Gxf()
:File__Analyze()
{
    //Configuration
    MustSynchronize=true;
    Buffer_TotalBytes_FirstSynched_Max=64*1024;

    //Temp
    Material_Fields_FieldsPerFrame=(int8u)-1;
    Parsers_Count=0;
    Material_Fields_First_IsValid=false;
    Material_Fields_Last_IsValid=false;
    Material_File_Size_IsValid=false;
    UMF_File=NULL;
    SizeToAnalyze=16*1024*1024;
}

//---------------------------------------------------------------------------
File_Gxf::~File_Gxf()
{
    //Temp
    delete UMF_File; //UMF_File=NULL;
    for (size_t Pos=0; Pos<Cdp_Data.size(); Pos++)
        delete Cdp_Data[Pos]; //Cdp_Data[Pos]=NULL;
}

//***************************************************************************
// Streams management
//***************************************************************************

//---------------------------------------------------------------------------
void File_Gxf::Streams_Finish()
{
    //For each Streams
    for (size_t StreamID=0; StreamID<Streams.size(); StreamID++)
        Streams_Finish_PerStream(StreamID, Streams[StreamID]);

    //Global
    if (Material_Fields_First_IsValid && Material_Fields_Last_IsValid && Material_Fields_FieldsPerFrame!=(int8u)-1)
    {
        Fill(Stream_Video, 0, Video_FrameCount, (Material_Fields_Last-Material_Fields_First)/(Material_Fields_FieldsPerFrame==2?2:1));

        //We trust more the MPEG Video bitrate thant the rest
        //TODO: Chech why there is incohenrency (mainly about Material File size info in the sample)
        if (Retrieve(Stream_Video, 0, Video_Format)==_T("MPEG Video"))
            Fill(Stream_Video, 0, Video_BitRate, Retrieve(Stream_Video, 0, Video_BitRate_Nominal));
    }
    if (Material_File_Size_IsValid)
    {
        //Fill(Stream_General, 0, General_OverallBitRate, ((int64u)Material_File_Size)*1024*8/???);
    }
}

//---------------------------------------------------------------------------
void File_Gxf::Streams_Finish_PerStream(size_t StreamID, stream &Temp)
{
    //Init
    if (Temp.StreamKind==Stream_Max && Temp.MediaType!=21) //and not Ancillary data
        return;
    StreamKind_Last=Temp.StreamKind;
    StreamPos_Last=Temp.StreamPos;

    //By the parser
    if (Temp.MediaType==21) //Ancillary data
    {
        Finish(Temp.Parser);
        size_t Count_Before=Count_Get(Stream_Text);
        Merge(*Temp.Parser);
        if (StreamPos_Last!=(size_t)-1)
        {
            for (size_t Pos=Count_Before; Pos<=StreamPos_Last; Pos++)
            {
                Fill(Stream_Text, Pos, Text_ID, Ztring::ToZtring(StreamID)+_T("-")+Retrieve(Stream_Text, StreamPos_Last, Text_ID), true);
                Fill(Stream_Text, Pos, Text_Title, Streams[StreamID].MediaFileName);
            }
        }
    }
    if (Temp.Parser && Temp.Parser->Status[IsAccepted])
    {
        Finish(Temp.Parser);
        Merge(*Temp.Parser, StreamKind_Last, 0, StreamPos_Last);

        //Special cases
        if (Temp.Parser->Count_Get(Stream_Video) && Temp.Parser->Count_Get(Stream_Text))
        {
            //Video and Text are together
            size_t Text_Count=Temp.Parser->Count_Get(Stream_Text);
            for (size_t Text_Pos=0; Text_Pos<Text_Count; Text_Pos++)
            {
                Stream_Prepare(Stream_Text);
                Merge(*Temp.Parser, Stream_Text, Text_Pos, StreamPos_Last);

                Ztring MuxingMode=Retrieve(Stream_Text, StreamPos_Last, "MuxingMode");
                Fill(Stream_Text, StreamPos_Last, "MuxingMode", _T("Ancillary data / ")+MuxingMode, true);
                if (!IsSub)
                    Fill(Stream_Text, StreamPos_Last, "MuxingMode_MoreInfo", _T("Muxed in Video #")+Ztring().From_Number(Temp.StreamPos+1));
                Ztring ID=Retrieve(Stream_Text, StreamPos_Last, Text_ID);
                Fill(Stream_Text, StreamPos_Last, Text_ID, Retrieve(Stream_Video, Temp.StreamPos, Video_ID)+_T("-")+ID, true);
                Fill(Stream_Text, StreamPos_Last, Text_ID_String, Retrieve(Stream_Video, Temp.StreamPos, Video_ID_String)+_T("-")+ID, true);
                Fill(Stream_Text, StreamPos_Last, Text_Delay, Retrieve(Stream_Video, Temp.StreamPos, Video_Delay), true);
            }

            StreamKind_Last=Temp.StreamKind;
            StreamPos_Last=Temp.StreamPos;
        }
    }
}

//***************************************************************************
// Buffer - Synchro
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Gxf::Synchronize()
{
    //Synchronizing
    while (Buffer_Offset+16<=Buffer_Size)
    {
        while (Buffer_Offset+16<=Buffer_Size)
        {
            if (CC5(Buffer+Buffer_Offset   )==0x0000000001
             && CC2(Buffer+Buffer_Offset+14)==0xE1E2)
                break;
            Buffer_Offset++;
        }

        if (Buffer_Offset+16<=Buffer_Size) //Testing if size is coherant
        {
            //Retrieving some info
            int32u Size=CC4(Buffer+Buffer_Offset+6);

            //Testing
            if (Buffer_Offset+Size+16>Buffer_Size)
                return false; //Need more data
            if (CC5(Buffer+Buffer_Offset+Size   )!=0x0000000001
             || CC2(Buffer+Buffer_Offset+Size+14)!=0xE1E2)
                Buffer_Offset++;
            else
                break;
        }
    }

    //Parsing last bytes if needed
    if (Buffer_Offset+16>Buffer_Size)
    {
        return false;
    }
    
    if (!Status[IsAccepted])
    {
        Accept("GXF");
        Fill(Stream_General, 0, General_Format, "GXF");
        Streams.resize(0x40);
    }

    //Synched is OK
    return true;
}

//---------------------------------------------------------------------------
bool File_Gxf::Synched_Test()
{
    //Must have enough buffer for having header
    if (Buffer_Offset+16>Buffer_Size)
        return false;

    //Quick test of synchro
    if (CC5(Buffer+Buffer_Offset   )!=0x0000000001
     || CC2(Buffer+Buffer_Offset+14)!=0xE1E2)
        Synched=false;

    //Test if the next synchro is available
    int32u PacketLength=BigEndian2int32u(Buffer+Buffer_Offset+6);
    if (File_Offset+Buffer_Offset+PacketLength+16<=File_Size)
    {
        if (Buffer_Offset+PacketLength+16>Buffer_Size)
            return false;
        if (CC5(Buffer+Buffer_Offset+PacketLength   )!=0x0000000001
         || CC2(Buffer+Buffer_Offset+PacketLength+14)!=0xE1E2)
            Synched=false;
    }

    //Clearing Cdp_Data
    if (!Synched)
    {
        for (size_t Pos=0; Pos<Cdp_Data.size(); Pos++)
            delete Cdp_Data[Pos]; //Cdp_Data[Pos]=NULL;
        Cdp_Data.clear();
    }

    //We continue
    return true;
}

//***************************************************************************
// Buffer - Per element
//***************************************************************************

//---------------------------------------------------------------------------
void File_Gxf::Header_Parse()
{
    //Parsing
    int32u PacketLength;
    int8u  PacketType;
    Skip_B5(                                                    "Packet leader");
    Get_B1 (PacketType,                                         "Packet type");
    Get_B4 (PacketLength,                                       "Packet length");
    Skip_B4(                                                    "Reserved");
    Skip_B2(                                                    "Packet trailer");

    //Filling
    Header_Fill_Size(PacketLength);
    Header_Fill_Code(PacketType);
}

//---------------------------------------------------------------------------
void File_Gxf::Data_Parse()
{
    switch (Element_Code)
    {
        case 0x00 : Finish("GXF"); break;
        case 0xBC : map(); break;
        case 0xBF : media(); break;
        case 0xFB : end_of_stream(); break;
        case 0xFC : field_locator_table(); break;
        case 0xFD : UMF_file(); break;
        default: ;
    }
}

//---------------------------------------------------------------------------
void File_Gxf::map()
{
    Element_Name("map");

    //Parsing
    int8u Version;
    Element_Begin("Preamble");
        BS_Begin();
        Mark_1();
        Mark_1();
        Mark_1();
        Get_S1(5, Version,                                      "Version");
        BS_End();
        Skip_B1(                                                "Reserved");
    Element_End();

    Element_Begin("Material Data");
        int16u SectionLength;
        Get_B2 (SectionLength,                                  "Section Length");
        if (Element_Offset+SectionLength>=Element_Size)
            SectionLength=(int16u)(Element_Size-Element_Offset);
        int64u Material_Data_End=Element_Offset+SectionLength;
        while (Element_Offset<Material_Data_End)
        {
            Element_Begin("Tag");
            int8u Tag, DataLength;
            Get_B1(Tag,                                         "Tag");
            Get_B1(DataLength,                                  "Data Length");
            Element_Name(Gxf_Tag_Name(Tag));
            switch (Tag)
            {
                case 0x40 : //Media file name of material
                            {
                            Ztring MediaFileName;
                            Get_Local(DataLength, MediaFileName, "Content");
                            Fill(Stream_General, 0, General_Title, MediaFileName, true);
                            }
                            break;
                case 0x41 : //First field of material in stream
                            if (DataLength==4)
                            {
                                Get_B4 (Material_Fields_First,  "Content");
                                Material_Fields_First_IsValid=true;
                            }
                            else
                                Skip_XX(DataLength,             "Unknown");
                            break;
                case 0x42 : //Last field of material in stream
                            if (DataLength==4)
                            {
                                Get_B4 (Material_Fields_Last,   "Content");
                                Material_Fields_Last_IsValid=true;
                            }
                            else
                                Skip_XX(DataLength,             "Unknown");
                            break;
                case 0x43 : //Mark in for the stream
                            if (DataLength==4)
                                Skip_B4(                        "Content");
                            else
                                Skip_XX(DataLength,             "Unknown");
                            break;
                case 0x44 : //Mark out for the stream
                            if (DataLength==4)
                                Skip_B4(                        "Content");
                            else
                                Skip_XX(DataLength,             "Unknown");
                            break;
                case 0x45 : //Estimated size of stream in 1024 byte units
                            if (DataLength==4)
                            {
                                Get_B4 (Material_File_Size  ,   "Content");
                                Material_File_Size_IsValid=true;
                            }
                            else
                                Skip_XX(DataLength,             "Unknown");
                            break;
                case 0x46 : //Reserved
                            if (DataLength==4)
                                Skip_B4(                        "Content");
                            else
                                Skip_XX(DataLength,             "Unknown");
                            break;
                case 0x47 : //Reserved
                            if (DataLength==8)
                                Skip_B8(                        "Content");
                            else
                                Skip_XX(DataLength,             "Unknown");
                            break;
                case 0x48 : //Reserved
                            Skip_String(DataLength,             "Content");
                            break;
                case 0x49 : //Reserved
                            Skip_String(DataLength,             "Content");
                            break;
                case 0x4A : //Reserved
                            Skip_String(DataLength,             "Content");
                            break;
                case 0x4B : //Reserved
                            Skip_String(DataLength,             "Content");
                            break;
                default   : Skip_XX(DataLength,                 "Unknown");
            }
            Element_End();
        }
    Element_End();

    Element_Begin("Track Description");
        Get_B2 (SectionLength,                                  "Section Length");
        if (Element_Offset+SectionLength>=Element_Size)
            SectionLength=(int16u)(Element_Size-Element_Offset);
        int64u Track_Data_End=Element_Offset+SectionLength;
        while (Element_Offset<Track_Data_End)
        {
            Element_Begin("Track");
            int16u TrackLength;
            int8u  MediaType, TrackID;
            Get_B1 (MediaType,                                  "Media type"); Param_Info(Gxf_MediaTypes(MediaType&0x7F));
            Get_B1 (TrackID,                                    "Track ID");
            Get_B2 (TrackLength,                                "Track Length");
            if (Element_Offset+TrackLength>=Track_Data_End)
                TrackLength=(int16u)(Track_Data_End-Element_Offset);
            int64u Track_End=Element_Offset+TrackLength;
            Element_Info(TrackID&0x3F);
            Element_Info(Gxf_MediaTypes(MediaType&0x7F));

            bool ShouldFill=false;
            FILLING_BEGIN();
                MediaType&=0x7F; //Remove the last bit
                TrackID&=0x3F; //Remove the 2 last bits
                Streams[TrackID].MediaType=MediaType;
                if (Streams[TrackID].StreamKind==Stream_Max)
                {
                    if (Gxf_MediaTypes_StreamKind(MediaType)!=Stream_Max)
                    {
                        Stream_Prepare(Gxf_MediaTypes_StreamKind(MediaType));
                        Streams[TrackID].StreamKind=StreamKind_Last;
                        Streams[TrackID].StreamPos=StreamPos_Last;
                        Fill(StreamKind_Last, StreamPos_Last, Fill_Parameter(StreamKind_Last, Generic_Format), Gxf_MediaTypes_Format(MediaType));
                        Fill(StreamKind_Last, StreamPos_Last, General_ID, TrackID);

                        if (StreamKind_Last==Stream_Audio)
                        {
                            //Resolution
                            switch (MediaType)
                            {
                                case  9 :
                                case 18 :   //24-bit
                                            Fill(Stream_Audio, StreamPos_Last, Audio_Resolution, 24);
                                            break;
                                case 10 :
                                case 17 :   //16-bit
                                            Fill(Stream_Audio, StreamPos_Last, Audio_Resolution, 16);
                                            break;
                                default : ;
                            }

                            //Channels
                            switch (MediaType)
                            {
                                case  9 :
                                case 10 :   //Mono
                                            Fill(Stream_Audio, StreamPos_Last, Audio_Channel_s_, 1);
                                            break;
                                default : ;
                            }

                            //Sampling rate
                            switch (MediaType)
                            {
                                case  9 :
                                case 10 :
                                case 17 :   //48000
                                            Fill(Stream_Audio, StreamPos_Last, Audio_SamplingRate, 48000);
                                            break;
                                default : ;
                            }

                            //Bit rate
                            switch (MediaType)
                            {
                                case  9 :
                                case 17 :   //Mono, 48 KHz, 24-bit (or padded up to 24-bit)
                                            Fill(Stream_Audio, StreamPos_Last, Audio_BitRate, 1*48000*24);
                                            break;
                                case 10 :   //Mono, 48 KHz, 16-bit
                                            Fill(Stream_Audio, StreamPos_Last, Audio_BitRate, 1*48000*16);
                                            break;
                                default : ;
                            }
                        }

                        //Parsers
                        switch (MediaType)
                        {
                            case 11 :
                            case 12 :
                            case 20 :
                            case 22 :
                            case 23 :   //MPEG Video
                                        Streams[TrackID].Parser=new File_Mpegv();
                                        ((File_Mpegv*)Streams[TrackID].Parser)->Cdp_Data=&Cdp_Data;
                                        Open_Buffer_Init(Streams[TrackID].Parser);
                                        Parsers_Count++;
                                        Streams[TrackID].Searching_Payload=true;
                                        break;
                            case 13 :
                            case 14 :
                            case 15 :
                            case 16 :   /*Streams[TrackID].Parser=new File_DvDif(); Parsers_Count++;*/ break;
                            case 17 :   /*Streams[TrackID].Parser=new File_Ac3(); Parsers_Count++;*/ break;
                            default : ;
                        }

                        ShouldFill=true;
                    }
                    else if (MediaType==21)
                    {
                        //Ancillary Metadata
                        Streams[TrackID].Parser=new File_Riff();
                        ((File_Riff*)Streams[TrackID].Parser)->Cdp_Data=&Cdp_Data;
                        Open_Buffer_Init(Streams[TrackID].Parser);
                        Parsers_Count++;
                        Streams[TrackID].Searching_Payload=true;
                        if (SizeToAnalyze<4*16*1024*1024)
                            SizeToAnalyze*=4; //4x more, to be sure to find captions
                    }
                }
            FILLING_END();

            while (Element_Offset<Track_End)
            {
                Element_Begin("Tag");
                int8u Tag, DataLength;
                Get_B1(Tag,                                     "Tag");
                Get_B1(DataLength,                              "Data Length");
                Element_Name(Gxf_Tag_Name(Tag));
                switch (Tag)
                {
                    case 0x4C : //Media file name
                                Get_Local(DataLength, Streams[TrackID].MediaFileName, "Content");
                                if (ShouldFill)
                                    Fill(StreamKind_Last, StreamPos_Last, "Title", Streams[TrackID].MediaFileName);
                                break;
                    case 0x4D : //Auxiliary Information
                                if (DataLength==8)
                                {
                                    if (MediaType==21)
                                    {
                                        //Ancillary
                                        Skip_B1(                "Reserved");
                                        Skip_B1(                "Reserved");
                                        Skip_B1(                "Ancillary data presentation format");
                                        Skip_B1(                "Number of ancillary data fields per ancillary data media packet");
                                        Skip_B2(                "Byte size of each ancillary data field");
                                        Skip_B2(                "Byte size of the ancillary data media packet in 256 byte units");
                                    }
                                    if (MediaType==7 || MediaType==8 || MediaType==24)
                                    {
                                        //TimeCode
                                        Skip_B1(                "Frame");
                                        Skip_B1(                "Second");
                                        Skip_B1(                "Minute");
                                        BS_Begin();
                                        Skip_SB(                "Invalid");
                                        Skip_SB(                "Color frame");
                                        Skip_SB(                "Drop frame");
                                        Skip_S1(5,              "Hour");
                                        BS_End();
                                        Skip_B1(                "User bits");
                                        Skip_B1(                "User bits");
                                        Skip_B1(                "User bits");
                                        Skip_B1(                "User bits");
                                    }
                                    else
                                        Skip_B8(                "Content");
                                }
                                else
                                    Skip_XX(DataLength,         "Unknown");
                                break;
                    case 0x4E : //Media file system version
                                if (DataLength==4)
                                    Skip_B4(                    "Content");
                                else
                                    Skip_XX(DataLength,         "Unknown");
                                break;
                    case 0x4F : //MPEG auxiliary information
                                Skip_String(DataLength,         "Content");
                                break;
                    case 0x50 : //Frame rate
                                if (DataLength==4)
                                {
                                    int32u Content;
                                    Get_B4 (Content,            "Content"); Param_Info(Gxf_FrameRate(Content)); Element_Info(Gxf_FrameRate(Content));
                                    if (ShouldFill && StreamKind_Last==Stream_Video)
                                        Fill(Stream_Video, StreamPos_Last, Video_FrameRate, Gxf_FrameRate(Content));
                                }
                                else
                                    Skip_XX(DataLength,         "Unknown");
                                break;
                    case 0x51 : //Lines per frame
                                if (DataLength==4)
                                {
                                    int32u Content;
                                    Get_B4 (Content,            "Content"); Param_Info(Gxf_LinesPerFrame_Height(Content)); Element_Info(Gxf_LinesPerFrame_Height(Content));
                                    if (ShouldFill && StreamKind_Last==Stream_Video)
                                    {
                                        if (Gxf_LinesPerFrame_Height(Content))
                                        {
                                            Fill(Stream_Video, StreamPos_Last, Video_Width, Gxf_LinesPerFrame_Width(Content));
                                            Fill(Stream_Video, StreamPos_Last, Video_Height, Gxf_LinesPerFrame_Height(Content));
                                        }
                                    }
                                }
                                else
                                    Skip_XX(DataLength,         "Unknown");
                                break;
                    case 0x52 : //Fields per frame
                                if (DataLength==4)
                                {
                                    int32u Content;
                                    Get_B4 (Content,            "Content"); Param_Info(Gxf_FieldsPerFrame(Content)); Element_Info(Gxf_FieldsPerFrame(Content));
                                    if (ShouldFill && StreamKind_Last==Stream_Video)
                                    {
                                        Fill(Stream_Video, StreamPos_Last, Video_ScanType, Gxf_FieldsPerFrame(Content));
                                        if (StreamPos_Last==0)
                                            Material_Fields_FieldsPerFrame=Content;
                                    }
                                }
                                else
                                    Skip_XX(DataLength,         "Unknown");
                                break;
                    default   : Skip_XX(DataLength,             "Unknown");
                }
                Element_End();
            }
            Element_End();
        }
    Element_End();
    if (Element_Offset<Element_Size)
        Skip_XX(Element_Size-Element_Offset,                    "Padding");
}

//---------------------------------------------------------------------------
void File_Gxf::media()
{
    Element_Name("media");

    //Parsing
    int8u TrackNumber;
    Element_Begin("Preamble");
        Skip_B1(                                                "Media type");
        Get_B1 (TrackNumber,                                    "Track number");
        Skip_B4(                                                "Media field number");
        Skip_B1(                                                "Field information");
        Skip_B1(                                                "Field information");
        Skip_B1(                                                "Field information");
        Skip_B1(                                                "Field information");
        Skip_B4(                                                "Time line field number");
        Skip_B1(                                                "Flags");
        Skip_B1(                                                "Reserved");
        TrackNumber&=0x3F;
    Element_End();
    Element_Info(TrackNumber);

    //Needed?
    if (!Streams[TrackNumber].Searching_Payload)
    {
        Skip_XX(Element_Size,                                   "data");
        Element_DoNotShow();
        return;
    }

    if (Streams[TrackNumber].Parser)
    {
        Open_Buffer_Continue(Streams[TrackNumber].Parser, Buffer+Buffer_Offset+(size_t)Element_Offset, (size_t)(Element_Size-Element_Offset));
        if (MediaInfoLib::Config.ParseSpeed_Get()<1 && Streams[TrackNumber].Parser->Status[IsFilled])
        {
            Streams[TrackNumber].Searching_Payload=false;

            if (Parsers_Count>0)
                Parsers_Count--;
            if (Parsers_Count==0)
            {
                Finish();
            }
        }
    }
}

//---------------------------------------------------------------------------
void File_Gxf::end_of_stream()
{
    Element_Name("end of stream");
}

//---------------------------------------------------------------------------
void File_Gxf::field_locator_table()
{
    Element_Name("field locator table");

    //Parsing
    int32u Entries;
    Skip_L4(                                                    "Number of fields per FLT entry");
    Get_L4 (Entries,                                            "Number of FLT entries");
    for (size_t Pos=0; Pos<Entries; Pos++)
    {
        Skip_L4(                                                "Offset to fields");
        if (Element_Offset==Element_Size)
            break;
    }
}

//---------------------------------------------------------------------------
void File_Gxf::UMF_file()
{
    Element_Name("UMF file");

    //Parsing
    int32u PayloadDataLength;
    Element_Begin("Preamble");
        Skip_B1(                                                "First/last packet flag");
        Get_B4 (PayloadDataLength,                              "Payload data length");
    Element_End();

    if (UMF_File==NULL)
    {
        UMF_File=new File_Umf();
        Open_Buffer_Init(UMF_File);
    }
    Open_Buffer_Continue(UMF_File, Buffer+Buffer_Offset+(size_t)Element_Offset, (size_t)(Element_Size-Element_Offset));
}

//***************************************************************************
// Helpers
//***************************************************************************

//---------------------------------------------------------------------------
void File_Gxf::Detect_EOF()
{
    if (File_Offset+Buffer_Size>=SizeToAnalyze)
    {
        Finish();
    }
}

} //NameSpace

#endif //MEDIAINFO_GXF_YES
