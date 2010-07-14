

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */
#pragma warning( disable: 4211 )  /* redefine extent to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "cvCompiler.h"

#define TYPE_FORMAT_STRING_SIZE   1105                              
#define PROC_FORMAT_STRING_SIZE   169                               
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IcvCompiler_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IcvCompiler_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get_ConnectionString */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 18 */	NdrFcShort( 0x1 ),	/* 1 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 24 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ConnectionString */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x8 ),	/* 8 */
/* 50 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 52 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x1 ),	/* 1 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 60 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Return value */

/* 66 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Compile */

/* 72 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 74 */	NdrFcLong( 0x0 ),	/* 0 */
/* 78 */	NdrFcShort( 0x9 ),	/* 9 */
/* 80 */	NdrFcShort( 0x34 ),	/* x86 Stack size/offset = 52 */
/* 82 */	NdrFcShort( 0x10 ),	/* 16 */
/* 84 */	NdrFcShort( 0x24 ),	/* 36 */
/* 86 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0xc,		/* 12 */
/* 88 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 90 */	NdrFcShort( 0x24 ),	/* 36 */
/* 92 */	NdrFcShort( 0x17 ),	/* 23 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter iContext */

/* 96 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 98 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 100 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iLevel */

/* 102 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 104 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter strVarName */

/* 108 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 110 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 112 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter strCaption */

/* 114 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 116 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 118 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter strFormat */

/* 120 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 122 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 124 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter strSource */

/* 126 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 128 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 130 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter strDescription */

/* 132 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 134 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 136 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter arrAggregation */

/* 138 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 140 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 142 */	NdrFcShort( 0x42c ),	/* Type Offset=1068 */

	/* Parameter arrErrors */

/* 144 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 146 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 148 */	NdrFcShort( 0x442 ),	/* Type Offset=1090 */

	/* Parameter arrCode */

/* 150 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 152 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 154 */	NdrFcShort( 0x442 ),	/* Type Offset=1090 */

	/* Parameter iVariableID */

/* 156 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 158 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
/* 160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 162 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 164 */	NdrFcShort( 0x30 ),	/* x86 Stack size/offset = 48 */
/* 166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1c ),	/* Offset= 28 (32) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xe ),	/* Offset= 14 (22) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 20 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 22 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 24 */	NdrFcShort( 0x8 ),	/* 8 */
/* 26 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (10) */
/* 28 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 30 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 32 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x4 ),	/* 4 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xffde ),	/* Offset= -34 (6) */
/* 42 */	
			0x12, 0x0,	/* FC_UP */
/* 44 */	NdrFcShort( 0xffea ),	/* Offset= -22 (22) */
/* 46 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x4 ),	/* 4 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (42) */
/* 56 */	
			0x11, 0x0,	/* FC_RP */
/* 58 */	NdrFcShort( 0x3f2 ),	/* Offset= 1010 (1068) */
/* 60 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 62 */	NdrFcShort( 0x2 ),	/* Offset= 2 (64) */
/* 64 */	
			0x12, 0x0,	/* FC_UP */
/* 66 */	NdrFcShort( 0x3d8 ),	/* Offset= 984 (1050) */
/* 68 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 70 */	NdrFcShort( 0x18 ),	/* 24 */
/* 72 */	NdrFcShort( 0xa ),	/* 10 */
/* 74 */	NdrFcLong( 0x8 ),	/* 8 */
/* 78 */	NdrFcShort( 0x5a ),	/* Offset= 90 (168) */
/* 80 */	NdrFcLong( 0xd ),	/* 13 */
/* 84 */	NdrFcShort( 0x90 ),	/* Offset= 144 (228) */
/* 86 */	NdrFcLong( 0x9 ),	/* 9 */
/* 90 */	NdrFcShort( 0xc2 ),	/* Offset= 194 (284) */
/* 92 */	NdrFcLong( 0xc ),	/* 12 */
/* 96 */	NdrFcShort( 0x2bc ),	/* Offset= 700 (796) */
/* 98 */	NdrFcLong( 0x24 ),	/* 36 */
/* 102 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (844) */
/* 104 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 108 */	NdrFcShort( 0x302 ),	/* Offset= 770 (878) */
/* 110 */	NdrFcLong( 0x10 ),	/* 16 */
/* 114 */	NdrFcShort( 0x31c ),	/* Offset= 796 (910) */
/* 116 */	NdrFcLong( 0x2 ),	/* 2 */
/* 120 */	NdrFcShort( 0x336 ),	/* Offset= 822 (942) */
/* 122 */	NdrFcLong( 0x3 ),	/* 3 */
/* 126 */	NdrFcShort( 0x350 ),	/* Offset= 848 (974) */
/* 128 */	NdrFcLong( 0x14 ),	/* 20 */
/* 132 */	NdrFcShort( 0x36a ),	/* Offset= 874 (1006) */
/* 134 */	NdrFcShort( 0xffff ),	/* Offset= -1 (133) */
/* 136 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 138 */	NdrFcShort( 0x4 ),	/* 4 */
/* 140 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 144 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 146 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 148 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 150 */	NdrFcShort( 0x4 ),	/* 4 */
/* 152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 154 */	NdrFcShort( 0x1 ),	/* 1 */
/* 156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 160 */	0x12, 0x0,	/* FC_UP */
/* 162 */	NdrFcShort( 0xff74 ),	/* Offset= -140 (22) */
/* 164 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 166 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 168 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 170 */	NdrFcShort( 0x8 ),	/* 8 */
/* 172 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 174 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 176 */	NdrFcShort( 0x4 ),	/* 4 */
/* 178 */	NdrFcShort( 0x4 ),	/* 4 */
/* 180 */	0x11, 0x0,	/* FC_RP */
/* 182 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (136) */
/* 184 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 186 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 188 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 190 */	NdrFcLong( 0x0 ),	/* 0 */
/* 194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 198 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 200 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 202 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 204 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 206 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 210 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 214 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 216 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 220 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 222 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 224 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (188) */
/* 226 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 228 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 230 */	NdrFcShort( 0x8 ),	/* 8 */
/* 232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x6 ),	/* Offset= 6 (240) */
/* 236 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 238 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 240 */	
			0x11, 0x0,	/* FC_RP */
/* 242 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (206) */
/* 244 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 246 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 254 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 256 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 258 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 260 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 262 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 264 */	NdrFcShort( 0x0 ),	/* 0 */
/* 266 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 270 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 272 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 276 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 278 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 280 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (244) */
/* 282 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 284 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 286 */	NdrFcShort( 0x8 ),	/* 8 */
/* 288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 290 */	NdrFcShort( 0x6 ),	/* Offset= 6 (296) */
/* 292 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 294 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 296 */	
			0x11, 0x0,	/* FC_RP */
/* 298 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (262) */
/* 300 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 302 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 304 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 306 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 308 */	NdrFcShort( 0x2 ),	/* Offset= 2 (310) */
/* 310 */	NdrFcShort( 0x10 ),	/* 16 */
/* 312 */	NdrFcShort( 0x2f ),	/* 47 */
/* 314 */	NdrFcLong( 0x14 ),	/* 20 */
/* 318 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 320 */	NdrFcLong( 0x3 ),	/* 3 */
/* 324 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 326 */	NdrFcLong( 0x11 ),	/* 17 */
/* 330 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 332 */	NdrFcLong( 0x2 ),	/* 2 */
/* 336 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 338 */	NdrFcLong( 0x4 ),	/* 4 */
/* 342 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 344 */	NdrFcLong( 0x5 ),	/* 5 */
/* 348 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 350 */	NdrFcLong( 0xb ),	/* 11 */
/* 354 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 356 */	NdrFcLong( 0xa ),	/* 10 */
/* 360 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 362 */	NdrFcLong( 0x6 ),	/* 6 */
/* 366 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (598) */
/* 368 */	NdrFcLong( 0x7 ),	/* 7 */
/* 372 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 374 */	NdrFcLong( 0x8 ),	/* 8 */
/* 378 */	NdrFcShort( 0xfeb0 ),	/* Offset= -336 (42) */
/* 380 */	NdrFcLong( 0xd ),	/* 13 */
/* 384 */	NdrFcShort( 0xff3c ),	/* Offset= -196 (188) */
/* 386 */	NdrFcLong( 0x9 ),	/* 9 */
/* 390 */	NdrFcShort( 0xff6e ),	/* Offset= -146 (244) */
/* 392 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 396 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (604) */
/* 398 */	NdrFcLong( 0x24 ),	/* 36 */
/* 402 */	NdrFcShort( 0xd2 ),	/* Offset= 210 (612) */
/* 404 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 408 */	NdrFcShort( 0xcc ),	/* Offset= 204 (612) */
/* 410 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 414 */	NdrFcShort( 0xfc ),	/* Offset= 252 (666) */
/* 416 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 420 */	NdrFcShort( 0xfa ),	/* Offset= 250 (670) */
/* 422 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 426 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (674) */
/* 428 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 432 */	NdrFcShort( 0xf6 ),	/* Offset= 246 (678) */
/* 434 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 438 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (682) */
/* 440 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 444 */	NdrFcShort( 0xf2 ),	/* Offset= 242 (686) */
/* 446 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 450 */	NdrFcShort( 0xdc ),	/* Offset= 220 (670) */
/* 452 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 456 */	NdrFcShort( 0xda ),	/* Offset= 218 (674) */
/* 458 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 462 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (690) */
/* 464 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 468 */	NdrFcShort( 0xda ),	/* Offset= 218 (686) */
/* 470 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 474 */	NdrFcShort( 0xdc ),	/* Offset= 220 (694) */
/* 476 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 480 */	NdrFcShort( 0xda ),	/* Offset= 218 (698) */
/* 482 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 486 */	NdrFcShort( 0xd8 ),	/* Offset= 216 (702) */
/* 488 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 492 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (706) */
/* 494 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 498 */	NdrFcShort( 0xdc ),	/* Offset= 220 (718) */
/* 500 */	NdrFcLong( 0x10 ),	/* 16 */
/* 504 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 506 */	NdrFcLong( 0x12 ),	/* 18 */
/* 510 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 512 */	NdrFcLong( 0x13 ),	/* 19 */
/* 516 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 518 */	NdrFcLong( 0x15 ),	/* 21 */
/* 522 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 524 */	NdrFcLong( 0x16 ),	/* 22 */
/* 528 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 530 */	NdrFcLong( 0x17 ),	/* 23 */
/* 534 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 536 */	NdrFcLong( 0xe ),	/* 14 */
/* 540 */	NdrFcShort( 0xba ),	/* Offset= 186 (726) */
/* 542 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 546 */	NdrFcShort( 0xbe ),	/* Offset= 190 (736) */
/* 548 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 552 */	NdrFcShort( 0xbc ),	/* Offset= 188 (740) */
/* 554 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 558 */	NdrFcShort( 0x70 ),	/* Offset= 112 (670) */
/* 560 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 564 */	NdrFcShort( 0x6e ),	/* Offset= 110 (674) */
/* 566 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 570 */	NdrFcShort( 0x6c ),	/* Offset= 108 (678) */
/* 572 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 576 */	NdrFcShort( 0x62 ),	/* Offset= 98 (674) */
/* 578 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 582 */	NdrFcShort( 0x5c ),	/* Offset= 92 (674) */
/* 584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 588 */	NdrFcShort( 0x0 ),	/* Offset= 0 (588) */
/* 590 */	NdrFcLong( 0x1 ),	/* 1 */
/* 594 */	NdrFcShort( 0x0 ),	/* Offset= 0 (594) */
/* 596 */	NdrFcShort( 0xffff ),	/* Offset= -1 (595) */
/* 598 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 600 */	NdrFcShort( 0x8 ),	/* 8 */
/* 602 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 604 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 606 */	NdrFcShort( 0x2 ),	/* Offset= 2 (608) */
/* 608 */	
			0x12, 0x0,	/* FC_UP */
/* 610 */	NdrFcShort( 0x1b8 ),	/* Offset= 440 (1050) */
/* 612 */	
			0x12, 0x0,	/* FC_UP */
/* 614 */	NdrFcShort( 0x20 ),	/* Offset= 32 (646) */
/* 616 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 618 */	NdrFcLong( 0x2f ),	/* 47 */
/* 622 */	NdrFcShort( 0x0 ),	/* 0 */
/* 624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 626 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 628 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 630 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 632 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 634 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 636 */	NdrFcShort( 0x1 ),	/* 1 */
/* 638 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 640 */	NdrFcShort( 0x4 ),	/* 4 */
/* 642 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 644 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 646 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 648 */	NdrFcShort( 0x10 ),	/* 16 */
/* 650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 652 */	NdrFcShort( 0xa ),	/* Offset= 10 (662) */
/* 654 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 656 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 658 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (616) */
/* 660 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 662 */	
			0x12, 0x0,	/* FC_UP */
/* 664 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (634) */
/* 666 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 668 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 670 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 672 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 674 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 676 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 678 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 680 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 682 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 684 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 686 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 688 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 690 */	
			0x12, 0x0,	/* FC_UP */
/* 692 */	NdrFcShort( 0xffa2 ),	/* Offset= -94 (598) */
/* 694 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 696 */	NdrFcShort( 0xfd72 ),	/* Offset= -654 (42) */
/* 698 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 700 */	NdrFcShort( 0xfe00 ),	/* Offset= -512 (188) */
/* 702 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 704 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (244) */
/* 706 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 708 */	NdrFcShort( 0x2 ),	/* Offset= 2 (710) */
/* 710 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 712 */	NdrFcShort( 0x2 ),	/* Offset= 2 (714) */
/* 714 */	
			0x12, 0x0,	/* FC_UP */
/* 716 */	NdrFcShort( 0x14e ),	/* Offset= 334 (1050) */
/* 718 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 720 */	NdrFcShort( 0x2 ),	/* Offset= 2 (722) */
/* 722 */	
			0x12, 0x0,	/* FC_UP */
/* 724 */	NdrFcShort( 0x14 ),	/* Offset= 20 (744) */
/* 726 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 728 */	NdrFcShort( 0x10 ),	/* 16 */
/* 730 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 732 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 734 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 736 */	
			0x12, 0x0,	/* FC_UP */
/* 738 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (726) */
/* 740 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 742 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 744 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 746 */	NdrFcShort( 0x20 ),	/* 32 */
/* 748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 750 */	NdrFcShort( 0x0 ),	/* Offset= 0 (750) */
/* 752 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 754 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 756 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 758 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 760 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (300) */
/* 762 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 764 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 766 */	NdrFcShort( 0x4 ),	/* 4 */
/* 768 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 772 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 774 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 776 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 778 */	NdrFcShort( 0x4 ),	/* 4 */
/* 780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 782 */	NdrFcShort( 0x1 ),	/* 1 */
/* 784 */	NdrFcShort( 0x0 ),	/* 0 */
/* 786 */	NdrFcShort( 0x0 ),	/* 0 */
/* 788 */	0x12, 0x0,	/* FC_UP */
/* 790 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (744) */
/* 792 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 794 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 796 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 798 */	NdrFcShort( 0x8 ),	/* 8 */
/* 800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 802 */	NdrFcShort( 0x6 ),	/* Offset= 6 (808) */
/* 804 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 806 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 808 */	
			0x11, 0x0,	/* FC_RP */
/* 810 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (764) */
/* 812 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 814 */	NdrFcShort( 0x4 ),	/* 4 */
/* 816 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 820 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 822 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 824 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 826 */	NdrFcShort( 0x4 ),	/* 4 */
/* 828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 830 */	NdrFcShort( 0x1 ),	/* 1 */
/* 832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 834 */	NdrFcShort( 0x0 ),	/* 0 */
/* 836 */	0x12, 0x0,	/* FC_UP */
/* 838 */	NdrFcShort( 0xff40 ),	/* Offset= -192 (646) */
/* 840 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 842 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 844 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 846 */	NdrFcShort( 0x8 ),	/* 8 */
/* 848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0x6 ),	/* Offset= 6 (856) */
/* 852 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 854 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 856 */	
			0x11, 0x0,	/* FC_RP */
/* 858 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (812) */
/* 860 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 862 */	NdrFcShort( 0x8 ),	/* 8 */
/* 864 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 866 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 868 */	NdrFcShort( 0x10 ),	/* 16 */
/* 870 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 872 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 874 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (860) */
			0x5b,		/* FC_END */
/* 878 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 880 */	NdrFcShort( 0x18 ),	/* 24 */
/* 882 */	NdrFcShort( 0x0 ),	/* 0 */
/* 884 */	NdrFcShort( 0xa ),	/* Offset= 10 (894) */
/* 886 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 888 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 890 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (866) */
/* 892 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 894 */	
			0x11, 0x0,	/* FC_RP */
/* 896 */	NdrFcShort( 0xfd4e ),	/* Offset= -690 (206) */
/* 898 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 900 */	NdrFcShort( 0x1 ),	/* 1 */
/* 902 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 904 */	NdrFcShort( 0x0 ),	/* 0 */
/* 906 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 908 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 910 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 912 */	NdrFcShort( 0x8 ),	/* 8 */
/* 914 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 916 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 918 */	NdrFcShort( 0x4 ),	/* 4 */
/* 920 */	NdrFcShort( 0x4 ),	/* 4 */
/* 922 */	0x12, 0x0,	/* FC_UP */
/* 924 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (898) */
/* 926 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 928 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 930 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 932 */	NdrFcShort( 0x2 ),	/* 2 */
/* 934 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 938 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 940 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 942 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 944 */	NdrFcShort( 0x8 ),	/* 8 */
/* 946 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 948 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 950 */	NdrFcShort( 0x4 ),	/* 4 */
/* 952 */	NdrFcShort( 0x4 ),	/* 4 */
/* 954 */	0x12, 0x0,	/* FC_UP */
/* 956 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (930) */
/* 958 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 960 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 962 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 964 */	NdrFcShort( 0x4 ),	/* 4 */
/* 966 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 968 */	NdrFcShort( 0x0 ),	/* 0 */
/* 970 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 972 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 974 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 976 */	NdrFcShort( 0x8 ),	/* 8 */
/* 978 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 980 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 982 */	NdrFcShort( 0x4 ),	/* 4 */
/* 984 */	NdrFcShort( 0x4 ),	/* 4 */
/* 986 */	0x12, 0x0,	/* FC_UP */
/* 988 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (962) */
/* 990 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 992 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 994 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 996 */	NdrFcShort( 0x8 ),	/* 8 */
/* 998 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1000 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1002 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1004 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1006 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1008 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1010 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1012 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1014 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1016 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1018 */	0x12, 0x0,	/* FC_UP */
/* 1020 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (994) */
/* 1022 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1024 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1026 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1028 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1030 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1032 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1034 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1036 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1038 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 1040 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 1042 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1044 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1046 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1026) */
/* 1048 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1050 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1052 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1054 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1034) */
/* 1056 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1056) */
/* 1058 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1060 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1062 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1064 */	NdrFcShort( 0xfc1c ),	/* Offset= -996 (68) */
/* 1066 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1068 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1070 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1072 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1076 */	NdrFcShort( 0xfc08 ),	/* Offset= -1016 (60) */
/* 1078 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1080 */	NdrFcShort( 0xa ),	/* Offset= 10 (1090) */
/* 1082 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1084 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1086) */
/* 1086 */	
			0x13, 0x0,	/* FC_OP */
/* 1088 */	NdrFcShort( 0xffda ),	/* Offset= -38 (1050) */
/* 1090 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1092 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1094 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1096 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1098 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (1082) */
/* 1100 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1102 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            LPSAFEARRAY_UserSize
            ,LPSAFEARRAY_UserMarshal
            ,LPSAFEARRAY_UserUnmarshal
            ,LPSAFEARRAY_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IcvCompiler, ver. 0.0,
   GUID={0x533FBF62,0xA034,0x4A58,{0x8F,0xB2,0x19,0xC6,0xE9,0xFA,0x0C,0xDE}} */

#pragma code_seg(".orpc")
static const unsigned short IcvCompiler_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    36,
    72
    };

static const MIDL_STUBLESS_PROXY_INFO IcvCompiler_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IcvCompiler_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IcvCompiler_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IcvCompiler_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IcvCompilerProxyVtbl = 
{
    &IcvCompiler_ProxyInfo,
    &IID_IcvCompiler,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IcvCompiler::get_ConnectionString */ ,
    (void *) (INT_PTR) -1 /* IcvCompiler::put_ConnectionString */ ,
    (void *) (INT_PTR) -1 /* IcvCompiler::Compile */
};


static const PRPC_STUB_FUNCTION IcvCompiler_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IcvCompilerStubVtbl =
{
    &IID_IcvCompiler,
    &IcvCompiler_ServerInfo,
    10,
    &IcvCompiler_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x600016e, /* MIDL Version 6.0.366 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _cvCompiler_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IcvCompilerProxyVtbl,
    0
};

const CInterfaceStubVtbl * _cvCompiler_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IcvCompilerStubVtbl,
    0
};

PCInterfaceName const _cvCompiler_InterfaceNamesList[] = 
{
    "IcvCompiler",
    0
};

const IID *  _cvCompiler_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _cvCompiler_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _cvCompiler, pIID, n)

int __stdcall _cvCompiler_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_cvCompiler_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo cvCompiler_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _cvCompiler_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _cvCompiler_StubVtblList,
    (const PCInterfaceName * ) & _cvCompiler_InterfaceNamesList,
    (const IID ** ) & _cvCompiler_BaseIIDList,
    & _cvCompiler_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

