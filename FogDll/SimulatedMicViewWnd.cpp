// SimulatedMicViewWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SimulatedMicViewWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimulatedMicViewWnd
int Round(float f)
{
	int ret;
	if(f > 0)ret = (f + 0.5f);
	else ret = (f - 0.5f);
	return ret;
}


CSimulatedMicViewWnd::CSimulatedMicViewWnd(SMicData * pMicData,CWnd* pParent)
{
	CString SimulatedViewClass;
	WNDCLASS wndcls;
	wndcls.style = CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW;
	wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hIcon = 0;
	wndcls.hCursor = ::LoadCursor(NULL,IDC_CROSS);//::LoadCursor(AfxGetResourceHandle(), MAKEINTRESOURCE(IDC_ODYSSEY));
	wndcls.hbrBackground = NULL;//m_BackgroundBrush;
	wndcls.lpszMenuName = 0;
	wndcls.lpszClassName = SimulatedViewClass = "Simulated Microscope View";
	AfxRegisterClass(&wndcls);
//	pWndDisplay = new CWndDisplay(&O, IsDisplaySmall, DisplayChooser.Width, DisplayChooser.Height, O.ImageWidth, O.ImageHeight, (DWORD)this, COdyssey::FG_Internal_SetLive, COdyssey::FG_Internal_SetStill, COdyssey::FG_Internal_LoadGrabBuffer, COdyssey::FG_Internal_Clear, COdyssey::FG_Internal_DrawCircles);

	int i;
	mP.maxup = 300.f;
	mP.minup = 250.f;
	mP.maxdw = 50.f;
	mP.mindw = 0.f;
	mP.sx = 0.707f;
	mP.sy = -0.707f;
	mP.pos = CPoint(640,512);
	mP.pixel = 0.304688f;
	mP.Captured = 0;
	mP.PaintEdge = 0;

	bWindowCaptured = false;

	mpBitmapInfo = (BITMAPINFO *)calloc(sizeof(BITMAPINFO) + sizeof(RGBQUAD)*256,1);	
	mpBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	mpBitmapInfo->bmiHeader.biWidth = 1280;
	mpBitmapInfo->bmiHeader.biHeight = -1024;
	mpBitmapInfo->bmiHeader.biPlanes = 1;
	mpBitmapInfo->bmiHeader.biBitCount = 8;
	mpBitmapInfo->bmiHeader.biCompression = BI_RGB;
	mpBitmapInfo->bmiHeader.biSizeImage = 0;
	mpBitmapInfo->bmiHeader.biXPelsPerMeter = 2000;
	mpBitmapInfo->bmiHeader.biYPelsPerMeter = 2000;
	mpBitmapInfo->bmiHeader.biClrUsed = 0;
	mpBitmapInfo->bmiHeader.biClrImportant = 0;
	for (i = 0; i < 256; i++)
	{
		mpBitmapInfo->bmiColors[i].rgbBlue = mpBitmapInfo->bmiColors[i].rgbGreen = mpBitmapInfo->bmiColors[i].rgbRed = i;
		mpBitmapInfo->bmiColors[i].rgbReserved = 0; 
	};
	mpMicData = pMicData;
	m_pImage = (char *)mpMicData->pGlobalBytes;
	mP.pdepths = mpMicData->pDepths;
	mTotalFrames = mpMicData->LevelsUp + mpMicData->LevelsDw;
	mActualFrame = 1;

	SDisplayChooser DisplayChooser;
	DisplayChooser.Number = 0;
	DisplayChooser.ChosenNumber = -1;
	DisplayChooser.Width = DisplayChooser.Height = 0;
	DisplayChooser.Left = DisplayChooser.Top = 0;
#if(WINVER >= 0x0501)
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&DisplayChooser);
#else
	DisplayChooser.Width = 1024;
	DisplayChooser.Height = 768;
	DisplayChooser.ChosenNumber = 1;
#endif
	mDiagonal.x = DisplayChooser.Width;
	mDiagonal.y = DisplayChooser.Height;
	mCorner.x = (1280 - mDiagonal.x) >> 1;
	mCorner.y = (1024 - mDiagonal.y) >> 1;
	mpParent = pParent;

	CreateEx(WS_EX_TOOLWINDOW | WS_EX_CONTROLPARENT, SimulatedViewClass, "Simulated Microscope View", 
		WS_VISIBLE | WS_POPUP, DisplayChooser.Left, DisplayChooser.Top, DisplayChooser.Width,
		DisplayChooser.Height, 0, 0, 0);

	SetWindowPos(&wndTopMost,0,0,0,0,SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
	
	MVD.Banner = true;
	MVD.Grains = false;
	MVD.Prediction = false;
	MVD.Tracks = false;
	MVD.CellSize = 2;
	MVD.Delta = 25;
	MVD.Threshold = 15;
	MVD.Differential = true;
	MVD.Frame = 1;
	MVD.Max = 0;
	MVD.Mean = 0;
	MVD.Min = 0;
	MVD.SeeMipDw = 0;
	MVD.SeeMipUp = 0;
	MVD.SimulatedView = true;
	MVD.Sx = mP.sx;
	MVD.Sy = mP.sy;
	MVD.TotalFrames = 0;
	MVD.GrainsUp = 0;
	MVD.GrainsDw = 0;
	MVD.LocalGrains = 0;
	MVD.x = MVD.y = MVD.z = 0.f;
}


void CSimulatedMicViewWnd::UpdateMicView()
{
	mP.pdepths = mpMicData->pDepths;
	mTotalFrames = mpMicData->LevelsDw + mpMicData->LevelsUp;
	mP.maxup = mpMicData->pSpaceUp->ZetaRange.UpperZ;
	mP.minup = mpMicData->pSpaceUp->ZetaRange.BottomZ;
	mP.maxdw = mpMicData->pSpaceDw->ZetaRange.UpperZ;
	mP.mindw = mpMicData->pSpaceDw->ZetaRange.BottomZ;
	if(mpMicData->LevelsDw == 0)
	{
		mP.maxdw = mP.minup - 200;
		mP.mindw = mP.maxdw - (mP.maxup - mP.minup);
	}
	DrawSimulatedMicView(NULL);
	MVD.Frame = 1;
	MVD.Grains = 0;
	MVD.Max = 0;
	MVD.Mean = 0;
	MVD.Min = 0;
	MVD.GrainsUp = mpMicData->pSpaceUp->NumGrains;
	MVD.GrainsDw = mpMicData->pSpaceDw->NumGrains;
	MVD.SeeMipUp = 0;
	MVD.SeeMipDw = 0;
	MVD.Sx = mP.sx = mpMicData->pOperaData->sx;
	MVD.Sy = mP.sy = mpMicData->pOperaData->sy;
	MVD.x = mpMicData->pOperaData->StageX;
	MVD.y = mpMicData->pOperaData->StageY;
	MVD.z = *(mP.pdepths + 1);
	mpParent->SendMessage(WM_USER_UPDATEFOG,0xFFFF,(LPARAM)&MVD);
}

/*	FOG_UPDATE_PRED = 1,
	FOG_UPDATE_TRACKS = 2,
	FOG_UPDATE_OPTIONS = 4,
	FOG_UPDATE_MICDATAZ = 8,
	FOG_UPDATE_MICDATAXY = 16,
	FOG_UPDATE_GRAINS = 32,
	FOG_UPDATE_FRAME = 64*/

LRESULT CSimulatedMicViewWnd::UpdateDialog(WPARAM wParam,LPARAM lParam)
{

	return NULL;
}

CSimulatedMicViewWnd::~CSimulatedMicViewWnd()
{
	if(mpZoom)
	{
		mpZoom->DestroyWindow();
		delete mpZoom;
	}
	if(mpBitmapInfo)free(mpBitmapInfo);
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(CSimulatedMicViewWnd, CWnd)
	//{{AFX_MSG_MAP(CSimulatedMicViewWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_MESSAGE(WM_USER_UPDATEFOG,UpdateDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSimulatedMicViewWnd message handlers


void CSimulatedMicViewWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	DrawSimulatedMicView((CDC *)&dc);
}


void CSimulatedMicViewWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(true)//nFlags & something);
	{
		mLPoint = point;
		int x = point.x + mCorner.x,y = point.y + mCorner.y;
		if((x - mP.pos.x > -2 && x - mP.pos.x < 2) && (y - mP.pos.y > -2 && y - mP.pos.y < 2))
		{
			mP.Captured = 5;
		}
		else if((x - mP.EdgeUp.x > -2 && x - mP.EdgeUp.x < 2) && (y - mP.EdgeUp.y > -2 && y - mP.EdgeUp.y < 2))
		{
			mP.Captured = 1;
		}
		else if((x - mP.BaseUp.x > -2 && x - mP.BaseUp.x < 2) && (y - mP.BaseUp.y > -2 && y - mP.BaseUp.y < 2))
		{
			mP.Captured = 2;
		}
		else if((x - mP.EdgeDw.x > -2 && x - mP.EdgeDw.x < 2) && (y - mP.EdgeDw.y > -2 && y - mP.EdgeDw.y < 2))
		{
			mP.Captured = 4;
		}
		else if((x - mP.BaseDw.x > -2 && x - mP.BaseDw.x < 2) && (y - mP.BaseDw.y > -2 && y - mP.BaseDw.y < 2))
		{
			mP.Captured = 3;
		}
		else 
			bWindowCaptured = true;
		mActualFrame = mpMicData->Level;
	}
	
//	CDialog::OnLButtonDown(nFlags, point);

}

void CSimulatedMicViewWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	mP.Captured = 0;
	bWindowCaptured = false;
	mLPoint = point;
	mActualFrame = mpMicData->Level;
//	CDialog::OnLButtonUp(nFlags, point);
}

void CSimulatedMicViewWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	int dx,dy,x,y,maxdx,maxdy,ddy;
	//MK_CONTROL	MK_RBUTTON	MK_SHIFT
	if(nFlags & MK_LBUTTON && nFlags & MK_CONTROL)
	{
		maxdx = 1280 - mDiagonal.x;
		maxdy = 1024 - mDiagonal.y;
		dx = point.x - mLPoint.x;
		dy = point.y - mLPoint.y;
		x = mCorner.x - dx;
		if(x > maxdx)
			mCorner.x = maxdx;
		else if(x < 0)
			mCorner.x = 0;
		else
			mCorner.x = x;
		y = mCorner.y - dy;
		if(y > maxdy)
			mCorner.y = maxdy;
		else if(y < 0)
			mCorner.y = 0;
		else
			mCorner.y = y;
		mLPoint = point;
		if(mpMicData->HasImages)
			DrawSimulatedMicView(NULL);
		else
			RedrawBitmap();
	}
	else if(nFlags & MK_LBUTTON)
	{
		dy = (point.y - mLPoint.y);
		ddy = (dy >> 2);
		if(mP.Captured == 5)
		{
			mP.pos = point + mCorner;
		}
		else if(bWindowCaptured)
		{
			SetFrame(mActualFrame + ddy);
			mpParent->SendMessage(WM_USER_UPDATEFOG,FOG_UPDATE_MICDATAZ,(LPARAM)&MVD);
			mpZoom->ShowArea();
		}
		else if(mP.Captured)
		{
			ChangePred(mP.Captured,point + mCorner);
			MVD.Sx = mP.sx;
			MVD.Sy = mP.sy;
			mpParent->SendMessage(WM_USER_UPDATEFOG,FOG_UPDATE_PRED,(LPARAM)&MVD);
		}
		DrawSimulatedMicView(NULL);
	}
	else
	{
		int x = point.x + mCorner.x,y = point.y + mCorner.y;
		bool testUp,testDw,testBUp,testBDw;
		testUp = ((x - mP.EdgeUp.x > -4 && x - mP.EdgeUp.x < 4) && (y - mP.EdgeUp.y > -4 && y - mP.EdgeUp.y < 4));
		testDw = ((x - mP.EdgeDw.x > -4 && x - mP.EdgeDw.x < 4) && (y - mP.EdgeDw.y > -4 && y - mP.EdgeDw.y < 4));
		testBUp = ((x - mP.BaseUp.x > -4 && x - mP.BaseUp.x < 4) && (y - mP.BaseUp.y > -4 && y - mP.BaseUp.y < 4));
		testBDw = ((x - mP.BaseDw.x > -4 && x - mP.BaseDw.x < 4) && (y - mP.BaseDw.y > -4 && y - mP.BaseDw.y < 4));
		if(testUp)
			mP.PaintEdge = 1;
		else if(testBUp)
			mP.PaintEdge = 2;
		else if(testBDw)
			mP.PaintEdge = 3;
		else if(testDw)
			mP.PaintEdge = 4;
		else 
			mP.PaintEdge = 0;
		DrawSimulatedMicView(NULL);
		MVD.x = mpMicData->pOperaData->StageX + mP.pixel*(x - 640);
		MVD.y = mpMicData->pOperaData->StageY + mP.pixel*(512 - y);//???? Chiarire il verso forse anche su x
		mpParent->SendMessage(WM_USER_UPDATEFOG,FOG_UPDATE_MICDATAXY,(LPARAM)&MVD);
	}
	
//	CDialog::OnMouseMove(nFlags, point);
}

void CSimulatedMicViewWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	int con = MK_CONTROL,lbu = MK_LBUTTON, shi = MK_SHIFT;
	if(nFlags & MK_LBUTTON)
		mpZoom->CheckDlgButton(IDC_CHK_ZOOM_MOVE,1);
	else if(nFlags & MK_CONTROL)
	{
		ShowWindow(SW_HIDE);
		MVD.SimulatedView = false;
		mpParent->SendMessage(WM_USER_UPDATEFOG,FOG_UPDATE_OPTIONS,(LPARAM)&MVD);
	}
	else
	{
		mpZoom->m_Point = point + mCorner;
		mpZoom->ShowWindow(SW_SHOW);
		mpZoom->m_Visible = true;
		CPoint ThePoint = point + mCorner;
		mpZoom->SetImagePos(&ThePoint);
		mpZoom->SetValues();
		mpZoom->ShowArea();
		mpZoom->CheckDlgButton(IDC_CHK_ZOOM_MOVE,0);
	}
}

void CSimulatedMicViewWnd::PaintPrediction(CDC *pDC)
{
	if(MVD.Prediction)
	{
		CPoint p1,p2,p3,p4;
		CPen * pOldPen;
		float CenterZ = (mP.minup + mP.maxdw)/2.f;
		float psx = mP.sx/mP.pixel;
		float psy = mP.sy/mP.pixel;
		float DeltaZ;
		float Step;
		DeltaZ = mP.maxup - CenterZ;
		Step = DeltaZ*psx;
		p1.x = Round(DeltaZ*psx) + mP.pos.x;
		p1.y = Round(DeltaZ*psy) + mP.pos.y;
		DeltaZ = mP.minup - CenterZ;
		p2.x = Round(DeltaZ*psx) + mP.pos.x;
		p2.y = Round(DeltaZ*psy) + mP.pos.y;
		DeltaZ = mP.maxdw - CenterZ;
		p3.x = Round(DeltaZ*psx) + mP.pos.x;
		p3.y = Round(DeltaZ*psy) + mP.pos.y;
		DeltaZ = mP.mindw - CenterZ;
		p4.x = Round(DeltaZ*psx) + mP.pos.x;
		p4.y = Round(DeltaZ*psy) + mP.pos.y;

		mP.EdgeUp = p1;
		mP.BaseUp = p2;
		mP.BaseDw = p3;
		mP.EdgeDw = p4;

		CPen RedPen(PS_SOLID,1,(COLORREF)0xff);
		CPen GreenPen(PS_SOLID,1,(COLORREF)0xff00);
		CPen BluePen(PS_SOLID,1,(COLORREF)0xff0000);

		pOldPen = pDC->SelectObject(&RedPen);
		pDC->MoveTo(p1);
		pDC->LineTo(p2);
		pDC->SelectObject(&GreenPen);
		pDC->LineTo(p3);
		pDC->Ellipse(mP.pos.x - 2,mP.pos.y - 2,mP.pos.x + 3,mP.pos.y + 3);
		pDC->SelectObject(&BluePen);
		pDC->MoveTo(p4);
		pDC->LineTo(p3);
		pDC->LineTo(p4);

		if(mP.pdepths)
		{
			if(mpMicData->Level < mpMicData->LevelsUp)
			{
				pDC->SelectObject(&RedPen);
			}
			else
			{
				pDC->SelectObject(&BluePen);
			}
			DeltaZ = *(mP.pdepths + mpMicData->Level) - CenterZ;
			Step = DeltaZ*psx;
			p1.x = Round(DeltaZ*psx) + mP.pos.x;
			p1.y = Round(DeltaZ*psy) + mP.pos.y;
			pDC->Ellipse(p1.x - 1,p1.y - 1,p1.x + 2,p1.y + 2);
		}
		if(mP.PaintEdge == 1 || mP.PaintEdge == 2)
		{
			pDC->SelectObject(&RedPen);
			if(mP.PaintEdge == 1)
				pDC->Ellipse(mP.EdgeUp.x - 2,mP.EdgeUp.y - 2,mP.EdgeUp.x + 3,mP.EdgeUp.y + 3);
			else
				pDC->Ellipse(mP.BaseUp.x - 2,mP.BaseUp.y - 2,mP.BaseUp.x + 3,mP.BaseUp.y + 3);
		}
		else if(mP.PaintEdge == 3 || mP.PaintEdge == 4)
		{
			pDC->SelectObject(&BluePen);
			if(mP.PaintEdge == 3)
				pDC->Ellipse(mP.BaseDw.x - 2,mP.BaseDw.y - 2,mP.BaseDw.x + 3,mP.BaseDw.y + 3);
			else
				pDC->Ellipse(mP.EdgeDw.x - 2,mP.EdgeDw.y - 2,mP.EdgeDw.x + 3,mP.EdgeDw.y + 3);
		}
		pDC->SelectObject(pOldPen);
	}
}

int CSimulatedMicViewWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CDC * pDC = GetDC();
	mCompBMP.CreateCompatibleBitmap(pDC,1280,1024);
	ReleaseDC(pDC);

	UpdateMicView();
	mpZoom = new CZoom(this);
	mpZoom->m_Visible = false;
	mpZoom->m_ppTracks = &mpMicData->pMipsUp;
	mpZoom->mpMicData = mpMicData;

	mpZoom->Create(IDD_DIALOG_ZOOM,this);

	MVD.Sx = mP.sx;
	MVD.Sy = mP.sy;
	mpParent->SendMessage(WM_USER_UPDATEFOG,0xFFFF,(LPARAM)&MVD);
	return 0;
}


void CSimulatedMicViewWnd::PaintFrame(CDC *pDC)
{
	if(m_pImage)
		StretchDIBits(pDC->m_hDC, 0, 0, 1280, 1024, 0, 0, 1280, 1024, 
		m_pImage, mpBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void CSimulatedMicViewWnd::PaintGrains(CDC *pDC)
{
}

void CSimulatedMicViewWnd::PaintCet(CDC *pDC)
{
	if(MVD.Banner)
	{
		CFont * pFont;
		pFont = new CFont();
		pFont->CreateFont(16,15,0,0,FW_BOLD,true,0,0,DEFAULT_CHARSET,OUT_DEVICE_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_ROMAN,"");
		CFont * pOldFont;
		pOldFont = pDC->SelectObject(pFont);
		pDC->TextOutA(mDiagonal.x - 260 + mCorner.x,mDiagonal.y - 30 + mCorner.y," Simulated View ");
		pDC->SelectObject(pOldFont);
		delete pFont;
	}
}

void CSimulatedMicViewWnd::DrawSimulatedMicView(CDC *pDC)
{
	CDC * pdc = pDC;
	if(pDC == NULL)
	{
		pdc = GetDC();
	}
	CDC & dc = *pdc;
	CDC HiddenDC;
	HiddenDC.CreateCompatibleDC(pdc);
	CBitmap * pOldBitmap;
	pOldBitmap = HiddenDC.SelectObject(&mCompBMP);
	if(mpMicData->HasImages)
	{
		PaintFrame(&HiddenDC);
		PaintCet(&HiddenDC);
	}
	else
		PaintSimulatedGrains(&HiddenDC);
	PaintPrediction(&HiddenDC);
	PaintGrains(&HiddenDC);
	PaintMips(&HiddenDC);
	dc.BitBlt(0,0,mDiagonal.x,mDiagonal.y,&HiddenDC,mCorner.x,mCorner.y,SRCCOPY);
	HiddenDC.SelectObject(pOldBitmap);
	if(pDC == NULL)
		ReleaseDC(pdc);
}

void CSimulatedMicViewWnd::RedrawBitmap()
{
	CDC * pdc = GetDC();
	CDC HiddenDC;
	HiddenDC.CreateCompatibleDC(pdc);
	CBitmap * pOldBitmap;
	pOldBitmap = HiddenDC.SelectObject(&mCompBMP);
	pdc->BitBlt(0,0,mDiagonal.x,mDiagonal.y,&HiddenDC,mCorner.x,mCorner.y,SRCCOPY);
	HiddenDC.SelectObject(pOldBitmap);
	ReleaseDC(pdc);
}

#if(WINVER >= 0x0501)
BOOL CALLBACK CSimulatedMicViewWnd::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	SDisplayChooser *pDispC = (SDisplayChooser *)dwData;
	if (pDispC->ChosenNumber < 0)
	{
		pDispC->ChosenNumber = pDispC->Number;
		pDispC->Left = lprcMonitor->left;
		pDispC->Top = lprcMonitor->top;
		pDispC->Width = lprcMonitor->right - lprcMonitor->left;
		pDispC->Height = lprcMonitor->bottom - lprcMonitor->top;
	}
	else
	{
		int w = lprcMonitor->right - lprcMonitor->left;
		int h = lprcMonitor->bottom - lprcMonitor->top;
//		if (w >= 1024 && h >= 1024)
//			if (pDispC->ChosenNumber == 0 || (pDispC->Width < w && pDispC->Height < h))
			{
				pDispC->ChosenNumber = pDispC->Number;
				pDispC->Width = w;
				pDispC->Height = h;
				pDispC->Left = lprcMonitor->left;
				pDispC->Top = lprcMonitor->top;
			}	
	}
	pDispC->Number++;
	return TRUE;
}
#endif

void CSimulatedMicViewWnd::SetFrame(int Frame)
{
	ASSERT(mTotalFrames >= 0 && mTotalFrames < 512);
	int TotalFrames = mTotalFrames;
	if(TotalFrames == 0)
	{
		mpMicData->Level = 1;
		return;
	}
	if(Frame < 1)Frame = 1;
	else if(Frame > mTotalFrames - 1)Frame = mTotalFrames - 1;
	mpMicData->Level = Frame;
	MVD.Frame = Frame;
	MVD.z = *(mpMicData->pDepths + Frame);
	if(mpMicData->HasImages)
		m_pImage = (char *)(mpMicData->pGlobalBytes + Frame*1024*1280);
}

void CSimulatedMicViewWnd::DrawCircles(SIntGrain * pGrains,int NumGrains,COLORREF Color,CDC * pDC)
{
	int i;
	pDC->SetROP2(R2_COPYPEN);
	CPen * oldPen;
//	pDC->SelectClipRgn(&m_PlotRegion);
	CBrush * oldBrush,newBrush;
	LOGBRUSH mybrush = {BS_HOLLOW,(COLORREF)0xffffff,0};
	newBrush.CreateBrushIndirect(&mybrush);
	oldBrush = pDC->SelectObject(&newBrush);
	int HalfCCDLength = 640;//m_MicroParameters.HalfCCDLength;
	int HalfCCDWidth = 512;//m_MicroParameters.HalfCCDWidth;
	const float ScaleFactor = 1.f/mP.pixel;
	if(Color == FOG_CIAN)pDC->SetROP2(R2_MASKPEN);
	CPen * newPen = new CPen(PS_SOLID,1,Color);
	oldPen = pDC->SelectObject(newPen);
	for(i = 0; i < NumGrains; i++)
	{
		SIntGrain circle = *(pGrains + i);
		int x = (int)(circle.xx*ScaleFactor + HalfCCDLength+0.01), y = (int)(-circle.yy*ScaleFactor + HalfCCDWidth+0.01);
		pDC->Ellipse(x - 5,y - 5,x + 4,y + 4);
	}
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	delete newPen;
}

void CSimulatedMicViewWnd::PaintSimulatedGrains(CDC * pDC)
{
	SEmulsionSpace * pSpace = mpMicData->pSpaceUp;

	DrawSpots(pSpace,0,pDC);

}

void CSimulatedMicViewWnd::ShowMips(SMip *pMip,int MipVisible,int color,CDC * pDC)
{
	SMip * pnext = pMip;
	if(pMip == NULL)return;
	int MipCounter = 0;
	MipVisible = 0;
	while(pnext != NULL)
	{
		MipCounter++;
		bool ShowCurrentMip = (MipVisible == MipCounter || MipVisible == 0);
		if(pnext->NGrains > 0 && ShowCurrentMip)
		{
			DrawCircles(pnext->pGrains,pnext->NGrains,(COLORREF)color,pDC);
		}
		pnext = pnext->pNext;
	}
}

void CSimulatedMicViewWnd::PaintMips(CDC *pDC)
{
	if(MVD.Tracks)
	{
		ShowMips(mpMicData->pMipsUp,0,FOG_RED,pDC);
		ShowMips(mpMicData->pMipsDw,0,FOG_BLUE,pDC);
	}
}

void CSimulatedMicViewWnd::ChangePred(int Edge, CPoint Pt)
{
	float CenterZ = (mP.minup + mP.maxdw)/2.f;
	float DeltaZ;
	if(Edge == 1 || Edge == 4)
	{
		if(Edge == 1)
		{
			DeltaZ = mP.maxup - CenterZ;
		}
		else 
			DeltaZ = mP.mindw - CenterZ;
		mP.sx = ((float)(Pt.x - mP.pos.x))*mP.pixel/DeltaZ;
		mP.sy = ((float)(Pt.y - mP.pos.y))*mP.pixel/DeltaZ;
	}
	else if(Edge == 2 || Edge == 3)
	{
		float d;
		int ds;
		if(Edge == 2)
		{
			DeltaZ = mP.maxup - CenterZ;
			float wF = DeltaZ/(mP.minup - CenterZ);
			mP.pos.x = Round((mP.EdgeUp.x - Pt.x*wF)/(1 - wF));
			mP.sx = mP.pixel*(Pt.x - mP.pos.x)/(mP.minup - CenterZ);
			mP.pos.y = Round((mP.EdgeUp.y - Pt.y*wF)/(1 - wF));
			mP.sy = mP.pixel*(Pt.y - mP.pos.y)/(mP.minup - CenterZ);
			int x,y;
			float psx = mP.sx/mP.pixel;
			float psy = mP.sy/mP.pixel;
			x = Round(DeltaZ*psx) + mP.pos.x;
			y = Round(DeltaZ*psy) + mP.pos.y;
			if(x != mP.EdgeUp.x || y != mP.EdgeUp.y)
				MessageBox("Break");
			x = 0;
		}
		else
		{
			DeltaZ = mP.mindw - CenterZ;
			float wF = DeltaZ/(mP.maxdw - CenterZ);
//			int x = mP.EdgeDw.x, y = mP.EdgeDw.y;
			mP.pos.x = Round((mP.EdgeDw.x - Pt.x*wF)/(1 - wF));
			mP.sx = mP.pixel*(Pt.x - mP.pos.x)/(mP.maxdw - CenterZ);
			mP.pos.y = Round((mP.EdgeDw.y - Pt.y*wF)/(1 - wF));
			mP.sy = mP.pixel*(Pt.y - mP.pos.y)/(mP.maxdw - CenterZ);
		}
	}
}

void CSimulatedMicViewWnd::DrawSpots(SEmulsionSpace * pSpace,int color,CDC *pDC)
{
	int i,NumGrains = pSpace->NumGrains;
	SIntGrain * pGrains = pSpace->pGrains;
	float currentZeta = *(mpMicData->pDepths + mpMicData->Level);
	int Color = FOG_SPOTS_COLOR;
	CPen Pen1(PS_SOLID,1,Color),Pen3(PS_SOLID,3,Color),* pW;
	CPen Pen4(PS_SOLID,4,Color),Pen5(PS_SOLID,5,Color), * pOldPen;
	CPen Pen2(PS_SOLID,2,Color),Pen7(PS_SOLID,7,Color),Pen8(PS_SOLID,8,Color);
	int ColorRed = FOG_SPOTS_RED;
	CPen Pen1R(PS_SOLID,1,ColorRed),Pen3R(PS_SOLID,3,ColorRed);
	CPen Pen4R(PS_SOLID,4,ColorRed),Pen5R(PS_SOLID,5,ColorRed);
	CPen * pen1[2] = {&Pen1,&Pen1R};
	CPen * pen3[2] = {&Pen3,&Pen3R};
	CPen * pen4[2] = {&Pen4,&Pen4R};
	CPen * pen5[2] = {&Pen5,&Pen5R};

	pOldPen = pDC->SelectObject(&Pen1);
	const float ScaleFactor = 1.f/mP.pixel;
	int size,x,y;
	float HalfFocalDepth = 4,MaxGrainSize = 2.f;
	float Multiplier = MaxGrainSize/HalfFocalDepth;
	pDC->FillSolidRect(0,0,1280,1024,0xefefef);
	for(i = 0; i < NumGrains; i++)
	{
		size = (int)(MaxGrainSize - (int)(Multiplier*fabs((pGrains + i)->z - currentZeta)));
		x = ((int)((pGrains + i)->xx*ScaleFactor + 640+0.01));
		y = (int)(-(pGrains + i)->yy*ScaleFactor + 512+0.01);
		if(!(x >= 0 && x < 1280 && y >= 0 && y < 1024))
			continue;
		switch(size)
		{
		case 0:
			pW = pDC->SelectObject(*(pen1 + color));
			pDC->MoveTo(x,y); 
			pDC->LineTo(x + 1,y);
			break;
		case 1:
			pDC->SelectObject(*(pen3 + color));
			pDC->MoveTo(x,y); pDC->LineTo(x,y);
			break;
		case 2:
			pDC->SelectObject(*(pen4 + color));
			pDC->MoveTo(x,y); pDC->LineTo(x,y);
			break;
		case 3:
			pDC->SelectObject(*(pen3 + color));
			pDC->MoveTo(x - 1,y);
			pDC->LineTo(x + 1,y);
			pDC->MoveTo(x,y - 1);
			pDC->LineTo(x,y + 1);
			break;
		case 4:
			pDC->SelectObject(*(pen5 + color));
			pDC->MoveTo(x,y); pDC->LineTo(x,y);
			break;
		case 5 :
			pDC->SelectObject(*(pen3 + color));
			pDC->MoveTo(x - 2,y); pDC->LineTo(x + 2,y);
			pDC->MoveTo(x,y - 2); pDC->LineTo(x,y + 2);
			break;
		case 6:
			pDC->SelectObject(*(pen3 + color));
			pDC->MoveTo(x - 2,y); pDC->LineTo(x + 2,y);
			pDC->MoveTo(x,y - 2); pDC->LineTo(x,y + 2);
			pDC->SelectObject(*(pen1 + color));
			pDC->MoveTo(x - 2,y - 2); pDC->LineTo(x + 3,y - 2);
			pDC->MoveTo(x - 2,y + 2); pDC->LineTo(x + 3,y + 2);
			break;
		case 7:
			pDC->SelectObject(&Pen7);
			pDC->MoveTo(x,y); pDC->LineTo(x,y);
			break;
		case 8:
			pDC->SelectObject(&Pen8);
			pDC->MoveTo(x,y); pDC->LineTo(x,y);
			break;
		default:
			break;
		}
	}
	pDC->SelectObject(pOldPen);
}

