#ifndef _SYSAL_ODYSSEY_DATA_
#define _SYSAL_ODYSSEY_DATA_

#include "Config.h"
#include "Globals.h"
#include "AsyncVisionProcessorDefs.h"

#define ODYSSEY_GRAB_PAGE_NUM 1
#define ODYSSEY_IMAGE_DEPTH 8L

#define ODYSSEY_CURSOR_HEADER_STRING_LENGTH 8

#define ODYSSEY_TRANSPARENT 0xFF
#define ODYSSEY_GRABMIN 0x10

#define ODYSSEY_BLACK 0x0
#define ODYSSEY_DKBLUE 0x01
#define ODYSSEY_DKGREEN 0x02
#define ODYSSEY_DKCYAN 0x03
#define ODYSSEY_DKRED 0x04
#define ODYSSEY_DKMAGENTA 0x05
#define ODYSSEY_DKYELLOW 0x06
#define ODYSSEY_DKGRAY 0x07
#define ODYSSEY_LTGRAY 0x08
#define ODYSSEY_LTBLUE 0x09
#define ODYSSEY_LTGREEN 0x0A
#define ODYSSEY_LTCYAN 0x0B
#define ODYSSEY_LTRED 0x0C
#define ODYSSEY_LTMAGENTA 0x0D
#define ODYSSEY_LTYELLOW 0x0E
#define ODYSSEY_WHITE 0x0F

#define MAX_XOP_BUFFERS 16
#define MAX_KERNEL_SIZE 8
#define MAX_PROGRAMS 8
/* Note: MAX_FRAMES_PER_NODE should never be less than 8 */
#define MAX_FRAMES_PER_NODE 128
#define MAX_OPTIMIZABLE_FRAMES_PER_NODE 32
#define MAX_CLUSTERING_PROCESSORS 8

#define XOP_TYPE_COPY	1
#define XOP_TYPE_HFLIP	2
#define XOP_TYPE_VFLIP	3
#define XOP_ROTATE_90	4
#define XOP_ROTATE_180	5
#define XOP_ROTATE_270	6

char *XopTypeName(int t);

struct t_ExtendedOperation
{
	struct t_OpDesc
	{
		int Count;
		struct t_Desc
		{
			RECT Src;
			RECT Dest;
			int Type;
			} Desc[MAX_XOP_BUFFERS];
		} OpDescriptions;

	t_ExtendedOperation &operator<<(SySalConfig &C);
	t_ExtendedOperation &operator>>(SySalConfig &C);
	};

struct t_VisionProcessorLibrary
{
	struct t_Program
	{
		UINT OffX, OffY;
		UINT WinWidth, WinHeight;
		int Threshold;
		UCHAR KWidth, KHeight;
		char KernelDesc[MAX_KERNEL_SIZE * MAX_KERNEL_SIZE / 4];
		char FlatFieldImage[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
		char FilterEqImage[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
/* TEMPORARY!!! */
		int LastThreshold;		
/* End TEMPORARY */
		} Programs[MAX_PROGRAMS];
	UINT Count;

	t_VisionProcessorLibrary &operator<<(SySalConfig &C);
	t_VisionProcessorLibrary &operator>>(SySalConfig &C);
	};

struct t_LightControlSettings
{
	UINT MinLev, MaxLev;
	float TargetGrayLev;
	UINT SaturationGrayLev;
	float TargetSaturationFraction;
	UINT LampTimeConstant;	

	t_LightControlSettings &operator<<(SySalConfig &C);
	t_LightControlSettings &operator>>(SySalConfig &C);
	};

struct t_GeneralSettings
{
	int ClusteringProcessors;
	int RefreshCycleTime;
	float ProcessingStartDelayPerFrame;

	t_GeneralSettings &operator<<(SySalConfig &C);
	t_GeneralSettings &operator>>(SySalConfig &C);
	};

struct OdysseyData
{	
	/* Region: Main data about the Odyssey grabbing functions */

	int CommandQueueLength;
	long Dev;
	long ProcSys;
	long GrabThread;
	long ProcThread;
	long ProcOSB;
	long Cam;
	long ConvBuff;
	long ConvResBuffs[2][MAX_OPTIMIZABLE_FRAMES_PER_NODE];
	long BinBuff;
	long LUTBuff;	
	t_GeneralSettings GeneralSettings;

	/* End region */

	/* Region: Data for VisionProcessor / VisionProcessor2 operation */

	long SrcGrabBuffs[3]; // a useful mirror name for child buffers in the SeqMainBuff
	long HostBinBuffs[2]; // a useful mirror name for child buffers in the SeqMainHostBinBuff
	BYTE *pHostBinBuffs[2]; // a useful mirror name for the mapped buffers in SeqMainHostBinBuff
	long GrabOSB[2];
	int ActiveProgram;
	int CycleParity;
	int CutOff;
	unsigned OffX, OffY, WinWidth, WinHeight;
	bool Locked;
	Segment *SegSpace;	
	UINT FrameCount;
	void (*pFrameStartCallBack)(DWORD);
	DWORD Context;
	t_ExtendedOperation ExtendedOperation;
	t_VisionProcessorLibrary ProgramLibrary;
	long KernelBuffs[MAX_PROGRAMS];
	long FlatFieldBuffs[MAX_PROGRAMS];
	long FilterEqBuffs[MAX_PROGRAMS];
	long XopSrcBuffs[2][MAX_FRAMES_PER_NODE][MAX_XOP_BUFFERS];
	long XopDestBuffs[2][MAX_FRAMES_PER_NODE][MAX_XOP_BUFFERS];

	/* End region */

	/* Region: Data for VisionProcessor3 (asynchronous) operation */
	
	long LUTOSB;
	BYTE *pLUT;
	long SeqStartThread;
	long SeqOSB;
	long SeqMainBuff[2];
	long SeqChildBuffs[2][MAX_FRAMES_PER_NODE];
	long SeqCtlBuff;
	long SeqStartTimeBuff;
	long SeqEndTimeBuff;
	double *pSeqStartTimeBuff;
	double *pSeqEndTimeBuff;
	long SeqMainHostBinBuff[2];
	long SeqChildHostBinBuffs[2][MAX_FRAMES_PER_NODE];
	BYTE *pSeqChildHostBinBuffs[2][MAX_FRAMES_PER_NODE];
	double SeqTimeZero[2];
	struct t_SequenceProgram
	{
		int ActiveProgram;
#define VP_PROGRAM_NULL			0
#define VP_PROGRAM_VALID		1
#define VP_PROGRAM_RUNNING		2
#define VP_PROGRAM_CLUSTERING	3
		int Status;
		AsyncImageSequence AIS;
		bool ProcessingProgrammed;
		} SequencePrograms[3];
	int SequenceIndex;
	int ClusteringSequenceIndex;
	HANDLE HTerminate;
	HANDLE HStart;
	HANDLE HReset;
	struct t_ActivationRecord
	{
		int ThreadIndex;
		HANDLE HThread;
		HANDLE HFinished;
		OdysseyData *pO;
		} ActivationRecords[MAX_CLUSTERING_PROCESSORS];

	/* End region */

	/* Region: Data for FrameGrabber operations */

	long Display;
	long DisplayCtlBuff;
	long DisplayHostBuff;
	BYTE *pDisplayHostBuff;
	long GrabBuff;	// a useful mirror name for the first child buffer in SeqMainBuff
	long FreezeBuff;
	BYTE *pFreezeBuff;
	long UnderlayBuff;
	int GrabMode;
	long GraphicsBuff;
	long GraColorBuff;
	long OverlayBuff;
	long CursorBuff;
	long CursorSaveArea;
	long OverlayLUT;
 	int CursorX, CursorY;
 	int CursorAlignX, CursorAlignY;
 	int CursorWidth, CursorHeight;
 	bool IsThereCursor;
	bool IsCursorAreaValid;
 	bool CursorVisible;
	int ImageWidth, ImageHeight;
	HANDLE HRefreshThread;
	HANDLE HRefreshStart;
	HANDLE HRefreshStopped;
	HANDLE HTerminateRefresh;
	BYTE OvrColors[3 * 256];		
	bool Initialization;

	/* End region */

	/* Region: Data for Automatic light control operation */

	t_LightControlSettings LightControlSettings;
	long HistoBuff;
	int *pHistoBuff;

	/* End region */
	};

#endif