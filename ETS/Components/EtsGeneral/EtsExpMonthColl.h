// EtsExpMonthColl.h : Declaration of the CEtsExpMonthColl
#ifndef __ETSEXPMONTHCOLL_H__
#define __ETSEXPMONTHCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsExpMonthAtom.h"

_COM_SMARTPTR_TYPEDEF(IEtsExpMonthColl, IID_IEtsExpMonthColl);

typedef IDispatchImpl<IEtsExpMonthColl, &IID_IEtsExpMonthColl, &LIBID_EtsGeneralLib>					IEtsExpMonthCollDispImpl;
typedef ICollectionOnSTLMapOfInterfacePtrImpl<IEtsExpMonthCollDispImpl, LONG, IEtsExpMonthAtom, LONG >	IEtsExpMonthCollImpl;

// CEtsExpMonthColl
class ATL_NO_VTABLE CEtsExpMonthColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsExpMonthColl, &CLSID_EtsExpMonthColl>,
	public ISupportErrorInfoImpl<&IID_IEtsExpMonthColl>,
	public IEtsExpMonthCollImpl
{
public:
	CEtsExpMonthColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSEXPMONTHCOLL)


BEGIN_COM_MAP(CEtsExpMonthColl)
	COM_INTERFACE_ENTRY(IEtsExpMonthColl)
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
		IEtsExpMonthCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(LONG Key, IEtsExpMonthAtom* Value, IEtsExpMonthAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsExpMonthColl), CEtsExpMonthColl)

#endif //__ETSEXPMONTHCOLL_H__