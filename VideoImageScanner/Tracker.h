// Tracker.h: interface for the CTracker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACKER_H__D1ED07C1_EAA2_11D3_BF7F_002018B80960__INCLUDED_)
#define AFX_TRACKER_H__D1ED07C1_EAA2_11D3_BF7F_002018B80960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "..\Common\datastructs.h"
#include "..\Common\ClusterFinder.h"
#include "..\Common\Objective.h"
#include "..\Common\IO.h"
#include "..\Common\Tracker.h"
#include "..\Common\Fitter.h"
#include <afxcmn.h>

class CTracker  
{
public:
	bool FindTracks(IO_Data *pData, UINT MaxTracks[2], Track *pTSpace[2], int MaxGrains, bool RelativeThreshold, UINT Thresholds[2], bool Equalization, 
		UINT StartLayer[2], UINT EndLayer[2], UINT MaxFlatTracks[2], FlatTrack *pFSpace[2], UINT MaxFlatStripsInTrack, float Shrinkage, int Iterations, float *pAvgTime, 
		CProgressCtrl *pClusterProgress, CString &RetString);
	CTracker(IClusterFinder * icl, ITrackFitter * ift, ITrackFitter2 * ift2, ITracker * itk, ITracker2 *itk2, IObjective * iob);
	virtual ~CTracker();

protected:
	void TrackFitDiscard(UINT *pMaxTracks, Track *pTSpace, UINT *pMaxFlatTracks, FlatTrack *pFSpace, UINT MaxFlatStripsInTrack, UINT StartLayer, UINT EndLayer, CameraSpec *pCamSpec, float ImageMat[2][2], 
		float YCenter, float ZCenter, float ZBase, float Thickness, float Shrinkage, int Iterations, float *pAvgTime);
	IClusterFinder * iCl;
	ITrackFitter * iFt;
	ITrackFitter2 * iFt2;
	ITracker * iTk;
	ITracker2 * iTk2;
	IObjective * iOb;
};

#endif // !defined(AFX_TRACKER_H__D1ED07C1_EAA2_11D3_BF7F_002018B80960__INCLUDED_)
