#include <windows.h>

const char g_szClassName[] = "myWindowClass";
HWND hwndSta1;
HWND hwndSta2;


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void CreateLabels(HWND);

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
  hwnd = CreateWindow( wc.lpszClassName, "Moving",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                150, 150, 250, 180, 0, 0, hInstance, 0);  
		


    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    CreateLabels(hwnd);		

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

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

	char buf[10];
	RECT rect;
	
    switch(Message)
    {
	    case WM_MOVE:
		GetWindowRect(hwnd, &rect);

		_itoa(rect.left, buf, 10);
		SetWindowText(hwndSta1, buf);

		_itoa(rect.top, buf, 10);
		SetWindowText(hwndSta2, buf);


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


void CreateLabels(HWND hwnd){

  CreateWindow("static", "x: ",
      WS_CHILD | WS_VISIBLE,
      10, 10, 25, 25, 
      hwnd, (HMENU) 1, NULL, NULL);
				
  hwndSta1 = CreateWindow("static", "150",
      WS_CHILD | WS_VISIBLE,
      40, 10, 55, 25, 
      hwnd, (HMENU) 2, NULL, NULL);

  CreateWindow("static", "y: ",
      WS_CHILD | WS_VISIBLE,
      10, 30, 25, 25, 
      hwnd, (HMENU) 3, NULL, NULL);

  hwndSta2 = CreateWindow("static", "150",
      WS_CHILD | WS_VISIBLE,
      40, 30, 55, 25, 
      hwnd, (HMENU) 4, NULL, NULL);
}
