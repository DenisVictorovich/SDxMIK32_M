object Form2: TForm2
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'SDxMIK32   TST'
  ClientHeight = 643
  ClientWidth = 1007
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Fixedsys'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 1007
    Height = 57
    Align = alTop
    Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' COM-'#1087#1086#1088#1090#1072
    TabOrder = 0
    object port_label: TStaticText
      Left = 8
      Top = 25
      Width = 68
      Height = 20
      AutoSize = False
      Caption = #1055#1086#1088#1090
      TabOrder = 0
    end
  end
  object Memo1: TMemo
    Left = 0
    Top = 82
    Width = 1007
    Height = 561
    Align = alClient
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object Button1: TButton
    Left = 0
    Top = 57
    Width = 1007
    Height = 25
    Align = alTop
    Caption = #1055#1056#1054#1048#1047#1042#1045#1057#1058#1048' '#1048#1057#1055#1067#1058#1040#1053#1048#1045
    TabOrder = 2
    OnClick = Button1Click
  end
end
