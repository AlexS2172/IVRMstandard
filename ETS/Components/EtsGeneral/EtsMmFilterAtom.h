// EtsMmFilterAtom.h : Declaration of the CEtsMmFilterAtom

#pragma once
#include "resource.h"       // main symbols

#include "EtsGeneral.h"


_COM_SMARTPTR_TYPEDEF(IEtsMmFilterAtom, IID_IEtsMmFilterAtom);

// CEtsMmFilterAtom
class _CEtsMmFilterAtom
{
public:
	long m_lID;
	_CEtsMmFilterAtom()
	:m_lID(0L)
	{}
};

class ATL_NO_VTABLE CEtsMmFilterAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsMmFilterAtom, &CLSID_EtsMmFilterAtom>,
	public ISupportErrorInfoImpl<&IID_IEtsMmFilterAtom>,
	public IDispatchImpl<IEtsMmFilterAtom, &IID_IEtsMmFilterAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public _CEtsMmFilterAtom
{
public:
	CEtsMmFilterAtom()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSMMFILTERATOM)


BEGIN_COM_MAP(CEtsMmFilterAtom)
	COM_INTERFACE_ENTRY(IEtsMmFilterAtom)
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
	IMPLEMENT_SIMPLE_PROPERTY(LONG, ID, m_lID);

};

OBJECT_ENTRY_AUTO(__uuidof(EtsMmFilterAtom), CEtsMmFilterAtom)
