#include<Windows.h>

extern "C" BOOL IsNegative(int iVal);

BOOL WINAPI DLLMain(HINSTANCE dllInst, DWORD dwReason, LPVOID lpReserve)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

	return TRUE;
}

extern "C" int MakeSquare(int iVal)
{
	int iResult = -1;
	if (!IsNegative(iVal))
		iResult = iVal * iVal;
	return iResult;
}

extern "C" BOOL IsNegative(int iVal)
{
	if (iVal < 0)
		return TRUE;
	else
		return FALSE;
}
