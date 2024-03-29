VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsInterestRateColl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'local variable to hold collection
Private m_Col As Collection

Public Function Add(sKey As String, Optional aItem As clsInterestRateAtom = Nothing) As clsInterestRateAtom
    'create a new object
    Dim objNewMember As clsInterestRateAtom
    
    If aItem Is Nothing Then
        Set objNewMember = New clsInterestRateAtom
    Else
        Set objNewMember = aItem
    End If

    'set the properties passed into the method
    If Len(sKey) = 0 Then
        m_Col.Add objNewMember
    Else
        m_Col.Add objNewMember, sKey
    End If


    'return the object created
    Set Add = objNewMember
    Set objNewMember = Nothing
End Function

Public Property Get Item(vntIndexKey As Variant) As clsInterestRateAtom
    'used when referencing an element in the collection
    'vntIndexKey contains either the Index or Key to the collection,
    'this is why it is declared as a Variant
    'Syntax: Set foo = x.Item(xyz) or Set foo = x.Item(5)
    On Error Resume Next
    Set Item = m_Col(vntIndexKey)
End Property

Public Property Get Count() As Long
    'used when retrieving the number of elements in the
    'collection. Syntax: Debug.Print x.Count
    Count = m_Col.Count
End Property

Public Sub Remove(vntIndexKey As Variant)
    'used when removing an element from the collection
    'vntIndexKey contains either the Index or Key, which is why
    'it is declared as a Variant
    'Syntax: x.Remove(xyz)
    On Error Resume Next
    m_Col.Remove vntIndexKey
End Sub

Public Sub Clear()
    On Error Resume Next
    Set m_Col = Nothing
    Set m_Col = New Collection
End Sub

Public Property Get NewEnum() As IUnknown
    'this property allows you to enumerate
    'this collection with the For...Each syntax
    On Error Resume Next
    Set NewEnum = m_Col.[_NewEnum]
End Property

Private Sub Class_Initialize()
    'creates the collection when this class is created
    Set m_Col = New Collection
End Sub

Private Sub Class_Terminate()
    On Error Resume Next
    'destroys collection when this class is terminated
    Set m_Col = Nothing
End Sub


