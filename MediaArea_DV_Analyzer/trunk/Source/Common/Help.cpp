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
#include "Common/Help.h"
#include <sstream>
//---------------------------------------------------------------------------

//***************************************************************************
//
//***************************************************************************

//---------------------------------------------------------------------------
std::string Help()
{
    std::ostringstream ToDisplay;

    ToDisplay<<"Usage: \"dvanalyzer [-Options...] FileName1 [Filename2...]\""<<std::endl;
    ToDisplay<<""<<std::endl;
    ToDisplay<<"Options:"<<std::endl;
    ToDisplay<<"--Help, -h         Display this help and exit"<<std::endl;
    ToDisplay<<"--Version          Display MediaArea DV Analyzer version and exit"<<std::endl;
    ToDisplay<<""<<std::endl;
    ToDisplay<<"--Header           With a header (file name, column names...)"<<std::endl;
    ToDisplay<<"--Footer           With a footer (global stats)"<<std::endl;
    ToDisplay<<""<<std::endl;
    ToDisplay<<"--Verbosity=x      Set the verbosity of the output"<<std::endl;
    ToDisplay<<""<<std::endl;
    ToDisplay<<"--Help-Format      Display more info about the output format"<<std::endl;
    ToDisplay<<"--Help-Verbosity   Display more info about the verbosity option"<<std::endl;
    ToDisplay<<"--LogFile=...      Save the output in the specified file"<<std::endl;

    return ToDisplay.str();
}

//---------------------------------------------------------------------------
std::string Help_Nothing()
{
    std::ostringstream ToDisplay;

    ToDisplay<<"Usage: \"dvanalyzer [-Options...] FileName1 [Filename2...]\""<<std::endl;
    ToDisplay<<"\"dvanalyzer --Help\" for displaying more information"<<std::endl;

    return ToDisplay.str();
}

//---------------------------------------------------------------------------
std::string Help_Verbosity()
{
    std::ostringstream ToDisplay;

    ToDisplay<<"0-2                : No info"<<std::endl;
    ToDisplay<<"3-4                : Errors only"<<std::endl;
    ToDisplay<<"5-9                : Errors and info"<<std::endl;
    ToDisplay<<"10                 : All"<<std::endl;

    return ToDisplay.str();
}

//---------------------------------------------------------------------------
std::string Help_Summary_Format()
{
    std::ostringstream ToDisplay;

    ToDisplay<<"Errors:"<<std::endl;
    ToDisplay<<"Timecode repeating (except 00:00:00:00"<<std::endl;
    ToDisplay<<"Timecode non sequential"<<std::endl;
    ToDisplay<<"Recdate/rectime non sequential"<<std::endl;
    ToDisplay<<"Video errors"<<std::endl;
    ToDisplay<<"Audio errors"<<std::endl;
    ToDisplay<<"Timecode incoherency"<<std::endl;
    ToDisplay<<"DIF incoherency"<<std::endl;
    ToDisplay<<""<<std::endl;
    ToDisplay<<"Information:"<<std::endl;
    ToDisplay<<"Recdate/rectime start"<<std::endl;
    ToDisplay<<"Recdate/rectime stop"<<std::endl;
    ToDisplay<<""<<std::endl;
    ToDisplay<<"Note:"<<std::endl;
    ToDisplay<<"First and last frames are always displayed"<<std::endl;

    return ToDisplay.str();
}

//---------------------------------------------------------------------------
std::string Help_ByFrame_Format()
{
    std::ostringstream ToDisplay;

    ToDisplay<<"Frame              : Frame number from the start of the file"<<std::endl;
    ToDisplay<<"Time               : Timecode relative to the timeline of the file"<<std::endl;
    ToDisplay<<"TimeCode           : timecode values"<<std::endl;
    ToDisplay<<"N                  : N if non-consecutive timecodes"<<std::endl;
    ToDisplay<<"Recorded date/time : recdate/rectime values"<<std::endl;
    ToDisplay<<"N                  : N if non-consecutive rectime"<<std::endl;
    ToDisplay<<"S                  : S if REC_START is set"<<std::endl;
    ToDisplay<<"E                  : E if REC_END is set"<<std::endl;
    ToDisplay<<"1                  : Video errors (STA detected"<<std::endl;
    ToDisplay<<"2                  : Audio errors detected"<<std::endl;
    ToDisplay<<"3                  : Timecode incoherency (multiple values"<<std::endl;
    ToDisplay<<"4                  : DIF incoherency (NULL DIFs"<<std::endl;
    ToDisplay<<"5                  : reserved"<<std::endl;
    ToDisplay<<"6                  : reserved"<<std::endl;
    ToDisplay<<"7                  : reserved"<<std::endl;
    ToDisplay<<"8                  : reserved"<<std::endl;
    ToDisplay<<"9                  : reserved"<<std::endl;
    ToDisplay<<"0                  : reserved"<<std::endl;
    ToDisplay<<"Error 1 details    : Details about video errors (STA "<<std::endl;
    ToDisplay<<"Error 2 details    : Details about audio errors "<<std::endl;
    ToDisplay<<"Error 3 details    : Details about timecode incoherency"<<std::endl;
    ToDisplay<<"Error 4 details    : Details about DIF incoherency"<<std::endl;
    ToDisplay<<"Error 5 details    : reserved"<<std::endl;
    ToDisplay<<"Error 6 details    : reserved"<<std::endl;
    ToDisplay<<"Error 7 details    : reserved"<<std::endl;
    ToDisplay<<"Error 8 details    : reserved"<<std::endl;
    ToDisplay<<"Error 9 details    : reserved"<<std::endl;
    ToDisplay<<"Error 0 details    : reserved"<<std::endl;

    return ToDisplay.str();
}

