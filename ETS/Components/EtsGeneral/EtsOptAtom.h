// EtsOptAtom.h : Declaration of the CEtsOptAtom
#ifndef __ETSOPTATOM_H__
#define __ETSOPTATOM_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"

_COM_SMARTPTR_TYPEDEF(IEtsOptAtom, IID_IEtsOptAtom);

struct __EtsOptAtom
{
	LONG				m_nID;
	CComBSTR			m_bstrSymbol;
	LONG				m_nRootID;	
	EtsOptionTypeEnum	m_enOptType;
	DATE				m_dtExpiry;
	DOUBLE				m_dStrike;
	CComBSTR			m_bstrSeries;
	DOUBLE				m_dPriceClose;
	DOUBLE				m_dPriceTheoClose;
	CComBSTR			m_bstrImportID;
	LONG				m_IsFlex;

	DATE				m_dtExpiryOV;
	DATE				m_dtTradingClose;

	__EtsOptAtom()
		: m_nID(0L), m_nRootID(0L), m_enOptType(enOtPut),
		m_dtExpiry(0.), m_dStrike(0.), m_dPriceClose(0.), m_dPriceTheoClose(0.), m_IsFlex(0),
		m_dtExpiryOV(0), m_dtTradingClose(0)
	{
	}
};

// CEtsOptAtom

class ATL_NO_VTABLE CEtsOptAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsOptAtom, &CLSID_EtsOptAtom>,
	public ISupportErrorInfoImpl<&IID_IEtsOptAtom>,
	public IDispatchImpl<IEtsOptAtom, &IID_IEtsOptAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __EtsOptAtom
{
public:
	CEtsOptAtom()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSOPTATOM)


BEGIN_COM_MAP(CEtsOptAtom)
	COM_INTERFACE_ENTRY(IEtsOptAtom)
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

	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
	IMPLEMENT_BSTR_PROPERTY(Symbol, m_bstrSymbol)
	IMPLEMENT_SIMPLE_PROPERTY(LONG, RootID, m_nRootID)
	IMPLEMENT_SIMPLE_PROPERTY(EtsOptionTypeEnum, OptType, m_enOptType)
	IMPLEMENT_SIMPLE_PROPERTY(DATE, Expiry, m_dtExpiry)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Strike, m_dStrike)
	IMPLEMENT_BSTR_PROPERTY(Series, m_bstrSeries)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceClose, m_dPriceClose)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceTheoClose, m_dPriceTheoClose)
	IMPLEMENT_BSTR_PROPERTY(ImportID, m_bstrImportID)
	IMPLEMENT_SIMPLE_PROPERTY(LONG, Flex, m_IsFlex)

	IMPLEMENT_SIMPLE_PROPERTY(DATE, ExpiryOV, m_dtExpiryOV)
	IMPLEMENT_SIMPLE_PROPERTY(DATE, TradingClose, m_dtTradingClose)

	STDMETHOD(CopyTo)(IEtsOptAtom* pDest);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsOptAtom), CEtsOptAtom)

#endif //__ETSOPTATOM_H__
