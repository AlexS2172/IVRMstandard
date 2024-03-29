#include "stdafx.h"
#include "resource_GUI.h"

#pragma hdrstop

#include "publisher.h"
#include "Trace.h"
#include "Lock.h"
#include "Win32Error.h"
#include "io.h"

//////////////////////////////////////////////////////////////////////////////////
CPublisher* CTracer::m_pPublisher = 0;

//////////////////////////////////////////////////////////////////////////////////
BOOL CTracer::m_bEnableConsoleLog = TRUE;
BOOL CTracer::m_bEnableFileLog = TRUE;
BOOL CTracer::m_bDailyLog = FALSE;

//////////////////////////////////////////////////////////////////////////////////
TCHAR CTracer::m_pFileName[_MAX_FNAME] = {0};
ULONG CTracer::m_nFileDate = 0;

//////////////////////////////////////////////////////////////////////////////////
void __stdcall CTracer::CreateFileName()
{	
	memset(m_pFileName, 0, sizeof(m_pFileName));
	
	m_nFileDate = (DATE)vt_date::GetCurrentDate();
	
	vt_date vtFileDate((DATE)m_nFileDate);	

    _stprintf(m_pFileName, _T("Logs/STrace_%02d_%02d_%4d.log"), 
		vtFileDate.get_day(), vtFileDate.get_month(), vtFileDate.get_year());
}

//////////////////////////////////////////////////////////////////////////////////
void __stdcall CTracer::Trace(const TCHAR * lpszMessage, ...)
{
	if (!lpszMessage)
		return;

	va_list arglist;
    va_start(arglist, lpszMessage);

    SYSTEMTIME st = {0};
	::GetLocalTime(&st);

	TCHAR szBuf[4096] = { 0 };

	_vsntprintf(szBuf, sizeof(szBuf)/sizeof(TCHAR), lpszMessage, arglist);

	TCHAR szTime[100];
	_stprintf(szTime, _T("[0x%04x] %-2.2i/%-2.2i/%-4.4i %-2.2i:%-2.2i:%-2.2i "), 
		GetCurrentThreadId(), st.wDay , st.wMonth , st.wYear , st.wHour, st.wMinute, st.wSecond);

	if (m_bEnableConsoleLog)
	{
        CWnd* pWnd = AfxGetMainWnd();
        if (pWnd)
        {
            if (pWnd = pWnd->GetDlgItem(IDC_EDLOG))
            {
                CEdit* pEdit = static_cast<CEdit*>(pWnd);
                LPCTSTR EOL = _T("\r\n");

                CString sOut;
                sOut += szTime;
                sOut += szBuf;
                sOut += EOL;

                pEdit->SetSel(-2, -1);
                pEdit->ReplaceSel(sOut);
                pEdit->SetModify(FALSE);
            }
        }
	}

	if(m_bEnableFileLog)
	{
		if (IsDateChanged())
		{
			if (m_pPublisher)
			{
				WIN32_FIND_DATA f_data = {0};
				if (INVALID_HANDLE_VALUE != ::FindFirstFile(m_pFileName, &f_data))
				{
					fstream fLogPrev( T2A(m_pFileName), ios::app | ios::out);
					fLogPrev << T2A(szTime) << T2A(_T("************************************")) << endl;
					fLogPrev << T2A(szTime) << T2A(_T("Results on file end since the last session begin:")) << endl;
					fLogPrev << T2A(szTime) << T2A(_T("Received:      \t")) << m_pPublisher->m_dwReceived << endl;
					fLogPrev << T2A(szTime) << T2A(_T("DB stored:     \t")) << m_pPublisher->m_dwDBStored << endl;
					fLogPrev << T2A(szTime) << T2A(_T("DB deleted:    \t")) << m_pPublisher->m_dwDBDeleted << endl;
					fLogPrev << T2A(szTime) << T2A(_T("Published:     \t")) << m_pPublisher->m_dwPublished << endl;
					fLogPrev << T2A(szTime) << T2A(_T("Not published: \t")) << m_pPublisher->m_dwReceived - m_pPublisher->m_dwPublished << endl;					
				}
			}
			
			CreateFileName();
		}
		
		fstream fLog( T2A(m_pFileName), ios::app | ios::out);
		fLog << T2A(szTime) << T2A(szBuf) << endl;
		fLog.close();
	}
}

//////////////////////////////////////////////////////////////////////////////////
void __stdcall CTracer::TraceInit()
{
	CEgRegKey key;

	LONG lResult = key.Open(HKEY_CURRENT_USER, TRACE_REGISTRY_KEY, KEY_READ);
	if (lResult != ERROR_SUCCESS )
		lResult = key.Open (HKEY_LOCAL_MACHINE, TRACE_REGISTRY_KEY, KEY_READ);

	if (lResult == ERROR_SUCCESS)
	{	
		key.QueryValue (m_bDailyLog, TRACE_DAILY);
		key.QueryValue (m_bEnableConsoleLog, TRACE_TO_CONSOLE);
		key.QueryValue (m_bEnableFileLog, TRACE_TO_FILE);
		key.Close();
	}
}

//////////////////////////////////////////////////////////////////////////////////
BOOL __stdcall CTracer::IsDateChanged()
{
	return m_nFileDate < (ULONG)(DATE)vt_date::GetCurrentDate();
}

//////////////////////////////////////////////////////////////////////////////////
void CTracer::SetPublisher(CPublisher* pPublisher)
{
	m_pPublisher = pPublisher;
}

//////////////////////////////////////////////////////////////////////////////////
DWORD __stdcall CTracer::TraceError(const DWORD dwErr, const TCHAR* const szDescription)
{
	CWin32Error Err(dwErr);

	Trace(_T("%s : (%d) %s"), szDescription, dwErr, (const TCHAR*)Err);

	return dwErr;
}
