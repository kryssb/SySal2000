// InteractiveTracking.cpp : implementation file
//

#include "stdafx.h"
#include "videoimagescanner.h"
#include "InteractiveTracking.h"
#include "SelectNameDlg.h"
#include "SelectObjectDlg.h"
#include "Tracker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInteractiveTracking dialog


CInteractiveTracking::CInteractiveTracking(HWND *phwnd, ISySalDataIO *iio, IClusterFinder *icl, IObjective *iob, ITracker *itk, ITrackFitter *ift, CWnd* pParent /*=NULL*/)
	: CDialog(CInteractiveTracking::IDD, pParent), phWnd(phwnd), pData(0), iIO(iio), iCl(icl), iOb(iob), iTk(itk), iFt(ift), pPSpace(0), pCorrSpace(0), iTk2(0), iFt2(0), pFSSpace(0)
{
	//{{AFX_DATA_INIT(CInteractiveTracking)
	m_Equalization = FALSE;
	m_Iterations = 1;
	m_RelativeThreshold = FALSE;
	m_MaxGrains = 10000;
	m_MaxTracks = 100;
	m_Shrinkage = 1.9f;
	m_EndLayer0 = 0;
	m_Layers0 = 0;
	m_EndLayer1 = 0;
	m_Layers1 = 0;
	m_StartLayer0 = 0;
	m_StartLayer1 = 0;
	m_Threshold0 = 0;
	m_Threshold1 = 0;
	m_MaxFlatTracks = 100;
	m_MaxFlatStripsInTrack = 20;
	//}}AFX_DATA_INIT
	InvImageMat[0][0] = InvImageMat[1][1] = 1.f;
	InvImageMat[1][0] = InvImageMat[0][1] = 0.f;
	YCenter = ZCenter = 0;
	TopDepth = 0.f;
	DeltaDepth = 1.f;
	pTSpace[0] = pTSpace[1] = 0;
	CountOfTracks[0] = 0;
	CountOfTracks[1] = 0;
	pFSpace[0] = pFSpace[1] = 0;
	if (!iTk) iTk2 = 0;
	else if (iTk->QueryInterface(IID_ITracker2, (void **)&iTk2) != S_OK) iTk2 = 0;
	if (!iFt) iFt2 = 0;
	else if (iFt->QueryInterface(IID_ITrackFitter2, (void **)&iFt2) != S_OK) iFt2 = 0;
}

CInteractiveTracking::~CInteractiveTracking() 
{
	if (iFt2) iFt2->Release();
	if (iTk2) iTk2->Release();
	if (pData) CoTaskMemFree(pData);
	if (pFSpace[0]) free(pFSpace[0]);
	if (pFSpace[1]) free(pFSpace[1]);
	if (pFSSpace) free(pFSSpace);
	if (pTSpace[0]) free(pTSpace[0]);
	if (pTSpace[1]) free(pTSpace[1]);
	if (pPSpace) free(pPSpace);
	if (pCorrSpace) free(pCorrSpace);
	};

void CInteractiveTracking::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInteractiveTracking)
	DDX_Control(pDX, IDC_IT_CLUSTERPROGRESS, m_ClusterProgress);
	DDX_Control(pDX, IDC_IT_AVGTIME, m_AvgTime);
	DDX_Check(pDX, IDC_IT_EQUALIZATION, m_Equalization);
	DDX_Text(pDX, IDC_IT_ITERATIONS, m_Iterations);
	DDV_MinMaxUInt(pDX, m_Iterations, 1, 10000);
	DDX_Check(pDX, IDC_IT_RELTHRESHOLD, m_RelativeThreshold);
	DDX_Text(pDX, IDC_IT_MAXGRAINS, m_MaxGrains);
	DDV_MinMaxUInt(pDX, m_MaxGrains, 1, 100000);
	DDX_Text(pDX, IDC_IT_MAXTRACKS, m_MaxTracks);
	DDV_MinMaxUInt(pDX, m_MaxTracks, 1, 1000);
	DDX_Text(pDX, IDC_IT_SHRINKAGE, m_Shrinkage);
	DDV_MinMaxFloat(pDX, m_Shrinkage, 1.f, 3.f);
	DDX_Text(pDX, IDC_IT_ENDLAYER0, m_EndLayer0);
	DDX_Text(pDX, IDC_IT_LAYERS0, m_Layers0);
	DDX_Text(pDX, IDC_IT_ENDLAYER1, m_EndLayer1);
	DDX_Text(pDX, IDC_IT_LAYERS1, m_Layers1);
	DDX_Text(pDX, IDC_IT_STARTLAYER0, m_StartLayer0);
	DDX_Text(pDX, IDC_IT_STARTLAYER1, m_StartLayer1);
	DDX_Text(pDX, IDC_IT_THRESHOLD0, m_Threshold0);
	DDX_Text(pDX, IDC_IT_THRESHOLD1, m_Threshold1);
	DDX_Text(pDX, IDC_IT_MAXFLATTRACKS, m_MaxFlatTracks);
	DDV_MinMaxUInt(pDX, m_MaxFlatTracks, 10, 1000);
	DDX_Text(pDX, IDC_IT_MAXFLATSTRIPSINTRACK, m_MaxFlatStripsInTrack);
	DDV_MinMaxUInt(pDX, m_MaxFlatStripsInTrack, 10, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInteractiveTracking, CDialog)
	//{{AFX_MSG_MAP(CInteractiveTracking)
	ON_BN_CLICKED(IDC_IT_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_IT_SAVE, OnSave)
	ON_BN_CLICKED(IDC_IT_SAVECONFIG, OnSaveConfig)
	ON_BN_CLICKED(IDC_IT_EDITCONFIG, OnEditConfig)
	ON_BN_CLICKED(IDC_IT_TRACK, OnTrack)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInteractiveTracking message handlers

void CInteractiveTracking::OnLoad() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (pData)
	{
		CoTaskMemFree(pData);
		pData = 0;
		};
	UINT ExtErrInfo;
	if (iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)&pData, &ExtErrInfo, 0) != S_OK)
	{
		CString RetCode;
		RetCode.Format("Error Code: %08X", ExtErrInfo);
		MessageBox(RetCode, "I/O Error", MB_ICONERROR | MB_OK);
		if (pData)
		{
			CoTaskMemFree(pData);
			pData = 0;			
			};
		return;
		};
	if (pData->Hdr.InfoType != (BULK_IMAGE_SECTION | BULK_HEADER_BYTES) &&
		pData->Hdr.InfoType != (BULK_IMAGEPRED_SECTION | BULK_HEADER_BYTES) &&
		pData->Hdr.InfoType != (BULK_CLUSTER_SECTION | BULK_HEADER_BYTES) &&
		pData->Hdr.InfoType != (BULK_CLUSTERPRED_SECTION | BULK_HEADER_BYTES))
	{
		CString FormatCode;
		FormatCode.Format("Info: %02X Header: %04X", pData->Hdr.InfoType, pData->Hdr.HeaderFormat);
		MessageBox(FormatCode, "Unsupported Format", MB_ICONERROR | MB_OK);
		CoTaskMemFree(pData);
		pData = 0;
		}
	else
	{
		if ((pData->Hdr.InfoType == (BULK_IMAGE_SECTION | BULK_HEADER_BYTES)) && !iCl)
		{
			MessageBox("A Cluster Finder is required to handle images!", "Config Error", MB_ICONERROR | MB_OK);
			CoTaskMemFree(pData);
			pData = 0;
			};
		m_Layers0 = m_Layers1 = 0;
		if ((pData->Hdr.InfoType == (BULK_IMAGE_SECTION | BULK_HEADER_BYTES)) || 
			(pData->Hdr.InfoType == (BULK_IMAGEPRED_SECTION | BULK_HEADER_BYTES)))
		{
			int i = 0;
			while (i < pData->BPhSeq.Hdr.Frames && pData->BPhSeq.pImages[i].Z > pData->BPhSeq.Hdr.RelevantZs.TopExt) i++;
			m_Layers0 = i;
			while (i < pData->BPhSeq.Hdr.Frames && pData->BPhSeq.pImages[i].Z >= pData->BPhSeq.Hdr.RelevantZs.TopInt) i++;
			m_Layers0 = i - m_Layers0;
			while (i < pData->BPhSeq.Hdr.Frames && pData->BPhSeq.pImages[i].Z > pData->BPhSeq.Hdr.RelevantZs.BottomInt) i++;
			m_Layers1 = i;
			while (i < pData->BPhSeq.Hdr.Frames && pData->BPhSeq.pImages[i].Z >= pData->BPhSeq.Hdr.RelevantZs.BottomExt) i++;
			m_Layers1 = i - m_Layers1;
			}
		else
		{
			int i = 0;
			while (i < pData->BCDmp.Hdr.Frames && pData->BCDmp.pPlanes[i].Z > pData->BCDmp.Hdr.RelevantZs.TopExt) i++;
			m_Layers0 = i;
			while (i < pData->BCDmp.Hdr.Frames && pData->BCDmp.pPlanes[i].Z >= pData->BCDmp.Hdr.RelevantZs.TopInt) i++;
			m_Layers0 = i - m_Layers0;
			while (i < pData->BCDmp.Hdr.Frames && pData->BCDmp.pPlanes[i].Z > pData->BCDmp.Hdr.RelevantZs.BottomInt) i++;
			m_Layers1 = i;
			while (i < pData->BCDmp.Hdr.Frames && pData->BCDmp.pPlanes[i].Z >= pData->BCDmp.Hdr.RelevantZs.BottomExt) i++;
			m_Layers1 = i - m_Layers1;
			};
		m_EndLayer0 = m_Layers0 ? (m_Layers0 - 1) : 0;
		m_EndLayer1 = m_Layers1 ? (m_Layers1 - 1) : 0;
		UpdateData(FALSE);
		};
	
}

void CInteractiveTracking::OnSave() 
{
	// TODO: Add your control notification handler code here
	if (pTSpace && iIO)
	{	
		BYTE FieldHistory[2] = {0, 0};
		IO_BULK_Tracks Tks;
		Tks.Hdr.Type.HeaderFormat = BULK_HEADER_TYPE;
		Tks.Hdr.Type.InfoType = BULK_HEADER_BYTES | BULK_TRACK_SECTION;
		Tks.Hdr.SideSlopeTolerance = Tks.Hdr.GlobalSlopeTolerance = Tks.Hdr.GoodSlopeTolerance = 0.f;
		Tks.Hdr.FCount = 1;
		Tks.Hdr.BTCount[0] = CountOfFlatTracks[0];
		Tks.Hdr.BTCount[1] = CountOfFlatTracks[1];
		Tks.Hdr.TCount[0] = CountOfTracks[0];
		Tks.Hdr.TCount[1] = CountOfTracks[1];
		Tks.Hdr.CodingMode = BULK_COMPRESSION_NULL;
		Tks.Hdr.FitCorrectionDataSize = 0;
		if (iFt) 
			if (iFt->GetCorrectionDataSize((UINT *)&Tks.Hdr.FitCorrectionDataSize) != S_OK)
				Tks.Hdr.FitCorrectionDataSize = 0;
		Tks.Hdr.YSlope = Tks.Hdr.ZSlope = 0.f;
		if ((pData->Hdr.InfoType == (BULK_HEADER_BYTES | BULK_IMAGE_SECTION)) || 
			(pData->Hdr.InfoType == (BULK_HEADER_BYTES | BULK_IMAGEPRED_SECTION)))
		{
			Tks.Hdr.ID = pData->BPhSeq.Hdr.ID;
			Tks.Hdr.YPos = pData->BPhSeq.Hdr.YPos;
			Tks.Hdr.ZPos = pData->BPhSeq.Hdr.ZPos;
			Tks.Hdr.RelevantZs.TopExt = pData->BPhSeq.Hdr.RelevantZs.TopExt;
			Tks.Hdr.RelevantZs.TopInt = pData->BPhSeq.Hdr.RelevantZs.TopInt;
			Tks.Hdr.RelevantZs.BottomExt = pData->BPhSeq.Hdr.RelevantZs.BottomExt;
			Tks.Hdr.RelevantZs.BottomInt = pData->BPhSeq.Hdr.RelevantZs.BottomInt;
			}
		else
		{
			Tks.Hdr.ID = pData->BCDmp.Hdr.ID;
			Tks.Hdr.YPos = pData->BCDmp.Hdr.YPos;
			Tks.Hdr.ZPos = pData->BCDmp.Hdr.ZPos;
			Tks.Hdr.RelevantZs.TopExt = pData->BCDmp.Hdr.RelevantZs.TopExt;
			Tks.Hdr.RelevantZs.TopInt = pData->BCDmp.Hdr.RelevantZs.TopInt;
			Tks.Hdr.RelevantZs.BottomExt = pData->BCDmp.Hdr.RelevantZs.BottomExt;
			Tks.Hdr.RelevantZs.BottomInt = pData->BCDmp.Hdr.RelevantZs.BottomInt;
			};
		Tks.FieldHistory = FieldHistory;
		Tks.pTracks[0] = pTSpace[0];
		Tks.pTracks[1] = pTSpace[1];
		Tks.pFlatTracks[0] = pFSpace[0];
		Tks.pFlatTracks[1] = pFSpace[1];
		UINT ExtErrInfo;
		if (iIO->Write((HSySalHANDLE)m_hWnd, (BYTE *)&Tks, &ExtErrInfo, 0) != S_OK)
		{
			CString Temp;
			Temp.Format("Error code: %08X", ExtErrInfo);
			MessageBox(Temp, "File Error", MB_ICONERROR | MB_OK);
			}
		else MessageBox("Tracks saved!", "Success", MB_ICONINFORMATION | MB_OK);
		};
}

void CInteractiveTracking::OnSaveConfig() 
{
	// TODO: Add your control notification handler code here
	SySalConfig TempConfig;
	TempConfig.CountOfItems = 0;
	TempConfig.pItems = 0;
	TempConfig.Name[0] = 0;
	ISySalObject *iSy = 0;
	{
		SySalConnection Slots[3] = 
		{
			{SYSAL_CONN_TYPE_INTERFACE, "Objective", iOb},
			{SYSAL_CONN_TYPE_INTERFACE, "Tracker", iTk},
			{SYSAL_CONN_TYPE_INTERFACE, "Track Fitter", iFt}
			};
		CSelectObjectDlg MyDlg(3, Slots, this);
		if (MyDlg.DoModal() == IDOK)
		{
			if (MyDlg.m_iSel->QueryInterface(IID_ISySalObject, (void **)&iSy) != S_OK) 
			{
				MessageBox("Type consistency check failed!", "COM Error", MB_ICONERROR | MB_OK);
				return;
				};
			}
		else return;
		};
	try
	{
		if (iSy->GetConfig(&TempConfig) != S_OK)
		{
			MessageBox("Can't get object config", "Object Error", MB_ICONERROR | MB_OK);
			throw 1;
			};

		CSelectNameDlg MyDlg(this);
		MyDlg.m_Name = TempConfig.Name;
		if (MyDlg.DoModal() != IDOK) throw 3;
		strncpy(TempConfig.Name, MyDlg.m_Name, SYSAL_MAXCONFIG_NAME_LEN);

		CRegKey MotherKey, ConfigKey;
		if (MotherKey.Open(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Configs", KEY_READ | KEY_WRITE) != ERROR_SUCCESS)
		{
			MessageBox("Can't open HKEY_LOCAL_MACHINE\\Software\\SySal2\\Configs\nThe registry might be corrupt"
				"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
			throw 4;
			};
		MotherKey.RecurseDeleteKey(TempConfig.Name);
		if (ConfigKey.Create(MotherKey, TempConfig.Name, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE) != ERROR_SUCCESS)
		{
			MessageBox("Can't save the specified config into registry\nThe registry might be corrupt"
				"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
			MotherKey.Close();
			throw 5;
			};
		ConfigKey.Close();
		ConfigKey.Open(MotherKey, TempConfig.Name, KEY_READ | KEY_WRITE);
		int i;
		for (i = 0; i < TempConfig.CountOfItems; i++)
		{
			char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN + 1];
			char Value[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN + 1];
			Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN] = 0;
			Value[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN] = 0;
			strncpy(Name, TempConfig.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			strncpy(Value, TempConfig.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
			if (ConfigKey.SetValue(Value, Name) != ERROR_SUCCESS)
			{
				CString Temp;
				Temp.Format("Error entering %s with value %s into registry\nThe registry might be corrupt"
					"\nRun REGEDIT to repair the registry");
				MessageBox(Temp, "Registry Error", MB_ICONERROR | MB_OK);
				ConfigKey.Close();
				MotherKey.Close();
				throw 6;
				};
			};
		ConfigKey.Close();
		MotherKey.Close();
		}
	catch (...)
	{
		if (iSy) iSy->Release();
		if (TempConfig.pItems) CoTaskMemFree(TempConfig.pItems);
		return;
		};
	if (iSy) iSy->Release();
	if (TempConfig.pItems) CoTaskMemFree(TempConfig.pItems);
	MessageBox("Config updated!", "Success", MB_ICONINFORMATION | MB_OK);
}

void CInteractiveTracking::OnEditConfig() 
{
	// TODO: Add your control notification handler code here
	SySalConfig TempConfig;
	TempConfig.CountOfItems = 0;
	TempConfig.pItems = 0;
	TempConfig.Name[0] = 0;
	ISySalObject *iSy = 0;
	{
		SySalConnection Slots[3] = 
		{
			{SYSAL_CONN_TYPE_INTERFACE, "Objective", iOb},
			{SYSAL_CONN_TYPE_INTERFACE, "Tracker", iTk},
			{SYSAL_CONN_TYPE_INTERFACE, "Track Fitter", iFt}
			};
		CSelectObjectDlg MyDlg(3, Slots, this);
		if (MyDlg.DoModal() == IDOK)
		{
			if (MyDlg.m_iSel->QueryInterface(IID_ISySalObject, (void **)&iSy) != S_OK) 
			{
				MessageBox("Type consistency check failed!", "COM Error", MB_ICONERROR | MB_OK);
				return;
				};
			}
		else return;
		};
	if (iSy->GetConfig(&TempConfig) != S_OK)
	{
		MessageBox("Can't get object config", "Object Error", MB_ICONERROR | MB_OK);
		iSy->Release();
		if (TempConfig.pItems) CoTaskMemFree(TempConfig.pItems);
		return;
		};
	if (iSy->EditConfig(&TempConfig, (HSySalHANDLE)m_hWnd) == S_OK) 
	{
		if (iSy->SetConfig(&TempConfig) == S_OK) MessageBox("Object configured!", "Success", MB_ICONINFORMATION | MB_OK);
		else MessageBox("Can't configure object!", "Object Error", MB_ICONERROR | MB_OK);
		};
	iSy->Release();
	if (TempConfig.pItems) CoTaskMemFree(TempConfig.pItems);
}

void CInteractiveTracking::OnTrack() 
{
	// TODO: Add your control notification handler code here
	int i, s;
	UINT corrsize = 0;
	UpdateData();
	CameraSpec TempCamSpec;
	if (iOb->GetSpecs(&TempCamSpec) != S_OK)
		MessageBox("Can't get camera specifications!\nCheck Objective.", "Error", MB_ICONERROR | MB_OK);
	float ImageMat[2][2] = {{1.f, 0.f}, {0.f, 1.f}};
	InvImageMat[0][0] = InvImageMat[1][1] = 1.f;
	InvImageMat[1][0] = InvImageMat[0][1] = 0.f;
	YCenter = ZCenter = 0.f;
	TopDepth = 0.f;
	float BottomDepth = -1.f;
	DeltaDepth = 1.f;
	if (pCorrSpace) free(pCorrSpace);
	pCorrSpace = 0;
	if (iFt) 
	{
		if (iFt->GetCorrectionDataSize(&corrsize) != S_OK)
		{
			MessageBox("Can't get correction data size!", "Tracking Error", MB_ICONERROR | MB_OK);
			return;
			};
		pCorrSpace = malloc(corrsize * 2 * (m_MaxTracks + m_MaxFlatTracks));
		if (!pCorrSpace)
		{
			MessageBox("Can't allocate memory for correction data!", "Tracking Error", MB_ICONERROR | MB_OK);
			return;
			}
		};
	if (pTSpace[0]) 
	{
		free(pTSpace[0]);
		pTSpace[0] = 0;
		};
	if (pTSpace[1]) 
	{
		free(pTSpace[1]);
		pTSpace[1] = 0;
		};
	pTSpace[0] = (Track *)malloc(sizeof(Track) * m_MaxTracks);
	pTSpace[1] = (Track *)malloc(sizeof(Track) * m_MaxTracks);
	if (pFSpace[0]) 
	{
		free(pFSpace[0]);
		pFSpace[0] = 0;
		};
	if (pFSpace[1]) 
	{
		free(pFSpace[1]);
		pFSpace[1] = 0;
		};
	pFSpace[0] = (FlatTrack *)malloc(sizeof(FlatTrack) * m_MaxFlatTracks);
	pFSpace[1] = (FlatTrack *)malloc(sizeof(FlatTrack) * m_MaxFlatTracks);
	if (!pTSpace[0] || !pTSpace[1])
	{
		MessageBox("Can't allocate memory for tracks!", "Tracking Error", MB_ICONERROR | MB_OK);
		return;
		};
	if (pPSpace) free(pPSpace);
	pPSpace = (TVector *)malloc(sizeof(TVector) * m_MaxTracks * (m_Layers0 + m_Layers1));
	if (!pPSpace)
	{
		MessageBox("Can't allocate memory for track grains!", "Tracking Error", MB_ICONERROR | MB_OK);
		return;
		};
	if (pFSSpace) free(pFSSpace);
	pFSSpace = (FlatStrip *)malloc(sizeof(FlatStrip) * m_MaxFlatStripsInTrack * 2 * m_MaxFlatTracks);
	if (!pFSSpace)
	{
		MessageBox("Can't allocate memory for flat strips!", "Tracking Error", MB_ICONERROR | MB_OK);
		return;
		};
	for (s = 0; s < 2; s++)
	{
		for (i = 0; i < m_MaxTracks; i++)
		{
			pTSpace[s][i].pPoints = pPSpace + i * (s ? m_Layers1 : m_Layers0) + s * m_Layers0 * m_MaxTracks;
			pTSpace[s][i].Field = 0;
			pTSpace[s][i].pCorrection = (BYTE *)pCorrSpace + corrsize * (i + s * m_MaxTracks);
			pTSpace[s][i].Intercept.X = pTSpace[s][i].Intercept.Y = pTSpace[s][i].Intercept.Z = 0.f;
			pTSpace[s][i].InterceptErrors.X = pTSpace[s][i].InterceptErrors.Y = pTSpace[s][i].InterceptErrors.Z = 0.f;
			pTSpace[s][i].Slope.X = pTSpace[s][i].Slope.Y = pTSpace[s][i].Slope.Z = 0.f;
			pTSpace[s][i].SlopeErrors.X = pTSpace[s][i].SlopeErrors.Y = pTSpace[s][i].SlopeErrors.Z = 0.f;
			pTSpace[s][i].FirstZ = pTSpace[s][i].LastZ = 0.f;
			pTSpace[s][i].Sigma = 0.f;
			pTSpace[s][i].Valid = false;
			};
		for (i = 0; i < m_MaxFlatTracks; i++)
		{
			pFSpace[s][i].pStrips = pFSSpace + (i + s * m_MaxFlatTracks) * m_MaxFlatStripsInTrack;
			pFSpace[s][i].Field = 0;
			pFSpace[s][i].pCorrection = (BYTE *)pCorrSpace + corrsize * (i + s * m_MaxFlatTracks + 2 * m_MaxTracks);
			pFSpace[s][i].Intercept.X = pFSpace[s][i].Intercept.Y = pFSpace[s][i].Intercept.Z = 0.f;
			pFSpace[s][i].InterceptErrors.X = pFSpace[s][i].InterceptErrors.Y = pFSpace[s][i].InterceptErrors.Z = 0.f;
			pFSpace[s][i].Slope.X = pFSpace[s][i].Slope.Y = pFSpace[s][i].Slope.Z = 0.f;
			pFSpace[s][i].SlopeErrors.X = pFSpace[s][i].SlopeErrors.Y = pFSpace[s][i].SlopeErrors.Z = 0.f;
			pFSpace[s][i].ZBase = 0.f;
			pFSpace[s][i].LastL = 0.f;
			pFSpace[s][i].VertSigma = pFSpace[s][i].HorizSigma = 0.f;
			pFSpace[s][i].Valid = false;	
			};
		};
	if ((m_Layers0 + m_Layers1) > 0)
	{
		if ((pData->Hdr.InfoType == (BULK_HEADER_BYTES | BULK_IMAGE_SECTION)) || 
			(pData->Hdr.InfoType == (BULK_HEADER_BYTES | BULK_IMAGEPRED_SECTION)))
		{	
			TopDepth = (pData->BPhSeq.Hdr.RelevantZs.TopExt - pData->BPhSeq.Hdr.RelevantZs.TopInt) * m_Shrinkage + pData->BPhSeq.Hdr.RelevantZs.TopInt;
			BottomDepth = (pData->BPhSeq.Hdr.RelevantZs.BottomExt - pData->BPhSeq.Hdr.RelevantZs.BottomInt) * m_Shrinkage + pData->BPhSeq.Hdr.RelevantZs.BottomInt;
			ImageMat[0][0] = pData->BPhSeq.Hdr.ImageMat[0][0] / TempCamSpec.PixelToMicronX;
			ImageMat[0][1] = pData->BPhSeq.Hdr.ImageMat[0][1] / TempCamSpec.PixelToMicronY;
			ImageMat[1][0] = pData->BPhSeq.Hdr.ImageMat[1][0] / TempCamSpec.PixelToMicronX;
			ImageMat[1][1] = pData->BPhSeq.Hdr.ImageMat[1][1] / TempCamSpec.PixelToMicronY;
			YCenter = pData->BPhSeq.Hdr.YCenter;
			ZCenter = pData->BPhSeq.Hdr.ZCenter;
			}
		else
		{
			TopDepth = (pData->BCDmp.Hdr.RelevantZs.TopExt - pData->BCDmp.Hdr.RelevantZs.TopInt) * m_Shrinkage + pData->BCDmp.Hdr.RelevantZs.TopInt;
			BottomDepth = (pData->BCDmp.Hdr.RelevantZs.BottomExt - pData->BCDmp.Hdr.RelevantZs.BottomInt) * m_Shrinkage + pData->BCDmp.Hdr.RelevantZs.BottomInt;
			ImageMat[0][0] = pData->BCDmp.Hdr.ImageMat[0][0] / TempCamSpec.PixelToMicronX;
			ImageMat[0][1] = pData->BCDmp.Hdr.ImageMat[0][1] / TempCamSpec.PixelToMicronY;
			ImageMat[1][0] = pData->BCDmp.Hdr.ImageMat[1][0] / TempCamSpec.PixelToMicronX;
			ImageMat[1][1] = pData->BCDmp.Hdr.ImageMat[1][1] / TempCamSpec.PixelToMicronY;
			YCenter = pData->BCDmp.Hdr.YCenter;
			ZCenter = pData->BCDmp.Hdr.ZCenter;
			};
		};
	DeltaDepth = TopDepth - BottomDepth;
	float delta = ImageMat[0][0] * ImageMat[1][1] - ImageMat[0][1] * ImageMat[1][0];
	if (delta != 0.f) 
	{
		delta = 1.f / delta;
		InvImageMat[0][0] = delta * (ImageMat[1][1]);
		InvImageMat[0][1] = delta * (-ImageMat[0][1]);
		InvImageMat[1][0] = delta * (-ImageMat[1][0]);
		InvImageMat[1][1] = delta * (ImageMat[0][0]);
		};

	float avg = 0.f;
	CString RetString;
	{
		CTracker MyTrk(iCl, iFt, iFt2, iTk, iTk2, iOb);
		CountOfTracks[0] = CountOfTracks[1] = m_MaxTracks;
		CountOfFlatTracks[0] = CountOfFlatTracks[1] = m_MaxFlatTracks;
		UINT Thresholds[2] = {m_Threshold0, m_Threshold1};
		UINT StartLayer[2] = {m_StartLayer0, m_StartLayer1}; 
		UINT EndLayer[2] = {m_EndLayer0, m_EndLayer1};
		if (!MyTrk.FindTracks(pData, (UINT *)CountOfTracks, pTSpace, m_MaxGrains, m_RelativeThreshold, 
			Thresholds, m_Equalization, StartLayer, EndLayer, (UINT *)CountOfFlatTracks, pFSpace, m_MaxFlatStripsInTrack,
			m_Shrinkage, m_Iterations, &avg, &m_ClusterProgress, RetString))
			MessageBox(RetString, "Error", MB_ICONERROR | MB_OK);
		};
	CString TAvg;
	TAvg.Format("%.1f", avg);
	m_AvgTime.SetWindowText(TAvg);
	RedrawWindow();
}

LRESULT CInteractiveTracking::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam == SYSAL_ASYNC_STATUS_IDLE) 
	{
		*phWnd = 0;
		EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
		};
	return 0;
}

BOOL CInteractiveTracking::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInteractiveTracking::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (lpDrawItemStruct->CtlID == IDC_IT_SCREEN)
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		CWnd *pScreen = GetDlgItem(IDC_IT_SCREEN);
		CRect ScreenRect;
		pScreen->GetClientRect(&ScreenRect);
		ScreenRect.DeflateRect(2, 2);

		CBrush BlackBrush(RGB(0, 0, 0));	
		dc.FillRect(ScreenRect, &BlackBrush);
		CameraSpec TCS;
		TCS.Width = TCS.Height = TCS.WinWidth = TCS.WinHeight = 0;
		if (iOb) iOb->GetSpecs(&TCS);
		if (TCS.Width > 0 && TCS.Height > 0 && TCS.WinWidth > 0 && TCS.WinHeight > 0 || (!pTSpace))
		{			
			int i, j, s;
			for (s = 0; s < 2; s++)
			{
				for (i = 0; i < CountOfTracks[s]; i++)
				{
					if (pTSpace[s][i].Valid)
					{
						float X, Y, PX, PY;
						if (pTSpace[s][i].PointsN > 0)
						{
							PX = InvImageMat[0][0] * (pTSpace[s][i].pPoints[0].X - YCenter) + InvImageMat[0][1] * (pTSpace[s][i].pPoints[0].Y - ZCenter);
							PY = InvImageMat[1][0] * (pTSpace[s][i].pPoints[0].X - YCenter) + InvImageMat[1][1] * (pTSpace[s][i].pPoints[0].Y - ZCenter);
							X = (PX / TCS.PixelToMicronX + TCS.Width / 2 - TCS.OffX) * ScreenRect.Width() / TCS.WinWidth + ScreenRect.left;
							Y = (PY / TCS.PixelToMicronY + TCS.Height / 2 - TCS.OffY) * ScreenRect.Height() / TCS.WinHeight + ScreenRect.top;
							dc.MoveTo(X, Y);
							};
						for (j = 1; j < pTSpace[s][i].PointsN; j++)
						{
							float lev = (TopDepth - 0.5f * (pTSpace[s][i].pPoints[j].Z + pTSpace[s][i].pPoints[j - 1].Z)) / DeltaDepth;
							if (lev < 0.f) lev = 0.f;
							else if (lev > 1.f) lev = 1.f;
							CPen GrainPen(PS_SOLID, 1, RGB(255 * (1.f - lev * lev), 255 * (4.f * lev * (1.f - lev)), 255 * lev * (2.f - lev)));						
							CPen *pOldPen = dc.SelectObject(&GrainPen);
							PX = InvImageMat[0][0] * (pTSpace[s][i].pPoints[j].X - YCenter) + InvImageMat[0][1] * (pTSpace[s][i].pPoints[j].Y - ZCenter);
							PY = InvImageMat[1][0] * (pTSpace[s][i].pPoints[j].X - YCenter) + InvImageMat[1][1] * (pTSpace[s][i].pPoints[j].Y - ZCenter);
							X = (PX / TCS.PixelToMicronX + TCS.Width / 2 - TCS.OffX) * ScreenRect.Width() / TCS.WinWidth + ScreenRect.left;
							Y = (PY / TCS.PixelToMicronY + TCS.Height / 2 - TCS.OffY) * ScreenRect.Height() / TCS.WinHeight + ScreenRect.top;
							dc.LineTo(X, Y);
							dc.SelectObject(pOldPen);
							};
						};
					};
				for (i = 0; i < CountOfFlatTracks[s]; i++)
				{
					if (pFSpace[s][i].Valid)
					{
						float X, Y, PX, PY;
						if (pFSpace[s][i].StripsN > 0)
						{
							PX = InvImageMat[0][0] * (pFSpace[s][i].pStrips[0].X - YCenter) + InvImageMat[0][1] * (pFSpace[s][i].pStrips[0].Y - ZCenter);
							PY = InvImageMat[1][0] * (pFSpace[s][i].pStrips[0].X - YCenter) + InvImageMat[1][1] * (pFSpace[s][i].pStrips[0].Y - ZCenter);
							X = (PX / TCS.PixelToMicronX + TCS.Width / 2 - TCS.OffX) * ScreenRect.Width() / TCS.WinWidth + ScreenRect.left;
							Y = (PY / TCS.PixelToMicronY + TCS.Height / 2 - TCS.OffY) * ScreenRect.Height() / TCS.WinHeight + ScreenRect.top;
							dc.MoveTo(X, Y);
							};
						for (j = 1; j < pFSpace[s][i].StripsN; j++)
						{
							float lev = (TopDepth - 0.5f * (pFSpace[s][i].pStrips[j].Z + pFSpace[s][i].pStrips[j - 1].Z)) / DeltaDepth;
							if (lev < 0.f) lev = 0.f;
							else if (lev > 1.f) lev = 1.f;
							CPen StripPen(PS_SOLID, 3, RGB(255 * (1.f - lev * lev), 255 * (4.f * lev * (1.f - lev)), 255 * lev * (2.f - lev)));						
							CPen *pOldPen = dc.SelectObject(&StripPen);
							PX = InvImageMat[0][0] * (pFSpace[s][i].pStrips[j].X - YCenter) + InvImageMat[0][1] * (pFSpace[s][i].pStrips[j].Y - ZCenter);
							PY = InvImageMat[1][0] * (pFSpace[s][i].pStrips[j].X - YCenter) + InvImageMat[1][1] * (pFSpace[s][i].pStrips[j].Y - ZCenter);
							X = (PX / TCS.PixelToMicronX + TCS.Width / 2 - TCS.OffX) * ScreenRect.Width() / TCS.WinWidth + ScreenRect.left;
							Y = (PY / TCS.PixelToMicronY + TCS.Height / 2 - TCS.OffY) * ScreenRect.Height() / TCS.WinHeight + ScreenRect.top;
							dc.LineTo(X, Y);
							dc.SelectObject(pOldPen);
							};
						};
					};
				};
			};
		dc.Detach();
		}
	else CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
