
#define WINVER 0x0500

#include <Windows.h>

const char g_szClassName[] = "myWindowClass";
HWND hwndSta1;
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        0,
        g_szClassName,
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        0, 0, 540, 240,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    //nCmdShow = 9;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

      hwndSta1 = CreateWindow(TEXT("BUTTON"), "xxx",
      WS_CHILD | WS_VISIBLE,
      80, 40, 55, 25, 
      hwnd, (HMENU) 2, NULL, NULL);
    ShowWindow(hwndSta1, nCmdShow);
    UpdateWindow(hwndSta1);    
    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
FLASHWINFO fwi;

	switch(Message)
    {
      case WM_CREATE:
          CreateWindow(TEXT("BUTTON"), TEXT("Flash"),
		  WS_CHILD | WS_VISIBLE,
		  10, 10, 80, 25, 
		  hwnd, (HMENU) 1, NULL, NULL);	    
        break;

      case WM_COMMAND:
				
          fwi.cbSize = sizeof(fwi);
          fwi.dwFlags = FLASHW_ALL;
          fwi.dwTimeout = 0;
          fwi.hwnd = hwndSta1;
          fwi.uCount = 10;

          FlashWindowEx(&fwi);
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