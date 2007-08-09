// ExchColl.h : Declaration of the CExchColl
#ifndef __EXCHCOLL_H__
#define __EXCHCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "ExchAtom.h"

typedef IDispatchImpl<IExchColl, &IID_IExchColl, &LIBID_EtsGeneralLib>										IExchCollDispImpl;
typedef ICollectionOnSTLMapExOfInterfacePtrImpl<IExchCollDispImpl, IExchAtom, LONG, LONG, BSTR, _bstr_t  >	IExchCollImpl;
_COM_SMARTPTR_TYPEDEF(IExchColl, IID_IExchColl);


// CExchColl
class ATL_NO_VTABLE CExchColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExchColl, &CLSID_ExchColl>,
	public ISupportErrorInfoImpl<&IID_IExchColl>,
	public IExchCollImpl
{
public:
	CExchColl()	{}

DECLARE_REGISTRY_RESOURCEID(IDR_EXCHCOLL)


BEGIN_COM_MAP(CExchColl)
	COM_INTERFACE_ENTRY(IExchColl)
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
		IExchCollImpl::Clear();

	}

public:

	STDMETHOD(Add)(LONG Key, BSTR SortKey, IExchAtom* Value, IExchAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(ExchColl), CExchColl)

#endif //__EXCHCOLL_H__
