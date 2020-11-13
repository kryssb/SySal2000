// Zoom.cpp : implementation file
//

#include "stdafx.h"
#include "FogDLL.h"
#include "Zoom.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoom dialog


CZoom::CZoom(CWnd* pParent /*=NULL*/)
	: CDialog(CZoom::IDD, pParent),m_Picture(SButtonParam(this,PictureRightButtonDown,PictureLeftButtonDown,PictureMouseMove))
{
	//{{AFX_DATA_INIT(CZoom)
	m_Byte = 0;
	m_PosX = 0;
	m_PosY = 0;
	//}}AFX_DATA_INIT
	HalfSize = 10;
	m_pParent = pParent;
	int Headersize = sizeof(BITMAPINFOHEADER);
	m_pByte = (BYTE *)malloc(Headersize + 1024);
	BITMAPINFOHEADER InfoHeader;
	InfoHeader.biSize = Headersize;
	InfoHeader.biWidth = 1280;
	InfoHeader.biHeight = -1024;
	InfoHeader.biPlanes = 1;
	InfoHeader.biBitCount = 8;
	InfoHeader.biCompression = BI_RGB;
	InfoHeader.biSizeImage = 0;
	InfoHeader.biXPelsPerMeter = 10000;
	InfoHeader.biYPelsPerMeter = 10000;
	InfoHeader.biClrUsed = 0;
	InfoHeader.biClrImportant = 0;
	BITMAPINFO Info;
	Info.bmiHeader = InfoHeader;
	memcpy(m_pByte,&Info,Headersize);
	RGBQUAD * pRGB = (RGBQUAD *)(((char *)m_pByte + Headersize));
	for (int i = 0; i < 256; i++)
	{
		(*(pRGB + i)).rgbBlue = (*(pRGB + i)).rgbGreen = (*(pRGB + i)).rgbRed = i;
		(*(pRGB + i)).rgbReserved = 0; 
	};
	m_PlotRegion.CreateRectRgn(10,42,310,342);
	mChkMove = false;
	mpMipCircles = (WORD *)calloc(sizeof(WORD)*2,500);
}

CZoom::~CZoom()
{
	if(m_pByte != NULL)free(m_pByte);
	if(mpMipCircles != NULL)free(mpMipCircles);
}

void CZoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoom)
	DDX_Control(pDX, IDC_CMB_ZOOM_SIZE, m_ZoomCombo);
	DDX_Control(pDX, IDC_BTN_ZOOM_ZOOM, m_Picture);
	DDX_Text(pDX, IDC_EDT_ZOOM_BYTE, m_Byte);
	DDX_Text(pDX, IDC_EDT_ZOOM_X, m_PosX);
	DDX_Text(pDX, IDC_EDT_ZOOM_Y, m_PosY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoom, CDialog)
	//{{AFX_MSG_MAP(CZoom)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(IDC_CMB_ZOOM_SIZE, OnSelchangeCmbZoomSize)
	ON_BN_CLICKED(IDC_BTN_ZOOM_ZOOM, OnBtnZoomZoom)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_CHK_ZOOM_MOVE, OnCheckMove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoom message handlers
//		ON_NOTIFY_EX(TTN_NEEDTEXT,0,ZoomToolTip)
//	ON_NOTIFY_EX(TTN_GETDISPINFO,0,DispatchInfo)

void CZoom::PictureLeftButtonDown(void * pContext,UINT	Flags,CPoint point)
{
}
void CZoom::PictureRightButtonDown(void * pContext,UINT	Flags,CPoint point)
{
	CZoom & Z = *((CZoom *)pContext);
//	if(Z.m_pGT->IsMinimum)
	{
		if(Z.m_pGT->IsGrain)
		{
			int SeeMip = 0;//pFogDlg->GetDlgItemInt(IDC_EDT_FOGMAIN_SEEMIP);
			SMip * pMip = Z.GetTrack(SeeMip);
//			pFogDlg->m_CTracker.ToggleGrain(&pFogDlg->m_CGrainFinder.m_EmSpaceUp,pMip,&Z.m_pGT->Grano);
//			if(pFogDlg->m_pTracksDlg)pFogDlg->m_pTracksDlg->SetTrackData();
		}
	}
	 
}

void CZoom::PictureMouseMove(void * pContext, UINT Flags,CPoint point)
{
	CZoom &dis = *((CZoom *)pContext);
	if(!(point.x == dis.m_PicturePoint.x && point.y == dis.m_PicturePoint.y))
	{// if is needed because of tooltip that invokes OnMouseMove
		int Dx,Dy;
		float fdx,fdy;
		float PixelPerCell;
		bool IsGrain,IsImageFile;
		IsImageFile = dis.mpMicData->HasImages;
		dis.m_pGT = NULL;
		dis.UpdateValues(point);
//		if(pFogDlg->m_FileLoaded && (IsImageFile || RealSize))
		{
			PixelPerCell = 300.f/(2*dis.HalfSize + 1);
			fdx = (float)point.x;//(float)(dx = point.x - 10);
			fdy = (float)point.y;//(float)(dy = point.y - 42);
			Dx = ((int)(fdx/PixelPerCell + 0.001) + dis.m_ImageCenter.x - dis.HalfSize);
			Dy = ((int)(fdy/PixelPerCell + 0.001) + dis.m_ImageCenter.y - dis.HalfSize);
			dis.m_PicturePoint = point;
			SGrain ZoomMin;
			BYTE * pByte = 
				dis.mpMicData->pGlobalBytes + 1280*1024*dis.mpMicData->Level + Dx - 1 + (Dy - 1)*1280;
			if(IsImageFile)
			{
				dis.m_pGT = dis.mpFD->m_CGrainFinder.ExtendedGrainTest(pByte,FOG_OPT_DIFFERENTIAL | FOG_OPT_PARENTPARAM);
			}
			else
			{
				CDC * pDC =  (dis.m_Picture.GetDC());
				IsGrain = pDC->GetPixel(point) == FOG_SPOTS_COLOR;
				if(pDC)dis.m_Picture.ReleaseDC(pDC);
				float z = 0;
//				GetFloat(pFogDlg,IDC_EDT_FOGMAIN_DEPTH,z);
				if(true)
					dis.m_pGT = dis.mpFD->m_CGrainFinder.ExtendedGrainTest(Dx,Dy,z);
		
			}
		}
/*		else if(pFogDlg->m_FileLoaded && !RealSize)
		{
//			float SizeOnZoom = 300.f*(((float)(2*HalfSize + 1))/((float)(2*HalfSize + 2)));
			PixelPerCell = 300.f/(2*dis.HalfSize + 1);
			fdx = (float)point.x;//(float)(dx = point.x - 10);
			fdy = (float)point.y;//(float)(dy = point.y - 42);
			Dx = ((int)(fdx/PixelPerCell + 0.001) + dis.m_ImageCenter.x - dis.HalfSize - 1);
			Dy = ((int)(fdy/PixelPerCell + 0.001) + dis.m_ImageCenter.y - dis.HalfSize - 1);
			dis.m_PicturePoint = point;
			CDC * pDC =  (dis.m_Picture.GetDC());
			IsGrain = pDC->GetPixel(point) == FOG_SPOTS_COLOR;
			if(pDC)dis.m_Picture.ReleaseDC(pDC);
			float z;
			GetFloat(pFogDlg,IDC_EDT_FOGMAIN_DEPTH,z);
			if(true)
			dis.m_pGT = pFogDlg->m_CGrainFinder.ExtendedGrainTest(Dx,Dy,z);

		}*/
		dis.PictureToolTip = *dis.mpFD->FormatGrainTestString(dis.m_pGT);
		char * pToolTip = *((char **)(&dis.PictureToolTip));
		static SToolTip mytip;
		mytip.pText = dis.PictureToolTip.operator LPCTSTR();
		mytip.hcaller = dis.m_Picture.m_hWnd;
		mytip.Position = point;
		dis.mpFD->m_pToolTip->ShowTip(&mytip);
	}
}


void CZoom::OnOK() 
{
	m_Visible = false;
	CDialog::OnCancel();
}

void CZoom::OnCancel()
{
	m_Visible = false;
	CDialog::OnCancel();
}

void CZoom::OnClose() 
{
	m_Visible = false;
	CDialog::OnClose();
}


void CZoom::OnPaint() 
{
	CPaintDC dc(this);
}

void CZoom::ShowArea(CDC * MyDC)
{
	CDC * pStartDC = MyDC;
	int ImageOffsetX = 1;
	int ImageOffsetY = 1;
	static int OldSize = 0;
	int &oldSize = OldSize;
	bool IsButtonDC = true;
	if(MyDC == NULL)
	{
		MyDC = GetDC();
		ImageOffsetX = 10;
		ImageOffsetY = 42;
		IsButtonDC = false;
	}
	CButton * pCheck = (CButton *)GetDlgItem(IDC_CHK_ZOOM_COMPUTE);
	int mZoomCompute = pCheck->GetCheck();
	pCheck = (CButton *)GetDlgItem(IDC_CHK_ZOOM_SHOWMIP);
	int mZoomShowMips = pCheck->GetCheck();
	bool IsImageFile = mpMicData->HasImages;
	if(IsImageFile)
	{
		BYTE * ImagePointer = mpMicData->pGlobalBytes + (1280*1024)*mpMicData->Level;
		WORD * pCircles = mpFD->m_CGrainFinder.ComputeArea(ImagePointer,m_ImageCenter.x,m_ImageCenter.y,HalfSize,HalfSize);
		int result = StretchDIBits(MyDC->m_hDC,ImageOffsetX,ImageOffsetY,300,300,m_ImageCenter.x - HalfSize - 1,1024 - m_ImageCenter.y - HalfSize,
			2*HalfSize + 1,2*HalfSize + 1,ImagePointer,(BITMAPINFO *)m_pByte,DIB_RGB_COLORS,SRCCOPY);
		if(mZoomCompute)DrawCircles(pCircles,MyDC,IsButtonDC);
		if(mZoomShowMips)ZoomShowMips(MyDC,IsButtonDC);
	}
	else
	{
		CDC * pParentDC = m_pParent->GetDC();
		CPoint ImagePoint;
		int X,Y,SizeOnMain,SizeOnZoom,HS;
//		if(IsImageRealSize)
		{
			SizeOnMain = 2*HalfSize + 1;
			SizeOnZoom = 300;
			HS = HalfSize;
			X = m_Point.x; Y = m_Point.y;
		}
/*		else
		{
			SizeOnMain = HalfSize + 1;
			float temp = ((300.f)/((float)(2*HalfSize + 1)))*((float)(2*HalfSize + 2));
			SizeOnZoom = (int)temp;
			HS = (HalfSize + 1)/2;
			X = m_Point.x; Y = m_Point.y;
		}*/
		if(X < HS + 1)X = HS + 1;
		if(X > 640 - HS)X = 640 - HS;
		if(Y < HS + 1)Y = HS + 1;
		if(Y > 512 - HS)Y = 512 - HS;
		if(IsButtonDC)m_PlotRegion.OffsetRgn(-10,-42);
		MyDC->SelectClipRgn(&m_PlotRegion);
		MyDC->StretchBlt(ImageOffsetX,ImageOffsetY,SizeOnZoom,SizeOnZoom,pParentDC,X - HS,Y - HS,SizeOnMain,SizeOnMain,SRCCOPY);
		if(IsButtonDC)m_PlotRegion.OffsetRgn(10,42);
		m_pParent->ReleaseDC(pParentDC);
	}
	if(pStartDC == NULL)ReleaseDC(MyDC);
}
void CZoom::DrawCircles(WORD *pCircles,CDC * pDC,bool IsButtonDC,bool IsMip)
{
	int i,ImageOffsetX = 1,ImageOffsetY = 1;
	if(IsButtonDC)
	{
		m_PlotRegion.OffsetRgn(-10,-42);
	}
	else
	{
		ImageOffsetX = 10;
		ImageOffsetY = 42;
	}
	pDC->SetROP2(R2_COPYPEN);
	CPen * oldPen;
	CBrush * oldBrush,newBrush;
	LOGBRUSH mybrush = {BS_HOLLOW,(COLORREF)0xffffff,0};
	newBrush.CreateBrushIndirect(&mybrush);
	oldBrush = pDC->SelectObject(&newBrush);
	pDC->SelectClipRgn(&m_PlotRegion);
	int Radius = (int)(((2.5f*301.f)/(HalfSize*2 + 1) + 0.5f));
	float PixelPerCell = 300.f/(2*HalfSize + 1);
	int PenSize = (int)(PixelPerCell/2 + 0.5f);
	if(IsMip && false)
	{
		if(PenSize > 1)PenSize--;
		if(Radius > 1)Radius--;
	}
	CPen * newPen;
	if(IsMip) newPen = new CPen(PS_SOLID,PenSize,FOG_CIAN);
	else newPen = new CPen(PS_SOLID,PenSize,FOG_RED);
	if(newPen == NULL)MessageBox("NULL");
	if(IsMip)pDC->SetROP2(R2_MASKPEN);
	oldPen = pDC->SelectObject(newPen);
	int counter = 0;
	for(i = 0; *pCircles != NULL;pCircles += 2)
	{
		int pointx = (int)((*pCircles - m_ImageCenter.x + HalfSize)*PixelPerCell + ImageOffsetX + PenSize);
		int pointy = (int)((*(pCircles + 1) - m_ImageCenter.y + HalfSize)*PixelPerCell + ImageOffsetY + PenSize);
		pDC->Ellipse(pointx - Radius,pointy - Radius,pointx + Radius,pointy + Radius);
		counter++;
	}
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	delete newPen;
	if(IsButtonDC)
	{
		m_PlotRegion.OffsetRgn(10,42);
	}
}
void CZoom::UpdateValues(CPoint ThePoint)
{
	static CPoint OldPoint;
//	if(ThePoint.x > 0 && ThePoint.y > 0)OldPoint = ThePoint;
	CPoint point = OldPoint;
	{
		bool IsImageFile = true;
		CString temp;
		int Dx,Dy;
		float fdx,fdy;
		float PixelPerCell;
		PixelPerCell = 300.f/(2*HalfSize + 1);
		fdx = (float)ThePoint.x;//(float)(dx = point.x - 10);
		fdy = (float)ThePoint.y;//(float)(dy = point.y - 42);
//		if(IsImageRealSize || IsImageFile)
		{
			Dx = ((int)(fdx/PixelPerCell + 0.001) + m_ImageCenter.x - HalfSize);
			Dy = ((int)(fdy/PixelPerCell + 0.001) + m_ImageCenter.y - HalfSize);
		}
/*		else
		{
			Dx = ((int)(fdx/PixelPerCell + 0.001) + m_ImageCenter.x - HalfSize - 1);
			Dy = ((int)(fdy/PixelPerCell + 0.001) + m_ImageCenter.y - HalfSize - 1);	
		}*/
		SetValues(Dx,Dy);
	}
}

void CZoom::SetValues(int x, int y)
{
	if(x == -1)x = m_ImageCenter.x;
	if(y == -1)y = m_ImageCenter.y;
	m_PosX = x;
	m_PosY = y;
	CString temp;
	SetDlgItemText(IDC_EDT_ZOOM_X,(temp.Format("%d",x),temp));
	SetDlgItemText(IDC_EDT_ZOOM_Y,(temp.Format("%d",y),temp));
	int XWidth = 1280;
	int YWidth = 1024;
	if(x < 1)x=1;if(x>XWidth)x=XWidth;if(y<1)y=1;if(y>YWidth)y=YWidth;
	BYTE ByteValue;
	BYTE * ImagePointer = mpMicData->pGlobalBytes + (1280*1024)*mpMicData->Level;
	bool IsImageFile = mpMicData->HasImages;
	if(IsImageFile)
	{
		ByteValue = *(ImagePointer + x + XWidth*y - XWidth - 1);
		SetDlgItemText(IDC_EDT_ZOOM_BYTE,(temp.Format("%d",ByteValue),temp));
	}
	else SetDlgItemText(IDC_EDT_ZOOM_BYTE,(temp.Format("   "),temp));
}

void CZoom::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CZoom::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CComboBox * pCombo = (CComboBox *)GetDlgItem(IDC_CMB_ZOOM_SIZE);
	int result = pCombo->SetDroppedWidth(60);
	if(result == CB_ERR)ASSERT(FALSE);
	pCombo->SetCurSel(2);
	int Items = pCombo->GetCount();
	int Value;
	CString text;
	for(int i = 0; i < Items; i++)
	{
		pCombo->GetLBText(i,text);
		int result = sscanf(text,"%d",&Value);
		pCombo->SetItemData(i,Value);
	}
	OnSelchangeCmbZoomSize();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CZoom::UpdateZoomSize()
{
	CComboBox * pCombo = (CComboBox *)GetDlgItem(IDC_CMB_ZOOM_SIZE);
	int Selected = pCombo->GetCurSel();
	UINT Selection = pCombo->GetItemData(Selected);
	float Sel = (float)Selection;
	float PixelLen = 3.282045f;
	bool IsImageFile = mpMicData->HasImages;
//	if(!pFogDlg->mChkRealSize && !IsImageFile)PixelLen *= 2.f;
	HalfSize = (int)((Sel*PixelLen - 1.f)/2.f + 0.5f);

	SetImagePos(&m_ImagePoint);

}

void CZoom::OnSelchangeCmbZoomSize() 
{
	UpdateZoomSize();
	ShowArea();
}

void CZoom::OnBtnZoomZoom() 
{
//	OnCancel();
	
}

void CZoom::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (nIDCtl == IDC_BTN_ZOOM_ZOOM && lpDrawItemStruct->itemAction == 1)
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		ShowArea(&dc);
		dc.Detach();	
	}
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CZoom::OnCheckMove() 
{
	mChkMove = !mChkMove;
}

void CZoom::ZoomShowMips(CDC *pDC,bool IsButtonDC)
{
	SMip * pNext = *m_ppTracks;
	int count = 1;
	while(pNext->pNext)
	{ count++; pNext = pNext->pNext;}
	int SeeMip = 0;//pFogDlg->GetDlgItemInt(IDC_EDT_FOGMAIN_SEEMIP);
	if(SeeMip > 0 && SeeMip < count)
	{
		MipToCircles(GetTrack(SeeMip));
		DrawCircles(mpMipCircles,pDC,IsButtonDC,true);
	}
}

SMip * CZoom::GetTrack(int TrackNumber)// Starting from 1
{
	int count = 1;
	SMip * pMip = *m_ppTracks;
	for(int i = 1; i < TrackNumber; i++)
	{
		if(pMip->pNext == NULL)break;
		pMip = pMip->pNext;
		count++;
	}
	if(count == TrackNumber)return pMip;
	else return *m_ppTracks;
}


void CZoom::SetImagePos(CPoint *pPoint)
{
	m_ImagePoint = *pPoint;
	int ZoomPosX = pPoint->x,ZoomPosY = pPoint->y;
	if(ZoomPosX < HalfSize + 1)ZoomPosX = HalfSize + 1;
	if(ZoomPosY < HalfSize + 1)ZoomPosY = HalfSize + 1;
	if(ZoomPosX > 1280 - HalfSize)ZoomPosX = 1280 - HalfSize;
	if(ZoomPosY > 1024 - HalfSize)ZoomPosY = 1024 - HalfSize;
	m_ImageCenter.x = ZoomPosX;
	m_ImageCenter.y = ZoomPosY;
}

void CZoom::MipToCircles(SMip *pMip)
{
	int i,pointx,pointy;
	float InvPixLen = 3.282045f;
	int HalfXWidth = 640,HalfYWidth = 512;
	memset(mpMipCircles,0,2000);
	for(i = 0; i < pMip->NGrains; i++)
	{
		pointx = (int)((pMip->pGrains + i)->xx*InvPixLen*1.0001) + HalfXWidth;
		pointy = HalfYWidth - (int)((pMip->pGrains + i)->yy*InvPixLen*1.0001);
		*(mpMipCircles + 2*i) = pointx;
		*(mpMipCircles + 2*i + 1) = pointy;
	}
}
