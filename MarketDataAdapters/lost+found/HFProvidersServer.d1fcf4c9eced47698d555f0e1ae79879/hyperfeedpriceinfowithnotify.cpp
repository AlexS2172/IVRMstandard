// HyperFeedPriceInfoWithNotify.cpp : Implementation of CHyperFeedPriceInfoWithNotifyWithNotify

#include "stdafx.h"
#include "HyperFeedPriceInfoWithNotify.h"

STDMETHODIMP CHyperFeedPriceInfoWithNotify::RequestLastQuote(QuoteUpdateParams *Params)
{
	ATLTRACE(_T("CHyperFeedPriceInfoWithNotify::RequestLastQuote\n"));
	try
	{
		CRequestBasePtr pRequest = CRequestBasePtr((CRequestBase*)new CQuoteRequest(_enRequestLast, Params));
		AddRequest(pRequest);
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"RequestLastQuote Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;
	return S_OK;
}
STDMETHODIMP CHyperFeedPriceInfoWithNotify::CancelLastQuote(VARIANT Params)
{
	ATLTRACE(_T("CHyperFeedPriceInfoWithNotify::CancelLastQuote\n"));
	try
	{
		if(V_VT(&Params) == VT_ERROR)
			RemoveAllRequest();
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"CancelLastQuote Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;
	return S_OK;
}
STDMETHODIMP CHyperFeedPriceInfoWithNotify::SubscribeQuote(QuoteUpdateParams *Params)
{
	ATLTRACE(_T("CHyperFeedPriceInfoWithNotify::SubscribeQuote: Start\n"));
	try
	{
		CRequestBasePtr pRequest = CRequestBasePtr((CRequestBase*)new CQuoteRequest(_enRequestRealtime, Params));
		AddRequest(pRequest);
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"SubscribeQuote Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;
	return S_OK;
}
STDMETHODIMP CHyperFeedPriceInfoWithNotify::UnSubscribeQuote(VARIANT Params)
{
	ATLTRACE(_T("CHyperFeedPriceInfoWithNotify::UnSubscribeQuote\n"));
	try
	{
		CGroupPrice::Unsubscribe(Params);
		if(V_VT(&Params) == VT_ERROR)
			RemoveAllRequest();
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"UnSubscribeQuote Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;

	return S_OK;
}
STDMETHODIMP CHyperFeedPriceInfoWithNotify::Connect()
{
	try 
	{
		ConnectProvider();
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"Connect Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;
	return S_OK;
}
STDMETHODIMP CHyperFeedPriceInfoWithNotify::Disconnect()
{
	try 
	{
		UnsubscribeAll();
		DisconnectProvider();
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"Disconnect Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;
	return S_OK;
}
STDMETHODIMP CHyperFeedPriceInfoWithNotify::RequestLastGroupQuotes(QuoteUpdateParams * Params)
{
	try
	{
		if(Params->Type != enGrSTK && Params->Type != enGrIDX)
			return E_INVALIDARG;

		CRequestBasePtr pRequest = CRequestBasePtr((CRequestBase*)new CGroupRequest(enGroupRequestLastQuote, Params));
		AddRequest(pRequest);
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"RequestLastGroupQuotes Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;
	return S_OK;
}

STDMETHODIMP CHyperFeedPriceInfoWithNotify::CancelLastGroupQuotes(VARIANT Params)
{
	try
	{
		CGroupPrice::CancelGroupPrice(Params);
		if(V_VT(&Params) == VT_ERROR)
			RemoveAllRequest();
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"CancelLastGroupQuotes Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;
	return S_OK;
}

STDMETHODIMP CHyperFeedPriceInfoWithNotify::SubscribeGroupQuotes(QuoteUpdateParams * Params)
{
	try
	{
		if(Params->Type != enGrSTK && Params->Type != enGrIDX)
			return E_INVALIDARG;

		CRequestBasePtr pRequest = CRequestBasePtr((CRequestBase*)new CGroupRequest(enGroupRequestAllNotify, Params));
		AddRequest(pRequest);
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"SubscribeGroupQuotes Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;
	return S_OK;
}

STDMETHODIMP CHyperFeedPriceInfoWithNotify::UnSubscribeGroupQuotes(VARIANT Params)
{
	try
	{
		CGroupPrice::UnsubscribeGroup(Params);
		if(V_VT(&Params) == VT_ERROR)
			RemoveAllRequest();
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"UnSubscribeGroupQuote Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;
	return S_OK;
}

void CHyperFeedPriceInfoWithNotify::OnResponse(CResponseBasePtr pResponse)
{
	switch(pResponse->m_enType)
	{
	case _enResponseLast:
		{
			CQuoteInfoResponse* pQuoteResponse = dynamic_cast<CQuoteInfoResponse*>(pResponse.get());
			if(pQuoteResponse)
				OnLastQuote(pQuoteResponse->m_vtParams, pQuoteResponse->m_vtInfo);
		}
		break;
	case _enResponseRealtime:
		{
			CQuoteInfoResponse* pQuoteResponse = dynamic_cast<CQuoteInfoResponse*>(pResponse.get());
			if(pQuoteResponse)
				OnQuoteUpdate(pQuoteResponse->m_vtParams, pQuoteResponse->m_vtInfo);
		}
		break;
	case _enResponseRealtimeNotification:
		{
			CSubscribedResponse* pSubsResponse = dynamic_cast<CSubscribedResponse*>(pResponse.get());
			if(pSubsResponse)
				OnSubscribed(pSubsResponse->m_vtParams);
		}
		break;
	}
}

void CHyperFeedPriceInfoWithNotify::OnRequest(CRequestBasePtr pRequest)
{
	switch(pRequest->m_enType)
	{
	case _enRequestLast:
		GetPrice(pRequest);
		break;
	case _enRequestRealtime:
		Subscribe(pRequest, true);
		break;
	case _enRequestGroup:
	{
		CGroupRequestPtr pGroupRequest = boost::shared_dynamic_cast<CGroupRequest>(pRequest);
		if(pGroupRequest)
		{
			if(enGroupRequestLastQuote == pGroupRequest->m_enGroupRequestType)
				GetGroupPrice(pGroupRequest->m_recParams);
			else
				SubscribeGroup(pGroupRequest->m_recParams, pGroupRequest->m_enGroupRequestType);
		}
	}
	break;
	}
}

HRESULT CHyperFeedPriceInfoWithNotify::OnLastQuote(const CComVariant &varParams, const CComVariant &varResults)
{
	ATLTRACE(_T("CHyperFeedPriceInfoWithNotify::OnLastQuote\n"));
	CComVariant varResult;
	HRESULT hr = S_OK;
	try
	{
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[2];
		int nConnections = m_vec.GetSize();


		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				VariantClear(&varResult);
				pvars[1] = varParams;
				pvars[0] = varResults;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };
				hr = pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
		}
		delete[] pvars;
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"OnLastQuote Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;

	if(FAILED(hr)) return hr;
	return varResult.scode;
}
HRESULT CHyperFeedPriceInfoWithNotify::OnQuoteUpdate(const CComVariant &varParams, const CComVariant &varResults)
{
	ATLTRACE(_T("CHyperFeedPriceInfoWithNotify::OnQuoteUpdate\n"));
	CComVariant varResult;
	HRESULT hr = S_OK;
	
	try
	{
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[2];
		int nConnections = m_vec.GetSize();
		

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				VariantClear(&varResult);
				pvars[1] = varParams;
				pvars[0] = varResults;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };
				hr = pDispatch->Invoke(0x2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
		}
		delete[] pvars;
	}
	_CATCH_COM_EXCEPTION_RETURN_COM( L"OnQuoteUpdate Failed")
	_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;

	if(FAILED(hr)) return hr;
	return varResult.scode;
	
	}

	HRESULT CHyperFeedPriceInfoWithNotify::OnSubscribed(const CComVariant &varParams)
	{
		//	CCriticalSectionWrapper cs(m_csEvent);
		CComVariant varResult;
		HRESULT hr = S_OK;
		try
		{
			ATLTRACE(_T("CHyperFeedPriceInfoWithNotify::OnSubscribed\n"));

			int nConnectionIndex;
			CComVariant* pvars = new CComVariant[1];
			int nConnections = m_vec.GetSize();


			for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
			{
				Lock();
				CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
				Unlock();

				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
				if (pDispatch != NULL)
				{
					VariantClear(&varResult);
					pvars[0] = varParams;
					DISPPARAMS disp = { pvars, NULL, 1, 0 };
					hr = pDispatch->Invoke(0x4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
				}
			}
			delete[] pvars;
		}
		_CATCH_COM_EXCEPTION_RETURN_COM( L"OnSubscribed Failed")
		_CATCH_UNHANDLED_EXCEPTION_RETURN_COM;
		if(FAILED(hr)) return hr;
		return varResult.scode;
}

long CHyperFeedPriceInfoWithNotify::Attach()
{
	long nRes;
	try
	 {
		nRes = CGroupPrice::Attach();
		if(nRes != DBA_ERR_NO_ERROR)
		{
			HRESULT hr = MAKE_HRESULT (SEVERITY_ERROR, FACILITY_ITF, nRes);
			EgLib::CComErrorWrapper::ThrowError(hr, _T("Failed to attach to price fundamental database."));
		}
	 }
	_CATCH_UNHANDLED_EXCEPTION;
	return nRes ;
}
long CHyperFeedPriceInfoWithNotify::Detach()
{
	
	long nRes;
	try
	{
		nRes = CGroupPrice::Detach();
		if(nRes != DBA_ERR_NO_ERROR)
		{
			HRESULT hr = MAKE_HRESULT (SEVERITY_ERROR, FACILITY_ITF, nRes);
			EgLib::CComErrorWrapper::ThrowError(hr, _T("Failed to detach from price fundamental database."));
		}
	}
	_CATCH_UNHANDLED_EXCEPTION;
	return nRes ;
}

void CHyperFeedPriceInfoWithNotify::PublicLastQuote(const _QuoteUpdateParams& Params, const DBA_RECORD_3& rec)
{
	try
	{
		_QuoteUpdateInfo info;
		CopyExtendedToInfo(rec, info);
		info->Exchange = SysAllocString(Params->Exchange);
		CResponseBasePtr pResponse = CResponseBasePtr((CResponseBase*)new CQuoteInfoResponse(_enResponseLast, Params, info));
		PublicResponse(pResponse);
		if(info->Currency)
		{
			SysFreeString(info->Currency);
			info->Currency;
		}
		if(info->Exchange)
		{
			SysFreeString(info->Exchange);
			info->Exchange;
		}
	}
_CATCH_UNHANDLED_EXCEPTION;

}

void CHyperFeedPriceInfoWithNotify::PublicQuoteUpdate(const _QuoteUpdateParams& Params, const DBA_RECORD_3& rec)
{
	try
	{
		_QuoteUpdateInfo info;
		CopyExtendedToInfo(rec, info);
		info->Exchange = SysAllocString(Params->Exchange);
		CResponseBasePtr pResponse = CResponseBasePtr((CResponseBase*)new CQuoteInfoResponse(_enResponseRealtime, Params, info));
		PublicResponse(pResponse);
		if(info->Currency)
		{
			SysFreeString(info->Currency);
			info->Currency;
		}
		if(info->Exchange)
		{
			SysFreeString(info->Exchange);
			info->Exchange;
		}
	}
_CATCH_UNHANDLED_EXCEPTION;

}