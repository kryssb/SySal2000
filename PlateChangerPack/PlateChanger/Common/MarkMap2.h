#ifndef _SYSAL_MARK_MAP2_
#define _SYSAL_MARK_MAP2_

#include "MarkMap.h"

#pragma pack(push)
#pragma pack(1)

typedef struct 
{
	unsigned Id;
	struct t_Pos
	{
		float X, Y;
		} Nominal, Stage;
	int Status;
	unsigned Side;
	} Mark2;

typedef struct 
{
	unsigned Count;
	Mark2 *pMarks;
	float PlateMinX;
	float PlateMinY;
	float PlateMaxX;
	float PlateMaxY;
	} MarkMap2;

#pragma pack(pop)

#endif