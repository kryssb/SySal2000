// PlaygroundView.h : interface of the CPlaygroundView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYGROUNDVIEW_H__4EBD0A30_7386_11D3_A47B_B3DA25ED5623__INCLUDED_)
#define AFX_PLAYGROUNDVIEW_H__4EBD0A30_7386_11D3_A47B_B3DA25ED5623__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConnectionDlg.h"
#include "..\Common\SySalObject2Structs.h"

#define UM_ASYNCSTATUS_IDLE		(WM_APP + 0x80)
#define UM_ASYNCSTATUS_RUNNING	(WM_APP + 0x81)
#define UM_ASYNCSTATUS_PAUSED	(WM_APP + 0x82)

class CPlaygroundView : public CView
{
protected: // create from serialization only
	CPlaygroundView();
	DECLARE_DYNCREATE(CPlaygroundView)

	int Status;
	CLSID DefaultCLSID;
	POSITION POSCurrentObject;
	CSize CursorOffset;
	CPoint NewConnStart, NewConnEnd;

	HICON HExecArrow;

// Attributes
public:
	CPlaygroundDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaygroundView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:	
	static bool LoadConfig(SySalConfig &C, CString &Name);
	static bool LoadMachineDefaults(SySalConfig &C, CLSID &clsid);
	void SetConfigManagerInterface(ISySalObject *iObj);
	bool SetConfig(CPoint point);
	afx_msg LRESULT OnAsyncPaused(WPARAM, LPARAM);
	afx_msg LRESULT OnAsyncIdle(WPARAM, LPARAM);
	afx_msg LRESULT OnAsyncRunning(WPARAM, LPARAM);
	static UINT WINAPI AsyncCheckStatusHook(void *pOwner);
	CString CurrentClassNameSelection;
	bool SetClassSel(CString &classname);
	virtual ~CPlaygroundView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	bool EnableMonitor(CPoint point, bool bEnable);
	bool SaveConfig(SySalConfig &C);
	bool SaveMachineDefaults(SySalConfig &C, CLSID &clsid);
	void FreeConfig(SySalConfig &C);
	bool EditConfig(CPoint point);
	bool EditMachineDefaults(CPoint point);
	ISySalObject * pExecutor;	
	CWinThread * pAsyncCheckStatus;
	HANDLE HAsyncStatusChangeEvent;
	int AsyncRunStatus;
	CString SelectedConfig;

	bool SetConfigs();

	UINT AsyncCheckStatus();
	bool CheckReady();
	bool SetExec(CPoint point);
	bool EditConnection(CPoint point);
	bool NewConnection(CPoint point);
	void DrawArrow(bool IsTemp, CDC *pDC, CPoint start, CPoint end);
	CBitmap * pBufferBitmap;
	CDC * pBufferDC;
	bool RenameObject(CPoint point);
	POSITION FindObjectInLayout(CPoint point);
	void DisplayObjInfo(CPoint point);
	bool DeleteObject(CPoint point);
	bool NewObject(CPoint point);
	void SetCursorShape();
	bool Draw(CDC *pDC);

	static bool _stdcall CMISaveConfig(DWORD context, SySalConfig *pC, char *name);
	static bool _stdcall CMILoadConfig(DWORD context, SySalConfig *pC, char *name);

	//{{AFX_MSG(CPlaygroundView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnObjNew();
	afx_msg void OnObjDelete();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnObjRename();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTitle();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnConnNew();
	afx_msg void OnConnEdit();
	afx_msg void OnConnDelete();
	afx_msg void OnResetExec();
	afx_msg void OnSetExec();
	afx_msg void OnPlaySync();
	afx_msg void OnUpdateObjDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjRename(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConnDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConnNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlaySync(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConnEdit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetExec(CCmdUI* pCmdUI);
	afx_msg void OnUpdateResetExec(CCmdUI* pCmdUI);
	afx_msg void OnPlayAsync();
	afx_msg void OnUpdatePlayAsync(CCmdUI* pCmdUI);
	afx_msg void OnStop();
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnPause();
	afx_msg void OnUpdatePause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTitle(CCmdUI* pCmdUI);
	afx_msg void OnSetConfig();
	afx_msg void OnUpdateSetConfig(CCmdUI* pCmdUI);
	afx_msg void OnConfigNew();
	afx_msg void OnConfigEdit();
	afx_msg void OnConfigDelete();
	afx_msg void OnUpdateConfigDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConfigEdit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConfigNew(CCmdUI* pCmdUI);
	afx_msg void OnMonitorDisable();
	afx_msg void OnMonitorEnable();
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnConfigApply();
	afx_msg void OnUpdateApplyConfig(CCmdUI* pCmdUI);
	afx_msg void OnConfigDuplicate();
	afx_msg void OnUpdateConfigDuplicate(CCmdUI* pCmdUI);
	afx_msg void OnObjInfo();
	afx_msg void OnUpdateObjInfo(CCmdUI* pCmdUI);
	afx_msg void OnMachineDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HCURSOR HCursor;
	HINSTANCE hResourceHandle;
};

#ifndef _DEBUG  // debug version in PlaygroundView.cpp
inline CPlaygroundDoc* CPlaygroundView::GetDocument()
   { return (CPlaygroundDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYGROUNDVIEW_H__4EBD0A30_7386_11D3_A47B_B3DA25ED5623__INCLUDED_)
