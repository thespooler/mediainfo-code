// File__Analyze_Inform - Base for other files
// Copyright (C) 2002-2011 MediaArea.net SARL, Info@MediaArea.net
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
//
// Init and Finalize part
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#include "MediaInfo/Setup.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "ZenLib/Utils.h"
#include "ZenLib/File.h"
#include "ZenLib/FileName.h"
#include "MediaInfo/File__Analyze.h"
#include "MediaInfo/MediaInfo_Config_MediaInfo.h"
using namespace ZenLib;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//---------------------------------------------------------------------------
extern MediaInfo_Config Config;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void File__Analyze::Streams_Finish_Global()
{
    if (IsSub)
        return;

    //Image as video
    if (Config->File_Names.size()==1 && Count_Get(Stream_Image) && !File_Name.empty() && !Config->File_IsReferenced_Get())
    {
        //Trying to detect continuous file names (video stream as an image) 
        FileName FileToTest(File_Name);
        Ztring FileToTest_Name=FileToTest.Name_Get();
        size_t FileNameToTest_Pos=FileToTest_Name.size();
        while (FileNameToTest_Pos && FileToTest_Name[FileNameToTest_Pos-1]>=_T('0') && FileToTest_Name[FileNameToTest_Pos-1]<=_T('9'))
            FileNameToTest_Pos--;
        if (FileNameToTest_Pos!=FileToTest_Name.size())
        {
            size_t Numbers_Size=FileToTest_Name.size()-FileNameToTest_Pos;
            int64u Pos=Ztring(FileToTest_Name.substr(FileNameToTest_Pos)).To_int64u();
            FileToTest_Name.resize(FileNameToTest_Pos);

            while (true)
            {
                Pos++;
                Ztring Pos_Ztring; Pos_Ztring.From_Number(Pos);
                Pos_Ztring.insert(0, Numbers_Size-Pos_Ztring.size(), _T('0'));
                Ztring Next=FileToTest.Path_Get()+PathSeparator+FileToTest_Name+Pos_Ztring+_T('.')+FileToTest.Extension_Get();
                if (!File::Exists(Next))
                    break;
                Config->File_Names.push_back(Next);
            }

            if (Config->File_Names.size()<24)
                Config->File_Names.resize(1); //Removing files, wrong detection
        }
    }
    if ((Config->File_Names.size()>1 || Config->File_IsReferenced_Get()) && Count_Get(Stream_Image))
    {
        int64u TotalSize=File_Size;
        for (size_t Pos=0; Pos<Config->File_Names.size(); Pos++)
        {
            int64u Size=File::Size_Get(Config->File_Names[Pos]);
            if (Size!=(int64u)-1)
                TotalSize+=Size;
        }

        Stream_Prepare(Stream_Video);
        for (size_t Pos=General_ID; Pos<Count_Get(Stream_Image, 0); Pos++)
            Fill(Stream_Video, 0, Get(Stream_Image, 0, Pos, Info_Name).To_UTF8().c_str(), Get(Stream_Image, 0, Pos), true);
        Stream_Erase(Stream_Image, 0);

        Fill(Stream_General, 0, General_FileSize, TotalSize, 10, true);
        Fill(Stream_Video, 0, Video_StreamSize, TotalSize, 10, true);
        Fill(Stream_Video, 0, Video_FrameCount, Config->File_Names.size(), 10, true);
    }
    if (Config->File_Names_Pos!=1)
        return;

    Streams_Finish_StreamOnly();
    Streams_Finish_StreamOnly();
    Streams_Finish_InterStreams();
    Streams_Finish_StreamOnly();
    Streams_Finish_InterStreams();
    Streams_Finish_StreamOnly();
    Streams_Finish_InterStreams();
    Streams_Finish_StreamOnly();
}

//---------------------------------------------------------------------------
void File__Analyze::Streams_Finish_StreamOnly()
{
    //Generic
    for (size_t StreamKind=Stream_General; StreamKind<Stream_Max; StreamKind++)
        for (size_t StreamPos=0; StreamPos<Count_Get((stream_t)StreamKind); StreamPos++)
            Streams_Finish_StreamOnly((stream_t)StreamKind, StreamPos);

    //For each kind of (*Stream)
    for (size_t Pos=0; Pos<Count_Get(Stream_General);  Pos++) Streams_Finish_StreamOnly_General(Pos);
    for (size_t Pos=0; Pos<Count_Get(Stream_Video);    Pos++) Streams_Finish_StreamOnly_Video(Pos);
    for (size_t Pos=0; Pos<Count_Get(Stream_Audio);    Pos++) Streams_Finish_StreamOnly_Audio(Pos);
    for (size_t Pos=0; Pos<Count_Get(Stream_Text);     Pos++) Streams_Finish_StreamOnly_Text(Pos);
    for (size_t Pos=0; Pos<Count_Get(Stream_Chapters); Pos++) Streams_Finish_StreamOnly_Chapters(Pos);
    for (size_t Pos=0; Pos<Count_Get(Stream_Image);    Pos++) Streams_Finish_StreamOnly_Image(Pos);
    for (size_t Pos=0; Pos<Count_Get(Stream_Menu);     Pos++) Streams_Finish_StreamOnly_Menu(Pos);
}

//---------------------------------------------------------------------------
void File__Analyze::Streams_Finish_StreamOnly(stream_t StreamKind, size_t Pos)
{
    //BitRate from Duration and StreamSize
    if (StreamKind!=Stream_General && StreamKind!=Stream_Chapters && StreamKind!=Stream_Menu && Retrieve(StreamKind, Pos, "BitRate").empty() && !Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_StreamSize)).empty() && !Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_Duration)).empty())
    {
        float64 Duration=0;
        if (StreamKind==Stream_Video && !Retrieve(Stream_Video, Pos, Video_FrameCount).empty() && !Retrieve(Stream_Video, Pos, Video_FrameRate).empty())
        {
            int64u FrameCount=Retrieve(Stream_Video, Pos, Video_FrameCount).To_int64u();
            float64 FrameRate=Retrieve(Stream_Video, Pos, Video_FrameRate).To_float64();
            if (FrameCount && FrameRate)
                Duration=FrameCount*1000/FrameRate; //More precise (example: 1 frame at 29.97 fps)
        }
        if (Duration==0)
            Duration=Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_Duration)).To_float64();
        int64u StreamSize=Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_StreamSize)).To_int64u();
        if (Duration>0 && StreamSize>0)
            Fill(StreamKind, Pos, "BitRate", StreamSize*8*1000/Duration, 0);
    }

    //Duration from Bitrate and StreamSize
    if (StreamKind!=Stream_Chapters && Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_Duration)).empty() && !Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_StreamSize)).empty() && !Retrieve(StreamKind, Pos, "BitRate").empty() && Count_Get(Stream_Video)+Count_Get(Stream_Audio)>1) //If only one stream, duration will be copied later, useful for exact bitrate calculation
    {
        int64u BitRate=Retrieve(StreamKind, Pos, "BitRate").To_int64u();
        int64u StreamSize=Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_StreamSize)).To_int64u();
        if (BitRate>0 && StreamSize>0)
            Fill(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_Duration), StreamSize*8*1000/BitRate);
    }

    //StreamSize from BitRate and Duration
    if (StreamKind!=Stream_Chapters && Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_StreamSize)).empty() && !Retrieve(StreamKind, Pos, "BitRate").empty() && !Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_Duration)).empty() && Retrieve(StreamKind, Pos, "BitRate").find(_T(" / "))==std::string::npos) //If not done the first time or by other routine
    {
        int64u BitRate=Retrieve(StreamKind, Pos, "BitRate").To_int64u();
        int64u Duration=Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_Duration)).To_int64u();
        if (BitRate>0 && Duration>0)
            Fill(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_StreamSize), BitRate*Duration/8/1000);
    }

    //Bit rate and maximum bit rate
    if (!Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_BitRate)).empty() && Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_BitRate))==Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_BitRate_Maximum)))
    {
        Clear(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_BitRate_Maximum));
        if (Retrieve(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_BitRate_Mode)).empty())
            Fill(StreamKind, Pos, Fill_Parameter(StreamKind, Generic_BitRate_Mode), "CBR");
    }
}

//---------------------------------------------------------------------------
void File__Analyze::Streams_Finish_StreamOnly_General(size_t UNUSED(StreamPos))
{
}

//---------------------------------------------------------------------------
void File__Analyze::Streams_Finish_StreamOnly_Video(size_t Pos)
{
    //Frame count
    if (Retrieve(Stream_Video, Pos, Video_FrameCount).empty() && Frame_Count_NotParsedIncluded!=(int64u)-1 && File_Offset+Buffer_Size==File_Size)
    {
        if (Count_Get(Stream_Video)==1 && Count_Get(Stream_Audio)==0)
            Fill(Stream_Video, 0, Video_FrameCount, Frame_Count_NotParsedIncluded);
    }

    //FrameCount from Duration and FrameRate
    if (Retrieve(Stream_Video, Pos, Video_FrameCount).empty())
    {
        int64s Duration=Retrieve(Stream_Video, Pos, Video_Duration).To_int64s();
        if (Duration==0)
            Duration=Retrieve(Stream_General, 0, General_Duration).To_int64s();
        float64 FrameRate=Retrieve(Stream_Video, Pos, Video_FrameRate).To_float64();
        if (Duration && FrameRate)
           Fill(Stream_Video, Pos, Video_FrameCount, Duration*FrameRate/1000, 0);
    }

    //Duration from FrameCount and FrameRate
    if (Retrieve(Stream_Video, Pos, Video_Duration).empty())
    {
        int64u FrameCount=Retrieve(Stream_Video, Pos, Video_FrameCount).To_int64u();
        float64 FrameRate=Retrieve(Stream_Video, Pos, "FrameRate").To_float64();
        if (FrameCount && FrameRate)
           Fill(Stream_Video, Pos, Video_Duration, FrameCount/FrameRate*1000, 0);
    }

    //Pixel Aspect Ratio forced to 1.000 if none
    if (Retrieve(Stream_Video, Pos, Video_PixelAspectRatio).empty())
        Fill(Stream_Video, Pos, Video_PixelAspectRatio, 1.000);

    //Standard
    if (Retrieve(Stream_Video, Pos, Video_Standard).empty() && (Retrieve(Stream_Video, Pos, Video_Width)==_T("720") || Retrieve(Stream_Video, Pos, Video_Width)==_T("704")))
    {
             if (Retrieve(Stream_Video, Pos, Video_Height)==_T("576"))
            Fill(Stream_Video, Pos, Video_Standard, "PAL");
        else if (Retrieve(Stream_Video, Pos, Video_Height)==_T("486") || Retrieve(Stream_Video, Pos, Video_Height)==_T("480"))
            Fill(Stream_Video, Pos, Video_Standard, "NTSC");
    }
    if (Retrieve(Stream_Video, Pos, Video_Standard).empty() && Retrieve(Stream_Video, Pos, Video_Width)==_T("352"))
    {
             if (Retrieve(Stream_Video, Pos, Video_Height)==_T("576") || Retrieve(Stream_Video, Pos, Video_Height)==_T("288"))
            Fill(Stream_Video, Pos, Video_Standard, "PAL");
        else if (Retrieve(Stream_Video, Pos, Video_Height)==_T("486") || Retrieve(Stream_Video, Pos, Video_Height)==_T("480") || Retrieve(Stream_Video, Pos, Video_Height)==_T("243") || Retrieve(Stream_Video, Pos, Video_Height)==_T("240"))
            Fill(Stream_Video, Pos, Video_Standard, "NTSC");
    }

    //Known bitrates
    if (Count_Get(Stream_Video)==1 && Count_Get(Stream_Audio)==0 && Retrieve(Stream_General, 0, General_Format)==_T("MXF"))
    {
        int32u BitRate=Retrieve(Stream_Video, 0, Video_BitRate).To_int32u();
        int32u BitRate_Sav=BitRate;

        if (BitRate>= 54942720 && BitRate<= 57185280) BitRate= 56064000; //AVC-INTRA50
        if (BitRate>=111390720 && BitRate<=115937280) BitRate=113664000; //AVC-INTRA100

        if (BitRate!=BitRate_Sav)
            Fill(Stream_Video, 0, Video_BitRate, BitRate, 0, true);
    }
}

//---------------------------------------------------------------------------
void File__Analyze::Streams_Finish_StreamOnly_Audio(size_t Pos)
{
    //Frame count
    if (Retrieve(Stream_Audio, Pos, Audio_FrameCount).empty() && Frame_Count_NotParsedIncluded!=(int64u)-1 && File_Offset+Buffer_Size==File_Size)
    {
        if (Count_Get(Stream_Video)==0 && Count_Get(Stream_Audio)==1)
            Fill(Stream_Audio, 0, Audio_FrameCount, Frame_Count_NotParsedIncluded);
    }

    //SamplingCount
    if (Retrieve(Stream_Audio, Pos, Audio_SamplingCount).empty())
    {
        int64s Duration=Retrieve(Stream_Audio, Pos, Audio_Duration).To_int64s();
        if (Duration==0)
            Duration=Retrieve(Stream_General, 0, General_Duration).To_int64s();
        float SamplingRate=Retrieve(Stream_Audio, Pos, Audio_SamplingRate).To_float32();
        if (Duration && SamplingRate)
           Fill(Stream_Audio, Pos, Audio_SamplingCount, ((float64)Duration)/1000*SamplingRate, 0);
    }

    //Duration
    if (Retrieve(Stream_Audio, Pos, Audio_Duration).empty() && Retrieve(Stream_Audio, Pos, Audio_SamplingRate).To_int64u()!=0)
    {
        int64u Duration=Retrieve(Stream_Audio, Pos, Audio_SamplingCount).To_int64u()*1000/Retrieve(Stream_Audio, Pos, Audio_SamplingRate).To_int64u();
        if (Duration)
           Fill(Stream_Audio, Pos, Audio_Duration, Duration);
    }

    //Stream size
    if (Retrieve(Stream_Audio, Pos, Audio_StreamSize).empty() && !Retrieve(Stream_Audio, Pos, Audio_BitRate).empty() && !Retrieve(Stream_Audio, Pos, Audio_Duration).empty() && Retrieve(Stream_Audio, Pos, Audio_BitRate_Mode)==_T("CBR"))
    {
        int64u Duration=Retrieve(Stream_Audio, Pos, Audio_Duration).To_int64u();
        int64u BitRate=Retrieve(Stream_Audio, Pos, Audio_BitRate).To_int64u();
        if (Duration && BitRate)
            Fill(Stream_Audio, Pos, Audio_StreamSize, Duration*BitRate/8/1000);
    }

    //CBR/VBR
    if (Retrieve(Stream_Audio, Pos, Audio_BitRate_Mode).empty() && !Retrieve(Stream_Audio, Pos, Audio_Codec).empty())
    {
        Ztring Z1=MediaInfoLib::Config.Codec_Get(Retrieve(Stream_Audio, Pos, Audio_Codec), InfoCodec_BitRate_Mode, Stream_Audio);
        if (!Z1.empty())
            Fill(Stream_Audio, Pos, Audio_BitRate_Mode, Z1);
    }
}

//---------------------------------------------------------------------------
void File__Analyze::Streams_Finish_StreamOnly_Text(size_t UNUSED(Pos))
{
}

//---------------------------------------------------------------------------
void File__Analyze::Streams_Finish_StreamOnly_Chapters(size_t UNUSED(StreamPos))
{
}

//---------------------------------------------------------------------------
void File__Analyze::Streams_Finish_StreamOnly_Image(size_t UNUSED(StreamPos))
{
}

//---------------------------------------------------------------------------
void File__Analyze::Streams_Finish_StreamOnly_Menu(size_t UNUSED(StreamPos))
{
}

//---------------------------------------------------------------------------
void File__Analyze::Streams_Finish_InterStreams()
{
    //Duration if General not filled
    if (Retrieve(Stream_General, 0, General_Duration).empty())
    {
        int64u Duration=0;
        //For all streams (Generic)
        for (size_t StreamKind=Stream_Video; StreamKind<Stream_Max; StreamKind++)
            for (size_t Pos=0; Pos<Count_Get((stream_t)StreamKind); Pos++)
            {
                if (!Retrieve((stream_t)StreamKind, Pos, Fill_Parameter((stream_t)StreamKind, Generic_Duration)).empty())
                {
                    int64u Duration_Stream=Retrieve((stream_t)StreamKind, Pos, Fill_Parameter((stream_t)StreamKind, Generic_Duration)).To_int64u();
                    if (Duration_Stream>Duration)
                        Duration=Duration_Stream;
                }
            }

        //Filling
        if (Duration>0)
            Fill(Stream_General, 0, General_Duration, Duration);
    }

    //(*Stream) size if all stream sizes are OK
    if (Retrieve(Stream_General, 0, General_StreamSize).empty())
    {
        int64u StreamSize_Total=0;
        bool IsOK=true;
        //For all streams (Generic)
        for (size_t StreamKind=Stream_Video; StreamKind<Stream_Max; StreamKind++)
        {
            if (StreamKind!=Stream_Chapters && StreamKind!=Stream_Menu) //They have no big size, we never calculate them
                for (size_t Pos=0; Pos<Count_Get((stream_t)StreamKind); Pos++)
                {
                    int64u StreamSize=Retrieve((stream_t)StreamKind, Pos, Fill_Parameter((stream_t)StreamKind, Generic_StreamSize)).To_int64u();
                    if (StreamSize>0)
                        StreamSize_Total+=StreamSize;
                    else if (IsOK)
                        IsOK=false; //StreamSize not available for 1 stream, we can't calculate
                }
        }

        //Filling
        if (IsOK && StreamSize_Total>0 && StreamSize_Total<File_Size)
            Fill(Stream_General, 0, General_StreamSize, File_Size-StreamSize_Total);
    }

    //OverallBitRate if we have one Audio stream with bitrate
    if (Retrieve(Stream_General, 0, General_Duration).empty() && Retrieve(Stream_General, 0, General_OverallBitRate).empty() && Count_Get(Stream_Video)==0 && Count_Get(Stream_Audio)==1 && Retrieve(Stream_Audio, 0, Audio_BitRate).To_int64u()!=0)
        Fill(Stream_General, 0, General_OverallBitRate, Retrieve(Stream_Audio, 0, Audio_BitRate));

    //OverallBitRate if Duration
    if (Retrieve(Stream_General, 0, General_OverallBitRate).empty() && Retrieve(Stream_General, 0, General_Duration).To_int64u()!=0 && !Retrieve(Stream_General, 0, General_FileSize).empty())
        Fill(Stream_General, 0, General_OverallBitRate, Retrieve(Stream_General, 0, General_FileSize).To_int64u()*8*1000/Retrieve(Stream_General, 0, General_Duration).To_int64u());

    //Duration if OverallBitRate
    if (Retrieve(Stream_General, 0, General_Duration).empty() && Retrieve(Stream_General, 0, General_OverallBitRate).To_int64u()!=0)
        Fill(Stream_General, 0, General_Duration, Retrieve(Stream_General, 0, General_FileSize).To_float64()*8*1000/Retrieve(Stream_General, 0, General_OverallBitRate).To_float64(), 0);

    //Video bitrate can be the nominal one if <4s (bitrate estimation is not enough precise
    if (Count_Get(Stream_Video)==1 && Retrieve(Stream_Video, 0, Video_BitRate).empty() && Retrieve(Stream_General, 0, General_Duration).To_int64u()<4000)
    {
        Fill(Stream_Video, 0, Video_BitRate, Retrieve(Stream_Video, 0, Video_BitRate_Nominal));
        Clear(Stream_Video, 0, Video_BitRate_Nominal);
    }

    //Video bitrate if we have all audio bitrates and overal bitrate
    if (Count_Get(Stream_Video)==1 && Retrieve(Stream_General, 0, General_OverallBitRate).size()>4 && Retrieve(Stream_Video, 0, Video_BitRate).empty() && Retrieve(Stream_General, 0, General_Duration).To_int64u()>=1000) //BitRate is > 10 000 and Duration>10s, to avoid strange behavior
    {
        double GeneralBitRate_Ratio=0.98;  //Default container overhead=2%
        int32u GeneralBitRate_Minus=5000;  //5000 bps because of a "classic" stream overhead
        double VideoBitRate_Ratio  =0.98;  //Default container overhead=2%
        int32u VideoBitRate_Minus  =2000;  //2000 bps because of a "classic" stream overhead
        double AudioBitRate_Ratio  =0.98;  //Default container overhead=2%
        int32u AudioBitRate_Minus  =2000;  //2000 bps because of a "classic" stream overhead
        double TextBitRate_Ratio   =0.98;  //Default container overhead=2%
        int32u TextBitRate_Minus   =2000;  //2000 bps because of a "classic" stream overhead
        //Specific value depends of Container
        if (Get(Stream_General, 0, _T("Format"))==_T("MPEG-TS"))
        {
            GeneralBitRate_Ratio=0.98;
            GeneralBitRate_Minus=0;
            VideoBitRate_Ratio  =0.97;
            VideoBitRate_Minus  =0;
            AudioBitRate_Ratio  =0.96;
            AudioBitRate_Minus  =0;
            TextBitRate_Ratio   =0.96;
            TextBitRate_Minus   =0;
        }
        if (Get(Stream_General, 0, _T("Format"))==_T("MPEG-PS"))
        {
            GeneralBitRate_Ratio=0.99;
            GeneralBitRate_Minus=0;
            VideoBitRate_Ratio  =0.99;
            VideoBitRate_Minus  =0;
            AudioBitRate_Ratio  =0.99;
            AudioBitRate_Minus  =0;
            TextBitRate_Ratio   =0.99;
            TextBitRate_Minus   =0;
        }
        if (MediaInfoLib::Config.Format_Get(Retrieve(Stream_General, 0, General_Format), InfoFormat_KindofFormat)==_T("MPEG-4"))
        {
            GeneralBitRate_Ratio=1;
            GeneralBitRate_Minus=0;
            VideoBitRate_Ratio  =1;
            VideoBitRate_Minus  =0;
            AudioBitRate_Ratio  =1;
            AudioBitRate_Minus  =0;
            TextBitRate_Ratio   =1;
            TextBitRate_Minus   =0;
        }
        if (Get(Stream_General, 0, _T("Format"))==_T("Matroska"))
        {
            GeneralBitRate_Ratio=0.99;
            GeneralBitRate_Minus=0;
            VideoBitRate_Ratio  =0.99;
            VideoBitRate_Minus  =0;
            AudioBitRate_Ratio  =0.99;
            AudioBitRate_Minus  =0;
            TextBitRate_Ratio   =0.99;
            TextBitRate_Minus   =0;
        }

        //Testing
        float64 VideoBitRate=Retrieve(Stream_General, 0, General_OverallBitRate).To_float64()*GeneralBitRate_Ratio-GeneralBitRate_Minus;
        bool VideobitRateIsValid=true;
        for (size_t Pos=0; Pos<Count_Get(Stream_Audio); Pos++)
        {
            float64 AudioBitRate=Retrieve(Stream_Audio, Pos, Audio_BitRate).To_float64();
            if (AudioBitRate>0 && AudioBitRate_Ratio)
                VideoBitRate-=AudioBitRate/AudioBitRate_Ratio+AudioBitRate_Minus;
            else
                VideobitRateIsValid=false;
        }
        for (size_t Pos=0; Pos<Count_Get(Stream_Text); Pos++)
        {
            float64 TextBitRate=Retrieve(Stream_Text, Pos, Text_BitRate).To_float64();
            if (TextBitRate_Ratio)
                VideoBitRate-=TextBitRate/TextBitRate_Ratio+TextBitRate_Minus;
            else
                VideoBitRate-=1000; //Estimation: Text stream are not often big
        }
        if (VideobitRateIsValid && VideoBitRate>=10000) //to avoid strange behavior
        {
            VideoBitRate=VideoBitRate*VideoBitRate_Ratio-VideoBitRate_Minus;
            Fill(Stream_Video, 0, Video_BitRate, VideoBitRate, 0); //Default container overhead=2%
            if (Retrieve(Stream_Video, 0, Video_StreamSize).empty() && !Retrieve(Stream_Video, 0, Video_Duration).empty())
            {
                int64u Duration=Retrieve(Stream_Video, 0, Video_Duration).To_int64u();
                if (Duration)
                    Fill(Stream_Video, 0, Video_StreamSize, VideoBitRate/8*Duration/1000, 0);
            }
        }
    }

    //General stream size if we have all streamsize
    if (File_Size!=(int64u)-1 && Retrieve(Stream_General, 0, General_StreamSize).empty())
    {
        //Testing
        int64s StreamSize=File_Size;
        bool StreamSizeIsValid=true;
        for (size_t StreamKind_Pos=Stream_General+1; StreamKind_Pos<Stream_Menu; StreamKind_Pos++)
            for (size_t Pos=0; Pos<Count_Get((stream_t)StreamKind_Pos); Pos++)
            {
                int64u StreamXX_StreamSize=Retrieve((stream_t)StreamKind_Pos, Pos, Fill_Parameter((stream_t)StreamKind_Pos, Generic_StreamSize)).To_int64u();
                if (StreamXX_StreamSize>0 || StreamKind_Pos==Stream_Text)
                    StreamSize-=StreamXX_StreamSize;
                else
                    StreamSizeIsValid=false;
            }
        if (StreamSizeIsValid && StreamSize>=0) //to avoid strange behavior
            Fill(Stream_General, 0, General_StreamSize, StreamSize);
    }

    //Tags
    Tags();
}

} //NameSpace

