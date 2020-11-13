// Mover.cpp: implementation of the CMover class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mover.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern bool ScanningAvailable;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMover::CMover(SScanningParam * pParam,void (*pShowGrid)(float,bool))
{
	pFShowGrid = pShowGrid;
	mpScanParam = pParam;
	mXYMoved = true;
	mZetaMoved = true;
	mpMoverDlg = NULL;
}

CMover::~CMover()
{
	if(mpMoverDlg)
	{
		if(mpMoverDlg->m_hWnd)mpMoverDlg->DestroyWindow();
		delete mpMoverDlg;
	}
}


int CMover::Messagebox(const char * pChar,int Type)
{
	return MessageBox(NULL,pChar,"Scanner",Type);
}

int CMover::MoveTo(float X,float Y,float SpeedX,float SpeedY,int WaitTime,bool Wait)
{
	int result;
	float speedx = SpeedX;
	float speedy = SpeedY;
	if(speedx == 0)speedx = mpScanParam->SpeedX;
	if(speedy == 0)speedy = mpScanParam->SpeedY;
	float AccX = mpScanParam->AccX;
	float AccY = mpScanParam->AccY;
	if(pFogInit->iSt2)result = (int)(pFogInit->iSt2->PosMove(0,X,speedx,AccX));
	if(pFogInit->iSt2)result = (int)(pFogInit->iSt2->PosMove(1,Y,speedy,AccY));
	else result = 0;
	if(WaitTime == FOG_WAITTIME_AUTOMATIC)
	{
		if(mXYMoved)UpdatePos();
		int waitTimex = (int)(((mCurrentX - X)/speedx)*1000 + 20);
		int waitTimey = (int)(((mCurrentY - Y)/speedy)*1000 + 20);
		if(waitTimex < 0)waitTimex *= -1;
		if(waitTimey < 0)waitTimey *= -1;
		WaitTime = waitTimex;
		if(WaitTime < waitTimey)WaitTime = waitTimey;
	}
	if(Wait)Sleep(WaitTime);
	mXYMoved = true;
	return WaitTime;
}

int CMover::SMoveTo(void * pContext,float X,float Y,float SpeedX,float SpeedY,int WaitTime,bool Wait)
{
	return ((CMover *)pContext)->MoveTo(X,Y,SpeedX,SpeedY,WaitTime,Wait);
}

int CMover::SMoveZTo(void * pContext,float NewPosZ,float SpeedZ,int WaitTime,int XYWaitTime)
{
	return ((CMover *)pContext)->MoveZTo(NewPosZ,SpeedZ,WaitTime,XYWaitTime);
}

//int CMover::PrecisionMoveZTo(int Increment,float SpeedZ,int WaitTime)
//{
//	int result = 0;
//	float speedz = SpeedZ;
//	if(speedz == 0)speedz = mpScanParam->SpeedZ;
//	if(pFogInit->iSt2)
//		result = (int)(pFogInit->iSt2->ZPrecisionMove(50,speedz,mpScanParam->AccZ));
//	if(WaitTime == FOG_WAITTIME_AUTOMATIC)
//	{
//		WaitTime = Increment*40;
//		if(WaitTime < 0)WaitTime *= -1;
//		WaitTime += 150;
//	}
//	if(WaitTime > 0)Sleep(WaitTime);
//	mZetaMoved = true;
//	return result;
//}

int CMover::MoveZTo(float NewPosZ,float SpeedZ,int WaitTime,int XYWaitTime)
{
//	BYTE * pImage;
	int result = 0;
	float speedz = SpeedZ;
	if(speedz == 0)speedz = mpScanParam->SpeedZ;
	if(pFogInit->iSt2)result = (int)(pFogInit->iSt2->PosMove(2,NewPosZ,speedz,mpScanParam->AccZ));
	if(WaitTime == FOG_WAITTIME_AUTOMATIC)
	{
		WaitTime = (int)(((mCurrentZ - NewPosZ)/speedz)*1000);
		if(WaitTime < 0)WaitTime *= -1;
		WaitTime += 150;
	}
	if(WaitTime < XYWaitTime)WaitTime = XYWaitTime;
	if(WaitTime > 0)Sleep(WaitTime);
	mZetaMoved = true;
	return result;
}

void CMover::UpdatePos(bool Force)
{
//	HRESULT ResX,ResY,ResZ;
//	float X,Y,Z;
	if(pFogInit->iSt2)
	{
		if(mXYMoved || Force)
		{
			/*ResX = */pFogInit->iSt2->GetPos(0,&mCurrentX);
			/*ResY = */pFogInit->iSt2->GetPos(1,&mCurrentY);
		}
		if(mZetaMoved || Force)
			/*ResZ = */pFogInit->iSt2->GetPos(2,&mCurrentZ);
	}
	mXYMoved = false;
	mZetaMoved = false;
}

void CMover::UpdateZeta(bool Force)
{
	if(pFogInit->iSt2 && (mZetaMoved || Force))pFogInit->iSt2->GetPos(2,&mCurrentZ);
	mZetaMoved = false;
}



int CMover::EnableStageMonitor(bool enable)
{
	int result = 0;
	if(pFogInit->iStOb && pFogInit->iSt2)
	{
		result = pFogInit->iStOb->EnableMonitor(enable);
		if(enable)pFogInit->iSt2->EnableManualControl(enable);
	}
	return result;
}

void CMover::Light(int & ToSetOrGet,bool Set)
{
	if(pFogInit->iSt2)
	{
		if(pFogInit->iSt2 && Set)
		{
			if(ToSetOrGet > MAX_MICROSCOPE_LIGHT)ToSetOrGet = MAX_MICROSCOPE_LIGHT - 200;
			if(ToSetOrGet < 0)ToSetOrGet = 0;
			pFogInit->iSt2->SetLight(ToSetOrGet);
		}
		else
		{
			pFogInit->iSt2->GetLight(&ToSetOrGet);
		}
	}
}


void CMover::Mover()
{
	CMoverDlg * pMover = mpMoverDlg;
	if(pMover == NULL)
	{
		pMover = new CMoverDlg(&mpMoverDlg,this);
		if(pMover == NULL)
		{
			Messagebox("Mover is Anavailable");
		}
		else
		{
			mpMoverDlg = pMover;
			pMover->Create(IDD_DLG_MOVER);
			pMover->ShowWindow(true);
			pMover->SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		}
	}
	else
	{
		pMover->SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}
}



