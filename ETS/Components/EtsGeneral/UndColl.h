// UndColl.h : Declaration of the CUndColl
#ifndef __UNDCOLL_H__
#define __UNDCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "UndAtom.h"

_COM_SMARTPTR_TYPEDEF(IUndColl, IID_IUndColl);

typedef IDispatchImpl<IUndColl, &IID_IUndColl, &LIBID_EtsGeneralLib>													IUndCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IUndCollDispImpl, IUndAtom, LONG, LONG, BSTR, _bstr_t >	IUndCollImpl;

// CUndColl
class ATL_NO_VTABLE CUndColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUndColl, &CLSID_UndColl>,
	public ISupportErrorInfoImpl<&IID_IUndColl>,
	public IUndCollImpl
{
public:
	CUndColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_UNDCOLL)


BEGIN_COM_MAP(CUndColl)
	COM_INTERFACE_ENTRY(IUndColl)
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
		IUndCollImpl::Clear();
	}

public:
	IUndAtomPtr AddNew(long lID, _bstr_t bsSymbol, CComObject<CUndAtom>** pAtom = NULL);

public:

	STDMETHOD(Add)(LONG Key, BSTR SortKey, IUndAtom* Value, IUndAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(UndColl), CUndColl)

#endif //__UNDCOLL_H__