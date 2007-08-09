// EtsTraderUndColl.h : Declaration of the CEtsTraderUndColl
#ifndef __ETSTRADERUNDCOLL_H__
#define __ETSTRADERUNDCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsTraderUndAtom.h"

_COM_SMARTPTR_TYPEDEF(IEtsTraderUndColl, IID_IEtsTraderUndColl);

typedef IDispatchImpl<IEtsTraderUndColl, &IID_IEtsTraderUndColl, &LIBID_EtsGeneralLib>													IEtsTraderUndCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IEtsTraderUndCollDispImpl, IEtsTraderUndAtom, LONG, LONG, BSTR, _bstr_t  >	IEtsTraderUndCollImpl;

// CEtsTraderUndColl
class ATL_NO_VTABLE CEtsTraderUndColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsTraderUndColl, &CLSID_EtsTraderUndColl>,
	public ISupportErrorInfoImpl<&IID_IEtsTraderUndColl>,
	public IEtsTraderUndCollImpl
{
public:
	CEtsTraderUndColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSTRADERUNDCOLL)


BEGIN_COM_MAP(CEtsTraderUndColl)
	COM_INTERFACE_ENTRY(IEtsTraderUndColl)
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
		IEtsTraderUndCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(LONG Key, BSTR SortKey, IEtsTraderUndAtom* Value, IEtsTraderUndAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsTraderUndColl), CEtsTraderUndColl)

#endif //__ETSTRADERUNDCOLL_H__