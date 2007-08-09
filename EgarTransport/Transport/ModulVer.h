////////////////////////////////////////////////////////////////
// 1998 Microsoft Systems Journal
//
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//

// 1999 Microsoft Systems Journal
// Extended by John Robbins
//  - Removed the MFC dependencies.
//  - Added a small bit of functionality.

#ifndef __MODULEVER_H
#define __MODULEVER_H

// tell linker to link with version.lib for VerQueryValue, etc.
#pragma comment(linker, "/defaultlib:version.lib")


//////////////////
// CModuleVersion version info about a module.
// To use:
//
// CModuleVersion ver
// if (ver.GetFileVersionInfo("_T("mymodule))) {
//    // info is in ver, you can call GetValue to get variable info like
//    CString s = ver.GetValue(_T("CompanyName"));
// }
//
// You can also call the static fn DllGetVersion to get DLLVERSIONINFO.
//
class CModuleVersion : public VS_FIXEDFILEINFO
{
protected:
    BYTE* m_pVersionInfo;   // all version info

    struct TRANSLATION
    {
        WORD langID;         // language ID
        WORD charset;        // character set (code page)
    } m_translation;

public:
    CModuleVersion();
    virtual ~CModuleVersion();

    BOOL     GetModuleVersionInfo(HINSTANCE hInstance);
    BOOL     GetModuleVersionInfo(LPCTSTR modulename);
    BOOL     GetFileVersionInfo(LPCTSTR filename);

	BOOL	 GetValue(LPCTSTR lpKeyName, tstring& strVal);
    static BOOL DllGetVersion(LPCTSTR modulename, DLLVERSIONINFO& dvi);
};

#endif
