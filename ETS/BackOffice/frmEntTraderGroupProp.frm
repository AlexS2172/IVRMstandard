VERSION 5.00
Object = "{E5B04F18-C63E-465D-B0C6-E598BBF429FE}#2.0#0"; "ElladaFlatControls.ocx"
Begin VB.Form frmEntTraderGroupProp 
   BackColor       =   &H80000005&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Traders Group Properties"
   ClientHeight    =   3825
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5235
   Icon            =   "frmEntTraderGroupProp.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3825
   ScaleWidth      =   5235
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   3135
      Left            =   120
      ScaleHeight     =   3105
      ScaleWidth      =   4935
      TabIndex        =   0
      Top             =   120
      Width           =   4965
      Begin VB.ListBox lstSrc 
         Appearance      =   0  'Flat
         Height          =   2565
         Left            =   120
         MultiSelect     =   2  'Extended
         TabIndex        =   2
         Top             =   360
         Width           =   1935
      End
      Begin VB.ListBox lstDest 
         Appearance      =   0  'Flat
         Height          =   2565
         Left            =   2880
         MultiSelect     =   2  'Extended
         TabIndex        =   1
         Top             =   360
         Width           =   1935
      End
      Begin ElladaFlatControls.FlatButton btnMoveLeftAll 
         Height          =   300
         Left            =   2160
         TabIndex        =   3
         Top             =   2280
         Width           =   615
         _ExtentX        =   1085
         _ExtentY        =   529
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Caption         =   "<<"
      End
      Begin ElladaFlatControls.FlatButton btnMoveRightAll 
         Height          =   300
         Left            =   2160
         TabIndex        =   4
         Top             =   1920
         Width           =   615
         _ExtentX        =   1085
         _ExtentY        =   529
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Caption         =   ">>"
      End
      Begin ElladaFlatControls.FlatButton btnMoveLeftOne 
         Height          =   300
         Left            =   2160
         TabIndex        =   5
         Top             =   1080
         Width           =   615
         _ExtentX        =   1085
         _ExtentY        =   529
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Caption         =   "<"
      End
      Begin ElladaFlatControls.FlatButton btnMoveRightOne 
         Height          =   300
         Left            =   2160
         TabIndex        =   6
         Top             =   720
         Width           =   615
         _ExtentX        =   1085
         _ExtentY        =   529
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Caption         =   ">"
      End
      Begin VB.Label lblDest 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "Traders In Group"
         Height          =   195
         Left            =   2640
         TabIndex        =   8
         Top             =   120
         Width           =   2100
         WordWrap        =   -1  'True
      End
      Begin VB.Label lblSrc 
         Alignment       =   2  'Center
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "Available Traders"
         Height          =   195
         Left            =   -90
         TabIndex        =   7
         Top             =   120
         Width           =   2355
         WordWrap        =   -1  'True
      End
   End
   Begin ElladaFlatControls.FlatButton btnCancel 
      Cancel          =   -1  'True
      Height          =   300
      Left            =   3720
      TabIndex        =   9
      Top             =   3360
      Width           =   1335
      _ExtentX        =   2355
      _ExtentY        =   529
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Caption         =   "&Cancel"
   End
   Begin ElladaFlatControls.FlatButton btnOk 
      Default         =   -1  'True
      Height          =   300
      Left            =   2280
      TabIndex        =   10
      Top             =   3360
      Width           =   1335
      _ExtentX        =   2355
      _ExtentY        =   529
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Caption         =   "&OK"
   End
   Begin VB.Image imgSave 
      Height          =   240
      Left            =   120
      Picture         =   "frmEntTraderGroupProp.frx":000C
      Top             =   3360
      Visible         =   0   'False
      Width           =   240
   End
End
Attribute VB_Name = "frmEntTraderGroupProp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
' Edit Traders list for RM
'
Option Explicit

Private m_ItemID As Long
Private m_ItemName As String
Private m_bChanged As Boolean
Private m_bOK As Boolean
Private rsList As ADODB.Recordset
Private m_Edit As Boolean

'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Public Function Execute(ByVal ItemID As Long, ByVal ItemName As String) As Boolean
    On Error GoTo Herr
    Screen.MousePointer = vbHourglass
    m_ItemID = ItemID
    m_ItemName = ItemName
    Load Me
    Me.Caption = m_ItemName & " Properties"
    m_bOK = False
    m_Edit = False
    If LoadData Then
        Changed = False
        CheckButtonsState
        Screen.MousePointer = vbDefault
        m_Edit = True
        Show vbModal
    End If
    Unload Me
    Execute = m_bOK
    Exit Function
Herr:
    Screen.MousePointer = vbDefault
    ShowError
End Function

'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Sub btnOK_Click()
    On Error GoTo Herr
    Screen.MousePointer = vbHourglass
    m_bOK = SaveData
    Screen.MousePointer = vbDefault
    If m_bOK Then Hide
    Exit Sub
Herr:
    Screen.MousePointer = vbDefault
    ShowError
End Sub

'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Sub btnCancel_Click()
    On Error Resume Next
    Me.Hide
End Sub

'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Sub Form_Load()
    On Error Resume Next
    If gCmn Is Nothing Then Exit Sub
    gCmn.CustomizeForm Me
    imgSave.Visible = False
    imgSave.ToolTipText = "Data has been changed"
End Sub

'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Property Get Changed() As Boolean
    Changed = m_bChanged
End Property

'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Property Let Changed(ByVal vNewValue As Boolean)
    m_bChanged = vNewValue
    imgSave.Visible = NeedSaveData
End Property

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
' Load data from database
'
Private Function LoadData() As Boolean
Dim rsFull As ADODB.Recordset
Dim rsSelected As ADODB.Recordset
Dim Title As String
Dim ID As Long
Dim Selected As Boolean
    
    ' Prepare internal recordset
    Set rsList = New ADODB.Recordset
    With rsList
        With .Fields
            .Append "ID", adInteger
            .Append "Name", adVarChar, 64
            .Append "OldValue", adBoolean
            .Append "NewValue", adBoolean
            .Append "Changed", adBoolean
            .Append "ToDelete", adBoolean
            .Append "ToInsert", adBoolean
        End With
        .Open
    End With
    
    ' Load items list
    Set rsFull = gDBW.usp_BoTrader_Get(Null)
    If Not rsFull Is Nothing Then
        With rsFull
            If .RecordCount > 0 Then
                .MoveFirst
                Do While Not .EOF
                    ID = !iTraderID
                    Title = !vcTraderName
                    
                    With rsList
                        .AddNew
                        !ID = ID
                        !Name = Title
                        !OldValue = False
                        !NewValue = False
                        !Changed = False
                        !ToDelete = False
                        !ToInsert = False
                        .Update
                    End With
                    .MoveNext
                Loop
            End If
        End With
    End If
    
    ' Load selected items list for the current group
    Set rsSelected = gDBW.usp_BoTraderInGroup_Get(m_ItemID)
    If Not rsSelected Is Nothing Then
        With rsSelected
            If .RecordCount > 0 Then
                .MoveFirst
                Do While Not .EOF
                    ID = !iTraderID
                    Title = !vcTraderName
                    With rsList
                        If .RecordCount > 0 Then
                            .MoveFirst
                        End If
                        .Find "ID=" & Format$(ID)
                        If Not .EOF Then
                            !OldValue = True
                            .Update
                        Else
                            .AddNew
                            !ID = ID
                            !Name = Title
                            !OldValue = True
                            !NewValue = False
                            !Changed = False
                            !ToDelete = False
                            !ToInsert = False
                            .Update
                        End If
                    End With
                    .MoveNext
                Loop
            End If
        End With
    End If
    
    lstSrc.Clear
    lstDest.Clear
    
    With rsList
        If .RecordCount > 0 Then
            .Sort = "Name"
            .MoveFirst
            Do While Not .EOF
                ID = !ID
                Title = !Name
                If !OldValue Then
                    With lstDest
                        .AddItem Title
                        .ItemData(.NewIndex) = ID
                    End With
                Else
                    With lstSrc
                        .AddItem Title
                        .ItemData(.NewIndex) = ID
                    End With
                End If
                .MoveNext
            Loop
        End If
    End With
    
    LoadData = True
End Function

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
' Save data into database
'
Private Function SaveData() As Boolean
Dim I As Long
Dim ID As Long
    
    With lstDest
        For I = 0 To .ListCount - 1
            ID = .ItemData(I)
            With rsList
                .MoveFirst
                .Find "ID=" & Format$(ID)
                If Not .EOF Then
                    !NewValue = True
                    If !NewValue <> !OldValue Then
                        !Changed = True
                    End If
                   .Update
                Else
                    Debug.Assert False
                End If
            End With
        Next I
    End With
    
    With lstSrc
        For I = 0 To .ListCount - 1
            ID = .ItemData(I)
            With rsList
                .MoveFirst
                .Find "ID=" & Format$(ID)
                If Not .EOF Then
                    !NewValue = False
                    If !NewValue <> !OldValue Then
                        !Changed = True
                    End If
                   .Update
                Else
                    Debug.Assert False
                End If
            End With
        Next I
    End With
    
    ' Detect changed items
    With rsList
        .Filter = "Changed = TRUE"
        If .RecordCount > 0 Then
            .MoveFirst
            Do While Not .EOF
                If !NewValue = True Then
                    !ToInsert = True
                Else
                    !ToDelete = True
                End If
                .Update
                .MoveNext
            Loop
        End If
    End With
    
    ' Remove deselected items
    With rsList
        .Filter = "ToDelete = true"
        If .RecordCount > 0 Then
            .MoveFirst
            Do While Not .EOF
                ID = !ID
                gDBW.usp_BoTrader_Save ID, Null, Null, Null, Null
                .MoveNext
            Loop
        End If
    End With
    
    ' Insert selected items
    With rsList
        .Filter = "ToInsert = true"
        If .RecordCount > 0 Then
            .MoveFirst
            Do While Not .EOF
                ID = !ID
                gDBW.usp_BoTrader_Save ID, Null, Null, Null, m_ItemID
                .MoveNext
            Loop
        End If
    End With

    SaveData = True
End Function

'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Function NeedSaveData() As Boolean
Dim I As Long
Dim ID As Long
Dim Selected As Boolean
    On Error GoTo Herr
    ' Scan listbox to detect changes
    With lstDest
        For I = 0 To .ListCount - 1
            ID = .ItemData(I)
            With rsList
                .MoveFirst
                .Find "ID=" & Format$(ID)
                If Not .EOF Then
                    Selected = True
                    If Selected <> !OldValue Then
                        NeedSaveData = True
                        Exit Function
                    End If
                   .Update
                Else
                    Debug.Assert False
                End If
            End With
        Next I
    End With
    With lstSrc
        For I = 0 To .ListCount - 1
            ID = .ItemData(I)
            With rsList
                .MoveFirst
                .Find "ID=" & Format$(ID)
                If Not .EOF Then
                    Selected = False
                    If Selected <> !OldValue Then
                        NeedSaveData = True
                        Exit Function
                    End If
                   .Update
                Else
                    Debug.Assert False
                End If
            End With
        Next I
    End With
    Exit Function
Herr:
    Debug.Print Err.Description
    Debug.Assert False
End Function

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
' proc for moving list's items from Src to Dest
' Opt=0 - move only selected items, Opt=1 - move all items
'
Private Sub MoveItem(ByRef Src As ListBox, ByRef Dest As ListBox, ByVal Opt As Long)
Dim I As Long
Dim s As String
Dim ID As Long
Dim inx As Long
    On Error GoTo Herr
    With Src
        I = 0
        Do While I < .ListCount
            If ((Opt = 0) And (.Selected(I))) Or (Opt > 0) Then
                s = .List(I)
                ID = .ItemData(I)
                .RemoveItem I
                With Dest
                    .AddItem s
                    .ItemData(.NewIndex) = ID
                    .ListIndex = .NewIndex
                    .Selected(.NewIndex) = True
                End With
            Else
                I = I + 1
            End If
        Loop
    End With
    CheckButtonsState
    Changed = True
    Exit Sub
Herr:
    ShowError "Unable to move an item"
End Sub

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
' searching for an item index in a listbox
'
Private Function FindItem(ByRef lst As ListBox, ByVal Item As Long) As Long
Dim I As Long
    On Error GoTo Herr
    FindItem = -1
    With lst
        For I = 0 To .ListCount - 1
            If .ItemData(I) = Item Then
                FindItem = I
                Exit Function
            End If
        Next I
    End With
    Exit Function
Herr:
    ShowError "Unable to find an item"
End Function

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Sub btnMoveRightOne_Click()
    On Error Resume Next
    If m_Edit Then
        MoveItem lstSrc, lstDest, 0
    End If
End Sub

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Sub btnMoveLeftOne_Click()
    On Error Resume Next
    If m_Edit Then
        MoveItem lstDest, lstSrc, 0
    End If
End Sub

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Sub btnMoveRightAll_Click()
    On Error Resume Next
    If m_Edit Then
        MoveItem lstSrc, lstDest, 1
    End If
End Sub

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Sub btnMoveLeftAll_Click()
    On Error Resume Next
    If m_Edit Then
        MoveItem lstDest, lstSrc, 1
    End If
End Sub

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Sub lstDest_DblClick()
    On Error Resume Next
    If m_Edit Then
        MoveItem lstDest, lstSrc, 0
    End If
End Sub

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Sub lstSrc_DblClick()
    On Error Resume Next
    If m_Edit Then
        MoveItem lstSrc, lstDest, 0
    End If
End Sub

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Sub lstDest_Click()
    On Error Resume Next
    If m_Edit Then
        CheckButtonsState
    End If
End Sub

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'
Private Sub lstSrc_Click()
    On Error Resume Next
    If m_Edit Then
        CheckButtonsState
    End If
End Sub

' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
' enabling move buttons
'
Private Sub CheckButtonsState()
Dim I As Long
Dim b As Boolean
    On Error Resume Next
    
    b = False
    If lstDest.ListCount > 0 Then
        btnMoveLeftAll.Enabled = True
        With lstDest
            For I = 0 To .ListCount - 1
                If .Selected(I) Then
                    b = True
                    Exit For
                End If
            Next
        End With
        btnMoveLeftOne.Enabled = b
    Else
        btnMoveLeftAll.Enabled = False
        btnMoveLeftOne.Enabled = False
    End If
    
    b = False
    If lstSrc.ListCount > 0 Then
        btnMoveRightAll.Enabled = True
        With lstSrc
            For I = 0 To .ListCount - 1
                If .Selected(I) Then
                    b = True
                    Exit For
                End If
            Next
        End With
        btnMoveRightOne.Enabled = b
    Else
        btnMoveRightOne.Enabled = False
        btnMoveRightAll.Enabled = False
    End If

End Sub

