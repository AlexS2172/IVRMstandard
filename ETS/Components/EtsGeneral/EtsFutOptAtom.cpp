// EtsFutOptAtom.cpp : Implementation of CEtsFutOptAtom
#include "stdafx.h"
#include "EtsFutOptAtom.h"

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CEtsFutOptAtom::CopyTo(IEtsFutOptAtom* pDest)
{
	try
	{
		if(!pDest)
			EgLib::CComErrorWrapper::ThrowError(E_INVALIDARG, _T("Invalid argument"));

		HRESULT hr = S_OK;
		IEtsFutOptAtomPtr spDest(pDest);

		_CHK(spDest->put_ID(m_nID));
		_CHK(spDest->put_Symbol(m_bstrSymbol));
		_CHK(spDest->put_FutID(m_nFutID));
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
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsFutOptAtom, e.Error());
	}

	return S_OK;
}
