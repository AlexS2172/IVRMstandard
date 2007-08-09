// MmRvRowData.cpp : Implementation of CMmRvRowData

#include "stdafx.h"
#include "MmRvRowData.h"
const static _variant_t _vtEmpty(L"");
const static _variant_t _vtCall(L"C");
const static _variant_t _vtPut(L"P");
const static _variant_t STR_NA(L"--");
const static _variant_t AGGSTR_NA(L"");
const static _variant_t ASTR_NA(L"AGG");

// CMmRvRowData
void CMmRvRowData::GetValue(double dValue, bool bForSorting, bool bNegativeFormatting, long lRound, _variant_t& vtRet)
{
	if(dValue >= 0)
		vtRet = _variant_t(dValue);
	else
		if(IsBadValue(dValue))
			vtRet = bForSorting?_variant_t(BAD_DOUBLE_VALUE):STR_NA;
		else
			if(bNegativeFormatting)
			{
				if(bForSorting)
				{
				  vtRet = _variant_t(dValue);
				}
				else
				{
					wchar_t wchBuffer[64] = {0};
					wchar_t wchFormat[10]  = {0};

					_snwprintf_s(wchFormat, sizeof(wchFormat)/sizeof(wchar_t), L"(%%.%df)", lRound);
					_snwprintf_s(wchBuffer, sizeof(wchBuffer)/sizeof(wchar_t), wchFormat, dValue);
					vtRet = _variant_t(wchBuffer);
				}
			}
			else
			   vtRet = _variant_t(dValue);
}

void CMmRvRowData::GetValue(long lValue, bool bForSorting, bool bNegativeFormatting, _variant_t& vtRet)
{
	if(lValue >= 0)
		vtRet = _variant_t(lValue);
	else
		if(IsBadValue(lValue))
			vtRet = bForSorting?_variant_t((long)BAD_LONG_VALUE):STR_NA;
		else
			if(bNegativeFormatting)
			{	
				if(bForSorting)
					vtRet = _variant_t(lValue);
				else
				{
					wchar_t wchBuffer[64] = {0};
					_snwprintf_s(wchBuffer, sizeof(wchBuffer)/sizeof(wchar_t), L"(%d)", lValue);
					vtRet = _variant_t(wchBuffer);
				}
			}
			else
				vtRet = _variant_t(lValue);
}

bool CMmRvRowData::GetField(RisksPosColumnEnum enCol, _variant_t& vtRet, bool bForSorting)
{
	bool bNegativeFormatting = false;
	long lRound              = 0 ;
	if(m_pPos)
	{
		switch(m_pPos->m_enContractType)
		{
			case enCtFutOption:
				return GetFutOptionField(enCol, vtRet, bForSorting, bNegativeFormatting, lRound);
				break;
			case enCtOption:
				return GetOptionField(enCol, vtRet, bForSorting, bNegativeFormatting, lRound);
				break;
			case enCtStock:
			case enCtIndex:
				return GetUndField(enCol, vtRet, bForSorting, bNegativeFormatting, lRound);
				break;
			case enCtFuture:
				return GetFutField(enCol, vtRet, bForSorting, bNegativeFormatting, lRound);
				break;
			default:
				ATLASSERT(false);
				return false;
		}
	}
	else
		if( m_pAgg)
			return GetAggregationField(enCol, vtRet, bForSorting, bNegativeFormatting, lRound);
	/*
	else if ( m_Type == RDT_UNDAGG) {
		return GetUndAggField(enCol, vtRet, bForSorting, bNegativeFormatting, lRound);
	}
	else{
		if(m_pAggregation ){
			return GetAggField(enCol, vtRet, bForSorting, bNegativeFormatting, lRound);
		}
	}*/
	return false;
}
/*bool CMmRvRowData::GetUndAggField(RisksPosColumnEnum enCol, _variant_t& vtRet, bool bForSorting, bool bNegativeFormatting, long lRound){
	if (!m_pUnd)
		return false;
	vtRet = vtMissing;
	switch(enCol)
	{
		case RPC_SYMBOL:
		case RPC_UND:
			vtRet = _variant_t(m_pUnd->m_bstrSymbol);
			break;
		case RPC_VEGA:
			GetValue(m_pUnd->m_dVega, bForSorting, bNegativeFormatting, lRound, vtRet);
			break;
		case RPC_BID:
			{
				if ( m_pUnd && m_pUnd->m_pPrice ) {
					vtRet = (m_pUnd->m_pPrice->m_dPriceBid > BAD_DOUBLE_VALUE) ?
						_variant_t(m_pUnd->m_pPrice->m_dPriceBid):
					(bForSorting? _variant_t(0.0): STR_NA);
				}
				else
					vtRet = bForSorting? _variant_t(0.0): STR_NA;
			}break;
		case RPC_ASK:
			{
				if ( m_pUnd && m_pUnd->m_pPrice ) {
					vtRet = m_pUnd->m_pPrice->m_dPriceAsk > BAD_DOUBLE_VALUE?
						_variant_t(m_pUnd->m_pPrice->m_dPriceAsk):
					bForSorting? _variant_t(0.0): STR_NA;
				}
				else
					vtRet = bForSorting? _variant_t(0.0): STR_NA;
			}break;
		case RPC_CLOSE:
			{
				if ( m_pUnd && m_pUnd->m_pPrice && m_pUnd->m_enContractType != enCtFutUnd) {
					vtRet = m_pUnd->m_pPrice->m_dPriceClose > BAD_DOUBLE_VALUE?
					_variant_t(m_pUnd->m_pPrice->m_dPriceClose):
					(bForSorting? _variant_t(0.0): STR_NA);
				}
				else
					vtRet = bForSorting? _variant_t(0.0): STR_NA;
			}break;
		case RPC_LAST:
			{
				if ( m_pUnd && m_pUnd->m_pPrice ) {
					vtRet = m_pUnd->m_pPrice->m_dPriceLast > BAD_DOUBLE_VALUE?
						_variant_t(m_pUnd->m_pPrice->m_dPriceLast):
					(bForSorting? _variant_t(0.0): STR_NA);
				}
				else
					vtRet = bForSorting? _variant_t(0.0): STR_NA;
			}break;
		case RPC_OPT_TYPE:
			vtRet = _vtEmpty;
			break;
		case RPC_DEL_UNIT:
			vtRet = _variant_t(m_pUnd->m_nLotSize);
			break;
		case RPC_EXPIRY:
		case RPC_STRIKE:
			vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
			break;
		case RPC_BETA_WTD_DELTA_USD:
			if ( m_pUnd )
				GetValue(m_pUnd->m_dBetaWtdDeltaEq, bForSorting, bNegativeFormatting, lRound, vtRet);
			break;
		case RPC_NET_DELTA_USD:
			if ( m_pUnd )
				GetValue(m_pUnd->m_dDeltaEq, bForSorting, bNegativeFormatting, lRound, vtRet);
			break;
		case RPC_NET_DELTA:
			if ( m_pUnd )
				GetValue(m_pUnd->m_dNetDelta, bForSorting, bNegativeFormatting, lRound, vtRet);
			break;
		case RPC_NETCHANGE:
			if ( m_pUnd )
				GetValue(m_pUnd->m_pPrice->m_dNetChange, bForSorting, bNegativeFormatting, lRound, vtRet);
			else
				vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
			break;
		//case RPC_DELTAP:
		//		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		//	break;
		case RPC_PNL_THEO:
			if ( m_pUnd) 
				GetValue( m_pUnd->m_dPnlTheo, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_PNL_MTM:
			if ( m_pUnd) 
				GetValue( m_pUnd->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_PNL_EDGE:
			if ( m_pUnd && m_pUnd->m_dPnlMtm > BAD_DOUBLE_VALUE && m_pUnd->m_dPnlTheo > BAD_DOUBLE_VALUE ){
				_variant_t pnlTheo, pnlMtm;
				GetValue( m_pUnd->m_dPnlTheo, bForSorting, bNegativeFormatting, lRound, pnlTheo);
				GetValue( m_pUnd->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, pnlMtm);
				if ( ( double) pnlTheo > BAD_DOUBLE_VALUE && ( double) pnlMtm > BAD_DOUBLE_VALUE ) {
					vtRet = ( double)pnlTheo - ( double)pnlMtm;
					return utils::HasValue(vtRet);
				}
			}
			vtRet = bForSorting?_variant_t(0.0):STR_NA;
			break;
		case RPC_OPT_QTY:
			if ( m_pUnd) {
				double d = ( m_pUnd->m_nOptQty == BAD_LONG_VALUE ? BAD_DOUBLE_VALUE : m_pUnd->m_nOptQty );
				GetValue( d, bForSorting, bNegativeFormatting, lRound, vtRet );
			}
			break;
		case RPC_OPT_DELTA:
			if ( m_pUnd )
				GetValue( m_pUnd->m_dOptDelta, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0.):STR_NA;
			break;
		case RPC_FUT_QTY:
			if ( m_pUnd) {
				double d = ( m_pUnd->m_nFutQty == BAD_LONG_VALUE ? BAD_DOUBLE_VALUE : m_pUnd->m_nFutQty );
				GetValue( d, bForSorting, bNegativeFormatting, lRound, vtRet );
			}
			break;
		case RPC_NET_GAMMA:
			if ( m_pUnd )
				GetValue( m_pUnd->m_dNetGamma, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_GAMMA:
			if ( m_pUnd )
				GetValue( m_pUnd->m_dGammaPerc, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_GAMMA_SHARES:
			if ( m_pUnd ) 
				GetValue( m_pUnd->m_dGamma, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		/*case RPC_GAMMAP:
			if ( m_pUnd ) 
				GetValue( m_pUnd->m_dGamma, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_RHO:
			if ( m_pUnd )
				GetValue( m_pUnd->m_dRho, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_THETA:
			if ( m_pUnd )
				GetValue( m_pUnd->m_dTheta, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_THETA_DELTA:
			if ( m_pUnd )
				GetValue( m_pUnd->m_dThetaDelta, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_THETA_GAMMA:
			if ( m_pUnd )
				GetValue( m_pUnd->m_dThetaGamma, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_TIME_VALUE:
			if ( m_pUnd )
				GetValue( m_pUnd->m_dTimeValue, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_VEGA_DELTA:
			if ( m_pUnd ) 
				GetValue( m_pUnd->m_dVegaDelta, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_VEGA_GAMMA:
			if ( m_pUnd ) 
				GetValue( m_pUnd->m_dVegaGamma, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_WTD_VEGA:
			if ( m_pUnd ) 
				GetValue( m_pUnd->m_dWtdVega, bForSorting, bNegativeFormatting, lRound, vtRet );
			break;
		case RPC_UND_POS:
		case RPC_FUTURES:
		case RPC_IMPORT_ID:
		case RPC_FUT_ROOT:
		case RPC_FUT_MATURITY:
		case RPC_FQUOT_UNIT:
		case RPC_FPRICE_FORMAT:
		case RPC_GAMMAP:
		case RPC_THETAP:
		case RPC_VEGAP:
		case RPC_RHOP:
		case RPC_DELTAP:
			vtRet = bForSorting ? _variant_t(0.0) : _vtEmpty;
			break;
		default:
			vtRet = bForSorting ? _variant_t(0.0) : L"UA: --";

	//case RPC_OPT_TYPE:
	//	vtRet = _vtEmpty;
	//	break;
	//case RPC_FUT_ROOT:
	//case RPC_FUTURES:
	//	vtRet = _vtEmpty;
	//	break;
	//case RPC_EXPIRY:
	//case RPC_STRIKE:
	//	vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
	//	break;
	//case RPC_BID:
	//	{
	//		vtRet = (m_pPos->m_pQuote->m_pPrice->m_dPriceBid > BAD_DOUBLE_VALUE) ?
	//			_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceBid):
	//		(bForSorting? _variant_t(0.0): STR_NA);
	//	}break;
	//case RPC_ASK:
	//	{
	//		vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceAsk > BAD_DOUBLE_VALUE?
	//			_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceAsk):
	//		bForSorting? _variant_t(0.0): STR_NA;
	//	}break;
	//case RPC_LAST:
	//	{
	//		vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceLast > BAD_DOUBLE_VALUE?
	//			_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceLast):
	//		bForSorting? _variant_t(0.0): STR_NA;
	//	}
	//case RPC_UND_POS:
	//	GetValue(m_pPos->m_nQtyInShares, bForSorting, bNegativeFormatting, vtRet);
	//case RPC_FUT_QTY:
	//case RPC_NET_DELTA:
	//case RPC_NET_DELTA_USD:
	//case RPC_BETA_WTD_DELTA_USD:
	//case RPC_FUT_MATURITY:
	//case RPC_OPT_QTY:
	//	vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
	//	break;
	//case RPC_PNL_MTM:
	//	GetValue(m_pPos->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet);
	//	break;
	//case RPC_PNL_THEO:
	//	GetValue(m_pPos->m_dPnlTheo, bForSorting, bNegativeFormatting, lRound, vtRet);
	//	break;
	//case RPC_PNL_EDGE:
	//	if(m_pPos->m_dPnlTheo > BAD_DOUBLE_VALUE && m_pPos->m_dPnlMtm > BAD_DOUBLE_VALUE)
	//		GetValue(m_pPos->m_dPnlTheo - m_pPos->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet);
	//	else
	//		vtRet = bForSorting?_variant_t(BAD_DOUBLE_VALUE):STR_NA;
	//	break;
	//case RPC_OPT_DELTA:
	//case RPC_GAMMA:
	//case RPC_NET_GAMMA:
	//case RPC_GAMMA_SHARES:
	//case RPC_VEGA:
	//case RPC_WTD_VEGA:
	//case RPC_THETA:
	//case RPC_RHO:
	//case RPC_VEGA_DELTA:
	//case RPC_VEGA_GAMMA:
	//case RPC_THETA_DELTA:
	//case RPC_THETA_GAMMA:
	//	vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
	//	break;
	/*case RPC_DEL_UNIT:
		vtRet = _variant_t(m_pUnd->m_nLotSize);
		break;
	case RPC_TIME_VALUE:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_CLOSE:
		vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceClose > BAD_DOUBLE_VALUE? _variant_t( m_pPos->m_pQuote->m_pPrice->m_dPriceClose): bForSorting?_variant_t(0):STR_NA;
		break;
	case RPC_IMPORT_ID:
		vtRet = STR_NA;
		break;
	case RPC_NETCHANGE:
		GetValue(m_pPos->m_pQuote->m_pPrice->m_dNetChange, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_DELTAP:
	case RPC_GAMMAP:
	case RPC_VEGAP:
	case RPC_THETAP:
	case RPC_RHOP:
		//	case RPC_MIV:
		//	case RPC_MIV_CALC_DATE:
		//vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		//	break;
		//case RPC_EXT_POSITION:
		//	GetValue(m_pPos->m_lExternalPosition, bForSorting, bNegativeFormatting, vtRet);
		//	break;
		//case RPC_DISTANSE_TO_STRIKE:
		//	break;
	}   
	return utils::HasValue(vtRet);

}*/
bool CMmRvRowData::GetUndField(RisksPosColumnEnum enCol, _variant_t& vtRet, bool bForSorting, bool bNegativeFormatting, long lRound)
{
	vtRet = vtMissing;

	switch(enCol)
	{
	case RPC_SYMBOL:
		vtRet = m_pPos->m_bstrSymbol;
		break;
	case RPC_OPT_TYPE:
		vtRet = _vtEmpty;
		break;
	case RPC_FUT_ROOT:
	case RPC_FUTURES:
		vtRet = _vtEmpty;
		break;
	case RPC_EXPIRY:
	case RPC_STRIKE:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_BID:
		{
			vtRet = (m_pPos->m_pQuote->m_pPrice->m_dPriceBid > BAD_DOUBLE_VALUE) ?
				_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceBid):
			(bForSorting? _variant_t(0.0): STR_NA);
		}break;
	case RPC_ASK:
		{
			vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceAsk > BAD_DOUBLE_VALUE?
				_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceAsk):
			bForSorting? _variant_t(0.0): STR_NA;
		}break;
	case RPC_LAST:
		{
			vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceLast > BAD_DOUBLE_VALUE?
				_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceLast):
			bForSorting? _variant_t(0.0): STR_NA;
		}
		break;
	case RPC_BETA_WTD_DELTA_USD:
	case RPC_FUT_QTY:
	case RPC_NET_DELTA:
	case RPC_NET_DELTA_USD:
	case RPC_FUT_MATURITY:
	case RPC_FQUOT_UNIT:
	case RPC_FPRICE_FORMAT:
	case RPC_OPT_QTY:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_PNL_MTM:
		GetValue(m_pPos->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_PNL_THEO:
		GetValue(m_pPos->m_dPnlTheo, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_PNL_EDGE:
		if(m_pPos->m_dPnlTheo > BAD_DOUBLE_VALUE && m_pPos->m_dPnlMtm > BAD_DOUBLE_VALUE)
			GetValue(m_pPos->m_dPnlTheo - m_pPos->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			vtRet = bForSorting?_variant_t(BAD_DOUBLE_VALUE):STR_NA;
		break;
	case RPC_OPT_DELTA:
	case RPC_GAMMA:
	case RPC_NET_GAMMA:
	case RPC_GAMMA_SHARES:
	case RPC_VEGA:
	case RPC_WTD_VEGA:
	case RPC_THETA:
	case RPC_RHO:
	case RPC_VEGA_DELTA:
	case RPC_VEGA_GAMMA:
	case RPC_THETA_DELTA:
	case RPC_THETA_GAMMA:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_UND:
		vtRet = _variant_t(m_pUnd->m_bstrSymbol);
		break;
	case RPC_UND_POS:
		vtRet = _variant_t(m_pPos->m_nQty);
		break;
	case RPC_DEL_UNIT:
		//!!!
		vtRet = _variant_t(m_pUnd->m_nLotSize);
		break;
	case RPC_TIME_VALUE:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_CLOSE:
		vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceClose > BAD_DOUBLE_VALUE? _variant_t( m_pPos->m_pQuote->m_pPrice->m_dPriceClose): bForSorting?_variant_t(0):STR_NA;
		break;
	case RPC_IMPORT_ID:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_NETCHANGE:
		GetValue(m_pPos->m_pQuote->m_pPrice->m_dNetChange, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_NET_EXPOSURE:
		GetValue( m_pPos->m_dNetExposure, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	//case RPC_DELTAP:
	//case RPC_GAMMAP:
	//case RPC_VEGAP:
	//case RPC_THETAP:
	//case RPC_RHOP:
//	case RPC_MIV:
//	case RPC_MIV_CALC_DATE:
	default:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
	//	break;
	//case RPC_EXT_POSITION:
	//	GetValue(m_pPos->m_lExternalPosition, bForSorting, bNegativeFormatting, vtRet);
	//	break;
	//case RPC_DISTANSE_TO_STRIKE:
	//	break;
	}   
	return utils::HasValue(vtRet);
}
/*bool CMmRvRowData::GetAggField(RisksPosColumnEnum enCol, _variant_t& vtRet, bool bForSorting, bool bNegativeFormatting, long lRound){
	vtRet = vtMissing;
	switch(enCol)
	{
		case RPC_SYMBOL:
			if ( m_pAggregation )
				vtRet = m_pAggregation->m_bstrSymbol;
			else
				vtRet = bForSorting ? _variant_t(0.0) : AGGSTR_NA;
			break;
		case RPC_UND:
			if ( m_pAggregation && m_pAggregation->m_pUnd )
				vtRet = m_pAggregation->m_pUnd->m_bstrSymbol;
			else
				vtRet = bForSorting ? _variant_t(0.0) : AGGSTR_NA;
			break;
		case RPC_ASK:
			if (m_pAggregation && m_pAggregation->m_pFut ) {
				vtRet = m_pAggregation ->m_pFut->m_dPriceAsk > BAD_DOUBLE_VALUE?
					_variant_t(m_pAggregation ->m_pFut->m_dPriceAsk):
				(bForSorting? _variant_t(0.0): STR_NA);
			}
			else if ( m_pAggregation && m_pAggregation ->m_pPrice ) {
				vtRet = m_pAggregation ->m_pPrice->m_dPriceAsk > BAD_DOUBLE_VALUE?
					_variant_t(m_pAggregation ->m_pPrice->m_dPriceAsk):
				(bForSorting? _variant_t(0.0): STR_NA);
			}
			else
				vtRet = bForSorting? _variant_t(0.0): STR_NA;
			break;
		case RPC_BID:
			if (m_pAggregation && m_pAggregation->m_pFut ) {
				vtRet = m_pAggregation ->m_pFut->m_dPriceBid > BAD_DOUBLE_VALUE?
					_variant_t(m_pAggregation ->m_pFut->m_dPriceBid):
				(bForSorting? _variant_t(0.0): STR_NA);
			}
			else if ( m_pAggregation && m_pAggregation ->m_pPrice ) {
				vtRet = m_pAggregation ->m_pPrice->m_dPriceBid > BAD_DOUBLE_VALUE?
					_variant_t(m_pAggregation ->m_pPrice->m_dPriceBid):
				(bForSorting? _variant_t(0.0): STR_NA);
			}
			else
				vtRet = bForSorting? _variant_t(0.0): STR_NA;
			break;
		case RPC_CLOSE:
			//if ( m_pAggregation && m_pAggregation ->m_pPrice ) {
			//	vtRet = m_pAggregation ->m_pPrice->m_dPriceClose > BAD_DOUBLE_VALUE?
			//		_variant_t(m_pAggregation ->m_pPrice->m_dPriceClose):
			//	(bForSorting? _variant_t(0.0): AGGSTR_NA);
			//}
			//else
			//	vtRet = bForSorting? _variant_t(0.0): AGGSTR_NA;
			//break;
			if (m_pAggregation && m_pAggregation->m_pFut ) {
				vtRet = m_pAggregation ->m_pFut->m_dPriceClose > BAD_DOUBLE_VALUE?
					_variant_t(m_pAggregation ->m_pFut->m_dPriceClose):
				(bForSorting? _variant_t(0.0): STR_NA);
			}
			else if ( m_pAggregation && m_pAggregation ->m_pPrice ) {
				vtRet = m_pAggregation ->m_pPrice->m_dPriceClose > BAD_DOUBLE_VALUE?
					_variant_t(m_pAggregation ->m_pPrice->m_dPriceClose):
				(bForSorting? _variant_t(0.0): STR_NA);
			}
			else
				vtRet = bForSorting? _variant_t(0.0): STR_NA;
			break;
		case RPC_LAST:
			if (m_pAggregation && m_pAggregation->m_pFut ) {
				vtRet = m_pAggregation ->m_pFut->m_dPriceLast > BAD_DOUBLE_VALUE?
					_variant_t(m_pAggregation ->m_pFut->m_dPriceLast):
				(bForSorting? _variant_t(0.0): STR_NA);
			}
			else if ( m_pAggregation && m_pAggregation ->m_pPrice ) {
				vtRet = m_pAggregation ->m_pPrice->m_dPriceLast > BAD_DOUBLE_VALUE?
					_variant_t(m_pAggregation ->m_pPrice->m_dPriceLast):
				(bForSorting? _variant_t(0.0): STR_NA);
			}
			else
				vtRet = bForSorting? _variant_t(0.0): STR_NA;
			break;
		case RPC_DEL_UNIT:
		case RPC_OPT_TYPE:
		case RPC_NETCHANGE:
			vtRet = bForSorting? _variant_t(0.0): AGGSTR_NA;
			break;
		case RPC_NET_DELTA:
			if ( m_pAggregation && m_pAggregation->m_dNetDelta > BAD_DOUBLE_VALUE )
				vtRet = _variant_t( m_pAggregation->m_dNetDelta );
			else
				vtRet = bForSorting ? _variant_t(0.) : AGGSTR_NA;
			break;
		case RPC_NET_DELTA_USD:
			if ( m_pAggregation && m_pAggregation->m_dDeltaEq > BAD_DOUBLE_VALUE )
				vtRet = _variant_t( m_pAggregation->m_dDeltaEq );
			else
				vtRet = bForSorting ? _variant_t(0.) : AGGSTR_NA;
			break;
		case RPC_EXPIRY:
			vtRet = bForSorting?_variant_t( (static_cast<long>(m_pAggregation->m_dtExpiry)) ? m_pAggregation->m_dtExpiry : 0.0):_vtEmpty;
			break;
		case RPC_BETA_WTD_DELTA_USD:
			if ( m_pAggregation && m_pAggregation->m_dBetaWtdDeltaEq > BAD_DOUBLE_VALUE )
				vtRet = _variant_t( m_pAggregation->m_dBetaWtdDeltaEq );
			else
				vtRet = bForSorting ? _variant_t(0.) : AGGSTR_NA;
			break;
		case RPC_GAMMAP:
		case RPC_THETAP:
		case RPC_VEGAP:
		case RPC_RHOP:
		case RPC_DELTAP:
			vtRet = bForSorting ? _variant_t(0.) : AGGSTR_NA;
			break;
		case RPC_PNL_THEO:
			if ( m_pAggregation && m_pAggregation->m_dPnlTheo > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dPnlTheo, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0.0):STR_NA;
			break;
		case RPC_PNL_MTM:
			if ( m_pAggregation && m_pAggregation->m_dPnlMtm > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0.0):STR_NA;
			break;
		case RPC_PNL_EDGE:
			if ( m_pAggregation && m_pAggregation->m_dPnlTheo > BAD_DOUBLE_VALUE && m_pAggregation->m_dPnlMtm > BAD_DOUBLE_VALUE ) {
				_variant_t pnlTheo, pnlMtm;
				GetValue( m_pAggregation->m_dPnlTheo, bForSorting, bNegativeFormatting, lRound, pnlTheo);
				GetValue( m_pAggregation->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, pnlMtm);
				if ( ( double ) pnlTheo > BAD_DOUBLE_VALUE && (double) pnlMtm > BAD_DOUBLE_VALUE ) {
					vtRet = ( double ) pnlTheo - ( double ) pnlMtm;
					return utils::HasValue(vtRet);
				}
			}
			vtRet = bForSorting?_variant_t(0.0):STR_NA;
			break;
		case RPC_OPT_QTY:
			if ( m_pAggregation && m_pAggregation->m_nOptQty > BAD_LONG_VALUE ) 
				GetValue( m_pAggregation->m_nOptQty, bForSorting, bNegativeFormatting, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_OPT_DELTA:
			if ( m_pAggregation && m_pAggregation->m_dOptDelta > BAD_LONG_VALUE ) 
				GetValue( m_pAggregation->m_dOptDelta, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0.):STR_NA;
			break;
		case RPC_FUT_QTY:
			if ( m_pAggregation && m_pAggregation->m_nFutQty > BAD_LONG_VALUE ) 
				GetValue( m_pAggregation->m_nFutQty, bForSorting, bNegativeFormatting, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_NET_GAMMA:
			if ( m_pAggregation && m_pAggregation->m_dNetGamma > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dNetGamma, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_GAMMA:
			if ( m_pAggregation && m_pAggregation->m_dGammaPerc > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dGammaPerc, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_GAMMA_SHARES:
			if ( m_pAggregation && m_pAggregation->m_dGamma > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dGamma, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_RHO:
			if ( m_pAggregation && m_pAggregation->m_dRho > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dRho, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_THETA:
			if ( m_pAggregation && m_pAggregation->m_dTheta > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dTheta, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_THETA_DELTA:
			if ( m_pAggregation && m_pAggregation->m_dThetaDelta > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dThetaDelta, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_THETA_GAMMA:
			if ( m_pAggregation && m_pAggregation->m_dThetaGamma > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dThetaGamma, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_TIME_VALUE:
			if ( m_pAggregation && m_pAggregation->m_dTimeValue > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dTimeValue, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_VEGA:
			if ( m_pAggregation && m_pAggregation->m_dVega > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dVega, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_VEGA_DELTA:
			if ( m_pAggregation && m_pAggregation->m_dVegaDelta > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dVegaDelta, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_VEGA_GAMMA:
			if ( m_pAggregation && m_pAggregation->m_dVegaGamma > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dVegaGamma, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_WTD_VEGA:
			if ( m_pAggregation && m_pAggregation->m_dWtdVega > BAD_DOUBLE_VALUE ) 
				GetValue( m_pAggregation->m_dWtdVega, bForSorting, bNegativeFormatting, lRound, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_UND_POS:
			if ( m_pAggregation && m_pAggregation->m_nQty > BAD_LONG_VALUE ) 
				GetValue( m_pAggregation->m_nQty, bForSorting, bNegativeFormatting, vtRet );
			else
				vtRet = bForSorting?_variant_t(0L):STR_NA;
			break;
		case RPC_FUTURES:
		case RPC_STRIKE:
		case RPC_IMPORT_ID:
		case RPC_FUT_ROOT:
		case RPC_FUT_MATURITY:
		case RPC_FQUOT_UNIT:
		case RPC_FPRICE_FORMAT:
			vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
			break;
		default:;
	}
	return utils::HasValue(vtRet);
}
*/
bool CMmRvRowData::GetFutField(RisksPosColumnEnum enCol, _variant_t& vtRet, bool bForSorting, bool bNegativeFormatting, long lRound)
{
	vtRet = vtMissing;

	switch(enCol)
	{
	case RPC_SYMBOL:
		vtRet = m_pPos->m_bstrSymbol;
		break;
	case RPC_OPT_TYPE:
		vtRet = _vtEmpty;
		break;
	case RPC_FUT_ROOT:
		{
			CComBSTR bsFutRoot;
			m_pPos->m_spFut->get_FutRootSymbol(&bsFutRoot);
			vtRet = bsFutRoot;
		}break;
	case RPC_FUTURES:
		{
			CComBSTR bsFut;
			m_pPos->m_spFut->get_Symbol(&bsFut);
			vtRet = bsFut;
		}
		break;
	case RPC_FUT_MATURITY:
		{
			DATE dtMaturity = 0.0;
		   m_pPos->m_spFut->get_Maturity(&dtMaturity);
		   vtRet = vt_date(dtMaturity).GetVtDate();
		}break;
	case RPC_FQUOT_UNIT:
		{
			CComBSTR bsFmt;
			m_pPos->m_spFut->get_QuotationUnitName(&bsFmt);
			vtRet = bsFmt;
		}
		break;
	case RPC_FPRICE_FORMAT:
		{
			CComBSTR bsFmt;
			m_pPos->m_spFut->get_QuotePriceFormat(&bsFmt);
			vtRet = bsFmt;
		}
		break;
	case RPC_EXPIRY:
	case RPC_STRIKE:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_BID:
		{
			vtRet = (m_pPos->m_pQuote->m_pPrice->m_dPriceBid > BAD_DOUBLE_VALUE) ?
				_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceBid):
			(bForSorting? _variant_t(0.0): STR_NA);
		}break;
	case RPC_ASK:
		{
			vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceAsk > BAD_DOUBLE_VALUE?
				_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceAsk):
			bForSorting? _variant_t(0.0): STR_NA;
		}break;
	case RPC_LAST:
		{
			vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceLast > BAD_DOUBLE_VALUE?
				_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceLast):
			bForSorting? _variant_t(0.0): STR_NA;
		}
		break;
	case RPC_CLOSE:
		vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceClose > BAD_DOUBLE_VALUE? _variant_t( m_pPos->m_pQuote->m_pPrice->m_dPriceClose): bForSorting?_variant_t(0):STR_NA;
		break;
	case RPC_FUT_QTY:
		GetValue( m_pPos->m_nQty, bForSorting, bNegativeFormatting, vtRet );
		break;
	case RPC_UND_POS:
		GetValue( m_pPos->m_nQty*m_pPos->m_pQuote->m_nLotSize, bForSorting, bNegativeFormatting, vtRet );
		break;
	case RPC_BETA_WTD_DELTA_USD:
	case RPC_NET_DELTA:
	case RPC_NET_DELTA_USD:
	case RPC_OPT_QTY:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_PNL_MTM:
		GetValue(m_pPos->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_PNL_THEO:
		GetValue(m_pPos->m_dPnlTheo, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_PNL_EDGE:
		if(m_pPos->m_dPnlTheo > BAD_DOUBLE_VALUE && m_pPos->m_dPnlMtm > BAD_DOUBLE_VALUE)
			GetValue(m_pPos->m_dPnlTheo - m_pPos->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			vtRet = bForSorting?_variant_t(BAD_DOUBLE_VALUE):STR_NA;
		break;
	case RPC_OPT_DELTA:
	case RPC_GAMMA:
	case RPC_NET_GAMMA:
	case RPC_GAMMA_SHARES:
	case RPC_VEGA:
	case RPC_WTD_VEGA:
	case RPC_THETA:
	case RPC_RHO:
	case RPC_VEGA_DELTA:
	case RPC_VEGA_GAMMA:
	case RPC_THETA_DELTA:
	case RPC_THETA_GAMMA:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_UND:
		vtRet = m_pUnd->m_bstrSymbol;
		break;
	case RPC_DEL_UNIT:
		vtRet = _variant_t(m_pPos->m_pQuote->m_nLotSize);
		break;
	case RPC_TIME_VALUE:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_IMPORT_ID:
		vtRet = _vtEmpty;
		break;
	case RPC_NETCHANGE:
		GetValue(m_pPos->m_pQuote->m_pPrice->m_dNetChange, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_NET_EXPOSURE:
		GetValue( m_pPos->m_dNetExposure, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_OPT_DELTA_USD:
		GetValue( m_pPos->m_dDeltaEq , bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_THEO_PRICE_VALUE:
		if ( m_pSynthGreeks == NULL )
		{
			GetValue( m_pPos->m_pQuote->m_dPriceTheo , bForSorting, bNegativeFormatting, lRound, vtRet);
		}
		else vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	default:
	//case RPC_DELTAP:
	//case RPC_GAMMAP:
	//case RPC_VEGAP:
	//case RPC_THETAP:
	//case RPC_RHOP:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	//case RPC_MIV:
	//	vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
	//	break;
	//case RPC_MIV_CALC_DATE:
	//	vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
	//	break;
	//case RPC_EXT_POSITION:
	//	GetValue(m_pPos->m_lExternalPosition, bForSorting, bNegativeFormatting, vtRet);
	//	break;
	//case RPC_DISTANSE_TO_STRIKE:
	//	{
	//		double fDist  = 0.0;
	//		double dPrice = 0.0;
	//		EtsReplacePriceStatusEnum enStatus; 

	//		dPrice = m_pUnd->m_spUndPriceProfile->GetUndPriceMid(m_pUnd->m_pPrice->m_dPriceBid, m_pUnd->m_pPrice->m_dPriceAsk, m_pUnd->m_pPrice->m_dPriceLast, m_dTolerance, m_enPriceRoundingRule, &enStatus, VARIANT_FALSE);
	//		m_pPos->DistanceToStrike(dPrice, &fDist);
	//		GetValue( fDist, bForSorting, bNegativeFormatting, lRound, vtRet);
	//	}
	//	break;
	}   
	return utils::HasValue(vtRet);}

bool CMmRvRowData::GetFutOptionField(RisksPosColumnEnum enCol, _variant_t& vtRet, bool bForSorting, bool bNegativeFormatting, long lRound)
{
	vtRet = vtMissing;

	switch(enCol)
	{
	case RPC_SYMBOL:
		vtRet = m_pPos->m_bstrSymbol;
		break;
	case RPC_OPT_TYPE:
		vtRet = m_pPos->m_enOptType == enOtCall? _vtCall: _vtPut;
		break;
	case RPC_FUT_ROOT:
		{
			CComBSTR bsFutRoot;
			m_pPos->m_spFut->get_FutRootSymbol(&bsFutRoot);
			vtRet = bsFutRoot;
		}break;
	case RPC_FUTURES:
		{
			CComBSTR bsFut;
			m_pPos->m_spFut->get_Symbol(&bsFut);
			vtRet = bsFut;
		}
		break;
	case RPC_FUT_MATURITY:
		{
			DATE dtMaturity = 0.0;
			m_pPos->m_spFut->get_Maturity(&dtMaturity);
			vtRet = vt_date(dtMaturity).GetVtDate();
		}break;
	case RPC_EXPIRY:
		vtRet = EgLib::vt_date(m_pPos->m_dtExpiry).GetVtDate();
		break;
	case RPC_STRIKE:
		{
			vtRet = m_pPos->m_dStrike>BAD_DOUBLE_VALUE ?
				_variant_t(m_pPos->m_dStrike):
			( bForSorting ?
				_variant_t(0.0):
			_vtEmpty         
				);
		}break;
	case RPC_BID:
		{
			vtRet = (m_pPos->m_pQuote->m_pPrice->m_dPriceBid > BAD_DOUBLE_VALUE) ?
				_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceBid):
			(bForSorting? _variant_t(0.0): STR_NA);
		}break;
	case RPC_ASK:
		{
			vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceAsk > BAD_DOUBLE_VALUE?
				_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceAsk):
			bForSorting? _variant_t(0.0): STR_NA;
		}break;
	case RPC_ACTIVEPRC:
		{
			vtRet = m_pPos->m_pQuote->m_pPrice->m_dActivePrice > BAD_DOUBLE_VALUE?
				_variant_t(m_pPos->m_pQuote->m_pPrice->m_dActivePrice):
			bForSorting? _variant_t(0.0): STR_NA;
		}break;
	case RPC_LAST:
		{
			vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceLast > BAD_DOUBLE_VALUE?
				_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceLast):
			bForSorting? _variant_t(0.0): STR_NA;
		}
		break;
	case RPC_UND_POS:
		vtRet = bForSorting?_variant_t((long)BAD_LONG_VALUE) :_vtEmpty;
		break;
	case RPC_BETA_WTD_DELTA_USD:
	case RPC_FUT_QTY:
	case RPC_NET_DELTA:
	case RPC_NET_DELTA_USD:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_FQUOT_UNIT:
		if ( m_pPos && m_pPos->m_spFut ) {
			CComBSTR bsFmt;
			m_pPos->m_spFut->get_QuotationUnitName(&bsFmt);
			vtRet = bsFmt;
		}
		else
			vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_FPRICE_FORMAT:
		if ( m_pPos && m_pPos->m_spFut ) {
			CComBSTR bsFmt;
			m_pPos->m_spFut->get_QuotePriceFormat(&bsFmt);
			vtRet = bsFmt;
		}
		else
			vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_OPT_QTY:
		GetValue(m_pPos->m_nQty, bForSorting, bNegativeFormatting, vtRet);
		break;
	case RPC_PNL_MTM:
		GetValue(m_pPos->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_PNL_THEO:
		GetValue(m_pPos->m_dPnlTheo, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_PNL_EDGE:
		if(m_pPos->m_dPnlTheo > BAD_DOUBLE_VALUE && m_pPos->m_dPnlMtm > BAD_DOUBLE_VALUE)
			GetValue(m_pPos->m_dPnlTheo - m_pPos->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			vtRet = bForSorting?_variant_t(BAD_DOUBLE_VALUE):STR_NA;
		break;
	case RPC_OPT_DELTA:
		GetValue(m_pPos->m_dDeltaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_GAMMA:
		GetValue(m_pPos->m_dGammaInSharesPerc, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_NET_GAMMA:
		GetValue(m_pPos->m_dNetGamma, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_GAMMA_SHARES:
		GetValue(m_pPos->m_dGammaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_VEGA:
		GetValue(m_pPos->m_dVegaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_WTD_VEGA:
		GetValue(m_pPos->m_dWtdVega, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_THETA:
		GetValue(m_pPos->m_dThetaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_RHO:
		GetValue(m_pPos->m_dRhoInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_VEGA_DELTA:
		GetValue(m_pPos->m_dVegaDeltaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_VEGA_GAMMA:
		GetValue(m_pPos->m_dVegaGammaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_THETA_DELTA:
		GetValue(m_pPos->m_dThetaDeltaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_THETA_GAMMA:
		GetValue(m_pPos->m_dThetaGammaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_UND:
		vtRet = m_pUnd->m_bstrSymbol;
		break;
	case RPC_DEL_UNIT:
		vtRet = _variant_t(m_pPos->m_pQuote->m_nLotSize);
		break;
	case RPC_TIME_VALUE:
		GetValue(m_pPos->m_dTimeValue, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_CLOSE:
		vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceClose > BAD_DOUBLE_VALUE? _variant_t( m_pPos->m_pQuote->m_pPrice->m_dPriceClose): bForSorting?_variant_t(0):STR_NA;
		break;
	case RPC_IMPORT_ID:
		vtRet = _variant_t(m_pPos->m_bstrImportId);
		break;
	case RPC_NETCHANGE:
		if ( m_pPos->m_pQuote->m_pPrice->m_dNetChange > BAD_DOUBLE_VALUE  )
			vtRet =  m_pPos->m_pQuote->m_pPrice->m_dNetChange;
		else		
			vtRet = bForSorting ? _variant_t(0.0) : STR_NA;
		break;
	case RPC_DELTAP:
		GetValue(m_pPos->m_pQuote->m_dDelta*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_GAMMAP:
		GetValue(m_pPos->m_pQuote->m_dGamma*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_VEGAP:
		GetValue(m_pPos->m_pQuote->m_dVega*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_THETAP:
		GetValue(m_pPos->m_pQuote->m_dTheta*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_RHOP:
		GetValue(m_pPos->m_pQuote->m_dRho*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_NET_EXPOSURE:
		{
			vtRet = m_pPos->m_dNetExposure > BAD_DOUBLE_VALUE && m_pPos->m_dNetExposure != 0.0?
				_variant_t(m_pPos->m_dNetExposure):
			bForSorting? _variant_t(0.0): STR_NA;
		}break;
	case RPC_OPT_DELTA_USD:
		{
			vtRet = m_pPos->m_dDeltaEq > BAD_DOUBLE_VALUE && m_pPos->m_dDeltaEq != 0.0?
				_variant_t(m_pPos->m_dDeltaEq):
			bForSorting? _variant_t(0.0): STR_NA;
		}break;
	case RPC_THEO_PRICE_VALUE:
		if ( m_pSynthGreeks == NULL )
		{
			GetValue(m_pPos->m_pQuote->m_dPriceTheo, bForSorting, bNegativeFormatting, lRound, vtRet);
		}
		else	vtRet = bForSorting?_variant_t(0.0):_vtEmpty;	
		break;
	case RPC_THEO_VOL:
		{
			if ( m_pSynthGreeks )
				GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
			else
				GetValue(m_pPos->m_pQuote->m_dVola*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		}break;
	//case RPC_DELTAP:
	//	GetValue(m_pPos->m_pQuote->m_dDelta, bForSorting, bNegativeFormatting, lRound, vtRet);
	//	break;
	//case RPC_GAMMAP:
	//	GetValue(m_pPos->m_pQuote->m_dGamma, bForSorting, bNegativeFormatting, lRound, vtRet);
	//	break;
	//case RPC_VEGAP:
	//	GetValue(m_pPos->m_pQuote->m_dVega, bForSorting, bNegativeFormatting, lRound, vtRet);
	//	break;
	//case RPC_THETAP:
	//	GetValue(m_pPos->m_pQuote->m_dTheta, bForSorting, bNegativeFormatting, lRound, vtRet);
	//	break;
	//case RPC_RHOP:
	//	GetValue(m_pPos->m_pQuote->m_dRho, bForSorting, bNegativeFormatting, lRound, vtRet);
	//	break;
	//case RPC_MIV:
	//	vtRet = bForSorting?_variant_t(0.0):_variant_t(L"Add");
	//	break;
	//case RPC_MIV_CALC_DATE:
	//	vtRet = bForSorting?_variant_t(0.0):_variant_t(L"Add");
	//	break;
	//case RPC_EXT_POSITION:
	//	GetValue(m_pPos->m_lExternalPosition, bForSorting, bNegativeFormatting, vtRet);
	//	break;
	//case RPC_DISTANSE_TO_STRIKE:
	//	{
	//		double fDist  = 0.0;
	//		double dPrice = 0.0;
	//		EtsReplacePriceStatusEnum enStatus; 

	//		dPrice = m_pUnd->m_spUndPriceProfile->GetUndPriceMid(m_pUnd->m_pPrice->m_dPriceBid, m_pUnd->m_pPrice->m_dPriceAsk, m_pUnd->m_pPrice->m_dPriceLast, m_dTolerance, m_enPriceRoundingRule, &enStatus, VARIANT_FALSE);
	//		m_pPos->DistanceToStrike(dPrice, &fDist);
	//		GetValue( fDist, bForSorting, bNegativeFormatting, lRound, vtRet);
	//	}
	//	break;
	}   
	return utils::HasValue(vtRet);}

bool CMmRvRowData::GetOptionField(RisksPosColumnEnum enCol, _variant_t& vtRet, bool bForSorting, bool bNegativeFormatting, long lRound)
{
	vtRet = vtMissing;

	switch(enCol)
	{
	case RPC_SYMBOL:
		{	
			vtRet = m_pPos->m_bstrSymbol;
		}break;
	case RPC_OPT_TYPE:
		vtRet = m_pPos->m_enOptType == enOtCall? _vtCall: _vtPut;
		break;
	case RPC_EXPIRY:
		vtRet = EgLib::vt_date(m_pPos->m_dtExpiry).GetVtDate();
		break;
	case RPC_STRIKE:
		{
			vtRet = m_pPos->m_dStrike>BAD_DOUBLE_VALUE ?
				_variant_t(m_pPos->m_dStrike):
			( bForSorting ?
				_variant_t(0.0):
			_vtEmpty         
				);
		}break;
	case RPC_BID:
		{
			if ( m_pSynthGreeks && m_pSynthGreeks->m_pSuPrice) {
				vtRet = /*(m_pSynthGreeks->m_pSuPrice->m_dPriceBid > BAD_DOUBLE_VALUE) ?
					_variant_t(m_pSynthGreeks->m_pSuPrice->m_dPriceBid):*/ (bForSorting? _variant_t(0.0): STR_NA);
			}
			else{
				vtRet = (m_pPos->m_pQuote->m_pPrice->m_dPriceBid > BAD_DOUBLE_VALUE) ?
												_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceBid):(bForSorting? _variant_t(0.0): STR_NA);
			}
		}break;
	case RPC_ASK:
		{
			if ( m_pSynthGreeks && m_pSynthGreeks->m_pSuPrice) {
				vtRet = /*m_pSynthGreeks->m_pSuPrice->m_dPriceAsk > BAD_DOUBLE_VALUE?
					_variant_t(m_pSynthGreeks->m_pSuPrice->m_dPriceAsk):*/ bForSorting? _variant_t(0.0): STR_NA;
			}
			else{
				vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceAsk > BAD_DOUBLE_VALUE?
					_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceAsk):bForSorting? _variant_t(0.0): STR_NA;
			}
		}break;
	case RPC_ACTIVEPRC:
		{
			if (m_pSynthGreeks && m_pSynthGreeks->m_pSuPrice ){
				vtRet = /*m_pSynthGreeks->m_pSuPrice->m_dPriceLast > BAD_DOUBLE_VALUE?
					_variant_t(m_pSynthGreeks->m_pSuPrice->m_dPriceLast):*/	bForSorting? _variant_t(0.0): STR_NA;
			}
			else{
				vtRet = m_pPos->m_pQuote->m_pPrice->m_dActivePrice > BAD_DOUBLE_VALUE?
					_variant_t(m_pPos->m_pQuote->m_pPrice->m_dActivePrice):	bForSorting? _variant_t(0.0): STR_NA;
			}
		}break;

	case RPC_LAST:
		{
			if ( m_pSynthGreeks && m_pSynthGreeks->m_pSuPrice ) {
				vtRet = /*m_pSynthGreeks->m_pSuPrice->m_dPriceLast > BAD_DOUBLE_VALUE?
					_variant_t(m_pSynthGreeks->m_pSuPrice->m_dPriceLast):*/	bForSorting? _variant_t(0.0): STR_NA;
			}
			else{
				vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceLast > BAD_DOUBLE_VALUE?
					_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceLast):	bForSorting? _variant_t(0.0): STR_NA;
			}
		}
		break;
	case RPC_NET_EXPOSURE:
		{
			if ( m_pSynthGreeks )
			{
				vtRet = m_pSynthGreeks->m_dNetExposure > BAD_DOUBLE_VALUE && m_pSynthGreeks->m_dNetExposure!=0.0?
				_variant_t(m_pSynthGreeks->m_dNetExposure):
				bForSorting? _variant_t(0.0): STR_NA;
			}
			else
			{
				vtRet = m_pPos->m_dNetExposure > BAD_DOUBLE_VALUE && m_pPos->m_dNetExposure!=0.0?
					_variant_t(m_pPos->m_dNetExposure):
				bForSorting? _variant_t(0.0): STR_NA;
			}
		}break;
	case RPC_OPT_DELTA_USD:
		if (m_pSynthGreeks)
			GetValue(m_pSynthGreeks->m_dDeltaInMoney, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dDeltaEq, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_THEO_PRICE_VALUE:
		if ( m_pSynthGreeks == NULL )
		{
			GetValue(m_pPos->m_pQuote->m_dPriceTheo, bForSorting, bNegativeFormatting, lRound, vtRet);
		}
		else	vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_FUT_ROOT:
	case RPC_FUTURES:
		vtRet = _vtEmpty;
		break;
	case RPC_UND_POS:
		vtRet = bForSorting?_variant_t((long)BAD_LONG_VALUE) :_vtEmpty;
		break;
	case RPC_BETA_WTD_DELTA_USD:
	case RPC_FUT_QTY:
	case RPC_NET_DELTA_USD:
	case RPC_NET_DELTA:
	case RPC_FUT_MATURITY:
	case RPC_FQUOT_UNIT:
	case RPC_FPRICE_FORMAT:
		vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
/*
	case RPC_NET_DELTA:
		if (!m_pSynthGreeks)
			GetValue(m_pPos->m_dNetDelta , bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pSynthGreeks->m_dNetDelta, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;*/

	case RPC_OPT_QTY:
		if ( !m_pSynthGreeks )
			GetValue(m_pPos->m_nQty, bForSorting, bNegativeFormatting, vtRet);
		else
			vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_PNL_MTM:
		if ( !m_pSynthGreeks )
			GetValue(m_pPos->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_PNL_THEO:
		if ( !m_pSynthGreeks )
			GetValue(m_pPos->m_dPnlTheo, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_PNL_EDGE:
		if ( !m_pSynthGreeks ){
			if(m_pPos->m_dPnlTheo > BAD_DOUBLE_VALUE && m_pPos->m_dPnlMtm > BAD_DOUBLE_VALUE)
				GetValue(m_pPos->m_dPnlTheo - m_pPos->m_dPnlMtm, bForSorting, bNegativeFormatting, lRound, vtRet);
			else
				vtRet = bForSorting?_variant_t(BAD_DOUBLE_VALUE):STR_NA;
		}
		else
			vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
		break;
	case RPC_OPT_DELTA:
		if ( m_pSynthGreeks )
			GetValue(m_pSynthGreeks->m_dDeltaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dDeltaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_GAMMA:
		if ( m_pSynthGreeks )
			GetValue(m_pSynthGreeks->m_dGammaInSharesPerc, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dGammaInSharesPerc, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_NET_GAMMA:
		if ( m_pSynthGreeks )
			GetValue(m_pSynthGreeks->m_dNetGamma, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dNetGamma, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_GAMMA_SHARES:
		if ( m_pSynthGreeks )
			GetValue(m_pSynthGreeks->m_dGammaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dGammaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_VEGA:
		if ( m_pSynthGreeks )
			GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dVegaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_WTD_VEGA:
		if ( m_pSynthGreeks )
			GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dWtdVega, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_THETA:
		if ( m_pSynthGreeks )
			GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dThetaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_RHO:
		if ( m_pSynthGreeks )
			GetValue(BAD_DOUBLE_VALUE/*m_pSynthGreeks->m_dRhoInShares*/, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dRhoInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_VEGA_DELTA:
		if ( m_pSynthGreeks )
			GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dVegaDeltaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_VEGA_GAMMA:
		if ( m_pSynthGreeks )
			GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dVegaGammaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_THETA_DELTA:
		if ( m_pSynthGreeks )
			GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dThetaDeltaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_THETA_GAMMA:
		if ( m_pSynthGreeks )
			GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dThetaGammaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_UND:
		{
			if ( m_pSynthGreeks ) {
				// synthetic position
				vtRet = m_pSynthGreeks->m_bstrSynthUndSymbol;
			}
			else
				vtRet = m_pUnd->m_bstrSymbol;
		}break;
	case RPC_DEL_UNIT:
		{
			if(m_pPos->m_bIsSynthetic==VARIANT_FALSE)
				vtRet = _variant_t(m_pPos->m_pQuote->m_nLotSize);
			else
			{
				ISynthRootAtomPtr spSynthAtom;
				ISynthRootCompAtomPtr spSRComp;
				m_pUnd->m_spSynthRoots->get_Item(m_pPos->m_nOptionRootID, &spSynthAtom);

				if( spSynthAtom!=NULL )
				{
					if ( m_pSynthGreeks )
					{
						long nSynthUndID;
						m_pSynthGreeks->get_SynthUndID(&nSynthUndID);
						spSRComp = spSynthAtom->SynthRootComponents->Item[nSynthUndID];

						if (spSRComp != NULL)
						{
							vtRet = _variant_t(spSRComp->Weight * m_pPos->m_pQuote->m_nLotSize);
						}
						else if ( nSynthUndID==0 )
						{
							DOUBLE dCashValue = spSynthAtom->CashValue;
							vtRet = _variant_t(dCashValue * m_pPos->m_pQuote->m_nLotSize);
						}

					}
					else
					{
						spSRComp = spSynthAtom->SynthRootComponents->Item[m_pUnd->m_nID];
						vtRet = _variant_t(spSRComp->Weight * m_pPos->m_pQuote->m_nLotSize);
					}

					//vtRet = _variant_t(spSynthAtom->SynthRootComponents->Item[m_pUnd->m_nID]->Weight * m_pPos->m_pQuote->m_nLotSize);
				}
				else
					vtRet = bForSorting?_variant_t(0.0):_vtEmpty;
			}
		}break;
	case RPC_TIME_VALUE:
		if ( m_pSynthGreeks )
			GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
		else
			GetValue(m_pPos->m_dTimeValue, bForSorting, bNegativeFormatting, lRound, vtRet);
		break;
	case RPC_CLOSE:
		{
			if ( m_pSynthGreeks && m_pSynthGreeks->m_pSuPrice) {
				vtRet = m_pSynthGreeks->m_pSuPrice->m_dPriceClose > BAD_DOUBLE_VALUE?
					_variant_t(m_pSynthGreeks->m_pSuPrice->m_dPriceClose):bForSorting? _variant_t(0.0): STR_NA;
			}
			else{
				vtRet = m_pPos->m_pQuote->m_pPrice->m_dPriceClose > BAD_DOUBLE_VALUE?
					_variant_t(m_pPos->m_pQuote->m_pPrice->m_dPriceClose):bForSorting? _variant_t(0.0): STR_NA;
			}
		}break;
	case RPC_IMPORT_ID:
		{
			vtRet = m_pPos->m_bstrImportId;
		}break;
	case RPC_NETCHANGE:
		{
			if(m_pPos->m_pQuote->m_pPrice->m_dNetChange > BAD_DOUBLE_VALUE)
				vtRet = _variant_t(m_pPos->m_pQuote->m_pPrice->m_dNetChange);
			else
				vtRet =  bForSorting? _variant_t(0.0) : STR_NA;
		}break;
	case RPC_DELTAP:
		{
			if ( m_pSynthGreeks )
				GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
			else
				GetValue(m_pPos->m_pQuote->m_dDelta*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		}break;
	case RPC_GAMMAP:
		{
			if ( m_pSynthGreeks )
				GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
			else
				GetValue(m_pPos->m_pQuote->m_dGamma*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		}break;
	case RPC_VEGAP:
		{
			if ( m_pSynthGreeks )
				GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
			else
				GetValue(m_pPos->m_pQuote->m_dVega*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		}break;
	case RPC_THETAP:
		{
			if ( m_pSynthGreeks )
				GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
			else
				GetValue(m_pPos->m_pQuote->m_dTheta*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		}break;
	case RPC_RHOP:
		{
			if ( m_pSynthGreeks )
				GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
			else
				GetValue(m_pPos->m_pQuote->m_dRho*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		}break;
	case RPC_THEO_VOL:
		{
			if ( m_pSynthGreeks )
				GetValue(BAD_DOUBLE_VALUE, bForSorting, bNegativeFormatting, lRound, vtRet);
			else
				GetValue(m_pPos->m_pQuote->m_dVola*100., bForSorting, bNegativeFormatting, lRound, vtRet);
		}break;
	/*case RPC_MIV:
		{
			vtRet = bForSorting?_variant_t(0.0):_variant_t(L"Add");
		}break;
	case RPC_MIV_CALC_DATE:
		{
			vtRet = bForSorting?_variant_t(0.0):_variant_t(L"Add");
		}break;
	case RPC_EXT_POSITION:
		GetValue(m_pPos->m_lExternalPosition, bForSorting, bNegativeFormatting, vtRet);
		break;
	case RPC_DISTANSE_TO_STRIKE:
		{
			double fDist  = 0.0;
			double dPrice = 0.0;
			EtsReplacePriceStatusEnum enStatus; 

			dPrice = m_pUnd->m_spUndPriceProfile->GetUndPriceMid(m_pUnd->m_pPrice->m_dPriceBid, m_pUnd->m_pPrice->m_dPriceAsk, m_pUnd->m_pPrice->m_dPriceLast, m_dTolerance, m_enPriceRoundingRule, &enStatus, VARIANT_FALSE);
			m_pPos->DistanceToStrike(dPrice, &fDist);
			GetValue( fDist, bForSorting, bNegativeFormatting, lRound, vtRet);
		}
		break;*/
	}   
	return utils::HasValue(vtRet);
}

bool CMmRvRowData::GetAggregationField(RisksPosColumnEnum enCol, _variant_t& vtRet, bool bForSorting, bool bNegativeFormatting, long lRound){
	vtRet = vtMissing;
	CMmRvAggData *pAgg = NULL;
	if ( m_pAgg) 
		pAgg = m_pAgg.get();
	else if( m_pUnd && m_Type == RDT_UNDAGG )
		pAgg = static_cast<CMmRvAggData*>(m_pUnd);
	if (!pAgg){
		vtRet = bForSorting ? _variant_t(0.) : STR_NA;
		return utils::HasValue(vtRet);
	}

	switch( enCol ) {
		case RPC_SYMBOL:
			{
				vtRet = pAgg->Name_;
				break;
			}
		case RPC_UND:
			{
				if ( m_pUnd )
					vtRet = m_pUnd->m_bstrSymbol;
				else
					vtRet = bForSorting ? _variant_t(0.) : STR_NA;
				break;
			}
		case RPC_BETA_WTD_DELTA_USD:
			{
				if (m_pSynthGreeks)
					GetValue(m_pSynthGreeks->m_dBetaWtdDeltaInMoney, bForSorting, bNegativeFormatting, lRound, vtRet);
				else
					GetValue( pAgg->BetaWtdDelta$_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_NET_DELTA:
			{
				if (m_pSynthGreeks)
					GetValue(m_pSynthGreeks->m_dNetDelta, bForSorting, bNegativeFormatting, lRound, vtRet);
				else
					GetValue( pAgg->NetDlt_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_NET_DELTA_USD:
			{
				if (m_pSynthGreeks)
					GetValue( m_pSynthGreeks->m_dDeltaInMoney, bForSorting, bNegativeFormatting, lRound, vtRet);
				else
					GetValue( pAgg->NetDlt$_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_OPT_DELTA:
			{
				if ( m_pSynthGreeks )
					GetValue( m_pSynthGreeks->m_dDeltaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
				else
					GetValue( pAgg->OptDlt_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_NET_GAMMA:
			{
				if (m_pSynthGreeks)
					GetValue( m_pSynthGreeks->m_dNetGamma, bForSorting, bNegativeFormatting, lRound, vtRet);
				else
					GetValue( pAgg->NetGma$_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_GAMMA:
			{
				if (m_pSynthGreeks)
					GetValue( m_pSynthGreeks->m_dGammaInSharesPerc , bForSorting, bNegativeFormatting, lRound, vtRet);
				else
					GetValue( pAgg->Gma1P_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_GAMMA_SHARES:
			{
				if (m_pSynthGreeks)
					GetValue( m_pSynthGreeks->m_dGammaInShares, bForSorting, bNegativeFormatting, lRound, vtRet);
				else
					GetValue( pAgg->Gma1$_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_UND_POS:
			{
				if ( pAgg->Type_ == CMmRvAggData::enUndAgg && pAgg->pUnd_ && pAgg->pUnd_->m_enContractType == enCtFutUnd ) 
					vtRet = bForSorting ? _variant_t(0L) : STR_NA;
				else
					GetValue( pAgg->UndPos_, bForSorting, bNegativeFormatting, vtRet);
			}
			break;
		case RPC_OPT_QTY:
			{
				if (m_pSynthGreeks)
					GetValue(BAD_LONG_VALUE, bForSorting, bNegativeFormatting, vtRet);
				else
					GetValue(pAgg->OptQty_, bForSorting, bNegativeFormatting, vtRet);
			}
			break;
		case RPC_FUT_QTY:
			{
				GetValue(pAgg->FutQty_, bForSorting, bNegativeFormatting, vtRet);
			}
			break;
		case RPC_PNL_MTM:
			{
				GetValue( pAgg->PnlMTM_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_PNL_THEO:
			{
				GetValue( pAgg->PnLTheo_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_PNL_EDGE:
			{
				GetValue( pAgg->PnlEdge_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_ASK:
			{
				if ( pAgg->Type_ == CMmRvAggData::enFutAgg ) {
					if ( pAgg->pFut_ ) 
						GetValue( pAgg->pFut_->m_pPrice->m_dPriceAsk, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else if (pAgg->Type_ == CMmRvAggData::enUndAgg ) {
					if (pAgg->pUnd_ && pAgg->pUnd_->m_pPrice)
						if(pAgg->pUnd_->m_enContractType == enCtFutUnd)
							vtRet = bForSorting ? _variant_t(0.) : STR_NA;
						else
							GetValue( pAgg->pUnd_->m_pPrice->m_dPriceAsk, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else
					vtRet = bForSorting ? _variant_t(0.) : STR_NA;
			}
			break;
		case RPC_BID:
			{
				if ( pAgg->Type_ == CMmRvAggData::enFutAgg ) {
					if ( pAgg->pFut_ ) 
						GetValue( pAgg->pFut_->m_pPrice->m_dPriceBid, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else if (pAgg->Type_ == CMmRvAggData::enUndAgg ) {
					if (pAgg->pUnd_ && pAgg->pUnd_->m_pPrice)
						if(pAgg->pUnd_->m_enContractType == enCtFutUnd)
							vtRet = bForSorting ? _variant_t(0.) : STR_NA;
						else
							GetValue( pAgg->pUnd_->m_pPrice->m_dPriceBid, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else
					vtRet = bForSorting ? _variant_t(0.) : STR_NA;
			}
			break;
		case RPC_CLOSE:
			{
				if ( pAgg->Type_ == CMmRvAggData::enFutAgg ) {
					if ( pAgg->pFut_ ) 
						GetValue( pAgg->pFut_->m_pPrice->m_dPriceClose, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else if (pAgg->Type_ == CMmRvAggData::enUndAgg ) {
					if (pAgg->pUnd_ && pAgg->pUnd_->m_pPrice) 
						if(pAgg->pUnd_->m_enContractType == enCtFutUnd)
							vtRet = bForSorting ? _variant_t(0.) : STR_NA;
						else
							GetValue( pAgg->pUnd_->m_pPrice->m_dPriceClose, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else
					vtRet = bForSorting ? _variant_t(0.) : STR_NA;
			}
			break;
		case RPC_LAST:
			{
				if ( pAgg->Type_ == CMmRvAggData::enFutAgg ) {
					if ( pAgg->pFut_ ) 
						GetValue( pAgg->pFut_->m_pPrice->m_dPriceLast, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else if (pAgg->Type_ == CMmRvAggData::enUndAgg ) {
					if (pAgg->pUnd_ && pAgg->pUnd_->m_pPrice)
						if(pAgg->pUnd_->m_enContractType == enCtFutUnd)
							vtRet = bForSorting ? _variant_t(0.) : STR_NA;
						else
							GetValue( pAgg->pUnd_->m_pPrice->m_dPriceLast, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else
					vtRet = bForSorting ? _variant_t(0.) : STR_NA;
			}
			break;
		case RPC_ACTIVEPRC:
			{
				if ( pAgg->Type_ == CMmRvAggData::enFutAgg ) {
					if ( pAgg->pFut_ ) 
						GetValue( pAgg->pFut_->m_pPrice->m_dActivePrice, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else if (pAgg->Type_ == CMmRvAggData::enUndAgg ) {
					if (pAgg->pUnd_ && pAgg->pUnd_->m_pPrice)
						if(pAgg->pUnd_->m_enContractType == enCtFutUnd)
							vtRet = bForSorting ? _variant_t(0.) : STR_NA;
						else
							GetValue( pAgg->pUnd_->m_pPrice->m_dActivePrice, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else
					vtRet = bForSorting ? _variant_t(0.) : STR_NA;
			}break;
		case RPC_NETCHANGE:
			{
				if ( pAgg->Type_ == CMmRvAggData::enFutAgg ) {
					if ( pAgg->pFut_ ) 
						GetValue( pAgg->pFut_->m_pPrice->m_dNetChange, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else if (pAgg->Type_ == CMmRvAggData::enUndAgg ) {
					if (pAgg->pUnd_ && pAgg->pUnd_->m_pPrice)
						if(pAgg->pUnd_->m_enContractType == enCtFutUnd)
							vtRet = bForSorting ? _variant_t(0.) : STR_NA;
						else
							GetValue( pAgg->pUnd_->m_pPrice->m_dNetChange, bForSorting, bNegativeFormatting, lRound, vtRet);
				}
				else
					vtRet = bForSorting ? _variant_t(0.) : STR_NA;
			}break;
		case RPC_VEGA:
			{
				GetValue( pAgg->Vga$_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_WTD_VEGA:
			{
				GetValue( pAgg->WtdVga$_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_VEGA_GAMMA:
			{
				GetValue( pAgg->VgaGma_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_VEGA_DELTA:
			{
				GetValue( pAgg->VgaDlt_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_THETA:
			{
				GetValue( pAgg->Tht$_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_THETA_DELTA:
			{
				GetValue( pAgg->ThtDlt_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_THETA_GAMMA:
			{
				GetValue( pAgg->ThtGma_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_RHO:
			{
				GetValue( pAgg->Rho$_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_TIME_VALUE:
			{
				GetValue( pAgg->TmVal_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}
			break;
		case RPC_NET_EXPOSURE:
			{
				if ( m_pSynthGreeks )
					GetValue( m_pSynthGreeks->m_dNetExposure, bForSorting, bNegativeFormatting, lRound, vtRet);
				else
					GetValue( pAgg->NetExposure_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}break;
		case RPC_OPT_DELTA_USD:
			{
				if ( m_pSynthGreeks )
					GetValue( m_pSynthGreeks->m_dDeltaInMoney, bForSorting, bNegativeFormatting, lRound, vtRet);
				else
					GetValue( pAgg->OptDlt$_, bForSorting, bNegativeFormatting, lRound, vtRet);
			}break;
		default:
			vtRet = bForSorting ? _variant_t(0.) : STR_NA;
	}
	return utils::HasValue(vtRet);
}

STDMETHODIMP CMmRvRowData::GetAggregationTradeSymbolID(LONG* pID){
	if( !pID ) return E_INVALIDARG;
	if (!(m_Type == RDT_UNDAGG || m_Type == RDT_AGG) ) {
		*pID = 0;
		return E_FAIL;
	}

	if (!m_pAgg) {
		*pID = 0;
		return E_FAIL;
	}

	if ( m_pAgg->Type_ == CMmRvAggData::enFutAgg) {
		if ( m_pAgg->pFut_ ) {
			*pID = m_pAgg->pFut_->m_nID;
			return S_OK;
		}
		else if ( m_pAgg->pUnd_ ) {
			*pID = m_pAgg->pUnd_->m_nID;
			return S_OK;
		}
		else{
			*pID = 0;
			return E_FAIL;
		}
	}

	if (m_pAgg->Type_ == CMmRvAggData::enExpAgg) {
		if ( !m_pAgg->Positions_.empty()) {
			*pID = m_pAgg->Positions_[0]->m_nID;
			return S_OK;
		}
		else if ( m_pAgg->pUnd_ ) {
			*pID = m_pAgg->pUnd_->m_nID;
			return S_OK;
		}
		else{
			*pID = 0;
			return E_FAIL;
		}
	}

	if (m_pAgg->Type_ == CMmRvAggData::enUndAgg) {
		if ( m_pAgg->pUnd_ ) {
			*pID = m_pAgg->pUnd_->m_nID;
			return S_OK;
		}
		else{
			*pID = 0;
			return E_FAIL;
		}
	}

	*pID = 0;
	return E_FAIL;

	//if (m_Type != RDT_UNDAGG && m_Type != RDT_AGG ){
	//	*pID = 0;
	//	return E_FAIL;
	//} 

	//if( m_Type == RDT_UNDAGG ){
	//	if ( !m_pUnd ) {
	//		*pID = 0;
	//		return E_FAIL;
	//	}

	//	*pID = m_pUnd->m_nID;
	//	return S_OK;
	//}

	//if ( !m_pAggregation) {
	//	*pID = 0;
	//	return E_FAIL;
	//}

	//if ( m_pAggregation->m_pParent ) {
	//	if(m_pAggregation->m_pParent->m_pFut ){
	//		*pID = m_pAggregation->m_pParent->m_pFut->m_nID;	// expiry aggregation for future
	//		return S_OK;
	//	}
	//	else{
	//		if(!m_pAggregation->m_pParent->m_pUnd){
	//			*pID = 0;
	//			return E_FAIL;
	//		}
	//		else{
	//			*pID = m_pAggregation->m_pParent->m_pUnd->m_nID;
	//			return S_OK;
	//		}
	//	}
	//}
	//else{
	//	if(m_pAggregation->m_pFut ){
	//		*pID = m_pAggregation->m_pFut->m_nID;	// expiry aggregation for future
	//		return S_OK;
	//	}
	//	else{
	//		if(!m_pAggregation->m_pUnd){
	//			*pID = 0;
	//			return E_FAIL;
	//		}
	//		else{
	//			*pID = m_pAggregation->m_pUnd->m_nID;
	//			return S_OK;
	//		}
	//	}
	//}

	//return E_FAIL;
}

STDMETHODIMP CMmRvRowData::GetAggregationPriceReplaceStatus( EtsReplacePriceStatusEnum *pRetVal){
	__CHECK_POINTER( pRetVal );

	if ( !m_pAgg ){
		*pRetVal = enRpsNone;
		return S_OK;
	}

	if (m_pAgg->Type_ == CMmRvAggData::enUndAgg) {
		if (!m_pAgg->pUnd_) {
			*pRetVal = enRpsNone;
			return E_FAIL;
		}
		*pRetVal = m_pAgg->pUnd_->m_enReplacePriceStatus;
		return S_OK;
	}

	if (m_pAgg->Type_ == CMmRvAggData::enFutAgg) {
		if (!m_pAgg->pFut_) {
			*pRetVal = enRpsNone;
			return E_FAIL;
		}
		*pRetVal = m_pAgg->pFut_->m_enReplacePriceStatus;
		return S_OK;
	}

	*pRetVal = enRpsNone;
	return S_OK;

	//if( m_Type == RDT_UNDAGG ){
	//	if ( !m_pUnd ) {
	//		*pRetVal = enRpsNone;
	//		return E_FAIL;
	//	}

	//	*pRetVal = m_pUnd->m_enReplacePriceStatus;
	//	return S_OK;
	//}

	//if ( !m_pAggregation) {
	//	*pRetVal = enRpsNone;
	//	return /*E_FAIL*/S_OK;
	//}


	//if(m_pAggregation->m_pFut ){
	//	*pRetVal = m_pAggregation->m_pFut->m_enReplacePriceStatus;
	//	return S_OK;
	//}
	//else{
	//	if(!m_pAggregation->m_pUnd){
	//		*pRetVal = enRpsNone;
	//		return E_FAIL;
	//	}
	//	else
	//		*pRetVal = enRpsNone; //m_pAggregation->m_pUnd->m_enReplacePriceStatus;
	//}
	//return S_OK;
}

