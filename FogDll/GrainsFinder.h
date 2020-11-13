// GrainsFinder.h: interface for the CGrainsFinder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAINSFINDER_H__06AD8C44_0D3E_11D8_BED7_D04454C10000__INCLUDED_)
#define AFX_GRAINSFINDER_H__06AD8C44_0D3E_11D8_BED7_D04454C10000__INCLUDED_

#include "Common.h"
#include "GrainRaw.h"
#include "Tracker.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct SGFTParam
{
	char * pFiles;
	UINT Options;
	int StartFrame;
	int LastFrame;
	int Frames;
	CString FilePath;
};
struct SGFContext
{
	void * pContext;
	CTracker * pT;
	int * pLastNumGrains;
	int * pNumGrains;
	SMicroParameters * pMicPar;
	SGrainFinderParameters * pGfPa;
	SGFTParam * pGFTParam;
	bool (* pIsDifferential)(void * thiss);
	void (* pSetDialogData)(void * thiss,int Min, int Max, int Frame, float Media , float Depth);
	void (* pGetComputingParameters)(void *, int &,int &,int &);
	void (* pShowGrains)(void *, SIntGrain *,int,int);
	void (* pSetInteger)(void *, UINT,int);
	void (* pShowPicture)(void *, int);
	void (* pSetDlgItemText)(void *, UINT,const char *);
	void (* pSetFloat)(void *, UINT,float);
	void (* pShowMips)(void *, SMip *);
	BYTE * (*pGrabImage)(void *, float * curDepth);
	struct IDCS{UINT Minimo,Medio,Massimo,Locali,Totali,Mips,Depth;}Idc;
};

class CGrainsFinder  
{
public:
	SGrainFinderParameters GFPa;
	SGFContext GFC;
	float * m_depths;
	void CheckDensity(SEmulsionSpace & Space);
	SDistortion FindDistortionCenter(SEmulsionSpace &Space);
	SDistortion FindDistortionParameters(SEmulsionSpace &Space);
	int LoadGrains(const char * Path,int Delta =0,int Threshold =0);
	void SaveGrains(CString Path,int version = 0);
	SMinimum * m_pMinimi;
	CGrainsFinder();
	virtual ~CGrainsFinder();
	int ComputeData(int frame,SGrain ** pMinGrains,SEmulsionSpace &Space, float * depths, int Options);
	void AdjustData(FILE * Stream,int position,BYTE * ImageData,float * pDepths,int ToStartFrame = 0);
	void GetRelevantFromHeader(int &Frames,int &Size,float * AMatrix,FILE *ComputeFile);
	friend UINT ComputingThread(LPVOID pParam);
	friend UINT FindGrainsThread(LPVOID pParam);
	CGrainRaw * m_pGrainRawBase;
private:
	BYTE IsAMinimum(BYTE * pointer);
	BYTE FindMax(BYTE * pointer);
	BYTE FindMinimum(BYTE * pointer);
	BYTE * FindMinP(BYTE * pointer);
	WORD FindMinMax(BYTE * pointer);
	bool GrainExists(SIntGrain * pBulk,int NumGrains,SIntGrain * pGrain,float DXY, float DZ);
	bool IsLocalMinimum(BYTE * pByte);
	void SelectEmulsionGrainsRange(SEmulsionSpace & Space,int &minzpos,int &maxzpos);
	void ShiftPointers(int shift);
	static	int compare(const void * elem1,const void * elem2);
	float Depth(double b1,double f1,double b2,double f2,double b3,double f3,double b4,double f4,double b5,double f5);
	float Depth(double b1,double f1,double b2,double f2,double b3,double f3);
	float DepthF(float b1, float f1, float b2, float f2, float b3, float f3);
	BYTE Scarto(BYTE * pByte);
	BYTE FindLocalMinimum(BYTE * pByte);
	WORD FindLocalMinimumEx(BYTE *pByte,int delta);
//	struct GrainRawBase
//	{
//		CGrainRaw State00,State01,State02,State04,State10,State20,State30,State40,Mic2Noise,Noise;
//	} m_GrainRawBase;
public:
	SSheet m_Sheet;
	void DTStatistics(CString Path);
	static byte * MemoryGrabber(void * pByte, float * currentDepth);
	SGrain * m_pMinGrains;
	bool GrainTest(SGrain * pMin,int frame,BYTE * pointer, int Delta, int Threshold,UINT Options);
	bool GrainTest2(SMinimum * pMin,int frame,BYTE * pointer, int Delta, int Threshold,UINT Options);
	bool GrainTestOld(SMinimum * pMin,int frame,BYTE * pointer, int Delta, int Threshold,UINT Options);
	int FindOffset(BYTE * pImage1, BYTE * pImage2, int size = 32, int MaxOffSet = 8);
	int ComputeFile(LPCSTR pFileName,SGFTParam * pGftP = NULL);
	int ComputeFileMem(byte * pFile,SGFTParam * pGftP = NULL);
	void ApplyCorrection(SEmulsionSpace &Space,SDistortion Dist);
	CString m_GrainsFilePath;
	int LoadTextGrains(CString Path);
	void ApplyCorrection(SDistortion Dist,SIntGrain &gr);
	int m_Session;
	int m_NumMin;
	BYTE * m_pImageData;
	bool m_bImageDataUsed;
//	void * m_pFogDlg;
	BYTE * ImageDataP[5];
	SEmulsionSpace m_EmulsionRegion;
	SEmulsionSpace m_ComputingRegion;
};

#endif // !defined(AFX_GRAINSFINDER_H__06AD8C44_0D3E_11D8_BED7_D04454C10000__INCLUDED_)
