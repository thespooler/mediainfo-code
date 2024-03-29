// MediaInfo_Config_MediaInfo - Configuration class
// Copyright (C) 2005-2011 MediaArea.net SARL, Info@MediaArea.net
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
#include "MediaInfo/MediaInfo_Config_MediaInfo.h"
#include "ZenLib/ZtringListListF.h"
#if MEDIAINFO_IBI
    #include "ZenLib/Base64/base64.h"
#endif //MEDIAINFO_IBI
#include <algorithm>
using namespace ZenLib;
using namespace std;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

const size_t Buffer_NormalSize=/*188*7;//*/64*1024;

//***************************************************************************
// Info
//***************************************************************************

MediaInfo_Config_MediaInfo::MediaInfo_Config_MediaInfo()
{
    FileIsSeekable=true;
    FileIsSub=false;
    FileIsReferenced=false;
    FileKeepInfo=false;
    FileStopAfterFilled=false;
    FileStopSubStreamAfterFilled=false;
    Audio_MergeMonoStreams=false;
    File_Demux_Interleave=false;
    File_ID_OnlyRoot=false;
    File_TimeToLive=0;
    File_Buffer_Size_Hint_Pointer=NULL;
    #if MEDIAINFO_NEXTPACKET
        NextPacket=false;
    #endif //MEDIAINFO_NEXTPACKET
    #if MEDIAINFO_FILTER
        File_Filter_HasChanged_=false;
    #endif //MEDIAINFO_FILTER
    #if MEDIAINFO_EVENTS
        Event_CallBackFunction=NULL;
        Event_UserHandler=NULL;
        SubFile_StreamID=(int64u)-1;
    #endif //MEDIAINFO_EVENTS
    #if MEDIAINFO_DEMUX
        Demux_ForceIds=false;
        Demux_PCM_20bitTo16bit=false;
        Demux_Unpacketize=false;
        Demux_Rate=0;
        Demux_InitData=0; //In Demux event
    #endif //MEDIAINFO_DEMUX
    #if MEDIAINFO_IBI
        Ibi_Create=false;
    #endif //MEDIAINFO_IBI

    //Specific
    File_MpegTs_ForceMenu=false;
    File_MpegTs_stream_type_Trust=true;
    File_MpegTs_Atsc_transport_stream_id_Trust=true;
    File_Bdmv_ParseTargetedFile=true;
    File_DvDif_DisableAudioIfIsInContainer=false;
    #if defined(MEDIAINFO_DVDIF_ANALYZE_YES)
        File_DvDif_Analysis=false;
    #endif //defined(MEDIAINFO_DVDIF_ANALYZE_YES)
    #if defined(MEDIAINFO_LIBMMS_YES)
        File_Mmsh_Describe_Only=false;
    #endif //defined(MEDIAINFO_LIBMMS_YES)
    File_Eia608_DisplayEmptyStream=false;
    File_Eia708_DisplayEmptyStream=false;
    State=0;

    //Internal to MediaInfo, not thread safe
    File_Names_Pos=0;
    File_Buffer=NULL;
    File_Buffer_Size_Max=0;
    File_Buffer_Size_ToRead=Buffer_NormalSize;
    File_Buffer_Size=0;
    File_Buffer_Repeat=false;
    #if MEDIAINFO_DEMUX
        Demux_EventWasSent=false;
        #if MEDIAINFO_SEEK
           Demux_IsSeeking=false;
        #endif //MEDIAINFO_SEEK
    #endif //MEDIAINFO_DEMUX
}

MediaInfo_Config_MediaInfo::~MediaInfo_Config_MediaInfo()
{
    delete[] File_Buffer; //File_Buffer=NULL;
}

//***************************************************************************
// Info
//***************************************************************************

Ztring MediaInfo_Config_MediaInfo::Option (const String &Option, const String &Value)
{
    #if MEDIAINFO_EVENTS
        SubFile_Config(Option)=Value;
    #endif //MEDIAINFO_EVENTS

    String Option_Lower(Option);
    size_t Egal_Pos=Option_Lower.find(_T('='));
    if (Egal_Pos==string::npos)
        Egal_Pos=Option_Lower.size();
    transform(Option_Lower.begin(), Option_Lower.begin()+Egal_Pos, Option_Lower.begin(), (int(*)(int))tolower); //(int(*)(int)) is a patch for unix

    if (Option_Lower==_T("file_isseekable"))
    {
        File_IsSeekable_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_isseekable_get"))
    {
        return File_IsSeekable_Get()?"1":"0";
    }
    if (Option_Lower==_T("file_issub"))
    {
        File_IsSub_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_issub_get"))
    {
        return File_IsSub_Get()?"1":"0";
    }
    if (Option_Lower==_T("file_isreferenced"))
    {
        File_IsReferenced_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_isreferenced_get"))
    {
        return File_IsReferenced_Get()?"1":"0";
    }
    if (Option_Lower==_T("file_keepinfo"))
    {
        File_KeepInfo_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_keepinfo_get"))
    {
        return File_KeepInfo_Get()?"1":"0";
    }
    if (Option_Lower==_T("file_stopafterfilled"))
    {
        File_StopAfterFilled_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_stopafterfilled_get"))
    {
        return File_StopAfterFilled_Get()?"1":"0";
    }
    if (Option_Lower==_T("file_stopsubstreamafterfilled"))
    {
        File_StopSubStreamAfterFilled_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_stopsubstreamafterfilled_get"))
    {
        return File_StopSubStreamAfterFilled_Get()?"1":"0";
    }
    if (Option_Lower==_T("file_audio_mergemonostreams"))
    {
        File_Audio_MergeMonoStreams_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_audio_mergemonostreams_get"))
    {
        return File_Audio_MergeMonoStreams_Get()?"1":"0";
    }
    else if (Option_Lower==_T("file_demux_interleave"))
    {
        File_Demux_Interleave_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_demux_interleave_get"))
    {
        return File_Demux_Interleave_Get()?"1":"0";
    }
    else if (Option_Lower==_T("file_id_onlyroot"))
    {
        File_ID_OnlyRoot_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_id_onlyroot_get"))
    {
        return File_ID_OnlyRoot_Get()?"1":"0";
    }
    else if (Option_Lower==_T("file_filename"))
    {
        File_FileName_Set(Value);
        return _T("");
    }
    else if (Option_Lower==_T("file_filename_get"))
    {
        return File_FileName_Get();
    }
    else if (Option_Lower==_T("file_filenameformat"))
    {
        File_FileNameFormat_Set(Value);
        return _T("");
    }
    else if (Option_Lower==_T("file_filenameformat_get"))
    {
        return File_FileNameFormat_Get();
    }
    else if (Option_Lower==_T("file_timetolive"))
    {
        File_TimeToLive_Set(Ztring(Value).To_float64());
        return _T("");
    }
    else if (Option_Lower==_T("file_timetolive_get"))
    {
        return Ztring::ToZtring(File_TimeToLive_Get(), 9);
    }
    else if (Option_Lower==_T("file_partial_begin"))
    {
        File_Partial_Begin_Set(Value);
        return _T("");
    }
    else if (Option_Lower==_T("file_partial_begin_get"))
    {
        return File_Partial_Begin_Get();
    }
    else if (Option_Lower==_T("file_partial_end"))
    {
        File_Partial_End_Set(Value);
        return _T("");
    }
    else if (Option_Lower==_T("file_partial_end_get"))
    {
        return File_Partial_End_Get();
    }
    else if (Option_Lower==_T("file_forceparser"))
    {
        File_ForceParser_Set(Value);
        return _T("");
    }
    else if (Option_Lower==_T("file_forceparser_get"))
    {
        return File_ForceParser_Get();
    }
    else if (Option_Lower==_T("file_buffer_size_hint_pointer"))
    {
        File_Buffer_Size_Hint_Pointer_Set((size_t*)Ztring(Value).To_int64u());
        return _T("");
    }
    else if (Option_Lower==_T("file_buffer_size_hint_pointer_get"))
    {
        return Ztring::ToZtring((size_t)File_Buffer_Size_Hint_Pointer_Get());
    }
    else if (Option_Lower==_T("file_filter"))
    {
        #if MEDIAINFO_FILTER
            File_Filter_Set(Ztring(Value).To_int64u());
            return _T("");
        #else //MEDIAINFO_FILTER
            return _T("Filter manager is disabled due to compilation options");
        #endif //MEDIAINFO_FILTER
    }
    else if (Option_Lower==_T("file_filter_get"))
    {
        #if MEDIAINFO_FILTER
            return Ztring();//.From_Number(File_Filter_Get());
        #else //MEDIAINFO_FILTER
            return _T("Filter manager is disabled due to compilation options");
        #endif //MEDIAINFO_FILTER
    }
    else if (Option_Lower==_T("file_duplicate"))
    {
        #if MEDIAINFO_DUPLICATE
            return File_Duplicate_Set(Value);
        #else //MEDIAINFO_DUPLICATE
            return _T("Duplicate manager is disabled due to compilation options");
        #endif //MEDIAINFO_DUPLICATE
    }
    else if (Option_Lower==_T("file_duplicate_get"))
    {
        #if MEDIAINFO_DUPLICATE
            //if (File_Duplicate_Get())
                return _T("1");
            //else
            //    return _T("");
        #else //MEDIAINFO_DUPLICATE
            return _T("Duplicate manager is disabled due to compilation options");
        #endif //MEDIAINFO_DUPLICATE
    }
    else if (Option_Lower==_T("file_demux_forceids"))
    {
        #if MEDIAINFO_DEMUX
            if (Value.empty())
                Demux_ForceIds_Set(false);
            else
                Demux_ForceIds_Set(true);
            return Ztring();
        #else //MEDIAINFO_DEMUX
            return _T("Demux manager is disabled due to compilation options");
        #endif //MEDIAINFO_DEMUX
    }
    else if (Option_Lower==_T("file_demux_pcm_20bitto16bit"))
    {
        #if MEDIAINFO_DEMUX
            if (Value.empty())
                Demux_PCM_20bitTo16bit_Set(false);
            else
                Demux_PCM_20bitTo16bit_Set(true);
            return Ztring();
        #else //MEDIAINFO_DEMUX
            return _T("Demux manager is disabled due to compilation options");
        #endif //MEDIAINFO_DEMUX
    }
    else if (Option_Lower==_T("file_demux_unpacketize"))
    {
        #if MEDIAINFO_DEMUX
            if (Value.empty())
                Demux_Unpacketize_Set(false);
            else
                Demux_Unpacketize_Set(true);
            return Ztring();
        #else //MEDIAINFO_DEMUX
            return _T("Demux manager is disabled due to compilation options");
        #endif //MEDIAINFO_DEMUX
    }
    else if (Option_Lower==_T("file_demux_rate"))
    {
        #if MEDIAINFO_DEMUX
            Demux_Rate_Set(Ztring(Value).To_float64());
            return Ztring();
        #else //MEDIAINFO_DEMUX
            return _T("Demux manager is disabled due to compilation options");
        #endif //MEDIAINFO_DEMUX
    }
    else if (Option_Lower==_T("file_demux_initdata"))
    {
        #if MEDIAINFO_DEMUX
            Ztring Value_Lower(Value); Value_Lower.MakeLowerCase();
                 if (Value_Lower==_T("event")) Demux_InitData_Set(0);
            else if (Value_Lower==_T("field")) Demux_InitData_Set(1);
            else return _T("Invalid value");
            return Ztring();
        #else //MEDIAINFO_DEMUX
            return _T("Demux manager is disabled due to compilation options");
        #endif //MEDIAINFO_DEMUX
    }
    else if (Option_Lower==_T("file_ibi"))
    {
        #if MEDIAINFO_IBI
            Ibi_Set(Value);
            return Ztring();
        #else //MEDIAINFO_IBI
            return _T("IBI support is disabled due to compilation options");
        #endif //MEDIAINFO_IBI
    }
    else if (Option_Lower==_T("file_ibi_create"))
    {
        #if MEDIAINFO_IBI
            if (Value.empty())
                Ibi_Create_Set(false);
            else
                Ibi_Create_Set(true);
            return Ztring();
        #else //MEDIAINFO_IBI
            return _T("IBI support is disabled due to compilation options");
        #endif //MEDIAINFO_IBI
    }
    else if (Option_Lower==_T("file_nextpacket"))
    {
        #if MEDIAINFO_NEXTPACKET
            if (Value.empty())
                NextPacket_Set(false);
            else
                NextPacket_Set(true);
            return Ztring();
        #else //MEDIAINFO_NEXTPACKET
            return _T("NextPacket manager is disabled due to compilation options");
        #endif //MEDIAINFO_NEXTPACKET
    }
    else if (Option_Lower==_T("file_subfile_streamid_set"))
    {
        #if MEDIAINFO_EVENTS
            SubFile_StreamID_Set(Ztring(Value).To_int64u());
            return Ztring();
        #else //MEDIAINFO_EVENTS
            return _T("Event manager is disabled due to compilation options");
        #endif //MEDIAINFO_EVENTS
    }
    else if (Option_Lower==_T("file_mpegts_forcemenu"))
    {
        File_MpegTs_ForceMenu_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_mpegts_forcemenu_get"))
    {
        return File_MpegTs_ForceMenu_Get()?"1":"0";
    }
    else if (Option_Lower==_T("file_mpegts_stream_type_trust"))
    {
        File_MpegTs_stream_type_Trust_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_mpegts_stream_type_trust_get"))
    {
        return File_MpegTs_stream_type_Trust_Get()?"1":"0";
    }
    else if (Option_Lower==_T("file_mpegts_atsc_transport_stream_id_trust"))
    {
        File_MpegTs_Atsc_transport_stream_id_Trust_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_mpegts_atsc_transport_stream_id_trust_get"))
    {
        return File_MpegTs_Atsc_transport_stream_id_Trust_Get()?"1":"0";
    }
    else if (Option_Lower==_T("file_bdmv_parsetargetedfile"))
    {
        File_Bdmv_ParseTargetedFile_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_bdmv_parsetargetedfile_get"))
    {
        return File_Bdmv_ParseTargetedFile_Get()?"1":"0";
    }
    else if (Option_Lower==_T("file_dvdif_disableaudioifisincontainer"))
    {
        File_DvDif_DisableAudioIfIsInContainer_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_dvdif_disableaudioifisincontainer_get"))
    {
        return File_DvDif_DisableAudioIfIsInContainer_Get()?"1":"0";
    }
    else if (Option_Lower==_T("file_dvdif_analysis"))
    {
        #if defined(MEDIAINFO_DVDIF_ANALYZE_YES)
            File_DvDif_Analysis_Set(!(Value==_T("0") || Value.empty()));
            return _T("");
        #else //defined(MEDIAINFO_DVDIF_ANALYZE_YES)
            return _T("DVDIF Analysis is disabled due to compilation options");
        #endif //defined(MEDIAINFO_DVDIF_ANALYZE_YES)
    }
    else if (Option_Lower==_T("file_dvdif_analysis_get"))
    {
        #if defined(MEDIAINFO_DVDIF_ANALYZE_YES)
            return File_DvDif_Analysis_Get()?"1":"0";
        #else //defined(MEDIAINFO_DVDIF_ANALYZE_YES)
            return _T("DVDIF Analysis is disabled due to compilation options");
        #endif //defined(MEDIAINFO_DVDIF_ANALYZE_YES)
    }
    else if (Option_Lower==_T("file_curl"))
    {
        #if defined(MEDIAINFO_LIBCURL_YES)
            File_Curl_Set(Value);
            return _T("");
        #else //defined(MEDIAINFO_LIBCURL_YES)
            return _T("Libcurl support is disabled due to compilation options");
        #endif //defined(MEDIAINFO_LIBCURL_YES)
    }
    else if (Option_Lower.find(_T("file_curl,"))==0 || Option_Lower.find(_T("file_curl;"))==0)
    {
        #if defined(MEDIAINFO_LIBCURL_YES)
            File_Curl_Set(Option.substr(10), Value);
            return _T("");
        #else //defined(MEDIAINFO_LIBCURL_YES)
            return _T("Libcurl support is disabled due to compilation options");
        #endif //defined(MEDIAINFO_LIBCURL_YES)
    }
    else if (Option_Lower==_T("file_curl_get"))
    {
        #if defined(MEDIAINFO_LIBCURL_YES)
            return File_Curl_Get(Value);
        #else //defined(MEDIAINFO_LIBCURL_YES)
            return _T("Libcurl support is disabled due to compilation options");
        #endif //defined(MEDIAINFO_LIBCURL_YES)
    }
    else if (Option_Lower==_T("file_mmsh_describe_only"))
    {
        #if defined(MEDIAINFO_LIBMMS_YES)
            File_Mmsh_Describe_Only_Set(!(Value==_T("0") || Value.empty()));
            return _T("");
        #else //defined(MEDIAINFO_LIBMMS_YES)
            return _T("Libmms support is disabled due to compilation options");
        #endif //defined(MEDIAINFO_LIBMMS_YES)
    }
    else if (Option_Lower==_T("file_mmsh_describe_only_get"))
    {
        #if defined(MEDIAINFO_LIBMMS_YES)
            return File_Mmsh_Describe_Only_Get()?"1":"0";
        #else //defined(MEDIAINFO_LIBMMS_YES)
            return _T("Libmms support is disabled due to compilation options");
        #endif //defined(MEDIAINFO_LIBMMS_YES)
    }
    else if (Option_Lower==_T("file_eia708_displayemptystream"))
    {
        File_Eia708_DisplayEmptyStream_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_eia708_displayemptystream_get"))
    {
        return File_Eia708_DisplayEmptyStream_Get()?"1":"0";
    }
    else if (Option_Lower==_T("file_eia608_displayemptystream"))
    {
        File_Eia608_DisplayEmptyStream_Set(!(Value==_T("0") || Value.empty()));
        return _T("");
    }
    else if (Option_Lower==_T("file_eia608_displayemptystream_get"))
    {
        return File_Eia608_DisplayEmptyStream_Get()?"1":"0";
    }
    else if (Option_Lower==_T("file_event_callbackfunction"))
    {
        #if MEDIAINFO_EVENTS
            return Event_CallBackFunction_Set(Value);
        #else //MEDIAINFO_EVENTS
            return _T("Event manager is disabled due to compilation options");
        #endif //MEDIAINFO_EVENTS
    }
    else
        return _T("Option not known");
}

//***************************************************************************
// File Is Seekable
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_IsSeekable_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    FileIsSeekable=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_IsSeekable_Get ()
{
    CriticalSectionLocker CSL(CS);
    return FileIsSeekable;
}

//***************************************************************************
// File Is Sub
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_IsSub_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    FileIsSub=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_IsSub_Get ()
{
    CriticalSectionLocker CSL(CS);
    return FileIsSub;
}

//***************************************************************************
// File Is Referenced
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_IsReferenced_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    FileIsReferenced=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_IsReferenced_Get ()
{
    CriticalSectionLocker CSL(CS);
    return FileIsReferenced;
}

//***************************************************************************
// File Keep Info
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_KeepInfo_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    FileKeepInfo=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_KeepInfo_Get ()
{
    CriticalSectionLocker CSL(CS);
    return FileKeepInfo;
}

//***************************************************************************
// File Keep Info
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_StopAfterFilled_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    FileStopAfterFilled=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_StopAfterFilled_Get ()
{
    CriticalSectionLocker CSL(CS);
    return FileStopAfterFilled;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_StopSubStreamAfterFilled_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    FileStopSubStreamAfterFilled=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_StopSubStreamAfterFilled_Get ()
{
    CriticalSectionLocker CSL(CS);
    return FileStopSubStreamAfterFilled;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_Audio_MergeMonoStreams_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    Audio_MergeMonoStreams=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_Audio_MergeMonoStreams_Get ()
{
    CriticalSectionLocker CSL(CS);
    return Audio_MergeMonoStreams;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_Demux_Interleave_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_Demux_Interleave=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_Demux_Interleave_Get ()
{
    CriticalSectionLocker CSL(CS);
    return File_Demux_Interleave;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_ID_OnlyRoot_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_ID_OnlyRoot=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_ID_OnlyRoot_Get ()
{
    CriticalSectionLocker CSL(CS);
    return File_ID_OnlyRoot;
}

//***************************************************************************
// File name from somewhere else
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_FileName_Set (const Ztring &NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_FileName=NewValue;
}

Ztring MediaInfo_Config_MediaInfo::File_FileName_Get ()
{
    CriticalSectionLocker CSL(CS);
    return File_FileName;
}

//***************************************************************************
// File name format
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_FileNameFormat_Set (const Ztring &NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_FileNameFormat=NewValue;
}

Ztring MediaInfo_Config_MediaInfo::File_FileNameFormat_Get ()
{
    CriticalSectionLocker CSL(CS);
    return File_FileNameFormat;
}

//***************************************************************************
// Time to live
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_TimeToLive_Set (float64 NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_TimeToLive=NewValue;
}

float64 MediaInfo_Config_MediaInfo::File_TimeToLive_Get ()
{
    CriticalSectionLocker CSL(CS);
    return File_TimeToLive;
}

//***************************************************************************
// Partial file (begin and end are cut)
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_Partial_Begin_Set (const Ztring &NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_Partial_Begin=NewValue;
}

Ztring MediaInfo_Config_MediaInfo::File_Partial_Begin_Get ()
{
    CriticalSectionLocker CSL(CS);
    return File_Partial_Begin;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_Partial_End_Set (const Ztring &NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_Partial_End=NewValue;
}

Ztring MediaInfo_Config_MediaInfo::File_Partial_End_Get ()
{
    CriticalSectionLocker CSL(CS);
    return File_Partial_End;
}

//***************************************************************************
// Force Parser
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_ForceParser_Set (const Ztring &NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_ForceParser=NewValue;
}

Ztring MediaInfo_Config_MediaInfo::File_ForceParser_Get ()
{
    CriticalSectionLocker CSL(CS);
    return File_ForceParser;
}

//***************************************************************************
// File_Buffer_Size_Hint_Pointer
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_Buffer_Size_Hint_Pointer_Set (size_t* NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_Buffer_Size_Hint_Pointer=NewValue;
}

size_t*  MediaInfo_Config_MediaInfo::File_Buffer_Size_Hint_Pointer_Get ()
{
    CriticalSectionLocker CSL(CS);
    return File_Buffer_Size_Hint_Pointer;
}

//***************************************************************************
// Filter
//***************************************************************************

//---------------------------------------------------------------------------
#if MEDIAINFO_FILTER
void MediaInfo_Config_MediaInfo::File_Filter_Set (int64u NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_Filter_16[(int16u)NewValue]=true;
    File_Filter_HasChanged_=true;
}

bool MediaInfo_Config_MediaInfo::File_Filter_Get (const int16u Value)
{
    CriticalSectionLocker CSL(CS);
    //Test
    bool Exists;
    if (File_Filter_16.empty())
        Exists=true;
    else
        Exists=(File_Filter_16.find(Value)!=File_Filter_16.end());
    return Exists;
}

bool MediaInfo_Config_MediaInfo::File_Filter_Get ()
{
    CriticalSectionLocker CSL(CS);
    bool Exist=!File_Filter_16.empty();
    return Exist;
}

bool MediaInfo_Config_MediaInfo::File_Filter_HasChanged ()
{
    CriticalSectionLocker CSL(CS);
    bool File_Filter_HasChanged_Temp=File_Filter_HasChanged_;
    File_Filter_HasChanged_=false;
    return File_Filter_HasChanged_Temp;
}
#endif //MEDIAINFO_FILTER

//***************************************************************************
// Duplicate
//***************************************************************************

#if MEDIAINFO_DUPLICATE
Ztring MediaInfo_Config_MediaInfo::File_Duplicate_Set (const Ztring &Value_In)
{
    //Preparing for File__Duplicate...
    CS.Enter();
    File__Duplicate_List.push_back(Value_In);

    //Handling Memory index
    Ztring ToReturn;
    ZtringList List=Value_In;
    for (size_t Pos=0; Pos<List.size(); Pos++)
    {
        //Form= "(-)Data", if "-" the value will be removed
        Ztring &Value=List[Pos];
        bool ToRemove=false;
        if (Value.find(_T('-'))==0)
        {
            Value.erase(Value.begin());
            ToRemove=true;
        }

        //Testing if this is information about a target
        if (List[Pos].find(_T("memory:"))==0 || List[Pos].find(_T("file:"))==0)
        {
            //Searching if already exist
            size_t Memory_Pos=File__Duplicate_Memory_Indexes.Find(List[Pos]);
            if (!ToRemove && Memory_Pos==Error)
            {
                //Does not exist yet (and adding is wanted)
                Memory_Pos=File__Duplicate_Memory_Indexes.Find(_T(""));
                if (Memory_Pos!=Error)
                    File__Duplicate_Memory_Indexes[Memory_Pos]=List[Pos]; //A free place is found
                else
                {
                    //Adding the place at the end
                    Memory_Pos=File__Duplicate_Memory_Indexes.size();
                    File__Duplicate_Memory_Indexes.push_back(List[Pos]);
                }
            }
            else if (ToRemove)
            {
                //Exists yet but Removal is wanted
                File__Duplicate_Memory_Indexes[Memory_Pos].clear();
                Memory_Pos=(size_t)-1;
            }

            ToReturn+=_T(";")+Ztring().From_Number(Memory_Pos);
        }
    }
    if (!ToReturn.empty())
        ToReturn.erase(ToReturn.begin()); //Remove first ";"

    CS.Leave();
    File_IsSeekable_Set(false); //If duplication, we can not seek anymore

    return ToReturn;
}

Ztring MediaInfo_Config_MediaInfo::File_Duplicate_Get (size_t AlreadyRead_Pos)
{
    CriticalSectionLocker CSL(CS);
    if (AlreadyRead_Pos>=File__Duplicate_List.size())
        return Ztring(); //Nothing or not more than the last time
    Ztring Temp=File__Duplicate_List[AlreadyRead_Pos];
    return Temp;
}

bool MediaInfo_Config_MediaInfo::File_Duplicate_Get_AlwaysNeeded (size_t AlreadyRead_Pos)
{
    CriticalSectionLocker CSL(CS);
    bool Temp=AlreadyRead_Pos>=File__Duplicate_List.size();
    return !Temp; //True if there is something to read
}

size_t MediaInfo_Config_MediaInfo::File__Duplicate_Memory_Indexes_Get (const Ztring &Value)
{
    CriticalSectionLocker CSL(CS);
    return File__Duplicate_Memory_Indexes.Find(Value);
}

void MediaInfo_Config_MediaInfo::File__Duplicate_Memory_Indexes_Erase (const Ztring &Value)
{
    CriticalSectionLocker CSL(CS);
    size_t Pos=File__Duplicate_Memory_Indexes.Find(Value);
    if (Pos!=Error)
        File__Duplicate_Memory_Indexes[Pos].clear();
}
#endif //MEDIAINFO_DUPLICATE

//***************************************************************************
// Demux
//***************************************************************************

#if MEDIAINFO_DEMUX
//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::Demux_ForceIds_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    Demux_ForceIds=NewValue;
}

bool MediaInfo_Config_MediaInfo::Demux_ForceIds_Get ()
{
    CriticalSectionLocker CSL(CS);
    return Demux_ForceIds;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::Demux_PCM_20bitTo16bit_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    Demux_PCM_20bitTo16bit=NewValue;
}

bool MediaInfo_Config_MediaInfo::Demux_PCM_20bitTo16bit_Get ()
{
    CriticalSectionLocker CSL(CS);
    return Demux_PCM_20bitTo16bit;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::Demux_Unpacketize_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    Demux_Unpacketize=NewValue;
}

bool MediaInfo_Config_MediaInfo::Demux_Unpacketize_Get ()
{
    CriticalSectionLocker CSL(CS);
    return Demux_Unpacketize;
}
#endif //MEDIAINFO_DEMUX

//---------------------------------------------------------------------------
#if MEDIAINFO_DEMUX
void MediaInfo_Config_MediaInfo::Demux_Rate_Set (float64 NewValue)
{
    CriticalSectionLocker CSL(CS);
    Demux_Rate=NewValue;
}

float64 MediaInfo_Config_MediaInfo::Demux_Rate_Get ()
{
    CriticalSectionLocker CSL(CS);
    return Demux_Rate;
}
#endif //MEDIAINFO_DEMUX

//---------------------------------------------------------------------------
#if MEDIAINFO_DEMUX
void MediaInfo_Config_MediaInfo::Demux_InitData_Set (int8u NewValue)
{
    CriticalSectionLocker CSL(CS);
    Demux_InitData=NewValue;
}

int8u MediaInfo_Config_MediaInfo::Demux_InitData_Get ()
{
    CriticalSectionLocker CSL(CS);
    return Demux_InitData;
}
#endif //MEDIAINFO_DEMUX

//***************************************************************************
// IBI support
//***************************************************************************

#if MEDIAINFO_IBI
//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::Ibi_Set (const Ztring &Value)
{
    string Data_Base64=Value.To_UTF8();

    CriticalSectionLocker CSL(CS);
    Ibi=Base64::decode(Data_Base64);
}

string MediaInfo_Config_MediaInfo::Ibi_Get ()
{
    CriticalSectionLocker CSL(CS);
    return Ibi;
}
//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::Ibi_Create_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    Ibi_Create=NewValue;
}

bool MediaInfo_Config_MediaInfo::Ibi_Create_Get ()
{
    CriticalSectionLocker CSL(CS);
    return Ibi_Create;
}
#endif //MEDIAINFO_IBI

//***************************************************************************
// NextPacket
//***************************************************************************

//---------------------------------------------------------------------------
#if MEDIAINFO_NEXTPACKET
void MediaInfo_Config_MediaInfo::NextPacket_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    NextPacket=NewValue;
}

bool MediaInfo_Config_MediaInfo::NextPacket_Get ()
{
    CriticalSectionLocker CSL(CS);
    return NextPacket;
}
#endif //MEDIAINFO_NEXTPACKET

//***************************************************************************
// SubFile
//***************************************************************************

#if MEDIAINFO_EVENTS
//---------------------------------------------------------------------------
ZtringListList MediaInfo_Config_MediaInfo::SubFile_Config_Get ()
{
    CriticalSectionLocker CSL(CS);

    return SubFile_Config;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::SubFile_StreamID_Set (int64u Value)
{
    CriticalSectionLocker CSL(CS);

    SubFile_StreamID=Value;
}

//---------------------------------------------------------------------------
int64u MediaInfo_Config_MediaInfo::SubFile_StreamID_Get ()
{
    CriticalSectionLocker CSL(CS);

    return SubFile_StreamID;
}
#endif //MEDIAINFO_EVENTS

//***************************************************************************
// Event
//***************************************************************************

//---------------------------------------------------------------------------
#if MEDIAINFO_EVENTS
bool MediaInfo_Config_MediaInfo::Event_CallBackFunction_IsSet ()
{
    CriticalSectionLocker CSL(CS);

    return Event_CallBackFunction?true:false;
}
#endif //MEDIAINFO_EVENTS

//---------------------------------------------------------------------------
#if MEDIAINFO_EVENTS
Ztring MediaInfo_Config_MediaInfo::Event_CallBackFunction_Set (const Ztring &Value)
{
    ZtringList List=Value;

    CriticalSectionLocker CSL(CS);

    if (List.empty())
    {
        Event_CallBackFunction=(MediaInfo_Event_CallBackFunction*)NULL;
        Event_UserHandler=NULL;
    }
    else
        for (size_t Pos=0; Pos<List.size(); Pos++)
        {
            if (List[Pos].find(_T("CallBack=memory://"))==0)
                Event_CallBackFunction=(MediaInfo_Event_CallBackFunction*)Ztring(List[Pos].substr(18, std::string::npos)).To_int64u();
            else if (List[Pos].find(_T("UserHandler=memory://"))==0)
                Event_UserHandler=(void*)Ztring(List[Pos].substr(21, std::string::npos)).To_int64u();
            else
                return("Problem during Event_CallBackFunction value parsing");
        }

    return Ztring();
}
#endif //MEDIAINFO_EVENTS

//---------------------------------------------------------------------------
#if MEDIAINFO_EVENTS
Ztring MediaInfo_Config_MediaInfo::Event_CallBackFunction_Get ()
{
    CriticalSectionLocker CSL(CS);

    return _T("CallBack=memory://")+Ztring::ToZtring((size_t)Event_CallBackFunction)+_T(";UserHandler=memory://")+Ztring::ToZtring((size_t)Event_UserHandler);
}
#endif //MEDIAINFO_EVENTS

//---------------------------------------------------------------------------
#if MEDIAINFO_EVENTS
void MediaInfo_Config_MediaInfo::Event_Send (const int8u* Data_Content, size_t Data_Size)
{
    CriticalSectionLocker CSL(CS);

    if (Event_CallBackFunction)
        Event_CallBackFunction ((unsigned char*)Data_Content, Data_Size, Event_UserHandler);
}
#endif //MEDIAINFO_EVENTS

//---------------------------------------------------------------------------
#if MEDIAINFO_EVENTS
void MediaInfo_Config_MediaInfo::Event_Send (const int8u* Data_Content, size_t Data_Size, const Ztring &File_Name)
{
    CriticalSectionLocker CSL(CS);

    if (Event_CallBackFunction)
        Event_CallBackFunction ((unsigned char*)Data_Content, Data_Size, Event_UserHandler);
    else
    {
        MediaInfo_Event_Generic* Event_Generic=(MediaInfo_Event_Generic*)Data_Content;
        if ((Event_Generic->EventCode&0x00FFFF03)==((MediaInfo_Event_Global_Demux<<8)|0x03)) //Demux version 3
        {
            if (!MediaInfoLib::Config.Demux_Get())
                return;

            if (File_Name.empty())
                return;

            MediaInfo_Event_Global_Demux_0* Event=(MediaInfo_Event_Global_Demux_0*)Data_Content;

            Ztring File_Name_Final(File_Name);
            if (Event->StreamIDs_Size==0)
                File_Name_Final+=_T(".demux");
            else for (size_t Pos=0; Pos<Event->StreamIDs_Size; Pos++)
            {
                if (Event->StreamIDs_Width[Pos]==17)
                {
                    Ztring ID;
                    ID.From_CC4((int32u)Event->StreamIDs[Pos]);
                    File_Name_Final+=_T('.')+ID;
                }
                else if (Event->StreamIDs_Width[Pos] && Event->StreamIDs_Width[Pos])
                {
                    Ztring ID;
                    ID.From_Number(Event->StreamIDs[Pos], 16);
                    while (ID.size()<Event->StreamIDs_Width[Pos])
                        ID.insert(0,  1, _T('0'));
                    if (ID.size()>Event->StreamIDs_Width[Pos])
                        ID.erase(0, ID.size()-Event->StreamIDs_Width[Pos]);
                    File_Name_Final+=_T('.')+ID;
                }
                else
                    File_Name_Final+=_T(".raw");
            }

            File F;
            F.Open(File_Name_Final, File::Access_Write_Append);
            F.Write(Event->Content, Event->Content_Size);
        }
    }
}
#endif //MEDIAINFO_EVENTS

//***************************************************************************
// Force Parser
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_MpegTs_ForceMenu_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_MpegTs_ForceMenu=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_MpegTs_ForceMenu_Get ()
{
    CriticalSectionLocker CSL(CS);
    bool Temp=File_MpegTs_ForceMenu;
    return Temp;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_MpegTs_stream_type_Trust_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_MpegTs_stream_type_Trust=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_MpegTs_stream_type_Trust_Get ()
{
    CS.Enter();
    bool Temp=File_MpegTs_stream_type_Trust;
    CS.Leave();
    return Temp;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_MpegTs_Atsc_transport_stream_id_Trust_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_MpegTs_Atsc_transport_stream_id_Trust=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_MpegTs_Atsc_transport_stream_id_Trust_Get ()
{
    CS.Enter();
    bool Temp=File_MpegTs_Atsc_transport_stream_id_Trust;
    CS.Leave();
    return Temp;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_Bdmv_ParseTargetedFile_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_Bdmv_ParseTargetedFile=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_Bdmv_ParseTargetedFile_Get ()
{
    CriticalSectionLocker CSL(CS);
    bool Temp=File_Bdmv_ParseTargetedFile;
    return Temp;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_DvDif_DisableAudioIfIsInContainer_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_DvDif_DisableAudioIfIsInContainer=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_DvDif_DisableAudioIfIsInContainer_Get ()
{
    CriticalSectionLocker CSL(CS);
    bool Temp=File_DvDif_DisableAudioIfIsInContainer;
    return Temp;
}

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_DVDIF_ANALYZE_YES)
void MediaInfo_Config_MediaInfo::File_DvDif_Analysis_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_DvDif_Analysis=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_DvDif_Analysis_Get ()
{
    CriticalSectionLocker CSL(CS);
    bool Temp=File_DvDif_Analysis;
    return Temp;
}
#endif //defined(MEDIAINFO_DVDIF_ANALYZE_YES)

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_LIBCURL_YES)
void MediaInfo_Config_MediaInfo::File_Curl_Set (const Ztring &NewValue)
{
    size_t Pos=NewValue.find(_T(','));
    if (Pos==string::npos)
        Pos=NewValue.find(_T(';'));
    if (Pos!=string::npos)
    {
        Ztring Field=NewValue.substr(0, Pos); Field.MakeLowerCase();
        Ztring Value=NewValue.substr(Pos+1, string::npos);
        CriticalSectionLocker CSL(CS);
        Curl[Field]=Value;
    }
}

void MediaInfo_Config_MediaInfo::File_Curl_Set (const Ztring &Field_, const Ztring &NewValue)
{
    Ztring Field=Field_; Field.MakeLowerCase();
    CriticalSectionLocker CSL(CS);
    Curl[Field]=NewValue;
}

Ztring MediaInfo_Config_MediaInfo::File_Curl_Get (const Ztring &Field_)
{
    Ztring Field=Field_; Field.MakeLowerCase();
    CriticalSectionLocker CSL(CS);
    std::map<Ztring, Ztring>::iterator Value=Curl.find(Field);
    if (Value==Curl.end())
        return Ztring();
    else
        return Curl[Field];
}
#endif //defined(MEDIAINFO_LIBCURL_YES)

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_LIBMMS_YES)
void MediaInfo_Config_MediaInfo::File_Mmsh_Describe_Only_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_Mmsh_Describe_Only=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_Mmsh_Describe_Only_Get ()
{
    CriticalSectionLocker CSL(CS);
    bool Temp=File_Mmsh_Describe_Only;
    return Temp;
}
#endif //defined(MEDIAINFO_LIBMMS_YES)

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_Eia608_DisplayEmptyStream_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_Eia608_DisplayEmptyStream=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_Eia608_DisplayEmptyStream_Get ()
{
    CriticalSectionLocker CSL(CS);
    bool Temp=File_Eia608_DisplayEmptyStream;
    return Temp;
}

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::File_Eia708_DisplayEmptyStream_Set (bool NewValue)
{
    CriticalSectionLocker CSL(CS);
    File_Eia708_DisplayEmptyStream=NewValue;
}

bool MediaInfo_Config_MediaInfo::File_Eia708_DisplayEmptyStream_Get ()
{
    CriticalSectionLocker CSL(CS);
    bool Temp=File_Eia708_DisplayEmptyStream;
    return Temp;
}

//***************************************************************************
// Analysis internal
//***************************************************************************

//---------------------------------------------------------------------------
void MediaInfo_Config_MediaInfo::State_Set (float NewValue)
{
    CriticalSectionLocker CSL(CS);
    State=NewValue;
}

float MediaInfo_Config_MediaInfo::State_Get ()
{
    CriticalSectionLocker CSL(CS);
    float Temp=State;
    return Temp;
}

} //NameSpace

