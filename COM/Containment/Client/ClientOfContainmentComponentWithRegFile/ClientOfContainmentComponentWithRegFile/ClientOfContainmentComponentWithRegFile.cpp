#include<Windows.h>
#include "HeaderForClientOfContainmentComponentWithRegFile.h"

ISum* pISum = NULL;
ISubstract* pISubstract = NULL;
IMultiplication* pIMultiplication = NULL;
IDivision* pIDivision = NULL;

void SafeInterfaceRelease(void);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR csCmd, int iShow)
{
	WNDCLASSEX wndClass;
	MSG msg;
	HWND hWnd;
	TCHAR szAppName[] = TEXT("ComClient");
	HRESULT hr;
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library can not be initialized. Program will exit now."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

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

	hWnd = CreateWindow(szAppName, TEXT("COM Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	UpdateWindow(hWnd);
	ShowWindow(hWnd, iShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CoUninitialize();
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HRESULT hr;

	int iNum1, iNum2, iSum, iSub, iMul, iDiv;
	TCHAR str[255];
	switch (msg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSSID_SumSubstract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)& pISum);
		if (FAILED(hr))
		{
			MessageBox(hWnd, TEXT("ISum interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hWnd);
			break;
		}
		iNum1 = 30;
		iNum2 = 40;
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		//Display result
		wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, iSum);
		MessageBox(hWnd, str, TEXT("Result"), MB_OK);
		hr = pISum->QueryInterface(IID_ISubstract, (void**)& pISubstract);
		if (FAILED(hr))
		{
			MessageBox(hWnd, TEXT("ISubtract interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hWnd);
		}
		pISum->Release();
		pISum = NULL;

		iNum1 = 145;
		iNum2 = 40;
		pISubstract->SubstractionOfTwoIntegere(iNum1, iNum2, &iSub);

		//Display result
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), iNum1, iNum2, iSub);
		MessageBox(hWnd, str, TEXT("Result"), MB_OK);

		hr = pISubstract->QueryInterface(IID_Multiplication, (void**)& pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hWnd, TEXT("IMultiplication interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hWnd);
		}

		pISubstract->Release();
		pISubstract = NULL;

		iNum1 = 125;
		iNum2 = 25;
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMul);

		//Display result
		wsprintf(str, TEXT("Multiplication of %d and %d is %d"), iNum1, iNum2, iMul);
		MessageBox(hWnd, str, TEXT("Result"), MB_OK);

		hr = pIMultiplication->QueryInterface(IID_Division, (void**)& pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hWnd, TEXT("IDivision interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hWnd);
		}

		pIMultiplication->Release();
		pIMultiplication = NULL;

		iNum1 = 125;
		iNum2 = 25;
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDiv);

		//Display result
		wsprintf(str, TEXT("Division of %d and %d is %d"), iNum1, iNum2, iDiv);
		MessageBox(hWnd, str, TEXT("Result"), MB_OK);
		pIDivision->Release();
		pIDivision = NULL;

		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void SafeInterfaceRelease(void)
{
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubstract)
	{
		pISubstract->Release();
		pISubstract = NULL;
	}
	if (pIMultiplication)
	{
		pIMultiplication->Release();
		pIMultiplication = NULL;
	}
	if (pIDivision)
	{
		pIDivision->Release();
		pIDivision = NULL;
	}
}