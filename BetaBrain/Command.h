#if !defined(AFX_COMMAND_H__C77F9FA7_0A84_4B11_855E_29A3B3B80E13__INCLUDED_)
#define AFX_COMMAND_H__C77F9FA7_0A84_4B11_855E_29A3B3B80E13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Command.h : header file
//

#include "CommandCodes.h"

/////////////////////////////////////////////////////////////////////////////
// CCommand dialog

class CCommand : public CDialog
{
// Construction
public:
	CCommand(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCommand)
	enum { IDD = IDD_COMMAND_CODE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommand)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommand)
	afx_msg void OnClusterDump();
	afx_msg void OnPhotoSeq();
	afx_msg void OnScanTracks();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMAND_H__C77F9FA7_0A84_4B11_855E_29A3B3B80E13__INCLUDED_)
