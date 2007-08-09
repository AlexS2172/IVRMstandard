VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsAuxRiskViewOut"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private m_Aux As clsAuxRiskView

Public gdFlt As clsGridDef
Public gdTot As clsGridDef
Public gdPos As clsGridDef

Public fgPos As VSFlex7Ctl.VSFlexGrid
Public fgTot As VSFlex7Ctl.VSFlexGrid
Public imgBadPrice As VB.Image

Public Sub Init(ByRef aAux As clsAuxRiskView)
    On Error Resume Next
    Set m_Aux = aAux
End Sub

Private Sub Class_Terminate()
    On Error Resume Next
    Set m_Aux = Nothing
End Sub

Public Sub UnderlyingsUpdate(ByVal bSymbol As Boolean, Optional ByVal bRealTimeUpdate As Boolean = False)
    On Error Resume Next
    Dim nRow&
    Dim aRowData As EtsMmRisksLib.MmRvRowData
    Dim aUnd As EtsMmRisksLib.MmRvUndAtom, aPos As EtsMmRisksLib.MmRvPosAtom, aFut As EtsMmRisksLib.MmRvFutAtom

    With fgPos
'        m_Aux.GridLock(GT_RISKS_POSITIONS).LockRedraw
    
'        For nRow = 1 To .Rows - 1
'            If .RowOutlineLevel(nRow) >= ROL_POS Then
'                PositionUpdate nRow, bSymbol, bRealTimeUpdate
'            Else
'                UnderlyingUpdate nRow, bSymbol, bRealTimeUpdate
'            End If
'        Next

        If bRealTimeUpdate Then
            m_Aux.Idx.CalcGreeks = False
            m_Aux.Idx.CalcTotals = False
            
            ' clear update status
            For Each aUnd In m_Aux.Und
                aUnd.CalcGreeks = False
                aUnd.CalcTotals = False
                
                For Each aPos In aUnd.Pos
                    aPos.CalcGreeks = False
                Next
            
                If Not aUnd.Fut Is Nothing Then
                    For Each aFut In aUnd.Fut
                        aFut.CalcGreeks = False
                    Next
                End If
            Next
        End If

'        m_Aux.GridLock(GT_RISKS_POSITIONS).UnlockRedraw
    End With
End Sub

Public Sub UnderlyingsUpdateBadStatus()
    On Error Resume Next
    Dim nRow&

    With fgPos
        m_Aux.GridLock(GT_RISKS_POSITIONS).LockRedraw
    
        nRow = .GetNodeRow(1, flexNTFirstSibling)
        While nRow > 0
            UnderlyingUpdateBadStatus nRow
            nRow = .GetNodeRow(nRow, flexNTNextSibling)
        Wend
        
        m_Aux.GridLock(GT_RISKS_POSITIONS).UnlockRedraw
    End With
End Sub

'Public Sub PositionsUpdate(ByVal nUndRow&, ByVal bSymbol As Boolean)
'    On Error Resume Next
'    Dim nRow&, nFirstRow&, nLastRow&
'
'    With fgPos
'        m_Aux.GridLock(GT_RISKS_POSITIONS).LockRedraw
'
'        nFirstRow = .GetNodeRow(nUndRow, flexNTFirstChild)
'        nLastRow = .GetNodeRow(nUndRow, flexNTLastChild)
'        If nFirstRow > 0 And nLastRow > 0 Then
'            For nRow = nFirstRow To nLastRow
'                PositionUpdate nRow, bSymbol
'            Next
'        End If
'
'        m_Aux.GridLock(GT_RISKS_POSITIONS).UnlockRedraw
'    End With
'End Sub
'
'Public Sub SyntheticPositionsUpdate(ByRef aUnd As EtsMmRisksLib.MmRvUndAtom)
'    On Error Resume Next
'    Dim aUnd2 As EtsMmRisksLib.MmRvUndAtom, sKey$, nRow&
'
'    With fgPos
'        m_Aux.GridLock(GT_RISKS_POSITIONS).LockRedraw
'
'        For Each aUnd2 In m_Aux.Und
'            sKey = CStr(aUnd2.ID) & "_" & CStr(aUnd.ID)
'            nRow = .FindRow(sKey, 1, RPC_KEY, , True)
'
'            If nRow > 0 Then
'                sKey = CStr(aUnd2.ID) & "_" & CStr(aUnd2.ID)
'                nRow = fgPos.FindRow(sKey, 1, RPC_KEY, , True)
'                If nRow > 0 Then
'                    UnderlyingUpdate nRow, False
'                    PositionsUpdate nRow, False
'                End If
'            End If
'        Next
'
'        m_Aux.GridLock(GT_RISKS_POSITIONS).UnlockRedraw
'    End With
'End Sub
'
'Public Sub SyntheticPositionGreeksUpdate(ByVal nUndID&, ByRef aPos As EtsMmRisksLib.MmRvPosAtom, ByVal bSymbol As Boolean)
'    On Error Resume Next
'    Dim sKey$, nRow&, aSynthGreek  As EtsMmRisksLib.MmRvSynthGreeksAtom
'
'    If aPos.SynthGreeks Is Nothing Then Exit Sub
'
'    With fgPos
'        m_Aux.GridLock(GT_RISKS_POSITIONS).LockRedraw
'
'        For Each aSynthGreek In aPos.SynthGreeks
'            sKey = CStr(nUndID) & "_" & CStr(aSynthGreek.SynthUndID) & "_" & CStr(aSynthGreek.ContractID)
'
'            nRow = .FindRow(sKey, 1, RPC_KEY, , True)
'
'            If nRow > 0 Then
'                SyntheticGreeksUpdate nRow, bSymbol
'            Else
'                Debug.Assert False
'            End If
'        Next
'
'        m_Aux.GridLock(GT_RISKS_POSITIONS).UnlockRedraw
'    End With
'End Sub
'
'Public Sub SyntheticUnderlyingGreeksUpdate(ByRef aUnd As EtsMmRisksLib.MmRvUndAtom, ByVal bSymbol As Boolean)
'    On Error Resume Next
'    Dim sKey$, nRow&, aSynthGreek  As EtsMmRisksLib.MmRvSynthGreeksAtom
'
'    If aUnd.SynthGreeks Is Nothing Then Exit Sub
'
'    With fgPos
'        m_Aux.GridLock(GT_RISKS_POSITIONS).LockRedraw
'
'        For Each aSynthGreek In aUnd.SynthGreeks
'            sKey = CStr(aUnd.ID) & "_" & CStr(aSynthGreek.SynthUndID)
'
'            nRow = .FindRow(sKey, 1, RPC_KEY, , True)
'
'            If nRow > 0 Then
'                SyntheticGreeksUpdate nRow, bSymbol
'            Else
'                Debug.Assert False
'            End If
'        Next
'
'        m_Aux.GridLock(GT_RISKS_POSITIONS).UnlockRedraw
'    End With
'End Sub

'Public Sub PositionUpdate(ByVal nRow&, ByVal bSymbol As Boolean, Optional ByVal bRealTimeUpdate As Boolean = False)
'    On Error Resume Next
'    Dim nCol&, aUnd As EtsMmRisksLib.MmRvUndAtom, aPos As EtsMmRisksLib.MmRvPosAtom, aRowData As EtsMmRisksLib.MmRvRowData
'
'    With fgPos
'        'Set aRowData = .RowData(nRow)
'        Set aRowData = m_Aux.RiskView.PosRowData(nRow)
'        Set aPos = aRowData.Pos
'        Set aUnd = aRowData.Und
'
'        If bRealTimeUpdate Then
'            Dim bNeedUpdate As Boolean
'
'            bNeedUpdate = aUnd.CalcGreeks Or aUnd.CalcTotals Or m_Aux.Idx.CalcTotals
'
'            If Not aPos Is Nothing Then
'                bNeedUpdate = bNeedUpdate Or aPos.CalcGreeks
'
'                If aPos.ContractType = enCtFutOption Then
'                    bNeedUpdate = bNeedUpdate Or aPos.Fut.CalcGreeks
'                End If
'            End If
'
'            If Not bNeedUpdate Then
'                GoTo Ex
'            End If
'        End If
'
'        If Not aRowData.SynthGreeks Is Nothing Then
'            SyntheticGreeksUpdate nRow, bSymbol
'            GoTo Ex
'        End If
'
'        If Not aUnd Is Nothing And Not aPos Is Nothing Then
'            Dim enPriceStatus As EtsGeneralLib.EtsReplacePriceStatusEnum
'
'            If aUnd.ID = aPos.ID Then
'                enPriceStatus = aUnd.ReplacePriceStatus
'            Else
'                enPriceStatus = aPos.Quote.ReplacePriceStatus
'            End If
'
'            m_Aux.GridLock(GT_RISKS_POSITIONS).LockRedraw
'
'            Dim i&, nIdx&
'            i = 0
'            nIdx = gdPos.Idx(0)
'            While nIdx >= 0 And i <= RPC_LAST_COLUMN
'                nCol = i + 1
'
'                '-------------------------------------------------------------
'                Select Case nIdx
'                    Case RPC_NET_DELTA, RPC_NET_DELTA_USD, RPC_BETA_WTD_DELTA_USD
'                        ' Clear table cell
'                        .TextMatrix(nRow, nCol) = ""
'                End Select
'
'                '-----------------------------------------------------------
'
'
'                If bSymbol Then
'                    Select Case aPos.ContractType
'                        Case enCtOption
'                            Select Case nIdx
'                                Case RPC_SYMBOL
'                                    .TextMatrix(nRow, nCol) = aPos.Symbol
'
'                                Case RPC_OPT_TYPE
'                                    .TextMatrix(nRow, nCol) = IIf(aPos.OptType = enOtCall, "C", "P")
'
'                                Case RPC_EXPIRY
'                                    .TextMatrix(nRow, nCol) = aPos.Expiry
'
'                                Case RPC_STRIKE
'                                    .TextMatrix(nRow, nCol) = IIf(aPos.Strike > BAD_DOUBLE_VALUE, aPos.Strike, STR_NA)
'
'                                Case RPC_UND
'                                    .TextMatrix(nRow, nCol) = aUnd.Symbol
'
'                                Case RPC_DEL_UNIT
'                                    If Not aPos.IsSynthetic Then
'                                        .TextMatrix(nRow, nCol) = aPos.Quote.LotSize
'                                    Else
'                                        Dim aSynthRoot As EtsGeneralLib.SynthRootAtom
'                                        Set aSynthRoot = aUnd.SynthRoots(aPos.OptionRootID)
'
'                                        .TextMatrix(nRow, nCol) = aSynthRoot.SynthRootComponents(aUnd.ID).Weight * aPos.Quote.LotSize
'                                    End If
'
'                                Case RPC_FUT_ROOT, RPC_FUTURES, RPC_FUT_MATURITY
'                                    .TextMatrix(nRow, nCol) = ""
'
'
'                                Case RPC_IMPORT_ID
'                                    .TextMatrix(nRow, nCol) = aPos.ImportID
'
'                            End Select
'
'                        Case enCtFuture
'                            Select Case nIdx
'                                Case RPC_SYMBOL
'                                    .TextMatrix(nRow, nCol) = aPos.Symbol
'
'                                Case RPC_OPT_TYPE, RPC_EXPIRY, RPC_STRIKE
'                                    .TextMatrix(nRow, nCol) = ""
'
'                                Case RPC_UND
'                                    .TextMatrix(nRow, nCol) = aUnd.Symbol
'
'                                Case RPC_DEL_UNIT
'                                    .TextMatrix(nRow, nCol) = aPos.Quote.LotSize
'
'                                Case RPC_FUT_ROOT
'                                    .TextMatrix(nRow, nCol) = aPos.Fut.FutRootSymbol
'
'                                Case RPC_FUTURES
'                                    .TextMatrix(nRow, nCol) = aPos.Fut.Symbol
'
'                                Case RPC_FUT_MATURITY
'                                    .TextMatrix(nRow, nCol) = aPos.Fut.Maturity
'
'                                'Case RPC_FPRICE_FORMAT
'                                '    .TextMatrix(nRow, nCol) = aPos.Fut.PriceFormat
'
''                                Case RPC_FCNTR_SIZE
''                                    .TextMatrix(nRow, nCol) = aPos.Fut.FutLotSize
'
'                                'Case RPC_FQUOT_UNIT
'                                '    .TextMatrix(nRow, nCol) = aPos.Fut.QuotationUnit
'                            End Select
'
'                        Case enCtFutOption
'                            Select Case nIdx
'                                Case RPC_SYMBOL
'                                    .TextMatrix(nRow, nCol) = aPos.Symbol
'
'                                Case RPC_OPT_TYPE
'                                    .TextMatrix(nRow, nCol) = IIf(aPos.OptType = enOtCall, "C", "P")
'
'                                Case RPC_EXPIRY
'                                    .TextMatrix(nRow, nCol) = aPos.Expiry
'
'                                Case RPC_STRIKE
'                                    .TextMatrix(nRow, nCol) = IIf(aPos.Strike > BAD_DOUBLE_VALUE, aPos.Strike, STR_NA)
'
'                                Case RPC_UND
'                                    .TextMatrix(nRow, nCol) = aUnd.Symbol
'
'                                Case RPC_DEL_UNIT
'                                    .TextMatrix(nRow, nCol) = aPos.Quote.LotSize
'
'                                Case RPC_FUT_ROOT
'                                    .TextMatrix(nRow, nCol) = aPos.Fut.FutRootSymbol
'
'                                Case RPC_FUTURES
'                                    .TextMatrix(nRow, nCol) = aPos.Fut.Symbol
'
'                                Case RPC_FUT_MATURITY
'                                    .TextMatrix(nRow, nCol) = aPos.Fut.Maturity
'
'                                Case RPC_IMPORT_ID
'                                    .TextMatrix(nRow, nCol) = aPos.ImportID
'
'                            End Select
'
'                        Case Else 'underlying
'                            Select Case nIdx
'                                Case RPC_SYMBOL
'                                    .TextMatrix(nRow, nCol) = aPos.Symbol
'
'                                Case RPC_OPT_TYPE, RPC_EXPIRY, RPC_STRIKE, RPC_FUT_ROOT, RPC_FUTURES, RPC_FUT_MATURITY
'                                    .TextMatrix(nRow, nCol) = ""
'
'                                Case RPC_UND
'                                    .TextMatrix(nRow, nCol) = aUnd.Symbol
'
'                                Case RPC_DEL_UNIT
'                                    .TextMatrix(nRow, nCol) = aUnd.LotSize
'                            End Select
'                    End Select
'                End If
'
'                Select Case nIdx
'                    Case RPC_NETCHANGE
'                        .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Price.NetChange <> BAD_DOUBLE_VALUE, aPos.Quote.Price.NetChange, STR_NA)
'                    Case RPC_BID
'                        .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Price.Bid > BAD_DOUBLE_VALUE, aPos.Quote.Price.Bid, STR_NA)
'
'                        If aPos.ContractType <> enCtOption And aPos.ID <> USD_ID Then
'                            If enPriceStatus And enRpsBid Then
'                                Set .Cell(flexcpPicture, nRow, nCol) = imgBadPrice.Picture
'                                .Cell(flexcpPictureAlignment, nRow, nCol) = flexPicAlignLeftCenter
'                            Else
'                                If Not .Cell(flexcpPicture, nRow, nCol) Is Nothing Then
'                                    Set .Cell(flexcpPicture, nRow, nCol) = Nothing
'                                End If
'                            End If
'                        End If
'
'                    Case RPC_ASK
'                        .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Price.Ask > BAD_DOUBLE_VALUE, aPos.Quote.Price.Ask, STR_NA)
'
'                        If aPos.ContractType <> enCtOption And aPos.ID <> USD_ID Then
'                            If enPriceStatus And enRpsAsk Then
'                                Set .Cell(flexcpPicture, nRow, nCol) = imgBadPrice.Picture
'                                .Cell(flexcpPictureAlignment, nRow, nCol) = flexPicAlignLeftCenter
'                            Else
'                                If Not .Cell(flexcpPicture, nRow, nCol) Is Nothing Then
'                                    Set .Cell(flexcpPicture, nRow, nCol) = Nothing
'                                End If
'                            End If
'                        End If
'
''                    Case RPC_SYNTHETIC_PRICE
''                         .TextMatrix(nRow, nCol) = IIf(aPos.SuPrice > BAD_DOUBLE_VALUE, aPos.SuPrice, STR_NA)
'
'                    Case RPC_LAST
'                        .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Price.Last > BAD_DOUBLE_VALUE, aPos.Quote.Price.Last, STR_NA)
'
'                    Case RPC_CLOSE
'                        .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Price.Close > 0#, aPos.Quote.Price.Close, STR_NA)
'
'                    Case RPC_PNL_MTM
'                        .TextMatrix(nRow, nCol) = IIf(aPos.PnlMtm > BAD_DOUBLE_VALUE, aPos.PnlMtm, STR_NA)
'
'                    Case RPC_PNL_THEO
'                        .TextMatrix(nRow, nCol) = IIf(aPos.PnlTheo > BAD_DOUBLE_VALUE, aPos.PnlTheo, STR_NA)
'
'                    Case RPC_PNL_EDGE
'                        If aPos.PnlTheo > BAD_DOUBLE_VALUE And aPos.PnlMtm > BAD_DOUBLE_VALUE Then
'                            .TextMatrix(nRow, nCol) = aPos.PnlTheo - aPos.PnlMtm
'                        Else
'                            .TextMatrix(nRow, nCol) = STR_NA
'                        End If
'                End Select
'
'                Select Case aPos.ContractType
'                    Case enCtOption
'                        Select Case nIdx
'                            Case RPC_UND_POS, RPC_FUT_QTY
'                                .TextMatrix(nRow, nCol) = ""
'
'                            Case RPC_OPT_QTY
'                                .TextMatrix(nRow, nCol) = IIf(aPos.Qty > BAD_LONG_VALUE, aPos.Qty, STR_NA)
'
'                            Case RPC_OPT_DELTA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.DeltaInShares > BAD_DOUBLE_VALUE, aPos.DeltaInShares, STR_NA)
'
'                            Case RPC_GAMMA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.GammaInSharesPerc > BAD_DOUBLE_VALUE, aPos.GammaInSharesPerc, STR_NA)
'
'                            Case RPC_NET_GAMMA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.NetGamma > BAD_DOUBLE_VALUE, aPos.NetGamma, STR_NA)
'
'                            Case RPC_GAMMA_SHARES
'                                .TextMatrix(nRow, nCol) = IIf(aPos.GammaInShares > BAD_DOUBLE_VALUE, aPos.GammaInShares, STR_NA)
'
'                            Case RPC_VEGA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.VegaInShares > BAD_DOUBLE_VALUE, aPos.VegaInShares, STR_NA)
'
'                            Case RPC_WTD_VEGA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.WtdVega > BAD_DOUBLE_VALUE, aPos.WtdVega, STR_NA)
'
'                            Case RPC_THETA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.ThetaInShares > BAD_DOUBLE_VALUE, aPos.ThetaInShares, STR_NA)
'
'                            Case RPC_RHO
'                                .TextMatrix(nRow, nCol) = IIf(aPos.RhoInShares > BAD_DOUBLE_VALUE, aPos.RhoInShares, STR_NA)
'
'                            Case RPC_THETA_DELTA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.ThetaDeltaInShares > BAD_DOUBLE_VALUE, aPos.ThetaDeltaInShares, STR_NA)
'
'                            Case RPC_THETA_GAMMA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.ThetaGammaInShares > BAD_DOUBLE_VALUE, aPos.ThetaGammaInShares, STR_NA)
'
'                            Case RPC_VEGA_DELTA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.VegaDeltaInShares > BAD_DOUBLE_VALUE, aPos.VegaDeltaInShares, STR_NA)
'
'                            Case RPC_VEGA_GAMMA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.VegaGammaInShares > BAD_DOUBLE_VALUE, aPos.VegaGammaInShares, STR_NA)
'
'                            Case RPC_TIME_VALUE
'                                .TextMatrix(nRow, nCol) = IIf(aPos.TimeValue > BAD_DOUBLE_VALUE, aPos.TimeValue, STR_NA)
'
''                            Case RPC_DELTAP
''                                .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Delta > BAD_DOUBLE_VALUE, aPos.Quote.Delta * 100, STR_NA)
''
''                            Case RPC_GAMMAP
''                                .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Gamma > BAD_DOUBLE_VALUE, aPos.Quote.Gamma * 100, STR_NA)
''
''                            Case RPC_VEGAP
''                                .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Vega > BAD_DOUBLE_VALUE, aPos.Quote.Vega * 100, STR_NA)
''
''                            Case RPC_THETAP
''                                .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Theta > BAD_DOUBLE_VALUE, aPos.Quote.Theta * 100, STR_NA)
''
''                            Case RPC_RHOP
''                                .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Rho > BAD_DOUBLE_VALUE, aPos.Quote.Rho * 100, STR_NA)
'
'                            'FIRST
''                            Case RPC_THEO_VOL
''                                .TextMatrix(nRow, nCol) = IIf(aPos.Vola > BAD_DOUBLE_VALUE, aPos.Vola * 100, STR_NA)
'
'                        End Select
'
'                    Case enCtFuture
'                        Select Case nIdx
'                            Case RPC_OPT_QTY, RPC_OPT_DELTA, RPC_GAMMA, RPC_NET_GAMMA, RPC_GAMMA_SHARES, _
'                                RPC_VEGA, RPC_WTD_VEGA, RPC_THETA, RPC_RHO, RPC_THETA_DELTA, RPC_THETA_GAMMA, _
'                                RPC_VEGA_DELTA, RPC_VEGA_GAMMA, RPC_TIME_VALUE
'                                .TextMatrix(nRow, nCol) = ""
'
'                            Case RPC_UND_POS
'                                .TextMatrix(nRow, nCol) = IIf(aPos.QtyInShares > BAD_LONG_VALUE, aPos.QtyInShares, STR_NA)
'
'                            Case RPC_FUT_QTY
'                                .TextMatrix(nRow, nCol) = IIf(aPos.Qty > BAD_LONG_VALUE, aPos.Qty, STR_NA)
'
'                        End Select
'
'                    Case enCtFutOption
'                        Select Case nIdx
'                            Case RPC_UND_POS, RPC_FUT_QTY, RPC_OPT_DELTA, RPC_GAMMA_SHARES, _
'                                 RPC_THETA_DELTA, RPC_THETA_GAMMA, RPC_VEGA_GAMMA, RPC_VEGA_DELTA, RPC_GAMMA, RPC_NET_GAMMA
'                                .TextMatrix(nRow, nCol) = ""
'
'                            Case RPC_OPT_QTY
'                                .TextMatrix(nRow, nCol) = IIf(aPos.Qty > BAD_LONG_VALUE, aPos.Qty, STR_NA)
'
'                            'Case RPC_OPT_DELTA
'                            '    .TextMatrix(nRow, nCol) = IIf(aPos.DeltaInShares > BAD_DOUBLE_VALUE, aPos.DeltaInShares, STR_NA)
'
'                            'Case RPC_GAMMA
'                            '    .TextMatrix(nRow, nCol) = IIf(aPos.GammaInSharesPerc > BAD_DOUBLE_VALUE, aPos.GammaInSharesPerc, STR_NA)
'
'                            'Case RPC_NET_GAMMA
'                            '    .TextMatrix(nRow, nCol) = IIf(aPos.NetGamma > BAD_DOUBLE_VALUE, aPos.NetGamma, STR_NA)
'
'                            'Case RPC_GAMMA_SHARES
'                            '    .TextMatrix(nRow, nCol) = IIf(aPos.GammaInShares > BAD_DOUBLE_VALUE, aPos.GammaInShares, STR_NA)
'
'                            Case RPC_VEGA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.VegaInShares > BAD_DOUBLE_VALUE, aPos.VegaInShares, STR_NA)
'
'                            Case RPC_WTD_VEGA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.WtdVega > BAD_DOUBLE_VALUE, aPos.WtdVega, STR_NA)
'
'                            Case RPC_THETA
'                                .TextMatrix(nRow, nCol) = IIf(aPos.ThetaInShares > BAD_DOUBLE_VALUE, aPos.ThetaInShares, STR_NA)
'
'                            Case RPC_RHO
'                                .TextMatrix(nRow, nCol) = IIf(aPos.RhoInShares > BAD_DOUBLE_VALUE, aPos.RhoInShares, STR_NA)
'
'                            'Case RPC_THETA_DELTA
'                            '    .TextMatrix(nRow, nCol) = IIf(aPos.ThetaDeltaInShares > BAD_DOUBLE_VALUE, aPos.ThetaDeltaInShares, STR_NA)
'
'                            'Case RPC_THETA_GAMMA
'                            '    .TextMatrix(nRow, nCol) = IIf(aPos.ThetaGammaInShares > BAD_DOUBLE_VALUE, aPos.ThetaGammaInShares, STR_NA)
'
'                            'Case RPC_VEGA_DELTA
'                            '    .TextMatrix(nRow, nCol) = IIf(aPos.VegaDeltaInShares > BAD_DOUBLE_VALUE, aPos.VegaDeltaInShares, STR_NA)
'
'                            'Case RPC_VEGA_GAMMA
'                            '    .TextMatrix(nRow, nCol) = IIf(aPos.VegaGammaInShares > BAD_DOUBLE_VALUE, aPos.VegaGammaInShares, STR_NA)
'
'                            Case RPC_TIME_VALUE
'                                .TextMatrix(nRow, nCol) = IIf(aPos.TimeValue > BAD_DOUBLE_VALUE, aPos.TimeValue, STR_NA)
'
'                            'Case RPC_DELTAP
'                            '        .TextMatrix(nRow, nCol) = IIf(aPos.Delta > BAD_DOUBLE_VALUE, aPos.Delta * 100, STR_NA)
'
'                            'Case RPC_GAMMAP
'                            '    .TextMatrix(nRow, nCol) = IIf(aPos.Gamma > BAD_DOUBLE_VALUE, aPos.Gamma * 100, STR_NA)
'
''                            Case RPC_VEGAP
''                                .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Vega > BAD_DOUBLE_VALUE, aPos.Quote.Vega * 100, STR_NA)
''
''                            Case RPC_THETAP
''                                .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Theta > BAD_DOUBLE_VALUE, aPos.Quote.Theta * 100, STR_NA)
''
''                            Case RPC_RHOP
''                                .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Rho > BAD_DOUBLE_VALUE, aPos.Quote.Rho * 100, STR_NA)
'
'
''                            Case RPC_FOPT_DELTA
''                                .TextMatrix(nRow, nCol) = IIf(aPos.DeltaInShares > BAD_DOUBLE_VALUE, aPos.DeltaInShares, STR_NA)
''
''                            Case RPC_FGAMMA_USD
''                                .TextMatrix(nRow, nCol) = IIf(aPos.GammaInShares > BAD_DOUBLE_VALUE, aPos.GammaInShares, STR_NA) 'GammaInShares
''
''                            Case RPC_FGAMMAP
''                                .TextMatrix(nRow, nCol) = IIf(aPos.Quote.Gamma > BAD_DOUBLE_VALUE, aPos.Quote.Gamma * 100, STR_NA)
''
''                            Case RPC_FTHETA_DELTA
''                                .TextMatrix(nRow, nCol) = IIf(aPos.ThetaDeltaInShares > BAD_DOUBLE_VALUE, aPos.ThetaDeltaInShares, STR_NA)
''
''                            Case RPC_FTHETA_GAMMA
''                                .TextMatrix(nRow, nCol) = IIf(aPos.ThetaGammaInShares > BAD_DOUBLE_VALUE, aPos.ThetaGammaInShares, STR_NA)
''
''                            Case RPC_FVEGA_DELTA
''                                .TextMatrix(nRow, nCol) = IIf(aPos.VegaDeltaInShares > BAD_DOUBLE_VALUE, aPos.VegaDeltaInShares, STR_NA)
''
''                            Case RPC_FVEGA_GAMMA
''                                .TextMatrix(nRow, nCol) = IIf(aPos.VegaGammaInShares > BAD_DOUBLE_VALUE, aPos.VegaGammaInShares, STR_NA)
''
''                            Case RPC_FINDEX_DELTA_EQ
''                                .TextMatrix(nRow, nCol) = ""
'
'
'                            'SECOND
''                            Case RPC_THEO_VOL
''                                .TextMatrix(nRow, nCol) = IIf(aPos.Vola > BAD_DOUBLE_VALUE, aPos.Vola * 100, STR_NA)
'
'                        End Select
'
'                    Case Else 'underlying
'                        Select Case nIdx
'                            Case RPC_UND_POS
'                                .TextMatrix(nRow, nCol) = IIf(aPos.QtyInShares > BAD_LONG_VALUE, aPos.QtyInShares, STR_NA)
'
'                            Case RPC_OPT_QTY, RPC_OPT_DELTA, RPC_GAMMA, RPC_VEGA, RPC_WTD_VEGA, _
'                                RPC_THETA, RPC_RHO, RPC_THETA_DELTA, RPC_THETA_GAMMA, RPC_VEGA_DELTA, _
'                                RPC_VEGA_GAMMA, RPC_TIME_VALUE, RPC_FUT_QTY
'                                .TextMatrix(nRow, nCol) = ""
'                        End Select
'
'                End Select
'
'                i = i + 1
'                nIdx = gdPos.Idx(i)
'            Wend
'
'            m_Aux.GridLock(GT_RISKS_POSITIONS).UnlockRedraw
'        End If
'Ex:
'        Set aUnd = Nothing
'        Set aPos = Nothing
'    End With
'End Sub
'
'Public Sub UnderlyingUpdate(ByVal nRow&, ByVal bSymbol As Boolean, Optional ByVal bRealTimeUpdate As Boolean = False)
'    On Error Resume Next
'    Dim nCol&, aUnd As EtsMmRisksLib.MmRvUndAtom, aRowData As EtsMmRisksLib.MmRvRowData
'
'    With fgPos
'        'Set aRowData = .RowData(nRow)
'        Set aRowData = m_Aux.RiskView.PosRowData(nRow)
'        Set aUnd = aRowData.Und
'        If Not aUnd Is Nothing Then
'
'            If bRealTimeUpdate Then
'                If Not aUnd.CalcGreeks And Not aUnd.CalcTotals And Not m_Aux.Idx.CalcTotals Then GoTo Ex
'            End If
'
'            m_Aux.GridLock(GT_RISKS_POSITIONS).LockRedraw
'
'            Dim i&, nIdx&
'            i = 0
'            nIdx = gdPos.Idx(0)
'            While nIdx >= 0 And i <= RPC_LAST_COLUMN
'                nCol = i + 1
'
'                If bSymbol Then
'                    Select Case nIdx
'                        Case RPC_SYMBOL
'                            .TextMatrix(nRow, nCol) = aUnd.Symbol
'
'                        Case RPC_OPT_TYPE, RPC_EXPIRY, RPC_STRIKE, RPC_UND, _
'                            RPC_DEL_UNIT, RPC_FUT_ROOT, RPC_FUTURES, RPC_FUT_MATURITY
'                            .TextMatrix(nRow, nCol) = ""
'                    End Select
'                End If
'
'                Select Case aUnd.ContractType
'                    Case enCtIndex, enCtStock, enCtOption, enCtFuture, enCtFutOption, enCtFutRoot  ' all except enCtFutUnd
'                        Select Case nIdx
'                            Case RPC_NETCHANGE
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Price.NetChange <> BAD_DOUBLE_VALUE, aUnd.Price.NetChange, STR_NA)
'                            Case RPC_BID
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Price.Bid > BAD_DOUBLE_VALUE, aUnd.Price.Bid, STR_NA)
'
'                                If aUnd.ReplacePriceStatus And enRpsBid Then
'                                    Set .Cell(flexcpPicture, nRow, nCol) = imgBadPrice.Picture
'                                    .Cell(flexcpPictureAlignment, nRow, nCol) = flexPicAlignLeftCenter
'                                Else
'                                    Set .Cell(flexcpPicture, nRow, nCol) = Nothing
'                                End If
'
'                            Case RPC_ASK
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Price.Ask > BAD_DOUBLE_VALUE, aUnd.Price.Ask, STR_NA)
'
'                                If aUnd.ReplacePriceStatus And enRpsAsk Then
'                                    Set .Cell(flexcpPicture, nRow, nCol) = imgBadPrice.Picture
'                                    .Cell(flexcpPictureAlignment, nRow, nCol) = flexPicAlignLeftCenter
'                                Else
'                                    Set .Cell(flexcpPicture, nRow, nCol) = Nothing
'                                End If
'
'                            Case RPC_LAST
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Price.Last > BAD_DOUBLE_VALUE, aUnd.Price.Last, STR_NA)
'
'                            Case RPC_CLOSE
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Price.Close > 0#, aUnd.Price.Close, STR_NA)
'
'                            Case RPC_UND_POS
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Qty > BAD_LONG_VALUE, aUnd.Qty, STR_NA)
'
'                            Case RPC_OPT_QTY
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.OptQty > BAD_LONG_VALUE, aUnd.OptQty, STR_NA)
'
'                            Case RPC_PNL_MTM
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.PnlMtm > BAD_DOUBLE_VALUE, aUnd.PnlMtm, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadPnlMtm, gdPos.Col(RPC_PNL_MTM).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_PNL_MTM).ForeColor)
'
'                            Case RPC_PNL_THEO
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.PnlTheo > BAD_DOUBLE_VALUE, aUnd.PnlTheo, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadPnlTheo, gdPos.Col(RPC_PNL_THEO).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_PNL_THEO).ForeColor)
'
'                            Case RPC_PNL_EDGE
'                                If aUnd.PnlTheo > BAD_DOUBLE_VALUE And aUnd.PnlMtm > BAD_DOUBLE_VALUE Then
'                                    .TextMatrix(nRow, nCol) = aUnd.PnlTheo - aUnd.PnlMtm
'                                Else
'                                    .TextMatrix(nRow, nCol) = STR_NA
'                                End If
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadPnlMtm Or aUnd.BadPnlTheo, gdPos.Col(RPC_PNL_EDGE).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_PNL_EDGE).ForeColor)
'
'                            Case RPC_NET_DELTA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.NetDelta > BAD_DOUBLE_VALUE, aUnd.NetDelta, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadNetDelta, gdPos.Col(RPC_NET_DELTA).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_NET_DELTA).ForeColor)
'
'                            Case RPC_NET_DELTA_USD
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.DeltaEq > BAD_DOUBLE_VALUE, aUnd.DeltaEq, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadDeltaEq, gdPos.Col(RPC_NET_DELTA_USD).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_NET_DELTA_USD).ForeColor)
'
'                            Case RPC_OPT_DELTA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.OptDelta > BAD_DOUBLE_VALUE, aUnd.OptDelta, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadOptDelta, gdPos.Col(RPC_OPT_DELTA).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_OPT_DELTA).ForeColor)
'
'                            Case RPC_GAMMA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.GammaPerc > BAD_DOUBLE_VALUE, aUnd.GammaPerc, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadGammaPerc, gdPos.Col(RPC_GAMMA).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_GAMMA).ForeColor)
'
'                            Case RPC_NET_GAMMA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.NetGamma > BAD_DOUBLE_VALUE, aUnd.NetGamma, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadNetGamma, gdPos.Col(RPC_NET_GAMMA).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_NET_GAMMA).ForeColor)
'
'                            Case RPC_GAMMA_SHARES
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Gamma > BAD_DOUBLE_VALUE, aUnd.Gamma, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadGamma, gdPos.Col(RPC_GAMMA_SHARES).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_GAMMA_SHARES).ForeColor)
'
'                            Case RPC_VEGA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Vega > BAD_DOUBLE_VALUE, aUnd.Vega, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadVega, gdPos.Col(RPC_VEGA).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_VEGA).ForeColor)
'
'                            Case RPC_WTD_VEGA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.WtdVega > BAD_DOUBLE_VALUE, aUnd.WtdVega, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadWtdVega, gdPos.Col(RPC_WTD_VEGA).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_WTD_VEGA).ForeColor)
'
'                            Case RPC_THETA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Theta > BAD_DOUBLE_VALUE, aUnd.Theta, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadTheta, gdPos.Col(RPC_THETA).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_THETA).ForeColor)
'
'                            Case RPC_RHO
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Rho > BAD_DOUBLE_VALUE, aUnd.Rho, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadRho, gdPos.Col(RPC_RHO).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_RHO).ForeColor)
'
'                            Case RPC_THETA_DELTA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.ThetaDelta > BAD_DOUBLE_VALUE, aUnd.ThetaDelta, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadThetaDelta, gdPos.Col(RPC_THETA_DELTA).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_THETA_DELTA).ForeColor)
'
'                            Case RPC_THETA_GAMMA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.ThetaGamma > BAD_DOUBLE_VALUE, aUnd.ThetaGamma, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadThetaGamma, gdPos.Col(RPC_THETA_GAMMA).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_THETA_GAMMA).ForeColor)
'
'                            Case RPC_VEGA_DELTA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.VegaDelta > BAD_DOUBLE_VALUE, aUnd.VegaDelta, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadVegaDelta, gdPos.Col(RPC_VEGA_DELTA).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_VEGA_DELTA).ForeColor)
'
'                            Case RPC_VEGA_GAMMA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.VegaGamma > BAD_DOUBLE_VALUE, aUnd.VegaGamma, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadVegaGamma, gdPos.Col(RPC_VEGA_GAMMA).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_VEGA_GAMMA).ForeColor)
'
'                            Case RPC_TIME_VALUE
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.TimeValue > BAD_DOUBLE_VALUE, aUnd.TimeValue, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadTimeValue, gdPos.Col(RPC_TIME_VALUE).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_TIME_VALUE).ForeColor)
'
'                            Case RPC_BETA_WTD_DELTA_USD
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.BetaWtdDeltaEq > BAD_DOUBLE_VALUE, aUnd.BetaWtdDeltaEq, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadBetaWtdDeltaEq, gdPos.Col(RPC_BETA_WTD_DELTA_USD).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_BETA_WTD_DELTA_USD).ForeColor)
'
'                            Case RPC_FUT_QTY
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.FutQty > BAD_LONG_VALUE, aUnd.FutQty, STR_NA)
'                        End Select
'
'                    Case enCtFutUnd
'                        Select Case nIdx
'                            Case RPC_NETCHANGE
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Price.NetChange <> BAD_DOUBLE_VALUE, aUnd.Price.NetChange, STR_NA)
'                            Case RPC_BID
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Price.Bid > BAD_DOUBLE_VALUE, aUnd.Price.Bid, STR_NA)
'
'                                If aUnd.ReplacePriceStatus And enRpsBid Then
'                                    Set .Cell(flexcpPicture, nRow, nCol) = imgBadPrice.Picture
'                                    .Cell(flexcpPictureAlignment, nRow, nCol) = flexPicAlignLeftCenter
'                                Else
'                                    Set .Cell(flexcpPicture, nRow, nCol) = Nothing
'                                End If
'
'                            Case RPC_ASK
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Price.Ask > BAD_DOUBLE_VALUE, aUnd.Price.Ask, STR_NA)
'
'                                If aUnd.ReplacePriceStatus And enRpsAsk Then
'                                    Set .Cell(flexcpPicture, nRow, nCol) = imgBadPrice.Picture
'                                    .Cell(flexcpPictureAlignment, nRow, nCol) = flexPicAlignLeftCenter
'                                Else
'                                    Set .Cell(flexcpPicture, nRow, nCol) = Nothing
'                                End If
'
'                            Case RPC_LAST
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Price.Last > BAD_DOUBLE_VALUE, aUnd.Price.Last, STR_NA)
'
'                            Case RPC_CLOSE
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Price.Close > 0#, aUnd.Price.Close, STR_NA)
'
'                            Case RPC_UND_POS
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Qty > BAD_LONG_VALUE, aUnd.Qty, STR_NA)
'
'                            Case RPC_OPT_QTY
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.OptQty > BAD_LONG_VALUE, aUnd.OptQty, STR_NA)
'
'                            Case RPC_PNL_MTM
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.PnlMtm > BAD_DOUBLE_VALUE, aUnd.PnlMtm, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadPnlMtm, gdPos.Col(RPC_PNL_MTM).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_PNL_MTM).ForeColor)
'
'                            Case RPC_PNL_THEO
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.PnlTheo > BAD_DOUBLE_VALUE, aUnd.PnlTheo, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadPnlTheo, gdPos.Col(RPC_PNL_THEO).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_PNL_THEO).ForeColor)
'
'                            Case RPC_PNL_EDGE
'                                If aUnd.PnlTheo > BAD_DOUBLE_VALUE And aUnd.PnlMtm > BAD_DOUBLE_VALUE Then
'                                    .TextMatrix(nRow, nCol) = aUnd.PnlTheo - aUnd.PnlMtm
'                                Else
'                                    .TextMatrix(nRow, nCol) = STR_NA
'                                End If
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadPnlMtm Or aUnd.BadPnlTheo, gdPos.Col(RPC_PNL_EDGE).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_PNL_EDGE).ForeColor)
'
'                            Case RPC_NET_DELTA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.NetDelta > BAD_DOUBLE_VALUE, aUnd.NetDelta, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadNetDelta, gdPos.Col(RPC_NET_DELTA).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_NET_DELTA).ForeColor)
'
'                            Case RPC_NET_DELTA_USD
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.DeltaEq > BAD_DOUBLE_VALUE, aUnd.DeltaEq, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadDeltaEq, gdPos.Col(RPC_NET_DELTA_USD).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_NET_DELTA_USD).ForeColor)
'
''                            Case RPC_FOPT_DELTA ' RPC_OPT_DELTA
''                                .TextMatrix(nRow, nCol) = IIf(aUnd.OptDelta > BAD_DOUBLE_VALUE, aUnd.OptDelta, STR_NA)
''                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadOptDelta, gdPos.Col(RPC_OPT_DELTA).ForeColorAlt1, _
''                                                                                        gdPos.Col(RPC_OPT_DELTA).ForeColor)
'
''                            Case RPC_FGAMMAP 'RPC_GAMMA
''                                .TextMatrix(nRow, nCol) = IIf(aUnd.GammaPerc > BAD_DOUBLE_VALUE, aUnd.GammaPerc, STR_NA)
''                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadGammaPerc, gdPos.Col(RPC_GAMMA).ForeColorAlt1, _
''                                                                                        gdPos.Col(RPC_GAMMA).ForeColor)
'
'                            Case RPC_NET_GAMMA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.NetGamma > BAD_DOUBLE_VALUE, aUnd.NetGamma, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadNetGamma, gdPos.Col(RPC_NET_GAMMA).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_NET_GAMMA).ForeColor)
'
''                            Case RPC_FGAMMA_USD 'RPC_GAMMA_SHARES
''                                .TextMatrix(nRow, nCol) = IIf(aUnd.Gamma > BAD_DOUBLE_VALUE, aUnd.Gamma, STR_NA)
''                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadGamma, gdPos.Col(RPC_GAMMA_SHARES).ForeColorAlt1, _
''                                                                                        gdPos.Col(RPC_GAMMA_SHARES).ForeColor)
'
'                            Case RPC_VEGA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Vega > BAD_DOUBLE_VALUE, aUnd.Vega, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadVega, gdPos.Col(RPC_VEGA).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_VEGA).ForeColor)
'
'                            Case RPC_WTD_VEGA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.WtdVega > BAD_DOUBLE_VALUE, aUnd.WtdVega, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadWtdVega, gdPos.Col(RPC_WTD_VEGA).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_WTD_VEGA).ForeColor)
'
'                            Case RPC_THETA
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Theta > BAD_DOUBLE_VALUE, aUnd.Theta, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadTheta, gdPos.Col(RPC_THETA).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_THETA).ForeColor)
'
'                            Case RPC_RHO
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Rho > BAD_DOUBLE_VALUE, aUnd.Rho, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadRho, gdPos.Col(RPC_RHO).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_RHO).ForeColor)
'
''                            Case RPC_FTHETA_DELTA 'RPC_THETA_DELTA
''                                .TextMatrix(nRow, nCol) = IIf(aUnd.ThetaDelta > BAD_DOUBLE_VALUE, aUnd.ThetaDelta, STR_NA)
''                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadThetaDelta, gdPos.Col(RPC_THETA_DELTA).ForeColorAlt1, _
''                                                                                    gdPos.Col(RPC_THETA_DELTA).ForeColor)
''
''                            Case RPC_FTHETA_GAMMA 'RPC_THETA_GAMMA
''                                .TextMatrix(nRow, nCol) = IIf(aUnd.ThetaGamma > BAD_DOUBLE_VALUE, aUnd.ThetaGamma, STR_NA)
''                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadThetaGamma, gdPos.Col(RPC_THETA_GAMMA).ForeColorAlt1, _
''                                                                                    gdPos.Col(RPC_THETA_GAMMA).ForeColor)
''
''                            Case RPC_FVEGA_DELTA 'RPC_VEGA_DELTA
''                                .TextMatrix(nRow, nCol) = IIf(aUnd.VegaDelta > BAD_DOUBLE_VALUE, aUnd.VegaDelta, STR_NA)
''                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadVegaDelta, gdPos.Col(RPC_VEGA_DELTA).ForeColorAlt1, _
''                                                                                    gdPos.Col(RPC_VEGA_DELTA).ForeColor)
''
''                            Case RPC_FVEGA_GAMMA 'RPC_VEGA_GAMMA
''                                .TextMatrix(nRow, nCol) = IIf(aUnd.VegaGamma > BAD_DOUBLE_VALUE, aUnd.VegaGamma, STR_NA)
''                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadVegaGamma, gdPos.Col(RPC_VEGA_GAMMA).ForeColorAlt1, _
''                                                                                    gdPos.Col(RPC_VEGA_GAMMA).ForeColor)
'
'                            Case RPC_TIME_VALUE
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.TimeValue > BAD_DOUBLE_VALUE, aUnd.TimeValue, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadTimeValue, gdPos.Col(RPC_TIME_VALUE).ForeColorAlt1, _
'                                                                                    gdPos.Col(RPC_TIME_VALUE).ForeColor)
'
'                            Case RPC_BETA_WTD_DELTA_USD
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.BetaWtdDeltaEq > BAD_DOUBLE_VALUE, aUnd.BetaWtdDeltaEq, STR_NA)
'                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadBetaWtdDeltaEq, gdPos.Col(RPC_BETA_WTD_DELTA_USD).ForeColorAlt1, _
'                                                                                        gdPos.Col(RPC_BETA_WTD_DELTA_USD).ForeColor)
'
'                            Case RPC_FUT_QTY
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.FutQty > BAD_LONG_VALUE, aUnd.FutQty, STR_NA)
''                            Case RPC_SYNTHETIC_PRICE
''                                 .TextMatrix(nRow, nCol) = IIf(aUnd.SuPrice > BAD_DOUBLE_VALUE, aUnd.SuPrice, STR_NA)
'
'                            Case RPC_CLOSE
'                                .TextMatrix(nRow, nCol) = IIf(aUnd.Price.Close >= 0#, aUnd.Price.Close, STR_NA)
'
'                        End Select
'
'                End Select
'
'                i = i + 1
'                nIdx = gdPos.Idx(i)
'            Wend
'
'            m_Aux.GridLock(GT_RISKS_POSITIONS).UnlockRedraw
'        End If
'
'Ex:
'        Set aUnd = Nothing
'        Set aRowData = Nothing
'    End With
'End Sub

Public Sub UnderlyingUpdateBadStatus(ByVal nRow&)
    On Error Resume Next
    Dim nCol&, aUnd As EtsMmRisksLib.MmRvUndAtom, aRowData As EtsMmRisksLib.MmRvRowData

    With fgPos
        m_Aux.GridLock(GT_RISKS_POSITIONS).LockRedraw
    
        'Set aRowData = .RowData(nRow)
        Set aRowData = m_Aux.RiskView.PosRowData(nRow)
        If Not aRowData.Und Is Nothing Then
            Set aUnd = aRowData.Und
            
            Dim i&, nIdx&
            i = 0
            nIdx = gdPos.Idx(0)
            While nIdx >= 0 And i <= RPC_LAST_COLUMN
                nCol = i + 1
            
                Select Case nIdx
                    Case RPC_PNL_MTM
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadPnlMtm, gdPos.Col(RPC_PNL_MTM).ForeColorAlt1, _
                                                                                gdPos.Col(RPC_PNL_MTM).ForeColor)
                    
                    Case RPC_PNL_THEO
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadPnlTheo, gdPos.Col(RPC_PNL_THEO).ForeColorAlt1, _
                                                                                gdPos.Col(RPC_PNL_THEO).ForeColor)
            
                    Case RPC_PNL_EDGE
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadPnlMtm Or aUnd.BadPnlTheo, gdPos.Col(RPC_PNL_EDGE).ForeColorAlt1, _
                                                                                gdPos.Col(RPC_PNL_EDGE).ForeColor)
            
                    Case RPC_NET_DELTA
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadNetDelta, gdPos.Col(RPC_NET_DELTA).ForeColorAlt1, _
                                                                                gdPos.Col(RPC_NET_DELTA).ForeColor)
            
                    Case RPC_NET_DELTA_USD
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadDeltaEq, gdPos.Col(RPC_NET_DELTA_USD).ForeColorAlt1, _
                                                                                gdPos.Col(RPC_NET_DELTA_USD).ForeColor)
                    Case RPC_NET_EXPOSURE
                        Dim aAgg As IMmRvAggregationDataAtom
                        Set aAgg = aUnd
                        
                       .Cell(flexcpForeColor, nRow, nCol) = IIf(aAgg.BadNetExposure, gdPos.Col(RPC_NET_EXPOSURE).ForeColorAlt1, _
                                                                              gdPos.Col(RPC_NET_EXPOSURE).ForeColor)
            
                    Case RPC_OPT_DELTA
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadOptDelta, gdPos.Col(RPC_OPT_DELTA).ForeColorAlt1, _
                                                                                gdPos.Col(RPC_OPT_DELTA).ForeColor)
            
                    Case RPC_GAMMA
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadGammaPerc, gdPos.Col(RPC_GAMMA).ForeColorAlt1, _
                                                                                gdPos.Col(RPC_GAMMA).ForeColor)
                    
                    Case RPC_NET_GAMMA
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadNetGamma, gdPos.Col(RPC_NET_GAMMA).ForeColorAlt1, _
                                                                                gdPos.Col(RPC_NET_GAMMA).ForeColor)
            
            
                    Case RPC_GAMMA_SHARES
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadGamma, gdPos.Col(RPC_GAMMA_SHARES).ForeColorAlt1, _
                                                                                gdPos.Col(RPC_GAMMA_SHARES).ForeColor)
            
                    Case RPC_VEGA
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadVega, gdPos.Col(RPC_VEGA).ForeColorAlt1, _
                                                                            gdPos.Col(RPC_VEGA).ForeColor)
        
                    Case RPC_WTD_VEGA
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadWtdVega, gdPos.Col(RPC_WTD_VEGA).ForeColorAlt1, _
                                                                            gdPos.Col(RPC_WTD_VEGA).ForeColor)
            
                    Case RPC_THETA
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadTheta, gdPos.Col(RPC_THETA).ForeColorAlt1, _
                                                                            gdPos.Col(RPC_THETA).ForeColor)
            
                    Case RPC_RHO
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadRho, gdPos.Col(RPC_RHO).ForeColorAlt1, _
                                                                            gdPos.Col(RPC_RHO).ForeColor)
            
                    Case RPC_THETA_DELTA
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadThetaDelta, gdPos.Col(RPC_THETA_DELTA).ForeColorAlt1, _
                                                                            gdPos.Col(RPC_THETA_DELTA).ForeColor)
            
                    Case RPC_THETA_GAMMA
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadThetaGamma, gdPos.Col(RPC_THETA_GAMMA).ForeColorAlt1, _
                                                                            gdPos.Col(RPC_THETA_GAMMA).ForeColor)
            
                    Case RPC_VEGA_DELTA
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadVegaDelta, gdPos.Col(RPC_VEGA_DELTA).ForeColorAlt1, _
                                                                            gdPos.Col(RPC_VEGA_DELTA).ForeColor)
            
                    Case RPC_VEGA_GAMMA
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadVegaGamma, gdPos.Col(RPC_VEGA_GAMMA).ForeColorAlt1, _
                                                                            gdPos.Col(RPC_VEGA_GAMMA).ForeColor)
            
                    Case RPC_TIME_VALUE
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadTimeValue, gdPos.Col(RPC_TIME_VALUE).ForeColorAlt1, _
                                                                            gdPos.Col(RPC_TIME_VALUE).ForeColor)
            
                    Case RPC_BETA_WTD_DELTA_USD
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadBetaWtdDeltaEq, gdPos.Col(RPC_BETA_WTD_DELTA_USD).ForeColorAlt1, _
                                                                                gdPos.Col(RPC_BETA_WTD_DELTA_USD).ForeColor)
                End Select
    
                i = i + 1
                nIdx = gdPos.Idx(i)
            Wend
            
            Set aUnd = Nothing
        End If
        
        m_Aux.GridLock(GT_RISKS_POSITIONS).UnlockRedraw
    End With
End Sub

Public Sub SyntheticGreeksUpdate(ByVal nRow&, ByVal bSymbol As Boolean)
    On Error Resume Next
    Dim nCol&, bUpdateOptSymbol As Boolean: bUpdateOptSymbol = False
    Dim bUpdateSynth As Boolean: bUpdateSynth = False
    Dim aUnd As EtsMmRisksLib.MmRvUndAtom, aPos As EtsMmRisksLib.MmRvPosAtom
    Dim aRowData As EtsMmRisksLib.MmRvRowData, aSynthUnd As EtsMmRisksLib.MmRvUndAtom
    Dim aSynthGreek As EtsMmRisksLib.MmRvSynthGreeksAtom

    With fgPos
        Set aRowData = .RowData(nRow) 'm_Aux.RiskView.PosRowData(nRow)
        
        If Not aRowData Is Nothing And Not aRowData.SynthGreeks Is Nothing And Not aRowData.Und Is Nothing Then
                
            Set aSynthGreek = aRowData.SynthGreeks
            Set aUnd = aRowData.Und
            Set aPos = aRowData.Pos
            m_Aux.GridLock(GT_RISKS_POSITIONS).LockRedraw
            
            If bSymbol Then bUpdateOptSymbol = (aPos.ContractType = enCtOption)
            
            Set aSynthUnd = m_Aux.Und(aSynthGreek.SynthUndID)
            bUpdateSynth = aSynthGreek.IsTotal And Not aSynthUnd Is Nothing
            
            Dim i&, nIdx&
            i = 0
            nIdx = gdPos.Idx(0)
            While nIdx >= 0 And i <= RPC_LAST_COLUMN
                nCol = i + 1
            
                If bSymbol Then
                    If bUpdateOptSymbol Then
                        Select Case nIdx
                            Case RPC_SYMBOL
                                .TextMatrix(nRow, nCol) = aSynthGreek.Symbol
                            
                            Case RPC_OPT_TYPE
                                .TextMatrix(nRow, nCol) = IIf(aPos.OptType = enOtCall, "C", "P")
                            
                            Case RPC_EXPIRY
                                .TextMatrix(nRow, nCol) = aPos.Expiry
                            
                            Case RPC_STRIKE
                                .TextMatrix(nRow, nCol) = IIf(aPos.Strike > BAD_DOUBLE_VALUE, aPos.Strike, STR_NA)
                            
                            Case RPC_UND
                                .TextMatrix(nRow, nCol) = aSynthGreek.SynthUndSymbol
                            
                            Case RPC_DEL_UNIT
                                .TextMatrix(nRow, nCol) = aSynthGreek.DeliveryUnits
                                
                            Case RPC_FUT_ROOT, RPC_FUTURES, RPC_FUT_MATURITY
                                .TextMatrix(nRow, nCol) = ""
                        End Select
                    Else
                        Select Case nIdx
                            Case RPC_SYMBOL
                                .TextMatrix(nRow, nCol) = aSynthGreek.Symbol
                            
                            Case RPC_OPT_TYPE, RPC_EXPIRY, RPC_STRIKE, RPC_UND, RPC_DEL_UNIT, _
                                RPC_FUT_ROOT, RPC_FUTURES, RPC_FUT_MATURITY
                                .TextMatrix(nRow, nCol) = ""
                        End Select
                    End If
                End If
                
                If bUpdateSynth Then
                    Select Case nIdx
                        Case RPC_NETCHANGE
                            .TextMatrix(nRow, nCol) = IIf(aSynthUnd.Price.NetChange <> BAD_DOUBLE_VALUE, aSynthUnd.Price.NetChange, STR_NA)
                        Case RPC_BID
                            .TextMatrix(nRow, nCol) = IIf(aSynthUnd.Price.Bid > BAD_DOUBLE_VALUE, aSynthUnd.Price.Bid, STR_NA)
                            
                            If aSynthUnd.ReplacePriceStatus And enRpsBid Then
                                Set .Cell(flexcpPicture, nRow, nCol) = imgBadPrice.Picture
                                .Cell(flexcpPictureAlignment, nRow, nCol) = flexPicAlignLeftCenter
                            Else
                                If Not .Cell(flexcpPicture, nRow, nCol) Is Nothing Then
                                    Set .Cell(flexcpPicture, nRow, nCol) = Nothing
                                End If
                            End If
                    
                        Case RPC_ASK
                            .TextMatrix(nRow, nCol) = IIf(aSynthUnd.Price.Ask > BAD_DOUBLE_VALUE, aSynthUnd.Price.Ask, STR_NA)
                            
                            If aSynthUnd.ReplacePriceStatus And enRpsAsk Then
                                Set .Cell(flexcpPicture, nRow, nCol) = imgBadPrice.Picture
                                .Cell(flexcpPictureAlignment, nRow, nCol) = flexPicAlignLeftCenter
                            Else
                                If Not .Cell(flexcpPicture, nRow, nCol) Is Nothing Then
                                    Set .Cell(flexcpPicture, nRow, nCol) = Nothing
                                End If
                            End If
                    
                        Case RPC_LAST
                            .TextMatrix(nRow, nCol) = IIf(aSynthUnd.Price.Last > BAD_DOUBLE_VALUE, aSynthUnd.Price.Last, STR_NA)
                    
'                        Case RPC_SYNTHETIC_PRICE
'                            .TextMatrix(nRow, nCol) = IIf(aSynthGreek.SuPrice > BAD_DOUBLE_VALUE, aSynthGreek.SuPrice, STR_NA)
                    
                        Case RPC_CLOSE
                            .TextMatrix(nRow, nCol) = IIf(aSynthUnd.Price.Close > 0#, aSynthUnd.Price.Close, STR_NA)
                    End Select
                Else
                    Select Case nIdx
                        Case RPC_NETCHANGE, RPC_BID, RPC_ASK, RPC_LAST, RPC_CLOSE
                            .TextMatrix(nRow, nCol) = ""
'                        Case RPC_SYNTHETIC_PRICE
'                            .TextMatrix(nRow, nCol) = IIf(aSynthGreek.SuPrice > BAD_DOUBLE_VALUE, aSynthGreek.SuPrice, STR_NA)
                    End Select
                End If
                
                Select Case nIdx
                    Case RPC_PNL_MTM, RPC_PNL_THEO, RPC_PNL_EDGE, RPC_UND_POS, RPC_OPT_QTY, _
                        RPC_VEGA, RPC_WTD_VEGA, RPC_THETA, RPC_RHO, RPC_THETA_DELTA, RPC_THETA_GAMMA, _
                        RPC_VEGA_DELTA, RPC_VEGA_GAMMA, RPC_TIME_VALUE, RPC_FUT_QTY
                        .TextMatrix(nRow, nCol) = ""
                                                
                    Case RPC_NET_DELTA
                        If Not aPos Is Nothing Then
                            If aPos.ContractType = enCtOption Then
                                .TextMatrix(nRow, nCol) = ""
                            Else
                                .TextMatrix(nRow, nCol) = IIf(aSynthGreek.DeltaInShares > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInShares, STR_NA)
                                If aSynthGreek.IsTotal Then _
                                    .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadDelta, gdPos.Col(RPC_NET_DELTA).ForeColorAlt1, _
                                    gdPos.Col(RPC_NET_DELTA).ForeColor)
                            End If
                        Else
                            .TextMatrix(nRow, nCol) = IIf(aSynthGreek.DeltaInShares > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInShares, STR_NA)
                            If aSynthGreek.IsTotal Then _
                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadDelta, gdPos.Col(RPC_NET_DELTA).ForeColorAlt1, _
                                 gdPos.Col(RPC_NET_DELTA).ForeColor)
                        End If
                            
                    Case RPC_NET_DELTA_USD
                        If Not aPos Is Nothing Then
                            If aPos.ContractType = enCtOption Then
                                .TextMatrix(nRow, nCol) = ""
                            Else
                                .TextMatrix(nRow, nCol) = IIf(aSynthGreek.DeltaInMoney > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInMoney, STR_NA)
                                If aSynthGreek.IsTotal Then _
                                    .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadDeltaInMoney, gdPos.Col(RPC_NET_DELTA_USD).ForeColorAlt1, _
                                    gdPos.Col(RPC_NET_DELTA_USD).ForeColor)
                            End If
                        Else
                            .TextMatrix(nRow, nCol) = IIf(aSynthGreek.DeltaInMoney > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInMoney, STR_NA)
                            If aSynthGreek.IsTotal Then _
                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadDeltaInMoney, gdPos.Col(RPC_NET_DELTA_USD).ForeColorAlt1, _
                                 gdPos.Col(RPC_NET_DELTA_USD).ForeColor)
                        End If
                            
                    Case RPC_OPT_DELTA
                        .TextMatrix(nRow, nCol) = IIf(aSynthGreek.DeltaInShares > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInShares, STR_NA)
                        If aSynthGreek.IsTotal Then _
                            .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadDelta, gdPos.Col(RPC_OPT_DELTA).ForeColorAlt1, _
                                                        gdPos.Col(RPC_OPT_DELTA).ForeColor)
                
                    Case RPC_GAMMA
                        .TextMatrix(nRow, nCol) = IIf(aSynthGreek.GammaInSharesPerc > BAD_DOUBLE_VALUE, aSynthGreek.GammaInSharesPerc, STR_NA)
                        If aSynthGreek.IsTotal Then _
                            .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadGammaPerc, gdPos.Col(RPC_GAMMA).ForeColorAlt1, _
                                                        gdPos.Col(RPC_GAMMA).ForeColor)
    
                    Case RPC_NET_GAMMA
                        .TextMatrix(nRow, nCol) = IIf(aSynthGreek.NetGamma > BAD_DOUBLE_VALUE, aSynthGreek.NetGamma, STR_NA)
                        If aSynthGreek.IsTotal Then _
                            .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadNetGamma, gdPos.Col(RPC_NET_GAMMA).ForeColorAlt1, _
                                                        gdPos.Col(RPC_NET_GAMMA).ForeColor)
                    
                    Case RPC_GAMMA_SHARES
                        .TextMatrix(nRow, nCol) = IIf(aSynthGreek.GammaInShares > BAD_DOUBLE_VALUE, aSynthGreek.GammaInShares, STR_NA)
                        If aSynthGreek.IsTotal Then _
                            .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadGamma, gdPos.Col(RPC_GAMMA_SHARES).ForeColorAlt1, _
                                                        gdPos.Col(RPC_GAMMA_SHARES).ForeColor)
                
                    Case RPC_BETA_WTD_DELTA_USD
                        If Not aPos Is Nothing Then
                            If aPos.ContractType = enCtOption Then
                                .TextMatrix(nRow, nCol) = ""
                            Else
                                .TextMatrix(nRow, nCol) = IIf(aSynthGreek.BetaWtdDeltaInMoney > BAD_DOUBLE_VALUE, aSynthGreek.BetaWtdDeltaInMoney, STR_NA)
                                If aSynthGreek.IsTotal Then _
                                    .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadBetaWtdDeltaInMoney, gdPos.Col(RPC_BETA_WTD_DELTA_USD).ForeColorAlt1, _
                                    gdPos.Col(RPC_BETA_WTD_DELTA_USD).ForeColor)
                            End If
                        Else
                            .TextMatrix(nRow, nCol) = IIf(aSynthGreek.BetaWtdDeltaInMoney > BAD_DOUBLE_VALUE, aSynthGreek.BetaWtdDeltaInMoney, STR_NA)
                            If aSynthGreek.IsTotal Then _
                                .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadBetaWtdDeltaInMoney, gdPos.Col(RPC_BETA_WTD_DELTA_USD).ForeColorAlt1, _
                                 gdPos.Col(RPC_BETA_WTD_DELTA_USD).ForeColor)
                        End If
                End Select
    
                i = i + 1
                nIdx = gdPos.Idx(i)
            Wend
                        
            Set aSynthUnd = Nothing
            
            m_Aux.GridLock(GT_RISKS_POSITIONS).UnlockRedraw
        End If
        Set aUnd = Nothing
        Set aPos = Nothing
        Set aRowData = Nothing
    End With
End Sub

Public Sub TotalsUpdate()
    On Error Resume Next
    Dim nCol&

    With fgTot
        m_Aux.GridLock(GT_RISKS_TOTALS).LockRedraw
        
        Dim i&, nIdx&
        i = 0
        nIdx = gdTot.Idx(0)
        While nIdx >= 0 And i <= RTC_LAST_COLUMN
            nCol = i
            Select Case nIdx
                Case RTC_PNL_MTM
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.PnlMtm > BAD_DOUBLE_VALUE, m_Aux.Grp.PnlMtm, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadPnlMtm, gdTot.Col(RTC_PNL_MTM).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_PNL_MTM).ForeColor)
        
                Case RTC_PNL_THEO
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.PnlTheo > BAD_DOUBLE_VALUE, m_Aux.Grp.PnlTheo, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadPnlTheo, gdTot.Col(RTC_PNL_THEO).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_PNL_THEO).ForeColor)
        
                Case RTC_PNL_EDGE
                    If m_Aux.Grp.PnlTheo > BAD_DOUBLE_VALUE And m_Aux.Grp.PnlMtm > BAD_DOUBLE_VALUE Then
                        .TextMatrix(1, nCol) = m_Aux.Grp.PnlTheo - m_Aux.Grp.PnlMtm
                    Else
                        .TextMatrix(1, nCol) = STR_NA
                    End If
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadPnlMtm Or m_Aux.Grp.BadPnlTheo, gdTot.Col(RTC_PNL_EDGE).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_PNL_EDGE).ForeColor)
            
                Case RTC_VEGA
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.Vega > BAD_DOUBLE_VALUE, m_Aux.Grp.Vega, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadVega, gdTot.Col(RTC_VEGA).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_VEGA).ForeColor)
        
                Case RTC_WTD_VEGA
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.WtdVega > BAD_DOUBLE_VALUE, m_Aux.Grp.WtdVega, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadWtdVega, gdTot.Col(RTC_WTD_VEGA).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_WTD_VEGA).ForeColor)
        
                Case RTC_THETA
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.Theta > BAD_DOUBLE_VALUE, m_Aux.Grp.Theta, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadTheta, gdTot.Col(RTC_THETA).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_THETA).ForeColor)
        
                Case RTC_DELTA_EQ
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.DeltaEq > BAD_DOUBLE_VALUE, m_Aux.Grp.DeltaEq, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadDeltaEq, gdTot.Col(RTC_DELTA_EQ).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_DELTA_EQ).ForeColor)
        
                Case RTC_GAMMA_EQ
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.NetGammaEq > BAD_DOUBLE_VALUE, m_Aux.Grp.NetGammaEq, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadNetGammaEq, gdTot.Col(RTC_GAMMA_EQ).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_GAMMA_EQ).ForeColor)
        
                Case RTC_RHO
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.Rho > BAD_DOUBLE_VALUE, m_Aux.Grp.Rho, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadRho, gdTot.Col(RTC_RHO).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_RHO).ForeColor)
        
                Case RTC_INDEX_DELTA_EQ
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.IdxDeltaEq > BAD_DOUBLE_VALUE, m_Aux.Grp.IdxDeltaEq, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadIdxDeltaEq, gdTot.Col(RTC_INDEX_DELTA_EQ).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_INDEX_DELTA_EQ).ForeColor)
        
                Case RTC_BETA_WTD_DELTA
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.BetaWtdDelta > BAD_DOUBLE_VALUE, m_Aux.Grp.BetaWtdDelta, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadBetaWtdDelta, gdTot.Col(RTC_BETA_WTD_DELTA).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_BETA_WTD_DELTA).ForeColor)
        
                Case RTC_OPT_DELTA
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.OptDelta > BAD_DOUBLE_VALUE, m_Aux.Grp.OptDelta, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadOptDelta, gdTot.Col(RTC_OPT_DELTA).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_OPT_DELTA).ForeColor)
        
'                Case RTC_NET_DELTA
'                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.NetDelta > BAD_DOUBLE_VALUE, m_Aux.Grp.NetDelta, STR_NA)
'                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadNetDelta, gdTot.Col(RTC_NET_DELTA).ForeColorAlt1, _
'                                                                            gdTot.Col(RTC_NET_DELTA).ForeColor)
'
'                Case RTC_NET_GAMMA
'                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.NetGamma > BAD_DOUBLE_VALUE, m_Aux.Grp.NetGamma, STR_NA)
'                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadNetGamma, gdTot.Col(RTC_NET_GAMMA).ForeColorAlt1, _
'                                                                            gdTot.Col(RTC_NET_GAMMA).ForeColor)
        
                Case RTC_BETA_WTD_DELTA_USD
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.BetaWtdDeltaEq > BAD_DOUBLE_VALUE, m_Aux.Grp.BetaWtdDeltaEq, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadBetaWtdDeltaEq, gdTot.Col(RTC_BETA_WTD_DELTA_USD).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_BETA_WTD_DELTA_USD).ForeColor)
                                                                            
            Case RTC_NET_EXPOSURE_LONG
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.NetExposureLong > BAD_DOUBLE_VALUE, m_Aux.Grp.NetExposureLong, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadNetExposure, gdTot.Col(RTC_NET_EXPOSURE_LONG).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_NET_EXPOSURE_LONG).ForeColor)
            Case RTC_NET_EXPOSURE_SHORT
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.NetExposureShort > BAD_DOUBLE_VALUE, m_Aux.Grp.NetExposureShort, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadNetExposure, gdTot.Col(RTC_NET_EXPOSURE_SHORT).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_NET_EXPOSURE_SHORT).ForeColor)
            Case RTC_NET_EXPOSURE
                    .TextMatrix(1, nCol) = IIf(m_Aux.Grp.NetExposure > BAD_DOUBLE_VALUE, m_Aux.Grp.NetExposure, STR_NA)
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadNetExposure, gdTot.Col(RTC_NET_EXPOSURE).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_NET_EXPOSURE).ForeColor)
                                                                            
            End Select

            i = i + 1
            nIdx = gdTot.Idx(i)
        Wend
        
        .AutoSize 0, .Cols - 1
        
        m_Aux.GridLock(GT_RISKS_TOTALS).UnlockRedraw
    End With
End Sub

Public Sub TotalsUpdateBadStatus()
    On Error Resume Next
    Dim nCol&

    With fgTot
        m_Aux.GridLock(GT_RISKS_TOTALS).LockRedraw
        
        Dim i&, nIdx&
        i = 0
        nIdx = gdTot.Idx(0)
        While nIdx >= 0 And i <= RTC_LAST_COLUMN
            nCol = i
            Select Case nIdx
                Case RTC_PNL_MTM
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadPnlMtm, gdTot.Col(RTC_PNL_MTM).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_PNL_MTM).ForeColor)
        
                Case RTC_PNL_THEO
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadPnlTheo, gdTot.Col(RTC_PNL_THEO).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_PNL_THEO).ForeColor)
        
                Case RTC_PNL_EDGE
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadPnlMtm Or m_Aux.Grp.BadPnlTheo, gdTot.Col(RTC_PNL_EDGE).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_PNL_EDGE).ForeColor)
            
                Case RTC_VEGA
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadVega, gdTot.Col(RTC_VEGA).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_VEGA).ForeColor)
        
                Case RTC_WTD_VEGA
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadWtdVega, gdTot.Col(RTC_WTD_VEGA).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_WTD_VEGA).ForeColor)
        
                Case RTC_THETA
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadTheta, gdTot.Col(RTC_THETA).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_THETA).ForeColor)
        
                Case RTC_DELTA_EQ
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadDeltaEq, gdTot.Col(RTC_DELTA_EQ).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_DELTA_EQ).ForeColor)
        
                Case RTC_GAMMA_EQ
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadNetGammaEq, gdTot.Col(RTC_GAMMA_EQ).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_GAMMA_EQ).ForeColor)
        
                Case RTC_RHO
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadRho, gdTot.Col(RTC_RHO).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_RHO).ForeColor)
        
                Case RTC_INDEX_DELTA_EQ
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadIdxDeltaEq, gdTot.Col(RTC_INDEX_DELTA_EQ).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_INDEX_DELTA_EQ).ForeColor)
        
                Case RTC_BETA_WTD_DELTA
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadBetaWtdDelta, gdTot.Col(RTC_BETA_WTD_DELTA).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_BETA_WTD_DELTA).ForeColor)
        
                Case RTC_OPT_DELTA
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadOptDelta, gdTot.Col(RTC_OPT_DELTA).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_OPT_DELTA).ForeColor)
        
'                Case RTC_NET_DELTA
'                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadNetDelta, gdTot.Col(RTC_NET_DELTA).ForeColorAlt1, _
'                                                                            gdTot.Col(RTC_NET_DELTA).ForeColor)
'
'                Case RTC_NET_GAMMA
'                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadNetGamma, gdTot.Col(RTC_NET_GAMMA).ForeColorAlt1, _
'                                                                            gdTot.Col(RTC_NET_GAMMA).ForeColor)
        
                Case RTC_BETA_WTD_DELTA_USD
                    .Cell(flexcpForeColor, 1, nCol) = IIf(m_Aux.Grp.BadBetaWtdDeltaEq, gdTot.Col(RTC_BETA_WTD_DELTA_USD).ForeColorAlt1, _
                                                                            gdTot.Col(RTC_BETA_WTD_DELTA_USD).ForeColor)
            End Select

            i = i + 1
            nIdx = gdTot.Idx(i)
        Wend
        
        m_Aux.GridLock(GT_RISKS_TOTALS).UnlockRedraw
    End With
End Sub



