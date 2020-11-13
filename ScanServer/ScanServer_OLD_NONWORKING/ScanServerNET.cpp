#include "StdAfx.h"
#include "ScanServerNET.h"
#include <memory.h>
#include "SySalObj2.h"
#include "Connection.h"

using namespace SySal::DAQSystem;

void ScanServer::Connect()
{
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	m_IsLoaded = m_IsBusy = false;
	SetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);	
}

void ScanServer::Disconnect()
{
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	m_IsLoaded = m_IsBusy = false;
	SetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
}

Object *ScanServer::InitializeLifetimeService()
{
	return 0;	
}

ScanServer::ScanServer()
	: pContext(0), pSetScanLayoutCallback(0), pAddStringCallback(0), pCreateObjectInWndThreadCallback(0)
{
	pMessage = 0;
	m_IsLoaded = m_IsBusy = false;
	HMessageMutex = CreateMutex(NULL, FALSE, NULL);
	HProcessed = CreateEvent(NULL, FALSE, FALSE, NULL);
	HFreeMutex = CreateMutex(NULL, FALSE, NULL);
	LayoutObjCount = 0;
	pLayoutObjs = 0;
	ResetLayout();
}

ScanServer::~ScanServer(void)
{	
	if (pMessage)
	{
		WaitForSingleObject(HMessageMutex, INFINITE);
		delete pMessage;
		pMessage = 0;
		ReleaseMutex(HMessageMutex);
	}
	PulseEvent(HProcessed);	
	CloseHandle(HFreeMutex);
	CloseHandle(HMessageMutex);
	CloseHandle(HProcessed);
	ResetLayout();
	if (pLayoutObjs) free(pLayoutObjs);
	iCOMSrv->Release();
}

void ScanServer::ResetLayout()
{
	int i;
	for (i = 0; i < LayoutObjCount; pLayoutObjs[i++]->Release());
	pLayoutObjs = (ISySalObject **)realloc(pLayoutObjs, sizeof(ISySalObject *) * (MaxLayoutObjs = 8));
	LayoutObjCount = 0;
}

void ScanServer::AddObjToLayout(ISySalObject *iObj)
{
	pLayoutObjs[LayoutObjCount++] = iObj;
	if (LayoutObjCount >= MaxLayoutObjs)
		pLayoutObjs = (ISySalObject **)realloc(pLayoutObjs, sizeof(ISySalObject *) * (MaxLayoutObjs *= 2));
}

bool ScanServer::Scan(SySal::DAQSystem::Scanning::ZoneDesc zone)
{
	WaitForSingleObject(HFreeMutex, INFINITE);
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	ScanZoneStart *p = new ScanZoneStart;
	pMessage = p;
	p->OpCode = SCANSRV_SCAN_ZONE_START;
	p->Size = sizeof(ScanZoneStart);
	p->Id.Part[0] = zone.Id.Part0;
	p->Id.Part[1] = zone.Id.Part1;
	p->Id.Part[2] = zone.Id.Part2;
	p->Id.Part[3] = zone.Id.Part3;
	p->MinX = 0;
	p->MinY = 0;
	p->MaxX = 0;
	p->MaxY = 0;
	p->MinX = zone.MinX;
	p->MinY = zone.MinY;
	p->MaxX = zone.MaxX;
	p->MaxY = zone.MaxY;
	int i;
	for (i = 0; i < 255 && i < zone.Outname->Length; i++)
		p->OutName[i] = zone.Outname->Chars[i];
	p->OutName[i] = 0;
	m_IsBusy = true;
	static char msgstr[512];
	sprintf(msgstr, "\r\nScanning zone %d/%d/%d/%d MinX: %.1f MaxX: %.1f MinY: %.1f MaxY: %.1f ... ", 
		p->Id.Part[0], p->Id.Part[1], p->Id.Part[2], p->Id.Part[3],
		p->MinX, p->MaxX, p->MinY, p->MaxY);
	((void (*)(void *, char *))pAddStringCallback)(pContext, msgstr);
	ResetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
	HANDLE HEvs[2] = {HProcessed, HMessageMutex};
	WaitForMultipleObjects(2, HEvs, TRUE, INFINITE);

	bool ret = (pMessage && (pMessage->OpCode == SCANSRV_OK));
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	};

	m_IsBusy = false;
	ResetEvent(HProcessed);
	((void (*)(void *, char *))pAddStringCallback)(pContext, ret ? "OK" : "FAILED");
	ReleaseMutex(HMessageMutex);
	ReleaseMutex(HFreeMutex);
	return ret;
}

bool ScanServer::LoadPlate(SySal::DAQSystem::Scanning::MountPlateDesc plate)
{
	WaitForSingleObject(HFreeMutex, INFINITE);
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	LoadPlateStart *p = new LoadPlateStart;
	pMessage = p;
	p->OpCode = SCANSRV_LOAD_PLATE;
	p->Size = sizeof(LoadPlateStart);
	p->Id.Part[0] = plate.Id.Part0;
	p->Id.Part[1] = plate.Id.Part1;
	p->Id.Part[2] = plate.Id.Part2;
	p->Id.Part[3] = plate.Id.Part3;
	int i;
	for (i = 0; i < 255 && i < plate.TextDesc->Length; i++)
		p->TextId[i] = plate.TextDesc->Chars[i];
	p->TextId[i] = 0;
	static char msgstr[512];
	sprintf(msgstr, "\r\nLoading plate %d/%d/%d/%d ... ", 
		p->Id.Part[0], p->Id.Part[1], p->Id.Part[2], p->Id.Part[3]);
	((void (*)(void *, char *))pAddStringCallback)(pContext, msgstr);
	ResetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
	HANDLE HEvs[2] = {HProcessed, HMessageMutex};
	WaitForMultipleObjects(2, HEvs, TRUE, INFINITE);

	bool ret = (pMessage && (pMessage->OpCode == SCANSRV_OK));
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	};

	((void (*)(void *, char *))pAddStringCallback)(pContext, ret ? "OK" : "FAILED");
	ResetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
	ReleaseMutex(HFreeMutex);
	return ret;	
}

bool ScanServer::UnloadPlate()
{
	WaitForSingleObject(HFreeMutex, INFINITE);
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	pMessage = new ScanSrvMessage;
	pMessage->OpCode = SCANSRV_UNLOAD_PLATE;
	pMessage->Size = sizeof(ScanSrvMessage);
	((void (*)(void *, char *))pAddStringCallback)(pContext, "\r\nUnloading plate .... ");
	ResetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
	HANDLE HEvs[2] = {HProcessed, HMessageMutex};
	WaitForMultipleObjects(2, HEvs, TRUE, INFINITE);

	bool ret = (pMessage && (pMessage->OpCode == SCANSRV_OK));
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	};

	((void (*)(void *, char *))pAddStringCallback)(pContext, ret ? "OK" : "FAILED");
	ResetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
	ReleaseMutex(HFreeMutex);
	return ret;	
}

bool ScanServer::Receive(ScanSrvMessage *p)
{
	bool ret = false;
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (!pMessage) 
	{
		p->Size = 0;
		p->OpCode = SCANSRV_NULL;
		ret = false;
	}
	else
	{
		if (p->Size >= pMessage->Size)
		{
			memcpy(p, pMessage, pMessage->Size);
			delete pMessage;
			pMessage = 0;
			ret = true;
		}
		else
		{
			p->OpCode = pMessage->OpCode;
			p->Size = pMessage->Size;
			ret = false;
		}
	}
	ReleaseMutex(HMessageMutex);
	return ret;
}

bool ScanServer::Send(ScanSrvMessage *pmsg)
{
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	switch (pmsg->OpCode)
	{
		case SCANSRV_OK:
		case SCANSRV_FAILED:
		case SCANSRV_NOTACKNOWLEDGED:
											pMessage = new ScanSrvMessage();
											pMessage->OpCode = pmsg->OpCode;
											pMessage->Size = sizeof(ScanSrvMessage);
											break;

		case SCANSRV_SET_BUSYSTATE:
											if (m_IsBusy = ((SetBusyState *)pmsg)->Busy) 
											{
												m_ZoneId.Part0 = ((SetBusyState *)pmsg)->ZoneId.Part[0];
												m_ZoneId.Part1 = ((SetBusyState *)pmsg)->ZoneId.Part[1];
												m_ZoneId.Part2 = ((SetBusyState *)pmsg)->ZoneId.Part[2];
												m_ZoneId.Part3 = ((SetBusyState *)pmsg)->ZoneId.Part[3];
											}
											ReleaseMutex(HMessageMutex);
											return true;
		
		case SCANSRV_SET_LOADEDSTATE:
											if (m_IsLoaded = ((SetLoadedState *)pmsg)->Loaded) 
											{
												m_PlateId.Part0 = ((SetLoadedState *)pmsg)->PlateId.Part[0];
												m_PlateId.Part1 = ((SetLoadedState *)pmsg)->PlateId.Part[1];
												m_PlateId.Part2 = ((SetLoadedState *)pmsg)->PlateId.Part[2];
												m_PlateId.Part3 = ((SetLoadedState *)pmsg)->PlateId.Part[3];
											}
											ReleaseMutex(HMessageMutex);
											return true;
		
		default:							pMessage = new ScanSrvMessage();
											pMessage->OpCode = SCANSRV_NOTACKNOWLEDGED;
											pMessage->Size = sizeof(ScanSrvMessage);
											break;
	}
	SetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
	return true;
}

bool ScanServer::SetSingleParameter(System::String *objectname, System::String *parametername, System::String *parametervalue)
{
	WaitForSingleObject(HFreeMutex, INFINITE);
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	SetParameter *p = new SetParameter;
	pMessage = p;

	p->OpCode = SCANSRV_SET_PARAMETER;
	p->Size = sizeof(p);
	int i;
	for (i = 0; i < 255 && i < objectname->Length; i++)
        p->ObjName[i] = objectname->Chars[i];
	p->ObjName[i] = 0;
	for (i = 0; i < 255 && i < parametername->Length; i++)
        p->ParamName[i] = parametername->Chars[i];
	p->ParamName[i] = 0;
	for (i = 0; i < 255 && i < parametervalue->Length; i++)
        p->ParamValue[i] = parametervalue->Chars[i];
	p->ParamValue[i] = 0;
	static char msgstr[512];	
	sprintf(msgstr, "\r\nSetting parameter %s[%s] = %s", p->ObjName, p->ParamName, p->ParamValue);
	((void (*)(void *, char *))pAddStringCallback)(pContext, msgstr);
	ResetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
	HANDLE HEvs[2] = {HProcessed, HMessageMutex};
	WaitForMultipleObjects(2, HEvs, TRUE, INFINITE);

	bool ret = (pMessage && (pMessage->OpCode == SCANSRV_OK));
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	};

	ResetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
	ReleaseMutex(HFreeMutex);
	return ret;
}

bool ScanServer::SetObjectConfiguration(System::String *objectname, System::String *xmlconfig)
{
	WaitForSingleObject(HFreeMutex, INFINITE);
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	SetConfig *p = new SetConfig;
	pMessage = p;

	p->OpCode = SCANSRV_SET_CONFIG;
	p->Size = sizeof(p);
	int i;
	for (i = 0; i < 255 && i < objectname->Length; i++)
        p->ObjName[i] = objectname->Chars[i];
	p->ObjName[i] = 0;
	for (i = 0; i < 8191 && i < xmlconfig->Length; i++)
        p->Config[i] = xmlconfig->Chars[i];
	p->Config[i] = 0;
	ResetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
	HANDLE HEvs[2] = {HProcessed, HMessageMutex};
	WaitForMultipleObjects(2, HEvs, TRUE, INFINITE);

	bool ret = (pMessage && (pMessage->OpCode == SCANSRV_OK));
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	};

	ResetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
	ReleaseMutex(HFreeMutex);
	return ret;
}

bool ScanServer::SetScanLayout(System::String *xmllayout)
{
	WaitForSingleObject(HFreeMutex, INFINITE);	
	((void (*)(void *, char *))pAddStringCallback)(pContext, "Resetting layout\r\n");
	//bool ret = ((bool (*)(void *, System::String *))pSetScanLayoutCallback)(pContext, xmllayout);
	static char tempstr[512];
	ResetLayout();
	try
	{
		System::Xml::XmlDocument *pXmlDoc = new System::Xml::XmlDocument();
		pXmlDoc->LoadXml(xmllayout);
		System::Xml::XmlElement *pXmlRoot = pXmlDoc->DocumentElement;
		System::Xml::XmlNode *pXmlSection;
		for (pXmlSection = pXmlRoot->FirstChild; 
			pXmlSection && 
			(System::String::Compare(pXmlSection->Name, S"objects", false)); 
			pXmlSection = pXmlSection->NextSibling);
		System::Xml::XmlNode *pXmlObjects;
		for (pXmlObjects = pXmlSection->FirstChild; pXmlObjects; pXmlObjects = pXmlObjects->NextSibling)
		{
			int i;
			char *clsidstr;
			for (i = 0; i < pXmlObjects->Attributes->Count &&
				System::String::Compare(pXmlObjects->Attributes->Item(i)->Name, "clsid", false); i++);
			((void (*)(void *, char *))pAddStringCallback)(pContext, clsidstr = String2Char(pXmlObjects->Attributes->Item(i)->Value));
			((void (*)(void *, char *))pAddStringCallback)(pContext, "\t");
			ISySalObject *iOb = ObjFromCLSIDStr(clsidstr);
			if (!iOb) throw new System::Exception(S"Object creation failure.");
			AddObjToLayout(iOb);
			ConnectionName conn;
			iOb->GetClassName(conn);
			iOb->EnableMonitor(true);
			conn[sizeof(conn) - 1] = 0;
/*			
			for (i = 0; i < pXmlObjects->Attributes->Count &&
				System::String::Compare(pXmlObjects->Attributes->Item(i)->Name, "class", false); i++);
			((void (*)(void *, char *))pAddStringCallback)(pContext, String2Char(pXmlObjects->Attributes->Item(i)->Value));
*/
			((void (*)(void *, char *))pAddStringCallback)(pContext, conn);
			((void (*)(void *, char *))pAddStringCallback)(pContext, "\t");
			for (i = 0; i < pXmlObjects->Attributes->Count &&
				System::String::Compare(pXmlObjects->Attributes->Item(i)->Name, "name", false); i++);
			strncpy(conn, String2Char(pXmlObjects->Attributes->Item(i)->Value), sizeof(conn) - 1);
			((void (*)(void *, char *))pAddStringCallback)(pContext, "\"");
			((void (*)(void *, char *))pAddStringCallback)(pContext, conn);
			((void (*)(void *, char *))pAddStringCallback)(pContext, "\"\r\n");
		}
		
	}
	catch (System::Exception *x)
	{
		ResetLayout();
		((void (*)(void *, char *))pAddStringCallback)(pContext, String2Char(x->Message));
		((void (*)(void *, char *))pAddStringCallback)(pContext, "\r\n");	
		return false;
	}
	ReleaseMutex(HFreeMutex);
	return true;
}

bool ScanServer::get_IsBusy()
{
	return m_IsBusy;
}

bool ScanServer::get_IsLoaded()
{
	return m_IsLoaded;
}

SySal::BasicTypes::Identifier ScanServer::get_CurrentZone()
{
	if (m_IsLoaded && m_IsBusy) return m_ZoneId;
	throw new System::Exception("No zone currently being scanned.");
}

SySal::BasicTypes::Identifier ScanServer::get_CurrentPlate()
{
	if (m_IsLoaded) return m_PlateId;
	throw new System::Exception("No plate currently loaded.");
}

bool ScanServer::TestComm(int h)
{
/*
	Console::WriteLine("Test called");
	Console::WriteLine(h);
*/
	return true;
}

ScanServer *ScanServer::Create(void *pcontext, ISySalObject __nogc *(*pcreateobjectinwndthreadcallback)(void __nogc *pcontext, CLSID &), bool (*psetscanlayoutcallback)(void *, System::String *), void (*paddstringcallback)(void *, char *), ISySalObject __nogc *icomsrv)
{
	ScanServer *pNETSrv = new ScanServer;
	pNETSrv->pContext = pcontext;
	pNETSrv->pCreateObjectInWndThreadCallback = pcreateobjectinwndthreadcallback;
	pNETSrv->pSetScanLayoutCallback = psetscanlayoutcallback;
	pNETSrv->pAddStringCallback = paddstringcallback;
	pNETSrv->iCOMSrv = icomsrv;
	pNETSrv->iCOMSrv->AddRef();
	return pNETSrv;
}
			
Tcp::TcpChannel *ScanServer::RegisterChannelAndServer(ScanServer *pNETSrv)
{
	Tcp::TcpChannel *pChannel = new Tcp::TcpChannel((int)SySal::DAQSystem::OperaPort::ScanServer);
	ChannelServices::RegisterChannel(pChannel);
	RemotingServices::Marshal(pNETSrv, S"ScanServer.rem");
	return pChannel;
}
			
void ScanServer::UnregisterChannelAndServer(Tcp::TcpChannel *pChannel, ScanServer *pNETSrv)
{
	RemotingServices::Disconnect(pNETSrv);
	ChannelServices::UnregisterChannel(pChannel);
}

char *ScanServer::String2Char(System::String *str)
{
	static char tempstr[512];
	int i;
	for (i = 0; i < str->Length; i++)
		tempstr[i] = str->Chars[i];
	tempstr[i] = 0;
	return tempstr;
}

ISySalObject __nogc *ScanServer::ObjFromCLSIDStr(char *clsidstr)
{
	if (!strnicmp(clsidstr, "{E8F1A43B-C0D3-4061-8E78-5C2A25C158F8}", 38))
	{
		iCOMSrv->AddRef();
		return iCOMSrv;
	}
	static CLSID ret;
	if (clsidstr[0] != '{') return 0;
	if (clsidstr[37] != '}') return 0;
	if (clsidstr[9] != '-') return 0;
	if (clsidstr[14] != '-') return 0;
	if (clsidstr[19] != '-') return 0;
	if (clsidstr[24] != '-') return 0;
	if (sscanf(clsidstr + 1, "%08X", &ret.Data1) != 1) return 0;
	if (sscanf(clsidstr + 10, "%04X", &ret.Data2) != 1) return 0;
	if (sscanf(clsidstr + 15, "%04X", &ret.Data3) != 1) return 0;
	if (sscanf(clsidstr + 20, "%02X", &ret.Data4[0]) != 1) return 0;
	if (sscanf(clsidstr + 22, "%02X", &ret.Data4[1]) != 1) return 0;
	if (sscanf(clsidstr + 25, "%02X", &ret.Data4[2]) != 1) return 0;
	if (sscanf(clsidstr + 27, "%02X", &ret.Data4[3]) != 1) return 0;
	if (sscanf(clsidstr + 29, "%02X", &ret.Data4[4]) != 1) return 0;
	if (sscanf(clsidstr + 31, "%02X", &ret.Data4[5]) != 1) return 0;
	if (sscanf(clsidstr + 33, "%02X", &ret.Data4[6]) != 1) return 0;
	if (sscanf(clsidstr + 35, "%02X", &ret.Data4[7]) != 1) return 0;

	ISySalObject *iRet2 = ((ISySalObject *(*)(void *pcontext, CLSID &))pCreateObjectInWndThreadCallback)(pContext, ret);
	if (iRet2) return iRet2;

	ISySalObject *iRet = 0;
	if (CoCreateInstance(ret, NULL, CLSCTX_INPROC_SERVER, IID_ISySalObject, (void **)&iRet) != S_OK)
	{
		MessageBox(0, "failed", "hello", MB_OK);
		if (iRet) iRet->Release();
		return 0;
	}

	return iRet;
}