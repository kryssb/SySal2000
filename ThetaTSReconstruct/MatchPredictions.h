#if !defined(AFX_MATCHPREDICTIONS_H__5201CCD6_5538_4147_974F_E1A77F9884A3__INCLUDED_)
#define AFX_MATCHPREDICTIONS_H__5201CCD6_5538_4147_974F_E1A77F9884A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatchPredictions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatchPredictions dialog

#include <afxcmn.h>
#include "resource.h"
#include "..\Common\datastructs.h"

typedef void (*MatchColorCallback)(void *, int *);

class CMatchPredictions : public CDialog
{
// Construction
public:	
	CMatchPredictions(MatchColorCallback pmatchcolorcallback, void *pcontext, IO_TS_Reconstruction *ptsrec, IO_DBPred_Tracks *ptracks, CWnd* pParent = NULL);   // standard constructor
	virtual ~CMatchPredictions();

// Dialog Data
	//{{AFX_DATA(CMatchPredictions)
	enum { IDD = IDD_MATCH_PREDICTION };
	CComboBox	m_SYC;
	CComboBox	m_SXC;
	CListCtrl	m_List;
	float	m_SlopeTol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatchPredictions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillList();
	void AssignColorIndices();

	void Match();

	MatchColorCallback pMatchColorCallback;
	void *pContext;
	int ColorBase;
	struct t_Match
	{
		float DSlope;
		TS_Track *pTrack;
		int ColorIndex;		
		} *pMatches;
	IO_TS_Reconstruction *pTSRec;
	IO_DBPred_Tracks *pTracks;	
	CImageList Images;

	// Generated message map functions
	//{{AFX_MSG(CMatchPredictions)
	afx_msg void OnMatch();
	virtual BOOL OnInitDialog();
	afx_msg void OnShuffle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATCHPREDICTIONS_H__5201CCD6_5538_4147_974F_E1A77F9884A3__INCLUDED_)
