
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
#include "poonapi.h"
//~ #include <ws2tcpip.h>
#include "resource.h"

int APIENTRY  WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
//		InitCommonControls();
 	DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)DlgProc);
	return 0;
}

int main(int argc, char *argv[]) {
	//~ LPSTR lpCmdLine ;
	//~ lpCmdLine = GetCommandLine();
	WinMain(NULL,NULL,argv[1],SW_SHOWNORMAL);
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
				case IDC_BUTTON1:
					{
						
					}
					break;
				case IDC_BUTTON2:
					{
						
					}					
					break;
				default:
					break;
			}
			return TRUE;
		}
		break;
	case WM_CLOSE://Massage for terminate/exit (may close button clicked on title bar)
		{
			//Close dialog
		printf("Dialog box is going to close!");
		Sleep(2000);
		EndDialog(hwndDlg,0);
			break;
		}
	case WM_CTLCOLORDLG: //set its text and background colors using the specified display device context handle.
		{
		
		 break;			
		}
	case WM_PAINT:
		{
			
		break;
		}
	case WM_CTLCOLORSTATIC: //���Կ��ƾ�̬�ؼ�����ɫ
		{
			
		break;
		}
	default:
		break;			

	}
	return FALSE;
}




