// OdysseyClass.cpp : Implementation of COdyssey
#include "stdafx.h"
#include "Odyssey1.h"
#include "OdysseyClass.h"
#include <imapi.h>
#include <math.h>
#include "EditConfig.h"
#include "Stage.h"
#include <process.h>

static BYTE	OvrColorsTable[16][3] = {	{	0,	0,	0},
										{	0,	0,	192},
										{	0,	192,	0},
										{	0,	192,	192},
										{	192,	0,	0},
										{	192,	0,	192},
										{	192,	192,	0},
										{	192,	192,	192},
										{	224,	224,	224},
										{	0,	0,	255},
										{	0,	255,	0},
										{	0,	255,	255},
										{	255,	0,	0},
										{	255,	0,	255},
										{	255,	255,	0},
										{	255,	255,	255}};

static char CursorHeaderString[ODYSSEY_CURSOR_HEADER_STRING_LENGTH] = {'O','D','Y','S','C','U','R','S'};

struct OdysseyStockCursor
{
	int Width, Height;
	int AlignX, AlignY;
	char Shape[1000];
	};

#pragma warning(disable: 4309 4305)

static OdysseyStockCursor Cross =
{
	9, 9, 4, 4,
	{ 
		0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
		}
	};

static const OdysseyStockCursor Area5 =
{
	7, 7, 3, 3,
	{ 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		}
	};

static const OdysseyStockCursor Area9 =
{
	11, 11, 5, 5,
	{ 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		}
	};

static const OdysseyStockCursor Area16 =
{
	18, 18, 8, 8,
	{ 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		}
	};

static const OdysseyStockCursor Area25 =
{
	27, 27, 13, 13,
	{ 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,		
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		}
	};	

#pragma warning(default: 4309 4305)

static struct t_DisplayChooser
{
	int Number;
	int ChosenNumber;
	int Width;
	int Height;
	int Left;
	int Top;
	};


/////////////////////////////////////////////////////////////////////////////
// COdyssey

COdyssey::COdyssey()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Name[0] = 0;
	strcpy(Slots[0].Name, "Lamp Controller");
	Slots[0].pUnknown = 0;
	Slots[0].Type = SYSAL_CONN_TYPE_NULL;

	HStatusChangeEvent = 0;
	int i;
	long d;

	O.GeneralSettings.RefreshCycleTime = 100;
	O.GeneralSettings.ClusteringProcessors = 1;

	/* Region: Main initialization */
	O.ProcSys = 0;
	imDevAlloc(0, 0, NULL, IM_DEFAULT, &O.Dev);
	imThrAlloc(O.Dev, 0, &O.GrabThread);
	imThrAlloc(O.Dev, 0, &O.ProcThread);
	imCamAlloc(O.ProcThread, NULL, IM_DEFAULT, &O.Cam);
	imSyncAlloc(O.ProcThread, &O.ProcOSB);
	imCamInquire(O.ProcThread, O.Cam, IM_DIG_SIZE_X, &O.ImageWidth);
	imCamInquire(O.ProcThread, O.Cam, IM_DIG_SIZE_Y, &O.ImageHeight);
	imCamInquire(O.ProcThread, O.Cam, IM_DIG_SIZE_BIT, &d);
	if (d != 8) MessageBox(0, "Cannot handle cameras that do not output 8 bit unsigned images!", "Camera Error", MB_ICONERROR | MB_OK);
	imBufAlloc2d(O.ProcThread, O.ImageWidth, O.ImageHeight, IM_SHORT, IM_PROC, &O.ConvBuff);
	imBufAlloc2d(O.ProcThread, O.ImageWidth, O.ImageHeight, IM_BINARY, IM_PROC, &O.BinBuff);
	/* Check */
	O.CommandQueueLength = imDevInquire(O.Dev, IM_DEV_MSG_TOTAL, 0);
	/* End check */
	/* End region */

	/* Region: initialization for VisionProcessor/VisionProcessor2 operation */
	imSyncAlloc(O.GrabThread, &O.GrabOSB[0]);
	imSyncControl(O.GrabThread, O.GrabOSB[0], IM_OSB_TIMEOUT, 0.1);
	imSyncAlloc(O.GrabThread, &O.GrabOSB[1]);
	imSyncControl(O.GrabThread, O.GrabOSB[1], IM_OSB_TIMEOUT, 0.1);
	O.ActiveProgram = -1;
	O.CycleParity = 0;
	O.CutOff = 0;
	O.Locked = false;
	O.OffX = O.OffY = 0;
	O.WinWidth = O.WinHeight = 0;
	O.SegSpace = (Segment *)GlobalAlloc(GMEM_FIXED, sizeof(Segment) * O.ImageWidth * 2 * MAX_CLUSTERING_PROCESSORS);
	O.FrameCount = 0;
	O.pFrameStartCallBack = 0;
	O.Context = 0;
	O.ExtendedOperation.OpDescriptions.Count = 0;
	O.ProgramLibrary.Count = 0;
	for (i = 0; i < MAX_PROGRAMS; i++) 
	{
		O.FilterEqBuffs[i] = 0;
		O.FlatFieldBuffs[i] = 0;
		O.KernelBuffs[i] = 0;
		}
	for (i = 0; i < MAX_FRAMES_PER_NODE; i++)
		for (d = 0; d < MAX_XOP_BUFFERS; d++)
		{
			O.XopSrcBuffs[0][i][d] = 0;
			O.XopDestBuffs[0][i][d] = 0;
			O.XopSrcBuffs[1][i][d] = 0;
			O.XopDestBuffs[1][i][d] = 0;
			}
	// mirror names for SrcGrabBuffs and HostBinBuffs are defined in the next section
	/* End region */

	/* Region: initialization for VisionProcessor3 operation */
	imThrAlloc(O.Dev, 0, &O.SeqStartThread);
	imSyncAlloc(O.GrabThread, &O.SeqOSB);
	imBufAlloc1d(O.ProcThread, 256, IM_UBYTE, IM_PROC, &O.LUTBuff);
	O.pLUT = (BYTE *)malloc(256);
	imSyncAlloc(O.ProcThread, &O.LUTOSB);
	imBufAlloc2d(O.ProcThread, O.ImageWidth, O.ImageHeight * MAX_FRAMES_PER_NODE, IM_UBYTE, IM_PROC, &O.SeqMainBuff[0]);
	imBufAlloc2d(O.ProcThread, O.ImageWidth, O.ImageHeight * MAX_FRAMES_PER_NODE, IM_BINARY, IM_HOST, &O.SeqMainHostBinBuff[0]);
	imBufAlloc2d(O.ProcThread, O.ImageWidth, O.ImageHeight * MAX_FRAMES_PER_NODE, IM_UBYTE, IM_PROC, &O.SeqMainBuff[1]);
	imBufAlloc2d(O.ProcThread, O.ImageWidth, O.ImageHeight * MAX_FRAMES_PER_NODE, IM_BINARY, IM_HOST, &O.SeqMainHostBinBuff[1]);
	for (i = 0; i < MAX_FRAMES_PER_NODE; i++)
	{
		imBufChild(O.ProcThread, O.SeqMainBuff[0], 0, i * O.ImageHeight, O.ImageWidth, O.ImageHeight, &O.SeqChildBuffs[0][i]);
		imBufChild(O.ProcThread, O.SeqMainHostBinBuff[0], 0, i * O.ImageHeight, O.ImageWidth, O.ImageHeight, &O.SeqChildHostBinBuffs[0][i]);
		imBufMap(O.ProcThread, O.SeqChildHostBinBuffs[0][i], 0, 0, (void **)&O.pSeqChildHostBinBuffs[0][i], &d, &d);
		imBufChild(O.ProcThread, O.SeqMainBuff[1], 0, i * O.ImageHeight, O.ImageWidth, O.ImageHeight, &O.SeqChildBuffs[1][i]);
		imBufChild(O.ProcThread, O.SeqMainHostBinBuff[1], 0, i * O.ImageHeight, O.ImageWidth, O.ImageHeight, &O.SeqChildHostBinBuffs[1][i]);
		imBufMap(O.ProcThread, O.SeqChildHostBinBuffs[1][i], 0, 0, (void **)&O.pSeqChildHostBinBuffs[1][i], &d, &d);
		}	
	imBufAllocControl(O.ProcThread, &O.SeqCtlBuff);
	imBufAlloc1d(O.ProcThread, MAX_FRAMES_PER_NODE, IM_DOUBLE, IM_PROC_SHARED, &O.SeqStartTimeBuff);
	imBufPutField(O.ProcThread, O.SeqCtlBuff, IM_SEQ_TIME_BUF, O.SeqStartTimeBuff);
	imBufMap(O.ProcThread, O.SeqStartTimeBuff, 0, 0, (void **)&O.pSeqStartTimeBuff, &d, &d);
	imBufAlloc1d(O.ProcThread, MAX_FRAMES_PER_NODE, IM_DOUBLE, IM_PROC_SHARED, &O.SeqEndTimeBuff);
	imBufPutField(O.ProcThread, O.SeqCtlBuff, IM_SEQ_TIME_BUF2, O.SeqEndTimeBuff);
	imBufMap(O.ProcThread, O.SeqStartTimeBuff, 0, 0, (void **)&O.pSeqEndTimeBuff, &d, &d);
	O.HStart = CreateEvent(NULL, TRUE, FALSE, NULL);
	O.HReset = CreateEvent(NULL, TRUE, FALSE, NULL);
	O.HTerminate = CreateEvent(NULL, TRUE, FALSE, NULL);
	for (i = 0; i < MAX_CLUSTERING_PROCESSORS; i++)
	{
		O.ActivationRecords[i].pO = &O;
		O.ActivationRecords[i].HFinished = CreateEvent(NULL, FALSE, FALSE, NULL);
		O.ActivationRecords[i].HThread = INVALID_HANDLE_VALUE;
		O.ActivationRecords[i].ThreadIndex = i;
		}
	for (i = 0; i < 3; i++)
	{
		O.SequencePrograms[i].ActiveProgram = -1;
		O.SequencePrograms[i].Status = VP_PROGRAM_NULL;
		O.SequencePrograms[i].AIS.ImageCount = 0;
		O.SequencePrograms[i].AIS.pImages = 0;
		O.SequencePrograms[i].ProcessingProgrammed = false;
		}
	O.SrcGrabBuffs[0] = O.SeqChildBuffs[0][0];
	O.SrcGrabBuffs[1] = O.SeqChildBuffs[0][1];
	O.SrcGrabBuffs[2] = O.SeqChildBuffs[0][2];
	O.HostBinBuffs[0] = O.SeqChildHostBinBuffs[0][0];
	O.HostBinBuffs[1] = O.SeqChildHostBinBuffs[0][1];
	O.pHostBinBuffs[0] = O.pSeqChildHostBinBuffs[0][0];
	O.pHostBinBuffs[1] = O.pSeqChildHostBinBuffs[0][1];
	O.SequenceIndex = 0;
	O.ClusteringSequenceIndex = 0;
	/* End region */

	/* Region: initialization for FrameGrabber operation */
	O.Initialization = false;
	O.IsCursorAreaValid = true;
	O.GrabBuff = O.SeqChildBuffs[0][0];
	O.Display = 0;
	imBufAlloc2d(O.ProcThread, O.ImageWidth, O.ImageHeight, IM_UBYTE, IM_HOST, &O.FreezeBuff);
	imBufMap(O.ProcThread, O.FreezeBuff, 0, 0, (void **)&O.pFreezeBuff, &d, &d);
	imBufAlloc2d(O.ProcThread, O.ImageWidth, O.ImageHeight, IM_UBYTE, IM_HOST, &O.DisplayHostBuff);
	imBufMap(O.ProcThread, O.DisplayHostBuff, 0, 0, (void **)&O.pDisplayHostBuff, &d, &d);
	imBufAlloc2d(O.ProcThread, O.ImageWidth, O.ImageHeight, IM_UBYTE, IM_PROC, &O.GraphicsBuff);
	O.CursorBuff = 0;
	O.CursorVisible = false;
	O.IsThereCursor = false;
	imBufChild(O.ProcThread, IM_DISP, 0, 0, O.ImageWidth, O.ImageHeight, &O.UnderlayBuff);
	imBufChild(O.ProcThread, IM_DISP_OVERLAY, 0, 0, O.ImageWidth, O.ImageHeight, &O.OverlayBuff);
	imBufAllocControl(O.ProcThread, &O.DisplayCtlBuff);
	imBufPutField(O.ProcThread, O.DisplayCtlBuff, IM_DISP_KEY_MODE, IM_KEY_IN_RANGE);
	imBufPutField(O.ProcThread, O.DisplayCtlBuff, IM_DISP_KEY_LOW, ODYSSEY_TRANSPARENT);
	imBufPutField(O.ProcThread, O.DisplayCtlBuff, IM_DISP_KEY_HIGH, ODYSSEY_TRANSPARENT);
	imBufAlloc1d(O.ProcThread, 256, IM_RGB, IM_PROC, &O.OverlayLUT);
	SetDefaultPalette();	
	imBufClear(O.ProcThread, O.UnderlayBuff, 0, 0);
	imBufClear(O.ProcThread, O.GraphicsBuff, ODYSSEY_TRANSPARENT, 0);
	imBufClear(O.ProcThread, O.OverlayBuff, ODYSSEY_TRANSPARENT, 0);
	imBufAllocControl(O.ProcThread, &O.GraColorBuff);
	O.Initialization = true;
	/* End region */

	/* Region: initialization for Automatic light control operation */
	imBufAlloc1d(O.ProcThread, 256, IM_LONG, IM_PROC_SHARED, &O.HistoBuff);
	imBufMap(O.ProcThread, O.HistoBuff, 0, 0, (void **)&O.pHistoBuff, &d, &d);
	O.LightControlSettings.LampTimeConstant = 100;
	O.LightControlSettings.MaxLev = 1;
	O.LightControlSettings.MinLev = 1;
	O.LightControlSettings.TargetGrayLev = 120;
	O.LightControlSettings.TargetSaturationFraction = 0;
	O.LightControlSettings.SaturationGrayLev = 255;
	/* End region */

	/* Kernel initialization */
	O.ProgramLibrary.Count = 1;
	{
		static short Kernel[36] = 
		{
			   1,  1,  1,  1,  1,  1,
			   1,  2,  3,  3,  2,  1,
			   1,  3,-13,-13,  3,  1,
			   1,  3,-13,-13,  3,  1,
			   1,  2,  3,  3,  2,  1,
			   1,  1,  1,  1,  1,  1
			};
		O.ProgramLibrary.Programs[0].KWidth = 6;
		O.ProgramLibrary.Programs[0].KHeight = 6;
		O.ProgramLibrary.Programs[0].FilterEqImage[0] = 0;
		O.ProgramLibrary.Programs[0].FlatFieldImage[0] = 0;
		O.ProgramLibrary.Programs[0].OffX = 8;
		O.ProgramLibrary.Programs[0].OffY = 8;
		O.ProgramLibrary.Programs[0].WinWidth = 1008;
		O.ProgramLibrary.Programs[0].WinHeight = 1008;
		O.ProgramLibrary.Programs[0].Threshold = 300;
		O.ProgramLibrary.Programs[0].KernelDesc[0] = 1;
		O.ProgramLibrary.Programs[0].KernelDesc[1] = 1;
		O.ProgramLibrary.Programs[0].KernelDesc[2] = 1;
		O.ProgramLibrary.Programs[0].KernelDesc[3] = 0;
		O.ProgramLibrary.Programs[0].KernelDesc[4] = 1;
		O.ProgramLibrary.Programs[0].KernelDesc[5] = 2;
		O.ProgramLibrary.Programs[0].KernelDesc[6] = 3;
		O.ProgramLibrary.Programs[0].KernelDesc[7] = 0;
		O.ProgramLibrary.Programs[0].KernelDesc[8] = 1;
		O.ProgramLibrary.Programs[0].KernelDesc[9] = 3;
		O.ProgramLibrary.Programs[0].KernelDesc[10] = -13;
		O.ProgramLibrary.Programs[0].KernelDesc[11] = 0;
		O.ProgramLibrary.Programs[0].KernelDesc[12] = 0;
		O.ProgramLibrary.Programs[0].KernelDesc[13] = 0;
		O.ProgramLibrary.Programs[0].KernelDesc[14] = 0;
		O.ProgramLibrary.Programs[0].KernelDesc[15] = 0;

		O.KernelBuffs[0] = 0;
		}
	/* End kernel initialization */

	/* Display initialization */

	t_DisplayChooser DisplayChooser;
	DisplayChooser.Number = 0;
	DisplayChooser.ChosenNumber = -1;
	DisplayChooser.Width = DisplayChooser.Height = 0;
	DisplayChooser.Left = DisplayChooser.Top = 0;
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&DisplayChooser);

	m_BackgroundBrush = CreateSolidBrush(RGB(64, 128, 224));
	pWndDisplay = new CWndDisplay(&O, DisplayChooser.Width, DisplayChooser.Height, O.ImageWidth, O.ImageHeight, (DWORD)this, COdyssey::FG_Internal_SetLive, COdyssey::FG_Internal_SetStill, COdyssey::FG_Internal_LoadGrabBuffer, COdyssey::FG_Internal_Clear, COdyssey::FG_Internal_DrawCircles);
	pWndDisplay->CreateEx(0, AfxRegisterWndClass(0, ::LoadCursor(AfxGetResourceHandle(), MAKEINTRESOURCE(IDC_ODYSSEY)), m_BackgroundBrush), "Odyssey Display", 
		WS_VISIBLE | WS_POPUP, DisplayChooser.Left, DisplayChooser.Top, DisplayChooser.Width, DisplayChooser.Height, 0, 0, 0);
	pWndDisplay->Init();
	pWndDisplay->ShowWindow(SW_SHOW);

	O.HTerminateRefresh = CreateEvent(NULL, TRUE, FALSE, NULL);
	O.HRefreshStart = CreateEvent(NULL, TRUE, TRUE, NULL);
	O.HRefreshStopped = CreateEvent(NULL, FALSE, FALSE, NULL);
	O.HRefreshThread = (HANDLE)_beginthreadex(NULL, 0, RefreshThreadHook, this, 0, (unsigned *)&d);
	SetThreadPriority(O.HRefreshThread, THREAD_PRIORITY_LOWEST);
	O.GrabMode = VC_GRAB_LIVE;

	/* End display initialization */
}


BOOL CALLBACK COdyssey::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	t_DisplayChooser *pDispC = (t_DisplayChooser *)(void *)dwData;
	if (pDispC->ChosenNumber < 0)
	{
		pDispC->ChosenNumber = pDispC->Number;
		pDispC->Left = lprcMonitor->left;
		pDispC->Top = lprcMonitor->top;
		pDispC->Width = lprcMonitor->right - lprcMonitor->left;
		pDispC->Height = lprcMonitor->bottom - lprcMonitor->top;
	}
	else
	{
		int w = lprcMonitor->right - lprcMonitor->left;
		int h = lprcMonitor->bottom - lprcMonitor->top;
		if (w >= 1024 && h >= 1024)
			if (pDispC->Width < w && pDispC->Height < h)
			{
				pDispC->ChosenNumber = pDispC->Number;
				pDispC->Width = w;
				pDispC->Height = h;
				pDispC->Left = lprcMonitor->left;
				pDispC->Top = lprcMonitor->top;
			}	
	}
	pDispC->Number++;
	return TRUE;
};

COdyssey::~COdyssey()
{
	//if (!O.Initialization) return;

	SetEvent(O.HTerminateRefresh);
	SetEvent(O.HTerminate);
	int i;
	for (i = 1; i < MAX_CLUSTERING_PROCESSORS; i++)
	{
		if (O.ActivationRecords[i].HThread != INVALID_HANDLE_VALUE)
		{
			WaitForSingleObject(O.ActivationRecords[i].HThread, INFINITE);
			CloseHandle(O.ActivationRecords[i].HThread);
			O.ActivationRecords[i].HThread = INVALID_HANDLE_VALUE;
			}
		CloseHandle(O.ActivationRecords[i].HFinished);
		};
	CloseHandle(O.ActivationRecords[0].HFinished);
	CloseHandle(O.HStart);
	CloseHandle(O.HReset);
	CloseHandle(O.HTerminate);

	if (O.Locked) VPUnlock();
	if (O.IsThereCursor) DeleteCursor();

	//SetLiveGrab();
	WaitForSingleObject(O.HRefreshThread, INFINITE);
	//SetNoGrab();

	if (pWndDisplay) delete pWndDisplay;

	CloseHandle(O.HRefreshThread);
	CloseHandle(O.HRefreshStopped);
	CloseHandle(O.HRefreshStart);
	CloseHandle(O.HTerminateRefresh);

	long d;

	imBufFree(O.ProcThread, O.HistoBuff);
	imBufFree(O.ProcThread, O.GraColorBuff);
	imBufFree(O.ProcThread, O.DisplayCtlBuff);
	imBufFree(O.ProcThread, O.OverlayBuff);
	imBufFree(O.ProcThread, O.GraphicsBuff);
	imBufFree(O.ProcThread, O.OverlayLUT);
	imBufFree(O.ProcThread, O.UnderlayBuff);
	imBufFree(O.ProcThread, O.FreezeBuff);
	imBufFree(O.ProcThread, O.DisplayHostBuff);

	for (i = 0; i < MAX_PROGRAMS; i++) 
	{
		if (O.KernelBuffs[i]) imBufFree(O.ProcThread, O.KernelBuffs[i]);
		O.KernelBuffs[i] = 0;
		if (O.FlatFieldBuffs[i]) imBufFree(O.ProcThread, O.FlatFieldBuffs[i]);
		O.FlatFieldBuffs[i] = 0;
		if (O.FilterEqBuffs[i]) imBufFree(O.ProcThread, O.FilterEqBuffs[i]);
		O.FilterEqBuffs[i] = 0;
		}
	for (i = 0; i < MAX_FRAMES_PER_NODE; i++)
		for (d = 0; d < MAX_XOP_BUFFERS; d++)
		{
			if (O.XopSrcBuffs[0][i][d]) imBufFree(O.ProcThread, O.XopSrcBuffs[0][i][d]);
			O.XopSrcBuffs[0][i][d] = 0;
			if (O.XopDestBuffs[0][i][d]) imBufFree(O.ProcThread, O.XopDestBuffs[0][i][d]);
			O.XopDestBuffs[0][i][d] = 0;
			if (O.XopSrcBuffs[1][i][d]) imBufFree(O.ProcThread, O.XopSrcBuffs[1][i][d]);
			O.XopSrcBuffs[1][i][d] = 0;
			if (O.XopDestBuffs[1][i][d]) imBufFree(O.ProcThread, O.XopDestBuffs[1][i][d]);
			O.XopDestBuffs[1][i][d] = 0;
			}

	for (i = 0; i < MAX_FRAMES_PER_NODE; i++)
	{
		imBufFree(O.ProcThread, O.SeqChildBuffs[0][i]);
		imBufFree(O.ProcThread, O.SeqChildHostBinBuffs[0][i]);
		imBufFree(O.ProcThread, O.SeqChildBuffs[1][i]);
		imBufFree(O.ProcThread, O.SeqChildHostBinBuffs[1][i]);
		}
	imBufFree(O.ProcThread, O.SeqMainBuff[0]);
	imBufFree(O.ProcThread, O.SeqMainHostBinBuff[0]);
	imBufFree(O.ProcThread, O.SeqMainBuff[1]);
	imBufFree(O.ProcThread, O.SeqMainHostBinBuff[1]);
	imBufFree(O.ProcThread, O.SeqCtlBuff);
	imBufFree(O.ProcThread, O.SeqStartTimeBuff);
	imBufFree(O.ProcThread, O.SeqEndTimeBuff);
	imBufFree(O.ProcThread, O.LUTBuff);
	imSyncFree(O.ProcThread, O.SeqOSB);
	GlobalFree(O.SegSpace);
	free(O.pLUT);
	
	imSyncFree(O.ProcThread, O.LUTOSB);
	imSyncFree(O.ProcThread, O.ProcOSB);
	imSyncFree(O.GrabThread, O.GrabOSB[0]);
	imSyncFree(O.GrabThread, O.GrabOSB[1]);
	imCamFree(O.ProcThread, O.Cam);
	imThrFree(O.SeqStartThread);
	imThrFree(O.ProcThread);
	imThrFree(O.GrabThread);
	imDevFree(O.Dev);

	DeleteObject(m_BackgroundBrush);

	Initialization = false;
	};


// ISySalObject
STDMETHODIMP COdyssey::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP COdyssey::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP COdyssey::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (O.Locked) return S_FALSE;
	BYTE OldGrabMode = O.GrabMode;
	SetNoGrab();
	
	SetEvent(O.HTerminate);
	int i, d;
	for (i = 1; i < MAX_CLUSTERING_PROCESSORS; i++)
		if (O.ActivationRecords[i].HThread != INVALID_HANDLE_VALUE)
		{
			WaitForSingleObject(O.ActivationRecords[i].HThread, INFINITE);
			CloseHandle(O.ActivationRecords[i].HThread);
			O.ActivationRecords[i].HThread = INVALID_HANDLE_VALUE;
			};
	ResetEvent(O.HTerminate);
	ResetEvent(O.HStart);
	ResetEvent(O.HReset);
	
	for (i = 0; i < MAX_PROGRAMS; i++) 
	{
		if (O.KernelBuffs[i]) imBufFree(O.ProcThread, O.KernelBuffs[i]);
		O.KernelBuffs[i] = 0;
		if (O.FlatFieldBuffs[i]) imBufFree(O.ProcThread, O.FlatFieldBuffs[i]);
		O.FlatFieldBuffs[i] = 0;
		if (O.FilterEqBuffs[i]) imBufFree(O.ProcThread, O.FilterEqBuffs[i]);
		O.FilterEqBuffs[i] = 0;
		}
	for (i = 0; i < MAX_FRAMES_PER_NODE; i++)
		for (d = 0; d < MAX_XOP_BUFFERS; d++)
		{
			if (O.XopSrcBuffs[0][i][d]) imBufFree(O.ProcThread, O.XopSrcBuffs[0][i][d]);
			O.XopSrcBuffs[0][i][d] = 0;
			if (O.XopDestBuffs[i][d]) imBufFree(O.ProcThread, O.XopDestBuffs[0][i][d]);
			O.XopDestBuffs[0][i][d] = 0;
			if (O.XopSrcBuffs[1][i][d]) imBufFree(O.ProcThread, O.XopSrcBuffs[1][i][d]);
			O.XopSrcBuffs[1][i][d] = 0;
			if (O.XopDestBuffs[i][d]) imBufFree(O.ProcThread, O.XopDestBuffs[1][i][d]);
			O.XopDestBuffs[1][i][d] = 0;
			}

	O.ExtendedOperation << *pConfig;
	O.ProgramLibrary << *pConfig;
	O.LightControlSettings << *pConfig;
	O.GeneralSettings << *pConfig;

	for (i = 1; i < O.GeneralSettings.ClusteringProcessors; i++)
		O.ActivationRecords[i].HThread = (HANDLE)_beginthreadex(NULL, 0, ClusterThreadHook, O.ActivationRecords + i, 0, (unsigned *)&d);

	for (i = 0; i < O.ProgramLibrary.Count; i++) 
	{
		int ix, iy;
		static short Kernel[MAX_KERNEL_SIZE * MAX_KERNEL_SIZE];

		imBufAlloc2d(O.ProcThread, O.ProgramLibrary.Programs[i].KWidth, O.ProgramLibrary.Programs[i].KHeight, IM_SHORT, IM_PROC, &O.KernelBuffs[i]);
		for (iy = 0; iy < (O.ProgramLibrary.Programs[i].KHeight + 1) / 2; iy++)
			for (ix = 0; ix < (O.ProgramLibrary.Programs[i].KWidth + 1) / 2; ix++)
			{
				Kernel[iy * O.ProgramLibrary.Programs[i].KWidth + ix] = 
					Kernel[iy * O.ProgramLibrary.Programs[i].KWidth + O.ProgramLibrary.Programs[i].KWidth - 1 - ix] = 
					Kernel[(O.ProgramLibrary.Programs[i].KHeight - 1 - iy) * O.ProgramLibrary.Programs[i].KWidth + ix] = 
					Kernel[(O.ProgramLibrary.Programs[i].KHeight - 1 - iy) * O.ProgramLibrary.Programs[i].KWidth + O.ProgramLibrary.Programs[i].KWidth - 1 - ix] = 
					O.ProgramLibrary.Programs[i].KernelDesc[iy * MAX_KERNEL_SIZE / 2 + ix];
				};
		imBufPut(O.ProcThread, O.KernelBuffs[i], Kernel);

		if (O.ProgramLibrary.Programs[i].FlatFieldImage[0]) 
		{
			imBufAlloc2d(O.ProcThread, O.ImageWidth, O.ImageHeight, IM_BYTE, IM_PROC, &O.FlatFieldBuffs[i]);
			BYTE *pTempBuff = (BYTE *)malloc(O.ImageWidth * O.ImageHeight);
			if (!pTempBuff && O.ImageHeight && O.ImageWidth) return S_FALSE;
			FILE *f = fopen(O.ProgramLibrary.Programs[i].FlatFieldImage, "rb");
			if (!f)
			{
				if (pTempBuff) free(pTempBuff);
				return S_FALSE;
				}
			if (fread(pTempBuff, O.ImageWidth * O.ImageHeight, 1, f) < 1)
			{
				fclose(f);
				if (pTempBuff) free(pTempBuff);
				return S_FALSE;
				}
			fclose(f);
			imBufPut(O.ProcThread, O.FlatFieldBuffs[i], pTempBuff);
			if (pTempBuff) free(pTempBuff);
			}
		else O.FlatFieldBuffs[i] = 0;
		if (O.ProgramLibrary.Programs[i].FilterEqImage[0]) 
		{
			imBufAlloc2d(O.ProcThread, O.ImageWidth, O.ImageHeight, IM_SHORT, IM_PROC, &O.FilterEqBuffs[i]);
			WORD *pTempBuff = (WORD *)malloc(O.ImageWidth * O.ImageHeight * 2);
			if (!pTempBuff && O.ImageHeight && O.ImageWidth) return S_FALSE;
			FILE *f = fopen(O.ProgramLibrary.Programs[i].FilterEqImage, "rb");
			if (!f)
			{
				if (pTempBuff) free(pTempBuff);
				return S_FALSE;
				}
			if (fread(pTempBuff, O.ImageWidth * O.ImageHeight * 2, 1, f) < 1)
			{
				fclose(f);
				if (pTempBuff) free(pTempBuff);
				return S_FALSE;
				}
			fclose(f);
			imBufPut(O.ProcThread, O.FilterEqBuffs[i], pTempBuff);
			if (pTempBuff) free(pTempBuff);
			}
		else O.FilterEqBuffs[i] = 0;

		}
	for (i = 0; i < MAX_FRAMES_PER_NODE; i++)
		for (d = 0; d < O.ExtendedOperation.OpDescriptions.Count; d++)
		{
			imBufChild(O.ProcThread, O.SeqMainBuff[0], O.ExtendedOperation.OpDescriptions.Desc[d].Src.left, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Src.top + i * O.ImageHeight, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Src.right - O.ExtendedOperation.OpDescriptions.Desc[d].Src.left, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Src.bottom - O.ExtendedOperation.OpDescriptions.Desc[d].Src.top, 
				&O.XopSrcBuffs[0][i][d]);
			imBufChild(O.ProcThread, O.SeqMainBuff[1], O.ExtendedOperation.OpDescriptions.Desc[d].Src.left, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Src.top + i * O.ImageHeight, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Src.right - O.ExtendedOperation.OpDescriptions.Desc[d].Src.left, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Src.bottom - O.ExtendedOperation.OpDescriptions.Desc[d].Src.top, 
				&O.XopSrcBuffs[1][i][d]);
			imBufChild(O.ProcThread, O.SeqMainBuff[0], O.ExtendedOperation.OpDescriptions.Desc[d].Dest.left, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Dest.top + i * O.ImageHeight, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Dest.right - O.ExtendedOperation.OpDescriptions.Desc[d].Dest.left, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Dest.bottom - O.ExtendedOperation.OpDescriptions.Desc[d].Dest.top, 
				&O.XopDestBuffs[0][i][d]);
			imBufChild(O.ProcThread, O.SeqMainBuff[1], O.ExtendedOperation.OpDescriptions.Desc[d].Dest.left, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Dest.top + i * O.ImageHeight, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Dest.right - O.ExtendedOperation.OpDescriptions.Desc[d].Dest.left, 
				O.ExtendedOperation.OpDescriptions.Desc[d].Dest.bottom - O.ExtendedOperation.OpDescriptions.Desc[d].Dest.top, 
				&O.XopDestBuffs[1][i][d]);
			}

	switch (OldGrabMode)
	{
		case VC_GRAB_LIVE:			SetLiveGrab(); break;
		case VC_GRAB_SINGLE_FRAME:	SetSingleFrameGrab(); break;
		};

	return S_OK;
}

STDMETHODIMP COdyssey::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	if (pConfig->pItems)
	{
		CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		};
	pConfig->CountOfItems = 0;
	O.LightControlSettings >> *pConfig;
	O.ExtendedOperation >> *pConfig;
	O.ProgramLibrary >> *pConfig;
	O.GeneralSettings >> *pConfig;
	return S_OK;
}

STDMETHODIMP COdyssey::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	// TODO: Add your implementation code here

	HRESULT HRes;
	CWnd MyWnd;
	MyWnd.Attach((HWND)hWnd);
	{
		CEditConfig MyDlg(*this, &MyWnd);
		MyDlg.m_XOP << *pConfig;
		MyDlg.m_ProgLib << *pConfig;
		MyDlg.m_LC << *pConfig;
		MyDlg.m_GS << *pConfig;
		if (MyDlg.DoModal() == IDOK) 
		{
			if (pConfig->pItems)
			{
				CoTaskMemFree(pConfig->pItems);
				pConfig->pItems = 0;
				};
			pConfig->CountOfItems = 0;
			MyDlg.m_LC >> *pConfig;
			MyDlg.m_XOP >> *pConfig;
			MyDlg.m_ProgLib >> *pConfig;
			MyDlg.m_GS >> *pConfig;

			HRes = S_OK;
			}
		else HRes = S_FALSE;
		};
	MyWnd.Detach();
	return HRes;
}

STDMETHODIMP COdyssey::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP COdyssey::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP COdyssey::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP COdyssey::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
}

STDMETHODIMP COdyssey::GetIcon(int n, HSySalHICON *pHICON)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	HANDLE HTemp = 0;
	switch (n)
	{
		case 0:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON32), IMAGE_ICON, 32, 32, LR_SHARED);
					break;

		case 1:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON64), IMAGE_ICON, 64, 64, LR_SHARED);
					break;

		default:	return E_INVALIDARG;
		};
	*pHICON = (HSySalHICON)HTemp;
	return S_OK;	
}

STDMETHODIMP COdyssey::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Matrox Odyssey Vision Processor", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP COdyssey::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP COdyssey::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP COdyssey::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP COdyssey::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP COdyssey::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP COdyssey::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP COdyssey::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP COdyssey::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here
	try
	{
		if (Slots[0].pUnknown)
		{
			IStage *iSt;
			if (Slots[0].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) == S_OK) iSt->Release();
			else throw 0;
			};
		}
	catch (int x)
	{
		*pWrongConn = x;
		*pRetCode = SYSAL_READYSTATUS_UNSUPPORTED_INTERFACE;
		return S_OK;
		};

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

//IFrameGrabber
STDMETHODIMP COdyssey::VideoInfo(VIDEOINFOSTRUCT *VIS)
{  
	VIS->Width = O.ImageWidth;
	VIS->Height = O.ImageHeight;
	VIS->PageSize = O.ImageWidth * O.ImageHeight;
	VIS->ColorsNumber = 256;
	VIS->DefaultColorsNumber = 16;
	VIS->WhereDefault = 0x00;
	VIS->ReservedColor = ODYSSEY_TRANSPARENT;
	VIS->DataSize = 1;
	VIS->Planes = 1;
	return S_OK;
	};

STDMETHODIMP COdyssey::GrabInfo(GRABBERINFOSTRUCT *GIS)
{  
	GIS->Width = O.ImageWidth;
	GIS->Height = O.ImageHeight;
	GIS->ColorsNumber = 256;
	GIS->DataSize = 1;
	GIS->Planes = 1;
	GIS->Synchronization = VC_GRAB_ASYNC;
	GIS->LiveMode = VC_GRAB_LIVE_YES;
	GIS->PagesNumber = ODYSSEY_GRAB_PAGE_NUM;
	GIS->PageSize = O.ImageWidth * O.ImageHeight;
	return S_OK;
	};

STDMETHODIMP COdyssey::GetPalette(PALETTESTRUCT *PS)
{  
	PS->ColorsNumber = 256;
	PS->ColorSize = 3;
	PS->IsByPlane = 0;
	memcpy(PS->PaletteData, O.OvrColors, 3 * 256);
	return S_OK;
	};

STDMETHODIMP COdyssey::SetPalette(PALETTESTRUCT *PS)
{	
	if ((PS->ColorsNumber > 256) || (PS->ColorSize != 3) || (PS->IsByPlane != 0)) return E_INVALIDARG;
	memcpy(O.OvrColors, PS->PaletteData, 3 * 256);
	imBufPut1d(O.ProcThread, O.OverlayLUT, 0, 256, O.OvrColors);
	imBufPutField(O.ProcThread, O.DisplayCtlBuff, IM_DISP_LUT_BUF, O.OverlayLUT);
	imDispControl(O.ProcThread, O.Display, O.DisplayCtlBuff, IM_NOW);
	return S_OK;
	};

STDMETHODIMP COdyssey::SetDefaultPalette()
{  
	int i,j;
	for (i = 0; i < 240; i++)
		for (j = 0; j < 3; j++)
			O.OvrColors[(16 + i) * 3 + j] = 0;
	for (i = 0; i < 16; i++)
		for (j = 0; j < 3; j++)
			O.OvrColors[i * 3 + j] = OvrColorsTable[i][j];
	imBufPut1d(O.ProcThread, O.OverlayLUT, 0, 256, O.OvrColors);
	imBufPutField(O.ProcThread, O.DisplayCtlBuff, IM_DISP_LUT_BUF, O.OverlayLUT);
	imDispControl(O.ProcThread, O.Display, O.DisplayCtlBuff, IM_NOW);
	return S_OK;
	};

STDMETHODIMP COdyssey::GetColorCode(int Color, int *pCode)
{
	if (Color == VC_TRANSPARENT) *pCode = ODYSSEY_TRANSPARENT;
	else if ((Color < VC_BLACK) || (Color > VC_WHITE)) 
	{
		*pCode = VC_NO_COLORCODE;
		return S_FALSE;
		}
	else *pCode = Color + ODYSSEY_BLACK;
	return S_OK;
	};

STDMETHODIMP COdyssey::Dot(unsigned int X, unsigned int Y, DWORD C)
{
	InvalidateCursorArea(X, Y, X, Y);
	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_COLOR, C);
	imGraLine(O.ProcThread, O.GraColorBuff, O.GraphicsBuff, X, Y, X, Y);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::Fill(unsigned int X, unsigned int Y, DWORD C)
{  
	InvalidateCursorArea(0, 0, O.ImageWidth, O.ImageHeight);
	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_COLOR, C);
	imGraFill(O.ProcThread, O.GraColorBuff, O.GraphicsBuff, X, Y);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::Arc(unsigned int XC, unsigned int YC, unsigned int XR,
	unsigned int YR, double SA, double EA, DWORD C)
{  
	InvalidateCursorArea(XC - XR, YC - YR, XC + XR, YC + YR);
	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_COLOR, C);
	imGraArc(O.ProcThread, O.GraColorBuff, O.GraphicsBuff, XC, YC, XR, YR, SA, EA);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::ArcFill(unsigned int XC, unsigned int YC, unsigned int XR,
	unsigned int YR, double SA, double EA, DWORD C)
{  
	InvalidateCursorArea(XC - XR, YC - YR, XC + XR, YC + YR);
	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_COLOR, C);
	imGraArcFill(O.ProcThread, O.GraColorBuff, O.GraphicsBuff, XC, YC, XR, YR, SA, EA);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::Rect(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_COLOR, C);
	imGraRect(O.ProcThread, O.GraColorBuff, O.GraphicsBuff, XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::RectFill(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_COLOR, C);
	imGraRectFill(O.ProcThread, O.GraColorBuff, O.GraphicsBuff, XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::Line(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_COLOR, C);
	imGraLine(O.ProcThread, O.GraColorBuff, O.GraphicsBuff, XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::Text(unsigned int XS, unsigned int YS, BYTE *S, DWORD C)
{  
	InvalidateCursorArea(0, 0, O.ImageWidth, O.ImageHeight);
	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_COLOR, C);
	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_BACK_MODE, IM_TRANSPARENT);
	imGraText(O.ProcThread, O.GraColorBuff, O.GraphicsBuff, XS, YS, (char *)S);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::TextFont(unsigned int F)
{  
	switch (F)
	{	
		case 0:	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_FONT, IM_FONT_LARGE); break;
		case 1:	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_FONT, IM_FONT_MEDIUM); break;
		case 2:	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_FONT, IM_FONT_SMALL); break;
		default: imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_FONT, IM_FONT_DEFAULT); break;
		};
	return S_OK;
	};

STDMETHODIMP COdyssey::TextScale(double XS, double YS)
{  
	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_FONT_SCALE_X, (int)XS);
	imBufPutField(O.ProcThread, O.GraColorBuff, IM_GRA_FONT_SCALE_Y, (int)YS);
	return S_OK;
	};

STDMETHODIMP COdyssey::Clear(unsigned int C)
{  
	InvalidateCursorArea(0, 0, O.ImageWidth, O.ImageHeight);
	imBufClear(O.ProcThread, O.GraphicsBuff, C, 0);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::SetZoom(int ZX, int ZY)
{	
	return E_NOTIMPL;
};

STDMETHODIMP COdyssey::SetOffset(int X, int Y)
{  
	return E_NOTIMPL;
	};

STDMETHODIMP COdyssey::LoadCursor(BYTE *CursorFile)
{  
	if (O.IsThereCursor) DeleteCursor();
	FILE *InFile = fopen((char *)CursorFile, "rb");
	if (!InFile) return E_INVALIDARG;
	char HeaderString[ODYSSEY_CURSOR_HEADER_STRING_LENGTH];
	fread(HeaderString, ODYSSEY_CURSOR_HEADER_STRING_LENGTH, 1, InFile);
	if (strncmp(HeaderString, CursorHeaderString, ODYSSEY_CURSOR_HEADER_STRING_LENGTH))
	{	
		fclose(InFile);
		return S_FALSE;
		}
	fread(&(O.CursorWidth), sizeof(int), 1, InFile);
	fread(&(O.CursorHeight), sizeof(int), 1, InFile);
	fread(&O.CursorAlignX, sizeof(int), 1, InFile);
	fread(&O.CursorAlignY, sizeof(int), 1, InFile);
	imBufAlloc2d(O.ProcThread, O.CursorWidth, O.CursorHeight, IM_UBYTE, IM_PROC, &O.CursorBuff);	
	imBufAlloc2d(O.ProcThread, O.CursorWidth, O.CursorHeight, IM_UBYTE, IM_PROC, &O.CursorSaveArea);	
	char *TempSpace = (char *)malloc(O.CursorWidth * O.CursorHeight);
	fread(TempSpace, O.CursorWidth * O.CursorHeight, 1, InFile);
	fclose(InFile);
	imBufPut2d(O.ProcThread, O.CursorBuff, 0, 0, O.CursorWidth, O.CursorHeight, TempSpace);
	free(TempSpace);
	O.IsThereCursor = true;
	O.CursorVisible = false;
	return S_OK;
	};

STDMETHODIMP COdyssey::DeleteCursor()
{  
	if (O.IsThereCursor)
	{	
		HideCursor();
		imBufFree(O.ProcThread, O.CursorBuff);
		imBufFree(O.ProcThread, O.CursorSaveArea);
		O.IsThereCursor = O.CursorVisible = false;
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP COdyssey::HideCursor()
{  
	if (O.IsThereCursor && O.CursorVisible)
	{	
		long TempBuff;
		imBufChild(O.ProcThread, O.GraphicsBuff, O.CursorX - O.CursorAlignX, O.CursorY - O.CursorAlignY, O.CursorWidth, O.CursorHeight, &TempBuff);
		imBufCopy(O.ProcThread, O.CursorSaveArea, TempBuff, 0, 0);
		imBufFree(O.ProcThread, TempBuff);
		O.CursorVisible = false;
		O.IsCursorAreaValid = false;
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP COdyssey::ShowCursor()
{  
	if (O.IsThereCursor && !O.CursorVisible)
	{	
		long TempBuff;
		imBufChild(O.ProcThread, O.GraphicsBuff, O.CursorX - O.CursorAlignX, O.CursorY - O.CursorAlignY, O.CursorWidth, O.CursorHeight, &TempBuff);
		imBufCopy(O.ProcThread, TempBuff, O.CursorSaveArea, 0, 0);
		imIntClip(O.ProcThread, TempBuff, TempBuff, IM_GREATER, O.CursorBuff, 0, ODYSSEY_LTMAGENTA, 0, IM_THRESH_PIXEL | IM_PASS_PIXEL, 0);
		imBufFree(O.ProcThread, TempBuff);
		O.CursorVisible = true;
		O.IsCursorAreaValid = true;
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP COdyssey::SetCursorPos(int X, int Y)
{	
	if (O.IsThereCursor && (X != O.CursorX) || (Y != O.CursorY))
	{  
		HideCursor();
		O.CursorX = X;
		O.CursorY = Y;
		ShowCursor();
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP COdyssey::GetCursorPos(int *X, int *Y)
{	
	*X = O.CursorX;
	*Y = O.CursorY;
	return S_OK;
	};

STDMETHODIMP COdyssey::SetNoGrab()
{  
	if (O.GrabMode == VC_GRAB_LIVE) 
	{
		SetThreadPriority(O.HRefreshThread, THREAD_PRIORITY_NORMAL);
		ResetEvent(O.HRefreshStart);
		WaitForSingleObject(O.HRefreshStopped, INFINITE);
		}
	O.GrabMode = VC_NO_GRAB;
	return S_OK;
	};

STDMETHODIMP COdyssey::SetLiveGrab()
{  
	if (O.GrabMode == VC_GRAB_LIVE) return S_OK;
	SetEvent(O.HRefreshStart);
	SetThreadPriority(O.HRefreshThread, THREAD_PRIORITY_LOWEST);
	O.GrabMode = VC_GRAB_LIVE;
	return S_OK;
	};

STDMETHODIMP COdyssey::ShowLive()
{  
	if (O.GrabMode != VC_GRAB_LIVE) return S_FALSE;
	return S_OK;
	};

STDMETHODIMP COdyssey::ShowFrozen()
{  
	return S_FALSE;
	};

STDMETHODIMP COdyssey::FreezeFrame(BYTE **ppImage)
{  
	if (O.GrabMode != VC_GRAB_LIVE)
	{	
   		*ppImage = 0;
		return S_FALSE;
		};

	ResetEvent(O.HRefreshStart);
	WaitForSingleObject(O.HRefreshStopped, INFINITE);
	imBufCopy(O.GrabThread, O.GrabBuff, O.FreezeBuff, 0, 0);
	*ppImage = O.pFreezeBuff;
	SetEvent(O.HRefreshStart);
	return S_OK;
	};

STDMETHODIMP COdyssey::ClearFrozen()
{  
	if (O.GrabMode != VC_GRAB_LIVE) return S_FALSE;
	imBufClear(O.GrabThread, O.FreezeBuff, 0, 0);
	return S_OK;
	};

STDMETHODIMP COdyssey::SetSingleFrameGrab()
{  
	if (O.GrabMode == VC_GRAB_LIVE) 
	{
		ResetEvent(O.HRefreshStart);
		WaitForSingleObject(O.HRefreshStopped, INFINITE);
		}
	O.GrabMode = VC_GRAB_SINGLE_FRAME;
	//imDigGrab(O.GrabThread, 0, O.Cam, O.FreezeBuff, 1, 0, 0);
	return S_OK;
	};

STDMETHODIMP COdyssey::HoldFrame(BYTE **ppImage)
{  
   
	if (O.GrabMode != VC_GRAB_SINGLE_FRAME)
	{	
		*ppImage = 0;
		return S_OK;
		};
	imDigGrab(O.GrabThread, 0, O.Cam, O.FreezeBuff, 1, 0, 0);
	if (ppImage) *ppImage = O.pFreezeBuff;
	return S_OK;
	};

STDMETHODIMP COdyssey::ShowHeldFrame()
{  
	if (O.GrabMode != VC_GRAB_SINGLE_FRAME) return S_FALSE;
	imBufCopy(O.GrabThread, O.FreezeBuff, O.UnderlayBuff, 0, 0);
	return S_OK;
	};

STDMETHODIMP COdyssey::ReleaseFrame()
{  
	if (O.GrabMode != VC_GRAB_SINGLE_FRAME) return S_FALSE;
	return S_OK;
	};

STDMETHODIMP COdyssey::GetCurrentFrameGrabDelay(UINT *pDelay)
{  
	switch (O.GrabMode)
	{
		case VC_NO_GRAB:	
							*pDelay = 0;
							break;

		case VC_GRAB_SINGLE_FRAME:

							*pDelay = 1;
							break;

		case VC_GRAB_LIVE:

							*pDelay = 0;
							break;

		default:			*pDelay = -1;
							return S_FALSE;
	   };
   return S_OK;
};

STDMETHODIMP COdyssey::FlushGrabBackBuffers()
{  
   switch (O.GrabMode)
   {
		case VC_NO_GRAB:	
							return S_FALSE;
							break;

		case VC_GRAB_SINGLE_FRAME:
							return S_OK;
							break;

		case VC_GRAB_LIVE:
							return S_OK;
							break;
	   };
   return S_FALSE;

};

STDMETHODIMP COdyssey::IsGrabCycleLockable(boolean *pAnswer)
{  
	*pAnswer = false; 
	return S_OK;
	};

STDMETHODIMP COdyssey::IsGrabCycleLocked(boolean *pAnswer)
{  
	*pAnswer = false;
	return S_OK;
	};

STDMETHODIMP COdyssey::LoadStockCursor(int StockCursorId)
{  
	const OdysseyStockCursor *pCursor;
	switch (StockCursorId)
	{
		case VC_STOCKCURSORS_CROSS:		pCursor = &Cross;
										break;

		case VC_STOCKCURSORS_AREA5:		pCursor = &Area5;
										break;

		case VC_STOCKCURSORS_AREA9:		pCursor = &Area9;
										break;

		case VC_STOCKCURSORS_AREA16:	pCursor = &Area16;
										break;

		case VC_STOCKCURSORS_AREA25:	pCursor = &Area25;
										break;

	   default:							return E_INVALIDARG;
	   };

	O.CursorWidth = pCursor->Width;
	O.CursorHeight = pCursor->Height;
	O.CursorAlignX = pCursor->AlignX;
	O.CursorAlignY = pCursor->AlignY;

	imBufAlloc2d(O.ProcThread, O.CursorWidth, O.CursorHeight, IM_UBYTE, IM_PROC, &O.CursorBuff);	
	imBufAlloc2d(O.ProcThread, O.CursorWidth, O.CursorHeight, IM_UBYTE, IM_PROC, &O.CursorSaveArea);	
	imBufPut2d(O.ProcThread, O.CursorBuff, 0, 0, O.CursorWidth, O.CursorHeight, (void *)(pCursor->Shape));
	O.IsThereCursor = true;
	O.CursorVisible = false;
	return S_OK;
	};

// Internal functions

void COdyssey::InvalidateCursorArea(int XL, int YT, int XR, int YB)
{  
	if (O.IsThereCursor && O.CursorVisible)
	{	
		int CXL = O.CursorX - O.CursorAlignX;
		int CXR = CXL + O.CursorWidth;
		int CYT = O.CursorY - O.CursorAlignY;
		int CYB = CYT + O.CursorHeight;

		O.IsCursorAreaValid = !(((XL <= CXL) && (XR >= CXR) && (YT <= CYT) && (YB >= CYB)) ||
			((CXL <= XL) && (CXR >= XR) && (CYT <= YT) && (CYB >= YB)));
		if (!O.IsCursorAreaValid) HideCursor();
		O.CursorVisible = true;
		};
	};

void COdyssey::UpdateCursorArea()
{	
	if (O.IsThereCursor && O.CursorVisible && (!O.IsCursorAreaValid))
	{	
		O.CursorVisible = 0;
		ShowCursor();
		O.IsCursorAreaValid = true;
		};
	};



STDMETHODIMP COdyssey::VPLock(UINT Threshold, UINT Width, UINT Height, UINT OffX, UINT OffY, UINT WinWidth, UINT WinHeight, DWORD PresetFrames, DWORD pfnFrameStartCallBack, DWORD Context)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (O.Locked) return S_FALSE;
	if (O.ProgramLibrary.Count < 1) return S_FALSE;

	SetNoGrab();
	pWndDisplay->SetLocked();

	O.pFrameStartCallBack = (void (*)(DWORD))pfnFrameStartCallBack;
	O.Context = Context;

	O.CutOff = Threshold;
	O.OffX = OffX;
	O.OffY = OffY;
	O.WinHeight = WinHeight;
	O.WinWidth = WinWidth;
	O.ActiveProgram = 0;
	O.FrameCount = 0;
	O.CycleParity = 0;
	O.SequencePrograms[0].Status = O.SequencePrograms[1].Status = O.SequencePrograms[2].Status = VP_PROGRAM_NULL;
	O.SequencePrograms[0].ActiveProgram = O.SequencePrograms[1].ActiveProgram = O.SequencePrograms[1].ActiveProgram = 0;
	O.SequencePrograms[0].AIS.ImageCount = O.SequencePrograms[1].AIS.ImageCount = O.SequencePrograms[1].AIS.ImageCount = 0;
	O.SequencePrograms[0].AIS.pImages = O.SequencePrograms[1].AIS.pImages = O.SequencePrograms[1].AIS.pImages = 0;
		
	O.Locked = true;

	return S_OK;
}

STDMETHODIMP COdyssey::VPUnlock()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!O.Locked) return S_FALSE;
	O.Locked = false;
	SetLiveGrab();
	return S_OK;
}

STDMETHODIMP COdyssey::VPStart()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!O.Locked) return S_FALSE;

	O.FrameCount = 0;
	O.CycleParity = 0;
		
	imDigGrab(O.GrabThread, 0, O.Cam, O.SrcGrabBuffs[0], 1, 0, O.GrabOSB[0]);
	imSyncHost(O.GrabThread, O.GrabOSB[0], IM_STARTED);

	return S_OK;
}

STDMETHODIMP COdyssey::VPIterate(Cluster *pSpace, UINT *pMaxClusters)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!O.Locked) return S_FALSE;

	HRESULT HRes;
	O.FrameCount++;
	int h, ho, hs, hso;
	int j;
	O.CycleParity = h = O.FrameCount % 2;
	hs = O.FrameCount % 3;
	ho = (O.FrameCount + 3 - 1) % 2;
	hso = (O.FrameCount + 3 - 1) % 3;

	imDigGrab(O.GrabThread, 0, O.Cam, O.SrcGrabBuffs[hs], 1, 0, O.GrabOSB[h]);
	imSyncHost(O.GrabThread, O.GrabOSB[ho], IM_COMPLETED);
	if (O.FlatFieldBuffs[O.ActiveProgram]) imIntDyadic(O.ProcThread, O.SrcGrabBuffs[hso], O.FlatFieldBuffs[O.ActiveProgram], O.SrcGrabBuffs[hso], IM_SUB, 0);
	for (j = 0; j < O.ExtendedOperation.OpDescriptions.Count; j++)
		switch (O.ExtendedOperation.OpDescriptions.Desc[j].Type)
		{
			case XOP_TYPE_COPY:		imBufCopy(O.ProcThread, O.XopSrcBuffs[0][hso][j], O.XopDestBuffs[0][hso][j], 0, 0); break;
			case XOP_TYPE_HFLIP:	imIntFlip(O.ProcThread, O.XopSrcBuffs[0][hso][j], O.XopDestBuffs[0][hso][j], IM_FLIP_H, IM_DEFAULT, 0); break;
			case XOP_TYPE_VFLIP:	imIntFlip(O.ProcThread, O.XopSrcBuffs[0][hso][j], O.XopDestBuffs[0][hso][j], IM_FLIP_V, IM_DEFAULT, 0); break;
			case XOP_ROTATE_90:		imIntFlip(O.ProcThread, O.XopSrcBuffs[0][hso][j], O.XopDestBuffs[0][hso][j], IM_ROTATE_90, IM_DEFAULT, 0); break;
			case XOP_ROTATE_180:	imIntFlip(O.ProcThread, O.XopSrcBuffs[0][hso][j], O.XopDestBuffs[0][hso][j], IM_ROTATE_180, IM_DEFAULT, 0); break;
			case XOP_ROTATE_270:	imIntFlip(O.ProcThread, O.XopSrcBuffs[0][hso][j], O.XopDestBuffs[0][hso][j], IM_ROTATE_270, IM_DEFAULT, 0); break;
			}
	// copy to display...
	imIntConvolve(O.ProcThread, O.SrcGrabBuffs[hso], O.ConvBuff, O.KernelBuffs[O.ActiveProgram], 0, 0);
	if (O.FilterEqBuffs[O.ActiveProgram]) imIntDyadic(O.ProcThread, O.ConvBuff, O.FilterEqBuffs[O.ActiveProgram], O.ConvBuff, IM_SUB, 0);
	imBinConvert(O.ProcThread, O.ConvBuff, O.BinBuff, IM_LESS, O.CutOff, 0, 0);
	imBufCopy(O.ProcThread, O.BinBuff, O.HostBinBuffs[ho], 0, O.ProcOSB);
	if (O.pFrameStartCallBack) O.pFrameStartCallBack(O.Context);

	if (O.FrameCount >= 2)
	{
		HRes = GetClusters(O.pHostBinBuffs[h], PrecompData, pSpace, (int *)pMaxClusters, O.ImageWidth, O.ImageHeight, O.OffX, O.OffY, O.WinWidth, O.WinHeight, O.SegSpace, O.SegSpace + O.ImageWidth);
		}
	else
	{
		HRes = S_OK;
		*pMaxClusters = 0;
		};
	return HRes;
}

STDMETHODIMP COdyssey::VPFlush(Cluster *pSpace, UINT *pMaxClusters)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!O.Locked) return S_FALSE;

	O.FrameCount++;
	int h;
	O.CycleParity = h = O.FrameCount % 2;

	imSyncHost(O.ProcThread, O.ProcOSB, IM_COMPLETED);
	return GetClusters(O.pHostBinBuffs[h], PrecompData, pSpace, (int *)pMaxClusters, O.ImageWidth, O.ImageHeight, O.OffX, O.OffY, O.WinWidth, O.WinHeight, O.SegSpace, O.SegSpace + O.ImageWidth);
}

STDMETHODIMP COdyssey::VPGetFrameDelay(UINT *pDelay)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!O.Locked) return S_FALSE;
	*pDelay = 1;
	return S_OK;
}

STDMETHODIMP COdyssey::VPGetProgramCount(UINT *pCount)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pCount = O.ProgramLibrary.Count;
	return S_OK;		
}

STDMETHODIMP COdyssey::VPGetProgram(UINT *pProgram)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pProgram = O.ActiveProgram;
	return S_OK;
}

STDMETHODIMP COdyssey::VPSetProgram(UINT Program)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Program > O.ProgramLibrary.Count) return E_INVALIDARG;
	O.ActiveProgram = Program;
	O.CutOff = O.ProgramLibrary.Programs[Program].Threshold;
	O.OffX = O.ProgramLibrary.Programs[Program].OffX;
	O.OffY = O.ProgramLibrary.Programs[Program].OffY;
	O.WinHeight = O.ProgramLibrary.Programs[Program].WinHeight;
	O.WinWidth = O.ProgramLibrary.Programs[Program].WinWidth;
	return S_OK;	
}

STDMETHODIMP COdyssey::VPLock2(DWORD pfnFrameStartCallBack, DWORD Context)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (O.Locked) return S_FALSE;
	if (O.ProgramLibrary.Count < 1) return S_FALSE;

	SetNoGrab();
	pWndDisplay->SetLocked();

	O.pFrameStartCallBack = (void (*)(DWORD))pfnFrameStartCallBack;
	O.Context = Context;

	VPSetProgram(0);
	O.SequencePrograms[0].Status = O.SequencePrograms[1].Status = O.SequencePrograms[2].Status = VP_PROGRAM_NULL;
	O.SequencePrograms[0].ActiveProgram = O.SequencePrograms[1].ActiveProgram = O.SequencePrograms[1].ActiveProgram = 0;
	O.SequencePrograms[0].AIS.ImageCount = O.SequencePrograms[1].AIS.ImageCount = O.SequencePrograms[1].AIS.ImageCount = 0;
	O.SequencePrograms[0].AIS.pImages = O.SequencePrograms[1].AIS.pImages = O.SequencePrograms[1].AIS.pImages = 0;
		
	O.Locked = true;

	return S_OK;
}

STDMETHODIMP COdyssey::VPGetPrimaryImage(BYTE *pImage)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (O.FrameCount < 2) return S_FALSE;
	int hs;
	hs = (O.FrameCount - 2) % 3;
	imBufGet2d(O.GrabThread, O.SrcGrabBuffs[hs], 0, 0, O.ImageWidth, O.ImageHeight, pImage);
	return S_OK;
}

STDMETHODIMP COdyssey::SetLightLevel()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!Slots[0].pUnknown) return E_ABORT;
	IStage *iSt = 0;
	if (Slots[0].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) != S_OK)
	{
		if (iSt) iSt->Release();
		return E_ABORT;
		};

	BYTE OldGrabMode = O.GrabMode;
	if (OldGrabMode != VC_NO_GRAB) SetNoGrab();

	int lightlev, minlev, maxlev, newlev, time, dlev;
	float graylev, satlev, ftime;
	iSt->GetLight(&lightlev);
	LC_Get_LightInfo(&graylev, &satlev);
	if (graylev <= O.LightControlSettings.TargetGrayLev)
	{
		minlev = lightlev;
		maxlev = O.LightControlSettings.MaxLev;
		}
	else
	{
		minlev = O.LightControlSettings.MinLev;
		maxlev = lightlev;
		}
	while (minlev < maxlev)
	{
		newlev = (maxlev + minlev) / 2;
		if ((dlev = abs(newlev - lightlev)) <= 1) break;
		ftime = log((double)dlev) * O.LightControlSettings.LampTimeConstant;
		time = (ftime > 60000) ? 60000 : ftime;
		iSt->SetLight(lightlev = newlev);
		time += GetTickCount();
		while (GetTickCount() < time)
		{
			imDigGrab(O.GrabThread, 0, O.Cam, O.GrabBuff, 1, 0, O.GrabOSB[0]);	
			// display...
			imSyncHost(O.GrabThread, O.GrabOSB[0], IM_COMPLETED);
			}
		LC_Get_LightInfo(&graylev, &satlev);
		if (graylev <= O.LightControlSettings.TargetGrayLev)
		{
			minlev = lightlev;
			}
		else
		{
			maxlev = lightlev;
			}		
		};

	if (!O.Locked) 
	{
		switch (OldGrabMode)
		{
			case VC_GRAB_LIVE:			SetLiveGrab(); break;
			case VC_GRAB_SINGLE_FRAME:	SetSingleFrameGrab(); break;
			};
		}

	if (iSt) iSt->Release();
	return S_OK;
}

bool COdyssey::VP_Internal_GetProgramArea(unsigned program, unsigned int *pOffX, unsigned int *pOffY, unsigned int *pWinWidth, unsigned int *pWinHeight)
{
	if (program >= O.ProgramLibrary.Count) return false;
	*pOffX = O.ProgramLibrary.Programs[program].OffX;
	*pOffY = O.ProgramLibrary.Programs[program].OffY;
	*pWinWidth = O.ProgramLibrary.Programs[program].WinWidth;
	*pWinHeight = O.ProgramLibrary.Programs[program].WinHeight;
	return true;
}

int COdyssey::VP_Internal_GetCommandQueueLength()
{
	return O.CommandQueueLength;
}

int COdyssey::VP_Internal_GetMaxAsyncFrames()
{
	return MAX_FRAMES_PER_NODE;
}

float COdyssey::VP_Internal_GetFrameRate()
{
	const int TESTINGCYCLES = 100;
	BYTE OldGrabMode = O.GrabMode;
	if (!O.Locked) 
		if (OldGrabMode != VC_NO_GRAB) SetNoGrab();

	imSyncControl(O.GrabThread, O.SeqOSB, IM_OSB_STATE, IM_NON_SIGNALLED);
	imDigGrabSequence(O.GrabThread, 0, O.Cam, O.SeqMainBuff[0], TESTINGCYCLES, O.SeqCtlBuff, O.SeqOSB);
	//imSyncHost(O.GrabThread, O.SeqOSB, IM_COMPLETED);
	int cycles = imSyncGrabSequence(O.GrabThread, O.SeqOSB, TESTINGCYCLES - 1, IM_SEQ_WAIT);

	float res = (float)(TESTINGCYCLES - 1) / (O.pSeqEndTimeBuff[TESTINGCYCLES - 1] - O.pSeqEndTimeBuff[0]);
	if (res < 0)
	{
		int i, j;
		for (i = TESTINGCYCLES - 1; i > 0 && O.pSeqEndTimeBuff[i] - O.pSeqEndTimeBuff[0] < 0; i--);
		float avg = (O.pSeqEndTimeBuff[i] - O.pSeqEndTimeBuff[0]) / i;
		for (j = 1; j < i && (O.pSeqEndTimeBuff[j] - O.pSeqEndTimeBuff[j - 1]) < 1.5f * avg; j++);
		char tempstr[256];
		sprintf(tempstr, "Missed frame at frame %d\r\nLast time delay: %f", j, O.pSeqEndTimeBuff[j] - O.pSeqEndTimeBuff[j - 1]);
		MessageBox(0, tempstr, "Grab error", MB_OK);
		}
	if (!O.Locked) 
	{
		switch (OldGrabMode)
		{
			case VC_GRAB_LIVE:			SetLiveGrab(); break;
			case VC_GRAB_SINGLE_FRAME:	SetSingleFrameGrab(); break;
			};
		}
	return res;
}

STDMETHODIMP COdyssey::VPPrepareAsyncProcessing(UINT Program, AsyncImageSequence ImageSeq)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Program >= O.ProgramLibrary.Count) return E_INVALIDARG;
	if (ImageSeq.ImageCount > MAX_FRAMES_PER_NODE) return E_INVALIDARG;

	int seqindex = (O.SequenceIndex + 1) % 2;
	OdysseyData::t_SequenceProgram &p = O.SequencePrograms[seqindex];
	p.ActiveProgram = Program;

	if (p.Status != VP_PROGRAM_NULL) return S_FALSE;
	imSyncControl(O.GrabThread, O.SeqOSB, IM_OSB_STATE, IM_WAITING);
	p.AIS = ImageSeq;

#if 0
	int i, j;

	p.ActiveProgram = Program;

	double zero;
	zero = imSysClock(O.SeqStartThread, 0);
	O.SeqTimeZero[seqindex] = imSysClock(O.ProcThread, 0) - zero;
	imSyncControl(O.GrabThread, O.SeqOSB, IM_OSB_STATE, IM_WAITING);
/*	imSyncControl(O.GrabThread, O.GrabOSB[0], IM_OSB_STATE, IM_NON_SIGNALLED);
	imSyncThread(O.ProcThread, O.GrabOSB[0], IM_SIGNALLED);
	imSyncThread(O.ProcThread, O.SeqOSB, IM_COMPLETED);
*/	for (i = 0; i < ImageSeq.ImageCount; i++)
	{
		//imSyncGrabSequence(O.ProcThread, O.SeqOSB, i, IM_SEQ_WAIT_THREAD);
/*
		imSyncGrabSequence(O.ProcThread, O.SeqOSB, i, IM_SEQ_WAIT_THREAD);
		for (j = 0; j < O.ExtendedOperation.OpDescriptions.Count; j++)
			switch (O.ExtendedOperation.OpDescriptions.Desc[j].Type)
			{
				case XOP_TYPE_COPY:		imBufCopy(O.ProcThread, O.XopSrcBuffs[seqindex][i][j], O.XopDestBuffs[seqindex][i][j], 0, 0); break;
				case XOP_TYPE_HFLIP:	imIntFlip(O.ProcThread, O.XopSrcBuffs[seqindex][i][j], O.XopDestBuffs[seqindex][i][j], IM_FLIP_H, IM_DEFAULT, 0); break;
				case XOP_TYPE_VFLIP:	imIntFlip(O.ProcThread, O.XopSrcBuffs[seqindex][i][j], O.XopDestBuffs[seqindex][i][j], IM_FLIP_V, IM_DEFAULT, 0); break;
				case XOP_ROTATE_90:		imIntFlip(O.ProcThread, O.XopSrcBuffs[seqindex][i][j], O.XopDestBuffs[seqindex][i][j], IM_ROTATE_90, IM_DEFAULT, 0); break;
				case XOP_ROTATE_180:	imIntFlip(O.ProcThread, O.XopSrcBuffs[seqindex][i][j], O.XopDestBuffs[seqindex][i][j], IM_ROTATE_180, IM_DEFAULT, 0); break;
				case XOP_ROTATE_270:	imIntFlip(O.ProcThread, O.XopSrcBuffs[seqindex][i][j], O.XopDestBuffs[seqindex][i][j], IM_ROTATE_270, IM_DEFAULT, 0); break;
				}
		// copy to display...
*/		imIntConvolve(O.ProcThread, O.SeqChildBuffs[seqindex][i], O.ConvBuff, O.KernelBuffs[Program], 0, 0);
		// add astygmatism compensation
		imBinConvert(O.ProcThread, O.ConvBuff, O.BinBuff, IM_LESS, O.CutOff, 0, 0);
		imBufCopy(O.ProcThread, O.BinBuff, O.SeqChildHostBinBuffs[seqindex][i], 0, (i == ImageSeq.ImageCount - 1) ? O.ProcOSB : 0);
		};
#endif
	p.ProcessingProgrammed = false;
	p.Status = VP_PROGRAM_VALID;

	return S_OK;
}

STDMETHODIMP COdyssey::VPStartAsyncProcessing()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	int seqindex = (O.SequenceIndex + 1) % 2;
	if (O.SequencePrograms[O.SequenceIndex].Status == VP_PROGRAM_RUNNING) return S_FALSE;
	if (O.SequencePrograms[seqindex].Status != VP_PROGRAM_VALID) return S_FALSE;
	O.SequenceIndex = seqindex;
	O.SeqTimeZero[seqindex] = imSysClock(O.GrabThread, 0);

	imDigGrabSequence(O.GrabThread, 0, O.Cam, O.SeqMainBuff[seqindex], O.SequencePrograms[seqindex].AIS.ImageCount, O.SeqCtlBuff, O.SeqOSB);
	imSyncHost(O.SeqStartThread, O.SeqOSB, IM_STARTED);

//	imSyncControl(O.SeqStartThread, O.GrabOSB[0], IM_OSB_STATE, IM_SIGNALLED);
	O.SequencePrograms[seqindex].Status = VP_PROGRAM_RUNNING;
	return S_OK;
}

STDMETHODIMP COdyssey::VPWaitForProcessingComplete()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	int i;
	if (O.SequencePrograms[O.SequenceIndex].Status != VP_PROGRAM_RUNNING) return S_FALSE;
	
	if (!O.SequencePrograms[O.SequenceIndex].ProcessingProgrammed) ProgramProcessing();

	imSyncHost(O.ProcThread, O.ProcOSB, IM_COMPLETED);

	for (i = 0; i < O.SequencePrograms[O.SequenceIndex].AIS.ImageCount; i++)
		O.SequencePrograms[O.SequenceIndex].AIS.pImages[i].TimeStamp = 1000.0f * 
			(O.pSeqStartTimeBuff[i] - O.SeqTimeZero[O.SequenceIndex]);
	O.ClusteringSequenceIndex = O.SequenceIndex;
/*
	imIntMonadic(O.ProcThread, O.SeqChildBuffs[O.SequenceIndex][O.SequencePrograms[O.SequenceIndex].AIS.ImageCount / 2], ODYSSEY_GRABMIN, O.SeqChildBuffs[O.SequenceIndex][O.SequencePrograms[O.SequenceIndex].AIS.ImageCount / 2], IM_MAX, 0);
	imIntDyadic(O.ProcThread, O.SeqChildBuffs[O.SequenceIndex][O.SequencePrograms[O.SequenceIndex].AIS.ImageCount / 2], O.GraphicsBuff, O.DisplayHostBuff, IM_MIN, O.ProcOSB);
	imSyncHost(O.ProcThread, O.ProcOSB, IM_COMPLETED);
	pWndDisplay->LiveImage(O.pDisplayHostBuff);	
*/
	O.SequencePrograms[2] = O.SequencePrograms[O.SequenceIndex];
	O.SequencePrograms[O.SequenceIndex].Status = VP_PROGRAM_NULL;
	O.SequencePrograms[2].Status = VP_PROGRAM_CLUSTERING;	
	return S_OK;
}

STDMETHODIMP COdyssey::VPGetCurrentImageSequenceDelay(int *pDelay)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	//if (!VP.Locked) return S_FALSE;
	*pDelay = 1;
	return S_OK;
}


STDMETHODIMP COdyssey::VPWaitForClusters()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	int i;
	OdysseyData::t_SequenceProgram &p = O.SequencePrograms[2];

	if (!O.SequencePrograms[O.SequenceIndex].ProcessingProgrammed) ProgramProcessing();

	if (p.Status == VP_PROGRAM_CLUSTERING)
	{
		HANDLE HFinished[MAX_CLUSTERING_PROCESSORS];
		for (i = 0; i < O.GeneralSettings.ClusteringProcessors; i++)
			HFinished[i] = O.ActivationRecords[i].HFinished;
		ResetEvent(O.HReset);
		SetEvent(O.HStart);
		GetClusters(O.ActivationRecords);
		if (O.GeneralSettings.ClusteringProcessors > 1) WaitForMultipleObjects(O.GeneralSettings.ClusteringProcessors - 1, HFinished + 1, TRUE, INFINITE);

		ResetEvent(O.HStart);
		SetEvent(O.HReset);
		if (O.GeneralSettings.ClusteringProcessors > 1) WaitForMultipleObjects(O.GeneralSettings.ClusteringProcessors - 1, HFinished + 1, TRUE, INFINITE);
		}
	else return S_FALSE;

	return S_OK;
}

void COdyssey::LC_Get_LightInfo(float *pGrayLev, float *pSatLev)
{
	BYTE OldGrabMode = O.GrabMode;
	if (!O.Locked) 
		if (OldGrabMode != VC_NO_GRAB) SetNoGrab();
	imSyncControl(O.GrabThread, O.GrabOSB[0], IM_OSB_STATE, IM_NON_SIGNALLED);
	imDigGrab(O.GrabThread, 0, O.Cam, O.GrabBuff, 1, 0, O.GrabOSB[0]);	
	imSyncHost(O.GrabThread, O.GrabOSB[0], IM_COMPLETED);
	//imBufCopy(O.GrabThread, O.GrabBuff, O.UnderlayBuff, 0, 0);
	imSyncControl(O.GrabThread, O.GrabOSB[0], IM_OSB_STATE, IM_NON_SIGNALLED);
	imIntHistogram(O.ProcThread, O.GrabBuff, O.HistoBuff, IM_DEFAULT, O.GrabOSB[0]);
	imSyncHost(O.GrabThread, O.GrabOSB[0], IM_COMPLETED);
	int Sum = 0;
	int GraySum = 0;
	int SatSum = 0;
	int i;
	for (i = 0; i < O.LightControlSettings.SaturationGrayLev; i++)
	{
		Sum += O.pHistoBuff[i];
		GraySum += O.pHistoBuff[i] * i;
		}
	for (; i < 256; i++)
	{
		Sum += O.pHistoBuff[i];
		SatSum += O.pHistoBuff[i];
		GraySum += O.pHistoBuff[i] * i;
		}
	*pGrayLev = (float)GraySum / (float)Sum;
	*pSatLev = (float)SatSum / (float)Sum;
	if (!O.Locked) 
		switch (OldGrabMode)
		{
			case VC_GRAB_LIVE:			SetLiveGrab(); break;
			case VC_GRAB_SINGLE_FRAME:	SetSingleFrameGrab(); break;
			};
}

bool COdyssey::LC_CanSetLightLevel()
{
	if (Slots[0].pUnknown)
	{
		IStage *iSt = 0;
		if (Slots[0].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) == S_OK)
		{
			iSt->Release();
			return true;
			}
		if (iSt) iSt->Release();
		};
	return false;
}

UINT COdyssey::ClusterThreadHook(void *ActRecord)
{
	OdysseyData::t_ActivationRecord *pAR = (OdysseyData::t_ActivationRecord *)ActRecord;
	HANDLE HEvsStart[2], HEvsReset[2];
	HEvsStart[0] = HEvsReset[0] = pAR->pO->HTerminate;
	HEvsStart[1] = pAR->pO->HStart;
	HEvsReset[1] = pAR->pO->HReset;
	while (WaitForMultipleObjects(2, HEvsStart, FALSE, INFINITE) != WAIT_OBJECT_0)
	{
		GetClusters(pAR);
		SetEvent(pAR->HFinished);
		if (WaitForMultipleObjects(2, HEvsReset, FALSE, INFINITE) == WAIT_OBJECT_0) break;
		SetEvent(pAR->HFinished);
		}
	_endthreadex(S_OK);
	return S_OK;
	};

void COdyssey::GetClusters(OdysseyData::t_ActivationRecord *pAR)
{
	int i;
	OdysseyData &O = *pAR->pO;
	OdysseyData::t_SequenceProgram &p = O.SequencePrograms[2];
	for (i = pAR->ThreadIndex; i < p.AIS.ImageCount; i += O.GeneralSettings.ClusteringProcessors)
		if (GetClusters(O.pSeqChildHostBinBuffs[O.ClusteringSequenceIndex][i], PrecompData, p.AIS.pImages[i].pClusters, 
			(int *)&p.AIS.pImages[i].ClusterCount, O.ImageWidth, O.ImageHeight, O.OffX, O.OffY, O.WinWidth, O.WinHeight, O.SegSpace + (O.ImageWidth * 2 * pAR->ThreadIndex), 
			O.SegSpace + (O.ImageWidth * 2 * pAR->ThreadIndex + O.ImageWidth)) != S_OK)
				p.AIS.pImages[i].ClusterCount = 0;
	}

void COdyssey::ProgramProcessing()
{
	int i, j;

	OdysseyData::t_SequenceProgram &p = O.SequencePrograms[O.SequenceIndex];

	imSyncGrabSequence(O.SeqStartThread, O.SeqOSB, 0, IM_SEQ_WAIT);
	imIntHistogram(O.SeqStartThread, O.SeqChildBuffs[O.SequenceIndex][0], O.HistoBuff, IM_DEFAULT, O.GrabOSB[0]);
	imSyncHost(O.SeqStartThread, O.GrabOSB[0], IM_COMPLETED);
	imSyncControl(O.SeqStartThread, O.LUTOSB, IM_OSB_STATE, IM_WAITING);
	int avg = 0;
	for (i = 0; i < 256; i++)
		avg += i * O.pHistoBuff[i];
	avg /= (O.ImageHeight * O.ImageWidth);
	float corr = O.LightControlSettings.TargetGrayLev / avg;
	for (i = 0; i < 256; i++) O.pLUT[i] = (corr * i <= 255) ? (corr * i) : 255;
	imBufPut1d(O.SeqStartThread, O.LUTBuff, 0, 256, O.pLUT);
	imThrNop(O.SeqStartThread, O.LUTOSB);
	
	imSyncThread(O.ProcThread, O.SeqOSB, IM_COMPLETED);
	imSyncThread(O.ProcThread, O.LUTOSB, IM_COMPLETED);

	for (i = 0; i < p.AIS.ImageCount; i++)
	{
		//imSyncGrabSequence(O.ProcThread, O.SeqOSB, i, IM_SEQ_WAIT_THREAD);
		if (O.FlatFieldBuffs[p.ActiveProgram]) imIntDyadic(O.ProcThread, O.SeqChildBuffs[O.SequenceIndex][i], O.FlatFieldBuffs[p.ActiveProgram], O.SeqChildBuffs[O.SequenceIndex][i], IM_SUB, 0);
		imIntLutMap(O.ProcThread, O.SeqChildBuffs[O.SequenceIndex][i], O.SeqChildBuffs[O.SequenceIndex][i], O.LUTBuff, 0);
		for (j = 0; j < O.ExtendedOperation.OpDescriptions.Count; j++)
			switch (O.ExtendedOperation.OpDescriptions.Desc[j].Type)
			{
				case XOP_TYPE_COPY:		imBufCopy(O.ProcThread, O.XopSrcBuffs[O.SequenceIndex][i][j], O.XopDestBuffs[O.SequenceIndex][i][j], 0, 0); break;
				case XOP_TYPE_HFLIP:	imIntFlip(O.ProcThread, O.XopSrcBuffs[O.SequenceIndex][i][j], O.XopDestBuffs[O.SequenceIndex][i][j], IM_FLIP_H, IM_DEFAULT, 0); break;
				case XOP_TYPE_VFLIP:	imIntFlip(O.ProcThread, O.XopSrcBuffs[O.SequenceIndex][i][j], O.XopDestBuffs[O.SequenceIndex][i][j], IM_FLIP_V, IM_DEFAULT, 0); break;
				case XOP_ROTATE_90:		imIntFlip(O.ProcThread, O.XopSrcBuffs[O.SequenceIndex][i][j], O.XopDestBuffs[O.SequenceIndex][i][j], IM_ROTATE_90, IM_DEFAULT, 0); break;
				case XOP_ROTATE_180:	imIntFlip(O.ProcThread, O.XopSrcBuffs[O.SequenceIndex][i][j], O.XopDestBuffs[O.SequenceIndex][i][j], IM_ROTATE_180, IM_DEFAULT, 0); break;
				case XOP_ROTATE_270:	imIntFlip(O.ProcThread, O.XopSrcBuffs[O.SequenceIndex][i][j], O.XopDestBuffs[O.SequenceIndex][i][j], IM_ROTATE_270, IM_DEFAULT, 0); break;
				}
		// copy to display...
		imIntConvolve(O.ProcThread, O.SeqChildBuffs[O.SequenceIndex][i], O.ConvBuff, O.KernelBuffs[p.ActiveProgram], 0, 0);
		if (O.FilterEqBuffs[p.ActiveProgram]) imIntDyadic(O.ProcThread, O.ConvBuff, O.FilterEqBuffs[p.ActiveProgram], O.ConvBuff, IM_SUB, 0);
		imBinConvert(O.ProcThread, O.ConvBuff, O.BinBuff, IM_LESS, O.ProgramLibrary.Programs[p.ActiveProgram].Threshold, 0, 0);
		imBufCopy(O.ProcThread, O.BinBuff, O.SeqChildHostBinBuffs[O.SequenceIndex][i], 0, 0);
		};
	imThrNop(O.ProcThread, O.ProcOSB);
	p.ProcessingProgrammed = true;
}

UINT COdyssey::RefreshThreadHook(void *owner)
{
	COdyssey *This = (COdyssey *)owner;
	
	HANDLE HFlux[2];
	HFlux[0] = This->O.HTerminateRefresh;
	HFlux[1] = This->O.HRefreshStart;
	int nexttime;
	DWORD wait = WAIT_OBJECT_0 + 1;
	nexttime = GetTickCount() + This->O.GeneralSettings.RefreshCycleTime;
	while (wait != WAIT_OBJECT_0 && WaitForMultipleObjects(2, HFlux, FALSE, INFINITE) != WAIT_OBJECT_0)
	{
		while ((wait = WaitForMultipleObjects(2, HFlux, FALSE, 0)) != WAIT_OBJECT_0)
			if (wait == WAIT_TIMEOUT)
			{
				This->pWndDisplay->SetImage(This->O.pDisplayHostBuff);	
				SetEvent(This->O.HRefreshStopped);
				break;
				}
			else if (wait == WAIT_OBJECT_0 + 1)
				if (GetTickCount() > nexttime)
				{
					imSyncControl(This->O.GrabThread, This->O.GrabOSB[0], IM_OSB_STATE, IM_WAITING);
					imDigGrab(This->O.GrabThread, 0, This->O.Cam, This->O.GrabBuff, 1, 0, This->O.GrabOSB[0]);
					imSyncHost(This->O.GrabThread, This->O.GrabOSB[0], IM_COMPLETED);
					imSyncControl(This->O.GrabThread, This->O.GrabOSB[0], IM_OSB_STATE, IM_WAITING);
					imIntMonadic(This->O.GrabThread, This->O.GrabBuff, ODYSSEY_GRABMIN, This->O.GrabBuff, IM_MAX, 0);
					imIntDyadic(This->O.GrabThread, This->O.GrabBuff, This->O.GraphicsBuff, This->O.DisplayHostBuff, IM_MIN, This->O.GrabOSB[0]);
					//imBufCopy(This->O.GrabThread, This->O.GrabBuff, This->O.DisplayHostBuff, 0, This->O.GrabOSB[0]);
					imSyncHost(This->O.GrabThread, This->O.GrabOSB[0], IM_COMPLETED);
					This->pWndDisplay->LiveImage(This->O.pDisplayHostBuff);	
					nexttime += This->O.GeneralSettings.RefreshCycleTime;
					Sleep(This->O.GeneralSettings.RefreshCycleTime / 2);
					};		
		}
	_endthreadex(S_OK);
	return S_OK;
	};

void COdyssey::VP_Internal_MakeFlatFieldImage(BYTE *pImg, int imgcount)
{
	BYTE OldGrabMode = O.GrabMode;
	if (!O.Locked) 
		if (OldGrabMode != VC_NO_GRAB) SetNoGrab();

	imSyncControl(O.GrabThread, O.SeqOSB, IM_OSB_STATE, IM_WAITING);
	imDigGrabSequence(O.GrabThread, 0, O.Cam, O.SeqMainBuff[0], imgcount, O.SeqCtlBuff, O.SeqOSB);
	imSyncHost(O.GrabThread, O.SeqOSB, IM_COMPLETED);

	int imgsize = O.ImageWidth * O.ImageHeight;
	int *pAvg = (int *)calloc(imgsize, sizeof(int));
	int i, j;
	for (i = 0; i < imgcount; i++)
	{
		imBufCopy(O.ProcThread, O.SeqChildBuffs[0][i], O.FreezeBuff, 0, O.ProcOSB);
		imSyncHost(O.ProcThread, O.ProcOSB, IM_COMPLETED);
		for (j = 0; j < imgsize; j++)
			pAvg[j] += (int)(unsigned)(unsigned char)O.pFreezeBuff[j];
		}
	__int64 avgsum = 0;
	for (j = 0; j < imgsize; j++) avgsum += pAvg[j];
	avgsum /= (imgsize * imgcount);
	for (j = 0; j < imgsize; j++)
		pImg[j] = (pAvg[j] / imgcount - avgsum);

	free(pAvg);

	if (!O.Locked)
		switch (OldGrabMode)
		{
			case VC_GRAB_LIVE:			SetLiveGrab(); break;
			case VC_GRAB_SINGLE_FRAME:	SetSingleFrameGrab(); break;
			};
}

void COdyssey::FG_Internal_SetLive(DWORD Context)
{
	((COdyssey *)(void *)Context)->SetLiveGrab();
}

void COdyssey::FG_Internal_SetStill(DWORD Context)
{
	((COdyssey *)(void *)Context)->SetNoGrab();
}

void COdyssey::FG_Internal_LoadGrabBuffer(DWORD Context, int bank, int number)
{
	COdyssey *pO = (COdyssey *)(void *)Context;
	OdysseyData &O = pO->O;
	imIntMonadic(O.ProcThread, O.SeqChildBuffs[bank][number], ODYSSEY_GRABMIN, O.DisplayHostBuff, IM_MAX, 0);
	imIntDyadic(O.ProcThread, O.DisplayHostBuff, O.GraphicsBuff, O.DisplayHostBuff, IM_MIN, O.ProcOSB);
	imSyncHost(O.ProcThread, O.ProcOSB, IM_COMPLETED);
	pO->pWndDisplay->SetImage(O.pDisplayHostBuff);
}

void COdyssey::FG_Internal_Clear(DWORD Context)
{
	((COdyssey *)(void *)Context)->Clear(ODYSSEY_TRANSPARENT);
}

void COdyssey::FG_Internal_DrawCircles(DWORD Context)
{
	COdyssey *pO = (COdyssey *)(void *)Context;
	OdysseyData &O = pO->O;
	int i;
	for (i = 100; i < O.ImageWidth / 2 || i < O.ImageHeight / 2; i += 100)
		pO->Arc(O.ImageWidth / 2, O.ImageHeight / 2, i, i, 0, 360.0, ODYSSEY_LTBLUE);
	pO->Arc(O.ImageWidth / 2, O.ImageHeight / 2, 10, 10, 0, 360.0, ODYSSEY_LTRED);
}

bool COdyssey::VP_Internal_AsyncAcquireWithForcedCutOff(unsigned program, int cutoff, Cluster *pSpace, int *pMaxClusters)
{
	AsyncImageSequence ASI;
	ASI.pImages = new AsyncProcessedImage[ASI.ImageCount = 1];
	ASI.pImages[0].ClusterCount = *pMaxClusters;
	ASI.pImages[0].pClusters = pSpace;
	ASI.pImages[0].TimeStamp = 0;
	int thresholdbackup = O.ProgramLibrary.Programs[program].Threshold;
	O.ProgramLibrary.Programs[program].Threshold = cutoff;
	try
	{		
		if (VPPrepareAsyncProcessing(program, ASI) != S_OK) throw "Error preparing buffers.\r\nTry reducing the number of images or increasing the nonpaged DMA buffers in GNL/MIL installation.";
		if (VPStartAsyncProcessing() != S_OK) throw "Error starting image sequence.";
		//VPWaitForClusters();
		if (VPWaitForProcessingComplete() != S_OK) throw "No valid image sequence running.";
	
		ASI.pImages[0].ClusterCount = *pMaxClusters;
		ASI.pImages[0].TimeStamp = 0;
		if (VPPrepareAsyncProcessing(program, ASI) != S_OK) throw "Unexpected error preparing buffers.\r\nDebug the program and check for memory corruption.";		
		if (VPStartAsyncProcessing() != S_OK) throw "Unexpected error starting image sequence.";		
		if (VPWaitForClusters() != S_OK) throw "Error during clustering.\r\nTry reducing / increasing the number of clusters.";
		if (VPWaitForProcessingComplete() != S_OK) throw "Unexpected error waiting for the end of image sequence.";
		}
	catch (char *x)
	{
		MessageBox(0, x, "Error in Asynchronous Acquisition with Forced CutOff", MB_ICONERROR | MB_OK);		
		};

	O.ProgramLibrary.Programs[program].Threshold = thresholdbackup;
	*pMaxClusters = ASI.pImages[0].ClusterCount;
	return true;
}

#include "Stage_i.c"




