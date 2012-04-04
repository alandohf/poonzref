
/****************************************************************************
  *  program name  : 基于对话框的应用程序_db2_connect
  *  author		   : panzhiwei
  *  date		   : 2012-03-27
  *  function desc : 使用SQLDriverConnect函数来连接db2数据库(非SQLConnect),通过TCPIP!
  *  compiler      : vc6 enterprise
  *  todo		   : 1.ctrl+a 实现全选
					 2.
					 3.
  *  notes		   : 1.注意对不同HANDLE 的 SQLGetDiagRec参数的使用!
  *  notes		   : 2.hostname can be 127.0.0.1 ; ip ; host name : poon-pc ; localhost
  *  notes		   : 3.只要添加 WS_HSCROLL|WS_VSCROLL 就能上下左右滚动！
  *  				 2.使用本例中字串来连接数据库的时候，在安装DB2时要设置好TCPIP的支持。最好把命名管道、DB2C_DB2服务名也设置了。
  *  				 3.<sql.h> 的使用
  *  revision log  : 1.成功连接DB2 EXP-C 数据库。关键点是数据库正确安装！并支持TCPIP访问功能！
					 2.
					 3.
  *  reference	   : 1.http://social.msdn.microsoft.com/Forums/nb-NO/vcgeneral/thread/62b20011-829c-4d18-9332-f640c552b5e4
					 2.http://www.codeproject.com/Articles/227831/A-dialog-based-Win32-C-program
					 3.http://cboard.cprogramming.com/windows-programming/20424-api-func-select-text-edit-control.html
					 4.http://msdn.microsoft.com/en-us/library/windows/desktop/bb849143(v=vs.85).aspx
					 
*****************************************************************************/

#include <windows.h>
#include <Windowsx.h> //Core header file for win32 based Applictions

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

HANDLE hinstAcc;    // handle to application instance 

LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
int APIENTRY  WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	HWND hDlg;	
	BOOL ret;
	MSG Msg;
	
	HACCEL hAccel;      // handle to accelerator table 
	hinstAcc = GetModuleHandle(NULL);	
    hAccel = LoadAccelerators(hinstAcc, MAKEINTRESOURCE(IDR_ACCELERATOR1)); 
    if (hAccel == NULL) 
       MessageBoxPrintf("error","error loading Accelerators"); //HandleAccelErr(ERR_LOADING);     // application defined 
	
 	//~ DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)DlgProc);
	
 //~ ACCEL dlgacc[] =
 //~ { 
  //~ {FVIRTKEY,     VK_F1,       IDHELP},
        //~ };
 //~ hAccel = CreateAcceleratorTable(dlgacc,sizeof(dlgacc)/sizeof(dlgacc[0]));
//~ SendDlgItemMessage 

	hDlg = CreateDialogParam(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),0,(DLGPROC)DlgProc,(LPARAM)0);
ShowWindow(hDlg, nCmdShow);
	
while((ret = GetMessage(&Msg, 0, 0, 0)) != 0) 
 {
		if(ret == -1) /* error found */
			return -1;

		if (TranslateAccelerator(hDlg, hAccel,&Msg))
			continue;
		if(!IsDialogMessage(hDlg, &Msg))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
 }	
	return 0;
}

LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   static SQLHENV henv;
   static SQLHDBC hdbc;
   static SQLHSTMT hstmt;
   static int ifconnect=0;
   static SQLCHAR server[32];
   static char Content[10240] ;
char Content2[10240] ;
	SQLCHAR sqlstr[1024];	
   SQLRETURN retcode;
   //~ SQLCHAR server[32] = "db2";
   //~ SQLCHAR * OutConnStr = (SQLCHAR * )malloc(255);
   //~ SQLSMALLINT * OutConnStrLen = (SQLSMALLINT *)malloc(255);

	SQLHENV env;
	char dsn[256];
	char desc[256];
	SQLSMALLINT dsn_ret;
	SQLSMALLINT desc_ret;
	SQLUSMALLINT direction;
	SQLRETURN ret;
	HWND hEditTN = GetDlgItem(hwndDlg, IDC_EDIT1);
	HWND hEdit = GetDlgItem(hwndDlg, IDC_EDIT2);
	HWND hCBox = GetDlgItem(hwndDlg,IDC_COMBO1);
	int curSel;
	char szTable[256]; // receives name of item to delete. 
	
	switch (uMsg)
	{

	case WM_INITDIALOG:// WM_INITDIALOG message is sent before dialog is displayed
		{
		   // Allocate environment handle
		   retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
		   // Set the ODBC version environment attribute
		   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			  retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
		   }
		   else {
					MessageBoxPrintf("Prompt","fail to SQLAllocHandle SQL_HANDLE_ENV\n");
					return FALSE;
			}
			
		  direction = SQL_FETCH_FIRST;
		  while(SQL_SUCCEEDED(ret = SQLDataSources(henv, direction,
							   dsn, sizeof(dsn), &dsn_ret,
							   desc, sizeof(desc), &desc_ret))) 
		  {
			direction = SQL_FETCH_NEXT;
			//MessageBoxPrintf("DSN","%s\n",dsn);
			ComboBox_InsertString(hCBox,0,dsn);								   
			if (ret == SQL_SUCCESS_WITH_INFO) printf("\tdata truncation\n");
		  }
			
			return TRUE;
		}
		break;
	case WM_COMMAND://
		{
			switch (LOWORD(wParam)) 
            { 
                // Process the accelerator and menu commands. 
 
                case ID_ACCELERATOR1: 
				//~ MessageBoxPrintf("hi","hello");
				//~ GetModuleHandle()
				SendMessage(hEdit, EM_SETSEL,(WPARAM)0,(LPARAM) sizeof(Content)/sizeof(char));
			return TRUE;
			}
			
			switch(wParam)
			{
				case IDC_BUTTON1:
				{
					//disconnect
					if (ifconnect) {
						retcode = SQLDisconnect(hdbc);	
					   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
							SetWindowText(GetDlgItem(hwndDlg, IDC_BUTTON1), (LPCTSTR )"Connect");				   
							//~ MessageBoxPrintf("Prompt","Disconnected from %s!\n",server);
							ifconnect = 0;
							return 0;
					   }
					   //~ else
					   //~ {
							//~ MessageBoxPrintf("Prompt","Not Connect yet!\n");						
						//~ }
					}

					  // Allocate connection handle
						 retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
					  if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
							 // Set login timeout to 5 seconds					  
							SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);	
					  }
					  else{
							SQLFreeHandle(SQL_HANDLE_DBC, hdbc);  
							SQLFreeHandle(SQL_HANDLE_ENV, henv);								
							return FALSE;					  
					  }

					// Connect to data source
						if(!ComboBox_GetTextLength(hCBox)){
							MessageBoxPrintf("ERROR","Please Select an Item!");
							return FALSE;
						}
						curSel=ComboBox_GetCurSel(hCBox);
						ComboBox_GetLBText(hCBox,curSel,server);
						retcode = SQLConnect(
						hdbc
						, (SQLCHAR*) server
						, SQL_NTS
						, (SQLCHAR*) NULL
						, 0
						, NULL
						, 0);
					  
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
						ifconnect=1;
						SetWindowText(GetDlgItem(hwndDlg, IDC_BUTTON1), (LPCTSTR )"Connected");
						//~ MessageBoxPrintf("Prompt","Connected to %s!\n" ,server);							
					}
					else {
						MessageBoxPrintf("Prompt","Fail to Connect to %s!\n",server);	
						ShowDBStmtError(hwndDlg,hdbc);								
					}
				}
				break;
				
				case IDC_BUTTON3:
				{
					//~ MessageBoxPrintf("INFO","length:%d\n",Edit_GetTextLength(hEdit));
					if(!Edit_GetTextLength(hEditTN)){
						MessageBoxPrintf("Error","[SKM.]TABNAME");
						return FALSE;
					}
					
					ZeroMemory(Content,sizeof(Content)/sizeof(char));
					SetDlgItemText(hwndDlg,IDC_EDIT2,Content);										
					if (!ifconnect) {
						MessageBoxPrintf("Prompt","Not Connect yet!\n");						
						return 0;
					}
					//初始化语句句柄
					retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
					//SQL_NTS telling the function the previous parameter is Null-Terminated String, 
					//please alculate the string length for me
                    if (!GetDlgItemText(hwndDlg, IDC_EDIT1, szTable, sizeof(szTable)/sizeof(SQLCHAR))) 
					{
						*szTable=0;
						MessageBoxPrintf("","%s\n",sqlstr);
					}
					
					// 判断表是否存在
					wsprintf(sqlstr,"select count(0) from syscat.columns where tabname = upper('%s')",szTable);
					retcode = SQLPrepare(hstmt,(SQLCHAR*)sqlstr,SQL_NTS);
					CHECKDBSTMTERROR(hwndDlg,retcode,hstmt);
					retcode =SQLExecute(hstmt);
					CHECKDBSTMTERROR(hwndDlg,retcode,hstmt);
					while ( SQLFetch(hstmt) != SQL_NO_DATA_FOUND ){
						SQLINTEGER id=0;
						SQLGetData(hstmt,1,SQL_C_ULONG,&id,sizeof(SQLINTEGER),(SQLINTEGER*)NULL);
						if(0==id){
						MessageBoxPrintf("ERROR","TABLE <%s> does not exists!",szTable);
							return FALSE;
						}
					}
					SQLFreeStmt(hstmt,SQL_CLOSE);

					// do the job
					wsprintf(sqlstr,"select COLNAME from syscat.columns where tabname = upper('%s') ORDER BY COLNO ASC",szTable);
					retcode = SQLPrepare(hstmt,(SQLCHAR*)sqlstr,SQL_NTS);
					CHECKDBSTMTERROR(hwndDlg,retcode,hstmt);
					retcode =SQLExecute(hstmt);
					CHECKDBSTMTERROR(hwndDlg,retcode,hstmt);
					while ( SQLFetch(hstmt) != SQL_NO_DATA_FOUND ){
						//~ SQLINTEGER id=0;
						char name[32];
						ZeroMemory(name,sizeof(name)/sizeof(char));
						//~ SQLGetData(hstmt,1,SQL_C_ULONG,&id,sizeof(SQLINTEGER),(SQLINTEGER*)NULL);
						SQLGetData(hstmt,1,SQL_C_CHAR,name,sizeof(name)/sizeof(SQLCHAR),(SQLINTEGER*)NULL);
						//~ MessageBoxPrintf("Result","%s",name);
						strncat(Content,name,32);
						strncat(Content,"\r\n,",32);
					}
					*(Content+strlen(Content)-1)=0;
					//~ strncpy(Content2,Content,strlen(Content)-2);
					SetDlgItemText(hwndDlg,IDC_EDIT2,Content);
					//~ SendMessage(hEdit, EM_LINESCROLL, 0, 80);//WS_VSCROLL
					SQLFreeStmt(hstmt,SQL_CLOSE);
				}				
				default:
					break;
			}
			return TRUE;
		}
		break;
	case WM_CLOSE://Massage for terminate/exit (may close button clicked on title bar)
		{
			//Close dialog
			SQLFreeStmt(hstmt,SQL_CLOSE);	
			SQLDisconnect(hdbc);	
			SQLFreeHandle(SQL_HANDLE_DBC, hdbc);  
			SQLFreeHandle(SQL_HANDLE_ENV, henv);					
			//~ EndDialog(hwndDlg,0);
			DestroyWindow(hwndDlg);			
			break;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0); 
			return TRUE;
		}
	case WM_CTLCOLORDLG: //set its text and background colors using the specified display device context handle.
		{
			break;			
		}
	case WM_PAINT:
		{
			break;			
		}
	case WM_CTLCOLORSTATIC: //可以控制静态控件的颜色
		{
			break;			
		}
	default:
		break;			
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

