// some useful function developed / collected by poon!
// std c lib
#include <stdio.h>     
// win32 c lib 
#include <windows.h>
#include <tchar.h>     // for _vsntprintf

// other c lib
#include <sqlext.h>
#include <sqltypes.h>

#define msgb(x) \
MessageBox(NULL, (LPCTSTR) x, \
(LPCTSTR) sAppName, \
(UINT) MB_OK | MB_ICONINFORMATION | MB_APPLMODAL)

	// Miscellaneous:
	#define STR_ABOUT _T("About \'odib\'")

	#define TEXT_HELP_ABOUT _T("\
\'odib\':\015\012\
Icon-based owner draw buttons\015\012\
Click the buttons or select menu items to\015\012\
display a string in the readonly edit control\015\012\
(c) Bruno Challier - 2007\015\012\015\012")


typedef struct tagThreadParam{
	HDBC hDBC;
	SQLCHAR server[32];
	int retcode;
} THREADPARAM,*pTHREADPARAM;



#define BUFFSIZE 1024
static TCHAR sLogFileName[] = _T("c:\\ccoutput\\file.log");

// use Messagebox like printf!
int CDECL MessageBoxPrintf (const char * szCaption,const char * szFormat, ...);
int APIENTRY  WinMain(HINSTANCE hInstance
						,HINSTANCE hPrevInstance
						,LPSTR lpCmdLine
						,int nCmdShow);
LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowError();
void exitm(char a[] );
void ShowDBError(HWND hwnd,SQLSMALLINT type,SQLHANDLE sqlHandle);
void ShowDBConnError(HWND hwnd,SQLHDBC hdbc);
void ShowDBStmtError(HWND hwnd,SQLHSTMT hstmt);
void HandleDiagnosticRecord (SQLHANDLE      hHandle,
                             SQLSMALLINT    hType,
                             RETCODE        RetCode);
int myWriteToLog(TCHAR* s);
void EraseBkGnd(HWND hwnd, HDC hdc,HBRUSH hbrWhite,HBRUSH hbrGray);
DWORD WINAPI db2connect(THREADPARAM * pTP);