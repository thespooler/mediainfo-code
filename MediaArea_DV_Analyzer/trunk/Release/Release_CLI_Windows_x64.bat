@rem echo off

@rem --- Clean up ---
del   MediaArea_DV_Analyzer_CLI_Windows_x64.zip
rmdir MediaArea_DV_Analyzer_CLI_Windows_x64 /S /Q
mkdir MediaArea_DV_Analyzer_CLI_Windows_x64

rem --- Copying : Exe ---
xcopy MSVCx64\CLI\MediaInfo.exe MediaArea_DV_Analyzer_CLI_Windows_x64\ /S
xcopy ..\..\MediaInfoLib\Release\MSVCx64\Dll\MediaInfo.dll MediaArea_DV_Analyzer_CLI_Windows_x64\ /S

rem --- Copying : Plugins ---
xcopy ..\Source\Ressource\Plugin\Custom\* MediaArea_DV_Analyzer_CLI_Windows_x64\Plugin\Custom\ /S

rem --- Copying : Information files ---
copy ..\License.html MediaArea_DV_Analyzer_CLI_Windows_x64\
copy ..\History_CLI.txt MediaArea_DV_Analyzer_CLI_Windows_x64\History.txt
copy Readme_CLI_Windows.txt MediaArea_DV_Analyzer_CLI_Windows_x64\ReadMe.txt


rem --- Compressing Archive ---
cd MediaArea_DV_Analyzer_CLI_Windows_x64\
..\..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -tzip ..\MediaArea_DV_Analyzer_CLI_Windows_x64.zip *
cd ..

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir MediaArea_DV_Analyzer_CLI_Windows_x64\ /S /Q
:SkipCleanUp
