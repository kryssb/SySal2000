// GrainFinder.h: interface for the CGrainFinder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAINSFINDER_H__06AD8C44_0D3E_11D8_BED7_D04454C10000__INCLUDED_)
#define AFX_GRAINSFINDER_H__06AD8C44_0D3E_11D8_BED7_D04454C10000__INCLUDED_

#include "FogDefinitions.h"
#include "Common.h"
#include "Tracker.h"

class CGrainFinder;

#include "Scanner.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct SGrainTest
{	
	bool IsGrain;
	bool IsMinimum;
	bool IsPreviousMinimum;
	bool IsNextMinimum;
	bool FromImage;
	int PreviousDelta;
	int Delta;
	int NextDelta;
	int Frame;
	SIntGrain Grano;
	float DistanceXY;
	float DistanceZ;
	float Distance;
	float IsoDistance;
};

struct SGFTParam
{
	char * pFiles;
	UINT Options;
	int StartFrame;
	int LastFrame;
	int Frames;
	CString FilePath;
	CString TablesPostFix;
	SGFTParam():pFiles(NULL),
		Options(FOG_OPT_DIFFERENTIAL | FOG_OPT_COMPUTEPHS | FOG_OPT_FOG2000 | FOG_OPT_SHOWPICTURE | 
		FOG_OPT_SHOWGRAINS | FOG_OPT_SAVEGRAINS | FOG_OPT_FINDGRAINS | FOG_OPT_GLOBALBYTES
		| FOG_OPT_CORRECTDIST | FOG_OPT_FILEDIRECTORY | FOG_OPT_SAVETABLES | FOG_OPT_SAVETRACKTABLE),
		StartFrame(3),LastFrame(3),
		Frames(5),FilePath(" "),TablesPostFix(""){};
};
struct SGFContext
{
	void * pContext;
	SMicroParameters * pMicPar;
	SGrainFinderParameters * pGfPa;
	SGFTParam * pGFTParam;
	CTracker * pT;
	CWinThread ** ppThread;
	CScanner * pScanner;
	int * pLastNumGrains;
	int * pNumGrains;
	bool (* pIsDifferential)(void * thiss);
	void (* pSetDialogData)(void * thiss,int Min, int Max, int Frame, float Media , float Depth);
	void (* pGetComputingParameters)(void *, int &,int &,int &);
	void (* pShowGrains)(void *, SIntGrain *,int,int);
	void (* pSetInteger)(void *, UINT,int);
	int (* pGetInteger)(void *, UINT,int &);
	void (* pShowPicture)(void *,int,UINT,SIntGrain *,int,SMip *);
	void (* pSetDlgItemText)(void *, UINT,const char *);
	void (* pSetFloat)(void *, UINT,float);
	void (* pShowMips)(void *, SMip *);
	BYTE * (*pGrabImage)(void *, float * curDepth);
	void (* pWriteLog)(const char *,const char *);
	void (* pUpdateShow)(void *,UINT toUpdate);
	void (* pMessage)(const char *,const char *,UINT Kind);
	IDCS *pIdc;
	char ConName[5];
};

struct SOperaData
{
	int ImageCountUp,ImageCountDw;
	float StageX,StageY;
	float MappedX,MappedY;
	double Imxx,Imxy,Imyx,Imyy;
	float sx,sy;
};

struct SPredictionTakeImages
{
	SOperaData D;
	CString OutputPath;
};

struct SMicData
{
	BYTE * pGlobalBytes;
	float * pDepths;
	SEmulsionSpace * pSpaceUp;
	SEmulsionSpace * pSpaceDw;
	SOperaData * pOperaData;
	int LevelsUp,LevelsDw;
	SMip * pMipsUp;
	SMip * pMipsDw;
	bool HasImages;
	int Level;
};

class CGrainFinder  
{
public:
	SPredictionTakeImages m_PredData;
	SMicData m_MicData;
	void SaveMicData(int Side,fpos_t & LastPos,const char * pPath = NULL);
	int ComputeFrame(int frame);
	int ComputeSetOfImages(BYTE * pBytes,int NumberOfImages);
	SGFContext GFC;
	WORD * CAPoints;
	BYTE ** CSFPointers;
	float * m_depths;
	void CheckDensity(SEmulsionSpace & Space);
	SDistortion FindOperaDistortion(SEmulsionSpace &Space);
	int LoadGrains(const char * Path,int Delta =0,int Threshold =0);
	void SaveGrains(CString Path,int version = 0);
	void SaveTables(CString Path,CString PostFix,int Side = 0);
	void SaveTables(CString PostFix);
	CGrainFinder(SGFContext *Context = NULL);
	virtual ~CGrainFinder();
	int ComputeData(int frame,SGrain ** ppMinGrains = NULL,int * pNumMin = NULL,SEmulsionSpace * space = NULL, float * depths = NULL, UINT Options = 0);
	WORD * ComputeArea(BYTE * pImage,int PosX,int PosY,int HalfSizeX,int HalfSizeY);
	BYTE ** ComputeSingleFrame(BYTE * pBytes,int XWidth,int YWidth,int Delta, int Margin);
	friend UINT FindGrainsThread(LPVOID pParam);
private:
	int * mpZetas;
	int * mpGoodOne;
	BYTE IsAMinimum(BYTE * pointer);
	BYTE FindMax(BYTE * pointer);
	BYTE FindMinimum(BYTE * pointer);
	BYTE * FindMinP(BYTE * pointer);
	WORD FindMinMax(BYTE * pointer);
	bool GrainExists(SIntGrain * pBulk,int NumGrains,SIntGrain * pGrain,float DXY, float DZ);
	bool IsLocalMinimum(BYTE * pByte);
	float Depth(double b1,double f1,double b2,double f2,double b3,double f3,double b4,double f4,double b5,double f5);
	float Depth(double b1,double f1,double b2,double f2,double b3,double f3);
	BYTE FindLocalMinimum(BYTE * pByte);
	WORD FindLocalMinimumEx(BYTE *pByte,int delta);
public:
	bool * m_pComputingInProgress;
	SGrainTest * ExtendedGrainTest(unsigned char * pByte,UINT Options);
	SGrainTest * ExtendedGrainTest(int Dx,int Dy,float z);
	int PurgeFile(int Up = 0, int Dw = 0);
	bool m_FileLoaded;
	int * m_pOffsets;
	int ChangeSet(int Delta, int Threshold,float Radius = 0.f,float RingSize = 0.f);
	void ZetaGoodness(SEmulsionSpace * pSpace, float & Product, int & Width, float & Depth);
	void Goodness(SEmulsionSpace * pSpace, float & Product, int & Width, float & Depth);
	int ImageSpace();
	SSheet m_Sheet;
	void DTStatistics(CString Path);
	SGrain * m_pMinGrains;
	bool GrainTest(SGrain * pMin,int frame,BYTE * pointer, int Delta, int Threshold,UINT Options);
	int ComputeFile(LPCSTR pFileName,SGFTParam * pGftP = NULL);
	void ApplyCorrection(SEmulsionSpace &Space,SDistortion Dist);
	CString m_GrainsFilePath;
	int LoadTextGrains(CString Path);
	void ApplyCorrection(SDistortion Dist,SIntGrain &gr);
	int m_Session;
	int m_NumMin;
	int m_UsedMin;
	int m_GrainsVersion;
	int mXWidth; 
	int mYWidth;
	int mImageSize;
	BYTE * m_pImageData;
	SEmulsionSpace m_EmSpaceUp;
	SEmulsionSpace m_EmSpaceDw;
	void ClearMemory(void);
	int LoadMicData(const char * pFilePath);
};

#endif // !defined(AFX_GRAINSFINDER_H__06AD8C44_0D3E_11D8_BED7_D04454C10000__INCLUDED_)
