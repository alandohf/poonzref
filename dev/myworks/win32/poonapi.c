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
  win32 c  : GetLastError �ķ�װ��
  -----------------------------------------------------*/

void ShowError()
{
    TCHAR* lpMsgBuf;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER| //�Զ�������Ϣ������
    FORMAT_MESSAGE_FROM_SYSTEM, //��ϵͳ��ȡ��Ϣ
    NULL,GetLastError(), //��ȡ������Ϣ��ʶ
    MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),//ʹ��ϵͳȱʡ����
    (LPTSTR)&lpMsgBuf, //��Ϣ������
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