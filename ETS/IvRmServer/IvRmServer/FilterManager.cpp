#pragma once
#include "stdafx.h"
#include "FilterManager.h"

HANDLE CStopEvent::hEvent;
//const TCHAR*	CAppSettings::m_ORB = _T("ORB");

bool 
CStopEvent::CreateEvent(){
	if (!hEvent){
		hEvent = ::CreateEvent(NULL,TRUE,FALSE,NULL);
	}
	return (hEvent != NULL);
};

void 
CStopEvent::CloseEvent(){
	if (hEvent){
		CloseHandle(hEvent);
		hEvent = NULL;
	};
};

//bool 
//CAppSettings::LoadSettings(){
//	bool result = true;	
//	
//	try	{
//		ReadRequiredParameter(MAIN_SECTION, OBJECT_NAME_KEY, m_paramByName[OBJECT_NAME_KEY]);
//		ReadSectionParameters(m_ORB, m_ORBParams);
//	}
//	catch(TCHAR* err){
//		std::cout<<"Exception occured while loading parameters. Description: " << err;
//		result = false;
//	};
//
//	SectionParamsList::iterator it = m_ORBParams.begin();
//	SectionParamsList::iterator it_end = m_ORBParams.end();		
//	for (; it != it_end; ++it){
//		std::string& params_key = it->first;
//		params_key = "-" + params_key;
//	};
//
//	return result;
//};
//
//void CFilterWorker::PostORBInit(const std::string& objectName)
//{
//	m_orbvar = CORBA::ORB::_duplicate(GetORB());
//
//	CORBA::Object_var poaRef				= m_orbvar->resolve_initial_references("omniINSPOA");
//	m_theInsPoa								= PortableServer::POA::_narrow(poaRef);
//	PortableServer::POAManager_var pman		= m_theInsPoa->the_POAManager();
//	pman->activate();
//
//	//CIVRMFilter* servant = new CIVRMFilter();
//	//servant->SetDataSource(m_dsPtr);
//
//	//PortableServer::ObjectId_var serviceIID = PortableServer::string_to_ObjectId(objectName.c_str());
//	//m_theInsPoa->activate_object_with_id(serviceIID, servant);
//}


//UINT WINAPI CFilterManager::_PullThread(LPVOID pData)
//{
//	LOG4CPLUS_INFO(VS::Log, _T("Filter Thread Started."));
//	
//	if (pData == NULL){
//		LOG4CPLUS_INFO(VS::Log, _T("Can't start filter: no data source provided"));
//		return 0;
//	};
//
//	CoInitializeEx(NULL, COINIT_MULTITHREADED);
//	VS::CAppSettingsBase::pointer ptr(new CAppSettings());
//	ptr->LoadLogSettings();
//	ptr->LoadSettings();
//
//	std::string object_name = ptr->GetValue(OBJECT_NAME_KEY);
//	
//	CFilterWorker worker(ptr, ((CFilterManager*)pData)->dSourcePtr);
//	CFilterWorker::ORBParametersList orbParamsList = ((CAppSettings*)&(*ptr))->GetORB();
//
//	printf("Filter Name: %s\n", object_name.c_str());
//
//	worker.Run(orbParamsList, object_name);
//	worker.ShutdownORB();
//	LOG4CPLUS_INFO(VS::Log, _T("Filter Thread Exiting"));
//	CoUninitialize();
//	return 0;
//}
//
//void 
//CFilterManager::StartFilter(IEtsMainPtr ptr){
//	try {
//		unsigned int thread_id = 0;
//		dSourcePtr = ptr;
//		CStopEvent::CreateEvent();
//		m_hPullThread  = (HANDLE)_beginthreadex(NULL, 0, _PullThread, this, 0, &thread_id);
//	}
//	catch (...){
//		std::cout<<"Unknown exception occured while starting filter.\n";
//	};
//};
//
//void 
//CFilterManager::StopFilter(){
//	CStopEvent::SetEvent();
//
//	if (m_hPullThread){
//
//		if(WaitForSingleObject(m_hPullThread, 1000) != WAIT_OBJECT_0){
//			::TerminateThread(m_hPullThread, -1);
//		};
//
//		CloseHandle(m_hPullThread);
//
//		m_hPullThread = NULL;
//	}
//};
//
//CFilterManager::~CFilterManager(){
//	try	{
//		StopFilter();
//	}
//	catch (...){
//		std::cout<<"Unknown exception occured while destroying Filter Manager.\n";
//	}
//	CStopEvent::CloseEvent();
//};