#include "StdAfx.h"
#include "ScanServerNET.h"
#include <memory.h>
#include "SySalObj2.h"
#include "Connection.h"
#include "atlbase.h"
#include "MachineDefaults.h"

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
	m_AcceptScanRequests = true;
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
	m_AcceptScanRequests = false;
	SetEvent(HProcessed);
	ReleaseMutex(HMessageMutex);
}

Object *ScanServer::InitializeLifetimeService()
{
	return 0;	
}

ScanServer::ScanServer()
	: pContext(0), pAddStringCallback(0), pCreateObjectInWndThreadCallback(0), pDeleteObjectInWndThreadCallback(0)
{
	pMessage = 0;
	m_IsLoaded = m_IsBusy = false;
	m_AcceptScanRequests = false;
	HMessageMutex = CreateMutex(NULL, FALSE, NULL);
	HProcessed = CreateEvent(NULL, FALSE, FALSE, NULL);
	HFreeMutex = CreateMutex(NULL, FALSE, NULL);
	HNotifyStatusChangeEvent = (HSySalHANDLE)CreateEvent(NULL, TRUE, FALSE, NULL);
	LayoutObjCount = 0;
	pLayoutObjs = 0;
	pCLSIDs = 0;
	iExecutor = 0;
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
	CloseHandle((HANDLE)HNotifyStatusChangeEvent);
	ResetLayout();
	if (pLayoutObjs) free(pLayoutObjs);
	if (pCLSIDs) free(pCLSIDs);
	if (iCOMSrv) iCOMSrv->Release();
}

void ScanServer::ResetLayoutForShutDown(ScanServer *pNETSrv)
{
	pNETSrv->ResetLayout();
}

void ScanServer::ResetLayout()
{
	if (iExecutor)
	{
		long execstatus;
		iExecutor->AsyncCheckStatus(&execstatus);
		if (execstatus != SYSAL_ASYNC_STATUS_IDLE)
		{
			ResetEvent((HANDLE)HNotifyStatusChangeEvent);
			iExecutor->AsyncStop();
			WaitForSingleObject((HANDLE)HNotifyStatusChangeEvent, INFINITE);	
			do
			{
				iExecutor->AsyncCheckStatus(&execstatus);
			}
			while (execstatus != SYSAL_ASYNC_STATUS_IDLE);
/*
			if (execstatus != SYSAL_ASYNC_STATUS_IDLE)
				((void (*)(void *, char *))pAddStringCallback)(pContext, "Unable to stop execution. Administrator help is required. An error is likely to occur after this call.");				
*/
		}
	}
	int i;
	for (i = 0; i < LayoutObjCount; ((void (*)(void *, ISySalObject *))pDeleteObjectInWndThreadCallback)(pContext, pLayoutObjs[i++]));
	pLayoutObjs = (ISySalObject **)realloc(pLayoutObjs, sizeof(ISySalObject *) * (MaxLayoutObjs = 8));
	pCLSIDs = (CLSID *)realloc(pCLSIDs, sizeof(CLSID) * MaxLayoutObjs);
	LayoutObjCount = 0;
	iExecutor = 0;
}

void ScanServer::AddObjToLayout(ISySalObject *iObj, CLSID &clsid)
{	
	pCLSIDs[LayoutObjCount] = clsid;
	pLayoutObjs[LayoutObjCount] = iObj;	
	if (++LayoutObjCount >= MaxLayoutObjs)
	{
		pLayoutObjs = (ISySalObject **)realloc(pLayoutObjs, sizeof(ISySalObject *) * (MaxLayoutObjs *= 2));
		pCLSIDs = (CLSID *)realloc(pCLSIDs, sizeof(CLSID) * MaxLayoutObjs);
	}
}

bool ScanServer::Scan(SySal::DAQSystem::Scanning::ZoneDesc *zone)
{
	WaitForSingleObject(HFreeMutex, INFINITE);
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (m_AcceptScanRequests == false) return false;
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	ScanZoneStart *p = new ScanZoneStart;
	pMessage = p;
	p->OpCode = SCANSRV_SCAN_ZONE_START;
	p->Size = sizeof(ScanZoneStart);
	p->Id.Part[0] = m_PlateId.Part0;
	p->Id.Part[1] = m_PlateId.Part1;
	p->Id.Part[2] = zone->Series;
	p->Id.Part[3] = 0;
/*
	p->Id.Part[0] = zone->Id.Part0;
	p->Id.Part[1] = zone->Id.Part1;
	p->Id.Part[2] = zone->Id.Part2;
	p->Id.Part[3] = zone->Id.Part3;
*/
	p->MinX = 0;
	p->MinY = 0;
	p->MaxX = 0;
	p->MaxY = 0;
	p->MinX = zone->MinX;
	p->MinY = zone->MinY;
	p->MaxX = zone->MaxX;
	p->MaxY = zone->MaxY;
	int i;
	for (i = 0; i < 255 && i < zone->Outname->Length; i++)
		p->OutName[i] = zone->Outname->Chars[i];
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

bool ScanServer::ScanAndMoveToNext(SySal::DAQSystem::Scanning::ZoneDesc *zone, SySal::BasicTypes::Rectangle *rect)
{
	WaitForSingleObject(HFreeMutex, INFINITE);
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (m_AcceptScanRequests == false) return false;
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	ScanZoneStartAndPreloadNext *p = new ScanZoneStartAndPreloadNext;
	pMessage = p;
	p->OpCode = SCANSRV_SCAN_ZONE_START_PRELOAD_NEXT;
	p->Size = sizeof(ScanZoneStartAndPreloadNext);
	p->Id.Part[0] = m_PlateId.Part0;
	p->Id.Part[1] = m_PlateId.Part1;
	p->Id.Part[2] = zone->Series;
	p->Id.Part[3] = 0;
/*
	p->Id.Part[0] = zone->Id.Part0;
	p->Id.Part[1] = zone->Id.Part1;
	p->Id.Part[2] = zone->Id.Part2;
	p->Id.Part[3] = zone->Id.Part3;
*/
	p->MinX = 0;
	p->MinY = 0;
	p->MaxX = 0;
	p->MaxY = 0;
	p->MinX = zone->MinX;
	p->MinY = zone->MinY;
	p->MaxX = zone->MaxX;
	p->MaxY = zone->MaxY;
	int i;
	for (i = 0; i < 255 && i < zone->Outname->Length; i++)
		p->OutName[i] = zone->Outname->Chars[i];
	p->OutName[i] = 0;
	p->NextMinX = rect->MinX;
	p->NextMinY = rect->MinY;
	p->NextMaxX = rect->MaxX;
	p->NextMaxY = rect->MaxY;
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

bool ScanServer::LoadPlate(SySal::DAQSystem::Scanning::MountPlateDesc *plate)
{
	WaitForSingleObject(HFreeMutex, INFINITE);
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (m_AcceptScanRequests == false) return false;	
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	LoadPlateStart *p = new LoadPlateStart;
	pMessage = p;
	p->OpCode = SCANSRV_LOAD_PLATE;
	p->Size = sizeof(LoadPlateStart);
	p->Id.Part[0] = plate->BrickId;
	p->Id.Part[1] = plate->PlateId;
	p->Id.Part[2] = 0;
	p->Id.Part[3] = 0;
/*
	p->Id.Part[0] = plate->Id.Part0;
	p->Id.Part[1] = plate->Id.Part1;
	p->Id.Part[2] = plate->Id.Part2;
	p->Id.Part[3] = plate->Id.Part3;
*/
	int i;
	for (i = 0; i < (sizeof(p->TextId) - 1) && i < plate->TextDesc->Length; i++)
		p->TextId[i] = plate->TextDesc->Chars[i];
	p->TextId[i] = 0;
	for (i = 0; i < (sizeof(p->MapInitString) - 1) && i < plate->MapInitString->Length; i++)
		p->MapInitString[i] = plate->MapInitString->Chars[i];
	p->MapInitString[i] = 0;
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
	if (m_AcceptScanRequests == false) return false;
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
	((void (*)(void *, char *))pAddStringCallback)(pContext, "\r\nResetting layout...\r\n");
	static char tempstr[512];

	if (iExecutor)
	{
		long execstatus;
		iExecutor->AsyncCheckStatus(&execstatus);
		if (execstatus != SYSAL_ASYNC_STATUS_IDLE)
		{
			ResetEvent((HANDLE)HNotifyStatusChangeEvent);
			iExecutor->AsyncStop();
			WaitForSingleObject((HANDLE)HNotifyStatusChangeEvent, INFINITE);	
			do
			{
				iExecutor->AsyncCheckStatus(&execstatus);
			}
			while (execstatus != SYSAL_ASYNC_STATUS_IDLE);
/*
			if (execstatus != SYSAL_ASYNC_STATUS_IDLE)
				((void (*)(void *, char *))pAddStringCallback)(pContext, "Unable to stop execution. Administrator help is required. An error is likely to occur after this call.");				
*/
		}
		iExecutor = 0;
	}

	//ResetLayout();
	if (xmllayout == S"") 
	{
		ResetLayout();
		((void (*)(void *, char *))pAddStringCallback)(pContext, "Layout empty.\r\n");
		return true;
	}
	int oldobjcount, maxoldobjcount;
	maxoldobjcount = 8;
	oldobjcount = 0;
	ISySalObject **poldobjs = (ISySalObject **)malloc(sizeof(ISySalObject *) * maxoldobjcount);
	CLSID *poldclsids = (CLSID *)malloc(sizeof(CLSID) * maxoldobjcount);
	try
	{
		System::String *Executor;
		int i, j;
		System::Xml::XmlDocument *pXmlDoc = new System::Xml::XmlDocument();
		pXmlDoc->LoadXml(xmllayout);
		System::Xml::XmlElement *pXmlRoot = pXmlDoc->DocumentElement;
		if (System::String::Compare(pXmlRoot->Name, S"scanning", true)) throw new System::Exception(S"The specified configuration does not contain a <scanning> XML element.");
		for (i = 0; i < pXmlRoot->Attributes->Count &&
			System::String::Compare(pXmlRoot->Attributes->Item(i)->Name, S"executor", true); i++);
		if (i == pXmlRoot->Attributes->Count) throw new System::Exception(S"Missing executor specification.");
		Executor = pXmlRoot->Attributes->Item(i)->InnerText;
		for (i = 0; i < pXmlRoot->Attributes->Count &&
			System::String::Compare(pXmlRoot->Attributes->Item(i)->Name, S"title", true); i++);
		if (i == pXmlRoot->Attributes->Count); // TODO: title set = "untitled" else set the layout title.
		System::Xml::XmlNode *pXmlSection;
		for (pXmlSection = pXmlRoot->FirstChild; 
			pXmlSection && (System::String::Compare(pXmlSection->Name, S"objects", true)); 
			pXmlSection = pXmlSection->NextSibling);
		if (!pXmlSection) throw new System::Exception(S"Missing <objects> section.");
		System::Xml::XmlNode *pXmlObjects;
		System::Xml::XmlNode *pXmlConfig;


		for (pXmlObjects = pXmlSection->FirstChild; pXmlObjects; pXmlObjects = pXmlObjects->NextSibling)
		{
			static char namestr[sizeof(ConnectionName) + 1];
			char *clsidstr;
			for (i = 0; i < pXmlObjects->Attributes->Count &&
				System::String::Compare(pXmlObjects->Attributes->Item(i)->Name, "clsid", true); i++);
			if (i == pXmlObjects->Attributes->Count) throw new System::Exception(S"Missing clsid.");
			clsidstr = String2Char(pXmlObjects->Attributes->Item(i)->Value);
			CLSID clsid;
			if (!CLSIDFromCLSIDStr(clsidstr, &clsid)) throw new System::Exception(S"Invalid CLSID passed.");
			for (i = 0; i < LayoutObjCount && memcmp(&clsid, &pCLSIDs[i], sizeof(clsid)) != 0; i++);
			if (i < LayoutObjCount)
			{
				poldobjs[oldobjcount] = pLayoutObjs[i];
				poldclsids[oldobjcount] = pCLSIDs[i];
				if (++oldobjcount >= maxoldobjcount)
				{
					maxoldobjcount += 8;
					poldobjs = (ISySalObject **)realloc(poldobjs, sizeof(ISySalObject *) * maxoldobjcount);
					poldclsids = (CLSID *)realloc(poldclsids, sizeof(CLSID) * maxoldobjcount);
				}
				for (LayoutObjCount--; i < LayoutObjCount; i++)
				{
					pLayoutObjs[i] = pLayoutObjs[i + 1];
					pCLSIDs[i] = pCLSIDs[i + 1];
				}
			}
		}

		for (i = 0; i < LayoutObjCount; i++) pLayoutObjs[i]->Release();
		LayoutObjCount = 0;
		
		for (pXmlObjects = pXmlSection->FirstChild; pXmlObjects; pXmlObjects = pXmlObjects->NextSibling)
		{
			static char namestr[sizeof(ConnectionName) + 1];
			char *clsidstr;
			for (i = 0; i < pXmlObjects->Attributes->Count &&
				System::String::Compare(pXmlObjects->Attributes->Item(i)->Name, "clsid", true); i++);
			if (i == pXmlObjects->Attributes->Count) throw new System::Exception(S"Missing clsid.");
			((void (*)(void *, char *))pAddStringCallback)(pContext, clsidstr = String2Char(pXmlObjects->Attributes->Item(i)->Value));
			((void (*)(void *, char *))pAddStringCallback)(pContext, "\t");
			CLSID clsid;
			ISySalObject *iOb = ObjFromCLSIDStr(clsidstr, &clsid, oldobjcount, poldobjs, poldclsids);
			if (!iOb) throw new System::Exception(S"Object creation failure.");
			AddObjToLayout(iOb, clsid);
			ISySalObjectMachineDefaults *iMD = 0;
			if (iOb->QueryInterface(IID_ISySalObjectMachineDefaults, (void **)&iMD) == S_OK)
			{
				SySalConfig MD;
				MD.Name[0] = 0;
				MD.CountOfItems = 0;
				MD.pItems = 0;
				if (LoadMachineDefaults(MD, clsid)) iMD->SetMachineDefaults(&MD);				
			}
			if (iMD) iMD->Release();
			ConnectionName conn;
			ConnectionName otherconn;
			iOb->GetClassName(conn);
			namestr[sizeof(ConnectionName)] = 0;
			strncpy(namestr, conn, sizeof(conn));
			iOb->EnableMonitor(true);			
			((void (*)(void *, char *))pAddStringCallback)(pContext, conn);
			((void (*)(void *, char *))pAddStringCallback)(pContext, "\t");
			for (i = 0; i < pXmlObjects->Attributes->Count &&
				System::String::Compare(pXmlObjects->Attributes->Item(i)->Name, "name", true); i++);
			if (i == pXmlObjects->Attributes->Count) throw new System::Exception(S"Missing name.");
			System::String *ObjName;
			strncpy(conn, String2Char(ObjName = pXmlObjects->Attributes->Item(i)->InnerText), sizeof(conn));
			if (conn[0] == 0) throw new System::Exception(S"Null name.");
			for (j = 0; j < LayoutObjCount - 1; j++)
			{
				pLayoutObjs[j]->GetName(otherconn);
				if (!strnicmp(otherconn, conn, sizeof(conn))) throw new System::Exception(S"Duplicate name found.");
			}
			iOb->SetName(conn);
			namestr[sizeof(ConnectionName)] = 0;
			strncpy(namestr, conn, sizeof(conn));
			if (!System::String::Compare(ObjName, Executor, true)) iExecutor = iOb;
			((void (*)(void *, char *))pAddStringCallback)(pContext, "\"");
			((void (*)(void *, char *))pAddStringCallback)(pContext, namestr);
			for (pXmlConfig = pXmlObjects->FirstChild; pXmlConfig && System::String::Compare(pXmlConfig->Name, S"config", true); pXmlConfig = pXmlConfig->NextSibling);
			if (pXmlConfig)
			{		
				static char configname[SYSAL_MAXCONFIG_NAME_LEN + 1];
				configname[SYSAL_MAXCONFIG_NAME_LEN];
				for (i = 0; i < pXmlConfig->Attributes->Count &&
					System::String::Compare(pXmlConfig->Attributes->Item(i)->Name, S"name", true); i++);
				if (i < pXmlConfig->Attributes->Count)
				{
					strncpy(configname, String2Char(pXmlConfig->Attributes->Item(i)->Value), SYSAL_MAXCONFIG_NAME_LEN);
					((void (*)(void *, char *))pAddStringCallback)(pContext, " [");
					((void (*)(void *, char *))pAddStringCallback)(pContext, configname);
					((void (*)(void *, char *))pAddStringCallback)(pContext, "]");					
					SySalConfig C;
					C.Name[0] = 0;
					C.CountOfItems = 0;
					C.pItems = (char *)CoTaskMemAlloc(pXmlConfig->ChildNodes->Count * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));					
					char *pI = C.pItems;
					for (pXmlConfig = pXmlConfig->FirstChild; pXmlConfig; pXmlConfig = pXmlConfig->NextSibling)
					{
						strncpy(pI, String2Char(pXmlConfig->Name), SYSAL_MAXCONFIG_ENTRY_NAME_LEN); pI += SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
						strncpy(pI, String2Char(pXmlConfig->InnerText), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN); pI += SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
						C.CountOfItems++;
					}
					if (iOb->SetConfig(&C) != S_OK)
					{
						if (C.pItems) CoTaskMemFree(C.pItems);
						throw new System::Exception(System::String::Concat(S"Invalid configuration specified for object ", ObjName));
					}
					if (C.pItems) CoTaskMemFree(C.pItems);
				}
			}
			((void (*)(void *, char *))pAddStringCallback)(pContext, "\"\r\n");
		}			
		if (iExecutor == 0) throw new System::Exception(S"No object matches the specified executor name.");
		for (pXmlSection = pXmlRoot->FirstChild; 
			pXmlSection && (System::String::Compare(pXmlSection->Name, S"connections", true)); 
			pXmlSection = pXmlSection->NextSibling);
		if (!pXmlSection) throw new System::Exception(S"Missing <connections> section.");
		System::Xml::XmlNode *pXmlConnections = pXmlSection;
		for (pXmlConnections = pXmlSection->FirstChild; pXmlConnections; pXmlConnections = pXmlConnections->NextSibling)
		{
			if (System::String::Compare(pXmlConnections->Name, S"connection", true) == 0)
			{
				char conn[sizeof(ConnectionName) + 1];
				char namestr[sizeof(ConnectionName) + 1];
				ISySalObject *iConnBegin = 0;
				ISySalObject *iConnEnd = 0;
				int SlotNumber = -1;
				for (i = 0; i < pXmlConnections->Attributes->Count &&
					System::String::Compare(pXmlConnections->Attributes->Item(i)->Name, S"begin", true); i++);
				if (i == pXmlConnections->Attributes->Count) throw new System::Exception("Missing specification of the connection begin.");
				strncpy(conn, String2Char(pXmlConnections->Attributes->Item(i)->Value), SYSAL_MAXCONFIG_NAME_LEN);
				for (i = 0; i < LayoutObjCount; i++)
				{
					pLayoutObjs[i]->GetName(namestr);
					if (strnicmp(namestr, conn, SYSAL_MAX_CONN_NAME_LEN) == 0) break;
				}
				if (i == LayoutObjCount) throw new System::Exception("Unknown connection begin specified.");
				iConnBegin = pLayoutObjs[i];
				for (i = 0; i < pXmlConnections->Attributes->Count &&
					System::String::Compare(pXmlConnections->Attributes->Item(i)->Name, S"end", true); i++);
				if (i == pXmlConnections->Attributes->Count) throw new System::Exception("Missing specification of the connection end.");
				strncpy(conn, String2Char(pXmlConnections->Attributes->Item(i)->Value), SYSAL_MAXCONFIG_NAME_LEN);
				for (i = 0; i < LayoutObjCount; i++)
				{
					pLayoutObjs[i]->GetName(namestr);
					if (strnicmp(namestr, conn, SYSAL_MAX_CONN_NAME_LEN) == 0) break;
				}
				if (i == LayoutObjCount) throw new System::Exception("Unknown connection end specified.");
				iConnEnd = pLayoutObjs[i];
				for (i = 0; i < pXmlConnections->Attributes->Count &&
					System::String::Compare(pXmlConnections->Attributes->Item(i)->Name, S"slot", true); i++);
				if (i == pXmlConnections->Attributes->Count) throw new System::Exception("Missing specification of the connection slot.");
				strncpy(namestr, String2Char(pXmlConnections->Attributes->Item(i)->Value), SYSAL_MAXCONFIG_NAME_LEN);
				iConnEnd->GetNumberOfConnections(&j);
				SySalConnection sconn;
				for (i = 0; i < j; i++)
				{
					iConnEnd->GetConnection(i, &sconn);
					if (strnicmp(sconn.Name, namestr, SYSAL_MAX_CONN_NAME_LEN) == 0) break;
				}
				if (i == j) throw new System::Exception("Unknown connection slot specified.");
				sconn.pUnknown = iConnBegin;
				sconn.Type = SYSAL_CONN_TYPE_INTERFACE;
				if (iConnEnd->SetConnection(i, sconn) != S_OK) throw new System::Exception("Error setting up connections.");
			}
		}

		int statuscode;
		for (i = 0; i < LayoutObjCount; i++)
			if (pLayoutObjs[i]->IsReady((long *)&j, (long *)&statuscode) != S_OK || statuscode != SYSAL_READYSTATUS_READY)
			{
				static char namestr[sizeof(ConnectionName) + 1];
				static char connstr[sizeof(ConnectionName) + 1];
				static SySalConnection conn;
				pLayoutObjs[i]->GetName(namestr);
				namestr[sizeof(ConnectionName)] = 0;
				pLayoutObjs[i]->GetConnection(j, &conn);
				strncpy(connstr, conn.Name, SYSAL_MAX_CONN_NAME_LEN);
				connstr[sizeof(ConnectionName)] = 0;
				static char msgstr[512];
				sprintf(msgstr, "Object #%d (%s) reports a problem on slot #%d (%s).", i, namestr, j, connstr);
				throw new System::Exception(msgstr);
			}
		((void (*)(void *, char *))pAddStringCallback)(pContext, "Layout created.\r\n");

		ResetEvent(HProcessed);
		ResetEvent((HANDLE)HNotifyStatusChangeEvent);
		iExecutor->AsyncExec(HNotifyStatusChangeEvent);
		long execstatus;
		WaitForSingleObject((HANDLE)HNotifyStatusChangeEvent, INFINITE);		
		iExecutor->AsyncCheckStatus(&execstatus);
		if (execstatus != SYSAL_ASYNC_STATUS_RUNNING)
			((void (*)(void *, char *))pAddStringCallback)(pContext, "Unable to start execution. Administrator help is required. An error is likely to occur after this call.");
		else
		{
			WaitForSingleObject(HProcessed, INFINITE);
			if (!m_AcceptScanRequests)
				((void (*)(void *, char *))pAddStringCallback)(pContext, "Unable to accept scanning requests. Administrator help is required. An error is likely to occur after this call.");
		}
	}
	catch (System::Exception *x)
	{
		while (oldobjcount > 0)		
			poldobjs[--oldobjcount]->Release();
		if (poldobjs) free(poldobjs);
		if (poldclsids) free(poldclsids);
		//iExecutor = 0; TODO: Check This
		ResetLayout();
		((void (*)(void *, char *))pAddStringCallback)(pContext, String2Char(x->Message));
		((void (*)(void *, char *))pAddStringCallback)(pContext, "\r\n");	
		((void (*)(void *, char *))pAddStringCallback)(pContext, "Layout discarded.\r\n");
		return false;
	}
	while (oldobjcount > 0)		
		poldobjs[--oldobjcount]->Release();
	if (poldobjs) free(poldobjs);
	if (poldclsids) free(poldclsids);
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

ScanServer *ScanServer::Create(void *pcontext, ISySalObject __nogc *(*pcreateobjectinwndthreadcallback)(void __nogc *pcontext, CLSID &), void (*pdeleteobjectinwndthreadcallback)(void __nogc *pcontext, ISySalObject __nogc *iobj), void (*paddstringcallback)(void *, char *), ISySalObject __nogc *icomsrv)
{
	ScanServer *pNETSrv = new ScanServer;
	pNETSrv->pContext = pcontext;
	pNETSrv->pCreateObjectInWndThreadCallback = pcreateobjectinwndthreadcallback;
	pNETSrv->pDeleteObjectInWndThreadCallback = pdeleteobjectinwndthreadcallback;
	pNETSrv->pAddStringCallback = paddstringcallback;
	pNETSrv->iCOMSrv = icomsrv;
	if (pNETSrv->iCOMSrv) pNETSrv->iCOMSrv->AddRef();
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

bool ScanServer::CLSIDFromCLSIDStr(char *clsidstr, CLSID *pclsid)
{
	if (clsidstr[0] != '{') return false;
	if (clsidstr[37] != '}') return false;
	if (clsidstr[9] != '-') return false;
	if (clsidstr[14] != '-') return false;
	if (clsidstr[19] != '-') return false;
	if (clsidstr[24] != '-') return false;
	if (sscanf(clsidstr + 1, "%08X", &pclsid->Data1) != 1) return false;
	if (sscanf(clsidstr + 10, "%04X", &pclsid->Data2) != 1) return false;
	if (sscanf(clsidstr + 15, "%04X", &pclsid->Data3) != 1) return false;
	if (sscanf(clsidstr + 20, "%02X", &pclsid->Data4[0]) != 1) return false;
	if (sscanf(clsidstr + 22, "%02X", &pclsid->Data4[1]) != 1) return false;
	if (sscanf(clsidstr + 25, "%02X", &pclsid->Data4[2]) != 1) return false;
	if (sscanf(clsidstr + 27, "%02X", &pclsid->Data4[3]) != 1) return false;
	if (sscanf(clsidstr + 29, "%02X", &pclsid->Data4[4]) != 1) return false;
	if (sscanf(clsidstr + 31, "%02X", &pclsid->Data4[5]) != 1) return false;
	if (sscanf(clsidstr + 33, "%02X", &pclsid->Data4[6]) != 1) return false;
	if (sscanf(clsidstr + 35, "%02X", &pclsid->Data4[7]) != 1) return false;	
	return true;
}

ISySalObject __nogc *ScanServer::ObjFromCLSIDStr(char *clsidstr, CLSID *pclsid, int &oldobjcount, ISySalObject **poldobjs, CLSID *poldclsids)
{
//	static CLSID ret;
	if (clsidstr[0] != '{') return 0;
	if (clsidstr[37] != '}') return 0;
	if (clsidstr[9] != '-') return 0;
	if (clsidstr[14] != '-') return 0;
	if (clsidstr[19] != '-') return 0;
	if (clsidstr[24] != '-') return 0;
	if (sscanf(clsidstr + 1, "%08X", &pclsid->Data1) != 1) return 0;
	if (sscanf(clsidstr + 10, "%04X", &pclsid->Data2) != 1) return 0;
	if (sscanf(clsidstr + 15, "%04X", &pclsid->Data3) != 1) return 0;
	if (sscanf(clsidstr + 20, "%02X", &pclsid->Data4[0]) != 1) return 0;
	if (sscanf(clsidstr + 22, "%02X", &pclsid->Data4[1]) != 1) return 0;
	if (sscanf(clsidstr + 25, "%02X", &pclsid->Data4[2]) != 1) return 0;
	if (sscanf(clsidstr + 27, "%02X", &pclsid->Data4[3]) != 1) return 0;
	if (sscanf(clsidstr + 29, "%02X", &pclsid->Data4[4]) != 1) return 0;
	if (sscanf(clsidstr + 31, "%02X", &pclsid->Data4[5]) != 1) return 0;
	if (sscanf(clsidstr + 33, "%02X", &pclsid->Data4[6]) != 1) return 0;
	if (sscanf(clsidstr + 35, "%02X", &pclsid->Data4[7]) != 1) return 0;

	int i;
	for (i = 0; i < oldobjcount; i++)
		if (memcmp(pclsid, &poldclsids[i], sizeof(CLSID)) == 0)
		{
			ISySalObject __nogc *pObj = poldobjs[i];
			oldobjcount--;
			while (i < oldobjcount)
			{
				poldobjs[i] = poldobjs[i + 1];
				poldclsids[i] = poldclsids[i + 1];
				i++;
			}
			return pObj;
		}

	if (!strnicmp(clsidstr, "{E8F1A43B-C0D3-4061-8E78-5C2A25C158F8}", 38))
	{
		iCOMSrv->AddRef();
		return iCOMSrv;
	}

	return ((ISySalObject *(*)(void *pcontext, CLSID &))pCreateObjectInWndThreadCallback)(pContext, *pclsid);
}

int ScanServer::GetLayoutListAndResetForShutdown(ScanServer *pNETSrv, ISySalObject ***playoutlist)
{	
	*playoutlist = pNETSrv->pLayoutObjs;
	int n = pNETSrv->LayoutObjCount;
	pNETSrv->LayoutObjCount = 0;
	pNETSrv->pLayoutObjs = 0;
	return n;
}

void ScanServer::ShowMonitors()
{
	int i;
	for (i = 0; i < LayoutObjCount; pLayoutObjs[i++]->EnableMonitor(true));
}

bool ScanServer::LoadMachineDefaults(SySalConfig &C, CLSID &clsid)
{
	C.pItems = 0;
	C.CountOfItems = 0;

	char CLSIDString[64];
	wsprintf(CLSIDString, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
		clsid.Data1, clsid.Data2, clsid.Data3, 
		clsid.Data4[0], clsid.Data4[1], clsid.Data4[2], clsid.Data4[3], 
		clsid.Data4[4], clsid.Data4[5], clsid.Data4[6], clsid.Data4[7]);
	HKEY HFindKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes", 0, KEY_READ, &HFindKey) != ERROR_SUCCESS)
	{
		::MessageBox(0, "Can't enumerate classes\nThe registry might be corrupt"
			"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		return false;
		}	
	char KeyName[SYSAL_MAXCONFIG_NAME_LEN + 1];
	DWORD KeyNameLen;
	int cc = 0;
	bool Found = false;
	while (!Found)
	{
		KeyNameLen = SYSAL_MAXCONFIG_NAME_LEN + 1;
		if (RegEnumKeyEx(HFindKey, cc, KeyName, &KeyNameLen, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) break;
		HKEY HCheckKey;
		if (RegOpenKeyEx(HFindKey, KeyName, 0, KEY_READ, &HCheckKey) != ERROR_SUCCESS) break;
		DWORD keysize = 0;
		if (RegQueryValueEx(HCheckKey, "CLSID", NULL, NULL, NULL, &keysize) != ERROR_SUCCESS)
		{
			RegCloseKey(HCheckKey);
			break;
			}
		char *pK = (char *)malloc(++keysize);
		RegQueryValueEx(HCheckKey, "CLSID", NULL, NULL, (UCHAR *)pK, &keysize);
		Found = (strcmpi(pK, CLSIDString) == 0);
		if (pK) free(pK);
		RegCloseKey(HCheckKey);
		cc++;
		}
	RegCloseKey(HFindKey);
	if (!Found)
	{
		::MessageBox(0, "Can't access class information\nThe registry might be corrupt"
			"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		return false;
		}	

	strncpy(C.Name, KeyName, SYSAL_MAXCONFIG_NAME_LEN);
	CRegKey MyKey;
	CString Temp = "Software\\SySal2\\Classes\\";
	Temp += KeyName;
	Temp += "\\Defaults";
	if (MyKey.Open(HKEY_LOCAL_MACHINE, Temp, KEY_READ) != ERROR_SUCCESS) return true;
	int i;
	char tempname[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	DWORD tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
	DWORD tempvalsize = SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
	for (i = 0; RegEnumValue(MyKey.m_hKey, i, tempname, &tempsize, 0, 0, 0, 0) == ERROR_SUCCESS; i++) tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
	C.pItems = (char *)CoTaskMemAlloc(i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	for (C.CountOfItems = 0; RegEnumValue(MyKey.m_hKey, C.CountOfItems, 
		C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), &tempsize, 
		0, 0, (LPBYTE)(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN), 
		&tempvalsize) == ERROR_SUCCESS; C.CountOfItems++)
	{
		tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
		tempvalsize = SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
		};
	MyKey.Close();
	return true;
}

#include "MachineDefaults_i.c"