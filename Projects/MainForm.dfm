object FormMain: TFormMain
  Left = 0
  Top = 0
  Caption = 'Database Management System - Orders & Details'
  ClientHeight = 700
  ClientWidth = 1200
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 17
  
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1200
    Height = 70
    Align = alTop
    BevelOuter = bvNone
    Color = 5395026
    ParentBackground = False
    TabOrder = 0
    object Label3: TLabel
      Left = 20
      Top = 15
      Width = 400
      Height = 28
      Caption = 'Database Management System'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -21
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 20
      Top = 45
      Width = 200
      Height = 15
      Caption = 'Orders and Details Management'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 14277081
      Font.Height = -12
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
    end
    object ButtonAddOrder: TButton
      Left = 950
      Top = 15
      Width = 120
      Height = 40
      Caption = #128221' Add Order'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = ButtonAddOrderClick
    end
    object ButtonRefresh: TButton
      Left = 1080
      Top = 15
      Width = 100
      Height = 40
      Caption = #128472' Refresh'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = ButtonRefreshClick
    end
  end
  
  object Panel2: TPanel
    Left = 0
    Top = 70
    Width = 1200
    Height = 300
    Align = alTop
    BevelOuter = bvNone
    Color = 14413823
    ParentBackground = False
    Padding.Left = 10
    Padding.Top = 10
    Padding.Right = 10
    Padding.Bottom = 5
    TabOrder = 1
    object Label1: TLabel
      Left = 10
      Top = 10
      Width = 260
      Height = 19
      Caption = #128203' Details and Products (Query 1)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 5395026
      Font.Height = -16
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Panel5: TPanel
      Left = 10
      Top = 35
      Width = 1180
      Height = 3
      Align = alNone
      BevelOuter = bvNone
      Color = 12171705
      ParentBackground = False
    end
    object DBGrid1: TDBGrid
      Left = 15
      Top = 45
      Width = 1170
      Height = 245
      Anchors = [akLeft, akTop, akRight, akBottom]
      BorderStyle = bsNone
      Color = clWhite
      Ctl3D = True
      FixedColor = 5395026
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentCtl3D = False
      ParentFont = False
      PopupMenu = PopupMenu1
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = 0000000
      TitleFont.Height = -13
      TitleFont.Name = 'Segoe UI'
      TitleFont.Style = [fsBold]
      OnDrawColumnCell = DBGrid1DrawColumnCell
    end
  end
  
  object Panel3: TPanel
    Left = 0
    Top = 370
    Width = 1200
    Height = 310
    Align = alClient
	BevelOuter = bvNone
    Color = 14413823
    ParentBackground = False
    Padding.Left = 10
    Padding.Top = 10
    Padding.Right = 10
    Padding.Bottom = 10
    TabOrder = 2
    object Label2: TLabel
      Left = 10
      Top = 10
      Width = 290
      Height = 19
      Caption = #128178' Orders for Selected Detail (Query 2)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 5395026
      Font.Height = -16
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Panel6: TPanel
      Left = 10
      Top = 35
      Width = 1180
      Height = 3
      Align = alNone
      BevelOuter = bvNone
      Color = 12171705
      ParentBackground = False
    end
    object DBGrid2: TDBGrid
      Left = 15
      Top = 45
      Width = 1170
      Height = 250
      Anchors = [akLeft, akTop, akRight, akBottom]
      BorderStyle = bsNone
      Color = clWhite
      Ctl3D = True
      FixedColor = 5395026
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentCtl3D = False
      ParentFont = False
      PopupMenu = PopupMenu1
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = 0000000
      TitleFont.Height = -13
      TitleFont.Name = 'Segoe UI'
      TitleFont.Style = [fsBold]
      OnDrawColumnCell = DBGrid2DrawColumnCell
    end
  end
  
  object StatusBar1: TStatusBar
    Left = 0
    Top = 680
    Width = 1200
    Height = 20
    Panels = <>
    SimplePanel = True
    SimpleText = 'Ready'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Segoe UI'
    Font.Style = []
    UseSystemFont = False
  end
  
  object PopupMenu1: TPopupMenu
    Left = 600
    Top = 200
    object MenuAddOrder: TMenuItem
      Caption = #128221' Add New Order'
      OnClick = MenuAddOrderClick
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object MenuRefresh: TMenuItem
      Caption = #128472' Refresh Data'
      OnClick = MenuRefreshClick
    end
  end
end