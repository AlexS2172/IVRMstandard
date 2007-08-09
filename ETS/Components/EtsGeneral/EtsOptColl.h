// EtsOptColl.h : Declaration of the CEtsOptColl
#ifndef __ETSOPTCOLL_H__
#define __ETSOPTCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsOptAtom.h"

typedef IDispatchImpl<IEtsOptColl, &IID_IEtsOptColl, &LIBID_EtsGeneralLib>													IEtsOptCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IEtsOptCollDispImpl, IEtsOptAtom, LONG, LONG, BSTR, _bstr_t  >	IEtsOptCollImpl;

// CEtsOptColl

class ATL_NO_VTABLE CEtsOptColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsOptColl, &CLSID_EtsOptColl>,
	public ISupportErrorInfoImpl<&IID_IEtsOptColl>,
	public IEtsOptCollImpl
{
public:
	CEtsOptColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSOPTCOLL)


BEGIN_COM_MAP(CEtsOptColl)
	COM_INTERFACE_ENTRY(IEtsOptColl)
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
		IEtsOptCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(LONG Key, BSTR SortKey, IEtsOptAtom* Value, IEtsOptAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsOptColl), CEtsOptColl)

#endif //__ETSOPTCOLL_H__
