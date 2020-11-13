// Tracker.cpp: implementation of the CTracker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tracker.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


extern CString LogFilePath;
extern CString DebugFilePath;

#include "FogDefinitions.h"
#include "TrackerASMip.cpp"
#include "TrackerASEmulsionSections.cpp"
#include "TrackerATrack3.cpp"
#include "TrackerADistortion.cpp"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTracker * pGT;

CTracker::CTracker(STracker *Service):m_Chains(),m_TrackerChains()
{

	m_pTrackUp = (SMip *)calloc(1,sizeof(SMip));
	m_pTrackDw = (SMip *)calloc(1,sizeof(SMip));
	if(Service != NULL)TP = *Service;
	else
	{
		STracker TContext = {0,0,0,0,0,0,0,0,0,0,0,0};
		TP = TContext;
	}
	if(TP.pTrackInfo == NULL)TP.pTrackInfo = &Parameters;
	else Parameters = *TP.pTrackInfo;
	m_IsTrackingInProgress = false;
	pGT = this;
	mpFromSection = NULL;
	mppSecs = (SSection **)calloc(sizeof(SSection *),9);
}

CTracker::~CTracker()
{
	DeleteMips(m_pTrackUp);
	DeleteMips(m_pTrackDw);
	free(m_pTrackUp);
	free(m_pTrackDw);
	if(mppSecs != NULL)free(mppSecs);
	if(mpFromSection)delete mpFromSection;
}



inline float CTracker::Distance(double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3)
{
	// distanza del punto (c1,c2,c3) dal segmento formato da a e b
	// supponendo la stessa metrica sui tre assi.
	double a12 = a1*a1,a22 = a2*a2,a32 = a3*a3;
	double b12 = b1*b1,b22 = b2*b2,b32 = b3*b3;
	double c12 = c1*c1,c22 = c2*c2,c32 = c3*c3;
	return (float)sqrt(((a12*b22 + a12*b32 - 2*a1*b22*c1 - 2*a1*b32*c1 + b22*c12 + b32*c12 - 2*a12*b2*c2 + 
    2*a1*b1*b2*c2 + 2*a1*b2*c1*c2 - 2*b1*b2*c1*c2 + a12*c22 - 2*a1*b1*c22 + b12*c22 + 
    b32*c22 + a32*(b12 + b22 - 2*b1*c1 + c12 - 2*b2*c2 + c22) - 2*a12*b3*c3 + 
    2*a1*b1*b3*c3 + 2*a1*b3*c1*c3 - 2*b1*b3*c1*c3 - 2*b2*b3*c2*c3 + a12*c32 - 2*a1*b1*c32 + 
    b12*c32 + b22*c32 - 2*a3*(a1*b1*b3 - a1*b3*c1 - b1*b3*c1 + b3*c12 - b2*b3*c2 + b3*c22 - 
       a1*b1*c3 + b12*c3 + b22*c3 + a1*c1*c3 - b1*c1*c3 - b2*c2*c3) + 
    a22*(b12 + b32 - 2*b1*c1 + c12 - 2*b3*c3 + c32) - 
    2*a2*(a3*b2*b3 - b1*b2*c1 + b2*c12 + a1*(b1 - c1)*(b2 - c2) + b12*c2 - a3*b3*c2 + b32*c2 - 
       b1*c1*c2 - a3*b2*c3 - b2*b3*c3 + a3*c2*c3 - b3*c2*c3 + b2*c32))/
  (a12 + a22 + a32 - 2*a1*b1 + b12 - 2*a2*b2 + b22 - 2*a3*b3 + b32)));

}

inline float CTracker::Distance(double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3,double alfa)
{
	// distanza del punto (c1,c2,c3) dal segmento formato da a e b
	// supponendo la metrica {1,1,1/alfa}.
	double UnoSuDenom,cx,cy,cz;
	UnoSuDenom = 1/((a1 - b1)*(a1 - b1) + (a2 - b2)*(a2 - b2) + (a3 - b3)*(a3 - b3));
	cx = a1 - c1 + UnoSuDenom*(a1 - b1)*((a1 - b1)*(-a1 + c1) + (a2 - b2)*(-a2 + c2) + (a3 - b3)*(-a3 + c3));
	cy = a2 - c2 + UnoSuDenom*(a2 - b2)*((a1 - b1)*(-a1 + c1) + (a2 - b2)*(-a2 + c2) + (a3 - b3)*(-a3 + c3));
	cz = (a3 - c3 + UnoSuDenom*(a3 - b3)*((a1 - b1)*(-a1 + c1) + (a2 - b2)*(-a2 + c2) + (a3 - b3)*(-a3 + c3)))*alfa;
	return (float)sqrt(cx*cx + cy*cy + cz*cz);
}

__forceinline float CTracker::DistanceQuad(SIntGrain gr1, SIntGrain gr2, SIntGrain gr3,double alfa)
{
	double a1,a2,a3,b1,b2,b3,c1,c2,c3,cx,cy,cz,UnoSuDen;
	a1 = gr1.x; a2 = gr1.y; a3 = gr1.z; b1 = gr2.x; b2 = gr2.y; b3 = gr2.z;
	c1 = gr3.x; c2 = gr3.y; c3 = gr3.z;
	UnoSuDen = 1/((a1 - b1)*(a1 - b1) + (a2 - b2)*(a2 - b2) + (a3 - b3)*(a3 - b3));
	cx = a1 - c1 + UnoSuDen*(a1 - b1)*((a1 - b1)*(-a1 + c1) + (a2 - b2)*(-a2 + c2) + (a3 - b3)*(-a3 + c3));
	cy = a2 - c2 + UnoSuDen*(a2 - b2)*((a1 - b1)*(-a1 + c1) + (a2 - b2)*(-a2 + c2) + (a3 - b3)*(-a3 + c3));
	cz = (a3 - c3 + UnoSuDen*(a3 - b3)*((a1 - b1)*(-a1 + c1) + (a2 - b2)*(-a2 + c2) + (a3 - b3)*(-a3 + c3)))*alfa;
	 return (float)(cx*cx + cy*cy + cz*cz);
}

inline float CTracker::Distance(double mx,double nx,double mz,double nz , double p1,double p2,double p3,double alfa)
{
	// distanza del punto {p1,p2,p3} dalla retta specificata dai primi quattro parametri
	// assegnando alla coponente z della distanza un peso alfa.
	return (float)sqrt(((nx - p1 + mx*p2)*(nx - p1 + mx*p2) + (mz*mz*((nx - p1)*(nx - p1) + p2*p2) - 
	2*mz*(mx*(nx - p1) - p2)*(nz - p3) + (1 + mx*mx)*(nz - p3)*(nz - p3))*alfa*alfa)/(1 + mx*mx + mz*mz*alfa*alfa));
//	double c1 = ((1 + mz*mz)*(-nx + p1) - mx*p2 + mx*mz*(nz - p3));
//	double c2 = (mx*(nx - p1) + (mx*mx + mz*mz)*p2 + mz*(nz - p3));
//	double c3 = (mz*(mx*nx - mx*p1 - p2) + (1 + mx*mx)*(-nz + p3));
//	double c4 = (1 + mx*mx + mz*mz);
//	return (float)sqrt((c1*c1 + c2*c2 + alfa*alfa*c3*c3)/(c4*c4));
}

inline float CTracker::AngleQuad(SIntGrain &gr1,SIntGrain &gr2)
{
	double x1,y1,z1,x2,y2,z2,mx,mz,UnoSuDen;
	x1 = gr1.x;	y1 = gr1.y; z1 = gr1.z; x2 = gr2.x; y2 = gr2.y; z2 = gr2.z;
	UnoSuDen = 1./(y1 - y2);
	mx = ((-x1 + x2)*UnoSuDen); mz = (-z1 + z2)*UnoSuDen;
	return (float)(mx*mx + mz*mz);
}

inline float CTracker::Distance(SIntGrain gr1, SIntGrain gr2, SIntGrain gr3,double alfa)
{
	static int counter = 0;
	counter++;
	 return Distance(gr1.x,gr1.y,gr1.z,gr2.x,gr2.y,gr2.z,gr3.x,gr3.y,gr3.z,alfa);
}

void CTracker::LinearFit(SMip &mip)
{
	double sx = 0,syz = 0,syx = 0,sx2 = 0,delta;
	double sy = 0,sy2 = 0,s2y = 0,sommax=0;
	double sz = 0,sz2 = 0,s2z = 0,sommaz=0;
	double worker,distances = 0,dist,mx,nx,mz,nz;
	float maxy = -300,miny = 300,maxx = -300,minx = 300,minz = 100000,maxz = -100000;
	int i,size = mip.NGrains;
	static int counter = 0;
	for(i = 0;i < size; i++)
	{
		SIntGrain &grain = *(mip.pGrains + i);
		sy2 += grain.y*grain.y;
		syx += grain.x*grain.y;
		syz += grain.y*grain.z;
		sx += grain.x;
		sy += grain.y;
		sz += grain.z;
		maxy = maxy > grain.y ? maxy : grain.y;
		miny = miny < grain.y ? miny : grain.y;
		maxx = maxx > grain.x ? maxx : grain.x;
		minx = minx < grain.x ? minx : grain.x;
		maxz = maxz > grain.z ? maxz : grain.z;
		minz = minz < grain.z ? minz : grain.z;
	}
	s2y = sy*sy;
	delta = size*sy2-s2y;
	mip.mx = (float)(mx = (size*syx - sx*sy)/delta);
	mip.mz = (float)(mz = (size*syz - sy*sz)/delta);
	mip.nx = (float)(nx = (sy2*sx - sy*syx)/delta);
	mip.nz = (float)(nz = (sy2*sz - sy*syz)/delta);
	for(i = 0;i < size; i++)
	{
		SIntGrain &grain = *(mip.pGrains + i);
		worker = grain.x - mip.nx - mip.mx*grain.y;
		sommax += worker*worker;
		worker = grain.z - mip.nz - mip.mz*grain.y;
		sommaz += worker*worker;
		counter++;
		dist = Distance(mx,nx,mz,nz,grain.x,grain.y,grain.z,Parameters.Alpha);//(0.707*Parameters.ErrorXY/Parameters.ErrorZ));
		distances += dist;
	}
	mip.md = (float)(distances/size);
	mip.sigmax = (float)sqrt(sommax/(size-2));
	mip.sigmaz = (float)sqrt(sommaz/(size-2));
	mip.GiC = ((float)(100*(size - 1)))/((float)sqrt((maxy - miny)*(maxy - miny) + (maxx - minx)*(maxx - minx) + (maxz - minz)*(maxz - minz)));
}



void CTracker::SearchTrack(SIntGrain * trackGrains,int numGrains,SIntGrain gr1)
{
	
}

UINT TrackingThread(LPVOID pParam)
{
	int count;
	CTracker &TT = *((CTracker *)pParam);
	if(TT.TP.pSetInteger)TT.TP.pSetInteger(TT.TP.pContext, TT.TP.pIdc->TotalMips,0);
	SEmulsionSpace * pSpace = TT.TP.pEmSpaceUp;
	STrackingInfo::ETracker Tracker = TT.TP.pTrackInfo->Tracker;
	if(Tracker == STrackingInfo::Tre)
	{
		count = TT.Track3(*pSpace,TT.m_pTrackUp);
		count = TT.Track3(*TT.TP.pEmSpaceDw,TT.m_pTrackDw);
	}
	return 1;
}

void CTracker::DeleteMips(SMip * pMips)
{
	SMip * pMip,* pNext;
	pMip = pMips->pNext;
	if(pMip)
		do
		{
			pNext = pMip->pNext;
			free(pMip);
			pMip = pNext;
		}
		while(pMip != NULL);
	memset(pMips,0,sizeof(SMip));
}



int CTracker::CountTracks(SMip *pmip)
{
	if(pmip == NULL)pmip = m_pTrackUp;
	int count = 0;
	SMip * pMip;
	pMip = pmip;
	while(pMip->pNext != NULL)
	{	count++;
		pMip = pMip->pNext;}
	return count;
}

void CTracker::SaveMip(SMip *pMip2,const char * Path,char mode[])
{
	int count = 0;
	SIntGrain * pGrains = pMip2->pGrains;
	for(int k = 0; k < pMip2->NGrains; k++)
	{
		SIntGrain &gr1 = *(pGrains + k);
		for(int l = k + 1; l < pMip2->NGrains; l++)
		{
			SIntGrain &gr2 = *(pGrains + l);
			if(gr1.xx == gr2.xx && gr1.yy == gr2.yy && gr1.zz == gr2.zz)
			{
				count++;
			}
		}
	}
	if(count > 0)
	{	CString Text;
		Text.Format("Found %d common Grains in Track",count);
		TP.pWriteLog(LogFilePath,Text);	}
	FILE * myfile;
	int i;
	myfile = fopen(Path,mode);
	fprintf(myfile,"%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%d\n",pMip2->mx,pMip2->nx,pMip2->sigmax,pMip2->mz,pMip2->nz,pMip2->sigmaz,pMip2->GiC,pMip2->md,pMip2->NGrains);
	for(i=0;i<120;i++)
	{
		fprintf(myfile,"%f\n",(pMip2->pGrains + i)->x);
		fprintf(myfile,"%f\n",(pMip2->pGrains + i)->y);
		fprintf(myfile,"%f\n",(pMip2->pGrains + i)->z);
		fprintf(myfile,"%f\n",(pMip2->pGrains + i)->zz);
		fprintf(myfile,"%f\n",(pMip2->pGrains + i)->zzz);
		fprintf(myfile,"%f\n",(pMip2->pGrains + i)->xx);
		fprintf(myfile,"%f\n",(pMip2->pGrains + i)->yy);
	}
	fclose(myfile);
}

int CTracker::SaveMips(const char * Path)
{
	int count = 1;
	SMip * pMip = m_pTrackUp;
	pMip = pMip->pNext;
	if(pMip == NULL)
	{
		fclose(fopen(Path,"w"));
		return 0;
	}
	SaveMip(m_pTrackUp,Path,"w");
	while(pMip->pNext != NULL)
	{
		count++;
		SaveMip(pMip,Path,"a");
		pMip = pMip->pNext;
	}
	FILE * myfile = fopen(Path,"a");
	fprintf(myfile,"%g\n%g\n%g\n%g\n%g\n%g\n%g\n",m_Distortion.xzero,m_Distortion.yzero,m_Distortion.A,m_Distortion.B,m_Distortion.R,m_Distortion.a,m_Distortion.b);
	fclose(myfile);
	return count;
}


int CTracker::LoadTracks(const char *pPath)
{
	FILE * InputFile = fopen(pPath,"r");
	if(InputFile == NULL)
	{	MessageBox(TP.pContext->m_hWnd,"Tracker","Error Opening File!",MB_OK);
		return 0;	}
	bool MemoryError = false;
	int size = sizeof(SMip);
	int MaxTrack = 10,TrackPlus = 2;
	SMip * pTrack, * pWt;
	float * Numbers = (float *)malloc(size * MaxTrack);
	if(Numbers == NULL)
	{	MessageBox(TP.pContext->m_hWnd,"Tracker","Memory Error!",MB_OK);
		return 0;	}
	memset(Numbers,0,size * MaxTrack);
	int Index = 0,read = 0;
	read = fscanf(InputFile,"%f",Numbers + Index++);
	while(read == 1)
	{
		if(Index % (size/4) == 8)read = fscanf(InputFile,"%d",(int *)(Numbers + Index++));
		else read = fscanf(InputFile,"%g",Numbers + Index++);
		if(Index % (size/4) == 9)Index += 4;
		if(Index*sizeof(float) == (UINT)(size*MaxTrack))
		{
			MaxTrack += TrackPlus;
			float * NewNumbers = (float *)realloc(Numbers,size*MaxTrack);
			if(NewNumbers != NULL)
			{
				Numbers = NewNumbers;
				memset((SMip *)Numbers + MaxTrack - TrackPlus,0,2*size);
			}
			else
			{	MessageBox(TP.pContext->m_hWnd,"Tracker","Error Allocating Memory!",MB_OK);
				MaxTrack -= TrackPlus;
				MemoryError = true;
				break;
			}
		}
	}
	fclose(InputFile);
	int NumTrack = Index / (120*7 + 9 + 4);
	if(NumTrack < MaxTrack)
	{
		float * NewNumbers = (float *)realloc(Numbers,size * (NumTrack + 1));
		if(NewNumbers != NULL)Numbers = NewNumbers;
	}
	else if(NumTrack == MaxTrack && MemoryError)NumTrack--;
	pTrack = (SMip *)Numbers;
	pTrack->pNext = pTrack + 1;
	pTrack->pPrevious = NULL;
	SMip *pNext = pTrack + 1;
	int i;
	for(i = 1; i < NumTrack; i++)
	{
		pNext->pPrevious = pNext - 1;
		pNext->pNext = pNext + 1;
		pNext = pNext->pNext;
	}
	pNext->pPrevious = pNext - 1;
	if(!MemoryError)
	{
	m_Distortion.xzero = *((float *)pNext + 0);
	m_Distortion.yzero = *((float *)pNext + 1);
	m_Distortion.A = *((float *)pNext + 2);
	m_Distortion.B = *((float *)pNext + 3);
	m_Distortion.R = *((float *)pNext + 4);
	m_Distortion.a = *((float *)pNext + 5);
	m_Distortion.b = *((float *)pNext + 6);
	for(i = 0; i < 8; i++)*((float *)pNext + i) = 0;	}
	else
	{
		m_Distortion = SDistortion(0,0,0,0,0);
		memset(pNext,0,size);
		pNext->pPrevious = pNext - 1;
	}
	pNext = m_pTrackUp;
	for(i = 0; i < NumTrack; i++)
	{
		pWt = (SMip *)calloc(1,size);
		memcpy(pNext,(SMip *)Numbers + i,size);
		pNext->pNext = pWt;
		pNext->pNext->pPrevious = pNext;
		pNext = pNext->pNext;
	}
	free(Numbers);
	if(TP.pSetInteger)TP.pSetInteger(TP.pContext,TP.pIdc->Mips,NumTrack);
	return NumTrack;
}

float CTracker::Distance0(SIntGrain *pGrain, SMip *pMip,int KIND)
{
	float wx,wy,wz,wf1,Add,AlfaQuadro = pMip->Alfa*pMip->Alfa;
	if(KIND == FOG_DISTANCE_ISOMETRIC)AlfaQuadro = 1.f;
	else if(KIND == FOG_DISTANCE_XY)AlfaQuadro = 0.f;
	else if(KIND == FOG_DISTANCE_Z)AlfaQuadro = 1.e24f;
	float nxMenox0,nyMenoy0,nzMenoz0;
	wx = pGrain->x; wy = pGrain->y; wz = pGrain->z;
	nxMenox0 = pMip->nx - wx; nyMenoy0 = pMip->ny - wy; nzMenoz0 = pMip->nz - wz;
	wf1 = pMip->mz*nxMenox0;
	wf1 -= pMip->mx*nzMenoz0;
	Add = wf1*wf1;
	wf1 = pMip->mz*nyMenoy0;
	wf1 -= pMip->my*nzMenoz0;
	Add += wf1*wf1;
	Add *= AlfaQuadro;
	wf1 = pMip->my*nxMenox0;
	wf1 -= pMip->mx*nyMenoy0;
	Add += wf1*wf1;
	wf1 =  Add/(pMip->mx*pMip->mx + pMip->my*pMip->my + AlfaQuadro*pMip->mz*pMip->mz);
	return (float)sqrt(wf1);
}

float CTracker::Distance(SIntGrain *pGrain, SMip *pMip,int KIND)
{
	float wx,wy,wz,wf1,AlfaQuadro = (pMip->Alfa*pMip->Alfa);
	if(KIND == FOG_DISTANCE_ISOMETRIC)AlfaQuadro = 1.f;
	float f1,f2,f3,UnoSuDen;
	wf1 = pMip->mx*pMip->mx + pMip->my*pMip->my + pMip->mz*pMip->mz*AlfaQuadro;
	UnoSuDen = 1.f/wf1;
	wx = pGrain->x; wy = pGrain->y; wz = pGrain->z;
	f1 = pMip->mx*(pMip->nx - wx); f2 = pMip->my*(pMip->ny - wy); f3 = pMip->mz*(pMip->nz - wz)*AlfaQuadro;
	wx -= (pMip->nx - UnoSuDen*pMip->mx*(f1 + f2 + f3));
	wy -= (pMip->ny - UnoSuDen*pMip->my*(f1 + f2 + f3));
	wz -= (pMip->nz - UnoSuDen*pMip->mz*(f1 + f2 + f3));
	switch(KIND)
	{
	case FOG_DISTANCE_XY :
		wf1 = wx*wx + wy*wy;
		break;
	case FOG_DISTANCE_Z :
		wf1 = wz*wz;
		break;
	case FOG_DISTANCE_ISOMETRIC :
		//wf1 = wx*wx + wy*wy + wz*wz;
		//break;
	case FOG_DISTANCE_DEFAULT :
	default :
		wf1 = wx*wx + wy*wy + AlfaQuadro*wz*wz;
	}
	return (float)sqrt(wf1);
}

float CTracker::Distance(SIntGrain *pGrain, SGrainChain *pMip,int KIND)
{
	float wx,wy,wz,wf1,AlfaQuadro = pMip->Alpha*pMip->Alpha;
	if(KIND == FOG_DISTANCE_ISOMETRIC)AlfaQuadro = 1.f;
	float f1,f2,f3,UnoSuDen;
	wf1 = pMip->mx*pMip->mx + pMip->my*pMip->my + pMip->mz*pMip->mz*AlfaQuadro;
	UnoSuDen = 1.f/wf1;
	wx = pGrain->x; wy = pGrain->y; wz = pGrain->z;
	f1 = pMip->mx*(pMip->nx - wx); f2 = pMip->my*(pMip->ny - wy); f3 = pMip->mz*(pMip->nz - wz)*AlfaQuadro;
	wx -= (pMip->nx - UnoSuDen*pMip->mx*(f1 + f2 + f3));
	wy -= (pMip->ny - UnoSuDen*pMip->my*(f1 + f2 + f3));
	wz -= (pMip->nz - UnoSuDen*pMip->mz*(f1 + f2 + f3));
	switch(KIND)
	{
	case FOG_DISTANCE_XY :
		wf1 = wx*wx + wy*wy;
		break;
	case FOG_DISTANCE_Z :
		wf1 = wz*wz;
		break;
	case FOG_DISTANCE_ISOMETRIC :
	case FOG_DISTANCE_DEFAULT :
		wf1 = wx*wx + wy*wy + wz*wz;
	}
	return (float)sqrt(wf1);
}

int CTracker::ToggleGrain( SEmulsionSpace * pSpace,SMip * pMip,SIntGrain * pGrain)
{
	bool test;
	int i,j;
	SIntGrain * pG, * pGrains = pSpace->pGrains;
	for(i = 0; i < pMip->NGrains; i++)
	{
		pG = pMip->pGrains + i;
        test = (pGrain->xx - pG->xx > -0.001 && pGrain->xx - pG->xx < 0.001);
		if(test)
		{
			test = (pGrain->yy - pG->yy > -0.001 && pGrain->yy - pG->yy < 0.001);
			if(test)
			{
				test = (pGrain->zz - pG->zz > -0.001 && pGrain->zz - pG->zz < 0.001);
			}
		}
		if(test)break;
	}
	if(test)
	{
		for(j = i; j < pMip->NGrains - 1; j++)
		{
			pG = pMip->pGrains + j + 1;
			memcpy(pMip->pGrains + j,pG,sizeof(SIntGrain));
		}
		pMip->NGrains--;
	}
	else
	{
		pG = (pMip->pGrains + pMip->NGrains);
		*pG = *pGrain;
		pMip->NGrains++;
	}

	SMip Mip = *pMip;
	SGrainChain * pChain = new SGrainChain(&Mip);
	LinearFit(pChain,true);
	GetNominalLength(pSpace,pChain);
	GrainChainToMip(pChain,pMip);
	delete pChain;

	return pMip->NGrains;
}

