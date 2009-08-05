@rem echo off

@rem --- Clean up ---
del   MediaArea_DV_Analyzer_GUI_Windows_i386.exe
del   MediaArea_DV_Analyzer_GUI_Windows_i386_WithoutInstaller.7z
rmdir MediaArea_DV_Analyzer_GUI_Windows_i386 /S /Q
mkdir MediaArea_DV_Analyzer_GUI_Windows_i386


@rem --- Preparing ---
copy BCB\GUI\MediaArea_DV_Analyzer_GUI.exe BCB\GUI\MediaInfo.exe

@rem --- Copying : Exe ---
copy  ..\Project\BCB\GUI\Release_Build\MediaArea_DV_Analyzer_GUI.exe MediaArea_DV_Analyzer_GUI_Windows_i386\MediaInfo.exe
xcopy ..\..\MediaInfoLib\Project\MSVC2005\DLL\Win32\Release\MediaInfo.dll MediaArea_DV_Analyzer_GUI_Windows_i386\ /S
xcopy ..\..\MediaInfoLib\Project\MSVC\ShellExtension\Win32\Release\MediaInfo_InfoTip.dll MediaArea_DV_Analyzer_GUI_Windows_i386\ /S

@rem --- Copying : Plugins ---
xcopy ..\Source\Ressource\Plugin\* MediaArea_DV_Analyzer_GUI_Windows_i386\Plugin\ /S

@rem --- Copying : Information files ---
copy ..\License.html MediaArea_DV_Analyzer_GUI_Windows_i386\
copy ..\History_GUI.txt MediaArea_DV_Analyzer_GUI_Windows_i386\History.txt
copy ReadMe_GUI_Windows.txt MediaArea_DV_Analyzer_GUI_Windows_i386\ReadMe.txt


rem --- Compressing Archive ---
cd MediaArea_DV_Analyzer_GUI_Windows_i386\
..\..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -t7z -mx9 ..\MediaArea_DV_Analyzer_GUI_Windows_i386_WithoutInstaller.7z *
cd ..

rem --- Installer ---
copy ..\Project\BCB\GUI\Release_Build\MediaArea_DV_Analyzer_GUI.exe BCB\GUI\MediaInfo.exe
..\..\Shared\Binary\Windows_i386\NSIS\makensis ..\Source\Install\MediaArea_DV_Analyzer_GUI_Windows_i386.nsi

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir MediaArea_DV_Analyzer_GUI_Windows_i386\ /S /Q
:SkipCleanUp