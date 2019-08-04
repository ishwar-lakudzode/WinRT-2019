#include<Windows.h>
#include<tchar.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR csCmd, int iShow)
{
	WNDCLASSEX wndClass;
	MSG msg;
	HWND hWnd;
	TCHAR szAppName[] = TEXT("MultipleBKColor");

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

	hWnd = CreateWindow(szAppName, TEXT("Multiple Background Color"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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

	switch (msg)
	{
	case WM_CHAR:
		switch (wParam)
		{
		case 'R':
		case 'r':
			iPaintFlag = 1;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case 'G':
		case 'g':
			iPaintFlag = 2;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case 'B':
		case 'b':
			iPaintFlag = 3;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case 'C':
		case 'c':
			iPaintFlag = 4;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case 'M':
		case 'm':
			iPaintFlag = 5;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case 'Y':
		case 'y':
			iPaintFlag = 6;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case 'W':
		case 'w':
			iPaintFlag = 7;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case 'K':
		case 'k':
			iPaintFlag = 0;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		default:
			iPaintFlag = -1;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		}
		break;

	case WM_PAINT:
		GetClientRect(hWnd, &rc);
		hdc = BeginPaint(hWnd, &ps);
		switch (iPaintFlag)
		{
		case 0:
			hBrush = CreateSolidBrush(RGB(0,0,0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 7:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		default:
			break;
		}
	
		EndPaint(hWnd, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}