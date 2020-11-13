#pragma once

#include "ums.h"
#include "resource.h"
#include "FlexMapData.h"
#include "../ESS/Log.h"

const char               kMapDefExt[] = "txt" ;
const DWORD              kMapFlags    = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ;
const char BASED_CODE    kMapFilters[] = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";

// CDlgMain dialog

class CDlgMain : public CDialog //, public ESS::Log::TLogger
{
//	DECLARE_DYNAMIC(CDlgMain)

// Function Members (Methods)
public:
   CDlgMain(HWND *phwnd, CWnd* pParent = NULL);   // standard constructor  //TO BE CALLED BY ASYNCEXEC
	//CDlgMain(CWnd* pParent = NULL);              // default standard constructor
	virtual ~CDlgMain();

   void        SetConfig( FlexMapData config) ;
   FlexMapData GetConfig()                    ;

   DECLARE_MESSAGE_MAP()
   afx_msg void OnBnClickedImSelpath();
   afx_msg void OnBnClickedRadio1();
   afx_msg void OnBnClickedRadio2();
   afx_msg void OnBnClickedRadio3();
   afx_msg void OnBnClickedRadio4();
   afx_msg void OnBnClickedRadio5();
   CString FileToString() ;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);        //TO BE CALLED BY ASYNCEXEC

// Data Members
public:
   // Dialog Data
	enum { IDD = IDD_MAIN } ;
   int      m_AutoSearchFirstMark   ;
   int      m_SheetRotated180 ;
   int      m_ForceLateral    ;
   CString  m_InitString      ;

protected:
   HWND*       m_phWnd    ;  //TO BE CALLED BY ASYNCEXEC
   FlexMapData m_Config  ;
public:
   afx_msg void OnBnClickedMainEditconfig();
   afx_msg void OnBnClickedRadio0();
};
