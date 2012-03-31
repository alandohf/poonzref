' VBScript.
Set Shell = CreateObject("WScript.Shell")
ProgPath = "C:\poon\poonzref\dev\gcc\release"
DesktopPath = Shell.SpecialFolders("Desktop")
Set link = Shell.CreateShortcut(DesktopPath & "\alert.lnk")
link.Arguments = ""
link.Description = "test shortcut"
link.HotKey = "CTRL+ALT+SHIFT+X"
link.IconLocation = "app.exe,1"
link.TargetPath = ProgPath & "\alert.exe"
link.WindowStyle = 3
link.WorkingDirectory = DesktopPath
link.Save
