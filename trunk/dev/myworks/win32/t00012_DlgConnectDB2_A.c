
/****************************************************************************
  *  program name  : 基于对话框的应用程序_db2_connect
  *  author		   : panzhiwei
  *  date		   : 2012-03-27
  *  function desc : 使用SQLConnect函数来连接db2数据库(非SQLDriverConnect)，使用了ODBC!
  *  compiler      : vc6 enterprise
  *  todo		   : 1.
					 2.
					 3.
  *  notes		   : 1.注意对不同HANDLE 的 SQLGetDiagRec参数的使用!
  *  				 2.
  *  				 3.
  *  revision log  : 1.
					 2.
					 3.
  *  reference	   : 1.
					 2.
					 3.
*****************************************************************************/

#include <windows.h>
#include "resource.h"

#include <sqlext.h>
#include <tchar.h>     // for _vsntprintf

#define CHECKDBSTMTERROR(hwnd,result,hstmt) if(SQL_ERROR==result){ShowDBStmtError(hwnd,hstmt);return 0;}
int CDECL MessageBoxPrintf (TCHAR * szCaption, TCHAR * szFormat, ...);
void HandleDiagnosticRecord (SQLHANDLE      hHandle,
                             SQLSMALLINT    hType,
                             RETCODE        RetCode);

void ShowDBError(HWND hwnd,SQLSMALLINT type,SQLHANDLE sqlHandle);
void ShowDBConnError(HWND hwnd,SQLHDBC hdbc);
void ShowDBStmtError(HWND hwnd,SQLHSTMT hstmt);

void ShowError();
LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
int APIENTRY  WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
//		InitCommonControls();
 	DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)DlgProc);
	return 0;
}

LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   SQLHENV henv;
   SQLHDBC hdbc;
   SQLHSTMT hstmt;
   SQLRETURN retcode;
   SQLCHAR server[32] = "db2";
   //~ SQLCHAR * OutConnStr = (SQLCHAR * )malloc(255);
   //~ SQLSMALLINT * OutConnStrLen = (SQLSMALLINT *)malloc(255);

	switch (uMsg)
	{

	case WM_INITDIALOG:// WM_INITDIALOG message is sent before dialog is displayed
		{
			return TRUE;
		}
		break;
	case WM_COMMAND://
		{
			switch(wParam)
			{
				case IDC_BUTTON1:
				{
				   // Allocate environment handle
				   retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
				   // Set the ODBC version environment attribute
				   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
					  retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

					  // Allocate connection handle
					  if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
						 retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
						 // Set login timeout to 5 seconds
						 if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
							SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
							//HandleDiagnosticRecord(hdbc,SQL_HANDLE_DBC,retcode);
							// Connect to data source
							retcode = SQLConnect(
								hdbc
								, (SQLCHAR*) server
								, SQL_NTS
								, (SQLCHAR*) NULL
								, 0
								, NULL
								, 0);

							// Allocate statement handle
							if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
							   retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
							   // Process data
								//~ retcode = SQLPrepare(hstmt,(SQLCHAR*)"drop table poon.test",SQL_NTS);
								retcode = SQLPrepare(hstmt,(SQLCHAR*)"select xx from syscat.tables",SQL_NTS);
								CHECKDBSTMTERROR(hwndDlg,retcode,hstmt);
								retcode =SQLExecute(hstmt);
								CHECKDBSTMTERROR(hwndDlg,retcode,hstmt);

							   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
								  SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
							   }
							   else{
								  ShowDBStmtError(hwndDlg,hstmt);
							   }

							   SQLDisconnect(hdbc);
							}
							else{
								 ShowDBConnError(hwndDlg,hdbc);
							}

							SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
						 }
					  }
					  SQLFreeHandle(SQL_HANDLE_ENV, henv);
				   }

				}
				default:
					break;
			}
			return TRUE;
		}
		break;
	case WM_CTLCOLORDLG: //set its text and background colors using the specified display device context handle.
		{
		}
		break;
	case WM_PAINT:
		{

		}
		break;
	case WM_CTLCOLORSTATIC: //可以控制静态控件的颜色
		{

		}
		break;
	case WM_CLOSE://Massage for terminate/exit (may close button clicked on title bar)
		{
			//Close dialog
		EndDialog(hwndDlg,0);
			break;
		}


	}
	return FALSE;
}




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
    SQLSMALLINT SQLmsglen;
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
                              ,&SQLmsglen
                );
    wsprintf(error,"ERROR DESC:%s \nSQLCODE: %ld\n SQLGetDiagRec RETURN:%ld\n",pMsg,(long)SQLerr,erg2);
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


