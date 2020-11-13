// ExWinThread.cpp : implementation file
//

#include "stdafx.h"
#include "videoimagescanner.h"
#include "ExWinThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExWinThread

IMPLEMENT_DYNCREATE(CExWinThread, CWinThread)

CExWinThread::CExWinThread()
{
}

CExWinThread::CExWinThread(AFX_THREADPROC pThreadProc, LPVOID pVoid) : CWinThread(pThreadProc, pVoid)
{
}

CExWinThread::~CExWinThread()
{
}

BOOL CExWinThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CExWinThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CExWinThread, CWinThread)
	//{{AFX_MSG_MAP(CExWinThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExWinThread message handlers

void CExWinThread::RegisterMsgHandler(HWND hNewWnd)
{
	m_hDefWnd = hNewWnd;
}

BOOL CExWinThread::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->hwnd == NULL)
	{
		MSG NewMsg = *pMsg;
		NewMsg.hwnd = m_hDefWnd;
		return CWinThread::PreTranslateMessage(&NewMsg);
		};
	return CWinThread::PreTranslateMessage(pMsg);
}

