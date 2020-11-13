#ifndef _SCSCAN_DATA_STRUCTURES_
#define _SCSCAN_DATA_STRUCTURES_

#define CS_SS_TRACK_SECTION 		1
#define CS_SS_LTRACK_SECTION 		2
#define CS_SS_FIELD_SECTION			3
#define OPERA_INDEX_SECTION			4
#define CS_SS_DATA_BYTES			0x20
#define CS_SS_HEADER_BYTES			0x40

#define CS_SS_OLD_HEADER_TYPE			0X08
#define CS_SS_OLD2_HEADER_TYPE			0X02
#define CS_SS_HEADER_TYPE				0X01
#define OPERA_HEADER_TYPE				0X03
#define OPERA_HEADER_TYPE_WITH_INDEX	0X04

#pragma pack(push)
#pragma pack(1)

#include "id.h"
#include "TVectors.h"
#include "Track.h"
#include "Track2.h"

typedef struct 
{
	IO_Header Type;
	Identifier ID;
	float YPos, ZPos;
	float YSlope, ZSlope;
	float SideSlopeTolerance;
	float GlobalSlopeTolerance;
	float GoodSlopeTolerance;
	int TCount[2];
	int LCount;
	int FCount;
	struct
	{
		float TopExt;
		float TopInt;
   		float BottomInt;
		float BottomExt;
		} RelevantZs;
	} CS_SS_TracksHeader;

typedef struct 
{
	IO_Header Type;
	Identifier ID;
	float XPos, YPos;
	float MinX, MaxX, MinY, MaxY;
	float fReserved;
	int TCount[2];
	int LCount;
	int FCount;
	struct
	{
		float TopExt;
		float TopInt;
   		float BottomInt;
		float BottomExt;
		} RelevantZs;
	} OPERA_TracksHeader;

typedef struct
{
	int PointsN;
	TVector Intercept;
	TVector Slope;
	float Sigma;
	Track *pTracks[2];
	TVector InterceptErrors;
	TVector SlopeErrors;
	} CS_SS_LinkedTrack;

typedef struct
{
	unsigned AreaSum;
	unsigned Grains;
	TVector Intercept;
	TVector Slope;
	float Sigma;
	Track2 *pTracks[2];
	} OPERA_LinkedTrack;

typedef struct
{
	CS_SS_TracksHeader Hdr;
	BYTE *FieldHistory;
	Track *pTracks[2];
	CS_SS_LinkedTrack *pLinked;
	} IO_CS_SS_Tracks;

typedef struct
{
	int Fragment;
	int View;
	int Track;
	} OPERA_TrackIndexEntry;

typedef struct
{
	OPERA_TracksHeader Hdr;
	BYTE *FieldHistory;
	Track2 *pTracks[2];
	OPERA_LinkedTrack *pLinked;
	OPERA_TrackIndexEntry *pIndexEntries[2];
	} IO_OPERA_Tracks;

#pragma pack(pop)

#endif