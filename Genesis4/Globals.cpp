#include "StdAfx.h"
#include "Globals.h"

PrecompSegmentBlock *PrecompData;

short Kernel[KERNEL_XSIZE * KERNEL_YSIZE] = 
{
	1, 1, 1, 1, 1, 1,
	1, 2, 3, 3, 2, 1,
	1, 3, -13, -13, 3, 1,
	1, 3, -13, -13, 3, 1,
	1, 2, 3, 3, 2, 1,
	1, 1, 1, 1, 1, 1
	};

// PACKED SEGMENTS HANDLING

void InitializePrecompSegments(PrecompSegmentBlock *DataSpace)
{
	unsigned i, j;
	unsigned TotalCount = 1 << PACKED_BLOCK;
	bool SegmentOpen;
	PrecompSegmentBlock;

	for (i = 0; i < TotalCount; i++)
	{
		unsigned tester;
		SegmentOpen = false;		
		DataSpace[i].NumberOfSegments = 0;
		//for ((tester = 0x80), (j = 0); tester; (tester >>= 1), j++)		
		// WARNING! THE GENESIS BUFFERS ARE REVERSED! USE THE VERSION BELOW!
		for ((tester = 0x01), (j = 0); tester & 0xFF; (tester <<= 1), j++)		
		{
			if (!(i & tester))
			{
				if (SegmentOpen)
					DataSpace[i].Segments[DataSpace[i].NumberOfSegments].RightOffset = j;
				else
				{
					SegmentOpen = true;
					DataSpace[i].Segments[DataSpace[i].NumberOfSegments].RightOffset = 
					DataSpace[i].Segments[DataSpace[i].NumberOfSegments].LeftOffset = j;
					};
				}
			else
			{				
				if (SegmentOpen)
					DataSpace[i].NumberOfSegments++;
				SegmentOpen = false;
				};
			};
		if (SegmentOpen) DataSpace[i].NumberOfSegments++;
		};
	};

#include "Config2.cpp"