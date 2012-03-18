
/*
*---------------------------------------------------------------------------
;program name  : 最基本的窗口程序_带基本菜单
;author		   : panzhiwei
;date		   : 2012-03-16
;function desc : 
;notes		   :
;revision log  :
;1.
;2.
;3.
*---------------------------------------------------------------------------
*/

#include <Windows.h>
#include "resource.h"

//#include "StdAfx.h"

char WinClassName[] = "MyWinClass";
char lpWndName[] = "MyWindow(Will do Something)";

//~ LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
			HMENU hmenu0;
			HMENU hmenu0_1;

    switch(Message)
    {
		
        case WM_CREATE:	
			 hmenu0 = CreateMenu();
			 hmenu0_1 = CreatePopupMenu();
			AppendMenu(hmenu0_1, MF_STRING, IDM_ABOUT1, ("&About"));
			AppendMenu(hmenu0, MF_STRING | MF_POPUP | MF_MENUBREAK, (UINT_PTR)hmenu0_1, ("&Help"));
		            SetMenu(hwnd, hmenu0);
        break;
		case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
          case IDM_ABOUT1:
               MessageBox (hwnd
							,TEXT("Menu Responed!")
							,TEXT("About")
							, MB_ICONINFORMATION | MB_OK
						  );
			break;
		}
		break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int APIENTRY
WinMain(HINSTANCE hinst,HINSTANCE phinst,LPSTR lpCmdLine,int nCmdShow){
	//~ WNDCLASS wc;
	WNDCLASSEX wc;
	HWND hWnd ;
	MSG msg;
	//~ wc.lpszClassName = WinClassName;
	//~ wc.hInstance = hinst;
	//~ wc.lpfnWndProc = WndProc;
	wc.cbClsExtra 		= 0;
	wc.cbSize 			= sizeof(wc);
	wc.cbWndExtra 		= 0;
	wc.hbrBackground 	= (HBRUSH)(COLOR_WINDOW+1);
	wc.hCursor 			= NULL;
	wc.hIcon 			= NULL;
	wc.hIconSm 			= NULL;
	wc.hInstance 		= hinst;
	wc.lpfnWndProc 		= WndProc;
	wc.lpszClassName 	= WinClassName;
	wc.lpszMenuName 	= NULL;
	//~ wc.style = CS_NOCLOSE;
	wc.style 			= 0;

if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

	
	hWnd = CreateWindowEx(0,WinClassName,lpWndName
							,WS_OVERLAPPEDWINDOW
							,0,0
							,400
							,200
							,NULL
							,NULL
							,hinst
							,NULL);
	
	
    if(hWnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
	
	ShowWindow(hWnd,SW_NORMAL);
	
	UpdateWindow(hWnd);
	
	while(1){
			if ( 0 == GetMessage(&msg,NULL,0,0) ){ // 注意NULL的使用!
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}
	
	//~ MessageBox(
	//~ NULL
	//~ ,TEXT("My Message")
	//~ ,TEXT("My Title")	
	//~ ,MB_OK);
    return msg.wParam;
	}


