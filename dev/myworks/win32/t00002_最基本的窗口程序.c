/*
*---------------------------------------------------------------------------
;program name  : 最基本的窗口程序
;author		   : panzhiwei
;date		   : 2012-03-15
;function desc : 
;notes		   :
;1.  However there is currently a bug that you'd still get this error if _start is linked at offset 0??
;2.  GetMessage的参数要设置正确(NULL),否则将出现窗口关闭，进程还在的情况。
;3.	 WNDCLASSEX类成员一定要设置正确，否则无法注册窗口。
;4.	 为什么用GCC编译产生的文件如此大(700k+)？而用VC才150K左右。
;revision log  :
;1.
;2.
;3.
*---------------------------------------------------------------------------
*/

#include <Windows.h>
//#include "StdAfx.h"


char WinClassName[] = "MyWinClass";
char lpWndName[] = "MyWindow";

//~ LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        //~ case WM_COMMAND:
        //~ break;
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
							,200
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


