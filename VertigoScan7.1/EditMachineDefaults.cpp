// EditMachineDefaults.cpp : implementation file
//

#include "stdafx.h"
#include "EditMachineDefaults.h"


// CEditMachineDefaults dialog

IMPLEMENT_DYNAMIC(CEditMachineDefaults, CDialog)

CEditMachineDefaults::CEditMachineDefaults(CWnd* pParent /*=NULL*/)
	: CDialog(CEditMachineDefaults::IDD, pParent)
{

}

CEditMachineDefaults::~CEditMachineDefaults()
{
}

void CEditMachineDefaults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditMachineDefaults)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EMD_XDIGDEC, C.DigXDec);
	DDV_MinMaxInt(pDX, C.DigYDec, -1, 31);
	DDX_Text(pDX, IDC_EMD_YDIGDEC, C.DigYDec);
	DDV_MinMaxInt(pDX, C.DigYDec, -1, 31);
	DDX_Text(pDX, IDC_EMD_XDIGINC, C.DigXInc);
	DDV_MinMaxInt(pDX, C.DigYInc, -1, 31);
	DDX_Text(pDX, IDC_EMD_YDIGINC, C.DigYInc);
	DDV_MinMaxInt(pDX, C.DigYInc, -1, 31);

	DDX_Text(pDX, IDC_EMD_DIGSET1, C.DigSet1);
	DDV_MinMaxInt(pDX, C.DigSet1, -1, 31);
	DDX_Text(pDX, IDC_EMD_DIGSET2, C.DigSet2);
	DDV_MinMaxInt(pDX, C.DigSet2, -1, 31);
	DDX_Text(pDX, IDC_EMD_DIGTOGGLEFOUND, C.DigToggleFound);
	DDV_MinMaxInt(pDX, C.DigToggleFound, -1, 31);
	DDX_Text(pDX, IDC_EMD_SWITCHEMULAY, C.DigSwitchEmuLayer);
	DDV_MinMaxInt(pDX, C.DigSwitchEmuLayer, -1, 31);
	DDX_Text(pDX, IDC_EMD_GO, C.DigGo);
	DDV_MinMaxInt(pDX, C.DigGo, -1, 31);

	DDX_Text(pDX, IDC_EMD_XAXIS, C.AxXAxis);
	DDV_MinMaxInt(pDX, C.AxXAxis, -1, 5);
	DDX_Text(pDX, IDC_EMD_YAXIS, C.AxYAxis);
	DDV_MinMaxInt(pDX, C.AxYAxis, -1, 5);
}


BEGIN_MESSAGE_MAP(CEditMachineDefaults, CDialog)
	ON_BN_CLICKED(IDC_EMD_SETXDIGDEC, &CEditMachineDefaults::OnBnClickedEmdSetxdigdec)
	ON_BN_CLICKED(IDC_EMD_SETXDIGINC, &CEditMachineDefaults::OnBnClickedEmdSetxdiginc)
	ON_BN_CLICKED(IDC_EMD_SETYDIGDEC, &CEditMachineDefaults::OnBnClickedEmdSetydigdec)
	ON_BN_CLICKED(IDC_EMD_SETYDIGINC, &CEditMachineDefaults::OnBnClickedEmdSetydiginc)
	ON_BN_CLICKED(IDC_EMD_SETSET1, &CEditMachineDefaults::OnBnClickedEmdSetset1)
	ON_BN_CLICKED(IDC_EMD_SETSET2, &CEditMachineDefaults::OnBnClickedEmdSetset2)
	ON_BN_CLICKED(IDC_EMD_SETTOGGLEFOUND, &CEditMachineDefaults::OnBnClickedEmdSettogglefound)
	ON_BN_CLICKED(IDC_EMD_SETSWITCHEMULAY, &CEditMachineDefaults::OnBnClickedEmdSetswitchemulay)
	ON_BN_CLICKED(IDC_EMD_SETGO, &CEditMachineDefaults::OnBnClickedEmdSetgo)
	ON_BN_CLICKED(IDC_EMD_SETXAXIS, &CEditMachineDefaults::OnBnClickedEmdSetxaxis)
	ON_BN_CLICKED(IDC_EMD_SETYAXIS, &CEditMachineDefaults::OnBnClickedEmdSetyaxis)
END_MESSAGE_MAP()


// CEditMachineDefaults message handlers




int CEditMachineDefaults::GetJoyButton()
{
	JOYINFOEX jinfo;
	jinfo.dwSize = sizeof(jinfo);
	jinfo.dwFlags = JOY_RETURNALL;
	if (joyGetNumDevs() < 1) return -1;
	int j;
	for (j = 15; j >= 0; j--)
	{
		if (joyGetPosEx(j, &jinfo) == JOYERR_NOERROR) break;
	}		
	if (j < 0) return 0;
	unsigned maskbit = 0, mask = -1;
	do
	{
		if (jinfo.dwButtons & (1 << maskbit))
		{
			if (mask != -1) return -1;
			else mask = maskbit;
		}
		maskbit++;
	}
	while (maskbit < 32);
	return mask;
}

int CEditMachineDefaults::GetJoyAxis()
{
	JOYINFOEX jinfo;
	jinfo.dwSize = sizeof(jinfo);
	jinfo.dwFlags = JOY_RETURNALL;
	if (joyGetNumDevs() < 1) return 0;
	int j;
	for (j = 15; j >= 0; j--)
	{
		if (joyGetPosEx(j, &jinfo) == JOYERR_NOERROR) break;
	}		
	if (j < 0) return -1;
	JOYCAPS caps;
	joyGetDevCaps((unsigned)j, &caps, sizeof(caps));
	unsigned axis = -1;
	float myx = 0.0f, qmyx = 0.0f;
	if (caps.wMaxAxes > 0)
	{
		myx = fabs((jinfo.dwXpos - (caps.wXmin + caps.wXmax) / 2)/(float)(caps.wXmax - caps.wXmin));
		if (myx > qmyx)
		{ 
			qmyx = myx;
			axis = 0;
		}
	}
	if (caps.wMaxAxes > 1)
	{
		myx = fabs((jinfo.dwYpos - (caps.wYmin + caps.wYmax) / 2)/(float)(caps.wYmax - caps.wYmin));
		if (myx > qmyx)
		{ 
			qmyx = myx;
			axis = 1;
		}
	}
	if (caps.wMaxAxes > 2)
	{
		myx = fabs((jinfo.dwZpos - (caps.wZmin + caps.wZmax) / 2)/(float)(caps.wZmax - caps.wZmin));
		if (myx > qmyx)
		{ 
			qmyx = myx;
			axis = 2;
		}
	}
	if (caps.wMaxAxes > 3)
	{
		myx = fabs((jinfo.dwRpos - (caps.wRmin + caps.wRmax) / 2)/(float)(caps.wRmax - caps.wRmin));
		if (myx > qmyx)
		{ 
			qmyx = myx;
			axis = 3;
		}
	}
	if (caps.wMaxAxes > 4)
	{
		myx = fabs((jinfo.dwUpos - (caps.wUmin + caps.wUmax) / 2)/(float)(caps.wUmax - caps.wUmin));
		if (myx > qmyx)
		{ 
			qmyx = myx;
			axis = 4;
		}
	}
	if (caps.wMaxAxes > 5)
	{
		myx = fabs((jinfo.dwVpos - (caps.wVmin + caps.wVmax) / 2)/(float)(caps.wVmax - caps.wVmin));
		if (myx > qmyx)
		{ 
			qmyx = myx;
			axis = 5;
		}
	}
	return axis;	
}

void CEditMachineDefaults::OnBnClickedEmdSetxdigdec()
{
	// TODO: Add your control notification handler code here
	C.DigXDec = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetxdiginc()
{
	// TODO: Add your control notification handler code here
	C.DigXInc = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetydigdec()
{
	// TODO: Add your control notification handler code here
	C.DigYDec = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetydiginc()
{
	// TODO: Add your control notification handler code here
	C.DigYInc = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetset1()
{
	// TODO: Add your control notification handler code here
	C.DigSet1 = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetset2()
{
	// TODO: Add your control notification handler code here
	C.DigSet2 = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSettogglefound()
{
	// TODO: Add your control notification handler code here
	C.DigToggleFound = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetswitchemulay()
{
	// TODO: Add your control notification handler code here
	C.DigSwitchEmuLayer = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetgo()
{
	// TODO: Add your control notification handler code here
	C.DigGo = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetxaxis()
{
	// TODO: Add your control notification handler code here
	C.AxXAxis = GetJoyAxis();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetyaxis()
{
	// TODO: Add your control notification handler code here
	C.AxYAxis = GetJoyAxis();
	UpdateData(FALSE);
}
