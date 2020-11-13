// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog


CEditConfig::CEditConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CEditConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditConfig)
	m_Width = 1024;
	m_Height = 1024;
	m_WinWidth = 1024;
	m_WinHeight = 1024;
	m_Left = 0;
	m_Top = 0;
	m_PixelToMicronX = 1.0f;
	m_PixelToMicronY = 1.0f;
	m_RefractiveShrinkage = 1.0f;
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Text(pDX, IDC_EC_WIDTH, m_Width);
	DDV_MinMaxUInt(pDX, m_Width, 1, 2048);
	DDX_Text(pDX, IDC_EC_HEIGHT, m_Height);
	DDV_MinMaxUInt(pDX, m_Height, 1, 2048);
	DDX_Text(pDX, IDC_EC_WINWIDTH, m_WinWidth);
	DDV_MinMaxUInt(pDX, m_WinWidth, 1, 2048);
	DDX_Text(pDX, IDC_EC_WINHEIGHT, m_WinHeight);
	DDV_MinMaxUInt(pDX, m_WinHeight, 1, 2048);
	DDX_Text(pDX, IDC_EC_LEFT, m_Left);
	DDV_MinMaxUInt(pDX, m_Left, 0, 2047);
	DDX_Text(pDX, IDC_EC_TOP, m_Top);
	DDV_MinMaxUInt(pDX, m_Top, 0, 2047);
	DDX_Text(pDX, IDC_EC_PIXELTOMICRONX, m_PixelToMicronX);
	DDX_Text(pDX, IDC_EC_PIXELTOMICRONY, m_PixelToMicronY);
	DDX_Text(pDX, IDC_EC_REFSHRINK, m_RefractiveShrinkage);
	DDV_MinMaxFloat(pDX, m_RefractiveShrinkage, 1.f, 3.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

bool CEditConfig::SetSpec(CameraSpec2 C)
{
	m_Width = C.Width;
	m_Height = C.Height;
	m_WinWidth = C.WinWidth;
	m_WinHeight = C.WinHeight;
	m_Left = C.OffX;
	m_Top = C.OffY;
	m_PixelToMicronX = C.PixelToMicronX;
	m_PixelToMicronY = C.PixelToMicronY;
	m_RefractiveShrinkage = C.RefractiveShrinkage;
	return true;
}

bool CEditConfig::GetSpec(CameraSpec2 &C)
{
	C.Width = m_Width;
	C.Height = m_Height;
	C.WinWidth = m_WinWidth;
	C.WinHeight = m_WinHeight;
	C.OffX = m_Left;
	C.OffY = m_Top;
	C.PixelToMicronX = m_PixelToMicronX;
	C.PixelToMicronY = m_PixelToMicronY;	
	C.RefractiveShrinkage = m_RefractiveShrinkage;
	return true;
}

void CEditConfig::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if (m_WinWidth > m_Width) 
	{
		MessageBox("Window Width cannot be larger than Image Width", "Config Error", MB_ICONWARNING | MB_OK);
		return;
		};
	if (m_WinHeight > m_Height) 
	{
		MessageBox("Window Height cannot be larger than Image Height", "Config Error", MB_ICONWARNING | MB_OK);
		return;
		};
	if ((m_Left + m_WinWidth) > m_Width)
	{
		MessageBox("Window Width + Window Left must be smaller than Image Width", "Config Error", MB_ICONWARNING | MB_OK);
		return;
		};
	if ((m_Top + m_WinHeight) > m_Height)
	{
		MessageBox("Window Height + Window Top must be smaller than Image Height", "Config Error", MB_ICONWARNING | MB_OK);
		return;
		};
	if (m_PixelToMicronX == 0.f) 
	{
		MessageBox("X Pixel Size cannot be 0", "Config Error", MB_ICONWARNING | MB_OK);
		return;
		};
	if (m_PixelToMicronY == 0.f) 
	{
		MessageBox("Y Pixel Size cannot be 0", "Config Error", MB_ICONWARNING | MB_OK);
		return;
		};
	CDialog::OnOK();
}
