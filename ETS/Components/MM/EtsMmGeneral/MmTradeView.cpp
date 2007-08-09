// MmTradeView.cpp : Implementation of CMmTradeView

#include "stdafx.h"
#include "MmTradeView.h"


// CMmTradeView
bool CTradeViewSort::operator()(const IMmTradeInfoAtomPtr& Ptr1,  const IMmTradeInfoAtomPtr& Ptr2)
{
	CMmTradeInfoAtom* pPtr1 = static_cast<CMmTradeInfoAtom*>((IMmTradeInfoAtom*)Ptr1);
	CMmTradeInfoAtom* pPtr2 = static_cast<CMmTradeInfoAtom*>((IMmTradeInfoAtom*)Ptr2);
	if(pPtr1 && pPtr2)
	{
		_variant_t vt1;  bool bvt1 = pPtr1->GetField(m_enSortField, vt1, true);
		_variant_t vt2;  bool bvt2 = pPtr2->GetField(m_enSortField, vt2, true);

		if(bvt1 && bvt2)
		{
			switch(vt1.vt)
			{
			case VT_I2:
				if(m_enSortType != enSortDescending)
					return V_I2(&vt1) < V_I2(&vt2);
				else
					return V_I2(&vt2) < V_I2(&vt1);
				break;
			case VT_I4:
				if(m_enSortType != enSortDescending)
					return V_I4(&vt1) < V_I4(&vt2);
				else
					return V_I4(&vt2) < V_I4(&vt1);
				break;
			case VT_R4:
				if(m_enSortType != enSortDescending)
					return V_R4(&vt1) < V_R4(&vt2);
				else
					return V_R4(&vt2) < V_R4(&vt1);
				break;
			case VT_R8:
				if(m_enSortType != enSortDescending)
					return V_R8(&vt1) < V_R8(&vt2);
				else
					return V_R8(&vt2) < V_R8(&vt1);
				break;
			case VT_DATE:
				if(m_enSortType != enSortDescending)
					return V_DATE(&vt1) < V_DATE(&vt2);
				else
					return V_DATE(&vt2) < V_DATE(&vt1);
			case VT_BSTR:
				if(m_enSortType != enSortDescending)
					return wcscmp(V_BSTR(&vt1) , V_BSTR(&vt2))<0;
				else
					return wcscmp(V_BSTR(&vt2) , V_BSTR(&vt1))<0;
			default:
				{
					_bstr_t bsT1(vt1);
					_bstr_t bsT2(vt2);
					if(m_enSortType != enSortDescending)
						return bsT1 < bsT2;
					else
						return bsT2 < bsT1;
				}
			}
		}
	}
	return true;
}


STDMETHODIMP CMmTradeView::get_TradeViewFilter(/*[in]*/ EtsTradesFilterEnum Filter, /*[out, retval]*/ LONG* pVal)
{
	try{
		if(!pVal) return E_POINTER;
		if(Filter > TFC_NONE && Filter <= TFC_LAST_COLUMN){
			//*pVal = m_TradeViewFilters[Filter];
			*pVal = m_spFilterData->Data[Filter];
		}
		else
			return E_INVALIDARG;
	}
	catch( _com_error& e){
		return Error((PTCHAR)CComErrorWrapper::ErrorDescription(e), IID_IMmTradeView, e.Error());
	}

	return S_OK;
}

STDMETHODIMP CMmTradeView::put_TradeViewFilter(/*[in]*/ EtsTradesFilterEnum Filter, /*[in]*/ LONG newVal)
{
	try {
		if(Filter > TFC_NONE && Filter <= TFC_LAST_COLUMN)
		{
			//long lOldOne = m_TradeViewFilters[Filter];
			//m_TradeViewFilters[Filter] = newVal;
			long lOldOne = m_spFilterData->Data[Filter];
			m_spFilterData->Data[Filter] = newVal;
			if(m_vecShow.empty() || lOldOne!=newVal)
			{
				m_pTradeChannel->FilterData(m_spFilterData, m_vecShow);
				PerformSorting();
			}
		}
		else
			return E_INVALIDARG;
	}
	catch (_com_error& e) {
		return Error((PTCHAR)CComErrorWrapper::ErrorDescription(e), IID_IMmTradeView, e.Error());
	}

	//FilterData();
	return S_OK;
}

STDMETHODIMP CMmTradeView::put_TradeViewColumnsOrder(SAFEARRAY** colOrder)
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

				if(j>=TLC_COLUMN_COUNT)
					break;
			}
		}
	}
	catch (...) {
	}
	return S_OK;
}

STDMETHODIMP CMmTradeView::raw_GetFieldCount (/*[out,retval]*/ long * pFields )
{
	//*pFields = static_cast<long>(TLC_COLUMN_COUNT);
	*pFields = m_lVisibleColumns+1;
	return S_OK;
}
STDMETHODIMP CMmTradeView::raw_GetRecordCount(/*[out,retval]*/ long * pRecords )
{
	*pRecords  = static_cast<long>(m_vecShow.size());
	return S_OK;
}
STDMETHODIMP CMmTradeView::raw_GetFieldName  (/*[in]*/ long Field, /*[out,retval]*/ BSTR * pFieldName )
{
	*pFieldName = SysAllocString(L"");
	return S_OK;
}
STDMETHODIMP CMmTradeView::raw_GetData		 (/*[in]*/ long Field, /*[in]*/ long Record, /*[out,retval]*/ BSTR * pData )
{
	*pData = NULL;
	if(Field > 0 && m_ColumnsEncoding[Field-1]>=0 && static_cast<size_t>(Record) < m_vecShow.size())
	{
		IMmTradeInfoAtomPtr spPtr = m_vecShow[Record];
		CMmTradeInfoAtom* pAtom = static_cast<CMmTradeInfoAtom*>((IMmTradeInfoAtom*)spPtr);

		_variant_t  vt; 
		if(pAtom->GetField(static_cast<TradesListColumnEnum>(m_ColumnsEncoding[Field-1]), vt))
			*pData = _bstr_t(vt).copy();
		else
		{
			*pData = ::SysAllocString(L"Unknown");
		}
	}
	if(!*pData)
		*pData = SysAllocString(L"Undefined");
	return S_OK;
}
STDMETHODIMP CMmTradeView::raw_SetData		 (/*[in]*/ long Field,	/*[in]*/ long Record,/*[in]*/ BSTR newData )
{
	return S_OK;
}

STDMETHODIMP CMmTradeView::Sort(TradesListColumnEnum enField, EtsSortingEnum enSort)
{
	bool bResort = false;
	if(m_enSortField != static_cast<TradesListColumnEnum>(m_ColumnsEncoding[enField-1]))
	{
		m_enSortField = static_cast<TradesListColumnEnum>(m_ColumnsEncoding[enField-1]);
		bResort		= true;
	}
	if(m_enSortType != enSort)
	{
		m_enSortType = enSort;
		bResort	   = true;
	}
	if(bResort)
		PerformSorting();
	return S_OK;
}

STDMETHODIMP CMmTradeView::get_RowData(LONG lRow, IMmTradeInfoAtom** ppVal)
{
	HRESULT hr = S_OK;
	try
	{
		if(ppVal && lRow > 0 )
		{
			size_t  lPos = static_cast<size_t>(lRow-1);
			if(m_vecShow.size()>lPos)
			{
				IMmTradeInfoAtomPtr spAtom = m_vecShow[lPos];
				if(spAtom!=NULL)
					*ppVal = spAtom.Detach();

			}
		}
	}
	catch (_com_error& err) 
	{
		hr = err.Error();
	}
	return hr;
}
