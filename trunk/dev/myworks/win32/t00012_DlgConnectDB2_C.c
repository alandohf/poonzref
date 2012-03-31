
/****************************************************************************
  *  program name  : 基于对话框的应用程序_db2_connect
  *  author		   : panzhiwei
  *  date		   : 2012-03-27
  *  function desc : 使用SQLDriverConnect函数来连接db2数据库(非SQLConnect),通过TCPIP!
  *  compiler      : vc6 enterprise
  *  todo		   : 1.
					 2.
					 3.
  *  notes		   : 1.注意对不同HANDLE 的 SQLGetDiagRec参数的使用!
  *  				 2.使用本例中字串来连接数据库的时候，在安装DB2时要设置好TCPIP的支持。最好把命名管道、DB2C_DB2服务名也设置了。
  *  				 3.<sql.h> 的使用
  *  revision log  : 1.成功连接DB2 EXP-C 数据库。关键点是数据库正确安装！并支持TCPIP访问功能！
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
#include <sqltypes.h>
#include <sql.h>
#define LOGIN_TIMEOUT 30
#define MAXBUFLEN 255
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
				case IDC_BTN_RECV:
				{
					SQLHENV henv = NULL;
					SQLHDBC hdbc = NULL;
					SQLHSTMT hstmt = NULL;
					SQLRETURN result;
					//~ SQLCHAR ConnStrIn[MAXBUFLEN] = "DRIVER={MySQL ODBC 5.1 Driver};SERVER=127.0.0.1;UID=root;PWD=root;DATABASE=test;CharSet=gbk;";
					//~ SQLCHAR ConnStrIn[MAXBUFLEN]=
					//~ "driver={IBM DB2 ODBC DRIVER};Database=BASSDB;hostname=172.16.9.27;port=50000;protocol=TCPIP;uid=bass2; pwd=bass2";//ok
					SQLCHAR ConnStrIn[MAXBUFLEN]=
					"driver={IBM DB2 ODBC DRIVER};Database=SAMPLE;hostname=localhost;port=50000;protocol=TCPIP;uid=poon; pwd=pzw@@Inn";
					//~ SQLCHAR ConnStrIn[MAXBUFLEN]="Dsn=db2;Uid=;Pwd=";
					SQLCHAR ConnStrOut[MAXBUFLEN];
					//分配环境句柄
					result = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
					//设置管理环境属性
					result = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
					//分配连接句柄
					result = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
					//设置连接属性
					result = SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (void*)LOGIN_TIMEOUT, 0);
					//连接数据库
					result = SQLDriverConnect(
												hdbc
												,NULL
												,ConnStrIn
												,SQL_NTS
												,ConnStrOut
												,MAXBUFLEN
												,(SQLSMALLINT *)0
												,SQL_DRIVER_NOPROMPT
												);
					if(SQL_ERROR==result)
					{
						ShowDBConnError(hwndDlg,hdbc);
					return FALSE;
					}
					//初始化语句句柄
					result = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
					//SQL_NTS telling the function the previous parameter is Null-Terminated String, 
					//please alculate the string length for me   
					result = SQLPrepare(hstmt,(SQLCHAR*)"select abc from syscat.t",SQL_NTS);
					CHECKDBSTMTERROR(hwndDlg,result,hstmt);
					result =SQLExecute(hstmt);
					CHECKDBSTMTERROR(hwndDlg,result,hstmt);
					SQLFreeStmt(hstmt,SQL_CLOSE);
					SQLDisconnect(hdbc);
					SQLFreeHandle(SQL_HANDLE_DBC,hdbc);
					SQLFreeHandle(SQL_HANDLE_ENV,henv);
					MessageBox(hwndDlg,TEXT("excute sussessfully"),TEXT("Prompt"),MB_OK);
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

