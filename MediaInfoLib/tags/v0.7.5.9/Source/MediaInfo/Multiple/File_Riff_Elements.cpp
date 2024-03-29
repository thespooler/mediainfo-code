// File_Riff - Info for RIFF files
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
//
// Elements part
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
// Compilation conditions
#include <MediaInfo/Setup.h>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifdef MEDIAINFO_RIFF_YES
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Multiple/File_Riff.h"
#if defined(MEDIAINFO_MPEG4V_YES)
    #include "MediaInfo/Video/File_Mpeg4v.h"
#endif
#if defined(MEDIAINFO_AVC_YES)
    #include "MediaInfo/Video/File_Avc.h"
#endif
#if defined(MEDIAINFO_MPEGA_YES)
    #include "MediaInfo/Audio/File_Mpega.h"
#endif
#if defined(MEDIAINFO_AC3_YES)
    #include "MediaInfo/Audio/File_Ac3.h"
#endif
#if defined(MEDIAINFO_DTS_YES)
    #include "MediaInfo/Audio/File_Dts.h"
#endif
#if defined(MEDIAINFO_MPEG4_YES)
    #include "MediaInfo/Audio/File_Mpeg4_AudioSpecificConfig.h"
#endif
#if defined(MEDIAINFO_ADTS_YES)
    #include "MediaInfo/Audio/File_Adts.h"
#endif
#if defined(MEDIAINFO_JPEG_YES)
    #include "MediaInfo/Image/File_Jpeg.h"
#endif
#if defined(MEDIAINFO_OTHERTEXT_YES)
    #include "MediaInfo/Text/File_OtherText.h"
#endif
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Const
//***************************************************************************

namespace Elements
{
    const int32u FORM=0x464F524D;
    const int32u LIST=0x4C495354;
    const int32u RIFF=0x52494646;

    const int32u AIFC=0x41494643;
    const int32u AIFC_COMM=0x434F4D4D;
    const int32u AIFC_COMT=0x434F4D54;
    const int32u AIFC_FVER=0x46564552;
    const int32u AIFC_SSND=0x53534E44;
    const int32u AIFF=0x41494646;
    const int32u AIFF_COMM=0x434F4D4D;
    const int32u AIFF_COMT=0x434F4D54;
    const int32u AIFF_SSND=0x53534E44;
    const int32u AIFF__c__=0x28632920;
    const int32u AIFF_ANNO=0x414E4E4F;
    const int32u AIFF_AUTH=0x41555448;
    const int32u AIFF_NAME=0x4E414D45;
    const int32u AVI_=0x41564920;
    const int32u AVI__cset=0x63736574;
    const int32u AVI__exif=0x65786966;
    const int32u AVI__exif_ecor=0x65636F72;
    const int32u AVI__exif_emdl=0x656D646C;
    const int32u AVI__exif_emnt=0x656D6E74;
    const int32u AVI__exif_erel=0x6572656C;
    const int32u AVI__exif_etim=0x6574696D;
    const int32u AVI__exif_eucm=0x6575636D;
    const int32u AVI__exif_ever=0x65766572;
    const int32u AVI__goog=0x676F6F67;
    const int32u AVI__goog_GDAT=0x47444154;
    const int32u AVI__GMET=0x474D4554;
    const int32u AVI__hdlr=0x6864726C;
    const int32u AVI__hdlr_avih=0x61766968;
    const int32u AVI__hdlr_JUNK=0x4A554E4B;
    const int32u AVI__hdlr_strl=0x7374726C;
    const int32u AVI__hdlr_strl_indx=0x696E6478;
    const int32u AVI__hdlr_strl_JUNK=0x4A554E4B;
    const int32u AVI__hdlr_strl_strd=0x73747264;
    const int32u AVI__hdlr_strl_strf=0x73747266;
    const int32u AVI__hdlr_strl_strh=0x73747268;
    const int32u AVI__hdlr_strl_strh_auds=0x61756473;
    const int32u AVI__hdlr_strl_strh_iavs=0x69617673;
    const int32u AVI__hdlr_strl_strh_mids=0x6D696473;
    const int32u AVI__hdlr_strl_strh_vids=0x76696473;
    const int32u AVI__hdlr_strl_strh_txts=0x74787473;
    const int32u AVI__hdlr_strl_strn=0x7374726E;
    const int32u AVI__hdlr_strl_vprp=0x76707270;
    const int32u AVI__hdlr_odml=0x6F646D6C;
    const int32u AVI__hdlr_odml_dmlh=0x646D6C68;
    const int32u AVI__idx1=0x69647831;
    const int32u AVI__INFO=0x494E464F;
    const int32u AVI__INFO_IARL=0x4941524C;
    const int32u AVI__INFO_IART=0x49415254;
    const int32u AVI__INFO_ICMS=0x49434D53;
    const int32u AVI__INFO_ICMT=0x49434D54;
    const int32u AVI__INFO_ICOP=0x49434F50;
    const int32u AVI__INFO_ICRD=0x49435244;
    const int32u AVI__INFO_ICRP=0x49435250;
    const int32u AVI__INFO_IDIM=0x4944494D;
    const int32u AVI__INFO_IDIT=0x49444954;
    const int32u AVI__INFO_IDPI=0x49445049;
    const int32u AVI__INFO_IENG=0x49454E47;
    const int32u AVI__INFO_IGNR=0x49474E52;
    const int32u AVI__INFO_IKEY=0x494B4559;
    const int32u AVI__INFO_ILGT=0x494C4754;
    const int32u AVI__INFO_ILNG=0x494C4E47;
    const int32u AVI__INFO_IMED=0x494D4544;
    const int32u AVI__INFO_INAM=0x494E414D;
    const int32u AVI__INFO_IPLT=0x49504C54;
    const int32u AVI__INFO_IPRD=0x49505244;
    const int32u AVI__INFO_IRTD=0x49525444;
    const int32u AVI__INFO_ISBJ=0x4953424A;
    const int32u AVI__INFO_ISFT=0x49534654;
    const int32u AVI__INFO_ISHP=0x49534850;
    const int32u AVI__INFO_ISRC=0x49535243;
    const int32u AVI__INFO_ISRF=0x49535246;
    const int32u AVI__INFO_ITCH=0x49544348;
    const int32u AVI__INFO_JUNK=0x4A554E4B;
    const int32u AVI__JUNK=0x4A554E4B;
    const int32u AVI__movi=0x6D6F7669;
    const int32u AVI__movi_rec_=0x72656320;
    const int32u AVI__movi_xxxx___db=0x00006462;
    const int32u AVI__movi_xxxx___dc=0x00006463;
    const int32u AVI__movi_xxxx___sb=0x00007362;
    const int32u AVI__movi_xxxx___tx=0x00007478;
    const int32u AVI__movi_xxxx___wb=0x00007762;
    const int32u AVIX=0x41564958;
    const int32u AVIX_idx1=0x69647831;
    const int32u AVIX_movi=0x6D6F7669;
    const int32u AVIX_movi_rec_=0x72656320;
    const int32u IDVX=0x49445658;
    const int32u JUNK=0x4A554E4B;
    const int32u menu=0x6D656E75;
    const int32u MThd=0x4D546864;
    const int32u MTrk=0x4D54726B;
    const int32u PAL_=0x50414C20;
    const int32u RDIB=0x52444942;
    const int32u RMID=0x524D4944;
    const int32u RMMP=0x524D4D50;
    const int32u WAVE=0x57415645;
    const int32u WAVE_data=0x64617461;
    const int32u WAVE_fact=0x66616374;
    const int32u WAVE_fmt_=0x666D7420;
    const int32u W3DI=0x57334449;
}

//***************************************************************************
// Format
//***************************************************************************

//---------------------------------------------------------------------------
void File_Riff::Data_Parse()
{
    //alignement specific
    if (Alignement_ExtraByte)
        Element_Size--;

    DATA_BEGIN
    LIST(AIFC)
        ATOM_BEGIN
        ATOM(AIFC_COMM)
        ATOM(AIFC_COMT)
        ATOM(AIFC_FVER)
        LIST(AIFC_SSND)
            ATOM_BEGIN
            ATOM_END
        ATOM_DEFAULT(AIFC_xxxx)
        ATOM_END_DEFAULT
    LIST(AIFF)
        ATOM_BEGIN
        ATOM(AIFF_COMM)
        ATOM(AIFF_COMT)
        LIST(AIFF_SSND)
            ATOM_BEGIN
            ATOM_END
        ATOM_DEFAULT(AIFF_xxxx)
        ATOM_END_DEFAULT
    LIST(AVI_)
        ATOM_BEGIN
        ATOM(AVI__cset)
        LIST(AVI__exif)
            ATOM_BEGIN
            ATOM_DEFAULT(AVI__exif_xxxx)
            ATOM_END_DEFAULT
        LIST(AVI__goog)
            ATOM_BEGIN
            ATOM(AVI__goog_GDAT)
            ATOM_END
        ATOM(AVI__GMET)
        LIST(AVI__hdlr)
            ATOM_BEGIN
            ATOM(AVI__hdlr_avih)
            ATOM(AVI__hdlr_JUNK)
            LIST(AVI__hdlr_strl)
                ATOM_BEGIN
                ATOM(AVI__hdlr_strl_indx)
                ATOM(AVI__hdlr_strl_JUNK)
                ATOM(AVI__hdlr_strl_strf)
                ATOM(AVI__hdlr_strl_strh)
                ATOM(AVI__hdlr_strl_strn)
                ATOM(AVI__hdlr_strl_vprp)
                ATOM_END
            LIST(AVI__hdlr_odml)
                ATOM_BEGIN
                ATOM(AVI__hdlr_odml_dmlh)
                ATOM_END
            ATOM_DEFAULT(AVI__hdlr_xxxx)
            ATOM_END_DEFAULT
        LIST(AVI__idx1)
            ATOM_BEGIN
            ATOM_END
        LIST(AVI__INFO)
            ATOM_BEGIN
            ATOM(AVI__INFO_JUNK)
            ATOM_DEFAULT(AVI__INFO_xxxx)
            ATOM_END_DEFAULT
        ATOM(AVI__JUNK)
        LIST(AVI__movi)
            ATOM_BEGIN
            LIST(AVI__movi_rec_)
                ATOM_BEGIN
                ATOM_DEFAULT(AVI__movi_xxxx)
                ATOM_END_DEFAULT
            ATOM_DEFAULT(AVI__movi_xxxx)
            ATOM_END_DEFAULT
        ATOM_END
    LIST(AVIX) //OpenDML
        ATOM_BEGIN
        ATOM(AVIX_idx1)
        LIST(AVIX_movi)
            ATOM_BEGIN
            LIST(AVIX_movi_rec_)
                ATOM_BEGIN
                ATOM_DEFAULT(AVIX_movi_xxxx)
                ATOM_END_DEFAULT
            ATOM_DEFAULT(AVIX_movi_xxxx)
            ATOM_END_DEFAULT
        ATOM_END
    ATOM(IDVX)
    LIST(JUNK)
        ATOM_BEGIN
        ATOM_END
    LIST(menu)
        ATOM_BEGIN
        ATOM_END
    ATOM(MThd)
    LIST(MTrk)
        ATOM_BEGIN
        ATOM_END
    LIST(PAL_)
        ATOM_BEGIN
        ATOM_END
    LIST(RDIB)
        ATOM_BEGIN
        ATOM_END
    LIST(RMID)
        ATOM_BEGIN
        ATOM_END
    LIST(RMMP)
        ATOM_BEGIN
        ATOM_END
    ATOM(W3DI)
    LIST(WAVE)
        ATOM_BEGIN
        ATOM(WAVE_fmt_)
        ATOM(WAVE_fact)
        LIST(WAVE_data)
            break;
        ATOM_END
    DATA_END

    if (Alignement_ExtraByte)
    {
        Element_Size++;
        if (File_GoTo==(size_t)-1)
            Skip_XX(1,                                          "Alignement");
    }
}

//***************************************************************************
// Elements
//***************************************************************************

//---------------------------------------------------------------------------
void File_Riff::AIFC()
{
    Element_Name("AIFF Compressed");

    //Filling
    Stream_Prepare(Stream_General);
    Fill("Format", "AIFF");
    Stream_Prepare(Stream_Audio);
}

//---------------------------------------------------------------------------
void File_Riff::AIFC_COMM()
{
    AIFF_COMM();
}

//---------------------------------------------------------------------------
void File_Riff::AIFC_COMT()
{
    AIFF_COMT();
}

//---------------------------------------------------------------------------
void File_Riff::AIFC_FVER()
{
    Element_Name("Format Version");

    //Parsing
    Skip_B4(                                                    "Version");
}

//---------------------------------------------------------------------------
void File_Riff::AIFC_SSND()
{
    AIFF_SSND();
}

//---------------------------------------------------------------------------
void File_Riff::AIFC_xxxx()
{
    AIFF_xxxx();
}

//---------------------------------------------------------------------------
void File_Riff::AIFF()
{
    Element_Name("AIFF");

    //Filling
    Stream_Prepare(Stream_General);
    Fill("Format", "AIFF");
    Stream_Prepare(Stream_Audio);
}

//---------------------------------------------------------------------------
void File_Riff::AIFF_COMM()
{
    Element_Name("Common");

    int32u numSampleFrames;
    int16u numChannels, sampleSize;
    float80 sampleRate;
    //Parsing
    Get_B2 (numChannels,                                    "numChannels");
    Get_B4 (numSampleFrames,                                "numSampleFrames");
    Get_B2 (sampleSize,                                     "sampleSize");
    Get_BF10(sampleRate,                                    "sampleRate");
    if (Data_Remain()) //AIFC
    {
        int32u compressionType;
        Get_C4 (compressionType,                            "compressionType");
        Skip_PA(                                            "compressionName");

        //Filling
        Fill("Codec", Ztring().From_CC4(compressionType));
    }
    else
        //Filling
        Fill("Codec", "PCM");

    //Filling
    Fill("Channel(s)", numChannels);
    Fill("Resolution", sampleSize);
    if (sampleRate)
        Fill("PlayTime", numSampleFrames/sampleRate*1000);
    Fill("SamplingRate", sampleRate, 0);
}

//---------------------------------------------------------------------------
void File_Riff::AIFF_COMT()
{
    //Parsing
    int16u numComments;
    Get_B2(numComments,                                         "numComments");
    for (int16u Pos=0; Pos<=numComments; Pos++)
    {
        Ztring text;
        int16u count;
        Element_Begin("Comment");
        Skip_B4(                                                "timeStamp");
        Skip_B4(                                                "marker");
        Get_B2 (count,                                          "count");
        count+=count%1; //always even
        Get_Local(count, text,                                  "text");
        Element_End();

        //Filling
        Fill("Comment", text);
    }
}

//---------------------------------------------------------------------------
void File_Riff::AIFF_SSND()
{
    Element_Name("Sound Data");

    //Filling
    Finnished();
}

//---------------------------------------------------------------------------
void File_Riff::AIFF_xxxx()
{
    #define ELEMENT_CASE(_ELEMENT, _NAME) \
        case Elements::_ELEMENT : Element_Name(_NAME); Name=_NAME; break;

    //Known?
    std::string Name;
    switch(Element_Code)
    {
        ELEMENT_CASE(AIFF__c__, "Copyright");
        ELEMENT_CASE(AIFF_ANNO, "Comment");
        ELEMENT_CASE(AIFF_AUTH, "Performer");
        ELEMENT_CASE(AIFF_NAME, "Title");
        default : Skip_XX(Element_Size,                         "Unknown");
                  return;
    }

    //Parsing
    Ztring text;
    Get_Local(Element_Size, text,                               "text");

    //Filling
    Fill(Name.c_str(), text);
}

//---------------------------------------------------------------------------
void File_Riff::AVI_()
{
    Element_Name("AVI");

    //Test if there is only one AVI chunk
    if (Count_Get(Stream_General)>0)
    {
        Element_Info("Problem: 2 AVI chunks, this is not normal");
        Finnished();
        return;
    }

    //Filling
    Stream_Prepare(Stream_General);
    Fill("Format", "AVI");

    //Configuring
    Buffer_MaximumSize=16*1024*1024;
}

//---------------------------------------------------------------------------
void File_Riff::AVI__cset()
{
    Element_Name("Regional settings");

    //Parsing
    Skip_L2(                                                    "CodePage"); //TODO: take a look about IBM/MS RIFF/MCI Specification 1.0
    Skip_L2(                                                    "CountryCode");
    Skip_L2(                                                    "LanguageCode");
    Skip_L2(                                                    "Dialect");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__exif()
{
    Element_Name("Exif (Exchangeable Image File Format)");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__exif_xxxx()
{
    Element_Name("Value");

    //Parsing
    Ztring Value;
    Get_Local(Element_Size, Value,                              "Value");

    //Filling
    switch (Element_Code)
    {
        case Elements::AVI__exif_ecor : Fill(Stream_General, 0, "Make", Value); break;
        case Elements::AVI__exif_emdl : Fill(Stream_General, 0, "Model", Value); break;
        case Elements::AVI__exif_emnt : Fill(Stream_General, 0, "MakerNotes", Value); break;
        case Elements::AVI__exif_erel : Fill(Stream_General, 0, "RelatedImageFile", Value); break;
        case Elements::AVI__exif_etim : Fill(Stream_General, 0, "Written_Date", Value); break;
        case Elements::AVI__exif_eucm : Fill(Stream_General, 0, "Comment", Value); break;
        case Elements::AVI__exif_ever : break; //Exif version
        default:                    Fill(Stream_General, 0, Ztring().From_CC4((int32u)Element_Code).To_Local().c_str(), Value);
    }
}

//---------------------------------------------------------------------------
void File_Riff::AVI__goog()
{
    Element_Name("Google specific");

    //Filling
    Fill("Format", "GVI", Unlimited, false, true);
}

//---------------------------------------------------------------------------
void File_Riff::AVI__goog_GDAT()
{
    Element_Name("Google datas");
}

//---------------------------------------------------------------------------
// Google Metadata
//
void File_Riff::AVI__GMET()
{
    Element_Name("Google Metadatas");

    //Parsing
    Ztring Value; Value.From_Local((const char*)(Buffer+Buffer_Offset+0), (size_t)Element_Size);
    ZtringListList List;
    List.Separator_Set(0, _T("\n"));
    List.Separator_Set(1, _T(":"));
    List.Max_Set(1, 2);
    List.Write(Value);

    //Details
    if (Config.Details_Get())
    {
        //for (size_t Pos=0; Pos<List.size(); Pos++)
        //    Details_Add_Info(Pos, List(Pos, 0).To_Local().c_str(), List(Pos, 1));
    }

    //Filling
    for (size_t Pos=0; Pos<List.size(); Pos++)
    {
        if (List(Pos, 0)==_T("gvp_version"));
        if (List(Pos, 0)==_T("duration"));
        if (List(Pos, 0)==_T("title"))          Fill(Stream_General, 0, "Title", List(Pos, 1));
        if (List(Pos, 0)==_T("description"))    Fill(Stream_General, 0, "Title/More", List(Pos, 1));
        if (List(Pos, 0)==_T("url"))            Fill(Stream_General, 0, "Title/Url", List(Pos, 1));
        if (List(Pos, 0)==_T("docid"))          Fill(Stream_General, 0, "UniqueID", List(Pos, 1));
    }
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr()
{
    Element_Name("AVI Header");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_avih()
{
    Element_Name("File header");

    //Parsing
    int32u MicrosecPerFrame, Flags;
    Get_L4 (MicrosecPerFrame,                                   "MicrosecPerFrame");
    Skip_L4(                                                    "MaxBytesPerSec");
    Skip_L4(                                                    "PaddingGranularity");
    Get_L4 (Flags,                                              "Flags");
        Skip_Flags(Flags,  4,                                   "HasIndex");
        Skip_Flags(Flags,  5,                                   "MustUseIndex");
        Skip_Flags(Flags,  8,                                   "IsInterleaved");
        Skip_Flags(Flags,  9,                                   "UseCKTypeToFindKeyFrames");
        Skip_Flags(Flags, 11,                                   "TrustCKType");
        Skip_Flags(Flags, 16,                                   "WasCaptureFile");
        Skip_Flags(Flags, 17,                                   "Copyrighted");
    Get_L4 (avih_TotalFrame,                                    "TotalFrames");
    Skip_L4(                                                    "InitialFrames");
    Skip_L4(                                                    "StreamsCount");
    Skip_L4(                                                    "SuggestedBufferSize");
    Skip_L4(                                                    "Width");
    Skip_L4(                                                    "Height");
    Skip_L4(                                                    "Reserved");
    Skip_L4(                                                    "Reserved");
    Skip_L4(                                                    "Reserved");
    Skip_L4(                                                    "Reserved");
    if(Element_Offset<Element_Size)
        Skip_XX(Element_Size-Element_Offset,                    "Unknown");

    //Filling
    if (MicrosecPerFrame>0)
        avih_FrameRate=1000000.0/MicrosecPerFrame;
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_JUNK()
{
    Element_Name("Garbage");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_odml()
{
    Element_Name("OpenDML");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_odml_dmlh()
{
    Element_Name("OpenDML Header");

    //Parsing
    Get_L4(dmlh_TotalFrame,                                     "GrandFrames");
    if (Element_Offset<Element_Size)
        Skip_XX(Element_Size-Element_Offset,                    "Unknown");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl()
{
    Element_Name("Stream info");
    Element_Info(stream_Count);

    //Clean up
    StreamKind_Last=Stream_Max;

    //Compute the current codec ID
    Stream_ID=(('0'+stream_Count/10)*0x01000000
              +('0'+stream_Count   )*0x00010000);
    stream_Count++;
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_indx()
{
    Element_Name("Index");

    int32u Entry_Count, ChunkId;
    int16u LongsPerEntry;
    int8u  IndexType, IndexSubType;
    Get_L2 (LongsPerEntry,                                      "LongsPerEntry"); //Size of each entry in aIndex array
    Get_L1 (IndexSubType,                                       "IndexSubType");
    Get_L1 (IndexType,                                          "IndexType");
    Get_L4 (Entry_Count,                                        "EntriesInUse"); //Index of first unused member in aIndex array
    Get_C4 (ChunkId,                                            "ChunkId"); //FCC of what is indexed

    //Depends of size of structure...
    switch (IndexType)
    {
        case 0x01 : //AVI_INDEX_OF_CHUNKS
                    switch (IndexSubType)
                    {
                        case 0x00 : AVI__hdlr_strl_indx_StandardIndex(Entry_Count, ChunkId); break;
                        case 0x01 : AVI__hdlr_strl_indx_FieldIndex(Entry_Count, ChunkId); break; //AVI_INDEX_2FIELD
                        default: Skip_XX(Element_Size-Element_Offset, "Unknown");
                    }
                    break;
        case 0x0 : //AVI_INDEX_OF_INDEXES
                    switch (IndexSubType)
                    {
                        case 0x00 :
                        case 0x01 : AVI__hdlr_strl_indx_SuperIndex(Entry_Count, ChunkId); break; //AVI_INDEX_2FIELD
                        default: Skip_XX(Element_Size-Element_Offset, "Unknown");
                    }
                    break;
        default: Skip_XX(Element_Size-Element_Offset,           "Unknown");
    }
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_indx_StandardIndex(int32u Entry_Count, int32u ChunkId)
{
    Element_Name("Standard Index");

    //Parsing
    int64u BaseOffset, StreamSize=0;
    Get_L8 (BaseOffset,                                         "BaseOffset");
    Skip_L4(                                                    "Reserved3");
    for (int32u Pos=0; Pos<Entry_Count; Pos++)
    {
        //Is too slow
        /*
        Element_Begin("Index");
        int32u Offset, Size;
        Get_L4 (Offset,                                         "Offset"); //BaseOffset + this is absolute file offset
        Get_L4 (Size,                                           "Size"); //Bit 31 is set if this is NOT a keyframe
        Element_Info(Size&0x7FFFFFFF);
        if (Size)
            Element_Info("KeyFrame");
        Element_End();
        */

        //Faster method
        int32u Offset=LittleEndian2int32u(Buffer+Buffer_Offset+Element_Offset  );
        int32u Size  =LittleEndian2int32u(Buffer+Buffer_Offset+Element_Offset+4)&0x7FFFFFFF;
        Element_Offset+=8;

        //Stream Position and size
        if (Pos<300)
            Stream_Pos[BaseOffset+Offset-8]=ChunkId&0xFFFF0000;
        StreamSize+=(Size&0x7FFFFFFF);

        //Interleaved
        if (Pos==  0 && (ChunkId&0xFFFF0000)==0x30300000 && Interleaved0_1  ==0)
            Interleaved0_1 =BaseOffset+Offset-8;
        if (Pos==Entry_Count/10 && (ChunkId&0xFFFF0000)==0x30300000 && Interleaved0_10==0)
            Interleaved0_10=BaseOffset+Offset-8;
        if (Pos==  0 && (ChunkId&0xFFFF0000)==0x30310000 && Interleaved1_1  ==0)
            Interleaved1_1 =BaseOffset+Offset-8;
        if (Pos==Entry_Count/10 && (ChunkId&0xFFFF0000)==0x30310000 && Interleaved1_10==0)
            Interleaved1_10=BaseOffset+Offset-8;
    }
    Stream[ChunkId&0xFFFF0000].StreamSize+=StreamSize;
    if (Element_Offset<Element_Size)
        Skip_XX(Element_Size-Element_Offset,                    "Garbage");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_indx_FieldIndex(int32u Entry_Count, int32u ChunkId)
{
    Element_Name("Field Index");

    //Parsing
    Skip_L8(                                                    "Offset");
    Skip_L4(                                                    "Reserved2");
    for (int32u Pos=0; Pos<Entry_Count; Pos++)
    {
        Element_Begin("Index");
        Skip_L4(                                                "Offset"); //BaseOffset + this is absolute file offset
        Skip_L4(                                                "Size"); //Bit 31 is set if this is NOT a keyframe
        Skip_L4(                                                "OffsetField2"); //Offset to second field
        Element_End();
    }
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_indx_SuperIndex(int32u Entry_Count, int32u ChunkId)
{
    Element_Name("Index of Indexes");

    //Parsing
    int64u Offset;
    Skip_L4(                                                    "Reserved0");
    Skip_L4(                                                    "Reserved1");
    Skip_L4(                                                    "Reserved2");
    for (int32u Pos=0; Pos<Entry_Count; Pos++)
    {
        Element_Begin("Index of Indexes");
        Get_L8 (Offset,                                         "Offset");
        Skip_L4(                                                "Size"); //Size of index chunk at this offset
        Skip_L4(                                                "Duration"); //time span in stream ticks
        Index_Pos[Offset]=ChunkId;
        Element_End();
    }

    //We needn't anymore Old version
    NeedOldIndex=false;
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_JUNK()
{
    Element_Name("Garbage");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_strd()
{
    Element_Name("Stream datas");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_strf()
{
    Element_Name("Stream format");

    //Parse depending of kind of stream
    switch (Stream[Stream_ID].fccType)
    {
        case Elements::AVI__hdlr_strl_strh_auds : AVI__hdlr_strl_strf_auds(); break;
        case Elements::AVI__hdlr_strl_strh_iavs : AVI__hdlr_strl_strf_iavs(); break;
        case Elements::AVI__hdlr_strl_strh_mids : AVI__hdlr_strl_strf_mids(); break;
        case Elements::AVI__hdlr_strl_strh_txts : AVI__hdlr_strl_strf_txts(); break;
        case Elements::AVI__hdlr_strl_strh_vids : AVI__hdlr_strl_strf_vids(); break;
        default :                                 Element_Info("Unknown");
    }

    //Registering stream
    Stream[Stream_ID].StreamKind=StreamKind_Last;
    Stream[Stream_ID].StreamPos=StreamPos_Last;
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_strf_auds()
{
    Element_Info("Audio");

    //Parsing
    int32u SamplesPerSec, AvgBytesPerSec;
    int16u FormatTag, Channels, BitsPerSample;
    Get_L2 (FormatTag,                                          "FormatTag");
    Get_L2 (Channels,                                           "Channels");
    Get_L4 (SamplesPerSec,                                      "SamplesPerSec");
    Get_L4 (AvgBytesPerSec,                                     "AvgBytesPerSec");
    Skip_L2(                                                    "BlockAlign");
    Get_L2 (BitsPerSample,                                      "BitsPerSample");

    //Filling
    Stream_Prepare(Stream_Audio);
    Stream[Stream_ID].Compression=FormatTag;
    Ztring Codec; Codec.From_Number(FormatTag, 16);
    Codec.MakeUpperCase();
    Fill("Codec", Codec); //May be replaced by codec parser
    Fill("Codec/CC", Codec);
    Fill("Channel(s)", Channels!=5?Channels:6);
    Fill("SamplingRate", SamplesPerSec);
    Fill("BitRate", AvgBytesPerSec*8);
    if (BitsPerSample) Fill("Resolution", BitsPerSample);
    Stream[Stream_ID].AvgBytesPerSec=AvgBytesPerSec; //Saving bitrate for each stream

    //Creating the parser
         if (0);
    #if defined(MEDIAINFO_MPEGA_YES)
    else if (Config.Codec_Get(Codec, InfoCodec_KindofCodec).find(_T("MPEG-"))==0)
        Stream[Stream_ID].Parser=new File_Mpega;
    #endif
    #if defined(MEDIAINFO_AC3_YES)
    else if (FormatTag==0x2000)
    {
        Stream[Stream_ID].Parser=new File_Ac3;
        ((File_Ac3*)Stream[Stream_ID].Parser)->Frame_Count_Valid=1;
    }
    #endif
    #if defined(MEDIAINFO_DTS_YES)
    else if (FormatTag==0x2001
          || (FormatTag==0x1 && Get(Stream_General, 0, _T("Format"))==_T("WAV"))) //Some DTS streams are coded "1"
    {
        Stream[Stream_ID].Parser=new File_Dts;
        ((File_Dts*)Stream[Stream_ID].Parser)->Frame_Count_Valid=1;
    }
    #endif
    #if defined(MEDIAINFO_ADTS_YES)
    else if (FormatTag==0xAAC || FormatTag==0xFF)
        Stream[Stream_ID].Parser=new File_Adts;
    #endif

    //Options
    if (Element_Offset+2>Element_Size)
        return; //No options
        
    //Parsing
    int16u Option_Size;
    Get_L2 (Option_Size,                                        "cbSize");

    //Filling
    if (Option_Size>0)
    {
             if (0);
        else if (Config.Codec_Get(Codec, InfoCodec_KindofCodec).find(_T("MPEG-1"))==0)
            AVI__hdlr_strl_strf_auds_Mpega();
        else if (Codec==_T("AAC") || Codec==_T("FF"))
            AVI__hdlr_strl_strf_auds_Aac();
        else Skip_XX(Option_Size,                               "Unknown");
    }
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_strf_auds_Mpega()
{
    //Parsing
    Element_Begin("MPEG Audio options");
    Skip_L2(                                                    "ID");
    Skip_L4(                                                    "Flags");
    Skip_L2(                                                    "BlockSize");
    Skip_L2(                                                    "FramesPerBlock");
    Skip_L2(                                                    "CodecDelay");
    Element_End();
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_strf_auds_Aac()
{
    //Parsing
    Element_Begin("AAC options");
    #if defined(MEDIAINFO_MPEG4_YES)
        File_Mpeg4_AudioSpecificConfig MI;
        Open_Buffer_Init(&MI, File_Size, File_Offset+Buffer_Offset+(size_t)Element_Offset);
        Open_Buffer_Continue(&MI, Buffer+Buffer_Offset+(size_t)Element_Offset, (size_t)(Element_Size-Element_Offset));
        Open_Buffer_Finalize(&MI);
        Merge(MI, StreamKind_Last, 0, StreamPos_Last);
    #endif
    Element_End();
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_strf_iavs()
{
    //Standard video header before Iavs?
    if (Element_Size==72)
    {
        Element_Begin();
            AVI__hdlr_strl_strf_vids();
        Element_End();
    }

    Element_Info("Interleaved Audio/Video");

    //Parsing
    Skip_L4(                                                    "DVAAuxSrc");
    Skip_L4(                                                    "DVAAuxCtl");
    Skip_L4(                                                    "DVAAuxSrc1");
    Skip_L4(                                                    "DVAAuxCtl1");
    Skip_L4(                                                    "DVVAuxSrc");
    Skip_L4(                                                    "DVVAuxCtl");
    Skip_L4(                                                    "DVReserved");

    //Filling
    Ztring Codec; Codec.From_CC4(Stream[Stream_ID].fccHandler);
    Stream_Prepare(Stream_Video);
    float32 FrameRate=Get(StreamKind_Last, StreamPos_Last, _T("FrameRate")).To_float32();
    Fill("Codec", Codec); //May be replaced by codec parser
    Fill("Codec/CC", Codec);
         if (Codec==_T("dvsd")
          || Codec==_T("dvsl"))
    {
                                    Fill("Width",  720);
             if (FrameRate==25.000) Fill("Height", 576);
        else if (FrameRate==29.970) Fill("Height", 480);
        Fill("DisplayAspectRatio", 4.0/3);
    }
    else if (Codec==_T("dvhd"))
    {
                                    Fill("Width",  1440);
             if (FrameRate==25.000) Fill("Height", 1152);
        else if (FrameRate==30.000) Fill("Height",  960);
        Fill("DisplayAspectRatio", 4.0/3);
    }
    Stream_Prepare(Stream_Audio);
    Fill("Codec", Codec); //May be replaced by codec parser
    Fill("Codec/CC", Codec);
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_strf_mids()
{
    Element_Info("Midi");

    //Filling
    Stream_Prepare(Stream_Audio);
    Fill("Codec", "Midi");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_strf_txts()
{
    Element_Info("Text");

    //Filling
    Stream_Prepare(Stream_Text);

    //Creating the parser
    #if defined(MEDIAINFO_OTHERTEXT_YES)
        Stream[Stream_ID].Parser=new File_OtherText;
    #endif
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_strf_vids()
{
    Element_Info("Video");

    //Parsing
    int32u Compression, Width, Height;
    int16u Resolution;
    Skip_L4(                                                    "Size");
    Get_L4 (Width,                                              "Width");
    Get_L4 (Height,                                             "Height");
    Skip_L2(                                                    "Planes");
    Get_L2 (Resolution,                                         "BitCount");
    Get_C4 (Compression,                                        "Compression");
    Skip_L4(                                                    "SizeImage");
    Skip_L4(                                                    "XPelsPerMeter");
    Skip_L4(                                                    "YPelsPerMeter");
    Skip_L4(                                                    "ClrUsed");
    Skip_L4(                                                    "ClrImportant");
    if(Element_Offset<Element_Size)
        Skip_XX(Element_Size-Element_Offset,                    "Unknown");

    //Filling
    Stream[Stream_ID].Compression=Compression;
    if (((Compression&0x000000FF)>=0x00000020 && (Compression&0x000000FF)<=0x0000007E
      && (Compression&0x0000FF00)>=0x00002000 && (Compression&0x0000FF00)<=0x00007E00
      && (Compression&0x00FF0000)>=0x00200000 && (Compression&0x00FF0000)<=0x007E0000
      && (Compression&0xFF000000)>=0x20000000 && (Compression&0xFF000000)<=0x7E000000)
     ||   Compression==0x00000000
       ) //Sometimes this value is wrong, we have to test this
    {
        if (Compression==CC4("DXSB"))
        {
            //Divx.com hack for subtitle, this is a text stream in a DivX container
            Fill(Stream_General, 0, "Format", "DivX", Unlimited, true, true);
            Stream_Prepare(Stream_Text);
        }
        else
            Stream_Prepare(Stream_Video);

        //Filling
        if (Compression==0x00000000)
            Fill("Codec", "RGB"); //Raw RGB, not handled by automatic codec mapping
        else
        {
            Fill("Codec", Ztring().From_CC4(Compression).To_Local().c_str()); //FormatTag, may be replaced by codec parser
            Fill("Codec/CC", Ztring().From_CC4(Compression).To_Local().c_str()); //FormatTag
        }
        Fill("Width", Width, 10, true);
        Fill("Height", Height, 10, true);
        Fill("Resolution", Resolution);
    }
    else
    {
        //Some Stream headers are broken, must use AVISTREAMINFOA structure instead of AVIFILEINFOA
        Stream_Prepare(Stream_Video);
    }
    Stream[Stream_ID].StreamKind=StreamKind_Last;

    //Creating the parser
         if (0);
    #if defined(MEDIAINFO_MPEG4V_YES)
    else if (Config.Codec_Get(Ztring().From_CC4(Compression), InfoCodec_KindofCodec).find(_T("MPEG-4V"))==0)
    {
        Stream[Stream_ID].Parser=new File_Mpeg4v;
        Stream[Stream_ID].Specific_IsMpeg4v=true;
        ((File_Mpeg4v*)Stream[Stream_ID].Parser)->FrameIsAlwaysComplete=true;
    }
    #endif
    #if defined(MEDIAINFO_AVC_YES)
    else if (Config.Codec_Get(Ztring().From_CC4(Compression), InfoCodec_KindofCodec).find(_T("AVC"))==0)
    {
        Stream[Stream_ID].Parser=new File_Avc;
        ((File_Avc*)Stream[Stream_ID].Parser)->FrameIsAlwaysComplete=true;
    }
    #endif
    #if defined(MEDIAINFO_JPEG_YES)
    else if (Ztring().From_CC4(Compression)==_T("MJPG"))
    {
        Stream[Stream_ID].Parser=new File_Jpeg;
    }
    #endif
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_strh()
{
    Element_Name("Stream header");

    //Parsing
    int32u fccType, fccHandler, Scale, Rate, Length;
    int16u Left, Top, Right, Bottom;
    Get_C4 (fccType,                                            "fccType");
    switch (fccType)
    {
        case Elements::AVI__hdlr_strl_strh_auds :
            Get_L4 (fccHandler,                                 "fccHandler");
            break;
        default:
            Get_C4 (fccHandler,                                 "fccHandler");
    }
    Skip_L4(                                                    "Flags");
    Skip_L2(                                                    "Priority");
    Skip_L2(                                                    "Language");
    Skip_L4(                                                    "InitialFrames");
    Get_L4 (Scale,                                              "Scale");
    Get_L4 (Rate,                                               "Rate"); //Rate/Scale is stream tick rate in ticks/sec
    Skip_L4(                                                    "Start");
    Get_L4 (Length,                                             "Length");
    Skip_L4(                                                    "SuggestedBufferSize");
    Skip_L4(                                                    "Quality");
    Skip_L4(                                                    "SampleSize");
    Get_L2 (Left,                                               "Frame_Left");
    Get_L2 (Top,                                                "Frame_Top");
    Get_L2 (Right,                                              "Frame_Right");
    Get_L2 (Bottom,                                             "Frame_Bottom");
    if(Element_Offset<Element_Size)
        Skip_XX(Element_Size-Element_Offset,                    "Unknown");

    //Filling
    float32 FrameRate=0;
    if (Rate>0 && Scale>0)
    {
        FrameRate=((float32)Rate)/Scale;
        int64u PlayTime=float32_int64s((1000*(float32)Length)/FrameRate);
        if (avih_TotalFrame>0 //avih_TotalFrame is here because some files have a wrong Audio Playtime if TotalFrame==0 (which is a bug, of course!)
        && (avih_FrameRate==0 || PlayTime<((float32)avih_TotalFrame)/avih_FrameRate*1000*1.10)  //Some file have a nearly perfect header, except that the value is false, trying to detect it (false if 10% more than 1st video)
        && (avih_FrameRate==0 || PlayTime>((float32)avih_TotalFrame)/avih_FrameRate*1000*0.90)) //Some file have a nearly perfect header, except that the value is false, trying to detect it (false if 10% less than 1st video)
            Fill("PlayTime", PlayTime);
        else
            Fill("Coherency/PlayTime", PlayTime);
    }
    switch (fccType)
    {
        case Elements::AVI__hdlr_strl_strh_iavs :
        case Elements::AVI__hdlr_strl_strh_vids :
            if (FrameRate>0)  Fill("FrameRate", FrameRate);
        case Elements::AVI__hdlr_strl_strh_txts :
            if (Right-Left>0) Fill("Width",  Right-Left);
            if (Bottom-Top>0) Fill("Height", Bottom-Top);
            break;
        default: ;
    }
    Stream[Stream_ID].fccType=fccType;
    Stream[Stream_ID].fccHandler=fccHandler;
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_strn()
{
    Element_Name("Stream name");

    //Parsing
    Ztring Title;
    Get_Local(Element_Size, Title,                              "StreamName");

    //Filling
    Fill("Title", Title);
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_strl_vprp()
{
    Element_Name("Video properties");

    //Parsing
    int32u FieldPerFrame;
    Skip_L4(                                                    "VideoFormatToken");
    Skip_L4(                                                    "VideoStandard");
    Skip_L4(                                                    "VerticalRefreshRate");
    Skip_L4(                                                    "HTotalInT");
    Skip_L4(                                                    "VTotalInLines");
    Skip_L4(                                                    "FrameAspectRatio");
    Skip_L4(                                                    "FrameWidthInPixels");
    Skip_L4(                                                    "FrameHeightInLines");
    Get_L4 (FieldPerFrame,                                      "FieldPerFrame");
    for (int32u Pos=0; Pos<FieldPerFrame; Pos++)
    {
        Skip_L4(                                                "CompressedBMHeight");
        Skip_L4(                                                "CompressedBMWidth");
        Skip_L4(                                                "ValidBMHeight");
        Skip_L4(                                                "ValidBMWidth");
        Skip_L4(                                                "ValidBMXOffset");
        Skip_L4(                                                "ValidBMYOffset");
        Skip_L4(                                                "VideoXOffsetInT");
        Skip_L4(                                                "VideoYValidStartLine");
    }
    if(Element_Offset<Element_Size)
        Skip_XX(Element_Size-Element_Offset,                    "Unknown");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__hdlr_xxxx()
{
    AVI__INFO_xxxx();
}

//---------------------------------------------------------------------------
void File_Riff::AVI__idx1()
{
    Element_Name("Index (old)");

    //Tests
    if (!NeedOldIndex || Idx1_Offset==(int64u)-1)
    {
        Skip_XX(Element_TotalSize_Get(),                            "Data");
        return;
    }
    else if (!Element_IsComplete_Get())
    {
        Element_WaitForMoreData();
        return;         
    }

    //Parsing
    std::map <int64u, size_t> Stream_Count;
    while (Element_Offset<Element_Size)
    {
        //Is too slow
        /*
        int32u ChunkID, Offset, Size;
        Element_Begin("Index");
        Get_C4 (ChunkID,                                        "ChunkID"); //Bit 31 is set if this is NOT a keyframe
        Info_L4(Flags,                                          "Flags");
            Skip_Flags(Flags, 0,                                "NoTime");
            Skip_Flags(Flags, 1,                                "Lastpart");
            Skip_Flags(Flags, 2,                                "Firstpart");
            Skip_Flags(Flags, 3,                                "Midpart");
            Skip_Flags(Flags, 4,                                "KeyFrame");
        Get_L4 (Offset,                                         "Offset"); //qwBaseOffset + this is absolute file offset
        Get_L4 (Size,                                           "Size"); //Bit 31 is set if this is NOT a keyframe
        Element_Info(Ztring().From_CC4(ChunkID));
        Element_Info(Size);

        //Stream Pos and Size
        int32u StreamID_Temp=(ChunkID&0xFFFF0000);
        Stream[StreamID_Temp].StreamSize+=Size;
        Stream_Pos[Idx1_Offset+Offset]=StreamID_Temp;
        Element_End();
        */

        //Faster method
        int32u StreamID=BigEndian2int32u   (Buffer+Buffer_Offset+Element_Offset   )&0xFFFF0000;
        int32u Offset  =LittleEndian2int32u(Buffer+Buffer_Offset+Element_Offset+ 8);
        int32u Size    =LittleEndian2int32u(Buffer+Buffer_Offset+Element_Offset+12);
        Stream[StreamID].StreamSize+=Size;
        Stream_Pos[Idx1_Offset+Offset]=StreamID;
        Element_Offset+=16;
    }

    //Interleaved
    std::map<int64u, int64u>::iterator Temp=Stream_Pos.begin();
    size_t Pos0=0;
    size_t Pos1=0;
    while (Temp!=Stream_Pos.end())
    {
        switch (Temp->second)
        {
            case 0x30300000 :
                if (Interleaved0_1==0) Interleaved0_1=Temp->first;
                if (Interleaved0_10==0)
                {
                    Pos0++;
                    if (Pos0>1)
                        Interleaved0_10=Temp->first;
                }
                break;
            case 0x30310000 :
                if (Interleaved1_1==0) Interleaved1_1=Temp->first;
                if (Interleaved1_10==0)
                {
                    Pos1++;
                    if (Pos1>1)
                        Interleaved1_10=Temp->first;
                }
                break;
            default:;
        }
        Temp++;
    }
}

//---------------------------------------------------------------------------
void File_Riff::AVI__INFO()
{
    Element_Name("Tags");
}

//---------------------------------------------------------------------------
void File_Riff::AVI__INFO_JUNK()
{
    Element_Name("Garbage");
}

//---------------------------------------------------------------------------
// List of information atoms
// Name                             X bytes, Pos=0
//
void File_Riff::AVI__INFO_xxxx()
{
    //Parsing
    Ztring Value;
    Get_Local(Element_Size, Value,                              "Value");

    //Filling
    stream_t StreamKind=Stream_General;
    Ztring Name;
    switch (Element_Code)
    {
        case Elements::AVI__INFO_IARL : Name="Archival_Location"; break;
        case Elements::AVI__INFO_IART : Name="Director"; break;
        case Elements::AVI__INFO_ICMS : Name="CommissionedBy"; break;
        case Elements::AVI__INFO_ICMT : Name="Comment"; break;
        case Elements::AVI__INFO_ICOP : Name="Copyright"; break;
        case Elements::AVI__INFO_ICRD : Name="Written_Date"; Value.Date_From_String(Value.To_Local().c_str()); break;
        case Elements::AVI__INFO_ICRP : Name="Cropped"; break;
        case Elements::AVI__INFO_IDIM : Name="Dimensions"; break;
        case Elements::AVI__INFO_IDIT : Name="Mastered_Date", Value.Date_From_String(Value.To_Local().c_str()); break;
        case Elements::AVI__INFO_IDPI : Name="DotsPerInch"; break;
        case Elements::AVI__INFO_IENG : Name="Engineer"; break;
        case Elements::AVI__INFO_IGNR : Name="Genre"; break;
        case Elements::AVI__INFO_IKEY : Name="Keywords"; break;
        case Elements::AVI__INFO_ILGT : Name="Ligthness"; break;
        case Elements::AVI__INFO_ILNG : Name="Language"; StreamKind=Stream_Audio; break;
        case Elements::AVI__INFO_IMED : Name="Medium"; break;
        case Elements::AVI__INFO_INAM : Name="Title"; break;
        case Elements::AVI__INFO_IPLT : Name="NumColors"; break;
        case Elements::AVI__INFO_IPRD : Name="Product"; break;
        case Elements::AVI__INFO_IRTD : Name="LawRating"; break;
        case Elements::AVI__INFO_ISBJ : Name="Subject"; break;
        case Elements::AVI__INFO_ISFT : Name="Encoded_Application"; break;
        case Elements::AVI__INFO_ISHP : Name="Sharpness"; break;
        case Elements::AVI__INFO_ISRC : Name="Encoded_Original/DistributedBy"; break;
        case Elements::AVI__INFO_ISRF : Name="Encoded_Original"; break;
        case Elements::AVI__INFO_ITCH : Name="EncodedBy"; break;
        default: Name.From_CC4((int32u)Element_Code);
    }
    Element_Name(Name);
    Element_Info(Value);
    Fill(StreamKind, 0, Name.To_Local().c_str(), Value);
}

//---------------------------------------------------------------------------
void File_Riff::AVI__JUNK()
{
    Element_Name("Garbage"); //Library defined size for padding, often used to store library name

    //Detect DivX files
         if (CC5(Buffer+Buffer_Offset)==CC5("DivX "))
        Fill(Stream_General, 0, "Format", "DivX", Unlimited, true, true);
    //MPlayer
    else if (CC8(Buffer+Buffer_Offset)==CC8("[= MPlay") && Get(Stream_General, 0, _T("Encoded_Library")).empty())
        Fill(Stream_General, 0, "Encoded_Library", "MPlayer");
    //FFMpeg broken files detection
    else if (CC8(Buffer+Buffer_Offset)==CC8("odmldmlh"))
        dmlh_TotalFrame=0; //this is not normal to have this string in a JUNK block!!! and in files tested, in this case TotalFrame is broken too
    //VirtualDubMod
    else if (CC8(Buffer+Buffer_Offset)==CC8("INFOISFT"))
    {
        int32u Size=LittleEndian2int32u(Buffer+Buffer_Offset+8);
        if (Size>Element_Size-12)
            Size=(int32u)Element_Size-12;
        Fill(Stream_General, 0, "Encoded_Library", (const char*)(Buffer+Buffer_Offset+12), Size);
    }
    else if (CC8(Buffer+Buffer_Offset)==CC8("INFOIENG"))
    {
        int32u Size=LittleEndian2int32u(Buffer+Buffer_Offset+8);
        if (Size>Element_Size-12)
            Size=(int32u)Element_Size-12;
        Fill(Stream_General, 0, "Encoded_Library", (const char*)(Buffer+Buffer_Offset+12), Size);
    }
    //Other libraries?
    else if (CC1(Buffer+Buffer_Offset)>=CC1("A") && CC1(Buffer+Buffer_Offset)<=CC1("z") && Get(Stream_General, 0, _T("Encoded_Library")).empty())
        Fill(Stream_General, 0, "Encoded_Library", (const char*)(Buffer+Buffer_Offset), (size_t)Element_Size);
}

//---------------------------------------------------------------------------
void File_Riff::AVI__movi()
{
    Element_Name("Datas");

    //Only the first time, no need in AVIX
    if (movi_Size==0)
    {
        Idx1_Offset=File_Offset+Buffer_Offset-4;
        BookMark_Set(); //Remenbering this place, for stream parsing in phase 2

        //For each stream
        std::map<int32u, stream>::iterator Temp=Stream.begin();
        while (Temp!=Stream.end())
        {
            if (!Temp->second.Parser && Temp->second.fccType!=Elements::AVI__hdlr_strl_strh_txts)
            {
                AVI__movi_StreamClear(Temp->first);
                Temp->second.SearchingPayload=false;
                stream_Count--;
            }
            Temp++;
        }
    }

    //Filling
    movi_Size+=Element_TotalSize_Get();

    //We must parse moov?
    if (NeedOldIndex || (stream_Count==0 && Index_Pos.empty()))
    {
        //Jumping
        Skip_XX(Element_TotalSize_Get(),                        "Data");
        return;
    }

    //Jump to next useful data
    AVI__movi_StreamJump();
}

//---------------------------------------------------------------------------
void File_Riff::AVI__movi_rec_()
{
    Element_Name("Syncronisation");

    rec__Present=true;
}

//---------------------------------------------------------------------------
void File_Riff::AVI__movi_rec__xxxx()
{
    AVI__movi_xxxx();
}

//---------------------------------------------------------------------------
void File_Riff::AVI__movi_xxxx()
{
    if (Element_Code==Elements::AVI__JUNK)
    {
        Skip_XX(Element_Size,                                    "Junk");
        AVI__movi_StreamJump();
        return;
    }

    Stream_ID=(int32u)(Element_Code&0xFFFF0000);

    if (Stream_ID==0x69780000) //ix..
    {
        //AVI Standard Index Chunk
        AVI__hdlr_strl_indx();
        Stream_ID=(int32u)(Element_Code&0x0000FFFF)<<16;
        if (!Stream[Stream_ID].SearchingPayload)
            AVI__movi_StreamClear(Stream_ID);
        AVI__movi_StreamJump();
        return;
    }

    //Finished?
    if (!Stream[Stream_ID].SearchingPayload)
    {
        AVI__movi_StreamJump();
        return;
    }

    Stream[Stream_ID].PacketCount++;
    if (Config.Details_Get())
    {
        switch (Element_Code&0x0000FFFF) //2 last bytes
        {
            case Elements::AVI__movi_xxxx___db :
            case Elements::AVI__movi_xxxx___dc : Element_Info("Video"); break;
            case Elements::AVI__movi_xxxx___sb :
            case Elements::AVI__movi_xxxx___tx : Element_Info("Text"); break;
            case Elements::AVI__movi_xxxx___wb : Element_Info("Audio"); break;
            default :                            Element_Info("Unknown"); break;
        }
        Element_Info(Stream[Stream_ID].PacketCount);
    }

    //Some specific stuff
    switch (Element_Code&0x0000FFFF) //2 last bytes
    {
        case Elements::AVI__movi_xxxx___tx : AVI__movi_xxxx___tx(); break;
        default : ;
    }

    //Parsing
    if (Stream[Stream_ID].Parser)
    {
        Open_Buffer_Init(Stream[Stream_ID].Parser, File_Size, File_Offset+Buffer_Offset+(size_t)Element_Offset);
        Open_Buffer_Continue(Stream[Stream_ID].Parser, Buffer+Buffer_Offset+(size_t)Element_Offset, (size_t)(Element_Size-Element_Offset));
    }

    //Some specific stuff
    switch (Element_Code&0x0000FFFF) //2 last bytes
    {
        case Elements::AVI__movi_xxxx___db :
        case Elements::AVI__movi_xxxx___dc : AVI__movi_xxxx___dc(); break;
        case Elements::AVI__movi_xxxx___wb : AVI__movi_xxxx___wb(); break;
        default : ;
    }

    //We must always parse moov?
    AVI__movi_StreamJump();
}

//---------------------------------------------------------------------------
void File_Riff::AVI__movi_xxxx___dc()
{
    //Finalize (if requested)
    if (Stream[Stream_ID].Parser==NULL
     || Stream[Stream_ID].Parser->File_Offset==File_Size
     || Stream[Stream_ID].PacketCount>=300)
    {
        Stream[Stream_ID].SearchingPayload=false;
        AVI__movi_StreamClear(Stream_ID);
        stream_Count--;
        return;
    }

    //Specific
    #if defined(MEDIAINFO_MPEG4V_YES)
        if (Stream[Stream_ID].Specific_IsMpeg4v && ((File_Mpeg4v*)Stream[Stream_ID].Parser)->RIFF_VOP_Count>1)
        {
            Stream[Stream_ID].SearchingPayload=false;
            AVI__movi_StreamClear(Stream_ID);
            stream_Count--;
        }
    #endif
}

//---------------------------------------------------------------------------
void File_Riff::AVI__movi_xxxx___tx()
{
    //Parsing
    int32u Name_Size;
    Ztring Value;
    Skip_C4(                                                    "GAB2");
    Skip_L1(                                                    "Zero");
    Skip_L2(                                                    "CodePage"); //2=Unicode
    Get_L4 (Name_Size,                                          "Name_Size");
    Skip_UTF16L(Name_Size,                                      "Name");
    Skip_L2(                                                    "Four");
    Skip_L4(                                                    "File_Size");

    //Skip it
    Stream[Stream_ID].SearchingPayload=false;
    AVI__movi_StreamClear(Stream_ID);
    stream_Count--;
}

//---------------------------------------------------------------------------
void File_Riff::AVI__movi_xxxx___wb()
{
    //Finalize (if requested)
    if (Stream[Stream_ID].Parser==NULL
     || Stream[Stream_ID].Parser->File_Offset==File_Size
     || Stream[Stream_ID].PacketCount>=300
     || Element_Size>50000) //For PCM, we disable imediatly
    {
        Stream[Stream_ID].SearchingPayload=false;
        AVI__movi_StreamClear(Stream_ID);
        stream_Count--;
    }
}

//---------------------------------------------------------------------------
void File_Riff::AVI__movi_StreamJump()
{
    //Jump to next useful data
    if (!Index_Pos.empty())
    {
        if (Index_Pos.begin()->first<=File_Offset+Buffer_Offset)
            Index_Pos.erase(Index_Pos.begin());
        int64u ToJump=File_Size;
        if (!Index_Pos.empty())
            ToJump=Index_Pos.begin()->first;
        if (ToJump>File_Size)
            ToJump=File_Size;
        if (ToJump>=File_Offset+Buffer_Offset+Element_TotalSize_Get(Element_Level-2)) //We want always Element movi
            File_GoTo=File_Offset+Buffer_Offset+Element_TotalSize_Get(Element_Level-2); //Not in this chunk
        else if (ToJump!=File_Offset+Buffer_Offset+(Element_Code==Elements::AVI__movi?0:Element_Size))
            File_GoTo=ToJump; //Not just after
    }
    else if (stream_Count==0)
    {
        //Jumping
        Element_Show();
        Element_End();
        if (rec__Present)
            Element_End();
        Info("movi, Jumping to end of chunk");
        if (SecondPass)
            Finnished(); //The rest is already parsed
        else
            File_GoTo=File_Offset+Buffer_Offset+Element_TotalSize_Get();
    }
    else if (!Stream_Pos.empty())
    {
        if (Stream_Pos.begin()->first<=File_Offset+Buffer_Offset)
            Stream_Pos.erase(Stream_Pos.begin());
        if (!Stream_Pos.empty())
        {
            int64u ToJump=Stream_Pos.begin()->first;
            if (ToJump>=File_Offset+Buffer_Offset+Element_TotalSize_Get(Element_Level-2))
                File_GoTo=File_Offset+Buffer_Offset+Element_TotalSize_Get(Element_Level-2); //Not in this chunk
            else if (ToJump!=File_Offset+Buffer_Offset+Element_Size)
                File_GoTo=ToJump; //Not just after
        }
        else
            Finnished();
    }
}

//---------------------------------------------------------------------------
void File_Riff::AVI__movi_StreamClear(int32u ChunkId)
{
    //Erasing index if not needed
    std::map<int64u, int64u>::iterator Temp=Stream_Pos.begin();
    while (Temp!=Stream_Pos.end())
    {
        std::map<int64u, int64u>::iterator Stream_Pos_Temp=Temp;
        bool Useful=true;
        if (Temp->second==ChunkId)
            Useful=false;

        Temp++;

        if (!Useful)
            Stream_Pos.erase(Stream_Pos_Temp);
    }
}

//---------------------------------------------------------------------------
void File_Riff::AVIX()
{
}

//---------------------------------------------------------------------------
void File_Riff::AVIX_idx1()
{
    AVI__idx1();
}

//---------------------------------------------------------------------------
void File_Riff::AVIX_movi()
{
    AVI__movi();
}

//---------------------------------------------------------------------------
void File_Riff::AVIX_movi_rec_()
{
    AVI__movi_rec_();
}

//---------------------------------------------------------------------------
void File_Riff::AVIX_movi_rec__xxxx()
{
    AVIX_movi_xxxx();
}

//---------------------------------------------------------------------------
void File_Riff::AVIX_movi_xxxx()
{
    AVI__movi_xxxx();
}

//---------------------------------------------------------------------------
void File_Riff::IDVX()
{
    Element_Name("Tags");
}

//---------------------------------------------------------------------------
void File_Riff::JUNK()
{
    Element_Name("Junk");

    //Parse
    Skip_XX(Element_TotalSize_Get(),                            "Junk");
}

//---------------------------------------------------------------------------
void File_Riff::menu()
{
    Element_Name("DivX Menu");

    //Filling
    Stream_Prepare(Stream_Menu);
    Fill("Codec", "DivX");
}

//---------------------------------------------------------------------------
void File_Riff::MThd()
{
    Element_Name("MIDI header");

    //Parsing
    Skip_B2(                                                    "format");
    Skip_B2(                                                    "ntrks");
    Skip_B2(                                                    "division");
}

//---------------------------------------------------------------------------
void File_Riff::MTrk()
{
    Element_Name("MIDI Track");

    //Filling
    Stream_Prepare(Stream_General);
    Fill("Format", "Midi");
    Stream_Prepare(Stream_Audio);
    Fill("Codec", "Midi");
    Finnished();
}

//---------------------------------------------------------------------------
void File_Riff::PAL_()
{
    Element_Name("Format: RIFF Palette");

    //Filling
    Stream_Prepare(Stream_General);
    Fill("Format", "RIFF Palette");
}

//---------------------------------------------------------------------------
void File_Riff::RDIB()
{
    Element_Name("Format: RIFF DIB");

    //Filling
    Stream_Prepare(Stream_General);
    Fill("Format", "RIFF DIB");
}

//---------------------------------------------------------------------------
void File_Riff::RMID()
{
    Element_Name("Format: RIFF MIDI");

    //Filling
    Stream_Prepare(Stream_General);
    Fill("Format", "RIFF MIDI");
}

//---------------------------------------------------------------------------
void File_Riff::RMMP()
{
    Element_Name("Format: RIFF MMP");

    //Filling
    Stream_Prepare(Stream_General);
    Fill("Format", "RIFF MMP");
}

//---------------------------------------------------------------------------
void File_Riff::WAVE()
{
    Element_Name("Format: Wave");

    //Filling
    Stream_Prepare(Stream_General);
    Fill("Format", "WAV");
}

//---------------------------------------------------------------------------
void File_Riff::WAVE_data()
{
    Element_Name("Raw datas");

    //Parsing
    Element_Code=CC4("00wb");
    AVI__movi_xxxx();
}

//---------------------------------------------------------------------------
void File_Riff::WAVE_fact()
{
    Element_Name("Sample count");

    //Parsing
    Skip_L4(                                                    "SamplesCount");
    if(Element_Offset<Element_Size)
        Skip_XX(Element_Size-Element_Offset,                    "Unknown");
}

//---------------------------------------------------------------------------
void File_Riff::WAVE_fmt_()
{
    //Compute the current codec ID
    Stream_ID=0x30300000;
    stream_Count=1;

    Stream[0x30300000].fccType=Elements::AVI__hdlr_strl_strh_auds;
    AVI__hdlr_strl_strf();
}

//---------------------------------------------------------------------------
void File_Riff::W3DI()
{
    Element_Name("IDVX tags (Out of specs!)");

    //Parsing
    int32u Size=(int32u)Element_Size;
    Ztring Title, Artist, Album, Unknown, Genre, Comment;
    int32u TrackPos;
    Get_Local(Size, Title,                                      "Title");
    Element_Offset=(int32u)Title.size();
    Size-=(int32u)Title.size();
    if (Size==0) return;
    Skip_L1(                                                    "Zero"); Size--; //NULL char
    Get_Local(Size, Artist,                                     "Artist");
    Element_Offset=(int32u)Title.size()+1+(int32u)Artist.size();
    Size-=(int32u)Artist.size();
    if (Size==0) return;
    Skip_L1(                                                    "Zero"); Size--; //NULL char
    Get_Local(Size, Album,                                      "Album");
    Element_Offset=(int32u)Title.size()+1+(int32u)Artist.size()+1+(int32u)Album.size();
    Size-=(int32u)Album.size();
    if (Size==0) return;
    Skip_L1(                                                    "Zero"); Size--; //NULL char
    Get_Local(Size, Unknown,                                    "Unknown");
    Element_Offset=(int32u)Title.size()+1+(int32u)Artist.size()+1+(int32u)Album.size()+1+(int32u)Unknown.size();
    Size-=(int32u)Unknown.size();
    if (Size==0) return;
    Skip_L1(                                                    "Zero"); Size--; //NULL char
    Get_Local(Size, Genre,                                      "Genre");
    Element_Offset=(int32u)Title.size()+1+(int32u)Artist.size()+1+(int32u)Album.size()+1+(int32u)Unknown.size()+1+(int32u)Genre.size();
    Size-=(int32u)Genre.size();
    if (Size==0) return;
    Skip_L1(                                                    "Zero"); Size--; //NULL char
    Get_Local(Size, Comment,                                    "Comment");
    Element_Offset=(int32u)Title.size()+1+(int32u)Artist.size()+1+(int32u)Album.size()+1+(int32u)Unknown.size()+1+(int32u)Genre.size()+1+(int32u)Comment.size();
    Size-=(int32u)Comment.size();
    if (Size==0) return;
    Skip_L1(                                                    "Zero"); Size--; //NULL char
    Get_L4 (TrackPos,                                           "Track_Position");
    if(Element_Offset+8<Element_Size)
        Skip_XX(Element_Size-Element_Offset,                    "Unknown");
    Element_Begin("Footer");
        Skip_L4(                                                "Size");
        Skip_C4(                                                "Name");
    Element_End();

    //Filling
    Fill(Stream_General, 0, "Track", Title);
    Fill(Stream_General, 0, "Performer", Artist);
    Fill(Stream_General, 0, "Album", Album);
    Fill(Stream_General, 0, "Unknown", Unknown);
    Fill(Stream_General, 0, "Genre", Genre);
    Fill(Stream_General, 0, "Comment", Comment);
    Fill(Stream_General, 0, "Track/Position", TrackPos);
}

//***************************************************************************
// C++
//***************************************************************************

} //NameSpace

#endif //MEDIAINFO_RIFF_YES

