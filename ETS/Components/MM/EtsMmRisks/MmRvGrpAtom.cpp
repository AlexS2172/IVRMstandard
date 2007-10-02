// MmRvGrpAtom.cpp : Implementation of CMmRvGrpAtom

#include "stdafx.h"
#include "MmRvGrpAtom.h"
#include "MmRvUndColl.h"

/////////////////////////////////////////////////////////////////////////////
//
HRESULT CMmRvGrpAtom::CalcGroup( CMmRvUndColl* pUndColl,
										  CMmRvUndAtom* pIdx,
										  VARIANT_BOOL  bTotals,
										  LONG nMask,
										  VARIANT_BOOL bCalcGreeks,
										  VARIANT_BOOL bUpdateVola,
										  VARIANT_BOOL bRealtimeCalc,
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
	if(pUndColl == NULL || pIdx == NULL)
		return Error(L"Invalid objects passed.", IID_IMmRvGrpAtom, E_INVALIDARG);

	try
	{
		__MmRvGrpAtom::ClearValues();

		IEtsProcessDelayPtr spDelay(aDelay);
		if(spDelay != NULL && spDelay->IsInterrupted)
			return S_OK;

		if(pnOptUpdated)
			*pnOptUpdated = 0L;

		if(pnUndUpdated)
			*pnUndUpdated = 0L;

		if(pnFutUpdated)
			*pnFutUpdated = 0L;

		IUnknownPtr spUnk;
		_variant_t varItem;
		ULONG nFetched = 0L;
		//		HRESULT hr;

		DOUBLE		  dIdxPrice = 0.;
		LONG nIdxID = pIdx->m_nID;
		DOUBLE activeFuturePrice = 0.;

		if(nIdxID != 0L)
		{
			EtsReplacePriceStatusEnum enPriceStatusMid = enRpsNone;
			DOUBLE dPriceBid = 0., dPriceAsk = 0., dPriceLast = 0.;
			DOUBLE dFutPriceBid = 0., dFutPriceAsk = 0., dFutPriceLast = 0.;
			DOUBLE activeFutureBasis = 0.;

			IEtsPriceProfileAtomPtr spUndPriceProfile;
			spUndPriceProfile = pIdx->m_spUndPriceProfile;

			if(spUndPriceProfile != NULL)
			{
				dPriceBid  = pIdx->m_pPrice->m_dPriceBid;
				dPriceAsk  = pIdx->m_pPrice->m_dPriceAsk;
				dPriceLast = pIdx->m_pPrice->m_dPriceLast;

				dIdxPrice = spUndPriceProfile->GetUndPriceMid(dPriceBid, dPriceAsk,
					dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enPriceStatusMid, VARIANT_FALSE);
			}

			pIdx->m_enReplacePriceStatus = enPriceStatusMid;

			// get active future for index prices
			IMmRvFutAtomPtr spActiveFuture;
			_CHK( pIdx->get_ActiveFuture(&spActiveFuture) );
			if (spActiveFuture)	{
				_CHK(spActiveFuture->get_Basis(&activeFutureBasis));	// get basis value

				// get active future price
				IEtsPriceProfileAtomPtr activeFuturePriceProfile;
				_CHK(spActiveFuture->get_UndPriceProfile(&activeFuturePriceProfile));
				if ( NULL != activeFuturePriceProfile)
				{
					IMmRvPricePtr spPrice;
					_CHK(spActiveFuture->get_Price(&spPrice));

					_CHK(spPrice->get_Bid(&dFutPriceBid));
					_CHK(spPrice->get_Ask(&dFutPriceAsk));
					_CHK(spPrice->get_Last(&dFutPriceLast));
					activeFuturePrice = activeFuturePriceProfile->GetUndPriceMid(dFutPriceBid, dFutPriceAsk,
						dFutPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enPriceStatusMid, VARIANT_FALSE);
					if ( activeFuturePrice > 0.){
						activeFuturePrice += activeFutureBasis;
						dIdxPrice = activeFuturePrice;
						spPrice->put_Active(activeFuturePrice);
					}
				}
			}
		}

		CMmRvUndColl::EnumCollType::iterator itUnd    =  pUndColl->m_coll.begin();
		CMmRvUndColl::EnumCollType::iterator itUndEnd =  pUndColl->m_coll.end();


		for(; itUnd != itUndEnd; ++itUnd)
		{
			CMmRvUndAtom* pUnd = dynamic_cast<CMmRvUndAtom*>(itUnd->second);

			if(pUnd != NULL)
			{
				if(bTotals == VARIANT_FALSE)
				{
					_CHK(pUnd->Calc(pUndColl,
						nMask,
						bCalcGreeks,
						bUpdateVola,
						bRealtimeCalc,
						VARIANT_TRUE,
						spDelay,
						bIsPnlLTD,
						enCalcModel,
						bUseTheoVolatility,
						bUseTheoVolaNoBid,
						bUseTheoVolaBadMarket,
						dUndPriceTolerance,
						enPriceRoundingRule,
						/*lDayShift,*/
						pnOptUpdated,
						pnUndUpdated,
						pnFutUpdated,
						dtCalcDate ));
				}

				DOUBLE dUndMidPrice = 0.;

				IEtsPriceProfileAtomPtr spUndPriceProfile = pUnd->m_spUndPriceProfile;

				if(spUndPriceProfile != NULL)
				{
					//CComObject<CMmRvPrice>* pPrice = pUnd->m_pPrice;
					//dUndMidPrice = spUndPriceProfile->GetUndPriceMid(pPrice->m_dPriceBid, pPrice->m_dPriceAsk,pPrice->m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, NULL);
					VARIANT_BOOL	futureUsed = VARIANT_FALSE;
					EtsReplacePriceStatusEnum	dummy;
					_CHK(pUnd->GetUnderlyingPrice(dUndPriceTolerance, enPriceRoundingRule, &dummy ,&futureUsed, &dUndMidPrice) );
				}

				//asset group component computation coefficient
				DOUBLE	dCoeff = 1.0;
				if (pUnd->m_bIsHead == VARIANT_TRUE || pUnd->m_spHeadComponent)
					dCoeff	=	pUnd->m_dCoeff;

				// PnlMtm
				if(pUnd->PnlMTM_ > BAD_DOUBLE_VALUE)
				{
					if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
					m_dPnlMtm += pUnd->PnlMTM_;
				}
				if(VARIANT_FALSE != pUnd->BadPnlMtm_) m_bBadPnlMtm = VARIANT_TRUE;

				// PnlTheo
				if(pUnd->PnLTheo_ > BAD_DOUBLE_VALUE)
				{
					if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
					m_dPnlTheo += pUnd->PnLTheo_;
				}
				if(VARIANT_FALSE != pUnd->BadPnlTheo_) m_bBadPnlTheo = VARIANT_TRUE;

				// Vega
				if(pUnd->Vga$_ > BAD_DOUBLE_VALUE)
				{
					if(m_dVega <= BAD_DOUBLE_VALUE) m_dVega = 0.;
					m_dVega += pUnd->Vga$_;
				}
				if(VARIANT_FALSE != pUnd->BadVga$_) m_bBadVega = VARIANT_TRUE;

				// WtdVega
				if(pUnd->WtdVga$_ > BAD_DOUBLE_VALUE)
				{
					if(m_dWtdVega <= BAD_DOUBLE_VALUE) m_dWtdVega = 0.;
					m_dWtdVega += pUnd->WtdVga$_;
				}
				if(VARIANT_FALSE != pUnd->BadWtdVga$_) m_bBadWtdVega = VARIANT_TRUE;

				// Theta
				if(pUnd->Tht$_ > BAD_DOUBLE_VALUE)
				{
					if(m_dTheta <= BAD_DOUBLE_VALUE) m_dTheta = 0.;
					m_dTheta += pUnd->Tht$_;
				}
				if(VARIANT_FALSE != pUnd->BadTht$_) m_bBadTheta = VARIANT_TRUE;

				// DeltaEq
				if(pUnd->NetDlt$_ > BAD_DOUBLE_VALUE)
				{
					if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
					m_dDeltaEq += pUnd->NetDlt$_ * dCoeff;
				}
				if(pUnd->NetExposureSort_ > BAD_DOUBLE_VALUE)
				{
					if(m_dNetExposureShort ==BAD_DOUBLE_VALUE) m_dNetExposureShort = 0.0;
					m_dNetExposureShort += pUnd->NetExposureSort_ ; 
				}
				if(pUnd->NetExposureLong_ > BAD_DOUBLE_VALUE)
				{
					if(m_dNetExposureLong ==BAD_DOUBLE_VALUE) m_dNetExposureLong = 0.0;
					m_dNetExposureLong += pUnd->NetExposureLong_ ; 
				}

				if(pUnd->BadNetExposure_!=VARIANT_FALSE)
					m_bBadNetExposure = VARIANT_TRUE;

				if(VARIANT_FALSE != pUnd->BadNetDlt$_) m_bBadDeltaEq = VARIANT_TRUE;

				// GammaEq
				/*if(pUnd->NetGma$_ > BAD_DOUBLE_VALUE)
				{
					if(m_dGammaEq <= BAD_DOUBLE_VALUE) m_dGammaEq = 0.;
					m_dGammaEq += pUnd->NetGma$_;
				}
				if(VARIANT_FALSE != pUnd->BadNetGma$_) m_bBadGammaEq = VARIANT_TRUE;*/

				// m_dNetGammaEq
				if(pUnd->NetGma$_ > BAD_DOUBLE_VALUE)
				{
					if(m_dNetGammaEq <= BAD_DOUBLE_VALUE) m_dNetGammaEq = 0.;
					m_dNetGammaEq += pUnd->NetGma$_ * dCoeff * dCoeff;
				}
				if(VARIANT_FALSE != pUnd->BadNetGma$_) m_bBadNetGammaEq = VARIANT_TRUE;

				// Rho
				if(pUnd->Rho$_ > BAD_DOUBLE_VALUE)
				{
					if(m_dRho <= BAD_DOUBLE_VALUE) m_dRho = 0.;
					m_dRho += pUnd->Rho$_;
				}
				if(VARIANT_FALSE != pUnd->BadRho$_) m_bBadRho = VARIANT_TRUE;

				// OptDelta
				if(pUnd->OptDlt_ > BAD_DOUBLE_VALUE && (dUndMidPrice > DBL_EPSILON || pUnd->m_enContractType == enCtFutUnd))
				{
					if(m_dOptDelta <= BAD_DOUBLE_VALUE) m_dOptDelta = 0.;

					m_dOptDelta += pUnd->OptDlt$_ * dCoeff;
				}
				if(VARIANT_FALSE != pUnd->BadOptDelta_) m_bBadOptDelta = VARIANT_TRUE;

				// NetDelta & BetaWtdDelta
				if(pUnd->NetDlt_ > BAD_DOUBLE_VALUE)
				{
					if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
					m_dNetDelta += pUnd->NetDlt_ * dCoeff;

					DOUBLE dBeta = pUnd->Beta_;
					if(dBeta > BAD_DOUBLE_VALUE && DoubleNEQZero(dBeta) && dUndMidPrice > DBL_EPSILON)
					{
						if(m_dBetaWtdDelta <= BAD_DOUBLE_VALUE) m_dBetaWtdDelta = 0.;
						m_dBetaWtdDelta += pUnd->NetDlt_ * dBeta * dUndMidPrice;
					}
				}
				if(VARIANT_FALSE != pUnd->BadNetDelta_ )
				{
					m_bBadNetDelta = VARIANT_TRUE;
					m_bBadBetaWtdDelta = VARIANT_TRUE;
				}

				// NetGamma
				if(pUnd->Gma1$_ > BAD_DOUBLE_VALUE)
				{
					if(m_dNetGamma <= BAD_DOUBLE_VALUE) m_dNetGamma = 0.;
					m_dNetGamma += pUnd->Gma1$_ * dCoeff * dCoeff;
				}
				if(VARIANT_FALSE != pUnd->BadGma1$_) m_bBadNetGamma = VARIANT_TRUE;

				// BetaWtdDeltaEq
				if(pUnd->BetaWtdDelta$_ > BAD_DOUBLE_VALUE)
				{
					if(m_dBetaWtdDeltaEq <= BAD_DOUBLE_VALUE) m_dBetaWtdDeltaEq = 0.;
					m_dBetaWtdDeltaEq += pUnd->BetaWtdDelta$_;
				}
				if(VARIANT_FALSE != pUnd->BadBetaWtdDelta$_) m_bBadBetaWtdDeltaEq = VARIANT_TRUE;

				// synthetic Greeks
				if(VARIANT_FALSE != pUnd->m_bHasSynthetic)
					_CalcUndSynthValues(pUndColl, pUnd, dIdxPrice, dUndPriceTolerance, enPriceRoundingRule);

				//pUnd->CalcNetDeltas(pUnd->m_enContractType);
			}
		}

		if(dIdxPrice > DBL_EPSILON)
		{
			if(m_dDeltaEq > BAD_DOUBLE_VALUE)
			{
				if(m_dIdxDeltaEq <= BAD_DOUBLE_VALUE) m_dIdxDeltaEq = 0.;
				m_dIdxDeltaEq = m_dDeltaEq / dIdxPrice;
			}

			if(m_bBadDeltaEq) m_bBadIdxDeltaEq = VARIANT_TRUE;

			if(m_dBetaWtdDeltaEq > BAD_DOUBLE_VALUE)
				m_dBetaWtdDelta = m_dBetaWtdDeltaEq / dIdxPrice;
			else
			{
				m_dBetaWtdDelta = BAD_DOUBLE_VALUE;
				m_bBadBetaWtdDelta = VARIANT_TRUE;
			}
		}
		else
		{
			m_dBetaWtdDelta = BAD_DOUBLE_VALUE;
			m_bBadBetaWtdDelta = VARIANT_TRUE;
			m_bBadIdxDeltaEq = VARIANT_TRUE;
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvGrpAtom, e.Error());
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmRvGrpAtom::CalcWtdVega(IMmRvUndColl* aUndColl, IEtsExpCalColl* aExpCalColl)
{
	HRESULT hr = S_OK;

	if(aUndColl == NULL || aExpCalColl == NULL)
		return Error(L"Invalid objects passed.", IID_IMmRvGrpAtom, E_INVALIDARG);

	try
	{
		m_bBadWtdVega = VARIANT_FALSE;
		m_dWtdVega = BAD_DOUBLE_VALUE;

		IUnknownPtr spUnk;
		_variant_t varItem;
		ULONG nFetched = 0L;

		IEtsExpCalCollPtr spExpCalColl(aExpCalColl);
		CMmRvUndColl* pUndColl = dynamic_cast<CMmRvUndColl*>(aUndColl);
		if(pUndColl)
		{
			CMmRvUndColl::EnumCollType::iterator itUnd    =  pUndColl->m_coll.begin();
			CMmRvUndColl::EnumCollType::iterator itUndEnd =  pUndColl->m_coll.end();

			for(; itUnd != itUndEnd; ++itUnd)
			{
				CMmRvUndAtom* pUnd = dynamic_cast<CMmRvUndAtom*>(itUnd->second);
				if(pUnd)
				{
					IMmRvAggregationDataAtomPtr spUndData(pUnd);

					if(spUndData != NULL)
					{
						_CHK(pUnd->CalcWtdVega(spExpCalColl));

						// WtdVega
						if(pUnd->WtdVga$_ > BAD_DOUBLE_VALUE)
						{
							if(m_dWtdVega <= BAD_DOUBLE_VALUE) m_dWtdVega = 0.;
							m_dWtdVega += pUnd->WtdVga$_;
						}

						if(pUnd->BadWtdVga$_!=VARIANT_FALSE) 
							m_bBadWtdVega = VARIANT_TRUE;
					}
				}
			}
		}
	}
	catch(const _com_error& e)
	{
		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvGrpAtom, e.Error());
	}
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
//
void CMmRvGrpAtom::_CalcUndSynthValues(IMmRvUndCollPtr spUndColl, IMmRvUndAtomPtr spUnd, DOUBLE dIdxPrice, 
													DOUBLE dUndPriceTolerance, EtsPriceRoundingRuleEnum enPriceRoundingRule) throw()
{
	IMmRvSynthGreeksCollPtr spUndSynthGreeksColl;
	_CHK(spUnd->get_SynthGreeks(&spUndSynthGreeksColl));


	//-----------------------------------------------------------------------------------//
	DOUBLE	dTotalSynthNetExpLong	=	BAD_DOUBLE_VALUE;
	DOUBLE	dTotalSynthNetExpShort	=	BAD_DOUBLE_VALUE;
	DOUBLE	dAUM	=	BAD_DOUBLE_VALUE;
	DOUBLE	dCoeff	=	1.0;

	CMmRvUndAtom *pMainUnd = static_cast<CMmRvUndAtom*>(spUnd.GetInterfacePtr());
	
	if (pMainUnd)
	{
		dAUM	=	pMainUnd->GetNetExposureAUM();

		if (pMainUnd->m_spHeadComponent) 
			dCoeff = pMainUnd->m_dCoeff; //asset group component coeff
	}

 	if (pMainUnd->NetDlt$_ != BAD_DOUBLE_VALUE && dAUM != 0.0 && dAUM > BAD_DOUBLE_VALUE)
 	{
		DOUBLE	dNetExposure = pMainUnd->NetDlt$_ / dAUM * 100.0;
 		if (pMainUnd->NetDlt$_ < 0.0)
		{
			m_dNetExposureShort	-=	dNetExposure;
 			dTotalSynthNetExpShort	=	dNetExposure;
		}
 		else 
		{
			m_dNetExposureLong	-=	dNetExposure;
 			dTotalSynthNetExpLong = dNetExposure;
		}
 	}
	//-------------------------------------------------------------------------------------//
	if(spUndSynthGreeksColl != NULL)
	{
		LONG nSynthUndID = 0L;
		DOUBLE dSelfValue = BAD_DOUBLE_VALUE;
		IMmRvUndAtomPtr spSynthUnd;

		IUnknownPtr spUnk;
		_variant_t varItem;
		ULONG nFetched = 0L;
		HRESULT hr;

		_CHK(spUndSynthGreeksColl->get__NewEnum(&spUnk));
		IEnumVARIANTPtr spUndSynthGreekEnum(spUnk);
		_CHK(spUndSynthGreekEnum->Reset());
		while((hr = spUndSynthGreekEnum->Next(1L, &varItem, &nFetched)) == S_OK)
		{
			ATLASSERT(varItem.vt == VT_DISPATCH);
			IMmRvSynthGreeksAtomPtr spUndSynthGreeks(varItem);

			if(spUndSynthGreeks != NULL)
			{
				_CHK(spUndSynthGreeks->get_SynthUndID(&nSynthUndID));
				_CHK(spUndColl->get_Item(nSynthUndID, &spSynthUnd));
				IMmRvAggregationDataAtomPtr spSynthUndData(spSynthUnd);

				if(spSynthUnd != NULL && spSynthUndData != NULL)
				{
					EtsReplacePriceStatusEnum enPriceStatusMid = enRpsNone;
					DOUBLE dSynthUndMidPrice = 0.;

					IEtsPriceProfileAtomPtr spUndPriceProfile;
					_CHK(spSynthUnd->get_UndPriceProfile(&spUndPriceProfile));

					if(spUndPriceProfile != NULL)
					{
						/*DOUBLE dPriceBid = 0., dPriceAsk = 0., dPriceLast = 0.;
						IMmRvPricePtr spPrice;
						VARIANT_BOOL	bUseManualActive = VARIANT_FALSE;

						spSynthUndData->get_Price(&spPrice);

						_CHK(spPrice->get_Bid(&dPriceBid));
						_CHK(spPrice->get_Ask(&dPriceAsk));
						_CHK(spPrice->get_Last(&dPriceLast));

						_CHK(spPrice->get_IsUseManualActive(&bUseManualActive));
						if (bUseManualActive == VARIANT_FALSE)
							dSynthUndMidPrice = spUndPriceProfile->GetUndPriceMid(dPriceBid, dPriceAsk,
								dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enPriceStatusMid, VARIANT_FALSE);
						else
							_CHK(spPrice->get_Active(&dSynthUndMidPrice));*/
						enPriceStatusMid = enRpsNone;
						VARIANT_BOOL	bFutureUsed = VARIANT_FALSE;
						_CHK(spSynthUnd->GetUnderlyingPrice(dUndPriceTolerance,
														enPriceRoundingRule,
														&enPriceStatusMid,
														&bFutureUsed,
														&dSynthUndMidPrice));

					}
					_CHK(spSynthUnd->put_ReplacePriceStatus(enPriceStatusMid));

					DOUBLE dUndValue = BAD_DOUBLE_VALUE;
					// DeltaInShares
					_CHK(spUndSynthGreeks->get_DeltaInShares(&dUndValue));
					if(dUndValue > BAD_DOUBLE_VALUE)
					{

						if(dSynthUndMidPrice > DBL_EPSILON)
						{
							if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
							m_dDeltaEq += dUndValue * dSynthUndMidPrice * dCoeff;

							if(m_dOptDelta <= BAD_DOUBLE_VALUE) m_dOptDelta = 0.;
							m_dOptDelta += dUndValue * dSynthUndMidPrice * dCoeff;

							DOUBLE dDeltaInMoney = dUndValue * dSynthUndMidPrice;
							_CHK(spUndSynthGreeks->put_DeltaInMoney(dDeltaInMoney));

							DOUBLE dBeta = BAD_DOUBLE_VALUE, dBetaWtdDeltaInMoney = BAD_DOUBLE_VALUE;
							_CHK(spSynthUndData->get_Beta(&dBeta));

							if(nSynthUndID == 0L) // USD_ID
							{
								if(m_dBetaWtdDelta <= BAD_DOUBLE_VALUE) m_dBetaWtdDelta = 0.;
								m_dBetaWtdDelta += dUndValue;
								dBetaWtdDeltaInMoney = dDeltaInMoney;
							}
							else if(dBeta > BAD_DOUBLE_VALUE && DoubleNEQZero(dBeta) && dIdxPrice > DBL_EPSILON)
							{
								if(m_dBetaWtdDelta <= BAD_DOUBLE_VALUE) m_dBetaWtdDelta = 0.;
								m_dBetaWtdDelta += dUndValue * dBeta * dSynthUndMidPrice;
								dBetaWtdDeltaInMoney = dDeltaInMoney * dBeta;
							}
							else
							{
								m_bBadBetaWtdDelta = VARIANT_TRUE;
								_CHK(spUndSynthGreeks->put_BadBetaWtdDeltaInMoney(VARIANT_TRUE));
							}

							_CHK(spUndSynthGreeks->put_BetaWtdDeltaInMoney(dBetaWtdDeltaInMoney));

							if(dBetaWtdDeltaInMoney > BAD_DOUBLE_VALUE)
							{
								if(m_dBetaWtdDeltaEq <= BAD_DOUBLE_VALUE) m_dBetaWtdDeltaEq = 0.;
								m_dBetaWtdDeltaEq += dBetaWtdDeltaInMoney;
							}

							if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
							m_dNetDelta += dUndValue * dCoeff;
							dUndValue = 0.0;


						}
						else
						{
							m_bBadDeltaEq = VARIANT_TRUE;
							m_bBadOptDelta = VARIANT_TRUE;
							m_bBadBetaWtdDelta = VARIANT_TRUE;
							_CHK(spUndSynthGreeks->put_BadDeltaInMoney(VARIANT_TRUE));
							_CHK(spUndSynthGreeks->put_BadBetaWtdDeltaInMoney(VARIANT_TRUE));

							if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
							m_dNetDelta += dUndValue * dCoeff;
							dUndValue = 0.0;

						}
					}

					//[12/26/2006] Appearence of SU
					// NetExposure
					_CHK(spUndSynthGreeks->get_NetExposure(&dUndValue));
					if (dUndValue != BAD_DOUBLE_VALUE)
					{
						if (dUndValue < 0.0)
						{
							if (dTotalSynthNetExpShort==BAD_DOUBLE_VALUE) dTotalSynthNetExpShort = 0.0;
							dTotalSynthNetExpShort += dUndValue;
						}
						else
						{
							if (dTotalSynthNetExpLong==BAD_DOUBLE_VALUE) dTotalSynthNetExpLong = 0.0;
							dTotalSynthNetExpLong += dUndValue;
						}
					}

					// GammaInSharesPerc
					_CHK(spUndSynthGreeks->get_GammaInSharesPerc(&dUndValue));
					if(dUndValue > BAD_DOUBLE_VALUE && dSynthUndMidPrice > DBL_EPSILON)
					{
						if(m_dGammaEq <= BAD_DOUBLE_VALUE) m_dGammaEq = 0.;
						m_dGammaEq += dUndValue * dSynthUndMidPrice * dCoeff * dCoeff;
					}
					else
						m_bBadGammaEq = VARIANT_TRUE;

					// GammaInShares
					_CHK(spUndSynthGreeks->get_GammaInShares(&dUndValue));
					if(dUndValue > BAD_DOUBLE_VALUE)
					{
						if(m_dNetGamma <= BAD_DOUBLE_VALUE) m_dNetGamma = 0.;
						m_dNetGamma += dUndValue * dCoeff * dCoeff;
					}
					else
						m_bBadNetGamma = VARIANT_TRUE;

					// NetGammaEq
					_CHK(spUndSynthGreeks->get_NetGamma(&dUndValue));
					if(dUndValue > BAD_DOUBLE_VALUE)
					{
						if(m_dNetGammaEq <= BAD_DOUBLE_VALUE) m_dNetGammaEq = 0.;
						m_dNetGammaEq += dUndValue * dCoeff * dCoeff;
					}
					else
						m_bBadNetGammaEq = VARIANT_TRUE;

					// BadDelta
					VARIANT_BOOL bUndValue = VARIANT_FALSE;
					_CHK(spUndSynthGreeks->get_BadDelta(&bUndValue));
					if(bUndValue)
					{
						m_bBadDeltaEq = VARIANT_TRUE;
						m_bBadOptDelta = VARIANT_TRUE;
						m_bBadBetaWtdDelta = VARIANT_TRUE;
						_CHK(spUndSynthGreeks->put_BadDeltaInMoney(VARIANT_TRUE));
						_CHK(spUndSynthGreeks->put_BadBetaWtdDeltaInMoney(VARIANT_TRUE));
					}

					// BadGammaPerc
					_CHK(spSynthUndData->get_BadGammaPerc(&bUndValue));
					if(bUndValue)
						m_bBadGammaEq = VARIANT_TRUE;

					// BadGamma
					_CHK(spSynthUndData->get_BadGamma(&bUndValue));
					if(bUndValue)
						m_bBadNetGamma = VARIANT_TRUE;
				}
			}
		}

		if (m_dNetExposureLong==BAD_DOUBLE_VALUE) m_dNetExposureLong = 0.0;
		if (dTotalSynthNetExpLong!=BAD_DOUBLE_VALUE)
			m_dNetExposureLong += dTotalSynthNetExpLong;
		if (m_dNetExposureShort==BAD_DOUBLE_VALUE) m_dNetExposureShort = 0.0;
		if (dTotalSynthNetExpShort!=BAD_DOUBLE_VALUE)
			m_dNetExposureShort+= dTotalSynthNetExpShort;
	}

	if(dIdxPrice > DBL_EPSILON)
	{
		if(m_dDeltaEq > BAD_DOUBLE_VALUE)
		{
			if(m_dIdxDeltaEq <= BAD_DOUBLE_VALUE) m_dIdxDeltaEq = 0.;
			m_dIdxDeltaEq += m_dDeltaEq / dIdxPrice;
		}

		if(m_bBadDeltaEq)
			m_bBadIdxDeltaEq = VARIANT_TRUE;

		if(m_dBetaWtdDelta > BAD_DOUBLE_VALUE)
			m_dBetaWtdDelta /= dIdxPrice;
		else
			m_bBadBetaWtdDelta = VARIANT_TRUE;
	}
	else
	{
		m_dBetaWtdDelta = BAD_DOUBLE_VALUE;
		m_bBadBetaWtdDelta = VARIANT_TRUE;
		m_bBadIdxDeltaEq = VARIANT_TRUE;
	}
}

//// MmRvGrpAtom.cpp : Implementation of CMmRvGrpAtom
//
//#include "stdafx.h"
//#include "MmRvGrpAtom.h"
//#include "MmRvUndColl.h"
//
///////////////////////////////////////////////////////////////////////////////
////
//STDMETHODIMP CMmRvGrpAtom::Calc(IMmRvUndColl* aUndColl,
//								IMmRvUndAtom* aIdx,
//								VARIANT_BOOL  bTotals,
//								LONG nMask,
//								VARIANT_BOOL bCalcGreeks,
//								VARIANT_BOOL bUpdateVola,
//								VARIANT_BOOL bRealtimeCalc,
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
//	if(aUndColl == NULL || aIdx == NULL)
//		return Error(L"Invalid objects passed.", IID_IMmRvGrpAtom, E_INVALIDARG);
//
//	try
//	{
//		__MmRvGrpAtom::ClearValues();
//
//		IEtsProcessDelayPtr spDelay(aDelay);
//		if(spDelay != NULL && spDelay->IsInterrupted)
//			return S_OK;
//
//		if(pnOptUpdated)
//			*pnOptUpdated = 0L;
//
//		if(pnUndUpdated)
//			*pnUndUpdated = 0L;
//
//		if(pnFutUpdated)
//			*pnFutUpdated = 0L;
//
//		IUnknownPtr spUnk;
//		_variant_t varItem;
//		ULONG nFetched = 0L;
//		HRESULT hr;
//
//		DOUBLE dIdxPrice = 0.;
//		IMmRvUndAtomPtr spIdx(aIdx);
//		LONG nIdxID = 0L;
//		_CHK(spIdx->get_ID(&nIdxID));
//		
//		if(nIdxID != 0L)
//		{
//			EtsReplacePriceStatusEnum enPriceStatusMid = enRpsNone;
//			DOUBLE dPriceBid = 0., dPriceAsk = 0., dPriceLast = 0.;
//
//			IEtsPriceProfileAtomPtr spUndPriceProfile;
//			_CHK(spIdx->get_UndPriceProfile(&spUndPriceProfile));
//
//			if(spUndPriceProfile != NULL)
//			{
//				_CHK(spIdx->get_PriceBid(&dPriceBid));
//				_CHK(spIdx->get_PriceAsk(&dPriceAsk));
//				_CHK(spIdx->get_PriceLast(&dPriceLast));
//
//				dIdxPrice = spUndPriceProfile->GetUndPriceMid(dPriceBid, dPriceAsk,
//					dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enPriceStatusMid, TRUE);
//			}
//
//			_CHK(spIdx->put_ReplacePriceStatus(enPriceStatusMid));
//		}
//
//		IMmRvUndCollPtr spUndColl(aUndColl);
//		IMmRvUndAtomPtr spUnd;
//
//		_CHK(spUndColl->get__NewEnum(&spUnk));
//		IEnumVARIANTPtr spUndEnum(spUnk);
//		_CHK(spUndEnum->Reset());
//		while((hr = spUndEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//		{
//			ATLASSERT(varItem.vt == VT_DISPATCH);
//			spUnd = varItem;
//			if(spUnd != NULL)
//			{
//				if(bTotals == VARIANT_FALSE)
//				{
//					_CHK(spUnd->Calc(spUndColl,
//						nMask,
//						bCalcGreeks,
//						bUpdateVola,
//						bRealtimeCalc,
//						VARIANT_TRUE,
//						spDelay,
//						bIsPnlLTD,
//						enCalcModel,
//						bUseTheoVolatility,
//						bUseTheoVolaNoBid,
//						bUseTheoVolaBadMarket,
//						dUndPriceTolerance,
//						enPriceRoundingRule,
//						pnOptUpdated,
//						pnUndUpdated,
//						pnFutUpdated));
//				}
//
//				DOUBLE dUndMidPrice = 0.;
//
//				IEtsPriceProfileAtomPtr spUndPriceProfile;
//				_CHK(spUnd->get_UndPriceProfile(&spUndPriceProfile));
//
//				if(spUndPriceProfile != NULL)
//				{
//					DOUBLE dPriceBid = 0., dPriceAsk = 0., dPriceLast = 0.;
//					_CHK(spUnd->get_PriceBid(&dPriceBid));
//					_CHK(spUnd->get_PriceAsk(&dPriceAsk));
//					_CHK(spUnd->get_PriceLast(&dPriceLast));
//
//					dUndMidPrice = spUndPriceProfile->GetUndPriceMid(dPriceBid, dPriceAsk,
//						dPriceLast, dUndPriceTolerance, enPriceRoundingRule, NULL, TRUE);
//				}
//
//				DOUBLE dUndValue = BAD_DOUBLE_VALUE;
//				VARIANT_BOOL bBadValue = VARIANT_FALSE;
//				// PnlMtm
//				_CHK(spUnd->get_PnlMtm(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
//					m_dPnlMtm += dUndValue;
//				}
//				_CHK(spUnd->get_BadPnlMtm(&bBadValue));
//				if(bBadValue) m_bBadPnlMtm = VARIANT_TRUE;
//
//				// PnlTheo
//				_CHK(spUnd->get_PnlTheo(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
//					m_dPnlTheo += dUndValue;
//				}
//				_CHK(spUnd->get_BadPnlTheo(&bBadValue));
//				if(bBadValue) m_bBadPnlTheo = VARIANT_TRUE;
//
//				// Vega
//				_CHK(spUnd->get_Vega(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dVega <= BAD_DOUBLE_VALUE) m_dVega = 0.;
//					m_dVega += dUndValue;
//				}
//				_CHK(spUnd->get_BadVega(&bBadValue));
//				if(bBadValue) m_bBadVega = VARIANT_TRUE;
//
//				// WtdVega
//				_CHK(spUnd->get_WtdVega(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dWtdVega <= BAD_DOUBLE_VALUE) m_dWtdVega = 0.;
//					m_dWtdVega += dUndValue;
//				}
//				_CHK(spUnd->get_BadWtdVega(&bBadValue));
//				if(bBadValue) m_bBadWtdVega = VARIANT_TRUE;
//
//				// Theta
//				_CHK(spUnd->get_Theta(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dTheta <= BAD_DOUBLE_VALUE) m_dTheta = 0.;
//					m_dTheta += dUndValue;
//				}
//				_CHK(spUnd->get_BadTheta(&bBadValue));
//				if(bBadValue) m_bBadTheta = VARIANT_TRUE;
//
//				// DeltaEq
//				_CHK(spUnd->get_DeltaEq(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
//					m_dDeltaEq += dUndValue;
//				}
//				_CHK(spUnd->get_BadDeltaEq(&bBadValue));
//				if(bBadValue) m_bBadDeltaEq = VARIANT_TRUE;
//
//				// GammaEq
//				_CHK(spUnd->get_GammaEq(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dGammaEq <= BAD_DOUBLE_VALUE) m_dGammaEq = 0.;
//					m_dGammaEq += dUndValue;
//				}
//				_CHK(spUnd->get_BadGammaEq(&bBadValue));
//				if(bBadValue) m_bBadGammaEq = VARIANT_TRUE;
//
//				// Rho
//				_CHK(spUnd->get_Rho(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dRho <= BAD_DOUBLE_VALUE) m_dRho = 0.;
//					m_dRho += dUndValue;
//				}
//				_CHK(spUnd->get_BadRho(&bBadValue));
//				if(bBadValue) m_bBadRho = VARIANT_TRUE;
//
//				// OptDelta
//				_CHK(spUnd->get_OptDelta(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE && dUndMidPrice > DBL_EPSILON)
//				{
//					if(m_dOptDelta <= BAD_DOUBLE_VALUE) m_dOptDelta = 0.;
//					m_dOptDelta += dUndValue * dUndMidPrice;
//				}
//				_CHK(spUnd->get_BadOptDelta(&bBadValue));
//				if(bBadValue) m_bBadOptDelta = VARIANT_TRUE;
//
//				// NetDelta & BetaWtdDelta
//				_CHK(spUnd->get_NetDelta(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
//					m_dNetDelta += dUndValue;
//
//					DOUBLE dBeta = BAD_DOUBLE_VALUE;
//					_CHK(spUnd->get_Beta(&dBeta));
//					if(dBeta > BAD_DOUBLE_VALUE && DoubleNEQZero(dBeta) && dUndMidPrice > DBL_EPSILON)
//					{
//						if(m_dBetaWtdDelta <= BAD_DOUBLE_VALUE) m_dBetaWtdDelta = 0.;
//						m_dBetaWtdDelta += dUndValue * dBeta * dUndMidPrice;
//					}
//				}
//				_CHK(spUnd->get_BadNetDelta(&bBadValue));
//				if(bBadValue)
//				{
//					m_bBadNetDelta = VARIANT_TRUE;
//					m_bBadBetaWtdDelta = VARIANT_TRUE;
//				}
//
//				// NetGamma
//				_CHK(spUnd->get_Gamma(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dNetGamma <= BAD_DOUBLE_VALUE) m_dNetGamma = 0.;
//					m_dNetGamma += dUndValue;
//				}
//				_CHK(spUnd->get_BadGamma(&bBadValue));
//				if(bBadValue) m_bBadNetGamma = VARIANT_TRUE;
//
//				// BetaWtdDeltaEq
//				_CHK(spUnd->get_BetaWtdDeltaEq(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dBetaWtdDeltaEq <= BAD_DOUBLE_VALUE) m_dBetaWtdDeltaEq = 0.;
//					m_dBetaWtdDeltaEq += dUndValue;
//				}
//				_CHK(spUnd->get_BadBetaWtdDeltaEq(&bBadValue));
//				if(bBadValue && m_bBadBetaWtdDelta) m_bBadBetaWtdDeltaEq = VARIANT_TRUE;
//
//				// synthetic greeks
//				VARIANT_BOOL bHasSynthetic = VARIANT_FALSE;
//				_CHK(spUnd->get_HasSynthetic(&bHasSynthetic));
//				if(bHasSynthetic)
//					_CalcUndSynthValues(spUndColl, spUnd, dIdxPrice, dUndPriceTolerance, enPriceRoundingRule);
//			}
//		}
//
//		if(dIdxPrice > DBL_EPSILON)
//		{
//			if(m_dDeltaEq > BAD_DOUBLE_VALUE)
//			{
//				if(m_dIdxDeltaEq <= BAD_DOUBLE_VALUE) m_dIdxDeltaEq = 0.;
//				m_dIdxDeltaEq = m_dDeltaEq / dIdxPrice;
//			}
//	        
//			if(m_bBadDeltaEq) m_bBadIdxDeltaEq = VARIANT_TRUE;
//	        
//			if(m_dBetaWtdDeltaEq > BAD_DOUBLE_VALUE)
//				m_dBetaWtdDelta = m_dBetaWtdDeltaEq / dIdxPrice;
//			else
//			{
//				m_dBetaWtdDelta = BAD_DOUBLE_VALUE;
//				m_bBadBetaWtdDelta = VARIANT_TRUE;
//			}
//		}
//		else
//		{
//			m_dBetaWtdDelta = BAD_DOUBLE_VALUE;
//			m_bBadBetaWtdDelta = VARIANT_TRUE;
//			m_bBadIdxDeltaEq = VARIANT_TRUE;
//		}
//	}
//	catch(const _com_error& e)
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvGrpAtom, e.Error());
//	}
//	return S_OK;
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//STDMETHODIMP CMmRvGrpAtom::CalcWtdVega(IMmRvUndColl* aUndColl, IEtsExpCalColl* aExpCalColl)
//{
//	if(aUndColl == NULL || aExpCalColl == NULL)
//		return Error(L"Invalid objects passed.", IID_IMmRvGrpAtom, E_INVALIDARG);
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
//
//		IEtsExpCalCollPtr spExpCalColl(aExpCalColl);
//		IMmRvUndCollPtr spUndColl(aUndColl);
//		IMmRvUndAtomPtr spUnd;
//
//		_CHK(spUndColl->get__NewEnum(&spUnk));
//		IEnumVARIANTPtr spUndEnum(spUnk);
//		_CHK(spUndEnum->Reset());
//		while((hr = spUndEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//		{
//			ATLASSERT(varItem.vt == VT_DISPATCH);
//			spUnd = varItem;
//			if(spUnd != NULL)
//			{
//				_CHK(spUnd->CalcWtdVega(spExpCalColl));
//
//				DOUBLE dUndValue = BAD_DOUBLE_VALUE;
//				VARIANT_BOOL bBadValue = VARIANT_FALSE;
//				// WtdVega
//				_CHK(spUnd->get_WtdVega(&dUndValue));
//				if(dUndValue > BAD_DOUBLE_VALUE)
//				{
//					if(m_dWtdVega <= BAD_DOUBLE_VALUE) m_dWtdVega = 0.;
//					m_dWtdVega += dUndValue;
//				}
//				_CHK(spUnd->get_BadWtdVega(&bBadValue));
//				if(bBadValue) m_bBadWtdVega = VARIANT_TRUE;
//			}
//		}
//	}
//	catch(const _com_error& e)
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvGrpAtom, e.Error());
//	}
//	return S_OK;
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//void CMmRvGrpAtom::_CalcUndSynthValues(IMmRvUndCollPtr spUndColl, IMmRvUndAtomPtr spUnd, DOUBLE dIdxPrice, 
//				   DOUBLE dUndPriceTolerance, EtsPriceRoundingRuleEnum enPriceRoundingRule) throw()
//{
//	IMmRvSynthGreeksCollPtr spUndSynthGreeksColl;
//	_CHK(spUnd->get_SynthGreeks(&spUndSynthGreeksColl));
//	
//	if(spUndSynthGreeksColl != NULL)
//	{
//		IMmRvSynthGreeksAtomPtr spUndSynthGreeks;
//		LONG nSynthUndID = 0L;
//		DOUBLE dSelfValue = BAD_DOUBLE_VALUE;
//		IMmRvUndAtomPtr spSynthUnd;
//
//		IUnknownPtr spUnk;
//		_variant_t varItem;
//		ULONG nFetched = 0L;
//		HRESULT hr;
//
//		_CHK(spUndSynthGreeksColl->get__NewEnum(&spUnk));
//		IEnumVARIANTPtr spUndSynthGreekEnum(spUnk);
//		_CHK(spUndSynthGreekEnum->Reset());
//		while((hr = spUndSynthGreekEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//		{
//			ATLASSERT(varItem.vt == VT_DISPATCH);
//			spUndSynthGreeks = varItem;
//			if(spUndSynthGreeks != NULL)
//			{
//				_CHK(spUndSynthGreeks->get_SynthUndID(&nSynthUndID));
//				_CHK(spUndColl->get_Item(nSynthUndID, &spSynthUnd));
//
//				if(spSynthUnd != NULL)
//				{
//					EtsReplacePriceStatusEnum enPriceStatusMid = enRpsNone;
//					DOUBLE dSynthUndMidPrice = 0.;
//
//					IEtsPriceProfileAtomPtr spUndPriceProfile;
//					_CHK(spSynthUnd->get_UndPriceProfile(&spUndPriceProfile));
//
//					if(spUndPriceProfile != NULL)
//					{
//						DOUBLE dPriceBid = 0., dPriceAsk = 0., dPriceLast = 0.;
//						_CHK(spSynthUnd->get_PriceBid(&dPriceBid));
//						_CHK(spSynthUnd->get_PriceAsk(&dPriceAsk));
//						_CHK(spSynthUnd->get_PriceLast(&dPriceLast));
//
//						dSynthUndMidPrice = spUndPriceProfile->GetUndPriceMid(dPriceBid, dPriceAsk,
//							dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enPriceStatusMid, TRUE);
//					}
//					_CHK(spSynthUnd->put_ReplacePriceStatus(enPriceStatusMid));
//
//					DOUBLE dUndValue = BAD_DOUBLE_VALUE;
//					// DeltaInShares
//					_CHK(spUndSynthGreeks->get_DeltaInShares(&dUndValue));
//					if(dUndValue > BAD_DOUBLE_VALUE)
//					{
//						if(dSynthUndMidPrice > DBL_EPSILON)
//						{
//							if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
//							m_dDeltaEq += dUndValue * dSynthUndMidPrice;
//
//							if(m_dOptDelta <= BAD_DOUBLE_VALUE) m_dOptDelta = 0.;
//							m_dOptDelta += dUndValue * dSynthUndMidPrice;
//
//							DOUBLE dDeltaInMoney = dUndValue * dSynthUndMidPrice;
//							_CHK(spUndSynthGreeks->put_DeltaInMoney(dDeltaInMoney));
//
//							DOUBLE dBeta = BAD_DOUBLE_VALUE, dBetaWtdDeltaInMoney = BAD_DOUBLE_VALUE;
//							_CHK(spSynthUnd->get_Beta(&dBeta));
//
//							if(nSynthUndID == 0L) // USD_ID
//							{
//								if(m_dBetaWtdDelta <= BAD_DOUBLE_VALUE) m_dBetaWtdDelta = 0.;
//								m_dBetaWtdDelta += dUndValue;
//								dBetaWtdDeltaInMoney = dDeltaInMoney;
//							}
//							else if(dBeta > BAD_DOUBLE_VALUE && DoubleNEQZero(dBeta) && dIdxPrice > DBL_EPSILON)
//							{
//								if(m_dBetaWtdDelta <= BAD_DOUBLE_VALUE) m_dBetaWtdDelta = 0.;
//								m_dBetaWtdDelta += dUndValue * dBeta * dSynthUndMidPrice;
//								dBetaWtdDeltaInMoney = dDeltaInMoney * dBeta;
//							}
//							else
//							{
//								m_bBadBetaWtdDelta = VARIANT_TRUE;
//								_CHK(spUndSynthGreeks->put_BadBetaWtdDeltaInMoney(VARIANT_TRUE));
//							}
//
//							_CHK(spUndSynthGreeks->put_BetaWtdDeltaInMoney(dBetaWtdDeltaInMoney));
//
//							if(dBetaWtdDeltaInMoney > BAD_DOUBLE_VALUE)
//							{
//								if(m_dBetaWtdDeltaEq <= BAD_DOUBLE_VALUE) m_dBetaWtdDeltaEq = 0.;
//								m_dBetaWtdDeltaEq += dBetaWtdDeltaInMoney;
//							}
//
//							if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
//							m_dNetDelta += dUndValue;
//							dUndValue = 0.0;
//
//
//						}
//						else
//						{
//							m_bBadDeltaEq = VARIANT_TRUE;
//							m_bBadOptDelta = VARIANT_TRUE;
//							m_bBadBetaWtdDelta = VARIANT_TRUE;
//							_CHK(spUndSynthGreeks->put_BadDeltaInMoney(VARIANT_TRUE));
//							_CHK(spUndSynthGreeks->put_BadBetaWtdDeltaInMoney(VARIANT_TRUE));
//
//							if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
//							m_dNetDelta += dUndValue;
//							dUndValue = 0.0;
//
//						}
//					}
//
//					// GammaInSharesPerc
//					_CHK(spUndSynthGreeks->get_GammaInSharesPerc(&dUndValue));
//					if(dUndValue > BAD_DOUBLE_VALUE && dSynthUndMidPrice > DBL_EPSILON)
//					{
//						if(m_dGammaEq <= BAD_DOUBLE_VALUE) m_dGammaEq = 0.;
//						m_dGammaEq += dUndValue * dSynthUndMidPrice;
//					}
//					else
//						m_bBadGammaEq = VARIANT_TRUE;
//
//					// GammaInShares
//					_CHK(spUndSynthGreeks->get_GammaInShares(&dUndValue));
//					if(dUndValue > BAD_DOUBLE_VALUE)
//					{
//						if(m_dNetGamma <= BAD_DOUBLE_VALUE) m_dNetGamma = 0.;
//						m_dNetGamma += dUndValue;
//					}
//					else
//						m_bBadNetGamma = VARIANT_TRUE;
//
//					// BadDelta
//					VARIANT_BOOL bUndValue = VARIANT_FALSE;
//					_CHK(spUndSynthGreeks->get_BadDelta(&bUndValue));
//					if(bUndValue)
//					{
//						m_bBadDeltaEq = VARIANT_TRUE;
//						m_bBadOptDelta = VARIANT_TRUE;
//						m_bBadBetaWtdDelta = VARIANT_TRUE;
//						_CHK(spUndSynthGreeks->put_BadDeltaInMoney(VARIANT_TRUE));
//						_CHK(spUndSynthGreeks->put_BadBetaWtdDeltaInMoney(VARIANT_TRUE));
//					}
//
//					// BadGammaPerc
//					_CHK(spSynthUnd->get_BadGammaPerc(&bUndValue));
//					if(bUndValue)
//						m_bBadGammaEq = VARIANT_TRUE;
//
//					// BadGamma
//					_CHK(spSynthUnd->get_BadGamma(&bUndValue));
//					if(bUndValue)
//						m_bBadNetGamma = VARIANT_TRUE;
//				}
//			}
//		}
//	}
//
//	if(dIdxPrice > DBL_EPSILON)
//	{
//		if(m_dDeltaEq > BAD_DOUBLE_VALUE)
//		{
//			if(m_dIdxDeltaEq <= BAD_DOUBLE_VALUE) m_dIdxDeltaEq = 0.;
//			m_dIdxDeltaEq += m_dDeltaEq / dIdxPrice;
//		}
//
//		if(m_bBadDeltaEq)
//			m_bBadIdxDeltaEq = VARIANT_TRUE;
//
//		if(m_dBetaWtdDelta > BAD_DOUBLE_VALUE)
//			m_dBetaWtdDelta /= dIdxPrice;
//		else
//			m_bBadBetaWtdDelta = VARIANT_TRUE;
//	}
//	else
//	{
//		m_dBetaWtdDelta = BAD_DOUBLE_VALUE;
//		m_bBadBetaWtdDelta = VARIANT_TRUE;
//		m_bBadIdxDeltaEq = VARIANT_TRUE;
//	}
//}


STDMETHODIMP CMmRvGrpAtom::put_NetExposureAUM(DOUBLE dNewVal)
{
	HRESULT hr = S_OK;
	if(m_dNetExposureAUM != dNewVal)
	{
		m_dNetExposureAUM = dNewVal;
	}
	return hr;
}

