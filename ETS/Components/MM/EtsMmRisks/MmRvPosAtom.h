// MmRvPosAtom.h : Declaration of the CMmRvPosAtom
#ifndef __MMRVPOSATOM_H__
#define __MMRVPOSATOM_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsMmRisks.h"
#include "MmRvSynthGreeksColl.h"
#include "MmRvFutAtom.h"
#include "RvMmQuoteAtom.h"

_COM_SMARTPTR_TYPEDEF(IMmRvUndColl, IID_IMmRvUndColl); 
_COM_SMARTPTR_TYPEDEF(IMmRvPosAtom, IID_IMmRvPosAtom);

class CMmRvAggData;

/////////////////////////////////////////////////////////////////////////////
//
struct __MmRvPosAtom
{
	// aggregations
	CMmRvAggData*	AggregationsPtr_[3];		// pointers to aggregations where this position resides (underlying, future, expiry )
														// this is a REALLY WEAK pointers, so its doesn't matter of reference counter

	// main info
	LONG						m_nID;
	EtsContractTypeEnum			m_enContractType;
	_bstr_t						m_bstrSymbol;
	_bstr_t						m_bstrSymbolOposit ;

	_bstr_t						m_bsLogEnhansement ;
	// option related info
	EtsOptionTypeEnum			m_enOptType;

	DATE						m_dtExpiry;
	DOUBLE						m_dStrike;
	DOUBLE						m_dRate;
	DOUBLE						m_dVegaWeight;
	//LONG						m_nExpiryMonth;
	LONG						m_nOptionRootID;
	LONG						m_lExternalPosition ;

	// auxilary	info
	VARIANT_BOOL				m_bVisible;
	VARIANT_BOOL				m_bCalcGreeks;

	_bstr_t						m_bstrImportId;

	// position info
	DOUBLE						m_dSuPrice;
	LONG						m_nQty;
	LONG						m_nQtyInShares;

	LONG						m_nQtyLTDBuy;
	LONG						m_nQtyLTDSell;
	DOUBLE						m_dPosLTDBuy;
	DOUBLE						m_dPosLTDSell;

	LONG						m_nQtyDailyPrevDateBuy;
	LONG						m_nQtyDailyPrevDateSell;
	DOUBLE						m_dPosDailyPrevDateBuy;
	DOUBLE						m_dPosDailyPrevDateSell;

	LONG						m_nQtyDailyTodayBuy;
	LONG						m_nQtyDailyTodaySell;
	DOUBLE						m_dPosDailyTodayBuy;
	DOUBLE						m_dPosDailyTodaySell;

	// pnl info
	DOUBLE						m_dPnlMtm;
	DOUBLE						m_dPnlTheo;

	// theo in shares info
	DOUBLE						m_dDeltaInShares;
	DOUBLE						m_dGammaInShares;
	DOUBLE						m_dGammaInSharesPerc;
	DOUBLE						m_dVegaInShares;
	DOUBLE						m_dWtdVega;
	DOUBLE						m_dThetaInShares;
	DOUBLE						m_dRhoInShares;
	DOUBLE						m_dThetaDeltaInShares;
	DOUBLE						m_dThetaGammaInShares;
	DOUBLE						m_dVegaDeltaInShares;
	DOUBLE						m_dVegaGammaInShares;
	DOUBLE						m_dTimeValue;
	DOUBLE						m_dNetGamma;

	DOUBLE						m_dBetaWtdDeltaEq;
	VARIANT_BOOL				m_bBadBetaWtdDeltaEq;


	DOUBLE						m_dNetDelta;
	DOUBLE						m_dDeltaEq;


	// synthetic info
	VARIANT_BOOL				m_bIsSynthetic;
	VARIANT_BOOL				m_bIsSyntheticAggregation;
	IMmRvSynthGreeksCollPtr		m_spSynthGreeks;
	IEtsStrategyAtomPtr		    m_spStrategy;
	LONG						m_nUndID;

	VARIANT_BOOL				m_bBadNetGamma;
	VARIANT_BOOL				m_bBadNetDelta;
	VARIANT_BOOL				m_bBadDeltaEq;

	IRvMmQuoteAtomPtr           m_spQuote;    

	IMmRvFutAtomPtr				m_spFut;
	CComObject<CRvMmQuoteAtom>* m_pQuote;
	IMmRvFutAtomPtr				m_spActiveFuture;
	DOUBLE                      m_dInternalEqDelta;       

	DOUBLE						m_dNetExposure;
	VARIANT_BOOL				m_bBadNetExposure;

	double						m_dUndPriceSave;	// price of underlying used during calculation for this position

	double						m_dKEq;
	VARIANT_BOOL				m_bMultOptDltEq;
	__MmRvPosAtom() :
		m_nID(0L), m_enContractType(enCtNone),
		m_enOptType(enOtCall),
		m_dtExpiry(0.),
		m_dStrike(0.),
		m_dRate(0.),
		m_dVegaWeight(0.),
		//m_nExpiryMonth(0L),
		m_nOptionRootID(0L),
		m_lExternalPosition(0L),
		m_pQuote(NULL),

		m_bVisible(VARIANT_FALSE),
		m_bCalcGreeks(VARIANT_FALSE),

		m_nQty(BAD_LONG_VALUE),
		m_nQtyInShares(BAD_LONG_VALUE),

		m_nQtyLTDBuy(BAD_LONG_VALUE),
		m_nQtyLTDSell(BAD_LONG_VALUE),
		m_dPosLTDBuy(BAD_DOUBLE_VALUE),
		m_dPosLTDSell(BAD_DOUBLE_VALUE),

		m_nQtyDailyPrevDateBuy(BAD_LONG_VALUE),
		m_nQtyDailyPrevDateSell(BAD_LONG_VALUE),
		m_dPosDailyPrevDateBuy(BAD_DOUBLE_VALUE),
		m_dPosDailyPrevDateSell(BAD_DOUBLE_VALUE),

		m_nQtyDailyTodayBuy(BAD_LONG_VALUE),
		m_nQtyDailyTodaySell(BAD_LONG_VALUE),
		m_dPosDailyTodayBuy(BAD_DOUBLE_VALUE),
		m_dPosDailyTodaySell(BAD_DOUBLE_VALUE),
		m_bIsSynthetic(VARIANT_FALSE),
		m_bIsSyntheticAggregation(VARIANT_FALSE),
		m_dInternalEqDelta(BAD_DOUBLE_VALUE),
		m_nUndID(0L),
		m_dSuPrice(BAD_DOUBLE_VALUE),
		m_dUndPriceSave(BAD_DOUBLE_VALUE),
		m_spActiveFuture(NULL),
		m_dKEq(1.),
		m_bMultOptDltEq(VARIANT_FALSE)
	{
		AggregationsPtr_[0] = AggregationsPtr_[1] = AggregationsPtr_[2] = NULL;
		ClearValues();
		ClearValuesInShares();
	}

	void ClearValues()
	{
		if(m_pQuote)
			m_pQuote->ClearValues();
	}

	void ClearValuesInShares()
	{
		m_dNetDelta   = BAD_DOUBLE_VALUE;
		m_dPnlMtm = BAD_DOUBLE_VALUE;
		m_dPnlTheo = BAD_DOUBLE_VALUE;

		m_dDeltaInShares = BAD_DOUBLE_VALUE;
		m_dGammaInShares = BAD_DOUBLE_VALUE;
		m_dGammaInSharesPerc = BAD_DOUBLE_VALUE;
		m_dVegaInShares = BAD_DOUBLE_VALUE;
		m_dWtdVega = BAD_DOUBLE_VALUE;
		m_dThetaInShares = BAD_DOUBLE_VALUE;
		m_dRhoInShares = BAD_DOUBLE_VALUE;
		m_dThetaDeltaInShares = BAD_DOUBLE_VALUE;
		m_dThetaGammaInShares = BAD_DOUBLE_VALUE;
		m_dVegaDeltaInShares = BAD_DOUBLE_VALUE;
		m_dVegaGammaInShares = BAD_DOUBLE_VALUE;
		m_dTimeValue = BAD_DOUBLE_VALUE;

		m_dNetGamma = BAD_DOUBLE_VALUE;
		m_dDeltaEq  = BAD_DOUBLE_VALUE;

		m_bBadNetGamma = VARIANT_FALSE;
		m_bBadNetDelta = VARIANT_FALSE;
		m_bBadDeltaEq  = VARIANT_FALSE;

		m_dBetaWtdDeltaEq = BAD_DOUBLE_VALUE;
		m_bBadBetaWtdDeltaEq = VARIANT_FALSE;
		m_dInternalEqDelta = BAD_DOUBLE_VALUE;
		m_dUndPriceSave = BAD_DOUBLE_VALUE;

		m_dNetExposure = BAD_DOUBLE_VALUE;
		m_bBadNetExposure = VARIANT_FALSE;

	}
};

/////////////////////////////////////////////////////////////////////////////
//
class ATL_NO_VTABLE CMmRvPosAtom : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMmRvPosAtom, &CLSID_MmRvPosAtom>,
	public ISupportErrorInfoImpl<&IID_IMmRvPosAtom>,
	public IDispatchImpl<IMmRvPosAtom, &IID_IMmRvPosAtom, &LIBID_EtsMmRisksLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __MmRvPosAtom
{
public:
	CMmRvPosAtom()
	{
		m_pUnkMarshaler = NULL;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MMRVPOSATOM)

	DECLARE_NOT_AGGREGATABLE(CMmRvPosAtom)

	BEGIN_COM_MAP(CMmRvPosAtom)
		COM_INTERFACE_ENTRY(IMmRvPosAtom)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		CComObject<CRvMmQuoteAtom>::CreateInstance(&m_pQuote);
		m_spQuote.Attach(m_pQuote, TRUE);

		return CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease() 
	{
		m_spSynthGreeks = NULL;
		m_spFut = NULL;
		m_spActiveFuture = NULL;

		m_pQuote  = NULL;
		m_spQuote = NULL;

		m_pUnkMarshaler.Release();
	}

	IMmRvPosAtomPtr MakeCopy(bool bStaticDataOnly, bool bAddNewQuote);
	void SimpleCopyForETS_VME (CComObject<CMmRvPosAtom>*) ;

private:
	void _GetBasketIndexDividends(IIndexAtomPtr spBasketIndex, REGULAR_DIVIDENDS* pDivs, LONG nMaxCount) throw();
	void _GetSyntheticRootBasketDividends(ISynthRootAtomPtr spSynthRoot, REGULAR_DIVIDENDS* pDivs, LONG nMaxCount) throw();
	void _CalcPnlMtm(VARIANT_BOOL bIsPnlLTD, DOUBLE dOptPriceBid, DOUBLE dOptPriceAsk, bool ReplaceWithZero,DATE _dtCalculationDate);
	void _CalcPnlTheo(VARIANT_BOOL bIsPnlLTD,DATE _dtCalculationDate);

private:

	CComPtr<IUnknown>		m_pUnkMarshaler;

public:
	void _CalcOptPositionData(
		IEtsPriceProfileAtomPtr spOptPriceProfile,
		ISynthRootAtomPtr spSynthRoot,
		VARIANT_BOOL bIsPnlLTD,
		VARIANT_BOOL bUseTheoVolatility,
		VARIANT_BOOL bUseTheoVolaNoBid,
		VARIANT_BOOL bUseTheoVolaBadMarket,
		DOUBLE dUndPriceTolerance,
		EtsPriceRoundingRuleEnum enPriceRoundingRule, 
		IMmRvUndCollPtr spUndColl,
		DOUBLE dUndMidPrice,
		LONG   lUndId,
		DATE dtCalcDate
		);

	void _CalcFutPositionData(
		IEtsPriceProfileAtomPtr spOptPriceProfile,
		VARIANT_BOOL bIsPnlLTD,
		VARIANT_BOOL bUseTheoVolatility,
		VARIANT_BOOL bUseTheoVolaNoBid,
		VARIANT_BOOL bUseTheoVolaBadMarket,
		DOUBLE dUndPriceTolerance,
		EtsPriceRoundingRuleEnum enPriceRoundingRule, 
		DOUBLE dUndMidPrice,
		DATE dtCalcDate,
		EtsContractTypeEnum enUndType
		);

	bool IsVisible()const
	{
		return m_bVisible!=VARIANT_FALSE?true:false;
	}
public:

	// main info
	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
		IMPLEMENT_SIMPLE_PROPERTY(EtsContractTypeEnum, ContractType, m_enContractType)
		IMPLEMENT_BSTRT_PROPERTY(Symbol, m_bstrSymbol)
		IMPLEMENT_BSTRT_PROPERTY(LogEnhansement , m_bsLogEnhansement )
		IMPLEMENT_SIMPLE_PROPERTY(LONG,ExternalPosition,m_lExternalPosition)

		// option related info
		IMPLEMENT_SIMPLE_PROPERTY(EtsOptionTypeEnum, OptType, m_enOptType)
		IMPLEMENT_SIMPLE_PROPERTY(DATE, Expiry, m_dtExpiry)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Strike, m_dStrike)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Rate, m_dRate)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaWeight, m_dVegaWeight)
		//IMPLEMENT_SIMPLE_PROPERTY(LONG, ExpiryMonth, m_nExpiryMonth)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, OptionRootID, m_nOptionRootID)

		// auxilary	info
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, Visible, m_bVisible)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, CalcGreeks, m_bCalcGreeks)
		IMPLEMENT_BSTRT_PROPERTY(ImportId, m_bstrImportId)

		IMPLEMENT_SIMPLEREADONLY_PROPERTY(DOUBLE, NetExposure,		m_dNetExposure)
		IMPLEMENT_SIMPLEREADONLY_PROPERTY(VARIANT_BOOL, BadNetExposure,	m_bBadNetExposure)


		// position	info
		IMPLEMENT_SIMPLE_PROPERTY(LONG, Qty, m_nQty)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyInShares, m_nQtyInShares)

		IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyLTDBuy, m_nQtyLTDBuy)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyLTDSell, m_nQtyLTDSell)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosLTDBuy, m_dPosLTDBuy)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosLTDSell, m_dPosLTDSell)

		IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyDailyPrevDateBuy, m_nQtyDailyPrevDateBuy)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyDailyPrevDateSell, m_nQtyDailyPrevDateSell)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosDailyPrevDateBuy, m_dPosDailyPrevDateBuy)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosDailyPrevDateSell, m_dPosDailyPrevDateSell)

		IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyDailyTodayBuy, m_nQtyDailyTodayBuy)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyDailyTodaySell, m_nQtyDailyTodaySell)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosDailyTodayBuy, m_dPosDailyTodayBuy)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosDailyTodaySell, m_dPosDailyTodaySell)

		// pnl info
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlMtm, m_dPnlMtm)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlTheo, m_dPnlTheo)

		// theo in shares info
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DeltaInShares, m_dDeltaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaInShares, m_dGammaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaInSharesPerc, m_dGammaInSharesPerc)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaInShares, m_dVegaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, WtdVega, m_dWtdVega)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaInShares, m_dThetaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, RhoInShares, m_dRhoInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaDeltaInShares, m_dThetaDeltaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaGammaInShares, m_dThetaGammaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaDeltaInShares, m_dVegaDeltaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaGammaInShares, m_dVegaGammaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, TimeValue, m_dTimeValue)

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetDelta, m_dNetDelta)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetDelta, m_bBadNetDelta)

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DeltaEq, m_dDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadDeltaEq, m_bBadDeltaEq)

		// synthetic info
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsSynthetic, m_bIsSynthetic)
		IMPLEMENT_OBJECT_PROPERTY(IMmRvSynthGreeksColl*, SynthGreeks, m_spSynthGreeks)
		IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsStrategyAtom*,	Strategy,  m_spStrategy)
		IMPLEMENT_OBJECTREADONLY_PROPERTY(IRvMmQuoteAtom*,	Quote,  m_spQuote)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsSyntheticAggregation, m_bIsSyntheticAggregation)


		IMPLEMENT_SIMPLE_PROPERTY(LONG, UndID, m_nUndID)
		//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, SynthBeta, m_dSynthBeta)

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetGamma, m_dNetGamma)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetGamma, m_bBadNetGamma)

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, BetaWtdDeltaEq, m_dBetaWtdDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadBetaWtdDeltaEq, m_bBadBetaWtdDeltaEq)

		IMPLEMENT_OBJECT_PROPERTY(IMmRvFutAtom*, Fut, m_spFut)
		IMPLEMENT_OBJECT_PROPERTY(IMmRvFutAtom*, ActiveFuture, m_spActiveFuture)
		STDMETHODIMP ClearValues()
	{
		__MmRvPosAtom::ClearValues();
		return S_OK;
	}

	STDMETHODIMP ClearValuesInShares()
	{
		__MmRvPosAtom::ClearValuesInShares();
		return S_OK;
	}

	STDMETHOD(CalcOptionGreeks)(IMmRvUndColl* aUndColl,
		IMmRvUndAtom* aUnd,
		DOUBLE dUndMidPrice,
		LONG nMask,
		VARIANT_BOOL bIsPnlLTD, 
		EtsCalcModelTypeEnum enCalcModel,
		VARIANT_BOOL bUseTheoVolatility,
		VARIANT_BOOL bUseTheoVolaNoBid,
		VARIANT_BOOL bUseTheoVolaBadMarket,
		DOUBLE dUndPriceTolerance,
		EtsPriceRoundingRuleEnum enPriceRoundingRule,
		DATE dtCalcDate);

	STDMETHOD(CalcFutOptionGreeks)(IMmRvUndAtom* aUnd,
		DOUBLE dUndMidPrice,
		LONG nMask,
		VARIANT_BOOL bIsPnlLTD,
		EtsCalcModelTypeEnum enCalcModel,
		VARIANT_BOOL bUseTheoVolatility,
		VARIANT_BOOL bUseTheoVolaNoBid,
		VARIANT_BOOL bUseTheoVolaBadMarket,
		DOUBLE dUndPriceTolerance,
		EtsPriceRoundingRuleEnum enPriceRoundingRule,
		DATE dtCalcDate);

	STDMETHOD(CalcPnlMtm)(VARIANT_BOOL bIsPnlLTD,
		DOUBLE dPriceBid,
		DOUBLE dPriceAsk,
		VARIANT_BOOL bSetToTheoPnlAlso,
		DATE _dtCalculationDate)
	{
		_CalcPnlMtm(bIsPnlLTD, dPriceBid, dPriceAsk, false,_dtCalculationDate);
		if(bSetToTheoPnlAlso)
			m_dPnlTheo = m_dPnlMtm;
		return S_OK;
	}
	STDMETHOD(AddTrade)(IMmTradeInfoAtom* pTrade, IMmRvUndAtom* pUnd);
	STDMETHOD(GetOpositOption)(BSTR*vSymbol);
	STDMETHOD(GetCopyOfObject)(VARIANT_BOOL bNewQuote , IMmRvPosAtom**ppCopy);
	STDMETHOD(InitSyntAndFut)( IMmRvSynthGreeksColl* , IMmRvFutAtom*, IMmRvFutAtom*) ;
	STDMETHOD(IsOTM)(DOUBLE dUndPriceTolerance, EtsPriceRoundingRuleEnum enPriceRoundingRule , VARIANT_BOOL*pVal);
	STDMETHOD(GetFormatedXMLForDBUpdate)(LONG vUndID, BSTR*pVal);
	STDMETHOD(DistanceToStrike)(DOUBLE Price,DOUBLE*pDistance);
};

OBJECT_ENTRY_AUTO(__uuidof(MmRvPosAtom), CMmRvPosAtom)

#endif //__MMRVPOSATOM_H__
//// MmRvPosAtom.h : Declaration of the CMmRvPosAtom
//#ifndef __MMRVPOSATOM_H__
//#define __MMRVPOSATOM_H__
//#pragma once
//
//#include "resource.h"       // main symbols
//#include "EtsMmRisks.h"
//#include "MmRvSynthGreeksColl.h"
//#include "MmRvFutAtom.h"
//
//_COM_SMARTPTR_TYPEDEF(IMmRvPosAtom, IID_IMmRvPosAtom);
//
///////////////////////////////////////////////////////////////////////////////
////
//struct __MmRvPosAtom
//{
//	// main info
//	LONG						m_nID;
//	EtsContractTypeEnum			m_enContractType;
//	CComBSTR					m_bstrSymbol;
//
//	// option related info
//	EtsOptionTypeEnum			m_enOptType;
//	DATE						m_dtExpiry;
//	DOUBLE						m_dStrike;
//	DOUBLE						m_dVola;
//	DOUBLE						m_dRate;
//	DOUBLE						m_dVegaWeight;
//	LONG						m_nExpiryMonth;
//	LONG						m_nOptionRootID;
//
//	// auxilary	info
//	VARIANT_BOOL				m_bVisible;
//	VARIANT_BOOL				m_bCalcGreeks;
//	CComBSTR					m_bstrImportId;
//
//	// price info
//	DOUBLE						m_dPriceBid;
//	DOUBLE						m_dPriceAsk;
//	DOUBLE						m_dPriceLast;
//	DOUBLE						m_dPriceClose;
//
//	// position	info
//	LONG						m_nLotSize;
//	LONG						m_nQty;
//	LONG						m_nQtyInShares;
//
//	LONG						m_nQtyLTDBuy;
//	LONG						m_nQtyLTDSell;
//	DOUBLE						m_dPosLTDBuy;
//	DOUBLE						m_dPosLTDSell;
//
//	LONG						m_nQtyDailyPrevDateBuy;
//	LONG						m_nQtyDailyPrevDateSell;
//	DOUBLE						m_dPosDailyPrevDateBuy;
//	DOUBLE						m_dPosDailyPrevDateSell;
//
//	LONG						m_nQtyDailyTodayBuy;
//	LONG						m_nQtyDailyTodaySell;
//	DOUBLE						m_dPosDailyTodayBuy;
//	DOUBLE						m_dPosDailyTodaySell;
//
//	// pnl info
//	DOUBLE						m_dPnlMtm;
//	DOUBLE						m_dPnlTheo;
//
//	// theo info
//	DOUBLE						m_dPriceTheo;
//	DOUBLE						m_dDelta;
//	DOUBLE						m_dGamma;
//	DOUBLE						m_dVega;
//	DOUBLE						m_dTheta;
//	DOUBLE						m_dRho;
//	DOUBLE						m_dThetaDelta;
//	DOUBLE						m_dThetaGamma;
//	DOUBLE						m_dVegaDelta;
//	DOUBLE						m_dVegaGamma;
//	
//	// theo in shares info
//	DOUBLE						m_dDeltaInShares;
//	DOUBLE						m_dGammaInShares;
//	DOUBLE						m_dGammaInSharesPerc;
//	DOUBLE						m_dVegaInShares;
//	DOUBLE						m_dWtdVega;
//	DOUBLE						m_dThetaInShares;
//	DOUBLE						m_dRhoInShares;
//	DOUBLE						m_dThetaDeltaInShares;
//	DOUBLE						m_dThetaGammaInShares;
//	DOUBLE						m_dVegaDeltaInShares;
//	DOUBLE						m_dVegaGammaInShares;
//	DOUBLE						m_dTimeValue;
//	DOUBLE						m_dNetChange;
//
//	// synthetic info
//	VARIANT_BOOL				m_bIsSynthetic;
//	IMmRvSynthGreeksCollPtr		m_spSynthGreeks;
//	LONG						m_nUndID;
//	//DOUBLE						m_dSynthBeta;
//	EtsReplacePriceStatusEnum	m_enReplacePriceStatus;
//
//	DOUBLE							m_dNetGamma;
//	VARIANT_BOOL					m_bBadNetGamma;
//
//
//	IMmRvFutAtomPtr				m_spFut;
//
//	__MmRvPosAtom() :
//		m_nID(0L), m_enContractType(enCtNone),
//		m_enOptType(enOtCall),
//		m_dtExpiry(0.),
//		m_dStrike(0.),
//		m_dVola(0.),
//		m_dRate(0.),
//		m_dVegaWeight(0.),
//		m_nExpiryMonth(0L),
//		m_nOptionRootID(0L),
//
//		m_bVisible(VARIANT_FALSE),
//		m_bCalcGreeks(VARIANT_FALSE),
//
//		m_dPriceBid(BAD_DOUBLE_VALUE),
//		m_dPriceAsk(BAD_DOUBLE_VALUE),
//		m_dPriceLast(BAD_DOUBLE_VALUE),
//		m_dPriceClose(BAD_DOUBLE_VALUE),
//
//		m_nLotSize(0L),
//		m_nQty(BAD_LONG_VALUE),
//		m_nQtyInShares(BAD_LONG_VALUE),
//
//		m_nQtyLTDBuy(BAD_LONG_VALUE),
//		m_nQtyLTDSell(BAD_LONG_VALUE),
//		m_dPosLTDBuy(BAD_DOUBLE_VALUE),
//		m_dPosLTDSell(BAD_DOUBLE_VALUE),
//
//		m_nQtyDailyPrevDateBuy(BAD_LONG_VALUE),
//		m_nQtyDailyPrevDateSell(BAD_LONG_VALUE),
//		m_dPosDailyPrevDateBuy(BAD_DOUBLE_VALUE),
//		m_dPosDailyPrevDateSell(BAD_DOUBLE_VALUE),
//
//		m_nQtyDailyTodayBuy(BAD_LONG_VALUE),
//		m_nQtyDailyTodaySell(BAD_LONG_VALUE),
//		m_dPosDailyTodayBuy(BAD_DOUBLE_VALUE),
//		m_dPosDailyTodaySell(BAD_DOUBLE_VALUE),
//		m_dNetChange(BAD_DOUBLE_VALUE),
//		m_bIsSynthetic(VARIANT_FALSE),
//		m_nUndID(0L),
//		//m_dSynthBeta(0.),
//		m_enReplacePriceStatus(enRpsNone)
//	{
//		ClearValues();
//		ClearValuesInShares();
//	}
//
//	void ClearValues()
//	{
//		m_dPriceTheo = BAD_DOUBLE_VALUE;
//		m_dDelta = BAD_DOUBLE_VALUE;
//		m_dGamma = BAD_DOUBLE_VALUE;
//		m_dVega = BAD_DOUBLE_VALUE;
//		m_dTheta = BAD_DOUBLE_VALUE;
//		m_dRho = BAD_DOUBLE_VALUE;
//		m_dThetaDelta = BAD_DOUBLE_VALUE;
//		m_dThetaGamma = BAD_DOUBLE_VALUE;
//		m_dVegaDelta = BAD_DOUBLE_VALUE;
//		m_dVegaGamma = BAD_DOUBLE_VALUE;
//	}
//
//	void ClearValuesInShares()
//	{
//		m_dPnlMtm = BAD_DOUBLE_VALUE;
//		m_dPnlTheo = BAD_DOUBLE_VALUE;
//
//		m_dDeltaInShares = BAD_DOUBLE_VALUE;
//		m_dGammaInShares = BAD_DOUBLE_VALUE;
//		m_dGammaInSharesPerc = BAD_DOUBLE_VALUE;
//		m_dVegaInShares = BAD_DOUBLE_VALUE;
//		m_dWtdVega = BAD_DOUBLE_VALUE;
//		m_dThetaInShares = BAD_DOUBLE_VALUE;
//		m_dRhoInShares = BAD_DOUBLE_VALUE;
//		m_dThetaDeltaInShares = BAD_DOUBLE_VALUE;
//		m_dThetaGammaInShares = BAD_DOUBLE_VALUE;
//		m_dVegaDeltaInShares = BAD_DOUBLE_VALUE;
//		m_dVegaGammaInShares = BAD_DOUBLE_VALUE;
//		m_dTimeValue = BAD_DOUBLE_VALUE;
//
//		m_dNetGamma = BAD_DOUBLE_VALUE;
//
//	}
//};
//
///////////////////////////////////////////////////////////////////////////////
////
//class ATL_NO_VTABLE CMmRvPosAtom : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CMmRvPosAtom, &CLSID_MmRvPosAtom>,
//	public ISupportErrorInfoImpl<&IID_IMmRvPosAtom>,
//	public IDispatchImpl<IMmRvPosAtom, &IID_IMmRvPosAtom, &LIBID_EtsMmRisksLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
//	public __MmRvPosAtom
//{
//public:
//	CMmRvPosAtom()
//	{
//	}
//
//DECLARE_REGISTRY_RESOURCEID(IDR_MMRVPOSATOM)
//
//DECLARE_NOT_AGGREGATABLE(CMmRvPosAtom)
//
//BEGIN_COM_MAP(CMmRvPosAtom)
//	COM_INTERFACE_ENTRY(IMmRvPosAtom)
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
//		m_spSynthGreeks = NULL;
//		m_spFut = NULL;
//	}
//
//private:
//	void _GetBasketIndexDividends(IIndexAtomPtr spBasketIndex, REGULAR_DIVIDENDS* pDivs, LONG nMaxCount) throw();
//	void _GetSyntheticRootBasketDividends(ISynthRootAtomPtr spSynthRoot, REGULAR_DIVIDENDS* pDivs, LONG nMaxCount) throw();
//	void _CalcPnlMtm(VARIANT_BOOL bIsPnlLTD, DOUBLE dOptPriceBid, DOUBLE dOptPriceAsk, bool ReplaceWithZero);
//	void _CalcPnlTheo(VARIANT_BOOL bIsPnlLTD);
//
//public:
//	
//	// main info
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
//	IMPLEMENT_SIMPLE_PROPERTY(EtsContractTypeEnum, ContractType, m_enContractType)
//	IMPLEMENT_BSTR_PROPERTY(Symbol, m_bstrSymbol)
//
//	// option related info
//	IMPLEMENT_SIMPLE_PROPERTY(EtsOptionTypeEnum, OptType, m_enOptType)
//	IMPLEMENT_SIMPLE_PROPERTY(DATE, Expiry, m_dtExpiry)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Strike, m_dStrike)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Vola, m_dVola)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Rate, m_dRate)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaWeight, m_dVegaWeight)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, ExpiryMonth, m_nExpiryMonth)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, OptionRootID, m_nOptionRootID)
//
//	// auxilary	info
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, Visible, m_bVisible)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, CalcGreeks, m_bCalcGreeks)
//	IMPLEMENT_BSTR_PROPERTY(ImportId, m_bstrImportId)
//
//	// price info
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceBid,		m_dPriceBid)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceAsk,		m_dPriceAsk)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceLast,	m_dPriceLast)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceClose,	m_dPriceClose)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetChange,	m_dNetChange)
//
//	// position	info
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, LotSize, m_nLotSize)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, Qty, m_nQty)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyInShares, m_nQtyInShares)
//
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyLTDBuy, m_nQtyLTDBuy)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyLTDSell, m_nQtyLTDSell)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosLTDBuy, m_dPosLTDBuy)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosLTDSell, m_dPosLTDSell)
//
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyDailyPrevDateBuy, m_nQtyDailyPrevDateBuy)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyDailyPrevDateSell, m_nQtyDailyPrevDateSell)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosDailyPrevDateBuy, m_dPosDailyPrevDateBuy)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosDailyPrevDateSell, m_dPosDailyPrevDateSell)
//
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyDailyTodayBuy, m_nQtyDailyTodayBuy)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, QtyDailyTodaySell, m_nQtyDailyTodaySell)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosDailyTodayBuy, m_dPosDailyTodayBuy)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PosDailyTodaySell, m_dPosDailyTodaySell)
//
//	// pnl info
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlMtm, m_dPnlMtm)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlTheo, m_dPnlTheo)
//
//	// theo info
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceTheo, m_dPriceTheo)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Delta, m_dDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Gamma, m_dGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Vega, m_dVega)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Theta, m_dTheta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Rho, m_dRho)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaDelta, m_dThetaDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaGamma, m_dThetaGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaDelta, m_dVegaDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaGamma, m_dVegaGamma)
//	
//	// theo in shares info
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DeltaInShares, m_dDeltaInShares)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaInShares, m_dGammaInShares)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaInSharesPerc, m_dGammaInSharesPerc)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaInShares, m_dVegaInShares)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, WtdVega, m_dWtdVega)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaInShares, m_dThetaInShares)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, RhoInShares, m_dRhoInShares)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaDeltaInShares, m_dThetaDeltaInShares)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaGammaInShares, m_dThetaGammaInShares)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaDeltaInShares, m_dVegaDeltaInShares)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaGammaInShares, m_dVegaGammaInShares)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, TimeValue, m_dTimeValue)
//
//	// synthetic info
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsSynthetic, m_bIsSynthetic)
//	IMPLEMENT_OBJECT_PROPERTY(IMmRvSynthGreeksColl*, SynthGreeks, m_spSynthGreeks)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, UndID, m_nUndID)
//	//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, SynthBeta, m_dSynthBeta)
//	IMPLEMENT_SIMPLE_PROPERTY(EtsReplacePriceStatusEnum, ReplacePriceStatus, m_enReplacePriceStatus)
//
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetGamma, m_dNetGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetGamma, m_bBadNetGamma)
//
//	IMPLEMENT_OBJECT_PROPERTY(IMmRvFutAtom*, Fut, m_spFut)
//
//	STDMETHODIMP ClearValues()
//	{
//		__MmRvPosAtom::ClearValues();
//		return S_OK;
//	}
//
//	STDMETHODIMP ClearValuesInShares()
//	{
//		__MmRvPosAtom::ClearValuesInShares();
//		return S_OK;
//	}
//
//	STDMETHOD(CalcOptionGreeks)(IMmRvUndColl* aUndColl,
//								IMmRvUndAtom* aUnd,
//								DOUBLE dUndMidPrice,
//								LONG nMask,
//								VARIANT_BOOL bIsPnlLTD,
//								EtsCalcModelTypeEnum enCalcModel,
//								VARIANT_BOOL bUseTheoVolatility,
//								VARIANT_BOOL bUseTheoVolaNoBid,
//								VARIANT_BOOL bUseTheoVolaBadMarket,
//								DOUBLE dUndPriceTolerance,
//								EtsPriceRoundingRuleEnum enPriceRoundingRule);
//
//	STDMETHOD(CalcFutOptionGreeks)(IMmRvUndAtom* aUnd,
//								DOUBLE dUndMidPrice,
//								LONG nMask,
//								VARIANT_BOOL bIsPnlLTD,
//								EtsCalcModelTypeEnum enCalcModel,
//								VARIANT_BOOL bUseTheoVolatility,
//								VARIANT_BOOL bUseTheoVolaNoBid,
//								VARIANT_BOOL bUseTheoVolaBadMarket,
//								DOUBLE dUndPriceTolerance,
//								EtsPriceRoundingRuleEnum enPriceRoundingRule);
//
//	STDMETHOD(CalcPnlMtm)(VARIANT_BOOL bIsPnlLTD,
//							DOUBLE dPriceBid,
//							DOUBLE dPriceAsk,
//							VARIANT_BOOL bSetToTheoPnlAlso)
//	{
//		_CalcPnlMtm(bIsPnlLTD, dPriceBid, dPriceAsk, false);
//		if(bSetToTheoPnlAlso)
//			m_dPnlTheo = m_dPnlMtm;
//		return S_OK;
//	}
//	STDMETHOD(AddTrade)(IMmTradeInfoAtom* pTrade, IMmRvUndAtom* pUnd);
//
//};
//
//OBJECT_ENTRY_AUTO(__uuidof(MmRvPosAtom), CMmRvPosAtom)
//
//#endif //__MMRVPOSATOM_H__