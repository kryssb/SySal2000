// Tracker.h: interface for the CTracker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACKER_H__326A4BC2_C633_4BE4_A5CD_EF56DDEC3AEC__INCLUDED_)
#define AFX_TRACKER_H__326A4BC2_C633_4BE4_A5CD_EF56DDEC3AEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common.h"


#define FOG_DISTANCE_DEFAULT 0
#define FOG_DISTANCE_ISOMETRIC 1
#define FOG_DISTANCE_XY 2
#define FOG_DISTANCE_Z 3

struct SMip
{
	float mx;	// First term of equation x = mx*y + nx
	float nx;	// Second term of equation x = mx*y + nx
	float sigmax;// Standard Deviation of mx
	float my;
	float ny;
	float sigmay;
	float mz;	// First term of equation z = mz*y + nz
	float nz;	// Second term of equation z = mz*y + nz
	float sigmaz;// Standard Deviation of mz
	float GiC;	//	Grains in 100µ
	float md;	// mean distance
	float MeanGap;
	int NGrains;	// Number of Grains associated to Mip
	float MaxZ;
	float MinZ;
	float NomLength;
	float Length;
	float MaxDist;
	float MaxGap;
	float Alfa;
	FogAxe Axe;
	int Zero1;
	int Zero2;
	int Zero3;
	SMip * pNext;// Pointer to next Mip
	SMip * pPrevious;	// Pointer to previous Mip
	SIntGrain pGrains[300];	// Grains belonging to Mip
	SMip * AddNext(SMip * pMip = NULL);
	SMip * LinkNext(SMip * pMip = NULL);
	SMip * Delete(){SMip * pnext = pNext;if(pPrevious)pPrevious->pNext = pNext; pNext->pPrevious = pPrevious;free(this);return pnext;};
	void Load(FILE * loadFile,int Version);
	void Save(FILE * saveFile,int Version);	
public:
	void GetGap();
	SMip * AddNew();
};

typedef SMip * PSMip;

struct STracker
{
	SMicroParameters * pMicPar;
	STrackingInfo * pTrackInfo;
	CWnd * pContext;
	CString * pGrainsFilePath;
	SEmulsionSpace * pEmSpaceUp;
	SEmulsionSpace * pEmSpaceDw;
	CWinThread ** ppThread;
	void (* pShowGrains)(void *, SIntGrain *,int,int);
	void (* pSetInteger)(void *, UINT,int);
//	void (* pShowPicture)(void *,int,UINT,SIntGrain *,int,SMip *);
	void (* pShowPicture)(void *,int);
	void (* pSetDlgItemText)(void *, UINT,const char *);
	void (* pSetFloat)(void *, UINT,float);
	void (* pUpdateShow)(void *,UINT toUpdate);
	void (* pWriteLog)(const char *,const char *);
	IDCS *pIdc;
	char ConName[5];
};


struct SSection
{
	int NGrains;
	float Length;
	SIntGrain ** ppGrains;
//	void AddGrain(SIntGrain * pGrain){*(ppGrains + NGrains++) = pGrain;CheckSpace();};
//	bool CheckSpace();
};

struct SGrainChain
{
	int NGrains;
	SIntGrain ** ppGrains;
	FogAxe axe;
	float mx;	// First term of equation x = mx*y + nx
	float nx;	// Second term of equation x = mx*y + nx
	float sigmax;// Standard Deviation of mx
	float my;	// Analog to mx,mz;
	float ny;	// Analog to nx,nz;
	float sigmay;//Analog to sigmax,sigmaz;
	float mz;	// First term of equation z = mz*y + nz
	float nz;	// Second term of equation z = mz*y + nz
	float sigmaz;// Standard Deviation of mz
	float GiC;	//	Grains in 100µ
	float mdxy;	// Mean Distance
	float MeanGap; // Mean Gap between grains;
	float Alpha;	// xy/z error ratio;
	float MaxGap;
	float MaxDist;
	float Length;
	float NomLength;
	SGrainChain(int block):Block(block),NGrains(0),Allocated(block){ppGrains = (SIntGrain **)calloc(sizeof(SIntGrain *),Block);if(!ppGrains)Allocated = 0;};
	SGrainChain(SMip * pMip);
	bool PushGrain(SIntGrain * pGrain);
	bool PopGrain(int Pos);
	void Join(SGrainChain * pChain,bool Delete = true);
	void Join(SSection * pSection);
	~SGrainChain(){free(ppGrains);};
private:
	int Allocated;
	int Block;
public:
	int FromSections(SSection ** ppSec,int totGrains);
};

struct SChains
{
	int NChains;
	SGrainChain ** ppChains;
	SChains():NChains(0),Allocated(10){ppChains = (SGrainChain **)calloc(sizeof(SGrainChain *),10);if(!ppChains)Allocated = 0;};
	~SChains();
	bool PushChain(SGrainChain * pChain);
	bool PopChain(int Pos,bool Delete = true);
	void Join(SChains * pChains);
	void DeleteChains();
private:
	int Allocated;
};

/*struct STrack
{
	FogAxe axe;
	float mx;	// First term of equation x = mx*y + nx
	float nx;	// Second term of equation x = mx*y + nx
	float sigmax;// Standard Deviation of mx
	float my;	// Analog to mx,mz;
	float ny;	// Analog to nx,nz;
	float sigmay;//Analog to sigmax,sigmaz;
	float mz;	// First term of equation z = mz*y + nz
	float nz;	// Second term of equation z = mz*y + nz
	float sigmaz;// Standard Deviation of mz
	float GiC;	//	Grains in 100µ
	float mdxy,mdz;	// mean distance
	SGrainChain * pGrainChain;
};*/

struct SSphericals
{
	float Theta,Phi;
	float sinTheta,cosTheta,sinPhi,cosPhi;
	float tanTheta,cotTheta,tanPhi,cotPhi;
	float FactorX,FactorY,FactorZ;
	FogAxe RefAxe;
	void Update(float theta,float phi);
	SSphericals(float theta,float phi);
	SSphericals():Theta(1.570796f),Phi(1.570796f),sinTheta(1.),cosTheta(0.),sinPhi(1.),cosPhi(0.){};
};

struct SEmulsionSections
{
	SEmulsionSpace & Space;
	STracker * pTService;
	SSection * pSections;
	SSection ** ppHostSections;
	int * pIncrements;
	int * pIndexes;
	int NumHostSections;
	SIntGrain ** ppGrains;
	SIntGrain ** ppGrainsX;
	SIntGrain ** ppGrainsY;
	SIntGrain ** ppGrainsZ;
	float * pNewCoordinates;
	int NumHorSections,NumVerSections;
	int AllocatedSections;
	int UsedSections;
	SSphericals Sphericals;
	int * pGroupIndexes;
	float CellXY,CellZ;
	float HalfFieldX,HalfFieldY,HalfFieldZ;
	float BottomZ,UpperZ;
	float CenterZ;
	FogAxe &RefAxe;
	SEmulsionSections(STracker * TC,SEmulsionSpace * pSpace,float Theta,float Phi,float SecSizeXY,float SecSizeZ);
	~SEmulsionSections();
	bool Create(float Theta,float Phi,float cellXY,float cellZ);
	bool Create2(float Theta,float Phi,float dTh,float dPh);
};


class CTracker : public CObject  
{
public://Members;
	STrackingInfo Parameters;
	STracker TP;
	SDistortion m_Distortion;
	PSMip m_pTrackUp;
	PSMip m_pTrackDw;
	SEmulsionSpace m_MidSpace;
	SEmulsionSpace m_TrackSpace;
	SEmulsionSpace m_UpperEdgeSpace;
public://Methods;
	static float Distance(SIntGrain * pGrain,SGrainChain * pMip,int KIND = FOG_DISTANCE_DEFAULT);
	static float Distance(SIntGrain * pGrain,SMip * pMip,int KIND = FOG_DISTANCE_DEFAULT);
	static float Distance0(SIntGrain * pGrain,SMip * pMip,int KIND = FOG_DISTANCE_DEFAULT);
	void SortChains(SChains * pChains);
	SChains m_TrackerChains;
	void ChainToMips(SChains * pChains,SMip * pMips);
	SChains m_Chains;
	int MergeMips(SMip * pMip1,SMip * pMip2);
	bool m_IsTrackingInProgress;
	void ApplyDistortionCorrection(SDistortion Dist,SEmulsionSpace &Space);
	void ApplyDistortionCorrection(SDistortion Dist,SMip * pMip);
	int CommonGrains(SMip * pMip,SMip * pNext);
	int CountTracks(SMip * pmip = NULL);
	void FindLinearCorrection(SDistortion &Dist,SEmulsionSpace &Space);
	void FindGlobalDistortion(SDistortion &Dist);
	int LoadTracks(const char * pPath);
	int SaveMips(const char * Path);
	SEmulsionSpace SelectTrackGrains(SIntGrain gr1,SEmulsionSpace & Space);
	SSection ** SelectTrackGrains(SIntGrain * pGrain, SEmulsionSections & Sections);
	void SearchTrack(SIntGrain * trackGrains,int numGrains,SIntGrain gr1);
	CTracker(STracker *Service = NULL);
	~CTracker();
	int Track3(SEmulsionSpace & Space,SMip * pMips);
	int Track4(SEmulsionSpace & Space);
	int Track5(SEmulsionSpace & Space);
	int Track6(SEmulsionSpace & Space);
	void Track5(SEmulsionSections * pES,float Theta,float Phi,float DeltaTheta,float DeltaPhi,int NumGrains,int RefIUp, int RefIDw);
	void Track31(SEmulsionSections * pESections);
	void Track41(SEmulsionSections * pESections);
	void DeleteMips(SMip * pMips);
	int PurgeChain(SEmulsionSpace * pSpace,SChains * pChains);
	void GetNominalLength(SEmulsionSpace * pSpace,SGrainChain * pChain);
	void GetNominalLength(SEmulsionSpace * pSpace,SMip * pMip);
	void LookForMip(SSection ** ToSearch,SGrainChain ** pGrainChain);
	friend UINT TrackingThread(LPVOID pParam);
	void LinearFit(SGrainChain * pTrack,bool Complete = false);

protected:
	void LinearFit(SMip &mip);
	float Distance(SIntGrain gr1,SIntGrain gr2,SIntGrain gr3,double alfa);
	float DistanceQuad(SIntGrain gr1, SIntGrain gr2, SIntGrain gr3,double alfa);
	float Distance(double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3);
	float Distance(double mx,double nx,double mz,double nz , double p1,double p2,double p3,double alfa);
	float Distance(double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3,double alfa);
	float AngleQuad(SIntGrain &gr1,SIntGrain &gr2);
private:
	SSection ** mppSecs;
	SGrainChain * mpFromSection;
	SMip * DeleteMip(SMip * pmip);
	void SaveMip(SMip * pmip,const char * Path,char mode[]);
	bool RefineTrack2(SEmulsionSpace * pSpace,SGrainChain * pTrack);
	bool RefineTrack4(SEmulsionSpace * pSpace,SGrainChain * pTrack);
	SGrainChain * TrackSection2(SEmulsionSections * pSections,int SectionIndex,FogAxe Axe);
	SGrainChain * TrackSection4(SEmulsionSections * pSections,int SectionIndex,FogAxe Axe);
	void GetSpace(SEmulsionSpace & Space);
public:
	int ToggleGrain(SEmulsionSpace * pSpace,SMip * pMip, SIntGrain * pGrain);
	int GrainChainToMip(SGrainChain * pChain, SMip * pNext);
};

#endif // !defined(AFX_TRACKER_H__326A4BC2_C633_4BE4_A5CD_EF56DDEC3AEC__INCLUDED_)
