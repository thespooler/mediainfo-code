// File_Avc - Info for MPEG-4 Visual Visual files
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
//
// Information about MPEG-4 Visual files
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef MediaInfo_Mpeg4vH
#define MediaInfo_Mpeg4vH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
#include "MediaInfo/Multiple/File_Mpeg4.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_Mpeg4v
//***************************************************************************

class File_Mpeg4v : public File__Analyze
{
public :
    //In
    size_t Frame_Count_Valid;
    bool   FrameIsAlwaysComplete;
    void   OnlyVOP(); //Data has only VOPs in it (configuration is elsewhere)

    //Out
    size_t RIFF_VOP_Count;     //RIFF limited : count the number of VOP in this chunk
    size_t RIFF_VOP_Count_Max; //RIFF limited : count the number of VOP in this chunk

protected :
    //Format
    void Read_Buffer_Continue ();
    void Read_Buffer_Finalize ();

    //Information
    void HowTo (stream_t StreamKind);

public :
    File_Mpeg4v();

private :
    //Buffer
    bool Header_Begin();
    void Header_Parse();
    bool Header_Parse_Fill_Size();
    void Data_Parse();

    //Packets
    void video_object_start();
    void video_object_layer_start();
    void fgs_bp_start();
    void visual_object_sequence_start();
    void visual_object_sequence_end();
    void user_data_start();
    void group_of_vop_start();
    void video_session_error();
    void visual_object_start();
    void vop_start();
    void vop_start_Fill();
    void slice_start();
    void extension_start();
    void fgs_vop_start();
    void fba_object_start();
    void fba_object_plane_start();
    void mesh_object_start();
    void mesh_object_plane_start();
    void still_texture_object_start();
    void texture_spatial_layer_start();
    void texture_snr_layer_start();
    void texture_tile_start();
    void texture_shape_layer_start();
    void stuffing_start();
    void reserved();

    //Count of a Packets
    size_t Frame_Count;
    size_t IVOP_Count;
    size_t PVOP_Count;
    size_t BVOP_Count;
    size_t SVOP_Count;
    size_t NVOP_Count;
    size_t Interlaced_Top;
    size_t Interlaced_Bottom;

    //From video_object_layer
    size_t time_size;
    int32u fixed_vop_time_increment;
    int16u object_layer_width;
    int16u object_layer_height;
    int16u vop_time_increment_resolution;
    int8u  visual_object_verid;
    int8u  profile_and_level_indication;
    int8u  no_of_sprite_warping_points;
    int8u  aspect_ratio_info;
    int8u  par_width;
    int8u  par_height;
    int8u  bits_per_pixel;
    int8u  shape;
    int8u  sprite_enable;
    int8u  estimation_method;
    int8u  chroma_format;
    bool   quarter_sample;
    bool   low_delay;
    bool   load_intra_quant_mat;
    bool   load_nonintra_quant_mat;
    bool   load_intra_quant_mat_grayscale;
    bool   load_nonintra_quant_mat_grayscale;
    bool   interlaced;
    bool   newpred_enable;
    bool   reduced_resolution_vop_enable;
    bool   scalability;
    bool   enhancement_type;
    bool   complexity_estimation_disable;
    bool   opaque;
    bool   transparent;
    bool   intra_cae;
    bool   inter_cae;
    bool   no_update;
    bool   upsampling;
    bool   intra_blocks;
    bool   inter_blocks;
    bool   inter4v_blocks;
    bool   not_coded_blocks;
    bool   dct_coefs;
    bool   dct_lines;
    bool   vlc_symbols;
    bool   vlc_bits;
    bool   apm;
    bool   npm;
    bool   interpolate_mc_q;
    bool   forw_back_mc_q;
    bool   halfpel2;
    bool   halfpel4;
    bool   sadct;
    bool   quarterpel;

    //From user_data
    Ztring Library;

    //Streams
    struct stream
    {
        bool   Searching_Payload;

        stream()
        {
            Searching_Payload=false;
        }
    };
    std::map<int8u, stream> Stream;

    //Helpers
    bool Synchronize();
    bool Header_Parser_QuickSearch();
    bool Detect_NonMPEG4V();
};

} //NameSpace

#endif
