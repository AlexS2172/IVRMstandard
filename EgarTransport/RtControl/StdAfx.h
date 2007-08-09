// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BB71444E_AC87_43E6_857E_2E9A501FD586__INCLUDED_)
#define AFX_STDAFX_H__BB71444E_AC87_43E6_857E_2E9A501FD586__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#define _ATL_FREE_THREADED


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CRtControlModule : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
	LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);
	DWORD dwThreadID;
};
extern CRtControlModule _Module;
#include <atlcom.h>

#include <winsock2.h>
#include <process.h>

#import "..\tlb\Transport.tlb" no_namespace named_guids raw_interfaces_only rename("SendMessage", "SendMessageX")
#import "..\tlb\EgTpPrx.tlb" no_namespace named_guids raw_interfaces_only

#include <map>
using namespace std;


#include <winsvc.h>


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BB71444E_AC87_43E6_857E_2E9A501FD586__INCLUDED_)
