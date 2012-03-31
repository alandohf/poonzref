
/****************************************************************************
  *  program name  : ���ڶԻ����Ӧ�ó���_db2_connect
  *  author		   : panzhiwei
  *  date		   : 2012-03-27
  *  function desc : ʹ��SQLDriverConnect����������db2���ݿ�(��SQLConnect),ͨ��TCPIP!
  *  compiler      : vc6 enterprise
  *  todo		   : 1.
					 2.
					 3.
  *  notes		   : 1.ע��Բ�ͬHANDLE �� SQLGetDiagRec������ʹ��!
  *  				 2.ʹ�ñ������ִ����������ݿ��ʱ���ڰ�װDB2ʱҪ���ú�TCPIP��֧�֡���ð������ܵ���DB2C_DB2������Ҳ�����ˡ�
  *  				 3.<sql.h> ��ʹ��
  *  revision log  : 1.�ɹ�����DB2 EXP-C ���ݿ⡣�ؼ��������ݿ���ȷ��װ����֧��TCPIP���ʹ��ܣ�
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
					//���价�����
					result = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
					//���ù���������
					result = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
					//�������Ӿ��
					result = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
					//������������
					result = SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (void*)LOGIN_TIMEOUT, 0);
					//�������ݿ�
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
					//��ʼ�������
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
	case WM_CTLCOLORSTATIC: //���Կ��ƾ�̬�ؼ�����ɫ
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

