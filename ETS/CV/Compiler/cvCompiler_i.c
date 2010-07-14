

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Wed Jul 14 15:40:40 2010
 */
/* Compiler settings for .\cvCompiler.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IcvCompiler,0x533FBF62,0xA034,0x4A58,0x8F,0xB2,0x19,0xC6,0xE9,0xFA,0x0C,0xDE);


MIDL_DEFINE_GUID(IID, LIBID_cvCompilerLib,0x48FE0F84,0xE446,0x430B,0x8D,0x01,0xC1,0xAF,0xFC,0xA3,0xFC,0x6B);


MIDL_DEFINE_GUID(IID, DIID__IcvCompilerEvents,0xC144615B,0xB41A,0x4C2B,0xBA,0x81,0xA0,0xF4,0x43,0x90,0xFF,0xB7);


MIDL_DEFINE_GUID(CLSID, CLSID_cvCompiler,0xFAB06E55,0xA144,0x45B1,0xBB,0xDA,0x22,0x5E,0x56,0x8B,0x9F,0x78);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



