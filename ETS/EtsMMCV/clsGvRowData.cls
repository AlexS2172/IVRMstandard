VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsGvRowData"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Und As EtsMmRisksLib.MmRvUndAtom
Public SynthUndID As Long

Public ParamIdx As Long

Private Sub Class_Initialize()
    On Error Resume Next
    SynthUndID = 0&
    
    ParamIdx = BAD_LONG_VALUE
End Sub

Private Sub Class_Terminate()
    On Error Resume Next
    Set Und = Nothing
End Sub
