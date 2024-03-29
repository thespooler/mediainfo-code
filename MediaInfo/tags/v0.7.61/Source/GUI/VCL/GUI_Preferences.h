// GUI_Preferences - Preferences interface of MediaInfo
// Copyright (C) 2002-2012 MediaArea.net SARL, Info@MediaArea.net
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU Library General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef GUI_PreferencesH
#define GUI_PreferencesH
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <StdCtrls.hpp>
#include "GUI_Main.h"
#include "Common/Preferences.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TPreferencesF : public TForm
{
__published:    // IDE-managed Components
    TButton *OK;
    TTreeView *Tree;
    TButton *Cancel;
    TPageControl *Page;
    TTabSheet *Setup;
    TLabel *Langue_C;
    TLabel *Output_C;
    TComboBox *General_Language_Sel;
    TComboBox *General_Output_Sel;
    TCheckBox *CB_CheckUpdate;
    TButton *General_Language_More;
    TButton *General_Output_More;
    TTabSheet *Setup_Advanced;
    TCheckBox *CB_ShowToolBar;
    TCheckBox *Advanced_CloseAllAuto;
    TTabSheet *Customize_Language;
    TLabel *Language_Caption;
    TButton *Language_New;
    TButton *Language_Delete;
    TButton *Language_Edit;
    TComboBox *Language_Sel;
    TTabSheet *Customize_Sheet;
    TLabel *Sheet_Caption;
    TComboBox *Sheet_Sel;
    TButton *Sheet_Delete;
    TButton *Sheet_Edit;
    TButton *Sheet_New;
    TTabSheet *Customize_TreeText;
    TLabel *Tree_NotYet;
    TTabSheet *Customize_Custom;
    TLabel *Custom_Caption;
    TButton *Custom_New;
    TButton *Custom_Edit;
    TButton *Custom_Delete;
    TComboBox *Custom_Sel;
    TTabSheet *Customize;
    TCheckBox *CB_ShowMenu;
    TCheckBox *CB_InfoTip;
    TCheckBox *CB_InscrireShell;
    TCheckBox *CB_InscrireShell_Folder;
    void __fastcall General_Language_SelChange(TObject *Sender);
    void __fastcall General_Output_SelChange(TObject *Sender);
    void __fastcall Custom_EditClick(TObject *Sender);
    void __fastcall Language_EditClick(TObject *Sender);
    void __fastcall OKClick(TObject *Sender);
    void __fastcall Custom_SelChange(TObject *Sender);
    void __fastcall CB_InscrireShellClick(TObject *Sender);
    void __fastcall CB_CheckUpdateClick(TObject *Sender);
    void __fastcall Language_NewClick(TObject *Sender);
    void __fastcall Language_DeleteClick(TObject *Sender);
    void __fastcall Custom_NewClick(TObject *Sender);
    void __fastcall Custom_DeleteClick(TObject *Sender);
    void __fastcall TreeChange(TObject *Sender, TTreeNode *Node);
    void __fastcall General_Language_MoreClick(TObject *Sender);
    void __fastcall General_Output_MoreClick(TObject *Sender);
    void __fastcall CB_ShowToolBarClick(TObject *Sender);
    void __fastcall Language_SelChange(TObject *Sender);
    void __fastcall Advanced_CloseAllAutoClick(TObject *Sender);
    void __fastcall Setup_GeneralShow(TObject *Sender);
    void __fastcall Setup_AdvancedShow(TObject *Sender);
    void __fastcall Customize_LanguageShow(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Customize_CustomShow(TObject *Sender);
    void __fastcall Sheet_SelChange(TObject *Sender);
    void __fastcall Sheet_DeleteClick(TObject *Sender);
    void __fastcall Sheet_EditClick(TObject *Sender);
    void __fastcall Sheet_NewClick(TObject *Sender);
    void __fastcall Customize_SheetShow(TObject *Sender);
    void __fastcall CB_ShowMenuClick(TObject *Sender);
    void __fastcall CB_InfoTipClick(TObject *Sender);
    void __fastcall CB_InscrireShell_FolderClick(TObject *Sender);
private:    // User declarations
public:        // User declarations
    __fastcall TPreferencesF(TComponent* Owner);
    void __fastcall ComboBox_Update(TComboBox *CB, Prefs_t List);
    void __fastcall ComboBox_SelChange(TComboBox *CB, Prefs_t List);
    void __fastcall GUI_Configure();
};
//---------------------------------------------------------------------------
extern PACKAGE TPreferencesF *PreferencesF;
//---------------------------------------------------------------------------
#endif
