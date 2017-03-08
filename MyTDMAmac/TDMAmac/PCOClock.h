//***************************************************************************
// * File:        This file is part of TS2.
// * Created on:  07 Dov 2016
// * Author:      Yan Zong, Xuweu Dai
// *
// * Copyright:   (C) 2016 Northumbria University, UK.
// *
// *              TS2 is free software; you can redistribute it and/or modify it
// *              under the terms of the GNU General Public License as published
// *              by the Free Software Foundation; either version 3 of the
// *              License, or (at your option) any later version.
// *
// *              TS2 is distributed in the hope that it will be useful, but
// *              WITHOUT ANY WARRANTY; without even the implied warranty of
// *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *              GNU General Public License for more details.
// *
// * Funding:     This work was financed by the Northumbria University Faculty
//                Funded and RDF funded studentship, UK
// ****************************************************************************


#ifndef PCOClock_H_
#define PCOClock_H_

#include <string.h>
#include <omnetpp.h>
#include <fstream>
#include "Packet_m.h"

class PCOClock:public cSimpleModule
{
    public:
        void adjustThreshold();
        int getnumPulse();
        double getPCOTimestamp();
        double getTimestamp();  // timestamp clock
        double setReceivedTime(double value);

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void finish();
        virtual void updateDisplay();
        cModule *findHost(void);

    private:
        double Phyclockupdate();
        void   recordResult();
        void generateSYNC();

        double lastupdatetime;
        double phyclock;
        double softclock;
        double softclock_t2;
        double softclock_t3;
        double offset;
        double drift;
        double error_offset;
        double error_drift;
        double sigma1;
        double sigma2;
        double sigma3;
        double u3;
        double noise1;
        double noise2;
        double noise3;
        double Tcamp;
        double Tsync;
        double t_previous;
        double drift_previous; //�������������Ϊ�˼���drift10-drift0��ֵ
        double offset_previous;
        double delta_drift;  //����drift10-drift0��ֵ
        double delta_offset;
        double offset_adj_value;//offset��У��ֵ
        double offset_adj_previous;//ǰһ��ͬ��ʱoffset��У��ֵ
        double drift_adj_value;
        double sim_time_limit;  //����ʱ��
        int i;
        int j;//ȥ��ǰ10��ͬ��У��ֵ
        int k;
        double Tm;
        double Tm_previous;


        /*PCO Parameter*/
        double RegisterThreshold;   // the threshold value of register
        double PulseTimePrevious;    // used to reset the clock
        int numPulse;
        double FrameDuration;
        double LastUpdateTime;
        double ThresholdAdjustValue;
        double offsetTotal;
        double RefTimePreviousPulse;
        double ReceivedPulseTime;

        double ThresholdOffset;

        /* @brief this delay consists of transmission delay and propagation delay
         * for propagation delay, the time for 50m is 1/6us
         * for transmission delay, the time for one SYNC packet (44 bytes) is 1.408ms
         * the propagation delay is negligible */
        double delay;

        /* @breif the offset between the PCO drifting clock and standard clock */
        double ClockOffset;

        /* @brief the id of node */
        int NodeId;

        /* @brief Duration of a slot #LMAC */
        double slotDuration;

        /* @brief schedule the second SYNC from node (i.e., rnode[0]) */
        /* @brief duration between beacon (first SYNC packet) and second SYNC packet */
        double ScheduleOffset;

        double AdjustParameter;

        /* @brief time of generating pulse (simTime) */
        double PulseTime;


        std::ofstream outFile;
        cOutVector softclockVec;
        cOutVector softclock_t2Vec;
        cOutVector softclock_t3Vec;
        cOutVector noise1Vec;
        cOutVector noise2Vec;
        cOutVector noise3Vec;
        cOutVector driftVec;
        cOutVector offsetVec;
        cOutVector update_numberVec;  // ��¼����ʱ�Ӹ��µĴ���
        cOutVector delta_driftVec; // ��¼drift10-drift0��ֵ
        cOutVector delta_offsetVec;
        cOutVector drift_adj_valueVec ;//��¼�˲����У��ֵ
        cOutVector offset_adj_valueVec;
        cOutVector drift_valueVec;    //ͬ��У��offsetʱ����¼offset��ʵֵ
        cOutVector offset_valueVec;   //ͬ��У��driftʱ����¼drift��ʵֵ
        cOutVector error_driftVec;   // ��¼driftͬ������ʸ����
        cOutVector error_offsetVec; // ��¼offsetͬ������ʸ����
        cStdDev    driftStd;           //Ϊ����drift��ƽ��ֵ�ͱ�׼��
        cStdDev    offsetStd;
        cStdDev    error_sync_drift;  // Ϊ����driftͬ�����ƽ��ֵ�ͱ�׼��
        cStdDev    error_sync_offset;     // Ϊ����offsetͬ�����ƽ��ֵ�ͱ�׼��

        cOutVector adjustedthresholdvalueVec;    // the adjusted value of threshold
        cOutVector thresholdVec;    // the threshold value
        cOutVector phyclockVec;
        cOutVector pulsetimeVec;    // the threshold value
        cOutVector thresholdOffsetVec;
};

#endif /* PCOClock_H_ */