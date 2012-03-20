
/*
*---------------------------------------------------------------------------
;program name  : 基于对话框的应用程序_颜色值提取工具
;author		   : panzhiwei
;date		   : 2012-03-20
;function desc : 通过调色板选择颜色并输出颜色值(10进制和16进制)
;compiler      : vc6 enterprise 
;notes		   :t00008_DAPcolorPanel提取颜色值
;revision log  :
;1.	cl /c /IC:\poon\wcwp\wcwp\bin\VC6CMD\INCLUDE;C:\poon\wcwp\wcwp\bin\VC6CMD\MFC\INCLUDE;C:\poon\wcwp\wcwp\bin\VC6CMD\MFC\ATL\INCLUDE /c t00008_DAPcolorPanel.c
;2.	rc  /r t00008_DAPcolorPanel
;3.	link.exe /DEFAULTLIB:kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib winmm.lib wininet.lib MSWSOCK.LIB /OUT:t00008_DAPcolorPanel.exe  /nologo /subsystem:windows /incremental:no /machine:I386 t00008_DAPcolorPanel.obj t00008_DAPcolorPanel.res

*---------------------------------------------------------------------------
*/


/**
DlgProc 中的switch语句对各种消息的处理可以通过
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);
    }
来处理，让各个消息过程更清晰！（rupeng.com)
**/	

#include <Windows.h> //Core header file for win32 based Applictions
//#include <COMMCTRL.H>
#include "resource.h" //Include for dialog(IDD_DIALOG1) resource 
#define true TRUE
//Callback function for DialogBox Function.

//~ RECT rect;

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
	CHOOSECOLOR cc;                 // common dialog box structure 
	static COLORREF acrCustClr[16]; // array of custom colors 
	//HWND hwnd;                      // owner window
	HBRUSH hbrush,hB;                  // brush handle
	//const DWORD RGBinit = GetSysColor(COLOR_WINDOW);
	static RedrawFlag = 0;
	static DWORD rgbCurrent;        // initial color selection
	TCHAR  cRgbValH[32];        
	TCHAR  cRgbValD[32];        
//
    static PAINTSTRUCT ps;
//    static HDC hDC ;
    HDC hDC = (HDC)wParam;

	switch (uMsg)
	{

	case WM_INITDIALOG:// WM_INITDIALOG message is sent before dialog is displayed
		{	
			//Optional : set dialog icon 
			SendMessage(hwndDlg,WM_SETICON,ICON_BIG,(LPARAM)LoadIcon(NULL,IDI_APPLICATION));
			
			//Must return true for keyboard focus 
			return true;
		}
		break;
	case WM_COMMAND:// 
		{	
			switch(wParam)
			{
				case IDC_BTN_CLK:
					{
						// Initialize CHOOSECOLOR 
						ZeroMemory(&cc, sizeof(cc));
						cc.lStructSize = sizeof(cc);
						cc.hwndOwner = hwndDlg;
						cc.lpCustColors = (LPDWORD) acrCustClr;
						cc.rgbResult = rgbCurrent;
						cc.Flags = CC_ANYCOLOR | CC_RGBINIT;
 
						if (ChooseColor(&cc)==TRUE) {
							hbrush = CreateSolidBrush(cc.rgbResult);
							rgbCurrent = cc.rgbResult; 
							//%[-][#][0][width][.precision]type
							wsprintf(cRgbValH,"0x%02X%02X%02X",GetRValue(rgbCurrent),GetGValue(rgbCurrent),GetBValue(rgbCurrent)); //0x00bbggrr 
							wsprintf(cRgbValD,"%hu,%hu,%hu",GetRValue(rgbCurrent),GetGValue(rgbCurrent),GetBValue(rgbCurrent)); //0x00bbggrr 
							SetDlgItemText(hwndDlg,IDC_EDIT_COLORVAL,cRgbValH);
							SetDlgItemText(hwndDlg,IDC_EDIT_COLORVAL2,cRgbValD);
						    RedrawFlag = 1;
							//强制重绘客户区
							InvalidateRect(hwndDlg,NULL,TRUE);	//获取颜色后强制重绘客户区
						}
					}
					break;
				case IDC_BTN_QUIT:
					{
						EndDialog(hwndDlg,0);
					}
				default:
					break;
			}
			return true;
		}
		break;
	case WM_CTLCOLORDLG: //set its text and background colors using the specified display device context handle. 
		{	
			if ( 1 == RedrawFlag ){
				hB = CreateSolidBrush(rgbCurrent);
				return (LONG)hB;		
			}
		}
		break;
/*
//InvalidateRect不适用！
	case WM_PAINT:
		{
			hB = CreateSolidBrush(rgbCurrent);
			hoB=hB;
			DeleteObject(hoB);
			return (LONG)hB;
		}
		break;
	
*/
	case WM_CTLCOLORSTATIC: //可以控制静态控件的颜色
		{

							//~ rect.left = 0;
							//~ rect.right = 50;
							//~ rect.top = 0;
							//~ rect.bottom = 50;
							//~ hDC = BeginPaint(hwndDlg, &ps);
							//~ FillRect(hDC, &rect, (HBRUSH)(rgbCurrent+1));
							//~ EndPaint(hwndDlg, &ps);
							//~ hB = CreateSolidBrush(0XFFFFFF);
							//~ SetTextColor(hDC, RGB(255, 0, 255));
							//~ SetBkMode(hDC, TRANSPARENT);
							//~ return (LONG)hB;
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

