#if !defined(AFX_EDITCONFIG_H__81527C40_7E26_11D3_A47C_9BC8A49A4326__INCLUDED_)
#define AFX_EDITCONFIG_H__81527C40_7E26_11D3_A47C_9BC8A49A4326__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

#define USE_MIDL_INCOMPATIBLE_STRUCTS
#include "..\Common\CameraSpec.h"
#include "..\Common\CameraSpec2.h"

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

class CEditConfig : public CDialog
{
// Construction
public:
	bool GetSpec(CameraSpec2 &C);
	bool SetSpec(CameraSpec2 C);
	CEditConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	UINT	m_Width;
	UINT	m_Height;
	UINT	m_WinWidth;
	UINT	m_WinHeight;
	UINT	m_Left;
	UINT	m_Top;
	float	m_PixelToMicronX;
	float	m_PixelToMicronY;
	float	m_RefractiveShrinkage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditConfig)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__81527C40_7E26_11D3_A47C_9BC8A49A4326__INCLUDED_)
