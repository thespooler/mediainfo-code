@echo off

rem --- Clean up ---
del MediaArea_DV_Analyzer_.tar.bz2
del MediaArea_DV_Analyzer_Source.tar
del MediaArea_DV_Analyzer_-1.tar.gz 
del MediaArea_DV_Analyzer__AllInclusive.7z
rmdir MediaArea_DV_Analyzer_Source /S /Q
rmdir MediaInfoLib /S /Q
rmdir ZenLib /S /Q
rmdir zlib /S /Q
mkdir MediaArea_DV_Analyzer_Source


@rem --- Copying : Sources ---
xcopy ..\Source\*.cpp MediaArea_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.h MediaArea_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.dfm MediaArea_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.xml MediaArea_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.rc MediaArea_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.txt MediaArea_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.csv MediaArea_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.ico MediaArea_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\Install\MediaArea_DV_Analyzer.nsi MediaArea_DV_Analyzer_Source\Source\Install\
xcopy ..\Source\*.sh  MediaArea_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.png MediaArea_DV_Analyzer_Source\Source\ /S
xcopy ..\Source\*.xpm MediaArea_DV_Analyzer_Source\Source\ /S

@rem --- Copying : Projects ---
xcopy ..\Project\*.bpg MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.bpf MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.bpr MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.cpp MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.c MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.h MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.bdsgroup MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.bdsproj MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.dev MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.sln MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.vc MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.vcproj MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.ico MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.workspace MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.cbp MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.def MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.idl MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.rgs MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\*.bat MediaArea_DV_Analyzer_Source\Project\ /S
xcopy ..\Project\BCB\MediaArea_DV_Analyzer*.res MediaArea_DV_Analyzer_Source\Project\BCB /S
xcopy ..\Project\MSVC\*.rc MediaArea_DV_Analyzer_Source\Project\MSVC\ /S
xcopy ..\Project\GNU\* MediaArea_DV_Analyzer_Source\Project\GNU\ /S

@rem --- Copying : Release ---
xcopy *.txt MediaArea_DV_Analyzer_Source\Release\
xcopy *.bat MediaArea_DV_Analyzer_Source\Release\
xcopy *.sh  MediaArea_DV_Analyzer_Source\Release\
xcopy *.sub MediaArea_DV_Analyzer_Source\Release\
xcopy BCB\*.txt MediaArea_DV_Analyzer_Source\Release\BCB\ /S
xcopy MSVC\*.txt MediaArea_DV_Analyzer_Source\Release\MSVC\ /S
xcopy GCC_MinGW32\*.txt MediaArea_DV_Analyzer_Source\Release\GCC_MinGW32\ /S
xcopy GCC_Linux_i386\*.txt MediaArea_DV_Analyzer_Source\Release\GCC_Linux_i386\ /S
xcopy Make_GCC.sh MediaArea_DV_Analyzer_Source\Release\

@rem --- Copying : debian ---
xcopy ..\debian\* MediaArea_DV_Analyzer_Source\debian\ /S

rem --- Copying : Information files ---
xcopy ..\*.txt MediaArea_DV_Analyzer_Source\
xcopy ..\*.html MediaArea_DV_Analyzer_Source\

rem --- Copying : Contrib files ---
xcopy ..\Contrib\*.doc MediaArea_DV_Analyzer_Source\Contrib\ /S

rem --- Copying : CVS files ---
xcopy ..\*.cvsignore MediaArea_DV_Analyzer_Source\

rem --- Copying : MediaInfoLib files ---
cd ..\..\MediaInfoLib\Release
call Release_Source.bat SkipCleanUp SkipCompression
cd ..\..\MediaArea_DV_Analyzer\Release
move ..\..\MediaInfoLib\Release\MediaInfo_Lib_Source .\MediaInfoLib

rem --- Copying : ZenLib files ---
cd ..\..\ZenLib\Release
call Release_Source.bat SkipCleanUp SkipCompression
cd ..\..\MediaArea_DV_Analyzer\Release
move ..\..\ZenLib\Release\ZenLib_Source .\ZenLib

rem --- Copying : zlib files ---
xcopy ..\..\Shared\Source\zlib .\zlib\ /S
xcopy ..\..\Shared\Project\zlib\Template .\zlib\ /S


rem --- Compressing Archive ---
if "%2"=="SkipCompression" goto SkipCompression
move MediaArea_DV_Analyzer_Source MediaArea_DV_Analyzer
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -ttar -mx9 MediaArea_DV_Analyzer_Source.tar MediaArea_DV_Analyzer\*
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -tbzip2 -mx9 MediaArea_DV_Analyzer_.tar.bz2 MediaArea_DV_Analyzer_Source.tar
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -tgzip -mx9 MediaArea_DV_Analyzer_-1.tar.gz MediaArea_DV_Analyzer_Source.tar
del MediaArea_DV_Analyzer_Source.tar
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -t7z -mx9 MediaArea_DV_Analyzer__AllInclusive.7z MediaArea_DV_Analyzer\* MediaInfoLib\* ZenLib\* zlib\*
move MediaArea_DV_Analyzer MediaArea_DV_Analyzer_Source
:SkipCompression

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir MediaArea_DV_Analyzer_Source /S /Q
:SkipCleanUp
rmdir MediaInfoLib /S /Q
rmdir ZenLib /S /Q
rmdir zlib /S /Q
