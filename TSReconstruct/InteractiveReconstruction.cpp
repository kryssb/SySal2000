// InteractiveReconstruction.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "InteractiveReconstruction.h"
#include "EditConfig.h"
#include "SelectEventData.h"
#include <math.h>
#include <afxdlgs.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_ZOOM 0.5f
#define MAX_ZOOM 20.f
#define ZOOM_SLIDER_RANGE 100
#define ZOOM_SLIDER_PAGE  10
#define ZOOM_SLIDER_LINE  1

#define SHOW_RAW			0
#define SHOW_SEGMENTS		1
#define SHOW_TRACKSEGS		2
#define SHOW_TRACKS			3

static struct ColorVector
{
	float R, G, B;
	};

static ColorVector MatchColorTable[6] =
{
	{1.0, 0.5, 0.5},
	{0.5, 1.0, 0.5},
	{0.5, 0.5, 1.0},
	{1.0, 1.0, 0.5},
	{0.5, 1.0, 1.0},
	{1.0, 0.5, 1.0}
	};

/////////////////////////////////////////////////////////////////////////////
// CInteractiveReconstruction dialog


CInteractiveReconstruction::CInteractiveReconstruction(HWND *phwnd, ISySalDataIO *iio, ISySalDataIO *ipr, TSReconData *pTSRD, ISySalObject *iself, ConfigManagerInterface *pcmi, CWnd* pParent/* = NULL*/)
	: CDialog(CInteractiveReconstruction::IDD, pParent), phWnd(phwnd), iIO(iio), iPr(ipr), iED(0), pMatchDlg(0), iSelf(iself), pCMI(pcmi)
{
	if (CoCreateInstance(CLSID_EmulsionDisplay, NULL, CLSCTX_INPROC_SERVER, IID_IEmulsionDisplay, (void **)&iED) != S_OK) 
	{
		pParent->MessageBox("Can't create Emulsion Display!\nCheck for COM registration of EmuDisplay.dll and correct setup of DirectX 7.", "COM Error", MB_ICONERROR | MB_OK);
		throw 0;
		};
	//{{AFX_DATA_INIT(CInteractiveReconstruction)
	m_AlignmentData = _T("");
	m_ListFile = _T("");
	m_OnlyTracksFromVertex = FALSE;
	m_PassingThrough = FALSE;
	//}}AFX_DATA_INIT
	RM.SetReconstructionData(pTSRD);
	PD.Pos.X = PD.Pos.Y = 0.;
}


CInteractiveReconstruction::~CInteractiveReconstruction()
{
	if (pMatchDlg) 
	{
		delete pMatchDlg;
		pMatchDlg = 0;
		};
	if (iED) iED->Release();	
	};


void CInteractiveReconstruction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInteractiveReconstruction)
	DDX_Control(pDX, IDC_IR_ID, m_Id);
	DDX_Control(pDX, IDC_IR_NOTES, m_Notes);
	DDX_Control(pDX, IDC_IR_ZOOM, m_Zoom);
	DDX_Control(pDX, IDC_IR_ACTIONPROGRESS, m_ActionProgress);
	DDX_Control(pDX, IDC_IR_ACTION, m_Action);
	DDX_Text(pDX, IDC_IR_EALIGNMENTDATA, m_AlignmentData);
	DDX_Text(pDX, IDC_IR_ELISTFILE, m_ListFile);
	DDX_Check(pDX, IDC_IR_FROMVERTEX, m_OnlyTracksFromVertex);
	DDX_Check(pDX, IDC_IR_PASSINGTHROUGH, m_PassingThrough);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInteractiveReconstruction, CDialog)
	//{{AFX_MSG_MAP(CInteractiveReconstruction)
	ON_BN_CLICKED(IDC_IR_DEFAULTVIEW, OnDefaultView)
	ON_WM_DRAWITEM()
	ON_WM_KILLFOCUS()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_IR_SEL_ALIGNMENTDATA, OnSelAlignmentData)
	ON_BN_CLICKED(IDC_IR_SEL_LISTFILE, OnSelListFile)
	ON_BN_CLICKED(IDC_IR_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_IR_SHOWRAW, OnShowRaw)
	ON_BN_CLICKED(IDC_IR_SHOWSEGMENTS, OnShowSegments)
	ON_BN_CLICKED(IDC_IR_SHOWTRACKS, OnShowTracks)
	ON_BN_CLICKED(IDC_IR_SHOWTRACKSEGS, OnShowTrackSegments)
	ON_BN_CLICKED(IDC_IR_RECONSTRUCT, OnReconstruct)
	ON_BN_CLICKED(IDC_IR_EDITCONFIG, OnEditConfig)
	ON_BN_CLICKED(IDC_IR_LOAD_RECONSTRUCTION, OnLoadReconstruction)
	ON_BN_CLICKED(IDC_IR_SAVE, OnSave)
	ON_BN_CLICKED(IDC_IR_TOPOLOGY, OnTopology)
	ON_BN_CLICKED(IDC_IR_FROMVERTEX, OnFromVertex)
	ON_BN_CLICKED(IDC_IR_MATCHPRED, OnMatchPredictions)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_IR_PASSINGTHROUGH, OnPassingThrough)
	ON_BN_CLICKED(IDC_IR_SAVECONFIG, OnSaveConfig)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInteractiveReconstruction message handlers

void CInteractiveReconstruction::OnDefaultView() 
{
	// TODO: Add your control notification handler code here
	EDM.Dir.X = EDM.Dir.Y = 0.f;
	EDM.Dir.Z = -1.f;
	EDM.Norm.X = EDM.Norm.Z = 0.f;
	EDM.Norm.Y = -1.f;	
	Vector C = EDM.InterestingPoint - EDM.Distance * EDM.Dir;
	iED->SetZoom(EDM.Zoom);
	iED->SetCamera(C.X, C.Y, C.Z, EDM.Dir.X, EDM.Dir.Y, EDM.Dir.Z, EDM.Norm.X, EDM.Norm.Y, EDM.Norm.Z);
	iED->Render();
}

/*
void CInteractiveReconstruction::OnMouseRotate() 
{
	// TODO: Add your control notification handler code here
	EDM.MouseRotates = true;
}

void CInteractiveReconstruction::OnMouseZoom() 
{
	// TODO: Add your control notification handler code here
	EDM.MouseRotates = false;
}
*/

LRESULT CInteractiveReconstruction::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam == SYSAL_ASYNC_STATUS_IDLE) 
	{
		*phWnd = 0;
		EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
		};
	return 0;
}

BOOL CInteractiveReconstruction::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;
	HRESULT hRes = S_OK;
	if ((hRes = iED->InitWithWindow((int)(GetDlgItem(IDC_IR_SCREEN)->m_hWnd))) != S_OK)
	{
		if (hRes == S_FALSE)
			MessageBox("Can't init Emulsion Display!\nCheck for correct setup of DirectX 7.\nYour display should be set up for at least 65536 colors.",
				"DirectX Error", MB_ICONERROR | MB_OK);
		else if (hRes == E_INVALIDARG)
			MessageBox("Can't find display window!\nReport to Cristiano Bozza for support.",
				"Debug Info", MB_ICONERROR | MB_OK);
		else 
			MessageBox("Unknown error!\nReport to Cristiano Bozza for support.",
				"Debug Info", MB_ICONERROR | MB_OK);
		return FALSE;
		};
	EDM.ShowMode = SHOW_RAW;
	EDM.HasFocus = false;
	EDM.LastMousePoint.x = EDM.LastMousePoint.y = 0;
	EDM.InterestingPoint.X = EDM.InterestingPoint.Y = EDM.InterestingPoint.Z = 0.f;
	EDM.Dir.X = EDM.Dir.Y = 0.f;
	EDM.Dir.Z = -1.f;
	EDM.Norm.X = EDM.Norm.Z = 0.f;
	EDM.Norm.Y = -1.f;
	EDM.Distance = 10.f;	
	Vector C = EDM.InterestingPoint - EDM.Distance * EDM.Dir;
	EDM.MouseRotationMultiplier = 0.003f;
	EDM.MouseZoomMultiplier = 0.003f;
//	EDM.MouseRotates = true;	
	iED->SetCamera(C.X, C.Y, C.Z, EDM.Dir.X, EDM.Dir.Y, EDM.Dir.Z, EDM.Norm.X, EDM.Norm.Y, EDM.Norm.Z);
	m_Zoom.SetRange(0, ZOOM_SLIDER_RANGE);
	m_Zoom.SetPos(ZOOM_SLIDER_RANGE / 2);
	EDM.Zoom = MIN_ZOOM * exp(0.5f * log(MAX_ZOOM / MIN_ZOOM));
	iED->SetZoom(EDM.Zoom);
//	GetDlgItem(EDM.MouseRotates ? IDC_IR_ROTATE : IDC_IR_ZOOM)->SendMessage(BM_SETCHECK, BST_CHECKED);
	switch (EDM.ShowMode)
	{
		case SHOW_RAW:			GetDlgItem(IDC_IR_SHOWRAW)->SendMessage(BM_SETCHECK, BST_CHECKED);
								break;

		case SHOW_SEGMENTS:		GetDlgItem(IDC_IR_SHOWSEGMENTS)->SendMessage(BM_SETCHECK, BST_CHECKED);
								break;

		case SHOW_TRACKSEGS:	GetDlgItem(IDC_IR_SHOWTRACKSEGS)->SendMessage(BM_SETCHECK, BST_CHECKED);
								break;

		case SHOW_TRACKS:		GetDlgItem(IDC_IR_SHOWTRACKS)->SendMessage(BM_SETCHECK, BST_CHECKED);
								break;
		};
	m_Action.SetWindowText("Action: <Idle>");
	m_ActionProgress.SetPos(0);
	m_ActionProgress.SetRange(0, 100);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInteractiveReconstruction::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (nIDCtl != IDC_IR_SCREEN) CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
	else if (iED) iED->Render();
}

void CInteractiveReconstruction::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	EDM.HasFocus = false;	
}

void CInteractiveReconstruction::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDown(nFlags, point);
	EDM.HasFocus = true;
	EDM.LastMousePoint = point;
}

void CInteractiveReconstruction::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
	if (nFlags & MK_RBUTTON)
	{
		if (!EDM.HasFocus)
		{
			EDM.HasFocus = true;
			EDM.LastMousePoint = point;
			}
		else 
		{
			POINT DeltaMouse = {point.x - EDM.LastMousePoint.x, point.y - EDM.LastMousePoint.y};
			EDM.LastMousePoint = point;
			MouseRotate(DeltaMouse);
/*
			if (EDM.MouseRotates) MouseRotate(DeltaMouse);
			else MouseZoom(DeltaMouse);
*/
			};
		};
}

void CInteractiveReconstruction::MouseRotate(POINT DeltaMouse)
{
	if (!iED) return;
	float Theta = EDM.MouseRotationMultiplier * hypot(DeltaMouse.x, DeltaMouse.y);
	if (Theta > 0.f)
	{
		float Rx = -DeltaMouse.y / Theta * EDM.MouseRotationMultiplier;
		float Ry = DeltaMouse.x / Theta * EDM.MouseRotationMultiplier;		
		float C = cos(Theta), S = sin(Theta); 

		Vector B(
			EDM.Dir.Y * EDM.Norm.Z - EDM.Dir.Z * EDM.Norm.Y,
			EDM.Dir.Z * EDM.Norm.X - EDM.Dir.X * EDM.Norm.Z,
			EDM.Dir.X * EDM.Norm.Y - EDM.Dir.Y * EDM.Norm.X
			);

		Vector R
		(
			Rx * B.X + Ry * EDM.Norm.X, Rx * B.Y + Ry * EDM.Norm.Y, Rx * B.Z + Ry * EDM.Norm.Z
			);

		Vector T 
		(
			Ry * B.X - Rx * EDM.Norm.X, Ry * B.Y - Rx * EDM.Norm.Y, Ry * B.Z - Rx * EDM.Norm.Z
			);

		Vector N2
		(
			Ry * R.X - Rx * (C * T.X + S * EDM.Dir.X),
			Ry * R.Y - Rx * (C * T.Y + S * EDM.Dir.Y),
			Ry * R.Z - Rx * (C * T.Z + S * EDM.Dir.Z)
			);

		Vector D2
		(
			C * EDM.Dir.X - S * T.X, C * EDM.Dir.Y - S * T.Y, C * EDM.Dir.Z - S * T.Z
			);

		EDM.Dir = D2;
		EDM.Norm = N2;
		Vector CamPos = EDM.InterestingPoint - EDM.Distance * EDM.Dir;
		iED->SetCamera(CamPos.X, CamPos.Y, CamPos.Z, EDM.Dir.X, EDM.Dir.Y, EDM.Dir.Z, EDM.Norm.X, EDM.Norm.Y, EDM.Norm.Z);
		iED->Render();
		};
}

/*
void CInteractiveReconstruction::MouseZoom(POINT DeltaMouse)
{
	if (!iED) return;
	EDM.Zoom *= exp(DeltaMouse.y * EDM.MouseZoomMultiplier);
	if (EDM.Zoom < MIN_ZOOM) EDM.Zoom = MIN_ZOOM;
	else if (EDM.Zoom > MAX_ZOOM) EDM.Zoom = MAX_ZOOM;	
	iED->SetZoom(EDM.Zoom);
	iED->Render();
}
*/

void CInteractiveReconstruction::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if (iED) iED->Render();
	// Do not call CDialog::OnPaint() for painting messages
}

void CInteractiveReconstruction::OnSelAlignmentData() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, NULL, m_AlignmentData, OFN_FILEMUSTEXIST | OFN_EXPLORER, NULL, this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_AlignmentData = MyDlg.GetPathName();
		UpdateData(FALSE);
		};
}

void CInteractiveReconstruction::OnSelListFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, NULL, m_ListFile, OFN_FILEMUSTEXIST | OFN_EXPLORER, NULL, this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_ListFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};	
}

void CInteractiveReconstruction::OnLoad() 
{
	// TODO: Add your control notification handler code here
	m_Notes.SetWindowText("");
	UpdateData();
	if (m_ListFile == "") return;
	FILE *f = fopen(m_ListFile, "rt");
	if (!f)
	{
		MessageBox("Error opening list file!", "File Error", MB_ICONERROR | MB_OK);
		return;
		};
	CSelectEventData SelDlg(f, this);
	if ((SelDlg.DoModal() != IDOK) || (SelDlg.m_Selection < 0))
	{
		fclose(f);
		return;
		};
	fseek(f, SelDlg.m_Selection, SEEK_SET);
	
	if (pMatchDlg) 
	{
		delete pMatchDlg;
		pMatchDlg = 0;
		};
	RM.ClearTracks();
	if (iED) 
	{
		iED->Clear();
		iED->Render();
		};
	int N;
	CInteractiveReconstruction::AlignmentData *pData = LoadAlignmentData(&N);
	if (!pData) 
	{
		MessageBox("Error reading alignment data!", "File Error", MB_ICONERROR | MB_OK);
		fclose(f);
		return;
		};
	
	HCURSOR HOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
	if (!LoadTracks(f, N, pData))
	{		
		SetCursor(HOldCursor);
		if (pData) delete [] pData;
		MessageBox("Error loading tracks!", "File Error", MB_ICONERROR | MB_OK);
		fclose(f);
		return;
		};
	SetCursor(HOldCursor);
	delete [] pData;
	fclose(f);
	{
		IO_TS_Reconstruction *pTSRec = RM.AccessReconstruction();
		if (!pTSRec) m_Id.SetWindowText("");
		CString Temp;
		Temp.Format("%d/%d/%d/%d", pTSRec->Hdr.ID.Part[0], pTSRec->Hdr.ID.Part[1], pTSRec->Hdr.ID.Part[2], pTSRec->Hdr.ID.Part[3]);
		m_Id.SetWindowText(Temp);
		};
	Refresh();
}

CInteractiveReconstruction::AlignmentData * CInteractiveReconstruction::LoadAlignmentData(int *pN)
{	
	*pN = 0;
	if (m_AlignmentData == "") return 0;
	FILE *f = fopen(m_AlignmentData, "rt");
	if (!f) return 0;
	CInteractiveReconstruction::AlignmentData *pRet = 0;
	try
	{
		if (fscanf(f, "%d", pN) != 1) throw 0;
		pRet = new CInteractiveReconstruction::AlignmentData[*pN];
		int i;
		for (i = 0; i < *pN; i++)
			if (fscanf(f, "%d %f %f %f %f %f %f %f %f", 
				&pRet[i].SheetId, &pRet[i].SideAlign[0].X.DSlope, &pRet[i].SideAlign[0].X.DShrink,
				&pRet[i].SideAlign[0].Y.DSlope, &pRet[i].SideAlign[0].Y.DShrink,
				&pRet[i].SideAlign[1].X.DSlope, &pRet[i].SideAlign[1].X.DShrink,
				&pRet[i].SideAlign[1].Y.DSlope, &pRet[i].SideAlign[1].Y.DShrink) != 9) throw 1;
		fclose(f);
		f = 0;
		}
	catch (...)
	{
		if (pRet) delete [] pRet;
		if (f) fclose(f);
		*pN = 0;
		return false;
		};
	return pRet;
}

bool CInteractiveReconstruction::LoadTracks(FILE *f, int N, CInteractiveReconstruction::AlignmentData *pData)
{
	try
	{
		int Plates, StartSheet, i;
		float RefDepth;
		char FileName[1024];
		UINT ExtErrInfo;
		if (fscanf(f, "%d %d %d %d %d %d %f %f %f", &Plates, &StartSheet, &PD.Id.Part[0], 
			&PD.Id.Part[1], &PD.Id.Part[2], &PD.Id.Part[3], &PD.Pos.X, &PD.Pos.Y, &PD.Pos.Z) != 9) throw 0;
		if (StartSheet < 0 || (StartSheet + Plates - 1) > N) throw 0;		
		if (!RM.StartAdding(StartSheet, Plates, PD.Id, PD.Pos)) throw 1;
		for (i = 0; i < Plates; i++)
		{
			if (fscanf(f, "%f %s", &RefDepth, FileName) != 2) throw 2;
			IO_Data *pTracks = 0;
			if (iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)&pTracks, &ExtErrInfo, (UCHAR *)FileName) != S_OK) throw 3;
			if (pTracks->Hdr.InfoType != (BULK_HEADER_BYTES | BULK_TRACK_SECTION) || pTracks->Hdr.HeaderFormat != BULK_HEADER_TYPE) 
			{
				CoTaskMemFree(pTracks);
				throw 4;
				};
			TS_LayerInfo TempLayer;
			TempLayer.SheetId = StartSheet + i;
			TempLayer.RefDepth = RefDepth;
			TempLayer.SCount[0] = TempLayer.SCount[1] = 0;
			TempLayer.pSegments[0] = TempLayer.pSegments[1] = 0;
			TempLayer.GlobalSideAlign[0].DShrink[0] = pData[StartSheet + i - 1].SideAlign[0].X.DShrink;
			TempLayer.GlobalSideAlign[0].DShrink[1] = pData[StartSheet + i - 1].SideAlign[0].Y.DShrink;
			TempLayer.GlobalSideAlign[1].DShrink[0] = pData[StartSheet + i - 1].SideAlign[1].X.DShrink;
			TempLayer.GlobalSideAlign[1].DShrink[1] = pData[StartSheet + i - 1].SideAlign[1].Y.DShrink;
			TempLayer.GlobalSideAlign[0].DSlope[0] = pData[StartSheet + i - 1].SideAlign[0].X.DSlope;
			TempLayer.GlobalSideAlign[0].DSlope[1] = pData[StartSheet + i - 1].SideAlign[0].Y.DSlope;
			TempLayer.GlobalSideAlign[1].DSlope[0] = pData[StartSheet + i - 1].SideAlign[1].X.DSlope;
			TempLayer.GlobalSideAlign[1].DSlope[1] = pData[StartSheet + i - 1].SideAlign[1].Y.DSlope;
			TempLayer.pReserved[0] = TempLayer.pReserved[1] = TempLayer.pReserved[2] = TempLayer.pReserved[3] = 0;
			TempLayer.RelevantZs.TopExt = pTracks->BTks.Hdr.RelevantZs.TopExt;
			TempLayer.RelevantZs.TopInt = pTracks->BTks.Hdr.RelevantZs.TopInt;
			TempLayer.RelevantZs.BottomInt = pTracks->BTks.Hdr.RelevantZs.BottomInt;
			TempLayer.RelevantZs.BottomExt = pTracks->BTks.Hdr.RelevantZs.BottomExt;
			TempLayer.LocalSideAlign[0].PosAlign.M[0][0] = TempLayer.LocalSideAlign[1].PosAlign.M[0][0] = 
			TempLayer.LocalSideAlign[0].PosAlign.M[1][1] = TempLayer.LocalSideAlign[1].PosAlign.M[1][1] = 1.;
			TempLayer.LocalSideAlign[0].PosAlign.M[0][1] = TempLayer.LocalSideAlign[1].PosAlign.M[0][1] = 
			TempLayer.LocalSideAlign[0].PosAlign.M[1][0] = TempLayer.LocalSideAlign[1].PosAlign.M[1][0] = 0.;
			TempLayer.LocalSideAlign[0].PosAlign.D[0] = TempLayer.LocalSideAlign[0].PosAlign.D[1] = TempLayer.LocalSideAlign[0].PosAlign.D[2] = 
				TempLayer.LocalSideAlign[1].PosAlign.D[0] = TempLayer.LocalSideAlign[1].PosAlign.D[1] = TempLayer.LocalSideAlign[1].PosAlign.D[2] = 0.;
			TempLayer.LocalSideAlign[0].SlopeAlign.DShrink[0] = TempLayer.LocalSideAlign[0].SlopeAlign.DShrink[1] =
				TempLayer.LocalSideAlign[1].SlopeAlign.DShrink[0] = TempLayer.LocalSideAlign[1].SlopeAlign.DShrink[1] = 0.;
			TempLayer.LocalSideAlign[0].SlopeAlign.DSlope[0] = TempLayer.LocalSideAlign[0].SlopeAlign.DSlope[1] =
				TempLayer.LocalSideAlign[1].SlopeAlign.DSlope[0] = TempLayer.LocalSideAlign[1].SlopeAlign.DSlope[1] = 0.;
			TempLayer.RTCount[0] = pTracks->BTks.Hdr.TCount[0];
			TempLayer.RTCount[1] = pTracks->BTks.Hdr.TCount[1];
			TempLayer.pRawTracks[0] = (TS_RawTrack *)malloc(sizeof(TS_RawTrack) * TempLayer.RTCount[0]);
			TempLayer.pRawTracks[1] = (TS_RawTrack *)malloc(sizeof(TS_RawTrack) * TempLayer.RTCount[1]);
			int s, j;
			for (s = 0; s < 2; s++)
				for (j = 0; j < TempLayer.RTCount[s]; j++)
				{
					TempLayer.pRawTracks[s][j].Field = pTracks->BTks.pTracks[s][j].Field;
					TempLayer.pRawTracks[s][j].PointsN = pTracks->BTks.pTracks[s][j].PointsN;
					TempLayer.pRawTracks[s][j].Intercept = pTracks->BTks.pTracks[s][j].Intercept;
					TempLayer.pRawTracks[s][j].Slope = pTracks->BTks.pTracks[s][j].Slope;
					TempLayer.pRawTracks[s][j].Sigma = pTracks->BTks.pTracks[s][j].Sigma;
					TempLayer.pRawTracks[s][j].FirstZ = pTracks->BTks.pTracks[s][j].FirstZ;
					TempLayer.pRawTracks[s][j].LastZ = pTracks->BTks.pTracks[s][j].LastZ;
					};
			bool Success = RM.AddLayer(&TempLayer, true, true);
			CoTaskMemFree(pTracks);
			if (TempLayer.pRawTracks[0]) free(TempLayer.pRawTracks[0]);
			if (TempLayer.pRawTracks[1]) free(TempLayer.pRawTracks[1]);
			if (!Success) throw 5;
			};
		RM.EndAdding();
		}
	catch (...)
	{
		return false;
		};
	return true;
}

void CInteractiveReconstruction::OnShowRaw() 
{
	// TODO: Add your control notification handler code here
	EDM.ShowMode = SHOW_RAW;
	if (!iED) return;
	iED->Clear();
	Vector MinBounds, MaxBounds;
	int s, i, j;	
	TS_LayerInfo *pTracks;
	IO_TS_Reconstruction *pRec = RM.AccessReconstruction();
	if (!pRec) 
	{
		iED->Render();
		return;
		};
	for (i = 0; (i < pRec->Hdr.SheetsCount) && ((pRec->pLayers[i].RTCount[0] + pRec->pLayers[i].RTCount[1]) == 0); i++);	
	if (i < pRec->Hdr.SheetsCount)
	{
		pTracks = &pRec->pLayers[i];
		MaxBounds = MinBounds = (pTracks->RTCount[0]) ? pTracks->pRawTracks[0][0].Intercept : pTracks->pRawTracks[1][0].Intercept;
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			for (s = 0; s < 2; s++)
				for (j = 0; j < pTracks->RTCount[s]; j++)
				{
					Vector V;
					V = pTracks->pRawTracks[s][j].Intercept + pTracks->pRawTracks[s][j].Slope * (pTracks->pRawTracks[s][j].FirstZ - pTracks->pRawTracks[s][j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					V = pTracks->pRawTracks[s][j].Intercept + pTracks->pRawTracks[s][j].Slope * (pTracks->pRawTracks[s][j].LastZ - pTracks->pRawTracks[s][j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					};
			};
		EDM.InterestingPoint = 0.5f * (MaxBounds + MinBounds);
		Vector D = MaxBounds - MinBounds;
		EDM.Distance = 3.f * !D + 1.f;
		Vector CamPos = EDM.InterestingPoint - EDM.Distance * EDM.Dir;
		MaxBounds = MaxBounds + Vector(10.f, 10.f, 10.f);
		MinBounds = MinBounds - Vector(10.f, 10.f, 10.f);
		iED->SetBounds(MinBounds.X, MaxBounds.X, MinBounds.Y, MaxBounds.Y, MinBounds.Z, MaxBounds.Z);
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			iED->AddPlane(pTracks->RelevantZs.BottomInt);
			iED->AddPlane(pTracks->RelevantZs.TopInt);
			for (s = 0; s < 2; s++)
				for (j = 0; j < pTracks->RTCount[s]; j++)
				{
					Vector V1, V2;
					V1 = pTracks->pRawTracks[s][j].Intercept + pTracks->pRawTracks[s][j].Slope * (pTracks->pRawTracks[s][j].FirstZ - pTracks->pRawTracks[s][j].Intercept.Z);
					V2 = pTracks->pRawTracks[s][j].Intercept + pTracks->pRawTracks[s][j].Slope * (pTracks->pRawTracks[s][j].LastZ - pTracks->pRawTracks[s][j].Intercept.Z);
					iED->AddSegmentAutoColor(V1.X, V1.Y, V1.Z, V2.X, V2.Y, V2.Z);
					};
			};
		iED->SetCamera(CamPos.X, CamPos.Y, CamPos.Z, EDM.Dir.X, EDM.Dir.Y, EDM.Dir.Z, EDM.Norm.X, EDM.Norm.Y, EDM.Norm.Z);
		};
	iED->Render();
}

void CInteractiveReconstruction::OnShowSegments() 
{
	// TODO: Add your control notification handler code here
	EDM.ShowMode = SHOW_SEGMENTS;	
	if (!iED) return;
	iED->Clear();
	Vector MinBounds, MaxBounds;
	int s, i, j;	
	TS_LayerInfo *pTracks;
	TS_Segment *pSegs;
	IO_TS_Reconstruction *pRec = RM.AccessReconstruction();
	if (!pRec) 
	{
		iED->Render();
		return;
		};
	int Count;
	for (i = 0; (i < pRec->Hdr.SheetsCount) && ((pRec->pLayers[i].RTCount[0] + pRec->pLayers[i].RTCount[1]) == 0); i++);
	if (i < pRec->Hdr.SheetsCount)
	{
		pTracks = &pRec->pLayers[i];
		if (pTracks->RTCount[0])
		{
			if (!(Count = pTracks->SCount[0]))
			{			
				iED->Render();
				return;
				};
			pSegs = pTracks->pSegments[0]; 
			MaxBounds = MinBounds = pSegs[0].Intercept;
			}
		else
		{
			if (!(Count = pTracks->SCount[1]))
			{
				iED->Render();
				return;
				};
			pSegs = pTracks->pSegments[1]; 
			MaxBounds = MinBounds = pSegs[1].Intercept;
			};
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			for (s = 0; s < 2; s++)
			{
				pSegs = pTracks->pSegments[s];
				Count = pTracks->SCount[s];
				for (j = 0; j < Count; j++)
				{
					Vector V;
					V = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].FirstZ - pSegs[j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					V = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].LastZ - pSegs[j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					};
				};
			};
		EDM.InterestingPoint = 0.5f * (MaxBounds + MinBounds);
		Vector D = MaxBounds - MinBounds;
		EDM.Distance = 3.f * !D + 1.f;
		Vector CamPos = EDM.InterestingPoint - EDM.Distance * EDM.Dir;
		MaxBounds = MaxBounds + Vector(10.f, 10.f, 10.f);
		MinBounds = MinBounds - Vector(10.f, 10.f, 10.f);
		iED->SetBounds(MinBounds.X, MaxBounds.X, MinBounds.Y, MaxBounds.Y, MinBounds.Z, MaxBounds.Z);
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			iED->AddPlane(pTracks->RelevantZs.BottomInt);
			iED->AddPlane(pTracks->RelevantZs.TopInt);
			for (s = 0; s < 2; s++)
			{
				pSegs = pTracks->pSegments[s];
				Count = pTracks->SCount[s];
				for (j = 0; j < Count; j++)
				{
					Vector V1, V2;
					V1 = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].FirstZ - pSegs[j].Intercept.Z);
					V2 = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].LastZ - pSegs[j].Intercept.Z);
					iED->AddSegmentAutoColor(V1.X, V1.Y, V1.Z, V2.X, V2.Y, V2.Z);
					};
				};
			};
		iED->SetCamera(CamPos.X, CamPos.Y, CamPos.Z, EDM.Dir.X, EDM.Dir.Y, EDM.Dir.Z, EDM.Norm.X, EDM.Norm.Y, EDM.Norm.Z);
		};
	iED->Render();
}

void CInteractiveReconstruction::OnShowTracks() 
{
	// TODO: Add your control notification handler code here
	EDM.ShowMode = SHOW_TRACKS;
	if (!iED) return;
	iED->Clear();
	Vector MinBounds, MaxBounds;
	int s, i, j;
	TS_LayerInfo *pTracks;
	TS_Segment *pSegs;
	TS_Track *pTSTracks;
	TS_Vertex *pVertices;
	IO_TS_Reconstruction *pRec = RM.AccessReconstruction();
	if (!pRec) 
	{
		iED->Render();
		return;
		};
	int Count;
	for (i = 0; (i < pRec->Hdr.SheetsCount) && ((pRec->pLayers[i].RTCount[0] + pRec->pLayers[i].RTCount[1]) == 0); i++);
	if (i < pRec->Hdr.SheetsCount)
	{
		pTracks = &pRec->pLayers[i];
		if (pTracks->RTCount[0])
		{
			if (!(Count = pTracks->SCount[0]))
			{				
				iED->Render();
				return;
				};
			pSegs = pTracks->pSegments[0]; 
			MaxBounds = MinBounds = pSegs[0].Intercept;
			}
		else
		{
			if (!(Count = pTracks->SCount[1]))
			{				
				iED->Render();
				return;
				};
			pSegs = pTracks->pSegments[1]; 
			MaxBounds = MinBounds = pSegs[1].Intercept;
			};
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			for (s = 0; s < 2; s++)
			{
				pSegs = pTracks->pSegments[s];
				Count = pTracks->SCount[s];
				for (j = 0; j < Count; j++)
				{
					Vector V;
					V = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].FirstZ - pSegs[j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					V = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].LastZ - pSegs[j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					};
				};
			};
		EDM.InterestingPoint = 0.5f * (MaxBounds + MinBounds);
		Vector D = MaxBounds - MinBounds;
		EDM.Distance = 3.f * !D + 1.f;
		Vector CamPos = EDM.InterestingPoint - EDM.Distance * EDM.Dir;
		MaxBounds = MaxBounds + Vector(10.f, 10.f, 10.f);
		MinBounds = MinBounds - Vector(10.f, 10.f, 10.f);
		iED->SetBounds(MinBounds.X, MaxBounds.X, MinBounds.Y, MaxBounds.Y, MinBounds.Z, MaxBounds.Z);
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			iED->AddPlane(pTracks->RelevantZs.BottomInt);
			iED->AddPlane(pTracks->RelevantZs.TopInt);
			};

		pTSTracks = pRec->pTracks;
		Count = pRec->Hdr.TSTracksCount;
		for (i = 0; i < Count; i++)
		{
			iED->StartNewSegment();
			pSegs = pTSTracks[i].pBottomEnd;
			do
			{
				Vector V1, V2/*, I, S*/;
/*				int j, s;
				RM.SegPtrToIndices(pSegs, &j, &s);
				TS_LayerInfo::t_LocalSideAlign &ra = pRec->pLayers[j].LocalSideAlign[2 + s];
				I.X = (1. + ra.PosAlign.M[0][0]) * (pSegs->Intercept.X - pRec->Hdr.RefCenter.X) + ra.PosAlign.M[0][1] * (pSegs->Intercept.Y - pRec->Hdr.RefCenter.Y) + ra.PosAlign.D[0] + pRec->Hdr.RefCenter.X;
				I.Y = ra.PosAlign.M[1][0] * (pSegs->Intercept.X - pRec->Hdr.RefCenter.X) + (1. + ra.PosAlign.M[1][1]) * (pSegs->Intercept.Y - pRec->Hdr.RefCenter.Y) + ra.PosAlign.D[1] + pRec->Hdr.RefCenter.Y;
				I.Z = pSegs->Intercept.Z - ra.PosAlign.D[2];
				S.X = (1. + ra.SlopeAlign.DShrink[0]) * pSegs->Slope.X + ra.SlopeAlign.DSlope[0];
				S.Y = (1. + ra.SlopeAlign.DShrink[1]) * pSegs->Slope.Y + ra.SlopeAlign.DSlope[1];
				S.Z = 1.;
				V1 = I + S * (pSegs->LastZ - pSegs->Intercept.Z);
				V2 = I + S * (pSegs->FirstZ - pSegs->Intercept.Z);
*/
				V1 = pSegs->Intercept + pSegs->Slope * (pSegs->LastZ - pSegs->Intercept.Z);
				V2 = pSegs->Intercept + pSegs->Slope * (pSegs->FirstZ - pSegs->Intercept.Z);

				if ((!m_PassingThrough && (pTSTracks[i].Flags & TSTRACK_FLAG_PASSING_THROUGH)) || (m_OnlyTracksFromVertex && !pTSTracks[i].pBottomVertex && !pTSTracks[i].pTopVertex))
				{
					iED->AddVertexToSegment(V1.X, V1.Y, V1.Z, 0.3, 0.3, 0.3);
					iED->AddVertexToSegment(V2.X, V2.Y, V2.Z, 0.3, 0.3, 0.3);	
					}
				else
				{
					iED->AddVertexToSegmentAutoColor(V1.X, V1.Y, V1.Z);
					iED->AddVertexToSegmentAutoColor(V2.X, V2.Y, V2.Z);				
					};
				pSegs = pSegs->pTopLink;
				}
			while (pSegs);
			iED->EndNewSegment();
			};

		pVertices = pRec->pVertices;
		Count = pRec->Hdr.VerticesCount;
		for (i = 0; i < Count; i++)
		{
			iED->AddSegment(pVertices[i].Pos.X - 10., pVertices[i].Pos.Y, pVertices[i].Pos.Z, 1., 1., 1.,
				pVertices[i].Pos.X + 10., pVertices[i].Pos.Y, pVertices[i].Pos.Z, 1., 1., 1.);
			iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y - 10., pVertices[i].Pos.Z, 1., 1., 1.,
				pVertices[i].Pos.X, pVertices[i].Pos.Y + 10., pVertices[i].Pos.Z, 1., 1., 1.);
			iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z - 10., 1., 1., 1.,
				pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z + 10., 1., 1., 1.);
			for (j = 0; j < pVertices[i].Count; j++)
			{
				Vector V = (pVertices[i].pTSTracks[j].IsDownstream) ? 
					(pVertices[i].pTSTracks[j].pTSTrack->Intercept + (pVertices[i].pTSTracks[j].pTSTrack->LastZ - 
					pVertices[i].pTSTracks[j].pTSTrack->Intercept.Z) * pVertices[i].pTSTracks[j].pTSTrack->Slope) :
					(pVertices[i].pTSTracks[j].pTSTrack->Intercept + (pVertices[i].pTSTracks[j].pTSTrack->FirstZ - 
					pVertices[i].pTSTracks[j].pTSTrack->Intercept.Z) * pVertices[i].pTSTracks[j].pTSTrack->Slope);
				iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z, 0.9, 0.9, 0.9,
					V.X, V.Y, V.Z, 0.9, 0.9, 0.9);
				};
			};

		iED->SetCamera(CamPos.X, CamPos.Y, CamPos.Z, EDM.Dir.X, EDM.Dir.Y, EDM.Dir.Z, EDM.Norm.X, EDM.Norm.Y, EDM.Norm.Z);
		};
	iED->Render();
}

void CInteractiveReconstruction::OnShowTrackSegments() 
{
	// TODO: Add your control notification handler code here
	EDM.ShowMode = SHOW_TRACKSEGS;
	if (!iED) return;
	iED->Clear();
	Vector MinBounds, MaxBounds;
	int s, i, j;
	TS_LayerInfo *pTracks;
	TS_Segment *pSegs;
	TS_Track *pTSTracks;
	TS_Vertex *pVertices;
	IO_TS_Reconstruction *pRec = RM.AccessReconstruction();
	if (!pRec) 
	{
		iED->Render();
		return;
		};
	int Count;
	for (i = 0; (i < pRec->Hdr.SheetsCount) && ((pRec->pLayers[i].RTCount[0] + pRec->pLayers[i].RTCount[1]) == 0); i++);
	if (i < pRec->Hdr.SheetsCount)
	{
		pTracks = &pRec->pLayers[i];
		if (pTracks->RTCount[0])
		{
			if (!(Count = pTracks->SCount[0]))
			{				
				iED->Render();
				return;
				};
			pSegs = pTracks->pSegments[0]; 
			MaxBounds = MinBounds = pSegs[0].Intercept;
			}
		else
		{
			if (!(Count = pTracks->SCount[1]))
			{				
				iED->Render();
				return;
				};
			pSegs = pTracks->pSegments[1]; 
			MaxBounds = MinBounds = pSegs[1].Intercept;
			};
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			for (s = 0; s < 2; s++)
			{
				pSegs = pTracks->pSegments[s];
				Count = pTracks->SCount[s];
				for (j = 0; j < Count; j++)
				{
					Vector V;
					V = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].FirstZ - pSegs[j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					V = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].LastZ - pSegs[j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					};
				};
			};
		EDM.InterestingPoint = 0.5f * (MaxBounds + MinBounds);
		Vector D = MaxBounds - MinBounds;
		EDM.Distance = 3.f * !D + 1.f;
		Vector CamPos = EDM.InterestingPoint - EDM.Distance * EDM.Dir;
		MaxBounds = MaxBounds + Vector(10.f, 10.f, 10.f);
		MinBounds = MinBounds - Vector(10.f, 10.f, 10.f);
		iED->SetBounds(MinBounds.X, MaxBounds.X, MinBounds.Y, MaxBounds.Y, MinBounds.Z, MaxBounds.Z);
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			iED->AddPlane(pTracks->RelevantZs.BottomInt);
			iED->AddPlane(pTracks->RelevantZs.TopInt);
			};

		pTSTracks = pRec->pTracks;
		Count = pRec->Hdr.TSTracksCount;
		for (i = 0; i < Count; i++)
		{
			pSegs = pTSTracks[i].pBottomEnd;
			do
			{
				Vector V1, V2/*, I, S*/;
/*				int j, s;
				RM.SegPtrToIndices(pSegs, &j, &s);
				TS_LayerInfo::t_LocalSideAlign &ra = pRec->pLayers[j].LocalSideAlign[2 + s];
				I.X = (1. + ra.PosAlign.M[0][0]) * (pSegs->Intercept.X - pRec->Hdr.RefCenter.X) + ra.PosAlign.M[0][1] * (pSegs->Intercept.Y - pRec->Hdr.RefCenter.Y) + ra.PosAlign.D[0] + pRec->Hdr.RefCenter.X;
				I.Y = ra.PosAlign.M[1][0] * (pSegs->Intercept.X - pRec->Hdr.RefCenter.X) + (1. + ra.PosAlign.M[1][1]) * (pSegs->Intercept.Y - pRec->Hdr.RefCenter.Y) + ra.PosAlign.D[1] + pRec->Hdr.RefCenter.Y;
				I.Z = pSegs->Intercept.Z - ra.PosAlign.D[2];
				S.X = (1. + ra.SlopeAlign.DShrink[0]) * pSegs->Slope.X + ra.SlopeAlign.DSlope[0];
				S.Y = (1. + ra.SlopeAlign.DShrink[1]) * pSegs->Slope.Y + ra.SlopeAlign.DSlope[1];
				S.Z = 1.;
				V1 = I + S * (pSegs->LastZ - pSegs->Intercept.Z);
				V2 = I + S * (pSegs->FirstZ - pSegs->Intercept.Z);
*/
				V1 = pSegs->Intercept + pSegs->Slope * (pSegs->LastZ - pSegs->Intercept.Z);
				V2 = pSegs->Intercept + pSegs->Slope * (pSegs->FirstZ - pSegs->Intercept.Z);

				if ((!m_PassingThrough && (pTSTracks[i].Flags & TSTRACK_FLAG_PASSING_THROUGH)) || (m_OnlyTracksFromVertex && !pTSTracks[i].pBottomVertex && !pTSTracks[i].pTopVertex)) 
					iED->AddSegment(V1.X, V1.Y, V1.Z, 0.3, 0.3, 0.3, V2.X, V2.Y, V2.Z, 0.3, 0.3, 0.3);
				else iED->AddSegmentAutoColor(V1.X, V1.Y, V1.Z, V2.X, V2.Y, V2.Z);
				pSegs = pSegs->pTopLink;
				}
			while (pSegs);
			};

		pVertices = pRec->pVertices;
		Count = pRec->Hdr.VerticesCount;
		for (i = 0; i < Count; i++)
		{
			iED->AddSegment(pVertices[i].Pos.X - 10., pVertices[i].Pos.Y, pVertices[i].Pos.Z, 1., 1., 1.,
				pVertices[i].Pos.X + 10., pVertices[i].Pos.Y, pVertices[i].Pos.Z, 1., 1., 1.);
			iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y - 10., pVertices[i].Pos.Z, 1., 1., 1.,
				pVertices[i].Pos.X, pVertices[i].Pos.Y + 10., pVertices[i].Pos.Z, 1., 1., 1.);
			iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z - 10., 1., 1., 1.,
				pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z + 10., 1., 1., 1.);
			for (j = 0; j < pVertices[i].Count; j++)
			{
				Vector V = (pVertices[i].pTSTracks[j].IsDownstream) ? 
					(pVertices[i].pTSTracks[j].pTSTrack->Intercept + (pVertices[i].pTSTracks[j].pTSTrack->LastZ - 
					pVertices[i].pTSTracks[j].pTSTrack->Intercept.Z) * pVertices[i].pTSTracks[j].pTSTrack->Slope) :
					(pVertices[i].pTSTracks[j].pTSTrack->Intercept + (pVertices[i].pTSTracks[j].pTSTrack->FirstZ - 
					pVertices[i].pTSTracks[j].pTSTrack->Intercept.Z) * pVertices[i].pTSTracks[j].pTSTrack->Slope);
				iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z, 0.9, 0.9, 0.9,
					V.X, V.Y, V.Z, 0.9, 0.9, 0.9);
				};
			};

		iED->SetCamera(CamPos.X, CamPos.Y, CamPos.Z, EDM.Dir.X, EDM.Dir.Y, EDM.Dir.Z, EDM.Norm.X, EDM.Norm.Y, EDM.Norm.Z);
		};
	iED->Render();	
}

void CInteractiveReconstruction::OnReconstruct() 
{
	// TODO: Add your control notification handler code here
	m_Notes.SetWindowText("");
	CString Notes;
	if (pMatchDlg) 
	{
		delete pMatchDlg;
		pMatchDlg = 0;
		};
	HCURSOR HOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
#ifdef DISABLE_EXCEPTION_INTERCEPTION
	if (RM.Reconstruct(this, ProgressMonitor, &Notes) && RM.CheckTopology(this, ProgressMonitor, &Notes))
		MessageBox("Reconstruction Ok!", "Success", MB_ICONINFORMATION | MB_OK);
	else
		MessageBox("Reconstruction failed!", "Warning", MB_ICONINFORMATION | MB_OK);
#else
	try
	{
		if (RM.Reconstruct(this, ProgressMonitor, &Notes) && RM.CheckTopology(this, ProgressMonitor, &Notes))
			MessageBox("Reconstruction Ok!", "Success", MB_ICONINFORMATION | MB_OK);
		else
			MessageBox("Reconstruction failed!", "Warning", MB_ICONINFORMATION | MB_OK);
		}
	catch (...)
	{
		MessageBox("Unknown exception performing reconstruction!", "Error", MB_ICONERROR | MB_OK);
		};
#endif
	SetCursor(HOldCursor);
	Refresh();
	ProgressMonitor(this, "Idle", 0.f);
	m_Notes.SetWindowText(Notes);
}

void CInteractiveReconstruction::OnTopology() 
{
	// TODO: Add your control notification handler code here
	m_Notes.SetWindowText("");
	CString Notes;
	if (pMatchDlg) 
	{
		delete pMatchDlg;
		pMatchDlg = 0;
		};
	HCURSOR HOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
#ifdef DISABLE_EXCEPTION_INTERCEPTION
	if (RM.CheckTopology(this, ProgressMonitor, &Notes))
		MessageBox("Topological structure Ok!", "Success", MB_ICONINFORMATION | MB_OK);
	else
		MessageBox("Topological reconstruction failed!", "Warning", MB_ICONINFORMATION | MB_OK);
#else
	try
	{
		if (RM.CheckTopology(this, ProgressMonitor, &Notes))
			MessageBox("Topological structure Ok!", "Success", MB_ICONINFORMATION | MB_OK);
		else
			MessageBox("Topological reconstruction failed!", "Warning", MB_ICONINFORMATION | MB_OK);
		}
	catch (...)
	{
		MessageBox("Unknown exception performing topological analysis!", "Error", MB_ICONERROR | MB_OK);
		};
#endif
	SetCursor(HOldCursor);
	Refresh();
	ProgressMonitor(this, "Idle", 0.f);	
	m_Notes.SetWindowText(Notes);
}


void CInteractiveReconstruction::OnEditConfig() 
{
	// TODO: Add your control notification handler code here
	TSReconData Temp;
	RM.GetReconstructionData(&Temp);
	CEditConfig MyDlg(this);
	MyDlg.m_InField_D_Pos = Temp.InField_D_Pos; 
	MyDlg.m_InField_D_Slope = Temp.InField_D_Slope;
	MyDlg.m_OffField_D_Pos = Temp.OffField_D_Pos;
	MyDlg.m_OffField_D_Slope = Temp.OffField_D_Slope;
	MyDlg.m_MaxRemeasuresInSegment = Temp.MaxRemeasuresInSegment;
	MyDlg.m_RemeasureHandling = Temp.RemeasureHandling;
	MyDlg.m_LowestPrescanPeak = Temp.LowestPrescanPeak;
	MyDlg.m_InPlate_D_Pos = Temp.InPlate_D_Pos;
	MyDlg.m_InPlate_D_Slope = Temp.InPlate_D_Slope;
	MyDlg.m_InPlate_Gross_D_Pos = Temp.InPlate_Gross_D_Pos;
	MyDlg.m_InPlate_Gross_D_Slope = Temp.InPlate_Gross_D_Slope;
	MyDlg.m_InPlate_Pos_Prescan = Temp.InPlate_Pos_Prescan;
	MyDlg.m_InPlate_MaxIters = Temp.InPlate_MaxIters;
	MyDlg.m_MaxMissingSegments = Temp.MaxMissingSegments;
	MyDlg.m_MinSegments = Temp.MinSegments;
	MyDlg.m_MinSegmentsRecovery = Temp.MinSegmentsRecovery;
	MyDlg.m_OffPlate_D_Pos = Temp.OffPlate_D_Pos;
	MyDlg.m_OffPlate_D_Slope = Temp.OffPlate_D_Slope;
	MyDlg.m_OffPlate_Gross_D_Pos = Temp.OffPlate_Gross_D_Pos;
	MyDlg.m_OffPlate_Gross_D_Slope = Temp.OffPlate_Gross_D_Slope;
	MyDlg.m_OffPlate_Pos_Prescan = Temp.OffPlate_Pos_Prescan;
	MyDlg.m_OffPlate_MaxIters = Temp.OffPlate_MaxIters;
	MyDlg.m_RequireOffPlateLinking = Temp.RequireOffPlateLinking;
	MyDlg.m_FinalAlignment_Enable = Temp.FinalAlignment_Enable;
	MyDlg.m_FinalAlignment_SlopeMeasures = Temp.FinalAlignment_SlopeMeasures;
	MyDlg.m_FinalAlignment_MaxIters = Temp.FinalAlignment_MaxIters;
	MyDlg.m_FinalAlignment_MaxSlopeDiff = Temp.FinalAlignment_MaxSlopeDiff;
	MyDlg.m_FinalAlignment_MinSlopeDiff = Temp.FinalAlignment_MinSlopeDiff;
	MyDlg.m_FinalAlignment_MinEntries = Temp.FinalAlignment_MinEntries;
	MyDlg.m_FinalAlignment_MaxRMS = Temp.FinalAlignment_MaxRMS;
	MyDlg.m_PassingThrough_Radius = Temp.PassingThrough_Radius;
	MyDlg.m_PassingThrough_Angle = Temp.PassingThrough_Angle;
	MyDlg.m_PassingThrough_OutLength = Temp.PassingThrough_OutLength;
	MyDlg.m_Vertex_XYTol = Temp.Vertex_XYTol;
	MyDlg.m_Vertex_XYTolIncrease = Temp.Vertex_XYTolIncrease;
	MyDlg.m_Vertex_LowestZ = Temp.Vertex_LowestZ;
	MyDlg.m_Vertex_Overlength = Temp.Vertex_Overlength;
	MyDlg.m_Vertex_MergeXYTol = Temp.Vertex_MergeXYTol;
	MyDlg.m_Vertex_MergeZTol = Temp.Vertex_MergeZTol;
	MyDlg.m_Vertex_ZExtrapolation = Temp.Vertex_ZExtrapolation;
	MyDlg.m_Vertex_Recovery_ZExtrapolation = Temp.Vertex_Recovery_ZExtrapolation;
	if (MyDlg.DoModal() == IDOK)
	{
		Temp.InField_D_Pos = MyDlg.m_InField_D_Pos; 
		Temp.InField_D_Slope = MyDlg.m_InField_D_Slope;
		Temp.OffField_D_Pos = MyDlg.m_OffField_D_Pos;
		Temp.OffField_D_Slope = MyDlg.m_OffField_D_Slope;
		Temp.MaxRemeasuresInSegment = MyDlg.m_MaxRemeasuresInSegment;
		Temp.RemeasureHandling = MyDlg.m_RemeasureHandling;
		Temp.LowestPrescanPeak = MyDlg.m_LowestPrescanPeak;
		Temp.InPlate_D_Pos = MyDlg.m_InPlate_D_Pos;
		Temp.InPlate_D_Slope = MyDlg.m_InPlate_D_Slope;
		Temp.InPlate_Gross_D_Pos = MyDlg.m_InPlate_Gross_D_Pos;
		Temp.InPlate_Gross_D_Slope = MyDlg.m_InPlate_Gross_D_Slope;
		Temp.InPlate_Pos_Prescan = MyDlg.m_InPlate_Pos_Prescan;
		Temp.InPlate_MaxIters = MyDlg.m_InPlate_MaxIters;
		Temp.MaxMissingSegments = MyDlg.m_MaxMissingSegments;
		Temp.MinSegments = MyDlg.m_MinSegments;
		Temp.MinSegmentsRecovery = MyDlg.m_MinSegmentsRecovery;
		Temp.OffPlate_D_Pos = MyDlg.m_OffPlate_D_Pos;
		Temp.OffPlate_D_Slope = MyDlg.m_OffPlate_D_Slope;
		Temp.OffPlate_Gross_D_Pos = MyDlg.m_OffPlate_Gross_D_Pos;
		Temp.OffPlate_Gross_D_Slope = MyDlg.m_OffPlate_Gross_D_Slope;
		Temp.OffPlate_Pos_Prescan = MyDlg.m_OffPlate_Pos_Prescan;
		Temp.OffPlate_MaxIters = MyDlg.m_OffPlate_MaxIters;
		Temp.RequireOffPlateLinking = MyDlg.m_RequireOffPlateLinking;
		Temp.FinalAlignment_Enable = MyDlg.m_FinalAlignment_Enable;
		Temp.FinalAlignment_SlopeMeasures = MyDlg.m_FinalAlignment_SlopeMeasures;
		Temp.FinalAlignment_MaxIters = MyDlg.m_FinalAlignment_MaxIters;
		Temp.FinalAlignment_MaxSlopeDiff = MyDlg.m_FinalAlignment_MaxSlopeDiff;
		Temp.FinalAlignment_MinSlopeDiff = MyDlg.m_FinalAlignment_MinSlopeDiff;
		Temp.FinalAlignment_MinEntries = MyDlg.m_FinalAlignment_MinEntries;
		Temp.FinalAlignment_MaxRMS = MyDlg.m_FinalAlignment_MaxRMS;
		Temp.PassingThrough_Radius = MyDlg.m_PassingThrough_Radius;
		Temp.PassingThrough_Angle = MyDlg.m_PassingThrough_Angle;
		Temp.PassingThrough_OutLength = MyDlg.m_PassingThrough_OutLength;
		Temp.Vertex_XYTol = MyDlg.m_Vertex_XYTol;
		Temp.Vertex_XYTolIncrease = MyDlg.m_Vertex_XYTolIncrease;
		Temp.Vertex_LowestZ = MyDlg.m_Vertex_LowestZ;
		Temp.Vertex_Overlength = MyDlg.m_Vertex_Overlength;
		Temp.Vertex_MergeXYTol = MyDlg.m_Vertex_MergeXYTol;
		Temp.Vertex_MergeZTol = MyDlg.m_Vertex_MergeZTol;
		Temp.Vertex_ZExtrapolation = MyDlg.m_Vertex_ZExtrapolation;
		Temp.Vertex_Recovery_ZExtrapolation = MyDlg.m_Vertex_Recovery_ZExtrapolation;
		RM.SetReconstructionData(&Temp);
		};
}

void CInteractiveReconstruction::ProgressMonitor(void *pContext, char *Text, float Percent)
{
	if (!pContext) return;
	CInteractiveReconstruction *pOwner = (CInteractiveReconstruction *)pContext;
	CString Temp;
	Temp.Format("Action: <%s>", Text);
	pOwner->m_Action.SetWindowText(Temp);
	pOwner->m_ActionProgress.SetPos((int)(Percent * 100.f));
	};

void CInteractiveReconstruction::OnLoadReconstruction() 
{
	// TODO: Add your control notification handler code here	
	static CString m_LoadFile = "";
	CFileDialog MyDlg(TRUE, ".TSR", m_LoadFile, OFN_FILEMUSTEXIST | OFN_EXPLORER, "TotalScan Reconstruction Files|*.TSR|All Files|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_Notes.SetWindowText("");
		if (pMatchDlg) 
		{
			delete pMatchDlg;
			pMatchDlg = 0;
			};
		m_LoadFile = MyDlg.GetPathName();
		IO_TS_Reconstruction *pRec = 0;
		UINT ExtErrorInfo;
		HCURSOR HOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
		if (iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)&pRec, &ExtErrorInfo, (UCHAR *)m_LoadFile.GetBuffer(1)) != S_OK)
		{
			SetCursor(HOldCursor);
			m_LoadFile.ReleaseBuffer();
			CString Temp;
			Temp.Format("Error reading file!\nError code: %08X", ExtErrorInfo);
			MessageBox(Temp, "Error", MB_ICONERROR | MB_OK);
			}
		else 
		{
			SetCursor(HOldCursor);
			m_LoadFile.ReleaseBuffer();
			if (RM.LoadReconstruction(pRec)) 
			{
				MessageBox("File loaded!", "Success", MB_ICONINFORMATION | MB_OK);
				m_Id.SetWindowText(m_LoadFile);
				}
			else 
			{
				MessageBox("Cannot restore reconstruction!", "Error", MB_ICONINFORMATION | MB_OK);
				m_Id.SetWindowText("");
				};
			};
		if (pRec) CoTaskMemFree(pRec);
		};	
	Refresh();
}

void CInteractiveReconstruction::OnSave() 
{
	// TODO: Add your control notification handler code here
	static CString m_SaveFile = "";
	CFileDialog MyDlg(FALSE, ".TSR", m_SaveFile, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_EXPLORER, "TotalScan Reconstruction Files|*.TSR|All Files|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_SaveFile = MyDlg.GetPathName();
		IO_TS_Reconstruction *pRec = RM.AccessReconstruction();
		if (!pRec) MessageBox("Null reconstruction!", "File Error", MB_ICONERROR | MB_OK);
		else
		{
			UINT ExtErrorInfo;
			HCURSOR HOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
			if (iIO->Write((HSySalHANDLE)m_hWnd, (BYTE *)pRec, &ExtErrorInfo, (UCHAR *)m_SaveFile.GetBuffer(1)) != S_OK)
			{
				SetCursor(HOldCursor);
				m_SaveFile.ReleaseBuffer();
				CString Temp;
				Temp.Format("Error writing file!\nError code: %08X", ExtErrorInfo);
				MessageBox(Temp, "Error", MB_ICONERROR | MB_OK);
				}
			else 
			{
				SetCursor(HOldCursor);
				m_SaveFile.ReleaseBuffer();
				MessageBox("File saved!", "Success", MB_ICONINFORMATION | MB_OK);
				};
			};
		};
}

void CInteractiveReconstruction::OnFromVertex() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Refresh();
}

void CInteractiveReconstruction::OnPassingThrough() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Refresh();	
}

void CInteractiveReconstruction::Refresh()
{
	switch (EDM.ShowMode)
	{
		case SHOW_RAW:			OnShowRaw();
								break;

		case SHOW_SEGMENTS:		OnShowSegments();
								break;

		case SHOW_TRACKSEGS:	OnShowTrackSegments();
								break;

		case SHOW_TRACKS:		OnShowTracks();
								break;		
		};
}

void CInteractiveReconstruction::OnMatchPredictions() 
{
	// TODO: Add your control notification handler code here
	if (iPr)
	{
		IO_DBPred_Tracks *pTracks = 0;
		IO_TS_Reconstruction *pTSRec = RM.AccessReconstruction();
		if (!pTSRec) return;
		char temp[256];
		sprintf(temp, "TPID %d %d %d %d", pTSRec->Hdr.ID.Part[0], pTSRec->Hdr.ID.Part[1], pTSRec->Hdr.ID.Part[2], pTSRec->Hdr.ID.Part[3]);
		UINT Err;
		HCURSOR HOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
		if (iPr->Read((HSySalHANDLE)m_hWnd, (BYTE *)(&pTracks), &Err, (UCHAR *)temp) != S_OK)
		{
			SetCursor(HOldCursor);
			sprintf(temp, "Can't find information for prediction %d/%d/%d/%d.\r\nError code: %08X", pTSRec->Hdr.ID.Part[0], pTSRec->Hdr.ID.Part[1], pTSRec->Hdr.ID.Part[2], pTSRec->Hdr.ID.Part[3], Err);
			MessageBox(temp, "Error", MB_ICONERROR | MB_OK);
			if (pTracks) CoTaskMemFree(pTracks);
			return;
			};
		if (pTracks) 
		{
			if (pMatchDlg) 
			{
				delete pMatchDlg;
				pMatchDlg = 0;
				};
			pMatchDlg = new CMatchPredictions(ShowMatchCallBack, this, pTSRec, pTracks, this);
			pMatchDlg->Create(IDD_MATCH_PREDICTION, this);
			CoTaskMemFree(pTracks);
			};
		SetCursor(HOldCursor);
		};
}

void CInteractiveReconstruction::ShowMatchCallBack(void *pContext, int *pMatchColors)
{
	CInteractiveReconstruction *This = (CInteractiveReconstruction *)pContext;
	if (This->EDM.ShowMode == SHOW_TRACKSEGS) 
		This->OnShowMatchTrackSegments(pMatchColors);
	else if (This->EDM.ShowMode == SHOW_TRACKS) 
		This->OnShowMatchTracks(pMatchColors);
	};

void CInteractiveReconstruction::OnShowMatchTracks(int *pMatchColors)
{
	// TODO: Add your control notification handler code here
	EDM.ShowMode = SHOW_TRACKS;
	if (!iED) return;
	iED->Clear();
	Vector MinBounds, MaxBounds;
	int s, i, j;
	TS_LayerInfo *pTracks;
	TS_Segment *pSegs;
	TS_Track *pTSTracks;
	TS_Vertex *pVertices;
	IO_TS_Reconstruction *pRec = RM.AccessReconstruction();
	if (!pRec) 
	{
		iED->Render();
		return;
		};
	int Count;
	for (i = 0; (i < pRec->Hdr.SheetsCount) && ((pRec->pLayers[i].RTCount[0] + pRec->pLayers[i].RTCount[1]) == 0); i++);
	if (i < pRec->Hdr.SheetsCount)
	{
		pTracks = &pRec->pLayers[i];
		if (pTracks->RTCount[0])
		{
			if (!(Count = pTracks->SCount[0]))
			{				
				iED->Render();
				return;
				};
			pSegs = pTracks->pSegments[0]; 
			MaxBounds = MinBounds = pSegs[0].Intercept;
			}
		else
		{
			if (!(Count = pTracks->SCount[1]))
			{				
				iED->Render();
				return;
				};
			pSegs = pTracks->pSegments[1]; 
			MaxBounds = MinBounds = pSegs[1].Intercept;
			};
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			for (s = 0; s < 2; s++)
			{
				pSegs = pTracks->pSegments[s];
				Count = pTracks->SCount[s];
				for (j = 0; j < Count; j++)
				{
					Vector V;
					V = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].FirstZ - pSegs[j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					V = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].LastZ - pSegs[j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					};
				};
			};
		EDM.InterestingPoint = 0.5f * (MaxBounds + MinBounds);
		Vector D = MaxBounds - MinBounds;
		EDM.Distance = 3.f * !D + 1.f;
		Vector CamPos = EDM.InterestingPoint - EDM.Distance * EDM.Dir;
		MaxBounds = MaxBounds + Vector(10.f, 10.f, 10.f);
		MinBounds = MinBounds - Vector(10.f, 10.f, 10.f);
		iED->SetBounds(MinBounds.X, MaxBounds.X, MinBounds.Y, MaxBounds.Y, MinBounds.Z, MaxBounds.Z);
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			iED->AddPlane(pTracks->RelevantZs.BottomInt);
			iED->AddPlane(pTracks->RelevantZs.TopInt);
			};

		pTSTracks = pRec->pTracks;
		Count = pRec->Hdr.TSTracksCount;
		for (i = 0; i < Count; i++)
		{
			if ((pTSTracks[i].Flags & TSTRACK_FLAG_PASSING_THROUGH) || (m_OnlyTracksFromVertex && !pTSTracks[i].pBottomVertex && !pTSTracks[i].pTopVertex)) continue;
			iED->StartNewSegment();
			pSegs = pTSTracks[i].pBottomEnd;
			ColorVector C;
			if (pMatchColors[i] < 0) C.R = C.G = C.B = 0.75f;
			else C = MatchColorTable[pMatchColors[i]];
			do
			{
				Vector V1, V2;
				V1 = pSegs->Intercept + pSegs->Slope * (pSegs->LastZ - pSegs->Intercept.Z);
				V2 = pSegs->Intercept + pSegs->Slope * (pSegs->FirstZ - pSegs->Intercept.Z);
				float L1 = 0.25f * (V1.Z - MinBounds.Z) / (MaxBounds.Z - MinBounds.Z) + 0.75f;
				float L2 = 0.25f * (V2.Z - MinBounds.Z) / (MaxBounds.Z - MinBounds.Z) + 0.75f;
				iED->AddVertexToSegment(V1.X, V1.Y, V1.Z, C.R * L1, C.G * L1, C.B * L1);
				iED->AddVertexToSegment(V2.X, V2.Y, V2.Z, C.R * L2, C.G * L2, C.B * L2);				
				pSegs = pSegs->pTopLink;
				}
			while (pSegs);
			iED->EndNewSegment();
			};

		pVertices = pRec->pVertices;
		Count = pRec->Hdr.VerticesCount;
		for (i = 0; i < Count; i++)
		{
			iED->AddSegment(pVertices[i].Pos.X - 10., pVertices[i].Pos.Y, pVertices[i].Pos.Z, 1., 1., 1.,
				pVertices[i].Pos.X + 10., pVertices[i].Pos.Y, pVertices[i].Pos.Z, 1., 1., 1.);
			iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y - 10., pVertices[i].Pos.Z, 1., 1., 1.,
				pVertices[i].Pos.X, pVertices[i].Pos.Y + 10., pVertices[i].Pos.Z, 1., 1., 1.);
			iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z - 10., 1., 1., 1.,
				pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z + 10., 1., 1., 1.);
			for (j = 0; j < pVertices[i].Count; j++)
			{
				Vector V = (pVertices[i].pTSTracks[j].IsDownstream) ? 
					(pVertices[i].pTSTracks[j].pTSTrack->pBottomEnd->Intercept + (pVertices[i].pTSTracks[j].pTSTrack->pBottomEnd->LastZ - 
					pVertices[i].pTSTracks[j].pTSTrack->pBottomEnd->Intercept.Z) * pVertices[i].pTSTracks[j].pTSTrack->pBottomEnd->Slope) :
					(pVertices[i].pTSTracks[j].pTSTrack->pTopEnd->Intercept + (pVertices[i].pTSTracks[j].pTSTrack->pTopEnd->FirstZ - 
					pVertices[i].pTSTracks[j].pTSTrack->pTopEnd->Intercept.Z) * pVertices[i].pTSTracks[j].pTSTrack->pTopEnd->Slope);
				iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z, 0.9, 0.9, 0.9,
					V.X, V.Y, V.Z, 0.9, 0.9, 0.9);
				};
			};

		iED->SetCamera(CamPos.X, CamPos.Y, CamPos.Z, EDM.Dir.X, EDM.Dir.Y, EDM.Dir.Z, EDM.Norm.X, EDM.Norm.Y, EDM.Norm.Z);
		};
	iED->Render();
}

void CInteractiveReconstruction::OnShowMatchTrackSegments(int *pMatchColors)
{
	// TODO: Add your control notification handler code here
	EDM.ShowMode = SHOW_TRACKSEGS;
	if (!iED) return;
	iED->Clear();
	Vector MinBounds, MaxBounds;
	int s, i, j;
	TS_LayerInfo *pTracks;
	TS_Segment *pSegs;
	TS_Track *pTSTracks;
	TS_Vertex *pVertices;
	IO_TS_Reconstruction *pRec = RM.AccessReconstruction();
	if (!pRec) 
	{
		iED->Render();
		return;
		};
	int Count;
	for (i = 0; (i < pRec->Hdr.SheetsCount) && ((pRec->pLayers[i].RTCount[0] + pRec->pLayers[i].RTCount[1]) == 0); i++);
	if (i < pRec->Hdr.SheetsCount)
	{
		pTracks = &pRec->pLayers[i];
		if (pTracks->RTCount[0])
		{
			if (!(Count = pTracks->SCount[0]))
			{				
				iED->Render();
				return;
				};
			pSegs = pTracks->pSegments[0]; 
			MaxBounds = MinBounds = pSegs[0].Intercept;
			}
		else
		{
			if (!(Count = pTracks->SCount[1]))
			{				
				iED->Render();
				return;
				};
			pSegs = pTracks->pSegments[1]; 
			MaxBounds = MinBounds = pSegs[1].Intercept;
			};
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			for (s = 0; s < 2; s++)
			{
				pSegs = pTracks->pSegments[s];
				Count = pTracks->SCount[s];
				for (j = 0; j < Count; j++)
				{
					Vector V;
					V = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].FirstZ - pSegs[j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					V = pSegs[j].Intercept + pSegs[j].Slope * (pSegs[j].LastZ - pSegs[j].Intercept.Z);
					if (V.X < MinBounds.X) MinBounds.X = V.X;
					else if (V.X > MaxBounds.X) MaxBounds.X = V.X;
					if (V.Y < MinBounds.Y) MinBounds.Y = V.Y;
					else if (V.Y > MaxBounds.Y) MaxBounds.Y = V.Y;
					if (V.Z < MinBounds.Z) MinBounds.Z = V.Z;
					else if (V.Z > MaxBounds.Z) MaxBounds.Z = V.Z;
					};
				};
			};
		EDM.InterestingPoint = 0.5f * (MaxBounds + MinBounds);
		Vector D = MaxBounds - MinBounds;
		EDM.Distance = 3.f * !D + 1.f;
		Vector CamPos = EDM.InterestingPoint - EDM.Distance * EDM.Dir;
		MaxBounds = MaxBounds + Vector(10.f, 10.f, 10.f);
		MinBounds = MinBounds - Vector(10.f, 10.f, 10.f);
		iED->SetBounds(MinBounds.X, MaxBounds.X, MinBounds.Y, MaxBounds.Y, MinBounds.Z, MaxBounds.Z);
		for (i = 0; i < pRec->Hdr.SheetsCount; i++)
		{
			pTracks = &pRec->pLayers[i];
			iED->AddPlane(pTracks->RelevantZs.BottomInt);
			iED->AddPlane(pTracks->RelevantZs.TopInt);
			};

		pTSTracks = pRec->pTracks;
		Count = pRec->Hdr.TSTracksCount;
		for (i = 0; i < Count; i++)
		{
			if ((pTSTracks[i].Flags & TSTRACK_FLAG_PASSING_THROUGH) || (m_OnlyTracksFromVertex && !pTSTracks[i].pBottomVertex && !pTSTracks[i].pTopVertex)) continue;
			pSegs = pTSTracks[i].pBottomEnd;
			ColorVector C;
			if (pMatchColors[i] < 0) C.R = C.G = C.B = 0.75f;
			else C = MatchColorTable[pMatchColors[i]];
			do
			{
				Vector V1, V2;
				V1 = pSegs->Intercept + pSegs->Slope * (pSegs->FirstZ - pSegs->Intercept.Z);
				V2 = pSegs->Intercept + pSegs->Slope * (pSegs->LastZ - pSegs->Intercept.Z);
				float L1 = 0.25f * (V1.Z - MinBounds.Z) / (MaxBounds.Z - MinBounds.Z) + 0.75f;
				float L2 = 0.25f * (V2.Z - MinBounds.Z) / (MaxBounds.Z - MinBounds.Z) + 0.75f;
				iED->AddSegment(V1.X, V1.Y, V1.Z, L1 * C.R, L1 * C.G, L1 * C.B, V2.X, V2.Y, V2.Z, L2 * C.R, L2 * C.G, L2 * C.B);
				pSegs = pSegs->pTopLink;
				}
			while (pSegs);
			};

		pVertices = pRec->pVertices;
		Count = pRec->Hdr.VerticesCount;
		for (i = 0; i < Count; i++)
		{
			iED->AddSegment(pVertices[i].Pos.X - 10., pVertices[i].Pos.Y, pVertices[i].Pos.Z, 1., 1., 1.,
				pVertices[i].Pos.X + 10., pVertices[i].Pos.Y, pVertices[i].Pos.Z, 1., 1., 1.);
			iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y - 10., pVertices[i].Pos.Z, 1., 1., 1.,
				pVertices[i].Pos.X, pVertices[i].Pos.Y + 10., pVertices[i].Pos.Z, 1., 1., 1.);
			iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z - 10., 1., 1., 1.,
				pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z + 10., 1., 1., 1.);
			for (j = 0; j < pVertices[i].Count; j++)
			{
				Vector V = (pVertices[i].pTSTracks[j].IsDownstream) ? 
					(pVertices[i].pTSTracks[j].pTSTrack->pBottomEnd->Intercept + (pVertices[i].pTSTracks[j].pTSTrack->pBottomEnd->LastZ - 
					pVertices[i].pTSTracks[j].pTSTrack->pBottomEnd->Intercept.Z) * pVertices[i].pTSTracks[j].pTSTrack->pBottomEnd->Slope) :
					(pVertices[i].pTSTracks[j].pTSTrack->pTopEnd->Intercept + (pVertices[i].pTSTracks[j].pTSTrack->pTopEnd->FirstZ - 
					pVertices[i].pTSTracks[j].pTSTrack->pTopEnd->Intercept.Z) * pVertices[i].pTSTracks[j].pTSTrack->pTopEnd->Slope);
				iED->AddSegment(pVertices[i].Pos.X, pVertices[i].Pos.Y, pVertices[i].Pos.Z, 0.9, 0.9, 0.9,
					V.X, V.Y, V.Z, 0.9, 0.9, 0.9);
				};
			};

		iED->SetCamera(CamPos.X, CamPos.Y, CamPos.Z, EDM.Dir.X, EDM.Dir.Y, EDM.Dir.Z, EDM.Norm.X, EDM.Norm.Y, EDM.Norm.Z);
		};
	iED->Render();	
}

void CInteractiveReconstruction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar)
	{
		int p = m_Zoom.GetPos();
		switch (nSBCode)
		{
			case SB_LINELEFT:		p -= ZOOM_SLIDER_LINE;
									break;

			case SB_LINERIGHT:		p += ZOOM_SLIDER_LINE;
									break;

			case SB_PAGELEFT:		p -= ZOOM_SLIDER_PAGE;
									break;

			case SB_PAGERIGHT:		p += ZOOM_SLIDER_PAGE;
									break;

			case SB_THUMBPOSITION:	
			case SB_THUMBTRACK:		p = nPos;
									break;

			default:				return;
			};
		if (p < 0) p = 0;
		else if (p > ZOOM_SLIDER_RANGE) p = ZOOM_SLIDER_RANGE;
		m_Zoom.SetPos(p);
		EDM.Zoom = MIN_ZOOM * exp((double)p * log(MAX_ZOOM / MIN_ZOOM) / (double)ZOOM_SLIDER_RANGE);
		if (iED) 
		{
			iED->SetZoom(EDM.Zoom);
			iED->Render();
			};
		return;
		};
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CInteractiveReconstruction::OnSaveConfig() 
{
	// TODO: Add your control notification handler code here
	if (!pCMI->pSaveConfig) return;
	SySalConfig Temp = {0, 0, 0};
	iSelf->GetConfig(&Temp);
	pCMI->pSaveConfig(pCMI->Context, &Temp, Temp.Name);
	if (Temp.pItems)
	{
		CoTaskMemFree(Temp.pItems);
		Temp.pItems = 0;
		};
}
