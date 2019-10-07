#include "windows.h"
#include "tchar.h"

#define TimerID 201

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	WNDCLASS WndClass;
	HWND hWnd;
	MSG msg;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = NULL;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = TEXT("MyPaintApp");
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&WndClass))
	{
		MessageBox(NULL, TEXT("Error in Class registration "), TEXT(""), 0);
		return 0;
	}

	hWnd = CreateWindow(TEXT("MyPaintApp"), TEXT("MyPaint App"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static bool bStartDraw = false, bFlag = false;
	static int nKeyState = 0;
	static int iStartX, iStartY, iEndX, iEndY, iXpoint, iYpoint, iKeyVal;
	TCHAR szBuff[255];
	RECT rect;
	RECT rectTemp;
	static int iPaintFlag = -1;
	static int iThresold = 10;
	static RECT RectNew;
	static int iCenterX = 0;
	int iCenterY = 0;
	int iVal = 0;
	static int iRed = 50;
	static int iGreen = 100;
	static int iBlue = 100;
	
	switch (message)
	{
	case WM_SIZE:
		iXpoint = LOWORD(lParam);
		iYpoint = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		swprintf_s(szBuff, TEXT("Window Size : x - %d , y - %d"), iXpoint, iYpoint);
		TextOut(hdc, 10, 10, szBuff, _tcslen(szBuff));
		swprintf_s(szBuff, TEXT("Press Shift+R to draw Rectangle"));
		TextOut(hdc, 10, 30, szBuff, _tcslen(szBuff));
		swprintf_s(szBuff, TEXT("Press Shift+E to draw Ellipse"));
		TextOut(hdc, 10, 50, szBuff, _tcslen(szBuff));
		swprintf_s(szBuff, TEXT("Press Shift+L to draw Line"));
		TextOut(hdc, 10, 70, szBuff, _tcslen(szBuff));
		swprintf_s(szBuff, TEXT("Press Shift+A to Auto Draw"));
		TextOut(hdc, 10, 90, szBuff, _tcslen(szBuff));
		swprintf_s(szBuff, TEXT("Press Shift+C to Clear"));
		TextOut(hdc, 10, 110, szBuff, _tcslen(szBuff));

		if (iKeyVal == 1)
		{
			HPEN hPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));
			SelectObject(hdc, hPen);
			Rectangle(hdc, iStartX, iStartY, iEndX, iEndY);
			DeleteObject(hPen);
		}
		else if (iKeyVal == 2)
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, iStartX, iStartY, iEndX, iEndY);
			DeleteObject(hBrush);
		}
		else if (iKeyVal == 3)
		{
			HPEN hPen = CreatePen(PS_DASHDOTDOT, 1, RGB(255, 0, 0));
			SelectObject(hdc, hPen);
			MoveToEx(hdc, iStartX, iStartY, NULL);
			LineTo(hdc, iEndX, iEndY);

			DeleteObject(hPen);
		}
		else if (iKeyVal == 4)
		{
			GetClientRect(hWnd, &RectNew);
			iCenterX = RectNew.right/2;
			iCenterY = RectNew.bottom;
			HBRUSH hBrush = CreateSolidBrush(RGB(iRed, 0, iThresold));
			SelectObject(hdc, hBrush);
			iStartX = iCenterX - iThresold;
			iStartY = iCenterY - iThresold;
			Ellipse(hdc, iStartX, iStartY, iCenterX + iThresold, iCenterY + iThresold);
			DeleteObject(hBrush);
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:
		nKeyState = GetKeyState(VK_SHIFT);
		if (nKeyState < 0)
		{
			switch (wParam)
			{
			case 82:
				iKeyVal = 1;
				break;
			case 69:
				iKeyVal = 2;
				break;
			case 76:
				iKeyVal = 3;
				break;
			case 65:
				iKeyVal = 4;
				SetTimer(hWnd, TimerID, 50, NULL);
				break;
			case 67:
				iKeyVal = 0;
				GetClientRect(hWnd, &rect);
				InvalidateRect(hWnd, &rect, true);
				break;

			}
		}
		break;
	case WM_LBUTTONDOWN:
		bStartDraw = true;
		bFlag = true;
		break;
	case WM_LBUTTONUP:
		bStartDraw = false;
		bFlag = false;
		break;
	case WM_MOUSEMOVE:

		if (bStartDraw)
		{
			if (bFlag)
			{
				iStartX = LOWORD(lParam);
				iStartY = HIWORD(lParam);
				bFlag = false;
			}

			iEndX = LOWORD(lParam);
			iEndY = HIWORD(lParam);
			GetClientRect(hWnd, &rect);
			InvalidateRect(hWnd, &rect, true);
		}

		break;
	case WM_TIMER:
		KillTimer(hWnd, TimerID);
		iThresold+=10;
		iRed += 30;
		iGreen += 30;
		iBlue += 30;
		iVal = iCenterX + iThresold;
		GetClientRect(hWnd, &rectTemp);
		if (iVal > rectTemp.right)
		{
			iThresold = 10;
			iRed = 50;
			iGreen = 150;
			iBlue = 150;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		SetTimer(hWnd, TimerID, 50, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}