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
    //��ʼ��Socket��
    SOCKADDR_IN sa;
	SOCKET sock ;
	int ret_conn;
	TCHAR cQuit[] = "QUIT\n";
    WSAStartup(MAKEWORD(2,0),&wsaData);
    //����һ������
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sa.sin_family=AF_INET;
    //���õ������ӷ������˵Ķ˿�
    sa.sin_port = htons(IPPORT_SMTP);
    //123.125.50.135��ping smtp.163.com�����ģ�����ὲʹ��gethostbyname��ֱ�Ӵ�
    //�������õ�ip��ַ
    sa.sin_addr.S_un.S_addr = inet_addr("220.181.12.15");
    //Ϊʲô�������ÿͻ��˵Ķ˿ڣ��ѵ�����Ҫ�ͻ��˵Ķ˿���
    switch(uMsg)
    {
        case WM_INITDIALOG:
            /*
             * TODO: Add code to initialize the dialog.
             */
            return TRUE;

        case WM_CLOSE:
            //�����顣�Ѵ���ű����ܹ��ּ���
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
                    //�����ʺ���
                    recv(sock,buffer,256,0);
                    MessageBox(hwndDlg,buffer,"the Server say:",0);
                    // send quit
                    send(sock,cQuit,lstrlen(cQuit),0);
                    ZeroMemory(buffer,sizeof(buffer)/sizeof(char));
                    //����GoodBye
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
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER| //�Զ�������Ϣ������
    FORMAT_MESSAGE_FROM_SYSTEM, //��ϵͳ��ȡ��Ϣ
    NULL,GetLastError(), //��ȡ������Ϣ��ʶ
    MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),//ʹ��ϵͳȱʡ����
    (LPTSTR)&lpMsgBuf, //��Ϣ������
    0,
    NULL);
    MessageBox(NULL,lpMsgBuf,"",MB_ICONERROR);
}
