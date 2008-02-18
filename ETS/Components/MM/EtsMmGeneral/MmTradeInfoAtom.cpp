// MmTradeInfoAtom.cpp : Implementation of CMmTradeInfoAtom

#include "stdafx.h"
#include "MmTradeInfoAtom.h"

_variant_t CMmTradeInfoAtom::bsTradeTypeActual(L"Actual");
_variant_t CMmTradeInfoAtom::bsTradeTypeSimulated(L"Simulated");
_variant_t CMmTradeInfoAtom::bsTradeTypeManual(L"Manual");
_variant_t CMmTradeInfoAtom::bsTradeTypeUnknown(L"<Unknown>");
_variant_t CMmTradeInfoAtom::bsEmpty(L"");
_variant_t CMmTradeInfoAtom::bsNA(L"--");


/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::CopyTo(IMmTradeInfoAtom* pDest)
{
	try
	{
		if(!pDest)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		HRESULT hr = S_OK;
		IMmTradeInfoAtomPtr spDest(pDest);

		__CHECK_HRESULT3(spDest->put_TradeID(m_nTradeID));
		__CHECK_HRESULT3(spDest->put_SeqNum(m_nSeqNum));		
		__CHECK_HRESULT3(spDest->put_Price(m_dPrice));	
		__CHECK_HRESULT3(spDest->put_Quantity(m_nQuantity));	
		__CHECK_HRESULT3(spDest->put_IsBuy(m_bIsBuy));	
		__CHECK_HRESULT3(spDest->put_TradeDate(m_dtTradeDate));		
		__CHECK_HRESULT3(spDest->put_SpotReference(m_dSpotReference));
		__CHECK_HRESULT3(spDest->put_TradedIV(m_dTradedIV));
		__CHECK_HRESULT3(spDest->put_IsPosition(m_bIsPosition));
		__CHECK_HRESULT3(spDest->put_Status(m_enStatus));
		__CHECK_HRESULT3(spDest->put_BrokerCommission(m_dBrokerCommission));
		__CHECK_HRESULT3(spDest->put_ClearingBrokerCommission(m_dClearingBrokerCommission));
		__CHECK_HRESULT3(spDest->put_Mark(m_nMark));

		__CHECK_HRESULT3(spDest->putref_Und(m_spUnd));
		__CHECK_HRESULT3(spDest->putref_OptRoot(m_spOptRoot));
		__CHECK_HRESULT3(spDest->putref_Trader(m_spTrader));
		__CHECK_HRESULT3(spDest->putref_Broker(m_spBroker));
		__CHECK_HRESULT3(spDest->putref_ClearingBroker(m_spClearingBroker));
		__CHECK_HRESULT3(spDest->putref_Strategy(m_spStrategy));
		__CHECK_HRESULT3(spDest->putref_FutRoot(m_spFutRoot));
		__CHECK_HRESULT3(spDest->putref_Fut(m_spFut));

		if(m_spOpt != NULL)
		{
			IEtsOptAtomPtr spDestOpt;
			__CHECK_HRESULT3(spDest->get_Opt(&spDestOpt));

			if(spDestOpt == NULL)
			{
				__CHECK_HRESULT(spDestOpt.CreateInstance(CLSID_EtsOptAtom), 
								_T("Fail to create option data."));
				__CHECK_HRESULT3(spDest->putref_Opt(spDestOpt));
			}

			__CHECK_HRESULT(m_spOpt->CopyTo(spDestOpt),_T("Fail to copy option data."));
		}
		else
			__CHECK_HRESULT3(spDest->putref_Opt(NULL));

		if(m_spFutOpt != NULL)
		{
			IEtsFutOptAtomPtr spDestFutOpt;
			__CHECK_HRESULT3(spDest->get_FutOpt(&spDestFutOpt));

			if(spDestFutOpt == NULL)
			{
				__CHECK_HRESULT(spDestFutOpt.CreateInstance(CLSID_EtsFutOptAtom), 
								_T("Fail to create futures option data."));
				__CHECK_HRESULT3(spDest->putref_FutOpt(spDestFutOpt));
			}

			__CHECK_HRESULT(m_spFutOpt->CopyTo(spDestFutOpt),_T("Fail to copy futures option data."));
		}
		else
			__CHECK_HRESULT3(spDest->putref_FutOpt(NULL));
	
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::GetTradeTypeString(BSTR* pDest)
{
	try
	{
		if(!pDest)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(*pDest)
			::SysFreeString(*pDest);

		*pDest = TradeTypeString().copy();
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::GetTradeMatchedString(BSTR* pDest)
{
	try	
	{
		if(!pDest)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(*pDest)
			::SysFreeString(*pDest);

		switch(m_enStatus)
		{
			case enTrsMatchedRealtime:
				*pDest = ::SysAllocString(L"Yes");
				break;

			case enTrsRealtime:
				*pDest = ::SysAllocString(L"No");
				break;

			default:
				*pDest = SysAllocString(L"");
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_ContractID(LONG* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spOpt != NULL)
		{
			__CHECK_HRESULT3(m_spOpt->get_ID(pRetVal));
		}
		else if(m_spFutOpt != NULL)
		{
			__CHECK_HRESULT3(m_spFutOpt->get_ID(pRetVal));
		}
		else if(m_spFut != NULL)
		{
			__CHECK_HRESULT3(m_spFut->get_ID(pRetVal));
		}
		else if(m_spUnd != NULL)
		{
			__CHECK_HRESULT3(m_spUnd->get_ID(pRetVal));
		}
		else
			*pRetVal = 0;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_ContractType(enum EtsContractTypeEnum* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spOpt != NULL)
		{
			*pRetVal = enCtOption;
		}
		else if(m_spFutOpt != NULL)
		{
			*pRetVal = enCtFutOption;
		}
		else if(m_spFut != NULL)
		{
			*pRetVal = enCtFuture;
		}
		else if(m_spUnd != NULL)
		{
			__CHECK_HRESULT3(m_spUnd->get_UndType(pRetVal));
		}
		else
			*pRetVal = static_cast<EtsContractTypeEnum>(0);
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_Symbol(BSTR* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(*pRetVal)
			::SysFreeString(*pRetVal);

		if(m_spOpt != NULL)
		{
			__CHECK_HRESULT3(m_spOpt->get_Symbol(pRetVal));
		}
		else if(m_spFutOpt != NULL)
		{
			__CHECK_HRESULT3(m_spFutOpt->get_Symbol(pRetVal));
		}
		else if(m_spFut != NULL)
		{
			__CHECK_HRESULT3(m_spFut->get_Symbol(pRetVal));
		}
		else if(m_spUnd != NULL)
		{
			__CHECK_HRESULT3(m_spUnd->get_Symbol(pRetVal));
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_UndID(LONG* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spUnd != NULL)
			*pRetVal = m_spUnd->ID;
		else
			*pRetVal = 0;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_OptRootID(LONG* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spOptRoot != NULL)
		{
			__CHECK_HRESULT3(m_spOptRoot->get_ID(pRetVal));
		}
		else
			*pRetVal = 0;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_FutRootID(LONG* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spFutRoot != NULL)
		{
			__CHECK_HRESULT3(m_spFutRoot->get_ID(pRetVal));
		}
		else
			*pRetVal = 0;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_FutID(LONG* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spFut != NULL)
		{
			__CHECK_HRESULT3(m_spFut->get_ID(pRetVal));
		}
		else
			*pRetVal = 0;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_LotSize(LONG* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spOptRoot != NULL)
		{
			__CHECK_HRESULT3(m_spOptRoot->get_LotSize(pRetVal));
		}
		else if(m_spFutRoot != NULL)
		{
			if(m_spFutOpt != NULL)
			{
				LONG nFutLotSize = 0L;
				__CHECK_HRESULT3(m_spFutRoot->get_FutLotSize(&nFutLotSize));
				__CHECK_HRESULT3(m_spFutRoot->get_OptLotSize(pRetVal));
				*pRetVal = *pRetVal * nFutLotSize;
			}
			else if(m_spFut != NULL)
			{
				__CHECK_HRESULT3(m_spFutRoot->get_FutLotSize(pRetVal));
			}
		}
		else if(m_spUnd != NULL)
		{
			__CHECK_HRESULT3(m_spUnd->get_LotSize(pRetVal));
		}
		else
			*pRetVal = 0;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_TotalCommission(DOUBLE* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		*pRetVal = m_dBrokerCommission + m_dClearingBrokerCommission;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_TotalPrice(DOUBLE* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		LONG nLotSize = 0L;
		__CHECK_HRESULT3(get_LotSize(&nLotSize));
		*pRetVal = m_dPrice * m_nQuantity * nLotSize;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_StrategyID(LONG* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spStrategy != NULL)
		{
			__CHECK_HRESULT3(m_spStrategy->get_ID(pRetVal));
		}
		else
			*pRetVal = 0;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_ContractName(BSTR* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(*pRetVal)
			::SysFreeString(*pRetVal);

		if(m_spOpt != NULL)
		{
			__CHECK_HRESULT3(m_spOpt->get_Series(pRetVal));
		}
		else if(m_spFutOpt != NULL)
		{
			__CHECK_HRESULT3(m_spFutOpt->get_Series(pRetVal));
		}
		else if(m_spFut != NULL)
		{
			__CHECK_HRESULT3(m_spFut->get_ContractName(pRetVal));
		}
		else if(m_spUnd != NULL)
		{
			__CHECK_HRESULT3(m_spUnd->get_ContractName(pRetVal));
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_BrokerID(LONG* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spBroker != NULL)
		{
			__CHECK_HRESULT3(m_spBroker->get_ID(pRetVal));
		}
		else
			*pRetVal = 0;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_ClearingBrokerID(LONG* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spClearingBroker != NULL)
		{
			__CHECK_HRESULT3(m_spClearingBroker->get_ID(pRetVal));
		}
		else
			*pRetVal = 0;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CMmTradeInfoAtom::get_ImportID(BSTR* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(*pRetVal)
			::SysFreeString(*pRetVal);

		if(m_spOpt != NULL)
		{
			__CHECK_HRESULT3(m_spOpt->get_ImportID(pRetVal));
		}
		else if(m_spFutOpt != NULL)
		{
			__CHECK_HRESULT3(m_spFutOpt->get_ImportID(pRetVal));
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}

HRESULT CMmTradeInfoAtom::Load(EtsContractTypeEnum enType, CClientRecordset& rc)
{
		m_nTradeID    = rc[L"iTradeID"];
		m_dPrice      = rc[L"fPrice"];
		m_nQuantity   = rc[L"iQuantity"];
		m_bIsBuy      = long(rc[L"tiIsBuy"]) != 0 ? VARIANT_TRUE:VARIANT_FALSE;
		m_bIsPosition = long(rc[L"tiIsPosition"]) != 0 ? VARIANT_TRUE:VARIANT_FALSE;

		EgLib::CGMTTimeZone tz;
		m_dtTradeDate = tz.GMTTimeZoneToLocal(rc[L"dtTradeDate"]);

		m_enStatus = static_cast<EtsTradeStatusEnum>(long(rc[L"tiStatus"]));
		m_dBrokerCommission			=	rc[L"fBrokerCommission"];
		m_dClearingBrokerCommission =	rc[L"fClearingBrokerCommission"];
		m_nMark					    =   rc[L"iMark"];
		m_nOrderID					=	rc[L"iOrderID"];
		m_nExecStatus				=	rc[L"iExecStatus"];
		//m_dManualActivePrice		= rc[L"fManualPrice"];
		switch(enType)
		{
		case enCtOption:
			{
				long lOptionRootID	= rc[L"iOptionRootID"];
				m_spOptRoot			= m_spUnd->Roots->Item[lOptionRootID];
				
				m_spOpt				= IEtsOptAtomPtr(__uuidof(EtsOptAtom));

				m_spOpt->RootID			= lOptionRootID;
				m_spOpt->ID				= rc[L"iContractID"];
				m_spOpt->Symbol			= rc[L"vcSymbol"];
				m_spOpt->OptType		= static_cast<EtsOptionTypeEnum>((long)rc[L"tiIsCall"]);
				m_spOpt->Expiry			= rc[L"dtExpiry"];
				m_spOpt->Strike			= rc[L"fStrike"];
				m_spOpt->PriceClose		= rc[L"fPriceClose"];
				m_spOpt->PriceTheoClose = rc[L"fPriceTheoClose"];
				m_spOpt->Series			= rc[L"vcContractName"];
				m_spOpt->ImportID		= rc[L"vcImportID"];
				m_spOpt->Flex			= rc[L"iIsFlex"];
				m_dSpotReference		= rc[L"fSpotReference"];
				m_dTradedIV				= rc[L"fTradedIV"];

				m_spOpt->ExpiryOV		= rc[L"dtExpiryOV"];
				m_spOpt->TradingClose	= rc[L"dtTradingClose"];

				m_spOpt->TradingClose	= m_spOpt->TradingClose - floor(m_spOpt->TradingClose);
			}
			break;
		case enCtFuture:
			{
				m_spFutRoot = m_spUnd->FutRoots->Item[rc[L"iFutureRootID"]];
				m_spFut		= m_spFutRoot->Futures->Item[rc[L"iFutureID"]];

			}break;
		case enCtFutOption:
			{
				long lFutureRootID	= rc[L"iFutureRootID"];
				long lFutureID		= rc[L"iFutureID"];

				m_spFutRoot					= m_spUnd->FutRoots->Item[lFutureRootID];
				m_spFut						= m_spFutRoot->Futures->Item[lFutureID];

				m_spFutOpt					= IEtsFutOptAtomPtr(__uuidof(EtsFutOptAtom));
				m_spFutOpt->FutID			= lFutureID;
				m_spFutOpt->ID				= rc[L"iContractID"];
				m_spFutOpt->Symbol			= rc[L"vcSymbol"];
				m_spFutOpt->OptType			=  static_cast<EtsOptionTypeEnum>((long)rc[L"tiIsCall"]);;
				m_spFutOpt->Expiry			= rc[L"dtExpiry"];
				m_spFutOpt->Strike			= rc[L"fStrike"];
				m_spFutOpt->PriceClose		= rc[L"fPriceClose"];
				m_spFutOpt->PriceTheoClose	= rc[L"fPriceTheoClose"];
				m_spFutOpt->Series			= rc[L"vcContractName"];
				m_spFutOpt->ImportID		= rc[L"vcImportID"];
				m_dSpotReference			= rc[L"fSpotReference"];
				m_dTradedIV					= rc[L"fTradedIV"];

				m_spFutOpt->ExpiryOV		= rc[L"dtExpiryOV"];
				m_spFutOpt->TradingClose	= rc[L"dtTradingClose"];

				m_spFutOpt->TradingClose	= m_spFutOpt->TradingClose - floor(m_spFutOpt->TradingClose);
			}
		case enCtIndex:
		case enCtStock:
			{
				if(m_spUnd->TotalQtyInShares == BAD_LONG_VALUE)
					m_spUnd->TotalQtyInShares =  m_nQuantity * (m_bIsBuy!=VARIANT_FALSE?1:-1);
				else
					m_spUnd->TotalQtyInShares +=  m_nQuantity * (m_bIsBuy!=VARIANT_FALSE?1:-1);

					if(m_enStatus != enTrsSimulated && m_spUnd->PriceClose >= DBL_EPSILON)
						m_spUnd->UndPosForRates += (m_nQuantity * m_spUnd->PriceClose * (m_bIsBuy!=VARIANT_FALSE?1:-1));
			} break;
		}
	return S_OK;
}


bool CMmTradeInfoAtom::GetField(TradesListColumnEnum field, _variant_t& vtRet, bool bForCompare)
{
	vtRet = vtMissing;
	switch(field)
	{
	case TLC_KEY:
		vtRet = _variant_t(m_nTradeID);
		break;
	case TLC_TYPE:
		vtRet = TradeTypeString();
		break;
	case TLC_UNDERLYING:
		if(!m_bsUndSymbol.length())
			m_bsUndSymbol =  m_spUnd->Symbol;
		vtRet = m_bsUndSymbol;
		break;
	case TLC_SYMBOL:
		if(!m_bsTlcSymbol.length())
		{
			CComBSTR bsSymbol;
			if(SUCCEEDED(get_Symbol(&bsSymbol)))
				m_bsTlcSymbol = (BSTR)bsSymbol;
		}
		vtRet = m_bsTlcSymbol;
		break;
	case TLC_OPT_TYPE:
		{
			EtsContractTypeEnum enType; 
			get_ContractType(&enType);
			switch(enType)
			{
			case enCtOption:
				if(m_spOpt != NULL)
					vtRet = m_spOpt->OptType == enOtCall?_bstr_t(L"C"):_bstr_t(L"P");
				break;
			case enCtFutOption:
				if(m_spFutOpt != NULL)
					vtRet = m_spFutOpt->OptType == enOtCall?_bstr_t(L"C"):_bstr_t(L"P");
				break;
			default:
				vtRet = bsEmpty;
			}
		}break;
	case TLC_DTE:
		EtsContractTypeEnum enType; 
		get_ContractType(&enType);
		switch(enType)
		{
		case enCtOption:
			{
				if( m_spOpt != NULL )
				{
					DATE expiryDateOV = m_spOpt->ExpiryOV;

					typedef boost::date_time::local_adjustor<ptime, -5, us_dst> us_eastern;
					ptime	ptNYNow = us_eastern::utc_to_local(second_clock::universal_time());
					tm		tmNYNow = to_tm(ptNYNow);
					vt_date dtToday(tmNYNow.tm_year + 1900, tmNYNow.tm_mon + 1, tmNYNow.tm_mday,
						tmNYNow.tm_hour, tmNYNow.tm_min);

					vt_date dtTimeToExp( expiryDateOV - (DATE)dtToday > 0 ? expiryDateOV - (DATE)dtToday : 0 );

					std::wstring wsFormat;
					wchar_t buffer[1024];
					if( dtTimeToExp < 2 )
						wsFormat = L"%d day %02d:%02d";
					else
						wsFormat = L"%d days %02d:%02d";

					_snwprintf_s(buffer, sizeof(buffer), wsFormat.c_str(), static_cast<LONG>((DATE)dtTimeToExp), dtTimeToExp.get_hour(), dtTimeToExp.get_minute() );
					vtRet =(wchar_t*)buffer;

					//long lDTE = static_cast<long>(m_spOpt->Expiry)- static_cast<long>(vt_date::GetCurrentDate(true));
					//vtRet = _variant_t(lDTE>0?lDTE:0L);
				}
			}break;
		case enCtFutOption:
			{
				if( m_spFutOpt!= NULL )
				{
					DATE expiryDateOV = m_spFutOpt->ExpiryOV;

					typedef boost::date_time::local_adjustor<ptime, -5, us_dst> us_eastern;
					ptime	ptNYNow = us_eastern::utc_to_local(second_clock::universal_time());
					tm		tmNYNow = to_tm(ptNYNow);
					vt_date dtToday(tmNYNow.tm_year + 1900, tmNYNow.tm_mon + 1, tmNYNow.tm_mday,
						tmNYNow.tm_hour, tmNYNow.tm_min);

					vt_date dtTimeToExp( expiryDateOV - (DATE)dtToday > 0 ? expiryDateOV - (DATE)dtToday : 0 );

					std::wstring wsFormat;
					wchar_t buffer[1024];
					if( dtTimeToExp < 2 )
						wsFormat = L"%d day %02d:%02d";
					else
						wsFormat = L"%d days %02d:%02d";

					_snwprintf_s(buffer, sizeof(buffer), wsFormat.c_str(), static_cast<LONG>((DATE)dtTimeToExp), dtTimeToExp.get_hour(), dtTimeToExp.get_minute() );
					vtRet =(wchar_t*)buffer;

					//long lDTE = static_cast<long>(m_spFutOpt->Expiry)- static_cast<long>(vt_date::GetCurrentDate(true));
					//vtRet = _variant_t(lDTE>0?lDTE:0L);
				}
			}break;
		default:
			if(bForCompare)
				vtRet = _variant_t(-1L);
			else
				vtRet = bsEmpty;
		}
		break;
	case TLC_EXPIRY:
		{
			EtsContractTypeEnum enType; 
			get_ContractType(&enType);
			switch(enType)
			{
			case enCtOption:
				if(m_spOpt!=NULL)
					vtRet = vt_date(m_spOpt->Expiry).GetVtDate();
				break;
			case enCtFutOption:
				{
					if(m_spFutOpt!=NULL)
						vtRet = vt_date(m_spFutOpt->Expiry).GetVtDate();
				}break;
			default:
				if(bForCompare)
					vtRet = vt_date().GetVtDate();
				else
					vtRet = bsEmpty;
			}
		}break;
	case TLC_STRIKE:
		{
			EtsContractTypeEnum enType; 
			get_ContractType(&enType);
			switch(enType)
			{
			case enCtOption:
				{
					if(m_spOpt != NULL)
						vtRet = m_spOpt->Strike;
				}break;
			case enCtFutOption:
				{
					if(m_spFutOpt != NULL)
						vtRet = m_spFutOpt->Strike;
				}break;
			default:
				if(bForCompare)
					vtRet = _variant_t(-1.);
				else
					vtRet = bsEmpty;
			}
		}break;
	case TLC_BS:
		vtRet = _variant_t(m_bIsBuy);
		break;
	case TLC_PRICE:
		if(m_bIsPosition)
		{
			if(bForCompare)
				vtRet =  _variant_t(0.0);
			else
				vtRet =  _variant_t(L"--");
		}
		else
			vtRet = _variant_t(m_dPrice);
		break;
	case TLC_QTY:
		vtRet = _variant_t(m_nQuantity);
		break;
	case TLC_TRADETYPE:
		{
			if(m_bIsPosition)
				vtRet = _variant_t(L"Position");
			else
				vtRet = _variant_t(L"Trade");
		}break;
	case TLC_LOTSIZE:
		{
			long lLotPrice = 0;
			get_LotSize(&lLotPrice);
			vtRet = _variant_t(lLotPrice);
		}
		break;
	case TLC_TOT_PRICE:
		{
			if(m_bIsPosition)
			{
				if(bForCompare)
					vtRet =  _variant_t(0.0);
				else
					vtRet =  _variant_t(L"--");
			}
			else
			{
				double dTotalPrice = 0;
				get_TotalPrice(&dTotalPrice);
				vtRet = _variant_t(dTotalPrice);
			}
		}break;
	case TLC_DATE:
		{
			DATE dtTrade = 0;
			get_TradeDate(&dtTrade);
			vtRet = vt_date(dtTrade).GetVtDate();
		}break;
	case TLC_TRADER:
		vtRet = m_spTrader->Name;
		break;
	case TLC_STRATEGY:
		{
			if(m_spStrategy != NULL)
				vtRet = m_spStrategy->Name;
			else
				vtRet = bsEmpty;
		}break;
	case TLC_BROKER:
		{
			if(m_spBroker!=NULL)
				vtRet = m_spBroker->Name;
			else
				vtRet = bsEmpty;
		}break;
	case TLC_CLR_BROKER:
		{
			if(m_spClearingBroker!=NULL)
				vtRet = m_spClearingBroker->Name;
			else
				vtRet = bsEmpty;
		}break;
	case TLC_COMMISSION:
		{
			double dTotalCommission = 0;
			get_TotalCommission(&dTotalCommission);
			vtRet = dTotalCommission;
		}break;
	case TLC_MATCHED:
		{
			CComBSTR bsMatched;
			GetTradeMatchedString(&bsMatched);
			vtRet = (BSTR)bsMatched;
		}
		break;
	case TLC_MARKED:
		vtRet = _variant_t(m_nMark);
		break;
	case TLC_FUT_ROOT:
		{
			EtsContractTypeEnum enType; 
			get_ContractType(&enType);
			if((enCtFuture == enType || enCtFutOption == enType) && m_spFutRoot!=NULL)
				vtRet = m_spFutRoot->Symbol;
			else
				vtRet = bsEmpty;

		}break;
	case TLC_FUTURES:
		{
			EtsContractTypeEnum enType; 
			get_ContractType(&enType);
			if((enCtFuture == enType || enCtFutOption == enType) && m_spFut!=NULL)
				vtRet = m_spFut->Symbol;
			else
				vtRet = bsEmpty;
		}break;
	case TLC_FUT_MATURITY:
		{
			EtsContractTypeEnum enType; 
			get_ContractType(&enType);
			if((enCtFuture == enType || enCtFutOption == enType) && m_spFut!=NULL)
				vtRet = vt_date(m_spFut->MaturityDate).GetVtDate(); 
			else
				vtRet = bForCompare?vt_date(0).GetVtDate():bsEmpty;

		}break;
	case TLC_STOCKREFPRICE:
		{
			EtsContractTypeEnum enType; 
			get_ContractType(&enType);
			if(enCtOption == enType || enCtFutOption == enType)
				vtRet = m_dSpotReference; 
			else
			{
				if(bForCompare)
					vtRet = _variant_t(-10000);
				else
					vtRet = bsEmpty;
			}

		}break;
	case TLC_TRADED_IV:
		{
			EtsContractTypeEnum enType; 
			get_ContractType(&enType);
			if(enCtOption == enType || enCtFutOption == enType)
				vtRet = m_dTradedIV*100.; 
			else
			{
				if(bForCompare)
					vtRet = _variant_t(-10000);
				else
					vtRet = bsEmpty;
			}
		}break;
	}
	return utils::HasValue(vtRet);
}

STDMETHODIMP CMmTradeInfoAtom::get_ExecStatusString(BSTR* pRetVal)
{
	try
	{
		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		EtsOrderExecutionStatusEnum enExecStatus = static_cast<EtsOrderExecutionStatusEnum>(m_nExecStatus);

		if(*pRetVal)
			::SysFreeString(*pRetVal);

		switch(enExecStatus)
		{
		case enOesNew:
			*pRetVal = ::SysAllocString(L"NEW");
			break;

		case enOesPartiallyFilled:
			*pRetVal = ::SysAllocString(L"PART");
			break;

		case enOesFilled:
			*pRetVal = ::SysAllocString(L"FILL");
			break;

		case enOesDoneForDay:
			*pRetVal = ::SysAllocString(L"DFD");
			break;

		case enOesCanceled:
			*pRetVal = ::SysAllocString(L"CXL");
			break;

		case enOesReplaced:
			*pRetVal = ::SysAllocString(L"CXLR");
			break;

		case enOesPendingCancelReplace:
			*pRetVal = ::SysAllocString(L"@CXLR");
			break;

		case enOesStopped:
			*pRetVal = ::SysAllocString(L"STOP");
			break;

		case enOesRejected:
			*pRetVal = ::SysAllocString(L"RJCT");
			break;

		case enOesSuspended:
			*pRetVal = ::SysAllocString(L"SPND");
			break;

		case enOesPendingNew:
			*pRetVal = ::SysAllocString(L"@NEW");
			break;

		case enOesCalculated:
			*pRetVal = ::SysAllocString(L"CALC");
			break;

		case enOesExpired:
			*pRetVal = ::SysAllocString(L"EXP");
			break;

		default:
			*pRetVal = ::SysAllocString(L"???");
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeInfoAtom, e.Error());
	}

	return S_OK;
}