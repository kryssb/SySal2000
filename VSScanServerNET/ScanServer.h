#pragma once

#include "ScanServerDefs.h"
#include <windows.h>

#using <mscorlib.dll>
#using <System.Runtime.Remoting.dll>
#using "d:\sysal.net.beta2\sysal\daqsystem\bin\debug\SySalCore.dll"
#using "d:\sysal.net.beta2\sysal\daqsystem\bin\debug\DAQSystem.dll"

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

			HANDLE HMessageMutex;
			HANDLE HProcessed;
			ScanSrvMessage *pMessage;

			ScanServer(void);
			static ScanServer *pServer = 0;
			static Tcp::TcpChannel *pChannel = 0;

			static bool m_IsBusy = false;
			static bool m_IsLoaded = false;
			static SySal::BasicTypes::Identifier m_ZoneId;
			static SySal::BasicTypes::Identifier m_PlateId;

		public:
			
			static bool Connect();
			static void Disconnect();
			static ScanServer *Srv();
			~ScanServer(void);

			Object *InitializeLifetimeService();
			
			bool Scan(SySal::DAQSystem::Scanning::ZoneDesc *zone);
			bool LoadPlate(SySal::DAQSystem::Scanning::MountPlateDesc *plate);
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
		};
	}
}