// File_Mpeg4 - Info for MPEG-4 files
// Copyright (C) 2005-2008 Jerome Martinez, Zen@MediaArea.net
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
#ifdef MEDIAINFO_MPEG4_YES
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Multiple/File_Mpeg4.h"
#if defined(MEDIAINFO_AVC_YES)
    #include "MediaInfo/Video/File_Avc.h"
#endif
#if defined(MEDIAINFO_PCM_YES)
    #include "MediaInfo/Audio/File_Pcm.h"
#endif
#include <zlib.h>
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Const
//***************************************************************************

//---------------------------------------------------------------------------
const char* Mpeg4_Meta_Kind(int32u Kind)
{
    switch (Kind)
    {
        case 0x00 : return "Binary";
        case 0x01 : return "UTF8";
        case 0x02 : return "UTF16";
        case 0x03 : return "Mac String";
        case 0x0E : return "Jpeg";
        case 0x15 : return "Signed Integer"; //the size of the integer is derived from the container size
        case 0x16 : return "Float 32";
        case 0x17 : return "Float 64";
        default   : return "Unknown";
    }
}

namespace Elements
{
    const int64u free=0x66726565;
    const int64u ftyp=0x66747970;
    const int64u ftyp_qt=0x71742020;
    const int64u ftyp_isom=0x69736F6D;
    const int64u ftyp_caqv=0x63617176;
    const int64u idat=0x69646174;
    const int64u idsc=0x69647363;
    const int64u mdat=0x6D646174;
    const int64u moov=0x6D6F6F76;
    const int64u moov_cmov=0x636D6F76;
    const int64u moov_cmov_cmvd=0x636D7664;
    const int64u moov_cmov_dcom=0x64636F6D;
    const int64u moov_cmov_dcom_zlib=0x7A6C6962;
    const int64u moov_ctab=0x63746162;
    const int64u moov_iods=0x696F6473;
    const int64u moov_meta=0x6D657461;
    const int64u moov_meta______=0x2D2D2D2D;
    const int64u moov_meta___ART=0xA9415254;
    const int64u moov_meta___alb=0xA9616C62;
    const int64u moov_meta___aut=0xA9617574;
    const int64u moov_meta___cmt=0xA9636D74;
    const int64u moov_meta___cpy=0xA9637079;
    const int64u moov_meta___day=0xA9646179;
    const int64u moov_meta___des=0xA9646573;
    const int64u moov_meta___dir=0xA9646972;
    const int64u moov_meta___dis=0xA9646973;
    const int64u moov_meta___edl=0xA965646C;
    const int64u moov_meta___fmt=0xA9666D74;
    const int64u moov_meta___gen=0xA967656E;
    const int64u moov_meta___hos=0xA9686F73;
    const int64u moov_meta___inf=0xA9696E66;
    const int64u moov_meta___key=0xA96B6579;
    const int64u moov_meta___mak=0xA96D616B;
    const int64u moov_meta___mod=0xA96D6F64;
    const int64u moov_meta___nam=0xA96E616D;
    const int64u moov_meta___prd=0xA9707264;
    const int64u moov_meta___PRD=0xA9505244;
    const int64u moov_meta___prf=0xA9707266;
    const int64u moov_meta___req=0xA9726571;
    const int64u moov_meta___src=0xA9737263;
    const int64u moov_meta___swr=0xA9737772;
    const int64u moov_meta___too=0xA9746F6F;
    const int64u moov_meta___wrn=0xA977726E;
    const int64u moov_meta___wrt=0xA9777274;
    const int64u moov_meta__auth=0x61757468;
    const int64u moov_meta__cpil=0x6370696C;
    const int64u moov_meta__covr=0x636F7672;
    const int64u moov_meta__disk=0x6469736B;
    const int64u moov_meta__dscp=0x64736370;
    const int64u moov_meta__gnre=0x676E7265;
    const int64u moov_meta__name=0x6E616D65;
    const int64u moov_meta__perf=0x70657266;
    const int64u moov_meta__titl=0x7469746C;
    const int64u moov_meta__trkn=0x74726B6E;
    const int64u moov_meta__tmpo=0x746D706F;
    const int64u moov_meta_hdlr=0x68646C72;
    const int64u moov_meta_hdlr_mdir=0x6D646972;
    const int64u moov_meta_hdlr_mdta=0x6D647461;
    const int64u moov_meta_hdlr_mp7b=0x6D703762;
    const int64u moov_meta_hdlr_mp7t=0x6D703774;
    const int64u moov_meta_bxml=0x62786D6C;
    const int64u moov_meta_keys=0x6B657973;
    const int64u moov_meta_keys_mdta=0x6D647461;
    const int64u moov_meta_ilst=0x696C7374;
    const int64u moov_meta_ilst_xxxx_data=0x64617461;
    const int64u moov_meta_ilst_xxxx_mean=0x6D65616E;
    const int64u moov_meta_ilst_xxxx_name=0x6E616D65;
    const int64u moov_meta_xml=0x786D6C20;
    const int64u moov_mvhd=0x6D766864;
    const int64u moov_trak=0x7472616B;
    const int64u moov_trak_edts=0x65647473;
    const int64u moov_trak_edts_elst=0x656C7374;
    const int64u moov_trak_mdia=0x6D646961;
    const int64u moov_trak_mdia_hdlr=0x68646C72;
    const int64u moov_trak_mdia_hdlr_MPEG=0x4D504547;
    const int64u moov_trak_mdia_hdlr_soun=0x736F756E;
    const int64u moov_trak_mdia_hdlr_subp=0x73756270;
    const int64u moov_trak_mdia_hdlr_text=0x74657874;
    const int64u moov_trak_mdia_hdlr_vide=0x76696465;
    const int64u moov_trak_mdia_mdhd=0x6D646864;
    const int64u moov_trak_mdia_minf=0x6D696E66;
    const int64u moov_trak_mdia_minf_dinf=0x64696E66;
    const int64u moov_trak_mdia_minf_dinf_url =0x75726C20;
    const int64u moov_trak_mdia_minf_dinf_urn =0x75726E20;
    const int64u moov_trak_mdia_minf_dinf_dref=0x64726566;
    const int64u moov_trak_mdia_minf_dinf_dref_url =0x75726C20;
    const int64u moov_trak_mdia_minf_dinf_derf_urn =0x75726E20;
    const int64u moov_trak_mdia_minf_hint=0x68696E74;
    const int64u moov_trak_mdia_minf_hdlr=0x68646C72;
    const int64u moov_trak_mdia_minf_hmhd=0x686D6864;
    const int64u moov_trak_mdia_minf_nmhd=0x6E6D6864;
    const int64u moov_trak_mdia_minf_smhd=0x736D6864;
    const int64u moov_trak_mdia_minf_stbl=0x7374626C;
    const int64u moov_trak_mdia_minf_stbl_ctts=0x63747473;
    const int64u moov_trak_mdia_minf_stbl_stco=0x7374636F;
    const int64u moov_trak_mdia_minf_stbl_stdp=0x73746470;
    const int64u moov_trak_mdia_minf_stbl_stsc=0x73747363;
    const int64u moov_trak_mdia_minf_stbl_stsd=0x73747364;
    const int64u moov_trak_mdia_minf_stbl_stsd_alac=0x616C6163;
    const int64u moov_trak_mdia_minf_stbl_stsd_mp4a=0x6D703461;
    const int64u moov_trak_mdia_minf_stbl_stsd_mp4s=0x6D703473;
    const int64u moov_trak_mdia_minf_stbl_stsd_mp4v=0x6D703476;
    const int64u moov_trak_mdia_minf_stbl_stsd_xxxx_alac=0x616C6163;
    const int64u moov_trak_mdia_minf_stbl_stsd_xxxx_avcC=0x61766343;
    const int64u moov_trak_mdia_minf_stbl_stsd_xxxx_btrt=0x62747274;
    const int64u moov_trak_mdia_minf_stbl_stsd_xxxx_chan=0x6368616E;
    const int64u moov_trak_mdia_minf_stbl_stsd_xxxx_dac3=0x64616333;
    const int64u moov_trak_mdia_minf_stbl_stsd_xxxx_damr=0x64616D72;
    const int64u moov_trak_mdia_minf_stbl_stsd_xxxx_esds=0x65736473;
    const int64u moov_trak_mdia_minf_stbl_stsd_xxxx_wave=0x77617665;
    const int64u moov_trak_mdia_minf_stbl_stsd_xxxx_wave_frma=0x66726D61;
    const int64u moov_trak_mdia_minf_stbl_stsh=0x73747368;
    const int64u moov_trak_mdia_minf_stbl_stss=0x73747373;
    const int64u moov_trak_mdia_minf_stbl_stsz=0x7374737A;
    const int64u moov_trak_mdia_minf_stbl_stts=0x73747473;
    const int64u moov_trak_mdia_minf_vmhd=0x766D6864;
    const int64u moov_trak_tapt=0x74617074;
    const int64u moov_trak_tapt_clef=0x636C6566;
    const int64u moov_trak_tapt_prof=0x70726F66;
    const int64u moov_trak_tapt_enof=0x656E6F66;
    const int64u moov_trak_tkhd=0x746B6864;
    const int64u moov_trak_tref=0x74726566;
    const int64u moov_trak_tref_dpnd=0x64706E64;
    const int64u moov_trak_tref_ipir=0x69706972;
    const int64u moov_trak_tref_hint=0x68696E74;
    const int64u moov_trak_tref_mpod=0x6D706F64;
    const int64u moov_trak_tref_sync=0x73796E63;
    const int64u moov_trak_tref_tmcd=0x746D6364;
    const int64u moov_udta=0x75647461;
    const int64u moov_udta_AllF=0x416C6C46;
    const int64u moov_udta_chpl=0x6368706C;
    const int64u moov_udta_cprt=0x63707274;
    const int64u moov_udta_FIEL=0x4649454C;
    const int64u moov_udta_FXTC=0x46585443;
    const int64u moov_udta_hinf=0x68696E66;
    const int64u moov_udta_hinv=0x68696E76;
    const int64u moov_udta_hnti=0x686E7469;
    const int64u moov_udta_hnti_rtp=0x72747020;
    const int64u moov_udta_LOOP=0x4C4F4F50;
    const int64u moov_udta_MCPS=0x4D435053;
    const int64u moov_udta_meta=0x6D657461;
    const int64u moov_udta_meta_hdlr=0x68646C72;
    const int64u moov_udta_meta_ilst=0x696C7374;
    const int64u moov_udta_meta_ilst_xxxx_data=0x64617461;
    const int64u moov_udta_meta_ilst_xxxx_mean=0x6D65616E;
    const int64u moov_udta_meta_ilst_xxxx_name=0x6E616D65;
    const int64u moov_udta_nsav=0x74736176;
    const int64u moov_udta_ptv =0x70747620;
    const int64u moov_udta_Sel0=0x53656C30;
    const int64u moov_udta_WLOC=0x574C4F43;
    const int64u moov_udta_XMP_=0x584D505F;
    const int64u pckg=0x70636B67;
    const int64u pnot=0x706E6F74;
    const int64u skip=0x736B6970;
    const int64u wide=0x77696465;
}

//***************************************************************************
// Format
//***************************************************************************

//---------------------------------------------------------------------------
void File_Mpeg4::Data_Parse()
{
    //Parsing
    DATA_BEGIN
    LIST(free)
        ATOM_BEGIN
        ATOM_END
    ATOM(ftyp)
    ATOM(idat)
    ATOM(idsc)
    LIST(mdat)
        ATOM_BEGIN
        ATOM_END
    LIST(moov)
        ATOM_BEGIN
        LIST(moov_cmov)
            ATOM_BEGIN
            ATOM(moov_cmov_dcom)
            ATOM(moov_cmov_cmvd)
            ATOM_END
        ATOM(moov_ctab)
        ATOM(moov_iods)
        LIST(moov_meta)
            ATOM_BEGIN
            ATOM(moov_meta_hdlr)
            LIST(moov_meta_keys)
                ATOM_BEGIN
                ATOM(moov_meta_keys_mdta)
                ATOM_END
            LIST(moov_meta_ilst)
                ATOM_BEGIN
                LIST_DEFAULT (moov_meta_ilst_xxxx)
                    ATOM_BEGIN
                    ATOM (moov_meta_ilst_xxxx_data)
                    ATOM (moov_meta_ilst_xxxx_mean)
                    ATOM (moov_meta_ilst_xxxx_name)
                    ATOM_END
                ATOM_END_DEFAULT
            ATOM_END
        ATOM(moov_mvhd)
        LIST(moov_trak)
            ATOM_BEGIN
            LIST(moov_trak_edts)
                ATOM_BEGIN
                ATOM(moov_trak_edts_elst)
                ATOM_END
            LIST(moov_trak_mdia)
                ATOM_BEGIN
                ATOM(moov_trak_mdia_hdlr)
                ATOM(moov_trak_mdia_mdhd)
                LIST(moov_trak_mdia_minf)
                    ATOM_BEGIN
                    LIST(moov_trak_mdia_minf_dinf)
                        ATOM_BEGIN
                        ATOM(moov_trak_mdia_minf_dinf_url)
                        ATOM(moov_trak_mdia_minf_dinf_urn)
                        LIST(moov_trak_mdia_minf_dinf_dref)
                            ATOM_BEGIN
                            ATOM(moov_trak_mdia_minf_dinf_url)
                            ATOM(moov_trak_mdia_minf_dinf_urn)
                            ATOM_END
                        ATOM_END
                    ATOM(moov_trak_mdia_minf_hdlr)
                    ATOM(moov_trak_mdia_minf_hint)
                    ATOM(moov_trak_mdia_minf_hmhd)
                    ATOM(moov_trak_mdia_minf_nmhd)
                    ATOM(moov_trak_mdia_minf_smhd)
                    LIST(moov_trak_mdia_minf_stbl)
                        ATOM_BEGIN
                        ATOM(moov_trak_mdia_minf_stbl_ctts)
                        ATOM(moov_trak_mdia_minf_stbl_stco)
                        ATOM(moov_trak_mdia_minf_stbl_stdp)
                        ATOM(moov_trak_mdia_minf_stbl_stsc)
                        LIST(moov_trak_mdia_minf_stbl_stsd)
                            ATOM_BEGIN
                            LIST_DEFAULT(moov_trak_mdia_minf_stbl_stsd_xxxx)
                                ATOM_BEGIN
                                ATOM(moov_trak_mdia_minf_stbl_stsd_xxxx_alac)
                                ATOM(moov_trak_mdia_minf_stbl_stsd_xxxx_avcC)
                                ATOM(moov_trak_mdia_minf_stbl_stsd_xxxx_btrt)
                                ATOM(moov_trak_mdia_minf_stbl_stsd_xxxx_chan)
                                ATOM(moov_trak_mdia_minf_stbl_stsd_xxxx_dac3)
                                ATOM(moov_trak_mdia_minf_stbl_stsd_xxxx_damr)
                                ATOM(moov_trak_mdia_minf_stbl_stsd_xxxx_esds)
                                LIST(moov_trak_mdia_minf_stbl_stsd_xxxx_wave)
                                    ATOM_BEGIN
                                    ATOM(moov_trak_mdia_minf_stbl_stsd_xxxx_esds)
                                    ATOM(moov_trak_mdia_minf_stbl_stsd_xxxx_wave_frma)
                                    ATOM_DEFAULT(moov_trak_mdia_minf_stbl_stsd_xxxx_wave_xxxx)
                                    ATOM_END_DEFAULT
                                ATOM_END
                            ATOM_END_DEFAULT
                        ATOM(moov_trak_mdia_minf_stbl_stsh)
                        ATOM(moov_trak_mdia_minf_stbl_stss)
                        ATOM(moov_trak_mdia_minf_stbl_stsz)
                        ATOM(moov_trak_mdia_minf_stbl_stts)
                        ATOM_END
                    ATOM(moov_trak_mdia_minf_vmhd)
                    ATOM_END
                ATOM_END
            LIST(moov_trak_tapt)
                ATOM_BEGIN
                ATOM(moov_trak_tapt_clef)
                ATOM(moov_trak_tapt_prof)
                ATOM(moov_trak_tapt_enof)
                ATOM_END
            ATOM(moov_trak_tkhd)
            LIST(moov_trak_tref)
                ATOM_BEGIN
                ATOM(moov_trak_tref_dpnd)
                ATOM(moov_trak_tref_ipir)
                ATOM(moov_trak_tref_hint)
                ATOM(moov_trak_tref_mpod)
                ATOM(moov_trak_tref_sync)
                ATOM(moov_trak_tref_tmcd)
                ATOM_END
            ATOM_END
        LIST(moov_udta)
            ATOM_BEGIN
            ATOM(moov_udta_AllF)
            ATOM(moov_udta_chpl)
            ATOM(moov_udta_cprt)
            ATOM(moov_udta_FIEL)
            ATOM(moov_udta_FXTC)
            ATOM(moov_udta_hinf)
            ATOM(moov_udta_hinv)
            LIST(moov_udta_hnti)
                ATOM_BEGIN
                ATOM(moov_udta_hnti_rtp)
                ATOM_END
            ATOM(moov_udta_LOOP)
            ATOM(moov_udta_MCPS)
            LIST(moov_udta_meta)
                ATOM_BEGIN
                ATOM(moov_udta_meta_hdlr)
                LIST(moov_udta_meta_ilst)
                    ATOM_BEGIN
                    LIST_DEFAULT (moov_udta_meta_ilst_xxxx);
                        ATOM_BEGIN
                        ATOM (moov_udta_meta_ilst_xxxx_data);
                        ATOM (moov_udta_meta_ilst_xxxx_mean);
                        ATOM (moov_udta_meta_ilst_xxxx_name);
                        ATOM_END
                    ATOM_END_DEFAULT
                ATOM_END
            ATOM(moov_udta_nsav)
            ATOM(moov_udta_ptv )
            ATOM(moov_udta_Sel0)
            ATOM(moov_udta_WLOC)
            ATOM(moov_udta_XMP_)
            ATOM_DEFAULT (moov_udta_xxxx); //User data
            ATOM_END_DEFAULT
        ATOM_END
    ATOM(pckg)
    ATOM(pnot)
    ATOM(skip)
    ATOM(wide)
    DATA_END
}

//***************************************************************************
// Elements
//***************************************************************************

#define NAME_VERSION_FLAG(ELEMENT_NAME) \
    Element_Name(ELEMENT_NAME); \
    int32u Flags; \
    int8u Version; \
    { \
        Get_B1(Version,                                         "Version"); \
        Get_B3(Flags,                                           "Flags"); \
    } \

#define INTEGRITY_VERSION(_VERSION) \
    if (Version>_VERSION) \
    { \
        Skip_XX(Element_Size-Element_Offset,                    "Unknown data"); \
        return; \
    } \

#define INTEGRITY(TOVALIDATE, ERRORTEXT) \
    if (!(TOVALIDATE)) \
    { \
        Trusted_IsNot(ERRORTEXT); \
        return; \
    } \

#define INTEGRITY_SIZE1(ELEMENT_SIZE0) \
    INTEGRITY_VERSION(0); \
    if (Element_Size!=ELEMENT_SIZE0+4) \
    { \
        Trusted_IsNot("Size is wrong"); \
        return; \
    } \

#define INTEGRITY_SIZE2(ELEMENT_SIZE0, ELEMENT_SIZE1) \
    INTEGRITY_VERSION(1); \
    if (Version==0 && Element_Size!=ELEMENT_SIZE0 \
     || Version==1 && Element_Size!=ELEMENT_SIZE1) \
    { \
        Trusted_IsNot("Size is wrong"); \
        return; \
    } \

#define INTEGRITY_SIZE_ATLEAST1(ELEMENT_SIZE0) \
    INTEGRITY_VERSION(0); \
    if (Version==0 && Element_Size<ELEMENT_SIZE0) \
    { \
        Trusted_IsNot("Size is wrong"); \
        return; \
    } \

#define INTEGRITY_SIZE_ATLEAST2(ELEMENT_SIZE0, ELEMENT_SIZE1) \
    INTEGRITY_VERSION(1); \
    if (Version==0 && Element_Size<ELEMENT_SIZE0 \
     || Version==1 && Element_Size<ELEMENT_SIZE1) \
    { \
        Trusted_IsNot("Size is wrong"); \
        return; \
    } \

#define Get_B_DEPENDOFVERSION(_INFO, _NAME) \
    { \
        if (Version==0) \
        { \
            int32u Info; \
            Get_B4(Info,                                        _NAME); \
            _INFO=Info; \
        } \
        else \
            Get_B8(_INFO,                                       _NAME); \
    } \

#define Get_DATE1904_DEPENDOFVERSION(_INFO, _NAME) \
    { \
        if (Version==0) \
        { \
            int32u Temp; \
            Get_B4(Temp,                                        _NAME); \
            _INFO.Date_From_Seconds_1904(Temp); \
        } \
        else \
        { \
            int64u Temp; \
            Get_B8(Temp,                                        _NAME); \
            _INFO.Date_From_Seconds_1904(Temp); \
        } \
        Param_Info(_INFO); \
    } \

//---------------------------------------------------------------------------
void File_Mpeg4::free()
{
    Element_Name("Free space");

    //Parsing
    Skip_XX(Element_TotalSize_Get(),                            "Free");
}

//---------------------------------------------------------------------------
void File_Mpeg4::ftyp()
{
    Element_Name("File Type");

    //Parsing
    int32u MajorBrand;
    Get_C4 (MajorBrand,                                         "MajorBrand");
    Skip_B4(                                                    "MajorBrandVersion");
    while (Element_Offset<Element_Size)
    {
        int32u CompatibleBrand;
        Get_C4 (CompatibleBrand,                                "CompatibleBrand");

        //Filling
        switch (CompatibleBrand)
        {
            case Elements::ftyp_caqv : Fill("Encoded_Application", "Casio Digital Camera"); break;
            default : ;
        }
    }

    FILLING_BEGIN();
        Stream_Prepare(Stream_General);
        Fill("Format", Ztring().From_CC4(MajorBrand));
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::idat()
{
    Element_Name("QTI");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");

    FILLING_BEGIN();
        Stream_Prepare(Stream_General);
        Fill("Format", "QTI");
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::idsc()
{
    Element_Name("QTI");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");

    FILLING_BEGIN();
        Stream_Prepare(Stream_General);
        Fill("Format", "QTI");
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::mdat()
{
    Element_Name("Data");

    //Parsing
    Skip_XX(Element_TotalSize_Get(),                            "Data");
    
    /*
    //Filling
    if (Count_Get(Stream_General)==0)
    {
        Stream_Prepare(Stream_General);
        Fill("Format", "QT"); //if there is no ftyp atom, this is an old Quictime file
    }

    //Parse mdat if needed
    if (moov_trak_mdia_minf_stbl_stco_ID.size()>0)
    {
        //Currently, we can only parse one chunk in one stream (for MPEG-PS in MOV), must be improved
        if (moov_trak_mdia_minf_stbl_stco_ID.size()==1 && moov_trak_mdia_minf_stbl_stco_Map[moov_trak_mdia_minf_stbl_stco_ID[0]]->size()==1)
        {
            mdat_MustParse=true;
            mdat_Parse();
            return;
        }
    }
    */
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov()
{
    Element_Name("File header");

    FILLING_BEGIN();
        if (Count_Get(Stream_General)==0)
        {
            Stream_Prepare(Stream_General);
            Fill("Format", "QT"); //If there is no ftyp atom, this is an old Quictime file
        }
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_cmov()
{
    Element_Name("Compressed file header");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_cmov_cmvd()
{
    Element_Name("Data");

    switch (moov_cmov_dcom_Compressor)
    {
        case Elements::moov_cmov_dcom_zlib : moov_cmov_cmvd_zlib(); break;
        default: Skip_XX(Element_Size,                          "Data");
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_cmov_cmvd_zlib()
{
    Element_Name("Zlib");

    //Parsing
    int32u Dest_Size32;
    Get_B4(Dest_Size32,                                         "Destination size");

    FILLING_BEGIN();
        //Sizes
        unsigned long Source_Size=(unsigned long)(Element_Size-Element_Offset);
        unsigned long Dest_Size=Dest_Size32;

        //Uncompressing
        int8u* Dest=new int8u[Dest_Size];
		if (uncompress((Bytef*)Dest, &Dest_Size, (const Bytef*)Buffer+Buffer_Offset+4, Source_Size)<0)
		{
            delete Dest; //Dest=NULL;
            return;
        }
        File_Mpeg4 MI;
        Open_Buffer_Init(&MI, File_Size, File_Offset+Buffer_Offset+4);
        Open_Buffer_Continue(&MI, Dest, Dest_Size);
        Open_Buffer_Finalize(&MI);
        Merge(MI);
        Merge(MI, Stream_General, 0, 0);
        delete Dest; //Dest=NULL;
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_ctab()
{
    Element_Name("Color Table");

    //Parsing
    int16u Size;
    Skip_B4(                                                    "Color table seed");
    Skip_B2(                                                    "Color table flags");
    Get_B2 (Size,                                               "Color table size");
    for (int16u Pos=0; Pos<=Size; Pos++)
    {
        Skip_B2(                                                "Zero");
        Skip_B2(                                                "Red");
        Skip_B2(                                                "Green");
        Skip_B2(                                                "Blue");
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_cmov_dcom()
{
    Element_Name("Data compressor name");

    //Parsing
    Get_C4 (moov_cmov_dcom_Compressor,                          "Value");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_iods()
{
    NAME_VERSION_FLAG("Initial object descriptor");
    INTEGRITY_VERSION(0);

    FILLING_BEGIN();
        Descriptors();
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_meta()
{
    NAME_VERSION_FLAG("Metadatas");
    INTEGRITY_VERSION(0);

    //Filling
    moov_meta_hdlr_Type=0;
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_meta_bxml()
{
    NAME_VERSION_FLAG("Binary XML"); //ISO/IEC 14496-12
    INTEGRITY(moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mp7b, "Bad meta type");

    //Parsing
    Skip_XX(Element_Size-Element_Offset,                        "Binary XML dump");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_meta_hdlr()
{
    NAME_VERSION_FLAG("Metadata Header"); //ISO/IEC 14496-12 handler

    //Parsing
    Skip_C4(                                                    "Type (Quicktime)"); //Filled if Quicktime
    Get_C4 (moov_meta_hdlr_Type,                                "Metadata type");
    Skip_C4(                                                    "Manufacturer");
    Skip_B4(                                                    "Component reserved flags"); //Filled if Quicktime
    Skip_B4(                                                    "Component reserved flags mask"); //Filled if Quicktime
    Skip_Local(Element_Size-Element_Offset,                     "Component type name");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_meta_keys()
{
    NAME_VERSION_FLAG("Keys");
    INTEGRITY(moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mdta, "Bad meta type");

    //Parsing
    Skip_B4(                                                    "Count");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_meta_keys_mdta()
{
    Element_Name("Name");
    INTEGRITY(moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mdta, "Bad meta type");

    //Parsing
    std::string Value;
    Get_String(Element_Size, Value,                             "Value");

    //Filling
    moov_udta_meta_keys_List.push_back(Value);
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_meta_ilst()
{
    Element_Name("List");
    INTEGRITY(moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mdta || moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mdir, "Bad meta type");

    //Filling
    moov_udta_meta_keys_ilst_Pos=0;
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_meta_ilst_xxxx()
{
    Element_Name("Element");
    INTEGRITY(moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mdta || moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mdir, "Bad meta type");

    //Filling
    moov_meta_ilst_xxxx_name_Name.clear(); //useful if metadata type = "mdir"
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_meta_ilst_xxxx_data()
{
    Element_Name("Data");
    INTEGRITY(moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mdta || moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mdir, "Bad meta type");

    //Parsing
    int32u Kind, Language;
    Ztring Value;
    Get_B4(Kind,                                                  "Kind"); Param_Info(Mpeg4_Meta_Kind(Kind));
    Get_B4(Language,                                              "Language");
    switch (Kind)
    {
        case 0x00 : //Binary
                    switch (Element_Code_Get(Element_Level-1))
                    {
                        case Elements::moov_meta__disk :
                            {
                            //Parsing
                            int16u Position, Total;
                            Skip_B2(                            "Reserved");
                            Get_B2(Position,                    "Position");
                            Get_B2(Total,                       "Total");
                            if (Element_Offset+2<=Element_Size)
                                Skip_B2(                        "Reserved"); //Sometimes there are 2 more bytes, unknown

                            //Filling
                            Fill(Stream_General, 0, "Part/Position", Position, 10, true);
                            Fill(Stream_General, 0, "Part/Position_Total", Total, 10, true);
                            }
                            return;
                        case Elements::moov_meta__trkn :
                            {
                            //Parsing
                            int16u Position, Total;
                            Skip_B2(                            "Reserved");
                            Get_B2(Position,                    "Position");
                            Get_B2(Total,                       "Total");
                            if (Element_Offset+2<=Element_Size)
                                Skip_B2(                        "Reserved"); //Sometimes there are 2 more bytes, unknown

                            //Filling
                            Fill(Stream_General, 0, "Track/Position", Position, 10, true);
                            Fill(Stream_General, 0, "Track/Position_Total", Total, 10, true);
                            }
                            return;
                        case Elements::moov_meta__covr :
                            {
                            Skip_XX(Element_Size-Element_Offset,"Data");

                            //Filling
                            Fill(Stream_General, 0, "Cover", "Yes");
                            }
                            return;
                        default:
                            Value=_T("(Binary)");
                    }
                    break;
        case 0x01 : //UTF-8
                    switch (Element_Code_Get(Element_Level-1))
                    {
                        case Elements::moov_meta___day :
                            {
                            std::string ValueS;
                            Get_String(Element_Size-Element_Offset, ValueS, "Value");
                            Value.Date_From_String(ValueS.c_str(), ValueS.size());
                            }
                            break;
                        default:
                            Get_UTF8(Element_Size-Element_Offset, Value, "Value");
                    }
                     break;
        case 0x02 : //UTF-16
                    Value=_T("UTF-16 encoding not yet supported");
                    break;
        case 0x03 : //Mac String
                    Value=_T("String(Mac) encoding not yet supported");
                    break;
        case 0x0E : //JPEG
                    Value=_T("(Image)");
                    break;
        case 0x15 : //Signed Integer
                    {
                    switch (Element_Size-Element_Offset)
                    {
                        case 1 : {int8u  ValueI; Get_B1(ValueI, "Value"); Value.From_Number((int8s) ValueI);}; break;
                        case 2 : {int16u ValueI; Get_B2(ValueI, "Value"); Value.From_Number((int16s)ValueI);}; break;
                        case 4 : {int32u ValueI; Get_B4(ValueI, "Value"); Value.From_Number((int32s)ValueI);}; break;
                        case 8 : {int64u ValueI; Get_B8(ValueI, "Value"); Value.From_Number((int64s)ValueI);}; break;
                        default  : Value=_T("Unknown kind of integer value!");
                    }
                    }
                    break;
        case 0x16 : //Float 32
                    Value=_T("Float32 encoding not yet supported");
                    break;
        case 0x17 : //Float 64
                    Value=_T("Float64 encoding not yet supported");
                    break;
        default: Value=_T("Unknown kind of value!");
   }

   FILLING_BEGIN();
        switch (moov_meta_hdlr_Type)
        {
            case Elements::moov_meta_hdlr_mdir :
                {
                    std::string Parameter;
                    if (Element_Code_Get(Element_Level-1)==Elements::moov_meta______)
                        Metadata_Get(Parameter, moov_meta_ilst_xxxx_name_Name);
                    else
                        Metadata_Get(Parameter, Element_Code_Get(Element_Level-1));
                    if (!Parameter.empty())
                        Fill(Stream_General, 0, Parameter.c_str(), Value, true);
                }
                break;
            case Elements::moov_meta_hdlr_mdta :
                INTEGRITY(moov_udta_meta_keys_ilst_Pos<moov_udta_meta_keys_List.size(), "Keys atom is not enough large!");
                {
                    std::string Parameter;
                    Metadata_Get(Parameter, moov_udta_meta_keys_List[moov_udta_meta_keys_ilst_Pos]);
                    if (!Parameter.empty())
                        Fill(Stream_General, 0, Parameter.c_str(), Value, true);
                    moov_udta_meta_keys_ilst_Pos++;
                }
            default: ;
        }
   FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_meta_ilst_xxxx_mean()
{
    Element_Name("Mean");
    INTEGRITY(moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mdir, "Bad meta type");

    //Parsing
    Skip_B4(                                                    "Unknown");
    Skip_Local(Element_Size-Element_Offset,                     "Value");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_meta_ilst_xxxx_name()
{
    Element_Name("Name");
    INTEGRITY(moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mdir, "Bad meta type");

    //Parsing
    Skip_B4(                                                    "Unknown");
    Get_String(Element_Size-Element_Offset, moov_meta_ilst_xxxx_name_Name, "Value");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_meta_xml()
{
    NAME_VERSION_FLAG("XML"); //ISO/IEC 14496-12
    INTEGRITY(moov_meta_hdlr_Type==Elements::moov_meta_hdlr_mp7t, "Bad meta type");

    //Parsing
    Skip_XX(Element_Size-Element_Offset,                        "XML dump");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_mvhd()
{
    NAME_VERSION_FLAG("Movie header");

    //Parsing
    Ztring Date_Created, Date_Modified;
    int64u Duration;
    int32u TimeScale, Rate;
    int16u Volume;
    Get_DATE1904_DEPENDOFVERSION(Date_Created,                  "Creation time");
    Get_DATE1904_DEPENDOFVERSION(Date_Modified,                 "Modification time");
    Get_B4(TimeScale,                                           "Time scale"); Param_Info(Ztring::ToZtring(TimeScale)+_T(" Hz"));
    Get_B_DEPENDOFVERSION(Duration,                             "Duration"); Param_Info(Ztring::ToZtring(Duration*1000/TimeScale)+_T(" ms"));
    Get_B4 (Rate,                                               "Preferred rate"); Param_Info(Ztring::ToZtring(((float32)Rate)/0x10000));
    Get_B2 (Volume,                                             "Preferred volume"); Param_Info(Ztring::ToZtring(((float32)Volume)/0x100));
    Skip_XX(10,                                                 "Reserved");
    Skip_XX(36,                                                 "Matrix structure");
    Skip_B4(                                                    "Preview time");
    Skip_B4(                                                    "Preview duration");
    Skip_B4(                                                    "Poster time");
    Skip_B4(                                                    "Selection time");
    Skip_B4(                                                    "Selection duration");
    Skip_B4(                                                    "Current time");
    Skip_B4(                                                    "Next track ID");

    FILLING_BEGIN();
        if (TimeScale)
        {
            //int32u PlayTime=(int32u)(((float)Duration)/TimeScale*1000);
            //Fill("PlayTime", PlayTime);
        }
        Fill("Encoded_Date", Date_Created);
        Fill("Tagged_Date", Date_Modified);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak()
{
    Element_Name("Track");

    FILLING_BEGIN();
        Fill_Flush();
        moov_trak_tkhd_TrackID=(int32u)-1;
        moov_trak_mdia_minf_stbl_stco_Parse=true;//false;
        Stream_Prepare(Stream_Max); //clear filling
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_edts()
{
    Element_Name("Edit");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_edts_elst()
{
    NAME_VERSION_FLAG("Edit List");

    //Parsing
    int32u Count;
    Get_B4 (Count,                                              "Number of entries");
    for (int32u Pos=0; Pos<Count; Pos++)
    {
        Element_Begin("Entry", 12);
        Skip_B4(                                                "Track duration");
        Skip_B4(                                                "Media time");
        Info_B4(MediaRate,                                      "Media rate"); Param_Info(((float)MediaRate)/0x10000);
        Element_End();
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia()
{
    Element_Name("Media");

    FILLING_BEGIN();
        moov_trak_mdia_mdhd_PlayTime=0;
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_hdlr()
{
    NAME_VERSION_FLAG("Handler Reference");

    //Parsing
    Ztring Manufacturer, Title;
    int32u SubType;
    int8u Size;
    Skip_C4(                                                    "Component type");
    Get_C4 (SubType,                                            "Component subtype");
    Skip_C4(                                                    "Component manufacturer");
    Skip_B4(                                                    "Component flags");
    Skip_B4(                                                    "Component flags mask");
    Peek_B1(Size);
    if (Element_Offset+1+Size==Element_Size)
    {
        Skip_B1(                                                "Component name size");
        Get_Local(Size, Title,                                  "Component name");
    }
    else
    {
        std::string TitleS;
        Get_String(Element_Size-Element_Offset, TitleS,         "Component name");
        Title.From_UTF8(TitleS.c_str());
        if (Title.empty())
            Title.From_Local(TitleS.c_str()); //Trying Local...
    }
    if (Title.find(_T("Handler"))!=std::string::npos || Title.find(_T("vide"))!=std::string::npos || Title.find(_T("soun"))!=std::string::npos)
        Title.clear(); //This is not a Title

    FILLING_BEGIN();
        if (!Title.empty()) Fill("Title",    Title);
        switch (SubType)
        {
            case Elements::moov_trak_mdia_hdlr_soun :
                if (StreamKind_Last!=Stream_Audio)
                {
                    Stream_Prepare(Stream_Audio);
                }
                break;
            case Elements::moov_trak_mdia_hdlr_vide :
                if (StreamKind_Last!=Stream_Video)
                {
                    Stream_Prepare(Stream_Video);
                }
                break;
            case Elements::moov_trak_mdia_hdlr_text :
                if (StreamKind_Last!=Stream_Text)
                {
                    Stream_Prepare(Stream_Text);
                    Fill("Codec", "tx3g");
                }
                break;
            case Elements::moov_trak_mdia_hdlr_subp :
                if (StreamKind_Last!=Stream_Text)
                {
                    Stream_Prepare(Stream_Text);
                    Fill("Codec", "subp");
                }
                break;
            case Elements::moov_trak_mdia_hdlr_MPEG :
                moov_trak_mdia_minf_stbl_stco_Parse=true; //Data is in MDAT
                break;
            default: ;
        }
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_mdhd()
{
    NAME_VERSION_FLAG("Media Header");

    //Parsing
    Ztring Date_Created, Date_Modified;
    int64u Duration;
    int16u Language;
    Get_DATE1904_DEPENDOFVERSION(Date_Created,                  "Creation time");
    Get_DATE1904_DEPENDOFVERSION(Date_Modified,                 "Modification time");
    Get_B4(moov_trak_mdia_mdhd_TimeScale,                       "Time scale");
    Get_B_DEPENDOFVERSION(Duration,                             "Duration");
    Get_B2 (Language,                                           "Language"); Param_Info(Language_Get(Language));
    Skip_B2(                                                    "Quality");

    FILLING_BEGIN();
        Fill("Language", Language_Get(Language));
        if (moov_trak_mdia_mdhd_TimeScale)
        {
            moov_trak_mdia_mdhd_PlayTime=(int32u)(((float)Duration)/moov_trak_mdia_mdhd_TimeScale*1000);
            Fill("PlayTime", moov_trak_mdia_mdhd_PlayTime);
        }
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf()
{
    Element_Name("Media Information");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_dinf()
{
    Element_Name("Data Information");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_dinf_url()
{
    NAME_VERSION_FLAG("Data Location");

    //Parsing
    Skip_Local(Element_Size-Element_Offset,                     "location");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_dinf_urn()
{
    NAME_VERSION_FLAG("Data Naem");

    //Parsing
    Skip_Local(Element_Size-Element_Offset,                     "name TODO location after null string");
    //Skip_Local(Element_Size,                                    location);
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_dinf_dref()
{
    NAME_VERSION_FLAG("Data Reference");

    //Parsing
    Skip_B4(                                                    "entry_count");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_hint()
{
    NAME_VERSION_FLAG("Hint");

    //Parsing
    Skip_B2(                                                    "Maximum packet delivery unit");
    Skip_B2(                                                    "Average packet delivery unit");
    Skip_B4(                                                    "Maximum bit rate");
    Skip_B4(                                                    "Average bit rate");
    Skip_B4(                                                    "Reserved");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_hdlr()
{
    moov_trak_mdia_hdlr();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_hmhd()
{
    NAME_VERSION_FLAG("Hint Media Header");

    //Parsing
    Skip_B2(                                                    "maxPDUsize");
    Skip_B2(                                                    "avgPDUsize");
    Skip_B4(                                                    "maxbitrate");
    Skip_B4(                                                    "avgbitrate");
    Skip_B4(                                                    "reserved");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_nmhd()
{
    NAME_VERSION_FLAG("Null Media Header");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_smhd()
{
    NAME_VERSION_FLAG("Sound Media Header");

    //Parsing
    Skip_B2(                                                    "Audio balance");
    Skip_B2(                                                    "Reserved");

    FILLING_BEGIN();
        if (StreamKind_Last!=Stream_Audio)
            Stream_Prepare(Stream_Audio);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_vmhd()
{
    NAME_VERSION_FLAG("Video Media Header")

    //Parsing
    Skip_B2(                                                    "Graphic mode");
    Skip_B2(                                                    "Graphic mode color R");
    Skip_B2(                                                    "Graphic mode color G");
    Skip_B2(                                                    "Graphic mode color B");

    FILLING_BEGIN();
        if (StreamKind_Last!=Stream_Video)
            Stream_Prepare(Stream_Video);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl()
{
    Element_Name("Sample Table");

    FILLING_BEGIN();
        Buffer_MaximumSize=16*1024*1024; //If we are here, this is really a MPEG-4 file, and some atoms are very bigs...
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_ctts()
{
    Element_Name("Composition Time To Sample");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stco()
{
    NAME_VERSION_FLAG("Chunk offset");

    int32u Count;
    Get_B4 (Count,                                              "Number of entries");
    if (moov_trak_mdia_minf_stbl_stco_Parse)
    {
        moov_trak_mdia_minf_stbl_stco_ID.push_back(moov_trak_tkhd_TrackID);
        if (moov_trak_mdia_minf_stbl_stco_Map[moov_trak_tkhd_TrackID]==NULL)
            moov_trak_mdia_minf_stbl_stco_Map[moov_trak_tkhd_TrackID]=new std::vector<int64u>;
        int32u Offset;
        for (int32u Pos=0; Pos<Count; Pos++)
        {
            //Too much slow
            /*
            Get_B4 (Offset,                                     "Offset");
            */

            //Faster
            if (Element_Offset+4>Element_Size)
                break; //Problem
            Offset=BigEndian2int32u(Buffer+Buffer_Offset+Element_Offset);
            Element_Offset+=4;

            moov_trak_mdia_minf_stbl_stco_Map[moov_trak_tkhd_TrackID]->push_back(Offset);
            mdat_Pos[Offset].StreamKind=StreamKind_Last;
            mdat_Pos[Offset].StreamPos=StreamPos_Last;
        }
    }
    else
        Skip_XX(Count,                                          "Offsets");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stdp()
{
    Element_Name("Degradation Priority");

    //Parsing
    int32u sample_count;
    Get_B4 (sample_count,                                       "sample-count");

    for (int32u Pos=0; Pos<sample_count; Pos++)
    {
        Skip_B2(                                                "priority");
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsc()
{
    Element_Name("Sample To Chunk");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd()
{
    NAME_VERSION_FLAG("Sample Description");

    //Parsing
    Skip_B4(                                                    "Count");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxx()
{
    switch (StreamKind_Last)
    {
        case Stream_Audio : moov_trak_mdia_minf_stbl_stsd_xxxxSound(); break;
        case Stream_Video : moov_trak_mdia_minf_stbl_stsd_xxxxVideo(); break;
        default : ;
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxxSound()
{
    Element_Name("Audio");

    int16u Version, Channels, SampleSize, ID, SampleRate;
    Skip_B4(                                                    "Reserved");
    Skip_B2(                                                    "Reserved");
    Skip_B2(                                                    "Data reference index");
    Get_B2 (Version,                                            "Version");
    Skip_B2(                                                    "Revision level");
    Skip_B4(                                                    "Vendor");
    Get_B2 (Channels,                                           "Number of channels");
    Get_B2 (SampleSize,                                         "Sample size");
    Get_B2 (ID,                                                 "Compression ID");
    Skip_B2(                                                    "Packet size");
    Get_B2 (SampleRate,                                         "Sample rate"); Param_Info(SampleRate, " Hz");
    Skip_B2(                                                    "Reserved");
    if (Version>=1)
    {
        Skip_B4(                                                "Samples per packet");
        Skip_B4(                                                "Bytes per packet");
        Skip_B4(                                                "Bytes per frame");
        Skip_B4(                                                "Bytes per sample");
        if (Version>=2)
        {
            Skip_B4(                                            "Unknown");
            Skip_B4(                                            "Unknown");
            Skip_B4(                                            "Unknown");
            Skip_B4(                                            "Unknown");
            Skip_B4(                                            "Unknown");
        }
    }

    FILLING_BEGIN();
        //samr bug viewed in one file: codec=AMR-NB but Sampling rate is 1000, impossible
        if (Element_Code==0x73616D72 && SampleRate==1000) //Element_Code="samr"
            SampleRate=8000;

        std::string Codec;
        Codec.append(1, (char)((Element_Code&0xFF000000)>>24));
        Codec.append(1, (char)((Element_Code&0x00FF0000)>>16));
        if (Codec!="ms") //Normal
        {
            Codec.append(1, (char)((Element_Code&0x0000FF00)>> 8));
            Codec.append(1, (char)((Element_Code&0x000000FF)>> 0));
            if (Codec!="raw ")
                Fill("Codec", Codec, false, true);
            else
                Fill("Codec", "PCM", Error, false, true);
            Fill("Codec/CC", Codec, false, true);
            if (Codec=="drms")
                Fill("Encryption", "iTunes");
            if (Codec=="enca")
                Fill("Encryption", "Encrypted");
        }
        else //Microsoft 2CC
        {
            int64u CodecI= ((Element_Code&0x0000FF00ULL)>> 8)
                         + ((Element_Code&0x000000FFULL)>> 0); //FormatTag
            Codec=Ztring().From_Number(CodecI, 16).To_Local();
            Fill("Codec", Codec, true);
            Fill("Codec/CC", Codec, true);
        }
        #if defined(MEDIAINFO_MPEG4V_YES)
        if (Codec=="raw "
         || Config.Codec_Get(Ztring().From_Local(Codec.c_str()), InfoCodec_KindofCodec).find(_T("PCM"))==0
         || Config.Codec_Get(Ztring().From_Local(Codec.c_str()), InfoCodec_KindofCodec).find(_T("ADPCM"))==0)
        {
            //Creating the parser
            File__Analyze* MI=new File_Pcm;
            ((File_Pcm*)MI)->Codec=Ztring().From_Local(Codec.c_str());

            //Parsing
            Open_Buffer_Finalize(MI);

            //Filling
            Merge(*MI, StreamKind_Last, 0, StreamPos_Last);
            delete MI; //MI=NULL;
        }
        #endif
        Fill("Channel(s)", Channels, 10, true);
        if (SampleSize!=0)
            Fill("Resolution", SampleSize, 10, true);
        Fill("SamplingRate", SampleRate);

        //Sometimes, more Atoms in this atoms
        if (Element_Offset+8<Element_Size)
            Element_ThisIsAList();
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxxVideo()
{
    Element_Name("Video");

    int16u Width, Height, ColorTableID;
    int8u  CompressorName_Size;
    Skip_B4(                                                    "Reserved");
    Skip_B2(                                                    "Reserved");
    Skip_B2(                                                    "Data reference index");
    Skip_B2(                                                    "Version");
    Skip_B2(                                                    "Revision level");
    Skip_B4(                                                    "Vendor");
    Skip_B4(                                                    "Temporal quality");
    Skip_B4(                                                    "Spatial quality");
    Get_B2 (Width,                                              "Width");
    Get_B2 (Height,                                             "Height");
    Skip_B4(                                                    "Horizontal resolution");
    Skip_B4(                                                    "Vertical resolution");
    Skip_B4(                                                    "Data size");
    Skip_B2(                                                    "Frame count");
    Get_B1 (CompressorName_Size,                                "Compressor name size");
    Skip_Local(CompressorName_Size,                             "Compressor name");
    Element_Offset+=32-1-CompressorName_Size;
    Skip_B2(                                                    "Depth");
    Get_B2 (ColorTableID,                                       "Color table ID");
    if (ColorTableID==0)
        Skip_XX(32,                                             "Color Table");

    FILLING_BEGIN();
        std::string Codec;
        Codec.append(1, (char)((Element_Code&0xFF000000)>>24));
        Codec.append(1, (char)((Element_Code&0x00FF0000)>>16));
        Codec.append(1, (char)((Element_Code&0x0000FF00)>> 8));
        Codec.append(1, (char)((Element_Code&0x000000FF)>> 0));
        Fill("Codec", Codec, false, true);
        Fill("Codec/CC", Codec, false, true);
        if (Codec=="drms")
            Fill("Encryption", "iTunes");
        if (Codec=="enca")
            Fill("Encryption", "Encrypted");
        Fill("Width", BigEndian2int16u(Buffer+Buffer_Offset+24), 10, true);
        Fill("Height", BigEndian2int16u(Buffer+Buffer_Offset+26), 10, true);

        //Specific
        if (Codec=="dvc " || Codec=="DVC " || Codec=="dvcp" || Codec=="DVCP" || Codec=="dvpn" || Codec=="DVPN" || Codec=="dvpp" || Codec=="DVPP")
        {
            Fill("DisplayAspectRatio", ((float)4)/3, 3, true);
        }

        //Descriptors or a list (we can see both!)
        if (Element_Offset+8<=Element_Size
             && CC1(Buffer+Buffer_Offset+Element_Offset+4+0)>='A' && CC1(Buffer+Buffer_Offset+Element_Offset+4+0)<='z'
             && CC1(Buffer+Buffer_Offset+Element_Offset+4+1)>='A' && CC1(Buffer+Buffer_Offset+Element_Offset+4+1)<='z'
             && CC1(Buffer+Buffer_Offset+Element_Offset+4+2)>='A' && CC1(Buffer+Buffer_Offset+Element_Offset+4+2)<='z'
             && CC1(Buffer+Buffer_Offset+Element_Offset+4+3)>='A' && CC1(Buffer+Buffer_Offset+Element_Offset+4+3)<='z')
                Element_ThisIsAList();
        else
            Descriptors();
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxx_alac()
{
    Element_Name("ALAC");

    //Parsing
    Skip_B4(                                                    "Reserved");
    Skip_B2(                                                    "Reserved");
    Skip_B2(                                                    "Count");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxx_avcC()
{
    Element_Name("AVC decode");

    //Parsing
    int8u Version;
    Get_B1 (Version,                                            "Version");
    if (Version==1)
    {
        #ifdef MEDIAINFO_AVC_YES
            File_Avc Parser;
            Parser.FrameIsAlwaysComplete=true;
            Parser.MustParse_SPS_PPS=true;
            Parser.MustParse_SPS_PPS_Only=true;

            //Parsing
            Open_Buffer_Init(&Parser, File_Size, File_Offset+Buffer_Offset+(size_t)Element_Offset);
            Open_Buffer_Continue(&Parser, Buffer+Buffer_Offset+(size_t)Element_Offset, (size_t)(Element_Size-Element_Offset));

            //Filling
            Open_Buffer_Finalize(&Parser);
            Merge(Parser, Stream_Video, 0, StreamPos_Last);
        #else
            Skip_XX(Element_Size,                               "AVC Data");
        #endif
    }
    else
        Skip_XX(Element_Size,                                   "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxx_btrt()
{
    Element_Name("BitRate");

    //Parsing
    int32u maxBitrate, avgBitrate;
    Skip_B4(                                                    "bufferSizeDB");
    Get_B4 (maxBitrate,                                         "maxBitrate");
    Get_B4 (avgBitrate,                                         "avgBitrate");

    FILLING_BEGIN();
        Fill("BitRate",     avgBitrate);
        Fill("BitRate_Max", maxBitrate);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxx_chan()
{
    Element_Name("Channels");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxx_dac3()
{
    Element_Name("AC3 (Nero)");

    //Parsing
    int8u version;
    Get_B1 (version,                                            "version");
    switch (version)
    {
        case 0x01 :
                    Skip_B1(                                    "bsid");
                    break;
        default   : Skip_XX(Element_Size-Element_Offset,        "Unknown");
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxx_damr()
{
    Element_Name("AMR decode config");

    //Parsing
    Skip_C4(                                                    "Encoder vendor");
    Skip_B1(                                                    "Encoder version");
    Skip_B2(                                                    "Packet modes");
    Skip_B1(                                                    "Number of packet mode changes");
    Skip_B1(                                                    "Samples per packet");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxx_esds()
{
    NAME_VERSION_FLAG("ES Descriptor");
    INTEGRITY_VERSION(0);

    FILLING_BEGIN();
        Descriptors();
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxx_wave()
{
    Element_Name("Wave");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxx_wave_frma()
{
    Element_Name("Data format");

    //Parsing
    std::string Codec;
    Peek_String(2, Codec);
    if (Codec=="ms") //Microsoft 2CC
    {
        int16u CodecMS;
        Skip_C2(                                                "Codec_MS");
        Get_B2 (CodecMS,                                        "CC2");

        FILLING_BEGIN();
            Fill("Codec", CodecMS, 16, true);
            Fill("Codec/CC", CodecMS, 16, true);
        FILLING_END();
    }
    else
    {
        Ztring Codec;
        Get_Local(4, Codec,                                     "Codec");

        FILLING_BEGIN();
            Fill("Codec", Codec, true);
            Fill("Codec/CC", Codec, true);
        FILLING_END();
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsd_xxxx_wave_xxxx()
{
    if ((Element_Code&0x6D730000)!=0x6D730000)
        return; //Only msxx format is known

    Element_Name("Microsoft Audio");

    //Parsing
    int32u SamplesPerSec, AvgBytesPerSec;
    int16u FormatTag, Channels, BitsPerSample;
    Get_L2 (FormatTag,                                          "FormatTag");
    Get_L2 (Channels,                                           "Channels");
    Get_L4 (SamplesPerSec,                                      "SamplesPerSec");
    Get_L4 (AvgBytesPerSec,                                     "AvgBytesPerSec");
    Skip_L2(                                                    "BlockAlign");
    Get_L2 (BitsPerSample,                                      "BitsPerSample");

    FILLING_BEGIN();
        Fill("Channel(s)", Channels!=5?Channels:6, 10, true);
        Fill("SamplingRate", SamplesPerSec, 10, true);
        Fill("BitRate_Nominal", AvgBytesPerSec*8, 10, true);
    FILLING_END();

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
        else Skip_XX(Option_Size,                               "Unknown");
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsh()
{
    Element_Name("Shadow Sync Sample");

    //Parsing
    int32u entry_count;
    Get_B4 (entry_count,                                        "entry-count");

    for (int32u Pos=0; Pos<entry_count; Pos++)
    {
        Skip_B4(                                                "shadowed-sample-number");
        Skip_B4(                                                "sync-sample-number");
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stss()
{
    NAME_VERSION_FLAG("Sync Sample");

    //Parsing
    int32u entry_count;
    Get_B4 (entry_count,                                        "entry-count");

    for (int32u Pos=0; Pos<entry_count; Pos++)
    {
        Skip_B4(                                                "sample-number");
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stsz()
{
    NAME_VERSION_FLAG("Sample Size")

    int32u Size, Count;
    Get_B4 (Size,                                               "Sample Size");
    Get_B4 (Count,                                              "Number of entries");

    int64u Stream_Size=0;

    if (Size>0)
    {
        Stream_Size=Size*Count;
        if (moov_trak_mdia_minf_stbl_stco_Parse)
        {
            if (moov_trak_mdia_minf_stbl_stsz_Map[moov_trak_tkhd_TrackID]==NULL)
                moov_trak_mdia_minf_stbl_stsz_Map[moov_trak_tkhd_TrackID]=new std::vector<int64u>;
            moov_trak_mdia_minf_stbl_stsz_Map[moov_trak_tkhd_TrackID]->push_back(Stream_Size);
        }
    }
    else
    {
        if (moov_trak_mdia_minf_stbl_stsz_Map[moov_trak_tkhd_TrackID]==NULL)
            moov_trak_mdia_minf_stbl_stsz_Map[moov_trak_tkhd_TrackID]=new std::vector<int64u>;
        int32u Size;
        for (int32u Pos=0; Pos<Count; Pos++)
        {
            //Too much slow
            /*
            Get_B4 (Size,                                     "Size");
            */

            if (Element_Offset+4>Element_Size)
                break; //Problem
            Size=BigEndian2int32u(Buffer+Buffer_Offset+Element_Offset);
            Element_Offset+=4;

            Stream_Size+=Size;
            if (moov_trak_mdia_minf_stbl_stco_Parse)
                moov_trak_mdia_minf_stbl_stsz_Map[moov_trak_tkhd_TrackID]->push_back(Size);
        }
    }

    FILLING_BEGIN();
        if (Stream_Size>0)
            Fill("StreamSize", Stream_Size);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_mdia_minf_stbl_stts()
{
    NAME_VERSION_FLAG("Time to Sample");

    //Parsing
    int32u NumberOfEntries;
    Get_B4(NumberOfEntries,                                     "Number of entries");

    int32u Min=(int32u)-1;
    int32u Max=0;
    int64u FrameCount=0;

    for (int32u Pos=0; Pos<NumberOfEntries; Pos++)
    {
        int32u SampleCount, SampleDuration;
        Get_B4(SampleCount,                                     "Sample Count");
        Get_B4(SampleDuration,                                  "Sample Duration");

        FILLING_BEGIN();
            FrameCount+=SampleCount;
            if (SampleDuration<Min) Min=SampleDuration;
            if (SampleDuration>Max) Max=SampleDuration;
        FILLING_END();
    }

    FILLING_BEGIN();
        if (StreamKind_Last==Stream_Video)
        {
            if (moov_trak_mdia_mdhd_TimeScale && Min && Max)
            {
                if (Min!=Max)
                {
                    Fill("FrameRate_Min", ((float)moov_trak_mdia_mdhd_TimeScale)/Max);
                    Fill("FrameRate_Max", ((float)moov_trak_mdia_mdhd_TimeScale)/Min);
                    Fill("FrameRate",     ((float)FrameCount)/moov_trak_mdia_mdhd_PlayTime*1000, 3, true);
                }
                else
                    Fill("FrameRate",     ((float)moov_trak_mdia_mdhd_TimeScale)/Max, 3, true);
            }
            Fill("FrameCount", FrameCount);
        }
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tapt()
{
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tapt_clef()
{
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tapt_prof()
{
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tapt_enof()
{
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tkhd()
{
    NAME_VERSION_FLAG("Track Header")

    //Parsing
    Ztring Date_Created, Date_Modified;
    int64u Duration;
    int16u Volume;
        Skip_Flags(Flags, 0,                                    "Track Enabled");
        Skip_Flags(Flags, 1,                                    "Track in Movie");
        Skip_Flags(Flags, 2,                                    "Track in Preview");
        Skip_Flags(Flags, 3,                                    "Track in Poster");
    Get_DATE1904_DEPENDOFVERSION(Date_Created,                  "Creation time");
    Get_DATE1904_DEPENDOFVERSION(Date_Modified,                 "Modification time");
    Get_B4 (moov_trak_tkhd_TrackID,                             "Track ID");
    Skip_B4(                                                    "Reserved");
    Get_B_DEPENDOFVERSION(Duration,                             "Duration");
    Skip_B4(                                                    "Reserved");
    Skip_B4(                                                    "Reserved");
    Skip_B2(                                                    "Layer");
    Skip_B2(                                                    "Alternate group");
    Get_B2 (Volume,                                             "Volume"); Param_Info(Ztring::ToZtring(((float)Volume)/256));
    Skip_B2(                                                    "Reserved");
    Skip_XX(36,                                                 "Matrix structure");
    Skip_B4(                                                    "Track width");
    Skip_B4(                                                    "Track height");

    FILLING_BEGIN();
        Fill("Encoded_Date", Date_Created);
        Fill("Tagged_Date", Date_Modified);
        Fill("ID", moov_trak_tkhd_TrackID, 10, true);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tref()
{
    Element_Name("Track Reference");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tref_dpnd()
{
    Element_Name("MPEG-4 dependency");

    //Parsing
    while (Element_Offset<Element_Size)
        Skip_B4(                                                "track-ID");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tref_ipir()
{
    Element_Name("IPI declarations");

    //Parsing
    while (Element_Offset<Element_Size)
        Skip_B4(                                                "track-ID");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tref_hint()
{
    Element_Name("original media");

    //Parsing
    while (Element_Offset<Element_Size)
        Skip_B4(                                                "track-ID");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tref_mpod()
{
    Element_Name("included elementary stream");

    //Parsing
    while (Element_Offset<Element_Size)
        Skip_B4(                                                "track-ID");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tref_sync()
{
    Element_Name("synchronization source");

    //Parsing
    while (Element_Offset<Element_Size)
        Skip_B4(                                                "track-ID");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_trak_tref_tmcd()
{
    Element_Name("TimeCode");

    //Parsing
    while (Element_Offset<Element_Size)
        Skip_B4(                                                "track-ID");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta()
{
    Element_Name("User Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_AllF()
{
    Element_Name("AllF");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_chpl()
{
    Element_Name("Chapters");

    //Parsing
    Ztring Value;
    std::string ValueS;
    int64u Time;
    int8u Size;
    size_t Pos=0;
    Stream_Prepare(Stream_Chapters);
    Skip_B8(                                                    "Unknown");
    Skip_B1(                                                    "Chapter Count");
    while (Element_Offset<Element_Size)
    {
        Get_B8 (Time,                                           "Time");
        Get_B1 (Size,                                           "Text size");
        Get_String(Size, ValueS,                                "Value");
        //Value.From_UTF8(ValueS.c_str());
        //if (Value.empty())
            Value.From_Local(ValueS.c_str()); //Trying Local...

        FILLING_BEGIN();
            Ztring ToAdd;
            ToAdd+=Ztring().Duration_From_Milliseconds(Time/10000);
            ToAdd+=_T(" - ");
            ToAdd+=Value;
            Fill(Ztring::ToZtring(Pos+1).To_Local().c_str(), ToAdd);
        FILLING_END();

        //Next
        Pos++;
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_cprt()
{
    NAME_VERSION_FLAG("Copyright");

    //Parsing
    Ztring Copyright;
    Skip_B2(                                                    "Language");
    Get_Local(Element_Size-Element_Offset, Copyright,           "Copyright");

    FILLING_BEGIN();
        Fill(Stream_General, 0, "Copyright", Copyright);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_FIEL()
{
    Element_Name("FIEL?");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_FXTC()
{
    Element_Name("Adobe After Effects?");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_hinf()
{
    Element_Name("Hint Format");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_hinv()
{
    Element_Name("Hint Version");

    //Parsing
    Skip_Local(Element_Size,                                    "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_hnti()
{
    Element_Name("Hint Info");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_hnti_rtp()
{
    Element_Name("Real Time");

    //Parsing
    Skip_Local(Element_Size,                                    "Value");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_MCPS()
{
    Element_Name("Mechanical Copyright Protection Society?");

    //Parsing
    Ztring Encoder;
    Get_Local(Element_Size, Encoder,                            "Value");

    //Filling
    Fill(Stream_General, 0, "Encoded_Library", Encoder);
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_LOOP()
{
    Element_Name("LOOP");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_meta()
{
    NAME_VERSION_FLAG("Metadata");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_meta_hdlr()
{
    moov_meta_hdlr();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_meta_ilst()
{
    moov_meta_ilst();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_meta_ilst_xxxx()
{
    moov_meta_ilst_xxxx();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_meta_ilst_xxxx_data()
{
    moov_meta_ilst_xxxx_data();
}
//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_meta_ilst_xxxx_mean()
{
    moov_meta_ilst_xxxx_mean();
}
//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_meta_ilst_xxxx_name()
{
    moov_meta_ilst_xxxx_name();
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_nsav()
{
    Element_Name("No Save");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_ptv()
{
    Element_Name("Print To Video");

    //Parsing
    Skip_B2(                                                    "Display size");
    Skip_B2(                                                    "Reserved");
    Skip_B2(                                                    "Reserved");
    Skip_B1(                                                    "Slide show");
    Skip_B1(                                                    "Play on open");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_Sel0()
{
    Element_Name("Sel0");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_WLOC()
{
    Element_Name("WLOC");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_XMP_()
{
    Element_Name("eXtensible Metadata Platform");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");
}

//---------------------------------------------------------------------------
void File_Mpeg4::moov_udta_xxxx()
{
    //Getting the method
    std::string Parameter;
    method Method=Metadata_Get(Parameter, Element_Code);

    switch (Method)
    {
        case Method_None :
            {
                Element_Name("Unknown");
            }
            break;
        case Method_Binary :
            {
                Element_Name("Binary");
            }
            break;
        case Method_String :
            {
                Element_Name("Text");

                //Parsing
                Ztring Value;
                int16u Size, Language;
                bool IsText=true;
                if (Element_Size<=4)
                    IsText=false;
                else
                {
                    Peek_B2(Size);
                    if (4+(int64u)Size>Element_Size)
                        IsText=false;
                }
                if (!IsText)
                {
                    Skip_XX(Element_Size,                       "Unknown");
                    return;    
                }

                while(Element_Offset<Element_Size)
                {
                    Get_B2(Size,                                "Size");
                    Get_B2(Language,                            "Language"); Param_Info(Language_Get(Language));
                    Get_Local(Size, Value,                      "Value");

                    FILLING_BEGIN();
                        Fill(Stream_General, 0, Parameter.c_str(), Value);
                    FILLING_END();
                }
            }
            break;
        case Method_String2 :
            {
                NAME_VERSION_FLAG("Text");

                //Parsing
                Ztring Value;
                int16u Language;
                while(Element_Offset<Element_Size)
                {
                    Get_B2(Language,                            "Language"); Param_Info(Language_Get(Language));
                    Get_UTF8(Element_Size-Element_Offset, Value,"Value");

                    FILLING_BEGIN();
                        Fill(Stream_General, 0, Parameter.c_str(), Value);
                    FILLING_END();
                }
            }
            break;
        case Method_Integer :
            {
                Element_Name("Integer");

                //Parsing
                Skip_XX(4,                                      "Value");
            }
            break;
    }
}

//---------------------------------------------------------------------------
void File_Mpeg4::pckg()
{
    Element_Name("QTCA");

    //Parsing
    Skip_XX(Element_Size,                                       "Data");

    FILLING_BEGIN();
        Stream_Prepare(Stream_General);
        Fill("Format", "QTCA");
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Mpeg4::pnot()
{
    Element_Name("Preview");

    //Parsing
    Info_B4(Date_Modified,                                      "Modification date"); Param_Info(Ztring().Date_From_Seconds_1904(Date_Modified));
    Skip_B2(                                                    "Version number");
    Skip_C4(                                                    "Atom type");
    Skip_B4(                                                    "Atom index");
}

//---------------------------------------------------------------------------
void File_Mpeg4::skip()
{
    Element_Name("Skip");

    //Parsing
    Skip_XX(Element_Size,                                       "Free");
}

//---------------------------------------------------------------------------
void File_Mpeg4::wide()
{
    Element_Name("Wide");

    //Parsing
    Skip_XX(Element_Size,                                       "Free");
}

//***************************************************************************
// C++
//***************************************************************************

} //NameSpace

#endif //MEDIAINFO_MPEG4_YES
