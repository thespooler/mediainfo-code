// File_Eia608 - Info for EIA-608 files
// Copyright (C) 2009-2011 MediaArea.net SARL, Info@MediaArea.net
//
// This library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
// Compilation conditions
#include "MediaInfo/Setup.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_EIA608_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Text/File_Eia608.h"
#include "MediaInfo/MediaInfo_Config_MediaInfo.h"
using namespace std;
//---------------------------------------------------------------------------


//***************************************************************************
// Constants
//***************************************************************************

/* screen size -- specified by the standard */
const int8u Eia608_Rows=15;
const int8u Eia608_Columns=32;

//---------------------------------------------------------------------------
// CAE-608-E section F.1.1.5
static const int8u Eia608_PAC_Row[]=
{
    10,
    0,  //or 1
    2,  //or 3
    11, //or 12
    13, //or 14
    4,  //or 5
    6,  //or 7
    8   //or 9
};

//***************************************************************************
//
//***************************************************************************

namespace MediaInfoLib
{

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
File_Eia608::File_Eia608()
:File__Analyze()
{
    //Configuration
    PTS_DTS_Needed=true;

    //In

    //Temp
    TextMode=false;
    DataChannelMode=false;
    InBack=false;
    CC_Displayed.resize(Eia608_Rows);
    for (size_t Pos=0; Pos<CC_Displayed.size(); Pos++)
        CC_Displayed[Pos].resize(Eia608_Columns);
    CC_NonDisplayed.resize(Eia608_Rows);
    for (size_t Pos=0; Pos<CC_NonDisplayed.size(); Pos++)
        CC_NonDisplayed[Pos].resize(Eia608_Columns);
    Text_Displayed.resize(Eia608_Rows);
    for (size_t Pos=0; Pos<Text_Displayed.size(); Pos++)
        Text_Displayed[Pos].resize(Eia608_Columns);
    x=0;
    y=Eia608_Rows-1;
    Attribute_Current=0;
    RollUpLines=0;
    cc_data_1_Old=0x00;
    cc_data_2_Old=0x00;
    HasContent=false;
    FieldNumber=0;
}

//***************************************************************************
// Streams management
//***************************************************************************

//---------------------------------------------------------------------------
void File_Eia608::Streams_Fill()
{
    Stream_Prepare(Stream_Text);
    Fill(Stream_Text, 0, Text_Format, "EIA-608");
    Fill(Stream_Text, 0, Text_StreamSize, 0);
    if (FieldNumber)
        Fill(Stream_Text, 0, Text_ID, FieldNumber);
}

//---------------------------------------------------------------------------
void File_Eia608::Streams_Finish()
{
    if (!HasContent)
        Fill(Stream_Text, 0, "ContentInfo", "No content");
}

//***************************************************************************
// Buffer - Synchro
//***************************************************************************

//---------------------------------------------------------------------------
void File_Eia608::Read_Buffer_Unsynched()
{
    for (size_t Pos_Y=0; Pos_Y<CC_Displayed.size(); Pos_Y++)
    {
        for (size_t Pos_X=0; Pos_X<CC_Displayed[Pos_Y].size(); Pos_X++)
        {
            CC_Displayed[Pos_Y][Pos_X].Value=L' ';
            CC_Displayed[Pos_Y][Pos_X].Attribute=0;
            CC_NonDisplayed[Pos_Y][Pos_X].Value=L' ';
            CC_NonDisplayed[Pos_Y][Pos_X].Attribute=0;
            Text_Displayed[Pos_Y][Pos_X].Value=L' ';
            Text_Displayed[Pos_Y][Pos_X].Attribute=0;
        }
    }

    XDS_Data.clear();
}

//***************************************************************************
// Buffer - Global
//***************************************************************************

//---------------------------------------------------------------------------
void File_Eia608::Read_Buffer_Continue()
{
    FrameInfo.PTS=FrameInfo.DTS;

    if (!Status[IsAccepted])
    {
        Accept("EIA-608");

        //Forcing detection even if this is empty caption (option)
        if (Config->File_Eia608_DisplayEmptyStream_Get()) //TODO: separate CC1/CC2/T1/T2
            Fill("EIA-608");
    }

    int8u cc_data_1, cc_data_2;
    Get_B1 (cc_data_1,                                          "cc_data");
    Get_B1 (cc_data_2,                                          "cc_data");

    //Removing checksume
    cc_data_1&=0x7F;
    cc_data_2&=0x7F;

    //Test if non-printing chars (0x10-0x1F) are repeated (CEA-608-E section D.2)
    if (cc_data_1_Old)
    {
        if (cc_data_1_Old==cc_data_1 && cc_data_2_Old==cc_data_2)
        {
            //This is duplicate
            cc_data_1_Old=0x00;
            cc_data_2_Old=0x00;
            return; //Nothing to do
        }
        else
        {
            //They should be duplicated, there is a problem
        }
        cc_data_1_Old=0x00;
        cc_data_2_Old=0x00;
    }
    
    if ((cc_data_1 && cc_data_1<0x10) || !XDS_Data.empty()) //XDS
    {
        TextMode=false; //This is CC
        XDS_Data.push_back(cc_data_1);
        XDS_Data.push_back(cc_data_2);
        if (cc_data_1==0x0F)
            XDS();
        if (XDS_Data.size()>64)
            XDS_Data.clear(); //This is a security
    }
    else if (cc_data_1>=0x20) //Basic characters
    {
        if (Synched)
        {
            Standard(cc_data_1);
            if ((cc_data_2&0x7F)>=0x20)
                Standard(cc_data_2);
        }
    }
    else if (cc_data_1) //Special
        Special(cc_data_1, cc_data_2);
}

//***************************************************************************
// Functions
//***************************************************************************

//---------------------------------------------------------------------------
void File_Eia608::XDS()
{
    if (XDS_Data.size()<4)
    {
        XDS_Data.clear();
        return; //There is a problem
    }

    switch (XDS_Data[0])
    {
        case 0x01 : XDS_Current(); break;
        case 0x05 : XDS_Channel(); break;
        case 0x09 : XDS_PublicService(); break;
        default   : ;
    }

    XDS_Data.clear();

    //With have a point of synchro
    if (!Synched)
        Synched=true;
}

//---------------------------------------------------------------------------
void File_Eia608::XDS_Current()
{
    switch (XDS_Data[1])
    {
        case 0x03 : XDS_Current_ProgramName(); break;
        case 0x05 : XDS_Current_ContentAdvisory(); break;
        case 0x08 : XDS_Current_CopyAndRedistributionControlPacket(); break;
        default   : ;
    }
}

//---------------------------------------------------------------------------
void File_Eia608::XDS_Current_ContentAdvisory()
{
    if (XDS_Data.size()!=6)
    {
        return; //There is a problem
    }
}

//---------------------------------------------------------------------------
void File_Eia608::XDS_Current_ProgramName()
{
    string ValueS;
    for (size_t Pos=2; Pos<XDS_Data.size()-2; Pos++)
        ValueS.append(1, (const char)(XDS_Data[Pos]));
    Ztring Value;
    Value.From_UTF8(ValueS.c_str());
    Element_Info(_T("Program Name=")+Value);
}

//---------------------------------------------------------------------------
void File_Eia608::XDS_Current_CopyAndRedistributionControlPacket()
{
    if (XDS_Data.size()!=6)
    {
        return; //There is a problem
    }
}

//---------------------------------------------------------------------------
void File_Eia608::XDS_Channel()
{
    switch (XDS_Data[1])
    {
        case 0x01 : XDS_Channel_NetworkName(); break;
        default   : ;
    }
}

//---------------------------------------------------------------------------
void File_Eia608::XDS_Channel_NetworkName()
{
    string ValueS;
    for (size_t Pos=2; Pos<XDS_Data.size()-2; Pos++)
        ValueS.append(1, (const char)(XDS_Data[Pos]));
    Ztring Value;
    Value.From_UTF8(ValueS.c_str());
    Element_Info(_T("Network Name=")+Value);
}

//---------------------------------------------------------------------------
void File_Eia608::XDS_PublicService()
{
    switch (XDS_Data[1])
    {
        case 0x01 : XDS_PublicService_NationalWeatherService(); break;
        default   : ;
    }
}

//---------------------------------------------------------------------------
void File_Eia608::XDS_PublicService_NationalWeatherService()
{
    if (XDS_Data.size()!=20)
    {
        return; //There is a problem
    }
}

//---------------------------------------------------------------------------
void File_Eia608::Special(int8u cc_data_1, int8u cc_data_2)
{
    //Data channel check
    DataChannelMode=(cc_data_1&0x08)!=0; //bit3 is the Data Channel number

    //Field check
    cc_data_1&=~0x08;
    if (FieldNumber==0)
    {
        if (cc_data_1==0x14 && (cc_data_2&0xF0)==0x20)
            FieldNumber=1;
        if (cc_data_1==0x15 && (cc_data_2&0xF0)==0x20)
            FieldNumber=2;
    }

    if (cc_data_1>=0x10 && cc_data_1<=0x17 && cc_data_2>=0x40)
    {
        PreambleAddressCode(cc_data_1, cc_data_2);
    }
    else
    {
        switch (cc_data_1)
        {
            case 0x10 : Special_10(cc_data_2); break;
            case 0x11 : Special_11(cc_data_2); break;
            case 0x12 : Special_12(cc_data_2); break;
            case 0x13 : Special_13(cc_data_2); break;
            case 0x14 : Special_14(cc_data_2); break;
            case 0x17 : Special_17(cc_data_2); break;
            default   : Illegal(cc_data_1, cc_data_2);
        }
    }

    //Saving data, for repetition of the code
    cc_data_1_Old=cc_data_1;
    cc_data_2_Old=cc_data_2;

    //With have a point of synchro
    if (!Synched)
        Synched=true;
}

//---------------------------------------------------------------------------
void File_Eia608::PreambleAddressCode(int8u cc_data_1, int8u cc_data_2)
{
    //CEA-608-E, Section F.1.1.5

    x=0; //I am not sure of this, specifications are not precise

    //Horizontal position
    if (!TextMode)
    {
        y=Eia608_PAC_Row[cc_data_1&0x0F]+((cc_data_2&0x20)?1:0);
        if (y>=Eia608_Rows)
        {
            y=Eia608_Rows-1;
        }
    }

    //Attributes (except Underline)
    if (cc_data_2&0x10) //0x5x and 0x7x
    {
        x=(cc_data_2&0x0E)<<1;
        Attribute_Current=Attribute_Color_White;
    }
    else if ((cc_data_2&0x0E)==0x0E) //0x4E, 0x4F, 0x6E, 0x6F
    {
        Attribute_Current=Attribute_Color_White|Attribute_Italic;
    }
    else //0x40-0x4D, 0x60-0x6D
        Attribute_Current=(cc_data_2&0x0E)>>1;

    //Underline
    if (cc_data_2&0x01)
        Attribute_Current|=Attribute_Underline;
}

//---------------------------------------------------------------------------
void File_Eia608::Special_10(int8u cc_data_2)
{
    switch (cc_data_2)
    {
        //CEA-608-E, Section 6.2
        case 0x20 : break;  //Background White, Opaque
        case 0x21 : break;  //Background White, Semi-transparent
        case 0x22 : break;  //
        case 0x23 : break;  //
        case 0x24 : break;  //
        case 0x25 : break;  //
        case 0x26 : break;  //
        case 0x27 : break;  //
        case 0x28 : break;  //
        case 0x29 : break;  //
        case 0x2A : break;  //
        case 0x2B : break;  //
        case 0x2C : break;  //
        case 0x2D : break;  //
        case 0x2E : break;  //
        case 0x2F : break;  //
        default   : Illegal(0x10, cc_data_2);
    }
}

//---------------------------------------------------------------------------
void File_Eia608::Special_11(int8u cc_data_2)
{
    switch (cc_data_2)
    {
        //CEA-608-E, Section F.1.1.3
        case 0x20 : //White
        case 0x21 : //White Underline
        case 0x22 : //
        case 0x23 : //
        case 0x24 : //
        case 0x25 : //
        case 0x26 : //
        case 0x27 : //
        case 0x28 : //
        case 0x29 : //
        case 0x2A : //
        case 0x2B : //
        case 0x2C : //
        case 0x2D : //
        case 0x2E : //
        case 0x2F : //
                    //Color or Italic
                    if ((cc_data_2&0xFE)==0x2E) //Italic
                        Attribute_Current|=Attribute_Italic;
                    else //Other attributes
                        Attribute_Current=(cc_data_2&0x0F)>>1;

                    //Underline
                    if (cc_data_2&0x01)
                        Attribute_Current|=Attribute_Underline;

                    break;
        //CEA-608-E, Section F.1.1.1
        case 0x30 : Character_Fill(L'\x2122'); break;  //Registered mark symbol
        case 0x31 : Character_Fill(L'\xB0'  ); break;  //Degree sign
        case 0x32 : Character_Fill(L'\xBD'  ); break;  //1/2
        case 0x33 : Character_Fill(L'\xBF'  ); break;  //interogation mark inverted
        case 0x34 : Character_Fill(L'\xA9'  ); break;  //Trademark symbol
        case 0x35 : Character_Fill(L'\xA2'  ); break;  //Cents sign
        case 0x36 : Character_Fill(L'\xA3'  ); break;  //Pounds Sterling sign
        case 0x37 : Character_Fill(L'\x266A'); break;  //Music note
        case 0x38 : Character_Fill(L'\xE0'  ); break;  //a grave
        case 0x39 : Character_Fill(L' '     ); break;  //Transparent space
        case 0x3A : Character_Fill(L'\xE8'  ); break;  //e grave
        case 0x3B : Character_Fill(L'\xE2'  ); break;  //a circumflex
        case 0x3C : Character_Fill(L'\xEA'  ); break;  //e circumflex
        case 0x3D : Character_Fill(L'\xEE'  ); break;  //i circumflex
        case 0x3E : Character_Fill(L'\xF4'  ); break;  //o circumflex
        case 0x3F : Character_Fill(L'\xFB'  ); break;  //u circumflex
        default   : Illegal(0x11, cc_data_2);
    }
}

//---------------------------------------------------------------------------
void File_Eia608::Special_12(int8u cc_data_2)
{
    switch (cc_data_2)
    {
        //CEA-608-E, Section 6.4.2
        case 0x20 : Character_Fill(L'A'     ); break;  //A with acute
        case 0x21 : Character_Fill(L'E'     ); break;  //E with acute
        case 0x22 : Character_Fill(L'O'     ); break;  //O with acute
        case 0x23 : Character_Fill(L'U'     ); break;  //U with acute
        case 0x24 : Character_Fill(L'U'     ); break;  //U withdiaeresis or umlaut
        case 0x25 : Character_Fill(L'u'     ); break;  //u with diaeresis or umlaut
        case 0x26 : Character_Fill(L'\''    ); break;  //opening single quote
        case 0x27 : Character_Fill(L'!'     ); break;  //inverted exclamation mark
        case 0x28 : Character_Fill(L'*'     ); break;  //Asterisk
        case 0x29 : Character_Fill(L'\''    ); break;  //plain single quote
        case 0x2A : Character_Fill(L'_'     ); break;  //em dash
        case 0x2B : Character_Fill(L'C'     ); break;  //Copyright
        case 0x2C : Character_Fill(L'S'     ); break;  //Servicemark
        case 0x2D : Character_Fill(L'x'     ); break;  //round bullet
        case 0x2E : Character_Fill(L'\"'    ); break;  //opening double quotes
        case 0x2F : Character_Fill(L'\"'    ); break;  //closing double quotes
        case 0x30 : Character_Fill(L'A'     ); break;  //A with grave accent
        case 0x31 : Character_Fill(L'A'     ); break;  //A with circumflex accent
        case 0x32 : Character_Fill(L'C'     ); break;  //C with cedilla
        case 0x33 : Character_Fill(L'E'     ); break;  //E with grave accent
        case 0x34 : Character_Fill(L'E'     ); break;  //E with circumflex accent
        case 0x35 : Character_Fill(L'E'     ); break;  //E with diaeresis or umlaut mark
        case 0x36 : Character_Fill(L'e'     ); break;  //e with diaeresis or umlaut mark
        case 0x37 : Character_Fill(L'I'     ); break;  //I with circumflex accent
        case 0x38 : Character_Fill(L'I'     ); break;  //I with diaeresis or umlaut mark
        case 0x39 : Character_Fill(L'i'     ); break;  //i with diaeresis or umlaut mark
        case 0x3A : Character_Fill(L'O'     ); break;  //O with circumflex
        case 0x3B : Character_Fill(L'U'     ); break;  //U with grave accent
        case 0x3C : Character_Fill(L'u'     ); break;  //u with grave accent
        case 0x3D : Character_Fill(L'U'     ); break;  //U with circumflex accent
        case 0x3E : Character_Fill(L'\"'    ); break;  //opening guillemets
        case 0x3F : Character_Fill(L'\"'    ); break;  //closing guillemets
        default   : Illegal(0x12, cc_data_2);
    }
}

//---------------------------------------------------------------------------
void File_Eia608::Special_13(int8u cc_data_2)
{
    switch (cc_data_2)
    {
        //CEA-608-E, Section 6.4.2
        case 0x20 : Character_Fill(L'A'     ); break;  //A with tilde
        case 0x21 : Character_Fill(L'a'     ); break;  //a with tilde
        case 0x22 : Character_Fill(L'I'     ); break;  //I with acute accent
        case 0x23 : Character_Fill(L'I'     ); break;  //I with grave accent
        case 0x24 : Character_Fill(L'i'     ); break;  //i with grave accent
        case 0x25 : Character_Fill(L'O'     ); break;  //O with grave accent
        case 0x26 : Character_Fill(L'o'     ); break;  //o with grave accent
        case 0x27 : Character_Fill(L'O'     ); break;  //O with tilde
        case 0x28 : Character_Fill(L'o'     ); break;  //o with tilde
        case 0x29 : Character_Fill(L'{'     ); break;  //opening brace
        case 0x2A : Character_Fill(L'}'     ); break;  //closing brace
        case 0x2B : Character_Fill(L'\\'    ); break;  //backslash
        case 0x2C : Character_Fill(L'^'     ); break;  //caret
        case 0x2D : Character_Fill(L'_'     ); break;  //Underbar
        case 0x2E : Character_Fill(L'|'     ); break;  //pipe
        case 0x2F : Character_Fill(L'~'     ); break;  //tilde
        case 0x30 : Character_Fill(L'A'     ); break;  //A with diaeresis or umlaut mark
        case 0x31 : Character_Fill(L'a'     ); break;  //a with diaeresis or umlaut mark
        case 0x32 : Character_Fill(L'O'     ); break;  //o with diaeresis or umlaut mark
        case 0x33 : Character_Fill(L'o'     ); break;  //o with diaeresis or umlaut mark
        case 0x34 : Character_Fill(L's'     ); break;  //eszett (mall sharp s)
        case 0x35 : Character_Fill(L'Y'     ); break;  //yen
        case 0x36 : Character_Fill(L' '     ); break;  //non-specific currency sign
        case 0x37 : Character_Fill(L'|'     ); break;  //Vertical bar
        case 0x38 : Character_Fill(L'A'     ); break;  //I with diaeresis or umlaut mark
        case 0x39 : Character_Fill(L'a'     ); break;  //i with diaeresis or umlaut mark
        case 0x3A : Character_Fill(L'O'     ); break;  //O with ring
        case 0x3B : Character_Fill(L'o'     ); break;  //a with ring
        case 0x3C : Character_Fill(L' '     ); break;  //upper left corner
        case 0x3D : Character_Fill(L' '     ); break;  //upper right corner
        case 0x3E : Character_Fill(L' '     ); break;  //lower left corner
        case 0x3F : Character_Fill(L' '     ); break;  //lower right corner
        default   : Illegal(0x13, cc_data_2);
    }
}

//---------------------------------------------------------------------------
void File_Eia608::Special_14(int8u cc_data_2)
{
    switch (cc_data_2)
    {
        case 0x20 : //RCL - Resume Caption Loading
        case 0x25 : //RU2 - Roll-Up Captions�2 Rows
        case 0x26 : //RU3 - Roll-Up Captions�3 Rows
        case 0x27 : //RU4 - Roll-Up Captions�4 Rows
        case 0x29 : //RDC - Resume Direct Captioning
        case 0x2F : //EOC - End of Caption
                    TextMode=false; break; //This is CC
        case 0x2A : //TR  - Text Restart
        case 0x2B : //RTD - Resume Text Display
                    TextMode=true; break; //This is Text
        default: ;
    }

    switch (cc_data_2)
    {
        case 0x20 : TextMode=false;
                    InBack=true;
                    break; //RCL - Resume Caption Loading (Select pop-on style)
        case 0x21 : if (x)
                        x--;
                    (InBack?CC_NonDisplayed:CC_Displayed)[y][x].Value=L' '; //Clear the character
                    if (!InBack)
                        HasChanged();
                    break; //BS  - Backspace
        case 0x22 : Special_14(0x2D); //Found 1 file with AOF and non CR
                    break; //AOF - Alarm Off
        case 0x23 : break; //AON - Alarm On
        case 0x24 : for (size_t Pos=x; Pos<Eia608_Columns; Pos++)
                        (InBack?CC_NonDisplayed:CC_Displayed)[y][Pos].Value=L' '; //Clear up to the end of line
                    if (!InBack)
                        HasChanged();
                    break; //DER - Delete to End of Row
        case 0x25 : //RU2 - Roll-Up Captions�2 Rows
        case 0x26 : //RU3 - Roll-Up Captions�3 Rows
        case 0x27 : //RU4 - Roll-Up Captions�4 Rows
                    RollUpLines=cc_data_2-0x25+2;
                    InBack=false;
                    break; //RUx - Roll-Up Captions�x Rows
        case 0x28 : break; //FON - Flash On
        case 0x29 : InBack=false;
                    break; //RDC - Resume Direct Captioning (paint-on style)
        case 0x2A : TextMode=true;
                    RollUpLines=Eia608_Rows; //Roll up all the lines
                    y=Eia608_Rows-1; //Base is the bottom line
                    Attribute_Current=0; //Reset all attributes
                    Special_14(0x2D); //Next line
                    break; //TR  - Text Restart (clear Text, but not boxes)
        case 0x2B : TextMode=true;
                    break; //RTD - Resume Text Display
        case 0x2C :
                    for (size_t Pos_Y=0; Pos_Y<Eia608_Rows; Pos_Y++)
                        for (size_t Pos_X=0; Pos_X<Eia608_Columns; Pos_X++)
                        {
                            CC_Displayed[Pos_Y][Pos_X].Value=L' ';
                            CC_Displayed[Pos_Y][Pos_X].Attribute=0;
                        }
                    HasChanged();
                    break; //EDM - Erase Displayed Memory
        case 0x2D : for (size_t Pos=1; Pos<RollUpLines; Pos++)
                    {
                        if (y>=RollUpLines-Pos && y-RollUpLines+Pos+1<Eia608_Rows)
                        {
                            if (TextMode)
                                Text_Displayed[y-RollUpLines+Pos]=Text_Displayed[y-RollUpLines+Pos+1];
                            else
                                CC_Displayed[y-RollUpLines+Pos]=CC_Displayed[y-RollUpLines+Pos+1];
                        }
                    }
                    for (size_t Pos_X=0; Pos_X<Eia608_Columns; Pos_X++)
                    {
                        if (TextMode)
                        {
                            Text_Displayed[y][Pos_X].Value=L' ';
                            Text_Displayed[y][Pos_X].Attribute=0;
                        }
                        else
                        {
                            CC_Displayed[y][Pos_X].Value=L' ';
                            CC_Displayed[y][Pos_X].Attribute=0;
                        }
                    }
                    if (!InBack)
                        HasChanged();
                    x=0;
                    break; //CR  - Carriage Return
        case 0x2E : for (size_t Pos_Y=0; Pos_Y<Eia608_Rows; Pos_Y++)
                        for (size_t Pos_X=0; Pos_X<Eia608_Columns; Pos_X++)
                        {
                            CC_NonDisplayed[Pos_Y][Pos_X].Value=L' ';
                            CC_NonDisplayed[Pos_Y][Pos_X].Attribute=0;
                        }
                    break; //ENM - Erase Non-Displayed Memory
        case 0x2F : CC_Displayed.swap(CC_NonDisplayed);
                        HasChanged();
                    break; //EOC - End of Caption
        default   : Illegal(0x14, cc_data_2);
    }
}

//---------------------------------------------------------------------------
void File_Eia608::Special_17(int8u cc_data_2)
{
    switch (cc_data_2)
    {
        //CEA-608-E, section B.4
        case 0x20 : //TO1 - Tab Offset 1 Column
        case 0x21 : //TO2 - Tab Offset 2 Columns
        case 0x22 : //TO3 - Tab Offset 3 Columns
                    x+=cc_data_2&0x03;
                    if (x>=Eia608_Columns)
                        x=Eia608_Columns-1;
                    break;
        //CEA-608-E, section 6.3
        case 0x24 : break;  //Select the standard line 21 character set in normal size
        case 0x25 : break;  //Select the standard line 21 character set in double size
        case 0x26 : break;  //Select the first private character set
        case 0x27 : break;  //Select the second private character set
        case 0x28 : break;  //Select the People's Republic of China character set: GB 2312-80
        case 0x29 : break;  //Select the Korean Standard character set: KSC 5601-1987
        case 0x2A : break;  //Select the first registered character set
        //CEA-608-E, section 6.2
        case 0x2D : break;  //Background Transparent
        case 0x2E : break;  //Foreground Black
        case 0x2F : break;  //Foreground Black Underline
        default   : Illegal(0x17, cc_data_2);
    }
}

//---------------------------------------------------------------------------
void File_Eia608::Standard(int8u Character)
{
    switch (Character)
    {
        //CEA-608-E, Section F.1.1.2
        case 0x20 : Character_Fill(L' '     ); break;
        case 0x21 : Character_Fill(L'!'     ); break;
        case 0x22 : Character_Fill(L'"'     ); break;
        case 0x23 : Character_Fill(L'#'     ); break;
        case 0x24 : Character_Fill(L'$'     ); break;
        case 0x25 : Character_Fill(L'%'     ); break;
        case 0x26 : Character_Fill(L'&'     ); break;
        case 0x27 : Character_Fill(L'\''    ); break;
        case 0x28 : Character_Fill(L'('     ); break;
        case 0x29 : Character_Fill(L')'     ); break;
        case 0x2A : Character_Fill(L'\xE1'  ); break; //a acute
        case 0x2B : Character_Fill(L'+'     ); break;
        case 0x2C : Character_Fill(L','     ); break;
        case 0x2D : Character_Fill(L'-'     ); break;
        case 0x2E : Character_Fill(L'.'     ); break;
        case 0x2F : Character_Fill(L'/'     ); break;
        case 0x30 : Character_Fill(L'0'     ); break;
        case 0x31 : Character_Fill(L'1'     ); break;
        case 0x32 : Character_Fill(L'2'     ); break;
        case 0x33 : Character_Fill(L'3'     ); break;
        case 0x34 : Character_Fill(L'4'     ); break;
        case 0x35 : Character_Fill(L'5'     ); break;
        case 0x36 : Character_Fill(L'6'     ); break;
        case 0x37 : Character_Fill(L'7'     ); break;
        case 0x38 : Character_Fill(L'8'     ); break;
        case 0x39 : Character_Fill(L'9'     ); break;
        case 0x3A : Character_Fill(L':'     ); break;
        case 0x3B : Character_Fill(L';'     ); break;
        case 0x3C : Character_Fill(L'<'     ); break;
        case 0x3E : Character_Fill(L'>'     ); break;
        case 0x3F : Character_Fill(L'?'     ); break;
        case 0x40 : Character_Fill(L'@'     ); break;
        case 0x41 : Character_Fill(L'A'     ); break;
        case 0x42 : Character_Fill(L'B'     ); break;
        case 0x43 : Character_Fill(L'C'     ); break;
        case 0x44 : Character_Fill(L'D'     ); break;
        case 0x45 : Character_Fill(L'E'     ); break;
        case 0x46 : Character_Fill(L'F'     ); break;
        case 0x47 : Character_Fill(L'G'     ); break;
        case 0x48 : Character_Fill(L'H'     ); break;
        case 0x49 : Character_Fill(L'I'     ); break;
        case 0x4A : Character_Fill(L'J'     ); break;
        case 0x4B : Character_Fill(L'K'     ); break;
        case 0x4C : Character_Fill(L'L'     ); break;
        case 0x4D : Character_Fill(L'M'     ); break;
        case 0x4E : Character_Fill(L'N'     ); break;
        case 0x4F : Character_Fill(L'O'     ); break;
        case 0x50 : Character_Fill(L'P'     ); break;
        case 0x51 : Character_Fill(L'Q'     ); break;
        case 0x52 : Character_Fill(L'R'     ); break;
        case 0x53 : Character_Fill(L'S'     ); break;
        case 0x54 : Character_Fill(L'T'     ); break;
        case 0x55 : Character_Fill(L'U'     ); break;
        case 0x56 : Character_Fill(L'V'     ); break;
        case 0x57 : Character_Fill(L'W'     ); break;
        case 0x58 : Character_Fill(L'X'     ); break;
        case 0x59 : Character_Fill(L'Y'     ); break;
        case 0x5A : Character_Fill(L'Z'     ); break;
        case 0x5B : Character_Fill(L'['     ); break;
        case 0x5C : Character_Fill(L'\xE9'  ); break; //e acute
        case 0x5D : Character_Fill(L']'     ); break;
        case 0x5E : Character_Fill(L'\xED'  ); break; //i acute
        case 0x5F : Character_Fill(L'\xF3'  ); break; //o acute
        case 0x60 : Character_Fill(L'\xFA'  ); break; //u acute
        case 0x61 : Character_Fill(L'a'     ); break;
        case 0x62 : Character_Fill(L'b'     ); break;
        case 0x63 : Character_Fill(L'c'     ); break;
        case 0x64 : Character_Fill(L'd'     ); break;
        case 0x65 : Character_Fill(L'e'     ); break;
        case 0x66 : Character_Fill(L'f'     ); break;
        case 0x67 : Character_Fill(L'g'     ); break;
        case 0x68 : Character_Fill(L'h'     ); break;
        case 0x69 : Character_Fill(L'i'     ); break;
        case 0x6A : Character_Fill(L'j'     ); break;
        case 0x6B : Character_Fill(L'k'     ); break;
        case 0x6C : Character_Fill(L'l'     ); break;
        case 0x6D : Character_Fill(L'm'     ); break;
        case 0x6E : Character_Fill(L'n'     ); break;
        case 0x6F : Character_Fill(L'o'     ); break;
        case 0x70 : Character_Fill(L'p'     ); break;
        case 0x71 : Character_Fill(L'q'     ); break;
        case 0x72 : Character_Fill(L'r'     ); break;
        case 0x73 : Character_Fill(L's'     ); break;
        case 0x74 : Character_Fill(L't'     ); break;
        case 0x75 : Character_Fill(L'u'     ); break;
        case 0x76 : Character_Fill(L'v'     ); break;
        case 0x77 : Character_Fill(L'w'     ); break;
        case 0x78 : Character_Fill(L'x'     ); break;
        case 0x79 : Character_Fill(L'y'     ); break;
        case 0x7A : Character_Fill(L'z'     ); break;
        case 0x7B : Character_Fill(L'\xE7'  ); break; //c with cedilla
        case 0x7C : Character_Fill(L'\xF7'  ); break; //division symbol
        case 0x7D : Character_Fill(L'\xD1'  ); break; //N tilde
        case 0x7E : Character_Fill(L'\xF1'  ); break; //n tilde
        case 0x7F : Character_Fill(L'\x25A0'); break; //Solid block
        default   : Illegal(0x00, Character);
    }
}

//---------------------------------------------------------------------------
void File_Eia608::Character_Fill(wchar_t Character)
{
    if (x==Eia608_Columns)
    {
        x--; //There is a problem

        //TODO: Put it at the end, for the conversion
        //TODO: Handle special chars
    }

    if (TextMode)
    {
        Text_Displayed[y][x].Value=Character;
    }
    else if (InBack)
    {
        CC_NonDisplayed[y][x].Value=Character;
    }
    else
    {
        CC_Displayed[y][x].Value=Character;
    }

    x++;
    
    if (TextMode || !InBack)
        HasChanged();

    if (!HasContent)
        HasContent=true;
    if (!Status[IsFilled]) //TODO: separate CC1/CC2/T1/T2
    {
        Fill("EIA-608");
        if (MediaInfoLib::Config.ParseSpeed_Get()<1)
            Finish("EIA-608");
    }
}

//---------------------------------------------------------------------------
void File_Eia608::HasChanged()
{
}

//---------------------------------------------------------------------------
void File_Eia608::Illegal(int8u cc_data_1, int8u cc_data_2)
{
}

//***************************************************************************
// C++
//***************************************************************************

} //NameSpace

#endif //MEDIAINFO_EIA608_YES
