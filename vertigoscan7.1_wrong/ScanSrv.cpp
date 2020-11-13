#include "StdAfx.h"
#include "ScanSrv.h"

using namespace SySal::DAQSystem;

VSScanServer::VSScanServer()
{
	m_Answer = false;
	m_RequestObject = nullptr;
	EvAnswer = gcnew System::Threading::AutoResetEvent(false);
	MtxWork = gcnew System::Threading::Mutex(false);
}

VSScanServer::!VSScanServer()
{
	MtxWork->WaitOne();
}

void VSScanServer::Answer(bool ans)
{
	m_Answer = ans;
	EvAnswer->Set();
}

void VSScanServer::AnswerId(SySal::BasicTypes::Identifier ^ans)
{
	m_AnswerId = *ans;
	EvAnswer->Set();
}

void VSScanServer::AnswerManualCheckBaseTrack(SySal::DAQSystem::Scanning::ManualCheck::OutputBaseTrack ans)
{
	m_AnswerManualCheckBaseTrack = ans;
	EvAnswer->Set();
}

void VSScanServer::AnswerFogThickness(SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet ans)
{
	m_AnswerFogThickness = ans;
	EvAnswer->Set();
}

System::Object ^VSScanServer::GetRequest()
{
	return m_RequestObject;
}

bool VSScanServer::Scan(SySal::DAQSystem::Scanning::ZoneDesc ^zone)
{
	MtxWork->WaitOne();
	m_RequestObject = zone;
	EvAnswer->WaitOne();
	bool ans = m_Answer;
	m_RequestObject = nullptr;
	MtxWork->ReleaseMutex();
	return ans;
}

bool VSScanServer::ScanAndMoveToNext(SySal::DAQSystem::Scanning::ZoneDesc ^zone, SySal::BasicTypes::Rectangle ^rect)
{
	MtxWork->WaitOne();
	ScanMoveNext ^o = gcnew ScanMoveNext();
	o->zone = zone;
	o->rect = rect;
	m_RequestObject = o;
	EvAnswer->WaitOne();
	bool ans = m_Answer;
	m_RequestObject = nullptr;
	MtxWork->ReleaseMutex();
	return ans;
}

bool VSScanServer::LoadPlate(SySal::DAQSystem::Scanning::MountPlateDesc ^plate)
{
	MtxWork->WaitOne();
	m_RequestObject = plate;
	EvAnswer->WaitOne();
	bool ans = m_Answer;
	m_RequestObject = nullptr;
	MtxWork->ReleaseMutex();
	return ans;
}

bool VSScanServer::UnloadPlate()
{
	MtxWork->WaitOne();	
	m_RequestObject = this;
	EvAnswer->WaitOne();
	bool ans = m_Answer;
	m_RequestObject = nullptr;
	MtxWork->ReleaseMutex();
	return ans;
}

SySal::DAQSystem::Scanning::ManualCheck::OutputBaseTrack VSScanServer::RequireManualCheck(SySal::DAQSystem::Scanning::ManualCheck::InputBaseTrack inputbasetrack)
{
	MtxWork->WaitOne();	
	m_RequestObject = inputbasetrack;
	EvAnswer->WaitOne();
	SySal::DAQSystem::Scanning::ManualCheck::OutputBaseTrack ans = m_AnswerManualCheckBaseTrack;
	m_RequestObject = nullptr;
	MtxWork->ReleaseMutex();
	return ans;
}

SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet VSScanServer::GetFogAndThickness()
{
	MtxWork->WaitOne();	
	SySal::DAQSystem::Scanning::PlateQuality::FogThicknessSet ans;
	m_RequestObject = ans;
	EvAnswer->WaitOne();
	ans = m_AnswerFogThickness;
	m_RequestObject = nullptr;
	MtxWork->ReleaseMutex();
	return ans;
}

bool VSScanServer::SetScanLayout(System::String ^xmllayout)
{
	return false;
}

bool VSScanServer::SetSingleParameter(System::String ^objectname, System::String ^parametername, System::String ^parametervalue)
{
	MtxWork->WaitOne();	
	SySal::DAQSystem::SetSingleParameter ^ssp = gcnew SySal::DAQSystem::SetSingleParameter();
	ssp->objectname = objectname;
	ssp->parametername = parametername;
	ssp->parametervalue = parametervalue;
	m_RequestObject = ssp;
	EvAnswer->WaitOne();
	bool ans = m_Answer;
	m_RequestObject = nullptr;
	MtxWork->ReleaseMutex();
	return ans;
}

bool VSScanServer::SetObjectConfiguration(System::String ^objectname, System::String ^xmlconfig)
{
	return false;
}

bool VSScanServer::IsBusy::get()
{
	return m_IsBusy;
}

bool VSScanServer::IsLoaded::get()
{
	return m_IsLoaded;
}

SySal::BasicTypes::Identifier VSScanServer::CurrentZone::get()
{
	return m_CurrentZone;
}

SySal::BasicTypes::Identifier VSScanServer::CurrentPlate::get()
{
	return m_CurrentPlate;
}

bool VSScanServer::TestComm(int h)
{
	return !h;
}

bool VSScanServer::HasRequest::get()
{
	return m_RequestObject != nullptr;
}