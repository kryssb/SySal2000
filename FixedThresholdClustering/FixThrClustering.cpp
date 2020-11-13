// FixThrClustering.cpp : Implementation of CFixThrClustering
#include "stdafx.h"
#include "FixedThresholdClustering.h"
#include "FixThrClustering.h"

/////////////////////////////////////////////////////////////////////////////
// CFixThrClustering

// ISySalObject
STDMETHODIMP CFixThrClustering::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFixThrClustering::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFixThrClustering::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFixThrClustering::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	//	return S_OK;
	return E_NOTIMPL;
}

STDMETHODIMP CFixThrClustering::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here

	//	return S_OK;
	return E_NOTIMPL;
}

STDMETHODIMP CFixThrClustering::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CFixThrClustering::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CFixThrClustering::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CFixThrClustering::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CFixThrClustering::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CFixThrClustering::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Fixed Threshold ClusterFinder", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFixThrClustering::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CFixThrClustering::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CFixThrClustering::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CFixThrClustering::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFixThrClustering::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CFixThrClustering::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CFixThrClustering::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CFixThrClustering::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

// IClusterFinder
STDMETHODIMP CFixThrClustering::EnableImageEqualization(boolean bEnable)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	
	EnableEq = bEnable;
	return S_OK;
}

STDMETHODIMP CFixThrClustering::EnableShapeParameters(boolean bEnable)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!bEnable) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CFixThrClustering::EnableGrayLevel(boolean bEnable)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!bEnable) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CFixThrClustering::GetClusters(BYTE *pImage, Cluster *pSpace, int *pMaxNumber, BYTE Threshold, BYTE *pBinaryImage)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!(this->LightBias) || (!(SegPointer1)) || (!(SegPointer2)))
	{
		*pMaxNumber = 0;
		return S_FALSE;
		};
	byte *LightBias = this->LightBias;
	unsigned short Width = CamSpec.Width;
	unsigned short Height = CamSpec.Height;
	unsigned short OffX = CamSpec.OffX;
	unsigned short OffY = CamSpec.OffY;
	unsigned short WinWidth = CamSpec.WinWidth;
	unsigned short WinHeight = CamSpec.WinHeight;
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
	LineBuffer = pImage + Width * (unsigned int)OffY + OffX;
	if (EnableEq)
		for (YLine = 0; (YLine < WinHeight) && (NextFree); YLine++)
		{  
			SegNum[1] = GetSegments(LineBuffer, WinWidth, SegmentArray[1], (WORD)Threshold - (WORD)LightBias[YLine + OffY]);
			NextFree = ChainSegments(SegmentArray[0], SegmentArray[1], SegNum[0], SegNum[1], YLine, LightBias[YLine+OffY], &ClusterCount, NextFree);
			SegSwap = SegmentArray[0];
			SegmentArray[0] = SegmentArray[1];
			SegmentArray[1] = SegSwap;
			SegNum[0] = SegNum[1];
			LineBuffer += Width;
			}
	else
		for (YLine = 0; (YLine < WinHeight) && (NextFree); YLine++)
		{  
			SegNum[1] = GetSegments(LineBuffer, WinWidth, SegmentArray[1], (WORD)Threshold);
			NextFree = ChainSegments(SegmentArray[0], SegmentArray[1], SegNum[0], SegNum[1], YLine, 0, &ClusterCount, NextFree);
			SegSwap = SegmentArray[0];
			SegmentArray[0] = SegmentArray[1];
			SegmentArray[1] = SegSwap;
			SegNum[0] = SegNum[1];
			LineBuffer += Width;
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
	return S_OK;
}

STDMETHODIMP CFixThrClustering::GetGrayLevelStatus(boolean *pReturn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pReturn = true;
	return S_OK;
}

STDMETHODIMP CFixThrClustering::GetImageEqualizationStatus(boolean *pReturn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pReturn = EnableEq;
	return S_OK;
}

STDMETHODIMP CFixThrClustering::GetShapeParametersStatus(boolean *pReturn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pReturn = true;
	return S_OK;
}

STDMETHODIMP CFixThrClustering::SetCameraSpec(CameraSpec Spec)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (Spec.Width <= 0 || Spec.Height <= 0 || Spec.WinWidth <= 0 || Spec.WinHeight <= 0 ||
		Spec.PixelToMicronX == 0.f || Spec.PixelToMicronY == 0.f) return E_INVALIDARG;
	CamSpec = Spec;
	if (LightBias) delete [] LightBias;
	LightBias = new BYTE[CamSpec.Height];
	ResetLightBias();
	if (SegPointer1) delete [] SegPointer1;
	if (SegPointer2) delete [] SegPointer2;
	SegPointer1 = new Segment[CamSpec.WinWidth];
	SegPointer2 = new Segment[CamSpec.WinWidth];
	return S_OK;
}

STDMETHODIMP CFixThrClustering::GetCameraSpec(CameraSpec *pSpec)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pSpec = CamSpec;
	return S_OK;
}

STDMETHODIMP CFixThrClustering::MakeEqualization(BYTE *pImage, BYTE *pRefLevel)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	BYTE *LightBias = this->LightBias;
	int Width = CamSpec.Width;
	int Height = CamSpec.Height;

	int i;
	int GrayLevel;
	BYTE Max = 0;
	BYTE *Scan, *End;
	for (i = 0; i < Height; i++)
	{  
		GrayLevel = 0;
		End = pImage + (i + 1) * Width;
		for (Scan = pImage + i * Width; Scan < End; GrayLevel += *Scan++);
		GrayLevel /= Width;
		if (GrayLevel > Max) Max = GrayLevel;
		LightBias[i] = GrayLevel;
		};
	for (i = 0; i < Height; i++)
	{	LightBias[i] = Max - LightBias[i];  };
	*pRefLevel = Max;
	return S_OK;
}

// INTERNAL FUNCTIONS

unsigned short CFixThrClustering::GetSegments(BYTE *ScanLine, unsigned short Len, Segment *SegmentArray, WORD Threshold)
{
	// Precomputed optimization constants

	int NumberOfSegments = 0;
	byte *ScanLine1 = ScanLine+1;
	byte *ScanLine2 = ScanLine+2;
	byte *ScanLine3 = ScanLine+3;
	byte *ScanLine4 = ScanLine+4;
	byte *ScanLine5 = ScanLine+5;

		/* REGISTERS USAGE:

				ESI -> Scanning position on the video buffer
				ECX -> End position on the video buffer
				EDI -> Pointer to the next segment to be formed
				EDX -> Temporary - also used for total gray level in the current segment
				BL  -> Threshold value
				EAX -> 4-pixel gray levels read from buffer
		*/

	_asm {	
				cld
				mov esi,dword ptr [ScanLine]
				movzx ecx,word ptr [Len] 
				add ecx,esi
				mov edi,dword ptr [SegmentArray]
				mov bx,word ptr [Threshold]
				};

LdW:	
	_asm {	
				cmp esi,ecx
				jae End
				lodsd
				jmp Wht0
				};

LdB:	
	_asm {	
				cmp esi,ecx
				jae TrS
				lodsd
				jmp Blk0
				};

Wht0:	
	_asm { 
				cmp al,bl
				ja Wht1
				mov edx,esi
				sub edx,dword ptr [ScanLine4]
				mov word ptr [edi+4],dx
				xor edx,edx
				mov dword ptr [edi],edx
				movzx edx,al
				jmp Blk1
				};

Blk0:	
	_asm { 
				cmp al,bl
				ja ClS0
				add dl,al
				jnc Blk1
				add edx,0x100
				jmp Blk1
				};

ClS0:	
	_asm { 
				mov dword ptr [edi+8],edx
				mov edx,esi
				sub edx,dword ptr [ScanLine5]
				mov word ptr [edi+6],dx
				add edi,12
				};

Wht1:	
	_asm { 
				cmp ah,bl
				ja Wht2
				mov edx,esi
				sub edx,dword ptr [ScanLine3]
				mov word ptr [edi+4],dx
				xor edx,edx
				mov dword ptr [edi],edx
				movzx edx,ah
				jmp Blk2
				};

Blk1:	
	_asm { 
				cmp ah,bl
				ja ClS1
				add dl,ah
				jnc Blk2
				add edx,0x100
				jmp Blk2
				};

ClS1:	
	_asm { 
				mov dword ptr [edi+8],edx
				mov edx,esi
				sub edx,dword ptr [ScanLine4]
				mov word ptr [edi+6],dx
				add edi,12
				};

Wht2:	
	_asm { 
				shr eax,16
				cmp al,bl
				ja Wht3
				mov edx,esi
				sub edx,dword ptr [ScanLine2]
				mov word ptr [edi+4],dx
				xor edx,edx
				mov dword ptr [edi],edx
				movzx edx,al
				jmp Blk3
				};

Blk2:	
	_asm { 
				shr eax,16
				cmp al,bl
				ja ClS2
				add dl,al
				jnc Blk3
				add edx,0x100
				jmp Blk3
				};

ClS2:	
	_asm { 
				mov dword ptr [edi+8],edx
				mov edx,esi
				sub edx,dword ptr [ScanLine3]
				mov word ptr [edi+6],dx
				add edi,12
				};

Wht3:	
	_asm { 
				cmp ah,bl
				ja LdW
				mov edx,esi
				sub edx,dword ptr [ScanLine1]
				mov word ptr [edi+4],dx
				xor edx,edx
				mov dword ptr [edi],edx
				movzx edx,ah
				jmp LdB
				};

Blk3:	
	_asm { 
				cmp ah,bl
				ja ClS3
				add dl,ah
				jnc LdB
				add edx,0x100
				jmp LdB
				};

ClS3:	
	_asm { 
				mov dword ptr [edi+8],edx
				mov edx,esi
				sub edx,dword ptr [ScanLine2]
				mov word ptr [edi+6],dx
				add edi,12
				jmp LdW
				};

TrS:	
	_asm { 
				mov dword ptr [edi+8],edx
				mov edx,esi
				sub edx,dword ptr [ScanLine1]
				mov word ptr [edi+6],dx
				add edi,12
				};

End:	
	_asm { 
				mov eax,edi
				sub eax,dword ptr [SegmentArray]
				xor edx,edx
				mov ebx,12
				div ebx
				mov dword ptr [NumberOfSegments], eax
				};

	return NumberOfSegments;
}

IntCluster *CFixThrClustering::ChainSegments(Segment *Line1, Segment *Line2, unsigned short SegNum1,
	unsigned short SegNum2, unsigned short YLine, int LightBias, unsigned *PClusterNumber,
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
			{  XMaxD = XMax = SegPointer2->Right + 1;
				XMinD = XMin = SegPointer2->Left;
				ClusterPointer = SegPointer2->ClusterPointer = SegPointer1->ClusterPointer;
				SegLength = XMax - XMin;
				ClusterPointer->Area += SegLength;
				ClusterPointer->YSum += YLine * SegLength;
				ClusterPointer->XSum += SX = (XMax * (XMax - 1) - XMin * (XMin - 1)) / 2;
				ClusterPointer->Inertia.IYY += YLine * YLine * SegLength;
				ClusterPointer->Inertia.IXY += YLine * SX;
				ClusterPointer->Inertia.IXX += (XMaxD * (1. + XMaxD * (3. + 2. * XMaxD)) - XMinD * (1. + XMinD * (3. + 2. * XMinD))) / 6.;
				ClusterPointer->GrayLevelSum += SegPointer2->GrayLevel + SegLength * LightBias;
				}
			else
			{  ClusterPointer = SegPointer1->ClusterPointer;
				ClusterPointer2 = SegPointer2->ClusterPointer;
				if (ClusterPointer2 != ClusterPointer)
				{  ClusterPointer2->Area += ClusterPointer->Area;
					ClusterPointer2->XSum += ClusterPointer->XSum;
					ClusterPointer2->YSum += ClusterPointer->YSum;
					ClusterPointer2->Inertia.IXX += ClusterPointer->Inertia.IXX;
					ClusterPointer2->Inertia.IXY += ClusterPointer->Inertia.IXY;
					ClusterPointer2->Inertia.IYY += ClusterPointer->Inertia.IYY;
					ClusterPointer2->GrayLevelSum += ClusterPointer->GrayLevelSum;
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
				ClusterPointer->GrayLevelSum = SegPointer2->GrayLevel + SegLength * LightBias;
				ClusterNumber++;
				};
			};
		};
	*PClusterNumber = ClusterNumber;
	return NextFree;
	};

void CFixThrClustering::ResetLightBias()
{
	int i;
	for (i = 0; i < CamSpec.Height; LightBias[i++] = 0);
}
