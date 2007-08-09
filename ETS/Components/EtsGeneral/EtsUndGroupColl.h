// EtsUndGroupColl.h : Declaration of the CEtsUndGroupColl
#ifndef __ETSUNDGROUPCOLL_H__
#define __ETSUNDGROUPCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsUndGroupAtom.h"

_COM_SMARTPTR_TYPEDEF(IEtsUndGroupColl, IID_IEtsUndGroupColl);

typedef IDispatchImpl<IEtsUndGroupColl, &IID_IEtsUndGroupColl, &LIBID_EtsGeneralLib>													IEtsUndGroupCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IEtsUndGroupCollDispImpl, IEtsUndGroupAtom, LONG, LONG, BSTR, _bstr_t >	IEtsUndGroupCollImpl;

// CEtsUndGroupColl
class ATL_NO_VTABLE CEtsUndGroupColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsUndGroupColl, &CLSID_EtsUndGroupColl>,
	public ISupportErrorInfoImpl<&IID_IEtsUndGroupColl>,
	public IEtsUndGroupCollImpl
{
public:
	CEtsUndGroupColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSUNDGROUPCOLL)


BEGIN_COM_MAP(CEtsUndGroupColl)
	COM_INTERFACE_ENTRY(IEtsUndGroupColl)
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
		IEtsUndGroupCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(LONG Key, BSTR SortKey, IEtsUndGroupAtom* Value, IEtsUndGroupAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsUndGroupColl), CEtsUndGroupColl)

#endif //__ETSUNDGROUPCOLL_H__
