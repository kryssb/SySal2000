#if !defined(AFX_CLUSTERDUMP_H__B3C2F29A_F441_4BBF_AE24_84023108F5A3__INCLUDED_)
#define AFX_CLUSTERDUMP_H__B3C2F29A_F441_4BBF_AE24_84023108F5A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClusterDump.h : header file
//

#include "..\Common\id.h"

/////////////////////////////////////////////////////////////////////////////
// CClusterDump dialog

class CClusterDump : public CDialog
{
// Construction
public:
	CClusterDump(float *_pPosX, float *_pPosY, float *_pStartDepth, float *_pEndDepth, 
	UINT *_pFrames, UINT *_pThreshold, Identifier *_pID, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClusterDump)
	enum { IDD = IDD_COMMAND_CLUSTERDUMP };
	float	*pEndDepth;
	UINT	*pFrames;
	Identifier *pID;
	float	*pPosX;
	float	*pPosY;
	float	*pStartDepth;
	UINT	*pThreshold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClusterDump)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClusterDump)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLUSTERDUMP_H__B3C2F29A_F441_4BBF_AE24_84023108F5A3__INCLUDED_)
