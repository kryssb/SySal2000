#include "StdAfx.h"
#include "BrainStructs.h"
#include "CommandCodes.h"
#include "Command.h"
#include "ScanTracks.h"
#include "PhotoSeq.h"
#include "ClusterDump.h"
#include "FieldMap.h"
#include "ums.h"

#define LOCK_MONITOR WaitForSingleObject(Monitor.HMutex, INFINITE)
#define UNLOCK_MONITOR ReleaseMutex(Monitor.HMutex)

#define FOCUS_LIMITER 	 		-1
#define FOCUS_ENDSTROKE 		-2
#define FOCUS_TIMEOUT			-3
#define FOCUS_TERMINATE			-4
#define FOCUS_OK 				 0

#define SCAN_1_TERMINATED		-1
#define SCAN_1_NOFOCUS			1
#define SCAN_1_LIMITER			2
#define SCAN_1_TOOFAST			3
#define SCAN_1_OK				0
#define SCAN_1_NOTSCANNED		-1

const char C_STRING_SCANTRACKS[] = "scantracks";
const char C_STRING_PHOTOSEQ[] = "photoseq";
const char C_STRING_CLUSTERDUMP[] = "clusterdump";
const char C_STRING_LOADANDSCAN[] = "loadscantks";
const char C_STRING_LOADANDEXEC[] = "loadexec";
const char C_STRING_REPORT[] = "report";
const char C_STRING_EXIT[] = "exit";

const char INPUTSTREAM_ERROR_MSG[] = "failure for ERROR on INPUTSTREAM\n";
const char OUTPUTSTREAM_ERROR_MSG[] = "failure for ERROR on OUTPUTSTREAM\n";
const char WAITING_IMMEDIATE_MSG[] = "command received... waiting for completion of current task\n";

static char GlobalObjectMessage[128];
static char GlobalMsg[512];

static void delay(int del);

static char *skipblanks(char *string);

static char *gettoken(char *string, char end);

#ifdef IMPLEMENT_MON_COMMANDS_AS_DEFINES
// useful defines

#define CDM_SET_ID(id)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_ID0, id.Part[0]);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_ID1, id.Part[1]);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_ID2, id.Part[2]);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_ID3, id.Part[3]);\
	ReleaseMutex(Monitor.HMutex);\
	}

#define CDM_SET_POSXY(x, y)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_POSXY, *(WPARAM *)(&x), *(LPARAM *)(&y));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define CDM_SET_STARTENDDEPTH(s, e)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_STARTENDDEPTH, *(WPARAM *)(&s), *(LPARAM *)(&e));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define CDM_SET_FRAMEDEPTH(f, d)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_FRAMEDEPTH, *(WPARAM *)(&f), *(LPARAM *)(&d));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define CDM_SET_ACTION(a)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_ACTION, a);\
	ReleaseMutex(Monitor.HMutex);\
	}

#define CDM_SET_CLUSTERS(c)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_CLUSTERS, c);\
	ReleaseMutex(Monitor.HMutex);\
	}

#define PSM_SET_ID(id)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_ID0, id.Part[0]);\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_ID1, id.Part[1]);\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_ID2, id.Part[2]);\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_ID3, id.Part[3]);\
	ReleaseMutex(Monitor.HMutex);\
	}

#define PSM_SET_POSXY(x, y)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_POSXY, *(WPARAM *)(&x), *(LPARAM *)(&y));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define PSM_SET_STARTENDDEPTH(s, e)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_STARTENDDEPTH, *(WPARAM *)(&s), *(LPARAM *)(&e));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define PSM_SET_FRAMEDEPTH(f, d)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_FRAMEDEPTH, *(WPARAM *)(&f), *(LPARAM *)(&d));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define PSM_SET_ACTION(a)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_ACTION, a);\
	ReleaseMutex(Monitor.HMutex);\
	}

#define STM_SET_ID(id)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_ID0, id.Part[0]);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_ID1, id.Part[1]);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_ID2, id.Part[2]);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_ID3, id.Part[3]);\
	ReleaseMutex(Monitor.HMutex);\
	}

#define STM_SET_POSXY(x, y)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_POSXY, *(WPARAM *)(&x), *(LPARAM *)(&y));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define STM_SET_SLOPEXY(x, y)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_SLOPEXY, *(WPARAM *)(&x), *(LPARAM *)(&y));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define STM_SET_SIDEFIELD(s, f)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_SIDEFIELD, s, f);\
	ReleaseMutex(Monitor.HMutex);\
	}

#define STM_SET_ACTION(a)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_ACTION, a);\
	ReleaseMutex(Monitor.HMutex);\
	}

#define STM_SET_LIGHTLEVEL(l)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_LIGHTLEVEL, *(WPARAM *)(&l));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define STM_SET_CLUSTERSLAYER(c, l)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_CLUSTERSLAYER, *(WPARAM *)(&c), *(LPARAM *)(&l));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define STM_SET_TRACKS(t, b)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_TRACKS, t, b);\
	ReleaseMutex(Monitor.HMutex);\
	}

#define STM_SET_TOPFOCUS(t, r)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_TOPFOCUS, *(WPARAM *)(&t), *(LPARAM *)(&r));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define STM_SET_BOTTOMFOCUS(t, b)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_BOTTOMFOCUS, *(WPARAM *)(&t), *(LPARAM *)(&b));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define GM_SET_STARTTIME(x)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->PostMessage(UM_SET_STARTTIME, *(WPARAM *)(&x));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define GM_SET_TOTALENTRIES(x)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->PostMessage(UM_SET_TOTALENTRIES, *(WPARAM *)(&x));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define GM_SET_TIMETOCOMPL(x)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->PostMessage(UM_SET_TIMETOCOMPL, *(WPARAM *)(&x));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define GM_SET_ENTRIES(x)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->PostMessage(UM_SET_ENTRIES, *(WPARAM *)(&x));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define GM_SET_TKSFNDSCAN(x, y)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->PostMessage(UM_SET_TKSFNDSCAN, *(WPARAM *)(&x),  *(LPARAM *)(&y));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define GM_SET_PHOTOSEQS(x)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->PostMessage(UM_SET_PHOTOSEQS, *(WPARAM *)(&x));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define GM_SET_CLUSTERDUMPS(x)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->PostMessage(UM_SET_CLUSTERDUMPS, *(WPARAM *)(&x));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define GM_SET_FOCUSFAULTS(x)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->PostMessage(UM_SET_FOCUSFAULTS, *(WPARAM *)(&x));\
	ReleaseMutex(Monitor.HMutex);\
	}

#define GM_SET_STAGEFAULTS(x)\
{\
	WaitForSingleObject(Monitor.HMutex, INFINITE);\
	Monitor.pBatchMon->PostMessage(UM_SET_STAGEFAULTS, *(WPARAM *)(&x));\
	ReleaseMutex(Monitor.HMutex);\
	}

#else

// useful functions

void CScanner:: CDM_SET_ID(Identifier id)\
{\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_ID0, id.Part[0]);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_ID1, id.Part[1]);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_ID2, id.Part[2]);\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_ID3, id.Part[3]);\
	}

void CScanner:: CDM_SET_POSXY(float x, float y)\
{\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_POSXY, *(WPARAM *)(&x), *(LPARAM *)(&y));\
	}

void CScanner:: CDM_SET_STARTENDDEPTH(float s, float e)\
{\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_STARTENDDEPTH, *(WPARAM *)(&s), *(LPARAM *)(&e));\
	}

void CScanner:: CDM_SET_FRAMEDEPTH(int f, float d)\
{\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_FRAMEDEPTH, *(WPARAM *)(&f), *(LPARAM *)(&d));\
	}

void CScanner:: CDM_SET_ACTION(int a)\
{\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_ACTION, a);\
	}

void CScanner:: CDM_SET_CLUSTERS(int c)\
{\
	Monitor.pBatchMon->pClusterDumpMonitor->PostMessage(UM_SET_CLUSTERS, c);\
	}

void CScanner:: PSM_SET_ID(Identifier id)\
{\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_ID0, id.Part[0]);\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_ID1, id.Part[1]);\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_ID2, id.Part[2]);\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_ID3, id.Part[3]);\
	}

void CScanner:: PSM_SET_POSXY(float x, float y)\
{\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_POSXY, *(WPARAM *)(&x), *(LPARAM *)(&y));\
	}

void CScanner:: PSM_SET_STARTENDDEPTH(float s, float e)\
{\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_STARTENDDEPTH, *(WPARAM *)(&s), *(LPARAM *)(&e));\
	}

void CScanner:: PSM_SET_FRAMEDEPTH(int f, float d)\
{\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_FRAMEDEPTH, *(WPARAM *)(&f), *(LPARAM *)(&d));\
	}

void CScanner:: PSM_SET_ACTION(int a)\
{\
	Monitor.pBatchMon->pPhotoSeqMonitor->PostMessage(UM_SET_ACTION, a);\
	}

void CScanner:: STM_SET_ID(Identifier id)\
{\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_ID0, id.Part[0]);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_ID1, id.Part[1]);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_ID2, id.Part[2]);\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_ID3, id.Part[3]);\
	}

void CScanner:: STM_SET_POSXY(float x, float y)\
{\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_POSXY, *(WPARAM *)(&x), *(LPARAM *)(&y));\
	}

void CScanner:: STM_SET_SLOPEXY(float x, float y)\
{\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_SLOPEXY, *(WPARAM *)(&x), *(LPARAM *)(&y));\
	}

void CScanner:: STM_SET_SIDEFIELD(int s, int f)\
{\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_SIDEFIELD, s, f);\
	}

void CScanner:: STM_SET_ACTION(int a)\
{\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_ACTION, a);\
	}

void CScanner:: STM_SET_LIGHTLEVEL(int l)\
{\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_LIGHTLEVEL, *(WPARAM *)(&l));\
	}

void CScanner:: STM_SET_CLUSTERSLAYER(int c, int l)\
{\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_CLUSTERSLAYER, *(WPARAM *)(&c), *(LPARAM *)(&l));\
	}

void CScanner:: STM_SET_TRACKS(int t, int b)\
{\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_TRACKS, t, b);\
	}

void CScanner:: STM_SET_TOPFOCUS(float t, float r)\
{\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_TOPFOCUS, *(WPARAM *)(&t), *(LPARAM *)(&r));\
	}

void CScanner:: STM_SET_BOTTOMFOCUS(float t, float b)\
{\
	Monitor.pBatchMon->pScanTracksMonitor->PostMessage(UM_SET_BOTTOMFOCUS, *(WPARAM *)(&t), *(LPARAM *)(&b));\
	}

void CScanner:: GM_SET_STARTTIME(int x)\
{\
	Monitor.pBatchMon->PostMessage(UM_SET_STARTTIME, *(WPARAM *)(&x));\
	}

void CScanner:: GM_SET_TOTALENTRIES(int x)\
{\
	Monitor.pBatchMon->PostMessage(UM_SET_TOTALENTRIES, *(WPARAM *)(&x));\
	}

void CScanner:: GM_SET_TIMETOCOMPL(int x)\
{\
	Monitor.pBatchMon->PostMessage(UM_SET_TIMETOCOMPL, *(WPARAM *)(&x));\
	}

void CScanner:: GM_SET_ENTRIES(int x)\
{\
	Monitor.pBatchMon->PostMessage(UM_SET_ENTRIES, *(WPARAM *)(&x));\
	}

void CScanner:: GM_SET_TKSFNDSCAN(int x, int y)\
{\
	Monitor.pBatchMon->PostMessage(UM_SET_TKSFNDSCAN, *(WPARAM *)(&x),  *(LPARAM *)(&y));\
	}

void CScanner:: GM_SET_PHOTOSEQS(int x)\
{\
	Monitor.pBatchMon->PostMessage(UM_SET_PHOTOSEQS, *(WPARAM *)(&x));\
	}

void CScanner:: GM_SET_CLUSTERDUMPS(int x)\
{\
	Monitor.pBatchMon->PostMessage(UM_SET_CLUSTERDUMPS, *(WPARAM *)(&x));\
	}

void CScanner:: GM_SET_FOCUSFAULTS(int x)\
{\
	Monitor.pBatchMon->PostMessage(UM_SET_FOCUSFAULTS, *(WPARAM *)(&x));\
	}

void CScanner:: GM_SET_STAGEFAULTS(int x)\
{\
	Monitor.pBatchMon->PostMessage(UM_SET_STAGEFAULTS, *(WPARAM *)(&x));\
	}


#endif


// CommandQueue

CommandQueue::CommandQueue(CWnd *parent, ISySalDataIO *ics)
	: ICS(ics), Parent(parent)
{
	Head = Tail = 0;
	LastImmediate.OpCode = COMMAND_NULL;
	};

CommandQueue::~CommandQueue()
{
	while (Head)
	{
   		QueueItem *temp = Head->Next;
		delete Head;
		Head = temp;
   		};
	};

int CommandQueue::PeekLastImmediate()
{  
	if (!ICS) return COMMAND_NULL;
	if (LastImmediate.OpCode != COMMAND_NULL) return LastImmediate.OpCode;
	Command NewCommand = PeekNext();
	if (NewCommand.Priority != COMMAND_PRIORITY_IMMEDIATE) return COMMAND_NULL;
	return NewCommand.OpCode;
	};

Command CommandQueue::PeekNext()
{
	Command NewCommand;
	if (Head) return Head->Info;
	do
	{
   		if (ICS) NewCommand = GetFromStream();
		else NewCommand = GetFromDialog();

		if (NewCommand.OpCode != COMMAND_NULL)
      	switch (NewCommand.Priority)
	   	{
			case COMMAND_PRIORITY_IMMEDIATE:		return LastImmediate = NewCommand;

			case COMMAND_PRIORITY_QUEUED:			QueueItem *Place = new QueueItem;
      												Place->Info = NewCommand;
               										Place->Next = 0;
      												if (!Tail) Head = Tail = Place;
                           							else 
													{
														Tail->Next = Place;
                                 	         			Tail = Place;
														};
													break;
			};
   		}
	while (NewCommand.OpCode != COMMAND_NULL);
	Command RetCommand;
	if (Head) RetCommand = Head->Info;
	else RetCommand.OpCode = COMMAND_NULL;
	return RetCommand;
	};

Command CommandQueue::GetNext()
{
	Command RetCommand;
	if (LastImmediate.OpCode)
	{  
		RetCommand = LastImmediate;
   		ReleaseImmediate();
		return RetCommand;
		};
	RetCommand = PeekNext();
	if (RetCommand.Priority != COMMAND_NULL)
	{	
		if (RetCommand.Priority != COMMAND_PRIORITY_IMMEDIATE)
   		{	
			if (Head)
			{	
				QueueItem *temp = Head;
		   		Head = Head->Next;
      			delete temp;
				if (!Head) Tail = 0;
      			};
			}
		else ReleaseImmediate();
		};
	return RetCommand;
	};

void CommandQueue::ReleaseImmediate()
{	LastImmediate.OpCode = COMMAND_NULL; };

void CommandQueue::QueueCommand(Command &C)
{
	QueueItem *Place = new QueueItem;
    Place->Info = C;
    Place->Next = 0;
    if (!Tail) Head = Tail = Place;
    else 
	{
		Tail->Next = Place;
    	Tail = Place;
		};
	};

#define MAXCOMMLEN 256

Command CommandQueue::GetFromStream()
{
	unsigned char CommandString[MAXCOMMLEN];
	static int currlen = 0;
	int bytesread;
	Command Temp;
	Temp.OpCode = COMMAND_NULL;
	Temp.Priority = COMMAND_PRIORITY_QUEUED;
	bool MessageOk = false;
	do
	{
   		try
		{
			UINT ErrInfo = IODATA_EXT_ERROR_OK;
			if (ICS->Read((HSySalHANDLE)Parent->m_hWnd, (BYTE *)CommandString + currlen, &ErrInfo, 0) == S_OK)
			{
				bytesread = 1;
				if ((CommandString[currlen] < ' ') || (CommandString[currlen] > 127))
   				{
            		CommandString[currlen] = 0;
					MessageOk = true;
					}
				else MessageOk = false;
         		currlen++;
				}
			else 
			{
				bytesread = 0;
				if (ErrInfo != IODATA_EXT_ERROR_OK) throw ErrInfo;
				};
      		}
		catch (...)
		{
			return Temp;
      		};
   		}
	while ((currlen < (MAXCOMMLEN - 1)) && bytesread && !MessageOk);
	if (MessageOk)
	{
		CommandString[currlen + 1] = 0;
   		char *token = gettoken((char *)CommandString, ' ');
		if (!strcmpi(skipblanks(token), "immediate"))
   		{	
			Temp.Priority = COMMAND_PRIORITY_IMMEDIATE;
   			token = gettoken(0, ' ');
			}
   		else Temp.Priority = COMMAND_PRIORITY_QUEUED;

		if (!strcmpi(skipblanks(token), C_STRING_CLUSTERDUMP))
   		{	
			Temp.OpCode = COMMAND_CLUSTERDUMP;
      		if (sscanf(gettoken(0, 0), "%d,%d,%d,%d,%f,%f,%f,%f,%d,%d", &Temp.Parameters.ClusterDump.ID.Part[0],
         		&Temp.Parameters.ClusterDump.ID.Part[1], &Temp.Parameters.ClusterDump.ID.Part[2], &Temp.Parameters.ClusterDump.ID.Part[3],
				&Temp.Parameters.ClusterDump.Pos.Y, &Temp.Parameters.ClusterDump.Pos.Z, &Temp.Parameters.ClusterDump.Pos.StartDepth,
				&Temp.Parameters.ClusterDump.Pos.EndDepth, &Temp.Parameters.ClusterDump.Pos.Frames, &Temp.Parameters.ClusterDump.GrayStep) != 10)
      				Temp.OpCode = COMMAND_ERROR;
	   		}
		if (!strcmpi(skipblanks(token), C_STRING_PHOTOSEQ))
   		{	
			Temp.OpCode = COMMAND_PHOTOSEQ;
      		if (sscanf(gettoken(0, 0), "%d,%d,%d,%d,%f,%f,%f,%f,%d,%d,%d", &Temp.Parameters.PhotoSequence.ID.Part[0],
         		&Temp.Parameters.PhotoSequence.ID.Part[1], &Temp.Parameters.PhotoSequence.ID.Part[2], &Temp.Parameters.PhotoSequence.ID.Part[3],
      			&Temp.Parameters.PhotoSequence.Pos.Y, &Temp.Parameters.PhotoSequence.Pos.Z, &Temp.Parameters.PhotoSequence.Pos.StartDepth,
	      		&Temp.Parameters.PhotoSequence.Pos.EndDepth, &Temp.Parameters.PhotoSequence.Pos.Frames,
   				&Temp.Parameters.PhotoSequence.ImageSize.Width, &Temp.Parameters.PhotoSequence.ImageSize.Height) != 11)
      				Temp.OpCode = COMMAND_ERROR;
   			}
		else if (!strcmpi(skipblanks(token), C_STRING_SCANTRACKS))
   		{	
			Temp.OpCode = COMMAND_SCANTRACKS;
      		if (sscanf(gettoken(0, 0), "%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f", &Temp.Parameters.ScanTracks.ID.Part[0],
         		&Temp.Parameters.ScanTracks.ID.Part[1], &Temp.Parameters.ScanTracks.ID.Part[2], &Temp.Parameters.ScanTracks.ID.Part[3],
      			&Temp.Parameters.ScanTracks.Pos.Y, &Temp.Parameters.ScanTracks.Pos.Z, &Temp.Parameters.ScanTracks.Slope.Global.Y,
	      		&Temp.Parameters.ScanTracks.Slope.Global.Z, &Temp.Parameters.ScanTracks.SideSlopeTolerance,
   				&Temp.Parameters.ScanTracks.GlobalSlopeTolerance, &Temp.Parameters.ScanTracks.GoodSlopeTolerance) != 11)
      				Temp.OpCode = COMMAND_ERROR;
			else
   			{
      	 		Temp.Parameters.ScanTracks.Slope.Top = Temp.Parameters.ScanTracks.Slope.Global;
       			Temp.Parameters.ScanTracks.Slope.Bottom = Temp.Parameters.ScanTracks.Slope.Global;
	      		};
   			}
	  	else if (!strcmpi(skipblanks(token), C_STRING_LOADANDSCAN)) Temp.OpCode = COMMAND_LOAD_AND_SCAN;
	  	else if (!strcmpi(skipblanks(token), C_STRING_LOADANDEXEC)) Temp.OpCode = COMMAND_LOAD_AND_EXEC;
		else if (!strcmpi(skipblanks(token), C_STRING_REPORT)) Temp.OpCode = COMMAND_REPORT;
		else if (!strcmpi(skipblanks(token), C_STRING_EXIT)) Temp.OpCode = COMMAND_EXIT;
		currlen = 0;
		}
	else Temp.OpCode = COMMAND_NULL;
	return Temp;
	};

Command CommandQueue::GetFromDialog()
{
	Command Temp;
	Temp.Priority = COMMAND_PRIORITY_IMMEDIATE;
	CCommand MyDlg(Parent);
	switch (Temp.OpCode = MyDlg.DoModal())
	{
		case COMMAND_SCANTRACKS:	{
										Temp.Parameters.ScanTracks.MapN = 0;
										CScanTracks MyDlg(&Temp.Parameters.ScanTracks.Pos.Y,
				                         	&Temp.Parameters.ScanTracks.Pos.Z, &Temp.Parameters.ScanTracks.Slope.Global.Y,
					                        &Temp.Parameters.ScanTracks.Slope.Global.Z, &Temp.Parameters.ScanTracks.SideSlopeTolerance,
						                    &Temp.Parameters.ScanTracks.GlobalSlopeTolerance, &Temp.Parameters.ScanTracks.GoodSlopeTolerance,
											&Temp.Parameters.ScanTracks.ID, Parent);
										if (MyDlg.DoModal() != IDOK) Temp.OpCode = COMMAND_NULL;
										};
									break;

		case COMMAND_PHOTOSEQ:		{
										Temp.Parameters.PhotoSequence.MapN = 0;
										CPhotoSeq MyDlg(&Temp.Parameters.PhotoSequence.Pos.Y,
		                             		&Temp.Parameters.PhotoSequence.Pos.Z, &Temp.Parameters.PhotoSequence.Pos.StartDepth,
											&Temp.Parameters.PhotoSequence.Pos.EndDepth, (UINT *)&Temp.Parameters.PhotoSequence.Pos.Frames,
											(UINT *)&Temp.Parameters.PhotoSequence.ImageSize.Width, (UINT *)&Temp.Parameters.PhotoSequence.ImageSize.Height,
											&Temp.Parameters.PhotoSequence.ID, Parent);
										if (MyDlg.DoModal() != IDOK) Temp.OpCode = COMMAND_NULL;
										};
									break;

		case COMMAND_CLUSTERDUMP:	{
										Temp.Parameters.ClusterDump.MapN = 0;
										CClusterDump MyDlg(&Temp.Parameters.ClusterDump.Pos.Y,
											&Temp.Parameters.ClusterDump.Pos.Z, &Temp.Parameters.ClusterDump.Pos.StartDepth,
											&Temp.Parameters.ClusterDump.Pos.EndDepth, (UINT *)&Temp.Parameters.ClusterDump.Pos.Frames,
											(UINT *)&Temp.Parameters.ClusterDump.GrayStep, &Temp.Parameters.ClusterDump.ID, Parent);
										if (MyDlg.DoModal() != IDOK) Temp.OpCode = COMMAND_NULL;
										};
									break;

		case COMMAND_EXIT:			Temp.OpCode = COMMAND_EXIT;
									break;

		case COMMAND_LOAD_AND_SCAN:	Temp.OpCode = COMMAND_LOAD_AND_SCAN;
      								break;

		case COMMAND_LOAD_AND_EXEC:	Temp.OpCode = COMMAND_LOAD_AND_EXEC;
      								break;

		default:					Temp.OpCode = COMMAND_NULL;
      								break;
   		};
	return Temp;
	};

bool CommandQueue::ImmediateCommandWaiting()
{	return LastImmediate.OpCode != COMMAND_NULL; };

// BScanStatus

char *BScanStatus::GenerateReport()
{
	static char Temp[2048];
	UpdateTime();
	sprintf(Temp, "CurrentCommand: %d\rTracksScanned: %d\rTracksFound: %d\r"
   		"FocusFaults: %d\rStageFaults: %d\rTimeElapsed: %d\r"
        "PhotoSequences: %d\rClusterDumps: %d\r",
		CurrentCommand, TracksScanned, TracksFound, FocusFaults, StageFaults,
        TimeElapsed, PhotoSequences, ClusterDumps);
	return Temp;
	};

// Defines

#define SAFE_WRITE(stream, data, len)\
{	try\
	{\
		if (stream)\
		{\
			UINT ErrInfo;\
			stream->Write(NULL, (BYTE *)data, &ErrInfo, 0);\
			};\
		}\
	catch (...) {};\
	}


#define SAFE_WRITE_STRING(stream, data)\
{	int len = strlen(data);\
	data[len] = '\r';\
	data[++len] = '\0';\
	SAFE_WRITE(stream, data, len);\
	}

#define GENERATE_MSG(message)\
{\
	sprintf(GlobalMsg, "%s %s", GlobalObjectMessage, message);\
	SAFE_WRITE_STRING(iOCS, GlobalMsg);\
	}

#define GENERATE_EXIT_MSG(message, retcode)\
{\
	GENERATE_MSG(message);\
	return retcode;\
	}

/*	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS); */

// CScanner

UINT WINAPI CScanner::MonitorThreadHook(void *pOwner)
{
	return ((CScanner *)pOwner)->MonitorThread();
	};

UINT CScanner::MonitorThread()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Monitor.pBatchMon = new CBatchMonitor(Monitor.phWnd, pHTerminateEvent, 
		Monitor.HInitCompleted, &OverridePauseEachField, &SD.OptD.PauseEachField);
	Monitor.pBatchMon->DoModal();
	delete Monitor.pBatchMon;
	Monitor.pBatchMon = 0;
	return 0;
	};

UINT WINAPI CScanner::TrackerThreadHook(void *pOwner)
{
	return ((CScanner *)pOwner)->TrackerThread();	
	};

CScanner::CScanner()
	: iFG(0), iSt(0), iOb(0), iCl(0), iTk(0), iFt(0), 
	iS1(0), iS2(0), iS3(0), iIO(0), iStMon(0), iLC(0), iTk2(0), iFt2(0), 
	iICS(0), iOCS(0)
{
	Name = "";
	TSpace[0] = TSpace[1] = 0;
	GSpace[0] = GSpace[1] = 0;
	FTSpace[0] = FTSpace[1] = 0;
	FSSpace[0] = FSSpace[1] = 0;
	FCSpace[0] = FCSpace[1] = FCSpace[2] = FCSpace[3] = 0;
	CSpace = 0;
	FocusInfo = 0;
	FitWorkSpace[0] = FitWorkSpace[1] = 0;
	Monitor.pBatchMon = 0;
	};

CScanner::~CScanner()
{
	FlushConfig();
	// TODO
	// MORE FLUSHING (threads, etc.) NEEDED!!!
	};

DWORD CScanner::Init(char *name, IFrameGrabber *ifg, IStage *ist, IObjective *iob, 
	IClusterFinder *icl, ITracker *itk, ITrackFitter *ift, ISheetMap *is1, 
	ISheetMap *is2, ISheetMap *is3, ISySalDataIO *iio, SetupData sd)
{
	FlushConfig();

	iFG = ifg;
	iSt = ist;
	iOb = iob;
	iCl = icl;
	iTk = itk;
	iFt = ift;
	iS1 = is1;
	iS2 = is2;
	iS3 = is3;
	iIO = iio;
	SD = sd;
	Name = name;


	sprintf(GlobalObjectMessage, ":%s: -SCAN- ", Name);

	if (!iOb) GENERATE_EXIT_MSG("ERROR - NULL OBJECTIVE\n", SCANNER_WRONG_INIT);
	if (!iFG) GENERATE_EXIT_MSG("ERROR - NULL FRAMEGRABBER\n", SCANNER_WRONG_INIT);
	if (!iSt) GENERATE_EXIT_MSG("ERROR - NULL STAGE\n", SCANNER_WRONG_INIT);
	if (!(iSM = iS1))
		if (!(iSM = iS2))
			if (!(iSM = iS3)) GENERATE_EXIT_MSG("ERROR - NULL SHEETMAP\n", SCANNER_WRONG_INIT);
	if (!iIO) GENERATE_MSG("ERROR - NULL OUTPUTSTREAM\n");

	bool MemOk;

	int i;

	UINT FitCorrDataSize = 0;
	if (iFt) iFt->GetCorrectionDataSize(&FitCorrDataSize);

	if (iCl->QueryInterface(IID_ILockUnlock, (void **)&iLC) != S_OK) iLC = 0;
	if (iTk->QueryInterface(IID_ITracker2, (void **)&iTk2) != S_OK) iTk2 = 0;
	if (iFt->QueryInterface(IID_ITrackFitter2, (void **)&iFt2) != S_OK) iFt2 = 0;
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStMon);

	MemOk = ((CSpace = (Cluster *)GlobalAlloc(GMEM_FIXED, sizeof(Cluster) * SD.ModD.MaxClusters)) != 0);

	EmuEdges.Left = EmuEdges.Right = EmuEdges.Top = EmuEdges.Bottom = 0.f;
	LFD_XCount = floor(2. * SD.EmuD.Width / SD.EmuD.DepthCoherenceLength + 1.);
	LFD_YCount = floor(2. * SD.EmuD.Height / SD.EmuD.DepthCoherenceLength + 1.);
	
	MemOk = ((FocusInfo = (LocalFocusDepths *)GlobalAlloc(GMEM_FIXED, sizeof(LocalFocusDepths) * LFD_XCount * LFD_YCount)) != 0);

	for (i = 0; i < LFD_XCount * LFD_YCount; i++)
	{
		FocusInfo[i].TopExt = FocusInfo[i].TopInt = FocusInfo[i].BottomExt = FocusInfo[i].BottomInt = 0.;
		FocusInfo[i].HitCount = 0;
		};

	for (i = 0; i < 2; i++)	MemOk &= ((TSpace[i] = (Track *)GlobalAlloc(GMEM_FIXED, sizeof(Track) * SD.ModD.MaxTracks)) != 0);
	for (i = 0; i < 2; i++)	MemOk &= ((FTSpace[i] = (FlatTrack *)GlobalAlloc(GMEM_FIXED, sizeof(FlatTrack) * SD.ModD.MaxFlatTracks)) != 0);
	MemOk &= ((FSSpace[0] = (FlatStrip *)GlobalAlloc(GMEM_FIXED, sizeof(FlatStrip) * SD.TopD.MaxFlatStripsPerTrack * SD.ModD.MaxFlatTracks)) != 0);
	MemOk &= ((FSSpace[1] = (FlatStrip *)GlobalAlloc(GMEM_FIXED, sizeof(FlatStrip) * SD.BottomD.MaxFlatStripsPerTrack * SD.ModD.MaxFlatTracks)) != 0);
	MemOk &= ((GSpace[0] = (Vector *)GlobalAlloc(GMEM_FIXED, sizeof(Vector) * SD.ModD.MaxTracks * SD.TopD.MaxLayers)) != 0);
	MemOk &= ((GSpace[1] = (Vector *)GlobalAlloc(GMEM_FIXED, sizeof(Vector) * SD.ModD.MaxTracks * SD.BottomD.MaxLayers)) != 0);
	if (FitCorrDataSize)
	{
		MemOk &= ((FCSpace[0] = GlobalAlloc(GMEM_FIXED, FitCorrDataSize * SD.ModD.MaxTracks)) != 0);
		MemOk &= ((FCSpace[1] = GlobalAlloc(GMEM_FIXED, FitCorrDataSize * SD.ModD.MaxTracks)) != 0);
		MemOk &= ((FCSpace[2] = GlobalAlloc(GMEM_FIXED, FitCorrDataSize * SD.ModD.MaxFlatTracks)) != 0);
		MemOk &= ((FCSpace[3] = GlobalAlloc(GMEM_FIXED, FitCorrDataSize * SD.ModD.MaxFlatTracks)) != 0);
   		};
	MemOk &= ((FitWorkSpace[0] = (double *)GlobalAlloc(GMEM_FIXED, sizeof(double) * SD.TopD.MaxLayers)) != 0);
	MemOk &= ((FitWorkSpace[1] = (double *)GlobalAlloc(GMEM_FIXED, sizeof(double) * SD.BottomD.MaxLayers)) != 0);

	if (!MemOk)
	{
		if (CSpace)
		{	
			GlobalFree(CSpace);
      		CSpace = 0;
			};
		if (FocusInfo) 
		{
			GlobalFree(FocusInfo);
			FocusInfo = 0;
			};
		for (i = 0; i < 2; i++)
		{	
			if (TSpace[i])
			{	
				GlobalFree(TSpace[i]);
   	   			TSpace[i] = 0;
      			};
			if (FTSpace[i])
			{	
				GlobalFree(FTSpace[i]);
   	   			FTSpace[i] = 0;
      			};
			if (FSSpace[i])
			{	
				GlobalFree(FSSpace[i]);
   	   			FSSpace[i] = 0;
      			};
			if (GSpace[i])	      
			{	
				GlobalFree(GSpace[i]);
   	   			GSpace[i] = 0;
				};
			if (FitCorrDataSize)
			{
				if (FCSpace[i])
				{
					GlobalFree(FCSpace[i]);
					FCSpace[i] = 0;
            		};
				if (FCSpace[i + 2])
				{
					GlobalFree(FCSpace[i + 2]);
					FCSpace[i + 2] = 0;
            		};
         		};
			if (FitWorkSpace[i])
			{	
				GlobalFree(FitWorkSpace[i]);
   	   			FitWorkSpace[i] = 0;
				};
			};
		GENERATE_EXIT_MSG("ERROR - MEMORY\n", SCANNER_TOO_MANY_OBJECTS);
   		};

	for (i = 0; i < SD.ModD.MaxTracks; i++)
		TSpace[0][i].pPoints = (TVector *)(GSpace[0] + i * SD.TopD.MaxLayers);
	for (i = 0; i < SD.ModD.MaxTracks; i++)
		TSpace[1][i].pPoints = (TVector *)(GSpace[1] + i * SD.BottomD.MaxLayers);
	for (i = 0; i < SD.ModD.MaxFlatTracks; i++)
		FTSpace[0][i].pStrips = (FlatStrip *)(FSSpace[0] + i * SD.TopD.MaxFlatStripsPerTrack);
	for (i = 0; i < SD.ModD.MaxFlatTracks; i++)
		FTSpace[1][i].pStrips = (FlatStrip *)(FSSpace[1] + i * SD.BottomD.MaxFlatStripsPerTrack);
	if (FitCorrDataSize)
	{
		for (i = 0; i < SD.ModD.MaxTracks; i++)
			TSpace[0][i].pCorrection = (BYTE *)FCSpace[0] + i * FitCorrDataSize;
		for (i = 0; i < SD.ModD.MaxTracks; i++)
			TSpace[1][i].pCorrection = (BYTE *)FCSpace[1] + i * FitCorrDataSize;
		for (i = 0; i < SD.ModD.MaxFlatTracks; i++)
			FTSpace[0][i].pCorrection = (BYTE *)FCSpace[2] + i * FitCorrDataSize;
		for (i = 0; i < SD.ModD.MaxFlatTracks; i++)
			FTSpace[1][i].pCorrection = (BYTE *)FCSpace[3] + i * FitCorrDataSize;
		}
	else 
	{
		for (i = 0; i < SD.ModD.MaxTracks; i++)
   			TSpace[0][i].pCorrection = TSpace[1][i].pCorrection = 0;
		for (i = 0; i < SD.ModD.MaxFlatTracks; i++)
   			FTSpace[0][i].pCorrection = FTSpace[1][i].pCorrection = 0;
		};

	ScanStatus.Reset();

	iOb->GetSpecs(&CAM);
	if (iCl) iCl->SetCameraSpec(CAM);
	if (iTk) iTk->SetCameraSpec(CAM);

// TODO: remember that the condition is: SD->BackGroundTrackingInfo.FT = (SD->OptD.CenterScanBack) ? FT : 0;
	BackGroundTrackingInfo.CamCX = CAM.Width / 2 * CAM.PixelToMicronX;
	BackGroundTrackingInfo.CamCY = CAM.Height / 2 * CAM.PixelToMicronY;
	BackGroundTrackingInfo.pTrackingThread = 0;
	PauseEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	Monitor.HMutex = CreateMutex(NULL, FALSE, NULL);
	Monitor.HInitCompleted = CreateEvent(NULL, TRUE, FALSE, NULL);
	Monitor.pThread = AfxBeginThread((AFX_THREADPROC)MonitorThreadHook, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	Monitor.pThread->m_bAutoDelete = false;
	Monitor.pThread->ResumeThread();
	WaitForSingleObject(Monitor.HInitCompleted, INFINITE);
	Master = new CommandQueue(0, iICS);
	return SCANNER_NO_ERROR;
	};

void CScanner::UpdateGlobal()
{
	LOCK_MONITOR;
	Monitor.pBatchMon->PostMessage(UM_SET_STARTTIME, ScanStatus.StartTime);
	Monitor.pBatchMon->PostMessage(UM_SET_TKSFNDSCAN, ScanStatus.TracksScanned, ScanStatus.TracksFound);
	Monitor.pBatchMon->PostMessage(UM_SET_PHOTOSEQS, ScanStatus.PhotoSequences);
	Monitor.pBatchMon->PostMessage(UM_SET_CLUSTERDUMPS, ScanStatus.ClusterDumps);
	UNLOCK_MONITOR;
	};

void CScanner::DisableAllMonitors()
{
	Monitor.pBatchMon->pClusterDumpMonitor->ShowWindow(SW_HIDE);
	Monitor.pBatchMon->pPhotoSeqMonitor->ShowWindow(SW_HIDE);
	Monitor.pBatchMon->pScanTracksMonitor->ShowWindow(SW_HIDE);
	};

void CScanner::EnableScanTracksMonitor()
{
	Monitor.pBatchMon->pClusterDumpMonitor->ShowWindow(SW_HIDE);
	Monitor.pBatchMon->pPhotoSeqMonitor->ShowWindow(SW_HIDE);
	Monitor.pBatchMon->pScanTracksMonitor->ShowWindow(SW_SHOW);
	};

void CScanner::EnablePhotoSeqMonitor()
{
	Monitor.pBatchMon->pClusterDumpMonitor->ShowWindow(SW_HIDE);
	Monitor.pBatchMon->pPhotoSeqMonitor->ShowWindow(SW_SHOW);
	Monitor.pBatchMon->pScanTracksMonitor->ShowWindow(SW_HIDE);
	};

void CScanner::EnableClusterDumpMonitor()
{
	Monitor.pBatchMon->pClusterDumpMonitor->ShowWindow(SW_SHOW);
	Monitor.pBatchMon->pPhotoSeqMonitor->ShowWindow(SW_HIDE);
	Monitor.pBatchMon->pScanTracksMonitor->ShowWindow(SW_HIDE);
	};

DWORD CScanner::Exec(HANDLE *phterminateevent, HWND *phwnd, char *name, IFrameGrabber *ifg, IStage *ist, IObjective *iob, 
	IClusterFinder *icl, ITracker *itk, ITrackFitter *ift, ISheetMap *is1, 
	ISheetMap *is2, ISheetMap *is3, ISySalDataIO *iio, SetupData sd, bool Batch)
{
	Monitor.phWnd = phwnd;
	pHTerminateEvent = phterminateevent;
	if (Init(name, ifg, ist, iob, icl, itk, ift, is1, is2, is3, iio, sd) == SCANNER_NO_ERROR)
	{

/*

  TODO: Add SheetMap Initialization code

  */

		ISySalObject *iStOb;
		iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
		GENERATE_MSG("SCANNING MODULE LISTENING");
		Command NextCommand;
		if (Batch)
		{
			NextCommand.OpCode = COMMAND_LOAD_AND_EXEC;
			NextCommand.Priority = COMMAND_PRIORITY_QUEUED;
			Master->QueueCommand(NextCommand);
			};

		do
		{
			NextCommand = Master->GetNext();
			if (NextCommand.Priority == COMMAND_PRIORITY_IMMEDIATE)
      			Master->ReleaseImmediate();
			switch (NextCommand.OpCode)
			{
      			case COMMAND_SCANTRACKS:
												OverridePauseEachField = false;
												UpdateGlobal();
												EnableScanTracksMonitor();
         										Scan_Tracks(&NextCommand, 0);
												iFG->SetLiveGrab();
												iStOb->EnableMonitor(true);
         										break;

				case COMMAND_PHOTOSEQ:
												UpdateGlobal();
												EnablePhotoSeqMonitor();
         										Scan_PhotoSequence(&NextCommand);
         										iFG->SetLiveGrab();
												iStOb->EnableMonitor(true);
         										break;

				case COMMAND_CLUSTERDUMP:
												UpdateGlobal();
												EnableClusterDumpMonitor();
         										Scan_PhotoSequence(&NextCommand);
         										iFG->SetLiveGrab();
												iStOb->EnableMonitor(true);
         										break;

				case COMMAND_LOAD_AND_EXEC:
												UpdateGlobal();
												DisableAllMonitors();
         										Load_and_Exec(&NextCommand);
         										iFG->SetLiveGrab();
												iStOb->EnableMonitor(true);
         										break;

				case COMMAND_REPORT:			SAFE_WRITE_STRING(iOCS, ScanStatus.GenerateReport());
         										break;

      			};
   			}
		while (NextCommand.OpCode != COMMAND_EXIT);

		Monitor.pBatchMon->PostMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_IDLE);
		iStOb->Release();
		Free();		
		};
	return SCANNER_NO_ERROR;
	};

DWORD CScanner::Free()
{
	WaitForSingleObject(Monitor.pThread->m_hThread, INFINITE);
	GENERATE_MSG("SCANNING MODULE EXITING");   
	//SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
	CloseHandle(Monitor.HInitCompleted);
	CloseHandle(Monitor.HMutex);
	CloseHandle(PauseEvent);
	delete Master;
	FlushConfig();
	GENERATE_EXIT_MSG("SUCCESS\n", SCANNER_NO_ERROR);
	};

bool CScanner::SharpPosition(float x, float y, float speed, float acc, float xtol, float ytol, float z, float zspeed, float zacc, float ztol, int retry)
{
	float OldX, OldY, OldZ;
	iSt->GetPos(0, &OldX);
	iSt->GetPos(1, &OldY);
	iSt->GetPos(2, &OldZ);

	int MaxTime = 0.f;
	float TimeNeeded;
	if (fabs(speed) > 0.f && fabs(acc) > 0.f)
	{
   		TimeNeeded = fabs((x - OldX) / speed) + 2.f * sqrt(fabs((x - OldX) / acc)) * 1000.f;
		if (TimeNeeded > MaxTime) MaxTime = TimeNeeded;
   		TimeNeeded = fabs((y - OldY) / speed) + 2.f * sqrt(fabs((y - OldY) / acc)) * 1000.f;
		if (TimeNeeded > MaxTime) MaxTime = TimeNeeded;
   		};
	if (fabs(zspeed) > 0.f && fabs(zacc) > 0.f)
	{
   		TimeNeeded = fabs((z - OldZ) / zspeed) + 2.f * sqrt(fabs((z - OldZ) / zacc)) * 1000.f;
		if (TimeNeeded > MaxTime) MaxTime = TimeNeeded;
   		};
	MaxTime += 10000;

	int Lim, lim;
	iSt->GetLimiter(0, &Lim);
	iSt->GetLimiter(1, &lim);
	Lim |= lim;
	iSt->GetLimiter(2, &lim);
	Lim |= lim;
	bool OldPosGood = !Lim;
	iSt->PosMove(0, x, speed, acc);
	iSt->PosMove(1, y, speed, acc);
	iSt->PosMove(2, z, zspeed, zacc);

	bool fail = false;
	float xfb, yfb, zfb;

	unsigned ActiveLimiterTime; 
	unsigned EndTime = (ActiveLimiterTime = GetTickCount()) + MaxTime;
	ActiveLimiterTime += SD.StageD.WaitForLimiterResetTime;

	do
	{
		Sleep(0);
		if (!OldPosGood && (GetTickCount() < ActiveLimiterTime)) Lim = 0;
		else
		{
			iSt->GetLimiter(0, &Lim);
			iSt->GetLimiter(1, &lim);
			Lim |= lim;
			iSt->GetLimiter(2, &lim);
			Lim |= lim;
			};
		iSt->GetPos(0, &xfb);
		iSt->GetPos(1, &yfb);
		iSt->GetPos(2, &zfb);
		}
	while (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0 && !Lim && 
		((fabs(xfb - x) >= xtol) || (fabs(yfb - y) >= ytol) || (fabs(zfb - z) >= ztol)) &&
   		!(fail = (GetTickCount() > EndTime)));

   if (fail || (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0))
   {
		iSt->Stop(0);
		iSt->Stop(1);
		iSt->Stop(2);
		if (OldPosGood)
		{
			iSt->PosMove(0, x, speed, acc);
			iSt->PosMove(1, y, speed, acc);
			iSt->PosMove(2, z, speed, acc);
      		};
		if (!retry && WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0) 
			return SharpPosition(x, y, speed, acc, xtol, ytol, z, zspeed, zacc, ztol, 1); 
		return false;
		};
	Sleep(SD.StageD.RelaxTime);
	return true;
	};

ISheetMap *CScanner::Select_Map(UINT MapN)
{
	switch (MapN)
	{
		case 0:		return iS1;
		case 1:		return iS2;
		case 2:		return iS3;
		};
	return 0;
	};


bool CScanner::Scan_ClustersDump(Command *Cmd)
{	
	int i, j;
	float NextZPos;
	double StageX, StageY, DX, DY;
	BYTE *Image;
	float CAMCenterX, CAMCenterY;
	FocusDepths Temp;

	GENERATE_MSG("CLUSTERDUMP STARTED\n");

	IO_BULK_ClustersDump Data;

	Data.Hdr.Type.InfoType = BULK_HEADER_BYTES | BULK_CLUSTERPRED_SECTION;
	Data.Hdr.Type.HeaderFormat = BULK_HEADER_TYPE;
	ISheetMap *iSM = Select_Map(Cmd->Parameters.ClusterDump.MapN);
	if (!iSM)
	{
		GENERATE_MSG("CLUSTERDUMP FAILED - failure due to INVALID MAP SELECTION\n");
		return false;
		};
	Data.Hdr.ID = Cmd->Parameters.ClusterDump.ID;
	Data.Hdr.MaxClusters = SD.ModD.MaxClusters;
	Data.Hdr.Frames = Cmd->Parameters.ClusterDump.Pos.Frames;
	Data.Hdr.YPos = Cmd->Parameters.ClusterDump.Pos.Y;
	Data.Hdr.ZPos = Cmd->Parameters.ClusterDump.Pos.Z;
	Data.pPlanes = (BULK_ClustersPlaneInfo *)GlobalAlloc(GMEM_FIXED, (sizeof(BULK_ClustersPlaneInfo) + sizeof(Cluster) * Data.Hdr.MaxClusters) * Data.Hdr.Frames);
	if (!Data.pPlanes)
	{
		GENERATE_MSG("CLUSTERDUMP FAILED - failure due to MEMORY FAULT\n");
		return false;
		};
	for (i = 0; i < Data.Hdr.Frames; i++)
		Data.pPlanes[i].pClusters = (Cluster *)(Data.pPlanes + Data.Hdr.Frames) + i * Data.Hdr.MaxClusters;

	iSM->DirFixPoint(Cmd->Parameters.ClusterDump.Pos.Y, Cmd->Parameters.ClusterDump.Pos.Z);
	iSM->DirMapPoint(Cmd->Parameters.ClusterDump.Pos.Y, Cmd->Parameters.ClusterDump.Pos.Z, &StageX, &StageY);
	Temp = GetNextFocusDepths(Cmd->Parameters.ClusterDump.Pos.Y, Cmd->Parameters.ClusterDump.Pos.Z, StageX, StageY);

	{
   		char IDString[256];
		sprintf(IDString, "Scanning Cluster Dump %d/%d/%d/%d", Data.Hdr.ID.Part[0], Data.Hdr.ID.Part[1], Data.Hdr.ID.Part[2], Data.Hdr.ID.Part[3]);
		GENERATE_MSG(IDString);
   		};

	if (Cmd->Parameters.ClusterDump.Pos.StartDepth > 0)
	{
		Cmd->Parameters.ClusterDump.Pos.StartDepth = Temp.TopInt + Cmd->Parameters.ClusterDump.Pos.StartDepth / SD.EmuD.Shrinkage;
		}
	else if (Cmd->Parameters.ClusterDump.Pos.StartDepth < (Temp.BottomInt - Temp.TopInt)) 
	{
		Cmd->Parameters.ClusterDump.Pos.StartDepth = Temp.BottomInt +
		(Cmd->Parameters.ClusterDump.Pos.StartDepth - (Temp.BottomInt - Temp.TopInt)) / SD.EmuD.Shrinkage;
		}
	else 
	{
		Cmd->Parameters.ClusterDump.Pos.StartDepth = Temp.TopInt + Cmd->Parameters.ClusterDump.Pos.StartDepth;
		};

	if (Cmd->Parameters.ClusterDump.Pos.EndDepth > 0)
	{
		Cmd->Parameters.ClusterDump.Pos.EndDepth = Temp.TopInt + Cmd->Parameters.ClusterDump.Pos.EndDepth / SD.EmuD.Shrinkage;
		}
	else if (Cmd->Parameters.ClusterDump.Pos.EndDepth < (Temp.BottomInt - Temp.TopInt))
	{
		Cmd->Parameters.ClusterDump.Pos.EndDepth = Temp.BottomInt +
		(Cmd->Parameters.ClusterDump.Pos.EndDepth - (Temp.BottomInt - Temp.TopInt)) / SD.EmuD.Shrinkage;
		}
	else 
	{
		Cmd->Parameters.ClusterDump.Pos.EndDepth = Temp.TopInt + Cmd->Parameters.ClusterDump.Pos.EndDepth;
		};

	Data.Hdr.RelevantZs.TopExt = Temp.TopExt;
	Data.Hdr.RelevantZs.TopInt = Temp.TopInt;
	Data.Hdr.RelevantZs.BottomInt = Temp.BottomInt;
	Data.Hdr.RelevantZs.BottomExt = Temp.BottomExt;
	iSM->InvMapVector(CAM.PixelToMicronX, 0, &DX, &DY);
	Data.Hdr.ImageMat[0][0] = DX;
	Data.Hdr.ImageMat[1][0] = DY;
	iSM->InvMapVector(0, CAM.PixelToMicronY, &DX, &DY);
	Data.Hdr.ImageMat[0][1] = DX;
	Data.Hdr.ImageMat[1][1] = DY;
	CAMCenterX = CAM.Width * .5f;
	CAMCenterY = CAM.Height * .5f;

	float fTemp = 0;
	
	LOCK_MONITOR;
	CDM_SET_ID(Data.Hdr.ID);
	CDM_SET_POSXY(Data.Hdr.YPos, Data.Hdr.ZPos);
	CDM_SET_STARTENDDEPTH(Cmd->Parameters.ClusterDump.Pos.StartDepth, Cmd->Parameters.ClusterDump.Pos.EndDepth);
	CDM_SET_CLUSTERS(fTemp);
	CDM_SET_FRAMEDEPTH(fTemp, fTemp);
	CDM_SET_ACTION(CDM_ACTION_MOVING);
	UNLOCK_MONITOR;

	if (!SharpPosition(StageX, StageY, SD.StageD.HorizontalSpeed, SD.StageD.LongDistAcc, SD.StageD.XTolerance, SD.StageD.YTolerance,
      Cmd->Parameters.ClusterDump.Pos.StartDepth, SD.StageD.RewindSpeed, SD.StageD.ZAcc, SD.StageD.ZStaticTolerance))
	{
		ScanStatus.StageFaults++;
		GENERATE_EXIT_MSG("CLUSTERDUMP FAILED - failure due to STAGE FAULT\n", false);
		};

	iSt->GetPos(0, &fTemp); StageX = fTemp;
	iSt->GetPos(1, &fTemp); StageY = fTemp;
	iSM->InvMapPoint(StageX, StageY, &DX, &DY);
	Data.Hdr.YCenter = DX;
	Data.Hdr.ZCenter = DY;

	iFG->SetSingleFrameGrab();

	if (SD.OptD.AutoLightControl) 
	{
		LOCK_MONITOR;
		CDM_SET_ACTION(CDM_ACTION_SETTINGLIGHT);
		UNLOCK_MONITOR;
		SetLightLevel();
		};

	LOCK_MONITOR;
	CDM_SET_ACTION(CDM_ACTION_TAKINGGRAINS);
	UNLOCK_MONITOR;

	if (iLC) iLC->Lock();
	UINT FrameDelay;
	iFG->GetCurrentFrameGrabDelay(&FrameDelay);
	int Lim = 0;
	UINT MaxTime;
	bool TimeOut = false, Terminate = false, Exit = false;
	for (i = 0; i < FrameDelay; i++)
	{
		iFG->HoldFrame(&Image);
		iFG->ReleaseFrame();
		};
	iFG->HoldFrame(&Image);
	BYTE RefLevel = 0, Threshold = 0;
	iCl->MakeEqualization(Image, &RefLevel);
	Threshold = (SD.OptD.RelativeClusterThreshold) ? 
		(RefLevel - Cmd->Parameters.ClusterDump.GrayStep) : Cmd->Parameters.ClusterDump.GrayStep;
	iFG->ReleaseFrame();
	for (i = 0; i < (FrameDelay + Data.Hdr.Frames); i++)
	{
		iSt->GetPos(2, &fTemp);
		NextZPos = Cmd->Parameters.ClusterDump.Pos.StartDepth + i *
      		(Cmd->Parameters.ClusterDump.Pos.EndDepth - Cmd->Parameters.ClusterDump.Pos.StartDepth) /
			(float)(Cmd->Parameters.ClusterDump.Pos.Frames);
		if (SD.StageD.ScanningSpeed <= 0.f || SD.StageD.ZAcc <= 0.f) MaxTime = 0;
		else MaxTime = 2 * (fabs(NextZPos - fTemp) * (1. / SD.StageD.ScanningSpeed + 1. / sqrt(SD.StageD.ZAcc))) * 1000.;
		iSt->PosMove(2, NextZPos, SD.StageD.ScanningSpeed, SD.StageD.ZAcc);
		MaxTime += GetTickCount() + 10000;
		do
		{
	   		int NextCommand = Master->PeekLastImmediate();
   			if (NextCommand == COMMAND_REPORT)
			{	
				SAFE_WRITE_STRING(iOCS, ScanStatus.GenerateReport());
				Master->GetNext();
      			}
   			else if (NextCommand == COMMAND_EXIT)
			{
				Exit = true;
				break;
      			};
			iSt->GetPos(2, &fTemp);
			iSt->GetLimiter(2, &Lim);
			}
		while (fabs(fTemp - NextZPos) > SD.StageD.ZStaticTolerance && !Lim &&
			(TimeOut = (GetTickCount() < MaxTime)) && 
			!(Terminate = (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0)) &&
			!Exit);
		if (Lim || TimeOut || *pTermination || Exit)
		{
			GlobalFree(Data.pPlanes);
			if (*pTermination)
				GENERATE_MSG("CLUSTERDUMP FAILED - failure due to TERMINATION\n")
			else if (Exit)
				GENERATE_MSG("CLUSTERDUMP FAILED - failure due to EXIT COMMAND\n")
			else if (TimeOut)
			{
				ScanStatus.StageFaults++;
				GENERATE_MSG("CLUSTERDUMP FAILED - failure due to STAGE FAULT(TIMEOUT)\n");
				}
			else if (Lim)
			{
				ScanStatus.StageFaults++;
				GENERATE_MSG("CLUSTERDUMP FAILED - failure due to STAGE FAULT(LIMITER)\n");
				};
			if (iLC) iLC->Unlock();
			return false;
			}
		else
		{
			int k;
			iSt->Stop(2);
			if (i < Data.Hdr.Frames) Data.pPlanes[i].Z = fTemp;
			iFG->HoldFrame(&Image);
			j = (i < FrameDelay) ? 0 : (i - FrameDelay);
			Data.pPlanes[j].Count = SD.ModD.MaxClusters;
			iCl->GetClusters(Image, Data.pPlanes[j].pClusters, 
				&Data.pPlanes[j].Count, Threshold, 0);
			for (k = 0; k < Data.pPlanes[j].Count; k++)
			{
				Data.pPlanes[j].pClusters[k].X -= CAMCenterX;
				Data.pPlanes[j].pClusters[k].Y -= CAMCenterY;
				};
			iFG->ReleaseFrame();
			if (i >= FrameDelay)
			{
				LOCK_MONITOR;
				CDM_SET_FRAMEDEPTH(j, Data.pPlanes[j].Z);
				CDM_SET_CLUSTERS(Data.pPlanes[j].Count);
				UNLOCK_MONITOR;
				};
			};		
		};
	if (iLC) iLC->Unlock();
	UINT ExtErrInfo;
	if (iIO->Write(0, (BYTE *)&Data, &ExtErrInfo, 0) != S_OK)
	{
		GlobalFree(Data.pPlanes);
		char retstring[128];
		sprintf(retstring, "CLUSTERDUMP FAILED - failure due to OUTPUTSTREAM(CODE: %08X)", ExtErrInfo);
		GENERATE_MSG(retstring);
		return false;
		};

	GlobalFree(Data.pPlanes);
	GENERATE_MSG("CLUSTERDUMP SUCCESS\n");
	return true;
	};

bool CScanner::Scan_PhotoSequence(Command *Cmd)
{	
	int i;
	float NextZPos;
	double StageX, StageY, DX, DY;
	BYTE *Image;
	FocusDepths Temp;
	int *XResize, *YResize, *XSize, *YSize;

	GENERATE_MSG("PHOTOSEQUENCE STARTED\n");

	IO_BULK_PhotoSeq Data;

	Data.Hdr.Type.InfoType = BULK_HEADER_BYTES | BULK_IMAGEPRED_SECTION;
	Data.Hdr.Type.HeaderFormat = BULK_HEADER_TYPE;
	ISheetMap *iSM = Select_Map(Cmd->Parameters.ClusterDump.MapN);
	if (!iSM)
	{
		GENERATE_MSG("PHOTOSEQUENCE FAILED - failure due to INVALID MAP SELECTION\n");
		return false;
		};
	Data.Hdr.ID = Cmd->Parameters.PhotoSequence.ID;
	Data.Hdr.Width = Cmd->Parameters.PhotoSequence.ImageSize.Width;
	Data.Hdr.Height = Cmd->Parameters.PhotoSequence.ImageSize.Height;
	Data.Hdr.Frames = Cmd->Parameters.PhotoSequence.Pos.Frames;
	Data.Hdr.YPos = Cmd->Parameters.PhotoSequence.Pos.Y;
	Data.Hdr.ZPos = Cmd->Parameters.PhotoSequence.Pos.Z;

	if (!(XResize = (int *)malloc(sizeof(int) * (Data.Hdr.Width + 1))))
	{
		GENERATE_EXIT_MSG("PHOTOSEQUENCE FAILED - failure due to MEMORY FAULT\n", false);
		};
	if (!(YResize = (int *)malloc(sizeof(int) * (Data.Hdr.Height + 1))))
	{
   		free(XResize);
		GENERATE_EXIT_MSG("PHOTOSEQUENCE FAILED - failure due to MEMORY FAULT\n", false);
		};
	if (!(XSize = (int *)malloc(sizeof(int) * Data.Hdr.Width)))
	{
   		free(XResize);
   		free(YResize);
		GENERATE_EXIT_MSG("PHOTOSEQUENCE FAILED - failure due to MEMORY FAULT\n", false);
		};
	if (!(YSize = (int *)malloc(sizeof(int) * Data.Hdr.Height)))
	{
   		free(XResize);
   		free(YResize);
		free(XSize);
		GENERATE_EXIT_MSG("PHOTOSEQUENCE FAILED - failure due to MEMORY FAULT\n", false);
		};

	for (i = 0; i < Data.Hdr.Width; i++) XResize[i] = (i * CAM.Width) / Data.Hdr.Width;
	for (i = 0; i < Data.Hdr.Height; i++) YResize[i] = ((i * CAM.Height) / Data.Hdr.Height) * CAM.Width;
	XResize[Data.Hdr.Width] = CAM.Width;
	YResize[Data.Hdr.Height] = CAM.Height * CAM.Width;
	for (i = 0; i < Data.Hdr.Width; i++) XSize[i] = XResize[i + 1] - XResize[i];
	for (i = 0; i < Data.Hdr.Height; i++) YSize[i] = YResize[i + 1] - YResize[i];

	Data.pImages = (BULK_PhotoInfo *)malloc((sizeof(BULK_PhotoInfo) + Data.Hdr.Width * Data.Hdr.Height) * Data.Hdr.Frames);
	if (!Data.pImages)
	{
		GENERATE_MSG("PHOTOSEQUENCE FAILED - failure due to MEMORY FAULT\n");
		free(XResize);
		free(YResize);
		free(XSize);
		free(YSize);
		return false;
		};
	for (i = 0; i < Data.Hdr.Frames; i++)
		Data.pImages[i].pImage = (BYTE *)(Data.pImages + Data.Hdr.Frames) + i * Data.Hdr.Width * Data.Hdr.Height;

	iSM->DirFixPoint(Cmd->Parameters.PhotoSequence.Pos.Y, Cmd->Parameters.PhotoSequence.Pos.Z);
	iSM->DirMapPoint(Cmd->Parameters.PhotoSequence.Pos.Y, Cmd->Parameters.PhotoSequence.Pos.Z, &StageX, &StageY);
	Temp = GetNextFocusDepths(Cmd->Parameters.PhotoSequence.Pos.Y, Cmd->Parameters.PhotoSequence.Pos.Z, StageX, StageY);

	{
   		char IDString[256];
		sprintf(IDString, "Scanning Photo Sequence %d/%d/%d/%d", Data.Hdr.ID.Part[0], Data.Hdr.ID.Part[1], Data.Hdr.ID.Part[2], Data.Hdr.ID.Part[3]);
		GENERATE_MSG(IDString);
   		};

	if (Cmd->Parameters.PhotoSequence.Pos.StartDepth > 0)
	{
		Cmd->Parameters.PhotoSequence.Pos.StartDepth = Temp.TopInt + Cmd->Parameters.PhotoSequence.Pos.StartDepth / SD.EmuD.Shrinkage;
		}
	else if (Cmd->Parameters.PhotoSequence.Pos.StartDepth < (Temp.BottomInt - Temp.TopInt)) 
	{
		Cmd->Parameters.PhotoSequence.Pos.StartDepth = Temp.BottomInt +
		(Cmd->Parameters.PhotoSequence.Pos.StartDepth - (Temp.BottomInt - Temp.TopInt)) / SD.EmuD.Shrinkage;
		}
	else 
	{
		Cmd->Parameters.PhotoSequence.Pos.StartDepth = Temp.TopInt + Cmd->Parameters.PhotoSequence.Pos.StartDepth;
		};

	if (Cmd->Parameters.PhotoSequence.Pos.EndDepth > 0)
	{
		Cmd->Parameters.PhotoSequence.Pos.EndDepth = Temp.TopInt + Cmd->Parameters.PhotoSequence.Pos.EndDepth / SD.EmuD.Shrinkage;
		}
	else if (Cmd->Parameters.PhotoSequence.Pos.EndDepth < (Temp.BottomInt - Temp.TopInt))
	{
		Cmd->Parameters.PhotoSequence.Pos.EndDepth = Temp.BottomInt +
		(Cmd->Parameters.PhotoSequence.Pos.EndDepth - (Temp.BottomInt - Temp.TopInt)) / SD.EmuD.Shrinkage;
		}
	else 
	{
		Cmd->Parameters.PhotoSequence.Pos.EndDepth = Temp.TopInt + Cmd->Parameters.PhotoSequence.Pos.EndDepth;
		};

	Data.Hdr.RelevantZs.TopExt = Temp.TopExt;
	Data.Hdr.RelevantZs.TopInt = Temp.TopInt;
	Data.Hdr.RelevantZs.BottomInt = Temp.BottomInt;
	Data.Hdr.RelevantZs.BottomExt = Temp.BottomExt;
	iSM->InvMapVector((CAM.PixelToMicronX * CAM.Width) / Data.Hdr.Width, 0, &DX, &DY);
	Data.Hdr.ImageMat[0][0] = DX;
	Data.Hdr.ImageMat[1][0] = DY;
	iSM->InvMapVector(0, (CAM.PixelToMicronY * CAM.Height) / Data.Hdr.Height, &DX, &DY);
	Data.Hdr.ImageMat[0][1] = DX;
	Data.Hdr.ImageMat[1][1] = DY;

	float fTemp = 0;
	
	LOCK_MONITOR;
	PSM_SET_ID(Data.Hdr.ID);
	PSM_SET_POSXY(Data.Hdr.YPos, Data.Hdr.ZPos);
	PSM_SET_STARTENDDEPTH(Cmd->Parameters.PhotoSequence.Pos.StartDepth, Cmd->Parameters.PhotoSequence.Pos.EndDepth);
	PSM_SET_FRAMEDEPTH(fTemp, fTemp);
	PSM_SET_ACTION(PSM_ACTION_MOVING);
	UNLOCK_MONITOR;

	if (!SharpPosition(StageX, StageY, SD.StageD.HorizontalSpeed, SD.StageD.LongDistAcc, SD.StageD.XTolerance, SD.StageD.YTolerance,
      Cmd->Parameters.PhotoSequence.Pos.StartDepth, SD.StageD.RewindSpeed, SD.StageD.ZAcc, SD.StageD.ZStaticTolerance))
	{
		ScanStatus.StageFaults++;
		GENERATE_EXIT_MSG("PHOTOSEQUENCE FAILED - failure due to STAGE FAULT\n", false);
		};

	iSt->GetPos(0, &fTemp); StageX = fTemp;
	iSt->GetPos(1, &fTemp); StageY = fTemp;
	iSM->InvMapPoint(StageX, StageY, &DX, &DY);
	Data.Hdr.YCenter = DX;
	Data.Hdr.ZCenter = DY;

	iFG->SetSingleFrameGrab();

	if (SD.OptD.AutoLightControl) 
	{
		LOCK_MONITOR;
		PSM_SET_ACTION(PSM_ACTION_SETTINGLIGHT);
		UNLOCK_MONITOR;
		SetLightLevel();
		};

	LOCK_MONITOR;
	PSM_SET_ACTION(PSM_ACTION_TAKINGIMAGES);
	UNLOCK_MONITOR;

	UINT FrameDelay;
	iFG->GetCurrentFrameGrabDelay(&FrameDelay);
	int Lim = 0;
	UINT MaxTime;
	bool TimeOut = false, Terminate = false, Exit = false;
	for (i = 0; i < (FrameDelay + Data.Hdr.Frames); i++)
	{
		iSt->GetPos(2, &fTemp);
		if (i < Data.Hdr.Frames)
			NextZPos = Cmd->Parameters.PhotoSequence.Pos.StartDepth + i *
		  		(Cmd->Parameters.PhotoSequence.Pos.EndDepth - Cmd->Parameters.PhotoSequence.Pos.StartDepth) /
				(float)(Cmd->Parameters.PhotoSequence.Pos.Frames);
		if (SD.StageD.ScanningSpeed <= 0.f || SD.StageD.ZAcc <= 0.f) MaxTime = 0;
		else MaxTime = 2 * (fabs(NextZPos - fTemp) * (1. / SD.StageD.ScanningSpeed + 1. / sqrt(SD.StageD.ZAcc))) * 1000.;
		iSt->PosMove(2, NextZPos, SD.StageD.ScanningSpeed, SD.StageD.ZAcc);
		MaxTime += GetTickCount() + 10000;
		do
		{
	   		int NextCommand = Master->PeekLastImmediate();
   			if (NextCommand == COMMAND_REPORT)
			{	
				SAFE_WRITE_STRING(iOCS, ScanStatus.GenerateReport());
				Master->GetNext();
      			}
   			else if (NextCommand == COMMAND_EXIT)
			{
				Exit = true;
				break;
      			};
			iSt->GetPos(2, &fTemp);
			iSt->GetLimiter(2, &Lim);
			}
		while (fabs(fTemp - NextZPos) > SD.StageD.ZStaticTolerance && !Lim &&
			(TimeOut = (GetTickCount() < MaxTime)) && 
			!(Terminate = (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0)) &&
			!Exit);
		if (Lim || TimeOut || Terminate || Exit)
		{
			free(Data.pImages);
			free(XResize);
			free(YResize);
			free(XSize);
			free(YSize);
			if (Terminate)
				GENERATE_MSG("PHOTOSEQUENCE FAILED - failure due to TERMINATION\n")
			else if (Exit)
				GENERATE_MSG("PHOTOSEQUENCE FAILED - failure due to EXIT COMMAND\n")
			else if (TimeOut)
			{
				ScanStatus.StageFaults++;
				GENERATE_MSG("PHOTOSEQUENCE FAILED - failure due to STAGE FAULT(TIMEOUT)\n");
				}
			else if (Lim)
			{
				ScanStatus.StageFaults++;
				GENERATE_MSG("PHOTOSEQUENCE FAILED - failure due to STAGE FAULT(LIMITER)\n");
				};
			return false;
			}
		else
		{
			int j;
			iSt->Stop(2);
			if (i < Data.Hdr.Frames) Data.pImages[i].Z = fTemp;
			iFG->HoldFrame(&Image);
			if (i >= FrameDelay)
			{
				j = i - FrameDelay;
				int px, py;
				BYTE *Scan = Data.pImages[j].pImage;
				unsigned PixVal;
				for (py = 0; py < Data.Hdr.Height; py++)
      				for (px = 0; px < Data.Hdr.Width; px++)
					{
         				PixVal = 0;
						int ix, iy;
						for (ix = 0; ix < XSize[px]; ix++)
							for (iy = 0; iy < YSize[py]; iy += CAM.Width)
               					PixVal += Image[YResize[py] + iy + XResize[px] + ix];
						*Scan++ = PixVal / (XSize[px] * (YSize[py] / CAM.Width));
						};
				LOCK_MONITOR;
				PSM_SET_FRAMEDEPTH(j, Data.pImages[j].Z);
				UNLOCK_MONITOR;
				};
			iFG->ReleaseFrame();
			};		
		};
	UINT ExtErrInfo;
	if (iIO->Write(0, (BYTE *)&Data, &ExtErrInfo, 0) != S_OK)
	{
		free(Data.pImages);
		free(XResize);
		free(YResize);
		free(XSize);
		free(YSize);
		char retstring[128];
		sprintf(retstring, "PHOTOSEQUENCE FAILED - failure due to OUTPUTSTREAM(CODE: %08X)", ExtErrInfo);
		GENERATE_MSG(retstring);
		return false;
		};

	free(Data.pImages);
	free(XResize);
	free(YResize);
	free(XSize);
	free(YSize);
	GENERATE_MSG("PHOTOSEQUENCE SUCCESS\n");
	return true;
	};

float CScanner::EvalGrayLev(BYTE *Image)
{
	unsigned sum = 0, b, count = 0;
	BYTE *pScan = Image;
	BYTE *pEnd = Image + CAM.Width * CAM.Height;
	while (pScan < pEnd)
	{
		if ((b = *pScan++) > SD.OptD.MinGrayLev)
		{
			sum += b;
			count++;
        	};
     	};
	return (count > 0) ? ((float)sum / (float)count) : 0.f;
	};

void CScanner::SetLightLevel()
{
	BYTE *Image;
	int level, bestlev, i;
	UINT FrameDelay;
	float Dist, BestDist;
	int LightIncrement = SD.OptD.LightIncrement;

	iSt->GetLight(&level);
	if (level < SD.OptD.MinLight) iSt->SetLight(level = SD.OptD.MinLight);
	else if (level > SD.OptD.MaxLight) iSt->SetLight(level = SD.OptD.MaxLight);
	bestlev = level;

	iFG->GetCurrentFrameGrabDelay(&FrameDelay);
	for (i = 0; i < FrameDelay; i++)
	{
		iFG->HoldFrame(&Image);
		iFG->ReleaseFrame();
		};
	iFG->HoldFrame(&Image);
	if ((BestDist = EvalGrayLev(Image)) > SD.OptD.TargetGrayLev) LightIncrement = -LightIncrement;
	BestDist = fabs(BestDist - SD.OptD.TargetGrayLev);
	iFG->ReleaseFrame();

	for (i = 0; level >= (SD.OptD.MinLight - SD.OptD.LightIncrement * FrameDelay) && 
		level <= (SD.OptD.MaxLight + SD.OptD.LightIncrement * FrameDelay); i++)
	{
		iFG->HoldFrame(&Image);
		if (i >= FrameDelay)
		{
			Dist = fabs(EvalGrayLev(Image) - SD.OptD.TargetGrayLev);
			if (Dist < BestDist)
			{
				bestlev = level - LightIncrement * FrameDelay;
				BestDist = Dist;
      			}
			};
		iFG->ReleaseFrame();
		iSt->SetLight(level += LightIncrement);
		delay(SD.OptD.LampDelay);
		};
	iSt->SetLight(bestlev);
	delay(SD.OptD.LampDelay * abs((bestlev - level) / LightIncrement));
	};

int CScanner::CountGrains(int CCount, int MinPixels, int MaxPixels)
{
	int i, j;
	for (i = j = 0; i < CCount; i++)
   	if ((CSpace[i].Area >= MinPixels) && (CSpace[i].Area <= MaxPixels)) j++;
	return j;
	};

#define SEQ_VOID_LIMIT	6

bool CScanner::SeekTopSurface(int GThresh, int MaxClusters, int CThresh, int PixMin, int PixMax, float Tolerance, float *FoundZ)
{
	UINT FrameDelay;
	BYTE *Image;
	iFG->GetCurrentFrameGrabDelay(&FrameDelay);
	float LastZ;
	iSt->GetPos(2, &LastZ);
	float NextZ = LastZ;
	float Z;
	float *pZ = new float[FrameDelay + 1];

	bool TopFound;
	bool TopExtReached;
	int Limiter = 0;
	int CC, GC, i;
	int SequentialVoidFrames = 0;

	float ExtTop = LastZ + Tolerance;
	TopFound = false;
	iSt->SpeedMove(2, SD.StageD.ScanningSpeed, SD.StageD.ZAcc);
	i = 0;
	do
	{
		iSt->GetPos(2, &Z);
		pZ[i % (FrameDelay + 1)] = Z;
		if (Z >= NextZ)
		{
			iFG->HoldFrame(&Image);
			if (i >= FrameDelay)
			{
				CC = SD.ModD.MaxClusters;
				if (iCl->GetClusters(Image, CSpace, &CC, GThresh, 0))
				{	
					SequentialVoidFrames = 0;
         			GC = 0;
					}
				else if ((GC = CountGrains(CC, PixMin, PixMax)) < CThresh)
			 	{ 	
					if (++SequentialVoidFrames > SEQ_VOID_LIMIT) TopFound = true; 
					}
				else SequentialVoidFrames = 0;
				LOCK_MONITOR;
				STM_SET_CLUSTERSLAYER(GC, SequentialVoidFrames);
				UNLOCK_MONITOR;
				};
			iFG->ReleaseFrame();
			LastZ = Z;
			NextZ = LastZ + SD.StageD.ScanningStep;
			};
		iSt->GetPos(2, &Z);
		TopExtReached = (i < FrameDelay) ? 0 : (Z > (ExtTop + SD.StageD.ScanningStep * FrameDelay));
		iSt->GetLimiter(2, &Limiter);
		i++;
	   	}
	while (!TopFound && !TopExtReached && !Limiter);
	if (Limiter)
	{
		iSt->Stop(2);
		delete pZ;
		return false;
		};
	if (TopFound)
	{
		iSt->GetPos(2, &Z);
		NextZ = LastZ = Z;
   		ExtTop -= 2 * Tolerance;
		iSt->SpeedMove(2, -SD.StageD.ScanningSpeed, SD.StageD.ZAcc);
	  	TopFound = false;
		SequentialVoidFrames = 0;
		i = 0;
   		do
		{
			iSt->GetPos(2, &Z);
			pZ[i % (FrameDelay + 1)] = Z;
			if (Z <= NextZ)
			{
				iFG->HoldFrame(&Image);
				if (i >= FrameDelay)
				{
					CC = SD.ModD.MaxClusters;
					if (iCl->GetClusters(Image, CSpace, &CC, GThresh, 0))
					{	
						SequentialVoidFrames = 0;
         				GC = 0;
						}
					else if ((GC = CountGrains(CC, PixMin, PixMax)) >= CThresh)
				 	{ 	
						if (++SequentialVoidFrames > SEQ_VOID_LIMIT) 
						{
							TopFound = true;
							*FoundZ = pZ[(i + 1) % (FrameDelay + 1)];
							};
						}
					else SequentialVoidFrames = 0;
					LOCK_MONITOR;
					STM_SET_CLUSTERSLAYER(GC, SequentialVoidFrames);
					UNLOCK_MONITOR;
					};
				iFG->ReleaseFrame();
				LastZ = Z;
      			NextZ = LastZ -SD.StageD.ScanningStep;
				};
			iSt->GetPos(2, &Z);
			TopExtReached = (i < FrameDelay) ? 0 : (Z < (ExtTop - SD.StageD.ScanningStep * FrameDelay));
			iSt->GetLimiter(2, &Limiter);
			i++;
	   		}
		while (!TopFound && !TopExtReached && !Limiter);
		};
	iSt->Stop(2);
	delete pZ;
	return TopFound;
	};

bool CScanner::CheckSideSwap(FocusDepths *NewFocus)
{
	float NewTop = NewFocus->TopExt + SD.EmuD.BaseThickness + SD.EmuD.TopThickness;
	float Z;
  	iSt->PosMove(2, NewTop + SD.StageD.ZTolerance, SD.StageD.RewindSpeed, SD.StageD.ZAcc);
	int Limiter;
	bool Terminate;
	do
	{
		iSt->GetPos(2, &Z);
		iSt->GetLimiter(2, &Limiter);
		}
	while ((Terminate = (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0)) && 
		!Limiter && (fabs(Z - NewTop - SD.StageD.ZTolerance) > SD.StageD.ZTolerance));
	iSt->Stop(2);
	if (Terminate || Limiter) return false;

  	BYTE RefLevel;
	int i;
	UINT FrameDelay;
	BYTE *Image;
	if (iLC) iLC->Lock();
	iFG->GetCurrentFrameGrabDelay(&FrameDelay);
	for (i = 0; i < FrameDelay; i++)
	{
		iFG->HoldFrame(&Image);
		iFG->ReleaseFrame();
		};
	iFG->HoldFrame(&Image);
	iCl->MakeEqualization(Image, &RefLevel);
	int GrayThreshold = (SD.OptD.RelativeClusterThreshold) ? (RefLevel - SD.TopD.ClusterContrast) : SD.TopD.ClusterContrast;
	iFG->ReleaseFrame();

	if (SeekTopSurface(GrayThreshold, SD.ModD.MaxClusters, SD.TopD.ClusterThreshold, SD.TopD.PixMin, SD.TopD.PixMax, SD.StageD.FocusTolerance, &NewTop) &&
      (fabs(NewTop - NewFocus->TopExt) > SD.StageD.ThicknessTolerance))
	{
		NewFocus->TopExt = NewTop;
		NewFocus->TopInt = NewTop - SD.EmuD.TopThickness;
		NewFocus->BottomInt = NewFocus->TopInt - SD.EmuD.BaseThickness;
		NewFocus->BottomExt = NewFocus->BottomInt - SD.EmuD.BottomThickness;

		if (iLC) iLC->Unlock();
		return true;
   		};
	
	if (iLC) iLC->Unlock();
	return false;
	};

int CScanner::GetGrains(int GThresh, int MaxClusters, float BeginPos, float EndPos, float EndPosTol, int PixMin, int PixMax, int CThresh, float *EndZ, bool NoFocus)
{
	float LastZ;
	iSt->GetPos(2, &LastZ);
	float NextZ = LastZ;
	float Z;
	float *pZ;
	BYTE *Image;
	UINT FrameDelay;
	iFG->GetCurrentFrameGrabDelay(&FrameDelay);
	pZ = new float[FrameDelay + 1];

	bool EndFound;
	bool EndExtReached;
	int Limiter;
	bool BeginReached, TimeOut, Terminate;
	int CC, GC, i;
	int Layers = 0;
	int SequentialVoidFrames = 0;
	int MaxTime = (SD.StageD.ScanningSpeed <= 0. || SD.StageD.ZAcc <= 0.) ? 0 : ((2. * fabs((LastZ - BeginPos) / 
		(1. / SD.StageD.ScanningSpeed + 1. / SD.StageD.ZAcc))) * 1000.);
	MaxTime += GetTickCount() + 10000;


	iTk->StartFilling();
	iSt->SpeedMove(2, -SD.StageD.ScanningSpeed, SD.StageD.ZAcc);

	do
	{
		iSt->GetLimiter(2, &Limiter);
		TimeOut = (GetTickCount() > MaxTime);
		Terminate = (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0);
		iSt->GetPos(2, &LastZ);
   		BeginReached = (LastZ <= BeginPos);
		EndExtReached = LastZ < (EndPos - EndPosTol);
		}
	while (!Terminate && !TimeOut && !Limiter && !BeginReached && !EndExtReached);
	if (Limiter || Terminate || TimeOut || EndExtReached)
	{
		delete pZ;
		iSt->Stop(2);
		if (Terminate) return FOCUS_TERMINATE;
		if (TimeOut) return FOCUS_TIMEOUT;
		if (Limiter) return FOCUS_LIMITER;
		return FOCUS_ENDSTROKE;
		};
	NextZ = LastZ - SD.StageD.ScanningStep;
	EndFound = false;
	i = 0;
	do
	{
		iSt->GetPos(2, &Z);
		pZ[i % (FrameDelay + 1)] = Z;
		if (Z <= NextZ)
		{
			iFG->HoldFrame(&Image);
			if (i >= FrameDelay)
			{
				CC = SD.ModD.MaxClusters;
				if (iCl->GetClusters(Image, CSpace, &CC, GThresh, 0) == S_OK)
				{
					GC = CountGrains(CC, PixMin, PixMax);
					if (GC < CThresh)
					{
						if (!(EndFound = ((pZ[(i + 1) % (FrameDelay + 1)] <= (EndPos + EndPosTol)) && (++SequentialVoidFrames > SEQ_VOID_LIMIT)))) *EndZ = LastZ;
						}
			         else
				     {
						SequentialVoidFrames = 0;
						EndFound = false;
						};
					}
				iTk->PutClusters(CSpace, CC, pZ[(i + 1) & (FrameDelay + 1)]);
				Layers = i - FrameDelay;
				LOCK_MONITOR;
				STM_SET_CLUSTERSLAYER(GC, Layers);
				UNLOCK_MONITOR;
				}
			else
			{
				CC = SD.ModD.MaxClusters;
				iCl->GetClusters(Image, CSpace, &CC, GThresh, 0);
				};
			iFG->ReleaseFrame();
	        LastZ = Z;
			NextZ = LastZ - SD.StageD.ScanningStep;
			i++;
			};
		EndExtReached = (Z < (EndPos - EndPosTol));
		iSt->GetLimiter(2, &Limiter);
   		}
	while ((!EndFound || NoFocus) && !EndExtReached && !Limiter);
	delete pZ;
	iSt->Stop(2);

	if (EndExtReached)
	{	
		if (NoFocus) return FOCUS_OK + Layers;
   		else return FOCUS_ENDSTROKE;
		};
	if (Limiter) return FOCUS_LIMITER;
	return FOCUS_OK + Layers - SequentialVoidFrames;
	};

DWORD CScanner::Scan_Top(int Field, FocusDepths BestKnown, FocusDepths *BestFound, bool ReFocus)
{
	int Layers, i;
	BYTE RefLevel, GrayThreshold;
	int RetCode;
	bool MinLayersFlag, MaxLayersFlag, MinThicknessFlag, MaxThicknessFlag;
	int Limiter;
	float MeasuredThickness, Z;
	bool Terminate;
	UINT FrameDelay;
	BYTE *Image;

	BackGroundTrackingInfo.TracksFoundCount = BackGroundTrackingInfo.FlatTracksFoundCount = 0;
	*BestFound = BestKnown;

	iSt->PosMove(2, BestKnown.TopExt + SD.StageD.ZTolerance, SD.StageD.RewindSpeed, SD.StageD.ZAcc); 
	do
	{
		iSt->GetPos(2, &Z);
		iSt->GetLimiter(2, &Limiter);
		Terminate = (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0);
		}
	while (!Terminate && !Limiter && (fabs(Z - BestKnown.TopExt - SD.StageD.ZTolerance) > SD.StageD.ZTolerance));
	iSt->Stop(2);
	if (Terminate) return SCAN_1_TERMINATED;
	if (Limiter) return SCAN_1_LIMITER;

	LOCK_MONITOR;
	STM_SET_SIDEFIELD(0, Field + 1);
	UNLOCK_MONITOR;
	if (SD.OptD.AutoLightControl && ReFocus)
	{	
		LOCK_MONITOR;
		STM_SET_ACTION(STM_ACTION_SETTINGLIGHT);
		UNLOCK_MONITOR;
		SetLightLevel();
		};
  	
	if (iLC) iLC->Lock();
	iFG->GetCurrentFrameGrabDelay(&FrameDelay);
	for (i = 0; i < FrameDelay; i++)
	{
		iFG->HoldFrame(&Image);
		iFG->ReleaseFrame();
		};

	iFG->HoldFrame(&Image);
	iCl->MakeEqualization(Image, &RefLevel);
	GrayThreshold = (SD.OptD.RelativeClusterThreshold) ? (RefLevel - SD.TopD.ClusterContrast) : SD.TopD.ClusterContrast;
	iFG->ReleaseFrame();
	if (ReFocus)
	{
		LOCK_MONITOR;
		STM_SET_ACTION(STM_ACTION_FOCUSING);
		UNLOCK_MONITOR;
   		float TempZ = BestFound->TopExt;
		if (!SeekTopSurface(GrayThreshold, SD.ModD.MaxClusters, SD.TopD.ClusterThreshold, SD.TopD.PixMin, SD.TopD.PixMax, 
			SD.StageD.FocusTolerance, &TempZ))
		{
			if (iLC) iLC->Unlock();
			return SCAN_1_NOFOCUS;
			}
		else
		{
      		BestFound->TopExt = TempZ;
      		BestFound->TopInt = BestFound->TopExt - (BestKnown.TopExt - BestKnown.TopInt);
			BestFound->BottomInt = BestFound->TopInt - (BestKnown.TopInt - BestKnown.BottomInt);
			BestFound->BottomExt = BestFound->BottomInt - (BestKnown.BottomInt - BestKnown.BottomExt);         
			};
     	}
	else
	{
		BestFound->TopExt = BestKnown.TopExt;
		BestFound->TopInt = BestKnown.TopInt;
		iSt->PosMove(2, BestFound->TopExt + 2 * SD.StageD.ZTolerance, SD.StageD.RewindSpeed, SD.StageD.ZAcc);
		do
		{
			iSt->GetPos(2, &Z);
			iSt->GetLimiter(2, &Limiter);
			Terminate = (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0);
			}
		while (!Terminate && !Limiter && (fabs(Z - BestFound->TopExt - 2 * SD.StageD.ZTolerance) > SD.StageD.ZTolerance));
		iSt->Stop(2);
		if (Terminate || Limiter)
		{
			if (iLC) iLC->Unlock();
			if (Terminate) return SCAN_1_TERMINATED;
			return SCAN_1_LIMITER;
			};
		};
	LOCK_MONITOR;
	STM_SET_ACTION(STM_ACTION_TAKINGGRAINS);
	UNLOCK_MONITOR;

	if ((RetCode = GetGrains(GrayThreshold, SD.ModD.MaxClusters, BestFound->TopExt, BestFound->TopInt,
	   SD.StageD.FocusTolerance, SD.TopD.PixMin, SD.TopD.PixMax, SD.TopD.ClusterThreshold, 
	   &(BestFound->TopInt), false)) < FOCUS_OK)
	{
		if (iLC) iLC->Unlock();
     	return SCAN_1_NOFOCUS;
		};
	if (iLC) iLC->Unlock();
	Layers = RetCode - FOCUS_OK;
	MeasuredThickness = BestFound->TopExt - BestFound->TopInt;
	MinLayersFlag = (Layers < SD.TopD.EndLayer);
	MaxLayersFlag = (Layers > SD.TopD.MaxLayers);
	MinThicknessFlag = (MeasuredThickness < (SD.EmuD.TopThickness - SD.StageD.ThicknessTolerance));
	MaxThicknessFlag = (MeasuredThickness > (SD.EmuD.TopThickness + SD.StageD.ThicknessTolerance));
	if ((MinLayersFlag && MinThicknessFlag) || (MaxLayersFlag && MaxThicknessFlag))
	{
		BestFound->TopExt = BestFound->TopInt + SD.EmuD.TopThickness;
		iSt->PosMove(2, BestKnown.TopExt, SD.StageD.RewindSpeed, SD.StageD.ZAcc);
		do
		{
			iSt->GetPos(2, &Z);
			iSt->GetLimiter(2, &Limiter);
			Terminate = (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0);
			}
		while (!Terminate && !Limiter && (fabs(Z - BestFound->TopExt) > SD.StageD.ZTolerance));
		if (Terminate) return SCAN_1_TERMINATED;
   		if (Limiter) return SCAN_1_LIMITER;
		float voidfloat;
		if (iLC) iLC->Lock();
		if ((RetCode = GetGrains(GrayThreshold, SD.ModD.MaxClusters, BestFound->TopExt, BestFound->TopInt,
			0, SD.TopD.PixMin, SD.TopD.PixMax, SD.TopD.ClusterThreshold, 
			&voidfloat, true)) < FOCUS_OK)
		{
			if (iLC) iLC->Unlock();
   	  		return SCAN_1_NOFOCUS;
			};
		if (iLC) iLC->Unlock();
		Layers = RetCode - FOCUS_OK;
		if ((Layers > SD.TopD.MaxLayers) || (Layers < SD.TopD.EndLayer))
		{
   	  		return SCAN_1_NOFOCUS;
			};
		}
	else if (MinLayersFlag && !MinThicknessFlag)
	{
  	  	return SCAN_1_TOOFAST;
   		}
	else if (MaxLayersFlag)
	{
		BestFound->TopExt = BestFound->TopInt + SD.StageD.ScanningStep * SD.TopD.MaxLayers;
		iSt->PosMove(2, BestKnown.TopExt, SD.StageD.RewindSpeed, SD.StageD.ZAcc);
		do
		{
			iSt->GetPos(2, &Z);
			iSt->GetLimiter(2, &Limiter);
			Terminate = (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0);
			}
		while (!Terminate && !Limiter && (fabs(Z - BestFound->TopExt) > SD.StageD.ZTolerance));
		if (Terminate) return SCAN_1_TERMINATED;
		if (Limiter) return SCAN_1_LIMITER;
		float voidfloat;
		if ((RetCode = GetGrains(GrayThreshold, SD.ModD.MaxClusters, BestFound->TopExt, BestFound->TopInt,
			0, SD.TopD.PixMin, SD.TopD.PixMax, SD.TopD.ClusterThreshold, 
			&voidfloat, true)) < FOCUS_OK)
		{
			if (iLC) iLC->Unlock();
   	  		return SCAN_1_NOFOCUS;
			};
		if (iLC) iLC->Unlock();
		Layers = RetCode - FOCUS_OK;
		if ((Layers > SD.TopD.MaxLayers) || (Layers < SD.TopD.EndLayer))
		{
      		return SCAN_1_NOFOCUS;
    	   };
     	};
	BackGroundTrackingInfo.StartLayer = Layers - (BestFound->TopExt - BestFound->TopInt) / SD.StageD.ScanningStep;
	if (BackGroundTrackingInfo.StartLayer < 0) BackGroundTrackingInfo.StartLayer = 0;
  	if (BackGroundTrackingInfo.StartLayer >= SD.TopD.MaxLayers)
   	BackGroundTrackingInfo.StartLayer = SD.TopD.MaxLayers - 1;
  	if ((BackGroundTrackingInfo.EndLayer = Layers - 1) >= SD.TopD.MaxLayers)
   	BackGroundTrackingInfo.EndLayer = SD.TopD.MaxLayers - 1;
	float X, Y;
	iSt->GetPos(0, &X);
	iSt->GetPos(1, &Y);
	BackGroundTrackingInfo.ActX = X;
	BackGroundTrackingInfo.ActY = Y;
	BackGroundTrackingInfo.Shrinkage = SD.EmuD.Shrinkage;
	BackGroundTrackingInfo.BaseDepth = BestKnown.TopInt;
	BackGroundTrackingInfo.EmThick = SD.EmuD.TopThickness;
	BackGroundTrackingInfo.Field = Field;
	BackGroundTrackingInfo.Side = 0;
 	StartBkGndTracking();
	BestFound->BottomInt = BestFound->TopInt - (BestKnown.TopInt - BestKnown.BottomInt);
	BestFound->BottomExt = BestFound->BottomInt - (BestKnown.BottomInt - BestKnown.BottomExt);
	return SCAN_1_OK;
	};

DWORD CScanner::Scan_Bottom(int Field, FocusDepths BestKnown, FocusDepths *BestFound, bool ReFocus, bool WaitZ)
{
	int Layers, i;
	BYTE RefLevel, GrayThreshold;
	int RetCode;
	int Limiter;
	float MeasuredThickness, Z;
	bool Terminate;
	UINT FrameDelay;
	BYTE *Image;

	BackGroundTrackingInfo.TracksFoundCount = BackGroundTrackingInfo.FlatTracksFoundCount = 0;
	*BestFound = BestKnown;


	LOCK_MONITOR;
	STM_SET_SIDEFIELD(1, Field + 1);
	UNLOCK_MONITOR;
	if (WaitZ)
	{
		do
		{
			iSt->GetPos(2, &Z);
			iSt->GetLimiter(2, &Limiter);
			Terminate = (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0);
			}
	  	while (!Terminate && !Limiter && (fabs(Z - BestFound->BottomInt - SD.StageD.SlowdownLength) > SD.StageD.ZTolerance));
		};
	iSt->Stop(2);
  	if (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0) return SCAN_1_TERMINATED;
	if (Limiter) return SCAN_1_LIMITER;
  	
	if (iLC) iLC->Lock();
	iFG->GetCurrentFrameGrabDelay(&FrameDelay);
	for (i = 0; i < FrameDelay; i++)
	{
		iFG->HoldFrame(&Image);
		iFG->ReleaseFrame();
		};

	iFG->HoldFrame(&Image);
	iCl->MakeEqualization(Image, &RefLevel);
	GrayThreshold = (SD.OptD.RelativeClusterThreshold) ? (RefLevel - SD.BottomD.ClusterContrast) : SD.BottomD.ClusterContrast;
	iFG->ReleaseFrame();
	if (ReFocus)
  	{
		LOCK_MONITOR;
		STM_SET_ACTION(STM_ACTION_FOCUSING);
		UNLOCK_MONITOR;
   		float TempZ = BestFound->BottomInt;
		if (!SeekTopSurface(GrayThreshold, SD.ModD.MaxClusters, SD.BottomD.ClusterThreshold, SD.BottomD.PixMin, SD.BottomD.PixMax, 
			SD.StageD.FocusTolerance, &TempZ))
		{
			if (iLC) iLC->Unlock();
			return SCAN_1_NOFOCUS;
			}
		else
		{
	      	BestFound->BottomInt = TempZ;
			iSt->PosMove(2, BestFound->BottomInt + 2 * SD.StageD.ZTolerance, SD.StageD.RewindSpeed, SD.StageD.ZAcc);
			do
			{
				iSt->GetPos(2, &Z);
				iSt->GetLimiter(2, &Limiter);
				Terminate = (WaitForSingleObject(*pHTerminateEvent, 0) == WAIT_OBJECT_0);
				}
	  		while (!Terminate && !Limiter && (fabs(Z - BestFound->BottomInt - 2 * SD.StageD.ZTolerance) > SD.StageD.ZTolerance));
		  	iSt->Stop(2);
			if (Terminate || Limiter)
			{
				if (iLC) iLC->Unlock();
				if (Terminate) return SCAN_1_TERMINATED;
				return SCAN_1_LIMITER;
				};
      		};
   		};
	BestFound->BottomExt = BestFound->BottomInt - (BestKnown.BottomInt - BestKnown.BottomExt);
	LOCK_MONITOR;
	STM_SET_ACTION(STM_ACTION_TAKINGGRAINS);
	UNLOCK_MONITOR;
	if ((RetCode = GetGrains(GrayThreshold, SD.ModD.MaxClusters, BestFound->BottomInt, BestFound->BottomExt,
   		SD.StageD.FocusTolerance, SD.BottomD.PixMin, SD.BottomD.PixMax, SD.BottomD.ClusterThreshold, 
		&(BestFound->BottomExt), false)) < FOCUS_OK)
	{
  	  	return SCAN_1_NOFOCUS;
     	};
	Layers = RetCode - FOCUS_OK;
  	MeasuredThickness = BestFound->BottomInt - BestFound->BottomExt;
	if (fabs(MeasuredThickness - SD.EmuD.BottomThickness) > SD.StageD.ThicknessTolerance)
		BestFound->BottomExt = BestFound->BottomInt - (BestKnown.BottomInt - BestKnown.BottomExt);
  	BackGroundTrackingInfo.StartLayer = Layers - (BestFound->BottomInt - BestFound->BottomExt) / SD.StageD.ScanningStep;
	if (BackGroundTrackingInfo.StartLayer < 0) BackGroundTrackingInfo.StartLayer = 0;
  	if (BackGroundTrackingInfo.StartLayer >= SD.BottomD.MaxLayers)
   		BackGroundTrackingInfo.StartLayer = SD.BottomD.MaxLayers - 1;
  	if ((BackGroundTrackingInfo.EndLayer = Layers - 1) >= SD.BottomD.MaxLayers)
   		BackGroundTrackingInfo.EndLayer = SD.BottomD.MaxLayers - 1;
	if (BackGroundTrackingInfo.EndLayer < 0) BackGroundTrackingInfo.EndLayer = 0;
	float X, Y;
	iSt->GetPos(0, &X);
	iSt->GetPos(1, &Y);
	BackGroundTrackingInfo.ActX = X;
	BackGroundTrackingInfo.ActY = Y;
	BackGroundTrackingInfo.Shrinkage = SD.EmuD.Shrinkage;
	BackGroundTrackingInfo.BaseDepth = BestKnown.BottomInt;
	BackGroundTrackingInfo.EmThick = -SD.EmuD.BottomThickness;
	BackGroundTrackingInfo.Field = Field;
	BackGroundTrackingInfo.Side = 1;
 	StartBkGndTracking();
	return SCAN_1_OK;
	};

void CScanner::CreateBkGndTracking()
{
	BackGroundTrackingInfo.HStartStop = CreateEvent(NULL, FALSE, FALSE, NULL);
	BackGroundTrackingInfo.HFinished = CreateEvent(NULL, TRUE, TRUE, NULL);
	BackGroundTrackingInfo.HExit = CreateEvent(NULL, TRUE, FALSE, NULL);
	BackGroundTrackingInfo.pTrackingThread = AfxBeginThread((AFX_THREADPROC)TrackerThreadHook, this, THREAD_PRIORITY_NORMAL, 65536, CREATE_SUSPENDED, NULL);
	BackGroundTrackingInfo.pTrackingThread->m_bAutoDelete = FALSE;
	BackGroundTrackingInfo.pTrackingThread->ResumeThread();
	};

void CScanner::StartBkGndTracking()
{	
	ResetEvent(BackGroundTrackingInfo.HFinished);
	SetEvent(BackGroundTrackingInfo.HStartStop); 
	};

void CScanner::WaitForBkGndTracking()
{	
	HANDLE HEvs[2];
	HEvs[0] = *pHTerminateEvent;
	HEvs[1] = BackGroundTrackingInfo.HFinished;
	WaitForMultipleObjects(2, HEvs, FALSE, INFINITE);
	};

void CScanner::TerminateBkGndTracking()
{
	SetEvent(BackGroundTrackingInfo.HExit);
	WaitForSingleObject(BackGroundTrackingInfo.pTrackingThread->m_hThread, INFINITE);
	CloseHandle(BackGroundTrackingInfo.HExit);
	CloseHandle(BackGroundTrackingInfo.HFinished);
	CloseHandle(BackGroundTrackingInfo.HStartStop);
	delete BackGroundTrackingInfo.pTrackingThread;
	};

UINT CScanner::TrackerThread()
{
	int i;
	HANDLE TheHandles[2];

	TheHandles[0] = BackGroundTrackingInfo.HExit;
	TheHandles[1] = BackGroundTrackingInfo.HStartStop;
	while (WaitForMultipleObjects(2, TheHandles, FALSE, INFINITE) != WAIT_OBJECT_0)
	{
		BackGroundTrackingInfo.TracksFoundCount = 0;
		BackGroundTrackingInfo.FlatTracksFoundCount = 0;

		int Side = BackGroundTrackingInfo.Side;
   		int TkFndCount;
		Track *TracksSpace = TSpace[Side] + TCount[Side];
		FlatTrack *FTracksSpace = FTSpace[Side] + FTCount[Side];
		TkFndCount = SD.ModD.MaxTracks - TCount[Side]; 
		iTk->GetTracks(TracksSpace, &TkFndCount, BackGroundTrackingInfo.StartLayer, BackGroundTrackingInfo.EndLayer);
		BackGroundTrackingInfo.TracksFoundCount = TkFndCount;
		TracksToWorld(iSM, BackGroundTrackingInfo.ActX, BackGroundTrackingInfo.ActY, BackGroundTrackingInfo.CamCX, 
			BackGroundTrackingInfo.CamCY, BackGroundTrackingInfo.BaseDepth, TracksSpace, TkFndCount);
		for (i = 0; i < TkFndCount; TracksSpace[i++].Field = BackGroundTrackingInfo.Field);

		if (iTk2)
		{
			TkFndCount = SD.ModD.MaxFlatTracks - FTCount[Side];
			iTk2->GetFlatTracks(FTracksSpace, &TkFndCount, Side ? SD.BottomD.MaxFlatStripsPerTrack : SD.TopD.MaxFlatStripsPerTrack, BackGroundTrackingInfo.StartLayer, BackGroundTrackingInfo.EndLayer);
			BackGroundTrackingInfo.FlatTracksFoundCount = TkFndCount;
			FlatTracksToWorld(iSM, BackGroundTrackingInfo.ActX, BackGroundTrackingInfo.ActY, BackGroundTrackingInfo.CamCX, 
				BackGroundTrackingInfo.CamCY, BackGroundTrackingInfo.BaseDepth, FTracksSpace, TkFndCount);
			for (i = 0; i < TkFndCount; FTracksSpace[i++].Field = BackGroundTrackingInfo.Field);
			};

		SetEvent(BackGroundTrackingInfo.HFinished);
		};
	return 0;
	};

// Tools

char *skipblanks(char *string)
{
	while (*string == ' ') string++;
	char *next = string;
	while ((*next) && (*next != ' ')) next++;
	*next = 0;
	return string;
	};

static char *gettoken(char *string, char end)
{
	static char *str;
	char *search, *ret;
	if (string) str = string;
	if (!str) return 0;
	search = str;
	while (*search && (*search != end)) search++;
	ret = str;
	if (!(*search)) str = 0;
	else
	{	
		str = search + 1;
   		*search = 0;
		};
	return skipblanks(ret);
	};

void delay(int del)
{
	int start = GetTickCount();
	while ((GetTickCount() - start) < del);
	};



// Multi Field Scanning

#define REPORT_SCAN(scanfunc_call)\
{\
	/*if (iLC) iLC->Lock();*/\
	switch (scanfunc_call)\
	{\
		case SCAN_1_LIMITER:    FocusFault = true;\
      							StageFault = true;\
								ScanStatus.StageFaults++;\
								ScanStatus.FocusFaults++;\
								CountOfFocusFaults++;\
  								GENERATE_MSG("SCANTRACKS - STAGE FAULT\n");\
								LOCK_MONITOR;\
								GM_SET_STAGEFAULTS(ScanStatus.StageFaults);\
								GM_SET_FOCUSFAULTS(ScanStatus.FocusFaults);\
								UNLOCK_MONITOR;\
								break;\
	\
	   	case SCAN_1_TOOFAST:\
		case SCAN_1_NOFOCUS:	StageFault = false;\
      							FocusFault = true;\
   	  							GENERATE_MSG("SCANTRACKS - FOCUS FAULT\n");\
      							ScanStatus.FocusFaults++;\
								CountOfFocusFaults++;\
								LOCK_MONITOR;\
								GM_SET_FOCUSFAULTS(ScanStatus.FocusFaults);\
								UNLOCK_MONITOR;\
								break;\
	\
		default:				FocusFault = StageFault = false;\
   								break;\
	  	};\
	/*if (iLC) iLC->Unlock();*/\
	}

bool CScanner::Scan_Tracks(Command *Cmd, ScanResult *ScanReport, bool Retry)
{
	bool SideSwapped = false;
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
	GENERATE_MSG("SCANTRACKS STARTED\n")
	if (!iCl) GENERATE_MSG("SCANTRACKS FAILED - CLUSTERFINDER NULL\n");
	if (!iTk) GENERATE_MSG("SCANTRACKS FAILED - TRACKER NULL\n");
	if (!iFt) GENERATE_MSG("SCANTRACKS FAILED - TRACKFITTER NULL\n");

	FieldMap *FM;
	if (SD.SeekerD.ZoneScanning && SD.OptD.CenterScanBack && ScanReport && (ScanReport->Pred.GoodSlopeTolerance <= 0.f)) Retry = true;
	if (SD.SeekerD.ZoneScanning && SD.OptD.CenterScanBack && Retry)
	{
		FM = new FieldMap(SD.SeekerD.ZoneXFields, SD.SeekerD.ZoneYFields);
   		}
	else if (SD.PathD.PathFileName[0])
	{
		FM = new FieldMap(SD.PathD.PathFileName);
		if (FM->GetLength() <= 0)
		{
			GENERATE_EXIT_MSG("SCANTRACKS FAILED - PATHFILE NONEXISTING\n", false);
      		};
		}
	else FM = new FieldMap(SD.PathD.XFields, SD.PathD.YFields);
	FM->SetStep(SD.StageD.XStep, SD.StageD.YStep);

	BackGroundTrackingInfo.pTrackingThread = 0;
	CreateBkGndTracking();

	double StageX, StageY;
	double NewX, NewY;
	float fNewX, fNewY;
	float CamCX = CAM.Width / 2 * CAM.PixelToMicronX;
	float CamCY = CAM.Height / 2 * CAM.PixelToMicronY;

	IO_BULK_Tracks TracksInfo;

	TrackPrediction TargetTrack;
	if (ScanReport)
	{
		if (SD.OptD.CenterScanBack) TargetTrack = CorrectPrediction(ScanReport->Pred);
		else TargetTrack = ScanReport->Pred;
		}
	else
	{
		TargetTrack.MapN = Cmd->Parameters.ScanTracks.MapN;
		TargetTrack.Pos.Y = Cmd->Parameters.ScanTracks.Pos.Y;
		TargetTrack.Pos.Z = Cmd->Parameters.ScanTracks.Pos.Z;
		TargetTrack.Slope.Top.Y = TargetTrack.Slope.Bottom.Y =
			TargetTrack.Slope.Global.Y = Cmd->Parameters.ScanTracks.Slope.Global.Y;
		TargetTrack.Slope.Top.Z = TargetTrack.Slope.Bottom.Z =
			TargetTrack.Slope.Global.Z = Cmd->Parameters.ScanTracks.Slope.Global.Z;
		};

	TracksInfo.Hdr.Type.InfoType = BULK_HEADER_BYTES | BULK_TRACK_SECTION;
	TracksInfo.Hdr.Type.HeaderFormat = BULK_HEADER_TYPE;
	TracksInfo.Hdr.ID = Cmd->Parameters.ScanTracks.ID;
	TracksInfo.Hdr.YPos = Cmd->Parameters.ScanTracks.Pos.Y;
	TracksInfo.Hdr.ZPos = Cmd->Parameters.ScanTracks.Pos.Z;
	TracksInfo.Hdr.YSlope = Cmd->Parameters.ScanTracks.Slope.Global.Y;
	TracksInfo.Hdr.ZSlope = Cmd->Parameters.ScanTracks.Slope.Global.Z;
	TracksInfo.Hdr.SideSlopeTolerance = Cmd->Parameters.ScanTracks.SideSlopeTolerance;
	TracksInfo.Hdr.GlobalSlopeTolerance = Cmd->Parameters.ScanTracks.GlobalSlopeTolerance;
	TracksInfo.Hdr.GoodSlopeTolerance = Cmd->Parameters.ScanTracks.GoodSlopeTolerance;
	if (iFt) iFt->GetCorrectionDataSize((UINT *)&TracksInfo.Hdr.FitCorrectionDataSize);
	else TracksInfo.Hdr.FitCorrectionDataSize = 0;
	TracksInfo.Hdr.FCount = FM->GetLength();
	BYTE *FieldStatus = (BYTE *)malloc(2 * TracksInfo.Hdr.FCount);
	TracksInfo.FieldHistory = FieldStatus;
	memset(FieldStatus, SCAN_1_NOTSCANNED, 2 * TracksInfo.Hdr.FCount);
	
	{
   		char IDString[256];
		sprintf(IDString, "Scanning Prediction %d/%d/%d/%d", TracksInfo.Hdr.ID.Part[0], TracksInfo.Hdr.ID.Part[1],
      		TracksInfo.Hdr.ID.Part[2], TracksInfo.Hdr.ID.Part[3]);
		GENERATE_MSG(IDString);
   		};

	ISheetMap *iSM = Select_Map(TargetTrack.MapN);
	if (!iSM)
	{
		GENERATE_EXIT_MSG("SCANTRACKS FAILED - INVALID MAP SELECTION\n", false);
		};
	iSM->DirFixPoint(TargetTrack.Pos.Y, TargetTrack.Pos.Z);
	iSM->DirMapPoint(TargetTrack.Pos.Y, TargetTrack.Pos.Z, &StageX, &StageY);

	iFG->SetLiveGrab();
	FM->SetStart(StageX, StageY);

	FocusDepths KnownFocus = GetNextFocusDepths(TracksInfo.Hdr.YPos, TracksInfo.Hdr.ZPos, StageX, StageY);
	iFG->SetSingleFrameGrab();
	FocusDepths NewFocus = KnownFocus;


  	TCount[0] = TCount[1] = FTCount[0] = FTCount[1] = LCount = 0;

	int i, k;
	float f;
	i = 0;

	LOCK_MONITOR;
	STM_SET_ID(TracksInfo.Hdr.ID);
	STM_SET_POSXY(TracksInfo.Hdr.YPos, TracksInfo.Hdr.ZPos);
	STM_SET_SLOPEXY(TracksInfo.Hdr.YSlope, TracksInfo.Hdr.ZSlope);
	STM_SET_TRACKS(i, i);
	STM_SET_CLUSTERSLAYER(i, i);
	STM_SET_LIGHTLEVEL(i);
	f = KnownFocus.TopExt - KnownFocus.TopInt;
	STM_SET_TOPFOCUS(f, KnownFocus.TopInt);
	f = KnownFocus.BottomInt - KnownFocus.BottomExt;
	STM_SET_BOTTOMFOCUS(f, KnownFocus.TopInt - KnownFocus.BottomInt);
	STM_SET_SIDEFIELD(i, i);
	STM_SET_ACTION(STM_ACTION_MOVING);
	UNLOCK_MONITOR;

	BYTE *pImage;
	DWORD ScanRetCode;
	int FieldCount = 0;
	bool StageFault = false;
	bool FocusFault = false;
	int CountOfFocusFaults = 0;
	bool ScanningOk = true;
	bool RetCode;
	int PrevTCount[2] = {0, 0};
	int PrevFTCount[2] = {0, 0};
  	int NextCommand;
	bool OneFound = false;
	int PauseEachField = SD.OptD.PauseEachField;
	OverridePauseEachField = false;

	iFG->SetSingleFrameGrab();
	iStMon->EnableMonitor(false);
	iSM->InvFixPoint(StageX, StageY);
	BackGroundTrackingInfo.TracksFoundCount = BackGroundTrackingInfo.FlatTracksFoundCount = 0;

  	FieldCount = 0;
	UINT FrameDelay = 0;
	iFG->GetCurrentFrameGrabDelay(&FrameDelay);
	do
  	{
		LOCK_MONITOR;
		f = KnownFocus.TopExt - KnownFocus.TopInt;
		STM_SET_TOPFOCUS(f, KnownFocus.TopInt);
		f = KnownFocus.BottomInt - KnownFocus.BottomExt;
		STM_SET_BOTTOMFOCUS(f, KnownFocus.TopInt - KnownFocus.BottomInt);
		STM_SET_SIDEFIELD(0, FieldCount + 1);
		STM_SET_ACTION(STM_ACTION_MOVINGNEXTFIELD);
		UNLOCK_MONITOR;

  		FM->GetFieldPos(FieldCount, &fNewX, &fNewY);
		NewX = fNewX;
		NewY = fNewY;
     	if (WaitForSingleObject(PauseEvent, 0) == WAIT_OBJECT_0)
		{
			iFG->SetLiveGrab();
			iStMon->EnableMonitor(true);
			while (WaitForSingleObject(PauseEvent, 0) == WAIT_OBJECT_0) Sleep(0);
			iStMon->EnableMonitor(false);
			iFG->SetSingleFrameGrab();
			for (i = 0; i < FrameDelay; i++)
			{
				iFG->HoldFrame(&pImage);
				iFG->ReleaseFrame();
				};
			};
		if (!SharpPosition(NewX, NewY, SD.StageD.HorizontalSpeed,
		 		SD.StageD.LongDistAcc, SD.StageD.XTolerance, SD.StageD.YTolerance,
		     	KnownFocus.TopExt + SD.StageD.ZTolerance, SD.StageD.RewindSpeed, SD.StageD.ZAcc, SD.StageD.ZTolerance))
		{
			TracksInfo.Hdr.FCount = 0;
        	StageFault = true;
			FieldStatus[FieldCount] = SCAN_1_LIMITER;
			ScanStatus.StageFaults++;
			LOCK_MONITOR;
			GM_SET_STAGEFAULTS(ScanStatus.StageFaults);
			UNLOCK_MONITOR;
	        };
		WaitForBkGndTracking();
		if (FieldCount && (!PauseEachField))
		{
      		if (SD.OptD.ScanBoth) 
			{
				TCount[1] += BackGroundTrackingInfo.TracksFoundCount;
				FTCount[1] += BackGroundTrackingInfo.FlatTracksFoundCount;
				}
			else 
			{
				TCount[0] += BackGroundTrackingInfo.TracksFoundCount;
				FTCount[0] += BackGroundTrackingInfo.FlatTracksFoundCount;
				}
			LOCK_MONITOR;
			STM_SET_TRACKS(TCount[0], TCount[1]);
			UNLOCK_MONITOR;
			};
		if (!StageFault)
		{
			bool LastFocusFault = FocusFault;
			if (OverridePauseEachField)
			{	
           		PauseEachField = SD.OptD.PauseEachField;
				OverridePauseEachField = false;
				};
			REPORT_SCAN(ScanRetCode = Scan_Top(FieldCount, KnownFocus, &NewFocus, !FieldCount || FocusFault));
			FieldStatus[FieldCount] = ScanRetCode;
			if (ScanRetCode == SCAN_1_OK)
			{
           		KnownFocus = NewFocus;
				if (SD.OptD.ScanBoth)
				{
					iSt->PosMove(2, NewFocus.BottomInt + SD.StageD.SlowdownLength, SD.StageD.BaseCrossingSpeed, SD.StageD.ZAcc);
					WaitForBkGndTracking();
         			PrevTCount[0] = TCount[0];
         			PrevFTCount[0] = FTCount[0];
					TCount[0] += BackGroundTrackingInfo.TracksFoundCount;
					FTCount[0] += BackGroundTrackingInfo.FlatTracksFoundCount;
					BackGroundTrackingInfo.TracksFoundCount = BackGroundTrackingInfo.FlatTracksFoundCount = 0;
					LOCK_MONITOR;
					STM_SET_TRACKS(TCount[0], TCount[1]);
					STM_SET_SIDEFIELD(1, FieldCount + 1);
					UNLOCK_MONITOR;
		   			if (OverridePauseEachField)
	   				{
     	   	   			PauseEachField = SD.OptD.PauseEachField;
        	   			OverridePauseEachField = false;
   	           			};
					for (i = 0; i < FrameDelay; i++)
					{
						iFG->HoldFrame(&pImage);
						iFG->ReleaseFrame();
						};
		   			REPORT_SCAN(ScanRetCode = Scan_Bottom(FieldCount, KnownFocus, &NewFocus, !FieldCount || LastFocusFault, true));
					FieldStatus[FieldCount + TracksInfo.Hdr.FCount] = ScanRetCode;
         			if (ScanRetCode == SCAN_1_OK) KnownFocus = NewFocus;
            		else if (!FieldCount && (ScanRetCode == SCAN_1_NOFOCUS || ScanRetCode == SCAN_1_TOOFAST) && !SideSwapped)
					{
   	         			if (SideSwapped = CheckSideSwap(&NewFocus))
						{
					 		KnownFocus = NewFocus;
				    	    FieldCount--;
           	  				WaitForBkGndTracking();
                  			BackGroundTrackingInfo.TracksFoundCount = 0;
                  			BackGroundTrackingInfo.FlatTracksFoundCount = 0;
							TCount[0] = TCount[1] = FTCount[0] = FTCount[1] = 0;
   							ScanningOk = true;
      	         			};
         				};
            		}
				else ScanningOk = true;
				};
      		}
		else ScanningOk = false;
		NextCommand = Master->PeekLastImmediate();
   		if (NextCommand == COMMAND_REPORT)
		{	
			SAFE_WRITE_STRING(iOCS, ScanStatus.GenerateReport());
        	Master->GetNext();
		  	}
   		else if (NextCommand == COMMAND_EXIT)
		{
        	*pTermination = true;
   			Master->GetNext();
			delete FM;
			free(FieldStatus);
	     	return false;
   	  		};

		if (PauseEachField)
		{
	  		WaitForBkGndTracking();
			if (SD.OptD.ScanBoth)
			{
         		PrevTCount[1] = TCount[1];
				PrevFTCount[1] = FTCount[1];
				TCount[1] += BackGroundTrackingInfo.TracksFoundCount;
				FTCount[1] += BackGroundTrackingInfo.FlatTracksFoundCount;
				}
	        else
		    {
			 	PrevTCount[0] = TCount[0];
			 	PrevFTCount[0] = FTCount[0];
				TCount[0] += BackGroundTrackingInfo.TracksFoundCount;
				FTCount[0] += BackGroundTrackingInfo.FlatTracksFoundCount;
				};
	        BackGroundTrackingInfo.TracksFoundCount = BackGroundTrackingInfo.FlatTracksFoundCount = 0;
			LOCK_MONITOR;
			STM_SET_TRACKS(TCount[0], TCount[1]);
			UNLOCK_MONITOR;
			iFG->SetLiveGrab();
			iFG->GetColorCode(VC_TRANSPARENT, &i);
			iFG->Clear(i);
        	for (k = 0; k < (SD.OptD.ScanBoth ? 2 : 1); k++)
				ShowTracks(iSM, TSpace[k] + PrevTCount[k], TCount[k] - PrevTCount[k], 
					FTSpace[k] + PrevFTCount[k], FTCount[k] - PrevFTCount[k], 
						k ? NewFocus.TopInt : NewFocus.BottomInt, k, false);
			GENERATE_MSG("HELP_REQUEST - Press OK to continue scanning");
			RestorePriorities();
			iStMon->EnableMonitor(true);
        	MessageBox(0, "Press OK to continue scanning", "Display Active", MB_OK);
			RestorePriorities();
			iFG->Clear(i);
			iStMon->EnableMonitor(false);
			RestorePriorities();
			iFG->SetSingleFrameGrab();
			for (i = 0; i < FrameDelay; i++)
			{
				iFG->HoldFrame(&pImage);
				iFG->ReleaseFrame();
				};
			RestorePriorities();
			};
		}
	while (ScanningOk && (++FieldCount < TracksInfo.Hdr.FCount));
	WaitForBkGndTracking();
	if (SD.OptD.ScanBoth) 
	{
		TCount[1] += BackGroundTrackingInfo.TracksFoundCount;
		FTCount[1] += BackGroundTrackingInfo.FlatTracksFoundCount;
		}
	else 
	{
		TCount[0] += BackGroundTrackingInfo.TracksFoundCount;
		FTCount[0] += BackGroundTrackingInfo.FlatTracksFoundCount;
		}
	LOCK_MONITOR;
	STM_SET_TRACKS(TCount[0], TCount[1]);
	f = KnownFocus.TopExt - KnownFocus.TopInt;
	STM_SET_TOPFOCUS(f, KnownFocus.TopInt);
	f = KnownFocus.BottomInt - KnownFocus.BottomExt;
	STM_SET_BOTTOMFOCUS(f, KnownFocus.TopInt - KnownFocus.BottomInt);
	UNLOCK_MONITOR;

	delete FM;
// TODO: add check for iFt2 and so on...	
	if (iFt)
	{
		if (iFt2)
		{
			iFt2->Fit2(TSpace[0], &TCount[0], FTSpace[0], &FTCount[0], KnownFocus.TopInt, SD.EmuD.TopThickness * SD.EmuD.Shrinkage);
			iFt2->Fit2(TSpace[1], &TCount[1], FTSpace[1], &FTCount[1], KnownFocus.BottomInt, -SD.EmuD.BottomThickness * SD.EmuD.Shrinkage);
			FTCount[0] = DiscardInvalidFlatTracks(FTSpace[0], FTCount[0], TracksInfo.Hdr.FitCorrectionDataSize);
			FTCount[1] = DiscardInvalidFlatTracks(FTSpace[1], FTCount[1], TracksInfo.Hdr.FitCorrectionDataSize);
			}
		else  
		{
			iFt->Fit(TSpace[0], &TCount[0], KnownFocus.TopInt, SD.EmuD.TopThickness * SD.EmuD.Shrinkage);
			iFt->Fit(TSpace[1], &TCount[1], KnownFocus.BottomInt, -SD.EmuD.BottomThickness * SD.EmuD.Shrinkage);
			};
		TCount[0] = DiscardInvalidTracks(TSpace[0], TCount[0], TracksInfo.Hdr.FitCorrectionDataSize);
		TCount[1] = DiscardInvalidTracks(TSpace[1], TCount[1], TracksInfo.Hdr.FitCorrectionDataSize);
		};


	LOCK_MONITOR;
	STM_SET_TRACKS(TCount[0], TCount[1]);
	UNLOCK_MONITOR;

	if (ScanningOk && ((CountOfFocusFaults * 2) < FieldCount)) AddFocusInfo(TracksInfo.Hdr.YPos, TracksInfo.Hdr.ZPos, NewFocus);
	if (SD.OptD.CenterScanBack)
	{
		Track *BestCandidate = 0;
		float BestDisp, Disp;
		if (SD.SeekerD.CheckTop)
		{
			for (i = 0; i < TCount[0]; i++)
			{
       			Disp = hypot(TSpace[0][i].Slope.X - TargetTrack.Slope.Top.Y, TSpace[0][i].Slope.Y - TargetTrack.Slope.Top.Z);
				if (Disp < TargetTrack.SideSlopeTolerance)
           			if (Retry || (hypot(TSpace[0][i].Intercept.X - TargetTrack.Pos.Y, TSpace[0][i].Intercept.Y - TargetTrack.Pos.Z) < SD.SeekerD.PosTolerance))
		            	if (!BestCandidate || (Disp < BestDisp))
   						{
			       			BestCandidate = TSpace[0] + i;
							BestDisp = Disp;
       	      				};
    			};
			if (SD.SeekerD.CheckBottom)
			{
				for (i = 0; i < TCount[1]; i++)
				{
       				Disp = hypot(TSpace[1][i].Slope.X - TargetTrack.Slope.Top.Y, TSpace[1][i].Slope.Y - TargetTrack.Slope.Top.Z);
					if (Disp <	TargetTrack.SideSlopeTolerance)
	           			if (Retry || (hypot(TSpace[1][i].Intercept.X - TargetTrack.Pos.Y, TSpace[1][i].Intercept.Y - TargetTrack.Pos.Z) < SD.SeekerD.PosTolerance))
			           		if (!BestCandidate || (Disp < BestDisp))
   							{
				       			BestCandidate = TSpace[1] + i;
								BestDisp = Disp;
       			  				};
					};
    			};
			};

		if (ScanReport)
		{ 	
			if (ScanReport->Found.IsValid = BestCandidate)
			{
    			ScanReport->Found.Pos.Y = BestCandidate->Intercept.X + BestCandidate->Slope.X * (KnownFocus.TopInt - BestCandidate->Intercept.Z);
    			ScanReport->Found.Pos.Z = BestCandidate->Intercept.Y + BestCandidate->Slope.Y * (KnownFocus.TopInt - BestCandidate->Intercept.Z);
       			ScanReport->Found.Slope.Global.Y = BestCandidate->Slope.X;
				ScanReport->Found.Slope.Global.Z = BestCandidate->Slope.Y;
				GENERATE_MSG("SCANTRACKS RESULT: TRACK FOUND");
   				}
			else if (SD.SeekerD.ZoneScanning && !Retry)
			{
       			free(FieldStatus);
       			GENERATE_MSG("SCANTRACKS RESULT: TRACK NOT FOUND - RETRYING WITH ZONE SCANNING");
				return Scan_Tracks(Cmd, ScanReport, true);
				}
			else GENERATE_MSG("SCANTRACKS RESULT: TRACK NOT FOUND");
			};
   		};

	TracksInfo.Hdr.FCount = FieldCount;
	TracksInfo.Hdr.TCount[0] = TCount[0];
	TracksInfo.Hdr.TCount[1] = TCount[1];
// TODO: add Black Tracks Count
	TracksInfo.Hdr.BTCount[0] = 0;
	TracksInfo.Hdr.BTCount[1] = 0;
	TracksInfo.Hdr.CodingMode = BULK_COMPRESSION_NULL;
	TerminateBkGndTracking();

	RestorePriorities();
	
	LOCK_MONITOR;
// TODO: shouldn't we update ScanStatus???
	GM_SET_TKSFNDSCAN(ScanStatus.TracksFound, ScanStatus.TracksScanned);
	UNLOCK_MONITOR;

	TracksInfo.Hdr.RelevantZs.TopExt = NewFocus.TopExt;
	TracksInfo.Hdr.RelevantZs.TopInt = NewFocus.TopInt;
	TracksInfo.Hdr.RelevantZs.BottomInt = NewFocus.BottomInt;
	TracksInfo.Hdr.RelevantZs.BottomExt = NewFocus.BottomExt;
	TracksInfo.pTracks[0] = TSpace[0];
	TracksInfo.pTracks[1] = TSpace[1];
	TracksInfo.pFlatTracks[0] = FTSpace[0];
	TracksInfo.pFlatTracks[1] = FTSpace[1];

	if (iIO->Write((HSySalHANDLE)NULL, (BYTE *)&TracksInfo, (UINT *)&i, NULL) != S_OK)
	{
		sprintf(GlobalObjectMessage, "SCANTRACKS FAILED - I/O ERROR (code: %08X)", i);
		GENERATE_EXIT_MSG(GlobalObjectMessage, false);
		};

	free(FieldStatus);

	GENERATE_EXIT_MSG("SCANTRACKS SUCCESS", RetCode);
	};


void CScanner::TracksToWorld(ISheetMap *iSM, double actx, double acty, float camcx, float camcy, float basedepth, Track *TSpace, int TCount)
{
	int i, j;
	TVector *Points;
	int p;
	double x, y;

	for (i = 0; i < TCount; i++)
	{
   		if (TSpace[i].Valid)
		{
			p = TSpace[i].PointsN;
   			Points = TSpace[i].pPoints;
      		for (j = 0; j < p; j++)
			{
				Points[j].X += actx - camcx;
				Points[j].Y += acty - camcy;
         		iSM->InvMapPoint(Points[j].X, Points[j].Y, &x, &y);
				Points[j].X = x;
   				Points[j].Y = y;
				Points[j].Z = (Points[j].Z - basedepth) * SD.EmuD.Shrinkage + basedepth;
				};
	   		};
		};
   };


void CScanner::FlatTracksToWorld(ISheetMap *iSM, double actx, double acty, float camcx, float camcy, float basedepth, FlatTrack *FTSpace, int FTCount)
{
	int i, j;
	FlatStrip *Strips;
	int p;
	double x, y;

	for (i = 0; i < FTCount; i++)
	{
   		if (FTSpace[i].Valid)
		{
			p = FTSpace[i].StripsN;
   			Strips = FTSpace[i].pStrips;
      		for (j = 0; j < p; j++)
			{
				Strips[j].X += actx - camcx;
				Strips[j].Y += acty - camcy;
         		iSM->InvMapPoint(Strips[j].X, Strips[j].Y, &x, &y);
				Strips[j].X = x;
   				Strips[j].Y = y;
				Strips[j].Z = (Strips[j].Z - basedepth) * SD.EmuD.Shrinkage + basedepth;
				};
	   		};
		};
   };



FocusDepths CScanner::GetNextFocusDepths(float YPos, float ZPos, float ActX, float ActY)
{
	FocusDepths Temp;
	int i;
	float TotalWeight = 0.f;
	float Weight;
	float FY, FZ;

	Temp.TopExt = Temp.TopInt = Temp.BottomInt = Temp.BottomExt = 0;

	for (i = 0; i < (LFD_XCount * LFD_YCount); i++)
	{
   		FY = EmuEdges.Left + ((i % LFD_XCount) + .5f) * SD.EmuD.DepthCoherenceLength;
   		FZ = EmuEdges.Bottom + ((i / LFD_XCount) + .5f) * SD.EmuD.DepthCoherenceLength;
   		if (FocusInfo[i].HitCount)
		{
	   		Weight = exp(- hypot(FY - YPos, FZ - ZPos) / SD.EmuD.DepthCoherenceLength);
   			TotalWeight += Weight;
      		Temp.TopExt += Weight * FocusInfo[i].TopExt;
			Temp.TopInt += Weight * FocusInfo[i].TopInt;
   			Temp.BottomInt += Weight * FocusInfo[i].BottomInt;
      		Temp.BottomExt += Weight * FocusInfo[i].BottomExt;
	     	};
		}
	if (TotalWeight == 0.f)
	{
		float Z;
   		iSt->Stop(2);
		iSt->GetPos(2, &Z);
		EmuEdges.Left = ActX - SD.EmuD.Width;
		EmuEdges.Right = ActX + SD.EmuD.Width;
		EmuEdges.Bottom = ActY - SD.EmuD.Height;
		EmuEdges.Top = ActY + SD.EmuD.Height;
		SharpPosition(ActX, ActY, SD.StageD.HorizontalSpeed,
  			SD.StageD.LongDistAcc, SD.StageD.XTolerance, SD.StageD.YTolerance,
     		Z, SD.StageD.RewindSpeed, SD.StageD.ZAcc, SD.StageD.ZTolerance);
		iFG->SetLiveGrab();
		GENERATE_MSG("HELP_REQUEST - Place the stage at the top surface of the base and press OK");
		RestorePriorities();
		iStMon->EnableMonitor(true);
		MessageBox(NULL, "Place the stage at the top surface of the base and press OK", "Help Request", MB_OK);
		iSt->GetPos(2, &Temp.TopInt);
		iStMon->EnableMonitor(false);
		RestorePriorities();
		iFG->SetSingleFrameGrab();

		Temp.TopExt = Temp.TopInt + SD.EmuD.TopThickness;
		Temp.BottomInt = Temp.TopInt - SD.EmuD.BaseThickness;
		Temp.BottomExt = Temp.BottomInt - SD.EmuD.BottomThickness;
		AddFocusInfo(YPos, ZPos, Temp);
		return Temp;
   		};

	Temp.TopExt /= TotalWeight;
  	Temp.TopInt /= TotalWeight;
	Temp.BottomInt /= TotalWeight;
  	Temp.BottomExt /= TotalWeight;
	return Temp;
	};


bool CScanner::AddFocusInfo(float X, float Y, FocusDepths F)
{
	int IX = (X - EmuEdges.Left) / SD.EmuD.DepthCoherenceLength;
	if ((IX < 0) || (IX >= LFD_XCount)) return false;
	int IY = (Y - EmuEdges.Bottom) / SD.EmuD.DepthCoherenceLength;
	if ((IY < 0) || (IY >= LFD_YCount)) return false;
	int i = IX + IY * LFD_XCount;
	FocusDepths G = F;
	int Hits = FocusInfo[i].HitCount;
	if (Hits)
	{
		G.TopExt += Hits * FocusInfo[i].TopExt;
		G.TopInt += Hits * FocusInfo[i].TopInt;
		G.BottomInt += Hits * FocusInfo[i].BottomInt;
		G.BottomExt += Hits * FocusInfo[i].BottomExt;
		};
	Hits++;
	G.TopExt /= Hits;
	G.TopInt /= Hits;
	G.BottomInt /= Hits;
	G.BottomExt /= Hits;
	if ((fabs(G.TopExt - G.TopInt - SD.EmuD.TopThickness) < SD.StageD.ThicknessTolerance) &&
   		(fabs(G.TopInt - G.BottomInt - SD.EmuD.BaseThickness) < SD.StageD.ThicknessTolerance) &&
		(fabs(G.BottomInt - G.BottomExt - SD.EmuD.BottomThickness) < SD.StageD.ThicknessTolerance))
	{
   		FocusInfo[i].TopExt = G.TopExt;
   		FocusInfo[i].TopInt = G.TopInt;
   		FocusInfo[i].BottomInt = G.BottomInt;
   		FocusInfo[i].BottomExt = G.BottomExt;
		FocusInfo[i].HitCount = Hits;
		return true;
   		};
	return false;
	};


int CScanner::DiscardInvalidTracks(Track *TSpace, int TCount, int FitCorrectionDataSize)
{
	int V, C;
	TVector *pPoints;
	BYTE *pCorr;
	V = 0;
	for (C = 0; C < TCount; C++)
	{
   		if (TSpace[C].Valid)
		{
			pPoints = TSpace[V].pPoints;
			pCorr = TSpace[V].pCorrection;
			TSpace[V] = TSpace[C];
			TSpace[V].pPoints = pPoints;
			TSpace[V].pCorrection = pCorr;
			memcpy(TSpace[V].pPoints, TSpace[C].pPoints, sizeof(TVector) * TSpace[C].PointsN);
			if (FitCorrectionDataSize)
				memcpy(TSpace[V].pCorrection, TSpace[C].pCorrection, FitCorrectionDataSize);
			V++;
      		};
   		};
	return V;
	};


int CScanner::DiscardInvalidFlatTracks(FlatTrack *FTSpace, int FTCount, int FitCorrectionDataSize)
{
	int V, C;
	FlatStrip *pStrips;
	BYTE *pCorr;
	V = 0;
	for (C = 0; C < FTCount; C++)
	{
   		if (FTSpace[C].Valid)
		{
			pStrips = FTSpace[V].pStrips;
			pCorr = FTSpace[V].pCorrection;
			FTSpace[V] = FTSpace[C];
			FTSpace[V].pStrips = pStrips;
			FTSpace[V].pCorrection = pCorr;
			memcpy(FTSpace[V].pStrips, FTSpace[C].pStrips, sizeof(TVector) * FTSpace[C].StripsN);
			if (FitCorrectionDataSize)
				memcpy(FTSpace[V].pCorrection, FTSpace[C].pCorrection, FitCorrectionDataSize);
			V++;
      		};
   		};
	return V;
	};


void CScanner::ShowTracks(ISheetMap *iSM, Track *TSpace, int TCount, FlatTrack *FTSpace, int FTCount, double OtherZ, int Side, bool ShowFits)
{
	float ActX, ActY;
	iSt->GetPos(0, &ActX);
	iSt->GetPos(1, &ActY);
	float CamCX = CAM.Width / 2 * CAM.PixelToMicronX;
	float CamCY = CAM.Height / 2 * CAM.PixelToMicronY;
	double PrevX, PrevY, NextX, NextY;
	Track TempTrack;
	FlatTrack TempFTrack;
	int i, j, c;

	for (i = 0; i < TCount; i++)
  	{
		TempTrack = TSpace[i];
		if (TempTrack.Valid)
		{
			iSM->DirMapPoint(TempTrack.pPoints[0].X, TempTrack.pPoints[0].Y, &PrevX, &PrevY);
			PrevX = (PrevX - ActX + CamCX) / CAM.PixelToMicronX;
   			PrevY = (PrevY - ActY + CamCY) / CAM.PixelToMicronY;
      		for (j = 1; j < TempTrack.PointsN; j++)
      		{
				iSM->DirMapPoint(TempTrack.pPoints[j].X, TempTrack.pPoints[j].Y, &NextX, &NextY);
           		NextX = (NextX - ActX + CamCX) / CAM.PixelToMicronX;
     	     	NextY = (NextY - ActY + CamCY) / CAM.PixelToMicronY;
				iFG->GetColorCode(Side ? VC_LTBLUE : VC_LTRED, &c);
        		iFG->Line(PrevX, PrevY, NextX, NextY, c);
				PrevX = NextX;
				PrevY = NextY;
           		};
			if (ShowFits)
			{
				iSM->DirMapPoint(TempTrack.Intercept.X, TempTrack.Intercept.Y, &PrevX, &PrevY);
   				PrevX = (PrevX - ActX + CamCX) / CAM.PixelToMicronX;
  	   			PrevY = (PrevY - ActY + CamCY) / CAM.PixelToMicronY;
         		iSM->DirMapPoint(TempTrack.Intercept.X + TempTrack.Slope.X * (OtherZ - TempTrack.Intercept.Z),
			    	TempTrack.Intercept.Y + TempTrack.Slope.Y * (OtherZ - TempTrack.Intercept.Z), &NextX, &NextY);
   				NextX = (NextX - ActX + CamCX) / CAM.PixelToMicronX;
  	   			NextY = (NextY - ActY + CamCY) / CAM.PixelToMicronY;
				iFG->GetColorCode(Side ? VC_DKGREEN : VC_DKYELLOW, &c);
     	   		iFG->Line(PrevX, PrevY, NextX, NextY, c);
				};
			};
   		};
	for (i = 0; i < FTCount; i++)
  	{
		TempFTrack = FTSpace[i];
		if (TempFTrack.Valid)
		{
			iSM->DirMapPoint(TempFTrack.pStrips[0].X, TempFTrack.pStrips[0].Y, &PrevX, &PrevY);
			PrevX = (PrevX - ActX + CamCX) / CAM.PixelToMicronX;
   			PrevY = (PrevY - ActY + CamCY) / CAM.PixelToMicronY;
      		for (j = 1; j < TempFTrack.StripsN; j++)
      		{
				iSM->DirMapPoint(TempFTrack.pStrips[j].X, TempFTrack.pStrips[j].Y, &NextX, &NextY);
           		NextX = (NextX - ActX + CamCX) / CAM.PixelToMicronX;
     	     	NextY = (NextY - ActY + CamCY) / CAM.PixelToMicronY;
				iFG->GetColorCode(Side ? VC_LTBLUE : VC_LTRED, &c);
        		iFG->Line(PrevX, PrevY, NextX, NextY, c);
				PrevX = NextX;
				PrevY = NextY;
           		};
			};
   		};
	};


void CScanner::RestorePriorities()
{
	return;
// TODO: delete this function at all.
	};



#define AYYLIM .003
#define AYZLIM .003
#define AZYLIM .003
#define AZZLIM .003
#define LONGADJLIM 1000.
#define TYLIM 10000.
#define TZLIM 10000.

#define GMULTCENTER 1.0
#define GMULTTOL	   .3
#define GTYLIM		  20.
#define GTZLIM		  20.

#define TMULTCENTER 1.0
#define TMULTTOL	   .5
#define TTYLIM		  30.
#define TTZLIM		  30.

#define BMULTCENTER 1.0
#define BMULTTOL	   .5
#define BTYLIM		  30.
#define BTZLIM		  30.


void CScanner::RearrangePredictions(int PredCount, ScanResult *Batch)
{
	float MinY, MaxY, MinZ, MaxZ;
	int i, j, my, mz, iz, iy;
	float DyCell, DzCell;

	if (PredCount < 2) return;
	MinY = MaxY = Batch[0].Pred.Pos.Y;
	MinZ = MaxZ = Batch[0].Pred.Pos.Z;
	for (i = 1; i < PredCount; i++)
	{
		if (Batch[i].Pred.Pos.Y < MinY) MinY = Batch[i].Pred.Pos.Y;
		else if (Batch[i].Pred.Pos.Y > MaxY) MaxY = Batch[i].Pred.Pos.Y;
		if (Batch[i].Pred.Pos.Z < MinZ) MinZ = Batch[i].Pred.Pos.Z;
		else if (Batch[i].Pred.Pos.Z > MaxZ) MaxZ = Batch[i].Pred.Pos.Z;
		};
	DyCell = (MaxY - MinY) / sqrt(PredCount);
	DzCell = (MaxZ - MinZ) / sqrt(PredCount);
	my = (MaxY - MinY) / DyCell + 1;
	mz = (MaxZ - MinZ) / DzCell + 1;
	int *CellIndexes = (int *)malloc(sizeof(int) * PredCount);
	for (i = 0; i < PredCount; i++)
	{	
		iy = floor((Batch[i].Pred.Pos.Y - MinY) / DyCell);
   		iz = floor((Batch[i].Pred.Pos.Z - MinZ) / DzCell);
		CellIndexes[i] = ((iz % 2) ? iy : (my - iy)) + my * iz;
		};
	for (i = 0; i < PredCount; i++)
		for (j = i + 1; j < PredCount; j++)
			if (CellIndexes[i] > CellIndexes[j])
			{
				int t = CellIndexes[i];
				CellIndexes[i] = CellIndexes[j];
				CellIndexes[j] = t;
				ScanResult Temp = Batch[i];
				Batch[i] = Batch[j];
				Batch[j] = Temp;
				};
	free(CellIndexes);
	};


TrackPrediction CScanner::CorrectPrediction(TrackPrediction &Original)
{
	TrackPrediction Temp = Original;
	if (PredCorrection.IsReliable)
	{
		float TotalWeight = 0.f;
		float Weight;
		float DX = 0.f, DY = 0.f, X, Y;
		int i, n = PredCorrection.CountOfCellsX * PredCorrection.CountOfCellsY;
		for (i = 0; i < n; i++)
		{
	   		if (PredCorrection.Cells[i].HitCount)
			{
		   		X = EmuEdges.Left + ((i % PredCorrection.CountOfCellsX) + .5f) * PredCorrection.CellSize;
		   		Y = EmuEdges.Bottom + ((i / PredCorrection.CountOfCellsX) + .5f) * PredCorrection.CellSize;
		   		Weight = exp(- hypot(X - Original.Pos.Y, Y - Original.Pos.Z) / PredCorrection.CellSize);
   				TotalWeight += Weight;
				DX += Weight * PredCorrection.Cells[i].DeltaX;
				DY += Weight * PredCorrection.Cells[i].DeltaY;
				};
			};
		if (TotalWeight > 0.f)
		{
			Temp.Pos.Y += DX / TotalWeight;
			Temp.Pos.Z += DY / TotalWeight;
      		};
		};
	return Temp;
	};


void CScanner::ResetPredictionCorrections()
{
	PredCorrection.IsReliable = false;
	int i, n = PredCorrection.CountOfCellsX * PredCorrection.CountOfCellsY;
	for (i = 0; i < n; i++)
	{
   		PredCorrection.Cells[i].DeltaX = PredCorrection.Cells[i].DeltaY = 0.f;
		PredCorrection.Cells[i].HitCount = 0;
   		};
	};


bool CScanner::AddPredictionsCorrection(int ScanCount, ScanResult *Batch)
{
	int IX = (Batch->Pred.Pos.Y - EmuEdges.Left) / PredCorrection.CellSize;
	if ((IX < 0) || (IX >= PredCorrection.CountOfCellsX)) return false;
	int IY = (Batch->Pred.Pos.Z - EmuEdges.Bottom) / PredCorrection.CellSize;
	if ((IY < 0) || (IY >= PredCorrection.CountOfCellsY)) return false;
	int i = IX + IY * PredCorrection.CountOfCellsX;
	float DX = Batch->Found.Pos.Y - Batch->Pred.Pos.Y;
	float DY = Batch->Found.Pos.Z - Batch->Pred.Pos.Z;
	if (PredCorrection.Cells[i].HitCount)
	{
   		DX += PredCorrection.Cells[i].HitCount * PredCorrection.Cells[i].DeltaX;
   		DY += PredCorrection.Cells[i].HitCount * PredCorrection.Cells[i].DeltaY;
		};
	PredCorrection.Cells[i].HitCount++;
	PredCorrection.Cells[i].DeltaX = DX / PredCorrection.Cells[i].HitCount;
	PredCorrection.Cells[i].DeltaY = DY / PredCorrection.Cells[i].HitCount;
	int n = PredCorrection.CountOfCellsX * PredCorrection.CountOfCellsY;
	int h = 0;
	for (i = 0; i < n; h += PredCorrection.Cells[i++].HitCount);
	if (h >= SD.OptD.MinSample) PredCorrection.IsReliable = true;
	return true;
	};



bool CScanner::Load_and_Exec(Command *Cmd)
{
	struct
	{
		int Count;
		ScanResult *Batch;
		} ScanBatchDescriptor;

	struct
	{
		int Count;
		BS_ClusterDump *Batch;
		} CDBatchDescriptor;

	struct
	{
		int Count;
		BS_PhotoSequence *Batch;
		} PSBatchDescriptor;

	ScanBatchDescriptor.Batch = 0;
	CDBatchDescriptor.Batch = 0;
	PSBatchDescriptor.Batch = 0;

	int Current;
	try
	{
		int i, j;
		IO_BS_Batch *pBatch = 0;
		UINT ExtErrInfo;
		CString msg;
		if (iIO->Read(NULL, (BYTE *)&pBatch, &ExtErrInfo, NULL) != S_OK) 
		{
			msg.Format("Error loading prediction batch!\r\nError code %08X.\r\nAborting batch.", ExtErrInfo);
			MessageBox(0, msg, "I/O Error", MB_ICONERROR | MB_OK);
			throw 0;
			};
		if ((pBatch->Hdr.InfoType != (BS_HEADER_BYTES | BS_PRED_SECTION)) ||
			(pBatch->Hdr.HeaderFormat != BS_HEADER_TYPE))
		{
			msg.Format("Unsupported prediction batch format!\r\nFormat type found: %02X-%04X", pBatch->Hdr.InfoType, pBatch->Hdr.HeaderFormat);
			MessageBox(0, msg, "I/O Error", MB_ICONERROR | MB_OK);
			CoTaskMemFree(pBatch);
			throw 1;
			};
		
		ScanBatchDescriptor.Count = pBatch->CountOfTracks;
		CDBatchDescriptor.Count = pBatch->CountOfClusterDumps;
		PSBatchDescriptor.Count = pBatch->CountOfPhotoSequences;

		if (ScanBatchDescriptor.Count && !(ScanBatchDescriptor.Batch = (ScanResult *)GlobalAlloc(GMEM_FIXED, ScanBatchDescriptor.Count * sizeof(ScanResult)))) throw 1;
		if (CDBatchDescriptor.Count && !(CDBatchDescriptor.Batch = (BS_ClusterDump *)GlobalAlloc(GMEM_FIXED, CDBatchDescriptor.Count * sizeof(BS_ClusterDump)))) throw 2;
		if (PSBatchDescriptor.Count && !(PSBatchDescriptor.Batch = (BS_PhotoSequence *)GlobalAlloc(GMEM_FIXED, PSBatchDescriptor.Count * sizeof(BS_PhotoSequence)))) throw 2;

		for (i = 0; i < ScanBatchDescriptor.Count; i++)
		{
			ScanBatchDescriptor.Batch[i].Pred.ID = pBatch->pTracks[i].Id;
			ScanBatchDescriptor.Batch[i].Pred.MapN = pBatch->pTracks[i].MapId.Part[3];
			///HERE!!! ADD CHECK ON MAP #
			ScanBatchDescriptor.Batch[i].Pred.Pos.Y = pBatch->pTracks[i].Pos.X;
			ScanBatchDescriptor.Batch[i].Pred.Pos.Z = pBatch->pTracks[i].Pos.Y;
			ScanBatchDescriptor.Batch[i].Pred.Slope.Top.Y = pBatch->pTracks[i].Slope.X;
			ScanBatchDescriptor.Batch[i].Pred.Slope.Top.Z = pBatch->pTracks[i].Slope.Y;
			ScanBatchDescriptor.Batch[i].Pred.Slope.Bottom.Y = pBatch->pTracks[i].Slope.X;
			ScanBatchDescriptor.Batch[i].Pred.Slope.Bottom.Z = pBatch->pTracks[i].Slope.Y;
			ScanBatchDescriptor.Batch[i].Pred.Slope.Global.Y = pBatch->pTracks[i].Slope.X;
			ScanBatchDescriptor.Batch[i].Pred.Slope.Global.Z = pBatch->pTracks[i].Slope.Y;
			ScanBatchDescriptor.Batch[i].Pred.SideSlopeTolerance = pBatch->pTracks[i].SideSlopeTol;
			ScanBatchDescriptor.Batch[i].Pred.GoodSlopeTolerance = pBatch->pTracks[i].GoodSlopeTol;
			ScanBatchDescriptor.Batch[i].Pred.GlobalSlopeTolerance = pBatch->pTracks[i].GlobalSlopeTol;
			ScanBatchDescriptor.Batch[i].Found.IsValid = false;
			};
		memcpy(CDBatchDescriptor.Batch, pBatch->pClusterDumps, sizeof(BS_ClusterDump) * pBatch->CountOfClusterDumps);
		memcpy(PSBatchDescriptor.Batch, pBatch->pPhotoSequences, sizeof(BS_PhotoSequence) * pBatch->CountOfPhotoSequences);

		CoTaskMemFree(pBatch);
		}
	catch (...)
	{
		if (ScanBatchDescriptor.Batch) GlobalFree(ScanBatchDescriptor.Batch);
		if (CDBatchDescriptor.Batch) GlobalFree(CDBatchDescriptor.Batch);
		if (PSBatchDescriptor.Batch) GlobalFree(PSBatchDescriptor.Batch);
		return false;
		};
	ScanStatus.Reset();

	ResetPredictionCorrections();

	RearrangePredictions(ScanBatchDescriptor.Count, ScanBatchDescriptor.Batch);

	GENERATE_MSG("SCANNING BATCH STARTED");
	for (Current = 0; (Current < (ScanBatchDescriptor.Count + CDBatchDescriptor.Count + PSBatchDescriptor.Count)) && (WaitForSingleObject(*pHTerminateEvent, 0) != WAIT_OBJECT_0); Current++)
	{
		Command NextCommand;

		NextCommand.OpCode = Master->PeekLastImmediate();
		if (NextCommand.OpCode == COMMAND_REPORT)
		{  
			SAFE_WRITE_STRING(iOCS, ScanStatus.GenerateReport());
			Master->GetNext();
			}
		else if (NextCommand.OpCode == COMMAND_EXIT)
		{
			if (ScanBatchDescriptor.Batch) GlobalFree(ScanBatchDescriptor.Batch);
			if (CDBatchDescriptor.Batch) GlobalFree(CDBatchDescriptor.Batch);
			if (PSBatchDescriptor.Batch) GlobalFree(PSBatchDescriptor.Batch);
			Master->GetNext();
			GENERATE_EXIT_MSG("SCANNING BATCH INTERRUPTED", false);
			}
		else if (NextCommand.OpCode == COMMAND_SCANTRACKS)
		{
			NextCommand = Master->GetNext();
//			*pTermination = false;
			Scan_Tracks(&NextCommand, 0);
			
			// HERE!!!!!!!!!! CHECK MONITORRRRR!!!
			//SD->Monitor->UpdateGlobal(&(SD->ScanStatus));
			}
		else if (NextCommand.OpCode == COMMAND_PHOTOSEQ)
		{
			NextCommand = Master->GetNext();
//			*pTermination = false;
			// HERE!!!!!!!!! CHECK MONITORRRRR!!!
			//SD->Monitor->EnablePhotoSeqGroup();
   			Scan_PhotoSequence(&NextCommand);
			// HERE!!!!!!!!! CHECK MONITORRRRR!!!
			//SD->Monitor->EnableScanBackGroup();
			//SD->Monitor->UpdateGlobal(&(SD->ScanStatus));
			};
		if (Current < ScanBatchDescriptor.Count)
		{
			NextCommand.OpCode = COMMAND_SCANTRACKS;
			NextCommand.Parameters.ScanTracks = ScanBatchDescriptor.Batch[Current].Pred;
			EnableScanTracksMonitor();
			Scan_Tracks(&NextCommand, ScanBatchDescriptor.Batch + Current);
			ScanStatus.TracksScanned++;
			if (ScanBatchDescriptor.Batch[Current].Found.IsValid)
			{
		  		ScanStatus.TracksFound++;
				if (SD.OptD.CorrectPredictions) AddPredictionsCorrection(Current, ScanBatchDescriptor.Batch + Current);
				};
			}
		else if (Current < (ScanBatchDescriptor.Count + CDBatchDescriptor.Count))
		{
			BS_ClusterDump &c = CDBatchDescriptor.Batch[Current - ScanBatchDescriptor.Count];
			NextCommand.OpCode = COMMAND_CLUSTERDUMP;
			NextCommand.Parameters.ClusterDump.ID = c.Id;
			NextCommand.Parameters.ClusterDump.MapN = c.MapId.Part[3];
			NextCommand.Parameters.ClusterDump.GrayStep = c.Threshold;
			NextCommand.Parameters.ClusterDump.Pos.Y = c.Pos.X;
			NextCommand.Parameters.ClusterDump.Pos.Z = c.Pos.Y;
			NextCommand.Parameters.ClusterDump.Pos.StartDepth = c.StartZ;
			NextCommand.Parameters.ClusterDump.Pos.EndDepth = c.EndZ;
			NextCommand.Parameters.ClusterDump.Pos.Frames = c.Frames;
			EnableClusterDumpMonitor();
			Scan_ClustersDump(&NextCommand);
			}
		else
		{
			BS_PhotoSequence &p = PSBatchDescriptor.Batch[Current - ScanBatchDescriptor.Count - CDBatchDescriptor.Count];
			NextCommand.OpCode = COMMAND_PHOTOSEQ;
			NextCommand.Parameters.PhotoSequence.ID = p.Id;
			NextCommand.Parameters.PhotoSequence.MapN = p.MapId.Part[3];
			NextCommand.Parameters.PhotoSequence.ImageSize.Width = p.XSize;
			NextCommand.Parameters.PhotoSequence.ImageSize.Height = p.YSize;
			NextCommand.Parameters.PhotoSequence.Pos.Y = p.Pos.X;
			NextCommand.Parameters.PhotoSequence.Pos.Z = p.Pos.Y;
			NextCommand.Parameters.PhotoSequence.Pos.StartDepth = p.StartZ;
			NextCommand.Parameters.PhotoSequence.Pos.EndDepth = p.EndZ;
			NextCommand.Parameters.PhotoSequence.Pos.Frames = p.Frames;
			EnablePhotoSeqMonitor();
			Scan_PhotoSequence(&NextCommand);
			};
	// HERE!!!!!!!!! CHECK MONITORRRRR!!!
	//SD->Monitor->UpdateGlobal(&(SD->ScanStatus));
    }

	if (ScanBatchDescriptor.Batch) GlobalFree(ScanBatchDescriptor.Batch);
	if (CDBatchDescriptor.Batch) GlobalFree(CDBatchDescriptor.Batch);
	if (PSBatchDescriptor.Batch) GlobalFree(PSBatchDescriptor.Batch);

	GENERATE_EXIT_MSG("SCANNING BATCH FINISHED", true);
	};


void CScanner::FlushConfig()
{
	if (iStMon)
	{
		iStMon->Release();
		iStMon = 0;
		};
	if (iFt2) 
	{
		iFt2->Release();
		iFt2 = 0;
		};
	if (iTk2) 
	{
		iTk2->Release();
		iTk2 = 0;
		};
	if (iLC) 
	{
		iLC->Release();
		iLC = 0;
		};

	int i;
	for (i = 0; i < 2; i++)
	{
		if (TSpace[i]) 
		{
			GlobalFree(TSpace[i]);
			TSpace[i] = 0;
			};
		if (FTSpace[i]) 
		{
			GlobalFree(FTSpace[i]);
			FTSpace[i] = 0;
			};
		if (FSSpace[i]) 
		{
			GlobalFree(FSSpace[i]);
			FSSpace[i] = 0;
			};
		if (GSpace[i]) 
		{
			GlobalFree(GSpace[i]);
			GSpace[i] = 0;
			};
		if (FCSpace[i]) 
		{
			GlobalFree(FCSpace[i]);
			FCSpace[i] = 0;
			};
		if (FCSpace[i + 2]) 
		{
			GlobalFree(FCSpace[i + 2]);
			FCSpace[i + 2] = 0;
			};
		if (FitWorkSpace[i]) 
		{			
			GlobalFree(FitWorkSpace[i]);
			FitWorkSpace[i] = 0;
			};
		};
	if (CSpace) 
	{
		GlobalFree(CSpace);
		CSpace = 0;
		};
	if (FocusInfo) 
	{
		GlobalFree(FocusInfo);
		FocusInfo = 0;
		};
}
