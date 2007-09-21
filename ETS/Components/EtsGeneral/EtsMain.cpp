// EtsMain.cpp : Implementation of CEtsMain

#include "stdafx.h"
#include "EtsMain.h"


// CEtsMain
STDMETHODIMP CEtsMain::Clear()
{
	try
	{
		_Clear();

	}
	catch(_com_error& e )
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());

	}
	catch(...)
	{
		return Error(_T("Unknown Error in Main::Clear "), IID_IEtsMain, E_FAIL);
	}
	return S_OK;
}

STDMETHODIMP CEtsMain::LoadBetas()
{
	try
	{
		_bstr_t bsStatus(L"Loading index underlying betas...");

		Fire_Progress(bsStatus, -1);
		InitializeDB();
		CStoredProc<> sp(m_DbConnection, L"usp_MmIndexUnderlyingBeta_Get");
		CClientRecordset rs;
		rs.Open(sp);

		long lTotalCount = rs.GetRecordCount();
		long lLoaded = 0;
		long lLastPerc = -1;

		if(lTotalCount && m_pIndex)
		{
			for(rs.MoveFirst(); !rs.IsEOF(); ++rs, ++lLoaded)
			{
				double dBeta = rs[L"fBeta"];
				if(dBeta!=0.0)
				{
					long nIdxID = rs[L"iIndexID"];
					long nID    = rs[L"iContractID"];

					IUndAtomPtr spUndAtom;
					m_pUnderlyingAll->get_Item(nIdxID, &spUndAtom);
					if(spUndAtom)
					{
						VARIANT_BOOL bIsHedgeSymbol = VARIANT_FALSE;
						spUndAtom->get_IsHedgeSymbol(&bIsHedgeSymbol);
						if(bIsHedgeSymbol!=VARIANT_FALSE)
						{
							_bstr_t bsIndexSymbol = rs[L"vcIndexSymbol"];
							// Hedge Symbol
							IIndexAtomPtr spHedgeIndex = m_pHedgeSymbols->GetIndex(nIdxID);
							if(spHedgeIndex==NULL)
							{
								// Add New	
								m_pHedgeSymbols->Add(nIdxID, bsIndexSymbol,NULL, &spHedgeIndex);
							}
							if(spHedgeIndex!=NULL)
							{
								spHedgeIndex->put_ID(nIdxID);
								spHedgeIndex->put_Symbol(bsIndexSymbol);

								IEtsPriceProfileAtomPtr spProfile;
								spUndAtom->get_UndPriceProfile(&spProfile);
								spHedgeIndex->putref_UndPriceProfile(spProfile);

								spProfile = NULL;
								spUndAtom->get_OptPriceProfile(&spProfile);
								spHedgeIndex->putref_OptPriceProfile(spProfile);

								IIndexCompCollPtr spIdxCompColl;
								spHedgeIndex->get_Components(&spIdxCompColl);
								if(spIdxCompColl != NULL)
								{
									IIndexCompAtomPtr spCompAtom;
									spIdxCompColl->get_Item(nID, &spCompAtom);
									if(spCompAtom==NULL)
										spIdxCompColl->Add(nID, NULL, &spCompAtom);

									if(spCompAtom!=NULL)
									{
										spCompAtom->put_Beta(dBeta);
										spHedgeIndex->put_HaveComponentBetas(VARIANT_TRUE);
									}
								}
							}
						}
					}

					IIndexAtomPtr spIdx = m_pIndex->GetIndex(nIdxID);
					if(spIdx)
					{
						IIndexCompCollPtr spIdxCompColl;
						spIdx->get_Components(&spIdxCompColl);
						if(spIdxCompColl != NULL)
						{
							IIndexCompAtomPtr spCompAtom;
							spIdxCompColl->get_Item(nID, &spCompAtom);
							if(spCompAtom==NULL)
								spIdxCompColl->Add(nID, NULL, &spCompAtom);

							if(spCompAtom!=NULL)
							{
								spCompAtom->put_Beta(dBeta);
								spIdx->put_HaveComponentBetas(VARIANT_TRUE);
							}						

						}
					}
				}
				long lPerc = static_cast<long>( 100.* double(lLoaded)/ double(lTotalCount));
				if(lPerc != lLastPerc)
				{
					lLastPerc = lPerc;
					Fire_Progress(bsStatus,lLastPerc);
				}
			}
		}
	}
	catch(_com_error& e )
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());

	}
	catch(...)
	{
		return Error(_T("Unknown Error in CEtsMain::LoadStrategy "), IID_IEtsMain, E_FAIL);
	}
	return S_OK;

}

STDMETHODIMP CEtsMain::LoadStrategy()
{
	try
	{
		Fire_Progress(L"Loading strategies data...", -1);

		m_pStrategy->Clear();
		InitializeDB();
		CStoredProc<> sp(m_DbConnection, L"usp_Strategy_Get");
		CClientRecordset rs;
		rs.Open(sp);
		if(rs.GetRecordCount())
		{
			rs.MoveFirst();
			while(!rs.IsEOF())
			{
				IEtsStrategyAtomPtr spStrategy;
				long lStrategyID = rs[L"iStrategyID"];

				m_pStrategy->get_Item(lStrategyID, &spStrategy);
				if(spStrategy == NULL)
				{
					_bstr_t bsStrategyName = rs[L"vcStrategyName"];
					_bstr_t bsDescription  = rs[L"vcDescription"];

					spStrategy = m_pStrategy->AddNew(lStrategyID, bsStrategyName, bsDescription);
				}
				rs.MoveNext();
			}
		}
	}
	catch(_com_error& e )
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());

	}
	catch(...)
	{
		return Error(_T("Unknown Error in CEtsMain::LoadStrategy "), IID_IEtsMain, E_FAIL);
	}
	return S_OK;
}
STDMETHODIMP CEtsMain::LoadBroker()
{
	try
	{
		Fire_Progress(L"Loading brokers data...", -1);

		m_pBroker->Clear();
		m_pClearingBroker->Clear();
		InitializeDB();

		CStoredProc<CClientRecordset> rs(m_DbConnection, L"usp_Broker_Get");
		rs.Open();
		if(rs.GetRecordCount())
		{
			rs.MoveFirst();
			while(!rs.IsEOF())
			{
				long lID = rs[L"iBrokerID"];
				bool bIsClearing = rs[L"tiIsClearing"];

				IEtsBrokerAtomPtr spBroker;
				CComObject<CEtsBrokerAtom>* pAtom= NULL;
				if(!bIsClearing)
				{
					m_pBroker->get_Item(lID, &spBroker);
					if(spBroker == NULL)
					{
						IEtsBrokerAtomPtr spAtom = m_pBroker->AddNew(lID, rs[L"vcBrokerName"], rs[L"vcDescription"], &pAtom);
						if(spAtom!=NULL && pAtom!=NULL)
						{
							pAtom->m_bIsClearing = VARIANT_FALSE;
							pAtom->m_dUndComm    = rs[L"fUndComm"];
							pAtom->m_dOptRegComm = rs[L"fOptRegComm"];
							pAtom->m_dOptSpreadComm = rs[L"fOptSpreadComm"];
							pAtom->m_dLowPremComm = rs[L"fLowPremComm"];
						}
					}
				}
				else
				{
					m_pClearingBroker->get_Item(lID, &spBroker);
					if(spBroker == NULL)
					{
						IEtsBrokerAtomPtr spAtom = m_pClearingBroker->AddNew(lID, rs[L"vcBrokerName"], rs[L"vcDescription"], &pAtom);
						if(spAtom!=NULL && pAtom!=NULL)
						{
							pAtom->m_bIsClearing = VARIANT_TRUE;
							pAtom->m_dUndComm    = rs[L"fUndComm"];
							pAtom->m_dOptRegComm = rs[L"fOptRegComm"];
							pAtom->m_dOptSpreadComm = rs[L"fOptSpreadComm"];
							pAtom->m_dLowPremComm = rs[L"fLowPremComm"];
						}
					}
				}
				rs.MoveNext();
			}
		}
	}
	catch(_com_error& e )
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());

	}
	catch(...)
	{
		return Error(_T("Unknown Error in CEtsMain::LoadBroker "), IID_IEtsMain, E_FAIL);
	}
	return S_OK;
}


STDMETHODIMP CEtsMain::LoadTraderGroup()
{
	HRESULT hr = S_OK;
	try
	{
		Fire_Progress(L"Loading trader groups data...",-1);

		m_pTraderGroup->Clear();
		InitializeDB();

		// Add Default Data
		//m_pTraderGroup->AddNew(0, L"<Defualt>", L"Default Trader Group");

		CStoredProc<CClientRecordset> rs(m_DbConnection, L"usp_TraderGroup_Get");
		rs.Open();
		if(rs.GetRecordCount())
		{
			rs.MoveFirst();
			while(!rs.IsEOF())
			{
				long nID = rs[L"iTraderGroupID"];
				IEtsTraderGroupAtomPtr spTraderGroup;
				CComObject<CEtsTraderGroupAtom> pTraderGroup = NULL;
				m_pTraderGroup->get_Item(nID, &spTraderGroup);
				if(spTraderGroup == NULL)
					m_pTraderGroup->AddNew(nID, rs[L"vcGroupName"], rs[L"vcGroupDesc"]);

				rs.MoveNext();
			}
		}
	}
	catch(_com_error& e )
	{
		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());

	}
	catch(...)
	{
		hr = Error(_T("Unknown Error in CEtsMain::LoadStrategy "), IID_IEtsMain, E_FAIL);
	}
	return hr;
}

STDMETHODIMP CEtsMain::LoadTrader(LONG lTraderID)
{
	HRESULT hr = S_OK;
	try
	{
		Fire_Progress(L"Loading traders data...",-1);
		m_pTraderColl->Clear();
		InitializeDB();

		CStoredProc<CClientRecordset> rs(m_DbConnection, L"usp_Trader_Get");
		if(lTraderID)
			rs << lTraderID;
		rs.Open();
		if(rs.GetRecordCount())
		{
			rs.MoveFirst();
			while (!rs.IsEOF()) 
			{
				IEtsTraderAtomPtr spTrader;
				CComObject<CEtsTraderAtom>* pTrader = NULL;

				long nID = rs[L"iTraderID"];
				m_pTraderColl->get_Item(nID, &spTrader);
				if(spTrader == NULL)
				{
					spTrader = m_pTraderColl->AddNew(nID, rs[L"vcAcronym"], &pTrader);
					if(spTrader != NULL && pTrader!=NULL)
					{
						pTrader->m_nGroupID = rs[L"iTraderGroupID"];

						IEtsTraderGroupAtomPtr spTraderGroup;
						m_pTraderGroup->get_Item(pTrader->m_nGroupID, &spTraderGroup);
						if(spTraderGroup!=NULL)
						{
							IEtsTraderCollPtr spTraderColl;
							spTraderGroup->get_Trader(&spTraderColl);
							if(spTraderColl!=NULL)
							{
								IEtsTraderAtomPtr spNew;
								spTraderColl->Add(nID, pTrader->m_bstrName, spTrader, &spNew);
							}
						}
					}
				}
				rs.MoveNext();
			}

			CStoredProc<CClientRecordset> rsTr(m_DbConnection, L"usp_TraderContractByTrader_Get");
			if(lTraderID)
				rsTr << lTraderID;
			rsTr.Open();
			if(rsTr.GetRecordCount())
			{
				rsTr.MoveFirst();
				while(!rsTr.IsEOF())
				{
					long lTraderId = rsTr[L"iTraderID"];
					IEtsTraderAtomPtr spTrader;
					m_pTraderColl->get_Item(lTraderId, &spTrader);
					if(spTrader!=NULL)
					{
						long lContractID = rsTr[L"iContractID"];
						IUndAtomPtr spUndAtom;
						m_pUnderlying->get_Item(lContractID, &spUndAtom);
						if(spUndAtom!=NULL)
						{
							IUndAtomPtr				spTraderUndAtom;
							IEtsTraderUndCollPtr	spTraderUndColl;
							spTrader->get_Und(&spTraderUndColl);
							if(spTraderUndColl!=NULL)
							{
								IEtsTraderUndAtomPtr spTrUndAtom;
								spTraderUndColl->get_Item(lContractID, &spTrUndAtom);
								if(spTrUndAtom == NULL)
								{	CComBSTR bsSymbol;
								spUndAtom->get_Symbol(&bsSymbol);
								IEtsTraderUndAtomPtr spNew;
								spTraderUndColl->Add(lContractID, bsSymbol, NULL, &spNew);
								if(spNew != NULL)
									spNew->putref_Und(spUndAtom);
								}
							}
						}
					}   

					rsTr.MoveNext();
				}
			}

		}
	}
	catch(_com_error& e )
	{
		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());

	}
	catch(...)
	{
		hr = Error(_T("Unknown Error in CEtsMain::LoadStrategy "), IID_IEtsMain, E_FAIL);
	}
	return hr;
}

//STDMETHODIMP CEtsMain::LoadUnderlying(LONG lTraderID)
//{
//	try
//	{
//		m_pUnderlying->Clear();
//		m_pUnderlyingAll->Clear();
//		m_pStock->Clear();
//		m_pOptRootByName->Clear();
//		m_pContract->Clear();
//		m_pContractAll->Clear();
//
//		_bstr_t bsStatus(L"Loading Underlying data...");
//
//		InitializeDB();
//		Fire_Progress(bsStatus,-1);
//		CStoredProc<> db(m_DbConnection, L"usp_MmUnderlying_Get");
//
//		if(lTraderID)
//			db << lTraderID;
//
//		CClientRecordset rs;
//		rs.Open(db);
//		long lTotalCount = rs.GetRecordCount();
//		long lLoaded = 0;
//		long lLastPerc = -1;
//		if(lTotalCount)
//		{
//			for(rs.MoveFirst(); !rs.IsEOF(); ++rs, ++lLoaded)
//			{
//				long lID = rs[L"iContractID"];
//				IUndAtomPtr spAtom;
//				m_pUnderlyingAll->get_Item(lID,&spAtom);
//				if(spAtom == NULL)
//				{
//					_bstr_t bsSymbol = rs[L"vcSymbol"];
//					CComObject<CUndAtom> *pObject  = NULL;
//
//					spAtom = m_pUnderlyingAll->AddNew(lID, bsSymbol, &pObject);
//					if(pObject)
//					{
//						pObject->m_enUndType		= static_cast<EtsContractTypeEnum>((long)rs[L"iContractTypeID"]);
//						pObject->m_bIsAmerican		= ((bool)rs[L"tiCalcOptionType"])?VARIANT_TRUE:VARIANT_FALSE;
//						pObject->m_bIsHTB			= ((bool)rs[L"tiIsHTB"])?VARIANT_TRUE:VARIANT_FALSE;
//						pObject->m_nExpCalendarID   = rs[L"iExpCalendarID"];
//						pObject->m_bstrPrimaryExchImportID = rs[L"PrimaryExchImportID"] ;
//						pObject->m_bstrImportID_DGH = rs[L"ImportID_DGH"] ;
//						pObject->m_bstrImportID		= rs[L"ImportID"] ;
//						pObject->m_lExtPosition		= rs[L"CEPiPositions"] ;
//
//						if(!pObject->m_nExpCalendarID)
//						{
//							ATLASSERT(FALSE);
//							if(m_spDefExpCalendar!=NULL)
//								m_spDefExpCalendar->get_ID(&pObject->m_nExpCalendarID);
//						}
//
//						pObject->m_bstrContractName	= rs[L"vcContractName"]; 
//						pObject->m_nLotSize			= 1;
//						pObject->m_dPriceClose      = rs[L"fPriceClose"];
//						pObject->m_dSkew            = rs[L"fSkew"];
//						pObject->m_dKurt		    = rs[L"fKurt"];
//						pObject->m_dSTDValue		= rs[L"StdValue"] ;
//
//						long lUndTraderID = rs[L"iTraderID"];
//						pObject->m_bIsTraderContract	= (lUndTraderID ==	lTraderID)?VARIANT_TRUE:VARIANT_FALSE;
//						pObject->m_bIsActive			= (bool)rs[L"tiIsActive"]?VARIANT_TRUE:VARIANT_FALSE;
//						pObject->m_nVolume10Day			= rs[L"iVolume10Day"];
//						pObject->m_nVolume5Expiration	= rs[L"iVolume5Expiration"];
//
//						long lUndPriceProfileID =rs[L"iUndPriceProfileID"];
//						long lOptPriceProfileID =rs[L"iOptPriceProfileID"];
//						m_pPriceProfile->get_Item(lUndPriceProfileID, &pObject->m_spUndPriceProfile);
//						m_pPriceProfile->get_Item(lOptPriceProfileID, &pObject->m_spOptPriceProfile);
//
//
//						switch(pObject->m_enUndType)
//						{
//						case enCtStock:
//							{
//								CComObject<CEtsIndexDivAtom>* pDivAtom = NULL;
//								CComObject<CEtsIndexDivAtom>::CreateInstance(&pDivAtom);
//								IEtsIndexDivAtomPtr spDivAtom;
//								if(pDivAtom)
//								{
//									spDivAtom.Attach(pDivAtom, TRUE);
//
//									pDivAtom->m_enDivType		= static_cast<EtsDivTypeEnum>((long)rs[L"tiIsDivCustom"]);
//									pDivAtom->m_nDivFreq		= rs[L"iDivFreq"];
//									pDivAtom->m_dtDivDate		= (vt_date) rs[L"dtDivDate"];
//									pDivAtom->m_dDivAmt			= rs[L"fDivAmt"];
//									pDivAtom->m_nDivFreqCust	= rs[L"iDivFreqCustom"];
//									pDivAtom->m_dtDivDateCust   = (vt_date) rs[L"dtDivDateCustom"];
//									pDivAtom->m_dDivAmtCust     = rs[L"fDivAmtCustom"];
//
//									pObject->m_spDividend		= spDivAtom;
//								}
//								if(pObject->m_spUndPriceProfile == NULL)
//									pObject->m_spUndPriceProfile = m_spDefStkPriceProfile;
//
//								IUndAtomPtr spUndAtom;
//								m_pStock->Add(lID, bsSymbol, spAtom, &spUndAtom);
//
//							}
//							break;
//						case enCtIndex:
//							{
//								pObject->m_dYield = rs[L"fYield"];
//								pObject->m_bIsBasketIndex = ((bool)rs[L"tiIsBasket"])?VARIANT_TRUE:VARIANT_FALSE;
//
//								if(pObject->m_spUndPriceProfile == NULL)
//									pObject->m_spUndPriceProfile = m_spDefIdxPriceProfile;
//
//								pObject->m_dSOQ = rs[L"SOQ"];
//							}
//							break;
//						}
//						if(pObject->m_spOptPriceProfile == NULL)
//							pObject->m_spOptPriceProfile = m_spDefOptPriceProfile;
//
//
//						if(pObject->m_bIsTraderContract)
//						{	
//							IUndAtomPtr spNewAtom;
//							m_pUnderlying->Add(lID, bsSymbol, spAtom, &spNewAtom);
//						}
//
//						IEtsContractAtomPtr	spContractAtom;
//						m_pContractAll->get_Item(lID, &spContractAtom);
//						if(spContractAtom==NULL)
//						{
//							CComObject<CEtsContractAtom>* pObj = NULL;
//							spContractAtom = m_pContractAll->AddNew(lID, bsSymbol, &pObj);
//							if(pObj)
//								pObj->m_spUnd = spAtom;
//							if(pObject->m_bIsTraderContract)
//							{
//								IEtsContractAtomPtr  spNA;
//								m_pContract->Add(lID, bsSymbol,spContractAtom, &spNA);
//							}
//						}
//					}
//				}
//				long lPerc = static_cast<long>( 100.* double(lLoaded)/ double(lTotalCount));
//				if(lPerc != lLastPerc)
//				{
//					lLastPerc = lPerc;
//					Fire_Progress(bsStatus,lLastPerc);
//				}
//			}
//		}
//	}
//	catch(_com_error& e )
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());
//
//	}
//	catch(...)
//	{
//		return Error(_T("Unknown Error in CEtsMain::LoadUnderlying "), IID_IEtsMain, E_FAIL);
//	}
//	return S_OK;
//}

//// EtsMain.cpp : Implementation of CEtsMain
//
//#include "stdafx.h"
//#include "EtsMain.h"
//
//
//// CEtsMain
//STDMETHODIMP CEtsMain::Clear()
//{
//	try
//	{
//		_Clear();
//
//	}
//	catch(_com_error& e )
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());
//
//	}
//	catch(...)
//	{
//		return Error(_T("Unknown Error in Main::Clear "), IID_IEtsMain, E_FAIL);
//	}
//	return S_OK;
//}
//
//STDMETHODIMP CEtsMain::LoadStrategy()
//{
//	try
//	{
//		Fire_Progress(L"Loading strategies data...", -1);
//
//		m_pStrategy->Clear();
//		InitializeDB();
//		CStoredProc<> sp(m_DbConnection, L"usp_Strategy_Get");
//		CClientRecordset rs;
//		rs.Open(sp);
//		if(rs.GetRecordCount())
//		{
//			rs.MoveFirst();
//			while(!rs.IsEOF())
//			{
//				IEtsStrategyAtomPtr spStrategy;
//				long lStrategyID = rs[L"iStrategyID"];
//
//				m_pStrategy->get_Item(lStrategyID, &spStrategy);
//				if(spStrategy == NULL)
//				{
//					_bstr_t bsStrategyName = rs[L"vcStrategyName"];
//					_bstr_t bsDescription  = rs[L"vcDescription"];
//
//					spStrategy = m_pStrategy->AddNew(lStrategyID, bsStrategyName, bsDescription);
//				}
//				rs.MoveNext();
//			}
//		}
//	}
//	catch(_com_error& e )
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());
//
//	}
//	catch(...)
//	{
//		return Error(_T("Unknown Error in CEtsMain::LoadStrategy "), IID_IEtsMain, E_FAIL);
//	}
//	return S_OK;
//}
//STDMETHODIMP CEtsMain::LoadBroker()
//{
//	try
//	{
//		Fire_Progress(L"Loading brokers data...", -1);
//
//		m_pBroker->Clear();
//		m_pClearingBroker->Clear();
//		InitializeDB();
//
//		CStoredProc<CClientRecordset> rs(m_DbConnection, L"usp_Broker_Get");
//		rs.Open();
//		if(rs.GetRecordCount())
//		{
//			rs.MoveFirst();
//			while(!rs.IsEOF())
//			{
//				long lID = rs[L"iBrokerID"];
//				bool bIsClearing = rs[L"tiIsClearing"];
//				
//				IEtsBrokerAtomPtr spBroker;
//				CComObject<CEtsBrokerAtom>* pAtom= NULL;
//				if(!bIsClearing)
//				{
//					m_pBroker->get_Item(lID, &spBroker);
//					if(spBroker == NULL)
//					{
//						IEtsBrokerAtomPtr spAtom = m_pBroker->AddNew(lID, rs[L"vcBrokerName"], rs[L"vcDescription"], &pAtom);
//						if(spAtom!=NULL && pAtom!=NULL)
//						{
//							pAtom->m_bIsClearing = VARIANT_FALSE;
//							pAtom->m_dUndComm    = rs[L"fUndComm"];
//							pAtom->m_dOptRegComm = rs[L"fOptRegComm"];
//							pAtom->m_dOptSpreadComm = rs[L"fOptSpreadComm"];
//							pAtom->m_dLowPremComm = rs[L"fLowPremComm"];
//						}
//					}
//				}
//				else
//				{
//					m_pClearingBroker->get_Item(lID, &spBroker);
//					if(spBroker == NULL)
//					{
//						IEtsBrokerAtomPtr spAtom = m_pClearingBroker->AddNew(lID, rs[L"vcBrokerName"], rs[L"vcDescription"], &pAtom);
//						if(spAtom!=NULL && pAtom!=NULL)
//						{
//							pAtom->m_bIsClearing = VARIANT_TRUE;
//							pAtom->m_dUndComm    = rs[L"fUndComm"];
//							pAtom->m_dOptRegComm = rs[L"fOptRegComm"];
//							pAtom->m_dOptSpreadComm = rs[L"fOptSpreadComm"];
//							pAtom->m_dLowPremComm = rs[L"fLowPremComm"];
//						}
//					}
//				}
//				rs.MoveNext();
//			}
//		}
//	}
//	catch(_com_error& e )
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());
//
//	}
//	catch(...)
//	{
//		return Error(_T("Unknown Error in CEtsMain::LoadBroker "), IID_IEtsMain, E_FAIL);
//	}
//	return S_OK;
//}
//
//
//STDMETHODIMP CEtsMain::LoadTraderGroup()
//{
//	HRESULT hr = S_OK;
//	try
//	{
//		Fire_Progress(L"Loading trader groups data...",-1);
//
//		m_pTraderGroup->Clear();
//		InitializeDB();
//		
//		// Add Default Data
//		m_pTraderGroup->AddNew(0, L"<Default>", L"Default Trader Group");
//
//		CStoredProc<CClientRecordset> rs(m_DbConnection, L"usp_TraderGroup_Get");
//		rs.Open();
//		if(rs.GetRecordCount())
//		{
//			rs.MoveFirst();
//			while(!rs.IsEOF())
//			{
//				long nID = rs[L"iTraderGroupID"];
//				IEtsTraderGroupAtomPtr spTraderGroup;
//				CComObject<CEtsTraderGroupAtom> pTraderGroup = NULL;
//				m_pTraderGroup->get_Item(nID, &spTraderGroup);
//				if(spTraderGroup == NULL)
//					m_pTraderGroup->AddNew(nID, rs[L"vcGroupName"], rs[L"vcGroupDesc"]);
//
//				rs.MoveNext();
//			}
//		}
//	}
//	catch(_com_error& e )
//	{
//		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());
//
//	}
//	catch(...)
//	{
//		hr = Error(_T("Unknown Error in CEtsMain::LoadStrategy "), IID_IEtsMain, E_FAIL);
//	}
//	return hr;
//}
//STDMETHODIMP CEtsMain::LoadTrader(LONG lTraderID)
//{
//	HRESULT hr = S_OK;
//	try
//	{
//		Fire_Progress(L"Loading traders data...",-1);
//		m_pTraderColl->Clear();
//		InitializeDB();
//
//		CStoredProc<CClientRecordset> rs(m_DbConnection, L"usp_Trader_Get");
//		if(lTraderID)
//			rs << lTraderID;
//		rs.Open();
//		if(rs.GetRecordCount())
//		{
//			rs.MoveFirst();
//			while (!rs.IsEOF()) 
//			{
//				IEtsTraderAtomPtr spTrader;
//				CComObject<CEtsTraderAtom>* pTrader = NULL;
//
//				long nID = rs[L"iTraderID"];
//				m_pTraderColl->get_Item(nID, &spTrader);
//				if(spTrader == NULL)
//				{
//					spTrader = m_pTraderColl->AddNew(nID, rs[L"vcAcronym"], &pTrader);
//					if(spTrader != NULL && pTrader!=NULL)
//					{
//						pTrader->m_nGroupID = rs[L"iTraderGroupID"];
//
//						IEtsTraderGroupAtomPtr spTraderGroup;
//						m_pTraderGroup->get_Item(pTrader->m_nGroupID, &spTraderGroup);
//						if(spTraderGroup!=NULL)
//						{
//							IEtsTraderCollPtr spTraderColl;
//							spTraderGroup->get_Trader(&spTraderColl);
//							if(spTraderColl!=NULL)
//							{
//								IEtsTraderAtomPtr spNew;
//								spTraderColl->Add(nID, pTrader->m_bstrName, spTrader, &spNew);
//							}
//						}
//					}
//				}
//				rs.MoveNext();
//			}
//
//			CStoredProc<CClientRecordset> rsTr(m_DbConnection, L"usp_TraderContractByTrader_Get");
//			if(lTraderID)
//				rsTr << lTraderID;
//			rsTr.Open();
//			if(rsTr.GetRecordCount())
//			{
//				rsTr.MoveFirst();
//				while(!rsTr.IsEOF())
//				{
//					long lTraderId = rsTr[L"iTraderID"];
//					IEtsTraderAtomPtr spTrader;
//					m_pTraderColl->get_Item(lTraderId, &spTrader);
//					if(spTrader!=NULL)
//					{
//						long lContractID = rsTr[L"iContractID"];
//						IUndAtomPtr spUndAtom;
//						m_pUnderlying->get_Item(lContractID, &spUndAtom);
//						if(spUndAtom!=NULL)
//						{
//							IUndAtomPtr				spTraderUndAtom;
//							IEtsTraderUndCollPtr	spTraderUndColl;
//							spTrader->get_Und(&spTraderUndColl);
//							if(spTraderUndColl!=NULL)
//							{
//								IEtsTraderUndAtomPtr spTrUndAtom;
//								spTraderUndColl->get_Item(lContractID, &spTrUndAtom);
//								if(spTrUndAtom == NULL)
//								{	CComBSTR bsSymbol;
//									spUndAtom->get_Symbol(&bsSymbol);
//									IEtsTraderUndAtomPtr spNew;
//									spTraderUndColl->Add(lContractID, bsSymbol, NULL, &spNew);
//									if(spNew != NULL)
//										spNew->putref_Und(spUndAtom);
//								}
//							}
//						}
//					}   
//
//					rsTr.MoveNext();
//				}
//			}
//
//		}
//	}
//	catch(_com_error& e )
//	{
//		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());
//
//	}
//	catch(...)
//	{
//		hr = Error(_T("Unknown Error in CEtsMain::LoadStrategy "), IID_IEtsMain, E_FAIL);
//	}
//	return hr;
//}
//
STDMETHODIMP CEtsMain::LoadUnderlying(LONG lTraderID)
{
	try
	{
		m_pUnderlying->Clear();
		m_pUnderlyingAll->Clear();
		m_pStock->Clear();
		m_pOptRootByName->Clear();
		m_pContract->Clear();
		m_pContractAll->Clear();
		_bstr_t bsStatus("Loading Underlying data...");

		InitializeDB();
		Fire_Progress(bsStatus,-1);
		CStoredProc<> db(m_DbConnection, L"usp_MmUnderlying_Get");
		
		if(lTraderID)
			db << lTraderID;
		
		CClientRecordset rs;
		rs.Open(db);
		long lTotalCount = rs.GetRecordCount();
		long lLoaded = 0;
		long lLastPerc = -1;
		if(lTotalCount)
		{
			for(rs.MoveFirst(); !rs.IsEOF(); ++rs, ++lLoaded)
			{
				long lID = rs[L"iContractID"];
				IUndAtomPtr spAtom;
				m_pUnderlyingAll->get_Item(lID,&spAtom);
				if(spAtom == NULL)
				{
					_bstr_t bsSymbol = rs[L"vcSymbol"];
					CComObject<CUndAtom> *pObject  = NULL;

					spAtom = m_pUnderlyingAll->AddNew(lID, bsSymbol, &pObject);
					if(pObject)
					{
						pObject->m_enUndType		= static_cast<EtsContractTypeEnum>((long)rs[L"iContractTypeID"]);
						pObject->m_bIsAmerican		= ((bool)rs[L"tiCalcOptionType"])?VARIANT_TRUE:VARIANT_FALSE;
						pObject->m_bIsHTB			= ((bool)rs[L"tiIsHTB"])?VARIANT_TRUE:VARIANT_FALSE;

						pObject->m_bstrContractName	= rs[L"vcContractName"]; 
						pObject->m_nLotSize			= 1;
						pObject->m_dPriceClose      = rs[L"fPriceClose"];
						pObject->m_dPriceTheoClose	 = rs[L"fPriceTheoClose"];

						pObject->m_dSkew            = rs[L"fSkew"];
						pObject->m_dKurt		    = rs[L"fKurt"];
						pObject->m_bIsHedgeSymbol = ((bool)rs[L"tiIsHedgeSymbol"]) ? VARIANT_TRUE : VARIANT_FALSE;

						long lUndTraderID = rs[L"iTraderID"];
						pObject->m_bIsTraderContract	= (lUndTraderID ==	lTraderID)?VARIANT_TRUE:VARIANT_FALSE;
						pObject->m_bIsActive			= (bool)rs[L"tiIsActive"]?VARIANT_TRUE:VARIANT_FALSE;
						pObject->m_nVolume10Day			= rs[L"iVolume10Day"];
						pObject->m_nVolume5Expiration	= rs[L"iVolume5Expiration"];
						pObject->m_nPrimaryExchangeID	= rs[L"iPrimaryExchangeID"];
						pObject->m_dManualActivePrice = rs[L"dManualActivePrice"];
						pObject->m_fIsManualVol = (bool)rs[L"fManualVol"]?VARIANT_TRUE:VARIANT_FALSE;

						long lUndPriceProfileID =rs[L"iUndPriceProfileID"];
						long lOptPriceProfileID =rs[L"iOptPriceProfileID"];
						m_pPriceProfile->get_Item(lUndPriceProfileID, &pObject->m_spUndPriceProfile);
						m_pPriceProfile->get_Item(lOptPriceProfileID, &pObject->m_spOptPriceProfile);


						switch(pObject->m_enUndType)
						{
						case enCtStock:
							{

								CComObject<CEtsIndexDivAtom>* pDivAtom = NULL;
								CComObject<CEtsIndexDivAtom>::CreateInstance(&pDivAtom);
								IEtsIndexDivAtomPtr spDivAtom;
								if(pDivAtom)
								{
									spDivAtom.Attach(pDivAtom, TRUE);

									pDivAtom->m_enDivType		= static_cast<EtsDivTypeEnum>((long)rs[L"tiIsDivCustom"]);
									pDivAtom->m_nDivFreq		= rs[L"iDivFreq"];
									pDivAtom->m_dtDivDate		= (vt_date) rs[L"dtDivDate"];
									pDivAtom->m_dDivAmt			= rs[L"fDivAmt"];
									pDivAtom->m_nDivFreqCust	= rs[L"iDivFreqCustom"];
									pDivAtom->m_dtDivDateCust   = (vt_date) rs[L"dtDivDateCustom"];
									pDivAtom->m_dDivAmtCust     = rs[L"fDivAmtCustom"];

									pObject->m_spDividend		= spDivAtom;
								}
								if(pObject->m_spUndPriceProfile == NULL)
									pObject->m_spUndPriceProfile = m_spDefStkPriceProfile;

								IUndAtomPtr spUndAtom;
								m_pStock->Add(lID, bsSymbol, spAtom, &spUndAtom);

							}
							break;
						case enCtIndex:
							{
								pObject->m_dYield = rs[L"fYield"];
								pObject->m_bIsBasketIndex = ((bool)rs[L"tiIsBasket"])?VARIANT_TRUE:VARIANT_FALSE;

								CComObject<CEtsIndexDivAtom>* pDivAtom = NULL;
								CComObject<CEtsIndexDivAtom>::CreateInstance(&pDivAtom);
								IEtsIndexDivAtomPtr spDivAtom;
								if(pDivAtom)
								{
									spDivAtom.Attach(pDivAtom, TRUE);

									pDivAtom->m_enDivType		= static_cast<EtsDivTypeEnum>((long)rs[L"tiIsDivCustom"]);

									pObject->m_spDividend		= spDivAtom;
								}

								if(pObject->m_spUndPriceProfile == NULL)
									pObject->m_spUndPriceProfile = m_spDefIdxPriceProfile;
								
								pObject->m_dSOQ = rs[L"SOQ"];
							}
							break;
						}
						if(pObject->m_spOptPriceProfile == NULL)
							pObject->m_spOptPriceProfile = m_spDefOptPriceProfile;


						if(pObject->m_bIsTraderContract)
						{	
							IUndAtomPtr spNewAtom;
							m_pUnderlying->Add(lID, bsSymbol, spAtom, &spNewAtom);
						}

						IEtsContractAtomPtr	spContractAtom;
						m_pContractAll->get_Item(lID, &spContractAtom);
						if(spContractAtom==NULL)
						{
							CComObject<CEtsContractAtom>* pObj = NULL;
							spContractAtom = m_pContractAll->AddNew(lID, bsSymbol, &pObj);
							if(pObj)
								pObj->m_spUnd = spAtom;
							if(pObject->m_bIsTraderContract)
							{
								IEtsContractAtomPtr  spNA;
								m_pContract->Add(lID, bsSymbol,spContractAtom, &spNA);
							}
						}
					}
				}
				long lPerc = static_cast<long>( 100.* double(lLoaded)/ double(lTotalCount));
				if(lPerc != lLastPerc)
				{
					lLastPerc = lPerc;
					Fire_Progress(bsStatus,lLastPerc);
				}
			}
		}
		LoadAssetGroup();
	}
	catch(_com_error& e )
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());

	}
	catch(...)
	{
		return Error(_T("Unknown Error in CEtsMain::LoadUnderlying "), IID_IEtsMain, E_FAIL);
	}
	return S_OK;
}

STDMETHODIMP CEtsMain::LoadAssetGroup()
{
	try
	{

		_bstr_t bsStatus("Loading Asset Group data...");

		InitializeDB();
		Fire_Progress(bsStatus,-1);
		CStoredProc<> db(m_DbConnection, L"usp_AllGroupAssets_Get");

		CClientRecordset rs;
		rs.Open(db);
		long lTotalCount = rs.GetRecordCount();
		long lLoaded = 0;
		long lLastPerc = -1;

		if(lTotalCount)
		{
			for(rs.MoveFirst(); !rs.IsEOF(); ++rs, ++lLoaded)
			{
				long	lHeadID			= rs[L"iHeadID"];
				long	lElementID		= rs[L"iElementID"];
				bool	bPriceByHead	= rs[L"bPriceByHead"];
				double	dCoeff			= rs[L"fCoeff"];


				IUndAtomPtr spHead;
				m_pUnderlyingAll->get_Item(lHeadID, &spHead);
				if(spHead)
				{
					spHead->put_IsHead( VARIANT_TRUE );
					spHead->put_Coeff( 1.0 );

					IUndAtomPtr spElement;
					m_pUnderlyingAll->get_Item(lElementID, &spElement);

					if(spElement)
					{
						spElement->put_PriceByHead(bPriceByHead ? VARIANT_TRUE : VARIANT_FALSE);
						spElement->put_Coeff(dCoeff);
						spElement->putref_HeadComponent(spHead);
					}

				}

				long lPerc = static_cast<long>( 100.* double(lLoaded)/ double(lTotalCount));
				if(lPerc != lLastPerc)
				{
					lLastPerc = lPerc;
					Fire_Progress(bsStatus, lLastPerc);
				}
			}
		}
	}
	catch(_com_error& e )
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());

	}
	catch(...)
	{
		return Error(_T("Unknown Error in CEtsMain::LoadAssetGroup "), IID_IEtsMain, E_FAIL);
	}
	return S_OK;
}