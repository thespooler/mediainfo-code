// File_DvDif - Info for DV-DIF files
// Copyright (C) 2002-2009 Jerome Martinez, Zen@MediaArea.net
//
// This library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
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
#if defined(MEDIAINFO_DVDIF_YES) && defined(MEDIAINFO_DVDIF_ANALYZE_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Multiple/File_DvDif.h"
#include "MediaInfo/MediaInfo_Config_MediaInfo.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Analysis
//***************************************************************************

//---------------------------------------------------------------------------
void File_DvDif::Read_Buffer_Continue()
{
    if (!Analyze_Activated)
    {
        if (Config->File_DvDif_Analysis_Get())
            Analyze_Activated=true;
        else
            return;    
    }       

    //Errors stats
    while (Buffer_Offset+80<=Buffer_Size)
    {
        if ((Buffer[Buffer_Offset]&0xE0)==0x00  //SCT=0 (Header)
         && !(Buffer[Buffer_Offset  ]==0x00
           && Buffer[Buffer_Offset+1]==0x00
           && Buffer[Buffer_Offset+2]==0x00))
        {
            Frame_AtLeast1DIF=true;

            if (!DSF_IsValid)
            {
                DSF=(Buffer[Buffer_Offset+3]&0x80)?true:false;
                DSF_IsValid=true;
                Dseq_Old=DSF?11:9;
            }
        }

        //Quick search depends of SCT
        switch(Buffer[Buffer_Offset]&0xE0)
        {
            case 0x20 : //SCT=1 (Subcode)
                {
                    Frame_AtLeast1DIF=true;

                    for (size_t Pos=3*8; Pos<40; Pos+=2*8)
                    {
                        int8u PackType=Buffer[Buffer_Offset+3+Pos+3];
                        //timecode
                        if (PackType==0x13) //Pack type=0x13 (timecode)
                        {
                            bool  DropFrame                 =( Buffer[Buffer_Offset+3+Pos+3+1]&0x40)?true:false;
                            int8u Frames                    =((Buffer[Buffer_Offset+3+Pos+3+1]&0x30)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+3+1]&0x0F)   )   ;
                            int8u Seconds                   =((Buffer[Buffer_Offset+3+Pos+3+2]&0x70)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+3+2]&0x0F))      ;
                            int8u Minutes                   =((Buffer[Buffer_Offset+3+Pos+3+3]&0x70)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+3+3]&0x0F)   )   ;
                            int8u Hours                     =((Buffer[Buffer_Offset+3+Pos+3+4]&0x30)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+3+4]&0x0F)   )   ;

                            if (Frames ==0x00
                             && Seconds==0x00
                             && Minutes==0x00
                             && Hours  ==0x00
                             && Buffer[Buffer_Offset+3+Pos+3+1]==0x00
                             && Buffer[Buffer_Offset+3+Pos+3+2]==0x00
                             && Buffer[Buffer_Offset+3+Pos+3+3]==0x00
                             && Buffer[Buffer_Offset+3+Pos+3+4]==0x00
                             )
                            {
                                Frames =45;
                                Seconds=85;
                                Minutes=85;
                                Hours  =45;
                            }
                            if (Frames !=45
                             && Seconds!=85
                             && Minutes!=85
                             && Hours  !=45) //If not disabled
                            {
                                if (Speed_TimeCode_Current.IsValid
                                 && (Speed_TimeCode_Current.DropFrame !=DropFrame
                                  || Speed_TimeCode_Current.Frames    !=Frames
                                  || Speed_TimeCode_Current.Seconds   !=Seconds
                                  || Speed_TimeCode_Current.Minutes   !=Minutes
                                  || Speed_TimeCode_Current.Hours     !=Hours))
                                {
                                    Speed_TimeCode_Current.MultipleValues=true; //There are 2+ different values
                                }
                                else if (!Speed_TimeCode_Current.IsValid && !Speed_TimeCode_Current.MultipleValues)
                                {
                                    Speed_TimeCode_Current.DropFrame=DropFrame;
                                    Speed_TimeCode_Current.Frames   =Frames;
                                    Speed_TimeCode_Current.Seconds  =Seconds;
                                    Speed_TimeCode_Current.Minutes  =Minutes;
                                    Speed_TimeCode_Current.Hours    =Hours;
                                    Speed_TimeCode_Current.IsValid  =true;
                                }
                            }
                        }

                        //video_recdate
                        if (PackType==0x62) //Pack type=0x62 (video_rectime)
                        {
                            int8u Days                      =((Buffer[Buffer_Offset+3+Pos+2]&0x30)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+2]&0x0F)   )   ;
                            int8u Months                    =((Buffer[Buffer_Offset+3+Pos+3]&0x10)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+3]&0x0F)   )   ;
                            int8u Years                     =((Buffer[Buffer_Offset+3+Pos+4]&0xF0)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+4]&0x0F)   )   ;
                            if (Months<=12
                             && Days  <=31)
                            {
                                if (Speed_RecDate_Current.IsValid
                                 && Speed_RecDate_Current.Days      !=Days
                                 && Speed_RecDate_Current.Months     !=Months
                                 && Speed_RecDate_Current.Years     !=Years)
                                {
                                    Speed_RecDate_Current.MultipleValues=true; //There are 2+ different values
                                }
                                else if (!Speed_RecTime_Current.MultipleValues)
                                {
                                    Speed_RecDate_Current.Days     =Days;
                                    Speed_RecDate_Current.Months   =Months;
                                    Speed_RecDate_Current.Years    =Years;
                                    Speed_RecDate_Current.IsValid  =true;
                                }
                            }
                        }

                        //video_rectime
                        if (PackType==0x63) //Pack type=0x63 (video_rectime)
                        {
                            int8u Frames                    =((Buffer[Buffer_Offset+3+Pos+1]&0x30)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+1]&0x0F)   )   ;
                            int8u Seconds                   =((Buffer[Buffer_Offset+3+Pos+2]&0x70)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+2]&0x0F))      ;
                            int8u Minutes                   =((Buffer[Buffer_Offset+3+Pos+3]&0x70)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+3]&0x0F)   )   ;
                            int8u Hours                     =((Buffer[Buffer_Offset+3+Pos+4]&0x30)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+4]&0x0F)   )   ;
                            if (Seconds<61
                             && Minutes<60
                             && Hours  <24) //If not disabled
                            {
                                if (Speed_RecTime_Current.IsValid
                                 && Speed_RecTime_Current.Frames    !=Frames
                                 && Speed_RecTime_Current.Seconds   !=Seconds
                                 && Speed_RecTime_Current.Minutes   !=Minutes
                                 && Speed_RecTime_Current.Hours     !=Hours)
                                {
                                    Speed_RecTime_Current.MultipleValues=true; //There are 2+ different values
                                }
                                else if (!Speed_RecTime_Current.MultipleValues)
                                {
                                    Speed_RecTime_Current.Frames   =Frames;
                                    Speed_RecTime_Current.Seconds  =Seconds;
                                    Speed_RecTime_Current.Minutes  =Minutes;
                                    Speed_RecTime_Current.Hours    =Hours;
                                    Speed_RecTime_Current.IsValid  =true;
                                }
                            }
                        }
                    }
                }
                break;

            case 0x40 : //SCT=2 (VAUX)
                {
                    Frame_AtLeast1DIF=true;

                    for (size_t Pos=0; Pos<15*5; Pos+=5)
                    {
                        int8u PackType=Buffer[Buffer_Offset+3+Pos];
                        //video_source
                        if (PackType==0x60 && !System_IsValid) //Pack type=0x60 (video_source)
                        {
                            System=(Buffer[Buffer_Offset+3+Pos+3]&0x20)==0x20?true:false;
                            System_IsValid=true;
                        }

                        //video_recdate
                        if (PackType==0x62) //Pack type=0x62 (video_rectime)
                        {
                            int8u Days                      =((Buffer[Buffer_Offset+3+Pos+2]&0x30)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+2]&0x0F)   )   ;
                            int8u Months                    =((Buffer[Buffer_Offset+3+Pos+3]&0x10)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+3]&0x0F)   )   ;
                            int8u Years                     =((Buffer[Buffer_Offset+3+Pos+4]&0xF0)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+4]&0x0F)   )   ;
                            if (Months<=12
                             && Days  <=31)
                            {
                                if (Speed_RecDate_Current.IsValid
                                 && Speed_RecDate_Current.Days      !=Days
                                 && Speed_RecDate_Current.Months     !=Months
                                 && Speed_RecDate_Current.Years     !=Years)
                                {
                                    Speed_RecDate_Current.MultipleValues=true; //There are 2+ different values
                                }
                                else if (!Speed_RecTime_Current.MultipleValues)
                                {
                                    Speed_RecDate_Current.Days     =Days;
                                    Speed_RecDate_Current.Months   =Months;
                                    Speed_RecDate_Current.Years    =Years;
                                    Speed_RecDate_Current.IsValid  =true;
                                }
                            }
                        }

                        //video_rectime
                        if (PackType==0x63) //Pack type=0x63 (video_rectime)
                        {
                            int8u Frames                    =((Buffer[Buffer_Offset+3+Pos+1]&0x30)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+1]&0x0F)   )   ;
                            int8u Seconds                   =((Buffer[Buffer_Offset+3+Pos+2]&0x70)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+2]&0x0F))      ;
                            int8u Minutes                   =((Buffer[Buffer_Offset+3+Pos+3]&0x70)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+3]&0x0F)   )   ;
                            int8u Hours                     =((Buffer[Buffer_Offset+3+Pos+4]&0x30)>>4)*10
                                                           + ((Buffer[Buffer_Offset+3+Pos+4]&0x0F)   )   ;
                            if (Seconds!=85
                             && Minutes!=85
                             && Hours  !=45) //If not disabled
                            {
                                if (Speed_RecTime_Current.IsValid
                                 && Speed_RecTime_Current.Frames    !=Frames
                                 && Speed_RecTime_Current.Seconds   !=Seconds
                                 && Speed_RecTime_Current.Minutes   !=Minutes
                                 && Speed_RecTime_Current.Hours     !=Hours)
                                {
                                    Speed_RecTime_Current.MultipleValues=true; //There are 2+ different values
                                }
                                else if (!Speed_RecTime_Current.MultipleValues)
                                {
                                    Speed_RecTime_Current.Frames   =Frames;
                                    Speed_RecTime_Current.Seconds  =Seconds;
                                    Speed_RecTime_Current.Minutes  =Minutes;
                                    Speed_RecTime_Current.Hours    =Hours;
                                    Speed_RecTime_Current.IsValid  =true;
                                }
                            }
                        }
                    }
                }
                break;

            case 0x60 : //SCT=3 (Audio)
                {
                    //audio_source
                    if (Buffer[Buffer_Offset+3+0]==0x50) //audio_source
                    {
                              QU_FSC    =(Buffer[Buffer_Offset+1  ]&0x08)?true:false; //FSC
                              QU_System =(Buffer[Buffer_Offset+3+3]&0x20)?true:false; //50/60

                        int8u AUDIO_MODE=Buffer[Buffer_Offset+3+2]&0x0F;
                              QU        =Buffer[Buffer_Offset+3+4]&0x07;

                        size_t Channel=(QU_FSC?2:0)+((Buffer[Buffer_Offset+1]>>4)>=(QU_System?6:5)?1:0); //If Dseq>=5 or 6
                        if (audio_source_IsPresent.empty())
                            audio_source_IsPresent.resize(8);
                        audio_source_IsPresent[Channel]=true;

                        if (AUDIO_MODE==0x0F)
                        {
                            if (Audio_Invalids.empty())
                            {
                                Audio_Invalids.resize(8);
                                for (size_t Pos=0; Pos<8; Pos++)
                                    Audio_Invalids[Pos].resize(16);
                            }
                            Audio_Invalids[Channel][Buffer[Buffer_Offset+1]>>4]+=9;
                        }
                    }

                    //audio_source_control
                    if (Buffer[Buffer_Offset+3+0]==0x51) //audio_source_control
                    {
                        REC_ST =(Buffer[Buffer_Offset+3+2]&0x80)?true:false;
                        REC_END=(Buffer[Buffer_Offset+3+2]&0x40)?true:false;
                        REC_IsValid=true;
                    }

                    //audio_recdate
                    if (Buffer[Buffer_Offset+3+0]==0x52) //Pack type=0x52 (audio_rectime)
                    {
                        int8u Days                      =((Buffer[Buffer_Offset+3+2]&0x30)>>4)*10
                                                       + ((Buffer[Buffer_Offset+3+2]&0x0F)   )   ;
                        int8u Months                    =((Buffer[Buffer_Offset+3+3]&0x10)>>4)*10
                                                       + ((Buffer[Buffer_Offset+3+3]&0x0F)   )   ;
                        int8u Years                     =((Buffer[Buffer_Offset+3+4]&0xF0)>>4)*10
                                                       + ((Buffer[Buffer_Offset+3+4]&0x0F)   )   ;
                        if (Months<=12
                         && Days  <=31)
                        {
                            if (Speed_RecDate_Current.IsValid
                             && Speed_RecDate_Current.Days      !=Days
                             && Speed_RecDate_Current.Months     !=Months
                             && Speed_RecDate_Current.Years     !=Years)
                            {
                                Speed_RecDate_Current.MultipleValues=true; //There are 2+ different values
                            }
                            else if (!Speed_RecTime_Current.MultipleValues)
                            {
                                Speed_RecDate_Current.Days     =Days;
                                Speed_RecDate_Current.Months   =Months;
                                Speed_RecDate_Current.Years    =Years;
                                Speed_RecDate_Current.IsValid  =true;
                            }
                        }
                    }

                    //audio_rectime
                    if (Buffer[Buffer_Offset+3+0]==0x53) //Pack type=0x53 (audio_rectime)
                    {
                        int8u Frames                    =((Buffer[Buffer_Offset+3+1]&0x30)>>4)*10
                                                       + ((Buffer[Buffer_Offset+3+1]&0x0F)   )   ;
                        int8u Seconds                   =((Buffer[Buffer_Offset+3+2]&0x70)>>4)*10
                                                       + ((Buffer[Buffer_Offset+3+2]&0x0F))      ;
                        int8u Minutes                   =((Buffer[Buffer_Offset+3+3]&0x70)>>4)*10
                                                       + ((Buffer[Buffer_Offset+3+3]&0x0F)   )   ;
                        int8u Hours                     =((Buffer[Buffer_Offset+3+4]&0x30)>>4)*10
                                                       + ((Buffer[Buffer_Offset+3+4]&0x0F)   )   ;
                        if (Seconds!=85
                         && Minutes!=85
                         && Hours  !=45) //If not disabled
                        {
                            if (Speed_RecTime_Current.IsValid
                             && Speed_RecTime_Current.Frames    !=Frames
                             && Speed_RecTime_Current.Seconds   !=Seconds
                             && Speed_RecTime_Current.Minutes   !=Minutes
                             && Speed_RecTime_Current.Hours     !=Hours)
                            {
                                Speed_RecTime_Current.MultipleValues=true; //There are 2+ different values
                            }
                            else if (!Speed_RecTime_Current.MultipleValues)
                            {
                                Speed_RecTime_Current.Frames   =Frames;
                                Speed_RecTime_Current.Seconds  =Seconds;
                                Speed_RecTime_Current.Minutes  =Minutes;
                                Speed_RecTime_Current.Hours    =Hours;
                                Speed_RecTime_Current.IsValid  =true;
                            }
                        }
                    }

                    //Audio errors
                    if (Buffer[Buffer_Offset+8]==0x80)
                    {
                        if (QU==0 && Buffer[Buffer_Offset+ 9]==0x00  //16-bit 0x8000
                         || QU==1 && Buffer[Buffer_Offset+10]==0x00  //12-bit 0x800
                         || QU==(int8u)-1 && (Buffer[Buffer_Offset+ 9]==0x00 && Buffer[Buffer_Offset+10]==0x80 && Buffer[Buffer_Offset+11]==0x00
                                           || Buffer[Buffer_Offset+ 9]==0x80 && Buffer[Buffer_Offset+10]==0x00)) //In case of QU is not already detected
                        {
                            if (Audio_Errors.empty())
                                Audio_Errors.resize(16);
                            Audio_Errors[Buffer[Buffer_Offset+1]>>4]++;
                        }
                    }
                }
                break;

            case 0x80 : //SCT=4 (Video)
                {
                    //Arb
                    int8u Value=Buffer[Buffer_Offset+0]&0x0F;
                    if (Value==0xF)
                        break;    
                    if (Arb.IsValid
                     && Arb.Value!=Value)
                        Arb.MultipleValues=true; //There are 2+ different values
                    else if (!Arb.MultipleValues)
                    {
                        Arb.Value  =Value;
                        Arb.IsValid=true;
                    }

                    //STA
                    if (Buffer[Buffer_Offset+3]&0xF0)
                    {
                        if (Video_STA_Errors.empty())
                            Video_STA_Errors.resize(16);
                        Video_STA_Errors[Buffer[Buffer_Offset+3]>>4]++;
                    }
                }
                break;
        }

        //Errors stats
        if (Frame_AtLeast1DIF &&
            (Buffer[Buffer_Offset  ]&0xE0)==0x00  //SCT=0 (Header)
         && (Buffer[Buffer_Offset+1]&0xF0)==0x00  //Dseq=0
         && (Buffer[Buffer_Offset+1]&0x08)==0x00) //FSC=0
            Errors_Stats_Update();

        //Coherency test
        if (Buffer[Buffer_Offset  ]==0x00
         && Buffer[Buffer_Offset+1]==0x00
         && Buffer[Buffer_Offset+2]==0x00)
           Speed_Contains_NULL++;

        Buffer_Offset+=80;
    }

    if (!Status[IsAccepted])
        File__Analyze::Buffer_Offset=0;
}

void File_DvDif::Errors_Stats_Update()
{
    if (!Analyze_Activated)
    {
        if (Config->File_DvDif_Analysis_Get())
            Analyze_Activated=true;
        else
            return;    
    }       

    bool Errors_AreDetected=false;
    bool Infos_AreDetected=false;
    Ztring Errors_Stats_Line;
    if (Speed_FrameCount) //We must have at least one complete frame
    {
        //Framerate computing
        float64 FrameRate=29.970;
        if (System_IsValid)
            FrameRate=System?25.000:29.970;
        else if (DSF_IsValid)
            FrameRate=DSF?25.000:29.970;
        else
            FrameRate=29.970;
        if (FrameRate==29.970 && Speed_TimeCode_Current.IsValid && !Speed_TimeCode_Current.DropFrame)
            FrameRate=30.000;

        //Frame number
        Ztring Frame_Number_Padded=Ztring::ToZtring(Speed_FrameCount-1);
        if (Frame_Number_Padded.size()<8)
            Frame_Number_Padded.insert(0, 8-Frame_Number_Padded.size(), _T(' '));
        Errors_Stats_Line+=Frame_Number_Padded;
        Errors_Stats_Line+=_T('\t');

        //Time Offset
        float64 Time_Offset=(Speed_FrameCount-1)*1000/FrameRate;
        Errors_Stats_Line+=Ztring().Duration_From_Milliseconds((int64u)Time_Offset);
        Errors_Stats_Line+=_T('\t');

        //TimeCode
        if (Speed_TimeCode_Current.IsValid)
        {
            Speed_TimeCodeZ_Last=Speed_TimeCodeZ_Current;
            Speed_TimeCodeZ_Current.clear();
            Speed_TimeCodeZ_Current.reserve(12);
            Speed_TimeCodeZ_Current.reserve(11);
            Speed_TimeCodeZ_Current+=_T('0')+Speed_TimeCode_Current.Hours  /10;
            Speed_TimeCodeZ_Current+=_T('0')+Speed_TimeCode_Current.Hours  %10;
            Speed_TimeCodeZ_Current+=_T(':');
            Speed_TimeCodeZ_Current+=_T('0')+Speed_TimeCode_Current.Minutes/10;
            Speed_TimeCodeZ_Current+=_T('0')+Speed_TimeCode_Current.Minutes%10;
            Speed_TimeCodeZ_Current+=_T(':');
            Speed_TimeCodeZ_Current+=_T('0')+Speed_TimeCode_Current.Seconds/10;
            Speed_TimeCodeZ_Current+=_T('0')+Speed_TimeCode_Current.Seconds%10;
            Speed_TimeCodeZ_Current+=(!DSF && Speed_TimeCode_Current.DropFrame)?_T(';'):_T(':');
            Speed_TimeCodeZ_Current+=_T('0')+Speed_TimeCode_Current.Frames /10;
            Speed_TimeCodeZ_Current+=_T('0')+Speed_TimeCode_Current.Frames %10;
            Errors_Stats_Line+=Speed_TimeCodeZ_Current;
            if (Speed_TimeCodeZ.empty())
            {
                Speed_TimeCodeZ.resize(1);
                Speed_TimeCodeZ[0].First.FramePos=Speed_FrameCount;
                Speed_TimeCodeZ[0].First.TimeCode=Speed_TimeCodeZ_Current;
            }
            if (Speed_TimeStampsZ.empty())
            {
                Speed_TimeStampsZ.resize(1);
                Speed_TimeStampsZ[0].First.FramePos=Speed_FrameCount;
                float64 Time_Offset=(Speed_FrameCount-1)*1000/FrameRate;
                Speed_TimeStampsZ[0].First.Time+=Ztring().Duration_From_Milliseconds((int64u)Time_Offset);
            }
            if (Speed_TimeStampsZ[0].First.FramePos==Speed_FrameCount)
                Speed_TimeStampsZ[0].First.TimeCode=Speed_TimeCodeZ_Current;
        }
        else
            Errors_Stats_Line+=_T("XX:XX:XX:XX");
        Errors_Stats_Line+=_T('\t');

        //Order coherency
        bool TimeCode_Disrupted=false;
        if (Speed_TimeCode_Current.IsValid && Speed_TimeCode_Last.IsValid
         && Speed_TimeCode_Current.Frames ==Speed_TimeCode_Last.Frames
         && Speed_TimeCode_Current.Seconds==Speed_TimeCode_Last.Seconds
         && Speed_TimeCode_Current.Minutes==Speed_TimeCode_Last.Minutes
         && Speed_TimeCode_Current.Hours  ==Speed_TimeCode_Last.Hours)
        {
            Errors_Stats_Line+=_T('R');
            if (Speed_TimeCode_Current.Hours
             || Speed_TimeCode_Current.Seconds
             || Speed_TimeCode_Current.Minutes
             || Speed_TimeCode_Current.Hours)
                Errors_AreDetected=true;
        }
        else if (Speed_TimeCode_Current.IsValid && Speed_TimeCode_Current_Theory.IsValid
              && (   Speed_TimeCode_Current.Frames !=Speed_TimeCode_Current_Theory.Frames
                  || Speed_TimeCode_Current.Seconds!=Speed_TimeCode_Current_Theory.Seconds
                  || Speed_TimeCode_Current.Minutes!=Speed_TimeCode_Current_Theory.Minutes
                  || Speed_TimeCode_Current.Hours  !=Speed_TimeCode_Current_Theory.Hours))
        {
            size_t Speed_TimeCodeZ_Pos=Speed_TimeCodeZ.size();
            Speed_TimeCodeZ.resize(Speed_TimeCodeZ_Pos+1);
            Speed_TimeCodeZ[Speed_TimeCodeZ_Pos].First.FramePos=Speed_FrameCount-1;
            Speed_TimeCodeZ[Speed_TimeCodeZ_Pos].First.TimeCode=Speed_TimeCodeZ_Current;
            Speed_TimeCodeZ[Speed_TimeCodeZ_Pos-1].Last.FramePos=Speed_FrameCount-1;
            Speed_TimeCodeZ[Speed_TimeCodeZ_Pos-1].Last.TimeCode=Speed_TimeCodeZ_Last;

            Errors_Stats_Line+=_T('N');
            Speed_TimeCode_Current_Theory=Speed_TimeCode_Current;
            TimeCode_Disrupted=true;
            Errors_AreDetected=true;
        }
        else
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');

        //RecDate/RecTime
        if (Speed_RecDate_Current.IsValid)
        {
            Speed_RecDateZ_Last=Speed_RecDateZ_Current;
            Speed_RecDateZ_Current.clear();
            Speed_RecDateZ_Current.reserve(10);
            Speed_RecDateZ_Current+=Speed_RecDate_Current.Years<75?_T("20"):_T("19");
            Speed_RecDateZ_Current+=_T('0')+Speed_RecDate_Current.Years  /10;
            Speed_RecDateZ_Current+=_T('0')+Speed_RecDate_Current.Years  %10;
            Speed_RecDateZ_Current+=_T('-');
            Speed_RecDateZ_Current+=_T('0')+Speed_RecDate_Current.Months /10;
            Speed_RecDateZ_Current+=_T('0')+Speed_RecDate_Current.Months %10;
            Speed_RecDateZ_Current+=_T('-');
            Speed_RecDateZ_Current+=_T('0')+Speed_RecDate_Current.Days   /10;
            Speed_RecDateZ_Current+=_T('0')+Speed_RecDate_Current.Days   %10;
            Errors_Stats_Line+=Speed_RecDateZ_Current;
            if (Speed_RecZ.empty())
            {
                Speed_RecZ.resize(1);
                Speed_RecZ[0].First.FramePos=Speed_FrameCount;
                Speed_RecZ[0].First.Date=Speed_RecDateZ_Current;
            }
            if (Speed_TimeStampsZ.empty())
            {
                Speed_TimeStampsZ.resize(1);
                Speed_TimeStampsZ[0].First.FramePos=Speed_FrameCount;
                float64 Time_Offset=(Speed_FrameCount-1)*1000/FrameRate;
                Speed_TimeStampsZ[0].First.Time+=Ztring().Duration_From_Milliseconds((int64u)Time_Offset);
            }
            if (Speed_TimeStampsZ[0].First.FramePos==Speed_FrameCount)
                Speed_TimeStampsZ[0].First.Date=Speed_RecDateZ_Current;
        }
        else
            Errors_Stats_Line+=_T("XXXX-XX-XX");
        Errors_Stats_Line+=_T(" ");
        if (Speed_RecTime_Current.IsValid)
        {
            Speed_RecTimeZ_Last=Speed_RecTimeZ_Current;
            Speed_RecTimeZ_Current.clear();
            Speed_RecTimeZ_Current.reserve(12);
            Speed_RecTimeZ_Current+=_T('0')+Speed_RecTime_Current.Hours  /10;
            Speed_RecTimeZ_Current+=_T('0')+Speed_RecTime_Current.Hours  %10;
            Speed_RecTimeZ_Current+=_T(':');
            Speed_RecTimeZ_Current+=_T('0')+Speed_RecTime_Current.Minutes/10;
            Speed_RecTimeZ_Current+=_T('0')+Speed_RecTime_Current.Minutes%10;
            Speed_RecTimeZ_Current+=_T(':');
            Speed_RecTimeZ_Current+=_T('0')+Speed_RecTime_Current.Seconds/10;
            Speed_RecTimeZ_Current+=_T('0')+Speed_RecTime_Current.Seconds%10;
            if (Speed_RecTime_Current.Frames!=45)
            {
                int32u Milliseconds;
                if (System_IsValid)
                    Milliseconds=Speed_RecTime_Current.Frames*(System?40:33);
                else if (DSF_IsValid)
                    Milliseconds=Speed_RecTime_Current.Frames*(DSF?40:33);
                else
                    Milliseconds=Speed_RecTime_Current.Frames*33;
                Speed_RecTimeZ_Current+=_T('.');
                Speed_RecTimeZ_Current+=_T('0')+(Char)(Milliseconds/100);
                Speed_RecTimeZ_Current+=_T('0')+(Char)((Milliseconds%100)/10);
                Speed_RecTimeZ_Current+=_T('0')+(Char)(Milliseconds%10);
            }
            else
                Speed_RecTimeZ_Current+=_T("    ");
            Errors_Stats_Line+=Speed_RecTimeZ_Current;
            if (Speed_RecZ.empty() || Speed_RecZ[0].First.FramePos==Speed_FrameCount) //Empty or the same frame as RecDate
            {
                if (Speed_RecZ.empty())
                    Speed_RecZ.resize(1);
                Speed_RecZ[0].First.FramePos=Speed_FrameCount;
                Speed_RecZ[0].First.Time=Speed_RecTimeZ_Current;
            }
            if (Speed_TimeStampsZ.empty())
            {
                Speed_TimeStampsZ.resize(1);
                Speed_TimeStampsZ[0].First.FramePos=Speed_FrameCount;
                float64 Time_Offset=(Speed_FrameCount-1)*1000/FrameRate;
                Speed_TimeStampsZ[0].First.Time+=Ztring().Duration_From_Milliseconds((int64u)Time_Offset);
            }
            if (Speed_TimeStampsZ[0].First.FramePos==Speed_FrameCount) //Empty or the same frame as RecDate or the same frame as TimeCode
                Speed_TimeStampsZ[0].First.Time=Speed_RecTimeZ_Current;
        }
        else
            Errors_Stats_Line+=_T("XX:XX:XX.XXX");
        Errors_Stats_Line+=_T('\t');

        //RecDate/RecTime coherency, Rec start/end
        bool RecTime_Disrupted=false;
        if (/*(!REC_IsValid || !REC_ST || !REC_END) &&*/
            Speed_RecTime_Current.IsValid && Speed_RecTime_Current_Theory.IsValid
         && !(   Speed_RecTime_Current.Seconds==Speed_RecTime_Current_Theory.Seconds
              && Speed_RecTime_Current.Minutes==Speed_RecTime_Current_Theory.Minutes
              && Speed_RecTime_Current.Hours  ==Speed_RecTime_Current_Theory.Hours)
         && !(   Speed_RecTime_Current.Seconds==Speed_RecTime_Current_Theory2.Seconds
              && Speed_RecTime_Current.Minutes==Speed_RecTime_Current_Theory2.Minutes
              && Speed_RecTime_Current.Hours  ==Speed_RecTime_Current_Theory2.Hours))
        {
            size_t Speed_RecZ_Pos=Speed_RecZ.size();
            Speed_RecZ.resize(Speed_RecZ_Pos+1);
            Speed_RecZ[Speed_RecZ_Pos].First.FramePos=Speed_FrameCount-1;
            Speed_RecZ[Speed_RecZ_Pos].First.Date=Speed_RecDateZ_Current;
            Speed_RecZ[Speed_RecZ_Pos].First.Time=Speed_RecTimeZ_Current;
            Speed_RecZ[Speed_RecZ_Pos-1].Last.FramePos=Speed_FrameCount-1;
            Speed_RecZ[Speed_RecZ_Pos-1].Last.Date=Speed_RecDateZ_Last;
            Speed_RecZ[Speed_RecZ_Pos-1].Last.Time=Speed_RecTimeZ_Last;

            Errors_Stats_Line+=_T('N');
            if (!REC_IsValid || REC_ST)
            {
                RecTime_Disrupted=true;
                Errors_AreDetected=true; //If there is a start, this is not an error
            }
        }
        else
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');

        //Arb
        if (Arb.IsValid)
            Errors_Stats_Line+=Ztring::ToZtring(Arb.Value, 16);
        else
            Errors_Stats_Line+=_T('X');
        Errors_Stats_Line+=_T('\t');

        //Start
        if (REC_IsValid && !REC_ST)
        {
            Errors_Stats_Line+=_T('S');
            Infos_AreDetected=true;
        }
        else
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');

        //End
        if (REC_IsValid && !REC_END)
        {
            Errors_Stats_Line+=_T('E');
            Infos_AreDetected=true;
        }
        else
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');

        //TimeStamp (RecDate/RecTime and TimeCode together)
        if (TimeCode_Disrupted || RecTime_Disrupted)
        {
            size_t Speed_TimeStampsZ_Pos=Speed_TimeStampsZ.size();
            Speed_TimeStampsZ.resize(Speed_TimeStampsZ_Pos+1);
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].First.FramePos=Speed_FrameCount-1;
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].First.TimeCode=Speed_TimeCodeZ_Current;
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].First.Date=Speed_RecDateZ_Current;
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].First.Time=Speed_RecTimeZ_Current;
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos-1].Last.FramePos=Speed_FrameCount-1;
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos-1].Last.TimeCode=Speed_TimeCodeZ_Last;
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos-1].Last.Date=Speed_RecDateZ_Last;
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos-1].Last.Time=Speed_RecTimeZ_Last;
        }

        //Channels
        for (size_t Channel=0; Channel<8; Channel++)
        {
            if (!audio_source_IsPresent.empty() && audio_source_IsPresent[Channel])
            {
                if (Channel<4 && (!Audio_Invalids.empty() || !Audio_Errors.empty()))
                {
                    size_t Audio_Errors_Count=0;
                    size_t Pos_Begin=(Channel%2)*(QU_System?6:5);
                    size_t Pos_End=(Channel%2+1)*(QU_System?6:5);
                    if (Channel>=2 && !QU_FSC
                     || Channel< 2 &&  QU_FSC)
                        Pos_End=Pos_Begin; //Not here
                    if (!Audio_Invalids.empty())
                        for (size_t Pos=Pos_Begin; Pos<Pos_End; Pos++)
                            if (Audio_Invalids[Channel][Pos])
                                Audio_Errors_Count+=Audio_Invalids[Channel][Pos];
                    if (!Audio_Errors.empty())
                        for (size_t Pos=Pos_Begin; Pos<Pos_End; Pos++)
                            if (Audio_Errors[Pos])
                                Audio_Errors_Count+=Audio_Errors[Pos];
                    if (Audio_Errors_Count>=(size_t)((QU_System?6:5)*9))
                        audio_source_IsPresent[Channel]=false;
                    else
                        CH_IsPresent[Channel]=true;
                }
            }
        }


        //Error 1: Video errors
        Ztring Errors_Stats_Line_Details;
        if (!Video_STA_Errors.empty())
        {
            Errors_Stats_Line+=_T('1');

            size_t Video_STA_Errors_Count=0;
            Ztring Video_STA_Errors_Details;
            for (size_t Pos=0; Pos<16; Pos++)
            {
                if (Video_STA_Errors[Pos])
                {
                    Video_STA_Errors_Count+=Video_STA_Errors[Pos];
                    Ztring Video_STA_Errors_Count_Padded=Ztring::ToZtring(Video_STA_Errors[Pos]);
                    if (Video_STA_Errors_Count_Padded.size()<8)
                        Video_STA_Errors_Count_Padded.insert(0, 8-Video_STA_Errors_Count_Padded.size(), _T(' '));
                    Video_STA_Errors_Details+=Video_STA_Errors_Count_Padded;
                    Video_STA_Errors_Details+=_T(" \"");
                    Video_STA_Errors_Details+=Ztring::ToZtring(Pos, 16);
                    Video_STA_Errors_Details+=_T("\" errors, ");
                    if (Video_STA_Errors_Total.empty())
                        Video_STA_Errors_Total.resize(16);
                    Video_STA_Errors_Total[Pos]+=Video_STA_Errors[Pos];
                }
            }
            if (Video_STA_Errors_Details.size()>2)
            {
                Ztring Video_STA_Errors_Count_Padded=Ztring::ToZtring(Video_STA_Errors_Count);
                if (Video_STA_Errors_Count_Padded.size()<8)
                    Video_STA_Errors_Count_Padded.insert(0, 8-Video_STA_Errors_Count_Padded.size(), _T(' '));
                Errors_Stats_Line_Details+=Video_STA_Errors_Count_Padded+_T(" STA errors");
                Video_STA_Errors_Details.resize(Video_STA_Errors_Details.size()-2);
                Errors_Stats_Line_Details+=_T(" (")+Video_STA_Errors_Details+_T(")");
                Speed_FrameCount_Video_STA_Errors++;
                Errors_AreDetected=true;
            }
        }
        else
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');
        Errors_Stats_Line_Details+=_T('\t');

        //Error 2: Audio errors
        if (QU!=(int8u)-1 && (!Audio_Invalids.empty() || !Audio_Errors.empty()))
        {
            if (Audio_Errors.empty())
                Audio_Errors.resize(16);
            bool ErrorsAreAlreadyDetected=false;
            for (size_t Channel=0; Channel<4; Channel++)
            {
                size_t Audio_Errors_Count=0;
                Ztring Audio_Errors_Details;
                size_t Pos_Begin=(Channel%2)*(QU_System?6:5);
                size_t Pos_End=(Channel%2+1)*(QU_System?6:5);
                if (Channel>=2 && !QU_FSC
                 || Channel< 2 &&  QU_FSC
                 || !CH_IsPresent[Channel])
                    Pos_End=Pos_Begin; //Not here
                for (size_t Pos=Pos_Begin; Pos<Pos_End; Pos++)
                {
                    if (Audio_Errors[Pos])
                    {
                        Audio_Errors_Count+=Audio_Errors[Pos];
                        Ztring Audio_Errors_Count_Padded=Ztring::ToZtring(Audio_Errors[Pos]);
                        if (Audio_Errors_Count_Padded.size()<2)
                            Audio_Errors_Count_Padded.insert(0, 2-Audio_Errors_Count_Padded.size(), _T(' '));
                        Audio_Errors_Details+=Audio_Errors_Count_Padded;
                        Audio_Errors_Details+=_T(" Dseq=");
                        Audio_Errors_Details+=Ztring::ToZtring(Pos, 16);
                        Audio_Errors_Details+=_T(", ");
                        if (Audio_Errors_Total.empty())
                        {
                            Audio_Errors_Total.resize(8);
                            for (size_t Pos=0; Pos<8; Pos++)
                                Audio_Errors_Total[Pos].resize(16);
                        }
                        Audio_Errors_Total[Channel][Pos]+=Audio_Errors[Pos];
                    }
                }
                if (Audio_Errors_Count)
                {
                    if (!ErrorsAreAlreadyDetected)
                        Errors_Stats_Line+=_T('2');

                    Ztring Audio_Errors_Count_Padded=Ztring::ToZtring(Audio_Errors_Count);
                    if (Audio_Errors_Count_Padded.size()<2)
                        Audio_Errors_Count_Padded.insert(0, 2-Audio_Errors_Count_Padded.size(), _T(' '));
                    if (ErrorsAreAlreadyDetected)
                        Errors_Stats_Line_Details+=_T(", ");
                    if (Audio_Errors_Count<(size_t)((QU_System?6:5)*9))
                    {
                        Errors_Stats_Line_Details+=_T("CH")+Ztring::ToZtring(Channel+1)+_T(": ")+Audio_Errors_Count_Padded+_T(" audio errors");
                        Audio_Errors_Details.resize(Audio_Errors_Details.size()-2);
                        Errors_Stats_Line_Details+=_T(" (")+Audio_Errors_Details+_T(")");
                    }
                    else
                        Errors_Stats_Line_Details+=_T("CH")+Ztring::ToZtring(Channel+1)+_T(": no valid DIF");

                    Speed_FrameCount_Audio_Errors[Channel]++;
                    ErrorsAreAlreadyDetected=true;
                    Errors_AreDetected=true;
                }
            }
            if (!ErrorsAreAlreadyDetected)
                Errors_Stats_Line+=_T(' ');
        }
        else
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');
        Errors_Stats_Line_Details+=_T('\t');

        //Error 3: Timecode incoherency
        if (Speed_TimeCode_Current.MultipleValues)
        {
            Errors_Stats_Line+=_T('3');
            Errors_Stats_Line_Details+=_T("(Timecode incoherency, first detected value is used)");
            Speed_FrameCount_Timecode_Incoherency++;
            Errors_AreDetected=true;
        }
        else
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');
        Errors_Stats_Line_Details+=_T('\t');

        //Error 4: DIF order incoherency
        if (Speed_Contains_NULL)
        {
            Errors_Stats_Line+=_T('4');
            Errors_Stats_Line_Details+=_T("(DIF incoherency, ")+Ztring::ToZtring(Speed_Contains_NULL)+_T(" NULL DIFs)");
            Speed_FrameCount_Contains_NULL++;
            Errors_AreDetected=true;
        }
        else
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');
        Errors_Stats_Line_Details+=_T('\t');

        //Error 5: Arb incoherency
        if (Arb.MultipleValues)
        {
            Errors_Stats_Line+=_T('5');
            Errors_Stats_Line_Details+=_T("(Arb incoherency, first detected value is used)");
            Speed_FrameCount_Arb_Incoherency++;
            Errors_AreDetected=true;
        }
        else
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');
        Errors_Stats_Line_Details+=_T('\t');

        //Error 6:
        if (Mpeg4_stts && Mpeg4_stts_Pos<Mpeg4_stts->size() && Speed_FrameCount-1>=Mpeg4_stts->at(Mpeg4_stts_Pos).Pos_Begin && Speed_FrameCount-1<Mpeg4_stts->at(Mpeg4_stts_Pos).Pos_End)
        {
            Errors_Stats_Line+=_T('6');
            Errors_Stats_Line_Details+=_T("stts flucuation");
            Speed_FrameCount_Stts_Fluctuation++;
            Errors_AreDetected=true;
        }
        else
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');
        Errors_Stats_Line_Details+=_T('\t');

        //Error 7:
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');
        Errors_Stats_Line_Details+=_T('\t');

        //Error 8:
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');
        Errors_Stats_Line_Details+=_T('\t');

        //Error 9:
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');
        Errors_Stats_Line_Details+=_T('\t');

        //Error 0:
            Errors_Stats_Line+=_T(' ');
        Errors_Stats_Line+=_T('\t');
        Errors_Stats_Line_Details+=_T('\t');

        //Filling the main text if needed
        if (Speed_FrameCount==1
         || Status[IsFinished]
         || Errors_AreDetected)
        {
            Errors_Stats_03+=Errors_Stats_Line;
            Errors_Stats_03+=Errors_Stats_Line_Details;
            Errors_Stats_03+=_T("&");
        }
        if (Speed_FrameCount==1
         || Status[IsFinished]
         || Errors_AreDetected
         || Infos_AreDetected)
        {
            Errors_Stats_05+=Errors_Stats_Line;
            Errors_Stats_05+=Errors_Stats_Line_Details;
            Errors_Stats_05+=_T("&");
        }
        {
            Errors_Stats_10+=Errors_Stats_Line;
            Errors_Stats_10+=Errors_Stats_Line_Details;
            Errors_Stats_10+=_T("&");
        }
    }

    //Speed_TimeCode_Current
    if (!Speed_TimeCode_Current_Theory.IsValid)
        Speed_TimeCode_Current_Theory=Speed_TimeCode_Current;
    if (Speed_TimeCode_Current_Theory.IsValid)
    {
        int8u Frames_Max;
        if (System_IsValid)
            Frames_Max=System?25:30;
        else if (DSF_IsValid)
            Frames_Max=DSF?25:30;
        else
            Frames_Max=30;

        Speed_TimeCode_Current_Theory.Frames++;
        if (Speed_TimeCode_Current_Theory.Frames>=Frames_Max)
        {
            Speed_TimeCode_Current_Theory.Seconds++;
            Speed_TimeCode_Current_Theory.Frames=0;
            if (Speed_TimeCode_Current_Theory.Seconds>=60)
            {
                Speed_TimeCode_Current_Theory.Seconds=0;
                Speed_TimeCode_Current_Theory.Minutes++;

                if (Speed_TimeCode_Current_Theory.DropFrame && Speed_TimeCode_Current_Theory.Minutes%10)
                    Speed_TimeCode_Current_Theory.Frames=2; //frames 0 and 1 are dropped for every minutes except 00 10 20 30 40 50

                if (Speed_TimeCode_Current_Theory.Minutes>=60)
                {
                    Speed_TimeCode_Current_Theory.Minutes=0;
                    Speed_TimeCode_Current_Theory.Hours++;
                    if (Speed_TimeCode_Current_Theory.Hours>=24)
                    {
                        Speed_TimeCode_Current_Theory.Hours=0;
                    }
                }
            }
        }
    }

    //Speed_RecTime_Current_Theory
    Speed_RecTime_Current_Theory=Speed_RecTime_Current;
    Speed_RecTime_Current_Theory2=Speed_RecTime_Current; //Don't change it
    if (Speed_RecTime_Current_Theory.IsValid)
    {
        Speed_RecTime_Current_Theory.Seconds++;
        if (Speed_RecTime_Current_Theory.Seconds>=60)
        {
            Speed_RecTime_Current_Theory.Seconds=0;
            Speed_RecTime_Current_Theory.Minutes++;
            if (Speed_RecTime_Current_Theory.Seconds>=60)
            {
                Speed_RecTime_Current_Theory.Minutes=0;
                Speed_RecTime_Current_Theory.Hours++;
                if (Speed_RecTime_Current_Theory.Hours>=24)
                {
                    Speed_RecTime_Current_Theory.Hours=0;
                }
            }
        }
    }

    Speed_TimeCode_Last=Speed_TimeCode_Current;
    Speed_TimeCode_Current.Clear();
    Speed_RecDate_Current.IsValid=false;
    Speed_RecDate_Current.MultipleValues=false;
    Speed_RecTime_Current.IsValid=false;
    Speed_RecTime_Current.MultipleValues=false;
    Arb.IsValid=false;
    Arb.MultipleValues=false;
    Speed_FrameCount++;
    REC_IsValid=false;
    Speed_Contains_NULL=0;
    Frame_AtLeast1DIF=true;
    if (Buffer_Offset+2>=Buffer_Size
     || Buffer[Buffer_Offset  ]==0x00
     && Buffer[Buffer_Offset+1]==0x00
     && Buffer[Buffer_Offset+2]==0x00)
        Frame_AtLeast1DIF=false;
    Video_STA_Errors.clear();
    Audio_Errors.clear();
    Audio_Invalids.clear();
}

void File_DvDif::Errors_Stats_Update_Finnish()
{
    if (!Analyze_Activated)
    {
        if (Config->File_DvDif_Analysis_Get())
            Analyze_Activated=true;
        else
            return;    
    }       

    //Preparing next frame
    Speed_FrameCount--;
    Ztring Errors_Stats_End_03;
    Ztring Errors_Stats_End_05;
    Ztring Errors_Stats_End_Lines;

    //Frames
    if (Speed_FrameCount)
        Errors_Stats_End_Lines+=_T("Frame Count: ")+Ztring::ToZtring(Speed_FrameCount)+_T('&');

    //One block
    if (!Errors_Stats_End_Lines.empty())
    {
        Errors_Stats_End_05+=Errors_Stats_End_Lines;
        Errors_Stats_End_05+=_T('&');
        Errors_Stats_End_Lines.clear();
    }

    //Error 1: Video error concealment
    if (Speed_FrameCount_Video_STA_Errors)
        Errors_Stats_End_Lines+=_T("Frame count with video error concealment: ")+Ztring::ToZtring(Speed_FrameCount_Video_STA_Errors)+_T(" frames &");
    if (!Video_STA_Errors_Total.empty())
    {
        Ztring Errors_Details;
        size_t Errors_Count=0;
        for (size_t Pos=0; Pos<16; Pos++)
        {
            if (Video_STA_Errors_Total[Pos])
            {
                Errors_Count+=Video_STA_Errors_Total[Pos];
                Ztring Errors_Count_Padded=Ztring::ToZtring(Video_STA_Errors_Total[Pos]);
                if (Errors_Count_Padded.size()<8)
                    Errors_Count_Padded.insert(0, 8-Errors_Count_Padded.size(), _T(' '));
                Errors_Details+=Errors_Count_Padded;
                Errors_Details+=_T(" \"");
                Errors_Details+=Ztring::ToZtring(Pos, 16);
                Errors_Details+=_T("\" errors, ");
            }
        }
        if (Errors_Details.size()>2)
        {
            Errors_Stats_End_Lines+=_T("Total video error concealment: ");
            Ztring Errors_Count_Padded=Ztring::ToZtring(Errors_Count);
            if (Errors_Count_Padded.size()<8)
                Errors_Count_Padded.insert(0, 8-Errors_Count_Padded.size(), _T(' '));
            Errors_Stats_End_Lines+=_T(" ")+Errors_Count_Padded+_T(" errors");
            Errors_Details.resize(Errors_Details.size()-2);
            Errors_Stats_End_Lines+=_T(" (")+Errors_Details+_T(")")+_T('&');
        }
    }

    //Error 2: Audio error code
    if (!Audio_Errors_Total.empty())
    {
        for (size_t Channel=0; Channel<8; Channel++)
        {
            if (Speed_FrameCount_Audio_Errors[Channel])
                Errors_Stats_End_Lines+=_T("Frame count with CH")+Ztring::ToZtring(Channel+1)+_T(" audio error code: ")+Ztring::ToZtring(Speed_FrameCount_Audio_Errors[Channel])+_T(" frames &");

            Ztring Errors_Details;
            size_t Errors_Count=0;
            for (size_t Pos=0; Pos<16; Pos++)
            {
                if (Audio_Errors_Total[Channel][Pos])
                {
                    Errors_Count+=Audio_Errors_Total[Channel][Pos];
                    Ztring Errors_Count_Padded=Ztring::ToZtring(Audio_Errors_Total[Channel][Pos]);
                    if (Errors_Count_Padded.size()<8)
                        Errors_Count_Padded.insert(0, 8-Errors_Count_Padded.size(), _T(' '));
                    Errors_Details+=Errors_Count_Padded;
                    Errors_Details+=_T(" Dseq=");
                    Errors_Details+=Ztring::ToZtring(Pos, 16);
                    Errors_Details+=_T(", ");
                }
            }
            if (Errors_Details.size()>2)
            {
                Errors_Stats_End_Lines+=_T("Total audio error code for CH")+Ztring::ToZtring(Channel+1)+_T(": ");
                Ztring Errors_Count_Padded=Ztring::ToZtring(Errors_Count);
                if (Errors_Count_Padded.size()<8)
                    Errors_Count_Padded.insert(0, 8-Errors_Count_Padded.size(), _T(' '));
                Errors_Stats_End_Lines+=_T(" ")+Errors_Count_Padded+_T(" errors");
                Errors_Details.resize(Errors_Details.size()-2);
                Errors_Stats_End_Lines+=_T(" (")+Errors_Details+_T(")")+_T('&');
            }
        }
    }

    //Error 3: Timecode incoherency
    if (Speed_FrameCount_Timecode_Incoherency)
        Errors_Stats_End_Lines+=_T("Frame count with timecode incoherency: ")+Ztring::ToZtring(Speed_FrameCount_Timecode_Incoherency)+_T(" frames &");

    //Error 4: DIF incohereny
    if (Speed_FrameCount_Contains_NULL)
        Errors_Stats_End_Lines+=_T("Frame count with DIF incoherency: ")+Ztring::ToZtring(Speed_FrameCount_Contains_NULL)+_T(" frames &");

    //Error 5: Arbitrary bit incoherency
    if (Speed_FrameCount_Arb_Incoherency)
        Errors_Stats_End_Lines+=_T("Frame count with arbitrary bit incoherency: ")+Ztring::ToZtring(Speed_FrameCount_Arb_Incoherency)+_T(" frames &");

    //Error 6: Stts fluctuation
    if (Speed_FrameCount_Stts_Fluctuation)
        Errors_Stats_End_Lines+=_T("Frame count with stts fluctuation: ")+Ztring::ToZtring(Speed_FrameCount_Stts_Fluctuation)+_T(" frames &");

    //One block
    if (!Errors_Stats_End_Lines.empty())
    {
        Errors_Stats_End_03+=Errors_Stats_End_Lines;
        Errors_Stats_End_03+=_T('&');
        Errors_Stats_End_05+=Errors_Stats_End_Lines;
        Errors_Stats_End_05+=_T('&');
        Errors_Stats_End_Lines.clear();
    }

    /*
    //RecDate/RecTime
    if (!Speed_RecDateZ_Current.empty() && !Speed_RecTimeZ_Current.empty()) //Date and Time must be both available
    {
        size_t Speed_RecZ_Pos=Speed_RecZ.size();
        if (Speed_RecZ_Pos)
        {
            Speed_RecZ_Pos--;
            Speed_RecZ[Speed_RecZ_Pos].Last.FramePos=Speed_FrameCount;
            Speed_RecZ[Speed_RecZ_Pos].Last.Date=Speed_RecDateZ_Current;
            Speed_RecZ[Speed_RecZ_Pos].Last.Time=Speed_RecTimeZ_Current;
            if (Speed_RecZ[Speed_RecZ_Pos].Last.FramePos-(Speed_RecZ_Pos?Speed_RecZ[Speed_RecZ_Pos-1].Last.FramePos:0)==1)
            {
                //Only one frame, the "Last" part is not filled
                Speed_RecZ[Speed_RecZ_Pos].Last.Date=Speed_RecZ[Speed_RecZ_Pos].First.Date;
                Speed_RecZ[Speed_RecZ_Pos].Last.Time=Speed_RecZ[Speed_RecZ_Pos].First.Time;
            }

            for (size_t Pos=0; Pos<Speed_RecZ.size(); Pos++)
            {
                Errors_Stats_End_Lines+=_T("Date Covered: ");
                Errors_Stats_End_Lines+=Speed_RecZ[Pos].First.Date.empty()?Ztring(_T("XXXX-XX-XX")):Speed_RecZ[Pos].First.Date;
                Errors_Stats_End_Lines+=_T(' ');
                Errors_Stats_End_Lines+=Speed_RecZ[Pos].First.Time.empty()?Ztring(_T("XX:XX:XX:XX")):Speed_RecZ[Pos].First.Time;

                Errors_Stats_End_Lines+=_T(" - ");

                Errors_Stats_End_Lines+=Speed_RecZ[Pos].Last.Date.empty()?Ztring(_T("XXXX-XX-XX")):Speed_RecZ[Pos].Last.Date;
                Errors_Stats_End_Lines+=_T(' ');
                Errors_Stats_End_Lines+=Speed_RecZ[Pos].Last.Time.empty()?Ztring(_T("XX:XX:XX:XX")):Speed_RecZ[Pos].Last.Time;

                Ztring Start_Padded=Ztring::ToZtring((Pos?Speed_RecZ[Pos-1].Last.FramePos+1:1));
                if (Start_Padded.size()<8)
                    Start_Padded.insert(0, 8-Start_Padded.size(), _T(' '));
                Errors_Stats_End_Lines+=_T(" (start at ")+Start_Padded;

                Ztring Frames_Padded=Ztring::ToZtring(Speed_RecZ[Pos].Last.FramePos-(Pos?Speed_RecZ[Pos-1].Last.FramePos:0));
                if (Frames_Padded.size()<8)
                    Frames_Padded.insert(0, 8-Frames_Padded.size(), _T(' '));
                Errors_Stats_End_Lines+=_T(", ")+Frames_Padded+_T(" frames)");

                Errors_Stats_End_Lines+=_T('&');
            }
        }
    }

    //One block
    if (!Errors_Stats_End_Lines.empty())
    {
        Errors_Stats_End_05+=Errors_Stats_End_Lines;
        Errors_Stats_End_05+=_T('&');
        Errors_Stats_End_Lines.clear();
    }

    //TimeCode
    if (!Speed_TimeCodeZ_Current.empty())
    {
        size_t Speed_TimeCodeZ_Pos=Speed_TimeCodeZ.size();
        if (Speed_TimeCodeZ_Pos)
        {
            Speed_TimeCodeZ_Pos--;
            Speed_TimeCodeZ[Speed_TimeCodeZ_Pos].Last.FramePos=Speed_FrameCount;
            Speed_TimeCodeZ[Speed_TimeCodeZ_Pos].Last.TimeCode=Speed_TimeCodeZ_Current;
            if (Speed_TimeCodeZ[Speed_TimeCodeZ_Pos].Last.FramePos-(Speed_TimeCodeZ_Pos?Speed_TimeCodeZ[Speed_TimeCodeZ_Pos-1].Last.FramePos:0)==1)
            {
                //Only one frame, the "Last" part is not filled
                Speed_TimeCodeZ[Speed_TimeCodeZ_Pos].Last.TimeCode=Speed_TimeCodeZ[Speed_TimeCodeZ_Pos].First.TimeCode;
            }

            for (size_t Pos=0; Pos<Speed_TimeCodeZ.size(); Pos++)
            {
                Errors_Stats_End_Lines+=_T("Timecode Covered: ");
                Errors_Stats_End_Lines+=Speed_TimeCodeZ[Pos].First.TimeCode;

                Errors_Stats_End_Lines+=_T(" - ");

                Errors_Stats_End_Lines+=Speed_TimeCodeZ[Pos].Last.TimeCode;

                Ztring Start_Padded=Ztring::ToZtring((Pos?Speed_TimeCodeZ[Pos-1].Last.FramePos+1:1));
                if (Start_Padded.size()<8)
                    Start_Padded.insert(0, 8-Start_Padded.size(), _T(' '));
                Errors_Stats_End_Lines+=_T(" (start at ")+Start_Padded;

                Ztring Frames_Padded=Ztring::ToZtring(Speed_TimeCodeZ[Pos].Last.FramePos-(Pos?Speed_TimeCodeZ[Pos-1].Last.FramePos:0));
                if (Frames_Padded.size()<8)
                    Frames_Padded.insert(0, 8-Frames_Padded.size(), _T(' '));
                Errors_Stats_End_Lines+=_T(", ")+Frames_Padded+_T(" frames)");

                Errors_Stats_End_Lines+=_T('&');
            }
        }
    }

    //One block
    if (!Errors_Stats_End_Lines.empty())
    {
        Errors_Stats_End_05+=Errors_Stats_End_Lines;
        Errors_Stats_End_05+=_T('&');
        Errors_Stats_End_Lines.clear();
    }
    */

    //TimeStamps (RecDate/RecTime and TimeCode)
    if (!Speed_RecDateZ_Current.empty() || !Speed_RecTimeZ_Current.empty()) //Date and Time must be both available
    {
        size_t Speed_TimeStampsZ_Pos=Speed_TimeStampsZ.size();
        if (Speed_TimeStampsZ_Pos)
        {
            Speed_TimeStampsZ_Pos--;
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].Last.FramePos=Speed_FrameCount;
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].Last.FramePos=Speed_FrameCount;
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].Last.TimeCode=Speed_TimeCodeZ_Current;
            if (Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].Last.FramePos-(Speed_TimeStampsZ_Pos?Speed_TimeStampsZ[Speed_TimeStampsZ_Pos-1].Last.FramePos:0)==1) //Only one frame, the "Last" part is not filled
                Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].Last.TimeCode=Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].First.TimeCode; 
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].Last.Date=Speed_RecDateZ_Current;
            Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].Last.Time=Speed_RecTimeZ_Current;
            if (Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].Last.FramePos-(Speed_TimeStampsZ_Pos?Speed_TimeStampsZ[Speed_TimeStampsZ_Pos-1].Last.FramePos:0)==1)
            {
                //Only one frame, the "Last" part is not filled
                Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].Last.Date=Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].First.Date;
                Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].Last.Time=Speed_TimeStampsZ[Speed_TimeStampsZ_Pos].First.Time;
            }

            //Framerate computing
            float64 FrameRate=29.970;
            if (System_IsValid)
                FrameRate=System?25.000:29.970;
            else if (DSF_IsValid)
                FrameRate=DSF?25.000:29.970;
            else
                FrameRate=29.970;
            if (FrameRate==29.970 && Speed_TimeCode_Current.IsValid && !Speed_TimeCode_Current.DropFrame)
                FrameRate=30.000;

            Errors_Stats_End_Lines+=_T("Abs. Time    \tTimeCode_range           \tRecorded date/time_range                         \tFrame range&");
            for (size_t Pos=0; Pos<Speed_TimeStampsZ.size(); Pos++)
            {
                //Time
                float64 Time_Offset=(Pos?Speed_TimeStampsZ[Pos-1].Last.FramePos:0)*1000/FrameRate;
                Errors_Stats_End_Lines+=Ztring().Duration_From_Milliseconds((int64u)Time_Offset);

                Errors_Stats_End_Lines+=_T("\t");

                //TimeCode_range
                Errors_Stats_End_Lines+=Speed_TimeStampsZ[Pos].First.TimeCode.empty()?Ztring(_T("XX:XX:XX:XX")):Speed_TimeStampsZ[Pos].First.TimeCode;

                Errors_Stats_End_Lines+=_T(" - ");

                Errors_Stats_End_Lines+=Speed_TimeStampsZ[Pos].Last.TimeCode.empty()?Ztring(_T("XX:XX:XX:XX")):Speed_TimeStampsZ[Pos].Last.TimeCode;

                Errors_Stats_End_Lines+=_T("\t");

                //Recorded date/time_range
                Errors_Stats_End_Lines+=Speed_TimeStampsZ[Pos].First.Date.empty()?Ztring(_T("XXXX-XX-XX")):Speed_TimeStampsZ[Pos].First.Date;
                Errors_Stats_End_Lines+=_T(' ');
                Errors_Stats_End_Lines+=Speed_TimeStampsZ[Pos].First.Time.empty()?Ztring(_T("XX:XX:XX:XX")):Speed_TimeStampsZ[Pos].First.Time;

                Errors_Stats_End_Lines+=_T(" - ");

                Errors_Stats_End_Lines+=Speed_TimeStampsZ[Pos].Last.Date.empty()?Ztring(_T("XXXX-XX-XX")):Speed_TimeStampsZ[Pos].Last.Date;
                Errors_Stats_End_Lines+=_T(' ');
                Errors_Stats_End_Lines+=Speed_TimeStampsZ[Pos].Last.Time.empty()?Ztring(_T("XX:XX:XX:XX")):Speed_TimeStampsZ[Pos].Last.Time;

                Errors_Stats_End_Lines+=_T("\t");

                //Frame range
                int64u Start=Pos?Speed_TimeStampsZ[Pos-1].Last.FramePos:0;
                Ztring Start_Padded=Ztring::ToZtring(Start);
                if (Start_Padded.size()<8)
                    Start_Padded.insert(0, 8-Start_Padded.size(), _T(' '));
                
                Errors_Stats_End_Lines+=Start_Padded;

                int64u End=Speed_TimeStampsZ[Pos].Last.FramePos-1;
                Ztring End_Padded=Ztring::ToZtring(End);
                if (End_Padded.size()<8)
                    End_Padded.insert(0, 8-End_Padded.size(), _T(' '));
                Errors_Stats_End_Lines+=_T(" - ")+End_Padded;

                Errors_Stats_End_Lines+=_T('&');
            }
        }
    }

    //One block
    if (!Errors_Stats_End_Lines.empty())
    {
        Errors_Stats_End_05+=Errors_Stats_End_Lines;
        Errors_Stats_End_05+=_T('&');
        Errors_Stats_End_Lines.clear();
    }

    //
    if (Errors_Stats_End_03.size()>2)
        Errors_Stats_End_03.resize(Errors_Stats_End_03.size()-2); //Removing last carriage returns
    if (Errors_Stats_End_05.size()>2)
        Errors_Stats_End_05.resize(Errors_Stats_End_05.size()-2); //Removing last carriage returns

    //Filling
    if (Count_Get(Stream_Video)==0)
        Stream_Prepare(Stream_Video);
    Fill(Stream_Video, 0, "Errors_Stats_Begin", "Frame # \tTime        \tTimeCode   \tN\tRecorded date/time     \tN\tA\tS\tE\t1\t2\t3\t4\t5\t6\t7\t8\t9\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\t0");
    (*Stream_More)[Stream_Video][0](Ztring().From_Local("Errors_Stats_Begin"), Info_Options)=_T("N NT");
    Fill(Stream_Video, 0, "Errors_Stats_03", Errors_Stats_03);
    (*Stream_More)[Stream_Video][0](Ztring().From_Local("Errors_Stats_03"), Info_Options)=_T("N NT");
    Fill(Stream_Video, 0, "Errors_Stats_05", Errors_Stats_05);
    (*Stream_More)[Stream_Video][0](Ztring().From_Local("Errors_Stats_05"), Info_Options)=_T("N NT");
    Fill(Stream_Video, 0, "Errors_Stats_10", Errors_Stats_10);
    (*Stream_More)[Stream_Video][0](Ztring().From_Local("Errors_Stats_10"), Info_Options)=_T("N NT");
    if (MediaInfoLib::Config.Verbosity_Get()>=(float32)1.0)
        Fill(Stream_Video, 0, "Errors_Stats", Errors_Stats_10);
    else if (MediaInfoLib::Config.Verbosity_Get()>=(float32)0.5)
        Fill(Stream_Video, 0, "Errors_Stats", Errors_Stats_05);
    else
        Fill(Stream_Video, 0, "Errors_Stats", Errors_Stats_03);
    (*Stream_More)[Stream_Video][0](Ztring().From_Local("Errors_Stats"), Info_Options)=_T("N NT");
    Fill(Stream_Video, 0, "Errors_Stats_End_03", Errors_Stats_End_03);
    (*Stream_More)[Stream_Video][0](Ztring().From_Local("Errors_Stats_End_03"), Info_Options)=_T("N NT");
    Fill(Stream_Video, 0, "Errors_Stats_End_05", Errors_Stats_End_05);
    (*Stream_More)[Stream_Video][0](Ztring().From_Local("Errors_Stats_End_05"), Info_Options)=_T("N NT");
    if (MediaInfoLib::Config.Verbosity_Get()>=(float32)0.5)
        Fill(Stream_Video, 0, "Errors_Stats_End", Errors_Stats_End_05);
    else
        Fill(Stream_Video, 0, "Errors_Stats_End", Errors_Stats_End_03);
    (*Stream_More)[Stream_Video][0](Ztring().From_Local("Errors_Stats_End"), Info_Options)=_T("N NT");
    Fill(Stream_Video, 0, "FrameCount_Speed", Speed_FrameCount);
    (*Stream_More)[Stream_Video][0](Ztring().From_Local("FrameCount_Speed"), Info_Options)=_T("N NT");
}

} //NameSpace

#endif //MEDIAINFO_DV_YES

