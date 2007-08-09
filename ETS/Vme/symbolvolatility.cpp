// SymbolVolatility.cpp : Implementation of CSymbolVolatility
#include "stdafx.h"
#include "VME.h"
#include "SymbolVolatility.h"

#include "VolatilitySource.h"

_ATL_FUNC_INFO CSymbolVolatility::m_OnVMESurfaceInfo = 
	{CC_STDCALL, VT_EMPTY, 2, {VT_DISPATCH, VT_DISPATCH}};

/////////////////////////////////////////////////////////////////////////////
// Construction/destruction/initialization
/////////////////////////////////////////////////////////////////////////////
CSymbolVolatility::CSymbolVolatility(): 
	m_bInitialized(false),
	m_bEnableEvents(VARIANT_TRUE),
	m_bEnableCache(VARIANT_FALSE),
	m_bEnableEditing(VARIANT_FALSE),
	m_pSource(NULL), 
	m_nSurfaceID(0), 
	m_enOptType(OTM)
{
}


HRESULT CSymbolVolatility::FinalConstruct()
{
	try
	{
		__CHECK_HRESULT( m_spSymbolObject.CreateInstance( CLSID_SymbolObject ), _T("Error creating publisher symbol object.") );
		__CHECK_HRESULT( m_spVMESurface.CreateInstance( CLSID_VMESurface ), _T("Error creating publisher data object.") );
	}
	catch( const _com_error& e )
	{
		return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
	}

	return S_OK;
}


void CSymbolVolatility::FinalRelease()
{
	//UnregisterPublisher();

	m_spSymbolObject = NULL;
	m_spVMESurface   = NULL;
}


STDMETHODIMP CSymbolVolatility::Init( CVolatilitySource* pSource, const _bstr_t& bsSymbolName, SYMBOL_TYPE enSymbolType )
{
	__CHECK_POINTER( pSource );

	try
	{
		ObjectLock lock(this);

		if( m_bInitialized )
			Deinit();

		m_pSource = pSource;
		m_spDS	  = pSource->m_spDS;

		m_bsSymbolName = bsSymbolName;
		m_enSymbolType = enSymbolType == 0 ? m_enSymbolType : enSymbolType;

		m_bInitialized = true;
	}
	catch( const _com_error& e )
	{
		//return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		return CComErrorWrapper::SetError(e, L"VolaControl", L"", __FILE__,__FUNCDNAME__,__LINE__);;

	}

	return S_OK;
}


STDMETHODIMP CSymbolVolatility::Deinit()
{
	try
	{
		ObjectLock lock(this);

		// Deinit() intentionaly skips symbol name and type clearing!!!

		m_pSource = NULL;
		m_spDS	  = NULL;

		m_bInitialized = false;
	}
	catch( const _com_error& e )
	{
		//return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		return CComErrorWrapper::SetError(e, L"VolaControl", L"", __FILE__,__FUNCDNAME__,__LINE__);;

	}

	return S_OK;
}


/*STDMETHODIMP CSymbolVolatility::RegisterPublisher()
{
	try
	{
		ObjectLock lock(this);

		__CHECK_HRESULT( m_spSymbolObject->Set( m_enSymbolType, m_bsSymbolName, _T(""), _T("") ), _T("Error setting publisher symbol object properties") );
	  
		if( m_spPubManager == NULL )
		{
			__CHECK_HRESULT( m_spPubManager.CreateInstance( CLSID_MsgManager ), _T("Error creating publisher instance.") );
			__CHECK_HRESULT( m_spPubManager->RegPublisher( enMtVola, m_spSymbolObject ), _T("Error registering publisher.") );
		}
		
		if( m_spSubManager == NULL )
		{
			m_spSubManager = m_spPubManager;
			__CHECK_INTERFACE_POINTER( m_spSubManager, _T("Error quering subscriber interface.") );

			// Advise for events
			__CHECK_HRESULT( DispEventAdvise( m_spSubManager ), _T("Error advising messaging source interface") );
			__CHECK_HRESULT( m_spSubManager->SubVola( m_spSymbolObject ), _T("Error subscribing for vola messages.") );
		}

	}
	catch( const _com_error& e )
	{
		//return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		return CComErrorWrapper::SetError(e, L"VolaControl", L"", __FILE__,__FUNCDNAME__,__LINE__);;
	}

	return S_OK;
}*/


/*STDMETHODIMP CSymbolVolatility::UnregisterPublisher()
{
	try
	{
		ObjectLock lock(this);

		ATLASSERT( m_spSymbolObject != NULL );
		if( m_spPubManager != NULL )
			__CHECK_HRESULT( m_spPubManager->UnregPublisher( enMtVola, m_spSymbolObject ), _T("Error unregistering publisher.") );
		//m_spPubManager = NULL;

		if( m_spSubManager != NULL )
		{
			__CHECK_HRESULT( DispEventUnadvise( m_spSubManager ), _T("Error unadvising messaging source interface") );
			__CHECK_HRESULT( m_spSubManager->UnsubVola( m_spSymbolObject ), _T("Error unsubscribing from volatility messages.") );
		}
		//m_spSubManager = NULL;
	}
	catch( const _com_error& e )
	{
		//return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		return CComErrorWrapper::SetError(e, L"VolaControl", L"", __FILE__,__FUNCDNAME__,__LINE__);;
	}
	
	return S_OK;
}*/


STDMETHODIMP CSymbolVolatility::EnableEvents( VARIANT_BOOL bEnable )
{
	ObjectLock lock(this);

	m_bEnableEvents = bEnable;

	return S_OK;
}


STDMETHODIMP CSymbolVolatility::EnableCache( VARIANT_BOOL bEnable )
{
	ObjectLock lock(this);

	m_bEnableCache = bEnable;

	return S_OK;
}


STDMETHODIMP CSymbolVolatility::EnableEditing( VARIANT_BOOL bEnable )
{
	ObjectLock lock(this);

	m_bEnableEditing = bEnable;

	return S_OK;
}


STDMETHODIMP CSymbolVolatility::DefaultVola( double dVola )
{
	ObjectLock lock(this);

	m_dDefaultVola = dVola;

	return S_OK;
}


STDMETHODIMP CSymbolVolatility::LoadData()
{
	try
	{
		ObjectLock lock(this);

		if( !m_spDS.GetInterfacePtr() )
			CComErrorWrapper::ThrowError( E_PENDING, _T("Error loading volatility surface - no data source provided.") );

		HRESULT hr;
		/*hr = m_spDS->raw_GenerateDefaultVolatilities( m_bsSymbolName, OTM, m_dDefaultVola );
		if( FAILED(hr) && hr != E_NOTIMPL )
			CComErrorWrapper::ThrowError( hr, _T("Error generating default volatilities.") );*/

		m_nSurfaceID = -1;
		hr = m_spDS->raw_GetDefaultSurfaceID( m_bsSymbolName, &m_nSurfaceID );

		if( SUCCEEDED(hr) )
		{
			// Prepare buffer
			m_data.ClearAll();

			// Get vola surface for specified mode
			_RecordsetPtr spRS;
			_Recordset* pRs = NULL;

			 __CHECK_HRESULT4(m_spDS->raw_GetSurfaceVolatilities( m_nSurfaceID, m_enOptType, &pRs), _T("Error getting surface data."));
			 spRS =	 _RecordsetPtr(pRs, false);

			__CHECK_HRESULT4( SetSurfaceData( spRS ), _T("Error setting surface data.") );
			spRS->Close();
			pRs = NULL;

			__CHECK_HRESULT4(m_spDS->raw_GetVolatilitySurfaceProps( m_nSurfaceID, &pRs ), _T("Error getting surface properties."));
			spRS =	 _RecordsetPtr(pRs, false);

			__CHECK_HRESULT4( SetSurfaceProps( spRS ), _T("Error setting surface properties.") );
			spRS->Close();
		}
	}
	catch( const _com_error& e )
	{
		return CComErrorWrapper::SetError(e, L"SymbolVolatility", L"", __FILE__, __FUNCDNAME__,__LINE__);
	}

	return S_OK;
}


STDMETHODIMP CSymbolVolatility::SetSurfaceData( _RecordsetPtr& spData )
{
	try
	{
		ObjectLock lock(this);

		// For each record
		if( SUCCEEDED( spData->raw_MoveFirst() ) )
		{
			for( ; !spData->BOF && !spData->Eof; spData->MoveNext() )
				m_data.SetPoint( spData->Fields->GetItem(L"iCustomStrikeSkewPointID")->Value,
								 spData->Fields->GetItem(L"fStrike")->Value,
								 spData->Fields->GetItem(L"dtExpDate")->Value,
								 spData->Fields->GetItem(L"fVolatility")->Value,
								 spData->Fields->GetItem(L"iIsBasePoint")->Value
							   );

			m_data.UpdateSurfaceStatus();
		}
	}
	catch( const _com_error& e )
	{
		return CComErrorWrapper::SetError(e, L"SymbolVolatility", L"", __FILE__,__FUNCDNAME__,__LINE__);
	}

	return S_OK;
}


STDMETHODIMP CSymbolVolatility::SetSurfaceProps( _RecordsetPtr& spProps )
{
	_variant_t vtValue;
	
	try
	{
		ObjectLock lock(this);
		if((!spProps->Eof )&&( SUCCEEDED( spProps->MoveFirst() ) ))
		{
			vtValue = spProps->Fields->GetItem(L"fBaseUnderlinePrice")->Value;
			if( vtValue.vt != VT_NULL )
				m_data.SetUnderlinePrice( vtValue );
			else
			m_data.SetUnderlinePrice( 0.0f );

			vtValue = spProps->Fields->GetItem(L"fSmileAccelerator")->Value;
			if( vtValue.vt != VT_NULL )
				m_data.SetSmileAccelerator( vtValue );
			else
				m_data.SetSmileAccelerator( 0.0f );

			vtValue = spProps->Fields->GetItem(L"fInterpolationFactor")->Value;
			if( vtValue.vt != VT_NULL )
				m_data.SetInterpolationFactor( 1.0f - vtValue.dblVal );
			else
				m_data.SetInterpolationFactor( 0.0f );

			vtValue = spProps->Fields->GetItem(L"bIsDiscreteAcceleration")->Value;
			if( vtValue.vt != VT_NULL )
				m_data.SetDiscreteAcceleration( vtValue );
			else
				m_data.SetDiscreteAcceleration( false );

			vtValue = spProps->Fields->GetItem(L"bIsPriceOverride")->Value;
			if( vtValue.vt != VT_NULL )
				m_data.SetPriceOverride( vtValue );
			else
				m_data.SetPriceOverride( false );
		}
	}
	catch( const _com_error& e )
	{
		return CComErrorWrapper::SetError(e, L"SymbolVolatility", L"", __FILE__,__FUNCDNAME__,__LINE__);;
	}

	return S_OK;
}


STDMETHODIMP CSymbolVolatility::GetSurfaceData( _RecordsetPtr& spData )
{
	try
	{
		ObjectLock lock(this);

		// Create recordset instance
		if( !spData.GetInterfacePtr() )
			__CHECK_HRESULT( spData.CreateInstance( CLSID_Recordset ), _T("Error creating recordset instance.") );

		// Specify RS fields and properties
		spData->CursorLocation = adUseClient;
		spData->LockType	   = adLockOptimistic;
		spData->Fields->Append( L"iCustomStrikeSkewPointID", adInteger, 4, adFldUnspecified );
		spData->Fields->Append( L"fStrike",			         adDouble,  8, adFldUnspecified );
		spData->Fields->Append( L"fVolatility",			     adDouble,  8, adFldUnspecified );
		spData->Fields->Append( L"dtExpDate",				 adDate,    4, adFldUnspecified );
		spData->Fields->Append( L"iIsBasePoint",			 adInteger, 4, adFldUnspecified );
		spData->Fields->Append( L"iStatus",				     adInteger, 4, adFldUnspecified );

		// Open disconnected RS
		__CHECK_HRESULT( spData->Open( L"data source=none", vtMissing, adOpenUnspecified, adLockUnspecified, adCmdUnspecified ), _T("Error opening recordset.") );

		// For each expiration
		for( long j = 0; j < m_data.GetExpirationsCount(); j++ )
		{
			DATE dtExpDate = m_data.GetExpirationDate( j );

			// For each strike
			for( long i = 0; i < m_data.GetPointsCount( dtExpDate ); i++ )
			{
				EVolaItemStatus enStatus = m_data.GetPointStatus( dtExpDate, i );
				if( enStatus == Untouched )
					continue;

				spData->AddNew();
				spData->Fields->GetItem(L"iCustomStrikeSkewPointID")->PutValue( m_data.GetPointID( dtExpDate, i ) );
				spData->Fields->GetItem(L"fStrike")->PutValue( m_data.GetPointStrike( dtExpDate, i ) );
				spData->Fields->GetItem(L"fVolatility")->PutValue( m_data.GetPointVolatility( dtExpDate, i ) );
				spData->Fields->GetItem(L"dtExpDate")->PutValue( dtExpDate );
				spData->Fields->GetItem(L"iIsBasePoint")->PutValue( m_data.GetIsBasePoint( dtExpDate, i ) );
				spData->Fields->GetItem(L"iStatus")->PutValue( (long)enStatus );
				spData->Update();
			}
		}
	}
	catch( const _com_error& e )
	{
//		return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		return CComErrorWrapper::SetError(e, L"SymbolVolatility", L"", __FILE__,__FUNCDNAME__,__LINE__);;
	}

	return S_OK;
}


STDMETHODIMP CSymbolVolatility::GetSurfaceProps( _RecordsetPtr& spProps )
{
	try
	{
		ObjectLock lock(this);

		// Create recordset instance
		if( !spProps.GetInterfacePtr() )
			__CHECK_HRESULT( spProps.CreateInstance( CLSID_Recordset ), _T("Error creating recordset instance.") );

		// Open disconnected recordset
		spProps->CursorLocation = adUseClient;
		spProps->LockType = adLockOptimistic;
		spProps->Fields->Append( L"fBaseUnderlinePrice",   adDouble,  8, adFldUnspecified );
		spProps->Fields->Append( L"fSmileAccelerator",     adDouble,  8, adFldUnspecified );
		spProps->Fields->Append( L"fInterpolationFactor",  adDouble,  8, adFldUnspecified );
		spProps->Fields->Append( L"bDiscreteAcceleration", adInteger, 4, adFldUnspecified );
		spProps->Fields->Append( L"bPriceOverride",		   adInteger, 4, adFldUnspecified );
		spProps->Fields->Append( L"vcSymbolName",		   adVarChar, 32, adFldUnspecified );
		__CHECK_HRESULT( spProps->Open( L"data source=none", vtMissing, adOpenUnspecified, adLockUnspecified, adCmdUnspecified ), _T("Error opening recordset.") );

		// Put data into recordset
		spProps->AddNew();
		spProps->Fields->GetItem(L"fBaseUnderlinePrice")->PutValue( m_data.GetUnderlinePrice() );
		spProps->Fields->GetItem(L"fSmileAccelerator")->PutValue( m_data.GetSmileAccelerator() );
		spProps->Fields->GetItem(L"fInterpolationFactor")->PutValue( 1.0 - m_data.GetInterpolationFactor() );
		spProps->Fields->GetItem(L"bDiscreteAcceleration")->PutValue( m_data.GetDiscreteAcceleration() );
		spProps->Fields->GetItem(L"bPriceOverride")->PutValue( m_data.GetPriceOverride() );
		spProps->Fields->GetItem(L"vcSymbolName")->PutValue( m_bsSymbolName );
		spProps->Update();
	}
	catch( const _com_error& e )
	{
		return CComErrorWrapper::SetError(e, L"SymbolVolatility", L"", __FILE__,__FUNCDNAME__,__LINE__);;
	}

	return S_OK;
}


STDMETHODIMP CSymbolVolatility::Save()
{
	try
	{
		ObjectLock lock(this);

		if( m_nSurfaceID == -1 )
			return S_OK;

		// Check data source
		if( !m_spDS.GetInterfacePtr() )
			CComErrorWrapper::ThrowError( E_PENDING, _T("Error saving volatility surface - no data source provided.") );

		// Save properties
		_RecordsetPtr spRS;
		__CHECK_HRESULT4( GetSurfaceProps( spRS ), _T("Error collecting volatility surface properties.") );

		__CHECK_HRESULT4( m_spDS->raw_SaveVolatilitySurfaceProps( m_nSurfaceID, spRS ), _T("Error saving volatility surface properties.") );
		spRS->Close();

		// Save data
		__CHECK_HRESULT4( GetSurfaceData( spRS ), _T("Error collecting volatility surface data.") );
		__CHECK_HRESULT4( m_spDS->raw_SaveSurfaceVolatilities( m_nSurfaceID, m_enOptType, spRS ), _T("Error saving volatility surface data.") );

		spRS->Close();
	}
	catch( const _com_error& e )
	{
		//return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		return CComErrorWrapper::SetError(e, L"SymbolVolatility", L"", __FILE__,__FUNCDNAME__,__LINE__);;

	}

	return S_OK;
}

	
STDMETHODIMP CSymbolVolatility::PublishChanges( _RecordsetPtr& spRS )
{
	try
	{
		ObjectLock  lock(this);

		m_spVMESurface->SurfaceID = m_nSurfaceID;
		m_spVMESurface->OptType   = m_enOptType;
		m_spVMESurface->UnderlinePrice   = m_data.GetUnderlinePrice();
		m_spVMESurface->SmileAccelerator = m_data.GetSmileAccelerator();
		m_spVMESurface->InterpolationFactor = m_data.GetInterpolationFactor();
		m_spVMESurface->PriceOverride = m_data.GetPriceOverride() ? VARIANT_TRUE : VARIANT_FALSE;
		m_spVMESurface->DiscreteAcceleration = m_data.GetDiscreteAcceleration() ? VARIANT_TRUE : VARIANT_FALSE;
		m_spVMESurface->Symbol = m_bsSymbolName;
		m_spVMESurface->Points = spRS->Clone( adLockReadOnly );
		m_pSource->PublishChanges(spRS, m_spVMESurface );
		//m_spPubManager->PubVola( m_spSymbolObject, m_spVMESurface );
	}
	catch( const _com_error& e )
	{
		_bstr_t message(L"Error calling publishing manager. ");
		message += CComErrorWrapper::ErrorDescription( e );

		//return Error( (PTCHAR)message, IID_IVSSymbolVolatility, e.Error() );
		return CComErrorWrapper::SetError(e, L"SymbolVolatility", message, __FILE__,__FUNCDNAME__,__LINE__);

	}

	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo implementation
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CSymbolVolatility::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVSSymbolVolatility,
		&IID_IVSTargetVolatility
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// ISymbolVolatility implementation
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CSymbolVolatility::get_Volatility(double UnderlinePrice, double Strike, DATE ExpDate, double *pVal)
{
	__CHECK_POINTER( pVal );

	try
	{
		*pVal = m_data.GetPointVolatility( ExpDate, Strike, UnderlinePrice );
	}
	catch( const _com_error& )
	{
		*pVal = -1;
		return S_FALSE;
	}

	return S_OK;
}


STDMETHODIMP CSymbolVolatility::put_Volatility(double UnderlinePrice, double Strike, DATE ExpDate, double newVal)
{
	try
	{
		ObjectLock lock(this);

		if( m_bEnableEditing == VARIANT_FALSE )
			m_data.AddPoint( ExpDate, Strike, newVal, false, true );
		else
		{
			bool bPriceChanged = false;

			m_data.AddPoint( ExpDate, Strike, newVal, true, false );

			double dUnderlinePrice = m_data.GetUnderlinePrice();
			if( 0.0 == dUnderlinePrice )
			{
				dUnderlinePrice = UnderlinePrice;
				m_data.SetUnderlinePrice( dUnderlinePrice );

				bPriceChanged = true;
			}
			
			if( m_nSurfaceID == -1 )
				return S_OK;

			// Check data source
			if( !m_spDS.GetInterfacePtr() )
				CComErrorWrapper::ThrowError( E_PENDING, _T("Error saving volatility surface - no data source provided.") );

			_RecordsetPtr rsData;
			if( bPriceChanged )
			{
				__CHECK_HRESULT( GetSurfaceProps( rsData ), _T("Error collecting volatility surface properties.") );
				__CHECK_HRESULT( m_spDS->SaveVolatilitySurfaceProps( m_nSurfaceID, rsData ), _T("Error saving volatility surface properties.") );
				rsData->Close();
			}
			
			// Save data
			__CHECK_HRESULT( GetSurfaceData( rsData ), _T("Error collecting volatility surface data.") );
			__CHECK_HRESULT( m_spDS->SaveSurfaceVolatilities( m_nSurfaceID, m_enOptType, rsData ), _T("Error saving volatility surface data.") );

			// Publish changes
			__CHECK_HRESULT( PublishChanges( rsData ), _T("Error publishing changes") );
			
			rsData->Close();
		}
	}
	catch( const _com_error& e )
	{
		//return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		return CComErrorWrapper::SetError(e, L"VolaControl", L"", __FILE__,__FUNCDNAME__,__LINE__);;
	}

	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// _IOnMessages implementation
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CSymbolVolatility::OnVMESurface(/*[in]*/IDispatch* Symbol, /*[in]*/IDispatch* Data)
{
	try
	{
		ObjectLock lock(this);

		IVMESurfacePtr spData = Data;
		if(	m_nSurfaceID != spData->SurfaceID || m_enOptType != spData->OptType )
		{
			m_data.ClearAll();
		
			m_nSurfaceID = spData->SurfaceID;
			m_enOptType  = (EOptType)spData->OptType;
		}

		// Set properties
		m_data.SetUnderlinePrice( spData->UnderlinePrice );
		m_data.SetInterpolationFactor( spData->InterpolationFactor );
		m_data.SetSmileAccelerator( spData->SmileAccelerator );
		m_data.SetPriceOverride( spData->PriceOverride == VARIANT_TRUE ? true : false );
		m_data.SetDiscreteAcceleration( spData->DiscreteAcceleration == VARIANT_TRUE ? true : false );

		// Import points
		_RecordsetPtr spPoints = spData->Points;
		if( spPoints != NULL && SUCCEEDED( spPoints->raw_MoveFirst() ) )
		{
			CObjectLock dataLock( &m_data );

			for( ; !spPoints->BOF && !spPoints->Eof; spPoints->MoveNext() )
				m_data.ImportPoint( spPoints->Fields->GetItem(L"iCustomStrikeSkewPointID")->Value,
									spPoints->Fields->GetItem(L"fStrike")->Value,
									spPoints->Fields->GetItem(L"dtExpDate")->Value,
									spPoints->Fields->GetItem(L"fVolatility")->Value,
									spPoints->Fields->GetItem(L"iIsBasePoint")->Value,
									spPoints->Fields->GetItem(L"iStatus")->Value
								  );
		}

		if( m_bEnableCache == VARIANT_TRUE )
			Save();

		m_data.UpdateSurfaceStatus();
		if( m_bEnableEvents == VARIANT_TRUE )
			m_pSource->OnSurfaceChanged( m_bsSymbolName );
	}
	catch( const _com_error& e )
	{
		ATLTRACE( (PTCHAR)CComErrorWrapper::ErrorDescription( e ) );
		//return CComErrorWrapper::SetError(e, L"VolaControl", L"", __FILE__,__FUNCDNAME__,__LINE__);;
	}

	return S_OK;
}

STDMETHODIMP CSymbolVolatility::get_TargetVolatility(double UnderlinePrice, double Strike, DATE expDate, double *pVal)
{
	if(!pVal)
		return E_POINTER;

	double dA1 = 5.;
	double dA2 = 4.;
	double dB1 = -3.;
	double dB2 = 10.;

	double dUndPriceSQ = UnderlinePrice*UnderlinePrice;
	
	double dC1= 30.-( dA1*dUndPriceSQ+dB1*UnderlinePrice);
	double dC2= 30.-( dA2*dUndPriceSQ+dB2*UnderlinePrice);

	if(Strike<=UnderlinePrice)
		*pVal = dA1*Strike*Strike+dB1*Strike+dC1;
	else
		*pVal = dA2*Strike*Strike+dB2*Strike+dC2;

	return S_OK;
}

STDMETHODIMP CSymbolVolatility::VolatilityShift(DATE expDate, double fShift)
{
	try
	{
		m_data.SetTimeSkewVolatilityDelta(expDate, fShift);
		// Check data source
		if( !m_spDS.GetInterfacePtr() )
			CComErrorWrapper::ThrowError( E_PENDING, _T("Error saving volatility surface - no data source provided.") );

		_RecordsetPtr rsData;
		__CHECK_HRESULT( GetSurfaceProps( rsData ), _T("Error collecting volatility surface properties.") );
		__CHECK_HRESULT( m_spDS->SaveVolatilitySurfaceProps( m_nSurfaceID, rsData ), _T("Error saving volatility surface properties.") );
		rsData->Close();
		
		// Save data
		__CHECK_HRESULT( GetSurfaceData( rsData ), _T("Error collecting volatility surface data.") );
		__CHECK_HRESULT( m_spDS->SaveSurfaceVolatilities( m_nSurfaceID, m_enOptType, rsData ), _T("Error saving volatility surface data.") );

		// Publish changes
		__CHECK_HRESULT( PublishChanges( rsData ), _T("Error publishing changes") );
		
		rsData->Close();
	}
	catch( const _com_error& e )
	{
	//	return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		return CComErrorWrapper::SetError(e, L"VolaControl", L"", __FILE__,__FUNCDNAME__,__LINE__);;

	}
	
	return S_OK;
}

STDMETHODIMP CSymbolVolatility::VolatilitySet(DATE expDate, double newValue)
{
	try
	{
		m_data.SetTimeSkewVolatility(expDate, newValue);
		// Check data source
		if( !m_spDS.GetInterfacePtr() )
			CComErrorWrapper::ThrowError( E_PENDING, _T("Error saving volatility surface - no data source provided.") );

		_RecordsetPtr rsData;
		__CHECK_HRESULT( GetSurfaceProps( rsData ), _T("Error collecting volatility surface properties.") );
		__CHECK_HRESULT( m_spDS->SaveVolatilitySurfaceProps( m_nSurfaceID, rsData ), _T("Error saving volatility surface properties.") );
		rsData->Close();
		
		// Save data
		__CHECK_HRESULT( GetSurfaceData( rsData ), _T("Error collecting volatility surface data.") );
		__CHECK_HRESULT( m_spDS->SaveSurfaceVolatilities( m_nSurfaceID, m_enOptType, rsData ), _T("Error saving volatility surface data.") );

		// Publish changes
		__CHECK_HRESULT( PublishChanges( rsData ), _T("Error publishing changes") );
		
		rsData->Close();
	}
	catch( const _com_error& e )
	{
	//	return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		return CComErrorWrapper::SetError(e, L"VolaControl", L"", __FILE__,__FUNCDNAME__,__LINE__);;

	}
	
	return S_OK;
}

STDMETHODIMP CSymbolVolatility::VolatilitySetAll(double newValue)
{
	try
	{
		m_data.SetTimeSkewVolatilityAll(newValue);
		// Check data source
		if( !m_spDS.GetInterfacePtr() )
			CComErrorWrapper::ThrowError( E_PENDING, _T("Error saving volatility surface - no data source provided.") );

		_RecordsetPtr rsData;
		__CHECK_HRESULT( GetSurfaceProps( rsData ), _T("Error collecting volatility surface properties.") );
		__CHECK_HRESULT( m_spDS->SaveVolatilitySurfaceProps( m_nSurfaceID, rsData ), _T("Error saving volatility surface properties.") );
		rsData->Close();
		
		// Save data
		__CHECK_HRESULT( GetSurfaceData( rsData ), _T("Error collecting volatility surface data.") );
		__CHECK_HRESULT( m_spDS->SaveSurfaceVolatilities( m_nSurfaceID, m_enOptType, rsData ), _T("Error saving volatility surface data.") );

		// Publish changes
		__CHECK_HRESULT( PublishChanges( rsData ), _T("Error publishing changes") );
		
		rsData->Close();
	}
	catch( const _com_error& e )
	{
//		return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		return CComErrorWrapper::SetError(e, L"VolaControl", L"", __FILE__,__FUNCDNAME__,__LINE__);;

	}
	
	return S_OK;
}

STDMETHODIMP CSymbolVolatility::VolatilitySetAllByExp(LPSAFEARRAY* saData)
{
	if(saData == NULL || *saData == NULL)
		return E_POINTER;

	ExpiryVolaData* pData;

	UINT uiDim = SafeArrayGetDim(*saData);
	if(uiDim == 1)
	{
		HRESULT hr = SafeArrayAccessData(*saData, (PVOID*)&pData);
		if(FAILED(hr)) return hr;

		try
		{
			for(ULONG iIndex = 0; iIndex < (*saData)->rgsabound[0].cElements; iIndex++)
			{
				const ExpiryVolaData& evData = pData[iIndex];
				m_data.SetTimeSkewVolatility(evData.Expiry, evData.Vola);
			}

			// Check data source
			if( !m_spDS.GetInterfacePtr() )
				CComErrorWrapper::ThrowError( E_PENDING, _T("Error saving volatility surface - no data source provided.") );

			_RecordsetPtr rsData;
			__CHECK_HRESULT( GetSurfaceProps( rsData ), _T("Error collecting volatility surface properties.") );
			__CHECK_HRESULT( m_spDS->SaveVolatilitySurfaceProps( m_nSurfaceID, rsData ), _T("Error saving volatility surface properties.") );
			rsData->Close();
			
			// Save data
			__CHECK_HRESULT( GetSurfaceData( rsData ), _T("Error collecting volatility surface data.") );
			__CHECK_HRESULT( m_spDS->SaveSurfaceVolatilities( m_nSurfaceID, m_enOptType, rsData ), _T("Error saving volatility surface data.") );

			// Publish changes
			__CHECK_HRESULT( PublishChanges( rsData ), _T("Error publishing changes") );
			
			rsData->Close();
		}
		catch( const _com_error& e )
		{
			SafeArrayUnaccessData(*saData);
			return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		}

		SafeArrayUnaccessData(*saData);
	}
	else
	{
		return E_INVALIDARG;
	}
	
	return S_OK;
}

STDMETHODIMP CSymbolVolatility::VolatilitySetAllByExpAndStrike(LPSAFEARRAY* saData)
{
	if(saData == NULL || *saData == NULL)
		return E_POINTER;

	ExpiryStrikeVolaData* pData;

	UINT uiDim = SafeArrayGetDim(*saData);
	if(uiDim == 1)
	{
		HRESULT hr = SafeArrayAccessData(*saData, (PVOID*)&pData);
		if(FAILED(hr)) return hr;

		try
		{
			for(ULONG iIndex = 0; iIndex < (*saData)->rgsabound[0].cElements; iIndex++)
			{
				const ExpiryStrikeVolaData& evData = pData[iIndex];
				m_data.AddPoint(evData.Expiry, evData.Strike, evData.Vola, true, false);
			}

			// Check data source
			if( !m_spDS.GetInterfacePtr() )
				CComErrorWrapper::ThrowError( E_PENDING, _T("Error saving volatility surface - no data source provided.") );

			_RecordsetPtr rsData;
			__CHECK_HRESULT( GetSurfaceProps( rsData ), _T("Error collecting volatility surface properties.") );
			__CHECK_HRESULT( m_spDS->SaveVolatilitySurfaceProps( m_nSurfaceID, rsData ), _T("Error saving volatility surface properties.") );
			rsData->Close();
			
			// Save data
			__CHECK_HRESULT( GetSurfaceData( rsData ), _T("Error collecting volatility surface data.") );
			__CHECK_HRESULT( m_spDS->SaveSurfaceVolatilities( m_nSurfaceID, m_enOptType, rsData ), _T("Error saving volatility surface data.") );

			// Publish changes
			__CHECK_HRESULT( PublishChanges( rsData ), _T("Error publishing changes") );
			
			rsData->Close();
		}
		catch( const _com_error& e )
		{
			SafeArrayUnaccessData(*saData);
			return Error( (PTCHAR)CComErrorWrapper::ErrorDescription( e ), IID_IVSSymbolVolatility, e.Error() );
		}

		SafeArrayUnaccessData(*saData);
	}
	else
	{
		return E_INVALIDARG;
	}
	
	return S_OK;
}
//////////////////////////////////////////////////////////////////////////
/*STDMETHODIMP CSymbolVolatility::SetPubManager(IPubManagerPtr spPubManger)
{
	if (m_spPubManager == NULL)
		m_spPubManager = spPubManger;
	return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CSymbolVolatility::SetSubManager(ISubManagerPtr spSubManger)
{
	if (m_spSubManager == NULL)
		m_spSubManager = spSubManger;
	return S_OK;
}*/