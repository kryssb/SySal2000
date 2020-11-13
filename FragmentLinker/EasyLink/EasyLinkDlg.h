// EasyLinkDlg.h : header file
//

#if !defined(AFX_EASYLINKDLG_H__634FEF0C_6F46_474B_B1A6_209717C9486B__INCLUDED_)
#define AFX_EASYLINKDLG_H__634FEF0C_6F46_474B_B1A6_209717C9486B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxcmn.h>
#include "..\..\Common\datastructs.h"
#include "..\..\SySalDataIO\SySalDataIO.h"
#include "..\FragmentLinker.h"

/////////////////////////////////////////////////////////////////////////////
// CEasyLinkDlg dialog

class CEasyLinkDlg : public CDialog
{
// Construction
public:
	CEasyLinkDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CEasyLinkDlg();

// Dialog Data
	//{{AFX_DATA(CEasyLinkDlg)
	enum { IDD = IDD_EASYLINK_DIALOG };
	CProgressCtrl	m_Progress;
	CString	m_Catalog;
	CString	m_Output;
	UINT	m_MinPoints;
	float	m_PosTol;
	float	m_SlopeTol;
	float	m_MergePosTol;
	float	m_MergeSlopeTol;
	float	m_MinSlope;
	float	m_Bottom_Ax;
	float	m_Bottom_Ay;
	float	m_Bottom_Bx;
	float	m_Bottom_By;
	float	m_Top_Ax;
	float	m_Top_Ay;
	float	m_Top_Bx;
	float	m_Top_By;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyLinkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEasyLinkDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelCatalog();
	afx_msg void OnSelOutput();
	afx_msg void OnStart();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);

private:
	static UINT LoadCallback(void *pContext, UINT Index, IO_VS_Fragment **ppFrag);
	static UINT SaveCallback(void *pContext, IO_CS_SS_Tracks *pTracks);
	static void ProgressCallback(void *pContext, float Percent);
	static bool StopCallback(void *pContext);

	UINT Thread();
	static UINT ThreadHook(void *pOwner);
	CWinThread * pThread;
	IFragmentLinker * iFL;
	ISySalDataIO * iIO;
	void EnableControls(bool IsRunning);
	bool ShouldStop;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EASYLINKDLG_H__634FEF0C_6F46_474B_B1A6_209717C9486B__INCLUDED_)
