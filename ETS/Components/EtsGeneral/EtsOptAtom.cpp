// EtsOptAtom.cpp : Implementation of CEtsOptAtom
#include "stdafx.h"
#include "EtsOptAtom.h"

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CEtsOptAtom::CopyTo(IEtsOptAtom* pDest)
{
	try
	{
		if(!pDest)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		HRESULT hr = S_OK;
		IEtsOptAtomPtr spDest(pDest);

		_CHK(spDest->put_ID(m_nID));
		_CHK(spDest->put_Symbol(m_bstrSymbol));
		_CHK(spDest->put_RootID(m_nRootID));
		_CHK(spDest->put_OptType(m_enOptType));
		_CHK(spDest->put_Expiry(m_dtExpiry));
		_CHK(spDest->put_Strike(m_dStrike));
		_CHK(spDest->put_Series(m_bstrSeries));
		_CHK(spDest->put_PriceClose(m_dPriceClose));
		_CHK(spDest->put_PriceTheoClose(m_dPriceTheoClose));
		_CHK(spDest->put_ImportID(m_bstrImportID));
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsOptAtom, e.Error());
	}

	return S_OK;
}
