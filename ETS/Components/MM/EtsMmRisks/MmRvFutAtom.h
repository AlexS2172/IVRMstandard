// MmRvFutAtom.h : Declaration of the CMmRvFutAtom
#ifndef __MMRVFUTATOM_H__
#define __MMRVFUTATOM_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsMmRisks.h"
#include "MmRvPrice.h"

_COM_SMARTPTR_TYPEDEF(IMmRvFutAtom, IID_IMmRvFutAtom);
_COM_SMARTPTR_TYPEDEF(IMmRvUndAtom, IID_IMmRvUndAtom);

/////////////////////////////////////////////////////////////////////////////
//
struct __MmRvFutAtom
{
	// core info
	LONG							m_nID;
	DATE							m_dtMaturity;

	_bstr_t							m_bstrSymbol;
	_bstr_t							m_bstrFutRootSymbol;
	_bstr_t							m_bstrContractName;
	_bstr_t							m_bstrQuotationUnitName;
	_bstr_t							m_bstrQuotePriceFormat;

	VARIANT_BOOL					m_bIsAmerican;

	IEtsPriceProfileAtomPtr		m_spUndPriceProfile;
	IEtsPriceProfileAtomPtr		m_spOptPriceProfile;
	IMmRvPricePtr				m_spPrice;

	LONG							m_nFutRootID;
	LONG							m_nUndID;

	VARIANT_BOOL					m_bCalcGreeks;

	//DOUBLE							m_dPriceBid;
	//DOUBLE							m_dPriceAsk;
	//DOUBLE							m_dPriceLast;
	//DOUBLE							m_dPriceClose;

	//DOUBLE							m_dNetChange;
	LONG							m_nOptLotSize;
	LONG							m_nFutLotSize;

	EtsReplacePriceStatusEnum	m_enReplacePriceStatus;
	IMmRvUndAtomPtr				m_spUnd;
	double						m_dK;
	double						m_dKEq;
    DOUBLE                      m_dUndMidPrice;
	VARIANT_BOOL				m_bMultOptDltEq;
	double						m_dRatio;
	double						m_dBasis;

	__MmRvFutAtom() :
	m_nID(0L),
		m_dtMaturity(0.),

		m_bIsAmerican(VARIANT_FALSE),

		m_nFutRootID(0L),
		m_nUndID(0L),

		m_bCalcGreeks(VARIANT_FALSE),

		//m_dPriceBid(BAD_DOUBLE_VALUE),
		//m_dPriceAsk(BAD_DOUBLE_VALUE),
		//m_dPriceLast(BAD_DOUBLE_VALUE),
		//m_dPriceClose(BAD_DOUBLE_VALUE),
		//m_dNetChange(BAD_DOUBLE_VALUE),

		m_nOptLotSize(0L),
		m_nFutLotSize(0L),
		m_enReplacePriceStatus(enRpsNone),
		m_dK(1.),
		m_dUndMidPrice(BAD_DOUBLE_VALUE),
		m_dKEq(1.),
		m_bMultOptDltEq(VARIANT_FALSE),
		m_dBasis(BAD_DOUBLE_VALUE),
		m_dRatio(BAD_DOUBLE_VALUE)
	{
	}
};

/////////////////////////////////////////////////////////////////////////////
//
class ATL_NO_VTABLE CMmRvFutAtom : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMmRvFutAtom, &CLSID_MmRvFutAtom>,
	public ISupportErrorInfoImpl<&IID_IMmRvFutAtom>,
	public IDispatchImpl<IMmRvFutAtom, &IID_IMmRvFutAtom, &LIBID_EtsMmRisksLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __MmRvFutAtom
{
public:
	CMmRvFutAtom():m_pPrice(NULL)
	{
		m_pUnkMarshaler = NULL;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MMRVFUTATOM)

	DECLARE_NOT_AGGREGATABLE(CMmRvFutAtom)

	BEGIN_COM_MAP(CMmRvFutAtom)
		COM_INTERFACE_ENTRY(IMmRvFutAtom)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		try
		{
			_CHK(CComObject<CMmRvPrice>::CreateInstance(&m_pPrice), _T("Fail to create Price Info."));
			m_spPrice.Attach(m_pPrice, TRUE);

			_CHK(CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkMarshaler.p));
		}
		catch(const _com_error& e)
		{
			return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvFutAtom, e.Error());
		}
		return S_OK;
	}

	void FinalRelease() 
	{
		m_spUndPriceProfile = NULL;
		m_spOptPriceProfile = NULL;

		m_pUnkMarshaler.Release();
	}

	CComObject<CMmRvPrice>*		m_pPrice;

private:

	CComPtr<IUnknown>			m_pUnkMarshaler;

public:

	// core info
	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
		IMPLEMENT_BSTRT_PROPERTY(Symbol, m_bstrSymbol)
		IMPLEMENT_BSTRT_PROPERTY(QuotationUnitName, m_bstrQuotationUnitName)
		IMPLEMENT_BSTRT_PROPERTY(QuotePriceFormat, m_bstrQuotePriceFormat)
		IMPLEMENT_SIMPLE_PROPERTY(DATE, Maturity, m_dtMaturity)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsAmerican, m_bIsAmerican)
		IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, UndPriceProfile, m_spUndPriceProfile)
		IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, OptPriceProfile, m_spOptPriceProfile)

		IMPLEMENT_SIMPLE_PROPERTY(LONG, FutRootID, m_nFutRootID)
		IMPLEMENT_BSTRT_PROPERTY(FutRootSymbol, m_bstrFutRootSymbol)

		IMPLEMENT_SIMPLE_PROPERTY(LONG, UndID, m_nUndID)

		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, CalcGreeks, m_bCalcGreeks)

		//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceBid,   m_dPriceBid)
		//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceAsk,   m_dPriceAsk)
		//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceLast,  m_dPriceLast)
		//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceClose, m_dPriceClose)
		//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetChange,  m_dNetChange)
		IMPLEMENT_OBJECTREADONLY_PROPERTY(IMmRvPrice*, Price,   m_spPrice);

		IMPLEMENT_SIMPLE_PROPERTY(LONG, OptLotSize,   m_nOptLotSize)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, FutLotSize,   m_nFutLotSize)

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, K,   m_dK)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, KEq,   m_dKEq)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, MultOptDltEq,   m_bMultOptDltEq)

		IMPLEMENT_BSTRT_PROPERTY(ContractName, m_bstrContractName)
		IMPLEMENT_SIMPLE_PROPERTY(EtsReplacePriceStatusEnum, ReplacePriceStatus, m_enReplacePriceStatus)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, FutureBasis, m_dBasis)
		STDMETHOD(get_Underlying)(IMmRvUndAtom**);
		STDMETHOD(putref_Underlying)(IMmRvUndAtom*);
		STDMETHOD(GetFuturePrice)(	DOUBLE dTolerance, EtsPriceRoundingRuleEnum enPriceRound,EtsReplacePriceStatusEnum * penPriceStatus, VARIANT_BOOL *bFutureUsed,  DOUBLE *pPrice);

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Ratio, m_dRatio)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Basis, m_dBasis)

};

OBJECT_ENTRY_AUTO(__uuidof(MmRvFutAtom), CMmRvFutAtom)

#endif //__MMRVFUTATOM_H__
//// MmRvFutAtom.h : Declaration of the CMmRvFutAtom
//#ifndef __MMRVFUTATOM_H__
//#define __MMRVFUTATOM_H__
//#pragma once
//
//#include "resource.h"       // main symbols
//#include "EtsMmRisks.h"
//
//_COM_SMARTPTR_TYPEDEF(IMmRvFutAtom, IID_IMmRvFutAtom);
//
///////////////////////////////////////////////////////////////////////////////
////
//struct __MmRvFutAtom
//{
//	// core info
//	LONG						m_nID;
//	CComBSTR					m_bstrSymbol;
//	DATE						m_dtMaturity;
//
//	VARIANT_BOOL				m_bIsAmerican;
//	LONG						m_nExpCalendarID;
//
//	IEtsPriceProfileAtomPtr		m_spUndPriceProfile;
//	IEtsPriceProfileAtomPtr		m_spOptPriceProfile;
//
//	LONG						m_nFutRootID;
//	CComBSTR					m_bstrFutRootSymbol;
//	LONG						m_nUndID;
//	
//	VARIANT_BOOL				m_bCalcGreeks;
//
//	DOUBLE						m_dPriceBid;
//	DOUBLE						m_dPriceAsk;
//	DOUBLE						m_dPriceLast;
//	DOUBLE						m_dPriceClose;
//		
//	DOUBLE						m_dNetChange;
//	LONG						m_nOptLotSize;
//	LONG						m_nFutLotSize;
//
//	CComBSTR					m_bstrContractName;
//	EtsReplacePriceStatusEnum	m_enReplacePriceStatus;
//
//
//	__MmRvFutAtom() :
//		m_nID(0L),
//		m_dtMaturity(0.),
//		
//		m_bIsAmerican(VARIANT_FALSE),
//		m_nExpCalendarID(0L),
//
//		m_nFutRootID(0L),
//		m_nUndID(0L),
//
//		m_bCalcGreeks(VARIANT_FALSE),
//
//		m_dPriceBid(BAD_DOUBLE_VALUE),
//		m_dPriceAsk(BAD_DOUBLE_VALUE),
//		m_dPriceLast(BAD_DOUBLE_VALUE),
//		m_dPriceClose(BAD_DOUBLE_VALUE),
//		m_dNetChange(BAD_DOUBLE_VALUE),
//			
//		m_nOptLotSize(0L),
//		m_nFutLotSize(0L),
//		m_enReplacePriceStatus(enRpsNone)
//	{
//	}
//};
//
///////////////////////////////////////////////////////////////////////////////
////
//class ATL_NO_VTABLE CMmRvFutAtom : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CMmRvFutAtom, &CLSID_MmRvFutAtom>,
//	public ISupportErrorInfoImpl<&IID_IMmRvFutAtom>,
//	public IDispatchImpl<IMmRvFutAtom, &IID_IMmRvFutAtom, &LIBID_EtsMmRisksLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
//	public __MmRvFutAtom
//{
//public:
//	CMmRvFutAtom()
//	{
//	}
//
//DECLARE_REGISTRY_RESOURCEID(IDR_MMRVFUTATOM)
//
//DECLARE_NOT_AGGREGATABLE(CMmRvFutAtom)
//
//BEGIN_COM_MAP(CMmRvFutAtom)
//	COM_INTERFACE_ENTRY(IMmRvFutAtom)
//	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(ISupportErrorInfo)
//END_COM_MAP()
//
//	DECLARE_PROTECT_FINAL_CONSTRUCT()
//
//	HRESULT FinalConstruct()
//	{
//		return S_OK;
//	}
//	
//	void FinalRelease() 
//	{
//		m_spUndPriceProfile = NULL;
//		m_spOptPriceProfile = NULL;
//	}
//
//public:
//	
//	// core info
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
//	IMPLEMENT_BSTR_PROPERTY(Symbol, m_bstrSymbol)
//	IMPLEMENT_SIMPLE_PROPERTY(DATE, Maturity, m_dtMaturity)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsAmerican, m_bIsAmerican)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, ExpCalendarID, m_nExpCalendarID)
//	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, UndPriceProfile, m_spUndPriceProfile)
//	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, OptPriceProfile, m_spOptPriceProfile)
//
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, FutRootID, m_nFutRootID)
//	IMPLEMENT_BSTR_PROPERTY(FutRootSymbol, m_bstrFutRootSymbol)
//
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, UndID, m_nUndID)
//
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, CalcGreeks, m_bCalcGreeks)
//
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceBid,   m_dPriceBid)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceAsk,   m_dPriceAsk)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceLast,  m_dPriceLast)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceClose, m_dPriceClose)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetChange,  m_dNetChange)
//
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, OptLotSize,   m_nOptLotSize)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, FutLotSize,   m_nFutLotSize)
//
//	IMPLEMENT_BSTR_PROPERTY(ContractName, m_bstrContractName)
//	IMPLEMENT_SIMPLE_PROPERTY(EtsReplacePriceStatusEnum, ReplacePriceStatus, m_enReplacePriceStatus)
//};
//
//OBJECT_ENTRY_AUTO(__uuidof(MmRvFutAtom), CMmRvFutAtom)
//
//#endif //__MMRVFUTATOM_H__