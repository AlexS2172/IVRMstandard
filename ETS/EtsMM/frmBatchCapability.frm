VERSION 5.00
Object = "{C115893A-A3BF-43AF-B28D-69DB846077F3}#1.0#0"; "vsflex8u.ocx"
Object = "{BEEECC20-4D5F-4F8B-BFDC-5D9B6FBDE09D}#1.0#0"; "vsflex8.ocx"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form frmBatchCapability 
   Caption         =   "Batch Reporting"
   ClientHeight    =   4620
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10965
   Icon            =   "frmBatchCapability.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4620
   ScaleWidth      =   10965
   StartUpPosition =   3  'Windows Default
   Begin EtsMM.ctlRiskMatrix ctlRMView 
      Height          =   255
      Left            =   9720
      TabIndex        =   18
      Top             =   1920
      Visible         =   0   'False
      Width           =   255
      _ExtentX        =   450
      _ExtentY        =   450
   End
   Begin VSFlex8UCtl.VSFlexGrid fgExecution 
      Height          =   555
      Left            =   840
      TabIndex        =   16
      Top             =   3780
      Width           =   3795
      _cx             =   6694
      _cy             =   979
      Appearance      =   1
      BorderStyle     =   1
      Enabled         =   -1  'True
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
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
      SelectionMode   =   2
      GridLines       =   1
      GridLinesFixed  =   2
      GridLineWidth   =   1
      Rows            =   2
      Cols            =   3
      FixedRows       =   1
      FixedCols       =   0
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
      Editable        =   2
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
      AccessibleName  =   ""
      AccessibleDescription=   ""
      AccessibleValue =   ""
      AccessibleRole  =   24
   End
   Begin VB.CheckBox chkFilter 
      Alignment       =   1  'Right Justify
      Caption         =   "Filter Display"
      Height          =   315
      Left            =   4680
      TabIndex        =   15
      Top             =   3780
      Width           =   1215
   End
   Begin VB.TextBox txtEmail 
      Height          =   285
      Left            =   6000
      TabIndex        =   14
      Top             =   4080
      Width           =   2295
   End
   Begin VB.CheckBox chkEmail 
      Alignment       =   1  'Right Justify
      Caption         =   "Email reports"
      Height          =   315
      Left            =   4680
      TabIndex        =   13
      Top             =   4080
      Width           =   1215
   End
   Begin VB.CommandButton btnEnableDisable 
      Caption         =   "Enable All"
      Height          =   315
      Left            =   9600
      TabIndex        =   12
      Top             =   480
      Width           =   1335
   End
   Begin EtsMM.ctlRiskView ctlView 
      Height          =   255
      Left            =   9600
      TabIndex        =   6
      Top             =   1320
      Visible         =   0   'False
      Width           =   255
      _ExtentX        =   450
      _ExtentY        =   450
   End
   Begin VB.CommandButton btnSave 
      Caption         =   "Save"
      Height          =   315
      Left            =   9600
      TabIndex        =   4
      Top             =   3420
      Width           =   1335
   End
   Begin MSComDlg.CommonDialog dlgCommon 
      Left            =   6000
      Top             =   2280
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton btnDelete 
      Caption         =   "Delete"
      Height          =   315
      Left            =   9600
      TabIndex        =   3
      Top             =   3000
      Width           =   1335
   End
   Begin VB.CommandButton btnAddNew 
      Caption         =   "Add"
      Height          =   315
      Left            =   9600
      TabIndex        =   2
      Top             =   2580
      Width           =   1335
   End
   Begin VB.Timer tmrCalc 
      Enabled         =   0   'False
      Interval        =   60000
      Left            =   5040
      Top             =   2400
   End
   Begin VB.CommandButton btnClose 
      Caption         =   "Close"
      Height          =   315
      Left            =   9600
      TabIndex        =   5
      Top             =   4080
      Width           =   1335
   End
   Begin VB.CommandButton btnStart 
      Caption         =   "Run Now"
      Height          =   315
      Left            =   9600
      TabIndex        =   1
      Top             =   60
      Width           =   1335
   End
   Begin MSComctlLib.ProgressBar pbProgress 
      Height          =   240
      Left            =   0
      TabIndex        =   7
      Top             =   4380
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   423
      _Version        =   393216
      Appearance      =   1
      Scrolling       =   1
   End
   Begin MSComctlLib.ProgressBar pbOverall 
      Height          =   240
      Left            =   7260
      TabIndex        =   10
      Top             =   4380
      Visible         =   0   'False
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   423
      _Version        =   393216
      Appearance      =   1
      Scrolling       =   1
   End
   Begin VSFlex8Ctl.VSFlexGrid fgShedule 
      Height          =   3735
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   9495
      _cx             =   16748
      _cy             =   6588
      Appearance      =   1
      BorderStyle     =   1
      Enabled         =   -1  'True
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
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
      AllowSelection  =   0   'False
      AllowBigSelection=   0   'False
      AllowUserResizing=   1
      SelectionMode   =   1
      GridLines       =   1
      GridLinesFixed  =   2
      GridLineWidth   =   1
      Rows            =   1
      Cols            =   7
      FixedRows       =   1
      FixedCols       =   0
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
      Editable        =   2
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
      AccessibleName  =   ""
      AccessibleDescription=   ""
      AccessibleValue =   ""
      AccessibleRole  =   24
      Begin VB.Timer tmrClearView 
         Enabled         =   0   'False
         Interval        =   10
         Left            =   3120
         Top             =   1920
      End
   End
   Begin VB.Label lblShedule 
      Caption         =   "Shedule"
      Height          =   195
      Left            =   120
      TabIndex        =   17
      Top             =   3840
      Width           =   705
   End
   Begin VB.Image imgOverallStop 
      Height          =   240
      Left            =   9240
      MouseIcon       =   "frmBatchCapability.frx":0E42
      MousePointer    =   99  'Custom
      Picture         =   "frmBatchCapability.frx":0F94
      ToolTipText     =   "Cancel"
      Top             =   4380
      Visible         =   0   'False
      Width           =   240
   End
   Begin VB.Label lblOverall 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Overall:"
      Height          =   195
      Left            =   6660
      TabIndex        =   11
      Top             =   4380
      Visible         =   0   'False
      Width           =   540
   End
   Begin VB.Image imgStopDis 
      Enabled         =   0   'False
      Height          =   240
      Left            =   0
      Picture         =   "frmBatchCapability.frx":10DE
      Top             =   4380
      Visible         =   0   'False
      Width           =   240
   End
   Begin VB.Image imgStop 
      Height          =   240
      Left            =   1980
      MouseIcon       =   "frmBatchCapability.frx":1228
      MousePointer    =   99  'Custom
      Picture         =   "frmBatchCapability.frx":137A
      ToolTipText     =   "Cancel"
      Top             =   4380
      Visible         =   0   'False
      Width           =   240
   End
   Begin VB.Label lblStatus 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Height          =   195
      Left            =   -60
      TabIndex        =   9
      Top             =   4620
      Width           =   45
   End
   Begin VB.Label lblProcess 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Process status..."
      Height          =   195
      Left            =   2280
      TabIndex        =   8
      Top             =   4380
      Visible         =   0   'False
      Width           =   1170
   End
End
Attribute VB_Name = "frmBatchCapability"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private m_frmOwner As Form

Private m_bIsLoaded As Boolean
Private m_bIsOpened As Boolean
Private m_bInit As Boolean

Private m_bCalc As Boolean
Private m_bStopCalc As Boolean
Private m_bManualStart As Boolean

Private m_bIsRM As Boolean

Private m_CurReport As clsBatchReport

Private m_bEnableAll As Boolean
Private m_nDisableReportsCount As Long

Private m_nFrmHeight As Long
Private m_nFrmWidth As Long

Private Const STR_DEFAULT As String = "Default"

Private Enum BatchReportingColumnEnum
    BRC_ID = 0
    BRC_USER
    BRC_STATUS
    BRC_LAYOUT
    BRC_GROUP
    BRC_TRADER
    BRC_STRATEGY
    BRC_TRADER_GROUP
    BRC_POSITIONS
    BRC_LAST_RUN
    BRC_RESULT_FILE
    
    BRC_COLUMN_COUNT
End Enum

Private m_Reports As Collection
Private m_Shedule As Collection

Public Sub Init()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting Init Enter.", GetCaption

    If m_bIsLoaded Then Exit Sub
    m_bIsLoaded = True
    
    m_bCalc = False
    m_bInit = False
    
    m_bManualStart = False
    
    CopyShedule g_Params.BatchReportingShedules, m_Shedule
    CopyReports g_Params.BatchReports, m_Reports

    Load Me
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting Init Exit.", GetCaption
End Sub

Public Sub ShowData(Optional ByRef frmOwner As Form = Nothing)
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting ShowData Enter.", GetCaption
    
    If m_bIsOpened Then Exit Sub
    m_bIsOpened = True
    
    Set m_frmOwner = Nothing
    Set m_frmOwner = frmOwner
    If Not m_frmOwner Is Nothing Then m_frmOwner.Enabled = False
        
    CopyShedule g_Params.BatchReportingShedules, m_Shedule
    CopyReports g_Params.BatchReports, m_Reports
    InitControls
    RefreshData
    
    Me.Show
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting ShowData Exit.", GetCaption
End Sub

Private Sub AddNewReport()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting AddNewReport Enter.", GetCaption
    
    Dim aNewReport As clsBatchReport
    Set aNewReport = New clsBatchReport
    
    Sleep 100
    
    aNewReport.Init
    aNewReport.UserName = g_Params.UserName
    aNewReport.Status = SS_NEW
    aNewReport.ID = CLng(Format(Now, "DDHHSSNN"))
    aNewReport.UseDefaultLayout = True
    aNewReport.LayoutFile = STR_DEFAULT

    m_Reports.Add aNewReport, CStr(aNewReport.ID)

    Set aNewReport = Nothing
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting AddNewReport Exit.", GetCaption
End Sub

Private Sub DeleteReport(ByRef aReport As clsBatchReport)
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting DeleteReport Enter.", GetCaption
        
    If (Not aReport Is Nothing) Then
        aReport.Status = SS_DELETED
    End If
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting DeleteReport Exit.", GetCaption
End Sub

Private Sub InitControls()
    On Error Resume Next
    Dim sComboList As String
    Dim aStrategy As EtsGeneralLib.EtsStrategyAtom
    Dim aTrader As EtsGeneralLib.EtsTraderAtom, aUndGroup As EtsGeneralLib.EtsUndGroupAtom
    Dim aTraderGroup As EtsGeneralLib.EtsTraderGroupAtom
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting InitControls Enter.", GetCaption
    
    m_bInit = True
    
    fgShedule.Cols = BRC_COLUMN_COUNT
    
    fgShedule.TextMatrix(0, BRC_ID) = "#"
    fgShedule.TextMatrix(0, BRC_USER) = "User"
    fgShedule.TextMatrix(0, BRC_STATUS) = "Status"
    fgShedule.TextMatrix(0, BRC_LAYOUT) = "Layout"
    fgShedule.TextMatrix(0, BRC_GROUP) = "Group"
    fgShedule.TextMatrix(0, BRC_TRADER) = "Trader"
    fgShedule.TextMatrix(0, BRC_STRATEGY) = "Strategy"
    fgShedule.TextMatrix(0, BRC_TRADER_GROUP) = "Trader Group"
    fgShedule.TextMatrix(0, BRC_POSITIONS) = "Positions"
    fgShedule.TextMatrix(0, BRC_LAST_RUN) = "Last Run"
    fgShedule.TextMatrix(0, BRC_RESULT_FILE) = "Result File"
    
    fgShedule.ColComboList(BRC_LAYOUT) = "#0;" & STR_DEFAULT & "|#1;Custom"
    fgShedule.ColComboList(BRC_RESULT_FILE) = "..."
    
    fgShedule.ColComboList(BRC_STATUS) = "#1;Active|#0;Disabled"
    fgShedule.ColComboList(BRC_POSITIONS) = "#1;Expanded|#0;Totals"
    
    sComboList = ""
    For Each aUndGroup In g_UnderlyingGroup
        sComboList = sComboList & "|#" & Trim$(Str$(aUndGroup.ID)) & ";" & aUndGroup.Name
    Next
    fgShedule.ColComboList(BRC_GROUP) = AdjustComboList(sComboList)
    
    sComboList = ""
    For Each aTrader In g_Trader
        sComboList = sComboList & "|#" & Trim$(Str$(aTrader.ID)) & ";" & aTrader.Name
    Next
    fgShedule.ColComboList(BRC_TRADER) = AdjustComboList(sComboList)
    
    sComboList = "|#" & Trim$(Str$(NO_STRATEGY_ID)) & ";" & NO_STRATEGY_NAME
    For Each aStrategy In g_Strategy
        sComboList = sComboList & "|#" & Trim$(Str$(aStrategy.ID)) & ";" & aStrategy.Name
    Next
    fgShedule.ColComboList(BRC_STRATEGY) = AdjustComboList(sComboList)
    
    sComboList = ""
    For Each aTraderGroup In g_TraderGroup
        If aTraderGroup.ID <> 0 Then
            sComboList = sComboList & "|#" & Trim$(Str$(aTraderGroup.ID)) & ";" & aTraderGroup.Name
        End If
    Next
    fgShedule.ColComboList(BRC_TRADER_GROUP) = AdjustComboList(sComboList)
    
    
    fgShedule.ColAlignment(BRC_ID) = flexAlignLeftCenter
    fgShedule.ColAlignment(BRC_USER) = flexAlignLeftCenter
    fgShedule.ColAlignment(BRC_STATUS) = flexAlignLeftCenter
    fgShedule.ColAlignment(BRC_LAYOUT) = flexAlignLeftCenter
    fgShedule.ColAlignment(BRC_GROUP) = flexAlignLeftCenter
    fgShedule.ColAlignment(BRC_TRADER) = flexAlignLeftCenter
    fgShedule.ColAlignment(BRC_STRATEGY) = flexAlignLeftCenter
    fgShedule.ColAlignment(BRC_TRADER_GROUP) = flexAlignLeftCenter
    fgShedule.ColAlignment(BRC_POSITIONS) = flexAlignLeftCenter
    fgShedule.ColAlignment(BRC_LAST_RUN) = flexAlignLeftCenter
    fgShedule.ColAlignment(BRC_RESULT_FILE) = flexAlignLeftCenter
    
    fgShedule.ColDataType(BRC_LAST_RUN) = flexDTDate
    fgShedule.ColFormat(BRC_LAST_RUN) = "hh:mm:ss AMPM"
    
    fgShedule.ColHidden(BRC_USER) = True
              
    fgExecution.TextMatrix(0, 0) = "Execution 1"
    fgExecution.TextMatrix(0, 1) = "Execution 2"
    fgExecution.TextMatrix(0, 2) = "Execution 3"
    
    fgExecution.ColAlignment(0) = flexAlignCenterCenter
    fgExecution.ColAlignment(1) = flexAlignCenterCenter
    fgExecution.ColAlignment(2) = flexAlignCenterCenter
    
    fgExecution.ColDataType(0) = flexDTDate
    fgExecution.ColDataType(1) = flexDTDate
    fgExecution.ColDataType(2) = flexDTDate
    
    fgExecution.ColFormat(0) = "hh:mm:ss AMPM"
    fgExecution.ColFormat(1) = "hh:mm:ss AMPM"
    fgExecution.ColFormat(2) = "hh:mm:ss AMPM"
    
    
    m_bInit = False
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting InitControls Exit.", GetCaption
End Sub

Private Function AdjustComboList(sComboList As String) As String
    On Error Resume Next
    
    If Len(sComboList) > 0 Then
        If InStr(1, sComboList, "|") = 1 Then
            sComboList = "#0;<All>|" & Mid$(sComboList, InStr(1, sComboList, "|") + 1)
        Else
            sComboList = "#0;<All>|" & sComboList
        End If
    Else
        sComboList = "#0;<None>"
    End If
        
    AdjustComboList = sComboList
End Function

Private Sub RefreshData()
    On Error Resume Next
    Dim aShedule As clsBatchReportingShedule
    Dim aReport As clsBatchReport

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RefreshData Enter.", GetCaption

    m_bInit = True
    
    fgShedule.Rows = 1

    Dim nRow As Long
    For Each aReport In m_Reports
        If aReport.Status <> SS_DELETED And (aReport.UserName = g_Params.UserName Or g_Params.AllReportsAvalable = True) Then
            nRow = nRow + 1
            fgShedule.Rows = fgShedule.Rows + 1
            fgShedule.TextMatrix(nRow, BRC_ID) = nRow
            fgShedule.TextMatrix(nRow, BRC_USER) = aReport.UserName
            fgShedule.TextMatrix(nRow, BRC_STATUS) = IIf(aReport.IsActive, 1, 0)
            fgShedule.TextMatrix(nRow, BRC_LAYOUT) = IIf(aReport.UseDefaultLayout, STR_DEFAULT, aReport.LayoutFile)
            fgShedule.TextMatrix(nRow, BRC_GROUP) = aReport.GroupID
            fgShedule.TextMatrix(nRow, BRC_TRADER) = aReport.TraderID
            fgShedule.TextMatrix(nRow, BRC_STRATEGY) = aReport.strategyID
            fgShedule.TextMatrix(nRow, BRC_TRADER_GROUP) = aReport.TraderGroupID
            fgShedule.TextMatrix(nRow, BRC_POSITIONS) = IIf(aReport.IsPosExpanded, 1, 0)
            fgShedule.TextMatrix(nRow, BRC_LAST_RUN) = IIf(aReport.LastRun > 0, aReport.LastRun, "")
            fgShedule.TextMatrix(nRow, BRC_RESULT_FILE) = aReport.ResultFile

            fgShedule.RowData(nRow) = aReport
        End If
    Next

    fgShedule.AutoSize 0, fgShedule.Cols - 1, , 100
    
    Dim nCol As Long
    For Each aShedule In m_Shedule
        fgExecution.TextMatrix(1, nCol) = IIf(aShedule.Enabled, aShedule.ExecTime, "<none>")
        fgExecution.ColData(nCol) = aShedule.ID
        nCol = nCol + 1
    Next
    
    fgExecution.AutoSize 0, fgExecution.Cols - 1, , 100
    
    btnEnableDisable.Caption = IIf(m_bEnableAll, "Enable All", "Disable All")
    
    chkFilter.Value = IIf(g_Params.BR_FilterDisplay, 1, 0)
    chkEmail.Value = IIf(g_Params.BR_SendEmail, 1, 0)
    txtEmail.Text = g_Params.BR_Email
    txtEmail.Enabled = g_Params.BR_SendEmail
    

    m_bInit = False
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RefreshData Exit.", GetCaption
End Sub

Private Sub btnAddNew_Click()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnAddNew_Click Enter.", GetCaption
    
    If m_bInit Then Exit Sub
    
    AddNewReport
    RefreshData
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnAddNew_Click Exit.", GetCaption
End Sub

Private Sub btnClose_Click()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnClose_Click Enter.", GetCaption
    
    m_bIsOpened = False
    
    If Not m_frmOwner Is Nothing Then
        m_frmOwner.Enabled = True
        m_frmOwner.SetFocus
    End If
    
    Set m_frmOwner = Nothing
    
    Set m_Reports = Nothing
    Set m_Shedule = Nothing
    
    Me.Hide
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnClose_Click Exit.", GetCaption
End Sub

Private Sub btnDelete_Click()
    On Error Resume Next
    Dim nRow As Long
    Dim aReportTask As clsBatchReport
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnDelete_Click Enter.", GetCaption
    
    If m_bInit Then Exit Sub
    
    nRow = fgShedule.RowSel
    If nRow > 0 Then
        Set aReportTask = fgShedule.RowData(nRow)
        If (Not aReportTask Is Nothing) Then
            DeleteReport aReportTask
            RefreshData
            Set aReportTask = Nothing
        End If
    End If
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnDelete_Click Exit.", GetCaption
End Sub

Private Sub btnEnableDisable_Click()
    On Error Resume Next
    Dim aReport As clsBatchReport
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnEnableDisable_Click Enter.", GetCaption

    m_nDisableReportsCount = 0
    
    For Each aReport In m_Reports
        If (aReport.UserName = g_Params.UserName Or g_Params.AllReportsAvalable = True) Then
            aReport.IsActive = m_bEnableAll
        
            If (aReport.Status <> SS_NEW And aReport.Status <> SS_DELETED) Then aReport.Status = SS_UPDATED
        
            If Not aReport.IsActive Then m_nDisableReportsCount = m_nDisableReportsCount + 1
        End If
    Next
    
    m_bEnableAll = CBool(m_nDisableReportsCount > 0)
    
    RefreshData
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnEnableDisable_Click Exit.", GetCaption
    
End Sub

Private Sub btnSave_Click()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnSave_Click Enter.", GetCaption
    
    
    Screen.MousePointer = vbHourglass
    g_Params.BatchReports = m_Reports
    g_Params.BatchReportingShedules = m_Shedule
    g_Params.SaveBatchShedule
    g_Params.SaveBatchReports
    
    g_Params.LoadBatchShedule
    g_Params.LoadBatchReports

    CopyShedule g_Params.BatchReportingShedules, m_Shedule
    CopyReports g_Params.BatchReports, m_Reports
    RefreshData
    Screen.MousePointer = vbDefault
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnSave_Click Exit.", GetCaption
End Sub

Private Sub btnStart_Click()
    On Error Resume Next
    Dim nRow As Long
    Dim aReportTask As clsBatchReport
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnStart_Click Enter.", GetCaption
    
    nRow = fgShedule.RowSel
    
    If nRow > 0 And Not m_bCalc Then
        m_bManualStart = True
        
        Set aReportTask = fgShedule.RowData(nRow)
        If (Not aReportTask Is Nothing) Then
            CalcReport aReportTask
            Set aReportTask = Nothing
        End If
    End If
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting btnStart_Click Exit.", GetCaption
End Sub

Private Sub chkEmail_Click()
    On Error Resume Next
    g_Params.BR_SendEmail = chkEmail.Value
    txtEmail.Enabled = g_Params.BR_SendEmail
End Sub

Private Sub chkFilter_Click()
    On Error Resume Next
    g_Params.BR_FilterDisplay = chkFilter.Value
End Sub

Private Sub ctlRMView_OnRefreshCancel()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RM_OnRefreshCancel Enter. " & GetCurInfo, GetCaption
    
    tmrClearView.Enabled = True
    
    Set m_CurReport = Nothing
    m_bManualStart = False
        
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RM_OnRefreshCancel Exit.", GetCaption
End Sub

Private Sub ctlRMView_OnRefreshComplete()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RM_OnRefreshComplete Enter. " & GetCurInfo, GetCaption
        
    SaveResults
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RM_OnRefreshComplete Exit.", GetCaption
End Sub

Private Sub ctlRMView_OnRefreshEmpty()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RM_OnRefreshEmpty Enter. " & GetCurInfo, GetCaption
        
    SaveResults
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RM_OnRefreshEmpty Exit.", GetCaption
End Sub

Private Sub ctlRMView_OnRefreshError()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RM_OnRefreshError Enter. " & GetCurInfo, GetCaption
        
    SaveResults
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RM_OnRefreshError Exit.", GetCaption
End Sub

Private Sub ctlView_OnRefreshCancel()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RV_OnRefreshCancel Enter. " & GetCurInfo, GetCaption
        
    tmrClearView.Enabled = True
    
    Set m_CurReport = Nothing
    m_bManualStart = False
            
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RV_OnRefreshCancel Exit.", GetCaption
End Sub

Private Sub ctlView_OnRefreshComplete()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RV_OnRefreshComplete Enter. " & GetCurInfo, GetCaption
            
    SaveResults
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RV_OnRefreshComplete Exit.", GetCaption
End Sub

Private Sub ctlView_OnRefreshEmpty()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RV_OnRefreshEmpty Enter. " & GetCurInfo, GetCaption

    SaveResults
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RV_OnRefreshEmpty Exit.", GetCaption
End Sub

Private Sub ctlView_OnRefreshError()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RV_OnRefreshError Enter. " & GetCurInfo, GetCaption
    
    SaveResults
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting RV_OnRefreshError Exit.", GetCaption
End Sub

Private Sub fgExecution_AfterEdit(ByVal Row As Long, ByVal Col As Long)
    On Error Resume Next
    Dim dtValue As Date
    Dim aShedule As clsBatchReportingShedule
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting fgExecution_AfterEdit Enter. Row/Col = " & CStr(Row) & "/" & CStr(Col), GetCaption
    
    Set aShedule = m_Shedule(fgExecution.ColData(Col))
    
    Err.Clear
    dtValue = CDate(fgExecution.TextMatrix(Row, Col))
    If Err.Number = 0 Then
        aShedule.ExecTime = dtValue
        aShedule.Enabled = True
    Else
        aShedule.ExecTime = 0
        aShedule.Enabled = False
    End If
    
    RefreshData
    
    Set aShedule = Nothing
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting fgExecution_AfterEdit Exit.", GetCaption
End Sub

Private Sub fgShedule_AfterEdit(ByVal Row As Long, ByVal Col As Long)
    On Error Resume Next
    Dim dtValue As Date
    Dim aReportTask As clsBatchReport
    Dim sFileName As String
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting fgShedule_AfterEdit Enter. Row/Col = " & CStr(Row) & "/" & CStr(Col), GetCaption
    
    If m_bInit Then Exit Sub
    
    Set aReportTask = fgShedule.RowData(Row)
    If (Not aReportTask Is Nothing) Then
        Select Case Col
            Case BRC_STATUS
                aReportTask.IsActive = CBool(fgShedule.TextMatrix(Row, Col))
                If aReportTask.Status = SS_COMMON Then aReportTask.Status = SS_UPDATED
                
                m_nDisableReportsCount = m_nDisableReportsCount + IIf(aReportTask.IsActive, -1, 1)
                m_bEnableAll = CBool(m_bDisableReportsCount > 0)
                btnEnableDisable.Caption = IIf(m_bEnableAll, "Enable All", "Disable All")
                
            Case BRC_GROUP
                aReportTask.GroupID = fgShedule.TextMatrix(Row, Col)
                If aReportTask.Status = SS_COMMON Then aReportTask.Status = SS_UPDATED
                
            Case BRC_TRADER
                aReportTask.TraderID = fgShedule.TextMatrix(Row, Col)
                If aReportTask.Status = SS_COMMON Then aReportTask.Status = SS_UPDATED
                
            Case BRC_STRATEGY
                aReportTask.strategyID = fgShedule.TextMatrix(Row, Col)
                If aReportTask.Status = SS_COMMON Then aReportTask.Status = SS_UPDATED
                
            Case BRC_TRADER_GROUP
                aReportTask.TraderGroupID = fgShedule.TextMatrix(Row, Col)
                If aReportTask.Status = SS_COMMON Then aReportTask.Status = SS_UPDATED
                
            Case BRC_POSITIONS
                aReportTask.IsPosExpanded = CBool(fgShedule.TextMatrix(Row, Col))
                If aReportTask.Status = SS_COMMON Then aReportTask.Status = SS_UPDATED
            Case BRC_LAYOUT
                If (fgShedule.ValueMatrix(Row, Col) <> 0) Then
                
                    aReportTask.UseDefaultLayout = False
                    
                    sFileName = LayoutFileDialog
                    If sFileName <> STR_NA Then
                        aReportTask.LayoutFile = ExtractFileName(sFileName)
                        aReportTask.LayoutFilePath = ExtractFilePath(sFileName)
                        If aReportTask.Status = SS_COMMON Then aReportTask.Status = SS_UPDATED
        
                        fgShedule.TextMatrix(Row, Col) = aReportTask.LayoutFile
                    End If
                Else
                    aReportTask.UseDefaultLayout = True
                    aReportTask.LayoutFile = STR_DEFAULT
                End If
            
            Case Else
        End Select
    End If
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting fgShedule_AfterEdit Exit.", GetCaption
End Sub

Private Sub fgShedule_BeforeEdit(ByVal Row As Long, ByVal Col As Long, Cancel As Boolean)
    On Error Resume Next
    If m_bInit Then Exit Sub
    
    If Col = BRC_ID Or Col = BRC_USER Or Col = BRC_LAST_RUN Then
        Cancel = True
        Exit Sub
    End If
    
End Sub

Private Sub fgShedule_CellButtonClick(ByVal Row As Long, ByVal Col As Long)
    On Error Resume Next
    Dim sFilePath As String
    Dim sFileName As String
    Dim aReportTask As clsBatchReport
    
    If m_bInit Then Exit Sub

    Set aReportTask = fgShedule.RowData(Row)
    
    If (Not aReportTask Is Nothing) Then
        Select Case Col
            Case BRC_RESULT_FILE
                sFilePath = aReportTask.ResultFilePath
                If BrowseForFolder(Me, "Select folder for result file", sFilePath) And Len(sFilePath) > 0 Then
                    aReportTask.ResultFilePath = sFilePath + "\"
                    If aReportTask.Status = SS_COMMON Then aReportTask.Status = SS_UPDATED
                End If
            Case Else
        End Select
    End If
End Sub

Private Function LayoutFileDialog() As String
    On Error Resume Next
    
    LayoutFileDialog = STR_NA
    
    dlgCommon.Flags = cdlOFNExplorer Or cdlOFNLongNames Or cdlOFNPathMustExist _
                                     Or cdlOFNHideReadOnly Or cdlOFNFileMustExist
    
    dlgCommon.CancelError = True
    dlgCommon.DefaultExt = ".txt"
    dlgCommon.DialogTitle = "Load layout file"
    dlgCommon.FileName = ""
    dlgCommon.InitDir = g_Params.CurrentUserPrivateFolder
    dlgCommon.Filter = "Risk View and Risk Matrix layout files (*.rvw; *.mvw)|*.rvw;*.mvw|All Files|*.*"
    dlgCommon.FilterIndex = 1
    
    dlgCommon.ShowOpen
    If Err.Number = 0 Then
        LayoutFileDialog = dlgCommon.FileName
    End If
    
End Function

Private Sub Form_Load()
    On Error Resume Next
    
    InitRisksView
    InitRMView
    
    m_nFrmHeight = Me.Height
    m_nFrmWidth = Me.Width
        
    tmrCalc.Enabled = g_Params.ExecuteBatchReporting 'True
    tmrClearView.Enabled = False
End Sub

Private Sub Form_Resize()
    On Error Resume Next
    
    fgShedule.Move fgShedule.Left, fgShedule.Top, ScaleWidth - 1515, ScaleHeight - 900
    
    btnAddNew.Move btnAddNew.Left + (Me.Width - m_nFrmWidth), btnAddNew.Top + (Me.Height - m_nFrmHeight)
    btnStart.Move btnStart.Left + (Me.Width - m_nFrmWidth), btnStart.Top
    btnClose.Move btnClose.Left + (Me.Width - m_nFrmWidth), btnClose.Top + (Me.Height - m_nFrmHeight)
    btnSave.Move btnSave.Left + (Me.Width - m_nFrmWidth), btnSave.Top + (Me.Height - m_nFrmHeight)
    btnDelete.Move btnDelete.Left + (Me.Width - m_nFrmWidth), btnDelete.Top + (Me.Height - m_nFrmHeight)
    btnEnableDisable.Move btnEnableDisable.Left + (Me.Width - m_nFrmWidth), btnEnableDisable.Top
    
    pbProgress.Move pbProgress.Left, pbProgress.Top + (Me.Height - m_nFrmHeight)
    lblProcess.Move lblProcess.Left, lblProcess.Top + (Me.Height - m_nFrmHeight)
    lblStatus.Move lblStatus.Left, lblStatus.Top + (Me.Height - m_nFrmHeight)
    imgStop.Move imgStop.Left, imgStop.Top + (Me.Height - m_nFrmHeight)
    imgStopDis.Move imgStopDis.Left, imgStopDis.Top + (Me.Height - m_nFrmHeight)
    
    lblShedule.Move lblShedule.Left, lblShedule.Top + (Me.Height - m_nFrmHeight)
    fgExecution.Move fgExecution.Left, fgExecution.Top + (Me.Height - m_nFrmHeight)
    chkFilter.Move chkFilter.Left, chkFilter.Top + (Me.Height - m_nFrmHeight)
    chkEmail.Move chkEmail.Left, chkEmail.Top + (Me.Height - m_nFrmHeight)
    txtEmail.Move txtEmail.Left, txtEmail.Top + (Me.Height - m_nFrmHeight)
    
    lblOverall.Move lblOverall.Left + (Me.Width - m_nFrmWidth), lblOverall.Top + (Me.Height - m_nFrmHeight)
    pbOverall.Move pbOverall.Left + (Me.Width - m_nFrmWidth), pbOverall.Top + (Me.Height - m_nFrmHeight)
    imgOverallStop.Move imgOverallStop.Left + (Me.Width - m_nFrmWidth), imgOverallStop.Top + (Me.Height - m_nFrmHeight)
    
    m_nFrmHeight = Me.Height
    m_nFrmWidth = Me.Width
End Sub

Public Sub Term()
    On Error Resume Next
    Set m_Shedule = Nothing
End Sub

Private Sub Form_Unload(Cancel As Integer)
    On Error Resume Next
    Cancel = True
    m_bIsOpened = False
    
    If Not m_frmOwner Is Nothing Then
        m_frmOwner.Enabled = True
        m_frmOwner.SetFocus
    End If
    
    Set m_frmOwner = Nothing
    Set m_Reports = Nothing
    Set m_Shedule = Nothing
    
    Me.Hide
End Sub

Private Sub imgOverallStop_Click()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting imgOverallStop_Click.", GetCaption
    
    tmrClearView.Enabled = True
    
    Set m_CurReport = Nothing
    
    m_bManualStart = False
    
End Sub

Private Sub tmrCalc_Timer()
    On Error Resume Next
    Dim dtNow As Date
    Dim aShedule As clsBatchReportingShedule
    Dim aReport As clsBatchReport

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting tmrCalc_Timer Enter.", GetCaption

    dtNow = Now
    For Each aShedule In g_Params.BatchReportingShedules
        If aShedule.IsReady(dtNow) Then
            
            If m_bCalc Then
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogDebug, "BatchCapability tmrCalc_Timer. Some report already executed.", GetCaption
                Exit Sub
            End If
            
            gDBW.usp_BR_Shedule_Complete aShedule.ID, dtNow
            aShedule.LastRun = dtNow

            m_bManualStart = False
            
            For Each aReport In g_Params.BatchReports
                If aReport.IsActive Then
                    CalcReport aReport
                End If
            Next
        End If
    Next

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting tmrCalc_Timer Exit.", GetCaption
End Sub

Private Sub CalcReport(ByRef aReport As clsBatchReport)
    On Error Resume Next
    Dim aFilters As EtsGeneralLib.EtsFilterData
    Dim aStorage As clsSettingsStorage

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting CalcReport Enter. " & GetCurInfo, GetCaption

    While m_bCalc
        MMSleep 100
    Wend

    If m_bStopCalc Then
        m_bStopCalc = False

        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting CalcReport Stop Calc.", GetCaption
        Exit Sub
    End If

    m_bCalc = True

    InitRisksView
    InitRMView
    Set aStorage = New clsSettingsStorage
    
    If (Not aReport.UseDefaultLayout) Then
        aStorage.Init aReport.LayoutFilePath + aReport.LayoutFile
        aStorage.ReadData
        If aStorage.GetStringValue("Type", "Value") = "RisksView" Then
            m_bIsRM = False
            ctlView.OpenFromFile aStorage, "", False, False
        ElseIf aStorage.GetStringValue("Type", "Value") = "RiskMatrix" Then
            m_bIsRM = True
            ctlRMView.OpenFromFile aStorage, "", False, False
        Else
            m_bCalc = False
            LogEvent EVENT_ERROR, "Can't start report calculation, invalid file " & aReport.LayoutFilePath + aReport.LayoutFile
            Exit Sub
        End If
    Else
        m_bIsRM = False
        ctlView.InitColumns
    End If

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting CalcReport. " & GetCurInfo, GetCaption

    Set m_CurReport = aReport
    
    Set aFilters = New EtsGeneralLib.EtsFilterData
    aFilters.Initialize RFC_SYMBOL, RFC_COLUMN_COUNT
    aFilters.Data(RFC_GROUPS) = aReport.GroupID
    aFilters.Data(RFC_TRADER) = aReport.TraderID
    aFilters.Data(RFC_STRATEGY) = aReport.strategyID
    aFilters.Data(RFC_TRADER_GROUP) = aReport.TraderGroupID
    
    If Not m_bIsRM Then
        ctlView.ImmediateRefresh
        ctlView.ShowDataByFilter aFilters
    Else
        ctlRMView.ImmediateRefresh
        ctlRMView.ShowDataByFilter aFilters
    End If
    
    If (aReport.Status <> SS_NEW And aReport.Status <> SS_DELETED) Then aReport.Status = SS_UPDATED
    
    Set aFilters = Nothing

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting CalcReport Exit.", GetCaption
End Sub

Public Function GetCaption() As String
    On Error Resume Next
    GetCaption = Me.Caption
End Function

Private Sub CopyShedule(ByRef aSrc As Collection, ByRef aDst As Collection)
    On Error Resume Next
    Dim aSrcItem As clsBatchReportingShedule
    Dim aDstItem As clsBatchReportingShedule

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting CopyShedule Enter.", GetCaption

    Set aDst = Nothing
    Set aDst = New Collection

    For Each aSrcItem In aSrc
        Set aDstItem = New clsBatchReportingShedule
        
        aDstItem.ID = aSrcItem.ID
        aDstItem.ExecTime = aSrcItem.ExecTime
        aDstItem.Enabled = aSrcItem.Enabled
        aDstItem.LastRun = aSrcItem.LastRun
        
        aDst.Add aDstItem
    
        Set aDstItem = Nothing
    Next

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting CopyShedule Exit.", GetCaption
End Sub

Private Sub CopyReports(ByRef aSrc As Collection, ByRef aDst As Collection)
    On Error Resume Next
    Dim aSrcItem As clsBatchReport
    Dim aDstItem As clsBatchReport

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting CopyReports Enter.", GetCaption
        
    m_nDisableReportsCount = 0

    Set aDst = Nothing
    Set aDst = New Collection

    For Each aSrcItem In aSrc
        Set aDstItem = New clsBatchReport
        
        aDstItem.ID = aSrcItem.ID
        aDstItem.UserName = aSrcItem.UserName
        aDstItem.IsActive = aSrcItem.IsActive
        aDstItem.LayoutFile = aSrcItem.LayoutFile
        aDstItem.LayoutFilePath = aSrcItem.LayoutFilePath
        aDstItem.GroupID = aSrcItem.GroupID
        aDstItem.TraderID = aSrcItem.TraderID
        aDstItem.strategyID = aSrcItem.strategyID
        aDstItem.TraderGroupID = aSrcItem.TraderGroupID
        aDstItem.IsPosExpanded = aSrcItem.IsPosExpanded
        aDstItem.LastRun = aSrcItem.LastRun
        aDstItem.ResultFile = aSrcItem.ResultFile
        aDstItem.ResultFilePath = aSrcItem.ResultFilePath
        aDstItem.UseDefaultLayout = aSrcItem.UseDefaultLayout
        
        aDstItem.Status = SS_COMMON

        aDst.Add aDstItem
        
        If Not aDstItem.IsActive Then m_nDisableReportsCount = m_nDisableReportsCount + 1

        Set aDstItem = Nothing
    Next
    
    m_bEnableAll = CBool(m_nDisableReportsCount > 0)

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting CopyReports Exit.", GetCaption
End Sub

Private Function GetCurInfo() As String
    On Error Resume Next
    GetCurInfo = CStr(m_CurReport.ID & "/" & m_CurReport.LayoutFile)
End Function

Private Sub InitRisksView()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting InitRisksView Enter.", GetCaption
    
    pbProgress.Visible = False
    lblProcess.Visible = False
    lblStatus.Visible = False
    imgStop.Visible = False
    imgStopDis.Visible = False
    
    Set ctlView.m_frmOwner = Me
    Set ctlView.pbProgress = pbProgress
    Set ctlView.lblProcess = lblProcess
    Set ctlView.lblStatus = lblStatus
    Set ctlView.imgStop = imgStop
    Set ctlView.imgStopDis = imgStopDis
    
    ctlView.Init
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting InitRisksView Exit.", GetCaption
End Sub

Private Sub InitRMView()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting InitRMView Enter.", GetCaption
    
    pbProgress.Visible = False
    lblProcess.Visible = False
    lblStatus.Visible = False
    imgStop.Visible = False
    imgStopDis.Visible = False
    
    Set ctlRMView.m_frmOwner = Me
    Set ctlRMView.pbProgress = pbProgress
    Set ctlRMView.lblProcess = lblProcess
    Set ctlRMView.lblStatus = lblStatus
    Set ctlRMView.imgStop = imgStop
    Set ctlRMView.imgStopDis = imgStopDis
    
    ctlRMView.Init
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogDebug, "BatchReporting InitRMView Exit.", GetCaption
End Sub

Private Sub ClearRisksView()
    On Error Resume Next
    ctlView.Term
    
    pbProgress.Visible = False
    lblProcess.Visible = False
    lblStatus.Visible = False
    imgStop.Visible = False
    imgStopDis.Visible = False
End Sub

Private Sub ClearRMView()
    On Error Resume Next
    ctlRMView.Term
    
    pbProgress.Visible = False
    lblProcess.Visible = False
    lblStatus.Visible = False
    imgStop.Visible = False
    imgStopDis.Visible = False
End Sub

Private Function GetFileName(dtDate As Date) As String
    On Error Resume Next
    Dim sLayout As String: sLayout = m_CurReport.LayoutFile
    If InStrRev(sLayout, ".") <> 0 Then sLayout = ExtractName(sLayout)
    
    GetFileName = m_CurReport.UserName & "_" & sLayout & "_" & Format(dtDate, "_hhmmss") & ".htm"
End Function

Private Sub tmrClearView_Timer()
    On Error Resume Next
    tmrClearView.Enabled = False
    m_bCalc = False
    
    ClearRisksView
    ClearRMView
End Sub

Private Sub txtEmail_Change()
    On Error Resume Next
    g_Params.BR_Email = txtEmail.Text
End Sub

Private Sub SaveResults()
    On Error Resume Next
    Dim dtDate As Date
    Dim sFileName As String
    
    dtDate = Now
    sFileName = GetFileName(dtDate)
    
    If Not m_bIsRM Then
        ctlView.ExportToHTML sFileName, m_CurReport.ResultFilePath, g_Params.BR_FilterDisplay, m_CurReport.IsPosExpanded
    Else
        ctlRMView.ExportToHTML sFileName, m_CurReport.ResultFilePath, g_Params.BR_FilterDisplay
    End If
    
    If g_Params.BR_SendEmail Then
        SendEmail g_Params.BR_Email, m_CurReport.ResultFilePath & sFileName
    End If
    
    m_CurReport.LastRun = dtDate
    m_CurReport.ResultFile = sFileName
    gDBW.usp_BR_Report_Complete m_CurReport.ID, dtDate, sFileName
    RefreshData

    tmrClearView.Enabled = True
    
    Set m_CurReport = Nothing
    m_bManualStart = False
End Sub

Private Sub SendEmail(ByVal sEmail As String, ByVal sFile As String)
    On Error Resume Next
    MAPI_SendMail sEmail, "IvRM Batch Reporting", "", sFile
End Sub
