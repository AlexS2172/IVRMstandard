// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6C9BE35A_23D6_4B71_86EB_CBEB69D5A2F2__INCLUDED_)
#define AFX_STDAFX_H__6C9BE35A_23D6_4B71_86EB_CBEB69D5A2F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#pragma warning(disable : 4786)

#ifdef _AFXDLL
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxpriv.h>
#endif // _AFXDLL

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

#include <windows.h>

#include <stdio.h>
#include <comdef.h>
#include <process.h>
#include <time.h>

#include <string>
#include <set>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

typedef basic_string<TCHAR>	tstring;

#define EG_DB_BACKWARD_COMPATIBLE



#include <EgLib/EgLibDbg.h>
#include <EgLib/EgLibSync.h>
#include <EgLib/EgLibThread.h>
#include <EgLib/EgLibMisc.h>
#include <EgLib/EgLibDb.h>
#include <EgLib/EgLibReg.h>
#include <EgLib/EgLibStrategy.h>
using namespace EgLib;



#include <appreg.h>
#include <winsock2.h>
#include <Mswsock.h>
#include <mstcpip.h>
#include <assert.h>
#include <egdebugutil.h>
// QuickFix Library Header Files
//
#pragma warning(push)
#pragma warning(disable : 4244 4267)
#include <Application.h>
#include <MessageCracker.h>
#include <FileStore.h>
#include <FileLog.h>
#include <SocketInitiator.h>
#include <SocketAcceptor.h>
#include <SessionSettings.h>
#include <Dictionary.h>
#include <SessionID.h>
#include <Exceptions.h>
#include <Session.h>
#include <Utility.h>
#include <Mutex.h>
#include <Messages.h>
#pragma warning(pop)

#include <Boost/shared_ptr.hpp>

#pragma warning(disable:4192)

#import "../../../tlb/msgstruct.tlb" no_namespace named_guids
#import "../../../tlb/mmw.tlb" no_namespace named_guids
#import "../../../tlb/etsmanager.tlb" no_namespace named_guids
#import "../../../tlb/Oledb32.tlb" rename_namespace("Oledb32") named_guids

#import "../../../tlb/ETSXMLParams.tlb" no_namespace named_guids
#include "XMLParamsHelper.h"

#pragma comment(lib, "quickfix.lib")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6C9BE35A_23D6_4B71_86EB_CBEB69D5A2F2__INCLUDED_)
