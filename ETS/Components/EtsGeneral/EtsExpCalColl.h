// EtsExpCalColl.h : Declaration of the CEtsExpCalColl
#ifndef __ETSEXPCALCOLL_H__
#define __ETSEXPCALCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"

typedef IDispatchImpl<IEtsExpCalColl, &IID_IEtsExpCalColl, &LIBID_EtsGeneralLib>						IEtsExpCalCollDispImpl;
typedef ICollectionOnSTLMapOfInterfacePtrImpl<IEtsExpCalCollDispImpl, LONG, IEtsExpMonthAtom, LONG >	IEtsExpCalCollImpl;

struct __EtsExpCalColl
{
	LONG	m_nMaturity;

	__EtsExpCalColl()
		: m_nMaturity(0L)
	{
	}
};
_COM_SMARTPTR_TYPEDEF(IEtsExpCalColl, IID_IEtsExpCalColl);

// CEtsExpCalColl
class ATL_NO_VTABLE CEtsExpCalColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsExpCalColl, &CLSID_EtsExpCalColl>,
	public ISupportErrorInfoImpl<&IID_IEtsExpCalColl>,
	public IEtsExpCalCollImpl,
	public __EtsExpCalColl
{
public:
	CEtsExpCalColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSEXPCALCOLL)


BEGIN_COM_MAP(CEtsExpCalColl)
	COM_INTERFACE_ENTRY(IEtsExpCalColl)
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
		IEtsExpCalCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(LONG Key,  IEtsExpMonthAtom* Value, IEtsExpMonthAtom** pRetVal);
	IMPLEMENT_SIMPLE_PROPERTY(LONG, Maturity, m_nMaturity)
	STDMETHOD(GetVegaWeight)(DATE dtExpiry, DOUBLE* pdRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsExpCalColl), CEtsExpCalColl)

#endif //__ETSEXPCALCOLL_H__
