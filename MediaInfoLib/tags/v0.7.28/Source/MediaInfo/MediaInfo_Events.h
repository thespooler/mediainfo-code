/*Structures for MediaInfo events */

#ifndef MediaInfo_EventsH
#define MediaInfo_EventsH

/***************************************************************************/
/* Platforms (from libzen)                                                 */
/***************************************************************************/

/*-------------------------------------------------------------------------*/
/*Win32*/
#if defined(__NT__) || defined(_WIN32) || defined(WIN32)
    #ifndef WIN32
        #define WIN32
    #endif
    #ifndef _WIN32
        #define _WIN32
    #endif
    #ifndef __WIN32__
        #define __WIN32__ 1
    #endif
#endif

/*-------------------------------------------------------------------------*/
/*Win64*/
#if defined(_WIN64) || defined(WIN64)
    #ifndef WIN64
        #define WIN64
    #endif
    #ifndef _WIN64
        #define _WIN64
    #endif
    #ifndef __WIN64__
        #define __WIN64__ 1
    #endif
#endif

/*-------------------------------------------------------------------------*/
/*Windows*/
#if defined(WIN32) || defined(WIN64)
    #ifndef WINDOWS
        #define WINDOWS
    #endif
    #ifndef _WINDOWS
        #define _WINDOWS
    #endif
    #ifndef __WINDOWS__
        #define __WINDOWS__ 1
    #endif
#endif

/*-------------------------------------------------------------------------*/
/*Unix (Linux, HP, Sun, BeOS...)*/
#if defined(UNIX) || defined(_UNIX) || defined(__UNIX__) \
    || defined(__unix) || defined(__unix__) \
    || defined(____SVR4____) || defined(__LINUX__) || defined(__sgi) \
    || defined(__hpux) || defined(sun) || defined(__SUN__) || defined(_AIX) \
    || defined(__EMX__) || defined(__VMS) || defined(__BEOS__)
    #ifndef UNIX
        #define UNIX
    #endif
    #ifndef _UNIX
        #define _UNIX
    #endif
    #ifndef __UNIX__
        #define __UNIX__ 1
    #endif
#endif

/*-------------------------------------------------------------------------*/
/*MacOS Classic*/
#if defined(macintosh)
    #ifndef MACOS
        #define MACOS
    #endif
    #ifndef _MACOS
        #define _MACOS
    #endif
    #ifndef __MACOS__
        #define __MACOS__ 1
    #endif
#endif

/*-------------------------------------------------------------------------*/
/*MacOS X*/
#if defined(__APPLE__) && defined(__MACH__)
    #ifndef MACOSX
        #define MACOSX
    #endif
    #ifndef _MACOSX
        #define _MACOSX
    #endif
    #ifndef __MACOSX__
        #define __MACOSX__ 1
    #endif
#endif

/*Test of targets*/
#if defined(WINDOWS) && defined(UNIX) && defined(MACOS) && defined(MACOSX)
    #pragma message Multiple platforms???
#endif

#if !defined(WIN32) && !defined(UNIX) && !defined(MACOS) && !defined(MACOSX)
    #pragma message No known platforms, assume default
#endif

/*-------------------------------------------------------------------------*/
/*8-bit int                                                                */
#if UCHAR_MAX==0xff
    #undef  MAXTYPE_INT
    #define MAXTYPE_INT 8
    typedef signed   char       MediaInfo_int8s;
    typedef unsigned char       MediaInfo_int8u;
#else
    #pragma message This machine has no 8-bit integertype?
#endif

/*-------------------------------------------------------------------------*/
/*16-bit int                                                               */
#if UINT_MAX == 0xffff
    #undef  MAXTYPE_INT
    #define MAXTYPE_INT 16
    typedef signed   int        MediaInfo_int16s;
    typedef unsigned int        MediaInfo_int16u;
#elif USHRT_MAX == 0xffff
    #undef  MAXTYPE_INT
    #define MAXTYPE_INT 16
    typedef signed   short      MediaInfo_int16s;
    typedef unsigned short      MediaInfo_int16u;
#else
    #pragma message This machine has no 16-bit integertype?
#endif

/*-------------------------------------------------------------------------*/
/*32-bit int                                                               */
#if UINT_MAX == 0xfffffffful
    #undef  MAXTYPE_INT
    #define MAXTYPE_INT 32
    typedef signed   int        MediaInfo_int32s;
    typedef unsigned int        MediaInfo_int32u;
#elif ULONG_MAX == 0xfffffffful
    #undef  MAXTYPE_INT
    #define MAXTYPE_INT 32
    typedef signed   long       MediaInfo_int32s;
    typedef unsigned long       MediaInfo_int32u;
#elif USHRT_MAX == 0xfffffffful
    #undef  MAXTYPE_INT
    #define MAXTYPE_INT 32
    typedef signed   short      MediaInfo_int32s;
    typedef unsigned short      MediaInfo_int32u;
#else
    #pragma message This machine has no 32-bit integer type?
#endif

/*-------------------------------------------------------------------------*/
/*64-bit int                                                               */
#if defined(__MINGW32__) || defined(__CYGWIN32__) || defined(__UNIX__) || defined(__MACOSX__)
    #undef  MAXTYPE_INT
    #define MAXTYPE_INT 64
    typedef unsigned long long  MediaInfo_int64u;
#elif defined(__WIN32__) || defined(_WIN32)
    #undef  MAXTYPE_INT
    #define MAXTYPE_INT 64
    typedef unsigned __int64    MediaInfo_int64u;
#else
    #pragma message This machine has no 64-bit integer type?
#endif
/*-------------------------------------------------------------------------*/


/***************************************************************************/
/* The callback function
/***************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    typedef void (__stdcall MediaInfo_Event_CallBackFunction)(unsigned char* Data_Content, size_t Data_Size, void* UserHandler);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/***************************************************************************/
/* EventCode management
/***************************************************************************/

#define MediaInfo_EventCode_Create(ParserID, EventID, EventVersion) \
  (  ((MediaInfo_int32u)ParserID    )<<24 \
   | ((MediaInfo_int32u)EventID     )<< 8 \
   | ((MediaInfo_int32u)EventVersion)    )

/***************************************************************************/
/* General                                                                 */
/***************************************************************************/

#define MediaInfo_Parser_None           0x00 

/*-------------------------------------------------------------------------*/
/* Generic                                                                 */
struct MediaInfo_Event_Generic
{
    MediaInfo_int32u    EventCode;
};

/*-------------------------------------------------------------------------*/
/* Start                                                                   */
#define MediaInfo_Event_General_Start 0x7001
struct MediaInfo_Event_General_Start_0
{
    MediaInfo_int32u    EventCode;
    MediaInfo_int64u    Stream_Size;
};

/*-------------------------------------------------------------------------*/
/* End                                                                     */
#define MediaInfo_Event_General_End 0x7002
struct MediaInfo_Event_General_End_0
{
    MediaInfo_int32u    EventCode;
    MediaInfo_int64u    Stream_Bytes_Analyzed;
};

/*-------------------------------------------------------------------------*/
/* Parser_Selected                                                         */
#define MediaInfo_Event_General_Parser_Selected 0x7003
struct MediaInfo_Event_General_Parser_Selected_0
{
    MediaInfo_int32u    EventCode;
    char                Name[16];
};

/*-------------------------------------------------------------------------*/
/* Move request                                                            */
#define MediaInfo_Event_General_Move_Request 0x7004 
struct MediaInfo_Event_General_Move_Request_0
{
    MediaInfo_int32u    EventCode;
    MediaInfo_int64u    Stream_Offset;
};

/*-------------------------------------------------------------------------*/
/* Move done                                                               */
#define MediaInfo_Event_General_Move_Done 0x7005 
struct MediaInfo_Event_General_Move_Done_0
{
    MediaInfo_int32u    EventCode;
    MediaInfo_int64u    Stream_Offset;
};

#endif //MediaInfo_EventsH

