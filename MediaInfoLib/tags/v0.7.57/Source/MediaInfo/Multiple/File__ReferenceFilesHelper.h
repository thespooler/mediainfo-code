// File__ReferenceFilesHelper - class for analyzing/demuxing reference files
// Copyright (C) 2011-2011 MediaArea.net SARL, Info@MediaArea.net
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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef File__ReferenceFilesHelperH
#define File__ReferenceFilesHelperH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
#include <vector>
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File__ReferenceFilesHelper
//***************************************************************************

class File__ReferenceFilesHelper
{
public :
    //In
    struct reference
    {
        ZtringList          FileNames;
        Ztring              Source; //Source file name (relative path)
        stream_t            StreamKind;
        size_t              StreamPos;
        int64u              StreamID;
        float64             FrameRate;
        int64u              Delay;
        int64u              FileSize;
        bool                IsCircular;
        size_t              State;
        MediaInfo_Internal* MI;
        #if MEDIAINFO_FILTER
            int64u          Enabled;
        #endif //MEDIAINFO_FILTER
        #if MEDIAINFO_NEXTPACKET
            std::bitset<32> Status;
        ibi::stream         IbiStream;
        #endif //MEDIAINFO_NEXTPACKET

        reference()
        {
            FileNames.Separator_Set(0, _T(","));
            StreamKind=Stream_Max;
            StreamPos=(size_t)-1;
            StreamID=(int64u)-1;
            FrameRate=0;
            Delay=0;
            FileSize=(int64u)-1;
            IsCircular=false;
            State=0;
            MI=NULL;
            #if MEDIAINFO_FILTER
                Enabled=true;
            #endif //MEDIAINFO_FILTER
        }
    };
    typedef std::vector<reference>  references;
    references                      References;

    //Streams management
    void ParseReferences();

    //Constructor / Destructor
    File__ReferenceFilesHelper(File__Analyze* MI, MediaInfo_Config_MediaInfo* Config);

    #if MEDIAINFO_SEEK
    size_t Read_Buffer_Seek (size_t Method, int64u Value, int64u ID);
    #endif //MEDIAINFO_SEEK

private :
    //Streams management
    void ParseReference ();
    void ParseReference_Finalize ();
    void ParseReference_Finalize_PerStream ();
    void Open_Buffer_Unsynch() {Read_Buffer_Unsynched();}

    //Buffer - Global
    void Read_Buffer_Unsynched();

    //temp
    File__Analyze*                  MI;
    MediaInfo_Config_MediaInfo*     Config;
    references::iterator            Reference;
    int64u                          File_Size_Total;
    bool                            Init_Done;
    bool                            Demux_Interleave;
    size_t                          CountOfReferencesToParse;
    float64                         FrameRate;
    float64                         Duration;
    stream_t                        StreamKind_Last;
    size_t                          StreamPos_From;
    size_t                          StreamPos_To;

    //Helpers
    size_t Stream_Prepare(stream_t StreamKind, size_t StreamPos=(size_t)-1);
};

} //NameSpace

#endif

