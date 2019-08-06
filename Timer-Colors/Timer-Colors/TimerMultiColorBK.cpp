#include<Windows.h>
#include<tchar.h>
#define TimerID 201

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR csCmd, int iShow)
{
	WNDCLASSEX wndClass;
	MSG msg;
	HWND hWnd;
	TCHAR szAppName[] = TEXT("TimerMultiBKColor");

	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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

	hWnd = CreateWindow(szAppName, TEXT("Timer Multiple Background Color"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	HDC hdc;
	RECT rc;
	TCHAR str[255];
	PAINTSTRUCT ps;
	static int iPaintFlag = -1;
	HBRUSH hBrush;
	RECT rectTemp;
	switch (msg)
	{
	case WM_CREATE:
		SetTimer(hWnd, TimerID, 500, NULL);
		break;
	case WM_TIMER:
		KillTimer(hWnd, TimerID);
		iPaintFlag++;
		if (iPaintFlag > 7)
			iPaintFlag = 0;
		InvalidateRect(hWnd,NULL, TRUE);
		SetTimer(hWnd, TimerID, 500, NULL);
		break;
	case WM_PAINT:
		GetClientRect(hWnd, &rc);
		
		hdc = BeginPaint(hWnd, &ps);
		if (iPaintFlag >= 0)
		{
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rc.left;
			rectTemp.top = rc.top;
			rectTemp.right = rc.right / 8;
			FillRect(hdc, &rectTemp, hBrush);
		}
		if (iPaintFlag >= 1)
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
		}
		if (iPaintFlag >= 2)
		{
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
		}
		if (iPaintFlag >= 3)
		{
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
		}
		if (iPaintFlag >= 4)
		{
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
		}
		if (iPaintFlag >= 5)
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
		}
		if (iPaintFlag >= 6)
		{
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
		}
		if (iPaintFlag >= 7)
		{
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
		}

		EndPaint(hWnd, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}