#ifndef _SYSAL_VIRTUALMICROSCOPE_TRACK_SIMULATION_
#define _SYSAL_VIRTUALMICROSCOPE_TRACK_SIMULATION_

#include "TVectors.h"

struct SimTrack
{
	int ID;
	TVector Intercept;
	TVector Slope;
	};

#endif