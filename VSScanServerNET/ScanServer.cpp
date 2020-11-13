#include "StdAfx.h"
#include "scanserver.h"
#include <memory.h>

using namespace SySal::DAQSystem;

bool ScanServer::Connect()
{
	try
	{
		ChannelServices::RegisterChannel(pChannel = new Tcp::TcpChannel(1777));
	}
	catch (System::Exception *)
	{
		pChannel = 0;
		return false;
	};
	try
	{
		pServer = new SySal::DAQSystem::ScanServer();
		RemotingServices::Marshal(pServer = new ScanServer(), S"ScanServer.rem");
	}
	catch (System::Exception *)
	{
		pServer = 0;
		ChannelServices::UnregisterChannel(pChannel);
		pChannel = 0;
		return false;
	};
	return true;
}

void ScanServer::Disconnect()
{
	if (pServer)
	{
		RemotingServices::Disconnect(SySal::DAQSystem::ScanServer::pServer);
		ChannelServices::UnregisterChannel(pChannel);
		pServer = 0;
		pChannel = 0;
	}
}

Object *ScanServer::InitializeLifetimeService()
{
	return 0;	
}

ScanServer *ScanServer::Srv()
{
	return pServer;	
}

ScanServer::ScanServer(void)
{
	pMessage = 0;
	HMessageMutex = CreateMutex(NULL, FALSE, NULL);
	HProcessed = CreateEvent(NULL, FALSE, FALSE, NULL);
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
	CloseHandle(HMessageMutex);
	CloseHandle(HProcessed);
}

bool ScanServer::Scan(SySal::DAQSystem::Scanning::ZoneDesc *zone)
{
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
	return ret;
}

bool ScanServer::LoadPlate(SySal::DAQSystem::Scanning::MountPlateDesc *plate)
{
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
	for (i = 0; i < 255 && i < plate->TextDesc->Length; i++)
		p->TextId[i] = plate->TextDesc->Chars[i];
	p->TextId[i] = 0;
	for (i = 0; i < 8191 && i < plate->MapInitString->Length; i++)
		p->MapInitString[i] = plate->MapInitString->Chars[i];
	p->MapInitString[i] = 0;
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
	return ret;	
}

bool ScanServer::UnloadPlate()
{
	WaitForSingleObject(HMessageMutex, INFINITE);
	if (pMessage)
	{
		delete pMessage;
		pMessage = 0;
	}
	pMessage = new ScanSrvMessage;
	pMessage->OpCode = SCANSRV_UNLOAD_PLATE;
	pMessage->Size = sizeof(ScanSrvMessage);
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
											if (m_IsBusy = ((SetLoadedState *)pmsg)->Loaded) 
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
	return ret;
}

bool ScanServer::SetObjectConfiguration(System::String *objectname, System::String *xmlconfig)
{
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
	return ret;
}

bool ScanServer::SetScanLayout(System::String *xmllayout)
{
	return false;
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
	if (m_IsBusy) return m_ZoneId;
	throw new System::Exception("No zone currently being scanned.");
}

SySal::BasicTypes::Identifier ScanServer::get_CurrentPlate()
{
	if (m_IsLoaded) return m_PlateId;
	throw new System::Exception("No plate currently loaded.");
}

bool ScanServer::TestComm(int h)
{
	Console::WriteLine("Test called");
	Console::WriteLine(h);
	return true;
}

