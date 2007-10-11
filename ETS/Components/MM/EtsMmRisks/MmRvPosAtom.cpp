// MmRvPosAtom.cpp : Implementation of CMmRvPosAtom
#include "stdafx.h"
#include "MmRvPosAtom.h"
#include "MmRvUndColl.h"
#include "MmRvUndAtom.h"

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmRvPosAtom::CalcOptionGreeks(IMmRvUndColl* aUndColl,
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
														  DATE dtCalcDate)
{
	if(aUnd == NULL || aUndColl == NULL)
		return Error(L"Invalid objects passed.", IID_IMmRvPosAtom, E_INVALIDARG);

	if(m_enContractType != enCtOption)
		return S_OK;

	LONG nExpiry = static_cast<LONG>(m_dtExpiry);
	LONG nToday = static_cast<LONG>(vt_date::GetCurrentDate());

	if(nExpiry < nToday )
		return S_OK;

	try
	{
		IMmRvUndCollPtr spUndColl(aUndColl);

		CMmRvUndAtom* pUnd     = dynamic_cast<CMmRvUndAtom*>(aUnd);
		CMmRvAggData* pUndData = static_cast<CMmRvAggData*>(pUnd);
		if(pUnd && pUndData)
		{
			IEtsPriceProfileAtomPtr spUndPriceProfile;
			IEtsPriceProfileAtomPtr spOptPriceProfile;

			CSafeArrayWrapper<double> saDates;
			CSafeArrayWrapper<double> saAmounts;

			spUndPriceProfile = pUnd->m_spUndPriceProfile;
			spOptPriceProfile = pUnd->m_spOptPriceProfile;


			DOUBLE dUndPrice = dUndMidPrice;

			DOUBLE sUndPriceSave = dUndMidPrice;
			ISynthRootAtomPtr spSynthRoot;

			if(m_bIsSynthetic)
			{
				ISynthRootCollPtr spSynthRootColl = pUnd->m_spSynthRoots;
				if(spSynthRootColl != NULL)
				{
					spSynthRoot = spSynthRootColl->Item[m_nOptionRootID];
					if(spSynthRoot != NULL)
					{
						DOUBLE dSynthBid = 0., dSynthAsk = 0., dSynthLast = 0.;
						_CHK(pUnd->GetSyntheticUnderlyingPrice(spUndColl, spSynthRoot, &dSynthBid, &dSynthAsk, &dSynthLast));
						dUndMidPrice = spUndPriceProfile->GetUndPriceMid(dSynthBid, dSynthAsk, dSynthLast, dUndPriceTolerance, enPriceRoundingRule, NULL, VARIANT_FALSE);
						m_pQuote->m_pSuPrice->put_Last(dUndMidPrice);
						m_pQuote->m_pSuPrice->put_Bid(dSynthBid);
						m_pQuote->m_pSuPrice->put_Ask(dSynthAsk);
					}
				}
			}

			EtsReplacePriceStatusEnum enPriceStatusMid = enRpsNone;
			DOUBLE dOptPriceMid = 0.;

			dOptPriceMid = spOptPriceProfile->GetOptPriceMid(m_pQuote->m_pPrice->m_dPriceBid,
				m_pQuote->m_pPrice->m_dPriceAsk, m_pQuote->m_pPrice->m_dPriceLast, enPriceRoundingRule, 
				bUseTheoVolatility, 0., &enPriceStatusMid);

			if (m_pQuote->m_pPrice->m_bManualActive == VARIANT_TRUE)
				dOptPriceMid = m_pQuote->m_pPrice->m_dActivePrice;
			else
				m_pQuote->m_pPrice->m_dActivePrice = dOptPriceMid;

			m_pQuote->m_enReplacePriceStatus = enPriceStatusMid;
			if(m_pQuote->IsDirty() || pUnd->m_pPrice->m_bDirty!=VARIANT_FALSE || pUnd->m_pSuPrice->m_bDirty!=VARIANT_FALSE)
			{
				if( (nMask != GT_NOTHING  && dUndMidPrice > DBL_EPSILON))
				{
					GREEKS aGreeks;
					ZeroMemory(&aGreeks, sizeof(aGreeks));

					aGreeks.nMask = nMask;
					__MmRvPosAtom::ClearValues();

					LONG nModel = static_cast<LONG>(enCalcModel);
					LONG nIsAmerican = (pUnd->m_bIsAmerican ? 1L : 0L);

					DOUBLE dYield = 0., dVolaCalculated = 0.;

					LONG nDivCount = 0L, nRetCount = 0L;
					EtsContractTypeEnum enUndType = pUnd->m_enContractType;

					DOUBLE dSkew = 0., dKurt = 0.;
					vt_date dt_vt_CalcDate ( dtCalcDate ) ;
					dt_vt_CalcDate.ClearTime() ;

					EgLib::vt_date_span dtSp = ( dtCalcDate - vt_date::GetCurrentDate( true )) ;

					LONG nTimeShift = dtSp.get_days() ;

					LONG nToday = nTimeShift + static_cast<LONG>(vt_date::GetCurrentDate());
					// prepare parameters
					if(!m_bIsSynthetic)
					{
						dSkew = pUnd->m_dSkew;
						dKurt = pUnd->m_dKurt;
						dYield = 0;

						EtsDivTypeEnum enDivType = enDivCustomStream;
						IEtsIndexDivAtomPtr spDiv = pUnd->m_spDividend;
						if(spDiv)
							spDiv->get_DivType(&enDivType);

						switch(enDivType)
						{
						case enDivMarket:
						case enDivCustomPeriodical:
						case enDivCustomStream:
							{
									nDivCount = 0;

									if (spDiv != NULL)
									{
										spDiv->GetDividendCount(nToday, nExpiry, &nDivCount);
										if(nDivCount > 0L) 
										{
											LPSAFEARRAY psaAmounts = NULL;
											LPSAFEARRAY psaDates = NULL;

											spDiv->GetDividends(nToday, nExpiry, nDivCount, &psaAmounts, &psaDates, &nRetCount);

											saAmounts.Attach(psaAmounts);
											saDates.Attach(psaDates);
										}
									}

							}
							break;
						case enDivStockBasket:
							{
								VARIANT_BOOL bIsBasket = VARIANT_FALSE;

								IIndexAtomPtr spBasketIndex = pUnd->m_spBasketIndex;

								if(spBasketIndex != NULL)
								{
									_CHK((spBasketIndex->get_IsBasket(&bIsBasket)));
									if(bIsBasket)
									{
										IEtsIndexDivCollPtr spBasketDivs;
										spBasketIndex->get_BasketDivs(&spBasketDivs);
										nDivCount = 0;
										LPSAFEARRAY psaAmounts = NULL;
										LPSAFEARRAY psaDates = NULL;

										spBasketDivs->GetDividends(nToday, nExpiry, nDivCount, &psaAmounts, &psaDates, &nDivCount);

										saAmounts.Attach(psaAmounts);
										saDates.Attach(psaDates);
									}
								}
							}
							break;
						case enDivIndexYield:
							{
								dYield = pUnd->m_dYield;
							}
							break;	
						}

						//if(enUndType == enCtStock)
						//{
						//	nDivCount = 0;
						//	IEtsIndexDivAtomPtr spDiv = pUnd->m_spDividend;

						//	if (spDiv != NULL)
						//	{
						//		spDiv->GetDividendCount(nToday, nExpiry, &nDivCount);
						//		if(nDivCount > 0L) 
						//		{
						//			LPSAFEARRAY psaAmounts = NULL;
						//			LPSAFEARRAY psaDates = NULL;

						//			spDiv->GetDividends(nToday, nExpiry, nDivCount, &psaAmounts, &psaDates, &nRetCount);

						//			saAmounts.Attach(psaAmounts);
						//			saDates.Attach(psaDates);
						//		}
						//	}
						//}
						//else
						//{
						//	VARIANT_BOOL bIsBasket = VARIANT_FALSE;

						//	IIndexAtomPtr spBasketIndex = pUnd->m_spBasketIndex;

						//	if(spBasketIndex != NULL)
						//	{
						//		_CHK((spBasketIndex->get_IsBasket(&bIsBasket)));
						//		if(bIsBasket)
						//		{
						//			IEtsIndexDivCollPtr spBasketDivs;
						//			spBasketIndex->get_BasketDivs(&spBasketDivs);
						//			nDivCount = 0;
						//			LPSAFEARRAY psaAmounts = NULL;
						//			LPSAFEARRAY psaDates = NULL;

						//			spBasketDivs->GetDividends(nToday, nExpiry, nDivCount, &psaAmounts, &psaDates, &nDivCount);

						//			saAmounts.Attach(psaAmounts);
						//			saDates.Attach(psaDates);
						//		}
						//	}
						//	if(bIsBasket)
						//		dYield = 0.0;
						//	else 
						//		dYield = pUnd->m_dYield;
						//}
					}
					else if(spSynthRoot != NULL) // synthetic
					{
						VARIANT_BOOL bIsBasket = spSynthRoot->Basket;

						dSkew  = spSynthRoot->Skew;
						dKurt  = spSynthRoot->Kurt;

						if(bIsBasket)
						{
							dYield  = 0.0;
							IEtsIndexDivCollPtr spBasketDivs;
							LONG nBaskDivCount = 0L;
							spSynthRoot->get_BasketDivs(&spBasketDivs);
							spBasketDivs->get_Count(&nBaskDivCount);

							if((spBasketDivs != NULL)&&(nBaskDivCount > 0L))
							{
								nDivCount = 0;

								LPSAFEARRAY psaAmounts = NULL;
								LPSAFEARRAY psaDates = NULL;

								spBasketDivs->GetDividends(nToday, nExpiry, nDivCount, &psaAmounts, &psaDates, &nDivCount);

								saAmounts.Attach(psaAmounts);
								saDates.Attach(psaDates);
							}
						}
						else
							dYield = spSynthRoot->Yield;
					}

					// calc vola
					if(bUseTheoVolatility == VARIANT_TRUE )
						dVolaCalculated = m_pQuote->m_dVola;
					else
					{
						dVolaCalculated = 0.;
						if(!bUseTheoVolaNoBid || bUseTheoVolaNoBid && m_pQuote->m_pPrice->m_dPriceBid > DBL_EPSILON) 
						{
							bool bCalcInAnyCase =  false ;
							if (( m_pQuote->m_pPrice->m_dPriceBid > 0 || m_pQuote->m_pPrice->m_dPriceAsk > 0 || m_pQuote->m_pPrice->m_dPriceLast > 0 ) )
								bCalcInAnyCase = true ;

							if(dOptPriceMid > DBL_EPSILON || bCalcInAnyCase )
							{
								LONG nFlag = VF_OK;
								dVolaCalculated = ::CalcVolatilityMM3(m_dRate, dYield, dUndMidPrice, dOptPriceMid, m_dStrike, 
									nExpiry - nToday, m_enOptType, nIsAmerican, nDivCount,
									saAmounts.GetPlainData(), saDates.GetPlainData(), 100L, dSkew, dKurt, nModel, &nFlag);

								if(bUseTheoVolaBadMarket && nFlag != VF_OK)
									dVolaCalculated = m_pQuote->m_dVola;
							}
							else if (bUseTheoVolaBadMarket)
								dVolaCalculated = m_pQuote->m_dVola;
						}
						else
							dVolaCalculated = m_pQuote->m_dVola;
					}

					m_pQuote->m_dImpliedVola = dVolaCalculated ;

					char strlog[1024] ;

					if ( m_pQuote->m_dImpliedVola <=0 )
					{
						if ( m_pQuote->m_pPrice->m_dPriceBid > 0 || m_pQuote->m_pPrice->m_dPriceAsk > 0 || m_pQuote->m_pPrice->m_dPriceLast > 0 )
							m_bsLogEnhansement = m_pQuote->m_bsVolaCalculatedParametrs;
						else
							m_bsLogEnhansement = _bstr_t(L"Wrong option Price. It's ")+ _bstr_t(dOptPriceMid);
					}

					memset ( strlog , 0 , sizeof(strlog) ) ;
					sprintf_s ( strlog , sizeof(strlog) ,  "Rate %f , Yield %f , Price %f , dOptPriceMid %f , dStrike %f , days %i , OptType %i , IsAmerican %i, DivCount %i, Steps  %i , Skew %f , Kurt %f , Model %i " ,
															m_dRate, dYield, dUndMidPrice, dOptPriceMid, m_dStrike, 
															nExpiry - nToday, m_enOptType, nIsAmerican, nDivCount, 100L, dSkew, dKurt, nModel) ;

					m_pQuote->m_bsVolaCalculatedParametrs  = _bstr_t( strlog ) ;

					m_pQuote->m_dVolaCalcPrice = dUndMidPrice ;


					if(nMask != GT_NOTHING)
					{
						// calc greeks
						nRetCount = ::CalcGreeksMM2(m_dRate, dYield, dUndMidPrice, m_dStrike, dVolaCalculated, nExpiry - nToday,
							m_enOptType, nIsAmerican, nDivCount, saAmounts.GetPlainData(), saDates.GetPlainData(), 100L, dSkew, dKurt, nModel, &aGreeks);

						if(nRetCount != 0L)
						{
							if ((aGreeks.dTheoPrice > BAD_DOUBLE_VALUE)&&(aGreeks.dTheoPrice < 0))
								aGreeks.dTheoPrice = 0;

							if((aGreeks.nMask & GT_THEOPRICE) && _finite(aGreeks.dTheoPrice) && aGreeks.dTheoPrice >= 0.)

								m_pQuote->m_dPriceTheo = aGreeks.dTheoPrice;
							if((aGreeks.nMask & GT_DELTA) && _finite(aGreeks.dDelta))
								m_pQuote->m_dDelta = aGreeks.dDelta;
							if((aGreeks.nMask & GT_GAMMA) && _finite(aGreeks.dGamma))
								m_pQuote->m_dGamma = aGreeks.dGamma;
							if((aGreeks.nMask & GT_THETA) && _finite(aGreeks.dTheta))
								m_pQuote->m_dTheta = aGreeks.dTheta;
							if((aGreeks.nMask & GT_VEGA) && _finite(aGreeks.dVega))
								m_pQuote->m_dVega = aGreeks.dVega;
							if((aGreeks.nMask & GT_RHO) && _finite(aGreeks.dRho))
								m_pQuote->m_dRho = aGreeks.dRho;
							if((aGreeks.nMask & GT_DELTA_VEGA) && _finite(aGreeks.dDeltaVega))
								m_pQuote->m_dVegaDelta = aGreeks.dDeltaVega;
							if((aGreeks.nMask & GT_GAMMA_VEGA) && _finite(aGreeks.dGammaVega))
								m_pQuote->m_dVegaGamma = aGreeks.dGammaVega;
							if((aGreeks.nMask & GT_DELTA_THETA) && _finite(aGreeks.dDeltaTheta))
								m_pQuote->m_dThetaDelta = aGreeks.dDeltaTheta;
							if((aGreeks.nMask & GT_GAMMA_THETA) && _finite(aGreeks.dGammaTheta))
								m_pQuote->m_dThetaGamma = aGreeks.dGammaTheta;
						}
					}
				}

				m_pQuote->ClearDirty();
			}

				LONG nUndID = pUnd->m_nID;

				_CalcOptPositionData(spOptPriceProfile,
					spSynthRoot,
					bIsPnlLTD,
					bUseTheoVolatility,
					bUseTheoVolaNoBid,
					bUseTheoVolaBadMarket,
					dUndPriceTolerance,
					enPriceRoundingRule,
					spUndColl,
					sUndPriceSave, 
					nUndID,
					dtCalcDate);

		}
		else
		{
			return E_POINTER;
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvPosAtom, e.Error());
	}

	return S_OK;
}

void CMmRvPosAtom::_CalcOptPositionData(
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
													 LONG   nUndID,
													 DATE dtCalcDate
													 )
{
	// clear values in shares
	__MmRvPosAtom::ClearValuesInShares();
	if(m_bIsSynthetic && m_spSynthGreeks != NULL)
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

	// calc values in shares
	EtsReplacePriceStatusEnum enPriceStatusMid = enRpsNone;
	EtsReplacePriceStatusEnum enPriceStatusBid = enRpsNone;
	EtsReplacePriceStatusEnum enPriceStatusAsk = enRpsNone;

	DOUBLE dOptPriceBid = spOptPriceProfile->GetOptPriceBidForPnL(m_pQuote->m_pPrice->m_dPriceBid, m_pQuote->m_pPrice->m_dPriceAsk, m_pQuote->m_pPrice->m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_pQuote->m_dPriceTheo, &enPriceStatusBid);
	DOUBLE dOptPriceAsk = spOptPriceProfile->GetOptPriceAskForPnL(m_pQuote->m_pPrice->m_dPriceBid, m_pQuote->m_pPrice->m_dPriceAsk, m_pQuote->m_pPrice->m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_pQuote->m_dPriceTheo, &enPriceStatusAsk);

	enPriceStatusMid = enRpsNone;
	DOUBLE dOptPriceMid = spOptPriceProfile->GetOptPriceMid(m_pQuote->m_pPrice->m_dPriceBid, m_pQuote->m_pPrice->m_dPriceAsk, m_pQuote->m_pPrice->m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_pQuote->m_dPriceTheo, &enPriceStatusMid);

	m_pQuote->m_enReplacePriceStatus = static_cast<EtsReplacePriceStatusEnum>(enPriceStatusMid | enPriceStatusBid | enPriceStatusAsk);

	if (m_pQuote->m_pPrice->m_bManualActive == VARIANT_TRUE)	
		dOptPriceAsk = dOptPriceBid = dOptPriceMid = m_pQuote->m_pPrice->m_dActivePrice;
	else
	   m_pQuote->m_pPrice->m_dActivePrice = dOptPriceMid;

	// pnl
	_CalcPnlMtm(bIsPnlLTD, dOptPriceBid, dOptPriceAsk, spOptPriceProfile->GetBadOptSinglePriceRule() == enObsprReplaceWithZero , dtCalcDate);
	_CalcPnlTheo(bIsPnlLTD, dtCalcDate);

	//AUM
	DOUBLE	dAUM		=	BAD_DOUBLE_VALUE;
	IMmRvUndAtomPtr spMainUnd;
	_CHK(spUndColl->get_Item(nUndID, &spMainUnd));
	CMmRvUndAtom *pMainUnd = static_cast<CMmRvUndAtom*>(spMainUnd.GetInterfacePtr());
	if (pMainUnd)
	{
		dAUM	=	pMainUnd->GetNetExposureAUM();
	}

	DOUBLE dMainComponentWeight = 1.0;

	// delta & gamma
	if(m_pQuote->m_dDelta > BAD_DOUBLE_VALUE || m_pQuote->m_dGamma > BAD_DOUBLE_VALUE)
	{
		if(!m_bIsSynthetic || m_spSynthGreeks == NULL || spSynthRoot == NULL)
		{
			if(m_pQuote->m_dDelta > BAD_DOUBLE_VALUE)
			{
				m_dDeltaInShares = m_pQuote->m_dDelta * m_nQtyInShares;
			}

			if(m_pQuote->m_dGamma > BAD_DOUBLE_VALUE)
			{
				m_dGammaInShares = m_pQuote->m_dGamma * m_nQtyInShares;

				if(dUndMidPrice > DBL_EPSILON)
					m_dGammaInSharesPerc = m_pQuote->m_dGamma * m_nQtyInShares * dUndMidPrice / 100.;

				m_dNetGamma = m_pQuote->m_dGamma * m_nQtyInShares  / 100.;

				if(dUndMidPrice > DBL_EPSILON)
					m_dNetGamma = m_pQuote->m_dGamma * m_nQtyInShares  * dUndMidPrice * dUndMidPrice / 100.;

			}


		}
		else // synthetic
		{
			LONG nSynthUndID = 0L;
			ISynthRootCompAtomPtr spSRComp;
			ISynthRootCompCollPtr spSRCompColl;
			
			//only for display ActivPrice for main SU component as price of SU
			/*if (m_pQuote->m_pPrice->m_bManualActive == VARIANT_FALSE)
				m_pQuote->m_pPrice->m_dActivePrice = m_pQuote->m_pSuPrice->m_dPriceLast;*/

			spSRCompColl = spSynthRoot->SynthRootComponents;
			if(spSRCompColl != NULL)
			{
				spSRComp = spSRCompColl->Item[nUndID];
				if(spSRComp != NULL)
				{
					if(m_pQuote->m_dDelta > BAD_DOUBLE_VALUE)
						m_dDeltaInShares = m_pQuote->m_dDelta * m_nQtyInShares * spSRComp->Weight;

					if(m_pQuote->m_dGamma > BAD_DOUBLE_VALUE)
						m_dGammaInShares = m_pQuote->m_dGamma * m_nQtyInShares * spSRComp->Weight;

					dMainComponentWeight = spSRComp->Weight;
				}

				if(dUndMidPrice > DBL_EPSILON && m_dGammaInShares > BAD_DOUBLE_VALUE)
					m_dGammaInSharesPerc = m_dGammaInShares * dUndMidPrice / 100.;

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
					{
						DOUBLE dGammaInShares = BAD_DOUBLE_VALUE;
						DOUBLE dDeltaInShares = BAD_DOUBLE_VALUE;
						DOUBLE dUndPrice = BAD_DOUBLE_VALUE;

						_CHK(spSynthGreeks->get_SynthUndID(&nSynthUndID));
						spSRComp = spSRCompColl->Item[nSynthUndID];

						IMmRvUndAtomPtr spUnd2;
						_CHK(spUndColl->get_Item(nSynthUndID, &spUnd2));
						IMmRvAggregationDataAtomPtr spUndData2(spUnd2);
						if(spUnd2 != NULL)
						{
							enPriceStatusMid = enRpsNone;

							/*this commented part of code is equal to next 2 lines in this scope*/
							/*IEtsPriceProfileAtomPtr spUndPriceProfile2;
							_CHK(spUnd2->get_UndPriceProfile(&spUndPriceProfile2));

							DOUBLE dUndPriceBid = 0., dUndPriceAsk = 0., dUndPriceLast = 0.;
							IMmRvPricePtr spPrice2;

							_CHK(spUndData2->get_Price(&spPrice2));
							_CHK(spPrice2->get_Bid(&dUndPriceBid));
							_CHK(spPrice2->get_Ask(&dUndPriceAsk));
							_CHK(spPrice2->get_Last(&dUndPriceLast));

							dUndPrice = spUndPriceProfile2->GetUndPriceMid(dUndPriceBid, dUndPriceAsk,
								dUndPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enPriceStatusMid, VARIANT_FALSE);
							_CHK(spUnd2->put_ReplacePriceStatus(enPriceStatusMid));*/

							VARIANT_BOOL bFutureUsed = VARIANT_FALSE;
							spUnd2->GetUnderlyingPrice(	dUndPriceTolerance,
														enPriceRoundingRule,
														&enPriceStatusMid,
														&bFutureUsed,
														&dUndPrice);
						}


						if(spSRComp != NULL)
						{
							DOUBLE dWeight = spSRComp->Weight;
							if(m_pQuote->m_dDelta > BAD_DOUBLE_VALUE)
							{
								dDeltaInShares = m_pQuote->m_dDelta * m_nQtyInShares * dWeight;
								_CHK(spSynthGreeks->put_DeltaInShares(dDeltaInShares));
								_CHK(spSynthGreeks->put_NetDelta(dDeltaInShares));

								if ( (dAUM != BAD_DOUBLE_VALUE || dAUM != 0.0) && dUndPrice != BAD_DOUBLE_VALUE)
									_CHK(spSynthGreeks->put_NetExposure(dDeltaInShares * dUndPrice / dAUM * 100.0));
								else
									_CHK(spSynthGreeks->put_NetExposure(BAD_DOUBLE_VALUE));
							}

							if(m_pQuote->m_dRho > BAD_DOUBLE_VALUE)
								_CHK(spSynthGreeks->put_RhoInShares(m_pQuote->m_dRho * m_nQtyInShares * dWeight));
							else
								_CHK(spSynthGreeks->put_BadRhoInShares(VARIANT_TRUE));

							if(m_pQuote->m_dGamma > BAD_DOUBLE_VALUE)
							{
								dGammaInShares = m_pQuote->m_dGamma * m_nQtyInShares * dWeight;
								_CHK(spSynthGreeks->put_GammaInShares(dGammaInShares));
							}
						}
						else if(nSynthUndID == 0L) // USD_ID
						{
							DOUBLE dCashValue = spSynthRoot->CashValue;
							if(m_pQuote->m_dDelta > BAD_DOUBLE_VALUE)
							{
								_CHK(spSynthGreeks->put_DeltaInShares(m_pQuote->m_dDelta * m_nQtyInShares * dCashValue));
								_CHK(spSynthGreeks->put_NetDelta(m_pQuote->m_dDelta * m_nQtyInShares * dCashValue));

								if ( dAUM != BAD_DOUBLE_VALUE || dAUM != 0.0)
									_CHK(spSynthGreeks->put_NetExposure(m_pQuote->m_dDelta * m_nQtyInShares * dCashValue / dAUM * 100.0));
								else
									_CHK(spSynthGreeks->put_NetExposure(BAD_DOUBLE_VALUE));
							}

							if(m_pQuote->m_dGamma > BAD_DOUBLE_VALUE)
							{
								dGammaInShares = m_pQuote->m_dGamma * m_nQtyInShares * dCashValue;
								_CHK(spSynthGreeks->put_GammaInShares(dGammaInShares));
							}
							_CHK(spSynthGreeks->put_DeltaInMoney(m_pQuote->m_dDelta * m_nQtyInShares * dCashValue));
						}


						if(dUndPrice >= 0.0)
						{
							if( dGammaInShares > BAD_DOUBLE_VALUE && m_pQuote->m_dGamma > BAD_DOUBLE_VALUE)
							{
								_CHK(spSynthGreeks->put_GammaInSharesPerc(dGammaInShares * dUndPrice / 100.));
								_CHK(spSynthGreeks->put_NetGamma(dGammaInShares * dUndPrice * dUndPrice / 100));
							}
							else
								spSynthGreeks->put_BadNetGamma(VARIANT_TRUE);

							if(dDeltaInShares > BAD_DOUBLE_VALUE)
							{
								_CHK(spSynthGreeks->put_NetDelta(dDeltaInShares /** dUndMidPrice*/));

								if ( dAUM != BAD_DOUBLE_VALUE || dAUM != 0.0)
									_CHK(spSynthGreeks->put_NetExposure(dDeltaInShares * dUndPrice / dAUM * 100.0));
								else
									_CHK(spSynthGreeks->put_NetExposure(BAD_DOUBLE_VALUE));

								if(nSynthUndID != 0L)
									_CHK(spSynthGreeks->put_DeltaInMoney(dDeltaInShares * dUndPrice));
							}
							else 
								if(nSynthUndID != 0L)
								{
									spSynthGreeks->put_BadDeltaInMoney(VARIANT_TRUE);
									spSynthGreeks->put_BadNetDelta(VARIANT_TRUE);
									spSynthGreeks->put_BadNetExposure(VARIANT_TRUE);
								}

						}
					}
				}
			}

		}
	}

	// other theos
	if(m_pQuote->m_dVega > BAD_DOUBLE_VALUE)
	{
		m_dVegaInShares = m_pQuote->m_dVega * m_nQtyInShares;
		m_dWtdVega = m_dVegaInShares * m_dVegaWeight;
	}

	if(m_pQuote->m_dTheta > BAD_DOUBLE_VALUE)
		m_dThetaInShares = m_pQuote->m_dTheta * m_nQtyInShares;

	if(m_pQuote->m_dRho > BAD_DOUBLE_VALUE)
		m_dRhoInShares = m_pQuote->m_dRho * m_nQtyInShares;

	if(m_pQuote->m_dVegaDelta > BAD_DOUBLE_VALUE)
		m_dVegaDeltaInShares = m_pQuote->m_dVegaDelta * m_nQtyInShares;

	if(m_pQuote->m_dThetaDelta > BAD_DOUBLE_VALUE)
		m_dThetaDeltaInShares = m_pQuote->m_dThetaDelta * m_nQtyInShares;

	DOUBLE dOptPricePnL = 0.;
	VARIANT_BOOL bUseMidMarketForPnL = spOptPriceProfile->UseMidMarketForPnL;
	VARIANT_BOOL bUseZeroBidRule = spOptPriceProfile->UseZeroBidRule;
	if (bUseMidMarketForPnL == VARIANT_TRUE && bUseZeroBidRule == VARIANT_FALSE)
		dOptPricePnL = dOptPriceMid;
	else
	{
		if(m_nQty > 0.)
			dOptPricePnL = spOptPriceProfile->GetOptPriceBidForPnL(m_pQuote->m_pPrice->m_dPriceBid, m_pQuote->m_pPrice->m_dPriceAsk, m_pQuote->m_pPrice->m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_pQuote->m_dPriceTheo, NULL);
		else
			dOptPricePnL = spOptPriceProfile->GetOptPriceAskForPnL(m_pQuote->m_pPrice->m_dPriceBid, m_pQuote->m_pPrice->m_dPriceAsk, m_pQuote->m_pPrice->m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_pQuote->m_dPriceTheo, NULL);
	}
	
	DOUBLE dUndMidPrice4Calc = (((m_bIsSynthetic || m_spSynthGreeks ) && m_pQuote->m_pSuPrice->m_dPriceLast > DBL_EPSILON) ?
								m_pQuote->m_pSuPrice->m_dPriceLast : dUndMidPrice);

	if(dUndMidPrice4Calc > DBL_EPSILON && dOptPricePnL >= 0/*DBL_EPSILON*/)
	{
		//			formula for time value:
		//			for calls strike >=spot: time value= call price
		//			for calls strike <spot, time value= max(0, call price -(spot-strike))
		//			for puts strike >spot: time value= max(0, put price -(strike-spot))
		//			for puts strike <=spot, time value= put price
		if(m_enOptType == enOtCall)
		{
			if(m_dStrike >= dUndMidPrice4Calc)
				m_dTimeValue = dOptPricePnL;
			else
				m_dTimeValue = max(0., dOptPricePnL - (dUndMidPrice4Calc-m_dStrike));
		}
		else
		{
			if(m_dStrike <= dUndMidPrice4Calc)
				m_dTimeValue = dOptPricePnL;
			else
				m_dTimeValue = max(0., dOptPricePnL- (m_dStrike-dUndMidPrice4Calc));
		}
	}

	if(m_pQuote->m_dVegaGamma > BAD_DOUBLE_VALUE && dUndMidPrice > DBL_EPSILON)
		m_dVegaGammaInShares = m_pQuote->m_dVegaGamma * m_nQtyInShares * dUndMidPrice4Calc / 100.;

	if(m_pQuote->m_dThetaGamma > BAD_DOUBLE_VALUE && dUndMidPrice > DBL_EPSILON)
		m_dThetaGammaInShares = m_pQuote->m_dThetaGamma * m_nQtyInShares * dUndMidPrice4Calc / 100.;


	if(m_dNetGamma == BAD_DOUBLE_VALUE && m_pQuote->m_dGamma > BAD_DOUBLE_VALUE )
	{
			m_dNetGamma = m_pQuote->m_dGamma * m_nQtyInShares  / 100.;
			if(dUndMidPrice > DBL_EPSILON)
				m_dNetGamma = m_pQuote->m_dGamma * m_nQtyInShares * dMainComponentWeight* dUndMidPrice * dUndMidPrice / 100.;
	}
	
}


/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmRvPosAtom::CalcFutOptionGreeks(IMmRvUndAtom* aUnd,
															  DOUBLE dUndMidPrice,
															  LONG nMask,
															  VARIANT_BOOL bIsPnlLTD,
															  EtsCalcModelTypeEnum enCalcModel,
															  VARIANT_BOOL bUseTheoVolatility,
															  VARIANT_BOOL bUseTheoVolaNoBid,
															  VARIANT_BOOL bUseTheoVolaBadMarket,
															  DOUBLE dUndPriceTolerance,
															  EtsPriceRoundingRuleEnum enPriceRoundingRule,
															  DATE _dtCalcDate)
{
	if(aUnd == NULL)
		return Error(L"Invalid object passed.", IID_IMmRvPosAtom, E_INVALIDARG);

	if(m_enContractType != enCtFutOption)
		return S_OK;

	try
	{
		IMmRvUndAtomPtr spUnd(aUnd);
		IMmRvAggregationDataAtomPtr spUndData(aUnd);
		IEtsPriceProfileAtomPtr spUndPriceProfile;
		IEtsPriceProfileAtomPtr spOptPriceProfile;

		_CHK(m_spFut->get_UndPriceProfile(&spUndPriceProfile));
		_CHK(m_spFut->get_OptPriceProfile(&spOptPriceProfile));

		EtsReplacePriceStatusEnum enPriceStatusMid = enRpsNone;
		DOUBLE dFutMidPrice = 0., dOptPriceMid = 0.;
		DOUBLE dFutPriceBid = 0., dFutPriceAsk = 0., dFutPriceLast = 0.;

		IMmRvPricePtr spFutPrice;
		_CHK(m_spFut->get_Price(&spFutPrice));

		_CHK(spFutPrice->get_Bid(&dFutPriceBid));
		_CHK(spFutPrice->get_Ask(&dFutPriceAsk));
		_CHK(spFutPrice->get_Last(&dFutPriceLast));

		//dFutMidPrice = spUndPriceProfile->GetUndPriceMid(dFutPriceBid, dFutPriceAsk, dFutPriceLast, dUndPriceTolerance, enPriceRoundingRule, NULL);
		VARIANT_BOOL	bNotUsed;
		_CHK(m_spFut->GetFuturePrice(dUndPriceTolerance, enPriceRoundingRule, NULL, &bNotUsed, &dFutMidPrice ));
		dOptPriceMid = spOptPriceProfile->GetOptPriceMid(m_pQuote->m_pPrice->m_dPriceBid, m_pQuote->m_pPrice->m_dPriceAsk, m_pQuote->m_pPrice->m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, 0., &enPriceStatusMid);

		m_pQuote->m_enReplacePriceStatus = enPriceStatusMid;

		if (m_pQuote->m_pPrice->m_bManualActive == VARIANT_TRUE)
			dOptPriceMid = m_pQuote->m_pPrice->m_dActivePrice;
		else
			m_pQuote->m_pPrice->m_dActivePrice = dOptPriceMid;

		CSafeArrayWrapper<double> saDates;
		CSafeArrayWrapper<double> saAmounts;

		DOUBLE dYield = 0;
		LPVOID lpDateData = NULL;
		LPVOID lpAmountData = NULL;
		IEtsIndexDivAtomPtr			spDividend = NULL;
		IIndexAtomPtr				spBasketIndex = NULL;
		EtsContractTypeEnum			m_enUndType = enCtStock;
		if (spUnd != NULL)
		{
			spUnd->get_Dividend(&spDividend);
			spUnd->get_ContractType(&m_enUndType);
			spUnd->get_BasketIndex(&spBasketIndex);
		}

		if (  (nMask != GT_NOTHING && dFutMidPrice > DBL_EPSILON ) )
		{
			GREEKS aGreeks;
			memset(&aGreeks, 0, sizeof(aGreeks));
			aGreeks.nMask = nMask;
			__MmRvPosAtom::ClearValues();

			LONG nModel = static_cast<LONG>(enCalcModel);
			VARIANT_BOOL bIsAmerican = VARIANT_FALSE;
			_CHK(m_spFut->get_IsAmerican(&bIsAmerican));
			LONG nIsAmerican = (bIsAmerican ? 1L : 0L);

			DOUBLE dVola = 0.;
			LONG nRetCount = 0L;

			LONG nExpiry = static_cast<LONG>(m_dtExpiry);

			vt_date dt_vt_CalcDate ( _dtCalcDate ) ;
			dt_vt_CalcDate.ClearTime() ;

			EgLib::vt_date_span dtSp = ( _dtCalcDate - vt_date::GetCurrentDate( true )) ;

			LONG nTimeShift = dtSp.get_days() ;

			LONG nToday = nTimeShift + static_cast<LONG>(vt_date::GetCurrentDate());

			DOUBLE dSkew = 0., dKurt = 0.;
			_CHK(spUnd->get_Skew(&dSkew));
			_CHK(spUnd->get_Kurt(&dKurt));

			////////////////////////
			LONG nDivCount = 0L;
			nRetCount = 0L;


			EtsDivTypeEnum enDivType = enDivCustomStream;
			if(spDividend)
				spDividend->get_DivType(&enDivType);

			switch(enDivType)
			{
			case enDivMarket:
			case enDivCustomPeriodical:
			case enDivCustomStream:
				{
					if (spDividend != NULL)
					{
						nDivCount = 0;
						spDividend->GetDividendCount(nToday, nExpiry, &nDivCount);
						if (nDivCount< 0)
							nDivCount = 0;

						if (nDivCount> 0)
						{

							LPSAFEARRAY psaDates	= NULL;
							LPSAFEARRAY psaAmounts  = NULL ;

							spDividend->GetDividends(nToday, nExpiry, nDivCount, &psaAmounts, &psaDates, &nRetCount);

							saDates.Attach(psaDates);
							saAmounts.Attach(psaAmounts);
						}
					}

				}
				break;
			case enDivStockBasket:
				{
					VARIANT_BOOL bIsBasket = VARIANT_FALSE;
					if(spBasketIndex != NULL)
					{
						LONG nBaskDivCount = 0L; 
						nDivCount = 0;
						_CHK(spBasketIndex->get_IsBasket(&bIsBasket));

						IEtsIndexDivCollPtr spDivColl = NULL;
						spBasketIndex->get_BasketDivs(&spDivColl);

						if ( bIsBasket && spDivColl != NULL )
						{
							dYield = 0.0;
							spDivColl->GetDividendCount(nToday, nExpiry, &nDivCount);
							if(nDivCount > 0L)
							{

								LPSAFEARRAY psaDates	= NULL;
								LPSAFEARRAY psaAmounts  = NULL ;

								spDivColl->GetDividends(nToday, nExpiry,  nDivCount, &psaAmounts, &psaDates, &nRetCount);

								saDates.Attach(psaDates);
								saAmounts.Attach(psaAmounts);
							}
						}
					}
				}
				break;
			case enDivIndexYield:
				{
					aUnd->get_Yield(&dYield);
				}
				break;	
			}



			//if(m_enUndType == enCtStock)
			//{
			//	if (spDividend != NULL)
			//	{
			//		nDivCount = 0;
			//		spDividend->GetDividendCount(nToday, nExpiry, &nDivCount);
			//		if (nDivCount< 0)
			//			nDivCount = 0;

			//		if (nDivCount> 0)
			//		{

			//			LPSAFEARRAY psaDates	= NULL;
			//			LPSAFEARRAY psaAmounts  = NULL ;

			//			spDividend->GetDividends(nToday, nExpiry, nDivCount, &psaAmounts, &psaDates, &nRetCount);

			//			saDates.Attach(psaDates);
			//			saAmounts.Attach(psaAmounts);
			//		}
			//	}
			//}
			//else
			//{
			//	VARIANT_BOOL bIsBasket = VARIANT_FALSE;
			//	if(spBasketIndex != NULL)
			//	{
			//		LONG nBaskDivCount = 0L; 
			//		nDivCount = 0;
			//		_CHK(spBasketIndex->get_IsBasket(&bIsBasket));

			//		IEtsIndexDivCollPtr spDivColl = NULL;
			//		spBasketIndex->get_BasketDivs(&spDivColl);

			//		if ( bIsBasket && spDivColl != NULL )
			//		{
			//			dYield = 0.0;
			//			spDivColl->GetDividendCount(nToday, nExpiry, &nDivCount);
			//			if(nDivCount > 0L)
			//			{

			//				LPSAFEARRAY psaDates	= NULL;
			//				LPSAFEARRAY psaAmounts  = NULL ;

			//				spDivColl->GetDividends(nToday, nExpiry,  nDivCount, &psaAmounts, &psaDates, &nRetCount);

			//				saDates.Attach(psaDates);
			//				saAmounts.Attach(psaAmounts);
			//			}
			//		}
			//	}
			//	if(bIsBasket==VARIANT_FALSE)
			//		aUnd->get_Yield(&dYield);
			//}

			if(nDivCount < 0)
				nDivCount = 0;


			/////////////////////////
			// calc vola
			if(bUseTheoVolatility)
				dVola = m_pQuote->m_dVola;
			else
			{
				dVola = 0.;
				if(!bUseTheoVolaNoBid || bUseTheoVolaNoBid && m_pQuote->m_pPrice->m_dPriceBid > DBL_EPSILON) 
				{
					if( dOptPriceMid > DBL_EPSILON)
					{

						LONG nFlag = VF_OK;
						dVola = ::CalcFutureOptionVolatility(m_dRate, dFutMidPrice, dOptPriceMid, m_dStrike, 
							nExpiry - nToday, m_enOptType, nIsAmerican, 100L, dSkew, dKurt, nModel, &nFlag);

						if(bUseTheoVolaBadMarket && nFlag != VF_OK)
							dVola = m_pQuote->m_dVola;
					}
					else if (bUseTheoVolaBadMarket)
						dVola = m_pQuote->m_dVola;
				}
				else
					dVola = m_pQuote->m_dVola;
			}

			char strlog[2048] ;
			memset ( strlog , 0 , sizeof(strlog) ) ;
			sprintf_s ( strlog , sizeof(strlog) , "Rate %f , Yield %f , Price %f , dOptPriceMid %f , dStrike %f , days %i , OptType %i , IsAmerican %i, DivCount %i, Steps  %i , Skew %f , Kurt %f , Model %i " , m_dRate, dYield, dUndMidPrice, dOptPriceMid, m_dStrike, 
				nExpiry - nToday, m_enOptType, nIsAmerican, nDivCount,
				/*saAmounts.GetPlainData(), saDates.GetPlainData(), */100L, dSkew, dKurt, nModel) ;
			m_pQuote->m_bsVolaCalculatedParametrs  =  strlog ;

			m_pQuote->m_dVolaCalcPrice = dFutMidPrice ;
			m_pQuote->m_dImpliedVola = dVola ;

			// calc greeks
			if(m_enUndType== enCtFutUnd)
				nRetCount = ::CalcFutureOptionGreeks2(m_dRate, dFutMidPrice,false, m_dStrike, dVola, nExpiry - nToday,
				m_enOptType, nIsAmerican, 100L, dSkew, dKurt, nModel, &aGreeks);
			else
			{

				nRetCount = ::CalcFutureOptionGreeks3(m_dRate, dYield, dFutMidPrice,true/*false*/, m_dStrike, dVola, nExpiry - nToday,
					m_enOptType, nIsAmerican, 100L, dSkew, dKurt, nModel, nRetCount, saAmounts.GetPlainData(), saDates.GetPlainData(), &aGreeks);
			}

			if ((aGreeks.dTheoPrice > BAD_DOUBLE_VALUE)&&(aGreeks.dTheoPrice < 0))
				aGreeks.dTheoPrice = 0;

			if (aGreeks.dTheoPrice < 0)	aGreeks.dTheoPrice = 0;
			if((aGreeks.nMask & GT_THEOPRICE) && _finite(aGreeks.dTheoPrice) && aGreeks.dTheoPrice >= 0.)
				m_pQuote->m_dPriceTheo = aGreeks.dTheoPrice;
			if((aGreeks.nMask & GT_DELTA) && _finite(aGreeks.dDelta))
				m_pQuote->m_dDelta = aGreeks.dDelta;
			if((aGreeks.nMask & GT_GAMMA) && _finite(aGreeks.dGamma))
				m_pQuote->m_dGamma = aGreeks.dGamma;
			if((aGreeks.nMask & GT_THETA) && _finite(aGreeks.dTheta))
				m_pQuote->m_dTheta = aGreeks.dTheta;
			if((aGreeks.nMask & GT_VEGA) && _finite(aGreeks.dVega))
				m_pQuote->m_dVega = aGreeks.dVega;
			if((aGreeks.nMask & GT_RHO) && _finite(aGreeks.dRho))
				m_pQuote->m_dRho = aGreeks.dRho;
			if((aGreeks.nMask & GT_DELTA_VEGA) && _finite(aGreeks.dDeltaVega))
				m_pQuote->m_dVegaDelta = aGreeks.dDeltaVega;
			if((aGreeks.nMask & GT_GAMMA_VEGA) && _finite(aGreeks.dGammaVega))
				m_pQuote->m_dVegaGamma = aGreeks.dGammaVega;
			if((aGreeks.nMask & GT_DELTA_THETA) && _finite(aGreeks.dDeltaTheta))
				m_pQuote->m_dThetaDelta = aGreeks.dDeltaTheta;
			if((aGreeks.nMask & GT_GAMMA_THETA) && _finite(aGreeks.dGammaTheta))
				m_pQuote->m_dThetaGamma = aGreeks.dGammaTheta;
			//}
		}
		else
		{
			m_bsLogEnhansement = _bstr_t( L"Can't get futures price" ) ;
		}

		_CalcFutPositionData	(	
										spOptPriceProfile, 
										bIsPnlLTD, bUseTheoVolatility, 
										bUseTheoVolaNoBid, bUseTheoVolaBadMarket, 
										dUndPriceTolerance, enPriceRoundingRule, 
										m_enUndType == enCtFutUnd ? dFutMidPrice : dUndMidPrice,
										_dtCalcDate, m_enUndType
									);
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvPosAtom, e.Error());
	}

	return S_OK;
}

void CMmRvPosAtom::_CalcFutPositionData(
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
													 )
{
	// clear values in shares
	__MmRvPosAtom::ClearValuesInShares();

	// calc values in shares
	EtsReplacePriceStatusEnum enPriceStatusBid = enRpsNone;
	EtsReplacePriceStatusEnum enPriceStatusMid = enRpsNone;
	EtsReplacePriceStatusEnum enPriceStatusAsk = enRpsNone;

	DOUBLE dOptPriceBid = spOptPriceProfile->GetOptPriceBidForPnL(m_pQuote->m_pPrice->m_dPriceBid, m_pQuote->m_pPrice->m_dPriceAsk, m_pQuote->m_pPrice->m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_pQuote->m_dPriceTheo, &enPriceStatusBid);
	DOUBLE dOptPriceAsk = spOptPriceProfile->GetOptPriceAskForPnL(m_pQuote->m_pPrice->m_dPriceBid, m_pQuote->m_pPrice->m_dPriceAsk, m_pQuote->m_pPrice->m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_pQuote->m_dPriceTheo, &enPriceStatusAsk);
	DOUBLE dOptPriceMid = spOptPriceProfile->GetOptPriceMid(m_pQuote->m_pPrice->m_dPriceBid, m_pQuote->m_pPrice->m_dPriceAsk, m_pQuote->m_pPrice->m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_pQuote->m_dPriceTheo, &enPriceStatusMid);

	m_pQuote->m_enReplacePriceStatus = static_cast<EtsReplacePriceStatusEnum>(enPriceStatusMid | enPriceStatusBid | enPriceStatusAsk);

	if (m_pQuote->m_pPrice->m_bManualActive == VARIANT_TRUE)	
		dOptPriceAsk = dOptPriceBid = dOptPriceMid = m_pQuote->m_pPrice->m_dActivePrice;
	else
		m_pQuote->m_pPrice->m_dActivePrice = dOptPriceMid;

	if ( m_enContractType == enCtFutOption && enUndType == enCtFutUnd && m_spFut ) {
		CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
		if ( pFut )
		{
			m_dKEq = pFut->m_dKEq;
			m_bMultOptDltEq = pFut->m_bMultOptDltEq;
		}
	}

	// pnl
	_CalcPnlMtm ( bIsPnlLTD, dOptPriceBid, dOptPriceAsk, spOptPriceProfile->GetBadOptSinglePriceRule() == enObsprReplaceWithZero , dtCalcDate ) ;
	_CalcPnlTheo ( bIsPnlLTD,dtCalcDate ) ;

	if ( m_enContractType == enCtFutOption && enUndType == enCtFutUnd && m_spFut ) {
		CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
		if ( pFut ){
			if(m_dPnlMtm <= BAD_DOUBLE_VALUE)
				m_dPnlMtm = 0.;
			else
				m_dPnlMtm *= pFut->m_dKEq / pFut->m_nFutLotSize;
			
			if(m_dPnlTheo <= BAD_DOUBLE_VALUE)
				m_dPnlTheo = 0.;
			else
				m_dPnlTheo *= pFut->m_dKEq / pFut->m_nFutLotSize;
		}
	}
	// delta
	if(m_pQuote->m_dDelta > BAD_DOUBLE_VALUE){
		if ( m_enContractType == enCtFutOption && enUndType == enCtFutUnd && m_spFut ) {
			CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
			if ( pFut ){
				LONG nDeltaMult = 1;
				if(!pFut->m_bMultOptDltEq)
					nDeltaMult = pFut->m_nFutLotSize;
				m_dDeltaInShares = m_pQuote->m_dDelta * m_nQty * nDeltaMult;
				m_dDeltaEq = m_pQuote->m_dDelta * m_nQty * dUndMidPrice * pFut->m_dKEq;
				pFut->m_dUndMidPrice = dUndMidPrice;
			}
		}
		else{
			m_dDeltaInShares = m_pQuote->m_dDelta * m_nQtyInShares;
			m_dDeltaEq = m_dDeltaInShares * dUndMidPrice;
		}
	}

	// gamma
	if(m_pQuote->m_dGamma > BAD_DOUBLE_VALUE)
	{
		if ( m_enContractType == enCtFutOption && enUndType == enCtFutUnd && m_spFut ) {
			CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
			if ( pFut ){
				LONG nCSzMult = 1;
				if(!pFut->m_bMultOptDltEq)
					nCSzMult = pFut->m_nFutLotSize;
				m_dGammaInShares = m_pQuote->m_dGamma * m_nQty * nCSzMult;
				if ( dUndMidPrice > DBL_EPSILON ) {
					m_dNetGamma          = m_pQuote->m_dGamma * m_nQty * dUndMidPrice * dUndMidPrice * pFut->m_dKEq / 100;
					m_dGammaInSharesPerc = m_pQuote->m_dGamma * m_nQty * dUndMidPrice * nCSzMult / 100.;
				}
			}
		}
		else{
			m_dGammaInShares = m_pQuote->m_dGamma * m_nQtyInShares;

			if(dUndMidPrice > DBL_EPSILON)
				m_dGammaInSharesPerc = m_pQuote->m_dGamma * m_nQtyInShares * dUndMidPrice / 100.;

			m_dNetGamma = m_pQuote->m_dGamma * m_nQtyInShares   / 100.;
			if(dUndMidPrice > DBL_EPSILON)
				m_dNetGamma = m_pQuote->m_dGamma * m_nQtyInShares  * dUndMidPrice * dUndMidPrice / 100.;
		}
	}

	// other theos
	if(m_pQuote->m_dVega > BAD_DOUBLE_VALUE){
		if ( m_enContractType == enCtFutOption && enUndType == enCtFutUnd && m_spFut ) {
			CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
			if ( pFut ){
				m_dVegaInShares = m_pQuote->m_dVega * m_nQty * pFut->m_dKEq;
				m_dWtdVega = m_dVegaInShares * m_dVegaWeight;
			}
		}
		else{
			m_dVegaInShares = m_pQuote->m_dVega * m_nQtyInShares;
			m_dWtdVega = m_dVegaInShares * m_dVegaWeight;
		}
	}

	if(m_pQuote->m_dTheta > BAD_DOUBLE_VALUE){
		if ( m_enContractType == enCtFutOption && enUndType == enCtFutUnd && m_spFut ) {
			CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
			if ( pFut )
				m_dThetaInShares = m_pQuote->m_dTheta * m_nQty * pFut->m_dKEq;
		}
		else
			m_dThetaInShares = m_pQuote->m_dTheta * m_nQtyInShares;
	}

	if(m_pQuote->m_dRho > BAD_DOUBLE_VALUE){
		if ( m_enContractType == enCtFutOption && enUndType == enCtFutUnd && m_spFut ) {
			CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
			if ( pFut )
				m_dRhoInShares = m_pQuote->m_dRho * m_nQty * pFut->m_dKEq;
		}
		else
			m_dRhoInShares = m_pQuote->m_dRho * m_nQtyInShares;
	}

	if(m_pQuote->m_dVegaDelta > BAD_DOUBLE_VALUE)
		if ( m_enContractType == enCtFutOption && enUndType == enCtFutUnd && m_spFut ) {
			CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
			if ( pFut )
			{
				LONG nVegaDeltaMult = 1;
				if(!pFut->m_bMultOptDltEq)
					nVegaDeltaMult = pFut->m_nFutLotSize;
				m_dVegaDeltaInShares = m_pQuote->m_dVegaDelta * m_nQty * nVegaDeltaMult;
			}
		}
		else
			m_dVegaDeltaInShares = m_pQuote->m_dVegaDelta * m_nQtyInShares;

	if(m_pQuote->m_dVegaGamma > BAD_DOUBLE_VALUE && dUndMidPrice > DBL_EPSILON)
		if ( m_enContractType == enCtFutOption && enUndType == enCtFutUnd && m_spFut ) {
			CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
			if ( pFut )
			{
				LONG nVegaGammaMult = 1;
				if(!pFut->m_bMultOptDltEq)
					nVegaGammaMult = pFut->m_nFutLotSize;
				m_dVegaGammaInShares = m_pQuote->m_dVegaGamma * m_nQty * dUndMidPrice / 100. * nVegaGammaMult;
			}
		}
		else
		m_dVegaGammaInShares = m_pQuote->m_dVegaGamma * m_nQtyInShares * dUndMidPrice / 100.;

	if(m_pQuote->m_dThetaDelta > BAD_DOUBLE_VALUE)
		if ( m_enContractType == enCtFutOption && enUndType == enCtFutUnd && m_spFut ) {
			CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
			if ( pFut )
			{
				LONG nThetaDeltaMult = 1;
				if(!pFut->m_bMultOptDltEq)
					nThetaDeltaMult = pFut->m_nFutLotSize;
				m_dThetaDeltaInShares = m_pQuote->m_dThetaDelta * m_nQty * nThetaDeltaMult;
			}
		}
		else
			m_dThetaDeltaInShares = m_pQuote->m_dThetaDelta * m_nQtyInShares;

	if(m_pQuote->m_dThetaGamma > BAD_DOUBLE_VALUE && dUndMidPrice > DBL_EPSILON)
		if ( m_enContractType == enCtFutOption && enUndType == enCtFutUnd && m_spFut ) {
			CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
			if ( pFut )
			{
				LONG nThetaGammaMult = 1;
				if(!pFut->m_bMultOptDltEq)
					nThetaGammaMult = pFut->m_nFutLotSize;
				m_dThetaGammaInShares = m_pQuote->m_dThetaGamma * m_nQty * dUndMidPrice / 100. * nThetaGammaMult;
			}
		}
		else
		m_dThetaGammaInShares = m_pQuote->m_dThetaGamma * m_nQtyInShares * dUndMidPrice / 100.;

	if(dOptPriceMid > DBL_EPSILON)
	{
		if ( m_enContractType == enCtFutOption /*&& enUndType == enCtFutUnd*/ && m_spFut )
		{
			CMmRvFutAtom* pFut = static_cast<CMmRvFutAtom*>(m_spFut.GetInterfacePtr() );
			if ( pFut )
			{
				EtsReplacePriceStatusEnum penPriceStatus;	VARIANT_BOOL dummy; double dFutPrice;
				pFut->GetFuturePrice(dUndPriceTolerance, enPriceRoundingRule, &penPriceStatus, &dummy, &dFutPrice );
				if(dFutPrice > DBL_EPSILON)
				{
					if(m_enOptType == enOtCall)
					{
						if(m_dStrike > dFutPrice)
							m_dTimeValue = dOptPriceMid;
						else
							m_dTimeValue = max(0., (dOptPriceMid - (dFutPrice - m_dStrike)));
					}
					else
					{
						if(m_dStrike <= dFutPrice)
							m_dTimeValue = dOptPriceMid;
						else
							m_dTimeValue = max(0., (dOptPriceMid - (m_dStrike - dFutPrice)));
					}
				}
			}
		}
		else
		{
			if(dUndMidPrice > DBL_EPSILON)
			{
				if(m_enOptType == enOtCall)
				{
					if(m_dStrike >= dUndMidPrice)
						m_dTimeValue = dOptPriceMid;
					else
						m_dTimeValue = max(0., dOptPriceMid - (dUndMidPrice-m_dStrike));
				}
				else
				{
					if(m_dStrike <= dUndMidPrice)
						m_dTimeValue = dOptPriceMid;
					else
						m_dTimeValue = max(0., dOptPriceMid- (m_dStrike-dUndMidPrice)) ;
				}
			}
		}

		//			m_dTimeValue = dOptPriceMid - (m_enOptType == enOtCall
		//							? (dFutMidPrice - m_dStrike > DBL_EPSILON ? dFutMidPrice - m_dStrike : 0.)
		//							: (m_dStrike - dFutMidPrice > DBL_EPSILON ? m_dStrike - dFutMidPrice : 0.));
	}
}

/////////////////////////////////////////////////////////////////////////////
//
void CMmRvPosAtom::_CalcPnlMtm(VARIANT_BOOL bIsPnlLTD, DOUBLE dPriceBid, DOUBLE dPriceAsk, bool ReplaceWithZero, DATE _dtCalculationDate)
{
	m_dPnlMtm = BAD_DOUBLE_VALUE;

	_dtCalculationDate = (DWORD)_dtCalculationDate ;
	DATE dtCurr = EgLib::vt_date::GetCurrentDate ( true ) ;

	if ( bIsPnlLTD /*|| dtCurr != _dtCalculationDate*/ )
	{
		if(m_nQtyLTDBuy > BAD_LONG_VALUE)
		{
			if((dPriceAsk > 0 || dPriceBid > 0 || ReplaceWithZero ) && m_dPosLTDBuy > BAD_DOUBLE_VALUE)
				m_dPnlMtm = dPriceBid * m_nQtyLTDBuy - m_dPosLTDBuy;
			else
				return;
		}

		if(m_nQtyLTDSell > BAD_LONG_VALUE)
		{
			if((dPriceAsk > 0 || dPriceBid > 0|| ReplaceWithZero ) && m_dPosLTDSell > BAD_DOUBLE_VALUE)
			{
				if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
				m_dPnlMtm += dPriceAsk * m_nQtyLTDSell - m_dPosLTDSell;
			}
			else
				return;
		}
	}
	else
	{
		if(m_nQtyDailyPrevDateBuy > BAD_LONG_VALUE)
		{
			if((dPriceAsk > 0 || dPriceBid > 0 || ReplaceWithZero ) && m_dPosDailyPrevDateBuy > BAD_DOUBLE_VALUE)
				m_dPnlMtm = dPriceBid * m_nQtyDailyPrevDateBuy - m_dPosDailyPrevDateBuy;
			else
				return;
		}

		if(m_nQtyDailyPrevDateSell > BAD_LONG_VALUE)
		{
			if((dPriceAsk > 0 /*BAD_DOUBLE_VALUE*/ || dPriceBid > 0 || ReplaceWithZero ) && m_dPosDailyPrevDateSell > BAD_DOUBLE_VALUE)
			{
				if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
				m_dPnlMtm += dPriceAsk * m_nQtyDailyPrevDateSell - m_dPosDailyPrevDateSell;
			}
			else
				return;
		}

		if(m_nQtyDailyTodayBuy > BAD_LONG_VALUE)
		{
			if( (dPriceBid > 0/*BAD_DOUBLE_VALUE*/ || dPriceAsk > 0 /*BAD_DOUBLE_VALUE*/ || ReplaceWithZero ) && m_dPosDailyTodayBuy > BAD_DOUBLE_VALUE)
			{
				if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
				m_dPnlMtm += dPriceBid * m_nQtyDailyTodayBuy - m_dPosDailyTodayBuy;
			}
			else
				return;
		}

		if(m_nQtyDailyTodaySell > BAD_LONG_VALUE)
		{
			if((dPriceBid > 0 /*BAD_DOUBLE_VALUE*/ || dPriceAsk > 0 /*BAD_DOUBLE_VALUE*/ || ReplaceWithZero ) && m_dPosDailyTodaySell > BAD_DOUBLE_VALUE)
			{
				if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
				m_dPnlMtm += dPriceAsk * m_nQtyDailyTodaySell - m_dPosDailyTodaySell;
			}
			else
				return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//
void CMmRvPosAtom::_CalcPnlTheo(VARIANT_BOOL bIsPnlLTD,DATE _dtCalculationDate)
{

	DATE dtCurr = EgLib::vt_date::GetCurrentDate ( true ) ;
	_dtCalculationDate  = (DWORD)_dtCalculationDate ;
	m_dPnlTheo = BAD_DOUBLE_VALUE;

	if(m_pQuote->m_dPriceTheo >= 0./*DBL_EPSILON*/)
	{
		if(bIsPnlLTD /*|| dtCurr != _dtCalculationDate*/ )
		{
			if(m_nQtyLTDBuy > BAD_LONG_VALUE)
			{
				if(m_dPosLTDBuy > BAD_DOUBLE_VALUE)
					m_dPnlTheo = m_pQuote->m_dPriceTheo * m_nQtyLTDBuy - m_dPosLTDBuy;
				else
					return;
			}

			if(m_nQtyLTDSell > BAD_LONG_VALUE)
			{
				if(m_dPosLTDSell > BAD_DOUBLE_VALUE)
				{
					if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
					m_dPnlTheo += m_pQuote->m_dPriceTheo * m_nQtyLTDSell - m_dPosLTDSell;
				}
				else
					return;
			}
		}
		else
		{
			if(m_nQtyDailyPrevDateBuy > BAD_LONG_VALUE)
			{
				if(m_dPosDailyPrevDateBuy > BAD_DOUBLE_VALUE)
					m_dPnlTheo = m_pQuote->m_dPriceTheo * m_nQtyDailyPrevDateBuy - m_dPosDailyPrevDateBuy;
				else
					return;
			}

			if(m_nQtyDailyPrevDateSell > BAD_LONG_VALUE)
			{
				if(m_dPosDailyPrevDateSell > BAD_DOUBLE_VALUE)
				{
					if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
					m_dPnlTheo += m_pQuote->m_dPriceTheo * m_nQtyDailyPrevDateSell - m_dPosDailyPrevDateSell;
				}
				else
					return;
			}

			if(m_nQtyDailyTodayBuy > BAD_LONG_VALUE)
			{
				if(m_dPosDailyTodayBuy > BAD_DOUBLE_VALUE)
				{
					if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
					m_dPnlTheo += m_pQuote->m_dPriceTheo * m_nQtyDailyTodayBuy - m_dPosDailyTodayBuy;
				}
				else
					return;
			}

			if(m_nQtyDailyTodaySell > BAD_LONG_VALUE)
			{
				if(m_dPosDailyTodaySell > BAD_DOUBLE_VALUE)
				{
					if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
					m_dPnlTheo += m_pQuote->m_dPriceTheo * m_nQtyDailyTodaySell - m_dPosDailyTodaySell;
				}
				else
					return;
			}
		}
	}

}

/////////////////////////////////////////////////////////////////////////////
//
void CMmRvPosAtom::_GetBasketIndexDividends(IIndexAtomPtr spBasketIndex, REGULAR_DIVIDENDS* pDivs, LONG nMaxCount) throw()
{
	ATLASSERT(spBasketIndex != NULL);
	EtsRegularDividend aDiv;

	for(LONG i = 0; i < nMaxCount; i++)
	{
		aDiv = spBasketIndex->BasketDiv[i];
		pDivs[i].nLastDivDate = static_cast<LONG>(aDiv.LastDate);
		pDivs[i].nFrequency = aDiv.Freq;
		pDivs[i].dAmount = aDiv.Amt;
	}
}

/////////////////////////////////////////////////////////////////////////////
//
void CMmRvPosAtom::_GetSyntheticRootBasketDividends(ISynthRootAtomPtr spSynthRoot, REGULAR_DIVIDENDS* pDivs, LONG nMaxCount) throw()
{
	ATLASSERT(spSynthRoot != NULL);
	EtsRegularDividend aDiv;

	for(LONG i = 0; i < nMaxCount; i++)
	{
		aDiv = spSynthRoot->BasketDiv[i];
		pDivs[i].nLastDivDate = static_cast<LONG>(aDiv.LastDate);
		pDivs[i].nFrequency = aDiv.Freq;
		pDivs[i].dAmount = aDiv.Amt;
	}
}

//STDMETHODIMP CMmRvPosAtom::AddTrade(IMmTradeInfoAtom* pTrade, IMmRvUndAtom* pUnd)
//{
//	long nQty = 0;
//	long nQtyInShares = 0;
//	HRESULT hr = S_OK;
//	IMmTradeInfoAtomPtr			spTrade(pTrade);
//	IMmRvAggregationDataAtomPtr spUndAtomData(pUnd);
//	double	dPriceClose = BAD_DOUBLE_VALUE;
//
//	try
//	{
//		if(spTrade!=NULL)
//		{
//			bool bIsBuy  = spTrade->IsBuy!=VARIANT_FALSE?true:false;
//			nQty		 = spTrade->Quantity * (bIsBuy?1:-1);
//			nQtyInShares = nQty * m_pQuote->m_nLotSize;
//			dPriceClose	 = m_pQuote->m_pPrice->m_dPriceClose;
//
//			if(bIsBuy)
//			{
//				if (m_nQtyLTDBuy == BAD_LONG_VALUE)
//					m_nQtyLTDBuy = 0 ;
//
//				m_nQtyLTDBuy += nQtyInShares;
//				if(spTrade->IsPosition)
//				{
//					if (/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= DBL_EPSILON )
//					{
//						if(m_dPosLTDBuy == BAD_DOUBLE_VALUE ) 
//							m_dPosLTDBuy = 0;
//
//						m_dPosLTDBuy += (/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * nQtyInShares);
//					}
//				}else
//				{
//					if (m_dPosLTDBuy == BAD_DOUBLE_VALUE)
//						m_dPosLTDBuy = 0;
//
//					m_dPosLTDBuy += (spTrade->Price * nQtyInShares);
//				}
//
//				if( spTrade->TradeDate < vt_date::GetCurrentDate(true))
//				{
//					if (m_nQtyDailyPrevDateBuy == BAD_LONG_VALUE) 
//						m_nQtyDailyPrevDateBuy = 0;
//
//					m_nQtyDailyPrevDateBuy +=  nQtyInShares;
//
//					if (/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= DBL_EPSILON) 
//					{
//						if(m_dPosDailyPrevDateBuy == BAD_DOUBLE_VALUE) 
//							m_dPosDailyPrevDateBuy = 0;
//						m_dPosDailyPrevDateBuy +=  (/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * nQtyInShares);
//					}
//					else
//						if(!spTrade->IsPosition)
//						{
//							if(m_dPosDailyPrevDateBuy == BAD_DOUBLE_VALUE) m_dPosDailyPrevDateBuy = 0;
//
//							m_dPosDailyPrevDateBuy += (spTrade->Price * nQtyInShares);
//						}
//				}else
//				{
//					if(m_nQtyDailyTodayBuy == BAD_LONG_VALUE) m_nQtyDailyTodayBuy = 0;
//
//					m_nQtyDailyTodayBuy += nQtyInShares;
//					if(spTrade->IsPosition) 
//					{
//						if(/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= DBL_EPSILON)
//						{
//							if (m_dPosDailyTodayBuy == BAD_DOUBLE_VALUE) m_dPosDailyTodayBuy = 0;
//							m_dPosDailyTodayBuy += (/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * nQtyInShares);
//						}
//					}
//					else
//					{
//						if (m_dPosDailyTodayBuy == BAD_DOUBLE_VALUE) m_dPosDailyTodayBuy = 0;
//						m_dPosDailyTodayBuy += (spTrade->Price * nQtyInShares);
//					}
//				}
//			}
//			else
//			{
//				if(m_nQtyLTDSell == BAD_LONG_VALUE)
//					m_nQtyLTDSell = 0;
//				m_nQtyLTDSell += nQtyInShares;
//
//				if (spTrade->IsPosition) 
//				{
//					if(/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= DBL_EPSILON)
//					{
//						if(m_dPosLTDSell == BAD_DOUBLE_VALUE) 
//							m_dPosLTDSell = 0;
//						m_dPosLTDSell += (/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * nQtyInShares);
//					}
//				}
//				else
//				{
//					if (m_dPosLTDSell == BAD_DOUBLE_VALUE) 
//						m_dPosLTDSell = 0;
//					m_dPosLTDSell += (spTrade->Price * nQtyInShares);
//				}
//
//				if (spTrade->TradeDate < vt_date::GetCurrentDate(true))
//				{
//					if (m_nQtyDailyPrevDateSell == BAD_LONG_VALUE) 
//						m_nQtyDailyPrevDateSell = 0; 
//					m_nQtyDailyPrevDateSell += nQtyInShares;
//					if (/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= DBL_EPSILON)
//					{
//						if (m_dPosDailyPrevDateSell == BAD_DOUBLE_VALUE) m_dPosDailyPrevDateSell = 0;
//						m_dPosDailyPrevDateSell +=  (/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * nQtyInShares);
//					}
//					else if(!spTrade->IsPosition)
//					{
//						if (m_dPosDailyPrevDateSell == BAD_DOUBLE_VALUE) m_dPosDailyPrevDateSell = 0;
//						m_dPosDailyPrevDateSell += (spTrade->Price * nQtyInShares);
//					}
//				}
//				else
//				{
//					if(m_nQtyDailyTodaySell == BAD_LONG_VALUE) m_nQtyDailyTodaySell = 0;
//					m_nQtyDailyTodaySell += nQtyInShares;
//					if (spTrade->IsPosition)
//					{
//						if (/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= DBL_EPSILON) 
//						{
//							if(m_dPosDailyTodaySell == BAD_DOUBLE_VALUE) 
//								m_dPosDailyTodaySell = 0;
//
//							m_dPosDailyTodaySell += (/*m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * nQtyInShares);
//						}
//					}
//					else
//					{
//						if (m_dPosDailyTodaySell == BAD_DOUBLE_VALUE) m_dPosDailyTodaySell = 0;
//						m_dPosDailyTodaySell += (spTrade->Price * nQtyInShares);
//					}
//				}
//			}
//
//			m_nQty +=  nQty;
//			m_nQtyInShares += nQtyInShares;
//
//			if(pUnd != NULL)
//			{
//				if(enCtOption==m_enContractType || enCtFutOption ==m_enContractType)
//				{
//					long lUndOptQty = BAD_LONG_VALUE;
//					spUndAtomData->get_OptQty(&lUndOptQty);
//
//					if (lUndOptQty == BAD_LONG_VALUE) 
//					{
//						lUndOptQty = 0L;
//						spUndAtomData->put_OptQty(0L);
//					}
//					spUndAtomData->put_OptQty(lUndOptQty + nQty);
//				}
//				else 
//					if (m_enContractType == enCtFuture)
//					{
//						long lUndFutQty = BAD_LONG_VALUE;
//						spUndAtomData->get_FutQty(&lUndFutQty);
//
//						if(lUndFutQty == BAD_LONG_VALUE) 
//						{
//							lUndFutQty = 0L;
//							spUndAtomData->put_FutQty(0L);
//						}
//						spUndAtomData->put_FutQty(lUndFutQty + nQty);
//
//						long lUndQty = BAD_LONG_VALUE;
//						spUndAtomData->get_Qty(&lUndQty);
//
//						if(lUndQty == BAD_LONG_VALUE){
//							spUndAtomData->put_Qty(0);
//							lUndQty = 0;
//						}
//						spUndAtomData->put_Qty(lUndQty+ nQtyInShares);
//
//					}
//					else
//					{
//						long lUndQty = BAD_LONG_VALUE;
//						spUndAtomData->get_Qty(&lUndQty);
//
//						if(lUndQty == BAD_LONG_VALUE){
//							spUndAtomData->put_Qty(0);
//							lUndQty = 0;
//						}
//						spUndAtomData->put_Qty(lUndQty+ nQtyInShares);
//					}
//			}
//
//		}
//		else
//			hr = E_POINTER;
//	}
//	catch (_com_error& e)
//	{
//		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvPosAtom, e.Error());
//	}
//	catch (...) 
//	{
//		hr = Error((LPCOLESTR)_bstr_t(L"Unknown error while adding trade to position"), IID_IMmRvPosAtom, E_FAIL);
//	}
//
//	return hr;
//}

STDMETHODIMP CMmRvPosAtom::GetOpositOption(BSTR*pVal)
{
	try
	{
		if(!pVal)
		{
			return E_POINTER;
		}

		if ( !m_bstrSymbolOposit.length() )
		{

			CString strTmp((LPCTSTR)m_bstrSymbol) ;
			*pVal = L"" ;
			long lOffset = 2 ;
			char chSymZv = strTmp.GetAt ( strTmp.GetLength() - 1  ) ;
			if ( chSymZv == '*' )
			{
				lOffset = 3 ;
			}
			if ( strTmp.GetLength() > 2 )
			{
				long lPos = strTmp.GetLength() - lOffset  ;
				char chSym = strTmp.GetAt ( lPos ) ;
				if ( chSym <= 'L' )
					chSym +=12 ;
				else
					chSym -=12 ;
				strTmp.SetAt( lPos , chSym ) ;
				m_bstrSymbolOposit = CComBSTR ( strTmp ) ;
			}
		}
		ObjectLock lock(this);
		*pVal = m_bstrSymbolOposit.copy();
	}
	catch ( ... )
	{
		ATLASSERT ( !"catch ..." ) ;
	}
	return S_OK ;
}

IMmRvPosAtomPtr CMmRvPosAtom::MakeCopy(bool bStaticDataOnly, bool bAddNewQuote)
{
	IMmRvPosAtomPtr spCopy ;
	try
	{
		CComObject<CMmRvPosAtom>* pCopy = NULL;

		HRESULT hr = CComObject<CMmRvPosAtom>::CreateInstance(&pCopy) ;
		if ( SUCCEEDED( hr ) )
		{
			spCopy.Attach(pCopy, TRUE);

			if ( !bAddNewQuote )
			{
				pCopy->m_pQuote  =  m_pQuote;
				pCopy->m_spQuote =  m_spQuote;
			}

			pCopy->InitSyntAndFut			( m_spSynthGreeks  , m_spFut, m_spActiveFuture ) ;

			pCopy->m_nID			= m_nID;
			pCopy->m_enContractType = m_enContractType;
			pCopy->m_bstrSymbol		= m_bstrSymbol;

			pCopy->m_enOptType		= m_enOptType;
			pCopy->m_dtExpiry		= m_dtExpiry;
			pCopy->m_dStrike		= m_dStrike;
			pCopy->m_dRate			= m_dRate;
			pCopy->m_dVegaWeight	= m_dVegaWeight;
			//pCopy->m_nExpiryMonth	= m_nExpiryMonth;
			pCopy->m_nOptionRootID	= m_nOptionRootID;

			pCopy->m_bVisible		= m_bVisible;
			pCopy->m_bCalcGreeks    = m_bCalcGreeks;
			pCopy->m_bstrImportId	= m_bstrImportId;

			pCopy->m_dTimeValue		= m_dTimeValue;
			pCopy->m_bIsSynthetic	= m_bIsSynthetic;
			pCopy->m_bVisible       = m_bVisible;  

			pCopy->m_nUndID			= m_nUndID;

			if(!bStaticDataOnly)
			{
				pCopy->m_nQty			= m_nQty;
				pCopy->m_nQtyInShares	= m_nQtyInShares;

				pCopy->m_nQtyLTDBuy		= m_nQtyLTDBuy;
				pCopy->m_nQtyLTDSell	= m_nQtyLTDSell;
				pCopy->m_dPosLTDBuy     = m_dPosLTDBuy;
				pCopy->m_dPosLTDSell	= m_dPosLTDSell;

				pCopy->m_nQtyDailyPrevDateBuy	= m_nQtyDailyPrevDateBuy;
				pCopy->m_nQtyDailyPrevDateSell	= m_nQtyDailyPrevDateSell  ;
				pCopy->m_dPosDailyPrevDateBuy	= m_dPosDailyPrevDateBuy  ;
				pCopy->m_dPosDailyPrevDateSell	= m_dPosDailyPrevDateSell ;

				pCopy->m_nQtyDailyTodayBuy	= m_nQtyDailyTodayBuy  ;
				pCopy->m_nQtyDailyTodaySell	= m_nQtyDailyTodaySell  ;
				pCopy->m_dPosDailyTodayBuy	= m_dPosDailyTodayBuy  ;
				pCopy->m_dPosDailyTodaySell	= m_dPosDailyTodaySell  ;

				pCopy->m_dPnlMtm			= m_dPnlMtm ;
				pCopy->m_dPnlTheo			= m_dPnlTheo ;

				pCopy->m_dDeltaInShares		= m_dDeltaInShares ;
				pCopy->m_dGammaInShares		= m_dGammaInShares ;
				pCopy->m_dGammaInSharesPerc	= m_dGammaInSharesPerc ;
				pCopy->m_dVegaInShares		= m_dVegaInShares  ;
				pCopy->m_dWtdVega			= m_dWtdVega  ;
				pCopy->m_dThetaInShares		= m_dThetaInShares ;
				pCopy->m_dRhoInShares		= m_dRhoInShares;
				pCopy->m_dThetaDeltaInShares= m_dThetaDeltaInShares ;
				pCopy->m_dThetaGammaInShares= m_dThetaGammaInShares ;
				pCopy->m_dVegaDeltaInShares	= m_dVegaDeltaInShares ;
				pCopy->m_dVegaGammaInShares	= m_dVegaGammaInShares;

				pCopy->m_dNetGamma				= m_dNetGamma;
				pCopy->m_bBadNetGamma			= m_bBadNetGamma;
			}
		}
		else
		{
			ATLASSERT ( !"Can't generate object" ) ;
		}
	}
	catch ( ... )
	{
		ATLASSERT ( !"catch ..." ) ;
	}
	return spCopy;
}

STDMETHODIMP CMmRvPosAtom::GetCopyOfObject(VARIANT_BOOL bGetCopyOpQuote , IMmRvPosAtom**ppCopy)
{

	try
	{
		IMmRvPosAtomPtr spCopy = MakeCopy ( false , bGetCopyOpQuote = VARIANT_TRUE ? true : false ) ;
		if(spCopy!=NULL)
			*ppCopy = spCopy.Detach();
	}
	catch ( ... )
	{
		ATLASSERT ( !"catch ..." ) ;
	}
	return S_OK ;
}

STDMETHODIMP CMmRvPosAtom::InitSyntAndFut ( IMmRvSynthGreeksColl* _pSynth, IMmRvFutAtom* _pFut, IMmRvFutAtom* _pActiveFuture ) 
{
	m_spFut				= _pFut ;
	m_spSynthGreeks		= _pSynth ;
	m_spActiveFuture = _pActiveFuture;
	return S_OK ;
}

STDMETHODIMP CMmRvPosAtom::GetFormatedXMLForDBUpdate(LONG vUndID, BSTR*pVal)
{	
	try
	{
		if(*pVal)
			::SysFreeString(*pVal);

		CHAR str[500] ={0};
		_bstr_t bsvt(_variant_t(m_dtExpiry, VT_DATE));

		_snprintf_s ( str, sizeof(str), 400 , "<Vl UndID=\"%i\" Strike=\"%f\" Expiry=\"%s\" Vola=\"%f\"/>", vUndID, m_dStrike, (LPCSTR)bsvt, m_pQuote->m_dImpliedVola) ;

		*pVal = SysAllocString(CA2W(str));
	}
	catch ( ... )
	{
		ATLASSERT ( "catch ..." ) ;
	}
	return S_OK ;
}

STDMETHODIMP CMmRvPosAtom::IsOTM ( DOUBLE dUndPriceTolerance, EtsPriceRoundingRuleEnum enPriceRoundingRule , VARIANT_BOOL*pVal )
{	
	//m_bVolatilityEnginrCalculation = VARIANT_FALSE ;
	DOUBLE dUndMidPrice = m_pQuote->m_dVolaCalcPrice ;
	if ( !pVal )
		return E_POINTER ;
	*pVal = VARIANT_TRUE ;
	if ( m_enOptType == enOtPut && dUndMidPrice  <= m_dStrike  )
		*pVal = VARIANT_FALSE ;
	if ( m_enOptType == enOtCall && dUndMidPrice >= m_dStrike )
		*pVal = VARIANT_FALSE ;
	return S_OK ;
}

STDMETHODIMP CMmRvPosAtom::DistanceToStrike(DOUBLE _Price,DOUBLE*pDistance)
{

	if ( !pDistance )
		return E_POINTER ;

	if ( _Price > 0 )
		*pDistance  = _Price - m_dStrike ;
	else
		*pDistance = BAD_DOUBLE_VALUE ;
	return S_OK ;
}

void CMmRvPosAtom::SimpleCopyForETS_VME(CComObject<CMmRvPosAtom>* pCopy)
{

	pCopy->InitSyntAndFut			( m_spSynthGreeks  , m_spFut, m_spActiveFuture ) ;

	pCopy->m_nID			= m_nID;
	pCopy->m_enContractType = m_enContractType;
	pCopy->m_bstrSymbol		= m_bstrSymbol;

	//pCopy->m_pQuote->m_bVolatilityEnginrCalculation = VARIANT_TRUE ;
	//pCopy->m_pQuote->m_bManual = m_pQuote->m_bManual ;

	pCopy->m_enOptType		= m_enOptType;
	pCopy->m_dtExpiry		= m_dtExpiry;
	pCopy->m_dStrike		= m_dStrike;
	pCopy->m_dRate			= m_dRate;
	pCopy->m_dVegaWeight	= m_dVegaWeight;
//	pCopy->m_nExpiryMonth	= m_nExpiryMonth;
	pCopy->m_nOptionRootID	= m_nOptionRootID;

	pCopy->m_bVisible		= m_bVisible;
	pCopy->m_bCalcGreeks    = m_bCalcGreeks;
	pCopy->m_bstrImportId	= m_bstrImportId;

	pCopy->m_dTimeValue		= m_dTimeValue;
	pCopy->m_bIsSynthetic	= m_bIsSynthetic;

	pCopy->m_nUndID			= m_nUndID;

	{
		pCopy->m_nQty			= m_nQty;
		pCopy->m_nQtyInShares	= m_nQtyInShares;

		pCopy->m_nQtyLTDBuy		= m_nQtyLTDBuy;
		pCopy->m_nQtyLTDSell	= m_nQtyLTDSell;
		pCopy->m_dPosLTDBuy     = m_dPosLTDBuy;
		pCopy->m_dPosLTDSell	= m_dPosLTDSell;

		pCopy->m_nQtyDailyPrevDateBuy	= m_nQtyDailyPrevDateBuy;
		pCopy->m_nQtyDailyPrevDateSell	= m_nQtyDailyPrevDateSell  ;
		pCopy->m_dPosDailyPrevDateBuy	= m_dPosDailyPrevDateBuy  ;
		pCopy->m_dPosDailyPrevDateSell	= m_dPosDailyPrevDateSell ;

		pCopy->m_nQtyDailyTodayBuy	= m_nQtyDailyTodayBuy  ;
		pCopy->m_nQtyDailyTodaySell	= m_nQtyDailyTodaySell  ;
		pCopy->m_dPosDailyTodayBuy	= m_dPosDailyTodayBuy  ;
		pCopy->m_dPosDailyTodaySell	= m_dPosDailyTodaySell  ;

		pCopy->m_dPnlMtm			= m_dPnlMtm ;
		pCopy->m_dPnlTheo			= m_dPnlTheo ;

		pCopy->m_dDeltaInShares		= m_dDeltaInShares ;
		pCopy->m_dGammaInShares		= m_dGammaInShares ;
		pCopy->m_dGammaInSharesPerc	= m_dGammaInSharesPerc ;
		pCopy->m_dVegaInShares		= m_dVegaInShares  ;
		pCopy->m_dWtdVega			= m_dWtdVega  ;
		pCopy->m_dThetaInShares		= m_dThetaInShares ;
		pCopy->m_dRhoInShares		= m_dRhoInShares;
		pCopy->m_dThetaDeltaInShares= m_dThetaDeltaInShares ;
		pCopy->m_dThetaGammaInShares= m_dThetaGammaInShares ;
		pCopy->m_dVegaDeltaInShares	= m_dVegaDeltaInShares ;
		pCopy->m_dVegaGammaInShares	= m_dVegaGammaInShares;

		pCopy->m_dNetGamma				= m_dNetGamma;
		pCopy->m_bBadNetGamma			= m_bBadNetGamma;
	}
}
//// MmRvPosAtom.cpp : Implementation of CMmRvPosAtom
//#include "stdafx.h"
//#include "MmRvPosAtom.h"
//#include "MmRvUndColl.h"
//#include "MmRvUndAtom.h"
//
///////////////////////////////////////////////////////////////////////////////
////
//STDMETHODIMP CMmRvPosAtom::CalcOptionGreeks(IMmRvUndColl* aUndColl,
//											IMmRvUndAtom* aUnd,
//											DOUBLE dUndMidPrice,
//											LONG nMask,
//											VARIANT_BOOL bIsPnlLTD,
//											EtsCalcModelTypeEnum enCalcModel,
//											VARIANT_BOOL bUseTheoVolatility,
//											VARIANT_BOOL bUseTheoVolaNoBid,
//											VARIANT_BOOL bUseTheoVolaBadMarket,
//											DOUBLE dUndPriceTolerance,
//											EtsPriceRoundingRuleEnum enPriceRoundingRule)
//{
//	if(aUnd == NULL || aUndColl == NULL)
//		return Error(L"Invalid objects passed.", IID_IMmRvPosAtom, E_INVALIDARG);
//
//	if(m_enContractType != enCtOption)
//		return S_OK;
//
//	try
//	{
//		IMmRvUndCollPtr spUndColl(aUndColl);
//		IMmRvUndAtomPtr spUnd(aUnd);
//		IEtsPriceProfileAtomPtr spUndPriceProfile;
//		IEtsPriceProfileAtomPtr spOptPriceProfile;
//
//		CSafeArrayWrapper<double> saDates;
//		CSafeArrayWrapper<double> saAmounts;
//
//		_CHK(spUnd->get_UndPriceProfile(&spUndPriceProfile));
//		_CHK(spUnd->get_OptPriceProfile(&spOptPriceProfile));
//
//		DOUBLE dUndPrice = dUndMidPrice;
//		DOUBLE sUndPriceSave = dUndMidPrice;
//		ISynthRootAtomPtr spSynthRoot;
//
//		if(m_bIsSynthetic)
//		{
//			ISynthRootCollPtr spSynthRootColl;
//			_CHK(spUnd->get_SynthRoots(&spSynthRootColl));
//			if(spSynthRootColl != NULL)
//			{
//				spSynthRoot = spSynthRootColl->Item[m_nOptionRootID];
//				if(spSynthRoot != NULL)
//				{
//					DOUBLE dSynthBid = 0., dSynthAsk = 0., dSynthLast = 0.;
//					_CHK(spUnd->GetSyntheticUnderlyingPrice(spUndColl, spSynthRoot, &dSynthBid, &dSynthAsk, &dSynthLast));
//					dUndMidPrice = spUndPriceProfile->GetUndPriceMid(dSynthBid, dSynthAsk, dSynthLast, dUndPriceTolerance, enPriceRoundingRule, NULL, TRUE);
//				}
//			}
//		}
//		/*else
//		{
//			if(dUndMidPrice <= BAD_DOUBLE_VALUE) // try to get underlying mid price if not passed
//			{
//				enPriceStatusMid = enRpsNone;
//				DOUBLE dUndPriceBid = 0., dUndPriceAsk = 0., dUndPriceLast = 0.;
//				_CHK(spUnd->get_PriceBid(&dUndPriceBid));
//				_CHK(spUnd->get_PriceAsk(&dUndPriceAsk));
//				_CHK(spUnd->get_PriceLast(&dUndPriceLast));
//
//				dUndPrice = spUndPriceProfile->GetUndPriceMid(dUndPriceBid, dUndPriceAsk,
//						dUndPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enPriceStatusMid);
//
//				_CHK(spUnd2->put_ReplacePriceStatus(enPriceStatusMid));
//			}
//		}*/
//
//		EtsReplacePriceStatusEnum enPriceStatusMid = enRpsNone;
//		DOUBLE dOptPriceMid = 0.;
//		dOptPriceMid = spOptPriceProfile->GetOptPriceMid(m_dPriceBid, m_dPriceAsk, m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, 0., &enPriceStatusMid);
//
//		m_enReplacePriceStatus = enPriceStatusMid;
//
//		if(nMask != GT_NOTHING && dUndMidPrice > DBL_EPSILON)
//		{
//			GREEKS aGreeks;
//			memset(&aGreeks, 0, sizeof(aGreeks));
//			aGreeks.nMask = nMask;
//			__MmRvPosAtom::ClearValues();
//
//			LONG nModel = static_cast<LONG>(enCalcModel);
//			VARIANT_BOOL bIsAmerican = VARIANT_FALSE;
//			_CHK(spUnd->get_IsAmerican(&bIsAmerican));
//			LONG nIsAmerican = (bIsAmerican ? 1L : 0L);
//
//			DOUBLE dYield = 0., dVola = 0.;
//
//			LONG nDivCount = 0L, nRetCount = 0L;
//			EtsContractTypeEnum enUndType = enCtNone;
//			_CHK(spUnd->get_ContractType(&enUndType));
//
//			LONG nExpiry = static_cast<LONG>(m_dtExpiry);
//			LONG nToday = static_cast<LONG>(vt_date::GetCurrentDate());
//
//			DOUBLE dSkew = 0., dKurt = 0.;
//
//			// prepare parameters
//			if(!m_bIsSynthetic)
//			{
//				_CHK(spUnd->get_Skew(&dSkew));
//				_CHK(spUnd->get_Kurt(&dKurt));
//
//				if(enUndType == enCtStock)
//				{
//					nDivCount = 0;
//					IEtsIndexDivAtomPtr spDiv;
//					spUnd->get_Dividend(&spDiv);
//					if (spDiv != NULL)
//					{
//						spDiv->GetDividendCount(nToday, nExpiry, &nDivCount);
//						if(nDivCount > 0L) 
//						{
//							LPSAFEARRAY psaAmounts = NULL;
//							LPSAFEARRAY psaDates = NULL;
//
//							spDiv->GetDividends(nToday, nExpiry, nDivCount, &psaAmounts, &psaDates, &nRetCount);
//
//							saAmounts.Attach(psaAmounts);
//							saDates.Attach(psaDates);
//						}
//					}
//				}
//				else
//				{
//					VARIANT_BOOL bIsBasket = VARIANT_FALSE;
//
//					IIndexAtomPtr spBasketIndex;
//					_CHK(spUnd->get_BasketIndex(&spBasketIndex));
//
//					if(spBasketIndex != NULL)
//					{
//						_CHK((spBasketIndex->get_IsBasket(&bIsBasket)));
//						if(bIsBasket)
//						{
//							IEtsIndexDivCollPtr spBasketDivs;
//							spBasketIndex->get_BasketDivs(&spBasketDivs);
//							nDivCount = 0;
//							LPSAFEARRAY psaAmounts = NULL;
//							LPSAFEARRAY psaDates = NULL;
//
//							spBasketDivs->GetDividends(nToday, nExpiry, nDivCount, &psaAmounts, &psaDates, &nDivCount);
//
//							saAmounts.Attach(psaAmounts);
//							saDates.Attach(psaDates);
//						}
//					}
//					if(bIsBasket)
//						dYield = 0.0;
//					else 
//						_CHK(spUnd->get_Yield(&dYield));
//				}
//			}
//			else if(spSynthRoot != NULL) // synthetic
//			{
//				VARIANT_BOOL bIsBasket = spSynthRoot->Basket;
//
//				dSkew  = spSynthRoot->Skew;
//				dKurt  = spSynthRoot->Kurt;
//
//				if(bIsBasket)
//				{
//					dYield  = 0.0;
//					IEtsIndexDivCollPtr spBasketDivs;
//					LONG nBaskDivCount = 0L;
//					spSynthRoot->get_BasketDivs(&spBasketDivs);
//					spBasketDivs->get_Count(&nBaskDivCount);
//
//					if((spBasketDivs != NULL)&&(nBaskDivCount > 0L))
//					{
//						nDivCount = 0;
//
//						LPSAFEARRAY psaAmounts = NULL;
//						LPSAFEARRAY psaDates = NULL;
//
//						spBasketDivs->GetDividends(nToday, nExpiry, nDivCount, &psaAmounts, &psaDates, &nDivCount);
//
//						saAmounts.Attach(psaAmounts);
//						saDates.Attach(psaDates);
//					}
//				}
//				else
//					dYield = spSynthRoot->Yield;
//			}
//
//			// calc vola
//			if(bUseTheoVolatility)
//				dVola = m_dVola;
//			else
//			{
//				dVola = 0.;
//				if(!bUseTheoVolaNoBid || bUseTheoVolaNoBid && m_dPriceBid > DBL_EPSILON) 
//				{
//					if(dOptPriceMid > DBL_EPSILON)
//					{
//						LONG nFlag = VF_OK;
//						dVola = ::CalcVolatilityMM3(m_dRate, dYield, dUndMidPrice, dOptPriceMid, m_dStrike, 
//							nExpiry - nToday, m_enOptType, nIsAmerican, nDivCount,
//							saAmounts.GetPlainData(), saDates.GetPlainData(), 100L, dSkew, dKurt, nModel, &nFlag);
//						
//
//						if(bUseTheoVolaBadMarket && nFlag != VF_OK)
//							dVola = m_dVola;
//					}
//					else if (bUseTheoVolaBadMarket)
//						dVola = m_dVola;
//				}
//				else
//					dVola = m_dVola;
//			}
//
//			// calc greeks
//			nRetCount = ::CalcGreeksMM2(m_dRate, dYield, dUndMidPrice, m_dStrike, dVola, nExpiry - nToday,
//				m_enOptType, nIsAmerican, nDivCount, saAmounts.GetPlainData(), saDates.GetPlainData(), 100L, dSkew, dKurt, nModel, &aGreeks);
//			
//
//			if(nRetCount != 0L)
//			{
//				if ((aGreeks.dTheoPrice > BAD_DOUBLE_VALUE)&&(aGreeks.dTheoPrice < 0))
//					aGreeks.dTheoPrice = 0;
//
//				if((aGreeks.nMask & GT_THEOPRICE) && _finite(aGreeks.dTheoPrice) && aGreeks.dTheoPrice >= 0.)
//
//					m_dPriceTheo = aGreeks.dTheoPrice;
//				if((aGreeks.nMask & GT_DELTA) && _finite(aGreeks.dDelta))
//					m_dDelta = aGreeks.dDelta;
//				if((aGreeks.nMask & GT_GAMMA) && _finite(aGreeks.dGamma))
//					m_dGamma = aGreeks.dGamma;
//				if((aGreeks.nMask & GT_THETA) && _finite(aGreeks.dTheta))
//					m_dTheta = aGreeks.dTheta;
//				if((aGreeks.nMask & GT_VEGA) && _finite(aGreeks.dVega))
//					m_dVega = aGreeks.dVega;
//				if((aGreeks.nMask & GT_RHO) && _finite(aGreeks.dRho))
//					m_dRho = aGreeks.dRho;
//				if((aGreeks.nMask & GT_DELTA_VEGA) && _finite(aGreeks.dDeltaVega))
//					m_dVegaDelta = aGreeks.dDeltaVega;
//				if((aGreeks.nMask & GT_GAMMA_VEGA) && _finite(aGreeks.dGammaVega))
//					m_dVegaGamma = aGreeks.dGammaVega;
//				if((aGreeks.nMask & GT_DELTA_THETA) && _finite(aGreeks.dDeltaTheta))
//					m_dThetaDelta = aGreeks.dDeltaTheta;
//				if((aGreeks.nMask & GT_GAMMA_THETA) && _finite(aGreeks.dGammaTheta))
//					m_dThetaGamma = aGreeks.dGammaTheta;
//			}
//		}
//
//		// clear values in shares
//		__MmRvPosAtom::ClearValuesInShares();
//		if(m_bIsSynthetic && m_spSynthGreeks != NULL)
//		{
//			IUnknownPtr spUnk;
//			_variant_t varItem;
//			ULONG nFetched = 0L;
//			HRESULT hr;
//			IMmRvSynthGreeksAtomPtr spSynthGreeks;
//
//			_CHK(m_spSynthGreeks->get__NewEnum(&spUnk));
//			IEnumVARIANTPtr spSynthGreekEnum(spUnk);
//			_CHK(spSynthGreekEnum->Reset());
//			while((hr = spSynthGreekEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//			{
//				ATLASSERT(varItem.vt == VT_DISPATCH);
//				spSynthGreeks = varItem;
//				if(spSynthGreeks != NULL)
//					_CHK(spSynthGreeks->ClearValuesInShares());
//			}
//		}
//
//		// calc values in shares
//		EtsReplacePriceStatusEnum enPriceStatusBid = enRpsNone;
//		DOUBLE dOptPriceBid = spOptPriceProfile->GetOptPriceBidForPnL(m_dPriceBid, m_dPriceAsk, m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_dPriceTheo, &enPriceStatusBid);
//
//		EtsReplacePriceStatusEnum enPriceStatusAsk = enRpsNone;
//		DOUBLE dOptPriceAsk = spOptPriceProfile->GetOptPriceAskForPnL(m_dPriceBid, m_dPriceAsk, m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_dPriceTheo, &enPriceStatusAsk);
//
//		enPriceStatusMid = enRpsNone;
//		dOptPriceMid = spOptPriceProfile->GetOptPriceMid(m_dPriceBid, m_dPriceAsk, m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_dPriceTheo, &enPriceStatusMid);
//
//		m_enReplacePriceStatus = static_cast<EtsReplacePriceStatusEnum>(enPriceStatusMid | enPriceStatusBid | enPriceStatusAsk);
//
//		
//
//		// pnl
//		_CalcPnlMtm(bIsPnlLTD, dOptPriceBid, dOptPriceAsk, spOptPriceProfile->GetBadOptSinglePriceRule() == enObsprReplaceWithZero);
//		_CalcPnlTheo(bIsPnlLTD);
//
//		// delta & gamma
//		if(m_dDelta > BAD_DOUBLE_VALUE || m_dGamma > BAD_DOUBLE_VALUE)
//		{
//			if(!m_bIsSynthetic || m_spSynthGreeks == NULL || spSynthRoot == NULL)
//			{
//				if(m_dDelta > BAD_DOUBLE_VALUE)
//					m_dDeltaInShares = m_dDelta * m_nQtyInShares;
//
//				if(m_dGamma > BAD_DOUBLE_VALUE)
//				{
//					m_dGammaInShares = m_dGamma * m_nQtyInShares;
//
//					if(dUndMidPrice > DBL_EPSILON)
//						m_dGammaInSharesPerc = m_dGamma * m_nQtyInShares * dUndMidPrice / 100.;
//
//					m_dNetGamma = m_dGamma * m_nQtyInShares  / 100.;
//
//					if(dUndMidPrice > DBL_EPSILON)
//						m_dNetGamma = m_dGamma * m_nQtyInShares  * dUndMidPrice * dUndMidPrice / 100.;
//
//				}
//
//
//			}
//			else // synthetic
//			{
//				LONG nUndID = 0L, nSynthUndID = 0L;
//				_CHK(spUnd->get_ID(&nUndID));
//				ISynthRootCompAtomPtr spSRComp;
//				ISynthRootCompCollPtr spSRCompColl;
//
//				spSRCompColl = spSynthRoot->SynthRootComponents;
//				if(spSRCompColl != NULL)
//				{
//					spSRComp = spSRCompColl->Item[nUndID];
//					if(spSRComp != NULL)
//					{
//						if(m_dDelta > BAD_DOUBLE_VALUE)
//							m_dDeltaInShares = m_dDelta * m_nQtyInShares * spSRComp->Weight;
//
//						if(m_dGamma > BAD_DOUBLE_VALUE)
//							m_dGammaInShares = m_dGamma * m_nQtyInShares * spSRComp->Weight;
//
//
//					}
//
//					if(dUndPrice > DBL_EPSILON && m_dGammaInShares > BAD_DOUBLE_VALUE)
//						m_dGammaInSharesPerc = m_dGammaInShares * dUndPrice / 100.;
//
//					IUnknownPtr spUnk;
//					_variant_t varItem;
//					ULONG nFetched = 0L;
//					HRESULT hr;
//					IMmRvSynthGreeksAtomPtr spSynthGreeks;
//
//					_CHK(m_spSynthGreeks->get__NewEnum(&spUnk));
//					IEnumVARIANTPtr spSynthGreekEnum(spUnk);
//					_CHK(spSynthGreekEnum->Reset());
//					while((hr = spSynthGreekEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//					{
//						ATLASSERT(varItem.vt == VT_DISPATCH);
//						spSynthGreeks = varItem;
//						if(spSynthGreeks != NULL)
//						{
//							DOUBLE dGammaInShares = BAD_DOUBLE_VALUE;
//
//							_CHK(spSynthGreeks->get_SynthUndID(&nSynthUndID));
//							spSRComp = spSRCompColl->Item[nSynthUndID];
//							if(spSRComp != NULL)
//							{
//								DOUBLE dWeight = spSRComp->Weight;
//								if(m_dDelta > BAD_DOUBLE_VALUE)
//									_CHK(spSynthGreeks->put_DeltaInShares(m_dDelta * m_nQtyInShares * dWeight));
//
//								if(m_dGamma > BAD_DOUBLE_VALUE)
//								{
//									dGammaInShares = m_dGamma * m_nQtyInShares * dWeight;
//									_CHK(spSynthGreeks->put_GammaInShares(dGammaInShares));
//								}
//							}
//							else if(nSynthUndID == 0L) // USD_ID
//							{
//								DOUBLE dCashValue = spSynthRoot->CashValue;
//								if(m_dDelta > BAD_DOUBLE_VALUE)
//									_CHK(spSynthGreeks->put_DeltaInShares(m_dDelta * m_nQtyInShares * dCashValue));
//
//								if(m_dGamma > BAD_DOUBLE_VALUE)
//								{
//									dGammaInShares = m_dGamma * m_nQtyInShares * dCashValue;
//									_CHK(spSynthGreeks->put_GammaInShares(dGammaInShares));
//								}
//							}
//
//							if(m_dGamma > BAD_DOUBLE_VALUE)
//							{
//								IMmRvUndAtomPtr spUnd2;
//								_CHK(spUndColl->get_Item(nSynthUndID, &spUnd2));
//								if(spUnd2 != NULL)
//								{
//									IEtsPriceProfileAtomPtr spUndPriceProfile2;
//									_CHK(spUnd2->get_UndPriceProfile(&spUndPriceProfile2));
//
//									enPriceStatusMid = enRpsNone;
//									DOUBLE dUndPriceBid = 0., dUndPriceAsk = 0., dUndPriceLast = 0.;
//									_CHK(spUnd2->get_PriceBid(&dUndPriceBid));
//									_CHK(spUnd2->get_PriceAsk(&dUndPriceAsk));
//									_CHK(spUnd2->get_PriceLast(&dUndPriceLast));
//
//									dUndPrice = spUndPriceProfile2->GetUndPriceMid(dUndPriceBid, dUndPriceAsk,
//											dUndPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enPriceStatusMid, TRUE);
//
//									_CHK(spUnd2->put_ReplacePriceStatus(enPriceStatusMid));
//
//									if(dUndPrice > DBL_EPSILON && dGammaInShares > BAD_DOUBLE_VALUE)
//									{
//										_CHK(spSynthGreeks->put_GammaInSharesPerc(dGammaInShares * dUndPrice / 100.));
//										_CHK(spSynthGreeks->put_NetGamma(dGammaInShares * dUndPrice * dUndPrice / 100));
//									}
//								}
//							}
//						}
//					}
//				}
//				if(dUndMidPrice > DBL_EPSILON)
//					m_dNetGamma = m_dGammaInShares * sUndPriceSave * sUndPriceSave / 100.;
//
//			}
//		}
//
//		// other theos
//		if(m_dVega > BAD_DOUBLE_VALUE)
//		{
//			m_dVegaInShares = m_dVega * m_nQtyInShares;
//			m_dWtdVega = m_dVegaInShares * m_dVegaWeight;
//		}
//
//		if(m_dTheta > BAD_DOUBLE_VALUE)
//			m_dThetaInShares = m_dTheta * m_nQtyInShares;
//
//		if(m_dRho > BAD_DOUBLE_VALUE)
//			m_dRhoInShares = m_dRho * m_nQtyInShares;
//
//		if(m_dVegaDelta > BAD_DOUBLE_VALUE)
//			m_dVegaDeltaInShares = m_dVegaDelta * m_nQtyInShares;
//
//		if(m_dVegaGamma > BAD_DOUBLE_VALUE && dUndMidPrice > DBL_EPSILON)
//			m_dVegaGammaInShares = m_dVegaGamma * m_nQtyInShares * dUndMidPrice / 100.;
//
//		if(m_dThetaDelta > BAD_DOUBLE_VALUE)
//			m_dThetaDeltaInShares = m_dThetaDelta * m_nQtyInShares;
//
//		if(m_dThetaGamma > BAD_DOUBLE_VALUE && dUndMidPrice > DBL_EPSILON)
//			m_dThetaGammaInShares = m_dThetaGamma * m_nQtyInShares * dUndMidPrice / 100.;
//
//
//		DOUBLE dOptPricePnL = 0.;
//		VARIANT_BOOL bUseMidMarketForPnL = spOptPriceProfile->UseMidMarketForPnL;
//		VARIANT_BOOL bUseZeroBidRule = spOptPriceProfile->UseZeroBidRule;
//		if (bUseMidMarketForPnL == VARIANT_TRUE && bUseZeroBidRule == VARIANT_FALSE)
//			dOptPricePnL = dOptPriceMid;
//		else
//		{
//			if(m_nQty > 0.)
//				dOptPricePnL = spOptPriceProfile->GetOptPriceBidForPnL(m_dPriceBid, m_dPriceAsk, m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_dPriceTheo, NULL);
//			else
//				dOptPricePnL = spOptPriceProfile->GetOptPriceAskForPnL(m_dPriceBid, m_dPriceAsk, m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_dPriceTheo, NULL);
//		}
//
//		if(dUndMidPrice > DBL_EPSILON && dOptPricePnL >= 0/*DBL_EPSILON*/)
//		{
////			formula for time value:
////			for calls strike >=spot: time value= call price
////			for calls strike <spot, time value= max(0, call price -(spot-strike))
////			for puts strike >spot: time value= max(0, put price -(strike-spot))
////			for puts strike <=spot, time value= put price
//			if(m_enOptType == enOtCall)
//			{
//				if(m_dStrike >= dUndMidPrice)
//					m_dTimeValue = dOptPricePnL;
//				else
//					m_dTimeValue = max(0, dOptPricePnL - (dUndMidPrice-m_dStrike));
//			}
//			else
//			{
//				if(m_dStrike <= dUndMidPrice)
//					m_dTimeValue = dOptPricePnL;
//				else
//					m_dTimeValue = max(0, dOptPricePnL- (m_dStrike-dUndMidPrice));
//			}
////			m_dTimeValue = dOptPriceMid - (m_enOptType == enOtCall
////							? (dUndMidPrice - m_dStrike > DBL_EPSILON ? dUndMidPrice - m_dStrike : 0.)
////							: (m_dStrike - dUndMidPrice > DBL_EPSILON ? m_dStrike - dUndMidPrice : 0.));
//		}
//
//		if(m_dNetGamma <= BAD_DOUBLE_VALUE)
//		{
//			m_dNetGamma = m_dGamma * m_nQtyInShares  / 100.;
//			if(dUndMidPrice > DBL_EPSILON)
//				m_dNetGamma = m_dGamma * m_nQtyInShares  * dUndMidPrice * dUndMidPrice / 100.;
//
//		}
//	}
//	catch(const _com_error& e)
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvPosAtom, e.Error());
//	}
//
//	return S_OK;
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//STDMETHODIMP CMmRvPosAtom::CalcFutOptionGreeks(IMmRvUndAtom* aUnd,
//											DOUBLE dUndMidPrice,
//											LONG nMask,
//											VARIANT_BOOL bIsPnlLTD,
//											EtsCalcModelTypeEnum enCalcModel,
//											VARIANT_BOOL bUseTheoVolatility,
//											VARIANT_BOOL bUseTheoVolaNoBid,
//											VARIANT_BOOL bUseTheoVolaBadMarket,
//											DOUBLE dUndPriceTolerance,
//											EtsPriceRoundingRuleEnum enPriceRoundingRule)
//{
//	if(aUnd == NULL)
//		return Error(L"Invalid object passed.", IID_IMmRvPosAtom, E_INVALIDARG);
//
//	if(m_enContractType != enCtFutOption)
//		return S_OK;
//
//	try
//	{
//		IMmRvUndAtomPtr spUnd(aUnd);
//		IEtsPriceProfileAtomPtr spUndPriceProfile;
//		IEtsPriceProfileAtomPtr spOptPriceProfile;
//
//		_CHK(m_spFut->get_UndPriceProfile(&spUndPriceProfile));
//		_CHK(m_spFut->get_OptPriceProfile(&spOptPriceProfile));
//
//		EtsReplacePriceStatusEnum enPriceStatusMid = enRpsNone;
//		DOUBLE dFutMidPrice = 0., dOptPriceMid = 0.;
//		DOUBLE dFutPriceBid = 0., dFutPriceAsk = 0., dFutPriceLast = 0.;
//
//		_CHK(m_spFut->get_PriceBid(&dFutPriceBid));
//		_CHK(m_spFut->get_PriceAsk(&dFutPriceAsk));
//		_CHK(m_spFut->get_PriceLast(&dFutPriceLast));
//
//		dFutMidPrice = spUndPriceProfile->GetUndPriceMid(dFutPriceBid, dFutPriceAsk, dFutPriceLast, dUndPriceTolerance, enPriceRoundingRule, NULL, TRUE);
//		dOptPriceMid = spOptPriceProfile->GetOptPriceMid(m_dPriceBid, m_dPriceAsk, m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, 0., &enPriceStatusMid);
//
//		m_enReplacePriceStatus = enPriceStatusMid;
//
//		CSafeArrayWrapper<double> saDates;
//		CSafeArrayWrapper<double> saAmounts;
//
//		DOUBLE dYield = 0;
//		LPVOID lpDateData = NULL;
//		LPVOID lpAmountData = NULL;
//		IEtsIndexDivAtomPtr			spDividend = NULL;
//		IIndexAtomPtr				spBasketIndex = NULL;
//		EtsContractTypeEnum			m_enUndType = enCtStock;
//		if (spUnd != NULL)
//		{
//			spUnd->get_Dividend(&spDividend);
//			spUnd->get_ContractType(&m_enUndType);
//			spUnd->get_BasketIndex(&spBasketIndex);
//		}
//
//		if(nMask != GT_NOTHING && dFutMidPrice > DBL_EPSILON)
//		{
//			GREEKS aGreeks;
//			memset(&aGreeks, 0, sizeof(aGreeks));
//			aGreeks.nMask = nMask;
//			__MmRvPosAtom::ClearValues();
//
//			LONG nModel = static_cast<LONG>(enCalcModel);
//			VARIANT_BOOL bIsAmerican = VARIANT_FALSE;
//			_CHK(m_spFut->get_IsAmerican(&bIsAmerican));
//			LONG nIsAmerican = (bIsAmerican ? 1L : 0L);
//
//			DOUBLE dVola = 0.;
//			LONG nRetCount = 0L;
//
//			LONG nExpiry = static_cast<LONG>(m_dtExpiry);
//			LONG nToday = static_cast<LONG>(vt_date::GetCurrentDate());
//
//			DOUBLE dSkew = 0., dKurt = 0.;
//			_CHK(spUnd->get_Skew(&dSkew));
//			_CHK(spUnd->get_Kurt(&dKurt));
//
//			////////////////////////
//			LONG nDivCount = 0L;
//			nRetCount = 0L;
//
//			if(m_enUndType == enCtStock)
//			{
//				if (spDividend != NULL)
//				{
//					nDivCount = 0;
//					spDividend->GetDividendCount(nToday, nExpiry, &nDivCount);
//					if (nDivCount< 0)
//						nDivCount = 0;
//
//					if (nDivCount> 0)
//					{
//
//						LPSAFEARRAY psaDates	= NULL;
//						LPSAFEARRAY psaAmounts  = NULL ;
//
//						spDividend->GetDividends(nToday, nExpiry, nDivCount, &psaAmounts, &psaDates, &nRetCount);
//						
//						saDates.Attach(psaDates);
//						saAmounts.Attach(psaAmounts);
//					}
//				}
//			}
//			else
//			{
//				if(spBasketIndex != NULL)
//				{
//					LONG nBaskDivCount = 0L; VARIANT_BOOL bIsBasket = VARIANT_FALSE;
//					nDivCount = 0;
//					_CHK(spBasketIndex->get_IsBasket(&bIsBasket));
//
//					IEtsIndexDivCollPtr spDivColl = NULL;
//					spBasketIndex->get_BasketDivs(&spDivColl);
//
//					if ( bIsBasket && spDivColl != NULL )
//					{
//						dYield = 0.0;
//						spDivColl->GetDividendCount(nToday, nExpiry, &nDivCount);
//						if(nDivCount > 0L)
//						{
//
//							LPSAFEARRAY psaDates	= NULL;
//							LPSAFEARRAY psaAmounts  = NULL ;
//
//							spDivColl->GetDividends(nToday, nExpiry,  nDivCount, &psaAmounts, &psaDates, &nRetCount);
//
//							saDates.Attach(psaDates);
//							saAmounts.Attach(psaAmounts);
//						}
//					}
//				}
//
//			}
//
//			if(nDivCount < 0)
//				nDivCount = 0;
//
//
//			/////////////////////////
//			// calc vola
//			if(bUseTheoVolatility)
//				dVola = m_dVola;
//			else
//			{
//				dVola = 0.;
//				if(!bUseTheoVolaNoBid || bUseTheoVolaNoBid && m_dPriceBid > DBL_EPSILON) 
//				{
//					if(dOptPriceMid > DBL_EPSILON)
//					{
//						LONG nFlag = VF_OK;
//						dVola = ::CalcFutureOptionVolatility(m_dRate, dFutMidPrice, dOptPriceMid, m_dStrike, 
//							nExpiry - nToday, m_enOptType, nIsAmerican, 100L, dSkew, dKurt, nModel, &nFlag);
//						
//
//						if(bUseTheoVolaBadMarket && nFlag != VF_OK)
//							dVola = m_dVola;
//					}
//					else if (bUseTheoVolaBadMarket)
//						dVola = m_dVola;
//				}
//				else
//					dVola = m_dVola;
//			}
//
//			// calc greeks
//			nRetCount = ::CalcFutureOptionGreeks(m_dRate, dFutMidPrice, m_dStrike, dVola, nExpiry - nToday,
//				m_enOptType, nIsAmerican, 100L, dSkew, dKurt, nModel, &aGreeks);
//			
//			if ((aGreeks.dTheoPrice > BAD_DOUBLE_VALUE)&&(aGreeks.dTheoPrice < 0))
//				aGreeks.dTheoPrice = 0;
//
//			if (aGreeks.dTheoPrice < 0)	aGreeks.dTheoPrice = 0;
//			if((aGreeks.nMask & GT_THEOPRICE) && _finite(aGreeks.dTheoPrice) && aGreeks.dTheoPrice >= 0.)
//					m_dPriceTheo = aGreeks.dTheoPrice;
//				if((aGreeks.nMask & GT_DELTA) && _finite(aGreeks.dDelta))
//					m_dDelta = aGreeks.dDelta;
//				if((aGreeks.nMask & GT_GAMMA) && _finite(aGreeks.dGamma))
//					m_dGamma = aGreeks.dGamma;
//				if((aGreeks.nMask & GT_THETA) && _finite(aGreeks.dTheta))
//					m_dTheta = aGreeks.dTheta;
//				if((aGreeks.nMask & GT_VEGA) && _finite(aGreeks.dVega))
//					m_dVega = aGreeks.dVega;
//				if((aGreeks.nMask & GT_RHO) && _finite(aGreeks.dRho))
//					m_dRho = aGreeks.dRho;
//				if((aGreeks.nMask & GT_DELTA_VEGA) && _finite(aGreeks.dDeltaVega))
//					m_dVegaDelta = aGreeks.dDeltaVega;
//				if((aGreeks.nMask & GT_GAMMA_VEGA) && _finite(aGreeks.dGammaVega))
//					m_dVegaGamma = aGreeks.dGammaVega;
//				if((aGreeks.nMask & GT_DELTA_THETA) && _finite(aGreeks.dDeltaTheta))
//					m_dThetaDelta = aGreeks.dDeltaTheta;
//				if((aGreeks.nMask & GT_GAMMA_THETA) && _finite(aGreeks.dGammaTheta))
//					m_dThetaGamma = aGreeks.dGammaTheta;
//			//}
//		}
//
//		// clear values in shares
//		__MmRvPosAtom::ClearValuesInShares();
//
//		// calc values in shares
//		EtsReplacePriceStatusEnum enPriceStatusBid = enRpsNone;
//		DOUBLE dOptPriceBid = spOptPriceProfile->GetOptPriceBidForPnL(m_dPriceBid, m_dPriceAsk, m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_dPriceTheo, &enPriceStatusBid);
//
//		EtsReplacePriceStatusEnum enPriceStatusAsk = enRpsNone;
//		DOUBLE dOptPriceAsk = spOptPriceProfile->GetOptPriceAskForPnL(m_dPriceBid, m_dPriceAsk, m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_dPriceTheo, &enPriceStatusAsk);
//
//		enPriceStatusMid = enRpsNone;
//		dOptPriceMid = spOptPriceProfile->GetOptPriceMid(m_dPriceBid, m_dPriceAsk, m_dPriceLast, enPriceRoundingRule, bUseTheoVolatility, m_dPriceTheo, &enPriceStatusMid);
//
//		m_enReplacePriceStatus = static_cast<EtsReplacePriceStatusEnum>(enPriceStatusMid | enPriceStatusBid | enPriceStatusAsk);
//
//		// pnl
//		_CalcPnlMtm(bIsPnlLTD, dOptPriceBid, dOptPriceAsk, spOptPriceProfile->GetBadOptSinglePriceRule() == enObsprReplaceWithZero);
//		_CalcPnlTheo(bIsPnlLTD);
//
//		// delta
//		if(m_dDelta > BAD_DOUBLE_VALUE)
//			m_dDeltaInShares = m_dDelta * m_nQtyInShares;
//
//		// gamma
//		if(m_dGamma > BAD_DOUBLE_VALUE)
//		{
//			m_dGammaInShares = m_dGamma * m_nQtyInShares;
//
//			if(dUndMidPrice > DBL_EPSILON)
//				m_dGammaInSharesPerc = m_dGamma * m_nQtyInShares * dUndMidPrice / 100.;
//			else if(dFutMidPrice > DBL_EPSILON)
//				m_dGammaInSharesPerc = m_dGamma * m_nQtyInShares * dFutMidPrice / 100.;
//
//			m_dNetGamma = m_dGamma * m_nQtyInShares   / 100.;
//			if(dUndMidPrice > DBL_EPSILON)
//					m_dNetGamma = m_dGamma * m_nQtyInShares  * dUndMidPrice * dUndMidPrice / 100.;
//			else if(dFutMidPrice > DBL_EPSILON)
//					m_dNetGamma = m_dGamma * m_nQtyInShares  * dFutMidPrice * dFutMidPrice / 100.;
//
//		}
//
//		// other theos
//		if(m_dVega > BAD_DOUBLE_VALUE)
//		{
//			m_dVegaInShares = m_dVega * m_nQtyInShares;
//			m_dWtdVega = m_dVegaInShares * m_dVegaWeight;
//		}
//
//		if(m_dTheta > BAD_DOUBLE_VALUE)
//			m_dThetaInShares = m_dTheta * m_nQtyInShares;
//
//		if(m_dRho > BAD_DOUBLE_VALUE)
//			m_dRhoInShares = m_dRho * m_nQtyInShares;
//
//		if(m_dVegaDelta > BAD_DOUBLE_VALUE)
//			m_dVegaDeltaInShares = m_dVegaDelta * m_nQtyInShares;
//
//		if(m_dVegaGamma > BAD_DOUBLE_VALUE && dUndMidPrice > DBL_EPSILON)
//			m_dVegaGammaInShares = m_dVegaGamma * m_nQtyInShares * dUndMidPrice / 100.;
//		else if(m_dVegaGamma > BAD_DOUBLE_VALUE && dFutMidPrice > DBL_EPSILON)
//			m_dVegaGammaInShares = m_dVegaGamma * m_nQtyInShares * dFutMidPrice / 100.;
//
//		if(m_dThetaDelta > BAD_DOUBLE_VALUE)
//			m_dThetaDeltaInShares = m_dThetaDelta * m_nQtyInShares;
//
//		if(m_dThetaGamma > BAD_DOUBLE_VALUE && dUndMidPrice > DBL_EPSILON)
//			m_dThetaGammaInShares = m_dThetaGamma * m_nQtyInShares * dUndMidPrice / 100.;
//		else if(m_dThetaGamma > BAD_DOUBLE_VALUE && dFutMidPrice > DBL_EPSILON)
//			m_dThetaGammaInShares = m_dThetaGamma * m_nQtyInShares * dFutMidPrice / 100.;
//
//		if(dUndMidPrice > DBL_EPSILON && dOptPriceMid > DBL_EPSILON)
//		{
//			if(m_enOptType == enOtCall)
//			{
//				if(m_dStrike >= dUndMidPrice)
//					m_dTimeValue = dOptPriceMid;
//				else
//					m_dTimeValue = max(0, dOptPriceMid - (dUndMidPrice-m_dStrike));
//			}
//			else
//			{
//				if(m_dStrike <= dUndMidPrice)
//					m_dTimeValue = dOptPriceMid;
//				else
//					m_dTimeValue = max(0, dOptPriceMid- (m_dStrike-dUndMidPrice)) ;
//			}
//
////			m_dTimeValue = dOptPriceMid - (m_enOptType == enOtCall
////							? (dFutMidPrice - m_dStrike > DBL_EPSILON ? dFutMidPrice - m_dStrike : 0.)
////							: (m_dStrike - dFutMidPrice > DBL_EPSILON ? m_dStrike - dFutMidPrice : 0.));
//		}
//		else if(dFutMidPrice > DBL_EPSILON && dOptPriceMid > DBL_EPSILON)
//		{
//			if(m_enOptType == enOtCall)
//			{
//				if(m_dStrike >= dFutMidPrice)
//					m_dTimeValue = dOptPriceMid;
//				else
//					m_dTimeValue = max(0, dOptPriceMid - (dFutMidPrice-m_dStrike));
//			}
//			else
//			{
//				if(m_dStrike <= dFutMidPrice)
//					m_dTimeValue = dOptPriceMid;
//				else
//					m_dTimeValue = max(0, dOptPriceMid- (m_dStrike-dFutMidPrice)) ;
//			}
//
////			m_dTimeValue = dOptPriceMid - (m_enOptType == enOtCall
////							? (dFutMidPrice - m_dStrike > DBL_EPSILON ? dFutMidPrice - m_dStrike : 0.)
////							: (m_dStrike - dFutMidPrice > DBL_EPSILON ? m_dStrike - dFutMidPrice : 0.));
//		}
//
//		if(m_dNetGamma > BAD_DOUBLE_VALUE)
//		{
//			m_dNetGamma = m_dGamma * m_nQtyInShares  / 100.;
//			if(dUndMidPrice > DBL_EPSILON)
//				m_dNetGamma = m_dGamma * m_nQtyInShares  * dUndMidPrice * dUndMidPrice / 100.;
//		}
//	}
//	catch(const _com_error& e)
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvPosAtom, e.Error());
//	}
//
//	return S_OK;
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//void CMmRvPosAtom::_CalcPnlMtm(VARIANT_BOOL bIsPnlLTD, DOUBLE dPriceBid, DOUBLE dPriceAsk, bool ReplaceWithZero)
//{
//	m_dPnlMtm = BAD_DOUBLE_VALUE;
//
//	if(bIsPnlLTD)
//	{
//		if(m_nQtyLTDBuy > BAD_LONG_VALUE)
//		{
//			if((dPriceAsk >= 0 || dPriceBid >= 0 || ReplaceWithZero ) && m_dPosLTDBuy > BAD_DOUBLE_VALUE)
//				m_dPnlMtm = dPriceBid * m_nQtyLTDBuy - m_dPosLTDBuy;
//			else
//				return;
//		}
//			
//		if(m_nQtyLTDSell > BAD_LONG_VALUE)
//		{
//			if((dPriceAsk >= 0 || dPriceBid >= 0|| ReplaceWithZero ) && m_dPosLTDSell > BAD_DOUBLE_VALUE)
//			{
//				if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
//				m_dPnlMtm += dPriceAsk * m_nQtyLTDSell - m_dPosLTDSell;
//			}
//			else
//				return;
//		}
//	}
//	else
//	{
//		if(m_nQtyDailyPrevDateBuy > BAD_LONG_VALUE)
//		{
//			if((dPriceAsk >= 0 || dPriceBid >= 0 || ReplaceWithZero ) && m_dPosDailyPrevDateBuy > BAD_DOUBLE_VALUE)
//				m_dPnlMtm = dPriceBid * m_nQtyDailyPrevDateBuy - m_dPosDailyPrevDateBuy;
//			else
//				return;
//		}
//
//		if(m_nQtyDailyPrevDateSell > BAD_LONG_VALUE)
//		{
//			if((dPriceAsk > BAD_DOUBLE_VALUE || dPriceBid >=0 || ReplaceWithZero ) && m_dPosDailyPrevDateSell > BAD_DOUBLE_VALUE)
//			{
//				if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
//				m_dPnlMtm += dPriceAsk * m_nQtyDailyPrevDateSell - m_dPosDailyPrevDateSell;
//			}
//			else
//				return;
//		}
//
//		if(m_nQtyDailyTodayBuy > BAD_LONG_VALUE)
//		{
//			if( (dPriceBid > BAD_DOUBLE_VALUE || dPriceAsk > BAD_DOUBLE_VALUE || ReplaceWithZero ) && m_dPosDailyTodayBuy > BAD_DOUBLE_VALUE)
//			{
//				if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
//				m_dPnlMtm += dPriceBid * m_nQtyDailyTodayBuy - m_dPosDailyTodayBuy;
//			}
//			else
//				return;
//		}
//
//		if(m_nQtyDailyTodaySell > BAD_LONG_VALUE)
//		{
//			if((dPriceBid > BAD_DOUBLE_VALUE || dPriceAsk > BAD_DOUBLE_VALUE || ReplaceWithZero ) && m_dPosDailyTodaySell > BAD_DOUBLE_VALUE)
//			{
//				if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
//				m_dPnlMtm += dPriceAsk * m_nQtyDailyTodaySell - m_dPosDailyTodaySell;
//			}
//			else
//				return;
//		}
//	}
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//void CMmRvPosAtom::_CalcPnlTheo(VARIANT_BOOL bIsPnlLTD)
//{
//	m_dPnlTheo = BAD_DOUBLE_VALUE;
//
//	if(m_dPriceTheo >= 0/*DBL_EPSILON*/)
//	{
//		if(bIsPnlLTD)
//		{
//			if(m_nQtyLTDBuy > BAD_LONG_VALUE)
//			{
//				if(m_dPosLTDBuy > BAD_DOUBLE_VALUE)
//					m_dPnlTheo = m_dPriceTheo * m_nQtyLTDBuy - m_dPosLTDBuy;
//				else
//					return;
//			}
//				
//			if(m_nQtyLTDSell > BAD_LONG_VALUE)
//			{
//				if(m_dPosLTDSell > BAD_DOUBLE_VALUE)
//				{
//					if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
//					m_dPnlTheo += m_dPriceTheo * m_nQtyLTDSell - m_dPosLTDSell;
//				}
//				else
//					return;
//			}
//		}
//		else
//		{
//			if(m_nQtyDailyPrevDateBuy > BAD_LONG_VALUE)
//			{
//				if(m_dPosDailyPrevDateBuy > BAD_DOUBLE_VALUE)
//					m_dPnlTheo = m_dPriceTheo * m_nQtyDailyPrevDateBuy - m_dPosDailyPrevDateBuy;
//				else
//					return;
//			}
//
//			if(m_nQtyDailyPrevDateSell > BAD_LONG_VALUE)
//			{
//				if(m_dPosDailyPrevDateSell > BAD_DOUBLE_VALUE)
//				{
//					if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
//					m_dPnlTheo += m_dPriceTheo * m_nQtyDailyPrevDateSell - m_dPosDailyPrevDateSell;
//				}
//				else
//					return;
//			}
//
//			if(m_nQtyDailyTodayBuy > BAD_LONG_VALUE)
//			{
//				if(m_dPosDailyTodayBuy > BAD_DOUBLE_VALUE)
//				{
//					if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
//					m_dPnlTheo += m_dPriceTheo * m_nQtyDailyTodayBuy - m_dPosDailyTodayBuy;
//				}
//				else
//					return;
//			}
//
//			if(m_nQtyDailyTodaySell > BAD_LONG_VALUE)
//			{
//				if(m_dPosDailyTodaySell > BAD_DOUBLE_VALUE)
//				{
//					if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
//					m_dPnlTheo += m_dPriceTheo * m_nQtyDailyTodaySell - m_dPosDailyTodaySell;
//				}
//				else
//					return;
//			}
//		}
//	}
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//void CMmRvPosAtom::_GetBasketIndexDividends(IIndexAtomPtr spBasketIndex, REGULAR_DIVIDENDS* pDivs, LONG nMaxCount) throw()
//{
//	ATLASSERT(spBasketIndex != NULL);
//	EtsRegularDividend aDiv;
//
//	for(LONG i = 0; i < nMaxCount; i++)
//	{
//		aDiv = spBasketIndex->BasketDiv[i];
//		pDivs[i].nLastDivDate = static_cast<LONG>(aDiv.LastDate);
//		pDivs[i].nFrequency = aDiv.Freq;
//		pDivs[i].dAmount = aDiv.Amt;
//	}
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//void CMmRvPosAtom::_GetSyntheticRootBasketDividends(ISynthRootAtomPtr spSynthRoot, REGULAR_DIVIDENDS* pDivs, LONG nMaxCount) throw()
//{
//	ATLASSERT(spSynthRoot != NULL);
//	EtsRegularDividend aDiv;
//
//	for(LONG i = 0; i < nMaxCount; i++)
//	{
//		aDiv = spSynthRoot->BasketDiv[i];
//		pDivs[i].nLastDivDate = static_cast<LONG>(aDiv.LastDate);
//		pDivs[i].nFrequency = aDiv.Freq;
//		pDivs[i].dAmount = aDiv.Amt;
//	}
//}
//
//STDMETHODIMP CMmRvPosAtom::AddTrade(IMmTradeInfoAtom* pTrade, IMmRvUndAtom* pUnd)
//{
//	long nQty = 0;
//	long nQtyInShares = 0;
//	HRESULT hr = S_OK;
//	IMmTradeInfoAtomPtr spTrade(pTrade);
//
//	try
//	{
//		if(spTrade!=NULL)
//		{
//			bool bIsBuy  = spTrade->IsBuy!=VARIANT_FALSE?true:false;
//			nQty		 = spTrade->Quantity * (bIsBuy?1:-1);
//            nQtyInShares = nQty * m_nLotSize;
//
//			if(bIsBuy)
//			{
//				if (m_nQtyLTDBuy == BAD_LONG_VALUE)
//					m_nQtyLTDBuy = 0 ;
//
//				m_nQtyLTDBuy += nQtyInShares;
//				if(spTrade->IsPosition)
//				{
//					if (m_dPriceClose >= DBL_EPSILON )
//					{
//						if(m_dPosLTDBuy == BAD_DOUBLE_VALUE ) 
//							m_dPosLTDBuy = 0;
//                        
//						m_dPosLTDBuy += (m_dPriceClose * nQtyInShares);
//					}
//				}else
//				{
//					if (m_dPosLTDBuy == BAD_DOUBLE_VALUE)
//						m_dPosLTDBuy = 0;
//
//					m_dPosLTDBuy += (spTrade->Price * nQtyInShares);
//				}
//		    
//				if( spTrade->TradeDate < vt_date::GetCurrentDate(true))
//				{
//					if (m_nQtyDailyPrevDateBuy == BAD_LONG_VALUE) 
//						m_nQtyDailyPrevDateBuy = 0;
//
//					m_nQtyDailyPrevDateBuy +=  nQtyInShares;
//
//					if (m_dPriceClose >= DBL_EPSILON) 
//					{
//						if(m_dPosDailyPrevDateBuy == BAD_DOUBLE_VALUE) 
//							m_dPosDailyPrevDateBuy = 0;
//							m_dPosDailyPrevDateBuy +=  (m_dPriceClose * nQtyInShares);
//					}
//					else
//						if(!spTrade->IsPosition)
//						{
//							if(m_dPosDailyPrevDateBuy == BAD_DOUBLE_VALUE) m_dPosDailyPrevDateBuy = 0;
//                            
//							m_dPosDailyPrevDateBuy += (spTrade->Price * nQtyInShares);
//						}
//				}else
//				{
//					if(m_nQtyDailyTodayBuy == BAD_LONG_VALUE) m_nQtyDailyTodayBuy = 0;
//
//					m_nQtyDailyTodayBuy += nQtyInShares;
//					if(spTrade->IsPosition) 
//					{
//						if(m_dPriceClose >= DBL_EPSILON)
//						{
//							if (m_dPosDailyTodayBuy == BAD_DOUBLE_VALUE) m_dPosDailyTodayBuy = 0;
//							m_dPosDailyTodayBuy += (m_dPriceClose * nQtyInShares);
//						}
//					}
//					else
//					{
//						if (m_dPosDailyTodayBuy == BAD_DOUBLE_VALUE) m_dPosDailyTodayBuy = 0;
//						m_dPosDailyTodayBuy += (spTrade->Price * nQtyInShares);
//					}
//				}
//			}
//			else
//			{
//				if(m_nQtyLTDSell == BAD_LONG_VALUE)
//					m_nQtyLTDSell = 0;
//				m_nQtyLTDSell += nQtyInShares;
//
//				if (spTrade->IsPosition) 
//				{
//					if(m_dPriceClose >= DBL_EPSILON)
//					{
//						if(m_dPosLTDSell == BAD_DOUBLE_VALUE) 
//							m_dPosLTDSell = 0;
//						m_dPosLTDSell += (m_dPriceClose * nQtyInShares);
//					}
//				}
//				else
//				{
//					if (m_dPosLTDSell == BAD_DOUBLE_VALUE) 
//						m_dPosLTDSell = 0;
//					m_dPosLTDSell += (spTrade->Price * nQtyInShares);
//				}
//		    
//				if (spTrade->TradeDate < vt_date::GetCurrentDate(true))
//				{
//					if (m_nQtyDailyPrevDateSell == BAD_LONG_VALUE) 
//						m_nQtyDailyPrevDateSell = 0; 
//					m_nQtyDailyPrevDateSell += nQtyInShares;
//					if (m_dPriceClose >= DBL_EPSILON)
//					{
//						if (m_dPosDailyPrevDateSell == BAD_DOUBLE_VALUE) m_dPosDailyPrevDateSell = 0;
//						m_dPosDailyPrevDateSell +=  (m_dPriceClose * nQtyInShares);
//					}
//					else if(!spTrade->IsPosition)
//					{
//						if (m_dPosDailyPrevDateSell == BAD_DOUBLE_VALUE) m_dPosDailyPrevDateSell = 0;
//						m_dPosDailyPrevDateSell += (spTrade->Price * nQtyInShares);
//					}
//				}
//				else
//				{
//					if(m_nQtyDailyTodaySell == BAD_LONG_VALUE) m_nQtyDailyTodaySell = 0;
//					m_nQtyDailyTodaySell += nQtyInShares;
//					if (spTrade->IsPosition)
//					{
//						if (m_dPriceClose >= DBL_EPSILON) 
//						{
//							if(m_dPosDailyTodaySell == BAD_DOUBLE_VALUE) 
//								m_dPosDailyTodaySell = 0;
//                            
//							m_dPosDailyTodaySell += (m_dPriceClose * nQtyInShares);
//						}
//					}
//					else
//					{
//						if (m_dPosDailyTodaySell == BAD_DOUBLE_VALUE) m_dPosDailyTodaySell = 0;
//						m_dPosDailyTodaySell += (spTrade->Price * nQtyInShares);
//					}
//				}
//			}
//		    
//			m_nQty +=  nQty;
//			m_nQtyInShares += nQtyInShares;
//
//			if(pUnd != NULL)
//			{
//				if(enCtOption==m_enContractType || enCtFutOption ==m_enContractType)
//				{
//					long lUndOptQty = BAD_LONG_VALUE;
//					pUnd->get_OptQty(&lUndOptQty);
//
//					if (lUndOptQty == BAD_LONG_VALUE) 
//					{
//						lUndOptQty = 0L;
//						pUnd->put_OptQty(0L);
//					}
//					pUnd->put_OptQty(lUndOptQty + nQty);
//				}
//				else 
//				if (m_enContractType == enCtFuture)
//				{
//					long lUndFutQty = BAD_LONG_VALUE;
//					pUnd->get_FutQty(&lUndFutQty);
//
//					if(lUndFutQty == BAD_LONG_VALUE) 
//					{
//						lUndFutQty = 0L;
//						pUnd->put_FutQty(0L);
//					}
//					pUnd->put_FutQty(lUndFutQty + nQty);
//
//					long lUndQty = BAD_LONG_VALUE;
//					pUnd->get_Qty(&lUndQty);
//
//					if(lUndQty == BAD_LONG_VALUE){
//						pUnd->put_Qty(0);
//						lUndQty = 0;
//					}
//					pUnd->put_Qty(lUndQty+ nQtyInShares);
//
//				}
//				else
//				{
//					long lUndQty = BAD_LONG_VALUE;
//					pUnd->get_Qty(&lUndQty);
//
//					if(lUndQty == BAD_LONG_VALUE){
//						pUnd->put_Qty(0);
//						lUndQty = 0;
//					}
//					pUnd->put_Qty(lUndQty+ nQtyInShares);
//				}
//			}
//
//		}
//		else
//			hr = E_POINTER;
//	}
//	catch (_com_error& e)
//	{
//		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvPosAtom, e.Error());
//	}
//	catch (...) 
//	{
//		hr = Error((LPCOLESTR)_bstr_t(L"Unknown error while adding trade to position"), IID_IMmRvPosAtom, E_FAIL);
//	}
//
//	return hr;
//}
