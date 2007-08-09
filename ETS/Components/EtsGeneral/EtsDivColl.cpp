// EtsDivColl.cpp : Implementation of CEtsDivColl

#include "stdafx.h"
#include "EtsDivColl.h"

#include "OptionCalc\OptionCalc.h"
#include "OptionPriceModels\common.h"
#include ".\etsdivcoll.h"
#include <atlsafe.h>
#include <atlsafe.h>

// CEtsDivColl
STDMETHODIMP CEtsDivColl::GetDividends(LONG nToday, LONG nExpiry, LONG nCount, SAFEARRAY ** psaDivAmounts,  SAFEARRAY ** psaDivDates, LONG* pnCount)
{
	__CHECK_POINTER(pnCount);
	*pnCount = 0;
	__CHECK_POINTER(psaDivAmounts);
	__CHECK_POINTER(psaDivDates);

	if (nExpiry <= nToday) return S_OK;

	HRESULT hr = S_OK;
	try
	{
		CComSafeArray<double> spDates(nCount);
		CComSafeArray<double> spAmount(nCount);
//		if(m_nTodayCache == nToday && m_lExpryCache == nExpiry && m_bDivCacheInit)
//		{
//			spDates.CopyFrom(m_spDatesCache);
//			spAmount.CopyFrom(m_spAmountCache);
//		}
//		else
//		{
//			CComSafeArray<double> spDates(nCount);
//			CComSafeArray<double> spAmount(nCount);
			EnumIterType iter;
			EnumIterType iterStart = m_DivColl.upper_bound(nToday);
			EnumIterType iterExp = m_DivColl.lower_bound(nExpiry);
			EnumIterType iterEnd = m_DivColl.end();

			if ( iterStart != iterEnd && iterStart != iterExp )
			{
				LONG lDivCount = 0;
				LONG lCurDiv = 0;
				DOUBLE dDivDate;
				DOUBLE dCurAmount;

				for( iter = iterStart; iter != iterExp; ++iter)
				{
					dCurAmount = iter->second;
					dDivDate = iter->first;
					dDivDate = (dDivDate - nToday) / OPM::cdDaysPerYear365;

					spDates[lCurDiv] = dDivDate;
					spAmount[lCurDiv] = dCurAmount;

					++lCurDiv;
				}
				*pnCount = lCurDiv;
//				m_spDatesCache.CopyFrom(spDates);
//				m_spAmountCache.CopyFrom(spAmount);

				m_nTodayCache    = nToday;
				m_lExpryCache    = nExpiry;
				m_lQuantityCache = lCurDiv;
//				m_bDivCacheInit  = true;
//			}
		}
		*psaDivAmounts = spAmount.Detach();
		*psaDivDates = spDates.Detach();

	}
	catch(const _com_error& e)
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsDivColl, e.Error());
	}
	catch(...)
	{
		hr =  Error((PTCHAR)(_T("Unhandled exception at GetDividends")), IID_IEtsDivColl, E_FAIL);
	}
	return hr;
}

STDMETHODIMP CEtsDivColl::GetNearest( LONG nToday, LONG nExpiry, DOUBLE* pdDivAmount,  DOUBLE* pdDivDate)
{
	__CHECK_POINTER(pdDivAmount);
	__CHECK_POINTER(pdDivDate);

	if ( nExpiry > 0 && nExpiry <= nToday )	return E_FAIL;
	if ( m_nTodayCache != nToday ) ClearCache();

	HRESULT hr = S_OK;
	try
	{
		EnumIterType iterStart = m_DivColl.upper_bound(nToday);
		EnumIterType iterEnd = m_DivColl.end();
		EnumIterType iterExp;
		if (nExpiry > 0)
			iterExp = m_DivColl.lower_bound(nExpiry);
		else
			iterExp = iterEnd;

		

		if ((iterStart != iterEnd)&&(iterStart != iterExp))
		{
			*pdDivAmount = iterStart->second;	
			*pdDivDate = iterStart->first;
		}
	}
	catch(const _com_error& e)
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsDivColl, e.Error());
	}
	catch(...)
	{
		hr =  Error((PTCHAR)(_T("Unhandled exception at GetNearest")), IID_IEtsDivColl, E_FAIL);
	}
	return hr;
}



STDMETHODIMP CEtsDivColl::GetDividendCount(LONG nToday, LONG nExpiry,  LONG* pnCount)
{
	__CHECK_POINTER(pnCount);
	*pnCount = 0;
	long lCount = 0;

	if (nExpiry <= nToday) return S_OK;


	HRESULT hr = S_OK;
	try
	{
		if(m_nTodayCache == nToday && m_lExpryCache == nExpiry)
			*pnCount = m_lQuantityCache;
		else
		{
			EnumIterType iter;
			EnumIterType iterStart = m_DivColl.upper_bound(nToday);
			EnumIterType iterEnd = m_DivColl.end();
			EnumIterType iterExp = m_DivColl.lower_bound(nExpiry);

			if( iterStart != iterEnd && iterStart != iterExp )
				for(iter = iterStart; iter != iterExp; ++iter)
					++lCount;

			*pnCount = lCount;
			m_nTodayCache    = nToday;
			m_lExpryCache    = nExpiry;
			m_lQuantityCache = lCount;
			m_bDivCacheInit  = false;

		}
	}
	catch(const _com_error& e)
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsDivColl, e.Error());
	}
	catch(...)
	{
		hr =  Error((PTCHAR)(_T("Unhandled exception at GetDividendCount")), IID_IEtsDivColl, E_FAIL);
	}
	return hr;

}

STDMETHODIMP CEtsDivColl::Add(DATE Date, DOUBLE Amount)
{
	try
	{
		long lDate = static_cast<long>(Date);

		if(m_DivColl.find(lDate) != m_DivColl.end())
		{
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Div with the same date is already exists."));
		}

		ClearCache();
		m_DivColl.insert(std::pair<LONG, DOUBLE>(lDate, Amount));
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsDivColl, e.Error());
	}

	return S_OK;
}


STDMETHODIMP CEtsDivColl::AddNonUnique(DATE Date, DOUBLE Amount)
{
	try
	{
		long lDate = static_cast<long>(Date);
		EnumIterType iter = m_DivColl.find(lDate);

		if(iter != m_DivColl.end())
		{
			iter->second += Amount;
		}
		else
			m_DivColl.insert(std::pair<LONG, DOUBLE>(lDate, Amount));

		ClearCache();
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsDivColl, e.Error());
	}

	return S_OK;
}


STDMETHODIMP CEtsDivColl::Remove(DATE Date)
{
	HRESULT hr = S_OK;
	try
	{
		long lDate = static_cast<long>(Date);
		if(m_DivColl.find(lDate) == m_DivColl.end())
			hr = E_FAIL;
		else
		{
			m_DivColl.erase(lDate);
		}
		ClearCache();
	}
	catch(const _com_error& e)
	{
		hr = Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsDivColl, e.Error());
	}
	return hr;
}

STDMETHODIMP CEtsDivColl::Clear(void)
{
	m_DivColl.clear();
	ClearCache();
	return S_OK;
}

STDMETHODIMP CEtsDivColl::CopyToWithWeight( DOUBLE dWeight, IEtsDivColl* pDest , IEtsDivColl** ppVal)
{
	__CHECK_POINTER(ppVal);
	HRESULT hr = S_OK;
	try
	{
		if (pDest == NULL)
		{
			CComObject<CEtsDivColl>* pCustDivs; 
			_CHK(CComObject<CEtsDivColl>::CreateInstance(&pCustDivs),  _T("Fail to create dividend object."));
			pCustDivs->AddRef();
			pDest = pCustDivs;
		}
		EnumIterType iter = m_DivColl.begin();
		EnumIterType iterEnd = m_DivColl.end();
		DOUBLE dDate = 0;
		DOUBLE dAmount = 0;
		for(;iter != iterEnd; ++iter)
		{
			dDate = iter->first;
			dAmount = iter->second;
			pDest->Add(dDate ,  (dAmount * dWeight) );
		}
		if(ppVal)
		{
			*ppVal = pDest;
			pDest->AddRef();
		}

	}
	catch (_com_error& e) 
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsDivColl, e.Error());
	}
	catch(...)
	{
		hr =  Error( _T("Unhandled exception handled at CopyToWithWeight"), IID_IEtsDivColl, E_FAIL);
	}
	return hr;
}


STDMETHODIMP CEtsDivColl::Clone(IEtsDivColl** ppVal)
{
	HRESULT hr = S_OK;
	__CHECK_POINTER(ppVal);

	try
	{
		ClearCache();
		IEtsDivCollPtr spColl;
		CComObject<CEtsDivColl>* pColl = NULL;
		_CHK(CComObject<CEtsDivColl>::CreateInstance(&pColl));
		spColl.Attach(pColl, TRUE);
		if(!m_DivColl.empty())
		{
			EnumIterType itr = m_DivColl.begin();
			while(itr!=m_DivColl.end())
			{
				pColl->m_DivColl.insert(*itr);
				++itr;
			}

		}   
		*ppVal = spColl.Detach();
	}
	catch (_com_error& e) 
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsDivColl, e.Error());
	}
	return hr;
}
