object Historico: THistorico
  Left = 757
  Top = 194
  Width = 717
  Height = 405
  Caption = 'Mensajes'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
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
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object Mhistory: TMemo
    Left = 0
    Top = 0
    Width = 701
    Height = 337
    Align = alClient
    Color = cl3DLight
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      'Log')
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 337
    Width = 701
    Height = 33
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      701
      33)
    object BClearHistory: TButton
      Left = 587
      Top = 6
      Width = 89
      Height = 20
      Anchors = [akTop, akRight, akBottom]
      Caption = 'Borrar Historia'
      TabOrder = 0
      OnClick = BClearHistoryClick
    end
    object bGrabarHistoria: TButton
      Left = 27
      Top = 6
      Width = 89
      Height = 20
      Anchors = [akTop, akRight, akBottom]
      Caption = 'Grabar Historia'
      TabOrder = 1
      OnClick = bGrabarHistoriaClick
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.txt'
    FileName = 'Historia'
    Filter = 'Test file (*,txt)|*.txt'
    Left = 136
    Top = 336
  end
end
