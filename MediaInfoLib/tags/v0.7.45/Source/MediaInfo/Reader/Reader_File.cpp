// MediaInfo_Internal - All info about media files
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

//---------------------------------------------------------------------------
// For user: you can disable or enable it
//#define MEDIAINFO_DEBUG
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Compilation conditions
#include "MediaInfo/Setup.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Reader/Reader_File.h"
#include "MediaInfo/File__Analyze.h"
#include "ZenLib/FileName.h"
#ifdef WINDOWS
    #undef __TEXT
    #include "Windows.h"
#endif WINDOWS
using namespace ZenLib;
using namespace std;
//---------------------------------------------------------------------------
// Debug stuff
#ifdef MEDIAINFO_DEBUG
    int64u Reader_File_Offset=0;
    int64u Reader_File_BytesRead_Total=0;
    int64u Reader_File_BytesRead=0;
    int64u Reader_File_Count=1;
    #include <iostream>
#endif // MEDIAINFO_DEBUG
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

const size_t Buffer_NormalSize=/*188*7;//*/64*1024;
const size_t Buffer_NoJump=128*1024;

//---------------------------------------------------------------------------
size_t Reader_File::Format_Test(MediaInfo_Internal* MI, const String &File_Name)
{
    #if MEDIAINFO_EVENTS
        {
            struct MediaInfo_Event_General_Start_0 Event;
            Event.EventCode=MediaInfo_EventCode_Create(MediaInfo_Parser_None, MediaInfo_Event_General_Start, 0);
            Event.Stream_Size=File::Size_Get(File_Name);
            MI->Config.Event_Send((const int8u*)&Event, sizeof(MediaInfo_Event_General_Start_0));
        }
    #endif //MEDIAINFO_EVENTS

    //With Parser MultipleParsing
    /*
    MI->Open_Buffer_Init((int64u)-1, File_Name);
    if (Format_Test_PerParser(MI, File_Name))
         return 1;
    return 0; //There is a problem
    */

    //Get the Extension
    Ztring Extension=FileName::Extension_Get(File_Name);
    Extension.MakeLowerCase();

    //Search the theorical format from extension
    InfoMap &FormatList=MediaInfoLib::Config.Format_Get();
    InfoMap::iterator Format=FormatList.begin();
    while (Format!=FormatList.end())
    {
        const Ztring &Extensions=FormatList.Get(Format->first, InfoFormat_Extensions);
        if (Extensions.find(Extension)!=Error)
        {
            if(Extension.size()==Extensions.size())
                break; //Only one extenion in the list
            if(Extensions.find(Extension+_T(" "))!=Error
            || Extensions.find(_T(" ")+Extension)!=Error)
                break;
        }
        Format++;
    }
    if (Format!=FormatList.end())
    {
        const Ztring &Parser=Format->second(InfoFormat_Parser);
        if (MI->SelectFromExtension(Parser))
        {
            //Test the theorical format
            if (Format_Test_PerParser(MI, File_Name)>0)
                 return 1;
        }
    }

    size_t ToReturn=MI->ListFormats(File_Name);
    return ToReturn;
}

//---------------------------------------------------------------------------
size_t Reader_File::Format_Test_PerParser(MediaInfo_Internal* MI, const String &File_Name)
{
    //Opening the file
    F.Open(File_Name);
    if (!F.Opened_Get())
        return 0;

    //Info
    Status=0;
    FileSize_Current=F.Size_Get();
    IsGrowing=false;

    //Partial file handling
    Ztring Config_Partial_Begin=MI->Config.File_Partial_Begin_Get();
    if (!Config_Partial_Begin.empty() && Config_Partial_Begin[0]>=_T('0') && Config_Partial_Begin[0]<=_T('9'))
    {
        if (Config_Partial_Begin.find(_T('%'))==Config_Partial_Begin.size()-1)
            Partial_Begin=float64_int64s(FileSize_Current*Config_Partial_Begin.To_float64()/100);
        else
            Partial_Begin=Config_Partial_Begin.To_int64u();
        if (Partial_Begin)
            F.GoTo(Partial_Begin);
    }
    else
        Partial_Begin=0;
    Ztring Config_Partial_End=MI->Config.File_Partial_End_Get();
    if (!Config_Partial_End.empty() && Config_Partial_End[0]>=_T('0') && Config_Partial_End[0]<=_T('9'))
    {
        if (Config_Partial_End.find(_T('%'))==Config_Partial_End.size()-1)
            Partial_End=float64_int64s(FileSize_Current*Config_Partial_End.To_float64()/100);
        else
            Partial_End=Config_Partial_End.To_int64u();
    }
    else
        Partial_End=FileSize_Current;
    if (Partial_Begin>FileSize_Current)
        Partial_Begin=0; //Wrong value
    if (Partial_End>FileSize_Current)
        Partial_End=FileSize_Current; //Wrong value
    if (Partial_Begin>Partial_End)
    {
        Partial_Begin=0; //Wrong value
        Partial_End=FileSize_Current; //Wrong value
    }

    //Parser
    MI->Open_Buffer_Init(Partial_End-Partial_Begin, File_Name);

    //Buffer
    Buffer=NULL;
    Buffer_Size_Max=Buffer_NormalSize>1?(Buffer_NormalSize/2):1;
    Buffer_Size_ToRead=Buffer_NormalSize;
    MI->Option(_T("File_Buffer_Size_Hint_Pointer"), Ztring::ToZtring((size_t)(&Buffer_Size_ToRead)));

    //Test the format with buffer
    return Format_Test_PerParser_Continue(MI);
}

//---------------------------------------------------------------------------
size_t Reader_File::Format_Test_PerParser_Continue (MediaInfo_Internal* MI)
{
    bool StopAfterFilled=MI->Config.File_StopAfterFilled_Get();

    #if MEDIAINFO_DEMUX
    //PerPacket
    bool ShouldContinue=true;
    if (MI->Config.Demux_EventWasSent)
    {
        MI->Config.Demux_EventWasSent=false;

        //Parser
        Status=MI->Open_Buffer_Continue(NULL, 0);

        //Demux
        if (MI->Config.Demux_EventWasSent)
            return 2; //Must return immediately

        //Threading
        if (MI->IsTerminating())
            return 1; //Termination is requested

        if (Status[File__Analyze::IsFinished] || (StopAfterFilled && Status[File__Analyze::IsFilled]))
            ShouldContinue=false;
    }

    if (ShouldContinue)
    #endif //MEDIAINFO_DEMUX
    {
        //Test the format with buffer
        while (!(Status[File__Analyze::IsFinished] || (StopAfterFilled && Status[File__Analyze::IsFilled])))
        {
            //Seek (if needed)
            if (MI->Open_Buffer_Continue_GoTo_Get()!=(int64u)-1)
            {
                #ifdef MEDIAINFO_DEBUG
                    std::cout<<std::hex<<Reader_File_Offset<<" - "<<Reader_File_Offset+Reader_File_BytesRead<<" : "<<std::dec<<Reader_File_BytesRead<<" bytes"<<std::endl;
                    Reader_File_Offset=MI->Open_Buffer_Continue_GoTo_Get();
                    Reader_File_BytesRead=0;
                    Reader_File_Count++;
                #endif //MEDIAINFO_DEBUG

                if (MI->Open_Buffer_Continue_GoTo_Get()>=F.Size_Get())
                    break; //Seek requested, but on a file bigger in theory than what is in the real file, we can't do this
                if (!(MI->Open_Buffer_Continue_GoTo_Get()>F.Position_Get() && MI->Open_Buffer_Continue_GoTo_Get()<F.Position_Get()+Buffer_NoJump)) //No smal jumps
                {
                     if (!F.GoTo(Partial_Begin+MI->Open_Buffer_Continue_GoTo_Get()))
                        break; //File is not seekable

                    MI->Open_Buffer_Init((int64u)-1, F.Position_Get()-Partial_Begin);
                }
            }

            //Handling of hints
            if (Buffer_Size_ToRead==0)
                Buffer_Size_ToRead=Buffer_NormalSize;
            if (Buffer_Size_ToRead>Buffer_Size_Max)
            {
                delete[] Buffer;
                while (Buffer_Size_ToRead>Buffer_Size_Max)
                    Buffer_Size_Max*=2;
                Buffer=new int8u[Buffer_Size_Max];
            }

            size_t Buffer_Size=F.Read(Buffer, (F.Position_Get()+Buffer_Size_ToRead<Partial_End)?Buffer_Size_ToRead:((size_t)(Partial_End-F.Position_Get())));
            if (Buffer_Size==0)
                break; //Problem while reading

            //Testing growing files
            if (!IsGrowing && F.Position_Get()>=FileSize_Current)
            {
                if (MediaInfoLib::Config.ParseSpeed_Get()>=1.0) //Only if full parsing
                {
                    int64u FileSize_New=F.Size_Get();
                    if (FileSize_Current!=FileSize_New)
                        IsGrowing=true;
                }
            }
            if (IsGrowing && F.Position_Get()>=FileSize_Current)
            {
                for (size_t CountOfSeconds=0; CountOfSeconds<10; CountOfSeconds++)
                {
                    int64u FileSize_New=F.Size_Get();
                    if (FileSize_Current!=FileSize_New)
                    {
                        Partial_End=FileSize_Current=FileSize_New;
                        MI->Open_Buffer_Init(FileSize_Current, F.Position_Get()-Buffer_Size);
                        break;
                    }
                    #ifdef WINDOWS
                        Sleep(1000);
                    #endif //WINDOWS
                }
            }

            #ifdef MEDIAINFO_DEBUG
                Reader_File_BytesRead_Total+=Buffer_Size;
                Reader_File_BytesRead+=Buffer_Size;
            #endif //MEDIAINFO_DEBUG

            //Parser
            Status=MI->Open_Buffer_Continue(Buffer, Buffer_Size);

            #if MEDIAINFO_DEMUX
                if (MI->Config.Demux_EventWasSent)
                    return 2; //Must return immediately
            #endif //MEDIAINFO_DEMUX

            //Threading
            if (MI->IsTerminating())
                break; //Termination is requested
        }
        if (F.Size_Get()==0) //If Size==0, Status is never updated
            Status=MI->Open_Buffer_Continue(NULL, 0);
    }

    #ifdef MEDIAINFO_DEBUG
        std::cout<<std::hex<<Reader_File_Offset<<" - "<<Reader_File_Offset+Reader_File_BytesRead<<" : "<<std::dec<<Reader_File_BytesRead<<" bytes"<<std::endl;
        std::cout<<"Total: "<<std::dec<<Reader_File_BytesRead_Total<<" bytes in "<<Reader_File_Count<<" blocks"<<std::endl;
    #endif //MEDIAINFO_DEBUG

    if (MI==NULL || !MI->Config.File_KeepInfo_Get())
    {
        //File
        F.Close();

        //Buffer
        delete[] Buffer; Buffer=NULL;
    }

    //Is this file detected?
    if (!Status[File__Analyze::IsAccepted])
        return 0;

    MI->Open_Buffer_Finalize();

    #if MEDIAINFO_DEMUX
        if (MI->Config.Demux_EventWasSent)
            return 2; //Must return immediately
    #endif //MEDIAINFO_DEMUX

    return 1;
}

//---------------------------------------------------------------------------
#if MEDIAINFO_SEEK
size_t Reader_File::Format_Test_PerParser_Seek (MediaInfo_Internal* MI, size_t Method, int64u Value, int64u ID)
{
    size_t ToReturn=MI->Open_Buffer_Seek(Method, Value, ID);

    if (ToReturn==0 || ToReturn==1)
    {
        //Reset
        Status=0;
    }

    return ToReturn;
}
#endif //MEDIAINFO_SEEK

} //NameSpace


