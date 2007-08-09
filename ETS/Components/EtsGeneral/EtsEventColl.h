// EtsEventColl.h : Declaration of the CEtsEventColl
#ifndef __ETSEVENTCOLL_H__
#define __ETSEVENTCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsEventAtom.h"

typedef IDispatchImpl<IEtsEventColl, &IID_IEtsEventColl, &LIBID_EtsGeneralLib>									IEtsEventCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IEtsEventCollDispImpl, IEtsEventAtom, LONG, LONG, DATE, DATE >	IEtsEventCollImpl;

// CEtsEventColl

class ATL_NO_VTABLE CEtsEventColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsEventColl, &CLSID_EtsEventColl>,
	public ISupportErrorInfoImpl<&IID_IEtsEventColl>,
	public IEtsEventCollImpl
{
public:
	CEtsEventColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSEVENTCOLL)


BEGIN_COM_MAP(CEtsEventColl)
	COM_INTERFACE_ENTRY(IEtsEventColl)
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
		IEtsEventCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(LONG Key, DATE SortKey, IEtsEventAtom* Value, IEtsEventAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsEventColl), CEtsEventColl)

#endif //__ETSEVENTCOLL_H__
