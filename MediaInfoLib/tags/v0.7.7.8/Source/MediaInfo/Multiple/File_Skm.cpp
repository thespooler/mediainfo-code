// File_Flv - Info for Flash files
// Copyright (C) 2006-2008 Jerome Martinez, Zen@MediaArea.net
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
#if defined(MEDIAINFO_SKM_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Multiple/File_Skm.h"
#if defined(MEDIAINFO_MPEG4V_YES)
    #include "MediaInfo/Video/File_Mpeg4v.h"
#endif
#include "ZenLib/Utils.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Buffer
//***************************************************************************

//---------------------------------------------------------------------------
void File_Skm::FileHeader_Parse()
{
    //Parsing
    Element_Begin("SKM header");
    int64u Signature;
    Get_C5 (Signature,                                          "Signature");
    Element_End();

    FILLING_BEGIN();
        //Integrity
        if (Signature!=CC5("DMSKM"))
        {
            Finnished();
            return;
        }

        //Filling
        Stream_Prepare(Stream_General);
        Fill(Stream_General, 0, General_Format, "SKM");
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Skm::Header_Parse()
{
    //Parsing
    int32u BodyLength;
    int8u Type;
    Skip_B4(                                                    "PreviousTagSize");
    if (File_Offset+Buffer_Offset+4<File_Size)
    {
        Get_B1 (Type,                                           "Type"); //Param_Info(Type<19?Flv_Type[Type]:_T("Unknown"));
        Get_B3 (BodyLength,                                     "BodyLength");
        Skip_B3(                                                "Timestamp_Base"); //in ms
        Skip_B1(                                                "Timestamp_Extended"); //TimeStamp = Timestamp_Extended*0x01000000+Timestamp_Base
        Skip_B3(                                                "StreamID");
    }
    else
    {
        Type=0;
        BodyLength=0;
    }

    //Filling
    Header_Fill_Code(Type, Ztring().From_Number(Type, 16));
    Header_Fill_Size(Element_Offset+BodyLength);
}

//***************************************************************************
// Buffer
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Skm::Header_Begin()
{
    //Synchro
    if (!Synched && !Synchronize())
        return false;

    //All should be OK...
    return true;
}

//---------------------------------------------------------------------------
bool File_Skm::Header_Parse_Fill_Size()
{
    //Look for next Sync word
    if (Buffer_Offset_Temp==0) //Buffer_Offset_Temp is not 0 if Header_Parse_Fill_Size() has already parsed first frames
        Buffer_Offset_Temp=Buffer_Offset+4;
    while (Buffer_Offset_Temp+4<=Buffer_Size
        && CC3(Buffer+Buffer_Offset_Temp)!=0x000001)
        Buffer_Offset_Temp++;

    //Must wait more data?
    if (Buffer_Offset_Temp+4>Buffer_Size)
    {
        if (File_Offset+Buffer_Size==File_Size)
            Buffer_Offset_Temp=Buffer_Size; //We are sure that the next bytes are a start
        else
            return false;
    }

    //OK, we continue
    Header_Fill_Size(Buffer_Offset_Temp-Buffer_Offset);
    Buffer_Offset_Temp=0;
    return true;
}

//***************************************************************************
// Elements
//***************************************************************************

//---------------------------------------------------------------------------
void File_Skm::Data_Parse()
{
    #if defined(MEDIAINFO_MPEG4V_YES)
        Stream.Parser=new File_Mpeg4v();
        ((File_Mpeg4v*)Stream.Parser)->FrameIsAlwaysComplete=true;
        ((File_Mpeg4v*)Stream.Parser)->OnlyVOP();
        Open_Buffer_Init(Stream.Parser, File_Size, File_Offset+Buffer_Offset);
        Open_Buffer_Continue(Stream.Parser, Buffer+Buffer_Offset, (size_t)Element_Size);
        //if (Stream.Parser->Count_Get(Stream_Video)>0)
        {
            Open_Buffer_Finalize(Stream.Parser);
            Merge(*Stream.Parser);
            Finnished();
        }
    #endif
}

//***************************************************************************
// Helpers
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Skm::Synchronize()
{
    //Synchronizing
    while (Buffer_Offset+4<=Buffer_Size
        && CC3(Buffer+Buffer_Offset)!=0x000001)
        Buffer_Offset++;
    if (Buffer_Offset+4>Buffer_Size)
    {
        //Parsing last bytes
        if (Buffer_Offset+3==Buffer_Size)
        {
            if (CC3(Buffer+Buffer_Offset)!=0x000001)
            {
                Buffer_Offset++;
                if (CC2(Buffer+Buffer_Offset)!=0x0000)
                {
                    Buffer_Offset++;
                    if (CC1(Buffer+Buffer_Offset)!=0x00)
                        Buffer_Offset++;
                }
            }
        }

        return false;
    }

    //Synched is OK
    Synched=true;
    return true;
}

} //NameSpace

#endif //MEDIAINFO_SKM_YES
