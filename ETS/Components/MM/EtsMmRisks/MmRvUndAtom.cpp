// MmRvUndAtom.cpp : Implementation of CMmRvUndAtom+

#include "stdafx.h"
#include "MmRvUndAtom.h"
#include "MmRvUndColl.h"
#include <algorithm>
#include <functional>
#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>

using namespace std;
using namespace boost;

const WCHAR* CMmRvUndAtom::bsMonth[12] ={
	L"Jan",
	L"Feb",
	L"Mar",
	L"Apr",
	L"May",
	L"Jun",
	L"Jul",
	L"Aug",
	L"Sep",
	L"Oct",
	L"Nov",
	L"Dec"
};

/*
DATE GetDateWitOutDayOfMonth( DATE dtExpiration)
{
	SYSTEMTIME st ;//= _dtExparation ;
	::VariantTimeToSystemTime ( dtExpiration, &st);
	st.wDay = 1 ;
	SystemTimeToVariantTime ( &st , &dtExpiration) ;
	return dtExpiration ;
}*/


void __MmRvUndAtom::AddPosToAggregations( MmRvPosAtomPtr& pPos){
	CComBSTR						bstrFutName;
	_bstr_t						aggName, intName;
	CMmRvAggData*				pAgg, *pAggExp;
	unsigned					cntrAggregations = 0;
	
	if (!pPos) return;

	// first, add position to aggregations of this underlying
	pPos->AggregationsPtr_[cntrAggregations++] = static_cast<CMmRvAggData*>(this);
	intName = Name_;
	// try to find appropriate aggregation by future for this position
	if (pPos->m_spFut){									// if we have future related for this position
		pPos->m_spFut->get_Symbol(&bstrFutName);	// get it name
		aggName = bstrFutName;

		// try to find future aggregation
		Aggregations::iterator itrCrnt = Aggregations_.begin();
		for ( Aggregations::iterator itrEnd = Aggregations_.end(); itrCrnt != itrEnd; ++itrCrnt ) 
			if ( (*itrCrnt)->Name_ == aggName ) 
				break;

		if (itrCrnt == Aggregations_.end() ) {
			// future aggregation for this position hasn't been created yet, do this now
			pAgg = new CMmRvAggData(CMmRvAggData::enFutAgg, aggName );

			pAgg->pFut_ = static_cast<CMmRvFutAtom*>(pPos->m_spFut.GetInterfacePtr());
			pAgg->pUnd_ = static_cast<CMmRvUndAtom*>(this);
			intName = pAgg->internalName_ = intName + aggName;			// underlying symbol + future symbol
			Aggregations_.push_back(MmRvAggDataPtr(pAgg));
		}
		else
			pAgg = (*itrCrnt).get();
		pPos->AggregationsPtr_[cntrAggregations++] = pAgg;
	}
	else{
		//pAgg = static_cast<CMmRvAggData*>(this);	// no related future for this position
		//															// add it directly to underlying or expiry aggregation 
		//															// for this underlying
		Positions_.push_back(pPos);
		return;
	}
	if (pPos->m_dtExpiry ) {		// if position has expiry date  ( i.e. it's a kind of option position )
		// get appropriate expiry aggregation name
		CMmRvUndAtom::Date2Text(pPos->m_dtExpiry, aggName);

		// try to find expiry aggregation for this option position within aggregation pointed by pAgg
		// (it's a future aggregation or underlying itself)
		Aggregations::iterator itrCrnt = pAgg->Aggregations_.begin();
		for ( Aggregations::iterator itrEnd = pAgg->Aggregations_.end(); itrCrnt != itrEnd; ++itrCrnt ) 
			if ( (*itrCrnt)->Name_ == aggName ) 
				break;

		if (itrCrnt == pAgg->Aggregations_.end() ) {
			// expiry aggregation for this position hasn't been created yet, do this now
			pAggExp =  new CMmRvAggData(CMmRvAggData::enExpAgg, aggName );
			pAgg->Aggregations_.push_back(MmRvAggDataPtr(pAggExp));
			pAgg->pUnd_ = static_cast<CMmRvUndAtom*>(this);
			pAggExp->internalName_ = intName + aggName;
			pAgg = pAggExp;
		}
		else
			pAgg = (*itrCrnt).get();
		pPos->AggregationsPtr_[cntrAggregations] = pAgg;
	}

	// add position to appropriate aggregation
	pAgg->Positions_.push_back( pPos );
}
void __MmRvUndAtom::AggregatePosition(CMmRvPosAtom* pPos, double underlyingPtrice,DOUBLE dUndPriceTolerance, EtsPriceRoundingRuleEnum enPriceRoundingRule){

	AggregatePositionQuantity(pPos);
	AggregatePositionDeltas(pPos);
	AggregatePositionGammas(pPos, underlyingPtrice, dUndPriceTolerance, enPriceRoundingRule);
	AggregatePositionPnLs(pPos);
	AggregatePositionVegas(pPos);
	AggregatePositionThetas(pPos);
	AggregatePositionRhos(pPos);
	AggregatePositionTmVal(pPos);
}

void __MmRvUndAtom::AggregatePositionQuantity(CMmRvPosAtom* pPos){
	if ( !IsBadValue(pPos->m_nQty) && pPos->AggregationsPtr_[0] ){
		// if we have quantity in position and where to aggregate it
		for (unsigned i = 0; i < 3 && pPos->AggregationsPtr_[i]; ++i ) {
			switch(pPos->m_enContractType) {
				case enCtFutOption:
				case enCtOption:
					if( IsBadValue(pPos->AggregationsPtr_[i]->OptQty_) )
						pPos->AggregationsPtr_[i]->OptQty_ = 0;
					pPos->AggregationsPtr_[i]->OptQty_ += pPos->m_nQty;		// aggregate options quantity
					break;
				case enCtFuture:
					if( IsBadValue(pPos->AggregationsPtr_[i]->FutQty_) )
						pPos->AggregationsPtr_[i]->FutQty_ = 0;
					pPos->AggregationsPtr_[i]->FutQty_ += pPos->m_nQty;		// aggregate futures quantity
					if (/*pPos->AggregationsPtr_[i]->Type_ != enUndAgg &&*/ pPos->m_pQuote && !IsBadValue(pPos->m_pQuote->m_nLotSize) ) {
						if( IsBadValue(pPos->AggregationsPtr_[i]->UndPos_) )
							pPos->AggregationsPtr_[i]->UndPos_ = 0;
						pPos->AggregationsPtr_[i]->UndPos_ += (pPos->m_nQty * pPos->m_pQuote->m_nLotSize);	// adjust underlying position
					}
					break;
				default:
					/*if (pPos->AggregationsPtr_[i]->Type_ != enUndAgg )*/ {		// do not aggregate in underlying aggregation
						if( IsBadValue(pPos->AggregationsPtr_[i]->UndPos_) )
							pPos->AggregationsPtr_[i]->UndPos_ = 0;
						pPos->AggregationsPtr_[i]->UndPos_ += pPos->m_nQty;		// aggregate underlying quantity
					}
					break;
			}
		}
	}
}

void __MmRvUndAtom::AggregatePositionDeltas(CMmRvPosAtom* pPos){
	if ( !IsBadValue(pPos->m_dDeltaInShares) && pPos->AggregationsPtr_[0] && pPos->m_dDeltaInShares){
		// if we have delta in position and where to aggregate it
		for (unsigned i = 0; i < 3 && pPos->AggregationsPtr_[i]; ++i ) {
			// aggregate option delta
			if (IsBadValue(pPos->AggregationsPtr_[i]->OptDlt_) ) 
				pPos->AggregationsPtr_[i]->OptDlt_ = 0.;
			pPos->AggregationsPtr_[i]->OptDlt_ += pPos->m_dDeltaInShares;

			if (IsBadValue(pPos->AggregationsPtr_[i]->OptDlt$_) ) 
				pPos->AggregationsPtr_[i]->OptDlt$_ = 0.;
			pPos->AggregationsPtr_[i]->OptDlt$_ += pPos->m_dDeltaEq;

			if (IsBadValue(pPos->AggregationsPtr_[i]->NetExposure_) ) 
				pPos->AggregationsPtr_[i]->NetExposure_ = 0.;
			pPos->AggregationsPtr_[i]->NetExposure_ += pPos->m_dNetExposure;
		}
	}
}

void __MmRvUndAtom::AggregatePositionGammas(CMmRvPosAtom* pPos, double underlyingPtrice, DOUBLE dUndPriceTolerance, EtsPriceRoundingRuleEnum enPriceRoundingRule){
	if ( !IsBadValue(pPos->m_dGammaInShares) && pPos->AggregationsPtr_[0] && pPos->m_dGammaInShares){
		// if we have gamma in position and where to aggregate it
		for (unsigned i = 0; i < 3 && pPos->AggregationsPtr_[i]; ++i ) {
			// aggregate gamma1%
			double undPrice;
			if (IsBadValue(pPos->AggregationsPtr_[i]->Gma1P_) ) 
				pPos->AggregationsPtr_[i]->Gma1P_ = 0.;
			if(m_enContractType == enCtFutUnd && pPos){
				EtsReplacePriceStatusEnum penPriceStatus;	VARIANT_BOOL dummy;
				CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(pPos->m_spFut.GetInterfacePtr() );
				if( pFut ){
					try{	
						// NOTE: pPos->m_dGammaInShares already multiplied by FutureContractSize
						// if this needed
						pFut->GetFuturePrice(dUndPriceTolerance, enPriceRoundingRule, &penPriceStatus, &dummy, &undPrice ); 	
						if (IsBadValue(undPrice) || !undPrice)
							continue;
						// aggregate gamma1%
						pPos->AggregationsPtr_[i]->Gma1P_ += (pPos->m_dGammaInShares * undPrice / 100.);
						// aggregate net gamma$
						if (!IsBadValue(undPrice) && undPrice && pPos->m_pQuote) {
							if (IsBadValue(pPos->AggregationsPtr_[i]->NetGma$_) ) 
								pPos->AggregationsPtr_[i]->NetGma$_ = 0.;
							pPos->AggregationsPtr_[i]->NetGma$_ += (pPos->m_pQuote->m_dGamma * pPos->m_nQty * undPrice * undPrice / 100. * pFut->m_dKEq);
						}
						// aggregate gamma 1$
						if (IsBadValue(pPos->AggregationsPtr_[i]->Gma1$_) )
							pPos->AggregationsPtr_[i]->Gma1$_ = 0.;
						pPos->AggregationsPtr_[i]->Gma1$_+= pPos->m_dGammaInShares;
					}
					catch(...){}
				}
			}
			else{
				// aggregate gamma 1$
				if (IsBadValue(pPos->AggregationsPtr_[i]->Gma1$_) )
					pPos->AggregationsPtr_[i]->Gma1$_ = 0.;
				pPos->AggregationsPtr_[i]->Gma1$_ += pPos->m_dGammaInShares;

				if (IsBadValue(underlyingPtrice) || !underlyingPtrice)
					continue;

				// aggregate gamma1%
				pPos->AggregationsPtr_[i]->Gma1P_ += pPos->m_dGammaInShares * underlyingPtrice / 100.;
				
				// aggregate net gamma$
				if (IsBadValue(pPos->AggregationsPtr_[i]->NetGma$_) ) 
					pPos->AggregationsPtr_[i]->NetGma$_ = 0.;
				pPos->AggregationsPtr_[i]->NetGma$_ += (pPos->m_dGammaInShares * underlyingPtrice* underlyingPtrice/100.);
			}
		}
	}
}

void __MmRvUndAtom::AggregatePositionPnLs(CMmRvPosAtom* pPos){
	for (unsigned i = 0; i < 3 && pPos->AggregationsPtr_[i]; ++i ) {
		bool  goodTheo = false, goodMTM = false;
		if ( !IsBadValue(pPos->m_dPnlMtm) /*&& DoubleNEQZero(pPos->m_dPnlMtm)*/ ) {
			if (IsBadValue(pPos->AggregationsPtr_[i]->PnlMTM_) )
				pPos->AggregationsPtr_[i]->PnlMTM_ = 0.;
			pPos->AggregationsPtr_[i]->PnlMTM_ += pPos->m_dPnlMtm;
			goodMTM = true;
		}
		if ( !IsBadValue(pPos->m_dPnlTheo) /*&& DoubleNEQZero(pPos->m_dPnlTheo)*/ ) {
			if (IsBadValue(pPos->AggregationsPtr_[i]->PnLTheo_) )
				pPos->AggregationsPtr_[i]->PnLTheo_ = 0.;
			pPos->AggregationsPtr_[i]->PnLTheo_ += pPos->m_dPnlTheo;
			goodTheo = true;
		}
		

		double tmpTheo = IsBadValue(pPos->AggregationsPtr_[i]->PnLTheo_) ? 0. : pPos->AggregationsPtr_[i]->PnLTheo_;
		double tmpMTM = IsBadValue(pPos->AggregationsPtr_[i]->PnlMTM_) ? 0. : pPos->AggregationsPtr_[i]->PnlMTM_;

		if ( goodTheo && goodMTM ) {
			if (IsBadValue(pPos->AggregationsPtr_[i]->PnlEdge_) )
				pPos->AggregationsPtr_[i]->PnlEdge_ = 0.;
			pPos->AggregationsPtr_[i]->PnlEdge_ += (pPos->m_dPnlTheo /*tmpTheo*/- pPos->m_dPnlMtm/*tmpMTM*/);
		}
	}
}
void __MmRvUndAtom::AggregatePositionVegas(CMmRvPosAtom* pPos)
{
	for (unsigned i = 0; i < 3 && pPos->AggregationsPtr_[i]; ++i ) 
	{
		// aggregate Vega$
		// NOTE: pPos->m_dVegaInShares is already Vega * OptQty * (* CSz if !enCtFutUnd) * (* K if == enCtFutUnd)
		if (!IsBadValue(pPos->m_dVegaInShares))
		{
			if (IsBadValue(pPos->AggregationsPtr_[i]->Vga$_)) 
				pPos->AggregationsPtr_[i]->Vga$_= 0.;
			pPos->AggregationsPtr_[i]->Vga$_ += pPos->m_dVegaInShares;
		}

		// aggregate WtdVga
		// NOTE: pPos->m_dWtdVega is already (Weight of Vega) * Vega * OptQty * (* CSz if !enCtFutUnd) * (* K if == enCtFutUnd)
		if (!IsBadValue(pPos->m_dWtdVega))
		{
			if (IsBadValue(pPos->AggregationsPtr_[i]->WtdVga$_)) 
				pPos->AggregationsPtr_[i]->WtdVga$_= 0.;
			pPos->AggregationsPtr_[i]->WtdVga$_ += pPos->m_dWtdVega;
		}

		// aggregate VegaGma
		if (!IsBadValue(pPos->m_dVegaGammaInShares))
		{
			if (IsBadValue(pPos->AggregationsPtr_[i]->VgaGma_)) 
				pPos->AggregationsPtr_[i]->VgaGma_= 0.;
			pPos->AggregationsPtr_[i]->VgaGma_ += pPos->m_dVegaGammaInShares;
		}

		// aggregate VegaDlt
		if (!IsBadValue(pPos->m_dVegaDeltaInShares))
		{
			if (IsBadValue(pPos->AggregationsPtr_[i]->VgaDlt_)) 
				pPos->AggregationsPtr_[i]->VgaDlt_ = 0.;
			pPos->AggregationsPtr_[i]->VgaDlt_ += pPos->m_dVegaDeltaInShares;
		}
	}
}
void __MmRvUndAtom::AggregatePositionThetas(CMmRvPosAtom* pPos)
{
	for (unsigned i = 0; i < 3 && pPos->AggregationsPtr_[i]; ++i ) 
	{
		// aggregate Theta$
		// NOTE: pPos->m_dThetaInShares is already Theta * OptQty * (* CSz if !enCtFutUnd) * (* K if == enCtFutUnd)
		if(!IsBadValue(pPos->m_dThetaInShares))
		{
			if (IsBadValue(pPos->AggregationsPtr_[i]->Tht$_)) 
				pPos->AggregationsPtr_[i]->Tht$_= 0.;
			pPos->AggregationsPtr_[i]->Tht$_ += pPos->m_dThetaInShares;
		}

		// aggregate ThtDlt
		if(!IsBadValue(pPos->m_dThetaDeltaInShares))
		{
			if (IsBadValue(pPos->AggregationsPtr_[i]->ThtDlt_)) 
				pPos->AggregationsPtr_[i]->ThtDlt_= 0.;
			pPos->AggregationsPtr_[i]->ThtDlt_ += pPos->m_dThetaDeltaInShares;
		}

		// aggregate ThtGma
		if(!IsBadValue(pPos->m_dThetaGammaInShares))
		{
			if (IsBadValue(pPos->AggregationsPtr_[i]->ThtGma_)) 
				pPos->AggregationsPtr_[i]->ThtGma_= 0.;
			pPos->AggregationsPtr_[i]->ThtGma_ += pPos->m_dThetaGammaInShares;
		}
	}
}
void __MmRvUndAtom::AggregatePositionRhos(CMmRvPosAtom* pPos)
{
	for (unsigned i = 0; i < 3 && pPos->AggregationsPtr_[i]; ++i ) 
	{
		// aggregate Rho$
		// NOTE: pPos->m_dRhoInShares is already Rho * OptQty * (* CSz if !enCtFutUnd) * (* K if == enCtFutUnd)
		if (!IsBadValue(pPos->m_dRhoInShares))
		{
			if (IsBadValue(pPos->AggregationsPtr_[i]->Rho$_))
				pPos->AggregationsPtr_[i]->Rho$_= 0.;
			pPos->AggregationsPtr_[i]->Rho$_ += pPos->m_dRhoInShares;
		}
	}
}
void __MmRvUndAtom::AggregatePositionTmVal(CMmRvPosAtom* pPos)
{
	for (unsigned i = 0; i < 3 && pPos->AggregationsPtr_[i]; ++i ) {
		/*if(m_enContractType == enCtFutUnd)
		{}
		else*/
		if (!IsBadValue(pPos->m_dTimeValue))	{
			if (IsBadValue(pPos->AggregationsPtr_[i]->TmVal_))
				pPos->AggregationsPtr_[i]->TmVal_= 0.;
			pPos->AggregationsPtr_[i]->TmVal_ += pPos->m_dTimeValue;
			if (IsBadValue(pPos->AggregationsPtr_[i]->TmValInShares_))
				pPos->AggregationsPtr_[i]->TmValInShares_= 0.;
			TmValInShares_ += (pPos->m_dTimeValue*pPos->m_nQtyInShares);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmRvUndAtom::GetSyntheticUnderlyingPrice(IMmRvUndColl* aUndColl,
																		 ISynthRootAtom* aSynthRoot,
																		 DOUBLE* pdSynthBid,
																		 DOUBLE* pdSynthAsk,
																		 DOUBLE* pdSynthLast)
{
	if(aUndColl == NULL)
		return Error(L"Invalid object passed.", IID_IMmRvUndAtom, E_INVALIDARG);

	__CHECK_POINTER(pdSynthBid);
	__CHECK_POINTER(pdSynthAsk);
	__CHECK_POINTER(pdSynthLast);

	*pdSynthBid = BAD_DOUBLE_VALUE;
	*pdSynthAsk = BAD_DOUBLE_VALUE;
	*pdSynthLast = BAD_DOUBLE_VALUE;

	if(!m_bHasSynthetic || m_spSynthRoots == NULL || aSynthRoot == NULL)
		return S_OK;

	try
	{
		IUnknownPtr spUnk;
		_variant_t varItem;
		ULONG nFetched = 0L;
		HRESULT hr;

		ISynthRootAtomPtr spSynthRoot(aSynthRoot);

		IMmRvUndCollPtr spUndColl(aUndColl);
		IMmRvUndAtomPtr spSynthUnd;

		bool bBadSpotBid = false, bBadSpotAsk = false, bBadSpotLast = false;


		*pdSynthBid = spSynthRoot->CashValue;
		*pdSynthAsk = *pdSynthBid;
		*pdSynthLast = *pdSynthBid;

		ISynthRootCompAtomPtr spSRComp;
		ISynthRootCompCollPtr spSRCompColl;

		spSRCompColl = spSynthRoot->SynthRootComponents;


		_CHK(spSRCompColl->get__NewEnum(&spUnk), _T("Fail to get synthetic underlying component collection enum."));
		IEnumVARIANTPtr spSynthRootEnum(spUnk);
		_CHK(spSynthRootEnum->Reset(), _T("Fail to reset synthetic underlying component collection."));
		while((hr = spSynthRootEnum->Next(1L, &varItem, &nFetched)) == S_OK)
		{
			ATLASSERT(varItem.vt == VT_DISPATCH);
			spSRComp = varItem;
			if(spSRComp != NULL)
			{
				LONG nUndID = 0L;
				DOUBLE dWeight = 0.;
				DOUBLE dPrice = 0.;

				nUndID = spSRComp->UndID;
				_CHK(spUndColl->get_Item(nUndID, &spSynthUnd), _T("Fail to get synthetic underlying."));
				IMmRvAggregationDataAtomPtr spSynthUndData(spSynthUnd);
				if(spSynthUnd != NULL && spSynthUndData!=NULL)
				{
					dWeight = spSRComp->Weight;
					IMmRvPricePtr spPrice;
					_CHK(spSynthUndData->get_Price(&spPrice));


					_CHK(spPrice->get_Bid(&dPrice));
					if(!bBadSpotBid && dPrice > DBL_EPSILON)
						*pdSynthBid += dPrice * dWeight;
					else
					{
						bBadSpotBid = true;
						*pdSynthBid = BAD_DOUBLE_VALUE;
					}

					_CHK(spPrice->get_Ask(&dPrice));
					if(!bBadSpotAsk && dPrice > DBL_EPSILON)
						*pdSynthAsk += dPrice * dWeight;
					else
					{
						bBadSpotAsk = true;
						*pdSynthAsk = BAD_DOUBLE_VALUE;
					}

					_CHK(spPrice->get_Last(&dPrice));
					if(!bBadSpotLast && dPrice > DBL_EPSILON)
						*pdSynthLast += dPrice * dWeight;
					else
					{
						bBadSpotLast = true;
						*pdSynthLast = BAD_DOUBLE_VALUE;
					}
				}
			}
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvUndAtom, e.Error());
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmRvUndAtom::Calc(IMmRvUndColl* aUndColl,
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
										  DATE dtCalcDate)
{
	if(aUndColl == NULL)
		return Error(L"Invalid object passed.", IID_IMmRvUndAtom, E_INVALIDARG);
	try
	{
		IMmRvUndCollPtr spUndColl(aUndColl);

		//IUnknownPtr spUnk;
		//_variant_t varItem;
		ULONG nFetched = 0L;
		LONG nOptUpdated = 0L, nUndUpdated = 0L, nFutUpdated = 0L;

		IEtsProcessDelayPtr spDelay(aDelay);
		if(spDelay != NULL && spDelay->IsInterrupted)
			return S_OK;

		if(bUpdateVola)
			bCalcGreeks = VARIANT_TRUE;

		//__MmRvUndAtom::ClearValues();
		ClearAggregatedValues();
		if(bClearSynthGreeks)
			_ClearSynthGreeks();

		EtsReplacePriceStatusEnum enUndPriceStatusMid = enRpsNone;
		EtsReplacePriceStatusEnum enUndPriceStatusBid = enRpsNone;
		EtsReplacePriceStatusEnum enUndPriceStatusAsk = enRpsNone;
		DOUBLE dUndPriceMid = 0., dUndPriceBid = 0., dUndPriceAsk = 0.;
		DOUBLE dActiveFutureMid = 0., dActiveFutureBid = 0., dActiveFutureAsk = 0., dActiveFutureLast = 0.;
		DOUBLE dActiveFutureBasis = 0.;

		if(m_spUndPriceProfile != NULL)
		{
			dUndPriceMid = m_spUndPriceProfile->GetUndPriceMid(m_pPrice->m_dPriceBid, m_pPrice->m_dPriceAsk,
				m_pPrice->m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enUndPriceStatusMid, VARIANT_FALSE);

			dUndPriceBid = m_spUndPriceProfile->GetUndPriceBidForPnL(m_pPrice->m_dPriceBid, m_pPrice->m_dPriceAsk,
				m_pPrice->m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enUndPriceStatusBid);

			dUndPriceAsk = m_spUndPriceProfile->GetUndPriceAskForPnL(m_pPrice->m_dPriceBid, m_pPrice->m_dPriceAsk,
				m_pPrice->m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enUndPriceStatusAsk);
		}

		m_enReplacePriceStatus = static_cast<EtsReplacePriceStatusEnum>(enUndPriceStatusMid | enUndPriceStatusBid | enUndPriceStatusAsk);

		if (NULL != m_spActiveFuture )
		{
			IEtsPriceProfileAtomPtr spUndPriceProfile;

			m_spActiveFuture->get_UndPriceProfile(&spUndPriceProfile);
			if ( NULL != spUndPriceProfile)
			{
				IMmRvPricePtr spFutPrice;
				_CHK(m_spActiveFuture->get_Price(&spFutPrice));

				_CHK(m_spActiveFuture->get_Basis(&dActiveFutureBasis));
				_CHK(spFutPrice->get_Bid(&dActiveFutureBid) );
				_CHK(spFutPrice->get_Ask(&dActiveFutureAsk) );
				_CHK(spFutPrice->get_Last(&dActiveFutureLast) );
				dActiveFutureMid = spUndPriceProfile->GetUndPriceMid(dActiveFutureBid, dActiveFutureAsk,
					dActiveFutureLast, dUndPriceTolerance, enPriceRoundingRule, &enUndPriceStatusMid, VARIANT_FALSE);

				if ( dActiveFutureMid > 0.)
				{
					if(dActiveFutureBasis>BAD_DOUBLE_VALUE)
						dActiveFutureMid += dActiveFutureBasis;
					//spFutPrice->put_Active(dActiveFutureMid);
					dUndPriceMid = dActiveFutureMid;
				}
			}
		}
		if (!m_pPrice->m_bManualActive) m_pPrice->m_dActivePrice = dUndPriceMid;
			else dUndPriceMid = m_pPrice->m_dActivePrice;


		//DATE dtToday = vt_date::GetCurrentDate(true);
		VARIANT_BOOL bNeedRecalc = VARIANT_FALSE;
		VARIANT_BOOL bPosCalcGreeks = VARIANT_FALSE;
		VARIANT_BOOL bCalcTheos = VARIANT_FALSE;
		DOUBLE dPosValue = BAD_DOUBLE_VALUE;

		bool bHasItems = false;
		CMmRvPosColl::EnumCollType::iterator itrPos    = m_pPos->m_coll.begin();
		const CMmRvPosColl::EnumCollType::iterator itrPosEnd = m_pPos->m_coll.end();
		if(!m_pPos->m_coll.empty())
			bHasItems = true;
		double underlyingPriceSave = dUndPriceMid;

		for(;itrPos!=itrPosEnd; ++itrPos)
		{
			dUndPriceMid = underlyingPriceSave;
			CMmRvPosAtom* pPos = dynamic_cast<CMmRvPosAtom*>(itrPos->second);

			if(pPos != NULL)
			{
				if(pPos->m_bVisible)
				{
					EtsContractTypeEnum enContractType = pPos->m_enContractType;
					LONG nPosQty = pPos->m_nQty;
					LONG nPosQtyInShares = pPos->m_nQtyInShares;

					// options
					if(enContractType == enCtOption || enContractType == enCtFutOption)
					{
						//if(OptQty_ <= BAD_LONG_VALUE) OptQty_ = 0L;
						//OptQty_ += nPosQty;

						DATE dtExpiry = pPos->m_dtExpiry;
						DOUBLE dStrike = pPos->m_dStrike;

						if(dtExpiry > dtCalcDate )
						{
							bPosCalcGreeks = pPos->m_bCalcGreeks;

							if(bRealtimeCalc)
							{
								bCalcTheos = m_bCalcGreeks || m_bCalcTotals || bPosCalcGreeks;

								if(!bCalcTheos && enContractType == enCtFutOption)
								{
									IMmRvFutAtomPtr spFut = pPos->m_spFut;

									if(spFut != NULL)
									{
										VARIANT_BOOL bFutCalcGreeks = VARIANT_FALSE;
										_CHK(spFut->get_CalcGreeks(&bFutCalcGreeks));
										bCalcTheos = bCalcTheos || bFutCalcGreeks;
									}
								}

								bUpdateVola = m_bCalcGreeks;
								bNeedRecalc = m_bCalcTotals;
							}
							else
							{
								bCalcTheos = bCalcGreeks;
								bNeedRecalc = VARIANT_TRUE;
							}

							if(bNeedRecalc)
							{
								nOptUpdated++;

								if(bUpdateVola)
								{
									if(pPos->m_spQuote!=NULL)
										_CHK(pPos->m_spQuote->put_Vola(m_spVolaSrv->GetOptionVola(dtExpiry, dStrike)));
								}

								if(enContractType == enCtOption)
								{
									_CHK(pPos->CalcOptionGreeks(spUndColl, this, dUndPriceMid,
										(bCalcTheos ? nMask : GT_NOTHING), bIsPnlLTD, enCalcModel,
										bUseTheoVolatility, bUseTheoVolaNoBid, bUseTheoVolaBadMarket,
										dUndPriceTolerance, enPriceRoundingRule,dtCalcDate));
								}
								else
								{
									/*if (NULL != m_spActiveFuture )
									{
										VARIANT_BOOL bFutPriceReplaced = VARIANT_FALSE;
										pPos->m_spFut->GetFuturePrice(dUndPriceTolerance,
											enPriceRoundingRule, &enUndPriceStatusMid, &bFutPriceReplaced, &dUndPriceMid);
									}*/

									_CHK(pPos->CalcFutOptionGreeks(this, dUndPriceMid,
										(bCalcTheos ? nMask : GT_NOTHING), bIsPnlLTD, enCalcModel,
										bUseTheoVolatility, bUseTheoVolaNoBid, bUseTheoVolaBadMarket,
										dUndPriceTolerance, enPriceRoundingRule,dtCalcDate));
								}

								if(spDelay != NULL)
									spDelay->Sleep();
							}

							if ( m_enContractType == enCtFutUnd && pPos->m_spFut ) {
								// we have no price for this underlying, use 
								// price of future
								VARIANT_BOOL futureUsed = VARIANT_FALSE;
								EtsReplacePriceStatusEnum enFutPriceStatusMid = enRpsNone;
								_CHK(pPos->m_spFut->GetFuturePrice(dUndPriceTolerance, enPriceRoundingRule, &enFutPriceStatusMid, &futureUsed, &dUndPriceMid));
							}
							_CalcTotalsForOptionPos(pPos);
						}
						else
						{

							if(nMask != GT_NOTHING)
							{
								if(nMask & GT_THEOPRICE)
									pPos->m_pQuote->m_dPriceTheo = 0;

								if((nMask & GT_DELTA))
								{
									pPos->m_pQuote->m_dDelta = 0.0;
									if(pPos->m_enOptType == enOtPut && dUndPriceMid < pPos->m_dStrike)
										pPos->m_pQuote->m_dDelta = -1.;

									if(pPos->m_enOptType == enOtCall && dUndPriceMid > pPos->m_dStrike)
										pPos->m_pQuote->m_dDelta = 1.;
								}

								if(nMask & GT_GAMMA) pPos->m_pQuote->m_dGamma = 0;
								if(nMask & GT_THETA) pPos->m_pQuote->m_dTheta = 0;
								if(nMask & GT_VEGA)  pPos->m_pQuote->m_dVega  = 0;
								if(nMask & GT_RHO)   pPos->m_pQuote->m_dRho	  = 0;
								if(nMask & GT_DELTA_VEGA) pPos->m_pQuote->m_dVegaDelta = 0;
								if(nMask & GT_GAMMA_VEGA) pPos->m_pQuote->m_dVegaGamma = 0;
								if(nMask & GT_DELTA_THETA) pPos->m_pQuote->m_dThetaDelta = 0;
								if(nMask & GT_GAMMA_THETA) pPos->m_pQuote->m_dThetaGamma = 0;

								if(enContractType == enCtOption)
								{
									ISynthRootAtomPtr spSynthRoot;
									if(pPos->m_bIsSynthetic && m_spSynthRoots != NULL)
											spSynthRoot = m_spSynthRoots->Item[pPos->m_nOptionRootID];

									pPos->_CalcOptPositionData(m_spOptPriceProfile,
															   spSynthRoot,
															   bIsPnlLTD,
															   bUseTheoVolatility,
															   bUseTheoVolaNoBid,
															   bUseTheoVolaBadMarket,
															   dUndPriceTolerance,
															   enPriceRoundingRule, 
															   spUndColl,
															   dUndPriceMid,
															   m_nID, 
															   dtCalcDate);
								}
								else
								{
									pPos->_CalcFutPositionData(m_spOptPriceProfile,
										bIsPnlLTD,
										bUseTheoVolatility,
										bUseTheoVolaNoBid,
										bUseTheoVolaBadMarket,
										dUndPriceTolerance,
										enPriceRoundingRule, 
										dUndPriceMid,
										dtCalcDate,
										m_enContractType);

								}

								_CalcTotalsForOptionPos(pPos);

							}

							pPos->put_LogEnhansement ( L"The option is expired" ) ;

							WCHAR strparam[200] ;
							_snwprintf_s ( strparam, sizeof(strparam), L"Expiration Date %f" , dtExpiry  ) ;

							IRvMmQuoteAtomPtr spQuote = pPos->m_spQuote;

							if(spQuote!=NULL)
								spQuote->put_VolaCalculatedParametrs( strparam ) ;

							__MmRvUndAtom::SetAllValuesAsBad();
						}
					}

					// underlyings
					else if(enContractType == enCtStock || enContractType == enCtIndex)
					{
						//if(UndPos_ <= BAD_LONG_VALUE) UndPos_ = 0L;
						//UndPos_ += nPosQtyInShares;

						nUndUpdated++;
						
						_CHK(pPos->CalcPnlMtm(bIsPnlLTD, dActiveFutureMid > 0 ? dActiveFutureMid : dUndPriceBid, dActiveFutureMid > 0 ? dActiveFutureMid : dUndPriceAsk, VARIANT_TRUE , dtCalcDate));
						
						if(dUndPriceMid > DBL_EPSILON)
						{
							/*if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
							m_dDeltaEq += nPosQtyInShares * dUndPriceMid;*/
							/*if(pPos->m_dDeltaEq <= BAD_DOUBLE_VALUE) pPos->m_dDeltaEq = 0.;
							pPos->m_dDeltaEq = nPosQtyInShares * dUndPriceMid;*/
							pPos->m_dNetExposure = nPosQtyInShares * dUndPriceMid / m_dNetExposureAUM * 100.0;

						}
						else
							BadNetDlt$_= VARIANT_TRUE;

/*						if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
						m_dNetDelta += nPosQtyInShares;*/
						IRvMmQuoteAtomPtr spQuote = pPos->m_spQuote;
						if( spQuote!=NULL )
						{
							_CHK(spQuote->put_ReplacePriceStatus(m_enReplacePriceStatus));
						}

						if (enContractType == enCtIndex)
							pPos->m_pQuote->m_pPrice->m_dActivePrice = dUndPriceMid;
					}

					// futures
					else if(enContractType == enCtFuture)
					{
						//if(FutQty_ <= BAD_LONG_VALUE) FutQty_ = 0L;
						//FutQty_ += nPosQty;

						//if(UndPos_ <= BAD_LONG_VALUE) UndPos_ = 0L;
						//UndPos_ += nPosQtyInShares;

						nFutUpdated++;

						IMmRvFutAtomPtr spFut = pPos->m_spFut;
						DOUBLE futurePrice = BAD_DOUBLE_VALUE;
						CMmRvFutAtom *pFut = static_cast<CMmRvFutAtom*>(spFut.GetInterfacePtr());

						if(pFut != NULL)
						{
							EtsReplacePriceStatusEnum enFutPriceStatusMid = enRpsNone;
							EtsReplacePriceStatusEnum enFutPriceStatusBid = enRpsNone;
							EtsReplacePriceStatusEnum enFutPriceStatusAsk = enRpsNone;
							DOUBLE dFutPriceMid = 0., dFutPriceBid = 0., dFutPriceAsk = 0.;
							
							IEtsPriceProfileAtomPtr spUndPriceProfile = pFut->m_spUndPriceProfile;
							VARIANT_BOOL futureUsed = VARIANT_FALSE;
							VARIANT_BOOL vb;
							DOUBLE dPriceActive = 0.;

							if(spUndPriceProfile != NULL)
							{
								DOUBLE dPriceBid = 0., dPriceAsk = 0., dPriceLast = 0.;
								

								IMmRvPricePtr spFutPrice;
								_CHK(spFut->get_Price(&spFutPrice));

								_CHK(spFutPrice->get_Bid(&dPriceBid));
								_CHK(spFutPrice->get_Ask(&dPriceAsk));
								_CHK(spFutPrice->get_Last(&dPriceLast));
								_CHK(spFutPrice->get_Active(&dPriceActive));
								_CHK(spFutPrice->get_IsUseManualActive(&vb));

								_CHK(spFut->GetFuturePrice(dUndPriceTolerance, enPriceRoundingRule, &enFutPriceStatusMid, &futureUsed, &futurePrice ));

								if (futureUsed && futurePrice > 0.)	
									/*dUndPriceMid = */dFutPriceBid = dFutPriceAsk = dFutPriceMid = futurePrice;
								else
								{
									/*if(futurePrice > 0.)
										dUndPriceMid = futurePrice;*/
									dFutPriceBid = spUndPriceProfile->GetUndPriceBidForPnL(dPriceBid, dPriceAsk,
										dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enFutPriceStatusBid);

									dFutPriceAsk = spUndPriceProfile->GetUndPriceAskForPnL(dPriceBid, dPriceAsk,
										dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enFutPriceStatusAsk);
								}
							}

							IRvMmQuoteAtomPtr spQuote = pPos->m_spQuote;
							if( spQuote!=NULL )
							{
								_CHK(spQuote->put_ReplacePriceStatus(static_cast<EtsReplacePriceStatusEnum>(enFutPriceStatusMid | enFutPriceStatusBid | enFutPriceStatusAsk)));
							}
							spFut->put_ReplacePriceStatus(static_cast<EtsReplacePriceStatusEnum>(enFutPriceStatusMid | enFutPriceStatusBid | enFutPriceStatusAsk));

							if (vb == FALSE)
							{
								_CHK(pPos->CalcPnlMtm(bIsPnlLTD, ( futurePrice > 0. && futureUsed ) ? futurePrice  : dFutPriceBid, 
									( futurePrice > 0. && futureUsed ) ? futurePrice  : dFutPriceAsk, VARIANT_TRUE , dtCalcDate) );
							}
							else
							{
								_CHK(pPos->CalcPnlMtm(bIsPnlLTD, dPriceActive, dPriceActive, VARIANT_TRUE , dtCalcDate) );							
							}

							if ( m_enContractType == enCtFutUnd ) 
							{
								if(pPos->m_dPnlMtm <= BAD_DOUBLE_VALUE)
									pPos->m_dPnlMtm = 0.;
								else
									pPos->m_dPnlMtm *= pFut->m_dKEq / pFut->m_nFutLotSize;

								pPos->m_bMultOptDltEq = pFut->m_bMultOptDltEq;
								pPos->m_dKEq = pFut->m_dKEq;

								pFut->m_dUndMidPrice = dUndPriceMid;
							}
							pPos->m_dPnlTheo = pPos->m_dPnlMtm;

							if(dUndPriceMid > DBL_EPSILON || (futurePrice > 0 &&  m_enContractType == enCtFutUnd) )
							{
								if(m_enContractType != enCtFutUnd)
								{
									if (IsBadValue(pPos->m_dDeltaEq) ) pPos->m_dDeltaEq = 0.;
									double dEq = nPosQtyInShares * dUndPriceMid;

									pPos->m_dDeltaEq += dEq;
									pPos->m_dNetExposure = dEq / m_dNetExposureAUM * 100.0;

								}
								else
								{
									double dEq = nPosQtyInShares * futurePrice;
									pPos->m_dNetExposure = dEq / m_dNetExposureAUM * 100.0;

								}

							}
							else
								BadNetDlt$_ = VARIANT_TRUE;


							if(pFut && !pFut->m_bMultOptDltEq)
								pPos->m_dNetExposure *= pFut->m_nFutLotSize;
						}


					}

		
					// PnlMtm
					if ( IsBadValue(pPos->m_dPnlMtm)) 
						BadPnlMtm_ = VARIANT_TRUE;
					if ( IsBadValue(pPos->m_dPnlTheo)) 
						BadPnlTheo_ = VARIANT_TRUE;
					//if(pPos->m_dPnlMtm > BAD_DOUBLE_VALUE)
					//{
					//	if(PnlMTM_ <= BAD_DOUBLE_VALUE) PnlMTM_ = 0.;
					//	PnlMTM_ += pPos->m_dPnlMtm;
					//}
					//else
					//	BadPnlMtm_ = VARIANT_TRUE;

					//// PnlTheo
					//if(pPos->m_dPnlTheo > BAD_DOUBLE_VALUE)
					//{
					//	if(PnLTheo_<= BAD_DOUBLE_VALUE) PnLTheo_ = 0.;
					//	PnLTheo_ += pPos->m_dPnlTheo;
					//}
					//else
					//	BadPnlTheo_ = VARIANT_TRUE;

					// aggregate
					AggregatePosition(pPos, dUndPriceMid, dUndPriceTolerance, enPriceRoundingRule);
				}
			}
		}

		CalcNetDeltas(m_enContractType);
		if(NetDlt$_ > BAD_DOUBLE_VALUE && Beta_ > BAD_DOUBLE_VALUE && DoubleNEQZero(Beta_))
		{
			BetaWtdDelta$_ = NetDlt$_ * Beta_;
			if(BadNetDlt$_) BadBetaWtdDelta$_ = VARIANT_TRUE;
		}
		else
			BadBetaWtdDelta$_ = VARIANT_TRUE;



		if(pnOptUpdated)
			*pnOptUpdated += nOptUpdated;

		if(pnUndUpdated)
			*pnUndUpdated += nUndUpdated;

		if(pnFutUpdated)
			*pnFutUpdated += nFutUpdated;

		m_pPrice->m_bDirty   = VARIANT_FALSE;
		m_pSuPrice->m_bDirty = VARIANT_FALSE;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvUndAtom, e.Error());
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
void CMmRvUndAtom::_CalcTotalsForOptionPos(CMmRvPosAtom* pPos) throw()
{
	DOUBLE dOptDltEqOnePos;
	CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(pPos->m_spFut.GetInterfacePtr());

	DOUBLE dUndPriceMid = m_pPrice->m_dActivePrice;
	if((pFut && m_enContractType == enCtFutUnd))
		dUndPriceMid = pFut->m_pPrice->m_dActivePrice;

	if ( pPos )
		pPos->m_dUndPriceSave = dUndPriceMid;

	// DeltaInShares
	if(pPos->m_dDeltaInShares > BAD_DOUBLE_VALUE)
	{
		/*if(m_dOptDelta <= BAD_DOUBLE_VALUE) m_dOptDelta = 0.;
		m_dOptDelta += pPos->m_dDeltaInShares;*/
		/*if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
		m_dNetDelta += pPos->m_dDeltaInShares;*/
		if(dUndPriceMid > DBL_EPSILON)
		{
			//if(NetDlt$_ <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
			{
				//if(OptDlt$_ <= BAD_DOUBLE_VALUE) OptDlt$_ = 0.;
				pPos->m_dInternalEqDelta = pPos->m_dDeltaInShares * dUndPriceMid;
// 				if(pPos->m_dInternalEqDelta > BAD_DOUBLE_VALUE )
// 				{
// 					if(m_dNetExposureAUM >BAD_DOUBLE_VALUE && m_dNetExposureAUM != 0.0)
// 					{
// 						pPos->m_dNetExposure = pPos->m_dInternalEqDelta / m_dNetExposureAUM * 100;
// 						if(pPos->m_spFut!=NULL)
// 						{
// 							CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(pPos->m_spFut.GetInterfacePtr());
// 							if(pFut && pFut->m_bMultOptDltEq)
// 								pPos->m_dNetExposure *= pFut->m_nFutLotSize;
// 						}
// 						
//						if(NetExposure_ == BAD_DOUBLE_VALUE) NetExposure_ = 0.0;
// 						 NetExposure_ += pPos->m_dNetExposure;
// 
// 						ATLTRACE("NetExp %.4f -> %.4f\n",pPos->m_dNetExposure, NetExposure_);
// 						if(pPos->m_dNetExposure < 0.0)
// 						{
// 							if(NetExposureSort_ == BAD_DOUBLE_VALUE) NetExposureSort_ = 0;
// 							NetExposureSort_+= pPos->m_dNetExposure;
// 						}
// 						if(pPos->m_dNetExposure > 0.0)
// 						{
// 							if(NetExposureLong_ == BAD_DOUBLE_VALUE) NetExposureLong_ = 0;
// 							NetExposureLong_+= pPos->m_dNetExposure;
// 						}
// 						
// 					}
// 					else
// 						pPos->m_dNetExposure = BAD_DOUBLE_VALUE;
// 					pPos->m_bBadNetExposure = VARIANT_FALSE;
// 				}
// 				else
// 				{
// 					pPos->m_dNetExposure = BAD_DOUBLE_VALUE;
// 					pPos->m_bBadNetExposure = VARIANT_TRUE;
// 				}
// 
				if(m_dNetExposureAUM >BAD_DOUBLE_VALUE && m_dNetExposureAUM != 0.0)
					pPos->m_dNetExposure = pPos->m_dInternalEqDelta / m_dNetExposureAUM * 100;

				if(m_enContractType != enCtFutUnd)
				{
					pPos->m_dDeltaEq = pPos->m_dInternalEqDelta;
				}
				else
				{
					if(pPos->m_spFut!=NULL)
					{
						CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(pPos->m_spFut.GetInterfacePtr());
						if(pFut && pFut->m_bMultOptDltEq)
							pPos->m_dNetExposure *= pFut->m_nFutLotSize;
					}
				}

				/*if(pPos->m_dDeltaEq > BAD_DOUBLE_VALUE)
					m_dDeltaEq += pPos->m_dDeltaEq;

				if(pPos->m_bMultOptDltEq)
					dOptDltEqOnePos = pPos->m_dInternalEqDelta * pPos->m_dKEq;
				else
					dOptDltEqOnePos = pPos->m_dInternalEqDelta;

				OptDlt$_ += dOptDltEqOnePos;*/

				if( m_enContractType == enCtFutUnd)
				{
					dOptDltEqOnePos = pPos->m_dInternalEqDelta * pPos->m_dKEq;
					if (!pPos->m_bMultOptDltEq && pPos->m_pQuote && !IsBadValue(pPos->m_pQuote->m_nLotSize) && pPos->m_pQuote->m_nLotSize) 
						dOptDltEqOnePos /= pPos->m_pQuote->m_nLotSize;
				}
				else
					dOptDltEqOnePos = pPos->m_dInternalEqDelta;
				//OptDlt$_ += dOptDltEqOnePos;
			}
		}
		else
		{
			BadOptDlt$_ = VARIANT_TRUE;
			BadOptDlt$_ = VARIANT_TRUE;
		}
	}
	else
	{
		BadNetDelta_ = VARIANT_TRUE;
		BadOptDelta_ = VARIANT_TRUE;
		BadNetDlt$_ = VARIANT_TRUE;
	}

	// GammaInSharesPerc
	/*if(pPos->m_dGammaInSharesPerc > BAD_DOUBLE_VALUE)
	{
		if(m_dGammaPerc <= BAD_DOUBLE_VALUE) m_dGammaPerc = 0.;
		m_dGammaPerc += pPos->m_dGammaInSharesPerc;
		if(dUndPriceMid > DBL_EPSILON)
		{
			if(m_dGammaEq <= BAD_DOUBLE_VALUE) m_dGammaEq = 0.;
			m_dGammaEq += pPos->m_dGammaInSharesPerc * dUndPriceMid;
		}
		else
			m_bBadGammaEq = VARIANT_TRUE;
	}*/
	if(IsBadValue(pPos->m_dGammaInSharesPerc)) /*else*/
	{
		BadGma1P_ = VARIANT_TRUE;
		BadNetGma$_ = VARIANT_TRUE;
	}

	// GammaInShares
	/*if(pPos->m_dGammaInShares > BAD_DOUBLE_VALUE)
	{
		if(m_dGamma <= BAD_DOUBLE_VALUE) m_dGamma = 0.;
		m_dGamma += pPos->m_dGammaInShares;
	}*/
	if(IsBadValue(pPos->m_dGammaInShares) )/*else*/
		BadGma1$_ = VARIANT_TRUE;


	// Net Gamma
	/*if(pPos->m_dNetGamma > BAD_DOUBLE_VALUE)
	{
		if(m_dNetGamma <= BAD_DOUBLE_VALUE) m_dNetGamma = 0.;
		m_dNetGamma += pPos->m_dNetGamma;
	}
	else*/
	if(IsBadValue(pPos->m_dNetGamma))
		BadNetGma_ = VARIANT_TRUE;


	// VegaInShares
	/*if(pPos->m_dVegaInShares > BAD_DOUBLE_VALUE)
	{
		if(m_dVega <= BAD_DOUBLE_VALUE) m_dVega = 0.;
		m_dVega += pPos->m_dVegaInShares;
	}
	else*/
	if(IsBadValue(pPos->m_dVegaInShares))
		BadVga$_ = VARIANT_TRUE;

	// WtdVega
	/*if(pPos->m_dWtdVega > BAD_DOUBLE_VALUE)
	{
		if(m_dWtdVega <= BAD_DOUBLE_VALUE) m_dWtdVega = 0.;
		m_dWtdVega += pPos->m_dWtdVega;
	}
	else*/
	if(IsBadValue(pPos->m_dWtdVega))
		BadWtdVga$_ = VARIANT_TRUE;

	// ThetaInShares
	/*if(pPos->m_dThetaInShares > BAD_DOUBLE_VALUE)
	{
		if(m_dTheta <= BAD_DOUBLE_VALUE) m_dTheta = 0.;
		m_dTheta += pPos->m_dThetaInShares;
	}
	else*/
	if(IsBadValue(pPos->m_dThetaInShares))
		BadTht$_ = VARIANT_TRUE;

	// RhoInShares
	/*if(pPos->m_dRhoInShares > BAD_DOUBLE_VALUE)
	{
		if(m_dRho <= BAD_DOUBLE_VALUE) m_dRho = 0.;
		m_dRho += pPos->m_dRhoInShares;
	}
	else*/
	if(IsBadValue(pPos->m_dRhoInShares))
		BadRho$_ = VARIANT_TRUE;

	// ThetaDeltaInShares
	/*if(pPos->m_dThetaDeltaInShares > BAD_DOUBLE_VALUE)
	{
		if(m_dThetaDelta <= BAD_DOUBLE_VALUE) m_dThetaDelta = 0.;
		m_dThetaDelta += pPos->m_dThetaDeltaInShares;
	}
	else
		m_bBadThetaDelta = VARIANT_TRUE;*/
	if(IsBadValue(pPos->m_dThetaDeltaInShares))
		BadThtDlt_ = VARIANT_TRUE;

	// ThetaGammaInShares
	/*if(pPos->m_dThetaGammaInShares > BAD_DOUBLE_VALUE)
	{
		if(m_dThetaGamma <= BAD_DOUBLE_VALUE) m_dThetaGamma = 0.;
		m_dThetaGamma += pPos->m_dThetaGammaInShares;
	}
	else
		m_bBadThetaGamma = VARIANT_TRUE;*/
	if(IsBadValue(pPos->m_dThetaGammaInShares))
		BadThtGma_ = VARIANT_TRUE;


	// VegaDeltaInShares
	/*if(pPos->m_dVegaDeltaInShares > BAD_DOUBLE_VALUE)
	{
		if(m_dVegaDelta <= BAD_DOUBLE_VALUE) m_dVegaDelta = 0.;
		m_dVegaDelta += pPos->m_dVegaDeltaInShares;
	}
	else*/
	if(IsBadValue(pPos->m_dVegaDeltaInShares))
		BadVgaDlt_ = VARIANT_TRUE;

	// VegaGammaInShares
	/*if(pPos->m_dVegaGammaInShares > BAD_DOUBLE_VALUE)
	{
		if(m_dVegaGamma <= BAD_DOUBLE_VALUE) m_dVegaGamma = 0.;
		m_dVegaGamma += pPos->m_dVegaGammaInShares;
	}
	else
		m_bBadVegaGamma = VARIANT_TRUE;*/
	if(IsBadValue(pPos->m_dVegaGammaInShares))
		BadVgaGma_ = VARIANT_TRUE;

	// TimeValue
	/*if(pPos->m_dTimeValue > BAD_DOUBLE_VALUE)
	{
		if(m_dTimeValue <= BAD_DOUBLE_VALUE) m_dTimeValue = 0.;
		m_dTimeValue += pPos->m_dTimeValue;

		if(m_dTimeValueInShares <= BAD_DOUBLE_VALUE) m_dTimeValueInShares = 0.;
		m_dTimeValueInShares += (pPos->m_dTimeValue*pPos->m_nQtyInShares);
	}
	else*/
	if(IsBadValue(pPos->m_dTimeValue))
		BadTmVal_ = VARIANT_TRUE;

	VARIANT_BOOL bPosIsSynthetic = pPos->m_bIsSynthetic;
	if(bPosIsSynthetic)
	{
		IMmRvSynthGreeksCollPtr spPosSynthGreeksColl = pPos->m_spSynthGreeks;

		if(spPosSynthGreeksColl != NULL)
		{
			IMmRvSynthGreeksAtomPtr spPosSynthGreeks;
			LONG nSynthUndID = 0L;
			DOUBLE dSelfValue = BAD_DOUBLE_VALUE;

			IUnknownPtr spUnk;
			_variant_t varItem;
			ULONG nFetched = 0L;
			HRESULT hr;

			_CHK(spPosSynthGreeksColl->get__NewEnum(&spUnk));
			IEnumVARIANTPtr spPosSynthGreekEnum(spUnk);
			_CHK(spPosSynthGreekEnum->Reset());
			while((hr = spPosSynthGreekEnum->Next(1L, &varItem, &nFetched)) == S_OK)
			{
				ATLASSERT(varItem.vt == VT_DISPATCH);
				spPosSynthGreeks = varItem;
				if(spPosSynthGreeks != NULL)
				{
					_CHK(spPosSynthGreeks->get_SynthUndID(&nSynthUndID));
					IMmRvSynthGreeksAtomPtr spSynthGreeks;
					_CHK(m_spSynthGreeks->get_Item(nSynthUndID, &spSynthGreeks));

					if(spSynthGreeks != NULL)
					{
						double dPosValue =BAD_DOUBLE_VALUE;

						//NetExp
						_CHK(spPosSynthGreeks->get_NetExposure(&dPosValue));
						if (dPosValue > BAD_DOUBLE_VALUE)
						{
							_CHK(spSynthGreeks->get_NetExposure(&dSelfValue));
							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
							_CHK(spSynthGreeks->put_NetExposure(dSelfValue + dPosValue));
						}
						else
							_CHK(spSynthGreeks->put_BadNetExposure(VARIANT_TRUE));

						//NetDelta
						_CHK(spPosSynthGreeks->get_NetDelta(&dPosValue));
						if (dPosValue > BAD_DOUBLE_VALUE)
						{
							_CHK(spSynthGreeks->get_NetDelta(&dSelfValue));
							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
							_CHK(spSynthGreeks->put_NetDelta(dSelfValue + dPosValue));
						}
						else
							_CHK(spSynthGreeks->put_BadNetDelta(VARIANT_TRUE));

						// DeltaInShares
						_CHK(spPosSynthGreeks->get_DeltaInShares(&dPosValue));
						if(dPosValue > BAD_DOUBLE_VALUE)
						{
							_CHK(spSynthGreeks->get_DeltaInShares(&dSelfValue));
							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
							_CHK(spSynthGreeks->put_DeltaInShares(dSelfValue + dPosValue));
						}
						else
							_CHK(spSynthGreeks->put_BadDelta(VARIANT_TRUE));

						// GammaInSharesPerc
						_CHK(spPosSynthGreeks->get_GammaInSharesPerc(&dPosValue));
						if(dPosValue > BAD_DOUBLE_VALUE)
						{
							_CHK(spSynthGreeks->get_GammaInSharesPerc(&dSelfValue));
							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
							_CHK(spSynthGreeks->put_GammaInSharesPerc(dSelfValue + dPosValue));
						}
						else
							_CHK(spSynthGreeks->put_BadGammaPerc(VARIANT_TRUE));

						// GammaInShares
						_CHK(spPosSynthGreeks->get_GammaInShares(&dPosValue));
						if(dPosValue > BAD_DOUBLE_VALUE)
						{
							_CHK(spSynthGreeks->get_GammaInShares(&dSelfValue));
							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
							_CHK(spSynthGreeks->put_GammaInShares(dSelfValue + dPosValue));
						}
						else
							_CHK(spSynthGreeks->put_BadGamma(VARIANT_TRUE));

						// Net Gamma
						_CHK(spPosSynthGreeks->get_NetGamma(&dPosValue));
						if(dPosValue > BAD_DOUBLE_VALUE)
						{
							_CHK(spSynthGreeks->get_NetGamma(&dSelfValue));
							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
							_CHK(spSynthGreeks->put_NetGamma(dSelfValue + dPosValue));
						}
						else
							_CHK(spSynthGreeks->put_BadNetGamma(VARIANT_TRUE));

					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//
void CMmRvUndAtom::_ClearSynthGreeks() throw()
{
	if(m_bHasSynthetic && m_spSynthGreeks != NULL)
	{
		IUnknownPtr spUnk;
		_variant_t varItem;
		ULONG nFetched = 0L;
		HRESULT hr;
		IMmRvSynthGreeksAtomPtr spSynthGreeks;

		_CHK(m_spSynthGreeks->get__NewEnum(&spUnk));
		IEnumVARIANTPtr spSynthGreekEnum(spUnk);
		_CHK(spSynthGreekEnum->Reset());
		while((hr = spSynthGreekEnum->Next(1L, &varItem, &nFetched)) == S_OK)
		{
			ATLASSERT(varItem.vt == VT_DISPATCH);
			spSynthGreeks = varItem;
			if(spSynthGreeks != NULL)
				_CHK(spSynthGreeks->ClearValuesInShares());
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmRvUndAtom::CalcWtdVega(IEtsExpCalColl* aExpCalColl)
{
	if(aExpCalColl == NULL)
		return Error(L"Invalid objects passed.", IID_IMmRvUndAtom, E_INVALIDARG);

	HRESULT hr = S_OK;

	try
	{
		BadWtdVga$_ = VARIANT_FALSE;
		WtdVga$_ = BAD_DOUBLE_VALUE;

		IUnknownPtr spUnk;
		_variant_t varItem;
		ULONG nFetched = 0L;
 		DATE dtToday = vt_date::GetCurrentDate(true);
		IEtsExpCalCollPtr spExpCalColl(aExpCalColl);

		if(m_pPos)
		{
			CMmRvPosColl::CollType::iterator itr = m_pPos->m_collRef.begin();
			CMmRvPosColl::CollType::iterator itrEnd = m_pPos->m_collRef.end();
			for(;itr!=itrEnd;++itr)
			{
				CMmRvPosAtom* pPosAtom = dynamic_cast<CMmRvPosAtom*>(itr->second->second);
				if(pPosAtom)
				{
					EtsContractTypeEnum enContractType = pPosAtom->m_enContractType;

					if(enContractType == enCtOption || enContractType == enCtFutOption)
					{
						DOUBLE dVegaWeight = BAD_DOUBLE_VALUE;
						DATE dtExpiry = pPosAtom->m_dtExpiry;

						dVegaWeight = spExpCalColl->GetVegaWeight(dtExpiry);
						pPosAtom->m_dVegaWeight = dVegaWeight;


						VARIANT_BOOL bVisible = pPosAtom->m_bVisible;
						if(bVisible && dtExpiry >= dtToday && dVegaWeight > BAD_DOUBLE_VALUE)
						{
							// VegaInShares							
							if(pPosAtom->m_dVegaInShares > BAD_DOUBLE_VALUE)
							{
								pPosAtom->m_dWtdVega = pPosAtom->m_dVegaInShares * dVegaWeight;

								if(WtdVga$_ <= BAD_DOUBLE_VALUE) WtdVga$_ = 0.;
								WtdVga$_ += pPosAtom->m_dVegaInShares * pPosAtom->m_dVegaInShares;
							}
							else
								BadWtdVga$_ = VARIANT_TRUE;
						}
					}

				}
			}
		}
	}
	catch(const _com_error& e)
	{
		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvUndAtom, e.Error());
	}
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmRvUndAtom::CalcSyntheticUnderlying(IMmRvUndColl* aUndColl,
																	LONG nMask,
																	VARIANT_BOOL bIsPnlLTD,
																	EtsCalcModelTypeEnum enCalcModel,
																	VARIANT_BOOL bUseTheoVolatility,
																	VARIANT_BOOL bUseTheoVolaNoBid,
																	VARIANT_BOOL bUseTheoVolaBadMarket,
																	DOUBLE dUndPriceTolerance,
																	EtsPriceRoundingRuleEnum enPriceRoundingRule,
																	DATE dtCalcDate)
{
	if(aUndColl == NULL)
		return Error(L"Invalid objects passed.", IID_IMmRvUndAtom, E_INVALIDARG);

	try
	{
		IUnknownPtr spUnk;
		_variant_t varItem;
		ULONG nFetched = 0L;
		HRESULT hr;

		DOUBLE dUndPriceMid = 0.;
		if(m_spUndPriceProfile != NULL)
		{
			dUndPriceMid = m_spUndPriceProfile->GetUndPriceMid(m_pPrice->m_dPriceBid, m_pPrice->m_dPriceAsk, m_pPrice->m_dPriceLast, 
				dUndPriceTolerance, enPriceRoundingRule, NULL, VARIANT_FALSE);
		}

		IMmRvUndCollPtr spUndColl(aUndColl);
		IMmRvUndCollPtr spUndColl2;
		IMmRvPosAtomPtr spPos;
		IMmRvUndAtomPtr spUnd, spUnd2;

		_CHK(spUndColl2.CreateInstance(CLSID_MmRvUndColl), _T("Fail to create underlings."));
		if(spUndColl2 == NULL)
			return Error(L"Fail to create underlings.", IID_IMmRvUndAtom, E_INVALIDARG);

		spUndColl2.AddRef();

		_CHK(m_spSynthPos->get__NewEnum(&spUnk));
		IEnumVARIANTPtr spPosEnum(spUnk);
		_CHK(spPosEnum->Reset());
		while((hr = spPosEnum->Next(1L, &varItem, &nFetched)) == S_OK)
		{
			ATLASSERT(varItem.vt == VT_DISPATCH);
			spPos = varItem;
			if(spPos != NULL)
			{
				EtsContractTypeEnum enContractType = enCtNone;
				_CHK(spPos->get_ContractType(&enContractType));

				if(enContractType == enCtOption)
				{
					LONG nUndID = 0L;
					_CHK(spPos->get_UndID(&nUndID));
					_CHK(spUndColl->get_Item(nUndID, &spUnd));

					if(spUnd != NULL)
					{
						_CHK(spUndColl2->get_Item(nUndID, &spUnd2));
						if(spUnd2 == NULL)
							_CHK(spUndColl2->Add(nUndID, L"", spUnd, NULL));

						_CHK(spUnd->ClearValues());
						_CHK(spPos->CalcOptionGreeks(spUndColl, this, dUndPriceMid,
							nMask, bIsPnlLTD, enCalcModel,
							bUseTheoVolatility, bUseTheoVolaNoBid, bUseTheoVolaBadMarket,
							dUndPriceTolerance, enPriceRoundingRule,dtCalcDate));
					}
				}
			}
		}

		_CHK(spUndColl2->get__NewEnum(&spUnk));
		IEnumVARIANTPtr spUndEnum(spUnk);
		_CHK(spUndEnum->Reset());
		while((hr = spUndEnum->Next(1L, &varItem, &nFetched)) == S_OK)
		{
			ATLASSERT(varItem.vt == VT_DISPATCH);
			spUnd = varItem;
			if(spUnd != NULL)
			{
				LONG nUndID = 0L;
				_CHK(spUnd->get_ID(&nUndID));
				if(nUndID != m_nID)
				{
					_CHK(spUnd->Calc(spUndColl,
						nMask,
						VARIANT_TRUE,
						VARIANT_TRUE,
						VARIANT_FALSE,
						VARIANT_TRUE,
						NULL,
						bIsPnlLTD,
						enCalcModel,
						bUseTheoVolatility,
						bUseTheoVolaNoBid,
						bUseTheoVolaBadMarket,
						dUndPriceTolerance,
						enPriceRoundingRule,
						NULL, NULL, NULL,dtCalcDate));
				}
			}
		}

		spUndColl2 = NULL;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvUndAtom, e.Error());
	}
	return S_OK;
}

/*
This function returns index( or stock) "mid" price, according to active future or price profile.
Sets bFutureUsed to VARIANT_TRUE if active future was used.
*/

STDMETHODIMP CMmRvUndAtom::GetUnderlyingPrice(DOUBLE dTolerance, EtsPriceRoundingRuleEnum enPriceRound,EtsReplacePriceStatusEnum * penPriceStatus, VARIANT_BOOL *bFutureUsed, DOUBLE *pPrice){
	HRESULT	hr = S_OK;

	if( !pPrice || !bFutureUsed)
		return E_POINTER;
	try{
		*pPrice = 0;
		*bFutureUsed = VARIANT_FALSE;

		bool dontUseFuture = true;
		if ( m_spActiveFuture )	
		{
			// this underlying - is index with active future 
			DOUBLE dActiveFutureMid = 0., dActiveFutureBid = 0., dActiveFutureAsk = 0., dActiveFutureLast = 0.;
			DOUBLE dActiveFutureBasis = 0.;
			IEtsPriceProfileAtomPtr spUndPriceProfile;

			m_spActiveFuture->get_UndPriceProfile(&spUndPriceProfile);
			if ( NULL != spUndPriceProfile)
			{
				IMmRvPricePtr spFutPrice;
				_CHK(m_spActiveFuture->get_Price(&spFutPrice));

				_CHK(m_spActiveFuture->get_Basis(&dActiveFutureBasis));
				_CHK(spFutPrice->get_Bid(&dActiveFutureBid) );
				_CHK(spFutPrice->get_Ask(&dActiveFutureAsk) );
				_CHK(spFutPrice->get_Last(&dActiveFutureLast) );

				dActiveFutureMid = spUndPriceProfile->GetUndPriceMid(dActiveFutureBid, dActiveFutureAsk,
					dActiveFutureLast, dTolerance, enPriceRound, penPriceStatus, VARIANT_FALSE);

				if ( dActiveFutureMid > 0.)
				{
					dActiveFutureMid += dActiveFutureBasis;
					//_CHK(spFutPrice->put_Active(dActiveFutureMid));
					*pPrice = dActiveFutureMid;
					dontUseFuture = false;
					*bFutureUsed = VARIANT_TRUE;
				}
			}
		}
		if ( dontUseFuture && m_spUndPriceProfile ){
			*pPrice = m_spUndPriceProfile->GetUndPriceMid(	m_pPrice->m_dPriceBid, m_pPrice->m_dPriceAsk, m_pPrice->m_dPriceLast, dTolerance, enPriceRound, penPriceStatus, VARIANT_FALSE );
		}
	}
	catch ( _com_error& e ) {
		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(e), __uuidof(IMmRvUndAtom), e.Error());
	}

	return hr;

}


STDMETHODIMP CMmRvUndAtom::FindPosition(DOUBLE dStrike, DATE dtExpiration, EtsOptionTypeEnum enType, IMmRvPosAtom** pPosAtom)
{
	HRESULT hr = S_OK;
	if(!pPosAtom)
		return E_POINTER;
	try
	{
		IMmRvPosAtomPtr spPosAtom;
		if(m_pPos && !m_pPos->m_coll.empty())
		{
			CMmRvPosColl::EnumCollType::iterator itrPos    = m_pPos->m_coll.begin();
			CMmRvPosColl::EnumCollType::iterator itrPosEnd = m_pPos->m_coll.end();
			for(;itrPos!=itrPosEnd; ++itrPos)
			{
				CMmRvPosAtom* pPos = dynamic_cast<CMmRvPosAtom*>(itrPos->second);
				if((pPos->m_enContractType == enCtOption || pPos->m_enContractType == enCtFutOption) 
					&& pPos->m_dStrike == dStrike && pPos->m_enOptType == enType && static_cast<long>(pPos->m_dtExpiry) == static_cast<long>(dtExpiration))
				{
					spPosAtom.Attach(pPos, TRUE);
					break;
				}
			}			
		}
		if(spPosAtom!=NULL)
			*pPosAtom = spPosAtom.Detach();
	}
	catch ( _com_error& e ) {
		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(e), __uuidof(IMmRvUndAtom), e.Error());
	}
	return hr;
}

STDMETHODIMP CMmRvUndAtom::ClearRatios()
{
	if (m_spFut != NULL)
	{
		CComObject<CMmRvFutColl>* futColl = dynamic_cast<CComObject<CMmRvFutColl>*>(m_spFut.GetInterfacePtr());

		CMmRvFutColl::EnumCollType::iterator itrFut    = futColl->m_coll.begin();
		CMmRvFutColl::EnumCollType::iterator itrFutEnd = futColl->m_coll.end();

		for(;itrFut!=itrFutEnd; ++itrFut)
		{
			CMmRvFutAtom* pFut = dynamic_cast<CMmRvFutAtom*>(itrFut->second);
			if (pFut != NULL)
				pFut->m_dRatio	=	BAD_DOUBLE_VALUE;
		}
	}
	else
		return E_POINTER;

	return S_OK;
}
//// MmRvUndAtom.cpp : Implementation of CMmRvUndAtom
//
//#include "stdafx.h"
//#include "MmRvUndAtom.h"
//#include "MmRvUndColl.h"
//#include "MmRvUndAtom.h"
//
///////////////////////////////////////////////////////////////////////////////
////
//STDMETHODIMP CMmRvUndAtom::GetSyntheticUnderlyingPrice(IMmRvUndColl* aUndColl,
//														ISynthRootAtom* aSynthRoot,
//														DOUBLE* pdSynthBid,
//														DOUBLE* pdSynthAsk,
//														DOUBLE* pdSynthLast)
//{
//	if(aUndColl == NULL)
//		return Error(L"Invalid object passed.", IID_IMmRvUndAtom, E_INVALIDARG);
//
//	__CHECK_POINTER(pdSynthBid);
//	__CHECK_POINTER(pdSynthAsk);
//	__CHECK_POINTER(pdSynthLast);
//
//	*pdSynthBid = BAD_DOUBLE_VALUE;
//	*pdSynthAsk = BAD_DOUBLE_VALUE;
//	*pdSynthLast = BAD_DOUBLE_VALUE;
//
//	if(!m_bHasSynthetic || m_spSynthRoots == NULL || aSynthRoot == NULL)
//		return S_OK;
//
//	try
//	{
//		IUnknownPtr spUnk;
//		_variant_t varItem;
//		ULONG nFetched = 0L;
//		HRESULT hr;
//
//		ISynthRootAtomPtr spSynthRoot(aSynthRoot);
//
//		IMmRvUndCollPtr spUndColl(aUndColl);
//		IMmRvUndAtomPtr spSynthUnd;
//
//		bool bBadSpotBid = false, bBadSpotAsk = false, bBadSpotLast = false;
//
//
//		*pdSynthBid = spSynthRoot->CashValue;
//		*pdSynthAsk = *pdSynthBid;
//		*pdSynthLast = *pdSynthBid;
//
//		ISynthRootCompAtomPtr spSRComp;
//		ISynthRootCompCollPtr spSRCompColl;
//
//		spSRCompColl = spSynthRoot->SynthRootComponents;
//
//
//		_CHK(spSRCompColl->get__NewEnum(&spUnk), _T("Fail to get synthetic underlying component collection enum."));
//		IEnumVARIANTPtr spSynthRootEnum(spUnk);
//		_CHK(spSynthRootEnum->Reset(), _T("Fail to reset synthetic underlying component collection."));
//		while((hr = spSynthRootEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//		{
//			ATLASSERT(varItem.vt == VT_DISPATCH);
//			spSRComp = varItem;
//			if(spSRComp != NULL)
//			{
//				LONG nUndID = 0L;
//				DOUBLE dWeight = 0.;
//				DOUBLE dPrice = 0.;
//
//				nUndID = spSRComp->UndID;
//				_CHK(spUndColl->get_Item(nUndID, &spSynthUnd), _T("Fail to get synthetic underlying."));
//
//				if(spSynthUnd != NULL)
//				{
//					dWeight = spSRComp->Weight;
//
//					_CHK(spSynthUnd->get_PriceBid(&dPrice));
//					if(!bBadSpotBid && dPrice > DBL_EPSILON)
//						*pdSynthBid += dPrice * dWeight;
//					else
//					{
//						bBadSpotBid = true;
//						*pdSynthBid = BAD_DOUBLE_VALUE;
//					}
//
//					_CHK(spSynthUnd->get_PriceAsk(&dPrice));
//					if(!bBadSpotAsk && dPrice > DBL_EPSILON)
//						*pdSynthAsk += dPrice * dWeight;
//					else
//					{
//						bBadSpotAsk = true;
//						*pdSynthAsk = BAD_DOUBLE_VALUE;
//					}
//
//					_CHK(spSynthUnd->get_PriceLast(&dPrice));
//					if(!bBadSpotLast && dPrice > DBL_EPSILON)
//						*pdSynthLast += dPrice * dWeight;
//					else
//					{
//						bBadSpotLast = true;
//						*pdSynthLast = BAD_DOUBLE_VALUE;
//					}
//				}
//			}
//		}
//	}
//	catch(const _com_error& e)
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvUndAtom, e.Error());
//	}
//	return S_OK;
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//STDMETHODIMP CMmRvUndAtom::Calc(IMmRvUndColl* aUndColl,
//								LONG nMask,
//								VARIANT_BOOL bCalcGreeks,
//								VARIANT_BOOL bUpdateVola,
//								VARIANT_BOOL bRealtimeCalc,
//								VARIANT_BOOL bClearSynthGreeks,
//								IEtsProcessDelay* aDelay,
//								VARIANT_BOOL bIsPnlLTD,
//								EtsCalcModelTypeEnum enCalcModel,
//								VARIANT_BOOL bUseTheoVolatility,
//								VARIANT_BOOL bUseTheoVolaNoBid,
//								VARIANT_BOOL bUseTheoVolaBadMarket,
//								DOUBLE dUndPriceTolerance,
//								EtsPriceRoundingRuleEnum enPriceRoundingRule,
//								LONG* pnOptUpdated,
//								LONG* pnUndUpdated,
//								LONG* pnFutUpdated)
//{
//	if(aUndColl == NULL)
//		return Error(L"Invalid object passed.", IID_IMmRvUndAtom, E_INVALIDARG);
//   	try
//	{
//		IMmRvUndCollPtr spUndColl(aUndColl);
//
//		IUnknownPtr spUnk;
//		_variant_t varItem;
//		ULONG nFetched = 0L;
//		HRESULT hr;
//		LONG nOptUpdated = 0L, nUndUpdated = 0L, nFutUpdated = 0L;
//
//		IEtsProcessDelayPtr spDelay(aDelay);
//		if(spDelay != NULL && spDelay->IsInterrupted)
//			return S_OK;
//		
//		if(bUpdateVola)
//			bCalcGreeks = VARIANT_TRUE;
//
//		__MmRvUndAtom::ClearValues();
//
//		if(bClearSynthGreeks)
//			_ClearSynthGreeks();
//
//		EtsReplacePriceStatusEnum enUndPriceStatusMid = enRpsNone;
//		EtsReplacePriceStatusEnum enUndPriceStatusBid = enRpsNone;
//		EtsReplacePriceStatusEnum enUndPriceStatusAsk = enRpsNone;
//		DOUBLE dUndPriceMid = 0., dUndPriceBid = 0., dUndPriceAsk = 0.;
//
//		if(m_spUndPriceProfile != NULL)
//		{
//			dUndPriceMid = m_spUndPriceProfile->GetUndPriceMid(m_dPriceBid, m_dPriceAsk,
//				m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enUndPriceStatusMid, TRUE);
//
//			dUndPriceBid = m_spUndPriceProfile->GetUndPriceBidForPnL(m_dPriceBid, m_dPriceAsk,
//				m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enUndPriceStatusBid);
//
//			dUndPriceAsk = m_spUndPriceProfile->GetUndPriceAskForPnL(m_dPriceBid, m_dPriceAsk,
//				m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enUndPriceStatusAsk);
//		}
//	          
//		m_enReplacePriceStatus = static_cast<EtsReplacePriceStatusEnum>(enUndPriceStatusMid | enUndPriceStatusBid | enUndPriceStatusAsk);
//	                
//		DATE dtToday = vt_date::GetCurrentDate(true);
//		VARIANT_BOOL bNeedRecalc = VARIANT_FALSE;
//		VARIANT_BOOL bPosCalcGreeks = VARIANT_FALSE;
//		VARIANT_BOOL bCalcTheos = VARIANT_FALSE;
//		DOUBLE dPosValue = BAD_DOUBLE_VALUE;
//
//		IMmRvPosAtomPtr spPos;
//
//		_CHK(m_spPos->get__NewEnum(&spUnk));
//		IEnumVARIANTPtr spPosEnum(spUnk);
//		_CHK(spPosEnum->Reset());
//		bool bHasItems = false;
//
//		while((hr = spPosEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//		{
//			bHasItems = true;
//			ATLASSERT(varItem.vt == VT_DISPATCH);
//			spPos = varItem;
//			if(spPos != NULL)
//			{
//				VARIANT_BOOL bVisible = VARIANT_FALSE;
//				_CHK(spPos->get_Visible(&bVisible));
//				if(bVisible)
//				{
//					EtsContractTypeEnum enContractType = enCtNone;
//					_CHK(spPos->get_ContractType(&enContractType));
//					LONG nPosQty = 0L;
//					_CHK(spPos->get_Qty(&nPosQty));
//
//					LONG nPosQtyInShares = 0L;
//					_CHK(spPos->get_QtyInShares(&nPosQtyInShares));
//
//					// options
//					if(enContractType == enCtOption || enContractType == enCtFutOption)
//					{
//						if(m_nOptQty <= BAD_LONG_VALUE) m_nOptQty = 0L;
//						m_nOptQty += nPosQty;
//
//						DATE dtExpiry = 0.;
//						_CHK(spPos->get_Expiry(&dtExpiry));
//						DOUBLE dStrike = 0.;
//						_CHK(spPos->get_Strike(&dStrike));
//
//						if(dtExpiry >= dtToday)
//						{
//							_CHK(spPos->get_CalcGreeks(&bPosCalcGreeks));
//
//							if(bRealtimeCalc)
//							{
//								bCalcTheos = m_bCalcGreeks || m_bCalcTotals || bPosCalcGreeks;
//
//								if(!bCalcTheos && enContractType == enCtFutOption)
//								{
//									IMmRvFutAtomPtr spFut;
//									_CHK(spPos->get_Fut(&spFut));
//
//									if(spFut != NULL)
//									{
//										VARIANT_BOOL bFutCalcGreeks = VARIANT_FALSE;
//										_CHK(spFut->get_CalcGreeks(&bFutCalcGreeks));
//										bCalcTheos = bCalcTheos || bFutCalcGreeks;
//									}
//								}
//
//								bUpdateVola = m_bCalcGreeks;
//								bNeedRecalc = m_bCalcTotals;
//							}
//							else
//							{
//								bCalcTheos = bCalcGreeks;
//								bNeedRecalc = VARIANT_TRUE;
//							}
//
//							if(bNeedRecalc)
//							{
//								nOptUpdated++;
//
//								if(bUpdateVola)
//									_CHK(spPos->put_Vola(m_spVolaSrv->GetOptionVola(dtExpiry, dStrike)));
//
//								if(enContractType == enCtOption)
//								{
//									_CHK(spPos->CalcOptionGreeks(spUndColl, this, dUndPriceMid,
//										(bCalcTheos ? nMask : GT_NOTHING), bIsPnlLTD, enCalcModel,
//										bUseTheoVolatility, bUseTheoVolaNoBid, bUseTheoVolaBadMarket,
//										dUndPriceTolerance, enPriceRoundingRule));
//								}
//								else
//								{
//									_CHK(spPos->CalcFutOptionGreeks(this, dUndPriceMid,
//										(bCalcTheos ? nMask : GT_NOTHING), bIsPnlLTD, enCalcModel,
//										bUseTheoVolatility, bUseTheoVolaNoBid, bUseTheoVolaBadMarket,
//										dUndPriceTolerance, enPriceRoundingRule));
//								}
//
//								if(spDelay != NULL)
//									spDelay->Sleep();
//							}
//
//							_CalcTotalsForOptionPos(spPos, dUndPriceMid);
//						}
//						else
//							__MmRvUndAtom::SetAllValuesAsBad();
//					}
//
//					// underlyings
//					else if(enContractType == enCtStock || enContractType == enCtIndex)
//					{
//						if(m_nQty <= BAD_LONG_VALUE) m_nQty = 0L;
//						m_nQty += nPosQtyInShares;
//
//						nUndUpdated++;
//
//						_CHK(spPos->CalcPnlMtm(bIsPnlLTD, dUndPriceBid, dUndPriceAsk, VARIANT_TRUE));
//
//						if(dUndPriceMid > DBL_EPSILON)
//						{
//							if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
//							m_dDeltaEq += nPosQtyInShares * dUndPriceMid;
//						}
//						else
//							m_bBadDeltaEq = VARIANT_TRUE;
//
//						if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
//						m_dNetDelta += nPosQtyInShares;
//					}
//
//					// futures
//					else if(enContractType == enCtFuture)
//					{
//						if(m_nFutQty <= BAD_LONG_VALUE) m_nFutQty = 0L;
//						m_nFutQty += nPosQty;
//
//						if(m_nQty <= BAD_LONG_VALUE) m_nQty = 0L;
//						m_nQty += nPosQtyInShares;
//
//						nFutUpdated++;
//
//						IMmRvFutAtomPtr spFut;
//						_CHK(spPos->get_Fut(&spFut));
//
//						if(spFut != NULL)
//						{
//							EtsReplacePriceStatusEnum enFutPriceStatusMid = enRpsNone;
//							EtsReplacePriceStatusEnum enFutPriceStatusBid = enRpsNone;
//							EtsReplacePriceStatusEnum enFutPriceStatusAsk = enRpsNone;
//							DOUBLE dFutPriceMid = 0., dFutPriceBid = 0., dFutPriceAsk = 0.;
//							IEtsPriceProfileAtomPtr spUndPriceProfile;
//
//							_CHK(spFut->get_UndPriceProfile(&spUndPriceProfile));
//
//							if(spUndPriceProfile != NULL)
//							{
//								DOUBLE dPriceBid = 0., dPriceAsk = 0., dPriceLast = 0.;
//
//								_CHK(spFut->get_PriceBid(&dPriceBid));
//								_CHK(spFut->get_PriceAsk(&dPriceAsk));
//								_CHK(spFut->get_PriceLast(&dPriceLast));
//
//								dFutPriceMid = spUndPriceProfile->GetUndPriceMid(dPriceBid, dPriceAsk,
//									dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enFutPriceStatusMid, TRUE);
//
//								dFutPriceBid = spUndPriceProfile->GetUndPriceBidForPnL(dPriceBid, dPriceAsk,
//									dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enFutPriceStatusBid);
//
//								dFutPriceAsk = spUndPriceProfile->GetUndPriceAskForPnL(dPriceBid, dPriceAsk,
//									dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enFutPriceStatusAsk);
//							}
//						          
//							_CHK(spPos->put_ReplacePriceStatus(static_cast<EtsReplacePriceStatusEnum>(enFutPriceStatusMid | enFutPriceStatusBid | enFutPriceStatusAsk)));
//
//							_CHK(spPos->CalcPnlMtm(bIsPnlLTD, dFutPriceBid, dFutPriceAsk, VARIANT_TRUE));
//						}
//
//						if(dUndPriceMid > DBL_EPSILON)
//						{
//							if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
//							m_dDeltaEq += nPosQtyInShares * dUndPriceMid;
//						}
//						else
//							m_bBadDeltaEq = VARIANT_TRUE;
//
//						if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
//						m_dNetDelta += nPosQtyInShares;
//					}
//
//					// PnlMtm
//					_CHK(spPos->get_PnlMtm(&dPosValue));
//					if(dPosValue > BAD_DOUBLE_VALUE)
//					{
//						if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
//						m_dPnlMtm += dPosValue;
//					}
//					else
//						m_bBadPnlMtm = VARIANT_TRUE;
//
//					// PnlTheo
//					_CHK(spPos->get_PnlTheo(&dPosValue));
//					if(dPosValue > BAD_DOUBLE_VALUE)
//					{
//						if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
//						m_dPnlTheo += dPosValue;
//					}
//					else
//						m_bBadPnlTheo = VARIANT_TRUE;
//				}
//			}
//		}
//
//		if(m_dDeltaEq > BAD_DOUBLE_VALUE && m_dBeta > BAD_DOUBLE_VALUE && DoubleNEQZero(m_dBeta))
//		{
//			m_dBetaWtdDeltaEq = m_dDeltaEq * m_dBeta;
//			if(m_bBadDeltaEq) m_bBadBetaWtdDeltaEq = VARIANT_TRUE;
//		}
//		else
//			m_bBadBetaWtdDeltaEq = VARIANT_TRUE;
//
//
//
//		if(pnOptUpdated)
//			*pnOptUpdated += nOptUpdated;
//
//		if(pnUndUpdated)
//			*pnUndUpdated += nUndUpdated;
//
//		if(pnFutUpdated)
//			*pnFutUpdated += nFutUpdated;
//	}
//	catch(const _com_error& e)
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvUndAtom, e.Error());
//	}
//	return S_OK;
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//void CMmRvUndAtom::_CalcTotalsForOptionPos(IMmRvPosAtomPtr spPos, DOUBLE dUndPriceMid) throw()
//{
//	DOUBLE dPosValue = BAD_DOUBLE_VALUE;
//	// DeltaInShares
//	_CHK(spPos->get_DeltaInShares(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dOptDelta <= BAD_DOUBLE_VALUE) m_dOptDelta = 0.;
//		m_dOptDelta += dPosValue;
//		if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
//		m_dNetDelta += dPosValue;
//		if(dUndPriceMid > DBL_EPSILON)
//		{
//			if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
//			m_dDeltaEq += dPosValue * dUndPriceMid;
//		}
//		else
//			m_bBadDeltaEq = VARIANT_TRUE;
//	}
//	else
//	{
//		m_bBadNetDelta = VARIANT_TRUE;
//		m_bBadOptDelta = VARIANT_TRUE;
//		m_bBadDeltaEq = VARIANT_TRUE;
//	}
//
//	// GammaInSharesPerc
//	_CHK(spPos->get_GammaInSharesPerc(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dGammaPerc <= BAD_DOUBLE_VALUE) m_dGammaPerc = 0.;
//		m_dGammaPerc += dPosValue;
//		if(dUndPriceMid > DBL_EPSILON)
//		{
//			if(m_dGammaEq <= BAD_DOUBLE_VALUE) m_dGammaEq = 0.;
//			m_dGammaEq += dPosValue * dUndPriceMid;
//		}
//		else
//			m_bBadGammaEq = VARIANT_TRUE;
//	}
//	else
//	{
//		m_bBadGammaPerc = VARIANT_TRUE;
//		m_bBadGammaEq = VARIANT_TRUE;
//	}
//
//	// GammaInShares
//	_CHK(spPos->get_GammaInShares(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dGamma <= BAD_DOUBLE_VALUE) m_dGamma = 0.;
//		m_dGamma += dPosValue;
//	}
//	else
//		m_bBadGamma = VARIANT_TRUE;
//
//
//	// Net Gamma
//	_CHK(spPos->get_NetGamma(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dNetGamma <= BAD_DOUBLE_VALUE) m_dNetGamma = 0.;
//		m_dNetGamma += dPosValue;
//	}
//	else
//		m_bBadNetGamma = VARIANT_TRUE;
//
//
//	// VegaInShares
//	_CHK(spPos->get_VegaInShares(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dVega <= BAD_DOUBLE_VALUE) m_dVega = 0.;
//		m_dVega += dPosValue;
//	}
//	else
//		m_bBadVega = VARIANT_TRUE;
//
//	// WtdVega
//	_CHK(spPos->get_WtdVega(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dWtdVega <= BAD_DOUBLE_VALUE) m_dWtdVega = 0.;
//		m_dWtdVega += dPosValue;
//	}
//	else
//		m_bBadWtdVega = VARIANT_TRUE;
//
//	// ThetaInShares
//	_CHK(spPos->get_ThetaInShares(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dTheta <= BAD_DOUBLE_VALUE) m_dTheta = 0.;
//		m_dTheta += dPosValue;
//	}
//	else
//		m_bBadTheta = VARIANT_TRUE;
//
//	// RhoInShares
//	_CHK(spPos->get_RhoInShares(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dRho <= BAD_DOUBLE_VALUE) m_dRho = 0.;
//		m_dRho += dPosValue;
//	}
//	else
//		m_bBadRho = VARIANT_TRUE;
//
//	// ThetaDeltaInShares
//	_CHK(spPos->get_ThetaDeltaInShares(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dThetaDelta <= BAD_DOUBLE_VALUE) m_dThetaDelta = 0.;
//		m_dThetaDelta += dPosValue;
//	}
//	else
//		m_bBadThetaDelta = VARIANT_TRUE;
//
//	// ThetaGammaInShares
//	_CHK(spPos->get_ThetaGammaInShares(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dThetaGamma <= BAD_DOUBLE_VALUE) m_dThetaGamma = 0.;
//		m_dThetaGamma += dPosValue;
//	}
//	else
//		m_bBadThetaGamma = VARIANT_TRUE;
//
//	// VegaDeltaInShares
//	_CHK(spPos->get_VegaDeltaInShares(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dVegaDelta <= BAD_DOUBLE_VALUE) m_dVegaDelta = 0.;
//		m_dVegaDelta += dPosValue;
//	}
//	else
//		m_bBadVegaDelta = VARIANT_TRUE;
//
//	// VegaGammaInShares
//	_CHK(spPos->get_VegaGammaInShares(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dVegaGamma <= BAD_DOUBLE_VALUE) m_dVegaGamma = 0.;
//		m_dVegaGamma += dPosValue;
//	}
//	else
//		m_bBadVegaGamma = VARIANT_TRUE;
//
//	// TimeValue
//	_CHK(spPos->get_TimeValue(&dPosValue));
//	if(dPosValue > BAD_DOUBLE_VALUE)
//	{
//		if(m_dTimeValue <= BAD_DOUBLE_VALUE) m_dTimeValue = 0.;
//		m_dTimeValue += dPosValue;
//	}
//	else
//		m_bBadTimeValue = VARIANT_TRUE;
//
//	VARIANT_BOOL bPosIsSynthetic = VARIANT_FALSE;
//	_CHK(spPos->get_IsSynthetic(&bPosIsSynthetic));
//	if(bPosIsSynthetic)
//	{
//		IMmRvSynthGreeksCollPtr spPosSynthGreeksColl;
//		_CHK(spPos->get_SynthGreeks(&spPosSynthGreeksColl));
//		
//		if(spPosSynthGreeksColl != NULL)
//		{
//			IMmRvSynthGreeksAtomPtr spPosSynthGreeks;
//			LONG nSynthUndID = 0L;
//			DOUBLE dSelfValue = BAD_DOUBLE_VALUE;
//
//			IUnknownPtr spUnk;
//			_variant_t varItem;
//			ULONG nFetched = 0L;
//			HRESULT hr;
//
//			_CHK(spPosSynthGreeksColl->get__NewEnum(&spUnk));
//			IEnumVARIANTPtr spPosSynthGreekEnum(spUnk);
//			_CHK(spPosSynthGreekEnum->Reset());
//			while((hr = spPosSynthGreekEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//			{
//				ATLASSERT(varItem.vt == VT_DISPATCH);
//				spPosSynthGreeks = varItem;
//				if(spPosSynthGreeks != NULL)
//				{
//					_CHK(spPosSynthGreeks->get_SynthUndID(&nSynthUndID));
//					IMmRvSynthGreeksAtomPtr spSynthGreeks;
//					_CHK(m_spSynthGreeks->get_Item(nSynthUndID, &spSynthGreeks));
//
//					if(spSynthGreeks != NULL)
//					{
//						// DeltaInShares
//						_CHK(spPosSynthGreeks->get_DeltaInShares(&dPosValue));
//						if(dPosValue > BAD_DOUBLE_VALUE)
//						{
//							_CHK(spSynthGreeks->get_DeltaInShares(&dSelfValue));
//							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
//							_CHK(spSynthGreeks->put_DeltaInShares(dSelfValue + dPosValue));
//						}
//						else
//							_CHK(spSynthGreeks->put_BadDelta(VARIANT_TRUE));
//
//						// GammaInSharesPerc
//						_CHK(spPosSynthGreeks->get_GammaInSharesPerc(&dPosValue));
//						if(dPosValue > BAD_DOUBLE_VALUE)
//						{
//							_CHK(spSynthGreeks->get_GammaInSharesPerc(&dSelfValue));
//							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
//							_CHK(spSynthGreeks->put_GammaInSharesPerc(dSelfValue + dPosValue));
//						}
//						else
//							_CHK(spSynthGreeks->put_BadGammaPerc(VARIANT_TRUE));
//
//						// GammaInShares
//						_CHK(spPosSynthGreeks->get_GammaInShares(&dPosValue));
//						if(dPosValue > BAD_DOUBLE_VALUE)
//						{
//							_CHK(spSynthGreeks->get_GammaInShares(&dSelfValue));
//							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
//							_CHK(spSynthGreeks->put_GammaInShares(dSelfValue + dPosValue));
//						}
//						else
//							_CHK(spSynthGreeks->put_BadGamma(VARIANT_TRUE));
//
//						// Net Gamma
//						_CHK(spPosSynthGreeks->get_NetGamma(&dPosValue));
//						if(dPosValue > BAD_DOUBLE_VALUE)
//						{
//							_CHK(spSynthGreeks->get_NetGamma(&dSelfValue));
//							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
//							_CHK(spSynthGreeks->put_NetGamma(dSelfValue + dPosValue));
//						}
//						else
//							_CHK(spSynthGreeks->put_BadNetGamma(VARIANT_TRUE));
//
//					}
//				}
//			}
//		}
//	}
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//void CMmRvUndAtom::_ClearSynthGreeks() throw()
//{
//	if(m_bHasSynthetic && m_spSynthGreeks != NULL)
//	{
//		IUnknownPtr spUnk;
//		_variant_t varItem;
//		ULONG nFetched = 0L;
//		HRESULT hr;
//		IMmRvSynthGreeksAtomPtr spSynthGreeks;
//
//		_CHK(m_spSynthGreeks->get__NewEnum(&spUnk));
//		IEnumVARIANTPtr spSynthGreekEnum(spUnk);
//		_CHK(spSynthGreekEnum->Reset());
//		while((hr = spSynthGreekEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//		{
//			ATLASSERT(varItem.vt == VT_DISPATCH);
//			spSynthGreeks = varItem;
//			if(spSynthGreeks != NULL)
//				_CHK(spSynthGreeks->ClearValuesInShares());
//		}
//	}
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//STDMETHODIMP CMmRvUndAtom::CalcWtdVega(IEtsExpCalColl* aExpCalColl)
//{
//	if(aExpCalColl == NULL)
//		return Error(L"Invalid objects passed.", IID_IMmRvUndAtom, E_INVALIDARG);
//
//	try
//	{
//		m_bBadWtdVega = VARIANT_FALSE;
//		m_dWtdVega = BAD_DOUBLE_VALUE;
//
//		IUnknownPtr spUnk;
//		_variant_t varItem;
//		ULONG nFetched = 0L;
//		HRESULT hr;
//		DATE dtToday = vt_date::GetCurrentDate(true);
//
//		IEtsExpCalCollPtr spExpCalColl(aExpCalColl);
//		IMmRvPosAtomPtr spPos;
//
//		_CHK(m_spPos->get__NewEnum(&spUnk));
//		IEnumVARIANTPtr spPosEnum(spUnk);
//		_CHK(spPosEnum->Reset());
//		while((hr = spPosEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//		{
//			ATLASSERT(varItem.vt == VT_DISPATCH);
//			spPos = varItem;
//			if(spPos != NULL)
//			{
//				EtsContractTypeEnum enContractType = enCtNone;
//				_CHK(spPos->get_ContractType(&enContractType));
//				
//				if(enContractType == enCtOption || enContractType == enCtFutOption)
//				{
//					DOUBLE dVegaWeight = BAD_DOUBLE_VALUE;
//					DATE dtExpiry = 0.;
//					_CHK(spPos->get_Expiry(&dtExpiry));
//
//					if(enContractType == enCtOption)
//						dVegaWeight = spExpCalColl->GetVegaWeight(m_nExpCalendarID, dtExpiry);
//					else
//					{
//						LONG nExpCalendarID = 0L;
//						IMmRvFutAtomPtr spFut;
//						_CHK(spPos->get_Fut(&spFut));
//
//						if(spFut != NULL)
//						{
//							_CHK(spFut->get_ExpCalendarID(&nExpCalendarID));
//							dVegaWeight = spExpCalColl->GetVegaWeight(nExpCalendarID, dtExpiry);
//						}
//					}
//
//					_CHK(spPos->put_VegaWeight(dVegaWeight));
//
//					VARIANT_BOOL bVisible = VARIANT_FALSE;
//					_CHK(spPos->get_Visible(&bVisible));
//					if(bVisible && dtExpiry >= dtToday && dVegaWeight > BAD_DOUBLE_VALUE)
//					{
//						DOUBLE dPosValue = BAD_DOUBLE_VALUE;
//						// VegaInShares
//						_CHK(spPos->get_VegaInShares(&dPosValue));
//						if(dPosValue > BAD_DOUBLE_VALUE)
//						{
//							_CHK(spPos->put_WtdVega(dPosValue * dVegaWeight));
//
//							if(m_dWtdVega <= BAD_DOUBLE_VALUE) m_dWtdVega = 0.;
//							m_dWtdVega += dPosValue * dVegaWeight;
//						}
//						else
//							m_bBadWtdVega = VARIANT_TRUE;
//					}
//				}
//			}
//		}
//	}
//	catch(const _com_error& e)
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvUndAtom, e.Error());
//	}
//	return S_OK;
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//STDMETHODIMP CMmRvUndAtom::CalcSyntheticUnderlying(IMmRvUndColl* aUndColl,
//													LONG nMask,
//													VARIANT_BOOL bIsPnlLTD,
//													EtsCalcModelTypeEnum enCalcModel,
//													VARIANT_BOOL bUseTheoVolatility,
//													VARIANT_BOOL bUseTheoVolaNoBid,
//													VARIANT_BOOL bUseTheoVolaBadMarket,
//													DOUBLE dUndPriceTolerance,
//													EtsPriceRoundingRuleEnum enPriceRoundingRule)
//{
//	if(aUndColl == NULL)
//		return Error(L"Invalid objects passed.", IID_IMmRvUndAtom, E_INVALIDARG);
//
//	try
//	{
//		IUnknownPtr spUnk;
//		_variant_t varItem;
//		ULONG nFetched = 0L;
//		HRESULT hr;
//
//		DOUBLE dUndPriceMid = 0.;
//		if(m_spUndPriceProfile != NULL)
//		{
//			dUndPriceMid = m_spUndPriceProfile->GetUndPriceMid(m_dPriceBid, m_dPriceAsk,
//				m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, NULL, TRUE);
//		}
//
//		IMmRvUndCollPtr spUndColl(aUndColl);
//		IMmRvUndCollPtr spUndColl2;
//		IMmRvPosAtomPtr spPos;
//		IMmRvUndAtomPtr spUnd, spUnd2;
//
//		_CHK(spUndColl2.CreateInstance(CLSID_MmRvUndColl), _T("Fail to create underlings."));
//		if(spUndColl2 == NULL)
//			return Error(L"Fail to create underlings.", IID_IMmRvUndAtom, E_INVALIDARG);
//
//		spUndColl2.AddRef();
//
//		_CHK(m_spSynthPos->get__NewEnum(&spUnk));
//		IEnumVARIANTPtr spPosEnum(spUnk);
//		_CHK(spPosEnum->Reset());
//		while((hr = spPosEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//		{
//			ATLASSERT(varItem.vt == VT_DISPATCH);
//			spPos = varItem;
//			if(spPos != NULL)
//			{
//				EtsContractTypeEnum enContractType = enCtNone;
//				_CHK(spPos->get_ContractType(&enContractType));
//
//				if(enContractType == enCtOption)
//				{
//					LONG nUndID = 0L;
//					_CHK(spPos->get_UndID(&nUndID));
//					_CHK(spUndColl->get_Item(nUndID, &spUnd));
//
//					if(spUnd != NULL)
//					{
//						_CHK(spUndColl2->get_Item(nUndID, &spUnd2));
//						if(spUnd2 == NULL)
//							_CHK(spUndColl2->Add(nUndID, L"", spUnd, NULL));
//
//						_CHK(spUnd->ClearValues());
//						_CHK(spPos->CalcOptionGreeks(spUndColl, this, dUndPriceMid,
//							nMask, bIsPnlLTD, enCalcModel,
//							bUseTheoVolatility, bUseTheoVolaNoBid, bUseTheoVolaBadMarket,
//							dUndPriceTolerance, enPriceRoundingRule));
//					}
//				}
//			}
//		}
//
//		_CHK(spUndColl2->get__NewEnum(&spUnk));
//		IEnumVARIANTPtr spUndEnum(spUnk);
//		_CHK(spUndEnum->Reset());
//		while((hr = spUndEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//		{
//			ATLASSERT(varItem.vt == VT_DISPATCH);
//			spUnd = varItem;
//			if(spUnd != NULL)
//			{
//				LONG nUndID = 0L;
//				_CHK(spUnd->get_ID(&nUndID));
//				if(nUndID != m_nID)
//				{
//					_CHK(spUnd->Calc(spUndColl,
//									nMask,
//									VARIANT_TRUE,
//									VARIANT_TRUE,
//									VARIANT_FALSE,
//									VARIANT_TRUE,
//									NULL,
//									bIsPnlLTD,
//									enCalcModel,
//									bUseTheoVolatility,
//									bUseTheoVolaNoBid,
//									bUseTheoVolaBadMarket,
//									dUndPriceTolerance,
//									enPriceRoundingRule,
//									NULL, NULL, NULL));
//				}
//			}
//		}
//
//		spUndColl2 = NULL;
//	}
//	catch(const _com_error& e)
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvUndAtom, e.Error());
//	}
//	return S_OK;
//}
