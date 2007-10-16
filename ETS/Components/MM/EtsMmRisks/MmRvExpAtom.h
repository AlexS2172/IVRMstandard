// MmRvExpAtom.h : Declaration of the CMmRvExpAtom

#pragma once
#include "resource.h"       // main symbols

#include "EtsMmRisks.h"
#include "MmRvPosColl.h"

_COM_SMARTPTR_TYPEDEF(IMmRvExpAtom, IID_IMmRvExpAtom);

struct __MmRvExpAtom
{
	LONG					m_nExpiryMonth;
	DATE					m_dtExpiry;
	DOUBLE					m_dRate;
	IMmRvPosCollPtr			m_spPos;
	IMmRvSynthGreeksCollPtr m_spSynthGreek;
	DOUBLE					m_dDeltaInShares;
	DOUBLE					m_dDeltaEq;
	DOUBLE					m_dGammaInShares;
	DOUBLE					m_dGammaEq;
	DOUBLE					m_dVegaInShares;
	DOUBLE					m_dTimeValueInShares;
	VARIANT_BOOL			m_bBadDeltaInShares;
	VARIANT_BOOL			m_bBadRhoInShares;
	VARIANT_BOOL			m_bBadDeltaEq;
	VARIANT_BOOL			m_bBadGammaInShares;
	VARIANT_BOOL			m_bBadGammaEq;
	VARIANT_BOOL			m_bBadVegaInShares;
	VARIANT_BOOL			m_bBadTimeValueInShares;
	VARIANT_BOOL			m_bHasSynth;
	DOUBLE					m_dRhoInShares;

	__MmRvExpAtom()
		: m_nExpiryMonth(0L), m_dtExpiry(0.), m_dRate(0.),
		m_dDeltaInShares(BAD_DOUBLE_VALUE), m_dDeltaEq(BAD_DOUBLE_VALUE),
		m_dGammaInShares(BAD_DOUBLE_VALUE), m_dGammaEq(BAD_DOUBLE_VALUE),
		m_dVegaInShares(BAD_DOUBLE_VALUE), m_dTimeValueInShares(BAD_DOUBLE_VALUE),
		m_bBadDeltaInShares(VARIANT_FALSE), m_bBadDeltaEq(VARIANT_FALSE),
		m_bBadGammaInShares(VARIANT_FALSE), m_bBadGammaEq(VARIANT_FALSE),
		m_bBadVegaInShares(VARIANT_FALSE), m_bBadTimeValueInShares(VARIANT_FALSE),
		m_bHasSynth(VARIANT_FALSE),m_dRhoInShares(BAD_DOUBLE_VALUE),
		m_bBadRhoInShares(VARIANT_FALSE)
	{
	}

	void ClearValues()
	{
		m_dDeltaInShares = BAD_DOUBLE_VALUE;
		m_dDeltaEq = BAD_DOUBLE_VALUE;
		m_dGammaInShares = BAD_DOUBLE_VALUE;
		m_dGammaEq = BAD_DOUBLE_VALUE;
		m_dVegaInShares = BAD_DOUBLE_VALUE;
		m_dTimeValueInShares = BAD_DOUBLE_VALUE;

		m_bBadDeltaInShares = VARIANT_FALSE;
		m_bBadDeltaEq = VARIANT_FALSE;
		m_bBadGammaInShares = VARIANT_FALSE;
		m_bBadGammaEq = VARIANT_FALSE;
		m_bBadVegaInShares = VARIANT_FALSE;
		m_bBadTimeValueInShares = VARIANT_FALSE;
		m_dRhoInShares = BAD_DOUBLE_VALUE;
		m_bBadRhoInShares = VARIANT_FALSE;
	}
};


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CMmRvExpAtom

class ATL_NO_VTABLE CMmRvExpAtom :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMmRvExpAtom, &CLSID_MmRvExpAtom>,
	public ISupportErrorInfoImpl<&IID_IMmRvExpAtom>,
	public IDispatchImpl<IMmRvExpAtom, &IID_IMmRvExpAtom, &LIBID_EtsMmRisksLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public __MmRvExpAtom

{
public:
	CMmRvExpAtom()
		:m_pPos(NULL)

	{
		m_pUnkMarshaler = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MMRVEXPATOM)


BEGIN_COM_MAP(CMmRvExpAtom)
	COM_INTERFACE_ENTRY(IMmRvExpAtom)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		_CHK(CComObject<CMmRvPosColl>::CreateInstance(&m_pPos),  _T("Fail to create positions."));
		m_spPos.Attach(m_pPos, TRUE);

		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;
public:
	void	CalcTotals();
	double	GetCoeff();
private:
	void CalcSynthetictotals(CMmRvPosAtom* pPos);
	void ClearSyntheticsValues();

public:
	CComObject<CMmRvPosColl>* m_pPos;
public:

		IMPLEMENT_SIMPLE_PROPERTY(LONG, ExpiryMonth, m_nExpiryMonth)
		IMPLEMENT_SIMPLE_PROPERTY(DATE, Expiry, m_dtExpiry)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, Rate, m_dRate)
		IMPLEMENT_OBJECTREADONLY_PROPERTY(IMmRvPosColl*, Pos, m_spPos)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DeltaInShares, m_dDeltaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, DeltaEq, m_dDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaInShares, m_dGammaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, GammaEq, m_dGammaEq)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, VegaInShares, m_dVegaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, TimeValueInShares, m_dTimeValueInShares)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadDeltaInShares, m_bBadDeltaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadDeltaEq, m_bBadDeltaEq)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadGammaInShares, m_bBadGammaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadGammaEq, m_bBadGammaEq)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadVegaInShares, m_bBadVegaInShares)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadTimeValueInShares, m_bBadTimeValueInShares)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, HasSynth, m_bHasSynth)
		IMPLEMENT_SIMPLE_PROPERTY(VARIANT_BOOL, BadRhoInShares, m_bBadRhoInShares)
		IMPLEMENT_OBJECTREADONLY_PROPERTY(IMmRvSynthGreeksColl*, SynthGreek, m_spSynthGreek)
		IMPLEMENT_SIMPLE_PROPERTY(DOUBLE, RhoInShares,m_dRhoInShares)

		STDMETHODIMP ClearValues()
	{
		__MmRvExpAtom::ClearValues();
		return S_OK;
	}


};

OBJECT_ENTRY_AUTO(__uuidof(MmRvExpAtom), CMmRvExpAtom)
