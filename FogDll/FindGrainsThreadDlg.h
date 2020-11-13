#if !defined(AFX_FINDGRAINSTHREADDLG_H__3F070561_670A_42F0_9352_0B92194286E2__INCLUDED_)
#define AFX_FINDGRAINSTHREADDLG_H__3F070561_670A_42F0_9352_0B92194286E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindGrainsThreadDlg.h : header file
//
#include "GrainFinder.h"
/////////////////////////////////////////////////////////////////////////////
// CFindGrainsThreadDlg dialog

	
class CFindGrainsThreadDlg : public CDialog
{
// Construction
public:
	int m_RealSize;
	char * m_pFiles;
	int m_Frames; // Number of frames of the file specified in File Path Edit Box.
	int m_FileDirectory;
	int m_Color;
	UINT m_Options;
	SGFContext * pGFC;
	CFindGrainsThreadDlg(SGFContext * pgfc,CWnd* pParent = NULL);   // standard constructor
	~CFindGrainsThreadDlg(){if(m_pFiles != NULL){free(m_pFiles); m_pFiles = NULL;}};
	bool m_InvertXY;

// Dialog Data
	//{{AFX_DATA(CFindGrainsThreadDlg)
	enum { IDD = IDD_FINDGRAINSTHREAD };
	BOOL	m_ShowGrains;
	BOOL	m_ShowPicture;
	BOOL	m_SaveGrains;
	BOOL	m_SelectFrames;
	CString	m_FilePath;
	int		m_LastFrame;
	int		m_StartFrame;
	BOOL	m_ShowTracks;
	BOOL	m_bTrack;
	BOOL	m_ShowGrid;
	BOOL	m_ParentParam;
	BOOL	m_SaveTxt;
	BOOL	m_FindGrains;
	BOOL	m_SaveTables;
	CString	m_TablesPostFix;
	BOOL	m_Fog2000;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindGrainsThreadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindGrainsThreadDlg)
	virtual void OnOK();
	afx_msg void OnCheckShowgrains();
	afx_msg void OnCheckOnoff();
	afx_msg void OnButtonBrowse();
	afx_msg void OnRadioColor();
	afx_msg void OnRadioFileDirectory();
	afx_msg void OnCheckSelectframes();
	virtual BOOL OnInitDialog();
	afx_msg void OnBSetTrackerParam();
	afx_msg void OnKillfocusEditThreadstartframe();
	afx_msg void OnKillfocusEditThreadlastframe();
	afx_msg void OnCheckParent();
	afx_msg void OnButtonSetgfparam();
	afx_msg void OnCckSavetable();
	afx_msg void OnBtnFgthreadOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool CheckFile();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDGRAINSTHREADDLG_H__3F070561_670A_42F0_9352_0B92194286E2__INCLUDED_)
