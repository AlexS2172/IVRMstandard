VERSION 5.00
Object = "{D76D7128-4A96-11D3-BD95-D296DC2DD072}#1.0#0"; "vsflex7.ocx"
Object = "{0AFE7BE0-11B7-4A3E-978D-D4501E9A57FE}#1.0#0"; "c1Sizer.ocx"
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomct2.ocx"
Begin VB.UserControl ctlQuotesViewSingle 
   ClientHeight    =   8265
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   10155
   KeyPreview      =   -1  'True
   ScaleHeight     =   8265
   ScaleWidth      =   10155
   Begin VB.Timer tmrPriceProviderIdle 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   8640
      Top             =   480
   End
   Begin VB.Timer tmrSwitchFutures 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   8160
      Top             =   480
   End
   Begin C1SizerLibCtl.C1Elastic estQuotes 
      Height          =   6615
      Left            =   0
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   1560
      Width           =   10035
      _cx             =   17701
      _cy             =   11668
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Enabled         =   -1  'True
      Appearance      =   4
      MousePointer    =   0
      Version         =   801
      BackColor       =   4210752
      ForeColor       =   -2147483630
      FloodColor      =   6553600
      ForeColorDisabled=   -2147483631
      Caption         =   ""
      Align           =   0
      AutoSizeChildren=   4
      BorderWidth     =   0
      ChildSpacing    =   1
      Splitter        =   -1  'True
      FloodDirection  =   0
      FloodPercent    =   0
      CaptionPos      =   1
      WordWrap        =   -1  'True
      MaxChildSize    =   0
      MinChildSize    =   0
      TagWidth        =   0
      TagPosition     =   0
      Style           =   0
      TagSplit        =   2
      PicturePos      =   4
      CaptionStyle    =   0
      ResizeFonts     =   0   'False
      GridRows        =   0
      GridCols        =   0
      Frame           =   3
      FrameStyle      =   0
      FrameWidth      =   1
      FrameColor      =   -2147483628
      FrameShadow     =   -2147483632
      FloodStyle      =   1
      _GridInfo       =   ""
      AccessibleName  =   ""
      AccessibleDescription=   ""
      AccessibleValue =   ""
      AccessibleRole  =   9
      Begin C1SizerLibCtl.C1Elastic estOpt 
         Height          =   4725
         Left            =   0
         TabIndex        =   6
         TabStop         =   0   'False
         Top             =   0
         Width           =   10035
         _cx             =   17701
         _cy             =   8334
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   -1  'True
         Appearance      =   4
         MousePointer    =   0
         Version         =   801
         BackColor       =   -2147483633
         ForeColor       =   -2147483630
         FloodColor      =   6553600
         ForeColorDisabled=   -2147483631
         Caption         =   ""
         Align           =   0
         AutoSizeChildren=   2
         BorderWidth     =   0
         ChildSpacing    =   1
         Splitter        =   0   'False
         FloodDirection  =   0
         FloodPercent    =   0
         CaptionPos      =   1
         WordWrap        =   -1  'True
         MaxChildSize    =   0
         MinChildSize    =   0
         TagWidth        =   0
         TagPosition     =   0
         Style           =   0
         TagSplit        =   2
         PicturePos      =   4
         CaptionStyle    =   0
         ResizeFonts     =   0   'False
         GridRows        =   0
         GridCols        =   0
         Frame           =   3
         FrameStyle      =   0
         FrameWidth      =   1
         FrameColor      =   -2147483628
         FrameShadow     =   -2147483632
         FloodStyle      =   1
         _GridInfo       =   ""
         AccessibleName  =   ""
         AccessibleDescription=   ""
         AccessibleValue =   ""
         AccessibleRole  =   9
         Begin VSFlex7Ctl.VSFlexGrid fgOpt 
            Height          =   4725
            Left            =   0
            TabIndex        =   7
            Top             =   0
            Width           =   10035
            _cx             =   17701
            _cy             =   8334
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
      End
      Begin C1SizerLibCtl.C1Elastic estFut 
         Height          =   1875
         Left            =   0
         TabIndex        =   5
         TabStop         =   0   'False
         Top             =   4740
         Width           =   10035
         _cx             =   17701
         _cy             =   3307
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   -1  'True
         Appearance      =   4
         MousePointer    =   0
         Version         =   801
         BackColor       =   -2147483633
         ForeColor       =   -2147483630
         FloodColor      =   6553600
         ForeColorDisabled=   -2147483631
         Caption         =   ""
         Align           =   0
         AutoSizeChildren=   1
         BorderWidth     =   0
         ChildSpacing    =   1
         Splitter        =   0   'False
         FloodDirection  =   0
         FloodPercent    =   0
         CaptionPos      =   1
         WordWrap        =   -1  'True
         MaxChildSize    =   0
         MinChildSize    =   0
         TagWidth        =   0
         TagPosition     =   0
         Style           =   0
         TagSplit        =   2
         PicturePos      =   4
         CaptionStyle    =   0
         ResizeFonts     =   0   'False
         GridRows        =   0
         GridCols        =   0
         Frame           =   3
         FrameStyle      =   0
         FrameWidth      =   1
         FrameColor      =   -2147483628
         FrameShadow     =   -2147483632
         FloodStyle      =   1
         _GridInfo       =   ""
         AccessibleName  =   ""
         AccessibleDescription=   ""
         AccessibleValue =   ""
         AccessibleRole  =   9
         Begin VSFlex7Ctl.VSFlexGrid fgFut 
            Height          =   1875
            Left            =   0
            TabIndex        =   8
            Top             =   0
            Width           =   10035
            _cx             =   17701
            _cy             =   3307
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
      End
   End
   Begin VB.Timer tmrQuoteCalculation 
      Enabled         =   0   'False
      Interval        =   10
      Left            =   7680
      Top             =   480
   End
   Begin VB.Timer tmrTradesProcessing 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   7680
      Top             =   0
   End
   Begin MSComCtl2.DTPicker dtCalculationDate 
      Height          =   255
      Left            =   7680
      TabIndex        =   3
      Top             =   1200
      Visible         =   0   'False
      Width           =   2295
      _ExtentX        =   4048
      _ExtentY        =   450
      _Version        =   393216
      Format          =   20578305
      CurrentDate     =   38517
   End
   Begin VB.Timer tmrRealTime 
      Enabled         =   0   'False
      Interval        =   10
      Left            =   8640
      Top             =   0
   End
   Begin VB.Timer tmrShow 
      Enabled         =   0   'False
      Interval        =   10
      Left            =   8160
      Top             =   0
   End
   Begin VSFlex7Ctl.VSFlexGrid fgUnd 
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
   Begin VSFlex7Ctl.VSFlexGrid fgDiv 
      Height          =   495
      Left            =   0
      TabIndex        =   1
      Top             =   600
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
   Begin VSFlex7Ctl.VSFlexGrid fgVol 
      Height          =   495
      Left            =   0
      TabIndex        =   2
      Top             =   1080
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
   Begin VB.Image imgInSpreadBadPrice 
      Height          =   240
      Left            =   8520
      Picture         =   "ctlQuotesViewSingle.ctx":0000
      Top             =   960
      Width           =   240
   End
   Begin VB.Image Image1 
      Height          =   375
      Left            =   0
      Top             =   0
      Width           =   255
   End
   Begin VB.Image imgInSpread 
      Height          =   240
      Left            =   8040
      Picture         =   "ctlQuotesViewSingle.ctx":058A
      Top             =   960
      Width           =   240
   End
   Begin VB.Image imgBadPrice 
      Height          =   240
      Left            =   7680
      Picture         =   "ctlQuotesViewSingle.ctx":0B14
      Top             =   960
      Width           =   75
   End
   Begin VB.Menu mnuCtx 
      Caption         =   "<Context>"
      Begin VB.Menu mnuCtxTradeNew 
         Caption         =   "New Trade..."
      End
      Begin VB.Menu mnuCtxSeparator1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxPositionTransfer 
         Caption         =   "Position Transfer..."
      End
      Begin VB.Menu mnuCtxSeparator2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxOtcOptionCalc 
         Caption         =   "OTC Option Calc..."
         Shortcut        =   ^{F12}
      End
      Begin VB.Menu mnuCtxSeparator99 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuCtxOrderNewStock 
         Caption         =   "New Stock Order..."
      End
      Begin VB.Menu mnuCtxOrderNewOption 
         Caption         =   "New Option Order..."
      End
      Begin VB.Menu mnuCtxSeparator3 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuCtxTntCardNew 
         Caption         =   "New Trade Message..."
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuCtxSeparator4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxTradeExercise 
         Caption         =   "Exercise Trades..."
      End
      Begin VB.Menu mnuCtxTradeExpiry 
         Caption         =   "Expiry Trades..."
      End
      Begin VB.Menu mnuCtxSeparator5 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxVolaFlat 
         Caption         =   "Flat Vola"
         Begin VB.Menu mnuCtxVolaFlatCur 
            Caption         =   "This Expiry"
         End
         Begin VB.Menu mnuCtxVolaFlatAll 
            Caption         =   "All Expiries"
         End
         Begin VB.Menu mnuCtxVolaFlatAllByCur 
            Caption         =   "All Expiries By This"
         End
      End
      Begin VB.Menu mnuCtxVolaFitToImp 
         Caption         =   "Fit Vola To Implied"
         Begin VB.Menu mnuCtxVolaFitToImpCur 
            Caption         =   "This Expiry"
         End
         Begin VB.Menu mnuCtxVolaFitToImpAll 
            Caption         =   "All Expiries"
         End
      End
      Begin VB.Menu mnuCtxSeparator61 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxCustomDividend 
         Caption         =   "Custom Dividends"
      End
      Begin VB.Menu mnuCtxSeparator6 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxViewSpread 
         Caption         =   "View Spread"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuCtxAddToSpread 
         Caption         =   "Add/Remove Item to Spread"
      End
      Begin VB.Menu mnuCtxClearSpread 
         Caption         =   "Clear Spread"
      End
      Begin VB.Menu mnuCtxSeparator69 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxDefOptSort 
         Caption         =   "Default Options Sorting"
         Shortcut        =   ^D
      End
      Begin VB.Menu mnuCtxSeparator7 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxRealTime 
         Caption         =   "Real Time Mode"
         Shortcut        =   {F9}
      End
      Begin VB.Menu mnuCtxRefresh 
         Caption         =   "Refresh"
         Shortcut        =   {F5}
      End
      Begin VB.Menu mnuCtxRefreshPrices 
         Caption         =   "Refresh Prices "
         Shortcut        =   +{F5}
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
      Begin VB.Menu mnuCtxSeparator8 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxHideCol 
         Caption         =   "Hide Column"
      End
      Begin VB.Menu mnuCtxAutosizeCol 
         Caption         =   "Autosize Column"
      End
      Begin VB.Menu mnuCtxAutosizeGrid 
         Caption         =   "Autosize Grid"
      End
      Begin VB.Menu mnuCtxSeparator9 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxGridLayout 
         Caption         =   "Grid Layout..."
      End
      Begin VB.Menu mnuCtxAddToMarketDepthView 
         Caption         =   "Add to Market Depth View"
         Shortcut        =   ^Z
      End
      Begin VB.Menu mnuCtxShowMarketDepthView 
         Caption         =   "Show Market Depth View"
         Shortcut        =   ^X
      End
      Begin VB.Menu mnuCtxSeparator10 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCtxUseManualPrice 
         Caption         =   "Use Manual Price"
      End
   End
End
Attribute VB_Name = "ctlQuotesViewSingle"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Event OnSetCaption()
Public Event OnStateChange()
Public Event OnExpiriesChange(ByVal bStateOnly As Boolean)
Public Event OnOptExchangesChange(ByVal bStateOnly As Boolean)
Public Event OnUndExchangesChange(ByVal bStateOnly As Boolean)
Public Event OnOptRootsChange(ByVal bStateOnly As Boolean)
Public Event OnFutChange(ByVal bStateOnly As Boolean)
Public Event OnActiveFutChange(ByVal aUndID As Long, ByVal iActiveFutID As Long)
Public Event OnFutParamsChange(ByVal aUndID As Long, ByVal iFutID As Long, ByVal dRatio As Double, ByVal dBasis As Double)
Public Event OnStrikesChange()
Public Event OnScreenRefresh()
Public Event OnScreenClose()
Public Event OnScreenRefreshAndShow()

Private WithEvents geFut As clsGridEx
Attribute geFut.VB_VarHelpID = -1
Private WithEvents geOpt As clsGridEx
Attribute geOpt.VB_VarHelpID = -1
Private WithEvents QV As EtsMmQuotesLib.EtsMmQuotesView
Attribute QV.VB_VarHelpID = -1

Private m_nNewGrpID&
Private m_bForseRecalc As Boolean
Private WithEvents PriceProvider As PRICEPROVIDERSLib.BatchPriceInfo
Attribute PriceProvider.VB_VarHelpID = -1
Private m_GroupPriceProvider As PRICEPROVIDERSLib.IGroupPriceWithNotify
Private m_BatchPriceProvider As PRICEPROVIDERSLib.IBatchPriceProvider
Private WithEvents VolaSource As VolatilitySourcesLib.VolatilitySource
Attribute VolaSource.VB_VarHelpID = -1
Private WithEvents TradeChannel As clsTradeChannel
Attribute TradeChannel.VB_VarHelpID = -1

Private WithEvents frmLayout As frmGridLayout
Attribute frmLayout.VB_VarHelpID = -1
Private frmSpread As frmSpreadCalculator
Private WithEvents m_aSpreadData As MmQvSpreadColl
Attribute m_aSpreadData.VB_VarHelpID = -1

Public pbProgress As MSComctlLib.ProgressBar
Public lblProcess As VB.Label
Public lblStatus As VB.Label

Public WithEvents imgStop As VB.Image
Attribute imgStop.VB_VarHelpID = -1
Public imgStopDis As VB.Image

Public MarketDepthVisible As Boolean
Public MarketDepthOptColl As EtsMmQuotesLib.MmQvOptColl

Private m_sUndComboList As String

Private m_gdUnd As New clsGridDef
Private m_gdDiv As New clsGridDef
Private m_gdVol As New clsGridDef
Private m_gdFut As New clsGridDef
Private m_gdOpt As New clsGridDef

Private m_bShutDown As Boolean
Private m_nUndMainRow As Long

Private m_bInProc As Boolean
Private m_bInRealTimeCalc As Boolean
Private m_bLastQuoteReqNow As Boolean
Private m_bSubscribingNow As Boolean
Private m_bDataLoad As Boolean
Private m_bFireEvent As Boolean
Private m_bInitializing As Boolean

Private m_nQuoteReqDone As Long
Private m_nQuoteGroupReqCount As Long
Private m_nQuoteGroupReqDone As Long
Private m_DecExpectations As Long
Private m_nVisibleRequestDone As Long
Private m_nFinSubStep As Long

Private m_nLastRecalcCycle As Long
Private m_nLastOutCycle As Long
Private m_nLastDataSize As Long

Private m_bVolaChangedNow As Boolean
Private m_bVolaChangedExt As Boolean
Public ProcessRealTime As Boolean

Private m_nCurrentExpiryIdx As Long
Private m_nCurrentOptExchIdx As Long
Private m_nCurrentOptRootIdx As Long
Private m_nCurrentFutIdx As Long

Public m_frmOwner As Form

Private m_sCurrentOriginalText As String
Private m_bKeyDown(GT_QUOTES_UNDERLYING To GT_QUOTES_OPTIONS) As Boolean

Private m_enMenuGrid As GridTypeEnum
Private m_nMenuGridCol As Long
Private m_nMenuGridRow As Long
Private m_nMenuGridCols As Long
Private m_nMenuGridRows As Long

Private m_bGroupRequestSupported As Boolean
Private m_bGroupRequest As Boolean
Private m_bUndListReloadNow As Boolean

Private WithEvents aParams As clsParams
Attribute aParams.VB_VarHelpID = -1

Private m_nOperation As Long

Private m_Aux As New clsAuxQuotesView
Private m_AuxOut As New clsAuxQuotesViewOut

Private m_bCalculationDateChanged As Boolean
Private m_bDateChanged As Boolean
Private m_frmCustDivs As frmCustomDivs
Private m_bInRefreshMode As Boolean
Private m_bFiersTealtimeCalculation As Boolean



Private m_bIsDblClick As Boolean
Private Function SavePriceClose(ByVal ContractType As Long, ByVal ContractID As Long, ByVal ClosePrice As Double) As Boolean
    On Error GoTo EH
    
    SavePriceClose = False
    
    gDBW.usp_ContractPrice_Save _
        Null, _
        ContractID, _
        Null, _
        Null, _
        Null, _
        Null, _
        Null, _
        Null, _
        ClosePrice, _
        Null, _
        Null, _
        Null, _
        Null, _
        Null, _
        ContractType, _
        Null, _
        Null
        
        SavePriceClose = True
        
        Exit Function
EH:
    gCmn.ErrorHandler "Error save close prices for '" & CStr(ContractID) & "': "
End Function
Private Sub InitView()
    On Error GoTo EH
    
    Set QV = Nothing
    Set m_Aux.QV = Nothing
    Set m_Aux.Grp = Nothing
    Set m_Aux.QuoteReqsAll = Nothing
    
    Set m_Aux.QV = New EtsMmQuotesLib.EtsMmQuotesView
    Set QV = m_Aux.QV
    Set QV.BatchPriceProvider = PriceProvider
    Set m_Aux.Grp = m_Aux.QV.Grp
    Set m_Aux.QuoteReqsAll = m_Aux.QV.QuoteReqsAll
    
    QV.ProcessorsLoad = g_Params.ProcessorsLoad
   

Exit Sub
EH:
    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to init quotes view."

End Sub
Private Function GetQuotationNameByID(ByVal ID As Long) As String
    Dim Name As String
    Select Case ID
        Case 0
            Name = "None"
        Case 1
            Name = "Nominal"
        Case 2
            Name = "Bags"
        Case 3
            Name = "Bushels"
        Case 4
            Name = "Barrels"
        Case 5
            Name = "Gallons"
        Case 6
            Name = "Crams"
        Case 7
            Name = "Kilos"
        Case 8
            Name = "ShortTones"
        Case 9
            Name = "LongTones"
        Case 10
            Name = "MetricTones"
        Case 11
            Name = "Ounces"
        Case 12
            Name = "Pounds"
        Case 13
            Name = "SquareFeet"
        Case 14
            Name = "FineTroyOunces"
        Case 15
            Name = "Troy Ounces"
        Case 16
            Name = "BoardFeet"
        Case 17
            Name = "Coins"
        Case 18
            Name = "Bales"
        Case 19
            Name = "BoxCases"
        Case 20
            Name = "BottleFlaskes"
        Case 21
            Name = "Percent"
        Case 22
            Name = "NonFatDryMilk"
        Case 23
            Name = "BtuMillions"
        Case 24
            Name = "MegaWattHours"
        Case 25
            Name = "HundredWeight"
        Case 26
            Name = "HundredWeight112LBS"
        Case 27
            Name = "Ones"
        Case 28
            Name = "Tens"
        Case 29
            Name = "Dozens"
        Case 30
            Name = "Hundreds"
        Case 31
            Name = "Thousands"
        Case 32
            Name = "Millions"
        Case 33
            Name = "Pieces"
        Case 34
            Name = "TenPieces"
        Case 35
            Name = "HundredPieces"
        Case 36
            Name = "ThousandPieces"
        Case 37
            Name = "TenThousandPieces"
        Case 38
            Name = "Indices"
        Case 39
            Name = "FuturesContracts"
        Case 40
            Name = "Currency"
        Case 41
            Name = "Shares"
    End Select
    GetQuotationNameByID = Name
End Function
Public Function Init() As Boolean
    On Error GoTo EH
    
    m_bShutDown = False
    m_bVolaChangedNow = False
    m_bVolaChangedExt = False
    m_Aux.TradesFilter = 0&
    m_bInRefreshMode = False
    m_bFiersTealtimeCalculation = False
    m_bIsDblClick = False
    m_bForseRecalc = False
    
    MarketDepthVisible = False
    Set MarketDepthOptColl = New EtsMmQuotesLib.MmQvOptColl
    


    m_bCalculationDateChanged = False
    m_bDateChanged = False

    m_DecExpectations = 0
    dtCalculationDate.Value = Date
    mnuCtxTradeNew.Caption = "New Trade..." & vbTab & "Ins"
    mnuCtxAutosizeCol.Caption = "Autosize Column" & vbTab & "Ctrl+A"
    mnuCtxAutosizeGrid.Caption = "Autosize Grid" & vbTab & "Ctrl+G"
    mnuCtxVolaFlatCur.Caption = "This Expiry by ATM" & vbTab & "Ctrl+F"
    mnuCtxVolaFlatAll.Caption = "All Expiries by Their ATM" & vbTab & "Ctrl+Shift+F"
    mnuCtxVolaFlatAllByCur.Caption = "All Expiries by This ATM" & vbTab & "Ctrl+Alt+F"
    mnuCtxVolaFitToImpCur.Caption = "This Expiry" & vbTab & "Ctrl+Shift+I"
    mnuCtxVolaFitToImpAll.Caption = "All Expiries" & vbTab & "Ctrl+Alt+I"
    mnuCtxOrderNewStock.Caption = "New Stock Order..." & vbTab & "Alt+Ins"
    mnuCtxOrderNewOption.Caption = "New Option Order..." & vbTab & "Ctrl+Alt+Ins"
    mnuCtxTntCardNew.Caption = "New Trade Message..." & vbTab & "Shift+Alt+Ins"
    
    Set VolaSource = g_VolaSource
    InitColumns
    
    
    Set m_Aux.gdUnd = m_gdUnd
    Set m_Aux.gdDiv = m_gdDiv
    Set m_Aux.gdVol = m_gdVol
    Set m_Aux.gdFut = m_gdFut
    Set m_Aux.gdOpt = m_gdOpt
    Set m_Aux.fgUnd = fgUnd
    Set m_Aux.fgDiv = fgDiv
    Set m_Aux.fgVol = fgVol
    Set m_Aux.fgFut = fgFut
    Set m_Aux.fgOpt = fgOpt
    m_Aux.RealTime = False
    m_Aux.RealTimeConnected = False
    
    m_AuxOut.Init m_Aux
    Set m_AuxOut.gdUnd = m_gdUnd
    Set m_AuxOut.gdDiv = m_gdDiv
    Set m_AuxOut.gdVol = m_gdVol
    Set m_AuxOut.gdFut = m_gdFut
    Set m_AuxOut.gdOpt = m_gdOpt
    Set m_AuxOut.fgUnd = fgUnd
    Set m_AuxOut.fgDiv = fgDiv
    Set m_AuxOut.fgVol = fgVol
    Set m_AuxOut.fgFut = fgFut
    Set m_AuxOut.fgOpt = fgOpt
    Set m_AuxOut.imgBadPrice = imgBadPrice
    Set m_AuxOut.imgInSpread = imgInSpread
    Set m_AuxOut.imgInSpreadBadPrice = imgInSpreadBadPrice
    
    m_bKeyDown(GT_QUOTES_UNDERLYING) = False
    m_bKeyDown(GT_QUOTES_DIVIDENDS) = False
    m_bKeyDown(GT_QUOTES_VOLA) = False
    m_bKeyDown(GT_QUOTES_FUTURES) = False
    m_bKeyDown(GT_QUOTES_OPTIONS) = False
    
    m_Aux.GridLock(GT_QUOTES_UNDERLYING).Init fgUnd
    m_Aux.GridLock(GT_QUOTES_DIVIDENDS).Init fgDiv
    m_Aux.GridLock(GT_QUOTES_VOLA).Init fgVol
    m_Aux.GridLock(GT_QUOTES_FUTURES).Init fgFut
    m_Aux.GridLock(GT_QUOTES_OPTIONS).Init fgOpt
    
    m_Aux.SortColKey = -2
    m_Aux.SortColOrder = flexSortGenericAscending
    m_Aux.InitGrids
    
    Set geFut = New clsGridEx
    geFut.Init fgFut
    Set m_Aux.geFut = geFut
    
    Set geOpt = New clsGridEx
    geOpt.Init fgOpt
    Set m_Aux.geOpt = geOpt
    
    ResetMenuData
    
    m_bInitializing = False
    m_bLastQuoteReqNow = False
    m_bSubscribingNow = False
    m_Aux.UseCustRates = False
    m_Aux.IsAmerican = -1
    m_bFireEvent = False
    
    m_Aux.CalcModelVisible = True
    'm_Aux.ExpCalendarVisible = True
    m_Aux.DividendsVisible = True
    m_Aux.VolaVisible = True
    m_Aux.RatesVisible = True
    m_Aux.FuturesVisible = True
    m_Aux.IndexOptionsComboVisible = False
        
    Dim aPT As PRICEPROVIDERSLib.IProvider
    Set PriceProvider = New PRICEPROVIDERSLib.BatchPriceInfo
    
    Set aPT = PriceProvider
    aPT.Type = g_Params.PriceProviderType
    Set aPT = Nothing
    
    PriceProvider.Connect

    m_bGroupRequestSupported = g_Params.PriceProviderIsGroupRequestSupported
    If m_bGroupRequestSupported Then
        Set m_GroupPriceProvider = PriceProvider
        If m_GroupPriceProvider Is Nothing Then m_bGroupRequestSupported = False
    Else
        Set m_GroupPriceProvider = Nothing
    End If
    
    Set m_BatchPriceProvider = PriceProvider
    If m_BatchPriceProvider Is Nothing Then LogEvent EVENT_ERROR, "Selected price provider is not compatible with Risk view."

    
    InitView
    
    Set TradeChannel = g_TradeChannel
    Set m_aSpreadData = m_Aux.Grp.Spread
    
    ClearViewAndData
    InitUndList
    
    fgUnd.Col = 1
    fgUnd.Row = 1
    Init = True
    UpdateTotals
    AdjustState
    Set frmLayout = New frmGridLayout
    Set frmSpread = New frmSpreadCalculator
    Set aParams = g_Params
    
    Set m_frmCustDivs = New frmCustomDivs
    m_frmCustDivs.InitRs
    
    Exit Function
EH:
    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to init quotes view."
End Function

Public Sub ShowData(Optional ByVal nType As Long = TYPE_UNDERLYING, Optional ByVal nValue As Long = 0)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If nType <> TYPE_UNDERLYING Or nValue = 0 Then Exit Sub
    Dim aContract As EtsGeneralLib.EtsContractAtom
    
    m_nNewGrpID = 0
    Set aContract = g_ContractAll(nValue)
    If Not aContract Is Nothing Then
        m_nNewGrpID = aContract.ID
        Set aContract = Nothing
    
        QV.VisibleUndExch.Clear
        If Not g_Params.QuoteUndExchAll Then
            QV.VisibleUndExch.Add(Trim$(Str$(g_Params.QuoteDefUndExchID))).ID = g_Params.QuoteDefUndExchID
        End If
        
        QV.VisibleOptExch.Clear
        If Not g_Params.QuoteOptExchAll Then
            QV.VisibleOptExch.Add(Trim$(Str$(g_Params.QuoteDefOptExchID))).ID = g_Params.QuoteDefOptExchID
        End If
    End If
    
    If m_nNewGrpID <> 0 And Not m_bShutDown Then
        m_bInRefreshMode = False
        tmrShow.Enabled = True
    End If
End Sub



Private Sub InitUndList()
    On Error Resume Next
    Dim sValue$, nValue&, nCol&
    Dim aContract As EtsGeneralLib.EtsContractAtom
    
    With fgUnd
        nCol = .ColIndex(QUC_SYMBOL)
        If nCol > 0 And nCol < .Cols Then
            m_Aux.GridLock(GT_QUOTES_UNDERLYING).LockRedraw
            
            sValue = "0"
            nValue = 0
            m_sUndComboList = g_Params.UnderlyingWithFuturesComboListAll
            
            If Len(m_sUndComboList) > 0 Then
                m_sUndComboList = "|" & m_sUndComboList
            Else
                m_sUndComboList = "#0;<None>"
            End If
            
            Set aContract = g_ContractAll(m_Aux.Grp.ID)
            If Not aContract Is Nothing Then
                nValue = aContract.ID
                sValue = aContract.Symbol 'Trim$(Str$(aUnd.ID))
                Set aContract = Nothing
            End If
        
            If nValue <> 0 Then .TextMatrix(m_nUndMainRow, nCol) = sValue
            
            m_Aux.GridLock(GT_QUOTES_UNDERLYING).UnlockRedraw
        End If
    End With
End Sub

Public Sub ModelUpdate()
    On Error Resume Next
    m_AuxOut.ModelUpdate
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
Ex:
    Set aExch = Nothing
    Exit Function
EH:
    Set AddExch = Nothing
    gCmn.ErrorHandler "Fail to add exchange."
    GoTo Ex
End Function

Private Function InitGroupExchanges() As Boolean
    On Error GoTo EH
    Dim rsExch As ADODB.Recordset, aExch As EtsGeneralLib.ExchAtom, nID&
    
    InitGroupExchanges = False
    If m_Aux.Grp.ID = 0 Then Exit Function
    
    Dim aUndExchAtom As ExchAtom
    Dim aOptExchAtom As ExchAtom
    Dim lPrimaryExchangeID As Long
    
    
    Set aUndExchAtom = AddExch(m_Aux.Grp.UndExchAll, 0, "", "<NBBO>")
    Set aOptExchAtom = AddExch(m_Aux.Grp.OptExchAll, 0, "", "<NBBO>")
         
    m_Aux.Grp.Und.UndExch.Add aUndExchAtom.ID, aUndExchAtom.Code, aUndExchAtom
    m_Aux.Grp.Und.OptExch.Add aOptExchAtom.ID, aOptExchAtom.Code, aOptExchAtom
        
    Select Case m_Aux.Grp.ContractType
        Case enCtIndex, enCtStock
            Set rsExch = gDBW.usp_MmUnderlyingExchanges_Get(m_Aux.Grp.ID)
        
            Do While Not rsExch.EOF
                nID = ReadLng(rsExch!iExchangeId)
                Set aExch = g_Exch(nID)
                If Not aExch Is Nothing Then
        
                    If ReadByte(rsExch!tiIsUnderlying) <> 0 Then
                        If m_Aux.Grp.UndExchAll(nID) Is Nothing Then
                          Set aUndExchAtom = AddExch(m_Aux.Grp.UndExchAll, nID, aExch.Code, aExch.Name)
                          m_Aux.Grp.Und.UndExch.Add aUndExchAtom.ID, aUndExchAtom.Code, aUndExchAtom
                        End If
'                        If m_Aux.Grp.Und.UndExch(nID) Is Nothing Then AddExch m_Aux.Grp.Und.UndExch, nID, aExch.Code, aExch.Name
                    End If
        
                    If ReadByte(rsExch!tiIsOption) <> 0 Then
                        If m_Aux.Grp.OptExchAll(nID) Is Nothing Then
                          Set aOptExchAtom = AddExch(m_Aux.Grp.OptExchAll, nID, aExch.Code, aExch.Name)
                          m_Aux.Grp.Und.OptExch.Add aOptExchAtom.ID, aOptExchAtom.Code, aOptExchAtom
                        End If
'                        If m_Aux.Grp.Und.OptExch(nID) Is Nothing Then AddExch m_Aux.Grp.Und.OptExch, nID, aExch.Code, aExch.Name
                    End If
        
                    Set aExch = Nothing
                End If
                
                DoEvents
                If Not m_bDataLoad Then GoTo Ex
                rsExch.MoveNext
            Loop
            
            lPrimaryExchangeID = m_Aux.Grp.Und.PrimaryExchangeID
            Set aExch = g_Exch(lPrimaryExchangeID)
            
            If (Not aExch Is Nothing) Then
                If (m_Aux.Grp.UndExchAll(lPrimaryExchangeID) Is Nothing) Then
                    Set aUndExchAtom = AddExch(m_Aux.Grp.UndExchAll, lPrimaryExchangeID, aExch.Code, aExch.Name)
                    m_Aux.Grp.Und.UndExch.Add aUndExchAtom.ID, aUndExchAtom.Code, aUndExchAtom
                End If
            End If
            
        Case enCtFutUnd
'            Set rsExch = gDBW.usp_MmFutureExchanges_Get(m_Aux.Grp.ID)
'            AddExch m_Aux.Grp.Fut.FutExch, 0, "", "<Primary>"
'            AddExch m_Aux.Grp.Fut.OptExch, 0, "", "<Primary>"
'
'            Do While Not rsExch.EOF
'                nID = ReadLng(rsExch!iExchangeID)
'                Set aExch = g_Exch(nID)
'                If Not aExch Is Nothing Then
'
'                    If ReadByte(rsExch!tiIsUnderlying) <> 0 Then
'                        If m_Aux.Grp.UndExchAll(nID) Is Nothing Then AddExch m_Aux.Grp.UndExchAll, nID, aExch.Code, aExch.Name
'                        If m_Aux.Grp.Fut.FutExch(nID) Is Nothing Then AddExch m_Aux.Grp.Fut.FutExch, nID, aExch.Code, aExch.Name
'                    End If
'
'                    If ReadByte(rsExch!tiIsOption) <> 0 Then
'                        If m_Aux.Grp.OptExchAll(nID) Is Nothing Then AddExch m_Aux.Grp.OptExchAll, nID, aExch.Code, aExch.Name
'                        If m_Aux.Grp.Fut.OptExch(nID) Is Nothing Then AddExch m_Aux.Grp.Fut.OptExch, nID, aExch.Code, aExch.Name
'                    End If
'
'                    Set aExch = Nothing
'                End If
'
'                DoEvents
'                If Not m_bDataLoad Then GoTo EX
'                rsExch.MoveNext
'            Loop
            
        Case enCtFuture
'            Set rsExch = gDBW.usp_MmFutureExchanges_Get(m_Aux.Grp.ID)
'            AddExch m_Aux.Grp.Fut.FutExch, 0, "", "<Primary>"
'            AddExch m_Aux.Grp.Fut.OptExch, 0, "", "<Primary>"
'
'            'If m_Aux.Grp.UndExchAll(35) Is Nothing Then AddExch m_Aux.Grp.UndExchAll, 35, "G", "Globex"
'            'If m_Aux.Grp.Fut.FutExch(35) Is Nothing Then AddExch m_Aux.Grp.Fut.FutExch, 35, "G", "Globex"
'
'            Do While Not rsExch.EOF
'                nID = ReadLng(rsExch!iExchangeID)
'                Set aExch = g_Exch(nID)
'                If Not aExch Is Nothing Then
'
'                    If ReadByte(rsExch!tiIsUnderlying) <> 0 Then
'                        If m_Aux.Grp.UndExchAll(nID) Is Nothing Then AddExch m_Aux.Grp.UndExchAll, nID, aExch.Code, aExch.Name
'                        If m_Aux.Grp.Fut.FutExch(nID) Is Nothing Then AddExch m_Aux.Grp.Fut.FutExch, nID, aExch.Code, aExch.Name
'                    End If
'
'                    If ReadByte(rsExch!tiIsOption) <> 0 Then
'                        If m_Aux.Grp.OptExchAll(nID) Is Nothing Then AddExch m_Aux.Grp.OptExchAll, nID, aExch.Code, aExch.Name
'                        If m_Aux.Grp.Fut.OptExch(nID) Is Nothing Then AddExch m_Aux.Grp.Fut.OptExch, nID, aExch.Code, aExch.Name
'                    End If
'
'                    Set aExch = Nothing
'                End If
'
'                DoEvents
'                If Not m_bDataLoad Then GoTo EX
'                rsExch.MoveNext
'            Loop
            
        Case Else
            GoTo Ex
    End Select
    
    InitGroupExchanges = True
Ex:
    Set rsExch = Nothing
    Set aExch = Nothing
    Exit Function
EH:
    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to load underlying."
    GoTo Ex
End Function

Private Sub InitUnderlying(ByRef aContract As EtsGeneralLib.EtsContractAtom)
    On Error Resume Next
    Dim aIdx As EtsGeneralLib.IndexAtom, sKey$
    Dim nID As Long
    
    If m_Aux.Grp.ID = 0 Then Exit Sub
    
    nID = aContract.Und.ID
    m_Aux.Grp.Und.ID = aContract.Und.ID
    m_Aux.Grp.Und.Symbol = aContract.Und.Symbol
    m_Aux.Grp.Und.SymbolName = aContract.Und.ContractName
    m_Aux.Grp.Und.UndType = aContract.Und.UndType
    m_Aux.Grp.Und.IsTraderContract = aContract.Und.IsTraderContract
    m_Aux.Grp.Und.PrimaryExchangeID = aContract.Und.PrimaryExchangeID
    InitVola m_Aux.Grp.Und
    
    m_Aux.Grp.Und.IsHTB = aContract.Und.IsHTB
    m_Aux.Grp.Und.Skew = aContract.Und.Skew
    m_Aux.Grp.Und.Kurt = aContract.Und.Kurt
    m_Aux.Grp.Und.IsManualVol = aContract.Und.IsManualVol
    
    m_Aux.Grp.Und.IsHead = aContract.Und.IsHead
    m_Aux.Grp.Und.PriceByHead = aContract.Und.PriceByHead
    m_Aux.Grp.Und.Coeff = aContract.Und.Coeff
    
    Set m_Aux.Grp.Und.UndPriceProfile = aContract.Und.UndPriceProfile
    Set m_Aux.Grp.Und.OptPriceProfile = aContract.Und.OptPriceProfile
    
    m_Aux.Grp.Und.UndPosForRates = 0#
    
    If aContract.Und.manualActivePrice <> 0 Then
        m_Aux.Grp.Und.UseManualActivePrice = True
        m_Aux.Grp.Und.ActivePrice = aContract.Und.manualActivePrice
    Else
        m_Aux.Grp.Und.UseManualActivePrice = False
        m_Aux.Grp.Und.ActivePrice = aContract.Und.manualActivePrice
    End If
        
    
    If m_Aux.IsAmerican < 0 Then
        m_Aux.Grp.Und.IsAmerican = aContract.Und.IsAmerican
    Else
        m_Aux.Grp.Und.IsAmerican = (m_Aux.IsAmerican <> 0)
    End If
    
    m_Aux.Grp.UseCustRates = m_Aux.UseCustRates
    
    If aContract.Und.UndType = enCtStock Then
        Set m_Aux.Grp.Und.Dividend = aContract.Und.Dividend
        
        If m_Aux.Grp.Und.Dividend.DivDate = 0 Then m_Aux.Grp.Und.Dividend.DivDate = Date
        If m_Aux.Grp.Und.Dividend.DivDateCust = 0 Then m_Aux.Grp.Und.Dividend.DivDateCust = Date
        
        If m_Aux.Grp.Und.Dividend.DivType = enDivCustomStream Then
            LoadCustomDivs
        End If
        
    Else
        m_Aux.Grp.Und.Yield = aContract.Und.Yield
        
        Set m_Aux.Grp.Und.Dividend = Nothing
        Set m_Aux.Grp.Und.Dividend = aContract.Und.Dividend
        
        Set m_Aux.Grp.Und.BasketIndex = Nothing
        Set aIdx = g_Index(nID)
        If Not aIdx Is Nothing Then
            If aIdx.IsBasket Then
                Set m_Aux.Grp.Und.BasketIndex = aIdx
            End If
            Set aIdx = Nothing
        End If
        
        Select Case aContract.Und.Dividend.DivType
            Case enDivCustomStream:
                LoadCustomDivs
        End Select

    End If
    
    m_Aux.Grp.Und.Quote.Clear
    m_Aux.Grp.Und.Exp.Clear
    m_Aux.Grp.Und.OptRoot.Clear

    Set aIdx = Nothing
End Sub

Private Sub InitContracts(ByRef aContract As EtsGeneralLib.EtsContractAtom)
    On Error Resume Next
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim sKey$
    
    If m_Aux.Grp.ID = 0 Then Exit Sub
    
    If aContract.ContractType = enCtFuture Or enCtFutUnd Then
        Dim aFutRoot As EtsMmQuotesLib.MmQvFutRootAtom
        If Not aContract.FutRoot Is Nothing Then
            Set aFutRoot = m_Aux.Grp.FutRootColl.Add(aContract.FutRoot.ID)
        
            aFutRoot.ID = aContract.FutRoot.ID
            aFutRoot.Symbol = aContract.FutRoot.Symbol
            aFutRoot.Name = aContract.FutRoot.Name
            aFutRoot.FutLotSize = aContract.FutRoot.FutLotSize
            aFutRoot.OptLotSize = aContract.FutRoot.OptLotSize
            If (aContract.FutRoot.QuotationUnitID) = 40 Then
                aFutRoot.QuotationUnitName = aContract.FutRoot.QuotationUnitName
                aFutRoot.QuotationUnitID = aContract.FutRoot.QuotationUnitID
            Else
                aFutRoot.QuotationUnitName = GetQuotationNameByID(aContract.FutRoot.QuotationUnitID)
                aFutRoot.QuotationUnitID = aContract.FutRoot.QuotationUnitID
            End If
            
        End If
    End If
        
End Sub

Private Sub InitContractsQuotes(ByRef aContract As EtsGeneralLib.EtsContractAtom)
    On Error Resume Next
    Dim sKey$, aExch As EtsGeneralLib.ExchAtom
    Dim aReq As MmQvRequestAtom, aQuote As EtsMmQuotesLib.MmQvQuoteAtom
    
    If m_Aux.Grp.ID = 0 Then Exit Sub
    
    For Each aExch In m_Aux.Grp.Und.UndExch

        Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
        Set aQuote.Exch = aExch
        aQuote.LotSize = aContract.Und.LotSize
        aQuote.PriceClose = aContract.Und.PriceClose

        sKey = m_Aux.Grp.Und.Symbol
        If aExch.ID <> 0 Then
            sKey = sKey & "." & aExch.Code
        End If

        If m_Aux.Grp.IsStockOrIndex Then
            Set aReq = m_Aux.QuoteReqsAll(sKey)
            If aReq Is Nothing Then
                Set aReq = m_Aux.QuoteReqsAll.Add(sKey)
                Set aReq.Exch = aExch
                Set aReq.Und = m_Aux.Grp.Und
            End If
            Set aReq = Nothing
        End If

        m_Aux.Grp.Und.Quote.Add aExch.ID, aExch.Code, aQuote
        Set aQuote = Nothing
    Next
    
    QV.UndQuotesCount = m_Aux.Grp.Und.UndExch.Count

    If aContract.ContractType = enCtFuture Then
'        For Each aExch In m_Aux.Grp.Fut.FutExch
'
'            Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
'            Set aQuote.Exch = aExch
'            aQuote.LotSize = aContract.FutRoot.FutLotSize
'
'            sKey = m_Aux.Grp.Fut.Symbol
'            If aExch.ID <> 0 Then
'                sKey = sKey & "." & aExch.Code
'            End If
'
'            Set aReq = m_Aux.QuoteReqsAll(sKey)
'            If aReq Is Nothing Then
'                Set aReq = m_Aux.QuoteReqsAll.Add(sKey)
'                Set aReq.Exch = aExch
'                Set aReq.Und = m_Aux.Grp.Und
'                Set aReq.Fut = m_Aux.Grp.Fut
'                Set aReq.FutRoot = m_Aux.Grp.FutRoot
'            End If
'            Set aReq = Nothing
'
'            m_Aux.Grp.Fut.Quote.Add aExch.ID, aExch.Code, aQuote
'            Set aQuote = Nothing
'        Next
'
'        QV.FutQuotesCount = m_Aux.Grp.Fut.FutExch.Count
    End If
    
    If aContract.ContractType = enCtFutUnd Then 'fokiny
'        Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
'
'            aQuote.LotSize = aContract.FutRoot.FutLotSize
'
'            Set aReq = m_Aux.QuoteReqsAll(sKey)
'            If aReq Is Nothing Then
'                Set aReq = m_Aux.QuoteReqsAll.Add(sKey)
'                Set aReq.Und = m_Aux.Grp.Und
'                Set aReq.FutRoot = m_Aux.Grp.FutRoot
'            End If
'            Set aReq = Nothing
'
'            m_Aux.Grp.Und.Quote.Add 0, "<Primary>", aQuote
'            Set aQuote = Nothing
    End If
    
End Sub

'Private Function InitUnderlyingOptions(ByRef aContract As EtsGeneralLib.EtsContractAtom) As Boolean
'    On Error GoTo EH
'
'    QV.ConnectionString = g_Params.DbConnection
'    Set QV.EtsMain = g_Main
'
'    QV.Load m_Aux.Grp.ID, enCtStock
'    Dim rsOpt As ADODB.Recordset, aExch As EtsGeneralLib.ExchAtom, rsExch As ADODB.Recordset
'    Dim dtExpiry As Date, dStrike#, dtExpiryMonth As Date, sRoot$, aRoot As EtsMmQuotesLib.MmQvOptRootAtom, aPair As EtsMmQuotesLib.MmQvOptPairAtom
'    Dim aQuote As EtsMmQuotesLib.MmQvQuoteAtom, enOptType As EtsGeneralLib.EtsOptionTypeEnum, sKey$, aEnt As EtsGeneralLib.EtsMmEntityAtom
'    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, aStr As EtsMmQuotesLib.MmQvStrikeAtom, aOpt As EtsMmQuotesLib.MmQvOptAtom
'    Dim nID&, nOptRootID&, aGUnd As EtsGeneralLib.UndAtom, aSyntRootComp As EtsGeneralLib.SynthRootCompAtom
'    Dim aUnd As EtsMmQuotesLib.MmQvUndAtom, aSynthRoot As EtsGeneralLib.SynthRootAtom
'    Dim aStrAll As EtsMmQuotesLib.MmQvStrikeAtom, aReq As MmQvRequestAtom, aExpAll As EtsMmQuotesLib.MmQvExpAtom
'
'    InitUnderlyingOptions = False
'    If m_Aux.Grp.ID = 0 Then Exit Function
'
'    Set rsOpt = gDBW.usp_MmOptionByUnderlying_Get(m_Aux.Grp.ID, Date)
'    If rsOpt.RecordCount > 0 Then pbProgress.Max = rsOpt.RecordCount
'
'    DoEvents
'    If Not m_bDataLoad Then GoTo EX
'
'    Do While Not rsOpt.EOF
'        dtExpiry = ReadDate(rsOpt!dtExpiry)
'        dtExpiryMonth = DateSerial(Year(dtExpiry), Month(dtExpiry), 1)
'
'        Set aExp = m_Aux.Grp.Und.Exp(dtExpiryMonth)
'        If aExp Is Nothing Then
'            Set aExp = m_Aux.Grp.Und.Exp.Add(dtExpiryMonth)
'            aExp.Expiry = dtExpiry
'            aExp.ExpiryMonth = dtExpiryMonth
'            aExp.Visible = True
'
'            Set aEnt = qv.CustRates(CStr(CLng(aExp.ExpiryMonth)))
'            If Not aEnt Is Nothing Then
'                aExp.RateCust = aEnt.Data3
'                Set aEnt = Nothing
'            End If
'        End If
'
'        nOptRootID = ReadLng(rsOpt!iOptionRootID)
'
'        Set aRoot = m_Aux.Grp.Und.OptRoot(nOptRootID)
'        If aRoot Is Nothing Then
'            Set aRoot = New EtsMmQuotesLib.MmQvOptRootAtom
'            aRoot.ID = nOptRootID
'
'            aRoot.Name = ReadStr(rsOpt!vcOptionRootSymbol)
'            aRoot.LotSize = ReadLng(rsOpt!iLotSize)
'            aRoot.IsFit = IIf(ReadLng(rsOpt!tiIsFitEnabled) <> 0, True, False)
'            ' Sharky: unnecessary code. just for ensure not zero lot
'            If aRoot.LotSize <= 0 Then aRoot.LotSize = 100
'
'            If aContract.Und.HaveSyntheticRoots Then
'                Set aSynthRoot = aContract.Und.SyntheticRoots(nOptRootID)
'            End If
'
'            aRoot.Synthetic = Not aSynthRoot Is Nothing
'
'            If aRoot.Synthetic Then
'                Set aRoot.SynthOptRoot = aSynthRoot
'                Dim dDPC As Double
'                dDPC = aRoot.LotSize * aSynthRoot.CashValue
'                If dDPC <> 0# Then _
'                    aRoot.DPC = Trim$(Str$(aRoot.LotSize * aSynthRoot.CashValue)) & " USD"
'
'                If aSynthRoot.CashValue > 0# Then
'                    If m_Aux.Grp.Und.SynthUnd Is Nothing Then Set m_Aux.Grp.Und.SynthUnd = New EtsMmQuotesLib.MmQvUndColl
'
'                    If m_Aux.Grp.Und.SynthUnd(USD_ID) Is Nothing Then
'                        Set aUnd = New EtsMmQuotesLib.MmQvUndAtom
'                        aUnd.ID = USD_ID
'                        aUnd.Symbol = USD_SYMBOL
'                        aUnd.SymbolName = USD_SYMBOL
'                        aUnd.UndType = enCtStock
'
'                        aUnd.OptRoot.Add aRoot.ID, aRoot.Name, aRoot
'
'                        Set aExch = AddExch(aUnd.UndExch, 0, "", "<Primary>")
'
'                        Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
'                        Set aQuote.Exch = aExch
'                        aQuote.LotSize = aRoot.LotSize
'                        aQuote.PriceAsk = 1#
'                        aQuote.PriceBid = 1#
'                        aQuote.PriceLast = 1#
'
'                        aUnd.Quote.Add aExch.ID, aExch.Code, aQuote
'                        Set aQuote = Nothing
'                        Set aExch = Nothing
'
'                        m_Aux.Grp.Und.SynthUnd.Add USD_ID, USD_SYMBOL, aUnd
'                        Set aUnd = Nothing
'                    End If
'                End If
'
'                For Each aSyntRootComp In aSynthRoot.SynthRootComponents
'                    Set aGUnd = g_UnderlyingAll(aSyntRootComp.UndID)
'
'                    If Not aGUnd Is Nothing Then
'                        aRoot.DPC = aRoot.DPC & IIf(Len(aRoot.DPC) > 0, " + ", "") & Trim$(Str$(aRoot.LotSize * aSyntRootComp.Weight)) & " " & aGUnd.Symbol
'
'                        If aSyntRootComp.UndID <> m_Aux.Grp.Und.ID Then
'
'                            If m_Aux.Grp.Und.SynthUnd Is Nothing Then Set m_Aux.Grp.Und.SynthUnd = New EtsMmQuotesLib.MmQvUndColl
'
'                            If m_Aux.Grp.Und.SynthUnd(aSyntRootComp.UndID) Is Nothing Then
'                                Set aUnd = New EtsMmQuotesLib.MmQvUndAtom
'                                aUnd.ID = aSyntRootComp.UndID
'                                aUnd.Symbol = aGUnd.Symbol
'                                aUnd.SymbolName = aGUnd.ContractName
'                                aUnd.UndType = aGUnd.UndType
'
'                                aUnd.OptRoot.Add aRoot.ID, aRoot.Name, aRoot
'
'                                AddExch aUnd.UndExch, 0, "", "<Primary>"
'
'                                Set rsExch = gDBW.usp_MmUnderlyingExchanges_Get(aSyntRootComp.UndID)
'                                Do While Not rsExch.EOF
'                                    nID = ReadLng(rsExch!iExchangeID)
'                                    Set aExch = g_Exch(nID)
'
'                                    If Not aExch Is Nothing Then
'                                        If ReadByte(rsExch!tiIsUnderlying) <> 0 Then
'                                            If m_Aux.Grp.UndExchAll(nID) Is Nothing Then AddExch m_Aux.Grp.UndExchAll, nID, aExch.Code, aExch.Name
'                                            If aUnd.UndExch(nID) Is Nothing Then AddExch aUnd.UndExch, nID, aExch.Code, aExch.Name
'                                        End If
'                                        Set aExch = Nothing
'                                    End If
'
'                                    DoEvents
'                                    If Not m_bDataLoad Then GoTo EX
'                                    rsExch.MoveNext
'                                Loop
'                                Set rsExch = Nothing
'
'                                For Each aExch In aUnd.UndExch
'
'                                    Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
'                                    Set aQuote.Exch = aExch
'                                    aQuote.LotSize = aRoot.LotSize
'
'                                    sKey = aGUnd.Symbol
'                                    If aExch.ID <> 0 Then
'                                        sKey = sKey & "." & aExch.Code
'                                    End If
'
'                                    Set aReq = m_Aux.QuoteReqsAll(sKey)
'                                    If aReq Is Nothing Then
'                                        Set aReq = m_Aux.QuoteReqsAll.Add(sKey)
'                                        Set aReq.Exch = aExch
'                                        Set aReq.Und = aUnd
'                                    End If
'                                    Set aReq = Nothing
'
'                                    aUnd.Quote.Add aExch.ID, aExch.Code, aQuote
'                                    Set aQuote = Nothing
'                                Next
'
'                                QV.UndQuotesCount = QV.UndQuotesCount + aUnd.UndExch.Count
'
'                                m_Aux.Grp.Und.SynthUnd.Add aSyntRootComp.UndID, aGUnd.Symbol, aUnd
'                                Set aUnd = Nothing
'                            End If
'                        End If
'                        Set aGUnd = Nothing
'                    End If
'                Next
'            Else
'                aRoot.DPC = Trim$(Str$(aRoot.LotSize)) + " " + m_Aux.Grp.Und.Symbol
'            End If
'
'            aRoot.Visible = True
'            m_Aux.Grp.Und.OptRoot.Add aRoot.ID, aRoot.Name, aRoot
'        End If
'        Set aSynthRoot = Nothing
'
'        Set aExpAll = m_Aux.Grp.ExpAll(dtExpiryMonth)
'        If aExpAll Is Nothing Then
'            Set aExpAll = m_Aux.Grp.ExpAll.Add(dtExpiryMonth)
'            aExpAll.Expiry = dtExpiry
'            aExpAll.ExpiryMonth = dtExpiryMonth
'            aExpAll.Visible = True
'        End If
'
'        If InStr(aExpAll.RootNames, aRoot.Name) = 0 Then
'            If Len(aExpAll.RootNames) > 0 Then
'                aExpAll.RootNames = aExpAll.RootNames & "," & aRoot.Name
'            Else
'                aExpAll.RootNames = aRoot.Name
'            End If
'        End If
'
'        Set aExpAll = Nothing
'
'        dStrike = Round(ReadDbl(rsOpt!fStrike), STRIKE_DECIMALS_COUNT)
'
'        Set aStr = aExp.Strike(dStrike)
'        If aStr Is Nothing Then
'            Set aStr = aExp.Strike.Add(dStrike)
'            aStr.Strike = dStrike
'            aStr.Visible = True
'        End If
'
'        Set aStrAll = m_Aux.Grp.StrikeAll(dStrike)
'        If aStrAll Is Nothing Then
'            Set aStrAll = m_Aux.Grp.StrikeAll.Add(dStrike)
'            aStrAll.Strike = dStrike
'            aStrAll.Visible = True
'        End If
'        Set aStrAll = Nothing
'
'        Set aPair = aStr.OptPair(aRoot.ID)
'        If aPair Is Nothing Then
'            Set aPair = New EtsMmQuotesLib.MmQvOptPairAtom
'            aPair.RootID = aRoot.ID
'
'            aStr.OptPair.Add aRoot.ID, aRoot.Name, aPair
'        End If
'
'        enOptType = IIf(ReadLng(rsOpt!tiIsCall) <> 0, enOtCall, enOtPut)
'
'        Set aOpt = aPair.Opt(enOptType)
'        If aOpt.ID = 0 Then
'            aOpt.ID = ReadLng(rsOpt!iContractID)
'            aOpt.Symbol = ReadStr(rsOpt!vcSymbol)
'            aOpt.OptType = enOptType
'            aOpt.Expiry = dtExpiry
'            aOpt.Strike = dStrike
'            aOpt.RootID = aPair.RootID
'
'            aOpt.Vola = m_Aux.Grp.Und.VolaSrv.OptionVola(dtExpiry, dStrike)
'
'            If aOpt.Vola < 0 Then
'                aOpt.Vola = BAD_DOUBLE_VALUE
'            End If
'
'            m_Aux.Grp.Und.Opt.Add aOpt.ID, aOpt
'        End If
'
'        For Each aExch In m_Aux.Grp.Und.OptExch
'            Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
'            Set aQuote.Exch = aExch
'            aQuote.LotSize = aRoot.LotSize
'
'            If Int(aOpt.Strike) = aOpt.Strike Then
'                aQuote.Series = UCase$(Format$(aOpt.Expiry, "YYMMM")) & Trim$(Str$(Int(aOpt.Strike)))
'            Else
'                aQuote.Series = UCase$(Format$(aOpt.Expiry, "YYMMM")) & Trim$(Format$(aOpt.Strike, "##,##.#0"))
'            End If
'
'            sKey = aOpt.Symbol
'
'            If aExch.ID = 0 Then
'                Set aOpt.DefQuote = aQuote
'            Else
'                aQuote.Series = aQuote.Series & " " & aExch.Code
'                sKey = sKey & "." & aExch.Code
'            End If
'
'            Set aReq = m_Aux.QuoteReqsAll(sKey)
'            If aReq Is Nothing Then
'                Set aReq = m_Aux.QuoteReqsAll.Add(sKey)
'                Set aReq.Exch = aExch
'                Set aReq.Opt = aOpt
'                Set aReq.Exp = aExp
'            End If
'            Set aReq = Nothing
'
'            aOpt.Quote.Add aExch.ID, aExch.Code, aQuote
'            Set aQuote = Nothing
'        Next
'
'        DoEvents
'        If Not m_bDataLoad Then GoTo EX
'        IncProgress pbProgress
'
'        Set aOpt = Nothing
'        Set aPair = Nothing
'        Set aRoot = Nothing
'        Set aUnd = Nothing
'        Set aSyntRootComp = Nothing
'
'        rsOpt.MoveNext
'    Loop
'
'    QV.OptQuotesCount = m_Aux.Grp.Und.Opt.Count * m_Aux.Grp.Und.OptExch.Count
'
'
'    InitUnderlyingOptions = True
'EX:
'    Set aGUnd = Nothing
'    Set aPair = Nothing
'    Set aRoot = Nothing
'    Set aExp = Nothing
'    Set aQuote = Nothing
'    Set rsOpt = Nothing
'    Set rsExch = Nothing
'    Set aExch = Nothing
'    Set aSynthRoot = Nothing
'    Set aSyntRootComp = Nothing
'    Exit Function
'EH:
'    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to load underlying."
'    GoTo EX
'End Function

'Private Function InitFutures(ByRef aContract As EtsGeneralLib.EtsContractAtom) As Boolean
'
'    On Error GoTo EH
'
'    QV.ConnectionString = g_Params.DbConnection
'    Set QV.EtsMain = g_Main
'
'    QV.Load m_Aux.Grp.ID, enCtFutUnd
'
''
''    Dim rsFut As ADODB.Recordset, aExch As EtsGeneralLib.ExchAtom, nID&
''    Dim rsExch As ADODB.Recordset
''    Dim dtMaturity As Date, dtMaturityMonth As Date
''    Dim aQuote As EtsMmQuotesLib.MmQvQuoteAtom, sKey$
''    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
''    Dim aReq As MmQvRequestAtom
''    Dim nLotSize&, sQuotationUnit$
''
''    InitFutures = False
''    If m_Aux.Grp.ID = 0 Then Exit Function
''
''    m_Aux.Grp.ExpAll.Clear
''    Set rsFut = gDBW.usp_MmFutureByUnderlying_Get(m_Aux.Grp.ID, Date) 'Grp.ID ?
''    If rsFut.RecordCount > 0 Then pbProgress.Max = rsFut.RecordCount
''
''    DoEvents
''    If Not m_bDataLoad Then GoTo EX
''    Dim aFRoot As EtsFutRootAtom
''
''    Do While Not rsFut.EOF
''
''        '------------------------------------------------------------------------------
''        dtMaturity = ReadDate(rsFut!dtMaturity)
''        dtMaturityMonth = DateSerial(Year(dtMaturity), Month(dtMaturity), 1)
''        nLotSize = aContract.Und.FutRoots(ReadLng(rsFut!iFutureRootID)).FutLotSize
''
''        Set aFRoot = aContract.Und.FutRoots(ReadLng(rsFut!iFutureRootID))
''        If (aFRoot.QuotationUnitID) = 40 Then
''            sQuotationUnit = aFRoot.QuotationUnitName
''        Else
''            sQuotationUnit = GetQuotationNameByID(aFRoot.QuotationUnitID)
''        End If
''
''        Set aFut = m_Aux.Grp.Und.Fut(ReadLng(rsFut!iContractID))
''        If aFut Is Nothing Then
''            Set aFut = m_Aux.Grp.Und.Fut.Add(ReadLng(rsFut!iContractID))
''            aFut.ID = ReadLng(rsFut!iContractID)
''            aFut.Symbol = ReadStr(rsFut!vcSymbol)
''            aFut.MaturityDate = dtMaturity
''            aFut.MaturityMonth = dtMaturityMonth
''            aFut.LotSize = nLotSize
''            aFut.QuotationUnit = sQuotationUnit
''            'next two lines - need to move to InitContracts
''            Set aContract.Und.UndPriceProfile = aFRoot.Futures(aFut.ID).UndPriceProfile
''            Set aContract.Und.OptPriceProfile = aFRoot.Futures(aFut.ID).OptPriceProfile
''            Set m_Aux.Grp.Und.UndPriceProfile = aContract.Und.UndPriceProfile
''            Set m_Aux.Grp.Und.OptPriceProfile = aContract.Und.OptPriceProfile
''            Set aFut.UndPriceProfile = aContract.Und.UndPriceProfile
''            Set aFut.OptPriceProfile = aContract.Und.OptPriceProfile
''            aContract.Und.IsAmerican = aFRoot.Futures(aFut.ID).IsAmerican
''            m_Aux.Grp.Und.IsAmerican = aContract.Und.IsAmerican
''            aFut.IsAmerican = aContract.Und.IsAmerican
''            'aFut.UndPriceProfile.AlwaysUseLast = False
''            aFut.FutRootID = ReadLng(rsFut!iFutureRootID)
''
''            If m_Aux.Grp.FutRootColl(aFut.FutRootID) Is Nothing Then
''                Dim aFutRoot As EtsMmQuotesLib.MmQvFutRootAtom
''                Set aFutRoot = m_Aux.Grp.FutRootColl.Add(aFut.FutRootID)
''
''                aFutRoot.ID = aFRoot.ID
''                aFutRoot.Symbol = aFRoot.Symbol
''                aFutRoot.Name = aFRoot.Name
''                aFutRoot.MatCalendarID = aFRoot.MatCalendarID
''                aFutRoot.FutLotSize = aFRoot.FutLotSize
''                aFutRoot.OptLotSize = aFRoot.OptLotSize
''
''                If (aFRoot.QuotationUnitID) = 40 Then
''                    aFutRoot.QuotationUnitName = aFRoot.QuotationUnitName
''                    aFutRoot.QuotationUnitID = aFRoot.QuotationUnitID
''                Else
''                    aFutRoot.QuotationUnitName = GetQuotationNameByID(aFRoot.QuotationUnitID)
''                    aFutRoot.QuotationUnitID = aFRoot.QuotationUnitID
''                End If
''
''            End If
''        End If
''
''        '-------------------------------------------------------------------------------
''            Set rsExch = gDBW.usp_MmFutureExchanges_Get(aFut.ID)
''            AddExch aFut.FutExch, 0, "", "<Primary>"
''            AddExch aFut.OptExch, 0, "", "<Primary>"
''
''            Do While Not rsExch.EOF
''                nID = ReadLng(rsExch!iExchangeID)
''                Set aExch = g_Exch(nID)
''                If Not aExch Is Nothing Then
''
''                    If ReadByte(rsExch!tiIsUnderlying) <> 0 Then
''                        If m_Aux.Grp.UndExchAll(nID) Is Nothing Then AddExch m_Aux.Grp.UndExchAll, nID, aExch.Code, aExch.Name
''                        If aFut.FutExch(nID) Is Nothing Then AddExch aFut.FutExch, nID, aExch.Code, aExch.Name
''                    End If
''
''                    If ReadByte(rsExch!tiIsOption) <> 0 Then
''                        If m_Aux.Grp.OptExchAll(nID) Is Nothing Then AddExch m_Aux.Grp.OptExchAll, nID, aExch.Code, aExch.Name
''                        If aFut.OptExch(nID) Is Nothing Then AddExch aFut.OptExch, nID, aExch.Code, aExch.Name
''                    End If
''
''                    Set aExch = Nothing
''                End If
''
''                rsExch.MoveNext
''            Loop
''        '------------------------------------------------------------------------------
''            Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
''            'Set aQuote.Exch = aExch
''            'aQuote.LotSize = m_Aux.Grp.FutRoot.OptLotSize * m_Aux.Grp.FutRoot.FutLotSize
''
''            aQuote.Series = UCase$(Format$(dtMaturity, "MMM YY"))
''            sKey = aFut.Symbol
''
''            aQuote.Series = aQuote.Series '& " " & aExch.Code
''            sKey = sKey '& "." & aExch.Code
''
''            Set aReq = m_Aux.QuoteReqsAll(sKey)
''            If aReq Is Nothing Then
''                Set aReq = m_Aux.QuoteReqsAll.Add(sKey)
''                Set aReq.Exch = aFut.FutExch(0)
''                Set aReq.Fut = aFut
''                'Set aReq.FutRoot = m_Aux.Grp.FutRoot
''            End If
''            Set aReq = Nothing
''
''            aFut.Quote.Add 0, "<Primary>", aQuote
''            Set aQuote = Nothing
''
''        InitFuturesOptions aContract, aFut, ReadLng(rsFut!iContractID)
''
''        DoEvents
''        If Not m_bDataLoad Then GoTo EX
''
''        IncProgress pbProgress
''        Set aFut = Nothing
''        rsFut.MoveNext
''    Loop
''
'    InitFutures = True
'EX:
''    Set aFut = Nothing
''    Set rsFut = Nothing
''    Set rsExch = Nothing
''    Set aQuote = Nothing
''    Set aExch = Nothing
'    Exit Function
'EH:
'    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to load futures."
'    GoTo EX
'End Function

'Private Function InitFuturesOptions(ByRef aContract As EtsGeneralLib.EtsContractAtom, aFut As EtsMmQuotesLib.MmQvFutAtom, iFutureID As Long) As Boolean
'    On Error GoTo EH
'    Dim rsOpt As ADODB.Recordset, aExch As EtsGeneralLib.ExchAtom
'    Dim dtExpiry As Date, dStrike#, dtExpiryMonth As Date, aPair As EtsMmQuotesLib.MmQvOptPairAtom
'    Dim aQuote As EtsMmQuotesLib.MmQvQuoteAtom, enOptType As EtsGeneralLib.EtsOptionTypeEnum, sKey$, aEnt As EtsGeneralLib.EtsMmEntityAtom
'    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, aStr As EtsMmQuotesLib.MmQvStrikeAtom, aOpt As EtsMmQuotesLib.MmQvOptAtom
'    Dim aStrAll As EtsMmQuotesLib.MmQvStrikeAtom, aReq As MmQvRequestAtom, aExpAll As EtsMmQuotesLib.MmQvExpAtom
'    Dim sMonth$
'
'    InitFuturesOptions = False
'    If m_Aux.Grp.ID = 0 Then Exit Function
'
'    Set rsOpt = gDBW.usp_MmOptionByFuture_Get(iFutureID, Date)
'
'    DoEvents
'    If Not m_bDataLoad Then GoTo EX
'
'    Do While Not rsOpt.EOF
'            dtExpiry = ReadDate(rsOpt!dtExpiry)
'            dtExpiryMonth = DateSerial(Year(dtExpiry), Month(dtExpiry), 1)
'
'            Set aExp = aFut.Exp(dtExpiryMonth)
'            If aExp Is Nothing Then
'                Set aExp = aFut.Exp.Add(dtExpiryMonth)
'                aExp.Expiry = dtExpiry
'                aExp.ExpiryMonth = dtExpiryMonth
'                aExp.Visible = True
'
'                Set aEnt = QV.CustRates(CStr(CLng(aExp.ExpiryMonth)))
'                If Not aEnt Is Nothing Then
'                    aExp.RateCust = aEnt.Data3
'                    Set aEnt = Nothing
'                End If
'            End If
'
'            Set aExpAll = m_Aux.Grp.ExpAll(dtExpiryMonth)
'            If aExpAll Is Nothing Then
'                Set aExpAll = m_Aux.Grp.ExpAll.Add(dtExpiryMonth)
'                aExpAll.Expiry = dtExpiry
'                aExpAll.ExpiryMonth = dtExpiryMonth
'                aExpAll.Visible = True
'
'                'aExpAll.RateCust = aExp.RateCust 'fokiny
'            End If
'
'            If InStr(aExpAll.RootNames, aFut.Symbol) = 0 Then
'                If Len(aExpAll.RootNames) > 0 Then
'                    aExpAll.RootNames = aExpAll.RootNames & "," & aFut.Symbol
'                Else
'                    aExpAll.RootNames = aFut.Symbol
'                End If
'            End If
'
'            Set aExpAll = Nothing
'
'            dStrike = Round(ReadDbl(rsOpt!fStrike), STRIKE_DECIMALS_COUNT)
'
'            Set aStr = aExp.Strike(dStrike)
'            If aStr Is Nothing Then
'                Set aStr = aExp.Strike.Add(dStrike)
'                aStr.Strike = dStrike
'                aStr.Visible = True
'            End If
'
'            Set aStrAll = m_Aux.Grp.StrikeAll(dStrike)
'            If aStrAll Is Nothing Then
'                Set aStrAll = m_Aux.Grp.StrikeAll.Add(dStrike)
'                aStrAll.Strike = dStrike
'                aStrAll.Visible = True
'            End If
'            Set aStrAll = Nothing
'
'            Set aPair = aStr.OptPair(aFut.ID)
'            If aPair Is Nothing Then
'                Set aPair = New EtsMmQuotesLib.MmQvOptPairAtom
'                aPair.RootID = aFut.ID
'
'                aStr.OptPair.Add aFut.ID, aFut.Symbol, aPair
'            End If
'
'            enOptType = IIf(ReadLng(rsOpt!tiIsCall) <> 0, enOtCall, enOtPut)
'
'            Set aOpt = aPair.Opt(enOptType)
'            If aOpt.ID = 0 Then
'                aOpt.ID = ReadLng(rsOpt!iContractID)
'                aOpt.Symbol = ReadStr(rsOpt!vcSymbol)
'                aOpt.OptType = enOptType
'                aOpt.Expiry = dtExpiry
'                aOpt.Strike = dStrike
'                aOpt.RootID = aFut.ID
'
'                aOpt.Vola = m_Aux.Grp.Und.VolaSrv.OptionVola(dtExpiry, dStrike)
'
'                If aOpt.Vola < 0 Then
'                    aOpt.Vola = BAD_DOUBLE_VALUE
'                End If
'
'                aFut.Opt.Add aOpt.ID, aOpt
'            End If
'
'            For Each aExch In aFut.OptExch
'                Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
'                Set aQuote.Exch = aExch
'                aQuote.LotSize = m_Aux.Grp.FutRootColl(aFut.FutRootID).OptLotSize * m_Aux.Grp.FutRootColl(aFut.FutRootID).FutLotSize
'
'                sMonth = GetMonth(Mid(aOpt.Symbol, InStr(1, aOpt.Symbol, "/", vbTextCompare) + 2, 1))
'                aQuote.Series = UCase$(Format$(aOpt.Expiry, "YY")) & sMonth & Mid(aOpt.Symbol, InStr(6, aOpt.Symbol, "/", vbTextCompare) + 1, Len(aOpt.Symbol) - InStr(6, aOpt.Symbol, "/", vbTextCompare) - 1)
'                'aQuote.Series = UCase$(Format$(aOpt.Expiry, "YYMMM")) & Trim$(Str$(Int(aOpt.Strike)))
'                sKey = aOpt.Symbol
'
'                If aExch.ID = 0 Then
'                    Set aOpt.DefQuote = aQuote
'                Else
'                    aQuote.Series = aQuote.Series & " " & aExch.Code
'                    sKey = sKey & "." & aExch.Code
'                End If
'
'                Set aReq = m_Aux.QuoteReqsAll(sKey)
'                If aReq Is Nothing Then
'                    Set aReq = m_Aux.QuoteReqsAll.Add(sKey)
'                    Set aReq.Exch = aExch
'                    Set aReq.Opt = aOpt
'                    Set aReq.Exp = aExp
'                    Set aReq.Fut = aFut
'                    Set aReq.FutRoot = m_Aux.Grp.FutRootColl(aFut.FutRootID)
'                End If
'                Set aReq = Nothing
'
'                aOpt.Quote.Add aExch.ID, aExch.Code, aQuote
'                Set aQuote = Nothing
'            Next
'        DoEvents
'        If Not m_bDataLoad Then GoTo EX
'
'        Set aOpt = Nothing
'        Set aPair = Nothing
'        Set aStr = Nothing
'        Set aExp = Nothing
'        Set aExpAll = Nothing
'
'        rsOpt.MoveNext
'    Loop
'
'    QV.OptQuotesCount = aFut.Opt.Count * aFut.OptExch.Count
'
'    InitFuturesOptions = True
'EX:
'    Set rsOpt = Nothing
'    Set aPair = Nothing
'    Set aExp = Nothing
'    Set aQuote = Nothing
'    Set aExch = Nothing
'    Set aExpAll = Nothing
'    Set aStrAll = Nothing
'    Exit Function
'EH:
'    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to load future options."
'    GoTo EX
'End Function
'
'Private Function InitIndexFutures(ByRef aContract As EtsGeneralLib.EtsContractAtom) As Boolean
'
'    On Error GoTo EH
'    Dim rsFut As ADODB.Recordset, aExch As EtsGeneralLib.ExchAtom, nID&
'    Dim rsExch As ADODB.Recordset
'    Dim dtMaturity As Date, dtMaturityMonth As Date
'    Dim aQuote As EtsMmQuotesLib.MmQvQuoteAtom, sKey$
'    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
'    Dim aReq As MmQvRequestAtom
'    Dim nLotSize&, sQuotationUnit$
'    Dim aFRoot As EtsFutRootAtom
'
'    InitIndexFutures = False
'    If m_Aux.Grp.ID = 0 Then Exit Function
'
'    m_Aux.Grp.ExpAll.Clear
'    Set rsFut = gDBW.usp_MmFutureByIndex_Get(m_Aux.Grp.ID, Date) 'Grp.ID ?
'    If rsFut.RecordCount > 0 Then pbProgress.Max = rsFut.RecordCount
'
'    DoEvents
'    If Not m_bDataLoad Then GoTo EX
'
'    Do While Not rsFut.EOF
'
'        '------------------------------------------------------------------------------
'        dtMaturity = ReadDate(rsFut!dtMaturity)
'        dtMaturityMonth = DateSerial(Year(dtMaturity), Month(dtMaturity), 1)
'        nLotSize = aContract.Und.FutRoots(ReadLng(rsFut!iFutureRootID)).FutLotSize
'        If (aContract.Und.FutRoots(ReadLng(rsFut!iFutureRootID)).QuotationUnitID) = 40 Then
'            sQuotationUnit = aContract.Und.FutRoots(ReadLng(rsFut!iFutureRootID)).QuotationUnitName
'        Else
'            sQuotationUnit = GetQuotationNameByID(aContract.Und.FutRoots(ReadLng(rsFut!iFutureRootID)).QuotationUnitID)
'        End If
'
'        Set aFut = m_Aux.Grp.Und.Fut(ReadLng(rsFut!iContractID))
'        If aFut Is Nothing Then
'            Set aFut = m_Aux.Grp.Und.Fut.Add(ReadLng(rsFut!iContractID))
'            aFut.ID = ReadLng(rsFut!iContractID)
'            aFut.Symbol = ReadStr(rsFut!vcSymbol)
'            aFut.MaturityDate = dtMaturity
'            aFut.MaturityMonth = dtMaturityMonth
'            aFut.LotSize = nLotSize
'            aFut.QuotationUnit = sQuotationUnit
'            'next two lines - need to move to InitContracts
'            Set aFRoot = aContract.Und.FutRoots(ReadLng(rsFut!iFutureRootID))
'            Set aContract.Und.UndPriceProfile = aFRoot.Futures(aFut.ID).UndPriceProfile
'            Set aContract.Und.OptPriceProfile = aFRoot.Futures(aFut.ID).OptPriceProfile
'
'            Set m_Aux.Grp.Und.UndPriceProfile = aContract.Und.UndPriceProfile
'            Set m_Aux.Grp.Und.OptPriceProfile = aContract.Und.OptPriceProfile
'            Set aFut.UndPriceProfile = aContract.Und.UndPriceProfile
'            Set aFut.OptPriceProfile = aContract.Und.OptPriceProfile
'            aContract.Und.IsAmerican = aFRoot.Futures(aFut.ID).IsAmerican
'            m_Aux.Grp.Und.IsAmerican = aContract.Und.IsAmerican
'            aFut.IsAmerican = aContract.Und.IsAmerican
'            aFut.FutRootID = ReadLng(rsFut!iFutureRootID)
'
'            If m_Aux.Grp.FutRootColl(aFRoot.ID) Is Nothing Then
'               Dim aFutRoot As EtsMmQuotesLib.MmQvFutRootAtom
'               Set aFutRoot = m_Aux.Grp.FutRootColl.Add(aFRoot.ID)
'
'               aFutRoot.ID = aFRoot.ID
'               aFutRoot.Symbol = aFRoot.Symbol
'               aFutRoot.Name = aFRoot.Name
'               aFutRoot.MatCalendarID = aFRoot.MatCalendarID
'               aFutRoot.FutLotSize = aFRoot.FutLotSize
'               aFutRoot.OptLotSize = aFRoot.OptLotSize
'
'                If (aFRoot.QuotationUnitID) = 40 Then
'                    aFutRoot.QuotationUnitName = aFRoot.QuotationUnitName
'                    aFutRoot.QuotationUnitID = aFRoot.QuotationUnitID
'                Else
'                    aFutRoot.QuotationUnitName = GetQuotationNameByID(aFRoot.QuotationUnitID)
'                    aFutRoot.QuotationUnitID = aFRoot.QuotationUnitID
'                End If
'            End If
'
'        End If
'
'
'        '-------------------------------------------------------------------------------
'            Set rsExch = gDBW.usp_MmFutureExchanges_Get(aFut.ID)
'            AddExch aFut.FutExch, 0, "", "<Primary>"
'            AddExch aFut.OptExch, 0, "", "<Primary>"
'
'            Do While Not rsExch.EOF
'                nID = ReadLng(rsExch!iExchangeID)
'                Set aExch = g_Exch(nID)
'                If Not aExch Is Nothing Then
'
'                    If ReadByte(rsExch!tiIsUnderlying) <> 0 Then
'                        If m_Aux.Grp.UndExchAll(nID) Is Nothing Then AddExch m_Aux.Grp.UndExchAll, nID, aExch.Code, aExch.Name
'                        If aFut.FutExch(nID) Is Nothing Then AddExch aFut.FutExch, nID, aExch.Code, aExch.Name
'                    End If
'
'                    If ReadByte(rsExch!tiIsOption) <> 0 Then
'                        If m_Aux.Grp.OptExchAll(nID) Is Nothing Then AddExch m_Aux.Grp.OptExchAll, nID, aExch.Code, aExch.Name
'                        If aFut.OptExch(nID) Is Nothing Then AddExch aFut.OptExch, nID, aExch.Code, aExch.Name
'                    End If
'
'                    Set aExch = Nothing
'                End If
'
'                rsExch.MoveNext
'            Loop
'        '------------------------------------------------------------------------------
'            Set aQuote = New EtsMmQuotesLib.MmQvQuoteAtom
'
'            aQuote.Series = UCase$(Format$(dtMaturity, "MMM YY"))
'            sKey = aFut.Symbol
'
'            aQuote.Series = aQuote.Series '& " " & aExch.Code
'            sKey = sKey '& "." & aExch.Code
'
'            Set aReq = m_Aux.QuoteReqsAll(sKey)
'            If aReq Is Nothing Then
'                Set aReq = m_Aux.QuoteReqsAll.Add(sKey)
'                Set aReq.Exch = aFut.FutExch(0)
'                Set aReq.Fut = aFut
'                'Set aReq.FutRoot = m_Aux.Grp.FutRoot
'            End If
'            Set aReq = Nothing
'
'            aFut.Quote.Add 0, "<Primary>", aQuote
'            Set aQuote = Nothing
'
'        InitFuturesOptions aContract, aFut, ReadLng(rsFut!iContractID) 'fokiny
'
'        DoEvents
'        If Not m_bDataLoad Then GoTo EX
'
'        IncProgress pbProgress
'        Set aFut = Nothing
'        rsFut.MoveNext
'    Loop
'
'    InitIndexFutures = True
'EX:
'    Set aFut = Nothing
'    Set rsFut = Nothing
'    Set rsExch = Nothing
'    Set aQuote = Nothing
'    Set aExch = Nothing
'    Exit Function
'EH:
'    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to load futures."
'    GoTo EX
'End Function

Private Function InitGroup(ByVal nGroupID As Long) As Boolean
    On Error GoTo EH
    Dim aContract As EtsGeneralLib.EtsContractAtom
    
    Dim nStart&
    nStart = GetTickCount
    'InitView
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "Data loading Enter.", m_frmOwner.GetCaption

    InitGroup = False
    
    If m_bInProc Then Exit Function
    
    Set aContract = g_ContractAll(nGroupID)
       
    If aContract Is Nothing Then Exit Function
    
    m_bDataLoad = True
    m_bInProc = True
    
    QV.UndQuotesCount = 0
    QV.OptQuotesCount = 0
    QV.FutQuotesCount = 0

    pbProgress.Min = 0
    pbProgress.Value = pbProgress.Min
    DoEvents
    

    m_Aux.Grp.ID = aContract.ID
    m_Aux.Grp.ContractType = aContract.ContractType
    m_Aux.Grp.Symbol = aContract.Symbol
    AdjustCaption
    AdjustState
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "Data loading Process. " _
                                                & "GrpID=""" & m_Aux.Grp.ID & """ " _
                                                & "ContractType=""" & m_Aux.Grp.ContractType & """ " _
                                                & "Symbol=""" & m_Aux.Grp.Symbol & """ ", m_frmOwner.GetCaption
    
    InitUnderlying aContract
    DoEvents
    If Not m_bDataLoad Or m_bShutDown Then GoTo Ex

    InitContracts aContract
    DoEvents
    If Not m_bDataLoad Or m_bShutDown Then GoTo Ex

    If Not InitGroupExchanges Then GoTo Ex
    
    InitContractsQuotes aContract

    QV.ConnectionString = g_Params.DbConnection
    Set QV.EtsMain = g_Main
        
    QV.Load m_Aux.Grp.ID, aContract.ContractType
    DoEvents
    If m_bShutDown Then GoTo Ex
    
    m_Aux.geOpt.RemoveSortPicture
    
    m_Aux.IndexOptionsComboVisible = (aContract.ContractType = enCtIndex And QV.Grp.Und.Fut.Count > 0)
    
    m_Aux.Grp.ShowIndexFutureOptions = (m_Aux.OptionsFilter = 1 And m_Aux.IndexOptionsComboVisible)
    

    UnderlyingUpdatePositions
    UnderlyingAdjustRates True
    m_Aux.FormatFutGrid
    m_Aux.FormatUndGrid

    InitGroup = True
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "Data loading Exit. Duration " & GetTickCount - nStart & " ms", m_frmOwner.GetCaption
    
Ex:
    m_bInProc = False
    m_bDataLoad = False
    Set aContract = Nothing
    Exit Function
EH:
    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to load underlying."
    GoTo Ex
End Function

Private Sub ShowGroup()
    On Error GoTo Er
    Dim aRowData As MmQvRowData, aExch As EtsGeneralLib.ExchAtom, aPair As EtsMmQuotesLib.MmQvOptPairAtom, aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim nRow&, i&, sKey$, aExp As EtsMmQuotesLib.MmQvExpAtom, aStr As EtsMmQuotesLib.MmQvStrikeAtom, aQuote As EtsMmQuotesLib.MmQvQuoteAtom
    Dim bAllExpVisible As Boolean, bAllExchVisible As Boolean, bAllRootVisible As Boolean, bShowOnlyDefExch As Boolean, aRoot As EtsMmQuotesLib.MmQvOptRootAtom
    Dim bAllStrVisible As Boolean, aStrAll As EtsMmQuotesLib.MmQvStrikeAtom
               
    If (m_Aux.Grp.ID = 0) Then Exit Sub
    
    AdjustState
    DoEvents
    
    m_Aux.GridLock(GT_QUOTES_UNDERLYING).LockRedraw
    m_Aux.GridLock(GT_QUOTES_DIVIDENDS).LockRedraw
    m_Aux.GridLock(GT_QUOTES_FUTURES).LockRedraw
    m_Aux.GridLock(GT_QUOTES_OPTIONS).LockRedraw
    
    pbProgress.Max = QV.UndQuotesCount + QV.OptQuotesCount + QV.FutQuotesCount

    lblProcess.Caption = "Formatting..."
    lblProcess.Refresh
    
    With fgUnd
        
        .Rows = 1
        On Error GoTo Er
        bAllExchVisible = True
        If QV.VisibleUndExch.Count > 0 Then
            For Each aExch In m_Aux.Grp.UndExchAll
                If Not QV.VisibleUndExch(Trim$(Str$(aExch.ID))) Is Nothing Then
                    bAllExchVisible = False
                    Exit For
                End If
            Next
        End If
        
        For Each aExch In m_Aux.Grp.UndExchAll
            If Not bAllExchVisible Then
                aExch.Visible = Not QV.VisibleUndExch(Trim$(Str$(aExch.ID))) Is Nothing
            Else
                aExch.Visible = (aExch.ID = 0)
            End If
        Next
        
        AdjustUnderlyingsExchVisible
        AdjustUnderlyingsPosExchID
        On Error Resume Next
        
        If m_Aux.Grp.IsStockOrIndex Then
            For Each aExch In m_Aux.Grp.Und.UndExch
                Set aQuote = m_Aux.Grp.Und.Quote(aExch.ID)
                
                If Not aQuote Is Nothing Then
                    .AddItem ""
                    nRow = .Rows - 1
                
                    Set aRowData = New MmQvRowData
                    Set aRowData.Und = m_Aux.Grp.Und
                    Set aRowData.UndQuote = aQuote
                    Set aRowData.Exch = aExch
                    .RowData(nRow) = aRowData
    
                    sKey = aRowData.Und.Symbol
                    If aExch.ID <> 0 Then sKey = sKey & "." & aExch.Code
                    .TextMatrix(nRow, QUC_KEY) = sKey
                    
                    m_AuxOut.UnderlyingUpdateQuote nRow, True, False
    
                    .RowHidden(nRow) = Not aRowData.Exch.Visible
    
                    Set aRowData = Nothing
                    IncProgress pbProgress
                
                    Set aQuote = Nothing
                End If
            Next
            
            If Not m_Aux.Grp.Und.SynthUnd Is Nothing Then
                For Each aUnd In m_Aux.Grp.Und.SynthUnd
                    For Each aExch In aUnd.UndExch
                        Set aQuote = aUnd.Quote(aExch.ID)
                        If Not aQuote Is Nothing Then
                            .AddItem ""
                            nRow = .Rows - 1
                                                    
                            Set aRowData = New MmQvRowData
                            Set aRowData.Und = aUnd
                            Set aRowData.UndQuote = aQuote
                            Set aRowData.Exch = aExch
                            .RowData(nRow) = aRowData
            
                            sKey = aRowData.Und.Symbol
                            If aExch.ID <> 0 Then sKey = sKey & "." & aExch.Code
                            .TextMatrix(nRow, QUC_KEY) = sKey
                            
                            m_AuxOut.UnderlyingUpdateQuote nRow, True, False
            
                            .RowHidden(nRow) = Not aRowData.Exch.Visible
        
                            Set aRowData = Nothing
                            IncProgress pbProgress
                            
                            Set aQuote = Nothing
                        End If
                    Next
                Next
            End If
        Else
             For Each aExch In m_Aux.Grp.Und.UndExch
                Set aQuote = m_Aux.Grp.Und.Quote(aExch.ID)
                
                If Not aQuote Is Nothing Then
                    .AddItem ""
                    nRow = .Rows - 1
                
                    Set aRowData = New MmQvRowData
                    Set aRowData.Und = m_Aux.Grp.Und
                    'Set aRowData.FutRoot = m_Aux.Grp.FutRootColl(aFut.FutRootID)
                    Set aRowData.UndQuote = aQuote
                    Set aRowData.Exch = aExch
                    .RowData(nRow) = aRowData
    
                    sKey = aRowData.Und.Symbol
                    If aExch.ID <> 0 Then sKey = sKey & "." & aExch.Code
                    .TextMatrix(nRow, QUC_KEY) = sKey
                    
                    m_AuxOut.UnderlyingUpdateQuote nRow, True, False
    
                    .RowHidden(nRow) = Not aRowData.Exch.Visible
    
                    Set aRowData = Nothing
                    IncProgress pbProgress
                    
                    Set aQuote = Nothing
                End If
             Next
        End If
        
        m_Aux.FormatUndColumns
        m_AuxOut.UnderlyingUpdateColors
        m_AuxOut.UnderlyingUpdateTotals
    End With

    m_AuxOut.RatesUpdate
    m_Aux.AdjustDivsAndRatesVisible
    m_Aux.AdjustVolaVisible
    m_AuxOut.ProfilesUpdate
    m_AuxOut.DivsUpdate
    m_AuxOut.ModelUpdate
    m_AuxOut.CalendarUpdate
    m_AuxOut.VolaUpdate
    
    With fgOpt
        .Rows = 1

        QV.OptsRefresh True
        
        QV.OptsColumnsOrder = m_Aux.gdOpt.IdxCopy
        
        RefreshFutsGrid
        
        .FlexDataSource = QV
        
        SortOptionsByDefault
        
        QV.VisibleExp.Clear
        QV.VisibleRoot.Clear
        QV.VisibleStr.Clear

        
        m_Aux.FormatOptColumns
        m_AuxOut.OptionsUpdateColors
   
        i = -1
       
        m_AuxOut.OptionsUpdateBackColor g_Params.QuoteOptExpirySeparation
    End With
    
    QV.VisibleExp.Clear
    QV.VisibleRoot.Clear
    QV.VisibleUndExch.Clear
    QV.VisibleOptExch.Clear
    QV.VisibleStr.Clear
    QV.VisibleFut.Clear
    QV.CustRates.Clear
    m_Aux.UseCustRates = False
    m_Aux.IsAmerican = -1
    
    ClearSpread False
    AdjustCaption
    Set aRowData = Nothing
    
    m_Aux.GridLock(GT_QUOTES_UNDERLYING).UnlockRedraw
    m_Aux.GridLock(GT_QUOTES_DIVIDENDS).UnlockRedraw
    m_Aux.GridLock(GT_QUOTES_FUTURES).UnlockRedraw
    m_Aux.GridLock(GT_QUOTES_OPTIONS).UnlockRedraw
    
    imgStop.Visible = True
    imgStopDis.Visible = False
    lblProcess.Caption = ""
    m_bInProc = False
    AdjustState
    'UserControl_Resize
Exit Sub
Er:
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogWarning, "Show Group " & Err.Description, m_frmOwner.GetCaption
    
End Sub

Private Sub UnderlyingUpdatePositions()
    On Error Resume Next
    Dim aOpt As EtsMmQuotesLib.MmQvOptAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim i&, nCount&, aTrd As EtsMmGeneralLib.MmTradeInfoAtom, aTrdByUnd As EtsMmGeneralLib.MmTradeInfoColl, nBS&
    
        m_Aux.Grp.Und.Qty = BAD_LONG_VALUE
        m_Aux.Grp.Und.QtyInShares = BAD_LONG_VALUE
        
        For Each aOpt In m_Aux.Grp.Und.Opt
            aOpt.Qty = BAD_LONG_VALUE
            aOpt.QtyInShares = BAD_LONG_VALUE
        Next
        
        'Set aTrdByUnd = TradeChannel.Trades.FilterTrades(m_Aux.Grp.Und.ID, TYPE_UNDERLYING, m_Aux.TradesFilter, g_UnderlyingGroup, True)
        Set aTrdByUnd = TradeChannel.TradesByUnd(CStr(m_Aux.Grp.Und.ID))
        If Not aTrdByUnd Is Nothing Then
            nCount = aTrdByUnd.Count
    
            For Each aTrd In aTrdByUnd
                'If m_Aux.CheckTradeFilter(aTrd) Then
                    nBS = IIf(aTrd.IsBuy, 1, -1)
    
                    If aTrd.ContractType = enCtOption Then
                        Set aOpt = m_Aux.Grp.Und.Opt(aTrd.ContractID)
                        If Not aOpt Is Nothing Then
                            If aOpt.Qty <= BAD_LONG_VALUE Then aOpt.Qty = 0&
                            aOpt.Qty = aOpt.Qty + aTrd.Quantity * nBS
    
                            If aOpt.QtyInShares <= BAD_LONG_VALUE Then aOpt.QtyInShares = 0&
                            aOpt.QtyInShares = aOpt.QtyInShares + aTrd.Quantity * aTrd.LotSize * nBS
    
                            Set aOpt = Nothing
                        End If
                        
                    ElseIf aTrd.ContractType = enCtIndex Or aTrd.ContractType = enCtStock Then
                        If m_Aux.Grp.Und.Qty <= BAD_LONG_VALUE Then m_Aux.Grp.Und.Qty = 0&
                        m_Aux.Grp.Und.Qty = m_Aux.Grp.Und.Qty + aTrd.Quantity * nBS
    
                        If m_Aux.Grp.Und.QtyInShares <= BAD_LONG_VALUE Then m_Aux.Grp.Und.QtyInShares = 0&
                        m_Aux.Grp.Und.QtyInShares = m_Aux.Grp.Und.QtyInShares + aTrd.Quantity * aTrd.LotSize * nBS
                    End If
                'End If
                Set aTrd = Nothing
            Next
            Set aTrdByUnd = Nothing
        End If
        For Each aFut In m_Aux.Grp.Und.Fut
            aFut.Qty = BAD_LONG_VALUE
            aFut.QtyInShares = BAD_LONG_VALUE
            
            For Each aOpt In aFut.Opt
                aOpt.Qty = BAD_LONG_VALUE
                aOpt.QtyInShares = BAD_LONG_VALUE
            Next
            
            Set aTrdByUnd = TradeChannel.TradesByFut(CStr(aFut.ID))
            If Not aTrdByUnd Is Nothing Then
                nCount = aTrdByUnd.Count
        
                For Each aTrd In aTrdByUnd
                    If m_Aux.CheckTradeFilter(aTrd) Then
                        nBS = IIf(aTrd.IsBuy, 1, -1)
        
                        If aTrd.ContractType = enCtFutOption Then
                            Set aOpt = aFut.Opt(aTrd.ContractID)
                            If Not aOpt Is Nothing Then
                                If aOpt.Qty <= BAD_LONG_VALUE Then aOpt.Qty = 0&
                                aOpt.Qty = aOpt.Qty + aTrd.Quantity * nBS
        
                                If aOpt.QtyInShares <= BAD_LONG_VALUE Then aOpt.QtyInShares = 0&
                                aOpt.QtyInShares = aOpt.QtyInShares + aTrd.Quantity * aTrd.LotSize * nBS
        
                                Set aOpt = Nothing
                            End If
                            
                        ElseIf aTrd.ContractType = enCtFuture Then
                            If aFut.Qty <= BAD_LONG_VALUE Then aFut.Qty = 0&
                            aFut.Qty = aFut.Qty + aTrd.Quantity * nBS
        
                            If aFut.QtyInShares <= BAD_LONG_VALUE Then aFut.QtyInShares = 0&
                            aFut.QtyInShares = aFut.QtyInShares + aTrd.Quantity * aTrd.LotSize * nBS
                        End If
                    End If
                    Set aTrd = Nothing
                Next
                Set aTrdByUnd = Nothing
            End If
        Next
End Sub

Public Sub RefreshView()
    On Error Resume Next
    If m_bShutDown Or Not m_Aux.RealTime Or m_bSubscribingNow Then Exit Sub
    
    If m_BatchPriceProvider.IsQuotesUpdated Then
       If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "RefreshView: Initiate Realtime Refresh", m_frmOwner.GetCaption
       tmrRealTime.Enabled = True
    Else
           If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "RefreshView: No Realtime Refresh needed", m_frmOwner.GetCaption
    End If
End Sub

Private Sub InitColumns()
    On Error Resume Next
    g_DefGrids(GT_QUOTES_UNDERLYING).CopyTo m_gdUnd
    g_DefGrids(GT_QUOTES_DIVIDENDS).CopyTo m_gdDiv
    g_DefGrids(GT_QUOTES_VOLA).CopyTo m_gdVol
    g_DefGrids(GT_QUOTES_FUTURES).CopyTo m_gdFut
    g_DefGrids(GT_QUOTES_OPTIONS).CopyTo m_gdOpt
End Sub

Private Sub SetRefreshHint(ByVal bSet As Boolean)
    On Error Resume Next
    lblStatus.Visible = True
    lblStatus.Caption = IIf(bSet, "Use F5 to refresh results.", "")
End Sub

Private Sub UnderlyingCalculate()
    On Error Resume Next
    m_bInProc = True
    AdjustState
                
    CalculateUnderlyingOptions True
                
    m_bInProc = False
    AdjustState
    
    m_AuxOut.UnderlyingUpdate True, True
    m_AuxOut.ProfilesUpdate
    m_AuxOut.DivsUpdate
    m_AuxOut.CalendarUpdate
    m_AuxOut.ModelUpdate
    m_AuxOut.OptionsUpdate False, True, True
    m_AuxOut.FuturesUpdate False, True, True
    m_AuxOut.VolaUpdateValues
    m_AuxOut.UnderlyingUpdateTotals
    UpdateTotals
End Sub

Private Sub aParams_PriceProfilesChange()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.ID = 0 Then Exit Sub
    
    If Not m_Aux.RealTime Then
        SetRefreshHint True
        
    ElseIf Not m_bSubscribingNow Then
        UnderlyingCalculate
    End If
End Sub

Private Sub aParams_PriceRoundingRuleChange()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.ID = 0 Then Exit Sub
    
    If Not m_Aux.RealTime Then
        SetRefreshHint True
        
    ElseIf Not m_bSubscribingNow Then
        UnderlyingCalculate
    End If
End Sub

Private Sub aParams_UnderlyingsParamsChange(collUpdUnd As EtsGeneralLib.EtsMmFilterAtomColl)
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.ID = 0 Or m_bFireEvent Then Exit Sub
    Dim aUndFilterAtom As EtsGeneralLib.EtsMmFilterAtom, aFutFilterAtom As EtsGeneralLib.EtsMmFilterAtom
    Dim aContract As EtsGeneralLib.EtsContractAtom, bRecalc As Boolean: bRecalc = False
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    Set aUndFilterAtom = collUpdUnd(CStr(m_Aux.Grp.Und.ID))
    If Not m_Aux.Grp.IsStockOrIndex Then Set aFutFilterAtom = collUpdUnd(CStr(m_Aux.Grp.Und.ID))
    
    If aUndFilterAtom Is Nothing And aFutFilterAtom Is Nothing Then Exit Sub
    
    If Not m_Aux.RealTime Then
        SetRefreshHint True
    Else
        If Not aUndFilterAtom Is Nothing Then
            Set aContract = g_ContractAll(m_Aux.Grp.Und.ID)
            If Not aContract Is Nothing Then
                m_Aux.Grp.Und.IsAmerican = aContract.Und.IsAmerican
                Set m_Aux.Grp.Und.UndPriceProfile = aContract.Und.UndPriceProfile
                Set m_Aux.Grp.Und.OptPriceProfile = aContract.Und.OptPriceProfile
                If m_Aux.Grp.Und.UndType = enCtStock Then
                    Set m_Aux.Grp.Und.Dividend = aContract.Und.Dividend
                Else
                    m_Aux.Grp.Und.Yield = aContract.Und.Yield
                End If
                m_Aux.Grp.Und.Skew = aContract.Und.Skew
                m_Aux.Grp.Und.Kurt = aContract.Und.Kurt
                m_Aux.Grp.Und.IsHTB = aContract.Und.IsHTB
                
                bRecalc = True
            End If
        End If
        
        If Not m_Aux.Grp.IsStockOrIndex And Not aFutFilterAtom Is Nothing Then
            For Each aFut In m_Aux.Grp.Und.Fut
                Set aContract = g_ContractAll(aFut.ID)
                If Not aContract Is Nothing Then
                    aFut.IsAmerican = aContract.Und.IsAmerican
                    Set aFut.UndPriceProfile = aContract.Und.UndPriceProfile ' aContract.Fut.UndPriceProfile
                    Set aFut.OptPriceProfile = aContract.Und.OptPriceProfile ' aContract.Fut.OptPriceProfile
    
                    bRecalc = True
                End If
            Next
        End If
        
        If bRecalc And Not m_bSubscribingNow Then UnderlyingCalculate
        
        Set aUndFilterAtom = Nothing
        Set aFutFilterAtom = Nothing
        Set aContract = Nothing
    End If
End Sub

Private Sub aParams_UndPriceToleranceChange()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.ID = 0 Then Exit Sub
    
    If Not m_Aux.RealTime Then
        SetRefreshHint True
        
    ElseIf Not m_bSubscribingNow Then
        UnderlyingCalculate
    End If
End Sub


Private Sub dtCalculationDate_Change()
    fgVol.Text = dtCalculationDate.Value
    m_bDateChanged = True
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter changed date. New date: " & dtCalculationDate.Value, m_frmOwner.GetCaption
End Sub

Private Sub dtCalculationDate_KeyDown(KeyCode As Integer, Shift As Integer)
    Select Case KeyCode
        Case vbKeyEscape
            fgVol = dtCalculationDate.Tag
            dtCalculationDate.Visible = False
        Case vbKeyReturn
            dtCalculationDate.Visible = False
    End Select
    Dim nUnds&, nFuts&, nOpts&
    If m_bDateChanged And Not dtCalculationDate.Visible And Not m_Aux.RealTime And m_Aux.Grp.ID <> 0 Then
        CalculateUnderlyingOptions True
        nUnds = m_AuxOut.UnderlyingUpdate(False, True)
        nFuts = m_AuxOut.FuturesUpdate(False, True, True)
        nOpts = m_AuxOut.OptionsUpdate(False, True, True)
        m_AuxOut.VolaUpdateValues
        m_bCalculationDateChanged = True
        m_bDateChanged = False
        AdjustState
        m_AuxOut.UnderlyingUpdateTotals
        UpdateTotals
   End If

End Sub

Private Sub dtCalculationDate_LostFocus()
    dtCalculationDate.Visible = False
    Dim nUnds&, nOpts&, nFuts&
    If m_bDateChanged And Not dtCalculationDate.Visible And Not m_Aux.RealTime And m_Aux.Grp.ID <> 0 Then
        CalculateUnderlyingOptions True, , , True
        nUnds = m_AuxOut.UnderlyingUpdate(False, True)
        nFuts = m_AuxOut.FuturesUpdate(False, True, True)
        nOpts = m_AuxOut.OptionsUpdate(False, True, True)
        m_AuxOut.VolaUpdateValues
        m_bCalculationDateChanged = True
        m_bDateChanged = False
       
        AdjustState
        m_AuxOut.UnderlyingUpdateTotals
        UpdateTotals
   End If
End Sub

Private Sub fgDiv_DblClick()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter DblClick Enter", m_frmOwner.GetCaption
    
    With fgDiv
        m_enMenuGrid = GT_QUOTES_DIVIDENDS
        m_nMenuGridCol = .MouseCol
        m_nMenuGridRow = .MouseRow
        m_nMenuGridCols = .Cols
        m_nMenuGridRows = .Rows
        
        HandleGridDblClick False
    End With

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter DblClick Exit", m_frmOwner.GetCaption

End Sub

Private Sub fgDiv_KeyDown(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    If IsHotKeyGridClipOrOrderCard(KeyCode, Shift) Then
        m_bKeyDown(GT_QUOTES_DIVIDENDS) = True
    End If
End Sub

Private Sub fgDiv_KeyUp(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    
  
    If m_bKeyDown(GT_QUOTES_DIVIDENDS) Then
        m_bKeyDown(GT_QUOTES_DIVIDENDS) = False
        With fgDiv
            m_enMenuGrid = GT_QUOTES_DIVIDENDS
            m_nMenuGridCol = .Col
            m_nMenuGridRow = .Row
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
        End With
        
        Select Case True
            Case KeyCode = vbKeyInsert And Shift = vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter Hot key Alt+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxOrderNewStock_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbCtrlMask + vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter Hot key Alt+Ctrl+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxOrderNewOption_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbShiftMask + vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter Hot key Alt+Shift+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxTntCardNew_Click
            
            Case (KeyCode = vbKeyInsert Or KeyCode = vbKeyC) And Shift = vbCtrlMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter Hot key Ctrl+(Insert/C) pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxCopy_Click
        End Select
    End If
End Sub

Private Sub fgFut_AfterEdit(ByVal Row As Long, ByVal Col As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nKey&, sValue$, dValue#, aQuote As EtsMmQuotesLib.MmQvQuoteAtom, sKey$, nRow&
    Dim aRowData As MmQvRowData, aOpt As EtsMmQuotesLib.MmQvOptAtom, nOptType&
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim aTradeColl As MmTradeInfoColl
    Dim aTrd As EtsMmGeneralLib.MmTradeInfoAtom
    
    Dim aContract As EtsGeneralLib.EtsContractAtom
    Set aContract = g_ContractAll(m_Aux.Grp.Und.ID)
    Dim aPrProf As EtsGeneralLib.EtsPriceProfileAtom
    Dim mUndID&
        
    With fgFut
        sValue = Trim$(.TextMatrix(Row, Col))
        If m_sCurrentOriginalText <> sValue Then
            nKey = .ColKey(Col)
            If Err.Number = 0 Then
            
                Set aRowData = .RowData(Row)
                Debug.Assert Not aRowData Is Nothing
                Set aQuote = aRowData.FutQuote
                Set aFut = aRowData.Fut

                    If Not aRowData Is Nothing And Not aQuote Is Nothing Then
                        dValue = Abs(ReadDbl(sValue))

                        Select Case nKey
                            Case QOF_BID
                                If aQuote.IsDirty Then
                                    If Not g_PerformanceLog Is Nothing Then _
                                        g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter Changed " & " Bid. " _
                                                                                    & "OldValue=""" & aQuote.PriceBid & """ " _
                                                                                    & "NewValue=""" & dValue & """. " & GetFutureInfo, m_frmOwner.GetCaption
                                                                                    
                                If aQuote.PriceBid >= 0# Then aQuote.PriceBidTick = dValue - aQuote.PriceBid
                                aQuote.PriceBid = dValue
                                .TextMatrix(Row, Col) = aQuote.PriceBid
                                m_AuxOut.FutureUpdateColors Row
                                End If

                            Case QOF_ASK
                                If aQuote.IsDirty Then
                                    If Not g_PerformanceLog Is Nothing Then _
                                        g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter Changed " & " Ask. " _
                                                                                    & "OldValue=""" & aQuote.PriceAsk & """ " _
                                                                                    & "NewValue=""" & dValue & """. " & GetFutureInfo, m_frmOwner.GetCaption
                                                                                    
                                If aQuote.PriceAsk >= 0# Then aQuote.PriceAskTick = dValue - aQuote.PriceAsk
                                aQuote.PriceAsk = dValue
                                .TextMatrix(Row, Col) = aQuote.PriceAsk
                                m_AuxOut.FutureUpdateColors Row
                                End If
                            Case QOF_UND_PROFILE
                                Set aPrProf = g_PriceProfile(dValue)
                                Set aContract.Und.FutRoots(aFut.FutRootID).Futures(aFut.ID).UndPriceProfile = Nothing
                                Set aContract.Und.FutRoots(aFut.FutRootID).Futures(aFut.ID).UndPriceProfile = aPrProf
                                
                                .TextMatrix(Row, Col) = dValue
                                gDBW.usp_MmFuture_Save aFut.ID, dValue, 0
                            Case QOF_OPT_PROFILE
                                Set aPrProf = g_PriceProfile(dValue)
                                Set aContract.Und.FutRoots(aFut.FutRootID).Futures(aFut.ID).OptPriceProfile = Nothing
                                Set aContract.Und.FutRoots(aFut.FutRootID).Futures(aFut.ID).OptPriceProfile = aPrProf
                                                               
                                .TextMatrix(Row, Col) = dValue
                                gDBW.usp_MmFuture_Save aFut.ID, 0, dValue
                            Case QOF_ACTIVE
                                UpdateActiveFutures CLng(dValue)
                            Case QOF_RATIO
                               UpdateRatio aFut, dValue
                            Case QOF_BASIS
                                UpdateBasis aFut, ReadDbl(sValue)
                                
                            Case QOF_ACTIVEPRICE
                                If Not QV.Grp.Und.ActiveFuture Is Nothing Then
                                    If (aFut.ID = QV.Grp.Und.ActiveFuture.ID) Then
                                        aFut.ActivePrice = CDbl(sValue)
                                        aFut.IsUseManualActivePrice = True
                                        UpdateFutureManualPrice aFut.ActivePrice, aFut.ID
                                    End If
                                Else
                                    aFut.ActivePrice = CDbl(sValue)
                                    aFut.IsUseManualActivePrice = True
                                    UpdateFutureManualPrice aFut.ActivePrice, aFut.ID
                                End If

                            Case QOF_CLOSE
                                If aQuote.IsDirty Then
                                    If Not g_PerformanceLog Is Nothing Then _
                                        g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter Changed " & " Close. " _
                                                                                    & "OldValue=""" & aQuote.PriceClose & """ " _
                                                                                    & "NewValue=""" & dValue & """. " & GetFutureInfo, m_frmOwner.GetCaption
                                    If aQuote.PriceClose <> dValue Then
                                        aQuote.PriceClose = dValue
                                        .TextMatrix(Row, Col) = aQuote.PriceClose
                                        Set aFut = aRowData.Fut
                                        If Not aFut Is Nothing Then
                                            Set aTradeColl = TradeChannel.TradesByFut(aRowData.Fut.ID)
                                            If Not aTradeColl Is Nothing Then
                                                For Each aTrd In aTradeColl
                                                    If aTrd.ContractID = aFut.ID Then
                                                        aTrd.Fut.PriceClose = aFut.Quote(0).PriceClose
                                                        mUndID = aTrd.UndID
                                                        Set aTrd = Nothing
                                                    End If
                                                Next
                                            End If
                                            
                                            If SavePriceClose(enCtFuture, aFut.ID, aFut.Quote(0).PriceClose) Then
                                                TradeChannel.PriceCloseForPub enCtFuture, aFut.ID, aFut.UndID, aFut.Quote(0).PriceClose, BAD_DOUBLE_VALUE
                                            End If
                                            
                                            If (Not g_ContractAll(aFut.ID).Fut Is Nothing) Then
                                                g_ContractAll(aFut.ID).Fut.PriceClose = dValue
                                            End If
                                            
                                        End If
                                        m_AuxOut.FutureUpdateColors Row
                                    End If
                                End If
                        End Select
                        
                        If ((nKey <> QOF_UND_PROFILE) And (nKey <> QOF_OPT_PROFILE)) Then
                           Recalculate False
                        End If
                            
                    End If
                
                Set aQuote = Nothing
                Set aFut = Nothing
                Set aRowData = Nothing
            End If
        End If
    End With
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Future Filter AfterEdit Exit", m_frmOwner.GetCaption
    
End Sub

Private Sub fgFut_AfterMoveColumn(ByVal Col As Long, Position As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nIdx&, i&, nOldPos&, nNewPos&
    If Col = Position Then Exit Sub
    
    nOldPos = Col - QOF_SYMBOL
    nNewPos = Position - QOF_SYMBOL
    nIdx = m_gdFut.Idx(nOldPos)
    If nOldPos > nNewPos Then
        For i = nOldPos To nNewPos Step -1
            If i > nNewPos Then
                m_gdFut.Idx(i) = m_gdFut.Idx(i - 1)
            End If
        Next
        m_gdFut.Idx(nNewPos) = nIdx
    Else
        For i = nOldPos To nNewPos
            If i < nNewPos Then
                m_gdFut.Idx(i) = m_gdFut.Idx(i + 1)
            End If
        Next
        m_gdFut.Idx(nNewPos) = nIdx
    End If
End Sub

Private Sub fgFut_AfterUserResize(ByVal Row As Long, ByVal Col As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nIdx&
    
    If Col >= 0 And Row < 0 Then
        With fgFut
            nIdx = .ColKey(Col)
            If nIdx >= QOF_SYMBOL And nIdx <= QOF_LAST_COLUMN Then
                m_gdFut.Col(nIdx).Width = IIf(.ColWidth(Col) > 0, .ColWidth(Col), -1)
            End If
        End With
    End If
End Sub

Private Sub fgFut_BeforeMoveColumn(ByVal Col As Long, Position As Long)
On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nOldIdx&, nNewIdx&
    
    nOldIdx = fgFut.ColKey(Col)
    nNewIdx = fgFut.ColKey(Position)
    
    If nOldIdx = QOF_NONE Or nNewIdx = QOF_NONE Then
        Position = Col
    ElseIf Not m_gdFut.Col(nOldIdx).CanChangeOrder Or Not m_gdFut.Col(nNewIdx).CanChangeOrder Then
        Position = Col
    End If
End Sub

Private Sub fgFut_DblClick()
On Error Resume Next
    If m_bShutDown Then Exit Sub
    With fgFut
        m_enMenuGrid = GT_QUOTES_FUTURES
        m_nMenuGridCol = .MouseCol
        m_nMenuGridRow = .MouseRow
        m_nMenuGridCols = .Cols
        m_nMenuGridRows = .Rows
        
        HandleGridDblClick True
    End With
End Sub

Private Sub fgFut_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
On Error Resume Next
    If m_bShutDown Then Exit Sub
    If Button = vbRightButton Then
        With fgFut
            m_enMenuGrid = GT_QUOTES_FUTURES
            m_nMenuGridCol = .MouseCol
            m_nMenuGridRow = .MouseRow
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
            
            If m_nMenuGridRow > 0 And m_nMenuGridRow < m_nMenuGridRows And m_nMenuGridCol > 1 And m_nMenuGridCol < m_nMenuGridCols Then
                .Row = m_nMenuGridRow
            End If
            
            ShowPopup
        End With
    End If
End Sub

Private Sub fgFut_StartEdit(ByVal Row As Long, ByVal Col As Long, Cancel As Boolean)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim aRowData As MmQvRowData
    Dim nKey&
    Cancel = True
    
    If m_bInProc Or m_bDataLoad Or m_bLastQuoteReqNow Or m_bSubscribingNow Then Exit Sub
    If IsDblClickHandled Then Exit Sub
    
    If m_Aux.Grp.ID <> 0 Then
        With fgFut
            nKey = .ColKey(Col)
            If Err.Number = 0 Then
                If m_Aux.RealTime Then Exit Sub
                Cancel = Not m_gdFut.Col(nKey).CanEdit
                If Not Cancel Then
                    Set aRowData = .RowData(Row)
                    If nKey < QOF_SYMBOL Then
                        Cancel = (aRowData.Fut Is Nothing Or aRowData.FutQuote Is Nothing)
                    End If
                    If nKey = QOF_BASIS Then
                        Cancel = QV.Grp.ContractType = enCtFutUnd
                    End If
                    
                    Set aRowData = Nothing
                End If
                
                If Not Cancel Then
                    Cancel = (Not m_Aux.Grp.Und.IsTraderContract) 'And (nKey = QOC_C_VOLA Or nKey = QOC_P_VOLA))
                 End If
                 Set aRowData = .RowData(Row)
                  If Not m_Aux.Grp.Und.ActiveFuture Is Nothing Then
                    If m_Aux.Grp.Und.ActiveFuture.ID <> aRowData.Fut.ID Then
                        Cancel = True
                    End If
                End If

            End If
            
            If Not Cancel Then
                m_sCurrentOriginalText = Trim$(.TextMatrix(Row, Col))
            End If
        End With
    End If
End Sub

Private Sub fgOpt_AfterUserResize(ByVal Row As Long, ByVal Col As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nIdx&
    
    If Col >= 0 And Row < 0 Then
        With fgOpt
            nIdx = .ColKey(Col)
            If nIdx >= QOC_C_SYMBOL And nIdx <= QOC_LAST_COLUMN Then
                m_gdOpt.Col(nIdx).Width = IIf(.ColWidth(Col) > 0, .ColWidth(Col), -1)
            End If
        End With
    End If
End Sub




Private Sub fgUnd_AfterUserResize(ByVal Row As Long, ByVal Col As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nIdx&
    
    If Col >= 0 And Row < 0 Then
        With fgUnd
            nIdx = .ColKey(Col)
            If nIdx >= QUC_SYMBOL And nIdx <= QUC_LAST_COLUMN Then
                m_gdUnd.Col(nIdx).Width = IIf(.ColWidth(Col) > 0, .ColWidth(Col), -1)
            End If
        End With
    End If
End Sub

Private Sub fgUnd_SetupEditStyle(ByVal Row As Long, ByVal Col As Long, ByVal IsCombo As Boolean, style As Long, StyleEx As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If Row = m_nUndMainRow And fgUnd.ColKey(Col) = QUC_SYMBOL Then style = style Or CBS_UPPERCASE
End Sub

Private Sub fgVol_BeforeScroll(ByVal OldTopRow As Long, ByVal OldLeftCol As Long, ByVal NewTopRow As Long, ByVal NewLeftCol As Long, Cancel As Boolean)
    If dtCalculationDate.Visible Then Cancel = True
End Sub

Private Sub fgVol_DblClick()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    With fgVol
        m_enMenuGrid = GT_QUOTES_VOLA
        m_nMenuGridCol = .MouseCol
        m_nMenuGridRow = .MouseRow
        m_nMenuGridCols = .Cols
        m_nMenuGridRows = .Rows
        
        HandleGridDblClick False
    End With
End Sub

Private Sub fgVol_KeyDown(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If IsHotKeyGridClipOrOrderCard(KeyCode, Shift) _
            Or (KeyCode = vbKeyF And (Shift = vbCtrlMask _
                                    Or Shift = vbCtrlMask + vbShiftMask _
                                    Or Shift = vbCtrlMask + vbAltMask)) _
            Or (KeyCode = vbKeyI And (Shift = vbCtrlMask + vbShiftMask _
                                    Or Shift = vbCtrlMask + vbAltMask)) Then
        m_bKeyDown(GT_QUOTES_VOLA) = True
    End If
End Sub

Private Sub fgVol_KeyUp(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_bKeyDown(GT_QUOTES_VOLA) Then
        m_bKeyDown(GT_QUOTES_VOLA) = False
        With fgVol
            m_enMenuGrid = GT_QUOTES_VOLA
            m_nMenuGridCol = .Col
            m_nMenuGridRow = .Row
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
        End With
        
        
        Select Case True
            Case KeyCode = vbKeyInsert And Shift = vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter. Hot key Alt+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxOrderNewStock_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbCtrlMask + vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter. Hot key Alt+Ctrl+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxOrderNewOption_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbShiftMask + vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter. Hot key Alt+Shift+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxTntCardNew_Click
            
            Case KeyCode = vbKeyF And Shift = vbCtrlMask _
                And m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter. Hot key Ctrl+F pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFlatCur_Click
                
            Case KeyCode = vbKeyF And Shift = vbCtrlMask + vbShiftMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter. Hot key Ctrl+Shift+F pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFlatAll_Click
                
            Case KeyCode = vbKeyF And Shift = vbCtrlMask + vbAltMask _
                And m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter. Hot key Alt+Ctrl+F pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFlatAllByCur_Click
                
            Case KeyCode = vbKeyI And Shift = vbCtrlMask + vbShiftMask _
                And m_nMenuGridCol = 0 And m_nMenuGridCol < m_nMenuGridCols
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter. Hot key Ctrl+Shift+I pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFitToImpCur_Click
            
            Case KeyCode = vbKeyI And Shift = vbCtrlMask + vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter. Hot key Ctrl+Alt+I pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFitToImpAll_Click
            
            Case (KeyCode = vbKeyInsert Or KeyCode = vbKeyC) And Shift = vbCtrlMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter. Hot key Ctrl+(Insert/C) pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxCopy_Click
        End Select
    End If
End Sub

Private Sub fgVol_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If Button = vbRightButton Then
        With fgVol
            m_enMenuGrid = GT_QUOTES_VOLA
            m_nMenuGridCol = .MouseCol
            m_nMenuGridRow = .MouseRow
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
            
            ShowPopup
        End With
    End If
End Sub

Private Sub fgVol_AfterEdit(ByVal Row As Long, ByVal Col As Long)
    On Error GoTo Err
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter AfterEdit Enter", m_frmOwner.GetCaption
    
    If m_bShutDown Then Exit Sub
    Dim sValue$, dValue#, aQuote As EtsMmQuotesLib.MmQvQuoteAtom, sKey$, nRow&, nOptType&, aPair As EtsMmQuotesLib.MmQvOptPairAtom
    Dim aOpt As EtsMmQuotesLib.MmQvOptAtom, aExp As EtsMmQuotesLib.MmQvExpAtom, dAtmVola#
    Dim aStr As EtsMmQuotesLib.MmQvStrikeAtom, aExpColl As EtsMmQuotesLib.MmQvExpColl
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim nCallMask&, nPutMask&
    
    nCallMask = GetGreeksMask(enOtCall)
    nPutMask = GetGreeksMask(enOtPut)
    
    If m_Aux.Grp.IsStockOrIndex Then
        Set aExpColl = m_Aux.Grp.Und.Exp
        With fgVol
            sValue = Trim$(.TextMatrix(Row, Col))
            If m_sCurrentOriginalText <> sValue And Col = aExpColl.Count + 2 Then
                dValue = ReadLng(sValue)
                gDBW.usp_IsManualVol_Save m_Aux.Grp.Und.ID, IIf(dValue = 0, 0, 1)
                m_Aux.Grp.Und.IsManualVol = IIf(dValue = 0, False, True)
                g_Main.Contract(m_Aux.Grp.Und.ID).Und.IsManualVol = m_Aux.Grp.Und.IsManualVol
            Else
            If m_sCurrentOriginalText <> sValue And Col > 0 And Col <= aExpColl.Count Then
                Set aExp = .ColData(Col)
                If Not aExp Is Nothing Then
                    If True Then 'Not aExp.AtmStrike Is Nothing Then
                        dValue = Abs(ReadDbl(sValue))
                        dValue = dValue / 100#
                        'dAtmVola = aExp.AtmVola
                        dAtmVola = m_Aux.Grp.Und.atmVola(aExp, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)
                        
                        If dAtmVola <> dValue Then
                            If Not g_PerformanceLog Is Nothing Then _
                                g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter Changed Volatility. " _
                                                                            & "Date=""" & aExp.ExpiryMonth & """ " _
                                                                            & "OldValue=""" & dAtmVola * 100 & """ " _
                                                                            & "NewValue=""" & dValue * 100 & """. " & GetStockInfo, m_frmOwner.GetCaption
                                                                                                                
                            Screen.MousePointer = vbHourglass
                            
                            m_Aux.Grp.Und.VolaSrv.ShiftExpiryVola aExp.Expiry, 100# * (dValue - dAtmVola)
                            
                            m_bVolaChangedNow = True
                            g_Params.FireInternalVolatilityChanged m_Aux.Grp.Und.Symbol
                            m_bVolaChangedNow = False
                            
                            For Each aStr In aExp.Strike
                                dValue = m_Aux.Grp.Und.VolaSrv.OptionVola(aExp.Expiry, aStr.Strike)
                                For Each aPair In aStr.OptPair
                                    For nOptType = enOtPut To enOtCall
                                        Set aOpt = aPair.Opt(nOptType)
                                        If aOpt.ID <> 0 Then
                                            aOpt.Vola = dValue
                                        
                                            For Each aQuote In aOpt.Quote
                                                If g_Params.UseTheoVolatility Or aQuote.CalcGreeksIVType = enMmQvCalcGreeksIVTheo Then
                                                    CalcOptionGreeks aOpt, aQuote, aExp, _
                                                        IIf(aOpt.OptType = enOtCall, nCallMask, nPutMask), GetIvMask(nOptType), False, False
                                                End If
                                            
    '                                                If aQuote.Exch.Visible Then
    '                                                    sKey = aOpt.Symbol
    '                                                    If aQuote.Exch.ID > 0 Then sKey = sKey & "." & aQuote.Exch.Code
    '
    '    '                                                nRow = fgOpt.FindRow(sKey, , IIf(nOptType = enOtCall, QOC_C_KEY, QOC_P_KEY))
    '    '                                                If nRow > 0 Then
    '    '                                                    m_AuxOut.OptionUpdateQuote nRow, nOptType, False, True, True
    '    '                                                Else
    '    '                                                    Debug.Assert False
    '    '                                                End If
    '                                                End If
                                            Next
                                        End If
                                        Set aOpt = Nothing
                                    Next
                                    Set aPair = Nothing
                                Next
                                Set aStr = Nothing
                            Next
                            
                            fgOpt.Refresh
                            m_AuxOut.VolaUpdateValues
                            
                            Screen.MousePointer = vbDefault
                        End If
                    End If
                    End If
                Else
                    Debug.Assert False
                End If
                Set aExp = Nothing
            End If
        End With
    Else
      For Each aFut In m_Aux.Grp.Und.Fut
        For Each aExp In aFut.Exp
            With fgVol
                sValue = Trim$(.TextMatrix(Row, Col))
                If m_sCurrentOriginalText <> sValue And Col > 0 And Col <= m_Aux.Grp.ExpAll.Count And _
                  (fgVol.ColData(Col).ExpiryMonth = aExp.ExpiryMonth) Then
                    'Set aExp = .ColData(Col)
                    If Not aExp Is Nothing Then
                        If True Then 'Not aExp.AtmStrike Is Nothing Then
                            dValue = Abs(ReadDbl(sValue))
                            dValue = dValue / 100#
                            dAtmVola = aFut.atmVola(aExp, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)
                            
                            If dAtmVola <> dValue Then
                                If Not g_PerformanceLog Is Nothing Then _
                                    g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter Changed Volatility. " _
                                                                                & "Date=""" & aExp.ExpiryMonth & """ " _
                                                                                & "OldValue=""" & dAtmVola * 100 & """ " _
                                                                                & "NewValue=""" & dValue * 100 & """. " & GetStockInfo, m_frmOwner.GetCaption
                                                                                                                    
                                Screen.MousePointer = vbHourglass
                                
                                m_Aux.Grp.Und.VolaSrv.ShiftExpiryVola aExp.Expiry, 100# * (dValue - dAtmVola)
                                
                                m_bVolaChangedNow = True
                                g_Params.FireInternalVolatilityChanged m_Aux.Grp.Und.Symbol
                                m_bVolaChangedNow = False
                                
                                For Each aStr In aExp.Strike
                                    dValue = m_Aux.Grp.Und.VolaSrv.OptionVola(aExp.Expiry, aStr.Strike)
                                    For Each aPair In aStr.OptPair
                                        For nOptType = enOtPut To enOtCall
                                            Set aOpt = aPair.Opt(nOptType)
                                            If aOpt.ID <> 0 Then
                                                aOpt.Vola = dValue
                                            
                                                For Each aQuote In aOpt.Quote
                                                    If g_Params.UseTheoVolatility Or aQuote.CalcGreeksIVType = enMmQvCalcGreeksIVTheo Then
                                                        CalcOptionGreeks aOpt, aQuote, aExp, _
                                                            IIf(aOpt.OptType = enOtCall, nCallMask, nPutMask), GetIvMask(nOptType)
                                                    End If
                                                
                                                    If aQuote.Exch.Visible Then
                                                        sKey = aOpt.Symbol
                                                        If aQuote.Exch.ID > 0 Then sKey = sKey & "." & aQuote.Exch.Code
                                                    
        '                                                nRow = fgOpt.FindRow(sKey, , IIf(nOptType = enOtCall, QOC_C_KEY, QOC_P_KEY))
        '                                                If nRow > 0 Then
        '                                                    m_AuxOut.OptionUpdateQuote nRow, nOptType, False, True, True
        '                                                Else
        '                                                    Debug.Assert False
        '                                                End If
                                                    End If
                                                Next
                                            End If
                                            Set aOpt = Nothing
                                        Next
                                        Set aPair = Nothing
                                    Next
                                    Set aStr = Nothing
                                Next
                                
                                m_AuxOut.VolaUpdateValues
                                
                                Screen.MousePointer = vbDefault
                            End If
                        End If
                    Else
                        Debug.Assert False
                    End If
                    Set aExp = Nothing
                End If
            End With
        Next
      Next
    End If
    

    
    Set aExpColl = Nothing
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter AfterEdit Exit", m_frmOwner.GetCaption
Exit Sub
Err:
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogFaults, "Vola Filter AfterEdit Error " & CStr(Err.Number) & " " & Err.Description, m_frmOwner.GetCaption
End Sub

Private Sub fgVol_StartEdit(ByVal Row As Long, ByVal Col As Long, Cancel As Boolean)
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter StartEdit Enter", m_frmOwner.GetCaption
    
    Cancel = True
    If m_bShutDown Then Exit Sub
    If m_bInProc Or m_bDataLoad Or m_bLastQuoteReqNow Or m_bSubscribingNow Then Exit Sub
    If IsDblClickHandled Then Exit Sub
    If fgVol.ColDataType(Col) = flexDTDate And m_Aux.Grp.ID <> 0 And Not m_Aux.RealTime Then
        
        Cancel = True
        dtCalculationDate.Move fgVol.CellLeft, fgVol.CellTop + fgVol.Top, fgVol.CellWidth, fgVol.CellHeight
        dtCalculationDate.Value = fgVol
        dtCalculationDate.Tag = fgVol
        dtCalculationDate.CalendarForeColor = fgVol.Cell(flexcpForeColor, 1, fgVol.Cols - 1)
        'dtCalculationDate.CalendarTitleForeColor = fgVol.Cell(flexcpForeColor, 1, fgVol.Cols - 1)
        
        dtCalculationDate.CalendarBackColor = fgVol.Cell(flexcpBackColor, 1, fgVol.Cols - 1)
        'dtCalculationDate.CalendarTitleBackColor = fgVol.Cell(flexcpBackColor, 1, fgVol.Cols - 1)
                
        dtCalculationDate.Visible = True
        dtCalculationDate.SetFocus
        SendKeys "{f4}"
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter call calendar. Current date: " & dtCalculationDate.Value, m_frmOwner.GetCaption
        
    Else
        Dim aExp As EtsMmQuotesLib.MmQvExpAtom
        Cancel = (m_Aux.Grp.ID = 0 Or Not m_gdVol.Col(QVC_VOLA_VAL).CanEdit)
    
        If Not Cancel Then
            Cancel = True
            Set aExp = fgVol.ColData(Col)
            If Not aExp Is Nothing Then
                If True Then 'Not aExp.AtmStrike Is Nothing Then
                    m_sCurrentOriginalText = Trim$(fgVol.TextMatrix(Row, Col))
                    Cancel = False
                End If
                Set aExp = Nothing
            End If
        End If
    End If
    
    If fgVol.ColDataType(Col) = flexDTBoolean Then Cancel = False
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Vola Filter StartEdit Exit", m_frmOwner.GetCaption

End Sub

Private Sub geOpt_BeforeSort(ByVal Col As Long, Order As Integer)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nColKey&
    
    m_AuxOut.UpdateOptionsSpread Nothing
    'm_Aux.SortColKey = nColKey
    If m_Aux.SortColOrder = flexSortGenericDescending Then
        QV.OptsSort Col, enSortAscending
       m_Aux.SortColOrder = flexSortGenericAscending
    Else
        QV.OptsSort Col, enSortDescending
       m_Aux.SortColOrder = flexSortGenericDescending
    End If

    geOpt.FinishSorting Col, m_Aux.SortColOrder
   
'    nColKey = fgOpt.ColKey(Col)
'    If nColKey = QOC_C_SERIES Or nColKey = QOC_P_SERIES Then
'        Order = flexSortCustom
'    End If
End Sub

Private Sub geOpt_AfterSort(ByVal Col As Long, Order As Integer)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nColKey&
    nColKey = fgOpt.ColKey(Col)
    
    If g_Params.QuoteOptExpirySeparation Then m_AuxOut.OptionsUpdateBackColor True '(nColKey = QOC_C_SERIES Or nColKey = QOC_P_SERIES Or nColKey = QOC_C_EXPIRY Or nColKey = QOC_P_EXPIRY)
    m_AuxOut.UpdateOptionsSpread imgInSpread

    If m_Aux.SortColKey = nColKey Then
        Order = m_Aux.SortColOrder
        m_Aux.SortColKey = -2
    End If
End Sub

Private Sub fgOpt_Compare(ByVal Row1 As Long, ByVal Row2 As Long, Cmp As Integer)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim aOpt1 As EtsMmQuotesLib.MmQvOptAtom, aOpt2 As EtsMmQuotesLib.MmQvOptAtom, aOptQuote1 As EtsMmQuotesLib.MmQvQuoteAtom, aOptQuote2 As EtsMmQuotesLib.MmQvQuoteAtom
    Dim aExp1 As EtsMmQuotesLib.MmQvExpAtom, aExp2 As EtsMmQuotesLib.MmQvExpAtom, aRowData1 As MmQvRowData, aRowData2 As MmQvRowData
    Dim sRootName1$, sRootName2$
    
    If m_Aux.SortColKey = QOC_C_SERIES Or m_Aux.SortColKey = QOC_P_SERIES Then
        Cmp = 0
        
        Set aRowData1 = QV.OptsRowData(Row1)
        Set aRowData2 = QV.OptsRowData(Row2)
        If Not aRowData1 Is Nothing And Not aRowData2 Is Nothing Then
            Set aExp1 = aRowData1.Exp
            Set aExp2 = aRowData2.Exp
                
            If Not aExp1 Is Nothing And Not aExp2 Is Nothing Then
                If m_Aux.SortColKey = QOC_C_SERIES Then
                    Set aOpt1 = aRowData1.Opt(enOtCall)
                    Set aOpt2 = aRowData2.Opt(enOtCall)
                    Set aOptQuote1 = aRowData1.OptQuote(enOtCall)
                    Set aOptQuote2 = aRowData2.OptQuote(enOtCall)
                    
                ElseIf m_Aux.SortColKey = QOC_P_SERIES Then
                    Set aOpt1 = aRowData1.Opt(enOtPut)
                    Set aOpt2 = aRowData2.Opt(enOtPut)
                    Set aOptQuote1 = aRowData1.OptQuote(enOtPut)
                    Set aOptQuote2 = aRowData2.OptQuote(enOtPut)
                End If
                
                If Not aOpt1 Is Nothing And Not aOpt2 Is Nothing _
                    And Not aOptQuote1 Is Nothing And Not aOptQuote2 Is Nothing Then
                    
                    If m_Aux.Grp.IsStockOrIndex Then
                        sRootName1 = aRowData1.OptRoot.Name
                        sRootName2 = aRowData2.OptRoot.Name
                    Else
                        sRootName1 = aRowData1.Fut.Symbol
                        sRootName2 = aRowData1.Fut.Symbol
                    End If
                    
                    If aExp1.ExpiryMonth > aExp2.ExpiryMonth Then
                        Cmp = 1
                    ElseIf aExp1.ExpiryMonth < aExp2.ExpiryMonth Then
                        Cmp = -1
                    ElseIf aOpt1.Strike > aOpt2.Strike Then
                        Cmp = 1
                    ElseIf aOpt1.Strike < aOpt2.Strike Then
                        Cmp = -1
                    ElseIf sRootName1 > sRootName2 Then
                        Cmp = 1
                    ElseIf sRootName1 < sRootName2 Then
                        Cmp = -1
                    ElseIf aOptQuote1.Exch.Code > aOptQuote2.Exch.Code Then
                        Cmp = 1
                    ElseIf aOptQuote1.Exch.Code < aOptQuote2.Exch.Code Then
                        Cmp = -1
                    End If
                    
                    If m_Aux.SortColOrder <> flexSortGenericAscending Then
                        Cmp = -Cmp
                    End If
                End If
            
                Set aOpt1 = Nothing
                Set aOpt2 = Nothing
                Set aOptQuote1 = Nothing
                Set aOptQuote2 = Nothing
            End If
        End If
        
        Set aExp1 = Nothing
        Set aExp2 = Nothing
    End If
    
    Set aRowData1 = Nothing
    Set aRowData2 = Nothing
End Sub

Private Sub StopAllActivities()

    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_bLastQuoteReqNow Then
    
        m_bLastQuoteReqNow = False
        PriceProvider.CancelLastQuote
        If m_bGroupRequest Then m_GroupPriceProvider.CancelLastGroupQuotes
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogUserAction, "Last Quotes request Cancelling.", m_frmOwner.GetCaption
        
        pbProgress.Visible = False
        lblStatus.Visible = True
        lblProcess.Visible = False
        imgStop.Visible = False
        imgStopDis.Visible = False
        lblStatus.Caption = "Last quotes request cancelling..."
        lblStatus.Refresh
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.FinishLogMmOperation m_nOperation, OPER_REQUESTQUOTE, m_frmOwner.GetCaption, QV.UndResponses, QV.OptResponses, QV.FutResponses
            
        m_AuxOut.UnderlyingUpdate False, True
        m_AuxOut.FuturesUpdate False, True, True
        m_AuxOut.OptionsUpdate False, True, True
        m_AuxOut.UnderlyingUpdateTotals
        
        UpdateTotals
        AdjustState
        
    ElseIf m_Aux.RealTime Or m_bSubscribingNow Then
    
        m_Aux.RealTime = False
        m_Aux.RealTimeConnected = False
        m_bSubscribingNow = False
        
        pbProgress.Visible = False
        lblStatus.Visible = True
        lblProcess.Visible = False
        imgStop.Visible = False
        imgStopDis.Visible = False
        lblStatus.Caption = "Quotes subscription cancelling..."
        lblStatus.Refresh
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogUserAction, "Quotes subscription Cancelling.", m_frmOwner.GetCaption
        
        PriceProvider.UnSubscribeQuote
        If g_RTQuantity > 0 Then
            g_RTQuantity = g_RTQuantity - 1
        End If
        
        If m_bGroupRequest Then m_GroupPriceProvider.UnSubscribeGroupQuotes
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.FinishLogMmOperation m_nOperation, OPER_SUBSCRIBEQUOTE, m_frmOwner.GetCaption, QV.UndResponses, QV.OptResponses, QV.FutResponses
        
        UpdateTotals
        
        AdjustState
        AdjustCaption
        
    ElseIf m_bDataLoad Then
    
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogUserAction, "Data loading Cancelling.", m_frmOwner.GetCaption
    
        m_bDataLoad = False
        AdjustState
        
    ElseIf m_bInProc Then
    
        m_bInProc = False
        AdjustState
        
    End If
End Sub


Private Sub imgStop_Click()
    On Error Resume Next
    StopAllActivities
End Sub

Private Sub SaveProfilesInfo()
    On Error GoTo EH
    If m_Aux.Grp.ID = 0 Then Exit Sub
    Dim aContract As EtsGeneralLib.EtsContractAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom

    Set aContract = g_ContractAll(m_Aux.Grp.ID)
    If Not aContract Is Nothing Then
        If m_Aux.Grp.ContractType = enCtStock Then
            gDBW.usp_Stock_Save m_Aux.Grp.Und.ID, Null, Null, Null, Null, Null, Null, Null, _
                                Null, Null, Null, Null, Null, Null, Null, Null, Null, Null, Null, 0, _
                                m_Aux.Grp.Und.UndPriceProfile.ID, m_Aux.Grp.Und.OptPriceProfile.ID
                            
            Set aContract.Und.UndPriceProfile = m_Aux.Grp.Und.UndPriceProfile
            Set aContract.Und.OptPriceProfile = m_Aux.Grp.Und.OptPriceProfile
            
        ElseIf m_Aux.Grp.ContractType = enCtIndex Then
            gDBW.usp_Index_Save m_Aux.Grp.Und.ID, Null, Null, Null, Null, Null, Null, Null, Null, Null, Null, Null, Null, 0, 0, _
                                m_Aux.Grp.Und.UndPriceProfile.ID, m_Aux.Grp.Und.OptPriceProfile.ID
                                
            Set aContract.Und.UndPriceProfile = m_Aux.Grp.Und.UndPriceProfile
            Set aContract.Und.OptPriceProfile = m_Aux.Grp.Und.OptPriceProfile
        
        ElseIf m_Aux.Grp.ContractType = enCtFuture Then 'fokiny
'            For Each aFut In m_Aux.Grp.Und.Fut
'                gDBW.usp_MmFuture_Save aFut.ID, Null, Null, Null, Null, _
'                                    aFut.UndPriceProfile.ID, aFut.OptPriceProfile.ID
'
'                Set aContract.Fut.UndPriceProfile = aFut.UndPriceProfile
'                Set aContract.Fut.OptPriceProfile = aFut.OptPriceProfile
'            Next
            
        ElseIf m_Aux.Grp.ContractType = enCtFutUnd Then
            For Each aFut In m_Aux.Grp.Und.Fut
                gDBW.usp_MmFuture_Save aFut.ID, aFut.UndPriceProfile.ID, aFut.OptPriceProfile.ID
    
                Set aContract.Und.UndPriceProfile = aFut.UndPriceProfile
                Set aContract.Und.OptPriceProfile = aFut.OptPriceProfile
            Next
        End If
        
        Set aContract = Nothing
    End If
    
    Exit Sub
EH:
    LogEvent EVENT_ERROR, "Fail to save profiles info for " & m_Aux.Grp.Symbol & ". " & Err.Source & " " & Err.Description
End Sub

Private Sub SaveDividendsInfo()
    On Error GoTo EH
    If m_Aux.Grp.ID = 0 Or (m_Aux.Grp.ContractType <> enCtStock And m_Aux.Grp.ContractType <> enCtIndex) Then Exit Sub
    Dim aGUnd As EtsGeneralLib.UndAtom
    Dim aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim aDiv As EtsGeneralLib.EtsIndexDivAtom
    
    Set aUnd = m_Aux.Grp.Und
    
    If aUnd.ID >= 0 Then
    
        If Not aUnd Is Nothing Then
            Set aDiv = aUnd.Dividend
            If Not aDiv Is Nothing Then
                Set aGUnd = g_Underlying(aUnd.ID)
                If Not aGUnd Is Nothing Then
                    Set aGUnd.Dividend = aDiv
                End If
            
            
                With aDiv
                    If .DivType = enDivCustomPeriodical Then
                        gDBW.usp_Stock_Save aUnd.ID, Null, Null, Null, Null, Null, Null, Null, _
                                        1, .DivAmtCust, .DivFreqCust, IIf(.DivDateCust > 0, .DivDateCust, Null), Null, Null, _
                                        Null, Null, Null, Null, Null, 0, Null, Null
                    
                    End If
                    
                    If .DivType = enDivMarket Then
                        gDBW.usp_Stock_Save aUnd.ID, Null, Null, Null, Null, .DivFreq, .DivAmt, IIf(.DivDate > 0, .DivDate, Null), _
                                        0, Null, Null, Null, Null, Null, _
                                        Null, Null, Null, Null, Null, 0, Null, Null
                    
                    End If
                    
                    If .DivType = enDivCustomStream Then
                        If m_Aux.Grp.ContractType = enCtStock Then
                            gDBW.usp_Stock_Save aUnd.ID, Null, Null, Null, Null, Null, Null, Null, _
                                            2, Null, Null, Null, Null, Null, _
                                            Null, Null, Null, Null, Null, 0, Null, Null
                        Else
                            gDBW.usp_Index_Save aUnd.ID, Null, Null, Null, Null, Null, Null, Null, _
                                            Null, Null, Null, Null, Null, 0, _
                                            Null, Null, Null, 2
                        End If
                    End If
                    
                    If .DivType = enDivStockBasket Then
                        gDBW.usp_Index_Save aUnd.ID, Null, Null, Null, Null, Null, Null, Null, _
                                        Null, Null, Null, Null, Null, 0, _
                                        Null, Null, Null, 3
                    End If
                    
                    If .DivType = enDivIndexYield Then
                        gDBW.usp_Index_Save aUnd.ID, Null, Null, Null, Null, Null, Null, Null, _
                                        Null, Null, Null, Null, Null, 0, _
                                        Null, Null, Null, 4
                    End If
                    
                  
                    Dim aData As MSGSTRUCTLib.UnderlyingUpdate
                    Set aData = New MSGSTRUCTLib.UnderlyingUpdate
                    
                    aData.DivAmt = .DivAmt
                    aData.DivAmtCust = .DivAmtCust
                    aData.DivDate = .DivDate
                    aData.DivDateCust = .DivDateCust
                    aData.DivFreq = .DivFreq
                    aData.DivFreqCust = .DivFreqCust
                    aData.DivType = .DivType
                    
                    aData.UndID = aUnd.ID
                    aData.UpdStatus = enUndDividendUpdate
                    
                    g_TradeChannel.PubUnderlyingUpdate aData
                  
                End With
            
            End If 'Not aDiv  Is Nothing
        End If
    End If
    Set aGUnd = Nothing
    Exit Sub
EH:
    LogEvent EVENT_ERROR, "Fail to save dividends info for " & m_Aux.Grp.Und.Symbol & ". " & Err.Source & " " & Err.Description
    Set aGUnd = Nothing
End Sub

Private Sub fgDiv_AfterEdit(ByVal Row As Long, ByVal Col As Long)
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter AfterEdit Enter", m_frmOwner.GetCaption
    
    If m_bShutDown Then Exit Sub
    Dim sValue$, nValue&, dValue#, dtValue As Date, bValue As Boolean, bNeedRecalc As Boolean, bForceRecalc As Boolean
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, collUpdUnd As New EtsGeneralLib.EtsMmFilterAtomColl
    Dim lValue As Long
    Dim enDivType As EtsDivTypeEnum
    Dim aDiv As EtsGeneralLib.EtsIndexDivAtom
    Dim nOldValue As Long
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom, aExpAll As EtsMmQuotesLib.MmQvExpAtom
        
    
    With fgDiv
        bNeedRecalc = False
        bForceRecalc = False
        sValue = Trim$(.TextMatrix(Row, Col))
        If m_sCurrentOriginalText <> sValue Then
            Select Case Col
                Case QDC_TRADES ' trades filter
                    nValue = 0
                    nValue = CLng(sValue)
                    If m_Aux.TradesFilter <> nValue Then
                        m_Aux.TradesFilter = nValue
                        
                        UnderlyingUpdatePositions
                        
                        bNeedRecalc = True
                    End If
                    m_AuxOut.TradesFilterUpdate
                
                Case QDC_OPTIONS ' options filter - visible/unvisible index options
                    Screen.MousePointer = vbHourglass
                    
                    If m_Aux.OptionsFilter = 0 Then
                        m_Aux.OptionsFilter = 1
                        m_Aux.Grp.ShowIndexFutureOptions = True
                    Else
                        m_Aux.OptionsFilter = 0
                        m_Aux.Grp.ShowIndexFutureOptions = False
                    End If
                    
                    RaiseEvent OnFutChange(False)
                    RaiseEvent OnExpiriesChange(False)
                    
                    tmrSwitchFutures.Enabled = True
                    
                Case QDC_STYLE ' option style
                    nValue = -1
                    nValue = CLng(sValue)
                    If nValue = 0 Or nValue = 1 Then
                        If m_Aux.Grp.IsStockOrIndex Then
                            If m_Aux.Grp.Und.IsAmerican <> CBool(nValue) Then
                                m_Aux.Grp.Und.IsAmerican = CBool(nValue)
                                bNeedRecalc = True
                            End If
                        Else
                            For Each aFut In m_Aux.Grp.Und.Fut
                                If aFut.IsAmerican <> CBool(nValue) Then
                                    aFut.IsAmerican = CBool(nValue)
                                    bNeedRecalc = True
                                End If
                            Next
                        End If
                    End If
                    m_AuxOut.ModelUpdate
                
                Case QDC_UNDPROFILE
                    nValue = -1
                    nValue = CLng(sValue)
                    If m_Aux.Grp.Und.UndPriceProfile <> nValue Then
                        If m_Aux.Grp.IsStockOrIndex Then
                            Set m_Aux.Grp.Und.UndPriceProfile = Nothing
                            Set m_Aux.Grp.Und.UndPriceProfile = g_PriceProfile(nValue)
                        Else
                            For Each aFut In m_Aux.Grp.Und.Fut
                                Set aFut.UndPriceProfile = Nothing
                                Set aFut.UndPriceProfile = g_PriceProfile(nValue)
                            Next
                            Set m_Aux.Grp.Und.UndPriceProfile = Nothing
                            Set m_Aux.Grp.Und.UndPriceProfile = g_PriceProfile(nValue)
                        End If
                        
                        SaveProfilesInfo
                        
                        m_bFireEvent = True
                        collUpdUnd.Add(CStr(m_Aux.Grp.ID)).ID = m_Aux.Grp.ID
                        g_Params.FireUnderlyingsParamsChange collUpdUnd
                        m_bFireEvent = False
                        
                        bNeedRecalc = True
                    End If
                    m_AuxOut.ProfilesUpdate
                
                Case QDC_OPTPROFILE
                    nValue = -1
                    nValue = CLng(sValue)
                    If m_Aux.Grp.Und.UndPriceProfile <> nValue Then
                        If m_Aux.Grp.IsStockOrIndex Then
                            Set m_Aux.Grp.Und.OptPriceProfile = Nothing
                            Set m_Aux.Grp.Und.OptPriceProfile = g_PriceProfile(nValue)
                        Else
                            For Each aFut In m_Aux.Grp.Und.Fut
                                Set aFut.OptPriceProfile = Nothing
                                Set aFut.OptPriceProfile = g_PriceProfile(nValue)
                            Next
                            Set m_Aux.Grp.Und.OptPriceProfile = Nothing
                            Set m_Aux.Grp.Und.OptPriceProfile = g_PriceProfile(nValue)
                        End If
                        
                        SaveProfilesInfo
                        
                        m_bFireEvent = True
                        collUpdUnd.Add(CStr(m_Aux.Grp.ID)).ID = m_Aux.Grp.ID
                        g_Params.FireUnderlyingsParamsChange collUpdUnd
                        m_bFireEvent = False
                        
                        bNeedRecalc = True
                    End If
                    m_AuxOut.ProfilesUpdate
                
                Case QDC_DIV
                    If m_Aux.Grp.ContractType = enCtStock Or m_Aux.Grp.ContractType = enCtIndex Then
                    
                        lValue = CLng(sValue)
                        enDivType = m_Aux.Grp.Und.Dividend.DivType
                        Set aDiv = m_Aux.Grp.Und.Dividend

                        If CLng(enDivType) <> lValue Then
                        
                            If Not g_PerformanceLog Is Nothing Then _
                                g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter Changed Dividend. " _
                                                                        & "OldValue=""" & CLng(enDivType) & """ " _
                                                                        & "NewValue=""" & lValue & """. " & GetStockInfo, m_frmOwner.GetCaption
                            
                            If (enDivType = enDivMarket) And (lValue = 1) Then
                                If (aDiv.DivAmtCust = 0) Then
                                    aDiv.DivAmtCust = aDiv.DivAmt
                                End If
                                
                                If (aDiv.DivDateCust = 0) Or (aDiv.DivDateCust = CLng(Now)) Then
                                    aDiv.DivDateCust = aDiv.DivDate
                                End If
                                
                                If (aDiv.DivFreqCust = 0) Then
                                    aDiv.DivFreqCust = aDiv.DivFreq
                                End If
                            End If
                            
                            m_Aux.Grp.Und.Dividend.DivType = lValue
                            
                            If m_Aux.Grp.Und.Dividend.DivType = enDivCustomStream Then
                                LoadCustomDivs
                            End If
                           
                            SaveDividendsInfo
                            
                            Dim Data As MSGSTRUCTLib.UnderlyingUpdate
                            Set Data = New MSGSTRUCTLib.UnderlyingUpdate
                                            
                            Data.UpdStatus = enUndAggregationUpdate
                            Data.UndID = m_Aux.Grp.Und.ID
                            Data.DivType = lValue
                                            
                            g_TradeChannel.PubUnderlyingUpdate Data
                            
                            bNeedRecalc = True
                            bForceRecalc = True
                        End If
                        
                        
                    End If
                    m_AuxOut.DivsUpdate
                    mnuCtxCustomDividend.Enabled = m_Aux.Grp.ID <> 0
                    
                Case QDC_FREQ
                    If m_Aux.Grp.ContractType = enCtStock Then
                        nValue = -1
                        nValue = ReadLng(sValue)
                        If nValue = 0 Or nValue = 1 Or nValue = 2 Or nValue = 4 Or nValue = 12 Then
                            Set aDiv = m_Aux.Grp.Und.Dividend
                            enDivType = m_Aux.Grp.Und.Dividend.DivType
                            
                            If (enDivType = enDivMarket And aDiv.DivFreq <> nValue) _
                                Or (enDivType = enDivCustomPeriodical And aDiv.DivFreqCust <> nValue) Then
                                
                                If Not g_PerformanceLog Is Nothing Then _
                                    g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter Changed Dividends Frequency. " _
                                                                        & "OldValue=""" & IIf(enDivType = enDivMarket, aDiv.DivFreq, aDiv.DivFreqCust) & """ " _
                                                                        & "NewValue=""" & nValue & """. " & GetStockInfo, m_frmOwner.GetCaption

                                If aDiv.DivType = enDivCustomPeriodical Then
                                    aDiv.DivFreqCust = nValue
                                End If
                                 
                                If (aDiv.DivType = enDivMarket) And (aDiv.DivFreq <> nValue) Then
                                    aDiv.DivAmtCust = aDiv.DivAmt
                                    aDiv.DivDateCust = aDiv.DivDate
                                    aDiv.DivFreqCust = nValue
                                    
                                    aDiv.DivType = enDivCustomPeriodical
                                End If
                                
                            End If
                                
                            SaveDividendsInfo
                                                        
                            bNeedRecalc = True
                        
                        End If
                    End If
                    m_AuxOut.DivsUpdate
                    
                Case QDC_DATE
                    If m_Aux.Grp.ContractType = enCtStock Then
                        dtValue = 0#
                        dtValue = ReadDate(sValue)
                        If dtValue > 0# Then
                            Set aDiv = m_Aux.Grp.Und.Dividend
                            enDivType = m_Aux.Grp.Und.Dividend.DivType
                        
                            If enDivType = enDivMarket And aDiv.DivDate <> dtValue _
                                Or enDivType = enDivCustomPeriodical And aDiv.DivDateCust <> dtValue Then
                                
                                aDiv.DivDateCust = dtValue
                                If enDivType = enDivMarket Then
                                    aDiv.DivFreqCust = aDiv.DivFreq
                                    aDiv.DivAmtCust = aDiv.DivAmt
                                    aDiv.DivType = enDivCustomPeriodical
                                End If
                                
                            End If
                        
                        SaveDividendsInfo
                        bNeedRecalc = True
                            
                        End If
                    End If
                    m_AuxOut.DivsUpdate
                
                Case QDC_AMT
                    If m_Aux.Grp.ContractType = enCtStock Then
                        dValue = 0#
                        dValue = ReadDbl(sValue)
                        If dValue > 0# Then
                            Set aDiv = m_Aux.Grp.Und.Dividend
                            enDivType = m_Aux.Grp.Und.Dividend.DivType
                        
                            If enDivType = enDivMarket And aDiv.DivAmt <> dValue _
                                Or enDivType = enDivCustomPeriodical And aDiv.DivAmtCust <> dValue Then
                                
                                aDiv.DivAmtCust = dValue
                                If enDivType = enDivMarket Then
                                    aDiv.DivFreqCust = aDiv.DivFreq
                                    aDiv.DivDateCust = aDiv.DivDate
                                    enDivType = enDivCustomPeriodical
                                End If
                            End If
                            
                            SaveDividendsInfo
                            bNeedRecalc = True
                        End If
                    End If
                    m_AuxOut.DivsUpdate
                        
                Case Else ' rates
                    If Col > QDC_RATE Then
                        Set aExp = .ColData(Col)
                        If Not aExp Is Nothing Then
                            dValue = 0#
                            dValue = ReadDbl(sValue)
                            dValue = dValue / 100#
                            If dValue > 0# Then
                                If Not m_Aux.Grp.UseCustRates And aExp.Rate <> dValue _
                                    Or m_Aux.Grp.UseCustRates And aExp.RateCust <> dValue Then
                                    
                                    If Not g_PerformanceLog Is Nothing Then _
                                        g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter Changed Rate. " _
                                                                        & "Date=""" & aExp.ExpiryMonth & """ " _
                                                                        & "OldValue=""" & IIf(m_Aux.Grp.UseCustRates, aExp.RateCust, aExp.Rate) * 100 & """ " _
                                                                        & "NewValue=""" & dValue * 100 & """. " & GetStockInfo, m_frmOwner.GetCaption
                                    
                                    m_Aux.Grp.UseCustRates = True
                                                                        
                                    aExp.RateCust = dValue
                                    If Not m_Aux.Grp.IsStockOrIndex Then
                                        For Each aFut In m_Aux.Grp.Und.Fut
                                                For Each aExpAll In aFut.Exp
                                                    If aExpAll.ExpiryMonth = aExp.ExpiryMonth Then
                                                        aExp.RootNames = aExpAll.RootNames
                                                        aExpAll.Rate = dValue
                                                        aExpAll.RateCust = dValue
                                                    End If
                                                Next
                                        Next
                                    End If
                                    
                                    Dim aExpLoop As EtsMmQuotesLib.MmQvExpAtom
                                    Dim aExpColl As EtsMmQuotesLib.MmQvExpColl
                                    Dim strSerach As String
                                    strSerach = fgDiv.TextMatrix(0, Col)
                                    Dim strTmp1 As String
                                    Dim aExpGlobal As EtsMmQuotesLib.MmQvExpAtom
                                    
    '                                If m_Aux.Grp.IsStockOrIndex Then
                                        Set aExpColl = m_Aux.Grp.Und.Exp
    '                                   m_Aux.Grp.ExpAll.Clear
                                        For Each aExpLoop In aExpColl
                                             Set aExpGlobal = m_Aux.Grp.ExpAll(aExpLoop.ExpiryMonth)
                                             If Not aExpGlobal Is Nothing Then aExpGlobal.RateCust = aExpLoop.RateCust
    '                                        strTmp1 = Format$(aExpLoop.ExpiryMonth, "MMM YY")
    '                                        If strTmp1 = strSerach Then
    '                                            aExpLoop.RateCust = dValue
    '                                        End If
    '                                        aExpLoop.Rate = aExpLoop.RateCust
    '                                        m_Aux.Grp.ExpAll.Add aExpLoop.ExpiryMonth, aExpLoop
                                        Next
'                                    Else
'                                        For Each aFut In m_Aux.Grp.Und.Fut
'        '                                   m_Aux.Grp.ExpAll.Clear
'                                            For Each aExpLoop In m_Aux.Grp.ExpAll
'                                                 Set aExpGlobal = m_Aux.Grp.ExpAll(aExpLoop.ExpiryMonth)
'                                                 If Not aExpGlobal Is Nothing Then aExpGlobal.RateCust = aExpLoop.RateCust
'        '                                        strTmp1 = Format$(aExpLoop.ExpiryMonth, "MMM YY")
'        '                                        If strTmp1 = strSerach Then
'        '                                            aExpLoop.RateCust = dValue
'        '                                        End If
'        '                                        aExpLoop.Rate = aExpLoop.RateCust
'        '                                        m_Aux.Grp.ExpAll.Add aExpLoop.ExpiryMonth, aExpLoop
'                                            Next
'                                        Next
'                                    End If
                                    

                                    
                                    bNeedRecalc = True
                                    bForceRecalc = True
                                End If
                            End If
                            Set aExp = Nothing
                        End If
                    Else
                        bValue = (sValue <> "0")
                        If m_Aux.Grp.UseCustRates <> bValue Then
                            m_Aux.Grp.UseCustRates = bValue
                            bNeedRecalc = True
                        End If
                    End If
                    m_AuxOut.RatesUpdate
            End Select
            
            If bNeedRecalc Then
                Recalculate False, , bForceRecalc
                .AutoSize Col, Col
            End If
        End If
    End With
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter AfterEdit Exit", m_frmOwner.GetCaption

End Sub

Private Sub fgDiv_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If Button = vbRightButton Then
        With fgDiv
            m_enMenuGrid = GT_QUOTES_DIVIDENDS
            m_nMenuGridCol = .MouseCol
            m_nMenuGridRow = .MouseRow
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
            
            ShowPopup
        End With
    End If
End Sub

Private Sub fgDiv_StartEdit(ByVal Row As Long, ByVal Col As Long, Cancel As Boolean)
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter StartEdit Enter", m_frmOwner.GetCaption
    
   
    Dim nKey&
    Cancel = True
    If m_bInProc Or m_bDataLoad Or m_bLastQuoteReqNow Or m_bSubscribingNow Then Exit Sub
    If IsDblClickHandled Then Exit Sub
    
    nKey = IIf(Col > QDC_RATE, QDC_RATE_VAL, Col)
    Cancel = (m_Aux.Grp.ID = 0 Or Not m_gdDiv.Col(nKey).CanEdit)
    
    If Not Cancel Then
        If nKey = QDC_RATE_VAL Then
            Dim aExp As EtsMmQuotesLib.MmQvExpAtom
            Set aExp = fgDiv.ColData(Col)
            Cancel = aExp Is Nothing
            Set aExp = Nothing
        End If
        If Not Cancel Then m_sCurrentOriginalText = Trim$(fgDiv.TextMatrix(Row, Col))
    End If
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend Filter StartEdit Exit", m_frmOwner.GetCaption

End Sub

Private Sub fgOpt_AfterEdit(ByVal Row As Long, ByVal Col As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nKey&, sValue$, dValue#, aQuote As EtsMmQuotesLib.MmQvQuoteAtom, sKey$, nRow&
    Dim aRowData As MmQvRowData, aOpt As EtsMmQuotesLib.MmQvOptAtom, nOptType&
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, aStr As EtsMmQuotesLib.MmQvStrikeAtom
    Dim enCalcIV As EtsMmQuotesLib.MmQvIvCalcEnum, nMask&, aPair As EtsMmQuotesLib.MmQvOptPairAtom
    
    With fgOpt
        sValue = Trim$(.TextMatrix(Row, Col))
        If m_sCurrentOriginalText <> sValue Then
            nKey = .ColKey(Col)
            If Err.Number = 0 Then
                Set aRowData = QV.OptsRowData(Row)
                
                If Not aRowData Is Nothing Then
                    Set aExp = aRowData.Exp
                    Debug.Assert Not aExp Is Nothing
                    
                    Select Case nKey
                        Case QOC_C_BID, QOC_C_ASK, QOC_C_VOLA, QOC_C_LAST
                            nOptType = enOtCall
                            
                        Case QOC_P_BID, QOC_P_ASK, QOC_P_VOLA, QOC_P_LAST
                            nOptType = enOtPut
                        
                    End Select
                    
                    Set aOpt = aRowData.Opt(nOptType)
                    Set aQuote = aRowData.OptQuote(nOptType)
                    Set aStr = aRowData.Strike
                                   
                    If Not aOpt Is Nothing And Not aQuote Is Nothing And Not aExp Is Nothing And Not aStr Is Nothing Then
                        dValue = Abs(ReadDbl(sValue))
                        
                        If nKey <> QOC_C_VOLA And nKey <> QOC_P_VOLA Then
                            
                            enCalcIV = enMmQvCalcIvNone
                            nMask = GM_NONE
                            
                            Select Case nKey
                                Case QOC_C_BID, QOC_P_BID
                                    If aQuote.IsDirty Then
                                        If Not g_PerformanceLog Is Nothing Then _
                                            g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter Changed " & IIf(nKey = QOC_C_BID, "Call", "Put") & " Bid. " _
                                                                                        & "OldValue=""" & m_sCurrentOriginalText & """ " _
                                                                                        & "NewValue=""" & dValue & """. " & GetOptionInfo, m_frmOwner.GetCaption
                                    
'                                        If aQuote.PriceBid >= 0# Then aQuote.PriceBidTick = dValue - aQuote.PriceBid
'                                        aQuote.PriceBid = dValue
                                        enCalcIV = GetIvMask(nOptType)
                                        If Not g_Params.UseTheoVolatility Then nMask = GetGreeksMask(nOptType)
                                    End If
                                    
                                Case QOC_C_ASK, QOC_P_ASK
                                    If aQuote.IsDirty Then
                                        If Not g_PerformanceLog Is Nothing Then _
                                            g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter Changed " & IIf(nKey = QOC_C_ASK, "Call", "Put") & " Ask. " _
                                                                                        & "OldValue=""" & m_sCurrentOriginalText & """ " _
                                                                                        & "NewValue=""" & dValue & """. " & GetOptionInfo, m_frmOwner.GetCaption
                                    
'                                        If aQuote.PriceAsk >= 0# Then aQuote.PriceAskTick = dValue - aQuote.PriceAsk
'                                        aQuote.PriceAsk = dValue
                                        enCalcIV = GetIvMask(nOptType)
                                        If Not g_Params.UseTheoVolatility Then nMask = GetGreeksMask(nOptType)
                                    End If
                                Case QOC_C_LAST, QOC_P_LAST
                                    If aQuote.IsDirty Then
                                        If Not g_PerformanceLog Is Nothing Then _
                                            g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter Changed ", " Last. " _
                                                                                        & "OldValue=""" & m_sCurrentOriginalText _
                                                                                        & "NewValue=""" & dValue & """. " & GetOptionInfo, m_frmOwner.GetCaption
                                        enCalcIV = GetIvMask(enOtCall)
                                        If Not g_Params.UseTheoVolatility Then nMask = GetGreeksMask(nOptType)
                                    End If
                            End Select
                            
                            If enCalcIV <> enMmQvCalcIvNone Or nMask <> GM_NONE Or aQuote.CalcGreeksIVType = enMmQvCalcGreeksIVTheo Then
                                CalcOptionGreeks aOpt, aQuote, aExp, nMask, enCalcIV, False
                                '  m_AuxOut.OptionUpdateQuote Row, nOptType, False, True, True
                                
                                CalculateUnderlyingOptions False, , False
                                m_AuxOut.UnderlyingUpdateTotals
                                UpdateTotals
                            End If
                            
                        Else ' QOC_C_VOLA, QOC_P_VOLA
                            dValue = dValue / 100#
'                            If aOpt.Vola <> dValue Then
                            If True Then
                                If Not g_PerformanceLog Is Nothing Then _
                                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter Changed " & IIf(nKey = QOC_C_VOLA, "Call", "Put") & " Volatility. " _
                                                                                & "OldValue=""" & aOpt.Vola * 100 & """ " _
                                                                                & "NewValue=""" & dValue * 100 & """. " & GetOptionInfo, m_frmOwner.GetCaption
                            
                                m_Aux.Grp.Und.VolaSrv.OptionVola(aOpt.Expiry, aOpt.Strike) = dValue
                                
                                m_bVolaChangedNow = True
                                g_Params.FireInternalVolatilityChanged m_Aux.Grp.Und.Symbol
                                m_bVolaChangedNow = False
                                
                                If g_Params.UseTheoVolatility Then nMask = GetGreeksMask(nOptType)
                            
                                dValue = m_Aux.Grp.Und.VolaSrv.OptionVola(aExp.Expiry, aStr.Strike)
                                For Each aPair In aStr.OptPair
                                    For nOptType = enOtPut To enOtCall
                                        
                                        Set aOpt = aPair.Opt(nOptType)
                                        If aOpt.ID <> 0 Then
                                            aOpt.Vola = dValue
                                            
                                            For Each aQuote In aOpt.Quote
                                                
                                                If nMask <> GM_NONE Or aQuote.CalcGreeksIVType = enMmQvCalcGreeksIVTheo Then
                                                    CalcOptionGreeks aOpt, aQuote, aExp, nMask, GetIvMask(nOptType), , False
                                                End If
                                                
                                                sKey = aOpt.Symbol
                                                If aQuote.Exch.ID > 0 Then sKey = sKey & "." & aQuote.Exch.Code
                                                
'                                                nRow = .FindRow(sKey, , IIf(nOptType = enOtCall, QOC_C_KEY, QOC_P_KEY))
'                                                If nRow > 0 Then
'                                                    If Not .RowHidden(nRow) Then m_AuxOut.OptionUpdateQuote nRow, nOptType, False, True, True
'                                                Else
'                                                    Debug.Assert False
'                                                End If
                                                
                                            Next
                                        End If
                                        Set aOpt = Nothing
                                        
                                    Next
                                Next
                                
                               If Abs(aOpt.Strike - m_Aux.Grp.Und.AtmStrike(g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule, False)) <= DBL_EPSILON Then
                                        m_AuxOut.VolaUpdateValues False
                               End If
                                
                                If nMask <> GM_NONE Then
                                    CalculateUnderlyingOptions False, , False
                                    m_AuxOut.UnderlyingUpdateTotals
                                    UpdateTotals
                                    fgOpt.Refresh
                                End If
                            End If
                        End If
                    End If
                    
                Else
                    Debug.Assert False
                End If
                
                Set aExp = Nothing
                Set aOpt = Nothing
                Set aQuote = Nothing
                Set aStr = Nothing
                Set aRowData = Nothing
            End If
        End If
    End With
End Sub

Private Sub fgOpt_AfterMoveColumn(ByVal Col As Long, Position As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nIdx&, i&, nOldPos&, nNewPos&
    If Col = Position Then Exit Sub
    
    nOldPos = Col - QOC_C_SYMBOL
    nNewPos = Position - QOC_C_SYMBOL
    nIdx = m_gdOpt.Idx(nOldPos)
    If nOldPos > nNewPos Then
        For i = nOldPos To nNewPos Step -1
            If i > nNewPos Then
                m_gdOpt.Idx(i) = m_gdOpt.Idx(i - 1)
            End If
        Next
        m_gdOpt.Idx(nNewPos) = nIdx
    Else
        For i = nOldPos To nNewPos
            If i < nNewPos Then
                m_gdOpt.Idx(i) = m_gdOpt.Idx(i + 1)
            End If
        Next
        m_gdOpt.Idx(nNewPos) = nIdx
    End If
End Sub

Private Sub fgOpt_BeforeMoveColumn(ByVal Col As Long, Position As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nOldIdx&, nNewIdx&
    
    nOldIdx = fgOpt.ColKey(Col)
    nNewIdx = fgOpt.ColKey(Position)
    
    If nOldIdx = QOC_NONE Or nNewIdx = QOC_NONE Then
        Position = Col
    ElseIf Not m_gdOpt.Col(nOldIdx).CanChangeOrder Or Not m_gdOpt.Col(nNewIdx).CanChangeOrder Then
        Position = Col
    End If
End Sub

Private Sub fgOpt_DblClick()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_bDataLoad Or m_bLastQuoteReqNow Or m_bSubscribingNow Then Exit Sub
    With fgOpt
        m_enMenuGrid = GT_QUOTES_OPTIONS
        m_nMenuGridCol = .MouseCol
        m_nMenuGridRow = .MouseRow
        m_nMenuGridCols = .Cols
        m_nMenuGridRows = .Rows
        
        HandleGridDblClick True
    End With
End Sub

Private Sub fgOpt_KeyDown(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If IsHotKeyGridCommonOrTradeOrderCard(KeyCode, Shift) _
            Or (KeyCode = vbKeyF And (Shift = vbCtrlMask _
                                    Or Shift = vbCtrlMask + vbShiftMask _
                                    Or Shift = vbCtrlMask + vbAltMask)) _
            Or (KeyCode = vbKeyI And (Shift = vbCtrlMask + vbShiftMask _
                                    Or Shift = vbCtrlMask + vbAltMask)) _
            Or (KeyCode = vbKeyZ And Shift = vbCtrlMask) _
            Or (KeyCode = vbKeyX And Shift = vbCtrlMask) Then
        
        m_bKeyDown(GT_QUOTES_OPTIONS) = True
    End If
    
End Sub

Private Sub fgOpt_KeyUp(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_bKeyDown(GT_QUOTES_OPTIONS) Then
        m_bKeyDown(GT_QUOTES_OPTIONS) = False
        With fgOpt
            m_enMenuGrid = GT_QUOTES_OPTIONS
            m_nMenuGridCol = .Col
            m_nMenuGridRow = .Row
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
        End With
        
        Select Case True
            Case KeyCode = vbKeyInsert And Shift = 0
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxTradeNew_Click
                
            Case KeyCode = vbKeyInsert And Shift = vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Alt+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxOrderNewStock_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbCtrlMask + vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Alt+Ctrl+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxOrderNewOption_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbShiftMask + vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Shift+Alt+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxTntCardNew_Click
            
            Case KeyCode = vbKeyF And Shift = vbCtrlMask _
                And m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Ctrl+F pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFlatCur_Click
                
            Case KeyCode = vbKeyF And Shift = vbCtrlMask + vbShiftMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Ctrl+Shift+F pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFlatAll_Click
                
            Case KeyCode = vbKeyF And Shift = vbCtrlMask + vbAltMask _
                And m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Ctrl+Alt+F pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFlatAllByCur_Click
                
            Case KeyCode = vbKeyI And Shift = vbCtrlMask + vbShiftMask _
                And m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Ctrl+Shift+I pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFitToImpCur_Click
            
            Case KeyCode = vbKeyI And Shift = vbCtrlMask + vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Ctrl+Alt+I pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFitToImpAll_Click
            
            Case KeyCode = vbKeyG And Shift = vbCtrlMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Ctrl+G pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxAutosizeGrid_Click
                
            Case KeyCode = vbKeyA And Shift = vbCtrlMask _
                And m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Ctrl+A pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxAutosizeCol_Click
                
            Case (KeyCode = vbKeyC) And Shift = vbCtrlMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Ctrl+(Insert/C) pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxCopy_Click
                
            Case KeyCode = vbKeyZ And Shift = vbCtrlMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Ctrl+Z pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxAddToMarketDepthView_Click
                
            Case KeyCode = vbKeyX And Shift = vbCtrlMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option Filter. Hot key Ctrl+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxShowMarketDepthView_Click
        End Select
    End If
End Sub

Private Sub fgOpt_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    On Error Resume Next
       
    
    If m_bShutDown Then Exit Sub
    
    If Button = vbRightButton Then
        With fgOpt
            m_enMenuGrid = GT_QUOTES_OPTIONS
            m_nMenuGridCol = .MouseCol
            m_nMenuGridRow = .MouseRow
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
            .Row = .MouseRow
            .Col = .MouseCol
            
            If m_nMenuGridRow > 0 And m_nMenuGridRow < m_nMenuGridRows And m_nMenuGridCol > 1 And m_nMenuGridCol < m_nMenuGridCols Then
                .Row = m_nMenuGridRow
            End If
            
            ShowPopup
        End With
    End If
    
End Sub

Private Sub UpdateMenu()
    On Error Resume Next
    
    'And Not m_bInProc
    mnuCtxRealTime.Enabled = m_Aux.Grp.ID <> 0 _
                                And Not m_bLastQuoteReqNow And Not m_bSubscribingNow And Not m_bDataLoad And Not m_bInitializing
                                
'    If Not g_PerformanceLog Is Nothing Then _
'        g_PerformanceLog.LogMmInfo enLogUserAction, "ID " & Str(m_Aux.Grp.ID) & _
'                                                    " InProc: " & Str(m_bInProc) & _
'                                                    " LastQuote: " & Str(m_bLastQuoteReqNow) & _
'                                                    " Subs: " & Str(m_bSubscribingNow) & _
'                                                    " DtaLoad: " & Str(m_bDataLoad) & _
'                                                    " Init: " & Str(m_bInitializing), m_frmOwner.GetCaption
    
    Debug.Print "ID " & Str(m_Aux.Grp.ID) & _
                " InProc: " & Str(m_bInProc) & _
                " LastQuote: " & Str(m_bLastQuoteReqNow) & _
                " Subs: " & Str(m_bSubscribingNow) & _
                " DtaLoad: " & Str(m_bDataLoad) & _
                " Init: " & Str(m_bInitializing)
                        
    mnuCtxRealTime.Checked = m_Aux.RealTime
    mnuCtxRefresh.Enabled = mnuCtxRealTime.Enabled And Not m_Aux.RealTime
    mnuCtxRefreshPrices.Enabled = mnuCtxRefresh.Enabled
    mnuCtxDefOptSort.Enabled = m_Aux.Grp.ID <> 0 And Not m_bInProc
End Sub

Private Sub ShowPopup()
    On Error Resume Next
    Dim sValue$, aRowData As MmQvRowData: Set aRowData = Nothing
    Dim bEnabled As Boolean: bEnabled = False
    Dim nExpCount&
    Dim bEnableCustomDivs As Boolean
    Dim sValExpiryMonth$
    Dim enColum As EtsMmQuotesLib.MmQvOptColumnEnum
    Dim nIdx As Integer
    
    If m_nMenuGridCol < 0 Or m_nMenuGridRow < 0 Then Exit Sub

    'mnuCtxTradeNew                                 "New Trade..."
    'mnuCtxPositionTransfer                         "Position Transfer..."
    'mnuCtxOrderNewStock                            "New Stock Order..."
    'mnuCtxOrderNewOption                           "New Option Order..."
    'mnuCtxTradeExercise                            "Exercise Trades..."
    'mnuCtxTradeExpiry                              "Expiry Trades..."
    'mnuCtxVolaFlat                                 "Flat Vola"
    'mnuCtxVolaFlatCur                              "This Expiry"
    'mnuCtxVolaFlatAll                              "All Expiries"
    'mnuCtxVolaFlatAllByCur                         "All Expiries By This"
    'mnuCtxVolaFitToImp                             "Fit Vola To Implied"
    'mnuCtxVolaFitToImpCur                          "This Expiry"
    'mnuCtxVolaFitToImpAll                          "All Expiries"
    'mnuCtxDefOptSort                               "Default Options Sorting"
    'mnuCtxRealTime                                 "Real Time Mode"
    'mnuCtxRefresh                                  "Refresh"
    'mnuCtxCopy                                     "Copy Grid"
    'mnuCtxPrint                                    "Print Grid..."
    'mnuCtxHideCol                                  "Hide Column"
    'mnuCtxAutosizeCol                              "Autosize Column"
    'mnuCtxAutosizeGrid                             "Autosize Grid"
    'mnuCtxGridLayout                               "Grid Layout..."

    mnuCtxVolaFlatCur.Caption = "This Expiry by ATM" & vbTab & "Ctrl+F"
    mnuCtxVolaFlatAllByCur.Caption = "All Expiries by This ATM" & vbTab & "Ctrl+Alt+F"
    mnuCtxVolaFlatCur.Enabled = False
    mnuCtxVolaFlatAll.Enabled = False
    mnuCtxVolaFlatAllByCur.Enabled = False
    mnuCtxVolaFlat.Enabled = False
    mnuCtxCopy.Enabled = Not m_bInProc
    mnuCtxTradeExercise.Enabled = False
    mnuCtxTradeExpiry.Enabled = False
    
    mnuCtxUseManualPrice.Enabled = False
    mnuCtxUseManualPrice.Checked = False
    
    mnuCtxOrderNewStock.Visible = g_Params.OrdersVisible
    mnuCtxOrderNewOption.Visible = g_Params.OrdersVisible
    mnuCtxOrderNewStock.Enabled = Not m_bInProc And g_Params.OrdersEnabled
    mnuCtxOrderNewOption.Enabled = Not m_bInProc And g_Params.OrdersEnabled
    
    
'    mnuCtxOrderNewStock.Enabled = Not m_bInProc And g_Params.EnableOrders
'    mnuCtxOrderNewOption.Enabled = Not m_bInProc And g_Params.EnableOrders
    mnuCtxTntCardNew.Enabled = Not m_bInProc
    bEnableCustomDivs = False
 
    If (Not m_Aux.Grp.Und.Dividend Is Nothing) Then
        If (m_Aux.Grp.Und.Dividend.DivType = enDivCustomStream Or m_Aux.Grp.Und.Dividend.DivType = enDivStockBasket) Then
            mnuCtxCustomDividend.Enabled = True
        Else
            mnuCtxCustomDividend.Enabled = False
        End If
    End If
    
    
    mnuCtxVolaFitToImpCur.Caption = "This Expiry" & vbTab & "Ctrl+Shift+I"
    mnuCtxVolaFitToImpAll.Caption = "All Expiries" & vbTab & "Ctrl+Alt+I"
    mnuCtxVolaFitToImp.Enabled = False
    mnuCtxVolaFitToImpCur.Enabled = False
    mnuCtxVolaFitToImpAll.Enabled = False

    If m_Aux.Grp.IsStockOrIndex Then
        nExpCount = m_Aux.Grp.Und.Exp.Count
    Else
        nExpCount = m_Aux.Grp.ExpAll.Count
    End If
    mnuCtxClearSpread.Enabled = False
    mnuCtxAddToSpread.Enabled = False
    mnuCtxViewSpread.Enabled = False
    
    
    enColum = fgOpt.ColKey(m_nMenuGridCol)
    If enColum < QOC_P_SYMBOL Then
        mnuCtxAddToMarketDepthView.Enabled = True
    ElseIf enColum <= QOC_P_UPDATE_TIME Then
        mnuCtxAddToMarketDepthView.Enabled = True
    Else
        mnuCtxAddToMarketDepthView.Enabled = False
    End If
        

    Select Case m_enMenuGrid
        Case GT_QUOTES_UNDERLYING
            If m_nMenuGridRow > 0 Then Set aRowData = fgUnd.RowData(m_nMenuGridRow)
            
            If Not aRowData Is Nothing Then
                If m_Aux.Grp.IsStockOrIndex Then
                    If Not aRowData.Und Is Nothing Then
                        bEnabled = aRowData.Und.ID <> USD_ID
                    Else
                        bEnabled = True
                    End If
                Else
                    bEnabled = True
                End If
            End If
            
            mnuCtxTradeNew.Enabled = (m_Aux.Grp.ID <> 0 And m_Aux.Grp.Und.IsTraderContract And m_nMenuGridRow > 0 And m_nMenuGridCol < m_nMenuGridCols _
                                        And bEnabled)
            mnuCtxPositionTransfer.Enabled = mnuCtxTradeNew.Enabled
            
            mnuCtxHideCol.Enabled = (m_nMenuGridCol > 1 And m_nMenuGridCol < m_nMenuGridCols)
            mnuCtxAutosizeCol.Enabled = (m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols)
            mnuCtxAutosizeGrid.Enabled = True
            
            mnuCtxVolaFlatAll.Enabled = m_Aux.Grp.ID <> 0 And Not m_bInProc And Not m_bLastQuoteReqNow And nExpCount > 0
            mnuCtxVolaFlat.Enabled = mnuCtxVolaFlatAll.Enabled
            
            mnuCtxVolaFitToImpAll.Enabled = mnuCtxVolaFlatAll.Enabled
            mnuCtxVolaFitToImp.Enabled = mnuCtxVolaFitToImpAll.Enabled
            
            mnuCtxClearSpread.Enabled = (m_Aux.Grp.Spread.Count > 0)
            mnuCtxViewSpread.Enabled = mnuCtxClearSpread.Enabled
            mnuCtxAddToSpread.Enabled = (m_Aux.Grp.ContractType <> enCtFutUnd And m_Aux.Grp.ID <> 0 And m_nMenuGridRow > 0 And m_nMenuGridCol < m_nMenuGridCols _
                And (IsUndSpreadColumn(m_nMenuGridCol - 1)) And bEnabled)
                

            nIdx = fgUnd.ColKey(m_nMenuGridCol)
            
            If nIdx = QUC_INDEXCALCPRICE And Not aRowData.Und Is Nothing Then
                mnuCtxUseManualPrice.Enabled = aRowData.Und.ActiveFuture Is Nothing And _
                                               aRowData.Und.ID > 0 And _
                                               Not (m_Aux.RealTime Or m_bSubscribingNow)
                                               
                mnuCtxUseManualPrice.Checked = aRowData.Und.UseManualActivePrice
            End If
            
            If nIdx = QUC_ACTIVEFUTUREPRICE And Not aRowData.Und Is Nothing Then
                mnuCtxUseManualPrice.Enabled = Not aRowData.Und.ActiveFuture Is Nothing And _
                                               aRowData.Und.ID > 0 And _
                                               Not (m_Aux.RealTime Or m_bSubscribingNow)
                                                               
                If Not m_Aux.Grp.Und.ActiveFuture Is Nothing Then
                    mnuCtxUseManualPrice.Checked = aRowData.Und.ActiveFuture.IsUseManualActivePrice
                End If
            End If
                
            
            PopupMenu mnuCtx, , , , mnuCtxTradeNew
        
        Case GT_QUOTES_FUTURES
            mnuCtxTradeNew.Enabled = (m_Aux.Grp.ID <> 0 And m_Aux.Grp.Und.IsTraderContract And m_nMenuGridRow > 0 And m_nMenuGridCol < m_nMenuGridCols)
            mnuCtxHideCol.Enabled = (m_nMenuGridCol > 1 And m_nMenuGridCol < m_nMenuGridCols And m_gdOpt.Idx(1) <> QOF_NONE)
            mnuCtxAutosizeCol.Enabled = (m_nMenuGridCol > 1 And m_nMenuGridCol < m_nMenuGridCols)
            mnuCtxAutosizeGrid.Enabled = True
            mnuCtxPositionTransfer.Enabled = mnuCtxTradeNew.Enabled
            
            If m_nMenuGridRow > 0 Then Set aRowData = fgFut.RowData(m_nMenuGridRow)
            
            If Not m_bInProc And Not m_bLastQuoteReqNow _
                And m_Aux.Grp.ID <> 0 And m_nMenuGridRow > 0 And m_nMenuGridCol < m_nMenuGridCols Then
            End If
            
            mnuCtxClearSpread.Enabled = (m_Aux.Grp.Spread.Count > 0)
            mnuCtxViewSpread.Enabled = mnuCtxClearSpread.Enabled
            mnuCtxAddToSpread.Enabled = (m_Aux.Grp.ID <> 0 And m_nMenuGridRow > 0 And m_nMenuGridCol < m_nMenuGridCols) And IsFutSpreadColumn(m_nMenuGridCol - 1)
            
            nIdx = fgFut.ColKey(m_nMenuGridCol)
            
            If nIdx = QOF_ACTIVEPRICE Then
                If Not m_Aux.Grp.Und.ActiveFuture Is Nothing Then
                    If m_Aux.Grp.Und.ActiveFuture.ID = aRowData.Fut.ID Then
                        mnuCtxUseManualPrice.Enabled = True
                    End If
                Else
                    mnuCtxUseManualPrice.Enabled = True
                End If
                
                mnuCtxUseManualPrice.Checked = aRowData.Fut.IsUseManualActivePrice
            End If
            
            PopupMenu mnuCtx, , , , mnuCtxTradeNew
        Case GT_QUOTES_OPTIONS
            mnuCtxTradeNew.Enabled = (m_Aux.Grp.ID <> 0 And m_Aux.Grp.Und.IsTraderContract And m_nMenuGridRow > 0 And m_nMenuGridCol < m_nMenuGridCols)
            mnuCtxHideCol.Enabled = (m_nMenuGridCol > 1 And m_nMenuGridCol < m_nMenuGridCols And m_gdOpt.Idx(1) <> QOC_NONE)
            mnuCtxAutosizeCol.Enabled = (m_nMenuGridCol > 1 And m_nMenuGridCol < m_nMenuGridCols)
            mnuCtxAutosizeGrid.Enabled = True
            mnuCtxPositionTransfer.Enabled = mnuCtxTradeNew.Enabled
            
            If m_nMenuGridRow > 0 Then Set aRowData = QV.OptsRowData(m_nMenuGridRow)
            
            If Not m_bInProc And Not m_bLastQuoteReqNow _
                And m_Aux.Grp.ID <> 0 And m_nMenuGridRow > 0 And m_nMenuGridCol < m_nMenuGridCols Then
                
                Dim nColIdx&, aExp As EtsMmQuotesLib.MmQvExpAtom, aOpt As EtsMmQuotesLib.MmQvOptAtom
                
                nColIdx = fgOpt.ColKey(m_nMenuGridCol)
                If nColIdx >= QOC_C_SYMBOL And nColIdx <= QOC_LAST_COLUMN Then
                    Set aExp = aRowData.Exp
                    
                    If Not aExp Is Nothing Then
                        sValue = Format$(aExp.Expiry, "MMM YY")
                        sValExpiryMonth = Format$(aExp.ExpiryMonth, "MMM YY")
                        
                        mnuCtxVolaFlatCur.Caption = "By " & sValExpiryMonth & " ATM" & vbTab & "Ctrl+F"
                        mnuCtxVolaFlatAllByCur.Caption = "All Expiries by " & sValExpiryMonth & " ATM" & vbTab & "Ctrl+Alt+F"
                        mnuCtxVolaFlat.Enabled = True
                        mnuCtxVolaFlatCur.Enabled = True
                        mnuCtxVolaFlatAll.Enabled = True
                        mnuCtxVolaFlatAllByCur.Enabled = True
                        
                        mnuCtxVolaFitToImpCur.Caption = sValExpiryMonth & vbTab & "Ctrl+Shift+I"
                        mnuCtxVolaFitToImp.Enabled = True
                        mnuCtxVolaFitToImpCur.Enabled = True
                        mnuCtxVolaFitToImpAll.Enabled = True
                        
                        If nColIdx >= QOC_C_SYMBOL And nColIdx <= QOC_C_UPDATE_TIME _
                            Or nColIdx >= QOC_P_SYMBOL And nColIdx <= QOC_P_UPDATE_TIME Then
                            
                            Set aOpt = aRowData.Opt(IIf(nColIdx >= QOC_P_SYMBOL, enOtPut, enOtCall))
    
                            If Not aOpt Is Nothing Then
                                
                                mnuCtxTradeExercise.Enabled = (aOpt.Qty > BAD_LONG_VALUE)
                                mnuCtxTradeExpiry.Enabled = mnuCtxTradeExercise.Enabled
                                
                                Set aOpt = Nothing
                            End If
                        End If
                    End If
                    
                    Set aExp = Nothing
                End If
            End If
            
            mnuCtxClearSpread.Enabled = (m_Aux.Grp.Spread.Count > 0)
            mnuCtxViewSpread.Enabled = mnuCtxClearSpread.Enabled
            mnuCtxAddToSpread.Enabled = (m_Aux.Grp.ID <> 0 And m_nMenuGridRow > 0 And m_nMenuGridCol < m_nMenuGridCols _
                And IsOptSpreadColumn(m_nMenuGridCol - 2))
            
            
            PopupMenu mnuCtx, , , , mnuCtxTradeNew
        
        Case GT_QUOTES_DIVIDENDS
            mnuCtxTradeNew.Enabled = False
            mnuCtxHideCol.Enabled = False
            mnuCtxAutosizeCol.Enabled = False
            mnuCtxAutosizeGrid.Enabled = False
            mnuCtxPositionTransfer.Enabled = False
            
            PopupMenu mnuCtx
        
        Case GT_QUOTES_VOLA
            mnuCtxTradeNew.Enabled = False
            mnuCtxHideCol.Enabled = False
            mnuCtxAutosizeCol.Enabled = False
            mnuCtxAutosizeGrid.Enabled = False
            mnuCtxPositionTransfer.Enabled = False
            
            If Not m_bInProc And Not m_bLastQuoteReqNow _
                And m_Aux.Grp.ID <> 0 And m_nMenuGridCol > 0 And m_nMenuGridCol <= nExpCount Then
                
                sValue = fgVol.TextMatrix(0, m_nMenuGridCol)
                mnuCtxVolaFlatCur.Caption = "By " & sValue & " ATM" & vbTab & "Ctrl+F"
                mnuCtxVolaFlatAllByCur.Caption = "All Expiries by " & sValue & " ATM" & vbTab & "Ctrl+Alt+F"
                mnuCtxVolaFlat.Enabled = True
                mnuCtxVolaFlatCur.Enabled = True
                mnuCtxVolaFlatAll.Enabled = True
                mnuCtxVolaFlatAllByCur.Enabled = True
            
                mnuCtxVolaFitToImpCur.Caption = sValue & vbTab & "Ctrl+Shift+I"
                mnuCtxVolaFitToImp.Enabled = True
                mnuCtxVolaFitToImpCur.Enabled = True
                mnuCtxVolaFitToImpAll.Enabled = True
            End If
            
            PopupMenu mnuCtx
        
    End Select
    
    
    Set aRowData = Nothing
End Sub

Private Sub ResetMenuData()
    On Error Resume Next
    m_enMenuGrid = -1
    m_nMenuGridCol = -1
    m_nMenuGridRow = -1
    m_nMenuGridCols = 0
    m_nMenuGridRows = 0
End Sub

Private Sub fgOpt_StartEdit(ByVal Row As Long, ByVal Col As Long, Cancel As Boolean)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim aRowData As MmQvRowData
    Dim nKey&
    Cancel = True
    
    If m_bInProc Or m_bDataLoad Or m_bLastQuoteReqNow Or m_bSubscribingNow Then Exit Sub
    If IsDblClickHandled Then Exit Sub
    
    If m_Aux.Grp.ID <> 0 Then
        With fgOpt
            nKey = .ColKey(Col)
            If Err.Number = 0 Then
                If m_Aux.RealTime And nKey <> QOC_C_VOLA And _
                    nKey <> QOC_P_VOLA Then Exit Sub
                Cancel = Not m_gdOpt.Col(nKey).CanEdit
                If Not Cancel Then
                    Set aRowData = QV.OptsRowData(Row)
                    If nKey < QOC_P_SYMBOL Then
                        Cancel = (aRowData.Opt(enOtCall) Is Nothing Or aRowData.OptQuote(enOtCall) Is Nothing)
                    Else
                        Cancel = (aRowData.Opt(enOtPut) Is Nothing Or aRowData.OptQuote(enOtPut) Is Nothing)
                    End If
                    
                    Set aRowData = Nothing
                End If
                
                If Not Cancel Then
                    Cancel = (Not m_Aux.Grp.Und.IsTraderContract And (nKey = QOC_C_VOLA Or nKey = QOC_P_VOLA))
                End If
            End If
            
            If Not Cancel Then
                m_sCurrentOriginalText = Trim$(.TextMatrix(Row, Col))
            End If
        End With
    End If
End Sub

Public Sub UpdateManualPrices(ByRef ctrID() As Long, ByRef Price() As Double, ByRef isManual() As Boolean)

    Dim aRowData As MmQvRowData

    Set aRowData = fgUnd.RowData(1)

    Dim l, i As Long

    i = 1

    For Each l In ctrID

        If l = QV.Grp.Und.ID Then
            QV.Grp.Und.ActivePrice = Price(i)
            QV.Grp.Und.UseManualActivePrice = isManual(i)
            If QV.Grp.Und.UseManualActivePrice = False Then
                QV.EtsMain.Contract(QV.Grp.Und.ID).Und.manualActivePrice = 0
            End If
         End If

        i = i + 1

    Next
    
    Me.Refresh
    
End Sub

Private Sub fgUnd_AfterEdit(ByVal Row As Long, ByVal Col As Long)
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter AfterEdit Enter", m_frmOwner.GetCaption
    
    If m_bShutDown Then Exit Sub
    Dim nKey&, sValue$, dValue#, aQuote As EtsMmQuotesLib.MmQvQuoteAtom, bNeedRecalc As Boolean
    Dim aRowData As MmQvRowData, bManualEdit As Boolean
    Dim UnderlyingPriceHelp As Double
    Dim enPriceStatusMid As EtsGeneralLib.EtsReplacePriceStatusEnum
    Dim m_nOldGrpID As Long
    
    
    With fgUnd
        nKey = .ColKey(Col)
        If Err.Number = 0 Then
            sValue = Trim$(.TextMatrix(Row, Col))
            
            If m_sCurrentOriginalText <> sValue Then
                bNeedRecalc = False
                bManualEdit = False
                If nKey = QUC_SYMBOL Then
                
                    MarketDepthOptColl.Clear
                    RaiseEvent OnScreenRefresh
                        
                    Debug.Assert Row = m_nUndMainRow
                    sValue = UCase$(sValue)
                    If Not g_PerformanceLog Is Nothing Then _
                        g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter AfterEdit New Symbol: " & sValue, m_frmOwner.GetCaption
                    
                    m_nOldGrpID = m_nNewGrpID
                    m_nNewGrpID = 0
                    If g_Contract.BySortKey(sValue).ContractType = enCtStock Or _
                        g_Contract.BySortKey(sValue).ContractType = enCtIndex Or _
                        g_Contract.BySortKey(sValue).ContractType = enCtFutUnd Then
                        m_nNewGrpID = g_Contract.BySortKey(sValue).ID
                        
                        'as by default
                        m_Aux.OptionsFilter = 0
                        m_Aux.Grp.ShowIndexFutureOptions = False
                        m_Aux.IndexOptionsComboVisible = False
                    Else
                        If g_Contract.BySortKey(sValue).ContractType = enCtFuture Then
                            m_Aux.OptionsFilter = 1
                            m_Aux.Grp.ShowIndexFutureOptions = True
                            m_Aux.IndexOptionsComboVisible = True
                        Else
                            'as by default
                            m_Aux.OptionsFilter = 0
                            m_Aux.Grp.ShowIndexFutureOptions = False
                            m_Aux.IndexOptionsComboVisible = False
                        End If
                        m_nNewGrpID = g_Contract.BySortKey(sValue).Und.ID
                    End If
                    If m_nNewGrpID = 0 Then
                        If gCmn.MyMsgBox(m_frmOwner, "There is no market structure for symbol '" & sValue & "'." & vbCrLf & _
                                            "Update market structure for this symbol?", vbQuestion Or vbYesNo) = vbYes Then

                            Dim frmMS As New frmMarketStructure
                            
                            m_nNewGrpID = frmMS.Execute(sValue, m_frmOwner)
                            If m_nNewGrpID <> 0 Then
                                DoEvents
                                
                                Screen.MousePointer = vbHourglass
                                m_bUndListReloadNow = True
                                
                                g_Params.MakeUnderlingComboLists
                                InitUndList
                                g_Params.FireNewUnderlyingAdded m_nNewGrpID
                                
                                m_bUndListReloadNow = False
                                Screen.MousePointer = vbDefault
                            Else
                                m_nNewGrpID = m_nOldGrpID
                            End If
                        Else
                            m_nNewGrpID = m_nOldGrpID
                        End If
                    End If
                    
                    If m_nNewGrpID <> 0 Then
                        .TextMatrix(Row, Col) = sValue
                        
                        QV.VisibleUndExch.Clear
                         If Not g_Params.QuoteUndExchAll Then
                            QV.VisibleUndExch.Add(Trim$(Str$(g_Params.QuoteDefUndExchID))).ID = g_Params.QuoteDefUndExchID
                        End If
                        
                        QV.VisibleOptExch.Clear
                        If Not g_Params.QuoteOptExchAll Then
                            QV.VisibleOptExch.Add(Trim$(Str$(g_Params.QuoteDefOptExchID))).ID = g_Params.QuoteDefOptExchID
                        End If
                        
                        QV.ResetInitFlags
                        tmrShow.Enabled = True
                    Else
                        .TextMatrix(Row, Col) = m_Aux.Grp.Symbol
                    End If
                Else
                    Set aRowData = .RowData(Row)
                    Debug.Assert Not aRowData Is Nothing
                    Set aQuote = aRowData.UndQuote
                    
                    If Not aRowData Is Nothing And Not aQuote Is Nothing Then
                        Select Case nKey
                            Case QUC_BID
                                If aQuote.PriceBid >= 0# Then aQuote.PriceBidTick = 0
                                m_AuxOut.UnderlyingUpdateQuoteColors Row, aQuote
                                
                                dValue = Abs(ReadDbl(sValue))
                                If aQuote.PriceBid <> dValue Then
                                    If Not g_PerformanceLog Is Nothing Then _
                                        g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter Changed Bid. " _
                                                                                    & "OldValue=""" & aQuote.PriceBid & """ " _
                                                                                    & "NewValue=""" & dValue & """. " & GetStockInfo, m_frmOwner.GetCaption
                                    aQuote.PriceBid = dValue
                                    
                                    .TextMatrix(Row, Col) = aQuote.PriceBid
                                    
                                    bNeedRecalc = (aQuote.Exch.ID = aRowData.Und.PrimaryExchangeID)
                                End If
                                .TextMatrix(Row, Col) = Abs(dValue)
                            Case QUC_ASK
                                If aQuote.PriceAsk >= 0# Then aQuote.PriceAskTick = 0
                                m_AuxOut.UnderlyingUpdateQuoteColors Row, aQuote
                                
                                dValue = Abs(ReadDbl(sValue))
                                If aQuote.PriceAsk <> dValue Then
                                    If Not g_PerformanceLog Is Nothing Then _
                                        g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter Changed Ask. " _
                                                                                    & "OldValue=""" & aQuote.PriceAsk & """ " _
                                                                                    & "NewValue=""" & dValue & """. " & GetStockInfo, m_frmOwner.GetCaption
                                
                                    aQuote.PriceAsk = dValue
                                    .TextMatrix(Row, Col) = aQuote.PriceAsk
                                    bNeedRecalc = (aQuote.Exch.ID = aRowData.Und.PrimaryExchangeID)
                                End If
                                
                            Case QUC_LAST
                                dValue = Abs(ReadDbl(sValue))
                                If aQuote.PriceLast <> dValue Then
                                    If Not g_PerformanceLog Is Nothing Then _
                                        g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter Changed Last. " _
                                                                                    & "OldValue=""" & aQuote.PriceLast & """ " _
                                                                                    & "NewValue=""" & dValue & """. " & GetStockInfo, m_frmOwner.GetCaption
                                
                                    aQuote.PriceLast = dValue
                                    aQuote.PriceBid = dValue
                                    aQuote.PriceAsk = dValue
                                    
                                    .TextMatrix(Row, QUC_LAST) = aQuote.PriceLast
                                    .TextMatrix(Row, QUC_ASK) = aQuote.PriceLast
                                    .TextMatrix(Row, QUC_BID) = aQuote.PriceLast
                              
                                    bManualEdit = True
                                    bNeedRecalc = (aQuote.Exch.ID = aRowData.Und.PrimaryExchangeID)
                                End If
                            Case QUC_BASIS
                                If Not QV.Grp.Und.ActiveFuture Is Nothing Then
                                    UpdateBasis QV.Grp.Und.ActiveFuture, CDbl(sValue)
                                    bNeedRecalc = True
                                 End If
                            Case QUC_ACTIVEFUTURE
                                    UpdateActiveFutures CLng(sValue)
                                    bNeedRecalc = True
                            Case QUC_ACTIVEFUTUREPRICE
                                If Not aRowData.Und.ActiveFuture Is Nothing Then
                                    dValue = ReadDbl(sValue)
                                    If dValue <> 0 Then
                                        
                                        UpdateActiveFuturesPrice dValue
                                        bNeedRecalc = True
                                        bManualEdit = True
                                        gDBW.usp_MmManualPrice_Save aRowData.Und.ActiveFuture.ID, aRowData.Und.ActiveFuture.ActivePrice
                                    End If
                                End If
                            Case QUC_INDEXCALCPRICE
                                If aRowData.Und.ActiveFuture Is Nothing Then
                                
                                    aRowData.Und.ActivePrice = CDbl(sValue)
                                    aRowData.Und.UseManualActivePrice = True
                                    
                                    gDBW.usp_MmManualPrice_Save aRowData.Und.ID, aRowData.Und.ActivePrice
                                    
                                    SaveManualActivePrice aRowData.Und.ID, aRowData.Und.ActivePrice
                                    
                                    bNeedRecalc = True
                                    bManualEdit = True
                                 End If
                            Case QUC_CLOSE
                                m_AuxOut.UnderlyingUpdateQuoteColors Row, aQuote
                                dValue = Abs(ReadDbl(sValue))
                                If aQuote.PriceClose <> dValue Then
                                    If Not g_PerformanceLog Is Nothing Then _
                                        g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter Changed Close. " _
                                                                                    & "OldValue=""" & aQuote.PriceClose & """ " _
                                                                                    & "NewValue=""" & dValue & """. " & GetStockInfo, m_frmOwner.GetCaption
                                
                                    
                                    aQuote.PriceClose = dValue
                                    .TextMatrix(Row, Col) = aQuote.PriceClose
                                    bManualEdit = True
                                    bNeedRecalc = (aQuote.Exch.ID = aRowData.Und.PrimaryExchangeID)
                                    
                                    '''''''''''''''''''''''''''''''''''''''''''''''''''''''
                                    ''''''''''save and pub underlying close price''''''''''
                                    '''''''''''''''''''''''''''''''''''''''''''''''''''''''
                                    If Not aRowData.Und Is Nothing Then
                                        If SavePriceClose(aRowData.Und.UndType, aRowData.Und.ID, aRowData.UndQuote.PriceClose) Then
                                            TradeChannel.PriceCloseForPub aRowData.Und.UndType, 0, aRowData.Und.ID, aRowData.UndQuote.PriceClose, BAD_DOUBLE_VALUE
                                        End If
                                    End If
                                    '''''''''''''''''''''''''''''''''''''''''''''''''''''''
                                    If (Not g_ContractAll(aRowData.Und.ID).Und Is Nothing) Then
                                        g_ContractAll(aRowData.Und.ID).Und.PriceClose = dValue
                                    End If
                                    '''''''''''''''''''''''''''''''''''''''''''''''''''''''
                                End If
                            Case QUC_COEFF
                                Dim aGlUnd As EtsGeneralLib.UndAtom
                                Set aGlUnd = g_UnderlyingAll(m_Aux.Grp.Und.ID)
                            
                                If Not aGlUnd Is Nothing Then
                                    If Not aGlUnd.IsHead And Not aGlUnd.HeadComponent Is Nothing Then
                                        dValue = Abs(.ValueMatrix(Row, Col))
                                        If aGlUnd.Coeff <> dValue And dValue > 0 Then
                                            .TextMatrix(Row, Col) = dValue
                                            
                                            If (Not aRowData.Und Is Nothing) Then
                                                aRowData.Und.Coeff = dValue
                                                bNeedRecalc = True
                                            End If
                                            
                                            aGlUnd.Coeff = dValue
                                            gDBW.usp_AssetGroupElement_Save aGlUnd.HeadComponent.ID, aGlUnd.ID, IIf(aGlUnd.PriceByHead, 1, 0), aGlUnd.Coeff
                                            
                                            Dim Data As MSGSTRUCTLib.UnderlyingUpdate
                                            Set Data = New MSGSTRUCTLib.UnderlyingUpdate
                                            
                                            Data.UpdStatus = enUndAggregationUpdate
                                            Data.UndID = aGlUnd.ID
                                            Data.Coeff = aGlUnd.Coeff
                                            Data.UseHead = aGlUnd.PriceByHead
                                            
                                            g_TradeChannel.PubUnderlyingUpdate Data
                                            
                                        End If
                                    End If
                                End If
                            
                        End Select
                        
                        If bNeedRecalc Then
                            If m_Aux.Grp.IsStockOrIndex Then
                                                              
                                aRowData.Und.VolaSrv.UnderlyingPrice = aRowData.Und.UndPriceProfile.GetUndPriceMid( _
                                                                       aQuote.PriceBid, aQuote.PriceAsk, aQuote.PriceLast, _
                                                                       g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule, enPriceStatusMid, False)
                            aRowData.UndQuote.ReplacePriceStatus = enPriceStatusMid
                            End If
                            Recalculate False, bManualEdit
                        End If
                        
                        Set aQuote = Nothing
                    End If
                    
                    Set aRowData = Nothing
                End If
            End If
        End If
    End With
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter AfterEdit Exit", m_frmOwner.GetCaption

End Sub

Private Sub fgUnd_AfterMoveColumn(ByVal Col As Long, Position As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nIdx&, i&, nOldPos&, nNewPos&
    If Col = Position Then Exit Sub
    
    nOldPos = Col - QUC_SYMBOL
    nNewPos = Position - QUC_SYMBOL
    nIdx = m_gdUnd.Idx(nOldPos)
    If nOldPos > nNewPos Then
        For i = nOldPos To nNewPos Step -1
            If i > nNewPos Then
                m_gdUnd.Idx(i) = m_gdUnd.Idx(i - 1)
            End If
        Next
        m_gdUnd.Idx(nNewPos) = nIdx
    Else
        For i = nOldPos To nNewPos
            If i < nNewPos Then
                m_gdUnd.Idx(i) = m_gdUnd.Idx(i + 1)
            End If
        Next
        m_gdUnd.Idx(nNewPos) = nIdx
    End If
End Sub

Private Sub fgUnd_BeforeEdit(ByVal Row As Long, ByVal Col As Long, Cancel As Boolean)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nIdx&
    
    With fgUnd
        nIdx = .ColKey(Col)
        If Row <> m_nUndMainRow Or nIdx <> QUC_SYMBOL Then
            .ComboList = ""
        Else
            .ComboList = m_sUndComboList
            .EditMaxLength = 20
        End If
        
    End With
    
    If Not QV.Grp.Und.ActiveFuture Is Nothing And nIdx = QUC_INDEXCALCPRICE Then
        Cancel = True
    End If
    
End Sub

Private Sub fgUnd_BeforeMoveColumn(ByVal Col As Long, Position As Long)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nOldIdx&, nNewIdx&
    
    nOldIdx = fgUnd.ColKey(Col)
    nNewIdx = fgUnd.ColKey(Position)
    
    If nOldIdx = QUC_NONE Or nNewIdx = QUC_NONE Then
        Position = Col
    ElseIf Not m_gdUnd.Col(nOldIdx).CanChangeOrder Or Not m_gdUnd.Col(nNewIdx).CanChangeOrder Then
        Position = Col
    End If
End Sub

Private Sub fgUnd_DblClick()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    With fgUnd
        m_enMenuGrid = GT_QUOTES_UNDERLYING
        m_nMenuGridCol = .MouseCol
        m_nMenuGridRow = .MouseRow
        m_nMenuGridCols = .Cols
        m_nMenuGridRows = .Rows
        
        HandleGridDblClick (m_nMenuGridRow <> 1 Or m_nMenuGridRow = 1 And QUC_SYMBOL <> fgUnd.ColKey(m_nMenuGridCol))
    End With
End Sub

Private Sub fgUnd_KeyDown(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If IsHotKeyGridCommonOrTradeOrderCard(KeyCode, Shift) _
            Or (KeyCode = vbKeyF And Shift = vbCtrlMask + vbShiftMask) _
            Or (KeyCode = vbKeyI And Shift = vbCtrlMask + vbAltMask) Then
        
        m_bKeyDown(GT_QUOTES_UNDERLYING) = True
    End If
End Sub

Private Sub fgUnd_KeyUp(KeyCode As Integer, Shift As Integer)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_bKeyDown(GT_QUOTES_UNDERLYING) Then
        m_bKeyDown(GT_QUOTES_UNDERLYING) = False
        With fgUnd
            m_enMenuGrid = GT_QUOTES_UNDERLYING
            m_nMenuGridCol = .Col
            m_nMenuGridRow = .Row
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
        End With
        
        Select Case True
            Case KeyCode = vbKeyInsert And Shift = 0
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter. Hot key Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxTradeNew_Click
                
            Case KeyCode = vbKeyInsert And Shift = vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter. Hot key Alt+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxOrderNewStock_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbCtrlMask + vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter. Hot key Ctrl+Alt+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxOrderNewOption_Click
            
            Case KeyCode = vbKeyInsert And Shift = vbShiftMask + vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter. Hot key Shift+Alt+Insert pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxTntCardNew_Click
            
            Case KeyCode = vbKeyF And Shift = vbCtrlMask + vbShiftMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter. Hot key Ctrl+Shift+F pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFlatAll_Click
                
            Case KeyCode = vbKeyI And Shift = vbCtrlMask + vbAltMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter. Hot key Ctrl+Alt+I pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxVolaFitToImpAll_Click
            
            Case KeyCode = vbKeyG And Shift = vbCtrlMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter. Hot key Ctrl+G pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxAutosizeGrid_Click
                
            Case KeyCode = vbKeyA And Shift = vbCtrlMask _
                And m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter. Hot key Ctrl+A pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxAutosizeCol_Click
                
            Case (KeyCode = vbKeyInsert Or KeyCode = vbKeyC) And Shift = vbCtrlMask
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter. Hot key Ctrl+(Insert/C) pressed. " & GetOptionInfo, m_frmOwner.Caption
                mnuCtxCopy_Click
        End Select
    End If
End Sub

Private Sub fgUnd_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If Button = vbRightButton Then
        With fgUnd
            m_enMenuGrid = GT_QUOTES_UNDERLYING
            m_nMenuGridCol = .MouseCol
            m_nMenuGridRow = .MouseRow
            m_nMenuGridCols = .Cols
            m_nMenuGridRows = .Rows
            
            If m_nMenuGridRow > 0 And m_nMenuGridRow < m_nMenuGridRows And m_nMenuGridCol > 0 And m_nMenuGridCol < m_nMenuGridCols Then
                .Row = m_nMenuGridRow
            End If
            
            ShowPopup
        End With
    End If
End Sub

Private Sub fgUnd_StartEdit(ByVal Row As Long, ByVal Col As Long, Cancel As Boolean)
    On Error Resume Next
    Dim aRowData As EtsMmQuotesLib.MmQvRowData
    Dim aUnd As EtsMmQuotesLib.MmQvUndAtom
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter StartEdit Enter", m_frmOwner.GetCaption
    
    If m_bShutDown Then Exit Sub
    Dim nKey&
    Cancel = True
    
    If m_bInProc Or m_bDataLoad Or m_bLastQuoteReqNow Or m_bSubscribingNow Then Exit Sub
    If IsDblClickHandled Then Exit Sub
    
    With fgUnd
        nKey = .ColKey(Col)
        If Err.Number = 0 Then
            If m_Aux.Grp.ID <> 0 Then
                Cancel = Not m_gdUnd.Col(nKey).CanEdit _
                        Or (Row <> m_nUndMainRow And nKey = QUC_SYMBOL) _
                        Or (nKey <> QUC_SYMBOL And (m_Aux.RealTime Or m_bSubscribingNow))
            Else
                Cancel = Not (Row = m_nUndMainRow And nKey = QUC_SYMBOL)
            End If
        End If
        
        Set aRowData = .RowData(Row)
        Set aUnd = aRowData.Und
        
        If Not Cancel Then
            If nKey = QUC_ACTIVEFUTURE Or QUC_BASIS = nKey Then
                Cancel = (QV.Grp.ContractType = enCtStock)
                If QV.Grp.ContractType = enCtIndex Then
                    If Not QV.Grp.Und.Fut Is Nothing Then
                        Cancel = (QV.Grp.Und.Fut.Count = 0)
                    End If
                End If
                If QUC_BASIS = nKey And Not Cancel Then
                 Cancel = (QV.Grp.ContractType = enCtFutUnd)
                End If
            End If
            If nKey <> QUC_SYMBOL Then
                m_sCurrentOriginalText = Trim$(.TextMatrix(Row, Col))
            Else
                m_sCurrentOriginalText = Trim$(.Cell(flexcpTextDisplay, Row, Col))
            End If
            
            If nKey = QUC_ACTIVEFUTUREPRICE And QV.Grp.Und.ActiveFuture Is Nothing Then
                Cancel = True
            End If
            
            If (nKey = QUC_INDEXCALCPRICE And QV.Grp.Und.ActiveFuture Is Nothing And QV.Grp.Und.PriceByHead = True) Then
                Cancel = True
            End If

            If nKey = QUC_COEFF Then
                Dim aGlUnd As EtsGeneralLib.UndAtom
                Set aGlUnd = g_UnderlyingAll(aUnd.ID)
                
                Cancel = True
                            
                If Not aGlUnd Is Nothing And m_Aux.Grp.ID = aUnd.ID Then
                    If Not aGlUnd.IsHead And Not aGlUnd.HeadComponent Is Nothing Then
                        Cancel = False
                    End If
                End If
            End If

        End If
    End With
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying Filter StartEdit Exit", m_frmOwner.GetCaption

End Sub

Private Sub frmLayout_OnApply(ByVal enGridType As GridTypeEnum, gdGrid As clsGridDef)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    SetGridLayout enGridType, gdGrid
    If g_Params.QuoteOptExpirySeparation Then m_AuxOut.OptionsUpdateBackColor True
End Sub

Private Sub frmLayout_OnOK(ByVal enGridType As GridTypeEnum, gdGrid As clsGridDef)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Screen.MousePointer = vbHourglass
    SetGridLayout enGridType, gdGrid
    Screen.MousePointer = vbDefault
End Sub

Public Sub SetGridLayout(ByVal enGridType As GridTypeEnum, gdGrid As clsGridDef)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    Select Case enGridType
        Case GT_QUOTES_UNDERLYING
            gdGrid.CopyTo m_gdUnd
            
            m_Aux.GridLock(GT_QUOTES_UNDERLYING).LockRedraw
            m_Aux.FormatUndGrid
            m_Aux.FormatUndColumns
            m_AuxOut.UnderlyingUpdate True, True
            m_AuxOut.UnderlyingUpdateTotals
            m_Aux.GridLock(GT_QUOTES_UNDERLYING).UnlockRedraw
            ClearSpread
        Case GT_QUOTES_DIVIDENDS
            gdGrid.CopyTo m_gdDiv
            
            m_Aux.GridLock(GT_QUOTES_DIVIDENDS).LockRedraw
            m_Aux.FormatDivColumns
            m_Aux.GridLock(GT_QUOTES_DIVIDENDS).UnlockRedraw
    
        Case GT_QUOTES_VOLA
            gdGrid.CopyTo m_gdVol
            
            m_Aux.GridLock(GT_QUOTES_VOLA).LockRedraw
            m_Aux.FormatVolColumns
            m_Aux.GridLock(GT_QUOTES_VOLA).UnlockRedraw
    
        Case GT_QUOTES_FUTURES
            gdGrid.CopyTo m_gdFut
            
            m_Aux.GridLock(GT_QUOTES_FUTURES).LockRedraw
            
            m_Aux.FormatFutGrid
            m_Aux.FormatFutColumns
            'If mnuCtxRefresh.Enabled = False Then
                m_AuxOut.FuturesUpdate True, True, True
            'End If
                
            m_Aux.GridLock(GT_QUOTES_FUTURES).UnlockRedraw
            
        Case GT_QUOTES_OPTIONS
            Dim nCallMask&, nPutMask&, enCallIV As EtsMmQuotesLib.MmQvIvCalcEnum, enPutIV As EtsMmQuotesLib.MmQvIvCalcEnum
            nCallMask = GetGreeksMask(enOtCall)
            nPutMask = GetGreeksMask(enOtPut)
            
            enCallIV = GetIvMask(enOtCall)
            enPutIV = GetIvMask(enOtPut)
            
            gdGrid.CopyTo m_gdOpt
            
            m_Aux.GridLock(GT_QUOTES_OPTIONS).LockRedraw
            m_Aux.FormatOptGrid
            m_Aux.FormatOptColumns
            
            If g_Params.QuoteOptExpirySeparation And m_AuxOut.ExpiryColorSelection Then
                m_AuxOut.ExpiryColorSelection = False
                m_AuxOut.OptionsUpdateBackColor True
            End If
            
            If mnuCtxRefresh.Enabled _
                And (nCallMask <> GetGreeksMask(enOtCall) Or _
                    nPutMask <> GetGreeksMask(enOtPut) Or _
                    enCallIV <> GetIvMask(enOtCall) Or _
                    enPutIV <> GetIvMask(enOtPut)) Then
                
                Recalculate True
            Else
                m_AuxOut.OptionsUpdate True, True, True
            End If
            
            RefreshOptsGrid
'            ClearSpread
'            fgOpt.FlexDataSource = Nothing
'            QV.OptsColumnsOrder = m_gdOpt.IdxCopy
'            fgOpt.FlexDataSource = QV
'            fgOpt.Refresh
            
           
            m_Aux.GridLock(GT_QUOTES_OPTIONS).UnlockRedraw
            
    End Select
    
    UserControl_Resize
End Sub


Private Sub mnuCtxAddToMarketDepthView_Click()

    Dim nOptType As Long
    Dim aRowData As MmQvRowData
    Dim aOpt As MmQvOptAtom
    Dim aOptColl As New EtsMmQuotesLib.MmQvOptColl
    Dim enColum As EtsMmQuotesLib.MmQvOptColumnEnum
 
    If fgOpt.Col < 0 Or fgOpt.Row < 0 Or m_bShutDown Then Exit Sub
    nOptType = -1
    
    enColum = fgOpt.ColKey(fgOpt.Col)
    If enColum < QOC_P_SYMBOL Then
        nOptType = enOtCall
    ElseIf enColum <= QOC_P_UPDATE_TIME Then
         nOptType = enOtPut
    End If
                
    Set aRowData = QV.OptsRowData(fgOpt.Row)
    If Not aRowData Is Nothing And nOptType <> -1 Then
        If Not aRowData.Opt(nOptType) Is Nothing Then
            Set aOpt = aRowData.Opt(nOptType)
            If MarketDepthOptColl.Item(aOpt.ID) Is Nothing Then
                MarketDepthOptColl.Add aOpt.ID, aOpt
                RaiseEvent OnScreenRefreshAndShow
            End If
        End If
    End If
    
    If Not MarketDepthVisible Then
        mnuCtxShowMarketDepthView_Click
    Else
        RaiseEvent OnScreenRefreshAndShow
    End If
    
End Sub

Private Sub mnuCtxAutosizeCol_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nIdx&
    
    Screen.MousePointer = vbHourglass
    Select Case m_enMenuGrid
        Case GT_QUOTES_UNDERLYING
            With fgUnd
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying popup menu. ""RightClick -> Autosize Column"" selected. " & GetStockInfo, m_frmOwner.GetCaption
            
                m_Aux.GridLock(GT_QUOTES_UNDERLYING).LockRedraw
                If m_nMenuGridCol <> 1 Then
                    .AutoSize m_nMenuGridCol, m_nMenuGridCol
                Else
                    .AutoSize m_nMenuGridCol, m_nMenuGridCol, , 300
                End If
                
                nIdx = .ColKey(m_nMenuGridCol)
                If nIdx >= QUC_SYMBOL And nIdx <= QUC_LAST_COLUMN Then
                    m_gdUnd.Col(nIdx).Width = IIf(.ColWidth(m_nMenuGridCol) > 0, .ColWidth(m_nMenuGridCol), -1)
                End If
                
                m_Aux.GridLock(GT_QUOTES_UNDERLYING).UnlockRedraw
            End With
            
        Case GT_QUOTES_FUTURES
            With fgFut
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Future popup menu. ""RightClick -> Autosize Column"" selected. " & GetFutureInfo, m_frmOwner.GetCaption
            
                m_Aux.GridLock(GT_QUOTES_FUTURES).LockRedraw
                .AutoSize m_nMenuGridCol, m_nMenuGridCol
                
                nIdx = .ColKey(m_nMenuGridCol)
                If nIdx >= QOF_SYMBOL And nIdx <= QOF_LAST_COLUMN Then
                    m_gdFut.Col(nIdx).Width = IIf(.ColWidth(m_nMenuGridCol) > 0, .ColWidth(m_nMenuGridCol), -1)
                End If
                
                m_Aux.GridLock(GT_QUOTES_FUTURES).UnlockRedraw
            End With

        Case GT_QUOTES_OPTIONS
            With fgOpt
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option popup menu. ""RightClick -> Autosize Column"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
            
                m_Aux.GridLock(GT_QUOTES_OPTIONS).LockRedraw
                .AutoSize m_nMenuGridCol, m_nMenuGridCol
                
                nIdx = .ColKey(m_nMenuGridCol)
                If nIdx >= QOC_C_SYMBOL And nIdx <= QOC_LAST_COLUMN Then
                    m_gdOpt.Col(nIdx).Width = IIf(.ColWidth(m_nMenuGridCol) > 0, .ColWidth(m_nMenuGridCol), -1)
                End If
                
                m_Aux.GridLock(GT_QUOTES_OPTIONS).UnlockRedraw
            End With
        
    End Select
    Screen.MousePointer = vbDefault
End Sub

Private Sub mnuCtxAutosizeGrid_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim nIdx&, i&, nCount&
    
    Screen.MousePointer = vbHourglass
    Select Case m_enMenuGrid
        Case GT_QUOTES_UNDERLYING
            With fgUnd
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying popup menu. ""RightClick -> Autosize Grid"" selected. " & GetStockInfo, m_frmOwner.GetCaption
                    
                m_Aux.GridLock(GT_QUOTES_UNDERLYING).LockRedraw
                .AutoSize 1, 2, , 300
                .AutoSize 2, .Cols - 1
                
                nCount = .Cols - 1
                For i = 0 To nCount
                    nIdx = .ColKey(i)
                    If nIdx >= QUC_SYMBOL And nIdx <= QUC_LAST_COLUMN Then
                        m_gdUnd.Col(nIdx).Width = IIf(.ColWidth(i) > 0, .ColWidth(i), -1)
                    End If
                Next
                
                m_Aux.GridLock(GT_QUOTES_UNDERLYING).UnlockRedraw
            End With
            
        Case GT_QUOTES_FUTURES
            With fgFut
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Future popup menu. ""RightClick -> Autosize Grid"" selected. " & GetFutureInfo, m_frmOwner.GetCaption
                    
                m_Aux.GridLock(GT_QUOTES_FUTURES).LockRedraw
                .AutoSize 0, .Cols - 1
                
                nCount = .Cols - 1
                For i = 0 To nCount
                    nIdx = .ColKey(i)
                    If nIdx >= QOF_SYMBOL And nIdx <= QOF_LAST_COLUMN Then
                        m_gdFut.Col(nIdx).Width = IIf(.ColWidth(i) > 0, .ColWidth(i), -1)
                    End If
                Next
                
                m_Aux.GridLock(GT_QUOTES_FUTURES).UnlockRedraw
            End With

        Case GT_QUOTES_OPTIONS
            With fgOpt
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogUserAction, "Option popup menu. ""RightClick -> Autosize Grid"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
                    
                m_Aux.GridLock(GT_QUOTES_OPTIONS).LockRedraw
                .AutoSize 0, .Cols - 1
                
                nCount = .Cols - 1
                For i = 0 To nCount
                    nIdx = .ColKey(i)
                    If nIdx >= QOC_C_SYMBOL And nIdx <= QOC_LAST_COLUMN Then
                        m_gdOpt.Col(nIdx).Width = IIf(.ColWidth(i) > 0, .ColWidth(i), -1)
                    End If
                Next
                
                m_Aux.GridLock(GT_QUOTES_OPTIONS).UnlockRedraw
            End With
        
    End Select
    Screen.MousePointer = vbDefault
End Sub


Private Sub mnuCtxCopy_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_bInProc Then Exit Sub

    Screen.MousePointer = vbHourglass
    Select Case m_enMenuGrid
        Case GT_QUOTES_UNDERLYING
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying popup menu. ""RightClick -> Copy Grid"" selected. " & GetStockInfo, m_frmOwner.GetCaption
            g_ClipMgr.CopyGridToClipboard fgUnd

        Case GT_QUOTES_DIVIDENDS
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend popup menu. ""RightClick -> Copy Grid"" selected. " & GetStockInfo, m_frmOwner.GetCaption
            g_ClipMgr.CopyGridToClipboard fgDiv

        Case GT_QUOTES_VOLA
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Vola popup menu. ""RightClick -> Copy Grid"" selected. " & GetStockInfo, m_frmOwner.GetCaption
            g_ClipMgr.CopyGridToClipboard fgVol
            
        Case GT_QUOTES_FUTURES
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Future popup menu. ""RightClick -> Copy Grid"" selected. " & GetFutureInfo, m_frmOwner.GetCaption
            g_ClipMgr.CopyGridToClipboard fgFut

        Case GT_QUOTES_OPTIONS
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Option popup menu. ""RightClick -> Copy Grid"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
            g_ClipMgr.CopyGridToClipboard fgOpt

    End Select
    Screen.MousePointer = vbDefault
End Sub

Private Sub mnuCtxCustomDividend_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, IIf(m_bIsDblClick, "DblClick on Dividend Grid (custom dividends). ", "Dividend popup menu. ""RightClick -> Custom Dividends"" selected. ") & GetStockInfo, m_frmOwner.GetCaption
    'If Not g_PerformanceLog Is Nothing Then _
    '    g_PerformanceLog.LogMmInfo enLogUserAction, IIf(m_bIsDblClick, "DblClick on Dividend Grid (custom dividends). ", "Dividend popup menu. ""RightClick -> Custom Dividends"" selected. ") & GetStockInfo, m_frmOwner.GetCaption
    'If Not g_PerformanceLog Is Nothing Then _
    '    g_PerformanceLog.LogMmInfo enLogUserAction, IIf(m_bIsDblClick, "DblClick on Dividend Grid (custom dividends). ", "Dividend popup menu. ""RightClick -> Custom Dividends"" selected. ") & GetStockInfo, m_frmOwner.GetCaption
    
    If m_Aux.Grp.Und.UndType = enCtStock Or m_Aux.Grp.Und.UndType = enCtIndex Then
        Dim collUpdUnd As New EtsGeneralLib.EtsMmFilterAtomColl
        Dim aShareUnd As EtsGeneralLib.UndAtom
        Dim aCustDivs As EtsGeneralLib.EtsDivColl
        
        Dim expDate As Date
        Dim aExp As MmQvExpAtom
        expDate = Now + 365 * 5
        

        For Each aExp In m_Aux.Grp.Und.Exp
            expDate = aExp.Expiry
        Next

        m_frmCustDivs.Init m_Aux.Grp.Und.ID, m_Aux.Grp.Und.Symbol, expDate, m_Aux.Grp.Und.Dividend.DivType = enDivStockBasket, m_Aux.Grp.Und.Dividend.DivType = enDivCustomStream
        m_frmCustDivs.BasketDivs = IIf(m_Aux.Grp.Und.Dividend.DivType = enDivStockBasket, m_Aux.Grp.Und.BasketIndex.BasketDivs, Nothing)
        m_frmCustDivs.Show vbModal, Me
        If m_frmCustDivs.GotData Then
        
        
            Set aCustDivs = m_frmCustDivs.CustomDividend
            Set m_Aux.Grp.Und.Dividend.CustomDivs = aCustDivs
            
                Set aShareUnd = g_UnderlyingAll(m_Aux.Grp.Und.ID)
                If Not aShareUnd Is Nothing Then
                    
                    Dim aTmpContract As EtsGeneralLib.EtsContractAtom
                    Dim aTmpUnd As EtsGeneralLib.UndAtom
                    
                    If Not aShareUnd.Dividend Is Nothing Then
                        Set aShareUnd.Dividend.CustomDivs = aCustDivs
                    End If
                    
                    
                    Set aTmpUnd = g_Underlying(m_Aux.Grp.Und.ID)
                    
                    If Not aTmpUnd Is Nothing Then
                        If Not aTmpUnd.Dividend Is Nothing Then
                            Set aTmpUnd.Dividend.CustomDivs = aCustDivs
                        End If
                    End If
                    
                    Set aShareUnd = Nothing
                    Set aCustDivs = Nothing
                End If
            
            
            m_AuxOut.DivsUpdate
            SaveDividendsInfo
            Recalculate False
            
        End If
    End If
End Sub

Private Sub mnuCtxDefOptSort_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Default Options Sorting"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    SortOptionsByDefault
End Sub

Public Sub SortOptionsByDefault()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_Aux.Grp.ID = 0 Or m_bInProc Then Exit Sub
    
    With fgOpt
        m_Aux.GridLock(GT_QUOTES_OPTIONS).LockRedraw
        Screen.MousePointer = vbHourglass
        
        'begin 8801
        'm_Aux.SortColKey = QOC_C_SERIES
        'm_Aux.SortColOrder = flexSortGenericAscending
        
        '.Sort = flexSortCustom
        'geOpt.ShowSortImage .ColIndex(QOC_C_SERIES), 1
        
        'QV.OptsSort_Default_IndFut
        
        'If g_Params.QuoteOptExpirySeparation Then m_AuxOut.OptionsUpdateBackColor True
        
        m_Aux.SortColKey = -2
        QV.DefaultOptionsSort
        
        geOpt.RemoveSortPicture

        If g_Params.QuoteOptExpirySeparation Then m_AuxOut.OptionsUpdateBackColor True
        'end 8801
        m_Aux.GridLock(GT_QUOTES_OPTIONS).UnlockRedraw
        Screen.MousePointer = vbDefault
    End With
End Sub

Private Sub mnuCtxOtcOptionCalc_Click()
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> OTC Option Calc..."" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    OTCOptionCalcCall
End Sub

Private Sub mnuCtxShowMarketDepthView_Click()

    Dim nOptType As Long
    Dim aRowData As MmQvRowData
    Dim aOpt As MmQvOptAtom
    
    Dim mktBidDepth() As MmQvMarketDepthAtom
    Dim mktAskDepth() As MmQvMarketDepthAtom
    
    If m_bShutDown Then Exit Sub
        
    If Not MarketDepthVisible Then
        Dim frmDepth As frmMarketDepth
        Set frmDepth = New frmMarketDepth
        frmDepth.ShowContractsMarketDepth Me
        MarketDepthVisible = True
        Set frmDepth = Nothing
    Else
        RaiseEvent OnScreenRefreshAndShow
    End If
        
End Sub

Private Sub mnuCtxTradeExercise_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Exercise Trades..."" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Exercise Trades..."" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    
    If m_bInProc Or m_nMenuGridCol < 0 Or m_nMenuGridRow < 1 Or m_Aux.Grp.ID = 0 Or Not m_Aux.Grp.Und.IsTraderContract Then Exit Sub
    If m_enMenuGrid <> GT_QUOTES_OPTIONS Then Exit Sub
    
    Dim aRowData As MmQvRowData, nColIdx&, bBuy As Boolean, aOpt As EtsMmQuotesLib.MmQvOptAtom
    Dim collTrades As New clsTradeExecColl
    Dim frmExecTrades As frmExerciseTrades
    
    nColIdx = fgOpt.ColKey(m_nMenuGridCol)
    If nColIdx >= QOC_C_SYMBOL And nColIdx <= QOC_C_UPDATE_TIME _
        Or nColIdx >= QOC_P_SYMBOL And nColIdx <= QOC_P_UPDATE_TIME Then
        
        Set aRowData = QV.OptsRowData(m_nMenuGridRow)
        If Not aRowData Is Nothing Then
            Set aOpt = aRowData.Opt(IIf(nColIdx >= QOC_P_SYMBOL, enOtPut, enOtCall))
            
            If Not aOpt Is Nothing Then
                If aOpt.Qty >= BAD_LONG_VALUE Then
                    If m_Aux.Grp.IsStockOrIndex Then
'                        If m_Aux.Grp.Und.OptRoot(aOpt.RootID).Synthetic Then
'                            gCmn.MyMsgBox m_frmOwner, "Exercising trades for options with syntetic root is not supported.", vbExclamation
'                            Exit Sub
'                        End If
                        
                        TradeChannel.MakeTradesListForExec collTrades, m_Aux.Grp.Und.ID, 0, aOpt.ID
                    Else
                        TradeChannel.MakeTradesListForExec collTrades, 0, aOpt.RootID, aOpt.ID 'fokiny
                    End If
                        
                    If collTrades.Count > 0 Then
                        Set frmExecTrades = New frmExerciseTrades
                        frmExecTrades.Execute collTrades, True, m_frmOwner
                        Set frmExecTrades = Nothing
                    Else
                        gCmn.MyMsgBox m_frmOwner, "No actual/manual trades for exercise.", vbExclamation
                    End If
                End If
            End If
            Set aOpt = Nothing
            Set aRowData = Nothing
        End If
    End If
    
    ResetMenuData
End Sub

Private Sub mnuCtxTradeExpiry_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Expiry Trades..."" selected. " & GetOptionInfo, m_frmOwner.GetCaption
        
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Expiry Trades..."" selected. " & GetOptionInfo, m_frmOwner.GetCaption
        
    If m_bInProc Or m_nMenuGridCol < 0 Or m_nMenuGridRow < 1 Or m_Aux.Grp.ID = 0 Or Not m_Aux.Grp.Und.IsTraderContract Then Exit Sub
    If m_enMenuGrid <> GT_QUOTES_OPTIONS Then Exit Sub
    
    Dim aRowData As MmQvRowData, nColIdx&, bBuy As Boolean, aOpt As EtsMmQuotesLib.MmQvOptAtom
    Dim collTrades As New clsTradeExecColl
    Dim bValid As Boolean
    Dim frmExecTrades As frmExerciseTrades
    
    nColIdx = fgOpt.ColKey(m_nMenuGridCol)
    If nColIdx >= QOC_C_SYMBOL And nColIdx <= QOC_C_UPDATE_TIME _
        Or nColIdx >= QOC_P_SYMBOL And nColIdx <= QOC_P_UPDATE_TIME Then
        
        Set aRowData = QV.OptsRowData(m_nMenuGridRow)
        If Not aRowData Is Nothing Then
            Set aOpt = aRowData.Opt(IIf(nColIdx >= QOC_P_SYMBOL, enOtPut, enOtCall))
            
            If Not aOpt Is Nothing Then
                If aOpt.Qty >= BAD_LONG_VALUE Then
                    If m_Aux.Grp.IsStockOrIndex Then
                        TradeChannel.MakeTradesListForExec collTrades, m_Aux.Grp.Und.ID, 0, aOpt.ID
                    Else
                        TradeChannel.MakeTradesListForExec collTrades, 0, aOpt.RootID, aOpt.ID
                    End If
                    
                    If collTrades.Count > 0 Then
                        Set frmExecTrades = New frmExerciseTrades
                        frmExecTrades.Execute collTrades, False, m_frmOwner
                        Set frmExecTrades = Nothing
                    Else
                        gCmn.MyMsgBox m_frmOwner, "No actual/manual trades for expiry.", vbExclamation
                    End If
                End If
            End If
            Set aOpt = Nothing
            Set aRowData = Nothing
        End If
    End If
    
    ResetMenuData
End Sub
Private Function InterpolateVolas(ByRef arrVola() As VolatilitySourcesLib.ExpiryStrikeVolaData, _
                                                 ByRef findVola As VolatilitySourcesLib.ExpiryStrikeVolaData) As Double
                                                 
    Dim i&
    Dim findVolaBeforeLessStrike    As VolatilitySourcesLib.ExpiryStrikeVolaData
    Dim findVolaBeforeGreaterStrike As VolatilitySourcesLib.ExpiryStrikeVolaData
    Dim findVolaAfterLessStrike     As VolatilitySourcesLib.ExpiryStrikeVolaData
    Dim findVolaAfterGreaterStrike  As VolatilitySourcesLib.ExpiryStrikeVolaData
    
    For i = LBound(arrVola) To UBound(arrVola)
        If arrVola(i).Vola > 0# Then
            If arrVola(i).Expiry < findVola.Expiry And arrVola(i).Strike <= findVola.Strike Then
                 findVolaBeforeLessStrike = arrVola(i)
            End If
            If arrVola(i).Expiry < findVola.Expiry And arrVola(i).Strike > findVola.Strike Then
                 findVolaBeforeGreaterStrike = arrVola(i)
            End If
            
            If arrVola(i).Expiry > findVola.Expiry And arrVola(i).Strike <= findVola.Strike Then
                 findVolaAfterLessStrike = arrVola(i)
            End If
            If arrVola(i).Expiry > findVola.Expiry And arrVola(i).Strike > findVola.Strike Then
                 findVolaAfterGreaterStrike = arrVola(i)
                GoTo findAll
            End If
        End If
    Next
findAll:
Dim dVola1#, dVola2#
    dVola1 = InterpolateStrike(findVola.Strike, findVolaBeforeLessStrike, findVolaBeforeGreaterStrike)
    dVola2 = InterpolateStrike(findVola.Strike, findVolaAfterLessStrike, findVolaAfterGreaterStrike)
    
    If dVola1 > 0# And dVola2 > 0# Then
        Dim dP As Double
        Dim dN As Double
        Dim dChange As Double
        Dim dRatio As Double
                    
        dP = findVola.Expiry - findVolaBeforeLessStrike.Expiry
        dN = findVolaAfterLessStrike.Expiry - findVolaBeforeLessStrike.Expiry
                    
        dChange = dVola2 - dVola1
        dRatio = dP / dN
        InterpolateVolas = dVola1 + dChange * dRatio
        ElseIf dVola1 > 0# Then
            InterpolateVolas = dVola1
    ElseIf dVola2 > 0# Then
        InterpolateVolas = dVola2
    Else
        InterpolateVolas = BAD_DOUBLE_VALUE
    End If

End Function

Private Function InterpolateVola(ByRef arrVola() As VolatilitySourcesLib.ExpiryStrikeVolaData, _
                                                 ByRef findVola As VolatilitySourcesLib.ExpiryStrikeVolaData) As Double
                                                 
    Dim i&
    Dim findVolaLessStrike    As VolatilitySourcesLib.ExpiryStrikeVolaData
    Dim findVolaGreaterStrike As VolatilitySourcesLib.ExpiryStrikeVolaData
    
    For i = LBound(arrVola) To UBound(arrVola)
        If arrVola(i).Vola > 0# Then
            If arrVola(i).Expiry = findVola.Expiry And arrVola(i).Strike <= findVola.Strike Then
                 findVolaLessStrike = arrVola(i)
            End If
            If arrVola(i).Expiry = findVola.Expiry And arrVola(i).Strike > findVola.Strike Then
                 findVolaGreaterStrike = arrVola(i)
                 GoTo findAll
            End If
            
            If arrVola(i).Expiry > findVola.Expiry Then GoTo findAll

        End If
    Next
findAll:
Dim dVola#
    dVola = InterpolateStrike(findVola.Strike, findVolaLessStrike, findVolaGreaterStrike)
    
    If dVola > 0# Then
       InterpolateVola = dVola
    Else
        InterpolateVola = BAD_DOUBLE_VALUE
    End If

End Function

Private Function InterpolateStrike(dStrike As Double, _
                                   ByRef aVolaLess As VolatilitySourcesLib.ExpiryStrikeVolaData, _
                                   ByRef aVolaGreater As VolatilitySourcesLib.ExpiryStrikeVolaData) As Double
If aVolaLess.Strike = 0 And aVolaGreater.Strike = 0 Then
    InterpolateStrike = BAD_DOUBLE_VALUE
ElseIf aVolaLess.Strike = 0 Then
    InterpolateStrike = aVolaGreater.Vola
ElseIf aVolaGreater.Strike = 0 Then
    InterpolateStrike = aVolaLess.Vola
Else
    Dim dP As Double
    Dim dN As Double
    Dim dChange As Double
    Dim dRatio As Double
                    
    dP = dStrike - aVolaLess.Strike
    dN = aVolaGreater.Strike - aVolaLess.Strike
                    
    dChange = aVolaGreater.Vola - aVolaLess.Vola
    dRatio = dP / dN
    InterpolateStrike = aVolaLess.Vola + dChange * dRatio
End If
End Function

Private Function GetVola(ByRef arrVola() As VolatilitySourcesLib.ExpiryStrikeVolaData, Expiry As Date, Strike As Double) As Double
    Dim i&
    For i = LBound(arrVola) To UBound(arrVola)
        If arrVola(i).Strike = Strike And Expiry <= arrVola(i).Expiry Then
           GetVola = arrVola(i).Vola / 100#
           GoTo Exi
        End If
    Next
GetVola = 0#
Exi:
End Function


Private Function FitToImpiledInterpolatedMissing(ByRef arrVola() As VolatilitySourcesLib.ExpiryStrikeVolaData) As Long
    On Error GoTo Exi
    Dim nCount As Long: nCount = 0
    Dim i&
    Dim nLastGoodStrike As Long
    Dim dtLastGoodExp As Date
    Dim lastGoodVola As Double
    
    FitToImpiledInterpolatedMissing = 0
    For i = LBound(arrVola) To UBound(arrVola)
        If arrVola(i).Vola = BAD_DOUBLE_VALUE Then
           arrVola(i).Vola = InterpolateVolas(arrVola, arrVola(i))
           If arrVola(i).Vola > 0 Then
                nLastGoodStrike = arrVola(i).Strike
                dtLastGoodExp = arrVola(i).Expiry
                lastGoodVola = arrVola(i).Vola
                nCount = nCount + 1
           End If
        ElseIf arrVola(i).Vola = -1 Then
            If dtLastGoodExp = arrVola(i).Expiry Then
                arrVola(i).Vola = lastGoodVola
                nCount = nCount + 1
            Else
                arrVola(i).Vola = BAD_DOUBLE_VALUE
            End If
        Else
            nLastGoodStrike = arrVola(i).Strike
            dtLastGoodExp = arrVola(i).Expiry
            lastGoodVola = arrVola(i).Vola
            nCount = nCount + 1
        End If
    Next
Exi:
    FitToImpiledInterpolatedMissing = nCount
End Function

Private Function FitToImpFillVolasForExpiry(ByRef aExp As EtsMmQuotesLib.MmQvExpAtom, _
                                    ByRef arrVola() As VolatilitySourcesLib.ExpiryStrikeVolaData, _
                                    bSilent As Boolean) As Long
    On Error Resume Next
    Dim aStr As EtsMmQuotesLib.MmQvStrikeAtom, aPair As EtsMmQuotesLib.MmQvOptPairAtom
    Dim aQuote As EtsMmQuotesLib.MmQvQuoteAtom
    Dim aUndDefQuote As EtsMmQuotesLib.MmQvQuoteAtom, enPriceStatus As EtsGeneralLib.EtsReplacePriceStatusEnum
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim nExactCount&, dUndPrice#, div#, dIVBetter#, dAtmStrike#, nAtmIdx&, nFutureID&
    Dim nFirstIdx&, nLastIdx&, nLastGoodIdx&, nIdx&, i&
    Dim bSomeAdded   As Boolean: bSomeAdded = False
    Dim bSomeRemoved As Boolean: bSomeRemoved = False
    Dim bFlat As Boolean
    Dim nBadBidCount As Long
    Dim bOneVolaExists As Boolean
    Dim aFrm As New frmInfoMsgBox
    Dim msgStr As String
    
    nBadBidCount = 0
    bOneVolaExists = False
    FitToImpFillVolasForExpiry = 0
    If aExp.Strike.Count <= 0 Then Exit Function
    
    nExactCount = -1
    nExactCount = UBound(arrVola)
    If nExactCount > 0 Then
        ReDim Preserve arrVola(1 To nExactCount + aExp.Strike.Count)
    Else
        nExactCount = 0
        ReDim arrVola(1 To aExp.Strike.Count)
    End If
    
    nFirstIdx = nExactCount + 1
    nLastIdx = nExactCount + aExp.Strike.Count
    dUndPrice = -1#
    nFutureID = 0
    If m_Aux.Grp.IsStockOrIndex Then
        Set aUndDefQuote = m_Aux.Grp.Und.Quote(0)
        dUndPrice = m_Aux.Grp.Und.UndPriceProfile.GetUndPriceMid(aUndDefQuote.PriceBid, aUndDefQuote.PriceAsk, _
                                                        aUndDefQuote.PriceLast, g_Params.UndPriceToleranceValue, _
                                                        g_Params.PriceRoundingRule, enPriceStatus)
        Set aUndDefQuote = Nothing
        
        dAtmStrike = m_Aux.Grp.Und.AtmStrike(g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)
    End If
    
    nAtmIdx = -1
        
    ' OTM - take call if strike >= undprice, and put if strike < undprice
    nIdx = nFirstIdx - 1
    For Each aStr In aExp.Strike
        div = 0#
        dIVBetter = 0#
        Dim bAdd As Boolean
        bAdd = False
        bFlat = False
        
        For Each aPair In aStr.OptPair
            Dim dRootID As Long
            
            nFutureID = aPair.RootID
            
            If Not m_Aux.Grp.IsStockOrIndex And dUndPrice = -1 Then
                For Each aFut In m_Aux.Grp.Und.Fut
                    If aFut.ID = nFutureID Then
                        Set aUndDefQuote = aFut.Quote(0)
                        dUndPrice = aFut.UndPriceProfile.GetUndPriceMid(aUndDefQuote.PriceBid, aUndDefQuote.PriceAsk, _
                                                                    aUndDefQuote.PriceLast, g_Params.UndPriceToleranceValue, _
                                                                    g_Params.PriceRoundingRule, enPriceStatus)
                        Set aUndDefQuote = Nothing
                        dAtmStrike = aFut.AtmStrike(g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)
                        Exit For
                    End If
                Next
            End If
            
            If Not aPair.Opt(enOtCall) Is Nothing Then
                dRootID = aPair.Opt(enOtCall).RootID
            ElseIf Not aPair.Opt(enOtPut) Is Nothing Then
                dRootID = aPair.Opt(enOtPut).RootID
            End If
            If g_Params.QuoteFitToImpCurveType = enFitToImpCurveOTM And dUndPrice > 0 Then
                If aStr.Strike >= dUndPrice Then
                    Set aQuote = aPair.Opt(enOtCall).Quote(0)
                    If aQuote Is Nothing Then Set aQuote = aPair.Opt(enOtPut).Quote(0)
                Else
                    Set aQuote = aPair.Opt(enOtPut).Quote(0)
                    If aQuote Is Nothing Then Set aQuote = aPair.Opt(enOtCall).Quote(0)
                End If
            Else
                If g_Params.QuoteFitToImpCurveType <> enFitToImpCurvePuts Then
                    Set aQuote = aPair.Opt(enOtCall).Quote(0)
                    If aQuote Is Nothing Then Set aQuote = aPair.Opt(enOtPut).Quote(0)
                Else
                    Set aQuote = aPair.Opt(enOtPut).Quote(0)
                    If aQuote Is Nothing Then Set aQuote = aPair.Opt(enOtCall).Quote(0)
                End If
            End If
            
            If Not aQuote Is Nothing Then
               If m_Aux.Grp.Und.OptRoot(dRootID).IsFit Then
                    bAdd = True

                    div = aQuote.IV
                    If div > 0 Then bOneVolaExists = True
                    If div < 0 Then div = 0#
                    
                    If g_Params.QuoteFitToImpFlatNoBid And aQuote.PriceBid <= 0 Then div = 0
                    
                    If aQuote.PriceBid <= 0 Then
                        nBadBidCount = nBadBidCount + 1
                    End If
                
                    If aStr.OptPair.Count > 1 Then
                        If dIVBetter <= 0# And (aQuote.PriceBid > 0 Or aQuote.PriceAsk > 0 Or aQuote.PriceLast > 0) Then
                            dIVBetter = div
                        End If
                    Else
                        dIVBetter = div
                    End If
               Else
                If g_Params.QuoteFitToImpFlatNoBid And aQuote.PriceBid <= 0 Then bFlat = True
               End If
            Else
                Debug.Assert False
                div = 0#
            End If
                
            Set aQuote = Nothing
        Next
            nIdx = nIdx + 1
            arrVola(nIdx).Expiry = aExp.ExpiryMonth
            arrVola(nIdx).Strike = aStr.Strike
        If bAdd Then
            arrVola(nIdx).Vola = IIf(dIVBetter <= 0#, div, dIVBetter) * 100#
            bSomeAdded = True
        Else
            If Not bFlat Then
                arrVola(nIdx).Vola = BAD_DOUBLE_VALUE
            Else
                arrVola(nIdx).Vola = -1
            End If
            
                bSomeRemoved = True
        End If
        
        If dAtmStrike > aStr.Strike Then nAtmIdx = nIdx
    Next
    ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    If nBadBidCount = aExp.Strike.Count And g_Params.QuoteFitToImpFlatNoBid Then
        msgStr = "Currently there are no option bids on Quote View."
        aFrm.SetCheckBoxCaption "Use Flat Vola if No Bid"
        aFrm.SetCheckBoxChecked g_Params.QuoteFitToImpFlatNoBid
        aFrm.Init "Information", msgStr, MBM_FIT2IMP_NO_BIDS, True
        aFrm.Show vbModeless
        FitToImpFillVolasForExpiry = -2
        GoTo Ex
    End If
    ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    If bSomeAdded And bSomeRemoved Then
    ' interpolate missing
        Dim nIdxInterpolate&, nIdxFind&
        Dim dLastGoodVola#: dLastGoodVola = 0#
        
        For nIdxInterpolate = nFirstIdx To nLastIdx
            If arrVola(nIdxInterpolate).Vola = BAD_DOUBLE_VALUE Then
                Dim dStrike1#, dStrike2#
                Dim dVola1#, dVola2#
                dStrike1 = 0#
                dStrike2 = 0#

                For nIdxFind = nFirstIdx To nLastIdx
                    If arrVola(nIdxFind).Vola > 0# Then
                        If arrVola(nIdxFind).Strike < arrVola(nIdxInterpolate).Strike Then
                            dStrike1 = arrVola(nIdxFind).Strike
                            dVola1 = arrVola(nIdxFind).Vola
                        End If
                        If arrVola(nIdxFind).Strike > arrVola(nIdxInterpolate).Strike Then
                            dStrike2 = arrVola(nIdxFind).Strike
                            dVola2 = arrVola(nIdxFind).Vola
                            GoTo Found
                        End If
                    End If
                Next
Found:
                
                If dStrike1 = 0# And dStrike2 = 0# Then
                    arrVola(nIdxInterpolate).Vola = BAD_DOUBLE_VALUE
                ElseIf dStrike1 = 0# And dStrike2 > 0# Then
                   arrVola(nIdxInterpolate).Vola = dVola2
                ElseIf dStrike1 <> 0# And dStrike2 = 0# Then
                   arrVola(nIdxInterpolate).Vola = dVola1
                ElseIf dStrike1 <> 0# And dStrike2 <> 0# Then
                    Dim dP As Double
                    Dim dN As Double
                    Dim dChange As Double
                    Dim dRatio As Double
                    
                    dP = arrVola(nIdxInterpolate).Strike - dStrike1
                    dN = dStrike2 - dStrike1
                    dChange = dVola2 - dVola1
                    dRatio = dP / dN
                    arrVola(nIdxInterpolate).Vola = dVola1 + dChange * dRatio
                End If
            ElseIf arrVola(nIdxInterpolate).Vola = -1# And dLastGoodVola > 0# Then
                arrVola(nIdxInterpolate).Vola = dLastGoodVola
            End If
            If arrVola(nIdxInterpolate).Vola >= 0# Then
                dLastGoodVola = arrVola(nIdxInterpolate).Vola
            End If
        Next
    ElseIf Not bSomeAdded And bSomeRemoved Then
        FitToImpFillVolasForExpiry = -1
        GoTo Ex
    Else
        FitToImpFillVolasForExpiry = aExp.Strike.Count
    End If
    
    ' search for nearest to ATM strike with vola
    If nAtmIdx >= 0 Then
        If arrVola(nAtmIdx).Vola <= 0 Then
            nLastGoodIdx = -1

            ' search forth
            For nIdx = nAtmIdx + 1 To nLastIdx
                If arrVola(nIdx).Vola > 0 Then
                    nLastGoodIdx = nIdx
                    Exit For
                End If
            Next

            If nLastGoodIdx < 0 Then
                ' search back
                For nIdx = nAtmIdx - 1 To nFirstIdx Step -1
                    If arrVola(nIdx).Vola > 0 Then
                        nLastGoodIdx = nIdx
                        Exit For
                    End If
                Next
            End If

            nAtmIdx = nLastGoodIdx
        End If
    End If

    If nAtmIdx > 0 Then
        nLastGoodIdx = nAtmIdx
        ' go forth from nearest to ATM strike with vola
        For nIdx = nAtmIdx + 1 To nLastIdx
            If arrVola(nIdx).Vola > 0 Then
                nLastGoodIdx = nIdx
            Else
                If nLastGoodIdx > 0 Then
                    arrVola(nIdx).Vola = arrVola(nLastGoodIdx).Vola
                End If
            End If
        Next

        nLastGoodIdx = nAtmIdx
        ' go back from nearest to ATM strike with vola
        For nIdx = nAtmIdx - 1 To nFirstIdx Step -1
            If arrVola(nIdx).Vola > 0 Then
                nLastGoodIdx = nIdx
            Else
                If nLastGoodIdx > 0 Then
                    arrVola(nIdx).Vola = arrVola(nLastGoodIdx).Vola
                End If
            End If
        Next

        FitToImpFillVolasForExpiry = aExp.Strike.Count
    Else
        If Not bSilent Then _
            LogEvent EVENT_ERROR, m_Aux.Grp.Und.Symbol & _
                    ": Fail to fit vola to implied. No valid implied vola to fit for " _
                    & Format$(aExp.Expiry, "MMMYY") & " expiry."

        If nExactCount > 0 Then
            ReDim Preserve arrVola(1 To nExactCount)
        Else
            Erase arrVola
        End If
        If bSomeRemoved Then
            If nExactCount = 0 Then FitToImpFillVolasForExpiry = -1
        Else
            FitToImpFillVolasForExpiry = nExactCount
        End If
        
    End If
Ex:
End Function



Private Sub mnuCtxUseManualPrice_Click()
    On Error Resume Next
    Dim aRowData As EtsMmQuotesLib.MmQvRowData
    Dim aUnd As EtsMmQuotesLib.MmQvUndAtom
    
    Select Case m_enMenuGrid
        Case GT_QUOTES_UNDERLYING
        
            Set aRowData = fgUnd.RowData(m_nMenuGridRow)
            Set aUnd = aRowData.Und
            If aUnd Is Nothing Then Exit Sub
            
            Dim nIdx As Integer
            nIdx = fgUnd.ColKey(m_nMenuGridCol)
            
            If nIdx = QUC_INDEXCALCPRICE Then
            
                If mnuCtxUseManualPrice.Checked Then
                    aUnd.ActivePrice = 0
                    aUnd.UseManualActivePrice = False
                    
                    SaveManualActivePrice aUnd.ID, 0
                    gDBW.usp_MmManualPrice_Del aUnd.ID
                Else
                    aUnd.UseManualActivePrice = True
                    
                    SaveManualActivePrice aUnd.ID, aUnd.ActivePrice
                    gDBW.usp_MmManualPrice_Save aUnd.ID, aUnd.ActivePrice
                End If
                
            End If
            
            If nIdx = QUC_ACTIVEFUTUREPRICE Then

                If mnuCtxUseManualPrice.Checked Then
                    aUnd.ActiveFuture.IsUseManualActivePrice = False
                    aUnd.ActiveFuture.ActivePrice = 0
                
                    SaveManualFuturePrice aUnd.ActiveFuture.ID, 0
                    gDBW.usp_MmManualPrice_Del aUnd.ActiveFuture.ID
                Else
                    UpdateActiveFuturesPrice aUnd.ActiveFuture.ActivePrice
                
                    SaveManualFuturePrice aUnd.ActiveFuture.ID, aUnd.ActiveFuture.ActivePrice
                    gDBW.usp_MmManualPrice_Save aUnd.ActiveFuture.ID, aUnd.ActiveFuture.ActivePrice
                End If

            End If
        
        Case GT_QUOTES_FUTURES
            
            Set aRowData = fgFut.RowData(m_nMenuGridRow)
            
            If mnuCtxUseManualPrice.Checked Then
                aRowData.Fut.IsUseManualActivePrice = False
                aRowData.Fut.ActivePrice = 0
                
                SaveManualFuturePrice aRowData.Fut.ID, 0
                gDBW.usp_MmManualPrice_Del aRowData.Fut.ID
            Else
                aRowData.Fut.IsUseManualActivePrice = True
                UpdateFutureManualPrice aRowData.Fut.ActivePrice, aRowData.Fut.ID
                
                SaveManualFuturePrice aRowData.Fut.ID, aRowData.Fut.ActivePrice
                gDBW.usp_MmManualPrice_Save aRowData.Fut.ID, aRowData.Fut.ActivePrice
            End If
    
    End Select
        
    Recalculate False, True, True
    
End Sub

Private Sub mnuCtxVolaFitToImpAll_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Fit Vola To Implied -> All Expiries"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom
    Dim arrVola() As VolatilitySourcesLib.ExpiryStrikeVolaData, nExactCount&
    Dim aExpColl As EtsMmQuotesLib.MmQvExpColl
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim nCountTmp As Long
    
    
    If m_bInProc And m_bLastQuoteReqNow Or m_Aux.Grp.ID = 0 _
        Or m_enMenuGrid <> GT_QUOTES_VOLA _
            And m_enMenuGrid <> GT_QUOTES_OPTIONS _
            And m_enMenuGrid <> GT_QUOTES_UNDERLYING Then Exit Sub

    If m_Aux.Grp.IsStockOrIndex Then
        Set aExpColl = m_Aux.Grp.Und.Exp
    Else
        Set aExpColl = m_Aux.Grp.ExpAll
    End If
    
    If aExpColl.Count > 0 Then
        Screen.MousePointer = vbHourglass

        nExactCount = 0
        If m_Aux.Grp.IsStockOrIndex Then
            For Each aExp In aExpColl
                nCountTmp = FitToImpFillVolasForExpiry(aExp, arrVola, False)
                nExactCount = nExactCount + IIf(nCountTmp = -1, 0, nCountTmp)
            Next
        Else
            For Each aFut In m_Aux.Grp.Und.Fut
                For Each aExp In aFut.Exp
                    nCountTmp = FitToImpFillVolasForExpiry(aExp, arrVola, False)
                    nExactCount = nExactCount + IIf(nCountTmp = -1, 0, nCountTmp)
                Next
            Next
        End If

        If nExactCount > 0 Then
            Err.Clear
         
           If FitToImpiledInterpolatedMissing(arrVola) > 0 Then
            m_Aux.Grp.Und.VolaSrv.SetExpiryAndStrikeVolaAll arrVola
            If Err.Number = 0 Then

                m_bVolaChangedNow = True
                g_Params.FireInternalVolatilityChanged m_Aux.Grp.Und.Symbol
                m_bVolaChangedNow = False

                If g_Params.UseTheoVolatility Then
                    CalculateUnderlyingOptions True
                    m_AuxOut.UnderlyingUpdateTotals
                    UpdateTotals
                Else
                    OptionsUpdateVola
                End If

                m_AuxOut.FuturesUpdate False, True, True
                m_AuxOut.OptionsUpdate False, True, True
            Else
                LogEvent EVENT_ERROR, m_Aux.Grp.Und.Symbol & ": Fail to fit vola to implied. " & Err.Description
            End If
            
            m_AuxOut.VolaUpdateValues
           End If
        End If
        Screen.MousePointer = vbDefault
    End If
    
    Set aExpColl = Nothing
    Erase arrVola
End Sub

Private Sub mnuCtxVolaFitToImpCur_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Fit Vola To Implied -> This Expiry"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    
    Dim aStr As EtsMmQuotesLib.MmQvStrikeAtom, nOptType&
    Dim aOpt As EtsMmQuotesLib.MmQvOptAtom, aQuote As EtsMmQuotesLib.MmQvQuoteAtom, nMask(enOtPut To enOtCall) As Long, sKey$, nRow&
    Dim aExpInt As EtsMmQuotesLib.MmQvExpAtom, aExp As EtsMmQuotesLib.MmQvExpAtom, nColIdx&, aPair As EtsMmQuotesLib.MmQvOptPairAtom
    Dim arrVolaTmp() As VolatilitySourcesLib.ExpiryStrikeVolaData
    Dim arrVola() As VolatilitySourcesLib.ExpiryStrikeVolaData, nExactCount&, dVola#
    Dim aExpColl As EtsMmQuotesLib.MmQvExpColl
        
    If m_bInProc And m_bLastQuoteReqNow Or m_Aux.Grp.ID = 0 _
        Or m_enMenuGrid <> GT_QUOTES_VOLA And m_enMenuGrid <> GT_QUOTES_OPTIONS Then Exit Sub
    
    If m_Aux.Grp.IsStockOrIndex Then
        Set aExpColl = m_Aux.Grp.Und.Exp
        Set aExp = Nothing
        If m_enMenuGrid = GT_QUOTES_VOLA Then
            If m_nMenuGridCol < 1 Or m_nMenuGridCol > aExpColl.Count Then Exit Sub
            Set aExp = fgVol.ColData(m_nMenuGridCol)
            
        Else
            nColIdx = fgOpt.ColKey(m_nMenuGridCol)
            If nColIdx >= QOC_C_SYMBOL And nColIdx <= QOC_LAST_COLUMN Then
                Set aExp = QV.OptsRowData(m_nMenuGridRow).Exp
            End If
        End If
    Else
        Set aExpColl = m_Aux.Grp.ExpAll
        Set aExp = Nothing
        If m_enMenuGrid = GT_QUOTES_VOLA Then
            If m_nMenuGridCol < 1 Or m_nMenuGridCol > aExpColl.Count Then Exit Sub
            Set aExp = fgVol.ColData(m_nMenuGridCol)

        Else
            nColIdx = fgOpt.ColKey(m_nMenuGridCol)
            If nColIdx >= QOC_C_SYMBOL And nColIdx <= QOC_LAST_COLUMN Then
                Set aExp = QV.OptsRowData(m_nMenuGridRow).Exp
            End If
        End If
    End If
    
        
    
    If aExp Is Nothing Then Exit Sub
    
    nMask(enOtPut) = GetGreeksMask(enOtPut)
    nMask(enOtCall) = GetGreeksMask(enOtCall)
    
    Screen.MousePointer = vbHourglass
    m_Aux.GridLock(GT_QUOTES_OPTIONS).LockRedraw
    
    
    nExactCount = FitToImpFillVolasForExpiry(aExp, arrVola, True)
    If nExactCount = -2 Then GoTo Ex 'No one bid for current Expiry is exists
    If nExactCount = -1 Then 'No one point is added to surface
        For Each aExpInt In aExpColl
          FitToImpFillVolasForExpiry aExpInt, arrVolaTmp, True
        Next
          FitToImpiledInterpolatedMissing arrVolaTmp

        Dim posCount As Long: posCount = 1
        ReDim arrVola(1 To aExp.Strike.Count)
        For Each aStr In aExp.Strike
            arrVola(posCount).Expiry = aExp.ExpiryMonth
            arrVola(posCount).Strike = aStr.Strike
            arrVola(posCount).Vola = InterpolateVola(arrVolaTmp, arrVola(posCount))  'GetVola(arrVolaTmp, aExp.ExpiryMonth, aStr.Strike) * 100#
            If arrVola(posCount).Vola > 0# Then posCount = posCount + 1
        Next
        nExactCount = posCount - 1
    End If
    If nExactCount > 0 Then
            
        Err.Clear
        
        m_Aux.Grp.Und.VolaSrv.SetExpiryAndStrikeVolaAll arrVola
        If Err.Number = 0 Then
            
            m_bVolaChangedNow = True
            g_Params.FireInternalVolatilityChanged m_Aux.Grp.Und.Symbol
            m_bVolaChangedNow = False
            
            For Each aStr In aExp.Strike
                Dim bAssignedFromPair As Boolean:  bAssignedFromPair = False
                For Each aPair In aStr.OptPair
                    dVola = m_Aux.Grp.Und.VolaSrv.OptionVola(aExp.Expiry, aStr.Strike)
                    
                    For nOptType = enOtPut To enOtCall
                        Set aOpt = aPair.Opt(nOptType)
                        If aOpt.ID <> 0 Then
                            aOpt.Vola = dVola
                            bAssignedFromPair = True
                            
                            For Each aQuote In aOpt.Quote
                                If g_Params.UseTheoVolatility Or aQuote.CalcGreeksIVType = enMmQvCalcGreeksIVTheo Then
                                    CalcOptionGreeks aOpt, aQuote, aExp, nMask(nOptType), GetIvMask(nOptType)
                                End If
                                    
                                If aQuote.Exch.Visible Then
                                    sKey = aOpt.Symbol
                                    If aQuote.Exch.ID > 0 Then sKey = sKey & "." & aQuote.Exch.Code
                                        
'                                    nRow = fgOpt.FindRow(sKey, , IIf(nOptType = enOtCall, QOC_C_KEY, QOC_P_KEY))
'                                    If nRow > 0 Then
'                                        m_AuxOut.OptionUpdateQuote nRow, nOptType, False, True, True
'                                    Else
'                                        Debug.Assert False
'                                    End If
                                End If
                                    
                            Next
                        End If
                        Set aOpt = Nothing
                    Next
                Next
                If Not bAssignedFromPair Then _
                    aOpt.Vola = GetVola(arrVolaTmp, aOpt.Expiry, aOpt.Strike)
                
            Next
        Else
            LogEvent EVENT_ERROR, m_Aux.Grp.Und.Symbol & ": Fail to fit vola to implied. " & Err.Description
        End If
        
        m_AuxOut.VolaUpdateValues
    Else
       LogEvent EVENT_ERROR, m_Aux.Grp.Und.Symbol & _
                    ": Fail to fit vola to implied. No valid implied vola to fit for " _
                    & Format$(aExp.Expiry, "MMMYY") & " expiry."
    End If
    
    If g_Params.UseTheoVolatility Then
        CalculateUnderlyingOptions False
        m_AuxOut.UnderlyingUpdateTotals
        UpdateTotals
    End If
    
Ex:
    Set aExp = Nothing
    Set aExpColl = Nothing
    
    m_Aux.GridLock(GT_QUOTES_OPTIONS).UnlockRedraw
    Erase arrVola
    Screen.MousePointer = vbDefault
End Sub

Private Sub mnuCtxVolaFlatAllByCur_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Flat Vola -> All Expiries by This ATM"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, dVola#, nColIdx&, bUpdateOptions As Boolean
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    If m_bInProc And m_bLastQuoteReqNow Or m_Aux.Grp.ID = 0 _
        Or m_enMenuGrid <> GT_QUOTES_VOLA And m_enMenuGrid <> GT_QUOTES_OPTIONS Then Exit Sub
    
    If m_enMenuGrid = GT_QUOTES_VOLA Then
        If m_Aux.Grp.IsStockOrIndex Then
            If m_nMenuGridCol < 1 Or m_nMenuGridCol > m_Aux.Grp.Und.Exp.Count Then Exit Sub
        Else
            If m_nMenuGridCol < 1 Or m_nMenuGridCol > m_Aux.Grp.ExpAll.Count Then Exit Sub
        End If
        
        Set aExp = fgVol.ColData(m_nMenuGridCol)
        
    Else 'If m_enMenuGrid = GT_QUOTES_OPTIONS Then
        
        nColIdx = fgOpt.ColKey(m_nMenuGridCol)
        If nColIdx >= QOC_C_SYMBOL And nColIdx <= QOC_LAST_COLUMN Then
            Set aExp = QV.OptsRowData(m_nMenuGridRow).Exp
        End If
    End If
    
    If aExp Is Nothing Then Exit Sub

    Screen.MousePointer = vbHourglass
    
    If True Then 'Not aExp.AtmStrike Is Nothing Then
        If m_Aux.Grp.IsStockOrIndex Then
            dVola = m_Aux.Grp.Und.atmVola(aExp, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)
            If dVola > 0# Then
                Err.Clear
                m_Aux.Grp.Und.VolaSrv.SetExpiryVolaAll dVola
                If Err.Number = 0 Then
                    bUpdateOptions = True
                    
                    m_bVolaChangedNow = True
                    g_Params.FireInternalVolatilityChanged m_Aux.Grp.Und.Symbol
                    m_bVolaChangedNow = False
                Else
                    LogEvent EVENT_ERROR, m_Aux.Grp.Und.Symbol & ": Fail to flat vola. " & Err.Description
                End If
            Else
                bUpdateOptions = True
            End If

        Else
            For Each aFut In m_Aux.Grp.Und.Fut
                dVola = aFut.atmVola(aExp, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)
                If dVola > 0# Then
                    Err.Clear
                    m_Aux.Grp.Und.VolaSrv.SetExpiryVolaAll dVola
                    If Err.Number = 0 Then
                        bUpdateOptions = True
                        
                        m_bVolaChangedNow = True
                        g_Params.FireInternalVolatilityChanged m_Aux.Grp.Und.Symbol
                        m_bVolaChangedNow = False
                    Else
                        LogEvent EVENT_ERROR, m_Aux.Grp.Und.Symbol & ": Fail to flat vola. " & Err.Description
                    End If
                Else
                    bUpdateOptions = True
                End If
            Next
        End If
        
        Set aExp = Nothing
        
        If bUpdateOptions Then
            If g_Params.UseTheoVolatility Then
                m_bInProc = True
                CalculateUnderlyingOptions True
                m_bInProc = False
                
                m_AuxOut.UnderlyingUpdateTotals
                UpdateTotals
            Else
                OptionsUpdateVola
            End If
            m_AuxOut.FuturesUpdate False, True, True
            m_AuxOut.OptionsUpdate False, True, True
            
            m_AuxOut.VolaUpdateValues
        End If
    End If
    
    Screen.MousePointer = vbDefault
End Sub

Private Sub mnuCtxVolaFlatCur_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Flat Vola -> This Expiry by ATM"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    
    Dim aStr As EtsMmQuotesLib.MmQvStrikeAtom, nOptType&
    Dim aOpt As EtsMmQuotesLib.MmQvOptAtom, aQuote As EtsMmQuotesLib.MmQvQuoteAtom, nMask(enOtPut To enOtCall) As Long, sKey$, nRow&
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, dVola#, nColIdx&, nFutureID&, aPair As EtsMmQuotesLib.MmQvOptPairAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom, aExpTemp As EtsMmQuotesLib.MmQvExpAtom
    Dim bUpdateOptions As Boolean
    
    If m_bInProc And m_bLastQuoteReqNow Or m_Aux.Grp.ID = 0 _
        Or m_enMenuGrid <> GT_QUOTES_VOLA And m_enMenuGrid <> GT_QUOTES_OPTIONS Then Exit Sub
    
    If m_enMenuGrid = GT_QUOTES_VOLA Then
        If m_Aux.Grp.IsStockOrIndex Then
            If m_nMenuGridCol < 1 Or m_nMenuGridCol > m_Aux.Grp.Und.Exp.Count Then Exit Sub
        Else
            If m_nMenuGridCol < 1 Or m_nMenuGridCol > m_Aux.Grp.ExpAll.Count Then Exit Sub
        End If
        
        
        If Not m_Aux.Grp.IsStockOrIndex Then
            For Each aFut In m_Aux.Grp.Und.Fut
                For Each aExpTemp In aFut.Exp
                    If aExpTemp.ExpiryMonth = fgVol.ColData(m_nMenuGridCol).ExpiryMonth Then
                        Set aExp = aExpTemp
                        Exit For
                    End If
                Next
            Next
        Else
            Set aExp = fgVol.ColData(m_nMenuGridCol)
        End If
        
        
    Else 'If m_enMenuGrid = GT_QUOTES_OPTIONS Then
        
        nColIdx = fgOpt.ColKey(m_nMenuGridCol)
        If nColIdx >= QOC_C_SYMBOL And nColIdx <= QOC_LAST_COLUMN Then
            Set aExp = QV.OptsRowData(m_nMenuGridRow).Exp
        End If
    End If
    
    If aExp Is Nothing Then Exit Sub
    
    If True Then 'Not aExp.AtmStrike Is Nothing Then
        Screen.MousePointer = vbHourglass
        m_Aux.GridLock(GT_QUOTES_OPTIONS).LockRedraw
        
        nMask(enOtPut) = GetGreeksMask(enOtPut)
        nMask(enOtCall) = GetGreeksMask(enOtCall)
                
        If m_Aux.Grp.IsStockOrIndex Then
            dVola = m_Aux.Grp.Und.atmVola(aExp, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)
        Else
            nFutureID = QV.OptsRowData(m_nMenuGridRow).Opt(IIf(nColIdx < QOC_P_SYMBOL, enOtCall, enOtPut)).RootID
            If nFutureID = 0 Then
                dVola = fgVol.TextMatrix(m_nMenuGridRow, m_nMenuGridCol) / 100#
            Else
                For Each aFut In m_Aux.Grp.Und.Fut
                    If aFut.ID = nFutureID Then
                        dVola = aFut.atmVola(aExp, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)
                        Exit For
                    End If
                Next
            End If
        End If

        If dVola > 0# Then
            Err.Clear
            m_Aux.Grp.Und.VolaSrv.SetExpiryVola aExp.Expiry, dVola
            If Err.Number = 0 Then
                bUpdateOptions = True
            
                m_bVolaChangedNow = True
                g_Params.FireInternalVolatilityChanged m_Aux.Grp.Und.Symbol
                m_bVolaChangedNow = False
            Else
                LogEvent EVENT_ERROR, m_Aux.Grp.Und.Symbol & ": Fail to flat vola. " & Err.Description
            End If
        Else
            bUpdateOptions = True
        End If
                
        If bUpdateOptions Then
            For Each aStr In aExp.Strike
                
                For Each aPair In aStr.OptPair
                    dVola = m_Aux.Grp.Und.VolaSrv.OptionVola(aExp.Expiry, aStr.Strike)
                    
                    For nOptType = enOtPut To enOtCall
                        Set aOpt = aPair.Opt(nOptType)
                        If aOpt.ID <> 0 Then
                            aOpt.Vola = dVola
                                
                            For Each aQuote In aOpt.Quote
                                If g_Params.UseTheoVolatility Or aQuote.CalcGreeksIVType = enMmQvCalcGreeksIVTheo Then
                                    CalcOptionGreeks aOpt, aQuote, aExp, nMask(nOptType), GetIvMask(nOptType)
                                End If
                                    
                                If aQuote.Exch.Visible Then
                                    sKey = aOpt.Symbol
                                    If aQuote.Exch.ID > 0 Then sKey = sKey & "." & aQuote.Exch.Code
                                        
'                                    nRow = fgOpt.FindRow(sKey, , IIf(nOptType = enOtCall, QOC_C_KEY, QOC_P_KEY))
'                                    If nRow > 0 Then
'                                        m_AuxOut.OptionUpdateQuote nRow, nOptType, False, True, True
'                                    Else
'                                        Debug.Assert False
'                                    End If
                                End If
                            Next
                        End If
                        Set aOpt = Nothing
                    Next
                Next
            Next
        End If
    
        If g_Params.UseTheoVolatility Then
            CalculateUnderlyingOptions False
            m_AuxOut.UnderlyingUpdateTotals
            UpdateTotals
        End If
        m_AuxOut.VolaUpdateValues
        
        m_Aux.GridLock(GT_QUOTES_OPTIONS).UnlockRedraw
    End If
    Set aExp = Nothing
    
    Screen.MousePointer = vbDefault
End Sub

Private Sub mnuCtxVolaFlatAll_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Flat Vola -> All Expiries by Their ATM"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    
    Dim nCount&, aExp As EtsMmQuotesLib.MmQvExpAtom, dVola#
    Dim arrVola() As VolatilitySourcesLib.ExpiryVolaData, nExactCount&
    Dim aExpColl As EtsMmQuotesLib.MmQvExpColl, bUpdateOptions As Boolean
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom

    If m_bInProc And m_bLastQuoteReqNow Or m_Aux.Grp.ID = 0 _
        Or m_enMenuGrid <> GT_QUOTES_VOLA And m_enMenuGrid <> GT_QUOTES_OPTIONS And m_enMenuGrid <> GT_QUOTES_UNDERLYING Then Exit Sub

    If m_Aux.Grp.IsStockOrIndex Then
      Set aExpColl = m_Aux.Grp.Und.Exp
      nCount = aExpColl.Count
      If nCount > 0 Then
        Screen.MousePointer = vbHourglass

        nExactCount = 0
        ReDim arrVola(1 To nCount)
        For Each aExp In aExpColl
            dVola = m_Aux.Grp.Und.atmVola(aExp, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)

            If dVola > 0# Then
                nExactCount = nExactCount + 1
                arrVola(nExactCount).Expiry = aExp.ExpiryMonth
                arrVola(nExactCount).Vola = dVola * 100#
            End If
        Next
        If nExactCount > 0 Then
            If nExactCount <> nCount Then ReDim Preserve arrVola(1 To nExactCount)

            m_Aux.Grp.Und.VolaSrv.SetExpiryVolaByExpiry arrVola
            If Err.Number = 0 Then
                bUpdateOptions = True

                m_bVolaChangedNow = True
                g_Params.FireInternalVolatilityChanged m_Aux.Grp.Und.Symbol
                m_bVolaChangedNow = False
            Else
                LogEvent EVENT_ERROR, m_Aux.Grp.Und.Symbol & ": Fail to flat vola. " & Err.Description
            End If
        Else
            bUpdateOptions = True
        End If
        
        If bUpdateOptions Then
            If g_Params.UseTheoVolatility Then
                CalculateUnderlyingOptions True
                m_AuxOut.UnderlyingUpdateTotals
                UpdateTotals
            Else
                OptionsUpdateVola
            End If
    
            m_AuxOut.FuturesUpdate False, True, True
            m_AuxOut.OptionsUpdate False, True, True
            m_AuxOut.VolaUpdateValues
        End If
        Screen.MousePointer = vbDefault
      End If
        
    
    Else
        For Each aFut In m_Aux.Grp.Und.Fut
          Set aExpColl = aFut.Exp
          nCount = aExpColl.Count
          If nCount > 0 Then
            Screen.MousePointer = vbHourglass

            nExactCount = 0
            ReDim arrVola(1 To nCount)
            For Each aExp In aExpColl
                dVola = aFut.atmVola(aExp, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)

                If dVola > 0# Then
                    nExactCount = nExactCount + 1
                    arrVola(nExactCount).Expiry = aExp.ExpiryMonth
                    arrVola(nExactCount).Vola = dVola * 100#
                End If
            Next
            If nExactCount > 0 Then
                If nExactCount <> nCount Then ReDim Preserve arrVola(1 To nExactCount)

                m_Aux.Grp.Und.VolaSrv.SetExpiryVolaByExpiry arrVola 'fokiny
                If Err.Number = 0 Then
                    bUpdateOptions = True

                    m_bVolaChangedNow = True
                    g_Params.FireInternalVolatilityChanged m_Aux.Grp.Und.Symbol
                    m_bVolaChangedNow = False
                Else
                    LogEvent EVENT_ERROR, m_Aux.Grp.Und.Symbol & ": Fail to flat vola. " & Err.Description
                End If
            Else
                bUpdateOptions = True
            End If

            If bUpdateOptions Then
                If g_Params.UseTheoVolatility Then
                    CalculateUnderlyingOptions True
                    m_AuxOut.UnderlyingUpdateTotals
                    UpdateTotals
                Else
                    OptionsUpdateVola
                End If

                m_AuxOut.FuturesUpdate False, True, True
                m_AuxOut.OptionsUpdate False, True, True
                m_AuxOut.VolaUpdateValues
            End If
            Screen.MousePointer = vbDefault
          End If

        Next
    End If
        
    
    Set aExpColl = Nothing
    Erase arrVola
End Sub

Private Sub OptionsUpdateVola()
    On Error Resume Next
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, aStr As EtsMmQuotesLib.MmQvStrikeAtom, aOpt As EtsMmQuotesLib.MmQvOptAtom
    Dim aPair As EtsMmQuotesLib.MmQvOptPairAtom, dVola#
    Dim aExpColl As EtsMmQuotesLib.MmQvExpColl
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom

    If m_Aux.Grp.IsStockOrIndex Then
        Set aExpColl = m_Aux.Grp.Und.Exp
        For Each aExp In aExpColl
            For Each aStr In aExp.Strike
                For Each aPair In aStr.OptPair
                    dVola = m_Aux.Grp.Und.VolaSrv.OptionVola(aExp.Expiry, aStr.Strike)
                    
                    Set aOpt = aPair.Opt(enOtCall)
                    If aOpt.ID <> 0 Then aOpt.Vola = dVola
                    
                    Set aOpt = aPair.Opt(enOtPut)
                    If aOpt.ID <> 0 Then aOpt.Vola = dVola
                Next
            Next
        Next

    Else
        For Each aFut In m_Aux.Grp.Und.Fut
            Set aExpColl = aFut.Exp
            For Each aExp In aExpColl
                For Each aStr In aExp.Strike
                    For Each aPair In aStr.OptPair
                        dVola = m_Aux.Grp.Und.VolaSrv.OptionVola(aExp.Expiry, aStr.Strike)
                        
                        Set aOpt = aPair.Opt(enOtCall)
                        If aOpt.ID <> 0 Then aOpt.Vola = dVola
                        
                        Set aOpt = aPair.Opt(enOtPut)
                        If aOpt.ID <> 0 Then aOpt.Vola = dVola
                    Next
                Next
            Next
        Next
    End If
    
    Set aExpColl = Nothing
End Sub

Private Sub mnuCtxGridLayout_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Select Case m_enMenuGrid
        Case GT_QUOTES_UNDERLYING
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying popup menu. ""RightClick -> Grid Layout..."" selected. " & GetStockInfo, m_frmOwner.GetCaption
            CustomizeUnderlyingGridLayout
            
        Case GT_QUOTES_FUTURES
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Option popup menu. ""RightClick -> Grid Layout..."" selected. " & GetFutureInfo, m_frmOwner.GetCaption
            CustomizeFutureGridLayout

        Case GT_QUOTES_OPTIONS
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Option popup menu. ""RightClick -> Grid Layout..."" selected. " & GetOptionInfo, m_frmOwner.GetCaption
            CustomizeOptionGridLayout
        
        Case GT_QUOTES_VOLA
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Vola popup menu. ""RightClick -> Grid Layout..."" selected. " & GetStockInfo, m_frmOwner.GetCaption
            CustomizeVolaGridLayout
        
        Case GT_QUOTES_DIVIDENDS
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Dividend popup menu. ""RightClick -> Grid Layout..."" selected. " & GetStockInfo, m_frmOwner.GetCaption
            CustomizeDivGridLayout
        
    End Select
End Sub

Private Sub mnuCtxHideCol_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_nMenuGridCol < 0 Or m_nMenuGridRow < 0 Then Exit Sub
    
    Dim i&, nColIdx&, bMove As Boolean
    
    Select Case m_enMenuGrid
        Case GT_QUOTES_UNDERLYING
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying popup menu. ""RightClick -> Hide Column"" selected. " & GetStockInfo, m_frmOwner.GetCaption
                
            bMove = False
            
            nColIdx = fgUnd.ColKey(m_nMenuGridCol)
            For i = 1 To QUC_LAST_COLUMN ' skip QUC_SYMBOL
                If m_gdUnd.Idx(i) = nColIdx Then
                    m_gdUnd.Idx(i) = QUC_NONE
                    m_gdUnd.Col(nColIdx).Visible = False
                    bMove = True
                End If
                
                If bMove Then
                    If i + 1 <= QUC_LAST_COLUMN Then
                        m_gdUnd.Idx(i) = m_gdUnd.Idx(i + 1)
                    Else
                        m_gdUnd.Idx(i) = QUC_NONE
                    End If
                End If
            Next
            
            If bMove Then
                m_Aux.FormatUndGrid
                m_Aux.FormatUndColumns
                m_AuxOut.UnderlyingUpdate True, True
                m_AuxOut.UnderlyingUpdateTotals
            End If
            
        Case GT_QUOTES_FUTURES
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Future popup menu. ""RightClick -> Hide Column"" selected. " & GetFutureInfo, m_frmOwner.GetCaption
                
            bMove = False
            
            If m_gdFut.Idx(1) = QOF_NONE Then Exit Sub
            
            nColIdx = fgFut.ColKey(m_nMenuGridCol)
            For i = 0 To QOF_LAST_COLUMN
                If m_gdFut.Idx(i) = nColIdx Then
                    m_gdFut.Idx(i) = QOF_NONE
                    m_gdFut.Col(nColIdx).Visible = False
                    bMove = True
                End If
                
                If bMove Then
                    If i + 1 <= QOF_LAST_COLUMN Then
                        m_gdFut.Idx(i) = m_gdFut.Idx(i + 1)
                    Else
                        m_gdFut.Idx(i) = QOF_NONE
                    End If
                End If
            Next
            
            If bMove Then
                m_Aux.FormatFutGrid
                m_Aux.FormatFutColumns
                m_AuxOut.FuturesUpdate True, True, True
            End If

        Case GT_QUOTES_OPTIONS
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Option popup menu. ""RightClick -> Hide Column"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
                
            bMove = False
            
            If m_gdOpt.Idx(1) = QOC_NONE Then Exit Sub
            
            nColIdx = fgOpt.ColKey(m_nMenuGridCol)
            For i = 0 To QOC_LAST_COLUMN
                If m_gdOpt.Idx(i) = nColIdx Then
                    m_gdOpt.Idx(i) = QOC_NONE
                    m_gdOpt.Col(nColIdx).Visible = False
                    bMove = True
                End If
                
                If bMove Then
                    If i + 1 <= QOC_LAST_COLUMN Then
                        m_gdOpt.Idx(i) = m_gdOpt.Idx(i + 1)
                    Else
                        m_gdOpt.Idx(i) = QOC_NONE
                    End If
                End If
            Next
            
            If bMove Then
                m_Aux.FormatOptGrid
                m_Aux.FormatOptColumns
                m_AuxOut.OptionsUpdate True, True, True
            End If
            
    End Select
End Sub

Private Sub FillDataForOrderFromCurrentSelection(ByVal bIsStock As Boolean, _
                                        ByVal bForceStockNetDelta As Boolean, _
                                        ByRef aUnd As EtsGeneralLib.UndAtom, _
                                        ByRef aOpt As EtsGeneralLib.EtsOptAtom, _
                                        ByRef bBuy As Boolean, ByRef dPrice#, ByRef nQty&)
    On Error Resume Next
    Dim aRowData As MmQvRowData, nColIdx&
    Dim aCurOpt As EtsMmQuotesLib.MmQvOptAtom, aCurUnd As EtsMmQuotesLib.MmQvUndAtom
    
    bBuy = True
    dPrice = 0#
    nQty = IIf(bIsStock, 100, 10)
    
    Select Case True
        Case bIsStock And bForceStockNetDelta _
            Or m_enMenuGrid = GT_QUOTES_DIVIDENDS Or m_enMenuGrid = GT_QUOTES_VOLA _
            Or bIsStock And m_enMenuGrid = GT_QUOTES_OPTIONS
            
            Set aUnd = g_Underlying(m_Aux.Grp.Und.ID)
            If Not aUnd Is Nothing And bIsStock And (m_Aux.Grp.IsStockOrIndex) Then
                nQty = Round(m_Aux.Grp.Und.NetDelta / 100) * 100
                If m_Aux.Grp.Und.NetDelta >= 0 Then
                    bBuy = False
                    dPrice = m_Aux.Grp.Und.Quote(0).PriceBid
                    If nQty = 0 Then nQty = 100
                    
                Else
                    nQty = Abs(nQty)
                    bBuy = True
                    dPrice = m_Aux.Grp.Und.Quote(0).PriceAsk
                    If nQty = 0 Then nQty = 100
                End If
                
                If dPrice <= 0# Then dPrice = m_Aux.Grp.Und.Quote(0).PriceLast
            End If
            
        Case m_enMenuGrid = GT_QUOTES_UNDERLYING
            If m_Aux.Grp.IsStockOrIndex Then
                nColIdx = fgUnd.ColKey(m_nMenuGridCol)
                Set aCurUnd = fgUnd.RowData(m_nMenuGridRow).Und
                If Not aCurUnd Is Nothing Then
                    Set aUnd = g_Underlying(aCurUnd.ID)
                    
                    If Not aUnd Is Nothing And bIsStock Then
                        Select Case nColIdx
                            Case QUC_BID
                                bBuy = False
                                dPrice = aCurUnd.Quote(0).PriceBid
                        
                            Case QUC_ASK
                                bBuy = True
                                dPrice = aCurUnd.Quote(0).PriceAsk
                                
                            Case Else
                                nQty = Round(aCurUnd.NetDelta / 100) * 100
                                If aCurUnd.NetDelta >= 0 Then
                                    bBuy = False
                                    dPrice = aCurUnd.Quote(0).PriceBid
                                    If nQty = 0 Then nQty = 100
                                    
                                Else
                                    nQty = Abs(nQty)
                                    bBuy = True
                                    dPrice = aCurUnd.Quote(0).PriceAsk
                                    If nQty = 0 Then nQty = 100
                                End If
                        End Select
                        
                        If dPrice <= 0# Then dPrice = aCurUnd.Quote(0).PriceLast
                    End If
                    Set aCurUnd = Nothing
                End If
            End If
            
            If aUnd Is Nothing Then Set aUnd = g_Underlying(m_Aux.Grp.Und.ID)
        
        Case m_enMenuGrid = GT_QUOTES_OPTIONS
            Set aUnd = g_Underlying(m_Aux.Grp.Und.ID)
            If Not aUnd Is Nothing Then
                If Not bIsStock And (m_Aux.Grp.IsStockOrIndex) Then
                    nColIdx = fgOpt.ColKey(m_nMenuGridCol)
                    Set aCurOpt = QV.OptsRowData(m_nMenuGridRow).Opt(IIf(nColIdx < QOC_P_SYMBOL, enOtCall, enOtPut))
                    If Not aCurOpt Is Nothing Then
                        
                        Set aOpt = New EtsGeneralLib.EtsOptAtom
                        aOpt.ID = aCurOpt.ID
                        aOpt.OptType = aCurOpt.OptType
                        aOpt.RootID = aCurOpt.RootID
                        aOpt.Symbol = aCurOpt.Symbol
                        aOpt.Expiry = aCurOpt.Expiry
                        aOpt.Strike = aCurOpt.Strike
                        
                        If nColIdx = QOC_C_ASK Or nColIdx = QOC_P_ASK Then
                            bBuy = True
                            dPrice = aCurOpt.Quote(0).PriceAsk
                        Else
                            bBuy = False
                            dPrice = aCurOpt.Quote(0).PriceBid
                        End If
                        
                        If dPrice <= 0# Then dPrice = aCurOpt.Quote(0).PriceLast
                        
                        Set aCurOpt = Nothing
                    End If
                End If
            End If
        
    End Select
End Sub

Private Sub OrderNew(ByVal bIsStock As Boolean, ByVal bForceStockNetDelta As Boolean)
    On Error Resume Next
    If m_bInProc Then Exit Sub
    Dim bBuy As Boolean, aUnd As EtsGeneralLib.UndAtom
    Dim dPrice#, nQty&, aOpt As EtsGeneralLib.EtsOptAtom

    m_bInProc = True
    FillDataForOrderFromCurrentSelection bIsStock, bForceStockNetDelta, aUnd, aOpt, bBuy, dPrice, nQty
    m_bInProc = False

    On Error GoTo EH
    If bIsStock Then
        frmOrderEntry.NewStockOrder aUnd, bBuy, nQty, dPrice
    Else
        frmOrderEntry.NewOptionOrder aUnd, aOpt, bBuy, nQty, dPrice
    End If
    Set aUnd = Nothing
    Set aOpt = Nothing

    Exit Sub
EH:
    m_bInProc = False
    gCmn.ErrorMsgBox m_frmOwner, "Quotes View: Fail to create new order."
    ResetMenuData
    Set aUnd = Nothing
    Set aOpt = Nothing
End Sub

Private Sub mnuCtxOrderNewOption_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, IIf(m_bIsDblClick, "Ctrl + Alt + DblClick pressed (new option order). ", "Popup menu. ""RightClick -> New Option Order..."" selected. ") & GetOptionInfo, m_frmOwner.GetCaption
    OrderNew False, False
End Sub

Private Sub mnuCtxOrderNewStock_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, IIf(m_bIsDblClick, "Alt + DblClick pressed (new stock order). ", "Popup menu. ""RightClick -> New Stock Order..."" selected. ") & GetOptionInfo, m_frmOwner.GetCaption
    OrderNew True, False
End Sub

Public Sub NewStockOrderAtNetDelta()
    On Error Resume Next
    OrderNew True, True
End Sub

Private Sub mnuCtxTntCardNew_Click()
'    On Error Resume Next
'    If m_bShutDown Then Exit Sub
'    If m_bInProc Then Exit Sub
'    Dim bBuy As Boolean, aUnd As EtsGeneralLib.UndAtom
'    Dim dPrice#, nQty&, aOpt As EtsGeneralLib.EtsOptAtom
'
'    m_bInProc = True
'    FillDataForOrderFromCurrentSelection False, False, aUnd, aOpt, bBuy, dPrice, nQty
'    m_bInProc = False
'
'    On Error GoTo EH
'    frmTntCardEntry.NewCard m_frmOwner, aUnd, aOpt, bBuy, nQty, dPrice
'
'    Set aUnd = Nothing
'    Set aOpt = Nothing
'    Exit Sub
'EH:
'    m_bInProc = False
'    gCmn.ErrorMsgBox m_frmOwner, "Quotes View: Fail to create new trade message."
'    ResetMenuData
'    Set aUnd = Nothing
'    Set aOpt = Nothing
End Sub

Private Sub mnuCtxTradeNew_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_bInProc Or m_nMenuGridCol < 0 Or m_nMenuGridRow < 1 Or m_Aux.Grp.ID = 0 Or Not m_Aux.Grp.Und.IsTraderContract Then Exit Sub
    Dim aRowData As MmQvRowData, nColIdx&, bBuy As Boolean, aOpt As EtsMmQuotesLib.MmQvOptAtom, aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    Select Case m_enMenuGrid
        Case GT_QUOTES_UNDERLYING
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, IIf(m_bIsDblClick, "DblClick on Underlying Grid (new trade). ", "Underlying popup menu. ""RightClick -> New Trade..."" selected. ") & GetStockInfo, m_frmOwner.GetCaption
        
            Set aRowData = fgUnd.RowData(m_nMenuGridRow)
                 nColIdx = fgUnd.ColKey(m_nMenuGridCol)

            If Not aRowData Is Nothing Then
                Set aUnd = aRowData.Und
                
                If Not aUnd Is Nothing Then
                    If m_Aux.Grp.IsStockOrIndex Then
                        On Error GoTo EH
                        
                        If nColIdx = QUC_BID Then
                             bBuy = (g_Params.QuoteBidColBuy <> 0)
                        ElseIf nColIdx = QUC_ASK Then
                            bBuy = (g_Params.QuoteBidColBuy = 0)
                        Else
                            bBuy = (g_Params.QuoteOtherColBuy <> 0)
                        End If
                        If aUnd.ID <> USD_ID Then frmTradeEditor.NewTrade aUnd.ID, aUnd.ID, bBuy, m_frmOwner
                    Else
                        Set aFut = aRowData.Fut
                        If Not aFut Is Nothing Then
                            On Error GoTo EH
                            
                            frmTradeEditor.NewTrade aFut.ID, aUnd.ID, g_Params.QuoteOtherColBuy, m_frmOwner
                            Set aFut = Nothing
                        End If
                    End If
                    Set aUnd = Nothing
                End If
                Set aRowData = Nothing
            End If
            
        Case GT_QUOTES_FUTURES
            Set aRowData = fgFut.RowData(m_nMenuGridRow)
            nColIdx = fgFut.ColKey(m_nMenuGridCol)
            
            If Not aRowData Is Nothing Then
                Set aFut = aRowData.Fut
                If Not aFut Is Nothing Then
                
                    If Not g_PerformanceLog Is Nothing Then _
                        g_PerformanceLog.LogMmInfo enLogUserAction, IIf(m_bIsDblClick, "DblClick on Future Grid (new trade). ", "Future popup menu. ""RightClick -> New Trade..."" selected. ") & GetFutureInfo & "Future symbol = """ & aFut.Symbol & """.", m_frmOwner.GetCaption
                    
                    If nColIdx = QOF_BID Then
                        bBuy = (g_Params.QuoteBidColBuy <> 0)
                    ElseIf nColIdx = QOF_ASK Then
                        bBuy = (g_Params.QuoteBidColBuy = 0)
                    Else
                        bBuy = (g_Params.QuoteOtherColBuy <> 0)
                    End If
                    
                    On Error GoTo EH
                    frmTradeEditor.NewTrade aFut.ID, m_Aux.Grp.Und.ID, bBuy, m_frmOwner
                    
                    Set aFut = Nothing
                End If
                Set aRowData = Nothing
            End If
        
        Case GT_QUOTES_OPTIONS
            Set aRowData = QV.OptsRowData(m_nMenuGridRow)
            nColIdx = fgOpt.ColKey(m_nMenuGridCol)
            If Not aRowData Is Nothing Then
                Set aOpt = aRowData.Opt(IIf(nColIdx < QOC_P_SYMBOL, enOtCall, enOtPut))
                If Not aOpt Is Nothing Then
                
                    If Not g_PerformanceLog Is Nothing Then _
                        g_PerformanceLog.LogMmInfo enLogUserAction, IIf(m_bIsDblClick, "DblClick on Option Grid (new trade). ", "Option popup menu. ""RightClick -> New Trade..."" selected. ") & GetStockInfo & "Option symbol = """ & aOpt.Symbol & """.", m_frmOwner.GetCaption
                    
                    If nColIdx = QOC_C_BID Or nColIdx = QOC_P_BID Then
                        bBuy = (g_Params.QuoteBidColBuy <> 0)
                    ElseIf nColIdx = QOC_C_ASK Or nColIdx = QOC_P_ASK Then
                        bBuy = (g_Params.QuoteBidColBuy = 0)
                    Else
                        bBuy = (g_Params.QuoteOtherColBuy <> 0)
                    End If
                    
                    On Error GoTo EH
                    frmTradeEditor.NewTrade aOpt.ID, m_Aux.Grp.Und.ID, bBuy, m_frmOwner
                    
                    Set aOpt = Nothing
                End If
                Set aRowData = Nothing
            End If
        
    End Select
    
    ResetMenuData
    Exit Sub
EH:
    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to create new trade."
    ResetMenuData
End Sub

Private Sub mnuCtxPositionTransfer_Click()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_bInProc Or m_nMenuGridCol < 0 Or m_nMenuGridRow < 1 Or m_Aux.Grp.ID = 0 Or Not m_Aux.Grp.Und.IsTraderContract Then Exit Sub
    Dim aRowData As MmQvRowData, nColIdx&, aOpt As EtsMmQuotesLib.MmQvOptAtom, aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim sContractDesc$, aFut As EtsMmQuotesLib.MmQvFutAtom
    
    Select Case m_enMenuGrid
        Case GT_QUOTES_UNDERLYING
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Underlying popup menu. ""RightClick -> Position Transfer..."" selected. " & GetStockInfo, m_frmOwner.GetCaption
                
            Set aRowData = fgUnd.RowData(m_nMenuGridRow)
            If Not aRowData Is Nothing Then
                Set aUnd = aRowData.Und
                If Not aUnd Is Nothing Then
                    If m_Aux.Grp.IsStockOrIndex Then
                        If aUnd.ID <> USD_ID Then
                            On Error GoTo EH
                            
                            sContractDesc = aUnd.Symbol & " (" & aUnd.SymbolName & ")"
                            
                            frmPositionTransfer.TransferPosition aUnd.ID, aUnd.ID, 0, sContractDesc, m_frmOwner
                        End If
                    Else
                        Set aFut = aRowData.Fut
                        If Not aFut Is Nothing Then
                            On Error GoTo EH
                            
                            sContractDesc = aFut.Symbol & " (" & aFut.ContractName & ")"
                            
                            frmPositionTransfer.TransferPosition aUnd.ID, aFut.ID, 0, sContractDesc, m_frmOwner
                            Set aFut = Nothing
                        End If
                    End If
                    Set aUnd = Nothing
                End If
                Set aRowData = Nothing
            End If
            
        Case GT_QUOTES_FUTURES
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Future popup menu. ""RightClick -> Position Transfer..."" selected. " & GetFutureInfo, m_frmOwner.GetCaption
            'fokiny
        
        Case GT_QUOTES_OPTIONS
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Option popup menu. ""RightClick -> Position Transfer..."" selected. " & GetOptionInfo, m_frmOwner.GetCaption
                
            Set aRowData = QV.OptsRowData(m_nMenuGridRow)
            nColIdx = fgOpt.ColKey(m_nMenuGridCol)
            If Not aRowData Is Nothing Then
                Set aOpt = aRowData.Opt(IIf(nColIdx < QOC_P_SYMBOL, enOtCall, enOtPut))
                If Not aOpt Is Nothing Then
                    If m_Aux.Grp.IsStockOrIndex Then
                        sContractDesc = aOpt.Symbol & " (" & m_Aux.Grp.Und.Symbol & " " & Format$(aOpt.Expiry, "MMMM YYYY") & " " & _
                                    CStr(aOpt.Strike) & IIf(aOpt.OptType = enOtCall, " Call)", " Put)")
                    
                        On Error GoTo EH
                        frmPositionTransfer.TransferPosition m_Aux.Grp.Und.ID, aOpt.ID, 0, sContractDesc, m_frmOwner
                    Else
                        Set aFut = aRowData.Fut
                        If Not aFut Is Nothing Then
                            sContractDesc = aOpt.Symbol & " (" & aFut.Symbol & " " & Format$(aOpt.Expiry, "MMMM YYYY") & " " & _
                                        CStr(aOpt.Strike) & IIf(aOpt.OptType = enOtCall, " Call)", " Put)")
                            
                            On Error GoTo EH
                            frmPositionTransfer.TransferPosition m_Aux.Grp.Und.ID, aOpt.ID, 0, sContractDesc, m_frmOwner
                            Set aFut = Nothing
                        End If
                    End If
                    
                    Set aOpt = Nothing
                End If
                Set aRowData = Nothing
            End If
        
    End Select
    
    ResetMenuData
    Exit Sub
EH:
    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to transfer position."
    ResetMenuData
End Sub

Private Sub mnuCtxPrint_Click()
'    On Error Resume Next
'    If m_bShutDown Then Exit Sub
'    Screen.MousePointer = vbHourglass
'    Select Case m_enMenuGrid
'        Case GT_QUOTES_UNDERLYING
'            frmPrintPreview.Execute m_frmOwner, m_Aux.Grp.Symbol & " Quotes", "Underlying Quotes", fgUnd
'
'        Case GT_QUOTES_DIVIDENDS
'            frmPrintPreview.Execute m_frmOwner, m_Aux.Grp.Symbol & " Calculation Params", "Underlying Calculation Params", fgDiv
'
'        Case GT_QUOTES_VOLA
'            frmPrintPreview.Execute m_frmOwner, m_Aux.Grp.Symbol & " ATM Volas", "ATM Volas", fgVol
'
'        Case GT_QUOTES_FUTURES
'            frmPrintPreview.Execute m_frmOwner, m_Aux.Grp.Symbol & " Futures Quotes", "Futures Quotes", fgFut
'
'        Case GT_QUOTES_OPTIONS
'            frmPrintPreview.Execute m_frmOwner, m_Aux.Grp.Symbol & " Options Quotes", "Options Quotes", fgOpt
'
'    End Select
'    Screen.MousePointer = vbDefault
End Sub

Private Sub mnuCtxRealTime_Click()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Real Time Mode"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    ToggleRealtime
End Sub

Public Sub ToggleRealtime()
    On Error Resume Next
    If m_bShutDown Or m_bSubscribingNow Or m_bDataLoad Or m_bLastQuoteReqNow Or m_Aux.Grp.ID <= 0 Or m_bInitializing Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, IIf(Not m_Aux.RealTime, "Start", "Stop") & " Real Time Mode.", m_frmOwner.GetCaption
    
    
'    If Not m_Aux.RealTime And Not m_bInProc Then
    If Not m_Aux.RealTime Then
        StartRealTime
    Else
        StopRealTime
    End If
    
    UpdateTotals
End Sub

Private Sub mnuCtxRefresh_Click()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> Refresh"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    If Not m_bShutDown Then Refresh
End Sub
Private Sub mnuCtxRefreshPrices_Click()
    On Error Resume Next
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogUserAction, "Popup menu. ""RightClick -> RefreshPrices"" selected. " & GetOptionInfo, m_frmOwner.GetCaption
    If Not m_bShutDown Then RefreshPrices
End Sub

Private Sub PriceProvider_OnUnsubscribed()
    If Not m_bShutDown Then DoEvents
End Sub

Private Sub QV_Progress(ByVal lProgress As Long, ByVal lMaxProgress As Long)
        pbProgress.Visible = True
        pbProgress.Min = 0
        pbProgress.Max = lMaxProgress
        pbProgress.Value = lProgress
End Sub

Private Sub tmrPriceProviderIdle_Timer()
On Error Resume Next
tmrPriceProviderIdle.Enabled = False
 
 If m_bSubscribingNow Then
    m_bSubscribingNow = False
 End If

 If m_bLastQuoteReqNow Then
    m_bLastQuoteReqNow = False
    PriceProvider.CancelLastQuote
 End If
 AdjustState
End Sub

Private Sub tmrQuoteCalculation_Timer()
    On Error Resume Next
    Dim nTime As Long
    Dim nLogTime As Long
    Dim nOperation As Long
    Dim nUnds As Long
    Dim nFuts As Long
    Dim nOpts As Long
    
    tmrQuoteCalculation.Enabled = False
    lblProcess.Caption = "Calculation..."
        
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.FinishLogMmOperation m_nOperation, OPER_REQUESTQUOTE, m_frmOwner.GetCaption, QV.UndResponses, QV.OptResponses, QV.FutResponses
                
    nTime = timeGetTime
    If Not g_PerformanceLog Is Nothing Then m_nOperation = g_PerformanceLog.BeginLogMmOperation
        
    m_bInProc = True
    
    m_AuxOut.UnderlyingExchUpdate
    DoEvents
    CalculateUnderlyingOptions True
    m_bInProc = False
    
    m_nLastRecalcCycle = timeGetTime - nTime
    
    If Not g_PerformanceLog Is Nothing Then nLogTime = g_PerformanceLog.CheckLogMmOperation(m_nOperation)
        
    nTime = timeGetTime
    
    If Not g_PerformanceLog Is Nothing Then nOperation = g_PerformanceLog.BeginLogMmOperation
    
    nUnds = m_AuxOut.UnderlyingUpdate(False, True)
    nFuts = m_AuxOut.FuturesUpdate(False, True, True)
    nOpts = m_AuxOut.OptionsUpdate(False, True, True)
    m_AuxOut.VolaUpdateValues
    
    AdjustState
    m_AuxOut.UnderlyingUpdateTotals
    UpdateTotals
    
    m_AuxOut.OptionsUpdateColors
    
    m_nLastOutCycle = timeGetTime - nTime
    
    If Not g_PerformanceLog Is Nothing Then
        g_PerformanceLog.ContinueLogMmOperation m_nOperation, OPER_CALCULATION, m_frmOwner.GetCaption, nUnds, nOpts, nFuts, nLogTime
        g_PerformanceLog.FinishLogMmOperation nOperation, OPER_REFRESHSCREEN, m_frmOwner.GetCaption, nUnds, nOpts, nFuts
        g_PerformanceLog.FinishLogMmOperation m_nOperation, OPER_CALCREFRESHSCREEN, m_frmOwner.GetCaption, nUnds, nOpts, nFuts
    End If
                
    If g_Params.IsDebug Then UpdateStat
    
    pbProgress.Visible = False
    lblStatus.Visible = True
    lblProcess.Visible = False
    lblProcess.Caption = ""
    imgStopDis.Visible = False
End Sub

Private Sub tmrRealTime_Timer()
    On Error Resume Next
    tmrRealTime.Enabled = False
    If Not m_bShutDown And m_Aux.RealTime Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "tmrRealTime_Timer: Start RealTimeQuotesUpdate", m_frmOwner.GetCaption
        RealTimeQuotesUpdate
        RaiseEvent OnScreenRefresh
    Else
        If Not m_bShutDown Then
            QV.LoadQuoteUpdates
            fgOpt.Refresh
            DoEvents
            m_AuxOut.UnderlyingUpdate False, True
        End If
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "tmrRealTime_Timer: Risks are not in realtime mode", m_frmOwner.GetCaption
    End If
End Sub

Private Sub tmrShow_Timer()
    Dim nOperation&
    Dim bInRefresh As Boolean
    
    On Error Resume Next
    bInRefresh = m_bInRefreshMode
    m_bInRefreshMode = False

    tmrShow.Enabled = False
    If m_bShutDown Then Exit Sub
    
    If Not g_PerformanceLog Is Nothing Then _
        nOperation = g_PerformanceLog.BeginLogMmOperation
    
   
    If m_Aux.Grp.ID <> 0 And Not PriceProvider Is Nothing Then
        m_Aux.Grp.Und.StopCalc
       
        If m_bLastQuoteReqNow Then
            m_bLastQuoteReqNow = False
            PriceProvider.CancelLastQuote
            If m_bGroupRequest Then m_GroupPriceProvider.CancelLastGroupQuotes
        End If
        
        If m_bInRealTimeCalc Then
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogEnhDebug, "Start stoping calculations.", m_frmOwner.GetCaption
        End If
        
        Dim i As Long
        While m_bInRealTimeCalc And i < 5
            MMSleep 10
            i = i + 1
        Wend
        
        If m_bInRealTimeCalc Then
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogEnhDebug, "FAIL: Can't stop calculations.", m_frmOwner.GetCaption
        End If
        
        If m_Aux.RealTime Or m_bSubscribingNow Then
            m_bSubscribingNow = False
            m_Aux.RealTime = False
            m_Aux.RealTimeConnected = False
            PriceProvider.UnSubscribeQuote
            If g_RTQuantity > 0 Then
                g_RTQuantity = g_RTQuantity - 1
            End If
            
            If m_bGroupRequest Then m_GroupPriceProvider.UnSubscribeGroupQuotes
        End If
        
        pbProgress.Visible = False
        lblStatus.Visible = True
        lblProcess.Visible = False
        lblProcess.Caption = ""
        imgStop.Visible = False
        imgStopDis.Visible = False
    End If
    
    ClearViewAndData
        
    If m_nNewGrpID <> 0 Then
        pbProgress.Value = 0
        pbProgress.Visible = True
        
        lblStatus.Visible = False
        lblProcess.Visible = True
        lblProcess.Caption = "Data load..."
        lblProcess.Refresh
        imgStop.Visible = True
        imgStopDis.Visible = False
        Dim sttime As Long
        
        m_bInitializing = True
        If InitGroup(m_nNewGrpID) Then
        
            ShowGroup
        
            RaiseEvent OnExpiriesChange(False)
            RaiseEvent OnOptRootsChange(False)
            RaiseEvent OnOptExchangesChange(False)
            RaiseEvent OnUndExchangesChange(False)
            RaiseEvent OnFutChange(False)
            RaiseEvent OnStrikesChange
            
            AdjustOptExchVisible
            AdjustOptPosExchIDs
        
            fgUnd.Row = m_nUndMainRow
            fgUnd.Col = QUC_SYMBOL
            fgUnd.SetFocus
            
            UpdateTotals
            If g_Params.QuoteDirectlyToRealtime And Not bInRefresh Then
                sttime = GetTickCount
                If Not bInRefresh Then
                    m_bFiersTealtimeCalculation = True
                Else
                    m_bFiersTealtimeCalculation = False
                End If
                StartRealTime
                sttime = GetTickCount - sttime
            Else
                m_bFiersTealtimeCalculation = False
                RequestLastQuotes
            End If
        Else
            pbProgress.Visible = False
            lblStatus.Visible = True
            lblProcess.Visible = False
            lblProcess.Caption = ""
            imgStop.Visible = False
            imgStopDis.Visible = False
            
            UpdateTotals
            ClearViewAndData
            
            fgUnd.Row = m_nUndMainRow
            fgUnd.Col = QUC_SYMBOL
            fgUnd.SetFocus
            fgUnd.TextMatrix(m_nUndMainRow, QUC_SYMBOL) = ""
            
            AdjustCaption
        End If
        m_bInitializing = False
    End If

    Screen.MousePointer = vbDefault
    UserControl_Resize
    
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.FinishLogMmOperation nOperation, OPER_LOADDATA, m_frmOwner.GetCaption, QV.UndQuotesCount, QV.OptQuotesCount, QV.FutQuotesCount
End Sub

Public Sub RefreshFutsGrid()

Dim aFut As EtsMmQuotesLib.MmQvFutAtom, aExch As EtsGeneralLib.ExchAtom
Dim aRowData As MmQvRowData, nRow&, sKey$, bHidden As Boolean
On Error Resume Next
pbProgress.Value = 0
    
If m_Aux.Grp.Und.Fut.Count = 0 Then Exit Sub
    
    fgFut.Rows = 1
        For Each aFut In m_Aux.Grp.Und.Fut
            For Each aExch In aFut.FutExch
                Set aRowData = New MmQvRowData
                Set aRowData.Exch = aExch
                Set aRowData.Fut = aFut
                Set aRowData.FutQuote = aFut.Quote(aExch.ID)
                Set aRowData.FutRoot = m_Aux.Grp.FutRootColl(aFut.FutRootID)
                                               
                If Not aRowData.FutQuote Is Nothing Then
                    fgFut.AddItem ""
                    nRow = fgFut.Rows - 1
    
                    fgFut.RowData(nRow) = aRowData
   
                    If Not aRowData.FutQuote Is Nothing Then
                        sKey = aRowData.Fut.Symbol
                        If aExch.ID <> 0 Then
                            sKey = sKey & "." & aExch.Code
                        End If
                        fgFut.TextMatrix(nRow, QOF_KEY) = sKey
   
                        m_AuxOut.FutureUpdateQuote nRow, True, False, True
                        IncProgress pbProgress
                    End If
                        
                    bHidden = IIf(m_Aux.Grp.IsStockOrIndex, True, Not aRowData.Fut.Visible) 'Not aRowData.Exch.Visible
    
                    fgFut.RowHidden(nRow) = bHidden
                End If
                Set aRowData = Nothing
            Next
        Next
        
        m_Aux.AdjustFuturesVisible
        m_AuxOut.FuturesUpdate True, True, True
        
        m_Aux.FormatFutColumns
        m_AuxOut.FuturesUpdateColors
        
        UserControl_Resize

End Sub

Public Sub RefreshOptsGrid()
    On Error Resume Next
    ClearSpread

    m_Aux.GridLock(GT_QUOTES_OPTIONS).LockRedraw
    fgOpt.FlexDataSource = Nothing
    
    If Not m_bInRealTimeCalc Then
           m_bInRealTimeCalc = True
           CalculateUnderlyingOptions True
           m_bInRealTimeCalc = False
    End If
    
    QV.OptsColumnsOrder = m_Aux.gdOpt.IdxCopy
    QV.OptsRefresh False
    fgOpt.FlexDataSource = QV
    m_Aux.FormatOptColumns
    m_AuxOut.OptionsUpdateBackColor g_Params.QuoteOptExpirySeparation
    m_AuxOut.OptionsUpdateColors
   m_Aux.GridLock(GT_QUOTES_OPTIONS).UnlockRedraw
 

End Sub

Private Sub ClearViewAndData()
    On Error Resume Next
    Dim sSymbol$
    
    m_AuxOut.ExpiryColorSelection = False
    m_nUndMainRow = 1
    sSymbol = g_ContractAll(m_nNewGrpID).Symbol
    If Not m_bShutDown Then
        With fgUnd
            .Rows = 2
            .RowHidden(m_nUndMainRow) = False
            .RowData(m_nUndMainRow) = Empty
            .Row = m_nUndMainRow
            
            m_Aux.GridLock(GT_QUOTES_UNDERLYING).LockRedraw
            
            
            If Not m_bShutDown Then
                .Cell(flexcpText, 1, QUC_SYMBOL + 1, 1, .Cols - 1) = ""
                .TextMatrix(m_nUndMainRow, QUC_SYMBOL) = sSymbol
                
                m_Aux.FormatUndGrid
                m_Aux.FormatUndColumns
            End If
        
            m_Aux.GridLock(GT_QUOTES_UNDERLYING).UnlockRedraw
        End With
        
        With fgFut
            m_Aux.GridLock(GT_QUOTES_FUTURES).LockRedraw
            
            .Rows = 1
            fgFut.FlexDataSource = Nothing
            'RefreshOptsGrid
            m_Aux.FormatFutGrid
            m_Aux.FormatFutColumns
            
            m_Aux.GridLock(GT_QUOTES_FUTURES).UnlockRedraw
        End With
        
        With fgOpt
            m_Aux.GridLock(GT_QUOTES_OPTIONS).LockRedraw
            
            .Rows = 1
            fgOpt.FlexDataSource = Nothing
            'RefreshOptsGrid
            m_Aux.FormatOptGrid
            m_Aux.FormatOptColumns
            
            m_Aux.GridLock(GT_QUOTES_OPTIONS).UnlockRedraw
        End With
        
        With fgDiv
            m_Aux.GridLock(GT_QUOTES_DIVIDENDS).LockRedraw
            
            .Cols = QDC_LAST_COLUMN
            .TextMatrix(1, QDC_TRADES) = m_Aux.TradesFilter
            .TextMatrix(1, QDC_OPTIONS) = "1"
            .TextMatrix(1, QDC_MODEL) = g_Params.CalcModelName(g_Params.CalcModel)
            .TextMatrix(1, QDC_STYLE) = "1"
            .TextMatrix(1, QDC_FREQ) = "0"
            .TextMatrix(1, QDC_DIV) = "0"
            .TextMatrix(1, QDC_FREQ) = "0"
            .TextMatrix(1, QDC_DATE) = ""
            .TextMatrix(1, QDC_AMT) = ""
            .TextMatrix(1, QDC_RATE) = "0"
            
            .ColHidden(QDC_DATE) = True
            .ColHidden(QDC_AMT) = True
            .ColHidden(QDC_OPTIONS) = True
        
            m_Aux.FormatDivGrid
            m_Aux.FormatDivColumns
            
            m_Aux.FormatVolGrid
            m_Aux.FormatVolColumns
            
            m_Aux.GridLock(GT_QUOTES_DIVIDENDS).UnlockRedraw
        End With
    Else
      fgOpt.FlexDataSource = Nothing
      fgFut.Rows = 1
      fgUnd.Rows = 2
    End If
   
    
    fgOpt.FlexDataSource = Nothing
    QV.CleanUp False
    
    AdjustCaption
    RaiseEvent OnExpiriesChange(False)
    RaiseEvent OnOptRootsChange(False)
    RaiseEvent OnOptExchangesChange(False)
    RaiseEvent OnUndExchangesChange(False)
    RaiseEvent OnFutChange(False)
    RaiseEvent OnStrikesChange
    AdjustState
    UserControl_Resize
End Sub

Private Sub RequestLastQuotes()
    On Error GoTo EH
    Dim aParam As PRICEPROVIDERSLib.QuoteUpdateParams, sExch$, aReq As MmQvRequestAtom
    Dim aExch As EtsGeneralLib.ExchAtom, aUnd As EtsMmQuotesLib.MmQvUndAtom
    
    If Not PriceProvider Is Nothing Then
        Debug.Assert Not m_bLastQuoteReqNow
        
        If Not g_PerformanceLog Is Nothing Then _
            m_nOperation = g_PerformanceLog.BeginLogMmOperation

        QV.UndResponses = 0
        QV.OptResponses = 0
        QV.FutResponses = 0
        
        m_DecExpectations = 0
        
        If m_Aux.QuoteReqsAll.Count > 0 Then
            m_bInProc = True
            m_bLastQuoteReqNow = True
            AdjustState
            
            m_bGroupRequest = m_bGroupRequestSupported And (m_Aux.Grp.IsStockOrIndex) And Not g_Params.QuoteReqTypeAlwaysNonGroup
            
            m_nQuoteReqDone = 0&
            m_nVisibleRequestDone = 0&
            
            pbProgress.Min = 0
            pbProgress.Value = 0
            
            pbProgress.Max = m_Aux.QuoteReqsAll.Count
            pbProgress.Visible = True
            
            lblStatus.Visible = False
            lblProcess.Visible = True
            lblProcess.Caption = "Last quotes request..."
            lblProcess.Refresh
            imgStop.Visible = True
            imgStopDis.Visible = False
            
            If Not m_bGroupRequest Then
                m_nQuoteGroupReqCount = 0&
                m_nQuoteGroupReqDone = 0&
                
                QV.RequestLastQuotes
                            
                pbProgress.Max = m_Aux.QuoteReqsAll.VisibleRequests
                
            Else
                aParam.Symbol = m_Aux.Grp.Und.Symbol
                aParam.Type = IIf(m_Aux.Grp.Und.UndType = enCtStock, enSTK, enIDX)
                
                m_nQuoteGroupReqCount = m_Aux.Grp.Und.UndExch.Count + 1
                m_nQuoteGroupReqDone = 0&
                
                For Each aExch In m_Aux.Grp.Und.UndExch
                    If m_bShutDown Or Not m_bLastQuoteReqNow Then Exit For
                    aParam.Exchange = aExch.Code
                    PriceProvider.RequestLastQuote aParam
                    DoEvents
                Next
                
                If Not m_bShutDown And m_bLastQuoteReqNow And Not m_Aux.Grp.Und.SynthUnd Is Nothing Then
                    
                    For Each aUnd In m_Aux.Grp.Und.SynthUnd
                        If aUnd.ID <> USD_ID Then
                            m_nQuoteGroupReqCount = m_nQuoteGroupReqCount + aUnd.UndExch.Count
                            
                            aParam.Symbol = aUnd.Symbol
                            aParam.Type = IIf(aUnd.UndType = enCtStock, enSTK, enIDX)
                            
                            For Each aExch In aUnd.UndExch
                                If m_bShutDown Or Not m_bLastQuoteReqNow Then Exit For
                                                                
                                aParam.Exchange = aExch.Code
                                PriceProvider.RequestLastQuote aParam
                                DoEvents
                            Next
                        End If
                    Next
                End If
                aParam.Symbol = m_Aux.Grp.Und.Symbol
                aParam.Type = IIf(m_Aux.Grp.Und.UndType = enCtStock, enSTK, enIDX)
                
                If Not m_bShutDown And m_bLastQuoteReqNow Then
                    sExch = ""
                    
                    For Each aExch In m_Aux.Grp.Und.OptExch
                        If aExch.ID <> 0 Then sExch = sExch & "," & aExch.Code
                    Next
                    
                    aParam.Exchange = sExch
                    aParam.Type = IIf(m_Aux.Grp.Und.UndType = enCtStock, enGrSTK, enGrIDX)
                    m_GroupPriceProvider.RequestLastGroupQuotes aParam
                End If
                
            End If
            
            m_bInProc = False
            AdjustState
        Else
            pbProgress.Visible = False
            lblStatus.Visible = True
            lblProcess.Visible = False
            lblProcess.Caption = ""
            imgStop.Visible = False
            imgStopDis.Visible = False
        End If
    Else
        pbProgress.Visible = False
        lblStatus.Visible = True
        lblProcess.Visible = False
        lblProcess.Caption = ""
        imgStop.Visible = False
        imgStopDis.Visible = False
        If Not m_bShutDown Then gCmn.MyMsgBox m_frmOwner, "You are in offline mode now.", vbExclamation
    End If
    Exit Sub
EH:
    m_bLastQuoteReqNow = False
    m_bInProc = False
    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to request last quotes."
    On Error Resume Next
    pbProgress.Visible = False
    lblStatus.Visible = True
    lblProcess.Visible = False
    lblProcess.Caption = ""
    imgStop.Visible = False
    imgStopDis.Visible = False
    AdjustState
    
    PriceProvider.CancelLastQuote
    If m_bGroupRequest Then m_GroupPriceProvider.CancelLastGroupQuotes

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.FinishLogMmOperation m_nOperation, OPER_REQUESTQUOTE, m_frmOwner.GetCaption, QV.UndResponses, QV.OptResponses, QV.FutResponses
End Sub

Private Sub CheckRtCount()
    Dim aForm As clsFormAtom
    Dim nRtCount As Long
    Dim i As Long
   
    nRtCount = 0&
   
    For i = 1 To g_ViewFrm.Count
        Set aForm = g_ViewFrm(i)
        If TypeOf aForm.Frm Is frmQuotesViewSingle Then
            If aForm.Frm.IsRealTime Then
                nRtCount = nRtCount + 1
            End If
            Set aForm = Nothing
        End If
    Next
    g_RTQuantity = nRtCount
    
    Debug.Print "Count of RT Quotes windows: " & Str(nRtCount)
    
End Sub

Private Sub PriceProvider_OnError(ByVal ErrorNumber As PRICEPROVIDERSLib.ErrorNumberEnum, ByVal Description As String, ByVal ReqType As PRICEPROVIDERSLib.RequestsTypeEnum, ByVal Request As Variant)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim sKey$, bFinished As Boolean, nTime&
    Dim nOpts&, nFuts&, nUnds&, nOperation&, nLogTime&
    Dim aReq As MmQvRequestAtom
    If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "On Error: " & Description & " For " & Request.Symbol & " - " & Request.Exchange & " - " & Request.Type, m_frmOwner.GetCaption
    
    Dim bFinishedAll As Boolean
    Dim nRequests As Long
    
    bFinished = False
    bFinishedAll = False
    nRequests = m_Aux.QuoteReqsAll.VisibleRequests
    pbProgress.Max = nRequests
    
    
    If ReqType = enSubscribeQuote Then
        If Not Request Is Nothing And m_bSubscribingNow Then
            sKey = Request.Symbol
            If Len(Request.Exchange) > 0 Then
                sKey = sKey & "." & Request.Exchange
            End If
            
            If Not m_Aux.QuoteReqsAll(sKey) Is Nothing Then
                LogEvent EVENT_WARNING, sKey & ": " & Description
                
            End If
            
            m_nQuoteReqDone = m_nQuoteReqDone + 1

            IncProgress pbProgress
            
            bFinished = (m_nQuoteReqDone = nRequests)
            bFinishedAll = (m_nQuoteReqDone = QV.QuoteReqsAll.Count)
            

            If bFinished Then
                
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.FinishLogMmOperation m_nOperation, OPER_SUBSCRIBEQUOTE, m_frmOwner.GetCaption, QV.UndResponses, QV.OptResponses, QV.FutResponses
            
                If tmrPriceProviderIdle.Enabled = True Then tmrPriceProviderIdle.Enabled = False
                tmrPriceProviderIdle.Enabled = True
                
                m_nVisibleRequestDone = -1&
                pbProgress.Visible = False
                lblStatus.Visible = True
                lblProcess.Visible = False
                lblProcess.Caption = ""
                imgStopDis.Visible = False
                imgStop.Visible = False
                
                m_Aux.RealTime = True
                m_Aux.RealTimeConnected = True
                If m_BatchPriceProvider.IsQuotesUpdated Then tmrRealTime.Enabled = True
                
                UpdateTotals
                AdjustState
                AdjustCaption
                
                g_RTNumber = g_RTNumber + 1
                CheckRtCount
                m_frmOwner.lRTNum = g_RTNumber
                If g_RTQuantity > g_MaxRTQuantity Then
                    frmMain.StopExtraRT
                End If
                CheckRtCount
            ElseIf m_nQuoteReqDone > nRequests Then
                If tmrPriceProviderIdle.Enabled = True Then tmrPriceProviderIdle.Enabled = False
                tmrPriceProviderIdle.Enabled = True
            
            End If
            
            If bFinishedAll Then
                tmrPriceProviderIdle.Enabled = False
                m_bSubscribingNow = False
                PriceProvider.CancelLastQuote
                AdjustState
            End If
                        
        End If
    
    ElseIf ReqType = enRequestLastQuote Then
        If Not Request Is Nothing And m_bLastQuoteReqNow Then
            sKey = Request.Symbol
            
            If Len(Request.Exchange) > 0 Then
                sKey = sKey & "." & Request.Exchange
            End If
            
            ' Future options symbology has not been changed for Globex's symbols yet,
            ' so that's no need to write about it as about an error... I suppose...
            If Request.Type <> enFOP Or Request.Exchange <> "G" Then

                m_DecExpectations = m_DecExpectations + 1
                
                If Not m_Aux.QuoteReqsAll(sKey) Is Nothing Then
                    LogEvent EVENT_WARNING, sKey & ": " & Description
                End If
                                                            Else
                '    m_nQuoteReqCount = m_nQuoteReqCount - 1
                    
            End If
            
            m_nQuoteReqDone = m_nQuoteReqDone + 1
            
            
            
            Set aReq = m_Aux.QuoteReqsAll(sKey)
            If Not aReq Is Nothing Then
                If aReq.Visible Then
                    m_nVisibleRequestDone = m_nVisibleRequestDone + 1
                    IncProgress pbProgress
                End If
            End If
            
            bFinished = (m_nVisibleRequestDone = nRequests)
            bFinishedAll = (m_nQuoteReqDone = QV.QuoteReqsAll.Count)
        
            If bFinished Then
                Debug.Print "OnError: Finished = True:  tmrQuoteCalculation.Enabled = True"
                If tmrPriceProviderIdle.Enabled = True Then tmrPriceProviderIdle.Enabled = False
                tmrPriceProviderIdle.Enabled = True
                m_nVisibleRequestDone = m_nVisibleRequestDone + 1
                pbProgress.Value = pbProgress.Max
                imgStop.Visible = False
                imgStopDis.Visible = True
                tmrQuoteCalculation.Enabled = True
            ElseIf m_nQuoteReqDone > nRequests Then
                If tmrPriceProviderIdle.Enabled = True Then tmrPriceProviderIdle.Enabled = False
                tmrPriceProviderIdle.Enabled = True
            End If
            
            If bFinishedAll Then
                tmrPriceProviderIdle.Enabled = False
                m_bLastQuoteReqNow = False
                PriceProvider.CancelLastQuote
                AdjustState
            End If
        End If
    Else
        Select Case ErrorNumber
            Case enProviderConnected
                m_Aux.RealTimeConnected = True
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogFaults, Description, m_frmOwner.GetCaption
               AdjustState
                
            Case enProviderConnecting
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogFaults, Description, m_frmOwner.GetCaption

                
            Case enConnectionWasDisconnected, enCouldNotConnectToProvider, enNotConnected
                m_Aux.RealTimeConnected = False
                If Not g_PerformanceLog Is Nothing Then _
                    g_PerformanceLog.LogMmInfo enLogFaults, Description, m_frmOwner.GetCaption
                AdjustState
                
            Case Else
                LogEvent EVENT_ERROR, Description
        End Select
    End If
End Sub

Private Sub PriceProvider_OnLastQuote(Params As PRICEPROVIDERSLib.QuoteUpdateParams, Results As PRICEPROVIDERSLib.QuoteUpdateInfo)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If Not m_bLastQuoteReqNow Then Exit Sub
    
    Dim sKey$, aReq As MmQvRequestAtom, aQuote As EtsMmQuotesLib.MmQvQuoteAtom, bFinished As Boolean, nTime&
    Dim nOpts&, nUnds&, aOpt As EtsMmQuotesLib.MmQvOptAtom, aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim nOperation&, nLogTime&, nFuts&
    Dim bFinishedAll As Boolean
    Dim nRequests As Long
    
    bFinished = False
    bFinishedAll = False
    nRequests = m_Aux.QuoteReqsAll.VisibleRequests
    pbProgress.Max = nRequests

    
    If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "On Last Quote: " & Params.Symbol & " - " & Params.Exchange & " - " & Params.Type, m_frmOwner.GetCaption
    
    QV.Quote(Params) = Results
    
    'Debug.Print "Ask: " & Str(Results.AskPrice) & " Bid: " & Str(Results.BidPrice) & " Last: " & Str(Results.LastPrice) & " " & Params.Symbol
    sKey = Params.Symbol
    If Len(Params.Exchange) > 0 Then
        sKey = sKey & "." & Params.Exchange
    End If
           
    Set aReq = m_Aux.QuoteReqsAll(sKey)
    If Not aReq Is Nothing Then
        If aReq.Visible Then
            m_nVisibleRequestDone = m_nVisibleRequestDone + 1
            IncProgress pbProgress
        End If
    End If
        
    m_nQuoteReqDone = m_nQuoteReqDone + 1
    bFinished = (m_nVisibleRequestDone = nRequests)
    bFinishedAll = (m_nQuoteReqDone = QV.QuoteReqsAll.Count)
    
    If bFinished Then
        pbProgress.Value = pbProgress.Max
        imgStop.Visible = False
        imgStopDis.Visible = True
        m_nVisibleRequestDone = m_nVisibleRequestDone + 1
        Debug.Print "OnLastQuote: Finished = True:  tmrQuoteCalculation.Enabled = True"
        tmrQuoteCalculation.Enabled = True
        If tmrPriceProviderIdle.Enabled = True Then tmrPriceProviderIdle.Enabled = False
                   tmrPriceProviderIdle.Enabled = True
        
            
    ElseIf m_nQuoteReqDone > nRequests Then
        If tmrPriceProviderIdle.Enabled = True Then tmrPriceProviderIdle.Enabled = False
        tmrPriceProviderIdle.Enabled = True
    End If
    If bFinishedAll Then
        tmrPriceProviderIdle.Enabled = False
        m_bLastQuoteReqNow = False
        PriceProvider.CancelLastQuote
        AdjustState
        RaiseEvent OnScreenRefresh
    End If
End Sub
Private Sub PriceProvider_OnSubscribed(Params As PRICEPROVIDERSLib.QuoteUpdateParams)
 On Error Resume Next
    If m_bShutDown Or Not m_bSubscribingNow Then Exit Sub
    Dim sKey$, bFinished As Boolean
    Dim lAddition As Long
    Dim bFinishedAll As Boolean
    Dim nRequests As Long
    
    bFinished = False
    bFinishedAll = False
    nRequests = m_Aux.QuoteReqsAll.VisibleRequests
    pbProgress.Max = nRequests
      
    
    lAddition = m_BatchPriceProvider.UnNotifiedSubscribtionQuantity(True) + 1
    IncProgressEx pbProgress, lAddition
    m_nQuoteReqDone = m_nQuoteReqDone + lAddition
    If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "On Subscribed: " & Params.Symbol & " - " & Params.Exchange & " - " & Params.Type & "[" & CStr(lAddition) & "]", m_frmOwner.GetCaption
    
    Debug.Print "Subscribed " & CStr(m_nQuoteReqDone) & " From " & CStr(nRequests) & "( " & CStr(QV.QuoteReqsAll.Count) & " )"
    
    If (m_nQuoteReqDone >= nRequests) Then
        m_nFinSubStep = m_nFinSubStep + 1
        If (m_nFinSubStep = 1) Then bFinished = True
    End If
    
    bFinishedAll = (m_nQuoteReqDone = QV.QuoteReqsAll.Count)
            
    sKey = Params.Symbol
    If Len(Params.Exchange) > 0 Then
        sKey = sKey & "." & Params.Exchange
    End If
 
    If bFinished Then
        Debug.Print "Finished " & CStr(m_nQuoteReqDone) & " From " & CStr(nRequests) & "( " & CStr(QV.QuoteReqsAll.Count) & " )"
 
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.FinishLogMmOperation m_nOperation, OPER_SUBSCRIBEQUOTE, m_frmOwner.GetCaption, QV.UndResponses, QV.OptResponses, QV.FutResponses
        m_BatchPriceProvider.UnNotifiedSubscribtionQuantity True
        
        'If tmrPriceProviderIdle.Enabled = True Then tmrPriceProviderIdle.Enabled = False
        'tmrPriceProviderIdle.Enabled = True

        pbProgress.Visible = False
        lblStatus.Visible = True
        lblProcess.Visible = False
        lblProcess.Caption = ""
        imgStop.Visible = False
        imgStopDis.Visible = False
        
        m_Aux.RealTime = True
        m_Aux.RealTimeConnected = True
        If m_BatchPriceProvider.IsQuotesUpdated Then tmrRealTime.Enabled = True
        
        UpdateTotals
        AdjustState
        AdjustCaption
        
        g_RTNumber = g_RTNumber + 1
        CheckRtCount
        m_frmOwner.lRTNum = g_RTNumber
        If g_RTQuantity > g_MaxRTQuantity Then
            frmMain.StopExtraRT
        End If
        CheckRtCount
        
     ElseIf m_nQuoteReqDone > nRequests Then
        If tmrPriceProviderIdle.Enabled = True Then tmrPriceProviderIdle.Enabled = False
        tmrPriceProviderIdle.Enabled = True
    End If

   If bFinishedAll Then
        m_bSubscribingNow = False
        tmrPriceProviderIdle.Enabled = False
        AdjustState
    End If
    If Not bFinished And m_nQuoteReqDone > nRequests Then
       If m_Aux.RealTime = False Then bFinished = True
    End If
    
End Sub

Private Sub PriceProvider_OnQuoteUpdate()
    On Error Resume Next
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "OnQuoteUpdate", m_frmOwner.GetCaption
        
    If m_bShutDown Then
           If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogEnhDebug, "Did not pass condition: m_bShutDown", m_frmOwner.GetCaption
        
            Exit Sub
    
    End If
    
    If Not m_Aux.RealTime Then
           If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogEnhDebug, "Did not pass condition: Not m_Aux.RealTime", m_frmOwner.GetCaption
                
            Exit Sub
    End If
    

    If m_bSubscribingNow Then
           If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogEnhDebug, "Did not pass condition: m_bSubscribingNow", m_frmOwner.GetCaption
        
            Exit Sub
    
    End If
    
    If Not ProcessRealTime Then
           If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogEnhDebug, "Did not pass condition: Not ProcessRealTime", m_frmOwner.GetCaption
        
'            Exit Sub
    
    End If
    
    If m_BatchPriceProvider Is Nothing Then
           If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogEnhDebug, "Did not pass condition: m_BatchPriceProvider Is Nothing", m_frmOwner.GetCaption
        
            Exit Sub
    End If
    
    If tmrRealTime.Enabled = True Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "Update flag allready raised up", m_frmOwner.GetCaption
    Else
        tmrRealTime.Enabled = True
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "Update flag raised up", m_frmOwner.GetCaption
    End If
    
    RaiseEvent OnScreenRefresh
   
End Sub

Private Sub RealTimeQuotesUpdate()
    On Error Resume Next
    If Not m_Aux.RealTime Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "RealTimeQuotesUpdate: not in Realtime mode", m_frmOwner.GetCaption
        Exit Sub
    End If
    If m_bInProc Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "RealTimeQuotesUpdate: InProc", m_frmOwner.GetCaption
        Exit Sub
    End If
    If m_bInRealTimeCalc Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "RealTimeQuotesUpdate: In Realtime calc", m_frmOwner.GetCaption
        Exit Sub
    End If
'    If m_bSubscribingNow Then
'        If Not g_PerformanceLog Is Nothing Then _
'            g_PerformanceLog.LogMmInfo enLogEnhDebug, "RealTimeQuotesUpdate: Subscribing now", m_frmOwner.GetCaption
'        Exit Sub
'    End If

    If m_BatchPriceProvider Is Nothing Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "RealTimeQuotesUpdate: Price provider is not set", m_frmOwner.GetCaption
        Exit Sub
    End If

    Dim nRow&, sKey$, aReq As MmQvRequestAtom, dBidPrice#, dAskPrice#, dLastPrice#
    Dim aQuote As EtsMmQuotesLib.MmQvQuoteAtom, aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim enCalcIV As EtsMmQuotesLib.MmQvIvCalcEnum, nMask&, nTime&
    Dim Params As PRICEPROVIDERSLib.QuoteUpdateParams, Results As PRICEPROVIDERSLib.QuoteUpdateInfo
    'Dim Infos() As PRICEPROVIDERSLib.QuoteUpdateFullInfo, nLBound&, nUBound&, i&
    Dim bOptUpd As Boolean, bUndUpd As Boolean
    Dim aRoot As EtsMmQuotesLib.MmQvOptRootAtom
    Dim aSynthRoots As New EtsMmQuotesLib.MmQvOptRootColl
    Dim aEntity As EtsGeneralLib.EtsMmEntityAtom
    Dim nOperation&: nOperation = 0
    Dim nOperation2&: nOperation2 = 0
    Dim nUnds&: nUnds = 0
    Dim nOpts&: nOpts = 0
    Dim nFuts&: nFuts = 0
    Dim nLogTime&
    Dim bVolaChangedExt As Boolean: bVolaChangedExt = False
    
    m_bInRealTimeCalc = True
    
    Dim dTimer As Long
    
    If Not g_PerformanceLog Is Nothing Then _
           g_PerformanceLog.LogMmInfo enLogEnhDebug, "Get Quotes Update", m_frmOwner.GetCaption
           
    DoEvents
    If m_bShutDown Then Exit Sub
    
    dTimer = GetTickCount
    QV.LoadQuoteUpdates
    If m_bFiersTealtimeCalculation Then
        fgOpt.Refresh
        lblStatus.Caption = "Calculating..."
        lblStatus.Visible = True
        lblStatus.Refresh
    End If
    
    DoEvents
    If m_bShutDown Then Exit Sub
    
    dTimer = GetTickCount - dTimer
    
    nTime = timeGetTime
    Dim bForceRecalc As Boolean
    
    bForceRecalc = m_bFiersTealtimeCalculation Or m_bForseRecalc
    m_bFiersTealtimeCalculation = False
    m_bForseRecalc = False
    
    If (ProcessRealTime And QV.IsMarketDataChanged) Or bForceRecalc Then
        
        If Not g_PerformanceLog Is Nothing Then nOperation = g_PerformanceLog.BeginLogMmOperation
        
        Dim bIsCanceled As Boolean
        CalculateUnderlyingOptions True, , , , bIsCanceled
        If bIsCanceled Then
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogEnhDebug, "Calculation canceled by user", m_frmOwner.GetCaption
            GoTo Ex
        End If
       bUndUpd = True
      
       DoEvents
       If m_bShutDown Then Exit Sub
        
       If Not g_PerformanceLog Is Nothing Then nLogTime = g_PerformanceLog.CheckLogMmOperation(nOperation)
       m_bCalculationDateChanged = False
    End If
        
    m_nLastRecalcCycle = timeGetTime - nTime
                            
'   Update grid data
    nTime = timeGetTime
                        
    If (ProcessRealTime Or bForceRecalc) And Not m_bShutDown Then
        If Not g_PerformanceLog Is Nothing Then nOperation2 = g_PerformanceLog.BeginLogMmOperation
        
        nUnds = m_AuxOut.UnderlyingUpdate(False, True)
        nOpts = m_AuxOut.OptionsUpdate(False, True, bUndUpd Or bVolaChangedExt)
        nFuts = m_AuxOut.FuturesUpdate(False, True, True)
        
        If bUndUpd Or bVolaChangedExt Then m_AuxOut.VolaUpdateValues
        m_AuxOut.UnderlyingUpdateTotals
        UpdateTotals
    Else
        nUnds = m_AuxOut.UnderlyingUpdate(False, True)
    End If
    m_AuxOut.FuturesUpdateColors
    m_AuxOut.OptionsUpdateColors
    m_nLastOutCycle = timeGetTime - nTime
                        
    If Not g_PerformanceLog Is Nothing Then
        If nOperation > 0 Then _
            g_PerformanceLog.ContinueLogMmOperation nOperation, OPER_CALCULATION, m_frmOwner.GetCaption, nUnds, nOpts, nFuts, nLogTime
        If nOperation2 > 0 Then _
            g_PerformanceLog.FinishLogMmOperation nOperation2, OPER_REFRESHSCREEN, m_frmOwner.GetCaption, nUnds, nOpts, nFuts
        If nOperation > 0 Then _
            g_PerformanceLog.FinishLogMmOperation nOperation, OPER_CALCREFRESHSCREEN, m_frmOwner.GetCaption, nUnds, nOpts, nFuts
    End If
Ex:
    If g_Params.IsDebug Then UpdateStat
    m_bFiersTealtimeCalculation = False
    m_bInRealTimeCalc = False
End Sub

'comment this sub in production for prevent statistic output
Private Sub UpdateStat()
    On Error Resume Next
    Debug.Print Format$(m_nLastDataSize, "#0000") & _
                vbTab & Format$(m_nLastRecalcCycle, "#000000") & _
                vbTab & Format$(m_nLastOutCycle, "#000000") & _
                vbTab & Format$(m_nLastRecalcCycle + m_nLastOutCycle, "#000000")
End Sub


Private Sub UpdateTotals()
    On Error Resume Next
    
    lblStatus.Caption = m_AuxOut.GetTotalsString
    lblStatus.Refresh
    
End Sub

Private Sub CalculateUnderlyingOptions(ByVal bRecalcAll As Boolean, Optional aSynthRoots As EtsMmQuotesLib.MmQvOptRootColl = Nothing, Optional ManualEdit As Boolean = False, _
                                                                    Optional ByVal bForceRecalc As Boolean = False, _
                                                                    Optional ByRef bIsCanceled As Boolean)

    On Error Resume Next
    Dim nCallMask As Long, nPutMask As Long, enCallCalcIV As EtsMmQuotesLib.MmQvIvCalcEnum, enPutCalcIV As EtsMmQuotesLib.MmQvIvCalcEnum
    Dim nCalcSleepFreq&: nCalcSleepFreq = 0&
    Dim nCalcSleepAmt&: nCalcSleepAmt = 0&
    Dim lDayShift As Integer
    Dim sDate As String
    
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
   
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "Calculation Underlying Options Enter.", m_frmOwner.GetCaption

    If bRecalcAll Then
        nCallMask = GetGreeksMask(enOtCall)
        nPutMask = GetGreeksMask(enOtPut)
        enCallCalcIV = GetIvMask(enOtCall)
        enPutCalcIV = GetIvMask(enOtPut)
    Else
        nCallMask = GM_NONE
        nPutMask = GM_NONE
        enCallCalcIV = enMmQvCalcIvNone
        enPutCalcIV = enMmQvCalcIvNone
    End If
    
    If g_Params.UseCalcSleep And g_Params.CalcSleepAmt <> 0 Then
        nCalcSleepFreq = g_Params.CalcSleepFreq
        nCalcSleepAmt = g_Params.CalcSleepAmt
    End If
    
    If Len(dtCalculationDate.Value) Then
           sDate = Format(CDate(dtCalculationDate.Value), "Short Date")
           lDayShift = IIf(m_Aux.RealTime, 0, (CDate(sDate) - Date))
    Else
        lDayShift = 0
    End If
    
    Debug.Print "[Enter] CalculateUnderlyingOptions"
        
    m_Aux.Grp.Und.CalcAllOptions nCallMask, nPutMask, enCallCalcIV, enPutCalcIV, g_Params.CalcModel, _
                            g_Params.UseTheoVolatility, g_Params.UseTheoNoBid, g_Params.UseTheoBadMarketVola, _
                            bRecalcAll, aSynthRoots, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule, _
                            m_Aux.Grp.UseCustRates, nCalcSleepFreq, nCalcSleepAmt, lDayShift, ManualEdit, bForceRecalc
     
    Debug.Print "[Exit] CalculateUnderlyingOptions"
    
    
    bIsCanceled = CBool(Err.Number = ERROR_CANCELLED)
    If Err.Number <> 0 Then
    
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "Calculation Underlying Options Exit with Error: " & CStr(Err.Number) & " " & Err.Description, m_frmOwner.GetCaption
    Else
        m_Aux.Grp.Spread.Calculate (g_Params.QuoteBidColBuy)
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "Calculation Underlying Options Exit.", m_frmOwner.GetCaption
        'fgOpt.Refresh
    End If
End Sub

Private Sub CalcOptionGreeks(aOpt As EtsMmQuotesLib.MmQvOptAtom, aQuote As EtsMmQuotesLib.MmQvQuoteAtom, _
                            aExp As EtsMmQuotesLib.MmQvExpAtom, ByVal nMask As Long, ByVal enCalcIV As EtsMmQuotesLib.MmQvIvCalcEnum, Optional ManualEdit As Boolean = False, _
                            Optional ByVal bRefresh As Boolean = True)
    On Error Resume Next
    
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "Calculation Greeks Enter.", m_frmOwner.GetCaption
    
    Dim aExpColl As EtsMmQuotesLib.MmQvExpColl
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom, aFutForGreeks As EtsMmQuotesLib.MmQvFutAtom
    
    Dim lDayShift As Integer
    Dim sDate As String
    
    If m_Aux.Grp.IsStockOrIndex Then
        Set aExpColl = m_Aux.Grp.Und.Exp
                 sDate = fgVol.TextMatrix(1, QVC_VOLA_VAL + aExpColl.Count)
        If Len(sDate) Then
            lDayShift = IIf(m_Aux.RealTime, 0, (CDate(sDate) - Now))
        Else
            lDayShift = 0
        End If
            
        m_Aux.Grp.Und.CalcOptionGreeks aOpt, aQuote, aExp, m_Aux.Grp.Und.OptRoot(aOpt.RootID), nMask, enCalcIV, g_Params.CalcModel, _
                                    g_Params.UseTheoVolatility, g_Params.UseTheoNoBid, g_Params.UseTheoBadMarketVola, _
                                    g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule, m_Aux.Grp.UseCustRates, lDayShift, ManualEdit
        

    Else
        
        sDate = fgVol.TextMatrix(1, QVC_VOLA_VAL + m_Aux.Grp.ExpAll.Count)
        lDayShift = 0
        
        If Len(sDate) Then lDayShift = IIf(m_Aux.RealTime, 0, (CDate(sDate) - Now))
        
        m_Aux.Grp.Und.CalcFutureOptionGreeks aOpt, aQuote, aExp, nMask, enCalcIV, g_Params.CalcModel, _
                                    g_Params.UseTheoVolatility, g_Params.UseTheoNoBid, g_Params.UseTheoBadMarketVola, _
                                    g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule, m_Aux.Grp.UseCustRates, lDayShift, ManualEdit
                                   
    End If
    
    'fgOpt.Refresh
    If bRefresh Then fgOpt.Refresh
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogEnhDebug, "Calculation Greeks Exit.", m_frmOwner.GetCaption
                            
    'Debug.Assert Err.Number = 0 'fokiny
End Sub

Private Function GetGreeksMask(ByVal nOptType As Long) As Long
    On Error Resume Next
    Dim nShift&
    
    If nOptType = enOtPut Then
        nShift = QOC_P_SYMBOL - 2
    Else
        nShift = 0
    End If
    
    If m_gdOpt.Col(nShift + QOC_C_THEO_PRICE).Visible Then GetGreeksMask = GetGreeksMask Or GM_THEOPRICE
    If m_gdOpt.Col(nShift + QOC_C_DELTA).Visible Then GetGreeksMask = GetGreeksMask Or GM_DELTA
    If m_gdOpt.Col(nShift + QOC_C_GAMMA).Visible Then GetGreeksMask = GetGreeksMask Or GM_GAMMA
    If m_gdOpt.Col(nShift + QOC_C_VEGA).Visible Then GetGreeksMask = GetGreeksMask Or GM_VEGA
    If m_gdOpt.Col(nShift + QOC_C_THETA).Visible Then GetGreeksMask = GetGreeksMask Or GM_THETA
    If m_gdOpt.Col(nShift + QOC_C_RHO).Visible Then GetGreeksMask = GetGreeksMask Or GM_RHO
    If m_gdOpt.Col(nShift + QOC_C_VEGA_DELTA).Visible Then GetGreeksMask = GetGreeksMask Or GM_DELTA_VEGA
    If m_gdOpt.Col(nShift + QOC_C_VEGA_GAMMA).Visible Then GetGreeksMask = GetGreeksMask Or GM_GAMMA_VEGA
    If m_gdOpt.Col(nShift + QOC_C_THETA_DELTA).Visible Then GetGreeksMask = GetGreeksMask Or GM_DELTA_THETA
    If m_gdOpt.Col(nShift + QOC_C_THETA_GAMMA).Visible Then GetGreeksMask = GetGreeksMask Or GM_GAMMA_THETA
    If m_gdOpt.Col(nShift + QOC_C_GAMMA_PER_THETA).Visible Then GetGreeksMask = GetGreeksMask Or GM_GAMMA Or GM_THETA
End Function

Private Function GetIvMask(ByVal nOptType As Long) As EtsMmQuotesLib.MmQvIvCalcEnum
    On Error Resume Next
    Dim nShift&
    GetIvMask = enMmQvCalcIvNone
    
    If nOptType = enOtPut Then
        nShift = QOC_P_SYMBOL - 2
    Else
        nShift = 0
    End If
    
    If g_Params.UseTheoVolatility Then
        'If m_gdOpt.Col(nShift + QOC_C_IV).Visible Then GetIvMask = GetIvMask Or enMmQvCalcIv
        GetIvMask = GetIvMask Or enMmQvCalcIv
    Else
        GetIvMask = GetIvMask Or enMmQvCalcIv
    End If
    
    If Not m_gdOpt.Col(nShift + QOC_C_IV_SPREAD).Visible Then
        If m_gdOpt.Col(nShift + QOC_C_IV_BID).Visible Then GetIvMask = GetIvMask Or enMmQvCalcIvBid
        If m_gdOpt.Col(nShift + QOC_C_IV_ASK).Visible Then GetIvMask = GetIvMask Or enMmQvCalcIvAsk
    Else
        GetIvMask = GetIvMask Or enMmQvCalcIvBid Or enMmQvCalcIvAsk
    End If
End Function

Private Function UnderlyingAdjustRates(ByVal bForceUpdateCustom As Boolean) As Boolean
    On Error Resume Next
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, bUseMidRates As Boolean, cPosThreshold@, dPos#
    Dim bForceRateUpdate As Boolean, aExpColl As EtsMmQuotesLib.MmQvExpColl
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim aExpAll As EtsMmQuotesLib.MmQvExpAtom
    
    UnderlyingAdjustRates = False
    If m_Aux.Grp.ID = 0 Then Exit Function
    
    bForceRateUpdate = False
    
    dPos = g_UnderlyingAll(m_Aux.Grp.Und.ID).UndPosForRates
    
    If GetIrRuleType = enRateBasedOnPosition Then
        cPosThreshold = Abs(GetPosThreshold)
        bUseMidRates = (cPosThreshold = 0 Or cPosThreshold <> 0 And Abs(dPos) <= cPosThreshold)
    
        If Not bUseMidRates Then _
            bForceRateUpdate = (Sgn(dPos) * Sgn(m_Aux.Grp.Und.UndPosForRates) < 0)
    
    Else
        bUseMidRates = True
    End If
    
    If bForceUpdateCustom Or m_Aux.Grp.Und.UseMidRates <> bUseMidRates Or bForceRateUpdate Then
        m_Aux.Grp.Und.UseMidRates = bUseMidRates
        m_Aux.Grp.Und.UndPosForRates = dPos
        
        If m_Aux.Grp.IsStockOrIndex Then
            Set aExpColl = m_Aux.Grp.Und.Exp
            For Each aExp In aExpColl
                If bUseMidRates Then
                    If Not m_Aux.Grp.Und.IsHTB Then
                        aExp.Rate = GetNeutralRate(Date, aExp.Expiry)
                    Else
                        aExp.Rate = GetNeutralHTBRate(Date, aExp.Expiry)
                    End If
                Else
                    If Not m_Aux.Grp.Und.IsHTB Then
                        aExp.Rate = IIf(dPos < 0#, GetShortRate(Date, aExp.Expiry), GetLongRate(Date, aExp.Expiry))
                    Else
                        aExp.Rate = IIf(dPos < 0#, GetHTBRate(Date, aExp.Expiry), GetLongRate(Date, aExp.Expiry))
                    End If
                End If
                
                If bForceUpdateCustom Or Not m_Aux.Grp.UseCustRates Then
                    If QV.CustRates(CStr(CLng(aExp.ExpiryMonth))) Is Nothing Then
                        aExp.RateCust = aExp.Rate
                    Else
                        aExp.RateCust = QV.CustRates(CStr(CLng(aExp.ExpiryMonth))).Data3
                    End If
                End If
            Next

        Else
            For Each aExp In m_Aux.Grp.ExpAll
                    If bUseMidRates Then
                        If Not m_Aux.Grp.Und.IsHTB Then
                            aExp.Rate = GetNeutralRate(Date, aExp.Expiry)
                        Else
                            aExp.Rate = GetNeutralHTBRate(Date, aExp.Expiry)
                        End If
                    Else
                        If Not m_Aux.Grp.Und.IsHTB Then
                            aExp.Rate = IIf(dPos < 0#, GetShortRate(Date, aExp.Expiry), GetLongRate(Date, aExp.Expiry))
                        Else
                            aExp.Rate = IIf(dPos < 0#, GetHTBRate(Date, aExp.Expiry), GetLongRate(Date, aExp.Expiry))
                        End If
                    End If
                    
                    If bForceUpdateCustom Or Not m_Aux.Grp.UseCustRates Then
                        If QV.CustRates(CStr(CLng(aExp.ExpiryMonth))) Is Nothing Then
                            aExp.RateCust = aExp.Rate
                        Else
                            aExp.RateCust = QV.CustRates(CStr(CLng(aExp.ExpiryMonth))).Data3
                        End If
                    End If
            Next
            For Each aExpAll In m_Aux.Grp.ExpAll
                For Each aFut In m_Aux.Grp.Und.Fut
                    For Each aExp In aFut.Exp
                        If aExpAll.ExpiryMonth = aExp.ExpiryMonth Then
                            aExp.RootNames = aExpAll.RootNames
                            aExp.Rate = aExpAll.Rate
                            aExp.RateCust = aExpAll.RateCust
                        End If
                    Next
                Next
            Next
        End If
        
        
        UnderlyingAdjustRates = True
    End If
End Function



Private Sub AcceptTrade(aTrd As EtsMmGeneralLib.MmTradeInfoAtom, bAddTrade As Boolean, bRecalc As Boolean)
    On Error Resume Next
    Dim aOpt As EtsMmQuotesLib.MmQvOptAtom, nRow&, nBS&, bUpdate As Boolean, dtExpiryMonth As Date
    Dim bRecalcOption As Boolean, aExp As EtsMmQuotesLib.MmQvExpAtom, bRatesUpdated As Boolean
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim bUpdatePos As Boolean
    
    If g_CurTraderID <> 0 And aTrd.Trader.ID <> g_CurTraderID Or m_Aux.Grp.Und.ID <> aTrd.UndID Then Exit Sub
    
    bUpdate = False
    bRatesUpdated = False
    bRecalcOption = False
    bUpdatePos = m_Aux.CheckTradeFilter(aTrd)
    
    If aTrd.ContractType = enCtIndex Or aTrd.ContractType = enCtStock Then
        bRatesUpdated = UnderlyingAdjustRates(False) And Not m_Aux.Grp.UseCustRates
        If bRatesUpdated Then
            m_AuxOut.RatesUpdate
            m_Aux.AdjustDivsAndRatesVisible
            m_Aux.Grp.Und.SetDirty
        End If
    End If
        
    If bAddTrade Then
        nBS = IIf(aTrd.IsBuy, 1, -1)
    Else
        nBS = IIf(aTrd.IsBuy, -1, 1)
    End If
    
    If bUpdatePos Then
            If aTrd.ContractType = enCtOption Then
                dtExpiryMonth = DateSerial(Year(aTrd.Opt.Expiry), Month(aTrd.Opt.Expiry), 1)
                
                Set aExp = m_Aux.Grp.Und.Exp(dtExpiryMonth)
                Set aOpt = m_Aux.Grp.Und.Opt(aTrd.ContractID)
                If Not aOpt Is Nothing Then
                    If aOpt.ID <> 0 Then
                        If aOpt.Qty <= BAD_LONG_VALUE Then
                            aOpt.Qty = 0
                            bRecalcOption = True
                        End If
                        aOpt.Qty = aOpt.Qty + aTrd.Quantity * nBS
                        If aOpt.QtyInShares <= BAD_LONG_VALUE Then aOpt.QtyInShares = 0
                        aOpt.QtyInShares = aOpt.QtyInShares + aTrd.Quantity * aTrd.LotSize * nBS
                        bUpdate = True
                    End If
                End If
                
            ElseIf aTrd.ContractType = enCtIndex Or aTrd.ContractType = enCtStock Then
                If m_Aux.Grp.Und.Qty <= BAD_LONG_VALUE Then m_Aux.Grp.Und.Qty = 0
                m_Aux.Grp.Und.Qty = m_Aux.Grp.Und.Qty + aTrd.Quantity * nBS
                
                If m_Aux.Grp.Und.QtyInShares <= BAD_LONG_VALUE Then m_Aux.Grp.Und.QtyInShares = 0
                m_Aux.Grp.Und.QtyInShares = m_Aux.Grp.Und.QtyInShares + aTrd.Quantity * aTrd.LotSize * nBS
            
                bUpdate = True
        ElseIf aTrd.ContractType = enCtFutOption Then
                dtExpiryMonth = DateSerial(Year(aTrd.FutOpt.Expiry), Month(aTrd.FutOpt.Expiry), 1)
                
                Set aFut = m_Aux.Grp.Und.Fut(aTrd.FutID)
                If Not aFut Is Nothing Then
                    Set aExp = aFut.Exp(dtExpiryMonth)
                    Set aOpt = aFut.Opt(aTrd.ContractID)
                    If Not aOpt Is Nothing Then
                        If aOpt.ID <> 0 Then
                            If aOpt.Qty <= BAD_LONG_VALUE Then
                                aOpt.Qty = 0
                                bRecalcOption = True
                            End If
                            aOpt.Qty = aOpt.Qty + aTrd.Quantity * nBS
                            If aOpt.QtyInShares <= BAD_LONG_VALUE Then aOpt.QtyInShares = 0
                            aOpt.QtyInShares = aOpt.QtyInShares + aTrd.Quantity * aTrd.LotSize * nBS
                            bUpdate = True
                        End If
                    End If
               End If
            ElseIf aTrd.ContractType = enCtFuture Then
                Set aFut = m_Aux.Grp.Und.Fut(aTrd.FutID)
                If Not aFut Is Nothing Then
                    If aFut.Qty <= BAD_LONG_VALUE Then aFut.Qty = 0
                    aFut.Qty = aFut.Qty + aTrd.Quantity * nBS
                    bRecalcOption = True
                    
                    If aFut.QtyInShares <= BAD_LONG_VALUE Then aFut.QtyInShares = 0
                    aFut.QtyInShares = aFut.QtyInShares + aTrd.Quantity * aTrd.LotSize * nBS
                    bUpdate = True
                
                End If
                
            
'                If m_Aux.Grp.Fut.Qty <= BAD_LONG_VALUE Then m_Aux.Grp.Fut.Qty = 0
'                m_Aux.Grp.Fut.Qty = m_Aux.Grp.Fut.Qty + aTrd.Quantity * nBS
'
'                If m_Aux.Grp.Fut.QtyInShares <= BAD_LONG_VALUE Then m_Aux.Grp.Fut.QtyInShares = 0
'                m_Aux.Grp.Fut.QtyInShares = m_Aux.Grp.Fut.QtyInShares + aTrd.Quantity * aTrd.LotSize * nBS
'
'                bUpdate = True
            End If
        End If
    
    If bRecalc And (bUpdate Or bRatesUpdated) Then
        tmrTradesProcessing.Enabled = True
    End If
    
'    If bRecalc Then
'        If (bUpdate Or bRatesUpdated) Then
'            Screen.MousePointer = vbHourglass
'
'            If bUpdate And (aTrd.ContractType = enCtOption Or aTrd.ContractType = enCtFutOption) Then
'                Dim sKey$: sKey = aOpt.Symbol
'                Dim nMask&
'
'                'If m_Aux.Grp.IsStockOrIndex Then
'                    If m_Aux.Grp.Und.OptPosExchID <> 0 Then
'                        sKey = sKey & "." & m_Aux.Grp.OptExchAll(m_Aux.Grp.Und.OptPosExchID).Code
'                    End If
'
'                    nRow = fgOpt.FindRow(sKey, , IIf(aOpt.OptType = enOtCall, QOC_C_KEY, QOC_P_KEY))
'                    fgOpt.RowHidden(nRow) = False
'                    bRecalcOption = True
'
'                    If bRecalcOption Then
'                        nMask = GetGreeksMask(aOpt.OptType) Or GM_THEOPRICE Or GM_DELTA Or GM_GAMMA Or GM_VEGA Or GM_THETA Or GM_RHO
'
'                        CalcOptionGreeks aOpt, aOpt.Quote(0), aExp, nMask, enMmQvCalcIv
'                    End If
'
'                    CalculateUnderlyingOptions False
'
'        '            m_AuxOut.OptionUpdateQuote nRow, aOpt.OptType, False, False, True
'
'                'Else
'                    Set aFut = m_Aux.Grp.Und.Fut(aTrd.FutID)
'                    If Not aFut Is Nothing Then
'                        If aFut.OptPosExchID <> 0 Then
'                            sKey = sKey & "." & m_Aux.Grp.OptExchAll(aFut.OptPosExchID).Code
'                        End If
'
'                        nRow = fgFut.FindRow(sKey, , IIf(aOpt.OptType = enOtCall, QOC_C_KEY, QOC_P_KEY))
'                        fgFut.RowHidden(nRow) = False
'
'                        If bRecalcOption Then
'                            nMask = GetGreeksMask(aOpt.OptType) Or GM_THEOPRICE Or GM_DELTA Or GM_GAMMA Or GM_VEGA Or GM_THETA Or GM_RHO
'
'                            CalcOptionGreeks aOpt, aOpt.Quote(0), aExp, nMask, enMmQvCalcIv
'                        End If
'
'                        CalculateUnderlyingOptions False
'                        m_AuxOut.UnderlyingUpdateQuote 1, False, False
'                        If bRatesUpdated Then
'                            m_AuxOut.FuturesUpdate False, True, True
'                            m_AuxOut.OptionsUpdate False, True, True
'                        ElseIf bUpdate Then
'                            m_AuxOut.FuturesUpdate False, True, True
'                        End If
'
'
'            '            m_AuxOut.OptionUpdateQuote nRow, aOpt.OptType, False, False, True
'                   End If
'
'            ElseIf bUpdate And (aTrd.ContractType = enCtFuture) Then
'                        sKey = aFut.Symbol
'                        If aFut.OptPosExchID <> 0 Then
'                            sKey = sKey & "." & m_Aux.Grp.OptExchAll(aFut.OptPosExchID).Code
'                        End If
'
'                        nRow = fgFut.FindRow(sKey, , QOF_KEY)
'                        fgFut.RowHidden(nRow) = False
'
'                        If bRecalcOption Then
'                            nMask = GetGreeksMask(aOpt.OptType) Or GM_THEOPRICE Or GM_DELTA Or GM_GAMMA Or GM_VEGA Or GM_THETA Or GM_RHO
'
'                            CalcOptionGreeks aOpt, aOpt.Quote(0), aExp, nMask, enMmQvCalcIv
'                        End If
'
'                        CalculateUnderlyingOptions False
'                End If
'
'                CalculateUnderlyingOptions bRatesUpdated
'                m_AuxOut.UnderlyingUpdateQuote 1, False, False
'                If bRatesUpdated Then
'                    m_AuxOut.FuturesUpdate False, True, True
'                    m_AuxOut.OptionsUpdate False, True, True
'                ElseIf bUpdate And (aTrd.ContractType = enCtFuture) Then
'                    m_AuxOut.FuturesUpdate False, True, True
'                End If
'            End If
'
'            m_AuxOut.UnderlyingUpdateTotals
'            UpdateTotals
'
'            Screen.MousePointer = vbDefault
'        End If
    'End If
    Set aExp = Nothing
    Set aOpt = Nothing
End Sub

'Private Sub UpdateTrade(aNewTrd As EtsMmGeneralLib.MmTradeInfoAtom, aOldTrd As EtsMmGeneralLib.MmTradeInfoAtom)
'    On Error Resume Next
'    Dim aOpt As EtsMmQuotesLib.MmQvOptAtom, nRow&, nNewBS&, nOldBS&, bUpdate As Boolean, dtExpiryMonth As Date
'    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
'    Dim bRecalcOption As Boolean, aExp As EtsMmQuotesLib.MmQvExpAtom, bRatesUpdated As Boolean
'    Dim bAddPos As Boolean, bDelPos As Boolean
'
'    Debug.Assert aNewTrd.ContractID = aOldTrd.ContractID
'
'    If m_Aux.Grp.Und.ID <> aNewTrd.UndID Or m_Aux.Grp.Und.ID <> aOldTrd.UndID Then Exit Sub
'
'    bRecalcOption = False
'    bUpdate = False
'    bRatesUpdated = False
'
'    bAddPos = m_Aux.CheckTradeFilter(aNewTrd)
'    bDelPos = m_Aux.CheckTradeFilter(aOldTrd)
'
'    If aNewTrd.ContractType = enCtIndex Or aNewTrd.ContractType = enCtStock _
'        Or aOldTrd.ContractType = enCtIndex Or aOldTrd.ContractType = enCtStock Then
'
'        bRatesUpdated = UnderlyingAdjustRates(False) And Not m_Aux.Grp.UseCustRates
'        If bRatesUpdated Then
'            m_AuxOut.RatesUpdate
'            m_Aux.AdjustDivsAndRatesVisible
'        End If
'    End If
'
'    nNewBS = IIf(aNewTrd.IsBuy, 1, -1)
'    nOldBS = IIf(aOldTrd.IsBuy, 1, -1)
'
'    If bAddPos Or bDelPos Then
'        If m_Aux.Grp.IsStockOrIndex Then
'            If aNewTrd.ContractType = enCtOption Then
'
'                dtExpiryMonth = DateSerial(Year(aNewTrd.Opt.Expiry), Month(aNewTrd.Opt.Expiry), 1)
'
'                Set aExp = m_Aux.Grp.Und.Exp(dtExpiryMonth)
'                Set aOpt = m_Aux.Grp.Und.Opt(aNewTrd.ContractID)
'                If Not aOpt Is Nothing Then
'                    If aOpt.ID <> 0 Then
'                        If bAddPos And bDelPos And (g_CurTraderID = 0 Or aOldTrd.Trader.ID = g_CurTraderID) Then
'                            If aOpt.Qty <= BAD_LONG_VALUE Then
'                                aOpt.Qty = 0
'                                bRecalcOption = True
'                            End If
'                            aOpt.Qty = aOpt.Qty - aOldTrd.Quantity * nOldBS + aNewTrd.Quantity * nNewBS
'                            If aOpt.QtyInShares <= BAD_LONG_VALUE Then aOpt.QtyInShares = 0
'                            aOpt.QtyInShares = aOpt.QtyInShares - aOldTrd.Quantity * aOldTrd.LotSize * nOldBS + aNewTrd.Quantity * aNewTrd.LotSize * nNewBS
'                            bUpdate = True
'                        End If
'
'                        If bDelPos And Not bAddPos And (g_CurTraderID = 0 Or aNewTrd.Trader.ID = g_CurTraderID) Then
'                            If aOpt.Qty <= BAD_LONG_VALUE Then
'                                aOpt.Qty = 0
'                                bRecalcOption = True
'                            End If
'                            aOpt.Qty = aOpt.Qty - aOldTrd.Quantity * nOldBS
'                            If aOpt.QtyInShares <= BAD_LONG_VALUE Then aOpt.QtyInShares = 0
'                            aOpt.QtyInShares = aOpt.QtyInShares - aOldTrd.Quantity * aOldTrd.LotSize * nOldBS
'                            bUpdate = True
'                        End If
'
'                        If Not bDelPos And bAddPos And (g_CurTraderID = 0 Or aNewTrd.Trader.ID = g_CurTraderID) Then
'                            If aOpt.Qty <= BAD_LONG_VALUE Then
'                                aOpt.Qty = 0
'                                bRecalcOption = True
'                            End If
'                            aOpt.Qty = aOpt.Qty + aNewTrd.Quantity * nNewBS
'                            If aOpt.QtyInShares <= BAD_LONG_VALUE Then aOpt.QtyInShares = 0
'                            aOpt.QtyInShares = aOpt.QtyInShares + aNewTrd.Quantity * aNewTrd.LotSize * nNewBS
'                            bUpdate = True
'                        End If
'                        'If bAddPos And (g_CurTraderID = 0 Or aOldTrd.Trader.ID = g_CurTraderID) Then
'                        '    If aOpt.Qty <= BAD_LONG_VALUE Then
'                        '        aOpt.Qty = 0
'                        '        bRecalcOption = True
'                        '    End If
'                        '    aOpt.Qty = aOpt.Qty - aOldTrd.Quantity * nOldBS
'                        '    If aOpt.QtyInShares <= BAD_LONG_VALUE Then aOpt.QtyInShares = 0
'                        '    aOpt.QtyInShares = aOpt.QtyInShares - aOldTrd.Quantity * aOldTrd.LotSize * nOldBS
'                        '    bUpdate = True
'                        'End If
'
'                        'If bDelPos And (g_CurTraderID = 0 Or aNewTrd.Trader.ID = g_CurTraderID) Then
'                        '    If aOpt.Qty <= BAD_LONG_VALUE Then
'                        '        aOpt.Qty = 0
'                        '        bRecalcOption = True
'                        '    End If
'                        '    aOpt.Qty = aOpt.Qty + aNewTrd.Quantity * nNewBS
'                        '    If aOpt.QtyInShares <= BAD_LONG_VALUE Then aOpt.QtyInShares = 0
'                        '    aOpt.QtyInShares = aOpt.QtyInShares + aNewTrd.Quantity * aNewTrd.LotSize * nNewBS
'                        '    bUpdate = True
'                        'End If
'                    End If
'                End If
'
'            ElseIf aNewTrd.ContractType = enCtIndex Or aNewTrd.ContractType = enCtStock Then
'                If bAddPos And (g_CurTraderID = 0 Or aOldTrd.Trader.ID = g_CurTraderID) Then
'                    If m_Aux.Grp.Und.Qty <= BAD_LONG_VALUE Then m_Aux.Grp.Und.Qty = 0
'                    m_Aux.Grp.Und.Qty = m_Aux.Grp.Und.Qty - aOldTrd.Quantity * nOldBS
'
'                    If m_Aux.Grp.Und.QtyInShares <= BAD_LONG_VALUE Then m_Aux.Grp.Und.QtyInShares = 0
'                    m_Aux.Grp.Und.QtyInShares = m_Aux.Grp.Und.QtyInShares - aOldTrd.Quantity * aOldTrd.LotSize * nOldBS
'                    bUpdate = True
'                End If
'
'                If bDelPos And (g_CurTraderID = 0 Or aNewTrd.Trader.ID = g_CurTraderID) Then
'                    If m_Aux.Grp.Und.Qty <= BAD_LONG_VALUE Then m_Aux.Grp.Und.Qty = 0
'                    m_Aux.Grp.Und.Qty = m_Aux.Grp.Und.Qty + aNewTrd.Quantity * nNewBS
'
'                    If m_Aux.Grp.Und.QtyInShares <= BAD_LONG_VALUE Then m_Aux.Grp.Und.QtyInShares = 0
'                    m_Aux.Grp.Und.QtyInShares = m_Aux.Grp.Und.QtyInShares + aNewTrd.Quantity * aNewTrd.LotSize * nNewBS
'                    bUpdate = True
'                End If
'            End If
'        Else
'            If aNewTrd.ContractType = enCtFutOption Then
'                For Each aFut In m_Aux.Grp.Und.Fut
'                    dtExpiryMonth = DateSerial(Year(aNewTrd.FutOpt.Expiry), Month(aNewTrd.FutOpt.Expiry), 1)
'
'                    Set aExp = aFut.Exp(dtExpiryMonth)
'                    Set aOpt = aFut.Opt(aNewTrd.ContractID)
'                    If Not aOpt Is Nothing Then
'                        If aOpt.ID <> 0 Then
'                            If bAddPos And (g_CurTraderID = 0 Or aOldTrd.Trader.ID = g_CurTraderID) Then
'                                If aOpt.Qty <= BAD_LONG_VALUE Then
'                                    aOpt.Qty = 0
'                                    bRecalcOption = True
'                                End If
'                                aOpt.Qty = aOpt.Qty - aOldTrd.Quantity * nOldBS
'                                If aOpt.QtyInShares <= BAD_LONG_VALUE Then aOpt.QtyInShares = 0
'                                aOpt.QtyInShares = aOpt.QtyInShares - aOldTrd.Quantity * aOldTrd.LotSize * nOldBS
'                                bUpdate = True
'                            End If
'
'                            If bDelPos And (g_CurTraderID = 0 Or aNewTrd.Trader.ID = g_CurTraderID) Then
'                                If aOpt.Qty <= BAD_LONG_VALUE Then
'                                    aOpt.Qty = 0
'                                    bRecalcOption = True
'                                End If
'                                aOpt.Qty = aOpt.Qty + aNewTrd.Quantity * nNewBS
'                                If aOpt.QtyInShares <= BAD_LONG_VALUE Then aOpt.QtyInShares = 0
'                                aOpt.QtyInShares = aOpt.QtyInShares + aNewTrd.Quantity * aNewTrd.LotSize * nNewBS
'                                bUpdate = True
'                            End If
'                        End If
'                    End If
'                Next
'
'            ElseIf aNewTrd.ContractType = enCtFuture Then
'                Set aFut = m_Aux.Grp.Und.Fut(aNewTrd.FutID)
'                If Not aFut Is Nothing Then
'                    If bAddPos And (g_CurTraderID = 0 Or aOldTrd.Trader.ID = g_CurTraderID) Then
'                        If aFut.Qty <= BAD_LONG_VALUE Then aFut.Qty = 0
'                        aFut.Qty = aFut.Qty - aOldTrd.Quantity * nOldBS
'
'                        If aFut.QtyInShares <= BAD_LONG_VALUE Then aFut.QtyInShares = 0
'                        aFut.QtyInShares = aFut.QtyInShares - aOldTrd.Quantity * aOldTrd.LotSize * nOldBS
'                        bUpdate = True
'                    End If
'
'                    If bDelPos And (g_CurTraderID = 0 Or aNewTrd.Trader.ID = g_CurTraderID) Then
'                        If aFut.Qty <= BAD_LONG_VALUE Then aFut.Qty = 0
'                        aFut.Qty = aFut.Qty + aNewTrd.Quantity * nNewBS
'
'                        If aFut.QtyInShares <= BAD_LONG_VALUE Then aFut.QtyInShares = 0
'                        aFut.QtyInShares = aFut.QtyInShares + aNewTrd.Quantity * aNewTrd.LotSize * nNewBS
'                        bUpdate = True
'                    End If
'                End If
'            End If
'        End If
'    End If
'
'    If bUpdate Or bRatesUpdated Then
'        Screen.MousePointer = vbHourglass
'
'        If bUpdate And (aNewTrd.ContractType = enCtOption Or aNewTrd.ContractType = enCtFutOption) Then
'            Dim sKey$: sKey = aOpt.Symbol
'            Dim nMask&
'
'            If m_Aux.Grp.IsStockOrIndex Then
'                If m_Aux.Grp.Und.OptPosExchID <> 0 Then
'                    sKey = sKey & "." & m_Aux.Grp.OptExchAll(m_Aux.Grp.Und.OptPosExchID).Code
'                End If
'                nRow = fgOpt.FindRow(sKey, , IIf(aOpt.OptType = enOtCall, QOC_C_KEY, QOC_P_KEY))
'                fgOpt.RowHidden(nRow) = False
'
'                If bRecalcOption Then
'                    nMask = GetGreeksMask(aOpt.OptType) Or GM_THEOPRICE Or GM_DELTA Or GM_GAMMA Or GM_VEGA Or GM_THETA Or GM_RHO
'
'                    CalcOptionGreeks aOpt, aOpt.Quote(0), aExp, nMask, enMmQvCalcIv
'                End If
'
'                CalculateUnderlyingOptions False
'   '            m_AuxOut.OptionUpdateQuote nRow, aOpt.OptType, False, False, True
'
'            Else
'                For Each aFut In m_Aux.Grp.Und.Fut
'                     If aFut.OptPosExchID <> 0 Then
'                         sKey = sKey & "." & m_Aux.Grp.OptExchAll(aFut.OptPosExchID).Code
'                     End If
'                                     nRow = fgOpt.FindRow(sKey, , IIf(aOpt.OptType = enOtCall, QOC_C_KEY, QOC_P_KEY))
'                     fgOpt.RowHidden(nRow) = False
'
'                     If bRecalcOption Then
'                         nMask = GetGreeksMask(aOpt.OptType) Or GM_THEOPRICE Or GM_DELTA Or GM_GAMMA Or GM_VEGA Or GM_THETA Or GM_RHO
'
'                         CalcOptionGreeks aOpt, aOpt.Quote(0), aExp, nMask, enMmQvCalcIv
'                     End If
'
'                     CalculateUnderlyingOptions False
'        '            m_AuxOut.OptionUpdateQuote nRow, aOpt.OptType, False, False, True
'                Next
'            End If
'
'        Else
'            If bUpdate And (aNewTrd.ContractType = enCtFuture) Then
'                    sKey = aFut.Symbol
'                    If aFut.OptPosExchID <> 0 Then
'                        sKey = sKey & "." & m_Aux.Grp.OptExchAll(aFut.OptPosExchID).Code
'                    End If
'
'                    nRow = fgFut.FindRow(sKey, , QOF_KEY)
'                    fgFut.RowHidden(nRow) = False
'
'                    If bRecalcOption Then
'                        nMask = GetGreeksMask(aOpt.OptType) Or GM_THEOPRICE Or GM_DELTA Or GM_GAMMA Or GM_VEGA Or GM_THETA Or GM_RHO
'
'                        CalcOptionGreeks aOpt, aOpt.Quote(0), aExp, nMask, enMmQvCalcIv
'                    End If
'
'                    CalculateUnderlyingOptions False
'            End If
'
'            CalculateUnderlyingOptions bRatesUpdated
'            m_AuxOut.UnderlyingUpdateQuote 1, False, False
'            If bRatesUpdated Then
'                m_AuxOut.FuturesUpdate False, True, True
'                m_AuxOut.OptionsUpdate False, True, True
'            ElseIf bUpdate And (aNewTrd.ContractType = enCtFuture) Then
'                m_AuxOut.FuturesUpdate False, True, True
'            End If
'        End If
'
'        m_AuxOut.UnderlyingUpdateTotals
'        UpdateTotals
'
'        Screen.MousePointer = vbDefault
'    End If
'    Set aExp = Nothing
'    Set aOpt = Nothing
'End Sub
Private Sub AddTrade(aTrd As EtsMmGeneralLib.MmTradeInfoAtom, Optional bRecalc As Boolean = True)
    AcceptTrade aTrd, True, bRecalc
End Sub
Private Sub DeleteTrade(aTrd As EtsMmGeneralLib.MmTradeInfoAtom, Optional bRecalc As Boolean = True)
    AcceptTrade aTrd, False, bRecalc
End Sub

Private Sub tmrSwitchFutures_Timer()
On Error Resume Next
tmrSwitchFutures.Enabled = False
                    
If m_bShutDown Then Exit Sub

'If m_Aux.OptionsFilter = 0 Then
'    m_Aux.OptionsFilter = 1
'    m_Aux.Grp.ShowIndexFutureOptions = True
'Else
'    m_Aux.OptionsFilter = 0
'    m_Aux.Grp.ShowIndexFutureOptions = False
'End If
m_AuxOut.OptionsFilterUpdate

RefreshOptsGrid
RefreshFutsGrid

SortOptionsByDefault

If g_Params.QuoteOptExpirySeparation Then m_AuxOut.OptionsUpdateBackColor True
m_AuxOut.UnderlyingUpdate True, True
m_AuxOut.UnderlyingUpdateTotals
Screen.MousePointer = vbDefault
UserControl_Resize

End Sub

Private Sub tmrTradesProcessing_Timer()
    On Error Resume Next
    tmrTradesProcessing.Enabled = False
    
    If m_bShutDown Or m_bDataLoad Or m_bLastQuoteReqNow Or m_bSubscribingNow Then Exit Sub
    
    If Not m_Aux.RealTime Or Not ProcessRealTime Then
        CalculateUnderlyingOptions True
        m_AuxOut.UnderlyingUpdateQuote 1, False, False
        m_AuxOut.UnderlyingUpdateTotals
        UpdateTotals
    Else
        tmrRealTime.Enabled = True
    End If
End Sub

Private Sub TradeChannel_AssetUpdate(aUndData As MSGSTRUCTLib.UnderlyingUpdate)
    On Error GoTo Exception
        If (m_bShutDown) Then Exit Sub
        Dim bChange As Boolean
        Dim aUnd As EtsMmQuotesLib.MmQvUndAtom
    
        bChange = False
        
        If (aUndData.UpdStatus And enUndAggregationUpdate) Then
            Set aUnd = m_Aux.Grp.Und
            If (Not aUnd Is Nothing) Then
            
                'chech for modifications
                If (aUnd.ID = aUndData.UndID) Then
                    If (aUndData.UseHead <> aUnd.PriceByHead) Then
                        bChange = True
                        aUnd.PriceByHead = aUndData.UseHead
                    End If
                    If (aUndData.Coeff <> aUnd.Coeff) Then
                        bChange = True
                        aUnd.Coeff = aUndData.Coeff
                    End If
                End If
                
                'recalculate all data
                If bChange Then
                    If m_Aux.RealTime = False Then Recalculate True
                End If
                
            End If
        End If
    Exit Sub
Exception:
    Debug.Print "Error while try to update Asset configuration"
End Sub

Private Sub TradeChannel_DividendTypeUpdate(aUndData As MSGSTRUCTLib.UnderlyingUpdate)
    On Error GoTo Exception
        If (m_bShutDown) Then Exit Sub
        Dim bChange As Boolean
        Dim aUnd As EtsMmQuotesLib.MmQvUndAtom
    
        bChange = False
        
        If (aUndData.UpdStatus And enUndDividendUpdate) Then
            Set aUnd = m_Aux.Grp.Und
            If (Not aUnd Is Nothing) Then
            
                'chech for modifications
                If (aUnd.ID = aUndData.UndID) Then
                    bChange = True
                End If
                
                'recalculate all data
                If bChange Then
                    If m_Aux.RealTime = False Then Recalculate True, , True
                End If
                
            End If
        End If
    Exit Sub
Exception:
    Debug.Print "Error while try to update Dividend Type"
End Sub

Private Sub TradeChannel_PriceUpdate(aPrcData As MSGSTRUCTLib.PriceUpdate)
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim bChange As Boolean
    
    bChange = False
    
    Set aUnd = m_Aux.Grp.Und
    If Not aUnd Is Nothing Then
        If aPrcData.ContractType = enCtStock Or aPrcData.ContractType = enCtIndex Then
            If aUnd.Quote(0).PriceClose <> aPrcData.PriceClose And aUnd.ID = aPrcData.UndID Then
                aUnd.Quote(0).PriceClose = aPrcData.PriceClose
                bChange = True
            End If
        ElseIf aPrcData.ContractType = enCtFuture Then
            Set aFut = aUnd.Fut(aPrcData.ContractID)
            If Not aFut Is Nothing Then
                If aFut.Quote(0).PriceClose <> aPrcData.PriceClose Then
                    aFut.Quote(0).PriceClose = aPrcData.PriceClose
                    bChange = True
                End If
            End If
        End If
        If bChange Then
            If m_Aux.RealTime = False Then Recalculate False, True
        End If
    End If

End Sub

'Private Sub DeleteTrade(aTrd As EtsMmGeneralLib.MmTradeInfoAtom)
'    On Error Resume Next
'    Dim aOpt As EtsMmQuotesLib.MmQvOptAtom, nRow&, nBS&, bUpdate As Boolean, dtExpiryMonth As Date
'    Dim bRatesUpdated As Boolean, bUpdatePos As Boolean
'
'    If g_CurTraderID <> 0 And aTrd.Trader.ID <> g_CurTraderID Then Exit Sub
'    If m_Aux.Grp.Und.ID <> aTrd.UndID Then Exit Sub
'
'    bUpdate = False
'    bRatesUpdated = False
'
'    bUpdatePos = m_Aux.CheckTradeFilter(aTrd)
'
'    If aTrd.ContractType = enCtIndex Or aTrd.ContractType = enCtStock Then
'        bRatesUpdated = UnderlyingAdjustRates(False) And Not m_Aux.Grp.UseCustRates
'        If bRatesUpdated Then
'            m_AuxOut.RatesUpdate
'            m_Aux.AdjustDivsAndRatesVisible
'        End If
'    End If
'
'    nBS = IIf(aTrd.IsBuy, 1, -1)
'
'    If bUpdatePos Then
'        If m_Aux.Grp.IsStockOrIndex Then
'            If aTrd.ContractType = enCtOption Then
'
'                dtExpiryMonth = DateSerial(Year(aTrd.Opt.Expiry), Month(aTrd.Opt.Expiry), 1)
'
'                Set aOpt = m_Aux.Grp.Und.Opt(aTrd.ContractID)
'                If Not aOpt Is Nothing Then
'                    If aOpt.ID <> 0 Then
'                        If aOpt.Qty > BAD_LONG_VALUE Then
'                            aOpt.Qty = aOpt.Qty - aTrd.Quantity * nBS
'                            bUpdate = True
'                        End If
'
'                        If aOpt.QtyInShares > BAD_LONG_VALUE Then
'                            aOpt.QtyInShares = aOpt.QtyInShares - aTrd.Quantity * aTrd.LotSize * nBS
'                            bUpdate = True
'                        End If
'                    End If
'                End If
'
'            ElseIf aTrd.ContractType = enCtIndex Or aTrd.ContractType = enCtStock Then
'                If m_Aux.Grp.Und.Qty > BAD_LONG_VALUE Then
'                    m_Aux.Grp.Und.Qty = m_Aux.Grp.Und.Qty - aTrd.Quantity * nBS
'                    bUpdate = True
'                End If
'
'                If m_Aux.Grp.Und.QtyInShares > BAD_LONG_VALUE Then
'                    m_Aux.Grp.Und.QtyInShares = m_Aux.Grp.Und.QtyInShares - aTrd.Quantity * aTrd.LotSize * nBS
'                    bUpdate = True
'                End If
'            End If
'        Else
'            If aTrd.ContractType = enCtFutOption Then
'
'                dtExpiryMonth = DateSerial(Year(aTrd.FutOpt.Expiry), Month(aTrd.FutOpt.Expiry), 1)
'
'                Set aOpt = m_Aux.Grp.Fut.Opt(aTrd.ContractID)
'                If Not aOpt Is Nothing Then
'                    If aOpt.ID <> 0 Then
'                        If aOpt.Qty > BAD_LONG_VALUE Then
'                            aOpt.Qty = aOpt.Qty - aTrd.Quantity * nBS
'                            bUpdate = True
'                        End If
'
'                        If aOpt.QtyInShares > BAD_LONG_VALUE Then
'                            aOpt.QtyInShares = aOpt.QtyInShares - aTrd.Quantity * aTrd.LotSize * nBS
'                            bUpdate = True
'                        End If
'                    End If
'                End If
'
'            ElseIf aTrd.ContractType = enCtFuture Then
'                If m_Aux.Grp.Fut.Qty > BAD_LONG_VALUE Then
'                    m_Aux.Grp.Fut.Qty = m_Aux.Grp.Fut.Qty - aTrd.Quantity * nBS
'                    bUpdate = True
'                End If
'
'                If m_Aux.Grp.Fut.QtyInShares > BAD_LONG_VALUE Then
'                    m_Aux.Grp.Fut.QtyInShares = m_Aux.Grp.Fut.QtyInShares - aTrd.Quantity * aTrd.LotSize * nBS
'                    bUpdate = True
'                End If
'            End If
'        End If
'    End If
'
'    If bUpdate Or bRatesUpdated Then
'        Screen.MousePointer = vbHourglass
'
'        If bUpdate And (aTrd.ContractType = enCtOption Or aTrd.ContractType = enCtFutOption) Then
'            Dim sKey$: sKey = aOpt.Symbol
'
'            If m_Aux.Grp.IsStockOrIndex Then
'                If m_Aux.Grp.Und.OptPosExchID <> 0 Then
'                    sKey = sKey & "." & m_Aux.Grp.OptExchAll(m_Aux.Grp.Und.OptPosExchID).Code
'                End If
'            Else
'                If m_Aux.Grp.Fut.OptPosExchID <> 0 Then
'                    sKey = sKey & "." & m_Aux.Grp.OptExchAll(m_Aux.Grp.Fut.OptPosExchID).Code
'                End If
'            End If
'
'            nRow = fgOpt.FindRow(sKey, , IIf(aOpt.OptType = enOtCall, QOC_C_KEY, QOC_P_KEY))
'            fgOpt.RowHidden(nRow) = False
'
'            CalculateUnderlyingOptions False
''            m_AuxOut.OptionUpdateQuote nRow, aOpt.OptType, False, False, True
'        Else
'            CalculateUnderlyingOptions bRatesUpdated
'            m_AuxOut.UnderlyingUpdateQuote 1, False, False
'            If bRatesUpdated Then m_AuxOut.OptionsUpdate False, True, True
'        End If
'
'        m_AuxOut.UnderlyingUpdateTotals
'        UpdateTotals
'
'        Screen.MousePointer = vbDefault
'    End If
'    Set aOpt = Nothing
'End Sub

Private Sub TradeChannel_TradeAction(aNewTrdInfo As EtsMmGeneralLib.MmTradeInfoAtom, aOldTrdInfo As EtsMmGeneralLib.MmTradeInfoAtom, enAction As TradeActionEnum)
    On Error Resume Next
    If m_bShutDown Or m_bDataLoad Then Exit Sub
    If m_Aux.Grp.ID = 0 Then Exit Sub

    Select Case enAction
        Case enTaTradeNew
            Debug.Assert Not aNewTrdInfo Is Nothing
            AddTrade aNewTrdInfo

        Case enTaTradeUpdate
            Debug.Assert Not aNewTrdInfo Is Nothing
            Debug.Assert Not aOldTrdInfo Is Nothing
            DeleteTrade aOldTrdInfo, False
            AddTrade aNewTrdInfo, True
            
           'UpdateTrade aNewTrdInfo, aOldTrdInfo

        Case enTaTradeDelete
            Debug.Assert Not aOldTrdInfo Is Nothing
            DeleteTrade aOldTrdInfo
    End Select
End Sub

Private Sub TradeChannel_PositionTransfer(aTrdFrom As EtsMmGeneralLib.MmTradeInfoAtom, aTrdTo As EtsMmGeneralLib.MmTradeInfoAtom)
    On Error Resume Next
    If m_bShutDown Or m_bDataLoad Then Exit Sub
    If m_Aux.Grp.ID = 0 Then Exit Sub

    Debug.Assert Not aTrdFrom Is Nothing
    Debug.Assert Not aTrdTo Is Nothing
    
    AddTrade aTrdFrom
    AddTrade aTrdTo
End Sub

Private Sub UserControl_Hide()
    On Error Resume Next
    m_Aux.RealTime = False
    m_bDataLoad = False
    m_bSubscribingNow = False
    m_bLastQuoteReqNow = False
End Sub

Private Sub UserControl_Resize()
    On Error Resume Next
    If m_bShutDown Or gCmn Is Nothing Then Exit Sub
    Dim nHeight&, nRows&, i&, nVisRows&, nGridHeight&, nGridColWidth&, nHeightFut&, nVolWidth&, nDivWidth&
    
    Dim nTotalCols As Long
    
    With fgUnd
        nVisRows = 0
        nRows = .Rows - 1
        For i = 1 To nRows
            If Not .RowHidden(i) Then nVisRows = nVisRows + 1
        Next
        
        .Top = 0
        .Left = 0
        
        nTotalCols = .Cols - 1
        nGridHeight = .RowHeight(0) + _
                      nVisRows * .RowHeight(1) + _
                      ScaleY(.GridLineWidth * 2, vbPixels, vbTwips)
                      
        If nTotalCols = .RightCol And .LeftCol = 1 Then
            nGridColWidth = 0&
            For i = 0 To .Cols - 1
                If Not .ColHidden(i) Then nGridColWidth = nGridColWidth + .ColWidth(i) + .GridLineWidth '+ ScaleY(.GridLineWidth, vbPixels, vbTwips)
            Next
            If nGridColWidth > 0 Then nGridColWidth = nGridColWidth - ScaleY(.GridLineWidth, vbPixels, vbTwips)
            
            If ScaleWidth < nGridColWidth Then
                nGridHeight = nGridHeight + ScaleY(GetSystemMetrics(SM_CYHSCROLL), vbPixels, vbTwips)
                .ScrollBars = flexScrollBarHorizontal
            Else
                .ScrollBars = flexScrollBarNone
            End If
        ElseIf nTotalCols <> .RightCol Or .LeftCol <> 1 Then
              nGridHeight = nGridHeight + ScaleY(GetSystemMetrics(SM_CYHSCROLL), vbPixels, vbTwips)
             .ScrollBars = flexScrollBarHorizontal
        Else
          .ScrollBars = flexScrollBarNone
        End If

'
'        If ScaleWidth < nGridColWidth Then
'            nGridHeight = nGridHeight + ScaleY(GetSystemMetrics(SM_CYHSCROLL), vbPixels, vbTwips)
'            .ScrollBars = flexScrollBarHorizontal
'        Else
'            .ScrollBars = flexScrollBarNone
'        End If
        
        .Height = nGridHeight
        .Width = ScaleWidth
        nHeight = fgUnd.Height + GRID_VERT_SPACE
    End With

    
    nTotalCols = 0
    If m_Aux.DividendsVisible And (m_Aux.Grp.ID = 0 Or m_Aux.Grp.ID <> 0 And m_Aux.Grp.ContractType = enCtStock) Or m_Aux.RatesVisible Or m_Aux.CalcModelVisible Then
        fgDiv.Top = fgUnd.Height + GRID_VERT_SPACE
        fgDiv.Left = 0
        For i = 0 To fgDiv.Cols - 1
            nDivWidth = nDivWidth + IIf(fgDiv.ColHidden(i), 0, fgDiv.ColWidth(i))
            nTotalCols = nTotalCols + IIf(fgDiv.ColHidden(i), 0, 1)
        Next
        If ScaleWidth < nDivWidth Then
            fgDiv.Height = fgDiv.RowHeight(0) + (fgDiv.Rows - 1) * fgDiv.RowHeight(1) + ScaleY(fgDiv.GridLineWidth * 2, vbPixels, vbTwips) + fgDiv.RowHeight(0)
             fgDiv.ScrollBars = flexScrollBarHorizontal
        Else
            fgDiv.Height = fgDiv.RowHeight(0) + (fgDiv.Rows - 1) * fgDiv.RowHeight(1) + ScaleY(fgDiv.GridLineWidth * 2, vbPixels, vbTwips)
            fgDiv.ScrollBars = flexScrollBarNone
        End If
        fgDiv.Width = ScaleWidth
        nHeight = nHeight + fgDiv.Height + GRID_VERT_SPACE
        
    End If
    
    If m_Aux.VolaVisible Then
        nVolWidth = 0
        fgVol.Top = nHeight
        fgVol.Left = 0
        For i = 0 To fgVol.Cols - 1
            nVolWidth = nVolWidth + IIf(fgVol.ColHidden(i), 0, fgVol.ColWidth(i))
        Next
        nVolWidth = nVolWidth
        If ScaleWidth < nVolWidth Then
            fgVol.Height = fgVol.RowHeight(0) + (fgVol.Rows - 1) * fgVol.RowHeight(1) + ScaleY(fgVol.GridLineWidth * 2, vbPixels, vbTwips) + fgVol.RowHeight(0)
        Else
            fgVol.Height = fgVol.RowHeight(0) + (fgVol.Rows - 1) * fgVol.RowHeight(1) + ScaleY(fgVol.GridLineWidth * 2, vbPixels, vbTwips)
        End If
        fgVol.Width = ScaleWidth
        nHeight = nHeight + fgVol.Height + GRID_VERT_SPACE
    End If
    
   
    If m_Aux.FuturesVisible Then
        If m_Aux.Grp.ContractType = enCtFutUnd Then
           estFut.Visible = True
        ElseIf m_Aux.Grp.ContractType = enCtIndex Then
            estFut.Visible = m_Aux.Grp.ShowIndexFutureOptions Or Not m_Aux.Grp.IsStockOrIndex
        Else
            estFut.Visible = False
       End If
    Else
        estFut.Visible = False
    End If
    estFut.Refresh
    
    With estQuotes
        .Left = 0
        .Top = nHeight
        .Width = ScaleWidth
        .Height = ScaleHeight - .Top
        .Refresh
    End With
    
    
'    If m_Aux.FuturesVisible Then
'        With fgFut
'            .Left = 0
'            .Top = nHeight
'            .Width = ScaleWidth
'            If m_Aux.Grp.ContractType = enCtFutUnd Or m_Aux.Grp.ContractType = enCtIndex Then
'                If m_Aux.Grp.IsStockOrIndex Then
'                    nHeightFut = 0
'                Else
'                    nHeightFut = .RowHeight(0) + (.Rows - 1) * .RowHeight(1) + ScaleY(.GridLineWidth * 2, vbPixels, vbTwips)
'                End If
'
'                If nHeightFut >= ((ScaleHeight - .Top) / 5) Then
'                    .Height = (ScaleHeight - .Top) / 5
'                Else
'                    .Height = nHeightFut
'                End If
'                nHeight = nHeight + .Height + GRID_VERT_SPACE
'            Else
'                .Height = 0
'            End If
'        End With
'    End If
'
'    With fgOpt
'        .Left = 0
'        .Top = nHeight
'        .Width = ScaleWidth
'        .Height = ScaleHeight - .Top
'    End With
End Sub

Private Sub UserControl_Terminate()
    On Error Resume Next
    If Not m_bShutDown Then Term
End Sub

Public Sub Term()
    On Error Resume Next

    StopAllActivities
    
    m_bShutDown = True

    If gCmn Is Nothing Then Exit Sub
    
    m_AuxOut.Term
    Unload frmSpread
    
    QV.Cancel
    tmrShow.Enabled = False
        
    m_bSubscribingNow = False
    m_bDataLoad = False
    m_bLastQuoteReqNow = False
    
    ProcessRealTime = False
    m_Aux.Grp.Und.StopCalc
    
    m_bInProc = False
    m_bFireEvent = False
    
    Set frmLayout = Nothing
    Set TradeChannel = Nothing
    Set VolaSource = Nothing
    
    If Not PriceProvider Is Nothing Then
        lblStatus.Visible = True
        pbProgress.Visible = False
        lblProcess.Visible = False
        imgStop.Visible = False
        imgStopDis.Visible = False
        lblStatus.Caption = "Price provider connection closing..."
        lblStatus.Refresh
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "PriceProvider Connection Close Start", m_frmOwner.GetCaption
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "PriceProvider Cancel Last Quote", m_frmOwner.GetCaption
        
        If Not m_bSubscribingNow And Not m_Aux.RealTime Then
            PriceProvider.CancelLastQuote
        End If
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "PriceProvider Unsubscribe Quote", m_frmOwner.GetCaption
        
        If m_bSubscribingNow Or m_Aux.RealTime Then
            PriceProvider.UnSubscribeQuote
            If g_RTQuantity > 0 Then
                g_RTQuantity = g_RTQuantity - 1
            End If
        End If
        If m_bGroupRequest Then
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogEnhDebug, "PriceProvider Cancel Last Group Quote", m_frmOwner.GetCaption
            If Not m_bSubscribingNow And Not m_Aux.RealTime Then
                m_GroupPriceProvider.CancelLastGroupQuotes
            End If
            
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogEnhDebug, "PriceProvider Unsubscribe Group Quote", m_frmOwner.GetCaption
            If m_bSubscribingNow Or m_Aux.RealTime Then
                m_GroupPriceProvider.UnSubscribeGroupQuotes
            End If
        End If
       
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "PriceProvider Disconnect", m_frmOwner.GetCaption
        
        PriceProvider.Disconnect
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "PriceProvider Destroy", m_frmOwner.GetCaption
        
        Set PriceProvider = Nothing
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogEnhDebug, "PriceProvider Connection Closed", m_frmOwner.GetCaption
    
    End If
    
    RaiseEvent OnScreenClose
    
    Set m_GroupPriceProvider = Nothing
    Set m_BatchPriceProvider = Nothing
    
    ClearViewAndData
    fgUnd.Rows = 1
    fgOpt.Rows = 1
    fgDiv.Rows = 1
    fgVol.Rows = 1
    
    Set geOpt = Nothing
    Set m_Aux.QuoteReqsAll = Nothing
    Set m_Aux.Grp = Nothing
    Set m_Aux.QV = Nothing
    Set QV = Nothing
    Set MarketDepthOptColl = Nothing

    m_Aux.RealTime = False
    m_Aux.Term
    

    Set pbProgress = Nothing
    Set lblProcess = Nothing
    Set lblStatus = Nothing
    Set imgStop = Nothing
    Set imgStopDis = Nothing
    Set aParams = Nothing
End Sub

Public Sub ShowAllOptExchanges()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.OptExchAll.Count <= 1 Then Exit Sub
    Dim aExch As EtsGeneralLib.ExchAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    For Each aExch In m_Aux.Grp.OptExchAll
        aExch.Visible = True
    Next
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aExch In m_Aux.Grp.Und.OptExch
            aExch.Visible = True
        Next
    Else
      For Each aFut In m_Aux.Grp.Und.Fut
        For Each aExch In aFut.OptExch
            aExch.Visible = True
        Next
      Next
    End If
        
    AdjustOptPosExchIDs
    RefreshOptsGrid
    'm_AuxOut.ShowOptionRows True

    RaiseEvent OnOptExchangesChange(True)
End Sub

Public Sub ShowAllUndExchanges()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    Dim aExch As EtsGeneralLib.ExchAtom, aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    For Each aExch In m_Aux.Grp.UndExchAll
        aExch.Visible = True
    Next
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aExch In m_Aux.Grp.Und.UndExch
            aExch.Visible = True
        Next
            
        If Not m_Aux.Grp.Und.SynthUnd Is Nothing Then
            For Each aUnd In m_Aux.Grp.Und.SynthUnd
                For Each aExch In aUnd.UndExch
                    aExch.Visible = True
                Next
            Next
        End If
    Else
      For Each aFut In m_Aux.Grp.Und.Fut
        For Each aExch In aFut.FutExch
            aExch.Visible = True
        Next
      Next
    End If
    
    ShowUndExchanges
    
    RaiseEvent OnUndExchangesChange(True)
End Sub

Public Sub ShowNextOptExchange()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.OptExchAll.Count <= 1 Then Exit Sub
    Dim i&, aExch As EtsGeneralLib.ExchAtom
    
    m_nCurrentOptExchIdx = m_nCurrentOptExchIdx + 1
    If m_nCurrentOptExchIdx > m_Aux.Grp.OptExchAll.Count Then m_nCurrentOptExchIdx = 1
    
    i = 1
    For Each aExch In m_Aux.Grp.OptExchAll
        aExch.Visible = (i = m_nCurrentOptExchIdx)
        i = i + 1
    Next
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aExch In m_Aux.Grp.Und.OptExch
            aExch.Visible = m_Aux.Grp.OptExchAll(aExch.ID).Visible
        Next
    Else
        For Each aExch In m_Aux.Grp.Und.OptExch
            aExch.Visible = m_Aux.Grp.OptExchAll(aExch.ID).Visible
        Next
    End If
    
    AdjustOptExchVisible
    AdjustOptPosExchIDs
    'm_AuxOut.ShowOptionRows True
    RefreshOptsGrid
    
    RaiseEvent OnOptExchangesChange(True)
End Sub

Public Sub ShowPrevOptExchange()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.OptExchAll.Count <= 1 Then Exit Sub
    
    Dim i&, aExch As EtsGeneralLib.ExchAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    m_nCurrentOptExchIdx = m_nCurrentOptExchIdx - 1
    If m_nCurrentOptExchIdx < 1 Then m_nCurrentOptExchIdx = m_Aux.Grp.OptExchAll.Count
    
    i = 1
    For Each aExch In m_Aux.Grp.OptExchAll
        aExch.Visible = (i = m_nCurrentOptExchIdx)
        i = i + 1
    Next
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aExch In m_Aux.Grp.Und.OptExch
            aExch.Visible = m_Aux.Grp.OptExchAll(aExch.ID).Visible
        Next
    Else
      For Each aFut In m_Aux.Grp.Und.Fut
        For Each aExch In aFut.OptExch
            aExch.Visible = m_Aux.Grp.OptExchAll(aExch.ID).Visible
        Next
      Next
    End If
    
    AdjustOptExchVisible
    AdjustOptPosExchIDs
    'm_AuxOut.ShowOptionRows True
    RefreshOptsGrid
    
    RaiseEvent OnOptExchangesChange(True)
End Sub

Public Sub ShowOptExchange(ByVal nID As Long, ByVal bShow As Boolean, Optional ByVal bUpdate As Boolean = True)
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.OptExchAll.Count <= 1 Then Exit Sub
    
    Dim nVisibleCount&, aExch As EtsGeneralLib.ExchAtom, aExchAll As EtsGeneralLib.ExchAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    If Not bShow Then
        For Each aExch In m_Aux.Grp.OptExchAll
            If aExch.Visible Then nVisibleCount = nVisibleCount + 1
        Next
    Else
        nVisibleCount = 2
    End If
    
    If nVisibleCount > 1 Then
        Set aExchAll = m_Aux.Grp.OptExchAll(nID)
        
        If Not aExchAll Is Nothing Then
        
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Exchange -> """ & aExchAll.Code & " - [" & aExchAll.Name & "]""" & IIf(bShow, " Selected.", " Unselected."), m_frmOwner.GetCaption
        
            aExchAll.Visible = bShow
            If m_Aux.Grp.IsStockOrIndex Then
                Set aExch = m_Aux.Grp.Und.OptExch(nID)
                If Not aExch Is Nothing Then
                    aExch.Visible = bShow
                    
                    AdjustOptExchVisible
                    AdjustOptPosExchIDs
    '                m_AuxOut.ShowOptionRows True
                    
                    Set aExch = Nothing
                End If
            Else
                For Each aFut In m_Aux.Grp.Und.Fut
                    Set aExch = aFut.OptExch(nID)
                    If Not aExch Is Nothing Then
                        aExch.Visible = bShow
                        
                        AdjustOptExchVisible
                        AdjustOptPosExchIDs
        '                m_AuxOut.ShowOptionRows True
                        
                        Set aExch = Nothing
                    End If
                Next
            End If
            
            If bUpdate Then RefreshOptsGrid
           
            Set aExchAll = Nothing
        Else
            Debug.Assert False
        End If
        
        RaiseEvent OnOptExchangesChange(True)
    End If
End Sub

Private Sub AdjustOptExchVisible()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    Dim aExch As EtsGeneralLib.ExchAtom, aOptExch As EtsGeneralLib.ExchAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim bNoVisibleExch As Boolean, aExchColl As EtsGeneralLib.ExchColl
    
    If m_Aux.Grp.IsStockOrIndex Then
        Set aExchColl = m_Aux.Grp.Und.OptExch
        bNoVisibleExch = True
        For Each aExch In aExchColl
            Set aOptExch = m_Aux.Grp.OptExchAll(aExch.ID)
            If Not aOptExch Is Nothing Then
                aExch.Visible = aOptExch.Visible
                If aExch.Visible Then bNoVisibleExch = False
                Set aOptExch = Nothing
            End If
        Next
        If bNoVisibleExch Then aExchColl(0).Visible = True

    Else
        For Each aFut In m_Aux.Grp.Und.Fut
            Set aExchColl = aFut.OptExch
            bNoVisibleExch = True
            For Each aExch In aExchColl
                Set aOptExch = m_Aux.Grp.OptExchAll(aExch.ID)
                If Not aOptExch Is Nothing Then
                    aExch.Visible = aOptExch.Visible
                    If aExch.Visible Then bNoVisibleExch = False
                    Set aOptExch = Nothing
                End If
            Next
        Next
        If bNoVisibleExch Then aExchColl(0).Visible = True
    End If
    

    Set aExchColl = Nothing
End Sub

Private Sub AdjustOptPosExchIDs()
    On Error Resume Next
    Dim aExch As EtsGeneralLib.ExchAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    If m_Aux.Grp.IsStockOrIndex Then
        m_Aux.Grp.Und.OptPosExchID = 0
        For Each aExch In m_Aux.Grp.Und.OptExch
            If aExch.Visible Then
                m_Aux.Grp.Und.OptPosExchID = aExch.ID
                Exit For
            End If
        Next
    Else
        For Each aFut In m_Aux.Grp.Und.Fut
            aFut.OptPosExchID = 0
            For Each aExch In aFut.OptExch
                If aExch.Visible Then
                    aFut.OptPosExchID = aExch.ID
                    Exit For
                End If
            Next
        Next
    End If
    
End Sub

Public Sub ShowUndExchange(ByVal nID As Long, ByVal bShow As Boolean)
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.UndExchAll.Count <= 1 Then Exit Sub
    
    Dim nVisibleCount&, aExch As EtsGeneralLib.ExchAtom, aExchAll As EtsGeneralLib.ExchAtom
    
    If Not bShow Then
        For Each aExch In m_Aux.Grp.UndExchAll
            If aExch.Visible Then nVisibleCount = nVisibleCount + 1
        Next
    Else
        nVisibleCount = 2
    End If
    
    If nVisibleCount > 1 Then
        Set aExchAll = m_Aux.Grp.UndExchAll(nID)
        
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogUserAction, "Exchange -> """ & aExchAll.Code & " - [" & aExchAll.Name & "]""" & IIf(bShow, " Selected.", " Unselected."), m_frmOwner.GetCaption
        
        If Not aExchAll Is Nothing Then
            aExchAll.Visible = bShow
            
            AdjustUnderlyingsExchVisible
            AdjustUnderlyingsPosExchID
            
            ShowUndExchanges
            ClearSpread
            
            Set aExchAll = Nothing
        Else
            Debug.Assert False
        End If
        
        RaiseEvent OnUndExchangesChange(True)
    End If
End Sub

Private Sub ShowUndExchanges()
    On Error Resume Next
    m_AuxOut.ShowUndExchanges
    m_AuxOut.UnderlyingUpdateTotals
    UserControl_Resize
End Sub

Private Sub AdjustUnderlyingsExchVisible()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    
    Dim aExch As EtsGeneralLib.ExchAtom, aUndExch As EtsGeneralLib.ExchAtom, aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim bNoVisibleExch As Boolean
    
    bNoVisibleExch = True
    m_nUndMainRow = 1
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aExch In m_Aux.Grp.Und.UndExch
            Set aUndExch = m_Aux.Grp.UndExchAll(aExch.ID)
            If Not aUndExch Is Nothing Then
                aExch.Visible = aUndExch.Visible
                If aExch.Visible Then
                    bNoVisibleExch = False
                Else
                    If bNoVisibleExch Then m_nUndMainRow = m_nUndMainRow + 1
                End If
                Set aUndExch = Nothing
            End If
        Next
        
        If bNoVisibleExch Then
            m_Aux.Grp.Und.UndExch(0).Visible = True
            m_nUndMainRow = 1
        End If
    
        If Not m_Aux.Grp.Und.SynthUnd Is Nothing Then
            For Each aUnd In m_Aux.Grp.Und.SynthUnd
                
                bNoVisibleExch = True
                For Each aExch In aUnd.UndExch
                    Set aUndExch = m_Aux.Grp.UndExchAll(aExch.ID)
                    If Not aUndExch Is Nothing Then
                        aExch.Visible = aUndExch.Visible
                        If aExch.Visible Then bNoVisibleExch = False
                        Set aUndExch = Nothing
                    End If
                Next
                
                If bNoVisibleExch Then aUnd.UndExch(0).Visible = True
            Next
        End If
    Else
        
            For Each aExch In m_Aux.Grp.Und.UndExch
                Set aUndExch = m_Aux.Grp.UndExchAll(aExch.ID)
                If Not aUndExch Is Nothing Then
                    aExch.Visible = aUndExch.Visible
                    If aExch.Visible Then
                        bNoVisibleExch = False
                    Else
                        If bNoVisibleExch Then m_nUndMainRow = m_nUndMainRow + 1
                    End If
                    Set aUndExch = Nothing
                End If
            Next
            If bNoVisibleExch Then
                m_Aux.Grp.Und.UndExch(0).Visible = True
                m_nUndMainRow = 1
            End If
'            For Each aExch In aFut.FutExch
'                Set aUndExch = m_Aux.Grp.UndExchAll(aExch.ID)
'                If Not aUndExch Is Nothing Then
'                    aExch.Visible = aUndExch.Visible
'                    If aExch.Visible Then
'                        bNoVisibleExch = False
'                    Else
'                        If bNoVisibleExch Then m_nUndMainRow = m_nUndMainRow + 1
'                    End If
'                    Set aUndExch = Nothing
'                End If
'            Next
'            If bNoVisibleExch Then
'                aFut.FutExch(0).Visible = True
'                m_nUndMainRow = 1
'            End If
        
        
    End If
End Sub

Private Sub AdjustUnderlyingsPosExchID()
    On Error Resume Next
    Dim aExch As EtsGeneralLib.ExchAtom, aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aExch In m_Aux.Grp.Und.UndExch
            If aExch.Visible Then
                m_Aux.Grp.Und.PosExchID = aExch.ID
                Exit For
            End If
        Next
        
        If Not m_Aux.Grp.Und.SynthUnd Is Nothing Then
            For Each aUnd In m_Aux.Grp.Und.SynthUnd
                For Each aExch In aUnd.UndExch
                    If aExch.Visible Then
                        aUnd.PosExchID = aExch.ID
                        Exit For
                    End If
                Next
            Next
        End If
    Else
        For Each aExch In m_Aux.Grp.Und.UndExch
            If aExch.Visible Then
                m_Aux.Grp.Und.PosExchID = aExch.ID
                Exit For
            End If
        Next
    End If
End Sub

Public Sub ShowAllStrikes()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.StrikeAll.Count <= 1 Then Exit Sub
    
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, aStr As EtsMmQuotesLib.MmQvStrikeAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    For Each aStr In m_Aux.Grp.StrikeAll
        aStr.Visible = True
    Next
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aExp In m_Aux.Grp.Und.Exp
            For Each aStr In aExp.Strike
                aStr.Visible = True
            Next
        Next
    Else
        For Each aFut In m_Aux.Grp.Und.Fut
            For Each aExp In aFut.Exp
                For Each aStr In aExp.Strike
                    aStr.Visible = True
                Next
            Next
        Next
    End If
    RefreshOptsGrid
    'm_AuxOut.ShowOptionRows False
End Sub

Public Sub ShowOptStrike(ByRef aStrikes As EtsGeneralLib.EtsMmEntityAtomColl, Optional bRefresh As Boolean = True)
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.StrikeAll.Count <= 1 Then Exit Sub
    
    Dim aEnt As EtsGeneralLib.EtsMmEntityAtom, aExp As EtsMmQuotesLib.MmQvExpAtom, aStr As EtsMmQuotesLib.MmQvStrikeAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    For Each aEnt In aStrikes
        m_Aux.Grp.StrikeAll(aEnt.Data3).Visible = (aEnt.Data <> 0)
    Next
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aExp In m_Aux.Grp.Und.Exp
            For Each aStr In aExp.Strike
                aStr.Visible = m_Aux.Grp.StrikeAll(aStr.Strike).Visible
            Next
        Next
    Else
        For Each aFut In m_Aux.Grp.Und.Fut
            For Each aExp In aFut.Exp
                For Each aStr In aExp.Strike
                    aStr.Visible = m_Aux.Grp.StrikeAll(aStr.Strike).Visible
                Next
            Next
        Next
    End If
    If bRefresh Then RefreshOptsGrid
'    m_AuxOut.ShowOptionRows False
End Sub

Public Sub ShowAllExpiries()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.ExpAll.Count <= 1 Then Exit Sub
    
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    For Each aExp In m_Aux.Grp.ExpAll
        aExp.Visible = True
    Next
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aExp In m_Aux.Grp.Und.Exp
            aExp.Visible = True
        Next
    Else
        For Each aFut In m_Aux.Grp.Und.Fut
            For Each aExp In aFut.Exp
                aExp.Visible = True
            Next
        Next
    End If
    
    RefreshOptsGrid
    'm_AuxOut.ShowOptionRows False
    
    RaiseEvent OnExpiriesChange(True)
End Sub

Public Sub ShowExpiry(ByVal nIndex As Long, ByVal bShow As Boolean, Optional ByVal bRefresh As Boolean = True)
    On Error Resume Next
    If m_bShutDown Or nIndex < 1 Or nIndex > m_Aux.Grp.ExpAll.Count Then Exit Sub
    
    Dim nVisibleCount&, i&, aExpAll As EtsMmQuotesLib.MmQvExpAtom, aExp As EtsMmQuotesLib.MmQvExpAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    If Not bShow Then
        i = 1
        For Each aExp In m_Aux.Grp.ExpAll
            If aExp.Visible Then nVisibleCount = nVisibleCount + 1
            If i = nIndex Then Set aExpAll = aExp
            i = i + 1
        Next
    Else
        i = 1
        For Each aExp In m_Aux.Grp.ExpAll
            If i = nIndex Then
                Set aExpAll = aExp
                Exit For
            End If
            i = i + 1
        Next
        nVisibleCount = 2
    End If
    
    If nVisibleCount > 1 Then
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogUserAction, "Expiry -> """ & nIndex & Format$(aExpAll.ExpiryMonth, " - mmm yy (") & aExpAll.RootNames & ")""" & IIf(bShow, " Selected.", " Unselected."), m_frmOwner.GetCaption
    
        aExpAll.Visible = bShow
        
        If m_Aux.Grp.IsStockOrIndex Then
            m_Aux.Grp.Und.Exp(aExpAll.ExpiryMonth).Visible = bShow
        Else
            For Each aFut In m_Aux.Grp.Und.Fut
                aFut.Exp(aExpAll.ExpiryMonth).Visible = bShow
            Next
        End If
        
        If bRefresh Then RefreshOptsGrid
'        m_AuxOut.ShowOptionRows False
        
        RaiseEvent OnExpiriesChange(True)
    End If
    
    Set aExpAll = Nothing
End Sub

Public Sub ShowNextExpiry()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.ExpAll.Count <= 1 Then Exit Sub
    
    Dim nIdx&, aExp As EtsMmQuotesLib.MmQvExpAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    m_nCurrentExpiryIdx = m_nCurrentExpiryIdx + 1
    If m_nCurrentExpiryIdx > m_Aux.Grp.ExpAll.Count Then m_nCurrentExpiryIdx = 1
    
    nIdx = 1
    For Each aExp In m_Aux.Grp.ExpAll
        aExp.Visible = (nIdx = m_nCurrentExpiryIdx)
        nIdx = nIdx + 1
    Next
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aExp In m_Aux.Grp.Und.Exp
            aExp.Visible = m_Aux.Grp.ExpAll(aExp.ExpiryMonth).Visible
        Next
    Else
        For Each aFut In m_Aux.Grp.Und.Fut
            For Each aExp In aFut.Exp
                aExp.Visible = m_Aux.Grp.ExpAll(aExp.ExpiryMonth).Visible
            Next
        Next
    End If
    RefreshOptsGrid

   'm_AuxOut.ShowOptionRows False
    
    RaiseEvent OnExpiriesChange(True)
End Sub

Public Sub ShowPrevExpiry()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.ExpAll.Count <= 1 Then Exit Sub
    
    Dim nIdx&, aExp As EtsMmQuotesLib.MmQvExpAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    m_nCurrentExpiryIdx = m_nCurrentExpiryIdx - 1
    If m_nCurrentExpiryIdx < 1 Then m_nCurrentExpiryIdx = m_Aux.Grp.ExpAll.Count
    
    nIdx = 1
    For Each aExp In m_Aux.Grp.ExpAll
        aExp.Visible = (nIdx = m_nCurrentExpiryIdx)
        nIdx = nIdx + 1
    Next
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aExp In m_Aux.Grp.Und.Exp
            aExp.Visible = m_Aux.Grp.ExpAll(aExp.ExpiryMonth).Visible
        Next
    Else
        For Each aFut In m_Aux.Grp.Und.Fut
            For Each aExp In aFut.Exp
                aExp.Visible = m_Aux.Grp.ExpAll(aExp.ExpiryMonth).Visible
            Next
        Next
    End If
    
    RefreshOptsGrid
    'm_AuxOut.ShowOptionRows False
    
    RaiseEvent OnExpiriesChange(True)
End Sub

Public Sub ShowAllOptRoots()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.Und.OptRoot.Count <= 1 Then Exit Sub
    
    Dim aRoot As EtsMmQuotesLib.MmQvOptRootAtom

    If m_Aux.Grp.IsStockOrIndex Then
        For Each aRoot In m_Aux.Grp.Und.OptRoot
            aRoot.Visible = True
        Next
    
        RefreshOptsGrid
        'm_AuxOut.ShowOptionRows False
    
        RaiseEvent OnOptRootsChange(True)
    End If
End Sub

Public Sub ShowOptRoot(ByVal nIndex As Long, ByVal bShow As Boolean, Optional ByVal bRefresh As Boolean = True)
    On Error Resume Next
    If m_bShutDown Or nIndex < 1 Or nIndex > m_Aux.Grp.Und.OptRoot.Count Then Exit Sub
    
    Dim nVisibleCount&, i&, aRoot As EtsMmQuotesLib.MmQvOptRootAtom, aRoot2 As EtsMmQuotesLib.MmQvOptRootAtom

    If m_Aux.Grp.IsStockOrIndex Then
        If Not bShow Then
            i = 1
            For Each aRoot In m_Aux.Grp.Und.OptRoot
                If aRoot.Visible Then nVisibleCount = nVisibleCount + 1
                If i = nIndex Then Set aRoot2 = aRoot
                i = i + 1
            Next
        Else
            i = 1
            For Each aRoot In m_Aux.Grp.Und.OptRoot
                If i = nIndex Then
                    Set aRoot2 = aRoot
                    Exit For
                End If
                i = i + 1
            Next
            nVisibleCount = 2
        End If
    
        If nVisibleCount > 1 Then
        
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Option Root -> """ & nIndex & " - " & aRoot2.Name & IIf(bShow, """ Selected.", """ Unselected."), m_frmOwner.GetCaption
        
            aRoot2.Visible = bShow
            Set aRoot2 = Nothing
            'm_AuxOut.ShowOptionRows False
            If bRefresh Then RefreshOptsGrid

    
            RaiseEvent OnOptRootsChange(True)
        End If
    End If
End Sub

Public Sub ShowNextOptRoot()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.Und.OptRoot.Count <= 1 Then Exit Sub
    
    Dim i&, aRoot As EtsMmQuotesLib.MmQvOptRootAtom

    If m_Aux.Grp.IsStockOrIndex Then
        m_nCurrentOptRootIdx = m_nCurrentOptRootIdx + 1
        If m_nCurrentOptRootIdx > m_Aux.Grp.Und.OptRoot.Count Then m_nCurrentOptRootIdx = 1
    
        i = 1
        For Each aRoot In m_Aux.Grp.Und.OptRoot
            aRoot.Visible = (i = m_nCurrentOptRootIdx)
            i = i + 1
        Next
    
        RefreshOptsGrid
        'm_AuxOut.ShowOptionRows False
    
        RaiseEvent OnOptRootsChange(True)
    End If
End Sub

Public Sub ShowPrevOptRoot()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.Und.OptRoot.Count <= 1 Then Exit Sub
    
    Dim i&, aRoot As EtsMmQuotesLib.MmQvOptRootAtom

    If m_Aux.Grp.IsStockOrIndex Then
        m_nCurrentOptRootIdx = m_nCurrentOptRootIdx - 1
        If m_nCurrentOptRootIdx < 1 Then m_nCurrentOptRootIdx = m_Aux.Grp.Und.OptRoot.Count
    
        i = 1
        For Each aRoot In m_Aux.Grp.Und.OptRoot
            aRoot.Visible = (i = m_nCurrentOptRootIdx)
            i = i + 1
        Next
    
        RefreshOptsGrid
        'm_AuxOut.ShowOptionRows False
    
        RaiseEvent OnOptRootsChange(True)
    End If
End Sub







Public Sub ShowAllFutures()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.Und.Fut.Count <= 1 Then Exit Sub
    
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom

    'If m_Aux.Grp.IsStockOrIndex Then
        For Each aFut In m_Aux.Grp.Und.Fut
            aFut.Visible = True
        Next
    
        RefreshOptsGrid
        RefreshFutsGrid
        'm_AuxOut.ShowOptionRows False
    
        RaiseEvent OnFutChange(True)
    'End If
End Sub

Public Sub ShowFuture(ByVal nIndex As Long, ByVal bShow As Boolean, Optional ByVal bRefresh As Boolean = True)
    On Error Resume Next
    If m_bShutDown Or nIndex < 1 Or nIndex > m_Aux.Grp.Und.Fut.Count Then Exit Sub
    
    Dim nVisibleCount&, i&, aFut As EtsMmQuotesLib.MmQvFutAtom, aFut2 As EtsMmQuotesLib.MmQvFutAtom

    'If m_Aux.Grp.IsStockOrIndex Then
        If Not bShow Then
            i = 1
            For Each aFut In m_Aux.Grp.Und.Fut
                If aFut.Visible Then nVisibleCount = nVisibleCount + 1
                If i = nIndex Then Set aFut2 = aFut
                i = i + 1
            Next
        Else
            i = 1
            For Each aFut In m_Aux.Grp.Und.Fut
                If i = nIndex Then
                    Set aFut2 = aFut
                    Exit For
                End If
                i = i + 1
            Next
            nVisibleCount = 2
        End If
    
        If nVisibleCount > 1 Then
        
            If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "Futures -> """ & nIndex & " - " & aFut.Symbol & IIf(bShow, """ Selected.", """ Unselected."), m_frmOwner.GetCaption
        
            aFut2.Visible = bShow
            Set aFut2 = Nothing
            'm_AuxOut.ShowOptionRows False
            If bRefresh Then
                RefreshOptsGrid
                RefreshFutsGrid
            End If
    
            RaiseEvent OnFutChange(True)
        End If
    'End If
End Sub

Public Sub ShowNextFut()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.Und.Fut.Count <= 1 Then Exit Sub
    
    Dim i&, aFut As EtsMmQuotesLib.MmQvFutAtom

    'If m_Aux.Grp.IsStockOrIndex Then
        m_nCurrentFutIdx = m_nCurrentFutIdx + 1
        If m_nCurrentFutIdx > m_Aux.Grp.Und.Fut.Count Then m_nCurrentFutIdx = 1
    
        i = 1
        For Each aFut In m_Aux.Grp.Und.Fut
            aFut.Visible = (i = m_nCurrentFutIdx)
            i = i + 1
        Next
    
        RefreshOptsGrid
        RefreshFutsGrid
        'm_AuxOut.ShowOptionRows False
    
        RaiseEvent OnFutChange(True)
    'End If
End Sub

Public Sub ShowPrevFut()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.Und.Fut.Count <= 1 Then Exit Sub
    
    Dim i&, aFut As EtsMmQuotesLib.MmQvFutAtom

    'If m_Aux.Grp.IsStockOrIndex Then
        m_nCurrentFutIdx = m_nCurrentFutIdx - 1
        If m_nCurrentFutIdx < 1 Then m_nCurrentFutIdx = m_Aux.Grp.Und.Fut.Count
    
        i = 1
        For Each aFut In m_Aux.Grp.Und.Fut
            aFut.Visible = (i = m_nCurrentFutIdx)
            i = i + 1
        Next
    
        RefreshOptsGrid
        RefreshFutsGrid
        'm_AuxOut.ShowOptionRows False
    
        RaiseEvent OnFutChange(True)
    'End If
End Sub

Private Sub StopRealTime()
    On Error Resume Next
    m_Aux.RealTime = False
    m_bSubscribingNow = False
    'Screen.MousePointer = vbArrow

    
    lblStatus.Visible = True
    pbProgress.Visible = False
    lblProcess.Visible = False
    imgStop.Visible = False
    imgStopDis.Visible = False
    
    lblStatus.Caption = "Real Time (Quotes unsubscription...)"
    lblStatus.Refresh
    
    PriceProvider.UnSubscribeQuote
    If g_RTQuantity > 0 Then
       g_RTQuantity = g_RTQuantity - 1
    End If

    If m_bGroupRequest Then m_GroupPriceProvider.UnSubscribeGroupQuotes
    
    UpdateTotals
    
    AdjustCaption
    AdjustState
    Screen.MousePointer = vbDefault
End Sub

Private Sub StartRealTime()
    On Error GoTo EH
    Dim sExch$, aReq As MmQvRequestAtom, aExch As EtsGeneralLib.ExchAtom, aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim aParam As PRICEPROVIDERSLib.QuoteUpdateParams
    Dim tmr As Long
    Dim ttt As Long
    
    If m_bShutDown Or m_bInProc Or m_bLastQuoteReqNow Then Exit Sub
    
    If Not PriceProvider Is Nothing Then
        Debug.Assert Not m_bSubscribingNow
    
        QV.UndResponses = 0
        QV.OptResponses = 0
        QV.FutResponses = 0
    
        If m_Aux.QuoteReqsAll.Count > 0 Then
            If Not g_PerformanceLog Is Nothing Then m_nOperation = g_PerformanceLog.BeginLogMmOperation
    
            m_bSubscribingNow = True
            m_bInProc = True
            AdjustState
            
            m_bGroupRequest = m_bGroupRequestSupported And (m_Aux.Grp.IsStockOrIndex) And Not g_Params.QuoteReqTypeAlwaysNonGroup
            
            m_nQuoteReqDone = 0&
            
            m_nFinSubStep = 0&
            
            pbProgress.Min = 0
            pbProgress.Value = 0
            pbProgress.Max = m_Aux.QuoteReqsAll.Count
        
            pbProgress.Visible = True
        
            lblStatus.Visible = False
            lblProcess.Visible = True
            lblProcess.Caption = "Quotes subscription..."
            lblProcess.Refresh
            imgStop.Visible = True
            imgStopDis.Visible = False
            
            If Not m_bGroupRequest Then
                m_nQuoteGroupReqCount = 0&
                m_nQuoteGroupReqDone = 0&
                tmr = GetTickCount
                QV.StartRealTime
                tmr = GetTickCount - tmr
                ttt = 0
'                aParam.Type = enMStart
'                PriceProvider.SubscribeQuote aParam
'
'                For Each aReq In m_Aux.QuoteReqsAll
'                    If m_bShutDown Or Not m_bSubscribingNow Then Exit For
'                    PriceProvider.SubscribeQuote aReq.QuoteUpdateParam
'                    DoEvents
'                Next
'
'                aParam.Type = enMStop
'                PriceProvider.SubscribeQuote aParam
            Else
                aParam.Symbol = m_Aux.Grp.Und.Symbol
                aParam.Type = IIf(m_Aux.Grp.Und.UndType = enCtStock, enSTK, enIDX)
                
                m_nQuoteGroupReqCount = m_Aux.Grp.Und.UndExch.Count + 1
                m_nQuoteGroupReqDone = 0&
                
                For Each aExch In m_Aux.Grp.Und.UndExch
                    If m_bShutDown Or Not m_bSubscribingNow Then Exit For
                    aParam.Exchange = aExch.Code
                    PriceProvider.SubscribeQuote aParam
                    DoEvents
                Next
                
                If Not m_bShutDown And m_bSubscribingNow And Not m_Aux.Grp.Und.SynthUnd Is Nothing Then
                    
                    For Each aUnd In m_Aux.Grp.Und.SynthUnd
                        If aUnd.ID <> USD_ID Then
                            m_nQuoteGroupReqCount = m_nQuoteGroupReqCount + aUnd.UndExch.Count
                        
                            aParam.Symbol = aUnd.Symbol
                            aParam.Type = IIf(aUnd.UndType = enCtStock, enSTK, enIDX)
                                        
                            For Each aExch In aUnd.UndExch
                                If m_bShutDown Or Not m_bSubscribingNow Then Exit For
                                
                                aParam.Exchange = aExch.Code
                                PriceProvider.SubscribeQuote aParam
                                DoEvents
                            Next
                        End If
                    Next
                End If
                    
                aParam.Symbol = m_Aux.Grp.Und.Symbol
                aParam.Type = IIf(m_Aux.Grp.Und.UndType = enCtStock, enSTK, enIDX)
                
                If Not m_bShutDown And m_bSubscribingNow Then
                    sExch = ""
                    
                    For Each aExch In m_Aux.Grp.Und.OptExch
                        If aExch.ID <> 0 Then sExch = sExch & "," & aExch.Code
                    Next
                    
                    aParam.Exchange = sExch
                    aParam.Type = IIf(m_Aux.Grp.Und.UndType = enCtStock, enGrSTK, enGrIDX)
                    m_GroupPriceProvider.SubscribeGroupQuotes aParam
                End If
                
            End If
            
            m_bInProc = False
            AdjustState
            
        Else
            pbProgress.Visible = False
            lblStatus.Visible = True
            lblProcess.Visible = False
            lblProcess.Caption = ""
            imgStop.Visible = False
            imgStopDis.Visible = False
        End If
    Else
        pbProgress.Visible = False
        lblStatus.Visible = True
        lblProcess.Visible = False
        lblProcess.Caption = ""
        imgStop.Visible = False
        imgStopDis.Visible = False
        gCmn.MyMsgBox m_frmOwner, "You are in offline mode now.", vbExclamation
    End If

    Exit Sub
EH:
    m_bSubscribingNow = False
    m_bInProc = False
    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to start real time mode."
    On Error Resume Next
    AdjustCaption
    pbProgress.Visible = False
    lblStatus.Visible = True
    lblProcess.Visible = False
    lblProcess.Caption = ""
    imgStop.Visible = False
    imgStopDis.Visible = False
    AdjustState
    AdjustCaption
    
    PriceProvider.UnSubscribeQuote
    If m_bGroupRequest Then m_GroupPriceProvider.UnSubscribeGroupQuotes

    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.FinishLogMmOperation m_nOperation, OPER_SUBSCRIBEQUOTE, m_frmOwner.GetCaption, QV.UndResponses, QV.OptResponses, QV.FutResponses
End Sub

Private Sub AdjustCaption()
    On Error Resume Next
    RaiseEvent OnSetCaption
End Sub

Public Function GetCaption() As String
    On Error Resume Next
    Dim sCaption$
    
    sCaption = ""
    If m_Aux.Grp.ID <> 0 Then sCaption = sCaption & m_Aux.Grp.Symbol & " - "
    If m_Aux.RealTime Then _
        sCaption = sCaption & IIf(m_Aux.RealTimeConnected, "[Real Time] - ", "[Real Time (Disconnected)] - ")
    sCaption = sCaption & "Quotes"
    
    GetCaption = sCaption
End Function

Public Function GetShortCaption() As String
    On Error Resume Next
    If m_Aux.Grp.ID <> 0 Then
        GetShortCaption = m_Aux.Grp.Symbol
    Else
        GetShortCaption = "<Empty>"
    End If
End Function

Public Property Get InProc() As Boolean
    InProc = m_bInProc
End Property

Public Property Get LastQuoteReqNow() As Boolean
    LastQuoteReqNow = m_bLastQuoteReqNow
End Property

Public Property Get RealTime() As Boolean
    RealTime = m_Aux.RealTime
End Property

Public Property Get RealTimeConnected() As Boolean
    RealTimeConnected = m_Aux.RealTime And m_Aux.RealTimeConnected
End Property

Public Property Get SubscribingNow() As Boolean
    SubscribingNow = m_bSubscribingNow
End Property

Public Property Get Expiries() As EtsMmQuotesLib.MmQvExpColl
    Set Expiries = m_Aux.Grp.ExpAll
End Property

Public Property Get UndExchanges() As EtsGeneralLib.ExchColl
    Set UndExchanges = m_Aux.Grp.UndExchAll
End Property

Public Property Get OptExchanges() As EtsGeneralLib.ExchColl
    Set OptExchanges = m_Aux.Grp.OptExchAll
End Property

Public Property Get OptRoots() As EtsMmQuotesLib.MmQvOptRootColl
    Set OptRoots = m_Aux.Grp.Und.OptRoot
End Property

Public Property Get Strikes() As EtsMmQuotesLib.MmQvStrikeColl
    Set Strikes = m_Aux.Grp.StrikeAll
End Property

Public Property Get Underlying() As EtsMmQuotesLib.MmQvUndAtom
    Set Underlying = m_Aux.Grp.Und
End Property

Public Property Get Group() As EtsMmQuotesLib.MmQvGrpAtom
    Set Group = m_Aux.Grp
End Property

Public Sub CustomizeUnderlyingGridLayout()
    On Error Resume Next
    If Not m_bShutDown And Not frmLayout Is Nothing Then frmLayout.Execute GT_QUOTES_UNDERLYING, QUC_SYMBOL, QUC_LAST_COLUMN, m_gdUnd, m_frmOwner
End Sub

Public Sub CustomizeDivGridLayout()
    On Error Resume Next
    If Not m_bShutDown And Not frmLayout Is Nothing Then frmLayout.Execute GT_QUOTES_DIVIDENDS, QDC_TRADES, QDC_LAST_COLUMN, m_gdDiv, m_frmOwner
End Sub

Public Sub CustomizeFutureGridLayout()
    On Error Resume Next
    If Not m_bShutDown And Not frmLayout Is Nothing Then frmLayout.Execute GT_QUOTES_FUTURES, QOF_SYMBOL, QOF_LAST_COLUMN, m_gdFut, m_frmOwner
End Sub

Public Sub CustomizeOptionGridLayout()
    On Error Resume Next
    If Not m_bShutDown And Not frmLayout Is Nothing Then frmLayout.Execute GT_QUOTES_OPTIONS, QOC_C_SYMBOL, QOC_LAST_COLUMN, m_gdOpt, m_frmOwner
End Sub

Public Sub CustomizeVolaGridLayout()
    On Error Resume Next
    If Not m_bShutDown And Not frmLayout Is Nothing Then frmLayout.Execute GT_QUOTES_VOLA, QVC_VOLA_VAL, QVC_LAST_COLUMN, m_gdVol, m_frmOwner
End Sub

Public Sub SaveToFile(aStorage As clsSettingsStorage, ByVal sKey As String)
    On Error GoTo EH
    If m_bShutDown Then Exit Sub
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom, aExch As EtsGeneralLib.ExchAtom, sValue$, aRoot As EtsMmQuotesLib.MmQvOptRootAtom
    Dim aStr As EtsMmQuotesLib.MmQvStrikeAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    If Len(sKey) > 0 Then sKey = "." & sKey

    ' common info
    aStorage.SetStringValue "Quote" & sKey, "Symbol", m_Aux.Grp.Symbol
    aStorage.SetLongValue "Quote" & sKey, "ShowModel", m_Aux.CalcModelVisible
    'aStorage.SetLongValue "Quote" & sKey, "ShowCalendar", m_Aux.ExpCalendarVisible
    aStorage.SetLongValue "Quote" & sKey, "ShowDivs", m_Aux.DividendsVisible
    aStorage.SetLongValue "Quote" & sKey, "ShowVola", m_Aux.VolaVisible
    aStorage.SetLongValue "Quote" & sKey, "ShowRates", m_Aux.RatesVisible
    aStorage.SetLongValue "Quote" & sKey, "ShowFutures", m_Aux.FuturesVisible
'    aStorage.SetLongValue "Quote" & sKey, "CurrentExpiryIdx", m_nCurrentExpiryIdx
'    aStorage.SetLongValue "Quote" & sKey, "CurrentOptExchIdx", m_nCurrentOptExchIdx
    aStorage.SetLongValue "Quote" & sKey, "TradesFilter", m_Aux.TradesFilter

    StoreVisibles
    
    If QV.VisibleExp.Count < m_Aux.Grp.ExpAll.Count Then
        sValue = ""
        For Each aExp In m_Aux.Grp.ExpAll
            If aExp.Visible Then
                sValue = sValue & "|" & CLng(aExp.ExpiryMonth)
            End If
        Next
        
        If Len(sValue) > 0 Then
            sValue = Mid$(sValue, 2)
            aStorage.SetStringValue "Quote" & sKey, "VisibleExp", sValue
        End If
    End If

    If m_Aux.Grp.IsStockOrIndex Then
        sValue = ""
        For Each aExp In m_Aux.Grp.Und.Exp
            sValue = sValue & "|" & Trim$(Str$(CLng(aExp.ExpiryMonth))) & "," & Trim$(Str$(aExp.RateCust))
        Next
        aStorage.SetLongValue "Quote" & sKey, "UseCustRates", m_Aux.Grp.UseCustRates
        If Len(sValue) > 0 Then
            sValue = Mid$(sValue, 2)
            aStorage.SetStringValue "Quote" & sKey, "CustRates", sValue
        End If

    Else
        sValue = ""
        For Each aFut In m_Aux.Grp.Und.Fut
            For Each aExp In aFut.Exp
                sValue = sValue & "|" & Trim$(Str$(CLng(aExp.ExpiryMonth))) & "," & Trim$(Str$(aExp.RateCust))
            Next
            aStorage.SetLongValue "Quote" & sKey, "UseCustRates", m_Aux.Grp.UseCustRates
            If Len(sValue) > 0 Then
                sValue = Mid$(sValue, 2)
                aStorage.SetStringValue "Quote" & sKey, "CustRates", sValue
            End If
        Next
    End If


    If QV.VisibleStr.Count < m_Aux.Grp.StrikeAll.Count Then
        sValue = ""
        For Each aStr In m_Aux.Grp.StrikeAll
            If aStr.Visible Then
                sValue = sValue & "|" & Trim$(Str$(aStr.Strike))
            End If
        Next
        
        If Len(sValue) > 0 Then
            sValue = Mid$(sValue, 2)
            aStorage.SetStringValue "Quote" & sKey, "VisibleStr", sValue
        End If
    End If

    If m_Aux.Grp.IsStockOrIndex Then
        If QV.VisibleRoot.Count < m_Aux.Grp.Und.OptRoot.Count Then
            sValue = ""
            For Each aRoot In m_Aux.Grp.Und.OptRoot
                If aRoot.Visible Then
                    sValue = sValue & "|" & aRoot.Name
                End If
            Next
            
            If Len(sValue) > 0 Then
                sValue = Mid$(sValue, 2)
                aStorage.SetStringValue "Quote" & sKey, "VisibleRoot", sValue
            End If
        End If
    End If

    If m_Aux.Grp.ID <> 0 Then
        If m_Aux.Grp.IsStockOrIndex Then
            aStorage.SetLongValue "Quote" & sKey, "IsAmerican", IIf(m_Aux.Grp.Und.IsAmerican, 1, 0)
        Else
            For Each aFut In m_Aux.Grp.Und.Fut
                aStorage.SetLongValue "Quote" & sKey, "IsAmerican", IIf(aFut.IsAmerican, 1, 0)
                Exit For
            Next
        End If
    End If

    If QV.VisibleUndExch.Count < m_Aux.Grp.UndExchAll.Count Then
        sValue = ""
        For Each aExch In m_Aux.Grp.UndExchAll
            If aExch.Visible Then
                sValue = sValue & "|" & CLng(aExch.ID)
            End If
        Next
    
        If Len(sValue) > 0 Then
            sValue = Mid$(sValue, 2)
            aStorage.SetStringValue "Quote" & sKey, "VisibleUndExch", sValue
        End If
    End If

    If QV.VisibleOptExch.Count < m_Aux.Grp.OptExchAll.Count Then
        sValue = ""
        For Each aExch In m_Aux.Grp.OptExchAll
            If aExch.Visible Then
                sValue = sValue & "|" & CLng(aExch.ID)
            End If
        Next
    
        If Len(sValue) > 0 Then
            sValue = Mid$(sValue, 2)
            aStorage.SetStringValue "Quote" & sKey, "VisibleOptExch", sValue
        End If
    End If

    m_gdUnd.WriteToStorage "QuoteUndGrid" & sKey, aStorage
    m_gdDiv.WriteToStorage "QuoteDivGrid" & sKey, aStorage, False
    m_gdVol.WriteToStorage "QuoteVolGrid" & sKey, aStorage, False
    m_gdOpt.WriteToStorage "QuoteOptGrid" & sKey, aStorage
    Exit Sub
EH:
    gCmn.ErrorHandler ""
End Sub

Public Sub OpenFromFile(aStorage As clsSettingsStorage, ByVal sKey As String)
    On Error GoTo EH
    If m_bShutDown Then Exit Sub
    Dim i&, sSym$, aValues() As String, sValue$, aValues2() As String, sItemKey$
    Dim nValue&, nLBound&, nUBound&, nLBound2&, nUBound2&, dValue#
    Dim aContract As EtsGeneralLib.EtsContractAtom
    
    If Len(sKey) > 0 Then sKey = "." & sKey
    
    ' common info
    sSym = UCase$(Trim$(aStorage.GetStringValue("Quote" & sKey, "Symbol")))
    m_Aux.CalcModelVisible = aStorage.GetLongValue("Quote" & sKey, "ShowModel", True)
    'm_Aux.ExpCalendarVisible = aStorage.GetLongValue("Quote" & sKey, "ShowCalendar", True)
    m_Aux.DividendsVisible = aStorage.GetLongValue("Quote" & sKey, "ShowDivs", True)
    m_Aux.VolaVisible = aStorage.GetLongValue("Quote" & sKey, "ShowVola", True)
    m_Aux.RatesVisible = aStorage.GetLongValue("Quote" & sKey, "ShowRates", True)
    m_Aux.FuturesVisible = aStorage.GetLongValue("Quote" & sKey, "ShowFutures", True)
'    m_nCurrentExpiryIdx = aStorage.GetLongValue("Quote" & sKey, "CurrentExpiryIdx")
'    m_nCurrentOptExchIdx = aStorage.GetLongValue("Quote" & sKey, "CurrentOptExchIdx")
    m_Aux.TradesFilter = aStorage.GetLongValue("Quote" & sKey, "TradesFilter", 0)
    
    QV.VisibleExp.Clear
    sValue = aStorage.GetStringValue("Quote" & sKey, "VisibleExp")
    If Len(sValue) > 0 Then
        On Error Resume Next
        
        aValues = Split(sValue, "|")
        nLBound = 0
        nUBound = -1
        nLBound = LBound(aValues)
        nUBound = UBound(aValues)
        For i = nLBound To nUBound
            Err.Clear
            nValue = 0
            nValue = CLng(aValues(i))
            If Err.Number <> 0 Then nValue = val(aValues(i))
            If nValue <> 0 Then
                sItemKey = Trim$(Str$(nValue))
                If QV.VisibleExp(sItemKey) Is Nothing Then QV.VisibleExp.Add(sItemKey).ID = nValue
            End If
        Next
        
        On Error GoTo EH
    End If
    Erase aValues
    
    QV.VisibleStr.Clear
    sValue = aStorage.GetStringValue("Quote" & sKey, "VisibleStr")
    If Len(sValue) > 0 Then
        On Error Resume Next
        
        aValues = Split(sValue, "|")
        nLBound = 0
        nUBound = -1
        nLBound = LBound(aValues)
        nUBound = UBound(aValues)
        For i = nLBound To nUBound
            Err.Clear
            dValue = 0#
            dValue = CDbl(aValues(i))
            If Err.Number <> 0 Then dValue = val(aValues(i))
            If dValue > 0# Then
                sItemKey = Trim$(Str$(dValue))
                If QV.VisibleStr(sItemKey) Is Nothing Then QV.VisibleStr.Add(sItemKey).Data3 = dValue
            End If
        Next
        
        On Error GoTo EH
    End If
    Erase aValues
    
    QV.VisibleRoot.Clear
    sValue = aStorage.GetStringValue("Quote" & sKey, "VisibleRoot")
    If Len(sValue) > 0 Then
        On Error Resume Next
        
        aValues = Split(sValue, "|")
        nLBound = 0
        nUBound = -1
        nLBound = LBound(aValues)
        nUBound = UBound(aValues)
        For i = nLBound To nUBound
            sValue = UCase$(Trim$(aValues(i)))
            If sValue <> "" Then
                If QV.VisibleRoot(sValue) Is Nothing Then QV.VisibleRoot.Add sValue
            End If
        Next
        
        On Error GoTo EH
    End If
    Erase aValues
    
    QV.VisibleUndExch.Clear
    sValue = aStorage.GetStringValue("Quote" & sKey, "VisibleUndExch")
    If Len(sValue) > 0 Then
        On Error Resume Next
        
        aValues = Split(sValue, "|")
        nLBound = 0
        nUBound = -1
        nLBound = LBound(aValues)
        nUBound = UBound(aValues)
        For i = nLBound To nUBound
            Err.Clear
            nValue = 0
            nValue = CLng(aValues(i))
            If Err.Number <> 0 Then nValue = val(aValues(i))
            If Err.Number = 0 Then
                sItemKey = Trim$(Str$(nValue))
                If QV.VisibleUndExch(sItemKey) Is Nothing Then QV.VisibleUndExch.Add(sItemKey).ID = nValue
            End If
        Next
        
        On Error GoTo EH
    End If
    Erase aValues
    
    QV.VisibleOptExch.Clear
    sValue = aStorage.GetStringValue("Quote" & sKey, "VisibleOptExch")
    If Len(sValue) > 0 Then
        On Error Resume Next
        
        aValues = Split(sValue, "|")
        nLBound = 0
        nUBound = -1
        nLBound = LBound(aValues)
        nUBound = UBound(aValues)
        For i = nLBound To nUBound
            Err.Clear
            nValue = 0
            nValue = CLng(aValues(i))
            If Err.Number <> 0 Then nValue = val(aValues(i))
            If Err.Number = 0 Then
                sItemKey = Trim$(Str$(nValue))
                If QV.VisibleOptExch(sItemKey) Is Nothing Then QV.VisibleOptExch.Add(sItemKey).ID = nValue
            End If
        Next
        
        On Error GoTo EH
    End If
    Erase aValues
    
    m_Aux.UseCustRates = aStorage.GetLongValue("Quote" & sKey, "UseCustRates", False)
    QV.CustRates.Clear
    sValue = aStorage.GetStringValue("Quote" & sKey, "CustRates")
    If Len(sValue) > 0 Then
        On Error Resume Next
        
        aValues = Split(sValue, "|")
        nLBound = 0
        nUBound = -1
        nLBound = LBound(aValues)
        nUBound = UBound(aValues)
        For i = nLBound To nUBound
            aValues2 = Split(aValues(i), ",")
            nLBound2 = 0
            nUBound2 = -1
            nLBound2 = LBound(aValues2)
            nUBound2 = UBound(aValues2)
            If nUBound2 - nLBound2 = 1 Then
                nValue = ReadLng(aValues2(nLBound2))
                dValue = ReadDbl(aValues2(nUBound2))
                If nValue > 0 And dValue > 0# Then
                    If QV.CustRates(CStr(nValue)) Is Nothing Then QV.CustRates.Add(CStr(nValue)).Data3 = dValue
                End If
            End If
            Erase aValues2
        Next
        
        On Error GoTo EH
    End If
    Erase aValues
    
    m_Aux.IsAmerican = aStorage.GetLongValue("Quote" & sKey, "IsAmerican", -1)
    
    m_gdUnd.ReadFromStorage "QuoteUndGrid" & sKey, aStorage
    m_gdDiv.ReadFromStorage "QuoteDivGrid" & sKey, aStorage, False
    m_gdVol.ReadFromStorage "QuoteVolGrid" & sKey, aStorage, False
    m_gdOpt.ReadFromStorage "QuoteOptGrid" & sKey, aStorage
    
    m_nNewGrpID = 0
    
    If Len(sSym) > 0 Then
        Set aContract = g_Contract.BySortKey(sSym)
        If Not aContract Is Nothing Then
            m_nNewGrpID = aContract.ID
            Set aContract = Nothing
        End If
    
        'If m_nNewGrpID <> 0 Then tmrShow.Enabled = True
    End If
    
    tmrShow.Enabled = True
    
    Exit Sub
EH:
    Dim sDescription$, nHelpContext&, sHelpFile$, nNumber&, sSource$
    sDescription = Err.Description
    nHelpContext = Err.HelpContext
    sHelpFile = Err.HelpFile
    nNumber = Err.Number
    sSource = Err.Source

    Erase aValues
    Err.Raise nNumber, sSource, sDescription, sHelpFile, nHelpContext
End Sub

Private Sub Recalculate(ByVal bSymbol As Boolean, Optional ManualEdit As Boolean = False, Optional bForceRecalc As Boolean = False)
    On Error Resume Next
    If m_Aux.Grp.ID = 0 Or m_bInProc Or m_bShutDown Then Exit Sub
    
    If Not m_Aux.RealTime Then
        Screen.MousePointer = vbHourglass
        m_bInProc = True
        
        CalculateUnderlyingOptions True, , ManualEdit, bForceRecalc
        m_AuxOut.OptionsUpdate bSymbol, True, True
        m_AuxOut.FuturesUpdate bSymbol, True, True
        m_AuxOut.UnderlyingUpdate bSymbol, True, ManualEdit
        m_AuxOut.UnderlyingUpdateTotals
        m_AuxOut.DivsUpdate
        UpdateTotals
        m_AuxOut.VolaUpdateValues ManualEdit
    
        m_bInProc = False
        Screen.MousePointer = vbDefault
    Else
        m_bForseRecalc = True
        QV.Grp.Und.SetDirty
        tmrRealTime.Enabled = True
    End If
End Sub

Public Sub Refresh()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_Aux.Grp.ID = 0 Then Exit Sub
    
    StoreVisibles
     
    m_nNewGrpID = m_Aux.Grp.ID
    m_bInRefreshMode = True
    
    'MsgBox "Refresh Timer Start"
        
    If m_nNewGrpID <> 0 Then tmrShow.Enabled = True
         
End Sub

Public Sub RefreshPrices()
    On Error Resume Next
    If m_bShutDown Or m_Aux.RealTime Then Exit Sub
    If m_Aux.Grp.ID = 0 Then Exit Sub
    
    m_bFiersTealtimeCalculation = False
    RequestLastQuotes
    
End Sub

Private Sub StoreVisibles()
    On Error Resume Next
    Dim nValue&, sKey$, dValue#, aExp As EtsMmQuotesLib.MmQvExpAtom, aExch As EtsGeneralLib.ExchAtom
    Dim aRoot As EtsMmQuotesLib.MmQvOptRootAtom, aStr As EtsMmQuotesLib.MmQvStrikeAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    QV.VisibleExp.Clear
    QV.CustRates.Clear
    QV.VisibleStr.Clear
    QV.VisibleRoot.Clear
    QV.VisibleUndExch.Clear
    QV.VisibleOptExch.Clear
    QV.VisibleFut.Clear
    
    If m_Aux.Grp.ID = 0 Then Exit Sub
    
    m_Aux.UseCustRates = m_Aux.Grp.UseCustRates
    
    If m_Aux.Grp.IsStockOrIndex Then
        m_Aux.IsAmerican = IIf(m_Aux.Grp.Und.IsAmerican, 1, 0)
    Else
        For Each aFut In m_Aux.Grp.Und.Fut
            m_Aux.IsAmerican = IIf(aFut.IsAmerican, 1, 0)
            Exit For
        Next
    End If
    
    For Each aExp In m_Aux.Grp.ExpAll
        nValue = CLng(aExp.ExpiryMonth)
        If aExp.Visible Then
            sKey = Trim$(Str$(nValue))
            If QV.VisibleExp(sKey) Is Nothing Then QV.VisibleExp.Add(sKey).ID = nValue
        End If
        dValue = aExp.RateCust
        If QV.CustRates(CStr(nValue)) Is Nothing Then QV.CustRates.Add(CStr(nValue)).Data3 = dValue
    Next
    
    For Each aStr In m_Aux.Grp.StrikeAll
        If aStr.Visible Then
            sKey = Trim$(Str$(aStr.Strike))
            If aStr.Strike < 1# Then sKey = "0" + sKey
            If QV.VisibleStr(sKey) Is Nothing Then QV.VisibleStr.Add(sKey).Data3 = aStr.Strike
        End If
    Next
    
    If m_Aux.Grp.IsStockOrIndex Then
        For Each aRoot In m_Aux.Grp.Und.OptRoot
            If aRoot.Visible Then
                If QV.VisibleRoot(aRoot.Name) Is Nothing Then QV.VisibleRoot.Add aRoot.Name
            End If
        Next
    End If
    
    If Not m_Aux.Grp.IsStockOrIndex Then
        For Each aFut In m_Aux.Grp.Und.Fut
            If aFut.Visible Then
                If QV.VisibleFut(aFut.Symbol) Is Nothing Then QV.VisibleFut.Add aFut.Symbol
            End If
        Next
    End If
    
    For Each aExch In m_Aux.Grp.UndExchAll
        If aExch.Visible Then
            nValue = aExch.ID
            sKey = Trim$(Str$(nValue))
            If QV.VisibleUndExch(sKey) Is Nothing Then QV.VisibleUndExch.Add(sKey).ID = nValue
        End If
    Next
    
    For Each aExch In m_Aux.Grp.OptExchAll
        If aExch.Visible Then
            nValue = aExch.ID
            sKey = Trim$(Str$(nValue))
            If QV.VisibleOptExch(sKey) Is Nothing Then QV.VisibleOptExch.Add(sKey).ID = nValue
        End If
    Next
End Sub

Public Property Get CalcModelVisible() As Boolean
    On Error Resume Next
    CalcModelVisible = m_Aux.CalcModelVisible
End Property

Public Property Let CalcModelVisible(ByVal bVisible As Boolean)
    On Error Resume Next
    If m_bShutDown Then Exit Property
    m_Aux.CalcModelVisible = bVisible
    m_Aux.AdjustDivsAndRatesVisible
    UserControl_Resize
    AdjustState
End Property

Public Property Get DividendsVisible() As Boolean
    On Error Resume Next
    DividendsVisible = m_Aux.DividendsVisible
End Property

Public Property Let DividendsVisible(ByVal bVisible As Boolean)
    On Error Resume Next
    If m_bShutDown Then Exit Property
    m_Aux.DividendsVisible = bVisible
    m_Aux.AdjustDivsAndRatesVisible
    UserControl_Resize
    AdjustState
End Property

Public Property Get VolaVisible() As Boolean
    On Error Resume Next
    VolaVisible = m_Aux.VolaVisible
End Property

Public Property Let VolaVisible(ByVal bVisible As Boolean)
    On Error Resume Next
    If m_bShutDown Then Exit Property
    m_Aux.VolaVisible = bVisible
    m_Aux.AdjustVolaVisible
    UserControl_Resize
    AdjustState
End Property

Public Property Get RatesVisible() As Boolean
    On Error Resume Next
    RatesVisible = m_Aux.RatesVisible
End Property

Public Property Let RatesVisible(ByVal bVisible As Boolean)
    On Error Resume Next
    If m_bShutDown Then Exit Property
    m_Aux.RatesVisible = bVisible
    m_Aux.AdjustDivsAndRatesVisible
    UserControl_Resize
    AdjustState
End Property

Public Property Get FuturesVisible() As Boolean
    On Error Resume Next
    FuturesVisible = m_Aux.FuturesVisible
End Property

Public Property Let FuturesVisible(ByVal bVisible As Boolean)
    On Error Resume Next
    If m_bShutDown Then Exit Property
    m_Aux.FuturesVisible = bVisible
    m_Aux.AdjustFuturesVisible
    UserControl_Resize
    AdjustState
End Property

'Public Property Get ExpCalendarVisible() As Boolean
'    On Error Resume Next
'    ExpCalendarVisible = m_Aux.ExpCalendarVisible
'End Property

'Public Property Let ExpCalendarVisible(ByVal bVisible As Boolean)
'    On Error Resume Next
'    If m_bShutDown Then Exit Property
'    m_Aux.ExpCalendarVisible = bVisible
'    m_Aux.AdjustDivsAndRatesVisible
'    UserControl_Resize
'    AdjustState
'End Property

Private Sub VolaSource_VolatilityChanged(ByVal Symbol As String)
    On Error Resume Next
    If m_bShutDown Or (Not m_Aux.RealTime And Not m_bSubscribingNow) Or m_Aux.Grp.ID = 0 Then Exit Sub

    If Symbol = m_Aux.Grp.Und.Symbol Then
        If Not m_bSubscribingNow And m_Aux.RealTime Then 'And ProcessRealTime Then
            Recalculate False
        Else
            m_bVolaChangedExt = True
        End If
    End If
End Sub

Public Sub InternalVolatilityChanged(ByVal sSymbol As String)
    On Error Resume Next
    If m_bShutDown Or m_bVolaChangedNow Then Exit Sub
    VolaSource_VolatilityChanged sSymbol
End Sub

Private Sub AdjustState()
    On Error Resume Next
    Dim aExpColl As EtsMmQuotesLib.MmQvExpColl
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    
    If m_Aux.Grp.IsStockOrIndex Then
         Set aExpColl = m_Aux.Grp.Und.Exp
         fgVol.ColHidden(QVC_VOLA_VAL + aExpColl.Count) = m_Aux.RealTime
         If m_Aux.RealTime Then
             fgVol.TextMatrix(1, QVC_VOLA_VAL + aExpColl.Count) = Now
             dtCalculationDate.Value = Date
         End If
    Else
         'fokiny
         fgVol.ColHidden(QVC_VOLA_VAL + m_Aux.Grp.ExpAll.Count) = m_Aux.RealTime
        If m_Aux.RealTime Then
            fgVol.TextMatrix(1, QVC_VOLA_VAL + m_Aux.Grp.ExpAll.Count) = Now
            dtCalculationDate.Value = Date
        End If
    End If
   
    UpdateMenu
    RaiseEvent OnStateChange
End Sub

Public Sub NewUnderlyingAdded(ByVal nNewUndID As Long)
    On Error Resume Next
    If Not m_bShutDown And Not m_bUndListReloadNow Then InitUndList
End Sub

Public Sub OptExpirySeparationChange()
    On Error Resume Next
    If m_bShutDown Or m_Aux.Grp.ID = 0 Then Exit Sub
    
    Dim nColKey&
    
    If m_AuxOut.ExpiryColorSelection And Not g_Params.QuoteOptExpirySeparation Then
        m_AuxOut.OptionsUpdateBackColor False
    
    ElseIf Not m_AuxOut.ExpiryColorSelection And g_Params.QuoteOptExpirySeparation Then
        nColKey = geOpt.SortColKey
        If (nColKey = QOC_C_SERIES Or nColKey = QOC_P_SERIES Or nColKey = QOC_C_EXPIRY Or nColKey = QOC_P_EXPIRY) Then
            m_AuxOut.OptionsUpdateBackColor True
        End If
    End If
End Sub

Public Sub PrintView()
'    On Error Resume Next
'    If m_bShutDown Then Exit Sub
'    Screen.MousePointer = vbHourglass
'    frmPrintPreview.Execute m_frmOwner, m_Aux.Grp.Symbol & " Quotes", "Quotes", fgUnd, fgDiv, fgVol, fgOpt
'    Screen.MousePointer = vbDefault
End Sub

Private Sub InitVola(ByRef aUnd As EtsMmQuotesLib.MmQvUndAtom)
    On Error Resume Next
    Dim nLoopCounter As Long: nLoopCounter = 1
    
    Err.Clear
    aUnd.VolaSrv.Init aUnd.Symbol, aUnd.UndType, VolaSource
    
    While Err.Number <> 0 And nLoopCounter < 10
        If Not g_PerformanceLog Is Nothing Then _
            g_PerformanceLog.LogMmInfo enLogFaults, "Fail to init vola in " & CStr(nLoopCounter) & " attempt for symbol '" & aUnd.Symbol & "'.", m_frmOwner.GetCaption

        MMSleep 20
        Err.Clear
        aUnd.VolaSrv.Init aUnd.Symbol, aUnd.UndType, VolaSource

        nLoopCounter = nLoopCounter + 1
    Wend
    
    If Err.Number <> 0 Then GoTo EH
    
    Exit Sub
EH:
    LogEvent EVENT_WARNING, "Fail to init volatility for '" & aUnd.Symbol & "': " & Err.Description
End Sub

Private Sub HandleGridDblClick(ByVal bTradeNewAvailable As Boolean)
    On Error Resume Next
    m_bIsDblClick = True
    
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
        ElseIf m_enMenuGrid = GT_QUOTES_DIVIDENDS And m_nMenuGridRow = 1 And (m_nMenuGridCol = QDC_DATE Or m_nMenuGridCol = QDC_AMT) Then
            If m_Aux.Grp.Und.Dividend.DivType = enDivCustomStream Then mnuCtxCustomDividend_Click
        End If
    End If
    
    m_bIsDblClick = False
End Sub

Public Sub MakeDataSnapshot(ByVal sFileName$)
    On Error Resume Next
'    m_Aux.MakeDataSnapshot sFileName, m_frmOwner
End Sub

Public Sub OTCOptionCalcCall()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    Dim aRowData As MmQvRowData, nColIdx&, bBuy As Boolean, aOpt As EtsMmQuotesLib.MmQvOptAtom, aUnd As EtsMmQuotesLib.MmQvUndAtom
    Dim aFut As EtsMmQuotesLib.MmQvFutAtom
    Dim aQuote As EtsMmQuotesLib.MmQvQuoteAtom
    Dim aExp As EtsMmQuotesLib.MmQvExpAtom
    Dim dtDate As Date
    Dim lCalcModel As Long
    Dim aDiv As EtsGeneralLib.EtsIndexDivAtom

    
    Dim sStockSymbol As String
    Dim dVola As Double
    Dim sOptionSymbol As String
    
    Dim lSymbolType As Long
    
    Dim dStrike As Double
    Dim dBid As Double
    Dim dAsk As Double
    Dim dtExpiry As Date
    
    Dim lContractType As Long
    Dim dYield As Double
    Dim lDivType As Long
    
    Dim dDivAmount As Double
    
    Dim dRate As Double
    
    Dim dDivDate As Double
    Dim dDivFreq As Double
    Dim lCDStockID
    Dim lCDCount
    
    lCDStockID = 0
    lCDCount = 0
    dVola = -1
    
    lContractType = m_Aux.Grp.ContractType
    

    
'    If (Not m_Aux.Grp.Fut Is Nothing) Then
'        If (m_Aux.Grp.Fut.ID > 0) Then
'            lSymbolType = 0
'            If Not m_Aux.Grp.Fut.IsAmerican Then
'                lSymbolType = 1
'            End If
'        End If
'    End If
    
'    If (lContractType <= 3) And (Not m_Aux.Grp.Und Is Nothing) Then
    If (Not m_Aux.Grp.Und Is Nothing) Then

       sStockSymbol = m_Aux.Grp.Und.Symbol
       sOptionSymbol = m_Aux.Grp.Und.Symbol
       
       
       Set aDiv = m_Aux.Grp.Und.Dividend
       If Not aDiv Is Nothing Then
            If aDiv.DivType = enDivCustomPeriodical Then
              dDivAmount = aDiv.DivAmtCust
              dDivDate = aDiv.DivDateCust
              dDivFreq = aDiv.DivFreqCust
            End If
           
            If aDiv.DivType = enDivCustomPeriodical Then
              dDivAmount = aDiv.DivAmt
              dDivDate = aDiv.DivDate
              dDivFreq = aDiv.DivFreq
            End If
       End If
       Set aDiv = Nothing
       
       lSymbolType = 0
       If Not m_Aux.Grp.Und.IsAmerican Then
           lSymbolType = 1
       End If
       dYield = m_Aux.Grp.Und.Yield
       lContractType = m_Aux.Grp.ContractType
  
    End If
   
            Set aRowData = QV.OptsRowData(m_nMenuGridRow)
            nColIdx = fgOpt.ColKey(m_nMenuGridCol)
            If aRowData Is Nothing Then
                Set aRowData = QV.OptsRowData(fgOpt.Row)
            End If
            If Not aRowData Is Nothing Then
                Set aOpt = aRowData.Opt(IIf(nColIdx < QOC_P_SYMBOL, enOtCall, enOtPut))
                If Not aOpt Is Nothing Then
                        sOptionSymbol = aOpt.Symbol
                        
                        dStrike = aOpt.Strike
                        dtExpiry = aOpt.Expiry
                        dVola = aOpt.Vola
                        
                        If m_enMenuGrid = GT_QUOTES_UNDERLYING Then
                            dVola = 0
                            dStrike = 0
                        End If
                        Set aExp = m_Aux.Grp.Und.Exp(dtExpiry)
                        
                        dtDate = CDate(CDbl(dtExpiry) - CDbl(Day(dtExpiry)))
                        For Each aExp In m_Aux.Grp.Und.Exp
                            If aExp.ExpiryMonth > dtDate Then
                                dRate = aExp.Rate
                                If (aExp.RateCust > 0) And (aExp.Rate = 0) Then
                                   dRate = aExp.RateCust
                                End If
                                'dStrike = m_Aux.Grp.Und.AtmStrike(g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)
                                'dVola = m_Aux.Grp.Und.AtmVola(aExp, g_Params.UndPriceToleranceValue, g_Params.PriceRoundingRule)

                                
                                Exit For
                            End If
                        Next
                        'lContractType = 3
                        
                        If Not aOpt.DefQuote Is Nothing Then
                            dBid = 0
                            dAsk = 0
                            If aOpt.DefQuote.PriceBid <> BAD_DOUBLE_VALUE Then
                                dBid = aOpt.DefQuote.PriceBid
                                                                    Else
                                                                    
                                If aOpt.DefQuote.PriceLast <> BAD_DOUBLE_VALUE Then
                                    dBid = aOpt.DefQuote.PriceLast
                                End If
                            
                            End If
                            
                            If aOpt.DefQuote.PriceAsk <> BAD_DOUBLE_VALUE Then
                                dAsk = aOpt.DefQuote.PriceAsk
                                                                    Else
                                                                    
                                If aOpt.DefQuote.PriceLast <> BAD_DOUBLE_VALUE Then
                                    dAsk = aOpt.DefQuote.PriceLast
                                End If
                            
                            End If
                        End If
                End If
            End If
        
    'End Select
    lCalcModel = CLng(g_Params.CalcModel)
    If Not m_Aux.Grp.IsStockOrIndex Then
        lContractType = enCtFuture
        sStockSymbol = aRowData.Fut.Symbol
    End If

    m_bInProc = False
    On Error GoTo EH
    Dim sPath As String
    Dim sParams As String
    sPath = App.Path & "\OTCCalc\OTCOptionCalc.exe"
    sParams = sStockSymbol & " " & sOptionSymbol & " " & CStr(lSymbolType) & " " & CStr(dStrike) & " " & CStr(dBid) & " " & CStr(dAsk) & " " & _
    CStr(dtExpiry) & " " & _
    CStr(lContractType) & " " & CStr(dYield * 100) & " " & CStr(lDivType) & " " & _
    CStr(dDivAmount) & " " & CStr(dDivDate) & " " & CStr(dDivFreq) & " " & _
    CStr(lCDStockID) & " " & CStr(lCDCount) & " " & CStr(dRate) & " " & CStr(dVola) & " " & CStr(lCalcModel)

    If ShellExecute(0&, "Open", sPath, sParams, "", SW_SHOWNORMAL) <= 32 Then
         gCmn.MyMsgBox Me, "Fail to open OTC OptionCalc at '" & sPath & "'.", vbCritical
    Else
           If Not g_PerformanceLog Is Nothing Then _
                g_PerformanceLog.LogMmInfo enLogUserAction, "OTCOptionCalc start [" & sParams & "]", "OTC Calc"
    End If
    
   Exit Sub
EH:
    If Not m_bShutDown Then gCmn.ErrorMsgBox m_frmOwner, "Fail to open OTC Option Calc."
    ResetMenuData
    
End Sub

Public Sub ctlStopRT()
    On Error Resume Next
    If m_bShutDown Then Exit Sub
    If m_Aux.RealTime Then
        StopRealTime
    End If
    UpdateTotals
End Sub

Public Function GetStockInfo() As String
    On Error Resume Next
    Dim sStock As String
    sStock = fgUnd.RowData(m_nUndMainRow).Und.Symbol
    GetStockInfo = "Stock symbol = """ & sStock & """. "
End Function

Public Function GetFutureInfo() As String
    On Error Resume Next
    Dim sFuture As String
    sFuture = fgFut.RowData(fgFut.Row).Fut.Symbol
    GetFutureInfo = GetStockInfo & "Future symbol = """ & sFuture & """. "
End Function

Public Function GetOptionInfo() As String
    On Error Resume Next
    Dim sOptionC As String
    Dim sOptionP As String
    sOptionC = QV.OptsRowData(fgOpt.Row).Opt(enOtCall).Symbol
    sOptionP = QV.OptsRowData(fgOpt.Row).Opt(enOtPut).Symbol
    GetOptionInfo = GetStockInfo & "Option symbol = """ & sOptionC & "/" & sOptionP & """. "
End Function


Private Function LoadCustomDivs() As Boolean
    On Error Resume Next
    Dim expDate As Date
    Dim aExp As MmQvExpAtom
    
    LoadCustomDivs = False
    
    expDate = Now + 365 * 5
    For Each aExp In m_Aux.Grp.Und.Exp
        expDate = aExp.Expiry
    Next
        
    m_frmCustDivs.Init m_Aux.Grp.Und.ID, m_Aux.Grp.Und.Symbol, expDate, m_Aux.Grp.Und.Dividend.DivType = enDivStockBasket, m_Aux.Grp.Und.Dividend.DivType = enDivCustomStream
    m_frmCustDivs.BasketDivs = IIf(m_Aux.Grp.Und.Dividend.DivType = enDivStockBasket, m_Aux.Grp.Und.BasketIndex.BasketDivs, Nothing)
            
    If m_frmCustDivs.UpdateCollection Then
        Set m_Aux.Grp.Und.Dividend.CustomDivs = m_frmCustDivs.CustomDividend
        LoadCustomDivs = True
    End If
End Function

Private Sub mnuCtxViewSpread_Click()
    ViewSpread
End Sub

Private Sub mnuCtxClearSpread_Click()
    ClearSpread False
End Sub

Private Sub mnuCtxAddToSpread_Click()
    On Error Resume Next
    Dim enOpnType As EtsOptionTypeEnum
    Dim aRowData As MmQvRowData
    Dim nQty As Long
    Dim sSymbol As String
    Dim aSpread As MmQvSpreadAtom
    
    If m_enMenuGrid = GT_QUOTES_OPTIONS Then
        Set aRowData = QV.OptsRowData(m_nMenuGridRow)
        If Not aRowData Is Nothing Then
            enOpnType = IIf(m_gdOpt.Idx(m_nMenuGridCol - 2) > QOC_C_UPDATE_TIME, enOtPut, enOtCall)
            sSymbol = aRowData.Opt(enOpnType).Symbol
            nQty = IIf(IsOptSpreadSellColumn(m_nMenuGridCol - 2), -1, 1)
        
            Set aSpread = m_Aux.Grp.Spread(sSymbol)
            
            If Not aSpread Is Nothing Then
                 If aSpread.SpreadType = SPT_BUY And nQty > 0 Then
                    nQty = 0
                 ElseIf aSpread.SpreadType = SPT_SELL And nQty < 0 Then
                    nQty = 0
                 End If
            End If
            m_Aux.Grp.Spread.UpdateOption nQty, enOpnType, QV.OptsRowData(m_nMenuGridRow)
        End If
    ElseIf m_enMenuGrid = GT_QUOTES_UNDERLYING Then
        Set aRowData = fgUnd.RowData(m_nMenuGridRow)
        If Not aRowData Is Nothing Then
            sSymbol = aRowData.Und.Symbol
            nQty = IIf(IsUndSpreadSellColumn(m_nMenuGridCol - 1), -1, 1)
            Set aSpread = m_Aux.Grp.Spread(sSymbol)
            If Not aSpread Is Nothing Then
               If aSpread.Quote.Exch.ID = aRowData.Exch.ID Then
                 If aSpread.SpreadType = SPT_BUY And nQty > 0 Then
                    nQty = 0
                 ElseIf aSpread.SpreadType = SPT_SELL And nQty < 0 Then
                    nQty = 0
                 End If
               End If
            End If
            m_Aux.Grp.Spread.UpdateUnderlying nQty, aRowData.Exch.ID, aRowData.Und
        End If
    ElseIf m_enMenuGrid = GT_QUOTES_FUTURES Then
        Set aRowData = fgFut.RowData(m_nMenuGridRow)
        If Not aRowData Is Nothing Then
            sSymbol = aRowData.Fut.Symbol
            nQty = IIf(IsFutSpreadSellColumn(m_nMenuGridCol - 1), -1, 1)
            Set aSpread = m_Aux.Grp.Spread.Item(sSymbol)
            If Not aSpread Is Nothing Then
                If aSpread.SpreadType = SPT_BUY And nQty > 0 Then
                    nQty = 0
                ElseIf aSpread.SpreadType = SPT_SELL And nQty < 0 Then
                    nQty = 0
                End If
            End If
            m_Aux.Grp.Spread.UpdateFuture nQty, aRowData.Exch.ID, aRowData.Fut
        End If
    End If
    
        UpdateSpread
End Sub
Private Sub ViewSpread()
    On Error Resume Next
    frmSpread.Init m_aSpreadData, QV.Grp.Und.Quote(0), QV.Grp.Und.ID
    frmSpread.Show vbModeless, Me
End Sub
Private Sub ClearSpread(Optional ByVal bWaitNotofications As Boolean = False)
    On Error Resume Next
    m_Aux.Grp.Spread.Clear
    UpdateSpread
    m_AuxOut.ClearFutGrid
    Unload frmSpread
End Sub

Private Sub UpdateSpread()
    On Error Resume Next
        m_Aux.Grp.Spread.Calculate (g_Params.QuoteBidColBuy)
        UpdateTotals
End Sub

Private Function IsOptSpreadBuyColumn(nColumn As Long) As Boolean
Dim dOptColumn As Long

dOptColumn = m_gdOpt.Idx(nColumn)
IsOptSpreadBuyColumn = (dOptColumn = QOC_C_ASK Or _
                  dOptColumn = QOC_C_ASK_SIZE Or _
                  dOptColumn = QOC_C_IV_ASK Or _
                  dOptColumn = QOC_P_ASK Or _
                  dOptColumn = QOC_P_ASK_SIZE Or _
                  dOptColumn = QOC_P_IV_ASK)


End Function
Private Function IsOptSpreadSellColumn(nColumn As Long) As Boolean
Dim dOptColumn As Long

dOptColumn = m_gdOpt.Idx(nColumn)
IsOptSpreadSellColumn = (dOptColumn = QOC_C_BID Or _
                  dOptColumn = QOC_C_BID_SIZE Or _
                  dOptColumn = QOC_C_IV_BID Or _
                  dOptColumn = QOC_P_BID Or _
                  dOptColumn = QOC_P_BID_SIZE Or _
                  dOptColumn = QOC_P_IV_BID)

End Function

Private Function IsOptSpreadColumn(nColumn As Long) As Boolean
    IsOptSpreadColumn = IsOptSpreadBuyColumn(nColumn) Or IsOptSpreadSellColumn(nColumn)
End Function

Private Function IsFutSpreadBuyColumn(nColumn As Long) As Boolean
Dim dFutColumn As Long

dFutColumn = m_gdFut.Idx(nColumn)
IsFutSpreadBuyColumn = (dFutColumn = QOF_ASK)

End Function
Private Function IsFutSpreadSellColumn(nColumn As Long) As Boolean
Dim dFutColumn As Long

dFutColumn = m_gdFut.Idx(nColumn)
IsFutSpreadSellColumn = (dFutColumn = QOF_BID)

End Function

Private Function IsFutSpreadColumn(nColumn As Long) As Boolean
    IsFutSpreadColumn = IsFutSpreadBuyColumn(nColumn) Or IsFutSpreadSellColumn(nColumn)
End Function

Private Function IsUndSpreadBuyColumn(nColumn As Long) As Boolean
Dim dUndColumn As Long

dUndColumn = m_gdUnd.Idx(nColumn)
IsUndSpreadBuyColumn = (dUndColumn = QUC_ASK)

End Function
Private Function IsUndSpreadSellColumn(nColumn As Long) As Boolean
Dim dUndColumn As Long

dUndColumn = m_gdUnd.Idx(nColumn)
IsUndSpreadSellColumn = (dUndColumn = QUC_BID)

End Function

Private Function IsUndSpreadColumn(nColumn As Long) As Boolean
    IsUndSpreadColumn = IsUndSpreadBuyColumn(nColumn) Or IsUndSpreadSellColumn(nColumn)
End Function


Private Sub m_aSpreadData_OnSpreadItemAdded(ByVal pSpread As EtsMmQuotesLib.IMmQvSpreadAtom)
    On Error Resume Next
    If pSpread.Und Is Nothing Then
        If Not pSpread.Opt Is Nothing Then
            m_AuxOut.UpdateOptionsSpreadInfo pSpread, imgInSpread
        ElseIf pSpread.SpreadData.FutID <> BAD_LONG_VALUE Then
            m_AuxOut.UpdateFuturesSpreadInfo pSpread, imgInSpread, m_nMenuGridRow
        End If
    Else
        m_AuxOut.UnderlyingUpdate False, True
    End If
End Sub

Private Sub m_aSpreadData_OnSpreadItemRemoved(ByVal pSpread As EtsMmQuotesLib.IMmQvSpreadAtom)
    On Error Resume Next
    If pSpread.Und Is Nothing Then
        If Not pSpread.Opt Is Nothing Then
            m_AuxOut.UpdateOptionsSpreadInfo pSpread, Nothing
        ElseIf pSpread.SpreadData.FutID <> BAD_LONG_VALUE Then
            m_AuxOut.UpdateFuturesSpreadInfo pSpread, Nothing, m_nMenuGridRow
        End If
    Else
        m_AuxOut.UnderlyingUpdate False, True
    End If
End Sub


Public Sub ActiveFuturesChange(ByVal aUndID As Long, ByVal iActiveFutID As Long)
 On Error Resume Next
 Dim bFutureChanged As Boolean
 Dim aFut As MmQvFutAtom
 bFutureChanged = False
 
 If QV.Grp.Und.ID = aUndID Then
    If QV.Grp.Und.ActiveFuture Is Nothing Then
        If iActiveFutID > 0 Then bFutureChanged = True
    Else
        If iActiveFutID <> QV.Grp.Und.ActiveFuture.ID Then bFutureChanged = True
    End If
 End If
 If bFutureChanged Then
    If Not QV.Grp.Und.ActiveFuture Is Nothing Then Set QV.Grp.Und.ActiveFuture = Nothing
        
    For Each aFut In QV.Grp.Und.Fut
     aFut.Ratio = BAD_DOUBLE_VALUE
     If aFut.ID = iActiveFutID Then
        Set QV.Grp.Und.ActiveFuture = aFut
         aFut.Ratio = BAD_DOUBLE_VALUE
      End If
   Next
   Recalculate True
 End If
End Sub


Public Sub FuturesParamsChange(ByVal aUndID As Long, ByVal iFutID As Long, ByVal dRatio As Double, ByVal dBasis As Double)
 On Error Resume Next
 Dim bFutureChanged As Boolean
 Dim aFut As MmQvFutAtom
 bFutureChanged = False
 
 If QV.Grp.Und.ID = aUndID Then
        
    Set aFut = QV.Grp.Und.Fut(iFutID)
    If Not aFut Is Nothing Then
        If aFut.Ratio <> dRatio Then
            aFut.Ratio = dRatio
            bFutureChanged = True
        End If
        If aFut.bAsIs <> dBasis Then
            aFut.bAsIs = dBasis
            bFutureChanged = True
        End If
        If bFutureChanged Then
           Recalculate False
        End If
    End If
 End If
End Sub

Private Sub UpdateBasis(aFut As MmQvFutAtom, dBasis As Double)
    On Error GoTo Er
    gDBW.usp_MmFuture_Save aFut.ID, , , , , , dBasis
    aFut.bAsIs = dBasis
    RaiseEvent OnFutParamsChange(QV.Grp.Und.ID, aFut.ID, aFut.Ratio, aFut.bAsIs)
Exit Sub
Er:
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogFaults, "UpdateBasis " & Err.Description, m_frmOwner.GetCaption
End Sub

Private Sub UpdateRatio(aFut As MmQvFutAtom, dRatio As Double)
    On Error GoTo Er
        gDBW.usp_MmFuture_Save aFut.ID, , , , , , , , dRatio
        aFut.Ratio = dRatio
        RaiseEvent OnFutParamsChange(QV.Grp.Und.ID, aFut.ID, aFut.Ratio, aFut.bAsIs)
Exit Sub
Er:
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogFaults, "UpdateRatio " & Err.Description, m_frmOwner.GetCaption
End Sub


Private Sub UpdateActiveFutures(iFutureID As Long)
    On Error GoTo Er
    Dim aFut As MmQvFutAtom
    
    Dim bChanged As Boolean
    bChanged = False
    
    If iFutureID <> 0 Then
        QV.Grp.Und.UseManualActivePrice = False
        QV.Grp.Und.ActivePrice = 0
        g_ContractAll(QV.Grp.Und.ID).Und.manualActivePrice = 0
        gDBW.usp_MmManualPrice_Del QV.Grp.Und.ID
    End If

    If iFutureID <> 0 Then
        For Each aFut In QV.Grp.Und.Fut
        
            aFut.IsUseManualActivePrice = CBool(g_ContractAll(aFut.ID).Fut.manualActivePrice <> 0)
        
            If aFut.IsUseManualActivePrice And aFut.ID <> iFutureID Then
                aFut.IsUseManualActivePrice = False
                aFut.ActivePrice = 0
                gDBW.usp_MmManualPrice_Del aFut.ID

                SaveManualFuturePrice aFut.ID, 0

            End If
        Next
    End If
    
    
    If QV.Grp.Und.ActiveFuture Is Nothing Then
       bChanged = True
    ElseIf iFutureID <> QV.Grp.Und.ActiveFuture.ID Then
       bChanged = True
    End If
    If bChanged Then
      RaiseEvent OnActiveFutChange(QV.Grp.Und.ID, iFutureID)
      
      If Not QV.Grp.Und.ActiveFuture Is Nothing Then
           gDBW.usp_MmFuture_Save QV.Grp.Und.ActiveFuture.ID, , , , , , , False, 0
           Set QV.Grp.Und.ActiveFuture = Nothing
      End If
      
       For Each aFut In QV.Grp.Und.Fut
        aFut.Ratio = BAD_DOUBLE_VALUE
        If aFut.ID = iFutureID Then
           Set QV.Grp.Und.ActiveFuture = aFut
            aFut.Ratio = BAD_DOUBLE_VALUE
            gDBW.usp_MmFuture_Save QV.Grp.Und.ActiveFuture.ID, , , , , , , True, 0
         Else
            gDBW.usp_MmFuture_Save aFut.ID, , , , , , , False, 0
         End If
       Next
    End If
    


Exit Sub
Er:
    If Not g_PerformanceLog Is Nothing Then _
        g_PerformanceLog.LogMmInfo enLogFaults, "UpdateActiveFutures " & Err.Description, m_frmOwner.GetCaption
End Sub

Private Sub UpdateActiveFuturesPrice(newActiveFuturePrice As Double)
    
        If Not QV.Grp.Und.ActiveFuture Is Nothing Then
            QV.Grp.Und.ActiveFuture.ActivePrice = newActiveFuturePrice
            QV.Grp.Und.ActiveFuture.IsUseManualActivePrice = True
            If (Not g_ContractAll(QV.Grp.Und.ActiveFuture.ID).Fut Is Nothing) Then
                g_ContractAll(QV.Grp.Und.ActiveFuture.ID).Fut.manualActivePrice = newActiveFuturePrice
            End If
        End If
        
End Sub

Private Sub UpdateFutureManualPrice(ByVal dPrice As Double, ByVal lFutId As Long)
    If (Not g_ContractAll(lFutId) Is Nothing) Then
        If (Not g_ContractAll(lFutId).Fut Is Nothing) Then
            g_ContractAll(lFutId).Fut.manualActivePrice = dPrice
            gDBW.usp_MmManualPrice_Save lFutId, dPrice
        End If
    End If
End Sub

Private Sub SaveManualActivePrice(ID As Long, dPrice As Double)
    
    If Not g_ContractAll(ID) Is Nothing Then
        If Not g_ContractAll(ID).Und Is Nothing Then
                g_ContractAll(ID).Und.manualActivePrice = dPrice
        End If
    End If
    
End Sub

Private Sub SaveManualFuturePrice(ID As Long, dPrice As Double)
    
    If Not g_ContractAll(ID) Is Nothing Then
        If Not g_ContractAll(ID).Fut Is Nothing Then
                g_ContractAll(ID).Fut.manualActivePrice = dPrice
        End If
    End If
    
End Sub
