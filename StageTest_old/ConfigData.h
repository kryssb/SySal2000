#ifndef __CSTAGETEST_CONFIG_DATA_
#define __CSTAGETEST_CONFIG_DATA_

#include "Config.h"

struct ConfigData
{
	// SYSAL_OBJECT_PROPERTY_STRUCT_BEGIN

	float 	XStep;
	float 	YStep;
	float 	ZStep;
	float 	XAcc;
	float 	YAcc;
	float 	ZAcc;
	float 	XSpeed;
	float 	YSpeed;
	float 	ZSpeed;
	float 	XLongRange;
	float 	YLongRange;
	float 	ZLongRange;
	float 	XStopTol;
	float 	YStopTol;
	float 	ZStopTol;
	float 	XDampTol;
	float 	YDampTol;
	float 	ZDampTol;
	int 	Samples;
	int 	XWait;
	int 	YWait;
	int 	ZWait;
	int 	UseStop;

// SYSAL_OBJECT_PROPERTY_STRUCT_END
};

#endif