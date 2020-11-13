// Monitor.cpp : implementation file
//

#include "stdafx.h"
#include "time.h"
#include "resource.h"
#include "Monitor.h"
#include "../Common/Stage3.h"
//#include "PlateChangerClass.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog


CMonitor::CMonitor(ConfigData *pc, HANDLE *phmonitormutex, HANDLE *phrun, void *pctx, void (*penabler)(void *, bool), CWnd* pParent /*=NULL*/)
	: CDialog(CMonitor::IDD, pParent), pHMonitorMutex(phmonitormutex), pHRun(phrun), pContext(pctx), pEnabler(penabler), SpeedMultiplier(1)
{
	SourceBank=-1;
	ReadyToScan=false;
	DestinationBank=-1;
    DebugLevel=0;
	pSt=NULL;
	pC=pc;
	IsStageHomed=false;
	//{{AFX_DATA_INIT(CMonitor)
	m_checkin1x = FALSE;
	m_checkin0x = FALSE;
	m_checkin2x = FALSE;
	m_checkin3x = FALSE;
	m_checkin4x = FALSE;
	m_checkin5x = FALSE;
	m_checkin6x = FALSE;
	m_checkin7x = FALSE;
	m_xpos = _T("");
	m_checkin0z = FALSE;
	m_checkin1z = FALSE;
	m_checkin2z = FALSE;
	m_checkin3z = FALSE;
	m_checkin4z = FALSE;
	m_checkin5z = FALSE;
	m_checkin6z = FALSE;
	m_checkin7z = FALSE;
	m_zpos = _T("");
	m_xposmsg = _T("");
	m_zposmsg = _T("");
	m_source = _T("");
	m_scanned = _T("");
	//}}AFX_DATA_INIT
	m_source = "1";//default number for "source" emulsion bank
	m_scanned = "2";//default number for "scanned" emulsion bank
//	m_source3 = "1";//default number for "source" emulsion bank
//	m_scanned3 = "2";//default number for "scanned" emulsion bank
//	m_Numem=57;
	InitDone=false;
    ResetBanks();

}


void CMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonitor)
	DDX_Control(pDX, IDC_BANK4, m_BANK4);
	DDX_Control(pDX, IDC_CHECK_SEPARATOR2, m_Separator2);
	DDX_Control(pDX, IDC_CHECK_SEPARATOR, m_Separator);
	DDX_Control(pDX, IDC_BANK3, m_BANK3);
	DDX_Control(pDX, IDC_BANK2, m_BANK2);
	DDX_Control(pDX, IDC_BANK1, m_BANK1);
	DDX_Control(pDX, IDC_BANK0, m_BANK0);
	DDX_Check(pDX, IDC_CHECK_IN1_X, m_checkin1x);
	DDX_Check(pDX, IDC_CHECK_IN0_X, m_checkin0x);
	DDX_Check(pDX, IDC_CHECK_IN2_X, m_checkin2x);
	DDX_Check(pDX, IDC_CHECK_IN3_X, m_checkin3x);
	DDX_Check(pDX, IDC_CHECK_IN4_X, m_checkin4x);
	DDX_Check(pDX, IDC_CHECK_IN5_X, m_checkin5x);
	DDX_Check(pDX, IDC_CHECK_IN6_X, m_checkin6x);
	DDX_Check(pDX, IDC_CHECK_IN7_X, m_checkin7x);
	DDX_Text(pDX, IDC_M_THPOS, m_xpos);
	DDX_Check(pDX, IDC_CHECK_IN0_Z, m_checkin0z);
	DDX_Check(pDX, IDC_CHECK_IN1_Z, m_checkin1z);
	DDX_Check(pDX, IDC_CHECK_IN2_Z, m_checkin2z);
	DDX_Check(pDX, IDC_CHECK_IN3_Z, m_checkin3z);
	DDX_Check(pDX, IDC_CHECK_IN4_Z, m_checkin4z);
	DDX_Check(pDX, IDC_CHECK_IN5_Z, m_checkin5z);
	DDX_Check(pDX, IDC_CHECK_IN6_Z, m_checkin6z);
	DDX_Check(pDX, IDC_CHECK_IN7_Z, m_checkin7z);
	DDX_Text(pDX, IDC_M_ZPOS, m_zpos);
	DDX_Text(pDX, IDC_EDIT_XPOSMSG, m_xposmsg);
	DDX_Text(pDX, IDC_EDIT_ZPOSMSG, m_zposmsg);
	DDX_Text(pDX, IDC_EDIT_SOURCE, m_source);
	DDV_MaxChars(pDX, m_source, 1);
	DDX_Text(pDX, IDC_EDIT_SCANNED, m_scanned);
	DDV_MaxChars(pDX, m_scanned, 1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMonitor, CDialog)
	//{{AFX_MSG_MAP(CMonitor)
	ON_BN_CLICKED(IDC_M_HIDE, OnHide)
	ON_BN_CLICKED(IDC_M_TOGGLEMANUAL, OnToggleManual)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON_GO_X, OnButtonGoX)
	ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
	ON_EN_UPDATE(IDC_M_THPOS, OnUpdateMThpos)
	ON_EN_UPDATE(IDC_M_ZPOS, OnUpdateMZpos)
	ON_BN_CLICKED(IDC_BUTTON_GO_Z, OnButtonGoZ)
	ON_EN_UPDATE(IDC_EDIT_SOURCE, OnUpdateEditSource)
	ON_EN_UPDATE(IDC_EDIT_SCANNED, OnUpdateEditScanned)
	ON_BN_CLICKED(IDC_INITIALIZE, OnInitialize)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_BUTTON_VACON, OnButtonVacon)
	ON_BN_CLICKED(IDC_BUTTON_VACOFF, OnButtonVacoff)
	ON_BN_CLICKED(IDC_UNLOAD, OnUnload)
	ON_BN_CLICKED(IDC_CHGPLT, OnChgplt)
	ON_BN_CLICKED(IDC_MVSEP, OnMvsep)
	ON_BN_CLICKED(IDC_CHGPLT2, OnChgplt2)
	ON_BN_CLICKED(IDC_BUTTON_VACOFF2, OnButtonVacoff2)
	ON_BN_CLICKED(IDC_BUTTON_VACON2, OnButtonVacon2)
	ON_BN_CLICKED(IDC_SORT, OnSort)
	ON_BN_CLICKED(IDC_CHECK_SEPARATOR, OnCheckSeparator)
	ON_BN_CLICKED(IDC_CHECK_SEPARATOR2, OnCheckSeparator2)
	ON_EN_CHANGE(IDC_EDIT_SOURCE3, OnChangeEditSource3)
	ON_BN_CLICKED(IDC_LOADBANK, OnLoadbank)
	ON_BN_CLICKED(IDC_DEBUGLEVEL, OnDebuglevel)
	ON_BN_CLICKED(IDC_LOADEMID, OnLoademid)
	ON_BN_CLICKED(IDC_UNLOADEM, OnUnloadem)
	ON_BN_CLICKED(IDC_HOMESTAGE, OnHomestage)
	ON_BN_CLICKED(IDC_INITIALIZE2, OnInitialize2)
	ON_BN_CLICKED(IDC_BUTTON_POWERON, OnButtonPoweron)
	ON_WM_DRAWITEM()
	ON_MESSAGE(UM_REFRESH, OnRefresh)
	ON_BN_CLICKED(IDC_BUTTON_POWEROFF, OnButtonPoweroff)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitor message handlers

void CMonitor::OnHide() 
{
	// TODO: Add your control notification handler code here
	ResetEvent(*pHRun);
	ShowWindow(SW_HIDE);
	EnableWindow(FALSE);
	pEnabler(pContext, false);

}

//DEL void CMonitor::OnReset() //Here we write all 0 in ports P4 and P5
//DEL {
//DEL 		WaitForSingleObject(*pHMonitorMutex, INFINITE);
//DEL 		BYTE dataout[8] = {0,0,0,0,0,0,0,0};
//DEL 		int read;
//DEL 		InitDone=false;
//DEL         ReadyToScan=false;
//DEL 
//DEL 		ReleaseMutex(*pHMonitorMutex);
//DEL }


void CMonitor::OnToggleManual() 
{
}

void CMonitor::OnSpeedX1() 
{
	SpeedMultiplier = 1;
}

void CMonitor::OnSpeedX10() 
{
	SpeedMultiplier = 10;
}

void CMonitor::OnSpeedX100() 
{
	SpeedMultiplier = 100;
}

void CMonitor::EnableManualControl(bool bEnable)
{
	(*pEnabler)(pContext, bEnable);
	// SAMUEL: change the monitor dialog for manual control / software control
}

LRESULT CMonitor::OnRefresh(WPARAM, LPARAM)
{
//	char string[16];
	{
		int Pos = 0;
//		long retval;
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		GetDlgItem(IDC_M_THPOS)->GetWindowText(xpos);
		ReleaseMutex(*pHMonitorMutex);
		//sprintf(string, "%d", Pos);
		//GetDlgItem(IDC_M_THPOS)->SetWindowText(string);
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		GetDlgItem(IDC_M_ZPOS)->GetWindowText(zpos);
		ReleaseMutex(*pHMonitorMutex);
		//sprintf(string, "%d", Pos);
		//GetDlgItem(IDC_M_ZPOS)->SetWindowText(string);
		GetDlgItem(IDC_EDIT_SOURCE)->GetWindowText(sourcebank);
		GetDlgItem(IDC_EDIT_SCANNED)->GetWindowText(scannedbank);
		};
	{
//		unsigned char fwdStatus, revStatus;
		DWORD a;
		a = 0;
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		ReleaseMutex(*pHMonitorMutex);
//		if (revStatus & 0x02) a |= pC->InvertX ? 2 : 1;
//		if (fwdStatus & 0x02) a |= pC->InvertX ? 1 : 2;
//		DrawSemaphore(IDC_M_THRED, IDC_M_THGREEN, (bool)a);
		a = 0;
		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		// SAMUEL: read the limit switch for Z
		ReleaseMutex(*pHMonitorMutex);
		/* SAMUEL: change the value of a... */
//		if (revStatus & 0x04) a |= pC->InvertY ? 2 : 1;
//		if (fwdStatus & 0x04) a |= pC->InvertY ? 1 : 2;
//		DrawSemaphore(IDC_M_ZRED, IDC_M_ZGREEN, (bool)a);
		};
	if((!ReadyToScan) || (!IsStageHomed)) DrawSemaphore(IDC_M_RDYRED,IDC_M_RDYGREEN,true);
		else DrawSemaphore(IDC_M_RDYRED,IDC_M_RDYGREEN,false);
	if(!IsStageHomed) DrawSemaphore(IDC_M_RDYRED2,IDC_M_RDYGREEN2,true);
		else DrawSemaphore(IDC_M_RDYRED2,IDC_M_RDYGREEN2,false);

	return 0;
}

void CMonitor::DrawSemaphore(int IdRed, int IdGreen, bool Status)
{
	CWnd *pWnd;
	CRect ClRect;
	pWnd = GetDlgItem(IdRed);
	pWnd->GetClientRect(&ClRect);
	{	
		CClientDC dc(pWnd);
		CBrush Brush(Status ? RGB(255, 0, 0) : RGB(96, 0, 0));
		dc.FillRect(&ClRect, &Brush);
		};
	pWnd = GetDlgItem(IdGreen);
	pWnd->GetClientRect(&ClRect);
	{	
		CClientDC dc(pWnd);
		CBrush Brush(Status ? RGB(0, 96, 0) : RGB(0, 255, 0));
		dc.FillRect(&ClRect, &Brush);
		};
}

BOOL CMonitor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//    OnDebuglevel();
 	RECT r;
	r.left = r.top = 0;
	r.right = 125;
	r.bottom = 400;
	MapDialogRect(&r);
	SetWindowPos(0, 0, 0, r.right, r.bottom, SWP_NOZORDER | SWP_NOMOVE);

	((CButton*)GetDlgItem(IDC_CHECK_SEPARATOR))->SetCheck(pC->WithSeparators);
    ((CButton*)GetDlgItem(IDC_CHECK_SEPARATOR2))->SetCheck(pC->WithSeparators);
    ((CComboBox*)GetDlgItem(IDC_EDIT_BRICK))->SetWindowText("6");  
    ((CComboBox*)GetDlgItem(IDC_EDIT_SOURCE3))->SetWindowText("1");  
    ((CComboBox*)GetDlgItem(IDC_EDIT_SCANNED3))->SetWindowText("2"); 
    ((CComboBox*)GetDlgItem(IDC_EDIT_NUMEM))->SetWindowText("57"); 
 //   ((CButton*)GetDlgItem(IDC_INITIALIZE2))->SetColor(5);
//	if(pC->NumberOfBanks<4) ((CComboBox*)GetDlgItem(IDC_BANK4))->ShowWindow(SW_HIDE);
//	if(pC->NumberOfBanks<3) ((CComboBox*)GetDlgItem(IDC_BANK3))->ShowWindow(SW_HIDE);

    if(!OpenComPort(2)) AfxMessageBox("Can't open serial port!");
    


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CMonitor::IsManualControlEnabled()
{
	return false;
}

void CMonitor::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if (nID != SC_CLOSE) CDialog::OnSysCommand(nID, lParam);	
}

void CMonitor::OnButtonGoX()
{
	int pos;
	CString str;
	GetDlgItem(IDC_M_THPOS)->GetWindowText(str);
	pos=atoi(str);
	if(pos>=0 && pos<8) GoOnHAxis(pos,pC->PositionTimeout);
}
void CMonitor::OnButtonGoZ()
{
	int pos;
	CString str;
//	char mess[128];
	GetDlgItem(IDC_M_ZPOS)->GetWindowText(str);
	pos=atoi(str);

	if(pos>=0 && pos<8) GoOnVAxis(pos,pC->PositionTimeout);
}



void CMonitor::OnButtonRead() 
{
	
}

void CMonitor::OnUpdateMThpos() 
{
	// TODO: Add your control notification handler code here
	m_xpos = xpos;
	UpdateData(true);
	
}

void CMonitor::OnUpdateMZpos() 
{
	// TODO: Add your control notification handler code here
	m_zpos = zpos;
	UpdateData(true);
	
}




void CMonitor::OnUpdateEditSource() 
{
	// TODO: Add your control notification handler code here
	m_source = sourcebank;
	UpdateData(true);
	
}

void CMonitor::OnUpdateEditScanned() 
{
	// TODO: Add your control notification handler code here
	m_scanned = scannedbank;
	UpdateData(true);
}


void CMonitor::OnInitialize() 
{
	// TODO: Add your control notification handler code here
	int tme=0;
	int read;
	int bytesPerSamp;

    if(!PowerON(50)) {
		MessageBox("Can't turn drive power ON!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
		return;
	}
	if(GoOnVAxis(VPOS_UP,pC->PositionTimeout )<0)
	{
		MessageBox("Vertical drive position is not reached!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
//		OnReset();
		return;
	}
	if(GoOnHAxis(2,pC->PositionTimeout)<0)
	{
		MessageBox("Horizontal drive position is not reached!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
//		OnReset();
		return;
	}
	InitDone=true;
	GetDlgItem(IDC_LOAD)->EnableWindow();
    ReadyToScan=false;
    ReadStatusFile();
	if(EmulsionOnTable) TableVacuumControl(true,1,false);

   CString src,dest;
 //  MessageBox("Set proper source and destination bank numbers, then press OK", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
    GetDlgItem(IDC_EDIT_SOURCE3)->GetWindowText(src);  
    GetDlgItem(IDC_EDIT_SCANNED3)->GetWindowText(dest); 
	SourceBank=atoi(src);
	DestinationBank=atoi(dest);
	
}

int CMonitor::PowerON(int timeout)
{
	// Turns arm drives power ON.
//	StX=ST->X->GetPos();
//	StY=ST->Y->GetPos();
//	StZ=ST->Z->GetPos(); //save current stage positions
//	StageError=false;
	int tme=0;
	int res;
	char str[8];
	char rep[128];
   	str[0]='V';
	VacRegister= VacRegister | 0x10;
	str[1]=VacRegister;
	bool Reached=false;
	if(port.Write(str,2)!=2) return -tme;
		while( !Reached && tme<timeout)
	{
	  str[0]='Q';
	if(port.Write(str,1)!=1) return -tme;
	  port.Flush();
      Sleep(50);tme++;
	  port.Flush();
	  res=port.Read(rep,5);
//	  printf("res=%d rep[0]=%d  rep[1]=%d \n",res,rep[0],rep[1]);
	  if(res==0) continue;
	  if( rep[0]=='D' && (rep[1] & 0x08)) Reached=true;
	}
	if(tme>=timeout) return -tme;
	else return tme;

}

int CMonitor::PowerOFF(int timeout)
{
	// Turns arm drives power OFF.
	int tme=0;
	int res;
	char str[8];
	char rep[128];
   	str[0]='V';
	VacRegister = VacRegister & 0xEF;
	str[1]=VacRegister;
	bool Reached=false;
	if(port.Write(str,2)!=2) return -tme;
		while( !Reached && tme<timeout)
	{
	  str[0]='Q';
	if(port.Write(str,1)!=1) return -tme;
	  port.Flush();
      Sleep(50);tme++;
	  port.Flush();
	  res=port.Read(rep,5);
//	  printf("res=%d rep[0]=%d  rep[1]=%d \n",res,rep[0],rep[1]);
	  if(res==0) continue;
	  if(rep[0]=='D' && !(rep[1] & 0x08)) Reached=true;
	}
	if(tme>=timeout) return -tme;
	else return tme;

}

int CMonitor::ArmVacuumControl(bool VacOn, int timeout)
{
	// Switches the vacuum on/off at arm holder, if vacuum is not reached within given timeout returns -timeout,
	// otherwise returns actual time spent to reach vacuum
	int tme=0;
	int res;
	char str[8];
	char rep[128];
   	str[0]='V';
	if(VacOn) VacRegister= VacRegister | 0x01; else VacRegister = VacRegister & 0xFE;
	str[1]=VacRegister;
	bool Reached=false;
	if(port.Write(str,2)!=2) return -tme;
		while( !Reached && tme<timeout)
	{
	  str[0]='Q';
	if(port.Write(str,1)!=1) return -tme;
	  port.Flush();
       Sleep(50);tme++;
	  port.Flush();
	  res=port.Read(rep,5);
//	  printf("res=%d rep[0]=%d  rep[4]=%d \n",res,rep[0],rep[4]);
//	  port->CleanAll();
	  if(res==0) continue;
	 // if(res==5 && rep[0]=='D' && (rep[4] & 0x01)) Reached=true;
	  if(rep[0]=='D' && (rep[4] & 0x01)) Reached=true;
	}
	if(tme>=timeout) return -tme;
	else return tme;

}

int CMonitor::TableVacuumControl(bool VacOn, int timeout, bool PressureOn)
{
	// Switches the vacuum on/off at the table, if vacuum is not reached within given timeout returns -timeout,
	// otherwise returns actual time spent to reach vacuum
	if(VacOn) PressureOn=false;
	int tme=0;
	int res;
	char str[8];
	char rep[128];
	str[0]='V';
	if(VacOn) VacRegister= VacRegister | 0x02; else VacRegister = VacRegister & 0xFD;
	if(PressureOn) VacRegister= VacRegister | 0x04; else VacRegister = VacRegister & 0xFB;
	str[1]=VacRegister;
	bool Reached=false;
	if(port.Write(str,2)!=2) return -tme;
		while( !Reached && tme<timeout)
	{
	  str[0]='Q';
	if(port.Write(str,1)!=1) return -tme;
	  port.Flush();
       Sleep(50);tme++;
	  port.Flush();
	  res=port.Read(rep,5);
//	  printf("res=%d rep[0]=%d  rep[1]=%d \n",res,rep[0],rep[1]);
	  if(res==0) continue;
	  if(rep[0]=='D' && (rep[4] & 0x02)) Reached=true;
	}
	if(tme>=timeout) return -tme;
	else return tme;

}

int  CMonitor::GoOnHAxis(int bank, int timeout)
{
	// Moves arm horisontally to position <position>, if  not reached within given timeout returns -timeout,
	// otherwise returns actual time spent to reach position
	// ************ WARNING!!!!!!!  This low level function is not mechanically safe!! 
	// ************                 It may damage the plate changer
	// ************                 if used without caution to set the arm into UPMOST POSITION!

	int tme=0;
	int res;
	char str[8];
	char rep[128];
//	printf("GoOnHAxis(%d, %d) called.\n",position,timeout);
	str[0]='X';
	str[1]=bank & 0x07;
	bool Reached=false;
	if(port.Write(str,2)!=2) return -tme;
		while( !Reached && tme<timeout)
	{
	  str[0]='Q';
	if(port.Write(str,1)!=1) return -tme;
	  port.Flush();
       Sleep(50);tme++;
	  port.Flush();
	  res=port.Read(rep,5);
//	  printf("res=%h rep[0]=%h  rep[1]=%d \n",res,rep[0],rep[1]);
	  if(res==0) continue;
	  if(rep[0]=='D' && (rep[1] & 0x40) && (rep[1] & 0x10) && !(rep[1] & 0x80) && !(rep[1] & 0x20)) Reached=true;
	}
	if(tme>=timeout) return -tme;
	else return tme;

}
int  CMonitor::GoOnVAxis(int bank, int timeout)
{
	// Moves arm vertically to position <position>, if  not reached within given timeout returns -timeout,
	// otherwise returns actual time spent to reach position
	int tme=0;
	int res;
	char str[8];
	char rep[128];
	printf("GoOnVAxis(%d, %d) called.\n",position,timeout);
	str[0]='Y';
	str[1]=bank & 0x07;
	bool Reached=false;
	if(port.Write(str,2)!=2) return -tme;
		while( !Reached && tme<timeout)
	{
	  str[0]='Q';
	if(port.Write(str,1)!=1) return -tme;
	  port.Flush();
       Sleep(50);tme++;
	  port.Flush();
	  res=port.Read(rep,5);
	  if(res==0) continue;
	  printf("res=%d rep[0]=%h  rep[2]=%h \n",res,rep[0],rep[2]);
	  if(rep[0]=='D' && (rep[2] & 0x40) && (rep[2] & 0x10) && !(rep[2] & 0x80) && !(rep[2] & 0x20)) Reached=true;
	}
	if(tme>=timeout) return -tme;
	else return tme;


}
void CMonitor::OnButtonVacon() 
{
	// TODO: Add your control notification handler code here
if(ArmVacuumControl(true,pC->VacuumTimeout)<0)

	{
		MessageBox("ArmVacuum is not reached in 1 second!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
		return;
	}

	
}

void CMonitor::OnButtonVacoff() 
{
ArmVacuumControl(false,1);
	
}

void CMonitor::OnUnload() 
{
int isrc,idest;
CString src,dest;
    ReadyToScan=false;

    GetDlgItem(IDC_EDIT_SOURCE2)->GetWindowText(src);  
    GetDlgItem(IDC_EDIT_SCANNED2)->GetWindowText(dest); 
	isrc=atoi(src);
	idest=atoi(dest);
//	WaitForSingleObject(*pHMonitorMutex, INFINITE);
    EmulsionOnTable=NULL; 
	
    if(MoveEmulsion(0,idest)!=1)  return;
//	ReleaseMutex(*pHMonitorMutex);	

	GetDlgItem(IDC_LOAD)->EnableWindow();
	GetDlgItem(IDC_UNLOAD)->EnableWindow(false);
	GetDlgItem(IDC_CHGPLT)->EnableWindow(false);
	GetDlgItem(IDC_CHGPLT2)->EnableWindow(false);
		
}
void CMonitor::OnLoad() 
{
int isrc,idest;
CString src,dest;
    ReadyToScan=false;

    GetDlgItem(IDC_EDIT_SOURCE2)->GetWindowText(src);  
    GetDlgItem(IDC_EDIT_SCANNED2)->GetWindowText(dest); 
	isrc=atoi(src);
	idest=atoi(dest);
	if((isrc<0) || (isrc>3)) {MessageBox("Wrong Source Position assignement!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return;}
	if((idest<0) || (idest>3)) {MessageBox("Wrong Scanned Position assignement!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return;}
	if(isrc==idest) {MessageBox("Same Source and Scanned Position assignement!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return;}

//	WaitForSingleObject(*pHMonitorMutex, INFINITE);
 
    if(MoveEmulsion(isrc,0)!=1)  return;
 
	EmulsionOnTable=new TPlate;
	Park(idest);

//	ReleaseMutex(*pHMonitorMutex);	

	GetDlgItem(IDC_UNLOAD)->EnableWindow();
	GetDlgItem(IDC_LOAD)->EnableWindow(false);
	GetDlgItem(IDC_CHGPLT)->EnableWindow();
	GetDlgItem(IDC_CHGPLT2)->EnableWindow();
	
}
int CMonitor::Park(int idest)
{
	int res;
	if((idest<0) || (idest>3)) {MessageBox("Wrong Scanned Position assignement!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
	res=GoOnVAxis(VPOS_UP,pC->PositionTimeout); 
	if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
	res=GoOnHAxis(idest,pC->PositionTimeout);
	if(res<0) {MessageBox("Hpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
	return 1;
}

int CMonitor::MoveEmulsion(int isrc, int idest)
{
	int res,attempt=0;
	int cornpos;
	if((isrc<0) || (isrc>3)) {MessageBox("Wring Source Position assignement!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
	if((idest<0) || (idest>3)) {MessageBox("Wring Scanned Position assignement!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
	if(isrc==idest) {MessageBox("Same Source and Scanned Position assignement!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
pC->LiftCorners=false; //I.Kreslo temporary for new arm - to remove after scanback finished... This must be set in config!	
    if(isrc==0) { 
        if(!pC->LiftCorners) {
			res=GoOnHAxis(isrc,pC->PositionTimeout);
			if(res<0) {MessageBox("Hpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
			res=GoOnVAxis(VPOS_DOWN_TO_STAGE,pC->PositionTimeout); 
		    if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
			TableVacuumControl(false,1,true);
			res=ArmVacuumControl(true,pC->VacuumTimeout);
			if(res<0) {MessageBox("ArmVacuum is not reached in 2 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);}
			if(res<0) { GoOnVAxis(VPOS_UP,pC->PositionTimeout); return -1;} //error
		}
		TableVacuumControl(false,1, true);
		Sleep(100);
		attempt=0;
		while(attempt<pC->NumberOfAttempt){
		 attempt++;
         if((!pC->LiftCorners) || (attempt>1)) {
			 res=GoOnVAxis(VPOS_ABOVE_STAGE,2*pC->PositionTimeout); 
		     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
//		     res=GoOnVAxis(VPOS_UP,pC->PositionTimeout); 
		     res=ArmVacuumControl(true,pC->VacuumTimeout);
	     	 TableVacuumControl(false,1,true);
		     if(res>=0) break; //The emulsion is taken succesfully
		 }
//if not: try to lift up corners
         res=ArmVacuumControl(false,1); // leave emulsion
//		 if((attempt/2.)==int(attempt/2.)) cornpos=4; else cornpos=5; //try to lift the corner = pos #4 or #5
		 cornpos=4; //try to lift the corner = pos #4 or #5
		 res=GoOnHAxis(cornpos,pC->PositionTimeout); //try to lift the corner = pos #4 or #5
	     if(res<0) {MessageBox("Hpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
		 res=GoOnVAxis(VPOS_DOWN_TO_STAGE,pC->PositionTimeout);
	     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
         res=ArmVacuumControl(true,pC->VacuumTimeout); //vacuum ON
		 res=GoOnVAxis(VPOS_ABOVE_STAGE,2*pC->PositionTimeout); //lift the corner
	     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}

		 res=GoOnVAxis(VPOS_DOWN_TO_STAGE,pC->PositionTimeout); //back down
	     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
         res=ArmVacuumControl(false,1); //Vacuum OFF
		 res=GoOnVAxis(VPOS_UP,pC->PositionTimeout); // Go UP
	     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}

		  cornpos=5; //try to lift the corner = pos #4 or #5
		 res=GoOnHAxis(cornpos,pC->PositionTimeout); //try to lift the corner = pos #4 or #5
	     if(res<0) {MessageBox("Hpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
		 res=GoOnVAxis(VPOS_DOWN_TO_STAGE,pC->PositionTimeout);
	     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
         res=ArmVacuumControl(true,pC->VacuumTimeout); //vacuum ON
		 res=GoOnVAxis(VPOS_ABOVE_STAGE,2*pC->PositionTimeout); //lift the corner
	     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}

		 res=GoOnVAxis(VPOS_DOWN_TO_STAGE,pC->PositionTimeout); //back down
	     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
         res=ArmVacuumControl(false,1); //Vacuum OFF
		 res=GoOnVAxis(VPOS_UP,pC->PositionTimeout); // Go UP
	     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
         res=ArmVacuumControl(true,pC->VacuumTimeout); //Vacuum ON


		 res=GoOnHAxis(isrc,pC->PositionTimeout); //go back to 0 position
	     if(res<0) {MessageBox("Hpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
//         res=ArmVacuumControl(true,pC->VacuumTimeout); //Vacuum ON
		 res=GoOnVAxis(VPOS_DOWN_TO_STAGE,pC->PositionTimeout); //and DOWN again, ready for the next attempt
	     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
         res=ArmVacuumControl(true,pC->VacuumTimeout); //Vacuum ON
		}

		if(attempt==pC->NumberOfAttempt) {
			ArmVacuumControl(false,1);
	     	TableVacuumControl(false,1,false);
			GoOnVAxis(VPOS_UP,pC->PositionTimeout); 
			MessageBox("Robot can't take plate from the stage!", "Plate Changer Error", MB_ICONEXCLAMATION|MB_OK);
			return -1;}
	}
	else { //taking from the bank - perform attempts to separate top emulsion from the rest
	res=GoOnHAxis(isrc,pC->PositionTimeout);
	MessageBox("Point1", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
	if(res<0) {MessageBox("Hpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
	if(isrc==0) res=GoOnVAxis(VPOS_DOWN_TO_STAGE,pC->PositionTimeout); else res=GoOnVAxis(VPOS_DOWN,pC->PositionTimeout);
	MessageBox("Point2", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
    if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
	if(isrc==0) TableVacuumControl(false,1);
	MessageBox("Point3", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
	res=ArmVacuumControl(true,pC->VacuumTimeout);
	MessageBox("Point4", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
	if(res<0) {MessageBox("ArmVacuum is not reached in 2 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);}
	if(res<0) { GoOnVAxis(VPOS_UP,pC->PositionTimeout); return -2;} //no more emulsion in the bank
	MessageBox("Point5", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
		for(int att=0;att<pC->SeparationAttempts;att++){
		 res=GoOnVAxis(VPOS_UP,pC->PositionTimeout); // Go UP
	MessageBox("Pointloop1", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
	     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
		 res=GoOnVAxis(VPOS_DOWN_TO_STAGE,pC->PositionTimeout); //back down
	MessageBox("Pointloop2", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
	     if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
		}
	}
	MessageBox("PointOutOfLoop", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);

	res=GoOnVAxis(VPOS_UP,pC->PositionTimeout); 
	if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
	res=GoOnHAxis(idest,pC->PositionTimeout);
	if(res<0) {MessageBox("Hpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
	if(idest==0) res=GoOnVAxis(VPOS_DOWN_TO_STAGE,pC->PositionTimeout); else res=GoOnVAxis(VPOS_DOWN,pC->PositionTimeout);
	if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
	res=ArmVacuumControl(false,1);
	if(idest==0) {
		res=TableVacuumControl(true,200);
        if(res<0) {MessageBox("TableVacuum is not reached in 20 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);}
		}
	res=GoOnVAxis(VPOS_UP,pC->PositionTimeout);
	if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return -1;}
	return 1;

}

void CMonitor::OnChgplt() 
{
bool WithSeparator;
    WithSeparator=((CButton*)GetDlgItem(IDC_CHECK_SEPARATOR))->GetCheck();
OnUnload();
if(WithSeparator) OnMvsep();
OnLoad();
    ReadyToScan=false;
	
}

void CMonitor::OnMvsep() 
{
int isrc,idest;
CString src,dest;
    ReadyToScan=false;

    GetDlgItem(IDC_EDIT_SOURCE2)->GetWindowText(src);  
    GetDlgItem(IDC_EDIT_SCANNED2)->GetWindowText(dest); 
	isrc=atoi(src);
	idest=atoi(dest);
//	WaitForSingleObject(*pHMonitorMutex, INFINITE);
 

 	if(MoveEmulsion(isrc,idest)!=1) {  return;};
//	ReleaseMutex(*pHMonitorMutex);
}

void CMonitor::OnChgplt2() 
{
    ReadyToScan=false;
for(int nc=0;nc<10;nc++)
	{
	 OnChgplt();
	 Sleep(1000);
	}

}

void CMonitor::OnButtonVacoff2() 
{
TableVacuumControl(false,1);
	// TODO: Add your control notification handler code here
	
}

void CMonitor::OnButtonVacon2() 
{
if(TableVacuumControl(true,pC->VacuumTimeout)<0)

	{
		MessageBox("TableVacuum is not reached in 1 second!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
		return;
	}

	// TODO: Add your control notification handler code here
	
}

void CMonitor::OnSort() 
{
int res;
return;
    ReadyToScan=false;

if(!InitDone) OnInitialize();
if(TableVacuumControl(true,pC->VacuumTimeout)<0) {     EmulsionOnTable=new TPlate; }
for(int bnk=1; bnk<pC->NumberOfBanks+1;bnk++)
{ 
 	res=TableVacuumControl(true,pC->VacuumTimeout);
	if(res<0) {
		Bank[0].NEmulsions=0;
		Bank[0].NSeparators=0;
	}
	else {
		Bank[0].NEmulsions=MAX_NUMBER_OF_PLATES+1;
		Bank[0].NSeparators=MAX_NUMBER_OF_PLATES+1; //bank is full, but number is undefined
	}
 	TableVacuumControl(false,1);
	res=GoOnVAxis(VPOS_UP,pC->PositionTimeout);
    if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return;}
	res=GoOnHAxis(bnk,pC->PositionTimeout);
	if(res<0) {MessageBox("Hpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return;}
	res=GoOnVAxis(VPOS_DOWN,pC->PositionTimeout);
    if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return;}
	res=ArmVacuumControl(true,pC->VacuumTimeout);
	if(res<0) {
		Bank[bnk].NEmulsions=0;
		Bank[bnk].NSeparators=0;
	}
	else {
		Bank[bnk].NEmulsions=MAX_NUMBER_OF_PLATES+1;
		Bank[bnk].NSeparators=MAX_NUMBER_OF_PLATES+1; //bank is full, but number is undefined
	}
	ArmVacuumControl(false,1);
	res=GoOnVAxis(VPOS_UP,pC->PositionTimeout);
    if(res<0) {MessageBox("Vpos is not reached in 5 seconds!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);return;}
}

UpdateBanksView();

int EmptyBankNumber=-1;
int LastFullBankNumber=-1;
 for(bnk=1; bnk<pC->NumberOfBanks+1;bnk++){
  if(Bank[bnk].NEmulsions==0 && Bank[bnk].NSeparators==0) EmptyBankNumber=bnk;
  if(Bank[bnk].NEmulsions>0 || Bank[bnk].NSeparators>0) LastFullBankNumber=bnk;
 }

//Now sort emulsions using one empty bank
//If two banks are full and there is an emulsion on the table then in both banks top is the separator
//otherwize just move all from one to another.

}


void CMonitor::UpdateBanksView()
{
   CString str1,str2,strem,strsep,plidstr;
//   int i;
   str1.Format(_T("Empty"));
   str2.Format(_T("Not Empty"));
   strem.Format(_T("Emulsion "));
   strsep.Format(_T("Separator"));
// UpdateData(true);
 /*
  for(i=0;i<1000;i++) m_BANK0.DeleteString(0);
 if(Bank[0].NEmulsions==0) m_BANK0.InsertString(-1, str1 );
 else if(Bank[0].NEmulsions>MAX_NUMBER_OF_PLATES ) m_BANK0.InsertString(-1,  str2 );
 else for(i=0;i<Bank[0].NEmulsions;i++)  {
    strem.Format(_T("Emulsion %d"),i+1);
	m_BANK0.InsertString(-1,  strem );
    if(((CButton*)GetDlgItem(IDC_CHECK_SEPARATOR))->GetCheck())	m_BANK0.InsertString(-1,  strsep );
 }
 m_BANK0.SetCurSel(0);
*/

UpdateBankView(0,&m_BANK0);
UpdateBankView(1,&m_BANK1);
UpdateBankView(2,&m_BANK2);
if(pC->NumberOfBanks>2)  UpdateBankView(3,&m_BANK3);
if(pC->NumberOfBanks>3)  UpdateBankView(4,&m_BANK4);
 if(Bank[0].NEmulsions>0){
	plidstr.Format(_T("%d"),Bank[0].Plates[0]->id.Part[0]);
    ((CEdit*)GetDlgItem(IDC_EDIT_PLID0))->SetWindowText(plidstr);
	plidstr.Format(_T("%d"),Bank[0].Plates[0]->id.Part[1]);
    ((CEdit*)GetDlgItem(IDC_EDIT_PLID1))->SetWindowText(plidstr);
	plidstr.Format(_T("%d"),Bank[0].Plates[0]->id.Part[2]);
    ((CEdit*)GetDlgItem(IDC_EDIT_PLID2))->SetWindowText(plidstr);
	plidstr.Format(_T("%d"),Bank[0].Plates[0]->id.Part[3]);
    ((CEdit*)GetDlgItem(IDC_EDIT_PLID3))->SetWindowText(plidstr);
 }
 else{
	plidstr.Format(_T(" "));
    ((CEdit*)GetDlgItem(IDC_EDIT_PLID0))->SetWindowText(plidstr);
    ((CEdit*)GetDlgItem(IDC_EDIT_PLID1))->SetWindowText(plidstr);
    ((CEdit*)GetDlgItem(IDC_EDIT_PLID2))->SetWindowText(plidstr);
    ((CEdit*)GetDlgItem(IDC_EDIT_PLID3))->SetWindowText(plidstr);
 }
// UpdateData(false);
 UpdateStatusFile();


}


void CMonitor::OnCheckSeparator() 
{
	// TODO: Add your control notification handler code here
  m_Separator2.SetCheck(m_Separator.GetCheck());	
}

void CMonitor::OnCheckSeparator2() 
{
	// TODO: Add your control notification handler code here
  m_Separator.SetCheck(m_Separator2.GetCheck());	
	
}

void CMonitor::OnChangeEditSource3() 
{
//	CString src;
//	GetDlgItem(IDC_EDIT_SOURCE3)->GetWindowText(src);
 //   GetDlgItem(IDC_EDIT_SOURCE)->SetWindowText(src);	
}

void CMonitor::OnLoadbank() 
{
int res,isrc,idest,inumem,ibrick;
CString src,dest,numem,brick;
MessageBox("Set proper source and destination bank numbers, then press OK", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
    GetDlgItem(IDC_EDIT_BRICK)->GetWindowText(brick);  
    GetDlgItem(IDC_EDIT_SOURCE3)->GetWindowText(src);  
    GetDlgItem(IDC_EDIT_SCANNED3)->GetWindowText(dest); 
    GetDlgItem(IDC_EDIT_NUMEM)->GetWindowText(numem); 
	ibrick=atoi(brick);
	isrc=atoi(src);
	idest=atoi(dest);
	inumem=atoi(numem);
	if(isrc<1 || isrc>3 || idest<1 || idest>3 || isrc==idest || inumem<=0) {
		MessageBox("Wrong bank assignements!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
        return;
	}
if(!InitDone) OnInitialize();
Park(idest);
if(!IsStageHomed) OnHomestage();
MessageBox("Load source bank, top sheet must be first emulsion, then press OK", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
res=TableVacuumControl(true,pC->VacuumTimeout); TableVacuumControl(false,1);
while(res>=0){
	MessageBox("Please remove emulsion from the stage, then press OK", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
    res=TableVacuumControl(true,pC->VacuumTimeout); TableVacuumControl(false,1);
}
for(int bnk=0; bnk<pC->NumberOfBanks+1;bnk++){ 
	Bank[bnk].NEmulsions=0;
	Bank[bnk].NSeparators=0;
	}
Bank[isrc].NEmulsions=inumem;	
if(    ((CButton*)GetDlgItem(IDC_CHECK_SEPARATOR))->GetCheck()    ) 
Bank[isrc].NSeparators=inumem;
SourceBank=isrc;
DestinationBank=idest;	
if(    ((CButton*)GetDlgItem(IDC_CHECK_SEPARATOR))->GetCheck()    ) 
for(int i=0;i<inumem;i++) {
  Bank[isrc].Plates[i*2]=new TPlate; //add plate
  Bank[isrc].Plates[i*2]->SeqNumber=i*2;
  Bank[isrc].Plates[i*2]->InBank=isrc;
  Bank[isrc].Plates[i*2]->IsSeparator=false;
  Bank[isrc].Plates[i*2]->id.Part[0]=ibrick;
  Bank[isrc].Plates[i*2]->id.Part[1]=i+1;
  Bank[isrc].Plates[i*2]->id.Part[2]=0;
  Bank[isrc].Plates[i*2]->id.Part[3]=0;

  Bank[isrc].Plates[i*2+1]=new TPlate; //add sep
  Bank[isrc].Plates[i*2+1]->SeqNumber=i*2+1;
  Bank[isrc].Plates[i*2+1]->InBank=isrc;
  Bank[isrc].Plates[i*2+1]->IsSeparator=true;
  Bank[isrc].Plates[i*2+1]->id.Part[0]=ibrick;
  Bank[isrc].Plates[i*2+1]->id.Part[1]=i+1;
  Bank[isrc].Plates[i*2+1]->id.Part[2]=0;
  Bank[isrc].Plates[i*2+1]->id.Part[3]=0;

}
else for(int i=0;i<inumem;i++) {
  Bank[isrc].Plates[i]=new TPlate; //add emulsion
  Bank[isrc].Plates[i]->SeqNumber=i;
  Bank[isrc].Plates[i]->InBank=isrc;
  Bank[isrc].Plates[i]->IsSeparator=false;
  Bank[isrc].Plates[i]->id.Part[0]=ibrick;
  Bank[isrc].Plates[i]->id.Part[1]=i+1;
  Bank[isrc].Plates[i]->id.Part[2]=0;
  Bank[isrc].Plates[i]->id.Part[3]=0;

}


ReadyToScan=true;

UpdateBanksView();

}


void CMonitor::OnDebuglevel() 
{
 DebugLevel++;	
 if(DebugLevel>2) DebugLevel=0;
 	RECT r;
	r.left = r.top = 0;
	r.right = 125+DebugLevel*120;
	r.bottom = 420;
	MapDialogRect(&r);
	SetWindowPos(0, 0, 0, r.right, r.bottom, SWP_NOZORDER | SWP_NOMOVE);

}

int CMonitor::LoadPlate(Identifier id)
{
SetStatus("LoadPlate is in progress...");
	int SeqN=-1,sn,BankN;
	int Mfrom, Mto;
	float X0,Y0,Z0;
	float Xex,Yex,Zex;
	float CHTol=50;
	float CVTol=10;
	float CHAcc=pC->AccX;
	float CVAcc=pC->AccZ;
	float CVSpeed=pC->SpeedZ;
	float CHSpeed=pC->SpeedX;
    Xex=-pC->LimOffsetX;
    Yex=-pC->LimOffsetY;
    Zex=-pC->LimOffsetZ;
 /*   if(pSt){ //remember position
		pSt->GetPos(0,&X0);
		pSt->GetPos(1,&Y0);
		pSt->GetPos(2,&Z0);
    OnHomestage(); 
	pSt->PosMove(0,Xex,CHSpeed,CHAcc); 
	pSt->PosMove(1,Yex,CHSpeed,CHAcc); 
	pSt->PosMove(2,Zex,CVSpeed,CVAcc); 
	//wait for motion complete
				WaitTillReached(0,Xex,CHSpeed,CHTol);
				WaitTillReached(1,Yex,CHSpeed,CHTol);
				WaitTillReached(2,Zex,CVSpeed,CVTol);
	}
	else MessageBox("No connection with the stage!!! Move it manually to plate change position.", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
*/
	if(FindEmulsion(id,0)>=0) {SetStatus("Load Plate is complete (plate was already on the stage)."); return 2; }//Already loaded
	for(int bnk=1; bnk<pC->NumberOfBanks+1;bnk++) {
	  sn=FindEmulsion(id,bnk);
	  if(sn>=0){ SeqN=sn; BankN=bnk; break;}
	}
	if(SeqN<0) {SetStatus("Load Plate is failed. Emulsion is not found anywhere!"); return -1; }//Emulsion is not found anywhere
    // Emulsion is in bank  BankN at the position SeqN, SeqN=0 means at the top
    //Now put it onto the table
//	WaitForSingleObject(*pHMonitorMutex, INFINITE);
    if(pSt){ //Move stage to 0,0,0
		pSt->GetPos(0,&X0);
		pSt->GetPos(1,&Y0);
		pSt->GetPos(2,&Z0);
	pSt->PosMove(0,Xex,CHSpeed,CHAcc); 
	pSt->PosMove(1,Yex,CHSpeed,CHAcc); 
	pSt->PosMove(2,Zex,CVSpeed,CVAcc); 
	//wait for motion complete


	}
	else MessageBox("No connection with the stage!!! Move it manually to plate change position.", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
    if(BankN==SourceBank) { Mfrom=BankN; Mto=DestinationBank;} 
	else                 { Mto=SourceBank; Mfrom=BankN;} 
	if(EmulsionOnTable!=NULL) {
		TakeFromBank(0);
//       if(pSt) pSt->WaitForAsyncMotionComplete((DWORD)MyShouldStopCallback, (DWORD)this);
		if(pSt) {
				WaitTillReached(0,Xex,CHSpeed,CHTol);
				WaitTillReached(1,Yex,CHSpeed,CHTol);
				WaitTillReached(2,Zex,CVSpeed,CVTol);
		}
	//	WaitForSingleObject(*pHMonitorMutex, INFINITE);
		if(MoveEmulsion(0,Mto)!=1) {  return -1;};

//		ReleaseMutex(*pHMonitorMutex);
		AddToBank(Mto,EmulsionOnTable);

	}
	for(int num=0;num<SeqN;num++){ //move from one bank to another all unnecessary plates
		AddToBank(Mto,TakeFromBank(Mfrom));
//		WaitForSingleObject(*pHMonitorMutex, INFINITE);
		if(MoveEmulsion(Mfrom,Mto)!=1) {  return -1;};
//		ReleaseMutex(*pHMonitorMutex);
	}
//	ReleaseMutex(*pHMonitorMutex);

	//Now top in Mfrom bank must be emulsion that we search for
	if(FindEmulsion(id,Mfrom)!=0) {
		MessageBox("Brick structure incosistent!!! Reload the brick!", "Plate Changer Error", MB_ICONEXCLAMATION|MB_OK);
		return -1; //Inconsistency!!!!!
	}
 //	WaitForSingleObject(*pHMonitorMutex, INFINITE);
//    if(pSt) pSt->WaitForAsyncMotionComplete((DWORD)MyShouldStopCallback, (DWORD)this);
	if(pSt) {
				WaitTillReached(0,Xex,CHSpeed,CHTol);
				WaitTillReached(1,Yex,CHSpeed,CHTol);
				WaitTillReached(2,Zex,CVSpeed,CVTol);
	}

//    StageHoming(pC->LimOffsetX,pC->LimOffsetY,pC->LimOffsetZ,0,0,0);
/*    OnHomestage(); 
	pSt->PosMove(0,Xex,CHSpeed,CHAcc); 
	pSt->PosMove(1,Yex,CHSpeed,CHAcc); 
	pSt->PosMove(2,Zex,CVSpeed,CVAcc); 
	//wait for motion complete
	if(pSt) {
				WaitTillReached(0,Xex,CHSpeed,CHTol);
				WaitTillReached(1,Yex,CHSpeed,CHTol);
				WaitTillReached(2,Zex,CVSpeed,CVTol);
	}
*/
//	WaitForSingleObject(*pHMonitorMutex, INFINITE);
	if(MoveEmulsion(Mfrom,0)!=1) {  return -1;};
//	ReleaseMutex(*pHMonitorMutex);
	EmulsionOnTable=TakeFromBank(Mfrom); //if movement is OK update database
    AddToBank(0,EmulsionOnTable);
//	ReleaseMutex(*pHMonitorMutex);
	Park(Mfrom);
/*
    if(pSt){ //Move stage back
	X0=pC->FMOffsetX; // Put where 1st FM is expected
	Y0=pC->FMOffsetY; //

	pSt->PosMove(0,X0,CHSpeed,CHAcc);
	pSt->PosMove(1,Y0,CHSpeed,CHAcc); 
	pSt->PosMove(2,Z0,CVSpeed,CVAcc); 
	//wait for motion complete

	WaitTillReached(0,X0,CHSpeed,CHTol);
	WaitTillReached(1,Y0,CHSpeed,CHTol);
	WaitTillReached(2,Z0,CVSpeed,CVTol);
	}
	else MessageBox("No connection with the stage!!! Move it manually to scan position.", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
*/ 
	SetStatus("Load Plate is complete.");
	return 1;
}

int CMonitor::UnloadPlate()
{
SetStatus("Unload plate is in progress...");
	float X0,Y0,Z0;
	float CHTol=50;
	float CVTol=10;
	float CHAcc=pC->AccX;
	float CVAcc=pC->AccZ;
	float CVSpeed=pC->SpeedZ;
	float CHSpeed=pC->SpeedX;
    int isrc,idest;
	float Xex,Yex,Zex;
//	float X0,Y0,Z0;
    Xex=-pC->LimOffsetX;
    Yex=-pC->LimOffsetY;
    Zex=-pC->LimOffsetZ;
CString src,dest;
 UpdateData(true);
 EmulsionOnTable=TakeFromBank(0);
 if(!EmulsionOnTable) return S_OK;

    GetDlgItem(IDC_EDIT_SOURCE3)->GetWindowText(src);  
    GetDlgItem(IDC_EDIT_SCANNED3)->GetWindowText(dest); 
	isrc=atoi(src);
	idest=atoi(dest);
	if(isrc<1 || isrc>3 || idest<1 || idest>3 || isrc==idest) {
		MessageBox("Wrong bank assignements!", "Plate Changer Warning", MB_ICONEXCLAMATION|MB_OK);
		SetStatus("Unload Plate is failed.");
        return -1;
	}
//All is ok, now move plate to src bank
//WaitForSingleObject(*pHMonitorMutex, INFINITE);
    if(pSt){ //Move stage to 0,0,0
		pSt->GetPos(0,&X0);
		pSt->GetPos(1,&Y0);
		pSt->GetPos(2,&Z0);
	pSt->PosMove(0,Xex,CHSpeed,CHAcc); 
	pSt->PosMove(1,Yex,CHSpeed,CHAcc); 
	pSt->PosMove(2,Zex,CVSpeed,CVAcc); 
	//wait for motion complete

	WaitTillReached(0,Xex,CHSpeed,CHTol);
	WaitTillReached(1,Yex,CHSpeed,CHTol);
	WaitTillReached(2,Zex,CVSpeed,CVTol);

	}
//UpdateBanksView();

//	WaitForSingleObject(*pHMonitorMutex, INFINITE);

	AddToBank(isrc,EmulsionOnTable);
	EmulsionOnTable=NULL;

	if(MoveEmulsion(0,isrc)!=1) {	SetStatus("Unload Plate is failed. ");   return -1;};
//    ReleaseMutex(*pHMonitorMutex);	//And update bank records
//UpdateBanksView();
//ReleaseMutex(*pHMonitorMutex);

SetStatus("Unload Plate is complete.");
return S_OK;

}

int CMonitor::FindEmulsion(Identifier id, int bnk) //find emulsion in bank bnk
{
    for(int i=0;i<Bank[bnk].NEmulsions+Bank[bnk].NSeparators;i++) {
	 if(Bank[bnk].Plates[i]->IsSeparator==false)
	 if(Bank[bnk].Plates[i]->id.Part[0]==id.Part[0])
	 if(Bank[bnk].Plates[i]->id.Part[1]==id.Part[1])
	 if(Bank[bnk].Plates[i]->id.Part[2]==id.Part[2])
	 if(Bank[bnk].Plates[i]->id.Part[3]==id.Part[3])
		 return i;
	}

 return -1;
}

void CMonitor::AddToBank(int bnk, TPlate *plate)
{
    for(int i=Bank[bnk].NEmulsions+Bank[bnk].NSeparators;i>0;i--) {
		Bank[bnk].Plates[i]=Bank[bnk].Plates[i-1];
	}
 plate->InBank=bnk;
 plate->SeqNumber=0;
 Bank[bnk].Plates[0]=plate;
 if(plate->IsSeparator) Bank[bnk].NSeparators++;
 else Bank[bnk].NEmulsions++;
 UpdateBanksView();
}


TPlate* CMonitor::TakeFromBank(int bnk)
{
 TPlate* retvalue;
 if(Bank[bnk].NEmulsions+Bank[bnk].NSeparators<=0) return NULL;
 retvalue=Bank[bnk].Plates[0];
     for(int i=0;i<Bank[bnk].NEmulsions+Bank[bnk].NSeparators-1;i++) {
		Bank[bnk].Plates[i]=Bank[bnk].Plates[i+1];

	}
 if(retvalue->IsSeparator) Bank[bnk].NSeparators--;
 else Bank[bnk].NEmulsions--;
 //UpdateBanksView();

 retvalue->InBank=-1; //unknown
 return retvalue;
}

void CMonitor::OnLoademid() 
{
Identifier id;
CString str;
if(!IsStageHomed) { 
	MessageBox("Stage is not homed! Can't load emulsion.", "Plate Changer Info", MB_ICONEXCLAMATION|MB_OK);
    return;
}
GetDlgItem(IDC_EDIT_PLID4)->GetWindowText(str); id.Part[0]=atoi(str);	
GetDlgItem(IDC_EDIT_PLID5)->GetWindowText(str); id.Part[1]=atoi(str);	
GetDlgItem(IDC_EDIT_PLID6)->GetWindowText(str); id.Part[2]=atoi(str);	
GetDlgItem(IDC_EDIT_PLID7)->GetWindowText(str); id.Part[3]=atoi(str);
str.Format("Ready to load plate %d.%d.%d.%d",id.Part[0],id.Part[1],id.Part[2],id.Part[3]);
MessageBox(str, "Plate Changer Info", MB_ICONEXCLAMATION|MB_OK);
if(LoadPlate(id)>0) str.Format("Plate %d.%d.%d.%d is on the stage.",id.Part[0],id.Part[1],id.Part[2],id.Part[3]);
else str.Format("Loading of Plate %d.%d.%d.%d is failed..",id.Part[0],id.Part[1],id.Part[2],id.Part[3]);
MessageBox(str, "Plate Changer Info", MB_ICONEXCLAMATION|MB_OK);
UpdateBanksView();

}

void CMonitor::UpdateBankView(int bnk, CComboBox *Control)
{
 CString str;
 for(int i=0;i<1000;i++) Control->DeleteString(0);
 if(Bank[bnk].NEmulsions==0) { str.Format(_T("Empty")); Control->InsertString(-1,  str );}
 else if(Bank[bnk].NEmulsions>MAX_NUMBER_OF_PLATES ) { str.Format(_T("Not empty")); Control->InsertString(-1,  str );}
 else for(i=0;i<Bank[bnk].NEmulsions+Bank[bnk].NSeparators;i++)  {
    if(Bank[bnk].Plates[i]->IsSeparator) str.Format(_T("Separator"));
	else str.Format(_T("Emulsion %d"),Bank[bnk].Plates[i]->id.Part[1]);
	Control->InsertString(-1,  str );
 }
Control->SetCurSel(0);

}

void CMonitor::OnUnloadem() 
{
	CString str;
if(!IsStageHomed) { 
	MessageBox("Stage is not homed! Can't unload emulsion.", "Plate Changer Info", MB_ICONEXCLAMATION|MB_OK);
    return;
}
	if(UnloadPlate()!=S_OK) {
		str.Format("UnLoading of plate is failed..");
        MessageBox(str, "Plate Changer Info", MB_ICONEXCLAMATION|MB_OK);
	};	
UpdateBanksView();
}

bool CMonitor::MyShouldStopCallback(DWORD Context)
{
	return false;
}

bool CMonitor::StageHoming(int dirX, int dirY, int dirZ,  float HomeX, float HomeY, float HomeZ)
{
 SetStatus("Stage homing is in progress...");
	float CHTol=50;
	float CVTol=5;
	float CHAcc=pC->AccX;
	float CVAcc=pC->AccZ;
	float CVSpeed=pC->SpeedZ;
	float CHSpeed=pC->SpeedX;
    float dx,dy,dz,z0;
	int limx,limy,limz;
	if(!pSt) { SetStatus("Stage homing is failed: no pointer to stage!"); return false;}
	pSt->GetLimiter(0,&limx); pSt->GetLimiter(1,&limy); pSt->GetLimiter(2,&limz);
	//Move the head up by 2mm to avoid collision
    pSt->GetPos(2,&z0);
    pSt->PosMove(2,z0+2000.0,CVSpeed,CVAcc);

	//********************X-Y HOMING
	//Prepare to fast move to limiters
	dx=(float)dirX;
	dy=(float)dirY;
	dx=dx/fabs(dx)*CHSpeed;
	dy=dy/fabs(dy)*CHSpeed;
   pSt->SpeedMove(0,dx,CHAcc);
   pSt->SpeedMove(1,dy,CHAcc);
   while(limx==0 || limy==0) {pSt->GetLimiter(0,&limx); pSt->GetLimiter(1,&limy); if(limx!=0) pSt->Stop(0); if(limy!=0) pSt->Stop(1);}
   pSt->Stop(0);
   pSt->Stop(1);
//   Sleep(100);//to stabilize
   pSt->Reset(0);
   pSt->Reset(1);
   //now slowly move back till limiters go off
	dx=(float)dirX;
	dy=(float)dirY;
	dx=-1*dx/fabs(dx)*10000.0;
	dy=-1*dy/fabs(dy)*10000.0;
	pSt->PosMove(0,dx,CHSpeed/100.0,CHAcc/100.); 
//	pSt->SpeedMove(0,CHSpeed/100.0,CHAcc/100.); 
	while(limx!=0){pSt->GetLimiter(0,&limx);}
   pSt->Stop(0);
	pSt->PosMove(1,dy,CHSpeed/100.0,CHAcc/100.); 
//	pSt->SpeedMove(1,CHSpeed/100.0,CHAcc/100.); 
	while(limy!=0){pSt->GetLimiter(1,&limy);}
   pSt->Stop(1);

    //now go again forward but slowly
	dx=(float)dirX;
	dy=(float)dirY;
	dx=dx/fabs(dx)*CHSpeed/200.;
	dy=dy/fabs(dy)*CHSpeed/200.;
   pSt->SpeedMove(0,dx,CHAcc/200.);
   while(limx==0) {pSt->GetLimiter(0,&limx);}
   pSt->Stop(0);
   pSt->SpeedMove(1,dy,CHAcc/200.);
   while(limy==0) {pSt->GetLimiter(1,&limy); }
   pSt->Stop(1);
   Sleep(100);//to stabilize
   pSt->Reset(0);
   pSt->Reset(1);
   //go to plate change position

	pSt->PosMove(0,-1*pC->LimOffsetX,CHSpeed,CHAcc); 
	pSt->PosMove(1,-1*pC->LimOffsetY,CHSpeed,CHAcc); 
	//wait for motion complete

	if(!WaitTillReached(0,-1*pC->LimOffsetX,CHSpeed,CHTol)){return false;};
	if(!WaitTillReached(1,-1*pC->LimOffsetY,CHSpeed,CHTol)){return false;};

    pSt->Stop(0);
    pSt->Stop(1);
//   Sleep(100);//to stabilize
	pSt->Reset(0);
    pSt->Reset(1);

	//********************Z HOMING
	//Prepare to fast move to limiters
	dz=(float)dirZ;
	dz=dz/fabs(dz)*CVSpeed;
   pSt->SpeedMove(2,dz,CVAcc);
   while(limz==0) {pSt->GetLimiter(2,&limz);}
   pSt->Stop(2);
   pSt->Reset(2);
   //now slowly move back till limiters go off
	dz=(float)dirZ;
	dz=-1*dz/fabs(dz)*10000.0;
 	pSt->PosMove(2,dz,CVSpeed/100.0,CVAcc/100.); 
	while(limz!=0){pSt->GetLimiter(2,&limz);}
    //now go again forward but slowly
	dz=(float)dirZ;
	dz=dz/fabs(dz)*CVSpeed/100.;
    pSt->SpeedMove(2,dz,CVAcc/100.);
   while( limz==0) { pSt->GetLimiter(2,&limz);}
   pSt->Stop(2);
   pSt->Reset(2);
   //go to plate change position

	pSt->PosMove(2,-1*pC->LimOffsetZ,CVSpeed,CVAcc); 
	//wait for motion complete

	if(!WaitTillReached(2,-1*pC->LimOffsetZ,CVSpeed,CVTol)){return false;};
    pSt->Stop(2);
    pSt->Reset(2);
IsStageHomed=true;
//DrawSemaphore(IDC_M_RDYRED2,IDC_M_RDYGREEN2,false);
 SetStatus("Stage homing is done.");
return true;
}

void CMonitor::OnHomestage() 
{
	IStage3 *iSt3;
	pSt->QueryInterface(IID_IStage3, (void **)&iSt3);
	iSt3->FindHome();
//StageHoming(pC->LimOffsetX,pC->LimOffsetY,pC->LimOffsetZ,0,0,0);	
IsStageHomed=true;
}

void CMonitor::SetStatus(char *statusline)
{
  GetDlgItem(IDC_EDIT_STATUSBOX)->SetWindowText(statusline);
//  GetDlgItem(IDC_EDIT_STATUSBOX)->Update();
}

int CMonitor::WaitTillReached(int Axis, float TargetPos, float Speed, float Tolerance)
{
	float TimeNeeded,NextTime;
	float CurPos;
	pSt->GetPos(Axis,&CurPos);
    TimeNeeded = 2.f * fabs((CurPos - TargetPos) / Tolerance);
    NextTime = 1000.0* TimeNeeded  + GetTickCount(); 

	//wait for motion complete
    while( (GetTickCount() <= NextTime) &&  (fabs(CurPos - TargetPos)>Tolerance) ) pSt->GetPos(Axis,&CurPos);  
    if(fabs(CurPos - TargetPos)>Tolerance) return 0; //exit on timeout
	return 1; //exit on position reached
}

void CMonitor::UpdateStatusFile()
{
         char dateStr [9];
          char timeStr [9];
          _strdate( dateStr);
         _strtime( timeStr );
		 FILE *fp=fopen("c:\\ChangerStatus.txt","w");
  FILE *fpl=fopen("c:\\ChangerLog.txt","a");
  fprintf(fp,"Plate Changer Status on %s at %s.\n",dateStr,timeStr);
  fprintf(fpl,"Plate Changer Status on %s at %s.\n",dateStr,timeStr);
  for(int bnk=0;bnk<pC->NumberOfBanks+1;bnk++){
    fprintf(fp,"Bank %d\n",bnk);
    fprintf(fpl,"Bank %d\n",bnk);
    fprintf(fp,"SEPARATORS %d\n",Bank[bnk].NSeparators);
    fprintf(fpl,"SEPARATORS %d\n",Bank[bnk].NSeparators);
    fprintf(fp,"PLATES %d\n",Bank[bnk].NEmulsions);
    fprintf(fpl,"PLATES %d\n",Bank[bnk].NEmulsions);
    for(int i=0;i<Bank[bnk].NEmulsions+Bank[bnk].NSeparators;i++) 
		if(Bank[bnk].Plates[i]->IsSeparator){ fprintf(fp,"SEPARATOR\n");fprintf(fpl,"SEPARATOR\n");}
		else {
			fprintf(fp,"PLATE %d %d %d %d\n",Bank[bnk].Plates[i]->id.Part[0],Bank[bnk].Plates[i]->id.Part[1],Bank[bnk].Plates[i]->id.Part[2],Bank[bnk].Plates[i]->id.Part[3]);
			fprintf(fpl,"PLATE %d %d %d %d\n",Bank[bnk].Plates[i]->id.Part[0],Bank[bnk].Plates[i]->id.Part[1],Bank[bnk].Plates[i]->id.Part[2],Bank[bnk].Plates[i]->id.Part[3]);
		}
		fprintf(fp,"EndBank %d\n",bnk);
		fprintf(fpl,"EndBank %d\n",bnk);
   
  }

  fclose(fp);
  fclose(fpl);
}

int CMonitor::ReadStatusFile()
{
  char line[128];
  char key[32];
  int I,bnk,seps,plts,a,b,c,d,ip;
  FILE *fp=fopen("c:\\ChangerStatus.txt","r");
  if(fp==NULL) return 0;
  if(fgets(line,128,fp)==NULL) return 0; //date/time line is gisregarded
  ResetBanks();
  
  while(fgets(line,128,fp)!=NULL){
	  sscanf(line,"%s %d",key,&I);
	  if(strcmp(key,"Bank")==0)  bnk=I; 
	  if(strcmp(key,"SEPARATORS")==0) seps=I;
	  if(strcmp(key,"PLATES")==0) plts=I;
	  if(strcmp(key,"PLATE")==0){
		sscanf(line,"%s %d %d %d %d",key,&a,&b,&c,&d);
		ip=Bank[bnk].NEmulsions+Bank[bnk].NSeparators;
        Bank[bnk].Plates[ip]=new TPlate; //add plate
		Bank[bnk].Plates[ip]->SeqNumber=ip;
		Bank[bnk].Plates[ip]->InBank=bnk;
		Bank[bnk].Plates[ip]->IsSeparator=false;
		Bank[bnk].Plates[ip]->id.Part[0]=a;
		Bank[bnk].Plates[ip]->id.Part[1]=b;
		Bank[bnk].Plates[ip]->id.Part[2]=c;
		Bank[bnk].Plates[ip]->id.Part[3]=d;
		Bank[bnk].NEmulsions++;
	  }
	  if(strcmp(key,"SEPARATOR")==0){
		ip=Bank[bnk].NEmulsions+Bank[bnk].NSeparators;
        Bank[bnk].Plates[ip]=new TPlate; //add separator
		Bank[bnk].Plates[ip]->SeqNumber=ip;
		Bank[bnk].Plates[ip]->InBank=bnk;
		Bank[bnk].Plates[ip]->IsSeparator=true;
		Bank[bnk].Plates[ip]->id.Part[0]=0;
		Bank[bnk].Plates[ip]->id.Part[1]=0;
		Bank[bnk].Plates[ip]->id.Part[2]=0;
		Bank[bnk].Plates[ip]->id.Part[3]=0;
		Bank[bnk].NSeparators++;
	  }
	  if(strcmp(key,"EndBank")==0){ 
		  if((bnk!=I) || (Bank[bnk].NSeparators!=seps) || (Bank[bnk].NEmulsions!=plts))
		  {
			  AfxMessageBox("Plate Changer Error: ChangerStatus.txt file is corrupted!!! Resetting banks.");
			  ResetBanks();
			  UpdateBanksView();
			  return 0;
		  }
	  }

  }
  fclose(fp);
  EmulsionOnTable=Bank[0].Plates[0];
ReadyToScan=true;
  UpdateBanksView();
  return 1;
}

void CMonitor::ResetBanks()
{
    if(EmulsionOnTable) EmulsionOnTable->~TPlate();
	EmulsionOnTable=NULL;
	for(int i=0;i<pC->NumberOfBanks+1;i++) {
		Bank[i].Number=i; //0- microscope, 1-3 banks 
        Bank[i].NEmulsions=0; //not known how many plates it contains
        Bank[i].NSeparators=0; 
	    for(int j=0;j<MAX_NUMBER_OF_PLATES*2;j++) Bank[i].Plates[j]=NULL;
	}
    ReadyToScan=false;

}

void CMonitor::OnInitialize2() 
{
OnHomestage();
OnInitialize();	
}


int CMonitor::OpenComPort(int Nport)
{
	if(port.IsOpen()) return 1;
	int PORT;
	bool result;
	COMMCONFIG config;
    CSerialPort::GetDefaultConfig(Nport, config);
    port.Open(Nport, 19200, CSerialPort::NoParity, 8, CSerialPort::OneStopBit, CSerialPort::NoFlowControl);
    COMMTIMEOUTS timeouts;
    port.GetTimeouts(timeouts);

 //   port.Setup(10000, 10000);

timeouts.ReadIntervalTimeout = 40; 
timeouts.ReadTotalTimeoutMultiplier = 10;
timeouts.ReadTotalTimeoutConstant = 100;
timeouts.WriteTotalTimeoutMultiplier = 10;
timeouts.WriteTotalTimeoutConstant = 100;
    port.SetTimeouts(timeouts);
    DWORD dwErrors;                      
    port.ClearError(dwErrors);
//	  port.TerminateOutstandingWrites();
//  port.TerminateOutstandingReads();
//  port.ClearWriteBuffer();
 // port.ClearReadBuffer();

    port.Flush();

	return 1;
}

void CMonitor::CloseComPort()
{
		if(port.IsOpen())
	{
     port.Flush();
     port.Close();
	}

}


void CMonitor::OnButtonPoweron() 
{
if(!PowerON(50)) AfxMessageBox("Can't turn drive power ON! Check the serial connection!");	
}

void CMonitor::OnButtonPoweroff() 
{
if(!PowerOFF(50)) AfxMessageBox("Can't turn drive power OFF! Check the serial connection!");	
	
}
