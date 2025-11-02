object FormAddOrder: TFormAddOrder
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Adding new order'
  ClientHeight = 600
  ClientWidth = 520
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  OnCreate = FormCreate
  TextHeight = 15
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 520
    Height = 540
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object Label1: TLabel
      Left = 10
      Top = 10
      Width = 45
      Height = 15
      Caption = 'Product:'
    end
    object Label2: TLabel
      Left = 10
      Top = 70
      Width = 55
      Height = 15
      Caption = 'Customer:'
    end
    object Label3: TLabel
      Left = 10
      Top = 130
      Width = 49
      Height = 15
      Caption = 'Quantity:'
    end
    object Label4: TLabel
      Left = 10
      Top = 190
      Width = 29
      Height = 15
      Caption = 'Price:'
    end
    object Label6: TLabel
      Left = 10
      Top = 250
      Width = 76
      Height = 15
      Caption = 'Payment date:'
    end
    object Label7: TLabel
      Left = 10
      Top = 310
      Width = 76
      Height = 15
      Caption = 'Shipping date:'
    end
    object Label5: TLabel
      Left = 10
      Top = 370
      Width = 132
      Height = 15
      Caption = 'Information about detail:'
    end
    object ComboBoxIzdeliya: TComboBox
      Left = 10
      Top = 30
      Width = 490
      Height = 23
      Style = csDropDownList
      TabOrder = 0
      OnChange = ComboBoxIzdeliyaChange
    end
    object ComboBoxZakazchiki: TComboBox
      Left = 10
      Top = 90
      Width = 490
      Height = 23
      Style = csDropDownList
      TabOrder = 1
    end
    object EditKolichestvo: TEdit
      Left = 10
      Top = 150
      Width = 150
      Height = 23
      NumbersOnly = True
      TabOrder = 2
      Text = '1'
    end
    object EditCena: TEdit
      Left = 10
      Top = 210
      Width = 150
      Height = 23
      NumbersOnly = True
      TabOrder = 3
      Text = '0.00'
    end
    object CheckBoxDatePay: TCheckBox
      Left = 10
      Top = 270
      Width = 150
      Height = 17
      Caption = 'Specify payment date'
      TabOrder = 4
      OnClick = CheckBoxDatePayClick
    end
    object DateTimePickerPay: TDateTimePicker
      Left = 170
      Top = 268
      Width = 150
      Height = 23
      Date = 45291.000000000000000000
      Time = 0.500000000000000000
      Enabled = False
      TabOrder = 5
    end
    object CheckBoxDateShip: TCheckBox
      Left = 10
      Top = 330
      Width = 150
      Height = 17
      Caption = 'Specify shipping date'
      TabOrder = 6
      OnClick = CheckBoxDateShipClick
    end
    object DateTimePickerShip: TDateTimePicker
      Left = 170
      Top = 328
      Width = 150
      Height = 23
      Date = 45291.000000000000000000
      Time = 0.500000000000000000
      Enabled = False
      TabOrder = 7
    end
    object MemoInfo: TMemo
      Left = 10
      Top = 390
      Width = 490
      Height = 140
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 8
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 540
    Width = 520
    Height = 60
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object ButtonOK: TButton
      Left = 340
      Top = 15
      Width = 75
      Height = 30
      Caption = 'OK'
      Default = True
      TabOrder = 0
      OnClick = ButtonOKClick
    end
    object ButtonCancel: TButton
      Left = 425
      Top = 15
      Width = 75
      Height = 30
      Cancel = True
      Caption = 'Cancel'
      TabOrder = 1
      OnClick = ButtonCancelClick
    end
  end
end
