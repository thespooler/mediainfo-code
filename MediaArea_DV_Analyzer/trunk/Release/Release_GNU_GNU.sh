#! /bin/sh

#-----------------------------------------------------------------------
# Clean up
rm    MediaArea_DV_Analyzer_GUI_GNU.tar
rm    MediaArea_DV_Analyzer_GUI_GNU.tar.bz2
rm -r MediaArea_DV_Analyzer_GUI_GNU
mkdir MediaArea_DV_Analyzer_GUI_GNU

#-----------------------------------------------------------------------
# Copying : Exe
cp ../Project/GNU/GUI/MediaInfo MediaArea_DV_Analyzer_GUI_GNU/MediaInfo

#-----------------------------------------------------------------------
# Copying : Information file
cp ../License.html MediaArea_DV_Analyzer_GUI_GNU/
cp ../History_GUI.txt MediaArea_DV_Analyzer_GUI_GNU/History.txt
cp ReadMe_GUI_Linux.txt MediaArea_DV_Analyzer_GUI_GNU/ReadMe.txt

#-----------------------------------------------------------------------
# Compressing Archive
tar jcf MediaArea_DV_Analyzer_GUI_GNU.tar.bz2 MediaArea_DV_Analyzer_GUI_GNU
rm MediaArea_DV_Analyzer_GUI_GNU.tar

#-----------------------------------------------------------------------
# Clean up
#if "%1"=="SkipCleanUp" goto SkipCleanUp
rm -r MediaArea_DV_Analyzer_GUI_GNU
#:SkipCleanUp