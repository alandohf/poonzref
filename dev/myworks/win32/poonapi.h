// some useful function developed / collected by poon!
// std c lib
#include <stdio.h>     
// win32 c lib 
#include <windows.h>
#include <tchar.h>     // for _vsntprintf

// other c lib
#include <sqlext.h>
#include <sqltypes.h>

// use Messagebox like printf!
int CDECL MessageBoxPrintf (TCHAR * szCaption, TCHAR * szFormat, ...);
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

