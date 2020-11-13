// MoverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FogDLL.h"
#include "MoverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int GetFloat(CWnd * pContext,UINT IDC,float &ToGet);
extern void SetFloat(CWnd * pContext,UINT IDC,float ToSet,const char * pFormat = NULL);

/////////////////////////////////////////////////////////////////////////////
// CMoverDlg dialog


CMoverDlg::CMoverDlg(CMoverDlg ** ppThis,CMover * pMover,CWnd* pParent /*=NULL*/)
	: CDialog(CMoverDlg::IDD, pParent),m_XYMover(SButtonParam(this,SOnRightBDXY,SOnLeftBDXY,SOnMouseMoveXY)),
	m_ZMover(SButtonParam(this,SOnRigthBDZ,SOnLeftBDZ,SOnMouseMoveZ))
{
	//{{AFX_DATA_INIT(CMoverDlg)
	m_GridSize = 70.0f;
	//}}AFX_DATA_INIT
	m_ppThis = ppThis;
	m_pMover = pMover;
	m_pMover->GetPos(mX,mY,mZ);
	m_pMover->Light(mLight,FOG_GET);
}

CMoverDlg::~CMoverDlg()
{
//	OnOK();
}

void CMoverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoverDlg)
	DDX_Control(pDX, IDC_BTN_MOVER_XYMOVER, m_XYMover);
	DDX_Text(pDX, IDC_EDT_MOVER_GRIDSIZE, m_GridSize);
	DDV_MinMaxFloat(pDX, m_GridSize, 10.f, 100.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMoverDlg, CDialog)
	//{{AFX_MSG_MAP(CMoverDlg)
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_CAPTURECHANGED()
	ON_BN_CLICKED(IDC_BTN_MOVER_SETLIGHT, OnBtnMoverSetlight)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_CHK_MOVER_SHOWGRID, OnChkMoverShowgrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoverDlg message handlers

BOOL CMoverDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CMoverDlg::SOnLeftBDXY(void *pContext, UINT nFlags, CPoint point)
{
	((CMoverDlg *)pContext)->mButton = XY;
	((CMoverDlg *)pContext)->OnLeftBD(nFlags,point);
}
void CMoverDlg::SOnRightBDXY(void *pContext, UINT nFlags, CPoint point)
{
	((CMoverDlg *)pContext)->mButton = XY;
	((CMoverDlg *)pContext)->OnRightBD(nFlags,point);
}
void CMoverDlg::SOnMouseMoveXY(void *pContext, UINT nFlags, CPoint point)
{
	((CMoverDlg *)pContext)->mButton = XY;
	((CMoverDlg *)pContext)->OnMouseMove(nFlags,point);
}
void CMoverDlg::SOnLeftBDZ(void *pContext, UINT nFlags, CPoint point)
{
	((CMoverDlg *)pContext)->mButton = Z;
	((CMoverDlg *)pContext)->OnLeftBD(nFlags,point);
}
void CMoverDlg::SOnRigthBDZ(void *pContext, UINT nFlags, CPoint point)
{
	((CMoverDlg *)pContext)->mButton = Z;
	((CMoverDlg *)pContext)->OnRightBD(nFlags,point);
}
void CMoverDlg::SOnMouseMoveZ(void *pContext, UINT nFlags, CPoint point)
{
	((CMoverDlg *)pContext)->mButton = Z;
	((CMoverDlg *)pContext)->OnMouseMove(nFlags,point);
}


void CMoverDlg::OnRightBD(UINT nFlags, CPoint point)
{
	switch(mButton)
	{
	case XY :
		AButtonDown = point;
		LButtonDown = point;
		m_pMover->UpdatePos();
		m_pMover->GetPos(mX,mY,mZ);
		break;
	case Z:
		break;
	}

}
void CMoverDlg::OnLeftBD(UINT nFlags, CPoint point)
{
	m_pMover->UpdatePos(true);
	m_pMover->GetPos(mX,mY,mZ);
	AButtonDown = point;
	LButtonDown = point;
	GetFloat(this,IDC_EDT_MOVER_XSTEP,mStepX);
	GetFloat(this,IDC_EDT_MOVER_YSTEP,mStepY);
	GetFloat(this,IDC_EDT_MOVER_ZSTEP,mStepZ);
	switch(mButton)
	{
	case XY :
//		m_XYMover.SetCapture();
		m_XYMover.m_OldPoint = point;
		m_ZMover.m_OldPoint = point;
		mXYMoverCaptured = true;
		mZMoverCaptured = false;
		break;
	case Z:
//		m_ZMover.SetCapture();
		m_ZMover.m_OldPoint = point;
		mZMoverCaptured = true;
		mXYMoverCaptured = false;
		break;
	}
}

void CMoverDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_pMover->pFogInit->iSt2 == NULL)return;
	UINT RButtonIsDown = MK_RBUTTON,LButtonIsDown = MK_LBUTTON,CtrlButtonDown = MK_CONTROL;
	static bool ZMoving = false;
	static CPoint NewPoint;
	bool & zmoving = ZMoving;
	float X,Y,Zed;
	float mstepx = mStepX,mstepy = mStepY;
	if(nFlags & LButtonIsDown)
	{
		int DeltaX;
		int DeltaY;
		float ZVelocity = mStepZ*60;
		switch(mButton)
		{
		case XY :
			if((nFlags & CtrlButtonDown))
			{	
				OnLeftBD(nFlags,m_XYMover.m_OldPoint);
				mstepx /= 10;
				mstepy /= 10;
			}
			if((nFlags & RButtonIsDown)== 0)
			{
				if(zmoving == true)
				{
			/*		zmoving = false;
					m_pMover->UpdatePos();
					m_pMover->GetPos(mX,mY,mZ);
					m_XYMover.m_OldPoint = point;
					DeltaX = m_XYMover.m_OldPoint.x - point.x;
					DeltaY = point.y - m_XYMover.m_OldPoint.y;*/
				}
				m_ZMover.m_OldPoint = point;
				AButtonDown = point;
				m_pMover->UpdatePos();
				m_pMover->GetPos(X,Y,mZ);
				DeltaY = LButtonDown.y - point.y;
				DeltaX = LButtonDown.x - point.x;
				
				float XDistance = mstepx*DeltaX + mX - X;
				float YDistance = - mstepy*DeltaY + mY - Y;
				float XVelocity = 5*XDistance;
				float YVelocity = 5*YDistance;
				if(XVelocity < 0)XVelocity *= -1;
				if(YVelocity < 0)YVelocity *= -1;
				if(XVelocity > 15000)XVelocity = 15000;
				if(YVelocity > 15000)YVelocity = 15000;
				m_pMover->MoveTo(mX + mstepx * DeltaX,mY - mstepy * DeltaY,XVelocity,YVelocity,0,FOG_DONTWAIT);
				SetFloat(this,IDC_EDT_MOVER_XPOSITION,mX + mstepx*DeltaX);
				SetFloat(this,IDC_EDT_MOVER_YPOSITION,mY - mstepy*DeltaY);
				m_XYMover.m_OldPoint = point;
			}
			else
			{
				m_pMover->UpdatePos();
				LButtonDown = point;
				m_pMover->GetPos(mX,mY,Zed);
				DeltaY = AButtonDown.y - point.y;
				float ZetaDistance = mStepZ*DeltaY + mZ - Zed;
				m_XYMover.m_OldPoint = point;
				float ZVelocity = 4*ZetaDistance;
				if(ZVelocity < 0)ZVelocity *= -1;
				if(ZVelocity > 2000.f)ZVelocity = 2000.f;
				m_pMover->MoveZTo(mZ + mStepZ * DeltaY,ZVelocity,0,0);
				SetFloat(this,IDC_EDT_MOVER_ZPOSITION,mZ + mStepZ*DeltaY);
				zmoving = true;
			}
			break;
		case Z:
			DeltaY = m_ZMover.m_OldPoint.y - point.y;
			m_pMover->MoveZTo(mZ + mStepZ * DeltaY,ZVelocity);
			SetFloat(this,IDC_EDT_MOVER_ZPOSITION,mZ + mStepZ * DeltaY);
			break;
		}
	}
}

void CMoverDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	mXYMoverCaptured = false;
	mZMoverCaptured = false;
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CMoverDlg::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	
	mXYMoverCaptured = false;
	mZMoverCaptured = false;	
}

BOOL CMoverDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}

void CMoverDlg::OnOK() 
{
	*m_ppThis = NULL;
//	CDialog::OnOK();

	DestroyWindow();
	delete this;
	
}

void CMoverDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	OnOK();
}

BOOL CMoverDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CSliderCtrl * pSlider = (CSliderCtrl *)GetDlgItem(IDC_SLDR_MOVER_LIGHT);
	pSlider->SetRange(0,MAX_MICROSCOPE_LIGHT - 500);
	
	SetDlgItemText(IDC_EDT_MOVER_XSTEP,"20.0");
	SetDlgItemText(IDC_EDT_MOVER_YSTEP,"20.0");
	SetDlgItemText(IDC_EDT_MOVER_ZSTEP,"2.0");

	m_pMover->UpdatePos();
	m_pMover->GetPos(mX,mY,mZ);
	GetFloat(this,IDC_EDT_MOVER_XPOSITION,mX);
	GetFloat(this,IDC_EDT_MOVER_YPOSITION,mY);
	GetFloat(this,IDC_EDT_MOVER_ZPOSITION,mZ);
	m_pMover->Light(mLight,FOG_GET);
	SetDlgItemInt(IDC_EDT_MOVER_LIGHT,mLight);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMoverDlg::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CDialog::OnCaptureChanged(pWnd);
}

void CMoverDlg::OnBtnMoverSetlight() 
{
	int light = 27000;
	m_pMover->Light(light,FOG_SET/*true*/);
}

void CMoverDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
//	UINT values[9] = {SB_LEFT,SB_ENDSCROLL,SB_LINELEFT,SB_LINERIGHT,SB_PAGELEFT,SB_PAGERIGHT,SB_RIGHT,SB_THUMBPOSITION,SB_THUMBTRACK};
		int j;
		switch(nSBCode)
		{
		case SB_THUMBTRACK :	// SB_THUMBTRACK == 5;
		//	break;
		case SB_THUMBPOSITION : // SB_THUMBPOSITION == 4;
		//	break;
			m_pMover->Light((int &)nPos,FOG_SET);
			SetDlgItemInt(IDC_EDT_MOVER_LIGHT,nPos);
		default :
			break;
		}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMoverDlg::OnChkMoverShowgrid() 
{
	float GridSize;
	int ButtonStatus = ((CButton *)GetDlgItem(IDC_CHK_MOVER_SHOWGRID))->GetCheck();
	GetFloat(this,IDC_EDT_MOVER_GRIDSIZE,GridSize);
	if(GridSize < 1)GridSize = 1;
	(*(m_pMover->pFShowGrid))(GridSize,ButtonStatus == 1);
}























