// DBIO.cpp : Implementation of CDBIO
#include "stdafx.h"
#include "DBSySalIO.h"
#include "DBIO.h"
#include "EditConfig.h"
#include <afxdb.h>
#include "QueryRecordset.h"

/////////////////////////////////////////////////////////////////////////////
// CDBIO

const int DataION = 6;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo DataIOName[DataION] =
{	
	{"DSN",				"%s",	STRUCT_OFFSET(ConfigData, DSN), ""},
	{"UserName",		"%s",	STRUCT_OFFSET(ConfigData, UserName), ""},
	{"Password",		"%s",	STRUCT_OFFSET(ConfigData, Password), ""},
	{"InputEnable",		"%d",	STRUCT_OFFSET(ConfigData, InputEnabled), "1"},
	{"OutputEnable",	"%d",	STRUCT_OFFSET(ConfigData, OutputEnabled), "0"},
	{"TrackPrediction", "%q",	STRUCT_OFFSET(ConfigData, TrackPrediction), ""}
	};


int CDBIO::GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
{  
	int Index;
	if (!strcmp(DataName.Format, "%q"))
	{
		int p = 0;
		CString QueryText = "";
		char tempname[SYSAL_MAXCONFIG_ENTRY_NAME_LEN + 3];
		do
		{
			sprintf(tempname, "%s%02d", DataName.Name, p);
			for (Index = 0; (Index < N) && (strncmp(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index, 
				tempname, SYSAL_MAXCONFIG_ENTRY_NAME_LEN)); Index++);
			if (Index < N) 
			{
				char tstr[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN + 1];
				tstr[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN] = 0;
				strncpy(tstr, File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
				QueryText += tstr;
				p++;
				}
			else if (!p)
			{
				QueryText = DataName.Default;
				};
			}
		while (Index < N);
		StringToDBQueryData((*(ConfigData::t_DBQueryData *)((char *)StartPosition + DataName.Position)), QueryText);
		return p > 0;
		};
	for (Index = 0; (Index < N) && (strncmp(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index, 
		DataName.Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN)); Index++);
	if (Index >= N)
	{
		if (strcmp(DataName.Format, "%s")) sscanf(DataName.Default, DataName.Format, (char *)StartPosition + DataName.Position);
		else strcpy((char *)StartPosition + DataName.Position, DataName.Default);
   		return 0;
		};
	if (strcmp(DataName.Format, "%s")) return sscanf(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index + 
		SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataName.Format, (char *)StartPosition + DataName.Position);
	strcpy((char *)StartPosition + DataName.Position, File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index + 
		SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
	return 1;
	};

void CDBIO::DBQueryDataToString(ConfigData::t_DBQueryData &Q, CString &Out)
{
	CString Temp;
	Out.Format("%s ", Q.TableName);
	int i;
	for (i = 0; i < 4; i++)
	{
		Temp.Format("%d %s ", Q.Links[i].IsLinked, Q.Links[i].Name);
		Out += Temp;
		};
	for (i = 0; i < Q.CountOfAdditionalFields; i++)
	{
		Temp.Format("%d %s ", Q.AdditionalField[i].Type, Q.AdditionalField[i].Name);
		Out += Temp;
		};	
	};

bool CDBIO::StringToDBQueryData(ConfigData::t_DBQueryData &Q, CString &In)
{
	int i;
	Q.TableName[0] = 0;
	for (i = 0; i < 4; i++)
	{
		Q.Links[i].IsLinked = false;
		Q.Links[i].Name[0] = 0;
		};
	Q.CountOfAdditionalFields = 0;
	for (i = 0; i < DBP_MAX_ADDITIONAL_DATA_SIZE; i++)
	{
		Q.AdditionalField[i].Name[0] = 0;
		Q.AdditionalField[i].Type = -1;
		};
	if (!In.GetLength()) return false;
	CString Temp;
	int i1 = 0, i2 = 0;

	if (!In[i2]) return false;
	for (; ((unsigned char)(In[i2])) > ' '; i2++);
	Temp = In.Mid(i1, i2 - i1);
	strncpy(Q.TableName, Temp.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	Temp.ReleaseBuffer();
	i1 = ++i2;
	for (i = 0; i < 4; i++)
	{
		if (!In[i2]) return false;
		for (; ((unsigned char)(In[i2])) > ' '; i2++);
		Temp = In.Mid(i1, i2 - i1);
		if (sscanf(Temp.GetBuffer(1), "%d", &Q.Links[i].IsLinked) != 1)
		{
			Temp.ReleaseBuffer();
			return false;
			};
		Temp.ReleaseBuffer();
		i1 = ++i2;
		if (!In[i2]) return false;		
		for (; ((unsigned char)(In[i2])) > ' '; i2++);
		Temp = In.Mid(i1, i2 - i1);
		strncpy(Q.Links[i].Name, Temp.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		Temp.ReleaseBuffer();
		i1 = ++i2;
		};
	for (Q.CountOfAdditionalFields = 0; (Q.CountOfAdditionalFields < DBP_MAX_ADDITIONAL_DATA_SIZE) && (i2 < In.GetLength()); Q.CountOfAdditionalFields++)
	{	
		for (; ((unsigned char)(In[i2])) > ' '; i2++);
		Temp = In.Mid(i1, i2 - i1);
		if (sscanf(Temp.GetBuffer(1), "%d", &Q.AdditionalField[Q.CountOfAdditionalFields].Type) != 1)
		{
			Temp.ReleaseBuffer();
			return false;
			};
		Temp.ReleaseBuffer();
		i1 = ++i2;
		if (!In[i2]) return false;		
		for (; ((unsigned char)(In[i2])) > ' '; i2++);
		Temp = In.Mid(i1, i2 - i1);
		strncpy(Q.AdditionalField[Q.CountOfAdditionalFields].Name, Temp.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		Temp.ReleaseBuffer();
		i1 = ++i2;
		};
	return true;
	};

// ISySalObject
STDMETHODIMP CDBIO::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CDBIO::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CDBIO::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	OkToRun = false;
	int i;
	for (i = 0; (i < DataION) && (GetData(DataIOName[i], &C, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < DataION) return S_FALSE;
	OkToRun = true;
	return S_OK;
}

STDMETHODIMP CDBIO::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(DataION * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;

	CString QueryText;
	DBQueryDataToString(C.TrackPrediction, QueryText);
	int len, pieces;
	len = QueryText.GetLength();
	pieces = (len + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1) / (SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc((DataION + pieces - 1) * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = DataION + pieces - 1;
	int i, j;
	for (i = j = 0; i < DataION; i++)
	{
		if (!strcmp(DataIOName[i].Format, "%q"))
		{
			DBQueryDataToString(*(ConfigData::t_DBQueryData *)((char *)&C + DataIOName[j].Position), QueryText);
			int p;
			for (p = 0; QueryText.GetLength(); p++)
			{
				sprintf(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
					"%s%02d", DataIOName[i].Name, p);
				strncpy(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, QueryText.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1);
				pConfig->pItems[j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1] = 0;
				QueryText.ReleaseBuffer();
				if (QueryText.GetLength() <= (SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1)) QueryText = "";
				else QueryText = QueryText.Right(QueryText.GetLength() - SYSAL_MAXCONFIG_ENTRY_VALUE_LEN + 1);
				j++;
				};
			}
		else
		{
			strncpy(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				DataIOName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			if (!strcmp(DataIOName[i].Format, "%d"))
			{
				sprintf(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataIOName[i].Format, *(int *)((char *)&C + DataIOName[i].Position));
				j++;
				}
			else if (!strcmp(DataIOName[i].Format, "%f"))
			{
				sprintf(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataIOName[i].Format, *(float *)((char *)&C + DataIOName[i].Position));
				j++;
				}
			else 
			{
				sprintf(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataIOName[j].Format, ((char *)&C + DataIOName[j].Position));
				j++;
				};
			};
		};
	return S_OK;
}

STDMETHODIMP CDBIO::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ConfigData Temp;
	int i;
	for (i = 0; i < DataION; i++) 
		GetData(DataIOName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);
	MyDlg.C = Temp;
	if (MyDlg.DoModal() == IDOK)
	{
		Temp = MyDlg.C;
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		CString QueryText;
		DBQueryDataToString(MyDlg.C.TrackPrediction, QueryText);
		int len, pieces;
		len = QueryText.GetLength();
		pieces = (len + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1) / (SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc((DataION + pieces - 1) * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
				return S_FALSE;
		pConfig->CountOfItems = DataION + pieces - 1;
		int i, j;
		for (i = j = 0; i < DataION; i++)
		{
			if (!strcmp(DataIOName[i].Format, "%q"))
			{
				DBQueryDataToString(*(ConfigData::t_DBQueryData *)((char *)&Temp + DataIOName[j].Position), QueryText);
				int p;
				for (p = 0; QueryText.GetLength(); p++)
				{
					sprintf(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
						"%s%02d", DataIOName[i].Name, p);
					strncpy(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
						SYSAL_MAXCONFIG_ENTRY_NAME_LEN, QueryText.GetBuffer(1), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1);
					pConfig->pItems[j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
						SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1] = 0;
					QueryText.ReleaseBuffer();
					if (QueryText.GetLength() <= (SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1)) QueryText = "";
					else QueryText = QueryText.Right(QueryText.GetLength() - SYSAL_MAXCONFIG_ENTRY_VALUE_LEN + 1);
					j++;
					};
				}
			else
			{
				strncpy(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
					DataIOName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
				if (!strcmp(DataIOName[i].Format, "%d"))
				{
					sprintf(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
						SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataIOName[i].Format, *(int *)((char *)&Temp + DataIOName[i].Position));
					j++;
					}
				else if (!strcmp(DataIOName[i].Format, "%f"))
				{
					sprintf(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
						SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataIOName[i].Format, *(float *)((char *)&Temp + DataIOName[i].Position));
					j++;
					}
				else 
				{
					sprintf(pConfig->pItems + j * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
						SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataIOName[j].Format, ((char *)&Temp + DataIOName[j].Position));
					j++;
					};
				};
			};
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CDBIO::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_NOTIMPL : S_OK;
}

STDMETHODIMP CDBIO::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CDBIO::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CDBIO::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CDBIO::GetIcon(int n, HSySalHICON *pHICON)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	HANDLE HTemp = 0;
	switch (n)
	{
		case 0:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON32), IMAGE_ICON, 32, 32, LR_SHARED);
					break;

		case 1:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON64), IMAGE_ICON, 64, 64, LR_SHARED);
					break;

		default:	return E_INVALIDARG;
		};
	*pHICON = (HSySalHICON)HTemp;
	return S_OK;	
}

STDMETHODIMP CDBIO::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "DBSySal I/O Device", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CDBIO::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CDBIO::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CDBIO::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CDBIO::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CDBIO::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CDBIO::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CDBIO::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CDBIO::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

// ISySalDataIO
STDMETHODIMP CDBIO::Write(HSySalHANDLE hWnd, BYTE *pData, UINT *pExtErrorInfo, BYTE *FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
/*	
	if (!OkToRun)
	{
		*pExtErrorInfo = IODATA_EXT_ERROR_CANTRUN;
		return S_FALSE;
		};
	return (*pExtErrorInfo == IODATA_EXT_ERROR_OK) ? S_OK : S_FALSE;
*/
}

STDMETHODIMP CDBIO::Read(HSySalHANDLE hWnd, BYTE *pData, UINT *pExtErrorInfo, BYTE *FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	void **ppData = (void **)(BYTE *)pData;
	*ppData = 0;
	if (!OkToRun)
	{
		*pExtErrorInfo = IODATA_EXT_ERROR_CANTRUN;
		return S_FALSE;
		};
	if (!C.InputEnabled)
	{
		*pExtErrorInfo = IODATA_EXT_ERROR_DISABLED;
		return S_FALSE;
		};
	if (!FileName)
	{
		*pExtErrorInfo = IODATA_EXT_ERROR_UNKFORMAT;
		return E_INVALIDARG;
		};
	Identifier Id;
	try
	{
		char temp[256];
		strncpy(temp, (char *)FileName, 255);
		temp[255] = 0;
		char *token = strtok(temp, " ");
		strupr(token);
		if (strcmp(token, "TPID")) throw 0;
		int i;		
		for (i = 0; (i < 4) && (token = strtok(0, " ")) && (sscanf(token, "%d", &Id.Part[i]) == 1); i++);
		if (i < 4) throw 1;
		}
	catch (...)
	{
		*pExtErrorInfo = IODATA_EXT_ERROR_UNKFORMAT;
		return S_FALSE;
		};
	CDatabase DB;
	CString Temp;
	Temp.Format("DSN=%s;UID=%s;PWD=%s", C.DSN, C.UserName, C.Password);
	try
	{
		if (!DB.OpenEx(Temp, CDatabase::openReadOnly)) throw 0;
		}
	catch (...)
	{
		*pExtErrorInfo = IODATA_EXT_ERROR_OPEN;
		return S_FALSE;
		};
	CQueryRecordset RS(C.TrackPrediction, &DB);
	RS.SetId(Id);
	try
	{
		if (!RS.Open(CRecordset::snapshot)) throw 0;
		}
	catch (...)
	{
		*pExtErrorInfo = IODATA_EXT_ERROR_READ | DBP_TRACK_SECTION;
		return S_FALSE;
		};
	int i, j;
	i = 0;
	while (!RS.IsEOF()) 
	{
		i++;
		RS.MoveNext();
		};
	IO_DBPred_Tracks *pTracks = (IO_DBPred_Tracks *)(*ppData = CoTaskMemAlloc(sizeof(IO_DBPred_Tracks) + RS.GetRecordCount() * sizeof(DBPred_Track)));
	pTracks->Hdr.ID = Id;
	pTracks->pTracks = (pTracks->Hdr.Count = i) ? (DBPred_Track *)((BYTE *)*ppData + sizeof(IO_DBPred_Tracks)) : 0;
	pTracks->Hdr.Type.InfoType = DBP_HEADER_BYTES | DBP_TRACK_SECTION;
	pTracks->Hdr.Type.HeaderFormat = DBP_HEADER_TYPE;
	pTracks->Hdr.AdditionalDataSize = C.TrackPrediction.CountOfAdditionalFields;		
	for (i = 0; i < pTracks->Hdr.AdditionalDataSize; i++)
	{
		strcpy(pTracks->Hdr.AdditionalData[i].Name, C.TrackPrediction.AdditionalField[i].Name);
		pTracks->Hdr.AdditionalData[i].Type = C.TrackPrediction.AdditionalField[i].Type;
		};	
	RS.MoveFirst();
	for (i = 0; i < pTracks->Hdr.Count; i++)
	{
		if (RS.IsEOF())
		{
			*pExtErrorInfo = IODATA_EXT_ERROR_READ | DBP_TRACK_SECTION;
			if (pTracks->pTracks) 
			{				
				CoTaskMemFree(pTracks->pTracks);				
				*ppData = 0;
				RS.Close();
				};
			return S_FALSE;
			};
		RS.SyncFields();
		pTracks->pTracks[i].ID = RS.m_Id;
		for (j = 0; j < C.TrackPrediction.CountOfAdditionalFields; j++)
			if (C.TrackPrediction.AdditionalField[j].Name[0]) 
				memcpy(&pTracks->pTracks[i].AdditionalData[j], &RS.m_AdditionalFields[j], sizeof(RS.m_AdditionalFields[j]));
		RS.MoveNext();
		};
	RS.Close();
	*pExtErrorInfo = IODATA_EXT_ERROR_OK;
	return S_OK;
}

STDMETHODIMP CDBIO::GetStatus(UINT *pExtErrorInfo)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pExtErrorInfo = (OkToRun) ? IODATA_EXT_ERROR_OK : IODATA_EXT_ERROR_CANTRUN;
	return S_OK;
}
