#if !defined(AFX_SCANNERMANAGERDLG_H__742BF617_D410_4FAF_9D20_26C022E05350__INCLUDED_)
#define AFX_SCANNERMANAGERDLG_H__742BF617_D410_4FAF_9D20_26C022E05350__INCLUDED_

#include "FogScanningStructs.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScannerManagerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScannerManagerDlg dialog

class CScannerManagerDlg : public CDialog
{
// Construction
public:
	int m_StartPrediction;
	void SaveScanning(CString * pFile);
	void LoadScanning(CString * pFile,bool resume = false);
	int m_PointNumber;
	void SetScanningPoint(SScanningPoint * pScanningPoint);
	int m_Count;
	SScanningPoint * m_pScanningPoint;// Punta all'  ultimo scanning point visualizzato o registrato.
	SGFContext * m_pGFC;
	SScanningPoint * m_pNewScanningPoint;
	SScanningPoint m_ScanningPoint;
	CScannerManagerDlg(SGFContext * pGFC,CWnd* pParent = NULL);   // standard constructor
	void ClearAllScanningPoint();
	~CScannerManagerDlg(){ClearAllScanningPoint();};
// Dialog Data
	//{{AFX_DATA(CScannerManagerDlg)
	enum { IDD = IDD_DLG_SCANNER };
	CString	m_Directory;
	CString	m_FileName;
	int		m_NumStepX;
	int		m_NumStepY;
	float	m_StepY;
	float	m_X;
	float	m_StepX;
	float	m_Y;
	int		m_StartStepX;
	int		m_StartStepY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScannerManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScannerManagerDlg)
	afx_msg void OnBtnScanmanAddpoint();
	afx_msg void OnBtnScanmanDelpoint();
	afx_msg void OnBtnScanmanGrainfinder();
	afx_msg void OnBtnScanmanMicro();
	afx_msg void OnBtnScanmanOptions();
	afx_msg void OnBtnScanmanTracker();
	afx_msg void OnBtnScanmanNext();
	afx_msg void OnBtnScanmanPrevious();
	afx_msg void OnBtnScanmanMovetopoint();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnBtnScanmanUpdatep();
	afx_msg void OnBtnScanmanLoad();
	afx_msg void OnBtnScanmanSave();
	afx_msg void OnBtnScanmanClearall();
	afx_msg void OnBtnScanmanMover();
	afx_msg void OnBtnScamanScanopt();
	afx_msg void OnBtnScanmanResume();
	afx_msg void OnScanbatchSavesingleframe();
	afx_msg void OnBtnScanmanSaveimage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANNERMANAGERDLG_H__742BF617_D410_4FAF_9D20_26C022E05350__INCLUDED_)
