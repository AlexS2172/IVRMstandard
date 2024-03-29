// MmRpGreeksByMonthAtom.h : Declaration of the CMmRpGreeksByMonthAtom
#ifndef __MM_RP_GREEKS_BY_MONTH_ATOM__
#define __MM_RP_GREEKS_BY_MONTH_ATOM__
#pragma once

#include "resource.h"       // main symbols
#include "EtsMmReports.h"

_COM_SMARTPTR_TYPEDEF(IMmRpGreeksByMonthAtom, IID_IMmRpGreeksByMonthAtom);

struct __MmRpGreeksByMonthAtom
{
	LONG					m_nID;
	DOUBLE					m_dCallMarketValue;
	DOUBLE					m_dCallPoP;
	DOUBLE					m_dNetMarketValue;
	DOUBLE					m_dNetPoP;
	DOUBLE					m_dOptionsDelta;
	DOUBLE					m_dOptionsDeltaInShares;
	DOUBLE					m_dPutMarketValue;
	DOUBLE					m_dPutPoP;
	CComBSTR				m_bstrSymbol;
	DOUBLE					m_dTotalGamma;
	DOUBLE					m_dTotalGammaInShares;
	DOUBLE					m_dTotalRho;
	DOUBLE					m_dTotalVega;
	DOUBLE					m_dTotalTheta;
	DOUBLE					m_dTotalWeightedVega;
	EtsContractTypeEnum		m_enUndType;
	CComBSTR				m_bstrSeries;
	DATE					m_dtExpiry;
	DOUBLE					m_dTotalNetGamma;

	__MmRpGreeksByMonthAtom() :
		m_nID(0L), m_dCallMarketValue(0.), m_dCallPoP(0.),
        m_dNetMarketValue(0.), m_dNetPoP(0.),
        m_dOptionsDelta(0.), m_dOptionsDeltaInShares(0.),
        m_dPutMarketValue(0.), m_dPutPoP(0.),
		m_dTotalGamma(0.), m_dTotalGammaInShares(0.),
		m_dTotalRho(0.), m_dTotalVega(0.), m_dTotalTheta(0.),
		m_dTotalWeightedVega(0.), m_enUndType(enCtIndex), 
		m_dtExpiry(0.), m_dTotalNetGamma(0.)
	{
	}
};

// CMmRpGreeksByMonthAtom

class ATL_NO_VTABLE CMmRpGreeksByMonthAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMmRpGreeksByMonthAtom, &CLSID_MmRpGreeksByMonthAtom>,
	public ISupportErrorInfoImpl<&IID_IMmRpGreeksByMonthAtom>,
	public IDispatchImpl<IMmRpGreeksByMonthAtom, &IID_IMmRpGreeksByMonthAtom, &LIBID_EtsMmReportsLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __MmRpGreeksByMonthAtom
{
public:
	CMmRpGreeksByMonthAtom()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MMRPGREEKSBYMONTHATOM)

DECLARE_NOT_AGGREGATABLE(CMmRpGreeksByMonthAtom)

BEGIN_COM_MAP(CMmRpGreeksByMonthAtom)
	COM_INTERFACE_ENTRY(IMmRpGreeksByMonthAtom)
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

	IMPLEMENT_SIMPLE_PROPERTY(LONG,					ID,						m_nID)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				CallMarketValue,		m_dCallMarketValue)
    IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				CallPoP,				m_dCallPoP)
    IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				NetMarketValue,			m_dNetMarketValue)
    IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				NetPoP,					m_dNetPoP)
    IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				OptionsDelta,			m_dOptionsDelta)
    IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				OptionsDeltaInShares,	m_dOptionsDeltaInShares)
    IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				PutMarketValue,			m_dPutMarketValue)
    IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				PutPoP,					m_dPutPoP)
    IMPLEMENT_BSTR_PROPERTY(Symbol,		m_bstrSymbol)
    IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				TotalGamma,				m_dTotalGamma)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				TotalGammaInShares,		m_dTotalGammaInShares)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				TotalRho,				m_dTotalRho)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				TotalVega,				m_dTotalVega)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				TotalTheta,				m_dTotalTheta)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				TotalWeightedVega,		m_dTotalWeightedVega)
	IMPLEMENT_SIMPLE_PROPERTY(EtsContractTypeEnum,	UndType,				m_enUndType)
	IMPLEMENT_BSTR_PROPERTY(Series,		m_bstrSeries)
	IMPLEMENT_SIMPLE_PROPERTY(DATE,					Expiry,					m_dtExpiry)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,				TotalNetGamma,			m_dTotalNetGamma)

};

OBJECT_ENTRY_AUTO(__uuidof(MmRpGreeksByMonthAtom), CMmRpGreeksByMonthAtom)

#endif //__MM_RP_GREEKS_BY_MONTH_ATOM__