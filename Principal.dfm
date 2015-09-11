object Form1: TForm1
  Left = 216
  Top = 76
  Width = 1024
  Height = 710
  BorderIcons = [biMinimize, biMaximize]
  Caption = '   Control Observatorio Remoto'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF006666
    6666666666666666666666666666666666667777777777777776666666666666
    6667777777777777777766666666666667777777FFF77FF77FFF777666666666
    77777F77FFF77FF77FFF7777766666667777FF77FFF77FF77FFF77F776666662
    777FFF77FFF77FF77FFF77F776666662777FFF77FFF77FF77FFF77FF76666662
    778FFF77FFF77FF77FFF77FF76666662778FFF77FFF77FF77FFF77FF76666662
    778FFF77FFF77FF77FFF77FF66666662778FFF77FFF77FF77FFF77FF66666662
    778FFF77FFF77FF77F8F77FF66666662778FFF7777777777778F77FF66666667
    777777777777777777777777766766777777777777FFFFFFF77777777777C777
    777FFFFF77FFFFFFF77FFFFF77CCC7877007FFFF77FFFFFFF77FFFFF7CCCCCC8
    7007FFFF77FFFFFFF77FFFF77CCCCCC770077FFF77FFFFFFF77FFFF77CCCCCC7
    77077FFFF77FFFFFF77FFFF7CCECCCCC77007FFFF77FFFFF77FFFF77CCCCCCCC
    770877FFF777FFFF77FFF77CCCCCCCECC788F77FF777FFF777FF777CCCCCCCCC
    C78FFF77FF77FFF77FF777CCCCCCCCCCC78FF8777777777777777CCCCCCCCCCC
    CC777700777777777777CCCCCCCCCCCCCCCCC77007777777777CCCCCCCCCCCCE
    CCCCCCCC77777777CCCCCCCECCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
    CCCECCCCCCCCCCCCCCCCCCCCCCCCCCCCC7CCCCCCCCCCCCCCCECCCCCCCCCC0000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Scaled = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 16
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 225
    Height = 675
    ActivePage = CAMARA
    Align = alLeft
    Constraints.MinWidth = 225
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -10
    Font.Name = 'Arial'
    Font.Style = []
    Images = ImageList1
    MultiLine = True
    ParentFont = False
    TabHeight = 17
    TabIndex = 0
    TabOrder = 0
    TabPosition = tpLeft
    object CAMARA: TTabSheet
      Caption = 'ADQUISICION'
      object Panel11: TPanel
        Left = 0
        Top = 308
        Width = 200
        Height = 359
        Align = alClient
        TabOrder = 0
        object Label62: TLabel
          Left = 1
          Top = 17
          Width = 198
          Height = 14
          Align = alTop
          Alignment = taCenter
          Caption = 'Filtro A               Filtro B'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label60: TLabel
          Left = 5
          Top = 323
          Width = 51
          Height = 15
          Caption = 'Eco CFS:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label43: TLabel
          Left = 1
          Top = 1
          Width = 198
          Height = 16
          Align = alTop
          Alignment = taCenter
          Caption = 'CFS'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object PShuter: TPanel
          Left = 99
          Top = 36
          Width = 100
          Height = 100
          BevelOuter = bvNone
          Color = clSilver
          TabOrder = 0
        end
        object PFiltro: TPanel
          Left = 0
          Top = 36
          Width = 100
          Height = 100
          BevelOuter = bvNone
          Color = clSilver
          TabOrder = 1
        end
        object PCFS: TPanel
          Left = 6
          Top = 339
          Width = 190
          Height = 19
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'off'
          Color = 14342874
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
        object BResetFoco: TButton
          Left = 137
          Top = 317
          Width = 60
          Height = 20
          Caption = 'Stop xyzk'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          OnClick = BResetFocoClick
        end
        object Button2: TButton
          Left = 7
          Top = 295
          Width = 48
          Height = 21
          Caption = 'Enviar:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
          OnClick = Button2Click
        end
        object EEnviar_cfs: TEdit
          Left = 56
          Top = 295
          Width = 79
          Height = 23
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          Text = '<xp>'
        end
        object Button1: TButton
          Left = 137
          Top = 295
          Width = 60
          Height = 19
          Caption = 'Stop x'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
          OnClick = Button1Click
        end
        object Panel61: TPanel
          Left = 4
          Top = 155
          Width = 194
          Height = 138
          TabOrder = 7
          object Label48: TLabel
            Left = 38
            Top = 4
            Width = 87
            Height = 15
            Caption = 'Control de Foco'
            Color = clBtnFace
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentColor = False
            ParentFont = False
          end
          object Label49: TLabel
            Left = 75
            Top = 63
            Width = 51
            Height = 15
            Caption = 'Contador'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label35: TLabel
            Left = 16
            Top = 21
            Width = 36
            Height = 15
            Caption = 'Pasos'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label36: TLabel
            Left = 89
            Top = 21
            Width = 18
            Height = 13
            Caption = 'Vel.'
          end
          object Label88: TLabel
            Left = 125
            Top = 21
            Width = 64
            Height = 15
            Caption = 'Espera, ms'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object subir: TButton
            Left = 11
            Top = 61
            Width = 50
            Height = 18
            Caption = 'Subir'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = subirClick
          end
          object bajar: TButton
            Left = 136
            Top = 62
            Width = 50
            Height = 18
            Caption = 'Bajar'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnClick = bajarClick
          end
          object PContador: TPanel
            Left = 62
            Top = 90
            Width = 68
            Height = 18
            Caption = '00000'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
          end
          object MEEstabilizar: TMaskEdit
            Left = 146
            Top = 42
            Width = 26
            Height = 18
            AutoSize = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clCream
            EditMask = '000;1; '
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 3
            ParentFont = False
            TabOrder = 3
            Text = '200'
          end
          object BInitCalibration: TButton
            Left = 137
            Top = 90
            Width = 49
            Height = 18
            Caption = 'Calibrar'
            TabOrder = 4
            OnClick = BInitCalibrationClick
          end
          object CBAutoEnfoque: TCheckBox
            Left = 140
            Top = 4
            Width = 46
            Height = 17
            Caption = 'Auto'
            State = cbGrayed
            TabOrder = 5
          end
          object BVergraf: TButton
            Left = 10
            Top = 113
            Width = 42
            Height = 18
            Caption = 'Grafico'
            TabOrder = 6
            OnClick = BVergrafClick
          end
          object BGetBFP: TButton
            Left = 138
            Top = 115
            Width = 48
            Height = 16
            Caption = 'BFP'
            Enabled = False
            TabOrder = 7
            OnClick = BGetBFPClick
          end
          object BAutoEnfoque: TButton
            Left = 61
            Top = 110
            Width = 71
            Height = 23
            Caption = 'AUTOFOCO'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 8
            OnClick = BAutoEnfoqueClick
          end
          object EVelocidadEnfoque: TEdit
            Left = 85
            Top = 38
            Width = 26
            Height = 23
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 9
            Text = '20'
            OnChange = EVelocidadEnfoqueChange
          end
          object EPasosEnfoque: TEdit
            Left = 14
            Top = 37
            Width = 45
            Height = 23
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 10
            Text = '20'
            OnChange = EPasosEnfoqueChange
          end
          object CBhfd: TCheckBox
            Left = 12
            Top = 93
            Width = 41
            Height = 17
            Caption = 'HFD'
            Checked = True
            State = cbChecked
            TabOrder = 11
          end
        end
        object CBcfs_log: TCheckBox
          Left = 66
          Top = 322
          Width = 46
          Height = 17
          Caption = 'Log'
          TabOrder = 8
        end
      end
      object Panel63: TPanel
        Left = 0
        Top = 0
        Width = 200
        Height = 308
        Align = alTop
        BevelWidth = 2
        TabOrder = 1
        object Panel5: TPanel
          Left = 3
          Top = 4
          Width = 194
          Height = 240
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          object Label2: TLabel
            Left = 7
            Top = 70
            Width = 49
            Height = 15
            Caption = 'N. Fotos:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label3: TLabel
            Left = 122
            Top = 68
            Width = 30
            Height = 15
            Caption = 'F. Act.'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label56: TLabel
            Left = 25
            Top = 203
            Width = 74
            Height = 15
            Caption = 'Guardar Fich:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object TLabel
            Left = 6
            Top = 182
            Width = 39
            Height = 15
            Caption = 'Objeto:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label17: TLabel
            Left = 9
            Top = 96
            Width = 43
            Height = 15
            Caption = 'Exp. sg:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label16: TLabel
            Left = 127
            Top = 96
            Width = 28
            Height = 15
            Caption = 'msg:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object TLabel
            Left = 5
            Top = 155
            Width = 54
            Height = 15
            Caption = 'Tipo Foto:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label39: TLabel
            Left = 117
            Top = 128
            Width = 29
            Height = 15
            Caption = 'Cont.'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label8: TLabel
            Left = 8
            Top = 39
            Width = 34
            Height = 15
            Caption = 'Binin: '
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label77: TLabel
            Left = 28
            Top = 11
            Width = 56
            Height = 16
            Alignment = taCenter
            Caption = 'CAMARA'
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label80: TLabel
            Left = 8
            Top = 126
            Width = 46
            Height = 15
            Caption = 'Paso sg'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object ENombreFichero: TEdit
            Left = 103
            Top = 201
            Width = 86
            Height = 18
            AutoSize = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clCream
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            Text = 'test'
          end
          object TNFotos: TStaticText
            Left = 160
            Top = 68
            Width = 30
            Height = 19
            Alignment = taRightJustify
            AutoSize = False
            BevelInner = bvNone
            BevelKind = bkSoft
            Caption = '1'
            Color = clBtnFace
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            TabOrder = 1
          end
          object CBGuardar: TCheckBox
            Left = 9
            Top = 201
            Width = 15
            Height = 18
            Checked = True
            Color = clBtnFace
            ParentColor = False
            State = cbChecked
            TabOrder = 2
            OnClick = CBGuardarClick
          end
          object EObjeto: TEdit
            Left = 59
            Top = 180
            Width = 129
            Height = 18
            AutoSize = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clCream
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 3
          end
          object Esg: TEdit
            Left = 62
            Top = 96
            Width = 38
            Height = 18
            AutoSize = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clCream
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 4
            ParentFont = False
            TabOrder = 4
            Text = '1'
          end
          object Emsg: TEdit
            Left = 158
            Top = 94
            Width = 32
            Height = 18
            AutoSize = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clCream
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 4
            ParentFont = False
            TabOrder = 5
            Text = '0'
          end
          object TiempoPasado: TPanel
            Left = 156
            Top = 124
            Width = 36
            Height = 19
            Alignment = taLeftJustify
            BevelOuter = bvLowered
            Caption = '0'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
          end
          object UDNFotos: TUpDown
            Left = 100
            Top = 68
            Width = 16
            Height = 18
            Associate = ENFotos
            Min = 1
            Max = 999
            Position = 1
            TabOrder = 7
            Wrap = False
          end
          object ENFotos: TEdit
            Left = 64
            Top = 68
            Width = 36
            Height = 18
            AutoSize = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clCream
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 4
            ParentFont = False
            TabOrder = 8
            Text = '1'
          end
          object CBimagen: TComboBox
            Left = 62
            Top = 151
            Width = 131
            Height = 23
            BevelInner = bvNone
            BevelKind = bkTile
            Style = csDropDownList
            Color = clCream
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ItemHeight = 15
            ItemIndex = 0
            ParentFont = False
            TabOrder = 9
            Text = 'Imagen NORMAL'
            OnChange = CBimagenChange
            Items.Strings = (
              'Imagen NORMAL'
              'Imagen BIAS'
              'Imagen DARK'
              'ENFOQUE'
              'Imagen FLAT')
          end
          object UpDown1: TUpDown
            Left = 100
            Top = 96
            Width = 16
            Height = 18
            Associate = Esg
            Min = 0
            Max = 1800
            Position = 1
            TabOrder = 10
            Wrap = False
            OnChangingEx = UpDown1ChangingEx
          end
          object TBBinin: TTrackBar
            Left = 36
            Top = 40
            Width = 45
            Height = 18
            LineSize = 0
            Max = 4
            Min = 1
            Orientation = trHorizontal
            PageSize = 1
            Frequency = 1
            Position = 1
            SelEnd = 0
            SelStart = 0
            TabOrder = 11
            ThumbLength = 14
            TickMarks = tmBottomRight
            TickStyle = tsAuto
            OnChange = TBBininChange
          end
          object PBinin: TPanel
            Left = 78
            Top = 40
            Width = 13
            Height = 16
            Alignment = taRightJustify
            BevelOuter = bvLowered
            Caption = '1'
            Enabled = False
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 12
          end
          object CBT: TCheckBox
            Left = 148
            Top = 41
            Width = 42
            Height = 16
            Caption = 'Test'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 13
          end
          object CBSelCamara: TComboBox
            Left = 91
            Top = 8
            Width = 84
            Height = 20
            BevelInner = bvNone
            BevelKind = bkTile
            Style = csOwnerDrawFixed
            Color = clActiveBorder
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ItemHeight = 14
            ItemIndex = 0
            ParentFont = False
            TabOrder = 14
            Text = 'Principal'
            OnChange = CBSelCamaraChange
            Items.Strings = (
              'Principal'
              'Auxiliar')
          end
          object ETiempoEntreFotos: TEdit
            Left = 62
            Top = 123
            Width = 39
            Height = 18
            AutoSize = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clCream
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 4
            ParentFont = False
            TabOrder = 15
            Text = '0'
          end
          object CBRectangulo: TCheckBox
            Left = 98
            Top = 41
            Width = 42
            Height = 16
            Caption = 'Rect'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 16
          end
          object CBWeb: TCheckBox
            Left = 9
            Top = 222
            Width = 128
            Height = 14
            Caption = 'Avisar Fich Existe.'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 17
          end
        end
        object Panel51: TPanel
          Left = 2
          Top = 245
          Width = 194
          Height = 60
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -17
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          object PFoto: TPanel
            Left = 1
            Top = 1
            Width = 88
            Height = 42
            Align = alLeft
            BorderStyle = bsSingle
            Caption = 'FOTO'
            Color = clSilver
            FullRepaint = False
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold, fsItalic]
            ParentFont = False
            TabOrder = 0
            object IFoto: TImage
              Left = 1
              Top = 1
              Width = 80
              Height = 36
              Transparent = True
              OnMouseDown = IFotoMouseDown
            end
            object SLedFoto: TShape
              Left = 3
              Top = 3
              Width = 16
              Height = 19
              Brush.Color = clGray
              Shape = stCircle
            end
          end
          object PCancel: TPanel
            Left = 140
            Top = 1
            Width = 53
            Height = 42
            Align = alRight
            BorderStyle = bsSingle
            Caption = 'STOP'
            Color = clSilver
            FullRepaint = False
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnMouseDown = PCancelMouseDown
            OnMouseUp = PCancelMouseUp
          end
          object PBF: TProgressBar
            Left = 1
            Top = 43
            Width = 192
            Height = 16
            Align = alBottom
            Min = 0
            Max = 100
            Smooth = True
            Step = 1
            TabOrder = 2
          end
          object Brtml: TButton
            Left = 92
            Top = 12
            Width = 46
            Height = 22
            Caption = 'RTML'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 3
            OnClick = BrtmlClick
          end
        end
      end
    end
    object TELESCOPIO: TTabSheet
      Caption = 'TELESCOPIO'
      ImageIndex = 2
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 200
        Height = 238
        TabOrder = 0
        object Panel64: TPanel
          Left = 9
          Top = 24
          Width = 198
          Height = 83
          TabOrder = 0
          object Label86: TLabel
            Left = 6
            Top = 5
            Width = 19
            Height = 15
            Caption = 'RA:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label87: TLabel
            Left = 6
            Top = 25
            Width = 29
            Height = 15
            Caption = 'DEC:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object LAzimut: TLabel
            Left = 135
            Top = 65
            Width = 6
            Height = 13
            Caption = '--'
          end
          object LAltura: TLabel
            Left = 71
            Top = 65
            Width = 6
            Height = 13
            Caption = '--'
          end
          object LAlturaRx: TLabel
            Left = 72
            Top = 51
            Width = 6
            Height = 13
            Caption = '--'
          end
          object LAzimutRx: TLabel
            Left = 135
            Top = 51
            Width = 6
            Height = 13
            Caption = '--'
          end
          object Label83: TLabel
            Left = 6
            Top = 51
            Width = 48
            Height = 13
            Caption = 'Alt Az Tel:'
          end
          object LRAgrados: TLabel
            Left = 43
            Top = 40
            Width = 18
            Height = 13
            Caption = '---.--'
          end
          object LDecgrados: TLabel
            Left = 147
            Top = 40
            Width = 15
            Height = 13
            Caption = '--.--'
          end
          object Label106: TLabel
            Left = 6
            Top = 65
            Width = 49
            Height = 13
            Caption = 'Alt Az Cal:'
          end
          object STRa: TStaticText
            Left = 40
            Top = 3
            Width = 125
            Height = 18
            Alignment = taCenter
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '-'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Courier New'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
          end
          object STDe: TStaticText
            Left = 40
            Top = 23
            Width = 125
            Height = 18
            Alignment = taCenter
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '-'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Courier New'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
          end
        end
        object Panel65: TPanel
          Left = 1
          Top = 170
          Width = 198
          Height = 63
          TabOrder = 1
          object Label46: TLabel
            Left = 6
            Top = 18
            Width = 22
            Height = 16
            Caption = 'RA:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label10: TLabel
            Left = 6
            Top = 38
            Width = 31
            Height = 16
            Caption = 'DEC:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label82: TLabel
            Left = 1
            Top = 1
            Width = 196
            Height = 15
            Align = alTop
            Alignment = taCenter
            Caption = 'Ultimo Slew Recibido:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object arecta: TStaticText
            Left = 40
            Top = 16
            Width = 125
            Height = 18
            Alignment = taCenter
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '-'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Courier New'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
          end
          object declinacion: TStaticText
            Left = 40
            Top = 36
            Width = 125
            Height = 18
            Alignment = taCenter
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '-'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Courier New'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
          end
        end
        object Panel70: TPanel
          Left = 56
          Top = 5
          Width = 97
          Height = 17
          BevelOuter = bvNone
          Caption = 'Coordenadas'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
        object Panel29: TPanel
          Left = 1
          Top = 109
          Width = 198
          Height = 59
          TabOrder = 3
          object LDECtes: TLabel
            Left = 119
            Top = 7
            Width = 6
            Height = 13
            Caption = '--'
          end
          object LARtes: TLabel
            Left = 77
            Top = 7
            Width = 6
            Height = 13
            Caption = '--'
          end
          object Label104: TLabel
            Left = 13
            Top = 15
            Width = 31
            Height = 15
            Caption = 'TESS'
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object LAltTess: TLabel
            Left = 77
            Top = 24
            Width = 6
            Height = 13
            Caption = '--'
          end
          object LAzTess: TLabel
            Left = 123
            Top = 24
            Width = 6
            Height = 13
            Caption = '--'
          end
          object LmvTess: TLabel
            Left = 15
            Top = 41
            Width = 14
            Height = 13
            Caption = 'mv'
          end
          object LTcieloTess: TLabel
            Left = 65
            Top = 41
            Width = 29
            Height = 13
            Caption = 'Tcielo'
          end
          object LTambTess: TLabel
            Left = 127
            Top = 40
            Width = 27
            Height = 13
            Caption = 'Tamb'
          end
        end
      end
      object Panel10: TPanel
        Left = 0
        Top = 240
        Width = 200
        Height = 366
        TabOrder = 1
        object Label84: TLabel
          Left = 1
          Top = 1
          Width = 198
          Height = 16
          Alignment = taCenter
          AutoSize = False
          Caption = 'Control Manual'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object PerRefreco: TLabel
          Left = 116
          Top = 195
          Width = 54
          Height = 14
          Caption = ' Refres.sg:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label105: TLabel
          Left = 165
          Top = 157
          Width = 30
          Height = 13
          Caption = 'Ver Rx'
        end
        object Panel66: TPanel
          Left = 1
          Top = 218
          Width = 198
          Height = 86
          TabOrder = 0
          object Label89: TLabel
            Left = 1
            Top = 1
            Width = 196
            Height = 15
            Align = alTop
            Alignment = taCenter
            Caption = 'Coordenadas Manuales'
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label100: TLabel
            Left = 8
            Top = 25
            Width = 19
            Height = 15
            Caption = 'AR:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label101: TLabel
            Left = 4
            Top = 57
            Width = 29
            Height = 15
            Caption = 'DEC:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Bstop: TButton
            Left = 141
            Top = 55
            Width = 50
            Height = 23
            Caption = 'STOP'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = BstopClick
          end
          object EHra: TMaskEdit
            Left = 45
            Top = 22
            Width = 21
            Height = 23
            EditMask = '00;0;0'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 2
            ParentFont = False
            TabOrder = 1
            OnChange = EHraChange
          end
          object EMra: TMaskEdit
            Left = 75
            Top = 22
            Width = 21
            Height = 23
            EditMask = '00;0;0'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 2
            ParentFont = False
            TabOrder = 2
            OnChange = MaskEditChange
          end
          object EDdec: TMaskEdit
            Left = 45
            Top = 54
            Width = 21
            Height = 23
            EditMask = '00;0;0'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 2
            ParentFont = False
            TabOrder = 4
            OnChange = EDdecChange
          end
          object EMdec: TMaskEdit
            Left = 75
            Top = 54
            Width = 21
            Height = 23
            EditMask = '00;0;0'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 2
            ParentFont = False
            TabOrder = 5
            OnChange = MaskEditChange
          end
          object stSign: TStaticText
            Left = 30
            Top = 53
            Width = 14
            Height = 21
            Hint = 'Click paraCambiar'
            Alignment = taRightJustify
            AutoSize = False
            Caption = '+'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 8
            OnClick = stSignClick
          end
          object bbGo: TBitBtn
            Left = 141
            Top = 26
            Width = 51
            Height = 20
            Caption = 'GO'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 7
            OnClick = bbGoClick
          end
          object ESra: TMaskEdit
            Left = 105
            Top = 22
            Width = 21
            Height = 23
            EditMask = '00;0;0'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 2
            ParentFont = False
            TabOrder = 3
          end
          object ESdec: TMaskEdit
            Left = 105
            Top = 54
            Width = 21
            Height = 23
            EditMask = '00;1; '
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 2
            ParentFont = False
            TabOrder = 6
            Text = '00'
          end
        end
        object Panel68: TPanel
          Left = 31
          Top = 57
          Width = 130
          Height = 130
          BevelOuter = bvLowered
          TabOrder = 1
          object BNO: TSpeedButton
            Left = 11
            Top = 12
            Width = 30
            Height = 27
            AllowAllUp = True
            GroupIndex = 2
            Caption = 'NW'
            Transparent = False
            OnClick = BOClick
            OnMouseDown = BSMouseDown
            OnMouseUp = BNOMouseUp
          end
          object BN: TSpeedButton
            Left = 45
            Top = 3
            Width = 40
            Height = 40
            AllowAllUp = True
            GroupIndex = 2
            Caption = 'N'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            Transparent = False
            OnClick = BOClick
            OnMouseDown = BSMouseDown
            OnMouseUp = BNOMouseUp
          end
          object BNE: TSpeedButton
            Left = 89
            Top = 12
            Width = 31
            Height = 27
            AllowAllUp = True
            GroupIndex = 2
            Caption = 'NE'
            Transparent = False
            OnClick = BOClick
            OnMouseDown = BSMouseDown
            OnMouseUp = BNOMouseUp
          end
          object BE: TSpeedButton
            Left = 4
            Top = 44
            Width = 40
            Height = 40
            AllowAllUp = True
            GroupIndex = 2
            Caption = 'E'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            Transparent = False
            OnClick = BOClick
            OnMouseDown = BSMouseDown
            OnMouseUp = BNOMouseUp
          end
          object BSE: TSpeedButton
            Left = 90
            Top = 88
            Width = 31
            Height = 27
            AllowAllUp = True
            GroupIndex = 2
            Caption = 'SE'
            Transparent = False
            OnClick = BOClick
            OnMouseDown = BSMouseDown
            OnMouseUp = BNOMouseUp
          end
          object BS: TSpeedButton
            Left = 45
            Top = 85
            Width = 40
            Height = 40
            AllowAllUp = True
            GroupIndex = 2
            Caption = 'S'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            Transparent = False
            OnClick = BOClick
            OnMouseDown = BSMouseDown
            OnMouseUp = BNOMouseUp
          end
          object BSO: TSpeedButton
            Left = 10
            Top = 88
            Width = 30
            Height = 27
            AllowAllUp = True
            GroupIndex = 2
            Caption = 'SW'
            Transparent = False
            OnClick = BOClick
            OnMouseDown = BSMouseDown
            OnMouseUp = BNOMouseUp
          end
          object BO: TSpeedButton
            Left = 86
            Top = 44
            Width = 40
            Height = 40
            AllowAllUp = True
            GroupIndex = 2
            Caption = 'W'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            Transparent = False
            OnClick = BOClick
            OnMouseDown = BSMouseDown
            OnMouseUp = BNOMouseUp
          end
          object SBstop: TSpeedButton
            Left = 49
            Top = 48
            Width = 33
            Height = 32
            AllowAllUp = True
            GroupIndex = 2
            Caption = 'STOP'
            Transparent = False
            OnClick = BOClick
            OnMouseDown = BSMouseDown
            OnMouseUp = BNOMouseUp
          end
        end
        object Panel69: TPanel
          Left = 1
          Top = 17
          Width = 198
          Height = 34
          BevelOuter = bvLowered
          TabOrder = 2
          object BSLW: TSpeedButton
            Left = 6
            Top = 4
            Width = 42
            Height = 26
            GroupIndex = 5
            Caption = 'SLW'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object BMOV: TSpeedButton
            Left = 54
            Top = 4
            Width = 41
            Height = 26
            GroupIndex = 5
            Caption = 'MOV '
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            Spacing = 1
          end
          object BCEN: TSpeedButton
            Left = 102
            Top = 4
            Width = 42
            Height = 26
            GroupIndex = 5
            Down = True
            Caption = 'CEN'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object BGUI: TSpeedButton
            Left = 151
            Top = 4
            Width = 45
            Height = 26
            GroupIndex = 5
            Caption = 'GUI'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object ELXsend: TEdit
          Left = 52
          Top = 192
          Width = 53
          Height = 21
          TabOrder = 3
          Text = '#:GS#'
        end
        object BSendLX: TButton
          Left = 9
          Top = 194
          Width = 41
          Height = 17
          Caption = 'Send:'
          TabOrder = 4
          OnClick = BSendLXClick
        end
        object CBver_envio_lx: TCheckBox
          Left = 175
          Top = 169
          Width = 17
          Height = 17
          Caption = 'CBver_envio'
          Checked = True
          State = cbChecked
          TabOrder = 5
        end
        object PerRefresco: TEdit
          Left = 171
          Top = 190
          Width = 22
          Height = 21
          TabOrder = 6
          Text = '2'
        end
        object Panel58: TPanel
          Left = 1
          Top = 310
          Width = 198
          Height = 51
          TabOrder = 7
          object Label85: TLabel
            Left = 1
            Top = 1
            Width = 196
            Height = 15
            Align = alTop
            Alignment = taCenter
            Caption = 'Sincronizar Coordenadas'
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object CBSincronizar: TCheckBox
            Left = 18
            Top = 23
            Width = 80
            Height = 18
            Caption = 'SkyMap'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = CBSincronizarClick
          end
          object BElbrus: TButton
            Left = 124
            Top = 25
            Width = 57
            Height = 16
            Caption = 'ELBRUS'
            TabOrder = 1
            OnClick = BElbrusClick
          end
        end
      end
      object Panel67: TPanel
        Left = 0
        Top = 626
        Width = 200
        Height = 30
        TabOrder = 2
        object Label90: TLabel
          Left = 20
          Top = 5
          Width = 46
          Height = 16
          Alignment = taCenter
          Caption = 'Estado:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object STPerdido: TStaticText
          Left = 70
          Top = 5
          Width = 115
          Height = 17
          Alignment = taCenter
          AutoSize = False
          Caption = 'DESCONECTADO'
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
      end
      object CBCGEM: TCheckBox
        Left = 16
        Top = 608
        Width = 65
        Height = 17
        Caption = 'CGEM'
        Checked = True
        State = cbChecked
        TabOrder = 3
        OnClick = CBCGEMClick
      end
      object cbPrecision: TCheckBox
        Left = 72
        Top = 608
        Width = 89
        Height = 17
        Hint = 'Precisi'#243'n normal 16 bits, alta 24 bits'
        Caption = 'Alta Precisi'#243'n'
        Checked = True
        ParentShowHint = False
        ShowHint = True
        State = cbChecked
        TabOrder = 4
        Visible = False
        OnClick = CBCGEMClick
      end
    end
    object CUPULA: TTabSheet
      BorderWidth = 2
      Caption = 'CONTROL'
      ImageIndex = 3
      object Panel12: TPanel
        Left = 0
        Top = 0
        Width = 196
        Height = 222
        Align = alTop
        BevelInner = bvRaised
        TabOrder = 0
        object Label18: TLabel
          Left = 2
          Top = 2
          Width = 192
          Height = 16
          Align = alTop
          Alignment = taCenter
          Caption = 'Alimentaciones'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          Transparent = True
        end
        object SpeedButton1: TSpeedButton
          Left = 48
          Top = 193
          Width = 93
          Height = 22
          Caption = 'Validar'
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          Transparent = False
          OnClick = SpeedButton1Click
        end
        object P1: TPanel
          Left = 24
          Top = 169
          Width = 141
          Height = 20
          Color = 13948116
          TabOrder = 0
          object Label72: TLabel
            Left = 1
            Top = 1
            Width = 139
            Height = 18
            Align = alClient
            Alignment = taCenter
            Caption = 'Auxiliar 3'
            Color = 14211288
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentColor = False
            ParentFont = False
            Transparent = True
          end
          object Sbit8: TShape
            Left = 112
            Top = 6
            Width = 10
            Height = 10
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit8: TSpeedButton
            Left = 128
            Top = 5
            Width = 12
            Height = 14
            AllowAllUp = True
            GroupIndex = 8
            Caption = '8'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel14: TPanel
          Left = 24
          Top = 149
          Width = 141
          Height = 20
          Color = 14211288
          TabOrder = 1
          object Label71: TLabel
            Left = 1
            Top = 1
            Width = 139
            Height = 18
            Align = alClient
            Alignment = taCenter
            Caption = 'Auxiliar 2'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            Transparent = True
          end
          object Sbit7: TShape
            Left = 112
            Top = 4
            Width = 10
            Height = 10
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit7: TSpeedButton
            Left = 127
            Top = 4
            Width = 12
            Height = 14
            AllowAllUp = True
            GroupIndex = 7
            Caption = '7'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel15: TPanel
          Left = 24
          Top = 129
          Width = 141
          Height = 20
          Color = 14211288
          TabOrder = 2
          object Label70: TLabel
            Left = 1
            Top = 1
            Width = 139
            Height = 18
            Align = alClient
            Alignment = taCenter
            Caption = 'Auxiliar 1'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            Transparent = True
          end
          object Sbit6: TShape
            Left = 112
            Top = 4
            Width = 10
            Height = 10
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit6: TSpeedButton
            Left = 127
            Top = 4
            Width = 12
            Height = 14
            AllowAllUp = True
            GroupIndex = 6
            Caption = '6'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel16: TPanel
          Left = 24
          Top = 109
          Width = 141
          Height = 20
          Color = 14211288
          TabOrder = 3
          object Label69: TLabel
            Left = 1
            Top = 1
            Width = 139
            Height = 18
            Align = alClient
            Alignment = taCenter
            Caption = 'Luz Flat'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            Transparent = True
          end
          object Sbit5: TShape
            Left = 112
            Top = 4
            Width = 10
            Height = 10
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit5: TSpeedButton
            Left = 127
            Top = 4
            Width = 13
            Height = 14
            AllowAllUp = True
            GroupIndex = 5
            Caption = '5'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel17: TPanel
          Left = 24
          Top = 89
          Width = 141
          Height = 20
          Color = 14211288
          TabOrder = 4
          object Label68: TLabel
            Left = 1
            Top = 1
            Width = 139
            Height = 18
            Align = alClient
            Alignment = taCenter
            Caption = 'Calentadores'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            Transparent = True
          end
          object Sbit4: TShape
            Left = 112
            Top = 4
            Width = 10
            Height = 10
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit4: TSpeedButton
            Left = 127
            Top = 4
            Width = 12
            Height = 14
            AllowAllUp = True
            GroupIndex = 4
            Caption = '4'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel18: TPanel
          Left = 24
          Top = 69
          Width = 141
          Height = 20
          Color = 14211288
          TabOrder = 5
          object Label67: TLabel
            Left = 1
            Top = 1
            Width = 139
            Height = 18
            Align = alClient
            Alignment = taCenter
            Caption = 'Apertura Obs.'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            Transparent = True
          end
          object Sbit3: TShape
            Left = 112
            Top = 4
            Width = 10
            Height = 10
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit3: TSpeedButton
            Left = 127
            Top = 4
            Width = 12
            Height = 14
            AllowAllUp = True
            GroupIndex = 3
            Caption = '3'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label66: TLabel
            Left = 20
            Top = 4
            Width = 3
            Height = 13
          end
        end
        object Panel19: TPanel
          Left = 24
          Top = 49
          Width = 141
          Height = 20
          Color = 14211288
          TabOrder = 6
          object Label65: TLabel
            Left = 1
            Top = 1
            Width = 139
            Height = 18
            Align = alClient
            Alignment = taCenter
            Caption = 'Telescopio'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            Transparent = True
          end
          object Sbit2: TShape
            Left = 112
            Top = 4
            Width = 10
            Height = 10
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit2: TSpeedButton
            Left = 127
            Top = 4
            Width = 12
            Height = 14
            AllowAllUp = True
            GroupIndex = 2
            Caption = '2'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
        object Panel20: TPanel
          Left = 24
          Top = 29
          Width = 141
          Height = 20
          Color = 14211288
          TabOrder = 7
          object Label64: TLabel
            Left = 1
            Top = 1
            Width = 139
            Height = 18
            Align = alClient
            Alignment = taCenter
            Caption = 'CCD + CFS'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            Transparent = True
          end
          object Sbit1: TShape
            Left = 112
            Top = 5
            Width = 10
            Height = 10
            Brush.Color = clGray
            Shape = stCircle
          end
          object bit1: TSpeedButton
            Left = 127
            Top = 4
            Width = 12
            Height = 14
            AllowAllUp = True
            GroupIndex = 1
            Caption = '1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
        end
      end
      object Panel21: TPanel
        Left = 0
        Top = 222
        Width = 196
        Height = 171
        Align = alTop
        BevelInner = bvRaised
        TabOrder = 1
        object Label20: TLabel
          Left = 2
          Top = 2
          Width = 192
          Height = 16
          Align = alTop
          Alignment = taCenter
          Caption = 'Sensores Estado'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Panel47: TPanel
          Left = 26
          Top = 17
          Width = 143
          Height = 140
          Alignment = taRightJustify
          BevelInner = bvLowered
          Caption = 'Grupo 1 '
          Color = 14211288
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          object Panel25: TPanel
            Left = 2
            Top = 102
            Width = 139
            Height = 20
            Align = alTop
            Color = 14671839
            TabOrder = 0
            object ss6: TShape
              Left = 124
              Top = 1
              Width = 14
              Height = 18
              Align = alRight
              Brush.Color = clGray
              Shape = stCircle
            end
            object LSensor6: TLabel
              Left = 1
              Top = 1
              Width = 123
              Height = 18
              Align = alClient
              Alignment = taCenter
              Caption = 'Alimentacion AC '
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -10
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel24: TPanel
            Left = 2
            Top = 82
            Width = 139
            Height = 20
            Align = alTop
            Color = 14671839
            TabOrder = 1
            object ss5: TShape
              Left = 124
              Top = 1
              Width = 14
              Height = 18
              Align = alRight
              Brush.Color = clGray
              Shape = stCircle
            end
            object LSensor5: TLabel
              Left = 1
              Top = 1
              Width = 123
              Height = 18
              Align = alClient
              Alignment = taCenter
              Caption = 'Alarma Perimetral'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -10
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel23: TPanel
            Left = 2
            Top = 62
            Width = 139
            Height = 20
            Align = alTop
            Color = 14671839
            TabOrder = 2
            object ss4: TShape
              Left = 124
              Top = 1
              Width = 14
              Height = 18
              Align = alRight
              Brush.Color = clGray
              Shape = stCircle
            end
            object LSensor4: TLabel
              Left = 1
              Top = 1
              Width = 123
              Height = 18
              Align = alClient
              Alignment = taCenter
              Caption = 'Puerta Observatorio'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -10
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel22: TPanel
            Left = 2
            Top = 42
            Width = 139
            Height = 20
            Align = alTop
            Color = 14671839
            TabOrder = 3
            object ss3: TShape
              Left = 124
              Top = 1
              Width = 14
              Height = 18
              Align = alRight
              Brush.Color = clGray
              Shape = stCircle
            end
            object LSensor3: TLabel
              Left = 1
              Top = 1
              Width = 123
              Height = 18
              Align = alClient
              Alignment = taCenter
              Caption = 'Limites DEC'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -10
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel13: TPanel
            Left = 2
            Top = 22
            Width = 139
            Height = 20
            Align = alTop
            Color = 14671839
            TabOrder = 4
            object ss2: TShape
              Left = 124
              Top = 1
              Width = 14
              Height = 18
              Align = alRight
              Brush.Color = clGray
              Shape = stCircle
            end
            object LSensor2: TLabel
              Left = 1
              Top = 1
              Width = 123
              Height = 18
              Align = alClient
              Alignment = taCenter
              Caption = 'Limites AR '
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -10
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object Panel33: TPanel
            Left = 2
            Top = 2
            Width = 139
            Height = 20
            Align = alTop
            Color = 14671839
            TabOrder = 5
            object ss1: TShape
              Left = 124
              Top = 1
              Width = 14
              Height = 18
              Align = alRight
              Brush.Color = clGray
              Shape = stCircle
            end
            object LSensor1: TLabel
              Left = 1
              Top = 1
              Width = 123
              Height = 18
              Align = alClient
              Alignment = taCenter
              Caption = 'Apertura Observatorio'
              Font.Charset = ANSI_CHARSET
              Font.Color = clNavy
              Font.Height = -10
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
        end
      end
      object Panel8: TPanel
        Left = 0
        Top = 393
        Width = 196
        Height = 265
        BevelInner = bvRaised
        TabOrder = 2
        object Label63: TLabel
          Left = 2
          Top = 2
          Width = 192
          Height = 16
          Align = alTop
          Alignment = taCenter
          Caption = 'Control de Temperatura'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label96: TLabel
          Left = 23
          Top = 223
          Width = 99
          Height = 15
          Caption = 'Periodo Ajuste sg:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object ESegAdj: TEdit
          Left = 132
          Top = 220
          Width = 22
          Height = 21
          TabOrder = 0
          Text = '10'
        end
        object Panel1: TPanel
          Left = 5
          Top = 29
          Width = 91
          Height = 185
          TabOrder = 1
          object Label53: TLabel
            Left = 8
            Top = 103
            Width = 39
            Height = 15
            Caption = 'T Caja:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label54: TLabel
            Left = 10
            Top = 132
            Width = 31
            Height = 15
            Caption = 'V Pel:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label81: TLabel
            Left = 9
            Top = 58
            Width = 29
            Height = 15
            Caption = 'T Adj:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label51: TLabel
            Left = 8
            Top = 34
            Width = 40
            Height = 15
            Caption = 'T CCD:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label22: TLabel
            Left = 15
            Top = 6
            Width = 56
            Height = 15
            Caption = 'CAMARA A'
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object PTcajaA: TPanel
            Left = 52
            Top = 100
            Width = 34
            Height = 17
            BevelInner = bvLowered
            BevelOuter = bvNone
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
          end
          object PVpeltierA: TPanel
            Left = 51
            Top = 131
            Width = 35
            Height = 17
            BevelInner = bvLowered
            BevelOuter = bvNone
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
          end
          object BPeltierA: TButton
            Left = 3
            Top = 153
            Width = 50
            Height = 17
            Caption = 'Manual:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            OnClick = BPeltierAClick
          end
          object EVpelt_manA: TEdit
            Left = 57
            Top = 152
            Width = 27
            Height = 21
            TabOrder = 3
            Text = '100'
          end
          object EAdj_ccdA: TEdit
            Left = 44
            Top = 57
            Width = 27
            Height = 17
            AutoSize = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clCream
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 4
            ParentFont = False
            TabOrder = 4
            Text = '-10'
          end
          object UpDadj_ccdA: TUpDown
            Left = 71
            Top = 57
            Width = 15
            Height = 17
            Associate = EAdj_ccdA
            Min = -50
            Max = 30
            Increment = 5
            Position = -10
            TabOrder = 5
            Wrap = False
          end
          object CBregularTA: TCheckBox
            Left = 47
            Top = 77
            Width = 43
            Height = 19
            Caption = 'Auto'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
          end
          object PTccdA: TPanel
            Left = 51
            Top = 32
            Width = 35
            Height = 17
            BevelInner = bvLowered
            BevelOuter = bvNone
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 7
          end
        end
        object Panel26: TPanel
          Left = 100
          Top = 29
          Width = 91
          Height = 185
          TabOrder = 2
          object Label21: TLabel
            Left = 8
            Top = 60
            Width = 29
            Height = 15
            Caption = 'T Adj:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label23: TLabel
            Left = 15
            Top = 5
            Width = 58
            Height = 15
            Caption = 'CAMARA B'
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label24: TLabel
            Left = 8
            Top = 34
            Width = 40
            Height = 15
            Caption = 'T CCD:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label25: TLabel
            Left = 8
            Top = 103
            Width = 39
            Height = 15
            Caption = 'T Caja:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object Label74: TLabel
            Left = 10
            Top = 132
            Width = 31
            Height = 15
            Caption = 'V Pel:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object BPeltierB: TButton
            Left = 5
            Top = 155
            Width = 50
            Height = 17
            Caption = 'Manual:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = BPeltierBClick
          end
          object EVpelt_manB: TEdit
            Left = 57
            Top = 154
            Width = 27
            Height = 21
            TabOrder = 1
            Text = '100'
          end
          object EAdj_ccdB: TEdit
            Left = 42
            Top = 56
            Width = 27
            Height = 17
            AutoSize = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clCream
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            MaxLength = 4
            ParentFont = False
            TabOrder = 2
            Text = '-10'
          end
          object UpDadj_ccdB: TUpDown
            Left = 69
            Top = 56
            Width = 15
            Height = 17
            Associate = EAdj_ccdB
            Min = -50
            Max = 30
            Increment = 5
            Position = -10
            TabOrder = 3
            Wrap = False
          end
          object CBregularTB: TCheckBox
            Left = 44
            Top = 76
            Width = 44
            Height = 18
            Caption = 'Auto'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 4
          end
          object PTccdB: TPanel
            Left = 51
            Top = 32
            Width = 35
            Height = 17
            BevelInner = bvLowered
            BevelOuter = bvNone
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 5
          end
          object PTcajaB: TPanel
            Left = 52
            Top = 100
            Width = 34
            Height = 17
            BevelInner = bvLowered
            BevelOuter = bvNone
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
          end
          object PVpeltierB: TPanel
            Left = 51
            Top = 131
            Width = 35
            Height = 17
            BevelInner = bvLowered
            BevelOuter = bvNone
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 7
          end
        end
        object PCFS2: TPanel
          Left = 2
          Top = 243
          Width = 190
          Height = 19
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'off'
          Color = 14342874
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
      end
    end
    object VISUALIZACION: TTabSheet
      Caption = 'VISUALIZACION'
      ImageIndex = 1
      object Panel53: TPanel
        Left = 0
        Top = 81
        Width = 200
        Height = 582
        Align = alTop
        BevelWidth = 2
        TabOrder = 0
        object DG2: TDrawGrid
          Left = 2
          Top = 59
          Width = 196
          Height = 196
          TabStop = False
          Align = alTop
          Color = 14803425
          ColCount = 7
          DefaultColWidth = 26
          DefaultRowHeight = 26
          DragMode = dmAutomatic
          Enabled = False
          FixedCols = 0
          RowCount = 7
          FixedRows = 0
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -8
          Font.Name = 'Small Fonts'
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
          ParentFont = False
          ScrollBars = ssNone
          TabOrder = 0
          OnDrawCell = DG2DrawCell
        end
        object DG1: TDrawGrid
          Left = 2
          Top = 255
          Width = 196
          Height = 124
          TabStop = False
          Align = alTop
          Color = 14803425
          ColCount = 7
          DefaultColWidth = 26
          DefaultRowHeight = 15
          Enabled = False
          FixedCols = 0
          RowCount = 7
          FixedRows = 0
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -8
          Font.Name = 'Small Fonts'
          Font.Style = []
          Options = [goVertLine, goHorzLine]
          ParentFont = False
          ScrollBars = ssNone
          TabOrder = 1
          OnDrawCell = DG2DrawCell
        end
        object Panel55: TPanel
          Left = 2
          Top = 2
          Width = 196
          Height = 57
          Align = alTop
          TabOrder = 2
          object Label9: TLabel
            Left = 1
            Top = 1
            Width = 194
            Height = 16
            Align = alTop
            Alignment = taCenter
            Caption = 'Lupa'
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label75: TLabel
            Left = 11
            Top = 23
            Width = 49
            Height = 15
            Caption = 'Formato:'
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object RBH: TRadioButton
            Left = 80
            Top = 24
            Width = 47
            Height = 16
            Caption = 'Hex.'
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = RBHClick
          end
          object RBD: TRadioButton
            Left = 137
            Top = 24
            Width = 45
            Height = 16
            Caption = 'Dec.'
            Checked = True
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            TabStop = True
            OnClick = RBHClick
          end
        end
        object BFlipx: TButton
          Left = 16
          Top = 391
          Width = 75
          Height = 25
          Caption = 'Flip X'
          TabOrder = 3
          OnClick = BFlipxClick
        end
        object BFlipy: TButton
          Left = 97
          Top = 391
          Width = 75
          Height = 25
          Caption = 'Flip Y'
          TabOrder = 4
          OnClick = BFlipyClick
        end
        object RBStreching: TRadioButton
          Left = 66
          Top = 440
          Width = 64
          Height = 16
          Caption = 'Strech'
          Checked = True
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          TabStop = True
          OnClick = RBHClick
        end
      end
      object Panel54: TPanel
        Left = 0
        Top = 0
        Width = 200
        Height = 81
        Align = alTop
        BevelWidth = 2
        TabOrder = 1
        object Label55: TLabel
          Left = 2
          Top = 2
          Width = 196
          Height = 16
          Align = alTop
          Alignment = taCenter
          Caption = 'Visualizar'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object BAbrir: TBitBtn
          Left = 10
          Top = 27
          Width = 80
          Height = 24
          Caption = 'Abrir'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = BAbrirClick
        end
        object BGuardar: TBitBtn
          Left = 120
          Top = 27
          Width = 75
          Height = 25
          Caption = 'Guardar'
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          OnClick = BGuardarClick
        end
        object PFicheroAbierto: TPanel
          Left = 2
          Top = 58
          Width = 196
          Height = 21
          Align = alBottom
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
      end
    end
    object CONFIGURACION: TTabSheet
      Caption = 'CONFIGURACION'
      ImageIndex = 4
      object Panel60: TPanel
        Left = 0
        Top = 113
        Width = 200
        Height = 75
        Align = alTop
        TabOrder = 0
        DesignSize = (
          200
          75)
        object Label52: TLabel
          Left = 14
          Top = 13
          Width = 125
          Height = 16
          Caption = 'Num. limpiados CCD:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label47: TLabel
          Left = 9
          Top = 28
          Width = 151
          Height = 16
          Caption = 'Retraso shutter dec. seg.:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object ELimpiado: TEdit
          Left = 173
          Top = 12
          Width = 18
          Height = 16
          Anchors = [akTop, akRight]
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          MaxLength = 4
          ParentFont = False
          TabOrder = 0
          Text = '4'
        end
        object ERetraso: TEdit
          Left = 172
          Top = 29
          Width = 19
          Height = 16
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          MaxLength = 4
          ParentFont = False
          TabOrder = 1
          Text = '8'
        end
        object CBPintar: TCheckBox
          Left = 6
          Top = 49
          Width = 189
          Height = 15
          Caption = 'Presentar imagen recibiendo.'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
      end
      object Panel62: TPanel
        Left = 0
        Top = 0
        Width = 200
        Height = 113
        Align = alTop
        BevelInner = bvRaised
        TabOrder = 1
        object Panel57: TPanel
          Left = 2
          Top = 2
          Width = 196
          Height = 110
          Align = alTop
          TabOrder = 0
          object Label78: TLabel
            Left = 23
            Top = 47
            Width = 13
            Height = 12
            Caption = 'X1'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label79: TLabel
            Left = 65
            Top = 48
            Width = 13
            Height = 12
            Caption = 'Y1'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label73: TLabel
            Left = 12
            Top = 3
            Width = 63
            Height = 16
            Align = alCustom
            Alignment = taCenter
            Caption = 'Camara A'
            Color = clBtnFace
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentColor = False
            ParentFont = False
          end
          object Label34: TLabel
            Left = 65
            Top = 77
            Width = 13
            Height = 12
            Caption = 'Y2'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label50: TLabel
            Left = 24
            Top = 76
            Width = 13
            Height = 12
            Caption = 'X2'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label11: TLabel
            Left = 116
            Top = 4
            Width = 63
            Height = 16
            Align = alCustom
            Alignment = taCenter
            Caption = 'Camara B'
            Color = clBtnFace
            Font.Charset = ANSI_CHARSET
            Font.Color = clMaroon
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentColor = False
            ParentFont = False
          end
          object Label42: TLabel
            Left = 163
            Top = 49
            Width = 13
            Height = 12
            Caption = 'Y1'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label92: TLabel
            Left = 121
            Top = 48
            Width = 13
            Height = 12
            Caption = 'X1'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label97: TLabel
            Left = 163
            Top = 78
            Width = 13
            Height = 12
            Caption = 'Y2'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Label98: TLabel
            Left = 122
            Top = 77
            Width = 13
            Height = 12
            Caption = 'X2'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object EFilaInicioA: TEdit
            Left = 52
            Top = 60
            Width = 41
            Height = 15
            TabStop = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clSilver
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
          end
          object EColumnaInicioA: TEdit
            Left = 7
            Top = 60
            Width = 42
            Height = 15
            TabStop = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clSilver
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
          end
          object EFilaFinA: TEdit
            Left = 53
            Top = 88
            Width = 41
            Height = 15
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clSilver
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 2
            OnChange = EFilaFinAChange
          end
          object EColumnaFinA: TEdit
            Left = 7
            Top = 88
            Width = 42
            Height = 15
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clSilver
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 3
            OnChange = EColumnaFinAChange
          end
          object CBCCD_A: TComboBox
            Left = 6
            Top = 24
            Width = 87
            Height = 21
            BevelInner = bvNone
            BevelKind = bkSoft
            Color = clCream
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = []
            ItemHeight = 13
            ParentFont = False
            TabOrder = 4
            OnChange = CBCCD_A_Change
          end
          object CBCCD_B: TComboBox
            Left = 104
            Top = 24
            Width = 86
            Height = 21
            BevelInner = bvNone
            BevelKind = bkSoft
            Color = clCream
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = []
            ItemHeight = 13
            ParentFont = False
            TabOrder = 5
            OnChange = CBCCD_B_Change
          end
          object EColumnaInicioB: TEdit
            Left = 104
            Top = 61
            Width = 42
            Height = 15
            TabStop = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clSilver
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 6
          end
          object EFilaInicioB: TEdit
            Left = 149
            Top = 61
            Width = 41
            Height = 15
            TabStop = False
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clSilver
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 7
          end
          object EFilaFinB: TEdit
            Left = 150
            Top = 88
            Width = 41
            Height = 15
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clSilver
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 8
            OnChange = EFilaFinAChange
          end
          object EColumnaFinB: TEdit
            Left = 104
            Top = 88
            Width = 42
            Height = 15
            BevelInner = bvNone
            BevelKind = bkSoft
            BorderStyle = bsNone
            Color = clSilver
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -10
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 9
            OnChange = EColumnaFinAChange
          end
        end
      end
      object Panel52: TPanel
        Left = 0
        Top = 188
        Width = 200
        Height = 339
        Align = alTop
        TabOrder = 2
        object TLabel
          Left = 10
          Top = 24
          Width = 73
          Height = 15
          Caption = 'Observatorio:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object TLabel
          Left = 8
          Top = 217
          Width = 45
          Height = 15
          Caption = 'Imagen:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label76: TLabel
          Left = 1
          Top = 1
          Width = 198
          Height = 16
          Align = alTop
          Alignment = taCenter
          Caption = 'Fichero'
          Color = clBtnFace
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
        end
        object TLabel
          Left = 13
          Top = 178
          Width = 68
          Height = 15
          Caption = 'Comentario:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object TLabel
          Left = 7
          Top = 103
          Width = 63
          Height = 15
          Caption = 'Telescopio:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object TLabel
          Left = 7
          Top = 127
          Width = 33
          Height = 15
          Caption = 'Focal:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object TLabel
          Left = 16
          Top = 146
          Width = 69
          Height = 15
          Caption = 'Instrumento:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object TLabel
          Left = 106
          Top = 127
          Width = 31
          Height = 15
          Caption = 'Apert:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object TLabel
          Left = 7
          Top = 44
          Width = 20
          Height = 15
          Caption = 'Lat.'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object TLabel
          Left = 100
          Top = 46
          Width = 24
          Height = 15
          Caption = 'Lon.'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object TLabel
          Left = 6
          Top = 240
          Width = 114
          Height = 15
          Caption = 'Directorio de trabajo:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object TLabel
          Left = 11
          Top = 61
          Width = 67
          Height = 15
          Caption = 'Observador:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object ELocation: TEdit
          Left = 88
          Top = 22
          Width = 107
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          Text = 'Terraza'
        end
        object EObserver: TEdit
          Left = 7
          Top = 77
          Width = 188
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          Text = 'Cristobal Garcia'
        end
        object EComent: TEdit
          Left = 6
          Top = 192
          Width = 188
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          Text = '-'
        end
        object ETelescop: TEdit
          Left = 79
          Top = 100
          Width = 115
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          Text = 'LX200'
        end
        object EFocal: TEdit
          Left = 43
          Top = 125
          Width = 52
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
          Text = '1600'
        end
        object EInstrument: TEdit
          Left = 7
          Top = 159
          Width = 187
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          Text = 'Audine-LP - COR'
        end
        object EApert: TEdit
          Left = 141
          Top = 125
          Width = 53
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
          Text = '20'
        end
        object ELatitud: TEdit
          Left = 27
          Top = 43
          Width = 69
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 7
          Text = '42 12 30'
        end
        object ELongitud: TEdit
          Left = 124
          Top = 44
          Width = 70
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 8
          Text = '02 50 12'
        end
        object CBFlipHorizontal: TCheckBox
          Left = 128
          Top = 216
          Width = 66
          Height = 17
          Caption = 'Flip Horiz.'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 9
        end
        object CBFlipVertical: TCheckBox
          Left = 63
          Top = 216
          Width = 61
          Height = 17
          Caption = 'Flip Vert.'
          Checked = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          State = cbChecked
          TabOrder = 10
        end
        object DirectoryListBox1: TDirectoryListBox
          Left = 3
          Top = 255
          Width = 193
          Height = 80
          Color = clMenu
          ItemHeight = 16
          TabOrder = 11
          OnChange = DirectoryListBox1Change
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 528
        Width = 200
        Height = 105
        TabOrder = 3
        object Label41: TLabel
          Left = 7
          Top = 21
          Width = 69
          Height = 14
          Caption = 'IP COR:  x.x.x.'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label91: TLabel
          Left = 62
          Top = 2
          Width = 61
          Height = 16
          Align = alCustom
          Alignment = taCenter
          Caption = 'Conexion'
          Color = clBtnFace
          Font.Charset = ANSI_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
        end
        object CBEnviar: TComboBox
          Left = 127
          Top = 81
          Width = 59
          Height = 21
          Color = clCream
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          Sorted = True
          TabOrder = 0
          Text = 'ver'
          Items.Strings = (
            '1'
            'reset')
        end
        object BEnviar: TBitBtn
          Left = 13
          Top = 82
          Width = 94
          Height = 20
          Caption = 'Comando al COR:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          OnClick = BEnviarClick
        end
        object Edit_IP: TEdit
          Left = 76
          Top = 20
          Width = 25
          Height = 15
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BorderStyle = bsNone
          Color = clCream
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          MaxLength = 4
          ParentFont = False
          TabOrder = 2
          Text = '98'
        end
        object BcambiaIP: TButton
          Left = 103
          Top = 20
          Width = 22
          Height = 16
          Caption = 'OK'
          TabOrder = 3
          OnClick = BcambiaIPClick
        end
        object PHOST: TPanel
          Left = 4
          Top = 60
          Width = 190
          Height = 19
          Alignment = taLeftJustify
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object PRABBIT: TPanel
          Left = 4
          Top = 40
          Width = 190
          Height = 18
          Alignment = taLeftJustify
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
        object CBonof: TCheckBox
          Left = 137
          Top = 21
          Width = 57
          Height = 14
          Caption = 'Activar'
          Checked = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          State = cbChecked
          TabOrder = 6
        end
      end
      object BGuardaConfig: TButton
        Left = 11
        Top = 635
        Width = 176
        Height = 21
        Caption = 'Guardar Configuraciones'
        Font.Charset = ANSI_CHARSET
        Font.Color = clGreen
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
        OnClick = BGuardaConfigClick
      end
    end
    object TSEnfoque: TTabSheet
      Caption = 'METEO'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      ImageIndex = 5
      ParentFont = False
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 200
        Height = 625
        Align = alTop
        BevelInner = bvRaised
        TabOrder = 0
        object Label26: TLabel
          Left = 23
          Top = 39
          Width = 83
          Height = 15
          Caption = 'Temp. Amb. '#186'C:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label27: TLabel
          Left = 23
          Top = 68
          Width = 92
          Height = 15
          Caption = 'Humedad rel. %:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label28: TLabel
          Left = 24
          Top = 99
          Width = 86
          Height = 15
          Caption = 'Punto Rocio '#186'C:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label29: TLabel
          Left = 2
          Top = 2
          Width = 141
          Height = 19
          Align = alTop
          Alignment = taCenter
          Caption = 'Est. Meteorol'#243'gica'
          Font.Charset = ANSI_CHARSET
          Font.Color = clGreen
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label30: TLabel
          Left = 24
          Top = 157
          Width = 100
          Height = 15
          Caption = 'Anem. Movil Km/h:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label31: TLabel
          Left = 27
          Top = 214
          Width = 36
          Height = 15
          Caption = 'Veleta:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label32: TLabel
          Left = 26
          Top = 293
          Width = 89
          Height = 15
          Caption = 'Sens. Nubes %:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label33: TLabel
          Left = 25
          Top = 319
          Width = 84
          Height = 15
          Caption = 'Sens. Lluvia %:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label37: TLabel
          Left = 26
          Top = 395
          Width = 96
          Height = 15
          Caption = 'Tension Fuente v:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label38: TLabel
          Left = 25
          Top = 129
          Width = 95
          Height = 15
          Caption = 'Pluviometro l/m2:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label93: TLabel
          Left = 27
          Top = 345
          Width = 61
          Height = 15
          Caption = 'Luz Noche:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label94: TLabel
          Left = 27
          Top = 244
          Width = 94
          Height = 15
          Caption = 'Barometro mBar:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label95: TLabel
          Left = 25
          Top = 187
          Width = 66
          Height = 15
          Caption = 'Anem.Term:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label19: TLabel
          Left = 27
          Top = 369
          Width = 58
          Height = 15
          Caption = 'Luz Dia %:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label99: TLabel
          Left = 27
          Top = 266
          Width = 72
          Height = 15
          Caption = 'Presion Abs.:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Lemav2: TLabel
          Left = 79
          Top = 20
          Width = 34
          Height = 14
          Caption = 'EMAv2'
          Font.Charset = ANSI_CHARSET
          Font.Color = clGreen
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          Visible = False
        end
        object PTempAmbiente: TPanel
          Left = 136
          Top = 37
          Width = 39
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
        object PHumedad: TPanel
          Left = 135
          Top = 67
          Width = 40
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object PPuntoRocio: TPanel
          Left = 135
          Top = 97
          Width = 40
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
        object PDirViento: TPanel
          Left = 133
          Top = 213
          Width = 42
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object PVelViento: TPanel
          Left = 134
          Top = 155
          Width = 41
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object PLluvia: TPanel
          Left = 135
          Top = 318
          Width = 40
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
        object PNublados: TPanel
          Left = 135
          Top = 292
          Width = 40
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
        end
        object PPluviometro: TPanel
          Left = 135
          Top = 127
          Width = 40
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 7
        end
        object BGraficas: TButton
          Left = 40
          Top = 423
          Width = 114
          Height = 29
          Caption = 'Ver Graficas 24h'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 8
          OnClick = BGraficasClick
        end
        object PvelOmni: TPanel
          Left = 134
          Top = 184
          Width = 41
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 9
        end
        object PVFuente: TPanel
          Left = 135
          Top = 393
          Width = 40
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 10
        end
        object PDirNSEO: TPanel
          Left = 95
          Top = 213
          Width = 33
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 11
        end
        object PLuzR: TPanel
          Left = 135
          Top = 343
          Width = 40
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 12
        end
        object PBarometro: TPanel
          Left = 124
          Top = 243
          Width = 51
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 13
        end
        object PLuzUV: TPanel
          Left = 135
          Top = 368
          Width = 40
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 14
        end
        object BCalibrarMeteo: TButton
          Left = 107
          Top = 550
          Width = 86
          Height = 23
          Caption = 'Configuracion'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 15
          OnClick = BCalibrarMeteoClick
        end
        object CBHistoriaMeteo: TCheckBox
          Left = 13
          Top = 551
          Width = 87
          Height = 22
          Caption = 'Ver Mensaje'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 16
        end
        object Panel9: TPanel
          Left = 7
          Top = 462
          Width = 187
          Height = 82
          TabOrder = 17
          object Label40: TLabel
            Left = 64
            Top = 3
            Width = 43
            Height = 16
            Caption = 'Salidas'
            Font.Charset = ANSI_CHARSET
            Font.Color = clGreen
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = []
            ParentFont = False
          end
          object PTecho: TPanel
            Left = 8
            Top = 24
            Width = 88
            Height = 23
            Caption = 'Techo'
            TabOrder = 0
          end
          object PCalentar: TPanel
            Left = 7
            Top = 53
            Width = 89
            Height = 22
            Caption = 'Calentador'
            TabOrder = 1
          end
          object BBAbrirObs: TBitBtn
            Left = 108
            Top = 22
            Width = 74
            Height = 21
            Caption = 'Abrir'
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -13
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 2
            OnClick = BBAbrirObsClick
          end
        end
        object PBarometroAbs: TPanel
          Left = 124
          Top = 265
          Width = 51
          Height = 18
          BevelInner = bvLowered
          BevelOuter = bvNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 18
        end
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'ELBRUS'
      ImageIndex = 6
      object Panel28: TPanel
        Left = 2
        Top = 80
        Width = 198
        Height = 193
        TabOrder = 0
        object PLDeriva: TLabel
          Left = 6
          Top = 4
          Width = 114
          Height = 13
          Caption = 'Num Estrellas   dX     dY'
        end
        object LDifCoord: TLabel
          Left = 70
          Top = 115
          Width = 41
          Height = 13
          Caption = 'DifCoord'
        end
        object Label102: TLabel
          Left = 35
          Top = 120
          Width = 7
          Height = 13
          Caption = 'E'
        end
        object Label103: TLabel
          Left = 32
          Top = 80
          Width = 9
          Height = 13
          Caption = 'W'
        end
        object BDerivaAqui: TButton
          Left = 48
          Top = 21
          Width = 105
          Height = 22
          Caption = 'Ver Deriva Elbrus'
          TabOrder = 0
          OnClick = BDerivaAquiClick
        end
        object BrecentrarAR: TButton
          Left = 4
          Top = 23
          Width = 41
          Height = 20
          Caption = 'AR'
          TabOrder = 1
          OnClick = BrecentrarARClick
        end
        object BrecentrarDEC: TButton
          Left = 155
          Top = 21
          Width = 41
          Height = 22
          Caption = 'DEC'
          TabOrder = 2
          OnClick = BrecentrarDECClick
        end
        object EGuiadoDecWest: TEdit
          Left = 3
          Top = 77
          Width = 25
          Height = 21
          TabOrder = 3
          Text = '300'
        end
        object EGuiadoDecimasSgDec: TEdit
          Left = 157
          Top = 77
          Width = 25
          Height = 21
          TabOrder = 4
          Text = '100'
        end
        object CBrecentrar: TCheckBox
          Left = 44
          Top = 80
          Width = 55
          Height = 16
          Caption = 'Recent'
          TabOrder = 5
        end
        object CBcalibrar: TCheckBox
          Left = 130
          Top = 167
          Width = 35
          Height = 15
          Caption = 'cal'
          TabOrder = 6
        end
        object EGuiadoCalAR: TEdit
          Left = 100
          Top = 165
          Width = 26
          Height = 21
          TabOrder = 7
          Text = '1'
        end
        object EGuiadoCalDec: TEdit
          Left = 167
          Top = 164
          Width = 25
          Height = 21
          TabOrder = 8
          Text = '1'
        end
        object CBnorte: TCheckBox
          Left = 95
          Top = 79
          Width = 30
          Height = 17
          Caption = 'N'
          TabOrder = 9
        end
        object CBsur: TCheckBox
          Left = 127
          Top = 81
          Width = 29
          Height = 13
          Caption = 'S'
          TabOrder = 10
        end
        object EGuiadoDecEste: TEdit
          Left = 9
          Top = 115
          Width = 25
          Height = 21
          TabOrder = 11
          Text = '250'
        end
        object CBProporcional: TCheckBox
          Left = 9
          Top = 168
          Width = 56
          Height = 17
          Caption = 'Fijo'
          Checked = True
          State = cbChecked
          TabOrder = 12
        end
        object EFijo: TEdit
          Left = 62
          Top = 165
          Width = 23
          Height = 21
          TabOrder = 13
          Text = '2'
        end
      end
      object Panel30: TPanel
        Left = 24
        Top = 5
        Width = 145
        Height = 17
        BevelOuter = bvNone
        Caption = 'Recentrado'
        Font.Charset = ANSI_CHARSET
        Font.Color = clMaroon
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
    end
  end
  object Panel7: TPanel
    Left = 225
    Top = 0
    Width = 783
    Height = 675
    Align = alClient
    Caption = 'Panel7'
    TabOrder = 1
    object Label61: TLabel
      Left = 1
      Top = 558
      Width = 781
      Height = 17
      Align = alBottom
      Caption = 'Cabecera fit:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object PFotoO: TScrollBox
      Left = 1
      Top = 23
      Width = 781
      Height = 535
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvRaised
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object PB1: TPaintBox
        Left = 5
        Top = 2
        Width = 630
        Height = 423
        Cursor = crArrow
        Color = clBlack
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -10
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentColor = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        OnClick = PB1Click
        OnMouseDown = PB1MouseDown
        OnMouseMove = PB1MouseMove
        OnMouseUp = PB1MouseUp
        OnPaint = PB1Paint
      end
    end
    object Panel56: TPanel
      Left = 1
      Top = 630
      Width = 781
      Height = 44
      Align = alBottom
      TabOrder = 1
      object LHoraSideral: TLabel
        Left = 437
        Top = 3
        Width = 51
        Height = 16
        Caption = 'Hsideral'
      end
      object Panel49: TPanel
        Left = 209
        Top = 3
        Width = 208
        Height = 39
        Align = alCustom
        TabOrder = 0
        object Label1: TLabel
          Left = 13
          Top = 7
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
          Left = 37
          Top = 23
          Width = 28
          Height = 12
          Caption = 'Valor:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label45: TLabel
          Left = 73
          Top = 7
          Width = 9
          Height = 12
          Caption = 'Y:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label14: TLabel
          Left = 132
          Top = 22
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
          Left = 132
          Top = 6
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
        object PP: TPanel
          Left = 71
          Top = 21
          Width = 37
          Height = 15
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
          Left = 85
          Top = 5
          Width = 36
          Height = 15
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
          Left = 25
          Top = 4
          Width = 37
          Height = 15
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
        object PMax: TPanel
          Left = 157
          Top = 20
          Width = 37
          Height = 15
          Hint = 'max'
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '0'
          Color = clSilver
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 3
        end
        object PMin: TPanel
          Left = 158
          Top = 4
          Width = 37
          Height = 15
          Hint = 'min'
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = '0'
          Color = clSilver
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -10
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 4
        end
      end
      object Panel59: TPanel
        Left = 4
        Top = 3
        Width = 203
        Height = 38
        TabOrder = 1
        object Label4: TLabel
          Left = 68
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
        object Label6: TLabel
          Left = 135
          Top = 5
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
        object Label5: TLabel
          Left = 69
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
        object Label7: TLabel
          Left = 135
          Top = 20
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
        object Label57: TLabel
          Left = 4
          Top = 4
          Width = 59
          Height = 16
          Caption = 'Recuadro:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Pitch = fpFixed
          Font.Style = []
          ParentFont = False
        end
        object PX1: TPanel
          Left = 90
          Top = 4
          Width = 37
          Height = 15
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
        object PX2: TPanel
          Left = 154
          Top = 4
          Width = 36
          Height = 15
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
        object PY1: TPanel
          Left = 90
          Top = 20
          Width = 37
          Height = 15
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
        object PY2: TPanel
          Left = 154
          Top = 20
          Width = 37
          Height = 15
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
          TabOrder = 3
        end
        object PRecuadro: TPanel
          Left = 8
          Top = 20
          Width = 57
          Height = 15
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
          TabOrder = 4
        end
      end
      object Panel27: TPanel
        Left = 523
        Top = 4
        Width = 94
        Height = 37
        TabOrder = 2
        object Label59: TLabel
          Left = 5
          Top = 19
          Width = 54
          Height = 14
          Caption = 'Fallos UDP:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object Label58: TLabel
          Left = 3
          Top = 1
          Width = 58
          Height = 16
          Caption = 'Conexion:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object SC: TShape
          Left = 68
          Top = 5
          Width = 12
          Height = 13
          Brush.Color = clRed
          Shape = stCircle
        end
        object PPerdidos: TPanel
          Left = 62
          Top = 19
          Width = 26
          Height = 14
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -10
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
      end
      object BHistoria: TButton
        Left = 434
        Top = 21
        Width = 71
        Height = 20
        Caption = 'Mensajes'
        TabOrder = 3
        OnClick = BHistoriaClick
      end
      object Button3: TButton
        Left = 660
        Top = 3
        Width = 28
        Height = 24
        Caption = 'F 3'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = Button3Click
      end
      object PStatus: TPanel
        Left = 667
        Top = 28
        Width = 17
        Height = 13
        TabOrder = 5
      end
    end
    object Memo1: TMemo
      Left = 1
      Top = 575
      Width = 781
      Height = 55
      Align = alBottom
      Color = clSilver
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 2
    end
    object Panel6: TPanel
      Left = 1
      Top = 1
      Width = 781
      Height = 22
      Align = alTop
      TabOrder = 3
      object Label12: TLabel
        Left = 5
        Top = 4
        Width = 37
        Height = 15
        Caption = 'Negro:'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object Label13: TLabel
        Left = 210
        Top = 4
        Width = 41
        Height = 15
        Caption = 'Blanco:'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object TLabel
        Left = 570
        Top = 2
        Width = 26
        Height = 16
        Caption = 'f c +'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object TLabel
        Left = 504
        Top = 2
        Width = 22
        Height = 16
        Caption = 'f c -'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object Ex0: TEdit
        Left = 45
        Top = 3
        Width = 42
        Height = 15
        AutoSize = False
        BevelInner = bvNone
        BevelKind = bkSoft
        BorderStyle = bsNone
        Color = clCream
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        MaxLength = 4
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
        Text = '0'
      end
      object Ey0: TEdit
        Left = 253
        Top = 3
        Width = 42
        Height = 15
        AutoSize = False
        BevelInner = bvNone
        BevelKind = bkSoft
        BorderStyle = bsNone
        Color = clCream
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        MaxLength = 4
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
        Text = '32767'
      end
      object TBy0: TTrackBar
        Left = 295
        Top = 4
        Width = 115
        Height = 17
        LineSize = 10
        Max = 32767
        Min = 1
        Orientation = trHorizontal
        PageSize = 50
        Frequency = 25
        Position = 32767
        SelEnd = 0
        SelStart = 0
        TabOrder = 2
        ThumbLength = 10
        TickMarks = tmBoth
        TickStyle = tsNone
        OnChange = TBx0Change
      end
      object TBx0: TTrackBar
        Left = 91
        Top = 5
        Width = 115
        Height = 16
        LineSize = 10
        Max = 32767
        Orientation = trHorizontal
        PageSize = 50
        Frequency = 25
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 3
        ThumbLength = 10
        TickMarks = tmBoth
        TickStyle = tsNone
        OnChange = TBx0Change
      end
      object estirar_alto: TEdit
        Left = 597
        Top = 3
        Width = 38
        Height = 16
        AutoSize = False
        BevelInner = bvNone
        BevelKind = bkSoft
        BorderStyle = bsNone
        Color = clCream
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        Text = '400'
      end
      object CBautostrech: TCheckBox
        Left = 416
        Top = 4
        Width = 83
        Height = 17
        Caption = 'Visu. Auto'
        Checked = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        State = cbChecked
        TabOrder = 5
      end
      object estirar_bajo: TEdit
        Left = 527
        Top = 2
        Width = 38
        Height = 16
        AutoSize = False
        BevelInner = bvNone
        BevelKind = bkSoft
        BorderStyle = bsNone
        Color = clCream
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        TabOrder = 6
        Text = '100'
      end
    end
  end
  object OD1: TOpenDialog
    Filter = 'Fit files (*.fit)|*.FIT'
    Left = 259
    Top = 54
  end
  object SD1: TSaveDialog
    Filter = 'fit|*.fit;*.FIT'
    Left = 257
    Top = 104
  end
  object ImageList1: TImageList
    Height = 15
    Masked = False
    Width = 15
    Left = 261
    Top = 299
    Bitmap = {
      494C01010600090004000F000F00FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      00000000000036000000280000003C0000002D0000000100200000000000302A
      0000000000000000000000000000000000000808080008081000101010001010
      1000100810000808080010080800181818004A4A4A00B5BDBD00CED6D600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED6000000000000000000C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00C6C6C600C6C6C600D6D6D6004242
      4200101010005252520073737300635A6300393939004A4A4A00ADADAD00CECE
      CE00C6C6C600C6C6C600C6C6C600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00C6C6C600C6C6C600C6C6C600A5A5A5008C8C8C0084848400848484008484
      8400B5B5B500D6D6D600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CECECE00CED6D6005252520008081000181818002929290063636300ADAD
      B5006B6B6B0029292900211818001810180010101800949C9C00D6DEDE00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600000000000000
      0000C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600940000009C0000009C000000A500
      00009C000000A5000000A5000000AD000000AD000000AD000000AD000000B500
      0000B5000000BD000000BD000000C6000000BD000000C6000000C6000000CE00
      0000CE000000CE000000CE000000D6000000D6000000DE000000DE000000E700
      0000DE000000E7000000E7000000EF000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF006B000000730000007300000073000000730000007B0000007B0000008400
      00007B00000084000000840000008C000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED60000000000C6CE
      D600C6000000C6000000CE000000C6000000CE000000CE000000D6000000D600
      000000000000DE000000DE000000DE000000E7000000E7000000EF000000E700
      0000EF000000EF000000F7000000F7000000FF000000FF00000000000000FFFF
      FF00C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CED600C6CE
      D600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000009C0000009C0000009C00
      0000A5000000A5000000AD000000AD000000B5000000AD000000B5000000B500
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0000000000FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0000000000FFFFFF007B000000FFFFFF0000000000FFFFFF007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B000000FFFFFF000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600CECECE00CECECE0084848400B5B5B500BD84
      5200B57B4200BD844A00BD844A00BD844A00BD844A00BD844A00B58C6300BD84
      5200B57B4A00B5844A00B5844A00B5844A00B57B4200B5844A00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6CEC6008C8C
      8C004A4A4A00736B7300A5A5A500B5733100AD733100B5733100B5733100BD73
      3100B5733100B57339008C8C7B00A57B4200B5733100AD733100AD733100AD73
      3100AD733100AD733100FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600CECE
      CE00C6C6C6009C9C9C004A4A4A006B6B6B00CECECE00DEDEDE00BDBDBD00AD73
      3900AD6B2900AD6B3100AD6B3100AD6B2900AD6B3100AD6B39007B9C9C00A57B
      4A00AD6B3100AD6B3100AD6B3100AD6B3100AD6B2900AD733100C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600BDBD
      BD0084848400A5A5A500BDBDBD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00C6C6C600C6C6C600C6C6C600C6C6
      C600CECECE00CECECE00BDBDBD00636363005A5A5A004A4A4A00CECECE00EFEF
      EF00A5A5A50084848400B5B5B500AD733100AD6B2900AD632900AD733900A584
      5A00AD6B31009C735A0084ADB500A59C7B00AD7B4A00947352009C846300AD63
      2900A5632100A56B3100BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00D6DEDE00D6DEDE00ADA5AD00B5B5BD00C6BDB500BDBDC600D6CECE007B7B
      7B00C6C6C600B5BDB500B5B5B500A5ADA5009CADB500D6DEDE00D6D6D600FFFF
      FF00C6C6C600C6C6C600C6C6C600ADADAD004A4A4A00424242004A4A4A008C8C
      8C0094949400BDBDBD00ADA5AD0084848400BDBDBD00DEDEDE00CECECE00AD73
      3900A5632900AD632900AD632900849C9C009CADAD006BA5B50052BDDE006BB5
      CE006B9CAD007BB5BD00A57B5200A5632900A5632100A56B2900FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C6C6C600CECECE00737373004A4A
      4A00DEDEDE00B5B5B5008C8C8C00B5ADB5009C949C0084848400A5A5A500EFEF
      EF00EFEFEF00D6D6D600C6C6C600AD6B3100A5632900A5632100AD6331009484
      6B004AA5D60039BDE70039B5DE0042BDE70042B5E7007BADAD00A5734A00A563
      2900A5631800A5632100BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00C6C6C600CECECE004A4A4A00000000000000000031313100B5B5B500FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00BDBDBD00BDBDBD00BDBDBD0000000000FFFFFF0000000000000000000000
      0000CECECE00737373009C9C9C0000000000ADA5AD00B5BDB500B5B5B500B5B5
      B500C6C6C600DEDEDE00FFF7FF00E7E7E700D6D6D600BDBDBD00BDBDBD00AD6B
      3100A5633100A56B3100AD7B4200849C9C0052ADDE004AB5E7005AB5DE005AAD
      DE0042ADDE0052ADC6008C736300946331009C632900A56B2900BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00D6DEDE00D6DEDE00CEBDBD00CEC6
      BD00CEBDBD00CEC6BD00C6C6CE00848C9400D6C6CE00D6CEC600C6C6BD00BDBD
      BD00C6C6C600D6DEDE00CED6D600FFFFFF008C8C8C007B7B7B00CECECE009494
      9400D6D6D600FFF7FF0000000000FFF7FF00F7EFF700EFEFEF00D6CED600CECE
      CE009C9C9C005A525A0094949400AD7342008C846B00849C9C0094B5C6007BBD
      DE004AADDE0042A5D6005AB5DE0052ADDE0039ADDE0052BDDE006BA5C6006B94
      AD00848C7300A5733900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00C6C6C6008484840000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000084848400FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF007B7B7B005A5A5A00C6C6C600FFFFFF0000000000A5A5A50073737300B5B5
      B500EFE7EF00E7E7E700DED6DE00848484004242420073737300CECECE00AD63
      29009C5A18009C522100946339006B8C9C00429CD6004AA5DE005AB5E7004AC6
      E7004AC6DE006BB5CE008C7B6B009C5A2100945A10009C5A1800C6C6C600C6C6
      C600CECECE00CECECE00CECECE00CECECE005A5A5A0000000000000000002929
      290094949400BDBDBD00C6C6C600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00BDBDBD0000000000FFFFFF00FFFF
      FF00000000000000000000000000000000007B7B7B007B847B0000000000C6BD
      C6004A4A4A006B6B6B00737373006B6B6B00B5B5B500EFE7EF00E7E7E700524A
      52008C8C8C00D6D6D600C6C6C6009C5A18009C5208009C520800A55208009473
      4A0052BDDE0039ADE70039ADDE004AADDE004ABDEF006B7384009C522100944A
      0800944A00009C5A100000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007B7B7B006B6B6B00948C9400424242009C9C9C007B7B7B005A5A5A009C9C
      9C0073737300E7E7E700CECECE004A4A4A0094949400C6C6C600C6C6C6009C5A
      1000944A08009C520000945208008C948C00738C8C007BA5AD005AA5CE00638C
      B5007B9C9400739CA500845A3100944A0000944A080094521000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000ADADAD00636363007B7B7B00D6D6
      D6006B6B6B0084848400C6C6C6008C848C00ADADAD00DEDEDE008C848C004239
      4200CECECE00C6C6C600C6C6C6009C5A1000944A0000944A00009C5A1000945A
      290094520800A56B31007394A5007B5A4A00945218008C5218008C633100944A
      00008C4A00009452100000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000FFFF000000000000FFFF000000000000FFFF000000
      0000C6C6C600CECECE00D6DED6005A5A5A00948C9400BDB5BD00948C9400CECE
      CE00B5B5B5008C8C8C004A4A4A00B5B5B500C6C6C600C6C6C600C6C6C6009452
      1000944A0000944A0000944A0000944A0000944A00009C4A00006B8484007B52
      2100944200008C420000944200008C4A00008C42000094521000000000000000
      00000000000000FFFF000000000000FFFF000000000000FFFF000000000000FF
      FF000000000000FFFF000000000000FFFF000000000000FFFF00000000000000
      0000000000000000000000000000000000000000000000FFFF000000000000FF
      FF006321000000FFFF006321000000FFFF00C6C6C600C6C6C600D6D6D6004242
      4200101010005252520073737300635A6300393939004A4A4A00ADADAD00CECE
      CE00C6C6C600C6C6C600C6C6C600945208008C4200008C4200008C4200008C42
      00008C420000944A00007B7352008C5210008C4200008C4200008C4200008442
      0000844200008C4A08000000000000000000000000000000000000FFFF000000
      000000FFFF000000000000FFFF006321000000FFFF000000000000FFFF000000
      000000FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000FFFF000000000000FFFF0063210000632100006321
      0000C6C6C600C6C6C600C6C6C600A5A5A5008C8C8C0084848400848484008484
      8400B5B5B500D6D6D600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600945A
      2100844A1000844A1000844A1000844A1000844A1000844A10008C5A31008452
      1800844A1000844A1000844A1000844A1000844A10008C522100000000000000
      00000000000000FFFF000000000000FFFF000000000063210000000000006321
      000000000000632100000000000000FFFF000000000000FFFF00000000000000
      0000000000000000000000000000000000000000000000FFFF000000000000FF
      FF00632100006321000000FFFF0063210000C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600BDBDBD008484
      8400A5A5A500BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00000000000000000000000000BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00D6DEDE00D6DEDE00C6BDB500ADADAD00A5A59C009CA5AD00A5AD
      A5007B7B8400ADADBD00A5ADAD00A5A59C00A5A59C00ADADB500D6DEDE00CED6
      D600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00C6C6C600CECECE004A4A4A000000000021212100B5B5B500BDBDBD00BDBD
      BD00BDBDBD00BDBDBD0000000000BDBDBD00BDBDBD0000000000000000000000
      0000BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00D6DEDE00D6DEDE00ADA5
      AD00B5B5BD00C6BDB500BDBDC600D6CECE007B7B7B00C6C6C600B5BDB500B5B5
      B500A5ADA5009CADB500D6DEDE00D6D6D600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60084848400000000000000000084848400C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00C6C6C600CECECE004A4A4A00000000000000
      000031313100B5B5B500BDBDBD00BDBDBD00BDBDBD0000000000000000000000
      0000000000000000000000000000BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00C6D6DE00C6D6DE00ADADAD00B5ADAD00B5B5B500C6BDB500BDBD
      C6007B7B7B00B5BDB500BDBDC600BDBDC600ADB5C600B5ADB500D6DEDE00D6D6
      D600C6C6C6008484840000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000084848400C6C6
      C600BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00C6C6C600CECE
      CE005A5A5A0000000000000000003131310094949400C6C6C600BDBDBD00BDBD
      BD00000000000000000000000000000000000000000000000000BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00D6DEDE00D6DEDE00CEBD
      BD00CEC6BD00CEBDBD00CEC6BD00C6C6CE00848C9400D6C6CE00D6CEC600C6C6
      BD00BDBDBD00C6C6C600D6DEDE00CED6D600C6C6C60000000000848484008484
      8400000000000000000000000000000000000000000000000000000000000000
      0000848484008484840000000000C6C6C600BDBDBD00C6C6C600C6C6C600CECE
      CE00CECECE00CECECE00CECECE005A5A5A000000000000000000292929009494
      9400BDBDBD00C6C6C600BDBDBD00000000000000000000000000000000000000
      00000000000000000000BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00D6DEDE00D6DEDE007B7363008CADBD008CA5BD008CA5BD00848C
      8C005A5A5200738C9400949CA500949CA50084A5A5005A5A5200DEE7E700CED6
      D600C6C6C6000000000084848400848484000000000000000000000000000000
      000000000000000000000000000000000000848484008484840000000000C6C6
      C600C6C6C600BDBDBD008484840031313100313131004A4A4A009C9C9C001010
      100000000000292929008C8C8C00BDBDBD00C6C6C600C6C6C600BDBDBD00BDBD
      BD0000000000000000000000000000000000000000000000000000000000BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00D6DEDE00D6DEDE008C8C
      840010000000100810001000000031292900847B730029100800100800000800
      000008000000637B7B00E7E7E700CED6D600C6C6C60000000000848484008484
      8400000000000000000000000000000000000000000000000000000000000000
      0000848484008484840000000000C6C6C600B5B5B500424242005A5A5A00A5A5
      A500A5A5A5009C9C9C004242420010101000424242008C8C8C00BDBDBD00C6C6
      C600BDBDBD00C6C6C600BDBDBD00BDBDBD000000000000000000000000000000
      000000000000000000000000000000000000BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00D6DEDE00D6DED600B5B5C6009C848C0084736B00B5A5A5007B6B
      6B00848473005A525200635A4A008C7B7B00947B73008C8C8C00E7E7E700CED6
      D600C6C6C6000000000084848400848484000000000000000000000000000000
      000000000000000000008484840000000000848484008484840000000000CECE
      CE008C8C8C006B6B6B00DEDECE00ADAD8C00ADAD9400A5A5A500A5A5A5004A4A
      4A0084848400B5B5B500C6C6C600BDBDBD00BDBDBD00C6C6C600BDBDBD000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000BDBDBD00BDBDBD00BDBDBD00BDBDBD00C6D6DE00C6D6DE00848C
      9400101000001810080018100000293139008C8C840021101000181000001810
      080010080000638C9C00E7E7E700D6D6D600C6C6C60000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C6C6C60052525200DEDEE700F7F7CE00CECE
      8400BDBD7B009C9CA500ADADAD0073737300424242009C9C9C00C6C6C600BDBD
      BD00BDBDBD00C6C6C600BDBDBD00000000000000000000000000BDBDBD000000
      0000000000000000000000000000000000000000000000000000BDBDBD00BDBD
      BD00BDBDBD00D6DEDE00D6DEDE00948C84002118180029211800292110002129
      29008C8C940031212100291810001818180018100800738C9C00D6DEE700C6CE
      D600C6C6C6000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C6C6
      C6004A4A5200E7E79C00F7F7A500EFEFA500CECE8C00C6C67300ADADA5006B6B
      7300424242009C9C9C00C6C6C600BDBDBD00BDBDBD00C6C6C600BDBDBD00BDBD
      BD00BDBDBD000000000000000000BDBDBD000000000000000000000000000000
      0000000000000000000000000000BDBDBD00BDBDBD00C6D6DE00C6D6DE00BDAD
      AD00292110002921210018212100315A6B008C9CAD0042393100181821003129
      180018211800C6C6D600CEDEE700C6CED600C6C6C60000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C6C6C6007B7B8400EFEFA500F7F7DE00F7F7
      F700E7E79C00CECE8400ADADA50073737300424242009C9C9C00C6C6C600BDBD
      BD00BDBDBD00C6C6C600BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD000000000000000000000000000000000000000000000000000000
      0000BDBDBD00D6DEDE00D6DEDE008C949400948C9C00849C9C0094A5AD008494
      9C00737B8C0084849400849494007B9494007B8C8C00ADB5BD00DEDEDE00D6D6
      D600C6C6C600C6C6C6000000000000000000C6C6C60084848400000000000000
      0000000000000000000084848400C6C6C6000000000000000000C6C6C600CECE
      CE009C9C9C0094948400FFFFE700EFEFBD00EFEFB500F7F7DE00BDBDBD003939
      39007B7B7B00BDBDBD00C6C6C600BDBDBD00BDBDBD00C6C6C600BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00000000000000
      0000000000000000000000000000BDBDBD00BDBDBD00D6DEDE00D6DEDE00ADAD
      BD00A5A5AD00BDC6CE00ADADB50073736B006B736B00949CA500CECECE00B5C6
      CE00848C8C009C9CAD00DEDEDE00CED6D600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60084848400000000000000000084848400C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600BDBDBD0094949C0094947300EFEF
      AD00EFEFB50094949C00313131004A4A4A009C9C9C00C6C6C600C6C6C600BDBD
      BD00BDBDBD00C6C6C600BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00000000000000000000000000BDBDBD00BDBD
      BD00BDBDBD00D6DEDE00D6DEDE00A5ADBD00ADADAD00B5BDC600A5ADBD00A5AD
      BD0073738400ADB5BD0094A5B500A5A5B50094A5BD0094ADAD00CED6DE00C6CE
      D600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600BDBDBD00ADADB5005A5A6300393942004242420084848400BDBD
      BD00C6C6C600C6C6C600BDBDBD00BDBDBD00BDBDBD00C6C6C600BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD0000000000BDBDBD00BDBDBD00BDBDBD00BDBDBD00C6D6DE00C6D6DE00A5AD
      9C00B5AD8C00A5A59C00B5AD8C00B5AD940073735200B5AD8C00B5A57B00B5AD
      A500B5A57300A5A59400DEDEDE00CED6D600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600CECE
      CE00CECECE00CECECE00C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00C6D6DE00C6CED600ADB5C600B5B5C600B5B5C600A5B5C600A5AD
      C6009C9C9C0094ADB500B5BDCE0094A5B5008CADB50094A5B500CED6DE00C6CE
      D600424D3E000000000000003E000000280000003C0000002D00000001000100
      00000000680100000000000000000000000000000000000000000000FFFFFF00
      000000000000000018C600001084108042004C9C1CE79AD05184841083008300
      8200830883008530D7BD98DE98DE50900000D7BDD7BDD7B00000000000000000
      0000000000000000D7BD18C6D7BD0000108496B518C6D7B0559514A514A54940
      518C4D6BDBCE558010841084000059C000000000108400000000000000000000
      000000001084108000000000DAE658D000000001C510C3100000000105114420
      00000002DADE528010000000D7BDD7B0020000000000000008000000D7BD0000
      20000002D7BD00000000000018C6D7B00000000055AD8E70000000029ECF5980
      00000000000018C0000000000000000000000000000000000000000000000000
      0000000020000000000000006000000003C00000C000000007E000000C000000
      07E000001E00000007C000001F00000033CC0000CF800000381C000047C00000
      0000000003C00000018000000180000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000}
  end
  object Timer1: TTimer
    Interval = 50
    OnTimer = Timer1Timer
    Left = 574
    Top = 43
  end
  object Timer2: TTimer
    Interval = 60000
    OnTimer = Timer2Timer
    Left = 581
    Top = 395
  end
  object ServerSocket1: TServerSocket
    Active = True
    Port = 10005
    ServerType = stNonBlocking
    OnAccept = ServerSocket1Accept
    OnClientDisconnect = ServerSocket1ClientDisconnect
    OnClientRead = ServerSocket1ClientRead
    OnClientError = ServerSocket1ClientError
    Left = 417
    Top = 169
  end
  object Timer3: TTimer
    Interval = 3000
    OnTimer = Timer3Timer
    Left = 581
    Top = 282
  end
  object Timer4: TTimer
    Interval = 100
    OnTimer = Timer4Timer
    Left = 580
    Top = 125
  end
  object Timer5: TTimer
    Interval = 5000
    OnTimer = Timer5Timer
    Left = 581
    Top = 337
  end
  object Timer6: TTimer
    OnTimer = Timer6Timer
    Left = 576
    Top = 232
  end
  object Weather1: TWeather
    AutoConnect = True
    ConnectKind = ckRunningOrNew
    Left = 352
    Top = 480
  end
  object Skysensor1: TSkysensor
    AutoConnect = False
    ConnectKind = ckRunningOrNew
    Left = 272
    Top = 464
  end
end
