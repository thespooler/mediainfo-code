// MediaInfo - All info about media files
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
// For user: you can disable or enable it
//#define MEDIAINFO_DEBUG
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Compilation conditions
#include <MediaInfo/Setup.h>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/MediaInfo.h"
#include "MediaInfo/MediaInfo_Internal.h"
using namespace ZenLib;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//---------------------------------------------------------------------------
//To clarify the code
#ifdef MEDIAINFO_DEBUG
    #include <stdio.h>
    FILE* F;
    std::string Debug;

    #undef MEDIAINFO_DEBUG
    #define MEDIAINFO_DEBUG(_TOAPPEND) \
        F=fopen("MediaInfo_Debug.txt", "a+t"); \
        Debug.clear(); \
        _TOAPPEND; \
        Debug+="\r\n"; \
        fwrite(Debug.c_str(), Debug.size(), 1, F); \
        fclose(F);
#else // MEDIAINFO_DEBUG
    #define MEDIAINFO_DEBUG(_TOAPPEND)
#endif // MEDIAINFO_DEBUG

#ifndef MEDIAINFO_DEBUG
#define EXECUTE_VOID(_METHOD,_DEBUGB) \
        ((MediaInfo_Internal*)Internal)->_METHOD;
#else //MEDIAINFO_DEBUG
#define EXECUTE_VOID(_METHOD,_DEBUGB) \
        ((MediaInfo_Internal*)Internal)->_METHOD; \
        MEDIAINFO_DEBUG(_DEBUGB)
#endif //MEDIAINFO_DEBUG

#ifndef MEDIAINFO_DEBUG
#define EXECUTE_INT(_METHOD,_DEBUGB) \
        return ((MediaInfo_Internal*)Internal)->_METHOD;
#else //MEDIAINFO_DEBUG
#define EXECUTE_INT(_METHOD, _DEBUGB) \
        size_t ToReturn=((MediaInfo_Internal*)Internal)->_METHOD; \
        MEDIAINFO_DEBUG(_DEBUGB) \
        return ToReturn;
#endif //MEDIAINFO_DEBUG

#ifndef MEDIAINFO_DEBUG
#define EXECUTE_STRING(_METHOD,_DEBUGB) \
        return ((MediaInfo_Internal*)Internal)->_METHOD;
#else //MEDIAINFO_DEBUG
#define EXECUTE_STRING(_METHOD,_DEBUGB) \
        Ztring ToReturn=((MediaInfo_Internal*)Internal)->_METHOD; \
        MEDIAINFO_DEBUG(_DEBUGB) \
        return ToReturn;
#endif //MEDIAINFO_DEBUG

inline std::string ToString(int64u Integer)
{
    return Ztring::ToZtring(Integer).To_Local();
}

inline std::string ToString(size_t Integer)
{
    return Ztring::ToZtring(Integer).To_Local();
}

//***************************************************************************
// Constructor/destructor
//***************************************************************************

//---------------------------------------------------------------------------
MediaInfo::MediaInfo()
{
    Internal=new MediaInfo_Internal();
}

//---------------------------------------------------------------------------
MediaInfo::~MediaInfo()
{
    delete (MediaInfo_Internal*)Internal; //Internal=NULL;
}

//***************************************************************************
// Files
//***************************************************************************

//---------------------------------------------------------------------------
size_t MediaInfo::Open(const String &File_Name_)
{
    return ((MediaInfo_Internal*)Internal)->Open(File_Name_);
}

//---------------------------------------------------------------------------
size_t MediaInfo::Open (const int8u* Begin_, size_t Begin_Size_, const int8u*, size_t, int64u FileSize_)
{
    return ((MediaInfo_Internal*)Internal)->Open(Begin_, Begin_Size_);
}

//---------------------------------------------------------------------------
size_t MediaInfo::Open_Buffer_Init (int64u File_Size, int64u File_Offset)
{
    MEDIAINFO_DEBUG(Debug+="Open_Buffer_Init, File_Size=";Debug+=ToString(File_Size);Debug+=", File_Offset=";Debug+=ToString(File_Offset);)
    EXECUTE_INT(Open_Buffer_Init(File_Size, File_Offset), Debug+="Open_Buffer, will return ";Debug+=ToString(ToReturn);)
}

//---------------------------------------------------------------------------
size_t MediaInfo::Open_Buffer_Continue (const int8u* ToAdd, size_t ToAdd_Size)
{
    size_t ToReturn=((MediaInfo_Internal*)Internal)->Open_Buffer_Continue(ToAdd, ToAdd_Size);
    if (ToReturn==0)
    {
        MEDIAINFO_DEBUG(Debug+="Open_Buffer_Continue, will return ";Debug+=ToString(ToReturn);Debug+=", forcing a Get() :";)
        Get(Stream_General, 0, _T("Format"));        
    }
    return ToReturn;
}

//---------------------------------------------------------------------------
int64u MediaInfo::Open_Buffer_Continue_GoTo_Get ()
{
    return ((MediaInfo_Internal*)Internal)->Open_Buffer_Continue_GoTo_Get();
}

//---------------------------------------------------------------------------
size_t MediaInfo::Open_Buffer_Finalize ()
{
    MEDIAINFO_DEBUG(Debug+="Open_Buffer_Finalize";)
    EXECUTE_INT(Open_Buffer_Continue_GoTo_Get(), Debug+="Open_Buffer_Finalize, will return ";Debug+=ToString(ToReturn);)
}

//---------------------------------------------------------------------------
size_t MediaInfo::Save()
{
    return 0; //Not yet implemented
}

//---------------------------------------------------------------------------
void MediaInfo::Close()
{
    MEDIAINFO_DEBUG(Debug+="Close";)
    return ((MediaInfo_Internal*)Internal)->Close();
}

//***************************************************************************
// Get File info
//***************************************************************************

//---------------------------------------------------------------------------
String MediaInfo::Inform(size_t)
{
    MEDIAINFO_DEBUG(Debug+="Inform";)
    EXECUTE_STRING(Inform(), Debug+="Inform, will return ";Debug+=ToReturn.To_Local();)
}

//---------------------------------------------------------------------------
String MediaInfo::Get(stream_t StreamKind, size_t StreamPos, size_t Parameter, info_t KindOfInfo)
{
    MEDIAINFO_DEBUG(Debug+="Get, StreamKind=";Debug+=ToString((size_t)StreamKind);Debug+=", StreamKind=";Debug+=ToString(StreamPos);Debug+=", Parameter=";Debug+=ToString(Parameter);)
    EXECUTE_STRING(Get(StreamKind, StreamPos, Parameter, KindOfInfo), Debug+="Get, will return ";Debug+=ToReturn.To_Local();)
}

//---------------------------------------------------------------------------
String MediaInfo::Get(stream_t StreamKind, size_t StreamPos, const String &Parameter, info_t KindOfInfo, info_t KindOfSearch)
{
    MEDIAINFO_DEBUG(Debug+="Get, StreamKind=";Debug+=ToString((size_t)StreamKind);Debug+=", StreamKind=";Debug+=ToString(StreamPos);Debug+=", Parameter=";Debug+=Ztring(Parameter).To_Local();)
    //Legacy
    if (Parameter.find(_T("_String"))!=Error)
    {
        Ztring S1=Parameter;
        S1.FindAndReplace(_T("_String"), _T("/String"));
        return Get(StreamKind, StreamPos, S1, KindOfInfo, KindOfSearch);
    }
    if (Parameter==_T("Channels"))
        return Get(StreamKind, StreamPos, _T("Channel(s)"), KindOfInfo, KindOfSearch);
    if (Parameter==_T("Artist"))
        return Get(StreamKind, StreamPos, _T("Performer"), KindOfInfo, KindOfSearch);
    if (Parameter==_T("AspectRatio"))
        return Get(StreamKind, StreamPos, _T("DisplayAspectRatio"), KindOfInfo, KindOfSearch);
    if (Parameter==_T("AspectRatio/String"))
        return Get(StreamKind, StreamPos, _T("DisplayAspectRatio/String"), KindOfInfo, KindOfSearch);

    EXECUTE_STRING(Get(StreamKind, StreamPos, Parameter, KindOfInfo), Debug+="Get, will return ";Debug+=ToReturn.To_Local();)
}

//***************************************************************************
// Set File info
//***************************************************************************

//---------------------------------------------------------------------------
size_t MediaInfo::Set(const String &ToSet, stream_t StreamKind, size_t StreamNumber, size_t Parameter, const String &OldValue)
{
    return 0; //Not yet implemented
}

//---------------------------------------------------------------------------
size_t MediaInfo::Set(const String &ToSet, stream_t StreamKind, size_t StreamNumber, const String &Parameter, const String &OldValue)
{
    return 0; //Not yet implemented
}

//***************************************************************************
// Output buffer
//***************************************************************************

//---------------------------------------------------------------------------
size_t MediaInfo::Output_Buffer_Get (const String &Value)
{
    return ((MediaInfo_Internal*)Internal)->Output_Buffer_Get(Value);
}

//---------------------------------------------------------------------------
size_t MediaInfo::Output_Buffer_Get (size_t Pos)
{
    return ((MediaInfo_Internal*)Internal)->Output_Buffer_Get(Pos);
}

//***************************************************************************
// Information
//***************************************************************************

//---------------------------------------------------------------------------
String MediaInfo::Option (const String &Option, const String &Value)
{
    MEDIAINFO_DEBUG(Debug+="Option, Option=";Debug+=Ztring(Option).To_Local();Debug+=", Value=";Debug+=Ztring(Value).To_Local();)
    EXECUTE_STRING(Option(Option, Value), Debug+="Option, will return ";Debug+=ToReturn.To_Local();)
}

//---------------------------------------------------------------------------
String MediaInfo::Option_Static (const String &Option, const String &Value)
{
    MEDIAINFO_DEBUG(Debug+="Option_Static, Option=";Debug+=Ztring(Option).To_Local();Debug+=", Value=";Debug+=Ztring(Value).To_Local();)
    MediaInfoLib::Config.Init(); //Initialize Configuration

         if (Option==_T("Info_Capacities"))
    {
        return _T("Option desactivated for this version, will come back soon!");
        MediaInfo_Internal MI;
        return MI.Option(Option);
    }
    else if (Option==_T("Info_Version"))
    {
        Ztring ToReturn=MediaInfoLib::Config.Info_Version_Get();
        #if defined(MediaInfo_Internal_VIDEO_NO) || defined(MediaInfo_Internal_AUDIO_NO) || defined(MediaInfo_Internal_RIFF_NO) || defined(MediaInfo_Internal_OGG_NO) || defined(MediaInfo_Internal_MPEGPS_NO) || defined(MediaInfo_Internal_MPEGA_NO) || defined(MediaInfo_Internal_WM_NO) || defined(MediaInfo_Internal_QT_NO) || defined(MediaInfo_Internal_RM_NO) || defined(MediaInfo_Internal_DVDIF_NO) || defined(MediaInfo_Internal_DVDV_NO) || defined(MediaInfo_Internal_AAC_NO) || defined(MediaInfo_Internal_MK_NO) || defined(MediaInfo_Internal_APE_NO) || defined(MediaInfo_Internal_FLAC_NO) || defined(MediaInfo_Internal_SNDFILE_NO) || defined(MediaInfo_Internal_FLV_NO) || defined(MediaInfo_Internal_SWF_NO)
            ToReturn+=_T(" modified");
        #endif
        return ToReturn;
    }
    else
        return MediaInfoLib::Config.Option(Option, Value);
}

//---------------------------------------------------------------------------
size_t MediaInfo::Count_Get (stream_t StreamKind, size_t StreamPos)
{
    return ((MediaInfo_Internal*)Internal)->Count_Get(StreamKind, StreamPos);

}

//---------------------------------------------------------------------------
size_t MediaInfo::State_Get ()
{
    return 0; //Not yet implemented
}

} //NameSpace


