// PhotoSeq.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PhotoSeq.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhotoSeq dialog


CPhotoSeq::CPhotoSeq(float *_pPosX, float *_pPosY, float *_pStartDepth, float *_pEndDepth,
		UINT *_pFrames, UINT *_pXSize, UINT *_pYSize, Identifier *_pID, CWnd* pParent /*=NULL*/)
	: CDialog(CPhotoSeq::IDD, pParent), pPosX(_pPosX), pPosY(_pPosY), pStartDepth(_pStartDepth), 
		pEndDepth(_pEndDepth), pFrames(_pFrames), pXSize(_pXSize), pYSize(_pYSize), pID(_pID)
{
	//{{AFX_DATA_INIT(CPhotoSeq)
	*pEndDepth = 0.0f;
	*pFrames = 21;
	pID->Part[0] = 0;
	pID->Part[1] = 0;
	pID->Part[2] = 0;
	pID->Part[3] = 0;
	*pPosX = 0.0f;
	*pPosY = 0.0f;
	*pStartDepth = 0.0f;
	*pXSize = 256;
	*pYSize = 256;
	//}}AFX_DATA_INIT
}


void CPhotoSeq::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPhotoSeq)
	DDX_Text(pDX, IDC_PSI_ENDDEPTH, *pEndDepth);
	DDX_Text(pDX, IDC_PSI_FRAMES, *pFrames);
	DDV_MinMaxUInt(pDX, *pFrames, 1, 1000);
	DDX_Text(pDX, IDC_PSI_ID0, pID->Part[0]);
	DDX_Text(pDX, IDC_PSI_ID1, pID->Part[1]);
	DDX_Text(pDX, IDC_PSI_ID2, pID->Part[2]);
	DDX_Text(pDX, IDC_PSI_ID3, pID->Part[3]);
	DDX_Text(pDX, IDC_PSI_POSX, *pPosX);
	DDX_Text(pDX, IDC_PSI_POSY, *pPosY);
	DDX_Text(pDX, IDC_PSI_STARTDEPTH, *pStartDepth);
	DDX_Text(pDX, IDC_PSI_XSIZE, *pXSize);
	DDV_MinMaxUInt(pDX, *pXSize, 64, 4096);
	DDX_Text(pDX, IDC_PSI_YSIZE, *pYSize);
	DDV_MinMaxUInt(pDX, *pYSize, 64, 4096);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPhotoSeq, CDialog)
	//{{AFX_MSG_MAP(CPhotoSeq)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhotoSeq message handlers

