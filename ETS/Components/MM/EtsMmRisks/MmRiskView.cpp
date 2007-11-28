// MmRiskView.cpp : Implementation of CMmRiskView

#include "stdafx.h"
#include "MmRiskView.h"
//#include "MmRvExpTotalAtom.h"
#include "MmRvUndAtom.h"
#include "MmRvAggregationData.h"
#include <stack>
#include <string>
#include <utility>

const static _bstr_t USD_KEY(L"0");
const static _bstr_t USD_SYMBOL(L"$");

// CMmRiskView
STDMETHODIMP CMmRiskView::raw_GetFieldCount (/*[out,retval]*/ long * pFields )
{
	if (pFields) {
		*pFields = m_lVisibleColumns + 1;
	}
	else
		return E_POINTER;

	return S_OK/*E_NOTIMPL*/;
}
STDMETHODIMP CMmRiskView::raw_GetRecordCount(/*[out,retval]*/ long * pRecords )
{
	if (pRecords) {
		*pRecords = (long) m_Rows.size();
	}
	else
		return E_POINTER;

	return S_OK/*E_NOTIMPL*/;
}

STDMETHODIMP CMmRiskView::raw_GetFieldName  (/*[in]*/ long Field, /*[out,retval]*/ BSTR * pFieldName )
{
	if (pFieldName) {
		*pFieldName = SysAllocString(L"");
	}
	else
		return E_POINTER;
	return S_OK;
}

STDMETHODIMP CMmRiskView::raw_GetData		 (/*[in]*/ long Field, /*[in]*/ long Record, /*[out,retval]*/ BSTR * pData )
{
	HRESULT hr = S_OK;

	*pData = NULL;
	long lFieldID = Field-1;
	try
	{
		if(Field > 0 && m_ColumnsEncoding[lFieldID]>=0 && static_cast<size_t>(Record) < m_Rows.size())
		{
			IMmRvRowDataPtr spAtom = m_Rows[Record];
			CMmRvRowData* pAtom = static_cast<CMmRvRowData*>(spAtom.GetInterfacePtr());

			_variant_t  vt; 
			if(pAtom->GetField(static_cast<RisksPosColumnEnum>(m_ColumnsEncoding[lFieldID]), vt, false))
			{
				if(vt.vt == VT_BSTR)
					*pData = SysAllocString(vt.bstrVal);
				else
				{
					_variant_t vtOut;
					vtOut.ChangeType(VT_BSTR, &vt);
					*pData = SysAllocString(vtOut.bstrVal);
				}
			}		
			else
				*pData = ::SysAllocString(L"Unknown");
		}
		if(!*pData)
			*pData = SysAllocString(L"Undefined");
	}
	catch (_com_error& err )
	{
		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(err), IID_IMmRiskView, err.Error());
	}
	return hr;

}

STDMETHODIMP CMmRiskView::raw_SetData(/*[in]*/ long Field,	/*[in]*/ long Record,/*[in]*/ BSTR newData )
{
	long lFieldID = Field-1;
	HRESULT hr = S_OK;
	try {
		long lColumnId = m_ColumnsEncoding[lFieldID];
		switch (lColumnId)
		{
			case RPC_ACTIVEPRC:
			{
				IMmRvRowDataPtr spAtom = m_Rows[Record];
				CMmRvRowData* pAtom = static_cast<CMmRvRowData*>(spAtom.GetInterfacePtr());
				_variant_t	vtVal = _bstr_t(newData);
				double dblValue = vtVal;
				if(dblValue > 0.)
				{
					if(pAtom->m_pPos) 
					{
						if (pAtom->m_pPos->m_enContractType == enCtStock)
						{
							if (pAtom->m_pUnd && pAtom->m_pUnd->m_bPriceByHead == VARIANT_FALSE)
							{
								pAtom->m_pPos->m_pQuote->m_pPrice->put_Active(dblValue);
								pAtom->m_pPos->m_pQuote->m_pPrice->put_IsUseManualActive(VARIANT_TRUE);
							}
						}
						else if (pAtom->m_pPos->m_enContractType == enCtOption ||pAtom->m_pPos->m_enContractType == enCtFutOption)
						{
							pAtom->m_pPos->m_pQuote->m_pPrice->put_Active(dblValue);
							pAtom->m_pPos->m_pQuote->m_pPrice->put_IsUseManualActive(VARIANT_TRUE);
						}
						else if (pAtom->m_pPos->m_enContractType == enCtFuture)
						{
							if (pAtom->m_pUnd && pAtom->m_pPos->m_spFut)
							{
									IMmRvPricePtr spFutPrice;
									pAtom->m_pPos->m_spFut->get_Price(&spFutPrice);

									if (pAtom->m_pUnd->m_spActiveFuture)
									{
										long	lActiveFutID = 0;
										pAtom->m_pUnd->m_spActiveFuture->get_ID(&lActiveFutID);
										
										long lFutID = 0;
										pAtom->m_pPos->m_spFut->get_ID(&lFutID);

										if (lFutID == lActiveFutID)
										{
											pAtom->m_pPos->m_pQuote->m_pPrice->put_Active(dblValue);
											pAtom->m_pPos->m_pQuote->m_pPrice->put_IsUseManualActive(VARIANT_TRUE);

											if (spFutPrice){
												spFutPrice->put_Active(dblValue);
												spFutPrice->put_IsUseManualActive(VARIANT_TRUE);
											}
										}
									}
									else
									{
										pAtom->m_pPos->m_pQuote->m_pPrice->put_Active(dblValue);
										pAtom->m_pPos->m_pQuote->m_pPrice->put_IsUseManualActive(VARIANT_TRUE);

										if (spFutPrice){
											spFutPrice->put_Active(dblValue);
											spFutPrice->put_IsUseManualActive(VARIANT_TRUE);
										}
									}
							}
						}
						else if (pAtom->m_pPos->m_enContractType == enCtIndex)
						{
							if (pAtom->m_pUnd && pAtom->m_pUnd->m_bPriceByHead == VARIANT_FALSE)
							{
								if (pAtom->m_pPos->m_spActiveFuture == NULL)
								{
									pAtom->m_pPos->m_pQuote->m_pPrice->put_Active(dblValue);
									pAtom->m_pPos->m_pQuote->m_pPrice->put_IsUseManualActive(VARIANT_TRUE);
								}
							}
						}
					}
					else 
					{
						if(pAtom->m_Type == RDT_UNDAGG) 
						{
							if (pAtom->m_pUnd->m_bPriceByHead == VARIANT_FALSE)
							{
								if (pAtom->m_pUnd->m_enContractType == enCtStock)
								{
									pAtom->m_pUnd->m_pPrice->put_Active(dblValue);
									pAtom->m_pUnd->m_pPrice->put_IsUseManualActive(VARIANT_TRUE);
								}
								else if (pAtom->m_pUnd->m_enContractType == enCtIndex)
								{
									if (pAtom->m_pUnd->m_spActiveFuture == NULL)
									{
										pAtom->m_pUnd->m_pPrice->put_Active(dblValue);
										pAtom->m_pUnd->m_pPrice->put_IsUseManualActive(VARIANT_TRUE);
									}
								}
							}
						}
						else 
						{
							if(pAtom->m_pAgg && CMmRvAggData::enFutAgg == pAtom->m_pAgg->Type_ && pAtom->m_pAgg->pFut_) 
							{
								if (pAtom->m_pAgg->pFut_->m_spUnd)
								{
									IMmRvFutAtomPtr spActivFuture;
									_CHK(pAtom->m_pAgg->pFut_->m_spUnd->get_ActiveFuture(&spActivFuture));

									if (spActivFuture){
										long	lActiveFutureID = 0;
										spActivFuture->get_ID(&lActiveFutureID);
										if (lActiveFutureID == pAtom->m_pAgg->pFut_->m_nID)
										{
											pAtom->m_pAgg->pFut_->m_pPrice->put_Active(dblValue);
											pAtom->m_pAgg->pFut_->m_pPrice->put_IsUseManualActive(VARIANT_TRUE);
										}
									}
									else
									{
										pAtom->m_pAgg->pFut_->m_pPrice->put_Active(dblValue);
										pAtom->m_pAgg->pFut_->m_pPrice->put_IsUseManualActive(VARIANT_TRUE);
									}
								}
							}
						}
					}
				}
			}break;

			case RPC_CLOSE:
			{
				IMmRvRowDataPtr spAtom = m_Rows[Record];
				CMmRvRowData* pAtom = static_cast<CMmRvRowData*>(spAtom.GetInterfacePtr());
				_variant_t	vtVal = _bstr_t(newData);
				double dblValue = vtVal;
				if(!(dblValue < 0.))
				{
					if(pAtom->m_pPos) 
						pAtom->m_pPos->m_pQuote->m_pPrice->put_Close(dblValue); // set close for position
					else 
						if(pAtom->m_Type == RDT_UNDAGG) 
							pAtom->m_pUnd->m_pPrice->put_Close(dblValue); // set close for underlying aggregation
						else 
							if(pAtom->m_pAgg && CMmRvAggData::enFutAgg == pAtom->m_pAgg->Type_ && pAtom->m_pAgg->pFut_) 
								pAtom->m_pAgg->pFut_->m_pPrice->put_Close(dblValue); // set close for aggregation that have a price
				}
			}break;
			case RPC_THEO_PRICE_CLOSE:
				{
					IMmRvRowDataPtr spAtom = m_Rows[Record];
					CMmRvRowData* pAtom = static_cast<CMmRvRowData*>(spAtom.GetInterfacePtr());
					_variant_t	vtVal = _bstr_t(newData);
					double dblValue = vtVal;
					if(!(dblValue < 0.))
					{
					
						if(pAtom->m_pPos)
							pAtom->m_pPos->m_pQuote->m_pPrice->put_TheoClose(dblValue); // set CloseTheo for position
					}
				}break;
			case RPC_BID:
				{
					IMmRvRowDataPtr spAtom = m_Rows[Record];
					CMmRvRowData* pAtom = static_cast<CMmRvRowData*>(spAtom.GetInterfacePtr());
					_variant_t	vtVal = _bstr_t(newData);
					double dblValue = vtVal;
					if(dblValue > 0.)
					{
						if(pAtom->m_pPos) 
							pAtom->m_pPos->m_pQuote->m_pPrice->put_Bid(dblValue);		 // set bid for position
						else 
							if(pAtom->m_Type == RDT_UNDAGG) 
								pAtom->m_pUnd->m_pPrice->put_Bid(dblValue);		   // set bid for underlying aggregation
							else 
								if(pAtom->m_pAgg && pAtom->m_pAgg->Type_ == CMmRvAggData::enFutAgg && pAtom->m_pAgg->pFut_)
									pAtom->m_pAgg->pFut_->m_pPrice->put_Bid(dblValue); // set bid for aggregation that have a price
					}
				}
				break;
			case RPC_ASK:
				{
					IMmRvRowDataPtr spAtom = m_Rows[Record];
					CMmRvRowData* pAtom = static_cast<CMmRvRowData*>(spAtom.GetInterfacePtr());
					_variant_t	vtVal = _bstr_t(newData);
					double dblValue = vtVal;
					if(dblValue > 0.)
					{
						if(pAtom->m_pPos)
							pAtom->m_pPos->m_pQuote->m_pPrice->put_Ask (dblValue); // set ask for position
						else 
							if(pAtom->m_Type == RDT_UNDAGG) 
								pAtom->m_pUnd->m_pPrice->put_Ask (dblValue); // set ask for underlying aggregation
							else 
								if(pAtom->m_pAgg && pAtom->m_pAgg->Type_ == CMmRvAggData::enFutAgg && pAtom->m_pAgg->pFut_)
									pAtom->m_pAgg->pFut_->m_pPrice->put_Ask (dblValue); // set ask for aggregation that have a price
					}
				}
				break;
			default:
				return E_NOTIMPL;
		}
	}
	catch (_com_error& err )
	{
		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(err), IID_IMmRiskView, err.Error());
	}
	return hr;
}

STDMETHODIMP CMmRiskView::AddOpositSymbol( LONG ContractID, LONG ContractOfOposit  )
{
	m_opositoptions.insert ( m_opositoptions.begin() , type_opositoptions_pair ( ContractID, ContractOfOposit ) ) ;
	return S_OK ;
}

STDMETHODIMP CMmRiskView::SaveTheoPricesAsClose(IMmTradeInfoColl* pTradesColl)
{
	try 
	{

		CMmRvUndColl::EnumCollType::iterator itUnd    =  m_pUnd->m_coll.begin();
		CMmRvUndColl::EnumCollType::iterator itUndEnd =  m_pUnd->m_coll.end();

		double	dTheoClosePrice = BAD_DOUBLE_VALUE;
		bool	bNeedToSaveData	= false;
		CRvMmQuoteAtom * pPosQuote = NULL;
		long	lUndCount = static_cast<long>(m_pUnd->m_coll.size());
		long	lProcessed = 1;


		typedef std::set<long>	TradesSet;
		typedef std::map<long, TradesSet> ContractMap;
		typedef ContractMap::iterator	ItrCM;
		typedef TradesSet::iterator		ItrTS;

		ContractMap cmTradesContracts;

		if (pTradesColl)
		{
			IMmTradeInfoCollPtr spTrades(pTradesColl);
			if(spTrades->Count && SUCCEEDED(spTrades->raw_ResetTradesPosition()))
			{
				VARIANT_BOOL bIsLast = VARIANT_FALSE;
				while(!bIsLast)
				{
					IMmTradeInfoAtomPtr spTradeAtom = spTrades->TradeAtCurrentPosition;
					if(spTradeAtom)
					{
						cmTradesContracts[spTradeAtom->ContractID].insert(spTradeAtom->TradeID);
					}
					spTrades->MoveNextTrade(&bIsLast);
				}
			}
		}

		//prepare xpath string
		_bstr_t bstrXPath = L"<root>";

		for(; itUnd != itUndEnd; ++itUnd)
		{
			CMmRvUndAtom* pUnd = dynamic_cast<CMmRvUndAtom*>(itUnd->second);

			if(pUnd != NULL)
			{

				CMmRvPosColl::EnumCollType::iterator itrPos    = pUnd->m_pPos->m_coll.begin();
				const CMmRvPosColl::EnumCollType::iterator itrPosEnd = pUnd->m_pPos->m_coll.end();

				for(;itrPos!=itrPosEnd; ++itrPos)
				{
					CMmRvPosAtom* pPos = dynamic_cast<CMmRvPosAtom*>(itrPos->second);

					if(pPos != NULL)
					{
						//if(pPos->m_bVisible)
						{
							EtsContractTypeEnum enContractType = pPos->m_enContractType;
							long	lContractID = pPos->m_nID;

							if (lContractID != 0) //not synthetic cash part "$"
							{
									
								if ( pPos->m_pQuote != NULL && pPos->m_pQuote->m_pPrice != NULL )
								{
									pPosQuote = pPos->m_pQuote;
								}
								else continue;
								
								if (enContractType == enCtStock)
								{
									/*if (pUnd->m_spHeadComponent == NULL)
										dTheoClosePrice = pPosQuote->m_pPrice->m_dPriceClose;
									else*/
										dTheoClosePrice = pUnd->m_pPrice->m_dActivePrice;
								}
								else if (enContractType == enCtIndex)
								{
									/*if (pUnd->m_spActiveFuture == NULL && pUnd->m_spHeadComponent == NULL)
										dTheoClosePrice = pPosQuote->m_pPrice->m_dPriceClose;
									else*/
										dTheoClosePrice = pUnd->m_pPrice->m_dActivePrice;
								}
								else if (enContractType == enCtFuture)
								{
									/*if (pUnd->m_spActiveFuture == NULL)
										dTheoClosePrice = pPosQuote->m_pPrice->m_dPriceClose;
									else*/
										dTheoClosePrice = pPosQuote->m_pPrice->m_dActivePrice;
								}
								else if (enContractType == enCtFutOption)
								{
									dTheoClosePrice = pPos->m_pQuote->m_dPriceTheo;
								}
								else if (enContractType == enCtOption)
								{
									dTheoClosePrice = pPos->m_pQuote->m_dPriceTheo;
								}
								else if (enContractType == enCtFutUnd)
								{
									/*if (pUnd->m_spActiveFuture == NULL)
										dTheoClosePrice = pPosQuote->m_pPrice->m_dPriceClose;
									else*/
										dTheoClosePrice = pPosQuote->m_pPrice->m_dActivePrice;
								}
								
								if (dTheoClosePrice == BAD_DOUBLE_VALUE || dTheoClosePrice < 0.0)
								{
									dTheoClosePrice = pPosQuote->m_pPrice->m_dPriceTheoClose;
								}

								if (dTheoClosePrice != BAD_DOUBLE_VALUE && !(dTheoClosePrice < 0.0))
								{
									bstrXPath += L"<contract id=\"" + _bstr_t(lContractID) + "\" ";
									bstrXPath += L"price=\"" + _bstr_t(dTheoClosePrice) + "\" ";
									bstrXPath += L"symbol=\"" + _bstr_t(pPos->m_bstrSymbol) + "\" ";
									bstrXPath += L"type=\""	+ _bstr_t(enContractType) + "\" />";
									bNeedToSaveData	=	true;

									//update all trades CloseTheoPrice
									ItrCM iter = cmTradesContracts.find(lContractID);
									if (pTradesColl)
									{
										if (iter!=cmTradesContracts.end())
										{
											ItrTS iter_ts_s = iter->second.begin();
											ItrTS iter_ts_e = iter->second.end();
											for(;iter_ts_s != iter_ts_e; ++iter_ts_s)
											{
												IMmTradeInfoAtomPtr spTradeAtom = pTradesColl->GetItem(*iter_ts_s);
												if(spTradeAtom)
												{
													if(spTradeAtom->ContractID == lContractID && spTradeAtom->ContractType == enContractType)
													{
														if (enContractType == enCtOption)
														{
															spTradeAtom->Opt->put_PriceTheoClose(dTheoClosePrice);
														}
														else if (enContractType == enCtFutOption)
														{
															spTradeAtom->FutOpt->put_PriceTheoClose(dTheoClosePrice);
														}
														else if (enContractType == enCtFuture)
														{
															spTradeAtom->Fut->put_PriceTheoClose(dTheoClosePrice);
														}
														else
														{
															spTradeAtom->Und->put_PriceTheoClose(dTheoClosePrice);
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
					
				}
				double dPercent = 100.* double(lProcessed)/lUndCount;
				long lPercent = static_cast<long>(dPercent);
				Fire_Progress(L"Saving theoretical price . . .", lPercent);

				lProcessed++;
			}
		}
		bstrXPath += L"</root>";
		//xpath string is prepared and now try to save it to db

		if (bNeedToSaveData)
		{
			if(!m_Connection.IsOpened())
				m_Connection.Open(m_bsConnectionString, 10, 120, 300, 300);

			//save all data to db
			if(m_Connection.IsOpened())
			{

				CStoredProc<CClientRecordset> spTheoPrices(m_Connection, L"usp_MmTheoPrices_Save");
				spTheoPrices << bstrXPath;
				spTheoPrices.Open();
			}
		}

	}
	catch (const _com_error& Err)
	{
		return 
			Error((PTCHAR)CComErrorWrapper::ErrorDescription(Err), __uuidof(IMmRiskView), Err.Error());
	}
	catch (...)
	{
		HRESULT _hr = HRESULT_FROM_WIN32(::GetLastError());
		if(SUCCEEDED(_hr)) _hr = E_FAIL;

		return 
			Error((PTCHAR)"An exception occurred while trying to save data", __uuidof(IMmRiskView), _hr);
	}

	return S_OK;
}

STDMETHODIMP CMmRiskView::PositionsLoad(IMmTradeInfoColl* pTradesColl)
{
	//ATLASSERT ( 0 ) ;
	HRESULT hr = S_OK;
	m_bIsStopped = VARIANT_FALSE;

	if(!pTradesColl)
		return E_POINTER;
	try
	{

		CComBSTR	bsConnectionString;
		m_spEtsMain->get_DatabaseString(&bsConnectionString);

		if(!m_Connection.IsOpened())
			m_Connection.Open((BSTR)bsConnectionString, 10, 120, 300, 300);

		//save all data to db
		if(m_Connection.IsOpened())
		{
			CStoredProc<CClientRecordset> rs(m_Connection, L"usp_MmManualPrice_Get");
			rs.Open();
			
			m_mapManualPrice.clear();
			long lTotalCount = rs.GetRecordCount();

			if(lTotalCount)
			{
				for(rs.MoveFirst(); !rs.IsEOF(); ++rs)
				{
					long lID = rs[L"contractID"];
					double dPrice = rs[L"manualPrice"];
					m_mapManualPrice[lID] =dPrice;
				}
			}
		}

		m_lOptCount = 0L;
		m_lUndCount = 0L;
		m_lFutCount = 0L;
		IMmTradeInfoCollPtr spTrades(pTradesColl);

		m_pUnd->Clear();

		_variant_t varItem;
		ULONG nFetched = 0L;
		long lCurrentProgress = -1;
		long lProcessed       = 0;
		long lTotal           = spTrades->Count;
		if(lTotal && SUCCEEDED(spTrades->raw_ResetTradesPosition()))
		{
			VARIANT_BOOL bIsLast = VARIANT_FALSE;

			while(!bIsLast)
			{
				IMmTradeInfoAtomPtr spTradeAtom = spTrades->TradeAtCurrentPosition;
				if(spTradeAtom)
				{
					long lTradeId     = spTradeAtom->TradeID;
					long lContractId  = spTradeAtom->ContractID;
					long lUndID       = spTradeAtom->UndID;

					IMmRvUndAtomPtr spUndAtom = m_pUnd->GetUnderlying(lUndID);
					if(spUndAtom == NULL)
						spUndAtom = _AddNewUnderlying(spTradeAtom->Und);

					CMmRvUndAtom* pUndAtom = dynamic_cast<CMmRvUndAtom*>(spUndAtom.GetInterfacePtr());
					IMmRvPosAtomPtr spPosAtom = pUndAtom->m_pPos->GetPosition(lContractId);
					if(spPosAtom == NULL)
					{
						spPosAtom = _AddNewPosition(spTradeAtom, spUndAtom , -1 );
					}
					_AddNewTradeToPosition(spUndAtom, spPosAtom,spTradeAtom);					
					if(m_bIsStopped)
						break;
				}
				double dPercent = 100.* double(lProcessed)/lTotal;
				long lPercent = static_cast<long>(dPercent);
				if(lPercent != lCurrentProgress)
				{
					lCurrentProgress = lPercent;
					Fire_Progress(L"Data Loading", lCurrentProgress);
				}
				lProcessed++;
				spTrades->MoveNextTrade(&bIsLast);
			}
		}
	}
	catch (_com_error& err) 
	{
		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(err), __uuidof(IMmRiskView), err.Error());
	}
	return hr;
}

void CMmRiskView::InitVola(CMmRvUndAtom* pUnd)
{
	if(pUnd)
	{
		if(VARIANT_FALSE == pUnd->m_spVolaSrv->IsInitialized)
			pUnd->m_spVolaSrv->Init(pUnd->m_bstrSymbol, pUnd->m_enContractType == enCtStock ? enCtStock : enCtIndex, m_spVolatilitySource);
	}
}



IMmRvPosAtomPtr  CMmRiskView::_AddNewPosition(IMmTradeInfoAtomPtr spTradeAtom, IMmRvUndAtomPtr spUndAtom, LONG lOptionOposit, IMmRvReqColl* pRequestColl, VARIANT_BOOL bUpdateVola)
{
	struct null_deleter
	{
		void operator()(void const *) const
		{
		}
	};

	CMmRvUndAtom* pUndAtom = dynamic_cast<CMmRvUndAtom*>(spUndAtom.GetInterfacePtr());
	CComObject<CMmRvPosAtom>* pPosAtom = NULL;

	long lContractID = spTradeAtom->ContractID;
	IMmRvPosAtomPtr spPosAtom = pUndAtom->m_pPos->GetPosition(lContractID);
	if(spPosAtom == NULL)
	{
		_bstr_t bsTradeSymbol = spTradeAtom->Symbol;

		spPosAtom = pUndAtom->m_pPos->AddNew(spTradeAtom->ContractID, bsTradeSymbol, &pPosAtom);
		pPosAtom->m_spStrategy = spTradeAtom->Strategy;

		pPosAtom->m_enContractType     = spTradeAtom->ContractType;

		pPosAtom->m_pQuote->m_nLotSize    = spTradeAtom->LotSize;
		pPosAtom->m_bVisible              = VARIANT_TRUE;   


		_bstr_t sKey = _bstr_t(static_cast<long>(pPosAtom->m_enContractType )) + _bstr_t(L"_") + pPosAtom->m_bstrSymbol;

		if ((pPosAtom->m_enContractType == enCtStock || pPosAtom->m_enContractType == enCtIndex) &&  pUndAtom->m_bstrPrimaryExchangeCode.length())
			sKey += _bstr_t(L".")+pUndAtom->m_bstrPrimaryExchangeCode;

		IMmRvReqAtomPtr spRequestAtom = m_pQuoteReqsAll->GetRequest(sKey);

		CComObject<CMmRvReqAtom>* pRequestAtom = NULL;
		if(spRequestAtom == NULL)
		{
			spRequestAtom = m_pQuoteReqsAll->AddNew(sKey, &pRequestAtom);
			if(pRequestAtom!=NULL)
			{
				pRequestAtom->m_spUnd = spUndAtom;
				pRequestAtom->m_spPos = spPosAtom;
				if(pRequestColl!=NULL)
				{
					IMmRvReqAtomPtr spFake;
					pRequestColl->Add(sKey, pRequestAtom, &spFake);
				}
			}
		}
		else
		{
			pRequestAtom = dynamic_cast<CComObject<CMmRvReqAtom>*>(spRequestAtom.GetInterfacePtr());
			if(pRequestAtom->m_spPos == NULL)
				pRequestAtom->m_spPos = spPosAtom;
		}

		if (pPosAtom->m_spUnd == NULL)
			pPosAtom->m_spUnd = m_pUnd->GetUnderlying(pUndAtom->m_nID);

		switch(pPosAtom->m_enContractType)
		{
		case enCtOption:
			{
				InitVola(pUndAtom);
				IEtsOptAtomPtr spOpt = spTradeAtom->Opt;
				pPosAtom->m_enOptType    = spOpt->OptType;
				pPosAtom->m_dtExpiry     = spOpt->Expiry;

				pPosAtom->m_pQuote->m_pPrice->m_dPriceClose  = spOpt->PriceClose;
				pPosAtom->m_pQuote->m_pPrice->m_dPriceTheoClose = spOpt->PriceTheoClose;

				CMPItr cur_itr;
				if ((cur_itr = m_mapManualPrice.find(lContractID)) != m_mapManualPrice.end())
				{
					pPosAtom->m_pQuote->m_pPrice->m_bManualActive = VARIANT_TRUE;
					pPosAtom->m_pQuote->m_pPrice->m_dActivePrice = cur_itr->second;
				}


				
				vt_date dtExpiry(pPosAtom->m_dtExpiry);
				//pPosAtom->m_nExpiryMonth  = static_cast<long>((DATE)vt_date(dtExpiry.get_year(), dtExpiry.get_month(), 1));
				pPosAtom->m_dStrike       = spOpt->Strike;
				pPosAtom->m_nOptionRootID = spTradeAtom->OptRootID;
				pPosAtom->m_nUndID        = pUndAtom->m_nID;
				pPosAtom->m_bstrImportId  = spOpt->ImportID; 
				pPosAtom->m_dVegaWeight   = m_spEtsMain->ExpCalendar->GetVegaWeight(pPosAtom->m_dtExpiry);

				_bstr_t	bsExpiryKey = _bstr_t(static_cast<long>(pPosAtom->m_dtExpiry));
				_CHK(pUndAtom->m_spVolaSrv->get_OptionVola(pPosAtom->m_dtExpiry, spOpt->Strike, &pPosAtom->m_pQuote->m_dMIV )); 

				if(bUpdateVola)
					pPosAtom->m_pQuote->m_dVola = pPosAtom->m_pQuote->m_dMIV;

				//////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(m_enViewMode == RV_GREEKS)
				{
					CComObject<CMmRvExpTotalAtom>* pTotalAtom = NULL;
					IMmRvExpTotalAtomPtr  spTotalAtom = m_pExpTotal->GetExpiration(pPosAtom->m_dtExpiry);
					if(spTotalAtom == NULL)
					{
						spTotalAtom = m_pExpTotal->AddNew(pPosAtom->m_dtExpiry, &pTotalAtom);
					}
					else
						pTotalAtom = dynamic_cast<CComObject<CMmRvExpTotalAtom>*>(spTotalAtom.GetInterfacePtr());

					IMmRvExpAtomPtr spUndExp = pUndAtom->m_pExp->GetExpiration(pPosAtom->m_dtExpiry);
					CComObject<CMmRvExpAtom>* pUndExp = NULL;
					if(spUndExp == NULL)
					{
						spUndExp = pUndAtom->m_pExp->AddNew(pPosAtom->m_dtExpiry, &pUndExp);
						pUndExp->m_dtExpiry = dtExpiry;

						IMmRvPosAtomPtr spFakePosAtom;
						pUndExp->m_pPos->Add(pPosAtom->m_nID, pPosAtom->m_bstrSymbol, pPosAtom, &spFakePosAtom);
						if(pTotalAtom)
						{
							IMmRvExpAtomPtr spFake;
							pTotalAtom->m_spExpiry->Add(pUndAtom->m_nID, spUndExp, &spFake);
						}
					}
					else
					{
						pUndExp = dynamic_cast<CComObject<CMmRvExpAtom>*>(spUndExp.GetInterfacePtr());
						if(pUndExp)
						{
							IMmRvPosAtomPtr spFakePosAtom;
							pUndExp->m_pPos->Add(pPosAtom->m_nID, pPosAtom->m_bstrSymbol, pPosAtom, &spFakePosAtom);
						}
					}
				}
				/////////////////////////////////////////////////////////////////////////////////////////////////////
				IEtsMmEntityAtomPtr spExpiryAtom = m_spExp->Item[bsExpiryKey];
				if(spExpiryAtom == NULL)
				 {
					 spExpiryAtom       = m_spExp->Add(bsExpiryKey, NULL);
					 spExpiryAtom->ID   = static_cast<long>(pPosAtom->m_dtExpiry);
					 spExpiryAtom->Name = dtExpiry.Format(_T("%b,%d %y")).GetString();   

				 }
				 m_lOptCount++;

				 if(pUndAtom->m_bHasSynthetic && pUndAtom->m_spSynthRoots!=NULL)
				 {
					 InitPositionSynthetics(pUndAtom, pPosAtom, pRequestColl);
					 ////////////////////////////////////////////////////////////////////////////////////
				 	 if(m_enViewMode == RV_GREEKS && pPosAtom->m_spSynthGreeks!=NULL)
					 {
						 CMmRvSynthGreeksColl* pSynth = dynamic_cast<CMmRvSynthGreeksColl*>(pPosAtom->m_spSynthGreeks.GetInterfacePtr());
						 if(pSynth && !pSynth->m_coll.empty())
						 {
							 CMmRvSynthGreeksColl::EnumCollType::iterator itrSynthColl    = pSynth->m_coll.begin();
							 CMmRvSynthGreeksColl::EnumCollType::iterator itrSynthCollEnd = pSynth->m_coll.end();
							 for(;itrSynthColl!=itrSynthCollEnd; ++itrSynthColl)
							 {
								 CMmRvSynthGreeksAtom* pSGAtom = dynamic_cast<CMmRvSynthGreeksAtom*>(itrSynthColl->second);
								 if(pSGAtom)
								 {
									 IMmRvExpAtomPtr spExp = pUndAtom->m_pExp->GetExpiration(pPosAtom->m_dtExpiry);
									 if(spExp != NULL)
									 {
										 CMmRvExpAtom* pExp = dynamic_cast<CMmRvExpAtom*>(spExp.GetInterfacePtr());
										 if(pExp)
										 {
											 if(pExp->m_spSynthGreek==NULL)
											 {
												 CComObject<CMmRvSynthGreeksColl>* pExpSynthColl = NULL;
												 CComObject<CMmRvSynthGreeksColl>::CreateInstance(&pExpSynthColl);
												 if(pExpSynthColl!=NULL)
													 pExp->m_spSynthGreek.Attach(pExpSynthColl, TRUE);

											 }

										 }					
										 if(pExp->m_spSynthGreek!=NULL)
										 {
											 IMmRvSynthGreeksAtomPtr spAtom;
											 pExp->m_spSynthGreek->get_Item(pSGAtom->m_nSynthUndID, &spAtom);
											 if(spAtom == NULL)
												pExp->m_spSynthGreek->Add(pSGAtom->m_nSynthUndID, pSGAtom->m_bstrSynthUndSymbol, NULL, &spAtom);
										 }
									 }
								 }
							 }
						 }
					 }
					///////////////////////////////////////////////////////////////////////////////////////////////////////////
				 }
			}break;
		case enCtFuture:
		case enCtFutOption:
			{
				InitVola(pUndAtom);

				CComObject<CMmRvFutColl>* pFut = NULL;
				if(pUndAtom->m_spFut == NULL )
				{
					_CHK(CComObject<CMmRvFutColl>::CreateInstance(&pFut), _T("Unable to create Futures"));
					pUndAtom->m_spFut.Attach(pFut, TRUE);
				}
				else
					pFut = dynamic_cast<CComObject<CMmRvFutColl>*>(pUndAtom->m_spFut.GetInterfacePtr());
				long lFutID = spTradeAtom->FutID;

				IMmRvFutAtomPtr spFuture = pFut->GetFutures(lFutID);
				IEtsFutAtomPtr spFutAtom = spTradeAtom->Fut;
				CComObject<CMmRvFutAtom>* pFutAtom = NULL;


				if(spFuture == NULL)
				{

					CComBSTR	futureSymbol(L"");
					_CHK(spFutAtom->get_Symbol(&futureSymbol));
					_bstr_t sFutureKey = _bstr_t((long)enCtFuture) + _bstr_t(L"_")  + _bstr_t(futureSymbol);

					
					// this future atom may already exists as active future for some index
					// in this case, we already have request to price provider for it
					IMmRvReqAtomPtr spFutRequestAtom = m_pQuoteReqsAll->GetRequest(sFutureKey);
					if(NULL != spFutRequestAtom ){
						IMmRvFutAtomPtr spExistedFutAtom;

						_CHK(spFutRequestAtom->get_Fut(&spExistedFutAtom));
						if ( NULL != spExistedFutAtom)
						{
								// oky, oky...we already have this future
								// just add pointer to into underlying's futures collection
								pFut->Add(lFutID,  spFutAtom->Symbol, spExistedFutAtom, &spFuture);
								pFutAtom = dynamic_cast<CComObject<CMmRvFutAtom>*>(spFuture.GetInterfacePtr());

						}
						else
						{
							spFuture = pFut->AddNew(lFutID,  spFutAtom->Symbol, &pFutAtom);
						}
					}
					else 
						spFuture = pFut->AddNew(lFutID,  spFutAtom->Symbol, &pFutAtom);
					if(pFutAtom)
					{
						pFutAtom->m_dtMaturity			= spFutAtom->MaturityDate;
						pFutAtom->m_spUndPriceProfile	= spFutAtom->UndPriceProfile;
						pFutAtom->m_spOptPriceProfile	= spFutAtom->OptPriceProfile;
						pFutAtom->m_nFutRootID			= spTradeAtom->FutRootID;
						pFutAtom->m_bstrFutRootSymbol	= spTradeAtom->FutRoot->Symbol;
						pFutAtom->m_bstrContractName	= spFutAtom->ContractName;
						pFutAtom->m_nUndID				= pUndAtom->m_nID;
						pFutAtom->m_nOptLotSize			= spTradeAtom->FutRoot->OptLotSize; 
						pFutAtom->m_nFutLotSize			= spTradeAtom->FutRoot->FutLotSize; 
						pFutAtom->m_pPrice->m_dPriceClose	= spFutAtom->PriceClose;
						pFutAtom->m_pPrice->m_dPriceTheoClose = spFutAtom->PriceTheoClose;
						pFutAtom->m_bIsAmerican			= spFutAtom->IsAmerican;
						pFutAtom->m_spUnd					= spUndAtom;
						pFutAtom->m_dBasis				= spFutAtom->FutureBasis;
						pFutAtom->m_dRatio				= spFutAtom->ActiveFutureRatio;
						pFutAtom->m_dK					= spFutAtom->K;

						pFutAtom->m_dKEq				= spFutAtom->KEq;
						pFutAtom->m_bMultOptDltEq		= spFutAtom->MultOptDltEq;
						if (spFutAtom->ManualActivePrice > 0)
						{
							pFutAtom->m_pPrice->m_bManualActive = VARIANT_TRUE;
							pFutAtom->m_pPrice->m_dActivePrice = spFutAtom->ManualActivePrice;
						}

						pFutAtom->m_bstrQuotationUnitName = spTradeAtom->FutRoot->QuotationUnitName;
						switch(spTradeAtom->FutRoot->QuoteFormat) {
							case 2:
								pFutAtom->m_bstrQuotePriceFormat = "Pts";
								break;
							case 1:
								pFutAtom->m_bstrQuotePriceFormat = "c";
								break;
							default:
								pFutAtom->m_bstrQuotePriceFormat = "$";
						}	
						IMmRvReqAtomPtr spFutRequestAtom = m_pQuoteReqsAll->GetRequest(sFutureKey);
						if(spFutRequestAtom == NULL)
						{
							CComObject<CMmRvReqAtom>* pObject = NULL;
							spFutRequestAtom = m_pQuoteReqsAll->AddNew(sFutureKey, &pObject);
							if(pObject!=NULL)
								pObject->m_spFut = spFuture;
						}
						m_lFutCount++;
					}
				}
				else
					pFutAtom = dynamic_cast<CComObject<CMmRvFutAtom>* >(spFuture.GetInterfacePtr());

				pRequestAtom->m_spFut = spFuture;
				pPosAtom->m_spFut     = spFuture;
				pPosAtom->m_nUndID	  = pUndAtom->m_nID;
				if(enCtFutOption == pPosAtom->m_enContractType)
				{

					IEtsFutOptAtomPtr spFutOpt					= spTradeAtom->FutOpt;
					pPosAtom->m_pQuote->m_pPrice->m_dPriceClose = spFutOpt->PriceClose;
					pPosAtom->m_pQuote->m_pPrice->m_dPriceTheoClose = spFutOpt->PriceTheoClose;

					CMPItr cur_itr;
					if ((cur_itr = m_mapManualPrice.find(lContractID)) != m_mapManualPrice.end())
					{
						pPosAtom->m_pQuote->m_pPrice->m_bManualActive = VARIANT_TRUE;
						pPosAtom->m_pQuote->m_pPrice->m_dActivePrice = cur_itr->second;
					}

					pPosAtom->m_enOptType   = spFutOpt->OptType;
					pPosAtom->m_dtExpiry    = spFutOpt->Expiry;
					pPosAtom->m_dStrike     = spFutOpt->Strike;
					pPosAtom->m_dVegaWeight = m_spEtsMain->ExpCalendar->GetVegaWeight(pPosAtom->m_dtExpiry);
					pPosAtom->m_bstrImportId= spFutOpt->ImportID;

					_CHK(pUndAtom->m_spVolaSrv->get_OptionVola(pPosAtom->m_dtExpiry, pPosAtom->m_dStrike, &pPosAtom->m_pQuote->m_dMIV )); 

					if(bUpdateVola)
						pPosAtom->m_pQuote->m_dVola = pPosAtom->m_pQuote->m_dMIV;

					vt_date dtExpiry(pPosAtom->m_dtExpiry);
					//pPosAtom->m_nExpiryMonth  = static_cast<long>((DATE)vt_date(dtExpiry.get_year(), dtExpiry.get_month(), 1));

					//                
					_bstr_t bsExpiryKey(static_cast<long>(pPosAtom->m_dtExpiry));
					IEtsMmEntityAtomPtr spExpiryAtom = m_spExp->Item[bsExpiryKey];
					if(spExpiryAtom == NULL)
					{
						spExpiryAtom       = m_spExp->Add(bsExpiryKey, NULL);
						spExpiryAtom->ID   = static_cast<long>(pPosAtom->m_dtExpiry);
						spExpiryAtom->Name = dtExpiry.Format(_T("%b,%d %y")).GetString();   
					}
					if(m_enViewMode == RV_GREEKS)
					{
						CComObject<CMmRvExpTotalAtom>* pTotalAtom = NULL;
						IMmRvExpTotalAtomPtr  spTotalAtom = m_pExpTotal->GetExpiration(pPosAtom->m_dtExpiry);
						if(spTotalAtom == NULL)
						{
							spTotalAtom = m_pExpTotal->AddNew(pPosAtom->m_dtExpiry, &pTotalAtom);
						}
						else
							pTotalAtom = dynamic_cast<CComObject<CMmRvExpTotalAtom>*>(spTotalAtom.GetInterfacePtr());

						IMmRvExpAtomPtr spUndExp = pUndAtom->m_pExp->GetExpiration(pPosAtom->m_dtExpiry);
						CComObject<CMmRvExpAtom>* pUndExp = NULL;
						if(spUndExp == NULL)
						{
							spUndExp = pUndAtom->m_pExp->AddNew(pPosAtom->m_dtExpiry, &pUndExp);
							pUndExp->m_dtExpiry = dtExpiry;

							IMmRvPosAtomPtr spFakePosAtom;
							pUndExp->m_pPos->Add(pPosAtom->m_nID, pPosAtom->m_bstrSymbol, pPosAtom, &spFakePosAtom);

							if(pTotalAtom)
							{
								IMmRvExpAtomPtr spFake;
								pTotalAtom->m_spExpiry->Add(pUndAtom->m_nID, spUndExp, &spFake);
							}
						}
						else
						{
							pUndExp = dynamic_cast<CComObject<CMmRvExpAtom>*>(spUndExp.GetInterfacePtr());
							if(pUndExp)
							{
								IMmRvPosAtomPtr spFakePosAtom;
								pUndExp->m_pPos->Add(pPosAtom->m_nID, pPosAtom->m_bstrSymbol, pPosAtom, &spFakePosAtom);
							}
						}
					}
					//////////////////////////////////////////////////////////////////////////////////////////////////////////

					 m_lOptCount++;
				}
				else
				{
					pPosAtom->m_pQuote->m_pPrice = pFutAtom->m_pPrice;
					pPosAtom->m_pQuote->m_spPrice = pFutAtom->m_spPrice;
					pPosAtom->m_pQuote->m_pPrice->m_dPriceClose = spFutAtom->PriceClose;
					pPosAtom->m_pQuote->m_pPrice->m_dPriceTheoClose = spFutAtom->PriceTheoClose;

					CMPItr cur_itr;
					if ((cur_itr = m_mapManualPrice.find(lContractID)) != m_mapManualPrice.end())
					{
						pPosAtom->m_pQuote->m_pPrice->m_bManualActive = VARIANT_TRUE;
						pPosAtom->m_pQuote->m_pPrice->m_dActivePrice = cur_itr->second;
					}
				}


			}break;
		case enCtStock:
		case enCtIndex:
			{
				//IUndAtomPtr              spUnd       = spTradeAtom->Und;
				pPosAtom->m_pQuote->m_pPrice->m_dPriceClose = pUndAtom->m_pPrice->m_dPriceClose;
				pPosAtom->m_pQuote->m_pPrice->m_dPriceTheoClose = pUndAtom->m_pPrice->m_dPriceTheoClose;

				CMPItr cur_itr;
				if ((cur_itr = m_mapManualPrice.find(lContractID)) != m_mapManualPrice.end())
				{
					pPosAtom->m_pQuote->m_pPrice->m_bManualActive = VARIANT_TRUE;
					pPosAtom->m_pQuote->m_pPrice->m_dActivePrice = cur_itr->second;
				}
				// check for existence of active future for index 
				if ( pPosAtom->m_enContractType == enCtIndex )
				{
					//IEtsFutAtomPtr spActiveFuture = spUnd->ActiveFuture;		// here is atom from contracts collections
					IMmRvFutAtomPtr spIdxActiveFuture;								// here is atom from index atom

					//if ( NULL != spActiveFuture)
					{
						spUndAtom->get_ActiveFuture(&spIdxActiveFuture);	
						if ( spIdxActiveFuture )	// if still not active future for this index
							pPosAtom->m_spActiveFuture = spIdxActiveFuture;
						{
							// create active future atom for this index
							//CComObject<CMmRvFutAtom> *spRvUndAtomActiveFuture = NULL;

							//CComObject<CMmRvFutAtom>::CreateInstance(&spRvUndAtomActiveFuture);
							//spIdxActiveFuture.Attach(spRvUndAtomActiveFuture, TRUE);
							//spUndAtom->putref_ActiveFuture(spRvUndAtomActiveFuture);
						}

						//_CHK(spIdxActiveFuture->put_CalcGreeks(VARIANT_FALSE));

						//LONG valueLong;
						//_CHK(spActiveFuture->get_ID(&valueLong));
						//_CHK(spIdxActiveFuture->put_ID(valueLong));

						//_CHK(spActiveFuture->get_FutRootID(&valueLong));
						//_CHK(spIdxActiveFuture->put_FutRootID(valueLong));
						//_CHK(pUndAtom->get_ID(&valueLong));
						//_CHK(spIdxActiveFuture->put_UndID(valueLong));
						//_CHK(spActiveFuture->get_ExpCalendarID(&valueLong));
						//_CHK(spIdxActiveFuture->put_ExpCalendarID(valueLong) );

						//DATE valueDate;
						//_CHK(spActiveFuture->get_MaturityDate(&valueDate) );
						//_CHK(spIdxActiveFuture->put_Maturity(valueDate));

						//VARIANT_BOOL valueBool;
						//_CHK(spActiveFuture->get_IsAmerican(&valueBool));
						//_CHK(spIdxActiveFuture->put_IsAmerican(valueBool));

						//DOUBLE valueDouble;
						//_CHK(spActiveFuture->get_FutureBasis(&valueDouble));
						//_CHK(spIdxActiveFuture->put_FutureBasis(valueDouble));

						//CComBSTR	valueBstr;
						//_CHK(spActiveFuture->get_ContractName(&valueBstr));
						//_CHK(spIdxActiveFuture->put_ContractName(valueBstr));
						//_CHK(spActiveFuture->get_Symbol(&valueBstr));
						//_CHK(spIdxActiveFuture->put_Symbol(valueBstr));

						//IEtsPriceProfileAtomPtr valuePriceProfilePtr;
						//_CHK(spActiveFuture->get_UndPriceProfile(&valuePriceProfilePtr) );
						//_CHK(spIdxActiveFuture->putref_UndPriceProfile(valuePriceProfilePtr));
						//_CHK(spActiveFuture->get_OptPriceProfile(&valuePriceProfilePtr) );
						//_CHK(spIdxActiveFuture->putref_OptPriceProfile(valuePriceProfilePtr));

						///*				
						//If Not g_ContractAll(m_Aux.Idx.ID).Und.FutRoots(m_Aux.Idx.ActiveFuture.FutRootID) Is Nothing Then
						//m_Aux.Idx.ActiveFuture.FutRootSymbol = g_ContractAll(m_Aux.Idx.ID).Und.FutRoots(m_Aux.Idx.ActiveFuture.FutRootID).Symbol
						//m_Aux.Idx.ActiveFuture.FutLotSize = g_ContractAll(m_Aux.Idx.ID).Und.FutRoots(m_Aux.Idx.ActiveFuture.FutRootID).FutLotSize
						//m_Aux.Idx.ActiveFuture.OptLotSize = g_ContractAll(m_Aux.Idx.ID).Und.FutRoots(m_Aux.Idx.ActiveFuture.FutRootID).OptLotSize
						//End If*/

						//_bstr_t sActiveFutureKey = _bstr_t(static_cast<long>(enCtFuture)) + _bstr_t(L"_") + ( BSTR )valueBstr;
						//IMmRvReqAtomPtr spActiveFutureRequestAtom = m_pQuoteReqsAll->GetRequest(sActiveFutureKey);
						//if(spActiveFutureRequestAtom == NULL)
						//{
						//	CComObject<CMmRvReqAtom>* pObject = NULL;
						//	spActiveFutureRequestAtom = m_pQuoteReqsAll->AddNew(sActiveFutureKey, &pObject);
						//	if(pObject!=NULL)
						//		pObject->m_spFut = spIdxActiveFuture;
						//	if(pRequestColl!=NULL)
						//	{
						//		IMmRvReqAtomPtr spFake;
						//		pRequestColl->Add(sActiveFutureKey,spActiveFutureRequestAtom, &spFake);
						//	}
						//}
					}
				}
			}
			break;
		}

		pPosAtom->m_nQty					= 0;
		pPosAtom->m_nQtyInShares			= 0;
		pPosAtom->m_nQtyLTDBuy				= BAD_LONG_VALUE;
		pPosAtom->m_dPosLTDBuy				= BAD_DOUBLE_VALUE;
		pPosAtom->m_nQtyDailyPrevDateBuy	= BAD_LONG_VALUE;
		pPosAtom->m_dPosDailyPrevDateBuy	= BAD_DOUBLE_VALUE;
		pPosAtom->m_nQtyDailyTodayBuy		= BAD_LONG_VALUE;
		pPosAtom->m_dPosDailyTodayBuy		= BAD_DOUBLE_VALUE;
		pPosAtom->m_nQtyLTDSell				= BAD_LONG_VALUE;
		pPosAtom->m_dPosLTDSell				= BAD_DOUBLE_VALUE;

		pPosAtom->m_nQtyDailyPrevDateSell	= BAD_LONG_VALUE;
		pPosAtom->m_dPosDailyPrevDateSell	= BAD_DOUBLE_VALUE;
		pPosAtom->m_nQtyDailyTodaySell		= BAD_LONG_VALUE;
		pPosAtom->m_dPosDailyTodaySell		= BAD_DOUBLE_VALUE;

		if(pUndAtom)
			pUndAtom->AddPosToAggregations( CMmRvAggData::MmRvPosAtomPtr(pPosAtom, null_deleter()));

		/*if ( m_enViewMode == RV_VME )
		{
			type_opositoptionsI it = m_opositoptions.find ( lContractID ) ;
			if ( it == m_opositoptions.end() && lOptionOposit > 0 )
			{
				IRvMmQuoteAtomPtr pQuote ;
				pPosAtom->get_Quote ( &pQuote ) ;
				ATLASSERT  ( pQuote != NULL ) ;
				if ( pQuote != NULL )
					pQuote->put_VolatilityEnginrCalculation ( VARIANT_TRUE ) ;

				it = m_opositoptions.insert ( m_opositoptions.begin() , type_opositoptions_pair ( lContractID, lOptionOposit ) ) ;
			}

			if ( it != m_opositoptions.end() )
			{
				long lContractIDNew = it->second ;

				BSTR bsSymbolOposit ;
				pPosAtom->GetOpositOption ( &bsSymbolOposit) ;

				CComObject<CMmRvPosAtom>* pPosOpAtom = NULL;
				IMmRvPosAtomPtr spPosOpAtom ;

				spPosAtom->GetCopyOfObject ( VARIANT_TRUE , &spPosOpAtom ) ;
				spPosAtom = pUndAtom->m_pPos->AddNew(lContractIDNew, bsSymbolOposit, &pPosOpAtom);
				
				pPosAtom->SimpleCopyForETS_VME( pPosOpAtom ) ;
				pPosOpAtom->put_Symbol ( bsSymbolOposit ) ;
				EtsOptionTypeEnum enOptType ;
				pPosOpAtom->get_OptType ( &enOptType ) ;
				pPosOpAtom->put_OptType ( enOptType == enOtCall ? enOtPut : enOtCall ) ;

				IRvMmQuoteAtomPtr pQuote ;
				pPosOpAtom->get_Quote ( &pQuote ) ;
				ATLASSERT  ( pQuote != NULL ) ;
				if ( pQuote != NULL )
					pQuote->put_VolatilityEnginrCalculation ( VARIANT_TRUE ) ;

				CComObject<CMmRvReqAtom>* pRequestOpAtom = NULL;

				_bstr_t sKeyOposit = _bstr_t(static_cast<long>(pPosAtom->m_enContractType )) + _bstr_t(L"_") + bsSymbolOposit ;
				
				IMmRvReqAtomPtr spRequestOpAtom = m_pQuoteReqsAll->GetRequest(sKeyOposit);

				if(spRequestOpAtom == NULL)
				{
					spRequestOpAtom = m_pQuoteReqsAll->AddNew(sKeyOposit, &pRequestOpAtom);
					if(pRequestOpAtom!=NULL)
					{
						pRequestOpAtom->m_spUnd = spUndAtom;
						pRequestOpAtom->m_spPos = pPosOpAtom;
						if(pRequestColl!=NULL)
						{
							IMmRvReqAtomPtr spFake;
							pRequestColl->Add(sKeyOposit, pRequestOpAtom, &spFake);
						}
					}
				}
				else
				{
					pRequestOpAtom = dynamic_cast<CComObject<CMmRvReqAtom>*>(spRequestOpAtom.GetInterfacePtr());
					if(pRequestOpAtom->m_spPos == NULL)
						pRequestOpAtom->m_spPos = spPosAtom;
				}
				
			}
		}*/

	}
    return spPosAtom;
}

 IMmRvUndAtomPtr CMmRiskView::_AddNewUnderlying(IUndAtomPtr spEtsUndAtom /*IMmTradeInfoAtomPtr spTradeAtom*/, IMmRvReqColl* pRequestColl)
{
	CComObject<CMmRvUndAtom>* pUndAtom   = NULL;
	IUndAtomPtr              spUnd       = spEtsUndAtom;
	IExchAtomPtr			 spUndExch;
	long                     nUndId      = spUnd->ID;
	_bstr_t					 bsUndSymbol = spUnd->Symbol;

	IMmRvUndAtomPtr          spUndAtom = m_pUnd->AddNew(nUndId, bsUndSymbol, &pUndAtom);
	
	pUndAtom->m_enContractType     = spUnd->UndType;
	pUndAtom->internalName_=pUndAtom->Name_ = bsUndSymbol;

	pUndAtom->m_spDividend         = spUnd->Dividend;
	if(pUndAtom->m_enContractType != enCtStock)
	{
		pUndAtom->m_spBasketIndex  = m_spEtsMain->Index->Item[pUndAtom->m_nID];
		/*if(pUndAtom->m_spBasketIndex!=NULL)
		{
            if(pUndAtom->m_spBasketIndex->IsBasket == VARIANT_FALSE)
				pUndAtom->m_spBasketIndex = NULL;
		}*/
		pUndAtom->m_dYield = spUnd->Yield;
	}
    pUndAtom->m_bShouldMultOptDeltaEq   = spUnd->bShouldMultOptDeltaEq;
	pUndAtom->m_dKOptDeltaEq            = spUnd->dKOptDeltaEq;

	pUndAtom->m_bIsAmerican				= spUnd->IsAmerican;
	pUndAtom->m_bIsHTB					= spUnd->IsHTB;
	pUndAtom->m_dSkew					= spUnd->Skew;
	pUndAtom->m_dKurt					= spUnd->Kurt;
	pUndAtom->m_bHasSynthetic			= spUnd->HaveSyntheticRoots;
	pUndAtom->m_spSynthRoots		    = spUnd->SyntheticRoots;
	pUndAtom->m_spUndPriceProfile		= spUnd->UndPriceProfile;
	pUndAtom->m_spOptPriceProfile		= spUnd->OptPriceProfile;
	pUndAtom->m_pPrice->m_dPriceClose   = spUnd->PriceClose;

	pUndAtom->m_dCoeff					= spUnd->Coeff;
	pUndAtom->m_bIsHead					= spUnd->IsHead;
	pUndAtom->m_bPriceByHead			= spUnd->PriceByHead;

	if (spUnd->ManualActivePrice > 0)
	{
		pUndAtom->m_pPrice->m_bManualActive = VARIANT_TRUE;
		pUndAtom->m_pPrice->m_dActivePrice = spUnd->ManualActivePrice;
	}

	pUndAtom->m_pPrice->m_dPriceTheoClose   = spUnd->PriceTheoClose;
	pUndAtom->m_nLotSize				= spUnd->LotSize;

	pUndAtom->m_nPrimaryExchangeID		= spUnd->PrimaryExchangeID;
	if (m_spEtsMain->Exch)
	{
		spUndExch = m_spEtsMain->Exch->Item[pUndAtom->m_nPrimaryExchangeID];
		if (spUndExch)
			pUndAtom->m_bstrPrimaryExchangeCode = spUndExch->Code;
	}

	if(m_pGrp)
		pUndAtom->SetNetExposureAUM(m_pGrp->m_dNetExposureAUM);


	if (spUnd->HeadComponent)
	{
		pUndAtom->m_spHeadComponent = m_pUnd->GetUnderlying(spUnd->HeadComponent->ID);
		if(pUndAtom->m_spHeadComponent == NULL)
			pUndAtom->m_spHeadComponent = _AddNewUnderlying(spUnd->HeadComponent, pRequestColl);
	}
	
	pUndAtom->UndPos_ = BAD_LONG_VALUE;	
	pUndAtom->OptQty_ = BAD_LONG_VALUE;
	pUndAtom->FutQty_ = BAD_LONG_VALUE;

	if( enCtFutUnd != pUndAtom->m_enContractType)
	{

		_bstr_t sKey = _bstr_t(static_cast<long>(pUndAtom->m_enContractType)) + _bstr_t(L"_") + pUndAtom->m_bstrSymbol;

		if (pUndAtom->m_bstrPrimaryExchangeCode.length())
			sKey += _bstr_t(L".")+pUndAtom->m_bstrPrimaryExchangeCode;

		IMmRvReqAtomPtr spRequestAtom = m_pQuoteReqsAll->GetRequest(sKey);
		if(spRequestAtom == NULL)
		{
			CComObject<CMmRvReqAtom>* pObject = NULL;
			spRequestAtom = m_pQuoteReqsAll->AddNew(sKey, &pObject);
			if(pObject!=NULL)
				pObject->m_spUnd = spUndAtom;
			if(pRequestColl!=NULL)
			{
				IMmRvReqAtomPtr spFake;
				pRequestColl->Add(sKey,spRequestAtom, &spFake);
			}
		}
		else
			spRequestAtom->put_IndexOnly(VARIANT_FALSE);
	}

	//Groups Aggregation
	//if(m_spEtsMain && m_pGroups)
	//{
	//	IUnknownPtr spUnk;
	//	_variant_t varItem;

	//	ULONG nFetched = 0;
	//	HRESULT hr = S_OK;

	//	_CHK(m_spEtsMain->UnderlyingGroup->get__NewEnum(&spUnk), _T("Fail to get Groups collection."));

	//	IEnumVARIANTPtr spEnum(spUnk);
	//	_CHK(spEnum->Reset(), _T("Fail to reset Groups collection."));
	//	bool bAssigned = false;

	//	while((hr = spEnum->Next(1L, &varItem, &nFetched)) == S_OK)
	//	{
	//		ATLASSERT(varItem.vt == VT_DISPATCH);
	//		IEtsUndGroupAtomPtr spGroupAtom;
	//		spGroupAtom = varItem;
	//		if(nFetched > 0L && spGroupAtom != NULL)
	//		{
	//			IUndAtomPtr spEtsUndAtom = spGroupAtom->Und->Item[nUndId];
	//			if(spEtsUndAtom!=NULL)
	//			{
	//				bAssigned = true;
	//				long lGroupID = spGroupAtom->ID;
	//				CMmRvGroupColl::CollType::iterator itrFind = m_pGroups->m_coll.find(lGroupID);
	//				CComObject<CMmRvGroupAtom>* pGroupAtom = NULL;

	//				if(itrFind == m_pGroups->m_coll.end())
	//				{
	//					// New Group
	//					m_pGroups->AddNew(lGroupID, &pGroupAtom);
	//					pGroupAtom->m_bstrSymbol = spGroupAtom->Name;
	//				}
	//				else
	//					pGroupAtom = dynamic_cast<CComObject<CMmRvGroupAtom>*>(itrFind->second);

	//				pUndAtom->m_underlyingGroup.insert(lGroupID);
	//				if(pGroupAtom)
	//				{
	//					IMmRvUndAtomPtr spTmp;
	//					pGroupAtom->m_pUndColl->Add(nUndId, bsUndSymbol, spUndAtom, &spTmp);
	//				}
	//			}
	//		}
	//	}
	//	if(!bAssigned)
	//	{
	//		// No Group Assigned - use unassigned group Aggregation
	//		long    lGroupID = 0;
	//		_bstr_t bsGroupName = L"<Unassigned>";
	//		CMmRvGroupColl::CollType::iterator itrFind = m_pGroups->m_coll.find(lGroupID);
	//		CComObject<CMmRvGroupAtom>* pGroupAtom = NULL;

	//		if(itrFind == m_pGroups->m_coll.end())
	//		{
	//			m_pGroups->AddNew(lGroupID, &pGroupAtom);
	//			pGroupAtom->m_bstrSymbol = bsGroupName;
	//		}
	//		else
	//			pGroupAtom = dynamic_cast<CComObject<CMmRvGroupAtom>*>(itrFind->second);

	//		pUndAtom->m_underlyingGroup.insert(lGroupID);
	//		if(pGroupAtom)
	//		{
	//			IMmRvUndAtomPtr spTmp;
	//			if(pGroupAtom->m_pUndColl->GetUnderlying(nUndId)== NULL)
	//				pGroupAtom->m_pUndColl->Add(nUndId, bsUndSymbol, spUndAtom, &spTmp);
	//		}
	//	}
	//}
	m_lUndCount++;

	if ( (pUndAtom->m_enContractType == enCtIndex || pUndAtom->m_enContractType == enCtFutUnd))
		AddActiveFuture(spUnd, pUndAtom);

	return spUndAtom;

}

STDMETHODIMP CMmRiskView::AddNewActiveFutures(IMmRvUndAtom* spUndAtom, IMmRvReqColl* pRequests)
{
	HRESULT hr = S_OK;
	try
	{
		 CComObject<CMmRvUndAtom>* pUnd = dynamic_cast< CComObject<CMmRvUndAtom>*>(spUndAtom);
		 if (pUnd)
		 {
			 IUndAtomPtr spUnd = m_spEtsMain->UnderlyingAll->Item[pUnd->m_nID];
			 AddActiveFuture(spUnd, pUnd, pRequests);

		 }	
	}
	catch (_com_error& err )
	{
		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(err), IID_IMmRiskView, err.Error());
	}
	return hr;
}

void CMmRiskView::AddActiveFuture( IUndAtomPtr spUnd, CComObject<CMmRvUndAtom>* pUndAtom, IMmRvReqColl* pRequestColl )
{
	IEtsFutAtomPtr spActiveFuture = spUnd->ActiveFuture;	// here is atom from contracts collections
	IMmRvFutAtomPtr spIdxActiveFuture;							// here is atom from index atom

	// active future stuff
	// first check that this underlying is not index for this risk view
	// if it is, active future for underlying is the same as for index
	LONG	idxID;

	if (pUndAtom)
		pUndAtom->ClearRatios();

	_CHK(m_spIdx->get_ID(&idxID));
	if (idxID == pUndAtom->m_nID ) {
		pUndAtom->m_pPrice = m_pIdx->m_pPrice;
		pUndAtom->m_spPrice = m_pIdx->m_spPrice;
		//IMmRvFutAtomPtr	activeFuture;
		//_CHK(m_spIdx->get_ActiveFuture(&activeFuture));
		pUndAtom->m_spActiveFuture = m_pIdx->m_spActiveFuture;
		if ( pUndAtom->m_spActiveFuture ) {
			CComBSTR	valueBstr;
			_CHK(pUndAtom->m_spActiveFuture->get_Symbol(&valueBstr));
			_bstr_t sActiveFutureKey = _bstr_t(static_cast<long>(enCtFuture)) + _bstr_t(L"_") + ( BSTR )valueBstr;
			IMmRvReqAtomPtr spActiveFutureRequestAtom = m_pQuoteReqsAll->GetRequest(sActiveFutureKey);
			if(spActiveFutureRequestAtom == NULL)	{
				CComObject<CMmRvReqAtom>* pObject = NULL;
				spActiveFutureRequestAtom = m_pQuoteReqsAll->AddNew(sActiveFutureKey, &pObject);
				if(pObject!=NULL)
					pObject->m_spFut = m_pIdx->m_spActiveFuture;
			}
		}
	}
	else {
		if ( NULL != spActiveFuture)
		{
			spIdxActiveFuture = pUndAtom->m_spActiveFuture;
			if (NULL == spIdxActiveFuture )	// if still not active future for this index
			{
				// create active future atom for this index
				CComObject<CMmRvFutAtom> *pRvUndAtomActiveFuture = NULL;

				CComObject<CMmRvFutAtom>::CreateInstance(&pRvUndAtomActiveFuture);
				spIdxActiveFuture.Attach(pRvUndAtomActiveFuture, TRUE);
				//spUndAtom->putref_ActiveFuture(spRvUndAtomActiveFuture);
				pUndAtom->m_spActiveFuture = spIdxActiveFuture;
			}

			_CHK(spIdxActiveFuture->put_CalcGreeks(VARIANT_FALSE));

			LONG valueLong;
			_CHK(spActiveFuture->get_ID(&valueLong));
			_CHK(spIdxActiveFuture->put_ID(valueLong));

			_CHK(spActiveFuture->get_FutRootID(&valueLong));
			_CHK(spIdxActiveFuture->put_FutRootID(valueLong));
			_CHK(spIdxActiveFuture->put_UndID(pUndAtom->m_nID));

			DATE valueDate;
			_CHK(spActiveFuture->get_MaturityDate(&valueDate) );
			_CHK(spIdxActiveFuture->put_Maturity(valueDate));

			VARIANT_BOOL valueBool;
			_CHK(spActiveFuture->get_IsAmerican(&valueBool));
			_CHK(spIdxActiveFuture->put_IsAmerican(valueBool));

			DOUBLE valueDouble;
			_CHK(spActiveFuture->get_FutureBasis(&valueDouble));
			_CHK(spIdxActiveFuture->put_Basis(valueDouble));

			valueDouble = spActiveFuture->GetPriceClose();
			IMmRvPricePtr spPrice;
			_CHK(spIdxActiveFuture->get_Price(&spPrice));
			_CHK(spPrice->put_Close(valueDouble));

			valueDouble = spActiveFuture->GetPriceTheoClose();
			_CHK(spPrice->put_TheoClose(valueDouble));

			valueDouble = spActiveFuture->GetManualActivePrice();
			_CHK(spPrice->put_Active(valueDouble));

			if (valueDouble > 0.0){
				_CHK(spPrice->put_IsUseManualActive(VARIANT_TRUE));
			}
			else{
				_CHK(spPrice->put_IsUseManualActive(VARIANT_FALSE));
			}


			CComBSTR	valueBstr;
			_CHK(spActiveFuture->get_ContractName(&valueBstr));
			_CHK(spIdxActiveFuture->put_ContractName(valueBstr));
			_CHK(spActiveFuture->get_Symbol(&valueBstr));
			_CHK(spIdxActiveFuture->put_Symbol(valueBstr));

			IEtsPriceProfileAtomPtr valuePriceProfilePtr;
			_CHK(spActiveFuture->get_UndPriceProfile(&valuePriceProfilePtr) );
			_CHK(spIdxActiveFuture->putref_UndPriceProfile(valuePriceProfilePtr));
			_CHK(spActiveFuture->get_OptPriceProfile(&valuePriceProfilePtr) );
			_CHK(spIdxActiveFuture->putref_OptPriceProfile(valuePriceProfilePtr));

			/*				
			If Not g_ContractAll(m_Aux.Idx.ID).Und.FutRoots(m_Aux.Idx.ActiveFuture.FutRootID) Is Nothing Then
			m_Aux.Idx.ActiveFuture.FutRootSymbol = g_ContractAll(m_Aux.Idx.ID).Und.FutRoots(m_Aux.Idx.ActiveFuture.FutRootID).Symbol
			m_Aux.Idx.ActiveFuture.FutLotSize = g_ContractAll(m_Aux.Idx.ID).Und.FutRoots(m_Aux.Idx.ActiveFuture.FutRootID).FutLotSize
			m_Aux.Idx.ActiveFuture.OptLotSize = g_ContractAll(m_Aux.Idx.ID).Und.FutRoots(m_Aux.Idx.ActiveFuture.FutRootID).OptLotSize
			End If*/

			_bstr_t sActiveFutureKey = _bstr_t(static_cast<long>(enCtFuture)) + _bstr_t(L"_") + ( BSTR )valueBstr;
			IMmRvReqAtomPtr spActiveFutureRequestAtom = m_pQuoteReqsAll->GetRequest(sActiveFutureKey);
			if(spActiveFutureRequestAtom == NULL)
			{
				CComObject<CMmRvReqAtom>* pObject = NULL;
				spActiveFutureRequestAtom = m_pQuoteReqsAll->AddNew(sActiveFutureKey, &pObject);
				if(pObject!=NULL)
					pObject->m_spFut = spIdxActiveFuture;
				if(pRequestColl!=NULL)
				{
					IMmRvReqAtomPtr spFake;
					pRequestColl->Add(sActiveFutureKey,spActiveFutureRequestAtom, &spFake);
				}
			}
			//else
			//	spRequestAtom->put_IndexOnly(VARIANT_FALSE);

			m_lFutCount++;
		}
	}
}

   
void CMmRiskView::AppendTradeToPosition(IMmRvPosAtomPtr& spPosAtom, const IMmTradeInfoAtomPtr& spTradeAtom)    
{
	CMmRvPosAtom* pPosAtom = dynamic_cast<CMmRvPosAtom*>(spPosAtom.GetInterfacePtr());

	bool bIsBuy		  = spTradeAtom->IsBuy==VARIANT_TRUE;
	long lQty         = spTradeAtom->Quantity * (bIsBuy? 1: -1);
	long lQtyInShares = lQty * pPosAtom->m_pQuote->m_nLotSize;


	double dPriceClose = pPosAtom->m_pQuote->m_pPrice->m_dPriceClose;

	if (m_spEtsMain->UseTheoCloseForPNL && pPosAtom->m_pQuote->m_pPrice->m_dPriceTheoClose > 0.0)
	{
		dPriceClose = pPosAtom->m_pQuote->m_pPrice->m_dPriceTheoClose;
	}

	if(bIsBuy)
	{
		// Buy Side
		if(pPosAtom->m_nQtyLTDBuy == BAD_LONG_VALUE) 
			pPosAtom->m_nQtyLTDBuy = 0;
		pPosAtom->m_nQtyLTDBuy += lQtyInShares;
		if(spTradeAtom->IsPosition== VARIANT_TRUE)
		{
			if(/*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= 0.0 )
			{
				if(pPosAtom->m_dPosLTDBuy == BAD_DOUBLE_VALUE)  
					pPosAtom->m_dPosLTDBuy = 0;
				pPosAtom->m_dPosLTDBuy += (/*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * lQtyInShares);

			}
		}
		else
		{
			if(pPosAtom->m_dPosLTDBuy == BAD_DOUBLE_VALUE)  
				pPosAtom->m_dPosLTDBuy = 0;

			pPosAtom->m_dPosLTDBuy += (spTradeAtom->Price * lQtyInShares);
		}
		if(static_cast<long>(spTradeAtom->TradeDate) < static_cast<long>(vt_date::GetCurrentDate(true)))
		{
			if(pPosAtom->m_nQtyDailyPrevDateBuy == BAD_LONG_VALUE) 
				pPosAtom->m_nQtyDailyPrevDateBuy = 0;


			pPosAtom->m_nQtyDailyPrevDateBuy += lQtyInShares;


			if(/*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= 0.0)
			{

				if (pPosAtom->m_dPosDailyPrevDateBuy == BAD_DOUBLE_VALUE) 
					pPosAtom->m_dPosDailyPrevDateBuy = 0;
				pPosAtom->m_dPosDailyPrevDateBuy +=  /*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * lQtyInShares;
			}
			else
				if( spTradeAtom->IsPosition!=VARIANT_TRUE)
				{
					if(pPosAtom->m_dPosDailyPrevDateBuy == BAD_DOUBLE_VALUE)
						pPosAtom->m_dPosDailyPrevDateBuy = 0;
					pPosAtom->m_dPosDailyPrevDateBuy += spTradeAtom->Price * lQtyInShares;
				}
		}
		else
		{

			if(pPosAtom->m_nQtyDailyTodayBuy == BAD_LONG_VALUE)
				pPosAtom->m_nQtyDailyTodayBuy = 0;
			pPosAtom->m_nQtyDailyTodayBuy +=  lQtyInShares;

			if( spTradeAtom->IsPosition==VARIANT_TRUE)
			{
				if(/*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= 0.0)
				{

					if(pPosAtom->m_dPosDailyTodayBuy == BAD_DOUBLE_VALUE) pPosAtom->m_dPosDailyTodayBuy = 0;
					pPosAtom->m_dPosDailyTodayBuy += /*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * lQtyInShares;
				}
			}
			else
			{
				if( pPosAtom->m_dPosDailyTodayBuy == BAD_DOUBLE_VALUE) pPosAtom->m_dPosDailyTodayBuy = 0;
				pPosAtom->m_dPosDailyTodayBuy += spTradeAtom->Price * lQtyInShares;
			}
		}
	}
	else
	{
		// Sell side
		if (pPosAtom->m_nQtyLTDSell == BAD_LONG_VALUE) pPosAtom->m_nQtyLTDSell = 0;
		pPosAtom->m_nQtyLTDSell +=  lQtyInShares;


		if(spTradeAtom->IsPosition)
		{
			if(/*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= 0.0)
			{

				if(pPosAtom->m_dPosLTDSell == BAD_DOUBLE_VALUE)  pPosAtom->m_dPosLTDSell = 0;
				pPosAtom->m_dPosLTDSell +=  /*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * lQtyInShares;
			}
		}
		else
		{
			if(pPosAtom->m_dPosLTDSell == BAD_DOUBLE_VALUE) pPosAtom->m_dPosLTDSell = 0;
			pPosAtom->m_dPosLTDSell +=  spTradeAtom->Price * lQtyInShares;
		}

		if(static_cast<long>(spTradeAtom->TradeDate) < static_cast<long>(vt_date::GetCurrentDate(true)))
		{
			if (pPosAtom->m_nQtyDailyPrevDateSell == BAD_LONG_VALUE) pPosAtom->m_nQtyDailyPrevDateSell = 0;
			pPosAtom->m_nQtyDailyPrevDateSell += lQtyInShares;
			if(/*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= 0.0)
			{
				if (pPosAtom->m_dPosDailyPrevDateSell == BAD_DOUBLE_VALUE)  pPosAtom->m_dPosDailyPrevDateSell = 0;
				pPosAtom->m_dPosDailyPrevDateSell +=  /*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * lQtyInShares;
			}
			else
				if(VARIANT_TRUE!=spTradeAtom->IsPosition)
				{
					if(pPosAtom->m_dPosDailyPrevDateSell == BAD_DOUBLE_VALUE) pPosAtom->m_dPosDailyPrevDateSell = 0;
					pPosAtom->m_dPosDailyPrevDateSell +=  spTradeAtom->Price * lQtyInShares;
				}
		}
		else
		{

			if (pPosAtom->m_nQtyDailyTodaySell == BAD_LONG_VALUE) pPosAtom->m_nQtyDailyTodaySell = 0;
			pPosAtom->m_nQtyDailyTodaySell += lQtyInShares;
			if(spTradeAtom->IsPosition)
			{
				if(/*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose >= 0.0)
				{
					if(pPosAtom->m_dPosDailyTodaySell == BAD_DOUBLE_VALUE) pPosAtom->m_dPosDailyTodaySell = 0;
					pPosAtom->m_dPosDailyTodaySell +=  /*pPosAtom->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose * lQtyInShares;
				}
			}
			else
			{
				if(pPosAtom->m_dPosDailyTodaySell == BAD_DOUBLE_VALUE) pPosAtom->m_dPosDailyTodaySell = 0;
				pPosAtom->m_dPosDailyTodaySell += spTradeAtom->Price * lQtyInShares;
			}
		}
	}

	if(pPosAtom->m_nQty == BAD_LONG_VALUE)		   pPosAtom->m_nQty = 0L;
	if(pPosAtom->m_nQtyInShares == BAD_LONG_VALUE) pPosAtom->m_nQtyInShares = 0L;

	pPosAtom->m_nQty          += lQty;
	pPosAtom->m_nQtyInShares  += lQtyInShares;

}
  
HRESULT  CMmRiskView::_AddNewTradeToPosition(IMmRvUndAtomPtr spUndAtom, IMmRvPosAtomPtr spPosAtom, IMmTradeInfoAtomPtr spTradeAtom)
{
	
	CMmRvUndAtom* pUndAtom = dynamic_cast<CMmRvUndAtom*>(spUndAtom.GetInterfacePtr());
	CMmRvPosAtom* pPosAtom = dynamic_cast<CMmRvPosAtom*>(spPosAtom.GetInterfacePtr());
	bool bIsBuy = spTradeAtom->IsBuy==VARIANT_TRUE;

	long  lQty         = spTradeAtom->Quantity * (bIsBuy? 1: -1);
    long  lQtyInShares = lQty * pPosAtom->m_pQuote->m_nLotSize;
    
	AppendTradeToPosition(spPosAtom, spTradeAtom);

/*	switch(pPosAtom->m_enContractType)
	{
	case enCtOption:
	case enCtFutOption:
		{
			if(pUndAtom->OptQty_ == BAD_LONG_VALUE) 
				pUndAtom->OptQty_ = lQty;
			else
				pUndAtom->OptQty_ += lQty;
		}
		break;
	case enCtFuture:
		{
			if(pUndAtom->FutQty_ == BAD_LONG_VALUE)
				pUndAtom->FutQty_ = lQty;
			else
				pUndAtom->FutQty_ += lQty;

			if(pUndAtom->UndPos_ == BAD_LONG_VALUE)
				pUndAtom->UndPos_ = lQtyInShares;
			else
				pUndAtom->UndPos_ += lQtyInShares;
		}break;
	case enCtStock:
	case enCtIndex:
		{
			if(pUndAtom->UndPos_== BAD_LONG_VALUE)
				pUndAtom->UndPos_ = lQtyInShares;
			else
				pUndAtom->UndPos_ += lQtyInShares;
		}break;
	default:
		break;
	}

	if(m_enViewMode == RV_RISKS)
	{
		long     lStrategyId   = 0;
		_bstr_t bsStrategyName = L"<Unassigned>";
		IEtsStrategyAtomPtr spStrategy = spTradeAtom->Strategy;

		if(spStrategy != NULL)
		{
			lStrategyId    = spStrategy->ID;
			bsStrategyName = spStrategy->Name;
		}*/
		/*_AddPositionToStrategy(pUndAtom, m_pStrategy, lStrategyId, bsStrategyName, spTradeAtom, pPosAtom);
		if(!pUndAtom->m_underlyingGroup.empty())
		{
			CMmRvUndAtom::CUnderkyingGroup::iterator itGrp = pUndAtom->m_underlyingGroup.begin(); 
			CMmRvUndAtom::CUnderkyingGroup::iterator itGrpEnd = pUndAtom->m_underlyingGroup.end(); 
			for(; itGrp!=itGrpEnd; ++itGrp)
			{
				long lGroupId = *itGrp;
				CMmRvGroupColl::CollType::iterator itrGroups = m_pGroups->m_coll.find(lGroupId);
				if(itrGroups != m_pGroups->m_coll.end())
				{
					CMmRvGroupAtom* pAtom = dynamic_cast<CMmRvGroupAtom*>(itrGroups->second);
					if(pAtom)
						_AddPositionToStrategy(pUndAtom, pAtom->m_pStrategyColl, lStrategyId, bsStrategyName, spTradeAtom, pPosAtom);
				}
			}
		}*/
	/*}*/
	return S_OK;
}

//HRESULT CMmRiskView::_AddPositionToStrategy(CMmRvUndAtom* pUndAtom , CMmRvStrategyColl* pStrategyCollection, long lStrategyId, _bstr_t bsStrategyName, IMmTradeInfoAtomPtr spTradeAtom, CMmRvPosAtom* pPosAtom)
//{
//	if(pStrategyCollection && pUndAtom)
//	{
//		IMmRvStrategyAtomPtr spStrategyAtom = pStrategyCollection->GetStrategy(lStrategyId);
//		CComObject<CMmRvStrategyAtom>* pStrategyAtom = NULL;
//		if(spStrategyAtom == NULL)
//		{
//			spStrategyAtom = pStrategyCollection->AddNew(lStrategyId, &pStrategyAtom);
//			if(pStrategyAtom)
//			{
//				pStrategyAtom->m_bstrSymbol        = bsStrategyName;
//				pStrategyAtom->m_pMasterUnderlying = pUndAtom;
// 				pStrategyAtom->m_pPrice            = pUndAtom->m_pPrice;
// 				pStrategyAtom->m_spPrice           = pUndAtom->m_spPrice;    
//			}
//		}
//		else
//			pStrategyAtom = dynamic_cast<CComObject<CMmRvStrategyAtom>*>(spStrategyAtom.GetInterfacePtr());
//
//		if(pStrategyAtom != NULL)
//		{
//			if(pStrategyAtom->m_pMasterUnderlying!=NULL && pStrategyAtom->m_pMasterUnderlying->m_nID != pUndAtom->m_nID)
//			{
//				pStrategyAtom->m_pMasterUnderlying = NULL;
//				CComObject<CMmRvPrice>::CreateInstance(&pStrategyAtom->m_pPrice);
//				pStrategyAtom->m_spPrice.Attach(pStrategyAtom->m_pPrice, TRUE);
//			}
//
//			if(!pStrategyAtom->m_bSyntheticAggregationDisabled)
//			{
//				if(pStrategyAtom->CheckSyntheticEligibility(pPosAtom))
//				{
//					if(pPosAtom->m_enContractType == enCtOption)
//					{
//						if(pStrategyAtom->m_lSyntheticOptionRootID  != pPosAtom->m_nOptionRootID)
//						{
//							pStrategyAtom->m_pSuPrice				 = pPosAtom->m_pQuote->m_pSuPrice;
//							pStrategyAtom->m_spSuPrice				 = pPosAtom->m_pQuote->m_spSuPrice;    
//							pStrategyAtom->m_bIsSyntheticAggregation = VARIANT_TRUE;
//							pStrategyAtom->m_lSyntheticOptionRootID  = pPosAtom->m_nOptionRootID;
//
//							if(pStrategyAtom->m_pMasterUnderlying!=NULL)
//							{
//								pStrategyAtom->m_pMasterUnderlying = NULL;
//								CComObject<CMmRvPrice>::CreateInstance(&pStrategyAtom->m_pPrice);
//								pStrategyAtom->m_spPrice.Attach(pStrategyAtom->m_pPrice, TRUE);
//							}
//
//						}
//					}
//				}
//				else
//				{
//					pStrategyAtom->m_bIsSyntheticAggregation       = VARIANT_FALSE;
//					pStrategyAtom->m_bSyntheticAggregationDisabled = true;					
//					CComObject<CMmRvPrice>::CreateInstance(&pStrategyAtom->m_pSuPrice);
//					pStrategyAtom->m_spSuPrice.Attach(pStrategyAtom->m_pSuPrice, TRUE);
//					pStrategyAtom->m_lSyntheticOptionRootID = 0;
//				}
//			}
//
//			long lContractID	  = spTradeAtom->ContractID;
//			_bstr_t bsTradeSymbol = spTradeAtom->Symbol;
//
//			IMmRvPosAtomPtr spStrategyPos =  pStrategyAtom->m_pPos->GetPosition(lContractID);
//			if(spStrategyPos != NULL)
//				AppendTradeToPosition(spStrategyPos, spTradeAtom);
//			else
//			{
//				IMmRvPosAtomPtr spPosRet;
//				spStrategyPos = pPosAtom->MakeCopy(true, false );
//
//				AppendTradeToPosition(spStrategyPos, spTradeAtom);
//				pStrategyAtom->m_spPos->Add(lContractID, bsTradeSymbol, spStrategyPos, &spPosRet);
//			}
//
//			if((pPosAtom->m_bIsSynthetic && pPosAtom->m_spSynthGreeks != NULL) && pStrategyAtom)
//			{
//				ISynthRootAtomPtr spSynthRoot = pUndAtom->m_spSynthRoots->Item[pPosAtom->m_nOptionRootID];
//				if(spSynthRoot!= NULL)
//				{
//					if(spSynthRoot->CashValue > 0 )
//					{
//						IMmRvPosAtomPtr spCashPos;
//						CMmRvStrategyColl::CollType::iterator itrUSD = m_pStrategy->m_coll.find(USD_ID);
//						if(itrUSD == m_pStrategy->m_coll.end())
//						{
////							CComObject<CMmRvUndAtom>* pCashAtom = NULL;
////							IMmRvUndAtomPtr spCashAtom; 
//							CMmRvUndAtom* pCashAtom = dynamic_cast<CMmRvUndAtom*>(m_pUnd->m_collRef.find(USD_ID)->second->second);
//// 							CComObject<CMmRvUndAtom>::CreateInstance(&pCashAtom);
//// 							spCashAtom.Attach(pCashAtom, TRUE);
//// 
//// 							pCashAtom->m_nID        = USD_ID;
//// 							pCashAtom->m_bstrSymbol = USD_SYMBOL;
//// 
//// 							CComObject<CMmRvPosColl>* pSunthPosColl = NULL;
//// 							_CHK(CComObject<CMmRvPosColl>::CreateInstance(&pSunthPosColl),_T("Fail to create Synth Position"));
//// 
//// 							pCashAtom->m_spSynthPos.Attach(pSunthPosColl, TRUE);
//// 							pCashAtom->m_enContractType  = enCtStock;
//// 							pCashAtom->m_nLotSize		 = 1;
//// 							pCashAtom->m_nQty    = BAD_LONG_VALUE;
//// 							pCashAtom->m_nOptQty = BAD_LONG_VALUE;
//// 							pCashAtom->m_nFutQty = BAD_LONG_VALUE;
//// 							pCashAtom->m_dUndPosForRates = 0.0;
//// 
//// 							pCashAtom->m_pPrice->m_dPriceAsk  = 1.0;
//// 							pCashAtom->m_pPrice->m_dPriceBid  = 1.0;
//// 							pCashAtom->m_pPrice->m_dPriceLast = 1.0;
//// 
//// 							pCashAtom->m_spUndPriceProfile = m_spEtsMain->PriceProfile->Item[1];
//// 							pCashAtom->m_spOptPriceProfile = m_spEtsMain->PriceProfile->Item[1];
//
//							spCashPos = _AddNewSynthPosition(pStrategyAtom, pCashAtom);
//							
//						}
//						else
//							spCashPos = itrUSD->second;
//					}
//
//					_variant_t varItem;
//					ULONG nFetched = 0L;
//					IEnumVARIANTPtr spSynthRootEnum(spSynthRoot->SynthRootComponents->_NewEnum);
//
//					_CHK(spSynthRootEnum->Reset(), _T("Fail to Reset Trades collection."));
//					HRESULT hr = S_OK;
//					while((hr = spSynthRootEnum->Next(1L, &varItem, &nFetched)) == S_OK)
//					{
//						ATLASSERT(varItem.vt == VT_DISPATCH);
//						if(varItem.vt == VT_DISPATCH)
//						{
//							ISynthRootCompAtomPtr spSynthRootCompAtom(varItem);
//							if(spSynthRootCompAtom)
//							{
//								const long lCompUndId = spSynthRootCompAtom->UndID;
//								IMmRvUndAtomPtr spGUnd = m_pUnd->m_collRef.find(lCompUndId)->second->second;
//								CMmRvUndAtom* pGUnd = dynamic_cast<CMmRvUndAtom*>(spGUnd.GetInterfacePtr());
//
//								if(spGUnd != NULL)
//								{
//									CComObject<CMmRvUndAtom>* pSynthUnd = NULL;
//									IMmRvUndAtomPtr spSynthUnd;
//
//									IMmRvPosAtomPtr  spSynthUndPos = pStrategyAtom->m_pPos->GetPosition(lCompUndId);
//
//									EtsContractTypeEnum enContractType = pGUnd->m_enContractType;
//									_bstr_t bsKey;
//
//									if(spSynthUndPos == NULL)
//									{
//// 										CComObject<CMmRvUndAtom>::CreateInstance(&pSynthUnd);
//// 										spSynthUnd.Attach(pSynthUnd, TRUE);
//// 										pSynthUnd->m_nID = lCompUndId;
//// 										pSynthUnd->m_bstrSymbol = pGUnd->m_bstrSymbol;
//// 
//// 										IMmRvPosCollPtr spSynthPos(__uuidof(MmRvPosColl));
//// 										pSynthUnd->m_spSynthPos = spSynthPos;
//// 
//// 										bsKey = _bstr_t(enContractType) + _bstr_t(L"_")  + pSynthUnd->m_bstrSymbol;
//// 										pSynthUnd->m_enContractType = enContractType;
//// 
//// 
//// 										pSynthUnd->m_bIsAmerican			= pGUnd->m_bIsAmerican;
//// 										pSynthUnd->m_bIsHTB					= pGUnd->m_bIsHTB;
//// 										pSynthUnd->m_nExpCalendarID			= pGUnd->m_nExpCalendarID;
//// 										pSynthUnd->m_dSkew					= pGUnd->m_dSkew;
//// 										pSynthUnd->m_dKurt					= pGUnd->m_dKurt;
//// 										pSynthUnd->m_bHasSynthetic			= pGUnd->m_bHasSynthetic;
//// 										pSynthUnd->m_nLotSize				= pGUnd->m_nLotSize;
//// 										pSynthUnd->m_spSynthRoots			= pGUnd->m_spSynthRoots;
//// 										pSynthUnd->m_pPrice					= pGUnd->m_pPrice;
//// 										pSynthUnd->m_spPrice				= pGUnd->m_spPrice;
//// 
//// 										pSynthUnd->m_spDividend				= pGUnd->m_spDividend;
//// 										if(enContractType != enCtStock)
//// 										{
//// 											pSynthUnd->m_spBasketIndex = m_spEtsMain->Index->Item[lCompUndId];
//// 											if(pSynthUnd->m_spBasketIndex != NULL && pSynthUnd->m_spBasketIndex->IsBasket == VARIANT_FALSE)
//// 												pSynthUnd->m_spBasketIndex = NULL;
//// 
//// 											pSynthUnd->m_dYield = pGUnd->m_dYield;
//// 										}
//// 
//// 										pSynthUnd->m_spUndPriceProfile = pGUnd->m_spUndPriceProfile;
//// 										pSynthUnd->m_spOptPriceProfile = pGUnd->m_spOptPriceProfile;
//// 
//// 										m_lUndCount++;
//// 
//// 										pSynthUnd->m_nQty    = BAD_LONG_VALUE;
//// 										pSynthUnd->m_nOptQty = BAD_LONG_VALUE;
//// 										pSynthUnd->m_nFutQty = BAD_LONG_VALUE;
//// 										pSynthUnd->m_dUndPosForRates = 0.0;
//// 
//// 										InitVola(pSynthUnd);
//// 
//// 										IMmRvReqAtomPtr spRequestAtom = m_pQuoteReqsAll->GetRequest(bsKey);
//// 
//// 										CComObject<CMmRvReqAtom>* pRequestAtom = NULL;
//// 										if(spRequestAtom == NULL)
//// 										{
//// 											spRequestAtom = m_pQuoteReqsAll->AddNew(bsKey, &pRequestAtom);
//// 											if(pRequestAtom!=NULL)
//// 												pRequestAtom->m_spUnd = spSynthUnd;
//// 										}
//// 										else
//// 											spRequestAtom->put_IndexOnly(VARIANT_FALSE);
//// 
//										spSynthUndPos = _AddNewSynthPosition(pStrategyAtom, pGUnd);
//
//// 										if(pSynthUnd->m_spSynthPos==NULL)
//// 											pSynthUnd->m_spSynthPos = IMmRvPosCollPtr(__uuidof(MmRvPosColl));
//									}
//									//else
//								}
//
//							}
//						}
//					}
//				}				
//			}
//		}
//	}
//	return S_OK;
//}

HRESULT CMmRiskView::InitPositionSynthetics(CMmRvUndAtom* pUndAtom, CMmRvPosAtom* pPosAtom, IMmRvReqColl* pNewReqsAll)
{
	HRESULT hr = S_OK;
	ISynthRootAtomPtr spSynthRoot = pUndAtom->m_spSynthRoots->Item[pPosAtom->m_nOptionRootID];
	if(spSynthRoot!=NULL)
	{
		pPosAtom->m_bIsSynthetic = VARIANT_TRUE;
		CComObject<CMmRvSynthGreeksColl>* pSynthGreeksColl = NULL; 
		if(pPosAtom->m_spSynthGreeks == NULL)
		{
			_CHK(CComObject<CMmRvSynthGreeksColl>::CreateInstance(&pSynthGreeksColl), _T("Unable to create SynthGreeksColl"));
			pPosAtom->m_spSynthGreeks.Attach(pSynthGreeksColl, TRUE);
		}
		else
			pSynthGreeksColl = dynamic_cast<CComObject<CMmRvSynthGreeksColl>*>(pPosAtom->m_spSynthGreeks.GetInterfacePtr());
       
		if(spSynthRoot->CashValue > 0 )
		{
			IMmRvUndAtomPtr spCashAtom = m_pUnd->GetUnderlying(USD_ID);
			if(spCashAtom == NULL)
			{
				CComObject<CMmRvUndAtom>* pCashAtom = NULL;
				spCashAtom = m_pUnd->AddNew(USD_ID, USD_SYMBOL, &pCashAtom);

				CComObject<CMmRvPosColl>* pSunthPosColl = NULL;
				_CHK(CComObject<CMmRvPosColl>::CreateInstance(&pSunthPosColl),_T("Fail to create Synth Position"));
				pCashAtom->Name_ = pCashAtom->m_bstrSymbol;
				pCashAtom->m_spSynthPos.Attach(pSunthPosColl, TRUE);
				pCashAtom->m_enContractType  = enCtStock;
				pCashAtom->m_nLotSize		 = 1;
				pCashAtom->UndPos_ = BAD_LONG_VALUE;
				pCashAtom->OptQty_ = BAD_LONG_VALUE;
				pCashAtom->FutQty_ = BAD_LONG_VALUE;
				pCashAtom->UndPosForRates_ = 0.0;

				pCashAtom->m_pPrice->m_dPriceAsk  = 1.0;
				pCashAtom->m_pPrice->m_dPriceBid  = 1.0;
				pCashAtom->m_pPrice->m_dPriceLast = 1.0;

				pCashAtom->m_spUndPriceProfile = m_spEtsMain->PriceProfile->Item[1];
				pCashAtom->m_spOptPriceProfile = m_spEtsMain->PriceProfile->Item[1];
			}
			CComObject<CMmRvSynthGreeksAtom>* pSynthGreeks = NULL;
			
			IMmRvSynthGreeksAtomPtr spSynthGreeks =  pSynthGreeksColl->GetSynthGreeks(USD_ID);
			if(spSynthGreeks == NULL)
			{
				spSynthGreeks = pSynthGreeksColl->AddNew(USD_ID, USD_SYMBOL, &pSynthGreeks);
				pSynthGreeks->m_nContractID      = pPosAtom->m_nID;
				pSynthGreeks->m_enContractType   = pPosAtom->m_enContractType;
				pSynthGreeks->m_dDeliveryUnits   = pPosAtom->m_pQuote->m_nLotSize * spSynthRoot->CashValue;
				pSynthGreeks->m_bstrSymbol       = pPosAtom->m_bstrSymbol;
				pSynthGreeks->m_bVisible         = pPosAtom->m_bVisible;
				pSynthGreeks->m_bIsTotal         = VARIANT_FALSE;
				pSynthGreeks->m_pSuPrice         = pPosAtom->m_pQuote->m_pSuPrice;
				pSynthGreeks->m_spSuPrice        = pPosAtom->m_pQuote->m_spSuPrice;
			}
            
			IMmRvSynthGreeksAtom* pUndSynthAtom ;
			if(pUndAtom->m_spSynthGreeks == NULL)
				pUndAtom->m_spSynthGreeks = IMmRvSynthGreeksCollPtr(__uuidof(MmRvSynthGreeksColl));
			pUndAtom->m_spSynthGreeks->get_Item(USD_ID, &pUndSynthAtom);
			IMmRvSynthGreeksAtomPtr spUndSynthAtom(pUndSynthAtom, false);
			if(spUndSynthAtom == NULL)
			{
				pUndAtom->m_spSynthGreeks->Add(USD_ID, USD_SYMBOL, NULL, &pUndSynthAtom);
				spUndSynthAtom.Attach(pUndSynthAtom);

				CComObject<CMmRvSynthGreeksAtom>* pSuAtom = dynamic_cast<CComObject<CMmRvSynthGreeksAtom>*>(pUndSynthAtom);
				if(pSuAtom)
				{
					pSuAtom->m_nContractID		  = pUndAtom->m_nID;
					pSuAtom->m_dDeliveryUnits     = BAD_DOUBLE_VALUE;
					pSuAtom->m_enContractType     = pUndAtom->m_enContractType;
					pSuAtom->m_bstrSymbol		  = USD_SYMBOL;
					pSuAtom->m_bstrSynthUndSymbol = USD_SYMBOL;
					pSuAtom->m_nSynthUndID		  = USD_ID;
					pSuAtom->m_bVisible			  = VARIANT_TRUE;
					pSuAtom->m_bIsTotal			  = VARIANT_TRUE;
					pSuAtom->m_pSuPrice			  = pPosAtom->m_pQuote->m_pSuPrice;
					pSuAtom->m_spSuPrice		  = pPosAtom->m_pQuote->m_spSuPrice;
				}

			}
		}
        
		_variant_t varItem;
		ULONG nFetched = 0L;
		IEnumVARIANTPtr spSynthRootEnum(spSynthRoot->SynthRootComponents->_NewEnum);

		_CHK(spSynthRootEnum->Reset(), _T("Fail to Reset Trades collection."));
		while((hr = spSynthRootEnum->Next(1L, &varItem, &nFetched)) == S_OK)
		{
			ATLASSERT(varItem.vt == VT_DISPATCH);
			if(varItem.vt == VT_DISPATCH)
			{
				ISynthRootCompAtomPtr spSynthRootCompAtom(varItem);
				if(spSynthRootCompAtom)
				{
					const long lCompUndId = spSynthRootCompAtom->UndID;

					if(lCompUndId != pUndAtom->m_nID)
					{
						IUndAtomPtr spGUnd = m_spEtsMain->UnderlyingAll->Item[lCompUndId];
						if(spGUnd != NULL)
						{
							CComObject<CMmRvUndAtom>* pSynthUnd = NULL;
							IMmRvUndAtomPtr  spSynthUnd = m_pUnd->GetUnderlying(lCompUndId);

							EtsContractTypeEnum enContractType = spGUnd->UndType;
							_bstr_t bsKey;

							if(spSynthUnd == NULL)
							{
								spSynthUnd =  m_pUnd->AddNew(lCompUndId, spGUnd->Symbol, &pSynthUnd);

								IMmRvPosCollPtr spSynthPos(__uuidof(MmRvPosColl));
								pSynthUnd->m_spSynthPos = spSynthPos;

								pSynthUnd->m_enContractType = enContractType;
								pSynthUnd->Name_ = pSynthUnd->m_bstrSymbol;

								pSynthUnd->m_bIsAmerican			= spGUnd->IsAmerican;
								pSynthUnd->m_bIsHTB					= spGUnd->IsHTB;
								pSynthUnd->m_dSkew					= spGUnd->Skew;
								pSynthUnd->m_dKurt					= spGUnd->Kurt;
								pSynthUnd->m_bHasSynthetic			= spGUnd->HaveSyntheticRoots;
								pSynthUnd->m_nLotSize				= spGUnd->LotSize;
								pSynthUnd->m_spSynthRoots			= spGUnd->SyntheticRoots;
								pSynthUnd->m_pPrice->m_dPriceClose  = spGUnd->PriceClose;
								pSynthUnd->m_pPrice->m_dPriceTheoClose  = spGUnd->PriceTheoClose;

								if (spGUnd->ManualActivePrice > 0)
								{
									pSynthUnd->m_pPrice->m_bManualActive = VARIANT_TRUE;
									pSynthUnd->m_pPrice->m_dActivePrice = spGUnd->ManualActivePrice;
								}

								IExchAtomPtr			 spUndExch;
								pSynthUnd->m_nPrimaryExchangeID		= spGUnd->PrimaryExchangeID;
								if (m_spEtsMain->Exch)
								{
									spUndExch = m_spEtsMain->Exch->Item[pSynthUnd->m_nPrimaryExchangeID];
									if (spUndExch)
										pSynthUnd->m_bstrPrimaryExchangeCode = spUndExch->Code;
								}

								bsKey = _bstr_t(enContractType) + _bstr_t(L"_")  + pSynthUnd->m_bstrSymbol;

								if (pSynthUnd->m_bstrPrimaryExchangeCode.length())
									bsKey += _bstr_t(L".")+pSynthUnd->m_bstrPrimaryExchangeCode;

								pSynthUnd->m_spDividend     = spGUnd->Dividend;
								if(enContractType != enCtStock)
								{
									pSynthUnd->m_spBasketIndex = m_spEtsMain->Index->Item[lCompUndId];
									if(pSynthUnd->m_spBasketIndex != NULL && pSynthUnd->m_spBasketIndex->IsBasket == VARIANT_FALSE)
										pSynthUnd->m_spBasketIndex = NULL;

									pSynthUnd->m_dYield = spGUnd->Yield;
								}

								pSynthUnd->m_spUndPriceProfile = spGUnd->UndPriceProfile;
								pSynthUnd->m_spOptPriceProfile = spGUnd->OptPriceProfile;

								m_lUndCount++;

								pSynthUnd->UndPos_ = BAD_LONG_VALUE;
								pSynthUnd->OptQty_ = BAD_LONG_VALUE;
								pSynthUnd->FutQty_ = BAD_LONG_VALUE;
								pSynthUnd->UndPosForRates_ = 0.0;

								InitVola(pSynthUnd);

								/* if root component in asset group [now not realized]
								pSynthUnd->m_dCoeff					= spGUnd->Coeff;
								pSynthUnd->m_bIsHead					= spGUnd->IsHead;
								pSynthUnd->m_bPriceByHead			= spGUnd->PriceByHead;

								pSynthUnd->m_spHeadComponent = m_pUnd->GetUnderlying(spGUnd->HeadComponent->ID);
								if(pSynthUnd->m_spHeadComponent == NULL)
									pSynthUnd->m_spHeadComponent = _AddNewUnderlying(spGUnd->HeadComponent, m_pQuoteReqsAll);*/

								IMmRvReqAtomPtr spRequestAtom = m_pQuoteReqsAll->GetRequest(bsKey);

								CComObject<CMmRvReqAtom>* pRequestAtom = NULL;
								if(spRequestAtom == NULL)
								{
									spRequestAtom = m_pQuoteReqsAll->AddNew(bsKey, &pRequestAtom);
									if(pRequestAtom!=NULL)
									{
										pRequestAtom->m_spUnd = spSynthUnd;
										if(pNewReqsAll != NULL)
										{
											IMmRvReqAtomPtr spFake;
											pNewReqsAll->Add(bsKey, pRequestAtom, &spFake);
										}
									}
								}
								else
									spRequestAtom->put_IndexOnly(VARIANT_FALSE);
							}
							else
							{
								pSynthUnd = dynamic_cast<CComObject<CMmRvUndAtom>*>(spSynthUnd.GetInterfacePtr());
								bsKey = _bstr_t(enContractType) + _bstr_t(L"_")  + pSynthUnd->m_bstrSymbol;
								if (pSynthUnd->m_bstrPrimaryExchangeCode.length())
									bsKey += _bstr_t(L".")+pSynthUnd->m_bstrPrimaryExchangeCode;
							}

							if(pSynthUnd->m_spSynthPos==NULL)
		                        pSynthUnd->m_spSynthPos = IMmRvPosCollPtr(__uuidof(MmRvPosColl));
							
							IMmRvPosAtomPtr spFake;
							pSynthUnd->m_spSynthPos->Add(pPosAtom->m_nID, bsKey, pPosAtom, &spFake);

							IMmRvSynthGreeksAtomPtr  spSynthGreek;
							pPosAtom->m_spSynthGreeks->Add(spSynthRootCompAtom->UndID, pPosAtom->m_bstrSymbol,NULL, &spSynthGreek);
							
							CComObject<CMmRvSynthGreeksAtom>* pSuAtom = dynamic_cast<CComObject<CMmRvSynthGreeksAtom>*>(spSynthGreek.GetInterfacePtr());
							if(pSuAtom)
							{
								pSuAtom->m_nContractID		  = pPosAtom->m_nID;
								pSuAtom->m_dDeliveryUnits     = spSynthRootCompAtom->Weight * pPosAtom->m_pQuote->m_nLotSize;
								pSuAtom->m_enContractType     = enContractType;
								pSuAtom->m_bstrSymbol		  = pPosAtom->m_bstrSymbol;
								pSuAtom->m_bstrSynthUndSymbol = pSynthUnd->m_bstrSymbol;
								pSuAtom->m_nSynthUndID		  = spSynthRootCompAtom->UndID;
								pSuAtom->m_bVisible			  = pPosAtom->m_bVisible;
								pSuAtom->m_bIsTotal			  = VARIANT_FALSE;
								pSuAtom->m_pSuPrice			  = pPosAtom->m_pQuote->m_pSuPrice;
								pSuAtom->m_spSuPrice		  = pPosAtom->m_pQuote->m_spSuPrice;
							}
							
							spSynthGreek = NULL;
							if(pUndAtom->m_spSynthGreeks==NULL)
								pUndAtom->m_spSynthGreeks = IMmRvSynthGreeksCollPtr(__uuidof(MmRvSynthGreeksColl));

							pUndAtom->m_spSynthGreeks->get_Item(spSynthRootCompAtom->UndID, &spSynthGreek);
							if(spSynthGreek == NULL)
							{
								pUndAtom->m_spSynthGreeks->Add(spSynthRootCompAtom->UndID, pSynthUnd->m_bstrSymbol, NULL, &spSynthGreek);
								CComObject<CMmRvSynthGreeksAtom>* pSuAtomGreek = dynamic_cast<CComObject<CMmRvSynthGreeksAtom>*>(spSynthGreek.GetInterfacePtr());
								if(pSuAtomGreek)
								{
									pSuAtomGreek->m_nContractID		   = pUndAtom->m_nID;
									pSuAtomGreek->m_dDeliveryUnits     = BAD_DOUBLE_VALUE;
									pSuAtomGreek->m_enContractType     = pUndAtom->m_enContractType;
									pSuAtomGreek->m_bstrSymbol		   = pSynthUnd->m_bstrSymbol;
									pSuAtomGreek->m_bstrSynthUndSymbol = pSynthUnd->m_bstrSymbol;
									pSuAtomGreek->m_nSynthUndID		   = spSynthRootCompAtom->UndID;
									pSuAtomGreek->m_bVisible		   = VARIANT_TRUE;
									pSuAtomGreek->m_bIsTotal		   = VARIANT_TRUE;
									pSuAtomGreek->m_pSuPrice		   = pPosAtom->m_pQuote->m_pSuPrice;
									pSuAtomGreek->m_spSuPrice		   = pPosAtom->m_pQuote->m_spSuPrice;
								}
							}
						}
                
					}
				}
			}
		}
		if(SUCCEEDED(hr))
			hr = S_OK;
	}
return hr;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT CMmRiskView::Refresh(RisksPosColumnEnum SortField, long lExpiryFilter, SAFEARRAY** arrAggregationCols, DOUBLE dUndPriceToleranceValue, EtsPriceRoundingRuleEnum enPriceRoundingRule)
{
	if (!m_pUnd) return S_OK;
	{
	CRowsData undRows, undGroupedRows;
	CMmRvUndColl::EnumCollType::iterator it = m_pUnd->m_coll.begin();
	CMmRvUndColl::EnumCollType::iterator itEnd = m_pUnd->m_coll.end();

	// create vector of underlying pointers
	for (;it != itEnd; ++it) {
		CMmRvUndAtom* pUndAtom = dynamic_cast<CMmRvUndAtom*>(it->second);
		if (!pUndAtom || pUndAtom->m_spSynthPos ) continue;		// skip underlying used for synthetic position
		CComObject<CMmRvRowData>* pRow = NULL;
		if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pRow)))	{
			IMmRvRowDataPtr spRowData;
			spRowData.Attach(pRow, TRUE);
			pRow->m_Type = RDT_UNDAGG;
			pRow->m_spUnd.Attach(pUndAtom, TRUE);
			pRow->m_pUnd = pUndAtom;
			pRow->m_pAgg.reset( static_cast<CMmRvAggData*>(pUndAtom), null_deleter());
			if (pRow->m_pUnd->m_spHeadComponent || pRow->m_pUnd->m_bIsHead)
				pRow->m_nLevel = 1;
			else
				pRow->m_nLevel = 0;

			undRows.insert(undRows.end(), spRowData);
		}
	}
	
	// sort underlying according to sort column
	std::sort( undRows.begin(), undRows.end(), CRiskViewFieldSort(m_SortColumn, m_SortOrder));

	// group by asset group
	long	lID, lRowCounter  = 0;
	CRowsData::iterator itrCurUnd = undRows.begin();
	CRowsData::iterator itrLastUnd = undRows.end();
	std::set<long> vInserted;
	std::set<long> vHeadInserted;

	for (; itrCurUnd != itrLastUnd; ++itrCurUnd) 
	{
		CMmRvRowData* pRow = static_cast<CMmRvRowData*>((*itrCurUnd).GetInterfacePtr());
		if (pRow && pRow->m_pUnd)
		{
			if (pRow->m_pUnd->m_bIsHead)
				lID = pRow->m_pUnd->m_nID;
			else if (pRow->m_pUnd->m_spHeadComponent)
				pRow->m_pUnd->m_spHeadComponent->get_ID(&lID);
			else
				lID = -1;

			if (lID	> 0)
			{
				CRowsData::iterator itrCurHead = itrCurUnd;

				for (; itrCurHead != itrLastUnd; ++itrCurHead)
				{
					CMmRvRowData* pCurRow = static_cast<CMmRvRowData*>((*itrCurHead).GetInterfacePtr());

					if (pCurRow && pCurRow->m_pUnd)
					{
						long	lCurUndID = pCurRow->m_pUnd->m_nID;
						if (lCurUndID == lID && vInserted.find(lCurUndID) == vInserted.end())
						{	
							if (vHeadInserted.find(lID) == vHeadInserted.end())
							{
								CComObject<CMmRvRowData>* pRow = NULL;
								CComObject<CMmRvUndAtom>* pUndAtom = NULL;
								if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pRow)) && SUCCEEDED(CComObject<CMmRvUndAtom>::CreateInstance(&pUndAtom)))
								{
									IMmRvUndAtomPtr spUndAtom;
									spUndAtom.Attach(pUndAtom, TRUE);

									IMmRvRowDataPtr spRowData;
									spRowData.Attach(pRow, TRUE);

									pRow->m_Type = RDT_UNDAGG;
									pRow->m_spUnd.Attach(pUndAtom, TRUE);
									pRow->m_pUnd = pUndAtom;
									pRow->m_pAgg.reset( static_cast<CMmRvAggData*>(pUndAtom), null_deleter());

									CComBSTR	sSymbol;
									pCurRow->m_pUnd->get_Symbol(&sSymbol);
									EtsContractTypeEnum	enCtType;
									pCurRow->m_pUnd->get_ContractType(&enCtType);

									_CHK(pCurRow->m_pUnd->get_ActiveFuture(&pRow->m_pUnd->m_spActiveFuture));

									IMmRvPricePtr pPrice;
									pCurRow->m_pUnd->get_Price(&pPrice);
									pPrice->get_Bid(&pUndAtom->m_pPrice->m_dPriceBid);
									pPrice->get_Ask(&pUndAtom->m_pPrice->m_dPriceAsk);
									pPrice->get_Last(&pUndAtom->m_pPrice->m_dPriceLast);
									pPrice->get_Active(&pUndAtom->m_pPrice->m_dActivePrice);
									pPrice->get_TheoClose(&pUndAtom->m_pPrice->m_dPriceTheoClose);
									pPrice->get_Close(&pUndAtom->m_pPrice->m_dPriceClose);
									pPrice->get_IsUseManualActive(&pUndAtom->m_pPrice->m_bManualActive);

									pRow->m_spUnd->put_Symbol(sSymbol);
									pRow->m_pUnd->Name_ = pRow->m_pUnd->m_bstrSymbol;
									pRow->m_pUnd->m_nID = lID;
									pRow->m_pUnd->m_enContractType = enCtType;
									pRow->m_pAgg->m_bIsHeadAggregation = VARIANT_TRUE;

									vHeadInserted.insert(lID);
									undGroupedRows.insert(undGroupedRows.begin() + lRowCounter, spRowData);
									++lRowCounter;
								}
							}
							vInserted.insert(lCurUndID);
							undGroupedRows.insert(undGroupedRows.begin() + lRowCounter, (*itrCurHead));
							++lRowCounter;
						}
						else if	(pCurRow->m_pUnd->m_spHeadComponent)
						{
							long	lHeadCompID = 0;
							pCurRow->m_pUnd->m_spHeadComponent->get_ID(&lHeadCompID);
							if (lHeadCompID == lID && vInserted.find(lCurUndID) == vInserted.end())
							{
								if (vHeadInserted.find(lID) == vHeadInserted.end())
								{
									CComObject<CMmRvRowData>* pRow = NULL;
									CComObject<CMmRvUndAtom>* pUndAtom = NULL;
									if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pRow)) && SUCCEEDED(CComObject<CMmRvUndAtom>::CreateInstance(&pUndAtom)))
									{
										IMmRvUndAtomPtr spUndAtom;
										spUndAtom.Attach(pUndAtom, TRUE);

										IMmRvRowDataPtr spRowData;
										spRowData.Attach(pRow, TRUE);
										pRow->m_Type = RDT_UNDAGG;
										pRow->m_spUnd.Attach(pUndAtom, TRUE);
										pRow->m_pUnd = pUndAtom;
										pRow->m_pAgg.reset( static_cast<CMmRvAggData*>(pUndAtom), null_deleter());
										pRow->m_nLevel = 0;

										CComBSTR	sSymbol;
										pCurRow->m_pUnd->m_spHeadComponent->get_Symbol(&sSymbol);
										EtsContractTypeEnum	enCtType;
										pCurRow->m_pUnd->m_spHeadComponent->get_ContractType(&enCtType);

										_CHK(pCurRow->m_pUnd->m_spHeadComponent->get_ActiveFuture(&pRow->m_pUnd->m_spActiveFuture));

										IMmRvPricePtr pPrice;
										pCurRow->m_pUnd->m_spHeadComponent->get_Price(&pPrice);
										pPrice->get_Bid(&pUndAtom->m_pPrice->m_dPriceBid);
										pPrice->get_Ask(&pUndAtom->m_pPrice->m_dPriceAsk);
										pPrice->get_Last(&pUndAtom->m_pPrice->m_dPriceLast);
										pPrice->get_Active(&pUndAtom->m_pPrice->m_dActivePrice);
										pPrice->get_TheoClose(&pUndAtom->m_pPrice->m_dPriceTheoClose);
										pPrice->get_Close(&pUndAtom->m_pPrice->m_dPriceClose);
										pPrice->get_IsUseManualActive(&pUndAtom->m_pPrice->m_bManualActive);


										pRow->m_spUnd->put_Symbol(sSymbol);
										pRow->m_pUnd->Name_ = pRow->m_pUnd->m_bstrSymbol;
										pRow->m_pUnd->m_nID = lID;
										pRow->m_pUnd->m_enContractType = enCtType;
										pRow->m_pAgg->m_bIsHeadAggregation = VARIANT_TRUE;

										vHeadInserted.insert(lID);
										undGroupedRows.insert(undGroupedRows.begin() + lRowCounter, spRowData);
										++lRowCounter;
									}
								}

								vInserted.insert(lCurUndID);
								undGroupedRows.insert(undGroupedRows.begin() + lRowCounter, (*itrCurHead));
								++lRowCounter;
							}
						}
					}
				}
			}
			else
			{
				undGroupedRows.insert(undGroupedRows.begin() + lRowCounter, (*itrCurUnd));
				++lRowCounter;
			}
		}
	}
	undRows.clear();


	// create rows
	itrCurUnd = undGroupedRows.begin();
	itrLastUnd = undGroupedRows.end();
	
	long nLevel = 0;
	m_Rows.clear();
	m_nOptPositions = 0;
	m_nUndPositions = 0;

	CMmRvAggData::MmRvAggDataPtr pHeadAgg;

	for (; itrCurUnd != itrLastUnd; ++itrCurUnd) {
		CMmRvRowData* pRow = static_cast<CMmRvRowData*>((*itrCurUnd).GetInterfacePtr());
		if (!pRow || !pRow->m_pUnd) continue;
		pRow->m_pUnd->VisiblePositions(true);

		if (pRow->m_pUnd->m_spHeadComponent || pRow->m_pUnd->m_bIsHead)	nLevel = 1;
		else nLevel = 0;

		pRow->m_pUnd->CreateRows( pRow->m_pUnd, lExpiryFilter, nLevel, &CRiskViewFieldSort(m_SortColumn, m_SortOrder), m_Rows, m_nOptPositions, m_nUndPositions, m_pUnd);

		if (pRow->m_pAgg->m_bIsHeadAggregation == VARIANT_TRUE)	pHeadAgg = pRow->m_pAgg;

		if (pRow->m_pUnd->m_bIsHead == VARIANT_TRUE || pRow->m_pUnd->m_spHeadComponent)
			pHeadAgg->AddAggregatedValues(pRow);
	}
	return S_OK;
	}
//	HRESULT hr = S_OK;
//	try
//	{
//		m_nOptPositions = 0;
//		m_nUndPositions = 0;
//		CRowsData _Rows;
//
//		m_Rows.clear();
//		if (m_pUnd)	{
//			CMmRvUndColl::EnumCollType::iterator it = m_pUnd->m_coll.begin();
//			CMmRvUndColl::EnumCollType::iterator itEnd = m_pUnd->m_coll.end();
//			for (;it != itEnd; ++it)	{
//				CMmRvUndAtom* pUndAtom = dynamic_cast<CMmRvUndAtom*>(it->second);
//				if (pUndAtom && pUndAtom->m_pPos && pUndAtom->m_pPos->m_coll.size())	{
//					CMmRvPosColl::EnumCollType::iterator  itPos    = pUndAtom->m_pPos->m_coll.begin();
//					CMmRvPosColl::EnumCollType::iterator  itPosEnd = pUndAtom->m_pPos->m_coll.end();
//					for (; itPos!=itPosEnd; ++itPos)	{
//						CMmRvPosAtom* pPos = dynamic_cast<CMmRvPosAtom*>(itPos->second);
//						if ( pPos ) 	{
//							if	(!lExpiryFilter || 
//								(
//								(	
//								enCtOption == pPos->m_enContractType || 
//								enCtFutOption == pPos->m_enContractType
//								) && pPos->m_nExpiryMonth == lExpiryFilter
//								)
//								)
//							{
//								pPos->m_bVisible = VARIANT_TRUE;
//								CComObject<CMmRvRowData>* pRow = NULL;
//								if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pRow)))	{
//									IMmRvRowDataPtr spRowData;
//									spRowData.Attach(pRow, TRUE);
//									pRow->m_spPos.Attach(pPos, TRUE);
//									pRow->m_pPos = pPos;
//									pRow->m_Type = RDT_POS;
//									pRow->m_spUnd.Attach(pUndAtom, TRUE);
//									pRow->m_pUnd = pUndAtom;
//									pRow->m_nLevel = ROL_POS;
//
//									switch(pPos->m_enContractType) {
//										case enCtOption:
//										case enCtFutOption:
//											++m_nOptPositions;
//											break;
//										case enCtStock:
//										case enCtIndex:
//										case enCtFuture:
//											++m_nUndPositions;
//											break;
//									}
//									_Rows.insert(_Rows.end(), spRowData);
//									/*if(VARIANT_TRUE == pPos->m_bIsSynthetic && pPos->m_spSynthGreeks!=NULL)
//										{
//											CMmRvSynthGreeksColl* pSynthColl = dynamic_cast<CMmRvSynthGreeksColl*>(pPos->m_spSynthGreeks.GetInterfacePtr());
//											ATLASSERT(pSynthColl);
//
//											if(pSynthColl)
//											{
//												CMmRvSynthGreeksColl::EnumCollType::iterator itrSynth    =  pSynthColl->m_coll.begin();
//												CMmRvSynthGreeksColl::EnumCollType::iterator itrSynthEnd =  pSynthColl->m_coll.end();
//												for(; itrSynth != itrSynthEnd; ++itrSynth)
//												{
//													CMmRvSynthGreeksAtom* pSynthAtom = dynamic_cast<CMmRvSynthGreeksAtom*>(itrSynth->second);
//													if(pSynthAtom)
//													{
//														CComObject<CMmRvRowData>* pSynthRow = NULL;
//														if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pSynthRow)))
//														{
//															IMmRvRowDataPtr spSynthRowData;
//															spSynthRowData.Attach(pSynthRow, TRUE);
//															pSynthRow->m_spPos.Attach(pPos, TRUE);
//															pSynthRow->m_pPos = pPos;
//															//*pRow->m_Type = RDT_POS;
//															pSynthRow->m_Type = RDT_POS;
//															pSynthRow->m_spUnd.Attach(pUndAtom, TRUE);
//															pSynthRow->m_pUnd = pUndAtom;
//															pSynthRow->m_spSynthGreeks.Attach(pSynthAtom, TRUE);
//															pSynthRow->m_pSynthGreeks = pSynthAtom;
//															pSynthRow->m_nLevel = ROL_POS;
//
//															pSynthAtom->m_bVisible = VARIANT_TRUE;
//															_Rows.insert(_Rows.end(), spSynthRowData);
//														}
//													}
//												}
//											}
//										}*/
//								}
//							}
//							else
//								pPos->m_bVisible = VARIANT_FALSE;
//						}
//					}
//				}
//			}
//
//			
//			// retrieve aggregation columns
//			long lUpperBound = 0;
//			long lLowerBound = 0;
//			std::vector<RisksPosColumnEnum>	vecAggregations;
//			CComSafeArray<LONG> lArray(*arrAggregationCols);
//			void* pData = reinterpret_cast<LPVOID> (*arrAggregationCols);
//			if (pData) {
//				lUpperBound = lArray.GetUpperBound();
//				lLowerBound = lArray.GetLowerBound();
//				vecAggregations.reserve(lUpperBound - lLowerBound);
//				for (int i = lLowerBound; i < lUpperBound; i++ )
//					vecAggregations.insert( vecAggregations.end(), static_cast<RisksPosColumnEnum>(lArray[i]) );
//			}
//			std::sort(_Rows.begin(), _Rows.end(), CRiskViewSort( enSortDescending, vecAggregations));
//
//			if ( !_Rows.empty()){
//				m_Rows.reserve(_Rows.size() * vecAggregations.size() + 1 );
//				m_Rows.insert( m_Rows.begin(), _Rows.begin(), _Rows.end() );
//			}
//
//			
//			// make Aggregation
//			if (! m_Rows.empty() && !vecAggregations.empty() ) {
//				
//
//				CRowsData	*pSrc, *pDst, *pTmp;
//
//				_Rows.clear();
//				pSrc = &_Rows;
//				pDst = &m_Rows;
//
//				IMmRvRowDataPtr	spRowData;
//				IMmRvRowDataPtr	spPrevRowData = NULL;
//				CRowsData	tmpV;
//				
//				// for every aggregation field, starting from last field
//				for ( size_t i = vecAggregations.size() - 1; i != size_t(0-1); i-- ) {
//
//					// swap working vectors
//					pTmp = pSrc; pSrc = pDst; pDst = pTmp;
//					pDst->clear();		// clear destination
//
//					// will iterate through rows, backwards
//					CRowsData::reverse_iterator rAggregate = pSrc->rbegin();
//					CRowsData::reverse_iterator rLastInAggregation = rAggregate;
//
//					CMmRvRowData* pRowData = NULL;
//					CRiskViewFieldSort	FieldCmp( vecAggregations[i], enSortDescending );
//					spPrevRowData = NULL;
//
//					while(rAggregate != pSrc->rend())	{
//
//						// get row
//						pRowData = dynamic_cast<CMmRvRowData*>((*rAggregate).GetInterfacePtr());
//						spRowData = *rAggregate;
//
//						if ( !pRowData || pRowData->m_Type == RDT_AGG || pRowData->m_Type == RDT_UNDAGG){
//							if ( !pRowData || !spRowData)
//								continue;	// skip errors
//
//							// put aggregation row into destination vector 
//							pDst->insert(pDst->begin(), spRowData );
//
//							// get next row
//							rAggregate++;
//							continue;	
//						}
//						
//						// if this is not a first row to check
//						if (spPrevRowData) {	
//
//							// does it have same aggregation field as previous one?
//							if ( FieldCmp.CompareFields(vecAggregations[i], spRowData, spPrevRowData) ) {
//								// no, starting new aggregation
//								//  create aggregation by field vecAggregations[i], starting 
//								//  from rLastInAggregation to rAggregate
//								IMmRvRowDataPtr spAggRowData;
//								AggregateRows( spAggRowData, rLastInAggregation, rAggregate, vecAggregations[i], (unsigned )i, dUndPriceToleranceValue, enPriceRoundingRule);
//								CMmRvRowData *pRow = dynamic_cast<CMmRvRowData *>(spAggRowData.GetInterfacePtr() );
//								if ( spAggRowData ){
//									if ( pRow ) {
//										if ( pRow->m_Type == RDT_AGG ) {
//											if(!pRow->m_pAggregation->m_bstrSymbol.length())pRow->m_pAggregation->m_bstrSymbol = _bstr_t(L"�") ;
//											if(pRow->m_pAggregation /*&& pRow->m_pAggregation->m_bstrSymbol.length()*/ )
//												pDst->insert(pDst->begin(), spAggRowData ); // insert aggregation only it has a value
//										}
//										else
//											pDst->insert(pDst->begin(), spAggRowData );
//									}
//								}
//								spPrevRowData = spRowData;
//								rLastInAggregation = rAggregate;
//								pDst->insert(pDst->begin(), spRowData );
//							}
//							else{
//								// fields are identical, insure that this row has same values for all
//								// aggregation fields
//								std::vector<RisksPosColumnEnum>	vecTmpAgg; // compare only fields not aggregated yet
//								vecTmpAgg.insert	(
//															vecTmpAgg.begin(),
//															vecAggregations.begin(), 
//															vecAggregations.begin() + i + 1
//														);
//								if ( 
//										CRiskViewSort	(
//																enSortDescending, vecTmpAgg
//															).CompareFields(spPrevRowData, spRowData) 
//									) {
//									// this row is for other aggregation
//									// create aggregation and continue with new one
//									IMmRvRowDataPtr spAggRowData;
//									AggregateRows( spAggRowData, rLastInAggregation, rAggregate, vecAggregations[i], (unsigned )i, dUndPriceToleranceValue, enPriceRoundingRule);
//									CMmRvRowData *pRow = dynamic_cast<CMmRvRowData *>(spAggRowData.GetInterfacePtr() );
//									if ( spAggRowData ){
//										if ( pRow ) {
//											if ( pRow->m_Type == RDT_AGG ) {
//												if(!pRow->m_pAggregation->m_bstrSymbol.length())pRow->m_pAggregation->m_bstrSymbol = _bstr_t(L"�");
//												if(pRow->m_pAggregation /*&& pRow->m_pAggregation->m_bstrSymbol.length()*/ )
//													pDst->insert(pDst->begin(), spAggRowData ); // insert aggregation only if it has a value
//											}
//											else
//												pDst->insert(pDst->begin(), spAggRowData );
//										}
//									}
//									
//									spPrevRowData = spRowData;
//									rLastInAggregation = rAggregate;
//									pDst->insert(pDst->begin(), spRowData );
//								}
//								else{
//									// this row goes into the same aggregation as previous one
//									spPrevRowData = spRowData;
//									pDst->insert(pDst->begin(), spRowData );
//								}
//							}
//						}
//						else	{					// this is first row - just put it into destination vector
//							spPrevRowData = spRowData;
//							rLastInAggregation = rAggregate;
//							pDst->insert(pDst->begin(), spRowData );
//						}
//						rAggregate++;			// get previous row
//					}
//
//					// create aggregation for first row in vector 
//					if ( i != size_t(0-1) && vecAggregations[i] ) {
//						IMmRvRowDataPtr spAggRowData;
//						AggregateRows( spAggRowData, rLastInAggregation, rAggregate, vecAggregations[i], (unsigned )i, dUndPriceToleranceValue, enPriceRoundingRule);
//						CMmRvRowData *pRow = dynamic_cast<CMmRvRowData *>(spAggRowData.GetInterfacePtr() );
//						if ( spAggRowData ){
//							if ( pRow ) {
//								if ( pRow->m_Type == RDT_AGG ) {
//									if(!pRow->m_pAggregation->m_bstrSymbol.length())pRow->m_pAggregation->m_bstrSymbol = _bstr_t(L"�");
//									if(pRow->m_pAggregation /*&& pRow->m_pAggregation->m_bstrSymbol.length()*/ )
//										pDst->insert(pDst->begin(), spAggRowData ); // insert aggregation only it has a value
//									/*else
//										DecreaseOutline(rLastInAggregation, rAggregate);*/
//								}
//								else
//									pDst->insert(pDst->begin(), spAggRowData );
//							}
//						}
//						spPrevRowData = NULL;
//					}
//				}
//				if ( &m_Rows != pDst ) {
//					m_Rows.clear();
//					m_Rows.insert( m_Rows.end(), pDst->begin(), pDst->end() );
//				}
//			}
//
//
//			
//			// perform tricky sort
//			CRowsData underlyingAggregations,futureAgg, expiryAgg,Positions;
//			std::map< unsigned , CRowsData > mapUnd2FutAggs, mapFut2ExpAggs, mapExpAgg2Pos;
//			unsigned nUndMapKey = 0, nFutMapKey = 0, nExpMapKey = 0;
//			for (CRowsData::iterator itrCurrent = m_Rows.begin(), itrEnd = m_Rows.end(); itrCurrent != itrEnd; ++itrCurrent) {
//				CMmRvRowData *pRowData = dynamic_cast<CMmRvRowData*>((*itrCurrent).GetInterfacePtr() );
//				if (!pRowData) continue;
//				if ( pRowData->m_Type == RDT_UNDAGG) {
//					underlyingAggregations.push_back(*itrCurrent);
//					pRowData->m_nMapKey = ++nUndMapKey;
//					futureAgg.clear();
//					mapUnd2FutAggs[nUndMapKey] = futureAgg;
//				}
//				else if ( pRowData->m_Type == RDT_AGG ) {
//					if	(
//							( pRowData->m_pUnd && pRowData->m_pUnd->m_enContractType == enCtStock ) 
//							||
//							(
//								pRowData->m_pUnd && 
//								pRowData->m_pUnd->m_enContractType == enCtIndex && 
//								!pRowData->m_pUnd->m_spFut
//							)
//						) 
//						continue;
//					// start new aggregation within same underlying
//					if (pRowData->m_nLevel == 1){
//						pRowData->m_nMapKey = ++nFutMapKey;
//						expiryAgg.clear();
//						mapUnd2FutAggs[nUndMapKey].push_back(*itrCurrent);
//					}
//					else{
//						pRowData->m_nMapKey = ++nExpMapKey;
//						Positions.clear();
//						mapFut2ExpAggs[nFutMapKey].push_back(*itrCurrent);
//					}
//				}
//				else if( pRowData->m_pPos ){
//					if	(
//							( pRowData->m_pUnd && pRowData->m_pUnd->m_enContractType == enCtStock)
//							||
//							(
//								pRowData->m_pUnd && 
//								pRowData->m_pUnd->m_enContractType == enCtIndex && 
//								!pRowData->m_pUnd->m_spFut
//							)
//						) 
//						mapUnd2FutAggs[nUndMapKey].push_back(*itrCurrent);
//					else
//						mapExpAgg2Pos[nExpMapKey].push_back(*itrCurrent);
//				}
//			}
//
//			m_Rows.clear();
//			// sort positions within every expiry aggregation
//			for ( std::map< unsigned , CRowsData >::iterator itrPC = mapFut2ExpAggs.begin();  itrPC != mapFut2ExpAggs.end(); itrPC++)
//				std::sort( mapExpAgg2Pos[itrPC->first].begin(), mapExpAgg2Pos[itrPC->first].end(), CRiskViewFieldSort(m_SortColumn, m_SortOrder));
//
//			// sort expiry aggregation within every future aggregation
//			for ( std::map< unsigned , CRowsData >::iterator itrFC = mapUnd2FutAggs.begin();  itrFC != mapUnd2FutAggs.end(); itrFC++)
//				std::sort( mapFut2ExpAggs[itrFC->first].begin(), mapFut2ExpAggs[itrFC->first].end(), CRiskViewFieldSort(m_SortColumn, m_SortOrder));
//
//			// sort future aggregations within every underlying
//			for ( CRowsData::iterator itrUC = underlyingAggregations.begin();  itrUC != underlyingAggregations.end(); itrUC++){
//				CMmRvRowData *pRowData = dynamic_cast<CMmRvRowData*>((*itrUC).GetInterfacePtr() );
//				if(!pRowData ) continue;
//				std::sort( mapUnd2FutAggs[pRowData->m_nMapKey].begin(), mapUnd2FutAggs[pRowData->m_nMapKey].end(), CRiskViewFieldSort(m_SortColumn, m_SortOrder));
//			}
//
//			// sort underlying list
//			std::sort( underlyingAggregations.begin(), underlyingAggregations.end(), CRiskViewFieldSort(m_SortColumn, m_SortOrder));
//
//			for (CRowsData::iterator itrUC = underlyingAggregations.begin();  itrUC != underlyingAggregations.end(); itrUC++) {
//				m_Rows.push_back( *itrUC );
//				CMmRvRowData *pURowData = dynamic_cast<CMmRvRowData*>((*itrUC).GetInterfacePtr() );
//				if(!pURowData ) continue;
//				for (CRowsData::iterator itrFC = mapUnd2FutAggs[pURowData->m_nMapKey].begin();  itrFC != mapUnd2FutAggs[pURowData->m_nMapKey].end(); itrFC++) {
//					m_Rows.push_back( *itrFC );
//					CMmRvRowData *pFRowData = dynamic_cast<CMmRvRowData*>((*itrFC).GetInterfacePtr() );
//					if(!pFRowData ) continue;
//					for (CRowsData::iterator itrEC = mapFut2ExpAggs[pFRowData->m_nMapKey].begin();itrEC != mapFut2ExpAggs[pFRowData->m_nMapKey].end(); itrEC++) {
//						m_Rows.push_back( *itrEC );
//						CMmRvRowData *pERowData = dynamic_cast<CMmRvRowData*>((*itrEC).GetInterfacePtr() );
//						if(!pERowData ) continue;
//						for (CRowsData::iterator itrPC = mapExpAgg2Pos[pERowData->m_nMapKey].begin();itrPC != mapExpAgg2Pos[pERowData->m_nMapKey].end(); itrPC++) 
//							m_Rows.push_back( *itrPC );
//					}
//				}
//			}
//
//			//m_Rows.reserve(underlyingAggregations.size() );
//			//m_Rows.clear();
//			//m_Rows.insert( m_Rows.begin(), underlyingAggregations.begin(), underlyingAggregations.end() );
//
//
//			/*for (; itrCurrent != itrEnd; ++itrCurrent) {
//				CMmRvRowData *pRowData = dynamic_cast<CMmRvRowData*>((*itrCurrent).GetInterfacePtr() );
//				if (pRowData) {
//					pRowData->GetField(m_SortColumn, keyFieldValue, true);
//					if ( pRowData->m_Type == RDT_UNDAGG && pRowData->m_pUnd) {
//						// start new underlying
//						if (utils::HasValue(keyFieldValue) ){ 
//							undKeyValue = _bstr_t(keyFieldValue);
//							undKeyValue += pRowData->m_pUnd->m_bstrSymbol;
//						}
//						else{
//							undKeyValue = _bstr_t(L" ");
//							undKeyValue += pRowData->m_pUnd->m_bstrSymbol;
//						}
//						// save key value
//						pRowData->m_bstrSortKey = undKeyValue;
//					}
//					else if ( pRowData->m_Type == RDT_AGG && pRowData->m_pAggregation) {
//						// start new aggregation within same underlying
//						if (pRowData->m_nLevel == 1)
//							aggKeyValue = undKeyValue;
//						else{
//							aggKeyValue = lvl1AggKeyValue;
//							aggKeyValue += _bstr_t(L"�");
//						}
//
//						if (utils::HasValue(keyFieldValue) ){ 
//							aggKeyValue += _bstr_t(keyFieldValue);
//							aggKeyValue += pRowData->m_pAggregation->m_bstrSymbol;
//						}
//						else{
//							aggKeyValue = _bstr_t(L" ");
//							aggKeyValue += pRowData->m_pAggregation->m_bstrSymbol;
//						}
//							
//						// save key value
//						if (pRowData->m_nLevel == 1)
//							lvl1AggKeyValue = aggKeyValue;
//						pRowData->m_bstrSortKey = aggKeyValue;
//					}
//					else if( pRowData->m_pPos ){
//						// position within same aggregation within same underlying
//						//posKeyValue = undKeyValue;
//						posKeyValue = aggKeyValue;
//						if (utils::HasValue(keyFieldValue) ){ 
//							posKeyValue += _bstr_t(keyFieldValue);
//							posKeyValue += pRowData->m_pPos->m_bstrSymbol;
//						}
//						else{
//							posKeyValue = _bstr_t(L" ");
//							posKeyValue += pRowData->m_pPos->m_bstrSymbol;
//						}
//						// save key value
//						pRowData->m_bstrSortKey = posKeyValue;
//					}
//				}
//			}
//			std::sort(m_Rows.begin(), m_Rows.end(), CMmRiskViewSort(m_SortOrder));
//
//			if (m_SortOrder == enSortAscending) {
//				std::vector<std::pair<CRowsData::iterator, CRowsData::iterator> >	undAggVector;
//				CRowsData::iterator itrC = m_Rows.begin();
//				CRowsData::iterator itrE = m_Rows.end();
//				CRowsData::iterator itrFirstPosInAgg = itrC;
//				bool bStartNew= true;
//				for (; itrC != itrE; ++itrC) {
//					CMmRvRowData *pRowData = dynamic_cast<CMmRvRowData*>((*itrC).GetInterfacePtr() );
//					if (!pRowData) continue;
//					if (pRowData->m_Type != RDT_UNDAGG && bStartNew) {
//						itrFirstPosInAgg = itrC;
//						bStartNew = false;
//					}
//					else if(pRowData->m_Type == RDT_UNDAGG ){
//						undAggVector.push_back(std::pair<CRowsData::iterator, CRowsData::iterator>(itrFirstPosInAgg, itrC + 1));
//						bStartNew = true;
//					}
//				}
//				for ( std::vector<std::pair<CRowsData::iterator, CRowsData::iterator> >::iterator iC = undAggVector.begin();
//					iC != undAggVector.end(); iC++) {
//					
//					size_t undVecPosCntr = iC->second - iC->first;
//					
//
//					// rise current row
//					
//					/*if (pCurRowData->m_nLevel < pRow2CmpData->m_nLevel ) {
//					}*/
//				/*	size_t undVecCurPos = 1;
//					bool bRise;
//					while(1){
//						CRowsData::iterator itrCurRow = iC->second - undVecCurPos;
//						bRise = false;
//						while ( 1 ) {
//							if (itrCurRow == iC->first) 
//								break;
//							CMmRvRowData *pCurRowData = dynamic_cast<CMmRvRowData*>((*itrCurRow).GetInterfacePtr() );
//							CMmRvRowData *pRow2CmpData = dynamic_cast<CMmRvRowData*>((*(itrCurRow-1)).GetInterfacePtr() );
//							if (pCurRowData->m_nLevel < pRow2CmpData->m_nLevel) {
//								std::swap( *itrCurRow, *(itrCurRow-1));
//								bRise = true;
//							}
//							else
//								break;
//							itrCurRow--;
//						}
//						if( !bRise )
//							undVecCurPos++;
//						if (undVecCurPos > undVecPosCntr) 
//							break;
//					}
//					size_t currentUndVecSize = iC->second - iC->first;
//				}
//			}
//			
//*/
//			// build rows for synthetic positions and remove empty aggregations
//			CRowsData tmpVector;
//			_bstr_t emptyAgg(L"�"), spotAgg(L"Spot");
//			bool bDecreaseOutline = false;
//			size_t spotPos = 0;
//			for ( CRowsData::iterator itrCurrent= m_Rows.begin(), itrEnd = m_Rows.end(); itrCurrent != itrEnd; ++itrCurrent) {
//				CMmRvRowData *pRowData = dynamic_cast<CMmRvRowData*>((*itrCurrent).GetInterfacePtr() );
//				if ( pRowData->m_Type == RDT_AGG && pRowData->m_pAggregation->m_bstrSymbol ==  emptyAgg) {
//					bDecreaseOutline = true;
//				}
//				else{
//					if (pRowData->m_Type == RDT_AGG && pRowData->m_nLevel == 1) {
//						tmpVector.push_back( *itrCurrent);
//						spotPos = tmpVector.size();
//					}
//					else if (bDecreaseOutline) {
//						bDecreaseOutline = false;
//						tmpVector.insert(tmpVector.begin() + spotPos,  *itrCurrent );
//					}
//					else
//						tmpVector.push_back( *itrCurrent);		// copy row
//					if ( pRowData && pRowData->m_Type == RDT_POS && pRowData->m_pPos ) {
//						CMmRvPosAtom* pPos = pRowData->m_pPos;
//						if(VARIANT_TRUE == pPos->m_bIsSynthetic && pPos->m_spSynthGreeks!=NULL)	{
//							CMmRvSynthGreeksColl* pSynthColl = dynamic_cast<CMmRvSynthGreeksColl*>(pPos->m_spSynthGreeks.GetInterfacePtr());
//							ATLASSERT(pSynthColl);
//							if(pSynthColl) {
//								CMmRvSynthGreeksColl::EnumCollType::iterator itrSynth    =  pSynthColl->m_coll.begin();
//								CMmRvSynthGreeksColl::EnumCollType::iterator itrSynthEnd =  pSynthColl->m_coll.end();
//								for(; itrSynth != itrSynthEnd; ++itrSynth) {
//									CMmRvSynthGreeksAtom* pSynthAtom = dynamic_cast<CMmRvSynthGreeksAtom*>(itrSynth->second);
//									if(pSynthAtom)	{
//										CComObject<CMmRvRowData>* pSynthRow = NULL;
//										if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pSynthRow))) 	{
//											IMmRvRowDataPtr spSynthRowData;
//											spSynthRowData.Attach(pSynthRow, TRUE);
//											pSynthRow->m_spPos.Attach(pPos, TRUE);
//											pSynthRow->m_pPos = pPos;
//											pSynthRow->m_Type = RDT_POS;
//											pSynthRow->m_spUnd = pRowData->m_spUnd;
//											pSynthRow->m_pUnd = pRowData->m_pUnd;
//											pSynthRow->m_spSynthGreeks.Attach(pSynthAtom, TRUE);
//											pSynthRow->m_pSynthGreeks = pSynthAtom;
//											pSynthRow->m_nLevel = pRowData->m_nLevel+1;
//											pSynthAtom->m_bVisible = VARIANT_TRUE;
//											tmpVector.push_back( spSynthRowData );		// add row for synthetic position
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//
//			m_Rows.reserve(tmpVector.size() );
//			m_Rows.clear();
//			m_Rows.insert( m_Rows.begin(), tmpVector.begin(), tmpVector.end() );
//		}
//	}
//	catch (_com_error& err)
//	{
//		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(err), __uuidof(IMmRiskView), err.Error());
//
//	}
//	return hr;
}
/*
void	CMmRiskView::AggregateRows	(
													IMmRvRowDataPtr& spAggRowData,
													CRowsData::reverse_iterator& itrFirst, 
													CRowsData::reverse_iterator& itrLast,
													RisksPosColumnEnum aggClmn,
													unsigned outlineLevel,
													DOUBLE dUndPriceToleranceValue, 
													EtsPriceRoundingRuleEnum enPriceRoundingRule
											){
	LONG nMultiplier = 1;
	if ( aggClmn == RPC_UND ) {
		// aggregation by underlying would be done in a special way

		// every row in range [itrFirst-itrLast) points to his CRvUndAtom
		// which in turn is an aggregation by underlying for these rows, so just
		// create row for this underlying aggregation and attach atom to it
		CComObject<CMmRvRowData>* pRow = NULL;
		if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pRow))) {
			CMmRvRowData* pRowInAgg = dynamic_cast<CMmRvRowData*>((*itrFirst).GetInterfacePtr());
			spAggRowData.Attach(pRow, TRUE);
			pRow->m_pUnd = pRowInAgg->m_pUnd;
			pRow->m_spUnd = pRowInAgg->m_spUnd;
			pRow->m_Type = RDT_UNDAGG;
			pRow->m_nLevel = outlineLevel;
			return;
		}
		else{
			spAggRowData = NULL;
			return;
		}
	}
	if ( aggClmn == RPC_FUTURES ) {
		// aggregation by future symbol
		shared_ptr<__MmRvAggregationData>	spAggData( new __MmRvAggregationData );
		CComObject<CMmRvRowData>* pRow = NULL;
		if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pRow))) {
			CMmRvRowData* pRowInAgg = dynamic_cast<CMmRvRowData*>((*itrFirst).GetInterfacePtr());
			CMmRvFutAtom* pFut = NULL;
			spAggRowData.Attach(pRow, TRUE);
			pRow->m_pAggregation = spAggData;
			pRow->m_pUnd = pRowInAgg->m_pUnd;
			pRow->m_spUnd = pRowInAgg->m_spUnd;
			pRow->m_Type = RDT_AGG;
			pRow->m_nLevel = outlineLevel;
			if ( pRowInAgg->m_pPos && pRowInAgg->m_pPos->m_spFut ) {
				pFut = dynamic_cast<CMmRvFutAtom *>(pRowInAgg->m_pPos->m_spFut.GetInterfacePtr() );
				if( pFut ) {
					pRow->m_pAggregation->m_bstrSymbol = pFut->m_bstrSymbol;
					pRow->m_pAggregation->m_dtFutMaturity = pFut->m_dtMaturity;
					pRow->m_pAggregation->m_pFut = pFut;
					//pRow->m_pAggregation->m_pPrice = pFut->m_p
				}
			}
			else{
				pRow->m_pAggregation->m_bstrSymbol = L"Spot";
			}
			Aggregate( spAggData, itrFirst, itrLast, aggClmn, outlineLevel  + 1, dUndPriceToleranceValue, enPriceRoundingRule);
			if( pFut ){
				if(pRow->m_pUnd->m_enContractType == enCtFutUnd){
					DATE dtExpiry;
					pFut->get_Maturity(&dtExpiry);
					if(dtExpiry >= vt_date::GetCurrentDate(true))
					{
						//NetDelta
						if(!pFut->m_bMultOptDltEq)
							nMultiplier = pFut->m_nFutLotSize;
						pRow->m_pAggregation->m_dNetDelta = spAggData->m_nFutQty*nMultiplier + pRow->m_pAggregation->m_dNetDelta;

						//DeltaEq
						if(pRow->m_pAggregation->m_dDeltaEq <= BAD_DOUBLE_VALUE &&
							spAggData->m_nFutQty * pFut->m_dKEq * pFut->m_dUndMidPrice)
							pRow->m_pAggregation->m_dDeltaEq = 0.;
		
						pRow->m_pAggregation->m_dDeltaEq = spAggData->m_nFutQty * pFut->m_dKEq * pFut->m_dUndMidPrice + pRow->m_pAggregation->m_dDeltaEq;
					}
					else
					{
						pRow->m_pAggregation->m_dNetDelta = BAD_DOUBLE_VALUE;
						pRow->m_pAggregation->m_bBadNetDelta = VARIANT_TRUE;
					}
				}
				else
				{
					//pRow->m_pAggregation->m_dNetDelta = spAggData->m_nFutQty*pFut->m_dK + pRow->m_pAggregation->m_dNetDelta;
					DATE dtExpiry;
					pFut->get_Maturity(&dtExpiry);
					if(dtExpiry >= vt_date::GetCurrentDate(true))
					{
						//NetDelta
						pRow->m_pAggregation->m_dNetDelta = 
							spAggData->m_nFutQty * pFut->m_nFutLotSize * pFut->m_dK + pRow->m_pAggregation->m_dNetDelta;
						//DeltaEq
						EtsReplacePriceStatusEnum	dummy;
						VARIANT_BOOL	futureUsed = VARIANT_FALSE;
						DOUBLE dUndPrice;
						pRow->m_pUnd->GetUnderlyingPrice(dUndPriceToleranceValue, enPriceRoundingRule, &dummy, &futureUsed, &dUndPrice);
						if(dUndPrice > DBL_EPSILON)
						{
							pRow->m_pAggregation->m_dDeltaEq = 
									spAggData->m_nFutQty * pFut->m_nFutLotSize * dUndPrice + 
									(pRow->m_pAggregation->m_dDeltaEq > BAD_DOUBLE_VALUE ? pRow->m_pAggregation->m_dDeltaEq : 0);
						}
						else
						{
							pRow->m_pAggregation->m_dDeltaEq = BAD_DOUBLE_VALUE;
							pRow->m_pAggregation->m_bBadDeltaEq = VARIANT_TRUE;
						}
					}
					else
					{
						pRow->m_pAggregation->m_dNetDelta = BAD_DOUBLE_VALUE;
						pRow->m_pAggregation->m_bBadNetDelta = VARIANT_TRUE;
					}
				}
			}
			return;
		}
		else{
			spAggRowData = NULL;
			return;
		}

	}
	// create aggregation row
	shared_ptr<__MmRvAggregationData>	spAggData( new __MmRvAggregationData );
	CComObject<CMmRvRowData>* pRow = NULL;
	if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pRow))) {
		spAggRowData.Attach(pRow, TRUE);
		pRow->m_pAggregation = spAggData;
		pRow->m_Type = RDT_AGG;
		pRow->m_nLevel = outlineLevel;
		CMmRvRowData* pRowInAgg = dynamic_cast<CMmRvRowData*>((*itrFirst).GetInterfacePtr());
		pRow->m_pUnd = pRowInAgg->m_pUnd;
		pRow->m_spUnd = pRowInAgg->m_spUnd;
	}
	else{
		spAggRowData = NULL;
		return;
	}

	// perform aggregation
	switch(aggClmn) {
		case RPC_EXPIRY:
		case RPC_FUT_MATURITY:
			AggregateByDate( spAggData, itrFirst, itrLast, aggClmn, outlineLevel + 1, dUndPriceToleranceValue, enPriceRoundingRule);
			break;
		default:
			Aggregate( spAggData, itrFirst, itrLast, aggClmn, outlineLevel + 1);
	}
	return;
	
}


void	CMmRiskView::AggregateByDate	(
								 					shared_ptr<__MmRvAggregationData>& spAgg,
								 					CRowsData::reverse_iterator& itrFirst,
								 					CRowsData::reverse_iterator& itrLast,
								 					RisksPosColumnEnum aggClmn,
													unsigned outlineLevel,
													DOUBLE dUndPriceToleranceValue, 
													EtsPriceRoundingRuleEnum enPriceRoundingRule
												){
	CMmRvRowData* pRow = NULL;
	double	dInternalEqDelta;

	for ( ; itrFirst != itrLast; itrFirst++ ) {
		pRow = dynamic_cast<CMmRvRowData*>((*itrFirst).GetInterfacePtr() );
		if( !pRow ) continue;
		if ( pRow->m_nLevel < outlineLevel ) 
			pRow->m_nLevel = outlineLevel;		// outline only if row not yet outlined already
		// setup underlying for aggregation only once
		if ( !spAgg->m_pUnd) {
			if ( pRow->m_spUnd ) {
				spAgg->m_spUnd = pRow->m_spUnd;
				spAgg->m_pUnd = pRow->m_pUnd;
			}
		}
		if (!( pRow->m_Type == RDT_AGG ||  pRow->m_Type == RDT_UNDAGG) ) {
			if ( !pRow->m_pPos ) continue;
			if ( pRow->m_pPos->m_dPnlTheo > BAD_DOUBLE_VALUE){
				if ( spAgg->m_dPnlTheo == BAD_DOUBLE_VALUE ) spAgg->m_dPnlTheo = 0.;
				spAgg->m_dPnlTheo += pRow->m_pPos->m_dPnlTheo;
			}
			if ( pRow->m_pPos->m_dPnlMtm > BAD_DOUBLE_VALUE){
				if ( spAgg->m_dPnlMtm == BAD_DOUBLE_VALUE ) spAgg->m_dPnlMtm = 0.;
				spAgg->m_dPnlMtm += pRow->m_pPos->m_dPnlMtm;
			}
			if ( pRow->m_pPos->m_nQty > BAD_LONG_VALUE ){
				if (	pRow->m_pPos->m_enContractType == enCtFutOption ||
						pRow->m_pPos->m_enContractType == enCtOption 
					){
					if(spAgg->m_nOptQty <= BAD_LONG_VALUE) spAgg->m_nOptQty = 0L;
					spAgg->m_nOptQty += pRow->m_pPos->m_nQty;
				}
				else if(pRow->m_pPos->m_enContractType == enCtFuture ){
					if(spAgg->m_nFutQty <= BAD_LONG_VALUE) spAgg->m_nFutQty = 0L;
					spAgg->m_nFutQty += pRow->m_pPos->m_nQty;
					if(spAgg->m_nQty <= BAD_LONG_VALUE) spAgg->m_nQty = 0L;
					spAgg->m_nQty += (pRow->m_pPos->m_nQty * pRow->m_pPos->m_pQuote->m_nLotSize);
				}
				else{
					if(spAgg->m_nQty <= BAD_LONG_VALUE) spAgg->m_nQty = 0L;
					spAgg->m_nQty += pRow->m_pPos->m_nQty;
				}
			}
			if (pRow->m_pPos->m_pQuote->m_dDelta > BAD_DOUBLE_VALUE) {
				if(spAgg->m_dDeltaP <= BAD_DOUBLE_VALUE) spAgg->m_dDeltaP = 0.;
				spAgg->m_dDeltaP += pRow->m_pPos->m_pQuote->m_dDelta;
			}
			if(pRow->m_pPos->m_dDeltaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dOptDelta <= BAD_DOUBLE_VALUE) spAgg->m_dOptDelta = 0.;
				spAgg->m_dOptDelta += pRow->m_pPos->m_dDeltaInShares;
				//if(spAgg->m_dNetDelta <= BAD_DOUBLE_VALUE) spAgg->m_dNetDelta = 0.;
				//spAgg->m_dNetDelta += pRow->m_pPos->m_dDeltaInShares;
				if(pRow->m_pPos->m_dUndPriceSave > DBL_EPSILON)
				{
					if(spAgg->m_dDeltaEq <= BAD_DOUBLE_VALUE) spAgg->m_dDeltaEq = 0.;
					{
						if(spAgg->m_dOptDeltaEq <= BAD_DOUBLE_VALUE) spAgg->m_dOptDeltaEq = 0.;

						dInternalEqDelta = pRow->m_pPos->m_dDeltaInShares * pRow->m_pPos->m_dUndPriceSave;
						if(pRow->m_pUnd->m_enContractType != enCtFutUnd)
							spAgg->m_dDeltaEq += pRow->m_pPos->m_dInternalEqDelta;
						spAgg->m_dOptDeltaEq += pRow->m_pPos->m_dInternalEqDelta;
					}
				}
				else
				{
					spAgg->m_bBadDeltaEq = VARIANT_TRUE;
					spAgg->m_bBadOptDeltaEq = VARIANT_TRUE;
				}
			}
			else
			{
				spAgg->m_bBadNetDelta = VARIANT_TRUE;
				spAgg->m_bBadOptDelta = VARIANT_TRUE;
				spAgg->m_bBadDeltaEq = VARIANT_TRUE;
			}
			//m_dGammaEq
			//m_dGammaPerc
			if(pRow->m_pPos->m_dGammaInSharesPerc > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dGammaPerc <= BAD_DOUBLE_VALUE) spAgg->m_dGammaPerc = 0.;
				spAgg->m_dGammaPerc += pRow->m_pPos->m_dGammaInSharesPerc;
				if(pRow->m_pPos->m_dUndPriceSave > DBL_EPSILON)
				{
					if(spAgg->m_dGammaEq <= BAD_DOUBLE_VALUE) spAgg->m_dGammaEq = 0.;
					spAgg->m_dGammaEq += pRow->m_pPos->m_dGammaInSharesPerc * pRow->m_pPos->m_dUndPriceSave;
				}
				else
					spAgg->m_bBadGammaEq = VARIANT_TRUE;
			}
			else
			{
				spAgg->m_bBadGammaPerc = VARIANT_TRUE;
				spAgg->m_bBadGammaEq = VARIANT_TRUE;
			}
			//m_dGamma
			if(pRow->m_pPos->m_dGammaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dGamma <= BAD_DOUBLE_VALUE) spAgg->m_dGamma = 0.;
				spAgg->m_dGamma += pRow->m_pPos->m_dGammaInShares;
			}
			else
				spAgg->m_bBadGamma = VARIANT_TRUE;
			//m_dNetGamma
			if(pRow->m_pPos->m_dNetGamma > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dNetGamma <= BAD_DOUBLE_VALUE) spAgg->m_dNetGamma = 0.;
				spAgg->m_dNetGamma += pRow->m_pPos->m_dNetGamma;
			}
			else
				spAgg->m_bBadNetGamma = VARIANT_TRUE;
			//m_dVega
			if(pRow->m_pPos->m_dVegaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dVega <= BAD_DOUBLE_VALUE) spAgg->m_dVega = 0.;
				spAgg->m_dVega += pRow->m_pPos->m_dVegaInShares;
			}
			else
				spAgg->m_bBadVega = VARIANT_TRUE;
			// m_dWtdVega
			if(pRow->m_pPos->m_dWtdVega > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dWtdVega <= BAD_DOUBLE_VALUE) spAgg->m_dWtdVega = 0.;
				spAgg->m_dWtdVega += pRow->m_pPos->m_dWtdVega;
			}
			else
				spAgg->m_bBadWtdVega = VARIANT_TRUE;
			// m_dTheta
			if(pRow->m_pPos->m_dThetaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dTheta <= BAD_DOUBLE_VALUE) spAgg->m_dTheta = 0.;
				spAgg->m_dTheta += pRow->m_pPos->m_dThetaInShares;
			}
			else
				spAgg->m_bBadTheta = VARIANT_TRUE;
			// m_dRho
			if(pRow->m_pPos->m_dRhoInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dRho <= BAD_DOUBLE_VALUE) spAgg->m_dRho = 0.;
				spAgg->m_dRho += pRow->m_pPos->m_dRhoInShares;
			}
			else
				spAgg->m_bBadRho = VARIANT_TRUE;
			// m_dThetaDelta
			if(pRow->m_pPos->m_dThetaDeltaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dThetaDelta <= BAD_DOUBLE_VALUE) spAgg->m_dThetaDelta = 0.;
				spAgg->m_dThetaDelta += pRow->m_pPos->m_dThetaDeltaInShares;
			}
			else
				spAgg->m_bBadThetaDelta = VARIANT_TRUE;
			// m_dThetaGamma
			if(pRow->m_pPos->m_dThetaGammaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dThetaGamma <= BAD_DOUBLE_VALUE) spAgg->m_dThetaGamma = 0.;
				spAgg->m_dThetaGamma += pRow->m_pPos->m_dThetaGammaInShares;
			}
			else
				spAgg->m_bBadThetaGamma = VARIANT_TRUE;
			// m_dVegaDelta
			if(pRow->m_pPos->m_dVegaDeltaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dVegaDelta <= BAD_DOUBLE_VALUE) spAgg->m_dVegaDelta = 0.;
				spAgg->m_dVegaDelta += pRow->m_pPos->m_dVegaDeltaInShares;
			}
			else
				spAgg->m_bBadVegaDelta = VARIANT_TRUE;
			// m_dVegaGamma
			if(pRow->m_pPos->m_dVegaGammaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dVegaGamma <= BAD_DOUBLE_VALUE) spAgg->m_dVegaGamma = 0.;
				spAgg->m_dVegaGamma += pRow->m_pPos->m_dVegaGammaInShares;
			}
			else
				spAgg->m_bBadVegaGamma = VARIANT_TRUE;
			// m_dTimeValue
			// m_dTimeValueInShares
			if(pRow->m_pPos->m_dTimeValue > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dTimeValue <= BAD_DOUBLE_VALUE) spAgg->m_dTimeValue = 0.;
				spAgg->m_dTimeValue += pRow->m_pPos->m_dTimeValue;

				if(spAgg->m_dTimeValueInShares <= BAD_DOUBLE_VALUE) spAgg->m_dTimeValueInShares = 0.;
				spAgg->m_dTimeValueInShares += (pRow->m_pPos->m_dTimeValue*pRow->m_pPos->m_nQtyInShares);
			}
			else
				spAgg->m_bBadTimeValue = VARIANT_TRUE;
		}
		else{
			if (pRow->m_Type == RDT_UNDAGG && pRow->m_pUnd && !pRow->m_pUnd->m_pParent ) 
				pRow->m_pUnd->m_pParent = spAgg.get();
			else if(pRow->m_Type == RDT_AGG && pRow->m_pAggregation && !pRow->m_pAggregation->m_pParent ) 
				pRow->m_pAggregation->m_pParent = spAgg.get();
		}
	}
	switch(aggClmn) {
		case RPC_EXPIRY:
			spAgg->m_dtExpiry = pRow->m_pPos->m_dtExpiry;
			CMmRvUndAtom::Date2Text( spAgg->m_dtExpiry, spAgg->m_bstrSymbol );
			break;
		default:
			CMmRvFutAtom* pFut = dynamic_cast<CMmRvFutAtom*>( pRow->m_pPos->m_spFut.GetInterfacePtr() );
			if ( pFut ) {
				spAgg->m_dtFutMaturity = pFut->m_dtMaturity;
				CMmRvUndAtom::Date2Text( spAgg->m_dtFutMaturity , spAgg->m_bstrSymbol );
			}
	}
	spAgg->m_dDeltaEq = BAD_DOUBLE_VALUE;
}*//*
void	CMmRiskView::Aggregate	(
											shared_ptr<__MmRvAggregationData>& spAgg,
											CRowsData::reverse_iterator& itrFirst,
											CRowsData::reverse_iterator& itrLast,
											RisksPosColumnEnum aggClmn,
											unsigned outlineLevel,
											DOUBLE dUndPriceToleranceValue, 
											EtsPriceRoundingRuleEnum enPriceRoundingRule
										){
	CMmRvRowData* pRow = NULL;
	double	dInternalEqDelta;
	long unitsPerDelivery = 0;
	bool bIsSpot = false;

	if ( spAgg->m_bstrSymbol == _bstr_t(L"Spot") )
		bIsSpot = true;
	for ( ; itrFirst != itrLast; itrFirst++ ) {
		pRow = dynamic_cast<CMmRvRowData*>((*itrFirst).GetInterfacePtr() );
		if( !pRow ) continue;
		if ( pRow->m_nLevel < outlineLevel ) {
			pRow->m_nLevel = outlineLevel;		// outline only if row not yet outlined already
		}
		// setup underlying for aggregation only once
		if ( !spAgg->m_pUnd) {
			if ( pRow->m_spUnd ) {
				spAgg->m_spUnd = pRow->m_spUnd;
				spAgg->m_pUnd = pRow->m_pUnd;
			}
		}
		if (!( pRow->m_Type == RDT_AGG ||  pRow->m_Type == RDT_UNDAGG) ) {
			if ( !pRow->m_pPos ) continue;
			if ( pRow->m_pPos->m_dPnlTheo > BAD_DOUBLE_VALUE){
				if ( spAgg->m_dPnlTheo == BAD_DOUBLE_VALUE ) spAgg->m_dPnlTheo = 0.;
				spAgg->m_dPnlTheo += pRow->m_pPos->m_dPnlTheo;
			}
			if ( pRow->m_pPos->m_dPnlMtm > BAD_DOUBLE_VALUE){
				if ( spAgg->m_dPnlMtm == BAD_DOUBLE_VALUE ) spAgg->m_dPnlMtm = 0.;
				spAgg->m_dPnlMtm += pRow->m_pPos->m_dPnlMtm;
			}
			if ( pRow->m_pPos->m_nQty > BAD_LONG_VALUE ){
				if (	
						pRow->m_pPos->m_enContractType == enCtFutOption ||
						pRow->m_pPos->m_enContractType == enCtOption 
					){
						if(spAgg->m_nOptQty <= BAD_LONG_VALUE) spAgg->m_nOptQty = 0L;
						spAgg->m_nOptQty += pRow->m_pPos->m_nQty;
				}
				else if(pRow->m_pPos->m_enContractType == enCtFuture ){
					if(spAgg->m_nFutQty <= BAD_LONG_VALUE) spAgg->m_nFutQty = 0L;
					spAgg->m_nFutQty += pRow->m_pPos->m_nQty;
					if(spAgg->m_nQty <= BAD_LONG_VALUE) spAgg->m_nQty = 0L;
					spAgg->m_nQty += (pRow->m_pPos->m_nQty * pRow->m_pPos->m_pQuote->m_nLotSize);
				}
				else{
					if(spAgg->m_nQty <= BAD_LONG_VALUE) spAgg->m_nQty = 0L;
					spAgg->m_nQty += pRow->m_pPos->m_nQty;
				}
			}
			if (pRow && pRow->m_pPos && pRow->m_pPos->m_pQuote && pRow->m_pPos->m_pQuote->m_nLotSize > unitsPerDelivery )
				unitsPerDelivery = pRow->m_pPos->m_pQuote->m_nLotSize;
			
			//m_dNetDelta
			//m_dOptDelta
			//m_dOptDeltaEq
			//m_dDeltaEq
			if (pRow->m_pPos->m_pQuote->m_dDelta > BAD_DOUBLE_VALUE) {
				if(spAgg->m_dDeltaP <= BAD_DOUBLE_VALUE) spAgg->m_dDeltaP = 0.;
				spAgg->m_dDeltaP += pRow->m_pPos->m_pQuote->m_dDelta;
			}

			if (pRow->m_pPos->m_dDeltaEq > BAD_DOUBLE_VALUE ) {
				if(spAgg->m_dDeltaEq <= BAD_DOUBLE_VALUE) spAgg->m_dDeltaEq = 0.;
				spAgg->m_dDeltaEq += pRow->m_pPos->m_dDeltaEq;
			}
			if(pRow->m_pPos->m_dDeltaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dOptDelta <= BAD_DOUBLE_VALUE) spAgg->m_dOptDelta = 0.;
				spAgg->m_dOptDelta += pRow->m_pPos->m_dDeltaInShares;
				if(spAgg->m_dNetDelta <= BAD_DOUBLE_VALUE) spAgg->m_dNetDelta = 0.;
				spAgg->m_dNetDelta += pRow->m_pPos->m_dDeltaInShares;
				//if(spAgg->m_nFutQty <= BAD_LONG_VALUE) spAgg->m_nFutQty = 0L;
				//spAgg->m_dNetDelta += ( ( double ) (spAgg->m_nFutQty) + spAgg->m_dOptDelta );
				if(pRow->m_pPos->m_dUndPriceSave > DBL_EPSILON)
				{
					if(spAgg->m_dDeltaEq <= BAD_DOUBLE_VALUE) spAgg->m_dDeltaEq = 0.;
					{
						if(spAgg->m_dOptDeltaEq <= BAD_DOUBLE_VALUE) spAgg->m_dOptDeltaEq = 0.;

						dInternalEqDelta = pRow->m_pPos->m_dDeltaInShares * pRow->m_pPos->m_dUndPriceSave;
						//if(pRow->m_pUnd->m_enContractType != enCtFutUnd)
						//	spAgg->m_dDeltaEq += pRow->m_pPos->m_dInternalEqDelta;
						spAgg->m_dOptDeltaEq += pRow->m_pPos->m_dInternalEqDelta;
					}
				}
				else
				{
					spAgg->m_bBadDeltaEq = VARIANT_TRUE;
					spAgg->m_bBadOptDeltaEq = VARIANT_TRUE;
				}
			}
			else
			{
				spAgg->m_bBadNetDelta = VARIANT_TRUE;
				spAgg->m_bBadOptDelta = VARIANT_TRUE;
				spAgg->m_bBadDeltaEq = VARIANT_TRUE;
			}
			//m_dGammaEq
			//m_dGammaPerc
			if(pRow->m_pPos->m_dGammaInSharesPerc > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dGammaPerc <= BAD_DOUBLE_VALUE) spAgg->m_dGammaPerc = 0.;
				spAgg->m_dGammaPerc += pRow->m_pPos->m_dGammaInSharesPerc;
				if(pRow->m_pPos->m_dUndPriceSave > DBL_EPSILON)
				{
					if(spAgg->m_dGammaEq <= BAD_DOUBLE_VALUE) spAgg->m_dGammaEq = 0.;
					spAgg->m_dGammaEq += pRow->m_pPos->m_dGammaInSharesPerc * pRow->m_pPos->m_dUndPriceSave;
				}
				else
					spAgg->m_bBadGammaEq = VARIANT_TRUE;
			}
			else
			{
				spAgg->m_bBadGammaPerc = VARIANT_TRUE;
				spAgg->m_bBadGammaEq = VARIANT_TRUE;
			}
			//m_dGamma
			if(pRow->m_pPos->m_dGammaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dGamma <= BAD_DOUBLE_VALUE) spAgg->m_dGamma = 0.;
				spAgg->m_dGamma += pRow->m_pPos->m_dGammaInShares;
			}
			else
				spAgg->m_bBadGamma = VARIANT_TRUE;
			//m_dNetGamma
			if(pRow->m_pPos->m_dNetGamma > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dNetGamma <= BAD_DOUBLE_VALUE) spAgg->m_dNetGamma = 0.;
				spAgg->m_dNetGamma += pRow->m_pPos->m_dNetGamma;
			}
			else
				spAgg->m_bBadNetGamma = VARIANT_TRUE;
			//m_dVega
			if(pRow->m_pPos->m_dVegaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dVega <= BAD_DOUBLE_VALUE) spAgg->m_dVega = 0.;
				spAgg->m_dVega += pRow->m_pPos->m_dVegaInShares;
			}
			else
				spAgg->m_bBadVega = VARIANT_TRUE;
			// m_dWtdVega
			if(pRow->m_pPos->m_dWtdVega > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dWtdVega <= BAD_DOUBLE_VALUE) spAgg->m_dWtdVega = 0.;
				spAgg->m_dWtdVega += pRow->m_pPos->m_dWtdVega;
			}
			else
				spAgg->m_bBadWtdVega = VARIANT_TRUE;
			// m_dTheta
			if(pRow->m_pPos->m_dThetaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dTheta <= BAD_DOUBLE_VALUE) spAgg->m_dTheta = 0.;
				spAgg->m_dTheta += pRow->m_pPos->m_dThetaInShares;
			}
			else
				spAgg->m_bBadTheta = VARIANT_TRUE;
			// m_dRho
			if(pRow->m_pPos->m_dRhoInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dRho <= BAD_DOUBLE_VALUE) spAgg->m_dRho = 0.;
				spAgg->m_dRho += pRow->m_pPos->m_dRhoInShares;
			}
			else
				spAgg->m_bBadRho = VARIANT_TRUE;
			// m_dThetaDelta
			if(pRow->m_pPos->m_dThetaDeltaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dThetaDelta <= BAD_DOUBLE_VALUE) spAgg->m_dThetaDelta = 0.;
				spAgg->m_dThetaDelta += pRow->m_pPos->m_dThetaDeltaInShares;
			}
			else
				spAgg->m_bBadThetaDelta = VARIANT_TRUE;
			// m_dThetaGamma
			if(pRow->m_pPos->m_dThetaGammaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dThetaGamma <= BAD_DOUBLE_VALUE) spAgg->m_dThetaGamma = 0.;
				spAgg->m_dThetaGamma += pRow->m_pPos->m_dThetaGammaInShares;
			}
			else
				spAgg->m_bBadThetaGamma = VARIANT_TRUE;
			// m_dVegaDelta
			if(pRow->m_pPos->m_dVegaDeltaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dVegaDelta <= BAD_DOUBLE_VALUE) spAgg->m_dVegaDelta = 0.;
				spAgg->m_dVegaDelta += pRow->m_pPos->m_dVegaDeltaInShares;
			}
			else
				spAgg->m_bBadVegaDelta = VARIANT_TRUE;
			// m_dVegaGamma
			if(pRow->m_pPos->m_dVegaGammaInShares > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dVegaGamma <= BAD_DOUBLE_VALUE) spAgg->m_dVegaGamma = 0.;
				spAgg->m_dVegaGamma += pRow->m_pPos->m_dVegaGammaInShares;
			}
			else
				spAgg->m_bBadVegaGamma = VARIANT_TRUE;
			// m_dTimeValue
			// m_dTimeValueInShares
			if(pRow->m_pPos->m_dTimeValue > BAD_DOUBLE_VALUE)
			{
				if(spAgg->m_dTimeValue <= BAD_DOUBLE_VALUE) spAgg->m_dTimeValue = 0.;
				spAgg->m_dTimeValue += pRow->m_pPos->m_dTimeValue;

				if(spAgg->m_dTimeValueInShares <= BAD_DOUBLE_VALUE) spAgg->m_dTimeValueInShares = 0.;
				spAgg->m_dTimeValueInShares += (pRow->m_pPos->m_dTimeValue*pRow->m_pPos->m_nQtyInShares);
			}
			else
				spAgg->m_bBadTimeValue = VARIANT_TRUE;
		}
		else{
			if (pRow->m_Type == RDT_UNDAGG && pRow->m_pUnd && !pRow->m_pUnd->m_pParent ) 
				pRow->m_pUnd->m_pParent = spAgg.get();
			else if(pRow->m_Type == RDT_AGG && pRow->m_pAggregation && !pRow->m_pAggregation->m_pParent ) 
				pRow->m_pAggregation->m_pParent = spAgg.get();
		}
	}
	if ( bIsSpot ) {
		if(spAgg->m_nQty <= BAD_LONG_VALUE) spAgg->m_nQty = 0L;
		spAgg->m_dNetDelta = ( double ) (spAgg->m_nQty) +  spAgg->m_dOptDelta ;
	}
	else{
		if(spAgg->m_nFutQty <= BAD_LONG_VALUE) spAgg->m_nFutQty = 0L;

		if(spAgg->m_dOptDelta <= BAD_DOUBLE_VALUE)
			spAgg->m_dNetDelta = 0.;
		else
		{
			spAgg->m_dNetDelta = (  spAgg->m_dOptDelta );
		}
	}
}
void CMmRiskView::DecreaseOutline( CRowsData::reverse_iterator& begin, CRowsData::reverse_iterator& end){
	CMmRvRowData* pRow;
	for ( CRowsData::reverse_iterator itrCur = begin; itrCur != end; ++itrCur) {
		pRow = dynamic_cast<CMmRvRowData*>((*itrCur).GetInterfacePtr() );
		if (pRow) 
			pRow->m_nLevel--;
	}
}
*/
//STDMETHODIMP CMmRiskView::CalcStrategies(
//	IN VARIANT_BOOL bIsPnlLTD,
//	IN VARIANT_BOOL bUseTheoVolatility,
//	IN VARIANT_BOOL bUseTheoVolaNoBid,
//	IN VARIANT_BOOL bUseTheoVolaBadMarket,
//	IN DOUBLE dUndPriceTolerance,
//	IN enum EtsPriceRoundingRuleEnum enPriceRoundingRule,
//	IN DATE dtCalcDate)
//{
//	HRESULT hr = S_OK;
//	try
//	{
//		if(m_enViewMode == RV_GREEKS && m_pExpTotal)
//			m_pExpTotal->Calc();
//
//		if(m_enViewMode == RV_RISKS)
//		{
//			// Calc Totals
//			 if(m_pStrategy)
//				 m_pStrategy->Calc(	m_pUnd, m_pIdx,	bIsPnlLTD,	bUseTheoVolatility,	bUseTheoVolaNoBid, bUseTheoVolaBadMarket,
//									dUndPriceTolerance,	enPriceRoundingRule, dtCalcDate	);	
//			 if(m_pGroups)
//				 m_pGroups->Calc(m_pUnd, m_pIdx, bIsPnlLTD,	bUseTheoVolatility,	bUseTheoVolaNoBid,	bUseTheoVolaBadMarket,
//									dUndPriceTolerance,	enPriceRoundingRule, dtCalcDate	);
//		}
//	
//	}
//	catch (_com_error& err)
//	{
//		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(err), __uuidof(IMmRiskView), err.Error());
//	}
//	return hr;
//}


STDMETHODIMP CMmRiskView::Calc( VARIANT_BOOL  bTotals,
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
	HRESULT hr = S_OK;
	try
	{
		if(m_pGrp)
		{
			hr =    m_pGrp->CalcGroup(m_pUnd, m_pIdx, bTotals,  nMask, bCalcGreeks, bUpdateVola, bRealtimeCalc,  aDelay,
									  bIsPnlLTD,  enCalcModel,
									  bUseTheoVolatility, bUseTheoVolaNoBid,  bUseTheoVolaBadMarket,  dUndPriceTolerance,
									  enPriceRoundingRule,
									  pnOptUpdated,	  pnUndUpdated,	  pnFutUpdated,
									  dtCalcDate);
		}
		if(SUCCEEDED(hr)&& m_enViewMode == RV_GREEKS && m_pExpTotal) m_pExpTotal->Calc();
		/*if(SUCCEEDED(hr))
			hr = CalcStrategies( bIsPnlLTD, bUseTheoVolatility, bUseTheoVolaNoBid, bUseTheoVolaBadMarket, dUndPriceTolerance, enPriceRoundingRule, dtCalcDate);*/
	}
	catch (_com_error& err)
	{
		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(err), __uuidof(IMmRiskView), err.Error());
	}
	return hr;
}


STDMETHODIMP CMmRiskView::RemoveOldTradeFromPosition(IMmRvUndAtom* pUndAtom, IMmRvPosAtom* pPosAtom, IMmTradeInfoAtom* pTrd)
{
	HRESULT hr = S_OK;
	try
	{
		CMmRvUndAtom* pUnd = dynamic_cast<CMmRvUndAtom*>(pUndAtom);
		CMmRvPosAtom* pPos = dynamic_cast<CMmRvPosAtom*>(pPosAtom);

		IMmRvUndAtomPtr spUnderlying = m_pUnd->GetUnderlying(pUnd->m_nID);
		IMmRvPosCollPtr spPosColl;
		long lStrategyId = 0;
		pTrd->get_StrategyID(&lStrategyId);

		if(spUnderlying!=NULL)
		{
			spUnderlying->get_Pos(&spPosColl);

			if(spPosColl!=NULL)
			{
				IMmRvPosAtomPtr spPosAtom;
				spPosColl->get_Item(pPos->m_nID, &spPosAtom);
				long lQuanitiy = 0;
				pTrd->get_Quantity(&lQuanitiy);
				pTrd->put_Quantity(-1*lQuanitiy);
				_AddNewTradeToPosition(spUnderlying, spPosAtom, pTrd);
				pTrd->put_Quantity(lQuanitiy);

//				hr = _RemoveOldTradeFromPosition(dynamic_cast<CMmRvUndAtom*>(spUnderlying.GetInterfacePtr()), NULL, spPosAtom, pTrd);
			}
			
//			if(false && m_pGroups)
//			{
//				CMmRvGroupColl::CollType::iterator itrGrp    = m_pGroups->m_coll.begin();
//				CMmRvGroupColl::CollType::iterator itrGrpEnd = m_pGroups->m_coll.end();
//				for(; itrGrp!=itrGrpEnd; ++itrGrp)
//				{
//					CMmRvGroupAtom* pGrpAtom = dynamic_cast<CMmRvGroupAtom*>(itrGrp->second);
//					if(pGrpAtom)
//					{
//						CMmRvUndColl::CollType::iterator itrUnd = pGrpAtom->m_pUndColl->m_collRef.find(pUnd->m_nID);
//						if(itrUnd != pGrpAtom->m_pUndColl->m_collRef.end())
//						{
//// 							CMmRvUndAtom* pGrpUndAtom = dynamic_cast<CMmRvUndAtom*>(itrUnd->second->second);
//// 							if(pGrpUndAtom)
//// 							{
//// 								CMmRvPosColl::CollType::iterator itrGrpUndPos =  pGrpUndAtom->m_pPos->m_collRef.find(pPos->m_nID);
//// 								if(itrGrpUndPos !=  pGrpUndAtom->m_pPos->m_collRef.end())
//// 									hr = _RemoveOldTradeFromPosition(NULL, NULL, itrGrpUndPos->second->second, pTrd);
//// 							}
//							CMmRvStrategyColl::CollType::iterator itrStrategy = pGrpAtom->m_pStrategyColl->m_coll.find(lStrategyId);
//							if(itrStrategy != pGrpAtom->m_pStrategyColl->m_coll.end())
//							{
//								CMmRvStrategyAtom* pStrategyAtom = dynamic_cast<CMmRvStrategyAtom*>(itrStrategy->second);
//								if(pStrategyAtom)
//								{
//									CMmRvPosColl::CollType::iterator itrGrpStratPos = pStrategyAtom->m_pPos->m_collRef.find(pPos->m_nID);
//									if(itrGrpStratPos!=pStrategyAtom->m_pPos->m_collRef.end())
//										hr = _RemoveOldTradeFromPosition(NULL, pStrategyAtom, itrGrpStratPos->second->second, pTrd);
//								}
//
//							}
//						}
//						pGrpAtom->Aggregate();
//					}
//				}
//			}
		}
	}
	catch (_com_error &err)
	{
		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(err), __uuidof(IMmRiskView), err.Error());
	}
	return hr;

}


HRESULT CMmRiskView::_RemoveOldTradeFromPosition(CMmRvUndAtom* pUnd, /*CMmRvStrategyAtom* pStrategy,*/ IMmRvPosAtom* pPosAtom, IMmTradeInfoAtom* pTrd)
{
	HRESULT hr = S_OK;
	IMmTradeInfoAtomPtr spTradeAtom(pTrd); 
	CMmRvPosAtom* pPos = dynamic_cast<CMmRvPosAtom*>(pPosAtom);

	long	nQty			=0;
	long	nQtyInShares	=0;
	double  dTradePrice     =spTradeAtom->Price;
	bool    bIsBuy          =spTradeAtom->IsBuy!=VARIANT_FALSE; 
	nQty					=spTradeAtom->Quantity * (bIsBuy?1: -1);
    nQtyInShares			=nQty * pPos->m_pQuote->m_nLotSize;

	double	dPriceClose = pPos->m_pQuote->m_pPrice->m_dPriceClose;

	if (m_spEtsMain->UseTheoCloseForPNL && pPos->m_pQuote->m_pPrice->m_dPriceTheoClose > 0.0)
	{
		dPriceClose = pPos->m_pQuote->m_pPrice->m_dPriceTheoClose;
	}

	if (bIsBuy)
	{
	    pPos->m_nQtyLTDBuy -= nQtyInShares;
        pPos->m_dPosLTDBuy -=  dTradePrice * nQtyInShares;
        
		if (spTradeAtom->TradeDate < vt_date::GetCurrentDate(true))
		{
			pPos->m_nQtyDailyPrevDateBuy -= nQtyInShares;
			pPos->m_dPosDailyPrevDateBuy -= nQtyInShares *  /*pPos->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose  > DBL_EPSILON? /*pPos->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose : dTradePrice;
		}
		else
		{
			pPos->m_nQtyDailyTodayBuy -= nQtyInShares;
			pPos->m_dPosDailyTodayBuy -= dTradePrice * nQtyInShares;
		}
	} 
	else
	{
        pPos->m_nQtyLTDSell -= nQtyInShares;
        pPos->m_dPosLTDSell -= dTradePrice * nQtyInShares;
        
        if(spTradeAtom->TradeDate < vt_date::GetCurrentDate(true))
		{
			pPos->m_nQtyDailyPrevDateSell -= nQtyInShares;
			pPos->m_dPosDailyPrevDateSell -= nQtyInShares * /*pPos->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose > DBL_EPSILON? /*pPos->m_pQuote->m_pPrice->m_dPriceClose*/ dPriceClose : dTradePrice;
		}
		else
		{
			pPos->m_nQtyDailyTodaySell -= nQtyInShares;
			pPos->m_dPosDailyTodaySell = dTradePrice * nQtyInShares;
		}
	}
    
    pPos->m_nQty -= nQty;
    pPos->m_nQtyInShares -= nQtyInShares;

	if(pUnd)
	{
		switch(pPos->m_enContractType)
		{
		case enCtOption:
		case enCtFutOption:
			if(pUnd->OptQty_ == BAD_LONG_VALUE) pUnd->OptQty_ = 0;
			pUnd->OptQty_ -= nQty;
			break;
		case enCtFuture:
			if(pUnd->FutQty_ == BAD_LONG_VALUE) pUnd->FutQty_ = 0;
			pUnd->FutQty_ -= nQty;
			if(pUnd->UndPos_== BAD_LONG_VALUE) pUnd->UndPos_ = 0;
			pUnd->UndPos_ -= nQtyInShares;
			break;
		case enCtStock:
		case enCtIndex:
			if(pUnd->UndPos_ == BAD_LONG_VALUE) pUnd->UndPos_ = 0;
			pUnd->UndPos_ -= nQtyInShares;
			break;
		}
	}
	/*if(pStrategy)
	{
		switch(pPos->m_enContractType)
		{
		case enCtOption:
		case enCtFutOption:
			if(pStrategy->m_nOptQty == BAD_LONG_VALUE) pStrategy->m_nOptQty = 0;
			pStrategy->m_nOptQty -= nQty;
			break;
		case enCtFuture:
			if(pStrategy->m_nFutQty == BAD_LONG_VALUE) pStrategy->m_nFutQty = 0;
			pStrategy->m_nFutQty -= nQty;

			if(pStrategy->m_nQty == BAD_LONG_VALUE) pStrategy->m_nQty = 0;
			pStrategy->m_nQty -= nQtyInShares;
			break;
		case enCtStock:
		case enCtIndex:
			if(pStrategy->m_nQty == BAD_LONG_VALUE) pStrategy->m_nQty = 0;
			pStrategy->m_nQty -= nQtyInShares;
			break;
		}
	}*/

  	return hr;
}
STDMETHODIMP CMmRiskView::put_PosColumnsOrder(SAFEARRAY** colOrder)
{
	try
	{
		void* pData = reinterpret_cast<LPVOID> (*colOrder);
		if(pData!=NULL)
		{
			m_lVisibleColumns = 0L;
			CComSafeArray<LONG> lArray(*colOrder);
			long lUpperBound = lArray.GetUpperBound();
			long lLowerBound = lArray.GetLowerBound();
			int j=0;
			memset(m_ColumnsEncoding,-1,sizeof(m_ColumnsEncoding));
			for(long i = lLowerBound; i<lUpperBound; ++i)
			{
				m_ColumnsEncoding[j++] = lArray[i];
				if(lArray[i]>=0)
					m_lVisibleColumns++;

				if(j >= RPC_COLUMN_COUNT)
					break;
			}
		}
	}
	catch (...) {
	}
	return S_OK;

}
STDMETHODIMP CMmRiskView::get_PosRowData(long lRow , struct IMmRvRowData ** ppData)
{
	HRESULT hr = S_OK;
	try
	{
		if(ppData && lRow > 0 )
		{
			size_t  lPos = static_cast<size_t>(lRow-1);
			if(m_Rows.size()>lPos)
			{
				IMmRvRowDataPtr spAtom = m_Rows[lPos];
				if(spAtom!=NULL)
					*ppData = spAtom.Detach();
			}
		}
	}
	catch (_com_error& err) 
	{
		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(err), IID_IMmRiskView, err.Error());
	}
	return hr;
}
//IMmRvPosAtomPtr  CMmRiskView::_AddNewSynthPosition(CMmRvStrategyAtom* pStrategy, CMmRvUndAtom* pUndAtom )
//{
//	CComObject<CMmRvPosAtom>* pPosAtom = NULL;
//	IMmRvPosAtomPtr spPosAtom = pStrategy->m_pPos->GetPosition(pUndAtom->m_nID);
//	if(spPosAtom == NULL)
//	{
//		spPosAtom = pStrategy->m_pPos->AddNew(pUndAtom->m_nID, pUndAtom->m_bstrSymbol, &pPosAtom);
//		pPosAtom->m_spStrategy = pStrategy;
//
//		pPosAtom->m_enContractType      = pUndAtom->m_enContractType;
//		//pPosAtom->m_lExternalPosition   = pUndAtom->m_lExternalPosition;
//		pPosAtom->m_pQuote->m_nLotSize  = pUndAtom->m_nLotSize;
//		pPosAtom->m_pQuote->m_pPrice    = pUndAtom->m_pPrice;            
//		pPosAtom->m_pQuote->m_spPrice   = pUndAtom->m_spPrice;            
//		pPosAtom->m_bIsSyntheticAggregation = VARIANT_TRUE;
//
//		_bstr_t sKey = _bstr_t(static_cast<long>(pPosAtom->m_enContractType )) + _bstr_t(L"_") + pPosAtom->m_bstrSymbol;
//
//// 		IMmRvReqAtomPtr spRequestAtom = m_pQuoteReqsAll->GetRequest(sKey);
//// 
//// 		if(pUndAtom->m_nID >0)
//// 		{
//// 			CComObject<CMmRvReqAtom>* pRequestAtom = NULL;
//// 			if(spRequestAtom == NULL)
//// 			{
//// 				spRequestAtom = m_pQuoteReqsAll->AddNew(sKey, &pRequestAtom);
//// 				if(pRequestAtom!=NULL)
//// 				{
//// 					pRequestAtom->m_spUnd = pUndAtom;
//// 					pRequestAtom->m_spPos = spPosAtom;
//// 				}
//// 			}
//// 			else
//// 			{
//// 				pRequestAtom = dynamic_cast<CComObject<CMmRvReqAtom>*>(spRequestAtom.GetInterfacePtr());
//// 				if(pRequestAtom->m_spPos == NULL)
//// 					pRequestAtom->m_spPos = spPosAtom;
//// 			}
//// 		}
//
//// 		pPosAtom->m_pQuote->m_d`  = pBaseUndAtom->m_pQuote;
//// 		pPosAtom->m_spQuote = pBaseUndAtom->m_spQuote;
//
//		// check for existence of active future for index 
//		if ( pPosAtom->m_enContractType == enCtIndex )
//		{
//			IEtsFutAtomPtr spActiveFuture = pUndAtom->m_spActiveFuture;	// here is atom from contracts collections
//			IMmRvFutAtomPtr spIdxActiveFuture;								// here is atom from index atom
//
//			if ( NULL != spActiveFuture)
//			{
//				spIdxActiveFuture = pUndAtom->m_spActiveFuture;	
//				if (NULL == spIdxActiveFuture )	// if still not active future for this index
//				{
//					// create active future atom for this index
//					CComObject<CMmRvFutAtom> *spRvUndAtomActiveFuture = NULL;
//
//					CComObject<CMmRvFutAtom>::CreateInstance(&spRvUndAtomActiveFuture);
//					spIdxActiveFuture.Attach(spRvUndAtomActiveFuture, TRUE);
//					pUndAtom->m_spActiveFuture = spRvUndAtomActiveFuture;
//				}
//
//				_CHK(spIdxActiveFuture->put_CalcGreeks(VARIANT_FALSE));
//
//				LONG valueLong;
//				_CHK(spActiveFuture->get_ID(&valueLong));
//				_CHK(spIdxActiveFuture->put_ID(valueLong));
//
//				_CHK(spActiveFuture->get_FutRootID(&valueLong));
//				_CHK(spIdxActiveFuture->put_FutRootID(valueLong));
//				_CHK(pUndAtom->get_ID(&valueLong));
//				_CHK(spIdxActiveFuture->put_UndID(valueLong));
//				_CHK(spActiveFuture->get_ExpCalendarID(&valueLong));
//				_CHK(spIdxActiveFuture->put_ExpCalendarID(valueLong) );
//
//				DATE valueDate;
//				_CHK(spActiveFuture->get_MaturityDate(&valueDate) );
//				_CHK(spIdxActiveFuture->put_Maturity(valueDate));
//
//				VARIANT_BOOL valueBool;
//				_CHK(spActiveFuture->get_IsAmerican(&valueBool));
//				_CHK(spIdxActiveFuture->put_IsAmerican(valueBool));
//
//				DOUBLE valueDouble;
//				_CHK(spActiveFuture->get_FutureBasis(&valueDouble));
//				_CHK(spIdxActiveFuture->put_FutureBasis(valueDouble));
//
//				CComBSTR	valueBstr;
//				_CHK(spActiveFuture->get_ContractName(&valueBstr));
//				_CHK(spIdxActiveFuture->put_ContractName(valueBstr));
//				_CHK(spActiveFuture->get_Symbol(&valueBstr));
//				_CHK(spIdxActiveFuture->put_Symbol(valueBstr));
//
//				IEtsPriceProfileAtomPtr valuePriceProfilePtr;
//				_CHK(spActiveFuture->get_UndPriceProfile(&valuePriceProfilePtr) );
//				_CHK(spIdxActiveFuture->putref_UndPriceProfile(valuePriceProfilePtr));
//				_CHK(spActiveFuture->get_OptPriceProfile(&valuePriceProfilePtr) );
//				_CHK(spIdxActiveFuture->putref_OptPriceProfile(valuePriceProfilePtr));
//
//
//				_bstr_t sActiveFutureKey = _bstr_t(static_cast<long>(enCtFuture)) + _bstr_t(L"_") + ( BSTR )valueBstr;
//				IMmRvReqAtomPtr spActiveFutureRequestAtom = m_pQuoteReqsAll->GetRequest(sActiveFutureKey);
//				if(spActiveFutureRequestAtom == NULL)
//				{
//					CComObject<CMmRvReqAtom>* pObject = NULL;
//					spActiveFutureRequestAtom = m_pQuoteReqsAll->AddNew(sActiveFutureKey, &pObject);
//					if(pObject!=NULL)
//						pObject->m_spFut = spIdxActiveFuture;
//				}
//			}
//		}
//
//		pPosAtom->m_nQty					= 0;
//		pPosAtom->m_nQtyInShares			= 0;
//		pPosAtom->m_nQtyLTDBuy				= BAD_LONG_VALUE;
//		pPosAtom->m_dPosLTDBuy				= BAD_DOUBLE_VALUE;
//		pPosAtom->m_nQtyDailyPrevDateBuy	= BAD_LONG_VALUE;
//		pPosAtom->m_dPosDailyPrevDateBuy	= BAD_DOUBLE_VALUE;
//		pPosAtom->m_nQtyDailyTodayBuy		= BAD_LONG_VALUE;
//		pPosAtom->m_dPosDailyTodayBuy		= BAD_DOUBLE_VALUE;
//		pPosAtom->m_nQtyLTDSell				= BAD_LONG_VALUE;
//		pPosAtom->m_dPosLTDSell				= BAD_DOUBLE_VALUE;
//
//		pPosAtom->m_nQtyDailyPrevDateSell	= BAD_LONG_VALUE;
//		pPosAtom->m_dPosDailyPrevDateSell	= BAD_DOUBLE_VALUE;
//		pPosAtom->m_nQtyDailyTodaySell		= BAD_LONG_VALUE;
//		pPosAtom->m_dPosDailyTodaySell		= BAD_DOUBLE_VALUE;
//	}
//	return spPosAtom;
//}
