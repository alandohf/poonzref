/*-----------------------------------------------------
   SCRNSIZE.C -- Displays screen size in a message box
                 (c) Charles Petzold, 1998
  -----------------------------------------------------*/

#include <windows.h>
#include <tchar.h>     
#include <stdio.h>     
#include "poonapi.h"
/*-----------------------------------------------------
   use messagebox like printf !
  -----------------------------------------------------*/
int CDECL MessageBoxPrintf (TCHAR * szCaption, TCHAR * szFormat, ...)
{
     TCHAR   szBuffer [1024] ;
     va_list pArgList ;

          // The va_start macro (defined in STDARG.H) is usually equivalent to:
          // pArgList = (char *) &szFormat + sizeof (szFormat) ;

     va_start (pArgList, szFormat) ;

          // The last argument to wvsprintf points to the arguments

     _vsntprintf (szBuffer, sizeof (szBuffer) / sizeof (TCHAR), 
                  szFormat, pArgList) ;
	// The va_end macro just zeroes out pArgList for no good reason
     va_end (pArgList) ;

     return MessageBox (NULL, szBuffer, szCaption, 0) ;
}


/*-----------------------------------------------------
   exit program with a message! 
  -----------------------------------------------------*/

void exitm(char a[] ){
printf("%s\n",a);
	exit(0);
}




/*-----------------------------------------------------
  win32 c  : GetLastError 的封装！
  -----------------------------------------------------*/

void ShowError()
{
    TCHAR* lpMsgBuf;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER| //自动分配消息缓冲区
    FORMAT_MESSAGE_FROM_SYSTEM, //从系统获取信息
    NULL,GetLastError(), //获取错误信息标识
    MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),//使用系统缺省语言
    (LPTSTR)&lpMsgBuf, //消息缓冲区
    0,
    NULL);
    MessageBox(NULL,lpMsgBuf,"",MB_ICONERROR);
}


void ShowDBError(HWND hwnd,SQLSMALLINT type,SQLHANDLE sqlHandle)
{
    SQLCHAR pStatus[100]={0}, pMsg[1000]={0};
    SQLSMALLINT SQLMsglen;
    char error[2000] = {0};
    SQLINTEGER SQLerr;
    long erg2 = SQLGetDiagRec(
                              type
                              , sqlHandle
                              ,1
                              ,(SQLCHAR *)pStatus
                              ,&SQLerr
                              ,(SQLCHAR *)pMsg
                              ,1000
                              ,&SQLMsglen
                );
    wsprintf(error,"ERROR  MSG:%s \nSQL   CODE: %ld\nGetDiagRec:%ld\n",pMsg,(long)SQLerr,erg2);
    MessageBox(hwnd,error,TEXT("error"),MB_OK);
}


void ShowDBConnError(HWND hwnd,SQLHDBC hdbc)
{
	ShowDBError(hwnd,SQL_HANDLE_DBC,hdbc);
}


void ShowDBStmtError(HWND hwnd,SQLHSTMT hstmt)
{
	ShowDBError(hwnd,SQL_HANDLE_STMT,hstmt);
}

/************************************
* To write a string into a log file *
* with current date and time        *
************************************/
int myWriteToLog(TCHAR* s) {
	long nTime;
	struct tm *tmDateTime;
	TCHAR sDateTime[6][16];
	FILE *f;
	
	if (NULL == s) return(0);
	time(&nTime);
	tmDateTime = (struct tm*) localtime(&nTime);
	f = _tfopen(sLogFileName, _T("a+"));
	if (!f) return(0);
	
	_tcsftime(sDateTime[0], 16, _T("%B"), tmDateTime);
	_tcsftime(sDateTime[1], 16, _T("%d"), tmDateTime);
	_tcsftime(sDateTime[2], 16, _T("%Y"), tmDateTime);
	_tcsftime(sDateTime[3], 16, _T("%H"), tmDateTime);
	_tcsftime(sDateTime[4], 16, _T("%M"), tmDateTime);
	_tcsftime(sDateTime[5], 16, _T("%S"), tmDateTime);
	
	// Write string to log file with current date & time info:
	_ftprintf(f, _T("%s (%s %s, %s @ %s:%s:%s)\n"), s, sDateTime[0], sDateTime[1], sDateTime[2], sDateTime[3], sDateTime[4], sDateTime[5]);
	
	if (f) fclose(f);
	return(1);
}




//~ http://stackoverflow.com/questions/5869489/how-to-set-button-backcolor
//~ HBRUSH CYourDialogClass::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//~ {
    //~ HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    //~ if (pWnd->GetDlgCtrlID() == IDC_OF_YOUR_BUTTON)
    //~ {
        //~ pDC->SetBkColor (RGB(0, 0, 255)); // BLUE color for background
        //~ pDC->SetTextColor (RGB(255, 0, 0)); // RED color for text
    //~ }

    //~ return hbr;
//~ }