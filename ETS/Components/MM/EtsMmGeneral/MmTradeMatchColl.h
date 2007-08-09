// MmTradeMatchColl.h : Declaration of the CMmTradeMatchColl

#pragma once
#include "resource.h"       // main symbols

#include "EtsMmGeneral.h"


// CMmTradeMatchColl

_COM_SMARTPTR_TYPEDEF(IMmTradeMatchColl, IID_IMmTradeMatchColl);

//class CMmTradeMatchColl;
typedef IDispatchImpl<IMmTradeMatchColl, &IID_IMmTradeMatchColl, &LIBID_EtsMmGeneralLib>								IMmTradeMatchCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IMmTradeMatchCollDispImpl, IMmTradeMatchAtom, LONG, LONG, DATE, DATE>	IMmTradeMatchCollImpl;

class ATL_NO_VTABLE CMmTradeMatchColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMmTradeMatchColl, &CLSID_MmTradeMatchColl>,
	public ISupportErrorInfo,
	public IMmTradeMatchCollImpl
	//public IDispatchImpl<IMmTradeMatchColl, &IID_IMmTradeMatchColl, &LIBID_EtsMmGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMmTradeMatchColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MMTRADEMATCHCOLL)

DECLARE_ONLY_AGGREGATABLE(CMmTradeMatchColl)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CMmTradeMatchColl)
	COM_INTERFACE_ENTRY(IMmTradeMatchColl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
		IMmTradeMatchCollImpl::Clear();
	}

public:
	STDMETHOD(Add)(LONG Key, DATE SortKey, IMmTradeMatchAtom* Value, IMmTradeMatchAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(MmTradeMatchColl), CMmTradeMatchColl)
