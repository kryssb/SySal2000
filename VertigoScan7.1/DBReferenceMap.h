#pragma once
#include "resource.h"
#using <mscorlib.dll>
#using <System.dll>
#using <System.Data.dll>
#using "SySalCore.dll"
#using "Tracking.dll"
#using "OperaDb.dll"
#using "OperaDbLoginTools.dll"
#include <vcclr.h>
#include "afxwin.h"

// CDBReferenceMap dialog

class CDBReferenceMap : public CDialog
{
	DECLARE_DYNAMIC(CDBReferenceMap)

public:
	CDBReferenceMap(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDBReferenceMap();

// Dialog Data
	enum { IDD = IDD_DBREFMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	gcroot<SySal::OperaDb::OperaDbConnection ^> DBConn;
	gcroot<System::Data::DataRowCollection ^> drbricks;
	gcroot<System::Data::DataRowCollection ^> drplates;
	gcroot<System::Data::DataRowCollection ^> drprocops;
	gcroot<System::Data::DataRowCollection ^> drzones;

	void HandleException(System::Exception ^x);
	static char *String2Char(System::String ^s);	

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBrickSelChange();
	afx_msg void OnPlateSelChange();
	afx_msg void OnProcOpSelChange();
	afx_msg void OnZoneSelChange();
	double m_MinX;
	double m_MaxX;
	double m_MinY;
	double m_MaxY;
	int m_Limit;
	virtual BOOL OnInitDialog();
	CComboBox cmbBrick;
	CComboBox cmbPlate;
	CComboBox cmbProcOp;
	CComboBox cmbZone;
	BOOL m_ContainsEnabled;
	double m_HasX;
	double m_HasY;
	int m_MinGrains;
	double m_MinSlope;
	double m_MaxSlope;	
	afx_msg void OnReqContainClicked();	
	afx_msg void OnHasXLeave();
	afx_msg void OnHasYLeave();	
	afx_msg void OnBnClickedOk();
	gcroot<array<SySal::Tracking::MIPEmulsionTrackInfo ^> ^>TrackArray;
	afx_msg void OnBnClickedCancel();
};
