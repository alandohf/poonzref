
/****************************************************************************
  *  program name  : 基于对话框的应用程序_socket_smtp
  *  author		   : panzhiwei
  *  date		   : 2012-03-27
  *  function desc : recv & send msg between a smtp server
  *  compiler      : vc6 enterprise
  *  todo		   : 1.增加关闭连接的按钮  
					 2.
					 3.
  *  notes		   : 1.注意！socket()的返回值是一个SOCKET结构体！不是一个整数！
  *  				 2.send quit 以后，sock 要重新建立并连接才能再次通信。
  *  				 3.重复的recv会有问题！1个send，1个recv方可。
  *  revision log  : 1.
					 2.
					 3.
  *  reference	   : 1.
					 2.
					 3.
*****************************************************************************/

//~ #define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//~ #include <winsock2.h>
//~ #include <ws2tcpip.h>
#include "resource.h"

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
					break;
				case IDC_BTN_SEND:
					break;
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

