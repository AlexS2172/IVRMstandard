// EtsFutColl.h : Declaration of the CEtsFutColl
// EtsFutColl.h : Declaration of the CEtsFutColl
#ifndef __ETSFUTCOLL_H__
#define __ETSFUTCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsFutAtom.h"

_COM_SMARTPTR_TYPEDEF(IEtsFutColl, IID_IEtsFutColl);

typedef IDispatchImpl<IEtsFutColl, &IID_IEtsFutColl, &LIBID_EtsGeneralLib>										IEtsFutCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IEtsFutCollDispImpl, IEtsFutAtom, LONG, LONG, BSTR, _bstr_t >	IEtsFutCollImpl;

// CEtsFutColl
class ATL_NO_VTABLE CEtsFutColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsFutColl, &CLSID_EtsFutColl>,
	public ISupportErrorInfoImpl<&IID_IEtsFutColl>,
	public IEtsFutCollImpl
{
public:
	CEtsFutColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSFUTCOLL)

BEGIN_COM_MAP(CEtsFutColl)
	COM_INTERFACE_ENTRY(IEtsFutColl)
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
		IEtsFutCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(LONG Key, BSTR SortKey, IEtsFutAtom* Value, IEtsFutAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsFutColl), CEtsFutColl)

#endif //__ETSFUTCOLL_H__
