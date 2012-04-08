
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
static HBRUSH hbrWhite;
static HBRUSH hbrGray; 
    static HDC hdc ;
   static RECT rc;
	int i , x, y;
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


case WM_CREATE: 
    hbrWhite = GetStockObject(BLACK_BRUSH); 
    hbrGray  = GetStockObject(BLACK_BRUSH); 
    return 0L; 
 
case WM_ERASEBKGND:
	//~ {
		//~ hdc = (HDC) wParam; 
		//~ GetClientRect(hwndDlg, &rc); 
		//~ SetMapMode(hdc, MM_ANISOTROPIC); 
		//~ SetWindowExtEx(hdc, 100, 100, NULL); 
		//~ SetViewportExtEx(hdc, rc.right, rc.bottom, NULL); 
		//~ FillRect(hdc, &rc, hbrWhite); 
	 
		//~ for (i = 0; i < 13; i++) 
		//~ { 
			//~ x = (i * 40) % 100; 
			//~ y = ((i * 40) / 100) * 20; 
			//~ SetRect(&rc, x, y, x + 20, y + 20); 
			//~ FillRect(hdc, &rc, hbrGray); 
		//~ } 
	  //~ return 1L; 
	//~ }
	default:
		break;			

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

