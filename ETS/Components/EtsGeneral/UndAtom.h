// UndAtom.h : Declaration of the CUndAtom
#ifndef __UNDATOM_H__
#define __UNDATOM_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "SynthRootColl.h"
#include "EtsOptRootColl.h"
#include "EtsFutRootColl.h"
#include "EtsPriceProfileAtom.h"
#include "EtsDivAtom.h"
#include "EtsDivColl.h"
#include "EtsIndexDivAtom.h"
#include "EtsIndexDivColl.h"
#include "IndexAtom.h"
#include "EtsFutAtom.h"

_COM_SMARTPTR_TYPEDEF(IUndAtom, IID_IUndAtom);

struct __UndAtom
{
	LONG					m_nID;
	EtsContractTypeEnum		m_enUndType;
	_bstr_t					m_bstrSymbol;
    VARIANT_BOOL            m_bShouldMultOptDeltaEq;
	DOUBLE                  m_dKOptDeltaEq;
	VARIANT_BOOL			m_bIsAmerican;
	VARIANT_BOOL			m_bIsHTB;
	DOUBLE					m_dYield;
	DOUBLE					m_dPriceClose;
	DOUBLE					m_dPriceTheoClose;
	LONG					m_nLotSize;
	VARIANT_BOOL			m_bIsTraderContract;
	DOUBLE					m_dSkew;
	DOUBLE					m_dKurt;
	_bstr_t					m_bstrContractName;
	VARIANT_BOOL			m_bHaveSyntheticRoots;
	ISynthRootCollPtr		m_spSyntheticRoots;
	VARIANT_BOOL			m_bHaveOptions;
	VARIANT_BOOL			m_bIsActive;
	IEtsPriceProfileAtomPtr	m_spUndPriceProfile;
	IEtsPriceProfileAtomPtr	m_spOptPriceProfile;
	VARIANT_BOOL			m_bIsBasketIndex;
	LONG					m_nVolume10Day;
	LONG					m_nVolume5Expiration;
	DOUBLE					m_dUndPosForRates;
	IEtsOptRootCollPtr		m_spRoots;
	IEtsFutRootCollPtr		m_spFutRoots;
	VARIANT_BOOL			m_bHaveFutures;
	LONG					m_nTotalQtyInShares;
	EtsDivTypeEnum			m_enDivType;
	IEtsDivCollPtr			m_spCustomDivs;
	IEtsIndexDivAtomPtr		m_spDividend;
	_bstr_t				m_bstrPrimaryExchImportID;
	LONG					m_nPrimaryExchangeID;
	//_bstr_t			m_bstrImportID ;
	//_bstr_t			m_bstrImportID_DGH ;
	//LONG				m_lExtPosition ;
	//DOUBLE			m_dSOQ ;
	//DOUBLE			m_dSTDValue;
	IIndexAtomPtr			m_spBasketIndex ;

	IEtsFutAtomPtr			m_spActiveFuture;	// pointer to active future for indexes used in calculations
	DOUBLE				m_dSOQ;
	VARIANT_BOOL		m_bIsHedgeSymbol;
	DOUBLE m_dManualActivePrice;
	VARIANT_BOOL		m_fIsManualVol;


	__UndAtom()
		: m_nID(0L), m_enUndType(enCtStock), m_bIsAmerican(VARIANT_FALSE),
		m_bIsHTB(VARIANT_FALSE), m_dYield(0.),		
		m_dPriceClose(0.), m_nLotSize(0L), m_bIsTraderContract(VARIANT_FALSE),
		m_dSkew(0.), m_dKurt(0.),m_bHaveSyntheticRoots(VARIANT_FALSE),
		m_bHaveOptions(VARIANT_FALSE), m_bIsActive(VARIANT_FALSE),
		m_bIsBasketIndex(VARIANT_FALSE), m_nVolume10Day(0), m_nVolume5Expiration(0),
		m_dUndPosForRates(0.), m_bHaveFutures(VARIANT_FALSE), m_nTotalQtyInShares(BAD_LONG_VALUE)
		, m_enDivType(enDivMarket), m_dSOQ(0.), m_bIsHedgeSymbol(VARIANT_FALSE), m_nPrimaryExchangeID(0),
		m_dManualActivePrice(0), m_fIsManualVol(FALSE),
		m_dPriceTheoClose(BAD_DOUBLE_VALUE)

	{
	}
};

// CUndAtom

class ATL_NO_VTABLE CUndAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUndAtom, &CLSID_UndAtom>,
	public ISupportErrorInfoImpl<&IID_IUndAtom>,
	public IDispatchImpl<IUndAtom, &IID_IUndAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __UndAtom
{
public:
	CUndAtom()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_UNDATOM)


	BEGIN_COM_MAP(CUndAtom)
		COM_INTERFACE_ENTRY(IUndAtom)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		try
		{
			CComObject<CEtsOptRootColl>* oOptRoots = NULL;
			_CHK(CComObject<CEtsOptRootColl>::CreateInstance(&oOptRoots), _T("Fail to create option roots."));
			m_spRoots.Attach(oOptRoots, TRUE);

			CComObject<CEtsFutRootColl>* pEtsFutRootColl; 
			_CHK(CComObject<CEtsFutRootColl>::CreateInstance(&pEtsFutRootColl),  _T("Fail to create futures option roots."));
			m_spFutRoots.Attach(pEtsFutRootColl, TRUE);

			{

				CComObject<CEtsIndexDivAtom>* pEtsIndexDivAtom; 
				_CHK(CComObject<CEtsIndexDivAtom>::CreateInstance(&pEtsIndexDivAtom),  _T("Fail to create dividend object."));
				m_spDividend.Attach(pEtsIndexDivAtom, TRUE);
			}

			{

				CComObject<CIndexAtom>* pBasketIndex; 
				_CHK(CComObject<CIndexAtom>::CreateInstance(&pBasketIndex),  _T("Fail to create basket index object."));
				m_spBasketIndex.Attach(pBasketIndex, TRUE);
			}
		}
		catch(const _com_error& e)
		{
			return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IUndAtom, e.Error());
		}
		return S_OK;
	}

	void FinalRelease() 
	{
		m_spSyntheticRoots = NULL;
		m_spRoots = NULL;
		m_spFutRoots = NULL;
		m_spActiveFuture = NULL;
	}

public:

	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
		IMPLEMENT_SIMPLE_PROPERTY(EtsContractTypeEnum, UndType, m_enUndType)
		IMPLEMENT_BSTRT_PROPERTY(Symbol, m_bstrSymbol)
		//IMPLEMENT_BSTRT_PROPERTY(PrimaryExch, m_bstrPrimaryExch)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, bShouldMultOptDeltaEq, m_bShouldMultOptDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, dKOptDeltaEq, m_dKOptDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsAmerican, m_bIsAmerican)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsHTB, m_bIsHTB)
		//IMPLEMENT_SIMPLE_PROPERTY(LONG, ExtPosition, m_lExtPosition)
		//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, SOQ, m_dSOQ)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Yield, m_dYield)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceClose, m_dPriceClose)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceTheoClose, m_dPriceTheoClose)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, LotSize, m_nLotSize)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsTraderContract, m_bIsTraderContract)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Skew, m_dSkew)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Kurt, m_dKurt)
		IMPLEMENT_BSTRT_PROPERTY(ContractName, m_bstrContractName)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HaveSyntheticRoots, m_bHaveSyntheticRoots)	
		IMPLEMENT_OBJECT_PROPERTY(ISynthRootColl*, SyntheticRoots, m_spSyntheticRoots)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HaveOptions, m_bHaveOptions)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsActive, m_bIsActive)
		IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, UndPriceProfile, m_spUndPriceProfile)
		IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, OptPriceProfile, m_spOptPriceProfile)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsBasketIndex, m_bIsBasketIndex)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, Volume10Day, m_nVolume10Day)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, Volume5Expiration, m_nVolume5Expiration)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, UndPosForRates, m_dUndPosForRates)
		IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsOptRootColl*, Roots, m_spRoots)
		IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsFutRootColl*, FutRoots, m_spFutRoots)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HaveFutures, m_bHaveFutures)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, TotalQtyInShares, m_nTotalQtyInShares)
		IMPLEMENT_SIMPLE_PROPERTY(LONG, PrimaryExchangeID, m_nPrimaryExchangeID)
		IMPLEMENT_OBJECT_PROPERTY(IEtsIndexDivAtom*, Dividend, m_spDividend)
		IMPLEMENT_BSTRT_PROPERTY(PrimaryExchImportID, m_bstrPrimaryExchImportID)
		//IMPLEMENT_BSTRT_PROPERTY(DGH_PrimaryExchImportID,m_bstrImportID_DGH)
		//IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, STDValue, m_dSTDValue)
		IMPLEMENT_OBJECT_PROPERTY(IIndexAtom*, BasketIndex, m_spBasketIndex)
		//IMPLEMENT_BSTRT_PROPERTY(ImportID, m_bstrImportID)
		IMPLEMENT_OBJECT_PROPERTY(IEtsFutAtom*, ActiveFuture, m_spActiveFuture)
	
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, SOQ, m_dSOQ)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsHedgeSymbol, m_bIsHedgeSymbol)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, ManualActivePrice, m_dManualActivePrice)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsManualVol, m_fIsManualVol)
};

OBJECT_ENTRY_AUTO(__uuidof(UndAtom), CUndAtom)

#endif //__UNDATOM_H__
//// UndAtom.h : Declaration of the CUndAtom
//#ifndef __UNDATOM_H__
//#define __UNDATOM_H__
//#pragma once
//
//#include "resource.h"       // main symbols
//#include "EtsGeneral.h"
//#include "SynthRootColl.h"
//#include "EtsOptRootColl.h"
//#include "EtsFutRootColl.h"
//#include "EtsPriceProfileAtom.h"
//#include "EtsDivAtom.h"
//#include "EtsDivColl.h"
//#include "EtsIndexDivAtom.h"
//#include "EtsIndexDivColl.h"
//
//_COM_SMARTPTR_TYPEDEF(IUndAtom, IID_IUndAtom);
//
//struct __UndAtom
//{
//	LONG					m_nID;
//	EtsContractTypeEnum		m_enUndType;
//	_bstr_t					m_bstrSymbol;
//	VARIANT_BOOL			m_bIsAmerican;
//	VARIANT_BOOL			m_bIsHTB;
//	LONG					m_nExpCalendarID;
//	DOUBLE					m_dYield;
//	DOUBLE					m_dPriceClose;
//	LONG					m_nLotSize;
//	VARIANT_BOOL			m_bIsTraderContract;
//	DOUBLE					m_dSkew;
//	DOUBLE					m_dKurt;
//	_bstr_t					m_bstrContractName;
//	VARIANT_BOOL			m_bHaveSyntheticRoots;
//	ISynthRootCollPtr		m_spSyntheticRoots;
//	VARIANT_BOOL			m_bHaveOptions;
//	VARIANT_BOOL			m_bIsActive;
//	IEtsPriceProfileAtomPtr	m_spUndPriceProfile;
//	IEtsPriceProfileAtomPtr	m_spOptPriceProfile;
//	VARIANT_BOOL			m_bIsBasketIndex;
//	LONG					m_nVolume10Day;
//	LONG					m_nVolume5Expiration;
//	DOUBLE					m_dUndPosForRates;
//	IEtsOptRootCollPtr		m_spRoots;
//	IEtsFutRootCollPtr		m_spFutRoots;
//	VARIANT_BOOL			m_bHaveFutures;
//	LONG					m_nTotalQtyInShares;
//	EtsDivTypeEnum			m_enDivType;
//	IEtsDivCollPtr			m_spCustomDivs;
//	IEtsIndexDivAtomPtr		m_spDividend;
//	CComBSTR				m_bstrPrimaryExchImportID;
//
//	__UndAtom()
//		: m_nID(0L), m_enUndType(enCtStock), m_bIsAmerican(VARIANT_FALSE),
//		m_bIsHTB(VARIANT_FALSE), m_nExpCalendarID(0L), m_dYield(0.),		
//		m_dPriceClose(0.), m_nLotSize(0L), m_bIsTraderContract(VARIANT_FALSE),
//		m_dSkew(0.), m_dKurt(0.),m_bHaveSyntheticRoots(VARIANT_FALSE),
//		m_bHaveOptions(VARIANT_FALSE), m_bIsActive(VARIANT_FALSE),
//		m_bIsBasketIndex(VARIANT_FALSE), m_nVolume10Day(0), m_nVolume5Expiration(0),
//		m_dUndPosForRates(0.), m_bHaveFutures(VARIANT_FALSE), m_nTotalQtyInShares(BAD_LONG_VALUE)
//		, m_enDivType(enDivMarket)
//	{
//	}
//};
//
//// CUndAtom
//
//class ATL_NO_VTABLE CUndAtom : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CUndAtom, &CLSID_UndAtom>,
//	public ISupportErrorInfoImpl<&IID_IUndAtom>,
//	public IDispatchImpl<IUndAtom, &IID_IUndAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
//	public __UndAtom
//{
//public:
//	CUndAtom()
//	{
//	}
//
//DECLARE_REGISTRY_RESOURCEID(IDR_UNDATOM)
//
//
//BEGIN_COM_MAP(CUndAtom)
//	COM_INTERFACE_ENTRY(IUndAtom)
//	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(ISupportErrorInfo)
//END_COM_MAP()
//
//	DECLARE_PROTECT_FINAL_CONSTRUCT()
//
//	HRESULT FinalConstruct()
//	{
//		try
//		{
//			CComObject<CEtsOptRootColl>* oOptRoots = NULL;
//			_CHK(CComObject<CEtsOptRootColl>::CreateInstance(&oOptRoots), _T("Fail to create option roots."));
//			m_spRoots.Attach(oOptRoots, TRUE);
//
//			CComObject<CEtsFutRootColl>* pEtsFutRootColl; 
//			_CHK(CComObject<CEtsFutRootColl>::CreateInstance(&pEtsFutRootColl),  _T("Fail to create futures option roots."));
//			m_spFutRoots.Attach(pEtsFutRootColl, TRUE);
//
//			CComObject<CEtsIndexDivAtom>* pEtsIndexDivAtom; 
//			_CHK(CComObject<CEtsIndexDivAtom>::CreateInstance(&pEtsIndexDivAtom),  _T("Fail to create dividend object."));
//			m_spDividend.Attach(pEtsIndexDivAtom, TRUE);
//
//		}
//		catch(const _com_error& e)
//		{
//			return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IUndAtom, e.Error());
//		}
//		return S_OK;
//	}
//	
//	void FinalRelease() 
//	{
//		m_spSyntheticRoots = NULL;
//		m_spRoots = NULL;
//		m_spFutRoots = NULL;
//	}
//
//public:
//
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
//	IMPLEMENT_SIMPLE_PROPERTY(EtsContractTypeEnum, UndType, m_enUndType)
//	IMPLEMENT_BSTRT_PROPERTY(Symbol, m_bstrSymbol)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsAmerican, m_bIsAmerican)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsHTB, m_bIsHTB)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, ExpCalendarID, m_nExpCalendarID)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Yield, m_dYield)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, PriceClose, m_dPriceClose)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, LotSize, m_nLotSize)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsTraderContract, m_bIsTraderContract)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Skew, m_dSkew)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Kurt, m_dKurt)
//	IMPLEMENT_BSTRT_PROPERTY(ContractName, m_bstrContractName)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HaveSyntheticRoots, m_bHaveSyntheticRoots)	
//	IMPLEMENT_OBJECT_PROPERTY(ISynthRootColl*, SyntheticRoots, m_spSyntheticRoots)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HaveOptions, m_bHaveOptions)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsActive, m_bIsActive)
//	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, UndPriceProfile, m_spUndPriceProfile)
//	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*, OptPriceProfile, m_spOptPriceProfile)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsBasketIndex, m_bIsBasketIndex)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, Volume10Day, m_nVolume10Day)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, Volume5Expiration, m_nVolume5Expiration)
//	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, UndPosForRates, m_dUndPosForRates)
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsOptRootColl*, Roots, m_spRoots)
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsFutRootColl*, FutRoots, m_spFutRoots)
//	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HaveFutures, m_bHaveFutures)
//	IMPLEMENT_SIMPLE_PROPERTY(LONG, TotalQtyInShares, m_nTotalQtyInShares)
//	IMPLEMENT_OBJECT_PROPERTY(IEtsIndexDivAtom*, Dividend, m_spDividend)
//	IMPLEMENT_BSTR_PROPERTY(PrimaryExchImportID, m_bstrPrimaryExchImportID)
//	//STDMETHOD(IsValidDivs)(VARIANT_BOOL CheckCustom, VARIANT_BOOL* pVal);
//};
//
//OBJECT_ENTRY_AUTO(__uuidof(UndAtom), CUndAtom)
//
//#endif //__UNDATOM_H__
