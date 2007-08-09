// EtsFutAtom.h : Declaration of the CEtsFutAtom
#ifndef __ETSFUTATOM_H_
#define __ETSFUTATOM_H_
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsPriceProfileAtom.h"

_COM_SMARTPTR_TYPEDEF(IEtsFutAtom, IID_IEtsFutAtom);

struct __EtsFutAtom
{
	LONG					m_nID;
	CComBSTR				m_bstrSymbol;
	CComBSTR				m_bstrContractName;
	LONG					m_nFutRootID;
	IEtsPriceProfileAtomPtr	m_spUndPriceProfile;
	IEtsPriceProfileAtomPtr	m_spOptPriceProfile;
	DATE					m_dtMaturityDate;
	VARIANT_BOOL			m_bIsAmerican;
	VARIANT_BOOL			m_bIsActive;
	DOUBLE					m_dPriceClose;
	VARIANT_BOOL			m_bHaveOptions;

	VARIANT_BOOL			m_bShowInFutureContractEq;
	DOUBLE					m_dTickSize;
	DOUBLE					m_dTickValue;
	DOUBLE					m_dPriceQuotationUnit;
	DOUBLE					m_dQuoteFormat;
	double					m_dK;
	double					m_dKEq;
    VARIANT_BOOL            m_bMultOptDltEq;
	DOUBLE					m_dBasis;
	VARIANT_BOOL			m_bUseInCalc;
	DOUBLE					m_dActiveFutureRatio;

	__EtsFutAtom()
		: m_nID(0L)
		, m_nFutRootID(0L)
		, m_dtMaturityDate(0.)
		, m_dPriceClose(0.)
		, m_bHaveOptions(VARIANT_FALSE)
		, m_bIsAmerican(VARIANT_FALSE)
		, m_bIsActive(VARIANT_FALSE)
		, m_bShowInFutureContractEq(VARIANT_FALSE)
	    , m_dTickSize(BAD_DOUBLE_VALUE)
		, m_dTickValue(BAD_DOUBLE_VALUE)
		, m_dPriceQuotationUnit(BAD_DOUBLE_VALUE)
		, m_dQuoteFormat(BAD_DOUBLE_VALUE)
		, m_dBasis(0)
		, m_bUseInCalc( VARIANT_FALSE )
		,m_dActiveFutureRatio(BAD_DOUBLE_VALUE)
		,m_dK(1.)
		,m_dKEq(1.)
		,m_bMultOptDltEq(VARIANT_FALSE)
	{
	}
};

// CEtsFutAtom

class ATL_NO_VTABLE CEtsFutAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsFutAtom, &CLSID_EtsFutAtom>,
	public ISupportErrorInfoImpl<&IID_IEtsFutAtom>,
	public IDispatchImpl<IEtsFutAtom, &IID_IEtsFutAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __EtsFutAtom
{
public:
	CEtsFutAtom()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSFUTATOM)


BEGIN_COM_MAP(CEtsFutAtom)
	COM_INTERFACE_ENTRY(IEtsFutAtom)
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
		m_spUndPriceProfile = NULL;
		m_spOptPriceProfile = NULL;
	}

public:
	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
	IMPLEMENT_BSTR_PROPERTY(Symbol, m_bstrSymbol)
	IMPLEMENT_BSTR_PROPERTY(ContractName, m_bstrContractName)
	IMPLEMENT_SIMPLE_PROPERTY(LONG, FutRootID, m_nFutRootID)
	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, UndPriceProfile, m_spUndPriceProfile)
	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, OptPriceProfile, m_spOptPriceProfile)
	IMPLEMENT_SIMPLE_PROPERTY(DATE, MaturityDate, m_dtMaturityDate)
	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsAmerican, m_bIsAmerican)
	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsActive, m_bIsActive)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceClose, m_dPriceClose)
	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HaveOptions, m_bHaveOptions)

	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL,	ShowInFutureContractEq, m_bShowInFutureContractEq)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,		TickSize,				m_dTickSize)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,		TickValue,			m_dTickValue)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,		PriceQuotationUnit,		m_dPriceQuotationUnit)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,		QuoteFormat,			m_dQuoteFormat)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, FutureBasis, m_dBasis)
	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, UseInCalc, m_bUseInCalc)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ActiveFutureRatio, m_dActiveFutureRatio)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, K, m_dK)
    IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, KEq, m_dKEq)
	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, MultOptDltEq, m_bMultOptDltEq)
};

OBJECT_ENTRY_AUTO(__uuidof(EtsFutAtom), CEtsFutAtom)

#endif //__ETSFUTATOM_H_