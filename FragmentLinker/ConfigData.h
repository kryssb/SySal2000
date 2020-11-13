#ifndef _SYSAL_FRAGMENT_LINKER_CONFIG_DATA_H_
#define _SYSAL_FRAGMENT_LINKER_CONFIG_DATA_H_

typedef struct t_FragmentLinkerConfigData
{
	UINT MinPoints;
	float PositionTolerance;
	float SlopeTolerance;
	float MinSlope;
	float MergeSlopeTolerance;
	float MergePosTolerance;
	} FragmentLinkerConfigData;

#endif