// EtsMmFilterAtomColl.h : Declaration of the CEtsMmFilterAtomColl

#pragma once
#include "resource.h"       // main symbols

#include "EtsGeneral.h"

_COM_SMARTPTR_TYPEDEF(IEtsMmFilterAtomColl, IID_IEtsMmFilterAtomColl);

typedef IDispatchImpl<IEtsMmFilterAtomColl, &IID_IEtsMmFilterAtomColl, &LIBID_EtsGeneralLib> IEtsMmFilterAtomCollDispImpl;
typedef ICollectionOnSTLMapOfInterfacePtrImpl<IEtsMmFilterAtomCollDispImpl, BSTR, IEtsMmFilterAtom, _bstr_t >	IEtsMmFilterAtomCollImpl;



// CEtsMmFilterAtomColl

class ATL_NO_VTABLE CEtsMmFilterAtomColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsMmFilterAtomColl, &CLSID_EtsMmFilterAtomColl>,
	public ISupportErrorInfoImpl<&IID_IEtsMmFilterAtomColl>,
	public IEtsMmFilterAtomCollImpl
{
public:
	CEtsMmFilterAtomColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSMMFILTERATOMCOLL)


BEGIN_COM_MAP(CEtsMmFilterAtomColl)
	COM_INTERFACE_ENTRY(IEtsMmFilterAtomColl)
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
	}


public:

	STDMETHOD(Add)(BSTR Key, IEtsMmFilterAtom* Value, IEtsMmFilterAtom** pRetVal);

};

OBJECT_ENTRY_AUTO(__uuidof(EtsMmFilterAtomColl), CEtsMmFilterAtomColl)
