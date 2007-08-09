VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsAuxRiskView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private m_bShutDown As Boolean
Private m_RiskView As EtsMmRisksLib.MmRiskView

Private m_Idx As EtsMmRisksLib.MmRvUndAtom

Private m_Grp As EtsMmRisksLib.MmRvGrpAtom
Private m_Und As EtsMmRisksLib.MmRvUndColl
'Private m_Exp As New EtsGeneralLib.EtsMmEntityAtomColl

Public VolaSource As VolatilitySourcesLib.VolatilitySource
Public gePos As clsGridEx

Public gdFlt As clsGridDef
Public gdTot As clsGridDef
Public gdPos As clsGridDef

Public fgFlt As VSFlex7Ctl.VSFlexGrid
Public fgPos As VSFlex7Ctl.VSFlexGrid
Public fgTot As VSFlex7Ctl.VSFlexGrid

Private m_aFilter As EtsGeneralLib.EtsFilterData

Private m_GridLock(GT_RISKS_FILTER To GT_RISKS_POSITIONS) As New clsGridLock

Public RealTime As Boolean
Public RealTimeConnected As Boolean

Public SortColOrder As VSFlex7Ctl.SortSettings
Public SortColKey As Long

Private Sub Class_Initialize()
    On Error Resume Next
    
    Set m_RiskView = New EtsMmRisksLib.MmRiskView
    Set m_Idx = m_RiskView.Idx
    Set m_Grp = m_RiskView.Grp
    Set m_Und = m_RiskView.Und
    Set m_RiskView.EtsMain = g_Main
    Set m_aFilter = New EtsGeneralLib.EtsFilterData

    m_aFilter.Initialize RFC_SYMBOL, RFC_LAST_COLUMN
    
    m_bShutDown = False
End Sub

Public Sub Term()
    On Error Resume Next
    m_bShutDown = True
    Set gePos = Nothing
    Set m_Idx = Nothing
    Set m_Grp = Nothing
    Set m_Und = Nothing
    Set m_RiskView = Nothing
    Set m_aFilter = Nothing
End Sub

Public Property Get GridLock(nIdx&) As clsGridLock
    Set GridLock = m_GridLock(nIdx)
End Property
Public Property Get FilterData() As EtsGeneralLib.EtsFilterData
    Set FilterData = m_aFilter
End Property
Public Property Get Filter&(nIdx&)
    Filter = m_aFilter.Data(nIdx)
End Property

Public Property Let Filter(nIdx&, nFilter&)
    m_aFilter.Data(nIdx) = nFilter
End Property

Public Property Get RiskView() As EtsMmRisksLib.MmRiskView
    Set RiskView = m_RiskView
End Property

Public Sub KillRiskView()
    Set m_RiskView = Nothing
End Sub

Public Property Get Idx() As EtsMmRisksLib.MmRvUndAtom
    Set Idx = m_Idx
End Property

Public Property Let Idx(aIdx As EtsMmRisksLib.MmRvUndAtom)
    Set m_Idx = aIdx
End Property

Public Property Get Grp() As EtsMmRisksLib.MmRvGrpAtom
    Set Grp = m_Grp
End Property

Public Property Let Grp(aGrp As EtsMmRisksLib.MmRvGrpAtom)
    Set m_Grp = aGrp
End Property

Public Property Get Und() As EtsMmRisksLib.MmRvUndColl
    Set Und = m_Und
End Property

Public Property Let Und(aUnd As EtsMmRisksLib.MmRvUndColl)
    Set m_Und = aUnd
End Property

Public Property Get Exp() As EtsGeneralLib.EtsMmEntityAtomColl
    Set Exp = m_RiskView.Exp
End Property

'Public Sub MakeDataSnapshot(ByVal sFileName$, ByRef frmOwner As Form)
'    On Error GoTo EH
'    Dim aLog As New clsLogMgr, sDesc$
'
'    Screen.MousePointer = vbHourglass
'
'    aLog.Init sFileName, "Risk View Data Snapshot"
'    g_Params.MakeAllParamsDescription sDesc
'    aLog.LogInfo sDesc
'
'    sDesc = frmOwner.GetCaption() & vbCrLf & String$(70, "-") & vbCrLf
'    aLog.LogInfo sDesc
'
'    If m_Grp.ID <> 0 And m_Grp.GroupType <> 0 Then
'        AppendFilterData aLog
'        AppendTotalsData aLog
'        AppendPositionsData aLog
'    Else
'        sDesc = "Filter: <No Filter Selected>" & vbCrLf
'        aLog.LogInfo sDesc
'    End If
'
'    Screen.MousePointer = vbDefault
'
'    gCmn.MyMsgBox frmOwner, "Data snapshot was saved to a file" & vbCrLf & _
'                     App.Path & "\Logs\" & sFileName, vbInformation
'
'    'SendMailToSupport "ETS Data snapshot", "", App.Path & "\Logs\" & sFileName
'    Exit Sub
'EH:
'    Dim sErrDesc$
'    sErrDesc = Err.Description
'    On Error Resume Next
'    Screen.MousePointer = vbDefault
'    gCmn.MyMsgBox frmOwner, "Fail to save data snapshot to a file" & vbCrLf & _
'                    App.Path & "\Logs\" & sFileName & vbCrLf & _
'                    sErrDesc, vbCritical
'End Sub
'
'Private Sub AppendFilterData(ByRef aLog As clsLogMgr)
'    On Error Resume Next
'    Dim sDesc$, nIdx&
'    sDesc = "Filters Data" & vbCrLf
'
'    For nIdx = RFC_GROUP To RFC_LAST_COLUMN
'        sDesc = sDesc & gdFlt.Col(nIdx).Caption & vbTab
'    Next
'    sDesc = sDesc & vbCrLf
'    For nIdx = RFC_GROUP To RFC_LAST_COLUMN
'        sDesc = sDesc & fgFlt.Cell(flexcpTextDisplay, 1, nIdx) & vbTab
'    Next
'    sDesc = sDesc & vbCrLf
'    aLog.LogInfo sDesc
'
'    If m_Idx.ID <> 0 Then
'        sDesc = "Index Prices" & vbTab & "Bid" & vbTab & "Ask" & vbTab & "Last" & vbCrLf & vbTab
'        sDesc = sDesc & IIf(m_Idx.PriceBid > BAD_DOUBLE_VALUE, m_Idx.PriceBid, STR_NA) & vbTab & _
'                        IIf(m_Idx.PriceAsk > BAD_DOUBLE_VALUE, m_Idx.PriceAsk, STR_NA) & vbTab & _
'                        IIf(m_Idx.PriceLast > BAD_DOUBLE_VALUE, m_Idx.PriceLast, STR_NA) & vbTab & _
'        sDesc = sDesc & vbCrLf
'    End If
'
'    sDesc = sDesc & vbCrLf
'    aLog.LogInfo sDesc
'End Sub
'
'Private Sub AppendTotalsData(ByRef aLog As clsLogMgr)
'    On Error Resume Next
'    Dim sDesc$, nIdx&
'    sDesc = "Totals Data" & vbCrLf
'
'    For nIdx = RTC_PNL_MTM To RTC_LAST_COLUMN
'        sDesc = sDesc & gdTot.Col(nIdx).Caption & vbTab
'    Next
'    sDesc = sDesc & vbCrLf
'
'    sDesc = sDesc & IIf(m_Grp.BadPnlMtm, "!", "") & IIf(m_Grp.PnlMtm > BAD_DOUBLE_VALUE, m_Grp.PnlMtm, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadPnlTheo, "!", "") & IIf(m_Grp.PnlTheo > BAD_DOUBLE_VALUE, m_Grp.PnlTheo, STR_NA) & vbTab
'    If m_Grp.PnlTheo > BAD_DOUBLE_VALUE And m_Grp.PnlMtm > BAD_DOUBLE_VALUE Then
'        sDesc = sDesc & IIf(m_Grp.BadPnlMtm Or m_Grp.BadPnlTheo, "!", "") & m_Grp.PnlTheo - m_Grp.PnlMtm & vbTab
'    Else
'        sDesc = sDesc & IIf(m_Grp.BadPnlMtm Or m_Grp.BadPnlTheo, "!", "") & STR_NA & vbTab
'    End If
'    sDesc = sDesc & IIf(m_Grp.BadVega, "!", "") & IIf(m_Grp.Vega > BAD_DOUBLE_VALUE, m_Grp.Vega, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadWtdVega, "!", "") & IIf(m_Grp.WtdVega > BAD_DOUBLE_VALUE, m_Grp.WtdVega, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadTheta, "!", "") & IIf(m_Grp.Theta > BAD_DOUBLE_VALUE, m_Grp.Theta, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadDeltaEq, "!", "") & IIf(m_Grp.DeltaEq > BAD_DOUBLE_VALUE, m_Grp.DeltaEq, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadGammaEq, "!", "") & IIf(m_Grp.GammaEq > BAD_DOUBLE_VALUE, m_Grp.GammaEq, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadRho, "!", "") & IIf(m_Grp.Rho > BAD_DOUBLE_VALUE, m_Grp.Rho, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadIdxDeltaEq, "!", "") & IIf(m_Grp.IdxDeltaEq > BAD_DOUBLE_VALUE, m_Grp.IdxDeltaEq, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadBetaWtdDelta, "!", "") & IIf(m_Grp.BetaWtdDelta > BAD_DOUBLE_VALUE, m_Grp.BetaWtdDelta, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadOptDelta, "!", "") & IIf(m_Grp.OptDelta > BAD_DOUBLE_VALUE, m_Grp.OptDelta, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadNetDelta, "!", "") & IIf(m_Grp.NetDelta > BAD_DOUBLE_VALUE, m_Grp.NetDelta, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadNetGamma, "!", "") & IIf(m_Grp.NetGamma > BAD_DOUBLE_VALUE, m_Grp.NetGamma, STR_NA) & vbTab
'    sDesc = sDesc & IIf(m_Grp.BadBetaWtdDeltaEq, "!", "") & IIf(m_Grp.BetaWtdDeltaEq > BAD_DOUBLE_VALUE, m_Grp.BetaWtdDeltaEq, STR_NA) & vbTab
'    sDesc = sDesc & vbCrLf
'
'    aLog.LogInfo sDesc
'End Sub
'
'Private Sub AppendPositionsData(ByRef aLog As clsLogMgr)
'    On Error Resume Next
'    Dim sDesc$, nIdx&, aUnd As EtsMmRisksLib.MmRvUndAtom, aPos As EtsMmRisksLib.MmRvPosAtom
'    Dim aSynthUnd As EtsMmRisksLib.MmRvUndAtom, aSynthGreek As EtsMmRisksLib.MmRvSynthGreeksAtom
'    sDesc = "Positions Data" & vbCrLf
'
'    sDesc = sDesc & "Row" & vbTab
'    For nIdx = RPC_SYMBOL To RPC_LAST_COLUMN
'        sDesc = sDesc & gdPos.Col(nIdx).Caption & vbTab
'    Next
'    sDesc = sDesc & vbCrLf
'    aLog.LogInfo sDesc
'
'    For Each aUnd In m_Und
'        sDesc = "Und" & vbTab & aUnd.Symbol & vbTab
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & IIf(aUnd.ReplacePriceStatus And enRpsBid, "!", "") & _
'                        IIf(aUnd.PriceBid > BAD_DOUBLE_VALUE, aUnd.PriceBid, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.ReplacePriceStatus And enRpsAsk, "!", "") & _
'                        IIf(aUnd.PriceAsk > BAD_DOUBLE_VALUE, aUnd.PriceAsk, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.PriceLast > BAD_DOUBLE_VALUE, aUnd.PriceLast, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.Qty > BAD_LONG_VALUE, aUnd.Qty, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.OptQty > BAD_LONG_VALUE, aUnd.OptQty, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadPnlMtm, "!", "") & IIf(aUnd.PnlMtm > BAD_DOUBLE_VALUE, aUnd.PnlMtm, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadPnlTheo, "!", "") & IIf(aUnd.PnlTheo > BAD_DOUBLE_VALUE, aUnd.PnlTheo, STR_NA) & vbTab
'        If aUnd.PnlTheo > BAD_DOUBLE_VALUE And aUnd.PnlMtm > BAD_DOUBLE_VALUE Then
'            sDesc = sDesc & IIf(aUnd.BadPnlMtm Or aUnd.BadPnlTheo, "!", "") & aUnd.PnlTheo - aUnd.PnlMtm & vbTab
'        Else
'            sDesc = sDesc & IIf(aUnd.BadPnlMtm Or aUnd.BadPnlTheo, "!", "") & STR_NA & vbTab
'        End If
'        sDesc = sDesc & IIf(aUnd.BadNetDelta, "!", "") & IIf(aUnd.NetDelta > BAD_DOUBLE_VALUE, aUnd.NetDelta, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadOptDelta, "!", "") & IIf(aUnd.OptDelta > BAD_DOUBLE_VALUE, aUnd.OptDelta, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadGammaPerc, "!", "") & IIf(aUnd.GammaPerc > BAD_DOUBLE_VALUE, aUnd.GammaPerc, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadGamma, "!", "") & IIf(aUnd.Gamma > BAD_DOUBLE_VALUE, aUnd.Gamma, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadVega, "!", "") & IIf(aUnd.Vega > BAD_DOUBLE_VALUE, aUnd.Vega, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadWtdVega, "!", "") & IIf(aUnd.WtdVega > BAD_DOUBLE_VALUE, aUnd.WtdVega, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadTheta, "!", "") & IIf(aUnd.Theta > BAD_DOUBLE_VALUE, aUnd.Theta, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadRho, "!", "") & IIf(aUnd.Rho > BAD_DOUBLE_VALUE, aUnd.Rho, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadVegaDelta, "!", "") & IIf(aUnd.VegaDelta > BAD_DOUBLE_VALUE, aUnd.VegaDelta, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadVegaGamma, "!", "") & IIf(aUnd.VegaGamma > BAD_DOUBLE_VALUE, aUnd.VegaGamma, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadThetaDelta, "!", "") & IIf(aUnd.ThetaDelta > BAD_DOUBLE_VALUE, aUnd.ThetaDelta, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadThetaGamma, "!", "") & IIf(aUnd.ThetaGamma > BAD_DOUBLE_VALUE, aUnd.ThetaGamma, STR_NA) & vbTab
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & IIf(aUnd.BadTimeValue, "!", "") & IIf(aUnd.TimeValue > BAD_DOUBLE_VALUE, aUnd.TimeValue, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadDeltaEq, "!", "") & IIf(aUnd.DeltaEq > BAD_DOUBLE_VALUE, aUnd.DeltaEq, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.BadBetaWtdDeltaEq, "!", "") & IIf(aUnd.BetaWtdDeltaEq > BAD_DOUBLE_VALUE, aUnd.BetaWtdDeltaEq, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aUnd.PriceClose > BAD_DOUBLE_VALUE, aUnd.PriceClose, STR_NA) & vbTab
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & IIf(aUnd.FutQty > BAD_LONG_VALUE, aUnd.OptQty, STR_NA) & vbCrLf
'        aLog.LogInfo sDesc
'
'        If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
'            For Each aSynthGreek In aUnd.SynthGreeks
'                sDesc = "SynthUnd" & vbTab & aSynthGreek.Symbol & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                Set aSynthUnd = m_Und(aSynthGreek.SynthUndID)
'                If Not aSynthUnd Is Nothing Then
'                    sDesc = sDesc & IIf(aSynthUnd.ReplacePriceStatus And enRpsBid, "!", "") & _
'                                    IIf(aSynthUnd.PriceBid > BAD_DOUBLE_VALUE, aSynthUnd.PriceBid, STR_NA) & vbTab
'                    sDesc = sDesc & IIf(aSynthUnd.ReplacePriceStatus And enRpsAsk, "!", "") & _
'                                    IIf(aSynthUnd.PriceAsk > BAD_DOUBLE_VALUE, aSynthUnd.PriceAsk, STR_NA) & vbTab
'                    sDesc = sDesc & IIf(aSynthUnd.PriceLast > BAD_DOUBLE_VALUE, aSynthUnd.PriceLast, STR_NA) & vbTab
'                Else
'                    sDesc = sDesc & vbTab
'                    sDesc = sDesc & vbTab
'                    sDesc = sDesc & vbTab
'                End If
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & IIf(aSynthGreek.BadDelta, "!", "") & _
'                                IIf(aSynthGreek.DeltaInShares > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInShares, STR_NA) & vbTab
'                sDesc = sDesc & IIf(aSynthGreek.BadDelta, "!", "") & _
'                                IIf(aSynthGreek.DeltaInShares > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInShares, STR_NA) & vbTab
'                sDesc = sDesc & IIf(aSynthGreek.BadGammaPerc, "!", "") & _
'                                IIf(aSynthGreek.GammaInSharesPerc > BAD_DOUBLE_VALUE, aSynthGreek.GammaInSharesPerc, STR_NA) & vbTab
'                sDesc = sDesc & IIf(aSynthGreek.BadGamma, "!", "") & _
'                                IIf(aSynthGreek.GammaInShares > BAD_DOUBLE_VALUE, aSynthGreek.GammaInShares, STR_NA) & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & IIf(aSynthGreek.BadDeltaInMoney, "!", "") & _
'                                IIf(aSynthGreek.DeltaInMoney > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInMoney, STR_NA) & vbTab
'                sDesc = sDesc & IIf(aSynthGreek.BadBetaWtdDeltaInMoney, "!", "") & _
'                                IIf(aSynthGreek.BetaWtdDeltaInMoney > BAD_DOUBLE_VALUE, aSynthGreek.BetaWtdDeltaInMoney, STR_NA) & vbTab
'                If Not aSynthUnd Is Nothing Then
'                    sDesc = sDesc & IIf(aSynthUnd.PriceClose > BAD_DOUBLE_VALUE, aSynthUnd.PriceClose, STR_NA) & vbTab
'                Else
'                    sDesc = sDesc & vbTab
'                End If
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbCrLf
'                Set aSynthUnd = Nothing
'                aLog.LogInfo sDesc
'            Next
'        End If
'
'        For Each aPos In aUnd.Pos
'            AppendPositionData aUnd, aPos, aLog
'        Next
'    Next
'End Sub
'
'Private Sub AppendPositionData(ByRef aUnd As EtsMmRisksLib.MmRvUndAtom, ByRef aPos As EtsMmRisksLib.MmRvPosAtom, ByRef aLog As clsLogMgr)
'    On Error Resume Next
'    Dim sDesc$, aSynthGreek As EtsMmRisksLib.MmRvSynthGreeksAtom
'    sDesc = "Pos" & vbTab & aPos.Symbol & vbTab
'
'    If aPos.ContractType = enCtOption Or aPos.ContractType = enCtFutOption Then
'        sDesc = sDesc & IIf(aPos.OptType = enOtCall, "C", "P") & vbTab
'        sDesc = sDesc & aPos.Expiry & vbTab
'        sDesc = sDesc & aPos.Strike & vbTab
'    Else
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & vbTab
'    End If
'
'    sDesc = sDesc & IIf(aPos.PriceBid > BAD_DOUBLE_VALUE, aPos.PriceBid, STR_NA) & vbTab
'    sDesc = sDesc & IIf(aPos.PriceAsk > BAD_DOUBLE_VALUE, aPos.PriceAsk, STR_NA) & vbTab
'    sDesc = sDesc & IIf(aPos.PriceLast > BAD_DOUBLE_VALUE, aPos.PriceLast, STR_NA) & vbTab
'
'    If aPos.ContractType = enCtOption Or aPos.ContractType = enCtFutOption Then
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & IIf(aPos.Qty > BAD_LONG_VALUE, aPos.Qty, STR_NA) & vbTab
'
'    ElseIf aPos.ContractType = enCtIndex Or aPos.ContractType = enCtStock Then
'        sDesc = sDesc & IIf(aPos.QtyInShares > BAD_LONG_VALUE, aPos.QtyInShares, STR_NA) & vbTab
'        sDesc = sDesc & vbTab
'    Else
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & vbTab
'    End If
'
'    sDesc = sDesc & IIf(aPos.PnlMtm > BAD_DOUBLE_VALUE, aPos.PnlMtm, STR_NA) & vbTab
'    sDesc = sDesc & IIf(aPos.PnlTheo > BAD_DOUBLE_VALUE, aPos.PnlTheo, STR_NA) & vbTab
'
'    If aPos.PnlTheo > BAD_DOUBLE_VALUE And aPos.PnlMtm > BAD_DOUBLE_VALUE Then
'        sDesc = sDesc & aPos.PnlTheo - aPos.PnlMtm & vbTab
'    Else
'        sDesc = sDesc & STR_NA & vbTab
'    End If
'
'    sDesc = sDesc & vbTab
'
'    If aPos.ContractType = enCtOption Or aPos.ContractType = enCtFutOption Then
'        sDesc = sDesc & IIf(aPos.DeltaInShares > BAD_DOUBLE_VALUE, aPos.DeltaInShares, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aPos.GammaInSharesPerc > BAD_DOUBLE_VALUE, aPos.GammaInSharesPerc, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aPos.GammaInShares > BAD_DOUBLE_VALUE, aPos.GammaInShares, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aPos.VegaInShares > BAD_DOUBLE_VALUE, aPos.VegaInShares, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aPos.WtdVega > BAD_DOUBLE_VALUE, aPos.WtdVega, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aPos.ThetaInShares > BAD_DOUBLE_VALUE, aPos.ThetaInShares, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aPos.RhoInShares > BAD_DOUBLE_VALUE, aPos.RhoInShares, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aPos.ThetaDeltaInShares > BAD_DOUBLE_VALUE, aPos.ThetaDeltaInShares, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aPos.ThetaGammaInShares > BAD_DOUBLE_VALUE, aPos.ThetaGammaInShares, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aPos.VegaDeltaInShares > BAD_DOUBLE_VALUE, aPos.VegaDeltaInShares, STR_NA) & vbTab
'        sDesc = sDesc & IIf(aPos.VegaGammaInShares > BAD_DOUBLE_VALUE, aPos.VegaGammaInShares, STR_NA) & vbTab
'    Else
'        sDesc = sDesc & String$(11, vbTab)
'    End If
'
'    sDesc = sDesc & aUnd.Symbol & vbTab
'
'    If aPos.ContractType = enCtOption Then
'        If Not aPos.IsSynthetic Then
'            sDesc = sDesc & aPos.LotSize & vbTab
'        Else
'            Dim aSynthRootComp As EtsGeneralLib.SynthRootCompAtom
'            Set aSynthRootComp = aUnd.SynthRoots(aPos.OptionRootID).SynthRootComponents(aUnd.ID)
'
'            If Not aSynthRootComp Is Nothing Then
'                sDesc = sDesc & aSynthRootComp.Weight * aPos.LotSize & vbTab
'            Else
'                sDesc = sDesc & STR_NA & vbTab
'            End If
'        End If
'
'        sDesc = sDesc & IIf(aPos.TimeValue > BAD_DOUBLE_VALUE, aPos.TimeValue, STR_NA) & vbTab
'    Else
'        sDesc = sDesc & aUnd.LotSize & vbTab
'        sDesc = sDesc & vbTab
'    End If
'
'    sDesc = sDesc & vbTab
'    sDesc = sDesc & vbTab
'
'    sDesc = sDesc & IIf(aPos.PriceClose > BAD_DOUBLE_VALUE, aPos.PriceClose, STR_NA) & vbTab
'
'    If aPos.ContractType = enCtFuture Or aPos.ContractType = enCtFutOption Then
'        sDesc = sDesc & aPos.Fut.FutRootSymbol & vbTab
'        sDesc = sDesc & aPos.Fut.Symbol & vbTab
'        sDesc = sDesc & aPos.Fut.Maturity & vbTab
'    Else
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & vbTab
'        sDesc = sDesc & vbTab
'    End If
'
'    If aPos.ContractType = enCtFuture Then
'        sDesc = sDesc & IIf(aPos.Qty > BAD_LONG_VALUE, aPos.Qty, STR_NA) & vbCrLf
'    Else
'        sDesc = sDesc & vbCrLf
'    End If
'    aLog.LogInfo sDesc
'
'    If aPos.IsSynthetic And Not aPos.SynthGreeks Is Nothing Then
'        For Each aSynthGreek In aPos.SynthGreeks
'            sDesc = "SynthPos" & vbTab & aSynthGreek.Symbol & vbTab
'            If aPos.ContractType = enCtOption Then
'                sDesc = sDesc & IIf(aPos.OptType = enOtCall, "C", "P") & vbTab
'                sDesc = sDesc & aPos.Expiry & vbTab
'                sDesc = sDesc & aPos.Strike & vbTab
'            Else
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'            End If
'
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'
'            If aPos.ContractType = enCtOption Then
'                sDesc = sDesc & vbTab
'            Else
'                sDesc = sDesc & IIf(aSynthGreek.DeltaInShares > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInShares, STR_NA) & vbTab
'            End If
'
'            sDesc = sDesc & IIf(aSynthGreek.DeltaInShares > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInShares, STR_NA) & vbTab
'            sDesc = sDesc & IIf(aSynthGreek.DeltaInShares > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInShares, STR_NA) & vbTab
'            sDesc = sDesc & IIf(aSynthGreek.GammaInSharesPerc > BAD_DOUBLE_VALUE, aSynthGreek.GammaInSharesPerc, STR_NA) & vbTab
'            sDesc = sDesc & IIf(aSynthGreek.GammaInShares > BAD_DOUBLE_VALUE, aSynthGreek.GammaInShares, STR_NA) & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            If aPos.ContractType = enCtOption Then
'                sDesc = sDesc & aSynthGreek.SynthUndSymbol & vbTab
'                sDesc = sDesc & aSynthGreek.DeliveryUnits & vbTab
'            Else
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'            End If
'            sDesc = sDesc & vbTab
'            If aPos.ContractType = enCtOption Then
'                sDesc = sDesc & vbTab
'                sDesc = sDesc & vbTab
'            Else
'                sDesc = sDesc & IIf(aSynthGreek.DeltaInMoney > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInMoney, STR_NA) & vbTab
'                sDesc = sDesc & IIf(aSynthGreek.BetaWtdDeltaInMoney > BAD_DOUBLE_VALUE, aSynthGreek.BetaWtdDeltaInMoney, STR_NA) & vbTab
'            End If
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbTab
'            sDesc = sDesc & vbCrLf
'            aLog.LogInfo sDesc
'        Next
'    End If
'End Sub

Public Sub PosGridCompare(ByVal Row1&, ByVal Row2&, ByRef Cmp%)
    On Error Resume Next
'    Dim aRowData1 As EtsMmRisksLib.MmRvRowData, aRowData2 As EtsMmRisksLib.MmRvRowData
'    Dim aUnd1 As EtsMmRisksLib.MmRvUndAtom, aUnd2 As EtsMmRisksLib.MmRvUndAtom
'    Dim aSynthUnd1 As EtsMmRisksLib.MmRvUndAtom, aSynthUnd2 As EtsMmRisksLib.MmRvUndAtom
'    Dim aPos1 As EtsMmRisksLib.MmRvPosAtom, aPos2 As EtsMmRisksLib.MmRvPosAtom
'    Dim aSynthGreeks1 As EtsMmRisksLib.MmRvSynthGreeksAtom, aSynthGreeks2 As EtsMmRisksLib.MmRvSynthGreeksAtom, i&
'    Dim dValue1#, dValue2#, nValue1&, nValue2&, sValue1$, sValue2$
'    Dim aSynthRoot As EtsGeneralLib.SynthRootAtom
'    Dim nIdx&
'
'    Cmp = 0
'
'    Set aRowData1 = fgPos.RowData(Row1)
'    Set aRowData2 = fgPos.RowData(Row2)
'
'    If Not aRowData1 Is Nothing And Not aRowData2 Is Nothing Then
'
'        Set aUnd1 = aRowData1.Und
'        Set aUnd2 = aRowData2.Und
'        Set aPos1 = aRowData1.Pos
'        Set aPos2 = aRowData2.Pos
'        Set aSynthGreeks1 = aRowData1.SynthGreeks
'        If Not aSynthGreeks1 Is Nothing Then Set aSynthUnd1 = m_Und(aSynthGreeks1.SynthUndID)
'        Set aSynthGreeks2 = aRowData2.SynthGreeks
'        If Not aSynthGreeks2 Is Nothing Then Set aSynthUnd2 = m_Und(aSynthGreeks2.SynthUndID)
'
'        If Not aUnd1 Is Nothing And Not aUnd2 Is Nothing Then
'
'            If aPos1 Is Nothing And Not aPos2 Is Nothing Then
'                Cmp = -1
'                GoTo EX
'            ElseIf Not aPos1 Is Nothing And aPos2 Is Nothing Then
'                Cmp = 1
'                GoTo EX
'            End If
'
'            If Not aPos1 Is Nothing And Not aPos2 Is Nothing Then
'                    If Not aPos1.IsSyntheticAggregation And aPos2.IsSyntheticAggregation Then
'                        Cmp = 1
'                        GoTo EX
'                    ElseIf Not aPos2.IsSyntheticAggregation And aPos1.IsSyntheticAggregation Then
'                        Cmp = -1
'                        GoTo EX
'                    End If
'            End If
'
'            Select Case SortColKey
'                Case RPC_SYMBOL
'                    If aUnd1.Symbol > aUnd2.Symbol Then
'                        Cmp = 1
'                    ElseIf aUnd1.Symbol < aUnd2.Symbol Then
'                        Cmp = -1
'                    Else
'                        If Not aPos1 Is Nothing And Not aPos2 Is Nothing Then
'                            If aPos1.Symbol > aPos2.Symbol Then
'                                Cmp = 1
'                            ElseIf aPos1.Symbol < aPos2.Symbol Then
'                                Cmp = -1
'                            Else
'                                If Not aSynthGreeks1 Is Nothing Then
'                                    sValue1 = aSynthUnd1.Symbol
'                                Else
'                                    sValue1 = ""
'                                End If
'
'                                If Not aSynthGreeks2 Is Nothing Then
'                                    sValue2 = aSynthUnd2.Symbol
'                                Else
'                                    sValue2 = ""
'                                End If
'
'                                If sValue1 > sValue2 Then
'                                    Cmp = 1
'                                ElseIf sValue1 < sValue2 Then
'                                    Cmp = -1
'                                End If
'
'                                If sValue1 = "" Xor sValue2 = "" Then
'                                    If SortColOrder <> flexSortGenericAscending Then Cmp = -Cmp
'                                End If
'                            End If
'                        ElseIf Not aSynthGreeks1 Is Nothing And Not aSynthGreeks2 Is Nothing Then
'                            If aSynthGreeks1.Symbol > aSynthGreeks2.Symbol Then
'                                Cmp = 1
'                            ElseIf aSynthGreeks1.Symbol < aSynthGreeks2.Symbol Then
'                                Cmp = -1
'                            End If
'                        Else
'                            If Not aSynthGreeks1 Is Nothing Then
'                                sValue1 = aSynthUnd1.Symbol
'                            Else
'                                sValue1 = ""
'                            End If
'
'                            If Not aSynthGreeks2 Is Nothing Then
'                                sValue2 = aSynthUnd1.Symbol
'                            Else
'                                sValue2 = ""
'                            End If
'
'                            If sValue1 > sValue2 Then
'                                Cmp = 1
'                            ElseIf sValue1 < sValue2 Then
'                                Cmp = -1
'                            End If
'
'                            If sValue1 = "" Xor sValue2 = "" Then
'                                If SortColOrder <> flexSortGenericAscending Then Cmp = -Cmp
'                            End If
'                        End If
'                    End If
'
'                Case RPC_OPT_TYPE
'                    If Not aPos1 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos1.OptType > aPos2.OptType Then
'                            Cmp = 1
'                        ElseIf aPos1.OptType < aPos2.OptType Then
'                            Cmp = -1
'                        End If
'                    End If
'
'                Case RPC_EXPIRY
'                    If Not aPos1 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos1.Expiry > aPos2.Expiry Then
'                            Cmp = 1
'                        ElseIf aPos1.Expiry < aPos2.Expiry Then
'                            Cmp = -1
'                        End If
'                    End If
'
'                Case RPC_STRIKE
'                    If Not aPos1 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos1.Strike > aPos2.Strike Then
'                            Cmp = 1
'                        ElseIf aPos1.Strike < aPos2.Strike Then
'                            Cmp = -1
'                        End If
'                    End If
'
'                Case RPC_BID
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'                    If Not aSynthGreeks1 Is Nothing Then
'                        If aSynthGreeks1.IsTotal Then dValue1 = aSynthUnd1.Price.Bid
'                    ElseIf Not aPos1 Is Nothing Then
'                        dValue1 = aPos1.Quote.Price.Bid
'                    Else
'                        dValue1 = aUnd1.Price.Bid
'                    End If
'
'                    If Not aSynthGreeks2 Is Nothing Then
'                        If aSynthGreeks2.IsTotal Then dValue2 = aSynthUnd2.Price.Bid
'                    ElseIf Not aPos2 Is Nothing Then
'                        dValue2 = aPos2.Quote.Price.Bid
'                    Else
'                        dValue2 = aUnd2.Price.Bid
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_ASK
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'                    If Not aSynthGreeks1 Is Nothing Then
'                        If aSynthGreeks1.IsTotal Then dValue1 = aSynthUnd1.Price.Ask
'                    ElseIf Not aPos1 Is Nothing Then
'                        dValue1 = aPos1.Quote.Price.Ask
'                    Else
'                        dValue1 = aUnd1.Price.Ask
'                    End If
'
'                    If Not aSynthGreeks2 Is Nothing Then
'                        If aSynthGreeks2.IsTotal Then dValue2 = aSynthUnd2.Price.Ask
'                    ElseIf Not aPos2 Is Nothing Then
'                        dValue2 = aPos2.Quote.Price.Ask
'                    Else
'                        dValue2 = aUnd2.Price.Ask
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_LAST
'                     dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'                    If Not aSynthGreeks1 Is Nothing Then
'                        If aSynthGreeks1.IsTotal Then dValue1 = aSynthUnd1.Price.Last
'                    ElseIf Not aPos1 Is Nothing Then
'                        dValue1 = aPos1.Quote.Price.Last
'                    Else
'                        dValue1 = aUnd1.Price.Last
'                    End If
'
'                    If Not aSynthGreeks2 Is Nothing Then
'                        If aSynthGreeks2.IsTotal Then dValue2 = aSynthUnd2.Price.Last
'                    ElseIf Not aPos2 Is Nothing Then
'                        dValue2 = aPos2.Quote.Price.Last
'                    Else
'                        dValue2 = aUnd2.Price.Last
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_CLOSE
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'                    If Not aSynthGreeks1 Is Nothing Then
'                        If aSynthGreeks1.IsTotal Then dValue1 = aSynthUnd1.Price.Close
'                    ElseIf Not aPos1 Is Nothing Then
'                        dValue1 = aPos1.Quote.Price.Close
'                    Else
'                        dValue1 = aUnd1.Price.Close
'                    End If
'
'                    If Not aSynthGreeks2 Is Nothing Then
'                        If aSynthGreeks2.IsTotal Then dValue2 = aSynthUnd2.Price.Close
'                    ElseIf Not aPos2 Is Nothing Then
'                        dValue2 = aPos2.Quote.Price.Close
'                    Else
'                        dValue2 = aUnd2.Price.Close
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_UND_POS
'                    nValue1 = BAD_LONG_VALUE
'                    nValue2 = BAD_LONG_VALUE
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtStock Or aPos1.ContractType = enCtIndex Then nValue1 = aPos1.QtyInShares
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtStock Or aPos2.ContractType = enCtIndex Then nValue2 = aPos2.QtyInShares
'                    End If
'
'                    If nValue1 > nValue2 Then
'                        Cmp = 1
'                    ElseIf nValue1 < nValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_OPT_QTY
'                    nValue1 = BAD_LONG_VALUE
'                    nValue2 = BAD_LONG_VALUE
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Then nValue1 = aPos1.Qty
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Then nValue2 = aPos2.Qty
'                    End If
'
'                    If nValue1 > nValue2 Then
'                        Cmp = 1
'                    ElseIf nValue1 < nValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_FUT_QTY
'                    nValue1 = BAD_LONG_VALUE
'                    nValue2 = BAD_LONG_VALUE
'                    If Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtFuture Then nValue1 = aPos1.Qty
'                    End If
'
'                    If Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtFuture Then nValue2 = aPos2.Qty
'                    End If
'
'                    If nValue1 > nValue2 Then
'                        Cmp = 1
'                    ElseIf nValue1 < nValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_PNL_MTM
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        dValue1 = aPos1.PnlMtm
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        dValue2 = aPos2.PnlMtm
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_PNL_THEO
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        dValue1 = aPos1.PnlTheo
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        dValue2 = aPos2.PnlTheo
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_PNL_EDGE
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.PnlTheo > BAD_DOUBLE_VALUE And aPos1.PnlMtm > BAD_DOUBLE_VALUE Then
'                            dValue1 = aPos1.PnlTheo - aPos1.PnlMtm
'                        End If
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.PnlTheo > BAD_DOUBLE_VALUE And aPos2.PnlMtm > BAD_DOUBLE_VALUE Then
'                            dValue2 = aPos2.PnlTheo - aPos2.PnlMtm
'                        End If
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_NET_DELTA
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And aPos1 Is Nothing Then
'                        dValue1 = aUnd1.NetDelta
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And aPos2 Is Nothing Then
'                        dValue2 = aUnd2.NetDelta
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_NET_DELTA_USD
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And aPos1 Is Nothing Then
'                        dValue1 = aUnd1.DeltaEq
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And aPos2 Is Nothing Then
'                        dValue2 = aUnd2.DeltaEq
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_OPT_DELTA
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If Not aSynthGreeks1 Is Nothing Then
'                        dValue1 = aSynthGreeks1.DeltaInShares
'                    ElseIf Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.DeltaInShares
'                    End If
'
'                    If Not aSynthGreeks2 Is Nothing Then
'                        dValue2 = aSynthGreeks2.DeltaInShares
'                    ElseIf Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.DeltaInShares
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_GAMMA
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If Not aSynthGreeks1 Is Nothing Then
'                        dValue1 = aSynthGreeks1.GammaInSharesPerc
'                    ElseIf Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.GammaInSharesPerc
'                    End If
'
'                    If Not aSynthGreeks2 Is Nothing Then
'                        dValue2 = aSynthGreeks2.GammaInSharesPerc
'                    ElseIf Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.GammaInSharesPerc
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'                Case RPC_GAMMAP
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.Quote.Gamma
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.Quote.Gamma
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'                Case RPC_DELTAP
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.Delta
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.Delta
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'                Case RPC_NET_GAMMA
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If Not aSynthGreeks1 Is Nothing Then
'                        dValue1 = aSynthGreeks1.NetGamma
'                    ElseIf Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.NetGamma
'                    End If
'
'                    If Not aSynthGreeks2 Is Nothing Then
'                        dValue2 = aSynthGreeks2.NetGamma
'                    ElseIf Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.NetGamma
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_GAMMA_SHARES
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If Not aSynthGreeks1 Is Nothing Then
'                        dValue1 = aSynthGreeks1.GammaInShares
'                    ElseIf Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.GammaInShares
'                    End If
'
'                    If Not aSynthGreeks2 Is Nothing Then
'                        dValue2 = aSynthGreeks2.GammaInShares
'                    ElseIf Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.GammaInShares
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_VEGA
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.VegaInShares
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.VegaInShares
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'                Case RPC_VEGAP
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.Vega
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.Vega
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_WTD_VEGA
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.WtdVega
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.WtdVega
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_THETA
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.ThetaInShares
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.ThetaInShares
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'                Case RPC_THETAP
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.Theta
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.Theta
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'                Case RPC_RHO
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.RhoInShares
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.RhoInShares
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'                Case RPC_RHOP
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.Rho
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.Rho
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'                Case RPC_VEGA_DELTA
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.VegaDeltaInShares
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.VegaDeltaInShares
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_VEGA_GAMMA
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.VegaGammaInShares
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.VegaGammaInShares
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_THETA_DELTA
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.ThetaDeltaInShares
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.ThetaDeltaInShares
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_THETA_GAMMA
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.ThetaGammaInShares
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.ThetaGammaInShares
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_UND
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        sValue1 = aUnd1.Symbol
'                    ElseIf Not aSynthGreeks1 Is Nothing Then
'                        If Not aSynthGreeks1.IsTotal Then sValue1 = aSynthGreeks1.SynthUndSymbol
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        sValue2 = aUnd2.Symbol
'                    ElseIf Not aSynthGreeks2 Is Nothing Then
'                        If Not aSynthGreeks2.IsTotal Then sValue2 = aSynthGreeks2.SynthUndSymbol
'                    End If
'
'                    If sValue1 > sValue2 Then
'                        Cmp = 1
'                    ElseIf sValue1 < sValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_DEL_UNIT
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'
'                        If Not aPos1.IsSynthetic Then
'                            dValue1 = aPos1.Quote.LotSize
'                        Else
'                            Set aSynthRoot = aUnd1.SynthRoots(aPos1.OptionRootID)
'                            If Not aSynthRoot Is Nothing Then _
'                                If Not aSynthRoot.SynthRootComponents(aUnd1.ID) Is Nothing Then _
'                                    dValue1 = aSynthRoot.SynthRootComponents(aUnd1.ID).Weight * aPos1.Quote.LotSize
'                            Set aSynthRoot = Nothing
'                        End If
'                    ElseIf Not aSynthGreeks1 Is Nothing Then
'                        If Not aSynthGreeks1.IsTotal Then
'                            Set aSynthRoot = aUnd1.SynthRoots(aPos1.OptionRootID)
'                            If Not aSynthRoot Is Nothing Then
'                                If Not aSynthRoot.SynthRootComponents(aSynthGreeks1.SynthUndID) Is Nothing Then
'                                    dValue1 = aSynthRoot.SynthRootComponents(aSynthGreeks1.SynthUndID).Weight * aPos1.Quote.LotSize
'                                ElseIf aSynthGreeks1.SynthUndID = USD_ID Then
'                                    dValue1 = aSynthRoot.CashValue * aPos1.Quote.LotSize
'                                End If
'                            End If
'                            Set aSynthRoot = Nothing
'                        End If
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'
'                        If Not aPos2.IsSynthetic Then
'                            dValue2 = aPos2.Quote.LotSize
'                        Else
'                            Set aSynthRoot = aUnd2.SynthRoots(aPos2.OptionRootID)
'                            If Not aSynthRoot Is Nothing Then _
'                                If Not aSynthRoot.SynthRootComponents(aUnd2.ID) Is Nothing Then _
'                                    dValue2 = aSynthRoot.SynthRootComponents(aUnd2.ID).Weight * aPos2.Quote.LotSize
'                            Set aSynthRoot = Nothing
'                        End If
'                    ElseIf Not aSynthGreeks2 Is Nothing Then
'                        If Not aSynthGreeks2.IsTotal Then
'                            Set aSynthRoot = aUnd2.SynthRoots(aPos2.OptionRootID)
'                            If Not aSynthRoot Is Nothing Then
'                                If Not aSynthRoot.SynthRootComponents(aSynthGreeks2.SynthUndID) Is Nothing Then
'                                    dValue2 = aSynthRoot.SynthRootComponents(aSynthGreeks2.SynthUndID).Weight * aPos2.Quote.LotSize
'                                ElseIf aSynthGreeks2.SynthUndID = USD_ID Then
'                                    dValue2 = aSynthRoot.CashValue * aPos2.Quote.LotSize
'                                End If
'                            End If
'                            Set aSynthRoot = Nothing
'                        End If
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_TIME_VALUE
'                    dValue1 = BAD_DOUBLE_VALUE
'                    dValue2 = BAD_DOUBLE_VALUE
'
'                    If aSynthGreeks1 Is Nothing And Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtOption Or aPos1.ContractType = enCtFutOption Then dValue1 = aPos1.TimeValue
'                    End If
'
'                    If aSynthGreeks2 Is Nothing And Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtOption Or aPos2.ContractType = enCtFutOption Then dValue2 = aPos2.TimeValue
'                    End If
'
'                    If dValue1 > dValue2 Then
'                        Cmp = 1
'                    ElseIf dValue1 < dValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_FUT_ROOT
'                    sValue1 = ""
'                    sValue2 = ""
'
'                    If Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtFuture Or aPos1.ContractType = enCtFutOption Then sValue1 = aPos1.Fut.FutRootSymbol
'                    End If
'
'                    If Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtFuture Or aPos2.ContractType = enCtFutOption Then sValue2 = aPos2.Fut.FutRootSymbol
'                    End If
'
'                    If sValue1 > sValue2 Then
'                        Cmp = 1
'                    ElseIf sValue1 < sValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_FUTURES
'                    sValue1 = ""
'                    sValue2 = ""
'
'                    If Not aPos1 Is Nothing Then
'                        If aPos1.ContractType = enCtFuture Or aPos1.ContractType = enCtFutOption Then sValue1 = aPos1.Fut.Symbol
'                    End If
'
'                    If Not aPos2 Is Nothing Then
'                        If aPos2.ContractType = enCtFuture Or aPos2.ContractType = enCtFutOption Then sValue2 = aPos2.Fut.Symbol
'                    End If
'
'                    If sValue1 > sValue2 Then
'                        Cmp = 1
'                    ElseIf sValue1 < sValue2 Then
'                        Cmp = -1
'                    End If
'
'                Case RPC_FUT_MATURITY
'                    If Not aPos1 Is Nothing And Not aPos2 Is Nothing Then
'                        If Not aPos1.Fut Is Nothing And Not aPos2.Fut Is Nothing Then
'                            If aPos1.Fut.Maturity > aPos2.Fut.Maturity Then
'                                Cmp = 1
'                            ElseIf aPos1.Fut.Maturity < aPos2.Fut.Maturity Then
'                                Cmp = -1
'                            End If
'                        End If
'                    End If
'
'            End Select
'        End If
'    End If
'
'    If SortColOrder <> flexSortGenericAscending Then
'        Cmp = -Cmp
'    End If
'
'EX:
'    Set aPos1 = Nothing
'    Set aPos2 = Nothing
'    Set aUnd1 = Nothing
'    Set aUnd2 = Nothing
'    Set aSynthGreeks1 = Nothing
'    Set aSynthGreeks2 = Nothing
'    Set aRowData1 = Nothing
'    Set aRowData2 = Nothing
'    Set aSynthUnd1 = Nothing
'    Set aSynthUnd2 = Nothing
End Sub

Public Sub InitFltData()
    On Error Resume Next
    
    With fgFlt
        m_GridLock(GT_RISKS_FILTER).LockRedraw
'
'        .ColComboList(RFC_GROUP) = "#" & CStr(TYPE_UNDERLYING) & ";Underlying" & _
'                                    "|#" & CStr(TYPE_GROUP) & ";Group" & _
'                                    "|#" & CStr(TYPE_TRADER_GROUP) & ";TraderGroup" & _
'                                    "|#" & CStr(TYPE_TRADER) & ";Trader" & _
'                                    "|#" & CStr(TYPE_STRATEGY) & ";Strategy" & _
'                                    "|#" & CStr(TYPE_ALL) & ";<All>"
'        .TextMatrix(1, RFC_GROUP) = CStr(TYPE_UNDERLYING)
'        Filter(RFC_GROUP) = TYPE_UNDERLYING
'
'        .ColComboList(RFC_VALUE) = "#0;<None>"
'        .TextMatrix(1, RFC_VALUE) = "0"
'        Filter(RFC_VALUE) = 0
'
'        .ColComboList(RFC_TYPE) = "#0;<All>|#1;Today's|#2;OpenPos|#3;NetPos|#7;Manual|#4;Simulated|#5;Today's & Sim|#6;OpenPos & Sim|#8;Manual & Sim"
'        .TextMatrix(1, RFC_TYPE) = "0"
'
'        .ColComboList(RFC_EXPIRY) = "#0;<All>"
'        .TextMatrix(1, RFC_EXPIRY) = "0"
'        Filter(RFC_EXPIRY) = 0
'
'        .ColComboList(RFC_INDEX) = "#0;<None>"
'        .TextMatrix(1, RFC_INDEX) = "0"
'        Filter(RFC_INDEX) = 0
'
        .ColComboList(RFC_TRADES) = "#0;<All>|#1;Today's|#2;OpenPos|#3;NetPos|#7;Manual|#4;Simulated|#5;Today's & Sim|#6;OpenPos & Sim|#8;Manual & Sim"
        .TextMatrix(1, RFC_TRADES) = "0"
    
        .ColComboList(RFC_EXPIRY) = "#0;<All>"
        .TextMatrix(1, RFC_EXPIRY) = "0"
        Filter(RFC_EXPIRY) = 0
    
        .ColComboList(RFC_INDEX) = "#0;<None>"
        .TextMatrix(1, RFC_INDEX) = "0"
        Filter(RFC_INDEX) = 0
        
'        .ColComboList(RFC_AGGREGATION) = "#0;<None>|#1;Group"
'        .TextMatrix(1, RFC_AGGREGATION) = "0"
'        Filter(RFC_AGGREGATION) = 0
        
'        .ColComboList(RFC_SUBAGGREGATION) = "#0;Underlying|#1;Strategy"
'        .TextMatrix(1, RFC_SUBAGGREGATION) = "0"
'        Filter(RFC_SUBAGGREGATION) = 0
    
        FilterUpdateValue True, RFC_SYMBOL
        FilterUpdateValue True, RFC_GROUPS
        FilterUpdateValue True, RFC_TRADER
        FilterUpdateValue True, RFC_TRADER_GROUP
        FilterUpdateValue True, RFC_STRATEGY

        m_GridLock(GT_RISKS_FILTER).UnlockRedraw
        m_GridLock(GT_RISKS_FILTER).UnlockRedraw
    End With
End Sub

Public Sub InitGrids()
    On Error Resume Next
    With fgFlt
        .Rows = 2
        .Cols = RFC_COLUMN_COUNT
        
        .AllowBigSelection = False
        .AllowSelection = False
        .AllowUserFreezing = flexFreezeNone
        .AllowUserResizing = flexResizeNone
        .AutoSizeMode = flexAutoSizeColWidth
        .Appearance = flex3DLight
        .AutoSearch = flexSearchNone
        .AutoSizeMouse = True
        .Editable = flexEDKbdMouse
        .Ellipsis = flexEllipsisEnd
        .ExplorerBar = flexExNone
        .ExtendLastCol = False
        .FixedCols = 0
        .FixedRows = 1
        .FocusRect = flexFocusSolid
        .FrozenCols = 0
        .FrozenRows = 0
        .OutlineBar = flexOutlineBarNone
        .ScrollBars = flexScrollBarNone
        .SelectionMode = flexSelectionFree
        .TabBehavior = flexTabControls
        
        .HighLight = flexHighlightWithFocus
    End With
    
    With fgTot
        .Rows = 2
        .Cols = 10
        
        .AllowBigSelection = False
        .AllowSelection = False
        .AllowUserFreezing = flexFreezeNone
        .AllowUserResizing = flexResizeNone
        .Appearance = flex3DLight
        .AutoSizeMode = flexAutoSizeColWidth
        .AutoSearch = flexSearchNone
        .AutoSizeMouse = True
        .Editable = flexEDNone
        .Ellipsis = flexEllipsisEnd
        .ExplorerBar = flexExMove
        .ExtendLastCol = False
        .FixedCols = 0
        .FixedRows = 1
        .FocusRect = flexFocusSolid
        .FrozenCols = 0
        .FrozenRows = 0
        .OutlineBar = flexOutlineBarNone
        .ScrollBars = flexScrollBarNone
        .ScrollTrack = True
        .SelectionMode = flexSelectionFree
        .TabBehavior = flexTabControls
        
        .HighLight = flexHighlightWithFocus
    End With

    With fgPos
        .Rows = 1
        .Cols = 10
        
        .AllowBigSelection = False
        .AllowSelection = False
        .AllowUserFreezing = flexFreezeNone
        .AllowUserResizing = flexResizeColumns
        .Appearance = flex3DLight
        .AutoSizeMode = flexAutoSizeColWidth
        .AutoSearch = flexSearchNone
        .AutoSizeMouse = True
        .Editable = flexEDKbdMouse
        .Ellipsis = flexEllipsisEnd
        .ExplorerBar = flexExSortAndMove
        .ExtendLastCol = False
        .FixedCols = 0
        .FixedRows = 1
        .FocusRect = flexFocusHeavy
        .FrozenCols = 0
        .FrozenRows = 0
        .OutlineBar = flexOutlineBarSymbolsLeaf
        .OutlineCol = 1
        .ScrollBars = flexScrollBarBoth
        .ScrollTrack = True
        .SelectionMode = flexSelectionByRow
        .TabBehavior = flexTabControls
    End With
End Sub

Public Sub FormatFltGrid()
    On Error Resume Next
    Dim i&
    
    With fgFlt
        m_GridLock(GT_RISKS_FILTER).LockRedraw
    
        .Cols = RFC_COLUMN_COUNT
        
        For i = RFC_SYMBOL To RFC_LAST_COLUMN
            .TextMatrix(0, i) = gdFlt.Col(i).Caption
            .ColFormat(i) = gdFlt.Col(i).Format
            .ColDataType(i) = gdFlt.Col(i).DataType
        Next
        
        .Cell(flexcpAlignment, 0, 0, 0, .Cols - 1) = flexAlignCenterCenter
        
        m_GridLock(GT_RISKS_FILTER).UnlockRedraw
    End With
End Sub

Public Sub FormatFltColumns()
    On Error Resume Next
    Dim i&, nCols&, nRows&, aFont As New StdFont
    
    With fgFlt
        m_GridLock(GT_RISKS_FILTER).LockRedraw
    
        aFont.Name = gdFlt.Font.Name
        aFont.Size = gdFlt.Font.Size
        aFont.Bold = gdFlt.Font.Bold
        aFont.Italic = gdFlt.Font.Italic
        aFont.Strikethrough = gdFlt.Font.Strikethrough
        aFont.Underline = gdFlt.Font.Underline
        
        Set .Font = aFont
    
        nCols = .Cols - 1
        nRows = .Rows - 1
        For i = RFC_SYMBOL To RFC_LAST_COLUMN
            .Cell(flexcpBackColor, 1, i, nRows, i) = IIf(gdFlt.Col(i).BackColor <> 0, gdFlt.Col(i).BackColor, RGB(1, 1, 1))
            .Cell(flexcpForeColor, 1, i, nRows, i) = IIf(gdFlt.Col(i).ForeColor <> 0, gdFlt.Col(i).ForeColor, RGB(1, 1, 1))
        Next
    
        If gdFlt.HorizLinesVisible Then
            If gdFlt.VertLinesVisible Then
                .GridLines = flexGridFlat
            Else
                .GridLines = flexGridFlatHorz
            End If
        ElseIf gdFlt.VertLinesVisible Then
            .GridLines = flexGridFlatVert
        Else
            .GridLines = flexGridNone
        End If
        .GridColor = gdFlt.GridLinesColor
        
        .BackColorSel = gdFlt.BackColorSel
        .ForeColorSel = gdFlt.ForeColorSel
        
        .AutoSize 0, .Cols - 1, , 100
        
        m_GridLock(GT_RISKS_FILTER).UnlockRedraw
    End With
End Sub

Public Sub FormatTotGrid()
    On Error Resume Next
    Dim i&, nCols&, nIdx&
    
    With fgTot
        m_GridLock(GT_RISKS_TOTALS).LockRedraw
    
        nCols = 0
        For i = 0 To RTC_LAST_COLUMN
            If gdTot.Idx(i) <> RTC_NONE Then
                nCols = nCols + 1
            Else
                Exit For
            End If
        Next
        
        If nCols = 0 Then
            gdTot.Idx(0) = RTC_PNL_MTM
            nCols = 1
        End If
        
        .Cols = nCols
        
        For i = 0 To RTC_LAST_COLUMN
            nIdx = gdTot.Idx(i)
            If nIdx <> RTC_NONE Then
                .ColDataType(i) = gdTot.Col(nIdx).DataType
                .ColFormat(i) = gdTot.Col(nIdx).Format
                .ColKey(i) = nIdx
                .TextMatrix(0, i) = gdTot.Col(nIdx).Caption
            Else
                Exit For
            End If
        Next
        
        .Cell(flexcpAlignment, 0, 0, 0, nCols - 1) = flexAlignCenterCenter
        
        m_GridLock(GT_RISKS_TOTALS).UnlockRedraw
    End With
End Sub

Public Sub FormatTotColumns()
    On Error Resume Next
    Dim i&, nCols&, nRows&, nIdx&, aFont As New StdFont

    With fgTot
        m_GridLock(GT_RISKS_TOTALS).LockRedraw

        aFont.Name = gdTot.Font.Name
        aFont.Size = gdTot.Font.Size
        aFont.Bold = gdTot.Font.Bold
        aFont.Italic = gdTot.Font.Italic
        aFont.Strikethrough = gdTot.Font.Strikethrough
        aFont.Underline = gdTot.Font.Underline
        
        Set .Font = aFont
        
        nCols = .Cols - 1
        nRows = .Rows - 1
        For i = 0 To nCols
            nIdx = .ColKey(i)
            If nIdx <> RTC_NONE Then
                .Cell(flexcpBackColor, 1, i, nRows, i) = IIf(gdTot.Col(nIdx).BackColor <> 0, gdTot.Col(nIdx).BackColor, RGB(1, 1, 1))
                .Cell(flexcpForeColor, 1, i, nRows, i) = IIf(gdTot.Col(nIdx).ForeColor <> 0, gdTot.Col(nIdx).ForeColor, RGB(1, 1, 1))
            End If
        Next

        If gdTot.HorizLinesVisible Then
            If gdTot.VertLinesVisible Then
                .GridLines = flexGridFlat
            Else
                .GridLines = flexGridFlatHorz
            End If
        ElseIf gdTot.VertLinesVisible Then
            .GridLines = flexGridFlatVert
        Else
            .GridLines = flexGridNone
        End If
        .GridColor = gdTot.GridLinesColor

        .BackColorSel = gdTot.BackColorSel
        .ForeColorSel = gdTot.ForeColorSel

        .AutoSize 0, .Cols - 1

        m_GridLock(GT_RISKS_TOTALS).UnlockRedraw
    End With
End Sub

Public Sub FormatPosGrid()
    On Error Resume Next
    Dim i&, nCols&, nIdx&
    
    With fgPos
        m_GridLock(GT_RISKS_POSITIONS).LockRedraw
    
        gdPos.Idx(0) = RPC_SYMBOL
        nCols = 1
        For i = 1 To RPC_LAST_COLUMN
            If gdPos.Idx(i) <> RPC_NONE Then
                nCols = nCols + 1
            Else
                Exit For
            End If
        Next
        
        nCols = nCols + 1 ' for key column
        .Cols = nCols
        
        .ColHidden(RPC_KEY) = True
        .ColKey(RPC_KEY) = RPC_NONE
        .ColDataType(RPC_KEY) = flexDTString
        
        Set .Cell(flexcpPicture, 1, 0, .Rows - 1, nCols - 1) = Nothing
        .Cell(flexcpPictureAlignment, 1, 0, .Rows - 1, nCols - 1) = flexPicAlignLeftCenter
        
        For i = 0 To RPC_LAST_COLUMN
            nIdx = gdPos.Idx(i)
            If nIdx <> RPC_NONE Then
                .TextMatrix(0, i + 1) = gdPos.Col(nIdx).Caption
                .ColFormat(i + 1) = gdPos.Col(nIdx).Format
                .ColDataType(i + 1) = gdPos.Col(nIdx).DataType
                .ColKey(i + 1) = nIdx
                .ColWidth(i + 1) = IIf(gdPos.Col(nIdx).Width > 0, gdPos.Col(nIdx).Width, -1)
            Else
                Exit For
            End If
        Next
        
        .Cell(flexcpAlignment, 0, 0, 0, nCols - 1) = flexAlignCenterCenter
        gePos.AdjustSortImages
        
        m_GridLock(GT_RISKS_POSITIONS).UnlockRedraw
    End With
End Sub

Public Sub FormatPosColumns()
    On Error Resume Next
    Dim i&, nCols&, nRows&, nIdx&, aFont As New StdFont, aRowData As EtsMmRisksLib.MmRvRowData
    
    With fgPos
        m_GridLock(GT_RISKS_POSITIONS).LockRedraw

        aFont.Name = gdPos.Font.Name
        aFont.Size = gdPos.Font.Size
        aFont.Bold = gdPos.Font.Bold
        aFont.Italic = gdPos.Font.Italic
        aFont.Strikethrough = gdPos.Font.Strikethrough
        aFont.Underline = gdPos.Font.Underline
        
        Set .Font = aFont
        
        nCols = .Cols - 1
        nRows = .Rows - 1
        For i = 0 To nCols
            nIdx = .ColKey(i)
            If nIdx <> RPC_NONE Then
                .Cell(flexcpBackColor, 1, i, nRows, i) = IIf(gdPos.Col(nIdx).BackColor <> 0, gdPos.Col(nIdx).BackColor, RGB(1, 1, 1))
                .Cell(flexcpForeColor, 1, i, nRows, i) = IIf(gdPos.Col(nIdx).ForeColor <> 0, gdPos.Col(nIdx).ForeColor, RGB(1, 1, 1))
                
                If nRows > 1 Then
                    If nIdx = RPC_OPT_TYPE Then
                        .ColAlignment(i) = flexAlignCenterCenter
                    Else
                        .ColAlignment(i) = flexAlignGeneral
                    End If
                End If
            End If
        Next
        
'        For i = 1 To nRows
'            Set aRowData = .RowData(i)
'            If aRowData.Pos Is Nothing Then
'                .Cell(flexcpFontBold, i, 0, i, nCols) = True
'            ElseIf Not aRowData.Pos Is Nothing Then
'                If aRowData.Pos.IsSyntheticAggregation Then
'                    .Cell(flexcpFontBold, i, 0, i, nCols) = True
'                End If
'            End If
'        Next

        If gdPos.HorizLinesVisible Then
            If gdPos.VertLinesVisible Then
                .GridLines = flexGridFlat
            Else
                .GridLines = flexGridFlatHorz
            End If
        ElseIf gdPos.VertLinesVisible Then
            .GridLines = flexGridFlatVert
        Else
            .GridLines = flexGridNone
        End If
        .GridColor = gdPos.GridLinesColor
        
        .BackColorSel = gdPos.BackColorSel
        .ForeColorSel = gdPos.ForeColorSel

        m_GridLock(GT_RISKS_POSITIONS).UnlockRedraw
    End With
End Sub

Public Sub PosBeforeSort(ByVal Col As Long, Order As Integer)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    SortColKey = fgPos.ColKey(Col)
    SortColOrder = IIf(SortColOrder = flexSortGenericDescending, flexSortGenericAscending, flexSortGenericDescending)
        
    Order = flexSortCustom
End Sub

Public Sub PosAfterSort(ByVal Col&, ByRef Order%)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim bAsc As Boolean, nKey&
    
    nKey = fgPos.ColKey(Col)
    If SortColKey = nKey Then
        Order = SortColOrder
        SortColKey = -2
    End If
    
    If nKey <> RPC_OPT_TYPE And nKey <> RPC_EXPIRY And nKey <> RPC_STRIKE And nKey <> RPC_UND _
    And nKey <> RPC_DELTAP And nKey <> RPC_GAMMAP And nKey <> RPC_VEGAP And nKey <> RPC_THETAP And nKey <> RPC_RHOP Then 'And nKey <> RPC_SYNTHETIC_PRICE Then
        Select Case SortColOrder
            Case flexSortStringNoCaseAscending, flexSortStringAscending, flexSortNumericAscending, flexSortGenericAscending
                bAsc = True
            Case Else
                bAsc = False
        End Select
        
        m_GridLock(GT_RISKS_POSITIONS).LockRedraw
        SortPosNodes Col, bAsc
        m_GridLock(GT_RISKS_POSITIONS).UnlockRedraw
    End If
End Sub

Public Sub SortPosNodes(ByVal nCol As Long, ByVal bAsc As Boolean)
    On Error Resume Next
    Dim nRow&, arrVals() As NodeSortItemType, nUBound&, i&, bByStrKey As Boolean
    
'    With fgPos
'        If .Rows <= 1 Then Exit Sub
'
'        Select Case .ColDataType(nCol)
'            Case flexDTShort, flexDTLong, flexDTSingle, flexDTDouble, flexDTCurrency, flexDTDate, flexDTBoolean, flexDTDecimal
'                bByStrKey = False
'            Case flexDTString
'                bByStrKey = True
'            Case Else
'                Exit Sub
'        End Select
'
'        nUBound = 0
'        nRow = .GetNodeRow(1, flexNTFirstSibling)
'        While nRow > 0
'            If nUBound = 0 Then ReDim arrVals(1 To 1) Else ReDim Preserve arrVals(1 To nUBound + 1)
'            nUBound = nUBound + 1
'
'            Set arrVals(nUBound).Node = .GetNode(nRow)
'            If bByStrKey Then
'                arrVals(nUBound).StrKey = .TextMatrix(nRow, nCol)
'            Else
'                arrVals(nUBound).NumKey = .TextMatrix(nRow, nCol)
'            End If
'
'            nRow = .GetNodeRow(nRow, flexNTNextSibling)
'        Wend
'
'        If nUBound > 1 Then
'            SortNodeArray arrVals, 1, nUBound, bByStrKey
'
'            For i = 1 To nUBound
'                If bAsc Then
'                    arrVals(i).Node.Move flexNMLast
'                Else
'                    arrVals(i).Node.Move flexNMFirst
'                End If
'            Next
'        End If
'
'        Erase arrVals
'    End With
End Sub

Public Function CheckPosFilter(ByRef aPos As EtsMmRisksLib.MmRvPosAtom) As Boolean
    On Error Resume Next
    Dim bMatched As Boolean, nValue&
    
    nValue = Filter(RFC_EXPIRY)
    bMatched = (nValue = 0)
    If Not bMatched Then
        If aPos.ContractType = enCtOption Or aPos.ContractType = enCtFutOption Then
            bMatched = (nValue = CLng(aPos.Expiry))
        Else
            bMatched = False
        End If
    End If

    CheckPosFilter = bMatched
End Function

Public Function CheckTradeFilter(ByRef aTrd As EtsMmGeneralLib.MmTradeInfoAtom) As Boolean
    On Error Resume Next
    Dim bMatched As Boolean, nValue&
    
    'bMatched = False
    bMatched = True
    
    If Not aTrd Is Nothing Then
        
        If bMatched And Filter(RFC_SYMBOL) > 0 Then _
            bMatched = (aTrd.UndID = Filter(RFC_SYMBOL))
        If bMatched And Filter(RFC_GROUPS) > 0 Then _
            bMatched = Not g_UnderlyingGroup(Filter(RFC_GROUPS)).Und(aTrd.UndID) Is Nothing
        If bMatched And Filter(RFC_TRADER) > 0 Then _
            bMatched = (aTrd.Trader.ID = Filter(RFC_TRADER))
        If bMatched And Filter(RFC_TRADER_GROUP) > 0 Then _
            bMatched = (aTrd.Trader.GroupID = Filter(RFC_TRADER_GROUP))
        If bMatched And Filter(RFC_STRATEGY) <> 0 Then _
            bMatched = (aTrd.strategyID = IIf(Filter(RFC_STRATEGY) > 0, Filter(RFC_STRATEGY), 0))
        
        If bMatched Then
            nValue = Filter(RFC_TRADES)
            bMatched = (nValue = 0)
            If Not bMatched Then
                Select Case nValue
                    Case 1 ' Today's
                        bMatched = (Int(aTrd.TradeDate) = Int(Date) And aTrd.Status <> enTsSimulated)
                        
                    Case 2 ' OpenPos
                        bMatched = (Int(aTrd.TradeDate) < Int(Date) Or aTrd.IsPosition <> 0)
                        
                    Case 3 ' NetPos
                        bMatched = (aTrd.Status <> enTsSimulated)
                        
                    Case 4 ' Simulated
                        bMatched = (aTrd.Status = enTsSimulated)
                        
                    Case 5 ' Today's & Sim
                        bMatched = (Int(aTrd.TradeDate) = Int(Date) Or aTrd.Status = enTsSimulated)
                
                    Case 6 ' OpenPos & Sim
                        bMatched = (Int(aTrd.TradeDate) < Int(Date) Or aTrd.IsPosition <> 0 Or aTrd.Status = enTsSimulated)
                        
                    Case 7 ' Manual
                        bMatched = (aTrd.Status = enTsManual)
                
                    Case 8 ' Manual & Sim
                        bMatched = (aTrd.Status = enTsManual Or aTrd.Status = enTsSimulated)
                        
                End Select
            End If
        End If
    End If

    CheckTradeFilter = bMatched
'    If Not aTrd Is Nothing Then
''        If aTrd.ContractTypeID = enCtOption Then
''            If aTrd.Expiry <= Date Then Exit Sub
''        End If
'
'        nValue = Filter(RFC_SYMBOL)
'
'        If nValue <> 0 Then
'            Select Case Filter(RFC_SYMBOL)
'                Case TYPE_UNDERLYING
'                    bMatched = (aTrd.UndID = nValue)
'
'                Case TYPE_GROUP
'                    bMatched = Not g_UnderlyingGroup(nValue).Und(aTrd.UndID) Is Nothing
'
'                Case TYPE_TRADER_GROUP
'                    bMatched = Not g_TraderGroup(nValue).Trader(aTrd.Trader.ID) Is Nothing
'
'                Case TYPE_TRADER
'                    bMatched = (aTrd.Trader.ID = nValue)
'
'                Case TYPE_STRATEGY
'                    bMatched = (aTrd.StrategyID = IIf(nValue > 0, nValue, 0))
'
'                Case TYPE_ALL
'                    bMatched = True
'
'            End Select
'
'            If bMatched Then
'                nValue = Filter(RFC_SYMBOL)
'                bMatched = (nValue = 0)
'                If Not bMatched Then
'                    Select Case nValue
'                        Case 1 ' Today's
'                            bMatched = (Int(aTrd.TradeDate) = Int(Date) And aTrd.Status <> enTsSimulated)
'
'                        Case 2 ' OpenPos
'                            bMatched = (Int(aTrd.TradeDate) < Int(Date) Or aTrd.IsPosition <> 0)
'
'                        Case 3 ' NetPos
'                            bMatched = (aTrd.Status <> enTsSimulated)
'
'                        Case 4 ' Simulated
'                            bMatched = (aTrd.Status = enTsSimulated)
'
'                        Case 5 ' Today's & Sim
'                            bMatched = (Int(aTrd.TradeDate) = Int(Date) Or aTrd.Status = enTsSimulated)
'
'                        Case 6 ' OpenPos & Sim
'                            bMatched = (Int(aTrd.TradeDate) < Int(Date) Or aTrd.IsPosition <> 0 Or aTrd.Status = enTsSimulated)
'
'                        Case 7 ' Manual
'                            bMatched = (aTrd.Status = enTsManual)
'
'                        Case 8 ' Manual & Sim
'                            bMatched = (aTrd.Status = enTsManual Or aTrd.Status = enTsSimulated)
'
'                    End Select
'                End If
'            End If
'        End If
'    End If
'
'    CheckTradeFilter = bMatched
End Function

Public Sub FilterUpdateAll()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    With fgFlt
        m_GridLock(GT_RISKS_FILTER).LockRedraw
        
        
        FilterUpdateValue False, RFC_SYMBOL
        FilterUpdateValue False, RFC_GROUPS
        FilterUpdateValue False, RFC_TRADER
        FilterUpdateValue False, RFC_TRADER_GROUP
        
        FilterUpdateValue False, RFC_STRATEGY
        .TextMatrix(1, RFC_TRADES) = Filter(RFC_TRADES)
        
        FilterUpdateIndex False
        FilterUpdateExpiry False
        FilterUpdateModel False
        'FilterUpdateTimeLeft False, ""

'       .TextMatrix(1, RFC_AGGREGATION) = Filter(RFC_AGGREGATION)
'       .TextMatrix(1, RFC_SUBAGGREGATION) = Filter(RFC_SUBAGGREGATION)
        
        'PrepareCalcDateColumn
        
        .AutoSize 0, .Cols - 1, , 100
        
        m_GridLock(GT_RISKS_FILTER).UnlockRedraw
    End With

'    On Error Resume Next
'    If m_bShutDown Then Exit Sub
'
'    With fgFlt
'        m_GridLock(GT_RISKS_FILTER).LockRedraw
'
'        If Filter(RFC_GROUP) <> TYPE_UNDERLYING _
'            And Filter(RFC_GROUP) <> TYPE_GROUP _
'            And Filter(RFC_GROUP) <> TYPE_TRADER_GROUP _
'            And Filter(RFC_GROUP) <> TYPE_TRADER _
'            And Filter(RFC_GROUP) <> TYPE_STRATEGY _
'            And Filter(RFC_GROUP) <> TYPE_ALL Then
'
'            Filter(RFC_GROUP) = TYPE_UNDERLYING
'            Filter(RFC_VALUE) = 0
'        End If
'
'        If Filter(RFC_GROUP) = TYPE_ALL Then Filter(RFC_VALUE) = -1
'
'        .TextMatrix(1, RFC_GROUP) = Filter(RFC_GROUP)
'
'        FilterUpdateValue False
'
'        .TextMatrix(1, RFC_TYPE) = Filter(RFC_TYPE)
'
'        FilterUpdateIndex False
'        FilterUpdateExpiry False
'        FilterUpdateModel False
'
'        .AutoSize 0, .Cols - 1, , 100
'
'        m_GridLock(GT_RISKS_FILTER).UnlockRedraw
'    End With
End Sub
Public Sub FilterUpdateValue(ByVal bAutosize As Boolean, enColumn As RisksFilterColumnEnum)
'Public Sub FilterUpdateValue(ByVal bAutosize As Boolean)
 On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim i&, nCount&, sComboList$, sValue$, aUnd As EtsGeneralLib.UndAtom, aStrategy As EtsGeneralLib.EtsStrategyAtom
    Dim nValue&, aTrader As EtsGeneralLib.EtsTraderAtom, aUndGroup As EtsGeneralLib.EtsUndGroupAtom
    Dim aTraderGroup As EtsGeneralLib.EtsTraderGroupAtom
    
    With fgFlt
        m_GridLock(GT_RISKS_FILTER).LockRedraw
        
        sValue = "0"
        nValue = 0
        sComboList = ""
        Select Case enColumn
           Case RFC_SYMBOL
                sComboList = g_Params.UnderlyingComboList
                
                Set aUnd = g_Underlying(Filter(RFC_SYMBOL))
                If Not aUnd Is Nothing Then
                    nValue = aUnd.ID
                    sValue = Trim$(Str$(nValue))
                    Set aUnd = Nothing
                End If
                
                If Len(sComboList) > 0 And nValue = 0 Then sComboList = "|" & sComboList
           Case RFC_GROUPS
                For Each aUndGroup In g_UnderlyingGroup
                    sComboList = sComboList & "|#" & Trim$(Str$(aUndGroup.ID)) & ";" & aUndGroup.Name
                    If aUndGroup.ID = Filter(RFC_GROUPS) Then
                        nValue = aUndGroup.ID
                        sValue = Trim$(Str$(nValue))
                    End If
                Next
           Case RFC_TRADER
               For Each aTrader In g_Trader
                    sComboList = sComboList & "|#" & Trim$(Str$(aTrader.ID)) & ";" & aTrader.Name
                    If aTrader.ID = Filter(RFC_TRADER) Then
                        nValue = aTrader.ID
                        sValue = Trim$(Str$(nValue))
                    End If
                Next
           Case RFC_TRADER_GROUP
               For Each aTraderGroup In g_TraderGroup
                    If aTraderGroup.ID <> 0 Then
                        sComboList = sComboList & "|#" & Trim$(Str$(aTraderGroup.ID)) & ";" & aTraderGroup.Name
                    End If
                    If aTraderGroup.ID = Filter(RFC_TRADER_GROUP) Then
                        nValue = aTraderGroup.ID
                        sValue = Trim$(Str$(nValue))
                    End If
                Next
           Case RFC_STRATEGY
                sComboList = "|#" & Trim$(Str$(NO_STRATEGY_ID)) & ";" & NO_STRATEGY_NAME
                If Filter(RFC_STRATEGY) = NO_STRATEGY_ID Then
                    nValue = NO_STRATEGY_ID
                    sValue = NO_STRATEGY_NAME
                End If
                
                For Each aStrategy In g_Strategy
                    sComboList = sComboList & "|#" & Trim$(Str$(aStrategy.ID)) & ";" & aStrategy.Name
                    If aStrategy.ID = Filter(RFC_STRATEGY) Then
                        nValue = aStrategy.ID
                        sValue = Trim$(Str$(nValue))
                    End If
                Next
           Case Else
             Debug.Assert False
             Exit Sub
        End Select
        
        
        If Len(sComboList) > 0 Then
                If InStr(1, sComboList, "|") = 1 Then
                    sComboList = "#0;<All>|" & Mid$(sComboList, InStr(1, sComboList, "|") + 1)
                Else
                    sComboList = "#0;<All>|" & sComboList
                End If
        Else
            sComboList = "#0;<None>"
        End If
        
        .ColComboList(enColumn) = sComboList
        .TextMatrix(1, enColumn) = sValue
        Filter(enColumn) = nValue
        
        If bAutosize Then .AutoSize 0, .Cols - 1, , 100
        
        m_GridLock(GT_RISKS_FILTER).UnlockRedraw
    End With
'    On Error Resume Next
'    If m_bShutDown Then Exit Sub
'    Dim i&, nCount&, sComboList$, sValue$, aUnd As EtsGeneralLib.UndAtom, aStrategy As EtsGeneralLib.EtsStrategyAtom
'    Dim nValue&, aTrader As EtsGeneralLib.EtsTraderAtom, aUndGroup As EtsGeneralLib.EtsUndGroupAtom
'    Dim aTraderGroup As EtsGeneralLib.EtsTraderGroupAtom
'
'    With fgFlt
'        m_GridLock(GT_RISKS_FILTER).LockRedraw
'
'        sValue = "0"
'        nValue = 0
'        sComboList = ""
'
'        Select Case Filter(RFC_GROUP)
'            Case TYPE_ALL
'                sValue = "-1"
'                nValue = -1
'                sComboList = "#-1;<All>"
'
'            Case TYPE_UNDERLYING
'                sComboList = g_Params.UnderlyingComboList
'
'                Set aUnd = g_Underlying(Filter(RFC_VALUE))
'                If Not aUnd Is Nothing Then
'                    nValue = aUnd.ID
'                    sValue = Trim$(Str$(nValue))
'                    Set aUnd = Nothing
'                End If
'
'                If Len(sComboList) > 0 And nValue = 0 Then sComboList = "|" & sComboList
'
'            Case TYPE_TRADER_GROUP
'                For Each aTraderGroup In g_TraderGroup
'                    If aTraderGroup.ID <> 0 Then
'                        sComboList = sComboList & "|#" & Trim$(Str$(aTraderGroup.ID)) & ";" & aTraderGroup.Name
'                    End If
'                    If aTraderGroup.ID = Filter(RFC_VALUE) Then
'                        nValue = aTraderGroup.ID
'                        sValue = Trim$(Str$(nValue))
'                    End If
'                Next
'
'            Case TYPE_TRADER
'                For Each aTrader In g_Trader
'                    sComboList = sComboList & "|#" & Trim$(Str$(aTrader.ID)) & ";" & aTrader.Name
'                    If aTrader.ID = Filter(RFC_VALUE) Then
'                        nValue = aTrader.ID
'                        sValue = Trim$(Str$(nValue))
'                    End If
'                Next
'
'            Case TYPE_GROUP
'                For Each aUndGroup In g_UnderlyingGroup
'                    sComboList = sComboList & "|#" & Trim$(Str$(aUndGroup.ID)) & ";" & aUndGroup.Name
'                    If aUndGroup.ID = Filter(RFC_VALUE) Then
'                        nValue = aUndGroup.ID
'                        sValue = Trim$(Str$(nValue))
'                    End If
'                Next
'
'            Case TYPE_STRATEGY
'                sComboList = "|#" & Trim$(Str$(NO_STRATEGY_ID)) & ";" & NO_STRATEGY_NAME
'                If Filter(RFC_VALUE) = NO_STRATEGY_ID Then
'                    nValue = NO_STRATEGY_ID
'                    sValue = NO_STRATEGY_NAME
'                End If
'
'                For Each aStrategy In g_Strategy
'                    sComboList = sComboList & "|#" & Trim$(Str$(aStrategy.ID)) & ";" & aStrategy.Name
'                    If aStrategy.ID = Filter(RFC_VALUE) Then
'                        nValue = aStrategy.ID
'                        sValue = Trim$(Str$(nValue))
'                    End If
'                Next
'
'        End Select
'
'        If Len(sComboList) > 0 Then
'            If nValue = 0 Then
'                sComboList = "#0;<Select>" & sComboList
'            Else
'                If InStr(1, sComboList, "|") = 1 Then
'                    sComboList = Mid$(sComboList, InStr(1, sComboList, "|") + 1)
'                End If
'            End If
'        Else
'            sComboList = "#0;<None>"
'        End If
'
'        .ColComboList(RFC_VALUE) = sComboList
'        .TextMatrix(1, RFC_VALUE) = sValue
'        Filter(RFC_VALUE) = nValue
'
'        If bAutosize Then .AutoSize 0, .Cols - 1, , 100
'
'        m_GridLock(GT_RISKS_FILTER).UnlockRedraw
'    End With
End Sub

Public Sub FilterUpdateIndex(ByVal bAutosize As Boolean)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim sComboList$, sValue$, m_Idx As EtsGeneralLib.IndexAtom
    Dim nValue&, nFirstValue&
    
    With fgFlt
        m_GridLock(GT_RISKS_FILTER).LockRedraw
        
        sValue = "0"
        nValue = 0
        nFirstValue = 0
        sComboList = ""
        For Each m_Idx In g_HedgeSymbols
            If m_Idx.HaveComponentBetas Then
                sComboList = sComboList & "|#" & Trim$(Str$(m_Idx.ID)) & ";" & m_Idx.Symbol
                If m_Idx.ID = Filter(RFC_INDEX) Then
                    nValue = m_Idx.ID
                    sValue = Trim$(Str$(m_Idx.ID))
                End If
                If nFirstValue = 0 Then nFirstValue = m_Idx.ID
            End If
        Next
        
        If Len(sComboList) > 0 Then
            sComboList = Mid$(sComboList, 2)
            If nValue = 0 Then
                nValue = nFirstValue
                sValue = Trim$(Str$(nValue))
            End If
        Else
            sComboList = "#0;<None>"
        End If
        
        .ColComboList(RFC_INDEX) = sComboList
        .TextMatrix(1, RFC_INDEX) = sValue
        Filter(RFC_INDEX) = nValue
        
        If bAutosize Then .AutoSize 0, .Cols - 1, , 100
        
        m_GridLock(GT_RISKS_FILTER).UnlockRedraw
    End With
End Sub

Public Sub FilterUpdateExpiry(ByVal bAutosize As Boolean)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nValue&, aExp As EtsGeneralLib.EtsMmEntityAtom, sValue$, sComboList$
    
    With fgFlt
        m_GridLock(GT_RISKS_FILTER).LockRedraw
        
        sValue = "0"
        nValue = 0
        sComboList = "#0;<All>"
        For Each aExp In m_RiskView.Exp
            sComboList = sComboList & "|#" & Trim$(Str$(aExp.ID)) & ";" & aExp.Name
            If aExp.ID = Filter(RFC_EXPIRY) Then
                nValue = aExp.ID
                sValue = Trim$(Str$(aExp.ID))
            End If
        Next
        .ColComboList(RFC_EXPIRY) = sComboList
        .TextMatrix(1, RFC_EXPIRY) = sValue
        Filter(RFC_EXPIRY) = nValue
        
        If bAutosize Then .AutoSize 0, .Cols - 1, , 100
        
        m_GridLock(GT_RISKS_FILTER).UnlockRedraw
    End With
End Sub

Public Sub FilterUpdateModel(ByVal bAutosize As Boolean)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    With fgFlt
        m_GridLock(GT_RISKS_FILTER).LockRedraw
    
        .TextMatrix(1, RFC_MODEL) = g_Params.CalcModelName(g_Params.CalcModel)
        
        If bAutosize Then .AutoSize 0, .Cols - 1, , 100
        
        m_GridLock(GT_RISKS_FILTER).UnlockRedraw
    End With
End Sub

Public Sub GridAfterMoveColumn(ByRef gd As clsGridDef, ByVal Col&, ByRef Position&, ByVal nFirstCol&)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nIdx&, i&, nOldPos&, nNewPos&
    If Col = Position Then Exit Sub
    
    nOldPos = Col - nFirstCol
    nNewPos = Position - nFirstCol
    nIdx = gd.Idx(nOldPos)
    If nOldPos > nNewPos Then
        For i = nOldPos To nNewPos Step -1
            If i > nNewPos Then gd.Idx(i) = gd.Idx(i - 1)
        Next
        gd.Idx(nNewPos) = nIdx
    Else
        For i = nOldPos To nNewPos
            If i < nNewPos Then gd.Idx(i) = gd.Idx(i + 1)
        Next
        gd.Idx(nNewPos) = nIdx
    End If
End Sub

Public Sub GridBeforeMoveColumn(ByRef fg As VSFlex7Ctl.VSFlexGrid, ByRef gd As clsGridDef, _
                                ByVal Col&, ByRef Position&, ByVal nNoneCol&)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nOldIdx&, nNewIdx&
    
    nOldIdx = fg.ColKey(Col)
    nNewIdx = fg.ColKey(Position)
    
    If nOldIdx = nNoneCol Or nNewIdx = nNoneCol Then
        Position = Col
    ElseIf Not gd.Col(nOldIdx).CanChangeOrder Or Not gd.Col(nNewIdx).CanChangeOrder Then
        Position = Col
    End If
End Sub



