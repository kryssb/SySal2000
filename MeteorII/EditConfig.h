#if !defined(AFX_EDITCONFIG_H__C865CC3E_E281_47E0_8A47_04048AEAC2D1__INCLUDED_)
#define AFX_EDITCONFIG_H__C865CC3E_E281_47E0_8A47_04048AEAC2D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

#include "resource.h"
#include <afxcmn.h>
#include "MeteorIIData.h"
#include "MeteorIIClass.h"

class CEditConfig : public CDialog
{
// Construction
public:
	CEditConfig(CMeteorII &m, CWnd* pParent = NULL);   // standard constructor

	t_ExtendedOperation m_XOP;
	t_VisionProcessorLibrary m_ProgLib;

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	CComboBox	m_KWidth;
	CComboBox	m_KHeight;
	CTabCtrl	m_ProgTab;
	CListCtrl	m_XOP_Copy_List;
	UINT	m_XOP_Copy_Dest_H;
	UINT	m_XOP_Copy_Dest_L;
	UINT	m_XOP_Copy_Dest_T;
	UINT	m_XOP_Copy_Dest_W;
	UINT	m_XOP_Copy_Src_H;
	UINT	m_XOP_Copy_Src_L;
	UINT	m_XOP_Copy_Src_T;
	UINT	m_XOP_Copy_Src_W;
	int		m_Cutoff;
	UINT	m_MaxProcessors;
	int		m_K00;
	int		m_K01;
	int		m_K02;
	int		m_K03;
	int		m_K10;
	int		m_K11;
	int		m_K12;
	int		m_K13;
	int		m_K20;
	int		m_K21;
	int		m_K22;
	int		m_K23;
	int		m_K30;
	int		m_K31;
	int		m_K32;
	int		m_K33;
	UINT	m_OffX;
	UINT	m_OffY;
	UINT	m_WinHeight;
	UINT	m_WinWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableOtherProgramItems(bool bEnable);
	void EnableKernel();
	void FillBaseProgram();
	void ReadProgram(int index);
	void WriteProgram(int index);
	void SyncList();

	// Generated message map functions
	//{{AFX_MSG(CEditConfig)
	afx_msg void OnXopCopyAdd();
	afx_msg void OnXopCopyCopy();
	afx_msg void OnXopCopyDel();
	afx_msg void OnXopCopySet();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangingProgTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelChangeProgTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelChangeProgKHeight();
	afx_msg void OnSelChangeProgKWidth();
	afx_msg void OnProgramNew();
	afx_msg void OnProgramRemove();
	virtual void OnOK();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CMeteorII &M;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__C865CC3E_E281_47E0_8A47_04048AEAC2D1__INCLUDED_)
