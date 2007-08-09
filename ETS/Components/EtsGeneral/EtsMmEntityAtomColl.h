// EtsMmEntityAtomColl.h : Declaration of the CEtsMmEntityAtomColl

#pragma once
#include "resource.h"       // main symbols

#include "EtsGeneral.h"


// CEtsMmEntityAtomColl
_COM_SMARTPTR_TYPEDEF(IEtsMmEntityAtomColl, IID_IEtsMmEntityAtomColl);

typedef IDispatchImpl<IEtsMmEntityAtomColl, &IID_IEtsMmEntityAtomColl, &LIBID_EtsGeneralLib> IEtsMmEntityAtomCollDispImpl;
typedef ICollectionOnSTLMapOfInterfacePtrImpl<IEtsMmEntityAtomCollDispImpl, BSTR, IEtsMmEntityAtom, _bstr_t >	IEtsMmEntityAtomCollImpl;



class ATL_NO_VTABLE CEtsMmEntityAtomColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsMmEntityAtomColl, &CLSID_EtsMmEntityAtomColl>,
	public ISupportErrorInfoImpl<&IID_IEtsMmEntityAtomColl>,
	public IEtsMmEntityAtomCollImpl
{
public:
	CEtsMmEntityAtomColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSMMENTITYATOMCOLL)


BEGIN_COM_MAP(CEtsMmEntityAtomColl)
	COM_INTERFACE_ENTRY(IEtsMmEntityAtomColl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

	STDMETHOD(Add)(BSTR Key, IEtsMmEntityAtom* Value, IEtsMmEntityAtom** pRetVal);

};

OBJECT_ENTRY_AUTO(__uuidof(EtsMmEntityAtomColl), CEtsMmEntityAtomColl)
