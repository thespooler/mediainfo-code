project(mediainfo)

set(MEDIAINFO_MAJOR_VERSION 0)
set(MEDIAINFO_MINOR_VERSION 7)
set(MEDIAINFO_PATCH_VERSION 9)
set(MEDIAINFO_VERSION ${MEDIAINFO_MAJOR_VERSION}.${MEDIAINFO_MINOR_VERSION}.${MEDIAINFO_PATCH_VERSION})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

include_directories(${ZLIB_INCLUDE_DIR})

add_definitions(-DUNICODE -DMEDIAINFO_MINIMIZESIZE)

set(mediainfo_SRCS
	MediaInfo/File__Analyze.cpp
	MediaInfo/File__Analyze_Buffer.cpp
	MediaInfo/File__Analyze_Buffer_MinimizeSize.cpp
	MediaInfo/File__Analyze_Finalize.cpp
	MediaInfo/File__Analyze_Streams.cpp
	MediaInfo/File__Base.cpp
	MediaInfo/File__MultipleParsing.cpp
	MediaInfo/File__Duplicate.cpp
	MediaInfo/File_Dummy.cpp
	MediaInfo/File_Other.cpp
	MediaInfo/File_Unknown.cpp
	MediaInfo/MediaInfo.cpp
	MediaInfo/MediaInfo_Config.cpp
	MediaInfo/MediaInfo_Config_Automatic.cpp
	MediaInfo/MediaInfo_Config_MediaInfo.cpp
	MediaInfo/MediaInfo_File.cpp
	MediaInfo/MediaInfo_Inform.cpp
	MediaInfo/MediaInfo_Internal.cpp
	MediaInfo/MediaInfoList.cpp
	MediaInfo/MediaInfoList_Internal.cpp
	MediaInfo/Archive/File_7z.cpp
	MediaInfo/Archive/File_Ace.cpp
	MediaInfo/Archive/File_Bzip2.cpp
	MediaInfo/Archive/File_Elf.cpp
	MediaInfo/Archive/File_Gzip.cpp
	MediaInfo/Archive/File_Mz.cpp
	MediaInfo/Archive/File_Rar.cpp
	MediaInfo/Archive/File_Tar.cpp
	MediaInfo/Archive/File_Zip.cpp
	MediaInfo/Audio/File_Aac.cpp
	MediaInfo/Audio/File_Ac3.cpp
	MediaInfo/Audio/File_Adif.cpp
	MediaInfo/Audio/File_Adpcm.cpp
	MediaInfo/Audio/File_Adts.cpp
	MediaInfo/Audio/File_Aes3.cpp
	MediaInfo/Audio/File_Als.cpp
	MediaInfo/Audio/File_Amr.cpp
	MediaInfo/Audio/File_Amv.cpp
	MediaInfo/Audio/File_Ape.cpp
	MediaInfo/Audio/File_Au.cpp
	MediaInfo/Audio/File_Dts.cpp
	MediaInfo/Audio/File_ExtendedModule.cpp
	MediaInfo/Audio/File_Flac.cpp
	MediaInfo/Audio/File_ImpulseTracker.cpp
	MediaInfo/Audio/File_La.cpp
	MediaInfo/Audio/File_Latm.cpp
	MediaInfo/Audio/File_Midi.cpp
	MediaInfo/Audio/File_Module.cpp
	MediaInfo/Audio/File_Mpc.cpp
	MediaInfo/Audio/File_MpcSv8.cpp
	MediaInfo/Audio/File_Mpeg4_AudioSpecificConfig.cpp
	MediaInfo/Audio/File_Mpega.cpp
	MediaInfo/Audio/File_Pcm.cpp
	MediaInfo/Audio/File_Ps2Audio.cpp
	MediaInfo/Audio/File_ScreamTracker3.cpp
	MediaInfo/Audio/File_Speex.cpp
	MediaInfo/Audio/File_Tta.cpp
	MediaInfo/Audio/File_TwinVQ.cpp
	MediaInfo/Audio/File_Vorbis.cpp
	MediaInfo/Audio/File_Wvpk.cpp
	MediaInfo/Duplicate/File__Duplicate__Base.cpp
	MediaInfo/Duplicate/File__Duplicate__Writer.cpp
	MediaInfo/Duplicate/File__Duplicate_MpegTs.cpp
	MediaInfo/Image/File_Bmp.cpp
	MediaInfo/Image/File_Gif.cpp
	MediaInfo/Image/File_Ico.cpp
	MediaInfo/Image/File_Jpeg.cpp
	MediaInfo/Image/File_Png.cpp
	MediaInfo/Image/File_Rle.cpp
	MediaInfo/Image/File_Tiff.cpp
	MediaInfo/Multiple/File_Cdxa.cpp
	MediaInfo/Multiple/File_Dpg.cpp
	MediaInfo/Multiple/File_DvDif.cpp
	MediaInfo/Multiple/File_Dvdv.cpp
	MediaInfo/Multiple/File_Flv.cpp
	MediaInfo/Multiple/File_Mk.cpp
	MediaInfo/Multiple/File_Mpeg4.cpp
	MediaInfo/Multiple/File_Mpeg4_Descriptors.cpp
	MediaInfo/Multiple/File_Mpeg4_Elements.cpp
	MediaInfo/Multiple/File_Mpeg4_TimeCode.cpp
	MediaInfo/Multiple/File_Mpeg_Descriptors.cpp
	MediaInfo/Multiple/File_Mpeg_Psi.cpp
	MediaInfo/Multiple/File_MpegPs.cpp
	MediaInfo/Multiple/File_MpegTs.cpp
	MediaInfo/Multiple/File_MpegTs_Duplicate.cpp
	MediaInfo/Multiple/File_Mxf.cpp
	MediaInfo/Multiple/File_Nut.cpp
	MediaInfo/Multiple/File_Ogg.cpp
	MediaInfo/Multiple/File_Ogg_SubElement.cpp
	MediaInfo/Multiple/File_Riff.cpp
	MediaInfo/Multiple/File_Riff_Elements.cpp
	MediaInfo/Multiple/File_Rm.cpp
	MediaInfo/Multiple/File_Skm.cpp
	MediaInfo/Multiple/File_Swf.cpp
	MediaInfo/Multiple/File_Wm.cpp
	MediaInfo/Multiple/File_Wm_Elements.cpp
	MediaInfo/Tag/File__Tags.cpp
	MediaInfo/Tag/File_ApeTag.cpp
	MediaInfo/Tag/File_Id3.cpp
	MediaInfo/Tag/File_Id3v2.cpp
	MediaInfo/Tag/File_Lyrics3.cpp
	MediaInfo/Tag/File_Lyrics3v2.cpp
	MediaInfo/Tag/File_VorbisCom.cpp
	MediaInfo/Text/File_Cmml.cpp
	MediaInfo/Text/File_Eia608.cpp
	MediaInfo/Text/File_Eia708.cpp
	MediaInfo/Text/File_Kate.cpp
	MediaInfo/Text/File_OtherText.cpp
	MediaInfo/Text/File_Pgs.cpp
	MediaInfo/Video/File_Avc.cpp
	MediaInfo/Video/File_Avc_Duplicate.cpp
	MediaInfo/Video/File_AvsV.cpp
	MediaInfo/Video/File_Dirac.cpp
	MediaInfo/Video/File_Flic.cpp
	MediaInfo/Video/File_Mpeg4v.cpp
	MediaInfo/Video/File_Mpegv.cpp
	MediaInfo/Video/File_Theora.cpp
	MediaInfo/Video/File_Vc1.cpp
	MediaInfo/MediaInfoDLL.cpp
	MediaInfo/MediaInfoDLL.def
)

if (WIN32)
	#FIXME MediaInfo.rc should use ${MEDIAINFO_MAJOR_VERSION} and friends
	list(APPEND mediainfo_SRCS
		MediaInfo.rc
	)
endif (WIN32)

add_library(mediainfo SHARED ${mediainfo_SRCS})

target_link_libraries(mediainfo
	zenlib
	${ZLIB_LIBRARY}
)

set_target_properties(mediainfo PROPERTIES
	VERSION ${MEDIAINFO_VERSION}
	SOVERSION ${MEDIAINFO_MAJOR_VERSION}
)

install(TARGETS mediainfo DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})