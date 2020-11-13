#pragma once

#include "ScanServerDefs.h"
#include <windows.h>

#using <mscorlib.dll>
#using <System.Xml.dll>
#using <System.Runtime.Remoting.dll>
#using "SySalCore.dll"
#using "DAQSystem.dll"
#include "SySalObj2.h"

using namespace System;
using namespace SySal;
using namespace SySal::BasicTypes;
using namespace System::Runtime::Remoting;
using namespace System::Runtime::Remoting::Channels;

namespace SySal
{
	namespace DAQSystem
	{
		public __gc class ScanServer : public MarshalByRefObject
		{
		private:

			ScanSrvMessage *pMessage;

			bool m_IsLoaded;
			bool m_IsBusy;
			SySal::BasicTypes::Identifier m_ZoneId;
			SySal::BasicTypes::Identifier m_PlateId;

			void Connect();
			void Disconnect();

			void *pCreateObjectInWndThreadCallback;
			void *pSetScanLayoutCallback;//bool (_cdecl *pSetScanLayoutCallback)(void *pcontext, System::String *xmllayout);
			void *pAddStringCallback;//void (_cdecl *pAddStringCallback)(void *pcontext, char *msg);
			void *pContext;
			ISySalObject *iCOMSrv;
			int LayoutObjCount;
			int MaxLayoutObjs;
			ISySalObject **pLayoutObjs;
			void ResetLayout();
			void AddObjToLayout(ISySalObject *iObj);

			HANDLE HMessageMutex;
			HANDLE HProcessed;
			HANDLE HFreeMutex;
			
		public:

			static ScanServer *Create(void *pcontext, ISySalObject __nogc *(*pcreateobjectinwndthreadcallback)(void __nogc *pcontext, CLSID &), bool (*pSetScanLayoutCallback)(void __nogc *, System::String *), void (*paddstringcallback)(void __nogc *, char __nogc *), ISySalObject __nogc *icomsrv);
			static Tcp::TcpChannel *RegisterChannelAndServer(ScanServer *pNETSrv);
			static void UnregisterChannelAndServer(Tcp::TcpChannel *pChannel, ScanServer *pNETSrv);

			ScanServer();
			~ScanServer();

			Object *InitializeLifetimeService();
			
			bool Scan(SySal::DAQSystem::Scanning::ZoneDesc zone);
			bool LoadPlate(SySal::DAQSystem::Scanning::MountPlateDesc plate);
			bool UnloadPlate();
			bool SetSingleParameter(System::String *objectname, System::String *parametername, System::String *parametervalue);
			bool SetObjectConfiguration(System::String *objectname, System::String *xmlconfig);
			bool SetScanLayout(System::String *xmllayout);

			__property bool get_IsBusy();
			__property bool get_IsLoaded();
			__property SySal::BasicTypes::Identifier get_CurrentZone();
			__property SySal::BasicTypes::Identifier get_CurrentPlate();

			bool TestComm(int h);

			bool Receive(ScanSrvMessage *p);
			bool Send(ScanSrvMessage *pmsg);

			static char *String2Char(System::String *str);
			ISySalObject __nogc *ObjFromCLSIDStr(char *clsidstr);
		};
	}
}