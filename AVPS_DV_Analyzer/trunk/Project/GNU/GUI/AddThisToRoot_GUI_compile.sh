#! /bin/sh

#############################################################################
# Configure
Home=`pwd`
MediaInfoLib_Options="--enable-minimize-size --disable-all --enable-riff --enable-mpeg4 --enable-dvdif --enable-dvdif-analyze"
ZenLib_Options=""

#############################################################################
# Setup for parallel builds
Zen_Make()
{
 if test -e /proc/stat; then
  numprocs=`egrep -c ^cpu[0-9]+ /proc/stat || :`
  if [ "$numprocs" = "0" ]; then
   numprocs=1
  fi
  make -s -j$numprocs
 else
  make
 fi
}

#############################################################################
# ZenLib
if test -e ZenLib/Project/GNU/Library/configure; then
 cd ZenLib/Project/GNU/Library/
 test -e Makefile && rm Makefile
 chmod u+x configure
 ./configure $ZenLib_Options $*
 if test -e Makefile; then
  make clean
  Zen_Make
  if test -e libzen.la; then
   echo ZenLib compiled
  else
   echo Problem while compiling ZenLib
   exit
  fi
 else
  echo Problem while configuring ZenLib
  exit
 fi
else
 echo ZenLib directory is not found
 exit
fi
cd $Home

#############################################################################
# MediaInfoLib
if test -e MediaInfoLib/Project/GNU/Library/configure; then
 cd MediaInfoLib/Project/GNU/Library/
 test -e Makefile && rm Makefile
 chmod u+x configure
 ./configure $MediaInfoLib_Options $*
 if test -e Makefile; then
  make clean
  Zen_Make
  if test -e libmediainfo.la; then
   echo MediaInfoLib compiled
  else
   echo Problem while compiling MediaInfoLib
   exit
  fi
 else
  echo Problem while configuring MediaInfoLib
  exit
 fi
else
 echo MediaInfoLib directory is not found
 exit
fi
cd $Home

#############################################################################
# AVPS_DV_Analyzer
if test -e AVPS_DV_Analyzer/Project/GNU/GUI/configure; then
 cd AVPS_DV_Analyzer/Project/GNU/GUI/
 test -e Makefile && rm Makefile
 chmod u+x configure
 ./configure --enable-staticlibs $*
 if test -e Makefile; then
  make clean
  Zen_Make
  if test -e dvanalyzer-gui; then
   echo AVPS_DV_Analyzer compiled
  else
   echo Problem while compiling AVPS_DV_Analyzer
   exit
  fi
 else
  echo Problem while configuring AVPS_DV_Analyzer
  exit
 fi
else
 echo AVPS_DV_Analyzer directory is not found
 exit
fi
cd $Home

#############################################################################
# Going home
cd $Home
echo "AVPS_DV_Analyzer executable is in AVPS_DV_Analyzer/Project/GNU/GUI"
echo "For installing, cd AVPS_DV_Analyzer/Project/GNU/GUI && make install"


