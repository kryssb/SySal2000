#ifndef _TOTAL_SCAN_RECONSTRUCTION_DATA
#define _TOTAL_SCAN_RECONSTRUCTION_DATA

#define TSRD_REMEASURE_MERGE			1
#define TSRD_REMEASURE_DISCARDSHORTER	2
#define TSRD_REMEASURE_DISCARDWORSE		3

#define TSRD_PRESCAN_NONE				0
#define TSRD_PRESCAN_TRANSLATION		1
#define TSRD_PRESCAN_AFFINEDEFORMATION	2

struct TSReconData
{
	float InField_D_Pos;
	float InField_D_Slope;
	float OffField_D_Pos;
	float OffField_D_Slope;
	int MaxRemeasuresInSegment;
	int RemeasureHandling;
	float LocalityCellSize;
	float D_Pos;
	float D_Slope;
	float Gross_D_Pos;
	float Gross_D_Slope;
	int PrescanMode;
	float PrescanExtents;
	float PrescanZoneWidth;
	float PrescanLeverArm;
	BOOL AlignOnLinked;
	float AlignBeamXSlope;
	float AlignBeamYSlope;
	float AlignBeamWidth;
	int MaxIters;
	int MaxMissingSegments;
	int MinSegments;
	int MinSegmentsRecovery;
	float PassingThrough_Radius;
	float PassingThrough_Angle;
	float PassingThrough_OutLength;
	float Vertex_XYTol;
	float Vertex_XYTolIncrease;
	float Vertex_LowestZ;
	float Vertex_Overlength;
	float Vertex_MergeXYTol;
	float Vertex_MergeZTol;
	float Vertex_ZExtrapolation;
	float Vertex_Recovery_ZExtrapolation;
	BOOL FinalAlignment_Enable;	
	int FinalAlignment_MaxIters;
	float FinalAlignment_MaxSlopeDiff;
	float FinalAlignment_MinSlopeDiff;
	int FinalAlignment_SlopeMeasures;
	int FinalAlignment_MinEntries;
	float FinalAlignment_MaxRMS;
	};

#endif