VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Flex options close prices"
   ClientHeight    =   8805
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4470
   BeginProperty Font 
      Name            =   "Courier"
      Size            =   9.75
      Charset         =   204
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   8805
   ScaleWidth      =   4470
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox tbLog 
      Height          =   7455
      Left            =   0
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   3
      Top             =   480
      Width           =   4455
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Close"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1200
      TabIndex        =   0
      Top             =   8160
      Width           =   1935
   End
   Begin VB.Label lblUndTotal 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3120
      TabIndex        =   2
      Top             =   120
      Width           =   1335
   End
   Begin VB.Label lblUnd 
      Caption         =   "Underlyings with flex options found"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   2775
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private m_nNewGrpID&
Public Grp As EtsMmQuotesLib.MmQvGrpAtom
Public QuoteReqsAll As clsQvRequestColl
Public CustRates As New clsEntityColl
Public m_bDataLoad As Boolean
Private WithEvents VolaSource As VolatilitySourcesLib.VolatilitySource
Attribute VolaSource.VB_VarHelpID = -1


'Public m_frmOwner As Form
Private Sub Command1_Click()
   End
End Sub
Private Function InitGroup(ByVal nGroupID As Long) As Boolean
    On Error GoTo EH
    Dim aContract As EtsGeneralLib.EtsContractAtom

    InitGroup = False
    
    If m_bInProc Then Exit Function
    
    Set aContract = g_ContractAll(nGroupID)
    If aContract Is Nothing Then Exit Function
    
    m_bDataLoad = True
    m_bInProc = True
    
    m_nUndQuotesCount = 0
    m_nOptQuotesCount = 0
    m_nFutQuotesCount = 0

    'pbProgress.Min = 0
    'pbProgress.Value = pbProgress.Min
    DoEvents
    
    Grp.ID = aContract.ID
    Grp.ContractType = aContract.ContractType
    Grp.Symbol = aContract.Symbol
    'AdjustCaption
    AdjustState
    
    InitUnderlying aContract
    DoEvents
    If Not m_bDataLoad Then GoTo EX

    InitContracts aContract
    DoEvents
    If Not m_bDataLoad Then GoTo EX

    'If Not InitGroupExchanges Then GoTo EX
    
    InitContractsQuotes aContract

    Select Case aContract.ContractType
        Case enCtIndex, enCtStock
            If Not InitUnderlyingOptions(aContract) Then GoTo EX
            
'        Case enCtFuture
'            If Not InitFuturesOptions(aContract) Then GoTo EX
        
        Case Else
            GoTo EX
    End Select
    
    'UnderlyingUpdatePositions
    UnderlyingAdjustRates True

    InitGroup = True
EX:
    m_bInProc = False
    m_bDataLoad = False
    Set aContract = Nothing
    Exit Function
EH:
    If Not m_bShutDown Then gCmn.ErrorMsgBox Me, "Fail to load underlying."
    GoTo EX
End Function

Private Sub AdjustState()
    On Error Resume Next
    
'    Dim aExpColl As EtsMmQuotesLib.MmQvExpColl
'    If Grp.IsStockOrIndex Then
'         Set aExpColl = Grp.Und.Exp
'    Else
'         Set aExpColl = Grp.Fut.Exp
'     End If
'
    'fgVol.ColHidden(QVC_VOLA_VAL + aExpColl.Count) =  RealTime
    'If  RealTime Then
    '   fgVol.TextMatrix(1, QVC_VOLA_VAL + aExpColl.Count) = Now
    '    dtCalculationDate.Value = Now
    'End If
   
   ' UpdateMenu
   ' RaiseEvent OnStateChange
End Sub
Private Sub InitUnderlying(ByRef aContract As EtsGeneralLib.EtsContractAtom)
    On Error Resume Next
    Dim aIdx As EtsGeneralLib.IndexAtom, sKey$
    
    If Grp.ID = 0 Then Exit Sub
    
     Grp.Und.ID = aContract.Und.ID
     Grp.Und.Symbol = aContract.Und.Symbol
     Grp.Und.SymbolName = aContract.Und.ContractName
     Grp.Und.UndType = aContract.Und.UndType
     Grp.Und.IsTraderContract = aContract.Und.IsTraderContract
    
    InitVola Grp.Und
    
     Grp.Und.IsHTB = aContract.Und.IsHTB
     'Grp.Und.ExpCalendarID = aContract.Und.ExpCalendarID
    
     Grp.Und.Skew = aContract.Und.Skew
     Grp.Und.Kurt = aContract.Und.Kurt
    
    Set Grp.Und.UndPriceProfile = aContract.Und.UndPriceProfile
    Set Grp.Und.OptPriceProfile = aContract.Und.OptPriceProfile
    
     Grp.Und.UndPosForRates = 0#
    
    If IsAmerican < 0 Then
         Grp.Und.IsAmerican = aContract.Und.IsAmerican
    Else
         Grp.Und.IsAmerican = (IsAmerican <> 0)
    End If
    
     Grp.UseCustRates = UseCustRates
    
    If aContract.Und.UndType = enCtStock Then
        Set Grp.Und.Dividend = aContract.Und.Dividend
        
        If Grp.Und.Dividend.DivDate = 0 Then Grp.Und.Dividend.DivDate = Date
        If Grp.Und.Dividend.DivDateCust = 0 Then Grp.Und.Dividend.DivDateCust = Date
        
    Else
         Grp.Und.Yield = aContract.Und.Yield
        Set Grp.Und.BasketIndex = Nothing
        Set Grp.Und.Dividend = Nothing
        
        Set aIdx = g_Index(Grp.Und.ID)
        If Not aIdx Is Nothing Then
            If aIdx.IsBasket Then
                Set Grp.Und.BasketIndex = aIdx
            End If
            Set aIdx = Nothing
        End If
    End If
    
     Grp.Und.Quote.Clear
     Grp.Und.Exp.Clear
     Grp.Und.OptRoot.Clear

    Set aIdx = Nothing
End Sub

Private Sub InitContracts(ByRef aContract As EtsGeneralLib.EtsContractAtom)
    On Error Resume Next
    Dim sKey$
    
    If Grp.ID = 0 Then Exit Sub
    
'    If aContract.ContractType = enCtFuture Then
'         Grp.FutRoot.ID = aContract.FutRoot.ID
'         Grp.FutRoot.Symbol = aContract.FutRoot.Symbol
'         Grp.FutRoot.Name = aContract.FutRoot.Name
'         Grp.FutRoot.MatCalendarID = aContract.FutRoot.MatCalendarID
'         Grp.FutRoot.FutLotSize = aContract.FutRoot.FutLotSize
'         Grp.FutRoot.OptLotSize = aContract.FutRoot.OptLotSize
'
'         Grp.Fut.ID = aContract.Fut.ID
'         Grp.Fut.Symbol = aContract.Fut.Symbol
'         Grp.Fut.ContractName = aContract.Fut.ContractName
'         Grp.Fut.FutRootID = aContract.FutRoot.ID
'         Grp.Fut.ExpCalendarID = aContract.Fut.ExpCalendarID
'        Set Grp.Fut.UndPriceProfile = aContract.Fut.UndPriceProfile
'        Set Grp.Fut.OptPriceProfile = aContract.Fut.OptPriceProfile
'         Grp.Fut.MaturityDate = aContract.Fut.MaturityDate
'         Grp.Fut.MaturityMonth = DateSerial(Year(aContract.Fut.MaturityDate), Month(aContract.Fut.MaturityDate), 1)
'         Grp.Fut.IsAmerican = aContract.Fut.IsAmerican
'
'         Grp.Fut.Quote.Clear
'         Grp.Fut.Exp.Clear
'    End If
End Sub

Private Sub InitContractsQuotes(ByRef aContract As EtsGeneralLib.EtsContractAtom)
    On Error Resume Next
    Dim sKey$, aExch As EtsGeneralLib.ExchAtom
    Dim aReq As clsQvRequestAtom, aQuote As EtsMmQuotesLib.MmQvQuoteAtom
    
    If Grp.ID = 0 Then Exit Sub
    
    For Each aExch In Grp.Und.UndExch

        Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
        Set aQuote.Exch = aExch
        aQuote.LotSize = aContract.Und.LotSize

        sKey = Grp.Und.Symbol
        If aExch.ID <> 0 Then
            sKey = sKey & "." & aExch.Code
        End If

        Set aReq = QuoteReqsAll(sKey)
        If aReq Is Nothing Then
            Set aReq = QuoteReqsAll.Add(sKey)
            Set aReq.Exch = aExch
            Set aReq.Und = Grp.Und
        End If
        Set aReq = Nothing

         Grp.Und.Quote.Add aExch.ID, aExch.Code, aQuote
        Set aQuote = Nothing
    Next
    
    m_nUndQuotesCount = Grp.Und.UndExch.Count

    If aContract.ContractType = enCtFuture Then
        For Each aExch In Grp.UndExchAll
            If aExch.ID = 0 Then
                Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
                Set aQuote.Exch = aExch
                aQuote.LotSize = aContract.FutRoot.FutLotSize
        
                sKey = aContract.Symbol
                If aExch.ID <> 0 Then
                    sKey = sKey & "." & aExch.Code
                End If
        
                Set aReq = QuoteReqsAll(sKey)
                If aReq Is Nothing Then
                    Set aReq = QuoteReqsAll.Add(sKey)
                    Set aReq.Exch = aExch
                    Set aReq.Und = Grp.Und
                    'Set aReq.Fut = Grp.Fut
                    'Set aReq.FutRoot = Grp.FutRoot
                End If
                Set aReq = Nothing
        
                 Grp.Und.Quote.Add aExch.ID, aExch.Code, aQuote
                Set aQuote = Nothing
            End If
        Next
    
        m_nFutQuotesCount = 1
    End If
End Sub

Private Function InitUnderlyingOptions(ByRef aContract As EtsGeneralLib.EtsContractAtom) As Boolean
    On Error GoTo EH
    Dim rsOpt As ADODB.Recordset, aExch As EtsGeneralLib.ExchAtom, rsExch As ADODB.Recordset
    Dim dtExpiry As Date, dStrike#, dtExpiryMonth As Date, sRoot$, aRoot As EtsMmQuotesLib.MmQvOptRootAtom, aPair As EtsMmQuotesLib.MmQvOptPairAtom
    Dim aQuote As EtsMmQuotesLib.MmQvQuoteAtom, enOptType As EtsGeneralLib.EtsOptionTypeEnum, sKey$, aEnt As clsEntityAtom
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, aStr As EtsMmQuotesLib.MmQvStrikeAtom, aOpt As EtsMmQuotesLib.MmQvOptAtom
    Dim nID&, nOptRootID&, aGUnd As EtsGeneralLib.UndAtom, aSyntRootComp As EtsGeneralLib.SynthRootCompAtom
    Dim aUnd As EtsMmQuotesLib.MmQvUndAtom, aSynthRoot As EtsGeneralLib.SynthRootAtom
    Dim aStrAll As EtsMmQuotesLib.MmQvStrikeAtom, aReq As clsQvRequestAtom, aExpAll As EtsMmQuotesLib.MmQvExpAtom
    
    InitUnderlyingOptions = False
    If Grp.ID = 0 Then Exit Function
            
    Set rsOpt = gDBW.usp_FlexOptionByUnderlying_Get(Grp.ID, Date)
    'If rsOpt.RecordCount > 0 Then pbProgress.Max = rsOpt.RecordCount
    DoEvents
    If Not m_bDataLoad Then GoTo EX
    
    Do While Not rsOpt.EOF
        dtExpiry = ReadDate(rsOpt!dtExpiry)
        dtExpiryMonth = DateSerial(Year(dtExpiry), Month(dtExpiry), Day(dtExpiry))

        Set aExp = Grp.Und.Exp(dtExpiryMonth)
        If aExp Is Nothing Then
            Set aExp = Grp.Und.Exp.Add(dtExpiryMonth)
            aExp.Expiry = dtExpiry
            aExp.ExpiryMonth = dtExpiryMonth
            aExp.Visible = True
            
'            Set aEnt = CustRates(CStr(CLng(aExp.ExpiryMonth)))
'            If Not aEnt Is Nothing Then
'                aExp.RateCust = aEnt.Data3
'                Set aEnt = Nothing
'            End If
        End If

        nOptRootID = ReadLng(rsOpt!iOptionRootID)
        
        Set aRoot = Grp.Und.OptRoot(nOptRootID)
        If aRoot Is Nothing Then
            Set aRoot = New EtsMmQuotesLib.MmQvOptRootAtom
            aRoot.ID = nOptRootID
            
            aRoot.Name = ReadStr(rsOpt!vcOptionRootSymbol)
            aRoot.LotSize = ReadLng(rsOpt!iLotSize)
            aRoot.IsFit = IIf(ReadLng(rsOpt!tiIsFitEnabled) <> 0, True, False)
            ' Sharky: unnecessary code. just for ensure not zero lot
            If aRoot.LotSize <= 0 Then aRoot.LotSize = 100
            
            If aContract.Und.HaveSyntheticRoots Then
                Set aSynthRoot = aContract.Und.SyntheticRoots(nOptRootID)
            End If
            
            aRoot.Synthetic = Not aSynthRoot Is Nothing
                
            If aRoot.Synthetic Then
                Set aRoot.SynthOptRoot = aSynthRoot
                Dim dDPC As Double
                dDPC = aRoot.LotSize * aSynthRoot.CashValue
                If dDPC <> 0# Then _
                    aRoot.DPC = Trim$(Str$(aRoot.LotSize * aSynthRoot.CashValue)) & " USD"
                                                           
                If aSynthRoot.CashValue > 0# Then
                    If Grp.Und.SynthUnd Is Nothing Then Set Grp.Und.SynthUnd = New EtsMmQuotesLib.MmQvUndColl
                
                    If Grp.Und.SynthUnd(USD_ID) Is Nothing Then
                        Set aUnd = New EtsMmQuotesLib.MmQvUndAtom
                        aUnd.ID = USD_ID
                        aUnd.Symbol = USD_SYMBOL
                        aUnd.SymbolName = USD_SYMBOL
                        aUnd.UndType = enCtStock
                        
                        aUnd.OptRoot.Add aRoot.ID, aRoot.Name, aRoot
                        
                        Set aExch = AddExch(aUnd.UndExch, 0, "", "<Primary>")
                        
                        Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
                        Set aQuote.Exch = aExch
                        aQuote.LotSize = aRoot.LotSize
                        aQuote.PriceAsk = 1#
                        aQuote.PriceBid = 1#
                        aQuote.PriceLast = 1#
                                        
                        aUnd.Quote.Add aExch.ID, aExch.Code, aQuote
                        Set aQuote = Nothing
                        Set aExch = Nothing
                                                    
                         Grp.Und.SynthUnd.Add USD_ID, USD_SYMBOL, aUnd
                        Set aUnd = Nothing
                    End If
                End If
                                  
                For Each aSyntRootComp In aSynthRoot.SynthRootComponents
                    Set aGUnd = g_UnderlyingAll(aSyntRootComp.UndID)
                    
                    If Not aGUnd Is Nothing Then
                        aRoot.DPC = aRoot.DPC & IIf(Len(aRoot.DPC) > 0, " + ", "") & Trim$(Str$(aRoot.LotSize * aSyntRootComp.Weight)) & " " & aGUnd.Symbol
                                            
                        If aSyntRootComp.UndID <> Grp.Und.ID Then
                        
                            If Grp.Und.SynthUnd Is Nothing Then Set Grp.Und.SynthUnd = New EtsMmQuotesLib.MmQvUndColl
                            
                            If Grp.Und.SynthUnd(aSyntRootComp.UndID) Is Nothing Then
                                Set aUnd = New EtsMmQuotesLib.MmQvUndAtom
                                aUnd.ID = aSyntRootComp.UndID
                                aUnd.Symbol = aGUnd.Symbol
                                aUnd.SymbolName = aGUnd.ContractName
                                aUnd.UndType = aGUnd.UndType
                                
                                aUnd.OptRoot.Add aRoot.ID, aRoot.Name, aRoot
                                
                                AddExch aUnd.UndExch, 0, "", "<Primary>"
                                
                                Set rsExch = gDBW.usp_MmUnderlyingExchanges_Get(aSyntRootComp.UndID)
                                Do While Not rsExch.EOF
                                    nID = ReadLng(rsExch!iExchangeId)
                                    Set aExch = g_Exch(nID)
                                    
                                    If Not aExch Is Nothing Then
                                        If ReadByte(rsExch!tiIsUnderlying) <> 0 Then
                                            If Grp.UndExchAll(nID) Is Nothing Then AddExch Grp.UndExchAll, nID, aExch.Code, aExch.Name
                                            If aUnd.UndExch(nID) Is Nothing Then AddExch aUnd.UndExch, nID, aExch.Code, aExch.Name
                                        End If
                                        Set aExch = Nothing
                                    End If
                                    
                                    DoEvents
                                    If Not m_bDataLoad Then GoTo EX
                                    rsExch.MoveNext
                                Loop
                                Set rsExch = Nothing
                                
                                For Each aExch In aUnd.UndExch
                        
                                    Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
                                    Set aQuote.Exch = aExch
                                    aQuote.LotSize = aRoot.LotSize
                        
                                    sKey = aGUnd.Symbol
                                    If aExch.ID <> 0 Then
                                        sKey = sKey & "." & aExch.Code
                                    End If
                        
                                    Set aReq = QuoteReqsAll(sKey)
                                    If aReq Is Nothing Then
                                        Set aReq = QuoteReqsAll.Add(sKey)
                                        Set aReq.Exch = aExch
                                        Set aReq.Und = aUnd
                                    End If
                                    Set aReq = Nothing
                        
                                    aUnd.Quote.Add aExch.ID, aExch.Code, aQuote
                                    Set aQuote = Nothing
                                Next
                                
                                m_nUndQuotesCount = m_nUndQuotesCount + aUnd.UndExch.Count
                                
                                 Grp.Und.SynthUnd.Add aSyntRootComp.UndID, aGUnd.Symbol, aUnd
                                Set aUnd = Nothing
                            End If
                        End If
                        Set aGUnd = Nothing
                    End If
                Next
            Else
                aRoot.DPC = Trim$(Str$(aRoot.LotSize)) + " " + Grp.Und.Symbol
            End If
        
            aRoot.Visible = True
             Grp.Und.OptRoot.Add aRoot.ID, aRoot.Name, aRoot
        End If
        Set aSynthRoot = Nothing

        Set aExpAll = Grp.ExpAll(dtExpiryMonth)
        If aExpAll Is Nothing Then
            Set aExpAll = Grp.ExpAll.Add(dtExpiryMonth)
            aExpAll.Expiry = dtExpiry
            aExpAll.ExpiryMonth = dtExpiryMonth
            aExpAll.Visible = True
        End If
        
        If InStr(aExpAll.RootNames, aRoot.Name) = 0 Then
            If Len(aExpAll.RootNames) > 0 Then
                aExpAll.RootNames = aExpAll.RootNames & "," & aRoot.Name
            Else
                aExpAll.RootNames = aRoot.Name
            End If
        End If

        Set aExpAll = Nothing

        dStrike = Round(ReadDbl(rsOpt!fStrike), STRIKE_DECIMALS_COUNT)
        
        Set aStr = aExp.Strike(dStrike)
        If aStr Is Nothing Then
            Set aStr = aExp.Strike.Add(dStrike)
            aStr.Strike = dStrike
            aStr.Visible = True
        End If
        
        Set aStrAll = Grp.StrikeAll(dStrike)
        If aStrAll Is Nothing Then
            Set aStrAll = Grp.StrikeAll.Add(dStrike)
            aStrAll.Strike = dStrike
            aStrAll.Visible = True
        End If
        Set aStrAll = Nothing
        
        Set aPair = aStr.OptPair(aRoot.ID)
        If aPair Is Nothing Then
            Set aPair = New EtsMmQuotesLib.MmQvOptPairAtom
            aPair.RootID = aRoot.ID
            
            aStr.OptPair.Add aRoot.ID, aRoot.Name, aPair
        End If

        enOptType = IIf(ReadLng(rsOpt!tiIsCall) <> 0, enOtCall, enOtPut)
        
        Set aOpt = aPair.Opt(enOptType)
        If aOpt.ID = 0 Then
            aOpt.ID = ReadLng(rsOpt!iContractID)
            aOpt.Symbol = ReadStr(rsOpt!vcSymbol)
            aOpt.OptType = enOptType
            aOpt.Expiry = dtExpiry
            aOpt.Strike = dStrike
            aOpt.RootID = aPair.RootID
            
            aOpt.Vola = Grp.Und.VolaSrv.OptionVola(dtExpiry, dStrike)

            If aOpt.Vola < 0 Then
                aOpt.Vola = BAD_DOUBLE_VALUE
            End If

             Grp.Und.Opt.Add aOpt.ID, aOpt
        End If

        'For Each aExch In Grp.Und.OptExch
            Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
            Set aExch = g_Exch(nID)
            Set aQuote.Exch = aExch
            aQuote.LotSize = aRoot.LotSize
            
            If Int(aOpt.Strike) = aOpt.Strike Then
                aQuote.Series = UCase$(Format$(aOpt.Expiry, "YYMMM")) & Trim$(Str$(Int(aOpt.Strike)))
            Else
                aQuote.Series = UCase$(Format$(aOpt.Expiry, "YYMMM")) & Trim$(Format$(aOpt.Strike, "##,##.#0"))
            End If
            
            sKey = aOpt.Symbol
            
            'If aExch.ID = 0 Then
                Set aOpt.DefQuote = aQuote
            'Else
            '    aQuote.Series = aQuote.Series & " " & aExch.Code
            '    sKey = sKey & "." & aExch.Code
            'End If
            
            'Set aReq = QuoteReqsAll(sKey)
            'If aReq Is Nothing Then
            '    Set aReq = QuoteReqsAll.Add(sKey)
            '    Set aReq.Exch = aExch
            '    Set aReq.Opt = aOpt
            '    Set aReq.Exp = aExp
            'End If
            'Set aReq = Nothing
            
            aOpt.Quote.Add 0, "", aQuote
            Set aQuote = Nothing
       ' Next

        DoEvents
        If Not m_bDataLoad Then GoTo EX
        'IncProgress pbProgress

        Set aOpt = Nothing
        Set aPair = Nothing
        Set aRoot = Nothing
        Set aUnd = Nothing
        Set aSyntRootComp = Nothing
        
        rsOpt.MoveNext
    Loop
    
    m_nOptQuotesCount = Grp.Und.Opt.Count * Grp.Und.OptExch.Count
    
    InitUnderlyingOptions = True
EX:
    Set aGUnd = Nothing
    Set aPair = Nothing
    Set aRoot = Nothing
    Set aExp = Nothing
    Set aQuote = Nothing
    Set rsOpt = Nothing
    Set rsExch = Nothing
    Set aExch = Nothing
    Set aSynthRoot = Nothing
    Set aSyntRootComp = Nothing
    Exit Function
EH:
    'If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to load underlying."
    GoTo EX
End Function


Private Function UnderlyingAdjustRates(ByVal bForceUpdateCustom As Boolean) As Boolean
    On Error Resume Next
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, bUseMidRates As Boolean, cPosThreshold@, dPos#
    Dim bForceRateUpdate As Boolean, aExpColl As EtsMmQuotesLib.MmQvExpColl
    
    UnderlyingAdjustRates = False
    If Grp.ID = 0 Then Exit Function
    
    bForceRateUpdate = False
    
    dPos = g_UnderlyingAll(Grp.Und.ID).UndPosForRates
    
    If GetIrRuleType = enRateBasedOnPosition Then
        cPosThreshold = Abs(GetPosThreshold)
        bUseMidRates = (cPosThreshold = 0 Or cPosThreshold <> 0 And Abs(dPos) <= cPosThreshold)
    
        If Not bUseMidRates Then _
            bForceRateUpdate = (Sgn(dPos) * Sgn(Grp.Und.UndPosForRates) < 0)
    
    Else
        bUseMidRates = True
    End If
    
    If bForceUpdateCustom Or Grp.Und.UseMidRates <> bUseMidRates Or bForceRateUpdate Then
         Grp.Und.UseMidRates = bUseMidRates
         Grp.Und.UndPosForRates = dPos
        
        Set aExpColl = Grp.ExpAll
        
        For Each aExp In aExpColl
            If bUseMidRates Then
                If Not Grp.Und.IsHTB Then
                    aExp.Rate = GetNeutralRate(Date, aExp.Expiry)
                Else
                    aExp.Rate = GetNeutralHTBRate(Date, aExp.Expiry)
                End If
            Else
                If Not Grp.Und.IsHTB Then
                    aExp.Rate = IIf(dPos < 0#, GetShortRate(Date, aExp.Expiry), GetLongRate(Date, aExp.Expiry))
                Else
                    aExp.Rate = IIf(dPos < 0#, GetHTBRate(Date, aExp.Expiry), GetLongRate(Date, aExp.Expiry))
                End If
            End If
            
            If bForceUpdateCustom Or Not Grp.UseCustRates Then
                If CustRates(CStr(CLng(aExp.ExpiryMonth))) Is Nothing Then
                    aExp.RateCust = aExp.Rate
                End If
            End If
        Next
        
        UnderlyingAdjustRates = True
    End If
End Function


Private Sub InitVola(ByRef aUnd As EtsMmQuotesLib.MmQvUndAtom)
    On Error GoTo EH
    aUnd.VolaSrv.Init aUnd.Symbol, aUnd.UndType, VolaSource
    Exit Sub
EH:
    LogEvent EVENT_WARNING, "Fail to init volatility for '" & aUnd.Symbol & "': " & Err.Description
End Sub
Private Function AddExch(ByRef aExchColl As EtsGeneralLib.ExchColl, ByVal nID As Long, ByVal sCode As String, ByVal sName As String) As EtsGeneralLib.ExchAtom
    On Error GoTo EH
    Dim aExch As EtsGeneralLib.ExchAtom
    Set AddExch = Nothing
    
    Set aExch = New EtsGeneralLib.ExchAtom
    aExch.ID = nID
    aExch.Code = sCode
    aExch.Name = sName
    aExchColl.Add aExch.ID, aExch.Code, aExch
    Set AddExch = aExch
EX:
    Set aExch = Nothing
    Exit Function
EH:
    Set AddExch = Nothing
    gCmn.ErrorHandler "Fail to add exchange."
    GoTo EX
End Function

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
    Set VolaSource = aVolaSources.VolatilitySource(g_Params.VolatilitySourceType)
    vmDB.ConnectionString = g_Params.DbConnection

    Set VolaSource.DataSource = vmDB
    VolaSource.EnableEvents = True
    VolaSource.EnableEditing = True

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



Private Sub Form_Load()
    Dim Und(), Clp()
    Dim rsOpt As ADODB.Recordset
    Dim uc&, ucb&
    Dim sKey$
    Dim aReq As clsQvRequestAtom
    Dim aParam As PRICEPROVIDERSLib.QuoteUpdateParams
    Dim aExch As EtsGeneralLib.ExchAtom
    On Error GoTo EH
    uc& = 0
    ucb& = 0
    Set rsOpt = gDBW.usp_UnderlyingsWithFlexOptions_Get()
    lblUndTotal.Caption = Str(rsOpt.RecordCount)
    
    If Not rsOpt.RecordCount > 0 Then Exit Sub
    
    ReDim Und(0 To rsOpt.RecordCount - 1)
    ReDim Clp(0 To rsOpt.RecordCount - 1)
    Do While Not rsOpt.EOF
         dbl = ReadDbl(rsOpt!PriceClose)
         If dbl <> 0# Then
            Clp(uc) = dbl
            Und(uc) = ReadStr(rsOpt!ContractID)
            uc = uc + 1
         Else
            ucb = ucb + 1
         End If
         rsOpt.MoveNext
    Loop
    lblUndTotal.Caption = Str(rsOpt.RecordCount) + " (" + Str(ucb) + " bad)"
    Set Grp = New EtsMmQuotesLib.MmQvGrpAtom
    Set QuoteReqsAll = New clsQvRequestColl
    InitVolaSources True
    uc = 0
    For Each u In Und
        
        InitGroup (u)
        If Grp.Und.Symbol <> "" Then
        tbLog.Text = tbLog.Text + Grp.Und.Symbol + " (" + Trim(Str(Grp.Und.Opt.Count)) + " flex options found)" + vbNewLine
        tbLog.Text = tbLog.Text + "---------------------------------" + vbNewLine
        Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
        aQuote.PriceClose = Clp(uc)
        aQuote.PriceBid = Clp(uc)
        aQuote.PriceAsk = Clp(uc)
        aQuote.PriceLast = Clp(uc)
        aQuote.LotSize = 100
        Set aExch = New EtsGeneralLib.ExchAtom
        aExch.Code = ""
        aExch.IsUnderlying = True
        aExch.Visible = True
        Set aQuote.Exch = aExch
        Grp.Und.Quote.Add 0, "", aQuote
        'Grp.Und.CalcAllOptions 3965, 3965, 7, 7, enCmBinomial ,
        Grp.Und.CalcAllOptions GM_THEOPRICE, GM_THEOPRICE, enMmQvCalcIvNone, enMmQvCalcIvNone, enCmBinomial, _
                            True, False, False, _
                            True, Nothing, 0.05, 0, _
                            False, 0, 0, 0 'lDayShift
        'save theo price as close price
        o = 0
        For Each aOpt In Grp.Und.Opt
            If aOpt.Quote(0).PriceTheo > 0 Then
                gDBW.usp_ContractPrice_Save Null, aOpt.ID, Null, Null, Null, Null, Null, Null, aOpt.Quote(0).PriceTheo, Null, Null, Null, Null, Null, 3, Null
                o = o + 1
                tbLog.Text = tbLog.Text + aOpt.Symbol + vbTab + vbTab + Trim$(Format$(aOpt.Quote(0).PriceTheo, "##,##.####0")) + vbNewLine
            End If
        Next
        tbLog.Text = tbLog.Text + vbNewLine
        End If
        Grp.Und.Opt.Clear
        Grp.Und.CleanUp
        Grp.CleanUp (True)
        uc = uc + 1
    Next
    Exit Sub
EH:
    gCmn.ErrorMsgBox Me, "Operation failed."

End Sub
