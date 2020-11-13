// VertigoScanner.h: interface for the CVertigoScanner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERTIGOSCANNER_H__F73E86D2_345D_4163_94FE_6FE7EFDF9941__INCLUDED_)
#define AFX_VERTIGOSCANNER_H__F73E86D2_345D_4163_94FE_6FE7EFDF9941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "Objective.h"
#include "IO.h"
#include "Tracker.h"
#include "Fitter.h"
#include "Stage.h"
#include "FrameGrabber.h"
#include "VisionProcessor2.h"
#include "AutomaticLightControl.h"
#include "SheetMap.h"
#include "ConfigData.h"
#include "datastructs.h"
#include "CameraSpec.h"
#include "CameraSpec2.h"
#include "VSRawData.h"

#define SCANNING_SCHEME_TOPSIDE			0
#define SCANNING_SCHEME_BOTTOMSIDE		1
#define SCANNING_SCHEME_BOTH_IN_FIELD	2
#define SCANNING_SCHEME_TWO_SIDES		3

#define VSERR_OK						0x00000000
#define VSERR_WRONG_CONN				0x01000000
#define VSERR_WRONG_CONFIG				0x02000000
#define VSERR_MEMORY_ALLOC				0x03000000
#define VSERR_SCANNING_ERROR			0x04000000
#define VSERR_IO_ERROR					0x05000000
#define VSERR_CANTRUN					0xFE000000
#define VSERR_UNKNOWN					0xFFFFFFFF

#define FOCUS_LOCK_BASE					0
#define FOCUS_LOCK_CENTERLEVEL			1

class CVertigoScanner  
{
	protected:
		virtual void VPUnlock();
		virtual void VPLock();
		virtual UINT FocusEndNotify();
		virtual UINT FocusStartNotify();
		void XYOffset(Track2 *pTracks, UINT Count);
		void ZExpand(Track2 *pTracks, UINT Count, float ZBase);
		UINT DiscardInvalidTracks(Track2 *pTracks, UINT Count);
		virtual UINT EndNotify();
		virtual UINT FieldStartNotify();
		CameraSpec2 CSP;
	
		bool LightSet;

		float ViewCenterX, ViewCenterY;

		ConfigData & C;

		IO_VS_Fragment2 Frag;

		Track2 *pTSpace;
		BYTE *pCorrSpace;
		Grain *pPSpace;
		Cluster *pCSpace;
		VS_View2 *pVSpace;
		VS_View2::t_LayerInfo *pLSpace;

		ISySalObject *iSelf;
		IObjective *iOb;
		IStage *iSt;
		ISySalDataIO2 *iIO;
		ITracker3 *iTk[2];
		ITrackFitter3 *iFt[2];
		IFrameGrabber *iFG;
		IAutomaticLightControl *iLC;

		union
		{
			IVisionProcessor *iVP;
			IVisionProcessor2 *iVP2;
			};
		bool UseVP2;
		ISySalObject *iStOb;
		ISheetMap *iSM;

		UINT FitCorrectionDataSize;

		struct t_ProcessVariables
		{
			UINT Field;
			bool IsTop;
			UINT Layer;
			struct t_Rec
			{
				UINT Count;
				float Z;
				} *pRec;
			float StageX, StageY;
			float StartX, StartY, StartZ;
			float TargetX, TargetY, TargetZ;
			float X, Y, Z;
			float DZLayers;
			float DAQSpeed;
			UINT TopFrameDelay;
			UINT BottomFrameDelay;
			UINT FocusFrameDelay;
			UINT TCount[2];
			UINT CCount;
			UINT LastLimiterTime;
			UINT FocusSamples;
			bool XLimiter, YLimiter, ZLimiter;

			Cluster *pTempCSpace;
			} ProcessVariables;

		virtual UINT XYMotionNotify();
		virtual UINT ZRewindNotify();
		virtual UINT BaseCrossingNotify();
		virtual UINT FittingNotify();
		virtual UINT TrackingNotify();
		virtual UINT ImageProcessingNotify();
		virtual UINT FrameNotify();
		virtual UINT GrabbingNotify();
		virtual UINT StartNotify();
	
		virtual UINT Scan(float startx, float starty, bool xforward = true, bool yforward = true);
		virtual UINT GetRelevantZs(VS_View2::t_RelevantZs2 &F, UINT field, bool istop);
		virtual UINT GetFocus(float TargetX, float TargetY, VS_View2::t_RelevantZs2 &F);

		virtual bool ShouldPause();
		virtual bool ShouldContinue();
		virtual bool ShouldStop();

		virtual UINT Init(bool bAllocateClusterSpace = false);
		virtual UINT Free();

		static void ReadPosCallBack(DWORD Owner);
		float *pLoc;

	public:

		CVertigoScanner(ISySalObject *iself, ISySalDataIO2 *iio, IStage *ist,
			IObjective *iOb, IFrameGrabber *ifg, IVisionProcessor *ivp, 
			ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *itk2, ITrackFitter3 *ift2, 
			ISheetMap *ism, ConfigData &c);
		virtual ~CVertigoScanner();

};

#endif // !defined(AFX_VERTIGOSCANNER_H__F73E86D2_345D_4163_94FE_6FE7EFDF9941__INCLUDED_)
