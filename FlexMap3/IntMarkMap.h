#ifndef _SYSAL_INTERNAL_MARK_MAP_
#define _SYSAL_INTERNAL_MARK_MAP_

#include "id.h"

#define INTMARKMAP_FMT_BASE				0
#define INTMARKMAP_FMT_SIDEEXTENTS		1

struct IntMark
{
	unsigned Id;
	struct t_Pos
	{
		float X, Y;
		} Nominal, Stage;
	float Z;
	int Status;
	unsigned Side;
	};

struct IntMarkMap
{
	Identifier Id;
	unsigned Count;
	IntMark *pMarks;
	unsigned ExtendedFormat;	
	float PlateMinX;
	float PlateMinY;
	float PlateMaxX;
	float PlateMaxY;
	};

#endif