// VolaControl.h : Declaration of the CVolaControl
#ifndef __VOLACONTROL_H__
#define __VOLACONTROL_H__

#pragma once
#include "resource.h"       // main symbols

#include "EtsGeneral.h"

// CVolaControl

class ATL_NO_VTABLE CVolaControl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVolaControl, &CLSID_VolaControl>,
	public ISupportErrorInfoImpl<&IID_IVolaControl>,
	public IDispatchImpl<IVolaControl, &IID_IVolaControl, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CVolaControl()
		: m_dUnderlyingPrice(0.)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VOLACONTROL)

BEGIN_COM_MAP(CVolaControl)
	COM_INTERFACE_ENTRY(IVolaControl)
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
		CleanUp();
	}

public:
	IVSSymbolVolatilityPtr			m_spSymbolVola;
	DOUBLE							m_dUnderlyingPrice;

public:
	STDMETHOD(Init)(BSTR UnderlyingSymbol, EtsContractTypeEnum ContractType, IVolatilitySource* pVolaSrc);
	STDMETHOD(get_OptionVola)(DATE Expiry, DOUBLE Strike, DOUBLE* pVal);
	STDMETHOD(put_OptionVola)(DATE Expiry, DOUBLE Strike, DOUBLE newVal);
	STDMETHOD(get_OptionTargetVola)(DATE Expiry, DOUBLE Strike, DOUBLE* pVal);
	STDMETHOD(ShiftExpiryVola)(DATE Expiry, DOUBLE ShiftValue);
	STDMETHOD(SetExpiryVola)(DATE Expiry, DOUBLE Value);
	STDMETHOD(SetExpiryVolaByExpiry)(LPSAFEARRAY* saData);
	STDMETHOD(SetExpiryVolaAll)(DOUBLE Value);
	STDMETHOD(CleanUp)(void);
	STDMETHOD(SetExpiryAndStrikeVolaAll)(LPSAFEARRAY* saData);

	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, UnderlyingPrice, m_dUnderlyingPrice);

	IMPLEMENT_SIMPLEREADONLY_PROPERTY(VARIANT_BOOL,	IsInitialized, (m_spSymbolVola != NULL ? VARIANT_TRUE : VARIANT_FALSE))
};

OBJECT_ENTRY_AUTO(__uuidof(VolaControl), CVolaControl)

#endif //__VOLACONTROL_H__
