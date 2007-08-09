// MmRvFutColl.cpp : Implementation of CMmRvFutColl
#include "stdafx.h"
#include "MmRvFutColl.h"

/////////////////////////////////////////////////////////////////////////////
//
IMmRvFutAtomPtr CMmRvFutColl::AddNew(long lFutId, _bstr_t bsFutSymbol, CComObject<CMmRvFutAtom>** ppObject )
{
	IMmRvFutAtomPtr spResult;
	CComObject<CMmRvFutAtom>* pNewVal = NULL;

	_CHK(CComObject<CMmRvFutAtom>::CreateInstance(&pNewVal), _T("Fail to add futures."));
	spResult.Attach(pNewVal,  TRUE);

	if(FAILED(IMmRvFutCollImpl::Add(lFutId, bsFutSymbol, pNewVal)))
		EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Fail to add futures."));

	pNewVal->m_nID = lFutId;
	pNewVal->m_bstrSymbol = bsFutSymbol;

	if(ppObject)
		*ppObject = pNewVal;
	return spResult;
}

STDMETHODIMP CMmRvFutColl::Add(LONG Key, BSTR SortKey, IMmRvFutAtom* Value, IMmRvFutAtom** pRetVal)
{
	try
	{
		if(m_collRef.find(Key) != m_collRef.end())
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Futures with the same key is already exists."));

		_bstr_t bsSortKey(SortKey);

		if(!Value)
			*pRetVal = AddNew(Key, bsSortKey).Detach();
		else
		{
			_CHK(IMmRvFutCollImpl::Add(Key, bsSortKey, Value), _T("Fail to add futures."));
			Value->AddRef();
			*pRetVal = Value;
		}
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvFutColl, e.Error());
	}

	return S_OK;
}


//// MmRvFutColl.cpp : Implementation of CMmRvFutColl
//#include "stdafx.h"
//#include "MmRvFutColl.h"
//
///////////////////////////////////////////////////////////////////////////////
////
//STDMETHODIMP CMmRvFutColl::Add(LONG Key, BSTR SortKey, IMmRvFutAtom* Value, IMmRvFutAtom** pRetVal)
//{
//	try
//	{
//		if(m_collRef.find(Key) != m_collRef.end())
//			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Futures with the same key is already exists."));
//
//		if(!Value)
//		{
//			CComObject<CMmRvFutAtom>* pNewVal;
//
//			_CHK(CComObject<CMmRvFutAtom>::CreateInstance(&pNewVal), _T("Fail to add futures."));
//			pNewVal->AddRef();
//			if(FAILED(IMmRvFutCollImpl::Add(Key, CComBSTR(SortKey), pNewVal)))
//			{
//				pNewVal->Release();
//				EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Fail to add futures."));
//			}
//			*pRetVal = pNewVal;
//		}
//		else
//		{
//			_CHK(IMmRvFutCollImpl::Add(Key, CComBSTR(SortKey), Value), _T("Fail to add futures."));
//			Value->AddRef();
//			*pRetVal = Value;
//		}
//	}
//	catch(const _com_error& e)
//	{
//		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmRvFutColl, e.Error());
//	}
//
//	return S_OK;
//}
//
