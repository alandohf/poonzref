Dim szBuf
For Each Arg In WScript.Arguments
        szBuf = szBuf  & Arg & "	"
Next
MsgBox szBuf, vbInformation, "计划任务提示"
