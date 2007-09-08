// MmTradeChannel.cpp : Implementation of CMmTradeChannel

#include "stdafx.h"
#include "MmTradeChannel.h"
#include "MmtradeView.h"
//#include "MmTradeByUndAtom.h"

// CMmTradeChannel

STDMETHODIMP CMmTradeChannel::UpdateManualActivePrices()
{
		/*CMmTradeInfoColl::EnumCollType::iterator itrX    = m_pTrd->m_coll.begin();
		CMmTradeInfoColl::EnumCollType::iterator itrXend = m_pTrd->m_coll.end();

		for(; itrX != itrXend; ++itrX)
		{
			IMmTradeInfoAtomPtr spTradeInfoAtom = itrX->second;
			CMmTradeInfoAtom*  pTradeInfoAtom = static_cast<CMmTradeInfoAtom*>((IMmTradeInfoAtom*)spTradeInfoAtom);
			pTradeInfoAtom->m_dManualActivePrice = 0;
		}

		IEnumVARIANTPtr _cts = this->m_spMain->Contract->_NewEnum;
		
		_cts->Reset();

		_variant_t var;

		while(_cts->Next(1L, &var, NULL) == S_OK)
		{
			IEtsContractAtomPtr ctr = var;

			if(ctr->Und != NULL)
			{
				ctr->Und->ManualActivePrice = 0;
			}
			
			if (ctr->Fut != NULL)
			{
				ctr->Fut->ManualActivePrice = 0;
			}
		}

		_cts = NULL;

		CStoredProc<CClientRecordset> rs(m_Connection, L"usp_MmManualPriceForTrade_Get");
		rs.Open();
		if(rs.GetRecordCount())
		{
			rs.MoveFirst();

			while (!rs.IsEOF()) 
			{
				IMmTradeInfoAtom* pTradeInfo = NULL;

				m_pTrd->get_Item((LONG)rs[L"TradeID"], &pTradeInfo);

				if(pTradeInfo != NULL)
				{
					static_cast<CMmTradeInfoAtom*>(pTradeInfo)->m_dManualActivePrice = rs[L"ManualPrice"];

					pTradeInfo->Release();
				}else 
				{
					LONG lCtrID = rs[L"ContractID"];

					IEtsContractAtomPtr ctr = this->m_spMain->Contract->GetItem((LONG)rs[L"ContractID"]);

					if (ctr != NULL)
					{
						if (ctr->Fut != NULL)
						{
							ctr->Fut->ManualActivePrice = rs[L"ManualPrice"];
						}
						else
						{
							ctr->Und->ManualActivePrice = rs[L"ManualPrice"];
						}
					}
				}

				rs.MoveNext();
			}
		}

		rs.Close();*/

		return S_OK;
}

STDMETHODIMP CMmTradeChannel::LoadTrades(LONG lTraderId, 
										 IEtsMain* pMain,
										 VARIANT_BOOL bShowProgress)
{
	HRESULT hr = S_OK;
	try
	{
		__CHECK_POINTER(pMain);
		m_spMain.Attach(pMain, TRUE);

		IUndCollPtr			spUndColl				= m_spMain->Underlying;
		IEtsTraderCollPtr	spTraderColl			= m_spMain->Trader; 
		IEtsBrokerCollPtr	spBrokerColl			= m_spMain->Broker;
		IEtsBrokerCollPtr	spClearingBrokerColl	= m_spMain->ClearingBroker;
		IEtsStrategyCollPtr spStrategyColl			= m_spMain->Strategy;

		if(!m_Connection.IsOpened())
			m_Connection.Open(m_bstrDatabase, 10, 120, 300, 300);

		m_pTrdForMatch->Clear();
		m_pTrdByUndMan->Clear();
		m_pTrdByUnd->Clear();
		m_pTrdByTraderAndContract->Clear();
		m_pTrdByFut->Clear();
		m_pTrd->Clear();

		CStoredProc<> spTrades(m_Connection, L"usp_MmTradeByTrader_Get");
		if(lTraderId)
			spTrades << lTraderId;
		CClientRecordset spRcTrades;
		spRcTrades.Open(spTrades);
		long lTradesCount = spRcTrades.GetRecordCount();
		long lLoaded = 0;
		long lLastPercent= -1;
		long lPercent = 0;
		_bstr_t bsNotificationText(L"Loading trades data...");

		if(lTradesCount)
		{
			Fire_Notification(bsNotificationText, -1);
			for(spRcTrades.MoveFirst(); !spRcTrades.IsEOF(); spRcTrades.MoveNext(), ++lLoaded)
			{
				long lUndId		= spRcTrades[L"iUnderlyingContractID"];
				long lTraderId  = spRcTrades[L"iTraderID"]; 

				IUndAtomPtr			spUnd;
				IEtsTraderAtomPtr	spTrader; 
				

				_CHK(spUndColl->get_Item(lUndId, &spUnd),		 _T("Unable to get Underlying"));
				_CHK(spTraderColl->get_Item(lTraderId, &spTrader), _T("Unable to get Trader"));

				if(spUnd!=NULL && spTrader!=NULL)
				{
					EtsContractTypeEnum enType = static_cast<EtsContractTypeEnum>(long(spRcTrades[L"iContractTypeID"]));
					IMmTradeInfoAtomPtr spTradeInfo;

					CComObject<CMmTradeInfoAtom>* pTradeInfo = NULL;
					_CHK(CComObject<CMmTradeInfoAtom>::CreateInstance(&pTradeInfo),_T("Unable to create Trade info"));
					spTradeInfo.Attach(pTradeInfo, true);
					pTradeInfo->m_spUnd    = spUnd;
					pTradeInfo->m_spTrader = spTrader;

					if(spBrokerColl!=NULL)
						_CHK(spBrokerColl->get_Item(spRcTrades[L"iBrokerID"], &pTradeInfo->m_spBroker),_T("Unable to get  Broker info")); 
					if(spClearingBrokerColl!=NULL)
						_CHK(spClearingBrokerColl->get_Item(spRcTrades[L"iClearingBrokerID"], &pTradeInfo->m_spClearingBroker),_T("Unable to get Clearing Broker info")); 

					if(spStrategyColl!=NULL)
						_CHK(spStrategyColl->get_Item(spRcTrades[L"iStrategyID"], &pTradeInfo->m_spStrategy),_T("Unable to get Strategy info")); 

					pTradeInfo->Load(enType, spRcTrades);

					AdjustTraderContractAndStrategy(pTradeInfo);
					IMmTradeInfoAtomPtr spNewTrade;
					m_pTrd->Add( pTradeInfo->m_nTradeID, pTradeInfo->m_dtTradeDate, spTradeInfo, &spNewTrade);

					AddTradeToTradesByUnd(pTradeInfo);
					AddTradeToTradesByTraderAndContract(pTradeInfo);
					AddManualTradeToTradesByUndMan(pTradeInfo);
					AddTradeToTradesByFut(pTradeInfo);
					lPercent = static_cast<long>(100. * double(lLoaded)/double(lTradesCount));

					if(lLastPercent != lPercent)
					{
						lLastPercent = lPercent;
						Fire_Notification(bsNotificationText, lLastPercent);
					}

				}
			}   

			this->UpdateManualActivePrices();
		}   
	}
	catch (_com_error& err)
	{
		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(err), __uuidof(IMmTradeChannel), err.Error());

	}
	catch(...)
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		hr = Error(_T("Fail to load Trades"), __uuidof(IMmTradeChannel), FAILED(hr)?hr:E_FAIL);
	}
	return hr;
}


void CMmTradeChannel::AddTradeToTradesByUnd(CComObject<CMmTradeInfoAtom>* pTrd)
{
	if(pTrd->m_spFut==NULL || !pTrd->m_spFut->ID)
	{
		_bstr_t	bsKey(pTrd->m_spUnd->ID);
		IMmTradeInfoCollPtr aTrdByUnd;
		m_pTrdByUnd->get_Item(bsKey, &aTrdByUnd);
		if(aTrdByUnd == NULL)
			m_pTrdByUnd->Add(bsKey, NULL, &aTrdByUnd);

		IMmTradeInfoAtomPtr spTrade;
		IMmTradeInfoAtomPtr spNewTrade;
		
		spTrade.Attach(pTrd, TRUE);
		aTrdByUnd->Add(pTrd->m_nTradeID, pTrd->m_dtTradeDate, spTrade,&spNewTrade);
	}
}
void CMmTradeChannel::AddTradeToTradesByTraderAndContract(CComObject<CMmTradeInfoAtom>* pTrd)
{
	_bstr_t bsTraderKey(pTrd->m_spTrader->ID);

	long lContractID = 0L;
	pTrd->get_ContractID(&lContractID);

	_bstr_t bsContractKey(lContractID);
	_bstr_t bsKey = bsTraderKey + _bstr_t(L"_") +bsContractKey;

	IMmTradeInfoCollPtr aTrdFind;
	m_pTrdByTraderAndContract->get_Item(bsKey, &aTrdFind);
	if(aTrdFind == NULL)
		m_pTrdByTraderAndContract->Add(bsKey, NULL, &aTrdFind);

	IMmTradeInfoAtomPtr spTrade;
	IMmTradeInfoAtomPtr spNewTrade;

	spTrade.Attach(pTrd, TRUE);
	aTrdFind->Add(pTrd->m_nTradeID, pTrd->m_dtTradeDate, spTrade,&spNewTrade);

}
void	CMmTradeChannel::AddManualTradeToTradesByUndMan(CComObject<CMmTradeInfoAtom>* pTrd)
{
	if(pTrd->m_enStatus == enTrsManual)
	{
		_bstr_t	bsKey(pTrd->m_spUnd->ID);
		bsKey+= L"_" + _bstr_t(pTrd->m_spTrader->ID);

		IMmTradeInfoCollPtr aTrdFind;
		m_pTrdByUndMan->get_Item(bsKey, &aTrdFind);
		if(NULL == aTrdFind)
			m_pTrdByUndMan->Add(bsKey, NULL, &aTrdFind);

		IMmTradeInfoAtomPtr spTrade;
		IMmTradeInfoAtomPtr spNewTrade;

		spTrade.Attach(pTrd, TRUE);
		aTrdFind->Add(pTrd->m_nTradeID, pTrd->m_dtTradeDate, spTrade,&spNewTrade);
	}

}
void	CMmTradeChannel::AddTradeToTradesByFut(CComObject<CMmTradeInfoAtom>* pTrd)
{
	long lFutID = pTrd->m_spFut!=NULL?pTrd->m_spFut->ID:0L;
	if(lFutID)
	{
		_bstr_t bsKey(lFutID);
		IMmTradeInfoCollPtr aTrdFind;
		m_pTrdByFut->get_Item(bsKey, &aTrdFind);
		if(aTrdFind == NULL)
			m_pTrdByFut->Add(bsKey, NULL, &aTrdFind);

		IMmTradeInfoAtomPtr spTrade;
		IMmTradeInfoAtomPtr spNewTrade;

		spTrade.Attach(pTrd, TRUE);
		aTrdFind->Add(pTrd->m_nTradeID, pTrd->m_dtTradeDate, spTrade,&spNewTrade);
	}
}
STDMETHODIMP CMmTradeChannel::LoadStrategy(LONG lStrategyID, IEtsStrategyAtom** pStrategyAtom, VARIANT_BOOL* bNew)
{
	if(!bNew)
		*bNew = false;

	if(m_spMain != NULL)	
	{
		IEtsStrategyAtomPtr spStrategy = m_spMain->Strategy->Item[lStrategyID];
		if(spStrategy !=NULL)
			*pStrategyAtom = spStrategy.Detach();
		else
		{
			if(!m_Connection.IsOpened())
				m_Connection.Open(m_bstrDatabase, 10, 120, 300, 300);

			CStoredProc<> sp(m_Connection, L"usp_Strategy_Get");
			sp << lStrategyID;
			
			CClientRecordset rs;
			rs.Open(sp);
			if(rs.GetRecordCount())
			{
				IEtsStrategyAtomPtr spNewStrategy = m_spMain->Strategy->Add(lStrategyID,(_bstr_t)rs[L"vcStrategyName"], NULL);
				spNewStrategy->Desc = rs[L"vcDescription"];
				*pStrategyAtom = spNewStrategy.Detach();
                if(!bNew) *bNew = true;
			}
		}
	}
	return S_OK;
}

HRESULT CMmTradeChannel::AdjustTraderContractAndStrategy(CComObject<CMmTradeInfoAtom>* pTrade, bool bFireEvents )
{
 	long lUndId = 0;
	 pTrade->get_UndID(&lUndId);

	IUndAtomPtr spUnd = m_spMain->UnderlyingAll->Item[lUndId];
	if(spUnd != NULL)
	{
		IEtsTraderAtomPtr spTrader;
		spUnd->IsTraderContract = VARIANT_TRUE;
		spTrader = m_spMain->Trader->Item[pTrade->m_spTrader->ID];
		if(spTrader != NULL)
		{
			IEtsStrategyAtomPtr spStrategy;
			VARIANT_BOOL bNewStrategy = VARIANT_FALSE;
			if(pTrade->m_spStrategy!=NULL)
				LoadStrategy(pTrade->m_spStrategy->ID, &spStrategy, &bNewStrategy);

			_bstr_t bsSymbol(spUnd->Symbol);

			IEtsTraderUndAtomPtr aTrdUnd = spTrader->Und->Item[lUndId];
			if(aTrdUnd == NULL)
				aTrdUnd = spTrader->Und->Add(lUndId, bsSymbol, NULL);
			 aTrdUnd->Und = spUnd;

			 if(spStrategy != NULL)
			 {
				 long lStrategyId = spStrategy->ID;
				 if(aTrdUnd->Strategy->Item[lStrategyId] == NULL)
					 aTrdUnd->Strategy->Add(lStrategyId,spStrategy->Name,spStrategy);
			 } 
			 IEtsContractAtomPtr spContractAll = m_spMain->ContractAll->Item[lUndId];
			 IEtsContractAtomPtr spContract = m_spMain->Contract->Item[lUndId];
			 if(spContractAll != NULL && spContract == NULL)
				 m_spMain->Contract->Add(lUndId, bsSymbol, spContractAll);

//				If g_Underlying(aUnd.ID) Is Nothing Then
//				g_Underlying.Add aUnd.ID, aUnd.Symbol, aUnd
//
//				g_Params.MakeUnderlingComboLists

				if(bFireEvents  )
				{
					//g_Params.FireNewUnderlyingAdded aUnd.ID
					if(bNewStrategy)
					{
						//		If bFireEvents And bNewStrategy And Not aStrategy Is Nothing Then g_Params.FireNewStrategyAdded aStrategy.ID
					}

				}


		}
	}

	/*
	Dim aUnd As EtsGeneralLib.UndAtom, aTrader As EtsGeneralLib.EtsTraderAtom
	Dim aTrdUnd As EtsGeneralLib.EtsTraderUndAtom, aContract As EtsGeneralLib.EtsContractAtom
	Dim aStrategy As EtsGeneralLib.EtsStrategyAtom
	Dim bNewStrategy As Boolean

	Set aUnd = g_UnderlyingAll(nUndID)
	If Not aUnd Is Nothing Then

	aUnd.IsTraderContract = True*/


	return S_OK;
}

STDMETHODIMP CMmTradeChannel::OpenTradeView(IMmTradeView** pTradeView)
{
	HRESULT hr = S_OK;
	try
	{
		CComObject<CMmTradeView>* pView = NULL;
		CComObject<CMmTradeView>::CreateInstance(&pView);
		if(pView)
		{
			pView->AddRef();
			*pTradeView = pView;
			pView->SetTradeChannel(this);
		}   
	}
	catch (_com_error& err)
	{
		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(err), __uuidof(IMmTradeChannel), err.Error());
	}
	return hr;
}


