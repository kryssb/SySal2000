#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "Server.h"
#include "vscan_ds.h"
#include "CameraSpec2.h"

using namespace System;

namespace SySal
{
	namespace DAQSystem
	{
		public ref class NetPackagedView
		{
		public:
			System::Int32 Field;
			System::Int32 TileX;
			System::Int32 TileY;
			System::Single PosX;
			System::Single PosY;
			System::Single MapPosX;
			System::Single MapPosY;
			System::Single MapXX;
			System::Single MapXY;
			System::Single MapYX;
			System::Single MapYY;
			array<System::Single> ^ Z;
			array<System::Byte> ^ ClusterLayers;
			System::Boolean IsTop;
			System::Single ZTop;
			System::Single ZBottom;
			System::Single ZBase;
			System::Single Shrinkage;
		};

		public ref class NetPackagedFragment
		{
		public:
			System::String ^FilePath;
			System::Int32 Index;
			System::Int32 StartView;			
			array<System::Byte> ^CamSpec;
			array<System::Byte> ^TrackerCLSID_T;
			array<System::Byte> ^TrackerCLSID_B;
			array<System::Byte> ^TrackerConfig_T;
			array<System::Byte> ^TrackerConfig_B;
			array<System::Byte> ^FitterCLSID_T;
			array<System::Byte> ^FitterCLSID_B;
			array<System::Byte> ^FitterConfig_T;
			array<System::Byte> ^FitterConfig_B;
			System::Int32 MaxTracks;
			System::Boolean SaveGrains;
			System::Boolean UseSlopePreset;
			System::Single SlopePresetMinX;
			System::Single SlopePresetMinY;
			System::Single SlopePresetMaxX;
			System::Single SlopePresetMaxY;
			array<NetPackagedView ^> ^ViewInfo;

			NetPackagedFragment();

			NetPackagedFragment(array<System::Byte> ^camspec, array<System::Byte> ^trackerclsid_t, array<System::Byte> ^trackerclsid_b, array<System::Byte> ^trackerconfig_t, array<System::Byte> ^trackerconfig_b, 
				array<System::Byte> ^fitterclsid_t, array<System::Byte> ^fitterclsid_b, array<System::Byte> ^fitterconfig_t, array<System::Byte> ^fitterconfig_b, 
				IO_VS_Fragment2 *pFrag, char *outname, int maxtracks, bool usepresetslope, float slopeminx, float slopemaxx, float slopeminy, float slopemaxy, float shrinkage);

			NetPackagedFragment(array<System::Byte> ^camspec, array<System::Byte> ^trackerclsid_t, array<System::Byte> ^trackerclsid_b, array<System::Byte> ^trackerconfig_t, array<System::Byte> ^trackerconfig_b, 
				array<System::Byte> ^fitterclsid_t, array<System::Byte> ^fitterclsid_b, array<System::Byte> ^fitterconfig_t, array<System::Byte> ^fitterconfig_b, 
				int index, int codingmode, int views, int startview, char *outname, int maxtracks, bool usepresetslope, float slopeminx, float slopemaxx, float slopeminy, float slopemaxy, float shrinkage);
		};

		public ref class ErrorLogger
		{
			System::Exception ^m_Exception;

		public:
			virtual property System::Exception ^Error
			{
				System::Exception ^get();
				void set(System::Exception ^);
			}
			virtual void Clear();
			virtual property bool IsOK
			{
				bool get();
			}
		};

		public ref class TrackingClientConnection
		{
		
			System::String ^m_ServerName;
			System::String ^m_MachineName;
			SySal::DAQSystem::TrackingServer ^m_Server;
			System::Collections::ArrayList ^m_DataQueue;
			HANDLE HDataQueueMutex;
			HANDLE HTerminate;
			System::Threading::Thread ^m_Thread;

			SySal::DAQSystem::NetPackagedFragment ^m_Frag;
			ErrorLogger ^m_Logger;

			void SendData();

			System::Exception ^m_Exception;

			bool Active;

		public:
			TrackingClientConnection(System::String ^servername, System::String ^machinename, SySal::DAQSystem::TrackingServer ^server, System::Collections::ArrayList ^dataqueue, HANDLE hDataQueueMutex, HANDLE HTerminate, ErrorLogger ^logger);

			property System::String ^ServerName
			{
				System::String ^get();
			}

			void Execute(void);

			void Join();

			property bool IsActive
			{
				bool get();
			}

			property System::String ^CurrentTask
			{
				System::String ^get();
			}

			property System::String ^ExceptionText
			{
				System::String ^get();
			}

			void Test(System::String ^testfile);
		};

		public ref class TrackingClient : public ErrorLogger
		{		
			System::String ^m_MachineName;
			array<SySal::DAQSystem::TrackingClientConnection ^> ^m_Servers;
			System::Collections::ArrayList ^m_DataQueue;
			HANDLE HDataQueueMutex;
			HANDLE HTerminate;	
			bool m_Disposed;
			System::String ^m_DefaultOutNameBase;			

		public:
			TrackingClient();
			!TrackingClient();

			property System::String ^MachineName
			{
				System::String ^get();
			}

			property int ServerCount
			{
				int get();
			}

			SySal::DAQSystem::TrackingClientConnection ^Server(int i);

			property array<System::String ^> ^QueueItems
			{
				array<System::String ^> ^get();
			}

			void RemoveItem(System::String ^str);

			void GetDefaultOutName(char *pOutName);

			void Free();
			
			void AddFragment(NetPackagedFragment ^pkfg);

			property bool IsActive
			{
				bool get();
			}
		};

	}
}

#endif