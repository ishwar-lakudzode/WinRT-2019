#include<Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR csCmd, int iShow)
{
	WNDCLASSEX wndClass;
	MSG msg;
	HWND hWnd;
	TCHAR szAppName[] = TEXT("MessageboxAss");

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

	MessageBox(NULL, TEXT("Window creation is under progress..."), TEXT("Assignment 4"), MB_OK);

	hWnd = CreateWindow(szAppName, TEXT("MessageBox and MSG Handeling"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	TCHAR strMsg[255];

	switch (msg)
	{
	case WM_CREATE:
		wsprintf(strMsg, TEXT("WM_CREATE is called"));
		MessageBox(hWnd, strMsg, TEXT("WM_CREATE"), MB_OK);
		break;
	case WM_KEYDOWN:
		wsprintf(strMsg, TEXT("WM_KEYDOWN is called"));
		MessageBox(hWnd, strMsg, TEXT("WM_KEYDOWN"), MB_OK);
		break;
	case WM_LBUTTONDOWN:
		wsprintf(strMsg, TEXT("WM_LBUTTONDOWN is called"));
		MessageBox(hWnd, strMsg, TEXT("WM_LBUTTONDOWN"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}