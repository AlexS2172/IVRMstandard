// EtsOptRootAtom.h : Declaration of the CEtsOptRootAtom
#ifndef __ETSOPTROOTATOM_H_
#define __ETSOPTROOTATOM_H_
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"

_COM_SMARTPTR_TYPEDEF(IEtsOptRootAtom, IID_IEtsOptRootAtom);

struct __EtsOptRootAtom
{
	LONG					m_nID;
	CComBSTR				m_bstrName;
	LONG					m_nLotSize;
	VARIANT_BOOL			m_bIsSynth;
	VARIANT_BOOL            m_bIsFittingEnabled;
	LONG					m_nUndID;

	__EtsOptRootAtom()
		: m_nID(0L), m_nLotSize(0L), m_bIsSynth(VARIANT_FALSE), m_bIsFittingEnabled(VARIANT_TRUE)
	{
	}
};

// CEtsOptRootAtom

class ATL_NO_VTABLE CEtsOptRootAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsOptRootAtom, &CLSID_EtsOptRootAtom>,
	public ISupportErrorInfoImpl<&IID_IEtsOptRootAtom>,
	public IDispatchImpl<IEtsOptRootAtom, &IID_IEtsOptRootAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __EtsOptRootAtom
{
public:
	CEtsOptRootAtom()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSOPTROOTATOM)


BEGIN_COM_MAP(CEtsOptRootAtom)
	COM_INTERFACE_ENTRY(IEtsOptRootAtom)
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
	}

public:
	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_nID)
	IMPLEMENT_BSTR_PROPERTY(Name, m_bstrName)
	IMPLEMENT_SIMPLE_PROPERTY(LONG, LotSize, m_nLotSize)
	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsSynth, m_bIsSynth)
	IMPLEMENT_SIMPLE_PROPERTY(LONG, UndID, m_nUndID)
	IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, IsFit, m_bIsFittingEnabled)

};

OBJECT_ENTRY_AUTO(__uuidof(EtsOptRootAtom), CEtsOptRootAtom)

#endif //__ETSOPTROOTATOM_H_