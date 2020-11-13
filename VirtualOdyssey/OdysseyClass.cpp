// OdysseyClass.cpp : Implementation of COdyssey
#include "stdafx.h"
#include "Odyssey1.h"
#include "OdysseyClass.h"
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

	/* Region: Main initialization */
	O.ProcSys = 0;
	O.Dev = 0;
	O.GrabThread = 0;
	O.ProcThread = 0;
	O.Cam = 0;
	O.ProcOSB = 0;
	O.ImageWidth = 1024;
	O.ImageHeight = 1024;
	O.ConvBuff = 0;
	O.BinBuff = 0;
	/* Check */
	O.CommandQueueLength = 0;
	/* End check */
	/* End region */

	/* Region: initialization for VisionProcessor/VisionProcessor2 operation */
	O.GrabOSB[0] = 0;
	O.GrabOSB[1] = 0;
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
	O.SeqStartThread = 0;
	O.SeqOSB = 0;
	O.SeqMainBuff[0] = 0;
	O.SeqMainHostBinBuff[0] = 0;
	O.SeqMainBuff[1] = 0;
	O.SeqMainHostBinBuff[1] = 0;
	for (i = 0; i < MAX_FRAMES_PER_NODE; i++)
	{
		O.SeqChildBuffs[0][i] = 0;
		O.SeqChildHostBinBuffs[0][i] = 0;
		O.pSeqChildHostBinBuffs[0][i] = 0;
		O.SeqChildBuffs[1][i] = 0;
		O.SeqChildHostBinBuffs[1][i] = 0;
		O.pSeqChildHostBinBuffs[1][i] = 0;
		}	
	O.SeqCtlBuff = 0;
	O.SeqStartTimeBuff = 0;
	O.pSeqStartTimeBuff = 0;
	O.SeqEndTimeBuff = 0;
	O.pSeqEndTimeBuff = 0;
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
	O.FreezeBuff = 0;
	O.pFreezeBuff = 0;
	O.DisplayHostBuff = 0;
	O.pDisplayHostBuff = 0;
	O.GraphicsBuff = 0;
	O.CursorBuff = 0;
	O.CursorVisible = false;
	O.IsThereCursor = false;
	O.UnderlayBuff = 0;
	O.OverlayBuff = 0;
	O.DisplayCtlBuff = 0;
	O.OverlayLUT = 0;
	SetDefaultPalette();	
	O.GraColorBuff = 0;
	O.Initialization = true;
	/* End region */

	/* Region: initialization for Automatic light control operation */
	O.HistoBuff = 0;
	O.pHistoBuff = 0;
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

	pWndDisplay = new CWndDisplay(O.ImageWidth, O.ImageHeight);
	char *wndname = (char *)AfxRegisterWndClass(NULL);
	pWndDisplay->CreateEx(0, wndname, "Odyssey Display", WS_VISIBLE | WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX, 0, 0, O.ImageWidth, O.ImageHeight, NULL, NULL, NULL);
	pWndDisplay->ShowWindow(SW_SHOW);

	O.HTerminateRefresh = CreateEvent(NULL, TRUE, FALSE, NULL);
	O.HRefreshMutex = CreateMutex(NULL, TRUE, FALSE);
	O.HRefreshThread = (HANDLE)_beginthreadex(NULL, 0, RefreshThreadHook, this, 0, (unsigned *)&d);
	SetThreadPriority(O.HRefreshThread, THREAD_PRIORITY_LOWEST);
	ReleaseMutex(O.HRefreshMutex);
	O.GrabMode = VC_GRAB_LIVE;

	/* End display initialization */
}

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

	SetLiveGrab();
	WaitForSingleObject(O.HRefreshThread, INFINITE);
	SetNoGrab();

	CloseHandle(O.HRefreshThread);
	CloseHandle(O.HRefreshMutex);
	CloseHandle(O.HTerminateRefresh);

	long d;

	for (i = 0; i < MAX_PROGRAMS; i++) 
	{
		O.KernelBuffs[i] = 0;
		O.FlatFieldBuffs[i] = 0;
		O.FilterEqBuffs[i] = 0;
		}
	for (i = 0; i < MAX_FRAMES_PER_NODE; i++)
		for (d = 0; d < MAX_XOP_BUFFERS; d++)
		{
			O.XopSrcBuffs[0][i][d] = 0;
			O.XopDestBuffs[0][i][d] = 0;
			O.XopSrcBuffs[1][i][d] = 0;
			O.XopDestBuffs[1][i][d] = 0;
			}

	GlobalFree(O.SegSpace);
	
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
		O.KernelBuffs[i] = 0;
		O.FlatFieldBuffs[i] = 0;
		O.FilterEqBuffs[i] = 0;
		}
	for (i = 0; i < MAX_FRAMES_PER_NODE; i++)
		for (d = 0; d < MAX_XOP_BUFFERS; d++)
		{
			O.XopSrcBuffs[0][i][d] = 0;
			O.XopDestBuffs[0][i][d] = 0;
			O.XopSrcBuffs[1][i][d] = 0;
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

		O.KernelBuffs[i] = 0;
		for (iy = 0; iy < (O.ProgramLibrary.Programs[i].KHeight + 1) / 2; iy++)
			for (ix = 0; ix < (O.ProgramLibrary.Programs[i].KWidth + 1) / 2; ix++)
			{
				Kernel[iy * O.ProgramLibrary.Programs[i].KWidth + ix] = 
					Kernel[iy * O.ProgramLibrary.Programs[i].KWidth + O.ProgramLibrary.Programs[i].KWidth - 1 - ix] = 
					Kernel[(O.ProgramLibrary.Programs[i].KHeight - 1 - iy) * O.ProgramLibrary.Programs[i].KWidth + ix] = 
					Kernel[(O.ProgramLibrary.Programs[i].KHeight - 1 - iy) * O.ProgramLibrary.Programs[i].KWidth + O.ProgramLibrary.Programs[i].KWidth - 1 - ix] = 
					O.ProgramLibrary.Programs[i].KernelDesc[iy * MAX_KERNEL_SIZE / 2 + ix];
				};

		if (O.ProgramLibrary.Programs[i].FlatFieldImage[0]) 
		{
			O.FlatFieldBuffs[i] = 0;
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
			if (pTempBuff) free(pTempBuff);
			}
		else O.FlatFieldBuffs[i] = 0;
		if (O.ProgramLibrary.Programs[i].FilterEqImage[0]) 
		{
			O.FilterEqBuffs[i] = 0;
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
			if (pTempBuff) free(pTempBuff);
			}
		else O.FilterEqBuffs[i] = 0;

		}
	for (i = 0; i < MAX_FRAMES_PER_NODE; i++)
		for (d = 0; d < O.ExtendedOperation.OpDescriptions.Count; d++)
		{
			O.XopSrcBuffs[0][i][d] = 0;
			O.XopSrcBuffs[1][i][d] = 0;
			O.XopDestBuffs[0][i][d] = 0;
			O.XopDestBuffs[1][i][d] = 0;
			}

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
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::Fill(unsigned int X, unsigned int Y, DWORD C)
{  
	InvalidateCursorArea(0, 0, O.ImageWidth, O.ImageHeight);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::Arc(unsigned int XC, unsigned int YC, unsigned int XR,
	unsigned int YR, double SA, double EA, DWORD C)
{  
	InvalidateCursorArea(XC - XR, YC - YR, XC + XR, YC + YR);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::ArcFill(unsigned int XC, unsigned int YC, unsigned int XR,
	unsigned int YR, double SA, double EA, DWORD C)
{  
	InvalidateCursorArea(XC - XR, YC - YR, XC + XR, YC + YR);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::Rect(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::RectFill(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::Line(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::Text(unsigned int XS, unsigned int YS, BYTE *S, DWORD C)
{  
	InvalidateCursorArea(0, 0, O.ImageWidth, O.ImageHeight);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP COdyssey::TextFont(unsigned int F)
{  
	return S_OK;
	};

STDMETHODIMP COdyssey::TextScale(double XS, double YS)
{  
	return S_OK;
	};

STDMETHODIMP COdyssey::Clear(unsigned int C)
{  
	InvalidateCursorArea(0, 0, O.ImageWidth, O.ImageHeight);
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
	O.CursorBuff = 0;
	O.CursorSaveArea = 0;
	char *TempSpace = (char *)malloc(O.CursorWidth * O.CursorHeight);
	fread(TempSpace, O.CursorWidth * O.CursorHeight, 1, InFile);
	fclose(InFile);	
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
		O.IsThereCursor = O.CursorVisible = false;
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP COdyssey::HideCursor()
{  
	if (O.IsThereCursor && O.CursorVisible)
	{	
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
	if (O.GrabMode == VC_GRAB_LIVE) WaitForSingleObject(O.HRefreshMutex, INFINITE);
	O.GrabMode = VC_NO_GRAB;
	return S_OK;
	};

STDMETHODIMP COdyssey::SetLiveGrab()
{  
	if (O.GrabMode == VC_GRAB_LIVE) return S_OK;
	ReleaseMutex(O.HRefreshMutex);
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

	WaitForSingleObject(O.HRefreshMutex, INFINITE);
	*ppImage = O.pFreezeBuff;
	ReleaseMutex(O.HRefreshMutex);
	return S_OK;
	};

STDMETHODIMP COdyssey::ClearFrozen()
{  
	if (O.GrabMode != VC_GRAB_LIVE) return S_FALSE;
	return S_OK;
	};

STDMETHODIMP COdyssey::SetSingleFrameGrab()
{  
	O.GrabMode = VC_GRAB_SINGLE_FRAME;
	return S_OK;
	};

STDMETHODIMP COdyssey::HoldFrame(BYTE **ppImage)
{  
   
	if (O.GrabMode != VC_GRAB_SINGLE_FRAME)
	{	
		*ppImage = 0;
		return S_OK;
		};
	if (ppImage) *ppImage = O.pFreezeBuff;
	return S_OK;
	};

STDMETHODIMP COdyssey::ShowHeldFrame()
{  
	if (O.GrabMode != VC_GRAB_SINGLE_FRAME) return S_FALSE;
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

	O.CursorBuff = 0;
	O.CursorSaveArea = 0;
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

	if (O.pFrameStartCallBack) O.pFrameStartCallBack(O.Context);

	HRes = S_OK;
	*pMaxClusters = 0;
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

	*pMaxClusters = 0;
	return S_OK;
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

	SetNoGrab();

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

float COdyssey::VP_Internal_GetFrameRate()
{
	return 1000000.0f;
}

STDMETHODIMP COdyssey::VPPrepareAsyncProcessing(UINT Program, AsyncImageSequence ImageSeq)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Program >= O.ProgramLibrary.Count) return E_INVALIDARG;
	if (ImageSeq.ImageCount > MAX_FRAMES_PER_NODE) return E_INVALIDARG;

	int seqindex = (O.SequenceIndex + 1) % 2;
	OdysseyData::t_SequenceProgram &p = O.SequencePrograms[seqindex];

	if (p.Status != VP_PROGRAM_NULL) return S_FALSE;
	p.AIS = ImageSeq;

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
	O.SeqTimeZero[seqindex] = 0;
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
	for (i = 0; i < O.SequencePrograms[O.SequenceIndex].AIS.ImageCount; i++)
		O.SequencePrograms[O.SequenceIndex].AIS.pImages[i].TimeStamp = .001f * i;
	O.ClusteringSequenceIndex = O.SequenceIndex;

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
	*pGrayLev = 128.0f;
	*pSatLev = 0.0f;
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
		p.AIS.pImages[i].ClusterCount = 0;
	}

void COdyssey::ProgramProcessing()
{
	int i, j;

	OdysseyData::t_SequenceProgram &p = O.SequencePrograms[O.SequenceIndex];

	p.ProcessingProgrammed = true;
}

UINT COdyssey::RefreshThreadHook(void *owner)
{
	COdyssey *This = (COdyssey *)owner;
	
	HANDLE HFlux[2];
	HFlux[0] = This->O.HTerminateRefresh;
	HFlux[1] = This->O.HRefreshMutex;
	int nexttime;
	nexttime = GetTickCount() + This->O.GeneralSettings.RefreshCycleTime;
	while (WaitForMultipleObjects(2, HFlux, FALSE, INFINITE) != WAIT_OBJECT_0)
	{
		ReleaseMutex(This->O.HRefreshMutex);
		if (GetTickCount() > nexttime)
		{
			//This->pWndDisplay->LiveImage(This->O.pDisplayHostBuff);	
			nexttime += This->O.GeneralSettings.RefreshCycleTime;
			}
		}
	_endthreadex(S_OK);
	return S_OK;
	};

void COdyssey::VP_Internal_MakeFlatFieldImage(BYTE *pImg, int imgcount)
{
}

#include "Stage_i.c"



