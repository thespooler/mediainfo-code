#! /bin/sh

#-----------------------------------------------------------------------
# Clean up
test -e MediaArea_DV_Analyzer_CLI_GNU_FromSource.tar     && rm    MediaArea_DV_Analyzer_CLI_GNU_FromSource.tar
test -e MediaArea_DV_Analyzer_CLI_GNU_FromSource.tar.bz2 && rm    MediaArea_DV_Analyzer_CLI_GNU_FromSource.tar.bz2
test -d MediaArea_DV_Analyzer_CLI_GNU_FromSource         && rm -r MediaArea_DV_Analyzer_CLI_GNU_FromSource
mkdir MediaArea_DV_Analyzer_CLI_GNU_FromSource


#-----------------------------------------------------------------------
# Preparing : Project
cd ../Project/GNU/CLI
chmod u+x autogen
./autogen
cd ../../../Release


#-----------------------------------------------------------------------
# Copying : Project
mkdir -p MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI
cp ../Project/GNU/CLI/aclocal.m4 MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/autogen MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/config.guess MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/config.sub MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/configure MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/configure.ac MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/depcomp MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/install-sh MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/ltmain.sh MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/Makefile.am MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/Makefile.in MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/missing MediaArea_DV_Analyzer_CLI_GNU_FromSource/Project/GNU/CLI/

#-----------------------------------------------------------------------
# Copying : Source
mkdir -p MediaArea_DV_Analyzer_CLI_GNU_FromSource/Source/Common
cp -r ../Source/Common/*.h MediaArea_DV_Analyzer_CLI_GNU_FromSource/Source/Common/
cp -r ../Source/Common/*.cpp MediaArea_DV_Analyzer_CLI_GNU_FromSource/Source/Common/
mkdir -p MediaArea_DV_Analyzer_CLI_GNU_FromSource/Source/CLI
cp -r ../Source/CLI/*.h MediaArea_DV_Analyzer_CLI_GNU_FromSource/Source/CLI/
cp -r ../Source/CLI/*.cpp MediaArea_DV_Analyzer_CLI_GNU_FromSource/Source/CLI/

#-----------------------------------------------------------------------
# Copying : Release
mkdir -p MediaArea_DV_Analyzer_CLI_GNU_FromSource/Release
cp Release_CLI_GNU.sub MediaArea_DV_Analyzer_CLI_GNU_FromSource/Release/
cp *.sh MediaArea_DV_Analyzer_CLI_GNU_FromSource/Release/
chmod u+x MediaArea_DV_Analyzer_CLI_GNU_FromSource/Release/*.sh

#-----------------------------------------------------------------------
# Copying : Information
cp ../License.html MediaArea_DV_Analyzer_CLI_GNU_FromSource/
cp ../History_CLI.txt MediaArea_DV_Analyzer_CLI_GNU_FromSource/
dos2unix MediaArea_DV_Analyzer_CLI_GNU_FromSource/History_CLI.txt
cp ReadMe_CLI_Linux.txt MediaArea_DV_Analyzer_CLI_GNU_FromSource/Release/
cp ReadMe_CLI_Mac.txt MediaArea_DV_Analyzer_CLI_GNU_FromSource/Release/


#-----------------------------------------------------------------------
# Preparing Archive : MediaArea_DV_Analyzer
mv MediaArea_DV_Analyzer_CLI_GNU_FromSource MediaArea_DV_Analyzer
mkdir MediaArea_DV_Analyzer_CLI_GNU_FromSource
mv MediaArea_DV_Analyzer MediaArea_DV_Analyzer_CLI_GNU_FromSource/

#-----------------------------------------------------------------------
# Preparing Archive : From MediaInfoLib
cd ../../MediaInfoLib/Release
. ./Release_Lib_GNU_FromSource.sh
tar xf MediaInfo_Lib_GNU_FromSource.tar.bz2
rm MediaInfo_Lib_GNU_FromSource.tar.bz2
cd ../../MediaArea_DV_Analyzer/Release
mv ../../MediaInfoLib/Release/MediaInfo_Lib_GNU_FromSource MediaArea_DV_Analyzer_CLI_GNU_FromSource/MediaInfoLib

#-----------------------------------------------------------------------
# Preparing Archive : From ZenLib
cd ../../ZenLib/Release
. ./Release_GNU_FromSource.sh
tar xf ZenLib_GNU_FromSource.tar.bz2
rm ZenLib_GNU_FromSource.tar.bz2
cd ../../MediaArea_DV_Analyzer/Release
mv ../../ZenLib/Release/ZenLib_GNU_FromSource MediaArea_DV_Analyzer_CLI_GNU_FromSource/ZenLib

#-----------------------------------------------------------------------
# Preparing Archive : From Shared
mkdir -p MediaArea_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/_Common
cp -r ../../Shared/Project/_Common/*.sh MediaArea_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/_Common
mkdir -p MediaArea_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/ZLib
cp -r ../../Shared/Project/ZLib/*.sh MediaArea_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/ZLib
mkdir -p MediaArea_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/ZLib/Template/projects/GNU
cp -r ../../Shared/Project/ZLib/Template/projects/GNU/* MediaArea_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/ZLib/Template/projects/GNU
mkdir -p MediaArea_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/WxWidgets
cp -r ../../Shared/Project/WxWidgets/*.sh MediaArea_DV_Analyzer_CLI_GNU_FromSource/Shared/Project/WxWidgets

#-----------------------------------------------------------------------
# Preparing Archive : Automation
cp ../Project/GNU/CLI/AddThisToRoot_CLI_compile.sh MediaArea_DV_Analyzer_CLI_GNU_FromSource/CLI_Compile.sh
chmod u+x MediaArea_DV_Analyzer_CLI_GNU_FromSource/CLI_Compile.sh


#-----------------------------------------------------------------------
# Compressing Archive
tar jchf MediaArea_DV_Analyzer_CLI_GNU_FromSource.tar.bz2 MediaArea_DV_Analyzer_CLI_GNU_FromSource/*

#-----------------------------------------------------------------------
# Clean up
rm -r MediaArea_DV_Analyzer_CLI_GNU_FromSource
