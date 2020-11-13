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
		public ref class ScanServer : public MarshalByRefObject
		{
		private:

			ScanSrvMessage *pMessage;
			Tcp::TcpChannel ^pChannel;

			bool m_AcceptScanRequests;
			bool m_IsLoaded;
			bool m_IsBusy;
			SySal::BasicTypes::Identifier m_ZoneId;
			SySal::BasicTypes::Identifier m_PlateId;

			void *pCreateObjectInWndThreadCallback;
			void *pDeleteObjectInWndThreadCallback;
			void *pAddStringCallback;
			void *pContext;
			int LayoutObjCount;
			int MaxLayoutObjs;
			CLSID *pCLSIDs;
			ISySalObject **pLayoutObjs;
			ISySalObject *iExecutor;			
			void ResetLayout();
			void AddObjToLayout(ISySalObject *iObj, CLSID &clsid);

			HANDLE HMessageMutex;
			HANDLE HProcessed;
			HANDLE HFreeMutex;

			HSySalHANDLE HNotifyStatusChangeEvent;

			static char *String2Char(System::String ^str);
			ISySalObject *ObjFromCLSIDStr(char *clsidstr, CLSID *pclsid, int &oldobjcount, ISySalObject **poldobjs, CLSID *poldclsids);
			bool CLSIDFromCLSIDStr(char *clsidstr, CLSID *pclsid);
			bool LoadMachineDefaults(SySalConfig &C, CLSID &clsid);

			static System::Threading::AutoResetEvent ^EvCall = gcnew System::Threading::AutoResetEvent(false);
			static Object ^SSCall(Object ^input);

		public:

			void ResetLayoutForShutDown();
			static int GetLayoutListAndResetForShutdown(ScanServer ^pNETSrv, ISySalObject ***playoutlist);
			static ScanServer ^Create(void *pcontext, ISySalObject *(*pcreateobjectinwndthreadcallback)(void *pcontext, CLSID &), void (*pdeleteobjectinwndthreadcallback)(void  *pcontext, ISySalObject  *iobj), void (*paddstringcallback)(void  *, char  *));
			static void RegisterChannelAndServer(ScanServer ^pNETSrv);
			static void UnregisterChannelAndServer(ScanServer ^pNETSrv);

			ScanServer();
			//!ScanServer();

			virtual System::Object ^InitializeLifetimeService() override;
			
			bool Scan(SySal::DAQSystem::Scanning::ZoneDesc ^zone);
			bool ScanAndMoveToNext(SySal::DAQSystem::Scanning::ZoneDesc ^zone, SySal::BasicTypes::Rectangle ^rect);
			bool LoadPlate(SySal::DAQSystem::Scanning::MountPlateDesc ^plate);
			bool UnloadPlate();
			bool SetSingleParameter(System::String ^objectname, System::String ^parametername, System::String ^parametervalue);
			bool SetObjectConfiguration(System::String ^objectname, System::String ^xmlconfig);
			bool SetScanLayout(System::String ^xmllayout);

			property bool IsBusy { bool get(); }
			property bool IsLoaded { bool get(); }
			property SySal::BasicTypes::Identifier CurrentZone { SySal::BasicTypes::Identifier get(); }
			property SySal::BasicTypes::Identifier CurrentPlate { SySal::BasicTypes::Identifier get(); }

			SySal::DAQSystem::Scanning::ManualCheck::OutputBaseTrack RequireManualCheck(SySal::DAQSystem::Scanning::ManualCheck::InputBaseTrack inputbasetrack);
			SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet GetFogAndThickness();

			bool TestComm(int h);

			void Connect();
			void Disconnect();

			void ShowMonitors();

		};
	}
}