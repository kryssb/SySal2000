#if !defined(AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_)
#define AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Monitor.h : header file
//

#include <afxcmn.h>
#include "ConfigData.h"
#include "serialport.h"
#include "id.h"
#include "..//Common//Stage2.h"







/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog

#define UM_REFRESH (WM_APP + 1)

#define MAX_NUMBER_OF_PLATES		100
#define VPOS_UP		0
#define VPOS_DOWN		1
#define VPOS_DOWN_TO_STAGE		2
#define VPOS_ABOVE_STAGE		3

struct TPlate
{
	Identifier id;
	int SeqNumber;
	int InBank;
	bool IsSeparator;

};

struct TBank
{
	int Number; //0- microscope, 1-3 banks 
    int NEmulsions; //how many plates it contains
    int NSeparators; //how many plates it contains
	TPlate* Plates[MAX_NUMBER_OF_PLATES*2];


};

      class CMonitor : public CDialog
{
// Construction
public:

	TBank Bank[5];
    CSerialPort port;
	bool IsManualControlEnabled();
	void EnableManualControl(bool bEnable);
	CMonitor(ConfigData *pc, HANDLE *phmonitormutex, HANDLE *phrun, void *pctx, void (*penabler)(void *, bool), CWnd* pParent = NULL);   // standard constructor

	bool InitDone;
	bool ReadyToScan;
	int SourceBank;
	int DestinationBank;
	TPlate* EmulsionOnTable;
    void DrawSemaphore(int IdRed, int IdGreen, bool Status);
	CString xpos, zpos;//number of stop on X (Z) read from dialog in manual mode
	CString sourcebank, scannedbank;//number of "source"("scanned") bank; corresponds to stop number
	int currentx, currentz;
// Dialog Data
	//{{AFX_DATA(CMonitor)
	enum { IDD = IDD_MONITOR };
	CComboBox	m_BANK4;
	CButton	m_Separator2;
	CButton	m_Separator;
	CComboBox	m_BANK3;
	CComboBox	m_BANK2;
	CComboBox	m_BANK1;
	CComboBox	m_BANK0;
	BOOL	m_checkin1x;
	BOOL	m_checkin0x;
	BOOL	m_checkin2x;
	BOOL	m_checkin3x;
	BOOL	m_checkin4x;
	BOOL	m_checkin5x;
	BOOL	m_checkin6x;
	BOOL	m_checkin7x;
	CString	m_xpos;
	BOOL	m_checkin0z;
	BOOL	m_checkin1z;
	BOOL	m_checkin2z;
	BOOL	m_checkin3z;
	BOOL	m_checkin4z;
	BOOL	m_checkin5z;
	BOOL	m_checkin6z;
	BOOL	m_checkin7z;
	CString	m_zpos;
	CString	m_xposmsg;
	CString	m_zposmsg;
	CString	m_source;
	CString	m_scanned;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:	
	int DebugLevel;
//	void DrawSemaphore(int IdRed, int IdGreen, bool Status);
	HANDLE *pHMonitorMutex;
	HANDLE *pHRun;

	void *pContext;
	void (*pEnabler)(void *pCtx, bool bEnable);

	int SpeedMultiplier;
	ConfigData *pC; 
public:
	void CloseComPort();
	int PowerOFF(int timeout);
	int PowerON(int timeout);
	int VacRegister;
	int OpenComPort(int Nport);
	void ResetBanks();
	int ReadStatusFile();
	void UpdateStatusFile();
	int WaitTillReached(int Axis, float TargetPos, float Speed, float Tolerance);
	void SetStatus(char * statusline);
	bool IsStageHomed;
	bool StageHoming(int dirX, int dirY, int dirZ,  float HomeX, float HomeY, float HomeZ);
	IStage *pSt;
	void UpdateBankView(int bnk, CComboBox* Control);
	TPlate* TakeFromBank(int bnk);
	void AddToBank(int bnk, TPlate* plate);
	int FindEmulsion(Identifier id, int Bank);
	int UnloadPlate();
	int LoadPlate(Identifier id);
	void UpdateBanksView();
	int  GoOnHAxis(int bank, int timeout);
	int  GoOnVAxis(int bank, int timeout);
	int ArmVacuumControl(bool VacOn, int timeout);
	int TableVacuumControl(bool VacOn, int timeout, bool PressureOn=false);
	int MoveEmulsion(int isrc, int idst);
	int Park(int idst);
	static bool CMonitor::MyShouldStopCallback(DWORD Context);
	afx_msg LRESULT OnRefresh(WPARAM, LPARAM);
	// Generated message map functions
	//{{AFX_MSG(CMonitor)
	afx_msg void OnHide();
	afx_msg void OnReset();
	afx_msg void OnToggleManual();
	afx_msg void OnSpeedX1();
	afx_msg void OnSpeedX10();
	afx_msg void OnSpeedX100();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnButtonGoX();
	afx_msg void OnButtonRead();
	afx_msg void OnUpdateMThpos();
	afx_msg void OnUpdateMZpos();
	afx_msg void OnButtonPowZ();
	afx_msg void OnButtonGoZ();
	afx_msg void OnUpdateEditSource();
	afx_msg void OnUpdateEditScanned();
	afx_msg void OnInitialize();
	afx_msg void OnLoad();
	afx_msg void OnButtonVacon();
	afx_msg void OnButtonVacoff();
	afx_msg void OnUnload();
	afx_msg void OnChgplt();
	afx_msg void OnMvsep();
	afx_msg void OnChgplt2();
	afx_msg void OnButtonVacoff2();
	afx_msg void OnButtonVacon2();
	afx_msg void OnSort();
	afx_msg void OnCheckSeparator();
	afx_msg void OnCheckSeparator2();
	afx_msg void OnChangeEditSource3();
	afx_msg void OnLoadbank();
	afx_msg void OnDebuglevel();
	afx_msg void OnLoademid();
	afx_msg void OnUnloadem();
	afx_msg void OnHomestage();
	afx_msg void OnInitialize2();
	afx_msg void OnTestbutton();
	afx_msg void OnButtonPoweron();
	afx_msg void OnButtonPoweroff();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_)
