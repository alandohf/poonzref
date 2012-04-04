
/*
*---------------------------------------------------------------------------
;program name  : 基于对话框的应用程序_颜色值提取工具
;author		   : panzhiwei
;date		   : 2012-03-20
;function desc : 通过调色板选择颜色并输出颜色值(10进制和16进制)
;compiler      : vc6 enterprise 
;notes		   :t00008_DAPcolorPanel提取颜色值
;				2.http://blog.csdn.net/genaman/article/details/4336483
;revision log  :
;ref  :http://msdn.microsoft.com/en-us/library/windows/desktop/bb856484(v=vs.85).aspx
;1.	cl /c /IC:\poon\wcwp\wcwp\bin\VC6CMD\INCLUDE;C:\poon\wcwp\wcwp\bin\VC6CMD\MFC\INCLUDE;C:\poon\wcwp\wcwp\bin\VC6CMD\MFC\ATL\INCLUDE /c t00008_DAPcolorPanel.c
;2.	rc  /r t00008_DAPcolorPanel
;3.	link.exe /DEFAULTLIB:kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib winmm.lib wininet.lib MSWSOCK.LIB /OUT:t00008_DAPcolorPanel.exe  /nologo /subsystem:windows /incremental:no /machine:I386 t00008_DAPcolorPanel.obj t00008_DAPcolorPanel.res

*---------------------------------------------------------------------------
*/


#include <Windows.h> //Core header file for win32 based Applictions
#include <Windowsx.h> //Core header file for win32 based Applictions
//#include <COMMCTRL.H>
#include "resource.h" //Include for dialog(IDD_DIALOG1) resource 
#define true TRUE
//Callback function for DialogBox Function.

RECT rect;

LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Application entry point
int APIENTRY  WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//Create and display dialog box
//		InitCommonControls();
 	DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)DlgProc);
	//Exit  
	return 0;
}

//DlgProc processes messages sent to dialog by windows
LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
						HWND hCBox = GetDlgItem(hwndDlg,IDC_COMBO1);
						int curSel;
						int i = 0;
						int cnt;
						char a[1];
	switch (uMsg)
	{

	case WM_INITDIALOG:// WM_INITDIALOG message is sent before dialog is displayed
		{	


			//Optional : set dialog icon 

			//~ SendMessage(hCBox,CB_INSERTSTRING,0,(LPARAM)TEXT("CHOOSE1"));
			//~ SendMessage(hCBox,CB_INSERTSTRING,1,(LPARAM)TEXT("CHOOSE2"));
			//Must return true for keyboard focus 
			//~ ComboBox_InsertString(hCBox,0,TEXT("CHOOSE1a"));
			//~ ComboBox_InsertString(hCBox,1,TEXT("CHOOSE2a"));
			//~ ComboBox_InsertString(hCBox,2,TEXT("CHOOSE3a"));
			while ( i < 10){
				wsprintf(a,"choice%d",i);
				ComboBox_InsertString(hCBox,0,a);
				i++;
			}
			return true;
		}
		break;
	case WM_COMMAND:// 
		{	
			switch(wParam)
			{
				case IDC_BUTTON1:
					 curSel=ComboBox_GetCurSel(hCBox);
					//ComboBox_DeleteString(hCBox,curSel);
					cnt=ComboBox_GetCount(hCBox);
					//wsprintf(a,"%d",cnt);
					ComboBox_GetLBText(hCBox,curSel,a);
					MessageBox(hwndDlg,a,TEXT("EL"),MB_OK);
					//ComboBox_SetCurSel(hCBox,0);
				/**
				switch(curSel)
				{
					case 0 :
						MessageBox(hwndDlg,TEXT("you choose 0!"),TEXT("EL"),MB_OK);
					break;
					case 1 :
						MessageBox(hwndDlg,TEXT("you choose 1!"),TEXT("EL"),MB_OK);
					break;
					case 2 :
						MessageBox(hwndDlg,TEXT("you choose 2!"),TEXT("EL"),MB_OK);
					break;
					case 3 :
						MessageBox(hwndDlg,TEXT("you choose 3!"),TEXT("EL"),MB_OK);
					break;
					case 4 :
						MessageBox(hwndDlg,TEXT("you choose 4!"),TEXT("EL"),MB_OK);
					break;
					case 5 :
						MessageBox(hwndDlg,TEXT("you choose 5!"),TEXT("EL"),MB_OK);
					break;
					case 6 :
						MessageBox(hwndDlg,TEXT("you choose 6!"),TEXT("EL"),MB_OK);
					break;
					case 7 :
						MessageBox(hwndDlg,TEXT("you choose 7!"),TEXT("EL"),MB_OK);
					break;
					case 8 :
						MessageBox(hwndDlg,TEXT("you choose 8!"),TEXT("EL"),MB_OK);
					break;
					case 9 :
						MessageBox(hwndDlg,TEXT("you choose 9!"),TEXT("EL"),MB_OK);
					break;
					case 10 :
						MessageBox(hwndDlg,TEXT("you choose 10!"),TEXT("EL"),MB_OK);
					break;
					default:
				}
				**/
				default:
					break;
			}
			return true;
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

