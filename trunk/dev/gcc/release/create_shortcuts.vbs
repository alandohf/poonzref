' VBScript.
Set Shell = CreateObject("WScript.Shell")
ProgPath = "C:\poon\poonzref\dev\gcc\release"
DesktopPath = Shell.SpecialFolders("Desktop")
Set link = Shell.CreateShortcut(DesktopPath & "\bg.lnk")
link.Arguments = ""
link.Description = "bg.vbs shortcut"
link.HotKey = "CTRL+ALT+SHIFT+X"
link.IconLocation = "bg.vbs,1"
link.TargetPath = ProgPath & "\bg.vbs"
link.WindowStyle = 3
link.WorkingDirectory = ProgPath
link.Save
