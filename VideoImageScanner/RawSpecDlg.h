#if !defined(AFX_RAWSPECDLG_H__5BB83445_7E92_11D3_A47C_D38D47D98121__INCLUDED_)
#define AFX_RAWSPECDLG_H__5BB83445_7E92_11D3_A47C_D38D47D98121__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RawSpecDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRawSpecDlg dialog

class CRawSpecDlg : public CDialog
{
// Construction
public:
	CRawSpecDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRawSpecDlg)
	enum { IDD = IDD_RAW_SPECIFICATIONS };
	UINT	m_Height;
	UINT	m_Width;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRawSpecDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRawSpecDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAWSPECDLG_H__5BB83445_7E92_11D3_A47C_D38D47D98121__INCLUDED_)
