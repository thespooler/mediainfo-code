// MediaArea_DV_Analyzer_CLI - A Command Line Interface for DV analyzing
// Copyright (C) 2009-2009 Jerome Martinez, Zen@MediaArea.net
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "Help.h"
#include "Config.h"
//---------------------------------------------------------------------------

//***************************************************************************
//
//***************************************************************************

//---------------------------------------------------------------------------
int Help()
{
    TEXTOUT("Usage: \"dvanalyzer [-Options...] FileName1 [Filename2...]\"");
    TEXTOUT("");
    TEXTOUT("Options:");
    TEXTOUT("--Help, -h         Display this help and exit");
    TEXTOUT("--Version          Display MediaArea DV Analyzer version and exit");
    TEXTOUT("");
    TEXTOUT("--Header           With a header (file name, column names...)");
    TEXTOUT("--Footer           With a footer (global stats)");
    TEXTOUT("");
    TEXTOUT("--Verbosity=x      Set the verbosity of the output");
    TEXTOUT("");
    TEXTOUT("--Help-Format      Display more info about the output format");
    TEXTOUT("--Help-Verbosity   Display more info about the verbosity option");
    TEXTOUT("--LogFile=...      Save the output in the specified file");

    return -1;
}

//---------------------------------------------------------------------------
int Help_Nothing()
{
    TEXTOUT("Usage: \"dvanalyzer [-Options...] FileName1 [Filename2...]\"");
    TEXTOUT("\"dvanalyzer --Help\" for displaying more information");

    return -1;
}

//---------------------------------------------------------------------------
int Help_Verbosity()
{
    TEXTOUT("0-2                : No info");
    TEXTOUT("3-4                : Errors only");
    TEXTOUT("5-9                : Errors and info");
    TEXTOUT("10                 : All");
    TEXTOUT("");
    TEXTOUT("Errors:");
    TEXTOUT("Timecode repeating (except 00:00:00:00)");
    TEXTOUT("Timecode non sequential");
    TEXTOUT("Recdate/rectime non sequential");
    TEXTOUT("Video errors");
    TEXTOUT("Audio errors");
    TEXTOUT("Timecode incoherency");
    TEXTOUT("DIF incoherency");
    TEXTOUT("");
    TEXTOUT("Information:");
    TEXTOUT("Recdate/rectime start");
    TEXTOUT("Recdate/rectime stop");
    TEXTOUT("");
    TEXTOUT("Note:");
    TEXTOUT("First and last frames are always displayed");

    return -1;
}

//---------------------------------------------------------------------------
int Help_Format()
{
    TEXTOUT("Frame              : Frame number from the start of the file");
    TEXTOUT("Time               : Time from the first detected timecode");
    TEXTOUT("TimeCode           : timecode values");
    TEXTOUT("N                  : N if non-consecutive timecodes");
    TEXTOUT("Recorded date/time : recdate/rectime values");
    TEXTOUT("N                  : N if non-consecutive rectime");
    TEXTOUT("S                  : S if REC_START is set");
    TEXTOUT("E                  : E if REC_END is set");
    TEXTOUT("1                  : Video errors (STA) detected");
    TEXTOUT("2                  : Audio errors detected");
    TEXTOUT("3                  : Timecode incoherency (multiple values)");
    TEXTOUT("4                  : DIF incoherency (NULL DIFs)");
    TEXTOUT("5                  : reserved");
    TEXTOUT("6                  : reserved");
    TEXTOUT("7                  : reserved");
    TEXTOUT("8                  : reserved");
    TEXTOUT("9                  : reserved");
    TEXTOUT("0                  : reserved");
    TEXTOUT("Error 1 details    : Details about video errors (STA) ");
    TEXTOUT("Error 2 details    : Details about audio errors ");
    TEXTOUT("Error 3 details    : Details about timecode incoherency");
    TEXTOUT("Error 4 details    : Details about DIF incoherency");
    TEXTOUT("Error 5 details    : reserved");
    TEXTOUT("Error 6 details    : reserved");
    TEXTOUT("Error 7 details    : reserved");
    TEXTOUT("Error 8 details    : reserved");
    TEXTOUT("Error 9 details    : reserved");
    TEXTOUT("Error 0 details    : reserved");

    return -1;
}
