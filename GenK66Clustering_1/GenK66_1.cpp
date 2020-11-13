// GenK66_1.cpp : Implementation of CGenK66_1
#include "stdafx.h"

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "GenK66Clustering_1.h"
#include "GenK66_1.h"
#include "Config2.h"
#include "EditConfig.h"
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CGenK66_1
const int ConfigDataN = 4;

QueryDataInfo ConfigDataQDI[ConfigDataN] =
{
	{"EnableCracking",		ST_INT,   STRUCT_OFFSET(ConfigData, EnableCracking),	"1"},
	{"MinArea",				ST_INT,   STRUCT_OFFSET(ConfigData, MinArea),				"10"},
	{"SqueezeLimit",		ST_FLOAT, STRUCT_OFFSET(ConfigData, SqueezeLimit),		"3.0"},
	{"CrackDist",			ST_INT,   STRUCT_OFFSET(ConfigData, CrackDist),				"50."}
	};

CGenK66_1::CGenK66_1()
{
	Name[0] = 0;
	HANDLE HStatusChangeEvent = 0;
	strcpy(Slots[0].Name, "Genesis");
	
	SySalConfig Temp = {0, 0, 0};
	GetData(Temp, ConfigDataN, ConfigDataQDI, &C, true);	

	int i;
	for (i = 0; i < NUMBER_OF_SLOTS; i++)
	{
		Slots[i].pUnknown = 0;
		Slots[i].Type = SYSAL_CONN_TYPE_NULL;
		};
	CamSpec.Width = CamSpec.Height = 0;
	CamSpec.WinWidth = CamSpec.WinHeight = 0;
	CamSpec.OffX = CamSpec.OffY = 0;
	CamSpec.PixelToMicronX = CamSpec.PixelToMicronY = 1.f;
	SegPointer1 = SegPointer2 = 0;		
	Locked = false;
}

CGenK66_1::~CGenK66_1()
{
	if (Locked) Unlock();
	if (SegPointer1) delete [] SegPointer1;
	if (SegPointer2) delete [] SegPointer2;
	};


// ISySalObject
STDMETHODIMP CGenK66_1::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CGenK66_1::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CGenK66_1::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	ConfigData TC;
	if (GetData(*pConfig, ConfigDataN, ConfigDataQDI, &TC, false) != ConfigDataN) return S_FALSE;
	for (TC.ZoneCount = 0; (TC.ZoneCount < MAX_THRESHOLD_ZONES) && (ReadThresholdBuffer(pConfig, TC.ZoneCount, TC.ThresholdZones[TC.ZoneCount])); TC.ZoneCount++);
	C = TC;
	W2LLimit = C.SqueezeLimit * C.SqueezeLimit;
	return S_OK;
}

STDMETHODIMP CGenK66_1::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	return WriteConfig(pConfig, C);
}

STDMETHODIMP CGenK66_1::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);

	GetData(*pConfig, ConfigDataN, ConfigDataQDI, &MyDlg.C, true);
	for (MyDlg.C.ZoneCount = 0; (MyDlg.C.ZoneCount < MAX_THRESHOLD_ZONES) && (ReadThresholdBuffer(pConfig, MyDlg.C.ZoneCount, MyDlg.C.ThresholdZones[MyDlg.C.ZoneCount])); MyDlg.C.ZoneCount++);

	if (MyDlg.DoModal() == IDOK)
	{
		WriteConfig(pConfig, MyDlg.C);
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CGenK66_1::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CGenK66_1::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 1;
	return S_OK;
}

STDMETHODIMP CGenK66_1::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return E_NOTIMPL;
}

STDMETHODIMP CGenK66_1::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return E_NOTIMPL;
}

STDMETHODIMP CGenK66_1::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CGenK66_1::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Genesis Supported 6x6 Kernel FIR ClusterFinder", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CGenK66_1::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CGenK66_1::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CGenK66_1::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CGenK66_1::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CGenK66_1::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CGenK66_1::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CGenK66_1::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CGenK66_1::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here
	try
	{
		if (Slots[0].pUnknown)
		{
			IGenesis *iGe;
			if (Slots[0].pUnknown->QueryInterface(IID_IGenesis, (void **)&iGe) == S_OK) iGe->Release();
			else throw 0;
			}		
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

// IClusterFinder
STDMETHODIMP CGenK66_1::EnableImageEqualization(boolean bEnable)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	
	if (bEnable) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CGenK66_1::EnableShapeParameters(boolean bEnable)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!bEnable) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CGenK66_1::EnableGrayLevel(boolean bEnable)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (bEnable) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CGenK66_1::GetClusters(BYTE *pImage, Cluster *pSpace, int *pMaxNumber, BYTE Threshold, BYTE *pBinaryImage)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	CutOff = 50L * (unsigned)Threshold;

// CHECK WINDOW BOUNDS!
	if (!C.EnableCracking) 
		return GetClusters(pImage, PrecompData, pSpace, pMaxNumber, 
			CamSpec.Width, CamSpec.Height, CamSpec.OffX, CamSpec.OffY, CamSpec.WinWidth, CamSpec.WinHeight);
	else
	{
		int MaxBound = *pMaxNumber;
		int MaxCount = MaxBound;
		int i, j;
		HRESULT HRes = GetClusters(pImage, PrecompData, pSpace, &MaxCount, CamSpec.Width, CamSpec.Height, CamSpec.OffX, 
			CamSpec.OffY, CamSpec.WinWidth, CamSpec.WinHeight);
		for (i = 0; i < MaxCount; i++)
		{
			Cluster *p = pSpace + i;
			if (p->Area > C.MinArea)
			{
				double IXX = p->Inertia.IXX;
				double IYY = p->Inertia.IYY;
				double IXY = 2. * p->Inertia.IXY;
				double ISxxyy = IXX + IYY;
				double IDxxyy = IXX - IYY;
				double ID = IDxxyy * IDxxyy + IXY * IXY;
				double RX;
				if (ID > 0. && ISxxyy > 0.)
				{
					double IDR = sqrt(ID);
					double IL = ISxxyy + IDR;
					double IW = ISxxyy - IDR;
					double W2L = IW / IL;
					if (W2L < W2LLimit)
					{
						double DX;
						double DY;
						double INorm;
						if (IDxxyy > 0.)
						{
							DX = IDxxyy + IDR;
							DY = IXY;
							INorm = 1. / hypot(DX, DY);
							}
						else
						{
							DY = -IDxxyy + IDR;
							DX = IXY;
							INorm = 1. / hypot(DX, DY);
							IXX = IYY;
							};
						DX *= INorm;
						DY *= INorm;						
						RX = sqrt(IXX / p->Area);
						int steps = floor(2. * RX / C.CrackDist + 1.);
						if (MaxCount + steps - 1 >= MaxBound) 
						{
							*pMaxNumber = MaxCount;
							return S_FALSE;
							};
						for (j = 1; j <= steps; j++)
							pSpace[MaxCount + j - 1] = pSpace[i + j];
						Cluster T = *p;
						for (j = 0; j <= steps; j++)
						{
							double m = (2. * j - steps) / steps;
							pSpace[i + j] = T;
							pSpace[i + j].X = T.X + m * RX * DX;
							pSpace[i + j].Y = T.Y + m * RX * DY;
							};
						i += steps;
						MaxCount += steps - 1;
						};
					};
				};
			};
		
		*pMaxNumber = MaxCount;
		return HRes;
		};
}

STDMETHODIMP CGenK66_1::GetGrayLevelStatus(boolean *pReturn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pReturn = false;
	return S_OK;
}

STDMETHODIMP CGenK66_1::GetImageEqualizationStatus(boolean *pReturn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pReturn = false;
	return S_OK;
}

STDMETHODIMP CGenK66_1::GetShapeParametersStatus(boolean *pReturn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pReturn = true;
	return S_OK;
}

STDMETHODIMP CGenK66_1::SetCameraSpec(CameraSpec Spec)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (Spec.Width <= 0 || Spec.Height <= 0 || Spec.WinWidth <= 0 || Spec.WinHeight <= 0 ||
		Spec.PixelToMicronX == 0.f || Spec.PixelToMicronY == 0.f) return E_INVALIDARG;

	CamSpec = Spec;

	if (SegPointer1) delete [] SegPointer1;
	if (SegPointer2) delete [] SegPointer2;
	SegPointer1 = new Segment[CamSpec.WinWidth];
	SegPointer2 = new Segment[CamSpec.WinWidth];
	return S_OK;
}

STDMETHODIMP CGenK66_1::GetCameraSpec(CameraSpec *pSpec)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pSpec = CamSpec;
	return S_OK;
}

STDMETHODIMP CGenK66_1::MakeEqualization(BYTE *pImage, BYTE *pRefLevel)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

// IClusterFinder2
STDMETHODIMP CGenK66_1::GetBoundedClusters(BYTE *pImage, BoundedCluster *pSpace, int *pMaxNumber, BYTE Threshold, BYTE *pBinaryImage)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	CutOff = 50L * (unsigned)Threshold;

// CHECK WINDOW BOUNDS!

	return GetBoundedClusters(pImage, PrecompData, pSpace, pMaxNumber, CamSpec.Width, CamSpec.Height, CamSpec.OffX, CamSpec.OffY, CamSpec.WinWidth, CamSpec.WinHeight);
}

//ILockUnlock
STDMETHODIMP CGenK66_1::Lock()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Locked) return S_FALSE;
	if (!Slots[0].pUnknown) return S_FALSE;
	IGenesis *iGe;
	if (Slots[0].pUnknown->QueryInterface(IID_IGenesis, (void **)&iGe) != S_OK) return S_FALSE;
	GenesisData *CG;
	if (iGe->LockInternalData((BYTE **)&CG) != S_OK)
	{
		iGe->Release();
		return S_FALSE;
		};
	iGe->Release();
	CG->ExternalGrabData = this;
	CG->pHoldFrame = cgenk66HoldFrame;
	CG->pShowHeldFrame = cgenk66ShowHeldFrame;
	CG->pReleaseFrame = cgenk66ReleaseFrame;	
	CG->pGetCurrentFrameGrabDelay = cgenk66GetCurrentFrameGrabDelay;
	CG->pFlushGrabBackBuffers = cgenk66FlushGrabBackBuffers;

	HostBinBufId[0] = MbufAlloc2d(CG->Sys, GENESIS_GRAB_WINDOW_WIDTH, GENESIS_GRAB_WINDOW_HEIGHT, 1 + M_UNSIGNED, M_IMAGE + M_PROC + M_OFF_BOARD, M_NULL);
	HostBinBufId[1] = MbufAlloc2d(CG->Sys, GENESIS_GRAB_WINDOW_WIDTH, GENESIS_GRAB_WINDOW_HEIGHT, 1 + M_UNSIGNED, M_IMAGE + M_PROC + M_OFF_BOARD, M_NULL);
	NatHostBinBufId[0] = MbufInquire(HostBinBufId[0],  M_NATIVE_ID, M_NULL);
	NatHostBinBufId[1] = MbufInquire(HostBinBufId[1],  M_NATIVE_ID, M_NULL);
	HostBinBuf[0] = (BYTE *)MbufInquire(HostBinBufId[0], M_HOST_ADDRESS, 0);
	HostBinBuf[1] = (BYTE *)MbufInquire(HostBinBufId[1], M_HOST_ADDRESS, 0);

	NatSysThreadId = MsysInquire(CG->Sys, M_NATIVE_THREAD_ID,  M_NULL);
	NatDigCameraId = MdigInquire(CG->ImGrabber, M_NATIVE_CAMERA_ID , M_NULL);
	NatDigControlId = MdigInquire(CG->ImGrabber, M_NATIVE_CONTROL_ID, M_NULL);
	NatDigId = MdigInquire(CG->ImGrabber, M_NATIVE_ID, M_NULL);
	NatBufId = MbufInquire(CG->GrabPage[CG->DisplayGrabPage], M_NATIVE_ID, M_NULL);
	NatDevId = MsysInquire(CG->Sys, M_NATIVE_ID, M_NULL);

	MsysControl(CG->Sys, M_NATIVE_MODE_ENTER, M_NULL);

	imThrControl(NatSysThreadId, IM_THR_MAX_PPS, 4);
	imThrAlloc(NatDevId, 0, &NatGrabThreadId);
	imThrControl(NatGrabThreadId, IM_THR_MAX_PPS, 4);
	imThrControl(NatGrabThreadId, IM_THR_ACCELERATOR, IM_DISABLE);
   
	imSyncAlloc(NatSysThreadId, &SysOSB);
	imSyncAlloc(NatGrabThreadId, &GrabOSB[0]);
	imSyncAlloc(NatGrabThreadId, &GrabOSB[1]);

	imBufAllocControl(NatSysThreadId, &NatGrabCtlId);
	imBufPutField(NatSysThreadId, NatGrabCtlId, IM_CTL_GRAB_MODE, IM_ASYNCHRONOUS);

	imBufAlloc(NatSysThreadId, KERNEL_XSIZE, KERNEL_YSIZE, 1, IM_SHORT, IM_PROC, &NatFIRKernelId);
	imBufPut(NatSysThreadId, NatFIRKernelId, Kernel);
	imBufPutField(NatSysThreadId, NatFIRKernelId, IM_KER_CLIP, IM_ENABLE);

	imBufAlloc(NatSysThreadId, GENESIS_GRAB_WINDOW_WIDTH, GENESIS_GRAB_WINDOW_HEIGHT, 1, IM_USHORT, IM_PROC, &NatConvBufId);
	imBufAlloc2d(NatSysThreadId, GENESIS_GRAB_WINDOW_WIDTH, GENESIS_GRAB_WINDOW_HEIGHT, IM_BINARY, IM_PROC, &NatBinBufId);

	imBufAlloc(NatSysThreadId, GENESIS_GRAB_WINDOW_WIDTH, GENESIS_GRAB_WINDOW_HEIGHT, 1, IM_UBYTE, IM_PROC, &NatGrabBufId[0]);
	imBufAlloc(NatSysThreadId, GENESIS_GRAB_WINDOW_WIDTH, GENESIS_GRAB_WINDOW_HEIGHT, 1, IM_UBYTE, IM_PROC, &NatGrabBufId[1]);

	{
		int i;
		for (i = 0; i < C.ZoneCount; i++)
		{
			imBufChild(NatSysThreadId, NatBinBufId, C.ThresholdZones[i].Left, C.ThresholdZones[i].Top, C.ThresholdZones[i].Width, C.ThresholdZones[i].Height, &Children[i].NatBinChildBufId);
			imBufChild(NatSysThreadId, NatConvBufId, C.ThresholdZones[i].Left, C.ThresholdZones[i].Top, C.ThresholdZones[i].Width, C.ThresholdZones[i].Height, &Children[i].NatConvChildBufId);
			};
		};

	imThrNop(NatSysThreadId, SysOSB);

	imDigGrab(NatGrabThreadId, NatDigId, NatDigCameraId, NatGrabBufId[0], 1L, NatGrabCtlId, GrabOSB[CycleParity = 0]);
	imBufPutField(NatSysThreadId, NatGrabCtlId, IM_CTL_SETUP, IM_VIA_ONLY);

	Locked = true;
	HoldCount = 0;
	return S_OK;
}

STDMETHODIMP CGenK66_1::Unlock()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!Locked) return S_FALSE;
	if (!Slots[0].pUnknown) return S_FALSE;
	IGenesis *iGe;
	if (Slots[0].pUnknown->QueryInterface(IID_IGenesis, (void **)&iGe) != S_OK) return S_FALSE;
	GenesisData *CG;
	if (iGe->LockInternalData((BYTE **)&CG) != S_OK)
	{
		iGe->Release();
		return S_FALSE;
		};
	iGe->Release();
	imThrHalt(NatGrabThreadId, IM_NOW);
	int i;
	for (i = 0; i < C.ZoneCount; i++)
	{
		imBufFree(NatSysThreadId, Children[i].NatBinChildBufId);
		imBufFree(NatSysThreadId, Children[i].NatConvChildBufId);
		};

	imBufFree(NatSysThreadId, NatBinBufId);
	imBufFree(NatSysThreadId, NatConvBufId);
	imBufFree(NatSysThreadId, NatGrabBufId[0]);
	imBufFree(NatSysThreadId, NatGrabBufId[1]);
	imBufFree(NatSysThreadId, NatGrabCtlId);
	imBufFree(NatSysThreadId, NatFIRKernelId);
   
	imSyncFree(NatGrabThreadId, GrabOSB[0]);
	imSyncFree(NatGrabThreadId, GrabOSB[1]);
	imSyncFree(NatSysThreadId, SysOSB);
	imThrFree(NatGrabThreadId);	

	MsysControl(CG->Sys, M_NATIVE_MODE_LEAVE, M_NULL);
	MbufControl(CG->GrabPage[CG->ActiveGrabPage], M_MODIFIED, M_DEFAULT);	

	MbufFree(HostBinBufId[0]);
	MbufFree(HostBinBufId[1]);

	CG->ExternalGrabData = 0;
	CG->pHoldFrame = 0;
	CG->pShowHeldFrame = 0;
	CG->pReleaseFrame = 0;	
	CG->pGetCurrentFrameGrabDelay = 0;
	CG->pFlushGrabBackBuffers = 0;

	Locked = false;
	return S_OK;
}

// Internal Functions

#define PACKED_CYCLE (32 / PACKED_BLOCK)
#define DUP_PACKED_BLOCK 0x00080008
#define DUP_PACKED_CYCLE 0x00200020

int CGenK66_1::GetSegments(BYTE *ScanLine, unsigned Length, Segment *SegSpace, PrecompSegmentBlock *PrecData)
{
	/* 
		REGISTERS USAGE 

		EAX		->	32 Pixels block read (current in AL)		
		EBX		->	Current scan position (dword pointer) + Current position (unsigned, step = 8)
		EDX		->	computation register (loaded with offsets)
		ECX		->	number of precomputed segments (1 byte), 
						number of in-block cycles  = 32 / PACKED_BLOCK (1 byte),
						remaining cycles								
		ESI		->	PrecData base pointer
		EDI		->	Current segment position (quadword pointer)

	*/

	int NumberOfSegments;
	unsigned short sLength = Length / 32;

	union
	{
		BYTE *pScanLine;
		unsigned DupCurrPos;
		} Buff;
	
	Buff.pScanLine = ScanLine;

// Init all registers
	_asm
	{				
				xor esi, esi
				mov edi, dword ptr [SegSpace]
				mov cx, word ptr [sLength]
				xor edx, edx				
				cld
		};

// Start a 4 byte cycle with no open segment (as at startup)
CW:	_asm
	{
				xchg esi, dword ptr [Buff]
				lodsd
				xchg esi, dword ptr [Buff]
				cmp eax, 0xFFFFFFFF
				jz ZD
				ror ecx, 16
				mov ch, PACKED_CYCLE
		};

// Start a single byte cycle with no open segment
SW:	_asm
	{
				cmp al,0xFF
				jz ZB
				movzx ebx,al
				shl ebx,5
				add ebx, dword ptr [PrecData]
				mov cl, byte ptr [ebx]
		};

// 8 bit loop for segments
PW:	_asm
	{
				add ebx, 4
				mov edx, dword ptr [ebx]
				add edx, esi
				mov dword ptr [edi], edx				
				xor edx, edx
				mov dword ptr [edi + 4], edx
				add edi, 8
				dec cl
				jnz PW
				test al,0x80
				jz S1	
				ror eax, 8				
				add esi, DUP_PACKED_BLOCK
				dec ch
				jnz SW
				ror ecx,16
				dec cx
				jnz CW
				jmp End
		};

// Shortcut for zero byte (WARNING! INVERTED LOGIC!)
ZB:	_asm
	{
				ror eax, 8
				add esi, DUP_PACKED_BLOCK
				dec ch
				jnz SW
				ror ecx, 16
				dec cx
				jnz CW
				jmp End
		};

// Shortcut for zero dword (WARNING! INVERTED LOGIC!)
ZD:	_asm
	{
				add esi, DUP_PACKED_CYCLE
				dec cx
				jnz CW
				jmp End
		};
				
// Branch to enter 1 byte loop with open segment
S1:	_asm
	{
				ror eax,8
				add esi, DUP_PACKED_BLOCK
				dec ch
				jnz SB
				ror ecx,16
				dec cx
				jnz CB
				jmp End
		};

// Start a 4 byte cycle with an open segment
CB:	_asm
	{
				xchg esi, dword ptr [Buff]
				lodsd
				xchg esi, dword ptr [Buff]
				cmp eax, 0xFFFFFFFF
				jz ZD
				ror ecx, 16
				mov ch, PACKED_CYCLE
		};

// Start a single byte cycle with an open segment
SB:	_asm
	{
				cmp al,0xFF
				jz ZB
				movzx ebx,al
				shl ebx,5
				add ebx, dword ptr [PrecData]
				mov cl, byte ptr [ebx]
				test al,1
				jnz PW
				add ebx,4
				mov edx, dword ptr [ebx]
				add edx, esi
				shr edx,16
				mov word ptr [edi - 6], dx
				dec cl
				jnz PW
				test al,0x80
				jz S1
				ror eax,8
				add esi, DUP_PACKED_BLOCK
				dec ch
				jnz SW
				ror ecx,16
				dec cx
				jnz CW
				jmp End
		};

End:	
	_asm
	{
				sub edi, dword ptr [SegSpace];
				shr edi, 3
				mov dword ptr [NumberOfSegments], edi
		};

	return NumberOfSegments;
	};

IntCluster *CGenK66_1::ChainSegments(Segment *Line1, Segment *Line2, unsigned short SegNum1,
	unsigned short SegNum2, unsigned short YLine, unsigned *PClusterNumber,
	IntCluster *NextFree)
{
	Segment *SegPointer1, *SegPointer2;
	Segment *SegEnd1, *SegEnd2, *Start1;
	IntCluster *ClusterPointer, *ClusterPointer2;
	unsigned int SegLength;
	unsigned int ClusterNumber = *PClusterNumber;
	unsigned int SX, XMax, XMin;	
	double XMaxD, XMinD;

	SegEnd1 = Line1 + SegNum1;
	SegEnd2 = Line2 + SegNum2;
	Start1 = Line1;
	for (SegPointer2 = Line2; (SegPointer2 < SegEnd2) && (NextFree); SegPointer2++)
	{  for (SegPointer1 = Start1; (SegPointer1 < SegEnd1) && (SegPointer2->Left > SegPointer1->Right); SegPointer1++);
		Start1 = SegPointer1;
		for (SegPointer1 = Start1; (SegPointer1 < SegEnd1) && (SegPointer2->Right >= SegPointer1->Left); SegPointer1++)
		{  if (!(SegPointer2->ClusterPointer))
			{	XMaxD = XMax = SegPointer2->Right + 1;
				XMinD = XMin = SegPointer2->Left;
				ClusterPointer = SegPointer2->ClusterPointer = SegPointer1->ClusterPointer;
				SegLength = XMax - XMin;
				ClusterPointer->Area += SegLength;
				ClusterPointer->YSum += YLine * SegLength;
				ClusterPointer->XSum += SX = (XMax * (XMax - 1) - XMin * (XMin - 1)) / 2;
				ClusterPointer->Inertia.IYY += YLine * YLine * SegLength;
				ClusterPointer->Inertia.IXY += YLine * SX;
				ClusterPointer->Inertia.IXX += (XMaxD * (1. + XMaxD * (3. + 2. * XMaxD)) - XMinD * (1. + XMinD * (3. + 2. * XMinD))) / 6.;
				}
			else
			{	ClusterPointer = SegPointer1->ClusterPointer;
				ClusterPointer2 = SegPointer2->ClusterPointer;
				if (ClusterPointer2 != ClusterPointer)
				{	ClusterPointer2->Area += ClusterPointer->Area;
					ClusterPointer2->XSum += ClusterPointer->XSum;
					ClusterPointer2->YSum += ClusterPointer->YSum;
					ClusterPointer2->Inertia.IXX += ClusterPointer->Inertia.IXX;
					ClusterPointer2->Inertia.IXY += ClusterPointer->Inertia.IXY;
					ClusterPointer2->Inertia.IYY += ClusterPointer->Inertia.IYY;
					Segment *Sweep;
					for (Sweep = Start1; Sweep < SegEnd1; Sweep++)
					{  if (Sweep->ClusterPointer == ClusterPointer)
							Sweep->ClusterPointer = ClusterPointer2;
						};
					for (Sweep = Line2; Sweep < SegPointer2; Sweep++)
					{  if (Sweep->ClusterPointer == ClusterPointer)
							Sweep->ClusterPointer = ClusterPointer2;
						};
					ClusterPointer->Area = 0;
					ClusterPointer->NextFree = NextFree;
					NextFree = ClusterPointer;
					ClusterNumber--;
					};
				};
			};
		if (!(SegPointer2->ClusterPointer))
		{  if (ClusterPointer = NextFree)
			{
				NextFree = ClusterPointer->NextFree;
				XMaxD = XMax = SegPointer2->Right + 1;
				XMinD = XMin = SegPointer2->Left;
				SegPointer2->ClusterPointer = ClusterPointer;
				SegLength = XMax - XMin;
				ClusterPointer->Area = SegLength;
				ClusterPointer->YSum = YLine * SegLength;
				ClusterPointer->XSum = SX = (XMax * (XMax - 1) - XMin * (XMin - 1)) / 2;
				ClusterPointer->Inertia.IYY = YLine * YLine * SegLength;
				ClusterPointer->Inertia.IXY = YLine * SX;
				ClusterPointer->Inertia.IXX = (XMaxD * (1. + XMaxD * (3. + 2. * XMaxD)) - XMinD * (1. + XMinD * (3. + 2. * XMinD))) / 6.;
				ClusterNumber++;
				};
			};
		};
	*PClusterNumber = ClusterNumber;
	return NextFree;
	};

IntBoundedCluster *CGenK66_1::ChainSegments(Segment *Line1, Segment *Line2, unsigned short SegNum1,
	unsigned short SegNum2, unsigned short YLine, unsigned *PClusterNumber,
	IntBoundedCluster *NextFree)
{
	Segment *SegPointer1, *SegPointer2;
	Segment *SegEnd1, *SegEnd2, *Start1;
	IntBoundedCluster *ClusterPointer, *ClusterPointer2;
	unsigned int SegLength;
	unsigned int ClusterNumber = *PClusterNumber;
	unsigned int SX, XMax, XMin;	
	double XMaxD, XMinD;

	SegEnd1 = Line1 + SegNum1;
	SegEnd2 = Line2 + SegNum2;
	Start1 = Line1;
	for (SegPointer2 = Line2; (SegPointer2 < SegEnd2) && (NextFree); SegPointer2++)
	{	
		for (SegPointer1 = Start1; (SegPointer1 < SegEnd1) && (SegPointer2->Left > SegPointer1->Right); SegPointer1++);
		Start1 = SegPointer1;
		for (SegPointer1 = Start1; (SegPointer1 < SegEnd1) && (SegPointer2->Right >= SegPointer1->Left); SegPointer1++)
		{  
			if (!(SegPointer2->BoundedClusterPointer))
			{	
				XMaxD = XMax = SegPointer2->Right + 1;
				XMinD = XMin = SegPointer2->Left;
				ClusterPointer = SegPointer2->BoundedClusterPointer = SegPointer1->BoundedClusterPointer;
				SegLength = XMax - XMin;
				if (ClusterPointer->BoundingBox.MinX > SegPointer2->Left) ClusterPointer->BoundingBox.MinX = SegPointer2->Left;
				if (ClusterPointer->BoundingBox.MaxX < SegPointer2->Right) ClusterPointer->BoundingBox.MaxX = SegPointer2->Right;
				ClusterPointer->Area += SegLength;
				ClusterPointer->YSum += (ClusterPointer->BoundingBox.MaxY = YLine) * SegLength;
				ClusterPointer->XSum += SX = (XMax * (XMax - 1) - XMin * (XMin - 1)) / 2;
				ClusterPointer->Inertia.IYY += YLine * YLine * SegLength;
				ClusterPointer->Inertia.IXY += YLine * SX;
				ClusterPointer->Inertia.IXX += (XMaxD * (1. + XMaxD * (3. + 2. * XMaxD)) - XMinD * (1. + XMinD * (3. + 2. * XMinD))) / 6.;
				}
			else
			{	
				ClusterPointer = SegPointer1->BoundedClusterPointer;
				ClusterPointer2 = SegPointer2->BoundedClusterPointer;
				if (ClusterPointer2 != ClusterPointer)
				{	
					ClusterPointer2->BoundingBox.MaxY = YLine;
					if (ClusterPointer2->BoundingBox.MinY > ClusterPointer->BoundingBox.MinY) ClusterPointer2->BoundingBox.MinY = ClusterPointer->BoundingBox.MinY;
					if (ClusterPointer2->BoundingBox.MinX > ClusterPointer->BoundingBox.MinX) ClusterPointer2->BoundingBox.MinX = ClusterPointer->BoundingBox.MinX;
					if (ClusterPointer2->BoundingBox.MaxX < ClusterPointer->BoundingBox.MaxX) ClusterPointer2->BoundingBox.MaxX = ClusterPointer->BoundingBox.MaxX;
					ClusterPointer2->Area += ClusterPointer->Area;
					ClusterPointer2->XSum += ClusterPointer->XSum;
					ClusterPointer2->YSum += ClusterPointer->YSum;
					ClusterPointer2->Inertia.IXX += ClusterPointer->Inertia.IXX;
					ClusterPointer2->Inertia.IXY += ClusterPointer->Inertia.IXY;
					ClusterPointer2->Inertia.IYY += ClusterPointer->Inertia.IYY;
					Segment *Sweep;
					for (Sweep = Start1; Sweep < SegEnd1; Sweep++)
					{  
						if (Sweep->BoundedClusterPointer == ClusterPointer)
							Sweep->BoundedClusterPointer = ClusterPointer2;
						};
					for (Sweep = Line2; Sweep < SegPointer2; Sweep++)
					{  
						if (Sweep->BoundedClusterPointer == ClusterPointer)
							Sweep->BoundedClusterPointer = ClusterPointer2;
						};
					ClusterPointer->Area = 0;
					ClusterPointer->NextFree = NextFree;
					NextFree = ClusterPointer;
					ClusterNumber--;
					};
				};
			};
		if (!(SegPointer2->BoundedClusterPointer))
		{  
			if (ClusterPointer = NextFree)
			{
				NextFree = ClusterPointer->NextFree;
				XMaxD = XMax = (ClusterPointer->BoundingBox.MaxX = SegPointer2->Right) + 1;
				XMinD = XMin = (ClusterPointer->BoundingBox.MinX = SegPointer2->Left);
				SegPointer2->BoundedClusterPointer = ClusterPointer;
				SegLength = XMax - XMin;
				ClusterPointer->Area = SegLength;
				ClusterPointer->YSum = (ClusterPointer->BoundingBox.MaxY = ClusterPointer->BoundingBox.MinY = YLine) * SegLength;
				ClusterPointer->XSum = SX = (XMax * (XMax - 1) - XMin * (XMin - 1)) / 2;
				ClusterPointer->Inertia.IYY = YLine * YLine * SegLength;
				ClusterPointer->Inertia.IXY = YLine * SX;
				ClusterPointer->Inertia.IXX = (XMaxD * (1. + XMaxD * (3. + 2. * XMaxD)) - XMinD * (1. + XMinD * (3. + 2. * XMinD))) / 6.;
				ClusterNumber++;
				};
			};
		};
	*PClusterNumber = ClusterNumber;
	return NextFree;
	};

DWORD CGenK66_1::GetClusters(BYTE *ImageBuffer, PrecompSegmentBlock *PrecompData, Cluster *pSpace, int *pMaxNumber, 
	unsigned short Width, unsigned short Height, unsigned short OffX, unsigned short OffY, unsigned short WinWidth, 
	unsigned short WinHeight)
{
	if ((!(SegPointer1)) || (!(SegPointer2)))
	{
		*pMaxNumber = 0;
		return S_FALSE;
		};
	unsigned int ClusterCount = 0;
	unsigned int TempClusterCount;
	unsigned short int YLine;
	Segment *SegmentArray[2];
	Segment *SegSwap;
	unsigned short int SegNum[2];
	IntCluster *ClusterScan, *ClusterEnd, *NextFree, *Dummy;
	float Area;
	int MaxNumber = *pMaxNumber;

	byte *LineBuffer;

	ClusterEnd = ((IntCluster *)pSpace) + MaxNumber - 1;
	for (ClusterScan = ((IntCluster *)pSpace); ClusterScan < ClusterEnd; ClusterScan++)
	{  
		ClusterScan->Area = 0;
		ClusterScan->NextFree = ClusterScan + 1;
		};
	ClusterEnd->Area = 0;
	ClusterEnd->NextFree = 0;
	NextFree = (IntCluster *)pSpace;

	SegmentArray[0] = SegPointer1;
	SegmentArray[1] = SegPointer2;
	SegNum[0] = 0;	
	LineBuffer = ImageBuffer + (Width*(unsigned int)OffY + OffX) / PACKED_BLOCK;
	for (YLine = 0; (YLine < WinHeight) && (NextFree); YLine++)
	{  
		SegNum[1] = GetSegments(LineBuffer, WinWidth, SegmentArray[1], PrecompData);
		NextFree = ChainSegments(SegmentArray[0], SegmentArray[1], SegNum[0],
			SegNum[1], YLine, &ClusterCount, NextFree);
		SegSwap = SegmentArray[0];
		SegmentArray[0] = SegmentArray[1];
		SegmentArray[1] = SegSwap;
		SegNum[0] = SegNum[1];
		LineBuffer += Width / PACKED_BLOCK;
		};

	if (!NextFree) 
	{
		*pMaxNumber = -1;
		return S_FALSE;
		};
	TempClusterCount = 0;
	for (ClusterScan = ((IntCluster *)pSpace); TempClusterCount < ClusterCount; ClusterScan++)
	{	if (ClusterScan->Area)
		{  	Area = ClusterScan->Area;
			ClusterScan->X = ((float)ClusterScan->XSum) / Area;
			ClusterScan->Y = ((float)ClusterScan->YSum) / Area;
			ClusterScan->Inertia.IXY = Area * ClusterScan->X++ * ClusterScan->Y - ClusterScan->Inertia.IXY;
			ClusterScan->Inertia.IXX -= Area * ClusterScan->X * ClusterScan->X;
			ClusterScan->Inertia.IYY -= Area * ClusterScan->Y * ClusterScan->Y;
			ClusterScan->X += OffX;
			ClusterScan->Y += OffY;
			ClusterScan->GrayLevel = ((float)(ClusterScan->GrayLevelSum)) / Area;
			TempClusterCount++;
			};
		};
	ClusterEnd = ((IntCluster *)pSpace + ClusterCount);
	for (ClusterScan = Dummy = (IntCluster *)pSpace; ClusterScan < ClusterEnd;)
		if (Dummy->Area)
		{  *ClusterScan++ = *Dummy++; }
		else
		{  Dummy++; };
	*pMaxNumber = ClusterCount;
/*	WARNING: ACCESS TO PRIMARY IMAGE IS NOT SUPPORTED 
	if (pBinaryImage)
	{
		LineBuffer = pImage;
		unsigned char *DestBuffer = pBinaryImage;
		if (EnableEq)
			for (YLine = 0; YLine < CamSpec.Height; YLine++)
			{
				unsigned char LineThreshold = (unsigned char)Threshold - (unsigned char)LightBias[YLine];
				unsigned char *LineEnd = pImage + (YLine + 1) * Width;
				while (LineBuffer < LineEnd)
					*DestBuffer++ = ((unsigned char)*LineBuffer++ > LineThreshold) ? 255 : 0;
				}
			else
				for (YLine = 0; YLine < CamSpec.Height; YLine++)
				{
					unsigned char LineThreshold = (unsigned char)Threshold;
					unsigned char *LineEnd = pImage + (YLine + 1) * Width;
					while (LineBuffer < LineEnd)
						*DestBuffer++ = ((unsigned char)*LineBuffer++ > LineThreshold) ? 255 : 0;
					};
		};
*/	return S_OK;
	};

DWORD CGenK66_1::GetBoundedClusters(BYTE *ImageBuffer, PrecompSegmentBlock *PrecompData, BoundedCluster *pSpace, int *pMaxNumber, 
	unsigned short Width, unsigned short Height, unsigned short OffX, unsigned short OffY, unsigned short WinWidth, 
	unsigned short WinHeight)
{
	if ((!(SegPointer1)) || (!(SegPointer2)))
	{
		*pMaxNumber = 0;
		return S_FALSE;
		};
	unsigned int ClusterCount = 0;
	unsigned int TempClusterCount;
	unsigned short int YLine;
	Segment *SegmentArray[2];
	Segment *SegSwap;
	unsigned short int SegNum[2];
	IntBoundedCluster *ClusterScan, *ClusterEnd, *NextFree, *Dummy;
	float Area;
	int MaxNumber = *pMaxNumber;

	byte *LineBuffer;

	ClusterEnd = ((IntBoundedCluster *)pSpace) + MaxNumber - 1;
	for (ClusterScan = ((IntBoundedCluster *)pSpace); ClusterScan < ClusterEnd; ClusterScan++)
	{  
		ClusterScan->Area = 0;
		ClusterScan->NextFree = ClusterScan + 1;
		};
	ClusterEnd->Area = 0;
	ClusterEnd->NextFree = 0;
	NextFree = (IntBoundedCluster *)pSpace;

	SegmentArray[0] = SegPointer1;
	SegmentArray[1] = SegPointer2;
	SegNum[0] = 0;	
	LineBuffer = ImageBuffer + (Width*(unsigned int)OffY + OffX) / PACKED_BLOCK;
	for (YLine = 0; (YLine < WinHeight) && (NextFree); YLine++)
	{  
		SegNum[1] = GetSegments(LineBuffer, WinWidth, SegmentArray[1], PrecompData);
		NextFree = ChainSegments(SegmentArray[0], SegmentArray[1], SegNum[0],
			SegNum[1], YLine, &ClusterCount, NextFree);
		SegSwap = SegmentArray[0];
		SegmentArray[0] = SegmentArray[1];
		SegmentArray[1] = SegSwap;
		SegNum[0] = SegNum[1];
		LineBuffer += Width / PACKED_BLOCK;
		};

	if (!NextFree) 
	{
		*pMaxNumber = -1;
		return S_FALSE;
		};
	TempClusterCount = 0;
	for (ClusterScan = ((IntBoundedCluster *)pSpace); TempClusterCount < ClusterCount; ClusterScan++)
	{	if (ClusterScan->Area)
		{  	Area = ClusterScan->Area;
			ClusterScan->X = ((float)ClusterScan->XSum) / Area;
			ClusterScan->Y = ((float)ClusterScan->YSum) / Area;
			ClusterScan->Inertia.IXY = Area * ClusterScan->X++ * ClusterScan->Y - ClusterScan->Inertia.IXY;
			ClusterScan->Inertia.IXX -= Area * ClusterScan->X * ClusterScan->X;
			ClusterScan->Inertia.IYY -= Area * ClusterScan->Y * ClusterScan->Y;
			ClusterScan->X += OffX;
			ClusterScan->Y += OffY;
			ClusterScan->BoundingBox.MinX += OffX;
			ClusterScan->BoundingBox.MaxX += OffX;
			ClusterScan->BoundingBox.MinY += OffY;
			ClusterScan->BoundingBox.MaxY += OffY;
			ClusterScan->GrayLevel = ((float)(ClusterScan->GrayLevelSum)) / Area;
			TempClusterCount++;
			};
		};
	ClusterEnd = ((IntBoundedCluster *)pSpace + ClusterCount);
	for (ClusterScan = Dummy = (IntBoundedCluster *)pSpace; ClusterScan < ClusterEnd;)
		if (Dummy->Area)
		{  *ClusterScan++ = *Dummy++; }
		else
		{  Dummy++; };
	*pMaxNumber = ClusterCount;
	return S_OK;
	};

BYTE *CGenK66_1::cgenk66HoldFrame(void *data)
{
	CGenK66_1 *C = (CGenK66_1 *)data;
	if (!(C->Locked)) return 0;

	imDigGrab(C->NatGrabThreadId, C->NatDigId, C->NatDigCameraId, C->NatGrabBufId[C->CycleParity ^ 1], 1L, C->NatGrabCtlId, C->GrabOSB[C->CycleParity ^ 1]);
	imSyncHost(C->NatGrabThreadId, C->GrabOSB[C->CycleParity], IM_COMPLETED);
	imIntConvolve(C->NatSysThreadId, C->NatGrabBufId[C->CycleParity], C->NatConvBufId, C->NatFIRKernelId, IM_FAST, 0);
	int i;
	for (i = 0; i < C->C.ZoneCount; i++)
		imBinConvert(C->NatSysThreadId, C->Children[i].NatConvChildBufId, C->Children[i].NatBinChildBufId, IM_LESS, C->CutOff - C->C.ThresholdZones[i].Eq, 0, 0);
	imBufCopyPCI(C->NatSysThreadId, C->NatBinBufId, C->NatHostBinBufId[C->CycleParity], 0, C->SysOSB);
	
	if (C->HoldCount < 0) C->HoldCount = 1;
	else C->HoldCount++;
	return C->HostBinBuf[C->CycleParity ^ 1];	
	};

DWORD CGenK66_1::cgenk66ShowHeldFrame(void *data)
{		
	CGenK66_1 *C = (CGenK66_1 *)data;
	if (!(C->Locked)) return S_FALSE;
	imBufCopy(C->NatSysThreadId, C->NatGrabBufId[C->CycleParity], C->NatBufId, 0, 0);
	return S_OK;
	};

DWORD CGenK66_1::cgenk66ReleaseFrame(void *data)
{
	CGenK66_1 *C = (CGenK66_1 *)data;
	if (C->HoldCount <= 0) 
	{
		C->HoldCount = 0;
		return S_FALSE;
		};
	C->HoldCount--;
	if (!(C->Locked)) return S_FALSE;
//	imSyncHost(C->NatSysThreadId, C->SysOSB, IM_COMPLETED);
//	imSyncHost(C->NatGrabThreadId, C->GrabOSB[C->CycleParity], IM_COMPLETED);
	C->CycleParity ^= 1;
	return S_OK;
	};

DWORD CGenK66_1::cgenk66GetCurrentFrameGrabDelay(void *data)
{	return 3; };

DWORD CGenK66_1::cgenk66FlushGrabBackBuffers(void *data)
{	
	CGenK66_1 *C = (CGenK66_1 *)data;
	cgenk66HoldFrame(data);
	cgenk66ReleaseFrame(data);
	cgenk66HoldFrame(data);
	cgenk66ReleaseFrame(data);
	cgenk66HoldFrame(data);
	cgenk66ReleaseFrame(data);
	return S_OK;
	};

#include "Genesis_i.c"
#include "Config2.cpp"

bool CGenK66_1::ReadThresholdBuffer(SySalConfig *pC, int buffindex, ConfigData::t_ThresholdZone &Z)
{
	int i;
	char entryname[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	sprintf(entryname, "ThresholdZone_%02X", buffindex);
	for (i = 0; i < pC->CountOfItems; i++)
	{
		if (!strncmp(pC->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), entryname, SYSAL_MAXCONFIG_ENTRY_NAME_LEN))
		{
			if (sscanf(pC->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN,
				"%4X%4X%4X%4X%4X", &Z.Left, &Z.Top, &Z.Width, &Z.Height, &Z.Eq) == 5)
			{
				Z.Eq = (int)(short)Z.Eq;
				return true;
				}
			else return false;
			}
		}
	return false;
}

void CGenK66_1::WriteThresholdBuffer(SySalConfig *pC, int buffindex, ConfigData::t_ThresholdZone Z)
{
	sprintf(pC->pItems + buffindex * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), "ThresholdZone_%02X", buffindex);
	sprintf(pC->pItems + buffindex * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN,
		"%04X%04X%04X%04X%04X", Z.Left, Z.Top, Z.Width, Z.Height, Z.Eq);
}

HRESULT CGenK66_1::WriteConfig(SySalConfig *pConfig, ConfigData &C)
{
	if (PutData(*pConfig, ConfigDataN, ConfigDataQDI, &C) != ConfigDataN) return S_FALSE;
	char *p = (char *)CoTaskMemAlloc((ConfigDataN + C.ZoneCount) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	if (pConfig->pItems)
	{
		memcpy(p, pConfig->pItems, ConfigDataN * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		CoTaskMemFree(pConfig->pItems);
		};
	pConfig->pItems = p;
	int i;
	for (i = 0; i < C.ZoneCount; i++)
		WriteThresholdBuffer(pConfig, i + ConfigDataN, C.ThresholdZones[i]);
	pConfig->CountOfItems = ConfigDataN + C.ZoneCount;	
	return S_OK;
	
}
