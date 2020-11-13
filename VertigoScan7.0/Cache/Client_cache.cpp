#include "StdAfx.h"
#include "Client.h"
#using <mscorlib.dll>
#using <System.dll>
#using <System.Data.dll>
#ifdef ENABLE_NET
#using "SySalCore.dll"
#using "OperaDb.dll"
#using "OperaDbLoginTools.dll"
#endif

#undef _DUMP_

#ifdef _DUMP_
#include <stdio.h>
#define DUMP(x)\
{\
	FILE *f = fopen("c:\\sysal2000\\vs6win.txt", "a+t");\
	fprintf(f, "\n%s", x);\
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

int instances = 0;

namespace SySal
{
	namespace DAQSystem
	{
		void NetPackagedView::ToDisk(System::IO::BinaryWriter ^bw)
		{
			try
			{
				int i, n;
				bw->Write(Field);
				bw->Write(TileX);
				bw->Write(TileY);
				bw->Write(PosX);
				bw->Write(PosY);
				bw->Write(MapPosX);
				bw->Write(MapPosY);
				bw->Write(MapXX);
				bw->Write(MapXY);
				bw->Write(MapYX);
				bw->Write(MapYY);
				bw->Write((n = Z->Length));
				for (i = 0; i < n; i++)
					bw->Write(Z[i]);
				bw->Write((n = ClusterLayers->Length));
				bw->Write(ClusterLayers);
				bw->Write(IsTop);
				bw->Write(ZTop);
				bw->Write(ZBottom);
				bw->Write(ZBase);
				bw->Write(Shrinkage);
			}
			catch (System::Exception ^)
			{
				::MessageBox(0, "Error writing ScanGrid cache file.\r\nCheck disk operation and available space.", "Fatal error", MB_OK);
				ExitProcess(-1);
			}
		}

		NetPackagedView ^NetPackagedView::FromDisk(System::IO::BinaryReader ^br)
		{
			while (true)
				try
				{
					NetPackagedView ^v = gcnew NetPackagedView();
					int i, n;
					v->Field = br->ReadInt32();
					v->TileX = br->ReadInt32();
					v->TileY = br->ReadInt32();
					v->PosX = br->ReadSingle();
					v->PosY = br->ReadSingle();
					v->MapPosX = br->ReadSingle();
					v->MapPosY = br->ReadSingle();
					v->MapXX = br->ReadSingle();
					v->MapXY = br->ReadSingle();
					v->MapYX = br->ReadSingle();
					v->MapYY = br->ReadSingle();
					n = br->ReadInt32();
					v->Z = gcnew array<System::Single>(n);
					for (i = 0; i < n; i++)
						v->Z[i] = br->ReadSingle();
					n = br->ReadInt32();
					v->ClusterLayers = br->ReadBytes(n);
					v->IsTop = br->ReadBoolean();
					v->ZTop = br->ReadSingle();
					v->ZBottom = br->ReadSingle();
					v->ZBase = br->ReadSingle();
					v->Shrinkage = br->ReadSingle();
					return v;
				}
				catch (System::OutOfMemoryException ^) {}
		}

		void NetPackagedFragment::ToDisk(System::Int32 cacheindex)
		{
			try
			{
				System::IO::FileStream ^wstr = gcnew System::IO::FileStream(TrackingClient::CacheFile(cacheindex), System::IO::FileMode::Create, System::IO::FileAccess::ReadWrite, System::IO::FileShare::None);
				System::IO::BinaryWriter ^bw = gcnew System::IO::BinaryWriter(wstr);
				int i, n;
				bw->Write(FilePath);
				bw->Write(Index);
				bw->Write(StartView);
				bw->Write(CamSpec->Length);
				bw->Write(CamSpec);
				bw->Write(TrackerCLSID_T->Length);
				bw->Write(TrackerCLSID_T);
				bw->Write(TrackerCLSID_B->Length);
				bw->Write(TrackerCLSID_B);
				bw->Write(TrackerConfig_T->Length);
				bw->Write(TrackerConfig_T);
				bw->Write(TrackerConfig_B->Length);
				bw->Write(TrackerConfig_B);
				bw->Write(FitterCLSID_T->Length);
				bw->Write(FitterCLSID_T);
				bw->Write(FitterCLSID_B->Length);
				bw->Write(FitterCLSID_B);
				bw->Write(FitterConfig_T->Length);
				bw->Write(FitterConfig_T);
				bw->Write(FitterConfig_B->Length);
				bw->Write(FitterConfig_B);
				bw->Write(MaxTracks);
				bw->Write(SaveGrains);
				bw->Write(UseSlopePreset);
				bw->Write(SlopePresetMinX);
				bw->Write(SlopePresetMinY);
				bw->Write(SlopePresetMaxX);
				bw->Write(SlopePresetMaxY);
				bw->Write((n = ViewInfo->Length));
				for (i = 0; i < n; i++)
					ViewInfo[i]->ToDisk(bw);
				bw->Flush();
				wstr->Close();
			}
			catch (System::Exception ^)
			{
				::MessageBox(0, "Error writing ScanGrid cache file.\r\nCheck disk operation and available space.", "Fatal error", MB_OK);
				ExitProcess(-1);
			}
		}

		NetPackagedFragment ^NetPackagedFragment::FromDisk(System::Int32 cacheindex)
		{
			System::IO::FileStream ^rstr = nullptr;
			while (true)
				try
				{
					rstr = gcnew System::IO::FileStream(TrackingClient::CacheFile(cacheindex), System::IO::FileMode::Create, System::IO::FileAccess::ReadWrite, System::IO::FileShare::None);
					System::IO::BinaryReader ^br = gcnew System::IO::BinaryReader(rstr);
					NetPackagedFragment ^f = gcnew NetPackagedFragment();
					int i, n;
					f->FilePath = br->ReadString();
					f->Index = br->ReadInt32();
					f->StartView = br->ReadInt32();
					f->CamSpec = br->ReadBytes(br->ReadInt32());
					f->TrackerCLSID_T = br->ReadBytes(br->ReadInt32());
					f->TrackerCLSID_B = br->ReadBytes(br->ReadInt32());
					f->TrackerConfig_T = br->ReadBytes(br->ReadInt32());
					f->TrackerConfig_B = br->ReadBytes(br->ReadInt32());
					f->FitterCLSID_T = br->ReadBytes(br->ReadInt32());
					f->FitterCLSID_B = br->ReadBytes(br->ReadInt32());
					f->FitterConfig_T = br->ReadBytes(br->ReadInt32());
					f->FitterConfig_B = br->ReadBytes(br->ReadInt32());
					f->MaxTracks = br->ReadInt32();
					f->SaveGrains = br->ReadBoolean();
					f->UseSlopePreset = br->ReadBoolean();
					f->SlopePresetMinX = br->ReadSingle();
					f->SlopePresetMinY = br->ReadSingle();
					f->SlopePresetMaxX = br->ReadSingle();
					f->SlopePresetMaxY = br->ReadSingle();
					f->ViewInfo = gcnew array<NetPackagedView ^>(n = br->ReadInt32());
					for (i = 0; i < n; i++)
						f->ViewInfo[i] = NetPackagedView::FromDisk(br);
					return f;
				}
				catch (System::OutOfMemoryException ^) 
				{
					if (rstr != nullptr)
					{
						rstr->Close();
						rstr = nullptr;
					}
				}
		}


		NetPackagedFragment::NetPackagedFragment() {}

		NetPackagedFragment::NetPackagedFragment(array<System::Byte> ^camspec, array<System::Byte> ^trackerclsid_t, array<System::Byte> ^trackerclsid_b, array<System::Byte> ^trackerconfig_t, array<System::Byte> ^trackerconfig_b, 
				array<System::Byte> ^fitterclsid_t, array<System::Byte> ^fitterclsid_b, array<System::Byte> ^fitterconfig_t, array<System::Byte> ^fitterconfig_b, 
				IO_VS_Fragment2 *pFrag, char *outname, int maxtracks, bool usepresetslope, float slopeminx, float slopemaxx, float slopeminy, float slopemaxy, float shrinkage)
		{
			int i;
			this->CamSpec = camspec;
			this->FilePath = gcnew System::String(outname);
			this->FitterCLSID_B = fitterclsid_b;
			this->FitterCLSID_T = fitterclsid_t;
			this->FitterConfig_B = fitterconfig_b;
			this->FitterConfig_T = fitterconfig_t;
			this->TrackerCLSID_B = trackerclsid_b;
			this->TrackerCLSID_T = trackerclsid_t;
			this->TrackerConfig_B = trackerconfig_b;
			this->TrackerConfig_T = trackerconfig_t;
			this->Index = pFrag->Fragment.Index;
			this->MaxTracks = maxtracks;
			this->SaveGrains = (pFrag->Fragment.CodingMode != VS_COMPRESSION_GRAIN_SUPPRESSION);
			this->UseSlopePreset = usepresetslope;
			this->SlopePresetMinX = slopeminx;
			this->SlopePresetMaxX = slopemaxx;
			this->SlopePresetMinY = slopeminy;
			this->SlopePresetMaxY = slopemaxy;	
			this->StartView = pFrag->Fragment.StartView;
			this->ViewInfo = gcnew array<NetPackagedView ^>(2 * pFrag->Fragment.CountOfViews);
			for (i = 0; i < this->ViewInfo->Length; i++)
			{
				int f = i / 2;
				int s = i % 2;
				VS_View2 VW2 = pFrag->Fragment.pViews[f];
				NetPackagedView ^vw = gcnew NetPackagedView();
				vw->Field = f;
				vw->IsTop = (s == 0);
				vw->TileX = VW2.TileX;
				vw->TileY = VW2.TileY;
				vw->PosX = VW2.X[s];
				vw->PosY = VW2.Y[s];
				vw->MapPosX = VW2.MapX[s];
				vw->MapPosY = VW2.MapY[s];
				vw->MapXX = VW2.ImageMat[s][0][0];
				vw->MapXY = VW2.ImageMat[s][0][1];
				vw->MapYX = VW2.ImageMat[s][1][0];
				vw->MapYY = VW2.ImageMat[s][1][1];
				vw->Shrinkage = shrinkage;
				if (s == 0)
				{
					vw->ZTop = VW2.RelevantZs.TopExt;
					vw->ZBottom = VW2.RelevantZs.TopInt;
					vw->ZBase = VW2.RelevantZs.TopInt;
				}
				else
				{
					vw->ZTop = VW2.RelevantZs.BottomInt;
					vw->ZBottom = VW2.RelevantZs.BottomExt;
					vw->ZBase = VW2.RelevantZs.BottomInt;
				}
				vw->Z = gcnew array<System::Single>(VW2.Layers[s].Count);
				int lay;
				int totalclusters;
				for (lay = totalclusters = 0; lay < VW2.Layers[s].Count; lay++)
				{
					vw->Z[lay] = VW2.Layers[s].pLayerInfo[lay].Z;
					totalclusters += VW2.Layers[s].pLayerInfo[lay].Clusters; 
				}
				System::IO::MemoryStream ^memstr = gcnew System::IO::MemoryStream(VW2.Layers[s].Count * sizeof(int) + (sizeof(NetCluster) * totalclusters) + sizeof(int));
				System::IO::BinaryWriter ^wb = gcnew System::IO::BinaryWriter(memstr);				
				Grain *pG = VW2.pTracks[s][0].pGrains;
				for (lay = 0; lay < VW2.Layers[s].Count; lay++)
				{
					int clusters = VW2.Layers[s].pLayerInfo[lay].Clusters;
					wb->Write(clusters);
					int j;					
					for (j = 0; j < clusters; j++)
					{						
						wb->Write(pG->X);
						wb->Write(pG->Y);
						wb->Write((int)(pG++->Area));
					}
				}
				wb->Flush();
				wb->Close();
				vw->ClusterLayers = memstr->ToArray();				
				this->ViewInfo[i] = vw;				
			}
		}

		NetPackagedFragment::NetPackagedFragment(array<System::Byte> ^camspec, array<System::Byte> ^trackerclsid_t, array<System::Byte> ^trackerclsid_b, array<System::Byte> ^trackerconfig_t, array<System::Byte> ^trackerconfig_b, 
				array<System::Byte> ^fitterclsid_t, array<System::Byte> ^fitterclsid_b, array<System::Byte> ^fitterconfig_t, array<System::Byte> ^fitterconfig_b, 
				int index, int codingmode, int views, int startview, char *outname, int maxtracks, bool usepresetslope, float slopeminx, float slopemaxx, float slopeminy, float slopemaxy, float shrinkage)
		{
			int i;
			this->CamSpec = camspec;
			this->FilePath = gcnew System::String(outname);
			this->FitterCLSID_B = fitterclsid_b;
			this->FitterCLSID_T = fitterclsid_t;
			this->FitterConfig_B = fitterconfig_b;
			this->FitterConfig_T = fitterconfig_t;
			this->TrackerCLSID_B = trackerclsid_b;
			this->TrackerCLSID_T = trackerclsid_t;
			this->TrackerConfig_B = trackerconfig_b;
			this->TrackerConfig_T = trackerconfig_t;
			this->Index = index;
			this->MaxTracks = maxtracks;
			this->SaveGrains = (codingmode != VS_COMPRESSION_GRAIN_SUPPRESSION);
			this->UseSlopePreset = usepresetslope;
			this->SlopePresetMinX = slopeminx;
			this->SlopePresetMaxX = slopemaxx;
			this->SlopePresetMinY = slopeminy;
			this->SlopePresetMaxY = slopemaxy;	
			this->StartView = startview;
			this->ViewInfo = gcnew array<NetPackagedView ^>(2 * views);
			for (i = 0; i < this->ViewInfo->Length; i++)
				this->ViewInfo[i] = nullptr;
		}

		System::Exception ^ErrorLogger::Error::get()
		{
			DUMPBEGIN("ErrorLogger::Error::get");
			return m_Exception;
			DUMPEND("ErrorLogger::Error::get");
		}

		void ErrorLogger::Error::set(System::Exception ^x)
		{
			DUMPBEGIN("ErrorLogger::Error::set");
			m_Exception = x;
			DUMPEND("ErrorLogger::Error::get");
		}

		void ErrorLogger::Clear()
		{
			DUMPBEGIN("ErrorLogger::Error::Clear");
			m_Exception = nullptr;
			DUMPEND("ErrorLogger::Error::get");
		}

		bool ErrorLogger::IsOK::get()
		{
			DUMPBEGIN("ErrorLogger::IsOK::get");
			return (m_Exception == nullptr);
			DUMPEND("ErrorLogger::IsOK::get");
		}

		TrackingClientConnection::TrackingClientConnection(System::String ^servername, System::String ^machinename, SySal::DAQSystem::TrackingServer ^server, System::Collections::ArrayList ^dataqueue, System::Collections::ArrayList ^activebuffers, HANDLE hDataQueueMutex, HANDLE hTerminate, ErrorLogger ^logger)
			: m_ServerName(servername), m_Server(server), m_DataQueue(dataqueue), m_ActiveBuffers(activebuffers), HDataQueueMutex(hDataQueueMutex), HTerminate(hTerminate), m_MachineName(machinename), m_Logger(logger)
		{
			m_Frag = nullptr;
			m_Exception = nullptr;
			Active = false;
			m_Thread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &TrackingClientConnection::Execute));
			m_Thread->Name = this->m_MachineName + "_Execute";
			m_Thread->Start();
		}

		void TrackingClientConnection::Join()
		{
			DUMPBEGIN("TrackingClientConnection::Join");
			if (m_Thread != nullptr) m_Thread->Join();			
			DUMPEND("TrackingClientConnection::Join");
		}

		void TrackingClientConnection::SendData()
		{
			DUMPBEGIN("TrackingClientConnection::SendData");
			try
			{
				if (m_Server->OpenFragment(m_Frag->FilePath, m_Frag->Index, m_Frag->StartView, m_Frag->ViewInfo->Length / 2, m_Frag->CamSpec, m_Frag->TrackerConfig_T, m_Frag->TrackerCLSID_T, m_Frag->TrackerConfig_B, m_Frag->TrackerCLSID_B,
					m_Frag->FitterConfig_T, m_Frag->FitterCLSID_T, m_Frag->FitterConfig_B, m_Frag->FitterCLSID_B, m_Frag->MaxTracks, m_Frag->SaveGrains, m_Frag->UseSlopePreset, m_Frag->SlopePresetMinX, m_Frag->SlopePresetMaxX,
					m_Frag->SlopePresetMinY, m_Frag->SlopePresetMaxY))				
				{
					int i;
					for (i = 0; i < m_Frag->ViewInfo->Length; i++)
					{
						NetPackagedView ^nw = m_Frag->ViewInfo[i];
						if (m_Server->SendViewSide(nw->Field, nw->TileX, nw->TileY, nw->PosX, nw->PosY, nw->MapPosX, nw->MapPosY, nw->MapXX, nw->MapXY, nw->MapYX, nw->MapYY, nw->Z, nw->ClusterLayers, nw->IsTop, nw->ZTop, nw->ZBottom, nw->ZBase, nw->Shrinkage) == false) break;
					}
				}
				System::IO::File::Move(m_Frag->FilePath + ".twr", m_Frag->FilePath);
				m_Exception = nullptr;
				m_Frag = nullptr;
			}
			catch (System::Exception ^x)
			{
				m_Exception = x;
			}
			DUMPEND("TrackingClientConnection::SendData");
		}

		void TrackingClientConnection::Execute()
		{
			DUMPBEGIN("TrackingClientConnection::Execute");
			HANDLE HEvs[2];
			HEvs[0] = HTerminate;
			HEvs[1] = HDataQueueMutex;			
			System::Int64 SrvGUID = 0;
			System::Int32 index = 0;
			volatile DWORD waitexit = 0;
			while ((waitexit = WaitForMultipleObjects(2, HEvs, FALSE, 1000)) != WAIT_OBJECT_0)
			{				
				if (waitexit != WAIT_OBJECT_0 + 1)// ReleaseMutex(HDataQueueMutex);
				continue;
				try
				{
					if (m_Server == nullptr)
					{
						ReleaseMutex(HDataQueueMutex);
						System::String ^str = L"tcp://" + m_ServerName + L":1808/TrackServer_" + m_MachineName + L".rem";
						m_Server = (SySal::DAQSystem::TrackingServer ^)System::Runtime::Remoting::RemotingServices::Connect(SySal::DAQSystem::TrackingServer::typeid, str/*"tcp://" + m_ServerName + ":1808/TrackServer_" + m_MachineName + ".rem"*/);
						SrvGUID = m_Server->GUID;
						continue;
					}					
				}
				catch (Exception ^fx) 
				{
					m_Server = nullptr;
					continue;
				}

				try
				{					
					if (m_DataQueue->Count > 0)
					{						
						Active = true;
						//m_Frag = (SySal::DAQSystem::NetPackagedFragment ^)m_DataQueue[0];
						m_ActiveBuffers->Insert(0, (index = (System::Int32)(m_DataQueue[0])));
						m_DataQueue->Remove(index);
//						m_Frag = SySal::DAQSystem::NetPackagedFragment::FromDisk(index);
						ReleaseMutex(HDataQueueMutex);
					}
					else
					{
						ReleaseMutex(HDataQueueMutex);
						Sleep(1000); 
						continue;
					}
				}
				catch (Exception ^fx)
				{								
					if (index != 0 /*m_Frag != nullptr*/)
					{
						m_DataQueue->Insert(0, index);
						m_ActiveBuffers->Remove(index);
						Active = false;
						m_Frag = nullptr;	
						index = 0;
					}
					ReleaseMutex(HDataQueueMutex);
					continue;
				}

				try
				{
					m_Exception = nullptr;
					m_Frag = SySal::DAQSystem::NetPackagedFragment::FromDisk(index);
					System::Threading::Thread ^m_SendThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &SySal::DAQSystem::TrackingClientConnection::SendData));
					m_SendThread->Name = m_MachineName + "_SendData";
					m_SendThread->Start();					
					do
					{						
						m_SendThread->Join(10000);												
						if (m_Frag != nullptr)
						{							
							if (m_Exception != nullptr)
							{								
								System::Int64 newguid = m_Server->GUID;
								if (newguid != SrvGUID)
								{
									SrvGUID = newguid;
									throw gcnew System::Exception();
								}
							}							
						}
					}
					while (m_Frag != nullptr);
					System::IO::File::Delete(TrackingClient::CacheFile(index));					
				}				
				catch (System::IO::IOException ^x)
				{
					WaitForSingleObject(HDataQueueMutex, INFINITE);
					m_Logger->Error = x;
					m_Frag = nullptr;
					index = 0;
					Active = false;
					ReleaseMutex(HDataQueueMutex);
					m_Server = nullptr;					
				}
				catch (Exception ^fx)
				{
					WaitForSingleObject(HDataQueueMutex, INFINITE);					
					if (index != 0 /*m_Frag != nullptr*/)
					{						
						m_DataQueue->Insert(m_DataQueue->Count, index /* m_Frag */);	
						m_ActiveBuffers->Remove(index);
						m_Frag = nullptr;
						index = 0;
					}
					Active = false;
					ReleaseMutex(HDataQueueMutex);
					m_Server = nullptr;					
				}
				m_Thread = nullptr;
			}						
			DUMPEND("TrackingClientConnection::Execute");
		}

		bool TrackingClientConnection::IsActive::get()
		{
			DUMPBEGIN("TrackingClientConnection::IsActive::get");
			return Active;
			DUMPEND("TrackingClientConnection::IsActive::get");
		}

		TrackingClient::TrackingClient()
		{
			m_Disposed = false;
			HTerminate = INVALID_HANDLE_VALUE;
			HDataQueueMutex = INVALID_HANDLE_VALUE;

			m_DataQueue = gcnew System::Collections::ArrayList();
			m_ActiveBuffers = gcnew System::Collections::ArrayList();

			SySal::OperaDb::OperaDbConnection ^conn = SySal::OperaDb::OperaDbCredentials::CreateFromRecord()->Connect();
			conn->Open();

			int i;
			
			System::Net::IPHostEntry ^iph = System::Net::Dns::Resolve(System::Net::Dns::GetHostName());
			array<System::String ^> ^idstr = gcnew array<System::String ^>(iph->Aliases->Length + iph->AddressList->Length);
			idstr[0] = iph->HostName;
			for (i = 0; i < iph->Aliases->Length; i++)
				idstr[i] = iph->Aliases[i];
			for (i = 0; i < iph->AddressList->Length; i++)
				idstr[i + iph->Aliases->Length] = iph->AddressList[i]->ToString();
			System::String ^selstr = "LOWER(TB_MACHINES.ADDRESS)='" + iph->HostName->ToLower() + "'";
			for (i = 0; i < idstr->Length; i++)
				selstr += (" OR ADDRESS='" + idstr[i] + "'");
			System::Data::DataSet ^ds = gcnew System::Data::DataSet();
			(gcnew SySal::OperaDb::OperaDbDataAdapter("SELECT TB_SITES.ID, TB_SITES.NAME, TB_MACHINES.ID, TB_MACHINES.NAME, TB_MACHINES.ADDRESS FROM TB_SITES INNER JOIN TB_MACHINES ON (TB_MACHINES.ID_SITE = TB_SITES.ID AND TB_MACHINES.ISSCANNINGSERVER = 1 AND (" + selstr + "))", conn, nullptr))->Fill(ds);
			if (ds->Tables[0]->Rows->Count < 1) throw gcnew System::Exception("Can't find myself in OperaDb registered machines. This service is made unavailable.");
			System::Int64 IdSite = SySal::OperaDb::Convert::ToInt64(ds->Tables[0]->Rows[0][0]);
			m_MachineName = ds->Tables[0]->Rows[0][3]->ToString();
			ds = gcnew System::Data::DataSet();
			(gcnew SySal::OperaDb::OperaDbDataAdapter("SELECT ADDRESS FROM TB_MACHINES WHERE ID_SITE = " + IdSite.ToString() + " AND ISDATAPROCESSINGSERVER <> 0 AND ID = " + ds->Tables[0]->Rows[0][2]->ToString(), conn, nullptr))->Fill(ds);
			m_Servers = gcnew array<SySal::DAQSystem::TrackingClientConnection ^>(ds->Tables[0]->Rows->Count);
			HTerminate = CreateEvent(NULL, TRUE, FALSE, NULL);
			HDataQueueMutex = CreateMutex(NULL, TRUE, NULL);
			for (i = 0; i < m_Servers->Length; i++)
				m_Servers[i] = gcnew TrackingClientConnection(ds->Tables[0]->Rows[i][0]->ToString(), m_MachineName, nullptr, m_DataQueue, HDataQueueMutex, HTerminate, this);
			m_DefaultOutNameBase = (gcnew SySal::OperaDb::OperaDbCommand("SELECT VALUE FROM OPERA.LZ_SITEVARS WHERE NAME = 'ScratchDir'", conn))->ExecuteScalar()->ToString();
			if (!m_DefaultOutNameBase->EndsWith("\\")) m_DefaultOutNameBase = m_DefaultOutNameBase + "\\";
			m_DefaultOutNameBase = m_DefaultOutNameBase + m_MachineName + "_";
			m_CacheBase = System::Environment::ExpandEnvironmentVariables((gcnew SySal::OperaDb::OperaDbCommand("select fp from (select fp, row_number() over (order by order# desc) as onum from (select value as fp, 3 as order# from lz_machinevars where name = 'ScanGridCachePath' and id_machine = " + ds->Tables[0]->Rows[0][2]->ToString() + " union select value as fp, 2 as order# from lz_sitevars where name = 'ScanGridCachePath' union select '%TEMP%' as fp, 1 as order# from dual)) where onum = 1 ", conn, nullptr))->ExecuteScalar()->ToString());
			if (!m_CacheBase->EndsWith("/") && !m_CacheBase->EndsWith("\\")) m_CacheBase += "\\";
			m_CacheBase += "ScanGridCache_";
			conn->Close();
			ReleaseMutex(HDataQueueMutex);
		}

		System::String ^TrackingClient::CacheFile(System::Int32 cacheindex)
		{
			while (true)
				try
				{
					return gcnew System::String(m_CacheBase) + cacheindex.ToString() + gcnew System::String(".cache");
				}
				catch (System::OutOfMemoryException ^) {}
		}

		void TrackingClient::Free()
		{
			if (!m_Disposed)
			{
				int i;
				if (HTerminate != INVALID_HANDLE_VALUE && m_Servers != nullptr)
				{
					SetEvent(HTerminate);					
					for (i = 0; i < m_Servers->Length; i++)
						m_Servers[i]->Join();					
					CloseHandle(HTerminate);					
					CloseHandle(HDataQueueMutex);					
				}			
				for (i = 0; i < m_DataQueue->Count; i++)
					try
					{
						System::IO::File::Delete(CacheFile((System::Int32)m_DataQueue[i]));
					}
					catch (Exception ^) {};
				for (i = 0; i < m_ActiveBuffers->Count; i++)
					try
					{
						System::IO::File::Delete(CacheFile((System::Int32)m_ActiveBuffers[i]));
					}
					catch (Exception ^) {};
				m_Disposed = true;
				System::GC::SuppressFinalize(this);				
			}
		}

		TrackingClient::!TrackingClient()
		{
			Free();
		}

		void TrackingClient::GetDefaultOutName(char *pOutName)
		{
			int i;			
			for (i = 0; i < m_DefaultOutNameBase->Length; i++)
				pOutName[i] = m_DefaultOutNameBase[i];
			pOutName[i] = 0;
		}

		bool TrackingClient::IsActive::get()
		{
			DUMPBEGIN("TrackingClient::IsActive::get");
			WaitForSingleObject(HDataQueueMutex, INFINITE);			
			bool ret = true;
			if (m_DataQueue->Count == 0)
			{
				int i;
				for (i = 0; i < m_Servers->Length && !m_Servers[i]->IsActive; i++);
				if (i == m_Servers->Length) ret = false;
			}
			ReleaseMutex(HDataQueueMutex);
			return ret;
			DUMPEND("TrackingClient::IsActive::get");
		}

		void TrackingClient::AddFragment(NetPackagedFragment ^pkfg)
		{
			DUMPBEGIN("TrackingClient::AddFragment");
			while(true)
			{				
				WaitForSingleObject(HDataQueueMutex, INFINITE);	
				if (m_DataQueue->Count < /*2*/ 1 + this->m_Servers->Length)
				{
					pkfg->ToDisk(m_DataQueue->Count);
					m_DataQueue->Add(m_DataQueue->Count/*pkfg*/);
					ReleaseMutex(HDataQueueMutex);
					break;
				}
				else
				{
					ReleaseMutex(HDataQueueMutex);
					if (WaitForSingleObject(HTerminate, 1000) != WAIT_TIMEOUT) break;
				}
			}
			DUMPEND("TrackingClient::AddFragment");
		}
	}
}