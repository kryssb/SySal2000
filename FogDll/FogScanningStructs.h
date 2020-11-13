

#if !defined( _FOG_SCANNING_STRUCTURES_)
#define _FOG_SCANNING_STRUCTURES_

struct SScanningPoint;

//#include "common.h"
#include "GrainFinder.h"


struct SScanningPoint
{
	float StepX;
	int NumStepX;
	float StepY;
	int NumStepY;
	float X;
	float Y;
	int ResumedX;
	int ResumedY;
	UINT Options;
	CString Directory;
	CString FileNames;
	SScanningPoint * pPrevious;
	SScanningPoint * pNext;
	STrackingInfo * pTrackingInfo;
	SMicroParameters * pMicroParameters;
	SGrainFinderParameters * pGrainFinderParameters;
	SScanningPoint():FileNames(),Directory(),StepX(0),StepY(0),NumStepX(0),NumStepY(0),X(0),Y(0),pPrevious(NULL),
	pNext(NULL),pTrackingInfo(NULL),pMicroParameters(NULL),pGrainFinderParameters(NULL){};
	void Delete();
	void AddPoint(SScanningPoint * pNewPoint);
	UINT Save(FILE * pFile);
	UINT Load(FILE * pFile);
};


































#endif