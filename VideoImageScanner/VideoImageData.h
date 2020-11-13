#ifndef _VIDEO_IMAGE_SCANNER_DATA_
#define _VIDEO_IMAGE_SCANNER_DATA_

struct VideoImageData
{
	bool RelativeThreshold;
	bool Equalization;
	UINT Threshold[2];
	UINT MaxGrains;
	UINT StartLayer[2];
	UINT EndLayer[2];
	UINT MaxTracks;
	UINT MaxFlatTracks;
	UINT MaxFlatStripsInTrack;
	float Shrinkage;
	};

#endif