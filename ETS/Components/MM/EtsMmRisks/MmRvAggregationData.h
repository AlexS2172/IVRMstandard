#pragma once
#include "EtsMmRisks.h"
#include "MmRvPrice.h"
#include <vector>
#include <functional>
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>

class CMmRvPosColl;
class CMmRvUndColl;
class CMmRvUndAtom;
class CRiskViewFieldSort;

_COM_SMARTPTR_TYPEDEF(IMmRvUndColl, IID_IMmRvUndColl); 
_COM_SMARTPTR_TYPEDEF(IMmRvPosAtom, IID_IMmRvPosAtom);

_COM_SMARTPTR_TYPEDEF(IMmRvRowData, IID_IMmRvRowData);

class CMmRvAggData {
	size_t CreateRowsForPositions(CMmRvUndAtom* pUndAtom, long lExpilter, unsigned outlnLvl, 
											const CRiskViewFieldSort *Cmp, std::vector<IMmRvRowDataPtr>& posRows, long& nOptPositions,long& nUndPositions,
											CComObject<CMmRvUndColl>* pUndColl  );
	void CreateRowsForAggregations(CMmRvUndAtom* pUndAtom, long lExpilter, unsigned outlnLvl, const CRiskViewFieldSort *Cmp, std::vector<IMmRvRowDataPtr>& posRows);
	bool CreateRow(CMmRvUndAtom* pUndAtom, unsigned outlnLvl, std::vector<IMmRvRowDataPtr>& aggRows);
public:
	typedef boost::shared_ptr<CMmRvPosAtom>	MmRvPosAtomPtr;
	typedef boost::shared_ptr<CMmRvAggData>	MmRvAggDataPtr;
	typedef std::vector<MmRvPosAtomPtr>		Positions;
	typedef std::vector<MmRvAggDataPtr>		Aggregations;
	
	typedef enum{
		enUndAgg,
		enFutAgg,
		enExpAgg
	} AggregationType;

	_bstr_t				Name_;
	_bstr_t				internalName_;						// used as key in map
	Positions			Positions_;
	Aggregations		Aggregations_;
	AggregationType	Type_;
	CMmRvUndAtom*		pUnd_;
	CMmRvFutAtom*		pFut_;

	LONG					UndPos_, FutQty_, OptQty_;		// underlying position, future quantity and options quantity within aggregation
	double				NetDlt_, NetDlt$_, OptDlt_, OptDlt$_;	// net delta, net delta $, option delta
	double				Gma1P_, NetGma$_, Gma1$_, NetGma_;		// gamma 1 %, net gamma in dollars, gamma in shares & net gamma in dollars
	double				PnLTheo_, PnlMTM_, PnlEdge_;	//
	double				Vga$_, WtdVga$_, VgaGma_, VgaDlt_; //Vega$, WtdVga$, VgaGma, VgaDlt
	double				Tht$_, ThtDlt_, ThtGma_; //Tht$, ThtDlt, ThtGma
	double				Rho$_; //Rho$
	double				TmVal_, TmValInShares_; //TmVal (Time Value)
	double				Beta_;	// beta used in aggregation
	double				BetaWtdDelta$_;
	double				UndPosForRates_;
	double              NetExposure_;
	double              NetExposureSort_;
	double              NetExposureLong_;

	VARIANT_BOOL		BadBetaWtdDelta$_,BadRho$_, BadTht$_, BadThtDlt_, BadThtGma_,BadVga$_, BadWtdVga$_, BadVgaGma_, BadVgaDlt_,
							BadGma1$_, BadGma1P_, BadNetGma$_,BadNetGma_,BadPnlMtm_, BadPnlTheo_, BadNetDelta_, 
							BadOptDelta_, BadNetDlt$_, BadOptDlt$_, BadTmVal_, BadTmValInShares_, BadNetExposure_;
	
	VARIANT_BOOL		m_bIsSyntheticAggregation;	// this left for compatibility - not really used now

	CMmRvAggData( AggregationType Type, const _bstr_t& Name = _bstr_t(L"") ) : 
		Name_(Name)
		,Type_(Type)
		,pUnd_(NULL)
		,pFut_(NULL)
		,UndPos_(BAD_LONG_VALUE)
		,FutQty_(BAD_LONG_VALUE)
		,OptQty_(BAD_LONG_VALUE)
		,NetDlt_(BAD_DOUBLE_VALUE),NetDlt$_(BAD_DOUBLE_VALUE),OptDlt_(BAD_DOUBLE_VALUE), OptDlt$_(BAD_DOUBLE_VALUE)
		,Gma1P_(BAD_DOUBLE_VALUE), NetGma$_(BAD_DOUBLE_VALUE), Gma1$_(BAD_DOUBLE_VALUE), NetGma_(BAD_DOUBLE_VALUE)
		,PnLTheo_(BAD_DOUBLE_VALUE), PnlMTM_(BAD_DOUBLE_VALUE), PnlEdge_(BAD_DOUBLE_VALUE)
		,Vga$_(BAD_DOUBLE_VALUE), WtdVga$_(BAD_DOUBLE_VALUE), VgaGma_(BAD_DOUBLE_VALUE), VgaDlt_(BAD_DOUBLE_VALUE)
		,Tht$_(BAD_DOUBLE_VALUE), ThtDlt_(BAD_DOUBLE_VALUE), ThtGma_(BAD_DOUBLE_VALUE)
		,Rho$_(BAD_DOUBLE_VALUE)
		,TmVal_(BAD_DOUBLE_VALUE), TmValInShares_(BAD_DOUBLE_VALUE)
		,Beta_(BAD_DOUBLE_VALUE)
		,BetaWtdDelta$_(BAD_DOUBLE_VALUE)
		,UndPosForRates_(0)
		,BadPnlMtm_(VARIANT_FALSE), BadPnlTheo_(VARIANT_FALSE)
		,BadNetDelta_(VARIANT_FALSE), BadOptDelta_(VARIANT_FALSE)
		,BadNetDlt$_(VARIANT_FALSE), BadOptDlt$_(VARIANT_FALSE)
		,BadGma1$_(VARIANT_FALSE), BadGma1P_(VARIANT_FALSE), BadNetGma$_(VARIANT_FALSE), BadNetGma_(VARIANT_FALSE)
		,BadVga$_(VARIANT_FALSE), BadWtdVga$_(VARIANT_FALSE), BadVgaGma_(VARIANT_FALSE), BadVgaDlt_(VARIANT_FALSE)
		,BadTht$_(VARIANT_FALSE), BadThtDlt_(VARIANT_FALSE), BadThtGma_(VARIANT_FALSE)
		,BadTmVal_(VARIANT_FALSE),BadTmValInShares_(VARIANT_FALSE)
		,BadRho$_(VARIANT_FALSE)
		,BadBetaWtdDelta$_(VARIANT_FALSE)
		,m_bIsSyntheticAggregation(VARIANT_FALSE)
		,NetExposure_(BAD_DOUBLE_VALUE)
		,BadNetExposure_(VARIANT_FALSE)
		,NetExposureSort_(BAD_DOUBLE_VALUE)
		,NetExposureLong_(BAD_DOUBLE_VALUE)

	{}
	void ClearAggregatedValues(){
		UndPos_= FutQty_= OptQty_ = BAD_LONG_VALUE;
		OptDlt$_ =  NetDlt_= NetDlt$_ = OptDlt_ = Gma1P_= NetGma$_= Gma1$_= NetGma_ =PnLTheo_= PnlMTM_= PnlEdge_=
		Vga$_=  WtdVga$_=  VgaGma_=  VgaDlt_= Tht$_=  ThtDlt_=  ThtGma_= 	Rho$_= TmVal_ = BAD_DOUBLE_VALUE;
		UndPosForRates_ = 0.;
		NetExposure_=BAD_DOUBLE_VALUE;
		BadNetExposure_=VARIANT_FALSE;

		NetExposureSort_ = BAD_DOUBLE_VALUE;
		NetExposureLong_ = BAD_DOUBLE_VALUE;


		BadBetaWtdDelta$_=BadRho$_=BadTmValInShares_=BadTmVal_=BadTht$_= BadThtDlt_=BadThtGma_=BadVga$_= BadWtdVga$_= BadVgaGma_= BadVgaDlt_=BadGma1$_= BadGma1P_= BadNetGma$_= BadNetGma_=BadNetDlt$_ = 
		BadOptDlt$_ = BadPnlMtm_ = BadPnlTheo_ = BadNetDelta_ = BadOptDelta_ = VARIANT_FALSE;
		std::for_each( Aggregations_.begin(), Aggregations_.end(), boost::bind(&CMmRvAggData::ClearAggregatedValues, _1) );
	}
	void CalcNetDeltas(EtsContractTypeEnum underlyingContractType);
	void CreateRows(CMmRvUndAtom* pUndAtom, long lExpiryFilter, unsigned outlineLevel,
							const CRiskViewFieldSort *, std::vector<IMmRvRowDataPtr>& posRows,long& nOptPositions,
							long& nUndPositions,CComObject<CMmRvUndColl>* pUndColl );
	void SetAllValuesAsBad()	{
		BadNetExposure_ = BadBetaWtdDelta$_=BadRho$_=BadTmValInShares_=BadTmVal_=BadTht$_= BadThtDlt_=BadThtGma_=BadVga$_= BadWtdVga$_= BadVgaGma_= BadVgaDlt_=BadGma1$_= BadGma1P_= BadNetGma$_= BadNetDlt$_ = BadOptDlt$_ = 
		BadPnlMtm_ = BadPnlTheo_ = BadNetDelta_ = BadOptDelta_ = VARIANT_TRUE;
	}

	static bool IsAggregationRowVisible( const CMmRvAggData* pAgg);
	bool CheckPositions(long lExpiryFilter);

};

/*
class __MmRvAggregationData
{
public:
	//_bstr_t							m_bstrSymbol;			// name of aggregation
	//DOUBLE							m_dBeta;

	//LONG							m_nQty;
	//LONG							m_nOptQty;		// holds both options and future options
	//DOUBLE							m_dUndPosForRates;
	//LONG							m_nFutQty;

	/*DOUBLE							m_dPnlMtm;
	DOUBLE							m_dPnlTheo;*/

	//double							m_dDeltaP, m_dGammaP, m_dVegaP, m_dThetaP, m_dRhoP;
	//DOUBLE							m_dNetDelta;
	//DOUBLE							m_dOptDelta;
	//DOUBLE							m_dGamma;
	//DOUBLE							m_dGammaPerc;
	//DOUBLE							m_dVega;Vga$_
	//DOUBLE							m_dWtdVega;WtdVga$_
	//DOUBLE							m_dTheta;Tht$_
	//DOUBLE							m_dDeltaEq;
	//DOUBLE							m_dGammaEq;
	//DOUBLE							m_dRho;
	//DOUBLE							m_dThetaDelta;, ThtDlt_, 
	//DOUBLE							m_dThetaGamma;ThtGma_
	//DOUBLE							m_dVegaDelta;VgaDlt_
	//DOUBLE							m_dVegaGamma;VgaGma_
	//DOUBLE							m_dTimeValue;
	//DOUBLE							m_dTimeValueInShares;
	//DOUBLE							m_dBetaWtdDeltaEq;
	//DOUBLE							m_dNetGamma;
	//DOUBLE							m_dOptDeltaEq;
	//double							m_dNetDelta$;
	/*DOUBLE							m_dFutNetDelta;
	DOUBLE							m_dFutOptDelta;
	DOUBLE							m_dFutGamma;
	DOUBLE							m_dFutGammaPerc;
	DOUBLE							m_dFutVega;
	DOUBLE							m_dFutWtdVega;
	DOUBLE							m_dFutTheta;
	DOUBLE							m_dFutDeltaEq;
	DOUBLE							m_dFutGammaEq;
	DOUBLE							m_dFutRho;
	DOUBLE							m_dFutThetaDelta;
	DOUBLE							m_dFutThetaGamma;
	DOUBLE							m_dFutVegaDelta;
	DOUBLE							m_dFutVegaGamma;
	DOUBLE							m_dFutTimeValue;
	DOUBLE							m_dFutTimeValueInShares;
	DOUBLE							m_dFutBetaWtdDeltaEq;
	DOUBLE							m_dFutNetGamma;
	DOUBLE							m_dFutOptDeltaEq;*/
											
	//VARIANT_BOOL					m_bBadOptDeltaEq;
	//VARIANT_BOOL					m_bBadNetGamma;
	//VARIANT_BOOL					m_bBadPnlMtm;
	//VARIANT_BOOL					m_bBadPnlTheo;
	//VARIANT_BOOL					m_bBadNetDelta;
	//VARIANT_BOOL					m_bBadOptDelta;
	//VARIANT_BOOL					m_bBadGamma;
	//VARIANT_BOOL					m_bBadGammaPerc;
	//VARIANT_BOOL					m_bBadVega;
	//VARIANT_BOOL					m_bBadWtdVega;
	//VARIANT_BOOL					m_bBadTheta;
	//VARIANT_BOOL					m_bBadDeltaEq;
	//VARIANT_BOOL					m_bBadGammaEq;
	//VARIANT_BOOL					m_bBadRho;
	//VARIANT_BOOL					m_bBadThetaDelta;
	//VARIANT_BOOL					m_bBadThetaGamma;
	//VARIANT_BOOL					m_bBadVegaDelta;
	//VARIANT_BOOL					m_bBadVegaGamma;
	//VARIANT_BOOL					m_bBadTimeValue;
	//VARIANT_BOOL					m_bBadBetaWtdDeltaEq;

	/*VARIANT_BOOL					m_bBadFutNetDelta;
	VARIANT_BOOL					m_bBadFutOptDelta;
	VARIANT_BOOL					m_bBadFutGamma;
	VARIANT_BOOL					m_bBadFutGammaPerc;
	VARIANT_BOOL					m_bBadFutVega;
	VARIANT_BOOL					m_bBadFutWtdVega;
	VARIANT_BOOL					m_bBadFutTheta;
	VARIANT_BOOL					m_bBadFutDeltaEq;
	VARIANT_BOOL					m_bBadFutGammaEq;
	VARIANT_BOOL					m_bBadFutRho;
	VARIANT_BOOL					m_bBadFutThetaDelta;
	VARIANT_BOOL					m_bBadFutThetaGamma;
	VARIANT_BOOL					m_bBadFutVegaDelta;
	VARIANT_BOOL					m_bBadFutVegaGamma;
	VARIANT_BOOL					m_bBadFutTimeValue;
	VARIANT_BOOL					m_bBadFutTimeValueInShares;
	VARIANT_BOOL					m_bBadFutBetaWtdDeltaEq;
	VARIANT_BOOL					m_bBadFutNetGamma;
	VARIANT_BOOL					m_bBadFutOptDeltaEq;*/

	//EtsReplacePriceStatusEnum		m_enReplacePriceStatus;
	//LONG							m_lExternalPosition;


	//VARIANT_BOOL					m_bIsSyntheticAggregation;

	/*IMmRvPricePtr					m_spPrice;
	CComObject<CMmRvPrice>*		m_pPrice;

	IMmRvPricePtr					m_spSuPrice;
	CComObject<CMmRvPrice>*		m_pSuPrice;*/

	//DATE								m_dtExpiry;
	//DATE								m_dtFutMaturity;

	//IMmRvUndAtomPtr				m_spUnd;
	//CMmRvUndAtom*					m_pUnd;
	//__MmRvAggregationData*		m_pParent;
	//CMmRvFutAtom*					m_pFut;

	//__MmRvAggregationData()
	//	:m_pPrice(NULL)
	//	,m_pSuPrice(NULL)
	//	//,m_bIsSyntheticAggregation(VARIANT_FALSE)
	//	//,m_pUnd(NULL)
	//	//,m_bstrSymbol(L"")
	//	//,m_pParent(NULL)
	//	//,m_pFut(NULL)
	//{
	//	Clear(true, false);
	//}

	//void Clear(bool bErase, bool bClearPrice)
	//{

	//	if(bClearPrice && m_pPrice)
	//		m_pPrice->Clear();

	//	//m_dBeta = BAD_DOUBLE_VALUE;

	//	//m_nQty = BAD_LONG_VALUE;
	//	//m_nOptQty = BAD_LONG_VALUE;
	//	//m_nFutQty = BAD_LONG_VALUE;
	//	//m_dUndPosForRates = 0.;
	//	//m_enReplacePriceStatus = enRpsNone;
	//	//m_lExternalPosition = 0;
	//	//m_dtExpiry = m_dtFutMaturity = static_cast<DATE>(0);
	//	//m_pParent = NULL;
	//	//m_pFut =NULL;
	//	ClearValues();
	//}

	//void ClearValues()
	//{
	//	/*m_nQty = BAD_LONG_VALUE;
	//	m_nOptQty = BAD_LONG_VALUE;
	//	m_nFutQty = BAD_LONG_VALUE;*/
	//	//m_dPnlMtm = BAD_DOUBLE_VALUE;
	//	//m_dPnlTheo = BAD_DOUBLE_VALUE;
	//	//m_dNetDelta = BAD_DOUBLE_VALUE;
	//	//m_dOptDelta = BAD_DOUBLE_VALUE;
	//	//m_dOptDeltaEq = BAD_DOUBLE_VALUE;
	//	//m_dGamma = BAD_DOUBLE_VALUE;
	//	//m_dGammaPerc = BAD_DOUBLE_VALUE;
	//	//m_dVega = BAD_DOUBLE_VALUE;
	//	//m_dWtdVega = BAD_DOUBLE_VALUE;
	//	//m_dTheta = BAD_DOUBLE_VALUE;
	//	//m_dDeltaEq = BAD_DOUBLE_VALUE;
	//	//m_dGammaEq = BAD_DOUBLE_VALUE;
	//	//m_dRho = BAD_DOUBLE_VALUE;
	//	//m_dThetaDelta = BAD_DOUBLE_VALUE;
	//	//m_dThetaGamma = BAD_DOUBLE_VALUE;
	//	//m_dVegaDelta = BAD_DOUBLE_VALUE;
	//	//m_dVegaGamma = BAD_DOUBLE_VALUE;
	//	//m_dTimeValue = BAD_DOUBLE_VALUE;
	//	//m_dTimeValueInShares = BAD_DOUBLE_VALUE;
	//	//m_dBetaWtdDeltaEq = BAD_DOUBLE_VALUE;
	//	//m_dNetGamma = BAD_DOUBLE_VALUE;

	//	//m_dNetDelta$ = BAD_DOUBLE_VALUE;
	///*	m_dFutNetDelta=
	//	m_dFutOptDelta=
	//	m_dFutGamma=
	//	m_dFutGammaPerc=
	//	m_dFutVega=
	//	m_dFutWtdVega=
	//	m_dFutTheta=
	//	m_dFutDeltaEq=
	//	m_dFutGammaEq=
	//	m_dFutRho=
	//	m_dFutThetaDelta=
	//	m_dFutThetaGamma=
	//	m_dFutVegaDelta=
	//	m_dFutVegaGamma=
	//	m_dFutTimeValue=
	//	m_dFutTimeValueInShares=
	//	m_dFutBetaWtdDeltaEq=
	//	m_dFutNetGamma=
	//	m_dFutOptDeltaEq=*/
	//	//m_dDeltaP = m_dGammaP= m_dVegaP= m_dThetaP= m_dRhoP = BAD_DOUBLE_VALUE;

	//	//m_bBadNetGamma = VARIANT_FALSE;
	//	//m_bBadPnlMtm = VARIANT_FALSE;
	//	//m_bBadPnlTheo = VARIANT_FALSE;
	//	//m_bBadNetDelta = VARIANT_FALSE;
	//	//m_bBadOptDelta = VARIANT_FALSE;
	//	//m_bBadGamma = VARIANT_FALSE;
	//	//m_bBadGammaPerc = VARIANT_FALSE;
	//	//m_bBadVega = VARIANT_FALSE;
	//	//m_bBadWtdVega = VARIANT_FALSE;
	//	//m_bBadTheta = VARIANT_FALSE;
	//	//m_bBadDeltaEq = VARIANT_FALSE;
	//	//m_bBadGammaEq = VARIANT_FALSE;
	//	//m_bBadRho = VARIANT_FALSE;
	//	//m_bBadThetaDelta = VARIANT_FALSE;
	//	//m_bBadThetaGamma = VARIANT_FALSE;
	//	//m_bBadVegaDelta = VARIANT_FALSE;
	//	//m_bBadVegaGamma = VARIANT_FALSE;
	//	//m_bBadTimeValue = VARIANT_FALSE;
	//	//m_bBadBetaWtdDeltaEq = VARIANT_FALSE;
	//	//m_bBadOptDeltaEq = VARIANT_FALSE;

	//}
/*
	void SetAllValuesAsBad_()
	{
		m_bBadPnlMtm = VARIANT_TRUE;
		m_bBadPnlTheo = VARIANT_TRUE;
		m_bBadNetDelta = VARIANT_TRUE;
		m_bBadOptDelta = VARIANT_TRUE;
		m_bBadGamma = VARIANT_TRUE;
		m_bBadGammaPerc = VARIANT_TRUE;
		m_bBadVega = VARIANT_TRUE;
		m_bBadWtdVega = VARIANT_TRUE;
		m_bBadTheta = VARIANT_TRUE;
		m_bBadDeltaEq = VARIANT_TRUE;
		m_bBadGammaEq = VARIANT_TRUE;
		m_bBadRho = VARIANT_TRUE;
		m_bBadThetaDelta = VARIANT_TRUE;
		m_bBadThetaGamma = VARIANT_TRUE;
		m_bBadVegaDelta = VARIANT_TRUE;
		m_bBadVegaGamma = VARIANT_TRUE;
		m_bBadTimeValue = VARIANT_TRUE;
		m_bBadWtdVega = VARIANT_TRUE;
		m_bBadBetaWtdDeltaEq = VARIANT_TRUE;
		m_bBadNetGamma = VARIANT_TRUE;

	}

// public:
// 	void Calc(
// 		CMmRvPosColl*		 pPosColl,
// 		CMmRvUndColl*		 pUndColl,
// 		CMmRvUndAtom*		 pIdx,
// 		VARIANT_BOOL		 bIsPnlLTD,
// 		EtsCalcModelTypeEnum enCalcModel,
// 		VARIANT_BOOL		 bUseTheoVolatility,
// 		VARIANT_BOOL		 bUseTheoVolaNoBid,
// 		VARIANT_BOOL	     bUseTheoVolaBadMarket,
// 		DOUBLE				 dUndPriceTolerance,
// 		EtsPriceRoundingRuleEnum enPriceRoundingRule,
// 		DATE				 dtCalcDate);

// public:
// 
// private:
// 	void _CalcTotalsForOptionPos(IMmRvPosAtomPtr spPos, DOUBLE dUndPriceMid);


};
*/