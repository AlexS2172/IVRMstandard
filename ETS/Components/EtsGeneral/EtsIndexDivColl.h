// EtsIndexDivColl.h : Declaration of the CEtsIndexDivColl

#pragma once
#include "resource.h"       // main symbols

#include "EtsGeneral.h"

#include "EtsIndexDivAtom.h"


// CEtsIndexDivColl

_COM_SMARTPTR_TYPEDEF(IEtsIndexDivColl, IID_IEtsIndexDivColl);

class CEtsIndexDivColl;
typedef IDispatchImpl<IEtsIndexDivColl, &IID_IEtsIndexDivColl, &LIBID_EtsGeneralLib>		IEtsIndexDivCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IEtsIndexDivCollDispImpl, IEtsIndexDivAtom, LONG, LONG, LONG, LONG  >	IEtsIndexDivCollImpl;



class ATL_NO_VTABLE CEtsIndexDivColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsIndexDivColl, &CLSID_EtsIndexDivColl>,
	public ISupportErrorInfoImpl<&CLSID_EtsIndexDivColl>,
	public IEtsIndexDivCollImpl
{
	typedef std::map<long, double> CWeightsCollection;
public:
	CEtsIndexDivColl()
		:m_nTodayCache(0L)
		,m_nExpiryCache(0L)
	{
	}

	BEGIN_PROP_MAP(CEtsIndexDivColl)
	END_PROP_MAP()



DECLARE_REGISTRY_RESOURCEID(IDR_ETSINDEXDIVCOLL)


BEGIN_COM_MAP(CEtsIndexDivColl)
	COM_INTERFACE_ENTRY(IEtsIndexDivColl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
		IEtsIndexDivCollImpl::Clear();
	}

private:
	IEtsDivCollPtr m_spCustomDivsCache;
	LONG m_nTodayCache;
	LONG m_nExpiryCache;

	IEtsDivCollPtr GetCachedDividends(long nToday, long nExpiry);


private:
	CWeightsCollection m_collWeights;
public:
	STDMETHOD(Add)(LONG Key, LONG SortKey, IEtsIndexDivAtom* Value, IEtsIndexDivAtom** pRetVal);
	STDMETHOD(CopyToWithWeight)( DOUBLE dWeight, IEtsIndexDivColl* pDest , IEtsIndexDivColl** ppVal);
	STDMETHOD(GetDividends)( LONG nToday,  LONG nExpiry,  LONG nCount, SAFEARRAY ** psaDivAmounts, SAFEARRAY ** psaDivDates,  LONG* pnCount);
	STDMETHOD(GetNearest)( LONG nToday,  LONG nExpiry,  DOUBLE* pdDivAmount,  DOUBLE* pdDivDate);
	STDMETHOD(GetDividendCount)( LONG nToday,  LONG nExpiry,  LONG* pnCount);
	STDMETHOD(SetWeight)(LONG nKey, DOUBLE dWeight);

};

OBJECT_ENTRY_AUTO(__uuidof(EtsIndexDivColl), CEtsIndexDivColl)
