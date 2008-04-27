#! /bin/sh

#-----------------------------------------------------------------------
# Clean up
test -e MediaInfo_GUI_GNU_FromSource.tar     && rm    MediaInfo_GUI_GNU_FromSource.tar
test -e MediaInfo_GUI_GNU_FromSource.tar.bz2 && rm    MediaInfo_GUI_GNU_FromSource.tar.bz2
test -d MediaInfo_GUI_GNU_FromSource         && rm -r MediaInfo_GUI_GNU_FromSource
mkdir MediaInfo_GUI_GNU_FromSource


#-----------------------------------------------------------------------
# Preparing : Project
cd ../Project/GNU/GUI
chmod u+x autogen
./autogen
cd ../../../Release


#-----------------------------------------------------------------------
# Copying : Project
mkdir -p MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI
cp ../Project/GNU/GUI/aclocal.m4 MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/autogen MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/config.guess MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/config.sub MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/configure MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/configure.ac MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/depcomp MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/install-sh MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/ltmain.sh MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/Makefile.am MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/Makefile.in MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/missing MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/wxwin.m4 MediaInfo_GUI_GNU_FromSource/Project/GNU/GUI/

#-----------------------------------------------------------------------
# Copying : Source
mkdir -p MediaInfo_GUI_GNU_FromSource/Source/Common
cp -r ../Source/Common/*.h MediaInfo_GUI_GNU_FromSource/Source/Common/
cp -r ../Source/Common/*.cpp MediaInfo_GUI_GNU_FromSource/Source/Common/
mkdir -p MediaInfo_GUI_GNU_FromSource/Source/GUI/Common
cp -r ../Source/GUI/Common/*.h MediaInfo_GUI_GNU_FromSource/Source/GUI/Common/
cp -r ../Source/GUI/Common/*.cpp MediaInfo_GUI_GNU_FromSource/Source/GUI/Common/
mkdir -p MediaInfo_GUI_GNU_FromSource/Source/GUI/WxWidgets
cp -r ../Source/GUI/WxWidgets/*.h MediaInfo_GUI_GNU_FromSource/Source/GUI/WxWidgets/
cp -r ../Source/GUI/WxWidgets/*.cpp MediaInfo_GUI_GNU_FromSource/Source/GUI/WxWidgets/
mkdir -p MediaInfo_GUI_GNU_FromSource/Source/Ressource/Image/Menu
cp -r ../Source/Ressource/Image/*.xpm MediaInfo_GUI_GNU_FromSource/Source/Ressource/Image/
cp -r ../Source/Ressource/Image/Menu/*.xpm MediaInfo_GUI_GNU_FromSource/Source/Ressource/Image/Menu/

#-----------------------------------------------------------------------
# Copying : Release
mkdir -p MediaInfo_GUI_GNU_FromSource/Release
cp Release_GUI_GNU.sub MediaInfo_GUI_GNU_FromSource/Release/
cp *.sh MediaInfo_GUI_GNU_FromSource/Release/
chmod u+x MediaInfo_GUI_GNU_FromSource/Release/*.sh

#-----------------------------------------------------------------------
# Copying : Information
cp ../Licence.html MediaInfo_GUI_GNU_FromSource/
cp ../History_GUI.txt MediaInfo_GUI_GNU_FromSource/
cp ReadMe_GUI_Linux.txt MediaInfo_GUI_GNU_FromSource/Release/
cp ReadMe_GUI_Mac.txt MediaInfo_GUI_GNU_FromSource/Release/


#-----------------------------------------------------------------------
# Preparing Archive : MediaInfo
mv MediaInfo_GUI_GNU_FromSource MediaInfo
mkdir MediaInfo_GUI_GNU_FromSource
mv MediaInfo MediaInfo_GUI_GNU_FromSource/

#-----------------------------------------------------------------------
# Preparing Archive : From MediaInfoLib
cd ../../MediaInfoLib/Release
. ./Release_Lib_GNU_FromSource.sh
tar xf MediaInfo_Lib_GNU_FromSource.tar.bz2
rm MediaInfo_Lib_GNU_FromSource.tar.bz2
cd ../../MediaInfo/Release
mv ../../MediaInfoLib/Release/MediaInfo_Lib_GNU_FromSource MediaInfo_GUI_GNU_FromSource/MediaInfoLib

#-----------------------------------------------------------------------
# Preparing Archive : From ZenLib
cd ../../ZenLib/Release
. ./Release_GNU_FromSource.sh
tar xf ZenLib_GNU_FromSource.tar.bz2
rm ZenLib_GNU_FromSource.tar.bz2
cd ../../MediaInfo/Release
mv ../../ZenLib/Release/ZenLib_GNU_FromSource MediaInfo_GUI_GNU_FromSource/ZenLib

#-----------------------------------------------------------------------
# Preparing Archive : From Shared
mkdir -p MediaInfo_GUI_GNU_FromSource/Shared/Project/_Common
cp -r ../../Shared/Project/_Common/*.sh MediaInfo_GUI_GNU_FromSource/Shared/Project/_Common
mkdir -p MediaInfo_GUI_GNU_FromSource/Shared/Project/ZLib
cp -r ../../Shared/Project/ZLib/*.sh MediaInfo_GUI_GNU_FromSource/Shared/Project/ZLib
mkdir -p MediaInfo_GUI_GNU_FromSource/Shared/Project/WxWidgets
cp -r ../../Shared/Project/WxWidgets/*.sh MediaInfo_GUI_GNU_FromSource/Shared/Project/WxWidgets

#-----------------------------------------------------------------------
# Preparing Archive : Automation
cp ../Project/GNU/GUI/AddThisToRoot_GUI_compile.sh MediaInfo_GUI_GNU_FromSource/GUI_Compile.sh
chmod u+x MediaInfo_GUI_GNU_FromSource/GUI_Compile.sh


#-----------------------------------------------------------------------
# Compressing Archive
tar jchf MediaInfo_GUI_GNU_FromSource.tar.bz2 MediaInfo_GUI_GNU_FromSource/*

#-----------------------------------------------------------------------
# Clean up
rm -r MediaInfo_GUI_GNU_FromSource
