
/*
*---------------------------------------------------------------------------
;program name  : ���ڶԻ����Ӧ�ó���_socket_smtp
;author		   : panzhiwei
;date		   : 2012-03-27
;function desc : recv & send msg between a smtp server
;compiler      : vc6 enterprise
;notes		   :
;todo		   : ���ӹر����ӵİ�ť
;1.ע�⣡socket()�ķ���ֵ��һ��SOCKET�ṹ�壡����һ��������
;2.send quit �Ժ�sock Ҫ���½��������Ӳ����ٴ�ͨ�š�
;3.�ظ���recv�������⣡1��send��1��recv���ɡ�
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
                    //�����ʺ���
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
                    //����GoodBye
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
	case WM_CTLCOLORSTATIC: //���Կ��ƾ�̬�ؼ�����ɫ
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
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER| //�Զ�������Ϣ������
    FORMAT_MESSAGE_FROM_SYSTEM, //��ϵͳ��ȡ��Ϣ
    NULL,GetLastError(), //��ȡ������Ϣ��ʶ
    MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),//ʹ��ϵͳȱʡ����
    (LPTSTR)&lpMsgBuf, //��Ϣ������
    0,
    NULL);
    MessageBox(NULL,lpMsgBuf,"",MB_ICONERROR);
}

