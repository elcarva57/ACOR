object FConfigMeteo: TFConfigMeteo
  Left = 291
  Top = 38
  Width = 297
  Height = 675
  Caption = 'Configuracion Meteo'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel3: TPanel
    Left = 8
    Top = 2
    Width = 266
    Height = 300
    TabOrder = 0
    object Label25: TLabel
      Left = 42
      Top = 3
      Width = 183
      Height = 16
      Caption = 'Calibracion de la Estacion'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object PFechaConf: TPanel
      Left = 7
      Top = 252
      Width = 254
      Height = 19
      Caption = '--'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object BAjustes_Meteo: TButton
      Left = 17
      Top = 274
      Width = 116
      Height = 23
      Caption = 'Guardar en Fichero'
      TabOrder = 1
      OnClick = BAjustes_MeteoClick
    end
    object Panel2: TPanel
      Left = 7
      Top = 21
      Width = 124
      Height = 228
      TabOrder = 2
      object Label1: TLabel
        Left = 16
        Top = 31
        Width = 55
        Height = 13
        Caption = 'Pluvio cm3:'
      end
      object Label2: TLabel
        Left = 15
        Top = 57
        Width = 58
        Height = 13
        Caption = 'Offset mBar:'
      end
      object Label3: TLabel
        Left = 16
        Top = 82
        Width = 41
        Height = 13
        Caption = 'Altura m:'
      end
      object Label4: TLabel
        Left = 16
        Top = 108
        Width = 45
        Height = 13
        Caption = 'Offset IR:'
      end
      object Label5: TLabel
        Left = 17
        Top = 134
        Width = 49
        Height = 13
        Caption = 'Offset UV:'
      end
      object Label13: TLabel
        Left = 18
        Top = 157
        Width = 57
        Height = 13
        Caption = 'Anem. Mec:'
      end
      object EKPluvio: TEdit
        Left = 85
        Top = 28
        Width = 31
        Height = 21
        TabOrder = 0
        Text = '0'
      end
      object EOffset_Bar: TEdit
        Left = 85
        Top = 52
        Width = 31
        Height = 21
        TabOrder = 1
        Text = '0'
      end
      object EAltura_Bar: TEdit
        Left = 85
        Top = 76
        Width = 32
        Height = 21
        TabOrder = 2
        Text = '0'
      end
      object EOffset_IR: TEdit
        Left = 85
        Top = 101
        Width = 31
        Height = 21
        TabOrder = 3
        Text = '0'
      end
      object EOffset_UV: TEdit
        Left = 85
        Top = 126
        Width = 31
        Height = 21
        TabOrder = 4
        Text = '0'
      end
      object EKAnem_mec: TEdit
        Left = 86
        Top = 151
        Width = 31
        Height = 21
        TabOrder = 5
        Text = '0'
      end
    end
    object Panel1: TPanel
      Left = 132
      Top = 21
      Width = 128
      Height = 228
      TabOrder = 3
      object Label7: TLabel
        Left = 21
        Top = 29
        Width = 38
        Height = 13
        Caption = 'zener 1:'
      end
      object Label8: TLabel
        Left = 20
        Top = 55
        Width = 38
        Height = 13
        Caption = 'zener 2:'
      end
      object Label9: TLabel
        Left = 20
        Top = 82
        Width = 38
        Height = 13
        Caption = 'zener 3:'
      end
      object Label10: TLabel
        Left = 21
        Top = 106
        Width = 38
        Height = 13
        Caption = 'zener 4:'
      end
      object Label11: TLabel
        Left = 21
        Top = 130
        Width = 38
        Height = 13
        Caption = 'zener 5:'
      end
      object Label12: TLabel
        Left = 21
        Top = 156
        Width = 38
        Height = 13
        Caption = 'zener 6:'
      end
      object Label14: TLabel
        Left = 9
        Top = 183
        Width = 16
        Height = 13
        Caption = 'K1:'
      end
      object Label15: TLabel
        Left = 66
        Top = 183
        Width = 16
        Height = 13
        Caption = 'K2:'
      end
      object Label27: TLabel
        Left = 15
        Top = 5
        Width = 100
        Height = 13
        Caption = 'Anemometro Termico'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object BCalAnemT: TButton
        Left = 27
        Top = 205
        Width = 77
        Height = 20
        Caption = 'Tomar Ref.'
        TabOrder = 0
        OnClick = BCalAnemTClick
      end
      object Ezener1: TEdit
        Left = 84
        Top = 27
        Width = 31
        Height = 21
        TabOrder = 1
        Text = '0'
      end
      object Ezener2: TEdit
        Left = 85
        Top = 53
        Width = 31
        Height = 21
        TabOrder = 2
        Text = '0'
      end
      object Ezener3: TEdit
        Left = 85
        Top = 78
        Width = 31
        Height = 21
        TabOrder = 3
        Text = '0'
      end
      object Ezener4: TEdit
        Left = 85
        Top = 102
        Width = 31
        Height = 21
        TabOrder = 4
        Text = '0'
      end
      object Ezener5: TEdit
        Left = 85
        Top = 127
        Width = 31
        Height = 21
        TabOrder = 5
        Text = '0'
      end
      object Ezener6: TEdit
        Left = 85
        Top = 152
        Width = 31
        Height = 21
        TabOrder = 6
        Text = '0'
      end
      object EK1Anem_term: TEdit
        Left = 27
        Top = 178
        Width = 36
        Height = 21
        TabOrder = 7
        Text = '0'
      end
      object EK2Anem_term: TEdit
        Left = 84
        Top = 178
        Width = 38
        Height = 21
        TabOrder = 8
        Text = '0'
      end
    end
    object BAjuste_Meteo_Flash: TButton
      Left = 141
      Top = 275
      Width = 112
      Height = 22
      Caption = 'Guardar en Estacion'
      TabOrder = 4
      OnClick = BAjuste_Meteo_FlashClick
    end
  end
  object Panel4: TPanel
    Left = 7
    Top = 453
    Width = 267
    Height = 140
    TabOrder = 1
    object Label17: TLabel
      Left = 9
      Top = 28
      Width = 81
      Height = 13
      Caption = 'Fichero Mensual:'
    end
    object Label18: TLabel
      Left = 8
      Top = 73
      Width = 59
      Height = 13
      Caption = 'Graficas jpg:'
    end
    object Label16: TLabel
      Left = 10
      Top = 119
      Width = 58
      Height = 13
      Caption = 'Puerto Serie'
    end
    object Label19: TLabel
      Left = 97
      Top = 3
      Width = 78
      Height = 16
      Caption = 'Entorno PC'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object EDirectorio: TEdit
      Left = 8
      Top = 47
      Width = 250
      Height = 21
      TabOrder = 0
      Text = 'c:\'
    end
    object BOkDirectorio: TButton
      Left = 153
      Top = 114
      Width = 106
      Height = 22
      Caption = 'Guardar'
      TabOrder = 1
      OnClick = BOkDirectorioClick
    end
    object Ejpg: TEdit
      Left = 8
      Top = 87
      Width = 250
      Height = 21
      TabOrder = 2
      Text = 'c:\'
    end
    object EPuerto: TEdit
      Left = 76
      Top = 114
      Width = 31
      Height = 21
      TabOrder = 3
      Text = '1'
    end
    object CBGuardarJPG: TCheckBox
      Left = 149
      Top = 24
      Width = 108
      Height = 20
      Caption = 'Guardar Ficheros'
      Checked = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 4
    end
  end
  object Panel5: TPanel
    Left = 8
    Top = 600
    Width = 149
    Height = 35
    TabOrder = 2
    object BSendMeteo: TButton
      Left = 13
      Top = 7
      Width = 58
      Height = 24
      Caption = 'Enviar:'
      TabOrder = 0
      OnClick = BSendMeteoClick
    end
    object EEnvMeteo: TEdit
      Left = 75
      Top = 9
      Width = 64
      Height = 21
      TabOrder = 1
      Text = '(?)'
    end
  end
  object Panel6: TPanel
    Left = 7
    Top = 304
    Width = 266
    Height = 147
    TabOrder = 3
    object Label6: TLabel
      Left = 10
      Top = 39
      Width = 69
      Height = 13
      Caption = 'Nivel Lluvia %:'
    end
    object Label20: TLabel
      Left = 10
      Top = 67
      Width = 75
      Height = 13
      Caption = 'Nivel Nubes % :'
    end
    object Label21: TLabel
      Left = 142
      Top = 68
      Width = 72
      Height = 13
      Caption = 'Nivel Fuente v:'
    end
    object Label22: TLabel
      Left = 143
      Top = 39
      Width = 50
      Height = 13
      Caption = 'Espera sg:'
    end
    object Label23: TLabel
      Left = 142
      Top = 97
      Width = 76
      Height = 13
      Caption = 'Punto Rocio '#186'C:'
    end
    object Label24: TLabel
      Left = 11
      Top = 94
      Width = 63
      Height = 13
      Caption = 'Viento KM/h:'
    end
    object Label26: TLabel
      Left = 70
      Top = 6
      Width = 129
      Height = 16
      Caption = 'Control de Salidas'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ELimiteLluvia: TEdit
      Left = 82
      Top = 34
      Width = 33
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object ELimiteNubes: TEdit
      Left = 82
      Top = 61
      Width = 32
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object ELimiteFuente: TEdit
      Left = 221
      Top = 63
      Width = 32
      Height = 21
      TabOrder = 2
      Text = '0'
    end
    object ELimiteEspera: TEdit
      Left = 221
      Top = 34
      Width = 32
      Height = 21
      TabOrder = 3
      Text = '0'
    end
    object ELimiteRocio: TEdit
      Left = 221
      Top = 91
      Width = 32
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object ELimiteKmh: TEdit
      Left = 82
      Top = 89
      Width = 32
      Height = 21
      TabOrder = 5
      Text = '0'
    end
    object BGrabar: TButton
      Left = 131
      Top = 119
      Width = 124
      Height = 21
      Caption = 'Guardar en Estacion'
      TabOrder = 6
      OnClick = BGrabarClick
    end
    object BLeer: TButton
      Left = 33
      Top = 118
      Width = 62
      Height = 21
      Caption = 'Leer'
      TabOrder = 7
      OnClick = BLeerClick
    end
  end
  object BSalir: TButton
    Left = 176
    Top = 600
    Width = 97
    Height = 35
    Caption = 'Salir'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = BSalirClick
  end
end
