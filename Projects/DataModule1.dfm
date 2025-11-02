object DM: TDM
  OnCreate = DataModuleCreate
  Height = 938
  Width = 1250
  PixelsPerInch = 120
  object ADOConnection1: TADOConnection
    Left = 50
    Top = 40
  end
  object QueryDetails: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 50
    Top = 120
  end
  object QueryOrders: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 50
    Top = 200
  end
  object DataSourceDetails: TDataSource
    DataSet = QueryDetails
    Left = 180
    Top = 120
  end
  object DataSourceOrders: TDataSource
    DataSet = QueryOrders
    Left = 180
    Top = 200
  end
end
