// MmTradeInfoColl.cpp : Implementation of CMmTradeInfoColl

#include "stdafx.h"
#include "MmTradeInfoColl.h"
#include "MmTradeInfoAtom.h"

// CMmTradeInfoColl

STDMETHODIMP CMmTradeInfoColl::Add(LONG Key, DATE SortKey, IMmTradeInfoAtom* Value, IMmTradeInfoAtom** pRetVal)
{
	__CHECK_POINTER(pRetVal);

	try
	{

		if(m_coll.find(Key) != m_coll.end())
		{
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Trade with the same key already exists."));
		}

		if(!Value)
		{
			CComObject<CMmTradeInfoAtom>* pNewVal;
			__CHECK_HRESULT(CComObject<CMmTradeInfoAtom>::CreateInstance(&pNewVal), _T("Failed to add trade."));
			pNewVal->AddRef();
			if(FAILED(IMmTradeInfoCollImpl::Add(Key, SortKey, pNewVal)))
			{
				pNewVal->Release();
				EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Failed to add trade."));
			}
			*pRetVal = pNewVal;
		}
		else
		{
			__CHECK_HRESULT(IMmTradeInfoCollImpl::Add(Key, SortKey, Value), _T("Failed to add trade."));
			Value->AddRef();
			*pRetVal = Value;
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoColl, e.Error());
	}

	return S_OK;
}

STDMETHODIMP CMmTradeInfoColl::Clone(IMmTradeInfoColl** pSrcColl)
{
	HRESULT hr = S_OK;
	try
	{
		__CHECK_POINTER(pSrcColl);
		CComObject<CMmTradeInfoColl>* pColl = NULL;
		__CHECK_HRESULT3(CComObject<CMmTradeInfoColl>::CreateInstance(&pColl));
		if(pColl)
		{
			CComQIPtr<IMmTradeInfoColl> spCollection(pColl);
			CMmTradeInfoColl::EnumCollType::iterator itrX    = m_coll.begin();
			CMmTradeInfoColl::EnumCollType::iterator itrXend = m_coll.end();


			for(; itrX != itrXend; ++itrX)
			{
				IMmTradeInfoAtomPtr pTradeInfoAtom = itrX->second;
				LONG lId = 0;
				DATE dt  = 0.;
				IMmTradeInfoAtomPtr pRet;
				pTradeInfoAtom->get_TradeID(&lId);
				pTradeInfoAtom->get_TradeDate(&dt);
				spCollection->Add(lId, dt, pTradeInfoAtom,&pRet);
			}
			hr = spCollection.CopyTo(pSrcColl);
		}

	}
	catch(const _com_error& e)
	{
		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoColl, e.Error());
	}
	catch(...)
	{
		HRESULT _hr = HRESULT_FROM_WIN32(::GetLastError());
		if(SUCCEEDED(_hr)) _hr = E_FAIL;
		hr =  Error((PTCHAR)"System Error", IID_IMmTradeInfoColl, _hr);
	}

	return hr;
}

bool CMmTradeInfoColl::IsToday( IMmTradeInfoAtomPtr pTradeInfoAtom , bool bAdnSimulated ) 
{

	if ( !bAdnSimulated  )
	{	
		EtsTradeStatusEnum enStatus;
		pTradeInfoAtom->get_Status(&enStatus);
		if(enTrsSimulated == enStatus)
			return false;

		VARIANT_BOOL bIsPosition = VARIANT_FALSE;
		pTradeInfoAtom->get_IsPosition(&bIsPosition);
		if(bIsPosition == VARIANT_TRUE)
			return false;
	}
	DATE dtTrade;
	pTradeInfoAtom->get_TradeDate(&dtTrade);
	if(static_cast<int>(dtTrade) != static_cast<int>((DATE)vt_date::GetCurrentDate()))
		return false;

	return true ;
}

bool CMmTradeInfoColl::IsSimulated (IMmTradeInfoAtomPtr pTradeInfoAtom ) 
{
	EtsTradeStatusEnum enStatus;
	pTradeInfoAtom->get_Status(&enStatus);

	if(enTrsSimulated != enStatus)
		return false ;

	return true ;
}

bool CMmTradeInfoColl::IsOpenPos (IMmTradeInfoAtomPtr pTradeInfoAtom , bool bAdnSimulated ) 
{
	if ( !bAdnSimulated  )
	{	
		EtsTradeStatusEnum enStatus;
		pTradeInfoAtom->get_Status(&enStatus);
		if(enTrsSimulated == enStatus)
			return false ;
	}

	bool bReturn = false ;
	VARIANT_BOOL bIsPosition = VARIANT_FALSE;
	pTradeInfoAtom->get_IsPosition(&bIsPosition);
	if(bIsPosition == VARIANT_FALSE)
		bReturn = true;

	if ( bReturn )
	{	
		DATE dtTrade;
		pTradeInfoAtom->get_TradeDate(&dtTrade);
		if(static_cast<int>(dtTrade) == static_cast<int>((DATE)vt_date::GetCurrentDate()))
			return false ;
	}

	return true ;
}

STDMETHODIMP CMmTradeInfoColl::get_FilterTrades(IEtsFilterData* pFilter,
												IEtsUndGroupColl* pGroupCol,
												VARIANT_BOOL bActual,
												VARIANT_BOOL bSkipFutContracts,
												VARIANT_BOOL bFutWithDerivative,
												IMmTradeInfoColl** pVal)
{
	HRESULT hr = S_OK;
	if(!pVal || !pFilter)
		return E_POINTER;
	try
	{
		IEtsFilterDataPtr   spFilter(pFilter);
		*pVal = NULL;

		long lFilterUndID			= spFilter->Data[0/*RFC_SYMBOL*/];
		long lFilterTypeID			= spFilter->Data[1/*RFC_TRADES*/];
		long lFilterGroupID			= spFilter->Data[2/*RFC_GROUPS*/];
		long lFilterTraderGroupID	= spFilter->Data[3/*RFC_TRADER_GROUP*/]; 
		long lFilterTraderID		= spFilter->Data[4/*RFC_TRADER*/];
		long lFilterStrategyID		= spFilter->Data[5/*RFC_STRATEGY*/];

		CComObject<CMmTradeInfoColl>* pColl = NULL;
		__CHECK_HRESULT3(CComObject<CMmTradeInfoColl>::CreateInstance(&pColl));
		if(pColl)
		{
			CComQIPtr<IMmTradeInfoColl> spCollection(pColl);
			CMmTradeInfoColl::EnumCollType::iterator itrX    = m_coll.begin();
			CMmTradeInfoColl::EnumCollType::iterator itrXend = m_coll.end();
			bool bBreak = false;

			for(; itrX != itrXend; ++itrX)
			{
				if(bBreak)
					break;

				IMmTradeInfoAtomPtr pTradeInfoAtom = itrX->second;

				EtsContractTypeEnum enContractType;
				pTradeInfoAtom->get_ContractType(&enContractType);
				if ((enContractType == enCtFuture || enContractType == enCtFutOption) && bSkipFutContracts == VARIANT_TRUE)	continue;

				if(bActual!=VARIANT_FALSE)
				{
					switch(enContractType)
					{
					case enCtFuture: 
						{
							
							IEtsFutAtomPtr				spFut;
							hr = pTradeInfoAtom->get_Fut(&spFut);
							if(!spFut || FAILED(hr)) continue;

							DATE dtExpiry =0.;
							spFut->get_MaturityDate(&dtExpiry);
							if(dtExpiry < vt_date::GetCurrentDate(true))
								continue;
							
						}break;
					case enCtFutOption:
						{
							
							IEtsFutOptAtomPtr			spFutOpt;

							hr = pTradeInfoAtom->get_FutOpt(&spFutOpt);
							if(!spFutOpt || FAILED(hr)) continue;

							DATE dtExpiry =0.;
							spFutOpt->get_Expiry(&dtExpiry);
							if(dtExpiry < vt_date::GetCurrentDate(true))
								continue;
							
						}break;
					case enCtOption:
						{
							IEtsOptAtomPtr pOptAtom;
							hr = pTradeInfoAtom->get_Opt(&pOptAtom);
							if(FAILED(hr))
								continue;
							DATE dtExpiry =0.;
							pOptAtom->get_Expiry(&dtExpiry);
							if(dtExpiry < vt_date::GetCurrentDate(true))
								continue;

						}break;
					}
				}   
				if( lFilterUndID > 0 )
				{

					LONG lUndId = 0;
					
					if(bFutWithDerivative == VARIANT_TRUE) 
					{
						//in this case we will load only future, and options on it which has a positions
						if(enContractType == enCtFuture)
						{
							IEtsFutAtomPtr				spFut;
							hr = pTradeInfoAtom->get_Fut(&spFut);
							if(!spFut || FAILED(hr)) continue;
							spFut->get_ID(&lUndId);
							if(lFilterUndID != lUndId) continue;
						}
						else if(enContractType == enCtFutOption)
						{
							IEtsFutOptAtomPtr			spFutOpt;
							hr = pTradeInfoAtom->get_FutOpt(&spFutOpt);
							if(!spFutOpt || FAILED(hr)) continue;
							spFutOpt->get_FutID(&lUndId);
							if(lFilterUndID != lUndId) continue;
						}
						else
							continue;
					}
					else	//load all trades/positions
					{
						pTradeInfoAtom->get_UndID(&lUndId);
						if(lFilterUndID != lUndId)		continue;
					}
				}
				if( lFilterGroupID > 0 )
				{
					IUndCollPtr pGroupUndColl;
					if(pGroupUndColl==NULL)
					{
						IEtsUndGroupAtomPtr pGroupAtom;
						if(!pGroupCol)
							continue;
						pGroupCol->get_Item(lFilterGroupID, &pGroupAtom);
						if(pGroupAtom == NULL)
						{
							bBreak = true;
							continue;
						}
						pGroupAtom->get_Und(&pGroupUndColl);
					}

					LONG lUndId = 0;
					IUndAtomPtr spUnd;
					pTradeInfoAtom->get_UndID(&lUndId);

					pGroupUndColl->get_Item(lUndId, &spUnd);
					if(spUnd == NULL)
						continue;

				}
				if(lFilterTraderID  >0 )
				{
					long lTraderId = 0;
					IEtsTraderAtomPtr spTrader; 
					pTradeInfoAtom->get_Trader(&spTrader);
					spTrader->get_ID(&lTraderId);
					if(lTraderId != lFilterTraderID)
						continue;

				}
				if(lFilterTraderGroupID > 0)
				{
					long lTraderGroupID = 0;
					IEtsTraderAtomPtr spTrader; 
					pTradeInfoAtom->get_Trader(&spTrader);
					spTrader->get_GroupID(&lTraderGroupID); 
					if(lTraderGroupID != lFilterTraderGroupID)
						continue;
				}
				if(lFilterStrategyID != 0)
				{
					LONG lStrategyId = 0;
					pTradeInfoAtom->get_StrategyID(&lStrategyId);
					if(lStrategyId != (lFilterStrategyID  > 0? lFilterStrategyID: 0))
						continue;
				}

				if(lFilterTypeID >= 0)
				{
					switch(lFilterTypeID)
					{
					case 0:
						break;
					case 1: // Today's
						{
							if ( !IsToday( pTradeInfoAtom ) )
								continue ;
						}break;
					case 2: // OpenPos
						{
							if ( !IsOpenPos( pTradeInfoAtom ) )
								continue ;
						}break;
					case 3: // NetPos
						{
							EtsTradeStatusEnum enStatus;
							pTradeInfoAtom->get_Status(&enStatus);
							if(enTrsSimulated == enStatus)
								continue;

						}  break;

					case 4: // ' Simulated
						{
							if ( !IsSimulated( pTradeInfoAtom ))
								continue ;
						}   break;
					case 5: // Today's & Sim
						{
							if ( !IsToday( pTradeInfoAtom , true )  )
								continue ;
						}break;
					case 6: // OpenPos & Sim
						{
							DATE dtTrade;
							pTradeInfoAtom->get_TradeDate(&dtTrade);
							if(static_cast<int>(dtTrade) == static_cast<int>((DATE)vt_date::GetCurrentDate()))
								continue;

						}break;
					case 7: // Manual
						{
							EtsTradeStatusEnum enStatus;
							pTradeInfoAtom->get_Status(&enStatus);

							if(enTrsManual != enStatus)
								continue;

						} break;
					case 8: //Manual & Sim
						{
							EtsTradeStatusEnum enStatus;
							pTradeInfoAtom->get_Status(&enStatus);
							if(enTrsManual == enStatus || enTrsSimulated == enStatus)
								break;
							continue;

						}break;
					}
				}
				LONG lId = 0;
				DATE dt  = 0.;
				IMmTradeInfoAtomPtr pRet;
				pTradeInfoAtom->get_TradeID(&lId);
				pTradeInfoAtom->get_TradeDate(&dt);
				spCollection->Add(lId, dt, pTradeInfoAtom,&pRet);
			}
			hr = spCollection.CopyTo(pVal);
		}
	}

	catch (_com_error& e) 
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), __uuidof(IMmTradeInfoColl), e.Error());
	}
	catch(...)
	{
		HRESULT _hr = HRESULT_FROM_WIN32(::GetLastError());
		if(SUCCEEDED(_hr)) _hr = E_FAIL;
		hr =  Error((PTCHAR)"System Error", IID_IMmTradeInfoColl, _hr);
	}
	return hr;
}

void CMmTradeInfoColl::FilterData(/*long* spFilterData->Data,*/IEtsFilterDataPtr spFilterData, IEtsMainPtr spMain, CTradeInfoViewData&  vecShow)
{
	vecShow.clear();
	CMmTradeInfoColl::EnumCollType::iterator itrX    = m_coll.begin();
	CMmTradeInfoColl::EnumCollType::iterator itrXend = m_coll.end();
	vecShow.reserve(m_coll.size());
	long lPosType, lUnd, lType,lGroup, lTrader, lStrategy, lTraderGroup;

	lPosType		= spFilterData->Data[TFC_POSTYPE];
	lUnd			= spFilterData->Data[TFC_UNDERLYING];
	lType			= spFilterData->Data[TFC_TYPE];
	lGroup		= spFilterData->Data[TFC_GROUP];
	lTrader		= spFilterData->Data[TFC_TRADER];
	lStrategy	= spFilterData->Data[TFC_STRATEGY];
	lTraderGroup = spFilterData->Data[TFC_TRADER_GROUP]; 

	for(; itrX != itrXend; ++itrX)
	{
		IMmTradeInfoAtomPtr spTradeInfoAtom = itrX->second;
		CMmTradeInfoAtom*  pTradeInfoAtom = static_cast<CMmTradeInfoAtom*>((IMmTradeInfoAtom*)spTradeInfoAtom);
		if(pTradeInfoAtom)
		{
			//if(!pTradeInfoAtom->m_bIsPosition)
			{
				bool bMatched	= false;
				//long nValue = spFilterData->Data[TFC_POSTYPE];

				bMatched = lPosType==2 || (lPosType == 0 && !pTradeInfoAtom->m_bIsPosition) || (lPosType == 1 && pTradeInfoAtom->m_bIsPosition);

				if(bMatched)
				{
					//lUnd		= spFilterData->Data[TFC_UNDERLYING];
					bMatched = (!lUnd || lUnd == pTradeInfoAtom->GetUndID());
				}

				if(bMatched)
				{
					//nValue = spFilterData->Data[TFC_TYPE];
					bMatched = (lType == 0);
					if(!bMatched)
					{
						switch(lType)
						{
						case 1: // Today's
							bMatched =  static_cast<long>(pTradeInfoAtom->m_dtTradeDate)== static_cast<long>((DATE)vt_date::GetCurrentDate(TRUE));
							break;
						case 2:	// ' Simulated
							bMatched = (pTradeInfoAtom->m_enStatus == enTrsSimulated);
							break;
						case 3: // Manual
							bMatched = (pTradeInfoAtom->m_enStatus == enTrsManual);
							break;
						}
					}
				}
				if(bMatched)
				{
					bMatched = (lTraderGroup == 0);
					if(!bMatched)
					{
						bMatched = (pTradeInfoAtom->m_spTrader->GroupID == lTraderGroup);

					}
				}

				if(bMatched)
				{
					//nValue = spFilterData->Data[TFC_GROUP];
					bMatched = (lGroup == 0);
					if(!bMatched)
					{
						long lFilterGroupID = lGroup;
						if( lFilterGroupID >0 )
						{
							if(spMain && spMain->UnderlyingGroup!=NULL)
							{
								IEtsUndGroupAtomPtr spGroupAtom;
								spMain->UnderlyingGroup->get_Item(lFilterGroupID, &spGroupAtom);
								if(spGroupAtom != NULL)
								{
									IUndCollPtr spGroupUndColl;
									spGroupAtom->get_Und(&spGroupUndColl);
									if(spGroupUndColl!=NULL)	
									{
										IUndAtomPtr spUnd;
										spGroupUndColl->get_Item(pTradeInfoAtom->GetUndID(), &spUnd);
										if(spUnd != NULL)
											bMatched = true;

									}
								}
							}
						}
					}
				}
				if(bMatched)
				{
					//nValue = spFilterData->Data[TFC_TRADER];
					bMatched = (lTrader == 0);
					if(!bMatched)
					{
						bMatched = (pTradeInfoAtom->m_spTrader->ID == lTrader);

					}
				}
				if(bMatched)
				{
					//nValue = spFilterData->Data[TFC_STRATEGY];
					bMatched = (lStrategy == 0);
					if ( lStrategy == -2 && !pTradeInfoAtom->m_spStrategy  )
						bMatched = true ;
					else if(!bMatched && pTradeInfoAtom->m_spStrategy )
					{
						bMatched = (pTradeInfoAtom->m_spStrategy->ID == (lStrategy > 0? lStrategy: 0));
					}
				}    
				if(bMatched)
					vecShow.insert(vecShow.end(),spTradeInfoAtom);
			}

		}   
	}
}

STDMETHODIMP CMmTradeInfoColl::ResetTradesPosition()
{
	if(!m_coll.size())
		return E_FAIL;
	else
		m_itCurrentPosition = m_coll.begin();
	return S_OK;

}
STDMETHODIMP CMmTradeInfoColl::MoveNextTrade(VARIANT_BOOL* bIsLast)
{
	if(!bIsLast)
		return E_POINTER;
	if(!m_coll.size())
		*bIsLast = VARIANT_TRUE;
	else
	{   
		m_itCurrentPosition++;
		if(m_itCurrentPosition == m_coll.end())
			*bIsLast = VARIANT_TRUE;
		else
			*bIsLast = VARIANT_FALSE;
	}
	return S_OK;

}
STDMETHODIMP CMmTradeInfoColl::get_TradeAtCurrentPosition(IMmTradeInfoAtom** pDest)
{
	if(!pDest)
		return E_POINTER;

	if(!m_coll.size() || m_itCurrentPosition == m_coll.end())
		return E_FAIL;
	else
	{
		*pDest = m_itCurrentPosition->second;
		(*pDest)->AddRef();
	}
	return S_OK;
}


STDMETHODIMP CMmTradeInfoColl::GetFirstTrade(IMmTradeInfoAtom** pDest)
{
	if ( !m_coll.empty() )
	{
		EnumCollType::iterator it = m_coll.begin() ;
		*pDest = it->second ;
	}
	return S_OK ;
}