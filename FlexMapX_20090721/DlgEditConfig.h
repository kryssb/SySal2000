#if !defined(AFX_EDITCONFIG_H__8881B473_731B_49B2_aC5B_605325FB6AFF__INCLUDED_)
#define AFX_EDITCONFIG_H__8881B473_731B_49B2_aC5B_605325FB6AFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditConfig.h : header file
//

#include "FlexMapData.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEditConfig dialog

class CDlgEditConfig : public CDialog
{
// Function Members (Methods)
public:
	CDlgEditConfig(CWnd* pParent = NULL);   // standard constructor

   void GetConfig(FlexMapData &F);
	void SetConfig(FlexMapData &F);

protected:
   // Overrides [ClassWizard generated virtual function overrides]
	//{{AFX_VIRTUAL(CDlgEditConfig)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

   // Implementation
	// Generated message map functions
	//{{AFX_MSG(CDlgEditConfig)
	afx_msg void OnSelRecoveryFile();
	afx_msg void OnLeaveFIRString();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   
// Data Members
public:
	// Dialog Data
	//{{AFX_DATA(CDlgEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };

	float	    m_HorizTolerance           ;
	float	    m_LongDistAcc              ;
	float	    m_LongDistSpeed            ;
	CString	 m_RecoveryFileName         ;
	BOOL	    m_SheetIsRotatedBy180Deg   ;
	float	    m_ShortDistAcc             ;
	float	    m_ShortDistSpeed           ;
	float	    m_TimeOut                  ;
	float	    m_VertTolerance            ;
	float	    m_VertAcc                  ;
	float	    m_ZSetSpeed                ;
	BOOL	    m_SearchFirstMark          ;
	float	    m_TotalThickness           ;
	UINT	    m_BinningSize              ;
	CString	 m_FIRString                ;
	float	    m_GreyLevelSampleFraction  ;
	float	    m_StripSamplingDistance    ;
	UINT	    m_MaxStripCandidates       ;
	UINT	    m_StripPeakThreshold       ;
	float	    m_ScanTransverseTolerance  ;
	UINT	    m_SettlingTime             ;
	float	    m_StripWidth               ;

	float     m_FramesPerSecond          ;
	unsigned  m_ClusteringParameter      ;
	unsigned  m_MaxClusters              ;
	float     m_Diameter                 ;
	float     m_DiameterTolerance        ;
	float     m_MaxEllipticity           ;
	float     m_FocusSpeed               ;
	float     m_FocusStroke              ;
	float     m_CenterTolerance          ;

	BOOL      m_ForceLateralMark         ;

   BOOL      m_PauseIfCloneNotFound     ;
	//}}AFX_DATA
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__8881B473_731B_49B2_aC5B_605325FB6AFF__INCLUDED_)
