
/****************************************************************************
  *  program name  : ���ڶԻ����Ӧ�ó���_socket_smtp
  *  author		   : panzhiwei
  *  date		   : 2012-03-27
  *  function desc : recv & send msg between a smtp server
  *  compiler      : vc6 enterprise
  *  todo		   : 1.���ӹر����ӵİ�ť  
					 2.
					 3.
  *  notes		   : 1.ע�⣡socket()�ķ���ֵ��һ��SOCKET�ṹ�壡����һ��������
  *  				 2.send quit �Ժ�sock Ҫ���½��������Ӳ����ٴ�ͨ�š�
  *  				 3.�ظ���recv�������⣡1��send��1��recv���ɡ�
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

