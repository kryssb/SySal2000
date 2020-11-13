#ifndef _SYSAL_MARK_MAP3_
#define _SYSAL_MARK_MAP3_

#include "MarkMap.h"

#pragma pack(push)
#pragma pack(1)

#define MARK_XRAY_TYPE_X	'X'
#define MARK_XRAY_TYPE_Y	'Y'

typedef struct 
{
	unsigned Id;
	int Type;
	struct t_Pos
	{		
		float X, Y;
		} Nominal, Stage;
	int Status;
	unsigned Side;
	} Mark3;

typedef struct 
{
	unsigned Count;
	Mark3 *pMarks;
	float PlateMinX;
	float PlateMinY;
	float PlateMaxX;
	float PlateMaxY;
	} MarkMap3;

#pragma pack(pop)

#endif