// EtsMain.h : Declaration of the CEtsMain

#pragma once
#include "resource.h"       // main symbols

#include "EtsGeneral.h"

#include "EtsTraderColl.h"
#include "EtsTraderGroupColl.h"
#include "EtsStrategyColl.h"
#include "EtsBrokerColl.h"
#include "EtsUndGroupColl.h"
#include "EtsOptRootByNameColl.h"
#include "EtsContractColl.h"
#include "EtsPriceProfileColl.h"
#include "EtsExpCalColl.h"
#include "ExchColl.h"
#include "IndexColl.h"

#include "_IEtsMainEvents_CP.h"



// CEtsMain

class ATL_NO_VTABLE CEtsMain : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsMain, &CLSID_EtsMain>,
	public ISupportErrorInfoImpl<&IID_IEtsMain>,
	public IConnectionPointContainerImpl<CEtsMain>,
	public CProxy_IEtsMainEvents<CEtsMain>, 
	public IDispatchImpl<IEtsMain, &IID_IEtsMain, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CEtsMain()
		:m_pTraderColl(NULL)
		,m_pTraderGroup(NULL)
		,m_pStrategy(NULL)
		,m_pBroker(NULL)
		,m_pClearingBroker(NULL)
		,m_pUnderlying(NULL)
		,m_pUnderlyingAll(NULL)
		,m_pUnderlyingGroup(NULL)
		,m_pStock(NULL)
		,m_pOptRootByName(NULL)
		,m_pContractAll(NULL)
		,m_pContract(NULL)
		,m_pPriceProfile(NULL)
		,m_pExpCalendar(NULL)
		,m_pExhc(NULL)
		,m_pIndex(NULL)
		,m_pHedgeSymbols(NULL)
		,m_pBasketIndex(NULL)
		,m_bUseTheoCloseForPNL(VARIANT_FALSE)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_ETSMAIN)

	DECLARE_NOT_AGGREGATABLE(CEtsMain)

	BEGIN_COM_MAP(CEtsMain)
		COM_INTERFACE_ENTRY(IEtsMain)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CEtsMain)
		CONNECTION_POINT_ENTRY(__uuidof(_IEtsMainEvents))
	END_CONNECTION_POINT_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		try
		{
			_CHK(CComObject<CEtsTraderColl>::CreateInstance(&m_pTraderColl), _T("Fail to create Traders Collection."));
			m_spTraderColl.Attach(m_pTraderColl, TRUE);

			_CHK(CComObject<CEtsTraderGroupColl>::CreateInstance(&m_pTraderGroup), _T("Fail to create Trader Groups Collection."));
			m_spTraderGroup.Attach(m_pTraderGroup, TRUE);

			_CHK(CComObject<CEtsStrategyColl>::CreateInstance(&m_pStrategy), _T("Fail to create Strategy Collection."));
			m_spStrategy.Attach(m_pStrategy, TRUE);

			_CHK(CComObject<CEtsBrokerColl>::CreateInstance(&m_pBroker), _T("Fail to create Brokers Collection."));
			m_spBroker.Attach(m_pBroker, TRUE);

			_CHK(CComObject<CEtsBrokerColl>::CreateInstance(&m_pClearingBroker), _T("Fail to create Clearing Brokers Collection."));
			m_spClearingBroker.Attach(m_pClearingBroker, TRUE);

			_CHK(CComObject<CUndColl>::CreateInstance(&m_pUnderlying), _T("Fail to create Underliengs Collection."));
			m_spUnderlying.Attach(m_pUnderlying, TRUE);

			_CHK(CComObject<CUndColl>::CreateInstance(&m_pStock), _T("Fail to create Stocks Collection."));
			m_spStock.Attach(m_pStock, TRUE);

			_CHK(CComObject<CUndColl>::CreateInstance(&m_pUnderlyingAll), _T("Fail to create All Underliengs Collection."));
			m_spUnderlyingAll.Attach(m_pUnderlyingAll, TRUE);

			_CHK(CComObject<CEtsUndGroupColl>::CreateInstance(&m_pUnderlyingGroup), _T("Fail to create  Underliengs Groups Collection."));
			m_spUnderlyingGroup.Attach(m_pUnderlyingGroup, TRUE);

			_CHK(CComObject<CEtsOptRootByNameColl>::CreateInstance(&m_pOptRootByName), _T("Fail to create  Option Root By Name Collection."));
			m_spOptRootByName.Attach(m_pOptRootByName, TRUE);

			_CHK(CComObject<CEtsContractColl>::CreateInstance(&m_pContractAll), _T("Fail to create  All Contracts Collection."));
			m_spContractAll.Attach(m_pContractAll, TRUE);

			_CHK(CComObject<CEtsContractColl>::CreateInstance(&m_pContract), _T("Fail to create Contracts Collection."));
			m_spContract.Attach(m_pContract, TRUE);

			_CHK(CComObject<CEtsPriceProfileColl>::CreateInstance(&m_pPriceProfile), _T("Fail to create Price Profile Collection."));
			m_spPriceProfile.Attach(m_pPriceProfile, TRUE);

			_CHK(CComObject<CEtsExpCalColl>::CreateInstance(&m_pExpCalendar), _T("Fail to create Expiration Calendar Collection."));
			m_spExpCalendar.Attach(m_pExpCalendar, TRUE);

			_CHK(CComObject<CExchColl>::CreateInstance(&m_pExhc), _T("Fail to create Exchanges Collection."));
			m_spExhc.Attach(m_pExhc, TRUE);


			_CHK(CComObject<CIndexColl>::CreateInstance(&m_pIndex), _T("Fail to create Indices Collection."));
			m_spIndex.Attach(m_pIndex, TRUE);

			_CHK(CComObject<CIndexColl>::CreateInstance(&m_pBasketIndex), _T("Fail to create Basket Indices Collection."));
			m_spBasketIndex.Attach(m_pBasketIndex, TRUE);

			_CHK(CComObject<CIndexColl>::CreateInstance(&m_pHedgeSymbols), _T("Fail to create Hedge Symbols Collection."));
			m_spHedgeSymbols.Attach(m_pHedgeSymbols, TRUE);

		}
		catch(_com_error& e )
		{
			return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());
		}

		return S_OK;

	}

	void FinalRelease() 
	{
	}


private:
	void InitializeDB() 
	{
		if(!m_DbConnection.IsOpened())
			m_DbConnection.Open(m_bstrDatabaseString, 10, 120, 300, 300);
	}

	void _Clear()
	{

		if(m_pTraderColl) 		m_pTraderColl->Clear();
		if(m_pTraderGroup)		m_pTraderGroup->Clear();
		if(m_pStrategy)			m_pStrategy->Clear();
		if(m_pBroker)			m_pBroker->Clear();
		if(m_pClearingBroker)   m_pClearingBroker->Clear();
		if(m_pUnderlying)		m_pUnderlying->Clear();
		if(m_pUnderlyingAll)	m_pUnderlyingAll->Clear();
		if(m_pUnderlyingGroup)	m_pUnderlyingGroup->Clear();
		if(m_pStock)			m_pStock->Clear();
		if(m_pOptRootByName)    m_pOptRootByName->Clear();
		if(m_pContractAll)		m_pContractAll->Clear();
		if(m_pContract)			m_pContract->Clear();
		if(m_pPriceProfile)		m_pPriceProfile->Clear();
		if(m_pExpCalendar)      m_pExpCalendar->Clear();
		if(m_pExhc)			    m_pExhc->Clear();
		if(m_pIndex)            m_pIndex->Clear();
		if(m_pBasketIndex)      m_pBasketIndex->Clear();
		if(m_pHedgeSymbols)     m_pHedgeSymbols->Clear();
	}
private:
	CDBConnection                       m_DbConnection; 
	_bstr_t								m_bstrDatabaseString;
	VARIANT_BOOL						m_bUseTheoCloseForPNL;

	CComObject<CEtsTraderColl>*			m_pTraderColl;
	CComObject<CEtsTraderGroupColl>*	m_pTraderGroup;
	CComObject<CEtsStrategyColl>*		m_pStrategy;
	CComObject<CEtsBrokerColl>*			m_pBroker;
	CComObject<CEtsBrokerColl>*			m_pClearingBroker;
	CComObject<CUndColl>*				m_pUnderlying;
	CComObject<CUndColl>*				m_pUnderlyingAll;
	CComObject<CUndColl>*				m_pStock;
	CComObject<CEtsUndGroupColl>*		m_pUnderlyingGroup;
	CComObject<CEtsOptRootByNameColl>*	m_pOptRootByName;
	CComObject<CEtsContractColl>*		m_pContractAll;
	CComObject<CEtsContractColl>*		m_pContract;

	CComObject<CEtsPriceProfileColl>*	m_pPriceProfile;
	CComObject<CEtsExpCalColl>*			m_pExpCalendar;
	CComObject<CExchColl>*				m_pExhc;
	CComObject<CIndexColl>*				m_pIndex;

	CComObject<CIndexColl>*				m_pBasketIndex;	
	CComObject<CIndexColl>*				m_pHedgeSymbols;	
	


private:
	IEtsTraderCollPtr			m_spTraderColl;
	IEtsTraderGroupCollPtr		m_spTraderGroup;
	IEtsStrategyCollPtr			m_spStrategy;
	IEtsBrokerCollPtr			m_spBroker;
	IEtsBrokerCollPtr			m_spClearingBroker;
	IUndCollPtr					m_spUnderlying;
	IUndCollPtr					m_spUnderlyingAll;
	IUndCollPtr					m_spStock;
	IEtsUndGroupCollPtr			m_spUnderlyingGroup;
	IEtsOptRootByNameCollPtr	m_spOptRootByName;
	IEtsContractCollPtr			m_spContractAll;
	IEtsContractCollPtr			m_spContract;
	IEtsPriceProfileCollPtr		m_spPriceProfile;

	IEtsPriceProfileAtomPtr		m_spDefStkPriceProfile;
	IEtsPriceProfileAtomPtr		m_spDefIdxPriceProfile;
	IEtsPriceProfileAtomPtr		m_spDefOptPriceProfile;
	IEtsExpCalCollPtr		    m_spExpCalendar;
	IExchCollPtr				m_spExhc;
	IIndexCollPtr               m_spIndex;
	IIndexCollPtr				m_spBasketIndex;	
	IIndexCollPtr				m_spHedgeSymbols;
	//IETSLogPtr					m_spLogger;

public:
	STDMETHOD(Clear)();
	STDMETHOD(LoadStrategy)();
	STDMETHOD(LoadBroker)();
	STDMETHOD(LoadBetas)();
	STDMETHOD(LoadTraderGroup)();
	STDMETHOD(LoadTrader)(LONG lTraderID);
	STDMETHOD(LoadUnderlying)(LONG lTraderID);
	STDMETHOD(LoadAssetGroup)();

	IMPLEMENT_BSTRT_PROPERTY(DatabaseString, m_bstrDatabaseString)
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsTraderColl*,			Trader,			m_spTraderColl);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsTraderGroupColl*,		TraderGroup,	m_spTraderGroup);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsStrategyColl*,		Strategy,		m_spStrategy);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsBrokerColl*,			Broker,			m_spBroker);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsBrokerColl*,			ClearingBroker, m_spClearingBroker);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IUndColl*,				Underlying,		m_spUnderlying);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IUndColl*,				UnderlyingAll,	m_spUnderlyingAll);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IUndColl*,				Stock,			m_spStock);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsOptRootByNameColl*,	OptRootByName,	m_spOptRootByName);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsContractColl*,		ContractAll,	m_spContractAll);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsContractColl*,		Contract,		m_spContract);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsUndGroupColl*,		UnderlyingGroup,m_spUnderlyingGroup);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IIndexColl*,				Index,			m_spIndex);
	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*,	DefStkPriceProfile,	m_spDefStkPriceProfile);
	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*,	DefIdxPriceProfile,	m_spDefIdxPriceProfile);
	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*,	DefOptPriceProfile,	m_spDefOptPriceProfile);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsPriceProfileColl*,	PriceProfile,		m_spPriceProfile);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsExpCalColl*,			ExpCalendar,		m_spExpCalendar);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IExchColl*,			Exch,		m_spExhc);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IIndexColl*,	BasketIndex, m_spBasketIndex);
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IIndexColl*,	HedgeSymbols, m_spHedgeSymbols);
	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, UseTheoCloseForPNL, m_bUseTheoCloseForPNL);
	//IMPLEMENT_OBJECT_PROPERTY(IETSLog*,			Logger,		m_spLogger);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsMain), CEtsMain)

//// EtsMain.h : Declaration of the CEtsMain
//
//#pragma once
//#include "resource.h"       // main symbols
//
//#include "EtsGeneral.h"
//
//#include "EtsTraderColl.h"
//#include "EtsTraderGroupColl.h"
//#include "EtsStrategyColl.h"
//#include "EtsBrokerColl.h"
//#include "EtsUndGroupColl.h"
//#include "EtsOptRootByNameColl.h"
//#include "EtsContractColl.h"
//#include "EtsPriceProfileColl.h"
//#include "EtsExpCalColl.h"
//#include "ExchColl.h"
//
//#include "_IEtsMainEvents_CP.h"
//
//
//// CEtsMain
//
//class ATL_NO_VTABLE CEtsMain : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CEtsMain, &CLSID_EtsMain>,
//	public ISupportErrorInfoImpl<&IID_IEtsMain>,
//	public IConnectionPointContainerImpl<CEtsMain>,
//	public CProxy_IEtsMainEvents<CEtsMain>, 
//	public IDispatchImpl<IEtsMain, &IID_IEtsMain, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
//{
//public:
//	CEtsMain()
//		:m_pTraderColl(NULL)
//		,m_pTraderGroup(NULL)
//		,m_pStrategy(NULL)
//		,m_pBroker(NULL)
//		,m_pClearingBroker(NULL)
//		,m_pUnderlying(NULL)
//		,m_pUnderlyingAll(NULL)
//		,m_pUnderlyingGroup(NULL)
//		,m_pStock(NULL)
//		,m_pOptRootByName(NULL)
//		,m_pContractAll(NULL)
//		,m_pContract(NULL)
//		,m_pPriceProfile(NULL)
//		,m_pExpCalendar(NULL)
//		,m_pExhc(NULL)
//	{
//	}
//
//DECLARE_REGISTRY_RESOURCEID(IDR_ETSMAIN)
//
//DECLARE_NOT_AGGREGATABLE(CEtsMain)
//
//BEGIN_COM_MAP(CEtsMain)
//	COM_INTERFACE_ENTRY(IEtsMain)
//	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(ISupportErrorInfo)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//END_COM_MAP()
//
//BEGIN_CONNECTION_POINT_MAP(CEtsMain)
//	CONNECTION_POINT_ENTRY(__uuidof(_IEtsMainEvents))
//END_CONNECTION_POINT_MAP()
//
//	DECLARE_PROTECT_FINAL_CONSTRUCT()
//
//	HRESULT FinalConstruct()
//	{
//		try
//		{
//			_CHK(CComObject<CEtsTraderColl>::CreateInstance(&m_pTraderColl), _T("Fail to create Traders Collection."));
//			m_spTraderColl.Attach(m_pTraderColl, TRUE);
//
//			_CHK(CComObject<CEtsTraderGroupColl>::CreateInstance(&m_pTraderGroup), _T("Fail to create Trader Groups Collection."));
//			m_spTraderGroup.Attach(m_pTraderGroup, TRUE);
//
//			_CHK(CComObject<CEtsStrategyColl>::CreateInstance(&m_pStrategy), _T("Fail to create Strategy Collection."));
//			m_spStrategy.Attach(m_pStrategy, TRUE);
//
//			_CHK(CComObject<CEtsBrokerColl>::CreateInstance(&m_pBroker), _T("Fail to create Brokers Collection."));
//			m_spBroker.Attach(m_pBroker, TRUE);
//
//			_CHK(CComObject<CEtsBrokerColl>::CreateInstance(&m_pClearingBroker), _T("Fail to create Clearing Brokers Collection."));
//			m_spClearingBroker.Attach(m_pClearingBroker, TRUE);
//
//			_CHK(CComObject<CUndColl>::CreateInstance(&m_pUnderlying), _T("Fail to create Underliengs Collection."));
//			m_spUnderlying.Attach(m_pUnderlying, TRUE);
//
//			_CHK(CComObject<CUndColl>::CreateInstance(&m_pStock), _T("Fail to create Stocks Collection."));
//			m_spStock.Attach(m_pStock, TRUE);
//
//			_CHK(CComObject<CUndColl>::CreateInstance(&m_pUnderlyingAll), _T("Fail to create All Underliengs Collection."));
//			m_spUnderlyingAll.Attach(m_pUnderlyingAll, TRUE);
//
//			_CHK(CComObject<CEtsUndGroupColl>::CreateInstance(&m_pUnderlyingGroup), _T("Fail to create  Underliengs Groups Collection."));
//			m_spUnderlyingGroup.Attach(m_pUnderlyingGroup, TRUE);
//
//			_CHK(CComObject<CEtsOptRootByNameColl>::CreateInstance(&m_pOptRootByName), _T("Fail to create  Option Root By Name Collection."));
//			m_spOptRootByName.Attach(m_pOptRootByName, TRUE);
//
//			_CHK(CComObject<CEtsContractColl>::CreateInstance(&m_pContractAll), _T("Fail to create  All Contracts Collection."));
//			m_spContractAll.Attach(m_pContractAll, TRUE);
//
//			_CHK(CComObject<CEtsContractColl>::CreateInstance(&m_pContract), _T("Fail to create Contracts Collection."));
//			m_spContract.Attach(m_pContract, TRUE);
//
//			_CHK(CComObject<CEtsPriceProfileColl>::CreateInstance(&m_pPriceProfile), _T("Fail to create Price Profile Collection."));
//			m_spPriceProfile.Attach(m_pPriceProfile, TRUE);
//
//			_CHK(CComObject<CEtsExpCalColl>::CreateInstance(&m_pExpCalendar), _T("Fail to create Expiration Calendar Collection."));
//			m_spExpCalendar.Attach(m_pExpCalendar, TRUE);
//
//			_CHK(CComObject<CExchColl>::CreateInstance(&m_pExhc), _T("Fail to create Exchanges Collection."));
//			m_spExhc.Attach(m_pExhc, TRUE);
//
//		}
//		catch(_com_error& e )
//		{
//			return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsMain, e.Error());
//		}
//
//
//		return S_OK;
//	}
//	
//	void FinalRelease() 
//	{
//	}
//
//private:
//	void InitializeDB() 
//	{
//		if(!m_DbConnection.IsOpened())
//			m_DbConnection.Open(m_bstrDatabaseString, 10, 120, 300, 300);
//	}
//
//	void _Clear()
//	{
//		if(m_pTraderColl) 		m_pTraderColl->Clear();
//		if(m_pTraderGroup)		m_pTraderGroup->Clear();
//		if(m_pStrategy)			m_pStrategy->Clear();
//		if(m_pBroker)			m_pBroker->Clear();
//		if(m_pClearingBroker)   m_pClearingBroker->Clear();
//		if(m_pUnderlying)		m_pUnderlying->Clear();
//		if(m_pUnderlyingAll)	m_pUnderlyingAll->Clear();
//		if(m_pUnderlyingGroup)	m_pUnderlyingGroup->Clear();
//		if(m_pStock)			m_pStock->Clear();
//		if(m_pOptRootByName)    m_pOptRootByName->Clear();
//		if(m_pContractAll)		m_pContractAll->Clear();
//		if(m_pContract)			m_pContract->Clear();
//		if(m_pPriceProfile)		m_pPriceProfile->Clear();
//		if(m_pExpCalendar)      m_pExpCalendar->Clear();
//		if(m_pExhc)			    m_pExhc->Clear();
//
//	}
//private:
//	CDBConnection                       m_DbConnection; 
//	_bstr_t								m_bstrDatabaseString;
//
//	CComObject<CEtsTraderColl>*			m_pTraderColl;
//	CComObject<CEtsTraderGroupColl>*	m_pTraderGroup;
//	CComObject<CEtsStrategyColl>*		m_pStrategy;
//	CComObject<CEtsBrokerColl>*			m_pBroker;
//	CComObject<CEtsBrokerColl>*			m_pClearingBroker;
//	CComObject<CUndColl>*				m_pUnderlying;
//	CComObject<CUndColl>*				m_pUnderlyingAll;
//	CComObject<CUndColl>*				m_pStock;
//	CComObject<CEtsUndGroupColl>*		m_pUnderlyingGroup;
//	CComObject<CEtsOptRootByNameColl>*	m_pOptRootByName;
//	CComObject<CEtsContractColl>*		m_pContractAll;
//	CComObject<CEtsContractColl>*		m_pContract;
//
//	CComObject<CEtsPriceProfileColl>*	m_pPriceProfile;
//	CComObject<CEtsExpCalColl>*			m_pExpCalendar;
//	CComObject<CExchColl>*				m_pExhc;
//
//private:
//	IEtsTraderCollPtr			m_spTraderColl;
//	IEtsTraderGroupCollPtr		m_spTraderGroup;
//	IEtsStrategyCollPtr			m_spStrategy;
//	IEtsBrokerCollPtr			m_spBroker;
//	IEtsBrokerCollPtr			m_spClearingBroker;
//	IUndCollPtr					m_spUnderlying;
//	IUndCollPtr					m_spUnderlyingAll;
//	IUndCollPtr					m_spStock;
//	IEtsUndGroupCollPtr			m_spUnderlyingGroup;
//	IEtsOptRootByNameCollPtr	m_spOptRootByName;
//	IEtsContractCollPtr			m_spContractAll;
//	IEtsContractCollPtr			m_spContract;
//	IEtsPriceProfileCollPtr		m_spPriceProfile;
//	
//	IEtsPriceProfileAtomPtr		m_spDefStkPriceProfile;
//	IEtsPriceProfileAtomPtr		m_spDefIdxPriceProfile;
//	IEtsPriceProfileAtomPtr		m_spDefOptPriceProfile;
//	IEtsExpCalAtomPtr			m_spDefExpCalendar;
//	IEtsExpCalCollPtr		    m_spExpCalendar;
//	IExchCollPtr				m_spExhc;
//
//
//
//public:
//	STDMETHOD(Clear)();
//	STDMETHOD(LoadStrategy)();
//	STDMETHOD(LoadBroker)();
//	STDMETHOD(LoadTraderGroup)();
//	STDMETHOD(LoadTrader)(LONG lTraderID);
//	STDMETHOD(LoadUnderlying)(LONG lTraderID);
//
//	IMPLEMENT_BSTRT_PROPERTY(DatabaseString, m_bstrDatabaseString)
//
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsTraderColl*,			Trader,			m_spTraderColl);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsTraderGroupColl*,		TraderGroup,	m_spTraderGroup);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsStrategyColl*,		Strategy,		m_spStrategy);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsBrokerColl*,			Broker,			m_spBroker);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsBrokerColl*,			ClearingBroker, m_spClearingBroker);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IUndColl*,				Underlying,		m_spUnderlying);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IUndColl*,				UnderlyingAll,	m_spUnderlyingAll);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IUndColl*,				Stock,			m_spStock);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsOptRootByNameColl*,	OptRootByName,	m_spOptRootByName);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsContractColl*,		ContractAll,	m_spContractAll);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsContractColl*,		Contract,		m_spContract);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsUndGroupColl*,		UnderlyingGroup,m_spUnderlyingGroup);
//
//	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*,	DefStkPriceProfile,	m_spDefStkPriceProfile);
//	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*,	DefIdxPriceProfile,	m_spDefIdxPriceProfile);
//	IMPLEMENT_OBJECT_PROPERTY(IEtsPriceProfileAtom*,	DefOptPriceProfile,	m_spDefOptPriceProfile);
//	IMPLEMENT_OBJECT_PROPERTY(IEtsExpCalAtom*,			DefExpCalendar,		m_spDefExpCalendar);
//
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsPriceProfileColl*,	PriceProfile,		m_spPriceProfile);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsExpCalColl*,			ExpCalendar,		m_spExpCalendar);
//	IMPLEMENT_OBJECTREADONLY_PROPERTY(IExchColl*,			Exch,		m_spExhc);
//	
//};
//
//OBJECT_ENTRY_AUTO(__uuidof(EtsMain), CEtsMain)
