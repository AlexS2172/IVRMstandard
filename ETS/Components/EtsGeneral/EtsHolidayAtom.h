// EtsHolidayAtom.h : Declaration of the CEtsHolidayAtom

#pragma once
#include "resource.h"       // main symbols

#include "EtsGeneral.h"
// CEtsHolidayAtom

_COM_SMARTPTR_TYPEDEF(IEtsHolidayAtom, IID_IEtsHolidayAtom);

class ATL_NO_VTABLE CEtsHolidayAtom :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEtsHolidayAtom, &CLSID_EtsHolidayAtom>,
	public ISupportErrorInfoImpl<&IID_IEtsHolidayAtom>,
	public IDispatchImpl<IEtsHolidayAtom, &IID_IEtsHolidayAtom, &LIBID_EtsGeneralLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CEtsHolidayAtom()
	{
		m_vHoliday.clear();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ETSHOLIDAYATOM)


BEGIN_COM_MAP(CEtsHolidayAtom)
	COM_INTERFACE_ENTRY(IEtsHolidayAtom)
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

private:
	typedef	std::vector<long>		LongVector;
	typedef	LongVector::iterator	LVIterator;
	LongVector						m_vHoliday;
	
public:
	STDMETHOD(GetHolidays)(DATE dtToday, SAFEARRAY ** psaDates,  LONG* pnCount);
	STDMETHOD(Add)(DATE	dtDate);
	STDMETHOD(Remove)(DATE dtDate);
	STDMETHOD(GetPreviousWorkingDate)(DATE dtDate, DATE *dtPWDate);
	STDMETHOD(Clear)(void);
	STDMETHOD(TransformDividends)(SAFEARRAY ** psaDates, LONG nCount, SAFEARRAY **psaTDates, LONG *pnTCount);
};

OBJECT_ENTRY_AUTO(__uuidof(EtsHolidayAtom), CEtsHolidayAtom)
