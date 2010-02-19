@echo off

rem --- Clean up ---
del mediainfo_.tar.bz2
del MediaInfo_Source.tar
del mediainfo_-1.tar.gz 
del mediainfo__AllInclusive.7z
rmdir MediaInfo_Source /S /Q
rmdir MediaInfoLib /S /Q
rmdir ZenLib /S /Q
rmdir wxMSW /S /Q
rmdir zlib /S /Q
mkdir MediaInfo_Source


@rem --- Copying : Sources ---
xcopy ..\Source\*.cpp MediaInfo_Source\Source\ /S
xcopy ..\Source\*.h MediaInfo_Source\Source\ /S
xcopy ..\Source\*.dfm MediaInfo_Source\Source\ /S
xcopy ..\Source\*.xml MediaInfo_Source\Source\ /S
xcopy ..\Source\*.rc MediaInfo_Source\Source\ /S
xcopy ..\Source\*.csv MediaInfo_Source\Source\ /S
xcopy ..\Source\*.ico MediaInfo_Source\Source\ /S
xcopy ..\Source\Install\*.nsi MediaInfo_Source\Source\Install\
xcopy ..\Source\*.sh  MediaInfo_Source\Source\ /S
xcopy ..\Source\*.png MediaInfo_Source\Source\ /S
xcopy ..\Source\*.xpm MediaInfo_Source\Source\ /S

@rem --- Copying : Projects ---
xcopy ..\Project\*.bpg MediaInfo_Source\Project\ /S
xcopy ..\Project\*.bpf MediaInfo_Source\Project\ /S
xcopy ..\Project\*.bpr MediaInfo_Source\Project\ /S
xcopy ..\Project\*.cpp MediaInfo_Source\Project\ /S
xcopy ..\Project\*.c MediaInfo_Source\Project\ /S
xcopy ..\Project\*.h MediaInfo_Source\Project\ /S
xcopy ..\Project\*.bdsgroup MediaInfo_Source\Project\ /S
xcopy ..\Project\*.bdsproj MediaInfo_Source\Project\ /S
xcopy ..\Project\*.groupproj MediaInfo_Source\Project\ /S
xcopy ..\Project\*.cbproj MediaInfo_Source\Project\ /S
xcopy ..\Project\*.dev MediaInfo_Source\Project\ /S
xcopy ..\Project\*.sln MediaInfo_Source\Project\ /S
xcopy ..\Project\*.vc MediaInfo_Source\Project\ /S
xcopy ..\Project\*.vcproj MediaInfo_Source\Project\ /S
xcopy ..\Project\*.ico MediaInfo_Source\Project\ /S
xcopy ..\Project\*.workspace MediaInfo_Source\Project\ /S
xcopy ..\Project\*.cbp MediaInfo_Source\Project\ /S /Y
xcopy ..\Project\*.def MediaInfo_Source\Project\ /S
xcopy ..\Project\*.idl MediaInfo_Source\Project\ /S
xcopy ..\Project\*.rgs MediaInfo_Source\Project\ /S
xcopy ..\Project\*.bat MediaInfo_Source\Project\ /S
xcopy ..\Project\BCB\MediaInfo*.res MediaInfo_Source\Project\BCB /S
xcopy ..\Project\MSVC\*.rc MediaInfo_Source\Project\MSVC\ /S
xcopy ..\Project\GNU\* MediaInfo_Source\Project\GNU\ /S

@rem --- Copying : Release ---
xcopy *.txt MediaInfo_Source\Release\
xcopy *.bat MediaInfo_Source\Release\
xcopy *.sh  MediaInfo_Source\Release\
xcopy *.sub MediaInfo_Source\Release\
xcopy BCB\*.txt MediaInfo_Source\Release\BCB\ /S
xcopy MSVC\*.txt MediaInfo_Source\Release\MSVC\ /S
xcopy GCC_MinGW32\*.txt MediaInfo_Source\Release\GCC_MinGW32\ /S
xcopy GCC_Linux_i386\*.txt MediaInfo_Source\Release\GCC_Linux_i386\ /S
xcopy Make_GCC.sh MediaInfo_Source\Release\

@rem --- Copying : debian ---
xcopy ..\debian\* MediaInfo_Source\debian\ /S

rem --- Copying : Information files ---
xcopy ..\*.txt MediaInfo_Source\
xcopy ..\*.html MediaInfo_Source\

rem --- Copying : Contrib files ---
xcopy ..\Contrib\*.doc MediaInfo_Source\Contrib\ /S

rem --- Copying : CVS files ---
xcopy ..\*.cvsignore MediaInfo_Source\

rem --- Copying : MediaInfoLib files ---
cd ..\..\MediaInfoLib\Release
call Release_Source.bat SkipCleanUp SkipCompression
cd ..\..\MediaInfo\Release
move ..\..\MediaInfoLib\Release\MediaInfo_Lib_Source .\MediaInfoLib

rem --- Copying : ZenLib files ---
cd ..\..\ZenLib\Release
call Release_Source.bat SkipCleanUp SkipCompression
cd ..\..\MediaInfo\Release
move ..\..\ZenLib\Release\ZenLib_Source .\ZenLib

rem --- Copying : zlib files ---
xcopy ..\..\Shared\Source\zlib .\zlib\ /S
xcopy ..\..\Shared\Project\zlib\Template .\zlib\ /S

rem --- Copying : Wx files ---
xcopy ..\..\Shared\Source\wxMSW .\wxMSW\ /S
xcopy ..\..\Shared\Project\WxWidgets\Template .\wxMSW\ /S


rem --- Compressing Archive ---
if "%2"=="SkipCompression" goto SkipCompression
move MediaInfo_Source MediaInfo
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -ttar -mx9 MediaInfo_Source.tar MediaInfo\*
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -tbzip2 -mx9 mediainfo_.tar.bz2 MediaInfo_Source.tar
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -tgzip -mx9 mediainfo_-1.tar.gz MediaInfo_Source.tar
del MediaInfo_Source.tar
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -t7z -mx9 mediainfo__AllInclusive.7z MediaInfo\* MediaInfoLib\* ZenLib\* wxMSW\* zlib\*
move MediaInfo MediaInfo_Source
:SkipCompression

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir MediaInfo_Source /S /Q
:SkipCleanUp
rmdir MediaInfoLib /S /Q
rmdir ZenLib /S /Q
rmdir wxMSW /S /Q
rmdir zlib /S /Q
