
/*
*---------------------------------------------------------------------------
;program name  : 基于对话框的应用程序_socket_smtp
;author		   : panzhiwei
;date		   : 2012-03-27
;function desc : recv & send msg between a smtp server
;compiler      : vc6 enterprise
;notes		   :
;todo		   : 增加关闭连接的按钮
;1.注意！socket()的返回值是一个SOCKET结构体！不是一个整数！
;2.send quit 以后，sock 要重新建立并连接才能再次通信。
;3.重复的recv会有问题！1个send，1个recv方可。
;revision log  :

*---------------------------------------------------------------------------
*/

//~ #include <Winsock2.h>
//~ #include "resource.h"
//~ #pragma comment(lib,"ws2_32")

//~ #define WIN32_LEAN_AND_MEAN

//~ #include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

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
    char buffer[256];
	TCHAR cQuit[] = "QUIT\n";
	static  WSADATA wsadata;
	static  SOCKET	sock;
	static  SOCKADDR_IN sin;
	static  WORD wVersionRequested;
	int ret	= 0;
	sin.sin_family=AF_INET;
	sin.sin_port = htons(IPPORT_SMTP);
	sin.sin_addr.S_un.S_addr = inet_addr("220.181.12.11");
    wVersionRequested = MAKEWORD(2,0);
    ret=WSAStartup(wVersionRequested,&wsadata);
    if(ret != 0 )
        ShowError();

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
                    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
                    if(sock == INVALID_SOCKET )
                        ShowError();
                    ret=connect(sock,(SOCKADDR *)&sin,sizeof(sin));
                    if(ret == SOCKET_ERROR )
                        ShowError();
                    ZeroMemory(buffer,sizeof(buffer)/sizeof(char));
                    //接收问候语
                    ret = recv(sock,buffer,256,0);
                    if(ret == SOCKET_ERROR )
                        ShowError();
                    MessageBox(hwndDlg,buffer,"the Server say:",0);
					break;
				case IDC_BUTTON2:
                    // send quit
                    ret = send(sock,cQuit,lstrlen(cQuit),0);
                    printf("%d\n",ret);
                    if(ret == SOCKET_ERROR )
                        ShowError();
                    ZeroMemory(buffer,sizeof(buffer)/sizeof(char));
                    //接收GoodBye
                    recv(sock,buffer,256,0);
                    if(ret == SOCKET_ERROR )
                        ShowError();
                    MessageBox(hwndDlg,buffer,"the Server say:",0);
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
			closesocket(sock);
			WSACleanup();
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

