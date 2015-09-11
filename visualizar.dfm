object Form2: TForm2
  Left = 381
  Top = 267
  Width = 397
  Height = 323
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  AlphaBlendValue = 100
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Form2'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Arial'
  Font.Style = []
  FormStyle = fsStayOnTop
  Icon.Data = {
    0000010001002020100001000400E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000010000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF008888
    8888888888888800000088888888888888888888888880000008888888888888
    8888808888880000008888888888888888880008888000000888888888888888
    8880000088000000888888888888888888000FF0000000088888888888888888
    8000FFFF000000888888888888888888000FFFF0000008888888888888888880
    00FFFF000000888888888888888888000FFFF000F00008888888888888888880
    0FFF000000FF0088888888888888888800F000000FFFF0088888888888888888
    80000F00FFFFFF0088888888888888888000000FFFFFFFF00888888888888888
    000000FFFFFFFFFF0088888888888880F00000FFFFFFFFFFF00888888888880F
    0008800FFFFFFFFFFF0088888888888000F08800FFFFFFFFFFF0088888888880
    0FFF08800FFFFFFFFFFF00888888888880FFF08800FFFFFFFFFFF00888888888
    880FF008800FFFFFFFFFFF0088888888888000888800FFFFFFFFFF0008888888
    8888088888800FFFFFFFFF000088888888888888888800FFFFFFF00008888888
    888888888888800FFFFF0000888888888888888888888800FFF0000888888888
    8888888888888880000000888888888888888888888888880000088888888888
    8888888888888888800088888888888888888888888888888808888888888888
    8888888888888888888888888888888888888888888888888888888888880000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  Scaled = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseWheel = FormMouseWheel
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 15
  object Panel2: TPanel
    Left = 0
    Top = 244
    Width = 389
    Height = 45
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 0
    object Label5: TLabel
      Left = 123
      Top = 24
      Width = 67
      Height = 15
      Caption = 'Fondo cielo:'
    end
    object Label4: TLabel
      Left = 4
      Top = 26
      Width = 36
      Height = 15
      Caption = 'Media:'
    end
    object Label14: TLabel
      Left = 64
      Top = 2
      Width = 26
      Height = 13
      Caption = 'Max: '
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object Label15: TLabel
      Left = 3
      Top = 2
      Width = 24
      Height = 13
      Caption = 'Min: '
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object Label1: TLabel
      Left = 128
      Top = 3
      Width = 16
      Height = 13
      Caption = ' X: '
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 174
      Top = 3
      Width = 16
      Height = 13
      Caption = ' Y: '
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 221
      Top = 3
      Width = 25
      Height = 13
      Caption = ' Val: '
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object Edit2: TEdit
      Left = 195
      Top = 20
      Width = 40
      Height = 23
      TabOrder = 0
      Text = '-----'
    end
    object Edit1: TEdit
      Left = 43
      Top = 20
      Width = 40
      Height = 23
      TabOrder = 1
      Text = '------'
    end
    object PMax: TStaticText
      Left = 89
      Top = 2
      Width = 34
      Height = 17
      BevelOuter = bvNone
      Caption = '99999'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object PMin: TStaticText
      Left = 24
      Top = 2
      Width = 34
      Height = 17
      BevelOuter = bvNone
      Caption = '99999'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object PX: TStaticText
      Left = 146
      Top = 3
      Width = 28
      Height = 17
      BevelOuter = bvNone
      Caption = '9999'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object PY: TStaticText
      Left = 190
      Top = 3
      Width = 28
      Height = 17
      BevelOuter = bvNone
      Caption = '9999'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
    end
    object PP: TStaticText
      Left = 244
      Top = 3
      Width = 29
      Height = 17
      AutoSize = False
      BevelOuter = bvNone
      Caption = '99999'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
    end
    object Edit3: TEdit
      Left = 306
      Top = 14
      Width = 61
      Height = 23
      TabOrder = 7
      Text = 'Edit3'
    end
  end
end
