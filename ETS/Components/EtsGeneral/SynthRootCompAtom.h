// SynthRootCompAtom.h : Declaration of the CSynthRootCompAtom

#ifndef __SYNTROOTCOMPATOM_H__
#define __SYNTROOTCOMPATOM_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsGeneral.h"


_COM_SMARTPTR_TYPEDEF(ISynthRootCompAtom, IID_ISynthRootCompAtom);

struct __SynthRootCompAtom
{
	LONG			m_nUndID;
	DOUBLE			m_dWeight;
	DOUBLE          m_dSettlement;

	__SynthRootCompAtom()
		: m_nUndID(0L), m_dWeight(0.), m_dSettlement(0.)
	{
	}
};

// CSynthRootCompAtom

class ATL_NO_VTABLE CSynthRootCompAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSynthRootCompAtom, &CLSID_SynthRootCompAtom>,
	public ISupportErrorInfoImpl<&IID_ISynthRootCompAtom>,
	public IDispatchImpl<ISynthRootCompAtom, &IID_ISynthRootCompAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __SynthRootCompAtom
{
public:
	CSynthRootCompAtom()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SYNTHROOTCOMPATOM)


BEGIN_COM_MAP(CSynthRootCompAtom)
	COM_INTERFACE_ENTRY(ISynthRootCompAtom)
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

	IMPLEMENT_SIMPLE_PROPERTY(LONG, UndID,			m_nUndID);
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Weight,		m_dWeight);
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Settlement,   m_dSettlement);

};

OBJECT_ENTRY_AUTO(__uuidof(SynthRootCompAtom), CSynthRootCompAtom)

#endif //__SYNTROOTCOMPATOM_H__