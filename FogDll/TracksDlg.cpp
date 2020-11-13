// TracksDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FogDLL.h"
#include "TracksDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTracksDlg dialog
extern CTracker * pGT;

CTracksDlg::CTracksDlg(SMip ** ppMip,CWnd* pParent /*=NULL*/)
	: CDialog(CTracksDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTracksDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParent = pParent;
	m_ppTrack = ppMip;
	mChkShowMip = 0;
}


void CTracksDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTracksDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTracksDlg, CDialog)
	//{{AFX_MSG_MAP(CTracksDlg)
	ON_BN_CLICKED(IDC_BTN_TRACKS_PREVIOUS, OnBtnTrackerPrevious)
	ON_BN_CLICKED(IDC_BTN_TRACKS_NEXT, OnBtnTrackerNext)
	ON_BN_CLICKED(IDC_CHK_TRACKS_SHOW, OnChkTracksShow)
	ON_MESSAGE(WM_USER_UPDATETRACKS,UpdateTracks)
	ON_BN_CLICKED(IDC_BTN_TRACKS_DELETE, OnBtnTracksDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTracksDlg message handlers

void CTracksDlg::OnBtnTrackerPrevious() 
{
	if(m_NumTrack == m_TotalTrack)GetDlgItem(IDC_BTN_TRACKS_NEXT)->EnableWindow(TRUE);
	m_pCurrentMip = GetTrack(--m_NumTrack);
	if(m_NumTrack == 1)GetDlgItem(IDC_BTN_TRACKS_PREVIOUS)->EnableWindow(FALSE);
	SetTrackData();	
}

void CTracksDlg::OnBtnTrackerNext() 
{
	if(m_NumTrack == 1)GetDlgItem(IDC_BTN_TRACKS_PREVIOUS)->EnableWindow(TRUE);
	m_pCurrentMip = GetTrack(++m_NumTrack);
	if(m_NumTrack == m_TotalTrack)GetDlgItem(IDC_BTN_TRACKS_NEXT)->EnableWindow(FALSE);
	SetTrackData();	
}

int CTracksDlg::SetTrackData(int Sender)
{
	CString text;
	int NGrains = m_pCurrentMip->NGrains;
	SGrainChain * pChain = new SGrainChain(NGrains);
	float wx = 0, wy = 0, wz = 0;
	int i;
	for(i = 0; i < NGrains; i++)
	{
		*(pChain->ppGrains + i) = m_pCurrentMip->pGrains + i;
	}
	pChain->axe = m_pCurrentMip->Axe;
	pChain->NGrains = m_pCurrentMip->NGrains;
	pChain->Alpha = m_pCurrentMip->Alfa;
	pGT->GetNominalLength(pGT->TP.pEmSpaceUp,pChain);
	pGT->LinearFit(pChain,true);
	if(m_pCurrentMip->NGrains > 0)
	{
		for(i = 0; i < m_pCurrentMip->NGrains; i++)
		{
			wx += (m_pCurrentMip->pGrains + i)->x;
			wy += (m_pCurrentMip->pGrains + i)->y;
			wz += (m_pCurrentMip->pGrains + i)->z;
		}
		wx /= m_pCurrentMip->NGrains;
		wy /= m_pCurrentMip->NGrains;
		wz /= m_pCurrentMip->NGrains;
	}
	static Vector Center;
	Center = Vector(wx,wy,wz);
	Vector * pCenter = &Center;
	SetDlgItemText(IDC_EDT_TRACKS_CENTERX,(text.Format("%g",wx),text));
	SetDlgItemText(IDC_EDT_TRACKS_CENTERY,(text.Format("%g",wy),text));
	SetDlgItemText(IDC_EDT_TRACKS_CENTERZ,(text.Format("%g",wz),text));
	Vector Seg = *(m_pCurrentMip->pGrains) - *(m_pCurrentMip->pGrains + m_pCurrentMip->NGrains - 1);
	wx = m_pCurrentMip->mx; wz = m_pCurrentMip->mz;
	float module = Seg.Module();
	Vector NewSeg;
	if(NGrains)NewSeg = *(*(pChain->ppGrains + 0)) - *(*(pChain->ppGrains + NGrains - 1));
	float newModule = NewSeg.Module();
	SetDlgItemText(IDC_EDT_TRACKS_LENGTH,(text.Format("%g",m_pCurrentMip->Length),text));
	SetDlgItemText(IDC_EDT_TRACKS_NLENGTH,(text.Format("%g",m_pCurrentMip->NomLength),text));
	SetDlgItemText(IDC_EDT_TRACKS_LINEAR_DENSITY,(text.Format("%g",m_pCurrentMip->GiC),text));
	SetDlgItemText(IDC_EDT_TRACKS_MEANDEV,(text.Format("%g",m_pCurrentMip->md),text));
	SetDlgItemText(IDC_EDT_TRACKS_MX,(text.Format("%g",m_pCurrentMip->mx),text));
	SetDlgItemText(IDC_EDT_TRACKS_NX,(text.Format("%g",m_pCurrentMip->nx),text));
	SetDlgItemText(IDC_EDT_TRACKS_MY,(text.Format("%g",m_pCurrentMip->my),text));
	SetDlgItemText(IDC_EDT_TRACKS_NY,(text.Format("%g",m_pCurrentMip->ny),text));
	SetDlgItemText(IDC_EDT_TRACKS_MZ,(text.Format("%g",m_pCurrentMip->mz),text));
	SetDlgItemText(IDC_EDT_TRACKS_NZ,(text.Format("%g",m_pCurrentMip->nz),text));
	SetDlgItemText(IDC_EDT_TRACKS_SIGMAX,(text.Format("%g",m_pCurrentMip->sigmax),text));
	SetDlgItemText(IDC_EDT_TRACKS_SIGMAY,(text.Format("%g",m_pCurrentMip->sigmay),text));
	SetDlgItemText(IDC_EDT_TRACKS_SIGMAZ,(text.Format("%g",m_pCurrentMip->sigmaz),text));
	SetDlgItemInt(IDC_EDT_TRACKS_GRAINS,m_pCurrentMip->NGrains);
	SetDlgItemText(IDC_EDT_TRACKS_MEANDIST,(text.Format("%g",m_pCurrentMip->MeanGap),text));
	SetDlgItemInt(IDC_EDT_TRACKS_TRACK,m_NumTrack);
	wx = m_pCurrentMip->mx;
	wy = m_pCurrentMip->my;
	wz = m_pCurrentMip->mz;
	SetDlgItemText(IDC_EDT_TRACKS_THETA,(text.Format("%g",(180.f/PI_FOG)*(atan2(sqrt(wy*wy + wx*wx),sqrt(wz*wz)))),text));
	wz = (180.f/PI_FOG)*atan2(wy,wx);
	if(wz < 0)wz += 360.f;
	SetDlgItemText(IDC_EDT_TRACKS_PHI,(text.Format("%g",wz),text));
	wx = atan2(0.5,0.5);
	wy = atan2(0.5,-0.5);
	wz = atan2(-0.5,0.5);
	wx = atan2(-0.5,-0.5);

	if(mChkShowMip && !(Sender & FOG_CHECK_SHOW))m_pParent->PostMessage(WM_USER_SHOWSINGLEMIP,(WPARAM)m_NumTrack,(LPARAM)&Center);
	if(pChain)delete pChain;
	else MessageBox("Mii!");
	return 0;
}

void CTracksDlg::OnChkTracksShow() 
{
	mChkShowMip = !mChkShowMip;
	m_pParent->SetDlgItemInt(IDC_EDT_FOGMAIN_SEEMIP,m_NumTrack);	
}

void CTracksDlg::OnCancel() 
{
	ShowWindow(false);	
}

BOOL CTracksDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	PostMessage(WM_USER_UPDATETRACKS);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



int CTracksDlg::CountTracks(SMip *pmip)
{
	int count = 0;
	SMip * pMip;
	pMip = pmip;
	while(pMip->pNext != NULL)
	{	count++;
		pMip = pMip->pNext;}
	return count;
}

SMip * CTracksDlg::GetTrack(int TrackNumber)// Starting from 1
{
	int count = 1;
	SMip * pMip = *m_ppTrack;
	if(m_TotalTrack == 0)return pMip;
	if(TrackNumber == 0)TrackNumber = m_TotalTrack;
	for(int i = 1; i < TrackNumber; i++)
	{
		if(pMip->pNext == NULL)break;
		pMip = pMip->pNext;
		count++;
	}
	if(count == TrackNumber)return pMip;
	else return NULL;
}


void CTracksDlg::OnOK() 
{
//	ShowWindow();
//	CDialog::OnOK();
}

LRESULT CTracksDlg::UpdateTracks(WPARAM wParam,LPARAM lParam)
{
	WORD Sender = (unsigned short)wParam;
	int Track = (int)lParam;
	if(Sender & FOG_TRACKS_DLG || (Track == 0 && !(Sender & FOG_CHECK_SHOW)))
	{
		m_TotalTrack = CountTracks(*m_ppTrack);
		SetDlgItemInt(IDC_EDT_TRACKS_TRACKS,m_TotalTrack);
		if(m_TotalTrack == 0)m_NumTrack = 0;
	}
	if(Track == 0 && !(Sender & FOG_CHECK_SHOW))
	{
		if(m_TotalTrack > 0)m_NumTrack = 1;
		else m_NumTrack = 0;
		m_pCurrentMip = GetTrack(m_NumTrack);

		GetDlgItem(IDC_BTN_TRACKS_PREVIOUS)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TRACKS_NEXT)->EnableWindow(m_TotalTrack > 1);
	}
	else if(Track <= m_TotalTrack && mChkShowMip)
	{
		m_NumTrack = Track;
		m_pCurrentMip = GetTrack(m_NumTrack);
		GetDlgItem(IDC_BTN_TRACKS_PREVIOUS)->EnableWindow(m_NumTrack > 1);
		GetDlgItem(IDC_BTN_TRACKS_NEXT)->EnableWindow(m_NumTrack < m_TotalTrack);
	}
	if(m_NumTrack > 0)SetTrackData(Sender);
	return NULL;
}

UINT RenameButton(LPVOID pParam)
{
	CWnd * pButton = (CWnd *)pParam;
	Sleep(500);
	return 0;
}

void CTracksDlg::OnBtnTracksDelete() 
{
	static int NumTrack = -1;
	CWnd * pButton = GetDlgItem(IDC_BTN_TRACKS_DELETE);
	NumTrack = m_NumTrack;
	if(m_TotalTrack == 0)return;
	if(m_NumTrack == 1)
	{
		SMip * pMip = m_pCurrentMip->pNext;
		m_pCurrentMip->Delete();
		*m_ppTrack = pMip;
		m_pCurrentMip = pMip;
	}
	else if(m_NumTrack == m_TotalTrack)
	{
		SMip * pMip = m_pCurrentMip->pPrevious;
		m_pCurrentMip->Delete();
		m_pCurrentMip = pMip;
		NumTrack = --m_NumTrack;
	}
	else
	{
		m_pCurrentMip = m_pCurrentMip->Delete();
		NumTrack = m_NumTrack;
	}
	UpdateTracks(FOG_TRACKS_DLG,m_NumTrack);
	m_pParent->SetDlgItemInt(IDC_EDT_FOGMAIN_MIPS,m_TotalTrack);
}
