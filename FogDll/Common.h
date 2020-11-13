

#define NOT_USED_DEPTH 100000.f

#include <math.h>

#ifndef __COMMON_FOG_INCLUDED

#define __COMMON_FOG_INCLUDED

typedef unsigned char byte;
#include "FogDefinitions.h"

enum FogAxe
{
	NOAXE, XAXE, YAXE, ZAXE
};
//int CGrainFinder::compare(const void *elem1, const void *elem2)
int CompareIntGrainXD(const void * elem1,const void * elem2);
int CompareIntGrainXA(const void * elem1,const void * elem2);
int CompareIntGrainYD(const void * elem1,const void * elem2);
int CompareIntGrainYA(const void * elem1,const void * elem2);
int CompareIntGrainZD(const void * elem1,const void * elem2);
int CompareIntGrainZA(const void * elem1,const void * elem2);

int CompareIntGrainPointerXD(const void * elem1,const void * elem2);
int CompareIntGrainPointerXA(const void * elem1,const void * elem2);
int CompareIntGrainPointerYD(const void * elem1,const void * elem2);
int CompareIntGrainPointerYA(const void * elem1,const void * elem2);
int CompareIntGrainPointerZD(const void * elem1,const void * elem2);
int CompareIntGrainPointerZA(const void * elem1,const void * elem2);


struct Vector 
{ 
	float x ;
	float y ; 
	float z ;
	Vector() {};
	Vector(float X,float Y,float Z) : x(X), y(Y),z(Z) {};
	Vector(POINT pt,float Z) : x((float)pt.x),y((float)pt.y),z(Z) {};
	Vector(Vector pt1,Vector pt2): x(pt2.x - pt1.x),y(pt2.y - pt1.y),z(pt2.z - pt1.z) {}; 
//	Vector(SIntGrain gr1):x(gr1.x),y(gr1.y),z(gr1.z){};
//	Vector(SIntGrain gr1,SIntGrain gr2):x(gr2.x - gr1.x),y(gr2.y - gr1.y),z(gr2.z - gr1.z){};
	Vector Normalize(){float mod = this->Module();return Vector(x/mod,y/mod,z/mod);};
	float Module() { return (float)sqrt(x*x + y*y + z*z);};
	float Distance(Vector B){return Vector(*this,B).Module();};
	float TgY(){ float tx = x/y,tz = z/y; return (float)sqrt(tx*tx + tz*tz);}
	float Cos(Vector A){float product = x*A.x + y*A.y + z*A.z; return product/(Module()*A.Module());};
	//double Module() ;

};
	inline float operator*(Vector A,Vector B)
		{  return A.x*B.x+A.y*B.y+A.z*B.z;	};

	inline Vector operator*(float A,Vector B)
		{  return Vector(A*B.x,A*B.y,A*B.z);	};

	inline Vector operator*(Vector A,float B)
		{  return Vector(B*A.x,B*A.y,B*A.z);	};

	
	inline Vector operator-(Vector A)
		{	return Vector(-A.x,-A.y,-A.z);	};

	inline Vector operator+(Vector A,Vector B)
		{  return Vector(A.x+B.x,A.y+B.y,A.z+B.z);	};

	inline Vector operator-(Vector A,Vector B)
		{  return Vector(A.x-B.x,A.y-B.y,A.z-B.z);	};



struct SGrainFinderParameters
{
	int MaxImagesOffset;
	int CellSize;
	int Delta;
	int XOffset;
	int YOffset;
	int Threshold;
	bool RealSize;
	bool ThreeFrames;
	bool Statistics;
	bool Differential;
	bool InvertXY;
};

struct SMicroParameters
{
	float PixLen; // Pixel Length
	float InvPixLen; // Inverse Pixel Lenght
	int	HalfCCDWidth;
	int HalfCCDLength;
	float XStageCoordinate;
	float YStageCoordinate;
	float ZStageCoordinate;
	SMicroParameters():PixLen(0.304688f),InvPixLen(3.28204f),HalfCCDWidth(512),HalfCCDLength(640),XStageCoordinate(0),
		YStageCoordinate(0.f),ZStageCoordinate(0.f){};
};

struct IDCS
{
	UINT Minimo,Medio,Massimo,Frame,StaticLocalGrains,LocalGrains,SeeMip,TotalGrains,Mips,TotalMips,Depth;
};

struct SSheet
{
	int Brick;
	int Sheet;
	float Mark1X,Mark1Y,Mark2X,Mark2Y,Mark3X,Mark3Y,Mark4X,Mark4Y;
//	float Mark5X,Mark5Y,Mark6X,Mark6Y;
};

struct SDistortion
{
	double xzero;
	double yzero;
	double A;
	double B;
	double R;
	double a;
	double b;
	SDistortion(double x,double y,double a,double b,double r):xzero(x),yzero(y),A(a),B(b),R(r),a(0),b(0){};
	SDistortion(): xzero(-13.),yzero(-2),A(-0.00005),B(-0.0000000003),R(0.00000001),a(0),b(0){};
};

struct SMinimum
{
	BYTE alfa;BYTE b1;BYTE b2;BYTE b4;BYTE b5;short int x;short int y; BYTE z;BYTE *p;
	SMinimum(BYTE B1,BYTE B2,BYTE Alfa,BYTE B4,BYTE B5,int X,int Y,int Z,BYTE * P):b1(B1),b2(B2),b4(B4),b5(B5),alfa(Alfa),x(X),y(Y),z(Z),p(P) {};
	SMinimum():alfa(0),b1(0),b2(0),b4(0),b5(0),x(0),y(0),z(0),p(0){};
};

struct SIntGrain
{
	float x;float y;float z; float zz;float zzz;float xx;float yy;
	SIntGrain(float X, float Y, float Z,SDistortion * pDistortion = NULL):
	x(X),y(Y),z(Z),zz(Z),zzz(Z),xx(X),yy(Y)
	{	if(pDistortion)
		{	SDistortion &Dist = *pDistortion;
			double A = Dist.A,B = Dist.B, R = Dist.R,x0 = Dist.xzero,y0 = Dist.yzero;
			double deltax = xx - x0, deltay = yy - y0,r;
			r = deltax * deltax + deltay * deltay;
			x = xx + (float)(R * deltax * r);
			y = yy + (float)(R * deltay * r);
			z = zz + (float)(- A*r - B*r*r);	}};
	SIntGrain():x(0),y(0),z(0),zz(0),zzz(0),yy(0),xx(0){};
	SIntGrain(Vector * pVector,SDistortion * pDistortion = NULL)
	{
		*this = SIntGrain(pVector->x,pVector->y,pVector->z,pDistortion);
	}
};




	inline Vector operator-(SIntGrain A,SIntGrain B)
		{  return Vector(A.x-B.x,A.y-B.y,A.z-B.z);	};

	inline bool operator == (SIntGrain A,SIntGrain B)
		{	return A.x == B.x && A.y == B.y && A.z == B.z && 
		A.xx == B.xx && A.yy == B.yy && A.zz == B.zz && A.zzz == B.zzz;	};


struct SLongGrain
{
	short x,y,z,Min,Mean,Max,PrevMin,PrevMean,PrevMax,NextMin,NextMean,NextMax,
	PrevMinPos,NextMinPos;
	SLongGrain(){};
	SLongGrain(int X,int Y,int Z,int min,int mean,int max,int PMin,int NMin,int PMean,int NMean,
		int PMax, int NMax,int PMinP,int NMinP/*,int PMaxP,int NMaxP*/):x(X),y(Y),z(Z),Min(min),
		Mean(mean),Max(max),PrevMin(PMin),NextMin(NMin),PrevMean(PMean),
		NextMean(NMean),PrevMax(PMax),NextMax(NMax),PrevMinPos(PMinP),
		NextMinPos(NMinP)/*,PrevMaxPos(PMaxP),NextMaxPos(NMaxP)*/ {};
};

struct SGrain
{
	unsigned long x : 11,y : 11; // Indicano la posizione logica nell' immagine.
	long DeltaPrevMean : 5,DeltaNextMean : 4,NewType : 1;

	long  DeltaPrevMax : 7,DeltaNextMax : 7;
	unsigned long Mean : 7, Max : 7;
	unsigned long PrevMinPos : 4; 
	
	unsigned long z : 8;// Indica il frame a partire da 0.
	unsigned long NextMinPos : 4,DeltaPrevMin : 6, DeltaNextMin : 6 ,Min : 8;
//
//	unsigned char PrevMaxPos : 4, NextMaxPos : 4;

// x y z Min Mean Max DeltaPrevMin DeltaNextMin DeltaPrevMean DeltaNextMean DeltaPrevMax
// DeltaNextMax PrevMinPos NextMinPos NextMaxPos PrevMaxPos

	SGrain():x(0),y(0),z(0),Min(0),Mean(0),Max(0),DeltaPrevMin(0),DeltaNextMin(0),
		DeltaPrevMean(0),DeltaNextMean(0),DeltaPrevMax(0),DeltaNextMax(0),PrevMinPos(0),
		NextMinPos(0)/*,PrevMaxPos(0),NextMaxPos(0)*/ {};
	SGrain(int X,int Y,int Z,int min,int mean,int max,int DPMin,int DNMin,int DPMean,int DNMean,
		int DPMax, int DNMax,int PMinP,int NMinP/*,int PMaxP,int NMaxP*/):x(X),y(Y),z(Z),Min(min),
		Mean(mean),Max(max),DeltaPrevMin(DPMin),DeltaNextMin(DNMin),DeltaPrevMean(DPMean),
		DeltaNextMean(DNMean),DeltaPrevMax(DPMax),DeltaNextMax(DNMax),PrevMinPos(PMinP),
		NextMinPos(NMinP)/*,PrevMaxPos(PMaxP),NextMaxPos(NMaxP)*/ {};
	SGrain(SIntGrain *pGrain,float *pDepths,float *AMatrix)
	{
		int i;
		float InvPixLen = 1.f / *AMatrix;
		x = (unsigned long)(pGrain->xx*InvPixLen + 512);
		y = (unsigned long)(pGrain->yy*InvPixLen + 512);
		float zzz = pGrain->zzz;
		for(i = 0; i < 128; i++)if(*(AMatrix + i) == zzz)break;
		z = i;
	};
	void ToLongGrain(SLongGrain &Lg);
	SGrain(SLongGrain &L);
	void ToIntGrain(SIntGrain *Grain,float * pDepths,SMicroParameters * pMic,bool Invert,SDistortion *pDistortion = NULL)
	{	float X,Y,Z,xx = (float)x,yy = (float)y,HalfCCDW = (float)pMic->HalfCCDWidth,HalfCCDL = (float)pMic->HalfCCDLength;
	//	X = (xx - HalfCCDW)*(*AMatrix) + (yy - HalfCCDL)*(*(AMatrix + 1)) + *(AMatrix + 2);
	//	Y = (xx - HalfCCDW)*(*(AMatrix + 3)) + (yy - HalfCCDL)*(*(AMatrix + 4)) + *(AMatrix + 5);
		int eta = 1;
		if(Invert){float temp = HalfCCDL; HalfCCDL = HalfCCDW; HalfCCDW = temp; eta = -1;}
		X = eta*(xx - HalfCCDL)*(pMic->PixLen) /*+ (yy - HalfCCDL)*(*(AMatrix + 1))*/ ;//+ pMic->XStageCoordinate;
		Y = /*(xx - HalfCCDW)*(*(AMatrix + 3))*/ + eta*(HalfCCDW - yy)*(pMic->PixLen) ;//+ pMic->YStageCoordinate;
		Z = *(pDepths + z);
		if(Invert){float temp = X; X = Y; Y = temp; }
		Grain->xx = X; Grain->yy = Y; Grain->zzz = Z;
		double b1 = Min + DeltaPrevMin,b2 = Min, b3 = Min + DeltaNextMin;
		double f1 = *(pDepths + z - 1),f2 = *(pDepths + z), f3 = *(pDepths + z + 1);
		float result = (float)( ((b2 - b3)*f1*f1 - (b1 - b3)*f2*f2 + (b1 - b2)*f3*f3)/
			  (2*((b2 - b3)*f1 - (b1 - b3)*f2 + (b1 - b2)*f3)));
		bool Check = false;
		if(fabs(result - f2) > 5.)ASSERT(FALSE);
		if(Check)
		{
			if(result < -NOT_USED_DEPTH||result > NOT_USED_DEPTH)
				result = (float)f3;
			unsigned int Indeterminate = 4290772992;
			unsigned int Inf0 = 2139095040;
			unsigned int Ind = *((unsigned int *)(&result));
			if(Indeterminate == Ind || Ind == Inf0)
			{
				BYTE wByte = 255;
				float wFloat;
				if(wByte > b1)wByte = (byte)b1,wFloat = (float)f1;
				if(wByte > b2)wByte = (byte)b2,wFloat = (float)f2;
				if(wByte > b3)wByte = (byte)b3,wFloat = (float)f3;
				result = wFloat;
			}
			if(Ind == Inf0)
				MessageBox(NULL,"Infinito","SGrain",MB_OK);
		}
		Grain->zz = result;
		if(pDistortion)
		{	SDistortion &Dist = *pDistortion;
			double A = Dist.A,B = Dist.B, R = Dist.R,x0 = Dist.xzero,y0 = Dist.yzero;
			double deltax = X - x0, deltay = Y - y0,r;
			r = deltax * deltax + deltay * deltay;
			Grain->x = X + (float)(R * deltax * r);
			Grain->y = Y + (float)(R * deltay * r);
			Grain->z = result + (float)(- A*r - B*r*r);	}	};
};




struct STrackingInfo
{
	float MaxAngle;		// Angolo massimo di spread rispetto al piano dell' emulsione.
	float StartAngle;		// Center of Angle distribution
	float MaxGap;	// Distanza massima di due grani in una traccia orizzontale.
	float ErrorXY;// Distanza massima di un grano dalla traccia principale.
	float ErrorZ;
	float Alpha;			// Zeta/XY error ratio 
	float StartTheta;
	float EndTheta;
	float DeltaTheta;
	float StartPhi;
	float EndPhi;
	float DeltaPhi;
	float CellXY;
	float CellZ;
	float Rmax;
	float Rmin;
	float x0max;
	float x0min;
	float y0max;
	float y0min;
	float Amax;
	float Amin;
	float Bmax;
	float Bmin;
	float dx;
	float dy;
	float dR;
	float dA;
	float dB;
	float PipeFactor;
	float LengthFraction;
	int	MinNumber;		// Minimal Number of Grain a Mip should contain.
	int MinLinearDensity;
	enum ETracker {Uno,Due,Tre,Four,Five} Tracker;
	STrackingInfo(float MA,float SA,float MDi, float errorxy,float errorz,int MN):MaxAngle(MA),StartAngle(SA),MaxGap(MDi),ErrorXY(errorxy),MinNumber(MN),ErrorZ(errorz) {Tracker = STrackingInfo::Tre;};
	STrackingInfo():MaxAngle(0.05f),StartAngle(0.0f),MaxGap(50.f),ErrorXY(0.4f),ErrorZ(0.8f),MinNumber(6)
	{PipeFactor = 2.0f; x0min = -90.f; x0max = 90.f; dx = 15.f;
	y0min = -80.f;y0max = 80.f; dy = 15.f; Rmin = -0.0000003f;
	Rmax = 0.0000003f; dR = 0.00000002f;Amin = -0.00006f; Amax = -0.000005f; dA = 0.000001f;
	Bmin = (float)-1e-008; Bmax = -1e-009f; dB = 1e-009f; Tracker = Tre;StartTheta = 1.48353f;
	EndTheta = 1.65806f;DeltaTheta = 0.0087266f;StartPhi = 1.48353f;EndPhi = 1.65806f;
	DeltaPhi = 0.0087266f,Alpha = ErrorXY/ErrorZ;
	CellXY = 2/*ErrorXY*PipeFactor/2.f*/;CellZ = 3/*ErrorZ*PipeFactor/2.f*/;MinLinearDensity = 10;LengthFraction = 0.55f;};
	STrackingInfo Set(STrackingInfo s)
	{
		MaxAngle = s.MaxAngle;
		MaxGap = s.MaxGap;
		ErrorXY = s.ErrorXY;
		ErrorZ = s.ErrorZ;
		Alpha = (float)(s.ErrorXY/s.ErrorZ);//s.Alpha;
		MinNumber = s.MinNumber;
		StartAngle = s.StartAngle;
		return s;
	}
public:
	void SetPhiInterval(float StartPhi,float EndPhi);
};


struct SZetaRange
{	float UpperZ;		// Approximately Upper Surface of Emulsion
	float BottomZ;		// Approx Bottom Surface of Emulsion
	float DeadZoneUp; // Approx Upper Surface of middle DeadZone
	float DeadZoneDw; // Approx Bottom Surface of middle DeadZone
	float MaxX,MaxY,MaxZ;
	float MinX,MinY,MinZ;
};


struct SEmulsionSpace
{
	SZetaRange ZetaRange;
	Vector Diagonal;	// {1,-1,1}-{-1,1,-1}
	Vector LowerCorner;	// {-1,1,-1}
	Vector UpperCorner;	// {1,-1,1}
	float	 Volume;	// 8.f
	float	 Density;	// Numero di IntGrain per (10µ)³
	float	 AdjustedDensity;	// Numero di IntGrain per (10µ)³ nella sola emulsione
	int	 NumGrains;		// Number of Grain found
	int	 Allocated;		// Number of Grains allocated
	SDistortion Distortion; // Distortion Corrected
	SIntGrain * pGrains;	// Pointer to Grains
	FogAxe SortAxe;
	SEmulsionSpace(): Density(4.f),pGrains(NULL){memset(this,0,sizeof(SEmulsionSpace));Density=4.f;SortAxe = NOAXE;};
	~SEmulsionSpace(){if(pGrains != NULL)free(pGrains);};
	SEmulsionSpace(SIntGrain * p,int numGrains):NumGrains(numGrains),pGrains(p),SortAxe(NOAXE){};
	void GetSpace();
	float CheckDensity();
//	~SEmulsionSpace(){if(Allocated > 0)free(pGrains);}
public:
	int Purge();
};

struct SDot
{
	int PosX,PosY;
	float SizeX,SizeY,SizeXY,SizeYX;
	float XStage,YStage;
	float SommaX,SommaY,SommaXY,SommaYX;
	int Kind;
	SDot():PosX(0),PosY(0),SizeX(0),SizeY(0),SizeXY(0),SizeYX(0),XStage(0.f),YStage(0.f){SommaX = SommaY = SommaXY = SommaYX = 0;Kind = FOG_DOT_NODOT;};
};

int GetFloat(CWnd * pContext,UINT IDC,float &ToGet);


void SetFloat(CWnd * pContext,UINT IDC,float ToSet,const char * pFormat = NULL);

int GetInteger(void * pContext,UINT IDC,int &ToGet);

int SetInteger(void * pContext,UINT IDC,int ToSet);

void FromFullPathDirectory(CString & FullPath,bool IncludeSlash = false);
void FromFullPathFileName(CString & FullPath);
void ErrorMessage(DWORD Err);
#endif // Not Defined __COMMON_FOG_INCLUDED








