#include<Windows.h>
#include"SplashScreen.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR csCmd, int iShow)
{
	WNDCLASSEX wndClass;
	MSG msg;
	HWND hWnd;
	TCHAR szAppName[] = TEXT("SplashScreen");

	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(MyIcon));
	wndClass.hIconSm = LoadIcon(NULL, MAKEINTRESOURCE(MyIcon));
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wndClass))
	{
		MessageBox(NULL, TEXT("Error in window creation"), TEXT("Error"), MB_OK);
		return 0;
	}

	hWnd = CreateWindow(szAppName, TEXT("Splash Screen"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	UpdateWindow(hWnd);
	ShowWindow(hWnd, iShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInst;
	static HBITMAP hBitMap = NULL;
	HDC hdcSrc;
	BITMAP bmp;
	RECT rc;
	HDC hdc;
	PAINTSTRUCT ps;
	
	switch (msg)
	{
	case WM_CREATE:
		hInst = GetModuleHandle(NULL);
		hBitMap = LoadBitmap(hInst, MAKEINTRESOURCE(MyBitmap));
		break;
	case WM_PAINT:
		GetClientRect(hWnd, &rc);
		hdc = BeginPaint(hWnd, &ps);
		hdcSrc = CreateCompatibleDC(NULL);
		SelectObject(hdcSrc, hBitMap);
		GetObject(hBitMap, sizeof(BITMAP), &bmp);
		StretchBlt(hdc, 50, 50, 500, 500, hdcSrc, 0, 0, 500, 500, SRCCOPY);
		DeleteObject(hdcSrc);
		EndPaint(hWnd, &ps);
	
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}