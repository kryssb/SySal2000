// EditMachineDefaults.cpp : implementation file
//

#include "stdafx.h"
#include "flexstage4.h"
#include "EditMachineDefaults.h"
#include <mmsystem.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditMachineDefaults dialog


CEditMachineDefaults::CEditMachineDefaults(CWnd* pParent /*=NULL*/)
	: CDialog(CEditMachineDefaults::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditMachineDefaults)
	m_RefPosX = 0.0f;
	m_RefPosY = 0.0f;
	m_RefPosZ = 0.0f;
	m_RefPosName = _T("");
	//}}AFX_DATA_INIT
	m_pRefPos = 0;
	m_RefPosCount = 0;
	C.BoardId = 1;
	C.XYStepsRev = 4;
	C.ZStepsRev = 4;
	C.XYLinesRev = 20;
	C.ZLinesRev = 20;
	C.XYEncoderToMicrons = 0.5f;
	C.ZEncoderToMicrons = 0.5f;
	C.LimPol = 0;
	C.CtlModeIsCWCCW = 1;
	C.InvertX = C.InvertY = C.InvertZ = FALSE;
	C.LightLimit = 32767;
	C.TurnOffLightTime = 3;
	C.ZHomingSpeed = 1000.0f;
	C.ZHomingXPos = 120000.0f;
	C.ZHomingYPos = 120000.0f;
}


void CEditMachineDefaults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditMachineDefaults)
	DDX_Control(pDX, IDC_EMD_NAMELIST, m_NameList);
	DDX_Text(pDX, IDC_EMD_REFPOSX, m_RefPosX);
	DDV_MinMaxFloat(pDX, m_RefPosX, -300000.0f, 300000.0f);
	DDX_Text(pDX, IDC_EMD_REFPOSY, m_RefPosY);
	DDV_MinMaxFloat(pDX, m_RefPosY, -300000.0f, 300000.0f);
	DDX_Text(pDX, IDC_EMD_REFPOSZ, m_RefPosZ);
	DDV_MinMaxFloat(pDX, m_RefPosZ, -300000.0f, 300000.0f);
	DDX_Text(pDX, IDC_EMD_REFPOSNAME, m_RefPosName);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EMD_BOARDID, C.BoardId);
	DDV_MinMaxUInt(pDX, C.BoardId, 1, 16);
	DDX_Check(pDX, IDC_EMD_INVLIMPOL, C.LimPol);
	DDX_Text(pDX, IDC_EMD_XY_ENC2MICRON, C.XYEncoderToMicrons);
	DDV_MinMaxFloat(pDX, C.XYEncoderToMicrons, 1.e-003f, 1000.f);
	DDX_Text(pDX, IDC_EMD_XY_LINESREV, C.XYLinesRev);
	DDV_MinMaxUInt(pDX, C.XYLinesRev, 1, 100000);
	DDX_Text(pDX, IDC_EMD_XY_STEPSREV, C.XYStepsRev);
	DDV_MinMaxUInt(pDX, C.XYStepsRev, 1, 100000);
	DDX_Text(pDX, IDC_EMD_Z_ENC2MICRON, C.ZEncoderToMicrons);
	DDV_MinMaxFloat(pDX, C.ZEncoderToMicrons, 1.e-003f, 1000.f);
	DDX_Text(pDX, IDC_EMD_Z_LINESREV, C.ZLinesRev);
	DDV_MinMaxUInt(pDX, C.ZLinesRev, 1, 100000);
	DDX_Text(pDX, IDC_EMD_Z_STEPSREV, C.ZStepsRev);
	DDV_MinMaxUInt(pDX, C.ZStepsRev, 1, 100000);
	DDX_Text(pDX, IDC_EMD_LIGHTLIMIT, C.LightLimit);
	DDV_MinMaxUInt(pDX, C.LightLimit, 1, 100000);
	DDX_Text(pDX, IDC_EMD_TURNOFFLIGHTTIME, C.TurnOffLightTime);
	DDV_MinMaxUInt(pDX, C.TurnOffLightTime, 1, 10);
	DDX_Check(pDX, IDC_EMD_INVERTX, C.InvertX);
	DDX_Check(pDX, IDC_EMD_INVERTY, C.InvertY);
	DDX_Check(pDX, IDC_EMD_INVERTZ, C.InvertZ);
	DDX_Text(pDX, IDC_EMD_Z_HOMINGSPEED, C.ZHomingSpeed);
	DDV_MinMaxFloat(pDX, C.ZHomingSpeed, 100.0f, 5000.0f);
	DDX_Text(pDX, IDC_EMD_Z_HOMINGXPOS, C.ZHomingXPos);
	DDV_MinMaxFloat(pDX, C.ZHomingXPos, -300000.0f, 300000.0f);
	DDX_Text(pDX, IDC_EMD_Z_HOMINGYPOS, C.ZHomingYPos);
	DDV_MinMaxFloat(pDX, C.ZHomingYPos, -300000.0f, 300000.0f);

	DDX_Text(pDX, IDC_EMD_XDIGDEC, C.DigXDec);
	DDV_MinMaxInt(pDX, C.DigYDec, -1, 31);
	DDX_Text(pDX, IDC_EMD_YDIGDEC, C.DigYDec);
	DDV_MinMaxInt(pDX, C.DigYDec, -1, 31);
	DDX_Text(pDX, IDC_EMD_ZDIGDEC, C.DigZDec);
	DDV_MinMaxInt(pDX, C.DigZDec, -1, 31);
	DDX_Text(pDX, IDC_EMD_LDIGDEC, C.DigLDec);
	DDV_MinMaxInt(pDX, C.DigLDec, -1, 31);
	DDX_Text(pDX, IDC_EMD_XDIGINC, C.DigXInc);
	DDV_MinMaxInt(pDX, C.DigYInc, -1, 31);
	DDX_Text(pDX, IDC_EMD_YDIGINC, C.DigYInc);
	DDV_MinMaxInt(pDX, C.DigYInc, -1, 31);
	DDX_Text(pDX, IDC_EMD_ZDIGINC, C.DigZInc);
	DDV_MinMaxInt(pDX, C.DigZInc, -1, 31);
	DDX_Text(pDX, IDC_EMD_LDIGINC, C.DigLInc);
	DDV_MinMaxInt(pDX, C.DigLInc, -1, 31);

	DDX_Text(pDX, IDC_EMD_AUTOMAN, C.DigToggleAutoManual);
	DDV_MinMaxInt(pDX, C.DigToggleAutoManual, -1, 31);
	DDX_Text(pDX, IDC_EMD_SPEEDCHANGE, C.DigSpeedChange);
	DDV_MinMaxInt(pDX, C.DigSpeedChange, -1, 31);

	DDX_Text(pDX, IDC_EMD_XAXIS, C.AxXAxis);
	DDV_MinMaxInt(pDX, C.AxXAxis, -1, 5);
	DDX_Text(pDX, IDC_EMD_YAXIS, C.AxYAxis);
	DDV_MinMaxInt(pDX, C.AxYAxis, -1, 5);
	DDX_Text(pDX, IDC_EMD_ZAXIS, C.AxZAxis);
	DDV_MinMaxInt(pDX, C.AxZAxis, -1, 5);
	DDX_Text(pDX, IDC_EMD_LAXIS, C.AxLAxis);
	DDV_MinMaxInt(pDX, C.AxLAxis, -1, 5);
}


BEGIN_MESSAGE_MAP(CEditMachineDefaults, CDialog)
	//{{AFX_MSG_MAP(CEditMachineDefaults)
	ON_BN_CLICKED(IDC_EMD_REFPOSDEL, OnDel)
	ON_BN_CLICKED(IDC_EMD_REFPOSSET, OnSet)
	ON_BN_CLICKED(IDC_EMD_STEPDIR, OnStepDir)
	ON_BN_CLICKED(IDC_EMD_CWCCW, OnCWCCW)
	ON_LBN_SELCHANGE(IDC_EMD_NAMELIST, OnNameSelChange)
	ON_BN_CLICKED(IDC_EMD_XY, OnRefPosXY)
	ON_BN_CLICKED(IDC_EMD_Z, OnRefPosZ)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_EMD_SETXDIGDEC, &CEditMachineDefaults::OnBnClickedEmdSetxdigdec)
	ON_BN_CLICKED(IDC_EMD_SETXDIGINC, &CEditMachineDefaults::OnBnClickedEmdSetxdiginc)
	ON_BN_CLICKED(IDC_EMD_SETYDIGDEC, &CEditMachineDefaults::OnBnClickedEmdSetydigdec)
	ON_BN_CLICKED(IDC_EMD_SETYDIGINC, &CEditMachineDefaults::OnBnClickedEmdSetydiginc)
	ON_BN_CLICKED(IDC_EMD_SETZDIGDEC, &CEditMachineDefaults::OnBnClickedEmdSetzdigdec)
	ON_BN_CLICKED(IDC_EMD_SETZDIGINC, &CEditMachineDefaults::OnBnClickedEmdSetzdiginc)
	ON_BN_CLICKED(IDC_EMD_SETLDIGDEC, &CEditMachineDefaults::OnBnClickedEmdSetldigdec)
	ON_BN_CLICKED(IDC_EMD_SETLDIGINC, &CEditMachineDefaults::OnBnClickedEmdSetldiginc)
	ON_BN_CLICKED(IDC_EMD_SETAUTOMAN, &CEditMachineDefaults::OnBnClickedEmdSetautoman)
	ON_BN_CLICKED(IDC_EMD_SETSPEEDCHANGE, &CEditMachineDefaults::OnBnClickedEmdSetspeedchange)
	ON_BN_CLICKED(IDC_EMD_SETXAXIS, &CEditMachineDefaults::OnBnClickedEmdSetxaxis)
	ON_BN_CLICKED(IDC_EMD_SETYAXIS, &CEditMachineDefaults::OnBnClickedEmdSetyaxis)
	ON_BN_CLICKED(IDC_EMD_SETZAXIS, &CEditMachineDefaults::OnBnClickedEmdSetzaxis)
	ON_BN_CLICKED(IDC_EMD_SETLAXIS, &CEditMachineDefaults::OnBnClickedEmdSetlaxis)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditMachineDefaults message handlers

void CEditMachineDefaults::OnDel() 
{
	// TODO: Add your control notification handler code here
	int i, j;
	if ((j = m_NameList.GetCurSel()) < 0) return;
	RefPos r;
	m_NameList.GetText(j, r.Name);
	r.IsZ = m_NameList.GetItemData(j);
	for (i = 0; i < m_RefPosCount; i++)
	{
		if (strcmpi(r.Name, m_pRefPos[i].Name) == 0 && m_pRefPos[i].IsZ == r.IsZ)
		{
			m_NameList.DeleteString(j);
			m_RefPosCount--;
			while (i < m_RefPosCount)
			{
				m_pRefPos[i] = m_pRefPos[i + 1];
				i++;
				}
			m_pRefPos = (RefPos *)realloc(m_pRefPos, sizeof(RefPos) * m_RefPosCount);
			return;
			}
		}
	
}

void CEditMachineDefaults::OnSet() 
{
	// TODO: Add your control notification handler code here
	int i;
	UpdateData();
	m_RefPosName.TrimLeft();
	m_RefPosName.TrimRight();
	UpdateData(FALSE);
	if (m_RefPosName.GetLength() <= 0 || m_RefPosName.GetLength() >= REFPOSNAMELEN) return;
	RefPos r;
	strcpy(r.Name, m_RefPosName.GetBuffer(1));
	m_RefPosName.ReleaseBuffer();
	r.IsZ = SendDlgItemMessage(IDC_EMD_Z, BM_GETCHECK) == BST_CHECKED;
	if (r.IsZ)	
		r.Pos.Z = m_RefPosZ;	
	else
	{
		r.Pos.XY.X = m_RefPosX;
		r.Pos.XY.Y = m_RefPosY;
		}
	for (i = 0; i < m_RefPosCount; i++)
	{
		if (strcmpi(r.Name, m_pRefPos[i].Name) == 0 && m_pRefPos[i].IsZ == r.IsZ)
		{
			m_pRefPos[i] = r;
			return;
			}
		}	
	m_pRefPos[i] = r;
	m_pRefPos = (RefPos *)realloc(m_pRefPos, sizeof(RefPos) * (++m_RefPosCount + 1));
	i = m_NameList.AddString(r.Name);
	m_NameList.SetItemData(i, r.IsZ);
}

BOOL CEditMachineDefaults::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (C.CtlModeIsCWCCW)
	{
		GetDlgItem(IDC_EMD_STEPDIR)->SendMessage(BM_SETCHECK, BST_UNCHECKED);
		GetDlgItem(IDC_EMD_CWCCW)->SendMessage(BM_SETCHECK, BST_CHECKED);
		}
	else
	{
		GetDlgItem(IDC_EMD_STEPDIR)->SendMessage(BM_SETCHECK, BST_CHECKED);
		GetDlgItem(IDC_EMD_CWCCW)->SendMessage(BM_SETCHECK, BST_UNCHECKED);		
		};
	
	int i;
	for (i = 0; i < m_RefPosCount; i++)	
		m_NameList.SetItemData(m_NameList.AddString(m_pRefPos[i].Name), m_pRefPos[i].IsZ);		
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditMachineDefaults::OnNameSelChange() 
{
	// TODO: Add your control notification handler code here
	int i;
	if ((i = m_NameList.GetCurSel()) < 0) return;
	RefPos r;
	m_NameList.GetText(i, r.Name);
	r.IsZ = m_NameList.GetItemData(i);
	for (i = 0; i < m_RefPosCount; i++)
	{
		if (strcmpi(r.Name, m_pRefPos[i].Name) == 0 && m_pRefPos[i].IsZ == r.IsZ)
		{
			m_RefPosName = m_pRefPos[i].Name;
			if (m_pRefPos[i].IsZ)
			{
				m_RefPosZ = m_pRefPos[i].Pos.Z;
				m_RefPosX = m_RefPosY = 0.0f;
				}
			else
			{
				m_RefPosZ = 0.0f;
				m_RefPosX = m_pRefPos[i].Pos.XY.X;
				m_RefPosY = m_pRefPos[i].Pos.XY.Y;
				};
			SendDlgItemMessage(m_pRefPos[i].IsZ ? IDC_EMD_Z : IDC_EMD_XY, BM_SETCHECK, BST_CHECKED);
			SendDlgItemMessage(m_pRefPos[i].IsZ ? IDC_EMD_XY : IDC_EMD_Z, BM_SETCHECK, BST_UNCHECKED);
			GetDlgItem(IDC_EMD_REFPOSX)->EnableWindow(!m_pRefPos[i].IsZ);
			GetDlgItem(IDC_EMD_REFPOSY)->EnableWindow(!m_pRefPos[i].IsZ);
			GetDlgItem(IDC_EMD_REFPOSZ)->EnableWindow(m_pRefPos[i].IsZ);
			UpdateData(FALSE);
			return;
			}
		}
}

void CEditMachineDefaults::OnStepDir() 
{
	// TODO: Add your control notification handler code here
	C.CtlModeIsCWCCW = 0;
}

void CEditMachineDefaults::OnCWCCW() 
{
	// TODO: Add your control notification handler code here
	C.CtlModeIsCWCCW = 1;	
}


void CEditMachineDefaults::OnRefPosXY() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EMD_REFPOSX)->EnableWindow(TRUE);
	GetDlgItem(IDC_EMD_REFPOSY)->EnableWindow(TRUE);
	GetDlgItem(IDC_EMD_REFPOSZ)->EnableWindow(FALSE);
}

void CEditMachineDefaults::OnRefPosZ() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EMD_REFPOSX)->EnableWindow(FALSE);
	GetDlgItem(IDC_EMD_REFPOSY)->EnableWindow(FALSE);
	GetDlgItem(IDC_EMD_REFPOSZ)->EnableWindow(TRUE);	
}

void CEditMachineDefaults::OnBnClickedEmdSetxdigdec()
{
	C.DigXDec = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetxdiginc()
{
	C.DigXInc = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetydigdec()
{
	C.DigYDec = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetydiginc()
{
	C.DigYInc = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetzdigdec()
{
	C.DigZDec = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetzdiginc()
{
	C.DigZInc = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetldigdec()
{
	C.DigLDec = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetldiginc()
{
	C.DigLInc = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetautoman()
{
	C.DigToggleAutoManual = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetspeedchange()
{
	C.DigSpeedChange = GetJoyButton();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetxaxis()
{
	C.AxXAxis = GetJoyAxis();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetyaxis()
{
	C.AxYAxis = GetJoyAxis();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetzaxis()
{
	C.AxZAxis = GetJoyAxis();
	UpdateData(FALSE);
}

void CEditMachineDefaults::OnBnClickedEmdSetlaxis()
{
	C.AxLAxis = GetJoyAxis();
	UpdateData(FALSE);
}

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
