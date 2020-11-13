#if !defined(AFX_CLUSTERANALYSIS_H__8EA9C443_7E6A_11D3_A47C_9FAC8C19CD20__INCLUDED_)
#define AFX_CLUSTERANALYSIS_H__8EA9C443_7E6A_11D3_A47C_9FAC8C19CD20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClusterAnalysis.h : header file
//

#include "ImageWnd.h"
#include "..\Common\ClusterFinder.h"
#include "..\Common\Objective.h"
#include "..\Common\IO.h"
#include "ums.h"
#include "..\Common\datastructs.h"

/////////////////////////////////////////////////////////////////////////////
// CClusterAnalysis dialog

class CClusterAnalysis : public CDialog
{
// Construction
public:
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	virtual  ~CClusterAnalysis();
	CClusterAnalysis(HWND *phwnd, ISySalDataIO *iio, IClusterFinder *icl, IObjective *iob, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClusterAnalysis)
	enum { IDD = IDD_CLUSTER_ANALYSIS };
	UINT	m_MinSize;
	UINT	m_MaxSize;
	UINT	m_Threshold;
	UINT	m_Iterations;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClusterAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HWND * phWnd;
	bool LoadPHSImage(IO_Data *pData);
	bool LoadBMPImage(CString &FileName);
	bool LoadRAWImage(CString &FileName);
	bool SaveBMPImage(CString &FileName);
	bool SaveRAWImage(CString &FileName);
	void UpdateZoom();
	bool SaveImage(CString &FileName);
	int MaxNumber;
	Cluster * pSpace;
	bool LoadImage(CString &FileName);
	BYTE * pSecBits;
	BYTE * pPrimBits;
	BITMAPINFO * pSecBMPInfo;
	BITMAPINFO *pPrimBMPInfo;
	ISySalDataIO *iIO;
	IClusterFinder *iCl;
	IObjective *iOb;
	CImageWnd * pSecondaryImage;
	CImageWnd * pPrimaryImage;
	COLORREF WhiteColor;
	COLORREF BlackColor;
	bool EnableEq;
	bool ShowClusters;

	// Generated message map functions
	//{{AFX_MSG(CClusterAnalysis)
	afx_msg void OnBlackWhite();
	afx_msg void OnCustomColors();
	afx_msg void OnDumpClusters();
	afx_msg void OnDumpHistogram();
	afx_msg void OnFindClusters();
	afx_msg void OnGrayScale();
	afx_msg void OnInvGrayScale();
	afx_msg void OnLoadImage();
	afx_msg void OnSaveImage();
	afx_msg void OnShowClusters();
	afx_msg void OnToggleEqualization();
	afx_msg void OnWhiteBlack();
	virtual BOOL OnInitDialog();
	afx_msg void OnWhiteColor();
	afx_msg void OnBlackColor();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnLoadImageIO();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLUSTERANALYSIS_H__8EA9C443_7E6A_11D3_A47C_9FAC8C19CD20__INCLUDED_)
