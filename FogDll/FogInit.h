
#pragma once
#ifndef FOG_FOGINITSTRUCT_INCLUDED
#define FOG_FOGINITSTRUCT_INCLUDED
#ifndef FOG_HOME
#include "Stage3.h"
#include "FrameGrabber.h"
#include "SySalObj2.h"
#include "FrameGrabber.h"
#include "VisionProcessor4.h"
#endif



struct SFogInit
{
	bool IsEmbedded;
	bool ScanningAvailable;
#ifndef FOG_HOME
	ISySalObject * iStOb;
	IStage2 * iSt2;
	ISySalObject * iOdyOb;
	IFrameGrabber * iFG;
	SFogInit():iStOb(0),iSt2(0),iOdyOb(0),iFG(0),IsEmbedded(false),ScanningAvailable(true){};
#else
	SFogInit():IsEmbedded(true),ScanningAvailable(false){};
#endif
};


#endif FOG_FOGINITSTRUCT_INCLUDED