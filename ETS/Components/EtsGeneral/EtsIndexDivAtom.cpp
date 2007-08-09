// EtsIndexDivAtom.cpp : Implementation of CEtsIndexDivAtom

#include "stdafx.h"
#include "EtsIndexDivAtom.h"

#include "OptionCalc\OptionCalc.h"
#include "OptionPriceModels\common.h"

// CEtsIndexDivAtom

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CEtsIndexDivAtom::IsValidDivs(EtsDivTypeEnum enDivType, VARIANT_BOOL* pVal)
{
	__CHECK_POINTER(pVal);
	ObjectLock lock(this);

	if(enDivType == enDivCustomPeriodical)
	{
		*pVal = (m_nDivFreqCust == 1L || m_nDivFreqCust == 2L || m_nDivFreqCust == 4L || m_nDivFreqCust == 12L)
			&& m_dDivAmtCust > 0. && m_dtDivDateCust > 0.;
	}

	if(enDivType == enDivMarket)
	{
		*pVal = (m_nDivFreq == 1L || m_nDivFreq == 2L || m_nDivFreq == 4L || m_nDivFreq == 12L)
			&& m_dDivAmt > 0. && m_dtDivDate > 0.;
	}

	if(enDivType == enDivCustomStream)
	{
		*pVal = TRUE;
	}
	return S_OK;
}


/*
STDMETHODIMP CEtsIndexDivAtom::CopyToWithWeight( DOUBLE dWeight, IEtsIndexDivAtom* pDest , IEtsIndexDivAtom** ppVal)
{
	HRESULT hr = S_OK;
	__CHECK_POINTER(ppVal);

	try
	{
		if (pDest == NULL)
		{
			CComObject<CEtsIndexDivAtom>* pEtsIndexDivAtom; 
			_CHK(CComObject<CEtsIndexDivAtom>::CreateInstance(&pEtsIndexDivAtom),  _T("Fail to create dividend object."));
			pEtsIndexDivAtom->AddRef();
			pDest = pEtsIndexDivAtom;

		}
		__CHECK_HRESULT3(pDest->put_DivAmt(m_dDivAmt * dWeight));
		__CHECK_HRESULT3(pDest->put_DivDate(m_dtDivDate));
		__CHECK_HRESULT3(pDest->put_DivFreq(m_nDivFreq));
		__CHECK_HRESULT3(pDest->put_DivAmtCust(m_dDivAmtCust * dWeight));
		__CHECK_HRESULT3(pDest->put_DivDateCust(m_dtDivDateCust));
		__CHECK_HRESULT3(pDest->put_DivFreqCust(m_nDivFreqCust));
		__CHECK_HRESULT3(pDest->put_DivType(m_enDivType));
		
		if (m_spCustomDivs == NULL)
		{
			__CHECK_HRESULT3(pDest->putref_CustomDivs(NULL));
		}
		else
		{
			IEtsDivCollPtr spNewCustomDivs;
			IEtsDivCollPtr spCustomDivs;
			__CHECK_HRESULT3(pDest->get_CustomDivs(&spCustomDivs));

			__CHECK_HRESULT3(m_spCustomDivs->CopyToWithWeight(dWeight, spCustomDivs, &spNewCustomDivs));
			__CHECK_HRESULT3(pDest->putref_CustomDivs(spNewCustomDivs));
		
		}
		*ppVal = pDest;
	}
	catch (_com_error& e) 
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsIndexDivAtom, e.Error());
	}
	catch(...)
	{
		hr =  Error( _T("Unhandled exception handled at CopyToWithWeight"), IID_IEtsIndexDivAtom, E_FAIL);
	}
	return hr;

}
*/
STDMETHODIMP CEtsIndexDivAtom::GetDividends( LONG nToday,  LONG nExpiry,  LONG nCount, SAFEARRAY ** psaDivAmounts,  SAFEARRAY ** psaDivDates,  LONG* pnCount)
{

	__CHECK_POINTER(psaDivAmounts);
	__CHECK_POINTER(psaDivDates);
	__CHECK_POINTER(pnCount);
	HRESULT hr = S_OK;

	try
	{
		if (m_enDivType == enDivCustomStream)
		{
			if (m_spCustomDivs != NULL)
			{

				m_spCustomDivs->GetDividends( nToday,  nExpiry, nCount,psaDivAmounts, psaDivDates, pnCount);

			}
		}
		else
		{
	
			DOUBLE * pdDivDates = static_cast<DOUBLE*>(_alloca(nCount * sizeof(DOUBLE)));
			__CHECK_POINTER(pdDivDates);
			DOUBLE * pdDivAmounts = static_cast<DOUBLE*>(_alloca(nCount * sizeof(DOUBLE)));
			__CHECK_POINTER(pdDivAmounts);

			if (m_enDivType == enDivCustomPeriodical)
			{
				::GetDividends2(nToday, nExpiry - nToday, static_cast<LONG>(m_dtDivDateCust), m_nDivFreqCust, m_dDivAmtCust, nCount, pdDivAmounts,   pdDivDates, pnCount);
			}

			if (m_enDivType == enDivMarket)
			{
				::GetDividends2(nToday, nExpiry - nToday, static_cast<LONG>(m_dtDivDate), m_nDivFreq, m_dDivAmt, nCount, pdDivAmounts,   pdDivDates, pnCount);

			}

			if (*pnCount > 0)
			{
				LPSAFEARRAY pDates = SafeArrayCreateVector(VT_R8, 0, *pnCount);
				LPSAFEARRAY pAmounts = SafeArrayCreateVector(VT_R8, 0, *pnCount);

				::SafeArrayLock(pDates);
				::SafeArrayLock(pAmounts);
				LPVOID lpDateData = NULL;
				LPVOID lpAmountData = NULL;
				::SafeArrayAccessData(pDates, &lpDateData);
				::SafeArrayAccessData(pAmounts, &lpAmountData);

				DOUBLE * pdDates =	 reinterpret_cast<DOUBLE *>(lpDateData);
				DOUBLE * pdAmounts = reinterpret_cast<DOUBLE *>(lpAmountData);

					for(long i = 0; i< *pnCount; i++)
					{
						pdDates[i] = pdDivDates[i];
						pdAmounts[i] = pdDivAmounts[i];
					}

				::SafeArrayUnaccessData(pDates);
				::SafeArrayUnaccessData(pAmounts);

				::SafeArrayUnlock(pDates);
				::SafeArrayUnlock(pAmounts);

				*psaDivAmounts = pAmounts;
				*psaDivDates = pDates;
				}
			}
	}
	catch (_com_error& e) 
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsIndexDivAtom, e.Error());
	}
	catch(...)
	{
		hr =  Error( _T("Unhanded exception handled at GetDividends"), IID_IEtsIndexDivAtom, E_FAIL);
	}
	return hr;


}

STDMETHODIMP CEtsIndexDivAtom::GetNearest( LONG nToday,  LONG nExpiry,  DOUBLE* pdDivAmount,  DOUBLE* pdDivDate)
{
	HRESULT hr = S_OK;

	try
	{
		if (m_enDivType == enDivCustomStream)
		{
			m_spCustomDivs->GetNearest(nToday, nExpiry, pdDivAmount, pdDivDate);
		}
		else
			hr = E_NOTIMPL;


	}
	catch (_com_error& e) 
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsIndexDivAtom, e.Error());
	}
	catch(...)
	{
		hr =  Error( _T("Unhandled exception handled at GetDividendCount"), IID_IEtsIndexDivAtom, E_FAIL);
	}
	return hr;

}

STDMETHODIMP CEtsIndexDivAtom::GetDividendCount( LONG nToday,  LONG nExpiry,  LONG* pnCount)
{
	__CHECK_POINTER(pnCount);
	HRESULT hr = S_OK;

	try
	{
		if(m_CacheToday == nToday && m_CacheExpiry ==  nExpiry)
			*pnCount = m_lCacheDivCount;
		else
		{
			switch(m_enDivType)
			{
			case enDivCustomStream:
				if (m_spCustomDivs != NULL)
					m_spCustomDivs->GetDividendCount(  nToday,  nExpiry,  pnCount);
				break;
			case enDivCustomPeriodical:
				*pnCount = ::GetDividendsCount(nToday, nExpiry - nToday, static_cast<LONG>(m_dtDivDateCust), m_nDivFreqCust );
				break;
			case enDivMarket:
				*pnCount = ::GetDividendsCount(nToday, nExpiry - nToday, static_cast<LONG>(m_dtDivDate), m_nDivFreq );
			}
			m_CacheToday     = nToday;
			m_CacheExpiry    = nExpiry;
			m_lCacheDivCount = *pnCount;
		}
	}
	catch (_com_error& e) 
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsIndexDivAtom, e.Error());
	}
	catch(...)
	{
		hr =  Error( _T("Unhanded exception handled at GetDividendCount"), IID_IEtsIndexDivAtom, E_FAIL);
	}
	if(*pnCount < 0)
		*pnCount = 0;
	return hr;

}

STDMETHODIMP CEtsIndexDivAtom::Clear(void)
{
	m_nDivFreq = 0;
	m_dtDivDate = 0;
	m_dDivAmt = 0;
	m_nDivFreqCust = 0;
	m_dtDivDateCust = 0;
	m_dDivAmtCust = 0;
	m_enDivType = enDivMarket;
	m_spCustomDivs->Clear();
	return S_OK;
}
STDMETHODIMP CEtsIndexDivAtom::ResetInternalCache(void)
{
  m_CacheToday     = 0;
  m_CacheExpiry    = 0;
  m_lCacheDivCount = 0;
  return S_OK;
}

STDMETHODIMP CEtsIndexDivAtom::Clone(IEtsIndexDivAtom** pDestination)
{
	__CHECK_POINTER(pDestination);
	HRESULT hr = S_OK;
	try
	{
		CComObject<CEtsIndexDivAtom>* pClone = NULL;
		_CHK(CComObject<CEtsIndexDivAtom>::CreateInstance(&pClone));
		IEtsIndexDivAtomPtr spAtom;
		spAtom.Attach(pClone, true);

		pClone->m_dDivAmt       = m_dDivAmt;
		pClone->m_dDivAmtCust   = m_dDivAmtCust;
		pClone->m_dtDivDate	    = m_dtDivDate;
		pClone->m_dtDivDateCust = m_dtDivDateCust;
		pClone->m_nDivFreq		= m_nDivFreq;
		pClone->m_nDivFreqCust	= m_nDivFreqCust;
		pClone->m_enDivType		= m_enDivType;
		if(m_spCustomDivs!=NULL)
			m_spCustomDivs->Clone(&pClone->m_spCustomDivs);
		else
			pClone->m_spCustomDivs = NULL;


		*pDestination = spAtom.Detach();
	}
	catch (_com_error& e) 
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsIndexDivAtom, e.Error());
	}
	return hr;
}



