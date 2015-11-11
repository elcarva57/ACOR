object Fprog: TFprog
  Left = 556
  Top = 76
  Width = 323
  Height = 565
  Caption = 'Adquisicion Programada'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object LTdateTime: TLabel
    Left = 12
    Top = 396
    Width = 68
    Height = 13
    Caption = 'Tiempo Actual'
  end
  object lEstado: TLabel
    Left = 157
    Top = 478
    Width = 33
    Height = 13
    Caption = 'Estado'
  end
  object Label3: TLabel
    Left = 13
    Top = 439
    Width = 52
    Height = 13
    Caption = 'Dia Juliano'
  end
  object LJ2000: TLabel
    Left = 14
    Top = 462
    Width = 35
    Height = 13
    Caption = 'LJ2000'
  end
  object LHSideral: TLabel
    Left = 13
    Top = 416
    Width = 46
    Height = 13
    Caption = 'LHSideral'
  end
  object LAlturaInf: TLabel
    Left = 132
    Top = 400
    Width = 45
    Height = 13
    Caption = 'Altura Inf.'
  end
  object LAlturaSup: TLabel
    Left = 133
    Top = 438
    Width = 52
    Height = 13
    Caption = 'Altura Sup.'
  end
  object LAzimut1: TLabel
    Left = 231
    Top = 398
    Width = 21
    Height = 13
    Caption = 'Az 1'
  end
  object LAzimut2: TLabel
    Left = 231
    Top = 438
    Width = 21
    Height = 13
    Caption = 'Az 2'
  end
  object Label2: TLabel
    Left = 198
    Top = 372
    Width = 82
    Height = 16
    Caption = 'HORIZONTE:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LRestante: TLabel
    Left = 133
    Top = 418
    Width = 30
    Height = 13
    Caption = 'Alt, Az'
  end
  object LPending: TLabel
    Left = 157
    Top = 462
    Width = 37
    Height = 13
    Caption = 'Pend. 0'
  end
  object LmeteoSafe: TLabel
    Left = 94
    Top = 373
    Width = 80
    Height = 13
    Caption = 'Meteo Segura'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object BCarga: TButton
    Left = 107
    Top = 500
    Width = 78
    Height = 25
    Cursor = crHandPoint
    Caption = 'Iniciar Tarea'
    TabOrder = 0
    OnClick = BCargaClick
  end
  object BParaAuto: TButton
    Left = 208
    Top = 500
    Width = 87
    Height = 25
    Caption = 'Terminar Tarea'
    TabOrder = 1
    OnClick = BParaAutoClick
  end
  object BGuardaXML: TButton
    Left = 62
    Top = 469
    Width = 75
    Height = 26
    Caption = 'Guardar XML'
    TabOrder = 2
    Visible = False
    OnClick = BGuardaXMLClick
  end
  object Mver_rtml: TMemo
    Left = 8
    Top = 8
    Width = 289
    Height = 351
    Color = cl3DLight
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = []
    Lines.Strings = (
      'Log')
    OEMConvert = True
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 3
  end
  object BLeerFichXml: TButton
    Left = 11
    Top = 501
    Width = 76
    Height = 25
    Caption = 'Leer Fichero'
    TabOrder = 4
    OnClick = BLeerFichXmlClick
  end
  object BClear: TButton
    Left = 14
    Top = 374
    Width = 57
    Height = 15
    Caption = 'Borrar'
    TabOrder = 5
    OnClick = BClearClick
  end
  object EAlturaInf: TEdit
    Left = 192
    Top = 394
    Width = 33
    Height = 21
    TabOrder = 6
    Text = '20'
  end
  object EAzimut1: TEdit
    Left = 256
    Top = 394
    Width = 33
    Height = 21
    TabOrder = 7
    Text = '0'
  end
  object EAlturaSup: TEdit
    Left = 192
    Top = 432
    Width = 33
    Height = 21
    TabOrder = 8
    Text = '90'
  end
  object EAzimut2: TEdit
    Left = 256
    Top = 433
    Width = 33
    Height = 21
    TabOrder = 9
    Text = '360'
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 136
    Top = 304
  end
  object ODxml: TOpenDialog
    Filter = 'xml|*.xml|rtml|*.rtml|txt|*.txt'
    Options = [ofHideReadOnly, ofNoNetworkButton, ofEnableSizing]
    Left = 80
    Top = 304
  end
end
