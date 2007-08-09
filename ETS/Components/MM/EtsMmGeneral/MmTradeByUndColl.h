// MmTradeByUndColl.h : Declaration of the CMmTradeByUndColl

#pragma once
#include "resource.h"       // main symbols

#include "EtsMmGeneral.h"
//#include "MmTradeByUndAtom.h"


_COM_SMARTPTR_TYPEDEF(IMmTradeByUndColl, IID_IMmTradeByUndColl);

class CMmTradeByUndColl;
typedef IDispatchImpl<IMmTradeByUndColl, &IID_IMmTradeByUndColl, &LIBID_EtsMmGeneralLib>						IMmTradeByUndCollDispImpl;
typedef ICollectionOnSTLMapOfInterfacePtrImpl< IMmTradeByUndCollDispImpl, BSTR, IMmTradeInfoColl, _bstr_t >	IMmTradeByUndCollImpl;
// CMmTradeByUndColl

class ATL_NO_VTABLE CMmTradeByUndColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMmTradeByUndColl, &CLSID_MmTradeByUndColl>,
	public ISupportErrorInfoImpl<&IID_IMmTradeByUndColl>,
	public IMmTradeByUndCollImpl
{
public:
	CMmTradeByUndColl()//:m_bRequiresSave(true)
	{
	}


DECLARE_REGISTRY_RESOURCEID(IDR_MMTRADEBYUNDCOLL)
DECLARE_ONLY_AGGREGATABLE(CMmTradeByUndColl)
DECLARE_GET_CONTROLLING_UNKNOWN()


BEGIN_COM_MAP(CMmTradeByUndColl)
	COM_INTERFACE_ENTRY(IMmTradeByUndColl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)

END_COM_MAP()

BEGIN_PROP_MAP(CMmTradeByUndColl)
END_PROP_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
		IMmTradeByUndCollImpl::Clear();
	}


public:

	STDMETHOD(Add)(BSTR Key, IMmTradeInfoColl* Value, IMmTradeInfoColl** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(MmTradeByUndColl), CMmTradeByUndColl)
