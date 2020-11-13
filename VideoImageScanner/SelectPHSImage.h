#if !defined(AFX_SELECTPHSIMAGE_H__4BF01B30_A4E1_11D3_A47D_D5D85B532837__INCLUDED_)
#define AFX_SELECTPHSIMAGE_H__4BF01B30_A4E1_11D3_A47D_D5D85B532837__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectPHSImage.h : header file
//

#include "..\Common\datastructs.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectPHSImage dialog

class CSelectPHSImage : public CDialog
{
// Construction
public:
	UINT m_Image;
	CSelectPHSImage(IO_BULK_PhotoSeq *pphs, CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectPHSImage();

// Dialog Data
	//{{AFX_DATA(CSelectPHSImage)
	enum { IDD = IDD_SELECT_PHS_IMAGE };
	UINT	m_TotalImages;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectPHSImage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectPHSImage)
	afx_msg void OnDeltaPosImageSpin(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	IO_BULK_PhotoSeq *pPhS;
	BITMAPINFO * pBitmapInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTPHSIMAGE_H__4BF01B30_A4E1_11D3_A47D_D5D85B532837__INCLUDED_)
