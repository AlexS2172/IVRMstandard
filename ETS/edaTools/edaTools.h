
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the EDATOOLS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// EDATOOLS_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef EDATOOLS_EXPORTS
#define EDATOOLS_API WINAPI
//#define EDATOOLS_API __declspec(dllexport)
#else
#define EDATOOLS_API WINAPI
//#define EDATOOLS_API __declspec(dllimport)
#endif

extern "C"
{

unsigned long EDATOOLS_API CalcCRC32(const char* lpszData, int nDataLen);

}	// extern "C"

