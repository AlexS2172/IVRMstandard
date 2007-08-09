// EtsTraderUndAtom.h : Declaration of the CEtsTraderUndAtom
#ifndef __ETSTRADERUNDATOM_H__
#define __ETSTRADERUNDATOM_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "UndAtom.h"
#include "EtsStrategyColl.h"

_COM_SMARTPTR_TYPEDEF(IEtsTraderUndAtom, IID_IEtsTraderUndAtom);

struct __EtsTraderUndAtom
{
	IUndAtomPtr				m_spUnd;
	IEtsStrategyCollPtr		m_spStrategy;

	__EtsTraderUndAtom()
	{
	}
};

// CEtsTraderUndAtom

class ATL_NO_VTABLE CEtsTraderUndAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsTraderUndAtom, &CLSID_EtsTraderUndAtom>,
	public ISupportErrorInfoImpl<&IID_IEtsTraderUndAtom>,
	public IDispatchImpl<IEtsTraderUndAtom, &IID_IEtsTraderUndAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __EtsTraderUndAtom
{
public:
	CEtsTraderUndAtom()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSTRADERUNDATOM)


BEGIN_COM_MAP(CEtsTraderUndAtom)
	COM_INTERFACE_ENTRY(IEtsTraderUndAtom)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		try
		{
			CComObject<CEtsStrategyColl>* pCreator = NULL;
			_CHK(CComObject<CEtsStrategyColl>::CreateInstance(&pCreator), _T("Fail to create underlying strategies."));
			m_spStrategy.Attach(pCreator, TRUE);
		}
		catch(const _com_error& e)
		{
			return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IEtsTraderUndAtom, e.Error());
		}
		return S_OK;
	}
	
	void FinalRelease() 
	{
		m_spUnd = NULL;
		m_spStrategy = NULL;
	}

public:

	IMPLEMENT_OBJECT_PROPERTY(IUndAtom*, Und, m_spUnd);
	IMPLEMENT_OBJECT_PROPERTY(IEtsStrategyColl*, Strategy, m_spStrategy);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsTraderUndAtom), CEtsTraderUndAtom)

#endif //__ETSTRADERUNDATOM_H__
