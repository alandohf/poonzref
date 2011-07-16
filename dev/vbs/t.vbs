Function Wmp_StatusChange  
    If Wmp.playState = 8 Then   
        WScript.Quit
    End If
End Function

Set Wmp=WScript.CreateObject("WMPlayer.OCX", "Wmp_")
Wmp.Settings.autoStart = True
Wmp.Settings.Volume = "30"
Wmp.Settings.setMode "shuffle", True
Wmp.Url = "e:\bass1\bass1_daily_alert.mp3"

While True
    WScript.Sleep 10   
Wend