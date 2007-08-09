// MmRvExpTotalAtom.cpp : Implementation of CMmRvExpTotalAtom

#include "stdafx.h"
#include "MmRvExpTotalAtom.h"
#include "MmRvSynthGreeksColl.h"
#include "MmRvSynthGreeksAtom.h"


// CMmRvExpTotalAtom

STDMETHODIMP CMmRvExpTotalAtom::CalcTotals()
{
	try
	{
		HRESULT hr = S_OK;

		__MmRvExpTotalAtom::ClearValues();


		CMmRvExpColl::CollType::iterator itrExp    = m_pExpiry->m_coll.begin();
		CMmRvExpColl::CollType::iterator itrExpEnd = m_pExpiry->m_coll.end();
		for( ;itrExp!=itrExpEnd; ++itrExp)
		{
			CMmRvExpAtom* pExp = dynamic_cast<CMmRvExpAtom*>(itrExp->second);
			if( pExp != NULL)
			{
				// DeltaInShares total
				pExp->CalcTotals();
				if(pExp->m_dDeltaInShares > BAD_DOUBLE_VALUE)
				{
					if(m_dDeltaInShares <= BAD_DOUBLE_VALUE) m_dDeltaInShares = 0.;
					m_dDeltaInShares += pExp->m_dDeltaInShares;
				}

				if(VARIANT_FALSE == m_bBadDeltaInShares)
					m_bBadDeltaInShares = pExp->m_bBadDeltaInShares;

				if(VARIANT_FALSE == m_bBadRhoInShares)
					m_bBadRhoInShares = pExp->m_bBadRhoInShares;

				// DeltaEq total
				if(pExp->m_dDeltaEq > BAD_DOUBLE_VALUE)
				{
					if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
					m_dDeltaEq += pExp->m_dDeltaEq;
				}

				if(VARIANT_FALSE == m_bBadDeltaEq)
					m_bBadDeltaEq = pExp->m_bBadDeltaEq;

				// GammaInShares total
				if(pExp->m_dGammaInShares > BAD_DOUBLE_VALUE)
				{
					if(m_dGammaInShares <= BAD_DOUBLE_VALUE) m_dGammaInShares = 0.;
					m_dGammaInShares += pExp->m_dGammaInShares ;
				}

				if(VARIANT_FALSE == m_bBadGammaInShares)
					m_bBadGammaInShares = pExp->m_bBadGammaInShares;

				// GammaEq total
				if(pExp->m_dGammaEq > BAD_DOUBLE_VALUE)
				{
					if(m_dGammaEq <= BAD_DOUBLE_VALUE) m_dGammaEq = 0.;
					m_dGammaEq += pExp->m_dGammaEq;
				}

				// RhoEq total
				if(pExp->m_dRhoInShares > BAD_DOUBLE_VALUE)
				{
					if(m_dRhoInShares <= BAD_DOUBLE_VALUE) m_dRhoInShares = 0.;
					m_dRhoInShares += pExp->m_dRhoInShares;
				}

				if(VARIANT_FALSE == m_bBadGammaEq)
					m_bBadGammaEq = pExp->m_bBadGammaEq;

				// VegaInShares total
				if(pExp->m_dVegaInShares > BAD_DOUBLE_VALUE)
				{
					if(m_dVegaInShares <= BAD_DOUBLE_VALUE) m_dVegaInShares = 0.;
					m_dVegaInShares += pExp->m_dVegaInShares;
				}

				if(VARIANT_FALSE == m_bBadVegaInShares)
					m_bBadVegaInShares = pExp->m_bBadVegaInShares;

				// TimeValueInShares total
				if(pExp->m_dTimeValueInShares > BAD_DOUBLE_VALUE)
				{
					if(m_dTimeValueInShares <= BAD_DOUBLE_VALUE) m_dTimeValueInShares = 0.;
					m_dTimeValueInShares += pExp->m_dTimeValueInShares;
				}

				if(VARIANT_FALSE == m_bBadTimeValueInShares)
					m_bBadTimeValueInShares = pExp->m_bBadTimeValueInShares;

				if(pExp->m_pPos && !pExp->m_pPos->m_coll.empty())
				{
					CMmRvPosColl::EnumCollType::iterator itrPos    = pExp->m_pPos->m_coll.begin();
					CMmRvPosColl::EnumCollType::iterator itrPosEnd = pExp->m_pPos->m_coll.end();
					for(;itrPos!=itrPosEnd; ++itrPos)
					{
						CMmRvPosAtom* pPos = dynamic_cast<CMmRvPosAtom*>(itrPos->second);
						if(pPos && pPos->m_bIsSynthetic && pPos->m_spSynthGreeks!=NULL)
						{
							CMmRvSynthGreeksColl* pSynthColl = dynamic_cast<CMmRvSynthGreeksColl*>(pPos->m_spSynthGreeks.GetInterfacePtr());
							ATLASSERT(pSynthColl!=NULL);

							if(pSynthColl!=NULL)
							{
								CMmRvSynthGreeksColl::EnumCollType::iterator itrSynth    = pSynthColl->m_coll.begin();
								CMmRvSynthGreeksColl::EnumCollType::iterator itrSynthEnd = pSynthColl->m_coll.end();
								for(; itrSynth!=itrSynthEnd; ++itrSynth)
								{
									CMmRvSynthGreeksAtom* pSynthAtom = dynamic_cast<CMmRvSynthGreeksAtom*>(itrSynth->second);
									ATLASSERT(pSynthAtom);

									if(pSynthAtom)
									{
										if(pSynthAtom->m_dDeltaInShares > BAD_DOUBLE_VALUE)
										{
											if(m_dDeltaInShares <= BAD_DOUBLE_VALUE) m_dDeltaInShares = 0.;
											m_dDeltaInShares += pSynthAtom->m_dDeltaInShares;
										}

										if(VARIANT_FALSE == m_bBadDeltaInShares)
											m_bBadDeltaInShares = pSynthAtom->m_bBadDelta;

										// DeltaEq total
										if(pSynthAtom->m_dDeltaInMoney > BAD_DOUBLE_VALUE)
										{
											if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
											m_dDeltaEq += pSynthAtom->m_dDeltaInMoney;
										}

										if(VARIANT_FALSE == m_bBadDeltaEq)
											m_bBadDeltaEq = pSynthAtom->m_bBadDeltaInMoney;

										// GammaInShares total
										if(pSynthAtom->m_dGammaInShares > BAD_DOUBLE_VALUE)
										{
											if(m_dGammaInShares <= BAD_DOUBLE_VALUE) m_dGammaInShares = 0.;
											m_dGammaInShares += pSynthAtom->m_dGammaInShares;
										}

										if(VARIANT_FALSE == m_bBadGammaInShares)
											m_bBadGammaInShares = pSynthAtom->m_bBadGamma;

										// GammaEq total
										if(pSynthAtom->m_dNetGamma > BAD_DOUBLE_VALUE)
										{
											if(m_dGammaEq <= BAD_DOUBLE_VALUE) m_dGammaEq = 0.;
											m_dGammaEq += pSynthAtom->m_dNetGamma;
										}
										// RhoEq total
// 										if(pSynthAtom->m_dRhoInShares > BAD_DOUBLE_VALUE)
// 										{
// 											if(m_dRhoInShares <= BAD_DOUBLE_VALUE) m_dRhoInShares = 0.;
// 											m_dRhoInShares += pSynthAtom->m_dRhoInShares;
// 										}

										if(VARIANT_FALSE == m_bBadGammaEq)
											m_bBadGammaEq = pSynthAtom->m_bBadGamma;
									}
								}
							}
						}
					}
				}
			}
		}
		__CHECK_HRESULT(hr, _T("Fail to get next expiry."));
	}
	catch(const _com_error& e)
	{
		return Error((PTCHAR)CComErrorWrapper::ErrorDescription(e), IID_IMmRvExpTotalAtom, e.Error());
	}

	return S_OK;
}
