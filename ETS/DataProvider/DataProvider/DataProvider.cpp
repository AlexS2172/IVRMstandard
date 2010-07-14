// DataProvider.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyCorbaApplication.h"
#include "ActivFeedConnection.h"

#include <log4cplus/fileappender.h>
#include <log4cplus/tstring.h>
#include <log4cplus/layout.h>
#include "Messenger.h"


log4cplus::Logger ProviderLog = log4cplus::Logger::getInstance("log4cplusDataProvider");
log4cplus::Logger CorbaLog = log4cplus::Logger::getInstance("log4cplusDataProviderCorba");

void InitializeLogger();
void InitializeCorbaLogger();

CDatabaseImpl::pointer CDataBase::m_dbImpl = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		HRESULT hrStatus = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		if(FAILED(hrStatus))
			utils::ThrowErrorNoSetErrorInfo(hrStatus, L"Failed to DispEventAdvise.");

		InitializeLogger();
		InitializeCorbaLogger();

		CSettings::pointer userSettings = CSettings::pointer(new CSettings());
		if (!userSettings->LoadSettings()){
			std::cout<<"Fail to read settings.";
			return 0;
		}

		CProviderSingleton::Initialize(userSettings);

		CMyCorbaApplication	corbaApp(userSettings);	

		CMessengerPtr spMessenger(new CMessenger());

		CDataBase::getInstance()->setConnectionString(userSettings->m_DBConnectionString);
		
		spMessenger->SubscribeTradeUpdate();
		
		corbaApp.Run(userSettings->GetORBSettings(), std::string("IVDataService"));
		
		spMessenger->UnSubscribeTradeUpdate();

		CoUninitialize();
	}
	catch (_com_error& err)
	{
		LOG4CPLUS_ERROR(ProviderLog, _T("ComError: Main() ")<<(char*)(err.Description()));
		ATLASSERT(FALSE);
	}
	catch (...)
	{
		LOG4CPLUS_ERROR(ProviderLog, _T("Unknown error occured while Main()"));
		ATLASSERT(FALSE);
	};
	return 0;
}

void InitializeLogger(){
	using namespace log4cplus;
	ProviderLog.removeAllAppenders();
	std::string logPattern = "%D{%c} [%t] [%p]: %m%n";
	SharedAppenderPtr RMainFileApp(new RollingFileAppender("DataProvider.log", 100*1024*1024, 3));
	RMainFileApp->setName(_T("RMainQueueFileApp"));
	RMainFileApp->setLayout( std::auto_ptr<Layout>(new PatternLayout(logPattern)) );
	ProviderLog.addAppender(RMainFileApp);
};

void InitializeCorbaLogger(){
	using namespace log4cplus;
	CorbaLog.removeAllAppenders();
	std::string logPattern = "%D{%c} [%t] [%p]: %m%n";
	SharedAppenderPtr RMainFileApp(new RollingFileAppender("DataProviderCorba.log"));
	RMainFileApp->setName(_T("RMainQueueFileApp1"));
	RMainFileApp->setLayout( std::auto_ptr<Layout>(new PatternLayout(logPattern)) );
	CorbaLog.addAppender(RMainFileApp);
};

