#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#include "resource.h"
void ShowError();

HINSTANCE hInst;

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    char buffer[256];
    WSADATA wsaData;
    //初始化Socket库
    SOCKADDR_IN sa;
	SOCKET sock ;
	int ret_conn;
	TCHAR cQuit[] = "QUIT\n";
    WSAStartup(MAKEWORD(2,0),&wsaData);
    //创建一根电线
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sa.sin_family=AF_INET;
    //设置电线连接服务器端的端口
    sa.sin_port = htons(IPPORT_SMTP);
    //123.125.50.135是ping smtp.163.com出来的，后面会讲使用gethostbyname来直接从
    //主机名得到ip地址
    sa.sin_addr.S_un.S_addr = inet_addr("220.181.12.15");
    //为什么不用设置客户端的端口，难道不需要客户端的端口吗？
    switch(uMsg)
    {
        case WM_INITDIALOG:
            /*
             * TODO: Add code to initialize the dialog.
             */
            return TRUE;

        case WM_CLOSE:
            //做事情。把大象放冰箱总共分几步
            closesocket(sock);
            WSACleanup();
            EndDialog(hwndDlg, 0);
            return TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                /*
                 * TODO: Add more control ID's, when needed.
                 */
                case IDC_BTN_SEND:
                    break;
                case IDC_BTN_RECV:
					ret_conn = connect(sock,(SOCKADDR *)&sa,sizeof(sa));
                    if( ret_conn == SOCKET_ERROR)
                    {
                    ShowError();
                    return -1;
                    }
                    printf("connect return :%d\n",ret_conn);
                    ZeroMemory(buffer,sizeof(buffer)/sizeof(char));
                    //接收问候语
                    recv(sock,buffer,256,0);
                    MessageBox(hwndDlg,buffer,"the Server say:",0);
                    // send quit
                    send(sock,cQuit,lstrlen(cQuit),0);
                    ZeroMemory(buffer,sizeof(buffer)/sizeof(char));
                    //接收GoodBye
                    recv(sock,buffer,256,0);
                    MessageBox(hwndDlg,buffer,"",0);
                    return TRUE;
            }
    }

    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst = hInstance;

    // The user interface is a modal dialog box
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DialogProc);
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
