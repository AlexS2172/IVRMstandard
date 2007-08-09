// EtsOptRootByNameColl.h : Declaration of the CEtsOptRootByNameColl
#ifndef __ETSOPTROOTBYNAMECOLL_H__
#define __ETSOPTROOTBYNAMECOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsOptRootAtom.h"

_COM_SMARTPTR_TYPEDEF(IEtsOptRootByNameColl, IID_IEtsOptRootByNameColl);

typedef IDispatchImpl<IEtsOptRootByNameColl, &IID_IEtsOptRootByNameColl, &LIBID_EtsGeneralLib>								IEtsOptRootByNameCollDispImpl;
typedef ICollectionOnSTLMapOfInterfacePtrImpl<IEtsOptRootByNameCollDispImpl, BSTR, IEtsOptRootAtom, CAdapt<CComBSTR> >		IEtsOptRootByNameCollImpl;

// CEtsOptRootByNameColl
class ATL_NO_VTABLE CEtsOptRootByNameColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsOptRootByNameColl, &CLSID_EtsOptRootByNameColl>,
	public ISupportErrorInfoImpl<&IID_IEtsOptRootByNameColl>,
	public IEtsOptRootByNameCollImpl
{
public:
	CEtsOptRootByNameColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSOPTROOTBYNAMECOLL)


BEGIN_COM_MAP(CEtsOptRootByNameColl)
	COM_INTERFACE_ENTRY(IEtsOptRootByNameColl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
		IEtsOptRootByNameCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(BSTR Key, IEtsOptRootAtom* Value, IEtsOptRootAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsOptRootByNameColl), CEtsOptRootByNameColl)

#endif //__ETSOPTROOTBYNAMECOLL_H__