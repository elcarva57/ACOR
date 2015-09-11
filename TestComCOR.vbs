
Option explicit
Dim COR
Dim Foco
Dim nfoto
Dim CCD1

Set COR = CreateObject("RocPcServidor.cRocPcServidor")
Set Foco = CreateObject("RocPcServidor.Focuser")
Set CCD1 = CreateObject("RocPcServidor.CCD1")

 If COR.EstadoCor = 0 Then
	 	MsgBox " COR desconectado " &  Now()
 Else

    If CCD1.DisableAutoShutdown = True  Then
      MsgBox " DisableAutoShutdown SI"
    Else
	 	  MsgBox " DisableAutoShutdown NO"
	 	End If  

    CCD1.DisableAutoShutdown = True

	 	MsgBox " COR Conectado " &  Now()

    If CCD1.DisableAutoShutdown = True  Then
      MsgBox " DisableAutoShutdown SI"
    Else
	 	  MsgBox " DisableAutoShutdown NO"
	 	End If  


  	MsgBox "  Temp: " & COR.Tambiente & " RA " & COR.Ra
'  	MsgBox COR.MensEMAv2
  	
  	MsgBox "  Position: " & Foco.Position & "  Absoluto" & Foco.Absolute
  	Foco.Move 40
  	MsgBox "  Position2: " & Foco.Position 
  	MsgBox "  Moving " & Foco.IsMoving
  	Foco.Halt
  	
  	COR.Slewd 12.5, 23.6

 '     CCD1.Foto "2 0004 2 001 3 hola"  'Binin Exposg Tipo Numero Filtro Nombre

  	CCD1.Nombre "prueba"
  	CCD1.NumFotos 3
  	CCD1.TipoFoto 1
    CCD1.Binin 3
    CCD1.Exposicion 4
    CCD1.Foto
    
    EsperaFinSerie()
    
 
 End If
 
 
 Sub EsperaFinSerie()
   Do While CCD1.FotoActual < 3
   Loop   
   Do While CCD1.FotoActual > 1
   Loop   
   MsgBox "Fin serie de " & CCD1.FotoActual & " fotos."
 End Sub

