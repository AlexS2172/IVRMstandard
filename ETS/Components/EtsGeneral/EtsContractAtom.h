// EtsContractAtom.h : Declaration of the CEtsContractAtom
#ifndef __ETSCONTRACTATOM_H_
#define __ETSCONTRACTATOM_H_
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "UndAtom.h"
#include "EtsFutAtom.h"
#include "EtsFutRootAtom.h"

_COM_SMARTPTR_TYPEDEF(IEtsContractAtom, IID_IEtsContractAtom);

struct __EtsContractAtom
{
	IUndAtomPtr				m_spUnd;
	IEtsFutRootAtomPtr		m_spFutRoot;
	IEtsFutAtomPtr			m_spFut;

	__EtsContractAtom()
	{
	}
};

// CEtsContractAtom

class ATL_NO_VTABLE CEtsContractAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsContractAtom, &CLSID_EtsContractAtom>,
	public ISupportErrorInfoImpl<&IID_IEtsContractAtom>,
	public IDispatchImpl<IEtsContractAtom, &IID_IEtsContractAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __EtsContractAtom
{
public:
	CEtsContractAtom()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSCONTRACTATOM)


BEGIN_COM_MAP(CEtsContractAtom)
	COM_INTERFACE_ENTRY(IEtsContractAtom)
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
		m_spFut = NULL;
		m_spFutRoot = NULL;
		m_spUnd = NULL;
	}

public:
	IMPLEMENT_OBJECT_PROPERTY(IUndAtom*, Und, m_spUnd)
	IMPLEMENT_OBJECT_PROPERTY(IEtsFutRootAtom*, FutRoot, m_spFutRoot)
	IMPLEMENT_OBJECT_PROPERTY(IEtsFutAtom*, Fut, m_spFut)

	STDMETHOD(get_ID)(LONG* pRetVal);
	STDMETHOD(get_ContractType)(enum EtsContractTypeEnum* pRetVal);
	STDMETHOD(get_Symbol)(BSTR* pRetVal);
	STDMETHOD(get_ContractName)(BSTR* pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsContractAtom), CEtsContractAtom)

#endif //__ETSCONTRACTATOM_H_