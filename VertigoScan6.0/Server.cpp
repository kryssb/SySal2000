#include "Server.h"
#include <stdio.h>

#undef _DUMP_

#ifdef _DUMP_
#include <stdio.h>
#define DUMP(x)\
{\
	FILE *f = fopen("c:\\sysal2000\\vs6win.txt", "a+t");\
	fprintf(f, "%s", x);\
	fclose(f);\
}

#define DUMPBEGIN(x) \
	DUMP(x) \
	DUMP(" - Start\n") \
	try \
	{

#define DUMPEND(x) \
	} \
	catch(...)\
	{ DUMP(x); DUMP("Exception detected "); DUMP("\n"); } \
	finally \
	{ \
	DUMP(x) \
	DUMP(" - End\n") \
	}
#else
#define DUMP(x)
#define DUMPBEGIN(x)
#define DUMPEND(x)
#endif


namespace SySal
{
	namespace DAQSystem
	{
		TrackingServer::IntSide::IntSide(System::Single ztop, System::Single zbottom, System::Single X, System::Single Y, System::Single MapX, System::Single MapY, System::Single MXX, System::Single MXY, System::Single MYX, System::Single MYY, int trackcount, Track2 *ptracks, int layers, array<System::Single> ^Z, array<System::Int32> ^GrainCounts, bool savegrains)
		{
			this->m_BottomZ = zbottom;
			this->m_TopZ = ztop;
			this->m_Flags = SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::View::Side::SideFlags::OK;					
			this->m_MXX = MXX;
			this->m_MXY = MXY;
			this->m_MYX = MYX;
			this->m_MYY = MYY;
			double det = 1 / (m_MXX * m_MYY - m_MXY * m_MYX);
			m_IMXX = m_MYY * det;
			m_IMXY = -m_MXY * det;
			m_IMYX = -m_MYX * det;
			m_IMYY = m_MXX * det;
			this->m_MapPos.X = MapX;
			this->m_MapPos.Y = MapY;
			this->m_Pos.X = X;
			this->m_Pos.Y = Y;
			this->m_Tracks = gcnew array<SySal::Scanning::MIPIndexedEmulsionTrack ^>(trackcount);
			int i, j;
			for (i = 0; i < trackcount; i++)
			{
				Track2 *pT = ptracks + i;
				SySal::Tracking::MIPEmulsionTrackInfo ^info = gcnew SySal::Tracking::MIPEmulsionTrackInfo();
				array<SySal::Tracking::Grain ^> ^grains = savegrains ? gcnew array<SySal::Tracking::Grain ^>(pT->Grains) : nullptr;
				info->AreaSum = pT->AreaSum;
				info->BottomZ = pT->LastZ;
				info->Count = pT->Grains;
				info->Field = pT->Field;
				info->Intercept.X = pT->Intercept.X;
				info->Intercept.Y = pT->Intercept.Y;
				info->Intercept.Z = pT->Intercept.Z;
				info->Sigma = pT->Sigma;
				info->Slope.X = pT->Slope.X;
				info->Slope.Y = pT->Slope.Y;
				info->Slope.Z = pT->Slope.Z;
				info->TopZ = pT->FirstZ;
				if (savegrains)
				{
					Grain *pG = pT->pGrains;
					for (j = 0; j < pT->Grains; j++)
					{
						grains[j] = gcnew SySal::Tracking::Grain;
						grains[j]->Area = pG[j].Area;
						grains[j]->Position.X = pG[j].X;
						grains[j]->Position.Y = pG[j].Y;
						grains[j]->Position.Z = pG[j].Z;
					}
				}
				this->m_Tracks[i] = gcnew SySal::Scanning::MIPIndexedEmulsionTrack(info, grains, i);
			}
			array<SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::View::Side::LayerInfo> ^ layerinfo = gcnew array<SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::View::Side::LayerInfo>(Z->Length);
			for (i = 0; i < Z->Length; i++)
			{
				layerinfo[i].Z = Z[i];
				layerinfo[i].Grains = GrainCounts[i];
			}
			this->m_Layers = gcnew SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::View::Side::LayerInfoList(layerinfo);
		}

		void TrackingServer::IntView::SetSide(System::Boolean istop, SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::View::Side ^sd, System::Int32 tilex, System::Int32 tiley)
		{
			if (!initialized)
			{
				m_Tile.X = tilex;
				m_Tile.Y = tiley;
				initialized = true;
			}
			else if (m_Tile.X != tilex || m_Tile.Y != tiley) throw gcnew System::Exception("Can't change the tile position of a view.");					
			if (istop) m_Top = sd;
			else m_Bottom = sd;					
		}

		TrackingServer::IntView::IntView()
		{
			initialized = false;
		}

		TrackingServer::IntFragment::IntFragment(SySal::DAQSystem::TrackingServer ^owner, System::Int32 index, System::Int32 startview, System::Int32 views, bool savegrains, System::String ^path)
		{
			m_Owner = owner;
			this->m_Index = index;
			m_viewscompleted = 0;
			m_Path = path;		
			this->m_CodingMode = savegrains ? SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::FragmentCoding::Normal : SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::FragmentCoding::GrainSuppression;
			this->m_Id.Part0 = 0;
			this->m_Id.Part1 = 0;
			this->m_Id.Part2 = 0;
			this->m_Id.Part3 = index;
			this->m_StartView = startview;					
			this->m_Views = gcnew array<SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::View ^>(views);					
			int i;
			for (i = 0; i < views; i++)
				m_Views[i] = gcnew IntView();
		}

		bool TrackingServer::IntFragment::AddViewSide(int id, System::Boolean istop, SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::View::Side ^vwsd, System::Int32 tilex, System::Int32 tiley)
		{
			if (istop)
			{
				if (m_Views[id]->Top != nullptr) throw gcnew System::Exception("View already exists.");
				((IntView ^)m_Views[id])->SetSide(istop, vwsd, tilex, tiley);
				m_viewscompleted++;
			}
			else
			{
				if (m_Views[id]->Bottom != nullptr) throw gcnew System::Exception("View already exists.");
				((IntView ^)m_Views[id])->SetSide(istop, vwsd, tilex, tiley);
				m_viewscompleted++;
			}						
			if (m_viewscompleted == 2 * m_Views->Length)
			{
				while (true)
					try
					{
						System::IO::Stream ^m_Stream = gcnew System::IO::FileStream(m_Path + ".twr", System::IO::FileMode::Create, System::IO::FileAccess::Write, System::IO::FileShare::None);
						Save(m_Stream);
						m_Stream->Flush();
						m_Stream->Close();
						break;
					}
					catch (System::Exception ^x)				
					{
						m_Owner->SafeNotifyError(x->Message);
					}
				return true;
			}
			return false;
		}

	};

	bool SySal::DAQSystem::TrackingServer::EqualBytes(array<System::Byte> ^a1, array<System::Byte> ^a2)
	{
		DUMPBEGIN("EqualBytes");
		if (a1 == nullptr || a2 == nullptr) return false;
		int i, c;
		if ((c = a1->Length) != a2->Length) return false;				
		for (i = 0; i < c; i++)
			if (a1[i] == a2[i]) return false;
		return true;
		DUMPEND("EqualBytes");
	}

	void SySal::DAQSystem::TrackingServer::FillBytes(void *pdest, array<System::Byte> ^a, int startpoint)
	{
		DUMPBEGIN("EqualBytes");
		int c = a->Length;
		int i;
		for (i = startpoint; i < c; i++)
			((byte *)pdest)[i] = a[i];
		DUMPEND("EqualBytes");
	}

	void SySal::DAQSystem::TrackingServer::ReadBytes(void *pdest, array<System::Byte> ^a, int &readpoint, int count)
	{
		//DUMPBEGIN("ReadBytes");
		int c = a->Length;
		int i, r = readpoint;
		for (i = 0; i < count; i++)
			((byte *)pdest)[i] = a[r++];
		readpoint = r;
		//DUMPEND("ReadBytes");
	}

	void SySal::DAQSystem::TrackingServer::ZExpand(Track2 *pTracks, UINT Count, float ZBase, float shrinkage)
	{
		DUMPBEGIN("ZExpand");
		UINT i, j;
		for (i = 0; i < Count; i++)
			for (j = 0; j < pTracks[i].Grains; j++)
				pTracks[i].pGrains[j].Z = ((pTracks[i].pGrains[j].Z - ZBase) * shrinkage + ZBase) * RefractiveShrinkage;
		DUMPEND("ZExpand");
	}

	void SySal::DAQSystem::TrackingServer::XYOffset(Track2 *pTracks, UINT Count)
	{
		DUMPBEGIN("XYOffset");
		UINT i, j;
		for (i = 0; i < Count; i++)
			for (j = 0; j < pTracks[i].Grains; j++)
			{
				pTracks[i].pGrains[j].X -= ViewCenterX;
				pTracks[i].pGrains[j].Y -= ViewCenterY;
			};
		DUMPEND("XYOffset");
	}

	UINT SySal::DAQSystem::TrackingServer::DiscardInvalidTracks(Track2 *pTracks, UINT Count)
	{
		DUMPBEGIN("DiscardInvalidTracks");
		UINT i, j;
		for (i = j = 0; i < Count; i++)
		{
			if (pTracks[i].Valid)
			{
				pTracks[j].Field = pTracks[i].Field;
				pTracks[j].FirstZ = pTracks[i].FirstZ;
				pTracks[j].AreaSum = pTracks[i].AreaSum;
				pTracks[j].Intercept = pTracks[i].Intercept;
				pTracks[j].LastZ = pTracks[i].LastZ;
				pTracks[j].Grains = pTracks[i].Grains;
				pTracks[j].Sigma = pTracks[i].Sigma;
				pTracks[j].Slope = pTracks[i].Slope;
				memcpy(pTracks[j].pGrains, pTracks[i].pGrains, sizeof(Grain) * pTracks[i].Grains);
				pTracks[j].Valid = pTracks[i].Valid;
				j++;
			};
		};
		return j;
		DUMPEND("DiscardInvalidTracks");
	}

	bool SySal::DAQSystem::TrackingServer::ReadConfig(SySalConfig *pC, array<System::Byte> ^i_config)
	{
		DUMPBEGIN("ReadConfig");
		if (i_config->Length < sizeof(int)) return false;
		int readpoint = 0;
		ReadBytes(&(pC->CountOfItems), i_config, readpoint, sizeof(int));
		if (pC->CountOfItems > 0)
		{
			if (i_config->Length != (sizeof(int) + pC->CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))) return false;					
			pC->pItems = (char *)malloc(pC->CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
			ReadBytes(pC->pItems, i_config, readpoint, pC->CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		}
		return true;
		DUMPEND("ReadConfig");
	}

	bool SySal::DAQSystem::TrackingServer::SetupObject(array<System::Byte> ^i_clsid, array<System::Byte> ^i_config, array<System::Byte> ^ %r_clsid, array<System::Byte> ^ %r_config, IID i_interface, void **p_obj)
	{
		DUMPBEGIN("SetupObject");
		if (i_clsid->Length != sizeof(CLSID)) return false;				
		if (*p_obj == 0 || EqualBytes(r_clsid, i_clsid))
		{
			if (*p_obj)
			{
				((IUnknown *)p_obj)->Release();
				*p_obj = 0;
				r_clsid = nullptr;
			}
			CLSID clsid;
			FillBytes(&clsid, i_clsid, 0);
			IUnknown *pTemp = 0;				
			if (CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, i_interface, (void **)(&pTemp)) != S_OK)
			{
				if (pTemp) pTemp->Release();
				return false;
			}
			*p_obj = pTemp;
			r_clsid = i_clsid;
		}
		if (!EqualBytes(r_config, i_config))
		{
			SySalConfig C;
			C.CountOfItems = 0;
			C.pItems = 0;
			if (!ReadConfig(&C, i_config))
			{
				if (C.pItems) free(C.pItems);
				return false;
			}
			r_config = i_config;
			ISySalObject *iOb = 0;
			((IUnknown *)*p_obj)->QueryInterface(IID_ISySalObject, (void **)&iOb);					
			if (iOb->SetConfig(&C) != S_OK)
			{
				r_config = nullptr;
				if (C.pItems) free(C.pItems);
				iOb->Release();														
				return false;
			}
			if (C.pItems) free(C.pItems);
			iOb->Release();
		}		
		return true;
		DUMPEND("SetupObject");
	}

	bool SySal::DAQSystem::TrackingServer::SetConfig(array<System::Byte> ^ trackerconfig_t, array<System::Byte> ^ trackerclsid_t, array<System::Byte> ^ trackerconfig_b, array<System::Byte> ^ trackerclsid_b, array<System::Byte> ^ fitterconfig_t, array<System::Byte> ^ fitterclsid_t, array<System::Byte> ^ fitterconfig_b, array<System::Byte> ^ fitterclsid_b, array<System::Byte> ^ camspec)
	{	
		DUMPBEGIN("SetConfig");
		bool ret;
		void *pTemp;

		if (camspec->Length != sizeof(CameraSpec2))
		{
			SafeNotifyError("Wrong length for CameraSpec byte stream.");
			return false;
		}
		CameraSpec2 CAM;
		FillBytes(&CAM, camspec, 0);
		RefractiveShrinkage = CAM.RefractiveShrinkage;
		ViewCenterX = CAM.Width / 2 * CAM.PixelToMicronX;
		ViewCenterY = CAM.Height / 2 * CAM.PixelToMicronY;

		pTemp = pTracker_T;
		ret = SetupObject(trackerclsid_t, trackerconfig_t, m_TrackerCLSID_T, m_TrackerConfig_T, IID_ITracker4, &pTemp);
		pTracker_T = (ITracker4 *)pTemp;
		if (!ret) 
		{
			SafeNotifyError("Wrong class/configuration for top tracker.");
			return false;
		}

		if (pTracker_T->SetCameraSpec(*(CameraSpec *)(void *)&CAM) != S_OK)
		{
			SafeNotifyError("Camera specification configuration refused by top tracker.");
			return false;
		}

		pTemp = pTracker_B;
		ret = SetupObject(trackerclsid_b, trackerconfig_b, m_TrackerCLSID_B, m_TrackerConfig_B, IID_ITracker4, &pTemp);
		pTracker_B = (ITracker4 *)pTemp;
		if (!ret)
		{
			SafeNotifyError("Wrong class/configuration for bottom tracker.");
			return false;
		}

		if (pTracker_B->SetCameraSpec(*(CameraSpec *)(void *)&CAM) != S_OK)
		{
			SafeNotifyError("Camera specification configuration refused by bottom tracker.");
			return false;
		}

		if (pCorrectionData) free(pCorrectionData);
		pCorrectionData = 0;
		FitCorrectionDataSize = 0;			

		UINT cds;
		pTemp = pFitter_T;
		ret = SetupObject(fitterclsid_t, fitterconfig_t, m_FitterCLSID_T, m_FitterConfig_T, IID_ITrackFitter3, &pTemp);
		pFitter_T = (ITrackFitter3 *)pTemp;
		if (!ret)
		{
			SafeNotifyError("Wrong class/configuration for top trackfitter.");
			return false;
		}
		pFitter_T->GetCorrectionDataSize(&cds);
		FitCorrectionDataSize = cds;

		pTemp = pFitter_B;
		ret = SetupObject(fitterclsid_b, fitterconfig_b, m_FitterCLSID_B, m_FitterConfig_B, IID_ITrackFitter3, &pTemp);
		pFitter_B = (ITrackFitter3 *)pTemp;
		if (!ret)
		{
			SafeNotifyError("Wrong class/configuration for bottom trackfitter.");
			return false;
		}
		pFitter_T->GetCorrectionDataSize(&cds);
		if (cds > FitCorrectionDataSize) FitCorrectionDataSize = cds;
		if (FitCorrectionDataSize > 0) pCorrectionData = malloc(FitCorrectionDataSize);

		return true;
		DUMPEND("SetConfig");
	}

	void SySal::DAQSystem::TrackingServer::SafeNotifyError(System::String ^err)
	{
		DUMPBEGIN("SafeNotifyError");
		if (NotifyError != nullptr) NotifyError(err);
		DUMPEND("SafeNotifyError");
	}

	SySal::DAQSystem::TrackingServer::TrackingServer()
	{
		DUMPBEGIN("TrackingServer");
		m_TrackerCLSID_T = nullptr;
		m_TrackerConfig_T = nullptr;
		m_TrackerCLSID_B = nullptr;
		m_TrackerConfig_B = nullptr;
		m_FitterCLSID_T = nullptr;
		m_FitterConfig_T = nullptr;
		m_FitterCLSID_B = nullptr;
		m_FitterConfig_B = nullptr;
		pTracker_T = 0;
		pTracker_B = 0;
		pFitter_T = 0;
		pFitter_B = 0;
		m_Fragment = nullptr;
		pClusters = (Cluster *)malloc(sizeof(Cluster) * (MaxClusters = 10000));
		pTracks = (Track2 *)malloc(sizeof(Track2) * (MaxTracks = 100000));
		GrainsPerTrack = 0;
		MaxGrains = 0;
		pGrains = 0;
		pCorrectionData = 0;
		FitCorrectionDataSize = 0;
		HMutex = CreateMutex(NULL, FALSE, NULL);
		NotifyCall = nullptr;
		NotifyTracks = nullptr;
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		System::DateTime start = System::DateTime::Now;
		StartupGUID = (((((start.Year * 365 + start.DayOfYear) * 24 + start.Hour) * 60 + start.Minute) * 60 + start.Second) * 1000 + start.Millisecond);
		DUMPEND("TrackingServer");
	}

	SySal::DAQSystem::TrackingServer::TrackingServer(dNotifyCall ^ncall, dNotifyTracks ^ntracks, dNotifyError ^nerr)
	{
		DUMPBEGIN("TrackingServer0");
		m_TrackerCLSID_T = nullptr;
		m_TrackerConfig_T = nullptr;
		m_TrackerCLSID_B = nullptr;
		m_TrackerConfig_B = nullptr;
		m_FitterCLSID_T = nullptr;
		m_FitterConfig_T = nullptr;
		m_FitterCLSID_B = nullptr;
		m_FitterConfig_B = nullptr;
		pTracker_T = 0;
		pTracker_B = 0;
		pFitter_T = 0;
		pFitter_B = 0;
		m_Fragment = nullptr;
		pClusters = (Cluster *)malloc(sizeof(Cluster) * (MaxClusters = 10000));
		pTracks = (Track2 *)malloc(sizeof(Track2) * (MaxTracks = 100000));
		GrainsPerTrack = 0;
		MaxGrains = 0;
		pGrains = 0;
		pCorrectionData = 0;
		FitCorrectionDataSize = 0;
		HMutex = CreateMutex(NULL, FALSE, NULL);
		NotifyCall = ncall;
		NotifyTracks = ntracks;
		NotifyError = nerr;
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		System::DateTime start = System::DateTime::Now;
		StartupGUID = (((((start.Year * 365 + start.DayOfYear) * 24 + start.Hour) * 60 + start.Minute) * 60 + start.Second) * 1000 + start.Millisecond);
		DUMPEND("TrackingServer0");
	}

	SySal::DAQSystem::TrackingServer::~TrackingServer()
	{
		DUMPBEGIN("~TrackingServer");
		WaitForSingleObject(HMutex, INFINITE);
		if (pTracker_T) pTracker_T->Release();
		if (pTracker_B) pTracker_B->Release();
		if (pFitter_T) pFitter_T->Release();
		if (pFitter_B) pFitter_B->Release();
		if (pClusters) free(pClusters);
		if (pTracks) free(pTracks);
		if (pGrains) free(pGrains);
		if (pCorrectionData) free(pCorrectionData);
		CloseHandle(HMutex);
		DUMPEND("~TrackingServer0");
	}

	System::Int64 SySal::DAQSystem::TrackingServer::GUID::get()
	{
		return StartupGUID;
	}

	System::Boolean SySal::DAQSystem::TrackingServer::OpenFragment(System::String ^filepath, System::Int32 index, System::Int32 startview, System::Int32 views, array<System::Byte> ^ camspec, array<System::Byte> ^ trackerconfig_t,  array<System::Byte> ^ trackerclsid_t, array<System::Byte> ^ trackerconfig_b, array<System::Byte> ^ trackerclsid_b, array<System::Byte> ^ fitterconfig_t,  array<System::Byte> ^ fitterclsid_t, array<System::Byte> ^ fitterconfig_b,  array<System::Byte> ^ fitterclsid_b, System::Int32 maxtracks, System::Boolean savegrains, System::Boolean useslopepreset, System::Single slopepresetminx, System::Single slopepresetmaxx, System::Single slopepresetminy, System::Single slopepresetmaxy)
	{				
		DUMPBEGIN("OpenFragment");
		System::DateTime ms_start = System::DateTime::Now;
		WaitForSingleObject(HMutex, INFINITE);
		try
		{
			if (SetConfig(trackerconfig_t, trackerclsid_t, trackerconfig_b, trackerclsid_b, fitterconfig_t, fitterclsid_t, fitterconfig_b, fitterclsid_b, camspec) == false) return false;
			this->m_Fragment = gcnew IntFragment(this, index, startview, views, savegrains, filepath);
			if (maxtracks > MaxTracks)
			{
				Track2 *pT = (Track2 *)malloc(sizeof(Track2) * maxtracks);
				if (pT)
				{
					free(pTracks);
					pTracks = pT;
					MaxTracks = maxtracks;
				}
			}	
			int g;
			pTracker_T->GetMaxGrainsPerTrack(&g);
			GrainsPerTrack = g;
			pTracker_B->GetMaxGrainsPerTrack(&g);
			if (g > GrainsPerTrack) GrainsPerTrack = g;
			if (MaxTracks * GrainsPerTrack > MaxGrains)
			{
				if (pGrains) pGrains = (Grain *)realloc(pGrains, sizeof(Grain) * GrainsPerTrack * MaxTracks);
				else pGrains = (Grain *)malloc(sizeof(Grain) * GrainsPerTrack * MaxTracks);
				if (pGrains == 0) 
				{
					MaxGrains = 0;
					SafeNotifyError("Can't allocate space for grains. " + (GrainsPerTrack * MaxTracks).ToString() + " bytes requested.");
					return false;
				}
				MaxGrains = MaxTracks * GrainsPerTrack;
			}
			for (g = 0; g < MaxTracks; g++)
			{
				pTracks[g].pGrains = pGrains + GrainsPerTrack * g;
				pTracks[g].pCorrection = (BYTE *)pCorrectionData;
			}				
			return true;
		}
		finally
		{
			ReleaseMutex(HMutex);
			if (NotifyCall != nullptr) NotifyCall((System::DateTime::Now - ms_start).TotalMilliseconds);
		}
		DUMPEND("OpenFragment");
	}

	System::Boolean SySal::DAQSystem::TrackingServer::SendViewSide(System::Int32 Field, System::Int32 TileX, System::Int32 TileY, System::Single PosX, System::Single PosY, System::Single MapPosX, System::Single MapPosY, System::Single MapXX, System::Single MapXY, System::Single MapYX, System::Single MapYY, array<System::Single> ^ Z, array<System::Byte> ^ clusterlayers, System::Boolean IsTop, System::Single ztop, System::Single zbottom, System::Single zbase, System::Single shrinkage)
	{
		DUMPBEGIN("SendViewSide");
		System::DateTime ms_start = System::DateTime::Now;
		WaitForSingleObject(HMutex, INFINITE);
		int totalclusters = 0;
		try
		{
			if (m_Fragment == nullptr)
			{
				SafeNotifyError("No fragment open for writing.");
				return false;
			}					
			int layers = Z->Length;
			array<System::Int32> ^ GrainCount = gcnew array<System::Int32>(Z->Length);
			ITracker4 *pTracker = IsTop ? pTracker_T : pTracker_B;
			ITrackFitter3 *pTrackFitter = IsTop ? pFitter_T : pFitter_B;
			pTracker->StartFilling2(IsTop ? 0 : 1);
			NetCluster TC;
			Cluster *pc;
			int i, lay;
			int bytepos = 0;
			for (lay = 0; lay < layers; lay++)
			{
				if (clusterlayers->Length - bytepos < sizeof(int))
				{
					SafeNotifyError("Byte stream with clusters does not appear well-formed (Step #1).");
					return false;
				}
				int clustercount;
				ReadBytes(&clustercount, clusterlayers, bytepos, sizeof(int));
				GrainCount[lay] = clustercount;
				if (clustercount > MaxClusters)
				{
					Cluster *pCtemp = (Cluster *)malloc(sizeof(Cluster) * clustercount);
					if (pCtemp)
					{
						free(pClusters);
						pClusters = pCtemp;
						MaxClusters = clustercount;
					}
					else
					{
						SafeNotifyError("Can't allocate space for clusters. " + clustercount.ToString() + " bytes required.");
						return false;						
					}
				}
				if (clusterlayers->Length - bytepos < (sizeof(NetCluster) * clustercount))
				{
					SafeNotifyError("Byte stream with clusters does not appear well-formed (Step #2).");
					return false;
				}
				for (i = 0; i < clustercount; i++)
				{
					ReadBytes(&TC, clusterlayers, bytepos, sizeof(NetCluster));
					pc = pClusters + i;
					pc->X = TC.X;
					pc->Y = TC.Y;
					pc->Area = TC.Area;
					pc->Inertia.IXX = pc->Inertia.IXY = pc->Inertia.IYY = 0.0;
					pc->GrayLevel = 0;
				}
				totalclusters += clustercount;
				if (clustercount > 0 && pTracker->PutClusters(pClusters, clustercount, Z[lay]) != S_OK)
				{
					SafeNotifyError("Clusters refused by tracker.");
					return false;
				}
			}
			int ntracks = MaxTracks;
			char tempstr[512];
			sprintf(tempstr, "Layers: %d Clusters: %d Tracks: %d\n" , lay, totalclusters, ntracks);
			DUMP("Tracking\n");			
			DUMP(tempstr);			
			pTracker->GetTracks2(pTracks, &ntracks, 0, layers - 1);
			for (i = 0; i < ntracks; i++)
				pTracks[i].Field = Field;
			DUMP("Processing\n");
			ZExpand(pTracks, ntracks, zbase, shrinkage);
			XYOffset(pTracks, ntracks);
			DUMP("Fitting\n");
			pTrackFitter->Fit3(pTracks, &ntracks, zbase * RefractiveShrinkage, (ztop - zbottom) * RefractiveShrinkage * shrinkage);
			DUMP("Discard\n");
			ntracks = DiscardInvalidTracks(pTracks, ntracks);
			if (NotifyTracks != nullptr) NotifyTracks(ntracks);
			DUMP("AddViewSide\n");
			bool ret = m_Fragment->AddViewSide(Field, IsTop, gcnew IntSide(ztop * RefractiveShrinkage, zbottom * RefractiveShrinkage, PosX, PosY, MapPosX, MapPosY, MapXX, MapXY, MapYX, MapYY, ntracks, pTracks, layers, Z, GrainCount, m_Fragment->CodingMode != SySal::Scanning::Plate::IO::OPERA::RawData::Fragment::FragmentCoding::GrainSuppression), TileX, TileY);
			if (ret) m_Fragment = nullptr;		
			return true;
		}
		catch (System::Exception ^x)
		{
			SafeNotifyError(x->Message);
		}
		finally
		{
			ReleaseMutex(HMutex);
			if (NotifyCall != nullptr) NotifyCall((System::DateTime::Now - ms_start).TotalMilliseconds);
		}
		DUMPEND("SendViewSide");
	}

	Object^ SySal::DAQSystem::TrackingServer::InitializeLifetimeService ()
	{
		return nullptr;
	}
}