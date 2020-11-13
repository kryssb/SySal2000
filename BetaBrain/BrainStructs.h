#ifndef _SYSAL_BETA_BRAIN_STRUCTURES_
#define _SYSAL_BETA_BRAIN_STRUCTURES_

#include "StdAfx.h"
#include "..\Common\datastructs.h"
#include "..\Common\IO.h"
#include "..\Common\Objective.h"
#include "..\Common\ClusterFinder.h"
#include "..\Common\Tracker.h"
#include "..\Common\Fitter.h"
#include "..\Common\SheetMap.h"
#include "..\Common\FrameGrabber.h"
#include "..\Common\Stage.h"
#include "..\Common\CameraSpec.h"
#include "..\Common\Vectors.h"
#include "BatchMonitor.h"
#include "ClusterDumpMonitor.h"
#include "PhotoSeqMonitor.h"
#include "ScanTracksMonitor.h"

// Scanning Status

struct BScanStatus
{
	int CurrentCommand;
	int TracksScanned;
	int TracksFound;
	int FocusFaults;
	int StageFaults;
	int TimeElapsed;
	int PhotoSequences;	
	int ClusterDumps;

	int StartTime;

	void Reset()
	{
		CurrentCommand = 0;
   		TracksScanned = 0;
   		TracksFound = 0;
   		FocusFaults = 0;
   		StageFaults = 0;
   		TimeElapsed = 0;
   		PhotoSequences = 0;
   		ClusterDumps = 0;

		StartTime = GetTickCount();
   		};

	int UpdateTime()
	{	return TimeElapsed = GetTickCount() - StartTime; };

	char *GenerateReport();
	};

// Setup Data Groups

#define FILETEXTLIMIT 512

namespace DataGroups
{

	struct Mod
	{
		int MaxClusters;
		int MaxTracks;
		int MaxFlatTracks;
		};

	struct Emu
	{
		float TopThickness;
		float BottomThickness;
		float BaseThickness;
		float Shrinkage;
		float Height;
		float Width;
		float DepthCoherenceLength;
		float DistortionCellSize;
		};

	struct Side
	{
		int ClusterContrast;
		int ClusterThreshold;
		int MaxLayers, StartLayer, EndLayer;
		int PixMin, PixMax;
		int MaxFlatStripsPerTrack;
		};

	struct Stage
	{
		float FocusTolerance, ThicknessTolerance;
		float ScanningSpeed, ScanningStep, BaseCrossingSpeed, RewindSpeed;
		float SlowdownLength;
		float XStep, YStep;
		float XTolerance, YTolerance, ZTolerance, ZStaticTolerance;
		float LongDistAcc, ShortDistAcc;
		float HorizontalSpeed;
		float ZAcc;
		float RelaxTime, WaitForLimiterResetTime;
		};

	struct Opt
	{
		int RelativeClusterThreshold;
		int ScanTop, ScanBottom, ScanBoth;
		int PauseEachField;
		int CenterScanBack;
		float XCenterTol, YCenterTol;
		int AutoLightControl;
		int MinGrayLev, TargetGrayLev;
		int MinLight, MaxLight, LightIncrement, LampDelay;
		int CorrectPredictions;
		int MinSample;
		};

	struct Seeker
	{
		float PosTolerance;
  		int CheckTop, CheckBottom;
		int ZoneScanning;
		int ZoneXFields, ZoneYFields;
		};

	struct Path
	{
		char PathFileName[FILETEXTLIMIT];
		int XFields, YFields;
		};

	};

struct TrackPrediction
{
	Identifier ID;
	UINT MapN;
	struct
	{
		float Y;
		float Z;
		} Pos;
	struct
	{
		struct
		{
			float Y;
			float Z;
			} Top, Bottom, Global;
		} Slope;
	float SideSlopeTolerance;
	float GlobalSlopeTolerance;
	float GoodSlopeTolerance;
	};

struct ScanResult
{
	TrackPrediction Pred;
	struct
	{
		bool IsValid;
		struct
		{
			float Y;
			float Z;
			} Pos;
		struct
		{
      		struct
			{
				float Y;
   				float Z;
				} Global;
			} Slope;
		} Found;
	};

struct Command
{
	int OpCode;
	int Priority;
	union
	{
		TrackPrediction ScanTracks;

		struct t_PhotoSequence
		{
			Identifier ID;
			UINT MapN;
			struct t_Pos
			{
         		float Y;
				float Z;
				float StartDepth;
				float EndDepth;
				int Frames;
         		} Pos;
			struct t_ImageSize
			{
				int Width;
				int Height;
         		} ImageSize;
			} PhotoSequence;

		struct t_ClusterDump
		{
			Identifier ID;
			UINT MapN;
			struct t_Pos
			{
         		float Y;
				float Z;
				float StartDepth;
				float EndDepth;
				int Frames;
         		} Pos;
			int GrayStep;
      		} ClusterDump;
   		} Parameters;
	};

class CommandQueue
{
	private:

   		ISySalDataIO *ICS;
		CWnd *Parent;

		Command LastImmediate;

		struct QueueItem
		{
      		Command Info;
			QueueItem *Next;
      		};

		QueueItem *Head;
		QueueItem *Tail;

		Command GetFromStream();
		Command GetFromDialog();

		Command PeekNext();

	public:

		CommandQueue(CWnd *parent, ISySalDataIO *ics);
		~CommandQueue();

		int PeekLastImmediate();
		Command GetNext();
		bool ImmediateCommandWaiting();
		void ReleaseImmediate();
		void QueueCommand(Command &C);

	};

struct FocusDepths
{
	float TopExt;
	float TopInt;
	float BottomInt;
	float BottomExt;
	};

struct LocalFocusDepths : public FocusDepths
{
	int HitCount;
	};

struct DistortionCell
{
	int HitCount;
	float DeltaX, DeltaY;
	};

using namespace DataGroups;

struct SetupData
{
	Mod ModD;
	Emu EmuD;
	Side TopD;
	Side BottomD;
	Stage StageD;
	Opt OptD;
	Seeker SeekerD;
	Path PathD;
	};

class CScanner
{
	protected:
		void FlushConfig();

		CString Name;

		IFrameGrabber *iFG;
		IStage *iSt;
		ISySalObject *iStMon;
		IObjective *iOb;
		IClusterFinder *iCl;
		ILockUnlock *iLC;
		ITracker *iTk;
		ITracker2 *iTk2;
		ITrackFitter *iFt;
		ITrackFitter2 *iFt2;
		ISheetMap *iS1, *iS2, *iS3, *iSM;
		ISySalDataIO *iICS, *iOCS, *iIO;

		CameraSpec CAM;

		SetupData SD;
	
		Cluster *CSpace;
		FlatStrip *FSSpace[2];
		FlatTrack *FTSpace[2];
		Track *TSpace[2];
		int FTCount[2];
		int TCount[2];
		Vector *GSpace[2];
		void *FCSpace[4];
		int LCount;

		CommandQueue *Master;

		struct
		{
			CWinThread *pThread;
			CBatchMonitor *pBatchMon;
			HANDLE HMutex;
			HANDLE HInitCompleted;
			HWND *phWnd;
			} Monitor;
	
		bool *pTermination;
		HANDLE PauseEvent, *pHTerminateEvent;
		bool OverridePauseEachField;
		BScanStatus ScanStatus;

		struct BkGndTkInfo
		{
			CWinThread *pTrackingThread;
			HANDLE HStartStop;
			HANDLE HFinished;
			HANDLE HExit;

			int Side;
			int Field;
			int StartLayer;
   			int EndLayer;
   			int TracksFoundCount;
			int FlatTracksFoundCount;
			double ActX, ActY;
			float CamCX, CamCY;
			float Shrinkage;
			float BaseDepth;
			float EmThick;
			} BackGroundTrackingInfo;

		struct
		{
			float Left, Right;
			float Top, Bottom;
			} EmuEdges;
		int LFD_XCount, LFD_YCount;
		LocalFocusDepths *FocusInfo;

		double *FitWorkSpace[2];

		struct
		{
			bool IsReliable;
			int CountOfCellsX, CountOfCellsY;
			float CellSize;
			DistortionCell *Cells;
			} PredCorrection;

		UINT MonitorThread();
		UINT TrackerThread();

		TrackPrediction CorrectPrediction(TrackPrediction &Original);
		void ResetPredictionCorrections();
		bool AddPredictionsCorrection(int ScanCount, ScanResult *Batch);
		void RearrangePredictions(int PredCount, ScanResult *Batch);

		ISheetMap *Select_Map(UINT MapN);
		bool Scan_ClustersDump(Command *Cmd);
		bool Scan_PhotoSequence(Command *Cmd);
		bool Scan_Tracks(Command *Cmd, ScanResult *ScanReport, bool Retry = false);
		bool Load_and_Exec(Command *Cmd);

		bool SharpPosition(float x, float y, float speed, float acc, float xtol, float ytol, float z, float zspeed, float zacc, float ztol, int retry = 0);
	
		DWORD Scan_Top(int Field, FocusDepths BestKnown, FocusDepths *BestFound, bool ReFocus);
		DWORD Scan_Bottom(int Field, FocusDepths BestKnown, FocusDepths *BestFound, bool ReFocus, bool WaitZ);
		int CountGrains(int CCount, int MinPixels, int MaxPixels);

		void SetLightLevel();
		float EvalGrayLev(BYTE *Image);

		bool SeekTopSurface(int GThresh, int MaxClusters, int CThresh, int PixMin, int PixMax, float Tolerance, float *FoundZ);

		bool CheckSideSwap(FocusDepths *NewFocus);
		int GetGrains(int GThresh, int MaxClusters, float BeginPos, float EndPos, float EndPosTol, int PixMin, int PixMax, int CThresh, float *EndZ, bool NoFocus);

		void CreateBkGndTracking();
		void StartBkGndTracking();
		void WaitForBkGndTracking();
		void TerminateBkGndTracking();

		void RestorePriorities();

		void TracksToWorld(ISheetMap *iSM, double actx, double acty, float camcx, float camcy, float basedepth, Track *TSpace, int TCount);
		void FlatTracksToWorld(ISheetMap *iSM, double actx, double acty, float camcx, float camcy, float basedepth, FlatTrack *FTSpace, int FTCount);
		int DiscardInvalidTracks(Track *TSpace, int TCount, int FitCorrectionDataSize);
		int DiscardInvalidFlatTracks(FlatTrack *FTSpace, int FTCount, int FitCorrectionDataSize);

		FocusDepths GetNextFocusDepths(float YPos, float ZPos, float ActX, float ActY);
		bool AddFocusInfo(float X, float Y, FocusDepths F);

		void ShowTracks(ISheetMap *iSM, Track *TSpace, int TCount, FlatTrack *FTSpace, int FTCount, double OtherZ, int Side, bool ShowFits);

		void UpdateGlobal();
		void DisableAllMonitors();
		void EnableScanTracksMonitor();
		void EnablePhotoSeqMonitor();
		void EnableClusterDumpMonitor();

		DWORD Free();
		DWORD Init(char *name, IFrameGrabber *ifg, IStage *ist, IObjective *iob, 
			IClusterFinder *icl, ITracker *itk, ITrackFitter *ift, ISheetMap *is1, 
			ISheetMap *is2, ISheetMap *is3, ISySalDataIO *iio, SetupData sd);

	public:
		DWORD Exec(HANDLE *phterminateevent, HWND *phwnd, char *name, IFrameGrabber *ifg, IStage *ist, IObjective *iob, 
			IClusterFinder *icl, ITracker *itk, ITrackFitter *ift, ISheetMap *is1, 
			ISheetMap *is2, ISheetMap *is3, ISySalDataIO *iio, SetupData sd, bool Batch);
	
		CScanner();
		virtual ~CScanner();

		static UINT WINAPI MonitorThreadHook(void *pOwner);
		static UINT WINAPI TrackerThreadHook(void *pOwner);

#ifndef IMPLEMENT_MON_COMMANDS_AS_DEFINES
	protected:

		void CDM_SET_ID(Identifier id);
		void CDM_SET_POSXY(float x, float y);
		void CDM_SET_STARTENDDEPTH(float s, float e);
		void CDM_SET_FRAMEDEPTH(int f, float d);
		void CDM_SET_ACTION(int a);
		void CDM_SET_CLUSTERS(int c);
		
		void PSM_SET_ID(Identifier id);
		void PSM_SET_POSXY(float x, float y);
		void PSM_SET_STARTENDDEPTH(float s, float e);
		void PSM_SET_FRAMEDEPTH(int f, float d);
		void PSM_SET_ACTION(int a);

		void STM_SET_ID(Identifier id);
		void STM_SET_POSXY(float x, float y);
		void STM_SET_SLOPEXY(float x, float y);
		void STM_SET_SIDEFIELD(int s, int f);
		void STM_SET_ACTION(int a);
		void STM_SET_LIGHTLEVEL(int l);
		void STM_SET_CLUSTERSLAYER(int c, int l);
		void STM_SET_TRACKS(int t, int b);
		void STM_SET_TOPFOCUS(float t, float r);
		void STM_SET_BOTTOMFOCUS(float t, float b);

		void GM_SET_STARTTIME(int x);
		void GM_SET_TOTALENTRIES(int x);
		void GM_SET_TIMETOCOMPL(int x);
		void GM_SET_ENTRIES(int x);
		void GM_SET_TKSFNDSCAN(int x, int y);
		void GM_SET_PHOTOSEQS(int x);
		void GM_SET_CLUSTERDUMPS(int x);
		void GM_SET_FOCUSFAULTS(int x);
		void GM_SET_STAGEFAULTS(int x);

#endif

	};


#define SCANNER_NO_ERROR			0
#define SCANNER_UNKNOWN_ERROR		-1
#define SCANNER_OUT_OF_MEMORY		0x10
#define SCANNER_NO_INIT				0x100
#define SCANNER_WRONG_INIT			0x101
#define SCANNER_TOO_MANY_OBJECTS	0x200
#define SCANNER_TOO_MANY_LAYERS		0x400


#endif