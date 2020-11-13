#ifndef _TOTAL_SCAN_RECONSTRUCTION_DATA
#define _TOTAL_SCAN_RECONSTRUCTION_DATA

#define TSRD_REMEASURE_MERGE			1
#define TSRD_REMEASURE_DISCARDSHORTER	2
#define TSRD_REMEASURE_DISCARDWORSE		3

struct TSReconData
{
	float InField_D_Pos;
	float InField_D_Slope;
	float OffField_D_Pos;
	float OffField_D_Slope;
	int MaxRemeasuresInSegment;
	int RemeasureHandling;
	float LowestPrescanPeak;
	float InPlate_D_Pos;
	float InPlate_D_Slope;
	float InPlate_Gross_D_Pos;
	float InPlate_Gross_D_Slope;
	float InPlate_Pos_Prescan;
	int InPlate_MaxIters;
	int MaxMissingSegments;
	int MinSegments;
	int MinSegmentsRecovery;
	float OffPlate_D_Pos;
	float OffPlate_D_Slope;
	float OffPlate_Gross_D_Pos;
	float OffPlate_Gross_D_Slope;
	float OffPlate_Pos_Prescan;
	int OffPlate_MaxIters;
	int RequireOffPlateLinking;
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