#pragma once
#include "SettingsManager.h"
#include "EgTracingClass.h"

namespace ActivFeedSettings
{
	
	class CCustomerInfo
	{
	public:							
		static void Initialize();
	private:
		static CLock m_csInitializeLock;

	public:							

		CCustomerInfo()
			:m_spSettingsManager(new CSettingsManager)
		{
			TCHAR szBufferName[MAX_PATH];
			DWORD dwSize = MAX_PATH;
			::GetUserName(szBufferName, &dwSize);

			m_strUserName = szBufferName;

			/*CEgRegKey regUserKey;
			if(ERROR_SUCCESS == regUserKey.Open(HKEY_LOCAL_MACHINE, ASP_SETTINGS_ROOT, KEY_READ))
			{
				_bstr_t strSression;
				if(ERROR_SUCCESS == regUserKey.QueryValue(strSression, szBufferName))
				{
					m_strSessionId = (LPCSTR)strSression;
					m_spSettingsManager->Initialize(m_strSessionId);
				}   
			}*/
			m_strSessionId = m_strUserName;
			m_spSettingsManager->Initialize(m_strSessionId);
			EgLib::CEgLibTraceManager::Trace(LogInfo, __FUNCTION__ ,_T("Using session ID: %s"), m_strSessionId.c_str() );
		}

		virtual ~CCustomerInfo(void)
		{

		}
	public:
		__declspec (property(get = GetSessionId)) const std::string&        SessionId;
		__declspec (property(get = GetUserName)) const std::string&			UserName;
		__declspec (property(get = GetSettingsManager))CSettingsManagerPtr  Settings;

		const std::string& GetSessionId() const {return m_strSessionId;}
		const std::string& GetUserName() const {return m_strUserName;}

		CSettingsManagerPtr GetSettingsManager(){ return m_spSettingsManager; }
	private:


		CSettingsManagerPtr	m_spSettingsManager;
		std::string			m_strSessionId;
		std::string			m_strUserName;

	};

	typedef boost::shared_ptr<CCustomerInfo> UserSettingsPtr;
	__declspec(selectany)
		UserSettingsPtr g_spUserSettings;

	__declspec(selectany)
	CLock CCustomerInfo::m_csInitializeLock;

	inline
	void CCustomerInfo::Initialize()
	{
		CAutoLock lock(m_csInitializeLock);
		if(!EgLib::CEgLibTraceManager::g_spTrace)
			EgLib::CEgLibTraceManager::g_spTrace = EgLib::CEgLibTraceManagerPtr(static_cast<EgLib::CEgLibTraceManager*>(new Trace::CEgHyprFeedTrace));

		if(!ActivFeedSettings::g_spUserSettings)
		{
			ActivFeedSettings::g_spUserSettings = ActivFeedSettings::UserSettingsPtr (new ActivFeedSettings::CCustomerInfo);
			if(ActivFeedSettings::g_spUserSettings != NULL)
			{
				CDictionaryValue valLogLevel = g_spUserSettings->Settings->GetSettings(_T("LogLevel"));
				if(valLogLevel.length())
				{
					long lLogLevel = atol(valLogLevel.c_str());
					if(lLogLevel && EgLib::CEgLibTraceManager::g_spTrace!=NULL)
					   EgLib::CEgLibTraceManager::g_spTrace->MinLogLevel = lLogLevel;
				}

			}
		}
	}

};
