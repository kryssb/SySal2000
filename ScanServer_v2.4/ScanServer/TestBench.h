#pragma once
#include "vcclr.h"
#include "ScanServerNET.h"

// CTestBench dialog

class CTestBench : public CDialog
{
	DECLARE_DYNAMIC(CTestBench)

public:
	CTestBench(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestBench();

// Dialog Data
	enum { IDD = IDD_TESTMODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support	

	static UINT _cdecl ThreadHook(void *);
	UINT Thread();
	DECLARE_MESSAGE_MAP()
public:	
	gcroot<SySal::DAQSystem::ScanServer ^> SS;
	CString m_LoadPlateTextDesc;
	long m_LoadPlateBrick;
	long m_LoadPlatePlate;
	CString m_LoadPlateMapInit;
	long m_ScanZoneId;
	double m_ScanMinX;
	double m_ScanMaxX;
	double m_ScanMinY;
	double m_ScanMaxY;
	BOOL m_ScanPresetSlope;
	double m_ScanSlopeX;
	double m_ScanSlopeY;
	double m_ScanSlopeAccX;
	double m_ScanSlopeAccY;
	BOOL m_ScanMoveNext;
	double m_ScanMoveNextMinX;
	double m_ScanMoveNextMinY;
	double m_ScanMoveNextMaxX;
	double m_ScanMoveNextMaxY;
	CString m_SetSingleParamObject;
	CString m_SetSingleParamParam;
	CString m_SetSingleParamValue;
	CString m_SetObjectConfigObject;
	CString m_SetObjectConfigConfig;
	CString m_SetScanLayoutLayout;
	long m_ManualCheckId;
	double m_ManualCheckPosX;
	double m_ManualCheckPosY;
	double m_ManualCheckSlopeX;
	double m_ManualCheckSlopeY;
	double m_ManualCheckPosTol;
	double m_ManualCheckSlopeTol;
	int m_ManualCheckOutGrains;
	double m_ManualCheckOutPosX;
	double m_ManualCheckOutPosY;
	double m_ManualCheckOutSlopeX;
	double m_ManualCheckOutSlopeY;
	double m_TopFog;
	double m_BottomFog;
	double m_TopThickness;
	double m_BottomThickness;
	double m_BaseThickness;
	BOOL m_Done;
	CString m_Exception;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedTbHide();
	afx_msg void OnBnClickedTbSend();
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	CString m_ScanOutname;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedTbCheckdone();
	afx_msg void OnBnClickedTbFound();
	BOOL m_ManualCheckFound;
	BOOL m_ManualCheckDone;
	afx_msg void OnBnClickedTbLoadscanlayout();
};
