// EtsFutRootAtom.h : Declaration of the CEtsFutRootAtom
#ifndef __ETSFUTROOTATOM_H_
#define __ETSFUTROOTATOM_H_
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "EtsFutColl.h"

_COM_SMARTPTR_TYPEDEF(IEtsFutRootAtom, IID_IEtsFutRootAtom);

struct __EtsFutRootAtom
{
	LONG					m_nID;
	_bstr_t					m_bstrSymbol;
	_bstr_t					m_bstrName;
	_bstr_t					m_bstrQuotationUnitName;

	LONG					m_nUndID;
	LONG					m_nFutLotSize;
	LONG					m_nOptLotSize;
	LONG					m_nQuotationUnitID;
	DOUBLE					m_dTickSize;
	DOUBLE                  m_dTickValue;
	DOUBLE                  m_dPriceQuotationUnit;
	LONG	                m_lQuoteFormat;

	IEtsFutCollPtr			m_spFutures;

	__EtsFutRootAtom()
		: m_nID(0L)
		, m_nUndID(0L)
		, m_nFutLotSize(0L), m_nOptLotSize(0L), m_nQuotationUnitID(0L)
		, m_dTickSize(BAD_DOUBLE_VALUE)
		, m_dTickValue(BAD_DOUBLE_VALUE)
		, m_dPriceQuotationUnit(BAD_DOUBLE_VALUE)
		, m_lQuoteFormat(BAD_LONG_VALUE)

	{
	}
};

// CEtsFutRootAtom

class ATL_NO_VTABLE CEtsFutRootAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsFutRootAtom, &CLSID_EtsFutRootAtom>,
	public ISupportErrorInfoImpl<&IID_IEtsFutRootAtom>,
	public IDispatchImpl<IEtsFutRootAtom, &IID_IEtsFutRootAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __EtsFutRootAtom
{
public:
	CEtsFutRootAtom()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSFUTROOTATOM)


BEGIN_COM_MAP(CEtsFutRootAtom)
	COM_INTERFACE_ENTRY(IEtsFutRootAtom)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		try
		{
			_CHK(m_spFutures.CreateInstance(CLSID_EtsFutColl), _T("Fail to create futures."));
		}
		catch(const _com_error& e)
		{
			return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsFutRootAtom, e.Error());
		}
		return S_OK;
	}
	
	void FinalRelease() 
	{
		m_spFutures = NULL;
	}

public:
	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)

	IMPLEMENT_BSTRT_PROPERTY(Symbol, m_bstrSymbol)
	IMPLEMENT_BSTRT_PROPERTY(Name, m_bstrName)
	IMPLEMENT_BSTRT_PROPERTY(QuotationUnitName, m_bstrQuotationUnitName)

	IMPLEMENT_SIMPLE_PROPERTY(LONG, UndID, m_nUndID)
	IMPLEMENT_SIMPLE_PROPERTY(LONG, FutLotSize, m_nFutLotSize)
	IMPLEMENT_SIMPLE_PROPERTY(LONG, OptLotSize, m_nOptLotSize)	
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IEtsFutColl*, Futures, m_spFutures)
	IMPLEMENT_SIMPLE_PROPERTY(LONG, QuotationUnitID, m_nQuotationUnitID)

	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,		TickSize,			m_dTickSize)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,		TickValue,			m_dTickValue)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE,		PriceQuotationUnit,	m_dPriceQuotationUnit)
	IMPLEMENT_SIMPLE_PROPERTY(LONG,		QuoteFormat,		m_lQuoteFormat)
};

OBJECT_ENTRY_AUTO(__uuidof(EtsFutRootAtom), CEtsFutRootAtom)

#endif //__ETSFUTROOTATOM_H_