// File_Dxw - Info for DXW files
// Copyright (C) 2010-2011 MediaArea.net SARL, Info@MediaArea.net
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

//---------------------------------------------------------------------------
// Pre-compilation
#include "MediaInfo/PreComp.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Setup.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_DXW_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Multiple/File_Dxw.h"
#include "MediaInfo/MediaInfo.h"
#include "MediaInfo/MediaInfo_Internal.h"
#include "MediaInfo/Multiple/File__ReferenceFilesHelper.h"
#include "ZenLib/Dir.h"
#include "ZenLib/FileName.h"
#include "ZenLib/Format/Http/Http_Utils.h"
#include "tinyxml2.h"
using namespace tinyxml2;
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
File_Dxw::File_Dxw()
:File__Analyze()
{
    #if MEDIAINFO_EVENTS
        ParserIDs[0]=MediaInfo_Parser_None; //TODO
        StreamIDs_Width[0]=sizeof(size_t)*2;
    #endif //MEDIAINFO_EVENTS

    //Temp
    ReferenceFiles=NULL;
}

//---------------------------------------------------------------------------
File_Dxw::~File_Dxw()
{
    delete ReferenceFiles; //ReferenceFiles=NULL;
}

//***************************************************************************
// Streams management
//***************************************************************************

//---------------------------------------------------------------------------
void File_Dxw::Streams_Finish()
{
    if (ReferenceFiles==NULL)
        return;

    ReferenceFiles->ParseReferences();
}

//***************************************************************************
// Buffer - Global
//***************************************************************************

//---------------------------------------------------------------------------
#if MEDIAINFO_SEEK
size_t File_Dxw::Read_Buffer_Seek (size_t Method, int64u Value, int64u ID)
{
    if (ReferenceFiles==NULL)
        return 0;

    return ReferenceFiles->Read_Buffer_Seek(Method, Value, ID);
}
#endif //MEDIAINFO_SEEK

//***************************************************************************
// Buffer - File header
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Dxw::FileHeader_Begin()
{
    XMLDocument document;
    if (!FileHeader_Begin_XML(document))
       return false;

    {
        XMLElement* Root=document.FirstChildElement("indexFile");
        if (Root)
        {
            const char* Attribute=Root->Attribute("xmlns");
            if (Attribute==NULL || Ztring().From_UTF8(Attribute)!=_T("urn:digimetrics-xml-wrapper"))
            {
                Reject("DXW");
                return false;
            }

            Accept("DXW");
            Fill(Stream_General, 0, General_Format, "DXW");

            ReferenceFiles=new File__ReferenceFilesHelper(this, Config);

            XMLElement* Track=Root->FirstChildElement();
            while (Track)
            {
                if (string(Track->Value())=="clip")
                {
                    File__ReferenceFilesHelper::reference ReferenceFile;

                    Attribute=Track->Attribute("file");
                    if (Attribute)
                    {
                        ReferenceFile.FileNames.push_back(Ztring().From_UTF8(Attribute));

                        Attribute=Track->Attribute("type");
                        if (Attribute)
                        {
                            Ztring StreamKind; StreamKind.From_UTF8(Attribute);
                            if (StreamKind==_T("video"))
                                 ReferenceFile.StreamKind=Stream_Video;
                            if (StreamKind==_T("audio"))
                                 ReferenceFile.StreamKind=Stream_Audio;
                            if (StreamKind==_T("data"))
                                 ReferenceFile.StreamKind=Stream_Text; //Not sure this is a right mapping, but this is only used when file is missing
                        }

                        ReferenceFile.StreamID=ReferenceFiles->References.size()+1;
                    }

                    Attribute=Track->Attribute("framerate");
                    if (Attribute)
                    {
                        ReferenceFile.FrameRate=Ztring().From_UTF8(Attribute).To_float64();

                        Attribute=Track->Attribute("type");
                        if (Attribute)
                        {
                            Ztring StreamKind; StreamKind.From_UTF8(Attribute);
                            if (StreamKind==_T("video"))
                                 ReferenceFile.StreamKind=Stream_Video;
                            if (StreamKind==_T("audio"))
                                 ReferenceFile.StreamKind=Stream_Audio;
                            if (StreamKind==_T("data"))
                                 ReferenceFile.StreamKind=Stream_Text; //Not sure this is a right mapping, but this is only used when file is missing
                        }

                        XMLElement* Frame=Track->FirstChildElement();
                        while (Frame)
                        {
                            if (string(Frame->Value())=="frame")
                            {
                                Attribute=Frame->Attribute("file");
                                if (Attribute)
                                    ReferenceFile.FileNames.push_back(Ztring().From_UTF8(Attribute));
                            }

                            Frame=Frame->NextSiblingElement();
                        }
                    }

                    ReferenceFile.StreamID=ReferenceFiles->References.size()+1;
                    ReferenceFiles->References.push_back(ReferenceFile);
                }

                Track=Track->NextSiblingElement();
            }
        }
        else
        {
            Reject("DXW");
            return false;
        }
    }

    //All should be OK...
    return true;
}

} //NameSpace

#endif //MEDIAINFO_DXW_YES

