// EtsStrategyColl.h : Declaration of the CEtsStrategyColl
#ifndef __ETSSTRATEGYCOLL_H__
#define __ETSSTRATEGYCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsStrategyAtom.h"

_COM_SMARTPTR_TYPEDEF(IEtsStrategyColl, IID_IEtsStrategyColl);

typedef IDispatchImpl<IEtsStrategyColl, &IID_IEtsStrategyColl, &LIBID_EtsGeneralLib>													IEtsStrategyCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IEtsStrategyCollDispImpl, IEtsStrategyAtom, LONG, LONG, BSTR, _bstr_t  >	IEtsStrategyCollImpl;

// CEtsStrategyColl
class ATL_NO_VTABLE CEtsStrategyColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsStrategyColl, &CLSID_EtsStrategyColl>,
	public ISupportErrorInfoImpl<&IID_IEtsStrategyColl>,
	public IEtsStrategyCollImpl
{
public:
	CEtsStrategyColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSSTRATEGYCOLL)


BEGIN_COM_MAP(CEtsStrategyColl)
	COM_INTERFACE_ENTRY(IEtsStrategyColl)
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
		IEtsStrategyCollImpl::Clear();
	}

public:
	IEtsStrategyAtomPtr AddNew(long lKey, _bstr_t bsKey, _bstr_t bsDescription = L"", CComObject<CEtsStrategyAtom>** pAtom = NULL);
public:

	STDMETHOD(Add)(LONG Key, BSTR SortKey, IEtsStrategyAtom* Value, IEtsStrategyAtom** pRetVal);

};

OBJECT_ENTRY_AUTO(__uuidof(EtsStrategyColl), CEtsStrategyColl)

#endif //__ETSSTRATEGYCOLL_H__
