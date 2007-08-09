// SynthRootColl.h : Declaration of the CSynthRootColl
#ifndef __SYNTHROOTCOLL_H__
#define __SYNTHROOTCOLL_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"
#include "SynthRootAtom.h"


_COM_SMARTPTR_TYPEDEF(ISynthRootColl, IID_ISynthRootColl);

typedef IDispatchImpl<ISynthRootColl, &IID_ISynthRootColl, &LIBID_EtsGeneralLib>					ISynthRootCollDispImpl;
typedef ICollectionOnSTLMapOfInterfacePtrImpl<ISynthRootCollDispImpl, LONG, ISynthRootAtom, LONG >	ISynthRootCollImpl;

// CSynthRootColl

class ATL_NO_VTABLE CSynthRootColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSynthRootColl, &CLSID_SynthRootColl>,
	public ISupportErrorInfoImpl<&IID_ISynthRootColl>,
	public ISynthRootCollImpl
{
public:
	CSynthRootColl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SYNTHROOTCOLL)


BEGIN_COM_MAP(CSynthRootColl)
	COM_INTERFACE_ENTRY(ISynthRootColl)
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
		ISynthRootCollImpl::Clear();
	}

public:

	STDMETHOD(Add)(LONG Key, ISynthRootAtom* Value, ISynthRootAtom** pRetVal);
};

OBJECT_ENTRY_AUTO(__uuidof(SynthRootColl), CSynthRootColl)

#endif //__SYNTHROOTCOLL_H__
