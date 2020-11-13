// Mover.h: interface for the CMover class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVER_H__BBBBBDBB_4AB5_4E1C_816E_0DAB182FB690__INCLUDED_)
#define AFX_MOVER_H__BBBBBDBB_4AB5_4E1C_816E_0DAB182FB690__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "FogDefinitions.h"
#include "FogInit.h"
#include "MoverDlg.h"

class CMoverDlg;

struct SScanningParam
{
	int MaxLightValue;
	float ConfidenceEmulsionWidth;
	float ConfidenceUpperInterval;
	float ConfidenceLowerInterval;
	float Step;
	float Velocity;
	float SpeedX,SpeedY,SpeedZ;
	float AccX,AccY,AccZ;
	UINT WaitTime;
};

#ifndef FOG_HOME
class CMover  
{
public:
public: // Methods
	void GetPos(float &X,float &Y,float &Z){UpdatePos();X = mCurrentX; Y = mCurrentY; Z = mCurrentZ;};
	void GetZeta(float &Z){UpdateZeta();Z = mCurrentZ;};
	void Mover();
	CMover(SScanningParam * pParam,void (*pShowGrid)(float,bool));
	virtual ~CMover();
	int EnableStageMonitor(bool enable);
	void Light(int & ToSetOrGet,bool Set = FOG_SET/*true*/);
	int MoveTo(float X, float Y,float SpeedX = FOG_DEF_SPEED/*0*/, float SpeedY = FOG_DEF_SPEED/*0*/,int WaitTime = FOG_WAITTIME_AUTOMATIC/*0x70000000*/,bool Wait = FOG_DONTWAIT/*false*/);
	static int SMoveTo(void * pContext,float X,float Y,float SpeedX = FOG_DEF_SPEED/*0*/, float SpeedY = FOG_DEF_SPEED/*0*/,int WaitTime = FOG_WAITTIME_AUTOMATIC/*0x70000000*/,bool Wait = FOG_WAIT/*true*/);
	int MoveZTo(float NewPosZ,float SpeedZ = FOG_DEF_SPEED/*0*/,int WaitTime = FOG_WAITTIME_AUTOMATIC/*0x70000000*/,int XYWaitTime = 0);
	static int SMoveZTo(void * pContext,float NewPosZ,float SpeedZ = FOG_DEF_SPEED/*0*/,int WaitTime = FOG_WAITTIME_AUTOMATIC/*0x70000000*/,int XYWaitTime = 0);
//	int PrecisionMoveZTo(int Increment,float SpeedZ = FOG_DEF_SPEED,int WaitTime = FOG_WAITTIME_AUTOMATIC);
	void UpdatePos(bool Force = false);
	void UpdateZeta(bool Force = false);
	void (*pFShowGrid)(float,bool);
private:
	float mCurrentZ;
	float mCurrentY;
	float mCurrentX;
	CMoverDlg * mpMoverDlg;
	float mX;
	float mY;
	float mZ;
	bool mXYMoved;
	bool mZetaMoved;
	SScanningParam * mpScanParam;
private: //Methods
	int Messagebox(const char * pChar,int Type = MB_OK);
public:
	SFogInit * pFogInit;
};
#endif // !defined FOG_HOME
#endif // !defined(AFX_MOVER_H__BBBBBDBB_4AB5_4E1C_816E_0DAB182FB690__INCLUDED_)
