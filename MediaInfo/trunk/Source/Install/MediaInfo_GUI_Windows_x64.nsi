; Request application privileges for Windows Vista
RequestExecutionLevel admin

; Some defines
!define PRODUCT_NAME "MediaInfo"
!define PRODUCT_PUBLISHER "MediaArea.net"
!define PRODUCT_VERSION "0.7.17"
!define PRODUCT_VERSION4 "0.7.17.0"
!define PRODUCT_WEB_SITE "http://mediainfo.sourceforge.net"
!define COMPANY_REGISTRY "Software\MediaArea.net"
!define PRODUCT_REGISTRY "Software\MediaArea.net\MediaInfo"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\MediaInfo.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; Compression
SetCompressor /FINAL /SOLID lzma

; x64 stuff
!include "x64.nsh"

; Modern UI
!include "MUI.nsh"
!define MUI_ABORTWARNING
!define MUI_ICON "..\..\Source\Ressource\Image\MediaInfo_TinyOnly.ico"

; Language Selection Dialog Settings
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; Directory page
!insertmacro MUI_PAGE_DIRECTORY

; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\MediaInfo.exe"
!insertmacro MUI_PAGE_FINISH
; Uninstaller pages
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; Language files
!insertmacro MUI_LANGUAGE "Albanian"
!insertmacro MUI_LANGUAGE "Belarusian"
!insertmacro MUI_LANGUAGE "Catalan"
!insertmacro MUI_LANGUAGE "Croatian"
!insertmacro MUI_LANGUAGE "Czech"
!insertmacro MUI_LANGUAGE "Dutch"
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Farsi"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "Greek"
!insertmacro MUI_LANGUAGE "Korean"
!insertmacro MUI_LANGUAGE "Hungarian"
!insertmacro MUI_LANGUAGE "Italian"
!insertmacro MUI_LANGUAGE "Japanese"
!insertmacro MUI_LANGUAGE "Lithuanian"
!insertmacro MUI_LANGUAGE "Polish"
!insertmacro MUI_LANGUAGE "Portuguese"
!insertmacro MUI_LANGUAGE "PortugueseBR"
!insertmacro MUI_LANGUAGE "Romanian"
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "Spanish"
!insertmacro MUI_LANGUAGE "Swedish"
!insertmacro MUI_LANGUAGE "Thai"
!insertmacro MUI_LANGUAGE "TradChinese"
!insertmacro MUI_LANGUAGE "Turkish"

; Info
VIProductVersion "${PRODUCT_VERSION4}"
VIAddVersionKey "ProductName" "${PRODUCT_NAME} (GUI Windows x64)" 
VIAddVersionKey "Comments" "All about your audio and video files"
VIAddVersionKey "CompanyName" "MediaArea.net"
VIAddVersionKey "LegalTrademarks" "GPL license" 
VIAddVersionKey "LegalCopyright" "" 
VIAddVersionKey "FileDescription" "All about your audio and video files"
VIAddVersionKey "FileVersion" "${PRODUCT_VERSION}"
BrandingText " "

; Modern UI end

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "..\..\Release\MediaInfo_GUI_${PRODUCT_VERSION}_Windows_x64.exe"
InstallDir "$PROGRAMFILES64\MediaInfo"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails nevershow
ShowUnInstDetails nevershow

Function .onInit
  ${If} ${RunningX64}
    SetRegView 64
  ${Else}
    MessageBox MB_OK|MB_ICONSTOP 'You are trying to install the 64-bit version of ${PRODUCT_NAME} on 32-bit Windows.$\r$\nPlease download and use the 32-bit version instead.$\r$\nClick OK to quit Setup.'
    Quit
  ${EndIf}
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

Section "SectionPrincipale" SEC01
  SetOverwrite ifnewer
  SetOutPath "$INSTDIR"
  CreateDirectory "$SMPROGRAMS\MediaInfo"
  CreateShortCut "$SMPROGRAMS\MediaInfo\MediaInfo.lnk" "$INSTDIR\MediaInfo.exe" "" "" "" "" "" "MediaInfo"
  File "/oname=MediaInfo.exe" "..\..\Project\BCB\GUI\Release_Build\MediaInfo_GUI_x64.exe"
  File "..\..\..\MediaInfoLib\Project\MSVC\ShellExtension\x64\Release\MediaInfo_InfoTip.dll"
  File "..\..\..\MediaInfoLib\Project\MSVC\DLL\x64\Release\MediaInfo.dll"
  File  "/oname=MediaInfo_i386.dll""..\..\..\MediaInfoLib\Project\MSVC2005\DLL\Win32\Release\MediaInfo.dll"
  File "/oname=History.txt" "..\..\History_GUI.txt"
  File "..\..\License.html"
  File  "/oname=ReadMe.txt""..\..\Release\ReadMe_GUI_Windows.txt"
  SetOverwrite try
  SetOutPath "$INSTDIR\Plugin\Custom"
  File "..\Ressource\Plugin\Custom\*.csv"
  SetOutPath "$INSTDIR\Plugin\Language"
  File "..\Ressource\Plugin\Language\*.csv"
  SetOutPath "$INSTDIR\Plugin\Sheet"
  File "..\Ressource\Plugin\Sheet\*.csv"
  SetOutPath "$INSTDIR\Plugin\Tree"
  File "..\Ressource\Plugin\Tree\*.csv"

  # Delete files that might be present from older installation
  Delete "$INSTDIR\History_GUI.txt"
  Delete "$INSTDIR\Licence.txt"
  Delete "$INSTDIR\Licence.html"
  Delete "$INSTDIR\License.txt"
  Delete "$INSTDIR\ReadMe_Windows.txt"
SectionEnd

Section -AdditionalIcons
  SetOutPath $INSTDIR
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\MediaInfo\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url" "" "" "" "" "" "Website"
  CreateShortCut "$SMPROGRAMS\MediaInfo\Uninstall.lnk" "$INSTDIR\uninst.exe" "" "" "" "" "" "Uninstall MediaInfo"
  CreateShortCut "$SMPROGRAMS\MediaInfo\History.lnk" "$INSTDIR\History.txt" "" "" "" "" "" "History"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\MediaInfo.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\MediaInfo.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
SectionEnd


Section Uninstall
  UnRegDLL "$INSTDIR\MediaInfo_InfoTip.dll"
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\MediaInfo.exe"
  Delete "$INSTDIR\MediaInfo_InfoTip.dll"
  Delete "$INSTDIR\MediaInfo.dll"
  Delete "$INSTDIR\MediaInfo_i386.dll"
  Delete "$INSTDIR\History.txt"
  Delete "$INSTDIR\License.html"
  Delete "$INSTDIR\ReadMe.txt"
  Delete "$INSTDIR\Plugin\MediaInfo.cfg"
  Delete "$INSTDIR\Plugin\Custom\*.csv"
  Delete "$INSTDIR\Plugin\Language\*.csv"
  Delete "$INSTDIR\Plugin\Sheet\*.csv"
  Delete "$INSTDIR\Plugin\Tree\*.csv"
  Delete "$SMPROGRAMS\MediaInfo\Uninstall.lnk"
  Delete "$SMPROGRAMS\MediaInfo\Website.lnk"
  Delete "$SMPROGRAMS\MediaInfo\MediaInfo.lnk"
  Delete "$SMPROGRAMS\MediaInfo\History.lnk"

  RMDir "$SMPROGRAMS\MediaInfo"
  RMDir "$INSTDIR\Plugin\Custom"
  RMDir "$INSTDIR\Plugin\Language"
  RMDir "$INSTDIR\Plugin\Sheet"
  RMDir "$INSTDIR\Plugin\Tree"
  RMDir "$INSTDIR\Plugin"
  RMDir "$INSTDIR"

  ReadRegStr $1 HKCR ".mkv" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mka" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mks" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".ogg" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".ogm" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".wav" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".avi" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".divx" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mpeg" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mpg" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".dat" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mpe" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".dat" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mpgx" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mpm" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".m1s" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".vob" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".m2s" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".ts" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".tp" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mp4" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".m4a" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mpgv" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mpv" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".m1v" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".m2v" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mp2" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mp3" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mpc" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mp+" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".asf" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".wmv" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".wma" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mov" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".qt" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".rm" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".rmvb" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".ra" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".ifo" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".ac3" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".dts" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".aac" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".ape" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".mac" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".flac" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".3gp" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".swf" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".flv" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".m2ts" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".gvi" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".3gpp" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".evo" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".eac3" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".dv" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".jp2" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR ".j2k" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ReadRegStr $1 HKCR "Folder" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"

  SetRegView 64
  DeleteRegKey HKLM "${PRODUCT_REGISTRY}"
  DeleteRegKey /ifempty HKLM "${COMPANY_REGISTRY}"
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd