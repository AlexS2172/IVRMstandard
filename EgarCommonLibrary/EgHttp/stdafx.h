// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <wininet.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <tchar.h>
#include <malloc.h>

#pragma comment(lib, "wininet.lib")

#import "..\bin\WorkFlowIC.dll" rename_namespace ("IC")
