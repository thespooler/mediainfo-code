// Preferences - Manage preferences of MediaInfo
// Copyright (C) 2002-2008 Jerome Martinez, Zen@MediaArea.net
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Manage preferences of MediaInfo
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#define NO_WIN32_LEAN_AND_MEAN
#include <vcl.h>
#undef NO_WIN32_LEAN_AND_MEAN
#include <ZenLib/Conf.h>
#pragma hdrstop
#include <Forms.hpp>
#include <Registry.hpp>
#include <Wininet.h>
#include <Shlobj.h>
#include "Preferences.h"
#include <ZenLib/Dir.h>
#include <ZenLib/File.h>
#include <ZenLib/HTTP_Client.h>
using namespace ZenLib;
#ifdef MEDIAINFO_DLL
    #include "MediaInfoDLL/MediaInfoDLL_Static.h"
#else
    #include "MediaInfo/MediaInfo.h"
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
Preferences* Prefs=new Preferences;
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
Preferences::Preferences()
{
    //Name of folders
    FolderNames=_T(
        "Language;"
        "Sheet;"
        "Tree;"
        "Custom;"
        "Language");
    //Name of default for kind of list
    DefaultNames=_T(
        "en;"
        "Example;"
        "Example;"
        "Example;"
        "en;");
}

//***************************************************************************
// Config
//***************************************************************************

//---------------------------------------------------------------------------
int Preferences::Config_Create()
{
    Config=_T(
        "Version;X.X.X.X\r\n"
        "NewestVersion;X.X.X.X\r\n"
        "Output;Basic\r\n"
        "Language;en\r\n"
        "Sheet;Example\r\n"
        "Tree;Example\r\n"
        "Custom;Example\r\n"
        "CheckUpdate;1\r\n"
        "ShellExtension;1\r\n"
        "ShellInfoTip;0\r\n"
        "ShowToolBar;1\r\n"
        "ShowMenu;1\r\n"
        "CloseAllAuto;1\r\n");
    Config(_T("Version")).FindAndReplace(_T("X.X.X.X"), MediaInfo_Version_GUI);
    Config(_T("NewestVersion")).FindAndReplace(_T("X.X.X.X"), MediaInfo_Version_GUI);
    Config.Save(BaseFolder+_T("MediaInfo.cfg"));

    return 1;
}

//---------------------------------------------------------------------------
int Preferences::Config_Load()
{
    int Retour=1;

    //Base folder
    BaseFolder.From_Local(Application->ExeName.c_str());
    BaseFolder=BaseFolder.substr(0, BaseFolder.rfind(_T("\\"))+1);
    if (!Dir::Exists(BaseFolder+_T("Plugin")))
        Dir::Create(BaseFolder+_T("Plugin"));
    BaseFolder+=_T("Plugin\\");

    //Directories
    for (size_t Pos=0; Pos<FolderNames.size(); Pos++)
        if (!Dir::Exists(BaseFolder+FolderNames[Pos]))
            Dir::Create(BaseFolder+FolderNames[Pos]);

    //Default language
    if (!File::Exists(BaseFolder+_T("Language\\en.csv")))
        Create(Language, _T("en"));
    Load(Language_English, _T("en"));

    //Configuration
    Config.Load(BaseFolder+_T("MediaInfo.cfg"));
    if (Config.size()==0 || Config(_T("Version"))!=MediaInfo_Version_GUI)
    {
        Config_Create();
        Retour=2;
    }

    RefreshFilesList(Language);
    Load(Language, Config(FolderNames[Language]));
    RefreshFilesList(Sheet);
    Load(Sheet, Config(FolderNames[Sheet]));
    RefreshFilesList(Tree);
    Load(Tree, Config(FolderNames[Tree]));
    RefreshFilesList(Custom);
    Load(Custom, Config(FolderNames[Custom]));

    //Shell Extension
    ExplorerShell();
    ShellToolTip();

    //Internet
    if (Retour!=2 && Config(_T("CheckUpdate"))==_T("1"))
        Prefs->InternetCheck();

    return Retour;
}

//---------------------------------------------------------------------------
int Preferences::Config_Save()
{
    return Config.Save();
}

//---------------------------------------------------------------------------
int Preferences::Config_Remove()
{
    return -1;
}

//***************************************************************************
// KindOfList management
//***************************************************************************

//---------------------------------------------------------------------------
int Preferences::Create(List_t KindOfList, const ZenLib::Ztring &Name)
{
    switch (KindOfList)
    {
        case Language :
            Details[KindOfList]=MediaInfoLib::MediaInfo::Option_Static(_T("Language_Get")).c_str();
            if (Name!=_T("en"))
                for (size_t Pos=0; Pos<Details[KindOfList].size(); Pos++)
                    Details[KindOfList](Pos, 1)=_T("");
            break;
        case Sheet :
            Details[KindOfList]=_T(
                "ColumnsCount;5\r\n"
                "Column0;General;0;CompleteName;30\r\n"
                "Column1;General;0;Format;10\r\n"
                "Column2;General;0;Video_Codec_List;10\r\n"
                "Column3;General;0;Audio_Codec_List;10\r\n"
                "Column4;General;0;Text_Codec_List;10");
            break;
        case Tree :
            break;
        case Custom :
            Details[KindOfList]=_T(
                "General;General           : %FileName%\\r\\nFormat            : %Format%$if(%OveralBitRate%, at %OveralBitRate/String%)\\r\\nLength            : %FileSize/String1% for %PlayTime/String1%\\r\\n\\r\\n\r\n"
                "Video;Video #%StreamKindID%          : %Codec/String%$if(%BitRate%, at %BitRate/String%)\\r\\nAspect            : %Width% x %Height% (%AspectRatio%) at %fps% fps\\r\\n\\r\\n\r\n"
                "Audio;Audio #%StreamKindID%          : %Codec/String%$if(%BitRate%, at %BitRate/String%)\\r\\nInfos             : %Channel(s)/String%, %SamplingRate/String%\\r\\n$if(%Language%,Language          : %Language%\\r\\n)\\r\\n\r\n"
                "Text;Text #%StreamKindID%           : %Codec/String%\\r\\n$if(%Language%,Language          : %Language%\\r\\n)\\r\\n\r\n"
                "Chapters;Chapters #%StreamKindID%       : %Total% chapters\\r\\n\\r\\n\r\n"
                "File_Begin\r\n"
                "File_End\r\n"
                "Page_Begin\r\n"
                "Page_Middle\r\n"
                "Page_End\r\n"
                "General_Begin\r\n"
                "General_End\r\n"
                "Video_Begin\r\n"
                "Video_Middle\r\n"
                "Video_End\r\n"
                "Audio_Begin\r\n"
                "Audio_Middle\r\n"
                "Audio_End\r\n"
                "Text_Begin\r\n"
                "Text_Middle\r\n"
                "Text_End\r\n"
                "Chapters_Begin\r\n"
                "Chapters_Middle\r\n"
                "Chapters_End");
            break;
        default:
            return -1;
    }
    Details[KindOfList].Save(BaseFolder+FolderNames[KindOfList]+_T("\\")+Name+_T(".csv"));

    return 1;
}

//---------------------------------------------------------------------------
int Preferences::Copy(List_t KindOfList, const ZenLib::Ztring &From, const ZenLib::Ztring &To)
{
    return File::Copy(BaseFolder+FolderNames[KindOfList]+_T("\\")+From+_T(".csv"), BaseFolder+_T("MediaInfo.")+FolderNames[KindOfList]+_T(".")+To+_T(".csv"));
}

//---------------------------------------------------------------------------
int Preferences::Load(List_t KindOfList, const ZenLib::Ztring &Name)
{
    //Test if the file exists
    if (!File::Exists(BaseFolder+FolderNames[KindOfList]+_T("\\")+Name+_T(".csv")))
        return -1;

    Details[KindOfList].Load(BaseFolder+FolderNames[KindOfList]+_T("\\")+Name+_T(".csv"));

    return 1;
}

//---------------------------------------------------------------------------
int Preferences::Remove(List_t KindOfList, const ZenLib::Ztring &Name)
{
    Ztring Lang; if (KindOfList==Custom) Lang=Config(_T("Language"))+_T("."); //Special case : if Custom; we add Language in the file name
    return File::Delete(BaseFolder+FolderNames[KindOfList]+_T("\\")+Lang+Name+_T(".csv"));
}

//***************************************************************************
// FilesLists
//***************************************************************************

//---------------------------------------------------------------------------
int Preferences::RefreshFilesList(List_t KindOfList)
{
    //Default available?
    if (!File::Exists(BaseFolder+FolderNames[KindOfList]+_T("\\")+DefaultNames[KindOfList]+_T(".csv")))
        Create(KindOfList, DefaultNames[KindOfList]);

    //Listing
    FilesList[KindOfList]=Dir::GetAllFileNames(BaseFolder+FolderNames[KindOfList]+_T("\\")+_T("*.csv"));
    if (KindOfList==Language)
    {
        //Special case : Languages, should show the name of language in the local version
        FilesList[Language_List].clear();
        for (size_t Pos=0; Pos<FilesList[KindOfList].size(); Pos++)
        {
            ZtringListListF Lang;
            Lang.Load(FilesList[KindOfList][Pos]);
            Ztring Local=Lang(_T("  Language_Name"));
            if (Local.size()==0)
                Local=FilesList[KindOfList][Pos].SubString(BaseFolder+FolderNames[KindOfList]+_T("\\"), _T(".csv"));
            FilesList[Language_List].push_back(Local);
        }
    }

    //Only name
    for (size_t Pos=0; Pos<FilesList[KindOfList].size(); Pos++)
        FilesList[KindOfList][Pos]=FilesList[KindOfList][Pos].SubString(BaseFolder+FolderNames[KindOfList]+_T("\\"), _T(".csv"));

    return 1;
}

//***************************************************************************
// System
//***************************************************************************

class ThreadInternetCheck:public TThread
{
public:
    __fastcall ThreadInternetCheck(bool CreateSuspended): TThread(CreateSuspended){}
    void __fastcall Execute();
};

void __fastcall ThreadInternetCheck::Execute()
{
    //Connexion test
    if (InternetGetConnectedState(NULL, 0)==0)
        return; //No internet connexion

    HTTP_Client H;
    if (H.Open(Ztring(_T("http://mediaarea.net/mediainfo_check/changelog_"))+MediaInfo_Version_GUI+_T(".bin"))==0)
        return;

    Ztring Z=H.Read();
    ZtringListList Download(Z);

    //Verification de la version
    Ztring Version=Prefs->Config.FindValue(_T("NewestVersion"), 1);
    Ztring NewestVersion=Download(_T("NewVersion"));
    if (NewestVersion!=_T("") && NewestVersion>Version)
    {
        //Affichage d'un message
        ZtringListList C3=Download.SubSheet(_T("NewMessage"));
        int Pos=C3.Find(Prefs->Config(_T("Language")), 1);
        if (Pos==-1)
            Pos=C3.Find(_T("en"), 1);
        if (Pos==-1)
            return;
        C3(Pos, 2).FindAndReplace(_T("\\r\\n"), _T("\r\n"));
        Application->MessageBox(AnsiString(C3(Pos, 2).c_str()).c_str(), "New version released!");
        //Inscription version connue pour pas repeter l'avertissement
        int Version_Pos=Prefs->Config.Find(_T("NewestVersion"));
        Prefs->Config(Version_Pos, 1)=NewestVersion;
        Prefs->Config.Save();
    }

    //Chargement de pages
    ZtringListList Pages=Download.SubSheet(_T("Url"));
    for (size_t Pos=0; Pos<Pages.size(); Pos++)
    {
        //Doit-on charger ou pas?
        if (Pages.Read(Pos, 1)==_T("1"))
        {
            HTTP_Client H2;
            if (H2.Open(Pages.Read(Pos, 2))==0)
                return;
            Ztring Image=H2.Read();
        }
    }

    return;
}

//---------------------------------------------------------------------------
int Preferences::InternetCheck()
{
    new ThreadInternetCheck(false);
    return 1;
}

//---------------------------------------------------------------------------
int Preferences::ExplorerShell()
{
    TRegistry* Reg=new TRegistry;
    Reg->RootKey = HKEY_CLASSES_ROOT;

    ZtringListList Liste;
    Liste=_T(
        ".mkv;MKVFile\r\n"
        ".mka;MKAFile\r\n"
        ".mks;MKSFile\r\n"
        ".ogg;OGGFile\r\n"
        ".ogm;OGMFile\r\n"
        ".wav;WAVFile\r\n"
        ".avi;AVIFile\r\n"
        ".divx;AVIFile\r\n"
        ".gvi;AVIFile\r\n"
        ".mpeg;mpegFile\r\n"
        ".mpg;mpegFile\r\n"
        ".dat;datFile\r\n"
        ".mpe;mpegFile\r\n"
        ".mpgx;mpegFile\r\n"
        ".mpm;mpegFile\r\n"
        ".m1s;mpegFile\r\n"
        ".vob;mpegFile\r\n"
        ".m2s;mpegFile\r\n"
        ".mp4;mpeg4File\r\n"
        ".m4a;mpeg4File\r\n"
        ".mpgv;mpegFile\r\n"
        ".mpv;mpegFile\r\n"
        ".m1v;mpegFile\r\n"
        ".m2v;mpegFile\r\n"
        ".ts;tsFile\r\n"
        ".m2ts;m2tsFile\r\n"
        ".mp2;mp3File\r\n"
        ".mp3;mp3File\r\n"
        ".mpc;mpcFile\r\n"
        ".mp+;mpcFile\r\n"
        ".asf;ASFFile\r\n"
        ".wmv;WMVFile\r\n"
        ".wma;WMAFile\r\n"
        ".mov;MOVFile\r\n"
        ".qt;QTFile\r\n"
        ".rm;RMFile\r\n"
        ".ra;RMFile\r\n"
        ".ifo;IfoFile\r\n"
        ".ac3;AC3File\r\n"
        ".dts;DTSFile\r\n"
        ".aac;AACFile\r\n"
        ".ape;APEFile\r\n"
        ".mac;APEFile\r\n"
        ".flac;FLACFile\r\n"
        ".3gp;mpeg4File\r\n"
        ".3gpp;mpeg4File\r\n"
        ".swf;FlashFile\r\n"
        ".flv;FlashVideoFile");

    bool IsChanged=false;
    int32s ShellExtension=Config.Read(_T("ShellExtension")).To_int32s();
    for (size_t I1=0; I1<Liste.size(); I1++)
    {
        //Open (or create) a extension. Create only if Sheel extension is wanted
        if (Reg->OpenKey(Liste(I1, 0).c_str(), ShellExtension))
        {
            //test if extension is known
            AnsiString Player=Reg->ReadString(_T(""));
            if (Player=="")
            {
                //extension not known, will use our default
                Player=Liste(I1, 1).c_str();
                try {Reg->WriteString(_T(""), Player);} catch (...){}
                IsChanged=true;
            }
            Reg->CloseKey();

            //Test if MediaInfo shell extension is known
            if (Reg->OpenKey(Player+_T("\\Shell\\MediaInfo\\Command"), false))
            {
                //MediaInfo shell extension is known
                if (Config.Read(_T("ShellExtension")).To_int32s())
                {
                    //test if good writing
                    AnsiString ShellExtensionToWtrite="\"" + Application->ExeName +"\" \"%1\"";
                    AnsiString ShellExtension=Reg->ReadString(_T("")).c_str();
                    if (ShellExtension!=ShellExtensionToWtrite)
                    {
                        //This is not the good shell extension, writing new one
                        try {Reg->WriteString(_T(""), ShellExtensionToWtrite);} catch (...){}
                        IsChanged=true;
                    }
                }
                else
                {
                    //Should not be here, deleting
                    Reg->CloseKey();
                    Reg->DeleteKey(Player+"\\Shell\\MediaInfo");
                    Reg->DeleteKey(Player+"\\Shell\\Media Info");
                    IsChanged=true;
                }
                Reg->CloseKey();
            }
            else
            {
                //MediaInfo Shell extension is not known
                if (Config.Read(_T("ShellExtension")).To_int32s())
                {
                    //Create it
                    Reg->DeleteKey(Player+"\\Shell\\Media Info"); //Delete the lod version if it exists
                    Reg->OpenKey(Player+_T("\\Shell\\MediaInfo\\Command"), true);
                    AnsiString ShellExtensionToWtrite="\"" + Application->ExeName +"\" \"%1\"";
                    try {Reg->WriteString(_T(""), ShellExtensionToWtrite);} catch (...){}
                    Reg->CloseKey();
                    IsChanged=true;
                }
            }
        }
    }

    //end
    Reg->Free();
    if (IsChanged)
        SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);

    return 1;
}

//---------------------------------------------------------------------------
int Preferences::ShellToolTip()
{
    //Done in the GUI for performance. TODO : analyse only if this has changed
    return 1;
}

//***************************************************************************
// Translations
//***************************************************************************

//---------------------------------------------------------------------------
ZenLib::Ztring &Preferences::Translate(ZenLib::Ztring Name)
{
    size_t Pos=Details[Language].Find(Name, 0, 0, _T("=="), Ztring_CaseSensitive);

    //If not in the language, search for English language
    if (Pos==-1 || Details[Language][Pos].size()<2)
        return Details[Language_English](Name);
    else
        return Details[Language](Pos)(1);
}


