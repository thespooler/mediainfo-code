@rem echo off

@rem --- Clean up ---
del   MediaArea_DV_Analyzer_GUI_Windows_x64.exe
del   MediaArea_DV_Analyzer_GUI_Windows_x64_WithoutInstaller.7z
rmdir MediaArea_DV_Analyzer_GUI_Windows_x64 /S /Q
mkdir MediaArea_DV_Analyzer_GUI_Windows_x64


@rem --- Copying : Exe ---
copy  ..\Project\BCB\GUI\Release_Build\MediaArea_DV_Analyzer_GUI_x64.exe MediaArea_DV_Analyzer_GUI_Windows_x64\MediaInfo.exe
xcopy ..\..\MediaInfoLib\Project\MSVC\DLL\x64\Release\MediaInfo.dll MediaArea_DV_Analyzer_GUI_Windows_x64\ /S
copy  ..\..\MediaInfoLib\Project\MSVC2005\DLL\Win32\Release\MediaInfo.dll MediaArea_DV_Analyzer_GUI_Windows_x64\MediaInfo_i386.dll
xcopy ..\..\MediaInfoLib\Project\MSVC\ShellExtension\x64\Release\MediaInfo_InfoTip.dll MediaArea_DV_Analyzer_GUI_Windows_x64\ /S

@rem --- Copying : Plugins ---
xcopy ..\Source\Ressource\Plugin\* MediaArea_DV_Analyzer_GUI_Windows_x64\Plugin\ /S

@rem --- Copying : Information files ---
copy ..\License.html MediaArea_DV_Analyzer_GUI_Windows_x64\
copy ..\History_GUI.txt MediaArea_DV_Analyzer_GUI_Windows_x64\History.txt
copy ReadMe_GUI_Windows.txt MediaArea_DV_Analyzer_GUI_Windows_x64\ReadMe.txt


rem --- Compressing Archive ---
cd MediaArea_DV_Analyzer_GUI_Windows_x64\
..\..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -t7z -mx9 ..\MediaArea_DV_Analyzer_GUI_Windows_x64_WithoutInstaller.7z *
cd ..

rem --- Installer ---
..\..\Shared\Binary\Windows_i386\NSIS\makensis ..\Source\Install\MediaArea_DV_Analyzer_GUI_Windows_x64.nsi

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir MediaArea_DV_Analyzer_GUI_Windows_x64\ /S /Q
:SkipCleanUp