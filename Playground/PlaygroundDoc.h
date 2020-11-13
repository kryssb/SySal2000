// PlaygroundDoc.h : interface of the CPlaygroundDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYGROUNDDOC_H__4EBD0A2E_7386_11D3_A47B_B3DA25ED5623__INCLUDED_)
#define AFX_PLAYGROUNDDOC_H__4EBD0A2E_7386_11D3_A47B_B3DA25ED5623__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _WIN32_WINNT 0x0400

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "..\Common\SySalObj2.h"
#include "PersistentObject.h"
#include <afxtempl.h>

typedef CList<CPersistentObject, CPersistentObject &> CLayout;

class CPlaygroundDoc : public CDocument
{
protected: // create from serialization only
	CPlaygroundDoc();
	DECLARE_DYNCREATE(CPlaygroundDoc)

// Attributes
public:
	CLayout Layout;
	LOGFONT LogFont;
	CString Title;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaygroundDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	//}}AFX_VIRTUAL

// Implementation
public:
	static void WriteString(CFile *pFile, char *pText);
	bool LayoutLocked;
	CString Executor;
	CPersistentObject * SeekByName(CString &Name);
	virtual ~CPlaygroundDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	bool ExportLayoutToXML(CFile *pFile);

protected:

// Generated message map functions
protected:
	static void WriteIndent(CFile *pFile, int level);
	//{{AFX_MSG(CPlaygroundDoc)
	afx_msg void OnExportToXML();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

#ifndef OLE_DISABLE
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CPlaygroundDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYGROUNDDOC_H__4EBD0A2E_7386_11D3_A47B_B3DA25ED5623__INCLUDED_)
