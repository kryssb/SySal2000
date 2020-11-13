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
#include "Stage2.h"
#include "FrameGrabber.h"
#include "VisionProcessor4.h"
#include "SheetMap.h"
#include "ConfigData.h"
#include "datastructs.h"
#include "CameraSpec.h"
#include "CameraSpec2.h"
#include "VSRawData.h"
#include "AsyncVisionProcessorDefs.h"
#include "AsyncStageDefs.h"
#include "AutomaticLightControl.h"


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
#define FOCUS_LOCK_CENTERVALLEY			2

#define SEEK_SURFACE_ADJUST				0
#define SEEK_SURFACE_THICKNESS			1
#define SEEK_SURFACE_FOCUS				2

class CVertigoScanner  
{
	protected:
		virtual void WaitForProcessingComplete();
		int FindValley(AsyncImageSequence &AIS, int top, int bottom);
		bool GetPrevView(int currfield, bool curristop, int &prevfield, bool &previstop);
		bool GetNextView(int currfield, bool curristop, int &nextfield, bool &nextistop);
		UINT PrepareTrajectory(VS_View2::t_RelevantZs2 &RelZ, int NextField, bool NextIsTop);
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
		IStage2 *iSt;
		ISySalDataIO2 *iIO;
		ITracker3 *iTk[2];
		ITrackFitter3 *iFt[2];
		IFrameGrabber *iFG;
		IVisionProcessor3 *iVP;
		ISySalObject *iStOb;
		ISheetMap *iSM;
		IAutomaticLightControl *iLC;

		UINT FitCorrectionDataSize;

		struct t_ProcessVariables
		{
			bool PreserveClusters;
			int Field;
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
//			float DZLayers;
//			float DAQSpeed;
			int FieldDelay;
			UINT TCount[2];
			UINT CCount;
			UINT LastLimiterTime;
			UINT FocusSamples;
			bool XLimiter, YLimiter, ZLimiter;

			int AsyncImageIndex;
			AsyncImageSequence *pAIS;
			AsyncImageSequence FocusAIS;
			struct t_FieldSideRec
			{
				int Field;
				int Side;				
				} *pFieldSideRec;
			AsyncZScanTrajectory *pAZT;
			AsyncZScanTrajectory FocusAZT;

			int ValidLayers;
			} ProcessVariables;

		virtual UINT XYZMotionNotify();
		virtual UINT ZScanNotify();
		virtual UINT BaseCrossingNotify();
		virtual UINT FittingNotify();
		virtual UINT TrackingNotify();
		virtual UINT ImageProcessingNotify();
		virtual UINT FrameNotify();
		virtual UINT ClusteringNotify();
		virtual UINT StartNotify();
	
		virtual UINT Scan(float startx, float starty, bool xforward = true, bool yforward = true);
		virtual UINT GetRelevantZs(VS_View2::t_RelevantZs2 &F, UINT field, bool istop);
		virtual UINT GetFocus(float TargetX, float TargetY, VS_View2::t_RelevantZs2 &F);
		UINT SeekSurface(bool IsTop, TVector Start, int mode, float *pTopZ, float *pBottomZ, int *pValid);

		virtual bool ShouldPause();
		virtual bool ShouldContinue();
		virtual bool ShouldStop();

		virtual UINT Init();
		virtual UINT Free();

		static void ReadPosCallBack(DWORD Owner);
		float *pLoc;

		static bool ShouldStopCallback(DWORD Context);
		static float FindZInSampleSequence(float time, AsyncZScanTrajectory *pAZT);

		void CheckIntegrity();

	public:

		CVertigoScanner(ISySalObject *iself, ISySalDataIO2 *iio, IStage2 *ist,
			IObjective *iOb, IFrameGrabber *ifg, IVisionProcessor3 *ivp, 
			ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *itk2, ITrackFitter3 *ift2, 
			ISheetMap *ism, ConfigData &c);
		virtual ~CVertigoScanner();

};

#endif // !defined(AFX_VERTIGOSCANNER_H__F73E86D2_345D_4163_94FE_6FE7EFDF9941__INCLUDED_)
