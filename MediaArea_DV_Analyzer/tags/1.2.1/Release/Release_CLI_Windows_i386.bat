@rem echo off

@rem --- Clean up ---
del   MediaArea_DV_Analyzer_CLI_Windows_i386.zip
rmdir MediaArea_DV_Analyzer_CLI_Windows_i386 /S /Q
mkdir MediaArea_DV_Analyzer_CLI_Windows_i386

rem --- Copying : Exe ---
xcopy MSVC\CLI\MediaInfo.exe MediaArea_DV_Analyzer_CLI_Windows_i386\ /S
xcopy ..\..\MediaInfoLib\Release\MSVC2005\Dll\MediaInfo.dll MediaArea_DV_Analyzer_CLI_Windows_i386\ /S

rem --- Copying : Plugins ---
xcopy ..\Source\Ressource\Plugin\Custom\* MediaArea_DV_Analyzer_CLI_Windows_i386\Plugin\Custom\ /S

rem --- Copying : Information files ---
copy ..\License.html MediaArea_DV_Analyzer_CLI_Windows_i386\
copy ..\History_CLI.txt MediaArea_DV_Analyzer_CLI_Windows_i386\History.txt
copy Readme_CLI_Windows.txt MediaArea_DV_Analyzer_CLI_Windows_i386\ReadMe.txt

rem --- Compressing Archive ---
cd MediaArea_DV_Analyzer_CLI_Windows_i386\
..\..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -tzip ..\MediaArea_DV_Analyzer_CLI_Windows_i386.zip *
cd ..


rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir MediaArea_DV_Analyzer_CLI_Windows_i386\ /S /Q
:SkipCleanUp
