@echo off

rem --- Clean up ---
del MediaArea_DV_Analyzer_GUI_GNU_Prepare.7z
rmdir MediaArea_DV_Analyzer_GUI_GNU_Prepare /S /Q
mkdir MediaArea_DV_Analyzer_GUI_GNU_Prepare


rem --- Copying : Sources ---
xcopy ..\Source\Common\*.cpp MediaArea_DV_Analyzer_GUI_GNU_Prepare\Source\Common\ /S
xcopy ..\Source\Common\*.h MediaArea_DV_Analyzer_GUI_GNU_Prepare\Source\Common\ /S
xcopy ..\Source\GUI\Common\*.cpp MediaArea_DV_Analyzer_GUI_GNU_Prepare\Source\GUI\Common\ /S
xcopy ..\Source\GUI\Common\*.h MediaArea_DV_Analyzer_GUI_GNU_Prepare\Source\GUI\Common\ /S
xcopy ..\Source\GUI\WxWidgets\*.cpp MediaArea_DV_Analyzer_GUI_GNU_Prepare\Source\GUI\WxWidgets\ /S
xcopy ..\Source\GUI\WxWidgets\*.h MediaArea_DV_Analyzer_GUI_GNU_Prepare\Source\GUI\WxWidgets\ /S
xcopy ..\Source\*.png MediaArea_DV_Analyzer_GUI_GNU_Prepare\Source\ /S
xcopy ..\Source\*.xpm MediaArea_DV_Analyzer_GUI_GNU_Prepare\Source\ /S

rem --- Copying : Projects ---
xcopy ..\Project\GNU\GUI\autogen MediaArea_DV_Analyzer_GUI_GNU_Prepare\Project\GNU\GUI\ /S
xcopy ..\Project\GNU\GUI\configure.ac MediaArea_DV_Analyzer_GUI_GNU_Prepare\Project\GNU\GUI\ /S
xcopy ..\Project\GNU\GUI\Makefile.am MediaArea_DV_Analyzer_GUI_GNU_Prepare\Project\GNU\GUI\ /S
xcopy ..\Project\GNU\GUI\wxwin.m4 MediaArea_DV_Analyzer_GUI_GNU_Prepare\Project\GNU\GUI\ /S
xcopy ..\Project\GNU\GUI\AddThisToRoot_GUI_compile.sh MediaArea_DV_Analyzer_GUI_GNU_Prepare\Project\GNU\GUI\ /S
xcopy ..\Project\GNU\GUI\dvanalyzer-gui.* MediaArea_DV_Analyzer_GUI_GNU_Prepare\Project\GNU\GUI\ /S
copy ..\Source\Ressource\Image\MediaInfo.png MediaArea_DV_Analyzer_GUI_GNU_Prepare\Project\GNU\GUI\mediainfo.png

rem --- Copying : Release ---
xcopy Release_GUI_GNU.sub MediaArea_DV_Analyzer_GUI_GNU_Prepare\Release\
xcopy Release_GUI_*.sh MediaArea_DV_Analyzer_GUI_GNU_Prepare\Release\

rem --- Copying : Information files ---
copy ..\History_GUI.txt MediaArea_DV_Analyzer_GUI_GNU_Prepare\
copy ..\License.html MediaArea_DV_Analyzer_GUI_GNU_Prepare\
copy ReadMe_GUI_Linux.txt MediaArea_DV_Analyzer_GUI_GNU_Prepare\Release\
copy ReadMe_GUI_Mac.txt MediaArea_DV_Analyzer_GUI_GNU_Prepare\Release\


rem --- Preparing Archive : MediaArea_DV_Analyzer ---
move MediaArea_DV_Analyzer_GUI_GNU_Prepare MediaArea_DV_Analyzer
mkdir MediaArea_DV_Analyzer_GUI_GNU_Prepare
move MediaArea_DV_Analyzer MediaArea_DV_Analyzer_GUI_GNU_Prepare

rem --- Preparing Archive : MediaInfoLib ---
cd ..\..\MediaInfoLib\Release
call Release_Lib_GNU_Prepare.bat SkipCleanUp SkipCompression
cd ..\..\MediaArea_DV_Analyzer\Release
move ..\..\MediaInfoLib\Release\MediaInfo_Lib_GNU_Prepare MediaArea_DV_Analyzer_GUI_GNU_Prepare\MediaInfoLib

rem --- Preparing Archive : ZenLib ---
cd ..\..\ZenLib\Release
call Release_GNU_Prepare.bat SkipCleanUp SkipCompression
cd ..\..\MediaArea_DV_Analyzer\Release
move ..\..\ZenLib\Release\ZenLib_GNU_Prepare MediaArea_DV_Analyzer_GUI_GNU_Prepare\ZenLib

rem --- Shared ---
mkdir MediaArea_DV_Analyzer_GUI_GNU_Prepare\Shared
xcopy ..\..\Shared\Project\_Common\* MediaArea_DV_Analyzer_GUI_GNU_Prepare\Shared\Project\_Common\ /S
xcopy ..\..\Shared\Project\ZLib\*.sh MediaArea_DV_Analyzer_GUI_GNU_Prepare\Shared\Project\ZLib\ /S
xcopy ..\..\Shared\Project\WxWidgets\*.sh MediaArea_DV_Analyzer_GUI_GNU_Prepare\Shared\Project\WxWidgets\ /S


rem --- Compressing Archive ---
if "%2"=="SkipCompression" goto SkipCompression
..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -t7z -mx9 MediaArea_DV_Analyzer_GUI_GNU_Prepare.7z MediaArea_DV_Analyzer_GUI_GNU_Prepare\*
:SkipCompression

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir MediaArea_DV_Analyzer_GUI_GNU_Prepare /S /Q
:SkipCleanUp
