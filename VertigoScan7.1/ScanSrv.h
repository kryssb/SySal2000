#ifndef _VS6_SCANSRV_H_
#define _VS6_SCANSRV_H_

#using <mscorlib.dll>
#using "DAQSystem.dll"
#using "SySalCore.dll"
#using "Imaging.dll"
#using "Tracking.dll"
#using "Scanning.dll"
#using "ScanServerScheme.dll"

namespace SySal
{
	namespace DAQSystem
	{
		public ref class ScanMoveNext
		{
		public:
			SySal::DAQSystem::Scanning::ZoneDesc ^zone;
			SySal::BasicTypes::Rectangle ^rect;
		};

		public ref class SetSingleParameter
		{
		public:
			System::String ^objectname;
			System::String ^parametername;
			System::String ^parametervalue;
		};

		public ref class VSScanServer : public SySal::DAQSystem::ScanServer
		{
		private:

			bool m_Answer;
			SySal::DAQSystem::Scanning::ManualCheck::OutputBaseTrack m_AnswerManualCheckBaseTrack;
			SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet m_AnswerFogThickness;
			SySal::BasicTypes::Identifier m_AnswerId;
			System::Object ^m_RequestObject;

			System::Threading::AutoResetEvent ^EvAnswer;
			System::Threading::Mutex ^MtxWork;			

		public:
			VSScanServer();
			!VSScanServer();			

			void Answer(bool ans);
			void AnswerId(SySal::BasicTypes::Identifier ^ans);
			void AnswerManualCheckBaseTrack(SySal::DAQSystem::Scanning::ManualCheck::OutputBaseTrack ans);
			void AnswerFogThickness(SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet ans);
			System::Object ^GetRequest();
			property bool HasRequest { bool get(); }

			bool Scan(SySal::DAQSystem::Scanning::ZoneDesc ^zone);
			bool ScanAndMoveToNext(SySal::DAQSystem::Scanning::ZoneDesc ^zone, SySal::BasicTypes::Rectangle ^rect);
			bool LoadPlate(SySal::DAQSystem::Scanning::MountPlateDesc ^plate);
			bool UnloadPlate();
			bool SetSingleParameter(System::String ^objectname, System::String ^parametername, System::String ^parametervalue);
			bool SetObjectConfiguration(System::String ^objectname, System::String ^xmlconfig);
			bool SetScanLayout(System::String ^xmllayout);

			SySal::DAQSystem::Scanning::ManualCheck::OutputBaseTrack RequireManualCheck(SySal::DAQSystem::Scanning::ManualCheck::InputBaseTrack inputbasetrack);
			SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet GetFogAndThickness();

			property bool IsBusy { bool get(); }
			property bool IsLoaded { bool get(); }
			property SySal::BasicTypes::Identifier CurrentZone { SySal::BasicTypes::Identifier get(); }
			property SySal::BasicTypes::Identifier CurrentPlate { SySal::BasicTypes::Identifier get(); }

			bool TestComm(int h);

			bool m_IsBusy;
			bool m_IsLoaded;
			SySal::BasicTypes::Identifier m_CurrentZone;
			SySal::BasicTypes::Identifier m_CurrentPlate;
		};
	}
}

#endif