#! /bin/sh

#-----------------------------------------------------------------------
# Clean up
test -e MediaArea_DV_Analyzer_GUI_GNU_FromSource.tar     && rm    MediaArea_DV_Analyzer_GUI_GNU_FromSource.tar
test -e MediaArea_DV_Analyzer_GUI_GNU_FromSource.tar.bz2 && rm    MediaArea_DV_Analyzer_GUI_GNU_FromSource.tar.bz2
test -d MediaArea_DV_Analyzer_GUI_GNU_FromSource         && rm -r MediaArea_DV_Analyzer_GUI_GNU_FromSource
mkdir MediaArea_DV_Analyzer_GUI_GNU_FromSource


#-----------------------------------------------------------------------
# Preparing : Project
cd ../Project/GNU/GUI
chmod u+x autogen
./autogen
cd ../../../Release


#-----------------------------------------------------------------------
# Copying : Project
mkdir -p MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI
cp ../Project/GNU/GUI/aclocal.m4 MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/autogen MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/config.guess MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/config.sub MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/configure MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/configure.ac MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/depcomp MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/install-sh MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/ltmain.sh MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/Makefile.am MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/Makefile.in MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/missing MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/wxwin.m4 MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/dvanalyzer-gui.spec  MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/dvanalyzer-gui.desktop MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/dvanalyzer-gui.kde3.desktop MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/dvanalyzer-gui.kde4.desktop MediaArea_DV_Analyzer_GUI_GNU_FromSource/Project/GNU/GUI/

#-----------------------------------------------------------------------
# Copying : Source
mkdir -p MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/Common
cp -r ../Source/Common/*.h MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/Common/
cp -r ../Source/Common/*.cpp MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/Common/
mkdir -p MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/CLI
cp -r ../Source/CLI/*.h MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/CLI/
cp -r ../Source/CLI/*.cpp MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/CLI/
mkdir -p MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/GUI/Common
cp -r ../Source/GUI/Common/*.h MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/GUI/Common/
cp -r ../Source/GUI/Common/*.cpp MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/GUI/Common/
mkdir -p MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/GUI/WxWidgets
cp -r ../Source/GUI/WxWidgets/*.h MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/GUI/WxWidgets/
cp -r ../Source/GUI/WxWidgets/*.cpp MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/GUI/WxWidgets/
mkdir -p MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/Ressource/Image/Menu
cp -r ../Source/Ressource/Image/*.png MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/Ressource/Image/
cp -r ../Source/Ressource/Image/*.xpm MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/Ressource/Image/
cp -r ../Source/Ressource/Image/Menu/*.xpm MediaArea_DV_Analyzer_GUI_GNU_FromSource/Source/Ressource/Image/Menu/

#-----------------------------------------------------------------------
# Copying : Release
mkdir -p MediaArea_DV_Analyzer_GUI_GNU_FromSource/Release
cp Release_GUI_GNU.sub MediaArea_DV_Analyzer_GUI_GNU_FromSource/Release/
cp *.sh MediaArea_DV_Analyzer_GUI_GNU_FromSource/Release/
chmod u+x MediaArea_DV_Analyzer_GUI_GNU_FromSource/Release/*.sh

#-----------------------------------------------------------------------
# Copying : Information
cp ../License.html MediaArea_DV_Analyzer_GUI_GNU_FromSource/
cp ../History_GUI.txt MediaArea_DV_Analyzer_GUI_GNU_FromSource/
dos2unix MediaArea_DV_Analyzer_GUI_GNU_FromSource/History_GUI.txt
cp ReadMe_GUI_Linux.txt MediaArea_DV_Analyzer_GUI_GNU_FromSource/Release/
cp ReadMe_GUI_Mac.txt MediaArea_DV_Analyzer_GUI_GNU_FromSource/Release/


#-----------------------------------------------------------------------
# Preparing Archive : MediaArea_DV_Analyzer
mv MediaArea_DV_Analyzer_GUI_GNU_FromSource MediaArea_DV_Analyzer
mkdir MediaArea_DV_Analyzer_GUI_GNU_FromSource
mv MediaArea_DV_Analyzer MediaArea_DV_Analyzer_GUI_GNU_FromSource/

#-----------------------------------------------------------------------
# Preparing Archive : From MediaInfoLib
cd ../../MediaInfoLib/Release
. ./Release_Lib_GNU_FromSource.sh
tar xf MediaInfo_Lib_GNU_FromSource.tar.bz2
rm MediaInfo_Lib_GNU_FromSource.tar.bz2
cd ../../MediaArea_DV_Analyzer/Release
mv ../../MediaInfoLib/Release/MediaInfo_Lib_GNU_FromSource MediaArea_DV_Analyzer_GUI_GNU_FromSource/MediaInfoLib

#-----------------------------------------------------------------------
# Preparing Archive : From ZenLib
cd ../../ZenLib/Release
. ./Release_GNU_FromSource.sh
tar xf ZenLib_GNU_FromSource.tar.bz2
rm ZenLib_GNU_FromSource.tar.bz2
cd ../../MediaArea_DV_Analyzer/Release
mv ../../ZenLib/Release/ZenLib_GNU_FromSource MediaArea_DV_Analyzer_GUI_GNU_FromSource/ZenLib

#-----------------------------------------------------------------------
# Preparing Archive : From Shared
mkdir -p MediaArea_DV_Analyzer_GUI_GNU_FromSource/Shared/Project/_Common
cp -r ../../Shared/Project/_Common/*.sh MediaArea_DV_Analyzer_GUI_GNU_FromSource/Shared/Project/_Common
mkdir -p MediaArea_DV_Analyzer_GUI_GNU_FromSource/Shared/Project/ZLib
cp -r ../../Shared/Project/ZLib/*.sh MediaArea_DV_Analyzer_GUI_GNU_FromSource/Shared/Project/ZLib
mkdir -p MediaArea_DV_Analyzer_GUI_GNU_FromSource/Shared/Project/WxWidgets
cp -r ../../Shared/Project/WxWidgets/*.sh MediaArea_DV_Analyzer_GUI_GNU_FromSource/Shared/Project/WxWidgets

#-----------------------------------------------------------------------
# Preparing Archive : Automation
cp ../Project/GNU/GUI/AddThisToRoot_GUI_compile.sh MediaArea_DV_Analyzer_GUI_GNU_FromSource/GUI_Compile.sh
chmod u+x MediaArea_DV_Analyzer_GUI_GNU_FromSource/GUI_Compile.sh


#-----------------------------------------------------------------------
# Compressing Archive
tar jchf MediaArea_DV_Analyzer_GUI_GNU_FromSource.tar.bz2 MediaArea_DV_Analyzer_GUI_GNU_FromSource/*

#-----------------------------------------------------------------------
# Clean up
rm -r MediaArea_DV_Analyzer_GUI_GNU_FromSource
