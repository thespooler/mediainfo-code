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
//
// Configuration of MediaInfo (per MediaInfo block)
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef MediaInfo_Config_MediaInfoH
#define MediaInfo_Config_MediaInfoH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Setup.h"
#include "MediaInfo/MediaInfo_Internal_Const.h"
#if MEDIAINFO_EVENTS
    #include "MediaInfo/MediaInfo_Config.h"
    #include "MediaInfo/MediaInfo_Events.h"
    #include "ZenLib/File.h"
#endif //MEDIAINFO_EVENTS
#include "ZenLib/CriticalSection.h"
#include "ZenLib/ZtringListList.h"
#include "ZenLib/Translation.h"
#include "ZenLib/InfoMap.h"
#include <map>
#include <vector>
using namespace ZenLib;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class MediaInfo_Config_MediaInfo
//***************************************************************************

class MediaInfo_Config_MediaInfo
{
public :
    //Constructor/Destructor
    MediaInfo_Config_MediaInfo();
    ~MediaInfo_Config_MediaInfo();

    //General
    Ztring Option (const String &Option, const String &Value=Ztring());

    void          File_IsSeekable_Set (bool NewValue);
    bool          File_IsSeekable_Get ();

    void          File_IsSub_Set (bool NewValue);
    bool          File_IsSub_Get ();

    void          File_IsReferenced_Set (bool NewValue);
    bool          File_IsReferenced_Get ();

    void          File_KeepInfo_Set (bool NewValue);
    bool          File_KeepInfo_Get ();

    void          File_StopAfterFilled_Set (bool NewValue);
    bool          File_StopAfterFilled_Get ();

    void          File_StopSubStreamAfterFilled_Set (bool NewValue);
    bool          File_StopSubStreamAfterFilled_Get ();

    void          File_Audio_MergeMonoStreams_Set (bool NewValue);
    bool          File_Audio_MergeMonoStreams_Get ();

    void          File_Demux_Interleave_Set (bool NewValue);
    bool          File_Demux_Interleave_Get ();

    void          File_ID_OnlyRoot_Set (bool NewValue);
    bool          File_ID_OnlyRoot_Get ();

    void          File_FileName_Set (const Ztring &NewValue);
    Ztring        File_FileName_Get ();

    void          File_FileNameFormat_Set (const Ztring &NewValue);
    Ztring        File_FileNameFormat_Get ();

    void          File_TimeToLive_Set (float64 NewValue);
    float64       File_TimeToLive_Get ();

    void          File_Partial_Begin_Set (const Ztring &NewValue);
    Ztring        File_Partial_Begin_Get ();
    void          File_Partial_End_Set (const Ztring &NewValue);
    Ztring        File_Partial_End_Get ();

    void          File_ForceParser_Set (const Ztring &NewValue);
    Ztring        File_ForceParser_Get ();

    void          File_Buffer_Size_Hint_Pointer_Set (size_t* NewValue);
    size_t*       File_Buffer_Size_Hint_Pointer_Get ();

    #if MEDIAINFO_NEXTPACKET
    void          NextPacket_Set (bool NewValue);
    bool          NextPacket_Get ();
    #endif //MEDIAINFO_NEXTPACKET

    #if MEDIAINFO_FILTER
    void          File_Filter_Set     (int64u NewValue);
    bool          File_Filter_Get     (const int16u  Value);
    bool          File_Filter_Get     ();
    bool          File_Filter_HasChanged();
    #endif //MEDIAINFO_FILTER

    #if MEDIAINFO_DUPLICATE
    Ztring        File_Duplicate_Set  (const Ztring &Value);
    Ztring        File_Duplicate_Get  (size_t AlreadyRead_Pos); //Requester must say how many Get() it already read
    bool          File_Duplicate_Get_AlwaysNeeded (size_t AlreadyRead_Pos); //Requester must say how many Get() it already read
    #endif //MEDIAINFO_DEMUX

    #if MEDIAINFO_DUPLICATE
    size_t        File__Duplicate_Memory_Indexes_Get (const Ztring &ToFind);
    void          File__Duplicate_Memory_Indexes_Erase (const Ztring &ToFind);
    #endif //MEDIAINFO_DEMUX

    #if MEDIAINFO_EVENTS
    ZtringListList SubFile_Config_Get ();
    void          SubFile_StreamID_Set(int64u Value);
    int64u        SubFile_StreamID_Get();
    #endif //MEDIAINFO_EVENTS

    #if MEDIAINFO_EVENTS
    bool          ParseUndecodableFrames_Get ();
    void          ParseUndecodableFrames_Set (bool Value);
    #endif //MEDIAINFO_EVENTS

    #if MEDIAINFO_EVENTS
    bool          Event_CallBackFunction_IsSet ();
    Ztring        Event_CallBackFunction_Set (const Ztring &Value);
    Ztring        Event_CallBackFunction_Get ();
    void          Event_Send(const int8u* Data_Content, size_t Data_Size);
    void          Event_Send(const int8u* Data_Content, size_t Data_Size, const Ztring &File_Name);
    #endif //MEDIAINFO_EVENTS

    #if MEDIAINFO_DEMUX
    void          Demux_ForceIds_Set (bool NewValue);
    bool          Demux_ForceIds_Get ();
    void          Demux_PCM_20bitTo16bit_Set (bool NewValue);
    bool          Demux_PCM_20bitTo16bit_Get ();
    void          Demux_Unpacketize_Set (bool NewValue);
    bool          Demux_Unpacketize_Get ();
    void          Demux_Rate_Set (float64 NewValue);
    float64       Demux_Rate_Get ();
    void          Demux_FirstDts_Set (int64u NewValue);
    int64u        Demux_FirstDts_Get ();
    void          Demux_FirstFrameNumber_Set (int64u NewValue);
    int64u        Demux_FirstFrameNumber_Get ();
    void          Demux_InitData_Set (int8u NewValue);
    int8u         Demux_InitData_Get ();
    #endif //MEDIAINFO_DEMUX

    #if MEDIAINFO_IBI
    void          Ibi_Set (const Ztring &NewValue);
    std::string   Ibi_Get ();
    void          Ibi_Create_Set (bool NewValue);
    bool          Ibi_Create_Get ();
    #endif //MEDIAINFO_IBI

    //Specific
    void          File_MpegTs_ForceMenu_Set (bool NewValue);
    bool          File_MpegTs_ForceMenu_Get ();
    void          File_MpegTs_stream_type_Trust_Set (bool NewValue);
    bool          File_MpegTs_stream_type_Trust_Get ();
    void          File_MpegTs_Atsc_transport_stream_id_Trust_Set (bool NewValue);
    bool          File_MpegTs_Atsc_transport_stream_id_Trust_Get ();
    void          File_Bdmv_ParseTargetedFile_Set (bool NewValue);
    bool          File_Bdmv_ParseTargetedFile_Get ();
    void          File_DvDif_DisableAudioIfIsInContainer_Set (bool NewValue);
    bool          File_DvDif_DisableAudioIfIsInContainer_Get ();
    #if defined(MEDIAINFO_DVDIF_ANALYZE_YES)
    void          File_DvDif_Analysis_Set (bool NewValue);
    bool          File_DvDif_Analysis_Get ();
    #endif //defined(MEDIAINFO_DVDIF_ANALYZE_YES)
    #if defined(MEDIAINFO_LIBCURL_YES)
    void          File_Curl_Set (const Ztring &NewValue);
    void          File_Curl_Set (const Ztring &Field, const Ztring &NewValue);
    Ztring        File_Curl_Get (const Ztring &Field);
    #endif //defined(MEDIAINFO_LIBCURL_YES)
    #if defined(MEDIAINFO_LIBMMS_YES)
    void          File_Mmsh_Describe_Only_Set (bool NewValue);
    bool          File_Mmsh_Describe_Only_Get ();
    #endif //defined(MEDIAINFO_LIBMMS_YES)
    void          File_Eia608_DisplayEmptyStream_Set (bool NewValue);
    bool          File_Eia608_DisplayEmptyStream_Get ();
    void          File_Eia708_DisplayEmptyStream_Set (bool NewValue);
    bool          File_Eia708_DisplayEmptyStream_Get ();

    //Analysis internal
    void          State_Set (float State);
    float         State_Get ();

    //Internal to MediaInfo, not thread safe
    ZtringList    File_Names;
    size_t        File_Names_Pos;
    size_t        File_Buffer_Size_Max;
    size_t        File_Buffer_Size_ToRead;
    size_t        File_Buffer_Size;
    int8u*        File_Buffer;
    bool          File_Buffer_Repeat;
    bool          File_Buffer_Repeat_IsSupported;
    bool          File_IsGrowing;
    bool          File_IsNotGrowingAnymore;
    int64u        File_Size;
    #if MEDIAINFO_DEMUX
    bool          Demux_EventWasSent;
        #if MEDIAINFO_SEEK
        bool      Demux_IsSeeking;
        #endif //MEDIAINFO_SEEK
    #endif //MEDIAINFO_DEMUX

private :
    bool                    FileIsSeekable;
    bool                    FileIsSub;
    bool                    FileIsReferenced;
    bool                    FileKeepInfo;
    bool                    FileStopAfterFilled;
    bool                    FileStopSubStreamAfterFilled;
    bool                    Audio_MergeMonoStreams;
    bool                    File_Demux_Interleave;
    bool                    File_ID_OnlyRoot;
    Ztring                  File_FileName;
    Ztring                  File_FileNameFormat;
    float64                 File_TimeToLive;
    Ztring                  File_Partial_Begin;
    Ztring                  File_Partial_End;
    Ztring                  File_ForceParser;
    size_t*                 File_Buffer_Size_Hint_Pointer;

    //Extra
    #if MEDIAINFO_NEXTPACKET
    bool                    NextPacket;
    #endif //MEDIAINFO_NEXTPACKET

    #if MEDIAINFO_FILTER
    std::map<int16u, bool>  File_Filter_16;
    bool                    File_Filter_HasChanged_;
    #endif //MEDIAINFO_FILTER

    #if MEDIAINFO_DUPLICATE
    std::vector<Ztring>     File__Duplicate_List;
    ZtringList              File__Duplicate_Memory_Indexes;
    #endif //MEDIAINFO_DUPLICATE

    //Event
    #if MEDIAINFO_EVENTS
    MediaInfo_Event_CallBackFunction* Event_CallBackFunction; //void Event_Handler(unsigned char* Data_Content, size_t Data_Size, void* UserHandler)
    void*                   Event_UserHandler;
    ZtringListList          SubFile_Config;
    int64u                  SubFile_StreamID;
    bool                    ParseUndecodableFrames;
    #endif //MEDIAINFO_EVENTS

    #if MEDIAINFO_DEMUX
    bool                    Demux_ForceIds;
    bool                    Demux_PCM_20bitTo16bit;
    bool                    Demux_Unpacketize;
    float64                 Demux_Rate;
    int64u                  Demux_FirstDts;
    int64u                  Demux_FirstFrameNumber;
    int8u                   Demux_InitData;
    #endif //MEDIAINFO_DEMUX

    #if MEDIAINFO_IBI
    std::string             Ibi;
    bool                    Ibi_Create;
    #endif //MEDIAINFO_IBI

    //Specific
    bool                    File_MpegTs_ForceMenu;
    bool                    File_MpegTs_stream_type_Trust;
    bool                    File_MpegTs_Atsc_transport_stream_id_Trust;
    bool                    File_Bdmv_ParseTargetedFile;
    bool                    File_DvDif_DisableAudioIfIsInContainer;
    #if defined(MEDIAINFO_DVDIF_ANALYZE_YES)
    bool                    File_DvDif_Analysis;
    #endif //defined(MEDIAINFO_DVDIF_ANALYZE_YES)
    #if defined(MEDIAINFO_LIBMMS_YES)
    bool                    File_Mmsh_Describe_Only;
    #endif //defined(MEDIAINFO_LIBMMS_YES)
    bool                    File_Eia608_DisplayEmptyStream;
    bool                    File_Eia708_DisplayEmptyStream;

    //Analysis internal
    float                   State;

    //Generic
    #if defined(MEDIAINFO_LIBCURL_YES)
    std::map<Ztring, Ztring> Curl;
    #endif //defined(MEDIAINFO_LIBCURL_YES)

    ZenLib::CriticalSection CS;
};

} //NameSpace

#endif

