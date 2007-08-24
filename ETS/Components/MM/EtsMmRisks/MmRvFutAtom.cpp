// MmRvFutAtom.cpp : Implementation of CMmRvFutAtom

#include "stdafx.h"
#include "MmRvFutAtom.h"


// CMmRvFutAtom

STDMETHODIMP CMmRvFutAtom::get_Underlying(IMmRvUndAtom **pVal)
{
	if(!pVal)	return E_POINTER;	

	if(*pVal) {
		(*pVal)->Release();
		*pVal = NULL;
	}

	ObjectLock lock(this);

	*pVal = m_spUnd;

	if(*pVal)	(*pVal)->AddRef();

	return S_OK;		
}


STDMETHODIMP CMmRvFutAtom::putref_Underlying(IMmRvUndAtom* NewVal)
{	
	ObjectLock lock(this);
	m_spUnd = NewVal;
	return S_OK;
}	

/*
This function returns future "mid" price, according to active future or price profile.
Sets bFutureUsed to VARIANT_TRUE if active future was used.
*/
STDMETHODIMP CMmRvFutAtom::GetFuturePrice( DOUBLE dTolerance, EtsPriceRoundingRuleEnum enPriceRound, EtsReplacePriceStatusEnum * penPriceStatus , VARIANT_BOOL *bFutureUsed, DOUBLE *pPrice){
	IEtsPriceProfileAtomPtr	spActiveFuturePriceProfile;
	HRESULT hr = S_OK;
	if (!pPrice || !bFutureUsed)	return E_POINTER;

	*pPrice = BAD_DOUBLE_VALUE;
	*bFutureUsed = VARIANT_FALSE;
	IMmRvFutAtomPtr	spActiveFuture;

	if (m_spUnd )
		_CHK(m_spUnd->get_ActiveFuture(&spActiveFuture));

	try
	{
		bool	useThis = true;

		if ( spActiveFuture )	{
			double priceBid, priceAsk, priceLast;
			double	activeFutureClosePrice = 0., activeFutureCurrentPrice = 0.;

			IMmRvPricePtr spPrice;
			_CHK(spActiveFuture->get_Price(&spPrice));

			_CHK(spActiveFuture->get_UndPriceProfile(&spActiveFuturePriceProfile));
			_CHK(spPrice->get_Ask(&priceAsk));
			_CHK(spPrice->get_Bid(&priceBid));
			_CHK(spPrice->get_Last(&priceLast));
			activeFutureCurrentPrice = spActiveFuturePriceProfile->GetUndPriceMid(priceBid, priceAsk, priceLast, 
				dTolerance,  enPriceRound, NULL, VARIANT_FALSE );


			if (activeFutureCurrentPrice > 0)
			{

				// we have price of active future
				if ( m_dRatio <= 0.){
					_CHK(spPrice->get_Close(&activeFutureClosePrice));
					// we have no ratio, try to compute it on the fly
					if ( m_pPrice && m_pPrice->m_dPriceClose > 0. && activeFutureClosePrice > 0)
					{
						m_dRatio = m_pPrice->m_dPriceClose / activeFutureClosePrice;
						*pPrice = activeFutureCurrentPrice * m_dRatio;
					}
					else
						*pPrice = activeFutureCurrentPrice;	// couldn't compute ratio
				}
				else
					*pPrice = activeFutureCurrentPrice * m_dRatio;
				useThis = false;
				*bFutureUsed = VARIANT_TRUE;
			}
		}
		// if we were unable to compute future price based on price of active future
		// do it using this future quote 
		if( useThis && m_spUndPriceProfile) 
		{
			*pPrice = m_spUndPriceProfile->GetUndPriceMid(m_pPrice->m_dPriceBid, m_pPrice->m_dPriceAsk, 
				m_pPrice->m_dPriceLast, dTolerance,
				enPriceRound, penPriceStatus, VARIANT_FALSE );
		}
	}
	catch (_com_error& e) {
		hr = Error((PTCHAR)CComErrorWrapper::ErrorDescription(e), __uuidof(IMmRvFutAtom), e.Error());
	}
	if (!m_pPrice->m_bManualActive) m_pPrice->m_dActivePrice = *pPrice;
	return hr;
}

//// MmRvFutAtom.cpp : Implementation of CMmRvFutAtom
//
//#include "stdafx.h"
//#include "MmRvFutAtom.h"
//
//
//// CMmRvFutAtom
//
