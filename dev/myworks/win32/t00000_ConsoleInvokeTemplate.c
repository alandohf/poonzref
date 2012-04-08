
/****************************************************************************
  *  program name  : 通過控制臺調用的窗口程序模板
  *  author		   : panzhiwei
  *  date		   : 2012-03-27
  *  function desc : recv & send msg between a smtp server
  *  compiler      : vc6 enterprise
  *  todo		   : 1.
					 2.
					 3.
  *  notes		   : 1.DialogBoxParam可以传递参数！
  *  				 2.
  *  				 3.
  *  revision log  : 1.
					 2.
					 3.
  *  reference	   : 1.http://dslweb.nwnexus.com/~ast/dload/guicon.htm
					 2.
					 3.
*****************************************************************************/

//~ #define WIN32_LEAN_AND_MEAN
#include "poonapi.h"
#include "resource.h"

	static char buff[1000];
	
int main(int argc, char *argv[]) {
	ZeroMemory(buff,sizeof(buff)/sizeof(char));	
	printf("%s\n",argv[0]);	
	WinMain(NULL,NULL,argv[0],SW_SHOWNORMAL);
	printf("%s\n",argv[0]);
	return 0;
}

int APIENTRY  WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
//		InitCommonControls();
 	//~ DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)DlgProc);
	DialogBoxParam(hInstance, (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)DlgProc,(LPARAM)lpCmdLine);
	return 0;
}



LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{

	case WM_INITDIALOG:// WM_INITDIALOG message is sent before dialog is displayed
		{
			strncpy(buff,(char*)lParam,sizeof(buff)/sizeof(char));
			return TRUE;
		}
		break;
	case WM_COMMAND://
		{
			switch(wParam)
			{
				case IDC_BUTTON1:
					{
						MessageBoxPrintf("hi","%s\n",buff);
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
	case WM_CTLCOLORSTATIC: //可以控制静态控件的颜色
		{
			
		break;
		}
	default:
		break;			

	}
	return FALSE;
}




