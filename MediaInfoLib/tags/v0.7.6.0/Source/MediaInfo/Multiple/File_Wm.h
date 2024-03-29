// File_Wm - Info for Windows Media files
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
#ifndef MediaInfo_File_WmH
#define MediaInfo_File_WmH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
#include <map>
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_Wm
//***************************************************************************

class File_Wm : public File__Analyze
{
public :
    File_Wm();

protected :
    //Format
    void Read_Buffer_Finalize ();

    //Information
    void HowTo (stream_t StreamKind);

private :
    //Buffer
    void Header_Parse();
    void Header_Parse_Data();
    void Header_Parse_Data_Begin();
    void Header_Parse_Data_MultiplePayloads();
    void Header_Parse_Data_Payload();
    void Data_Parse();

    //Elements
    void Header();
    void Header_FileProperties();
    void Header_StreamProperties();
    void Header_StreamProperties_Audio();
    void Header_StreamProperties_Audio_WMA();
    void Header_StreamProperties_Audio_AMR();
    void Header_StreamProperties_Video();
    void Header_StreamProperties_JFIF();
    void Header_StreamProperties_DegradableJPEG();
    void Header_StreamProperties_Binary();
    void Header_HeaderExtension();
    void Header_HeaderExtension_ExtendedStreamProperties();
    void Header_HeaderExtension_AdvancedMutualExclusion();
    void Header_HeaderExtension_GroupMutualExclusion();
    void Header_HeaderExtension_StreamPrioritization();
    void Header_HeaderExtension_BandwidthSharing();
    void Header_HeaderExtension_LanguageList();
    void Header_HeaderExtension_Metadata();
    void Header_HeaderExtension_MetadataLibrary();
    void Header_HeaderExtension_IndexParameters();
    void Header_HeaderExtension_MediaIndexParameters();
    void Header_HeaderExtension_TimecodeIndexParameters();
    void Header_HeaderExtension_Compatibility();
    void Header_HeaderExtension_AdvancedContentEncryption();
    void Header_CodecList();
    void Header_ScriptCommand();
    void Header_Marker();
    void Header_BitRateMutualExclusion();
    void Header_ErrorCorrection();
    void Header_ContentDescription();
    void Header_ExtendedContentDescription();
    void Header_ExtendedContentDescription_ASFLeakyBucketPairs(int16u Value_Length);
    void Header_StreamBitRate();
    void Header_ContentBranding();
    void Header_ContentEncryption();
    void Header_ExtendedContentEncryption();
    void Header_DigitalSignature();
    void Header_Padding();
    void Data();
    void Data_Packet();
    void Data_Packet_Jump();
    void SimpleIndex();
    void Index();
    void MediaIndex();
    void TimecodeIndex();

    //Data
    struct stream
    {
        File__Analyze*          Parser;
        File__Analyze*          Parser2;
        File__Analyze*          Parser3;
        stream_t                StreamKind;
        size_t                  StreamPos;
        size_t                  PacketCount;
        int64u                  AverageTimePerFrame;
        int32u                  AverageBitRate;
        int16u                  LanguageID;
        std::map<std::string, ZenLib::Ztring> Info;
        bool                    IsCreated; //if Stream_Prepare() is done
        bool                    SearchingPayload;

        stream()
        {
            Parser=NULL;
            Parser2=NULL;
            Parser3=NULL;
            StreamKind=Stream_Max;
            StreamPos=0;
            PacketCount=0;
            AverageTimePerFrame=0;
            AverageBitRate=0;
            LanguageID=(int16u)-1;
            IsCreated=false;
            SearchingPayload=false;
        }

        ~stream()
        {
            delete Parser; //Parser=NULL;
            delete Parser2; //Parser2=NULL
            delete Parser3; //Parser3=NULL
        }
    };
    std::map<int16u, stream>    Stream;
    int16u                      Stream_Number; //In header: current pos, in Data: Count of enabled parsers
    std::vector<ZenLib::Ztring> Languages;
    Ztring                      Language_ForAll;
    int32u                      Data_Parse_Padding;
    int32u                      MaximumDataPacketSize;
    bool                        Data_Parse_Begin;
    bool                        Data_Parse_MultiplePayloads;
    bool                        Data_Parse_CompressedPayload;
    bool                        IsDvrMs;                        //Is DVR-Ms format (for finding MPEG Audio)

    //From Data headers
    int32u PacketLength;
    int32u SizeOfMediaObject;
    int8u  ReplicatedDataLengthType;
    int8u  OffsetIntoMediaObjectLengthType;
    int8u  MediaObjectNumberLengthType;
    int8u  StreamNumberLengthType;
    int8u  PayloadLengthType;
    int8u  NumberPayloads;
    int8u  NumberPayloads_Pos;
    bool   MultiplePayloadsPresent;
};

} //NameSpace

#endif
