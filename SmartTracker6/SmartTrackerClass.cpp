// SmartTrackerClass.cpp : Implementation of CSmartTrackerClass
#include "stdafx.h"
#include "SmartTracker6.h"
#include "SmartTrackerClass.h"
#include <math.h>
#include <stdio.h>
#include "EditConfig.h"
#include <process.h>

/////////////////////////////////////////////////////////////////////////////
// CSmartTrackerClass

char *CSmartTrackerClass::pHelpPath = 0;

const int ConfigDataN = 22 + (3 + MAX_TRIGGERS) * MAX_TRIALS;

QueryDataInfo ConfigDataQDI[ConfigDataN] =
{
	{"MaxGrains",   ST_INT,		STRUCT_OFFSET(TrackerData, MaxGrains), 	"10000"},
	{"CellOverflow",ST_INT,		STRUCT_OFFSET(TrackerData, CellOverflow),	"32"},
	{"LayerNum",	ST_INT,		STRUCT_OFFSET(TrackerData, LayerNum), 		"20"},
	{"CellNumX",	ST_INT,		STRUCT_OFFSET(TrackerData, CellNumX),		"10"},
	{"CellNumY",	ST_INT,		STRUCT_OFFSET(TrackerData, CellNumY),		"10"},
	{"PixMin",		ST_INT,		STRUCT_OFFSET(TrackerData, PixMin),			"2"},
	{"PixMax",		ST_INT,		STRUCT_OFFSET(TrackerData, PixMax), 		"64"},
	{"AlignTol",    ST_FLOAT,	STRUCT_OFFSET(TrackerData, AlignTol),		".7"},
	{"TrialCount",  ST_INT,		STRUCT_OFFSET(TrackerData, TrialCount),		"0"},
	{"NptMinV",		ST_FLOAT,	STRUCT_OFFSET(TrackerData, NptMinV)	,		"8.1"},
	{"NptMinH",		ST_FLOAT,	STRUCT_OFFSET(TrackerData, NptMinH)	,		"7"},
	{"NptMin01",	ST_FLOAT,	STRUCT_OFFSET(TrackerData, NptMin01),		"8"},
	{"MinSlope",	ST_FLOAT,   STRUCT_OFFSET(TrackerData, MinSlope),		"-.0005"},
	{"MaxSlope",	ST_FLOAT,   STRUCT_OFFSET(TrackerData, MaxSlope),		"1"},
	{"Processors",	ST_INT,		STRUCT_OFFSET(TrackerData, Processors),		"2"},
	{"MaxTrackingTime",	ST_INT,	STRUCT_OFFSET(TrackerData, MaxTrackingTime),	"300"},

	{"ReplicaRadius",			ST_FLOAT,	STRUCT_OFFSET(TrackerData, ReplicaRadius),		"2"},
	{"ReplicaSampleDivider",	ST_INT,		STRUCT_OFFSET(TrackerData, ReplicaSampleDivider),	"8"},
	{"MinReplicas",				ST_INT,		STRUCT_OFFSET(TrackerData, MinReplicas),			"40"},
	{"MaxReplicaSpread",		ST_FLOAT,	STRUCT_OFFSET(TrackerData, MaxReplicaSpread),		"1"},
	
	{"DiscardShadowSigma",		ST_FLOAT,	STRUCT_OFFSET(TrackerData, DiscardShadowSigma),		"2"},	
	{"CheckGrainSpacing",		ST_INT,		STRUCT_OFFSET(TrackerData, CheckGrainSpacing),		"1"},	

	{"TTop0",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[0].TopLayer),		"-1"},
	{"TBottom0",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[0].BottomLayer),	"-1"},
	{"TTriggers0",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[0].TriggerCount),	"-1"},
	{"TTrigger00",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[0].Triggers[0]),	"-1"},
	{"TTrigger01",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[0].Triggers[1]),	"-1"},
	{"TTrigger02",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[0].Triggers[2]),	"-1"},
	{"TTrigger03",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[0].Triggers[3]),	"-1"},
	{"TTrigger04",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[0].Triggers[4]),	"-1"},
	{"TTrigger05",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[0].Triggers[5]),	"-1"},
	{"TTrigger06",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[0].Triggers[6]),	"-1"},
	{"TTrigger07",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[0].Triggers[7]),	"-1"},

	{"TTop1",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[1].TopLayer),		"-1"},
	{"TBottom1",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[1].BottomLayer),	"-1"},
	{"TTrigger1",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[1].TriggerCount),	"-1"},
	{"TTrigger10",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[1].Triggers[0]),	"-1"},
	{"TTrigger11",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[1].Triggers[1]),	"-1"},
	{"TTrigger12",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[1].Triggers[2]),	"-1"},
	{"TTrigger13",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[1].Triggers[3]),	"-1"},
	{"TTrigger14",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[1].Triggers[4]),	"-1"},
	{"TTrigger15",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[1].Triggers[5]),	"-1"},
	{"TTrigger16",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[1].Triggers[6]),	"-1"},
	{"TTrigger17",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[1].Triggers[7]),	"-1"},

	{"TTop2",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[2].TopLayer),		"-1"},
	{"TBottom2",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[2].BottomLayer),	"-1"},
	{"TTrigger2",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[2].TriggerCount),	"-1"},
	{"TTrigger20",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[2].Triggers[0]),	"-1"},
	{"TTrigger21",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[2].Triggers[1]),	"-1"},
	{"TTrigger22",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[2].Triggers[2]),	"-1"},
	{"TTrigger23",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[2].Triggers[3]),	"-1"},
	{"TTrigger24",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[2].Triggers[4]),	"-1"},
	{"TTrigger25",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[2].Triggers[5]),	"-1"},
	{"TTrigger26",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[2].Triggers[6]),	"-1"},
	{"TTrigger27",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[2].Triggers[7]),	"-1"},

	{"TTop3",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[3].TopLayer),		"-1"},
	{"TBottom3",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[3].BottomLayer),	"-1"},
	{"TTrigger3",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[3].TriggerCount),	"-1"},
	{"TTrigger30",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[3].Triggers[0]),	"-1"},
	{"TTrigger31",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[3].Triggers[1]),	"-1"},
	{"TTrigger32",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[3].Triggers[2]),	"-1"},
	{"TTrigger33",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[3].Triggers[3]),	"-1"},
	{"TTrigger34",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[3].Triggers[4]),	"-1"},
	{"TTrigger35",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[3].Triggers[5]),	"-1"},
	{"TTrigger36",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[3].Triggers[6]),	"-1"},
	{"TTrigger37",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[3].Triggers[7]),	"-1"},

	{"TTop4",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[4].TopLayer),		"-1"},
	{"TBottom4",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[4].BottomLayer),	"-1"},
	{"TTrigger4",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[4].TriggerCount),	"-1"},
	{"TTrigger40",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[4].Triggers[0]),	"-1"},
	{"TTrigger41",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[4].Triggers[1]),	"-1"},
	{"TTrigger42",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[4].Triggers[2]),	"-1"},
	{"TTrigger43",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[4].Triggers[3]),	"-1"},
	{"TTrigger44",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[4].Triggers[4]),	"-1"},
	{"TTrigger45",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[4].Triggers[5]),	"-1"},
	{"TTrigger46",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[4].Triggers[6]),	"-1"},
	{"TTrigger47",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[4].Triggers[7]),	"-1"},

	{"TTop5",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[5].TopLayer),		"-1"},
	{"TBottom5",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[5].BottomLayer),	"-1"},
	{"TTrigger5",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[5].TriggerCount),	"-1"},
	{"TTrigger50",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[5].Triggers[0]),	"-1"},
	{"TTrigger51",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[5].Triggers[1]),	"-1"},
	{"TTrigger52",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[5].Triggers[2]),	"-1"},
	{"TTrigger53",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[5].Triggers[3]),	"-1"},
	{"TTrigger54",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[5].Triggers[4]),	"-1"},
	{"TTrigger55",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[5].Triggers[5]),	"-1"},
	{"TTrigger56",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[5].Triggers[6]),	"-1"},
	{"TTrigger57",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[5].Triggers[7]),	"-1"},

	{"TTop6",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[6].TopLayer),		"-1"},
	{"TBottom6",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[6].BottomLayer),	"-1"},
	{"TTrigger6",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[6].TriggerCount),	"-1"},
	{"TTrigger60",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[6].Triggers[0]),	"-1"},
	{"TTrigger61",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[6].Triggers[1]),	"-1"},
	{"TTrigger62",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[6].Triggers[2]),	"-1"},
	{"TTrigger63",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[6].Triggers[3]),	"-1"},
	{"TTrigger64",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[6].Triggers[4]),	"-1"},
	{"TTrigger65",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[6].Triggers[5]),	"-1"},
	{"TTrigger66",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[6].Triggers[6]),	"-1"},
	{"TTrigger67",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[6].Triggers[7]),	"-1"},

	{"TTop7",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[7].TopLayer),		"-1"},
	{"TBottom7",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[7].BottomLayer),	"-1"},
	{"TTrigger7",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[7].TriggerCount),	"-1"},
	{"TTrigger70",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[7].Triggers[0]),	"-1"},
	{"TTrigger71",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[7].Triggers[1]),	"-1"},
	{"TTrigger72",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[7].Triggers[2]),	"-1"},
	{"TTrigger73",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[7].Triggers[3]),	"-1"},
	{"TTrigger74",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[7].Triggers[4]),	"-1"},
	{"TTrigger75",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[7].Triggers[5]),	"-1"},
	{"TTrigger76",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[7].Triggers[6]),	"-1"},
	{"TTrigger77",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[7].Triggers[7]),	"-1"},

	{"TTop8",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[8].TopLayer),		"-1"},
	{"TBottom8",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[8].BottomLayer),	"-1"},
	{"TTrigger8",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[8].TriggerCount),	"-1"},
	{"TTrigger80",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[8].Triggers[0]),	"-1"},
	{"TTrigger81",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[8].Triggers[1]),	"-1"},
	{"TTrigger82",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[8].Triggers[2]),	"-1"},
	{"TTrigger83",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[8].Triggers[3]),	"-1"},
	{"TTrigger84",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[8].Triggers[4]),	"-1"},
	{"TTrigger85",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[8].Triggers[5]),	"-1"},
	{"TTrigger86",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[8].Triggers[6]),	"-1"},
	{"TTrigger87",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[8].Triggers[7]),	"-1"},

	{"TTop9",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[9].TopLayer),		"-1"},
	{"TBottom9",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[9].BottomLayer),	"-1"},
	{"TTrigger9",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[9].TriggerCount),	"-1"},
	{"TTrigger90",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[9].Triggers[0]),	"-1"},
	{"TTrigger91",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[9].Triggers[1]),	"-1"},
	{"TTrigger92",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[9].Triggers[2]),	"-1"},
	{"TTrigger93",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[9].Triggers[3]),	"-1"},
	{"TTrigger94",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[9].Triggers[4]),	"-1"},
	{"TTrigger95",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[9].Triggers[5]),	"-1"},
	{"TTrigger96",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[9].Triggers[6]),	"-1"},
	{"TTrigger97",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[9].Triggers[7]),	"-1"},

	{"TTopA",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[10].TopLayer),	"-1"},
	{"TBottomA",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[10].BottomLayer),	"-1"},
	{"TTriggerA",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[10].TriggerCount),"-1"},
	{"TTriggerA0",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[10].Triggers[0]),	"-1"},
	{"TTriggerA1",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[10].Triggers[1]),	"-1"},
	{"TTriggerA2",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[10].Triggers[2]),	"-1"},
	{"TTriggerA3",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[10].Triggers[3]),	"-1"},
	{"TTriggerA4",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[10].Triggers[4]),	"-1"},
	{"TTriggerA5",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[10].Triggers[5]),	"-1"},
	{"TTriggerA6",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[10].Triggers[6]),	"-1"},
	{"TTriggerA7",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[10].Triggers[7]),	"-1"},

	{"TTopB",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[11].TopLayer),	"-1"},
	{"TBottomB",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[11].BottomLayer),	"-1"},
	{"TTriggerB",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[11].TriggerCount),"-1"},
	{"TTriggerB0",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[11].Triggers[0]),	"-1"},
	{"TTriggerB1",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[11].Triggers[1]),	"-1"},
	{"TTriggerB2",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[11].Triggers[2]),	"-1"},
	{"TTriggerB3",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[11].Triggers[3]),	"-1"},
	{"TTriggerB4",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[11].Triggers[4]),	"-1"},
	{"TTriggerB5",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[11].Triggers[5]),	"-1"},
	{"TTriggerB6",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[11].Triggers[6]),	"-1"},
	{"TTriggerB7",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[11].Triggers[7]),	"-1"},

	{"TTopC",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[12].TopLayer),	"-1"},
	{"TBottomC",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[12].BottomLayer),	"-1"},
	{"TTriggerC",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[12].TriggerCount),"-1"},
	{"TTriggerC0",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[12].Triggers[0]),	"-1"},
	{"TTriggerC1",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[12].Triggers[1]),	"-1"},
	{"TTriggerC2",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[12].Triggers[2]),	"-1"},
	{"TTriggerC3",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[12].Triggers[3]),	"-1"},
	{"TTriggerC4",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[12].Triggers[4]),	"-1"},
	{"TTriggerC5",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[12].Triggers[5]),	"-1"},
	{"TTriggerC6",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[12].Triggers[6]),	"-1"},
	{"TTriggerC7",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[12].Triggers[7]),	"-1"},

	{"TTopD",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[13].TopLayer),	"-1"},
	{"TBottomD",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[13].BottomLayer),	"-1"},
	{"TTriggerD",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[13].TriggerCount),"-1"},
	{"TTriggerD0",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[13].Triggers[0]),	"-1"},
	{"TTriggerD1",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[13].Triggers[1]),	"-1"},
	{"TTriggerD2",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[13].Triggers[2]),	"-1"},
	{"TTriggerD3",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[13].Triggers[3]),	"-1"},
	{"TTriggerD4",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[13].Triggers[4]),	"-1"},
	{"TTriggerD5",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[13].Triggers[5]),	"-1"},
	{"TTriggerD6",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[13].Triggers[6]),	"-1"},
	{"TTriggerD7",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[13].Triggers[7]),	"-1"},

	{"TTopE",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[14].TopLayer),	"-1"},
	{"TBottomE",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[14].BottomLayer),	"-1"},
	{"TTriggerE",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[14].TriggerCount),"-1"},
	{"TTriggerE0",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[14].Triggers[0]),	"-1"},
	{"TTriggerE1",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[14].Triggers[1]),	"-1"},
	{"TTriggerE2",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[14].Triggers[2]),	"-1"},
	{"TTriggerE3",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[14].Triggers[3]),	"-1"},
	{"TTriggerE4",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[14].Triggers[4]),	"-1"},
	{"TTriggerE5",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[14].Triggers[5]),	"-1"},
	{"TTriggerE6",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[14].Triggers[6]),	"-1"},
	{"TTriggerE7",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[14].Triggers[7]),	"-1"},

	{"TTopF",		ST_INT,		STRUCT_OFFSET(TrackerData, Trials[15].TopLayer),	"-1"},
	{"TBottomF",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[15].BottomLayer),	"-1"},
	{"TTriggerF",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[15].TriggerCount),"-1"},
	{"TTriggerF0",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[15].Triggers[0]),	"-1"},
	{"TTriggerF1",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[15].Triggers[1]),	"-1"},
	{"TTriggerF2",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[15].Triggers[2]),	"-1"},
	{"TTriggerF3",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[15].Triggers[3]),	"-1"},
	{"TTriggerF4",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[15].Triggers[4]),	"-1"},
	{"TTriggerF5",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[15].Triggers[5]),	"-1"},
	{"TTriggerF6",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[15].Triggers[6]),	"-1"},
	{"TTriggerF7",	ST_INT,		STRUCT_OFFSET(TrackerData, Trials[15].Triggers[7]),	"-1"}
	};

// ISySalObject
STDMETHODIMP CSmartTrackerClass::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	OkToRun = false;
	if (GetData(*pConfig, ConfigDataN, ConfigDataQDI, &T, false) != ConfigDataN) return S_FALSE;
	if (T.GrainSpace) GlobalFree(T.GrainSpace);
	if (!(T.GrainSpace = (IntGrain *)GlobalAlloc(GMEM_FIXED, sizeof(IntGrain) * T.MaxGrains)))
		return S_FALSE;
	if (T.ZLayer) GlobalFree(T.ZLayer);
	if (!(T.ZLayer = (float *)GlobalAlloc(GMEM_FIXED, sizeof(float) * T.LayerNum)))
   		return S_FALSE;
	if (T.LayerGrains) GlobalFree(T.LayerGrains);
	if (!(T.LayerGrains = (IntGrain **)GlobalAlloc(GMEM_FIXED, sizeof(IntGrain *) * T.LayerNum)))
   		return S_FALSE;
	T.CellsInLayer = T.CellNumX * T.CellNumY;
	if (T.CellSpace) GlobalFree(T.CellSpace);
	if (!(T.CellSpace = (Cell *)GlobalAlloc(GMEM_FIXED, sizeof(Cell) * (T.CellsInLayer)*(T.LayerNum))))
   		return S_FALSE;
	SetEvent(HTerminate);
	int i;
	for (i = 1; i < MAX_PROCESSORS; i++)
		if (ThreadInfo[i].HThread)
		{
			WaitForSingleObject(ThreadInfo[i].HThread, INFINITE);
			CloseHandle(ThreadInfo[i].HThread);
			CloseHandle(ThreadInfo[i].HFinished);
			ThreadInfo[i].HThread = 0;
			ThreadInfo[i].HFinished = 0;
			};
	ResetEvent(HTerminate);
	ResetEvent(HStart);
	ResetEvent(HReset);
	ThreadInfo[0].ThreadIndex = 0;
	for (i = 1; i < T.Processors; i++)
	{
		unsigned dummy;
		ThreadInfo[i].HFinished = CreateEvent(NULL, FALSE, FALSE, NULL);
		ThreadInfo[i].pThis = this;
		ThreadInfo[i].ThreadIndex = i;
		ThreadInfo[i].HThread = (HANDLE)_beginthreadex(NULL, 0, TrackerThreadHook, ThreadInfo + i, 0, &dummy);
		}
	OkToRun = true;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	if (::PutData(*pConfig, ConfigDataN, ConfigDataQDI, &T) != ConfigDataN) return S_FALSE;
	return S_OK;	
}

STDMETHODIMP CSmartTrackerClass::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(this, &Owner);

	GetData(*pConfig, ConfigDataN, ConfigDataQDI, &MyDlg.C, true);

	if (MyDlg.DoModal() == IDOK)
	{
		::PutData(*pConfig, ConfigDataN, ConfigDataQDI, &MyDlg.C);
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CSmartTrackerClass::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? S_FALSE : S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::GetIcon(int n, HSySalHICON *pHICON)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	HANDLE HTemp = 0;
	switch (n)
	{
		case 0:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON32), IMAGE_ICON, 32, 32, LR_SHARED);
					break;

		case 1:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON64), IMAGE_ICON, 64, 64, LR_SHARED);
					break;

		default:	return E_INVALIDARG;
		};
	*pHICON = (HSySalHICON)HTemp;
	return S_OK;	
}

STDMETHODIMP CSmartTrackerClass::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Smart Tracker 6", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::StartFilling()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!OkToRun) return S_FALSE;
	T.Layer = 0;
	T.NumGrains = 0;
	T.DispX = T.DispY = 0.0f;
	T.ShadowSigmaMeasures = 0;
	T.ShadowSigmaXAccumulator = T.ShadowSigmaYAccumulator = 0.0f;
	return S_OK;
}



STDMETHODIMP CSmartTrackerClass::SetCameraSpec(CameraSpec Spec)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Spec.PixelToMicronX != 0.f && Spec.PixelToMicronY != 0.f &&
		Spec.Height > 0 && Spec.Width > 0 && Spec.WinHeight > 0 && Spec.WinWidth > 0)
	{
		CamSpec = Spec;
		T.PixelToMicronX = Spec.PixelToMicronX;
		T.PixelToMicronY = Spec.PixelToMicronY;
		if (T.PixelToMicronX > 0)
		{	T.Win.Xmin = Spec.OffX;
			T.Win.Xmax = Spec.OffX + Spec.WinWidth;
			}
		else
		{	T.Win.Xmax = Spec.OffX;
			T.Win.Xmin = Spec.OffX + Spec.WinWidth;
			};
		if (T.PixelToMicronY > 0)
		{  T.Win.Ymin = Spec.OffY;
			T.Win.Ymax = Spec.OffY + Spec.WinHeight;
			}
		else
		{	T.Win.Ymax = Spec.OffY;
			T.Win.Ymin = Spec.OffY + Spec.WinHeight;
			};
		T.Win.Xmin *= T.PixelToMicronX;
		T.Win.Xmax *= T.PixelToMicronX;
		T.Win.Ymin *= T.PixelToMicronY;
		T.Win.Ymax *= T.PixelToMicronY;
		T.DxCell = ((T.Win.Xmax - T.Win.Xmin)/(float)(T.CellNumX));
		T.DyCell = ((T.Win.Ymax - T.Win.Ymin)/(float)(T.CellNumY));
		return S_OK;
		};
	return E_INVALIDARG;
}

STDMETHODIMP CSmartTrackerClass::GetCameraSpec(CameraSpec *pSpec)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pSpec = CamSpec;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::PutClusters(Cluster *pClusters, int CountOfClusters, float Z)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	int Nc;
	int Icell;
	IntCluster *PClus;
	Cell *PCell;
	IntGrain *PGrain, *PGrainEnd;
	int PixMin = T.PixMin;
	int PixMax = T.PixMax;
	float PixelToMicronX = T.PixelToMicronX;
	float PixelToMicronY = T.PixelToMicronY;
	float PixelToMicronXY = fabs(PixelToMicronX * PixelToMicronY);
	float PixelToMicronX3Y = PixelToMicronXY * PixelToMicronX * PixelToMicronX;
	float PixelToMicronY3X = PixelToMicronXY * PixelToMicronY * PixelToMicronY;
	float PixelToMicronX2Y2 = PixelToMicronXY * PixelToMicronXY;
	int CellsInLayer = T.CellsInLayer;
	Cell *CellSpace = T.CellSpace;
	int Layer = T.Layer;
	int CellOverflow = T.CellOverflow;
	int CurrentGCounter = T.NumGrains;
	int MaxGrains = T.MaxGrains;
	float CurrDispX = 0.0f;
	float CurrDispY = 0.0f;
	float CurrDispSigmaX = 0.0f;
	float CurrDispSigmaY = 0.0f;
	float DispX = T.DispX;
	float DispY = T.DispY;
	float CX, CY, DX, DY;
	int ReplicaCount = 0;
	int ReplicaDivider = T.ReplicaSampleDivider;
	int DividerCount;
	float ReplicaRadius = T.ReplicaRadius;

	if (!OkToRun) return S_FALSE;

	if (Layer >= T.LayerNum) return S_FALSE;
	T.ZLayer[Layer] = Z;
	for (Icell = 0; Icell < CellsInLayer; Icell++)
	{	((Cell *)CellSpace)[Layer*CellsInLayer+Icell].FirstC = 0;
		((Cell *)CellSpace)[Layer*CellsInLayer+Icell].Free = 0;
		};

	if (T.ReplicaRadius > 0.0f && Layer > 0)
	{
		for (Nc = DividerCount = 0; (Nc < CountOfClusters) && (CurrentGCounter < MaxGrains); Nc++)
		{	
			PClus = (IntCluster *)(pClusters + Nc);
			if ((PClus->Area >= PixMin) && (PClus->Area <= PixMax))
			{	
				Icell = GetCell(PClus->X *= PixelToMicronX, PClus->Y *= PixelToMicronY);
				if (Icell >= 0)
				{	
					PCell = (Cell *)(CellSpace+(Layer*CellsInLayer+Icell));
					PCell->Free++;
					CurrentGCounter++;
					PClus->NextFree = PCell->FirstC;
					PCell->FirstC = PClus;
					if (++DividerCount == ReplicaDivider)
					{
						DividerCount = 0;
						PCell -= CellsInLayer;
						CX = PClus->X + DispX;
						CY = PClus->Y + DispY;						
						IntGrain *pRep = PCell->FirstG;
						IntGrain *pEnd = pRep + PCell->Free;
						while (pRep < pEnd)
						{
							if (fabs(DX = (pRep->Xcm - CX)) < ReplicaRadius && fabs(DY = (pRep->Ycm - CY)) < ReplicaRadius) 
							{
								CurrDispX += DX;
								CurrDispSigmaX += DX * DX;
								CurrDispY += DY;
								CurrDispSigmaY += DY * DY;
								ReplicaCount++;
								break;
								}
							pRep++;
							}
						}
					};
				};
			};
		if (ReplicaCount >= T.MinReplicas)
		{
			float r2 = 1.0f / (ReplicaCount * ReplicaCount);
			CurrDispSigmaX = (ReplicaCount * CurrDispSigmaX - CurrDispX * CurrDispX) * r2;
			CurrDispSigmaY = (ReplicaCount * CurrDispSigmaY - CurrDispY * CurrDispY) * r2;
			float maxspread2 = T.MaxReplicaSpread * T.MaxReplicaSpread;
			if (CurrDispSigmaX < maxspread2 && CurrDispSigmaY < maxspread2)
			{
				T.DispX = (DispX += CurrDispX / ReplicaCount);
				T.DispY = (DispY += CurrDispY / ReplicaCount);
				T.ShadowSigmaMeasures++;
				T.ShadowSigmaXAccumulator += CurrDispSigmaX;
				T.ShadowSigmaYAccumulator += CurrDispSigmaY;
				}
			}
		}
	else
	{
		for (Nc = 0; (Nc < CountOfClusters) && (CurrentGCounter < MaxGrains); Nc++)
		{	
			PClus = (IntCluster *)(pClusters + Nc);
			if ((PClus->Area >= PixMin) && (PClus->Area <= PixMax))
			{	
				Icell = GetCell(PClus->X *= PixelToMicronX, PClus->Y *= PixelToMicronY);
				if (Icell >= 0)
				{	
					PCell = (Cell *)(CellSpace+(Layer*CellsInLayer+Icell));
					PCell->Free++;
					CurrentGCounter++;
					PClus->NextFree = PCell->FirstC;
					PCell->FirstC = PClus;
					};
				};
			};
		};

	T.LayerGrains[Layer] = PGrain = T.GrainSpace + T.NumGrains;
	PGrainEnd = T.GrainSpace + MaxGrains;

	if (T.ReplicaRadius > 0.0f && Layer > 0)
	{
		for (Icell = 0; (Icell < CellsInLayer) && (PGrain < PGrainEnd); Icell ++)
		{	
			PCell = (Cell *)(CellSpace+(Layer*CellsInLayer+Icell));
			if (PCell->Free)
			{	
				if (PCell->Free < CellOverflow)
				{	
					PClus = PCell->FirstC;
					PCell->FirstG = PGrain;
					do
					{	
						PGrain->Xcm = PClus->X + DispX;
						PGrain->Ycm = PClus->Y + DispY;
						PGrain->Area = PClus->Area;
						PClus = PClus->NextFree;
						}
					while (((++PGrain) < PGrainEnd) && (PClus));
					}
				else
				{	
					PCell->Free = 0;
					PCell->FirstG = 0;
					};
				};
			T.NumGrains += PCell->Free;
			};		
		}
	else
	{
		for (Icell = 0; (Icell < CellsInLayer) && (PGrain < PGrainEnd); Icell ++)
		{	
			PCell = (Cell *)(CellSpace+(Layer*CellsInLayer+Icell));
			if (PCell->Free)
			{	
				if (PCell->Free < CellOverflow)
				{	
					PClus = PCell->FirstC;
					PCell->FirstG = PGrain;
					do
					{	
						PGrain->Xcm = PClus->X;
						PGrain->Ycm = PClus->Y;
						PGrain->Area = PClus->Area;
						PClus = PClus->NextFree;
						}
					while (((++PGrain) < PGrainEnd) && (PClus));
					}
				else
				{	
					PCell->Free = 0;
					PCell->FirstG = 0;
					};
				};
			T.NumGrains += PCell->Free;
			};
		}
/*
	{
		FILE *f = fopen("c:\\acq\\tk.txt", "at");
		fprintf(f, "%d %f %f %d %f %f\n", T.Layer, T.DispX, T.DispY, ReplicaCount, CurrDispSigmaX, CurrDispSigmaY);
		fclose(f);
		}
*/
	if (PGrain >= PGrainEnd) return S_FALSE;
	T.Layer++;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetTracks(Track *pSpace, int *pMaxNumber, int StartLayer, int EndLayer)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	int nx, ny;
	int lay;
	int itr, ibr;
	int NTracks = 0;
	float *ZLayer = T.ZLayer;
	float tz;
	int CellsInLayer = T.CellsInLayer;
	Cell *CellSpace = T.CellSpace;
	float MaxSlope = T.MaxSlope;
	float MinSlope = T.MinSlope;

	int ix, iy, iix, iiy, eix, eiy;
	int minix, maxix, miniy, maxiy;
	float Slope2;
	float SlopeX, SlopeY, ExpX, ExpY, DirX, DirY;
	float dirtol;
	int it, ib, ir;
	float idz;

	nx = T.CellNumX;
	ny = T.CellNumY;

	if (*pMaxNumber <= 0)
	{
		*pMaxNumber = 0;
		return S_OK;
		}

	if (EndLayer >= T.Layer) EndLayer = T.Layer - 1;

	IntGrain **pTempGrains = (IntGrain **)malloc(sizeof(IntGrain *) * (EndLayer + 1));

	float avgdz = (ZLayer[StartLayer] - ZLayer[EndLayer]) / (EndLayer - StartLayer);
			
	float tsl = 10.0f * (T.NptMinV - T.NptMin01) / (T.NptMin01 - T.NptMinH);
	float tinf = (float)(T.NptMinH);
	float td = (float)(T.NptMinV - T.NptMinH);

	for (itr = 0; itr < T.TrialCount; itr++)
	{
		Trial tr = T.Trials[itr];
		if (tr.TopLayer < StartLayer || tr.BottomLayer > EndLayer) continue;
		Cell *tp = CellsInLayer * tr.TopLayer + CellSpace;
		Cell *bp = CellsInLayer * tr.BottomLayer + CellSpace;
		tz = ZLayer[tr.TopLayer];
		idz = 1.0f / (tz - ZLayer[tr.BottomLayer]);

		for (ix = 0; ix < nx; ix++)
		{
			minix = ix - 1; if (minix < 0) minix = 0;
			maxix = ix + 1; if (maxix >= nx) maxix = nx - 1;
			for (iy = 0; iy < ny; iy++)
			{
				miniy = iy - 1; if (miniy < 0) miniy = 0;
				maxiy = iy + 1; if (maxiy >= ny) maxiy = ny - 1;
				Cell &ct = tp[iy * nx + ix];
				IntGrain *pT = ct.FirstG;
				IntGrain *pTE = ct.FirstG + ct.Free;
				for (;pT < pTE; pT++)
				{
					IntGrain gt = *pT;
					for (iix = minix; iix <= maxix; iix++)
						for (iiy = miniy; iiy <= maxiy; iiy++)
						{
							Cell &cb = bp[iiy * nx + iix];
							IntGrain *pB = cb.FirstG;
							IntGrain *pBE = cb.FirstG + cb.Free;
							for (;pB < pBE; pB++)
							{
								IntGrain gb = *pB;
								SlopeX = idz * (gt.Xcm - gb.Xcm);
								SlopeY = idz * (gt.Ycm - gb.Ycm);
								Slope2 = hypot(SlopeX, SlopeY);
								if (Slope2 < MaxSlope)
								{
									GetDirAndTol(SlopeX, SlopeY, avgdz, &DirX, &DirY, &dirtol);
									for (ir = 0; ir < tr.TriggerCount; ir++)
									{
										int TriggerLayer = tr.Triggers[ir];
										float ldz = (tz - ZLayer[TriggerLayer]) * idz;
										float cdz = 1.0f - ldz;
										ExpX = ldz * gb.Xcm + cdz * gt.Xcm;
										ExpY = ldz * gb.Ycm + cdz * gt.Ycm;
										eix = (int)((ExpX - T.Win.Xmin) / T.DxCell);
										eiy = (int)((ExpY - T.Win.Ymin) / T.DyCell);
										IntGrain *pTrg = CellSpace[(TriggerLayer * ny + eiy) * nx + eix].FindGrain(ExpX, ExpY, DirX, DirY, dirtol, T.AlignTol);
										if (pTrg)
										{
											memset(pTempGrains, 0, T.Layer * sizeof(Grain *));
											float dz;
											int seqlength = 3;

											pTempGrains[tr.TopLayer] = pT;
											pTempGrains[tr.BottomLayer] = pB;
											pTempGrains[TriggerLayer] = pTrg;

											for (lay = tr.TopLayer + 1; lay < TriggerLayer; lay++)
											{
												dz = ZLayer[lay] - tz;
												ExpX = dz * SlopeX + gt.Xcm;
												ExpY = dz * SlopeY + gt.Ycm;
												if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol)) seqlength++;
												};
											for (lay = TriggerLayer + 1; lay < tr.BottomLayer; lay++)
											{
												dz = ZLayer[lay] - tz;
												ExpX = dz * SlopeX + gt.Xcm;
												ExpY = dz * SlopeY + gt.Ycm;
												if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol)) seqlength++;
												};
											Vector topv, bottomv;
											topv.X = pT->Xcm;
											topv.Y = pT->Ycm;
											topv.Z = tz;
											bottomv.X = pB->Xcm;
											bottomv.Y = pB->Ycm;
											bottomv.Z = ZLayer[tr.BottomLayer];
											for (lay = (int)tr.TopLayer - 1; lay >= 0; lay--)
											{
												dz = (bottomv.Z - topv.Z);
												SlopeX = (bottomv.X - topv.X) / dz;
												SlopeY = (bottomv.Y - topv.Y) / dz;
												GetDirAndTol(SlopeX, SlopeY, avgdz, &DirX, &DirY, &dirtol);
												dz = ZLayer[lay] - topv.Z;
												ExpX = dz * SlopeX + topv.X;
												ExpY = dz * SlopeY + topv.Y;
												if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol))
												{
													topv.X = pTempGrains[lay]->Xcm;
													topv.Y = pTempGrains[lay]->Ycm;
													topv.Z = ZLayer[lay];
													seqlength++;
													}
												};
											for (lay = (int)tr.BottomLayer + 1; lay <= EndLayer; lay++)
											{
												dz = (bottomv.Z - topv.Z);
												SlopeX = (bottomv.X - topv.X) / dz;
												SlopeY = (bottomv.Y - topv.Y) / dz;
												GetDirAndTol(SlopeX, SlopeY, avgdz, &DirX, &DirY, &dirtol);
												dz = ZLayer[lay] - topv.Z;
												ExpX = dz * SlopeX + topv.X;
												ExpY = dz * SlopeY + topv.Y;
												if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol))
												{
													bottomv.X = pTempGrains[lay]->Xcm;
													bottomv.Y = pTempGrains[lay]->Ycm;
													bottomv.Z = ZLayer[lay];
													seqlength++;
													}
												};
											if ((float)seqlength > (tinf + td / (1.0f + tsl * Slope2)))
											{
												InsertNewTrack(pTempGrains, EndLayer + 1, seqlength, pSpace, NTracks);
												if (NTracks >= *pMaxNumber)
												{
													*pMaxNumber = FinalizeTracks(NTracks, pSpace);
													free(pTempGrains);
													}
												break;
												}
											}
										}
									}
								}
							}
					}
				}
			}
		}

	*pMaxNumber = FinalizeTracks(NTracks, pSpace);
	free(pTempGrains);
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetClusters(int Layer, Cluster *pSpace, int *pMaxNumber, float *pZ)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here	
	if (!OkToRun) return S_FALSE;	
	if (Layer < 0 || Layer >= T.LayerNum) return E_INVALIDARG;
	int MaxNumber = *pMaxNumber;
	*pZ = T.ZLayer[Layer];
	int i, j, ccount = 0;
	Cell *pCells = T.CellSpace;
	try
	{
		for (i = 0; i < T.CellsInLayer; i++)
		{
			Cell TCell = pCells[i];
			for (j = 0; j < TCell.Free; j++)
			{
				pSpace->X = TCell.FirstG[j].Xcm;
				pSpace->Y = TCell.FirstG[j].Ycm;
				pSpace->Area = 0;
				pSpace->GrayLevel = 0;
				pSpace->Inertia.IXX = pSpace->Inertia.IYY = pSpace->Inertia.IXY = 0;
				pSpace++;
				if (ccount >= MaxNumber) throw ccount;
				};
			}
		}
	catch (...) {};
	*pMaxNumber = ccount;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::PresetSlope(float SX, float SY, float AccX, float AccY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::EnableSlopePresetting(boolean SlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	T.EnableSlopePresetting = SlPresEnable;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetSlopePresetStatus(boolean *pSlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pSlPresEnable = false;
	return S_OK;
}

HRESULT CSmartTrackerClass::GetFlatTracks(FlatTrack *pSpace, int *pMaxNumber, int MaxStripsInTrack, int StartLayer, int EndLayer)
{
	*pMaxNumber = 0;
	return E_NOTIMPL;
	};

HRESULT CSmartTrackerClass::GetFlatStrips(int Layer, FlatStrip *pSpace, int *pMaxNumber, float *pZ)
{
	*pMaxNumber = 0;
	return E_NOTIMPL;
	};

/* 
	Double coding section:
	Function implementation followed by their fast macro versions 
*/
void CSmartTrackerClass::GetDirAndTol(float SlopeX, float SlopeY, float avgdz, float *pDirX, float *pDirY, float *pdirtol)
{
	float slope2 = (float)hypot(SlopeX, SlopeY);
	if (slope2 <= 0.0f)
	{
		*pDirX = 1.0f;
		*pDirY = 0.0f;
		*pdirtol = T.AlignTol;					
	}
	else
	{
		*pDirX = SlopeX / slope2;
		*pDirY = SlopeY / slope2;
		*pdirtol = hypot(T.AlignTol, avgdz * slope2);
	}
};

#define fastGetDirAndTol(SlopeS, ISlopeS, DirX, DirY, dirtol, avgds2, aligntol2) \
{ \
	if (SlopeS <= 0.0f) \
	{ \
		DirX = 1.0f; \
		DirY = 0.0f; \
		dirtol = T.AlignTol; \
		} \
	else \
	{ \
		DirX = SlopeX * ISlopeS; \
		DirY = SlopeY * ISlopeS; \
		dirtol = sqrt(aligntol2 + avgds2); \
		}; \
	}								

/* End of double coding section */

IntGrain *CSmartTrackerClass::FindGrain(float expx, float expy, Cell *pCellLayer, float dirx, float diry, float dirtol, IntGrain *pTopShadow, IntGrain *pBottomShadow, float xshadowtol, float yshadowtol)
{
	float fix, fiy;
	int eix = (int)(fix = ((expx - T.Win.Xmin) / T.DxCell));
	if (eix < 0 || eix >= T.CellNumX) return 0;
	int eiy = (int)(fiy = ((expy - T.Win.Ymin) / T.DyCell));
	if (eiy >= 0 && eiy < T.CellNumY)
	{
		IntGrain *pNew = pCellLayer[eiy * T.CellNumX + eix].FindGrainNoShadow(expx, expy, dirx, diry, dirtol, T.AlignTol, pTopShadow, pBottomShadow, xshadowtol, yshadowtol);
		if (pNew) return pNew;
		fix -= (0.5f + eix);
		fiy -= (0.5f + eiy);
		if (fabs(fix) >= fabs(fiy))
		{
			if (fix < 0.0f && eix > 0)
				return pCellLayer[eiy * T.CellNumX + eix - 1].FindGrainNoShadow(expx, expy, dirx, diry, dirtol, T.AlignTol, pTopShadow, pBottomShadow, xshadowtol, yshadowtol);
			else if (fix > 0.0f && eix < (T.CellNumX - 1))
				return pCellLayer[eiy * T.CellNumX + eix + 1].FindGrainNoShadow(expx, expy, dirx, diry, dirtol, T.AlignTol, pTopShadow, pBottomShadow, xshadowtol, yshadowtol);
			}
		else
		{
			if (fiy < 0.0f && eiy > 0)
				return pCellLayer[(eiy - 1) * T.CellNumX + eix].FindGrainNoShadow(expx, expy, dirx, diry, dirtol, T.AlignTol, pTopShadow, pBottomShadow, xshadowtol, yshadowtol);
			else if (fiy > 0.0f && eiy < (T.CellNumX - 1))
				return pCellLayer[(eiy + 1) * T.CellNumX + eix].FindGrainNoShadow(expx, expy, dirx, diry, dirtol, T.AlignTol, pTopShadow, pBottomShadow, xshadowtol, yshadowtol);
			}
		}
	return 0;
	}

UINT CSmartTrackerClass::PartialGetTracks2(ActivationRecord &AR)
{
	int nx, ny, bx, wx;
	int lay;
	int itr, ibr;
	int NTracks = 0;
	float *ZLayer = T.ZLayer;
	float tz;
	int CellsInLayer = T.CellsInLayer;
	Cell *CellSpace = T.CellSpace;
	float MaxSlope = T.MaxSlope;
	float MinSlope = T.MinSlope;
	float MaxSlope2 = MaxSlope * MaxSlope;
	float aligntol2 = T.AlignTol * T.AlignTol;
	int TimeLimit = AR.TimeLimit;

	int ix, iy, iix, iiy, eix, eiy;
	int minix, maxix, miniy, maxiy;
	float Slope2, SlopeS, ISlopeS;
	float SlopeX, SlopeY, ExpX, ExpY, DirX, DirY;
	float ShadowXTol, ShadowYTol;
	float CurrDeltaX, CurrDeltaY;
	float avgds2;
	float dirtol;
	int it, ib, ir, ifound;
	float idz;

	ShadowXTol = T.DiscardShadowSigma * T.ShadowSigmaX;
	ShadowYTol = T.DiscardShadowSigma * T.ShadowSigmaY;

	float PresetSlopeX, PresetSlopeY, PresetSlopeTol;
	if (T.EnableSlopePresetting)
	{
		PresetSlopeX = T.PresetSlopeX;
		PresetSlopeY = T.PresetSlopeY;
		PresetSlopeTol = T.PresetSlopeTol;
		}
	else
	{
		PresetSlopeX = 0.0f;
		PresetSlopeY = 0.0f;
		PresetSlopeTol = T.MaxSlope;
		}


	bx = T.CellNumX / T.Processors * AR.ThreadIndex;
	nx = T.CellNumX;
	wx = (AR.ThreadIndex == T.Processors - 1) ? T.CellNumX : (T.CellNumX / T.Processors * (AR.ThreadIndex + 1));
	ny = T.CellNumY;

	for (lay = 0; lay < T.Layer; lay++)
	{		
		Cell *pCellsL = CellSpace + lay * CellsInLayer;
		for (iy = 0; iy < ny; iy++)
		{
			Cell *pCellsR = pCellsL + bx;
			for (ix = bx; ix < wx; ix++)
			{
				IntGrain *pG = pCellsR->FirstG;
				IntGrain *pGEnd = pG + pCellsR->Free;
				while (pG < pGEnd)
				{
					pG->pTrack2 = 0;
					pG->TrackLength = 0;
					pG++;
					}
				pCellsR++;
				}
			pCellsL += nx;
			}
		}

	AR.Found = 0;
	if (AR.MaxTracks <= 0) return S_OK;

	int EndLayer = AR.EndLayer;
	int StartLayer = AR.StartLayer;
	if (EndLayer >= T.Layer) EndLayer = T.Layer - 1;

	IntGrain **pTempGrains = (IntGrain **)malloc(sizeof(IntGrain *) * (EndLayer + 1));

	float avgdz = (ZLayer[StartLayer] - ZLayer[EndLayer]) / (EndLayer - StartLayer);
	float avgdz2 = avgdz * avgdz;
			
	float tsl = 10.0f * (T.NptMinV - T.NptMin01) / (T.NptMin01 - T.NptMinH);
	float tinf = (float)(T.NptMinH);
	float td = (float)(T.NptMinV - T.NptMinH);

	for (itr = 0; itr < T.TrialCount; itr++)
	{
		Trial tr = T.Trials[itr];
		if (tr.TopLayer < StartLayer || tr.BottomLayer > EndLayer) continue;
		Cell *tp = CellsInLayer * tr.TopLayer + CellSpace;
		Cell *bp = CellsInLayer * tr.BottomLayer + CellSpace;
		tz = ZLayer[tr.TopLayer];
		idz = 1.0f / (tz - ZLayer[tr.BottomLayer]);

		for (ix = bx; ix < wx; ix++)
		{
			ifound = 0;
			minix = ix - 1; if (minix < 0) minix = 0;
			maxix = ix + 1; if (maxix >= nx) maxix = nx - 1;
			for (iy = 0; iy < ny; iy++)
			{
				miniy = iy - 1; if (miniy < 0) miniy = 0;
				maxiy = iy + 1; if (maxiy >= ny) maxiy = ny - 1;
				Cell &ct = tp[iy * nx + ix];
				IntGrain *pT = ct.FirstG;
				IntGrain *pTE = ct.FirstG + ct.Free;
				for (;pT < pTE; pT++)
				{
					IntGrain gt = *pT;
					for (iix = minix; iix <= maxix; iix++)
						for (iiy = miniy; iiy <= maxiy; iiy++)
						{
							Cell &cb = bp[iiy * nx + iix];
							IntGrain *pB = cb.FirstG;
							IntGrain *pBE = cb.FirstG + cb.Free;
							for (;pB < pBE; pB++)
							{
								if (GetTickCount() > TimeLimit)
								{
									AR.Found = 0;
									return S_FALSE;
									}
								IntGrain gb = *pB;
								SlopeX = idz * (gt.Xcm - gb.Xcm);
								//if (fabs(SlopeX) >= MaxSlope) continue;
								if (fabs(SlopeX - PresetSlopeX) >= PresetSlopeTol) continue;
								SlopeY = idz * (gt.Ycm - gb.Ycm);
								//if (fabs(SlopeY) >= MaxSlope) continue;
								if (fabs(SlopeY - PresetSlopeY) >= PresetSlopeTol) continue;
								Slope2 = SlopeX * SlopeX + SlopeY * SlopeY;
								if (Slope2 < MaxSlope2)
								{
									SlopeS = sqrt(Slope2);
									if (SlopeS > 0.0f) ISlopeS = 1.0f / SlopeS;
									avgds2 = avgdz2 * Slope2;
									fastGetDirAndTol(SlopeS, ISlopeS, DirX, DirY, dirtol, aligntol2, avgds2);
									//GetDirAndTol(SlopeX, SlopeY, avgdz, &DirX, &DirY, &dirtol);
									for (ir = 0; ir < tr.TriggerCount; ir++)
									{
										int TriggerLayer = tr.Triggers[ir];
										float ldz = (tz - ZLayer[TriggerLayer]) * idz;
										float cdz = 1.0f - ldz;
										ExpX = ldz * gb.Xcm + cdz * gt.Xcm;
										ExpY = ldz * gb.Ycm + cdz * gt.Ycm;
										eix = (int)((ExpX - T.Win.Xmin) / T.DxCell);
										eiy = (int)((ExpY - T.Win.Ymin) / T.DyCell);
										IntGrain *pTrg = CellSpace[(TriggerLayer * ny + eiy) * nx + eix].FindGrain(ExpX, ExpY, DirX, DirY, dirtol, T.AlignTol);
										if (pTrg)
										{
											memset(pTempGrains, 0, T.Layer * sizeof(Grain *));
											float dz;
											int seqlength = 3;
											int availablevoids = 3 + T.Layer - T.NptMinH;
											bool DiscardShadows;

											pTempGrains[tr.TopLayer] = pT;
											pTempGrains[tr.BottomLayer] = pB;
											pTempGrains[TriggerLayer] = pTrg;

											CurrDeltaX = fabs(avgdz * SlopeX);
											CurrDeltaY = fabs(avgdz * SlopeY);
											if (DiscardShadows = true/*(CurrDeltaX >= ShadowXTol || CurrDeltaY >= ShadowYTol)*/)
											{
												for (lay = tr.TopLayer + 1; lay < TriggerLayer; lay++)
												{
													dz = ZLayer[lay] - tz;
													ExpX = dz * SlopeX + gt.Xcm;
													ExpY = dz * SlopeY + gt.Ycm;
													if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, pTempGrains[lay - 1], pTempGrains[lay + 1], ShadowXTol, ShadowYTol)) seqlength++;
													else if (--availablevoids <= 0) break;
													};
												if (availablevoids <= 0) continue;
												for (lay = TriggerLayer + 1; lay < tr.BottomLayer; lay++)
												{
													dz = ZLayer[lay] - tz;
													ExpX = dz * SlopeX + gt.Xcm;
													ExpY = dz * SlopeY + gt.Ycm;
													if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, pTempGrains[lay - 1], pTempGrains[lay + 1], ShadowXTol, ShadowYTol)) seqlength++;
													else if (--availablevoids <= 0) break;
													};
												if (availablevoids <= 0) continue;
												}
											else
											{
												for (lay = tr.TopLayer + 1; lay < TriggerLayer; lay++)
												{
													dz = ZLayer[lay] - tz;
													ExpX = dz * SlopeX + gt.Xcm;
													ExpY = dz * SlopeY + gt.Ycm;
													if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol)) seqlength++;
													else if (--availablevoids <= 0) break;
													};
												if (availablevoids <= 0) continue;
												for (lay = TriggerLayer + 1; lay < tr.BottomLayer; lay++)
												{
													dz = ZLayer[lay] - tz;
													ExpX = dz * SlopeX + gt.Xcm;
													ExpY = dz * SlopeY + gt.Ycm;
													if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol)) seqlength++;
													else if (--availablevoids <= 0) break;
													};
												if (availablevoids <= 0) continue;
												}
											Vector topv, bottomv;
											topv.X = pT->Xcm;
											topv.Y = pT->Ycm;
											topv.Z = tz;
											bottomv.X = pB->Xcm;
											bottomv.Y = pB->Ycm;
											bottomv.Z = ZLayer[tr.BottomLayer];
											for (lay = (int)tr.TopLayer - 1; lay >= 0; lay--)
											{
												dz = (bottomv.Z - topv.Z);
												float diz = 1.0f / dz;
/*
												SlopeX = (bottomv.X - topv.X) * diz;
												SlopeY = (bottomv.Y - topv.Y) * diz;
												SlopeS = sqrt(Slope2 = (SlopeX * SlopeX + SlopeY * SlopeY));
												if (SlopeS > 0.0f) ISlopeS = 1.0f / SlopeS;
												avgds2 = avgdz2 * Slope2;
												fastGetDirAndTol(SlopeS, ISlopeS, DirX, DirY, dirtol, aligntol2, avgds2);
												//GetDirAndTol(SlopeX, SlopeY, avgdz, &DirX, &DirY, &dirtol);
*/												dz = ZLayer[lay] - topv.Z;
												ExpX = dz * SlopeX + topv.X;
												ExpY = dz * SlopeY + topv.Y;
												if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, 0, DiscardShadows ? pTempGrains[lay + 1] : 0, ShadowXTol, ShadowYTol))
												{
/*													topv.X = pTempGrains[lay]->Xcm;
													topv.Y = pTempGrains[lay]->Ycm;
													topv.Z = ZLayer[lay];
*/													seqlength++;
													}
												else if (--availablevoids <= 0) break;
												};
											if (availablevoids <= 0) continue;
											for (lay = (int)tr.BottomLayer + 1; lay <= EndLayer; lay++)
											{
												dz = (bottomv.Z - topv.Z);
												float diz = 1.0f / dz;
/*
												SlopeX = (bottomv.X - topv.X) * diz;
												SlopeY = (bottomv.Y - topv.Y) * diz;
												SlopeS = sqrt(Slope2 = (SlopeX * SlopeX + SlopeY * SlopeY));
												if (SlopeS > 0.0f) ISlopeS = 1.0f / SlopeS;
												avgds2 = avgdz2 * Slope2;
												fastGetDirAndTol(SlopeS, ISlopeS, DirX, DirY, dirtol, aligntol2, avgds2);
												//GetDirAndTol(SlopeX, SlopeY, avgdz, &DirX, &DirY, &dirtol);
*/												dz = ZLayer[lay] - topv.Z;
												ExpX = dz * SlopeX + topv.X;
												ExpY = dz * SlopeY + topv.Y;
												if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, DiscardShadows ? pTempGrains[lay - 1] : 0, 0, ShadowXTol, ShadowYTol))
												{
/*													bottomv.X = pTempGrains[lay]->Xcm;
													bottomv.Y = pTempGrains[lay]->Ycm;
													bottomv.Z = ZLayer[lay];
*/													seqlength++;
													}
												else if (--availablevoids <= 0) break;
												};
											//if (availablevoids <= 0) continue;
											if ((float)seqlength > (tinf + td / (1.0f + tsl * SlopeS)))
											{

												if (T.CheckGrainSpacing)
												{
													int fillcount;
													float ndirtol = sqrt(avgds2/* * 0.25*/ + aligntol2);
													for (lay = fillcount = 0; lay <= EndLayer; lay++)
														if (pTempGrains[lay])
														{
															dz = ZLayer[lay] - topv.Z;
															float dx = dz * SlopeX + topv.X - pTempGrains[lay]->Xcm;
															float dy = dz * SlopeY + topv.Y - pTempGrains[lay]->Ycm;
															if (fabs(dx * DirX + dy * DirY) < ndirtol/* &&
																fabs(dx * DirY - dy * DirX) < T.AlignTol*/)
																fillcount++;
															}
													if ((float)fillcount <= (tinf + td / (1.0f + tsl * SlopeS))) break;
													}
												

												if (AR.Found < AR.MaxTracks)
												{
													Track2 &N = AR.pSpace[AR.Found++];
													int i, j;
													for (i = j = 0; i <= EndLayer; i++)
														if (pTempGrains[i])
														{
															IntTrackGrain *pIG = ((IntTrackGrain *)N.pGrains) + j++;
															pIG->T.pG = pTempGrains[i];
															pIG->T.Z = ZLayer[i];
															}
													N.Field = (itr << 24) + (ix << 16) + ifound;//AR.Found;
													N.Valid = true;
													N.Grains = seqlength;
													ifound++;
													}
												break;
												}
											}
										}
									}
								}
							}
					}
				}
			}
		}
	free(pTempGrains);
	return S_OK;
	};


UINT CSmartTrackerClass::TrackerThreadHook(void *Context)
{
	ActivationRecord *pAR = (ActivationRecord *)Context;
	HANDLE HEvsStart[2], HEvsReset[2];
	HEvsStart[0] = HEvsReset[0] = pAR->pThis->HTerminate;
	HEvsStart[1] = pAR->pThis->HStart;
	HEvsReset[1] = pAR->pThis->HReset;
	while (WaitForMultipleObjects(2, HEvsStart, FALSE, INFINITE) != WAIT_OBJECT_0)
	{
		pAR->pThis->PartialGetTracks2(*pAR);
		SetEvent(pAR->HFinished);
		if (WaitForMultipleObjects(2, HEvsReset, FALSE, INFINITE) == WAIT_OBJECT_0) break;
		SetEvent(pAR->HFinished);
		}
	_endthreadex(S_OK);
	return S_OK;
	};


HRESULT CSmartTrackerClass::GetTracks2(Track2 *pSpace, int *pMaxNumber, int StartLayer, int EndLayer)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	HANDLE HEvs[MAX_PROCESSORS];
	int p, i, j, k, maxtracksperthread = *pMaxNumber / T.Processors;
	int found, seqlength;
	Grain *pTemp;
	int TempF, TempG;
	bool TempV;

	if (T.ShadowSigmaMeasures > 0)
	{
		T.ShadowSigmaX = T.ShadowSigmaXAccumulator / T.ShadowSigmaMeasures;
		T.ShadowSigmaY = T.ShadowSigmaYAccumulator / T.ShadowSigmaMeasures;
		}
	else	
		T.ShadowSigmaX = T.ShadowSigmaY = 0.0f;
	
	int TimeLimit = GetTickCount() + T.MaxTrackingTime;
	for (p = 0; p < T.Processors; p++)
	{
		ThreadInfo[p].MaxTracks = maxtracksperthread;
		ThreadInfo[p].pSpace = pSpace + p * maxtracksperthread;
		HEvs[p] = ThreadInfo[p].HFinished;
		ThreadInfo[p].StartLayer = StartLayer;
		ThreadInfo[p].EndLayer = EndLayer;
		ThreadInfo[p].TimeLimit = TimeLimit;
		}
	ResetEvent(HReset);
	SetEvent(HStart);
	PartialGetTracks2(ThreadInfo[0]);

	if (T.Processors > 1) WaitForMultipleObjects(T.Processors - 1, HEvs + 1, TRUE, INFINITE);
	ResetEvent(HStart);
	SetEvent(HReset);
	if (T.Processors > 1) WaitForMultipleObjects(T.Processors - 1, HEvs + 1, TRUE, INFINITE);

	if (GetTickCount() > TimeLimit) 
	{
		*pMaxNumber = 0;
		return S_FALSE;
		}

	for (p = 0; p < T.Processors; p++)
		for (i = 0; i < ThreadInfo[p].Found; i++)
		{
			Track2 &K = ThreadInfo[p].pSpace[i];
			seqlength = K.Grains;
			for (j = 0; (j < seqlength) && ((IntTrackGrain *)K.pGrains)[j].T.pG->TrackLength < seqlength; j++);
	
			if (j < seqlength) 
			{
				K.Valid = false;
				K.Grains = 0;
				continue;
				}
			for (j = 0; j < seqlength; j++)
			{
				IntTrackGrain *pIG = ((IntTrackGrain *)K.pGrains) + j;
				if (pIG->T.pG->pTrack2)
				{
					Track2 &N = *pIG->T.pG->pTrack2;
					for (k = 0; k < N.Grains; k++)
					{
						IntTrackGrain *pIJ = ((IntTrackGrain *)N.pGrains) + k;
						pIJ->T.pG->pTrack2 = 0;
						pIJ->T.pG->TrackLength = 0;
						}
					N.Valid = false;
					N.Grains = 0;
					}
				}

			for (j = 0; j < seqlength; j++)
			{
				IntTrackGrain *pIG = ((IntTrackGrain *)K.pGrains) + j;
				pIG->T.pG->pTrack2 = &K;
				pIG->T.pG->TrackLength = seqlength;
				}
			K.Valid = true;
			}

	found = ThreadInfo[0].Found;
	pTemp = (Grain *)malloc(sizeof(Grain) * T.LayerNum);
	for (p = 1; p < T.Processors; p++)
		for (i = 0; i < ThreadInfo[p].Found; i++)
		{
			TempF = ThreadInfo[p].pSpace[i].Field;
			TempG = ThreadInfo[p].pSpace[i].Grains;
			//if (TempV = ThreadInfo[p].pSpace[i].Valid)
			TempV = ThreadInfo[p].pSpace[i].Valid;
			memcpy(pTemp, ThreadInfo[p].pSpace[i].pGrains, sizeof(Grain) * TempG);
			for (j = 0; (j < found) && (pSpace[j].Field < TempF); j++);
			for (k = found; k > j; k--)
			{
				pSpace[k].Field = pSpace[k - 1].Field;
				pSpace[k].Grains = pSpace[k - 1].Grains;
				//if (pSpace[k].Valid = pSpace[k - 1].Valid)
				pSpace[k].Valid = pSpace[k - 1].Valid;
				memcpy(pSpace[k].pGrains, pSpace[k - 1].pGrains, sizeof(Grain) * pSpace[k].Grains);
				}
			pSpace[j].Field = TempF;
			pSpace[j].Grains = TempG;
			//if (pSpace[j].Valid = TempV)
			pSpace[j].Valid = TempV;
			memcpy(pSpace[j].pGrains, pTemp, sizeof(Grain) * TempG);
			found++;
			}
	free(pTemp);


/*
	found = ThreadInfo[0].Found;
	pTemp = (Grain *)malloc(sizeof(Grain) * T.LayerNum);
	for (p = 1; p < T.Processors; p++)
		for (i = 0; i < ThreadInfo[p].Found; i++)
		{
			TempF = ThreadInfo[p].pSpace[i].Field;
			TempG = ThreadInfo[p].pSpace[i].Grains;
			memcpy(pTemp, ThreadInfo[p].pSpace[i].pGrains, sizeof(Grain) * T.LayerNum);
			for (j = 0; (j < found) && (pSpace[j].Field < ThreadInfo[p].pSpace[i].Field); j++);
			for (k = found; k > j; k--)
			{
				pSpace[k].Field = pSpace[k - 1].Field;
				pSpace[k].Grains = pSpace[k - 1].Grains;
				//pTemp = pSpace[k].pGrains;
				memcpy(pSpace[k].pGrains, pSpace[k - 1].pGrains, sizeof(Grain) * T.LayerNum);
				//pSpace[k - 1].pGrains = pTemp;
				}
			pSpace[j].Field = TempF;
			pSpace[j].Grains = TempG;
			memcpy(pSpace[j].pGrains, pTemp, sizeof(Grain) * T.LayerNum);
			found++;
			}
	free(pTemp);

	*pMaxNumber = found;
	for (i = 0; i < found; i++)
	{
		seqlength = pSpace[i].Grains;
		for (j = 0; (j < seqlength) && ((IntTrackGrain *)pSpace[i].pGrains)[j].T.pG->TrackLength < seqlength; j++);

		if (j < seqlength) 
		{
			pSpace[i].Valid = false;
			continue;
			}
		for (j = 0; j < seqlength; j++)
		{
			IntTrackGrain *pIG = ((IntTrackGrain *)pSpace[i].pGrains) + j;
			if (pIG->T.pG->pTrack2)
			{
				Track2 &N = *pIG->T.pG->pTrack2;
				for (k = 0; k < N.Grains; k++)
				{
					IntTrackGrain *pIJ = ((IntTrackGrain *)N.pGrains) + k;
					pIJ->T.pG->pTrack2 = 0;
					pIJ->T.pG->TrackLength = 0;
					}
				N.Valid = false;
				N.Grains = 0;
				}
			}

		for (j = 0; j < seqlength; j++)
		{
			IntTrackGrain *pIG = ((IntTrackGrain *)pSpace[i].pGrains) + j;
			pIG->T.pG->pTrack2 = pSpace + i;
			pIG->T.pG->TrackLength = seqlength;
			}
		pSpace[i].Valid = true;
		}
*/
	*pMaxNumber = FinalizeTracks(found, pSpace);

	return S_OK;
	}

// INTERNAL FUNCTIONS

void CSmartTrackerClass::InitTrackerData()
{
	SySalConfig Temp = {0, 0, 0};
	GetData(Temp, ConfigDataN, ConfigDataQDI, &T, true);

	T.GrainSpace = 0;
	T.ZLayer = 0;
	T.LayerGrains = 0;
	T.CellSpace = 0;
	T.EnableSlopePresetting = false;
	T.PresetSlopeX = 0.0f;
	T.PresetSlopeY = 0.0f;
	T.PresetSlopeTol = T.MaxSlope;
}

int CSmartTrackerClass::GetCell(float Xp, float Yp)
{
	int Icl;
	if ((Xp < T.Win.Xmin) || (Xp >= T.Win.Xmax) ||
		(Yp < T.Win.Ymin) || (Yp >= T.Win.Ymax)) return -1;
	Icl = ((int)((Yp - T.Win.Ymin) / T.DyCell)) * T.CellNumX +
		(int)((Xp - T.Win.Xmin) / T.DxCell);
	if ((Icl >= 0) && (Icl < T.CellsInLayer)) return Icl;
	return -1;
	};

IntGrain *Cell::FindGrain(float x, float y, float dirx, float diry, float dirtol, float normtol)
{	
	IntGrain *pBest = 0;
	int i;
	float bestnormdist, normdist;
	float dx, dy;
	IntGrain *pStart = FirstG;
	IntGrain *pEnd = FirstG + Free;
	float reddirtol = dirtol * 1.5f;
	for (IntGrain *pScan = pStart; pScan < pEnd; pScan++)
		if (fabs(dx = (pScan->Xcm - x)) <= reddirtol)
			if (fabs(dy = (pScan->Ycm - y)) <= reddirtol)
				if ((normdist = fabs(dy * dirx - dx * diry)) < normtol)
					if (!pBest || normdist < bestnormdist)
						if (fabs(dx * dirx + dy * diry) < dirtol)
						{
							bestnormdist = normdist;
							pBest = pScan;
							};
	return pBest;
	};

IntGrain *Cell::FindGrainNoShadow(float x, float y, float dirx, float diry, float dirtol, float normtol, IntGrain *pTopShadow, IntGrain *pBottomShadow, float xshadowtol, float yshadowtol)
{
	IntGrain *pBest = 0;
	int i;
	float bestnormdist = normtol, normdist;
	float dx, dy;
	IntGrain *pStart = FirstG;
	IntGrain *pEnd = FirstG + Free;
	float reddirtol = dirtol * 1.5f;
	for (IntGrain *pScan = pStart; pScan < pEnd; pScan++)
		if (fabs(dx = (pScan->Xcm - x)) <= reddirtol)
			if (fabs(dy = (pScan->Ycm - y)) <= reddirtol)
				if ((normdist = fabs(dy * dirx - dx * diry)) < bestnormdist)
				{
					if (pTopShadow && fabs(pTopShadow->Xcm - pScan->Xcm) < xshadowtol && fabs(pTopShadow->Ycm - pScan->Ycm) < yshadowtol) continue;
					if (pBottomShadow && fabs(pBottomShadow->Xcm - pScan->Xcm) < xshadowtol && fabs(pBottomShadow->Ycm - pScan->Ycm) < yshadowtol) continue;
					if (normdist < bestnormdist)
						if (fabs(dx * dirx + dy * diry) < dirtol)
						{
							bestnormdist = normdist;
							pBest = pScan;
							};
					}
	return pBest;
	};

void CSmartTrackerClass::InsertNewTrack(IntGrain **pTempGrains, int Layers, int SequenceLength, Track *pTracks, int &NTracks)
{
	int i, j;
	for (i = 0; i < Layers; i++)
		if (pTempGrains[i] && pTempGrains[i]->TrackLength >= SequenceLength) return;
	for (i = 0; i < Layers; i++)
		if (pTempGrains[i] && pTempGrains[i]->pTrack)
		{
			Track &N = *pTempGrains[i]->pTrack;
			for (j = 0; j < N.PointsN; j++)
			{
				IntGrain *pG = ((IntTrackVector *)N.pPoints)[j].T.pG;
				pG->TrackLength = 0;
				pG->pTrack = 0;
				}
			N.Valid = false;
			N.PointsN = 0;
			}
	Track &N = pTracks[NTracks++];
	for (i = j = 0; i < Layers; i++)
		if (pTempGrains[i])
		{
			IntTrackVector *pIG = ((IntTrackVector *)N.pPoints) + j++;
			pIG->T.pG = pTempGrains[i];
			pIG->T.pG->pTrack = &N;
			pIG->T.pG->TrackLength = SequenceLength;
			pIG->T.Z = T.ZLayer[i];
			}
	N.Valid = true;
	N.PointsN = SequenceLength;
};

void CSmartTrackerClass::InsertNewTrack(IntGrain **pTempGrains, int Layers, int SequenceLength, Track2 *pTracks, int &NTracks)
{
	int i, j;
	for (i = 0; i < Layers; i++)
		if (pTempGrains[i] && pTempGrains[i]->TrackLength >= SequenceLength) return;
	for (i = 0; i < Layers; i++)
		if (pTempGrains[i] && pTempGrains[i]->pTrack2)
		{
			Track2 &N = *pTempGrains[i]->pTrack2;
			for (j = 0; j < N.Grains; j++)
			{
				IntGrain *pG = ((IntTrackGrain *)N.pGrains)[j].T.pG;
				pG->TrackLength = 0;
				pG->pTrack2 = 0;
				}
			N.Valid = false;
			N.Grains = 0;
			}
	Track2 &N = pTracks[NTracks++];
	for (i = j = 0; i < Layers; i++)
		if (pTempGrains[i])
		{
			IntTrackGrain *pIG = ((IntTrackGrain *)N.pGrains) + j++;
			pIG->T.pG = pTempGrains[i];
			pIG->T.pG->pTrack2 = &N;
			pIG->T.pG->TrackLength = SequenceLength;
			pIG->T.Z = T.ZLayer[i];
			}
	N.Valid = true;
	N.Grains = SequenceLength;
};

int CSmartTrackerClass::FinalizeTracks(int ntracks, Track *pspace)
{
	int i, j, k;
	for (i = j = 0; i < ntracks; i++)
		if (pspace[i].Valid)
		{
			Track &O = pspace[i];
			Track &N = pspace[j++];
			N.PointsN = O.PointsN;
			O.Valid = false;
			N.Valid = true;
			for (k = 0; k < N.PointsN; k++)
			{
				IntGrain *pG = ((IntTrackVector *)O.pPoints)[k].T.pG;
				N.pPoints[k].Z = ((IntTrackVector *)O.pPoints)[k].T.Z;
				N.pPoints[k].X = pG->Xcm;
				N.pPoints[k].Y = pG->Ycm;
				}
			}
	return j;
	}

int CSmartTrackerClass::FinalizeTracks(int ntracks, Track2 *pspace)
{
	int i, j, k, a, ta;
	float dsx, dsy;
	if (T.Layer > 1)
	{
		dsx = T.DispX / (T.ZLayer[0] - T.ZLayer[T.Layer - 1]);
		dsy = T.DispY / (T.ZLayer[0] - T.ZLayer[T.Layer - 1]);
		}
	else dsx = dsy = 0.0f;
	for (i = j = 0; i < ntracks; i++)
		if (pspace[i].Valid)
		{
			Track2 &O = pspace[i];
			Track2 &N = pspace[j++];
			N.Grains = O.Grains;
			O.Valid = false;
			N.Valid = true;
			a = 0;
			for (k = 0; k < N.Grains; k++)
			{
				IntGrain *pG = ((IntTrackGrain *)O.pGrains)[k].T.pG;
				a += (ta = pG->Area);
				float dz = (N.pGrains[k].Z = ((IntTrackGrain *)O.pGrains)[k].T.Z) - T.ZLayer[0];
				N.pGrains[k].X = pG->Xcm + dsx * dz;
				N.pGrains[k].Y = pG->Ycm + dsy * dz;				
				N.pGrains[k].Area = ta;
				}
			N.AreaSum = a;
			}
	return j;
	}

void CSmartTrackerClass::PutData(SySalConfig *pConfig, ConfigData *pC)
{
	::PutData(*pConfig, ConfigDataN, ConfigDataQDI, pC);
}

#include "..\Common\Config2.cpp"

