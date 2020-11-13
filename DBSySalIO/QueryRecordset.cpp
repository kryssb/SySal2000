// QueryRecordset.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "QueryRecordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryRecordset

IMPLEMENT_DYNAMIC(CQueryRecordset, CRecordset)

CQueryRecordset::CQueryRecordset(ConfigData::t_DBQueryData &q, CDatabase* pdb) : Q(q), 
	CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CQueryRecordset)
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	Id.Part[0] = Id.Part[1] = Id.Part[2] = Id.Part[3] = 0;
}


CString CQueryRecordset::GetDefaultConnect()
{
	return _T("ODBC;");
}

CString CQueryRecordset::GetDefaultSQL()
{
	CString Temp = "SELECT ";
	int i, f;
	f = 0;
	for (i = 0; i < 4; i++)
	{
		if (Q.Links[i].Name[0])
		{
			if (f) Temp += ",";
			Temp += "[";
			Temp += Q.Links[i].Name;
			Temp += "]";
			f++;
			};
		};
	for (i = 0; i < Q.CountOfAdditionalFields; i++)
	{
		if (Q.AdditionalField[i].Name[0])
		{
			if (f) Temp += ",";
			Temp += "[";
			Temp += Q.AdditionalField[i].Name;
			Temp += "]";
			f++;
			};
		};
	Temp += " FROM [";
	Temp += Q.TableName;
	Temp += "]";
	if (Q.Links[0].IsLinked || Q.Links[1].IsLinked || 
		Q.Links[2].IsLinked || Q.Links[3].IsLinked)
	{
		Temp += " WHERE(";

		f = 0;
		for (i = 0; i < 4; i++)
		{
			if (Q.Links[i].IsLinked)
			{
				if (f) Temp += " AND ";
				Temp += "[";
				Temp += Q.Links[i].Name;			
				Temp += "]=";
				CString IdStr;
				IdStr.Format("%d", Id.Part[i]);
				Temp += IdStr;
				f++;
				};
			};
		Temp +=")";
		};
	return Temp;
}

void CQueryRecordset::DoFieldExchange(CFieldExchange* pFX)
{
	int i;
	//{{AFX_FIELD_MAP(CQueryRecordset)
	if (!pFX) return;
	pFX->SetFieldType(CFieldExchange::outputColumn);
	for (i = 0; i < 4; i++)
		if (Q.Links[i].Name[0]) RFX_Long(pFX, _T(""), (long &)m_Id.Part[i]);
	for (i = 0; i < Q.CountOfAdditionalFields; i++)
		if (Q.AdditionalField[i].Name[0])
		{
			switch (Q.AdditionalField[i].Type)
			{
				case DBP_TYPE_INT:		RFX_Long(pFX, _T(""), (long &)m_AdditionalFields[i].Int);
										break;

				case DBP_TYPE_SHORT:	RFX_Int(pFX, _T(""), (int &)m_AdditionalFields[i].Short);
										break;

				case DBP_TYPE_CHAR:		RFX_Byte(pFX, _T(""), (BYTE &)m_AdditionalFields[i].Char);
										break;

				case DBP_TYPE_FLOAT:	RFX_Single(pFX, _T(""), m_AdditionalFields[i].Float);
										break;

				case DBP_TYPE_DOUBLE:	RFX_Double(pFX, _T(""), m_AdditionalFields[i].Double);
										break;
				};
			};
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CQueryRecordset diagnostics

#ifdef _DEBUG
void CQueryRecordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CQueryRecordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CQueryRecordset::SetId(Identifier &id)
{
	Id = id;
}

void CQueryRecordset::SyncFields()
{
	int i, index = 0;
	CDBVariant Value;
	for (i = 0; i < 4; i++)
	{
		if (Q.Links[i].Name[0]) 
		{
			GetFieldValue(index++, Value);
			m_Id.Part[i] = Value.m_lVal;
			}
		else m_Id.Part[i] = 0;
		};
	for (i = 0; i < Q.CountOfAdditionalFields; i++)
	{
		if (Q.AdditionalField[i].Name[0])
		{
			GetFieldValue(index++, Value);
			switch (Q.AdditionalField[i].Type)
			{
				case DBP_TYPE_INT:		m_AdditionalFields[i].Int = Value.m_lVal;
										break;

				case DBP_TYPE_SHORT:	m_AdditionalFields[i].Short = Value.m_iVal;
										break;

				case DBP_TYPE_CHAR:		m_AdditionalFields[i].Char = Value.m_chVal;
										break;

				case DBP_TYPE_FLOAT:	m_AdditionalFields[i].Float = Value.m_fltVal;
										break;

				case DBP_TYPE_DOUBLE:	m_AdditionalFields[i].Double = Value.m_dblVal;
										break;
				};
			};
		};
}
