// EtsPriceProfileColl.cpp : Implementation of CEtsPriceProfileColl

#include "stdafx.h"
#include "EtsPriceProfileColl1.h"

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CEtsPriceProfileColl::Add(LONG Key, BSTR SortKey, IEtsPriceProfileAtom* Value, IEtsPriceProfileAtom** pRetVal)
{
	try
	{
		if(m_collRef.find(Key) != m_collRef.end())
		{
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Price profile with the same key is already exists."));
		}

		if(!Value)
		{
			CComObject<CEtsPriceProfileAtom>* pNewVal;
			_CHK(CComObject<CEtsPriceProfileAtom>::CreateInstance(&pNewVal), _T("Fail to add price profile."));
			pNewVal->AddRef();
			if(FAILED(IEtsPriceProfileCollImpl::Add(Key, CComBSTR(SortKey), pNewVal)))
			{
				pNewVal->Release();
				EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Fail to add price profile."));
			}
			*pRetVal = pNewVal;
		}
		else
		{
			_CHK(IEtsPriceProfileCollImpl::Add(Key, CComBSTR(SortKey), Value), _T("Fail to add price profile."));
			Value->AddRef();
			*pRetVal = Value;
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsPriceProfileColl, e.Error());
	}

	return S_OK;
}

