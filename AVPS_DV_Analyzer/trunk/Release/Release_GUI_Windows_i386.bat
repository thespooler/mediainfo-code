@rem echo off

@rem --- Clean up ---
del   AVPS_DV_Analyzer_GUI_Windows_i386.exe
del   AVPS_DV_Analyzer_GUI_Windows_i386_WithoutInstaller.7z
rmdir AVPS_DV_Analyzer_GUI_Windows_i386 /S /Q
mkdir AVPS_DV_Analyzer_GUI_Windows_i386


@rem --- Preparing ---
copy BCB\GUI\AVPS_DV_Analyzer_GUI.exe BCB\GUI\MediaInfo.exe

@rem --- Copying : Exe ---
copy  ..\Project\BCB\GUI\Release_Build\AVPS_DV_Analyzer_GUI.exe AVPS_DV_Analyzer_GUI_Windows_i386\MediaInfo.exe
xcopy ..\..\MediaInfoLib\Project\MSVC2005\DLL\Win32\Release\MediaInfo.dll AVPS_DV_Analyzer_GUI_Windows_i386\ /S
xcopy ..\..\MediaInfoLib\Project\MSVC\ShellExtension\Win32\Release\MediaInfo_InfoTip.dll AVPS_DV_Analyzer_GUI_Windows_i386\ /S

@rem --- Copying : Plugins ---
xcopy ..\Source\Ressource\Plugin\* AVPS_DV_Analyzer_GUI_Windows_i386\Plugin\ /S

@rem --- Copying : Information files ---
copy ..\License.html AVPS_DV_Analyzer_GUI_Windows_i386\
copy ..\History_GUI.txt AVPS_DV_Analyzer_GUI_Windows_i386\History.txt
copy ReadMe_GUI_Windows.txt AVPS_DV_Analyzer_GUI_Windows_i386\ReadMe.txt


rem --- Compressing Archive ---
cd AVPS_DV_Analyzer_GUI_Windows_i386\
..\..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -t7z -mx9 ..\AVPS_DV_Analyzer_GUI_Windows_i386_WithoutInstaller.7z *
cd ..

rem --- Installer ---
copy ..\Project\BCB\GUI\Release_Build\AVPS_DV_Analyzer_GUI.exe BCB\GUI\MediaInfo.exe
..\..\Shared\Binary\Windows_i386\NSIS\makensis ..\Source\Install\AVPS_DV_Analyzer_GUI_Windows_i386.nsi

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir AVPS_DV_Analyzer_GUI_Windows_i386\ /S /Q
:SkipCleanUp