//**************************************************************************************************************//
// solution:	Pequote
// project:		Pequote
// filename:	Pequote.cpp
// created:		26-Dec-2002 19:23 by Suchkov Dmitry
//
// purpose:		implementation of main module
//
// contains:	
//
//**************************************************************************************************************//

//**************************************************************************************************************//
// includes
//**************************************************************************************************************//
#include "stdafx.h"
#include "Pequote.h"
#include "FrmMain.h"
#include "DlgAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ASP_SETTINGS_ROOT	    _T("SOFTWARE\\eGAR\\ETS\\ASP")

//**************************************************************************************************************//
// constants
//**************************************************************************************************************//
LPCTSTR c_szSingleInstanceId = _T("EGAR Pequote {E39D90DA-EDEA-4473-A87F-121C5C66AEF0}");

//**************************************************************************************************************//
// variables
//**************************************************************************************************************//
CPequoteApp theApp;

//--------------------------------------------------------------------------------------------------------------//
BEGIN_MESSAGE_MAP(CPequoteApp, CWinApp)
	//{{AFX_MSG_MAP(CPequoteApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

DWORD CheckLogsFolder()
{
	_TCHAR szBuf[_MAX_PATH];
	DWORD dwErr = GetModuleFileName(NULL, szBuf, _MAX_PATH);
	if(dwErr == 0)
		return GetLastError();

	_TCHAR szDrive[_MAX_DRIVE];
	_TCHAR szDir[_MAX_DIR];
	_TCHAR szFname[_MAX_FNAME];
	_TCHAR szExt[_MAX_EXT];
	_tsplitpath_s( szBuf, szDrive,_MAX_DRIVE, szDir,_MAX_DIR, szFname,_MAX_FNAME, szExt, _MAX_EXT );

	_TCHAR szLogsPath[_MAX_PATH];
	_TCHAR szCurrentPath[_MAX_PATH];
	_stprintf_s(szLogsPath, sizeof(szLogsPath),       _T("%s%sLogs"), szDrive, szDir);
	_stprintf_s(szCurrentPath, sizeof(szCurrentPath), _T("%s%s"), szDrive, szDir);

	BOOL bRes = CreateDirectory(szLogsPath, NULL);
	if(!bRes)
	{
		dwErr = GetLastError();
		if(ERROR_ALREADY_EXISTS != dwErr)
			return dwErr;
	}

	bRes = SetCurrentDirectory(szCurrentPath);
	if(!bRes)
		return GetLastError();

	return 0;
}

//--------------------------------------------------------------------------------------------------------------//
CPequoteApp::CPequoteApp()
{
}

//--------------------------------------------------------------------------------------------------------------//
CPequoteApp::~CPequoteApp()
{
	if (NULL != m_hSingleInstanceMutex) ::CloseHandle(m_hSingleInstanceMutex);

	CoUninitialize();
}

//--------------------------------------------------------------------------------------------------------------//
BOOL CPequoteApp::InitInstance()
{		
#ifndef _DEBUG
	SetMiniDumpDefaultCrashHandler();
#endif // _DEBUG

	CString strCmdStart("-Start");
	CString strCmdStop ("-Stop");

	DWORD dwRes = CheckLogsFolder();
	if(dwRes)
	{

		TraceError(dwRes, _T("Fail to check Logs folder"));
		return -1;
	}		

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	CXMLParamsHelper XMLParams;
	XMLParams.LoadXMLParams();

	_bstr_t sbsUserGroup;
	XMLParams.GetUserGroup(sbsUserGroup.GetAddress());
	m_strSessionId = (LPCSTR)sbsUserGroup;

	/*TCHAR szUserNameBuffer[256];
	ZeroMemory(szUserNameBuffer, sizeof(szUserNameBuffer));
	DWORD dwUserNameBuffer = static_cast<DWORD>(sizeof(szUserNameBuffer))-1;

	GetUserName(szUserNameBuffer, &dwUserNameBuffer);
	CEgRegKey regUserKey;
	if(ERROR_SUCCESS == regUserKey.Open(HKEY_LOCAL_MACHINE, ASP_SETTINGS_ROOT, KEY_READ))
	{
		_bstr_t strSression;
		if(ERROR_SUCCESS == regUserKey.QueryValue(strSression, szUserNameBuffer))
			m_strSessionId = (LPCSTR)strSression;
	}*/


	std::string sKeyName = m_strSessionId;

	sKeyName+=c_szSingleInstanceId;
	m_stopEventId = _T("__")+sKeyName;


	HANDLE hMutex = ::OpenMutex(MUTEX_ALL_ACCESS, FALSE, sKeyName.c_str());
	if (NULL != hMutex)
	{
		HWND hWnd = ::FindWindowEx(NULL, NULL, AfxGetApp()->m_pszAppName, NULL);
		if (NULL != hWnd)
		{
			if(strCmdStop.CompareNoCase(m_lpCmdLine)==0)
			{
				SendMessage(hWnd, WM_DESTROY, 0,0);

			}
			else
				::SetForegroundWindow(hWnd);
		}
		CHandle hStop(::CreateEvent(NULL, TRUE, FALSE, theApp.GetStopEventName().c_str()));
		if(hStop!=NULL)
			SetEvent(hStop);
		
		return FALSE;
	}
	else
	{
		m_hSingleInstanceMutex = ::CreateMutex(NULL, TRUE, sKeyName.c_str());
	}

//#ifdef _AFXDLL
//	Enable3dControls();
//#else
//	Enable3dControlsStatic();
//#endif

	//CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Egar\\Ets"));

	CFrmMain* pFrame = new CFrmMain;
	pFrame->SetSessionID(m_strSessionId);
	pFrame->AutoStart(strCmdStart.CompareNoCase(m_lpCmdLine)==0);
	m_pMainWnd = pFrame;

	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	CTracer::SetWindowHandle(pFrame->GetSafeHwnd());
	CTracer::SetMessageId(WM_INSERT_TRACE_MESSAGE);
	
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

//--------------------------------------------------------------------------------------------------------------//
void CPequoteApp::OnAppAbout()
{
	CDlgAbout aboutDlg;
	aboutDlg.DoModal();
}
