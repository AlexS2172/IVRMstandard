VERSION 5.00
Object = "{D76D7128-4A96-11D3-BD95-D296DC2DD072}#1.0#0"; "vsflex7.ocx"
Begin VB.UserControl ctlGreeksView 
   ClientHeight    =   3765
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   10515
   KeyPreview      =   -1  'True
   ScaleHeight     =   3765
   ScaleWidth      =   10515
   Begin VB.Timer tmrShow 
      Enabled         =   0   'False
      Interval        =   10
      Left            =   1440
      Top             =   3120
   End
   Begin VSFlex7Ctl.VSFlexGrid fgUnd 
      Height          =   2055
      Left            =   0
      TabIndex        =   1
      Top             =   780
      Width           =   7095
      _cx             =   12515
      _cy             =   3625
      _ConvInfo       =   1
      Appearance      =   1
      BorderStyle     =   1
      Enabled         =   -1  'True
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      MousePointer    =   0
      BackColor       =   -2147483643
      ForeColor       =   -2147483640
      BackColorFixed  =   -2147483633
      ForeColorFixed  =   -2147483630
      BackColorSel    =   -2147483635
      ForeColorSel    =   -2147483634
      BackColorBkg    =   -2147483636
      BackColorAlternate=   -2147483643
      GridColor       =   -2147483633
      GridColorFixed  =   -2147483632
      TreeColor       =   -2147483632
      FloodColor      =   192
      SheetBorder     =   -2147483642
      FocusRect       =   1
      HighLight       =   1
      AllowSelection  =   -1  'True
      AllowBigSelection=   -1  'True
      AllowUserResizing=   0
      SelectionMode   =   0
      GridLines       =   1
      GridLinesFixed  =   2
      GridLineWidth   =   1
      Rows            =   50
      Cols            =   10
      FixedRows       =   1
      FixedCols       =   1
      RowHeightMin    =   0
      RowHeightMax    =   0
      ColWidthMin     =   0
      ColWidthMax     =   0
      ExtendLastCol   =   0   'False
      FormatString    =   ""
      ScrollTrack     =   -1  'True
      ScrollBars      =   3
      ScrollTips      =   0   'False
      MergeCells      =   0
      MergeCompare    =   0
      AutoResize      =   -1  'True
      AutoSizeMode    =   0
      AutoSearch      =   0
      AutoSearchDelay =   2
      MultiTotals     =   -1  'True
      SubtotalPosition=   1
      OutlineBar      =   0
      OutlineCol      =   0
      Ellipsis        =   0
      ExplorerBar     =   0
      PicturesOver    =   0   'False
      FillStyle       =   0
      RightToLeft     =   0   'False
      PictureType     =   0
      TabBehavior     =   0
      OwnerDraw       =   0
      Editable        =   0
      ShowComboButton =   1
      WordWrap        =   0   'False
      TextStyle       =   0
      TextStyleFixed  =   0
      OleDragMode     =   0
      OleDropMode     =   0
      DataMode        =   0
      VirtualData     =   -1  'True
      DataMember      =   ""
      ComboSearch     =   3
      AutoSizeMouse   =   -1  'True
      FrozenRows      =   0
      FrozenCols      =   0
      AllowUserFreezing=   0
      BackColorFrozen =   0
      ForeColorFrozen =   0
      WallPaperAlignment=   9
   End
   Begin VSFlex7Ctl.VSFlexGrid fgFlt 
      Height          =   495
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   7575
      _cx             =   13361
      _cy             =   873
      _ConvInfo       =   1
      Appearance      =   1
      BorderStyle     =   1
      Enabled         =   -1  'True
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      MousePointer    =   0
      BackColor       =   -2147483643
      ForeColor       =   -2147483640
      BackColorFixed  =   -2147483633
      ForeColorFixed  =   -2147483630
      BackColorSel    =   -2147483635
      ForeColorSel    =   -2147483634
      BackColorBkg    =   -2147483636
      BackColorAlternate=   -2147483643
      GridColor       =   -2147483633
      GridColorFixed  =   -2147483632
      TreeColor       =   -2147483632
      FloodColor      =   192
      SheetBorder     =   -2147483642
      FocusRect       =   1
      HighLight       =   1
      AllowSelection  =   -1  'True
      AllowBigSelection=   -1  'True
      AllowUserResizing=   0
      SelectionMode   =   0
      GridLines       =   1
      GridLinesFixed  =   2
      GridLineWidth   =   1
      Rows            =   50
      Cols            =   10
      FixedRows       =   1
      FixedCols       =   1
      RowHeightMin    =   0
      RowHeightMax    =   0
      ColWidthMin     =   0
      ColWidthMax     =   0
      ExtendLastCol   =   0   'False
      FormatString    =   ""
      ScrollTrack     =   0   'False
      ScrollBars      =   3
      ScrollTips      =   0   'False
      MergeCells      =   0
      MergeCompare    =   0
      AutoResize      =   -1  'True
      AutoSizeMode    =   0
      AutoSearch      =   0
      AutoSearchDelay =   2
      MultiTotals     =   -1  'True
      SubtotalPosition=   1
      OutlineBar      =   0
      OutlineCol      =   0
      Ellipsis        =   0
      ExplorerBar     =   0
      PicturesOver    =   0   'False
      FillStyle       =   0
      RightToLeft     =   0   'False
      PictureType     =   0
      TabBehavior     =   0
      OwnerDraw       =   0
      Editable        =   0
      ShowComboButton =   1
      WordWrap        =   0   'False
      TextStyle       =   0
      TextStyleFixed  =   0
      OleDragMode     =   0
      OleDropMode     =   0
      DataMode        =   0
      VirtualData     =   -1  'True
      DataMember      =   ""
      ComboSearch     =   3
      AutoSizeMouse   =   -1  'True
      FrozenRows      =   0
      FrozenCols      =   0
      AllowUserFreezing=   0
      BackColorFrozen =   0
      ForeColorFrozen =   0
      WallPaperAlignment=   9
   End
   Begin VB.Menu mnuCtx 
      Caption         =   "<Context>"
      Begin VB.Menu mnuCtxTradeNew 
         Caption         =   "New Trade..."
      End
      Begin VB.Menu mnuCtxSeparator1 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuCtxOrderNewStock 
         Caption         =   "New Stock Order..."
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuCtxOrderNewOption 
         Caption         =   "New Option Order..."
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuCtxSeparator2 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuCtxTntCardNew 
         Caption         =   "New Trade Message..."
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuCtxSeparator3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxRefresh 
         Caption         =   "Refresh"
         Shortcut        =   {F5}
      End
      Begin VB.Menu mnuCtxCopy 
         Caption         =   "Copy Grid"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuCtxPrint 
         Caption         =   "Print Grid..."
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuCtxSeparator4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxGridLayout 
         Caption         =   "Grid Layout..."
      End
   End
End
Attribute VB_Name = "ctlGreeksView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Const ROW_TMVAL_TOTAL& = 1&
Private Const ROW_DELTA_TOTAL& = 2&
Private Const ROW_DELTA1_TOTAL& = 3&
Private Const ROW_GAMMA_TOTAL& = 4&
Private Const ROW_GAMMA1_TOTAL& = 5&
Private Const ROW_VEGA_TOTAL& = 6&
Private Const ROW_RHO_TOTAL& = 7&

Public Event OnSetCaption()
Public Event OnStateChange()

Private m_gdFlt As New clsGridDef
Private m_gdUnd As New clsGridDef
Private WithEvents geUnd As clsGridEx
Attribute geUnd.VB_VarHelpID = -1
Private m_iSeriesOrder As SortSettings

Private WithEvents PriceProvider As PRICEPROVIDERSLib.BatchPriceInfo
Attribute PriceProvider.VB_VarHelpID = -1
'Private m_GroupPriceProvider As PRICEPROVIDERSLib.IGroupPrice
Private VolaSource As VolatilitySourcesLib.VolatilitySource
Private TradeChannel As clsTradeChannel

Private WithEvents frmLayout As frmGridLayout
Attribute frmLayout.VB_VarHelpID = -1

Public pbProgress As MSComctlLib.ProgressBar
Public lblProcess As VB.Label
Public lblStatus As VB.Label
Public lblValue As VB.Label
Public WithEvents imgStop As VB.Image
Attribute imgStop.VB_VarHelpID = -1
Public imgStopDis As VB.Image

Private WithEvents m_View As EtsMmRisksLib.MmRiskView
Attribute m_View.VB_VarHelpID = -1
Private m_bFirstTime As Boolean

Private m_bInProc As Boolean
Private m_bDataLoad As Boolean
Private m_bRecalc As Boolean
Private m_bLastQuoteReqNow As Boolean
Private m_nLastQuoteReqCount As Long
Private m_nLastQuoteReqDone As Long
Private m_nLastQuoteGroupReqCount As Long
Private m_nLastQuoteGroupReqDone As Long

Public m_frmOwner As Form

Private m_sCurrentOriginalText As String
'Private m_nFilter(GFC_GROUP To GFC_COLUMN_COUNT) As Long
Private m_aFilter As EtsGeneralLib.EtsFilterData

Private m_enMenuGrid As GridTypeEnum
Private m_nMenuGridCol As Long
Private m_nMenuGridRow As Long
Private m_nMenuGridCols As Long
Private m_nMenuGridRows As Long

Private m_bKeyDown(GT_GREEKS_FILTER To GT_GREEKS_UNDERLYING) As Boolean
Private m_GridLock(GT_GREEKS_FILTER To GT_GREEKS_UNDERLYING) As New clsGridLock

'Private m_bGroupRequest As Boolean
Private m_bShutDown As Boolean
Private WithEvents aParams As clsParams
Attribute aParams.VB_VarHelpID = -1

Public Function Init() As Boolean
    On Error GoTo EH
    
    m_bShutDown = False
    m_bFirstTime = True
    
    
'    mnuCtxTradeNew.Caption = "New Trade..." & vbTab & "Ins"
'    mnuCtxOrderNewStock.Caption = "New Stock Order..." & vbTab & "Alt+Ins"
'    mnuCtxOrderNewOption.Caption = "New Option Order..." & vbTab & "Ctrl+Alt+Ins"
'    mnuCtxTntCardNew.Caption = "New Trade Message..." & vbTab & "Shift+Alt+Ins"
    Set m_aFilter = New EtsGeneralLib.EtsFilterData
    m_aFilter.Initialize GFC_SYMBOL, GFC_COLUMN_COUNT

    ResetMenuData
    m_sCurrentOriginalText = ""
    m_bKeyDown(GT_GREEKS_FILTER) = False
    m_bKeyDown(GT_GREEKS_UNDERLYING) = False
    
    m_GridLock(GT_GREEKS_FILTER).Init fgFlt
    m_GridLock(GT_GREEKS_UNDERLYING).Init fgUnd
    
    m_iSeriesOrder = flexSortGenericAscending
    
    InitColumns
    InitGrids
    
    Set geUnd = New clsGridEx
    geUnd.Init fgUnd
    
    FormatFltGrid
    FormatFltColumns
    Set m_View = New EtsMmRisksLib.MmRiskView
    Set m_View.EtsMain = g_Main
    m_View.ViewMode = RV_GREEKS
    
    InitFltData
    
    Set VolaSource = g_VolaSource
    Set TradeChannel = g_TradeChannel
    
    Dim aPT As PRICEPROVIDERSLib.IProvider
    Set PriceProvider = New PRICEPROVIDERSLib.BatchPriceInfo
    
    Set aPT = PriceProvider
    aPT.Type = g_Params.PriceProviderType
    Set aPT = Nothing
    
    PriceProvider.Connect
    
    'm_bGroupRequest = g_Params.PriceProviderIsGroupRequestSupported
    'If m_bGroupRequest Then
    '    Set m_GroupPriceProvider = PriceProvider
    '    If m_GroupPriceProvider Is Nothing Then m_bGroupRequest = False
    'Else
    '    Set m_GroupPriceProvider = Nothing
    'End If
    
    fgFlt.Col = GFC_SYMBOL
    fgFlt.Row = 1
    
    Set frmLayout = New frmGridLayout
    Set aParams = g_Params
    
    Init = True
    
    AdjustCaption
    AdjustState
    Exit Function
EH:
    gCmn.ErrorMsgBox m_frmOwner, "Fail to initialize greeks view."
End Function
Public Sub ShowDataByFilter(ByRef aFilters As EtsGeneralLib.EtsFilterData)
    On Error Resume Next
    m_aFilter.Data(GFC_SYMBOL) = aFilters.Data(GFC_SYMBOL)
    m_aFilter.Data(GFC_GROUPS) = aFilters.Data(GFC_GROUPS)
    m_aFilter.Data(GFC_TRADES) = aFilters.Data(GFC_TRADES)
    m_aFilter.Data(GFC_TRADER) = aFilters.Data(GFC_TRADER)
    m_aFilter.Data(GFC_TRADER_GROUPS) = aFilters.Data(GFC_TRADER_GROUPS)
    m_aFilter.Data(GFC_STRATEGY) = aFilters.Data(GFC_STRATEGY)
    
    FilterUpdateAll
    tmrShow.Enabled = True

End Sub



Public Sub ShowData(Optional ByVal nType As Long = TYPE_UNDERLYING, Optional ByVal nValue As Long = 0)
    On Error Resume Next
    Select Case nType
        Case TYPE_UNDERLYING
            m_aFilter.Data(GFC_SYMBOL) = nValue
        Case TYPE_GROUP
            m_aFilter.Data(GFC_GROUPS) = nValue
        Case TYPE_TRADER
            m_aFilter.Data(GFC_TRADER) = nValue
        Case TYPE_TRADER_GROUP
            m_aFilter.Data(GFC_TRADER_GROUPS) = nValue
        Case TYPE_STRATEGY
            m_aFilter.Data(GFC_STRATEGY) = nValue
    End Select
    
    FilterUpdateAll
    tmrShow.Enabled = True
End Sub

Private Sub FilterUpdateAll()
    On Error Resume Next
    
    With fgFlt
        m_GridLock(GT_GREEKS_FILTER).LockRedraw
        
        FilterUpdateValue True, GFC_SYMBOL
        FilterUpdateValue True, GFC_GROUPS
        FilterUpdateValue True, GFC_TRADER
        FilterUpdateValue True, GFC_TRADER_GROUPS
        FilterUpdateValue True, GFC_STRATEGY

        .TextMatrix(1, GFC_TRADES) = m_aFilter.Data(GFC_TRADES)
        
        FilterUpdateModel False

        .AutoSize 0, .Cols - 1, False, 100
        
        m_GridLock(GT_GREEKS_FILTER).UnlockRedraw
    End With
End Sub

Private Sub FilterUpdateValue(ByVal bAutosize As Boolean, enColumn As GreeksFilterColumnEnum)
    On Error Resume Next
'    Dim sComboList$, sValue$, aEnt As EtsGeneralLib.EtsMmEntityAtom, aUnd As EtsGeneralLib.UndAtom
'    Dim nValue&, collEnt As EtsGeneralLib.EtsMmEntityAtomColl
    If m_bShutDown Then Exit Sub
    Dim i&, nCount&, sComboList$, sValue$, aUnd As EtsGeneralLib.UndAtom, aStrategy As EtsGeneralLib.EtsStrategyAtom
    Dim nValue&, aTrader As EtsGeneralLib.EtsTraderAtom, aUndGroup As EtsGeneralLib.EtsUndGroupAtom
    Dim aTraderGroup As EtsGeneralLib.EtsTraderGroupAtom
    
    With fgFlt
        m_GridLock(GT_GREEKS_FILTER).LockRedraw
        
            sValue = "0"
        nValue = 0
        sComboList = ""
        Select Case enColumn
           Case GFC_SYMBOL
                'sComboList = g_Params.UnderlyingComboList
                sComboList = g_Params.UnderlyingComboListAllWhtFutUnd
                
                Set aUnd = g_Underlying(m_aFilter.Data(GFC_SYMBOL))
                If Not aUnd Is Nothing Then
                    nValue = aUnd.ID
                    sValue = Trim$(Str$(nValue))
                    Set aUnd = Nothing
                End If
                
                If Len(sComboList) > 0 And nValue = 0 Then sComboList = "|" & sComboList
           Case GFC_GROUPS
                For Each aUndGroup In g_UnderlyingGroup
                    sComboList = sComboList & "|#" & Trim$(Str$(aUndGroup.ID)) & ";" & aUndGroup.Name
                    If aUndGroup.ID = m_aFilter.Data(GFC_GROUPS) Then
                        nValue = aUndGroup.ID
                        sValue = Trim$(Str$(nValue))
                    End If
                Next
           Case GFC_TRADER
               For Each aTrader In g_Trader
                    sComboList = sComboList & "|#" & Trim$(Str$(aTrader.ID)) & ";" & aTrader.Name
                    If aTrader.ID = m_aFilter.Data(GFC_TRADER) Then
                        nValue = aTrader.ID
                        sValue = Trim$(Str$(nValue))
                    End If
                Next
            Case GFC_TRADER_GROUPS
               For Each aTraderGroup In g_TraderGroup
                    sComboList = sComboList & "|#" & Trim$(Str$(aTraderGroup.ID)) & ";" & aTraderGroup.Name
                    If aTraderGroup.ID = m_aFilter.Data(GFC_TRADER_GROUPS) Then
                        nValue = aTraderGroup.ID
                        sValue = Trim$(Str$(nValue))
                    End If
                Next
           Case GFC_STRATEGY
                sComboList = "|#" & Trim$(Str$(NO_STRATEGY_ID)) & ";" & NO_STRATEGY_NAME
                If m_aFilter.Data(GFC_STRATEGY) = NO_STRATEGY_ID Then
                    nValue = NO_STRATEGY_ID
                    sValue = NO_STRATEGY_NAME
                End If
                
                For Each aStrategy In g_Strategy
                    sComboList = sComboList & "|#" & Trim$(Str$(aStrategy.ID)) & ";" & aStrategy.Name
                    If aStrategy.ID = m_aFilter.Data(GFC_STRATEGY) Then
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
        m_aFilter.Data(enColumn) = nValue
        
        If bAutosize Then .AutoSize 0, .Cols - 1, , 100
        
    
        m_GridLock(GT_GREEKS_FILTER).UnlockRedraw
    End With
End Sub

Public Sub FilterUpdateModel(ByVal bAutosize As Boolean)
    On Error Resume Next
    
    With fgFlt
        m_GridLock(GT_GREEKS_FILTER).LockRedraw
    
        .TextMatrix(1, GFC_MODEL) = g_Params.CalcModelName(g_Params.CalcModel)
        
        If bAutosize Then
            .AutoSize 0, .Cols - 1, False, 100
        End If
        
        m_GridLock(GT_GREEKS_FILTER).UnlockRedraw
    End With
End Sub

Private Sub InitColumns()
    On Error Resume Next
    g_DefGrids(GT_GREEKS_FILTER).CopyTo m_gdFlt
    g_DefGrids(GT_GREEKS_UNDERLYING).CopyTo m_gdUnd
End Sub

Private Sub InitFltData()
    On Error Resume Next
    
    With fgFlt
        m_GridLock(GT_GREEKS_FILTER).LockRedraw
        
    
        .ColComboList(GFC_TRADES) = "#0;<All>|#1;Today's|#2;OpenPos|#3;NetPos|#7;Manual|#4;Simulated|#5;Today's & Sim|#6;OpenPos & Sim|#8;Manual & Sim"
        .TextMatrix(1, GFC_TRADES) = "0"
    
        m_GridLock(GT_GREEKS_FILTER).UnlockRedraw
    End With
End Sub

Private Sub InitGrids()
    On Error Resume Next
    With fgFlt
        .Rows = 2
        .Cols = GFC_COLUMN_COUNT
        
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
    
    With fgUnd
        .Rows = 1
        .Cols = 2
        
        .AllowBigSelection = False
        .AllowSelection = False
        .AllowUserFreezing = flexFreezeNone
        .AllowUserResizing = flexResizeNone
        .Appearance = flex3DLight
        .AutoSizeMode = flexAutoSizeColWidth
        .AutoSearch = flexSearchNone
        .AutoSizeMouse = False
        .Editable = flexEDNone
        .Ellipsis = flexEllipsisEnd
        .ExplorerBar = flexExSort
        .ExtendLastCol = False
        .FixedCols = 0
        .FixedRows = 1
        .FocusRect = flexFocusSolid
        .FrozenCols = 0
        .FrozenRows = 0
        .OutlineBar = flexOutlineBarNone
        .ScrollBars = flexScrollBarBoth
        .ScrollTrack = True
        .SelectionMode = flexSelectionFree
        .MergeCells = flexMergeFree
        .MergeCompare = flexMCExact
        .TabBehavior = flexTabControls
    End With
End Sub

Private Sub FormatFltGrid()
    On Error Resume Next
    Dim i&, nCols&
    
    With fgFlt
        m_GridLock(GT_GREEKS_FILTER).LockRedraw
    
        nCols = GFC_COLUMN_COUNT
        .Cols = nCols
        
        For i = GFC_SYMBOL To GFC_LAST_COLUMN
            .TextMatrix(0, i) = m_gdFlt.Col(i).Caption
            .ColFormat(i) = m_gdFlt.Col(i).Format
            .ColDataType(i) = m_gdFlt.Col(i).DataType
        Next
        
        .Cell(flexcpAlignment, 0, 0, 0, nCols - 1) = flexAlignCenterCenter
        
        m_GridLock(GT_GREEKS_FILTER).UnlockRedraw
    End With
End Sub

Private Sub FormatFltColumns()
    On Error Resume Next
    Dim i&, nCols&, nRows&, aFont As New StdFont
    
    With fgFlt
        m_GridLock(GT_GREEKS_FILTER).LockRedraw
    
        aFont.Name = m_gdFlt.Font.Name
        aFont.Size = m_gdFlt.Font.Size
        aFont.Bold = m_gdFlt.Font.Bold
        aFont.Italic = m_gdFlt.Font.Italic
        aFont.Strikethrough = m_gdFlt.Font.Strikethrough
        aFont.Underline = m_gdFlt.Font.Underline
        
        Set .Font = aFont
    
        nCols = .Cols - 1
        nRows = .Rows - 1
        For i = GFC_SYMBOL To GFC_LAST_COLUMN
            .Cell(flexcpBackColor, 1, i, nRows, i) = IIf(m_gdFlt.Col(i).BackColor <> 0, m_gdFlt.Col(i).BackColor, RGB(1, 1, 1))
            .Cell(flexcpForeColor, 1, i, nRows, i) = IIf(m_gdFlt.Col(i).ForeColor <> 0, m_gdFlt.Col(i).ForeColor, RGB(1, 1, 1))
        Next

        If m_gdFlt.HorizLinesVisible Then
            If m_gdFlt.VertLinesVisible Then
                .GridLines = flexGridFlat
            Else
                .GridLines = flexGridFlatHorz
            End If
        ElseIf m_gdFlt.VertLinesVisible Then
            .GridLines = flexGridFlatVert
        Else
            .GridLines = flexGridNone
        End If
        .GridColor = m_gdFlt.GridLinesColor
        
        .BackColorSel = m_gdFlt.BackColorSel
        .ForeColorSel = m_gdFlt.ForeColorSel
        
        .AutoSize 0, .Cols - 1, False, 100
        
        m_GridLock(GT_GREEKS_FILTER).UnlockRedraw
    End With
End Sub

Private Sub FormatUndGrid()
    On Error Resume Next
    Dim i&, nCols&, nIdx&, aExp As EtsMmRisksLib.MmRvExpTotalAtom
    
    With fgUnd
        m_GridLock(GT_GREEKS_UNDERLYING).LockRedraw
    
        nCols = GUC_COLUMN_COUNT - 3 + m_View.ExpTotal.Count
        .Cols = nCols + 1
        
        .ColHidden(GUC_KEY) = True
        .ColKey(GUC_KEY) = GUC_NONE
        .ColDataType(GUC_KEY) = flexDTString
        
        For i = GUC_SYMBOL To nCols
            .TextMatrix(0, i) = m_gdUnd.Col(i).Caption
            .ColFormat(i) = m_gdUnd.Col(i).Format
            .ColDataType(i) = m_gdUnd.Col(i).DataType
            .ColKey(i) = i
            .ColSort(i) = flexSortNone
        Next
        
        .TextMatrix(0, nCols) = m_gdUnd.Col(GUC_SYM_TOTAL).Caption
        .ColFormat(nCols) = m_gdUnd.Col(GUC_SYM_TOTAL).Format
        .ColDataType(nCols) = m_gdUnd.Col(GUC_SYM_TOTAL).DataType
        .ColKey(nCols) = GUC_SYM_TOTAL
        .ColSort(nCols) = flexSortNone
        
        i = GUC_VALUE + 1
        For Each aExp In m_View.ExpTotal
            nIdx = IIf((i - GUC_VALUE) Mod 2 <> 0, GUC_EXPIRY_ODD, GUC_EXPIRY_EVEN)
            .TextMatrix(0, i) = Format$(aExp.ExpiryMonth, "MMM DD YY")
            .ColFormat(i) = m_gdUnd.Col(nIdx).Format
            .ColDataType(i) = m_gdUnd.Col(nIdx).DataType
            .ColKey(i) = aExp.ExpiryMonth
            .ColSort(i) = flexSortNone
            i = i + 1
        Next
        
        .Cell(flexcpAlignment, 0, 0, 0, nCols) = flexAlignCenterCenter
        
        .Row = 1
        .Col = 1
        
        m_GridLock(GT_GREEKS_UNDERLYING).UnlockRedraw
    End With
End Sub

Private Sub FormatUndColumns()
    On Error Resume Next
    Dim i&, nCols&, nRows&, nIdx&, aFont As New StdFont, aExp As EtsMmRisksLib.MmRvExpTotalAtom

    With fgUnd
        m_GridLock(GT_GREEKS_UNDERLYING).LockRedraw

        aFont.Name = m_gdUnd.Font.Name
        aFont.Size = m_gdUnd.Font.Size
        aFont.Bold = m_gdUnd.Font.Bold
        aFont.Italic = m_gdUnd.Font.Italic
        aFont.Strikethrough = m_gdUnd.Font.Strikethrough
        aFont.Underline = m_gdUnd.Font.Underline
        
        Set .Font = aFont
        
        nCols = .Cols - 1
        nRows = .Rows - 1
        For i = GUC_SYMBOL To GUC_VALUE
            .Cell(flexcpBackColor, 1, i, nRows, i) = IIf(m_gdUnd.Col(i).BackColor <> 0, m_gdUnd.Col(i).BackColor, RGB(1, 1, 1))
            .Cell(flexcpForeColor, 1, i, nRows, i) = IIf(m_gdUnd.Col(i).ForeColor <> 0, m_gdUnd.Col(i).ForeColor, RGB(1, 1, 1))
        Next
        .Cell(flexcpBackColor, 1, nCols, nRows, nCols) = IIf(m_gdUnd.Col(GUC_SYM_TOTAL).BackColor <> 0, m_gdUnd.Col(GUC_SYM_TOTAL).BackColor, RGB(1, 1, 1))
        .Cell(flexcpForeColor, 1, nCols, nRows, nCols) = IIf(m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor <> 0, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor, RGB(1, 1, 1))
        
        i = GUC_VALUE + 1
        For Each aExp In m_View.ExpTotal
            nIdx = IIf((i - GUC_VALUE) Mod 2 <> 0, GUC_EXPIRY_ODD, GUC_EXPIRY_EVEN)
            .Cell(flexcpBackColor, 1, i, nRows, i) = IIf(m_gdUnd.Col(nIdx).BackColor <> 0, m_gdUnd.Col(nIdx).BackColor, RGB(1, 1, 1))
            .Cell(flexcpForeColor, 1, i, nRows, i) = IIf(m_gdUnd.Col(nIdx).ForeColor <> 0, m_gdUnd.Col(nIdx).ForeColor, RGB(1, 1, 1))
            i = i + 1
        Next
        
        .Cell(flexcpFontBold, 1, nCols, nRows, nCols) = True
        .Cell(flexcpFontBold, 1, 1, 7, nCols) = True
    
        If m_gdUnd.HorizLinesVisible Then
            If m_gdUnd.VertLinesVisible Then
                .GridLines = flexGridFlat
            Else
                .GridLines = flexGridFlatHorz
            End If
        ElseIf m_gdUnd.VertLinesVisible Then
            .GridLines = flexGridFlatVert
        Else
            .GridLines = flexGridNone
        End If
        .GridColor = m_gdUnd.GridLinesColor
        
        .BackColorSel = m_gdUnd.BackColorSel
        .ForeColorSel = m_gdUnd.ForeColorSel

        geUnd.AdjustSortImages
        
        nCols = GUC_COLUMN_COUNT - 3 + m_View.ExpTotal.Count
        
        nCols = .Cols - 1
        For i = GUC_SYMBOL To nCols
            nIdx = IIf((i - GUC_VALUE) Mod 2 <> 0, GUC_EXPIRY_ODD, GUC_EXPIRY_EVEN)
            If nIdx >= 0 Then
                If m_gdUnd.Col(nIdx).AllowNegative_DifCols = True Then
                    .ColFormat(i) = "(" + m_gdUnd.Col(nIdx).Format + ")"
                Else
                    .ColFormat(i) = m_gdUnd.Col(nIdx).Format
                End If
                .ColDataType(i) = m_gdUnd.Col(nIdx).DataType
                .ColHidden(i) = False
                .ColKey(i) = nIdx
                .ColWidth(i) = IIf(m_gdUnd.Col(nIdx).Width > 0, m_gdUnd.Col(nIdx).Width, -1)
            'Else
            '    .ColHidden(i) = True
            End If
        Next
        
        m_GridLock(GT_GREEKS_UNDERLYING).UnlockRedraw
    End With
End Sub

Private Sub UnderlyingsUpdateBackColor()
    On Error Resume Next
    Dim clrBackColor As OLE_COLOR, nStartRow&, nEndRow&, nRow&, nRows&, nUndID&, nNextUndID&, i&, nIdx&
    Dim bUseAltColor As Boolean
    
    With fgUnd
        m_GridLock(GT_GREEKS_UNDERLYING).LockRedraw
        
        nStartRow = 1&
        bUseAltColor = True
        nRows = .Rows - 1
        nUndID = 0&
        
        For nRow = 1 To nRows
            nNextUndID = 0&
            nNextUndID = .RowData(nRow).Und.ID
            If nNextUndID = 0& Then nUndID = nNextUndID
            
            If nRow = nRows Or nUndID <> nNextUndID Then
                nEndRow = IIf(nRow <> nRows, nRow - 1, nRow)
                nUndID = nNextUndID
                bUseAltColor = Not bUseAltColor
                
                For i = GUC_SYMBOL To GUC_VALUE
                    clrBackColor = m_gdUnd.Col(i).BackColor
                    If bUseAltColor Then clrBackColor = GetAlternateColor(clrBackColor)
                    .Cell(flexcpBackColor, nStartRow, i, nEndRow, i) = IIf(clrBackColor <> 0, clrBackColor, RGB(1, 1, 1))
                Next
                
                For i = GUC_VALUE + 1 To .Cols - 2
                    nIdx = IIf((i - GUC_VALUE) Mod 2 <> 0, GUC_EXPIRY_ODD, GUC_EXPIRY_EVEN)
                    clrBackColor = m_gdUnd.Col(nIdx).BackColor
                    If bUseAltColor Then clrBackColor = GetAlternateColor(clrBackColor)
                    .Cell(flexcpBackColor, nStartRow, i, nEndRow, i) = IIf(clrBackColor <> 0, clrBackColor, RGB(1, 1, 1))
                Next
                
                clrBackColor = m_gdUnd.Col(GUC_SYM_TOTAL).BackColor
                If bUseAltColor Then clrBackColor = GetAlternateColor(clrBackColor)
                .Cell(flexcpBackColor, nStartRow, .Cols - 1, nEndRow, .Cols - 1) = IIf(clrBackColor <> 0, clrBackColor, RGB(1, 1, 1))
                
                nStartRow = nEndRow + 1
            End If
        Next
        
        m_GridLock(GT_GREEKS_UNDERLYING).UnlockRedraw
    End With
End Sub
'
'Private Function CheckTradeFilter(ByRef aTrd As EtsMmGeneralLib.MmTradeInfoAtom) As Boolean
'    On Error Resume Next
'    Dim bMatched As Boolean, nValue&
'
'    bMatched = False
'
'    If Not aTrd Is Nothing Then
'        ' futures & futures options trades are not supported yet
'        If aTrd.ContractType = enCtFuture Or aTrd.ContractType = enCtFutOption Then Exit Function
'
'        If aTrd.ContractType = enCtOption Then
'            If aTrd.Opt.Expiry < Date Then Exit Function
'        End If
'
'        nValue = m_nFilter(GFC_VALUE)
'
'        If nValue <> 0 Then
'            Select Case m_nFilter(GFC_GROUP)
'                Case TYPE_UNDERLYING
'                    bMatched = (aTrd.UndID = nValue)
'
'                Case TYPE_GROUP
'                    bMatched = Not g_UnderlyingGroup(nValue).Und(aTrd.UndID) Is Nothing
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
'                nValue = m_nFilter(GFC_TYPE)
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
'End Function

Private Function CheckTradeFilter(ByRef aTrd As EtsMmGeneralLib.MmTradeInfoAtom) As Boolean
    On Error Resume Next
    Dim bMatched As Boolean, nValue&

    bMatched = True

    If Not aTrd Is Nothing Then
        ' futures & futures options trades are not supported yet
        If aTrd.ContractType = enCtFuture Or aTrd.ContractType = enCtFutOption Then Exit Function

        If aTrd.ContractType = enCtOption Then
            If aTrd.Opt.Expiry < Date Then Exit Function
        End If

       If bMatched And m_aFilter.Data(GFC_SYMBOL) > 0 Then _
            bMatched = (aTrd.UndID = m_aFilter.Data(GFC_SYMBOL))
        If bMatched And m_aFilter.Data(GFC_GROUPS) > 0 Then _
            bMatched = Not g_UnderlyingGroup(m_aFilter.Data(GFC_GROUPS)).Und(aTrd.UndID) Is Nothing
        If bMatched And m_aFilter.Data(GFC_TRADER) > 0 Then _
            bMatched = (aTrd.Trader.ID = m_aFilter.Data(GFC_TRADER))
        If bMatched And m_aFilter.Data(GFC_TRADER_GROUPS) > 0 Then _
            bMatched = (aTrd.Trader.GroupID = m_aFilter.Data(GFC_TRADER_GROUPS))
        If bMatched And m_aFilter.Data(GFC_STRATEGY) <> 0 Then _
            bMatched = (aTrd.strategyID = IIf(m_aFilter.Data(GFC_STRATEGY) > 0, m_aFilter.Data(GFC_STRATEGY), 0))

        If bMatched Then
            nValue = m_aFilter.Data(GFC_TRADES)
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
End Function

Private Sub ClearViewAndData()
    On Error Resume Next
    fgUnd.Rows = 1
    fgUnd.Rows = 8
    fgUnd.FrozenRows = 7

    Set m_View = Nothing
    Set m_View = New EtsMmRisksLib.MmRiskView
    Set m_View.EtsMain = g_Main
    m_View.ViewMode = RV_GREEKS
    
    FormatUndGrid
    FormatUndColumns
    UnderlyingsShow False
    SetRefreshHint False
End Sub

Private Sub aParams_PriceProfilesChange()
    If m_View.Grp.GroupType <> 0 And m_View.Grp.ID <> 0 Then SetRefreshHint True
End Sub

Private Sub aParams_PriceRoundingRuleChange()
    If m_View.Grp.GroupType <> 0 And m_View.Grp.ID <> 0 Then SetRefreshHint True
End Sub

Private Sub aParams_UnderlyingsParamsChange(collUpdUnd As EtsGeneralLib.EtsMmFilterAtomColl)
    Dim bUpdate As Boolean, aFilterAtom As EtsGeneralLib.EtsMmFilterAtom
    Dim aUnd As EtsMmHedgeLib.MmHsUndAtom
    
    If m_View.Grp.GroupType = 0 Or m_View.Grp.ID = 0 Then Exit Sub
    
    bUpdate = False
    On Error Resume Next
    
    For Each aFilterAtom In collUpdUnd
        If Not m_View.Und(aFilterAtom.ID) Is Nothing Then
            bUpdate = True
            Set aFilterAtom = Nothing
            Exit For
        End If
        Set aFilterAtom = Nothing
    Next
    If bUpdate Then SetRefreshHint True
End Sub

Private Sub aParams_UndPriceToleranceChange()
    If m_View.Grp.GroupType <> 0 And m_View.Grp.ID <> 0 Then SetRefreshHint True
End Sub

Private Sub fgFlt_AfterEdit(ByVal Row As Long, ByVal Col As Long)
    On Error Resume Next
    Dim sValue$, nValue&
    
    With fgFlt
        sValue = Trim$(.TextMatrix(Row, Col))
        If m_sCurrentOriginalText <> sValue Then
            nValue = CLng(sValue)
            If Err.Number <> 0 Then nValue = val(sValue)
            If Err.Number = 0 Then
                Select Case Col
                Case GFC_SYMBOL, GFC_GROUPS To GFC_STRATEGY
                    If (Col = GFC_SYMBOL) Then
                        If (Not g_UnderlyingAll(nValue) Is Nothing) Then
                            If (g_UnderlyingAll(nValue).IsHead) Then
                                m_aFilter.Data(Col) = g_UnderlyingAll(nValue).ID
                                .TextMatrix(Row, Col) = g_UnderlyingAll(nValue).Symbol
                            Else
                                If (Not g_UnderlyingAll(nValue).HeadComponent Is Nothing) Then
                                    m_aFilter.Data(Col) = g_UnderlyingAll(nValue).HeadComponent.ID
                                    .TextMatrix(Row, Col) = g_UnderlyingAll(nValue).HeadComponent.Symbol
                                Else
                                    m_aFilter.Data(Col) = nValue
                                End If
                            End If
                        End If
                    Else
                        m_aFilter.Data(Col) = nValue
                    End If
                    
                    .AutoSize 0, .Cols - 1, , 100
                    tmrShow.Enabled = True
                
                Case GFC_TRADES
                    m_aFilter.Data(GFC_TRADES) = nValue
                    .AutoSize 0, .Cols - 1, , 100
                    tmrShow.Enabled = True
                       
                End Select
            Else
                .TextMatrix(1, Col) = m_aFilter.Data(Col)
            End If
        End If
    End With
End Sub

Private Sub fgFlt_DblClick()
    On Error Resume Next
    With fgFlt
        m_enMenuGrid = GT_GREEKS_FILTER
        m_nMenuGridCol = .MouseCol
        m_nMenuGridRow = .MouseRow
        m_nMenuGridCols = .Cols
        m_nMenuGridRows = .Rows
        
        HandleGridDblClick False
    End With
End Sub

Private Sub fgFlt_KeyDown(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    If IsHotKeyGridClipOrOrderCard(KeyCode, Shift) Then
        m_bKeyDown(GT_GREEKS_FILTER) = True
    End If
End Sub

Private Sub fgFlt_KeyUp(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    If m_bKeyDown(GT_GREEKS_FILTER) Then
        m_bKeyDown(GT_GREEKS_FILTER) = False
        With fgFlt
            m_enMenuGrid = GT_GREEKS_FILTER
            m_nMenuGridCol = .Col
            m_nMenuGridRow = .Row
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
        End With
        
        Select Case True
            Case KeyCode = vbKeyInsert And Shift = vbAltMask
                mnuCtxOrderNewStock_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbCtrlMask + vbAltMask
                mnuCtxOrderNewOption_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbShiftMask + vbAltMask
                mnuCtxTntCardNew_Click
            
            Case (KeyCode = vbKeyInsert Or KeyCode = vbKeyC) And Shift = vbCtrlMask
                mnuCtxCopy_Click
        
        End Select
    End If
End Sub

Private Sub fgFlt_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    On Error Resume Next
    If Button = vbRightButton Then
        With fgFlt
            m_enMenuGrid = GT_GREEKS_FILTER
            m_nMenuGridCol = .MouseCol
            m_nMenuGridRow = .MouseRow
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
            ShowPopup
        End With
    End If
End Sub

Private Sub fgFlt_StartEdit(ByVal Row As Long, ByVal Col As Long, Cancel As Boolean)
    On Error Resume Next
    Cancel = True
    
    If IsDblClickHandled Then Exit Sub
    
    With fgFlt
        If Not m_bInProc And Not m_bDataLoad And Not m_bLastQuoteReqNow And Col >= GFC_SYMBOL And Col <= GFC_LAST_COLUMN Then
            Cancel = Not m_gdFlt.Col(Col).CanEdit
            
            If Not Cancel Then m_sCurrentOriginalText = Trim$(.TextMatrix(Row, Col))
        End If
    End With
End Sub

Private Sub fgUnd_DblClick()
    On Error Resume Next
    With fgUnd
        m_enMenuGrid = GT_GREEKS_UNDERLYING
        m_nMenuGridCol = .MouseCol
        m_nMenuGridRow = .MouseRow
        m_nMenuGridCols = .Cols
        m_nMenuGridRows = .Rows
        
        HandleGridDblClick True
    End With
End Sub

Private Sub fgUnd_KeyDown(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    If IsHotKeyGridClipOrTradeOrderCard(KeyCode, Shift) Then
        m_bKeyDown(GT_GREEKS_UNDERLYING) = True
    End If
End Sub

Private Sub fgUnd_KeyUp(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    If m_bKeyDown(GT_GREEKS_UNDERLYING) Then
        m_bKeyDown(GT_GREEKS_UNDERLYING) = False
        With fgUnd
            m_enMenuGrid = GT_GREEKS_UNDERLYING
            m_nMenuGridCol = .Col
            m_nMenuGridRow = .Row
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
        End With
        
        Select Case True
            Case KeyCode = vbKeyInsert And Shift = 0
                mnuCtxTradeNew_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbAltMask
                mnuCtxOrderNewStock_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbCtrlMask + vbAltMask
                mnuCtxOrderNewOption_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbShiftMask + vbAltMask
                mnuCtxTntCardNew_Click
            
            Case (KeyCode = vbKeyInsert Or KeyCode = vbKeyC) And Shift = vbCtrlMask
                mnuCtxCopy_Click
        End Select
    End If
End Sub

Private Sub fgUnd_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    On Error Resume Next
    If Button = vbRightButton Then
        With fgUnd
            m_enMenuGrid = GT_GREEKS_UNDERLYING
            m_nMenuGridCol = .MouseCol
            m_nMenuGridRow = .MouseRow
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
            
            If m_nMenuGridRow > 0 And m_nMenuGridRow < m_nMenuGridRows Then
                .Row = m_nMenuGridRow
            End If
            If m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols Then
                .Col = m_nMenuGridCol
            End If
            
            ShowPopup
        End With
    End If
End Sub

Private Sub geUnd_BeforeSort(ByVal Col As Long, Order As Integer)
    On Error Resume Next
    If Col = GUC_SYMBOL Then
        Order = flexSortCustom
    Else
        Order = flexSortNone
    End If
End Sub

Private Sub geUnd_AfterSort(ByVal Col As Long, Order As Integer)
    On Error Resume Next
    If Col = GUC_SYMBOL Then
        m_iSeriesOrder = IIf(m_iSeriesOrder = flexSortGenericAscending, flexSortGenericDescending, flexSortGenericAscending)
        Order = m_iSeriesOrder
        
        With fgUnd
            If .Rows > 8 Then
                Dim nRow&, nCol&
                
                nRow = .Row
                nCol = .Col
                
                UnderlyingsShow True
                UnderlyingsUpdateBadStatus
                TotalsUpdateBadStatus
                
                .Row = nRow
                .Col = nCol
            End If
        End With
    Else
        Order = flexSortCustom
    End If
End Sub

Private Sub imgStop_Click()
    On Error Resume Next
    If m_bLastQuoteReqNow Then
        m_bLastQuoteReqNow = False
        PriceProvider.CancelLastQuote
        'If m_bGroupRequest Then
        '    m_GroupPriceProvider.CancelGroup
        'End If
    
        pbProgress.Visible = False
        lblStatus.Visible = True
        lblProcess.Visible = False
        imgStop.Visible = False
        imgStopDis.Visible = False
        AdjustState
        
    ElseIf m_bDataLoad Then
        m_bDataLoad = False
    
        pbProgress.Visible = False
        lblStatus.Visible = True
        lblProcess.Visible = False
        imgStop.Visible = False
        imgStopDis.Visible = False
        AdjustState
        
    ElseIf m_bInProc Then
        m_bInProc = False
        AdjustState
    End If
End Sub

Private Sub m_View_Progress(ByVal bsDescription As String, ByVal Precent As Double)
    pbProgress.Value = Precent
    lblProcess.Caption = bsDescription
    lblProcess.Refresh
End Sub

Private Sub mnuCtxCopy_Click()
    On Error Resume Next
    If m_bInProc Then Exit Sub

    Screen.MousePointer = vbHourglass
    Select Case m_enMenuGrid
        Case GT_GREEKS_FILTER
            g_ClipMgr.CopyGridToClipboard fgFlt

        Case GT_GREEKS_UNDERLYING
            g_ClipMgr.CopyGridToClipboard fgUnd

    End Select
    Screen.MousePointer = vbDefault
End Sub

Private Sub FillDataForOrderFromCurrentSelection(ByVal bIsStock As Boolean, _
                                        ByRef aUnd As EtsGeneralLib.UndAtom, ByRef dPrice#)
    On Error Resume Next
    Dim aRowData As clsGvRowData
    
    Select Case True
        Case m_enMenuGrid = GT_GREEKS_UNDERLYING And m_nMenuGridRow > 6
            Do While aUnd Is Nothing And m_nMenuGridRow > 4
                Set aRowData = fgUnd.RowData(m_nMenuGridRow)
                
                If Not aRowData Is Nothing Then
                    If Not aRowData.Und Is Nothing Then
                        Set aUnd = g_Underlying(aRowData.Und.ID)
                    Else
                        Set aUnd = g_Underlying(aRowData.SynthUndID)
                    End If
                
                    Set aRowData = Nothing
                End If
                
                m_nMenuGridRow = m_nMenuGridRow - 1
            Loop
        
        Case m_enMenuGrid = GT_GREEKS_FILTER And m_aFilter.Data(GFC_SYMBOL) > 0
            Set aUnd = g_Underlying(m_aFilter.Data(GFC_SYMBOL))
            
    End Select

    If bIsStock And Not aUnd Is Nothing Then
        dPrice = m_View.Und(aUnd.ID).price.Bid
        If dPrice <= 0# Then dPrice = m_View.Und(aUnd.ID).price.Last
    End If
End Sub

Private Sub OrderNew(ByVal bIsStock As Boolean)
'    On Error Resume Next
'    If m_bInProc Then Exit Sub
'    Dim aUnd As EtsGeneralLib.UndAtom, dPrice#
'
'    m_bInProc = True
'    FillDataForOrderFromCurrentSelection bIsStock, aUnd, dPrice
'    m_bInProc = False
'
'    On Error GoTo EH
'    If bIsStock Then
'        frmOrderEntry.NewStockOrder aUnd, True, 100, dPrice
'    Else
'        frmOrderEntry.NewOptionOrder aUnd, Nothing, True, 10, dPrice
'    End If
'
'    Set aUnd = Nothing
'    Exit Sub
'EH:
'    m_bInProc = False
'    gCmn.ErrorMsgBox m_frmOwner, "Greeks View: Fail to create new order."
'    ResetMenuData
'    Set aUnd = Nothing
End Sub

Private Sub mnuCtxOrderNewOption_Click()
    On Error Resume Next
    OrderNew False
End Sub

Private Sub mnuCtxOrderNewStock_Click()
    On Error Resume Next
    OrderNew True
End Sub

Private Sub mnuCtxTntCardNew_Click()
'    On Error Resume Next
'    If m_bInProc Then Exit Sub
'    Dim aUnd As EtsGeneralLib.UndAtom, dPrice#
'
'    m_bInProc = True
'    FillDataForOrderFromCurrentSelection False, aUnd, dPrice
'    m_bInProc = False
'
'    On Error GoTo EH
'    frmTntCardEntry.NewCard m_frmOwner, aUnd, Nothing, False, 10&, 0#
'
'    Set aUnd = Nothing
'    Exit Sub
'EH:
'    m_bInProc = False
'    gCmn.ErrorMsgBox m_frmOwner, "Greeks View: Fail to create new trade message."
'    ResetMenuData
'    Set aUnd = Nothing
End Sub

Private Sub mnuCtxTradeNew_Click()
    On Error GoTo EH
    If m_bInProc Then Exit Sub
    Dim nUndID&, nID&, nColIdx&, bCheckSynth As Boolean
    Dim aRowData As clsGvRowData

    m_bInProc = True
    nUndID = 0
    nID = 0
    
    If m_enMenuGrid = GT_GREEKS_UNDERLYING Then
        If m_nMenuGridRow > 6 And m_nMenuGridRow < m_nMenuGridRows Then
            On Error Resume Next
            bCheckSynth = True
            
            Do While nUndID = 0 And m_nMenuGridRow > 4
                Set aRowData = fgUnd.RowData(m_nMenuGridRow)
                
                If Not aRowData Is Nothing Then
                    If Not aRowData.Und Is Nothing Then
                        nUndID = aRowData.Und.ID
                    Else
                        nUndID = IIf(bCheckSynth, aRowData.SynthUndID, 0)
                    End If
                    nID = nUndID
                    Set aRowData = Nothing
                Else
                    bCheckSynth = False
                End If
                
                m_nMenuGridRow = m_nMenuGridRow - 1
            Loop
            On Error GoTo EH
        End If
        
    ElseIf m_enMenuGrid = GT_GREEKS_FILTER Then
        If m_aFilter.Data(GFC_SYMBOL) > 0 And m_nMenuGridRow >= 0 And m_nMenuGridCol <= m_nMenuGridCols - 1 Then
            nUndID = m_aFilter.Data(GFC_SYMBOL)
            nID = nUndID
        End If
    End If

    m_bInProc = False
    If nUndID <> 0 Then frmTradeEditor.NewTrade nID, nUndID, 1, m_frmOwner
    Exit Sub
EH:
    m_bInProc = False
    gCmn.ErrorMsgBox m_frmOwner, "Fail to create new trade."
    ResetMenuData
End Sub

Private Sub mnuCtxPrint_Click()
'    On Error Resume Next
'    Screen.MousePointer = vbHourglass
'    Select Case m_enMenuGrid
'        Case GT_GREEKS_FILTER
'            frmPrintPreview.Execute m_frmOwner, m_Grp.Name & " Greeks Filter", "Greeks Filter", fgFlt
'
'        Case GT_GREEKS_UNDERLYING
'            frmPrintPreview.Execute m_frmOwner, m_Grp.Name & " Greeks", "Greeks", fgUnd
'
'    End Select
'    Screen.MousePointer = vbDefault
End Sub

Private Sub mnuCtxRefresh_Click()
    On Error Resume Next
    Refresh
End Sub

Private Sub mnuCtxGridLayout_Click()
    On Error Resume Next
    Select Case m_enMenuGrid
        Case GT_GREEKS_FILTER
            CustomizeFltGridLayout

        Case GT_GREEKS_UNDERLYING
            CustomizeUndGridLayout
        
    End Select
End Sub

Private Sub ShowPopup()
    On Error Resume Next
    If m_nMenuGridCol < 0 Or m_nMenuGridRow < 0 Then Exit Sub

    'mnuCtxTradeNew                 "New Trade..."
    'mnuCtxOrderNewStock            "New Stock Order..."
    'mnuCtxOrderNewOption           "New Option Order..."
    'mnuCtxRefresh                  "Refresh"
    'mnuCtxCopy                     "Copy Grid"
    'mnuCtxPrint                    "Print Grid..."
    'mnuCtxGridLayout               "Grid Layout..."
    
    mnuCtxCopy.Enabled = Not m_bInProc
    mnuCtxOrderNewStock.Enabled = Not m_bInProc
    mnuCtxOrderNewOption.Enabled = Not m_bInProc
    mnuCtxTntCardNew.Enabled = Not m_bInProc
    
    Select Case m_enMenuGrid
        Case GT_GREEKS_FILTER
            mnuCtxTradeNew.Enabled = (Not m_bInProc And m_aFilter.Data(GFC_SYMBOL) > 0 _
                                        And m_nMenuGridRow >= 0 And m_nMenuGridCol < m_nMenuGridCols)
            
            PopupMenu mnuCtx
        
        Case GT_GREEKS_UNDERLYING
            mnuCtxTradeNew.Enabled = (Not m_bInProc _
                                    And m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols _
                                    And m_nMenuGridRow > 6 And m_nMenuGridRow < m_nMenuGridRows)
            
            PopupMenu mnuCtx
    End Select
End Sub

Private Sub tmrShow_Timer()
    On Error Resume Next
    tmrShow.Enabled = False
    
    If m_bDataLoad Then Exit Sub
    
    Screen.MousePointer = vbArrow
    DoEvents
    
    If m_View.Grp.ID <> 0 And Not PriceProvider Is Nothing Then
        If m_bLastQuoteReqNow Then PriceProvider.CancelLastQuote
        'If m_bGroupRequest Then
        '    m_GroupPriceProvider.CancelGroup
        'End If
        m_bLastQuoteReqNow = False
        m_View.QuoteReqsAll.Clear
    End If
    
    ClearViewAndData
    AdjustCaption
    
    lblStatus.Visible = False
    imgStop.Visible = True
    imgStopDis.Visible = False
    pbProgress.Min = 0
    pbProgress.Value = 0
    pbProgress.Max = TradeChannel.Trades.Count
    pbProgress.Visible = True
    lblProcess.Caption = "Data loading..."
    lblProcess.Visible = True
    lblProcess.Refresh
    
    If UnderlyingsLoad Then
        AdjustCaption
        
        lblProcess.Caption = "Filter applying..."
        lblProcess.Refresh
        
        UnderlyingsShow False
    
        lblProcess.Caption = "Last quotes request..."
        lblProcess.Refresh
        
        RequestLastQuotes
        SetRefreshHint False
    Else
        If m_View.Grp.ID <> -1 Then
            ClearViewAndData
            lblStatus.Caption = ""
            FilterUpdateAll
            AdjustCaption
            AdjustState
        Else
            lblStatus.Caption = "Press F5 to Refresh"
            lblStatus.Refresh
        End If
      
        imgStop.Visible = False
        imgStopDis.Visible = False
        pbProgress.Visible = False
        lblProcess.Visible = False
        lblStatus.Visible = True
    End If
    
    Screen.MousePointer = vbDefault
End Sub

Private Function UnderlyingsLoad() As Boolean
    On Error GoTo EH
    UnderlyingsLoad = False
    If m_bInProc Then Exit Function
    
    Dim aTrd As EtsMmGeneralLib.MmTradeInfoAtom, nBS&, sKey$, nQty&, nQtyInShares&, nExpiryMonth&
    Dim aUnd As EtsMmRisksLib.MmRvUndAtom, aGUnd As EtsGeneralLib.UndAtom
    Dim aExp As EtsMmRisksLib.MmRvExpAtom, aExpTot As EtsMmRisksLib.MmRvExpTotalAtom
    Dim aPos As EtsMmRisksLib.MmRvPosAtom, aSynthRoot As EtsGeneralLib.SynthRootAtom
    Dim aSynthRootComp As EtsGeneralLib.SynthRootCompAtom, aSynthUnd As EtsMmRisksLib.MmRvUndAtom
    Dim aSynthGreek As EtsMmRisksLib.MmRvSynthGreeksAtom ', aReq As clsGvRequestAtom
    
    m_bInProc = True
    m_bDataLoad = True
    AdjustState
    
    m_View.Grp.GroupType = TYPE_ALL

    
   Err.Clear
    m_View.Grp.Name = ""
    If m_aFilter.Data(GFC_SYMBOL) > 0 Then
        m_View.Grp.Name = g_Underlying(m_aFilter.Data(GFC_SYMBOL)).Symbol
        If Err.Number <> 0 Then m_bDataLoad = False
    End If
    If m_aFilter.Data(GFC_GROUPS) > 0 Then
        If Len(m_View.Grp.Name) > 0 Then m_View.Grp.Name = m_View.Grp.Name & "; "
        m_View.Grp.Name = m_View.Grp.Name & g_UnderlyingGroup(m_aFilter.Data(GFC_GROUPS)).Name
        If Err.Number <> 0 Then m_bDataLoad = False
    End If
    If m_aFilter.Data(GFC_TRADER) > 0 Then
        If Len(m_View.Grp.Name) > 0 Then m_View.Grp.Name = m_View.Grp.Name & "; "
        m_View.Grp.Name = m_View.Grp.Name & g_Trader(m_aFilter.Data(GFC_TRADER)).Name
        If Err.Number <> 0 Then m_bDataLoad = False
    End If
    If m_aFilter.Data(GFC_TRADER_GROUPS) > 0 Then
        If Len(m_View.Grp.Name) > 0 Then m_View.Grp.Name = m_View.Grp.Name & "; "
        m_View.Grp.Name = m_View.Grp.Name & g_TraderGroup(m_aFilter.Data(GFC_TRADER_GROUPS)).Name
        If Err.Number <> 0 Then m_bDataLoad = False
    End If
    If m_aFilter.Data(GFC_STRATEGY) <> 0 Then
        If Len(m_View.Grp.Name) > 0 Then m_View.Grp.Name = m_View.Grp.Name & "; "
        If m_aFilter.Data(GFC_STRATEGY) > 0 Then
            m_View.Grp.Name = m_View.Grp.Name & g_Strategy(m_aFilter.Data(GFC_STRATEGY)).Name
        Else
            m_View.Grp.Name = m_View.Grp.Name & NO_STRATEGY_NAME
        End If
        
        If Err.Number <> 0 Then m_bDataLoad = False
        
    End If
    If Len(m_View.Grp.Name) = 0 Then
        If m_bFirstTime Then
            m_View.Grp.ID = -1
            m_bInProc = False
            
            AdjustState
            m_bDataLoad = False
        End If
        m_View.Grp.Name = "<All>"
    End If
    m_bFirstTime = False
    Dim mmTradesColl As MmTradeInfoColl

    If m_bDataLoad Then
        Set mmTradesColl = g_TradeChannel.Trades.FilterTrades(m_aFilter, g_UnderlyingGroup, False)
        pbProgress.Max = 100
        m_View.Grp.ID = mmTradesColl.Count
        Set m_View.EtsMain = g_Main
        Set m_View.VolaSource = VolaSource
        
        m_View.PositionsLoad mmTradesColl

'        For Each aTrd In mmTradesColl
'            Set aUnd = m_Grp.Und(aTrd.UndID)
'            If aUnd Is Nothing Then
'                Set aUnd = New EtsMmGreeksLib.MmGaUndAtom
'
'                aUnd.ID = aTrd.Und.ID
'                aUnd.UndType = aTrd.Und.UndType
'                aUnd.Symbol = aTrd.Und.Symbol
'
'                If aUnd.UndType = enCtStock Then
'                    Set aUnd.Dividend = aTrd.Und.Dividend
'                Else
'                    Set aUnd.BasketIndex = g_Index(aUnd.ID)
'                    If Not aUnd.BasketIndex Is Nothing Then
'                        If Not aUnd.BasketIndex.IsBasket Then Set aUnd.BasketIndex = Nothing
'                    End If
'
'                    aUnd.Yield = aTrd.Und.Yield
'                End If
'
'                aUnd.IsAmerican = aTrd.Und.IsAmerican
'                aUnd.IsHTB = aTrd.Und.IsHTB
'                aUnd.ExpCalendarID = aTrd.Und.ExpCalendarID
'                aUnd.Skew = aTrd.Und.Skew
'                aUnd.Kurt = aTrd.Und.Kurt
'                aUnd.Pos = BAD_DOUBLE_VALUE
'
'                aUnd.HasSynth = aTrd.Und.HaveSyntheticRoots
'                Set aUnd.SynthRoot = aTrd.Und.SyntheticRoots
'                Set aUnd.UndPriceProfile = aTrd.Und.UndPriceProfile
'                Set aUnd.OptPriceProfile = aTrd.Und.OptPriceProfile
'
'                InitVola aUnd
'
'                sKey = CStr(aUnd.UndType) & "_" & aUnd.Symbol
'                If m_QuoteRequests(sKey) Is Nothing Then m_QuoteRequests.Add aUnd, Nothing, sKey
'
'                m_Grp.Und.Add aUnd.ID, aUnd.Symbol, aUnd
'            End If
'
'            DoEvents
'            If Not m_bDataLoad Then Exit For
'
'            nBS = IIf(aTrd.IsBuy, 1, -1)
'            nQty = aTrd.Quantity * nBS
'            nQtyInShares = nQty * aTrd.LotSize
'
'            If aTrd.ContractType = enCtOption Then
'                nExpiryMonth = CLng(DateSerial(Year(aTrd.Opt.Expiry), Month(aTrd.Opt.Expiry), 1))
'
'                Set aExpTot = m_Grp.ExpiryTotal(nExpiryMonth)
'                If aExpTot Is Nothing Then
'                    Set aExpTot = New EtsMmGreeksLib.MmGaExpTotalAtom
'                    aExpTot.ExpiryMonth = nExpiryMonth
'
'                    m_Grp.ExpiryTotal.Add nExpiryMonth, aExpTot
'                End If
'
'                Set aExp = aUnd.Expiry(nExpiryMonth)
'                If aExp Is Nothing Then
'                    Set aExp = New EtsMmGreeksLib.MmGaExpAtom
'                    aExp.ExpiryMonth = nExpiryMonth
'                    aExp.Expiry = aTrd.Opt.Expiry
'
'                    aUnd.Expiry.Add nExpiryMonth, aExp
'                    aExpTot.Expiry.Add aUnd.ID, aExp
'                End If
'
'                Set aPos = aExp.Pos(aTrd.ContractID)
'                If aPos Is Nothing Then
'                    Set aPos = New EtsMmGreeksLib.MmGaPosAtom
'                    aPos.ID = aTrd.ContractID
'
'                    aPos.ContractType = aTrd.ContractType
'                    aPos.Symbol = aTrd.Symbol
'                    aPos.PriceClose = aTrd.Opt.PriceClose
'                    aPos.LotSize = aTrd.LotSize
'                    aPos.OptType = IIf(aTrd.Opt.OptType <> enOtPut, enOtCall, enOtPut)
'                    aPos.Expiry = aTrd.Opt.Expiry
'                    aPos.Strike = aTrd.Opt.Strike
'                    aPos.PriceTheoClose = aTrd.Opt.PriceTheoClose
'                    aPos.RootID = aTrd.OptRootID
'
'                    aExp.Pos.Add aPos.ID, aPos
'
'                    If aUnd.HasSynth And Not aUnd.SynthRoot Is Nothing Then
'                        Set aSynthRoot = aUnd.SynthRoot(aPos.RootID)
'
'                        If Not aSynthRoot Is Nothing Then
'                            aPos.IsSynth = True
'                            aExp.HasSynth = True
'                            If aPos.SynthGreek Is Nothing Then Set aPos.SynthGreek = New EtsMmGreeksLib.MmGaSynthGreekColl
'                            If aExp.SynthGreek Is Nothing Then Set aExp.SynthGreek = New EtsMmGreeksLib.MmGaSynthGreekColl
'                            If aUnd.SynthGreek Is Nothing Then Set aUnd.SynthGreek = New EtsMmGreeksLib.MmGaSynthGreekColl
'
'                            If aSynthRoot.CashValue > 0# Then
'                                If m_Grp.Und(USD_ID) Is Nothing Then
'                                    Set aSynthUnd = New EtsMmGreeksLib.MmGaUndAtom
'
'                                    aSynthUnd.ID = USD_ID
'                                    aSynthUnd.UndType = enCtStock
'                                    aSynthUnd.Symbol = USD_SYMBOL
'
'                                    aSynthUnd.Pos = BAD_DOUBLE_VALUE
'
'                                    aSynthUnd.PriceAsk = 1#
'                                    aSynthUnd.PriceBid = 1#
'                                    aSynthUnd.PriceLast = 1#
'
'                                    Set aSynthUnd.UndPriceProfile = g_PriceProfile(1)
'                                    Set aSynthUnd.OptPriceProfile = g_PriceProfile(1)
'
'                                    Set aSynthUnd.SynthPos = New EtsMmGreeksLib.MmGaPosColl
'
'                                    m_Grp.Und.Add aSynthUnd.ID, aSynthUnd.Symbol, aSynthUnd
'                                    Set aSynthUnd = Nothing
'                                End If
'
'                                Set aSynthGreek = New EtsMmGreeksLib.MmGaSynthGreekAtom
'                                aSynthGreek.UndID = USD_ID
'                                aSynthGreek.UndSymbol = USD_SYMBOL
'                                aPos.SynthGreek.Add aSynthGreek.UndID, aSynthGreek
'                                Set aSynthGreek = Nothing
'
'                                Set aSynthGreek = aExp.SynthGreek(USD_ID)
'                                If aSynthGreek Is Nothing Then
'                                    Set aSynthGreek = New EtsMmGreeksLib.MmGaSynthGreekAtom
'                                    aSynthGreek.UndID = USD_ID
'                                    aSynthGreek.UndSymbol = USD_SYMBOL
'                                    aExp.SynthGreek.Add aSynthGreek.UndID, aSynthGreek
'                                End If
'                                Set aSynthGreek = Nothing
'
'                                Set aSynthGreek = aUnd.SynthGreek(USD_ID)
'                                If aSynthGreek Is Nothing Then
'                                    Set aSynthGreek = New EtsMmGreeksLib.MmGaSynthGreekAtom
'                                    aSynthGreek.UndID = USD_ID
'                                    aSynthGreek.UndSymbol = USD_SYMBOL
'                                    aUnd.SynthGreek.Add aSynthGreek.UndID, aSynthGreek
'                                End If
'                                Set aSynthGreek = Nothing
'                            End If
'
'                            For Each aSynthRootComp In aSynthRoot.SynthRootComponents
'
'                                If aSynthRootComp.UndID <> aUnd.ID Then
'                                    Set aGUnd = g_UnderlyingAll(aSynthRootComp.UndID)
'                                    If Not aGUnd Is Nothing Then
'
'                                        Set aSynthUnd = m_Grp.Und(aSynthRootComp.UndID)
'                                        If aSynthUnd Is Nothing Then
'                                            Set aSynthUnd = New EtsMmGreeksLib.MmGaUndAtom
'                                            aSynthUnd.ID = aSynthRootComp.UndID
'
'                                            aSynthUnd.UndType = aGUnd.UndType
'                                            aSynthUnd.Symbol = aGUnd.Symbol
'                                            aSynthUnd.IsAmerican = aGUnd.IsAmerican
'                                            aSynthUnd.IsHTB = aGUnd.IsHTB
'                                            aSynthUnd.ExpCalendarID = aGUnd.ExpCalendarID
'                                            aSynthUnd.Skew = aGUnd.Skew
'                                            aSynthUnd.Kurt = aGUnd.Kurt
'                                            aSynthUnd.HasSynth = aGUnd.HaveSyntheticRoots
'
'                                            Set aSynthUnd.SynthRoot = aGUnd.SyntheticRoots
'                                            If aSynthUnd.UndType = enCtStock Then
'                                                Set aSynthUnd.Dividend = aGUnd.Dividend
'                                            Else
'                                                Set aSynthUnd.BasketIndex = g_Index(aSynthUnd.ID)
'                                                If Not aSynthUnd.BasketIndex Is Nothing Then
'                                                    If Not aSynthUnd.BasketIndex.IsBasket Then Set aSynthUnd.BasketIndex = Nothing
'                                                End If
'
'                                                aSynthUnd.Yield = aGUnd.Yield
'                                            End If
'
'                                            Set aSynthUnd.UndPriceProfile = aGUnd.UndPriceProfile
'                                            Set aSynthUnd.OptPriceProfile = aGUnd.OptPriceProfile
'
'                                            aSynthUnd.Pos = BAD_DOUBLE_VALUE
'
'                                            sKey = CStr(aSynthUnd.UndType) & "_" & aSynthUnd.Symbol
'                                            If m_QuoteRequests(sKey) Is Nothing Then m_QuoteRequests.Add aSynthUnd, Nothing, sKey
'
'                                            m_Grp.Und.Add aSynthUnd.ID, aSynthUnd.Symbol, aSynthUnd
'
'                                            Set aGUnd = Nothing
'                                        End If
'
'                                        If aSynthUnd.SynthPos Is Nothing Then Set aSynthUnd.SynthPos = New EtsMmGreeksLib.MmGaPosColl
'                                        aSynthUnd.SynthPos.Add aPos.ID, aPos
'
'                                        Set aSynthGreek = New EtsMmGreeksLib.MmGaSynthGreekAtom
'                                        aSynthGreek.UndID = aSynthRootComp.UndID
'                                        aSynthGreek.UndSymbol = aSynthUnd.Symbol
'                                        aPos.SynthGreek.Add aSynthGreek.UndID, aSynthGreek
'                                        Set aSynthGreek = Nothing
'
'                                        Set aSynthGreek = aUnd.SynthGreek(aSynthRootComp.UndID)
'                                        If aSynthGreek Is Nothing Then
'                                            Set aSynthGreek = New EtsMmGreeksLib.MmGaSynthGreekAtom
'                                            aSynthGreek.UndID = aSynthRootComp.UndID
'                                            aSynthGreek.UndSymbol = aSynthUnd.Symbol
'
'                                            aUnd.SynthGreek.Add aSynthGreek.UndID, aSynthGreek
'                                        End If
'                                        Set aSynthGreek = Nothing
'
'                                        Set aSynthGreek = aExp.SynthGreek(aSynthRootComp.UndID)
'                                        If aSynthGreek Is Nothing Then
'                                            Set aSynthGreek = New EtsMmGreeksLib.MmGaSynthGreekAtom
'                                            aSynthGreek.UndID = aSynthRootComp.UndID
'                                            aSynthGreek.UndSymbol = aSynthUnd.Symbol
'
'                                            aExp.SynthGreek.Add aSynthGreek.UndID, aSynthGreek
'                                        End If
'                                        Set aSynthGreek = Nothing
'                                    End If
'                                End If
'                            Next
'                            Set aSynthUnd = Nothing
'                            Set aSynthRoot = Nothing
'                        End If
'                    End If
'
'                    aPos.QtyInShares = 0
'
'                    sKey = CStr(aPos.ContractType) & "_" & aPos.Symbol
'                    Set aReq = m_QuoteRequests(sKey)
'                    If aReq Is Nothing Then
'                        m_QuoteRequests.Add aUnd, aPos, sKey
'                    Else
'                        If aReq.Pos Is Nothing Then Set aReq.Pos = aPos
'                        Set aReq = Nothing
'                    End If
'                End If
'
'                aPos.QtyInShares = aPos.QtyInShares + nQtyInShares
'
'                Set aPos = Nothing
'                Set aExp = Nothing
'                Set aExpTot = Nothing
'            Else
'                If aUnd.Pos = BAD_DOUBLE_VALUE Then aUnd.Pos = 0
'                aUnd.Pos = aUnd.Pos + aTrd.Price * nQtyInShares
'            End If
'
'            Set aUnd = Nothing
'
'            DoEvents
'            If Not m_bDataLoad Then Exit For
'
'            IncProgress pbProgress
'
'            Set aTrd = Nothing
'        Next
        
        UnderlyingsAdjustRates True
        UnderlyingsLoad = m_bDataLoad
    End If

    m_bInProc = False
Ex:
    On Error Resume Next
    Set aPos = Nothing
    Set aExp = Nothing
    Set aExpTot = Nothing
    Set aTrd = Nothing
    Set aGUnd = Nothing
    Set aUnd = Nothing
    m_bDataLoad = False
    AdjustState
    Exit Function
EH:
    m_bInProc = False
    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to load underlyings."
    GoTo Ex
End Function

Private Sub UnderlyingsShow(ByVal bReorderOnly As Boolean)
    On Error Resume Next
    Dim nUndRow&, aUnd As EtsMmRisksLib.MmRvUndAtom, aRowData As clsGvRowData
    
    With fgUnd
        m_GridLock(GT_GREEKS_UNDERLYING).LockRedraw
        Debug.Assert .Rows >= 7
        
        If Not bReorderOnly Then
            pbProgress.Min = 0
            pbProgress.Value = 0
            pbProgress.Max = m_View.Und.Count
            
            FormatUndGrid
            .TextMatrix(ROW_TMVAL_TOTAL, GUC_SYMBOL) = "Total"
            .TextMatrix(ROW_DELTA_TOTAL, GUC_SYMBOL) = " "
            .TextMatrix(ROW_DELTA1_TOTAL, GUC_SYMBOL) = " "
            .TextMatrix(ROW_GAMMA_TOTAL, GUC_SYMBOL) = " "
            .TextMatrix(ROW_GAMMA1_TOTAL, GUC_SYMBOL) = " "
            .TextMatrix(ROW_VEGA_TOTAL, GUC_SYMBOL) = " "
            .TextMatrix(ROW_RHO_TOTAL, GUC_SYMBOL) = " "
            
            .TextMatrix(ROW_TMVAL_TOTAL, GUC_VALUE) = "TimeValue"
            .TextMatrix(ROW_DELTA_TOTAL, GUC_VALUE) = "OptDlt$"
            .TextMatrix(ROW_DELTA1_TOTAL, GUC_VALUE) = "OptDlt"
            .TextMatrix(ROW_GAMMA_TOTAL, GUC_VALUE) = "Gma$"
            .TextMatrix(ROW_GAMMA1_TOTAL, GUC_VALUE) = "Gma$1"
            .TextMatrix(ROW_VEGA_TOTAL, GUC_VALUE) = "Vega"
            .TextMatrix(ROW_RHO_TOTAL, GUC_VALUE) = "Rho"
            
            .Cell(flexcpText, 1, GUC_VALUE + 1, 7, GUC_COLUMN_COUNT - 3 + m_View.ExpTotal.Count) = STR_NA
        Else
            .Rows = 8
        End If
'        .Select 4, 0, 4, .Cols - 1
'        .CellBorder .BackColorFrozen, -1, -1, -1, 3, -1, -1
        
        For Each aUnd In m_View.Und
            'If aUnd.Pos > BAD_DOUBLE_VALUE Or aUnd.Expiry.Count > 0 Then
            If aUnd.ExpColl.Count > 0 Then
                Set aRowData = New clsGvRowData
                Set aRowData.Und = aUnd
            
                If m_iSeriesOrder = flexSortGenericAscending Then nUndRow = .Rows Else nUndRow = 7
                .AddItem "", nUndRow
                .RowData(nUndRow) = aRowData
                .TextMatrix(nUndRow, GUC_KEY) = CStr(aUnd.ID)
                
                UnderlyingUpdate nUndRow, True, aRowData
                
                IncProgress pbProgress
                DoEvents
            End If
        Next
        
        If Not bReorderOnly Then
            TotalsUpdate False
        End If
        
        FormatUndColumns
        UnderlyingsUpdateBackColor
        
        If Not bReorderOnly Then
            geUnd.ShowSortImage GUC_SYMBOL, IIf(m_iSeriesOrder = flexSortGenericAscending, 1, -1)
            .AutoSize 1, .Cols - 1, False, 100
        End If
        
        .MergeCol(GUC_SYMBOL) = True
        If Not bReorderOnly Then
            .Row = 1
            .Col = 1
        End If
        
        m_GridLock(GT_GREEKS_UNDERLYING).UnlockRedraw
    End With
End Sub

Private Sub TotalsUpdate(ByVal bAutosize As Boolean)
    On Error Resume Next
    Dim aExpTot As EtsMmRisksLib.MmRvExpTotalAtom, nCol&, nIdx&
    Dim dTotalsTimeValue#, dTotalDeltaEq#, dTotDeltaInShares#, dTotGammaEq#, dTotGammaInShares#, dTotVegaInShares#, dTotRhoInShares#
    Dim bBadTotalsTimeValue As Boolean, bBadTotalDeltaEq As Boolean, bBadTotDeltaInShares As Boolean
    Dim bBadTotGammaEq As Boolean, bBaddTotGammaInShares As Boolean, bBadTotVegaInShares As Boolean, bBadTotRhoInShares As Boolean
    
    dTotalsTimeValue = BAD_DOUBLE_VALUE
    dTotalDeltaEq = BAD_DOUBLE_VALUE
    dTotDeltaInShares = BAD_DOUBLE_VALUE
    dTotGammaEq = BAD_DOUBLE_VALUE
    dTotGammaInShares = BAD_DOUBLE_VALUE
    dTotVegaInShares = BAD_DOUBLE_VALUE
    dTotRhoInShares# = BAD_DOUBLE_VALUE
    
    With fgUnd
        m_GridLock(GT_GREEKS_UNDERLYING).LockRedraw
        
        nCol = GUC_VALUE + 1
        For Each aExpTot In m_View.ExpTotal
            nIdx = IIf((nCol - GUC_VALUE) Mod 2 <> 0, GUC_EXPIRY_ODD, GUC_EXPIRY_EVEN)
            
            If aExpTot.TimeValueInShares > BAD_DOUBLE_VALUE Then
                If dTotalsTimeValue = BAD_DOUBLE_VALUE Then dTotalsTimeValue = 0
                dTotalsTimeValue = dTotalsTimeValue + aExpTot.TimeValueInShares
                .TextMatrix(ROW_TMVAL_TOTAL, nCol) = aExpTot.TimeValueInShares
            Else
                .TextMatrix(ROW_TMVAL_TOTAL, nCol) = STR_NA
            End If
            If aExpTot.BadTimeValueInShares Then bBadTotalsTimeValue = True
            
            .Cell(flexcpForeColor, ROW_TMVAL_TOTAL, nCol) = IIf(aExpTot.BadTimeValueInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
                                                                    
            ' OptDlt$
            If aExpTot.DeltaEq > BAD_DOUBLE_VALUE Then
                If dTotalDeltaEq = BAD_DOUBLE_VALUE Then dTotalDeltaEq = 0
                dTotalDeltaEq = dTotalDeltaEq + aExpTot.DeltaEq
                .TextMatrix(ROW_DELTA_TOTAL, nCol) = aExpTot.DeltaEq
            Else
                .TextMatrix(ROW_DELTA_TOTAL, nCol) = STR_NA
            End If
            If aExpTot.BadDeltaEq Then bBadTotalDeltaEq = True
            
            .Cell(flexcpForeColor, ROW_DELTA_TOTAL, nCol) = IIf(aExpTot.BadDeltaEq, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
                                                                                
            ' OptDlt
            If aExpTot.DeltaInShares > BAD_DOUBLE_VALUE Then
                If dTotDeltaInShares = BAD_DOUBLE_VALUE Then dTotDeltaInShares = 0
                dTotDeltaInShares = dTotDeltaInShares + aExpTot.DeltaInShares
                
                .TextMatrix(ROW_DELTA1_TOTAL, nCol) = aExpTot.DeltaInShares
            Else
                .TextMatrix(ROW_DELTA1_TOTAL, nCol) = STR_NA
            End If
            
            If aExpTot.BadDeltaInShares Then bBadTotDeltaInShares = True
            .Cell(flexcpForeColor, ROW_DELTA1_TOTAL, nCol) = IIf(aExpTot.BadDeltaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
                                                                                                                                                                  
            ' Gma$
            If aExpTot.GammaEq > BAD_DOUBLE_VALUE Then
                If dTotGammaEq = BAD_DOUBLE_VALUE Then dTotGammaEq = 0
                dTotGammaEq = dTotGammaEq + aExpTot.GammaEq
                
                .TextMatrix(ROW_GAMMA_TOTAL, nCol) = aExpTot.GammaEq
            Else
                .TextMatrix(ROW_GAMMA_TOTAL, nCol) = STR_NA
            End If
            If aExpTot.BadGammaEq Then bBadTotGammaEq = True
            
            .Cell(flexcpForeColor, ROW_GAMMA_TOTAL, nCol) = IIf(aExpTot.BadGammaEq, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
            ' Gma$1
            If aExpTot.GammaInShares > BAD_DOUBLE_VALUE Then
                If dTotGammaInShares = BAD_DOUBLE_VALUE Then dTotGammaInShares = 0#
                dTotGammaInShares = dTotGammaInShares + aExpTot.GammaInShares
                .TextMatrix(ROW_GAMMA1_TOTAL, nCol) = aExpTot.GammaInShares
            Else
                .TextMatrix(ROW_GAMMA1_TOTAL, nCol) = STR_NA
            End If
            If aExpTot.BadGammaInShares Then bBaddTotGammaInShares = True
           
            .Cell(flexcpForeColor, ROW_GAMMA1_TOTAL, nCol) = IIf(aExpTot.BadGammaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
            
            'Vega
            If aExpTot.VegaInShares > BAD_DOUBLE_VALUE Then
                If dTotVegaInShares = BAD_DOUBLE_VALUE Then dTotVegaInShares = 0#
                dTotVegaInShares = dTotVegaInShares + aExpTot.VegaInShares
                .TextMatrix(ROW_VEGA_TOTAL, nCol) = aExpTot.VegaInShares
            Else
                .TextMatrix(ROW_VEGA_TOTAL, nCol) = STR_NA
            End If
            If aExpTot.BadVegaInShares Then bBadTotVegaInShares = True
            
            .Cell(flexcpForeColor, ROW_VEGA_TOTAL, nCol) = IIf(aExpTot.BadVegaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
            
            'Rho
            If aExpTot.RhoInShares > BAD_DOUBLE_VALUE Then
                If dTotRhoInShares = BAD_DOUBLE_VALUE Then dTotRhoInShares = 0#
                dTotRhoInShares = dTotRhoInShares + aExpTot.RhoInShares
                .TextMatrix(ROW_RHO_TOTAL, nCol) = aExpTot.RhoInShares
            Else
                .TextMatrix(ROW_RHO_TOTAL, nCol) = STR_NA
            End If
            If aExpTot.BadRhoInShares Then bBadTotRhoInShares = True
            .Cell(flexcpForeColor, ROW_RHO_TOTAL, nCol) = IIf(aExpTot.BadRhoInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
            nCol = nCol + 1
        Next
        
        nCol = .Cols - 1
        .TextMatrix(ROW_TMVAL_TOTAL, nCol) = IIf(dTotalsTimeValue > BAD_DOUBLE_VALUE, dTotalsTimeValue, STR_NA)
        .Cell(flexcpForeColor, ROW_TMVAL_TOTAL, nCol) = IIf(bBadTotalsTimeValue, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                                                                
        .TextMatrix(ROW_DELTA_TOTAL, nCol) = IIf(dTotalDeltaEq > BAD_DOUBLE_VALUE, dTotalDeltaEq, STR_NA)
        .Cell(flexcpForeColor, ROW_DELTA_TOTAL, nCol) = IIf(bBadTotalDeltaEq, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                                                                
        .TextMatrix(ROW_DELTA1_TOTAL, nCol) = IIf(dTotDeltaInShares > BAD_DOUBLE_VALUE, dTotDeltaInShares, STR_NA)
        .Cell(flexcpForeColor, ROW_DELTA1_TOTAL, nCol) = IIf(bBadTotDeltaInShares, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                                                                
                                                                
        .TextMatrix(ROW_GAMMA_TOTAL, nCol) = IIf(dTotGammaEq > BAD_DOUBLE_VALUE, dTotGammaEq, STR_NA)
        .Cell(flexcpForeColor, ROW_GAMMA_TOTAL, nCol) = IIf(bBadTotGammaEq, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                                                                
        .TextMatrix(ROW_GAMMA1_TOTAL, nCol) = IIf(dTotGammaInShares > BAD_DOUBLE_VALUE, dTotGammaInShares, STR_NA)
        .Cell(flexcpForeColor, ROW_GAMMA1_TOTAL, nCol) = IIf(bBaddTotGammaInShares, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                                                                
        .TextMatrix(ROW_VEGA_TOTAL, nCol) = IIf(dTotVegaInShares > BAD_DOUBLE_VALUE, dTotVegaInShares, STR_NA)
        .Cell(flexcpForeColor, ROW_VEGA_TOTAL, nCol) = IIf(bBadTotVegaInShares, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
            
        .TextMatrix(ROW_RHO_TOTAL, nCol) = IIf(dTotRhoInShares > BAD_DOUBLE_VALUE, dTotRhoInShares, STR_NA)
        .Cell(flexcpForeColor, ROW_RHO_TOTAL, nCol) = IIf(bBadTotRhoInShares, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                                                                
        If bAutosize Then .AutoSize 1, .Cols - 1, False, 100
        
        m_GridLock(GT_GREEKS_UNDERLYING).UnlockRedraw
    End With

    With fgUnd
        Dim iCol As Long, iRow As Long, nRows As Long, nCols As Long
        nRows = .Rows - 1
        nCols = .Cols - 1
        For iCol = GUC_SYMBOL + 1 To nCols
            nIdx = IIf((iCol - GUC_VALUE) Mod 2 <> 0, GUC_EXPIRY_ODD, GUC_EXPIRY_EVEN)
            Debug.Assert nIdx > 0
            For iRow = 1 To nRows
                If m_gdUnd.Col(nIdx).AllowNegativeDifColsForCell = True And m_gdUnd.Col(nIdx).IsItNumberFormat = True Then
                    Dim dRowValue As Double
                    dRowValue = BAD_LONG_VALUE
                    dRowValue = .TextMatrix(iRow, iCol)
                    If dRowValue <> BAD_DOUBLE_VALUE And dRowValue <> BAD_LONG_VALUE And dRowValue < 0 Then
                        .Cell(flexcpForeColor, iRow, iCol, iRow, iCol) = m_gdUnd.Col(nIdx).NegativeForeColor
                        .Cell(flexcpBackColor, iRow, iCol, iRow, iCol) = m_gdUnd.Col(nIdx).NegativeBackColor
                    End If
                End If
            Next
        Next
    End With
End Sub

Private Sub TotalsUpdateBadStatus()
    On Error Resume Next
    Dim aExpTot As EtsMmRisksLib.MmRvExpTotalAtom, nCol&, nIdx&
    
    With fgUnd
        m_GridLock(GT_GREEKS_UNDERLYING).LockRedraw
        
        nCol = GUC_VALUE + 1
        For Each aExpTot In m_View.ExpTotal
            nIdx = IIf((nCol - GUC_VALUE) Mod 2 <> 0, GUC_EXPIRY_ODD, GUC_EXPIRY_EVEN)
            
            .Cell(flexcpForeColor, ROW_TMVAL_TOTAL, nCol) = IIf(aExpTot.BadTimeValueInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
                                                                    
            .Cell(flexcpForeColor, ROW_DELTA_TOTAL, nCol) = IIf(aExpTot.BadDeltaEq, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
                                                                    
            .Cell(flexcpForeColor, ROW_DELTA1_TOTAL, nCol) = IIf(aExpTot.BadDeltaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
                                                                    
            .Cell(flexcpForeColor, ROW_GAMMA_TOTAL, nCol) = IIf(aExpTot.BadGammaEq, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
            
            .Cell(flexcpForeColor, ROW_GAMMA1_TOTAL, nCol) = IIf(aExpTot.BadGammaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
            
            .Cell(flexcpForeColor, ROW_VEGA_TOTAL, nCol) = IIf(aExpTot.BadVegaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
            
            .Cell(flexcpForeColor, ROW_RHO_TOTAL, nCol) = IIf(aExpTot.BadRhoInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                    m_gdUnd.Col(nIdx).ForeColor)
            
            nCol = nCol + 1
        Next
        
        nCol = .Cols - 1
'        .Cell(flexcpForeColor, ROW_TMVAL_TOTAL, nCol) = IIf(m_Grp.BadTimeValueInShares, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
'                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
'
        .Cell(flexcpForeColor, ROW_DELTA_TOTAL, nCol) = IIf(m_View.Grp.BadDeltaEq, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
        .Cell(flexcpForeColor, ROW_DELTA1_TOTAL, nCol) = IIf(m_View.Grp.BadOptDelta, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)

        .Cell(flexcpForeColor, ROW_GAMMA_TOTAL, nCol) = IIf(m_View.Grp.BadGammaEq, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)

        .Cell(flexcpForeColor, ROW_GAMMA1_TOTAL, nCol) = IIf(m_View.Grp.BadNetGamma, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)

        .Cell(flexcpForeColor, ROW_VEGA_TOTAL, nCol) = IIf(m_View.Grp.BadVega, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)

        .Cell(flexcpForeColor, ROW_RHO_TOTAL, nCol) = IIf(m_View.Grp.BadRho, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                                                                
        m_GridLock(GT_GREEKS_UNDERLYING).UnlockRedraw
    End With
End Sub

Private Sub UnderlyingsCalc()
    On Error Resume Next
    Dim aUnd As EtsMmRisksLib.MmRvUndAtom
    Dim OptUpdated As Long
    Dim UndUpdated As Long
    Dim FutUpdated As Long
    

    If m_View.Und.Count > 0 Then
        lblStatus.Visible = False
        imgStop.Visible = True
        imgStopDis.Visible = False
        pbProgress.Min = 0
        pbProgress.Value = 0
        pbProgress.Max = m_View.Und.Count
        pbProgress.Visible = True
        lblProcess.Caption = "Calculation..."
        lblProcess.Visible = True
        lblProcess.Refresh
        
        m_View.Calc False, GM_ALL, True, True, False, Nothing, False, g_Params.CalcModel, _
        g_Params.UseTheoVolatility, g_Params.UseTheoNoBid, _
        g_Params.UseTheoBadMarketVola, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule, OptUpdated, UndUpdated, FutUpdated, Now
        
        imgStop.Visible = False
        imgStopDis.Visible = False
        pbProgress.Visible = False
        lblProcess.Visible = False
        lblStatus.Visible = True
    End If
End Sub

Private Sub UnderlyingsUpdateVola()
    On Error Resume Next
    Dim aUnd As EtsMmRisksLib.MmRvUndAtom, aExp As EtsMmRisksLib.MmRvExpAtom
    Dim aPos As EtsMmRisksLib.MmRvPosAtom, dVola#

    For Each aUnd In m_View.Und
        For Each aExp In aUnd.ExpColl
            For Each aPos In aExp.Pos
                dVola = BAD_DOUBLE_VALUE
                dVola = aUnd.VolaSrv.OptionVola(aPos.ExpiryOV, aPos.Strike)
                aPos.Quote.Vola = dVola
            Next
        Next
    Next
End Sub


Private Sub UnderlyingsUpdate(ByVal bAutosize As Boolean)
    On Error Resume Next
    Dim nRow&, aRowData As clsGvRowData
    
    With fgUnd
        m_GridLock(GT_GREEKS_UNDERLYING).LockRedraw
        
        For nRow = 8 To .Rows - 1
            Set aRowData = .RowData(nRow)
            If Not aRowData Is Nothing Then
                If Not aRowData.Und Is Nothing Then UnderlyingUpdate nRow, False, aRowData
                Set aRowData = Nothing
            End If
        Next
        
        If bAutosize Then .AutoSize 1, .Cols - 1, False, 100
        
        m_GridLock(GT_GREEKS_UNDERLYING).UnlockRedraw
    End With
End Sub

Private Sub UnderlyingUpdate(ByVal nUndRow As Long, ByVal bAddRows As Boolean, ByRef RowData As clsGvRowData)
    On Error Resume Next
    Dim aUnd As EtsMmRisksLib.MmRvUndAtom, aExpTot As EtsMmRisksLib.MmRvExpTotalAtom, aExp As EtsMmRisksLib.MmRvExpAtom, nCol&, nIdx&
    Dim aRowData As clsGvRowData, nRow&, aSynthGreek As EtsMmRisksLib.MmRvSynthGreeksAtom, aExpSynthGreek As EtsMmRisksLib.MmRvSynthGreeksAtom
    Dim aSynthRowData As clsGvRowData
    
    With fgUnd
        m_GridLock(GT_GREEKS_UNDERLYING).LockRedraw
        
        If Not RowData Is Nothing Then
            Set aRowData = RowData
        Else
            Set aRowData = .RowData(nUndRow)
        End If
        
        If Not aRowData Is Nothing Then
            Set aUnd = aRowData.Und
            If Not aUnd Is Nothing Then
                If bAddRows Then
                    .TextMatrix(nUndRow, GUC_SYMBOL) = aUnd.Symbol
                    .TextMatrix(nUndRow, GUC_VALUE) = "TimeValue"
                
                    nRow = nUndRow + 1
                    .AddItem "", nRow
                    .TextMatrix(nRow, GUC_VALUE) = "OptDlt$"
                    .TextMatrix(nRow, GUC_SYMBOL) = " "

                    If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                        For Each aSynthGreek In aUnd.SynthGreeks
                            Set aSynthRowData = New clsGvRowData
                            aSynthRowData.SynthUndID = aSynthGreek.SynthUndID
                            nRow = nRow + 1
                            .AddItem "", nRow
                            .RowData(nRow) = aSynthRowData
                            Set aSynthRowData = Nothing

                            .TextMatrix(nRow, GUC_VALUE) = aSynthGreek.SynthUndSymbol
                            .TextMatrix(nRow, GUC_SYMBOL) = " "
                            .Cell(flexcpAlignment, nRow, GUC_VALUE) = flexAlignRightCenter
                        Next
                    End If

                    nRow = nRow + 1
                    .AddItem "", nRow
                    .TextMatrix(nRow, GUC_VALUE) = "OptDlt"
                    .TextMatrix(nRow, GUC_SYMBOL) = " "
                
                    If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                        For Each aSynthGreek In aUnd.SynthGreeks
                            Set aSynthRowData = New clsGvRowData
                            aSynthRowData.SynthUndID = aSynthGreek.SynthUndID
                            nRow = nRow + 1
                            .AddItem "", nRow
                            .RowData(nRow) = aSynthRowData
                            Set aSynthRowData = Nothing

                            .TextMatrix(nRow, GUC_VALUE) = aSynthGreek.SynthUndSymbol
                            .TextMatrix(nRow, GUC_SYMBOL) = " "
                            .Cell(flexcpAlignment, nRow, GUC_VALUE) = flexAlignRightCenter
                        Next
                    End If
                
                    nRow = nRow + 1
                    .AddItem "", nRow
                    .TextMatrix(nRow, GUC_VALUE) = "Gma$"
                    .TextMatrix(nRow, GUC_SYMBOL) = " "
                
                    If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                        For Each aSynthGreek In aUnd.SynthGreeks
                            Set aSynthRowData = New clsGvRowData
                            aSynthRowData.SynthUndID = aSynthGreek.SynthUndID
                            nRow = nRow + 1
                            .AddItem "", nRow
                            .RowData(nRow) = aSynthRowData
                            Set aSynthRowData = Nothing

                            .TextMatrix(nRow, GUC_VALUE) = aSynthGreek.SynthUndSymbol
                            .TextMatrix(nRow, GUC_SYMBOL) = " "
                            .Cell(flexcpAlignment, nRow, GUC_VALUE) = flexAlignRightCenter
                        Next
                    End If
                
                    nRow = nRow + 1
                    .AddItem "", nRow
                    .TextMatrix(nRow, GUC_VALUE) = "Gma$1"
                    .TextMatrix(nRow, GUC_SYMBOL) = " "
                
                    If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                        For Each aSynthGreek In aUnd.SynthGreeks
                            Set aSynthRowData = New clsGvRowData
                            aSynthRowData.SynthUndID = aSynthGreek.SynthUndID
                            nRow = nRow + 1
                            .AddItem "", nRow
                            .RowData(nRow) = aSynthRowData
                            Set aSynthRowData = Nothing

                            .TextMatrix(nRow, GUC_VALUE) = aSynthGreek.SynthUndSymbol
                            .TextMatrix(nRow, GUC_SYMBOL) = " "
                            .Cell(flexcpAlignment, nRow, GUC_VALUE) = flexAlignRightCenter
                        Next
                    End If
                
                    nRow = nRow + 1
                    .AddItem "", nRow
                    .TextMatrix(nRow, GUC_VALUE) = "Vega"
                    .TextMatrix(nRow, GUC_SYMBOL) = " "
                    
                    nRow = nRow + 1
                    .AddItem "", nRow
                    .TextMatrix(nRow, GUC_VALUE) = "Rho"
                    .TextMatrix(nRow, GUC_SYMBOL) = " "
                    
                End If
                
                nCol = GUC_VALUE + 1
                For Each aExpTot In m_View.ExpTotal
                    Set aExp = aUnd.ExpColl(aExpTot.ExpiryMonth)
                    nRow = nUndRow
                    nIdx = IIf((nCol - GUC_VALUE) Mod 2 <> 0, GUC_EXPIRY_ODD, GUC_EXPIRY_EVEN)
                    
                    If Not aExp Is Nothing Then
                        .TextMatrix(nRow, nCol) = IIf(aExp.TimeValueInShares > BAD_DOUBLE_VALUE, aExp.TimeValueInShares, STR_NA)
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadTimeValueInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                        
                        ' OptDlt$
                        .TextMatrix(nRow, nCol) = IIf(aExp.DeltaEq > BAD_DOUBLE_VALUE, aExp.DeltaEq, STR_NA)
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadDeltaEq, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                        
                        If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                            For Each aSynthGreek In aUnd.SynthGreeks
                                If aExp.HasSynth And Not aExp.SynthGreek Is Nothing Then
                                    Set aExpSynthGreek = aExp.SynthGreek(aSynthGreek.SynthUndID)
                                    If Not aExpSynthGreek Is Nothing Then
                                        .TextMatrix(nRow, nCol) = IIf(aExpSynthGreek.DeltaInMoney > BAD_DOUBLE_VALUE, aExpSynthGreek.DeltaInMoney, STR_NA)
                                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExpSynthGreek.BadDeltaInMoney, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                                m_gdUnd.Col(nIdx).ForeColor)
                                        Set aExpSynthGreek = Nothing
                                    End If
                                End If
                                nRow = nRow + 1
                            Next
                        End If
                        
                        ' OptDlt
                        .TextMatrix(nRow, nCol) = IIf(aExp.DeltaInShares > BAD_DOUBLE_VALUE, aExp.DeltaInShares, STR_NA)
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadDeltaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                        
                        If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                            For Each aSynthGreek In aUnd.SynthGreeks
                                If aExp.HasSynth And Not aExp.SynthGreek Is Nothing Then
                                    Set aExpSynthGreek = aExp.SynthGreek(aSynthGreek.SynthUndID)
                                    If Not aExpSynthGreek Is Nothing Then
                                        .TextMatrix(nRow, nCol) = IIf(aExpSynthGreek.DeltaInShares > BAD_DOUBLE_VALUE, aExpSynthGreek.DeltaInShares, STR_NA)
                                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExpSynthGreek.BadNetDelta, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                                m_gdUnd.Col(nIdx).ForeColor)
                                        Set aExpSynthGreek = Nothing
                                    End If
                                End If
                                nRow = nRow + 1
                            Next
                        End If
                        
                        ' Gma$
                        .TextMatrix(nRow, nCol) = IIf(aExp.GammaEq > BAD_DOUBLE_VALUE, aExp.GammaEq, STR_NA)
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadGammaEq, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                        
                        If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                            For Each aSynthGreek In aUnd.SynthGreeks
                                If aExp.HasSynth And Not aExp.SynthGreek Is Nothing Then
                                    Set aExpSynthGreek = aExp.SynthGreek(aSynthGreek.SynthUndID)
                                    If Not aExpSynthGreek Is Nothing Then
                                        .TextMatrix(nRow, nCol) = IIf(aExpSynthGreek.NetGamma > BAD_DOUBLE_VALUE, aExpSynthGreek.NetGamma, STR_NA)
                                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExpSynthGreek.BadNetGamma, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                                m_gdUnd.Col(nIdx).ForeColor)
                                        Set aExpSynthGreek = Nothing
                                    End If
                                End If
                                nRow = nRow + 1
                            Next
                        End If
                    
                        ' Gma$1
                        .TextMatrix(nRow, nCol) = IIf(aExp.GammaInShares > BAD_DOUBLE_VALUE, aExp.GammaInShares, STR_NA)
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadGammaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                        
                        If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                            For Each aSynthGreek In aUnd.SynthGreeks
                                If aExp.HasSynth And Not aExp.SynthGreek Is Nothing Then
                                    Set aExpSynthGreek = aExp.SynthGreek(aSynthGreek.SynthUndID)
                                    If Not aExpSynthGreek Is Nothing Then
                                        .TextMatrix(nRow, nCol) = IIf(aExpSynthGreek.GammaInShares > BAD_DOUBLE_VALUE, aExpSynthGreek.GammaInShares, STR_NA)
                                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExpSynthGreek.BadGamma, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                                m_gdUnd.Col(nIdx).ForeColor)
                                        Set aExpSynthGreek = Nothing
                                    End If
                                End If
                                nRow = nRow + 1
                            Next
                        End If
                    
                        .TextMatrix(nRow, nCol) = IIf(aExp.VegaInShares > BAD_DOUBLE_VALUE, aExp.VegaInShares, STR_NA)
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadVegaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                                                                                
                        nRow = nRow + 1
                        
                        .TextMatrix(nRow, nCol) = IIf(aExp.RhoInShares > BAD_DOUBLE_VALUE, aExp.RhoInShares, STR_NA)
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadRhoInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                    End If
                
                    nCol = nCol + 1
                Next
                
                nCol = .Cols - 1
                nRow = nUndRow
                .TextMatrix(nRow, nCol) = IIf(aUnd.TimeValueInShares > BAD_DOUBLE_VALUE, aUnd.TimeValueInShares, STR_NA)
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadTimeValue, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                nRow = nRow + 1

                ' OptDlt$
                .TextMatrix(nRow, nCol) = IIf(aUnd.OptDeltaEq > BAD_DOUBLE_VALUE, aUnd.OptDeltaEq, STR_NA)
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadOptDeltaEq, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                nRow = nRow + 1

                If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                    For Each aSynthGreek In aUnd.SynthGreeks
                        .TextMatrix(nRow, nCol) = IIf(aSynthGreek.DeltaInMoney > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInMoney, STR_NA)
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadDeltaInMoney, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                        nRow = nRow + 1
                    Next
                End If

                ' OptDlt
                .TextMatrix(nRow, nCol) = IIf(aUnd.OptDelta > BAD_DOUBLE_VALUE, aUnd.OptDelta, STR_NA)
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadOptDelta, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                nRow = nRow + 1

                If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                    For Each aSynthGreek In aUnd.SynthGreeks
                        .TextMatrix(nRow, nCol) = IIf(aSynthGreek.DeltaInShares > BAD_DOUBLE_VALUE, aSynthGreek.DeltaInShares, STR_NA)
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadDelta, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                        nRow = nRow + 1
                    Next
                End If

                ' Gma$
                .TextMatrix(nRow, nCol) = IIf(aUnd.GammaEq > BAD_DOUBLE_VALUE, aUnd.GammaEq, STR_NA)
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadGammaEq, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                nRow = nRow + 1

                If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                    For Each aSynthGreek In aUnd.SynthGreeks
                        .TextMatrix(nRow, nCol) = IIf(aSynthGreek.NetGamma > BAD_DOUBLE_VALUE, aSynthGreek.NetGamma, STR_NA)
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadNetGamma, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                        nRow = nRow + 1
                    Next
                End If

                ' Gma$1
                .TextMatrix(nRow, nCol) = IIf(aUnd.Gamma > BAD_DOUBLE_VALUE, aUnd.Gamma, STR_NA)
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadGamma, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                
                nRow = nRow + 1
                                

                If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                    For Each aSynthGreek In aUnd.SynthGreeks
                        .TextMatrix(nRow, nCol) = IIf(aSynthGreek.GammaInShares > BAD_DOUBLE_VALUE, aSynthGreek.GammaInShares, STR_NA)
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadDelta, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                        nRow = nRow + 1
                    Next
                End If

                .TextMatrix(nRow, nCol) = IIf(aUnd.Vega > BAD_DOUBLE_VALUE, aUnd.Vega, STR_NA)
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadVega, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                
                nRow = nRow + 1
                
                ' Rho
                .TextMatrix(nRow, nCol) = IIf(aUnd.Rho > BAD_DOUBLE_VALUE, aUnd.Rho, STR_NA)
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadRho, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                
                nRow = nRow + 1
                
                
                Set aUnd = Nothing
            End If
        End If
        
        m_GridLock(GT_GREEKS_UNDERLYING).UnlockRedraw
    End With
End Sub

Private Sub UnderlyingsUpdateBadStatus()
    On Error Resume Next
    Dim nRow&, aRowData As clsGvRowData
    
    With fgUnd
        m_GridLock(GT_GREEKS_UNDERLYING).LockRedraw
        
        For nRow = 8 To .Rows - 1
            Set aRowData = .RowData(nRow)
            If Not aRowData Is Nothing Then
                If Not aRowData.Und Is Nothing Then UnderlyingUpdateBadStatus nRow, aRowData
                Set aRowData = Nothing
            End If
        Next
        
        m_GridLock(GT_GREEKS_UNDERLYING).UnlockRedraw
    End With
End Sub

Private Sub UnderlyingUpdateBadStatus(ByVal nUndRow As Long, ByRef RowData As clsGvRowData)
    On Error Resume Next
    Dim aUnd As EtsMmRisksLib.MmRvUndAtom, aExpTot As EtsMmRisksLib.MmRvExpTotalAtom, aExp As EtsMmRisksLib.MmRvExpAtom, nCol&, nIdx&
    Dim aRowData As clsGvRowData, nRow&, aSynthGreek As EtsMmRisksLib.MmRvSynthGreeksAtom, aExpSynthGreek As EtsMmRisksLib.MmRvSynthGreeksAtom
    
    With fgUnd
        m_GridLock(GT_GREEKS_UNDERLYING).LockRedraw
        
        If Not RowData Is Nothing Then
            Set aRowData = RowData
        Else
            Set aRowData = .RowData(nUndRow)
        End If
        
        If Not aRowData Is Nothing Then
            Set aUnd = aRowData.Und
            If Not aUnd Is Nothing Then
                
                nCol = GUC_VALUE + 1
                For Each aExpTot In m_View.ExpTotal
                    Set aExp = aUnd.ExpColl(aExpTot.ExpiryMonth)
                    nRow = nUndRow
                    nIdx = IIf((nCol - GUC_VALUE) Mod 2 <> 0, GUC_EXPIRY_ODD, GUC_EXPIRY_EVEN)
                    
                    If Not aExp Is Nothing Then
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadTimeValueInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                        
                        ' OptDlt$
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadDeltaEq, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                        
                        If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                            For Each aSynthGreek In aUnd.SynthGreeks
                                If aExp.HasSynth And Not aExp.SynthGreek Is Nothing Then
                                    Set aExpSynthGreek = aExp.SynthGreek(aSynthGreek.SynthUndID)
                                    If Not aExpSynthGreek Is Nothing Then
                                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExpSynthGreek.BadNetDelta, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                                m_gdUnd.Col(nIdx).ForeColor)
                                        Set aExpSynthGreek = Nothing
                                    End If
                                End If
                                nRow = nRow + 1
                            Next
                        End If
                        
                        ' OptDlt
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadDeltaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                        
                        If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                            For Each aSynthGreek In aUnd.SynthGreeks
                                If aExp.HasSynth And Not aExp.SynthGreek Is Nothing Then
                                    Set aExpSynthGreek = aExp.SynthGreek(aSynthGreek.SynthUndID)
                                    If Not aExpSynthGreek Is Nothing Then
                                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExpSynthGreek.BadDelta, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                                m_gdUnd.Col(nIdx).ForeColor)
                                        Set aExpSynthGreek = Nothing
                                    End If
                                End If
                                nRow = nRow + 1
                            Next
                        End If
                        
                        ' Gma$
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadGammaEq, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                        
                        If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                            For Each aSynthGreek In aUnd.SynthGreeks
                                If aExp.HasSynth And Not aExp.SynthGreek Is Nothing Then
                                    Set aExpSynthGreek = aExp.SynthGreek(aSynthGreek.SynthUndID)
                                    If Not aExpSynthGreek Is Nothing Then
                                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExpSynthGreek.BadNetGamma, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                                m_gdUnd.Col(nIdx).ForeColor)
                                        Set aExpSynthGreek = Nothing
                                    End If
                                End If
                                nRow = nRow + 1
                            Next
                        End If
                    
                        ' Gma$1
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadGammaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                        
                        If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                            For Each aSynthGreek In aUnd.SynthGreeks
                                If aExp.HasSynth And Not aExp.SynthGreek Is Nothing Then
                                    Set aExpSynthGreek = aExp.SynthGreek(aSynthGreek.SynthUndID)
                                    If Not aExpSynthGreek Is Nothing Then
                                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExpSynthGreek.BadGamma, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                                m_gdUnd.Col(nIdx).ForeColor)
                                        Set aExpSynthGreek = Nothing
                                    End If
                                End If
                                nRow = nRow + 1
                            Next
                        End If
                    
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aExp.BadVegaInShares, m_gdUnd.Col(nIdx).ForeColorAlt1, _
                                                                                m_gdUnd.Col(nIdx).ForeColor)
                        nRow = nRow + 1
                    End If
                
                    nCol = nCol + 1
                Next
                
                nCol = .Cols - 1
                nRow = nUndRow
'                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadTimeValueInShares, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
'                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                nRow = nRow + 1
                
                ' OptDlt$
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadDeltaEq, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                nRow = nRow + 1
                
                If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                    For Each aSynthGreek In aUnd.SynthGreeks
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadNetDelta, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                        nRow = nRow + 1
                    Next
                End If
                
                ' OptDlt
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadDeltaEq, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                nRow = nRow + 1
                
                If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                    For Each aSynthGreek In aUnd.SynthGreeks
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadDeltaInMoney, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                        nRow = nRow + 1
                    Next
                End If
                
                ' Gma$
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadGammaEq, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                nRow = nRow + 1
                
                If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                    For Each aSynthGreek In aUnd.SynthGreeks
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadGamma, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                        nRow = nRow + 1
                    Next
                End If
            
                 'Gma$ 1
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadGammaEq, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                nRow = nRow + 1
                
                If aUnd.HasSynthetic And Not aUnd.SynthGreeks Is Nothing Then
                    For Each aSynthGreek In aUnd.SynthGreeks
                        .Cell(flexcpForeColor, nRow, nCol) = IIf(aSynthGreek.BadNetGamma, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                                m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                        nRow = nRow + 1
                    Next
                End If
            
                .Cell(flexcpForeColor, nRow, nCol) = IIf(aUnd.BadVega, m_gdUnd.Col(GUC_SYM_TOTAL).ForeColorAlt1, _
                                                                        m_gdUnd.Col(GUC_SYM_TOTAL).ForeColor)
                nRow = nRow + 1
                
                Set aUnd = Nothing
            End If
        End If
        
        m_GridLock(GT_GREEKS_UNDERLYING).UnlockRedraw
    End With
End Sub

Private Sub RequestLastQuotes()
    On Error GoTo EH
    Dim i&, nCount&, aParam As PRICEPROVIDERSLib.QuoteUpdateParams, aUnd As EtsMmRisksLib.MmRvUndAtom
    Dim aReq As EtsMmRisksLib.MmRvReqAtom
    Dim qup As QuoteUpdateParams
    
    
    If Not PriceProvider Is Nothing Then
        Debug.Assert Not m_bLastQuoteReqNow
        nCount = m_View.QuoteReqsAll.Count
        
        If nCount > 0 Then
            m_bInProc = True
            m_bLastQuoteReqNow = True
            AdjustState
            
            m_nLastQuoteReqCount = nCount
            m_nLastQuoteReqDone = 0&
            
            pbProgress.Min = 0
            pbProgress.Value = 0
            pbProgress.Max = m_nLastQuoteReqCount
            
            imgStop.Visible = True
            imgStopDis.Visible = False
            DoEvents
            
'            If Not m_bGroupRequest Then
                m_nLastQuoteGroupReqCount = 0&
                m_nLastQuoteGroupReqDone = 0&
                
                Dim sRequests() As QuoteUpdateParams
                ReDim sRequests(m_View.QuoteReqsAll.Count - 1)
                Dim iRequest As Integer
                Dim aBatchPriceInfo As PRICEPROVIDERSLib.IBatchPriceProvider
                iRequest = 0
                For Each aReq In m_View.QuoteReqsAll
                    If Not m_bLastQuoteReqNow Then Exit For
                    sRequests(iRequest) = aReq.GetQuoteUpdateParam
                    iRequest = iRequest + 1
                    If iRequest = 100 Then
                        pbProgress.Min = 0
                    End If
                Next
                Set aBatchPriceInfo = PriceProvider
                aBatchPriceInfo.RequestMultipleQuotes sRequests
                
                
'            Else
'                m_nLastQuoteGroupReqCount = 0&
'                m_nLastQuoteGroupReqDone = 0&
'
'                For Each aUnd In m_Grp.Und
'                    If Not m_bLastQuoteReqNow Then Exit For
'                    If aUnd.ID <> USD_ID Then
'                        aParam.Symbol = aUnd.Symbol
'                        aParam.Exchange = ""
'
'                        aParam.Type = IIf(aUnd.UndType = enCtStock, enSTK, enIDX)
'                        m_nLastQuoteGroupReqCount = m_nLastQuoteGroupReqCount + 1
'                        PriceProvider.RequestLastQuote aParam
'
'                        If aUnd.Expiry.Count > 0 Then
'                            aParam.Type = IIf(aUnd.UndType = enCtStock, enGrSTK, enGrIDX)
'                            m_nLastQuoteGroupReqCount = m_nLastQuoteGroupReqCount + 1
'                            m_GroupPriceProvider.RequestGroup aParam, enGroupRequestLastQuote
'                        End If
'                    End If
'                    DoEvents
'                Next
'            End If
            
            m_bInProc = False
            AdjustState
        Else
            pbProgress.Visible = False
            lblStatus.Visible = True
            lblProcess.Visible = False
            imgStop.Visible = False
            imgStopDis.Visible = False
        End If
    Else
        If Not m_bShutDown Then gCmn.MyMsgBox m_frmOwner, "You are in offline mode now.", vbExclamation
    End If
    
    Exit Sub
EH:
    m_bLastQuoteReqNow = False
    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to request last quotes."
    On Error Resume Next
    PriceProvider.CancelLastQuote
'    If m_bGroupRequest Then
'        m_GroupPriceProvider.CancelGroup
'    End If
    pbProgress.Visible = False
    lblStatus.Visible = True
    lblProcess.Visible = False
    lblProcess.Caption = ""
    imgStop.Visible = False
    imgStopDis.Visible = False
    m_bInProc = False
    AdjustState
End Sub

Private Sub PriceProvider_OnError(ByVal ErrorNumber As PRICEPROVIDERSLib.ErrorNumberEnum, ByVal Description As String, ByVal ReqType As PRICEPROVIDERSLib.RequestsTypeEnum, ByVal Request As Variant)
    On Error Resume Next
    Dim sKey$, bFinished As Boolean, bCalcGreeks As Boolean
    Dim aReq As EtsMmRisksLib.MmRvReqAtom
    bFinished = False
    bCalcGreeks = False
    
    On Error Resume Next
    

    If Not Request Is Nothing And ReqType = enRequestLastQuote Then
        If m_bLastQuoteReqNow Then
            If PpIsNonGroupReqType(Request.Type) Then
                sKey = CStr(PpInstrumentTypeContractType(Request.Type)) & "_" & Request.Symbol
                
                If (Len(Request.Exchange) > 0) Then
                    sKey = sKey & "." & Request.Exchange
                End If
                
 '               sKey = CStr(IIf(Request.Type = enOPT, enCtOption, IIf(Request.Type = enSTK, enCtStock, enCtIndex))) & "_" & Request.Symbol
                
                Set aReq = m_View.QuoteReqsAll(sKey)
                If Not aReq Is Nothing Then
                    LogEvent EVENT_WARNING, Request.Symbol & ": " & Description
                
                    m_nLastQuoteReqDone = m_nLastQuoteReqDone + 1
                    IncProgress pbProgress
                    
                    bFinished = (m_nLastQuoteReqDone = m_nLastQuoteReqCount)
                End If
            ElseIf PpIsGroupReqType(Request.Type) Then
                LogEvent EVENT_WARNING, Request.Symbol & " options: " & Description
                m_nLastQuoteGroupReqDone = m_nLastQuoteGroupReqDone + 1
                bFinished = (m_nLastQuoteGroupReqCount = m_nLastQuoteGroupReqDone)
            End If
            
            If bFinished Then
                m_bLastQuoteReqNow = False
                
                PriceProvider.CancelLastQuote
'                If m_bGroupRequest Then
'                    m_GroupPriceProvider.CancelGroup
'                End If
                
                m_bInProc = True
                AdjustState
                
                UnderlyingsUpdateVola
                UnderlyingsCalc
                UnderlyingsUpdate False
                TotalsUpdate True
                
                m_bInProc = False
                AdjustState
                
                pbProgress.Visible = False
                lblStatus.Visible = True
                lblProcess.Visible = False
                imgStop.Visible = False
                imgStopDis.Visible = False
            End If
        Else
            Debug.Assert False
        End If
    
    Else
        LogEvent EVENT_ERROR, Description
    End If
End Sub

Private Sub PriceProvider_OnLastQuote(Params As PRICEPROVIDERSLib.QuoteUpdateParams, Results As PRICEPROVIDERSLib.QuoteUpdateInfo)
    On Error Resume Next
    If Not m_bLastQuoteReqNow Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "PriceProvider_OnLastQuote Started Symbol: " & Params.Symbol & ", Exchange:  " & Params.Exchange & ", Type:  " & Params.Type, m_frmOwner.GetCaption

    Dim sKey$, aReq As EtsMmRisksLib.MmRvReqAtom, dPriceBid#, dPriceAsk#, dPriceLast#, dNetChange#, nLotSize&
    Dim aUnd As EtsMmRisksLib.MmRvUndAtom, nTime&, aFut As EtsMmRisksLib.MmRvFutAtom
    Dim bFinished As Boolean, bCalcGreeks As Boolean
    Dim nOperation&, nLogTime&
    Dim aReqUndData As EtsMmRisksLib.IMmRvAggregationDataAtom
    Dim aReqIdxData As EtsMmRisksLib.IMmRvAggregationDataAtom
    
    
    bFinished = False
    If PpIsNonGroupReqType(Params.Type) Then
        sKey = CStr(PpInstrumentTypeContractType(Params.Type)) & "_" & Params.Symbol
        If (Len(Params.Exchange) > 0) Then
            sKey = sKey & "." & Params.Exchange
        End If
        
        Set aReq = m_View.QuoteReqsAll(sKey)
        If Not aReq Is Nothing Then
            dPriceBid = Results.BidPrice
            dPriceAsk = Results.AskPrice
            dPriceLast = Results.LastPrice
            dNetChange = Results.NetChange
            
            If Not aReq.IndexOnly Then
                If Not aReq.Pos Is Nothing Then
                    If dPriceBid > BAD_DOUBLE_VALUE Then aReq.Pos.Quote.price.Bid = dPriceBid
                    If dPriceAsk > BAD_DOUBLE_VALUE Then aReq.Pos.Quote.price.Ask = dPriceAsk
                    If dPriceLast > BAD_DOUBLE_VALUE Then aReq.Pos.Quote.price.Last = dPriceLast
                    If dNetChange <> BAD_DOUBLE_VALUE Then aReq.Pos.Quote.price.NetChange = dNetChange
                End If
                
                If Params.Type <> enOPT Then
                    Set aReqUndData = aReq.Und
                    
                    If Params.Type = enSTK Or Params.Type = enIDX Then
                        If dPriceBid > BAD_DOUBLE_VALUE Then aReqUndData.price.Bid = dPriceBid
                        If dPriceAsk > BAD_DOUBLE_VALUE Then aReqUndData.price.Ask = dPriceAsk
                        If dPriceLast > BAD_DOUBLE_VALUE Then aReqUndData.price.Last = dPriceLast
                        If dNetChange <> BAD_DOUBLE_VALUE Then aReq.Und.price.NetChange = dNetChange
                        
                        Debug.Assert (Not aReq.Und.UndPriceProfile Is Nothing)
                        If (aReq.Und.price.IsUseManualActive) Then
                            aReq.Und.VolaSrv.UnderlyingPrice = aReq.Und.price.Active
                        Else
                            aReq.Und.VolaSrv.UnderlyingPrice = aReq.Und.UndPriceProfile.GetUndPriceMid(aReqUndData.price.Bid, aReqUndData.price.Ask, aReqUndData.price.Last, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)
                        End If
                    
                        If m_View.Idx.ID = aReq.Und.ID Then
                            Set aReqIdxData = m_View.Idx
                            If dPriceBid > BAD_DOUBLE_VALUE Then aReqIdxData.price.Bid = dPriceBid
                            If dPriceAsk > BAD_DOUBLE_VALUE Then aReqIdxData.price.Ask = dPriceAsk
                            If dPriceLast > BAD_DOUBLE_VALUE Then aReqIdxData.price.Last = dPriceLast
                            If dNetChange <> BAD_DOUBLE_VALUE Then m_View.Idx.price.NetChange = dNetChange
                        End If
                        
                    ElseIf Params.Type = enFUT Then
                        If Not aReq.Pos Is Nothing Then
                            Set aFut = aReq.Pos.Fut
                        ElseIf Not aReq.Fut Is Nothing Then
                            Set aFut = aReq.Fut
                        End If
                    
                        If Not aFut Is Nothing Then
                            If dPriceBid > BAD_DOUBLE_VALUE Then aFut.price.Bid = dPriceBid
                            If dPriceAsk > BAD_DOUBLE_VALUE Then aFut.price.Ask = dPriceAsk
                            If dPriceLast > BAD_DOUBLE_VALUE Then aFut.price.Last = dPriceLast
                            'If dNetChange <> BAD_DOUBLE_VALUE Then aFut.NetChange = dNetChange

                            Set aFut = Nothing
                        End If
                    End If
                End If
            Else
                Debug.Assert m_View.Idx.ID = aReq.Und.ID
                If m_View.Idx.ID = aReq.Und.ID Then
                    Set aReqIdxData = m_View.Idx
                    If dPriceBid > BAD_DOUBLE_VALUE Then aReqIdxData.price.Bid = dPriceBid
                    If dPriceAsk > BAD_DOUBLE_VALUE Then aReqIdxData.price.Ask = dPriceAsk
                    If dPriceLast > BAD_DOUBLE_VALUE Then aReqIdxData.price.Last = dPriceLast
                     If dNetChange <> BAD_DOUBLE_VALUE Then m_View.Idx.price.NetChange = dNetChange
                    
                End If
            End If
        
            m_nLastQuoteReqDone = m_nLastQuoteReqDone + 1
            IncProgress pbProgress
        
            bFinished = (m_nLastQuoteReqDone = m_nLastQuoteReqCount)
        End If
    End If

    If bFinished Then
        m_bLastQuoteReqNow = False
        
        PriceProvider.CancelLastQuote
'        If m_bGroupRequest Then
'            m_GroupPriceProvider.CancelGroup
'        End If
        
        m_bInProc = True
        AdjustState
        
        UnderlyingsUpdateVola
        UnderlyingsCalc
        UnderlyingsUpdate False
        TotalsUpdate True
        
        m_bInProc = False
        AdjustState
        
        pbProgress.Visible = False
        lblStatus.Visible = True
        lblProcess.Visible = False
        imgStop.Visible = False
        imgStopDis.Visible = False
    End If
    Set aReq = Nothing
End Sub

'Private Sub UnderlyingsAdjustRates()
'    On Error Resume Next
'    Dim aUnd As EtsMmRisksLib.MmRvUndAtom, aExp As EtsMmRisksLib.MmRvExpAtom
'    Dim cPosThreshold@, bUseMidRates As Boolean, dPos#
'
'    For Each aUnd In m_View.Und
'        If aUnd.ExpColl.Count > 0 Then
'            dPos = g_UnderlyingAll(aUnd.ID).UndPosForRates ' aUnd.UndPos
'
'            If GetIrRuleType = enRateBasedOnPosition Then 'And dPos > BAD_DOUBLE_VALUE Then
'                cPosThreshold = Abs(GetPosThreshold)
'                bUseMidRates = (cPosThreshold = 0 Or cPosThreshold <> 0 And Abs(dPos) <= cPosThreshold)
'            Else
'                bUseMidRates = True
'            End If
'
'            For Each aExp In aUnd.ExpColl
'                If bUseMidRates Then
'                    If Not aUnd.IsHTB Then
'                        aExp.Rate = GetNeutralRate(Date, aExp.Expiry)
'                    Else
'                        aExp.Rate = GetNeutralHTBRate(Date, aExp.Expiry)
'                    End If
'                Else
'                    If dPos < 0 Then
'                        If Not aUnd.IsHTB Then
'                            aExp.Rate = GetShortRate(Date, aExp.Expiry)
'                        Else
'                            aExp.Rate = GetHTBRate(Date, aExp.Expiry)
'                        End If
'                    Else
'                        aExp.Rate = GetLongRate(Date, aExp.Expiry)
'                    End If
'                End If
'            Next
'        End If
'    Next
'End Sub

Public Sub NewUnderlyingAdded(ByVal nNewUndID As Long)
    On Error Resume Next
    Dim aUnd As EtsGeneralLib.UndAtom
     Set aUnd = g_Underlying(nNewUndID)
    If Not aUnd Is Nothing Then
        If aUnd.IsTraderContract Then FilterUpdateValue False, GFC_SYMBOL
    End If
End Sub

Public Sub NewUnderlyingGroupAdded(ByVal nNewUndGroupID As Long)
    On Error Resume Next
    FilterUpdateValue False, GFC_GROUPS
End Sub

Public Sub NewStrategyAdded(ByVal nStrategyID As Long)
    On Error Resume Next
    FilterUpdateValue False, GFC_STRATEGY
End Sub

Private Sub UpdateMenu()
    On Error Resume Next
    mnuCtxRefresh.Enabled = m_View.Grp.ID <> 0 And Not m_bInProc And Not m_bLastQuoteReqNow
End Sub

Private Sub AdjustState()
    On Error Resume Next
    UpdateMenu
    RaiseEvent OnStateChange
End Sub

Private Sub AdjustCaption()
    On Error Resume Next
    RaiseEvent OnSetCaption
End Sub

Public Function GetCaption() As String
    On Error Resume Next
    Dim sCaption$
    
    sCaption = ""
    If m_View.Grp.ID <> 0 Then sCaption = sCaption & m_View.Grp.Name & " - "
    
    sCaption = sCaption & "Greeks"
    
    GetCaption = sCaption
End Function

Public Function GetShortCaption() As String
    On Error Resume Next
    If m_View.Grp.ID <> 0 Then
        GetShortCaption = m_View.Grp.Name
    Else
        GetShortCaption = "<Empty>"
    End If
End Function

Public Property Get Filter() As EtsGeneralLib.EtsFilterData
    Set Filter = m_aFilter
End Property


Public Property Get InProc() As Boolean
    InProc = m_bInProc
End Property

Public Property Get LastQuoteReqNow() As Boolean
    LastQuoteReqNow = m_bLastQuoteReqNow
End Property

Public Sub Refresh()
    On Error Resume Next
    tmrShow.Enabled = True
End Sub

Public Function Group() As EtsMmRisksLib.MmRvGrpAtom
    On Error Resume Next
    Set Group = m_View.Grp
End Function

Public Function CurUnderlyingID() As Long
    On Error Resume Next
    Dim aRowData As clsGvRowData, nRow&

    CurUnderlyingID = 0
    
    If m_aFilter.Data(GFC_SYMBOL) > 0 Then
        CurUnderlyingID = m_aFilter.Data(GFC_SYMBOL)
    Else
        With fgUnd
            If .Row > 0 Then
                nRow = .Row
                
                Do While CurUnderlyingID = 0 And nRow >= 7
                    Set aRowData = .RowData(nRow)
                    If Not aRowData Is Nothing Then
                        If Not aRowData.Und Is Nothing Then
                            CurUnderlyingID = aRowData.Und.ID
'                        Else
'                            CurUnderlyingID = aRowData.SynthUndID
                        End If
                        Set aRowData = Nothing
                    End If
                    nRow = nRow - 1
                Loop
            End If
        End With
    End If
End Function

Private Sub UserControl_Hide()
    On Error Resume Next
    m_bDataLoad = False
    m_bLastQuoteReqNow = False
End Sub

Private Sub UserControl_Resize()
    On Error Resume Next
    If gCmn Is Nothing Then Exit Sub

    With fgFlt
        .Top = 0
        .Left = 0
        .Height = .RowHeight(0) + (.Rows - 1) * .RowHeight(1) + ScaleY(.GridLineWidth * 2, vbPixels, vbTwips)
        .Width = ScaleWidth
    End With

    With fgUnd
        .Left = 0
        .Top = fgFlt.Height + GRID_VERT_SPACE
        .Width = ScaleWidth
        .Height = ScaleHeight - .Top
    End With
End Sub

Private Sub UserControl_Terminate()
    On Error Resume Next
    Term
End Sub

Public Sub Term()
    On Error Resume Next
    If gCmn Is Nothing Then Exit Sub
    m_bShutDown = True
    
    m_bDataLoad = False
    m_bLastQuoteReqNow = False
    m_bInProc = False
    
    Set frmLayout = Nothing
    Set TradeChannel = Nothing
    Set VolaSource = Nothing
    
    If Not PriceProvider Is Nothing Then
        PriceProvider.CancelLastQuote
'        If m_bGroupRequest Then
'            m_GroupPriceProvider.CancelGroup
'        End If
        Set PriceProvider = Nothing
    End If
'    Set m_GroupPriceProvider = Nothing
    
    Set geUnd = Nothing
    Set m_View = Nothing
    
    Set pbProgress = Nothing
    Set lblProcess = Nothing
    Set lblStatus = Nothing
    Set lblValue = Nothing
    Set imgStop = Nothing
    Set imgStopDis = Nothing
    Set aParams = Nothing
End Sub

Public Sub SaveToFile(aStorage As clsSettingsStorage, ByVal sKey As String)
    On Error GoTo EH
    Dim i&
    If Len(sKey) > 0 Then sKey = "." & sKey

    ' common info
    For i = GFC_SYMBOL To GFC_LAST_COLUMN
        aStorage.SetLongValue "GreekFlt" & sKey, "Filter" & CStr(i), m_aFilter.Data(i)
    Next
    
    m_gdFlt.WriteToStorage "GreekFltGrid" & sKey, aStorage, False
    m_gdUnd.WriteToStorage "GreekUndGrid" & sKey, aStorage
    Exit Sub
EH:
    gCmn.ErrorHandler ""
End Sub

Public Sub OpenFromFile(aStorage As clsSettingsStorage, ByVal sKey As String)
    On Error GoTo EH
    Dim i&
    If Len(sKey) > 0 Then sKey = "." & sKey
    
    ' common info
    For i = GFC_SYMBOL To GFC_LAST_COLUMN
        m_aFilter.Data(i) = aStorage.GetLongValue("GreekFlt" & sKey, "Filter" & CStr(i), m_aFilter.Data(i))
    Next
    
    
    m_gdFlt.ReadFromStorage "GreekFltGrid" & sKey, aStorage, False
    m_gdUnd.ReadFromStorage "GreekUndGrid" & sKey, aStorage
    
    FilterUpdateAll
    tmrShow.Enabled = True
    Exit Sub
EH:
    gCmn.ErrorHandler ""
End Sub

Public Sub PrintView()
'    On Error Resume Next
'    Screen.MousePointer = vbHourglass
'    frmPrintPreview.Execute m_frmOwner, m_View.Grp.Name & " Greeks", "Greeks", fgFlt, fgUnd
'    Screen.MousePointer = vbDefault
End Sub

Public Sub CustomizeFltGridLayout()
    On Error Resume Next
    If Not frmLayout Is Nothing Then
        frmLayout.Execute GT_GREEKS_FILTER, GFC_SYMBOL, GFC_LAST_COLUMN, m_gdFlt, m_frmOwner
    End If
End Sub

Public Sub CustomizeUndGridLayout()
    On Error Resume Next
    If Not frmLayout Is Nothing Then
        frmLayout.Execute GT_GREEKS_UNDERLYING, GUC_SYMBOL, GUC_COLUMN_COUNT, m_gdUnd, m_frmOwner
    End If
End Sub

Private Sub ResetMenuData()
    On Error Resume Next
    m_enMenuGrid = -1
    m_nMenuGridCol = -1
    m_nMenuGridRow = -1
    m_nMenuGridCols = 0
    m_nMenuGridRows = 0
End Sub

Private Sub frmLayout_OnApply(ByVal enGridType As GridTypeEnum, gdGrid As clsGridDef)
    On Error Resume Next
    SetGridLayout enGridType, gdGrid
End Sub

Private Sub frmLayout_OnOK(ByVal enGridType As GridTypeEnum, gdGrid As clsGridDef)
    On Error Resume Next
    Screen.MousePointer = vbHourglass
    SetGridLayout enGridType, gdGrid
    Screen.MousePointer = vbDefault
End Sub

Public Sub SetGridLayout(ByVal enGridType As GridTypeEnum, gdGrid As clsGridDef)
    On Error Resume Next
    
    Select Case enGridType
        Case GT_GREEKS_FILTER
            gdGrid.CopyTo m_gdFlt
            
            m_GridLock(GT_GREEKS_FILTER).LockRedraw
            FormatFltGrid
            FormatFltColumns
            m_GridLock(GT_GREEKS_FILTER).UnlockRedraw
            
        Case GT_GREEKS_UNDERLYING
            gdGrid.CopyTo m_gdUnd
            
            m_GridLock(GT_GREEKS_UNDERLYING).LockRedraw
            FormatUndColumns
            UnderlyingsUpdateBackColor
            TotalsUpdateBadStatus
            UnderlyingsUpdateBadStatus
            fgUnd.AutoSize 1, fgUnd.Cols - 1, False, 100
            m_GridLock(GT_GREEKS_UNDERLYING).UnlockRedraw
            
            Refresh
    
    End Select
    
    UserControl_Resize
End Sub

Private Sub SetRefreshHint(ByVal bSet As Boolean)
    On Error Resume Next
    lblStatus.Visible = True
    lblStatus.Caption = IIf(bSet, "Use F5 to refresh results.", "")
End Sub

Private Sub HandleGridDblClick(ByVal bTradeNewAvailable As Boolean)
    On Error Resume Next
    If m_nMenuGridRow > 0 And m_nMenuGridRow < m_nMenuGridRows _
        And m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols Then
        
        If IsAltPressed Then
            Select Case True
                Case IsCtrlPressed
                    mnuCtxOrderNewOption_Click
                    
                Case IsShiftPressed
                    mnuCtxTntCardNew_Click
                
                Case Else
                    mnuCtxOrderNewStock_Click
            End Select
            
            FixDblClickHandled
        
        ElseIf bTradeNewAvailable And Not (IsCtrlPressed Or IsShiftPressed) Then
            mnuCtxTradeNew_Click
            FixDblClickHandled
        End If
    End If
End Sub

Public Sub UnderlyingsAdjustRates(ByVal bForceRateUpdate As Boolean)
    On Error Resume Next
    Dim aUnd As EtsMmRisksLib.MmRvUndAtom
    For Each aUnd In m_View.Und
        UnderlyingAdjustRates aUnd, bForceRateUpdate
    Next
End Sub

Public Function UnderlyingAdjustRates(ByRef aUnd As EtsMmRisksLib.MmRvUndAtom, ByVal bForceRateUpdate As Boolean) As Boolean
    On Error Resume Next
    UnderlyingAdjustRates = False
    If aUnd Is Nothing Then Exit Function
    
    Dim aPos As EtsMmRisksLib.MmRvPosAtom, bUseMidRates As Boolean, cPosThreshold@, dPos#
    
    Dim dtNow As Date
    dtNow = GetNewYorkTime
    
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
                        aPos.Rate = GetNeutralRate(dtNow, aPos.ExpiryOV)
                    Else
                        aPos.Rate = GetNeutralHTBRate(dtNow, aPos.ExpiryOV)
                    End If
                Else
                    If Not aUnd.IsHTB Then
                        aPos.Rate = IIf(dPos < 0, GetShortRate(dtNow, aPos.ExpiryOV), GetLongRate(dtNow, aPos.ExpiryOV))
                    Else
                        aPos.Rate = IIf(dPos < 0, GetHTBRate(dtNow, aPos.ExpiryOV), GetLongRate(dtNow, aPos.ExpiryOV))
                    End If
                End If

            End If
        Next
        
        UnderlyingAdjustRates = True
    End If
End Function


