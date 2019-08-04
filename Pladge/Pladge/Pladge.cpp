#include<Windows.h>
#include<tchar.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR csCmd, int iShow)
{
	WNDCLASSEX wndClass;
	MSG msg;
	HWND hWnd;
	TCHAR szAppName[] = TEXT("Pladge");

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

	hWnd = CreateWindow(szAppName, TEXT("Pladge"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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

	switch (msg)
	{
	case WM_PAINT:
		GetClientRect(hWnd, &rc);
		hdc = BeginPaint(hWnd, &ps);
		SetTextColor(hdc, RGB(255, 128, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		wsprintf(str, TEXT("India is my country"));
		TextOut(hdc, 10, 10, str, _tcslen(str));
		wsprintf(str, TEXT("and all Indians are my brothers and sisters."));
		TextOut(hdc, 10, 30, str, _tcslen(str));
		wsprintf(str, TEXT("I love my country"));
		TextOut(hdc, 10, 60, str, _tcslen(str));
		wsprintf(str, TEXT("and I am proud of its rich and varied heritage"));
		TextOut(hdc, 10, 90, str, _tcslen(str));

		SetTextColor(hdc, RGB(255, 255, 255));
		wsprintf(str, TEXT("I shall always strive to be worthy of it."));
		TextOut(hdc, 10, 120, str, _tcslen(str));
		wsprintf(str, TEXT("I shall give respect to my parents,"));
		TextOut(hdc, 10, 150, str, _tcslen(str));
		wsprintf(str, TEXT("teachers and elders"));
		TextOut(hdc, 10, 180, str, _tcslen(str));
		wsprintf(str, TEXT("and treat everyone with courtesy."));
		TextOut(hdc, 10, 210, str, _tcslen(str));

		SetTextColor(hdc, RGB(0, 255, 0));
		wsprintf(str, TEXT("To my country and my people,"));
		TextOut(hdc, 10, 240, str, _tcslen(str));
		wsprintf(str, TEXT("I pledge my devotion."));
		TextOut(hdc, 10, 270, str, _tcslen(str));
		wsprintf(str, TEXT("In their well being and prosperity alone, lies my happiness."));
		TextOut(hdc, 10, 300, str, _tcslen(str));
		wsprintf(str, TEXT("Jai Hind!"));
		TextOut(hdc, 10, 330, str, _tcslen(str));

		EndPaint(hWnd, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}