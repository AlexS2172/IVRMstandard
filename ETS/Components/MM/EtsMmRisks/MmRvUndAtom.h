// MmRvUndAtom.h : Declaration of the CMmRvUndAtom
#ifndef __MMRVUNDATOM_H__
#define __MMRVUNDATOM_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsMmRisks.h"
#include "MmRvPosColl.h"
#include "MmRvFutColl.h"
#include "MmRvExpColl.h"
#include "MmRvAggregationData.h"

_COM_SMARTPTR_TYPEDEF(IMmRvUndAtom, IID_IMmRvUndAtom);
_COM_SMARTPTR_TYPEDEF(IMmRvAggregationDataAtom, IID_IMmRvAggregationDataAtom);

/////////////////////////////////////////////////////////////////////////////
//
struct __MmRvUndAtom
	: public /*__MmRvAggregationData,*/ CMmRvAggData
{
	LONG							m_nID;
	EtsContractTypeEnum				m_enContractType;
	_bstr_t							m_bstrSymbol;

	DOUBLE							m_dYield;

    VARIANT_BOOL                    m_bShouldMultOptDeltaEq;
	DOUBLE                          m_dKOptDeltaEq;

	VARIANT_BOOL					m_bIsAmerican;
	VARIANT_BOOL					m_bIsHTB;

	DOUBLE							m_dSkew;
	DOUBLE							m_dKurt;

	VARIANT_BOOL					m_bCalcGreeks;
	VARIANT_BOOL					m_bCalcTotals;

	VARIANT_BOOL					m_bVolaUpdated;
	DOUBLE							m_dSuPrice;

	LONG							m_nLotSize;

	//DOUBLE							m_dSTDValue ;

	IMmRvPosCollPtr					m_spPos;
	IMmRvExpCollPtr                 m_spExp;
	VARIANT_BOOL					m_bHasOptPos;
	IVolaControlPtr					m_spVolaSrv;

	IIndexAtomPtr					m_spBasketIndex;

	VARIANT_BOOL					m_bUseMidRates;

	VARIANT_BOOL					m_bHasSynthetic;

	ISynthRootCollPtr				m_spSynthRoots;
	IMmRvSynthGreeksCollPtr			m_spSynthGreeks;
	IMmRvPosCollPtr					m_spSynthPos;
	IEtsPriceProfileAtomPtr			m_spUndPriceProfile;
	IEtsPriceProfileAtomPtr			m_spOptPriceProfile;
	EtsReplacePriceStatusEnum		m_enReplacePriceStatus;
	IEtsIndexDivAtomPtr				m_spDividend;

	IMmRvFutCollPtr					m_spFut;
	IMmRvFutAtomPtr					m_spActiveFuture;

	//IMmRvSynthGreeksCollPtr		    m_spSyntheticGreeks;

	IMmRvPricePtr					m_spPrice;
	CComObject<CMmRvPrice>*		m_pPrice;

	IMmRvPricePtr					m_spSuPrice;
	CComObject<CMmRvPrice>*		m_pSuPrice;
	LONG							m_nPrimaryExchangeID;
	_bstr_t							m_bstrPrimaryExchangeCode;

	void Clear(bool bErase, bool bClearPrice)
	{

		if(bClearPrice && m_pPrice)
			m_pPrice->Clear();
		ClearAggregatedValues();
	}

	__MmRvUndAtom()
		:/*__MmRvAggregationData(), */
		CMmRvAggData(CMmRvAggData::enUndAgg)
		,m_pPrice(NULL)
		,m_pSuPrice(NULL)
	{
		Clear(true, true);
		Clear(true);
	}

	void Clear(bool bErase)
	{
		Clear(bErase, true);

		m_nID = 0L;
		m_enContractType = enCtNone;
		m_bstrSymbol = L"";
		m_bUseMidRates = VARIANT_FALSE;
		m_bHasOptPos = VARIANT_FALSE;
		m_nPrimaryExchangeID = 0L;
		m_bstrPrimaryExchangeCode = L"";

		m_dYield = 0.;
		//m_dSTDValue = 0 ;
		m_bIsAmerican = VARIANT_FALSE;
		m_dSkew = 0.;
		m_dKurt = 0.;



		m_bCalcGreeks = VARIANT_FALSE;
		m_bCalcTotals = VARIANT_FALSE;
		//m_bBadOptDeltaEq = VARIANT_FALSE;

		m_dSuPrice = BAD_DOUBLE_VALUE;
		m_nLotSize = BAD_LONG_VALUE;

		m_bHasSynthetic = VARIANT_FALSE;

		if(!bErase && m_spPos != NULL)
			m_spPos->Clear();
		else
			m_spPos = NULL;

		if(!bErase && m_spVolaSrv != NULL)
			m_spVolaSrv->CleanUp();
		else
			m_spVolaSrv = NULL;

		m_spBasketIndex = NULL;
		m_spSynthRoots = NULL;
		m_spSynthGreeks = NULL;
		m_spSynthPos = NULL;

		m_spUndPriceProfile = NULL;
		m_spOptPriceProfile = NULL;
		m_spFut = NULL;

		m_enReplacePriceStatus = enRpsNone;
		m_spDividend = NULL;
		m_spActiveFuture = NULL;
		
		ClearAggregatedValues();
	}


	// adds position to aggregations under underlying
	void AddPosToAggregations(MmRvPosAtomPtr& pPos);

	void AggregatePositionQuantity(CMmRvPosAtom* pPos);
	void AggregatePosition(CMmRvPosAtom* pPos, double underlyingPtrice,DOUBLE dUndPriceTolerance, EtsPriceRoundingRuleEnum enPriceRoundingRule);
	void AggregatePositionDeltas(CMmRvPosAtom* pPos);
	void AggregatePositionGammas(CMmRvPosAtom* pPos, double underlyingPtrice,DOUBLE dUndPriceTolerance, EtsPriceRoundingRuleEnum enPriceRoundingRule);
	void AggregatePositionPnLs(CMmRvPosAtom* pPos);
	void AggregatePositionVegas(CMmRvPosAtom* pPos);
	void AggregatePositionThetas(CMmRvPosAtom* pPos);
	void AggregatePositionRhos(CMmRvPosAtom* pPos);
	void AggregatePositionTmVal(CMmRvPosAtom* pPos);
};

/////////////////////////////////////////////////////////////////////////////
//
class ATL_NO_VTABLE CMmRvUndAtom : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMmRvUndAtom, &CLSID_MmRvUndAtom>,
	public ISupportErrorInfoImpl<&IID_IMmRvUndAtom>,
	public IDispatchImpl<IMmRvUndAtom, &IID_IMmRvUndAtom, &LIBID_EtsMmRisksLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<IMmRvAggregationDataAtom, &IID_IMmRvAggregationDataAtom, &LIBID_EtsMmRisksLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __MmRvUndAtom
{
public:
	

	CMmRvUndAtom()
		:m_pPos(NULL)
		,m_dNetExposureAUM(BAD_DOUBLE_VALUE)

		
	{
		pUnd_ = this;
		__MmRvUndAtom::Clear(true, false);

		m_pUnkMarshaler = NULL;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MMRVUNDATOM)

	DECLARE_NOT_AGGREGATABLE(CMmRvUndAtom)

	BEGIN_COM_MAP(CMmRvUndAtom)
		COM_INTERFACE_ENTRY(IMmRvUndAtom)
		COM_INTERFACE_ENTRY(IMmRvAggregationDataAtom)	
		COM_INTERFACE_ENTRY2(IDispatch, IMmRvUndAtom)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		try
		{
			_CHK(CComObject<CMmRvPosColl>::CreateInstance(&m_pPos), _T("Fail to create positions."));
			m_spPos.Attach(m_pPos, TRUE);

			_CHK(CComObject<CMmRvExpColl>::CreateInstance(&m_pExp), _T("Fail to create Expirations."));
			m_spExp.Attach(m_pExp, TRUE);


			_CHK(CComObject<CMmRvPrice>::CreateInstance(&m_pPrice), _T("Fail to create Price Info."));
			m_spPrice.Attach(m_pPrice, TRUE);

			_CHK(CComObject<CMmRvPrice>::CreateInstance(&m_pSuPrice), _T("Fail to create Price Info."));
			m_spSuPrice.Attach(m_pSuPrice, TRUE);

			_CHK(m_spVolaSrv.CreateInstance(CLSID_VolaControl), _T("Fail to create volatility control."));
			_CHK(m_spDividend.CreateInstance(CLSID_EtsIndexDivAtom), _T("Fail to create dividend object"));

			_CHK(CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkMarshaler.p));
		}
		catch(const _com_error& e)
		{
			return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvUndAtom, e.Error());
		}
		return S_OK;
	}

	void FinalRelease()
	{
		//m_pPos->Clear();
		__MmRvUndAtom::Clear(true);

		m_pUnkMarshaler.Release();
	}

	static void Date2Text( DATE dt, _bstr_t& OutString )
	{
		EgLib::vt_date		vrntDate(dt);
		wchar_t	wchBuf[100];

		if ( 0 == static_cast<long>(dt) ) 
			_snwprintf_s(wchBuf, sizeof wchBuf/sizeof(wchar_t) ,L"");
		else
			_snwprintf_s(wchBuf, sizeof wchBuf/sizeof(wchar_t) ,L"%s%02d", bsMonth[vrntDate.get_month()-1], vrntDate.get_year()-2000 );
		OutString = wchBuf;
	}

private:
	static const WCHAR* bsMonth[12];
	void _ClearSynthGreeks() throw();
	void _CalcTotalsForOptionPos(CMmRvPosAtom* pPos) throw();

	CComPtr<IUnknown>			m_pUnkMarshaler;

	DOUBLE						m_dNetExposureAUM;
public:
	CComObject<CMmRvPosColl>* m_pPos;
	CComObject<CMmRvExpColl>* m_pExp; 

public:
	typedef std::set<long> CUnderkyingGroup;
	CUnderkyingGroup	m_underlyingGroup;

	void VisiblePositions(bool bVisible)
	{
		if(m_pPos)
		{
			CMmRvPosColl::CollType::iterator itr = m_pPos->m_collRef.begin();
			CMmRvPosColl::CollType::iterator itrEnd = m_pPos->m_collRef.end();
			for(;itr!=itrEnd;++itr)
			{
				CMmRvPosAtom* pPosAtom = dynamic_cast<CMmRvPosAtom*>(itr->second->second);
				if(pPosAtom)
					pPosAtom->m_bVisible = bVisible?VARIANT_TRUE:VARIANT_FALSE;
			}
		}
	}

public:

	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
		IMPLEMENT_SIMPLE_PROPERTY(EtsContractTypeEnum, ContractType, m_enContractType)
		//IMPLEMENT_BSTRT_PROPERTY(Symbol, m_bstrSymbol)
	//#define IMPLEMENT_BSTRT_PROPERTY(Name, Member)
	STDMETHODIMP put_Symbol(BSTR NewVal){
		ObjectLock lock(this);
		m_bstrSymbol = NewVal;
		Name_ = m_bstrSymbol;
		return S_OK;
	}
	
	STDMETHODIMP get_Symbol(BSTR* pVal){
		if(!pVal) return E_POINTER;
		if(*pVal)
			::SysFreeString(*pVal);
		ObjectLock lock(this);
		*pVal = m_bstrSymbol.copy();
		return S_OK;
	}



		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Yield, m_dYield)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, bShouldMultOptDeltaEq, m_bShouldMultOptDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, dKOptDeltaEq, m_dKOptDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsAmerican, m_bIsAmerican)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsHTB, m_bIsHTB)

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Skew, m_dSkew)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Kurt, m_dKurt)

		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, CalcGreeks, m_bCalcGreeks)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, CalcTotals, m_bCalcTotals)

		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, VolaUpdated, m_bVolaUpdated)

		IMPLEMENT_SIMPLE_PROPERTY(LONG, LotSize, m_nLotSize)

		//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Beta, m_dBeta)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Beta, Beta_)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, Qty, UndPos_)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, OptQty, OptQty_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, UndPosForRates, UndPosForRates_)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, FutQty, FutQty_)

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlMtm, PnlMTM_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlTheo, PnLTheo_)

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetDelta, NetDlt_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, OptDelta, OptDlt_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Gamma, Gma1$_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaPerc, Gma1P_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Vega, Vga$_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, WtdVega, WtdVga$_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Theta, Tht$_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DeltaEq, NetDlt$_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaEq, NetGma$_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Rho, Rho$_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaDelta, ThtDlt_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaGamma, ThtGma_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaDelta, VgaDlt_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaGamma, VgaGma_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, TimeValue, TmVal_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, BetaWtdDeltaEq, BetaWtdDelta$_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, TimeValueInShares, TmValInShares_)


		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadPnlMtm, BadPnlMtm_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadPnlTheo, BadPnlTheo_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetDelta, BadNetDelta_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadOptDelta, BadOptDelta_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadGamma, BadGma1$_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadGammaPerc, BadGma1P_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadVega, BadVga$_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadWtdVega, BadWtdVga$_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadTheta, BadTht$_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadDeltaEq, BadNetDlt$_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadGammaEq, BadNetGma$_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadRho, BadRho$_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadThetaDelta, BadThtDlt_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadThetaGamma, BadThtGma_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadVegaDelta, BadVgaDlt_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadVegaGamma, BadVgaGma_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadTimeValue, BadTmVal_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadBetaWtdDeltaEq, BadBetaWtdDelta$_)

		IMPLEMENT_OBJECTREADONLY_PROPERTY(IMmRvPosColl*, Pos, m_spPos)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HasOptPos, m_bHasOptPos)
		IMPLEMENT_OBJECTREADONLY_PROPERTY(IVolaControl*, VolaSrv, m_spVolaSrv)

		IMPLEMENT_OBJECT_PROPERTY(IIndexAtom*, BasketIndex, m_spBasketIndex)

		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, UseMidRates, m_bUseMidRates)

		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HasSynthetic, m_bHasSynthetic)

		IMPLEMENT_OBJECT_PROPERTY(ISynthRootColl*, SynthRoots, m_spSynthRoots)
		IMPLEMENT_OBJECT_PROPERTY(IMmRvSynthGreeksColl*, SynthGreeks, m_spSynthGreeks)
		IMPLEMENT_OBJECT_PROPERTY(IMmRvPosColl*, SynthPos, m_spSynthPos)
		IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, UndPriceProfile, m_spUndPriceProfile)
		IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, OptPriceProfile, m_spOptPriceProfile)
		IMPLEMENT_SIMPLE_PROPERTY(EtsReplacePriceStatusEnum, ReplacePriceStatus, m_enReplacePriceStatus)

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetGamma, NetGma_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetGamma, BadNetGma_)

		IMPLEMENT_OBJECT_PROPERTY(IMmRvFutColl*, Fut, m_spFut)
		IMPLEMENT_OBJECT_PROPERTY(IEtsIndexDivAtom*, Dividend, m_spDividend)
		//IMPLEMENT_SIMPLE_PROPERTY(LONG,ExternalPosition,m_lExternalPosition)

		//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, STDValue, m_dSTDValue)
		IMPLEMENT_OBJECT_PROPERTY(IMmRvFutAtom*, ActiveFuture, m_spActiveFuture)

		IMPLEMENT_OBJECTREADONLY_PROPERTY(IMmRvPrice*, Price,   m_spPrice);
		IMPLEMENT_OBJECTREADONLY_PROPERTY(IMmRvPrice*, SuPrice, m_spSuPrice);
		IMPLEMENT_OBJECTREADONLY_PROPERTY(IMmRvExpColl*, ExpColl, m_spExp);

		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsSyntheticAggregation,	 m_bIsSyntheticAggregation);

		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadOptDeltaEq,  BadOptDlt$_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,		OptDeltaEq,		OptDlt$_)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, SuPrice, m_dSuPrice)

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetExposure,		NetExposure_)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetExposure,		BadNetExposure_)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, PrimaryExchangeID, m_nPrimaryExchangeID)

		STDMETHODIMP put_PrimaryExchangeCode(BSTR NewVal){
			ObjectLock lock(this);
			m_bstrPrimaryExchangeCode = NewVal;
			Name_ = m_bstrPrimaryExchangeCode;
			return S_OK;
		}

		STDMETHODIMP get_PrimaryExchangeCode(BSTR* pVal){
			if(!pVal) return E_POINTER;
			if(*pVal)
				::SysFreeString(*pVal);
			ObjectLock lock(this);
			*pVal = m_bstrPrimaryExchangeCode.copy();
			return S_OK;
		}

	STDMETHODIMP Clear()
	{
		__MmRvUndAtom::Clear(false);
		return S_OK;
	}

	STDMETHODIMP ClearValues()
	{
		
		ClearAggregatedValues();
		return S_OK;
	}

	STDMETHODIMP SetAllValuesAsBad()
	{
		//__MmRvUndAtom::SetAllValuesAsBad();
		SetAllValuesAsBad();
		return S_OK;
	}

	void  SetNetExposureAUM(DOUBLE dNewVal)
	{
		m_dNetExposureAUM = dNewVal;
	}

	DOUBLE GetNetExposureAUM() const { return m_dNetExposureAUM;}

	STDMETHOD(GetSyntheticUnderlyingPrice)(IMmRvUndColl* aUndColl,
		ISynthRootAtom* aSynthRoot,
		DOUBLE* pdSynthBid,
		DOUBLE* pdSynthAsk,
		DOUBLE* pdSynthLast);

	STDMETHOD(Calc)(IMmRvUndColl* aUndColl,
		LONG nMask,
		VARIANT_BOOL bCalcGreeks,
		VARIANT_BOOL bUpdateVola,
		VARIANT_BOOL bRealtimeCalc,
		VARIANT_BOOL bClearSynthGreeks,
		IEtsProcessDelay* aDelay,
		VARIANT_BOOL bIsPnlLTD,
		EtsCalcModelTypeEnum enCalcModel,
		VARIANT_BOOL bUseTheoVolatility,
		VARIANT_BOOL bUseTheoVolaNoBid,
		VARIANT_BOOL bUseTheoVolaBadMarket,
		DOUBLE dUndPriceTolerance,
		EtsPriceRoundingRuleEnum enPriceRoundingRule,
		LONG* pnOptUpdated,
		LONG* pnUndUpdated,
		LONG* pnFutUpdated,
		DATE dtCalcDate);

	STDMETHOD(CalcWtdVega)(IEtsExpCalColl* aExpCalColl);
	STDMETHOD(FindPosition)(DOUBLE dStrike, DATE dtExpiration, EtsOptionTypeEnum enType, IMmRvPosAtom** pPosAtom);

	STDMETHOD(CalcSyntheticUnderlying)(IMmRvUndColl* aUndColl,
		LONG nMask,
		VARIANT_BOOL bIsPnlLTD,
		EtsCalcModelTypeEnum enCalcModel,
		VARIANT_BOOL bUseTheoVolatility,
		VARIANT_BOOL bUseTheoVolaNoBid,
		VARIANT_BOOL bUseTheoVolaBadMarket,
		DOUBLE dUndPriceTolerance,
		EtsPriceRoundingRuleEnum enPriceRoundingRule,
		DATE dtCalcDate);

	STDMETHOD(GetUnderlyingPrice)(DOUBLE dTolerance, EtsPriceRoundingRuleEnum enPriceRound,EtsReplacePriceStatusEnum * penPriceStatus, VARIANT_BOOL *bFutureUsed, DOUBLE *pPrice);

	STDMETHOD(ClearRatios)();
};

OBJECT_ENTRY_AUTO(__uuidof(MmRvUndAtom), CMmRvUndAtom)

#endif //__MMRVUNDATOM_H__
//// MmRvUndAtom.h : Declaration of the CMmRvUndAtom
//#ifndef __MMRVUNDATOM_H__
//#define __MMRVUNDATOM_H__
//#pragma once
//
//#include "resource.h"       // main symbols
//#include "EtsMmRisks.h"
//#include "MmRvPosColl.h"
//#include "MmRvFutColl.h"
//
//_COM_SMARTPTR_TYPEDEF(IMmRvUndAtom, IID_IMmRvUndAtom);
//
///////////////////////////////////////////////////////////////////////////////
////
//struct __MmRvUndAtom
//{
//	LONG							m_nID;
//	EtsContractTypeEnum				m_enContractType;
//	CComBSTR						m_bstrSymbol;
//
//	DOUBLE							m_dYield;
//	//LONG							m_nDivFreq;
//	//DATE							m_dtDivDate;
//	//DOUBLE						m_dDivAmt;
//	VARIANT_BOOL					m_bIsAmerican;
//	VARIANT_BOOL					m_bIsHTB;
//	LONG							m_nExpCalendarID;
//
//	DOUBLE							m_dSkew;
//	DOUBLE							m_dKurt;
//
//	VARIANT_BOOL					m_bCalcGreeks;
//	VARIANT_BOOL					m_bCalcTotals;
//
//	VARIANT_BOOL					m_bVolaUpdated;
//	
//	DOUBLE							m_dPriceBid;
//	DOUBLE							m_dPriceAsk;
//	DOUBLE							m_dPriceLast;
//	DOUBLE							m_dPriceClose;
//	DOUBLE							m_dNetChange;
//
//	LONG							m_nLotSize;
//
//	DOUBLE							m_dBeta;
//
//	LONG							m_nQty;
//	LONG							m_nOptQty;
//	DOUBLE							m_dUndPosForRates;
//	LONG							m_nFutQty;
//
//	DOUBLE							m_dPnlMtm;
//	DOUBLE							m_dPnlTheo;
//
//	DOUBLE							m_dNetDelta;
//	DOUBLE							m_dOptDelta;
//	DOUBLE							m_dGamma;
//	DOUBLE							m_dGammaPerc;
//	DOUBLE							m_dVega;
//	DOUBLE							m_dWtdVega;
//	DOUBLE							m_dTheta;
//	DOUBLE							m_dDeltaEq;
//	DOUBLE							m_dGammaEq;
//	DOUBLE							m_dRho;
//	DOUBLE							m_dThetaDelta;
//	DOUBLE							m_dThetaGamma;
//	DOUBLE							m_dVegaDelta;
//	DOUBLE							m_dVegaGamma;
//	DOUBLE							m_dTimeValue;
//	DOUBLE							m_dBetaWtdDeltaEq;
//
//	VARIANT_BOOL					m_bBadPnlMtm;
//	VARIANT_BOOL					m_bBadPnlTheo;
//	VARIANT_BOOL					m_bBadNetDelta;
//	VARIANT_BOOL					m_bBadOptDelta;
//	VARIANT_BOOL					m_bBadGamma;
//	VARIANT_BOOL					m_bBadGammaPerc;
//	VARIANT_BOOL					m_bBadVega;
//	VARIANT_BOOL					m_bBadWtdVega;
//	VARIANT_BOOL					m_bBadTheta;
//	VARIANT_BOOL					m_bBadDeltaEq;
//	VARIANT_BOOL					m_bBadGammaEq;
//	VARIANT_BOOL					m_bBadRho;
//	VARIANT_BOOL					m_bBadThetaDelta;
//	VARIANT_BOOL					m_bBadThetaGamma;
//	VARIANT_BOOL					m_bBadVegaDelta;
//	VARIANT_BOOL					m_bBadVegaGamma;
//	VARIANT_BOOL					m_bBadTimeValue;
//	VARIANT_BOOL					m_bBadBetaWtdDeltaEq;
//
//	IMmRvPosCollPtr					m_spPos;
//	VARIANT_BOOL					m_bHasOptPos;
//	IVolaControlPtr					m_spVolaSrv;
//
//	IIndexAtomPtr					m_spBasketIndex;
//
//	VARIANT_BOOL					m_bUseMidRates;
//
//	VARIANT_BOOL					m_bHasSynthetic;
//
//	DOUBLE							m_dNetGamma;
//	VARIANT_BOOL					m_bBadNetGamma;
//
//
//	ISynthRootCollPtr				m_spSynthRoots;
//	IMmRvSynthGreeksCollPtr			m_spSynthGreeks;
//	IMmRvPosCollPtr					m_spSynthPos;
//	IEtsPriceProfileAtomPtr			m_spUndPriceProfile;
//	IEtsPriceProfileAtomPtr			m_spOptPriceProfile;
//	EtsReplacePriceStatusEnum		m_enReplacePriceStatus;
//	IEtsIndexDivAtomPtr				m_spDividend;
//
//	IMmRvFutCollPtr					m_spFut;
//
//	__MmRvUndAtom()
//	{
//		Clear(true);
//	}
//
//	void Clear(bool bErase)
//	{
//		m_nID = 0L;
//		m_enContractType = enCtNone;
//		m_bstrSymbol = L"";
//		m_bUseMidRates = VARIANT_FALSE;
//		m_bHasOptPos = VARIANT_FALSE;
//
//		m_dYield = 0.;
////		m_nDivFreq = 0;
////		m_dtDivDate = 0.;
////		m_dDivAmt = 0.;
//		m_bIsAmerican = VARIANT_FALSE;
//		m_dSkew = 0.;
//		m_dKurt = 0.;
//
//		m_bCalcGreeks = VARIANT_FALSE;
//		m_bCalcTotals = VARIANT_FALSE;
//
//		m_dPriceBid = BAD_DOUBLE_VALUE;
//		m_dPriceAsk = BAD_DOUBLE_VALUE;
//		m_dPriceLast = BAD_DOUBLE_VALUE;
//		m_dPriceClose = BAD_DOUBLE_VALUE;
//		m_nLotSize = BAD_LONG_VALUE;
//		m_dNetChange = BAD_DOUBLE_VALUE;
//
//		m_dBeta = BAD_DOUBLE_VALUE;
//
//		m_nQty = BAD_LONG_VALUE;
//		m_nOptQty = BAD_LONG_VALUE;
//		m_nFutQty = BAD_LONG_VALUE;
//		m_dUndPosForRates = 0.;
//
//		m_bHasSynthetic = VARIANT_FALSE;
//
//		if(!bErase && m_spPos != NULL)
//			m_spPos->Clear();
//		else
//			m_spPos = NULL;
//
//		if(!bErase && m_spVolaSrv != NULL)
//			m_spVolaSrv->CleanUp();
//		else
//			m_spVolaSrv = NULL;
//
//		m_spBasketIndex = NULL;
//		m_spSynthRoots = NULL;
//		m_spSynthGreeks = NULL;
//		m_spSynthPos = NULL;
//
//		m_spUndPriceProfile = NULL;
//		m_spOptPriceProfile = NULL;
//		m_spFut = NULL;
//
//		m_enReplacePriceStatus = enRpsNone;
//		m_spDividend = NULL;
//
//		ClearValues();
//	}
//
//	void ClearValues()
//	{
//		m_nQty = BAD_LONG_VALUE;
//		m_nOptQty = BAD_LONG_VALUE;
//		m_nFutQty = BAD_LONG_VALUE;
//		m_dPnlMtm = BAD_DOUBLE_VALUE;
//		m_dPnlTheo = BAD_DOUBLE_VALUE;
//		m_dNetDelta = BAD_DOUBLE_VALUE;
//		m_dOptDelta = BAD_DOUBLE_VALUE;
//		m_dGamma = BAD_DOUBLE_VALUE;
//		m_dGammaPerc = BAD_DOUBLE_VALUE;
//		m_dVega = BAD_DOUBLE_VALUE;
//		m_dWtdVega = BAD_DOUBLE_VALUE;
//		m_dTheta = BAD_DOUBLE_VALUE;
//		m_dDeltaEq = BAD_DOUBLE_VALUE;
//		m_dGammaEq = BAD_DOUBLE_VALUE;
//		m_dRho = BAD_DOUBLE_VALUE;
//		m_dThetaDelta = BAD_DOUBLE_VALUE;
//		m_dThetaGamma = BAD_DOUBLE_VALUE;
//		m_dVegaDelta = BAD_DOUBLE_VALUE;
//		m_dVegaGamma = BAD_DOUBLE_VALUE;
//		m_dTimeValue = BAD_DOUBLE_VALUE;
//		m_dBetaWtdDeltaEq = BAD_DOUBLE_VALUE;
//
//		m_dNetGamma = BAD_DOUBLE_VALUE;
//		m_bBadNetGamma = VARIANT_FALSE;
//
//
//		m_bBadPnlMtm = VARIANT_FALSE;
//		m_bBadPnlTheo = VARIANT_FALSE;
//		m_bBadNetDelta = VARIANT_FALSE;
//		m_bBadOptDelta = VARIANT_FALSE;
//		m_bBadGamma = VARIANT_FALSE;
//		m_bBadGammaPerc = VARIANT_FALSE;
//		m_bBadVega = VARIANT_FALSE;
//		m_bBadWtdVega = VARIANT_FALSE;
//		m_bBadTheta = VARIANT_FALSE;
//		m_bBadDeltaEq = VARIANT_FALSE;
//		m_bBadGammaEq = VARIANT_FALSE;
//		m_bBadRho = VARIANT_FALSE;
//		m_bBadThetaDelta = VARIANT_FALSE;
//		m_bBadThetaGamma = VARIANT_FALSE;
//		m_bBadVegaDelta = VARIANT_FALSE;
//		m_bBadVegaGamma = VARIANT_FALSE;
//		m_bBadTimeValue = VARIANT_FALSE;
//		m_bBadBetaWtdDeltaEq = VARIANT_FALSE;
//	}
//
//	void SetAllValuesAsBad()
//	{
//		m_bBadPnlMtm = VARIANT_TRUE;
//		m_bBadPnlTheo = VARIANT_TRUE;
//		m_bBadNetDelta = VARIANT_TRUE;
//		m_bBadOptDelta = VARIANT_TRUE;
//		m_bBadGamma = VARIANT_TRUE;
//		m_bBadGammaPerc = VARIANT_TRUE;
//		m_bBadVega = VARIANT_TRUE;
//		m_bBadWtdVega = VARIANT_TRUE;
//		m_bBadTheta = VARIANT_TRUE;
//		m_bBadDeltaEq = VARIANT_TRUE;
//		m_bBadGammaEq = VARIANT_TRUE;
//		m_bBadRho = VARIANT_TRUE;
//		m_bBadThetaDelta = VARIANT_TRUE;
//		m_bBadThetaGamma = VARIANT_TRUE;
//		m_bBadVegaDelta = VARIANT_TRUE;
//		m_bBadVegaGamma = VARIANT_TRUE;
//		m_bBadTimeValue = VARIANT_TRUE;
//		m_bBadWtdVega = VARIANT_TRUE;
//		m_bBadBetaWtdDeltaEq = VARIANT_TRUE;
//		m_bBadNetGamma = VARIANT_TRUE;
//
//	}
//};
//
///////////////////////////////////////////////////////////////////////////////
////
//class ATL_NO_VTABLE CMmRvUndAtom : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CMmRvUndAtom, &CLSID_MmRvUndAtom>,
//	public ISupportErrorInfoImpl<&IID_IMmRvUndAtom>,
//	public IDispatchImpl<IMmRvUndAtom, &IID_IMmRvUndAtom, &LIBID_EtsMmRisksLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
//	public __MmRvUndAtom
//{
//public:
//	CMmRvUndAtom()
//	{
//	}
//
//DECLARE_REGISTRY_RESOURCEID(IDR_MMRVUNDATOM)
//
//DECLARE_NOT_AGGREGATABLE(CMmRvUndAtom)
//
//BEGIN_COM_MAP(CMmRvUndAtom)
//	COM_INTERFACE_ENTRY(IMmRvUndAtom)
//	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(ISupportErrorInfo)
//END_COM_MAP()
//
//	DECLARE_PROTECT_FINAL_CONSTRUCT()
//
//	HRESULT FinalConstruct()
//	{
//		try
//		{
//			CComObject<CMmRvPosColl>* pObject = NULL;
//			_CHK(CComObject<CMmRvPosColl>::CreateInstance(&pObject), _T("Fail to create positions."));
//			m_spPos.Attach(pObject, TRUE);
//
//			_CHK(m_spVolaSrv.CreateInstance(CLSID_VolaControl), _T("Fail to create volatility control."));
//			_CHK(m_spDividend.CreateInstance(CLSID_EtsIndexDivAtom), _T("Fail to create dividend object"));
//		}
//		catch(const _com_error& e)
//		{
//			return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvUndAtom, e.Error());
//		}
//		return S_OK;
//	}
//	
//	void FinalRelease() 
//	{
//		__MmRvUndAtom::Clear(true);
//	}
//
//private:
//	void _ClearSynthGreeks() throw();
//	void _CalcTotalsForOptionPos(IMmRvPosAtomPtr spPos, DOUBLE dUndPriceMid) throw();
//
//public:
//	
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
//	IMPLEMENT_SIMPLE_PROPERTY(EtsContractTypeEnum, ContractType, m_enContractType)
//	IMPLEMENT_BSTR_PROPERTY(Symbol, m_bstrSymbol)
//
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Yield, m_dYield)
//	//IMPLEMENT_SIMPLE_PROPERTY(LONG, DivFreq, m_nDivFreq)
//	//IMPLEMENT_SIMPLE_PROPERTY(DATE, DivDate, m_dtDivDate)
//	//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DivAmt, m_dDivAmt)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsAmerican, m_bIsAmerican)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsHTB, m_bIsHTB)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, ExpCalendarID, m_nExpCalendarID)
//
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Skew, m_dSkew)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Kurt, m_dKurt)
//
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, CalcGreeks, m_bCalcGreeks)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, CalcTotals, m_bCalcTotals)
//
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, VolaUpdated, m_bVolaUpdated)
//	
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceBid, m_dPriceBid)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetChange, m_dNetChange)
//	
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceAsk, m_dPriceAsk)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceLast, m_dPriceLast)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceClose, m_dPriceClose)
//
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, LotSize, m_nLotSize)
//
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Beta, m_dBeta)
//
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, Qty, m_nQty)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, OptQty, m_nOptQty)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, UndPosForRates, m_dUndPosForRates)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, FutQty, m_nFutQty)
//
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlMtm, m_dPnlMtm)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlTheo, m_dPnlTheo)
//
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetDelta, m_dNetDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, OptDelta, m_dOptDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Gamma, m_dGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaPerc, m_dGammaPerc)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Vega, m_dVega)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, WtdVega, m_dWtdVega)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Theta, m_dTheta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DeltaEq, m_dDeltaEq)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaEq, m_dGammaEq)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Rho, m_dRho)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaDelta, m_dThetaDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ThetaGamma, m_dThetaGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaDelta, m_dVegaDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaGamma, m_dVegaGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, TimeValue, m_dTimeValue)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, BetaWtdDeltaEq, m_dBetaWtdDeltaEq)
//
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadPnlMtm, m_bBadPnlMtm)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadPnlTheo, m_bBadPnlTheo)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetDelta, m_bBadNetDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadOptDelta, m_bBadOptDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadGamma, m_bBadGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadGammaPerc, m_bBadGammaPerc)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadVega, m_bBadVega)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadWtdVega, m_bBadWtdVega)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadTheta, m_bBadTheta)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadDeltaEq, m_bBadDeltaEq)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadGammaEq, m_bBadGammaEq)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadRho, m_bBadRho)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadThetaDelta, m_bBadThetaDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadThetaGamma, m_bBadThetaGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadVegaDelta, m_bBadVegaDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadVegaGamma, m_bBadVegaGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadTimeValue, m_bBadTimeValue)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadBetaWtdDeltaEq, m_bBadBetaWtdDeltaEq)
//
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IMmRvPosColl*, Pos, m_spPos)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HasOptPos, m_bHasOptPos)
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IVolaControl*, VolaSrv, m_spVolaSrv)
//
//	IMPLEMENT_OBJECT_PROPERTY(IIndexAtom*, BasketIndex, m_spBasketIndex)
//
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, UseMidRates, m_bUseMidRates)
//
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HasSynthetic, m_bHasSynthetic)
//
//	IMPLEMENT_OBJECT_PROPERTY(ISynthRootColl*, SynthRoots, m_spSynthRoots)
//	IMPLEMENT_OBJECT_PROPERTY(IMmRvSynthGreeksColl*, SynthGreeks, m_spSynthGreeks)
//	IMPLEMENT_OBJECT_PROPERTY(IMmRvPosColl*, SynthPos, m_spSynthPos)
//	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, UndPriceProfile, m_spUndPriceProfile)
//	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, OptPriceProfile, m_spOptPriceProfile)
//	IMPLEMENT_SIMPLE_PROPERTY(EtsReplacePriceStatusEnum, ReplacePriceStatus, m_enReplacePriceStatus)
//
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetGamma, m_dNetGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetGamma, m_bBadNetGamma)
//
//	IMPLEMENT_OBJECT_PROPERTY(IMmRvFutColl*, Fut, m_spFut)
//	IMPLEMENT_OBJECT_PROPERTY(IEtsIndexDivAtom*, Dividend, m_spDividend)
//
//	STDMETHODIMP Clear()
//	{
//		__MmRvUndAtom::Clear(false);
//		return S_OK;
//	}
//
//	STDMETHODIMP ClearValues()
//	{
//		__MmRvUndAtom::ClearValues();
//		return S_OK;
//	}
//
//	STDMETHODIMP SetAllValuesAsBad()
//	{
//		__MmRvUndAtom::SetAllValuesAsBad();
//		return S_OK;
//	}
//
//	STDMETHOD(GetSyntheticUnderlyingPrice)(IMmRvUndColl* aUndColl,
//											ISynthRootAtom* aSynthRoot,
//											DOUBLE* pdSynthBid,
//											DOUBLE* pdSynthAsk,
//											DOUBLE* pdSynthLast);
//
//	STDMETHOD(Calc)(IMmRvUndColl* aUndColl,
//					LONG nMask,
//					VARIANT_BOOL bCalcGreeks,
//					VARIANT_BOOL bUpdateVola,
//					VARIANT_BOOL bRealtimeCalc,
//					VARIANT_BOOL bClearSynthGreeks,
//					IEtsProcessDelay* aDelay,
//					VARIANT_BOOL bIsPnlLTD,
//					EtsCalcModelTypeEnum enCalcModel,
//					VARIANT_BOOL bUseTheoVolatility,
//					VARIANT_BOOL bUseTheoVolaNoBid,
//					VARIANT_BOOL bUseTheoVolaBadMarket,
//					DOUBLE dUndPriceTolerance,
//					EtsPriceRoundingRuleEnum enPriceRoundingRule,
//					LONG* pnOptUpdated,
//					LONG* pnUndUpdated,
//					LONG* pnFutUpdated);
//
//	STDMETHOD(CalcWtdVega)(IEtsExpCalColl* aExpCalColl);
//
//	STDMETHOD(CalcSyntheticUnderlying)(IMmRvUndColl* aUndColl,
//										LONG nMask,
//										VARIANT_BOOL bIsPnlLTD,
//										EtsCalcModelTypeEnum enCalcModel,
//										VARIANT_BOOL bUseTheoVolatility,
//										VARIANT_BOOL bUseTheoVolaNoBid,
//										VARIANT_BOOL bUseTheoVolaBadMarket,
//										DOUBLE dUndPriceTolerance,
//										EtsPriceRoundingRuleEnum enPriceRoundingRule);
//};
//
//OBJECT_ENTRY_AUTO(__uuidof(MmRvUndAtom), CMmRvUndAtom)
//
//#endif //__MMRVUNDATOM_H__