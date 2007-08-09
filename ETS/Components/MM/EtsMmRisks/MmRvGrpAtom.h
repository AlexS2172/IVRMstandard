// MmRvGrpAtom.h : Declaration of the CMmRvGrpAtom
#ifndef __MMRVGRPATOM_H__
#define __MMRVGRPATOM_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsMmRisks.h"
#include "MmRvUndColl.h"

_COM_SMARTPTR_TYPEDEF(IMmRvGrpAtom, IID_IMmRvGrpAtom);

/////////////////////////////////////////////////////////////////////////////
//
struct __MmRvGrpAtom
{
	LONG							m_nID;
	LONG							m_nGroupType;
	CComBSTR						m_bstrName;

	DOUBLE							m_dPnlMtm;
	DOUBLE							m_dPnlTheo;
	DOUBLE							m_dVega;
	DOUBLE							m_dWtdVega;
	DOUBLE							m_dTheta;
	DOUBLE							m_dDeltaEq;
	DOUBLE							m_dGammaEq;
	DOUBLE							m_dRho;
	DOUBLE							m_dIdxDeltaEq;
	DOUBLE							m_dBetaWtdDelta;
	DOUBLE							m_dOptDelta;
	DOUBLE							m_dNetDelta;
	DOUBLE							m_dNetGamma;
	DOUBLE                          m_dNetGammaEq;
	DOUBLE							m_dBetaWtdDeltaEq;

	VARIANT_BOOL					m_bBadPnlMtm;
	VARIANT_BOOL					m_bBadPnlTheo;
	VARIANT_BOOL					m_bBadVega;
	VARIANT_BOOL					m_bBadWtdVega;
	VARIANT_BOOL					m_bBadTheta;
	VARIANT_BOOL					m_bBadDeltaEq;
	VARIANT_BOOL					m_bBadGammaEq;
	VARIANT_BOOL					m_bBadNetGammaEq;
	VARIANT_BOOL					m_bBadRho;
	VARIANT_BOOL					m_bBadIdxDeltaEq;
	VARIANT_BOOL					m_bBadBetaWtdDelta;
	VARIANT_BOOL					m_bBadOptDelta;
	VARIANT_BOOL					m_bBadNetDelta;
	VARIANT_BOOL					m_bBadNetGamma;
	VARIANT_BOOL					m_bBadBetaWtdDeltaEq;

	DOUBLE							m_dNetExposureAUM;

	DOUBLE							m_dNetExposureLong;
	DOUBLE							m_dNetExposureShort;

	VARIANT_BOOL					m_bBadNetExposure;

	//	DOUBLE							m_dNetGamma;
	//	VARIANT_BOOL					m_bBadNetGamma;

	__MmRvGrpAtom()
	{
		Clear();
	}

	void Clear()
	{
		m_nID = 0L;
		m_nGroupType = 0L;
		m_bstrName = L"";
		ClearValues();
	}

	void ClearValues()
	{
		m_dPnlMtm = BAD_DOUBLE_VALUE;
		m_dPnlTheo = BAD_DOUBLE_VALUE;
		m_dVega = BAD_DOUBLE_VALUE;
		m_dWtdVega = BAD_DOUBLE_VALUE;
		m_dTheta = BAD_DOUBLE_VALUE;
		m_dDeltaEq = BAD_DOUBLE_VALUE;
		m_dGammaEq = BAD_DOUBLE_VALUE;
		m_dRho = BAD_DOUBLE_VALUE;
		m_dIdxDeltaEq = BAD_DOUBLE_VALUE;
		m_dBetaWtdDelta = BAD_DOUBLE_VALUE;
		m_dOptDelta = BAD_DOUBLE_VALUE;
		m_dNetDelta = BAD_DOUBLE_VALUE;
		m_dNetGamma = BAD_DOUBLE_VALUE;
		m_dBetaWtdDeltaEq = BAD_DOUBLE_VALUE;

		m_bBadPnlMtm = VARIANT_FALSE;
		m_bBadPnlTheo = VARIANT_FALSE;
		m_bBadVega = VARIANT_FALSE;
		m_bBadWtdVega = VARIANT_FALSE;
		m_bBadTheta = VARIANT_FALSE;
		m_bBadDeltaEq = VARIANT_FALSE;
		m_bBadGammaEq = VARIANT_FALSE;
		m_bBadRho = VARIANT_FALSE;
		m_bBadIdxDeltaEq = VARIANT_FALSE;
		m_bBadBetaWtdDelta = VARIANT_FALSE;
		m_bBadOptDelta = VARIANT_FALSE;
		m_bBadNetDelta = VARIANT_FALSE;
		m_bBadNetGamma = VARIANT_FALSE;
		m_bBadBetaWtdDeltaEq = VARIANT_FALSE;

		m_dNetGamma = BAD_DOUBLE_VALUE;
		m_bBadNetGamma = VARIANT_FALSE;

		m_dNetGammaEq = BAD_DOUBLE_VALUE;
		m_bBadNetGammaEq = VARIANT_FALSE;

		m_dNetExposureAUM;

		m_dNetExposureLong			= BAD_DOUBLE_VALUE;
		m_dNetExposureShort			= BAD_DOUBLE_VALUE;

		m_bBadNetExposure = VARIANT_FALSE;


	}
};

/////////////////////////////////////////////////////////////////////////////
//
class ATL_NO_VTABLE CMmRvGrpAtom : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMmRvGrpAtom, &CLSID_MmRvGrpAtom>,
	public ISupportErrorInfoImpl<&IID_IMmRvGrpAtom>,
	public IDispatchImpl<IMmRvGrpAtom, &IID_IMmRvGrpAtom, &LIBID_EtsMmRisksLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __MmRvGrpAtom
{
public:
	CMmRvGrpAtom()
	{
		m_pUnkMarshaler = NULL;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MMRVGRPATOM)

	DECLARE_NOT_AGGREGATABLE(CMmRvGrpAtom)

	BEGIN_COM_MAP(CMmRvGrpAtom)
		COM_INTERFACE_ENTRY(IMmRvGrpAtom)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease() 
	{
		m_pUnkMarshaler.Release();
	}

private:
	void _CalcUndSynthValues(IMmRvUndCollPtr spUndColl, IMmRvUndAtomPtr spUnd, DOUBLE dIdxPrice,
		DOUBLE dUndPriceTolerance, EtsPriceRoundingRuleEnum enPriceRoundingRule) throw();

private:

	CComPtr<IUnknown>		m_pUnkMarshaler;

public:

	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, GroupType, m_nGroupType)
		IMPLEMENT_BSTR_PROPERTY(Name, m_bstrName)

		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlMtm, m_dPnlMtm)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlTheo, m_dPnlTheo)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Vega, m_dVega)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, WtdVega, m_dWtdVega)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Theta, m_dTheta)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DeltaEq, m_dDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaEq, m_dGammaEq)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetGammaEq, m_dNetGammaEq)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Rho, m_dRho)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, IdxDeltaEq, m_dIdxDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, BetaWtdDelta, m_dBetaWtdDelta)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, OptDelta, m_dOptDelta)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetDelta, m_dNetDelta)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetGamma, m_dNetGamma)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, BetaWtdDeltaEq, m_dBetaWtdDeltaEq)


		IMPLEMENT_SIMPLEREADONLY_PROPERTY(DOUBLE, NetExposureShort, m_dNetExposureShort)
		IMPLEMENT_SIMPLEREADONLY_PROPERTY(DOUBLE, NetExposureLong,	m_dNetExposureLong)
		IMPLEMENT_SIMPLEREADONLY_PROPERTY(VARIANT_BOOL, BadNetExposure,	m_bBadNetExposure)


		IMPLEMENT_SIMPLEREADONLY_PROPERTY(DOUBLE, NetExposureAUM, m_dNetExposureAUM)
		STDMETHOD(put_NetExposureAUM)(DOUBLE dNewVal);

		STDMETHOD(get_NetExposure)(DOUBLE* pVal)
		{
			HRESULT hr = S_OK;
			if(!pVal) return E_POINTER;
			if(m_dNetExposureLong == BAD_DOUBLE_VALUE && m_dNetExposureShort == BAD_DOUBLE_VALUE)
				*pVal = BAD_DOUBLE_VALUE;
			else
				*pVal = ((m_dNetExposureLong == BAD_DOUBLE_VALUE)?0:m_dNetExposureLong)+((m_dNetExposureShort == BAD_DOUBLE_VALUE)?0:m_dNetExposureShort);
			return hr;
		}


		IMPLEMENT_SIMPLEREADONLY_PROPERTY(VARIANT_BOOL, ,		m_bBadNetExposure)


		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadPnlMtm, m_bBadPnlMtm)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadPnlTheo, m_bBadPnlTheo)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadVega, m_bBadVega)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadWtdVega, m_bBadWtdVega)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadTheta, m_bBadTheta)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadDeltaEq, m_bBadDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadGammaEq, m_bBadGammaEq)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetGammaEq, m_bBadNetGammaEq)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadRho, m_bBadRho)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadIdxDeltaEq, m_bBadIdxDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadBetaWtdDelta, m_bBadBetaWtdDelta)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadOptDelta, m_bBadOptDelta)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetDelta, m_bBadNetDelta)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetGamma, m_bBadNetGamma)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadBetaWtdDeltaEq, m_bBadBetaWtdDeltaEq)

		//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetGamma, m_dNetGamma)
		//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetGamma, m_bNetGamma)

		STDMETHODIMP Clear()
	{
		__MmRvGrpAtom::Clear();
		return S_OK;
	}

	STDMETHODIMP ClearValues()
	{
		__MmRvGrpAtom::ClearValues();
		return S_OK;
	}

	// 	STDMETHOD(CalcGroup)(IMmRvUndColl* aUndColl,
	// 				IMmRvUndAtom* aIdx,
	// 				VARIANT_BOOL  bTotals,
	// 				LONG nMask,
	// 				VARIANT_BOOL bCalcGreeks,
	// 				VARIANT_BOOL bUpdateVola,
	// 				VARIANT_BOOL bRealtimeCalc,
	// 				IEtsProcessDelay* aDelay,
	// 				VARIANT_BOOL bIsPnlLTD,
	// 				EtsCalcModelTypeEnum enCalcModel,
	// 				VARIANT_BOOL bUseTheoVolatility,
	// 				VARIANT_BOOL bUseTheoVolaNoBid,
	// 				VARIANT_BOOL bUseTheoVolaBadMarket,
	// 				DOUBLE dUndPriceTolerance,
	// 				EtsPriceRoundingRuleEnum enPriceRoundingRule,
	// 				LONG* pnOptUpdated,
	// 				LONG* pnUndUpdated,
	// 				LONG* pnFutUpdated,
	// 				DATE dtCalcDate);

	STDMETHOD(CalcWtdVega)(IMmRvUndColl* aUndColl,
		IEtsExpCalColl* aExpCalColl);


public:

	HRESULT CalcGroup(
		CMmRvUndColl* pUndColl,
		CMmRvUndAtom* pIdx,
		VARIANT_BOOL  bTotals,
		LONG nMask,
		VARIANT_BOOL bCalcGreeks,
		VARIANT_BOOL bUpdateVola,
		VARIANT_BOOL bRealtimeCalc,
		IEtsProcessDelay* aDelay,
		VARIANT_BOOL bIsPnlLTD,
		EtsCalcModelTypeEnum enCalcModel,
		VARIANT_BOOL bUseTheoVolatility,
		VARIANT_BOOL bUseTheoVolaNoBid,
		VARIANT_BOOL bUseTheoVolaBadMarket,
		DOUBLE dUndPriceTolerance,
		EtsPriceRoundingRuleEnum enPriceRoundingRule,
		LONG* pnOptUpdated,
		LONG* pnUndUpdated,
		LONG* pnFutUpdated,
		DATE dtCalcDate);

};

OBJECT_ENTRY_AUTO(__uuidof(MmRvGrpAtom), CMmRvGrpAtom)

#endif //__MMRVGRPATOM_H__
//// MmRvGrpAtom.h : Declaration of the CMmRvGrpAtom
//#ifndef __MMRVGRPATOM_H__
//#define __MMRVGRPATOM_H__
//#pragma once
//
//#include "resource.h"       // main symbols
//#include "EtsMmRisks.h"
//#include "MmRvUndColl.h"
//
//_COM_SMARTPTR_TYPEDEF(IMmRvGrpAtom, IID_IMmRvGrpAtom);
//
///////////////////////////////////////////////////////////////////////////////
////
//struct __MmRvGrpAtom
//{
//	LONG							m_nID;
//	LONG							m_nGroupType;
//	CComBSTR						m_bstrName;
//
//	DOUBLE							m_dPnlMtm;
//	DOUBLE							m_dPnlTheo;
//	DOUBLE							m_dVega;
//	DOUBLE							m_dWtdVega;
//	DOUBLE							m_dTheta;
//	DOUBLE							m_dDeltaEq;
//	DOUBLE							m_dGammaEq;
//	DOUBLE							m_dRho;
//	DOUBLE							m_dIdxDeltaEq;
//	DOUBLE							m_dBetaWtdDelta;
//	DOUBLE							m_dOptDelta;
//	DOUBLE							m_dNetDelta;
//	DOUBLE							m_dNetGamma;
//	DOUBLE							m_dBetaWtdDeltaEq;
//
//	VARIANT_BOOL					m_bBadPnlMtm;
//	VARIANT_BOOL					m_bBadPnlTheo;
//	VARIANT_BOOL					m_bBadVega;
//	VARIANT_BOOL					m_bBadWtdVega;
//	VARIANT_BOOL					m_bBadTheta;
//	VARIANT_BOOL					m_bBadDeltaEq;
//	VARIANT_BOOL					m_bBadGammaEq;
//	VARIANT_BOOL					m_bBadRho;
//	VARIANT_BOOL					m_bBadIdxDeltaEq;
//	VARIANT_BOOL					m_bBadBetaWtdDelta;
//	VARIANT_BOOL					m_bBadOptDelta;
//	VARIANT_BOOL					m_bBadNetDelta;
//	VARIANT_BOOL					m_bBadNetGamma;
//	VARIANT_BOOL					m_bBadBetaWtdDeltaEq;
//
//
////	DOUBLE							m_dNetGamma;
////	VARIANT_BOOL					m_bBadNetGamma;
//
//	__MmRvGrpAtom()
//	{
//		Clear();
//	}
//
//	void Clear()
//	{
//		m_nID = 0L;
//		m_nGroupType = 0L;
//		m_bstrName = L"";
//		ClearValues();
//	}
//
//	void ClearValues()
//	{
//		m_dPnlMtm = BAD_DOUBLE_VALUE;
//		m_dPnlTheo = BAD_DOUBLE_VALUE;
//		m_dVega = BAD_DOUBLE_VALUE;
//		m_dWtdVega = BAD_DOUBLE_VALUE;
//		m_dTheta = BAD_DOUBLE_VALUE;
//		m_dDeltaEq = BAD_DOUBLE_VALUE;
//		m_dGammaEq = BAD_DOUBLE_VALUE;
//		m_dRho = BAD_DOUBLE_VALUE;
//		m_dIdxDeltaEq = BAD_DOUBLE_VALUE;
//		m_dBetaWtdDelta = BAD_DOUBLE_VALUE;
//		m_dOptDelta = BAD_DOUBLE_VALUE;
//		m_dNetDelta = BAD_DOUBLE_VALUE;
//		m_dNetGamma = BAD_DOUBLE_VALUE;
//		m_dBetaWtdDeltaEq = BAD_DOUBLE_VALUE;
//
//		m_bBadPnlMtm = VARIANT_FALSE;
//		m_bBadPnlTheo = VARIANT_FALSE;
//		m_bBadVega = VARIANT_FALSE;
//		m_bBadWtdVega = VARIANT_FALSE;
//		m_bBadTheta = VARIANT_FALSE;
//		m_bBadDeltaEq = VARIANT_FALSE;
//		m_bBadGammaEq = VARIANT_FALSE;
//		m_bBadRho = VARIANT_FALSE;
//		m_bBadIdxDeltaEq = VARIANT_FALSE;
//		m_bBadBetaWtdDelta = VARIANT_FALSE;
//		m_bBadOptDelta = VARIANT_FALSE;
//		m_bBadNetDelta = VARIANT_FALSE;
//		m_bBadNetGamma = VARIANT_FALSE;
//		m_bBadBetaWtdDeltaEq = VARIANT_FALSE;
//		
//		m_dNetGamma = BAD_DOUBLE_VALUE;
//		m_bBadNetGamma = VARIANT_FALSE;
//
//	}
//};
//
///////////////////////////////////////////////////////////////////////////////
////
//class ATL_NO_VTABLE CMmRvGrpAtom : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CMmRvGrpAtom, &CLSID_MmRvGrpAtom>,
//	public ISupportErrorInfoImpl<&IID_IMmRvGrpAtom>,
//	public IDispatchImpl<IMmRvGrpAtom, &IID_IMmRvGrpAtom, &LIBID_EtsMmRisksLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
//	public __MmRvGrpAtom
//{
//public:
//	CMmRvGrpAtom()
//	{
//	}
//
//DECLARE_REGISTRY_RESOURCEID(IDR_MMRVGRPATOM)
//
//DECLARE_NOT_AGGREGATABLE(CMmRvGrpAtom)
//
//BEGIN_COM_MAP(CMmRvGrpAtom)
//	COM_INTERFACE_ENTRY(IMmRvGrpAtom)
//	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(ISupportErrorInfo)
//END_COM_MAP()
//
//	DECLARE_PROTECT_FINAL_CONSTRUCT()
//
//	HRESULT FinalConstruct()
//	{
//		return S_OK;
//	}
//	
//	void FinalRelease() 
//	{
//	}
//
//private:
//	void _CalcUndSynthValues(IMmRvUndCollPtr spUndColl, IMmRvUndAtomPtr spUnd, DOUBLE dIdxPrice,
//				DOUBLE dUndPriceTolerance, EtsPriceRoundingRuleEnum enPriceRoundingRule) throw();
//
//
//public:
//	
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, GroupType, m_nGroupType)
//	IMPLEMENT_BSTR_PROPERTY(Name, m_bstrName)
//
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlMtm, m_dPnlMtm)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PnlTheo, m_dPnlTheo)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Vega, m_dVega)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, WtdVega, m_dWtdVega)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Theta, m_dTheta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DeltaEq, m_dDeltaEq)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaEq, m_dGammaEq)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Rho, m_dRho)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, IdxDeltaEq, m_dIdxDeltaEq)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, BetaWtdDelta, m_dBetaWtdDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, OptDelta, m_dOptDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetDelta, m_dNetDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetGamma, m_dNetGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, BetaWtdDeltaEq, m_dBetaWtdDeltaEq)
//
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadPnlMtm, m_bBadPnlMtm)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadPnlTheo, m_bBadPnlTheo)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadVega, m_bBadVega)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadWtdVega, m_bBadWtdVega)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadTheta, m_bBadTheta)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadDeltaEq, m_bBadDeltaEq)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadGammaEq, m_bBadGammaEq)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadRho, m_bBadRho)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadIdxDeltaEq, m_bBadIdxDeltaEq)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadBetaWtdDelta, m_bBadBetaWtdDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadOptDelta, m_bBadOptDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetDelta, m_bBadNetDelta)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetGamma, m_bBadNetGamma)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadBetaWtdDeltaEq, m_bBadBetaWtdDeltaEq)
//
////	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, NetGamma, m_dNetGamma)
////	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadNetGamma, m_bNetGamma)
//
//	STDMETHODIMP Clear()
//	{
//		__MmRvGrpAtom::Clear();
//		return S_OK;
//	}
//
//	STDMETHODIMP ClearValues()
//	{
//		__MmRvGrpAtom::ClearValues();
//		return S_OK;
//	}
//
//	STDMETHOD(Calc)(IMmRvUndColl* aUndColl,
//				IMmRvUndAtom* aIdx,
//				VARIANT_BOOL  bTotals,
//				LONG nMask,
//				VARIANT_BOOL bCalcGreeks,
//				VARIANT_BOOL bUpdateVola,
//				VARIANT_BOOL bRealtimeCalc,
//				IEtsProcessDelay* aDelay,
//				VARIANT_BOOL bIsPnlLTD,
//				EtsCalcModelTypeEnum enCalcModel,
//				VARIANT_BOOL bUseTheoVolatility,
//				VARIANT_BOOL bUseTheoVolaNoBid,
//				VARIANT_BOOL bUseTheoVolaBadMarket,
//				DOUBLE dUndPriceTolerance,
//				EtsPriceRoundingRuleEnum enPriceRoundingRule,
//				LONG* pnOptUpdated,
//				LONG* pnUndUpdated,
//				LONG* pnFutUpdated);
//
//	STDMETHOD(CalcWtdVega)(IMmRvUndColl* aUndColl,
//				IEtsExpCalColl* aExpCalColl);
//};
//
//OBJECT_ENTRY_AUTO(__uuidof(MmRvGrpAtom), CMmRvGrpAtom)
//
//#endif //__MMRVGRPATOM_H__