// MmRvExpAtom.cpp : Implementation of CMmRvExpAtom

#include "stdafx.h"
#include "MmRvExpAtom.h"
#include "MmRvPosAtom.h"


// CMmRvExpAtom
void CMmRvExpAtom::CalcTotals()
{
	try
	{
		__MmRvExpAtom::ClearValues();
		ClearSyntheticsValues();
		CMmRvPosColl::EnumCollType::iterator itr    = m_pPos->m_coll.begin();
		CMmRvPosColl::EnumCollType::iterator itrEnd = m_pPos->m_coll.end();
		for(; itr!=itrEnd; ++ itr)
		{
			CMmRvPosAtom* pPos = dynamic_cast<CMmRvPosAtom*>(itr->second);
			if(pPos)
			{
				if(pPos->m_bIsSynthetic && pPos->m_spSynthGreeks!=NULL)
					m_bHasSynth = VARIANT_TRUE;
				//////////////////////////////////////////////////////////////////////////
				if(pPos->m_enContractType == enCtOption || pPos->m_enContractType == enCtFutOption)
				{
					if(pPos->m_dInternalEqDelta > BAD_DOUBLE_VALUE)
					{
						if(m_dDeltaEq == BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
						m_dDeltaEq += pPos->m_dInternalEqDelta;
					}
					else m_bBadDeltaEq = VARIANT_TRUE;
					//////////////////////////////////////////////////////////////////////////
					if(pPos->m_dDeltaInShares > BAD_DOUBLE_VALUE)
					{
						if(m_dDeltaInShares == BAD_DOUBLE_VALUE) m_dDeltaInShares = 0.;
						m_dDeltaInShares += pPos->m_dDeltaInShares;
					}
					else m_bBadDeltaInShares = VARIANT_TRUE;
				}
				//////////////////////////////////////////////////////////////////////////
				if(pPos->m_dNetGamma > BAD_DOUBLE_VALUE)
				{
					if(m_dGammaEq == BAD_DOUBLE_VALUE) m_dGammaEq = 0.;
					m_dGammaEq += pPos->m_dNetGamma;
				} 
				else m_bBadGammaEq = VARIANT_TRUE;
				//////////////////////////////////////////////////////////////////////////
				if(pPos->m_dRhoInShares > BAD_DOUBLE_VALUE)
				{
					if(m_dRhoInShares == BAD_DOUBLE_VALUE) m_dRhoInShares = 0.;
					m_dRhoInShares += pPos->m_dRhoInShares;
				}
				else m_bBadRhoInShares = VARIANT_TRUE;
				//////////////////////////////////////////////////////////////////////////
				if(pPos->m_dGammaInShares > BAD_DOUBLE_VALUE)
				{
					if(m_dGammaInShares == BAD_DOUBLE_VALUE) m_dGammaInShares = 0;
					m_dGammaInShares += pPos->m_dGammaInShares;
				}
				else m_bBadGammaInShares = VARIANT_TRUE;
				//////////////////////////////////////////////////////////////////////////
				if(pPos->m_dVegaInShares > BAD_DOUBLE_VALUE)
				{
					if(m_dVegaInShares == BAD_DOUBLE_VALUE) m_dVegaInShares = 0.0;
					m_dVegaInShares += pPos->m_dVegaInShares;
				}
				else m_bBadVegaInShares = VARIANT_TRUE;
				if(pPos->m_dTimeValue > BAD_DOUBLE_VALUE)
				{
					if(m_dTimeValueInShares == BAD_DOUBLE_VALUE) m_dTimeValueInShares = 0;
					m_dTimeValueInShares +=  pPos->m_dTimeValue* pPos->m_nQtyInShares;
				}
				else
					if(pPos->m_enContractType == enCtOption) m_bBadTimeValueInShares = VARIANT_TRUE;
			}
			CalcSynthetictotals(pPos);
		}
	}
	catch (_com_error& /*e*/){	}
}

void CMmRvExpAtom::ClearSyntheticsValues()
{
	if(m_spSynthGreek!=NULL)
	{
		CMmRvSynthGreeksColl* pSynthGreekColl = dynamic_cast<CMmRvSynthGreeksColl*>(m_spSynthGreek.GetInterfacePtr());
		if(pSynthGreekColl!=NULL && !pSynthGreekColl->m_coll.empty())
		{
			CMmRvSynthGreeksColl::EnumCollType::iterator itr    = pSynthGreekColl->m_coll.begin();
			CMmRvSynthGreeksColl::EnumCollType::iterator itrend = pSynthGreekColl->m_coll.end();
			for(;itr!=itrend;++itr)
				itr->second->ClearValuesInShares();
		}
	}

}

void CMmRvExpAtom::CalcSynthetictotals(CMmRvPosAtom* pPos)
{
	if(m_spSynthGreek!=NULL && pPos->m_bIsSynthetic && pPos->m_spSynthGreeks)
	{
		CMmRvSynthGreeksColl* pExpSynthColl = dynamic_cast<CMmRvSynthGreeksColl*>(m_spSynthGreek.GetInterfacePtr());
		CMmRvSynthGreeksColl* pPosSynthColl = dynamic_cast<CMmRvSynthGreeksColl*>(pPos->m_spSynthGreeks.GetInterfacePtr());
		if(pExpSynthColl && pPosSynthColl && !pPosSynthColl->m_coll.empty())
		{
			CMmRvSynthGreeksColl::EnumCollType::iterator itrPos    = pPosSynthColl->m_coll.begin();
			CMmRvSynthGreeksColl::EnumCollType::iterator itrPosEnd = pPosSynthColl->m_coll.end();
			for (;itrPos!=itrPosEnd;++itrPos)
			{
				CMmRvSynthGreeksAtom* sPosSynthAtom = dynamic_cast<CMmRvSynthGreeksAtom*>(itrPos->second);
				if(sPosSynthAtom)
				{
					IMmRvSynthGreeksAtomPtr spExpSynthAtom;
					pExpSynthColl->get_Item(sPosSynthAtom->m_nSynthUndID, &spExpSynthAtom);
					CMmRvSynthGreeksAtom* pExpSynthAtom = dynamic_cast<CMmRvSynthGreeksAtom*>(spExpSynthAtom.GetInterfacePtr());
					if(pExpSynthAtom)
					{
						if(sPosSynthAtom->m_dDeltaInShares > BAD_DOUBLE_VALUE)
						{
							if(pExpSynthAtom->m_dDeltaInShares <= BAD_DOUBLE_VALUE) pExpSynthAtom->m_dDeltaInShares = 0.;
							pExpSynthAtom->m_dDeltaInShares += sPosSynthAtom->m_dDeltaInShares;
						}

						if(VARIANT_FALSE == pExpSynthAtom->m_bBadDelta)
							pExpSynthAtom->m_bBadDelta = sPosSynthAtom->m_bBadDelta;

						// DeltaEq total
						if(sPosSynthAtom->m_dDeltaInMoney > BAD_DOUBLE_VALUE)
						{
							if(pExpSynthAtom->m_dDeltaInMoney <= BAD_DOUBLE_VALUE) pExpSynthAtom->m_dDeltaInMoney = 0.;
							pExpSynthAtom->m_dDeltaInMoney += sPosSynthAtom->m_dDeltaInMoney;
						}

						if(VARIANT_FALSE == pExpSynthAtom->m_bBadDeltaInMoney)
							pExpSynthAtom->m_bBadDeltaInMoney = sPosSynthAtom->m_bBadDeltaInMoney;

						// GammaInShares total
						if(sPosSynthAtom->m_dGammaInShares > BAD_DOUBLE_VALUE)
						{
							if(pExpSynthAtom->m_dGammaInShares <= BAD_DOUBLE_VALUE) pExpSynthAtom->m_dGammaInShares = 0.;
							pExpSynthAtom->m_dGammaInShares += sPosSynthAtom->m_dGammaInShares;
						}

						if(VARIANT_FALSE == pExpSynthAtom->m_bBadGamma)
							pExpSynthAtom->m_bBadGamma = sPosSynthAtom->m_bBadGamma;

						// GammaEq total
						if(sPosSynthAtom->m_dNetGamma > BAD_DOUBLE_VALUE)
						{
							if(pExpSynthAtom->m_dNetGamma <= BAD_DOUBLE_VALUE) pExpSynthAtom->m_dNetGamma = 0.;
							pExpSynthAtom->m_dNetGamma += sPosSynthAtom->m_dNetGamma;
						}
						// RhoEq total
						if(sPosSynthAtom->m_dRhoInShares > BAD_DOUBLE_VALUE)
						{
							if(pExpSynthAtom->m_dRhoInShares <= BAD_DOUBLE_VALUE) pExpSynthAtom->m_dRhoInShares = 0.;
							pExpSynthAtom->m_dRhoInShares += sPosSynthAtom->m_dRhoInShares;
						}

						if(VARIANT_FALSE == pExpSynthAtom->m_bBadGamma)
							pExpSynthAtom->m_bBadGamma = sPosSynthAtom->m_bBadGamma;


					}
				}
			}
		}
	}
}