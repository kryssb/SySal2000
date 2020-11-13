#include "Stage3.h"
#include "FrameGrabber.h"
#include "SySalObj2.h"
#include "..\common\FrameGrabber.h"
#include "..\common\VisionProcessor4.h"

//#include "FogInit.h"

int __declspec(
#ifdef _BUILD_FOG_
			  dllexport
#else
			  dllimport
#endif			  
			  )FogGetQuantities(IStage2 * iST, ISySalObject *iStOb, IFrameGrabber * iFG, float & TopFog, float & TopMaxZ, float & TopMinZ, float & TopQuality, int & TopLight, float & BtmFog, float & BtmMaxZ, float & BtmMinZ, float & BtmQuality, int & BtmLight);

