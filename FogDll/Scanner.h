// Scanner.h: interface for the CScanner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCANNER_H__7D0B7462_95FA_4B17_AFB8_AAD7F72C1EFF__INCLUDED_)
#define AFX_SCANNER_H__7D0B7462_95FA_4B17_AFB8_AAD7F72C1EFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScanner;

#include "common.h"
#include "Mover.h"
#include "FogScanningStructs.h"
#include <afxmt.h>


struct SScannerContext
{
	void * pContext;
	CGrainFinder * pGrainFinder;
	CTracker * pTracker;
	SFogInit * pFogInit;
	SScannerContext(void * pcontext,CGrainFinder * pgrainfinder,CTracker * ptracker,SFogInit * pfoginit):
	pContext(pcontext),pGrainFinder(pgrainfinder),pTracker(ptracker),pFogInit(pfoginit){};
};


struct SScanView
{
	// Variabili in lettura;
	float XStage;
	float YStage;
	float ZSearchRange;
	float NewPosZ;
	CString GrainsFilePath;
	//	Variabili in scrittura;
	int NumberOfImages;
	float MaxZ;
	float MinZ;
	bool IspThreadValid;
	//	Variabili di servizio;
	BYTE * pGlobalBytes;
	CScanner * pScanner;
	CGrainFinder * pGrainFinder;
	CWinThread * pThread;
	SScanView * pPrevious,* pNext;
	// Variabili di controllo
	int Identifier;
	int ViewNumber;
	int ScannedView;
	CString LogText;
	// Eventi
	CEvent StartedComputing;
	CEvent DataComputed;
	CEvent ScanningStarted;
	CEvent ScanningFinished;
};

struct SScanRepeat
{
	float XStage;
	float YStage;
	float MaxZeta;
	SScanView * pIdentifier;
};
struct SOperaAsked
{
	float XStage;
	float YStage;
	float SideUpMaxZ;
	float SideUpMinZ;
	float SideUpFogDensity;
	float SideUp;
	int SideUpLight;
	float SideDwMaxZ;
	float SideDwMinZ;
	float SideDwFogDensity;
	float SideDw;
	int SideDwLight;
	int ToReturn;
};

class CScanner  
{
public:// Members
#ifdef FOG_HOME

	int m_NumberOfImages;
	BYTE * m_pGlobalBytes1;
	SScanView mScanViewStruct1;
	bool * m_pScanningInProgress;
	SScannerContext & m_ScanContext;
	CScanner(SScannerContext * pContext);
	~CScanner();
	void Initialization();
	void Allocator(bool Alloc);
	bool m_bGlobalBytesLoaded;
	void ScanningBatch(){};
	void ShowImages();
	int MaxNumberOfImages;
	SScanningParam m_ScanningParam;
	SOperaAsked Opera;
	bool GlobalYetAllocated;
	int mXWidth;
	int mYWidth;
	bool m_bShouldStop;
	int Scan(bool SaveData = false);

#else

	SOperaAsked Opera;
	bool m_ScanningInitialized;
	bool * m_pScanningInProgress;
	bool m_bGlobalBytesLoaded;
	BYTE * m_pGlobalBytes1;
	CTracker * m_pScanTracker;
	CGrainFinder * m_pScanGrainFinder;
	CMover m_Mover;
	float m_ReferenceZ;
	float m_ConfidenceLowerInterval;
	float m_ConfidenceUpperInterval;
	float m_FramesZInterval;
	float m_MaxZetaScanInterval;
	float m_EmulsionWidth;
	int & m_NumberOfImages;
	SScanningPoint * m_pFirstScanPoint;
	SScannerContext & m_ScanContext;
//	SMicroParameters m_MicroParameters;
	SSheet m_Sheet;
	STrackingInfo m_TrackingInfo;
	SScanningParam m_ScanningParam;
	Vector m_CurrentPos;
	SScanView mScanViewStruct1;
	SScanRepeat mRepeat1,mRepeat2,mRepeat3,mRepeat4;
	int MaxNumberOfImages;
public:// Methods 
	BYTE * SafeFreezeFrame();
	void SaveSingleImage(const char * pFilePath);
	CString ScanningLogFile;
	bool GlobalYetAllocated;
	void UpdateScanningLog(SScanView * pScanView);
	void PrepareRepeating(SScanView * pScanView);
	void Allocator(bool Alloc);
	void Initialization();
	CScanner(SScannerContext *pContext);
	virtual ~CScanner();
	int SetLight(int toSet,bool IsReferredToPixels);
//	int EnableStageMonitor(bool enable);
	bool CScanner::FindStartingZeta(SScanView * pScanView,float & maxz);
	void GetNextPosition(float & NewPosX,float & NewPosY,SScanView * pnextscanview,int i,int j,SScanningPoint *pToScan);
	float GetEmulsionWidth(){return m_EmulsionWidth;};
	bool MoveToNextPosition(float NewPosX,float NewPosY,float NewPosZ,int Finder);
	CString PrepareNextFileName(int i, int j, SScanningPoint * pToScan);
	float PushNewWidth(float NewWidth);
	int ScanningBatch();
	int ScanPointOldStyle(SScanningPoint * pToScan);
	void ShowImages();
	int ScanView(SScanView * pScanViewStruct);
	int Scan(bool SaveData = false);
	int ScanViewOpera(bool SaveData = false);
	static SFogInit * m_pFogInit;
	bool m_bShouldStop;
	void ResetWidthCounter(){m_EmulsionWidth = 0.f; mWidthCounter = 0;};

private: // Members
	int mWidthCounter;
	int mXWidth;
	int mYWidth;
private: // Methods
	static void ShowGrid(float GridSize,bool Show);
	bool mbRepeat;
	int Messagebox(const char * pChar,int Type = MB_OK);
#endif // !defined FOG_HOME
public:
	bool ReallocGlobalBytes(int NumberOfImages);
};
#endif // !defined(AFX_SCANNER_H__7D0B7462_95FA_4B17_AFB8_AAD7F72C1EFF__INCLUDED_)
