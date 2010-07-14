

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __cvCompiler_h__
#define __cvCompiler_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IcvCompiler_FWD_DEFINED__
#define __IcvCompiler_FWD_DEFINED__
typedef interface IcvCompiler IcvCompiler;
#endif 	/* __IcvCompiler_FWD_DEFINED__ */


#ifndef ___IcvCompilerEvents_FWD_DEFINED__
#define ___IcvCompilerEvents_FWD_DEFINED__
typedef interface _IcvCompilerEvents _IcvCompilerEvents;
#endif 	/* ___IcvCompilerEvents_FWD_DEFINED__ */


#ifndef __cvCompiler_FWD_DEFINED__
#define __cvCompiler_FWD_DEFINED__

#ifdef __cplusplus
typedef class cvCompiler cvCompiler;
#else
typedef struct cvCompiler cvCompiler;
#endif /* __cplusplus */

#endif 	/* __cvCompiler_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IcvCompiler_INTERFACE_DEFINED__
#define __IcvCompiler_INTERFACE_DEFINED__

/* interface IcvCompiler */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IcvCompiler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("533FBF62-A034-4A58-8FB2-19C6E9FA0CDE")
    IcvCompiler : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectionString( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Compile( 
            /* [in] */ LONG iContext,
            /* [in] */ LONG iLevel,
            /* [in] */ BSTR strVarName,
            /* [in] */ BSTR strCaption,
            /* [in] */ BSTR strFormat,
            /* [in] */ BSTR strSource,
            /* [in] */ BSTR strDescription,
            /* [in] */ SAFEARRAY * *arrAggregation,
            /* [out] */ SAFEARRAY * *arrErrors,
            /* [out] */ SAFEARRAY * *arrCode,
            /* [retval][out] */ LONG *iVariableID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcvCompilerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcvCompiler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcvCompiler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcvCompiler * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcvCompiler * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcvCompiler * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcvCompiler * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcvCompiler * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConnectionString )( 
            IcvCompiler * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConnectionString )( 
            IcvCompiler * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Compile )( 
            IcvCompiler * This,
            /* [in] */ LONG iContext,
            /* [in] */ LONG iLevel,
            /* [in] */ BSTR strVarName,
            /* [in] */ BSTR strCaption,
            /* [in] */ BSTR strFormat,
            /* [in] */ BSTR strSource,
            /* [in] */ BSTR strDescription,
            /* [in] */ SAFEARRAY * *arrAggregation,
            /* [out] */ SAFEARRAY * *arrErrors,
            /* [out] */ SAFEARRAY * *arrCode,
            /* [retval][out] */ LONG *iVariableID);
        
        END_INTERFACE
    } IcvCompilerVtbl;

    interface IcvCompiler
    {
        CONST_VTBL struct IcvCompilerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcvCompiler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcvCompiler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcvCompiler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcvCompiler_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcvCompiler_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcvCompiler_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcvCompiler_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcvCompiler_get_ConnectionString(This,pVal)	\
    (This)->lpVtbl -> get_ConnectionString(This,pVal)

#define IcvCompiler_put_ConnectionString(This,newVal)	\
    (This)->lpVtbl -> put_ConnectionString(This,newVal)

#define IcvCompiler_Compile(This,iContext,iLevel,strVarName,strCaption,strFormat,strSource,strDescription,arrAggregation,arrErrors,arrCode,iVariableID)	\
    (This)->lpVtbl -> Compile(This,iContext,iLevel,strVarName,strCaption,strFormat,strSource,strDescription,arrAggregation,arrErrors,arrCode,iVariableID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcvCompiler_get_ConnectionString_Proxy( 
    IcvCompiler * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcvCompiler_get_ConnectionString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcvCompiler_put_ConnectionString_Proxy( 
    IcvCompiler * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcvCompiler_put_ConnectionString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvCompiler_Compile_Proxy( 
    IcvCompiler * This,
    /* [in] */ LONG iContext,
    /* [in] */ LONG iLevel,
    /* [in] */ BSTR strVarName,
    /* [in] */ BSTR strCaption,
    /* [in] */ BSTR strFormat,
    /* [in] */ BSTR strSource,
    /* [in] */ BSTR strDescription,
    /* [in] */ SAFEARRAY * *arrAggregation,
    /* [out] */ SAFEARRAY * *arrErrors,
    /* [out] */ SAFEARRAY * *arrCode,
    /* [retval][out] */ LONG *iVariableID);


void __RPC_STUB IcvCompiler_Compile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcvCompiler_INTERFACE_DEFINED__ */



#ifndef __cvCompilerLib_LIBRARY_DEFINED__
#define __cvCompilerLib_LIBRARY_DEFINED__

/* library cvCompilerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_cvCompilerLib;

#ifndef ___IcvCompilerEvents_DISPINTERFACE_DEFINED__
#define ___IcvCompilerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IcvCompilerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IcvCompilerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C144615B-B41A-4C2B-BA81-A0F44390FFB7")
    _IcvCompilerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IcvCompilerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IcvCompilerEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IcvCompilerEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IcvCompilerEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IcvCompilerEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IcvCompilerEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IcvCompilerEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IcvCompilerEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IcvCompilerEventsVtbl;

    interface _IcvCompilerEvents
    {
        CONST_VTBL struct _IcvCompilerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IcvCompilerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IcvCompilerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IcvCompilerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IcvCompilerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IcvCompilerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IcvCompilerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IcvCompilerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IcvCompilerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_cvCompiler;

#ifdef __cplusplus

class DECLSPEC_UUID("FAB06E55-A144-45B1-BBDA-225E568B9F78")
cvCompiler;
#endif
#endif /* __cvCompilerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


