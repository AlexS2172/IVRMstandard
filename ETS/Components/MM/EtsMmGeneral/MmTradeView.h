// MmTradeView.h : Declaration of the CMmTradeView

#pragma once
#include "resource.h"       // main symbols

#include "EtsMmGeneral.h"
#include "MmTradeChannel.h"
#include "_IMmTradeViewEvents_CP.h"


// CMmTradeView
typedef std::set<long> SelectionSet;
class CTradeViewSort
{
public:
	CTradeViewSort(TradesListColumnEnum enColumn, EtsSortingEnum enSortType)
		:m_enSortField(enColumn)
		,m_enSortType(enSortType){}


private:
	TradesListColumnEnum m_enSortField;
	EtsSortingEnum		 m_enSortType;
public:
	bool operator()(const IMmTradeInfoAtomPtr& Ptr1,  const IMmTradeInfoAtomPtr& sPtr2);
};

class ATL_NO_VTABLE CMmTradeView : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMmTradeView, &CLSID_MmTradeView>,
	public ISupportErrorInfoImpl<&IID_IMmTradeView>,
	public IConnectionPointContainerImpl<CMmTradeView>,
	public CProxy_IMmTradeViewEvents<CMmTradeView>, 
	public IDispatchImpl<IMmTradeView, &IID_IMmTradeView, &LIBID_EtsMmGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0> ,
	public IDispatchImpl<VSFLEX::IVSFlexDataSource, &__uuidof(VSFLEX::IVSFlexDataSource), &VSFLEX::LIBID_VSFLEX, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMmTradeView()
		:m_pTradeChannel(NULL)
		,m_enSortField(TLC_DATE)
		,m_enSortType(enSortDescending)
		,m_lVisibleColumns(0L)
	{
		//ZeroMemory(m_TradeViewFilters, sizeof(m_TradeViewFilters));
		ZeroMemory(m_ColumnsEncoding, sizeof(m_ColumnsEncoding));
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MMTRADEVIEW)


	BEGIN_COM_MAP(CMmTradeView)
		COM_INTERFACE_ENTRY(IMmTradeView)
		COM_INTERFACE_ENTRY(VSFLEX::IVSFlexDataSource)
		COM_INTERFACE_ENTRY2(IDispatch, IMmTradeView)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CMmTradeView)
		CONNECTION_POINT_ENTRY(__uuidof(_IMmTradeViewEvents))
	END_CONNECTION_POINT_MAP()
	// ISupportsErrorInfo

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		try {
			_CHK(m_spFilterData.CreateInstance(__uuidof(EtsFilterData) ), _T("Failed to create filter data"));
			_CHK(m_spFilterData->Initialize(TFC_UNDERLYING,TFC_COLUMN_COUNT), _T("Failed to initialize filter"));
		}
		catch (_com_error& e) {
			return Error((PTCHAR)CComErrorWrapper::ErrorDescription(e), IID_IMmTradeView, e.Error());
		}
		return S_OK;
	}

	void FinalRelease() 
	{
		m_spFilterData = NULL;
	}

public:

	STDMETHOD(raw_GetFieldCount) (/*[out,retval]*/ long * pFields );
	STDMETHOD(raw_GetRecordCount)(/*[out,retval]*/ long * pRecords );
	STDMETHOD(raw_GetFieldName)  (/*[in]*/ long Field, /*[out,retval]*/ BSTR * pFieldName );
	STDMETHOD(raw_GetData)		 (/*[in]*/ long Field, /*[in]*/ long Record, /*[out,retval]*/ BSTR * pData );
	STDMETHOD(raw_SetData)		 (/*[in]*/ long Field,	/*[in]*/ long Record,/*[in]*/ BSTR newData );


public:
	STDMETHOD(get_TradeViewFilter)(/*[in]*/ EtsTradesFilterEnum Filter, /*[out, retval]*/ LONG* pVal);	
	STDMETHOD(put_TradeViewFilter)(/*[in]*/ EtsTradesFilterEnum Filter, /*[in]*/ LONG newVal);
	IMPLEMENT_OBJECTREADONLY_PROPERTY( IEtsFilterData*, FilterData, m_spFilterData);
	STDMETHOD(put_TradeViewColumnsOrder)(SAFEARRAY** colOrder);
	STDMETHOD(Sort)(TradesListColumnEnum enField, EtsSortingEnum enSort);

	STDMETHOD(Refresh)()
	{
		m_vecShow.clear();
		m_pTradeChannel->FilterData(/*m_TradeViewFilters*/m_spFilterData, m_vecShow);
		PerformSorting();
		return S_OK;
	}

	STDMETHOD(ClearSelected)()
	{
		m_SelSet.clear();
		return S_OK;
	}
	STDMETHOD(SetTradeAsSelected)(LONG TradeID)
	{
		m_SelSet.insert(TradeID);
		return S_OK;
	}
	STDMETHOD(IsSelectedTrade)(LONG TradeID, VARIANT_BOOL* bIsSel)
	{
		__CHECK_POINTER(bIsSel);

		*bIsSel = FALSE;

		if(m_SelSet.find(TradeID)!=m_SelSet.end())
		{
			*bIsSel = TRUE;
		}
		return S_OK;
	}

	STDMETHOD(get_RowData)(LONG lRow, IMmTradeInfoAtom** ppVal);
	

private:
	CMmTradeChannel*	m_pTradeChannel;
	//long			m_TradeViewFilters[TFC_COLUMN_COUNT];
	long			m_ColumnsEncoding[TLC_COLUMN_COUNT];
	CTradeInfoViewData	m_vecShow;
	SelectionSet		m_SelSet;

	TradesListColumnEnum	m_enSortField;
	EtsSortingEnum			m_enSortType;
	long					m_lVisibleColumns;
	IEtsFilterDataPtr		m_spFilterData;
private:
	void PerformSorting()
	{
		if(!m_vecShow.empty())
		{
			CTradeViewSort sortingClass(m_enSortField, m_enSortType);
			std::sort(m_vecShow.begin(), m_vecShow.end(), sortingClass);
		}
	}
public:
	void SetTradeChannel(CMmTradeChannel* pChannel){m_pTradeChannel = pChannel;}
};

OBJECT_ENTRY_AUTO(__uuidof(MmTradeView), CMmTradeView)
