Dim szBuf
For Each Arg In WScript.Arguments
        szBuf = szBuf  & Arg & "	"
Next
MsgBox szBuf, vbInformation, "�ƻ�������ʾ"
