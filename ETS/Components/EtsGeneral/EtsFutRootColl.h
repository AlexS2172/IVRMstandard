// EtsFutRootColl.h : Declaration of the CEtsFutRootColl
#ifndef __ETSFUTROOTCOLL_H__
#define __ETSFUTROOTCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsFutRootAtom.h"

_COM_SMARTPTR_TYPEDEF(IEtsFutRootColl, IID_IEtsFutRootColl);

typedef IDispatchImpl<IEtsFutRootColl, &IID_IEtsFutRootColl, &LIBID_EtsGeneralLib>													IEtsFutRootCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IEtsFutRootCollDispImpl, IEtsFutRootAtom, LONG, LONG, BSTR, _bstr_t >	IEtsFutRootCollImpl;

// CEtsFutRootColl
class ATL_NO_VTABLE CEtsFutRootColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsFutRootColl, &CLSID_EtsFutRootColl>,
	public ISupportErrorInfoImpl<&IID_IEtsFutRootColl>,
	public IEtsFutRootCollImpl
{
public:
	CEtsFutRootColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSFUTROOTCOLL)


BEGIN_COM_MAP(CEtsFutRootColl)
	COM_INTERFACE_ENTRY(IEtsFutRootColl)
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
		IEtsFutRootCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(LONG Key, BSTR SortKey, IEtsFutRootAtom* Value, IEtsFutRootAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsFutRootColl), CEtsFutRootColl)

#endif //__ETSFUTROOTCOLL_H__
