// VolaControl.cpp : Implementation of CVolaControl

#include "stdafx.h"
#include "VolaControl.h"


/////////////////////////////////////////////////////////////////////////////
//
DATE FirstMonthDayDate(DATE dtDate)
{
	SYSTEMTIME st = {0};
	::VariantTimeToSystemTime(dtDate, &st);
	st.wDay = 1;
	::SystemTimeToVariantTime(&st, &dtDate);
	return dtDate;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CVolaControl::Init(BSTR UnderlyingSymbol, EtsContractTypeEnum ContractType, IVolatilitySource* pVolaSrc)
{
	ObjectLock lock(this);
	SYMBOL_TYPE Type;

	if(NULL == UnderlyingSymbol || ::SysStringLen(UnderlyingSymbol) == 0L)
	{
		return Error(L"Invalid underlying symbol argument.", IID_IVolaControl, E_INVALIDARG);
	}

	if(NULL == pVolaSrc)
	{
		return Error(L"Invalid volatility source argument.", IID_IVolaControl, E_INVALIDARG);
	}

	try
	{
		switch(ContractType){
		case enCtStock: 
			Type = enStStock;
			break;
		case enCtIndex: 
			Type = enStIndex;
			break;
		case enCtFutUnd: 
			Type = enStFutUnd;
			break;
		default:
			Type = enStStock;
		}

		m_dUnderlyingPrice = 0.;
		m_spSymbolVola = NULL;
		m_spSymbolVola = pVolaSrc->GetSymbolVolatility(UnderlyingSymbol, Type);
	}
	catch(const _com_error& e)
	{
		return CComErrorWrapper::SetError(e, L"VolaControl", L"", __FILE__,__FUNCDNAME__,__LINE__);
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CVolaControl::CleanUp(void)
{
	ObjectLock lock(this);
	m_dUnderlyingPrice = 0.;
	m_spSymbolVola = NULL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CVolaControl::get_OptionVola(DATE Expiry, DOUBLE Strike, DOUBLE* pVal)
{
	__CHECK_POINTER(pVal);

	if(NULL == m_spSymbolVola)
	{
		return Error(L"Volatility control is not initialized.", IID_IVolaControl, E_FAIL);
	}

	ObjectLock lock(this);

	try
	{
		*pVal = m_spSymbolVola->GetVolatility(m_dUnderlyingPrice, Strike, /*FirstMonthDayDate(*/Expiry/*)*/);
		*pVal = (*pVal >= 0. ? *pVal / 100. : ETS_DEF_VOLA);
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IVolaControl, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CVolaControl::put_OptionVola(DATE Expiry, DOUBLE Strike, DOUBLE newVal)
{
	if(NULL == m_spSymbolVola)
	{
		return Error(L"Volatility control is not initialized.", IID_IVolaControl, E_FAIL);
	}

	ObjectLock lock(this);

	try
	{
		m_spSymbolVola->PutVolatility(m_dUnderlyingPrice, Strike, /*FirstMonthDayDate(*/Expiry/*)*/, newVal * 100.);
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IVolaControl, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CVolaControl::get_OptionTargetVola(DATE Expiry, DOUBLE Strike, DOUBLE* pVal)
{
	__CHECK_POINTER(pVal);

	if(NULL == m_spSymbolVola)
	{
		return Error(L"Volatility control is not initialized.", IID_IVolaControl, E_FAIL);
	}

	ObjectLock lock(this);

	try
	{
		IVSTargetVolatilityPtr spTargetVola(m_spSymbolVola);
		*pVal = spTargetVola->GetTargetVolatility(m_dUnderlyingPrice, Strike, /*FirstMonthDayDate(*/Expiry/*)*/);
		*pVal = (*pVal >= 0. ? *pVal / 100. : ETS_DEF_VOLA);
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IVolaControl, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CVolaControl::ShiftExpiryVola(DATE Expiry, DOUBLE ShiftValue)
{
	if(NULL == m_spSymbolVola)
	{
		return Error(L"Volatility control is not initialized.", IID_IVolaControl, E_FAIL);
	}

	ObjectLock lock(this);

	try
	{
		m_spSymbolVola->VolatilityShift(/*FirstMonthDayDate(*/Expiry/*)*/, ShiftValue);
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IVolaControl, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CVolaControl::SetExpiryVola(DATE Expiry, DOUBLE Value)
{
	if(NULL == m_spSymbolVola)
	{
		return Error(L"Volatility control is not initialized.", IID_IVolaControl, E_FAIL);
	}

	ObjectLock lock(this);

	try
	{
		m_spSymbolVola->VolatilitySet(/*FirstMonthDayDate(*/Expiry/*)*/, Value * 100.);
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IVolaControl, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CVolaControl::SetExpiryVolaByExpiry(LPSAFEARRAY* saData)
{
	if(NULL == m_spSymbolVola)
	{
		return Error(L"Volatility control is not initialized.", IID_IVolaControl, E_FAIL);
	}

	ObjectLock lock(this);

	try
	{
		m_spSymbolVola->VolatilitySetAllByExp(saData);
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IVolaControl, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CVolaControl::SetExpiryVolaAll(DOUBLE Value)
{
	if(NULL == m_spSymbolVola)
	{
		return Error(L"Volatility control is not initialized.", IID_IVolaControl, E_FAIL);
	}

	ObjectLock lock(this);

	try
	{
		m_spSymbolVola->VolatilitySetAll(Value * 100.);
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IVolaControl, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CVolaControl::SetExpiryAndStrikeVolaAll(LPSAFEARRAY* saData)
{
	if(NULL == m_spSymbolVola)
	{
		return Error(L"Volatility control is not initialized.", IID_IVolaControl, E_FAIL);
	}

	ObjectLock lock(this);

	try
	{
		m_spSymbolVola->VolatilitySetAllByExpAndStrike(saData);
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IVolaControl, e.Error());
	}

	return S_OK;
}

