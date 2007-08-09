Attribute VB_Name = "modMain"
Option Explicit

Public Const APP_LIC_NAME As String = "EGAR ETS 85A70EF2-7BFD-446F-BBB9-D9BE82063CE4"
Public Const APP_TITLE As String = "EtsMM"
Public Const APP_REG_KEY As String = "SOFTWARE\Egar\ETS\Market Maker\"
Public Const PRODUCT_REG_KEY As String = "SOFTWARE\Egar\ETS\"
Public Const DATA_SHAPSHOT_FILENAME$ = "EtsMM_DataShapshot"
Public Const DB_VERSION_COMPATIBLE_MAJOR& = 3
Public Const DB_VERSION_COMPATIBLE_MINOR& = 46
Public Const DB_VERSION_COMPATIBLE_BUILD& = 123

Public Const APP_XML_KEY As String = "ETS\MarketMaker\"
Public Const PRODUCT_XML_KEY As String = "ETS\"

Public Const GCOLOR_LABEL_VALID As Long = &H80000008
Public Const GCOLOR_LABEL_INVALID As Long = &HC0&

Global g_lMainTop As Long
Global g_lMainLeft As Long
Global g_lMainWidth As Long
Global g_lMainHeight As Long
Global g_lMainState As Long

Global g_lMinLogLevel As Long

Global g_lLogTop As Long
Global g_lLogLeft As Long
Global g_lLogWidth As Long
Global g_lLogHeight As Long
Global g_frmLog As frmLog

Global gDBW As clsDBWork
Global gCmn As clsCommon
'Global g_TradeChannel As clsTradeChannel
'Global g_OrdersProcessor As clsOrdersProcessor
'Global g_TntProcessor As clsTntProcessor

'Global g_ViewFrm As clsFormColl
'Global g_ViewFrmID As Long

Global g_Params As New clsParams
Global g_aUserXMLParams As ETSXMLParamsLib.XMLParams
Global g_aMainXMLParams As ETSXMLParamsLib.XMLParams

Public Enum EntityTypeEnum
    ET_TRADER = &H1&
    ET_TRADER_GROUP = &H2&
    ET_STRATEGY = &H4&
    ET_BROKER = &H8&
    ET_UNDERLYING = &H10&
    ET_UNDERLYING_GROUP = &H20&
    ET_RM_SCENARIO = &H40&
    ET_EXP_CALENDAR = &H80&
    ET_INDEX = &H100&
    ET_EXCHANGE = &H200&
    ET_PRICE_PROFILE = &H400&
    ET_ORDER_EXEC_DEST = &H800&
    ET_TNT_CNT_PTY = &H1000&
    ET_ALL = &HFFFFFFFF
End Enum

Global g_CurTraderID As Long

Global g_Main As EtsGeneralLib.EtsMain

Global g_Trader As EtsGeneralLib.EtsTraderColl
Global g_TraderGroup As EtsGeneralLib.EtsTraderGroupColl
Global g_Strategy As EtsGeneralLib.EtsStrategyColl
Global g_Broker As EtsGeneralLib.EtsBrokerColl
Global g_ClearingBroker As EtsGeneralLib.EtsBrokerColl
Global g_Underlying As EtsGeneralLib.UndColl
'Global g_UnderlyingBySym As EtsGeneralLib.UndBySymColl
Global g_UnderlyingAll As EtsGeneralLib.UndColl
'Global g_UnderlyingAllBySym As EtsGeneralLib.UndBySymColl
Global g_UnderlyingGroup As EtsGeneralLib.EtsUndGroupColl
'Global g_RmScenario As clsRmScenarioColl
Global g_ExpCalendar As EtsGeneralLib.EtsExpCalColl
'Global g_DefExpCalendar As EtsGeneralLib.EtsExpCalAtom
Global g_Index As EtsGeneralLib.IndexColl
Global g_BasketIndex As EtsGeneralLib.IndexColl
Global g_Exch As EtsGeneralLib.ExchColl
Global g_PriceProfile As EtsGeneralLib.EtsPriceProfileColl
'Global g_OrderExecDest As EtsMmGeneralLib.MmOrderExecDestColl
'Global g_TntCntPty As EtsMmGeneralLib.MmTntCounterPartyColl
'Global g_TntCntPtyByName As EtsMmGeneralLib.MmTntCounterPartyByNameColl
Global g_OptRootByName As EtsGeneralLib.EtsOptRootByNameColl
Global g_ContractAll As EtsGeneralLib.EtsContractColl
Global g_Contract As EtsGeneralLib.EtsContractColl
'Global g_ContractAllBySym As EtsGeneralLib.EtsContractBySymColl
Global g_Stock As EtsGeneralLib.UndColl
'Global g_StockBySym As EtsGeneralLib.UndBySymColl
'Global g_BasketIndexUndBySym As EtsGeneralLib.UndBySymColl

Global g_DefStkPriceProfile As EtsGeneralLib.EtsPriceProfileAtom
Global g_DefIdxPriceProfile As EtsGeneralLib.EtsPriceProfileAtom
Global g_DefOptPriceProfile As EtsGeneralLib.EtsPriceProfileAtom

Global g_VolaSource As VolatilitySourcesLib.VolatilitySource
'Global g_MmManager As ISEPROVIDERLib.ISEMMManager

Global g_nQuotesUntitledIdx As Long
Global g_nRisksUntitledIdx As Long
Global g_nRiskMatrixUntitledIdx As Long
Global g_nTradesUntitledIdx As Long
Global g_nVolaUntitledIdx As Long
Global g_nQuotationUntitledIdx As Long
Global g_nVolaAnalysisUntitledIdx As Long
Global g_nGreeksUntitledIdx As Long
Global g_nHedgeSummaryUntitledIdx As Long
Global g_nReportsUntitledIdx As Long
Global g_nOrdersUntitledIdx As Long
Global g_nTntCardUntitledIdx As Long
Global g_nStockHedgeUntitledIdx As Long
Global g_nIndexHedge1UntitledIdx As Long
Global g_nIndexHedge2UntitledIdx As Long

'Global g_frmWtdVegaSettings As frmWtdVegaSettings
'Global g_frmStockHedgeMaintenance As frmStockHedgeMaintenance
Global g_nHedgeSummaryFileIdx As Long

Private m_hSingleInstanceMutex As Long
Private Const SINGLE_INSTANCE_MUTEX_NAME As String = "EGAR ETS MM EABA61FA-32DE-41D2-AE2B-F31A84FF9A47"

Global g_frmOwner As Form

Private m_bShutDownNow As Boolean

Global g_sLicenseKey As String
'Global g_lcLicense As LicenseType
Global g_sLicenseCompany As String
Global g_sLicenseUser As String

Global g_bIseEnable As Boolean

Global g_nDefaultTerm As Long

'Global g_ClipMgr As clsClipMgr
'Global g_ptDefWindowSize As POINTAPI

'Global g_frmMatchedTrades As frmMatchedTrades

'Global g_frmUnderlyings As clsFormAtom

Private m_bFirstRun As Boolean

Global g_PerformanceLog As clsPerformanceLog

'Global g_PerfObject As ETSPerfObjects.CCEtsPerformanceObject


'Private m_PriceProvider As PRICEPROVIDERSLib.BatchPriceInfo

Global g_RTQuantity As Long
Global g_MaxRTQuantity As Long
Global g_RTNumber As Long

Private m_nNewGrpID&

Sub Main()
    On Error GoTo EH
    Dim bNewLicense As Boolean
'    SetCrashHandler
    
    g_RTQuantity = 0
    g_MaxRTQuantity = 4
    g_RTNumber = 0
    
    
    App.OleRequestPendingTimeout = 2000000
    App.OleServerBusyTimeout = 2000000
    
    g_nQuotesUntitledIdx = 0
    g_nRisksUntitledIdx = 0
    g_nRiskMatrixUntitledIdx = 0
    g_nTradesUntitledIdx = 0
    g_nVolaUntitledIdx = 0
    g_nQuotationUntitledIdx = 0
    g_nVolaAnalysisUntitledIdx = 0
    g_nGreeksUntitledIdx = 0
    g_nHedgeSummaryUntitledIdx = 0
    g_nReportsUntitledIdx = 0
    g_nOrdersUntitledIdx = 0
    g_nTntCardUntitledIdx = 0
    g_nStockHedgeUntitledIdx = 0
    g_nIndexHedge1UntitledIdx = 0
    g_nIndexHedge2UntitledIdx = 0
    
    m_bShutDownNow = False
    
    g_nHedgeSummaryFileIdx = 0
    
    g_nDefaultTerm = 252
    
    If Not g_Params.IsDebug Then
        'm_hSingleInstanceMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, SINGLE_INSTANCE_MUTEX_NAME)
        'If m_hSingleInstanceMutex <> 0 Then Exit Sub
            
        'm_hSingleInstanceMutex = CreateMutex(0, 0, SINGLE_INSTANCE_MUTEX_NAME)
    End If
    
    'InstallExceptionHandler
      
    Set gCmn = New clsCommon
    
    CreateGlobalCollections
    
    Load frmSplash
    frmSplash.Show
    frmSplash.Refresh
        
    Set g_frmOwner = frmSplash

    frmSplash.lblStatus.Caption = "Loading application settings..."
    DoEvents
    
    LoadSettings frmSplash
    'InitEventLog
    
    g_Params.LoadSettings
    
    frmSplash.lblStatus.Caption = "Checking license ..."
    DoEvents
    
'    bNewLicense = False
'    If Not CheckLicense(frmSplash, bNewLicense) Then
'        ShutDown True
'        Exit Sub
'    End If
    
    Set gDBW = New clsDBWork

    frmSplash.lblStatus.Caption = "Connecting to database..."
    DoEvents
    If Not gDBW.CheckDBConnection(frmSplash, m_bFirstRun) Then
        gCmn.MyMsgBox frmSplash, "Fail to connect to database. Application will be closed.", vbCritical
        ShutDown True
        Exit Sub
    End If
    
    Do While Not LoadDBVersion(True)
        Set gDBW = Nothing
        Set gDBW = New clsDBWork
        'If Not gDBW.ChangeDatabase(frmSplash, Nothing, True) Then
            gCmn.MyMsgBox frmSplash, "Fail to connect to database. Application will be closed.", vbCritical
            ShutDown True
            Exit Sub
        'End If
    Loop
    
'    If Not CheckAspLicense(frmSplash) Then
'        ShutDown True
'        Exit Sub
'    End If
    
    'Set g_PerfObject = New ETSPerfObjects.CCEtsPerformanceObject
    
    g_Params.LoadActualTradesEditable
    g_Params.LoadPriceRoundingRule
    g_Params.LoadUndPriceToleranceValue
    g_Params.LoadCommissionLowPremiumLimit
    
    'Set g_TradeChannel = New clsTradeChannel
'    Set g_OrdersProcessor = New clsOrdersProcessor
'    Set g_TntProcessor = New clsTntProcessor
    
    'frmSplash.lblStatus.Caption = "Connecting to price provider..."
    'DoEvents
    'InitPriceProvider
    
'    If g_Params.LogAdvancedInfo Then
'        Set g_PerformanceLog = New clsPerformanceLog
'        If Not g_PerformanceLog.Init("EtsMM_PerfLog_" & CStr(Format(Now, "M_d_yyyy_H_mm")) & ".txt") Then
'            Set g_PerformanceLog = Nothing
'        End If
'
'        frmSplash.tmrPerformance.Interval = g_Params.LogPerfCountInterval
'        frmSplash.tmrPerformance.Enabled = g_Params.LogPerformanceCounters
'    End If
    
    frmSplash.lblStatus.Caption = "Initializing volatility source..."
    DoEvents
    InitVolaSources m_bFirstRun
    
    frmSplash.lblStatus.Caption = "Loading common data..."
    DoEvents
    g_CurTraderID = g_Params.DefTraderID
    
'    If frmTrader.Execute(g_CurTraderID, frmSplash) <> vbOK Then
'        gCmn.MyMsgBox frmSplash, "No active trader selected! Application will be closed.", vbCritical
'        ShutDown True
'        Exit Sub
'    End If
    DoEvents
    
    Dim nOperation&
'    If Not g_PerformanceLog Is Nothing Then _
'        nOperation = g_PerformanceLog.BeginLogMmOperation
        
    LoadEntities ET_ALL, frmSplash.lblStatus
    
'    If Not g_PerformanceLog Is Nothing Then _
'        g_PerformanceLog.FinishLogMmOperation nOperation, OPER_LOADINITDATA, "EtsMM"
        
    frmSplash.lblStatus.Caption = "Loading interest rates data..."
    DoEvents
    LoadInterestRates
    
    frmSplash.lblStatus.Caption = "Loading default settings..."
    DoEvents
    
    g_Params.MakeUnderlingComboLists
    'InitDefGrids
    
    'Set g_ViewFrm = New clsFormColl
    'Set g_frmWtdVegaSettings = New frmWtdVegaSettings
'    Set g_frmStockHedgeMaintenance = New frmStockHedgeMaintenance
    'Set g_frmMatchedTrades = New frmMatchedTrades
    
    frmSplash.lblStatus.Caption = "Connecting to real-time trades feed..."
    DoEvents
    'g_TradeChannel.InitMessaging
'    g_OrdersProcessor.InitMessaging
'    g_TntProcessor.InitAdapter
    
'    DeleteOldOrders

'    If Not g_PerformanceLog Is Nothing Then _
'        nOperation = g_PerformanceLog.BeginLogMmOperation
'
'    g_TradeChannel.LoadTrades frmSplash.lblStatus
'    g_OrdersProcessor.LoadOrders frmSplash.lblStatus
'    g_TntProcessor.LoadCards frmSplash.lblStatus
    
    Load Form1
'    If Not g_PerformanceLog Is Nothing Then _
'        g_PerformanceLog.FinishLogMmOperation nOperation, OPER_LOADTRADESDATA, "EtsMM"
    
'    g_TradeChannel.Start
'    g_OrdersProcessor.Start
'    g_TntProcessor.Start
    
    ' check ISE provider
'    frmSplash.lblStatus.Caption = "Checking ISE environment..."
'    DoEvents
'    g_bIseEnable = IsIseProviderPresent
    
    'Set g_ClipMgr = New clsClipMgr
    
'    If g_Params.LogAdvancedInfo Then
'        frmMain.tmrPerformance.Interval = g_Params.LogPerfCountInterval
'        frmMain.tmrPerformance.Enabled = g_Params.LogPerformanceCounters
'    End If
'    GetDefWindowSize g_ptDefWindowSize
'    g_ptDefWindowSize.X = frmMain.ScaleX(g_ptDefWindowSize.X, vbPixels, vbTwips)
'    g_ptDefWindowSize.Y = frmMain.ScaleY(g_ptDefWindowSize.Y, vbPixels, vbTwips)
'
'    If g_lMainWidth > 0 Then
'        frmMain.Left = g_lMainLeft
'        frmMain.Top = g_lMainTop
'        frmMain.Width = g_lMainWidth
'    End If
    
    Form1.Show
    Set g_frmOwner = Form1
    Unload frmSplash
    
'    g_frmMatchedTrades.StartMonitoring
    
'    CheckMarketStructureInCache frmMain

'    If Len(Command$) > 0 Then frmMain.OpenFromFile Replace$(Command$, """", "")
    Exit Sub
EH:
    gCmn.ErrorMsgBox g_frmOwner, "Fail to initialize ETS. Application will be closed."
    ShutDown True
End Sub
Private Sub CreateGlobalCollections()
    On Error GoTo EH
    Set g_Main = New EtsGeneralLib.EtsMain
    
    Set g_Trader = g_Main.Trader
    Set g_TraderGroup = g_Main.TraderGroup
    Set g_Strategy = g_Main.Strategy
    Set g_Broker = g_Main.Broker
    Set g_ClearingBroker = g_Main.ClearingBroker
    Set g_Underlying = g_Main.Underlying
    'Set g_UnderlyingBySym = New EtsGeneralLib.UndBySymColl
    Set g_UnderlyingAll = g_Main.UnderlyingAll
    'Set g_UnderlyingAllBySym = New EtsGeneralLib.UndBySymColl
    Set g_UnderlyingGroup = g_Main.UnderlyingGroup
   ' Set g_RmScenario = New clsRmScenarioColl
    Set g_ExpCalendar = g_Main.ExpCalendar
    Set g_Index = New EtsGeneralLib.IndexColl
    Set g_BasketIndex = New EtsGeneralLib.IndexColl
    Set g_Exch = New EtsGeneralLib.ExchColl
    Set g_PriceProfile = New EtsGeneralLib.EtsPriceProfileColl
'    Set g_OrderExecDest = New EtsMmGeneralLib.MmOrderExecDestColl
'    Set g_TntCntPty = New EtsMmGeneralLib.MmTntCounterPartyColl
'    Set g_TntCntPtyByName = New EtsMmGeneralLib.MmTntCounterPartyByNameColl
    Set g_OptRootByName = g_Main.OptRootByName
    Set g_ContractAll = g_Main.ContractAll
    Set g_Contract = g_Main.Contract
    
    'Set g_ContractAllBySym = New EtsGeneralLib.EtsContractBySymColl
    Set g_Stock = g_Main.Stock
    'Set g_StockBySym = New EtsGeneralLib.UndBySymColl
    Set g_BasketIndex = New EtsGeneralLib.IndexColl
    Exit Sub
EH:
    gCmn.ErrorHandler "Fail to init internal storage"
End Sub

Private Sub LoadSettings(ByRef frmOwner As Form)
    On Error Resume Next
    Dim sUID$, sTmp$, nTmp&
    
    Dim aXMLLoader As New ETSXMLParamsLib.XMLLoader
    Set g_aMainXMLParams = aXMLLoader.Load(MainXMLFilePath)
    If g_aMainXMLParams Is Nothing Then
        Set g_aMainXMLParams = New ETSXMLParamsLib.XMLParams
    End If
    
    'g_lcLicense.Modules = &H7FFFFFFF
    'g_sLicenseKey = g_aMainXMLParams.GetStringValue(PRODUCT_XML_KEY & "License", "Key", "")
    'g_sLicenseCompany = g_aMainXMLParams.GetStringValue(PRODUCT_XML_KEY & "License", "Company", "")
    'g_sLicenseUser = g_aMainXMLParams.GetStringValue(PRODUCT_XML_KEY & "License", "User", "")
    
    sTmp = String$(1024, 0)
    If GetWindowsDirectory(sTmp, 1024) <> 0 Then
        sTmp = Left$(sTmp, 3)
    Else
        sTmp = "C:\"
    End If
    
    'nTmp = GetVolumeSerialNo(sTmp)
    'If nTmp < 0 Then nTmp = -nTmp
    'sUID = Hex$(nTmp)
    'sUID = APP_LIC_NAME & " " & sUID & " " & g_sLicenseCompany & " " & g_sLicenseUser
    
    'g_lcLicense.UID = CalcCRC(sUID, frmOwner)
    
    Set g_aUserXMLParams = aXMLLoader.Load(CurrentUserXMLFilePath)
    If g_aUserXMLParams Is Nothing Then
        Set g_aUserXMLParams = New ETSXMLParamsLib.XMLParams
    End If
    
    g_lMainTop = g_aUserXMLParams.GetLongValue(APP_XML_KEY & "Settings", "MainTop", 0)
    g_lMainLeft = g_aUserXMLParams.GetLongValue(APP_XML_KEY & "Settings", "MainLeft", 0)
    g_lMainWidth = g_aUserXMLParams.GetLongValue(APP_XML_KEY & "Settings", "MainWidth", 0)
    g_lMainHeight = g_aUserXMLParams.GetLongValue(APP_XML_KEY & "Settings", "MainHeight", 0)
    g_lMainState = g_aUserXMLParams.GetLongValue(APP_XML_KEY & "Settings", "MainState", vbNormal)
    
    If g_lMainTop < 0 Then g_lMainTop = 0
    If g_lMainLeft < 0 Then g_lMainLeft = 0
    
    nTmp = GetSystemMetrics(SM_CXFULLSCREEN) * 15
    If g_lMainWidth < 0 Then g_lMainWidth = 0
    If g_lMainWidth > nTmp Then g_lMainWidth = nTmp
    If g_lMainLeft > nTmp Then g_lMainLeft = nTmp - g_lMainWidth
    nTmp = GetSystemMetrics(SM_CYFULLSCREEN) * 15
    If g_lMainTop > nTmp Then g_lMainTop = nTmp - 1500
    
    g_lLogTop = g_aUserXMLParams.GetLongValue(APP_XML_KEY & "Settings", "LogTop", 0)
    g_lLogLeft = g_aUserXMLParams.GetLongValue(APP_XML_KEY & "Settings", "LogLeft", 0)
    g_lLogWidth = g_aUserXMLParams.GetLongValue(APP_XML_KEY & "Settings", "LogWidth", 0)
    g_lLogHeight = g_aUserXMLParams.GetLongValue(APP_XML_KEY & "Settings", "LogHeight", 0)
    
    m_bFirstRun = False ' (GetLongKeyValueEx(APP_REG_KEY & "Settings", "FirstRun", 1) <> 0)
    
    'g_CurTraderID = GetLongKeyValueEx(APP_REG_KEY & "Settings", "CurTrader")
End Sub

Public Sub ShutDown(ByVal bEndExecution As Boolean)
    On Error Resume Next
    If m_bShutDownNow Then Exit Sub
    
    Dim aFrm As Form
    m_bShutDownNow = True
    
    For Each aFrm In Forms
        Unload aFrm
    Next
    'Set g_ViewFrm = Nothing
    
    'Set g_frmMatchedTrades = Nothing
    'Set g_TradeChannel = Nothing
'    Set g_OrdersProcessor = Nothing
    g_VolaSource.EnableEvents = False
    
'    g_TntProcessor.ShutDown
'    Set g_TntProcessor = Nothing
    
    'm_PriceProvider.Disconnect
    'Set m_PriceProvider = Nothing
    
    Set g_frmLog = Nothing
    'Set g_frmUnderlyings = Nothing
    
    Set g_frmOwner = Nothing
'    Set g_MmManager = Nothing
    
    'g_Params.SaveSettings
    'SaveSettings
    ClearInterestRates
    
    'Set g_frmWtdVegaSettings = Nothing
'    Set g_frmStockHedgeMaintenance = Nothing
    Set g_VolaSource = Nothing
    
    Set g_DefStkPriceProfile = Nothing
    Set g_DefIdxPriceProfile = Nothing
    Set g_DefOptPriceProfile = Nothing
    'Set g_DefExpCalendar = Nothing
    
    g_Trader.Clear
    g_TraderGroup.Clear
    g_Strategy.Clear
    g_Broker.Clear
    g_ClearingBroker.Clear
    g_Underlying.Clear
    'g_UnderlyingBySym.Clear
    g_UnderlyingAll.Clear
    'g_UnderlyingAllBySym.Clear
    g_UnderlyingGroup.Clear
    'g_RmScenario.Clear
    g_ExpCalendar.Clear
    g_Index.Clear
    g_BasketIndex.Clear
    'g_BasketIndexUndBySym.Clear
    g_Exch.Clear
    g_PriceProfile.Clear
'    g_OrderExecDest.Clear
'    g_TntCntPty.Clear
'    g_TntCntPtyByName.Clear
    g_OptRootByName.Clear
    g_Contract.Clear
    g_ContractAll.Clear
    'g_ContractAllBySym.Clear
    g_Stock.Clear
    'g_StockBySym.Clear
    
    'ClearDefGrids
    
    Set gDBW = Nothing
    Set gCmn = Nothing
'    Set g_ClipMgr = Nothing
    'Set g_PerformanceLog = Nothing
    
    'Set g_PerfObject = Nothing
    
    If Not g_Params.IsDebug And m_hSingleInstanceMutex <> 0 Then CloseHandle m_hSingleInstanceMutex
    'UninstallExceptionHandler
    
    If bEndExecution Then
        m_bShutDownNow = False
        End
    End If
    m_bShutDownNow = False
End Sub

'Public Sub InitPriceProvider()
'    On Error GoTo EH
'    Dim aPT As PRICEPROVIDERSLib.IProvider, bRetry As Boolean
'    Dim aProviderData As PRICEPROVIDERSLib.IProviderData
'    Dim aProviders As PRICEPROVIDERSLib.Providers
'
'    bRetry = False
'
'    Set aProviders = New PRICEPROVIDERSLib.Providers
'    aProviders.Initialize
'
'    On Error Resume Next
'    aProviders.GetProvider g_Params.PriceProviderType, aProviderData
'    g_Params.PriceProviderProgID = aProviderData.ProgId(enPriceInfo)
'
'    bRetry = True
'
'Retry:
'    On Error GoTo EH
'
'    If m_PriceProvider Is Nothing Then Set m_PriceProvider = New PRICEPROVIDERSLib.BatchPriceInfo
'    If aPT Is Nothing Then Set aPT = m_PriceProvider
'
'    aPT.Type = g_Params.PriceProviderType
'    m_PriceProvider.Connect
'
'    Set aPT = Nothing
'
'    Set aProviderData = Nothing
'    aProviders.GetProvider g_Params.PriceProviderType, aProviderData
'    If Not aProviderData Is Nothing Then
'        g_Params.PriceProviderIsGroupRequestSupported = aProviderData.IsGroupRequestSupported
'    Else
'        g_Params.PriceProviderIsGroupRequestSupported = False
'    End If
'
'    Set aProviderData = Nothing
'    Set aProviders = Nothing
'    Exit Sub
'EH:
'    Dim sDescription$, nHelpContext&, sHelpFile$, nNumber&, sSource$
'    sDescription = "Fail to initialize price provider. " & Err.Description
'    nHelpContext = Err.HelpContext
'    sHelpFile = Err.HelpFile
'    nNumber = Err.Number
'    sSource = Err.Source
'
''    If bRetry Then
''        If Not m_bFirstRun Then gCmn.ErrorMsgBox g_frmOwner, sDescription
''
''        On Error Resume Next
''        Dim frmConnect As frmConnections
''        Set frmConnect = New frmConnections
''
''        If frmConnect.Execute(True, enCsoPriceProviderOnly, True, Nothing) = vbOK Then
''            Set frmConnect = Nothing
''            Resume Retry
''        Else
''            On Error GoTo 0
''            Set frmConnect = Nothing
''            Set aPT = Nothing
''            Set m_PriceProvider = Nothing
''            Set aProviderData = Nothing
''            Set aProviders = Nothing
''            Err.Raise nNumber, sSource, sDescription, sHelpFile, nHelpContext
''        End If
''    End If
'
'    Set aPT = Nothing
'    Set m_PriceProvider = Nothing
'    Set aProviderData = Nothing
'    Set aProviders = Nothing
'    Err.Raise nNumber, sSource, sDescription, sHelpFile, nHelpContext
'End Sub

Private Sub InitVolaSources(ByVal bFirstRun As Boolean)
    On Error GoTo EH
    Dim bRetry As Boolean, sName$, sFileName$, sVersion$, nID&, sProgID$
    Dim vmDB As VADBLAYOUTLib.DBLayout
    Dim aVolaSources As VolatilitySourcesLib.VolatilitySources
    
    bRetry = False
    
    Set vmDB = New VADBLAYOUTLib.DBLayout
    Set aVolaSources = New VolatilitySourcesLib.VolatilitySources
    
    On Error Resume Next
    aVolaSources.GetVolatilitySourceInfoByID g_Params.VolatilitySourceType, sName, sFileName, sVersion, sProgID
    g_Params.VolatilitySourceProgID = sProgID

    bRetry = True

Retry:
    On Error GoTo EH
    Set g_VolaSource = aVolaSources.VolatilitySource(g_Params.VolatilitySourceType)
    vmDB.ConnectionString = g_Params.DbConnection

    Set g_VolaSource.DataSource = vmDB
    g_VolaSource.EnableEvents = True
    g_VolaSource.EnableEditing = True

    Exit Sub
EH:
    Dim sDescription$, nHelpContext&, sHelpFile$, nNumber&, sSource$
    sDescription = "Fail to initialize volatility source."
    nHelpContext = Err.HelpContext
    sHelpFile = Err.HelpFile
    nNumber = Err.Number
    sSource = Err.Source
    
'    If bRetry Then
'        If Not bFirstRun Then gCmn.ErrorMsgBox g_frmOwner, sDescription
'
'        On Error Resume Next
'        Dim frmConnect As frmConnections
'        Set frmConnect = New frmConnections
'
'        If frmConnect.Execute(True, enCsoVolatilitySourceOnly, True, Nothing) = vbOK Then
'            Set g_VolaSource = Nothing
'            Set frmConnect = Nothing
'            Resume Retry
'        Else
'            On Error GoTo 0
'            Set frmConnect = Nothing
'            Set vmDB = Nothing
'            Set aVolaSources = Nothing
'            Set g_VolaSource = Nothing
'            Err.Raise nNumber, sSource, sDescription, sHelpFile, nHelpContext
'        End If
'    End If
    Set vmDB = Nothing
    Set aVolaSources = Nothing
    Set g_VolaSource = Nothing
    Err.Raise nNumber, sSource, sDescription, sHelpFile, nHelpContext
End Sub

Public Sub LoadEntities(Optional ByVal enType As EntityTypeEnum = ET_ALL, Optional ByRef lblProgress As VB.Label = Nothing)
    On Error GoTo EH
    'Dim aScn As clsRmScenarioAtom
    Dim rs As ADODB.Recordset, rs2 As ADODB.Recordset, bAdd As Boolean
    Dim aExpMonth As EtsGeneralLib.EtsExpMonthAtom, nExpiryMonth&
    Dim aUnd As EtsGeneralLib.UndAtom, aIdx As EtsGeneralLib.IndexAtom, aIdxComp As EtsGeneralLib.IndexCompAtom, aExch As EtsGeneralLib.ExchAtom
    Dim nID&, dtExpiry As Date, sExpiryKey$, nIdxID&, sStep$, nUndID&, nFutRootID&, nFutID&, nSynthUndID&
    Dim aSyntRoot As EtsGeneralLib.SynthRootAtom
    Dim aSyntRootComp As EtsGeneralLib.SynthRootCompAtom
    Dim dWeight#, dBeta#, aPrProf As EtsGeneralLib.EtsPriceProfileAtom
    Dim aRoot As EtsGeneralLib.EtsOptRootAtom, nOptRootID&
'    Dim aExecDest As EtsMmGeneralLib.MmOrderExecDestAtom
    Dim aTrader As EtsGeneralLib.EtsTraderAtom
    Dim aBroker As EtsGeneralLib.EtsBrokerAtom
    Dim aStrategy As EtsGeneralLib.EtsStrategyAtom
    Dim aUndGroup As EtsGeneralLib.EtsUndGroupAtom
    Dim aTraderGroup As EtsGeneralLib.EtsTraderGroupAtom
'    Dim aCntPty As EtsMmGeneralLib.MmTntCounterPartyAtom
    Dim aTrdUnd As EtsGeneralLib.EtsTraderUndAtom
    Dim aFutRoot As EtsGeneralLib.EtsFutRootAtom
    Dim aFut As EtsGeneralLib.EtsFutAtom
    Dim aContract As EtsGeneralLib.EtsContractAtom
    
    Dim rsCust As ADODB.Recordset
    Dim aDiv As EtsGeneralLib.EtsIndexDivAtom
    Dim aCustDivColl As EtsGeneralLib.EtsDivColl
    Dim aUndDiv As EtsGeneralLib.EtsIndexDivAtom
    Dim dDate As Date
    Dim dAmount As Double


    If (enType And ET_STRATEGY) = ET_STRATEGY Then
        sStep = "strategies data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading strategies data...": lblProgress.Refresh
        g_Strategy.Clear
        Set rs = gDBW.usp_Strategy_Get(Null)
        While Not rs.EOF
            nID = ReadLng(rs!iStrategyID)
            If g_Strategy(nID) Is Nothing Then
                Set aStrategy = New EtsGeneralLib.EtsStrategyAtom
                aStrategy.ID = nID
                aStrategy.Name = Trim$(ReadStr(rs!vcStrategyName))
                aStrategy.Desc = ReadStr(rs!vcDescription)
            
                g_Strategy.Add aStrategy.ID, aStrategy.Name, aStrategy
                Set aStrategy = Nothing
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    End If
    
    If (enType And ET_BROKER) = ET_BROKER Then
        sStep = "brokers data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading brokers data...": lblProgress.Refresh
        g_Broker.Clear
        g_ClearingBroker.Clear
        Set rs = gDBW.usp_Broker_Get(Null)
        While Not rs.EOF
            nID = ReadLng(rs!iBrokerID)
            If ReadByte(rs!tiIsClearing) = 0 Then
                If g_Broker(nID) Is Nothing Then
                    Set aBroker = New EtsGeneralLib.EtsBrokerAtom
                    aBroker.ID = nID
                    aBroker.Name = Trim$(ReadStr(rs!vcBrokerName))
                    aBroker.IsClearing = False
                    aBroker.Desc = ReadStr(rs!vcDescription)
                    aBroker.UndComm = ReadDbl(rs!fUndComm)
                    aBroker.OptRegComm = ReadDbl(rs!fOptRegComm)
                    aBroker.OptSpreadComm = ReadDbl(rs!fOptSpreadComm)
                    aBroker.LowPremComm = ReadDbl(rs!fLowPremComm)
                
                    g_Broker.Add aBroker.ID, aBroker.Name, aBroker
                    Set aBroker = Nothing
                End If
            Else
                If g_ClearingBroker(nID) Is Nothing Then
                    Set aBroker = New EtsGeneralLib.EtsBrokerAtom
                    aBroker.ID = nID
                    aBroker.Name = Trim$(ReadStr(rs!vcBrokerName))
                    aBroker.IsClearing = True
                    aBroker.Desc = ReadStr(rs!vcDescription)
                    aBroker.UndComm = ReadDbl(rs!fUndComm)
                    aBroker.OptRegComm = ReadDbl(rs!fOptRegComm)
                    aBroker.OptSpreadComm = ReadDbl(rs!fOptSpreadComm)
                    aBroker.LowPremComm = ReadDbl(rs!fLowPremComm)
                
                    g_ClearingBroker.Add aBroker.ID, aBroker.Name, aBroker
                    Set aBroker = Nothing
                End If
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    End If
    
    If (enType And ET_PRICE_PROFILE) = ET_PRICE_PROFILE Then
        sStep = "price profiles."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading price profiles data...": lblProgress.Refresh
        g_PriceProfile.Clear
        
        Set g_DefStkPriceProfile = Nothing
        Set g_DefIdxPriceProfile = Nothing
        Set g_DefOptPriceProfile = Nothing
        
        gDBW.usp_PriceProfile_CheckDefaults
        
        Set rs = gDBW.usp_PriceProfile_Get(0)
        While Not rs.EOF
            nID = ReadLng(rs!iPriceProfileID)
            Set aPrProf = g_PriceProfile(nID)
            If aPrProf Is Nothing Then
                Set aPrProf = New EtsGeneralLib.EtsPriceProfileAtom
                aPrProf.ID = nID
                aPrProf.Name = ReadStr(rs!vcPriceProfileName)
                aPrProf.Description = ReadStr(rs!vcPriceProfileDesc)
                aPrProf.DefaultID = ReadByte(rs!tiDefaultID)
                aPrProf.IsOptionProfile = (ReadByte(rs!tiIsOptionProfile) <> 0)
                aPrProf.UseMidMarketForPnL = (ReadByte(rs!tiMidmarketPnL) <> 0)
                
                If aPrProf.IsOptionProfile Then
                    aPrProf.AlwaysUseLast = False
                    aPrProf.BadOptSinglePriceRule = ReadByte(rs!tiSinglePriceRule)
                    aPrProf.BadOptBothPriceRule = ReadByte(rs!tiBothPriceRule)
                    aPrProf.UseZeroBidRule = ReadByte(rs!tiZeroBidRuleForPnL)
                    
                    If aPrProf.BadOptSinglePriceRule <> enObsprReplaceWithLast _
                        And aPrProf.BadOptSinglePriceRule <> enObsprReplaceWithOpposite _
                        And aPrProf.BadOptSinglePriceRule <> enObsprReplaceWithTheo _
                        And aPrProf.BadOptSinglePriceRule <> enObsprReplaceWithZero Then
                        
                        aPrProf.BadOptSinglePriceRule = enObsprReplaceWithLast
                    End If
                    
                    If aPrProf.BadOptBothPriceRule <> enObbprUseLast _
                        And aPrProf.BadOptBothPriceRule <> enObbprUseTheo Then
                        
                        aPrProf.BadOptBothPriceRule = enObbprUseLast
                    End If
                Else
                    aPrProf.AlwaysUseLast = (ReadByte(rs!tiAlwaysLast) <> 0)
                    aPrProf.BadUndPriceRule = ReadByte(rs!tiSinglePriceRule)
                    
                    If aPrProf.BadUndPriceRule <> enUbprCheckTolerance _
                        And aPrProf.BadUndPriceRule <> enUbprDoNotCheckTolerance Then
                        
                        aPrProf.BadUndPriceRule = enUbprDoNotCheckTolerance
                    End If
                End If
                
                g_PriceProfile.Add aPrProf.ID, aPrProf.Name, aPrProf
                
                If g_DefStkPriceProfile Is Nothing Then
                    If aPrProf.DefaultID = 1 And Not aPrProf.IsOptionProfile Then Set g_DefStkPriceProfile = aPrProf
                End If
            
                If g_DefIdxPriceProfile Is Nothing Then
                    If aPrProf.DefaultID = 3 And Not aPrProf.IsOptionProfile Then Set g_DefIdxPriceProfile = aPrProf
                End If
            
                If g_DefOptPriceProfile Is Nothing Then
                    If aPrProf.DefaultID = 1 And aPrProf.IsOptionProfile Then Set g_DefOptPriceProfile = aPrProf
                End If
                
                CheckPriceProfileDefaults aPrProf
            End If
            Set aPrProf = Nothing
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    End If
    
    If (enType And ET_EXP_CALENDAR) = ET_EXP_CALENDAR Then
        sStep = "expiry calendars data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading expiry calendars data...": lblProgress.Refresh
        g_ExpCalendar.Clear
        'Set g_DefExpCalendar = Nothing
        
        Set rs = gDBW.usp_WtdVegaMaturity_Get()
        If Not rs.EOF Then
            g_ExpCalendar.Maturity = ReadLng(rs!iWtdVegaMaturity)
            If g_ExpCalendar.Maturity <= 0 Then g_ExpCalendar.Maturity = 30
        Else
            g_ExpCalendar.Maturity = 30
        End If
        Set rs = Nothing
        
        Set rs = gDBW.usp_MmVegaWeight_Get
        While Not rs.EOF
            dtExpiry = ReadDate(rs!dtExpiryDate)
            
            If dtExpiry > Date Then
                If g_ExpCalendar(CLng(dtExpiry)) Is Nothing Then
                
                    Set aExpMonth = New EtsGeneralLib.EtsExpMonthAtom
                    aExpMonth.ID = nID
                    aExpMonth.Expiry = dtExpiry
                    aExpMonth.VegaWeight = ReadDbl(rs!fVegaWeight)
                    aExpMonth.IsDirty = False
                    
                    If aExpMonth.VegaWeight <= 0# Then
                        aExpMonth.VegaWeight = Sqr(g_ExpCalendar.Maturity / (dtExpiry - Date))
                    End If
                    
                    g_ExpCalendar.Add CLng(dtExpiry), aExpMonth
                    Set aExpMonth = Nothing
                End If
            End If
            
            rs.MoveNext
        Wend
        Set rs = Nothing
    End If
    
'        Set rs = gDBW.usp_ExpiryCalendar_Get(Null)
'        While Not rs.EOF
'            nID = ReadLng(rs!iExpCalendarID)
'            If g_ExpCalendar(nID) Is Nothing Then
'                Set aExpCal = New EtsGeneralLib.EtsExpCalAtom
'                aExpCal.ID = nID
'                aExpCal.Name = ReadStr(rs!vcExpCalendarName)
'                aExpCal.Desc = ReadStr(rs!vcExpCalendarDesc)
'                aExpCal.Hidden = ReadLng(rs!vcFlagHidden)
'
'                Set rs2 = gDBW.usp_ExpiryInCalendar_Get(Null, aExpCal.ID)
'                While Not rs2.EOF
'                    dtExpiry = ReadDate(rs2!dtExpiryDate)
'
'                    If dtExpiry > Date Then
'                        nID = ReadLng(rs2!iExpiryID)
'                        nExpiryMonth = DateSerial(Year(dtExpiry), Month(dtExpiry), Day(dtExpiry))
'                        If aExpCal.ExpByMonth(nExpiryMonth) Is Nothing _
'                            And aExpCal.ExpByID(nExpiryMonth) Is Nothing Then
'
'                            Set aExpMonth = New EtsGeneralLib.EtsExpMonthAtom
'                            aExpMonth.ID = nID
'                            aExpMonth.Expiry = dtExpiry
'                            aExpMonth.ExpiryMonth = nExpiryMonth
'                            aExpMonth.VegaWeight = ReadDbl(rs2!fVegaWeight)
'                            aExpMonth.IsDirty = False
'
'                            If aExpMonth.VegaWeight <= 0# Then
'                                aExpMonth.VegaWeight = Sqr(g_ExpCalendar.Maturity / (dtExpiry - Date))
'                            End If
'
'                            aExpCal.ExpByMonth.Add aExpMonth.ExpiryMonth, aExpMonth
'                            aExpCal.ExpByID.Add aExpMonth.ID, aExpMonth
'
'                            Set aExpMonth = Nothing
'                        End If
'                    End If
'
'                    rs2.MoveNext
'                Wend
'                Set rs2 = Nothing
'
'                g_ExpCalendar.Add aExpCal.ID, aExpCal.Name, aExpCal
'
'                If g_DefExpCalendar Is Nothing Then Set g_DefExpCalendar = aExpCal
'
'                Set aExpCal = Nothing
'            End If
'            rs.MoveNext
'            DoEvents
'        Wend
'        Set rs = Nothing
'    End If
    
    If (enType And ET_UNDERLYING) = ET_UNDERLYING Then
        sStep = "underlyings data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading underlyings data...": lblProgress.Refresh
        g_Underlying.Clear
        'g_UnderlyingBySym.Clear
        g_UnderlyingAll.Clear
        'g_UnderlyingAllBySym.Clear
        g_OptRootByName.Clear
        g_Contract.Clear
        g_ContractAll.Clear
        'g_ContractAllBySym.Clear
        g_Stock.Clear
        'g_StockBySym.Clear
                
        Set rs = gDBW.usp_MmUnderlying_Get(g_CurTraderID)
        While Not rs.EOF
            nID = ReadLng(rs!iContractID)
            If g_UnderlyingAll(nID) Is Nothing Then
                Set aUnd = New EtsGeneralLib.UndAtom
                aUnd.ID = nID
                aUnd.UndType = IIf(ReadLng(rs!iContractTypeID) = enCtStock, enCtStock, enCtIndex)
                aUnd.Symbol = ReadStr(rs!vcSymbol)
                aUnd.ContractName = Trim$(ReadStr(rs!vcContractName))
                
                aUnd.IsAmerican = (ReadByte(rs!tiCalcOptionType) <> 0)
                aUnd.IsHTB = (ReadByte(rs!tiIsHTB) <> 0)
                'aUnd.ExpCalendarID = ReadLng(rs!iExpCalendarID)
    
'                If aUnd.ExpCalendarID = 0 Then
'                    Debug.Assert False
'                    If Not g_DefExpCalendar Is Nothing Then aUnd.ExpCalendarID = g_DefExpCalendar.ID
'                End If

                aUnd.PriceClose = ReadDbl(rs!fPriceClose)
                aUnd.LotSize = 1
                
                aUnd.Skew = ReadDbl(rs!fSkew)
                aUnd.Kurt = ReadDbl(rs!fKurt)
                
                If aUnd.UndType = enCtStock Then
                    Set aDiv = New EtsGeneralLib.EtsIndexDivAtom
                    
                    aDiv.DivType = ReadByte(rs!tiIsDivCustom)
                    
                    aDiv.DivFreq = ReadLng(rs!iDivFreq)
                    aDiv.DivDate = ReadDate(rs!dtDivDate)
                    aDiv.DivAmt = ReadDbl(rs!fDivAmt)
                    aDiv.DivFreqCust = ReadLng(rs!iDivFreqCustom)
                    aDiv.DivDateCust = ReadDate(rs!dtDivDateCustom)
                    aDiv.DivAmtCust = ReadDbl(rs!fDivAmtCustom)
                    Set aUnd.Dividend = aDiv
                Else
                    aUnd.Yield = ReadDbl(rs!fYield)
                    aUnd.IsBasketIndex = (ReadByte(rs!tiIsBasket) <> 0)
                End If
    
                aUnd.IsTraderContract = (g_CurTraderID = ReadLng(rs!iTraderID))
                aUnd.IsActive = (ReadByte(rs!tiIsActive) <> 0)
                Set aUnd.UndPriceProfile = g_PriceProfile(ReadLng(rs!iUndPriceProfileID))
                Set aUnd.OptPriceProfile = g_PriceProfile(ReadLng(rs!iOptPriceProfileID))
                
                If aUnd.UndPriceProfile Is Nothing Then
                    If aUnd.UndType = enCtStock Then
                        Set aUnd.UndPriceProfile = g_DefStkPriceProfile
                    Else
                        Set aUnd.UndPriceProfile = g_DefIdxPriceProfile
                    End If
                End If
                
                If aUnd.OptPriceProfile Is Nothing Then Set aUnd.OptPriceProfile = g_DefOptPriceProfile
                
                Debug.Assert Not aUnd.UndPriceProfile Is Nothing And Not aUnd.OptPriceProfile Is Nothing
                
                aUnd.Volume10Day = ReadLng(rs!iVolume10Day)
                aUnd.Volume5Expiration = ReadLng(rs!iVolume5Expiration)
                
                g_UnderlyingAll.Add aUnd.ID, aUnd.Symbol, aUnd
                'g_UnderlyingAllBySym.Add aUnd.Symbol, aUnd
                
                If aUnd.IsTraderContract Then
                    g_Underlying.Add aUnd.ID, aUnd.Symbol, aUnd
                    'g_UnderlyingBySym.Add aUnd.Symbol, aUnd
                    
                    If aUnd.UndType = enCtStock Then
                        g_Stock.Add aUnd.ID, aUnd.Symbol, aUnd
                        'g_StockBySym.Add aUnd.Symbol, aUnd
                    End If
                End If
                
                If g_ContractAll(aUnd.ID) Is Nothing Then
                    Set aContract = New EtsGeneralLib.EtsContractAtom
                    Set aContract.Und = aUnd
                    
                    g_ContractAll.Add aContract.Und.ID, aContract.Und.Symbol, aContract
                    'g_ContractAllBySym.Add aContract.Und.Symbol, aContract
                    
                    If aUnd.IsTraderContract Then g_Contract.Add aContract.Und.ID, aContract.Und.Symbol, aContract
                    
                    Set aContract = Nothing
                End If
                
            ' --------------------------------------------------------------------
            '   Try to get custom dividend for underlying
               Set rsCust = gDBW.usp_MmCustomDividend_Get(aUnd.ID)
               If Not rsCust.EOF Then
                If aUnd.Dividend Is Nothing Then
                    Set aUndDiv = New EtsGeneralLib.EtsIndexDivAtom
                    Set aUnd.Dividend = aUndDiv
                End If
                
                Set aCustDivColl = aUnd.Dividend.CustomDivs
                If aCustDivColl Is Nothing Then
                    Set aCustDivColl = New EtsGeneralLib.EtsDivColl
                End If
                
               
                While Not rsCust.EOF
                    dDate = ReadDate(rsCust!DivYtes)
                    dAmount = ReadDbl(rsCust!DivAmnt)
                    aCustDivColl.AddNonUnique dDate, dAmount
                    rsCust.MoveNext
                Wend
                rsCust.Close
                Set aUnd.Dividend.CustomDivs = aCustDivColl
                
               End If
               Set rsCust = Nothing
               
            '   Try to get custom dividend for underlying
            ' --------------------------------------------------------------------
                Set aUnd = Nothing
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    
        sStep = "option roots data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading option roots data...": lblProgress.Refresh
    
        Set rs = gDBW.usp_MmOptionRoot_Get(0)
        While Not rs.EOF
            nID = ReadLng(rs!iUnderlyingID)
            Set aUnd = g_UnderlyingAll(nID)
            If Not aUnd Is Nothing Then
                nOptRootID = ReadLng(rs!iRootID)
                If aUnd.Roots(nOptRootID) Is Nothing Then
                    Set aRoot = New EtsGeneralLib.EtsOptRootAtom
                    aRoot.ID = nOptRootID
                    aRoot.UndID = nID
                    aRoot.Name = ReadStr(rs!vcSymbol)
                    aRoot.LotSize = ReadLng(rs!iLotSize)
                    aRoot.IsFit = IIf(ReadByte(rs!tiIsFitEnabled) <> 0, True, False)
                    aRoot.IsSynth = IIf(ReadByte(rs!tiIsSynthetic) <> 0, True, False)
                    
                    If Not aUnd.HaveOptions Then aUnd.HaveOptions = True
                    
                    If aRoot.IsSynth Then
                        If aUnd.SyntheticRoots Is Nothing Then
                            aUnd.HaveSyntheticRoots = True
                            Set aUnd.SyntheticRoots = New EtsGeneralLib.SynthRootColl
                        End If
                        
                        Set aSyntRoot = New EtsGeneralLib.SynthRootAtom
                        aSyntRoot.Basket = (ReadByte(rs!tiSyntheticIsBasket) <> 0)
                        aSyntRoot.CashValue = ReadDbl(rs!fCash)
                        aSyntRoot.Skew = ReadDbl(rs!fSyntheticSkew)
                        aSyntRoot.Kurt = ReadDbl(rs!fSyntheticKurt)
                        aSyntRoot.Yield = ReadDbl(rs!fSyntheticYield)
                        aSyntRoot.OptRootID = nOptRootID
                                                
                        aUnd.SyntheticRoots.Add aSyntRoot.OptRootID, aSyntRoot
                        
                        Set aSyntRoot = Nothing
                    End If
                
                    aUnd.Roots.Add aRoot.ID, aRoot.Name, aRoot
                    
                    If g_OptRootByName(aRoot.Name) Is Nothing Then _
                        g_OptRootByName.Add aRoot.Name, aRoot
                    
                    Set aRoot = Nothing
                End If
                Set aUnd = Nothing
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    
        Set rs = gDBW.usp_MmSyntheticRootParams_Get(0)
        While Not rs.EOF
            nUndID = ReadLng(rs!iUnderlyingID)
            Set aUnd = g_UnderlyingAll(nUndID)
            If Not aUnd Is Nothing Then
                nOptRootID = ReadLng(rs!iOptionRootID)
                
                Set aSyntRoot = aUnd.SyntheticRoots(nOptRootID)
                If Not aSyntRoot Is Nothing Then
                    nSynthUndID = ReadLng(rs!iComponentUnderlyingID)
                    Set aSyntRootComp = aUnd.SyntheticRoots(nSynthUndID)
                    
                    If aSyntRootComp Is Nothing Then
                        Set aSyntRootComp = New EtsGeneralLib.SynthRootCompAtom
                    
                        aSyntRootComp.UndID = nSynthUndID
                        aSyntRootComp.Weight = ReadDbl(rs!fWeight)
                        aSyntRootComp.Settlement = ReadDbl(rs!fStrikeSettlement)
                        
                        aSyntRoot.SynthRootComponents.Add aSyntRootComp.UndID, aSyntRootComp
                        
                        Set aSyntRootComp = Nothing
                    End If
                    
                    Set aSyntRoot = Nothing
                End If
                
                Set aUnd = Nothing
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    
        sStep = "futures roots data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading futures roots data...": lblProgress.Refresh
    
        Set rs = gDBW.usp_MmFutureRoot_Get(0)
        While Not rs.EOF
            nUndID = ReadLng(rs!iUnderlyingID)
            Set aUnd = g_UnderlyingAll(nUndID)
            If Not aUnd Is Nothing Then
                nID = ReadLng(rs!iFutureRootID)
                
                If aUnd.FutRoots(nID) Is Nothing Then
                    Set aFutRoot = New EtsGeneralLib.EtsFutRootAtom
                    
                    aFutRoot.ID = nID
                    aFutRoot.Symbol = ReadStr(rs!vcFutureRootSymbol)
                    aFutRoot.Name = ReadStr(rs!vcFutureRootName)
                    aFutRoot.UndID = nUndID
                    'aFutRoot.MatCalendarID = ReadLng(rs!iMatCalendarID)
                    
'                    If aFutRoot.MatCalendarID = 0 Then
'                        Debug.Assert False
'                        If Not g_DefExpCalendar Is Nothing Then aFutRoot.MatCalendarID = g_DefExpCalendar.ID
'                    End If
                    
                    aFutRoot.FutLotSize = ReadLng(rs!iFutureLotSize)
                    aFutRoot.OptLotSize = ReadLng(rs!iOptionLotSize)
                    
                    aUnd.FutRoots.Add aFutRoot.ID, aFutRoot.Symbol, aFutRoot
                    Set aFutRoot = Nothing
                End If
                
                Set aUnd = Nothing
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    
        sStep = "futures data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading futures data...": lblProgress.Refresh
        
        Set rs = gDBW.usp_MmFuture_Get(0)
        While Not rs.EOF
            nUndID = ReadLng(rs!iUnderlyingID)
            Set aUnd = g_UnderlyingAll(nUndID)
            If Not aUnd Is Nothing Then
                nFutRootID = ReadLng(rs!iFutureRootID)
                Set aFutRoot = aUnd.FutRoots(nFutRootID)
                
                If Not aFutRoot Is Nothing Then
                    nFutID = ReadLng(rs!iFutureID)
                    
                    If aFutRoot.Futures(nFutID) Is Nothing Then
                        Set aFut = New EtsGeneralLib.EtsFutAtom
                        
                        aFut.ID = nFutID
                        aFut.Symbol = ReadStr(rs!vcFutureSymbol)
                        aFut.ContractName = ReadStr(rs!vcFutureName)
                        aFut.FutRootID = nFutRootID
'                        aFut.ExpCalendarID = ReadLng(rs!iExpCalendarID)
'
'                        If aFut.ExpCalendarID = 0 Then
'                            Debug.Assert False
'                            If Not g_DefExpCalendar Is Nothing Then aFut.ExpCalendarID = g_DefExpCalendar.ID
'                        End If
                        
                        'aFut.MaturityID = ReadLng(rs!iMaturityID)
                        aFut.MaturityDate = ReadDate(rs!dtMaturityDate)
                        aFut.IsAmerican = (ReadByte(rs!tiCalcOptionType) <> 0)
                        aFut.IsActive = (ReadByte(rs!tiIsActive) <> 0)
                        aFut.PriceClose = ReadDbl(rs!fPriceClose)
                        aFut.HaveOptions = (ReadLng(rs!iHaveOptions) <> 0)
                        
                        Set aFut.UndPriceProfile = g_PriceProfile(ReadLng(rs!iUndPriceProfileID))
                        Set aFut.OptPriceProfile = g_PriceProfile(ReadLng(rs!iOptPriceProfileID))
                        
                        If aFut.UndPriceProfile Is Nothing Then Set aFut.UndPriceProfile = g_DefStkPriceProfile
                        If aFut.OptPriceProfile Is Nothing Then Set aFut.OptPriceProfile = g_DefOptPriceProfile
                        
                        Debug.Assert Not aFut.UndPriceProfile Is Nothing And Not aFut.OptPriceProfile Is Nothing
                        
                        If Not aUnd.HaveFutures Then aUnd.HaveFutures = True
                        
                        aFutRoot.Futures.Add aFut.ID, aFut.Symbol, aFut
                        
                        If g_ContractAll(aFut.ID) Is Nothing Then
                            Set aContract = New EtsGeneralLib.EtsContractAtom
                            Set aContract.Und = aUnd
                            Set aContract.Fut = aFut
                            Set aContract.FutRoot = aFutRoot
                            
                            g_ContractAll.Add aContract.Fut.ID, aContract.Fut.Symbol, aContract
                            'g_ContractAllBySym.Add aContract.Fut.Symbol, aContract
                            
                            If aUnd.IsTraderContract Then g_Contract.Add aContract.Fut.ID, aContract.Fut.Symbol, aContract
                            
                            Set aContract = Nothing
                        End If
                        
                        Set aFut = Nothing
                    End If
                
                    Set aFutRoot = Nothing
                End If
                
                Set aUnd = Nothing
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    End If
    
    If (enType And ET_TRADER_GROUP) = ET_TRADER_GROUP Then
        sStep = "trader groups data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading trader groups data...": lblProgress.Refresh
        g_TraderGroup.Clear
        
        ' add default trader group
        Set aTraderGroup = New EtsGeneralLib.EtsTraderGroupAtom
        aTraderGroup.ID = 0
        aTraderGroup.Name = "<Defualt>"
        aTraderGroup.Desc = "Default Trader Group"
        g_TraderGroup.Add aTraderGroup.ID, aTraderGroup.Name, aTraderGroup
        Set aTraderGroup = Nothing
        
        Set rs = gDBW.usp_TraderGroup_Get(0)
        While Not rs.EOF
            nID = ReadLng(rs!iTraderGroupID)
            If g_TraderGroup(nID) Is Nothing Then
                Set aTraderGroup = New EtsGeneralLib.EtsTraderGroupAtom
                aTraderGroup.ID = nID
                aTraderGroup.Name = Trim$(ReadStr(rs!vcGroupName))
                aTraderGroup.Desc = ReadStr(rs!vcGroupDesc)
            
                g_TraderGroup.Add aTraderGroup.ID, aTraderGroup.Name, aTraderGroup
                Set aTraderGroup = Nothing
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    End If
    
    If (enType And ET_TRADER) = ET_TRADER Then
        sStep = "traders data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading traders data...": lblProgress.Refresh
        g_Trader.Clear
        Set rs = gDBW.usp_Trader_Get(g_CurTraderID)
        While Not rs.EOF
            nID = ReadLng(rs!iTraderID)
            If g_Trader(nID) Is Nothing Then
                Set aTrader = New EtsGeneralLib.EtsTraderAtom
                aTrader.ID = nID
                aTrader.Name = Trim$(ReadStr(rs!vcAcronym))
                aTrader.TntAccount = UCase$(Left$(aTrader.Name, TNT_ACCOUNT_MAXLEN))
                aTrader.GroupID = ReadLng(rs!iTraderGroupID)
                
                g_Trader.Add aTrader.ID, aTrader.Name, aTrader
                
                Set aTraderGroup = g_TraderGroup(aTrader.GroupID)
                If Not aTraderGroup Is Nothing Then
                    aTraderGroup.Trader.Add aTrader.ID, aTrader.Name, aTrader
                    Set aTraderGroup = Nothing
                End If
            
                Set aTrader = Nothing
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    
        Set rs = gDBW.usp_TraderContractByTrader_Get(g_CurTraderID)
        While Not rs.EOF
            nID = ReadLng(rs!iTraderID)
            Set aTrader = g_Trader(nID)
            If Not aTrader Is Nothing Then
                nID = ReadLng(rs!iContractID)
                Set aUnd = g_Underlying(nID)
                If Not aUnd Is Nothing And aTrader.Und(nID) Is Nothing Then
                    Set aTrdUnd = New EtsGeneralLib.EtsTraderUndAtom
                    Set aTrdUnd.Und = aUnd
                    
                    aTrader.Und.Add aTrdUnd.Und.ID, aTrdUnd.Und.Symbol, aTrdUnd
                    
                    Set aTrdUnd = Nothing
                End If
                Set aUnd = Nothing
                Set aTrader = Nothing
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    End If
    
    If (enType And ET_UNDERLYING_GROUP) = ET_UNDERLYING_GROUP Then
        sStep = "underlying groups data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading underlying groups data...": lblProgress.Refresh
        g_UnderlyingGroup.Clear
        Set rs = gDBW.usp_ContractGroup_Get(Null)
        While Not rs.EOF
            nID = ReadLng(rs!iGroupID)
            If g_UnderlyingGroup(nID) Is Nothing Then
                Set aUndGroup = New EtsGeneralLib.EtsUndGroupAtom
                aUndGroup.ID = nID
                aUndGroup.Name = ReadStr(rs!vcGroupName)
                aUndGroup.Desc = ReadStr(rs!vcDescription)
                
                Set rs2 = gDBW.usp_ContractInGroup_Get(aUndGroup.ID)
                While Not rs2.EOF
                    nID = ReadLng(rs2!iContractID)
                    
                    If g_CurTraderID = 0 Then
                        Set aUnd = g_UnderlyingAll(nID)
                    Else
                        Set aUnd = g_Underlying(nID)
                    End If
                    
                    If Not aUnd Is Nothing Then
                        If aUndGroup.Und(nID) Is Nothing Then
                            aUndGroup.Und.Add aUnd.ID, aUnd.Symbol, aUnd
                        End If
                        Set aUnd = Nothing
                    End If
                    rs2.MoveNext
                Wend
                Set rs2 = Nothing
            
                If g_CurTraderID = 0 Or aUndGroup.Und.Count > 0 Then
                    g_UnderlyingGroup.Add aUndGroup.ID, aUndGroup.Name, aUndGroup
                End If
                
                Set aUndGroup = Nothing
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    End If
    
'    If (enType And ET_RM_SCENARIO) = ET_RM_SCENARIO Then
'        sStep = "risk matrix scenarios data."
'        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading risk matrix scenarios data...": lblProgress.Refresh
'        g_RmScenario.Clear
'        Set rs = gDBW.usp_RMScenario_Get(Null)
'        While Not rs.EOF
'            nID = ReadLng(rs!iRMScenarioID)
'            Set aScn = g_RmScenario(CStr(nID))
'            If aScn Is Nothing Then
'                Set aScn = g_RmScenario.Add(CStr(nID))
'                aScn.ID = nID
'
'                aScn.ScenarioName = ReadStr(rs!vcScenarioName)
'                aScn.Description = ReadStr(rs!vcDescription)
'
'                aScn.Axis(RMA_HORZ) = ReadByte(rs!tiType1)
'                aScn.Points(RMA_HORZ) = ReadLng(rs!iPoints1)
'                aScn.Step(RMA_HORZ) = ReadDbl(rs!fStep1)
'                aScn.Units(RMA_HORZ) = ReadByte(rs!tiIsAbs1)
'
'                aScn.Axis(RMA_VERT) = ReadByte(rs!tiType2)
'                aScn.Points(RMA_VERT) = ReadLng(rs!iPoints2)
'                aScn.Step(RMA_VERT) = ReadDbl(rs!fStep2)
'                aScn.Units(RMA_VERT) = ReadByte(rs!tiIsAbs2)
'
'                aScn.VolaShiftType = IIf(ReadByte(rs!tiVolaShift) <> 0, RMVS_WEIGHTED, RMVS_COMMON)
'
'                aScn.FixValues
'
'                Set aScn = Nothing
'            End If
'            rs.MoveNext
'            DoEvents
'        Wend
'        Set rs = Nothing
'    End If
    
    If (enType And ET_INDEX) = ET_INDEX Then
        sStep = "indices data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading indices data...": lblProgress.Refresh
        g_Index.Clear
        g_BasketIndex.Clear
        'g_BasketIndexUndBySym.Clear
        Set rs = gDBW.usp_MmIndex_Get()
        While Not rs.EOF
            nID = ReadLng(rs!iContractID)
            If g_Index(nID) Is Nothing Then
                Set aIdx = New EtsGeneralLib.IndexAtom
                aIdx.ID = nID
                aIdx.Symbol = ReadStr(rs!vcSymbol)
                aIdx.IsBasket = (ReadByte(rs!tiIsBasket) <> 0)
                Set aIdx.UndPriceProfile = g_UnderlyingAll(nID).UndPriceProfile
                Set aIdx.OptPriceProfile = g_UnderlyingAll(nID).OptPriceProfile
                g_Index.Add aIdx.ID, aIdx.Symbol, aIdx
                Set aIdx = Nothing
            End If
            rs.MoveNext
        Wend
        Set rs = Nothing
    
        sStep = "index components data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading index components data...": lblProgress.Refresh
        Set rs = gDBW.usp_MmIndexDefinition_Get()
        While Not rs.EOF
            dWeight = ReadDbl(rs!fWeight)
            
            If dWeight > 0# Then
                nIdxID = ReadLng(rs!iIndexID)
                nID = ReadLng(rs!iStockID)
                Set aIdx = g_Index(nIdxID)
                If Not aIdx Is Nothing Then
                
                    Set aIdxComp = aIdx.Components(nID)
                    If aIdxComp Is Nothing Then
                        Set aIdxComp = aIdx.Components.Add(nID)
                        aIdxComp.ID = nID
                        aIdxComp.Weight = dWeight
                        aIdxComp.IsBasketComponent = True
                    End If
                    
                    If aIdx.IsBasket And g_BasketIndex(aIdx.ID) Is Nothing Then
                        g_BasketIndex.Add aIdx.ID, aIdx.Symbol, aIdx
                        'Set aUnd = g_UnderlyingAll(aIdx.ID)
                        'g_BasketIndexUndBySym.Add aUnd.Symbol, aUnd
                        Set aUnd = Nothing
                    End If
                        
                    Set aIdxComp = Nothing
                    Set aIdx = Nothing
                End If
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
        
        sStep = "index underlyings beta."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading index underlyings beta...": lblProgress.Refresh
        Set rs = gDBW.usp_MmIndexUnderlyingBeta_Get()
        While Not rs.EOF
            dBeta = ReadDbl(rs!fBeta)
            
            If dBeta <> 0# Then
                nIdxID = ReadLng(rs!iIndexID)
                nID = ReadLng(rs!iContractID)
                Set aIdx = g_Index(nIdxID)
                If Not aIdx Is Nothing Then
                
                    Set aIdxComp = aIdx.Components(nID)
                    If aIdxComp Is Nothing Then
                        Set aIdxComp = aIdx.Components.Add(nID)
                        aIdxComp.ID = nID
                    End If
                    
                    aIdxComp.Beta = dBeta
                    
                    If dBeta <> 0# Then
                        aIdx.HaveComponentBetas = True
                    End If
                    
                    Set aIdxComp = Nothing
                    Set aIdx = Nothing
                End If
            End If
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
        
'        sStep = "synthetic roots index betas."
'        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading synthetic roots index betas...": lblProgress.Refresh
'        Set rs = gDBW.usp_MmSyntheticIndexBeta_Get
'        While Not rs.EOF
'            dBeta = ReadDbl(rs!fBeta)
'
'            If dBeta <> 0# Then
'                nIdxID = ReadLng(rs!iIndexID)
'                nID = ReadLng(rs!iOptRootID)
'                Set aIdx = g_Index(nIdxID)
'                If Not aIdx Is Nothing Then
'
'                    Set aIdxComp = aIdx.SyntheticRootBetas(nID)
'                    If aIdxComp Is Nothing Then
'                        Set aIdxComp = aIdx.SyntheticRootBetas.Add(nID)
'                        aIdxComp.ID = nID
'                        aIdxComp.Beta = dBeta
'
'                        If dBeta <> 0# Then
'                            aIdx.HaveComponentBetas = True
'                        End If
'                    End If
'
'                    Set aIdxComp = Nothing
'                    Set aIdx = Nothing
'                End If
'            End If
'            rs.MoveNext
'            DoEvents
'        Wend
'        Set rs = Nothing
        
        For Each aIdx In g_Index
            If aIdx.IsBasket Then
                aIdx.InitBasketDivs g_UnderlyingAll
            End If
        Next
    End If
    
    ' init synthetic roots dividends
    If (enType And ET_UNDERLYING) = ET_UNDERLYING Then
        sStep = "synthetic roots dividends "
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Initialize synthetic roots dividends...": lblProgress.Refresh
        For Each aUnd In g_UnderlyingAll
            If aUnd.HaveSyntheticRoots Then
                If Not aUnd.SyntheticRoots Is Nothing Then
                    For Each aSyntRoot In aUnd.SyntheticRoots
                        aSyntRoot.InitBasketDivs g_UnderlyingAll, g_Index
                        DoEvents
                    Next
                End If
            End If
            DoEvents
        Next
    End If
    
    If (enType And ET_EXCHANGE) = ET_EXCHANGE Then
        sStep = "exchanges data."
        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading exchanges data...": lblProgress.Refresh
        g_Exch.Clear
        Set aExch = New EtsGeneralLib.ExchAtom
        aExch.ID = 0
        aExch.Code = ""
        aExch.Name = "<Primary>"
        aExch.IsUnderlying = 1
        aExch.IsOption = 1
        g_Exch.Add aExch.ID, aExch.Code, aExch
        Set aExch = Nothing
        
        Set rs = gDBW.usp_Exchange_Get(Null)
        While Not rs.EOF
            nID = ReadLng(rs!iExchangeId)
            Set aExch = g_Exch(nID)
            If aExch Is Nothing Then
                Set aExch = New EtsGeneralLib.ExchAtom
                aExch.ID = nID
                aExch.Name = ReadStr(rs!vcExchangeName)
                aExch.IsUnderlying = ReadByte(rs!tiIsUnderlying)
                aExch.IsOption = ReadByte(rs!tiIsOption)
                aExch.Code = ReadStr(rs!vcExchangeCode)
                g_Exch.Add aExch.ID, aExch.Code, aExch
            End If
            Set aExch = Nothing
            rs.MoveNext
            DoEvents
        Wend
        Set rs = Nothing
    End If
    
'    If (enType And ET_ORDER_EXEC_DEST) = ET_ORDER_EXEC_DEST Then
'        sStep = "execution destinations data."
'        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading execution destinations data...": lblProgress.Refresh
'        g_OrderExecDest.Clear
'
'        ' add default destination
'        Set aExecDest = New EtsMmGeneralLib.MmOrderExecDestAtom
'        aExecDest.ID = 0
'        aExecDest.Code = ""
'        aExecDest.Name = "<Default>"
'        aExecDest.IsOption = True
'        aExecDest.IsStock = True
'        g_OrderExecDest.Add aExecDest.ID, aExecDest.Code, aExecDest
'        Set aExecDest = Nothing
'
'        ' load destinations
'        Set rs = gDBW.usp_OrderExecDest_Get(0)
'        While Not rs.EOF
'            nID = ReadLng(rs!iDestID)
'            Set aExecDest = g_OrderExecDest(nID)
'            If aExecDest Is Nothing Then
'                Set aExecDest = New EtsMmGeneralLib.MmOrderExecDestAtom
'                aExecDest.ID = nID
'                aExecDest.Code = ReadStr(rs!vcCode)
'                aExecDest.Name = ReadStr(rs!vcName)
'                aExecDest.IsOption = ReadByte(rs!tiIsOption)
'                aExecDest.IsStock = ReadByte(rs!tiIsStock)
'                g_OrderExecDest.Add aExecDest.ID, aExecDest.Code, aExecDest
'            End If
'            Set aExecDest = Nothing
'            rs.MoveNext
'            DoEvents
'        Wend
'        Set rs = Nothing
'    End If
'
'    If (enType And ET_TNT_CNT_PTY) = ET_TNT_CNT_PTY Then
'        sStep = "conterparty data."
'        If Not lblProgress Is Nothing Then lblProgress.Caption = "Loading conterparty data...": lblProgress.Refresh
'        g_TntCntPty.Clear
'        g_TntCntPtyByName.Clear
'
'        Set rs = gDBW.usp_TntCounterParty_Get(0)
'        While Not rs.EOF
'            nID = ReadLng(rs!iCptID)
'            Set aCntPty = g_TntCntPty(nID)
'            If aCntPty Is Nothing Then
'                Set aCntPty = New EtsMmGeneralLib.MmTntCounterPartyAtom
'                aCntPty.ID = nID
'                aCntPty.Name = ReadStr(rs!vcName)
'                aCntPty.Desc = ReadStr(rs!vcDesc)
'
'                g_TntCntPty.Add aCntPty.ID, aCntPty.Name, aCntPty
'                g_TntCntPtyByName.Add aCntPty.Name, aCntPty
'            End If
'            Set aCntPty = Nothing
'            rs.MoveNext
'            DoEvents
'        Wend
'        Set rs = Nothing
'    End If
    
    Exit Sub
EH:
    Dim sDescription$, nHelpContext&, sHelpFile$, nNumber&, sSource$
    sDescription = Err.Description
    nHelpContext = Err.HelpContext
    sHelpFile = Err.HelpFile
    nNumber = Err.Number
    If sStep = "" Then sStep = "common data."
    sSource = "Fail to load " & sStep & vbCrLf & Err.Source
    
    'Set aScn = Nothing
    'Set aExpCal = Nothing
    Set aExpMonth = Nothing
    Set aUnd = Nothing
    Set aIdx = Nothing
    Set aIdxComp = Nothing
    Set aExch = Nothing
    Set aSyntRoot = Nothing
    Set aSyntRootComp = Nothing
    Set aPrProf = Nothing
    Set aRoot = Nothing
'    Set aExecDest = Nothing
    Set aTrader = Nothing
    Set aBroker = Nothing
    Set aStrategy = Nothing
    Set aUndGroup = Nothing
    Set aTraderGroup = Nothing
'    Set aCntPty = Nothing
    Set aTrdUnd = Nothing
    Set aFutRoot = Nothing
    Set aFut = Nothing
    Set aContract = Nothing
    
    If (enType And ET_TRADER) = ET_TRADER Then
        g_Trader.Clear
    End If
    
    If (enType And ET_TRADER_GROUP) = ET_TRADER_GROUP Then
        g_TraderGroup.Clear
    End If
    
    If (enType And ET_STRATEGY) = ET_STRATEGY Then
        g_Strategy.Clear
    End If
    
    If (enType And ET_BROKER) = ET_BROKER Then
        g_Broker.Clear
        g_ClearingBroker.Clear
    End If
    
    If (enType And ET_UNDERLYING) = ET_UNDERLYING Then
        g_Underlying.Clear
        'g_UnderlyingBySym.Clear
        g_UnderlyingAll.Clear
        'g_UnderlyingAllBySym.Clear
        g_Contract.Clear
        g_ContractAll.Clear
        'g_ContractAllBySym.Clear
        g_OptRootByName.Clear
        g_Stock.Clear
        'g_StockBySym.Clear
    End If
    
    If (enType And ET_UNDERLYING_GROUP) = ET_UNDERLYING_GROUP Then
        g_UnderlyingGroup.Clear
    End If
    
'    If (enType And ET_RM_SCENARIO) = ET_RM_SCENARIO Then
'        g_RmScenario.Clear
'    End If
    
    If (enType And ET_EXP_CALENDAR) = ET_EXP_CALENDAR Then
        g_ExpCalendar.Clear
        'Set g_DefExpCalendar = Nothing
    End If

    If (enType And ET_INDEX) = ET_INDEX Then
        g_Index.Clear
        g_BasketIndex.Clear
        'g_BasketIndexUndBySym.Clear
    End If
    
    If (enType And ET_EXCHANGE) = ET_EXCHANGE Then
        g_Exch.Clear
    End If
    
    If (enType And ET_PRICE_PROFILE) = ET_PRICE_PROFILE Then
        g_PriceProfile.Clear
    End If
    
'    If (enType And ET_ORDER_EXEC_DEST) = ET_ORDER_EXEC_DEST Then
'        g_OrderExecDest.Clear
'    End If
'
'    If (enType And ET_TNT_CNT_PTY) = ET_TNT_CNT_PTY Then
'        g_TntCntPty.Clear
'        g_TntCntPtyByName.Clear
'    End If
    
    Err.Raise nNumber, sSource, sDescription, sHelpFile, nHelpContext
End Sub


Private Sub CheckPriceProfileDefaults(ByRef aPrProf As EtsGeneralLib.EtsPriceProfileAtom)
    On Error Resume Next
    If aPrProf.IsOptionProfile Then
        Select Case aPrProf.DefaultID
            Case 1
                aPrProf.UseMidMarketForPnL = True
                
            Case 2
                aPrProf.UseMidMarketForPnL = False
                
        End Select
    Else
        Select Case aPrProf.DefaultID
            Case 1
                aPrProf.AlwaysUseLast = False
                aPrProf.UseMidMarketForPnL = True
            
            Case 2
                aPrProf.AlwaysUseLast = False
                aPrProf.UseMidMarketForPnL = False
            
            Case 3
                aPrProf.AlwaysUseLast = True
                aPrProf.UseMidMarketForPnL = False
                aPrProf.BadUndPriceRule = enUbprDoNotCheckTolerance
        End Select
    End If
End Sub


