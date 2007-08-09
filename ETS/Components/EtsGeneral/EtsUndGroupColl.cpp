// EtsUndGroupColl.cpp : Implementation of CEtsUndGroupColl

#include "stdafx.h"
#include "EtsUndGroupColl.h"

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CEtsUndGroupColl::Add(LONG Key, BSTR SortKey, IEtsUndGroupAtom* Value, IEtsUndGroupAtom** pRetVal)
{
	try
	{
		if(m_collRef.find(Key) != m_collRef.end())
		{
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Underlying group with the same key is already exists."));
		}

		if(!Value)
		{
			CComObject<CEtsUndGroupAtom>* pNewVal;

			_CHK(CComObject<CEtsUndGroupAtom>::CreateInstance(&pNewVal), _T("Fail to add underlying group."));
			pNewVal->AddRef();
			if(FAILED(IEtsUndGroupCollImpl::Add(Key, CComBSTR(SortKey), pNewVal)))
			{
				pNewVal->Release();
				EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Fail to add underlying group."));
			}
			*pRetVal = pNewVal;
		}
		else
		{
			_CHK(IEtsUndGroupCollImpl::Add(Key, CComBSTR(SortKey), Value), _T("Fail to add underlying group."));
			Value->AddRef();
			*pRetVal = Value;
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsUndGroupColl, e.Error());
	}

	return S_OK;
}

