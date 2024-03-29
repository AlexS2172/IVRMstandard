// HyperFeedBatchPriceInfo.h : Declaration of the CHyperFeedBatchPriceInfo
#ifndef __HYPERFEEDBATCHPRICEINFO_H__
#define __HYPERFEEDBATCHPRICEINFO_H__

#pragma once
#include "resource.h"       // main symbols
#include "HyperFeedBase.h"
#include "GroupPrice.h"

/////////////////////////////////////////////////////////////////////////////


typedef boost::shared_ptr<_QuoteUpdateFullInfo>	_QuoteUpdateFullInfoPtr;
typedef hash_set<CSubscriptionInfoPtr,	CPtr_Compare<CSubscriptionInfoPtr> > CFullInfoDataCollection;

//typedef map<_bstr_t, _QuoteUpdateFullInfoPtr>	CFullInfoDataCollection;
//typedef map<_QuoteUpdateParams, CComVariant, 
//	_less<QuoteUpdateParams, __QuoteUpdateParams> > CFullInfoDataCollection;

// CHyperFeedBatchPriceInfo
class ATL_NO_VTABLE CHyperFeedBatchPriceInfo : 
	public CHyperFeedBase<CHyperFeedBatchPriceInfo>,
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CHyperFeedBatchPriceInfo, &CLSID_HyperFeedBatchPriceInfo>,
	public ISupportErrorInfoImpl<&IID_IPriceProvider>,
	public IConnectionPointContainerImpl<CHyperFeedBatchPriceInfo>,
	public IDispatchImpl<IPriceProvider, &IID_IPriceProvider, &LIBID_HYPERFEEDPROVIDERSLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<IBatchPriceProvider, &IID_IBatchPriceProvider, &LIBID_HYPERFEEDPROVIDERSLib>,
	public IDispatchImpl<IGroupPriceWithNotify, &IID_IGroupPriceWithNotify, &LIBID_HYPERFEEDPROVIDERSLib>,
	public IDispatchImpl<IUserInformation, &IID_IUserInformation, &LIBID_HYPERFEEDPROVIDERSLib>,
	public IConnectionPointImpl<CHyperFeedBatchPriceInfo, &DIID__IBatchPriceInfoEvents, CComDynamicUnkArray>,
	public CGroupPrice,
	public EgLib::CThread
	// We can use trace here as the CGroupPrice are inherited from CPrice
{
public:
	CHyperFeedBatchPriceInfo()
	  : m_bUpdate(false)
	  , m_dtLastUpdate(vt_date::GetCurrentDate())
	  ,m_lAveTimer(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_HYPERFEEDBATCHPRICEINFO)

BEGIN_COM_MAP(CHyperFeedBatchPriceInfo)
	COM_INTERFACE_ENTRY(IPriceProvider)
	COM_INTERFACE_ENTRY(IBatchPriceProvider)
	COM_INTERFACE_ENTRY2(IDispatch, IBatchPriceProvider)
	COM_INTERFACE_ENTRY(IGroupPriceWithNotify)
	COM_INTERFACE_ENTRY2(IDispatch, IGroupPriceWithNotify)
	COM_INTERFACE_ENTRY(IUserInformation)
	COM_INTERFACE_ENTRY2(IDispatch, IUserInformation)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CHyperFeedBatchPriceInfo)
	CONNECTION_POINT_ENTRY(DIID__IBatchPriceInfoEvents)
END_CONNECTION_POINT_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_hBatchDataReady.Attach(::CreateEvent(NULL, FALSE, FALSE, NULL));
		return ERROR_SUCCESS;
	}
	void FinalRelease() 
	{
		Disconnect();
	}

	// IPriceProvider
	STDMETHOD(RequestLastQuote)(QuoteUpdateParams *Params);
	STDMETHOD(CancelLastQuote)(VARIANT Params);
	STDMETHOD(SubscribeQuote)(QuoteUpdateParams *Params);
	STDMETHOD(UnSubscribeQuote)(VARIANT Params);
	STDMETHOD(Connect)();
	STDMETHOD(Disconnect)();
	// IBatchPriceProvider
	STDMETHOD(get_IsQuotesUpdated)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(GetQuotesUpdates)(/*[out, retval]*/ SAFEARRAY** pRetVal);
	
	// IGroupPriceWithNotify
	STDMETHOD(RequestLastGroupQuotes)(QuoteUpdateParams * Params);
	STDMETHOD(CancelLastGroupQuotes)(VARIANT Params);
	STDMETHOD(SubscribeGroupQuotes)(QuoteUpdateParams * Params);
	STDMETHOD(UnSubscribeGroupQuotes)(VARIANT Params);
	STDMETHOD(put_UserName)(BSTR userName);

	long Attach();
	long Detach();

	void OnResponse(CResponseBasePtr pResponse);
	void OnRequest(CRequestBasePtr pResponse);
	void OnAddResponse();

	UINT Run();
private:
	HRESULT OnLastQuote(const CComVariant &varParams, const CComVariant &varResults);
	HRESULT OnQuoteUpdate();
	HRESULT OnSubscribed(const CComVariant &varParams);

	virtual void PublicResponse(CResponseBasePtr pResponse){ AddResponse(pResponse);}
	virtual void PublicLastQuote(const _QuoteUpdateParams* pParams, const CDBARecordPtr& pData);
	virtual void PublicQuoteUpdate(const _QuoteUpdateParams* pParams, const CSubscriptionInfoPtr& pData);
	virtual void ProcessMessage(CSubscriptionInfoPtr& pExtRec);

	void AddClientUpdate()
	{
		try{
			if(m_spGlobalPerfCounter)
				m_spGlobalPerfCounter->AddClientUpdate();
			if(m_pPerfMon)
				m_pPerfMon->AddClientUpdate();
		}catch(...){}
	}

private:

	CFullInfoDataCollection			m_FullInfoData;
	CHandle                         m_hBatchDataReady;

	EgLib::CLock					m_csData;
	LONGLONG						m_lAveTimer;

	_bstr_t _GetKey(const QuoteUpdateParams* pParams)
	{
		_bstr_t bsRet = L"";
		if(pParams)
		{
			wchar_t szType[64] = { 0 };
			try
			{
				if(!pParams->Exchange)
					_snwprintf(szType, 63, L"%s__%d", pParams->Symbol, pParams->Type);
				else
					_snwprintf(szType, 63, L"%s_%s_%d", pParams->Symbol, pParams->Exchange, pParams->Type);
				bsRet = szType;

			}
			_CATCH_UNHANDLED_EXCEPTION;
		}
		return bsRet;
	}
	CLock		m_csUpdate;
	bool		m_bUpdate;
	vt_date		m_dtLastUpdate;
};

OBJECT_ENTRY_AUTO(__uuidof(HyperFeedBatchPriceInfo), CHyperFeedBatchPriceInfo)

#endif //__HYPERFEEDBATCHPRICEINFO_H__