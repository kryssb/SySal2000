// ScanMapDetails.cpp : implementation file
//

#include "stdafx.h"
#include "ScanMapDetails.h"


// CScanMapDetails dialog

IMPLEMENT_DYNAMIC(CScanMapDetails, CDialog)

double CScanMapDetails::m_MinX = 0.0;
double CScanMapDetails::m_MaxX = 0.0;
double CScanMapDetails::m_MinY = 0.0;
double CScanMapDetails::m_MaxY = 0.0;
double CScanMapDetails::m_MinS = 0.05;
double CScanMapDetails::m_MaxS = 0.4;
int CScanMapDetails::m_MinGrains = 8;

CScanMapDetails::CScanMapDetails(CWnd* pParent /*=NULL*/)
	: CDialog(CScanMapDetails::IDD, pParent)	
{

}

CScanMapDetails::~CScanMapDetails()
{
}

void CScanMapDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SM_MINX, m_MinX);
	DDX_Text(pDX, IDC_SM_MAXX, m_MaxX);
	DDX_Text(pDX, IDC_SM_MINY, m_MinY);
	DDX_Text(pDX, IDC_SM_MAXY, m_MaxY);
	DDX_Text(pDX, IDC_SM_MINS, m_MinS);
	DDV_MinMaxDouble(pDX, m_MinS, 0, 1);
	DDX_Text(pDX, IDC_SM_MAXS, m_MaxS);
	DDV_MinMaxDouble(pDX, m_MaxS, 0, 1);
	DDX_Text(pDX, IDC_SM_MINGRAINS, m_MinGrains);
	DDV_MinMaxInt(pDX, m_MinGrains, 0, 100);
}


BEGIN_MESSAGE_MAP(CScanMapDetails, CDialog)
	ON_BN_CLICKED(IDOK, &CScanMapDetails::OnBnClickedOk)
END_MESSAGE_MAP()


// CScanMapDetails message handlers

void CScanMapDetails::OnBnClickedOk()
{
	if (UpdateData()) OnOK();
}
