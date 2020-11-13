#ifndef _SERVER_H_
#define _SERVER_H_

#include "stdafx.h"

#ifdef ENABLE_NET
#using <mscorlib.dll>
#using "SySalCore.dll"
#using "Imaging.dll"
#using "Tracking.dll"
#using "Scanning.dll"
#include <windows.h>
#include <malloc.h>
#include "..\Common\Tracker.h"
#include "..\Common\Fitter.h"
#include "..\Common\CameraSpec2.h"
#include "..\Common\Cluster.h"
#include "..\Common\Track2.h"

using namespace System;

namespace SySal
{
	namespace DAQSystem
	{
#pragma pack(push)
#pragma pack(1)

		typedef struct
		{
			float X;
			float Y;
			int Area;
		} NetCluster;

#pragma pack(pop)

		public delegate void dNotifyCall(System::Int32 TimeMilliSeconds);

		public delegate void dNotifyTracks(System::Int32 tks);

		public delegate void dNotifyError(System::String ^err);

		public ref class TrackingServer : public System::MarshalByRefObject
		{
			System::String ^Milestone;

			dNotifyCall ^NotifyCall;

			dNotifyTracks ^NotifyTracks;

			dNotifyError ^NotifyError;

			ref class IntSide : public SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::View::Side
			{
			public:
				IntSide(System::Single ztop, System::Single zbottom, System::Single X, System::Single Y, System::Single MapX, System::Single MapY, System::Single MXX, System::Single MXY, System::Single MYX, System::Single MYY, int trackcount, Track2 *ptracks, int layers, array<System::Single> ^Z, array<System::Int32> ^GrainCounts, bool savegrains);
			};

			ref class IntView : public SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::View
			{
				bool initialized;
			public:
				void SetSide(System::Boolean istop, SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::View::Side ^sd, System::Int32 tilex, System::Int32 tiley);

				IntView();
			};

			ref class IntFragment : public SySal::Scanning::Plate::IO::OPERA::RawData::Fragment
			{
				System::String ^m_Path;
				int m_viewscompleted;
				SySal::DAQSystem::TrackingServer ^m_Owner;

			public:
				IntFragment(SySal::DAQSystem::TrackingServer ^owner, System::Int32 index, System::Int32 startview, System::Int32 views, bool savegrains, System::String ^path);

				bool AddViewSide(int id, System::Boolean istop, SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::View::Side ^vwsd, System::Int32 tilex, System::Int32 tiley);

			};

			IntFragment ^m_Fragment;
		
			array<System::Byte> ^m_TrackerCLSID_T;
			array<System::Byte> ^m_TrackerConfig_T;
			array<System::Byte> ^m_TrackerCLSID_B;
			array<System::Byte> ^m_TrackerConfig_B;
			array<System::Byte> ^m_FitterCLSID_T;
			array<System::Byte> ^m_FitterConfig_T;
			array<System::Byte> ^m_FitterCLSID_B;
			array<System::Byte> ^m_FitterConfig_B;
			ITracker4 *pTracker_T;
			ITracker4 *pTracker_B;
			ITrackFitter3 *pFitter_T;
			ITrackFitter3 *pFitter_B;	
			Cluster *pClusters;
			Track2 *pTracks;
			Grain *pGrains;
			int MaxClusters;
			int MaxTracks;			
			int GrainsPerTrack, MaxGrains;
			float RefractiveShrinkage;
			float ViewCenterX;
			float ViewCenterY;
			int FitCorrectionDataSize;
			void *pCorrectionData;
			HANDLE HMutex;

			System::Int64 StartupGUID;

			bool EqualBytes(array<System::Byte> ^a1, array<System::Byte> ^a2);

			void FillBytes(void *pdest, array<System::Byte> ^a, int startpoint);

			void ReadBytes(void *pdest, array<System::Byte> ^a, int &readpoint, int count);

			void ZExpand(Track2 *pTracks, UINT Count, float ZBase, float shrinkage);

			void XYOffset(Track2 *pTracks, UINT Count);

			UINT DiscardInvalidTracks(Track2 *pTracks, UINT Count);

			bool ReadConfig(SySalConfig *pC, array<System::Byte> ^i_config);

			bool SetupObject(array<System::Byte> ^i_clsid, array<System::Byte> ^i_config, array<System::Byte> ^ %r_clsid, array<System::Byte> ^ %r_config, IID i_interface, void **p_obj);

			bool SetConfig(array<System::Byte> ^ trackerconfig_t, array<System::Byte> ^ trackerclsid_t, array<System::Byte> ^ trackerconfig_b, array<System::Byte> ^ trackerclsid_b, array<System::Byte> ^ fitterconfig_t, array<System::Byte> ^ fitterclsid_t, array<System::Byte> ^ fitterconfig_b, array<System::Byte> ^ fitterclsid_b, array<System::Byte> ^ camspec);

			void SafeNotifyError(System::String ^err);

		public:

			virtual Object^ InitializeLifetimeService () override;

			TrackingServer();

			TrackingServer(dNotifyCall ^ncall, dNotifyTracks ^ntracks, dNotifyError ^nerr);

			virtual ~TrackingServer();
			
			property System::Int64 GUID
			{
				System::Int64 get();
			}

			System::Boolean OpenFragment(System::String ^filepath, System::Int32 index, System::Int32 startview, System::Int32 views, array<System::Byte> ^ camspec, array<System::Byte> ^ trackerconfig_t,  array<System::Byte> ^ trackerclsid_t, array<System::Byte> ^ trackerconfig_b, array<System::Byte> ^ trackerclsid_b, array<System::Byte> ^ fitterconfig_t,  array<System::Byte> ^ fitterclsid_t, array<System::Byte> ^ fitterconfig_b,  array<System::Byte> ^ fitterclsid_b, System::Int32 maxtracks, System::Boolean savegrains, System::Boolean useslopepreset, System::Single slopepresetminx, System::Single slopepresetmaxx, System::Single slopepresetminy, System::Single slopepresetmaxy);

			System::Boolean SendViewSide(System::Int32 Field, System::Int32 TileX, System::Int32 TileY, System::Single PosX, System::Single PosY, System::Single MapPosX, System::Single MapPosY, System::Single MapXX, System::Single MapXY, System::Single MapYX, System::Single MapYY, array<System::Single> ^ Z, array<System::Byte> ^ clusterlayers, System::Boolean IsTop, System::Single ztop, System::Single zbottom, System::Single zbase, System::Single shrinkage);

			void Test(System::String ^testfile);
		};
	}
}
#endif
#endif