// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditConfig.h"
#include "EditField.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

#define VIEW_TRACK_PREDICTION		0

CEditConfig::CEditConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CEditConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditConfig)
	m_Password = _T("");
	m_UserName = _T("");
	m_InputEnable = FALSE;
	m_OutputEnable = FALSE;
	m_LinkId0 = FALSE;
	m_LinkId1 = FALSE;
	m_LinkId2 = FALSE;
	m_LinkId3 = FALSE;
	m_LinkField0 = _T("");
	m_LinkField1 = _T("");
	m_LinkField2 = _T("");
	m_LinkField3 = _T("");
	m_DSN = _T("");
	m_TableName = _T("");
	//}}AFX_DATA_INIT
	C.DSN[0] = 0;
	C.UserName[0] = 0;
	C.Password[0] = 0;
	C.InputEnabled = true;
	C.OutputEnabled = false;	
	C.TrackPrediction.CountOfAdditionalFields = 0;
	C.TrackPrediction.TableName[0] = 0;
	C.TrackPrediction.Links[0].IsLinked = C.TrackPrediction.Links[1].IsLinked = 
		C.TrackPrediction.Links[2].IsLinked = C.TrackPrediction.Links[3].IsLinked = false;
	C.TrackPrediction.Links[0].Name[0] = C.TrackPrediction.Links[0].Name[1] = 
		C.TrackPrediction.Links[0].Name[2] = C.TrackPrediction.Links[0].Name[3] = 0;
	Status = VIEW_TRACK_PREDICTION;
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Control(pDX, IDC_EC_TAB, m_Tab);
	DDX_Control(pDX, IDC_EC_ADDITIONALFIELDS, m_AdditionalFields);
	DDX_Text(pDX, IDC_EC_EPASSWORD, m_Password);
	DDX_Text(pDX, IDC_EC_EUSERNAME, m_UserName);
	DDX_Check(pDX, IDC_EC_INPUTENABLE, m_InputEnable);
	DDX_Check(pDX, IDC_EC_OUTPUTENABLE, m_OutputEnable);
	DDX_Check(pDX, IDC_EC_CLINKID0, m_LinkId0);
	DDX_Check(pDX, IDC_EC_CLINKID1, m_LinkId1);
	DDX_Check(pDX, IDC_EC_CLINKID2, m_LinkId2);
	DDX_Check(pDX, IDC_EC_CLINKID3, m_LinkId3);
	DDX_Text(pDX, IDC_EC_ELINKID0, m_LinkField0);
	DDX_Text(pDX, IDC_EC_ELINKID1, m_LinkField1);
	DDX_Text(pDX, IDC_EC_ELINKID2, m_LinkField2);
	DDX_Text(pDX, IDC_EC_ELINKID3, m_LinkField3);
	DDX_Text(pDX, IDC_EC_EDSN, m_DSN);
	DDX_Text(pDX, IDC_EC_ETABLENAME, m_TableName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_NOTIFY(TCN_SELCHANGE, IDC_EC_TAB, OnSelChangeTab)
	ON_BN_CLICKED(IDC_EC_EDITFIELD, OnEditField)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

void CEditConfig::OnSelChangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateLinks();
	ShowView(Status = m_Tab.GetCurSel());
	*pResult = 0;
}

void CEditConfig::ShowView(int v)
{
	ConfigData::t_DBQueryData *pQ = 0;
	switch (v)
	{
		case VIEW_TRACK_PREDICTION:		pQ = &C.TrackPrediction;
										break;

		default:						return;
		};
	m_TableName = pQ->TableName;
	m_LinkId0 = pQ->Links[0].IsLinked;
	m_LinkId1 = pQ->Links[1].IsLinked;
	m_LinkId2 = pQ->Links[2].IsLinked;
	m_LinkId3 = pQ->Links[3].IsLinked;
	m_LinkField0 = pQ->Links[0].Name;
	m_LinkField1 = pQ->Links[1].Name;
	m_LinkField2 = pQ->Links[2].Name;
	m_LinkField3 = pQ->Links[3].Name;
	m_AdditionalFields.DeleteAllItems();
	int i;
	CString N;
	for (i = 0; i < pQ->CountOfAdditionalFields; i++)
	{
		char *pN = "";
		switch (pQ->AdditionalField[i].Type)
		{
			case DBP_TYPE_INT:			pN = "Int";
										break;

			case DBP_TYPE_SHORT:		pN = "Short";
										break;

			case DBP_TYPE_CHAR:			pN = "Char";
										break;

			case DBP_TYPE_FLOAT:		pN = "Float";
										break;

			case DBP_TYPE_DOUBLE:		pN = "Double";
										break;

			default:					pN = "Unknown";
										break;
			};
		N.Format("%d", i);
		int Index = m_AdditionalFields.InsertItem(i, N);
		m_AdditionalFields.SetItemText(Index, 1, pQ->AdditionalField[i].Name);
		m_AdditionalFields.SetItemText(Index, 2, pN);
		m_AdditionalFields.SetItemData(Index, i);
		};
	for (; i < DBP_MAX_ADDITIONAL_DATA_SIZE; i++)
	{
		pQ->AdditionalField[i].Name[0] = 0;
		pQ->AdditionalField[i].Type = -1;
		N.Format("%d", i);
		int Index = m_AdditionalFields.InsertItem(i, N);
		m_AdditionalFields.SetItemText(Index, 1, "");
		m_AdditionalFields.SetItemText(Index, 2, "Unknown");
		m_AdditionalFields.SetItemData(Index, i);
		};
	pQ->CountOfAdditionalFields = DBP_MAX_ADDITIONAL_DATA_SIZE;
	UpdateData(FALSE);
}

BOOL CEditConfig::OnInitDialog() 
{
	m_InputEnable = C.InputEnabled;
	m_OutputEnable = C.OutputEnabled;
	m_DSN = C.DSN;
	m_UserName = C.UserName;
	m_Password = C.Password;	

	CDialog::OnInitDialog();

	m_AdditionalFields.DeleteColumn(0);
	m_AdditionalFields.InsertColumn(0, "#", LVCFMT_LEFT, 30, 0);
	m_AdditionalFields.InsertColumn(1, "Field Name", LVCFMT_LEFT, 100, 1);
	CRect ClRect;
	m_AdditionalFields.GetClientRect(&ClRect);	
	m_AdditionalFields.InsertColumn(2, "Type", LVCFMT_CENTER, ClRect.Width() - 130, 2);
	m_Tab.DeleteAllItems();
	m_Tab.InsertItem(VIEW_TRACK_PREDICTION, "Track Prediction");
	m_Tab.SetCurSel(VIEW_TRACK_PREDICTION);
	ShowView(VIEW_TRACK_PREDICTION);
	
	// TODO: Add extra initialization here	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditConfig::UpdateLinks()
{	
	ConfigData::t_DBQueryData *pQ = 0;
	switch (Status)
	{
		case VIEW_TRACK_PREDICTION:		pQ = &C.TrackPrediction;
										break;

		default:						return;
		};
	UpdateData();
	strncpy(pQ->TableName, m_TableName, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);	
	m_TableName.ReleaseBuffer();
	pQ->Links[0].IsLinked = m_LinkId0;
	pQ->Links[1].IsLinked = m_LinkId1;
	pQ->Links[2].IsLinked = m_LinkId2;
	pQ->Links[3].IsLinked = m_LinkId3;
	strncpy(pQ->Links[0].Name, m_LinkField0.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	m_LinkField0.ReleaseBuffer();
	strncpy(pQ->Links[1].Name, m_LinkField1.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	m_LinkField1.ReleaseBuffer();
	strncpy(pQ->Links[2].Name, m_LinkField2.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	m_LinkField2.ReleaseBuffer();
	strncpy(pQ->Links[3].Name, m_LinkField3.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);	
	m_LinkField3.ReleaseBuffer();
}

void CEditConfig::OnEditField() 
{
	// TODO: Add your control notification handler code here
	int Index = m_AdditionalFields.GetSelectionMark();
	if (Index < 0) return;

	m_AdditionalFields.EnsureVisible(Index, FALSE);

	ConfigData::t_DBQueryData *pQ = 0;
	switch (Status)
	{
		case VIEW_TRACK_PREDICTION:		pQ = &C.TrackPrediction;
										break;

		default:						return;
		};

	CEditField MyDlg(this);
	MyDlg.m_Name = pQ->AdditionalField[Index].Name;
	MyDlg.m_Type = pQ->AdditionalField[Index].Type;
	if (MyDlg.DoModal() == IDOK)
	{
		strncpy(pQ->AdditionalField[Index].Name, MyDlg.m_Name.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		MyDlg.m_Name.ReleaseBuffer();
		pQ->AdditionalField[Index].Type = MyDlg.m_Type;
		};
	UpdateData();
	UpdateLinks();
	ShowView(Status);
}

void CEditConfig::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	UpdateLinks();
	C.InputEnabled = m_InputEnable;
	C.OutputEnabled = m_OutputEnable;
	strncpy(C.DSN, m_DSN.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	m_DSN.ReleaseBuffer();
	strncpy(C.UserName, m_UserName.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	m_UserName.ReleaseBuffer();
	strncpy(C.Password, m_Password.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	m_Password.ReleaseBuffer();
	if ((C.TrackPrediction.Links[0].IsLinked && !C.TrackPrediction.Links[0].Name[0]) ||
		(C.TrackPrediction.Links[1].IsLinked && !C.TrackPrediction.Links[1].Name[0]) ||
		(C.TrackPrediction.Links[2].IsLinked && !C.TrackPrediction.Links[2].Name[0]) ||
		(C.TrackPrediction.Links[3].IsLinked && !C.TrackPrediction.Links[3].Name[0]))
	{
		MessageBox("Cannot link identifiers with emtpy fields!", "Error", MB_ICONERROR | MB_OK);
		return;
		};
	int i;
	for (i = 0; (i < DBP_MAX_ADDITIONAL_DATA_SIZE) && C.TrackPrediction.AdditionalField[i].Name[0]; i++);
	C.TrackPrediction.CountOfAdditionalFields = i;
	CDialog::OnOK();
}
