// SmartTrackerClass.cpp : Implementation of CSmartTrackerClass
#include "stdafx.h"
#include "SmartTracker8.h"
#include "SmartTrackerClass.h"
#include <math.h>
#include <stdio.h>
#include "EditConfig.h"
#include <process.h>

/////////////////////////////////////////////////////////////////////////////
// CSmartTrackerClass

char *CSmartTrackerClass::pHelpPath = 0;

const int ConfigDataN = 25 + (3 + MAX_TRIGGERS) * MAX_TRIALS;

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
	
	{"InitialMultiplicity",		ST_INT,		STRUCT_OFFSET(TrackerData, InitialMultiplicity),	"2"},	
	{"AllowOverlap",			ST_INT,		STRUCT_OFFSET(TrackerData, AllowOverlap),			"1"},	
	{"DeltaZMultiplier",		ST_FLOAT,	STRUCT_OFFSET(TrackerData, DeltaZMultiplier),		"1.0"},	

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

	if (T.GrainSpace) CoTaskMemFree(T.GrainSpace);
	if (!(T.GrainSpace = (IntGrain *)CoTaskMemAlloc( sizeof(IntGrain) * T.MaxGrains)))
		return S_FALSE;
	if (T.ZLayer) CoTaskMemFree(T.ZLayer);
	if (!(T.ZLayer = (float *)CoTaskMemAlloc( sizeof(float) * T.LayerNum)))
   		return S_FALSE;
	if (T.LayerGrains) CoTaskMemFree(T.LayerGrains);
	if (!(T.LayerGrains = (IntGrain **)CoTaskMemAlloc( sizeof(IntGrain *) * T.LayerNum)))
   		return S_FALSE;
	T.CellsInLayer = T.CellNumX * T.CellNumY;
	if (T.CellSpace) CoTaskMemFree(T.CellSpace);
	if (!(T.CellSpace = (Cell *)CoTaskMemAlloc( sizeof(Cell) * (T.CellsInLayer)*(T.LayerNum))))
   		return S_FALSE;
	if (T.pDeltaData) CoTaskMemFree(T.pDeltaData);
	if (!(T.pDeltaData = (float *)CoTaskMemAlloc( (4 * sizeof(float) + sizeof(IntCluster **)) * T.MaxGrains)))
		return S_FALSE;
	else
	{
		T.pX = T.pDeltaData;
		T.pY = T.pX + T.MaxGrains;
		T.pDX = T.pY + T.MaxGrains;
		T.pDY = T.pDX + T.MaxGrains;
		T.pReplicas = (IntCluster **)(void *)(T.pDY + T.MaxGrains);
		}

	if (!ResetDeltaHisto()) return S_FALSE;
	SetEvent(HTerminate);
	int i;
	for (i = 1; i < MaxProcessors; i++)
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
	ConfigMaxProcessors_backup = T.Processors;
	if (T.Processors == 0 || T.Processors > MaxProcessors) T.Processors = MaxProcessors;
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
	ConfigData C = T;
	C.Processors = ConfigMaxProcessors_backup;
	if (::PutData(*pConfig, ConfigDataN, ConfigDataQDI, &C) != ConfigDataN) return S_FALSE;
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
	
	strncpy(name, "Smart Tracker 8.6", SYSAL_MAX_CONN_NAME_LEN);
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

// ISySalObject2
STDMETHODIMP CSmartTrackerClass::SetConfigManagerInterface(ConfigManagerInterface *pCMI)
{	
	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::GetCLSID(CLSID *pCLSID)
{
	*pCLSID = CLSID_SmartTracker8;
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
	T.Side = 1;
	T.TotalLX = T.TotalLY = 0.0f;
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
		T.ViewCenterX = Spec.Width * Spec.PixelToMicronX * 0.5;
		T.ViewCenterY = Spec.Height * Spec.PixelToMicronY * 0.5;
		if (!ResetDeltaHisto()) return S_FALSE;
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
	double L0X = 0.0, L1X = 0.0, L0Y = 0.0, L1Y = 0.0;
	double AvgLX = 0.0, AvgLY = 0.0;
	float *pX = T.pX;
	float *pY = T.pY;
	float *pDX = T.pDX;
	float *pDY = T.pDY;
	IntCluster **pReplicas = T.pReplicas;
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

	static int run = 0;
	run++;

	int DeltaBins = T.DeltaBinsX * T.DeltaBinsY;
	int MaxHisto, MaxBin;
	for (Nc = 0; Nc < DeltaBins; T.pDeltaHisto2d[Nc++] = 0);

/*	FILE *fsmtg = fopen("c:\\acq\\smt8g.txt", "a+t");
	FILE *fsmtd = fopen("c:\\acq\\smt8d.txt", "a+t");
*/

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
						CX = PClus->X/* + DispX*/;
						CY = PClus->Y/* + DispY*/;
						IntGrain *pRep = PCell->FirstG;
						IntGrain *pEnd = pRep + PCell->Free;
						while (pRep < pEnd)
						{
							if (fabs(DX = (pRep->Xcm - CX)) < ReplicaRadius && fabs(DY = (pRep->Ycm - CY)) < ReplicaRadius) 
							{
								*(IntGrain **)(void *)&PClus->Inertia.IYY = pRep;
								pX[ReplicaCount] = CX;
								pY[ReplicaCount] = CY;
								pDX[ReplicaCount] = DX;
								pDY[ReplicaCount] = DY;
								pReplicas[ReplicaCount] = PClus;

								CurrDispX += DX;
								CurrDispSigmaX += DX * DX;
								CurrDispY += DY;
								CurrDispSigmaY += DY * DY;

								T.pDeltaHisto2d[((int)floor(DY / T.DeltaDY + 0.5) + T.DeltaBinsY / 2) * T.DeltaBinsX + ((int)floor(DX / T.DeltaDX + 0.5) + T.DeltaBinsX / 2)]++;
/*
								fprintf(fsmtg, "%d %d %d %f %f %f %f\n", run, Layer, ReplicaCount, PClus->X, PClus->Y, DX, DY);
*/								
								ReplicaCount++;								
								break;
								}
							pRep++;
							}
						}
					};
				};
			};
		MaxBin = DeltaBins / 2 + T.DeltaBinsX / 2;
		for (Nc = MaxHisto = MaxBin = 0; Nc < DeltaBins; Nc++)
			if (T.pDeltaHisto2d[Nc] > MaxHisto)
			{
				MaxHisto = T.pDeltaHisto2d[Nc];
				MaxBin = Nc;
				};

		if (MaxHisto)
			if ((MaxHisto = T.pDeltaHisto2d[MaxBin] + T.pDeltaHisto2d[MaxBin + 1] + T.pDeltaHisto2d[MaxBin - 1] + 
				T.pDeltaHisto2d[MaxBin + T.DeltaBinsX] + T.pDeltaHisto2d[MaxBin + 1 + T.DeltaBinsX] + T.pDeltaHisto2d[MaxBin - 1 + T.DeltaBinsX] + 
				T.pDeltaHisto2d[MaxBin - T.DeltaBinsX] + T.pDeltaHisto2d[MaxBin + 1 - T.DeltaBinsX] + T.pDeltaHisto2d[MaxBin - 1 - T.DeltaBinsX]) >= T.MinReplicas)
		{
			DX = ((MaxBin % T.DeltaBinsX) - T.DeltaBinsX / 2) * T.DeltaDX;
			DY = ((MaxBin / T.DeltaBinsX) - T.DeltaBinsY / 2) * T.DeltaDY;
			CurrDispX = (DX * (T.pDeltaHisto2d[MaxBin] + T.pDeltaHisto2d[MaxBin + T.DeltaBinsX] + T.pDeltaHisto2d[MaxBin - T.DeltaBinsX]) + 
				(DX + T.DeltaDX) * (T.pDeltaHisto2d[MaxBin + 1] + T.pDeltaHisto2d[MaxBin + T.DeltaBinsX + 1] + T.pDeltaHisto2d[MaxBin - T.DeltaBinsX + 1]) + 
				(DX - T.DeltaDX) * (T.pDeltaHisto2d[MaxBin - 1] + T.pDeltaHisto2d[MaxBin + T.DeltaBinsX - 1] + T.pDeltaHisto2d[MaxBin - T.DeltaBinsX - 1])) / MaxHisto;

			CurrDispY = (DY * (T.pDeltaHisto2d[MaxBin] + T.pDeltaHisto2d[MaxBin + 1] + T.pDeltaHisto2d[MaxBin - 1]) + 
				(DY + T.DeltaDY) * (T.pDeltaHisto2d[MaxBin + T.DeltaBinsX] + T.pDeltaHisto2d[MaxBin + T.DeltaBinsX + 1] + T.pDeltaHisto2d[MaxBin + T.DeltaBinsX - 1]) + 
				(DY - T.DeltaDY) * (T.pDeltaHisto2d[MaxBin - T.DeltaBinsX] + T.pDeltaHisto2d[MaxBin - T.DeltaBinsX + 1] + T.pDeltaHisto2d[MaxBin - T.DeltaBinsX - 1])) / MaxHisto;

			int rsp, rv;
			double SumPx = 0.0, SumX = 0.0, SumX2 = 0.0, SumXPx = 0.0, DenX = 0.0;
			double SumPy = 0.0, SumY = 0.0, SumY2 = 0.0, SumYPy = 0.0, DenY = 0.0;
			double V, W;
			for (rsp = rv = 0; rsp < ReplicaCount; rsp++)
			{
				if (fabs(pDX[rsp] - CurrDispX) < T.DeltaDX && fabs(pDY[rsp] - CurrDispY) < T.DeltaDY)
				{
					rv++;
					V = pX[rsp];
					W = pDX[rsp];
					SumX += V;
					SumX2 += V * V;
					SumPx += W;
					SumXPx += V * W;
					V = pY[rsp];
					W = pDY[rsp];
					SumY += V;
					SumY2 += V * V;
					SumPy += W;
					SumYPy += V * W;
					}
				}
			DenX = 1. / (rv * SumX2 - SumX * SumX);
			L0X = (SumPx * SumX2 - SumX * SumXPx) * DenX;
			L1X = (rv * SumXPx - SumX * SumPx) * DenX;
			DenY = 1. / (rv * SumY2 - SumY * SumY);
			L0Y = (SumPy * SumY2 - SumY * SumYPy) * DenY;
			L1Y = (rv * SumYPy - SumY * SumPy) * DenY;

			SumPx = 0.0; SumX = 0.0; SumX2 = 0.0; SumXPx = 0.0; DenX = 0.0;
			SumPy = 0.0; SumY = 0.0; SumY2 = 0.0; SumYPy = 0.0; DenY = 0.0;
			for (rsp = rv = 0; rsp < ReplicaCount; rsp++)
			{
				if (fabs(pDX[rsp] - (pX[rsp] * L1X + L0X)) < T.DeltaDX && fabs(pDY[rsp] - (pY[rsp] * L1Y + L0Y)) < T.DeltaDY)
				{
					rv++;
					V = pX[rsp];
					W = pDX[rsp];
					SumX += V;
					SumX2 += V * V;
					SumPx += W;
					SumXPx += V * W;
					V = pY[rsp];
					W = pDY[rsp];
					SumY += V;
					SumY2 += V * V;
					SumPy += W;
					SumYPy += V * W;
					}
				else pReplicas[rsp] = 0;
				}
			DenX = 1. / (rv * SumX2 - SumX * SumX);
			L0X = (SumPx * SumX2 - SumX * SumXPx) * DenX;
			L1X = (rv * SumXPx - SumX * SumPx) * DenX;
			DenY = 1. / (rv * SumY2 - SumY * SumY);
			L0Y = (SumPy * SumY2 - SumY * SumYPy) * DenY;
			L1Y = (rv * SumYPy - SumY * SumPy) * DenY;
			AvgLX = L0X + L1X * T.ViewCenterX;
			AvgLY = L0Y + L1Y * T.ViewCenterY;
			L1X += 1.0;
			L1Y += 1.0;
			T.TotalLX += AvgLX;
			T.TotalLY += AvgLY;
			for (rsp = 0; rsp < ReplicaCount; rsp++)
				if (pReplicas[rsp]) 
					pReplicas[rsp]->Area = -pReplicas[rsp]->Area;
/*
			T.DispX = (DispX += CurrDispX);
			T.DispY = (DispY += CurrDispY);
*/
/*
			fprintf(fsmtd, "%d %d %f %f %d %d %f %f %f %f\n", run, Layer, CurrDispX, CurrDispY, MaxHisto, MaxBin, DX, DY, T.DeltaDX, T.DeltaDY);
*/				
/*
			fprintf(fsmtd, "%d %d %f %f %f %d %d %f %f %f %f\n", run, Layer, Z - T.ZLayer[Layer - 1], CurrDispX, CurrDispY, MaxHisto, MaxBin, L0X, L1X, L0Y, L1Y);
*/				

			CurrDispSigmaX = T.DeltaDX * 0.5f;
			CurrDispSigmaY = T.DeltaDY * 0.5f;
			T.ShadowSigmaMeasures++;
			T.ShadowSigmaXAccumulator += CurrDispSigmaX;
			T.ShadowSigmaYAccumulator += CurrDispSigmaY;
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

/*	fclose(fsmtg);
	fclose(fsmtd);
*/
	T.LayerGrains[Layer] = PGrain = T.GrainSpace + T.NumGrains;
	PGrainEnd = T.GrainSpace + MaxGrains;
	IntCluster *NextFree;

	float pcx, pcy;
	IntGrain *pig;
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
//						PGrain->Xcm = PClus->X + DispX;
//						PGrain->Ycm = PClus->Y + DispY;
						NextFree = PClus->NextFree;
						if (PClus->Area < 0)
						{							
							PGrain->Xcm = (pcx = PClus->X) * L1X + L0X;
							PGrain->Ycm = (pcy = PClus->Y) * L1Y + L0Y;
							pig = *((IntGrain **)(void *)(&PClus->Inertia.IYY));
							PGrain->Area = -PClus->Area;
							PGrain->Xunc = pcx + AvgLX; 
							PGrain->Yunc = pcy + AvgLY;
							PGrain->ChainLinkNumber = 1 + (PGrain->pChainHead = pig)->ChainLinkNumber;
							}
						else
						{
							PGrain->Xcm = PClus->X + AvgLX;
							PGrain->Ycm = PClus->Y + AvgLY;
							PGrain->Area = PClus->Area;							
							PGrain->ChainLinkNumber = 0;
							PGrain->pChainHead = 0;
							PGrain->Xunc = PGrain->Xcm;
							PGrain->Yunc = PGrain->Ycm;
							}
						//PClus = PClus->NextFree;
						PClus = NextFree;
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
						NextFree = PClus->NextFree;
/*						if (PGrain->Area <= 0)
						{
							::MessageBox(0, "Here - Invalid grain area!", "Debug Info", MB_OK);
							volatile int uy = 0;
							uy = 1;
							}*/
						//PClus = PClus->NextFree;
						PClus = NextFree;
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

void CSmartTrackerClass::CorrectChains()
{
	int CellsInLayer = T.CellsInLayer;
	Cell *CellSpace = T.CellSpace;
	Cell *pCell, *pCellBase, *pCellEnd;
	IntGrain *pG, *pGE, *pC, *pNC;	
	int lay, n;	
	float DX, DY;
	for ((lay = T.Layer - 1), (pCellBase = CellSpace + lay * CellsInLayer), (pCellEnd = pCellBase + CellsInLayer); lay >= 0; (lay--), (pCellEnd = pCellBase), (pCellBase -= CellsInLayer))	
		for (pCell = pCellBase; pCell < pCellEnd; pCell++)
			if (pCell->Free)
				for ((pG = pCell->FirstG), (pGE = pG + pCell->Free); pG < pGE; pG++)
				{
					if (pG->pChainHead)
					{
						DX = pG->Xcm - pG->Xunc;
						DY = pG->Ycm - pG->Yunc;
						pC = pG->pChainHead;
						while (pC)
						{
							DX += (pC->Xcm - pC->Xunc);
							DY += (pC->Ycm - pC->Yunc);
							pC = pC->pChainHead;
							}
						n = pG->ChainLinkNumber + 1;
						DX /= n;
						DY /= n;
						pC = pG;
						while (pC)
						{
							pC->Xcm -= DX;
							pC->Ycm -= DY;
							pNC = pC->pChainHead;
							pC->pChainHead = 0;
							pC->ChainLinkNumber = 0;
							pC = pNC;
							}
						}
					}
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
	T.PresetSlopeX = SX;
	T.PresetSlopeY = SY;
	T.PresetSlopeAccX = AccX;
	T.PresetSlopeAccY = AccY;
	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::EnableSlopePresetting(boolean SlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	T.PresetSlope = SlPresEnable;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetSlopePresetStatus(boolean *pSlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pSlPresEnable = T.PresetSlope;
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
		*pdirtol = T.AlignTol + avgdz * slope2;
	}
};

#define fastGetDirAndTol(SlopeS, ISlopeS, DirX, DirY, dirtol) \
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
		dirtol = T.AlignTol + SlopeS * avgdz * T.DeltaZMultiplier; \
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

int CSmartTrackerClass::FindGrains(float expx, float expy, Cell *pCellLayer, float dirx, float diry, float dirtol, IntGrain **pGrainDest, int maxmult)
{

#define MAXMULT 16

	IntGrain *pOut[MAXMULT];
	float Dist[MAXMULT];
	if (maxmult > MAXMULT) maxmult = MAXMULT;
	int i;
	for (i = 0; i < maxmult; Dist[i++] = T.AlignTol);
	float fix, fiy;
	int eix = (int)(fix = ((expx - T.Win.Xmin) / T.DxCell));
	if (eix < 0 || eix >= T.CellNumX) return 0;
	int eiy = (int)(fiy = ((expy - T.Win.Ymin) / T.DyCell));
	if (eiy >= 0 && eiy < T.CellNumY)
	{
		pCellLayer[eiy * T.CellNumX + eix].FindGrains(expx, expy, dirx, diry, dirtol, T.AlignTol, pOut, Dist, maxmult);
		fix -= (0.5f + eix);
		fiy -= (0.5f + eiy);
		if (fabs(fix) >= fabs(fiy))
		{
			if (fix < 0.0f && eix > 0)
				pCellLayer[eiy * T.CellNumX + eix - 1].FindGrains(expx, expy, dirx, diry, dirtol, T.AlignTol, pOut, Dist, maxmult);
			else if (fix > 0.0f && eix < (T.CellNumX - 1))
				pCellLayer[eiy * T.CellNumX + eix + 1].FindGrains(expx, expy, dirx, diry, dirtol, T.AlignTol, pOut, Dist, maxmult);
			}
		else
		{
			if (fiy < 0.0f && eiy > 0)
				pCellLayer[(eiy - 1) * T.CellNumX + eix].FindGrains(expx, expy, dirx, diry, dirtol, T.AlignTol, pOut, Dist, maxmult);
			else if (fiy > 0.0f && eiy < (T.CellNumY - 1))
				pCellLayer[(eiy + 1) * T.CellNumX + eix].FindGrains(expx, expy, dirx, diry, dirtol, T.AlignTol, pOut, Dist, maxmult);
			}
		}
	for (i = 0; i < maxmult && Dist[i] < T.AlignTol; i++) pGrainDest[i] = pOut[i];
	return i;	
	}

UINT CSmartTrackerClass::PartialGetTracks2(CSmartTrackerClass::ActivationRecord &AR)
{
	int countIterations = 0, countSlopeX = 0, countSlopeY = 0, countTrials = 0, countFindGrains = 0, countPossible = 0, countAccepted = 0;
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

	IntGrain **pTempGrains = (IntGrain **)malloc(sizeof(IntGrain *) * (EndLayer + 1) * T.InitialMultiplicity);

	float avgdz = (ZLayer[StartLayer] - ZLayer[EndLayer]) / (EndLayer - StartLayer);
	float avgdz2 = avgdz * avgdz;
			
	float tsl = (T.NptMin01 == T.NptMinH) ? 0.0 : (10.0f * (T.NptMinV - T.NptMin01) / (T.NptMin01 - T.NptMinH));
	float tinf = (float)(T.NptMinH);
	float td = (float)(T.NptMinV - T.NptMinH);

	if (T.PresetSlope)
	{

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
									countIterations++;
									if (GetTickCount() > TimeLimit)
									{
										AR.Found = 0;
										return S_FALSE;
										}
									IntGrain gb = *pB;
									SlopeX = idz * (gt.Xcm - gb.Xcm);
									if (fabs(SlopeX) >= MaxSlope || fabs(SlopeX - T.PresetSlopeX) > T.PresetSlopeAccX) continue;									
									countSlopeX++;
									SlopeY = idz * (gt.Ycm - gb.Ycm);
									if (fabs(SlopeY) >= MaxSlope || fabs(SlopeY - T.PresetSlopeY) > T.PresetSlopeAccY) continue;
									Slope2 = SlopeX * SlopeX + SlopeY * SlopeY;
									countSlopeY++;
restart:	
									if (Slope2 < MaxSlope2)
									{
										countTrials++;
										SlopeS = sqrt(Slope2);
										if (SlopeS > 0.0f) ISlopeS = 1.0f / SlopeS;
										avgds2 = avgdz2 * Slope2;
										fastGetDirAndTol(SlopeS, ISlopeS, DirX, DirY, dirtol/*, aligntol2, avgds2*/);
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
												memset(pTempGrains, 0, T.Layer * sizeof(Grain *) * T.InitialMultiplicity);
												float dz;
												int seqlength = 0;
												//int seqlength = 3;
/*	
												pTempGrains[tr.TopLayer] = pT;
												pTempGrains[tr.BottomLayer] = pB;
												pTempGrains[TriggerLayer] = pTrg;
*/	
												CurrDeltaX = fabs(avgdz * SlopeX);
												CurrDeltaY = fabs(avgdz * SlopeY);
/*	
												for (lay = tr.TopLayer; lay <= tr.BottomLayer; lay++)
												{
													dz = ZLayer[lay] - tz;
													ExpX = dz * SlopeX + gt.Xcm;
													ExpY = dz * SlopeY + gt.Ycm;
													if (FindGrains(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, pTempGrains + lay * T.InitialMultiplicity, T.InitialMultiplicity)) seqlength++;												
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
													float diz = 1.0f / dz;
													dz = ZLayer[lay] - topv.Z;
													ExpX = dz * SlopeX + topv.X;
													ExpY = dz * SlopeY + topv.Y;
													if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, 0, DiscardShadows ? pTempGrains[lay + 1] : 0, ShadowXTol, ShadowYTol))
													{
														seqlength++;
														}
													else if (--availablevoids <= 0) break;
													};
												if (availablevoids <= 0) continue;
												for (lay = (int)tr.BottomLayer + 1; lay <= EndLayer; lay++)
												{
													dz = (bottomv.Z - topv.Z);
													float diz = 1.0f / dz;
													dz = ZLayer[lay] - topv.Z;
													ExpX = dz * SlopeX + topv.X;
													ExpY = dz * SlopeY + topv.Y;
													if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, DiscardShadows ? pTempGrains[lay - 1] : 0, 0, ShadowXTol, ShadowYTol))
													{
														seqlength++;
														}
													else if (--availablevoids <= 0) break;
													};
*/	
												for (lay = StartLayer; lay <= EndLayer; lay++)
												{
													dz = ZLayer[lay] - tz;
													ExpX = dz * SlopeX + gt.Xcm;
													ExpY = dz * SlopeY + gt.Ycm;
													countFindGrains++;
													if (FindGrains(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, pTempGrains + lay * T.InitialMultiplicity, T.InitialMultiplicity)) seqlength++;
													};											
												
												if ((float)seqlength > (tinf + td / (1.0f + tsl * SlopeS)))
												{					
													countPossible++;
													if (AR.Found < AR.MaxTracks)
													{
														countAccepted++;
														Track2 &N = AR.pSpace[AR.Found++];
														int i, j;
														for (i = j = 0; i <= EndLayer * T.InitialMultiplicity; i++)
															if (pTempGrains[i])
															{
																IntTrackGrain *pIG = ((IntTrackGrain *)N.pGrains) + j++;
																pIG->T.pG = pTempGrains[i];
																pIG->T.Z = ZLayer[i / T.InitialMultiplicity];
																}														
														N.Field = (itr << 24) + (ix << 16) + ifound;
														N.Valid = true;
														N.Grains = j;//seqlength;
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


		}
	else
	{

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
									countIterations++;
									if (GetTickCount() > TimeLimit)
									{
										AR.Found = 0;
										return S_FALSE;
										}
									IntGrain gb = *pB;
									SlopeX = idz * (gt.Xcm - gb.Xcm);
									if (fabs(SlopeX) >= MaxSlope) continue;
									countSlopeX++;
									SlopeY = idz * (gt.Ycm - gb.Ycm);
									if (fabs(SlopeY) >= MaxSlope) continue;
									Slope2 = SlopeX * SlopeX + SlopeY * SlopeY;
									countSlopeY++;
restartpreset:	
									if (Slope2 < MaxSlope2)
									{
										countTrials++;
										SlopeS = sqrt(Slope2);
										if (SlopeS > 0.0f) ISlopeS = 1.0f / SlopeS;
										avgds2 = avgdz2 * Slope2;
										fastGetDirAndTol(SlopeS, ISlopeS, DirX, DirY, dirtol/*, aligntol2, avgds2*/);
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
												memset(pTempGrains, 0, T.Layer * sizeof(Grain *) * T.InitialMultiplicity);
												float dz;
												int seqlength = 0;
												//int seqlength = 3;
/*	
												pTempGrains[tr.TopLayer] = pT;
												pTempGrains[tr.BottomLayer] = pB;
												pTempGrains[TriggerLayer] = pTrg;
*/	
												CurrDeltaX = fabs(avgdz * SlopeX);
												CurrDeltaY = fabs(avgdz * SlopeY);
/*	
												for (lay = tr.TopLayer; lay <= tr.BottomLayer; lay++)
												{
													dz = ZLayer[lay] - tz;
													ExpX = dz * SlopeX + gt.Xcm;
													ExpY = dz * SlopeY + gt.Ycm;
													if (FindGrains(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, pTempGrains + lay * T.InitialMultiplicity, T.InitialMultiplicity)) seqlength++;												
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
													float diz = 1.0f / dz;
													dz = ZLayer[lay] - topv.Z;
													ExpX = dz * SlopeX + topv.X;
													ExpY = dz * SlopeY + topv.Y;
													if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, 0, DiscardShadows ? pTempGrains[lay + 1] : 0, ShadowXTol, ShadowYTol))
													{
														seqlength++;
														}
													else if (--availablevoids <= 0) break;
													};
												if (availablevoids <= 0) continue;
												for (lay = (int)tr.BottomLayer + 1; lay <= EndLayer; lay++)
												{
													dz = (bottomv.Z - topv.Z);
													float diz = 1.0f / dz;
													dz = ZLayer[lay] - topv.Z;
													ExpX = dz * SlopeX + topv.X;
													ExpY = dz * SlopeY + topv.Y;
													if (pTempGrains[lay] = FindGrain(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, DiscardShadows ? pTempGrains[lay - 1] : 0, 0, ShadowXTol, ShadowYTol))
													{
														seqlength++;
														}
													else if (--availablevoids <= 0) break;
													};
*/	
												for (lay = StartLayer; lay <= EndLayer; lay++)
												{
													dz = ZLayer[lay] - tz;
													ExpX = dz * SlopeX + gt.Xcm;
													ExpY = dz * SlopeY + gt.Ycm;
													countFindGrains++;
													if (FindGrains(ExpX, ExpY, CellSpace + lay * T.CellsInLayer, DirX, DirY, dirtol, pTempGrains + lay * T.InitialMultiplicity, T.InitialMultiplicity)) seqlength++;
													};											
												
												if ((float)seqlength > (tinf + td / (1.0f + tsl * SlopeS)))
												{					
													countPossible++;
													if (AR.Found < AR.MaxTracks)
													{
														countAccepted++;
														Track2 &N = AR.pSpace[AR.Found++];
														int i, j;
														for (i = j = 0; i <= EndLayer * T.InitialMultiplicity; i++)
															if (pTempGrains[i])
															{
																IntTrackGrain *pIG = ((IntTrackGrain *)N.pGrains) + j++;
																pIG->T.pG = pTempGrains[i];
																pIG->T.Z = ZLayer[i / T.InitialMultiplicity];
																}														
														N.Field = (itr << 24) + (ix << 16) + ifound;
														N.Valid = true;
														N.Grains = j;//seqlength;
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


		}

	free(pTempGrains);
/*
	char fname[256];
	sprintf(fname, "c:\\acq\\smt8c_%d.txt", AR.ThreadIndex);
	FILE *f;
	if (!(f = fopen(fname, "r+t")))
	{
		f = fopen(fname, "w+t");
		fprintf(f, "Iters\tSlopeX\tSlopeY\tTrials\tFindGrn\tPoss\tAcc");
		}
	else
	{
		fclose(f);
		f = fopen(fname, "a+t");
		}
	fprintf(f, "\n%d\t%d\t%d\t%d\t%d\t%d\t%d", countIterations, countSlopeX, countSlopeY, countTrials, countFindGrains, countPossible, countAccepted);
	fclose(f);	
*/
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

	//CorrectChains();

	int starttime = GetTickCount();
	char fdumpname[256];
	
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

	int endtime = GetTickCount();
/*	if (endtime - starttime > T.MaxTrackingTime * 2)
	{
		sprintf(fdumpname, "c:\\acq\\smt8a_%08X.txt", starttime);
		FILE *f = fopen(fdumpname, "wt");
		fprintf(f, "Time: %d", endtime - starttime);
		fprintf(f, "StartLayer: %d EndLayer: %d", StartLayer, EndLayer);
		fprintf(f, "\nLayers: %d", T.Layer);
		fprintf(f, "\nGrains: %d", T.NumGrains);
		fprintf(f, "\nCells:");				
		int layer, icell, igrain;
		for (layer = 0; layer < T.Layer; layer++)
			for (icell = 0; icell < T.CellsInLayer; icell++)
				fprintf(f, "\n%d\t%d\t%f\t%d", layer, icell, T.ZLayer[layer], T.CellSpace[layer * T.CellsInLayer + icell].Free);
		for (layer = 0; layer < T.Layer; layer++)
			for (icell = 0; icell < T.CellsInLayer; icell++)
				for (igrain = 0; igrain < T.CellSpace[layer * T.CellsInLayer + icell].Free; igrain++)
					fprintf(f, "\n%d\t%d\t%f\t%d\t%f\t%f\t%d", layer, icell, T.ZLayer[layer], T.CellSpace[layer * T.CellsInLayer + icell].Free, T.CellSpace[layer * T.CellsInLayer + icell].FirstG[igrain].Xcm, T.CellSpace[layer * T.CellsInLayer + icell].FirstG[igrain].Ycm, T.CellSpace[layer * T.CellsInLayer + icell].FirstG[igrain].Area);
		fclose(f);
		}
*/

	for (p = 0; p < T.Processors; p++)
		for (i = 0; i < ThreadInfo[p].Found; i++)
		{
			Track2 &K = ThreadInfo[p].pSpace[i];
			seqlength = K.Grains;
			if (!T.AllowOverlap)
			{
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
				}			
			K.Valid = true;
			}
/*
	if ((endtime = GetTickCount()) > TimeLimit) 
	{
		sprintf(fdumpname, "c:\\acq\\smt8b_%08X.txt", starttime);
		FILE *f = fopen(fdumpname, "wt");
		fprintf(f, "Time: %d TimeLimit: %d", endtime - starttime, TimeLimit);
		fclose(f);
		}
*/
	found = ThreadInfo[0].Found;
	pTemp = (Grain *)malloc(sizeof(Grain) * T.LayerNum * T.InitialMultiplicity);
	for (p = 1; p < T.Processors; p++)
		for (i = 0; i < ThreadInfo[p].Found; i++)
		{
			TempF = ThreadInfo[p].pSpace[i].Field;
			TempG = ThreadInfo[p].pSpace[i].Grains;
			//if (TempV = ThreadInfo[p].pSpace[i].Valid)
			TempV = ThreadInfo[p].pSpace[i].Valid;
			memcpy(pTemp, ThreadInfo[p].pSpace[i].pGrains, sizeof(Grain) * TempG);
/* THESE LINES DISABLE TRACK ORDERING */
#if 1
			j = found;
#else
			for (j = 0; (j < found) && (pSpace[j].Field < TempF); j++);
			for (k = found; k > j; k--)
			{
				pSpace[k].Field = pSpace[k - 1].Field;
				pSpace[k].Grains = pSpace[k - 1].Grains;
				//if (pSpace[k].Valid = pSpace[k - 1].Valid)
				pSpace[k].Valid = pSpace[k - 1].Valid;
				memcpy(pSpace[k].pGrains, pSpace[k - 1].pGrains, sizeof(Grain) * pSpace[k].Grains);
				}
#endif
/* END OF TRACK ORDERING DISABLE */
			pSpace[j].Field = TempF;
			pSpace[j].Grains = TempG;
			//if (pSpace[j].Valid = TempV)
			pSpace[j].Valid = TempV;
			memcpy(pSpace[j].pGrains, pTemp, sizeof(Grain) * TempG);
			found++;
			}
	free(pTemp);

/*
	if ((endtime = GetTickCount()) > TimeLimit) 
	{
		sprintf(fdumpname, "c:\\acq\\smt8c_%08X.txt", starttime);
		FILE *f = fopen(fdumpname, "wt");
		fprintf(f, "Time: %d TimeLimit: %d", endtime - starttime, TimeLimit);
		for (p = 0; p < T.Processors; p++)
			fprintf(f, "\nThread: %d Found: %d", p, ThreadInfo[p].Found);

		fclose(f);
		}
*/
	*pMaxNumber = FinalizeTracks(found, pSpace);
/*
	if ((endtime = GetTickCount()) > TimeLimit) 
	{
		sprintf(fdumpname, "c:\\acq\\smt8d_%08X.txt", starttime);
		FILE *f = fopen(fdumpname, "wt");
		fprintf(f, "Time: %d TimeLimit: %d", endtime - starttime, TimeLimit);
		fclose(f);
		}
*/
	return S_OK;
	}

STDMETHODIMP CSmartTrackerClass::GetMaxGrainsPerTrack(int *pMaxGrains)
{
	*pMaxGrains = T.LayerNum * T.InitialMultiplicity;
	return S_OK;
	}

STDMETHODIMP CSmartTrackerClass::StartFilling2(int Side)
{	
	//if (Side < 0 || Side > 1) return E_INVALIDARG;
	HRESULT HRes = StartFilling();
	T.Side = Side;
	return HRes;
	}

// INTERNAL FUNCTIONS

void CSmartTrackerClass::InitTrackerData()
{
	SySalConfig Temp = {0, 0, 0};
	GetData(Temp, ConfigDataN, ConfigDataQDI, &T, true);

	T.PresetSlope = false;
	T.PresetSlopeAccX = T.PresetSlopeAccY = T.PresetSlopeX = T.PresetSlopeY = 0.0f;
	T.GrainSpace = 0;
	T.ZLayer = 0;
	T.LayerGrains = 0;
	T.CellSpace = 0;
	T.pDeltaHisto2d = 0;
	T.pDeltaData = 0;
	T.pX = T.pY = T.pDX = T.pDY = 0;
	T.pReplicas = 0;
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

void Cell::FindGrains(float x, float y, float dirx, float diry, float dirtol, float normtol, IntGrain **pDest, float *pDist, int maxmult)
{
	int i, j;
	float normdist;
	float dx, dy;
	IntGrain *pStart = FirstG;
	IntGrain *pEnd = FirstG + Free;
	float reddirtol = dirtol * 1.5f;
	for (IntGrain *pScan = pStart; pScan < pEnd; pScan++)
		if (fabs(dx = (pScan->Xcm - x)) <= reddirtol)
			if (fabs(dy = (pScan->Ycm - y)) <= reddirtol)
				if ((normdist = fabs(dy * dirx - dx * diry)) < normtol)
					if (fabs(dx * dirx + dy * diry) < dirtol)
					{
						for (i = 0; i < maxmult && pDist[i] <= normdist; i++);
						if (i == maxmult) continue;
						for (j = maxmult - 1; j > i; j--)
						{
							pDist[j] = pDist[j - 1];
							pDest[j] = pDest[j - 1];
							}
						pDest[i] = pScan;
						pDist[i] = normdist;
						};
	}

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
	float avglx = T.TotalLX / T.Layer;
	float avgly = T.TotalLY / T.Layer;
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
				if (T.Side == 0)
				{
					N.pGrains[k].X = pG->Xcm + dsx * dz - avglx;
					N.pGrains[k].Y = pG->Ycm + dsy * dz - avgly;
					N.pGrains[k].Area = ta;
					}
				else
				{
					N.pGrains[k].X = pG->Xcm + dsx * dz;
					N.pGrains[k].Y = pG->Ycm + dsy * dz;				
					N.pGrains[k].Area = ta;
					}
				}
			N.AreaSum = a;
			}
	return j;
}


bool CSmartTrackerClass::ResetDeltaHisto()
{
	if (T.pDeltaHisto2d) CoTaskMemFree(T.pDeltaHisto2d);
	T.pDeltaHisto2d = 0;
	T.DeltaDX = fabs(T.PixelToMicronX);
	T.DeltaDY = fabs(T.PixelToMicronY);
	T.DeltaBinsX = (int)floor(T.ReplicaRadius / T.DeltaDX + 1) * 2 + 5;
	T.DeltaBinsY = (int)floor(T.ReplicaRadius / T.DeltaDY + 1) * 2 + 5;
	return T.pDeltaHisto2d = (int *)CoTaskMemAlloc( sizeof(int) * T.DeltaBinsX * T.DeltaBinsY);
}





void CSmartTrackerClass::PutData(SySalConfig *pConfig, ConfigData *pC)
{
	::PutData(*pConfig, ConfigDataN, ConfigDataQDI, pC);
}

bool CSmartTrackerClass::IsSigmaValid(IntGrain **pTempGrains, int Layers)
{
	return false;
}




/*
void CSmartFitterClass::Linear_Fit2(IntTrack2 *Tk, float zbase)
{	
	double V, W, Base;
	double SumP, SumZ, SumZ2, SumZP, Den, D;
	Grain *ScanZ, *EndZ;
	int NPoints = Tk->Grains;
	double S = 0, C0, C1;

	EndZ = Tk->pGrains + NPoints;
	SumP = SumZ = SumZ2 = SumZP = 0;
	Base = Tk->pGrains->X;
	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	
		V = ScanZ->Z - zbase;
		W = ScanZ->X - Base;
		SumZ += V;
		SumZ2 += V * V;
		SumP += W;
		SumZP += V * W;
		};

	Den = 1. / (NPoints * SumZ2 - SumZ * SumZ);

	C0 = (SumP * SumZ2 - SumZ * SumZP) * Den + Base;
	C1 = Tk->Slope.X = (NPoints * SumZP - SumZ * SumP) * Den;
	Tk->Intercept.X = C0; // - C1 * zbase;

	SumP = SumZ = SumZ2 = SumZP = 0;
	Base = Tk->pGrains->Y;
	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	V = ScanZ->Z - zbase;
		W = ScanZ->Y - Base;
		SumZ += V;
		SumZ2 += V * V;
		SumP += W;
		SumZP += V * W;
		};

	Den = 1. / (NPoints * SumZ2 - SumZ * SumZ);

	C0 = (SumP * SumZ2 - SumZ * SumZP) * Den + Base;
	C1 = Tk->Slope.Y = (NPoints * SumZP - SumZ * SumP) * Den;
	Tk->Intercept.Y = C0; // - C1 * zbase;

	float Slope = sqrt(Tk->Slope.X * Tk->Slope.X + Tk->Slope.Y * Tk->Slope.Y);
	if (Slope <= 0.0f)
	{
		for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
		{	
			V = ScanZ->Z - zbase;
			S += (fabs(Tk->Slope.X * V + Tk->Intercept.X - ScanZ->X) + fabs(Tk->Slope.Y * V + Tk->Intercept.Y - ScanZ->Y)) * 0.5f;
			};
		}
	else
	{
		float NX = -Tk->Slope.Y / Slope;
		float NY = Tk->Slope.X / Slope;
		for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
		{	
			V = ScanZ->Z - zbase;
			S += fabs((Tk->Slope.X * V + Tk->Intercept.X - ScanZ->X) * NX +
				(Tk->Slope.Y * V + Tk->Intercept.Y - ScanZ->Y) * NY);
			};
		}
	S /= (NPoints - 2);
	Tk->Intercept.Z = zbase;
	Tk->Slope.Z = 1.;

	Tk->Sigma = S;
	Tk->Correction->C1.X = Tk->Correction->C1.Y = Tk->Correction->C2.X = Tk->Correction->C2.Y = 0.0f;
	};

  */

#include "..\Common\Config2.cpp"


