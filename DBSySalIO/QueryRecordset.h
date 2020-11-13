#if !defined(AFX_QUERYRECORDSET_H__8444DB74_7427_4ACB_8A6E_316B11EBD90E__INCLUDED_)
#define AFX_QUERYRECORDSET_H__8444DB74_7427_4ACB_8A6E_316B11EBD90E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryRecordset.h : header file
//

#include <afxdb.h>
#include "ConfigData.h"
#include "..\Common\datastructs.h"
#include "..\Common\id.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CQueryRecordset recordset

class CQueryRecordset : public CRecordset
{
public:
	void SyncFields();
	Identifier m_Id;
	union
	{
		int Int;
		short Short;
		char Char;
		float Float;
		double Double;
		bool Bool;
		} m_AdditionalFields[DBP_MAX_ADDITIONAL_DATA_SIZE];
	void SetId(Identifier &id);
	CQueryRecordset(ConfigData::t_DBQueryData &q, CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CQueryRecordset)

// Field/Param Data
	//{{AFX_FIELD(CQueryRecordset, CRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryRecordset)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	ConfigData::t_DBQueryData &Q;
	Identifier Id;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYRECORDSET_H__8444DB74_7427_4ACB_8A6E_316B11EBD90E__INCLUDED_)
