// GUI_Preferences_Custom - Preferences interface of MediaInfo
// Copyright (C) 2002-2011 MediaArea.net SARL, Info@MediaArea.net
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
// Compilation condition
#ifndef MEDIAINFOGUI_PREFS_NO
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "GUI_Preferences_Custom.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifdef MEDIAINFO_DLL_RUNTIME
    #include "MediaInfoDLL/MediaInfoDLL.h"
    #define MediaInfoNameSpace MediaInfoDLL
#elif defined MEDIAINFO_DLL_STATIC
    #include "MediaInfoDLL/MediaInfoDLL_Static.h"
    #define MediaInfoNameSpace MediaInfoDLL
#else
    #include "MediaInfo/MediaInfoList.h"
    #define MediaInfoNameSpace MediaInfoLib
#endif
#include "Common/Preferences.h"
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
__fastcall TPreferences_CustomF::TPreferences_CustomF(TComponent* Owner)
    : TForm(Owner)
{
    ItemIndex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TPreferences_CustomF::ListeChange(TObject *Sender)
{
    //Save modification
    Ztring C1=Memo->Text.c_str();
    C1.FindAndReplace(_T("\r\n"), _T("\\r\\n"));
    if (ItemIndex!=-1)
        EditedCustom(ItemIndex, 1)=C1;
    ItemIndex=Liste->ItemIndex;

    //Show new item
    C1=EditedCustom.Read(ItemIndex, 1);
    C1.FindAndReplace(_T("\\r\\n"), _T("\r\n"));
    Memo->Text=C1.c_str();

    //Manage list of options
    Infos->Items->Clear();
         if (Liste->ItemIndex==0)
        Infos_Parameters.Write(Ztring(MediaInfoNameSpace::MediaInfo::Option_Static(_T("Info_Parameters_CSV"))).SubString(Prefs->Translate(_T("General"))+_T("\r\n"), _T("\r\n\r\n")));
    else if (Liste->ItemIndex==1)
        Infos_Parameters.Write(Ztring(MediaInfoNameSpace::MediaInfo::Option_Static(_T("Info_Parameters_CSV"))).SubString(Prefs->Translate(_T("Video"))+_T("\r\n"), _T("\r\n\r\n")));
    else if (Liste->ItemIndex==2)
        Infos_Parameters.Write(Ztring(MediaInfoNameSpace::MediaInfo::Option_Static(_T("Info_Parameters_CSV"))).SubString(Prefs->Translate(_T("Audio"))+_T("\r\n"), _T("\r\n\r\n")));
    else if (Liste->ItemIndex==3)
        Infos_Parameters.Write(Ztring(MediaInfoNameSpace::MediaInfo::Option_Static(_T("Info_Parameters_CSV"))).SubString(Prefs->Translate(_T("Text"))+_T("\r\n"), _T("\r\n\r\n")));
    else if (Liste->ItemIndex==4)
        Infos_Parameters.Write(Ztring(MediaInfoNameSpace::MediaInfo::Option_Static(_T("Info_Parameters_CSV"))).SubString(Prefs->Translate(_T("Chapters"))+_T("\r\n"), _T("")));
    else
        Infos_Parameters.clear();

    for (size_t Pos=0; Pos<Infos_Parameters.size(); Pos++)
        Infos->Items->Add(Infos_Parameters.Read(Pos, 0).c_str());
}
//---------------------------------------------------------------------------
void __fastcall TPreferences_CustomF::OKClick(TObject *Sender)
{
    ListeChange(NULL);
    EditedCustom.Save();
}
//---------------------------------------------------------------------------

int TPreferences_CustomF::Run(const Ztring &Name)
{
    EditedCustom.Load(Prefs->BaseFolder+Prefs->FolderNames[Prefs_Custom]+_T("\\")+Name+_T(".csv"));

    ListeChange(NULL);

    return ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TPreferences_CustomF::InfosChange(TObject *Sender)
{
    AnsiString S1=Memo->Text;
    AnsiString S2=AnsiString(_T("%"))+Infos->Text+("%");
    S1.Insert(S2, Memo->SelStart+1);
    Memo->Text=S1;
}
//---------------------------------------------------------------------------

void __fastcall TPreferences_CustomF::FormResize(TObject *Sender)
{
    Infos->Top=ClientHeight-Infos->Height;
    Repeat->Top=Infos->Top;
    Memo->Width=ClientWidth-Memo->Left;
    Memo->Height=Infos->Top-Memo->Top;
    OK->Left=ClientWidth-OK->Width;
    Cancel->Left=OK->Left-Cancel->Width;
    Help->Left=ClientWidth-75;
    Help->Top=ClientHeight-Help->Height;
}
//---------------------------------------------------------------------------

void __fastcall TPreferences_CustomF::HelpClick(TObject *Sender)
{
    TForm* Form=new TForm(this);
    Form->Caption="Help on Custom text";
    Form->Caption="Help on Custom text";
    Form->Width=600;
    Form->Height=300;
    Form->BorderIcons<<biSystemMenu;
    TMemo* Memo=new TMemo(Form);
    Memo->Parent=Form;
    Memo->Width=Form->ClientWidth;
    Memo->Height=Form->ClientHeight;
    Memo->Text= "Availiable scripting methods :\r\n"
                "- %A% : inserts the tag A.\r\n"
                "- [A %B% C %D%] : inserts \"A %B% C %D%\" if tag B (the first tag) is available. If not, inserts nothing\r\n"
                "- $if(%A%,B,C) : inserts B if tag A is availbale. If not, inserts C.\r\n"
                "\r\n"
                "Sometimes, there are reserved characters.\r\n"
                "You can replace x with \\x\r\n"
                "Known reserved character : \\\, \\[, \\], \\, (comma), \\;, \\(; \\)\r\n"
                "\r\n"
                "Known parameters are :\r\n";
    Memo->Text=Memo->Text+MediaInfoNameSpace::MediaInfo::Option_Static(_T("Info_Parameters_CSV")).c_str();
    Form->ShowModal();
}

//***************************************************************************
// C++
//***************************************************************************

#endif //MEDIAINFOGUI_PREFS_NO

