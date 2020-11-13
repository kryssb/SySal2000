// ClusterDump.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ClusterDump.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClusterDump dialog


CClusterDump::CClusterDump(float *_pPosX, float *_pPosY, float *_pStartDepth, float *_pEndDepth, 
	UINT *_pFrames, UINT *_pThreshold, Identifier *_pID, CWnd* pParent /*=NULL*/)
	: CDialog(CClusterDump::IDD, pParent), pPosX(_pPosX), pPosY(_pPosY), pStartDepth(_pStartDepth),
	pEndDepth(_pEndDepth), pFrames(_pFrames), pThreshold(_pThreshold) 
{
	//{{AFX_DATA_INIT(CClusterDump)
	*pEndDepth = 0.0f;
	*pFrames = 41;
	pID->Part[0] = 0;
	pID->Part[1] = 0;
	pID->Part[2] = 0;
	pID->Part[3] = 0;
	*pPosX = 0.0f;
	*pPosY = 0.0f;
	*pStartDepth = 0.0f;
	*pThreshold = 10;
	//}}AFX_DATA_INIT
}


void CClusterDump::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClusterDump)
	DDX_Text(pDX, IDC_CDI_ENDDEPTH, *pEndDepth);
	DDX_Text(pDX, IDC_CDI_FRAMES, *pFrames);
	DDV_MinMaxUInt(pDX, *pFrames, 1, 1000);
	DDX_Text(pDX, IDC_CDI_ID0, pID->Part[0]);
	DDX_Text(pDX, IDC_CDI_ID1, pID->Part[1]);
	DDX_Text(pDX, IDC_CDI_ID2, pID->Part[2]);
	DDX_Text(pDX, IDC_CDI_ID3, pID->Part[3]);
	DDX_Text(pDX, IDC_CDI_POSX, *pPosX);
	DDX_Text(pDX, IDC_CDI_POSY, *pPosY);
	DDX_Text(pDX, IDC_CDI_STARTDEPTH, *pStartDepth);
	DDX_Text(pDX, IDC_CDI_THRESHOLD, *pThreshold);
	DDV_MinMaxUInt(pDX, *pThreshold, 1, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClusterDump, CDialog)
	//{{AFX_MSG_MAP(CClusterDump)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClusterDump message handlers
