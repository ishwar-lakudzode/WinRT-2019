#pragma once
#include<Windows.h>
class ISum :public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubstract :public IUnknown
{
public:
	virtual HRESULT __stdcall SubstractionOfTwoIntegere(int, int, int*) = 0;
};

// {A154A38C-E2E4-4E68-985F-E199EE463121}
const CLSID CLSSID_SumSubstract =
{ 0xa154a38c, 0xe2e4, 0x4e68, 0x98, 0x5f, 0xe1, 0x99, 0xee, 0x46, 0x31, 0x21 };

// {ACA0BEFC-9DCF-4C4D-9100-E2BBBB66FD19}
const IID IID_ISum =
{ 0xaca0befc, 0x9dcf, 0x4c4d, 0x91, 0x0, 0xe2, 0xbb, 0xbb, 0x66, 0xfd, 0x19 };

// {6D1E0334-504D-4C8B-B6E1-6277A7D442F0}
const IID IID_ISubstract =
{ 0x6d1e0334, 0x504d, 0x4c8b, 0xb6, 0xe1, 0x62, 0x77, 0xa7, 0xd4, 0x42, 0xf0 };