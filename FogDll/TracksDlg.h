#if !defined(AFX_TRACKSDLG_H__86BC061E_62A4_413F_BE7D_A9B61A45CD34__INCLUDED_)
#define AFX_TRACKSDLG_H__86BC061E_62A4_413F_BE7D_A9B61A45CD34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TracksDlg.h : header file
//
#include "Tracker.h"

/////////////////////////////////////////////////////////////////////////////
// CTracksDlg dialog

class CTracksDlg : public CDialog
{
// Construction
public:
	LRESULT UpdateTracks(WPARAM wParam,LPARAM lParam);
	SMip * GetTrack(int TrackNumber);
	CWnd * m_pParent;
	SMip ** m_ppTrack;
	int CountTracks(SMip * pmip);
	int SetTrackData(int Sender = 0);
	SMip * m_pCurrentMip;
	int m_NumTrack;
	int m_TotalTrack;
	int mChkShowMip;
	CTracksDlg(SMip ** ppMip,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTracksDlg)
	enum { IDD = IDD_DLG_TRACKS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTracksDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTracksDlg)
	afx_msg void OnBtnTrackerPrevious();
	afx_msg void OnBtnTrackerNext();
	afx_msg void OnChkTracksShow();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBtnTracksDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACKSDLG_H__86BC061E_62A4_413F_BE7D_A9B61A45CD34__INCLUDED_)
