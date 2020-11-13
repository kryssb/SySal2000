#ifndef _GENESIS_DATA_4_H_
#define _GENESIS_DATA_4_H_

#include "Config.h"

struct t_LightControlSettings
{
	UINT MinLev, MaxLev;
	float TargetGrayLev;
	UINT SaturationGrayLev;
	float TargetSaturationFraction;
	UINT LampTimeConstant;	

	t_LightControlSettings &operator<<(SySalConfig &C);
	t_LightControlSettings &operator>>(SySalConfig &C);
	};

#endif