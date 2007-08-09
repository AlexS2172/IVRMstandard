// EtsTraderColl.h : Declaration of the CEtsTraderColl
#ifndef __ETSTRADERCOLL_H__
#define __ETSTRADERCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsTraderAtom.h"

_COM_SMARTPTR_TYPEDEF(IEtsTraderColl, IID_IEtsTraderColl);

typedef IDispatchImpl<IEtsTraderColl, &IID_IEtsTraderColl, &LIBID_EtsGeneralLib>													IEtsTraderCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IEtsTraderCollDispImpl, IEtsTraderAtom, LONG, LONG, BSTR, _bstr_t  >	IEtsTraderCollImpl;

// CEtsTraderColl
class ATL_NO_VTABLE CEtsTraderColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsTraderColl, &CLSID_EtsTraderColl>,
	public ISupportErrorInfoImpl<&IID_IEtsTraderColl>,
	public IEtsTraderCollImpl
{
public:
	CEtsTraderColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSTRADERCOLL)


BEGIN_COM_MAP(CEtsTraderColl)
	COM_INTERFACE_ENTRY(IEtsTraderColl)
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
		IEtsTraderCollImpl::Clear();
	}

public:
	IEtsTraderAtomPtr AddNew(long lKey, const _bstr_t& bsName, CComObject<CEtsTraderAtom>** pAtom = NULL);

public:

	STDMETHOD(Add)(LONG Key, BSTR SortKey, IEtsTraderAtom* Value, IEtsTraderAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsTraderColl), CEtsTraderColl)

#endif //__ETSTRADERCOLL_H__
