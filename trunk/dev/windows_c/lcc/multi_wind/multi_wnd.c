#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK PanelProc(HWND, UINT, WPARAM, LPARAM);
void RegisterRedPanel(void);
void RegisterBluePanel(void);


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
  MSG  msg ;    
  WNDCLASS wc = {0};
  wc.lpszClassName = TEXT( "Windows" );
  wc.hInstance     = hInstance ;
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wc.lpfnWndProc   = WndProc ;
  wc.hCursor       = LoadCursor(0,IDC_ARROW);
  
  RegisterClass(&wc);
  CreateWindow( wc.lpszClassName, TEXT("Windows"),
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                100, 100, 250, 180, 0, 0, hInstance, 0);  

  while( GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (int) msg.wParam;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

    
  switch(msg)  
  {
    case WM_CREATE:
    {

	RegisterRedPanel();
	CreateWindow(TEXT("RedPanel"), NULL, 
		WS_CHILD | WS_VISIBLE,
		20, 20, 80, 80,
		hwnd, (HMENU) 1, NULL, NULL);

	RegisterBluePanel();
	CreateWindow(TEXT("BluePanel"), NULL, 
		WS_CHILD | WS_VISIBLE,
		120, 20, 100, 100,
		hwnd, (HMENU) 2, NULL, NULL);

	break;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break; 
    }
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK PanelProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

  switch(msg)  
  {
    case WM_LBUTTONUP:
    {
        Beep(50, 50);
        break;
    }
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}


void RegisterRedPanel(void) {

  HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 0));

  WNDCLASS rwc = {0};
  rwc.lpszClassName = TEXT( "RedPanel" );
  rwc.hbrBackground = hbrush;
  rwc.lpfnWndProc   = PanelProc ;
  rwc.hCursor       = LoadCursor(0,IDC_ARROW);
  RegisterClass(&rwc);
  
}

void RegisterBluePanel(void) {

  HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 255));

  WNDCLASS rwc = {0};
  rwc.lpszClassName = TEXT( "BluePanel" );
  rwc.hbrBackground = hbrush;
  rwc.lpfnWndProc   = PanelProc ;
  rwc.hCursor       = LoadCursor(0,IDC_ARROW);
  RegisterClass(&rwc);
  
}
