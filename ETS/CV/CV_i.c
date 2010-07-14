

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Wed Jul 14 15:40:40 2010
 */
/* Compiler settings for .\CV.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_CVLib,0xDACC06D8,0x9039,0x498F,0xA5,0xBB,0x9E,0x74,0x62,0x20,0x5C,0x74);


MIDL_DEFINE_GUID(IID, IID_IcvDataProvider,0x225DA231,0xB37D,0x43c7,0x94,0x7A,0x2F,0x24,0x9E,0xDF,0x9C,0xF5);


MIDL_DEFINE_GUID(IID, IID_IcvRTContext,0x10FC8A48,0x7539,0x4C54,0x87,0xC2,0x8F,0x61,0x74,0xCE,0x01,0x65);


MIDL_DEFINE_GUID(CLSID, CLSID_cvRTContext,0x9AFC738C,0x04A4,0x497B,0x9C,0x19,0x28,0x97,0xF3,0x38,0x7C,0xDC);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



