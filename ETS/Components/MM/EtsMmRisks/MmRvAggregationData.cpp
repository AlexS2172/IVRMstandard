#include "stdafx.h"

#include "MmRvRowData.h"
//#include "MmRvUndAtom.h"
//#include "MmRvAggregationData.h"
#include "MmRiskView.h"
#include "MmRvPosColl.h"
#include "MmRvUndColl.h"

#include <algorithm>
#include <boost/bind.hpp>

using namespace boost;

void accumulate_if_not_bad( double& sumValue, const double addValue){
	if ( !IsBadValue(addValue)) {
		if (IsBadValue(sumValue)) 
			sumValue = 0.;
		sumValue += addValue;
	}
}

void accumulate_if_not_bad( double& sumValue, const double addValue, const double K){
	if ( !IsBadValue(addValue)) {
		if (IsBadValue(sumValue)) 
			sumValue = 0.;
		sumValue += K * addValue;
	}
}

void accumulate_if_not_bad( LONG& sumValue, const LONG addValue, const double K){
	double tmpAdd = static_cast<double>(addValue);
	if ( !IsBadValue(addValue)) {
		if (IsBadValue(sumValue)) 
			sumValue = 0;
		sumValue += static_cast<LONG>(K * tmpAdd );
	}
}

void CMmRvAggData::AddAggregatedValues(const CMmRvRowData* pRow)
{
	if (pRow->m_pUnd->m_spHeadComponent || pRow->m_pUnd->m_bIsHead)
	{
		double	dCoeff = 1.0;
		if (pRow->m_pUnd->m_spHeadComponent || pRow->m_pUnd->m_bIsHead == VARIANT_TRUE) 
			dCoeff = pRow->m_pUnd->m_dCoeff;

		accumulate_if_not_bad( UndPos_,			pRow->m_pAgg->UndPos_,	dCoeff );
		accumulate_if_not_bad( OptQty_,			pRow->m_pAgg->OptQty_,	1.0 );
		accumulate_if_not_bad( FutQty_,			pRow->m_pAgg->FutQty_,	1.0 );

		accumulate_if_not_bad( OptDlt_,			pRow->m_pAgg->OptDlt_,	dCoeff );
		accumulate_if_not_bad( OptDlt$_,		pRow->m_pAgg->OptDlt$_, dCoeff );
		accumulate_if_not_bad( Gma1P_,			pRow->m_pAgg->Gma1P_,	dCoeff * dCoeff );
		accumulate_if_not_bad( Gma1$_,			pRow->m_pAgg->Gma1$_,	dCoeff * dCoeff );
		accumulate_if_not_bad( Vga$_,			pRow->m_pAgg->Vga$_,	1.0 );
		accumulate_if_not_bad( Tht$_,			pRow->m_pAgg->Tht$_,	1.0 );
		accumulate_if_not_bad( WtdVga$_,		pRow->m_pAgg->WtdVga$_, 1.0 );
		accumulate_if_not_bad( Rho$_,			pRow->m_pAgg->Rho$_,	1.0 );
		accumulate_if_not_bad( ThtDlt_,			pRow->m_pAgg->ThtDlt_,	dCoeff );
		accumulate_if_not_bad( ThtGma_,			pRow->m_pAgg->ThtGma_,	dCoeff * dCoeff );
		accumulate_if_not_bad( VgaDlt_,			pRow->m_pAgg->VgaDlt_,	dCoeff );
		accumulate_if_not_bad( VgaGma_,			pRow->m_pAgg->VgaGma_,	dCoeff * dCoeff );
		accumulate_if_not_bad( NetDlt_,			pRow->m_pAgg->NetDlt_,	1.0 );
		accumulate_if_not_bad( NetDlt$_,		pRow->m_pAgg->NetDlt$_, 1.0 );
		accumulate_if_not_bad( BetaWtdDelta$_,	pRow->m_pAgg->BetaWtdDelta$_, 1.0 );
		accumulate_if_not_bad( NetGma$_,		pRow->m_pAgg->NetGma$_, dCoeff * dCoeff );

		accumulate_if_not_bad( PnlEdge_,		pRow->m_pAgg->PnlEdge_, 1.0 );
		accumulate_if_not_bad( PnlMTM_,			pRow->m_pAgg->PnlMTM_,	1.0 );
		accumulate_if_not_bad( PnLTheo_,		pRow->m_pAgg->PnLTheo_, 1.0 );


		//-------------------------------------------------------------------------------//
		if(pRow->m_pUnd->m_spSynthGreeks != NULL)
		{
			IMmRvSynthGreeksAtomPtr spUndSynthGreeks;
			LONG nSynthUndID = 0L;
			DOUBLE dSelfValue	= BAD_DOUBLE_VALUE;
			DOUBLE dUndValue	= BAD_DOUBLE_VALUE;

			IUnknownPtr spUnk;
			_variant_t varItem;
			ULONG nFetched = 0L;
			HRESULT hr;

			_CHK(pRow->m_pUnd->m_spSynthGreeks->get__NewEnum(&spUnk));
			IEnumVARIANTPtr spUndSynthGreekEnum(spUnk);
			_CHK(spUndSynthGreekEnum->Reset());
			while((hr = spUndSynthGreekEnum->Next(1L, &varItem, &nFetched)) == S_OK)
			{
				ATLASSERT(varItem.vt == VT_DISPATCH);
				spUndSynthGreeks = varItem;
				if(spUndSynthGreeks != NULL)
				{
					_CHK(spUndSynthGreeks->get_NetDelta(&dUndValue));
					accumulate_if_not_bad(NetDlt_, dUndValue, 1.0);

					_CHK(spUndSynthGreeks->get_DeltaInMoney(&dUndValue));
					accumulate_if_not_bad(NetDlt$_, dUndValue, 1.0);
					accumulate_if_not_bad(OptDlt$_, dUndValue, dCoeff);

					_CHK(spUndSynthGreeks->get_DeltaInShares(&dUndValue));
					accumulate_if_not_bad(OptDlt_, dUndValue, dCoeff);

					_CHK(spUndSynthGreeks->get_GammaInShares(&dUndValue));
					accumulate_if_not_bad(Gma1$_, dUndValue, dCoeff * dCoeff);

					_CHK(spUndSynthGreeks->get_GammaInSharesPerc(&dUndValue));
					accumulate_if_not_bad(Gma1P_, dUndValue, dCoeff * dCoeff);

					_CHK(spUndSynthGreeks->get_NetGamma(&dUndValue));
					accumulate_if_not_bad(NetGma$_, dUndValue, dCoeff * dCoeff);
				}
			}
		}
	}	
}
void CMmRvAggData::CalcNetDeltas(EtsContractTypeEnum underlyingContractType)
{

	for_each(	
					Aggregations_.begin(), 
					Aggregations_.end(), 
					bind(&CMmRvAggData::CalcNetDeltas, _1, underlyingContractType)
				);

	// calculate NetDeltas only for aggregations by underlying and future 
	if ( Type_ == enFutAgg) 
	{

		// for future aggregation use FutureQuantity or UnderlyingPosition
		// depending on Underlying Contract Type
		double Qty, optDlt;
		if (underlyingContractType ==	enCtFutUnd)
			Qty = IsBadValue(FutQty_) ? BAD_DOUBLE_VALUE : ( double )FutQty_;
		else
			Qty = IsBadValue(UndPos_) ? BAD_DOUBLE_VALUE : ( double )UndPos_;
		if (! (IsBadValue(Qty) && IsBadValue(OptDlt_) ) ) {
			if (IsBadValue(Qty))
				Qty = 0.;
			optDlt = IsBadValue(OptDlt_) ? 0. : OptDlt_;

			double dNetDlt_CSzMult = 1.0;
			if (underlyingContractType == enCtFutUnd && pFut_ && !pFut_->m_bMultOptDltEq 
				&& !IsBadValue(pFut_->m_nFutLotSize) && pFut_->m_nFutLotSize)
				dNetDlt_CSzMult = ( (double)pFut_->m_nFutLotSize );
			// for future aggregation NetDelta = Qty + ( Sum(OptionDelta) in aggregation )
			NetDlt_ = Qty * dNetDlt_CSzMult + optDlt;//optDlt has been already multiplied by 
														//Contract Size, if this is needed.

			// calculate NetDelta$
			NetDlt$_ = BAD_DOUBLE_VALUE;
			if (underlyingContractType ==	enCtFutUnd ) 
			{
				if (pFut_ && !IsBadValue(pFut_->m_pPrice->m_dActivePrice) && pFut_->m_pPrice->m_dActivePrice) 
					NetDlt$_ = (NetDlt_ / dNetDlt_CSzMult) * pFut_->m_pPrice->m_dActivePrice * pFut_->m_dKEq;
			}
			else 
				if (pUnd_ && !IsBadValue(pUnd_->m_pPrice->m_dActivePrice) && pUnd_->m_pPrice->m_dActivePrice) 
					NetDlt$_ = NetDlt_ * pUnd_->m_pPrice->m_dActivePrice;
		}
		else
			NetDlt_ = NetDlt$_ = BAD_DOUBLE_VALUE;
	}
	else if ( Type_ == enUndAgg)
	{
		double sumNetDeltas = BAD_DOUBLE_VALUE;

		// for underlying aggregation there are 2 cases:
		// 1. underlying aggregation for future underlying: NetDelta = Sum of NetDelta of aggregations residing this aggregation
		// 2. underlying aggregation for stock/index: NetDelta = OptionDelta of aggregation + Underlying position of this aggregation
		if (underlyingContractType == enCtFutUnd ) {
			for_each(	
				Aggregations_.begin(), 
				Aggregations_.end(), 
				bind( accumulate_if_not_bad, ref(NetDlt_), bind(&CMmRvAggData::NetDlt_, _1) )
				);
			for_each(	
				Aggregations_.begin(), 
				Aggregations_.end(), 
				bind( accumulate_if_not_bad, ref(NetDlt$_), bind(&CMmRvAggData::NetDlt$_, _1) )
				);
		}
		else{
			if ( !(IsBadValue(OptDlt_) && IsBadValue(UndPos_) ) ) {
				NetDlt_ = IsBadValue(OptDlt_) ? 0. : OptDlt_;
				if ( !IsBadValue(UndPos_) ) 
					NetDlt_ += ( static_cast<double>(UndPos_) );

				NetDlt$_ = BAD_DOUBLE_VALUE;
				if (pUnd_ && !IsBadValue(NetDlt_)) 
				{
					if (!IsBadValue(pUnd_->m_pPrice->m_dActivePrice) && pUnd_->m_pPrice->m_dActivePrice!=0.0) 
						NetDlt$_ = NetDlt_ * pUnd_->m_pPrice->m_dActivePrice;
				}
			}
		}
	}
	if(Type_ != enExpAgg)
	{
		DOUBLE dAUM = BAD_DOUBLE_VALUE;
		if(pUnd_)
			dAUM = pUnd_->GetNetExposureAUM();

		if( dAUM >BAD_DOUBLE_VALUE && dAUM != 0.0 && !IsBadValue(NetDlt$_))
		{

			if(NetExposure_ == BAD_DOUBLE_VALUE) NetExposure_ = 0.0;
			double dExposure = (NetDlt$_ / dAUM * 100);

			if(dExposure < 0.0)
			{
				if(NetExposureSort_ == BAD_DOUBLE_VALUE) NetExposureSort_ = 0;
				NetExposureSort_+= dExposure;
			}
			if(dExposure > 0.0)
			{
				if(NetExposureLong_ == BAD_DOUBLE_VALUE) NetExposureLong_ = 0;
				NetExposureLong_+= dExposure;
			}
			BadNetExposure_ = VARIANT_TRUE;
			NetExposure_ = (NetExposureSort_ == BAD_DOUBLE_VALUE?0:NetExposureSort_)+(NetExposureLong_ == BAD_DOUBLE_VALUE?0:NetExposureLong_);

		}
		else
			NetExposure_ = BAD_DOUBLE_VALUE;
	}
}

bool CMmRvAggData::IsAggregationRowVisible( const CMmRvAggData* pAgg) 
{
	if (pAgg->m_bIsHeadAggregation == VARIANT_TRUE)
		return true;

	if( find_if(pAgg->Positions_.begin(),pAgg->Positions_.end(), bind( &CMmRvPosAtom::IsVisible, _1) ) != pAgg->Positions_.end() )
		return true;
	CMmRvAggData::Aggregations::const_iterator itrCurAgg = pAgg->Aggregations_.begin();
	CMmRvAggData::Aggregations::const_iterator itrEndAgg = pAgg->Aggregations_.end();
	while(itrCurAgg != itrEndAgg ){
		if( IsAggregationRowVisible( itrCurAgg->get() ) )
			return true;
		++itrCurAgg;
	}
	return false;
}
bool CMmRvAggData::CreateRow(CMmRvUndAtom* pUndAtom, unsigned outlnLvl, std::vector<IMmRvRowDataPtr>& aggRows){

	Positions::iterator itrCurPos = Positions_.begin();
	Positions::iterator itrEndPos = Positions_.end();

	IMmRvRowDataPtr spAggRowData;
	CComObject<CMmRvRowData>* pRow = NULL;

	if( IsAggregationRowVisible(this) && SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pRow))) {
		spAggRowData.Attach(pRow, TRUE);
		pRow->m_pUnd = pUndAtom;
		pRow->m_spUnd.Attach(pUndAtom, TRUE);
		pRow->m_Type = Type_ == enUndAgg ? RDT_UNDAGG : RDT_AGG;
		pRow->m_nLevel = outlnLvl;
		pRow->m_pAgg = MmRvAggDataPtr(this, null_deleter());
		aggRows.push_back(spAggRowData);
	}
	else
		return false;
	return true;
}
size_t CMmRvAggData::CreateRowsForPositions(CMmRvUndAtom* pUndAtom, long lExpiryFilter, unsigned outlineLevel, 
														const CRiskViewFieldSort *sortCmp, std::vector<IMmRvRowDataPtr>& positionsRows, 
														long& optPos,long& undPos, CComObject<CMmRvUndColl>* pUndColl ){
	Positions::iterator itrCurPos = Positions_.begin();
	Positions::iterator itrEndPos = Positions_.end();

	// underlyings aggregations in synthetic 
	CMmRiskView::CRowsData synthUndRows;

		/*for (; pUndColl && itrCurPos != itrEndPos; ++itrCurPos) {
		MmRvPosAtomPtr pPos = *itrCurPos;
		if (!pPos) continue;
		if	( !lExpiryFilter ||
			(( enCtOption == pPos->m_enContractType ||  enCtFutOption == pPos->m_enContractType ) && static_cast<long>(pPos->m_dtExpiry) == lExpiryFilter ) ) {	*/

			if (pUndAtom->m_spSynthGreeks) 
			{
				IMmRvUndAtomPtr spUndAtom;
				CMmRvSynthGreeksColl* pSynthColl = dynamic_cast<CMmRvSynthGreeksColl*>(pUndAtom->m_spSynthGreeks.GetInterfacePtr());
				CMmRvSynthGreeksColl::EnumCollType::iterator itrSynth    =  pSynthColl->m_coll.begin();
				CMmRvSynthGreeksColl::EnumCollType::iterator itrSynthEnd =  pSynthColl->m_coll.end();
				for(; itrSynth != itrSynthEnd; ++itrSynth) {
					CMmRvSynthGreeksAtom* pSynthAtom = dynamic_cast<CMmRvSynthGreeksAtom*>(itrSynth->second);
					if(pSynthAtom)	{
						pUndColl->get_Item(pSynthAtom->m_nSynthUndID, &spUndAtom );
						if ( spUndAtom ) {
							CComObject<CMmRvRowData>* pSynthUndRow = NULL;
							if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pSynthUndRow))) 	{
								IMmRvRowDataPtr spSynthRowData;
								spSynthRowData.Attach(pSynthUndRow, TRUE);
								//pSynthUndRow->m_spPos.Attach(pPos.get(), TRUE);
								//pSynthUndRow->m_pPos = pPos.get();
								pSynthUndRow->m_Type = RDT_UNDAGG;
								pSynthUndRow->m_spUnd = spUndAtom; //pRowData->m_spUnd;
								pSynthUndRow->m_pUnd = static_cast<CMmRvUndAtom*>(spUndAtom.GetInterfacePtr());
								pSynthUndRow->m_pAgg = MmRvAggDataPtr(pSynthUndRow->m_pUnd, null_deleter());
								pSynthUndRow->m_spSynthGreeks.Attach(pSynthAtom, TRUE);
								pSynthUndRow->m_pSynthGreeks = pSynthAtom;
								pSynthUndRow->m_nLevel = outlineLevel + 1;
								synthUndRows.push_back( spSynthRowData );
							}
						}
					}
				}

			}
		//}
	//}
	sort(synthUndRows.begin(), synthUndRows.end(), *sortCmp );
	positionsRows.reserve(positionsRows.size() + synthUndRows.size() );
	copy(synthUndRows.begin(), synthUndRows.end(), back_inserter(positionsRows));

	itrCurPos = Positions_.begin();
	itrEndPos = Positions_.end();

	// positions
	for (;itrCurPos != itrEndPos; ++itrCurPos) {
		MmRvPosAtomPtr pPos = *itrCurPos;
		if (!pPos) continue;
		if	( !lExpiryFilter || ( ( enCtOption == pPos->m_enContractType ||  enCtFutOption == pPos->m_enContractType ) && static_cast<long>(pPos->m_dtExpiry) == lExpiryFilter ) ) {
			pPos->m_bVisible = VARIANT_TRUE;
			CComObject<CMmRvRowData>* pRow = NULL;
			if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pRow)))	{
				IMmRvRowDataPtr spRowData;
				spRowData.Attach(pRow, TRUE);
				pRow->m_spPos.Attach(pPos.get(), TRUE);
				pRow->m_pPos = pPos.get();
				pRow->m_Type = RDT_POS;
				pRow->m_spUnd.Attach(pUndAtom, TRUE);
				pRow->m_pUnd = pUndAtom;
				pRow->m_nLevel = outlineLevel + 1;

				if(pPos->m_enContractType == enCtOption || pPos->m_enContractType == enCtFutOption)
					++optPos;
				else
					++undPos;
				positionsRows.push_back( spRowData);
			}
		}
		else
			pPos->m_bVisible = VARIANT_FALSE;
	}


	return synthUndRows.size();
}

bool CMmRvAggData::CheckPositions(long lExpiryFilter)
{
	Positions::iterator itrCurPos = Positions_.begin();
	Positions::iterator itrEndPos = Positions_.end();
	if(!lExpiryFilter)
		return true;

	for (;itrCurPos != itrEndPos; ++itrCurPos) 
	{
		MmRvPosAtomPtr pPos = *itrCurPos;
		if (!pPos || pPos->IsVisible()) continue;
		switch(pPos->m_enContractType)
		{
		case enCtOption:
		case enCtFutOption:
			if(static_cast<long>(pPos->m_dtExpiry) == lExpiryFilter) 
				return true;
			break;
		default:
			break;
		}
	}
	return false;
}

void CMmRvAggData::CreateRows(CMmRvUndAtom* pUndAtom, long lExpiryFilter, unsigned outlineLevel, 
										const CRiskViewFieldSort *sortCmp, std::vector<IMmRvRowDataPtr>& Rows,
										long& nOptPositions,long& nUndPositions,CComObject<CMmRvUndColl>* pUndColl ){
	CMmRiskView::CRowsData aggregationRows;
// 	if(!CheckPositions(lExpiryFilter))
// 		return;
	// first, create row for this aggregation
	if(!CreateRow(pUndAtom, outlineLevel, aggregationRows))
		return;
	
	long nOptPosSave = nOptPositions;
	long nUndPosSave = nUndPositions;
	// second, create rows for positions reside in this aggregation
	size_t synthUndCnt = CreateRowsForPositions(pUndAtom, lExpiryFilter, outlineLevel, sortCmp, aggregationRows, nOptPositions,nUndPositions, pUndColl  );

	// sort positions
	std::sort(aggregationRows.begin() + 1 + synthUndCnt, aggregationRows.end(), *sortCmp );

	// make rows for children aggregation
	CMmRiskView::CRowsData childrenAggRows;

	// expiry child aggregations first
	Aggregations::iterator itrCurAgg = Aggregations_.begin();
	Aggregations::iterator itrEndAgg = Aggregations_.end();
	for (;itrCurAgg != itrEndAgg; ++itrCurAgg) {
		MmRvAggDataPtr pAgg = *itrCurAgg;
		if (!pAgg || pAgg->Type_ != enExpAgg) continue;
		IMmRvRowDataPtr spAggRowData;
		CComObject<CMmRvRowData>* pRow = NULL;
		if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pRow))) {
			spAggRowData.Attach(pRow, TRUE);
			pRow->m_pUnd = pUndAtom;
			pRow->m_spUnd.Attach(pUndAtom, TRUE);
			pRow->m_Type = pAgg->Type_ == enUndAgg ? RDT_UNDAGG : RDT_AGG;
			pRow->m_nLevel = outlineLevel;
			pRow->m_pAgg = pAgg;
			childrenAggRows.push_back(spAggRowData);
		}
	}

	// sort expiry child aggregations
	std::sort(childrenAggRows.begin(), childrenAggRows.end(), *sortCmp );
	CMmRiskView::CRowsData::size_type expAggCount = childrenAggRows.size();

	// future aggregation next
	itrCurAgg = Aggregations_.begin();
	for (;itrCurAgg != itrEndAgg; ++itrCurAgg) {
		MmRvAggDataPtr pAgg = *itrCurAgg;
		if (!pAgg || pAgg->Type_ != enFutAgg) continue;
		IMmRvRowDataPtr spAggRowData;
		CComObject<CMmRvRowData>* pRow = NULL;
		if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pRow))) {
			spAggRowData.Attach(pRow, TRUE);
			pRow->m_pUnd = pUndAtom;
			pRow->m_spUnd.Attach(pUndAtom, TRUE);
			pRow->m_Type = pAgg->Type_ == enUndAgg ? RDT_UNDAGG : RDT_AGG;
			pRow->m_nLevel = outlineLevel;
			pRow->m_pAgg = pAgg;
			childrenAggRows.push_back(spAggRowData);
		}
	}
	std::sort(childrenAggRows.begin()+expAggCount, childrenAggRows.end(), *sortCmp );
	
	// create rows for data that reside in every child aggregation
	CMmRiskView::CRowsData::iterator itrCurChildAgg = childrenAggRows.begin();
	CMmRiskView::CRowsData::iterator itrEndChildAgg = childrenAggRows.end();
	for ( ;itrCurChildAgg != itrEndChildAgg; ++itrCurChildAgg) {
		CMmRvRowData *pRow = static_cast<CMmRvRowData *>( (*itrCurChildAgg).GetInterfacePtr() );
		MmRvAggDataPtr p(pRow->m_pAgg);
		if (!pRow || !p) continue;
		p->CreateRows(pUndAtom, lExpiryFilter, outlineLevel + 1, sortCmp, aggregationRows, nOptPositions, nUndPositions, pUndColl);
	}

	
	if(!CMmRvAggData::IsAggregationRowVisible(this))
		return;
	

	// add rows of this aggregation into final rows vector
	CMmRiskView::CRowsData::iterator itrCurRow = aggregationRows.begin();
	CMmRiskView::CRowsData::iterator itrEndRow = aggregationRows.end();
	Rows.reserve(Rows.size() + aggregationRows.size());
	for (; itrCurRow != itrEndRow; ++itrCurRow ) {
		IMmRvRowDataPtr spRow;
		spRow = (*itrCurRow);
		Rows.push_back(spRow);
		//if (Type_ != enExpAgg ) continue;
		CMmRvRowData *pRowData = dynamic_cast<CMmRvRowData*>((*itrCurRow).GetInterfacePtr() );
		if ( pRowData && pRowData->m_Type == RDT_POS && pRowData->m_pPos ) {
			CMmRvPosAtom* pPos = pRowData->m_pPos;
			if(VARIANT_TRUE == pPos->m_bIsSynthetic && pPos->m_spSynthGreeks!=NULL)	{
				CMmRvSynthGreeksColl* pSynthColl = dynamic_cast<CMmRvSynthGreeksColl*>(pPos->m_spSynthGreeks.GetInterfacePtr());
				ATLASSERT(pSynthColl);
				if(pSynthColl) {
					CMmRvSynthGreeksColl::EnumCollType::iterator itrSynth    =  pSynthColl->m_coll.begin();
					CMmRvSynthGreeksColl::EnumCollType::iterator itrSynthEnd =  pSynthColl->m_coll.end();
					for(; itrSynth != itrSynthEnd; ++itrSynth) {
						CMmRvSynthGreeksAtom* pSynthAtom = dynamic_cast<CMmRvSynthGreeksAtom*>(itrSynth->second);
						if(pSynthAtom)	{
							CComObject<CMmRvRowData>* pSynthRow = NULL;
							if(SUCCEEDED(CComObject<CMmRvRowData>::CreateInstance(&pSynthRow))) 	{
								IMmRvRowDataPtr spSynthRowData;
								spSynthRowData.Attach(pSynthRow, TRUE);
								pSynthRow->m_spPos.Attach(pPos, TRUE);
								pSynthRow->m_pPos = pPos;
								pSynthRow->m_Type = RDT_POS;
								pSynthRow->m_spUnd = pRowData->m_spUnd;
								pSynthRow->m_pUnd = pRowData->m_pUnd;
								pSynthRow->m_spSynthGreeks.Attach(pSynthAtom, TRUE);
								pSynthRow->m_pSynthGreeks = pSynthAtom;
								pSynthRow->m_nLevel = pRowData->m_nLevel+1;
								pSynthAtom->m_bVisible = VARIANT_TRUE;
								Rows.push_back( spSynthRowData );		// add row for synthetic position
							}
						}
					}
				}
			}
		}
	}
}

// void __MmRvAggregationData::Calc(
// 		  CMmRvPosColl*		 pPosColl,
// 		  CMmRvUndColl*		 pUndColl,
// 		  CMmRvUndAtom*		 pIdx,
// 		  VARIANT_BOOL		 bIsPnlLTD,
// 		  EtsCalcModelTypeEnum enCalcModel,
// 		  VARIANT_BOOL		 bUseTheoVolatility,
// 		  VARIANT_BOOL		 bUseTheoVolaNoBid,
// 		  VARIANT_BOOL	     bUseTheoVolaBadMarket,
// 		  DOUBLE				 dUndPriceTolerance,
// 		  EtsPriceRoundingRuleEnum enPriceRoundingRule,
// 		  DATE				 dtCalcDate)
// {
// 	try
// 	{
// 		Clear(true, false);
// 		if(pPosColl)
// 		{
// 			CMmRvPosColl::EnumCollType::iterator itrPos    = pPosColl->m_coll.begin();
// 			CMmRvPosColl::EnumCollType::iterator itrPosEnd = pPosColl->m_coll.end();
// 			for(;itrPos!=itrPosEnd; ++itrPos)
// 			{
// 				CMmRvPosAtom* pPosAtom = dynamic_cast<CMmRvPosAtom*>(itrPos->second);
// 				if(pPosAtom != NULL)
// 				{
// 					VARIANT_BOOL bVisible = VARIANT_FALSE;
// 					//_CHK(pPosAtom->get_Visible(&bVisible));
// 					//if(bVisible)
// 					{
// 						EtsContractTypeEnum enContractType = pPosAtom->m_enContractType;
// 						LONG nPosQty = pPosAtom->m_nQty;
// 						LONG nPosQtyInShares = pPosAtom->m_nQtyInShares;
// 
// 						// options
// 						if(enContractType == enCtOption || enContractType == enCtFutOption)
// 						{
// 							if(m_nOptQty <= BAD_LONG_VALUE) m_nOptQty = 0L;
// 							m_nOptQty += nPosQty;
// 
// 							DATE dtExpiry = 0.;
// 							_CHK(pPosAtom->get_Expiry(&dtExpiry));
// 							DOUBLE dStrike = 0.;
// 							_CHK(pPosAtom->get_Strike(&dStrike));
// 
// 							if(dtExpiry >= dtCalcDate)
// 							{
// 								double dUndMidPrice = 0;
// 								if(enContractType == enCtOption)
// 								{
// 									IEtsPriceProfileAtomPtr spUndPriceProfile;
// 									IEtsPriceProfileAtomPtr spOptPriceProfile;
// 									ISynthRootAtomPtr       spSynthRoot;
// 									IMmRvUndAtomPtr spUnd =	pUndColl->GetUnderlying(pPosAtom->m_nUndID);
// 
// 									_CHK(spUnd->get_UndPriceProfile(&spUndPriceProfile));
// 									_CHK(spUnd->get_OptPriceProfile(&spOptPriceProfile));
// 
// 									if(pPosAtom->m_bIsSynthetic)
// 									{
// 										ISynthRootCollPtr spSynthRootColl;
// 										_CHK(spUnd->get_SynthRoots(&spSynthRootColl));
// 										if(spSynthRootColl != NULL)
// 										{
// 											spSynthRoot = spSynthRootColl->Item[pPosAtom->m_nOptionRootID];
// 											if(spSynthRoot != NULL)
// 											{
// 												DOUBLE dSynthBid = 0., dSynthAsk = 0., dSynthLast = 0.;
// 												_CHK(spUnd->GetSyntheticUnderlyingPrice(pUndColl, spSynthRoot, &dSynthBid, &dSynthAsk, &dSynthLast));
// 												dUndMidPrice = spUndPriceProfile->GetUndPriceMid(dSynthBid, dSynthAsk, dSynthLast, dUndPriceTolerance, enPriceRoundingRule, NULL);
// 											}
// 										}
// 									}
// 									else
// 									{
// 										CMmRvUndAtom*  pUnd = dynamic_cast<CMmRvUndAtom*>(spUnd.GetInterfacePtr());
// 
// 										dUndMidPrice = spUndPriceProfile->GetUndPriceMid(pUnd->m_pPrice->m_dPriceBid, pUnd->m_pPrice->m_dPriceAsk,
// 											pUnd->m_pPrice->m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, NULL);
// 									}
// 
// 									pPosAtom->_CalcOptPositionData(spOptPriceProfile,
// 										spSynthRoot,
// 										bIsPnlLTD,
// 										bUseTheoVolatility,
// 										bUseTheoVolaNoBid, 
// 										bUseTheoVolaBadMarket,
// 										dUndPriceTolerance,
// 										enPriceRoundingRule,
// 										pUndColl,
// 										dUndMidPrice,
// 										pPosAtom->m_nUndID
// 										);									
// 
// 
// 								}
// 								else
// 								{
// 									IMmRvUndAtomPtr spUnd =	pUndColl->GetUnderlying(pPosAtom->m_nUndID);
// 									CMmRvUndAtom*   pUnd  = dynamic_cast<CMmRvUndAtom*>(spUnd.GetInterfacePtr());
// 									IEtsPriceProfileAtomPtr spUndPriceProfile;
// 									IEtsPriceProfileAtomPtr spOptPriceProfile;
// 
// 
// 									_CHK(spUnd->get_UndPriceProfile(&spUndPriceProfile));
// 									_CHK(spUnd->get_OptPriceProfile(&spOptPriceProfile));
// 
// 									dUndMidPrice = spUndPriceProfile->GetUndPriceMid(pUnd->m_pPrice->m_dPriceBid, pUnd->m_pPrice->m_dPriceAsk,
// 										pUnd->m_pPrice->m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, NULL);
// 
// 									pPosAtom->_CalcFutPositionData(spOptPriceProfile,
// 										bIsPnlLTD,
// 										bUseTheoVolatility,
// 										bUseTheoVolaNoBid, 
// 										bUseTheoVolaBadMarket,
// 										dUndPriceTolerance,
// 										enPriceRoundingRule,	dUndMidPrice);
// 
// 								}
// 								_CalcTotalsForOptionPos(pPosAtom, dUndMidPrice);
// 							}
// 							else
// 							{
// 								pPosAtom->put_LogEnhansement ( L"The option is expired" ) ;
// 
// 								WCHAR strparam[200] ;
// 								_snwprintf_s ( strparam, sizeof(strparam), L"Expiration Date %f" , dtExpiry  ) ;
// 
// 								IRvMmQuoteAtomPtr spQuote;
// 								pPosAtom->get_Quote(&spQuote);
// 
// 								if(spQuote!=NULL)
// 									spQuote->put_VolaCalculatedParametrs( strparam ) ;
// 
// 								SetAllValuesAsBad();
// 							}
// 						}
// 
// 						// underlyings
// 						else if(enContractType == enCtStock || enContractType == enCtIndex)
// 						{
// 							if(m_nQty <= BAD_LONG_VALUE) m_nQty = 0L;
// 							m_nQty += nPosQtyInShares;
// 
// 
// 							IMmRvUndAtomPtr spUnd =	pUndColl->GetUnderlying(pPosAtom->m_nID);
// 							CMmRvUndAtom*   pUnd  = dynamic_cast<CMmRvUndAtom*>(spUnd.GetInterfacePtr());
// 							IEtsPriceProfileAtomPtr spUndPriceProfile;
// 							double dUndPriceBid = 0;
// 							double dUndPriceAsk = 0;
// 							double dUndPriceMid = 0;
// 							EtsReplacePriceStatusEnum enUndPriceStatusMid = enRpsNone;
// 							EtsReplacePriceStatusEnum enUndPriceStatusBid = enRpsNone;
// 							EtsReplacePriceStatusEnum enUndPriceStatusAsk = enRpsNone;
// 
// 							_CHK(spUnd->get_UndPriceProfile(&spUndPriceProfile));
// 
// 							dUndPriceMid = spUndPriceProfile->GetUndPriceMid(pUnd->m_pPrice->m_dPriceBid, pUnd->m_pPrice->m_dPriceAsk,
// 								pUnd->m_pPrice->m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enUndPriceStatusMid);
// 
// 							dUndPriceBid = spUndPriceProfile->GetUndPriceBidForPnL(pUnd->m_pPrice->m_dPriceBid, pUnd->m_pPrice->m_dPriceAsk,
// 								pUnd->m_pPrice->m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enUndPriceStatusBid);
// 
// 							dUndPriceAsk = spUndPriceProfile->GetUndPriceAskForPnL(pUnd->m_pPrice->m_dPriceBid, pUnd->m_pPrice->m_dPriceAsk,
// 								pUnd->m_pPrice->m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enUndPriceStatusAsk);
// 
// 
// 
// 							_CHK(pPosAtom->CalcPnlMtm(bIsPnlLTD, dUndPriceBid, dUndPriceAsk, VARIANT_TRUE));
// 
// 							if(dUndPriceMid > DBL_EPSILON)
// 							{
// 								if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
// 								m_dDeltaEq += nPosQtyInShares * dUndPriceMid;
// 							}
// 							else
// 								m_bBadDeltaEq = VARIANT_TRUE;
// 
// 							if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
// 							m_dNetDelta += nPosQtyInShares;
// 						}
// 
// 						// futures
// 						else if(enContractType == enCtFuture)
// 						{
// 							if(m_nFutQty <= BAD_LONG_VALUE) m_nFutQty = 0L;
// 							m_nFutQty += nPosQty;
// 
// 							if(m_nQty <= BAD_LONG_VALUE) m_nQty = 0L;
// 							m_nQty += nPosQtyInShares;
// 
// 
// 							IMmRvFutAtomPtr spFut;
// 							_CHK(pPosAtom->get_Fut(&spFut));
// 
// 							IMmRvUndAtomPtr spUnd =	pUndColl->GetUnderlying(pPosAtom->m_nUndID);
// 							CMmRvUndAtom*   pUnd  = dynamic_cast<CMmRvUndAtom*>(spUnd.GetInterfacePtr());
// 
// 							IEtsPriceProfileAtomPtr spUndPriceProfile;
// 							double dUndPriceMid = 0;
// 							EtsReplacePriceStatusEnum enUndPriceStatusMid = enRpsNone;
// 
// 							_CHK(spUnd->get_UndPriceProfile(&spUndPriceProfile));
// 
// 							dUndPriceMid = spUndPriceProfile->GetUndPriceMid(pUnd->m_pPrice->m_dPriceBid, pUnd->m_pPrice->m_dPriceAsk,
// 								pUnd->m_pPrice->m_dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enUndPriceStatusMid);
// 
// 
// 							if(spFut != NULL)
// 							{
// 								EtsReplacePriceStatusEnum enFutPriceStatusMid = enRpsNone;
// 								EtsReplacePriceStatusEnum enFutPriceStatusBid = enRpsNone;
// 								EtsReplacePriceStatusEnum enFutPriceStatusAsk = enRpsNone;
// 								DOUBLE dFutPriceMid = 0., dFutPriceBid = 0., dFutPriceAsk = 0.;
// 								IEtsPriceProfileAtomPtr spUndPriceProfile;
// 
// 								_CHK(spFut->get_UndPriceProfile(&spUndPriceProfile));
// 
// 								if(spUndPriceProfile != NULL)
// 								{
// 									DOUBLE dPriceBid = 0., dPriceAsk = 0., dPriceLast = 0.;
// 
// 									_CHK(spFut->get_PriceBid(&dPriceBid));
// 									_CHK(spFut->get_PriceAsk(&dPriceAsk));
// 									_CHK(spFut->get_PriceLast(&dPriceLast));
// 
// 									dFutPriceMid = spUndPriceProfile->GetUndPriceMid(dPriceBid, dPriceAsk,
// 										dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enFutPriceStatusMid);
// 
// 									dFutPriceBid = spUndPriceProfile->GetUndPriceBidForPnL(dPriceBid, dPriceAsk,
// 										dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enFutPriceStatusBid);
// 
// 									dFutPriceAsk = spUndPriceProfile->GetUndPriceAskForPnL(dPriceBid, dPriceAsk,
// 										dPriceLast, dUndPriceTolerance, enPriceRoundingRule, &enFutPriceStatusAsk);
// 								}
// 
// 								IRvMmQuoteAtomPtr spQuote;
// 								_CHK(pPosAtom->get_Quote(&spQuote));
// 								if( spQuote!=NULL )
// 								{
// 									_CHK(spQuote->put_ReplacePriceStatus(static_cast<EtsReplacePriceStatusEnum>(enFutPriceStatusMid | enFutPriceStatusBid | enFutPriceStatusAsk)));
// 								}
// 
// 								_CHK(pPosAtom->CalcPnlMtm(bIsPnlLTD, dFutPriceBid, dFutPriceAsk, VARIANT_TRUE));
// 							}
// 
// 							if(dUndPriceMid > DBL_EPSILON)
// 							{
// 								if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
// 								m_dDeltaEq += nPosQtyInShares * dUndPriceMid;
// 							}
// 							else
// 								m_bBadDeltaEq = VARIANT_TRUE;
// 
// 							if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
// 							m_dNetDelta += nPosQtyInShares;
// 						}
// 
// 						// PnlMtm
// 						if(pPosAtom->m_dPnlMtm > BAD_DOUBLE_VALUE)
// 						{
// 							if(m_dPnlMtm <= BAD_DOUBLE_VALUE) m_dPnlMtm = 0.;
// 							m_dPnlMtm += pPosAtom->m_dPnlMtm;
// 						}
// 						else
// 							m_bBadPnlMtm = VARIANT_TRUE;
// 
// 						// PnlTheo
// 						if(pPosAtom->m_dPnlTheo > BAD_DOUBLE_VALUE)
// 						{
// 							if(m_dPnlTheo <= BAD_DOUBLE_VALUE) m_dPnlTheo = 0.;
// 							m_dPnlTheo += pPosAtom->m_dPnlTheo;
// 						}
// 						else
// 							m_bBadPnlTheo = VARIANT_TRUE;
// 					}
// 				}
// 			}
// 		}
// 	}
// 	catch (_com_error& /*e*/)
// 	{
// 
// 	}
// }

// void __MmRvAggregationData::_CalcTotalsForOptionPos(IMmRvPosAtomPtr spPos, DOUBLE dUndPriceMid)
// {
// 	DOUBLE dPosValue = BAD_DOUBLE_VALUE;
// 	// DeltaInShares
// 	_CHK(spPos->get_DeltaInShares(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dOptDelta <= BAD_DOUBLE_VALUE) m_dOptDelta = 0.;
// 		m_dOptDelta += dPosValue;
// 		if(m_dNetDelta <= BAD_DOUBLE_VALUE) m_dNetDelta = 0.;
// 		m_dNetDelta += dPosValue;
// 		if(dUndPriceMid > DBL_EPSILON)
// 		{
// 			if(m_dDeltaEq <= BAD_DOUBLE_VALUE) m_dDeltaEq = 0.;
// 			m_dDeltaEq += dPosValue * dUndPriceMid;
// 		}
// 		else
// 			m_bBadDeltaEq = VARIANT_TRUE;
// 	}
// 	else
// 	{
// 		m_bBadNetDelta = VARIANT_TRUE;
// 		m_bBadOptDelta = VARIANT_TRUE;
// 		m_bBadDeltaEq = VARIANT_TRUE;
// 	}
// 
// 	// GammaInSharesPerc
// 	_CHK(spPos->get_GammaInSharesPerc(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dGammaPerc <= BAD_DOUBLE_VALUE) m_dGammaPerc = 0.;
// 		m_dGammaPerc += dPosValue;
// 		if(dUndPriceMid > DBL_EPSILON)
// 		{
// 			if(m_dGammaEq <= BAD_DOUBLE_VALUE) m_dGammaEq = 0.;
// 			m_dGammaEq += dPosValue * dUndPriceMid;
// 		}
// 		else
// 			m_bBadGammaEq = VARIANT_TRUE;
// 	}
// 	else
// 	{
// 		m_bBadGammaPerc = VARIANT_TRUE;
// 		m_bBadGammaEq = VARIANT_TRUE;
// 	}
// 
// 	// GammaInShares
// 	_CHK(spPos->get_GammaInShares(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dGamma <= BAD_DOUBLE_VALUE) m_dGamma = 0.;
// 		m_dGamma += dPosValue;
// 	}
// 	else
// 		m_bBadGamma = VARIANT_TRUE;
// 
// 
// 	// Net Gamma
// 	_CHK(spPos->get_NetGamma(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dNetGamma <= BAD_DOUBLE_VALUE) m_dNetGamma = 0.;
// 		m_dNetGamma += dPosValue;
// 	}
// 	else
// 		m_bBadNetGamma = VARIANT_TRUE;
// 
// 
// 	// VegaInShares
// 	_CHK(spPos->get_VegaInShares(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dVega <= BAD_DOUBLE_VALUE) m_dVega = 0.;
// 		m_dVega += dPosValue;
// 	}
// 	else
// 		m_bBadVega = VARIANT_TRUE;
// 
// 	// WtdVega
// 	_CHK(spPos->get_WtdVega(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dWtdVega <= BAD_DOUBLE_VALUE) m_dWtdVega = 0.;
// 		m_dWtdVega += dPosValue;
// 	}
// 	else
// 		m_bBadWtdVega = VARIANT_TRUE;
// 
// 	// ThetaInShares
// 	_CHK(spPos->get_ThetaInShares(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dTheta <= BAD_DOUBLE_VALUE) m_dTheta = 0.;
// 		m_dTheta += dPosValue;
// 	}
// 	else
// 		m_bBadTheta = VARIANT_TRUE;
// 
// 	// RhoInShares
// 	_CHK(spPos->get_RhoInShares(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dRho <= BAD_DOUBLE_VALUE) m_dRho = 0.;
// 		m_dRho += dPosValue;
// 	}
// 	else
// 		m_bBadRho = VARIANT_TRUE;
// 
// 	// ThetaDeltaInShares
// 	_CHK(spPos->get_ThetaDeltaInShares(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dThetaDelta <= BAD_DOUBLE_VALUE) m_dThetaDelta = 0.;
// 		m_dThetaDelta += dPosValue;
// 	}
// 	else
// 		m_bBadThetaDelta = VARIANT_TRUE;
// 
// 	// ThetaGammaInShares
// 	_CHK(spPos->get_ThetaGammaInShares(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dThetaGamma <= BAD_DOUBLE_VALUE) m_dThetaGamma = 0.;
// 		m_dThetaGamma += dPosValue;
// 	}
// 	else
// 		m_bBadThetaGamma = VARIANT_TRUE;
// 
// 	// VegaDeltaInShares
// 	_CHK(spPos->get_VegaDeltaInShares(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dVegaDelta <= BAD_DOUBLE_VALUE) m_dVegaDelta = 0.;
// 		m_dVegaDelta += dPosValue;
// 	}
// 	else
// 		m_bBadVegaDelta = VARIANT_TRUE;
// 
// 	// VegaGammaInShares
// 	_CHK(spPos->get_VegaGammaInShares(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dVegaGamma <= BAD_DOUBLE_VALUE) m_dVegaGamma = 0.;
// 		m_dVegaGamma += dPosValue;
// 	}
// 	else
// 		m_bBadVegaGamma = VARIANT_TRUE;
// 
// 	// TimeValue
// 	_CHK(spPos->get_TimeValue(&dPosValue));
// 	if(dPosValue > BAD_DOUBLE_VALUE)
// 	{
// 		if(m_dTimeValue <= BAD_DOUBLE_VALUE) m_dTimeValue = 0.;
// 		m_dTimeValue += dPosValue;
// 	}
// 	else
// 		m_bBadTimeValue = VARIANT_TRUE;
// 
// // 	VARIANT_BOOL bPosIsSynthetic = VARIANT_FALSE;
// // 	_CHK(spPos->get_IsSynthetic(&bPosIsSynthetic));
// // 	if(bPosIsSynthetic)
// // 	{
// // 		IMmRvSynthGreeksCollPtr spPosSynthGreeksColl;
// // 		_CHK(spPos->get_SynthGreeks(&spPosSynthGreeksColl));
// // 
// // 		if(spPosSynthGreeksColl != NULL)
// // 		{
// // 			IMmRvSynthGreeksAtomPtr spPosSynthGreeks;
// // 			LONG nSynthUndID = 0L;
// // 			DOUBLE dSelfValue = BAD_DOUBLE_VALUE;
// // 
// // 			IUnknownPtr spUnk;
// // 			_variant_t varItem;
// // 			ULONG nFetched = 0L;
// // 			HRESULT hr;
// // 
// // 			_CHK(spPosSynthGreeksColl->get__NewEnum(&spUnk));
// // 			IEnumVARIANTPtr spPosSynthGreekEnum(spUnk);
// // 			_CHK(spPosSynthGreekEnum->Reset());
// // 			while((hr = spPosSynthGreekEnum->Next(1L, &varItem, &nFetched)) == S_OK)
// // 			{
// // 				ATLASSERT(varItem.vt == VT_DISPATCH);
// // 				spPosSynthGreeks = varItem;
// // 				if(spPosSynthGreeks != NULL)
// // 				{
// // 					_CHK(spPosSynthGreeks->get_SynthUndID(&nSynthUndID));
// // 					IMmRvSynthGreeksAtomPtr spSynthGreeks;
// // 					_CHK(m_spSynthGreeks->get_Item(nSynthUndID, &spSynthGreeks));
// // 
// // 					if(spSynthGreeks != NULL)
// // 					{
// // 						// DeltaInShares
// // 						_CHK(spPosSynthGreeks->get_DeltaInShares(&dPosValue));
// // 						if(dPosValue > BAD_DOUBLE_VALUE)
// // 						{
// // 							_CHK(spSynthGreeks->get_DeltaInShares(&dSelfValue));
// // 							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
// // 							_CHK(spSynthGreeks->put_DeltaInShares(dSelfValue + dPosValue));
// // 						}
// // 						else
// // 							_CHK(spSynthGreeks->put_BadDelta(VARIANT_TRUE));
// // 
// // 						// GammaInSharesPerc
// // 						_CHK(spPosSynthGreeks->get_GammaInSharesPerc(&dPosValue));
// // 						if(dPosValue > BAD_DOUBLE_VALUE)
// // 						{
// // 							_CHK(spSynthGreeks->get_GammaInSharesPerc(&dSelfValue));
// // 							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
// // 							_CHK(spSynthGreeks->put_GammaInSharesPerc(dSelfValue + dPosValue));
// // 						}
// // 						else
// // 							_CHK(spSynthGreeks->put_BadGammaPerc(VARIANT_TRUE));
// // 
// // 						// GammaInShares
// // 						_CHK(spPosSynthGreeks->get_GammaInShares(&dPosValue));
// // 						if(dPosValue > BAD_DOUBLE_VALUE)
// // 						{
// // 							_CHK(spSynthGreeks->get_GammaInShares(&dSelfValue));
// // 							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
// // 							_CHK(spSynthGreeks->put_GammaInShares(dSelfValue + dPosValue));
// // 						}
// // 						else
// // 							_CHK(spSynthGreeks->put_BadGamma(VARIANT_TRUE));
// // 
// // 						// Net Gamma
// // 						_CHK(spPosSynthGreeks->get_NetGamma(&dPosValue));
// // 						if(dPosValue > BAD_DOUBLE_VALUE)
// // 						{
// // 							_CHK(spSynthGreeks->get_NetGamma(&dSelfValue));
// // 							if(dSelfValue <= BAD_DOUBLE_VALUE) dSelfValue = 0.;
// // 							_CHK(spSynthGreeks->put_NetGamma(dSelfValue + dPosValue));
// // 						}
// // 						else
// // 							_CHK(spSynthGreeks->put_BadNetGamma(VARIANT_TRUE));
// // 
// // 					}
// // 				}
// // 			}
// // 		}
// // 	}
// }
