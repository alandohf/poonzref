#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    char* lpCmdLine, int nCmdShow)
{
    MessageBox(NULL, lpCmdLine, "Note", MB_OK);
    return 0;
}