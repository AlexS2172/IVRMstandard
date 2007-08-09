
////////////////////////////////////////////////////////////////
// 1998 Microsoft Systems Journal
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// 1999 Microsoft Systems Journal
// Updated by John Robbins to remove MFC dependencies.
//
// CModuleVersion provides an easy way to get version info
// for a module.(DLL or EXE).
//
#include "StdAfx.h"
#include "ModulVer.h"

CModuleVersion::CModuleVersion()
{
    m_pVersionInfo = NULL; // raw version info data
}

//////////////////
// Destroy: delete version info
//
CModuleVersion::~CModuleVersion()
{
    delete [] m_pVersionInfo;
}


//////////////////
// Get file version info for a given module
// Allocates storage for all info, fills "this" with
// VS_FIXEDFILEINFO, and sets codepage.
//


BOOL CModuleVersion::GetModuleVersionInfo(HINSTANCE hInstance)
{
    m_translation.charset = 1252;    // default = ANSI code page
    memset((VS_FIXEDFILEINFO*)this, 0, sizeof(VS_FIXEDFILEINFO));

    // get module handle
    TCHAR filename[_MAX_PATH];

 
   // get module file name
    DWORD len = GetModuleFileName(hInstance, filename,
                                  sizeof(filename)/sizeof(filename[0]));

    if ( len <= 0 )
        return (FALSE);
	
	return GetFileVersionInfo (filename);
}

BOOL CModuleVersion::GetModuleVersionInfo(LPCTSTR modulename)
{
    HMODULE hModule = ::LoadLibrary(modulename);
    if ( hModule==NULL && modulename!=NULL )
        return (FALSE);

    return (GetModuleVersionInfo(hModule));
}

BOOL CModuleVersion::GetFileVersionInfo(LPCTSTR filename)
{
    // read file version info
    DWORD dwDummyHandle;
    // will always be set to zero
    DWORD len = GetFileVersionInfoSize( (LPTSTR)filename, &dwDummyHandle);
    if ( len <= 0 )
        return (FALSE);
    m_pVersionInfo = new BYTE[len]; // allocate version info
    if ( !::GetFileVersionInfo( (LPTSTR) filename, 0, len, m_pVersionInfo) )
        return (FALSE);

    LPVOID lpvi;
    UINT iLen;

    if ( !VerQueryValue(m_pVersionInfo, _T("\\"), &lpvi, &iLen) )
        return (FALSE);

    // copy fixed info to myself, which am derived from VS_FIXEDFILEINFO
    *(VS_FIXEDFILEINFO*)this = *(VS_FIXEDFILEINFO*)lpvi;

    // Get translation info
    if ( VerQueryValue(m_pVersionInfo, _T("\\VarFileInfo\\Translation"),
                       &lpvi, &iLen) && iLen >= 4 )
    {
        m_translation = *(TRANSLATION*)lpvi;
        //TRACE("code page = %d\n", m_translation.charset);
    }
    return (dwSignature == VS_FFI_SIGNATURE);	
}



//////////////////
// Get string file info.
// Key name is something like "CompanyName".
// returns the value in szValue.
//
BOOL CModuleVersion::GetValue(LPCTSTR lpKeyName, CString & strVal)
{
    BOOL bRet = FALSE ;
    TCHAR szTemp [ MAX_PATH ] ;
    if ( m_pVersionInfo )
    {
        // To get a string value must pass query in the form
        //
        //    "\StringFileInfo\<langID><codepage>\keyname"
        //
        // where <langID><codepage> is the languageID concatenated with the
        // code page, in hex. Wow.
        //

        wsprintf ( szTemp ,
                  _T("\\StringFileInfo\\%04x%04x\\%s"),
                  m_translation.langID,
                  m_translation.charset,
                  lpKeyName);

        LPCTSTR pVal;
        UINT iLenVal;
        if ( VerQueryValue(m_pVersionInfo, szTemp,
                           (LPVOID*)&pVal, &iLenVal) )
        {
            LPTSTR szValue = strVal.GetBuffer (iLenVal);
			_tcsncpy ( szValue, pVal, iLenVal);
			
			strVal.ReleaseBuffer();


            bRet = TRUE ;
        }
    }
    return ( bRet );
}

// typedef for DllGetVersion proc
typedef HRESULT (CALLBACK* DLLGETVERSIONPROC)(DLLVERSIONINFO *);

/////////////////
// Get DLL Version by calling DLL's DllGetVersion proc
//
BOOL CModuleVersion::DllGetVersion(LPCTSTR modulename,
                                   DLLVERSIONINFO& dvi)
{
    HINSTANCE hinst = LoadLibrary(modulename);
    if ( !hinst )
        return (FALSE);

    // Must use GetProcAddress because the DLL might not implement
    // DllGetVersion. Depending upon the DLL, the lack of implementation
    // of the function may be a version marker in itself.
    //
    DLLGETVERSIONPROC pDllGetVersion =
    (DLLGETVERSIONPROC)GetProcAddress(hinst, _T("DllGetVersion"));
    if ( !pDllGetVersion )
        return (FALSE);

    memset(&dvi, 0, sizeof(dvi));        // clear
    dvi.cbSize = sizeof(dvi);            // set size for Windows

    return (SUCCEEDED((*pDllGetVersion)(&dvi)));
}
