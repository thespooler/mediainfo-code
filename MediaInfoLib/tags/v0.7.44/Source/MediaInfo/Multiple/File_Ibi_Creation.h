// File_Ibi_Creation - Creation of Ibi files
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
// Information about Ibi files
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef MediaInfo_File_Ibi_CreationH
#define MediaInfo_File_Ibi_CreationH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "ZenLib/Ztring.h"
#include <vector>
using namespace ZenLib;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Ibi structure
//***************************************************************************

struct ibi
{
    struct stream
    {
        int64u ID;
        int64u DtsFrequencyNumerator;
        int64u DtsFrequencyDenominator;
        struct info
        {
            int64u StreamOffset;
            int64u FrameNumber;
            int64u Dts;

            info()
            {
                StreamOffset=(int64u)-1;
                FrameNumber=(int64u)-1;
                Dts=(int64u)-1;
            }
        };
        std::vector<info> Infos;

        stream()
        {
            ID=(int64u)-1;
            DtsFrequencyNumerator=1000000000; //nanosecond
            DtsFrequencyDenominator=1;
        }
    };
    std::vector<stream> Streams;
};

//***************************************************************************
// File_Ibi_Creation class
//***************************************************************************

class File_Ibi_Creation
{
public :
    File_Ibi_Creation();
    ~File_Ibi_Creation();

    void Add(ibi::stream &Stream);
    Ztring Finish();

private :
    struct buffer
    {
        int8u* Content;
        size_t Size;

        buffer()
        {
            Content=NULL;
            Size=0;
        }

        ~buffer()
        {
            delete Content; //Content=NULL;
        }
    };
    std::vector<buffer*> Buffers;
};

} //NameSpace

#endif

