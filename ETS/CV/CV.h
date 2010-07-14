

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __CV_h__
#define __CV_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IcvDataProvider_FWD_DEFINED__
#define __IcvDataProvider_FWD_DEFINED__
typedef interface IcvDataProvider IcvDataProvider;
#endif 	/* __IcvDataProvider_FWD_DEFINED__ */


#ifndef __IcvRTContext_FWD_DEFINED__
#define __IcvRTContext_FWD_DEFINED__
typedef interface IcvRTContext IcvRTContext;
#endif 	/* __IcvRTContext_FWD_DEFINED__ */


#ifndef __cvRTContext_FWD_DEFINED__
#define __cvRTContext_FWD_DEFINED__

#ifdef __cplusplus
typedef class cvRTContext cvRTContext;
#else
typedef struct cvRTContext cvRTContext;
#endif /* __cplusplus */

#endif 	/* __cvRTContext_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __CVLib_LIBRARY_DEFINED__
#define __CVLib_LIBRARY_DEFINED__

/* library CVLib */
/* [helpstring][version][uuid] */ 

typedef /* [uuid] */  DECLSPEC_UUID("08F57F31-AA3E-4a00-9921-FC76BC73FAAA") 
enum cvType
    {	cvNone	= 0,
	cvNumeric	= cvNone + 1,
	cvBoolean	= cvNumeric + 1,
	cvString	= cvBoolean + 1
    } 	cvType;

/* [uuid] */ struct  DECLSPEC_UUID("8B070918-95BB-48ae-9EAD-99D037AA1DB4") cvInfo
    {
    BSTR Name;
    cvType Type;
    BSTR Caption;
    BSTR Format;
    LONG ID;
    } ;

EXTERN_C const IID LIBID_CVLib;

#ifndef __IcvDataProvider_INTERFACE_DEFINED__
#define __IcvDataProvider_INTERFACE_DEFINED__

/* interface IcvDataProvider */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IcvDataProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("225DA231-B37D-43c7-947A-2F249EDF9CF5")
    IcvDataProvider : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetData( 
            /* [in] */ LONG lDataID,
            /* [out] */ VARIANT *Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallFunction( 
            /* [in] */ LONG lFunctionID,
            /* [in] */ SAFEARRAY * *arrParameters,
            /* [out] */ VARIANT *Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Check( 
            /* [in] */ SAFEARRAY * *arrSysVars,
            /* [in] */ SAFEARRAY * *arrSysFuncs,
            /* [retval][out] */ LONG *pRetVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcvDataProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcvDataProvider * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcvDataProvider * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcvDataProvider * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcvDataProvider * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcvDataProvider * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcvDataProvider * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcvDataProvider * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetData )( 
            IcvDataProvider * This,
            /* [in] */ LONG lDataID,
            /* [out] */ VARIANT *Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CallFunction )( 
            IcvDataProvider * This,
            /* [in] */ LONG lFunctionID,
            /* [in] */ SAFEARRAY * *arrParameters,
            /* [out] */ VARIANT *Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Check )( 
            IcvDataProvider * This,
            /* [in] */ SAFEARRAY * *arrSysVars,
            /* [in] */ SAFEARRAY * *arrSysFuncs,
            /* [retval][out] */ LONG *pRetVal);
        
        END_INTERFACE
    } IcvDataProviderVtbl;

    interface IcvDataProvider
    {
        CONST_VTBL struct IcvDataProviderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcvDataProvider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcvDataProvider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcvDataProvider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcvDataProvider_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcvDataProvider_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcvDataProvider_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcvDataProvider_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcvDataProvider_GetData(This,lDataID,Value)	\
    (This)->lpVtbl -> GetData(This,lDataID,Value)

#define IcvDataProvider_CallFunction(This,lFunctionID,arrParameters,Value)	\
    (This)->lpVtbl -> CallFunction(This,lFunctionID,arrParameters,Value)

#define IcvDataProvider_Check(This,arrSysVars,arrSysFuncs,pRetVal)	\
    (This)->lpVtbl -> Check(This,arrSysVars,arrSysFuncs,pRetVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvDataProvider_GetData_Proxy( 
    IcvDataProvider * This,
    /* [in] */ LONG lDataID,
    /* [out] */ VARIANT *Value);


void __RPC_STUB IcvDataProvider_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvDataProvider_CallFunction_Proxy( 
    IcvDataProvider * This,
    /* [in] */ LONG lFunctionID,
    /* [in] */ SAFEARRAY * *arrParameters,
    /* [out] */ VARIANT *Value);


void __RPC_STUB IcvDataProvider_CallFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvDataProvider_Check_Proxy( 
    IcvDataProvider * This,
    /* [in] */ SAFEARRAY * *arrSysVars,
    /* [in] */ SAFEARRAY * *arrSysFuncs,
    /* [retval][out] */ LONG *pRetVal);


void __RPC_STUB IcvDataProvider_Check_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcvDataProvider_INTERFACE_DEFINED__ */


#ifndef __IcvRTContext_INTERFACE_DEFINED__
#define __IcvRTContext_INTERFACE_DEFINED__

/* interface IcvRTContext */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IcvRTContext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("10FC8A48-7539-4C54-87C2-8F6174CE0165")
    IcvRTContext : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitContext( 
            /* [in] */ LONG contextID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectionString( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Halted( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateCVPool( 
            /* [in] */ IcvDataProvider *pIcvDataProvider,
            /* [in] */ LONG lLevelID,
            /* [retval][out] */ LONG *lPoolID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRequiredDataProviderLevels( 
            LONG lLevelID,
            /* [retval][out] */ SAFEARRAY * *LevelsArray) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BindAggregations( 
            /* [in] */ LONG lPoolID,
            /* [in] */ LONG lAggregationPoolID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Recalculate( 
            LONG lPoolID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCVInfo( 
            /* [in] */ LONG lLevelID,
            /* [in] */ LONG lCVID,
            /* [retval][out] */ struct cvInfo *pInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCVIDs( 
            /* [in] */ LONG lLevelID,
            /* [retval][out] */ SAFEARRAY * *arrayCVIDs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCVValue( 
            /* [in] */ LONG lPoolID,
            /* [in] */ LONG lCVID,
            /* [retval][out] */ VARIANT *pRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RegisterPoolDataProvider( 
            /* [in] */ LONG lPoolID,
            /* [in] */ LONG lDataProviderLevelID,
            IcvDataProvider *pIcvDataProvider) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLevelIDByName( 
            /* [in] */ BSTR strLevelName,
            /* [retval][out] */ LONG *pID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSystemEnvironment( 
            /* [in] */ LONG lLevelID,
            /* [out] */ SAFEARRAY * *arrayVariables,
            /* [out] */ SAFEARRAY * *arrayFunctions) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveCVPool( 
            /* [in] */ LONG lPoolID,
            /* [in] */ VARIANT_BOOL bClearAggOnly) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Halt( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRecalculateCvCount( 
            /* [in] */ LONG Count) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IcvRTContextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcvRTContext * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcvRTContext * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcvRTContext * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcvRTContext * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcvRTContext * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcvRTContext * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcvRTContext * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitContext )( 
            IcvRTContext * This,
            /* [in] */ LONG contextID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConnectionString )( 
            IcvRTContext * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConnectionString )( 
            IcvRTContext * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Halted )( 
            IcvRTContext * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateCVPool )( 
            IcvRTContext * This,
            /* [in] */ IcvDataProvider *pIcvDataProvider,
            /* [in] */ LONG lLevelID,
            /* [retval][out] */ LONG *lPoolID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRequiredDataProviderLevels )( 
            IcvRTContext * This,
            LONG lLevelID,
            /* [retval][out] */ SAFEARRAY * *LevelsArray);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BindAggregations )( 
            IcvRTContext * This,
            /* [in] */ LONG lPoolID,
            /* [in] */ LONG lAggregationPoolID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Recalculate )( 
            IcvRTContext * This,
            LONG lPoolID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCVInfo )( 
            IcvRTContext * This,
            /* [in] */ LONG lLevelID,
            /* [in] */ LONG lCVID,
            /* [retval][out] */ struct cvInfo *pInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCVIDs )( 
            IcvRTContext * This,
            /* [in] */ LONG lLevelID,
            /* [retval][out] */ SAFEARRAY * *arrayCVIDs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCVValue )( 
            IcvRTContext * This,
            /* [in] */ LONG lPoolID,
            /* [in] */ LONG lCVID,
            /* [retval][out] */ VARIANT *pRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RegisterPoolDataProvider )( 
            IcvRTContext * This,
            /* [in] */ LONG lPoolID,
            /* [in] */ LONG lDataProviderLevelID,
            IcvDataProvider *pIcvDataProvider);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLevelIDByName )( 
            IcvRTContext * This,
            /* [in] */ BSTR strLevelName,
            /* [retval][out] */ LONG *pID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSystemEnvironment )( 
            IcvRTContext * This,
            /* [in] */ LONG lLevelID,
            /* [out] */ SAFEARRAY * *arrayVariables,
            /* [out] */ SAFEARRAY * *arrayFunctions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveCVPool )( 
            IcvRTContext * This,
            /* [in] */ LONG lPoolID,
            /* [in] */ VARIANT_BOOL bClearAggOnly);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Halt )( 
            IcvRTContext * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IcvRTContext * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRecalculateCvCount )( 
            IcvRTContext * This,
            /* [in] */ LONG Count);
        
        END_INTERFACE
    } IcvRTContextVtbl;

    interface IcvRTContext
    {
        CONST_VTBL struct IcvRTContextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcvRTContext_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IcvRTContext_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IcvRTContext_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IcvRTContext_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IcvRTContext_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IcvRTContext_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IcvRTContext_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IcvRTContext_InitContext(This,contextID)	\
    (This)->lpVtbl -> InitContext(This,contextID)

#define IcvRTContext_get_ConnectionString(This,pVal)	\
    (This)->lpVtbl -> get_ConnectionString(This,pVal)

#define IcvRTContext_put_ConnectionString(This,newVal)	\
    (This)->lpVtbl -> put_ConnectionString(This,newVal)

#define IcvRTContext_get_Halted(This,pVal)	\
    (This)->lpVtbl -> get_Halted(This,pVal)

#define IcvRTContext_CreateCVPool(This,pIcvDataProvider,lLevelID,lPoolID)	\
    (This)->lpVtbl -> CreateCVPool(This,pIcvDataProvider,lLevelID,lPoolID)

#define IcvRTContext_GetRequiredDataProviderLevels(This,lLevelID,LevelsArray)	\
    (This)->lpVtbl -> GetRequiredDataProviderLevels(This,lLevelID,LevelsArray)

#define IcvRTContext_BindAggregations(This,lPoolID,lAggregationPoolID)	\
    (This)->lpVtbl -> BindAggregations(This,lPoolID,lAggregationPoolID)

#define IcvRTContext_Recalculate(This,lPoolID)	\
    (This)->lpVtbl -> Recalculate(This,lPoolID)

#define IcvRTContext_GetCVInfo(This,lLevelID,lCVID,pInfo)	\
    (This)->lpVtbl -> GetCVInfo(This,lLevelID,lCVID,pInfo)

#define IcvRTContext_GetCVIDs(This,lLevelID,arrayCVIDs)	\
    (This)->lpVtbl -> GetCVIDs(This,lLevelID,arrayCVIDs)

#define IcvRTContext_GetCVValue(This,lPoolID,lCVID,pRetVal)	\
    (This)->lpVtbl -> GetCVValue(This,lPoolID,lCVID,pRetVal)

#define IcvRTContext_RegisterPoolDataProvider(This,lPoolID,lDataProviderLevelID,pIcvDataProvider)	\
    (This)->lpVtbl -> RegisterPoolDataProvider(This,lPoolID,lDataProviderLevelID,pIcvDataProvider)

#define IcvRTContext_GetLevelIDByName(This,strLevelName,pID)	\
    (This)->lpVtbl -> GetLevelIDByName(This,strLevelName,pID)

#define IcvRTContext_GetSystemEnvironment(This,lLevelID,arrayVariables,arrayFunctions)	\
    (This)->lpVtbl -> GetSystemEnvironment(This,lLevelID,arrayVariables,arrayFunctions)

#define IcvRTContext_RemoveCVPool(This,lPoolID,bClearAggOnly)	\
    (This)->lpVtbl -> RemoveCVPool(This,lPoolID,bClearAggOnly)

#define IcvRTContext_Halt(This)	\
    (This)->lpVtbl -> Halt(This)

#define IcvRTContext_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IcvRTContext_SetRecalculateCvCount(This,Count)	\
    (This)->lpVtbl -> SetRecalculateCvCount(This,Count)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_InitContext_Proxy( 
    IcvRTContext * This,
    /* [in] */ LONG contextID);


void __RPC_STUB IcvRTContext_InitContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcvRTContext_get_ConnectionString_Proxy( 
    IcvRTContext * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IcvRTContext_get_ConnectionString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IcvRTContext_put_ConnectionString_Proxy( 
    IcvRTContext * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IcvRTContext_put_ConnectionString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IcvRTContext_get_Halted_Proxy( 
    IcvRTContext * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IcvRTContext_get_Halted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_CreateCVPool_Proxy( 
    IcvRTContext * This,
    /* [in] */ IcvDataProvider *pIcvDataProvider,
    /* [in] */ LONG lLevelID,
    /* [retval][out] */ LONG *lPoolID);


void __RPC_STUB IcvRTContext_CreateCVPool_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_GetRequiredDataProviderLevels_Proxy( 
    IcvRTContext * This,
    LONG lLevelID,
    /* [retval][out] */ SAFEARRAY * *LevelsArray);


void __RPC_STUB IcvRTContext_GetRequiredDataProviderLevels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_BindAggregations_Proxy( 
    IcvRTContext * This,
    /* [in] */ LONG lPoolID,
    /* [in] */ LONG lAggregationPoolID);


void __RPC_STUB IcvRTContext_BindAggregations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_Recalculate_Proxy( 
    IcvRTContext * This,
    LONG lPoolID);


void __RPC_STUB IcvRTContext_Recalculate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_GetCVInfo_Proxy( 
    IcvRTContext * This,
    /* [in] */ LONG lLevelID,
    /* [in] */ LONG lCVID,
    /* [retval][out] */ struct cvInfo *pInfo);


void __RPC_STUB IcvRTContext_GetCVInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_GetCVIDs_Proxy( 
    IcvRTContext * This,
    /* [in] */ LONG lLevelID,
    /* [retval][out] */ SAFEARRAY * *arrayCVIDs);


void __RPC_STUB IcvRTContext_GetCVIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_GetCVValue_Proxy( 
    IcvRTContext * This,
    /* [in] */ LONG lPoolID,
    /* [in] */ LONG lCVID,
    /* [retval][out] */ VARIANT *pRetVal);


void __RPC_STUB IcvRTContext_GetCVValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_RegisterPoolDataProvider_Proxy( 
    IcvRTContext * This,
    /* [in] */ LONG lPoolID,
    /* [in] */ LONG lDataProviderLevelID,
    IcvDataProvider *pIcvDataProvider);


void __RPC_STUB IcvRTContext_RegisterPoolDataProvider_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_GetLevelIDByName_Proxy( 
    IcvRTContext * This,
    /* [in] */ BSTR strLevelName,
    /* [retval][out] */ LONG *pID);


void __RPC_STUB IcvRTContext_GetLevelIDByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_GetSystemEnvironment_Proxy( 
    IcvRTContext * This,
    /* [in] */ LONG lLevelID,
    /* [out] */ SAFEARRAY * *arrayVariables,
    /* [out] */ SAFEARRAY * *arrayFunctions);


void __RPC_STUB IcvRTContext_GetSystemEnvironment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_RemoveCVPool_Proxy( 
    IcvRTContext * This,
    /* [in] */ LONG lPoolID,
    /* [in] */ VARIANT_BOOL bClearAggOnly);


void __RPC_STUB IcvRTContext_RemoveCVPool_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_Halt_Proxy( 
    IcvRTContext * This);


void __RPC_STUB IcvRTContext_Halt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_Clear_Proxy( 
    IcvRTContext * This);


void __RPC_STUB IcvRTContext_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IcvRTContext_SetRecalculateCvCount_Proxy( 
    IcvRTContext * This,
    /* [in] */ LONG Count);


void __RPC_STUB IcvRTContext_SetRecalculateCvCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IcvRTContext_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_cvRTContext;

#ifdef __cplusplus

class DECLSPEC_UUID("9AFC738C-04A4-497B-9C19-2897F3387CDC")
cvRTContext;
#endif
#endif /* __CVLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


