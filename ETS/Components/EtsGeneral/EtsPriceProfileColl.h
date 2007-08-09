// EtsPriceProfileColl.h : Declaration of the CEtsPriceProfileColl
#ifndef __ETSPRICEPROFILECOLL_H__
#define __ETSPRICEPROFILECOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsPriceProfileAtom.h"

typedef IDispatchImpl<IEtsPriceProfileColl, &IID_IEtsPriceProfileColl, &LIBID_EtsGeneralLib>													IEtsPriceProfileCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IEtsPriceProfileCollDispImpl, IEtsPriceProfileAtom, LONG, LONG, BSTR, _bstr_t  >	IEtsPriceProfileCollImpl;

// CEtsPriceProfileColl
_COM_SMARTPTR_TYPEDEF(IEtsPriceProfileColl, IID_IEtsPriceProfileColl);

class ATL_NO_VTABLE CEtsPriceProfileColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsPriceProfileColl, &CLSID_EtsPriceProfileColl>,
	public ISupportErrorInfoImpl<&IID_IEtsPriceProfileColl>,
	public IEtsPriceProfileCollImpl
{
public:
	CEtsPriceProfileColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSPRICEPROFILECOLL)


BEGIN_COM_MAP(CEtsPriceProfileColl)
	COM_INTERFACE_ENTRY(IEtsPriceProfileColl)
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
		IEtsPriceProfileCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(LONG Key, BSTR SortKey, IEtsPriceProfileAtom* Value, IEtsPriceProfileAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsPriceProfileColl), CEtsPriceProfileColl)

#endif //__ETSPRICEPROFILECOLL_H__
