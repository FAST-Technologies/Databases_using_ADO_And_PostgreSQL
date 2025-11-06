object FormAddOrder: TFormAddOrder
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Create New Order'
  ClientHeight = 650
  ClientWidth = 560
  Color = 15790320
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  OnCreate = FormCreate
  TextHeight = 17
  object PanelHeader: TPanel
    Left = 0
    Top = 0
    Width = 560
    Height = 60
    Align = alTop
    BevelOuter = bvNone
    Color = 5395026
    ParentBackground = False
    TabOrder = 0
    ExplicitWidth = 558
    object LabelTitle: TLabel
      Left = 20
      Top = 15
      Width = 118
      Height = 25
      Caption = #62685' New Order'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -19
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 60
    Width = 560
    Height = 530
    Align = alClient
    BevelOuter = bvNone
    Color = 14413823
    ParentBackground = False
    TabOrder = 1
    ExplicitWidth = 558
    ExplicitHeight = 522
    object Label1: TLabel
      Left = 20
      Top = 20
      Width = 51
      Height = 17
      Caption = 'Product:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 5395026
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 20
      Top = 85
      Width = 63
      Height = 17
      Caption = 'Customer:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 5395026
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 20
      Top = 150
      Width = 56
      Height = 17
      Caption = 'Quantity:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 5395026
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 290
      Top = 150
      Width = 32
      Height = 17
      Caption = 'Price:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 5395026
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 20
      Top = 215
      Width = 89
      Height = 17
      Caption = 'Payment Date:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 5395026
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label7: TLabel
      Left = 20
      Top = 280
      Width = 88
      Height = 17
      Caption = 'Shipping Date:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 5395026
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 20
      Top = 345
      Width = 95
      Height = 17
      Caption = 'Product Details:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 5395026
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ComboBoxIzdeliya: TComboBox
      Left = 20
      Top = 45
      Width = 520
      Height = 25
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnChange = ComboBoxIzdeliyaChange
    end
    object ComboBoxZakazchiki: TComboBox
      Left = 20
      Top = 110
      Width = 520
      Height = 25
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object EditKolichestvo: TEdit
      Left = 20
      Top = 175
      Width = 250
      Height = 25
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      NumbersOnly = True
      ParentFont = False
      TabOrder = 2
      Text = '1'
    end
    object EditCena: TEdit
      Left = 290
      Top = 175
      Width = 250
      Height = 25
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      Text = '0.00'
      OnKeyDown = EditCenaKeyDown
      OnKeyPress = EditCenaKeyPress
    end
    object CheckBoxDatePay: TCheckBox
      Left = 20
      Top = 240
      Width = 200
      Height = 21
      Caption = 'Specify payment date'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = CheckBoxDatePayClick
    end
    object DateTimePickerPay: TDateTimePicker
      Left = 230
      Top = 238
      Width = 150
      Height = 25
      Date = 45291.000000000000000000
      Time = 0.500000000000000000
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
    end
    object CheckBoxDateShip: TCheckBox
      Left = 20
      Top = 305
      Width = 200
      Height = 21
      Caption = 'Specify shipping date'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = CheckBoxDateShipClick
    end
    object DateTimePickerShip: TDateTimePicker
      Left = 230
      Top = 303
      Width = 150
      Height = 25
      Date = 45291.000000000000000000
      Time = 0.500000000000000000
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 7
    end
    object MemoInfo: TMemo
      Left = 20
      Top = 370
      Width = 520
      Height = 150
      Color = 15790320
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Consolas'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 8
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 590
    Width = 560
    Height = 60
    Align = alBottom
    BevelOuter = bvNone
    Color = 15790320
    ParentBackground = False
    TabOrder = 2
    ExplicitTop = 582
    ExplicitWidth = 558
    object ButtonOK: TButton
      Left = 360
      Top = 15
      Width = 90
      Height = 35
      Caption = #10004' OK'
      Default = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = ButtonOKClick
    end
    object ButtonCancel: TButton
      Left = 460
      Top = 15
      Width = 90
      Height = 35
      Cancel = True
      Caption = #10006' Cancel'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = ButtonCancelClick
    end
  end
end
