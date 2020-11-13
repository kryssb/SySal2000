#if !defined(AFX_FILEINFODLG_H__8AE7BB5C_6E91_4C96_942E_816A9DB07680__INCLUDED_)
#define AFX_FILEINFODLG_H__8AE7BB5C_6E91_4C96_942E_816A9DB07680__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileInfoDlg dialog

#include "GrainFinder.h"


class CFileInfoDlg : public CDialog
{
// Construction
public:
	CFileInfoDlg(CGrainFinder * pGF,CWnd* pParent = NULL);   // standard constructor
	CGrainFinder * m_pGF;

// Dialog Data
	//{{AFX_DATA(CFileInfoDlg)
	enum { IDD = IDD_FILE_INFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileInfoDlg)
	afx_msg void OnBtnGoodness();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	SMip * m_pCurrentMip; // Points to the mip currently displayed on Dialog.
	int m_NumTrack;
	int m_TotalTrack;
public:
	afx_msg void OnBnClickedBtnTrackerPrevious();
	afx_msg void OnBnClickedBtnNext();
	int SetTrackData(void);
	void UpdateValues(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEINFODLG_H__8AE7BB5C_6E91_4C96_942E_816A9DB07680__INCLUDED_)
