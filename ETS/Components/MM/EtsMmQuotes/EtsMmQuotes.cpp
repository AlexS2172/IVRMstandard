// EtsMmQuotes.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "EtsMmQuotes.h"

class CEtsMmQuotesModule : public CAtlDllModuleT< CEtsMmQuotesModule >
{
public :
	DECLARE_LIBID(LIBID_EtsMmQuotesLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ETSMMQUOTES, "{97206935-B7C6-4321-A650-85736616CB95}")
};

CEtsMmQuotesModule _AtlModule;


// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}


// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}
