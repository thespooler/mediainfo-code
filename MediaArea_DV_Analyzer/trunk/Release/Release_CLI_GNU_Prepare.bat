@echo off

rem --- Clean up ---
del MediaArea_DV_Analyzer_CLI_GNU_Prepare.7z
rmdir MediaArea_DV_Analyzer_CLI_GNU_Prepare /S /Q
mkdir MediaArea_DV_Analyzer_CLI_GNU_Prepare


rem --- Copying : Sources ---
xcopy ..\Source\Common\*.cpp MediaArea_DV_Analyzer_CLI_GNU_Prepare\Source\Common\ /S
xcopy ..\Source\Common\*.h MediaArea_DV_Analyzer_CLI_GNU_Prepare\Source\Common\ /S
xcopy ..\Source\CLI\*.cpp MediaArea_DV_Analyzer_CLI_GNU_Prepare\Source\CLI\ /S
xcopy ..\Source\CLI\*.h MediaArea_DV_Analyzer_CLI_GNU_Prepare\Source\CLI\ /S

rem --- Copying : Projects ---
xcopy ..\Project\GNU\CLI\autogen MediaArea_DV_Analyzer_CLI_GNU_Prepare\Project\GNU\CLI\ /S
xcopy ..\Project\GNU\CLI\configure.ac MediaArea_DV_Analyzer_CLI_GNU_Prepare\Project\GNU\CLI\ /S
xcopy ..\Project\GNU\CLI\Makefile.am MediaArea_DV_Analyzer_CLI_GNU_Prepare\Project\GNU\CLI\ /S
xcopy ..\Project\GNU\CLI\wxwin.m4 MediaArea_DV_Analyzer_CLI_GNU_Prepare\Project\GNU\CLI\ /S
xcopy ..\Project\GNU\CLI\AddThisToRoot_CLI_compile.sh MediaArea_DV_Analyzer_CLI_GNU_Prepare\Project\GNU\CLI\ /S
xcopy ..\Project\GNU\CLI\dvanalyzer-cli.spec MediaArea_DV_Analyzer_CLI_GNU_Prepare\Project\GNU\CLI\ /S

rem --- Copying : Release ---
xcopy Release_CLI_GNU.sub MediaArea_DV_Analyzer_CLI_GNU_Prepare\Release\
xcopy Release_CLI_*.sh MediaArea_DV_Analyzer_CLI_GNU_Prepare\Release\

rem --- Copying : Information files ---
copy ..\History_CLI.txt MediaArea_DV_Analyzer_CLI_GNU_Prepare\
copy ..\License.html MediaArea_DV_Analyzer_CLI_GNU_Prepare\
copy ReadMe_CLI_Linux.txt MediaArea_DV_Analyzer_CLI_GNU_Prepare\Release\
copy ReadMe_CLI_Mac.txt MediaArea_DV_Analyzer_CLI_GNU_Prepare\Release\


rem --- Preparing Archive : MediaArea_DV_Analyzer ---
move MediaArea_DV_Analyzer_CLI_GNU_Prepare MediaArea_DV_Analyzer
mkdir MediaArea_DV_Analyzer_CLI_GNU_Prepare
move MediaArea_DV_Analyzer MediaArea_DV_Analyzer_CLI_GNU_Prepare

rem --- Preparing Archive : MediaInfoLib ---
cd ..\..\MediaInfoLib\Release
call Release_Lib_GNU_Prepare.bat SkipCleanUp SkipCompression
cd ..\..\MediaArea_DV_Analyzer\Release
move ..\..\MediaInfoLib\Release\MediaInfo_Lib_GNU_Prepare MediaArea_DV_Analyzer_CLI_GNU_Prepare\MediaInfoLib

rem --- Preparing Archive : ZenLib ---
cd ..\..\ZenLib\Release
call Release_GNU_Prepare.bat SkipCleanUp SkipCompression
cd ..\..\MediaArea_DV_Analyzer\Release
move ..\..\ZenLib\Release\ZenLib_GNU_Prepare MediaArea_DV_Analyzer_CLI_GNU_Prepare\ZenLib

rem --- Shared ---
mkdir MediaArea_DV_Analyzer_CLI_GNU_Prepare\Shared
xcopy ..\..\Shared\Project\_Common\* MediaArea_DV_Analyzer_CLI_GNU_Prepare\Shared\Project\_Common\ /S
xcopy ..\..\Shared\Project\ZLib\*.sh MediaArea_DV_Analyzer_CLI_GNU_Prepare\Shared\Project\ZLib\ /S
xcopy ..\..\Shared\Project\ZLib\Template\projects\GNU\* MediaArea_DV_Analyzer_CLI_GNU_Prepare\Shared\Project\ZLib\Template\projects\GNU\ /S
xcopy ..\..\Shared\Project\WxWidgets\*.sh MediaArea_DV_Analyzer_CLI_GNU_Prepare\Shared\Project\WxWidgets\ /S


rem --- Compressing Archive ---
if "%2"=="SkipCompression" goto SkipCompression
..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -t7z -mx9 MediaArea_DV_Analyzer_CLI_GNU_Prepare.7z MediaArea_DV_Analyzer_CLI_GNU_Prepare\*
:SkipCompression

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir MediaArea_DV_Analyzer_CLI_GNU_Prepare /S /Q
:SkipCleanUp
