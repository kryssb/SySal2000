#ifndef _SYSAL_INTERNAL_MARK_MAP_
#define _SYSAL_INTERNAL_MARK_MAP_

#include "id.h"
#include "MarkMap3.h"

struct IntMark 
{
	unsigned Id;
	int Type;
	struct t_Pos
	{		
		float X, Y;
		} Nominal, Stage;
	int Status;
	unsigned Side;
	float Z;
	};

struct IntMarkMap
{
	Identifier Id;
	unsigned Count;
	IntMark *pMarks;
	float PlateMinX;
	float PlateMinY;
	float PlateMaxX;
	float PlateMaxY;
	};

#endif