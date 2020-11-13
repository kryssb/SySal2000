#ifndef SYSAL_TRACKMAPPER
#define SYSAL_TRACKMAPPER

#include "Vectors2.h"
#include "..\Common\Segment.h"

struct Diff
{
	Vector2 FixPos;
	Vector2 MovPos;
	Vector2 FixSlope;
	Vector2 MovSlope;
	TS_Segment *Fix;
	TS_Segment *Mov;
	};

struct MappingParams
{
	int CoincN;
	Vector2 Overlap;
	Vector2 FixSize;
	Vector2 MovSize;
	Vector2 RawTransl;
	Diff *Pair;
	};

void MapTracks(MappingParams *Result, int N1, TS_Segment *T1, int N2, TS_Segment *T2, float TolP,
	float TolS, float MaxDisplacement, float LowestPrescanPeak);

#endif
