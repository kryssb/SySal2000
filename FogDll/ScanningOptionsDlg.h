#if !defined(AFX_SCANNINGOPTIONSDLG_H__B21E62DB_7BEF_4BE6_9C1A_D65BF05D1417__INCLUDED_)
#define AFX_SCANNINGOPTIONSDLG_H__B21E62DB_7BEF_4BE6_9C1A_D65BF05D1417__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanningOptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScanningOptionsDlg dialog

class CScanningOptionsDlg : public CDialog
{
// Construction
public:
	CScanningOptionsDlg(UINT * pOptions,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScanningOptionsDlg)
	enum { IDD = IDD_DLG_SCAN_OPTIONS };
	BOOL	m_FindGrains;
	BOOL	m_SaveGrains;
	BOOL	m_SaveImages;
	BOOL	m_SaveTables;
	BOOL	m_SaveTxt;
	BOOL	m_ShowGrains;
	BOOL	m_ShowGrid;
	BOOL	m_ShowPicture;
	BOOL	m_ShowTracks;
	BOOL	m_Track;
	BOOL	m_CorrectDistortion;
	BOOL	m_SaveGrainTable;
	BOOL	m_SaveTrackTable;
	BOOL	m_ParentParameters;
	BOOL	m_EnableOversampling;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanningOptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT * m_pOptions;
	// Generated message map functions
	//{{AFX_MSG(CScanningOptionsDlg)
	virtual void OnOK();
	afx_msg void OnChkScanoptShowGrains();
	virtual BOOL OnInitDialog();
	afx_msg void OnChkSaveTables();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANNINGOPTIONSDLG_H__B21E62DB_7BEF_4BE6_9C1A_D65BF05D1417__INCLUDED_)
