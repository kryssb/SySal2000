#if !defined(AFX_SCANTRACKS_H__1565AD46_7713_4ADA_B886_286F897C4C0E__INCLUDED_)
#define AFX_SCANTRACKS_H__1565AD46_7713_4ADA_B886_286F897C4C0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanTracks.h : header file
//

#include "..\Common\Id.h"

/////////////////////////////////////////////////////////////////////////////
// CScanTracks dialog

class CScanTracks : public CDialog
{
// Construction
public:
	CScanTracks(float *_pPosX, float *_pPosY, float *_pSlopeX, float *_pSlopeY,
		float *_pSideSlopeTol, float *_pGlobalSlopeTol, float *_pGoodSlopeTol,
		Identifier *_pID, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScanTracks)
	enum { IDD = IDD_COMMAND_SCANTRACKS };
	float	*pGlobalSlopeTol;
	float	*pGoodSlopeTol;
	Identifier *pID;
	float	*pPosX;
	float	*pPosY;
	float	*pSideSlopeTol;
	float	*pSlopeX;
	float	*pSlopeY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanTracks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanTracks)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANTRACKS_H__1565AD46_7713_4ADA_B886_286F897C4C0E__INCLUDED_)
