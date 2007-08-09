// MmTradeInfoColl.h : Declaration of the CMmTradeInfoColl
#ifndef __MM_TRADE_INFO_COLL_H__
#define __MM_TRADE_INFO_COLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsMmGeneral.h"
#include "MmTradeInfoAtom.h"

_COM_SMARTPTR_TYPEDEF(IMmTradeInfoColl, IID_IMmTradeInfoColl);

typedef IDispatchImpl<IMmTradeInfoColl, &IID_IMmTradeInfoColl, &LIBID_EtsMmGeneralLib>								IMmTradeInfoCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IMmTradeInfoCollDispImpl, IMmTradeInfoAtom, LONG, LONG, DATE, DATE>	IMmTradeInfoCollImpl;


// CMmTradeInfoColl

class ATL_NO_VTABLE CMmTradeInfoColl : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMmTradeInfoColl, &CLSID_MmTradeInfoColl>,
	public ISupportErrorInfoImpl<&IID_IMmTradeInfoColl>,
	public IMmTradeInfoCollImpl
{
public:
	CMmTradeInfoColl()
	{
		m_pUnkMarshaler = NULL;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MMTRADEINFOCOLL)
	DECLARE_GET_CONTROLLING_UNKNOWN()

	DECLARE_NOT_AGGREGATABLE(CMmTradeInfoColl)

	BEGIN_COM_MAP(CMmTradeInfoColl)
		COM_INTERFACE_ENTRY(IMmTradeInfoColl)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_itCurrentPosition = m_coll.begin();
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
		return S_OK;
	}

	void FinalRelease() 
	{
		IMmTradeInfoCollImpl::Clear();
		m_pUnkMarshaler.Release();

	}
	CComPtr<IUnknown> m_pUnkMarshaler;

public:
	void FilterData(/*long* filterData,*/ IEtsFilterDataPtr spFilterData, IEtsMainPtr spMain, CTradeInfoViewData&  vecShow);

private:
	EnumCollType::iterator  m_itCurrentPosition; 

public:

	STDMETHOD(Add)(LONG Key, DATE SortKey, IMmTradeInfoAtom* Value, IMmTradeInfoAtom** pRetVal);
	STDMETHOD(Clone)(IMmTradeInfoColl** ppSrcColl);
	STDMETHOD(get_FilterTrades)(IEtsFilterData* pFilter,
								IEtsUndGroupColl* pGroupCol,
								VARIANT_BOOL bActual,
								VARIANT_BOOL bSkipFutContracts,
								VARIANT_BOOL bFutWithDerivative,
								IMmTradeInfoColl** pVal);

	STDMETHOD(ResetTradesPosition)();
	STDMETHOD(MoveNextTrade)(VARIANT_BOOL* bIsLast);
	STDMETHOD(get_TradeAtCurrentPosition)(IMmTradeInfoAtom** pDest);
	STDMETHOD(GetFirstTrade)(IMmTradeInfoAtom** pDest);

private:
	bool IsToday( IMmTradeInfoAtomPtr pTradeInfoAtom , bool bAdnSimulated = false ) ;
	bool IsSimulated (IMmTradeInfoAtomPtr pTradeInfoAtom ) ;
	bool IsOpenPos (IMmTradeInfoAtomPtr pTradeInfoAtom, bool bAdnSimulated = false ) ;
};

OBJECT_ENTRY_AUTO(__uuidof(MmTradeInfoColl), CMmTradeInfoColl)

#endif //__MM_TRADE_INFO_COLL_H__