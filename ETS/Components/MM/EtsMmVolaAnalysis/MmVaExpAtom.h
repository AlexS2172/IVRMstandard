// MmVaExpAtom.h : Declaration of the CMmVaExpAtom
#ifndef __MMVAEXPATOM_H__
#define __MMVAEXPATOM_H__
#pragma once

#include "resource.h"       // main symbols
#include "EtsMmVolaAnalysis.h"
#include "MmVaStrikeColl.h"

_COM_SMARTPTR_TYPEDEF(IMmVaExpAtom, IID_IMmVaExpAtom);

struct __MmVaExpAtom
{
	//DATE					m_dtExpiryMonth;
	DATE					m_dtExpiry;
	DOUBLE					m_dRate;
	IMmVaStrikeCollPtr		m_spStrike;
	IMmVaStrikeAtomPtr		m_spAtmStrike;

	__MmVaExpAtom()
		: /*m_dtExpiryMonth(0.), */m_dtExpiry(0.), m_dRate(0.)
	{
	}
};

// CMmVaExpAtom

class ATL_NO_VTABLE CMmVaExpAtom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMmVaExpAtom, &CLSID_MmVaExpAtom>,
	public ISupportErrorInfoImpl<&IID_IMmVaExpAtom>,
	public IDispatchImpl<IMmVaExpAtom, &IID_IMmVaExpAtom, &LIBID_EtsMmVolaAnalysisLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __MmVaExpAtom
{
public:
	CMmVaExpAtom():m_pStrikeColl(NULL)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MMVAEXPATOM)


BEGIN_COM_MAP(CMmVaExpAtom)
	COM_INTERFACE_ENTRY(IMmVaExpAtom)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		try
		{
			__CHECK_HRESULT(CComObject<CMmVaStrikeColl>::CreateInstance(&m_pStrikeColl), _T("Fail to create strikes."));
			m_spStrike.Attach(m_pStrikeColl, true);
		}
		catch(const _com_error& e)
		{
			return Error((PTCHAR)CComErrorWrapper::ErrorDescription(e), IID_IMmVaExpAtom, e.Error());
		}
		return S_OK;
	}
	
	void FinalRelease() 
	{
		m_spStrike = NULL;
		m_spAtmStrike = NULL;
	}
private:
	CComObject<CMmVaStrikeColl>* m_pStrikeColl;
public:

	//IMPLEMENT_SIMPLE_PROPERTY(DATE, ExpiryMonth, m_dtExpiryMonth)
	IMPLEMENT_SIMPLE_PROPERTY(DATE, Expiry, m_dtExpiry)
	IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Rate, m_dRate)
	IMPLEMENT_OBJECTREADONLY_PROPERTY(IMmVaStrikeColl*, Strike, m_spStrike)
	IMPLEMENT_OBJECT_PROPERTY(IMmVaStrikeAtom*, AtmStrike, m_spAtmStrike)
	STDMETHOD(FindAtmStrike)(DOUBLE UnderlyingSpot);
};

OBJECT_ENTRY_AUTO(__uuidof(MmVaExpAtom), CMmVaExpAtom)

#endif //__MMVAEXPATOM_H__
