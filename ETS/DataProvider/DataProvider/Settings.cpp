#include "StdAfx.h"
#include "Settings.h"
//----------------------------------------------------------------//
CSettings::CSettings(void)
{
}
//----------------------------------------------------------------//
CSettings::~CSettings(void)
{
}
//----------------------------------------------------------------//
std::string 
CSettings::GetConfigFileName()
{
	TCHAR szBuf[1024] = {0};
	if(GetModuleFileName(NULL, szBuf, sizeof(szBuf)))
	{
		TCHAR szDrive[8] = {0};
		TCHAR szDir[512] = {0};
		TCHAR szName[128] = {0};
		_tsplitpath( szBuf, szDrive, szDir, szName, NULL);
		std::string strName = szName;
		std::string strDrive = szDrive;
		std::string strDir = szDir;
		return strDrive + strDir + strName + std::string(".ini");
	}
	return std::string("");	
}
//----------------------------------------------------------------//
std::string 
CSettings::GetParameter(std::string file, std::string section, std::string key)
{
	TCHAR strValue[2048] = {0};
	
	GetPrivateProfileString(section.c_str(), 
							key.c_str(),
							_T(""), 
							strValue,
							2048, 
							file.c_str()
							);

	LOG4CPLUS_INFO(ProviderLog, _T("Section=") << section << 
								_T("\tKey=") << key << 
								_T("\tValue=") << strValue);
		
	return strValue;
};
//----------------------------------------------------------------//
bool CSettings::LoadSettings()
{
	
	std::string fileName = GetConfigFileName();
	LOG4CPLUS_INFO(ProviderLog, _T("ConfigurationFile: ") << fileName.c_str());

	if (fileName.length() > 0){

		std::string sValue = GetParameter(fileName, "ORB", "ORBEndPoint");

		//ORB Configuration Params Initialization
		m_ORBSettings.push_back(std::make_pair<>(_T("-ORBendPoint"), GetParameter(fileName, "ORB", "ORBEndPoint")));
		m_ORBSettings.push_back(std::make_pair<>(_T("-ORBtraceLevel"), GetParameter(fileName, "ORB", "ORBLogLevel")));
		
		//Activ Configuration Params Initialization
		m_UserID = GetParameter(fileName, "ACTIV", "UserID");
		m_Password = GetParameter(fileName, "ACTIV", "Password");
		m_ServiceLocationINI = GetParameter(fileName, "ACTIV", "ServiceLocationINI");
		m_DBConnectionString = GetParameter(fileName, "DATABASE", "ConnectionString");

		m_ACTIVSettings.m_enableUiService = false;
		m_ACTIVSettings.m_createSystemLog = false;
		m_ACTIVSettings.m_systemLogMode = AgentApplication::Settings::SYSTEM_LOG_MODE_OFF;
		m_ACTIVSettings.m_serviceLocationIniFile = m_ServiceLocationINI;

		return true;
	}
	return false;
};
//----------------------------------------------------------------//
ORBParametersList& CSettings::GetORBSettings()
{
	return m_ORBSettings;
};
//----------------------------------------------------------------//
AgentApplication::Settings& CSettings::GetACTIVSettings()
{
	return m_ACTIVSettings;
}
//----------------------------------------------------------------//
//----------------------------------------------------------------//
//----------------------------------------------------------------//
//----------------------------------------------------------------//
//----------------------------------------------------------------//
//----------------------------------------------------------------//
