// ToolTip.cpp : implementation file
//

#include "stdafx.h"
#include "FogDLL.h"
#include "ToolTip.h"
#include "FogDefinitions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTip dialog


UINT CToolTip::ShowToolTipThread(LPVOID pParam)
{
	int Counter = 0;
	CToolTip & Tip = *((CToolTip *)pParam);
	DWORD result,ExitResult = WAIT_OBJECT_0;
	int WaitTime;
	bool test;
	static bool bMode = true;
	int &cy = Tip.mPos.cy;
	int &cx = Tip.mPos.cx;
	int i,Cx,OffsetX,OffsetY;
	int stepy,stepx; 
	DWORD WindowStatus = SWP_SHOWWINDOW | SWP_NOOWNERZORDER | SWP_NOACTIVATE;
	HANDLE ToWaitFor[2] = {Tip.PopToolTip.m_hObject,Tip.UpdatedTip.m_hObject};
	HANDLE ExitOrShow[2] = {Tip.ShowToolTip.m_hObject,Tip.ExitThread.m_hObject};
	while(true)
	{
		WaitTime = 0;
		ExitResult = WaitForMultipleObjects(2,ExitOrShow,false,INFINITE);
		if(ExitResult == WAIT_OBJECT_0 + 1)break;
		while(WaitTime < Tip.mAutoPopTime)
		{
			if(WaitTime == 0)
				if(bMode)
					for(i = 4; i < cy; i += stepy)
					{
						bMode = false;
						stepy = cy/20;
						Tip.SetWindowPos(&wndTopMost,Tip.mPos.x,Tip.mPos.y,cx,i,WindowStatus);
//						Tip.GetDlgItem(IDC_EDT_TOOLTIP_TIP)->Invalidate();
						Sleep(5);
						WaitTime += 5;
					}
				else
					for(i = 4; i < cx; i += stepx)
					{
						bMode = true;
						stepx = cx/20;
						Tip.SetWindowPos(&wndTopMost,Tip.mPos.x,Tip.mPos.y,i,cy,WindowStatus);
//						Tip.GetDlgItem(IDC_EDT_TOOLTIP_TIP)->Invalidate();
						Sleep(5);
						WaitTime += 5;
					}

			Tip.SetWindowPos(&wndTopMost,Tip.mPos.x,Tip.mPos.y,cx,cy,WindowStatus);
//			Tip.GetDlgItem(IDC_EDT_TOOLTIP_TIP)->Invalidate();
			result = WaitForMultipleObjects(2,ToWaitFor,false,100);
			test = Tip.IsMouseOnCaller();
			if(result == WAIT_OBJECT_0 + 1)WaitTime = 1;
			if(!test || result == WAIT_OBJECT_0)break;
			WaitTime += 100;
		}
		Tip.PopToolTip.SetEvent();
		stepx = cx/8;
		Cx = cx;
		OffsetX = 0;
		OffsetY = 0;
		for(i = cy; i > 0; i -= stepy)
		{
			stepy = cy/10;
			Cx -= stepx;
			OffsetX += stepx/2;
			OffsetY += stepy/2;
			Tip.SetWindowPos(&wndTopMost,Tip.mPos.x + OffsetX,Tip.mPos.y + OffsetY,Cx,i,WindowStatus);
//			Tip.GetDlgItem(IDC_EDT_TOOLTIP_TIP)->Invalidate();
			Sleep(5);
			WaitTime += 5;
		}
		Tip.ShowWindow(SW_HIDE);
		Counter++;
	}
	Tip.ShowToolTip.SetEvent();
	return 0;
}

CToolTip::CToolTip(CWnd* pParent /*=NULL*/)
	: CDialog(CToolTip::IDD, pParent),ShowToolTip(false,false),
	UpdatedTip(false,false),PopToolTip(false,false),ExitThread(false,false)
{
	//{{AFX_DATA_INIT(CToolTip)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	mpParent = pParent;
	mAutoPopTime = 5000;
	mWaitTime = 500;
	PopToolTip.SetEvent();
	ShowToolTip.ResetEvent();
	UpdatedTip.ResetEvent();
	ExitThread.ResetEvent();
	m_pWaitThread = AfxBeginThread(ShowToolTipThread,this,THREAD_PRIORITY_NORMAL,50000);
}


void CToolTip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolTip)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolTip, CDialog)
	//{{AFX_MSG_MAP(CToolTip)
	ON_MESSAGE(WM_USER_SHOWTIP,ShowTipM)
	ON_MESSAGE(WM_USER_POPTIP,PopTipM)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTip message handlers

BOOL CToolTip::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
HBRUSH CToolTip::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	static CBrush Yellow((COLORREF)0xe0ffff);
	pDC->SetBkColor((COLORREF)0xe0ffff);
	// TODO: Return a different brush if the default is not desired
	return (HBRUSH)Yellow.m_hObject;
}

LRESULT CToolTip::ShowTipM(WPARAM wParam,LPARAM lParam)
{
	ShowTip((SToolTip *)lParam);
	return NULL;
}

LRESULT CToolTip::PopTipM(WPARAM wParam,LPARAM lParam)
{
	PopTip();
	return NULL;
}

void CToolTip::PopTip()
{
	PopToolTip.SetEvent();
}

bool CToolTip::IsMouseOnCaller()
{
	CPoint Pos;
	CRect CallerRect;
	GetCursorPos(&Pos);
	HWND hW = ::WindowFromPoint(Pos);
/*	pCaller = FromHandle(m_pSTip->hcaller);
	pCaller->GetWindowRect(&CallerRect);
	
	return CallerRect.PtInRect(Pos);*/
	return hW == m_pSTip->hcaller;
}

bool CToolTip::UpdateTip(SToolTip * pTip)
{
	m_pSTip = pTip;

	UpdatedTip.SetEvent();
	return true;
}

void CToolTip::ShowTip(SToolTip * pTip)
{
	m_pSTip = pTip;
	if(WaitForSingleObject(PopToolTip.m_hObject,0) == WAIT_OBJECT_0)
	{
		if(SetText())ShowToolTip.SetEvent();
		else PopToolTip.SetEvent();
	}
	else
	{
		if(SetText())UpdatedTip.SetEvent();
		else PopToolTip.SetEvent();
	}
}


int CToolTip::SetText()
{
	static WINDOWPLACEMENT ToolTipPlacement;
	ToolTipPlacement.length = sizeof(WINDOWPLACEMENT);
	WINDOWPLACEMENT * pPlacement = &ToolTipPlacement;
	CRect CallerRect;
	CEdit * pEdit = (CEdit *)(GetDlgItem(IDC_EDT_TOOLTIP_TIP));
	CString Text = m_pSTip->pText;
	if(Text.IsEmpty())return 0;
	char OldText[] = "\n";
	char NewText[] = {13,10,0};
	Text.Replace(OldText,NewText);
	pEdit->SetWindowText(Text);
	int LineCount = pEdit->GetLineCount();
	int i,LineWidth,MaxWidth = 0;
	CString text;
	char * pText = text.GetBuffer(52);
	*(pText + 51) = 0;
	for(i = 0; i < LineCount; i++)
	{
		LineWidth = pEdit->GetLine(i,pText,50);
		if(LineWidth > MaxWidth)MaxWidth = LineWidth;
	}
	text.ReleaseBuffer();
	::GetWindowRect(m_pSTip->hcaller,&CallerRect);
	int left = CallerRect.left;
	int top = CallerRect.top;
	CPoint p(m_pSTip->Position);
	int sizex = MaxWidth*5 + 8;
	int sizey = LineCount*13 + 8;
	SPos Pos = {left + p.x,top + p.y + 25,sizex,sizey};
	mPos = Pos;
//	SetWindowPos(&wndTopMost,Pos.x,Pos.y,Pos.cx,Pos.cy,SWP_SHOWWINDOW | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
	return 1;
}












