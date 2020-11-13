// TestBench.cpp : implementation file
//

#include "stdafx.h"
#include "ScanServer.h"
#include "TestBench.h"


// CTestBench dialog

IMPLEMENT_DYNAMIC(CTestBench, CDialog)

CTestBench::CTestBench(CWnd* pParent /*=NULL*/)
	: CDialog(CTestBench::IDD, pParent)
	, m_LoadPlateTextDesc(_T(""))
	, m_LoadPlateBrick(0)
	, m_LoadPlatePlate(0)
	, m_LoadPlateMapInit(_T(""))
	, m_ScanZoneId(0)
	, m_ScanMinX(0)
	, m_ScanMaxX(0)
	, m_ScanMinY(0)
	, m_ScanMaxY(0)
	, m_ScanPresetSlope(FALSE)
	, m_ScanSlopeX(0)
	, m_ScanSlopeY(0)
	, m_ScanSlopeAccX(0)
	, m_ScanSlopeAccY(0)
	, m_ScanMoveNext(FALSE)
	, m_ScanMoveNextMinX(0)
	, m_ScanMoveNextMinY(0)
	, m_ScanMoveNextMaxX(0)
	, m_ScanMoveNextMaxY(0)
	, m_SetSingleParamObject(_T(""))
	, m_SetSingleParamParam(_T(""))
	, m_SetSingleParamValue(_T(""))
	, m_SetObjectConfigObject(_T(""))
	, m_SetObjectConfigConfig(_T(""))
	, m_SetScanLayoutLayout(_T(""))
	, m_ManualCheckId(0)
	, m_ManualCheckPosX(0)
	, m_ManualCheckPosY(0)
	, m_ManualCheckSlopeX(0)
	, m_ManualCheckSlopeY(0)
	, m_ManualCheckPosTol(0)
	, m_ManualCheckSlopeTol(0)
	, m_ManualCheckOutGrains(0)
	, m_ManualCheckOutPosX(0)
	, m_ManualCheckOutPosY(0)
	, m_ManualCheckOutSlopeX(0)
	, m_ManualCheckOutSlopeY(0)
	, m_TopFog(0)
	, m_BottomFog(0)
	, m_TopThickness(0)
	, m_BottomThickness(0)
	, m_BaseThickness(0)
	, m_Done(FALSE)
	, m_Exception(_T(""))
	, m_ScanOutname(_T(""))
	, m_ManualCheckFound(FALSE)
	, m_ManualCheckDone(FALSE)
{

}

CTestBench::~CTestBench()
{
}

void CTestBench::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TB_LOADPLATE_TEXTDESC, m_LoadPlateTextDesc);
	DDX_Text(pDX, IDC_TB_LOADPLATE_BRICK, m_LoadPlateBrick);
	DDX_Text(pDX, IDC_TB_LOADPLATE_PLATE, m_LoadPlatePlate);
	DDX_Text(pDX, IDC_TB_LOADPLATE_MAPINIT, m_LoadPlateMapInit);
	DDX_Text(pDX, IDC_TB_SCAN_ZONEID, m_ScanZoneId);
	DDX_Text(pDX, IDC_TB_SCAN_MINX, m_ScanMinX);
	DDX_Text(pDX, IDC_TB_SCAN_MAXX, m_ScanMaxX);
	DDX_Text(pDX, IDC_TB_SCAN_MINY, m_ScanMinY);
	DDX_Text(pDX, IDC_TB_SCAN_MAXY, m_ScanMaxY);
	DDX_Check(pDX, IDC_TB_SCAN_PRESETSLOPE, m_ScanPresetSlope);
	DDX_Text(pDX, IDC_TB_SCAN_SLOPEX, m_ScanSlopeX);
	DDX_Text(pDX, IDC_TB_SCAN_SLOPEY, m_ScanSlopeY);
	DDX_Text(pDX, IDC_TB_SCAN_SLOPEXACC, m_ScanSlopeAccX);
	DDX_Text(pDX, IDC_TB_SCAN_SLOPEYACC, m_ScanSlopeAccY);
	DDX_Check(pDX, IDC_TB_SCAN_MOVENEXT, m_ScanMoveNext);
	DDX_Text(pDX, IDC_TB_SCAN_NEXTMINX, m_ScanMoveNextMinX);
	DDX_Text(pDX, IDC_TB_SCAN_NEXTMINY, m_ScanMoveNextMinY);
	DDX_Text(pDX, IDC_TB_SCAN_NEXTMAXX, m_ScanMoveNextMaxX);
	DDX_Text(pDX, IDC_TB_SCAN_NEXTMAXY, m_ScanMoveNextMaxY);
	DDX_Text(pDX, IDC_TB_SETSINGLEPARAM_OBJECT, m_SetSingleParamObject);
	DDX_Text(pDX, IDC_TB_SETSINGLEPARAM_PARAM, m_SetSingleParamParam);
	DDX_Text(pDX, IDC_TB_SETSINGLEPARAM_VALUE, m_SetSingleParamValue);
	DDX_Text(pDX, IDC_TB_SETOBJCONFIG_OBJECT, m_SetObjectConfigObject);
	DDX_Text(pDX, IDC_TB_SETOBJCONFIG_CONFIG, m_SetObjectConfigConfig);
	DDX_Text(pDX, IDC_TB_SETSCANLAYOUT_LAYOUT, m_SetScanLayoutLayout);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_ID, m_ManualCheckId);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_POSX, m_ManualCheckPosX);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_POSY, m_ManualCheckPosY);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_SLOPEX, m_ManualCheckSlopeX);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_SLOPEY, m_ManualCheckSlopeY);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_POSTOL, m_ManualCheckPosTol);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_SLOPETOL, m_ManualCheckSlopeTol);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_GRAINS, m_ManualCheckOutGrains);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_FOUNDX, m_ManualCheckOutPosX);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_FOUNDY, m_ManualCheckOutPosY);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_FOUNDSX, m_ManualCheckOutSlopeX);
	DDX_Text(pDX, IDC_TB_MANUALCHECK_FOUNDSY, m_ManualCheckOutSlopeY);
	DDX_Text(pDX, IDC_TB_GETFOGTHICK_TOPFOG, m_TopFog);
	DDX_Text(pDX, IDC_TB_GETFOGTHICK_BOTFOG, m_BottomFog);
	DDX_Text(pDX, IDC_TB_GETFOGTHICK_TOPTHK, m_TopThickness);
	DDX_Text(pDX, IDC_TB_GETFOGTHICK_BOTTHK, m_BottomThickness);
	DDX_Text(pDX, IDC_TB_GETFOGTHICK_BASETHK, m_BaseThickness);
	DDX_Check(pDX, IDC_TB_DONE, m_Done);
	DDX_Text(pDX, IDC_TB_EXCEPTION, m_Exception);
	DDX_Text(pDX, IDC_TB_LOADPLATE_OUTNAME, m_ScanOutname);
	DDX_Check(pDX, IDC_TB_FOUND, m_ManualCheckFound);
	DDX_Check(pDX, IDC_TB_CHECKDONE, m_ManualCheckDone);
}


BEGIN_MESSAGE_MAP(CTestBench, CDialog)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(ID_TB_HIDE, &CTestBench::OnBnClickedTbHide)
	ON_BN_CLICKED(ID_TB_SEND, &CTestBench::OnBnClickedTbSend)
	ON_BN_CLICKED(IDC_TB_CHECKDONE, &CTestBench::OnBnClickedTbCheckdone)
	ON_BN_CLICKED(IDC_TB_FOUND, &CTestBench::OnBnClickedTbFound)
	ON_BN_CLICKED(IDC_TB_LOADSCANLAYOUT, &CTestBench::OnBnClickedTbLoadscanlayout)
END_MESSAGE_MAP()


// CTestBench message handlers

void CTestBench::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID != SC_CLOSE)
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CTestBench::OnBnClickedTbHide()
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
}

void CTestBench::OnBnClickedTbSend()
{
	// TODO: Add your control notification handler code here
	UpdateData();	
//	EnableWindow(FALSE);
	AfxBeginThread(ThreadHook, this);
}

BOOL CTestBench::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class

	if (wParam != 2) return CDialog::OnCommand(wParam, lParam);
	else return FALSE;
}

BOOL CTestBench::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

UINT _cdecl CTestBench::ThreadHook(void *par)
{
	return ((CTestBench *)par)->Thread();
}

UINT CTestBench::Thread()
{
	if (SendDlgItemMessage(IDC_TB_LOADPLATE, BM_GETCHECK) == BST_CHECKED)
	{
		bool ret = false;
		try
		{
			gcroot<SySal::DAQSystem::Scanning::MountPlateDesc ^>pl = gcnew SySal::DAQSystem::Scanning::MountPlateDesc();
			pl->BrickId = m_LoadPlateBrick;
			pl->PlateId = m_LoadPlatePlate;
			pl->TextDesc = gcnew System::String(m_LoadPlateTextDesc);
			pl->MapInitString = gcnew System::String(m_LoadPlateMapInit);
			ret = SS->LoadPlate(pl);
			m_Exception = "";
		}
		catch (System::Exception ^x)
		{
			m_Exception = x->Message;			
		}
		SendDlgItemMessage(IDC_TB_DONE, BM_SETCHECK, ret ? BST_CHECKED : BST_UNCHECKED);
		UpdateData(FALSE);
	} 
	else if (SendDlgItemMessage(IDC_TB_UNLOADPLATE, BM_GETCHECK) == BST_CHECKED)
	{
		bool ret = false;
		try
		{
			ret = SS->UnloadPlate();
			m_Exception = "";
		}
		catch (System::Exception ^x)
		{
			m_Exception = x->Message;			
		}
		SendDlgItemMessage(IDC_TB_DONE, BM_SETCHECK, ret ? BST_CHECKED : BST_UNCHECKED);
		UpdateData(FALSE);
	}
	else if (SendDlgItemMessage(IDC_TB_SCAN, BM_GETCHECK) == BST_CHECKED)
	{
		bool ret;
		try
		{
			gcroot<SySal::DAQSystem::Scanning::ZoneDesc ^>zone = gcnew SySal::DAQSystem::Scanning::ZoneDesc();
			zone->Series = m_ScanZoneId;
			zone->MinX = m_ScanMinX;
			zone->MinY = m_ScanMinY;
			zone->MaxX = m_ScanMaxX;
			zone->MaxY = m_ScanMaxY;
			zone->Outname = gcnew System::String(m_ScanOutname);
			zone->UsePresetSlope = m_ScanPresetSlope;
			zone->PresetSlope.X = m_ScanSlopeX;
			zone->PresetSlope.Y = m_ScanSlopeY;
			zone->PresetSlopeAcc.X = m_ScanSlopeAccX;
			zone->PresetSlopeAcc.Y = m_ScanSlopeAccY;
			if (m_ScanMoveNext)
			{
				gcroot<SySal::BasicTypes::Rectangle ^>rect = gcnew SySal::BasicTypes::Rectangle();
				rect->MinX = m_ScanMoveNextMinX;
				rect->MinY = m_ScanMoveNextMinY;
				rect->MaxX = m_ScanMoveNextMaxX;
				rect->MaxY = m_ScanMoveNextMaxY;
				ret = SS->ScanAndMoveToNext(zone, rect);
			}
			else ret = SS->Scan(zone);
			m_Exception = "";
		}
		catch (System::Exception ^x)
		{
			m_Exception = x->Message;			
		}
		SendDlgItemMessage(IDC_TB_DONE, BM_SETCHECK, ret ? BST_CHECKED : BST_UNCHECKED);
		UpdateData(FALSE);
	}
	else if (SendDlgItemMessage(IDC_TB_SETSINGLEPARAM, BM_GETCHECK) == BST_CHECKED)
	{
		bool ret = false;
		try
		{
			gcroot<System::String ^>obj = gcnew System::String(m_SetSingleParamObject);
			gcroot<System::String ^>parname = gcnew System::String(m_SetSingleParamParam);
			gcroot<System::String ^>parvalue = gcnew System::String(m_SetSingleParamValue);
			SS->SetSingleParameter(obj, parname, parvalue);
			m_Exception = "";
		}
		catch (System::Exception ^x)
		{
			m_Exception = x->Message;			
		}
		SendDlgItemMessage(IDC_TB_DONE, BM_SETCHECK, ret ? BST_CHECKED : BST_UNCHECKED);
		UpdateData(FALSE);
	}
	else if (SendDlgItemMessage(IDC_TB_SETOBJCONFIG, BM_GETCHECK) == BST_CHECKED)
	{
		bool ret = false;
		try
		{
			gcroot<System::String ^>obj = gcnew System::String(m_SetObjectConfigObject);
			gcroot<System::String ^>cfg = gcnew System::String(m_SetObjectConfigConfig);
			SS->SetObjectConfiguration(obj, cfg);
			m_Exception = "";
		}
		catch (System::Exception ^x)
		{
			m_Exception = x->Message;			
		}
		SendDlgItemMessage(IDC_TB_DONE, BM_SETCHECK, ret ? BST_CHECKED : BST_UNCHECKED);
		UpdateData(FALSE);
	}
	else if (SendDlgItemMessage(IDC_TB_SETSCANLAYOUT, BM_GETCHECK) == BST_CHECKED)
	{
		bool ret = false;
		try
		{
			gcroot<System::String ^>lay = gcnew System::String(m_SetScanLayoutLayout);
			SS->SetScanLayout(lay);
			m_Exception = "";
		}
		catch (System::Exception ^x)
		{
			m_Exception = x->Message;			
		}
		SendDlgItemMessage(IDC_TB_DONE, BM_SETCHECK, ret ? BST_CHECKED : BST_UNCHECKED);
		UpdateData(FALSE);
	}
	else if (SendDlgItemMessage(IDC_TB_MANUALCHECK, BM_GETCHECK) == BST_CHECKED)
	{
		SySal::DAQSystem::Scanning::ManualCheck::OutputBaseTrack mchko;
		mchko.CheckDone = false;
		try
		{
			SySal::DAQSystem::Scanning::ManualCheck::InputBaseTrack mchki;
			mchki.Id = m_ManualCheckId;
			mchki.Position.X = m_ManualCheckPosX;
			mchki.Position.Y = m_ManualCheckPosY;
			mchki.Slope.X = m_ManualCheckSlopeX;
			mchki.Slope.Y = m_ManualCheckSlopeY;
			mchki.PositionTolerance = m_ManualCheckPosTol;
			mchki.SlopeTolerance = m_ManualCheckSlopeTol;
			mchko = SS->RequireManualCheck(mchki);
			m_ManualCheckDone = mchko.CheckDone;
			m_ManualCheckFound = mchko.Found;
			m_ManualCheckOutGrains = mchko.Grains;
			m_ManualCheckOutPosX = mchko.Position.X;
			m_ManualCheckOutPosY = mchko.Position.Y;
			m_ManualCheckOutSlopeX = mchko.Slope.X;
			m_ManualCheckOutSlopeY = mchko.Slope.Y;
			m_Exception = "";
		}
		catch (System::Exception ^x)
		{
			m_Exception = x->Message;			
		}
		SendDlgItemMessage(IDC_TB_DONE, BM_SETCHECK, mchko.CheckDone ? BST_CHECKED : BST_UNCHECKED);
		UpdateData(FALSE);
	}
	else if (SendDlgItemMessage(IDC_TB_GETFOGTHICKNESS, BM_GETCHECK) == BST_CHECKED)
	{
		SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet fgthks;
		bool ret = false;
		try
		{
			fgthks = SS->GetFogAndThickness();
			m_TopFog = fgthks.TopFogGrains_1000MicronCubed;
			m_BottomFog = fgthks.BottomFogGrains_1000MicronCubed;
			m_TopThickness = fgthks.TopThickness;
			m_BottomThickness = fgthks.BottomThickness;
			m_BaseThickness = fgthks.BaseThickness;
			m_Exception = "";
			ret = true;
		}
		catch (System::Exception ^x)
		{
			m_Exception = x->Message;			
		}
		SendDlgItemMessage(IDC_TB_DONE, BM_SETCHECK, ret ? BST_CHECKED : BST_UNCHECKED);
		UpdateData(FALSE);		
	}	
	return 0;
}
void CTestBench::OnBnClickedTbCheckdone()
{
	SendDlgItemMessage(IDC_TB_CHECKDONE, BM_SETCHECK, m_ManualCheckDone ? BST_CHECKED : BST_UNCHECKED, 0);	
}

void CTestBench::OnBnClickedTbFound()
{
	SendDlgItemMessage(IDC_TB_FOUND, BM_SETCHECK, m_ManualCheckFound ? BST_CHECKED : BST_UNCHECKED, 0);
}

void CTestBench::OnBnClickedTbLoadscanlayout()
{
	CFileDialog ofn(TRUE, 0, 0, OFN_FILEMUSTEXIST, "XML files (*.xml)|*.xml", this);
	if (ofn.DoModal() == IDOK)
	{
		FILE *f = fopen(ofn.GetFileName(), "rb");
		if (f)
		{
			fseek(f, 0, SEEK_END);
			long len = ftell(f);
			fseek(f, 0, SEEK_SET);
			char *cbuff = (char *)malloc(len + 1);
			if (cbuff)
			{
				fread(cbuff, 1, len + 1, f);
				GetDlgItem(IDC_TB_SETSCANLAYOUT_LAYOUT)->SetWindowTextA(cbuff);
				free(cbuff);
			}
			fclose(f);
		}
	}	
}
