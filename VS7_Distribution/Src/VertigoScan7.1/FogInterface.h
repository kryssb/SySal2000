
#ifndef FOG_HOME
#include "Stage3.h"
#include "FrameGrabber.h"
#include "SySalObj2.h"
#include "FrameGrabber.h"
#include "VisionProcessor4.h"
#include "id.h"
#endif

//#include "FogInit.h"


void _declspec(
#ifdef _BUILD_FOG_
			  dllexport
#else
			  dllimport
#endif			  
			  )FogShouldStop(bool stop);


int _declspec(
#ifdef _BUILD_FOG_
			  dllexport
#else
			  dllimport
#endif			  
			  )FogShow(
#ifndef FOG_HOME
			  IStage2 * iST, ISySalObject *iStOb, IFrameGrabber * iFG
#endif
			  );

#ifndef FOG_HOME
int _declspec(
#ifdef _BUILD_FOG_
			  dllexport
#else
			  dllimport
#endif			  
			  )FogGetQuantities(IStage2 * iST, ISySalObject *iStOb, IFrameGrabber * iFG, float & TopFog, float & TopMaxZ, float & TopMinZ, float & TopQuality, int & TopLight, float & BtmFog, float & BtmMaxZ, float & BtmMinZ, float & BtmQuality, int & BtmLight);


int _declspec(
#ifdef _BUILD_FOG_
			  dllexport
#else
			  dllimport
#endif			  
			  )FogTakeImages(IStage2 *iST, ISySalObject *iStOb, IFrameGrabber *iFG, const char *outputpath, float mappedx, float mappedy, float topmaxz, float bottommaxz, double imxx, double imxy, double imyx, double imyy, float sbsx, float sbsy, Identifier id);
#endif

