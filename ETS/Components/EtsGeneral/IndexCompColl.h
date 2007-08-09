// IndexCompColl.h : Declaration of the CIndexCompColl
#ifndef __INDEXCOMPCOLL_H__
#define __INDEXCOMPCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "IndexCompAtom.h"

_COM_SMARTPTR_TYPEDEF(IIndexCompColl, IID_IIndexCompColl);

typedef IDispatchImpl<IIndexCompColl, &IID_IIndexCompColl, &LIBID_EtsGeneralLib>					IIndexCompCollDispImpl;
typedef ICollectionOnSTLMapOfInterfacePtrImpl<IIndexCompCollDispImpl, LONG, IIndexCompAtom, LONG >	IIndexCompCollImpl;

// CIndexCompColl
class ATL_NO_VTABLE CIndexCompColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIndexCompColl, &CLSID_IndexCompColl>,
	public ISupportErrorInfoImpl<&IID_IIndexCompColl>,
	public IIndexCompCollImpl
{
public:
	CIndexCompColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_INDEXCOMPCOLL)


BEGIN_COM_MAP(CIndexCompColl)
	COM_INTERFACE_ENTRY(IIndexCompColl)
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
		IIndexCompCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(LONG Key, IIndexCompAtom* Value, IIndexCompAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(IndexCompColl), CIndexCompColl)

#endif //__INDEXCOMPCOLL_H__