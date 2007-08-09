// EtsContractColl.h : Declaration of the CEtsContractColl
#ifndef __ETSCONTRACTCOLL_H__
#define __ETSCONTRACTCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsContractAtom.h"

_COM_SMARTPTR_TYPEDEF(IEtsContractColl, IID_IEtsContractColl);

typedef IDispatchImpl<IEtsContractColl, &IID_IEtsContractColl, &LIBID_EtsGeneralLib>													IEtsContractCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IEtsContractCollDispImpl, IEtsContractAtom, LONG, LONG, BSTR, _bstr_t  >	IEtsContractCollImpl;

// CEtsContractColl
class ATL_NO_VTABLE CEtsContractColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsContractColl, &CLSID_EtsContractColl>,
	public ISupportErrorInfoImpl<&IID_IEtsContractColl>,
	public IEtsContractCollImpl
{
public:
	CEtsContractColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSCONTRACTCOLL)


BEGIN_COM_MAP(CEtsContractColl)
	COM_INTERFACE_ENTRY(IEtsContractColl)
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
		IEtsContractCollImpl::Clear();
	}

public:
	IEtsContractAtomPtr AddNew(long lID, _bstr_t bsSymbol, CComObject<CEtsContractAtom>** pObject = NULL);

public:

	STDMETHOD(Add)(LONG Key, BSTR SortKey, IEtsContractAtom* Value, IEtsContractAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsContractColl), CEtsContractColl)

#endif //__ETSCONTRACTCOLL_H__
