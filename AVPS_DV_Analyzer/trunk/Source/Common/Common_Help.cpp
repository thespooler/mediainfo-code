// Common_Help - Help strings
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
#include "Common/Common_Help.h"
//---------------------------------------------------------------------------

const char* Help_Summary_HTML() {return
"<h3>Errors</h3>"
"<ul>"
"<li>Timecode repeating (except 00:00:00:00)</li>"
"<li>Timecode non sequential</li>"
"<li>Recdate/rectime non sequential</li>"
"<li>Video errors</li>"
"<li>Audio errors</li>"
"<li>Timecode incoherency</li>"
"<li>DIF incoherency</li>"
"</ul>"
"<h3>Information</h3>"
"<ul>"
"<li>Recdate/rectime/TimeCode discontinuity</li>"
"</ul>"
"<h3>Note</h3>"
"<ul>"
"<li>First and last frames are always displayed</li>"
"</ul>"
;}

const char* Help_Summary_Text() {return
"Errors\n"
"\n"
"Timecode repeating (except 00:00:00:00)\n"
"Timecode non sequential\n"
"Recdate/rectime non sequential\n"
"Video errors\n"
"Audio errors\n"
"Timecode incoherency\n"
"DIF incoherency\n"
"\n"
"Information\n"
"\n"
"Recdate/rectime/TimeCode discontinuity\n"
"\n"
"Note\n"
"\n"
"First and last frames are always displayed\n"
"\n"
;}

const char* Help_ByFrame_HTML() {return
"<h3>Per column</h3>"
"<ul>"
"<li>Frame              : Frame number from the start of the file</li>"
"<li>Time               : Timecode relative to the timeline of the file</li>"
"<li>TimeCode           : timecode values</li>"
"<li>N                  : N if non-consecutive timecodes</li>"
"<li>Recorded date/time : recdate/rectime values</li>"
"<li>N                  : N if non-consecutive rectime</li>"
"<li>A                  : Arb bits</li>"
"<li>S                  : S if REC_START is set</li>"
"<li>E                  : E if REC_END is set</li>"
"<li>1                  : Video errors (STA detected)</li>"
"<li>2                  : Audio errors detected</li>"
"<li>3                  : Timecode incoherency (multiple values)</li>"
"<li>4                  : DIF incoherency (NULL DIFs)</li>"
"<li>5                  : Arb incoherency (multiple values)</li>"
"<li>6                  : reserved</li>"
"<li>7                  : reserved</li>"
"<li>8                  : reserved</li>"
"<li>9                  : reserved</li>"
"<li>0                  : reserved</li>"
"<li>Error 1 details    : Details about video errors (STA detected)</li>"
"<li>Error 2 details    : Details about audio errors </li>"
"<li>Error 3 details    : Details about timecode incoherency</li>"
"<li>Error 4 details    : Details about DIF incoherency</li>"
"<li>Error 5 details    : Details about Arb incoherency</li>"
"<li>Error 6 details    : reserved</li>"
"<li>Error 7 details    : reserved</li>"
"<li>Error 8 details    : reserved</li>"
"<li>Error 9 details    : reserved</li>"
"<li>Error 0 details    : reserved</li>"
"</ul>"
;}

const char* Help_ByFrame_Text() {return
"Per column\n"
"\n"
"Frame              : Frame number from the start of the file\n"
"Time               : Timecode relative to the timeline of the file\n"
"TimeCode           : timecode values\n"
"N                  : N if non-consecutive timecodes\n"
"Recorded date/time : recdate/rectime values\n"
"N                  : N if non-consecutive rectime\n"
"S                  : S if REC_START is set\n"
"E                  : E if REC_END is set\n"
"1                  : Video errors (STA detected)\n"
"2                  : Audio errors detected\n"
"3                  : Timecode incoherency (multiple values)\n"
"4                  : DIF incoherency (NULL DIFs)\n"
"5                  : reserved\n"
"6                  : reserved\n"
"7                  : reserved\n"
"8                  : reserved\n"
"9                  : reserved\n"
"0                  : reserved\n"
"Error 1 details    : Details about video errors (STA detected)\n"
"Error 2 details    : Details about audio errors \n"
"Error 3 details    : Details about timecode incoherency\n"
"Error 4 details    : Details about DIF incoherency\n"
"Error 5 details    : reserved\n"
"Error 6 details    : reserved\n"
"Error 7 details    : reserved\n"
"Error 8 details    : reserved\n"
"Error 9 details    : reserved\n"
"Error 0 details    : reserved\n"
"\n"
;}
