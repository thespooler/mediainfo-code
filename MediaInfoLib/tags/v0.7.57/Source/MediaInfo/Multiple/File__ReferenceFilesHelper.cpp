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
#if defined(MEDIAINFO_REFERENCES_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Multiple/File__ReferenceFilesHelper.h"
#include "MediaInfo/MediaInfo_Internal.h"
#include "ZenLib/Dir.h"
#include "ZenLib/File.h"
#include "ZenLib/FileName.h"
#include "ZenLib/Format/Http/Http_Utils.h"
#include <set>
#include <algorithm>
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
File__ReferenceFilesHelper::File__ReferenceFilesHelper(File__Analyze* MI_, MediaInfo_Config_MediaInfo* Config_)
{
    //Temp
    MI=MI_;
    Config=Config_;
    Reference=References.end();
    File_Size_Total=MI->File_Size;
    Init_Done=false;
    FrameRate=0;
    Duration=0;
}

//***************************************************************************
// Streams management
//***************************************************************************

//---------------------------------------------------------------------------
bool File__ReferenceFilesHelper_Algo1 (const File__ReferenceFilesHelper::reference &Ref1, const File__ReferenceFilesHelper::reference &Ref2) { return (Ref1.StreamID<Ref2.StreamID);}
bool File__ReferenceFilesHelper_Algo2 (const File__ReferenceFilesHelper::reference &Ref1, const File__ReferenceFilesHelper::reference &Ref2) { return (Ref1.StreamPos<Ref2.StreamPos);}
bool File__ReferenceFilesHelper_Algo3 (const File__ReferenceFilesHelper::reference &Ref1, const File__ReferenceFilesHelper::reference &Ref2) { return (Ref1.StreamKind<Ref2.StreamKind);}
void File__ReferenceFilesHelper::ParseReferences()
{
    if (!Init_Done)
    {
        //Testing IDs
        std::sort(References.begin(), References.end(), File__ReferenceFilesHelper_Algo1);
        std::sort(References.begin(), References.end(), File__ReferenceFilesHelper_Algo2);
        std::sort(References.begin(), References.end(), File__ReferenceFilesHelper_Algo3);
        std::set<int64u> StreamList;
        bool StreamList_DuplicatedIds=false;
        for (Reference=References.begin(); Reference<References.end(); Reference++)
            if (StreamList.find((*Reference).StreamID)==StreamList.end())
                StreamList.insert((*Reference).StreamID);
            else
            {
                StreamList_DuplicatedIds=true;
                break;
            }
        if (StreamList_DuplicatedIds)
            for (Reference=References.begin(); Reference<References.end(); Reference++)
                (*Reference).StreamID=Reference-References.begin()+1;

        //Configuring file names
        File_Size_Total=0;
        Reference=References.begin();
        while (Reference!=References.end())
        {
            ZtringList Names=Reference->FileNames;
            ZtringList AbsoluteNames; AbsoluteNames.Separator_Set(0, ",");
            for (size_t Pos=0; Pos<Names.size(); Pos++)
            {
                if (Names[Pos].find(_T("file:///"))==0)
                {
                    Names[Pos].erase(0, 8); //Removing "file:///", this is the default behaviour and this makes comparison easier
                    Names[Pos]=ZenLib::Format::Http::URL_Encoded_Decode(Names[Pos]);
                }
                if (Names[Pos].find(_T("file://"))==0)
                {
                    Names[Pos].erase(0, 7); //Removing "file://", this is the default behaviour and this makes comparison easier
                    Names[Pos]=ZenLib::Format::Http::URL_Encoded_Decode(Names[Pos]);
                }
                if (Names[Pos].find(_T("file:"))==0)
                {
                    Names[Pos].erase(0, 5); //Removing "file:", this is the default behaviour and this makes comparison easier
                    Names[Pos]=ZenLib::Format::Http::URL_Encoded_Decode(Names[Pos]);
                }
                Ztring AbsoluteName;
                if (Names[Pos].find(_T(':'))!=1 && Names[Pos].find(_T("/"))!=0 && Names[Pos].find(_T("\\\\"))!=0) //If absolute patch
                {
                    AbsoluteName=ZenLib::FileName::Path_Get(MI->File_Name);
                    if (!AbsoluteName.empty())
                        AbsoluteName+=ZenLib::PathSeparator;
                }
                AbsoluteName+=Names[Pos];
                #ifdef __WINDOWS__
                    AbsoluteName.FindAndReplace(_T("/"), _T("\\"), 0, Ztring_Recursive); //Names[Pos] normalization
                #endif //__WINDOWS__
                AbsoluteNames.push_back(AbsoluteName);
            }
            if (!File::Exists(AbsoluteNames[0]))
            {
                AbsoluteNames.clear();
            
                //Configuring file name (this time, we try to force URL decode in all cases)
                for (size_t Pos=0; Pos<Names.size(); Pos++)
                {
                    Names[Pos]=ZenLib::Format::Http::URL_Encoded_Decode(Names[Pos]);
                    Ztring AbsoluteName;
                    if (Names[Pos].find(_T(':'))!=1 && Names[Pos].find(_T("/"))!=0 && Names[Pos].find(_T("\\\\"))!=0) //If absolute patch
                    {
                        AbsoluteName=ZenLib::FileName::Path_Get(MI->File_Name);
                        if (!AbsoluteName.empty())
                            AbsoluteName+=ZenLib::PathSeparator;
                    }
                    AbsoluteName+=Names[Pos];
                    #ifdef __WINDOWS__
                        AbsoluteName.FindAndReplace(_T("/"), _T("\\"), 0, Ztring_Recursive); //Names[Pos] normalization
                    #endif //__WINDOWS__
                    AbsoluteNames.push_back(AbsoluteName);
                }

                if (!File::Exists(AbsoluteNames[0]))
                {
                    AbsoluteNames.clear();
                    Names=Reference->FileNames;
            
                    //Configuring file name (this time, we try to test local files)
                    size_t PathSeparator_Pos=Names[0].find_last_of(_T("\\/"));
                    if (PathSeparator_Pos!=string::npos && PathSeparator_Pos)
                    {
                        Ztring PathToRemove=Names[0].substr(0, PathSeparator_Pos);
                        bool IsOk=true;
                        for (size_t Pos=0; Pos<Names.size(); Pos++)
                            if (Names[Pos].find(PathToRemove))
                            {
                                IsOk=false;
                                break;
                            }
                        if (IsOk)
                        {
                            for (size_t Pos=0; Pos<Names.size(); Pos++)
                            {
                                Names[Pos].erase(0, PathSeparator_Pos+1);
                                Ztring AbsoluteName=ZenLib::FileName::Path_Get(MI->File_Name);
                                if (!AbsoluteName.empty())
                                    AbsoluteName+=ZenLib::PathSeparator;
                                AbsoluteName+=Names[Pos];
                                #ifdef __WINDOWS__
                                    AbsoluteName.FindAndReplace(_T("/"), _T("\\"), 0, Ztring_Recursive); //Names[Pos] normalization
                                #endif //__WINDOWS__
                                AbsoluteNames.push_back(AbsoluteName);
                            }

                            if (!File::Exists(AbsoluteNames[0]))
                            {
                                AbsoluteNames.clear();
                                Names=Reference->FileNames;
            
                                //Configuring file name (this time, we try to test local files)
                                size_t PathSeparator_Pos=Names[0].find_last_of(_T("\\/"));
                                if (PathSeparator_Pos!=string::npos && PathSeparator_Pos)
                                    PathSeparator_Pos=Names[0].find_last_of(_T("\\/"), PathSeparator_Pos-1);
                                if (PathSeparator_Pos!=string::npos && PathSeparator_Pos)
                                {
                                    Ztring PathToRemove=Names[0].substr(0, PathSeparator_Pos);
                                    bool IsOk=true;
                                    for (size_t Pos=0; Pos<Names.size(); Pos++)
                                        if (Names[Pos].find(PathToRemove))
                                        {
                                            IsOk=false;
                                            break;
                                        }
                                    if (IsOk)
                                        for (size_t Pos=0; Pos<Names.size(); Pos++)
                                        {
                                            Names[Pos].erase(0, PathSeparator_Pos+1);
                                            Ztring AbsoluteName=ZenLib::FileName::Path_Get(MI->File_Name);
                                            if (!AbsoluteName.empty())
                                                AbsoluteName+=ZenLib::PathSeparator;
                                            AbsoluteName+=Names[Pos];
                                            #ifdef __WINDOWS__
                                                AbsoluteName.FindAndReplace(_T("/"), _T("\\"), 0, Ztring_Recursive); //Names[Pos] normalization
                                            #endif //__WINDOWS__
                                            AbsoluteNames.push_back(AbsoluteName);
                                        }
                                }
                            }
                        }
                    }
                }
            }
            Reference->Source=Reference->FileNames.Read(0);
            if (Reference->StreamKind!=Stream_Max)
                MI->Fill(Reference->StreamKind, Reference->StreamPos, "Source", Reference->Source);
            if (!AbsoluteNames.empty())
                Reference->FileNames=AbsoluteNames;

            if (!AbsoluteNames.empty() && AbsoluteNames[0]==MI->File_Name)
            {
                Reference->IsCircular=true;
                Reference->FileNames.clear();
            }
            else
                Reference->FileNames=AbsoluteNames;

            Reference->FileSize=0;
            for (size_t Pos=0; Pos<AbsoluteNames.size(); Pos++)
                Reference->FileSize+=File::Size_Get(AbsoluteNames[Pos]);
            File_Size_Total+=Reference->FileSize;

            Reference++;
        }

        Reference=References.begin();
        Init_Done=true;

        #if MEDIAINFO_DEMUX
            if (Config->NextPacket_Get())
            {
                Demux_Interleave=Config->File_Demux_Interleave_Get();
                if (Demux_Interleave)
                    CountOfReferencesToParse=References.size();
            }

            //Using the frame rate from the first stream having a frame rate
            if (!FrameRate)
                for (references::iterator ReferenceFrameRate=References.begin(); ReferenceFrameRate!=References.end(); ReferenceFrameRate++)
                    if (ReferenceFrameRate->FrameRate)
                    {
                        FrameRate=ReferenceFrameRate->FrameRate;
                        break;
                    }

            if (Config->NextPacket_Get() && MI->Demux_EventWasSent_Accept_Specific)
            {
                while (Reference!=References.end())
                {
                    ParseReference(); //Init
                    Reference++;
                }

                //Cleanup
                for (size_t Pos=0; Pos<References.size(); Pos++)
                    if (References[Pos].Status[File__Analyze::IsFinished])
                    {
                        References.erase(References.begin()+Pos);
                        Pos--;
                    }
                if (References.empty())
                    return;

                //File size handling
                if (File_Size_Total!=MI->File_Size)
                {
                    MI->Fill(Stream_General, 0, General_FileSize, File_Size_Total, 10, true);
                    MI->Fill(Stream_General, 0, General_StreamSize, MI->File_Size, 10, true);
                }

                Reference=References.begin();
                Config->Demux_EventWasSent=true;
                return;
            }
        #endif //MEDIAINFO_DEMUX
    }

    while (Reference!=References.end())
    {
        ParseReference();

        //State
        int64u FileSize_Parsed=0;
        for (references::iterator ReferenceTemp=References.begin(); ReferenceTemp!=References.end(); ReferenceTemp++)
        {
            if (ReferenceTemp->State<10000)
            {
                if (ReferenceTemp->MI)
                    ReferenceTemp->State=ReferenceTemp->MI->State_Get();
                if (ReferenceTemp->State && ReferenceTemp->FileSize!=(int64u)-1)
                    FileSize_Parsed+=(int64u)(ReferenceTemp->FileSize*(((float)ReferenceTemp->State)/10000));
            }
            else
                FileSize_Parsed+=ReferenceTemp->FileSize;
        }
        Config->State_Set(((float)FileSize_Parsed)/File_Size_Total);

        #if MEDIAINFO_DEMUX
            if (Demux_Interleave)
            {
                references::iterator Reference_Next=Reference; Reference_Next++;
                if (Reference_Next==References.end() && Config->NextPacket_Get() && CountOfReferencesToParse)
                    Reference=References.begin();
                else
                    Reference=Reference_Next;

                if (Config->Demux_EventWasSent)
                    return;
            }
            else
            {
                if (Config->Demux_EventWasSent)
                    return;

                Reference++;
            }
        #else //MEDIAINFO_DEMUX
            Reference++;
        #endif //MEDIAINFO_DEMUX
    }

    //File size handling
    if (File_Size_Total!=MI->File_Size)
    {
        MI->Fill(Stream_General, 0, General_FileSize, File_Size_Total, 10, true);
        MI->Fill(Stream_General, 0, General_StreamSize, MI->File_Size, 10, true);
    }
}

//---------------------------------------------------------------------------
void File__ReferenceFilesHelper::ParseReference()
{
    if (Reference->MI==NULL && !Reference->FileNames.empty())
    {
        //Configuration
        Reference->MI=new MediaInfo_Internal();
        Reference->MI->Option(_T("File_IsReferenced"), _T("1"));
        Reference->MI->Option(_T("File_FileNameFormat"), _T("CSV"));
        Reference->MI->Option(_T("File_KeepInfo"), _T("1"));
        Reference->MI->Option(_T("File_ID_OnlyRoot"), Config->File_ID_OnlyRoot_Get()?_T("1"):_T("0"));
        Reference->MI->Option(_T("File_DvDif_DisableAudioIfIsInContainer"), Config->File_DvDif_DisableAudioIfIsInContainer_Get()?_T("1"):_T("0"));
        if (References.size()>1 || Config->File_MpegTs_ForceMenu_Get())
            Reference->MI->Option(_T("File_MpegTs_ForceMenu"), _T("1"));
        #if MEDIAINFO_NEXTPACKET
            if (Config->NextPacket_Get())
                Reference->MI->Option(_T("File_NextPacket"), _T("1"));
        #endif //MEDIAINFO_NEXTPACKET
        #if MEDIAINFO_EVENTS
            if (Config->Event_CallBackFunction_IsSet())
                Reference->MI->Option(_T("File_Event_CallBackFunction"), Config->Event_CallBackFunction_Get());
            ZtringListList SubFile_IDs;
            for (size_t Pos=0; Pos<MI->StreamIDs_Size; Pos++)
            {
                ZtringList ID;
                if (MI->StreamIDs_Width[Pos]==0)
                    ID.push_back(Ztring::ToZtring(-1));
                else if (Pos+1==MI->StreamIDs_Size)
                    ID.push_back(Ztring::ToZtring(Reference->StreamID));
                else
                    ID.push_back(Ztring::ToZtring(MI->StreamIDs[Pos]));
                ID.push_back(Ztring::ToZtring(MI->StreamIDs_Width[Pos]));
                ID.push_back(Ztring::ToZtring(MI->ParserIDs[Pos]));
                SubFile_IDs.push_back(ID);
            }
            if (!SubFile_IDs.empty())
            {
                SubFile_IDs.Separator_Set(0, EOL);
                SubFile_IDs.Separator_Set(1, _T(","));
                Reference->MI->Option(_T("File_SubFile_IDs_Set"), SubFile_IDs.Read());
            }
        #endif //MEDIAINFO_EVENTS
        #if MEDIAINFO_DEMUX
            if (Config->Demux_Unpacketize_Get())
                Reference->MI->Option(_T("File_Demux_Unpacketize"), _T("1"));
            if (FrameRate)
                Reference->MI->Option(_T("File_Demux_Rate"), Ztring::ToZtring(FrameRate, 25));
            switch (Config->Demux_InitData_Get())
            {
                case 0 : Reference->MI->Option(_T("File_Demux_InitData"), _T("Event")); break;
                case 1 : Reference->MI->Option(_T("File_Demux_InitData"), _T("Field")); break;
                default: ;
            }
        #endif //MEDIAINFO_DEMUX
        #if MEDIAINFO_IBI
            if (!Reference->IbiStream.Infos.empty())
            {
                ibi Ibi;
                Ibi.Streams[(int64u)-1]=new ibi::stream(Reference->IbiStream);

                //IBI Creation
                File_Ibi_Creation IbiCreation(Ibi);
                Ztring IbiText=IbiCreation.Finish();
                if (!IbiText.empty())
                    Reference->MI->Option(_T("File_Ibi"), IbiText);
            }
        #endif //MEDIAINFO_IBI
 
        if (Reference->IsCircular)
        {
            MI->Fill(Reference->StreamKind, Reference->StreamPos, "Source_Info", "Circular");
            if (!Config->File_KeepInfo_Get())
            {
                #if MEDIAINFO_DEMUX
                    if (CountOfReferencesToParse)
                        CountOfReferencesToParse--;
                #endif //MEDIAINFO_DEMUX
                Reference->StreamKind=Stream_Max;
                Reference->StreamPos=(size_t)-1;
                delete Reference->MI; Reference->MI=NULL;
            }
            Reference->FileNames.clear();
        }
        else
        {
            //Run
            if (!Reference->MI->Open(Reference->FileNames.Read()))
            {
                MI->Fill(Reference->StreamKind, Reference->StreamPos, "Source_Info", "Missing");
                if (!Config->File_KeepInfo_Get())
                {
                    #if MEDIAINFO_DEMUX
                        if (CountOfReferencesToParse)
                            CountOfReferencesToParse--;
                    #endif //MEDIAINFO_DEMUX
                    Reference->StreamKind=Stream_Max;
                    Reference->StreamPos=(size_t)-1;
                    delete Reference->MI; Reference->MI=NULL;
                }
                Reference->FileNames.clear();
            }

            #if MEDIAINFO_NEXTPACKET && MEDIAINFO_DEMUX
                if (Config->NextPacket_Get() && MI->Demux_EventWasSent_Accept_Specific)
                    return;
            #endif //MEDIAINFO_NEXTPACKET
        }
    }

    if (Reference->MI)
    {
        #if MEDIAINFO_EVENTS && MEDIAINFO_NEXTPACKET
            if (Config->Event_CallBackFunction_IsSet() && !Reference->Status[File__Analyze::IsFinished])
            {
                #if MEDIAINFO_DEMUX
                    while ((Reference->Status=Reference->MI->Open_NextPacket())[8])
                    {
                            if (Config->Event_CallBackFunction_IsSet())
                            {
                                Config->Demux_EventWasSent=true;
                                return;
                            }
                    }
                if (CountOfReferencesToParse)
                    CountOfReferencesToParse--;
                #endif //MEDIAINFO_DEMUX
            }
        #endif //MEDIAINFO_EVENTS && MEDIAINFO_NEXTPACKET
        ParseReference_Finalize();
        if (!Config->File_KeepInfo_Get())
        {
            Reference->StreamKind=Stream_Max;
            Reference->StreamPos=(size_t)-1;
            Reference->State=10000;
            delete Reference->MI; Reference->MI=NULL;
        }
    }
}

//---------------------------------------------------------------------------
void File__ReferenceFilesHelper::ParseReference_Finalize ()
{
    bool StreamFound=false;
    for (size_t StreamKind=Stream_General+1; StreamKind<Stream_Max; StreamKind++)
        for (size_t StreamPos=0; StreamPos<Reference->MI->Count_Get((stream_t)StreamKind); StreamPos++)
        {
            StreamKind_Last=(stream_t)StreamKind;
            if (Reference->StreamPos!=(size_t)-1 && StreamKind_Last==Reference->StreamKind && StreamPos==0)
            {
                StreamPos_To=Reference->StreamPos;
                StreamFound=true;
            }
            else
                StreamPos_To=MI->Stream_Prepare((stream_t)StreamKind);
            StreamPos_From=StreamPos;

            ParseReference_Finalize_PerStream();
        }

    if (!StreamFound && Reference->StreamKind!=Stream_Max && Reference->StreamPos!=(size_t)-1)
    {
        Ztring MuxingMode=MI->Retrieve(Reference->StreamKind, Reference->StreamPos, "MuxingMode");
        if (!MuxingMode.empty())
            MuxingMode.insert(0, _T(" / "));
        MI->Fill(Reference->StreamKind, Reference->StreamPos, "MuxingMode", Reference->MI->Info->Get(Stream_General, 0, General_Format)+MuxingMode, true);
    }
}

//---------------------------------------------------------------------------
void File__ReferenceFilesHelper::ParseReference_Finalize_PerStream ()
{
    //Hacks - Before
    Ztring CodecID=MI->Retrieve(StreamKind_Last, StreamPos_To, MI->Fill_Parameter(StreamKind_Last, Generic_CodecID));
    Ztring ID_Base;
    if (Reference->StreamID!=(int64u)-1)
        ID_Base=Ztring::ToZtring(Reference->StreamID);
    Ztring ID=ID_Base;
    Ztring ID_String=ID_Base;
    Ztring MenuID;
    Ztring MenuID_String;

    MI->Clear(StreamKind_Last, StreamPos_To, General_ID);

    MI->Merge(*Reference->MI->Info, StreamKind_Last, StreamPos_From, StreamPos_To);

    //Frame rate if available from container
    if (StreamKind_Last==Stream_Video && Reference->FrameRate)
        MI->Fill(Stream_Video, StreamPos_To, Video_FrameRate, Reference->FrameRate, 3 , true);

    //Hacks - After
    if (CodecID!=MI->Retrieve(StreamKind_Last, StreamPos_To, MI->Fill_Parameter(StreamKind_Last, Generic_CodecID)))
    {
        if (!CodecID.empty())
            CodecID+=_T(" / ");
        CodecID+=MI->Retrieve(StreamKind_Last, StreamPos_To, MI->Fill_Parameter(StreamKind_Last, Generic_CodecID));
        MI->Fill(StreamKind_Last, StreamPos_To, MI->Fill_Parameter(StreamKind_Last, Generic_CodecID), CodecID, true);
    }
    if (!(Config->File_ID_OnlyRoot_Get() && Reference->MI->Count_Get(Stream_Video)+Reference->MI->Count_Get(Stream_Audio)<=1) || ID_Base.empty())
    {
        if (StreamKind_Last==Stream_Menu)
        {
            ZtringList List; List.Separator_Set(0, _T(" / ")); List.Write(MI->Retrieve(StreamKind_Last, StreamPos_To, "List"));
            ZtringList List_String; List_String.Separator_Set(0, _T(" / ")); List_String.Write(MI->Retrieve(StreamKind_Last, StreamPos_To, "List/String"));
            if (!ID_Base.empty())
                for (size_t Pos=0; Pos<List.size(); Pos++)
                {
                    List[Pos].insert(0, ID+_T("-"));
                    List_String[Pos].insert(0, ID+_T("-"));
                }
            MI->Fill(Stream_Menu, StreamPos_To, Menu_List, List.Read(), true);
            MI->Fill(Stream_Menu, StreamPos_To, Menu_List_String, List_String.Read(), true);
        }
        if (!MI->Retrieve(StreamKind_Last, StreamPos_To, General_ID).empty())
        {
            if (!ID_Base.empty())
                ID+=_T('-');
            ID+=MI->Retrieve(StreamKind_Last, StreamPos_To, General_ID);
            if (!ID_Base.empty())
                ID_String+=_T('-');
            ID_String+=MI->Retrieve(StreamKind_Last, StreamPos_To, General_ID_String);
            if (!MI->Retrieve(StreamKind_Last, StreamPos_To, "MenuID").empty())
            {
                if (!ID_Base.empty())
                    MenuID=ID_Base+_T('-');
                MenuID+=MI->Retrieve(StreamKind_Last, StreamPos_To, "MenuID");
                if (!ID_Base.empty())
                    MenuID_String=ID_Base+_T('-');
                MenuID_String+=MI->Retrieve(StreamKind_Last, StreamPos_To, "MenuID/String");
            }
        }
    }
    MI->Fill(StreamKind_Last, StreamPos_To, General_ID, ID, true);
    MI->Fill(StreamKind_Last, StreamPos_To, General_ID_String, ID_String, true);
    MI->Fill(StreamKind_Last, StreamPos_To, "MenuID", MenuID, true);
    MI->Fill(StreamKind_Last, StreamPos_To, "MenuID/String", MenuID_String, true);
    if (MI->Retrieve(StreamKind_Last, StreamPos_To, "Source").empty())
        MI->Fill(StreamKind_Last, StreamPos_To, "Source", Reference->Source);

    //Others
    if (Reference->MI->Info && MI->Retrieve(StreamKind_Last, StreamPos_To, Reference->MI->Info->Fill_Parameter(StreamKind_Last, Generic_Format))!=Reference->MI->Info->Get(Stream_General, 0, General_Format))
    {
        Ztring MuxingMode=MI->Retrieve(StreamKind_Last, StreamPos_To, "MuxingMode");
        if (!MuxingMode.empty())
            MuxingMode.insert(0, _T(" / "));
        MI->Fill(StreamKind_Last, StreamPos_To, "MuxingMode", Reference->MI->Info->Get(Stream_General, 0, General_Format)+MuxingMode, true);
    }
}

//---------------------------------------------------------------------------
void File__ReferenceFilesHelper::Read_Buffer_Unsynched()
{
    MI->Open_Buffer_Unsynch();
    for (references::iterator Reference=References.begin(); Reference!=References.end(); Reference++)
        if (Reference->MI)
            Reference->MI->Open_Buffer_Unsynch();

    #if MEDIAINFO_DEMUX
        Config->Demux_EventWasSent=true; //We want not try to read new data from the file
    #endif //MEDIAINFO_DEMUX
}

//---------------------------------------------------------------------------
#if MEDIAINFO_SEEK
size_t File__ReferenceFilesHelper::Read_Buffer_Seek (size_t Method, int64u Value, int64u ID)
{
    //Parsing
    switch (Method)
    {
        case 0  :   
                    #if MEDIAINFO_DEMUX
                        {
                        if (Value)
                        {
                            if (Value>File_Size_Total)
                                return 2; //Invalid value

                            //Init
                            if (!Duration)
                            {
                                MediaInfo_Internal MI2;
                                MI2.Option(_T("File_KeepInfo"), _T("1"));
                                Ztring ParseSpeed_Save=MI2.Option(_T("ParseSpeed_Get"), _T(""));
                                Ztring Demux_Save=MI2.Option(_T("Demux_Get"), _T(""));
                                MI2.Option(_T("ParseSpeed"), _T("0"));
                                MI2.Option(_T("Demux"), Ztring());
                                size_t MiOpenResult=MI2.Open(MI->File_Name);
                                MI2.Option(_T("ParseSpeed"), ParseSpeed_Save); //This is a global value, need to reset it. TODO: local value
                                MI2.Option(_T("Demux"), Demux_Save); //This is a global value, need to reset it. TODO: local value
                                if (!MiOpenResult)
                                    return (size_t)-1;
                                Duration=MI2.Get(Stream_General, 0, General_Duration).To_float64()/1000;
                            }

                            //Time percentage
                            float64 DurationF=Duration;
                            DurationF*=Value;
                            DurationF/=File_Size_Total;
                            size_t DurationM=(size_t)(DurationF*1000);
                            Ztring DurationS;
                            DurationS+=L'0'+(wchar_t)(DurationM/(10*60*60*1000)); DurationM%=10*60*60*1000;
                            DurationS+=L'0'+(wchar_t)(DurationM/(   60*60*1000)); DurationM%=   60*60*1000;
                            DurationS+=L':';
                            DurationS+=L'0'+(wchar_t)(DurationM/(   10*60*1000)); DurationM%=   10*60*1000;
                            DurationS+=L'0'+(wchar_t)(DurationM/(      60*1000)); DurationM%=      60*1000;
                            DurationS+=L':';
                            DurationS+=L'0'+(wchar_t)(DurationM/(      10*1000)); DurationM%=      10*1000;
                            DurationS+=L'0'+(wchar_t)(DurationM/(         1000)); DurationM%=         1000;
                            DurationS+=L'.';
                            DurationS+=L'0'+(wchar_t)(DurationM/(          100)); DurationM%=          100;
                            DurationS+=L'0'+(wchar_t)(DurationM/(           10)); DurationM%=           10;
                            DurationS+=L'0'+(wchar_t)(DurationM);

                            CountOfReferencesToParse=References.size();
                            bool HasProblem=false;
                            for (Reference=References.begin(); Reference!=References.end(); Reference++)
                            {
                                if (Reference->MI)
                                {
                                    Ztring Result=Reference->MI->Option(_T("File_Seek"), DurationS);
                                    if (!Result.empty())
                                        HasProblem=true;
                                }
                                Reference->Status.reset();
                            }
                            Reference=References.begin();
                            Open_Buffer_Unsynch();
                            return HasProblem?(size_t)-1:1; //Not supported value if there is a problem (TODO: better info)
                        }

                        CountOfReferencesToParse=References.size();
                        bool HasProblem=false;
                        for (Reference=References.begin(); Reference!=References.end(); Reference++)
                        {
                            if (Reference->MI)
                            {
                                Ztring Result=Reference->MI->Option(_T("File_Seek"), Ztring::ToZtring(Value));
                                if (!Result.empty())
                                    HasProblem=true;
                            }
                            Reference->Status.reset();
                        }
                        Reference=References.begin();
                        Open_Buffer_Unsynch();
                        return HasProblem?(size_t)-1:1; //Not supported value if there is a problem (TODO: better info)
                        }
                    #else //MEDIAINFO_DEMUX
                        return (size_t)-1; //Not supported
                    #endif //MEDIAINFO_DEMUX
        case 1  :   
                    {
                        //Time percentage
                        int64u Duration=MI->Get(Stream_General, 0, General_Duration).To_int64u();
                        Ztring DurationS;
                        if (Duration)
                        {
                            Duration*=Value;
                            Duration/=10000;
                            DurationS+=L'0'+(wchar_t)(Duration/(10*60*60*1000)); Duration%=10*60*60*1000;
                            DurationS+=L'0'+(wchar_t)(Duration/(   60*60*1000)); Duration%=   60*60*1000;
                            DurationS+=L':';
                            DurationS+=L'0'+(wchar_t)(Duration/(   10*60*1000)); Duration%=   10*60*1000;
                            DurationS+=L'0'+(wchar_t)(Duration/(      60*1000)); Duration%=      60*1000;
                            DurationS+=L':';
                            DurationS+=L'0'+(wchar_t)(Duration/(      10*1000)); Duration%=      10*1000;
                            DurationS+=L'0'+(wchar_t)(Duration/(         1000)); Duration%=         1000;
                            DurationS+=L'.';
                            DurationS+=L'0'+(wchar_t)(Duration/(          100)); Duration%=          100;
                            DurationS+=L'0'+(wchar_t)(Duration/(           10)); Duration%=           10;
                            DurationS+=L'0'+(wchar_t)(Duration);
                        }
                        else
                            DurationS=Ztring::ToZtring(((float64)Value)/100)+_T('%');

                        CountOfReferencesToParse=References.size();
                        bool HasProblem=false;
                        for (Reference=References.begin(); Reference!=References.end(); Reference++)
                        {
                            if (Reference->MI)
                            {
                                Ztring Result=Reference->MI->Option(_T("File_Seek"), DurationS);
                                if (!Result.empty())
                                    HasProblem=true;
                            }
                            Reference->Status.reset();
                        }
                        Reference=References.begin();
                        Open_Buffer_Unsynch();
                        return HasProblem?2:1; //Invalid value if there is a problem (TODO: better info)
                    }
        case 2  :   //Timestamp
                    #if MEDIAINFO_DEMUX
                    {
                        CountOfReferencesToParse=References.size();
                        Ztring Time; Time.Duration_From_Milliseconds(Value/1000000);
                        for (Reference=References.begin(); Reference!=References.end(); Reference++)
                        {
                            if (Reference->MI)
                            {
                                Ztring Result=Reference->MI->Option(_T("File_Seek"), Time);
                                if (!Result.empty())
                                    return 2; //Invalid value
                            }
                            else
                            {
                                //There was a problem, removing Reference
                                References.clear();
                                return Read_Buffer_Seek(Method, Value, ID);
                            }
                            Reference->Status.reset();
                        }
                        Reference=References.begin();
                        Open_Buffer_Unsynch();
                        return 1;
                    }
                    #else //MEDIAINFO_DEMUX
                        return (size_t)-1; //Not supported
                    #endif //MEDIAINFO_DEMUX
        case 3  :   //FrameNumber
                    #if MEDIAINFO_DEMUX
                        CountOfReferencesToParse=References.size();
                        for (Reference=References.begin(); Reference!=References.end(); Reference++)
                        {
                            if (Reference->MI)
                            {
                                Ztring Result=Reference->MI->Option(_T("File_Seek"), _T("Frame=")+Ztring::ToZtring(Value));
                                if (!Result.empty())
                                    return 2; //Invalid value
                            }
                            else
                            {
                                //There was a problem, removing Reference
                                References.clear();
                                return Read_Buffer_Seek(Method, Value, ID);
                            }
                            Reference->Status.reset();
                        }
                        Reference=References.begin();
                        Open_Buffer_Unsynch();
                        return 1;
                    #else //MEDIAINFO_DEMUX
                        return (size_t)-1; //Not supported
                    #endif //MEDIAINFO_DEMUX
         default :   return 0;
    }
}
#endif //MEDIAINFO_SEEK

//***************************************************************************
// Helpers
//***************************************************************************

//---------------------------------------------------------------------------
size_t File__ReferenceFilesHelper::Stream_Prepare (stream_t StreamKind, size_t StreamPos)
{
    size_t StreamPos_Last=MI->Stream_Prepare(StreamKind, StreamPos);

    for (references::iterator ReferencePos=References.begin(); ReferencePos!=References.end(); ReferencePos++)
        if (ReferencePos->StreamKind==StreamKind && ReferencePos->StreamPos>=StreamPos_Last)
            if (ReferencePos->StreamPos!=(size_t)-1)
                ReferencePos->StreamPos++;

    return StreamPos_Last;
}

} //NameSpace

#endif //MEDIAINFO_REFERENCES_YES
