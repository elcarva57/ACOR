object Form1: TForm1
  Left = 106
  Top = 146
  Width = 800
  Height = 600
  Caption = '             Control Telescopio'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Arial'
  Font.Style = [fsBold]
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF006666
    6666666666666600000066666666666666666666666660000006666666666666
    6666606666660000006666666666666666660006666000000666666666666666
    6660000066000000666666666666666666000FF0000000066666666666666666
    6000FFFF000000666666666666666666000FFFF0000006666666666666666660
    00FFFF000000666666666666666666000FFFF000F00006666666666666666660
    0FFF000000FF0066666666666666666600F000000FFFF0066666666666666666
    60000F00FFFFFF0066666666666666666000000FFFFFFFF00666666666666666
    000000FFFFFFFFFF0066666666666660F00000FFFFFFFFFFF00666666666660F
    0006600FFFFFFFFFFF0066666666666000F06600FFFFFFFFFFF0066666666660
    0FFF06600FFFFFFFFFFF00666666666660FFF06600FFFFFFFFFFF00666666666
    660FF006600FFFFFFFFFFF0066666666666000666600FFFFFFFFFF0006666666
    6666066666600FFFFFFFFF000066666666666666666600FFFFFFF00006666666
    666666666666600FFFFF0000666666666666666666666600FFF0000666666666
    6666666666666660000000666666666666666666666666660000066666666666
    6666666666666666600066666666666666666666666666666606666666666666
    6666666666666666666666666666666666666666666666666666666666660000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Scaled = False
  OnDestroy = FormDestroy
  PixelsPerInch = 120
  TextHeight = 15
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 215
    Height = 567
    ActivePage = CAMARA
    Align = alLeft
    Constraints.MaxWidth = 215
    Constraints.MinWidth = 215
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = []
    Images = ImageList1
    MultiLine = True
    ParentFont = False
    TabHeight = 17
    TabOrder = 0
    TabPosition = tpLeft
    object CAMARA: TTabSheet
      BorderWidth = 1
      Caption = 'CAMARA'
      object PCFS: TPanel
        Left = 0
        Top = 131
        Width = 188
        Height = 22
        Align = alTop
        Alignment = taRightJustify
        BevelOuter = bvLowered
        Color = 14342874
        TabOrder = 0
      end
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 188
        Height = 39
        Align = alTop
        BevelWidth = 2
        Color = 13619151
        TabOrder = 1
        object Label6: TLabel
          Left = 57
          Top = 4
          Width = 16
          Height = 12
          Caption = 'X2:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label7: TLabel
          Left = 57
          Top = 21
          Width = 16
          Height = 12
          Caption = 'Y2:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label4: TLabel
          Left = 2
          Top = 4
          Width = 16
          Height = 12
          Caption = 'X1:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label5: TLabel
          Left = 2
          Top = 20
          Width = 16
          Height = 12
          Caption = 'Y1:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = [fsBold]
          ParentFont = False
        end
        object CBR: TCheckBox
          Left = 109
          Top = 2
          Width = 48
          Height = 16
          Caption = 'Rect.'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = CBRClick
        end
        object CBT: TCheckBox
          Left = 109
          Top = 19
          Width = 48
          Height = 16
          Caption = 'Test'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object PX1: TPanel
          Left = 20
          Top = 3
          Width = 30
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '0'
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
        object PY1: TPanel
          Left = 20
          Top = 20
          Width = 30
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '0'
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
        end
        object PX2: TPanel
          Left = 74
          Top = 3
          Width = 30
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '768'
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
        end
        object PY2: TPanel
          Left = 74
          Top = 20
          Width = 30
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '512'
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
        end
      end
      object Panel10: TPanel
        Left = 0
        Top = 63
        Width = 188
        Height = 24
        Align = alTop
        BevelWidth = 2
        Color = 13619151
        TabOrder = 2
        object Label16: TLabel
          Left = 76
          Top = 3
          Width = 21
          Height = 12
          Caption = 'msg'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label17: TLabel
          Left = 5
          Top = 4
          Width = 12
          Height = 12
          Caption = 'sg'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Esg: TEdit
          Left = 20
          Top = 3
          Width = 54
          Height = 17
          AutoSize = False
          Color = clWhite
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = [fsBold]
          MaxLength = 4
          ParentFont = False
          TabOrder = 0
          Text = '1'
        end
        object Emsg: TEdit
          Left = 101
          Top = 3
          Width = 54
          Height = 17
          AutoSize = False
          Color = clWhite
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = [fsBold]
          MaxLength = 4
          ParentFont = False
          TabOrder = 1
          Text = '0'
        end
      end
      object Panel50: TPanel
        Left = 0
        Top = 39
        Width = 188
        Height = 24
        Align = alTop
        BevelWidth = 2
        Color = 13619151
        TabOrder = 3
        object Label8: TLabel
          Left = 17
          Top = 5
          Width = 31
          Height = 12
          Caption = 'Binin: '
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object TBBinin: TTrackBar
          Left = 72
          Top = 3
          Width = 61
          Height = 19
          LineSize = 0
          Max = 4
          Min = 1
          Orientation = trHorizontal
          PageSize = 1
          Frequency = 1
          Position = 1
          SelEnd = 0
          SelStart = 0
          TabOrder = 0
          ThumbLength = 12
          TickMarks = tmBottomRight
          TickStyle = tsAuto
          OnChange = TBBininChange
        end
        object PBinin: TPanel
          Left = 52
          Top = 5
          Width = 15
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '1'
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
      end
      object Panel51: TPanel
        Left = 0
        Top = 87
        Width = 188
        Height = 44
        Align = alTop
        BevelWidth = 2
        Color = 13619151
        TabOrder = 4
        object PFoto: TPanel
          Left = 2
          Top = 2
          Width = 83
          Height = 40
          Align = alLeft
          BorderStyle = bsSingle
          Caption = 'FOTO'
          Color = clSilver
          FullRepaint = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = [fsBold, fsItalic]
          ParentFont = False
          TabOrder = 0
          OnMouseDown = PFotoMouseDown
          object IFoto: TImage
            Left = 1
            Top = 1
            Width = 77
            Height = 34
            Align = alClient
            Transparent = True
            OnMouseDown = PFotoMouseDown
            OnMouseUp = IFotoMouseUp
          end
          object SLedFoto: TShape
            Left = 67
            Top = 5
            Width = 10
            Height = 10
            Brush.Color = clGray
            Shape = stCircle
          end
        end
        object PCancel: TPanel
          Left = 140
          Top = 2
          Width = 46
          Height = 40
          Align = alRight
          BorderStyle = bsSingle
          Caption = 'Cancel'
          Color = clSilver
          FullRepaint = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          OnMouseDown = PCancelMouseDown
          OnMouseUp = PCancelMouseUp
        end
      end
      object Panel11: TPanel
        Left = 0
        Top = 153
        Width = 188
        Height = 376
        Align = alTop
        Color = 13684944
        TabOrder = 5
        object PShuter: TPanel
          Left = 30
          Top = 196
          Width = 130
          Height = 136
          BevelOuter = bvNone
          Color = clSilver
          TabOrder = 0
        end
        object PFiltro: TPanel
          Left = 30
          Top = 26
          Width = 130
          Height = 151
          BevelOuter = bvNone
          Color = clSilver
          TabOrder = 1
        end
      end
    end
    object CUPULA: TTabSheet
      BorderWidth = 2
      Caption = 'CUPULA'
      ImageIndex = 3
      object Panel12: TPanel
        Left = 19
        Top = 39
        Width = 132
        Height = 68
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Color = clSilver
        TabOrder = 0
        object Label18: TLabel
          Left = 2
          Top = 2
          Width = 62
          Height = 14
          Align = alTop
          Alignment = taCenter
          Caption = 'Interruptores'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          Transparent = True
        end
        object SpeedButton1: TSpeedButton
          Left = 2
          Top = 49
          Width = 128
          Height = 17
          Caption = 'Validar'
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          Transparent = False
          OnClick = SpeedButton1Click
        end
        object P1: TPanel
          Left = 3
          Top = 16
          Width = 16
          Height = 32
          Color = 13948116
          TabOrder = 0
          object Sbit8: TShape
            Left = 2
            Top = 2
            Width = 11
            Height = 11
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit8: TSpeedButton
            Left = 2
            Top = 15
            Width = 12
            Height = 15
            AllowAllUp = True
            GroupIndex = 8
            Caption = '8'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel14: TPanel
          Left = 19
          Top = 16
          Width = 16
          Height = 32
          Color = 14211288
          TabOrder = 1
          object Sbit7: TShape
            Left = 2
            Top = 2
            Width = 11
            Height = 11
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit7: TSpeedButton
            Left = 2
            Top = 15
            Width = 12
            Height = 15
            AllowAllUp = True
            GroupIndex = 7
            Caption = '7'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel15: TPanel
          Left = 35
          Top = 16
          Width = 16
          Height = 32
          Color = 14211288
          TabOrder = 2
          object Sbit6: TShape
            Left = 2
            Top = 2
            Width = 11
            Height = 11
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit6: TSpeedButton
            Left = 2
            Top = 15
            Width = 12
            Height = 15
            AllowAllUp = True
            GroupIndex = 6
            Caption = '6'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel16: TPanel
          Left = 51
          Top = 16
          Width = 16
          Height = 32
          Color = 14211288
          TabOrder = 3
          object Sbit5: TShape
            Left = 2
            Top = 2
            Width = 11
            Height = 11
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit5: TSpeedButton
            Left = 2
            Top = 15
            Width = 12
            Height = 15
            AllowAllUp = True
            GroupIndex = 5
            Caption = '5'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel17: TPanel
          Left = 67
          Top = 16
          Width = 16
          Height = 32
          Color = 14211288
          TabOrder = 4
          object Sbit4: TShape
            Left = 2
            Top = 2
            Width = 11
            Height = 11
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit4: TSpeedButton
            Left = 2
            Top = 15
            Width = 12
            Height = 15
            AllowAllUp = True
            GroupIndex = 4
            Caption = '4'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel18: TPanel
          Left = 83
          Top = 16
          Width = 16
          Height = 32
          Color = 14211288
          TabOrder = 5
          object Sbit3: TShape
            Left = 2
            Top = 2
            Width = 11
            Height = 11
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit3: TSpeedButton
            Left = 2
            Top = 15
            Width = 12
            Height = 15
            AllowAllUp = True
            GroupIndex = 3
            Caption = '3'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel19: TPanel
          Left = 98
          Top = 16
          Width = 16
          Height = 32
          Color = 14211288
          TabOrder = 6
          object Sbit2: TShape
            Left = 2
            Top = 2
            Width = 11
            Height = 11
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit2: TSpeedButton
            Left = 2
            Top = 15
            Width = 12
            Height = 15
            AllowAllUp = True
            GroupIndex = 2
            Caption = '2'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel20: TPanel
          Left = 114
          Top = 16
          Width = 16
          Height = 32
          Color = 14211288
          TabOrder = 7
          object Sbit1: TShape
            Left = 2
            Top = 2
            Width = 11
            Height = 11
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit1: TSpeedButton
            Left = 2
            Top = 15
            Width = 12
            Height = 15
            AllowAllUp = True
            GroupIndex = 1
            Caption = '1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
      end
      object Panel21: TPanel
        Left = 19
        Top = 153
        Width = 132
        Height = 147
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Color = clSilver
        TabOrder = 1
        object Label20: TLabel
          Left = 2
          Top = 2
          Width = 47
          Height = 14
          Align = alTop
          Alignment = taCenter
          Caption = 'Sensores'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Panel3: TPanel
          Left = 2
          Top = 115
          Width = 128
          Height = 30
          Align = alBottom
          Alignment = taRightJustify
          BevelOuter = bvNone
          Caption = 'G4 '
          Color = clGray
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clSilver
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          object Panel44: TPanel
            Left = 0
            Top = 0
            Width = 17
            Height = 30
            Color = 14671839
            TabOrder = 0
            object ss24: TShape
              Left = 2
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label43: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '6'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel43: TPanel
            Left = 17
            Top = 0
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 1
            object ss23: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label42: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '5'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel42: TPanel
            Left = 32
            Top = 0
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 2
            object ss22: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label41: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '4'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel41: TPanel
            Left = 47
            Top = 0
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 3
            object ss21: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label40: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '3'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel40: TPanel
            Left = 62
            Top = 0
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 4
            object ss20: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label39: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '2'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel39: TPanel
            Left = 77
            Top = 0
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 5
            object ss19: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label38: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '1'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
        end
        object Panel45: TPanel
          Left = 2
          Top = 81
          Width = 128
          Height = 34
          Align = alBottom
          Alignment = taRightJustify
          BevelInner = bvLowered
          Caption = 'G3 '
          Color = clGray
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clSilver
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          object Panel32: TPanel
            Left = 2
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 0
            object ss18: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label32: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '6'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel38: TPanel
            Left = 17
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 1
            object ss17: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label37: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '5'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel37: TPanel
            Left = 32
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 2
            object ss16: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label36: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '4'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel36: TPanel
            Left = 47
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 3
            object ss15: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label35: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '3'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel35: TPanel
            Left = 62
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 4
            object ss14: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label34: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '2'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel34: TPanel
            Left = 77
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 5
            object ss13: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label33: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '1'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
        end
        object Panel46: TPanel
          Left = 2
          Top = 51
          Width = 128
          Height = 30
          Align = alBottom
          Alignment = taRightJustify
          BevelOuter = bvNone
          Caption = 'G2 '
          Color = clGray
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clSilver
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          object Panel31: TPanel
            Left = 0
            Top = 0
            Width = 17
            Height = 30
            Color = 14671839
            TabOrder = 0
            object ss12: TShape
              Left = 2
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label31: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '6'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel30: TPanel
            Left = 17
            Top = 0
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 1
            object ss11: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label30: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '5'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel29: TPanel
            Left = 32
            Top = 0
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 2
            object ss10: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label29: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '4'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel28: TPanel
            Left = 47
            Top = 0
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 3
            object ss9: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label28: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '3'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel27: TPanel
            Left = 62
            Top = 0
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 4
            object ss8: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label27: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '2'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel26: TPanel
            Left = 77
            Top = 0
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 5
            object ss7: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label26: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '1'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
        end
        object Panel47: TPanel
          Left = 2
          Top = 17
          Width = 128
          Height = 34
          Align = alBottom
          Alignment = taRightJustify
          BevelInner = bvLowered
          Caption = 'G1 '
          Color = clGray
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clSilver
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          object Panel25: TPanel
            Left = 2
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 0
            object ss6: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label25: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '6'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel24: TPanel
            Left = 17
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 1
            object ss5: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label24: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '5'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel23: TPanel
            Left = 32
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 2
            object ss4: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label23: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '4'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel22: TPanel
            Left = 47
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 3
            object ss3: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label22: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '3'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel13: TPanel
            Left = 62
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 4
            object ss2: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label21: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '2'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel33: TPanel
            Left = 77
            Top = 2
            Width = 15
            Height = 30
            Color = 14671839
            TabOrder = 5
            object ss1: TShape
              Left = 1
              Top = 15
              Width = 11
              Height = 11
              Brush.Color = clGray
              Shape = stCircle
            end
            object Label19: TLabel
              Left = 1
              Top = 1
              Width = 6
              Height = 14
              Align = alTop
              Alignment = taCenter
              Caption = '1'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 482
        Width = 186
        Height = 71
        Align = alBottom
        BevelOuter = bvLowered
        TabOrder = 2
        object CBEnviar: TComboBox
          Left = 2
          Top = 2
          Width = 164
          Height = 22
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = []
          ItemHeight = 14
          ParentFont = False
          Sorted = True
          TabOrder = 0
          Text = '1'
          Items.Strings = (
            'M1'
            'M2'
            'M3'
            'M4')
        end
        object BEnviar: TBitBtn
          Left = 2
          Top = 25
          Width = 58
          Height = 22
          Caption = 'Enviar'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          OnClick = BEnviarClick
        end
        object Panel1: TPanel
          Left = 1
          Top = 49
          Width = 184
          Height = 21
          Align = alBottom
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
      end
    end
    object TELESCOPIO: TTabSheet
      BorderWidth = 2
      Caption = 'TELESCOPIO'
      ImageIndex = 2
    end
    object CONFIGURACION: TTabSheet
      BorderWidth = 1
      Caption = 'CONFIGURACION'
      ImageIndex = 1
      object PRABBIT: TPanel
        Left = 0
        Top = 535
        Width = 188
        Height = 20
        Align = alBottom
        Alignment = taLeftJustify
        BevelInner = bvLowered
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object PHOST: TPanel
        Left = 0
        Top = 515
        Width = 188
        Height = 20
        Align = alBottom
        Alignment = taLeftJustify
        BevelInner = bvLowered
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
      end
      object Panel5: TPanel
        Left = 0
        Top = 0
        Width = 188
        Height = 41
        Align = alTop
        BevelWidth = 2
        Color = 13619151
        TabOrder = 2
        object Label3: TLabel
          Left = 4
          Top = 23
          Width = 52
          Height = 12
          Caption = 'Columnas:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label2: TLabel
          Left = 93
          Top = 23
          Width = 30
          Height = 12
          Caption = 'Filas: '
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Panel8: TPanel
          Left = 2
          Top = 2
          Width = 184
          Height = 19
          Align = alTop
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentColor = True
          ParentFont = False
          TabOrder = 0
          object RBK400: TRadioButton
            Left = 4
            Top = 3
            Width = 65
            Height = 13
            BiDiMode = bdLeftToRight
            Caption = 'KAF400'
            Checked = True
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 0
            TabStop = True
            OnClick = RBK400Click
          end
          object RBK1600: TRadioButton
            Left = 66
            Top = 3
            Width = 69
            Height = 13
            Caption = 'KAF1600'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnClick = RBK1600Click
          end
        end
        object PColumnas: TPanel
          Left = 60
          Top = 23
          Width = 29
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '768'
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object PFilas: TPanel
          Left = 123
          Top = 23
          Width = 29
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '512'
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
      end
    end
    object VISUALIZACION: TTabSheet
      Caption = 'VISUALIZACION'
      ImageIndex = 1
      object Panel6: TPanel
        Left = 0
        Top = 0
        Width = 190
        Height = 52
        Align = alTop
        BevelWidth = 2
        Color = 13619151
        TabOrder = 0
        object Label12: TLabel
          Left = 9
          Top = 30
          Width = 32
          Height = 12
          Caption = 'Offset:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label13: TLabel
          Left = 9
          Top = 6
          Width = 38
          Height = 12
          Caption = 'Strecth:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object EOffset: TEdit
          Left = 47
          Top = 29
          Width = 25
          Height = 15
          AutoSize = False
          Color = clWhite
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          MaxLength = 4
          ParentFont = False
          TabOrder = 0
          Text = '0'
          OnChange = EOffsetChange
        end
        object EStretch: TEdit
          Left = 47
          Top = 6
          Width = 25
          Height = 15
          AutoSize = False
          Color = clWhite
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          MaxLength = 4
          ParentFont = False
          TabOrder = 1
          Text = '255'
          OnChange = EStretchChange
        end
        object TBSt: TTrackBar
          Left = 75
          Top = 6
          Width = 112
          Height = 22
          Max = 255
          Min = 1
          Orientation = trHorizontal
          PageSize = 1
          Frequency = 25
          Position = 255
          SelEnd = 0
          SelStart = 0
          TabOrder = 2
          ThumbLength = 12
          TickMarks = tmBoth
          TickStyle = tsNone
          OnChange = TBStChange
        end
        object TBOff: TTrackBar
          Left = 75
          Top = 27
          Width = 112
          Height = 18
          Max = 255
          Orientation = trHorizontal
          PageSize = 1
          Frequency = 25
          Position = 0
          SelEnd = 0
          SelStart = 0
          TabOrder = 3
          ThumbLength = 12
          TickMarks = tmBoth
          TickStyle = tsNone
          OnChange = TBOffChange
        end
      end
      object Panel52: TPanel
        Left = 0
        Top = 71
        Width = 190
        Height = 94
        Align = alTop
        BevelOuter = bvLowered
        TabOrder = 1
        object DG1: TDrawGrid
          Left = 1
          Top = 1
          Width = 188
          Height = 92
          Align = alClient
          BorderStyle = bsNone
          Color = 14803425
          ColCount = 7
          DefaultColWidth = 26
          DefaultRowHeight = 12
          FixedCols = 0
          RowCount = 7
          FixedRows = 0
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -8
          Font.Name = 'Small Fonts'
          Font.Style = []
          ParentFont = False
          ScrollBars = ssNone
          TabOrder = 0
        end
      end
      object Panel53: TPanel
        Left = 0
        Top = 165
        Width = 190
        Height = 94
        Align = alTop
        BevelOuter = bvLowered
        TabOrder = 2
        object DG2: TDrawGrid
          Left = 1
          Top = 1
          Width = 188
          Height = 92
          Align = alClient
          BorderStyle = bsNone
          Color = 14803425
          ColCount = 7
          DefaultColWidth = 26
          DefaultRowHeight = 12
          FixedCols = 0
          RowCount = 7
          FixedRows = 0
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -8
          Font.Name = 'Small Fonts'
          Font.Style = []
          ParentFont = False
          ScrollBars = ssNone
          TabOrder = 0
        end
      end
      object Panel54: TPanel
        Left = 0
        Top = 259
        Width = 190
        Height = 41
        Align = alTop
        BevelOuter = bvLowered
        TabOrder = 3
        object BAbrir: TBitBtn
          Left = 1
          Top = 2
          Width = 75
          Height = 37
          Caption = 'Abrir'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = BAbrirClick
        end
        object BGuardar: TBitBtn
          Left = 113
          Top = 2
          Width = 75
          Height = 37
          Caption = 'Guardar'
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = BGuardarClick
        end
      end
      object Memo1: TMemo
        Left = 0
        Top = 488
        Width = 190
        Height = 69
        Align = alBottom
        Color = clSilver
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -10
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
      end
      object Panel55: TPanel
        Left = 0
        Top = 52
        Width = 190
        Height = 19
        Align = alTop
        Color = clSilver
        TabOrder = 5
        object RBH: TRadioButton
          Left = 42
          Top = 2
          Width = 43
          Height = 14
          Caption = 'Hex.'
          Checked = True
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          TabStop = True
        end
        object RBD: TRadioButton
          Left = 104
          Top = 2
          Width = 43
          Height = 14
          Caption = 'Dec.'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
      end
    end
  end
  object Panel7: TPanel
    Left = 215
    Top = 0
    Width = 577
    Height = 567
    Align = alClient
    Caption = 'Panel7'
    TabOrder = 1
    object PFotoO: TScrollBox
      Left = 1
      Top = 1
      Width = 575
      Height = 544
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object PB1: TPaintBox
        Left = 0
        Top = 0
        Width = 519
        Height = 391
        Color = clBlack
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentColor = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        OnMouseDown = Image1MouseDown
        OnMouseMove = Image1MouseMove
        OnMouseUp = IFotoMouseUp
      end
    end
    object ToolBar1: TToolBar
      Left = 1
      Top = 545
      Width = 575
      Height = 21
      Align = alBottom
      ButtonHeight = 20
      ButtonWidth = 208
      Caption = 'ToolBar1'
      EdgeBorders = []
      EdgeInner = esNone
      Flat = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      object Panel9: TPanel
        Left = 0
        Top = 0
        Width = 117
        Height = 20
        Align = alClient
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 3
        object Label9: TLabel
          Left = 2
          Top = 3
          Width = 19
          Height = 12
          Caption = 'Col.'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label11: TLabel
          Left = 56
          Top = 3
          Width = 24
          Height = 12
          Caption = 'Filas'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object PFil: TPanel
          Left = 82
          Top = 3
          Width = 30
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '0'
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
        end
        object PCol: TPanel
          Left = 24
          Top = 3
          Width = 30
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
      end
      object Panel48: TPanel
        Left = 117
        Top = 0
        Width = 127
        Height = 20
        Align = alClient
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 0
        object Label14: TLabel
          Left = 2
          Top = 3
          Width = 24
          Height = 12
          Caption = 'Max:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label15: TLabel
          Left = 64
          Top = 3
          Width = 21
          Height = 12
          Caption = 'Min:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object PMax: TPanel
          Left = 27
          Top = 3
          Width = 35
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '0'
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
        end
        object PMin: TPanel
          Left = 87
          Top = 3
          Width = 35
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
      end
      object Panel49: TPanel
        Left = 244
        Top = 0
        Width = 140
        Height = 20
        Align = alClient
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 1
        object Label1: TLabel
          Left = 2
          Top = 3
          Width = 10
          Height = 12
          Caption = 'X:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label44: TLabel
          Left = 91
          Top = 3
          Width = 10
          Height = 12
          Caption = 'P:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label45: TLabel
          Left = 47
          Top = 3
          Width = 10
          Height = 12
          Caption = 'Y:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object PP: TPanel
          Left = 102
          Top = 3
          Width = 35
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '0'
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
        end
        object PY: TPanel
          Left = 58
          Top = 3
          Width = 30
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '0'
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object PX: TPanel
          Left = 14
          Top = 3
          Width = 30
          Height = 14
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Color = clSilver
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
      end
      object ToolButton1: TToolButton
        Left = 384
        Top = 0
        Width = 8
        AutoSize = True
        Caption = 'ToolButton1'
        Style = tbsSeparator
      end
      object PStatus: TPanel
        Left = 392
        Top = 0
        Width = 183
        Height = 20
        Align = alRight
        Alignment = taLeftJustify
        BevelOuter = bvLowered
        Color = 13752796
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        object SC: TShape
          Left = 3
          Top = 5
          Width = 10
          Height = 10
          Brush.Color = clRed
          Shape = stCircle
        end
      end
    end
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 570
    Top = 280
  end
  object ImageList1: TImageList
    Height = 15
    Masked = False
    Width = 15
    Left = 456
    Top = 167
    Bitmap = {
      494C01010400090004000F000F00FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      00000000000036000000280000003C0000002D0000000100200000000000302A
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFF0000FFFF0000FFFF0000C0C0
      C000C0C0C000C0C0C000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000C0C0C000C0C0C000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000080800000808000008080000080800000808000008080
      0000808000008080000000000000000000000000000080800000808000008080
      0000808000008080000080800000808000008080000080808000808080008080
      8000808080008080800080808000808080008080000080800000808000008080
      0000FFFF0000FFFF0000FFFF000000000000000000000000000000000000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000000000000000000000000000000000008080
      80000000000080808000FFFF0000FFFF0000FFFF0000FFFF0000808000008080
      0000808000008080000000000000808000008080000000000000000000000000
      0000808000008080000080800000808000008080000080800000808000008080
      8000808080008080800080808000000000008080800000000000808080000000
      000080808000808080008080000080800000FFFF0000FFFF0000FFFF00000000
      00000000000000000000C0C0C000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000C0C0C000000000000000
      00000000000080808000FF00FF00FF00FF00000000008080800080808000C0C0
      C000FFFF0000FFFF000080800000808000008080000000000000000000000000
      0000000000000000000000000000808000008080000080800000808000008080
      0000808000008080000080800000808080008080800000000000808080000000
      0000808080000000000080808000000000008080800000000000808080008080
      0000FFFF0000FFFF0000FFFF0000000000000000000000000000C0C0C000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF000000000000000000000000000000000000FF00FF00FF00FF00FF00
      FF000000000080808000FF00000080808000FFFF0000FFFF0000808000008080
      0000000000000000000000000000000000000000000000000000808000008080
      0000808000008080000080800000808000008080000080800000008000008080
      8000000000000000000080808000000000008080800000000000808080000000
      000080808000000000008080800080800000FFFF0000FFFF0000FFFF00000000
      0000000000000000000000000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF00008080800000000000C0C0C000C0C0
      C0008080800000000000FF00FF008080800080808000FF000000FF000000FF00
      0000C0C0C000FFFF000080800000000000000000000000000000000000000000
      0000000000000000000080800000808000008080000080800000808000008080
      0000808000008080000000800000808080000000000000000000808080000000
      0000808080000000000080808000000000008080800000000000808080008080
      0000FFFF0000FFFF0000FFFF0000000000000000000000000000000000000000
      00000000000000000000000000008080800000000000FFFF0000FFFF0000FFFF
      000000000000C0C0C000C0C0C000C0C0C000C0C0C00000000000000000000000
      000080808000FF000000FF000000FF00000080808000FFFF0000808000008080
      0000000000000000000000000000000000000000000000000000000000008080
      0000808000008080000080800000808000008080000080800000008000008080
      8000000000000000000080808000000000008080800000000000808080000000
      000080808000000000008080000080800000FFFF0000FFFF0000FFFF00000000
      000000000000000000000080800000000000000000000000000000000000C0C0
      C00080808000FFFF0000FFFF0000C0C0C0000000000000000000C0C0C000C0C0
      C000000000000000000000000000000000000000000080808000FF0000008080
      800080808000C0C0C00080800000808000000000000000000000000000000000
      0000000000000000000000000000000000008080000080800000808000008080
      0000808000008080000000800000808080000000000000000000808080008080
      8000808080008080800080808000C0C0C0008080800000000000808000008080
      0000FFFF0000FFFF0000FFFF0000000000000000000000000000C0C0C0000000
      00000000000000000000000000008080800080808000FFFF0000FFFF0000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      00000000000080808000808080008080800080808000C0C0C000808000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008080000080800000808000008080000080800000808080008080
      8000808080008080800080808000808080000000000000000000000000008080
      800080808000808080008080800080808000FFFF0000FFFF0000FFFF00000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFF0000FFFF0000C0C0C0000000000080808000000000000000
      0000808080000000000000000000000000000000000000FF000000FF00008080
      800080808000FFFF000080800000000000000000000000000000808000000000
      0000000000000000000000000000000000000000000000000000808000008080
      000080800000FF000000C0C0C000000000008080800000000000000000008080
      800000000000000000000000000080808000000000000000000080808000FF00
      0000FFFF0000FFFF0000FFFF000000000000000000000000000000000000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      000000000000C0C0C0000000000000000000C0C0C00080808000000000000000
      000000FF000000FF000000FF000000FF000080808000FFFF0000808000008080
      0000808000000000000000000000808000000000000000000000000000000000
      00000000000000000000000000008080000080800000FF000000808080008080
      8000808080000000000000000000808080000000000000000000000000008080
      80000000000000000000FF000000FFFF0000FFFF0000FFFF0000FFFF00000000
      00000000000000000000C0C0C000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF00008080800000000000C0C0C000C0C0
      C00000000000000000000000FF00000000008080800000FF000000FF00008080
      8000C0C0C000FFFF000080800000808000008080000080800000808000008080
      0000808000000000000000000000000000000000000000000000000000000000
      000080800000FF000000FF00000080808000C0C0C00080808000000000008080
      8000000000000000000080808000000000000000000080808000FF000000FF00
      0000FFFF0000FFFF0000FFFF000000000000C0C0C0000000000080808000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000808080000000000000000000000000000000FF000000FF000000
      FF0080808000808080008080800080808000FFFF0000FFFF0000808000008080
      0000808000008080000080800000808000008080000080800000000000000000
      00000000000000000000000000008080000080800000FF000000FF0000008080
      8000000000000000000080808000000000000000000000000000808080000000
      000080808000FF000000FF000000FF000000FFFF0000FFFF0000FFFF00000000
      0000C0C0C0000000000000000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000000000000000
      000000000000000000000000FF0080808000808080008080800080808000FFFF
      0000FFFF0000FFFF000080800000808000008080000080800000808000008080
      0000808000008080000080800000000000000000000000000000808000008080
      000080800000FF000000FF000000FF0000008080800080808000000000008080
      800080808000808080008080800080808000FF000000FF000000FF000000FF00
      0000FFFF0000FFFF0000FFFF000000000000000000000000000000000000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000C0C0C0008080800080808000808080008080
      800080808000C0C0C000FFFF0000FFFF0000FFFF0000FFFF0000808000008080
      0000808000008080000080800000808000008080000080800000808000008080
      00000000000080800000808000008080000080800000FF000000FFFF0000FF00
      0000FF000000FF000000FF000000808080008080800080808000FF000000FF00
      0000FF000000FF000000FF000000FF000000FFFF0000FFFF0000FFFF0000C0C0
      C000C0C0C000C0C0C000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000080800000808000008080000080800000808000008080
      0000808000008080000080800000808000008080000080800000808000008080
      000080800000FF000000FF000000FF000000FFFF0000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000424D3E000000000000003E000000280000003C0000002D00000001000100
      00000000680100000000000000000000000000000000000000000000FFFFFF00
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001500
      0000000020005540000000006000D54000000000C000D540000000000C00D540
      000000001E00C04001E002001F000E0000003000CF806EC00000300047C06EC0
      0000000003C02D80000000000180DD0002000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000}
  end
  object OD1: TOpenDialog
    Left = 298
    Top = 50
  end
  object SD1: TSaveDialog
    Left = 393
    Top = 88
  end
end
