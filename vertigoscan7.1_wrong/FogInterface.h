#include "Stage3.h"
#include "FrameGrabber.h"
#include "SySalObj2.h"
#include "FrameGrabber.h"
#include "VisionProcessor4.h"

//#include "FogInit.h"

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
			  )FogShow(IStage2 * iST, ISySalObject *iStOb, IFrameGrabber * iFG);


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
			  )FogTakeImages(IStage2 *iST, ISySalObject *iStOb, IFrameGrabber *iFG, int imcountperside, const char *outputpath, float mappedx, float mappedy, float topmaxz, float bottommaxz, double imxx, double imxy, double imyx, double imyy, float sbsx, float sbsy);

