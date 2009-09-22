// Main - Main functions
// Copyright (C) 2009-2009 Jerome Martinez, Zen@MediaArea.net
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "Common/Core.h"
#include "ZenLib/ZtringListList.h"
#include "ZenLib/Ztring.h"
#include "ZenLib/File.h"
#include "Common/Common_About.h"
#include <sstream>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
using namespace ZenLib;
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
Core::Core()
{
    MI=new MediaInfoNameSpace::MediaInfoList;
    MI->Option(_T("ParseSpeed"), _T("1.000"));
    MI->Option(_T("File_DvDif_Analysis"), _T("1"));
    Errors_Stats_WithHeader=false;
    Errors_Stats_WithFooter=false;
    Errors_Stats_XML=false;
    Verbosity=0.5;
}

Core::~Core()
{
    delete MI;
}

//---------------------------------------------------------------------------
void Core::Data_Prepare()
{
    //Inform
    Text=MI->Inform((size_t)-1).c_str();
}

//***************************************************************************
// Menu
//***************************************************************************

//---------------------------------------------------------------------------
size_t Core::Menu_File_Open_File (const String& FileName)
{
    Menu_File_Open_Files_Begin();
    return Menu_File_Open_Files_Continue(FileName);
}

//---------------------------------------------------------------------------
void Core::Menu_File_Open_Files_Begin ()
{
    MI->Close();
}

//---------------------------------------------------------------------------
size_t Core::Menu_File_Open_Files_Continue (const String &FileName)
{
    return MI->Open(FileName);
}

//---------------------------------------------------------------------------
void Core::Menu_File_Open_Directory (const String &DirectoryName)
{
    MI->Open(DirectoryName);
}

//---------------------------------------------------------------------------
void Core::Menu_Verbosity_XX (const MediaInfoNameSpace::String &Value)
{
    Verbosity=Ztring(Value).To_float32();
    MI->Option(_T("Verbosity"), Value);
}

//---------------------------------------------------------------------------
void Core::Menu_Verbosity_03 ()
{
    Verbosity=(float)0.3;
    MI->Option(_T("Verbosity"), _T("0.3"));
}

//---------------------------------------------------------------------------
void Core::Menu_Verbosity_05 ()
{
    Verbosity=(float)0.5;
    MI->Option(_T("Verbosity"), _T("0.5"));
}

//---------------------------------------------------------------------------
void Core::Menu_Verbosity_10 ()
{
    Verbosity=(float)1.0;
    MI->Option(_T("Verbosity"), _T("1"));
}

//---------------------------------------------------------------------------
void Core::Menu_Option_Preferences_Option (const String& Param, const String& Value)
{
    MI->Option(Param, Value);
}

//***************************************************************************
// Helpers
//***************************************************************************

//---------------------------------------------------------------------------
String& Core::Summary ()
{
    Text.clear();
    
    size_t Count=MI->Count_Get();
    for (size_t Pos=0; Pos<Count; Pos++)
    {
        if (Errors_Stats_WithHeader)
        {
            Text+=Ztring().From_UTF8(NameVersion_Text())+_T("\n");
            Common_Header(Pos, Count);
        }

        if (Verbosity>=0.5)
            Text+=MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_End_05"));
        else if (Verbosity>=0.3)
            Text+=MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_End_03"));
        
        Text+=_T('\n');

        Common_Footer(Pos, Count);
    }

    Common();

    return Text;
}

//---------------------------------------------------------------------------
String& Core::ByFrame ()
{
    //From CLI
    if (Errors_Stats_XML)
        return XML();
    
    Text.clear();
    
    size_t Count=MI->Count_Get();
    for (size_t Pos=0; Pos<Count; Pos++)
    {
        if (Errors_Stats_WithHeader)
        {
            Text+=Ztring().From_UTF8(NameVersion_Text())+_T(", Verbosity is ")+Ztring::ToZtring(Verbosity*10, 0)+_T("\n");
            Common_Header(Pos, Count);
            Text+=MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_Begin"))+_T('\n');
        }
        
        if (Verbosity>=1.0)
            Text+=MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_10"));
        else if (Verbosity>=0.5)
            Text+=MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_05"));
        else if (Verbosity>=0.3)
            Text+=MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_03"));
        
        if (Errors_Stats_WithFooter)
        {
            Text+=_T('\n');
            if (Verbosity>=0.5)
                Text+=MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_End_05"));
            else if (Verbosity>=0.3)
                Text+=MI->Get(Pos, Stream_Video, 0, _T("Errors_Stats_End_03"));
        }

        Common_Footer(Pos, Count);
    }

    Common();
    
    return Text;
}

//---------------------------------------------------------------------------
MediaInfoNameSpace::String &Core::XML()
{
    Text.clear();

    //Header
    Text+=_T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    Text+=_T("<dvanalyzer>\n");
    Text+=_T("\t<configuration>\n");
    Text+=_T("\t\t<company>")+Ztring().From_UTF8(NameVersion_Text()).SubString(_T(""), _T(" DV Analyzer"))+_T("</company>\n");
    Text+=_T("\t\t<version>")+Ztring().From_UTF8(NameVersion_Text()).SubString(_T("DV Analyzer "), _T(""))+_T("</version>\n");
    Text+=_T("\t\t<verbosity>")+Ztring::ToZtring(Verbosity*10, 0)+_T("</verbosity>\n");
    Text+=_T("\t</configuration>\n");
    
    enum fields
    {
        frame,
        time,
        timecode,
        timecode_non_consecutive,
        recdate_rectime,
        recdate_rectime_non_consecutive,
        arb,
        flag_start,
        flag_end,
        error_1,
        error_2,
        error_3,
        error_4,
        error_5,
        error_6,
        error_7,
        error_8,
        error_9,
        error_0,
        error_1_more,
        error_2_more,
        error_3_more,
        error_4_more,
        error_5_more,
        error_6_more,
        error_7_more,
        error_8_more,
        error_9_more,
        error_0_more,
    };

    size_t Count=MI->Count_Get();
    for (size_t File_Pos=0; File_Pos<Count; File_Pos++)
    {
        //XML Header
        Text+=_T("\t<file>\n");
        Text+=_T("\t\t<filepath>")+MI->Get(File_Pos, Stream_General, 0, _T("CompleteName"))+_T("</filepath>\n");
        
        //By Frame - Retrieving
        ZtringListList List;
        List.Separator_Set(0, _T("&"));
        List.Separator_Set(1, _T("\t"));
        if (Verbosity>=1.0)
            List.Write(MI->Get(File_Pos, Stream_Video, 0, _T("Errors_Stats_10")));
        else if (Verbosity>=0.5)
            List.Write(MI->Get(File_Pos, Stream_Video, 0, _T("Errors_Stats_05")));
        else if (Verbosity>=0.3)
            List.Write(MI->Get(File_Pos, Stream_Video, 0, _T("Errors_Stats_03")));

        //By Frame - For each line
        if (!List.empty())
            Text+=_T("\t\t<frames>\n");
        for (size_t Pos=0; Pos<List.size(); Pos++)
        {
            Text+=_T("\t\t\t<frame");
            if (List(Pos, error_1                          )!=_T(" ")
             || List(Pos, error_2                          )!=_T(" ")
             || List(Pos, error_3                          )!=_T(" ")
             || List(Pos, error_4                          )!=_T(" ")
             || List(Pos, error_5                          )!=_T(" ")
             || List(Pos, error_6                          )!=_T(" ")
             || List(Pos, error_7                          )!=_T(" ")
             || List(Pos, error_8                          )!=_T(" ")
             || List(Pos, error_9                          )!=_T(" ")
             || List(Pos, error_0                          )!=_T(" "))
                Text+=_T(" type=\"error\"");
            else
            if (List(Pos, timecode_non_consecutive         )!=_T(" ")
             || List(Pos, recdate_rectime_non_consecutive  )!=_T(" ")
             || List(Pos, error_1                          )!=_T(" ")
             || List(Pos, error_2                          )!=_T(" ")
             || List(Pos, error_3                          )!=_T(" ")
             || List(Pos, error_4                          )!=_T(" ")
             || List(Pos, error_5                          )!=_T(" ")
             || List(Pos, error_6                          )!=_T(" ")
             || List(Pos, error_7                          )!=_T(" ")
             || List(Pos, error_8                          )!=_T(" ")
             || List(Pos, error_9                          )!=_T(" ")
             || List(Pos, error_0                          )!=_T(" "))
                Text+=_T(" type=\"info\"");
            else
            if (Pos==0)
                Text+=_T(" type=\"first\"");
            else
            if (Pos+1==List.size())
                Text+=_T(" type=\"last\"");
            Text+=_T(">\n");


            //General
            Text+=_T("\t\t\t\t<frame>")+List(Pos, frame).TrimLeft()+_T("</frame>\n");
            Text+=_T("\t\t\t\t<time>")+List(Pos, time)+_T("</time>\n");
            Text+=_T("\t\t\t\t<timecode>")+List(Pos, timecode)+_T("</timecode>\n");
            Text+=_T("\t\t\t\t<recdate_rectime>")+List(Pos, recdate_rectime).TrimRight()+_T("</recdate_rectime>\n");
            
            //Flags
            if (List(Pos, flag_start                        )!=_T(" ")
             || List(Pos, flag_end                          )!=_T(" "))
            {
                Text+=_T("\t\t\t\t<flags>\n");
                
                if (List(Pos, flag_start)!=_T(" "))
                    Text+=_T("\t\t\t\t\t<flag>REC_START</flag>\n");
                if (List(Pos, flag_end)!=_T(" "))
                    Text+=_T("\t\t\t\t\t<flag>REC_END</flag>\n");
                
                Text+=_T("\t\t\t\t</flags>\n");
            }

            //Events
            if (List(Pos, timecode_non_consecutive         )!=_T(" ")
             || List(Pos, recdate_rectime_non_consecutive  )!=_T(" ")
             || List(Pos, error_1                          )!=_T(" ")
             || List(Pos, error_2                          )!=_T(" ")
             || List(Pos, error_3                          )!=_T(" ")
             || List(Pos, error_4                          )!=_T(" ")
             || List(Pos, error_5                          )!=_T(" ")
             || List(Pos, error_6                          )!=_T(" ")
             || List(Pos, error_7                          )!=_T(" ")
             || List(Pos, error_8                          )!=_T(" ")
             || List(Pos, error_9                          )!=_T(" ")
             || List(Pos, error_0                          )!=_T(" "))
            {
                Text+=_T("\t\t\t\t<events>\n");
                
                //Info
                if (List(Pos, timecode_non_consecutive)!=_T(" "))
                    Text+=_T("\t\t\t\t\t<event type=\"info\" event_id=\"NTC\">non-consecutive timecode</event>\n");
                if (List(Pos, recdate_rectime_non_consecutive)!=_T(" "))
                    Text+=_T("\t\t\t\t\t<event type=\"info\" event_id=\"NRT\">non-consecutive recdate/rectime</event>\n");
                //if (List(Pos, arb_non_consecutive)!=_T(" "))
                //    Text+=_T("\t\t\t\t\t<event type)="info\" event_id=\"NAB\">non-consecutive arbitrary bit</event>\n");
                
                //Errors
                if (List(Pos, error_1)!=_T(" "))
                    Text+=_T("\t\t\t\t\t<event type=\"error\" event_id=\"")+Ztring::ToZtring(error_1-error_1+1)+_T("\" event_type=\"video error concealment\">")+List(Pos, error_1_more)+_T("</event>\n");
                if (List(Pos, error_2)!=_T(" "))
                    Text+=_T("\t\t\t\t\t<event type=\"error\" event_id=\"")+Ztring::ToZtring(error_2-error_1+1)+_T("\" event_type=\"audio error code\">")+List(Pos, error_2_more)+_T("</event>\n");
                if (List(Pos, error_3)!=_T(" "))
                    Text+=_T("\t\t\t\t\t<event type=\"error\" event_id=\"")+Ztring::ToZtring(error_3-error_1+1)+_T("\" event_type=\"timecode incoherency\">")+List(Pos, error_3_more)+_T("</event>\n");
                if (List(Pos, error_4)!=_T(" "))
                    Text+=_T("\t\t\t\t\t<event type=\"error\" event_id=\"")+Ztring::ToZtring(error_4-error_1+1)+_T("\" event_type=\"DIF incoherency\">")+List(Pos, error_4_more)+_T("</event>\n");
                if (List(Pos, error_5)!=_T(" "))
                    Text+=_T("\t\t\t\t\t<event type=\"error\" event_id=\"")+Ztring::ToZtring(error_5-error_1+1)+_T("\" event_type=\"Arbitrary bit incoherency\">")+List(Pos, error_5_more)+_T("</event>\n");
                if (List(Pos, error_6)!=_T(" "))
                    Text+=_T("\t\t\t\t\t<event type=\"error\" event_id=\"")+Ztring::ToZtring(error_6-error_1+1)+_T("\" event_type=\"Stts fluctuation\">")+List(Pos, error_6_more)+_T("</event>\n");
                
                Text+=_T("\t\t\t\t</events>\n");
            }
            //Text+=_T("\t\t\t\t<>")+List(Pos, )+_T("</>\n");
            Text+=_T("\t\t\t</frame>\n");
        }
        if (!List.empty())
        {
            Text+=_T("\t\t</frames>\n");

            //FrameCount
            if (!MI->Get(File_Pos, Stream_Video, 0, _T("FrameCount_Speed")).empty())
            {
                Text+=_T("\t\t<frames_count>")+MI->Get(File_Pos, Stream_Video, 0, _T("FrameCount_Speed"))+_T("</frames_count>\n");
                if (MI->Get(File_Pos, Stream_Video, 0, _T("FrameCount_Speed"))!=MI->Get(File_Pos, Stream_Video, 0, _T("FrameCount")))
                {
                    Text+=_T("\t\t<warnings>\n");
                    Text+=_T("\t\t\t<warning code=\"1\">Warning, frame count is maybe incoherant (reported by MediaInfo: ")+MI->Get(File_Pos, Stream_Video, 0, _T("FrameCount"))+_T(")</warning>\n");
                    Text+=_T("\t\t</warnings>\n");
                }
            }
        }

        //Summary - Retrieving
        List.clear();
        if (Verbosity>=0.5)
            List.Write(MI->Get(File_Pos, Stream_Video, 0, _T("Errors_Stats_End_05")));
        else if (Verbosity>=0.3)
            List.Write(MI->Get(File_Pos, Stream_Video, 0, _T("Errors_Stats_End_03")));

        //Summary - For each line
        bool events_summary_open=false;
        for (size_t Pos=0; Pos<List.size(); Pos++)
        {
            if (List(Pos, 0).empty())
            {
                if (events_summary_open)
                {
                    Text+=_T("\t\t</events_summary>\n");
                    events_summary_open=false;
                }
            }
            
            //error_1
            if (List(Pos, 0).find(_T("Frame count with video error concealment: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+=_T("\t\t<events_summary>\n");
                    events_summary_open=true;
                }
                Text+=_T("\t\t\t<event type=\"error\" event_id=\"1\" event_type=\"video error concealment\">\n");
                Text+=_T("\t\t\t\t<count>")+List(Pos+1, 0).SubString(_T(": "), _T(" errors")).TrimLeft()+_T("</count>\n");
                Text+=_T("\t\t\t\t<frames_count>")+List(Pos, 0).SubString(_T(": "), _T(" frames"))+_T("</frames_count>\n");
                Pos++;
                Text+=_T("\t\t\t</event>\n");
            }
            
            //error_2
            if (List(Pos, 0).find(_T("Frame count with CH1 audio error code: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+=_T("\t\t<events_summary>\n");
                    events_summary_open=true;
                }
                Text+=_T("\t\t\t<event type=\"error\" event_id=\"2\" event_type=\"audio error code\" ch=\"1\" >\n");
                Text+=_T("\t\t\t\t<count>")+List(Pos+1, 0).SubString(_T(": "), _T(" errors")).TrimLeft()+_T("</count>\n");
                Text+=_T("\t\t\t\t<frames_count>")+List(Pos, 0).SubString(_T(": "), _T(" frames"))+_T("</frames_count>\n");
                Text+=_T("\t\t\t\t<summary>")+List(Pos+1, 0).SubString(_T("("), _T(")"))+_T("</summary>\n");
                Pos++;
                Text+=_T("\t\t\t</event>\n");
            }
            if (List(Pos, 0).find(_T("Frame count with CH2 audio error code: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+=_T("\t\t<events_summary>\n");
                    events_summary_open=true;
                }
                Text+=_T("\t\t\t<event type=\"error\" event_id=\"2\" event_type=\"audio error code\" ch=\"2\" >\n");
                Text+=_T("\t\t\t\t<count>")+List(Pos+1, 0).SubString(_T(": "), _T(" errors")).TrimLeft()+_T("</count>\n");
                Text+=_T("\t\t\t\t<frames_count>")+List(Pos, 0).SubString(_T(": "), _T(" frames"))+_T("</frames_count>\n");
                Text+=_T("\t\t\t\t<summary>")+List(Pos+1, 0).SubString(_T("("), _T(")"))+_T("</summary>\n");
                Pos++;
                Text+=_T("\t\t\t</event>\n");
            }

            //error_3
            if (List(Pos, 0).find(_T("Frame count with timecode incoherency: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+=_T("\t\t<events_summary>\n");
                    events_summary_open=true;
                }
                Text+=_T("\t\t\t<event type=\"error\" event_id=\"3\" event_type=\"timecode incoherency\">\n");
                Text+=_T("\t\t\t\t<frames_count>")+List(Pos, 0).SubString(_T(": "), _T(" frames"))+_T("</frames_count>\n");
                Text+=_T("\t\t\t</event>\n");
            }

            //error_4
            if (List(Pos, 0).find(_T("Frame count with DIF incoherency: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+=_T("\t\t<events_summary>\n");
                    events_summary_open=true;
                }
                Text+=_T("\t\t\t<event type=\"error\" event_id=\"4\" event_type=\"DIF incoherency\">\n");
                Text+=_T("\t\t\t\t<frames_count>")+List(Pos, 0).SubString(_T(": "), _T(" frames"))+_T("</frames_count>\n");
                Text+=_T("\t\t\t</event>\n");
            }

            //error_5
            if (List(Pos, 0).find(_T("Frame count with arbitrary bit incoherency: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+=_T("\t\t<events_summary>\n");
                    events_summary_open=true;
                }
                Text+=_T("\t\t\t<event type=\"error\" event_id=\"5\" event_type=\"arbitrary bit incoherency\">\n");
                Text+=_T("\t\t\t\t<frames_count>")+List(Pos, 0).SubString(_T(": "), _T(" frames"))+_T("</frames_count>\n");
                Text+=_T("\t\t\t</event>\n");
            }

            //error_6
            if (List(Pos, 0).find(_T("Frame count with stts fluctuation: "))==0)
            {
                if (!events_summary_open)
                {
                    Text+=_T("\t\t<events_summary>\n");
                    events_summary_open=true;
                }
                Text+=_T("\t\t\t<event type=\"error\" event_id=\"6\" event_type=\"stts fluctuation\">\n");
                Text+=_T("\t\t\t\t<frames_count>")+List(Pos, 0).SubString(_T(": "), _T(" frames"))+_T("</frames_count>\n");
                Text+=_T("\t\t\t</event>\n");
            }

            //Date
            if (List(Pos, 0).find(_T("Abs. Time"))==0)
            {
                Text+=_T("\t\t<reverse_edl>\n");
                
                size_t PosLine=1;
                while (Pos+PosLine<List.size() && !List(Pos+PosLine, 0).empty())
                {
                    Text+=_T("\t\t\t<edit>\n");
                    Text+=_T("\t\t\t\t<frame_start>")+List(Pos+PosLine, 3).SubString(_T(""), _T(" -")).TrimLeft()+_T("</frame_start>\n");
                    Text+=_T("\t\t\t\t<frame_end>")+List(Pos+PosLine, 3).SubString(_T("- "), _T("")).TrimLeft()+_T("</frame_end>\n");
                    Text+=_T("\t\t\t\t<abstime_start>")+List(Pos+PosLine, 0)+_T("</abstime_start>\n");
                    //Text+=_T("\t\t\t\t<abstime_end>")+List(Pos+PosLine, 0)+_T("</abstime_end>\n");
                    Text+=_T("\t\t\t\t<timecode_start>")+List(Pos+PosLine, 1).SubString(_T(""), _T(" -"))+_T("</timecode_start>\n");
                    Text+=_T("\t\t\t\t<timecode_end>")+List(Pos+PosLine, 1).SubString(_T("- "), _T(""))+_T("</timecode_end>\n");
                    Text+=_T("\t\t\t\t<recdatetime_start>")+List(Pos+PosLine, 2).SubString(_T(""), _T(" -")).TrimRight()+_T("</recdatetime_start>\n");
                    Text+=_T("\t\t\t\t<recdatetime_end>")+List(Pos+PosLine, 2).SubString(_T("- "), _T("")).TrimRight()+_T("</recdatetime_end>\n");
                    Text+=_T("\t\t\t</edit>\n");

                    PosLine++;
                }

                Text+=_T("\t\t</reverse_edl>\n");
            }
        }

        //XML Footer
        Text+=_T("\t</file>\n");
    }
         
    //Footer
    Text+=_T("</dvanalyzer>\n");

    return Text;
}

//---------------------------------------------------------------------------
String& Core::MediaInfo ()
{
    Text=MI->Inform();

    //Adapting
    size_t Begin=Text.find(_T("Errors_Stats_Begin"));
    size_t End=Text.find(_T("\r\n\r\n"), Begin);
    if (Begin!=std::string::npos && End!=std::string::npos)
            Text.erase(Begin, End-Begin);

    return Text;
}

//---------------------------------------------------------------------------
void Core::Common_Header (size_t Pos, size_t)
{
    Text+=MI->Get(Pos, Stream_General, 0, _T("CompleteName"))+_T('\n');
    Text+=_T('\n');
}

//---------------------------------------------------------------------------
void Core::Common_Footer (size_t Pos, size_t Count)
{
    if (!MI->Get(Pos, Stream_Video, 0, _T("FrameCount")).empty() && MI->Get(Pos, Stream_Video, 0, _T("FrameCount"))!=MI->Get(Pos, Stream_Video, 0, _T("FrameCount_Speed")))
    {
        Text+=_T('\n');
        Text+=_T("Warning, frame count is maybe incoherant (reported by MediaInfo: ")+MI->Get(Pos, Stream_Video, 0, _T("FrameCount"))+_T(")\n");
    }
    if (Pos+1<Count)
    {
        Text+=_T('\n');
        Text+=_T("***************************************************************************\n");
        Text+=_T('\n');
    }
}

//---------------------------------------------------------------------------
void Core::Common ()
{
    for (size_t Pos=0; Pos<Text.size(); Pos++)
        if (Text[Pos]==_T('&'))
            Text[Pos]=_T('\n');
}
