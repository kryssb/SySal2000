// ScanTracks.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ScanTracks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScanTracks dialog


CScanTracks::CScanTracks(float *_pPosX, float *_pPosY, float *_pSlopeX, float *_pSlopeY,
		float *_pSideSlopeTol, float *_pGlobalSlopeTol, float *_pGoodSlopeTol,
		Identifier *_pID, CWnd* pParent)
	: CDialog(CScanTracks::IDD, pParent), pPosX(_pPosX), pPosY(_pPosY), pSlopeX(_pSlopeX), 
		pSlopeY(_pSlopeY), pSideSlopeTol(_pSideSlopeTol), pGlobalSlopeTol(_pGlobalSlopeTol), 
		pGoodSlopeTol(_pGoodSlopeTol), pID(_pID) 
{
	//{{AFX_DATA_INIT(CScanTracks)
	*pGlobalSlopeTol = 0.0f;
	*pGoodSlopeTol = 0.0f;
	pID->Part[0] = 0;
	pID->Part[1] = 0;
	pID->Part[2] = 0;
	pID->Part[3] = 0;
	*pPosX = 0.0f;
	*pPosY = 0.0f;
	*pSideSlopeTol = 0.0f;
	*pSlopeX = 0.0f;
	*pSlopeY = 0.0f;
	//}}AFX_DATA_INIT
}


void CScanTracks::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanTracks)
	DDX_Text(pDX, IDC_SCI_GLOBALSLOPETOL, *pGlobalSlopeTol);
	DDV_MinMaxFloat(pDX, *pGlobalSlopeTol, 0.f, 1.f);
	DDX_Text(pDX, IDC_SCI_GOODSLOPETOL, *pGoodSlopeTol);
	DDV_MinMaxFloat(pDX, *pGoodSlopeTol, 0.f, 1.f);
	DDX_Text(pDX, IDC_SCI_ID0, pID->Part[0]);
	DDX_Text(pDX, IDC_SCI_ID1, pID->Part[1]);
	DDX_Text(pDX, IDC_SCI_ID2, pID->Part[2]);
	DDX_Text(pDX, IDC_SCI_ID3, pID->Part[3]);
	DDX_Text(pDX, IDC_SCI_POSX, *pPosX);
	DDX_Text(pDX, IDC_SCI_POSY, *pPosY);
	DDX_Text(pDX, IDC_SCI_SIDESLOPETOL, *pSideSlopeTol);
	DDV_MinMaxFloat(pDX, *pSideSlopeTol, 0.f, 1.f);
	DDX_Text(pDX, IDC_SCI_SLOPEX, *pSlopeX);
	DDX_Text(pDX, IDC_SCI_SLOPEY, *pSlopeY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanTracks, CDialog)
	//{{AFX_MSG_MAP(CScanTracks)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanTracks message handlers
