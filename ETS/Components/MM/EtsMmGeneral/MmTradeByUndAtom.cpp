// MmTradeByUndAtom.cpp : Implementation of CMmTradeByUndAtom

#include "stdafx.h"
#include "MmTradeInfoAtom.h"
#include "MmTradeByUndAtom.h"


// CMmTradeByUndAtom

STDMETHODIMP CMmTradeByUndAtom::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMmTradeByUndAtom
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
/*
HRESULT CMmTradeByUndAtom::PersistSave(LPSTREAM pStream, BOOL bClearDirty, ATL_PROPMAP_ENTRY* pMap)
{
	HRESULT hr = S_OK;
	ULONG ret = 0;
	try
	{
		// Simple type properties (all):
		__CHECK_HRESULT3(pStream->Write(static_cast<__MmTradeByUndAtomBaseTypes*>(this), sizeof(__MmTradeByUndAtomBaseTypes), &ret));
		
		__CHECK_HRESULT3(m_bsKey.WriteToStream(pStream));

		// Object property:
		CComQIPtr<IPersistStreamInit> spPersistRoots(m_spTrd);
		ATLASSERT(spPersistRoots!=NULL);
		if(spPersistRoots!=NULL)
			__CHECK_HRESULT3(spPersistRoots->Save(pStream, bClearDirty));
	}
	catch (_com_error& e) 
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), __uuidof(IMmTradeByUndAtom), e.Error());
	}
	catch(...)
	{
		hr =  Error( _T("Unhandled exception handled at PersistSave"), __uuidof(IMmTradeByUndAtom), E_FAIL);
	}
	return hr;

}

HRESULT CMmTradeByUndAtom::PersistLoad(LPSTREAM pStream, ATL_PROPMAP_ENTRY* pMap)
{
	HRESULT hr = S_OK;
	ULONG ret = 0;
	try
	{
		// Simple type properties (all):
		__CHECK_HRESULT3(pStream->Read(static_cast<__MmTradeByUndAtomBaseTypes*>(this), sizeof(__MmTradeByUndAtomBaseTypes), &ret));
		
		m_bsKey.Empty();
		__CHECK_HRESULT3(m_bsKey.ReadFromStream(pStream));

		// Object property	
		m_spTrd = NULL;
		CComObject<CMmTradeInfoColl>* pNewObj;
		__CHECK_HRESULT(CComObject<CMmTradeInfoColl>::CreateInstance(&pNewObj), _T("Failed to create trade coll"));
		m_spTrd.Attach(pNewObj, TRUE);
		IPersistStreamInit* pStreamInt = static_cast<IPersistStreamInit*>(pNewObj);
		__CHECK_HRESULT3(pStreamInt->Load(pStream));
	}
	catch (_com_error& e) 
	{
		hr =  Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(e), __uuidof(IMmTradeByUndAtom), e.Error());
	}
	catch(...)
	{
		hr =  Error( _T("Unhandled exception handled at PersistSave"), __uuidof(IMmTradeByUndAtom), E_FAIL);
	}
	return hr;
}
// CEtsTraderUndAtom
*/