#include <Windows.h> //Core header file for win32 based Applictions
#include <COMMCTRL.H>
#include "resource.h" //Include for dialog(IDD_DIALOG1) resource 
#define true TRUE
//Callback function for DialogBox Function.

LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Application entry point
int APIENTRY  WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//Create and display dialog box
		//~ InitCommonControls();
 	DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)DlgProc);
	//Exit  
	return 0;
}

//DlgProc processes messages sent to dialog by windows
LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{

	case WM_INITDIALOG:// WM_INITDIALOG message is sent before dialog is displayed
		{	
			//Optional : set dialog icon 
			SendMessage(hwndDlg,WM_SETICON,ICON_BIG,(LPARAM)LoadIcon(NULL,IDI_APPLICATION));
			
			//Must return true for keyboard focus 
			return true;
		}
	case WM_CLOSE://Massage for terminate/exit (may close button clicked on title bar)
		{
			//Close dialog
		EndDialog(hwndDlg,0);
			break;
		}

	
	}
	return FALSE;
}