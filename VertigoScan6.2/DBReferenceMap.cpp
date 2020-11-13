// DBReferenceMap.cpp : implementation file
//

#include "stdafx.h"
#include "DBReferenceMap.h"


// CDBReferenceMap dialog

IMPLEMENT_DYNAMIC(CDBReferenceMap, CDialog)

CDBReferenceMap::CDBReferenceMap(CWnd* pParent /*=NULL*/)
	: CDialog(CDBReferenceMap::IDD, pParent)
	, m_MinX(0)
	, m_MaxX(0)
	, m_MinY(0)
	, m_MaxY(0)
	, m_Limit(10000)
	, m_ContainsEnabled(FALSE)
	, m_HasX(0)
	, m_HasY(0)
	, m_MinGrains(8)
	, m_MinSlope(0.05)
	, m_MaxSlope(0.4)
{
	DBConn = nullptr;
	TrackArray = nullptr;
}

char *CDBReferenceMap::String2Char(System::String ^s)
{
	int i;
	char *c = new char[s->Length + 1];
	for (i = 0; i < s->Length; i++)
		c[i] = s[i];
	c[i] = 0;
	return c;
}

CDBReferenceMap::~CDBReferenceMap()
{
	if (!System::Object::ReferenceEquals(DBConn, nullptr)) DBConn->Close();
}

void CDBReferenceMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DR_MINX, m_MinX);
	DDX_Text(pDX, IDC_DR_MAXX, m_MaxX);
	DDX_Text(pDX, IDC_DR_MINY, m_MinY);
	DDX_Text(pDX, IDC_DR_MAXY, m_MaxY);
	DDX_Text(pDX, IDC_DR_LIMIT, m_Limit);
	DDX_Control(pDX, IDC_DR_BRICKS, cmbBrick);
	DDX_Control(pDX, IDC_DR_PLATE, cmbPlate);
	DDX_Control(pDX, IDC_DR_PROCOP, cmbProcOp);
	DDX_Control(pDX, IDC_DR_ZONE, cmbZone);
	DDX_Check(pDX, IDC_DR_ENABLECONTAIN, m_ContainsEnabled);
	DDX_Text(pDX, IDC_DR_HASX, m_HasX);
	DDX_Text(pDX, IDC_DR_HASY, m_HasY);
	DDX_Text(pDX, IDC_DR_MINGRAINS, m_MinGrains);
	DDV_MinMaxInt(pDX, m_MinGrains, 0, 100);
	DDX_Text(pDX, IDC_DR_MINS, m_MinSlope);
	DDV_MinMaxDouble(pDX, m_MinSlope, 0, 1);
	DDX_Text(pDX, IDC_DR_MAXS, m_MaxSlope);
	DDV_MinMaxDouble(pDX, m_MaxSlope, 0, 1);
}


BEGIN_MESSAGE_MAP(CDBReferenceMap, CDialog)
	ON_CBN_SELCHANGE(IDC_DR_BRICKS, &CDBReferenceMap::OnBrickSelChange)
	ON_CBN_SELCHANGE(IDC_DR_PLATE, &CDBReferenceMap::OnPlateSelChange)
	ON_CBN_SELCHANGE(IDC_DR_PROCOP, &CDBReferenceMap::OnProcOpSelChange)
	ON_CBN_SELCHANGE(IDC_DR_ZONE, &CDBReferenceMap::OnZoneSelChange)
	ON_BN_CLICKED(IDC_DR_ENABLECONTAIN, &CDBReferenceMap::OnReqContainClicked)
	ON_EN_KILLFOCUS(IDC_DR_HASX, &CDBReferenceMap::OnHasXLeave)
	ON_EN_KILLFOCUS(IDC_DR_HASY, &CDBReferenceMap::OnHasYLeave)
	ON_BN_CLICKED(IDOK, &CDBReferenceMap::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDBReferenceMap::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDBReferenceMap message handlers

void CDBReferenceMap::HandleException(System::Exception ^x)
{
	char *c = String2Char(x->ToString());
	::MessageBox(0, c, "DB Connection Error", MB_ICONERROR | MB_OK);
	delete [] c;
	if (!DBConn->Equals(nullptr)) 
	{
		DBConn->Close();
		DBConn = nullptr;
		EndDialog(IDCANCEL);
	}
}

void CDBReferenceMap::OnBrickSelChange()
{
	try
	{
		cmbPlate.ResetContent();
		cmbProcOp.ResetContent();
		cmbZone.ResetContent();	
		System::Data::DataSet ^ds = gcnew System::Data::DataSet();
		System::Data::DataRowCollection ^dr = drbricks;
		(gcnew SySal::OperaDb::OperaDbDataAdapter(gcnew System::String("SELECT ID FROM TB_PLATES WHERE ID_EVENTBRICK=") + dr[cmbBrick.GetCurSel()][0]->ToString() + gcnew System::String(" ORDER BY ID"), DBConn))->Fill(ds);
		int i;
		for (i = 0; i < ds->Tables[0]->Rows->Count; i++)
		{
			char *c = String2Char(ds->Tables[0]->Rows[i][0]->ToString());
			cmbPlate.AddString(c);
			delete [] c;
		}
		drplates = ds->Tables[0]->Rows;
	}
	catch (System::Exception ^x)
	{
		HandleException(x);
	}
}

void CDBReferenceMap::OnPlateSelChange()
{
	try
	{
		cmbProcOp.ResetContent();
		cmbZone.ResetContent();	
		System::Data::DataSet ^ds = gcnew System::Data::DataSet();
		System::Data::DataRowCollection ^db = drbricks;
		System::Data::DataRowCollection ^dp = drplates;
		(gcnew SySal::OperaDb::OperaDbDataAdapter(gcnew System::String("SELECT DISTINCT ID_PROCESSOPERATION FROM TB_ZONES WHERE ID_EVENTBRICK=") + db[cmbBrick.GetCurSel()][0]->ToString() + gcnew System::String(" AND ID_PLATE=") + dp[cmbPlate.GetCurSel()][0]->ToString() + gcnew System::String(" ORDER BY ID_PROCESSOPERATION"), DBConn))->Fill(ds);
		int i;
		for (i = 0; i < ds->Tables[0]->Rows->Count; i++)
		{
			char *c = String2Char(ds->Tables[0]->Rows[i][0]->ToString());
			cmbProcOp.AddString(c);
			delete [] c;
		}
		drprocops = ds->Tables[0]->Rows;
	}
	catch (System::Exception ^x)
	{
		HandleException(x);
	}
}

void CDBReferenceMap::OnProcOpSelChange()
{
	try
	{
		UpdateData();
		cmbZone.ResetContent();	
		System::Data::DataSet ^ds = gcnew System::Data::DataSet();
		System::Data::DataRowCollection ^db = drbricks;
		System::Data::DataRowCollection ^dp = drplates;
		System::Data::DataRowCollection ^dq = drprocops;
		System::String ^sql = gcnew System::String("SELECT ID, ROUND(MINX), ROUND(MAXX), ROUND(MINY), ROUND(MAXY) FROM TB_ZONES WHERE ID_EVENTBRICK=") + db[cmbBrick.GetCurSel()][0]->ToString() + gcnew System::String(" AND ID_PLATE=") + dp[cmbPlate.GetCurSel()][0]->ToString() + gcnew System::String(" AND ID_PROCESSOPERATION=") + dq[cmbProcOp.GetCurSel()][0]->ToString();
		if (m_ContainsEnabled)
			sql += " AND MINX < " + m_HasX.ToString() + " AND MAXX > " + m_HasX.ToString() + " AND MINY < " + m_HasY.ToString() + " AND MAXY > " + m_HasY.ToString();
		sql += " ORDER BY ID";
		(gcnew SySal::OperaDb::OperaDbDataAdapter(sql, DBConn))->Fill(ds);
		int i;
		for (i = 0; i < ds->Tables[0]->Rows->Count; i++)
		{
			char *c = String2Char(ds->Tables[0]->Rows[i][0]->ToString() + " (" + ds->Tables[0]->Rows[i][1]->ToString() + " <X< " + ds->Tables[0]->Rows[i][2]->ToString() + " , " + ds->Tables[0]->Rows[i][3]->ToString() + " <Y< " + ds->Tables[0]->Rows[i][4]->ToString() + ")");
			cmbZone.AddString(c);
			delete [] c;
		}
		drzones = ds->Tables[0]->Rows;
	}
	catch (System::Exception ^x)
	{
		HandleException(x);
	}
}

void CDBReferenceMap::OnZoneSelChange()
{
	try
	{
		UpdateData();
		if (cmbZone.GetCurSel() < 0) TrackArray = nullptr;
		else
		{			
			System::Data::DataRowCollection ^dz = drzones;
			m_MinX = System::Convert::ToDouble(dz[cmbZone.GetCurSel()][1]);
			m_MaxX = System::Convert::ToDouble(dz[cmbZone.GetCurSel()][2]);
			m_MinY = System::Convert::ToDouble(dz[cmbZone.GetCurSel()][3]);
			m_MaxY = System::Convert::ToDouble(dz[cmbZone.GetCurSel()][4]);
			UpdateData(FALSE);
		}
	}
	catch (System::Exception ^x)
	{
		HandleException(x);
	}
}

BOOL CDBReferenceMap::OnInitDialog()
{
	CDialog::OnInitDialog();

	try
	{
		DBConn = SySal::OperaDb::OperaDbCredentials::CreateFromRecord()->Connect();
		DBConn->Open();
		cmbBrick.Clear();
		System::Data::DataSet ^ds = gcnew System::Data::DataSet();
		(gcnew SySal::OperaDb::OperaDbDataAdapter("SELECT ID FROM TB_EVENTBRICKS ORDER BY ID", DBConn))->Fill(ds);
		int i;
		for (i = 0; i < ds->Tables[0]->Rows->Count; i++)
		{
			char *c = String2Char(ds->Tables[0]->Rows[i][0]->ToString());
			cmbBrick.AddString(c), _atoi64(c);
			delete [] c;
		}
		drbricks = ds->Tables[0]->Rows;
	}
	catch (System::Exception ^x)
	{
		HandleException(x);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDBReferenceMap::OnReqContainClicked()
{
	if (cmbProcOp.GetCurSel() >= 0) OnProcOpSelChange();
}

void CDBReferenceMap::OnHasXLeave()
{
	UpdateData();
	if (cmbProcOp.GetCurSel() >= 0) OnProcOpSelChange();
}

void CDBReferenceMap::OnHasYLeave()
{
	UpdateData();
	if (cmbProcOp.GetCurSel() >= 0) OnProcOpSelChange();
}



void CDBReferenceMap::OnBnClickedOk()
{
	HCURSOR HCur = GetCursor();
	try
	{
		SetCursor(LoadCursor(0, IDC_WAIT));
		UpdateData();
		if (cmbZone.GetCurSel() < 0) return;
		System::Data::DataRowCollection ^db = drbricks;
		System::Data::DataRowCollection ^dz = drzones;
		System::String ^sql = "SELECT POSX,POSY,SLOPEX,SLOPEY FROM (SELECT POSX,POSY,SLOPEX,SLOPEY,ROW_NUMBER() OVER (ORDER BY GRAINS DESC, AREASUM DESC, SIGMA ASC) AS RNUM FROM TB_MIPMICROTRACKS WHERE ID_EVENTBRICK=" + db[cmbBrick.GetCurSel()][0]->ToString() + " AND ID_ZONE=" + dz[cmbZone.GetCurSel()][0]->ToString() + " AND SIDE=1 AND POSX BETWEEN " + m_MinX.ToString() + " AND " + m_MaxX.ToString() + " AND POSY BETWEEN " + m_MinY.ToString() + " AND " + m_MaxY.ToString() + " AND (SLOPEX * SLOPEX + SLOPEY * SLOPEY) BETWEEN " + (m_MinSlope * m_MinSlope).ToString() + " AND " + (m_MaxSlope * m_MaxSlope).ToString() + " AND GRAINS > " + m_MinGrains.ToString() + ") WHERE RNUM <= " + m_Limit.ToString();
		System::Data::DataSet ^dtks = gcnew System::Data::DataSet();
		(gcnew SySal::OperaDb::OperaDbDataAdapter(sql, DBConn))->Fill(dtks);
		TrackArray = gcnew array<SySal::Tracking::MIPEmulsionTrackInfo ^>(dtks->Tables[0]->Rows->Count);
		int i;
		for (i = 0; i < dtks->Tables[0]->Rows->Count; i++)
		{
			System::Data::DataRow ^dr = dtks->Tables[0]->Rows[i];
			SySal::Tracking::MIPEmulsionTrackInfo ^info = gcnew SySal::Tracking::MIPEmulsionTrackInfo();
			info->Intercept.X = System::Convert::ToDouble(dr[0]);
			info->Intercept.Y = System::Convert::ToDouble(dr[1]);
			info->Slope.X = System::Convert::ToDouble(dr[2]);
			info->Slope.Y = System::Convert::ToDouble(dr[3]);
			TrackArray[i] = info;
		}
	}
	catch (System::Exception ^x)
	{
		SetCursor(HCur);
		HandleException(x);
	}
	SetCursor(HCur);
	OnOK();
}

void CDBReferenceMap::OnBnClickedCancel()
{	
	if (!DBConn->Equals(nullptr))
	{
		DBConn->Close();
		DBConn = nullptr;
	}
	OnCancel();
}
