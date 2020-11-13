// MicroParametersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "MicroParametersDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMicroParametersDlg dialog


CMicroParametersDlg::CMicroParametersDlg(SMicroParameters * pMicPar,CWnd* pParent /*=NULL*/)
	: CDialog(CMicroParametersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMicroParametersDlg)
	m_CCDWidth = 0;
	m_CCDLength = 0;
	m_PixelLength = 0.0f;
	//}}AFX_DATA_INIT
	m_CCDLength = 2*pMicPar->HalfCCDLength;
	m_CCDWidth = 2*pMicPar->HalfCCDWidth;
	m_PixelLength = pMicPar->PixLen;
	m_pMicPar = pMicPar;
}


void CMicroParametersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMicroParametersDlg)
	DDX_Text(pDX, IDC_EDT_MICPAR_CCDWIDTH, m_CCDWidth);
	DDX_Text(pDX, IDC_EDT_MICPAR_CCDLENGTH, m_CCDLength);
	DDX_Text(pDX, IDC_EDT_MICPAR_PIXELLENGTH, m_PixelLength);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMicroParametersDlg, CDialog)
	//{{AFX_MSG_MAP(CMicroParametersDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMicroParametersDlg message handlers

void CMicroParametersDlg::OnOK() 
{
	UpdateData();
	m_pMicPar->HalfCCDLength = m_CCDLength/2;
	m_pMicPar->HalfCCDWidth = m_CCDWidth/2;
	m_pMicPar->PixLen = m_PixelLength;
	m_pMicPar->InvPixLen = 1.f/m_PixelLength;
	CDialog::OnOK();
}
