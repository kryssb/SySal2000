#if !defined(AFX_PHOTOSEQ_H__608F1358_7CEC_4485_8780_0675C123D70B__INCLUDED_)
#define AFX_PHOTOSEQ_H__608F1358_7CEC_4485_8780_0675C123D70B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PhotoSeq.h : header file
//

#include "..\Common\Id.h"

/////////////////////////////////////////////////////////////////////////////
// CPhotoSeq dialog

class CPhotoSeq : public CDialog
{
// Construction
public:
	CPhotoSeq(float *_pPosX, float *_pPosY, float *_pStartDepth, float *_pEndDepth,
		UINT *_pFrames, UINT *_pXSize, UINT *_pYSize, Identifier *_pID, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPhotoSeq)
	enum { IDD = IDD_COMMAND_PHOTOSEQ };
	float	*pEndDepth;
	UINT	*pFrames;
	Identifier *pID;
	float	*pPosX;
	float	*pPosY;
	float	*pStartDepth;
	UINT	*pXSize;
	UINT	*pYSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhotoSeq)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPhotoSeq)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHOTOSEQ_H__608F1358_7CEC_4485_8780_0675C123D70B__INCLUDED_)
