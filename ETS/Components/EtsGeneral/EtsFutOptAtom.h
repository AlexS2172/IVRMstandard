// EtsFutOptAtom.h : Declaration of the CEtsFutOptAtom
#ifndef __ETSFUTOPTATOM_H__
#define __ETSFUTOPTATOM_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"

_COM_SMARTPTR_TYPEDEF(IEtsFutOptAtom, IID_IEtsFutOptAtom);

struct __EtsFutOptAtom
{
	LONG				m_nID;
	CComBSTR			m_bstrSymbol;
	LONG				m_nFutID;	
	EtsOptionTypeEnum	m_enOptType;
	DATE				m_dtExpiry;
	DOUBLE				m_dStrike;
	CComBSTR			m_bstrSeries;
	DOUBLE				m_dPriceClose;
	DOUBLE				m_dPriceTheoClose;
	CComBSTR			m_bstrImportID;

	__EtsFutOptAtom()
		: m_nID(0L), m_nFutID(0L), m_enOptType(enOtPut),
		m_dtExpiry(0.), m_dStrike(0.), m_dPriceClose(0.), m_dPriceTheoClose(0.)
	{
	}
};

// CEtsFutOptAtom

class ATL_NO_VTABLE CEtsFutOptAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsFutOptAtom, &CLSID_EtsFutOptAtom>,
	public ISupportErrorInfoImpl<&IID_IEtsFutOptAtom>,
	public IDispatchImpl<IEtsFutOptAtom, &IID_IEtsFutOptAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __EtsFutOptAtom
{
public:
	CEtsFutOptAtom()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSFUTOPTATOM)


BEGIN_COM_MAP(CEtsFutOptAtom)
	COM_INTERFACE_ENTRY(IEtsFutOptAtom)
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
	IMPLEMENT_SIMPLE_PROPERTY(LONG, FutID, m_nFutID)
	IMPLEMENT_SIMPLE_PROPERTY(EtsOptionTypeEnum, OptType, m_enOptType)
	IMPLEMENT_SIMPLE_PROPERTY(DATE, Expiry, m_dtExpiry)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Strike, m_dStrike)
	IMPLEMENT_BSTR_PROPERTY(Series, m_bstrSeries)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceClose, m_dPriceClose)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceTheoClose, m_dPriceTheoClose)
	IMPLEMENT_BSTR_PROPERTY(ImportID, m_bstrImportID)

	STDMETHOD(CopyTo)(IEtsFutOptAtom* pDest);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsFutOptAtom), CEtsFutOptAtom)

#endif //__ETSFUTOPTATOM_H__
