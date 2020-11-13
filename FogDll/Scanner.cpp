// Scanner.cpp: implementation of the CScanner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FogDLL.h"
#include "Scanner.h"
#include "ScannerManagerDlg.h"
#include "FileInfoDlg.h"
#include "DistortionDlg.h"
#include <sys/timeb.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

SFogInit * pFogInit = NULL;
extern void ShowInfoDlg();
SMicroParameters * pGlobalMicroParameters;
char BitmapHeader[54] = {	0x42,0x4d,0x36,0x04,	0x14,0x00,0x00,0x00,	0x00,0x00,0x36,0x04,
	0x00,0x00,0x28,0x00,	0x00,0x00,0x00,0x05,	0x00,0x00,0x00,0x04,	0x00,0x00,0x01,0x00,
	0x08,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,	0x00,0x00,0x10,0x27,	0x00,0x00,0x10,0x27,
	0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,	0x00,0x00};
bool ScanningAvailable = true;
#ifdef FOG_HOME
CScanner::CScanner(SScannerContext * pContext):m_ScanContext(*pContext)
{
	int Width = 1280,Length = 1024;
	m_NumberOfImages = 0;
//	m_ScanningInProgress = false;
	int result = MessageBox(NULL,"Select Yes to allocate space for Image Files.","Scanner",MB_YESNO);
	if(result == IDYES)
	{
		m_pGlobalBytes1 = (BYTE *)GlobalAlloc(GMEM_FIXED, MAX_NUMBER_OF_IMAGES * Width * Length); 
		MaxNumberOfImages = MAX_NUMBER_OF_IMAGES;
	}
	else 
	{
		m_pGlobalBytes1 = NULL;
		MaxNumberOfImages = 0;
	}
	m_ScanContext.pGrainFinder->m_pImageData = m_pGlobalBytes1;
	mScanViewStruct1.NumberOfImages = 0;
}

void CScanner::Initialization()
{
	m_ScanContext.pGrainFinder->GFC.pGFTParam->Options |= FOG_OPT_GLOBALBYTES;
}
#endif

void CScanner::Allocator(bool Alloc)
{
	if(Alloc && GlobalYetAllocated);
	else if(!GlobalYetAllocated && Alloc)
	{
		int Width = m_ScanContext.pGrainFinder->GFC.pMicPar->HalfCCDWidth * 2;
		int Length = m_ScanContext.pGrainFinder->GFC.pMicPar->HalfCCDLength * 2;
		mXWidth = Width;
		mYWidth = Length;
		m_pGlobalBytes1 = (BYTE *)GlobalAlloc(GMEM_FIXED, MAX_NUMBER_OF_IMAGES * Width * Length);
		if(m_pGlobalBytes1)MaxNumberOfImages = MAX_NUMBER_OF_IMAGES;
		else MaxNumberOfImages = 0;
		m_ScanContext.pGrainFinder->m_pImageData = m_pGlobalBytes1;
		GlobalYetAllocated = m_pGlobalBytes1 != NULL;
		mScanViewStruct1.pGlobalBytes = m_pGlobalBytes1;
	}
	else if(GlobalYetAllocated && !Alloc)
	{
		GlobalFree(m_pGlobalBytes1);
		m_pGlobalBytes1 = NULL;
		m_ScanContext.pGrainFinder->m_pImageData = NULL;
		MaxNumberOfImages = 0;
		GlobalYetAllocated = false;
	}
	else if(!GlobalYetAllocated && !Alloc);
}

CScanner::~CScanner()
{
	if(m_pFirstScanPoint)delete m_pFirstScanPoint;
	Allocator(false);
}

#ifndef FOG_HOME
#include <objbase.h>
#include <windows.h>


extern void (* pWriteLog)(const char *pFile,const char *PText);
CString ScanLogFilePath ="C:\\SySal2000\\Fog2000\\Data\\LogTimes.txt";
CString LogText;
void WriteLog(const char * pText)
{
	pWriteLog(ScanLogFilePath,pText);
};
//	FILE * Out = fopen("C:\\Opera\\DiffTime.txt","a");
void LogWriteTime(CString &Text)
{
/*	CString TempText;
	_timeb LocalTime;
	_ftime(&LocalTime);
	static time_t OldTime = LocalTime.time;
	static ULONG OldMillSec = LocalTime.millitm;
	static ULONG LastMillSec = OldMillSec;
	time_t	ActualTime = LocalTime.time;
	ULONG ActualMillSec = LocalTime.millitm;
	ULONG seconds = ActualTime - OldTime;
	ULONG DiffTime = seconds*1000 + (ActualMillSec - OldMillSec);
	ULONG DeltaTime = DiffTime - LastMillSec;
	TempText.Format("%s\t%d\t%d",Text,DiffTime,DeltaTime);
	LastMillSec = DiffTime;
	Text = TempText;
	WriteLog(Text);*/
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScanner::CScanner(SScannerContext * pContext):m_ScanContext(*pContext),m_Mover(&m_ScanningParam,ShowGrid)
,m_NumberOfImages(mScanViewStruct1.NumberOfImages)
, m_bShouldStop(false)
{
	pFogInit = pContext->pFogInit;
	m_Mover.pFogInit = pContext->pFogInit;
	Opera.SideDw = 0;
	Opera.SideDwFogDensity = 0;
	Opera.SideDwLight = 0;
	Opera.SideDwMaxZ = 0;
	Opera.SideDwMinZ = 0;
	Opera.SideUp = 0;
	Opera.SideUpFogDensity = 0;
	Opera.SideUpLight = 0;
	Opera.SideUpMaxZ = 0;
	Opera.SideUpMinZ = 0;
	Opera.XStage = 0;
	Opera.YStage = 0;
	ScanningAvailable = pContext->pFogInit->ScanningAvailable;
	GlobalYetAllocated = false;
}



bool CScanner::FindStartingZeta(SScanView * pScanView,float & maxz)
{
	float StartingZ,ExpectedZeta,CurrentZeta,Step = 5.f;
	m_Mover.GetZeta(StartingZ);
	int NumberOfGrains = 0,worker = 0,MaxGrains = 0,MinGrains = 200000;
	int RefLight = 235;
	SetLight(RefLight,true);
	BYTE ** pGrainsPointers,* pImage;
	int MaxDownStepZeta = 120,MinNumberOfGrains,i;
	int FindCounter = 0,NullStepCounter = 0;
	float LastPosition = StartingZ;
	for(MinNumberOfGrains = 200; NumberOfGrains < MinNumberOfGrains; MinNumberOfGrains = (MaxGrains - MinGrains)/2)
	{	FindCounter++;
		for(i = 1;NumberOfGrains < MinNumberOfGrains && i < MaxDownStepZeta; i++)
		{
			if(m_bShouldStop)
			{
				m_Mover.MoveZTo(StartingZ);
				return false;
			}
			pFogInit->iFG->FreezeFrame(&pImage);
			Sleep(20);
			m_Mover.MoveZTo(StartingZ - Step*i,500);
			m_Mover.UpdateZeta();
			m_Mover.GetZeta(CurrentZeta);
			ExpectedZeta = StartingZ - i*Step;
			if((float)fabs(CurrentZeta - LastPosition) < 0.1f)NullStepCounter++;
			else NullStepCounter = 0;
			LastPosition = CurrentZeta;
			if(NullStepCounter == 10)
			{
				m_Mover.MoveZTo(StartingZ,500);
				maxz = StartingZ;
				return false;
			}
			pGrainsPointers = pScanView->pGrainFinder->ComputeSingleFrame(pImage,1280,1024,20,300);
			for(NumberOfGrains = 0; NumberOfGrains < 1024; NumberOfGrains++)if(*(pGrainsPointers + NumberOfGrains) == NULL)break;
			if(MaxGrains < NumberOfGrains)MaxGrains = NumberOfGrains;
			if(MinGrains > NumberOfGrains)MinGrains = NumberOfGrains;
			Sleep(5);
		}
		if(i == MaxDownStepZeta)
		{/*	if((FindCounter % 3)==0)
			{
				iSt->PosMove(2,StartingZ + 2000,600,500);
				m_Z = StartingZ + 2000;
				Sleep(Step*MaxDownStepZeta*2 + 300);
				MaxDownStepZeta += 250;
			}
			else
			{	iSt->PosMove(2,StartingZ,600,500);
				m_Z = StartingZ;
				Sleep(Step*MaxDownStepZeta*2 + 300);}	}*/	}
	}
	float ConfidenceStep = 15.f;
	m_Mover.MoveZTo(CurrentZeta + ConfidenceStep);
	Sleep(50);
	m_Mover.UpdateZeta();
	m_Mover.GetZeta(CurrentZeta);
	maxz = CurrentZeta;
	return true;
}

void CScanner::Initialization()
{
	pGlobalMicroParameters = m_ScanContext.pGrainFinder->GFC.pMicPar;
	Allocator(true);
	mWidthCounter = 0;
	m_EmulsionWidth = 0.f;
	mRepeat1.XStage = 0.f;
	mRepeat1.YStage = 0.f;
	mRepeat1.MaxZeta = 0.f;
	mRepeat1.pIdentifier = NULL;
	mbRepeat = false;
	ScanningLogFile = "C:\\SySal2000\\Fog2000\\Debug\\ScanningLog.dat";
	
	int test;
	mScanViewStruct1.MaxZ = 0;
	mScanViewStruct1.MinZ = 0;
	mScanViewStruct1.NumberOfImages = 0;
	mScanViewStruct1.pGrainFinder = m_ScanContext.pGrainFinder;
	mScanViewStruct1.pScanner = this;
	mScanViewStruct1.pThread = NULL;
	mScanViewStruct1.IspThreadValid = false;
	mScanViewStruct1.Identifier = 1;
	mScanViewStruct1.ZSearchRange = 0.0f;
	test = mScanViewStruct1.ScanningStarted.ResetEvent();
	test = mScanViewStruct1.DataComputed.SetEvent();
	test = mScanViewStruct1.StartedComputing.ResetEvent();
	mScanViewStruct1.pGrainFinder->GFC.pT->TP.pTrackInfo;

	m_ScanningParam.ConfidenceEmulsionWidth = 85.f;
	m_ScanningParam.ConfidenceLowerInterval = 20.f;
	m_ScanningParam.ConfidenceUpperInterval = 15.f;
	m_ScanningParam.MaxLightValue = 235;
	m_ScanningParam.Step = 1.f;
	m_ScanningParam.Velocity = 100.f;
	m_ScanningParam.WaitTime = 100;
	m_ScanningParam.SpeedX = 15000;
	m_ScanningParam.SpeedY = 15000;
	m_ScanningParam.SpeedZ = 2000;
	m_ScanningParam.AccX = 200000;
	m_ScanningParam.AccY = 200000;
	m_ScanningParam.AccZ = 100000;

	m_ConfidenceUpperInterval = 8;
	m_ConfidenceLowerInterval = 10;
	m_pFirstScanPoint = NULL;
	m_MaxZetaScanInterval = 175.f;
	m_Mover.UpdatePos();
	m_Mover.GetPos(m_CurrentPos.x,m_CurrentPos.y,m_CurrentPos.z);

	m_bGlobalBytesLoaded = false;
//	Assegnare in runtime newZ,ZetaVelocity,NewPos,SampleCount,XYZMotionDuration,ZScanDuration
}

int CScanner::Messagebox(const char * pChar,int Type)
{
	return MessageBox(((CWnd *)(m_ScanContext.pContext))->m_hWnd,pChar,"Scanner",Type);
}

int CScanner::Scan(bool SaveData)
{
	int Result = 0;
	if(!*m_pScanningInProgress && ScanningAvailable)
	{
		int ToWait;
		float MaxZ,RefZ,StartingZ;
		*m_pScanningInProgress = true;
		Allocator(true);
		m_Mover.EnableStageMonitor(false);
		Sleep(500);
		Vector NewPos;
		m_Mover.GetPos(Opera.XStage,Opera.YStage,m_CurrentPos.z);
		StartingZ = m_CurrentPos.z;
		ToWait = m_Mover.MoveZTo(m_CurrentPos.z + 50.f);
//		ToWait = m_Mover.MoveZTo(Opera.SideUpMaxZ + 100.f);
		Sleep(ToWait);
		int refLight = 22000;
		m_Mover.Light(refLight);
		FindStartingZeta(&mScanViewStruct1,MaxZ);
		RefZ = MaxZ;
		Result = ScanViewOpera(SaveData);
		if(Result == -1 && !m_bShouldStop)
		{
			FindStartingZeta(&mScanViewStruct1,MaxZ);
			RefZ = MaxZ;
			Result = ScanViewOpera(SaveData);
		}
		if(Result > 0 && !m_bShouldStop)
		{
			Opera.ToReturn = Result;
			m_Mover.MoveZTo(RefZ);
		}
		else
		{
			m_Mover.MoveZTo(StartingZ);
			Opera.ToReturn = 0;
		}
		*m_pScanningInProgress = false;
		if(m_ScanContext.pFogInit->IsEmbedded)Allocator(false);
		m_ScanContext.pGrainFinder->ClearMemory();
		mScanViewStruct1.ScanningFinished.SetEvent();
	}
	return Result > 0;
}

int CScanner::ScanViewOpera(bool SaveData)
{
	BYTE * pImage;
	UINT counter = 0;
	CGrainFinder & GF = *m_ScanContext.pGrainFinder;
	float LastZeta,* pDepths = GF.m_depths;
	float Step = m_ScanningParam.Step;
	float Velocity = m_ScanningParam.Velocity;
	float VelocityIncrement = 100;
	UINT WaitTime = m_ScanningParam.WaitTime;
	int i,j,LastNumGrains = 0;
	m_Mover.UpdatePos(true);
	m_Mover.GetPos(m_CurrentPos.x,m_CurrentPos.y,m_CurrentPos.z);
	float MaxZ = m_CurrentPos.z;
	float MinZ = MaxZ - m_ScanningParam.ConfidenceEmulsionWidth;
	GF.GFC.pMicPar->XStageCoordinate = m_CurrentPos.x;
	GF.GFC.pMicPar->YStageCoordinate = m_CurrentPos.y;
	GF.GFC.pMicPar->ZStageCoordinate = m_CurrentPos.z;
	m_bGlobalBytesLoaded = false;
	int ImageSize = mXWidth*mYWidth,FrameCounter;
	GF.m_EmSpaceUp.GetSpace();
	GF.m_GrainsVersion = 7;
	bool Repeated;
	CString text;
	fpos_t LastPos = 0;
	int possize = sizeof(fpos_t);
	for(j = 0; j < 2; j++)
	{
		FrameCounter = 0;
		SetLight(m_ScanningParam.MaxLightValue,true);
		for(i = 0; i < (MAX_NUMBER_OF_IMAGES) && m_CurrentPos.z > MinZ && FrameCounter < 4; i++)
		{
			if(m_bShouldStop)return -1;
			LastZeta = m_CurrentPos.z;
			*(pDepths + i) = LastZeta;
			pImage = SafeFreezeFrame();
			memcpy(m_pGlobalBytes1 + i*ImageSize,pImage,ImageSize);
			WaitTime = m_Mover.MoveZTo(LastZeta - Step,Velocity,0,0);
			if(i > 1 && !Repeated)
			{
				GF.m_MicData.Level = i;
				LastNumGrains = GF.ComputeFrame(i - 1);
			}
			if(i > 20 && LastNumGrains < 20)
				FrameCounter++;
			Sleep(WaitTime);
			m_Mover.GetZeta(m_CurrentPos.z);
			Repeated = false;
			float MicroStep = 1.f;
			counter = 0;
			while(LastZeta - m_CurrentPos.z < 0.2)
			{
				m_ScanContext.pGrainFinder->GFC.pSetInteger(m_ScanContext.pContext,IDC_EDT_FOGMAIN_TOTALMIPS,counter);
				WaitTime = m_Mover.MoveZTo(LastZeta - Step - MicroStep,Velocity,0,0);
				if(MicroStep < 2.f)MicroStep += 0.2f;
				Sleep(WaitTime);
				Sleep(200);
				counter++;
				m_Mover.GetZeta(m_CurrentPos.z);
			}
		}
		GF.FindOperaDistortion(GF.m_EmSpaceUp);
		if(SaveData)
		{
			GF.m_UsedMin = GF.m_EmSpaceUp.NumGrains;
			m_bGlobalBytesLoaded = true;
			m_NumberOfImages = i;
			GF.PurgeFile(0 + 2*j,2 - 2*j);
			GF.GFC.pT->TP.pTrackInfo->StartPhi = 0.f;
			GF.GFC.pT->TP.pTrackInfo->EndPhi = 6.2830f;
			GF.GFC.pT->TP.pTrackInfo->StartTheta = 0.f;
			GF.GFC.pT->TP.pTrackInfo->EndTheta = 3.1415f/4.f;
			GF.GFC.pT->Track3(GF.m_EmSpaceUp,GF.GFC.pT->m_pTrackUp);
			GF.SaveMicData(j,LastPos);
			CString FullPath = GF.m_GrainsFilePath;
			FromFullPathDirectory(FullPath,true);
			CString PostFix = "000000";
			if(GF.GFC.pGFTParam->Options & FOG_OPT_SAVETABLES)GF.SaveTables(FullPath,PostFix,/*j*/0);
		}
		m_Mover.GetZeta(m_CurrentPos.z);
		if(j == 0)
		{
			WaitTime = m_Mover.MoveZTo(m_CurrentPos.z - 170.f);
			Sleep(WaitTime);
			bool ZetaFound = FindStartingZeta(&mScanViewStruct1,MaxZ);
			if(!ZetaFound)
			{
				j--;
				WaitTime = m_Mover.MoveZTo(m_CurrentPos.z + 350.f);
				LastPos = 0;
				Sleep(WaitTime);
				return -1;
			}
			m_Mover.GetZeta(m_CurrentPos.z);
			WaitTime = m_Mover.MoveZTo(m_CurrentPos.z + 3.f);//Gives space between sides updw
			Sleep(WaitTime);
			Opera.SideUpMaxZ = GF.m_EmSpaceUp.ZetaRange.UpperZ;
			Opera.SideUpMinZ = GF.m_EmSpaceUp.ZetaRange.BottomZ;
			Opera.SideUpFogDensity = GF.m_EmSpaceUp.AdjustedDensity;
			Opera.SideUp = 0.f;
			m_Mover.Light(Opera.SideUpLight,false);
			MinZ = MaxZ - m_ScanningParam.ConfidenceEmulsionWidth;
			m_CurrentPos.z = MaxZ;
			for(i = 0; i < 255; i++)
				*(GF.m_depths + i) = NOT_USED_DEPTH;
			GF.m_EmSpaceUp.GetSpace();
		}
		else if(j == 1)
		{
			Opera.SideDwMaxZ = GF.m_EmSpaceUp.ZetaRange.UpperZ;
			Opera.SideDwMinZ = GF.m_EmSpaceUp.ZetaRange.BottomZ;
			Opera.SideDwFogDensity = GF.m_EmSpaceUp.AdjustedDensity;
			Opera.SideDw = 0.f;
			m_Mover.Light(Opera.SideDwLight,false);
			m_bGlobalBytesLoaded = true;
		}
	}
	if(GF.GFC.pUpdateShow)GF.GFC.pUpdateShow(GF.GFC.pContext,255);
	return i;
}


int CScanner::ScanningBatch()
{
	if(!*m_pScanningInProgress)
	{
		if(pFogInit->iFG)pFogInit->iFG->SetLiveGrab();
		else return 0;
		m_Mover.EnableStageMonitor(false);
		CScannerManagerDlg dlg(&m_ScanContext.pGrainFinder->GFC);
		if(dlg.DoModal() == IDCANCEL)return 0;
		*m_pScanningInProgress = true;
		int i;
		int TotalNumberOfScanningPoint = dlg.m_Count;
		int StartingScanPoint = dlg.m_StartPrediction;
		if(TotalNumberOfScanningPoint > 0)
		{
			SScanningPoint * pToScan = m_pFirstScanPoint;
			m_Mover.GetZeta(m_CurrentPos.z);
			m_ReferenceZ = m_CurrentPos.z;
			for(i = 0; i < StartingScanPoint; i++)pToScan = pToScan->pNext;
			for(i = StartingScanPoint; i < TotalNumberOfScanningPoint; i++)
			{
				ScanPointOldStyle(pToScan);
				pToScan = pToScan->pNext;
			}
		}
		*m_pScanningInProgress = false;
		return 1;
	}
	else return 0;
}


int CScanner::ScanView(SScanView * pScanViewStruct)
{
	float MaxZ = pScanViewStruct->MaxZ;
	float MinZ = pScanViewStruct->MinZ;
	if(pScanViewStruct->ScannedView > FOG_GOOD_VIEWS)MinZ = MaxZ - m_EmulsionWidth - m_ScanningParam.ConfidenceLowerInterval;
	else MinZ = MaxZ - m_ScanningParam.ConfidenceEmulsionWidth - m_ScanningParam.ConfidenceLowerInterval;
	BYTE * pGlobalBytes = pScanViewStruct->pGlobalBytes;
	BYTE * pImage;
	float LastZeta;
	UINT counter = 0;
	float Step = m_ScanningParam.Step;
	float Velocity = m_ScanningParam.Velocity;
	float VelocityIncrement = 100;
	UINT WaitTime = m_ScanningParam.WaitTime;
	int i;
	m_Mover.UpdatePos(true);
	m_Mover.GetPos(m_CurrentPos.x,m_CurrentPos.y,m_CurrentPos.z);
	pScanViewStruct->pGrainFinder->GFC.pMicPar->XStageCoordinate = m_CurrentPos.x;
	pScanViewStruct->pGrainFinder->GFC.pMicPar->YStageCoordinate = m_CurrentPos.y;
	pScanViewStruct->pGrainFinder->GFC.pMicPar->ZStageCoordinate = m_CurrentPos.z;
	m_bGlobalBytesLoaded = false;
	bool bEnableOverSampling = (m_ScanContext.pGrainFinder->GFC.pGFTParam->Options & FOG_OPT_ENABLEOVERSAMPLING) == FOG_OPT_ENABLEOVERSAMPLING;
	const int NumberOfSamples = 4;
	int Image,Byte;
	for(i = 0; i < (MAX_NUMBER_OF_IMAGES - NumberOfSamples) && m_CurrentPos.z > MinZ; i++)
	{
		LastZeta = m_CurrentPos.z;
		*(pScanViewStruct->pGrainFinder->m_depths + i) = LastZeta;
		if(bEnableOverSampling)
		{
			for(Image = 0; Image < NumberOfSamples; Image++)
			{
				pImage = SafeFreezeFrame();
				Sleep(10);
				memcpy(pGlobalBytes + (i + Image)*mXWidth*mYWidth,pImage,mXWidth*mYWidth);
			}
			for(int j = 0; j < mXWidth*mYWidth; j++)
			{
				Byte = 0;
				for(Image = 0; Image < NumberOfSamples; Image++)
				{
					Byte += *(pGlobalBytes + (i + Image)*mXWidth*mYWidth + j);
				}
				*(pGlobalBytes + i*mXWidth*mYWidth + j) = (Byte >> 2);
			}
		}
		else
		{
			pImage = SafeFreezeFrame();
			Sleep(20);

			memcpy(pGlobalBytes + i*mXWidth*mYWidth,pImage,mXWidth*mYWidth);
		}
		m_Mover.MoveZTo(LastZeta - Step,Velocity,0,0);
		Velocity = m_ScanningParam.Velocity;
		Sleep(WaitTime);
		m_Mover.GetZeta(m_CurrentPos.z);
		if(fabs(LastZeta - m_CurrentPos.z) < 0.2)
		{
			i--;
			counter++;
			if(counter == 5)
			{
				counter = 0;
				m_Mover.MoveZTo(LastZeta + Step,500,0,0);
				m_Mover.MoveZTo(LastZeta - Step,500,0,0);
				pScanViewStruct->LogText.Format("Microscope Twisted  %d identifier %d          \t",pScanViewStruct->pThread->m_nThreadID,pScanViewStruct->Identifier);
				LogWriteTime(pScanViewStruct->LogText);
			}
		}
	}
	if(pScanViewStruct->pGlobalBytes == m_pGlobalBytes1)m_bGlobalBytesLoaded = true;
	return i;
}

UINT ScanViewThread(void * pScanViewStruct)
{
	static int ScannedView = 0;
	ScannedView += 100;
	float maxZ,ConfidenceInterval = 20.f;
	int test;
	bool ZetaFound;

	SScanView &ScanViewStruct = *((SScanView *)pScanViewStruct);
	ScanViewStruct.IspThreadValid = false;
	if(ScanViewStruct.ZSearchRange > 0)
	{
		ZetaFound = ScanViewStruct.pScanner->FindStartingZeta(&ScanViewStruct,maxZ);
		ScanViewStruct.MaxZ = maxZ;// - ConfidenceInterval;
	}
	WaitForSingleObject(ScanViewStruct.DataComputed.m_hObject,INFINITE);
	ScanViewStruct.IspThreadValid = true;
	ScanViewStruct.pGrainFinder->m_GrainsFilePath = ScanViewStruct.GrainsFilePath;
	ScanViewStruct.NumberOfImages = ScanViewStruct.pScanner->ScanView(&ScanViewStruct);
	test = ScanViewStruct.ScanningFinished.SetEvent();
	CString Text;
	Text.Format("Fog - %s",ScanViewStruct.GrainsFilePath);
	if(ScanViewStruct.Identifier == 1)((CWnd *)ScanViewStruct.pScanner->m_ScanContext.pContext)->SetWindowText(Text);
	ScanViewStruct.pGrainFinder->ComputeSetOfImages(ScanViewStruct.pGlobalBytes,ScanViewStruct.NumberOfImages);
	if(ScanViewStruct.pGrainFinder->GFC.pGFTParam->Options & FOG_OPT_SAVETABLES)ScanViewStruct.pGrainFinder->SaveTables("scn");
	ScanViewStruct.MaxZ = ScanViewStruct.pGrainFinder->m_EmSpaceUp.ZetaRange.UpperZ;// + ScanViewStruct.pScanner->m_ScanningParam.ConfidenceUpperInterval;
	ScanViewStruct.MinZ = ScanViewStruct.pGrainFinder->m_EmSpaceUp.ZetaRange.BottomZ;// - ScanViewStruct.pScanner->m_ScanningParam.ConfidenceLowerInterval;
	if(ScanViewStruct.ScannedView < FOG_GOOD_VIEWS)ScanViewStruct.pScanner->PushNewWidth(ScanViewStruct.MaxZ - ScanViewStruct.MinZ);
	ScanViewStruct.pScanner->UpdateScanningLog(&ScanViewStruct);
	test = ScanViewStruct.DataComputed.SetEvent();
		ASSERT(test);
	return 1000000000 + ScannedView;
}

int CScanner::ScanPointOldStyle(SScanningPoint *pToScan)
{
	int i,j;
	static int bOdd = 0;
	bool result;
	if(pToScan->ResumedY == pToScan->NumStepY)return 0;
	int NumStepX = pToScan->NumStepX, NumStepY = pToScan->NumStepY;
	float StepX = pToScan->StepX, StepY = pToScan->StepY;
	float NewPosX,NewPosY,NewPosZ;
	float &MaxZeta = mScanViewStruct1.MaxZ;
	float &MinZeta = mScanViewStruct1.MinZ;
	float LastFirstOfRowMaxZeta;
	float NewPosZeta;//,ReferenceSurface;
	CGrainFinder & GF = *(m_ScanContext.pGrainFinder);
	int FirstOfRow = 0;
	int XYWaitTime;
	float StartingX = pToScan->X - pToScan->ResumedX*pToScan->StepX;//pToScan->X - StartingStepX*pToScan->StepX;
	float StartingY = pToScan->Y + pToScan->ResumedY*pToScan->StepY;//pToScan->Y + StartingStepY*pToScan->StepY;
	bool bForceFindingZeta = false,ZetaFound;
	m_Mover.GetZeta(NewPosZeta);
	XYWaitTime = m_Mover.MoveTo(StartingX,StartingY);
	m_Mover.MoveZTo(NewPosZeta + 200,FOG_DEF_SPEED,FOG_WAITTIME_AUTOMATIC,XYWaitTime);
	ZetaFound = FindStartingZeta(&mScanViewStruct1,MaxZeta);
	NewPosZeta = MaxZeta;
	MinZeta = MaxZeta - m_ScanningParam.ConfidenceEmulsionWidth;
//	ReferenceSurface = MaxZeta;
	SetLight(m_ScanningParam.MaxLightValue,true);
	ResetWidthCounter();
	SScanView * pScanViewStruct = NULL, * pNextScanViewStruct = NULL;
	bOdd += (pToScan->ResumedX + pToScan->ResumedY*NumStepX);
	pScanViewStruct = &mScanViewStruct1;
	pScanViewStruct->ZSearchRange = 0;
	int ViewScanned = 1;
	int StartingStepX = pToScan->ResumedX;
	if(m_pGlobalBytes1)
	{	
		for(i = pToScan->ResumedY; i < NumStepY; i++)
		{	
			if(m_EmulsionWidth > 20.f)//ie If m_EulsionWidth is meaningful
			{
				MaxZeta = LastFirstOfRowMaxZeta + m_ConfidenceUpperInterval;
				MinZeta = LastFirstOfRowMaxZeta - m_EmulsionWidth - m_ConfidenceLowerInterval;
			}
//			MaxZeta = -90;
			for(j = StartingStepX; j < NumStepX; j++)
			{	
				StartingStepX = 0;
				pScanViewStruct->ViewNumber = bOdd;
				pScanViewStruct->ScannedView = ViewScanned;
				float wf;
				if(bForceFindingZeta){FindStartingZeta(pScanViewStruct,wf);bForceFindingZeta = false;}
				m_Mover.UpdatePos();
				m_Mover.GetPos(NewPosX,NewPosY,NewPosZ);
				pScanViewStruct->XStage = NewPosX;
				pScanViewStruct->YStage = NewPosY;
				if(j == 0)LastFirstOfRowMaxZeta = NewPosZ;
				GetNextPosition(NewPosX,NewPosY,pScanViewStruct,i,j,pToScan);
				pScanViewStruct->GrainsFilePath = PrepareNextFileName(i,j,pToScan);

				pScanViewStruct->pThread = AfxBeginThread(ScanViewThread,pScanViewStruct,THREAD_PRIORITY_BELOW_NORMAL);

				result = MoveToNextPosition(NewPosX,NewPosY,pScanViewStruct->NewPosZ,bOdd);
				bOdd++;
				ViewScanned++;
			}
		}
		bOdd = 0;
		return 1;
	}
	else return 0;
}

bool CScanner::MoveToNextPosition(float NewPosX,float NewPosY,float NewPosZ,int Finder)
{
	bool result;
	{
		CEvent * pEventScanFinished;
		pEventScanFinished = &mScanViewStruct1.ScanningFinished;
		WaitForSingleObject(pEventScanFinished->m_hObject,INFINITE);
	}
	{
		float ZSearchRange;
		int XYWaitTime;
		if(mbRepeat)//bFirst)
		{
			ZSearchRange = 200;
			XYWaitTime = m_Mover.MoveTo(mRepeat1.XStage,mRepeat1.YStage);
			m_Mover.MoveZTo(mRepeat1.MaxZeta + 200,FOG_DEF_SPEED,FOG_WAITTIME_AUTOMATIC,XYWaitTime);
			m_Mover.UpdatePos();
			result = false;
		}
		else
		{
			XYWaitTime = m_Mover.MoveTo(NewPosX,NewPosY);//,FOG_DEF_SPEED,FOG_DEF_SPEED,FOG_WAITTIME_AUTOMATIC,FOG_DONTWAIT);
			m_Mover.MoveZTo(NewPosZ,FOG_DEF_SPEED,FOG_WAITTIME_AUTOMATIC,XYWaitTime);
			m_Mover.UpdatePos();
			result = true;
		}
	}
	return result;
}

void CScanner::GetNextPosition(float & NewPosX,float & NewPosY,SScanView * pScanView,int i,int j,SScanningPoint *pToScan)
{
	static float FirstOfRow;
	static int FirstOfRowViewNumber;
	float UpperInterval = m_ScanningParam.ConfidenceUpperInterval;
	int NumStepX = pToScan->NumStepX;
	int NumStepY = pToScan->NumStepY;
	float StepX = pToScan->StepX;
	float StepY = pToScan->StepY;
	float OldPosZ = pScanView->MaxZ, & NewPosZ = pScanView->NewPosZ;
	if(j == 0)FirstOfRowViewNumber = pScanView->ViewNumber;
	if(j == 0 && i == 0)FirstOfRow = OldPosZ;
//	else if(FirstOfRowViewNumber + 4 == pScanView->ViewNumber)FirstOfRow = OldPosZ;
	bool bResumedX = pToScan->ResumedX > 0;
	if(pToScan->ResumedX == j && pToScan->ResumedY == i)FirstOfRow = OldPosZ;
	float ZSearchRange = 0;
	NewPosX = pToScan->X - StepX*((j + 1)%NumStepX);
	NewPosY = pToScan->Y + StepY*(i + (j + 1)/NumStepX);
	NewPosZ = pScanView->MaxZ;
	if(j == NumStepX - 1 && i == NumStepY - 1)//Last View of actual point
	{
		if(pToScan->pNext)
		{
			NewPosX = pToScan->pNext->X;
			NewPosY = pToScan->pNext->Y;
		}
		else
		{
			NewPosX = m_pFirstScanPoint->X;
			NewPosY = m_pFirstScanPoint->Y;
		}
	}// NewZetaPositions
	if(j == NumStepX - 1)// Last View in current row
	{
		if(i == NumStepY - 1)
		{
			
		}
		else
		{
			if(StepY <= 800)
			{
				if(bResumedX)ZSearchRange = 200.f;
				else ZSearchRange = 0.f;
				NewPosZ = FirstOfRow + UpperInterval + ZSearchRange;
			}
			else
			{
				if(bResumedX)ZSearchRange = 200.f;
				else ZSearchRange = (StepY*200.f)/(StepY + 10000.f) + UpperInterval;
				NewPosZ = FirstOfRow + ZSearchRange;
			}
		}
	}
	else
	{
		if(StepX <= 800)
		{
			if(j < 4)
			{
				NewPosZ = FirstOfRow + UpperInterval;
				ZSearchRange = 0;
			}
			else 
			{
				NewPosZ += UpperInterval;
				ZSearchRange = 0;
			}
		}
		else
		{
			ZSearchRange = (StepX*200.f)/(StepX + 10000.f) + UpperInterval;
			NewPosZ += ZSearchRange;
		}
	}
	pScanView->ZSearchRange = ZSearchRange;
}

CString CScanner::PrepareNextFileName(int i, int j, SScanningPoint * pToScan)
{
	CString FileName,NameEnd;
	NameEnd.Format(" %02d %02d",i + 1,j + 1);
	FileName.Format("%s\\%s%s",pToScan->Directory,pToScan->FileNames,NameEnd);
	return FileName;
}

float CScanner::PushNewWidth(float NewWidth)
{
	return m_EmulsionWidth += ((NewWidth - m_EmulsionWidth)/(++mWidthCounter));
}

int CScanner::SetLight(int toSet,bool IsReferredToPixels)
{
	int levelSet = 0,counter = 0;
	if(toSet == -1)
	{
		m_Mover.Light(levelSet,FOG_GET);
		return levelSet;
	}
	int LightLimit = MAX_MICROSCOPE_LIGHT;//32767;
	if(IsReferredToPixels)
	{
		if(IsReferredToPixels && toSet > 250)toSet = 250;
		int LightLevel = 22000;

		int MaxByte = 0,Delta = 255,DeltaMultiplier,ii,jj;
		BYTE * pByte;
		if (LightLevel < 0) LightLevel = 0;
		else if (LightLevel > LightLimit) LightLevel = LightLimit;
		if(pFogInit->iFG != NULL)
		{
			m_Mover.Light(LightLevel,FOG_GET);
			while((Delta > 3 || Delta < -3) && counter < 15)
			{
				m_Mover.Light(LightLevel);
				levelSet = LightLevel;
				Sleep(700);
				if(m_bShouldStop)
				{
					m_Mover.Light(toSet);
					return 0;
				}
				pByte = SafeFreezeFrame();
				MaxByte = 0;
				for(ii = 7; ii < 1280 - 7; ii++)
				{
					for(jj = 7; jj < 1024 - 7; jj++)
					{
						if(MaxByte < *(pByte + ii + jj*1280))MaxByte = *(pByte+ ii + jj*1280);
					}
				}	
				Delta = toSet - MaxByte;
				DeltaMultiplier = 20;
				if(Delta < 20 && Delta > 0)DeltaMultiplier = Delta;
				else if(Delta > -20 && Delta <= 0)DeltaMultiplier = -Delta;
				LightLevel += Delta*DeltaMultiplier;
				if(LightLevel > LightLimit)LightLevel = LightLimit;
				counter++;
			}
		}
	}
	else
	{
		if(toSet > LightLimit)toSet = LightLimit;
		if(toSet < 0)toSet = 0;
		m_Mover.Light(toSet);
		levelSet = toSet;
	}
	return levelSet;
}

#endif //!defined FOG_HOME
void CScanner::ShowImages()
{
	if(!*m_pScanningInProgress)
	{
		*m_pScanningInProgress = true;
/*#ifndef FOG_HOME
		m_ScanContext.pGrainFinder->m_GrainsFilePath = "C:\\sysal2000\\fog2000\\FirstFile.grs";
#endif
#ifdef FOG_HOME
	m_ScanContext.pGrainFinder->m_GrainsFilePath = "C:\\Fulvio\\fog2000\\FirstFile.grs";
#endif*/
//		m_ScanContext.pGrainFinder->FindOffsets();
		UINT & Options = m_ScanContext.pGrainFinder->GFC.pGFTParam->Options;
		UINT TrackGrains = Options & FOG_OPT_TRACK;
		UINT SaveGrains = Options & FOG_OPT_SAVEGRAINS;
		Options &= ~FOG_OPT_TRACK;
		Options &= ~FOG_OPT_SAVEGRAINS;
		if(m_pGlobalBytes1)m_ScanContext.pGrainFinder->ComputeSetOfImages(m_pGlobalBytes1,m_NumberOfImages);
		*m_pScanningInProgress = false;
		if(m_ScanContext.pGrainFinder->GFC.pUpdateShow)m_ScanContext.pGrainFinder->GFC.pUpdateShow(m_ScanContext.pGrainFinder->GFC.pContext,255);
		Options |= (TrackGrains | SaveGrains);
	}
}

#ifndef FOG_HOME

void CScanner::PrepareRepeating(SScanView *pScanView)
{
	mbRepeat = true;
	mRepeat1.XStage = pScanView->XStage;
	mRepeat1.YStage = pScanView->YStage;
	if(mRepeat1.pIdentifier == NULL)mRepeat1.pIdentifier = pScanView;
	else ;
}

void CScanner::UpdateScanningLog(SScanView *pScanView)
{
#ifdef _DEBUG
	int Written;
	FILE * pScanningLogFile = fopen(ScanningLogFile,"a+b");
	if(pScanningLogFile)Written = fwrite(&pScanView->ViewNumber,sizeof(int),1,pScanningLogFile);
	if(Written == 0)Messagebox("Written == 0");
	if(pScanningLogFile)fclose(pScanningLogFile);
#endif
}

void CScanner::SaveSingleImage(const char *pFilePath)
{
	FILE * pOutputFile = fopen(pFilePath,"wb");
	if(pOutputFile == NULL)
	{
		Messagebox("Cannot Open the file Specified");
		return;
	}
	fwrite(BitmapHeader,sizeof(BitmapHeader),1,pOutputFile);
	unsigned int i,graylevel;
	unsigned char * pImage = NULL;
	pImage = SafeFreezeFrame();
	for(i = 0; i < 256; i++)
	{
		graylevel = (i + (i << 8) + (i << 16));
		fwrite(&graylevel,sizeof(int),1,pOutputFile);
	}
	if(pImage != NULL)
	{
		for(i = 0; i < 1024; i++)
		{
			int written = fwrite(pImage + (1023 - i)*1280,1280,1,pOutputFile);
			if(written < 1)Messagebox("errore");
		}
	}
	fclose(pOutputFile);
}

BYTE * CScanner::SafeFreezeFrame()
{
	int Counter1 = 0,Counter2 = 0;
	static BYTE * pBytes = NULL;
	BYTE wByte = 0;
	int i,ImageSize = mXWidth*mYWidth;
	if(pBytes == NULL && pFogInit->iFG != NULL)
	{
		pFogInit->iFG->FreezeFrame(&pBytes);
		Sleep(20);
	}
	if(pFogInit->iFG != NULL)
	{
		memset(pBytes,0,ImageSize);
		pFogInit->iFG->FreezeFrame(&pBytes);
		while(wByte == 0)
		{
			for(i = 0; i < ImageSize; i++)
			{
				wByte = *(pBytes + i);
				if(wByte == 0)break;
			}
			Counter2 += i;
			if(wByte == 0)
			{
				Sleep(5);
				Counter1++;
			}
		}
	}
	return pBytes;
}

void CScanner::ShowGrid(float GridSize,bool Show)
{
	int j,NumberOfPixels;
	float PixelSize = pGlobalMicroParameters->PixLen;
	NumberOfPixels = GridSize/PixelSize;
	int NumberOfLineX = 1280/NumberOfPixels;
	int NumberOfLineY = 1024/NumberOfPixels;
	int OffsetX = (1280 % NumberOfPixels)/2;
	int OffsetY = (1024 % NumberOfPixels)/2;
	if(Show)
	{
		for(j = 0; j < NumberOfLineY + 1; j++)
		{
			pFogInit->iFG->Line(0,OffsetY + j*NumberOfPixels,1280,OffsetY + j*NumberOfPixels,1);
		}
		for(j = 0; j < NumberOfLineX + 1; j++)
		{
			pFogInit->iFG->Line(OffsetX + j*NumberOfPixels,0,OffsetX + j*NumberOfPixels,1280,1);
		}
	}
	else
	{
		int ColorCode;
		pFogInit->iFG->GetColorCode(VC_TRANSPARENT,&ColorCode);
		pFogInit->iFG->Clear(ColorCode);
	}
}


#endif // !defined FOG_HOME





bool CScanner::ReallocGlobalBytes(int NumberOfImages)
{
	if(GlobalYetAllocated)
	{
		GlobalFree(m_pGlobalBytes1);
		m_pGlobalBytes1 = NULL;
		m_ScanContext.pGrainFinder->m_pImageData = NULL;
		MaxNumberOfImages = 0;
		GlobalYetAllocated = false;
	}
	if(!GlobalYetAllocated)
	{
		int Width = m_ScanContext.pGrainFinder->GFC.pMicPar->HalfCCDWidth * 2;
		int Length = m_ScanContext.pGrainFinder->GFC.pMicPar->HalfCCDLength * 2;
		mXWidth = Width;
		mYWidth = Length;
		m_pGlobalBytes1 = (BYTE *)GlobalAlloc(GMEM_FIXED, NumberOfImages * Width * Length);
		if(m_pGlobalBytes1)MaxNumberOfImages = NumberOfImages;
		else MaxNumberOfImages = 0;
		m_ScanContext.pGrainFinder->m_pImageData = m_pGlobalBytes1;
		GlobalYetAllocated = m_pGlobalBytes1 != NULL;
		mScanViewStruct1.pGlobalBytes = m_pGlobalBytes1;
	}
	return GlobalYetAllocated;
}
