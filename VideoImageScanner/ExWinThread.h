#if !defined(AFX_EXWINTHREAD_H__C22CE0EB_80EA_11D3_A47C_952517505B20__INCLUDED_)
#define AFX_EXWINTHREAD_H__C22CE0EB_80EA_11D3_A47C_952517505B20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExWinThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CExWinThread thread

class CExWinThread : public CWinThread
{
	DECLARE_DYNCREATE(CExWinThread)
protected:
	CExWinThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	CExWinThread(AFX_THREADPROC pThreadProc, LPVOID pVoid);
	void RegisterMsgHandler(HWND hNewWnd);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExWinThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HWND m_hDefWnd;
	virtual ~CExWinThread();

	// Generated message map functions
	//{{AFX_MSG(CExWinThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXWINTHREAD_H__C22CE0EB_80EA_11D3_A47C_952517505B20__INCLUDED_)
