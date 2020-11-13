#ifndef _SYSAL_INTERNAL_MARK_MAP_
#define _SYSAL_INTERNAL_MARK_MAP_

#include "id.h"

struct IntMark
{
	unsigned Id;
	struct t_Pos
	{
		float X, Y;
		} Nominal, Stage;
	float Z;
	int Status;
	};

struct IntMarkMap
{
	Identifier Id;
	unsigned Count;
	IntMark *pMarks;
	};

#endif