// PlaygroundDoc.cpp : implementation of the CPlaygroundDoc class
//

#include "stdafx.h"
#include "Playground.h"
#include "PlaygroundDoc.h"
#include "PlaygroundView.h"
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlaygroundDoc

IMPLEMENT_DYNCREATE(CPlaygroundDoc, CDocument)

BEGIN_MESSAGE_MAP(CPlaygroundDoc, CDocument)
	//{{AFX_MSG_MAP(CPlaygroundDoc)
	ON_COMMAND(IDM_FILE_EXPORTTOXML, OnExportToXML)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#ifndef OLE_DISABLE
BEGIN_DISPATCH_MAP(CPlaygroundDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CPlaygroundDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()
#endif

// Note: we add support for IID_IPlayground to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {4EBD0A24-7386-11D3-A47B-B3DA25ED5623}
static const IID IID_IPlayground =
{ 0x4ebd0a24, 0x7386, 0x11d3, { 0xa4, 0x7b, 0xb3, 0xda, 0x25, 0xed, 0x56, 0x23 } };

#ifndef OLE_DISABLE
BEGIN_INTERFACE_MAP(CPlaygroundDoc, CDocument)
	INTERFACE_PART(CPlaygroundDoc, IID_IPlayground, Dispatch)
END_INTERFACE_MAP()
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlaygroundDoc construction/destruction

CPlaygroundDoc::CPlaygroundDoc()
{
	// TODO: add one-time construction code here

#ifndef OLE_DISABLE
	EnableAutomation();

	AfxOleLockApp();
#else
	CoInitializeEx(NULL, COINIT_MULTITHREADED);		
#endif

	Title = "New Project";
	LogFont.lfHeight = 0;
	LogFont.lfWidth = 0;
	LogFont.lfEscapement = 0;
	LogFont.lfOrientation = 0;
	LogFont.lfWeight = FW_SEMIBOLD;
	LogFont.lfItalic = FALSE;
	LogFont.lfUnderline = FALSE;
	LogFont.lfStrikeOut = FALSE;
	LogFont.lfCharSet = DEFAULT_CHARSET;
	LogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	LogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	LogFont.lfQuality = DEFAULT_QUALITY;
	LogFont.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;
	strcpy(LogFont.lfFaceName, "Arial");
	LayoutLocked = false;
}

CPlaygroundDoc::~CPlaygroundDoc()
{
	Layout.RemoveAll();
#ifndef OLE_DISABLE
	AfxOleUnlockApp();
#else
	CoUninitialize();
#endif
}

BOOL CPlaygroundDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	Layout.RemoveAll();
	Title = "New Project";
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPlaygroundDoc serialization

void CPlaygroundDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		int work = 0x1;
		ar.Write(&work, sizeof(work)); // File version
		ar.Write(&LogFont, sizeof(LogFont));		
		work = Title.GetLength();
		ar.Write(&work, sizeof(work));		
		ar.Write(Title.GetBuffer(work), work);
		Title.ReleaseBuffer();
		work = Layout.GetCount();
		ar.Write(&work, sizeof(work));
		POSITION POS = Layout.GetHeadPosition();
		while (POS)
		{
			CPersistentObject &rObj = Layout.GetNext(POS);
			ar.Write(&rObj.clsId, sizeof(rObj.clsId));
			ar.Write(&rObj.Name, sizeof(rObj.Name));
			ar.Write(&rObj.ConfigName, sizeof(rObj.ConfigName));
			ar.Write(&rObj.Position, sizeof(rObj.Position));
			ar.Write(&rObj.CountOfConnections, sizeof(rObj.CountOfConnections));
			int i;
			for (i = 0; i < rObj.CountOfConnections; i++)
			{
				SySalConnection TempConn;
				if (rObj.iObject) rObj.iObject->GetConnection(i, &TempConn);
				else TempConn.Type = SYSAL_CONN_TYPE_INTERFACE; // if new connection types come up, we should be careful...
				ar.Write(&TempConn.Type, sizeof(TempConn.Type));
				ar.Write(rObj.pConnections + i, sizeof(rObj.pConnections[i]));
				};
			};
		work = Executor.GetLength();
		ar.Write(&work, sizeof(work));
		ar.Write(Executor.GetBuffer(work), work);
		Executor.ReleaseBuffer();
		}
	else
	{
		// TODO: add loading code here
		POSITION POS = GetFirstViewPosition();
		CPlaygroundView *pView = (CPlaygroundView *)GetNextView(POS);
		LayoutLocked = false;
		int work = 0;
		char *temp = 0;
		Layout.RemoveAll();
		try
		{
			if (ar.Read(&work, sizeof(int)) < sizeof(int) || work != 0x1) throw 1;
			if (ar.Read(&LogFont, sizeof(LogFont)) < sizeof(LogFont)) throw 2;
			if (ar.Read(&work, sizeof(int)) < sizeof(int)) throw 3;			
			if (work > 0) 
			{
				temp = new char[work + 1];
				if (ar.Read(temp, work) < work) throw 4;
				temp[work] = 0;
				Title = temp;
				delete [] temp;
				temp = 0;
				}
			else Title = "";
			if (ar.Read(&work, sizeof(work)) < sizeof(work)) throw 5;
			int i;
			for (i = 0; i < work; i++)
			{				
				CLSID tempclsId;
				if (ar.Read(&tempclsId, sizeof(tempclsId)) < sizeof(tempclsId)) throw 6;
				CPersistentObject Obj(tempclsId);
				if (ar.Read(&Obj.Name, sizeof(Obj.Name)) < sizeof(Obj.Name)) throw 7;
				if (Obj.iObject && Obj.iObject->SetName(Obj.Name) != S_OK) throw 8;
				if (ar.Read(Obj.ConfigName, sizeof(Obj.ConfigName)) < sizeof(Obj.ConfigName)) throw 9;
				if (ar.Read(&Obj.Position, sizeof(Obj.Position)) < sizeof(Obj.Position)) throw 10;
				if (ar.Read(&Obj.CountOfConnections, sizeof(Obj.CountOfConnections)) < sizeof(Obj.CountOfConnections)) throw 11;
				Obj.ResetConnections(Obj.CountOfConnections);
				int j;
				for (j = 0; j < Obj.CountOfConnections; j++)
				{
					SySalConnection TempConn;
					if (ar.Read(&TempConn.Type, sizeof(TempConn.Type)) < sizeof(TempConn.Type)) throw 12;
					if (Obj.iObject) Obj.iObject->GetConnection(j, &TempConn);
					TempConn.pUnknown = 0;
					if (Obj.iObject) Obj.iObject->SetConnection(j, TempConn);
					if (ar.Read(Obj.pConnections + j, sizeof(Obj.pConnections[j])) < sizeof(Obj.pConnections[j])) throw 13;
					};
				if (Obj.iObject) pView->SetConfigManagerInterface(Obj.iObject);
				Layout.AddTail(Obj);				
				};
			if (ar.Read(&work, sizeof(work)) < sizeof(work)) throw 14;
			char *temp = new char[work + 1];
			if (ar.Read(temp, work) < work) 
			{
				delete [] temp;
				throw 15;
				};
			temp[work] = 0;
			Executor = temp;
			delete [] temp;
			POSITION POSEnd = Layout.GetHeadPosition();
			while (POSEnd)
			{
				CPersistentObject &rEnd = Layout.GetNext(POSEnd);
				for (i = 0; i < rEnd.CountOfConnections; i++)
				{
					if (rEnd.pConnections[i][0])
					{
						POSITION POSStart = Layout.GetHeadPosition();
						while (POSStart)
						{
							CPersistentObject &rStart = Layout.GetNext(POSStart);
							if (!strcmp(rStart.Name, rEnd.pConnections[i]))
							{
								SySalConnection TempConn;
								if (rEnd.iObject) rEnd.iObject->GetConnection(i, &TempConn);
								TempConn.pUnknown = rStart.iObject;
								if (rEnd.iObject) rEnd.iObject->SetConnection(i, TempConn);
								break;
								};
							};
						};
					};
				};
			}
		catch (...)
		{
			if (temp) delete [] temp;
			::MessageBox(0, "Wrong File Format", "File Error", MB_OK | MB_ICONERROR);
			Layout.RemoveAll();
			};

	}
}

/////////////////////////////////////////////////////////////////////////////
// CPlaygroundDoc diagnostics

#ifdef _DEBUG
void CPlaygroundDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPlaygroundDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPlaygroundDoc commands



CPersistentObject * CPlaygroundDoc::SeekByName(CString &Name)
{
	POSITION POS = Layout.GetHeadPosition();
	while (POS)
	{
		CPersistentObject &rObj = Layout.GetNext(POS);
		if (Name == rObj.Name) return &rObj;
		};
	return 0;
}

BOOL CPlaygroundDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return (!LayoutLocked) && CDocument::CanCloseFrame(pFrame);
}

void CPlaygroundDoc::OnExportToXML() 
{
	// TODO: Add your command handler code here
	CFileDialog	MyDlg(FALSE, ".xml", NULL, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_EXPLORER, "XML files (*.xml)|*.xml|All files (*.*)|*.*|||");
	MyDlg.m_ofn.lpstrTitle = "Export layout to XML file";
	if (MyDlg.DoModal() == IDOK)
	{
		try
		{
			CStdioFile File(MyDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
			if (!ExportLayoutToXML(&File)) MessageBox(0, "Error exporting XML file", "File Error", MB_ICONERROR);
			}
		catch (...)
		{
			MessageBox(0, "Can't open the specified file for writing!", "File Error", MB_ICONERROR);
			}
		}
}

bool CPlaygroundDoc::ExportLayoutToXML(CFile *pFile)
{
	static char XMLhead[] = "<?xml version=\"1.0\" ?>";
	static char XMLscanningnode[] = "scanning";
	static char XMLscanningtitle[] = "title";
	static char XMLscanningexecutor[] = "executor";
	static char XMLobjectnode[] = "objects";
	static char XMLobject[] = "object";
	static char XMLobjclass[] = "class";
	static char XMLobjclsid[] = "clsid";
	static char XMLobjname[] = "name";
	static char XMLconfig[] = "config";
	static char XMLconfigname[] = "name";
	static char XMLconnectionnode[] = "connections";
	static char XMLconnection[] = "connection";
	static char XMLconnbegin[] = "begin";
	static char XMLconnend[] = "end";
	static char XMLconnslot[] = "slot";
	static char parname[SYSAL_MAXCONFIG_ENTRY_NAME_LEN + 1];
	static char parvalue[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN + 1];

	POSITION POS;

	WriteString(pFile, XMLhead);
	WriteString(pFile, "<"); WriteString(pFile, XMLscanningnode); WriteString(pFile, " "); WriteString(pFile, XMLscanningtitle); WriteString(pFile, "=\""); WriteString(pFile, Title.GetBuffer(1)); WriteString(pFile, "\" "); Title.ReleaseBuffer();
	WriteString(pFile, XMLscanningexecutor); WriteString(pFile, "=\""); WriteString(pFile, Executor.GetBuffer(1)); WriteString(pFile, ""); WriteString(pFile, "\">\n"); Executor.ReleaseBuffer();
	WriteIndent(pFile, 1); WriteString(pFile, "<"); WriteString(pFile, XMLobjectnode); WriteString(pFile, ">\n");

	POS = Layout.GetHeadPosition();
	int i;
	while (POS)
	{
		ConnectionName cn;
		static char clsidstr[256];
		CPersistentObject &o = Layout.GetNext(POS);
		sprintf(clsidstr, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", o.clsId.Data1, o.clsId.Data2, o.clsId.Data3, o.clsId.Data4[0], o.clsId.Data4[1], o.clsId.Data4[2], o.clsId.Data4[3], o.clsId.Data4[4], o.clsId.Data4[5], o.clsId.Data4[6], o.clsId.Data4[7]);
		o.iObject->GetClassName(cn);
		WriteIndent(pFile, 2); WriteString(pFile, "<"); WriteString(pFile, XMLobject); 
		WriteString(pFile, " "); WriteString(pFile, XMLobjclass); WriteString(pFile, "=\""); WriteString(pFile, cn); WriteString(pFile, "\"");
		WriteString(pFile, " "); WriteString(pFile, XMLobjclsid); WriteString(pFile, "=\""); WriteString(pFile, clsidstr); WriteString(pFile, "\"");
		WriteString(pFile, " "); WriteString(pFile, XMLobjname); WriteString(pFile, "=\""); WriteString(pFile, o.Name); WriteString(pFile, "\"");
		if (o.ConfigName[0] != 0)
		{
			WriteString(pFile, ">\n");
			WriteIndent(pFile, 3); WriteString(pFile, "<"); WriteString(pFile, XMLconfig); WriteString(pFile, " "); WriteString(pFile, XMLconfigname); WriteString(pFile, "=\""); WriteString(pFile, o.ConfigName); WriteString(pFile, "\">\n");
			SySalConfig config;
			config.CountOfItems = 0;
			config.Name[0] = 0;
			config.pItems = 0;
			CString configname = o.ConfigName;
			CPlaygroundView::LoadConfig(config, configname);
			for (i = 0; i < config.CountOfItems; i++)
			{
				strncpy(parname, config.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
				parname[SYSAL_MAXCONFIG_ENTRY_NAME_LEN] = 0;
				WriteIndent(pFile, 4); WriteString(pFile, "<"); WriteString(pFile, parname); WriteString(pFile, ">");
				strncpy(parvalue, config.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
				parvalue[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN] = 0;
				WriteString(pFile, parvalue); WriteString(pFile, "</"); WriteString(pFile, parname); WriteString(pFile, ">\n");
				}
			if (config.pItems) CoTaskMemFree(config.pItems);
			WriteIndent(pFile, 3); WriteString(pFile, "</"); WriteString(pFile, XMLconfig); WriteString(pFile, ">\n");
			WriteIndent(pFile, 2); WriteString(pFile, "</"); WriteString(pFile, XMLobject); WriteString(pFile, ">\n");
			}
		else WriteString(pFile, "/>\n");
		}
	WriteIndent(pFile, 1); WriteString(pFile, "</"); WriteString(pFile, XMLobjectnode); WriteString(pFile, ">\n");
	WriteIndent(pFile, 1); WriteString(pFile, "<"); WriteString(pFile, XMLconnectionnode); WriteString(pFile, ">\n");
	POS = Layout.GetHeadPosition();
	while (POS)
	{
		CPersistentObject &o = Layout.GetNext(POS);
		for (i = 0; i < o.CountOfConnections; i++)
		{
			SySalConnection conn;
			o.iObject->GetConnection(i, &conn);
			if (conn.pUnknown)
			{
				WriteIndent(pFile, 2); WriteString(pFile, "<"); WriteString(pFile, XMLconnection); WriteString(pFile, " ");
				WriteString(pFile, XMLconnend); WriteString(pFile, "=\""); WriteString(pFile, o.Name); WriteString(pFile, "\" ");
				WriteString(pFile, XMLconnslot); WriteString(pFile, "=\""); WriteString(pFile, conn.Name); WriteString(pFile, "\" ");
				WriteString(pFile, XMLconnbegin); WriteString(pFile, "=\""); WriteString(pFile, o.pConnections[i]); WriteString(pFile, "\"/>\n");
				}
			}
		}
	WriteIndent(pFile, 1); WriteString(pFile, "</"); WriteString(pFile, XMLconnectionnode); WriteString(pFile, ">\n");
	WriteString(pFile, "</"); WriteString(pFile, XMLscanningnode); WriteString(pFile, ">"); 
	return true;
	}

void CPlaygroundDoc::WriteIndent(CFile *pFile, int level)
{
	char *pblanks = new char [2 * level + 1];
	int i;
	for (i = 0; i < level; i++)
		pblanks[2 * i] = pblanks[2 * i + 1] = ' ';
	pblanks[2 * i] = 0;
	pFile->Write(pblanks, 2 * level);
	delete [] pblanks;
}

void CPlaygroundDoc::WriteString(CFile *pFile, char *pText)
{
	pFile->Write(pText, strlen(pText));
}

#include "..\Common\SySalObj2_i.c"
