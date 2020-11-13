// SelectField.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SelectField.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectField dialog


CSelectField::CSelectField(void (*papply)(void *), void *pcontext, IO_VS_Fragment *pfrag, CWnd* pParent /*=NULL*/)
	: CDialog(CSelectField::IDD, pParent), pApply(papply), pContext(pcontext), pFrag(pfrag)
{
	//{{AFX_DATA_INIT(CSelectField)
	m_Field = 0;
	m_XField = 0;
	m_YField = 0;
	//}}AFX_DATA_INIT
}


void CSelectField::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectField)
	DDX_Text(pDX, IDC_SF_FIELD, m_Field);
	DDX_Text(pDX, IDC_SF_XFIELD, m_XField);
	DDX_Text(pDX, IDC_SF_YFIELD, m_YField);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectField, CDialog)
	//{{AFX_MSG_MAP(CSelectField)
	ON_BN_CLICKED(IDC_SF_HIDE, OnHide)
	ON_BN_CLICKED(IDC_SF_APPLYN, OnApplyN)
	ON_BN_CLICKED(IDC_SF_APPLYPOS, OnApplyPos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectField message handlers

void CSelectField::OnHide() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
}

void CSelectField::OnApplyN() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_Field < pFrag->Fragment.StartView) m_Field = pFrag->Fragment.StartView;
	else if (m_Field >= (pFrag->Fragment.StartView + pFrag->Fragment.CountOfViews)) 
		m_Field = pFrag->Fragment.StartView + pFrag->Fragment.CountOfViews - 1;
	m_XField = pFrag->Fragment.pViews[m_Field - pFrag->Fragment.StartView].TileX;
	m_YField = pFrag->Fragment.pViews[m_Field - pFrag->Fragment.StartView].TileY;
	UpdateData(FALSE);
	pApply(pContext);
}

void CSelectField::OnApplyPos() 
{
	// TODO: Add your control notification handler code here
	int i;
	UpdateData();
	for (i = 0; i < pFrag->Fragment.CountOfViews &&
		(m_XField != pFrag->Fragment.pViews[i].TileX ||
		m_YField != pFrag->Fragment.pViews[i].TileY); i++);
	if (i >= pFrag->Fragment.CountOfViews) m_Field = pFrag->Fragment.StartView;
	else m_Field = i + pFrag->Fragment.StartView;
	m_XField = pFrag->Fragment.pViews[m_Field - pFrag->Fragment.StartView].TileX;
	m_YField = pFrag->Fragment.pViews[m_Field - pFrag->Fragment.StartView].TileY;
	UpdateData(FALSE);
	pApply(pContext);	
}
