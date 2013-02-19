/**  

File: MySignalHound.h  
Copyright 2012 Test Equipment Plus  
Author: Justin Crooks  
E-Mail: justin@testequipmentplus.com  
Description: Header file for CMySignalHound Class 
			which encapsulates the functionality of the Signal Hound  

Revision History (Windows):
12 JAN 2012		Justin Crooks		Created from Signal Hound code.  Removed Windows dependencies.
19 APR 2012		Justin Crooks		Added AD9864 recalibration support and cleaned up a bit
*/   
#include "Settings.h"
#include "MeasRcvr.h"

// 0 for OK, 1 for no Signal Hound, 2 for couldn't open Signal Hound ports, 98 for no tempco file, 99 for no cal data
#define ERROR_HOUND_MISSING		1
#define ERROR_HOUND_PORTS		2
#define ERROR_HOUND_TEMPCOFILE	98
#define ERROR_HOUND_CALFILE		99

#pragma once

__declspec(dllimport) double mW2dBm(double mWIn);			//Simple function to convert a reading in milliwatts to a reading in dBm.
__declspec(dllimport) double GetRBWFromIndex(int idx);	//Returns RBW in Hz


// *************************************************************************************
// Visit signalhound.com and download the Headless API Manual for documentation on
//  how to use the CMySignalHound class.
// *************************************************************************************

class CMySignalHound
{
public:

	__declspec(dllimport) CMySignalHound(void);
	__declspec(dllimport) ~CMySignalHound(void);

	__declspec(dllimport) int Initialize(void);

	// ***** Sweep functions *****
	__declspec(dllimport) int SetupForSweep(void);
	__declspec(dllimport) int PreamplifierOnOff(bool onoff);

	__declspec(dllimport) int SetCenterAndSpan(double cf, double span);
	__declspec(dllimport) int SetStartAndStop(double start, double stop);

	__declspec(dllimport) int DoSweep();

	__declspec(dllimport) double GetFrequencyFromIdx(int idx);
	__declspec(dllimport) int SetExternalRef();

	// ***** Channel power functions *****
	__declspec(dllimport) double GetACPL();
	__declspec(dllimport) double GetACPR();
	__declspec(dllimport) double GetCP();

	// ***** Special Purpose functions *****
	__declspec(dllimport) int DoPhaseNoiseSweep(int startDecade, int stopDecade, double referenceAmplitude);
	__declspec(dllimport) double ReadTemperature();
	__declspec(dllimport) int DoMeasuringReceiver(MEAS_RCVR_STRUCT * pMeasRcvr);
	__declspec(dllimport) void * OpenAudio();
	__declspec(dllimport) void CloseAudio(void * pAudioStr);

protected:	//Functions for internal use only.
	int SetBestClock(void);
	int GetBestSensitivity(void);
	int GetMaxFFTPowerFromRBW(double RBW);
	int GetMinFFTPowerFromRBW(double RBW);
	bool ForceFastSweep(double span, int swptmsetpt);
	int CheckRBWVBW(void);

	double m_lastCal9864Temp; //Variable for internal use only

public:
	CSettings m_settings;
	double * pDataMin;
	double * pDataMax;

	double	m_channelBW;
	double	m_channelSpacing;
	int m_BBSPSetpt;
	int m_serialNumber;

	double m_HzPerPt;
	int m_traceSize;
	int m_SubTraceSize;


};

