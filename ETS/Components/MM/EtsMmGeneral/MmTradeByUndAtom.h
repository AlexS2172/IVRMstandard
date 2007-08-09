// MmTradeByUndAtom.h : Declaration of the CMmTradeByUndAtom

#pragma once
#include "resource.h"       // main symbols
#include "MmTradeInfoColl.h"

#include "EtsMmGeneral.h"
#ifndef __MM_TRADE_BYUND_ATOM_H__
#define __MM_TRADE_BYUND_ATOM_H__

#pragma once

_COM_SMARTPTR_TYPEDEF(IMmTradeByUndAtom, IID_IMmTradeByUndAtom);

struct __MmTradeByUndAtomBaseTypes
{
	DOUBLE	m_dSortKey;
};



struct __MmTradeByUndAtom: public __MmTradeByUndAtomBaseTypes
{
	IMmTradeInfoCollPtr			m_spTrd;
	_bstr_t						m_bsKey;

	__MmTradeByUndAtom() 
	{
	}
};

// CMmTradeByUndAtom

class ATL_NO_VTABLE CMmTradeByUndAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMmTradeByUndAtom, &CLSID_MmTradeByUndAtom>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMmTradeByUndAtom, &IID_IMmTradeByUndAtom, &LIBID_EtsMmGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __MmTradeByUndAtom
{
public:
	
	CMmTradeByUndAtom()//:m_bRequiresSave(true)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MMTRADEBYUNDATOM)

BEGIN_PROP_MAP(CMmTradeByUndAtom)
END_PROP_MAP()

BEGIN_COM_MAP(CMmTradeByUndAtom)
	COM_INTERFACE_ENTRY(IMmTradeByUndAtom)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
//	COM_INTERFACE_ENTRY(IPersistStreamInit)
//	COM_INTERFACE_ENTRY(IPersistStream)
END_COM_MAP()
/*
private:
	HRESULT PersistSave(LPSTREAM pStream, BOOL bClearDirty, ATL_PROPMAP_ENTRY* pMap);
	HRESULT PersistLoad(LPSTREAM pStream, ATL_PROPMAP_ENTRY* pMap);

public:
	bool      m_bRequiresSave;

	STDMETHOD(IPersistStreamInit_Save)(LPSTREAM pStream, BOOL bClearDirty, ATL_PROPMAP_ENTRY* pMap){return PersistSave(pStream, bClearDirty, pMap);}
	STDMETHOD(IPersistStreamInit_Load)(LPSTREAM pStream, ATL_PROPMAP_ENTRY* pMap){return PersistLoad( pStream,  pMap);}
	STDMETHOD(IEgPersistStream_Save)(LPSTREAM pStream, BOOL bClearDirty, ATL_PROPMAP_ENTRY* pMap){return PersistSave(pStream, bClearDirty, pMap);}
	STDMETHOD(IEgPersistStream_Load)(LPSTREAM pStream, ATL_PROPMAP_ENTRY* pMap){return PersistLoad( pStream,  pMap);}
*/


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		try
		{
			CComObject<CMmTradeInfoColl>* pObject = NULL;
			_CHK(CComObject<CMmTradeInfoColl>::CreateInstance(&pObject), _T("Fail to create trades by underlying collection"));
			m_spTrd.Attach(pObject, TRUE);
		}
		catch(const _com_error& e)
		{
			return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), IID_IMmTradeByUndAtom, e.Error());
		}
		return S_OK;
	}
	
	void FinalRelease() 
	{
		m_spTrd = NULL;
	}

public:
	IMPLEMENT_OBJECT_PROPERTY( IMmTradeInfoColl* , Trd , m_spTrd )
	IMPLEMENT_BSTRT_PROPERTY(bsKey, m_bsKey)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, dSortKey, m_dSortKey)

};

OBJECT_ENTRY_AUTO(__uuidof(MmTradeByUndAtom), CMmTradeByUndAtom)

#endif //__MM_TRADE_BYUND_ATOM_H__