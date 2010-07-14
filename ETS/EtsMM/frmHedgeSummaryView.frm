VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form frmHedgeSummaryView 
   Caption         =   "Hedge Summary"
   ClientHeight    =   5610
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   9600
   Icon            =   "frmHedgeSummaryView.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   ScaleHeight     =   5610
   ScaleMode       =   0  'User
   ScaleWidth      =   9600
   StartUpPosition =   3  'Windows Default
   Begin EtsMM.ctlHedgeSummaryView ctlView 
      Height          =   4275
      Left            =   0
      TabIndex        =   5
      Top             =   0
      Width           =   6675
      _ExtentX        =   11774
      _ExtentY        =   7541
   End
   Begin VB.PictureBox picBottom 
      BorderStyle     =   0  'None
      Height          =   300
      Left            =   180
      ScaleHeight     =   300
      ScaleWidth      =   7620
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   4680
      Width           =   7620
      Begin MSComctlLib.ProgressBar pbProgress 
         Height          =   240
         Left            =   60
         TabIndex        =   1
         Top             =   45
         Visible         =   0   'False
         Width           =   2175
         _ExtentX        =   3836
         _ExtentY        =   423
         _Version        =   393216
         Appearance      =   1
         Scrolling       =   1
      End
      Begin VB.Label lblValue 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Value"
         Height          =   195
         Left            =   4200
         TabIndex        =   4
         Top             =   60
         UseMnemonic     =   0   'False
         Width           =   405
      End
      Begin VB.Label lblProcess 
         AutoSize        =   -1  'True
         Caption         =   "Process status..."
         Height          =   195
         Left            =   2655
         TabIndex        =   3
         Top             =   60
         Visible         =   0   'False
         Width           =   1170
      End
      Begin VB.Label lblStatus 
         AutoSize        =   -1  'True
         Height          =   195
         Left            =   30
         TabIndex        =   2
         Top             =   60
         Width           =   45
      End
      Begin VB.Image imgStop 
         Height          =   240
         Left            =   2340
         MouseIcon       =   "frmHedgeSummaryView.frx":000C
         MousePointer    =   99  'Custom
         Picture         =   "frmHedgeSummaryView.frx":015E
         ToolTipText     =   "Cancel"
         Top             =   45
         Visible         =   0   'False
         Width           =   240
      End
      Begin VB.Image imgStopDis 
         Enabled         =   0   'False
         Height          =   240
         Left            =   2340
         Picture         =   "frmHedgeSummaryView.frx":02A8
         Top             =   45
         Visible         =   0   'False
         Width           =   240
      End
   End
   Begin MSComDlg.CommonDialog dlgCommon 
      Left            =   7680
      Top             =   4020
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComctlLib.StatusBar sbStatus 
      Align           =   2  'Align Bottom
      Height          =   300
      Left            =   0
      TabIndex        =   6
      Top             =   5310
      Width           =   9600
      _ExtentX        =   16933
      _ExtentY        =   529
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileNew 
         Caption         =   "&New..."
         Shortcut        =   ^N
      End
      Begin VB.Menu mnuFileOpen 
         Caption         =   "&Open..."
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "&Save"
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuFileSaveAs 
         Caption         =   "Save &As..."
      End
      Begin VB.Menu mnuSeparator1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileTrades 
         Caption         =   "&Trades..."
         Shortcut        =   ^T
      End
      Begin VB.Menu mnuFileRisks 
         Caption         =   "&Risks..."
         Shortcut        =   ^R
      End
      Begin VB.Menu mnuFileQuotes 
         Caption         =   "&Quotes..."
         Shortcut        =   ^Q
      End
      Begin VB.Menu mnuFileRiskMatrix 
         Caption         =   "Risk &Matrix..."
         Shortcut        =   ^M
      End
      Begin VB.Menu mnuFileVola 
         Caption         =   "Volat&ility Monitor..."
         Shortcut        =   ^I
      End
      Begin VB.Menu mnuFileQuotation 
         Caption         =   "ISE M&arket Maker..."
         Enabled         =   0   'False
         Shortcut        =   ^K
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileVolaAnalysis 
         Caption         =   "Volatilit&y Analysis..."
         Shortcut        =   ^Y
      End
      Begin VB.Menu mnuFileGreeks 
         Caption         =   "Gr&eeks..."
         Shortcut        =   ^E
      End
      Begin VB.Menu mnuGraphicalPnL 
         Caption         =   "PnL &Projections"
         Shortcut        =   ^A
      End
      Begin VB.Menu mnuFileHedgeSummaryView 
         Caption         =   "&Hedge Summary..."
         Shortcut        =   ^H
      End
      Begin VB.Menu mnuFileReportsView 
         Caption         =   "Re&ports..."
         Shortcut        =   ^J
      End
      Begin VB.Menu mnuFileOrders 
         Caption         =   "Or&ders..."
         Shortcut        =   ^B
      End
      Begin VB.Menu mnuFileTntCards 
         Caption         =   "Trades Messa&ges..."
         Enabled         =   0   'False
         Shortcut        =   ^U
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileStockHedge 
         Caption         =   "Sto&ck Hedge..."
         Enabled         =   0   'False
         Shortcut        =   ^F
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileIndex1Hedge 
         Caption         =   "I&ndex Hedge..."
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileIndex2Hedge 
         Caption         =   "T&wo Indices Hedge..."
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuSepBR1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileBatchReporting 
         Caption         =   "Batch Reporting ..."
      End
      Begin VB.Menu mnuSeparator2 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFilePrint 
         Caption         =   "Print..."
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuSeparator3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolsVolaManager 
         Caption         =   "&Volatility Manager..."
         Shortcut        =   ^{F11}
      End
      Begin VB.Menu mnuToolsStrategyScanner 
         Caption         =   "Strategy Scanner"
      End
      Begin VB.Menu mnuToolsOptionScanner 
         Caption         =   "Options Scanner"
      End
      Begin VB.Menu mnuToolsBackOffice 
         Caption         =   "&Back Office..."
      End
      Begin VB.Menu mnuToolsHedger 
         Caption         =   "&Hedger..."
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuSeparator7 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileClose 
         Caption         =   "&Close"
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "&View"
      Begin VB.Menu mnuViewRefresh 
         Caption         =   "&Refresh"
         Shortcut        =   {F5}
      End
      Begin VB.Menu mnuSeparator4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewFltGridLayout 
         Caption         =   "&Filter Grid Layout..."
      End
      Begin VB.Menu mnuViewInstGridLayout 
         Caption         =   "&Instruments Grid Layout..."
      End
      Begin VB.Menu mnuViewResGridLayout 
         Caption         =   "&Results Grid Layout..."
      End
      Begin VB.Menu mnuViewTotGridLayout 
         Caption         =   "&Totals Grid Layout..."
      End
   End
   Begin VB.Menu mnuOrder 
      Caption         =   "O&rder"
      Begin VB.Menu mnuOrderNewStock 
         Caption         =   "New &Stock Order..."
      End
      Begin VB.Menu mnuOrderNewOption 
         Caption         =   "New &Option Order..."
      End
   End
   Begin VB.Menu mnuTntCard 
      Caption         =   "Trade Messa&ge"
      Enabled         =   0   'False
      Visible         =   0   'False
      Begin VB.Menu mnuTntCardNew 
         Caption         =   "&New Trade Message..."
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuManage 
      Caption         =   "&Manage"
      Begin VB.Menu mnuManageUnderlyings 
         Caption         =   "&Underlyings..."
      End
      Begin VB.Menu mnuExerciseScreen 
         Caption         =   "Exercise Screen..."
      End
      Begin VB.Menu mnuToolsSeparator2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuOptionsParameters 
         Caption         =   "&Parameters..."
         Shortcut        =   ^P
      End
      Begin VB.Menu mnuOptionsEventLog 
         Caption         =   "&Event Log"
         Shortcut        =   ^L
      End
   End
   Begin VB.Menu mnuWindow 
      Caption         =   "&Window"
      Begin VB.Menu mnuWindowArrange 
         Caption         =   "&Arrange"
      End
      Begin VB.Menu mnuWindowCloseAll 
         Caption         =   "&Close All"
      End
      Begin VB.Menu mnuWindowSeparator1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuWindowTileHorizontaly 
         Caption         =   "Tile &Horizontaly"
      End
      Begin VB.Menu mnuWindowTileVertically 
         Caption         =   "Tile &Vertically"
      End
      Begin VB.Menu mnuWindowCascade 
         Caption         =   "Ca&scade"
      End
      Begin VB.Menu mnuWindowSeparator2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuWindowMain 
         Caption         =   "&Main ETS Window..."
         Shortcut        =   {F12}
      End
      Begin VB.Menu mnuWindowShowInTaskBar 
         Caption         =   "&Show All In Taskbar"
      End
      Begin VB.Menu mnuWindowSeparator3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuWindowGo 
         Caption         =   "<win 1>"
         Index           =   1
         Shortcut        =   ^{F1}
         Visible         =   0   'False
      End
      Begin VB.Menu mnuWindowGo 
         Caption         =   "<win 2>"
         Index           =   2
         Shortcut        =   ^{F2}
         Visible         =   0   'False
      End
      Begin VB.Menu mnuWindowGo 
         Caption         =   "<win 3>"
         Index           =   3
         Shortcut        =   ^{F3}
         Visible         =   0   'False
      End
      Begin VB.Menu mnuWindowGo 
         Caption         =   "<win 4>"
         Index           =   4
         Shortcut        =   ^{F4}
         Visible         =   0   'False
      End
      Begin VB.Menu mnuWindowGo 
         Caption         =   "<win 5>"
         Index           =   5
         Shortcut        =   ^{F5}
         Visible         =   0   'False
      End
      Begin VB.Menu mnuWindowGo 
         Caption         =   "<win 6>"
         Index           =   6
         Shortcut        =   ^{F6}
         Visible         =   0   'False
      End
      Begin VB.Menu mnuWindowGo 
         Caption         =   "<win 7>"
         Index           =   7
         Shortcut        =   ^{F7}
         Visible         =   0   'False
      End
      Begin VB.Menu mnuWindowGo 
         Caption         =   "<win 8>"
         Index           =   8
         Shortcut        =   ^{F8}
         Visible         =   0   'False
      End
      Begin VB.Menu mnuWindowGo 
         Caption         =   "<win 9>"
         Index           =   9
         Shortcut        =   ^{F9}
         Visible         =   0   'False
      End
      Begin VB.Menu mnuWindowList 
         Caption         =   "&Windows..."
         Shortcut        =   ^W
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&?"
      Begin VB.Menu mnuHelpContents 
         Caption         =   "&Contents..."
         Shortcut        =   {F1}
      End
   End
End
Attribute VB_Name = "frmHedgeSummaryView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"3E4789250241"
Attribute VB_Ext_KEY = "RVB_ModelStereotype" ,"Form"
Option Explicit

Private WithEvents aParams As clsParams
Attribute aParams.VB_VarHelpID = -1
Private m_sKey As String
Private m_sFilePath As String
Private m_sFileName As String
Private m_bIsNew As Boolean
Private m_nWindowIndex As Long
Private m_sCaption As String
Private m_sShortCaption As String

Private m_bShowInTaskbar As Boolean
Private m_bShowInTaskbarChanging As Boolean
Public Sub ShowDataByFilter(ByRef aFilters As EtsGeneralLib.EtsFilterData)
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "frmHedgeSummary ShowData Call", Me.Caption

    ctlView.ShowDataByFilter aFilters

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "frmHedgeSummary ShowData Done", Me.Caption

End Sub

Public Sub ShowWindowInTaskbar(ByVal bShow As Boolean, Optional ByVal bExtended As Boolean = False)
    On Error Resume Next
    If m_bShowInTaskbar <> bShow Then
        m_bShowInTaskbar = bShow
        mnuWindowShowInTaskbar.Checked = bShow
        m_bShowInTaskbarChanging = True
        
        If bExtended Then SetWindowPos Me.hWnd, 0, 0, 0, 0, 0, SWP_HIDEWINDOW Or SWP_NOSIZE Or SWP_NOMOVE Or SWP_NOZORDER Or SWP_NOACTIVATE
        ShowFormInTaskBar Me, m_bShowInTaskbar
        If bExtended Then SetWindowPos Me.hWnd, 0, 0, 0, 0, 0, SWP_SHOWWINDOW Or SWP_NOSIZE Or SWP_NOMOVE Or SWP_NOZORDER Or SWP_NOACTIVATE
        
        m_bShowInTaskbarChanging = False
    End If
End Sub

Public Sub SetWinIndex(ByVal nIndex As Long)
    On Error Resume Next
    m_nWindowIndex = nIndex
    AdjustCaption
End Sub

Public Function GetCaption() As String
    On Error Resume Next
    GetCaption = m_sCaption
End Function

Public Function GetShortCaption() As String
    On Error Resume Next
    GetShortCaption = m_sShortCaption
End Function

Private Sub aParams_EventLogVisibleChange()
    On Error Resume Next
    mnuOptionsEventLog.Checked = aParams.EventLogVisible
End Sub

Private Sub aParams_NewUnderlyingAdded(ByVal nNewUndID As Long)
    On Error Resume Next
    ctlView.NewUnderlyingAdded nNewUndID
End Sub

Private Sub aParams_NewUnderlyingGroupAdded(ByVal nNewUndGroupID As Long)
    On Error Resume Next
    ctlView.NewUnderlyingGroupAdded nNewUndGroupID
End Sub

Private Sub aParams_NewStrategyAdded(ByVal nStrategyID As Long)
    On Error Resume Next
    ctlView.NewStrategyAdded nStrategyID
End Sub

Private Sub ctlSummary_OnRunHedger(sFileName As String)
'    frmMain.RunHedger sFileName
End Sub

Private Sub ctlView_OnSetCaption()
    On Error Resume Next
    AdjustCaption
    frmMain.AdjustWindowsListCaptions
End Sub

Private Sub AdjustCaption()
    On Error Resume Next
    m_sCaption = ctlView.GetCaption & " - [" & m_sFileName & "]"
    m_sShortCaption = ctlView.GetShortCaption
    Me.Caption = IIf(m_nWindowIndex > 0 And m_nWindowIndex < 10, CStr(m_nWindowIndex) & ": ", "") & m_sCaption
End Sub

Public Sub Init(sKey As String)
    On Error Resume Next

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "HedgeSummary View Init Enter", Me.Caption

    m_nWindowIndex = 0
    m_sFilePath = MakeCommonFilePath("", "", False)
    m_sCaption = ""
    m_sShortCaption = ""
    g_nHedgeSummaryUntitledIdx = g_nHedgeSummaryUntitledIdx + 1
    m_sFileName = "Untitled" & g_nHedgeSummaryUntitledIdx & ".hvw"
    m_bIsNew = True
    m_sKey = sKey
    mnuFileClose.Caption = "Close" & vbTab & "Alt+F4"
'    mnuTntCardNew.Caption = "&New Trade Message..." & vbTab & "Shift+Alt+Ins"
    
    Set ctlView.m_frmOwner = Me
    Set ctlView.pbProgress = pbProgress
    Set ctlView.lblProcess = lblProcess
    Set ctlView.lblStatus = lblStatus
    Set ctlView.lblValue = lblValue
    Set ctlView.imgStop = imgStop
    Set ctlView.imgStopDis = imgStopDis
    
    mnuFileOrders.Visible = g_Params.OrdersVisible
    mnuOrderNewStock.Visible = g_Params.OrdersVisible
    mnuOrderNewOption.Visible = g_Params.OrdersVisible
    mnuOrder.Visible = g_Params.OrdersVisible
    
    mnuFileOrders.Enabled = g_Params.OrdersEnabled
    mnuOrderNewStock.Enabled = g_Params.OrdersEnabled
    mnuOrderNewOption.Enabled = g_Params.OrdersEnabled
    
    mnuOrderNewStock.Caption = "New &Stock Order..." & vbTab & "Alt+Ins"
    mnuOrderNewOption.Caption = "New &Option Order..." & vbTab & "Ctrl+Alt+Ins"
    
    ctlView.Init
    Set aParams = g_Params
    mnuOptionsEventLog.Checked = aParams.EventLogVisible
'    mnuFileQuotation.Enabled = g_bIseEnable
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "HedgeSummary View Init Exit", Me.Caption

End Sub

Public Sub ShowData(Optional ByVal nType As Long = TYPE_UNDERLYING, Optional ByVal nValue As Long = 0)
    On Error Resume Next
    ctlView.ShowData nType, nValue
End Sub

Private Sub ctlView_OnStateChange()
    On Error Resume Next
    mnuViewRefresh.Enabled = ctlView.Group.ID <> 0 And Not ctlView.InProc And _
        Not ctlView.DataLoad And Not ctlView.LastQuoteReqNow And ctlView.Inited And Not ctlView.InCalc
    mnuFileOpen.Enabled = Not ctlView.InProc And Not ctlView.DataLoad And _
        Not ctlView.LastQuoteReqNow And ctlView.Inited And Not ctlView.InCalc
End Sub

Private Sub Form_Load()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "HedgeSummary View Load Enter", Me.Caption
    
    If gCmn Is Nothing Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "HedgeSummary View Load Exit - Not Done", Me.Caption

        Exit Sub
    End If
    m_bShowInTaskbar = True
    mnuWindowShowInTaskbar.Checked = True
    lblStatus.Caption = ""
    lblProcess.Caption = ""
    lblValue.Caption = ""
    
    mnuToolsOptionScanner.Enabled = g_bIsScannersEnable
    mnuToolsStrategyScanner.Enabled = g_bIsScannersEnable

    g_Params.SetIcon WND_HEDGESUMARY, Me.hWnd, False

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "HedgeSummary View Load Exit - Done", Me.Caption
    
End Sub

Private Sub Form_Resize()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Resize Enter", Me.Caption
    
    If gCmn Is Nothing Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Resize Exit - Not Done", Me.Caption
        Exit Sub
    End If
    
    LockWindowUpdate Me.hWnd
    
    ctlView.Move 0, 0, ScaleWidth, ScaleHeight - sbStatus.Height
    picBottom.Move 0, ScaleHeight - picBottom.Height, ScaleWidth - 300, picBottom.Height
    lblValue.Left = picBottom.ScaleWidth - lblValue.Width

    LockWindowUpdate 0
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Resize Exit - Done", Me.Caption
    
End Sub

Private Sub Form_Terminate()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Terminate Enter", Me.Caption
    
    If gCmn Is Nothing Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Terminate Exit - Not Done", Me.Caption
        Exit Sub
    End If
    Set aParams = Nothing
    
    ctlView.Term

    g_ViewFrm.Remove m_sKey
    frmMain.ReloadWindowsList
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Terminate Exit -  Done", Me.Caption
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "HedgeSummary View Unload", Me.Caption
    Form_Terminate
End Sub

Private Sub Form_Activate()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Activate Enter", Me.Caption
    
    If gCmn Is Nothing Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Activate Exit - Not Done", Me.Caption

        Exit Sub
    End If
    If Not m_bShowInTaskbarChanging Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Activate Exit - Not Done", Me.Caption
        Exit Sub
    End If
    If Not m_bShowInTaskbar Then
        ShowFormInTaskBar Me, False
    End If
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Activate Exit - Done", Me.Caption
    
End Sub

Private Sub Form_Deactivate()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Deactivate Enter", Me.Caption
    
    If gCmn Is Nothing Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Deactivate Exit - Not Done", Me.Caption
        Exit Sub
    End If
    If m_bShowInTaskbarChanging Then
        If Not g_PerformanceLog Is Nothing Then _
           g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Deactivate Exit - Not Done", Me.Caption
        Exit Sub
    End If
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "HedgeSummary View Deactivate Exit - Done", Me.Caption
    
End Sub

Private Sub mnuFileBatchReporting_Click()
    On Error Resume Next
    g_frmProjections.ShowData
End Sub

Private Sub mnuFileClose_Click()
    On Error Resume Next
    Unload Me
End Sub

Private Sub Save(ByVal sFilePath As String, ByVal sFileName As String)
    Dim aStorage As New clsSettingsStorage
    Screen.MousePointer = vbHourglass
    aStorage.Init sFilePath & sFileName
    aStorage.SetStringValue "Type", "Value", "HedgeSummaryView"
    ctlView.SaveToFile aStorage, ""
    aStorage.SaveData
    m_sFilePath = sFilePath
    m_sFileName = sFileName
    m_bIsNew = False
    AdjustCaption
    Screen.MousePointer = vbDefault
End Sub

Public Sub SaveLayout(aStorage As clsSettingsStorage, ByVal sKey As String)
    ctlView.SaveToFile aStorage, sKey
End Sub

Public Sub OpenLayout(aStorage As clsSettingsStorage, ByVal sKey As String)
    ctlView.OpenFromFile aStorage, sKey
End Sub

Private Sub mnuFileNew_Click()
    On Error Resume Next
    frmMain.ShowHedgeSummary
End Sub

Private Sub mnuFilePrint_Click()
    On Error Resume Next
'    ctlView.PrintView
End Sub

Private Sub mnuFileQuotes_Click()
    On Error Resume Next
    frmMain.ShowQuotes TYPE_UNDERLYING, IIf(ctlView.Group.GroupType = TYPE_UNDERLYING, ctlView.Group.ID, 0)
End Sub

Private Sub mnuFileReportsView_Click()
    On Error Resume Next
    frmMain.ShowReports ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileRiskMatrix_Click()
    On Error Resume Next
    frmMain.ShowRiskMatrix ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileRisks_Click()
    On Error Resume Next
    frmMain.ShowRisks ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileTrades_Click()
    On Error Resume Next
    frmMain.ShowTrades ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileVola_Click()
    On Error Resume Next
    frmMain.ShowVola ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileQuotation_Click()
    On Error Resume Next
'    frmMain.ShowQuotation TYPE_UNDERLYING, IIf(ctlView.Group.GroupType = TYPE_UNDERLYING, ctlView.Group.ID, 0)
End Sub

Private Sub mnuFileVolaAnalysis_Click()
    On Error Resume Next
    frmMain.ShowVolaAnalysis ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileGreeks_Click()
    On Error Resume Next
    frmMain.ShowGreeks ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileHedgeSummaryView_Click()
    On Error Resume Next
    frmMain.ShowHedgeSummary ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileOrders_Click()
    On Error Resume Next
    frmMain.ShowOrders ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileTntCards_Click()
    On Error Resume Next
'    frmMain.ShowTntCards ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileStockHedge_Click()
    On Error Resume Next
'    frmMain.ShowStockHedge ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileIndex1Hedge_Click()
    On Error Resume Next
'    frmMain.ShowIndex1Hedge ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileIndex2Hedge_Click()
    On Error Resume Next
'    frmMain.ShowIndex2Hedge ctlView.Group.GroupType, ctlView.Group.ID
End Sub

Private Sub mnuFileSave_Click()
    On Error GoTo EH
    
    If m_bIsNew Then
        With dlgCommon
            .Flags = cdlOFNExplorer Or cdlOFNLongNames Or cdlOFNPathMustExist _
                    Or cdlOFNHideReadOnly Or cdlOFNNoReadOnlyReturn Or cdlOFNOverwritePrompt
            .CancelError = True
            .DefaultExt = ".hvw"
            .DialogTitle = "Save Hedge Summary"
            .InitDir = ""
            .FileName = m_sFilePath & m_sFileName
            .Filter = "ETS Quotes (*.hvw)|*.hvw|All Files|*.*"
            .FilterIndex = 1
            On Error Resume Next
            .ShowSave
            If Err.Number = 0 Then
                On Error GoTo EH
                Save ExtractFilePath(.FileName), ExtractFileName(.FileName)
            End If
        End With
    Else
        Save m_sFilePath, m_sFileName
    End If
    Exit Sub
EH:
    Screen.MousePointer = vbDefault
    gCmn.ErrorMsgBox Me, "Fail to save hedge summary."
End Sub

Private Sub mnuFileSaveAs_Click()
    On Error GoTo EH
    
    With dlgCommon
        .Flags = cdlOFNExplorer Or cdlOFNLongNames Or cdlOFNPathMustExist _
                Or cdlOFNHideReadOnly Or cdlOFNNoReadOnlyReturn Or cdlOFNOverwritePrompt
        .CancelError = True
        .DefaultExt = ".hvw"
        .DialogTitle = "Save Hedge Summary As"
        .InitDir = ""
        .FileName = m_sFilePath & m_sFileName
        .Filter = "ETS Hedge Summary (*.hvw)|*.hvw|All Files|*.*"
        .FilterIndex = 1
        On Error Resume Next
        .ShowSave
        If Err.Number = 0 Then
            On Error GoTo EH
            Save ExtractFilePath(.FileName), ExtractFileName(.FileName)
        End If
    End With
    Exit Sub
EH:
    Screen.MousePointer = vbDefault
    gCmn.ErrorMsgBox Me, "Fail to save hedge summary."
End Sub

Private Sub mnuFileOpen_Click()
    On Error GoTo EH
    Dim aStorage As New clsSettingsStorage
    
    With dlgCommon
        .Flags = cdlOFNExplorer Or cdlOFNLongNames Or cdlOFNPathMustExist _
                Or cdlOFNHideReadOnly Or cdlOFNFileMustExist
        .CancelError = True
        .DefaultExt = ".hvw"
        .DialogTitle = "Open Hedge Summary"
        .FileName = ""
        .InitDir = m_sFilePath
        .Filter = "ETS Hedge Summary (*.hvw)|*.hvw|All Files|*.*"
        .FilterIndex = 1
        On Error Resume Next
        .ShowOpen
        If Err.Number = 0 Then
            On Error GoTo EH
            Screen.MousePointer = vbHourglass
            aStorage.Init .FileName
            aStorage.ReadData
            If aStorage.GetStringValue("Type", "Value") = "HedgeSummaryView" Then
                ctlView.OpenFromFile aStorage, ""
                m_sFilePath = ExtractFilePath(.FileName)
                m_sFileName = ExtractFileName(.FileName)
                m_bIsNew = False
                AdjustCaption
                Screen.MousePointer = vbDefault
            Else
                Screen.MousePointer = vbDefault
                gCmn.MyMsgBox Me, "Invalid hedge summary file."
            End If
        End If
    End With
    Exit Sub
EH:
    Screen.MousePointer = vbDefault
    gCmn.ErrorMsgBox Me, "Fail to open hedge summary."
End Sub

Private Sub mnuGraphicalPnL_Click()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
    g_PerformanceLog.LogMmInfo enLogUserAction, "Menu ""HedgeSummaryView->File->PnL Projections"" Enter. ", Me.Caption
    
    If ctlView.Filter(HFC_GROUP) = TYPE_UNDERLYING Then
        frmMain.ShowGraphicalPnL TYPE_UNDERLYING, ctlView.Filter(HFC_VALUE)
    Else
        frmMain.ShowGraphicalPnL TYPE_UNDERLYING
    End If
    
    If Not g_PerformanceLog Is Nothing Then _
    g_PerformanceLog.LogMmInfo enLogUserAction, "Menu ""HedgeSummaryView->File->PnL Projections"" Exit. ", Me.Caption
End Sub

Private Sub mnuOptionsParameters_Click()
    On Error Resume Next
    frmMain.ShowParameters
End Sub

Private Sub mnuViewFltGridLayout_Click()
    On Error Resume Next
    ctlView.CustomizeFltGridLayout
End Sub

Private Sub mnuViewInstGridLayout_Click()
    On Error Resume Next
    ctlView.CustomizeInstGridLayout
End Sub

Private Sub mnuViewResGridLayout_Click()
    On Error Resume Next
    ctlView.CustomizeResGridLayout
End Sub

Private Sub mnuViewTotGridLayout_Click()
    On Error Resume Next
    ctlView.CustomizeTotGridLayout
End Sub

Private Sub mnuViewRefresh_Click()
    On Error Resume Next
    ctlView.Refresh
End Sub

Private Sub mnuOptionsEventLog_Click()
    On Error Resume Next
    ShowEventLog (Not mnuOptionsEventLog.Checked), , True
End Sub

Private Sub mnuToolsBackOffice_Click()
    On Error Resume Next
    frmMain.RunBackOffice
End Sub
Private Sub mnuToolsOptionScanner_Click()
    On Error Resume Next
    frmMain.RunOptionScanner
End Sub

Private Sub mnuToolsStrategyScanner_Click()
    On Error Resume Next
    frmMain.RunStrategyScanner
End Sub

Private Sub mnuToolsHedger_Click()
    On Error Resume Next
    ctlView.PrepareHedgeFile
End Sub

Private Sub mnuToolsVolaManager_Click()
    On Error Resume Next
    frmMain.RunVolaManager
End Sub

Public Sub AdjustWindowsListCaptions()
    On Error Resume Next
    Dim i&, nCount&
    
    nCount = g_ViewFrm.Count
    For i = 1 To 9
        If i <= nCount Then
            mnuWindowGo(i).Caption = "&" & CStr(i) & " " & g_ViewFrm(i).Frm.GetCaption
            mnuWindowGo(i).Visible = True
            mnuWindowGo(i).Enabled = True
        Else
            mnuWindowGo(i).Visible = False
            mnuWindowGo(i).Enabled = False
        End If
    Next
End Sub

Private Sub mnuWindowArrange_Click()
    On Error Resume Next
    frmMain.WindowsArrange
End Sub

Private Sub mnuWindowCloseAll_Click()
    On Error Resume Next
    frmMain.WindowsCloseAll
End Sub

Private Sub mnuWindowList_Click()
    On Error Resume Next
    frmMain.WindowsList
End Sub

Private Sub mnuWindowMain_Click()
    On Error Resume Next
    ShowWindow frmMain.hWnd, SW_SHOWNORMAL
    frmMain.SetFocus
End Sub

Private Sub mnuWindowTileHorizontaly_Click()
    On Error Resume Next
    frmMain.WindowsTileHorizontally
End Sub

Private Sub mnuWindowTileVertically_Click()
    On Error Resume Next
    frmMain.WindowsTileVertically
End Sub

Private Sub mnuWindowCascade_Click()
    On Error Resume Next
    frmMain.WindowsCascade
End Sub

Private Sub mnuWindowShowInTaskBar_Click()
    On Error Resume Next
    frmMain.WindowsShowInTaskBar Not g_Params.ShowWindowsInTaskbar
End Sub

Private Sub mnuWindowGo_Click(Index As Integer)
    On Error Resume Next
    frmMain.WindowsGo Index
End Sub

Public Sub SetGridLayout(ByVal enGridType As GridTypeEnum, gdGrid As clsGridDef)
    On Error Resume Next
    ctlView.SetGridLayout enGridType, gdGrid
End Sub

Private Sub mnuHelpContents_Click()
    On Error Resume Next
    frmMain.HelpContents
End Sub

Public Property Get WindowKey() As String
    On Error Resume Next
    WindowKey = m_sKey
End Property

Private Sub mnuManageUnderlyings_Click()
    On Error Resume Next
    frmMain.ShowManageUnderlyings
End Sub

Private Sub mnuOrderNewOption_Click()
    On Error Resume Next
    frmOrderEntry.NewOptionOrder Nothing, Nothing, True, 10, 0#
End Sub

Private Sub mnuOrderNewStock_Click()
    On Error Resume Next
    frmOrderEntry.NewStockOrder Nothing, True, 100, 0#
End Sub

Private Sub mnuTntCardNew_Click()
    On Error Resume Next
'    frmTntCardEntry.NewCard Me, Nothing, Nothing, True, 10, 0#
End Sub

Private Sub mnuExerciseScreen_Click()
    On Error Resume Next
    frmMain.ShowExerciseScreen
End Sub
