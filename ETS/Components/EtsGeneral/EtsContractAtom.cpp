// EtsContractAtom.cpp : Implementation of CEtsContractAtom

#include "stdafx.h"
#include "EtsContractAtom.h"

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CEtsContractAtom::get_ID(LONG* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spFut != NULL)
		{
			_CHK(m_spFut->get_ID(pRetVal));
		}
		else if(m_spUnd != NULL)
		{
			_CHK(m_spUnd->get_ID(pRetVal));
		}
		else
			*pRetVal = 0;
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsContractAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CEtsContractAtom::get_ContractType(enum EtsContractTypeEnum* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(m_spFut != NULL)
			*pRetVal = enCtFuture;
		else
			_CHK(m_spUnd->get_UndType(pRetVal));
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsContractAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CEtsContractAtom::get_Symbol(BSTR* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(*pRetVal)
			::SysFreeString(*pRetVal);

		if(m_spFut != NULL)
		{
			_CHK(m_spFut->get_Symbol(pRetVal));
		}
		else if(m_spUnd != NULL)
		{
			_CHK(m_spUnd->get_Symbol(pRetVal));
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsContractAtom, e.Error());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CEtsContractAtom::get_ContractName(BSTR* pRetVal)
{
	try
	{
		HRESULT hr = S_OK;

		if(!pRetVal)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		if(*pRetVal)
			::SysFreeString(*pRetVal);

		if(m_spFut != NULL)
		{
			_CHK(m_spFut->get_ContractName(pRetVal));
		}
		else if(m_spUnd != NULL)
		{
			_CHK(m_spUnd->get_ContractName(pRetVal));
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsContractAtom, e.Error());
	}

	return S_OK;
}

