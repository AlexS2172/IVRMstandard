#pragma once
#include "stdafx.h"
#include "IVRMFilter.h"
#include <ORBInit.h>

class CStopEvent
{
public:
	static bool CreateEvent();
	static void CloseEvent();
	static BOOL SetEvent(){ return ::SetEvent(hEvent);}
	static bool HasSignaledState() {return (::WaitForSingleObject(hEvent, 0) == WAIT_OBJECT_0);}
	static HANDLE GetHandle() { return hEvent; }
	static HANDLE hEvent;
};

//class CAppSettings: public VS::CAppSettingsBase
//{
//	static const TCHAR* m_ORB;
//	VS::CIniFileParser::SectionParamsList m_ORBParams;
//public:	
//	bool LoadSettings();
//	SectionParamsList GetORB()	{ return m_ORBParams;}
//};
//
//
//class CFilterWorker: public VS::CCORBAServerApplication
//{
//private:
//	IEtsMainPtr m_dsPtr;
//	CORBA::ORB_var m_orbvar;
//
//public:
//	PortableServer::POA_var		m_theInsPoa;
//
//	std::string					m_remoteObjectName;
//	std::string					m_uName;
//	std::string					m_uPass;
//
//	CFilterWorker(CAppSettings::pointer appSettings):VS::CCORBAServerApplication(appSettings){}
//	CFilterWorker(CAppSettings::pointer appSettings, IEtsMainPtr dsPtr):VS::CCORBAServerApplication(appSettings)
//	{
//		m_dsPtr = dsPtr;
//	}
//
//	~CFilterWorker(){LOG4CPLUS_INFO(VS::Log, _T(__FUNCTION__));}
//	void PreORBInit(const std::string& objectName){}
//	void PostORBInit(const std::string& objectName);
//	void ShutdownORB()
//	{
//		LOG4CPLUS_INFO(VS::Log, _T(__FUNCTION__));
//		int calls = 0;
//		//ORBInit::ORBShutdown(&calls);
//		//m_orbvar->shutdown(true);
//		//m_orbvar->destroy();
//		LOG4CPLUS_INFO(VS::Log, _T(__FUNCTION__));
//	}
//};
//
//
//class CFilterManager
//{
//private:
//	HANDLE m_hPullThread;
//public:
//	IEtsMainPtr dSourcePtr;
//	CFilterManager()
//	{
//		m_hPullThread = NULL;
//	}
//	static UINT WINAPI _PullThread(LPVOID pData);
//	void StartFilter(IEtsMainPtr ptr);
//	void StopFilter();
//	~CFilterManager();
//};
//
//
//typedef boost::shared_ptr<CFilterManager> CFilterManagerPtr;