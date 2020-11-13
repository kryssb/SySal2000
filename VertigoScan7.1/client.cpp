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

		TrackingClientConnection::TrackingClientConnection(System::String ^servername, System::String ^machinename, SySal::DAQSystem::TrackingServer ^server, System::Collections::ArrayList ^dataqueue, HANDLE hDataQueueMutex, HANDLE hTerminate, ErrorLogger ^logger)
			: m_ServerName(servername), m_Server(server), m_DataQueue(dataqueue), HDataQueueMutex(hDataQueueMutex), HTerminate(hTerminate), m_MachineName(machinename), m_Logger(logger)
		{
			m_Frag = nullptr;
			m_Exception = nullptr;
			Active = false;
			m_Thread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &TrackingClientConnection::Execute));
			m_Thread->Name = this->m_MachineName + "_Execute";
			m_Thread->Start();
		}

		System::String ^TrackingClientConnection::ServerName::get()
		{
			return m_ServerName;
		}

		System::String ^TrackingClientConnection::CurrentTask::get()
		{
			if (m_Frag == nullptr) return gcnew System::String("");
			return m_Frag->FilePath;
		}

		System::String ^TrackingClientConnection::ExceptionText::get()
		{
			if (m_Exception == nullptr) return gcnew System::String("");
			return m_Exception->Message;
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
						m_Frag = (SySal::DAQSystem::NetPackagedFragment ^)m_DataQueue[0];
						m_DataQueue->RemoveAt(0);
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
					if (m_Frag != nullptr)
					{
						m_DataQueue->Insert(0, m_Frag);
						Active = false;
						m_Frag = nullptr;					
					}
					ReleaseMutex(HDataQueueMutex);
					continue;
				}

				try
				{
					m_Exception = nullptr;
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
				}				
				catch (System::IO::IOException ^x)
				{
					WaitForSingleObject(HDataQueueMutex, INFINITE);
					m_Logger->Error = x;
					m_Frag = nullptr;
					Active = false;
					ReleaseMutex(HDataQueueMutex);
					m_Server = nullptr;					
				}
				catch (Exception ^fx)
				{
/*					try
					{
						if (m_Frag != nullptr)
							System::IO::File::Delete(m_Frag->FilePath);
					}
					catch (Exception ^) {}
*/					
					WaitForSingleObject(HDataQueueMutex, INFINITE);					
					if (m_Frag != nullptr)
					{
						m_DataQueue->Insert(m_DataQueue->Count, m_Frag);						
						m_Frag = nullptr;
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

		void TrackingClientConnection::Test(System::String ^testfile)
		{
			DUMPBEGIN("TrackingClientConnection::Test");
			m_Server->Test(testfile);
			DUMPEND("TrackingClientConnection::Test");
		}

		TrackingClient::TrackingClient()
		{
			m_Servers = nullptr;
			m_DefaultOutNameBase = nullptr;
			m_MachineName = nullptr;
			m_Disposed = false;
			HTerminate = CreateEvent(NULL, TRUE, FALSE, NULL);
			HDataQueueMutex = CreateMutex(NULL, TRUE, NULL);

			m_DataQueue = gcnew System::Collections::ArrayList();

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
			if (ds->Tables[0]->Rows->Count < 1) throw gcnew System::Exception("Can't find myself in OperaDb registered machines. ScanGrid service unavailable.");
			System::Int64 IdSite = SySal::OperaDb::Convert::ToInt64(ds->Tables[0]->Rows[0][0]);
			m_MachineName = ds->Tables[0]->Rows[0][3]->ToString();
			ds = gcnew System::Data::DataSet();
			(gcnew SySal::OperaDb::OperaDbDataAdapter("SELECT ADDRESS FROM TB_MACHINES WHERE ID_SITE = " + IdSite.ToString() + " AND ISDATAPROCESSINGSERVER <> 0", conn, nullptr))->Fill(ds);
			m_Servers = gcnew array<SySal::DAQSystem::TrackingClientConnection ^>(ds->Tables[0]->Rows->Count);
			for (i = 0; i < m_Servers->Length; i++)
				m_Servers[i] = gcnew TrackingClientConnection(ds->Tables[0]->Rows[i][0]->ToString(), m_MachineName, nullptr, m_DataQueue, HDataQueueMutex, HTerminate, this);
			m_DefaultOutNameBase = (gcnew SySal::OperaDb::OperaDbCommand("SELECT VALUE FROM OPERA.LZ_SITEVARS WHERE NAME = 'ScratchDir'", conn))->ExecuteScalar()->ToString();
			if (!m_DefaultOutNameBase->EndsWith("\\")) m_DefaultOutNameBase = m_DefaultOutNameBase + "\\";
			m_DefaultOutNameBase = m_DefaultOutNameBase + m_MachineName + "_";
			conn->Close();
			ReleaseMutex(HDataQueueMutex);
		}

		void TrackingClient::Free()
		{
			if (!m_Disposed)
			{
				if (HTerminate != INVALID_HANDLE_VALUE && m_Servers != nullptr)
				{
					SetEvent(HTerminate);
					int i;
					for (i = 0; i < m_Servers->Length; i++)
						m_Servers[i]->Join();					
					CloseHandle(HTerminate);					
					CloseHandle(HDataQueueMutex);					
				}			
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

		System::String ^TrackingClient::MachineName::get()
		{
			return m_MachineName;
		}

		int TrackingClient::ServerCount::get()
		{
			return m_Servers->Length;
		}

		SySal::DAQSystem::TrackingClientConnection ^TrackingClient::Server(int i)
		{
			return m_Servers[i];
		}

		array<System::String ^> ^TrackingClient::QueueItems::get()
		{
			array<System::String ^> ^qu = nullptr;
			WaitForSingleObject(HDataQueueMutex, INFINITE);			
			int len = m_DataQueue->Count;
			qu =  gcnew array<System::String ^, 1>(len);
			int i;
			for (i = 0; i < len; i++)			
				qu[i] = ((SySal::DAQSystem::NetPackagedFragment ^)m_DataQueue[i])->FilePath;			
			ReleaseMutex(HDataQueueMutex);
			return qu;
		}

		void TrackingClient::RemoveItem(System::String ^str)
		{
			WaitForSingleObject(HDataQueueMutex, INFINITE);			
			int len = m_DataQueue->Count;
			array<System::String ^, 1> ^qu = gcnew array<System::String ^, 1>(len);
			int i;
			for (i = 0; i < len; i++)		
				if (System::String::Compare(str, ((SySal::DAQSystem::NetPackagedFragment ^)m_DataQueue[i])->FilePath, true) == 0)
				{
					m_DataQueue->RemoveAt(i);
					break;
				}
			ReleaseMutex(HDataQueueMutex);
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
				if (m_DataQueue->Count < 2 /*+ this->m_Servers->Length + 1*/)
				{
					m_DataQueue->Add(pkfg);
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