// EtsIndexDivAtom.h : Declaration of the CEtsIndexDivAtom

#pragma once
#include "resource.h"       // main symbols

#include "EtsGeneral.h"
#include "EtsDivAtom.h"
#include "EtsDivColl.h"

struct _IndexDivAtomBaseTypes
{
	LONG				m_nDivFreq;
	DATE				m_dtDivDate;
	DOUBLE				m_dDivAmt;
	LONG				m_nDivFreqCust;
	DATE				m_dtDivDateCust;
	DOUBLE				m_dDivAmtCust;
	EtsDivTypeEnum		m_enDivType;
	
	_IndexDivAtomBaseTypes():m_nDivFreq(0),
							 m_dtDivDate(0.0),
							 m_dDivAmt(0.0),
							 m_nDivFreqCust(0),
							 m_dtDivDateCust(0.0),
							 m_dDivAmtCust(0.0),
							 m_enDivType(enDivMarket)
	{
	}
};

struct _IndexDivAtom: public _IndexDivAtomBaseTypes
{
	IEtsDivCollPtr m_spCustomDivs;
};

// CEtsIndexDivAtom

_COM_SMARTPTR_TYPEDEF(IEtsIndexDivAtom, IID_IEtsIndexDivAtom);

class ATL_NO_VTABLE CEtsIndexDivAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsIndexDivAtom, &CLSID_EtsIndexDivAtom>,
	public ISupportErrorInfoImpl<&CLSID_EtsIndexDivAtom>,
	public IDispatchImpl<IEtsIndexDivAtom, &IID_IEtsIndexDivAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public _IndexDivAtom

{
public:
	CEtsIndexDivAtom()
		:m_CacheToday(0L)
		,m_CacheExpiry(0L)
		,m_lCacheDivCount(0L)
	{
	}

	BEGIN_PROP_MAP(CEtsIndexDivAtom)
	END_PROP_MAP()

	

DECLARE_REGISTRY_RESOURCEID(IDR_ETSINDEXDIVATOM)


BEGIN_COM_MAP(CEtsIndexDivAtom)
	COM_INTERFACE_ENTRY(IEtsIndexDivAtom)
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
		m_spCustomDivs = NULL;
	}

private:
	long  m_CacheToday;
	long  m_CacheExpiry;
	long  m_lCacheDivCount;

public:
	IMPLEMENT_SIMPLE_PROPERTY(LONG, DivFreq, m_nDivFreq)
	IMPLEMENT_SIMPLE_PROPERTY(DATE, DivDate,m_dtDivDate)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DivAmt, m_dDivAmt)
	IMPLEMENT_SIMPLE_PROPERTY(LONG, DivFreqCust, m_nDivFreqCust)
	IMPLEMENT_SIMPLE_PROPERTY(DATE, DivDateCust, m_dtDivDateCust)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DivAmtCust, m_dDivAmtCust)
	IMPLEMENT_SIMPLE_PROPERTY(EtsDivTypeEnum, DivType, m_enDivType)
	IMPLEMENT_OBJECT_PROPERTY(IEtsDivColl*, CustomDivs, m_spCustomDivs)
	STDMETHOD(IsValidDivs)(EtsDivTypeEnum enDivType, VARIANT_BOOL* pVal);
	//STDMETHOD(CopyToWithWeight)( DOUBLE dWeight, IEtsIndexDivAtom* pDest , IEtsIndexDivAtom** ppVal);
	STDMETHOD(GetDividends)( LONG nToday,  LONG nExpiry,  LONG nCount, SAFEARRAY ** psaDivAmounts,  SAFEARRAY ** psaDivDates,  LONG* pnCount);
	STDMETHOD(GetNearest)( LONG nToday,  LONG nExpiry,  DOUBLE* pdDivAmount,  DOUBLE* pdDivDate);
	STDMETHOD(GetDividendCount)( LONG nToday,  LONG nExpiry,  LONG* pnCount);
	STDMETHOD(Clear)(void);
	STDMETHOD(Clone)(IEtsIndexDivAtom** pDestination);
  STDMETHOD(ResetInternalCache)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsIndexDivAtom), CEtsIndexDivAtom)
