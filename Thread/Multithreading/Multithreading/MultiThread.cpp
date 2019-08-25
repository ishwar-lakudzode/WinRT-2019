#include<Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

DWORD WINAPI ThreadFuncOne(LPVOID);
DWORD WINAPI ThreadFuncTwo(LPVOID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR csCmd, int iShow)
{
	WNDCLASSEX wndClass;
	MSG msg;
	HWND hWnd;
	TCHAR szAppName[] = TEXT("FirstWin32Prog");

	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
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

	hWnd = CreateWindow(szAppName, TEXT("First Win32 Program"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	UpdateWindow(hWnd);
	ShowWindow(hWnd, iShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;

	switch (msg)
	{
	case WM_CREATE:
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFuncOne, (LPVOID)hWnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFuncTwo, (LPVOID)hWnd, 0, NULL);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, TEXT("WM_LBUTTONDOWN clicked"), TEXT("Message"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

DWORD WINAPI ThreadFuncOne(LPVOID Param)
{
	HDC hdc;
	long i;
	TCHAR str[255];
	hdc = GetDC((HWND)Param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (i = 0; i < 429496729; i++)
	{
		wsprintf(str, TEXT("Thread One -> Increasing Order: %ld"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));
	}
	ReleaseDC((HWND)Param, hdc);
	return 0;
}

DWORD WINAPI ThreadFuncTwo(LPVOID Param)
{
	HDC hdc;
	long i;
	TCHAR str[255];
	hdc = GetDC((HWND)Param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (i = 429496729; i > 0; i--)
	{
		wsprintf(str, TEXT("Thread Two -> Decreasing Order: %ld"), i);
		TextOut(hdc, 5, 25, str, wcslen(str));
	}
	ReleaseDC((HWND)Param, hdc);
	return 0;
}