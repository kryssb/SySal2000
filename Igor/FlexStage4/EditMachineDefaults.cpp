// EditMachineDefaults.cpp : implementation file
//

#include "stdafx.h"
#include "flexstage4.h"
#include "EditMachineDefaults.h"

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
