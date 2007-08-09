VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsAuxRiskViewCalc"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private m_bShutDown As Boolean
Private m_bInCalc As Boolean
Public m_bHaveFlexOptions As Boolean     ' true if riskview contains flex options - need it it to enforce recalc even when
                                        ' there are not any quotes from feed

Public UndUpdated&
Public OptUpdated&
Public FutUpdated&
Private m_nGreeksMask&

Private m_ProcessDelay As EtsGeneralLib.EtsProcessDelay
Public m_dtCalcDateShift As Date

Public UndCount&
Public OptCount&
Public FutCount&

'Public QuoteReqsAll As New EtsMmRisksLib.MmRvReqColl ' all quote requests
'Public QuoteReqsGrp As New EtsMmRisksLib.MmRvReqColl ' referencies to group requests
'Public QuoteReqsNonGrp As New EtsMmRisksLib.MmRvReqColl ' referencies to non-group requests

Private m_Aux As clsAuxRiskView
Private m_DateShift As Integer

'ACH_START
Public Property Let DateShift(ShiftDate As Integer)
    m_DateShift = ShiftDate
End Property

Public Property Get DateShift() As Integer
    DateShift = m_DateShift
End Property
'ACH_END

'ACH_START
Public Property Let CalcDate(ShiftDate As Date)
    m_dtCalcDateShift = ShiftDate
End Property

Public Property Get CalcDate() As Date
    CalcDate = m_dtCalcDateShift
End Property
'ACH_END
Public Property Get QuoteReqsAll() As EtsMmRisksLib.MmRvReqColl
    Set QuoteReqsAll = m_Aux.RiskView.QuoteReqsAll
End Property

Public Sub Init(aAux As clsAuxRiskView)
    On Error Resume Next
    m_bShutDown = False
    UndUpdated = 0
    OptUpdated = 0
    FutUpdated = 0
    UndCount = 0
    OptCount = 0
    FutCount = 0
    m_nGreeksMask = GM_ALL
    m_dtCalcDateShift = Date
    Set m_Aux = aAux
    Set m_ProcessDelay = New EtsGeneralLib.EtsProcessDelay
End Sub
Public Sub SetCalcDateShift(dtCalcDateShift As Date)
    If CLng(dtCalcDateShift) >= CLng(DateTime.Now) Then
        m_dtCalcDateShift = dtCalcDateShift
    Else
        LogEvent EVENT_ERROR, "You ented wrong data into Data Calculation Shift - " + CStr(dtCalcDateShift)
    End If
End Sub

Public Sub Term()
    On Error Resume Next
    m_bShutDown = True
    m_ProcessDelay.Interrupt
    Set m_ProcessDelay = Nothing
    
    'QuoteReqsNonGrp.Clear
    'QuoteReqsGrp.Clear
    QuoteReqsAll.Clear
    Set m_Aux = Nothing
End Sub

Public Function CantStartRealTime() As Boolean
    CantStartRealTime = CBool(OptCount > g_Params.MaxRTOptCount)
    If CantStartRealTime Then
        MsgBox "Can't start Real Time Mode because Options number is " & OptCount & " and it must be less or equal " & g_Params.MaxRTOptCount & ". Please use filters to decrease Options number.", vbExclamation
    End If
End Function

Public Sub UnderlyingsCalc(ByVal bCalcGreeks As Boolean, ByVal bUpdateVola As Boolean, Optional ByVal bRealtimeCalc As Boolean = False, Optional ByVal bTotalsOnly As Boolean = False)
    On Error Resume Next
    If m_bShutDown Or m_bInCalc Then Exit Sub
    m_bInCalc = True
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogSystem, "UnderlyingsCalc Enter", "clsAuxRiskViewCalc"
    
    If g_Params.UseCalcSleep Then
        m_ProcessDelay.Reset
        m_ProcessDelay.Frequency = g_Params.CalcSleepFreq
        m_ProcessDelay.Duration = g_Params.CalcSleepAmt
    End If
    
    Err.Clear
    
    m_Aux.RiskView.Calc bTotalsOnly, m_nGreeksMask, bCalcGreeks, bUpdateVola, bRealtimeCalc, _
                IIf(g_Params.UseCalcSleep, m_ProcessDelay, Nothing), _
                (g_Params.PnLCalcType = PNLCT_LTD), g_Params.CalcModel, g_Params.UseTheoVolatility, _
                g_Params.UseTheoNoBid, g_Params.UseTheoBadMarketVola, g_Params.UndPriceToleranceValue, _
                g_Params.PriceRoundingRule, OptUpdated, UndUpdated, FutUpdated, m_dtCalcDateShift
                
    Debug.Assert Err.Number = 0
    m_bInCalc = False
    
    If Err.Number = 0 Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogSystem, "UnderlyingsCalc Exit", "clsAuxRiskViewCalc"
    Else
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogFaults, "FAIL: UnderlyingsCalc Exit with error " & CStr(Err.Number) & " " & Err.Description, "clsAuxRiskViewCalc"
    End If
    
End Sub

Public Sub UnderlyingCalc(ByRef aUnd As EtsMmRisksLib.MmRvUndAtom, ByVal bCalcGreeks As Boolean, ByVal bUpdateVola As Boolean, _
                        Optional ByVal bRealtimeCalc As Boolean = False, Optional ByVal bClearSynthGreeks As Boolean = True)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
       
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogSystem, "UnderlyingCalc Enter", "clsAuxRiskViewCalc"
    
    Err.Clear
    aUnd.Calc m_Aux.Und, m_nGreeksMask, bCalcGreeks, bUpdateVola, bRealtimeCalc, bClearSynthGreeks, Nothing, _
                (g_Params.PnLCalcType = PNLCT_LTD), g_Params.CalcModel, g_Params.UseTheoVolatility, _
                g_Params.UseTheoNoBid, g_Params.UseTheoBadMarketVola, g_Params.UndPriceToleranceValue, _
                g_Params.PriceRoundingRule, 0, 0, 0, m_dtCalcDateShift
                
    Debug.Assert Err.Number = 0
    
    If Err.Number = 0 Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogSystem, "UnderlyingCalc Exit", "clsAuxRiskViewCalc"
    Else
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogFaults, "FAIL: UnderlyingCalc Exit with error " & CStr(Err.Number) & " " & Err.Description, "clsAuxRiskViewCalc"
    End If
        
End Sub

Public Sub UnderlyingsCalcWtdVega()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    Err.Clear
    m_Aux.Grp.CalcWtdVega m_Aux.Und, g_ExpCalendar
    Debug.Assert Err.Number = 0
End Sub
Public Sub ChangeQtyDailyLTD(ByRef aUnd As EtsMmRisksLib.MmRvUndAtom, _
                             ByRef aPos As EtsMmRisksLib.MmRvPosAtom, _
                             ByRef aTrd As EtsMmGeneralLib.MmTradeInfoAtom)
                             
    On Error Resume Next
    Dim nQty&, nQtyInShares&
        
    nQty = aTrd.Quantity * IIf(aTrd.IsBuy, 1, -1)
    nQtyInShares = nQty * aPos.Quote.LotSize
            
    If aTrd.IsBuy Then
        If aPos.QtyLTDBuy = BAD_LONG_VALUE Then aPos.QtyLTDBuy = 0
        aPos.QtyLTDBuy = aPos.QtyLTDBuy + nQtyInShares
        If aTrd.IsPosition Then
            If aPos.Quote.Price.Close >= 0# Then
                If aPos.PosLTDBuy = BAD_DOUBLE_VALUE Then aPos.PosLTDBuy = 0
                aPos.PosLTDBuy = aPos.PosLTDBuy + aPos.Quote.Price.Close * nQtyInShares
            End If
        Else
            If aPos.PosLTDBuy = BAD_DOUBLE_VALUE Then aPos.PosLTDBuy = 0
            aPos.PosLTDBuy = aPos.PosLTDBuy + aTrd.Price * nQtyInShares
        End If
    
        If aTrd.TradeDate < Date Then
            If aPos.QtyDailyPrevDateBuy = BAD_LONG_VALUE Then aPos.QtyDailyPrevDateBuy = 0
            aPos.QtyDailyPrevDateBuy = aPos.QtyDailyPrevDateBuy + nQtyInShares
            If aPos.Quote.Price.Close >= 0# Then
                If aPos.PosDailyPrevDateBuy = BAD_DOUBLE_VALUE Then aPos.PosDailyPrevDateBuy = 0
                aPos.PosDailyPrevDateBuy = aPos.PosDailyPrevDateBuy + aPos.Quote.Price.Close * nQtyInShares
            ElseIf Not aTrd.IsPosition Then
                If aPos.PosDailyPrevDateBuy = BAD_DOUBLE_VALUE Then aPos.PosDailyPrevDateBuy = 0
                aPos.PosDailyPrevDateBuy = aPos.PosDailyPrevDateBuy + aTrd.Price * nQtyInShares
            End If
        Else
            If aPos.QtyDailyTodayBuy = BAD_LONG_VALUE Then aPos.QtyDailyTodayBuy = 0
            aPos.QtyDailyTodayBuy = aPos.QtyDailyTodayBuy + nQtyInShares
            If aTrd.IsPosition Then
                If aPos.Quote.Price.Close >= 0# Then
                    If aPos.PosDailyTodayBuy = BAD_DOUBLE_VALUE Then aPos.PosDailyTodayBuy = 0
                    aPos.PosDailyTodayBuy = aPos.PosDailyTodayBuy + aPos.Quote.Price.Close * nQtyInShares
                End If
            Else
                If aPos.PosDailyTodayBuy = BAD_DOUBLE_VALUE Then aPos.PosDailyTodayBuy = 0
                aPos.PosDailyTodayBuy = aPos.PosDailyTodayBuy + aTrd.Price * nQtyInShares
            End If
        End If
    Else
        If aPos.QtyLTDSell = BAD_LONG_VALUE Then aPos.QtyLTDSell = 0
        aPos.QtyLTDSell = aPos.QtyLTDSell + nQtyInShares
        If aTrd.IsPosition Then
            If aPos.Quote.Price.Close >= 0# Then
                If aPos.PosLTDSell = BAD_DOUBLE_VALUE Then aPos.PosLTDSell = 0
                aPos.PosLTDSell = aPos.PosLTDSell + aPos.Quote.Price.Close * nQtyInShares
            End If
        Else
            If aPos.PosLTDSell = BAD_DOUBLE_VALUE Then aPos.PosLTDSell = 0
            aPos.PosLTDSell = aPos.PosLTDSell + aTrd.Price * nQtyInShares
        End If
    
        If aTrd.TradeDate < Date Then
            If aPos.QtyDailyPrevDateSell = BAD_LONG_VALUE Then aPos.QtyDailyPrevDateSell = 0
            aPos.QtyDailyPrevDateSell = aPos.QtyDailyPrevDateSell + nQtyInShares
            If aPos.Quote.Price.Close >= 0# Then
                If aPos.PosDailyPrevDateSell = BAD_DOUBLE_VALUE Then aPos.PosDailyPrevDateSell = 0
                aPos.PosDailyPrevDateSell = aPos.PosDailyPrevDateSell + aPos.Quote.Price.Close * nQtyInShares
            ElseIf Not aTrd.IsPosition Then
                If aPos.PosDailyPrevDateSell = BAD_DOUBLE_VALUE Then aPos.PosDailyPrevDateSell = 0
                aPos.PosDailyPrevDateSell = aPos.PosDailyPrevDateSell + aTrd.Price * nQtyInShares
            End If
        Else
            If aPos.QtyDailyTodaySell = BAD_LONG_VALUE Then aPos.QtyDailyTodaySell = 0
            aPos.QtyDailyTodaySell = aPos.QtyDailyTodaySell + nQtyInShares
            If aTrd.IsPosition Then
                If aPos.Quote.Price.Close >= 0# Then
                    If aPos.PosDailyTodaySell = BAD_DOUBLE_VALUE Then aPos.PosDailyTodaySell = 0
                    aPos.PosDailyTodaySell = aPos.PosDailyTodaySell + aPos.Quote.Price.Close * nQtyInShares
                End If
            Else
                If aPos.PosDailyTodaySell = BAD_DOUBLE_VALUE Then aPos.PosDailyTodaySell = 0
                aPos.PosDailyTodaySell = aPos.PosDailyTodaySell + aTrd.Price * nQtyInShares
            End If
        End If
    End If
    
    aPos.Qty = aPos.Qty + nQty
    aPos.QtyInShares = aPos.QtyInShares + nQtyInShares
    
End Sub

Public Sub CalcOptionGreeks(ByRef aUnd As EtsMmRisksLib.MmRvUndAtom, aPos As EtsMmRisksLib.MmRvPosAtom, ByVal nMask As Long)
     On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogSystem, "CalcOptionGreeks Enter", "clsAuxRiskViewCalc"
    
    Err.Clear
    aPos.CalcOptionGreeks m_Aux.Und, aUnd, _
            aUnd.UndPriceProfile.GetUndPriceMid(aUnd.Price.Bid, aUnd.Price.Ask, aUnd.Price.Last, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule), _
            m_nGreeksMask, (g_Params.PnLCalcType = PNLCT_LTD), g_Params.CalcModel, g_Params.UseTheoVolatility, _
            g_Params.UseTheoNoBid, g_Params.UseTheoBadMarketVola, g_Params.UndPriceToleranceValue, _
            g_Params.PriceRoundingRule, m_dtCalcDateShift

    Debug.Assert Err.Number = 0
    
    If Err.Number = 0 Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogSystem, "CalcOptionGreeks Exit", "clsAuxRiskViewCalc"
    Else
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogFaults, "FAIL: CalcOptionGreeks Exit with error " & CStr(Err.Number) & " " & Err.Description, "clsAuxRiskViewCalc"
    End If
    
End Sub

Public Sub CalcFutOptionGreeks(ByRef aUnd As EtsMmRisksLib.MmRvUndAtom, aPos As EtsMmRisksLib.MmRvPosAtom, ByVal nMask As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogSystem, "CalcFutOptionGreeks Enter", "clsAuxRiskViewCalc"
    
    Err.Clear
    aPos.CalcFutOptionGreeks aUnd, _
            aUnd.UndPriceProfile.GetUndPriceMid(aUnd.Price.Bid, aUnd.Price.Ask, aUnd.Price.Last, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule), _
            m_nGreeksMask, (g_Params.PnLCalcType = PNLCT_LTD), g_Params.CalcModel, g_Params.UseTheoVolatility, _
            g_Params.UseTheoNoBid, g_Params.UseTheoBadMarketVola, g_Params.UndPriceToleranceValue, _
            g_Params.PriceRoundingRule, m_dtCalcDateShift

    Debug.Assert Err.Number = 0
    
    If Err.Number = 0 Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogSystem, "CalcFutOptionGreeks Exit", "clsAuxRiskViewCalc"
    Else
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogFaults, "FAIL: CalcFutOptionGreeks Exit with error " & CStr(Err.Number) & " " & Err.Description, "clsAuxRiskViewCalc"
    End If
    
End Sub

Public Sub SyntheticUnderlyingCalc(ByRef aUnd As EtsMmRisksLib.MmRvUndAtom)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    Err.Clear
    aUnd.CalcSyntheticUnderlying m_Aux.Und, m_nGreeksMask, _
            (g_Params.PnLCalcType = PNLCT_LTD), g_Params.CalcModel, g_Params.UseTheoVolatility, _
            g_Params.UseTheoNoBid, g_Params.UseTheoBadMarketVola, g_Params.UndPriceToleranceValue, _
            g_Params.PriceRoundingRule, m_dtCalcDateShift
    Debug.Assert Err.Number = 0
End Sub

Public Sub InitVola(ByRef aUnd As EtsMmRisksLib.MmRvUndAtom)
    On Error Resume Next
    If Not aUnd.VolaSrv.IsInitialized Then
        Err.Clear
        aUnd.VolaSrv.Init aUnd.Symbol, IIf(aUnd.ContractType = enCtStock, enCtStock, enCtIndex), m_Aux.VolaSource
        If Err.Number <> 0 Then LogEvent EVENT_ERROR, "Fail to init volatility for '" & aUnd.Symbol & "': " & Err.Description
    End If
End Sub

'Public Function AddNewUnderlying(ByRef aTrd As EtsMmGeneralLib.MmTradeInfoAtom, _
'                                Optional ByRef aNewReqsAll As EtsMmRisksLib.MmRvReqColl = Nothing, _
'                                Optional ByRef aNewReqsNonGrp As EtsMmRisksLib.MmRvReqColl = Nothing) As EtsMmRisksLib.MmRvUndAtom
'    On Error GoTo EH
'    Set AddNewUnderlying = m_Aux.RiskView.AddNewUnderlying(aTrd, aNewReqsAll)
'
''    On Error Resume Next
''    Dim sKey$, aUnd As EtsMmRisksLib.MmRvUndAtom, aReq As EtsMmRisksLib.MmRvReqAtom
''
''    Debug.Assert m_Aux.Und(aTrd.UndID) Is Nothing
''
''    Set aUnd = m_Aux.Und.Add(aTrd.UndID, aTrd.Und.Symbol)
''    aUnd.ID = aTrd.Und.ID
''    aUnd.ContractType = aTrd.Und.UndType
''    aUnd.Symbol = aTrd.Und.Symbol
''
''    Set aUnd.Dividend = aTrd.Und.Dividend
''    If aUnd.ContractType <> enCtStock Then
''        Set aUnd.BasketIndex = g_Index(aUnd.ID)
''        If Not aUnd.BasketIndex Is Nothing Then
''            If Not aUnd.BasketIndex.IsBasket Then Set aUnd.BasketIndex = Nothing
''        End If
''        aUnd.Yield = aTrd.Und.Yield
''    End If
''
''    aUnd.IsAmerican = aTrd.Und.IsAmerican
''    aUnd.IsHTB = aTrd.Und.IsHTB
''    aUnd.ExpCalendarID = aTrd.Und.ExpCalendarID
''    aUnd.Skew = aTrd.Und.Skew
''    aUnd.Kurt = aTrd.Und.Kurt
''    aUnd.HasSynthetic = aTrd.Und.HaveSyntheticRoots
''    Set aUnd.SynthRoots = aTrd.Und.SyntheticRoots
''    Set aUnd.UndPriceProfile = aTrd.Und.UndPriceProfile
''    Set aUnd.OptPriceProfile = aTrd.Und.OptPriceProfile
''
''    aUnd.PriceClose = aTrd.Und.PriceClose
''    aUnd.LotSize = aTrd.Und.LotSize
''
''    aUnd.Qty = BAD_LONG_VALUE
''    aUnd.OptQty = BAD_LONG_VALUE
''    aUnd.FutQty = BAD_LONG_VALUE
''    aUnd.UndPosForRates = 0
''
''    ' InitVola aUnd
''
''    sKey = CStr(aUnd.ContractType) & "_" & aUnd.Symbol
''    Set aReq = QuoteReqsAll(sKey)
''    If aReq Is Nothing Then
''        Set aReq = QuoteReqsAll.Add(sKey)
''        Set aReq.Und = aUnd
''
''        QuoteReqsNonGrp.Add sKey, aReq
''
''        If Not aNewReqsAll Is Nothing Then aNewReqsAll.Add sKey, aReq
''        If Not aNewReqsNonGrp Is Nothing Then aNewReqsNonGrp.Add sKey, aReq
''    Else
''        aReq.IndexOnly = False
''    End If
''    Set aReq = Nothing
''
''    UndCount = UndCount + 1
''
''    Set AddNewUnderlying = aUnd
'
'    Exit Function
'EH:
'    If Not g_PerformanceLog Is Nothing Then _
'        g_PerformanceLog.LogMmInfo enLogFaults, "AddNewUnderlying exits with error " & CStr(Err.Number) & " " & Err.Description, "clsAuxRiskViewCalc"
'
'End Function

'Public Function AddNewPosition(ByRef aTrd As EtsMmGeneralLib.MmTradeInfoAtom, _
'                            ByRef aUnd As EtsMmRisksLib.MmRvUndAtom, _
'                            Optional ByRef aNewReqsAll As EtsMmRisksLib.MmRvReqColl = Nothing, _
'                            Optional ByRef aNewReqsNonGrp As EtsMmRisksLib.MmRvReqColl = Nothing, _
'                            Optional ByRef aNewReqsGrp As EtsMmRisksLib.MmRvReqColl = Nothing) As EtsMmRisksLib.MmRvPosAtom
''    On Error Resume Next
'    On Error GoTo EH
'    Set AddNewPosition = m_Aux.RiskView.AddNewPosition(aTrd, aUnd, aNewReqsAll, -1)
''    On Error Resume Next
''    Dim sKey$, aPos As EtsMmRisksLib.MmRvPosAtom, aReq As EtsMmRisksLib.MmRvReqAtom, sExpiryKey$
''    Dim aExp As EtsGeneralLib.EtsMmEntityAtom, aFutReq As EtsMmRisksLib.MmRvReqAtom
''
''    Debug.Assert Not aUnd Is Nothing And aUnd.Pos(aTrd.ContractID) Is Nothing
''
''    Set aPos = aUnd.Pos.Add(aTrd.ContractID, aTrd.Symbol)
''    aPos.ID = aTrd.ContractID
''    aPos.ContractType = aTrd.ContractType
''    aPos.Symbol = aTrd.Symbol
''
''    sKey = CStr(aPos.ContractType) & "_" & aPos.Symbol
''    Set aReq = QuoteReqsAll(sKey)
''    If aReq Is Nothing Then
''        Set aReq = QuoteReqsAll.Add(sKey)
''        Set aReq.Und = aUnd
''        Set aReq.Pos = aPos
''
''        If Not aNewReqsAll Is Nothing Then aNewReqsAll.Add sKey, aReq
''    Else
''        If aReq.Pos Is Nothing Then Set aReq.Pos = aPos
''    End If
''
''    If aPos.ContractType = enCtOption Then
''        If QuoteReqsGrp(sKey) Is Nothing Then
''            QuoteReqsGrp.Add sKey, aReq
''            If Not aNewReqsGrp Is Nothing Then aNewReqsGrp.Add sKey, aReq
''        End If
''    Else
''        If QuoteReqsNonGrp(sKey) Is Nothing Then
''            QuoteReqsNonGrp.Add sKey, aReq
''            If Not aNewReqsNonGrp Is Nothing Then aNewReqsNonGrp.Add sKey, aReq
''        End If
''    End If
''
''    aPos.LotSize = aTrd.LotSize
''
''    Select Case aPos.ContractType
''        Case enCtOption
''            InitVola aUnd
''
''            aPos.PriceClose = aTrd.Opt.PriceClose
''            aPos.OptType = aTrd.Opt.OptType
''            aPos.Expiry = aTrd.Opt.Expiry
''            aPos.ExpiryMonth = DateSerial(Year(aPos.Expiry), Month(aPos.Expiry), 1)
''            aPos.Strike = aTrd.Opt.Strike
''            aPos.OptionRootID = aTrd.OptRoot.ID
''            aPos.UndID = aUnd.ID
''            aPos.ImportID = aTrd.Opt.ImportID
''
''            aPos.VegaWeight = g_ExpCalendar.GetVegaWeight(aUnd.ExpCalendarID, aPos.Expiry)
''
''            sExpiryKey = CStr(aPos.ExpiryMonth)
''            Set aExp = m_Aux.Exp(sExpiryKey)
''            If aExp Is Nothing Then
''                Set aExp = m_Aux.Exp.Add(sExpiryKey)
''                aExp.ID = aPos.ExpiryMonth
''                aExp.Name = Format$(aPos.Expiry, "MMM YY")
''                Set aExp = Nothing
''            End If
''
''            OptCount = OptCount + 1
''
''            If aUnd.HasSynthetic And Not aUnd.SynthRoots Is Nothing Then
''                InitPositionSynthetics aUnd, aPos, aNewReqsAll, aNewReqsNonGrp
''            End If
''
''        Case enCtFuture, enCtFutOption
''            InitVola aUnd
''            Dim aFut As EtsMmRisksLib.MmRvFutAtom
''
''            If aUnd.Fut Is Nothing Then Set aUnd.Fut = New EtsMmRisksLib.MmRvFutColl
''
''            Set aFut = aUnd.Fut(aTrd.FutID)
''            If aFut Is Nothing Then
''                Set aFut = aUnd.Fut.Add(aTrd.FutID, aTrd.Fut.Symbol)
''                aFut.ID = aTrd.FutID
''
''                aFut.Symbol = aTrd.Fut.Symbol
''                aFut.Maturity = aTrd.Fut.MaturityDate
''                Set aFut.UndPriceProfile = aTrd.Fut.UndPriceProfile
''                Set aFut.OptPriceProfile = aTrd.Fut.OptPriceProfile
''
''                aFut.FutRootID = aTrd.FutRootID
''                aFut.FutRootSymbol = aTrd.FutRoot.Symbol
''                aFut.ContractName = aTrd.Fut.ContractName
''
''                aFut.UndID = aUnd.ID
''
''                aFut.OptLotSize = aTrd.FutRoot.OptLotSize
''                aFut.FutLotSize = aTrd.FutRoot.FutLotSize
''                aFut.PriceClose = aTrd.Fut.PriceClose
''
''                aFut.IsAmerican = aTrd.Fut.IsAmerican
''                aFut.ExpCalendarID = aTrd.Fut.ExpCalendarID
''
''                FutCount = FutCount + 1
''
''                sKey = CStr(enCtFuture) & "_" & aFut.Symbol
''                Set aFutReq = QuoteReqsAll(sKey)
''                If aFutReq Is Nothing Then
''                    Set aFutReq = QuoteReqsAll.Add(sKey)
''                    Set aFutReq.Und = aUnd
''
''                    If Not aNewReqsAll Is Nothing Then aNewReqsAll.Add sKey, aFutReq
''
''                    If QuoteReqsNonGrp(sKey) Is Nothing Then
''                        QuoteReqsNonGrp.Add sKey, aFutReq
''                        If Not aNewReqsNonGrp Is Nothing Then aNewReqsNonGrp.Add sKey, aFutReq
''                    End If
''                End If
''
''                Set aFutReq.Fut = aFut
''
''                Set aFutReq = Nothing
''            Else
''                Set aReq.Fut = aFut
''            End If
''
''            Set aPos.Fut = aFut
''            aPos.UndID = aUnd.ID
''
''            If aPos.ContractType = enCtFutOption Then
''                InitVola aUnd
''
''                aPos.PriceClose = aTrd.FutOpt.PriceClose
''                aPos.OptType = aTrd.FutOpt.OptType
''                aPos.Expiry = aTrd.FutOpt.Expiry
''                aPos.ExpiryMonth = DateSerial(Year(aPos.Expiry), Month(aPos.Expiry), 1)
''                aPos.Strike = aTrd.FutOpt.Strike
''
''                aPos.VegaWeight = g_ExpCalendar.GetVegaWeight(aUnd.ExpCalendarID, aPos.Expiry)
''                aPos.ImportID = aTrd.FutOpt.ImportID
''
''                sExpiryKey = CStr(aPos.ExpiryMonth)
''                Set aExp = m_Aux.Exp(sExpiryKey)
''                If aExp Is Nothing Then
''                    Set aExp = m_Aux.Exp.Add(sExpiryKey)
''                    aExp.ID = aPos.ExpiryMonth
''                    aExp.Name = Format$(aPos.Expiry, "MMM YY")
''                    Set aExp = Nothing
''                End If
''
''                OptCount = OptCount + 1
''            Else
''                aPos.PriceClose = aTrd.Fut.PriceClose
''            End If
''
''            Set aFut = Nothing
''
''        Case Else ' stock/index
''            aPos.PriceClose = aUnd.PriceClose
''    End Select
''
''    Set aReq = Nothing
''
''    aPos.Qty = 0
''    aPos.QtyInShares = 0
''
''    aPos.QtyLTDBuy = BAD_LONG_VALUE
''    aPos.PosLTDBuy = BAD_DOUBLE_VALUE
''    aPos.QtyDailyPrevDateBuy = BAD_LONG_VALUE
''    aPos.PosDailyPrevDateBuy = BAD_DOUBLE_VALUE
''    aPos.QtyDailyTodayBuy = BAD_LONG_VALUE
''    aPos.PosDailyTodayBuy = BAD_DOUBLE_VALUE
''
''    aPos.QtyLTDSell = BAD_LONG_VALUE
''    aPos.PosLTDSell = BAD_DOUBLE_VALUE
''    aPos.QtyDailyPrevDateSell = BAD_LONG_VALUE
''    aPos.PosDailyPrevDateSell = BAD_DOUBLE_VALUE
''    aPos.QtyDailyTodaySell = BAD_LONG_VALUE
''    aPos.PosDailyTodaySell = BAD_DOUBLE_VALUE
''
''    Set AddNewPosition = aPos
'
'    Exit Function
'EH:
'    If Not g_PerformanceLog Is Nothing Then _
'        g_PerformanceLog.LogMmInfo enLogFaults, "AddNewPosition exits with error " & CStr(Err.Number) & " " & Err.Description, "clsAuxRiskViewCalc"
'
'End Function
Public Sub UnderlyingsAdjustRates(ByVal bForceRateUpdate As Boolean)
    On Error Resume Next
    Dim aUnd As EtsMmRisksLib.MmRvUndAtom
    For Each aUnd In m_Aux.Und
        UnderlyingAdjustRates aUnd, bForceRateUpdate
    Next
End Sub

Public Function UnderlyingAdjustRates(ByRef aUnd As EtsMmRisksLib.MmRvUndAtom, ByVal bForceRateUpdate As Boolean) As Boolean
    On Error Resume Next
    UnderlyingAdjustRates = False
    If aUnd Is Nothing Then Exit Function
    
    Dim aPos As EtsMmRisksLib.MmRvPosAtom, bUseMidRates As Boolean, cPosThreshold@, dPos#
    
    dPos = g_UnderlyingAll(aUnd.ID).UndPosForRates
    
    If GetIrRuleType = enRateBasedOnPosition Then
        cPosThreshold = Abs(GetPosThreshold)
        bUseMidRates = (cPosThreshold = 0 Or cPosThreshold <> 0 And Abs(dPos) <= cPosThreshold)
        If Not bForceRateUpdate And Not bUseMidRates Then _
            bForceRateUpdate = (Sgn(dPos) * Sgn(aUnd.UndPosForRates) < 0)
    Else
        bUseMidRates = True
    End If

    If bForceRateUpdate Or aUnd.UseMidRates <> bUseMidRates Then
        aUnd.UseMidRates = bUseMidRates
        aUnd.UndPosForRates = dPos
        
        For Each aPos In aUnd.Pos
            If aPos.ContractType = enCtOption Or aPos.ContractType = enCtFutOption Then
                If bUseMidRates Then
                    If Not aUnd.IsHTB Then
                        aPos.Rate = GetNeutralRate(Date, aPos.Expiry)
                    Else
                        aPos.Rate = GetNeutralHTBRate(Date, aPos.Expiry)
                    End If
                Else
                    If Not aUnd.IsHTB Then
                        aPos.Rate = IIf(dPos < 0, GetShortRate(Date, aPos.Expiry), GetLongRate(Date, aPos.Expiry))
                    Else
                        aPos.Rate = IIf(dPos < 0, GetHTBRate(Date, aPos.Expiry), GetLongRate(Date, aPos.Expiry))
                    End If
                End If

            End If
        Next
        
        UnderlyingAdjustRates = True
    End If
End Function

Public Sub ClearPosQty(ByRef aPos As EtsMmRisksLib.MmRvPosAtom)
    On Error Resume Next
    
    aPos.Qty = 0
    aPos.QtyInShares = 0
    
    aPos.QtyLTDBuy = BAD_LONG_VALUE
    aPos.PosLTDBuy = BAD_DOUBLE_VALUE
    aPos.QtyDailyPrevDateBuy = BAD_LONG_VALUE
    aPos.PosDailyPrevDateBuy = BAD_DOUBLE_VALUE
    aPos.QtyDailyTodayBuy = BAD_LONG_VALUE
    aPos.PosDailyTodayBuy = BAD_DOUBLE_VALUE
    
    aPos.QtyLTDSell = BAD_LONG_VALUE
    aPos.PosLTDSell = BAD_DOUBLE_VALUE
    aPos.QtyDailyPrevDateSell = BAD_LONG_VALUE
    aPos.PosDailyPrevDateSell = BAD_DOUBLE_VALUE
    aPos.QtyDailyTodaySell = BAD_LONG_VALUE
    aPos.PosDailyTodaySell = BAD_DOUBLE_VALUE
End Sub

