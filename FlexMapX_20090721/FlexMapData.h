#ifndef _SYSAL_FLEXMAPDATA_
#define _SYSAL_FLEXMAPDATA_

#include "SySal_Common.h" //#include "../Common/Config.h"

#define MAXFIRSIZE 32

struct FlexMapData
{
	int   BinningSize;
	float GreyLevelSampleFraction;
	float StripWidth;
	int   StripPeakThreshold;
	char  FIRString[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	float ScanTransverseTolerance;
	int   SettlingTime;
	float StripSamplingDistance;
	int   MaxStripCandidates;

	float LongDistSpeed;
	float LongDistAcc;
	float ShortDistSpeed;
	float ShortDistAcc;
	float ZSetSpeed;
	float HorizTolerance;
	float VertTolerance;
	float VertAcc;
	float TimeOut;
	char  RecoveryFileName[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	BOOL  SheetIsRotatedBy180Deg;
	BOOL  SearchFirstMark;
	float TotalThickness;

	int   FIRSize;
	int   FIR[MAXFIRSIZE];

	static bool StringToFIR(char *str, int *pfirsize, int *pfir);
	static bool FIRToString(int firsize, int *pfir, int maxlen, char *pout);

	float    FramesPerSecond;
	unsigned ClusteringParameter;
	unsigned MaxClusters;
	float    Diameter;
	float    DiameterTolerance;
	float    MaxEllipticity;
	float    FocusSpeed;
	float    FocusStroke;
	float    CenterTolerance;

   BOOL     ForceLateralMark ;
  // BOOL     PauseIfCloneNotFound     ;

};

#endif