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

// {58E974BE-3CCE-4C19-92F3-014DAB13E7FC}
const CLSID CLSSID_SumSubstract =
{ 0x58e974be, 0x3cce, 0x4c19, 0x92, 0xf3, 0x1, 0x4d, 0xab, 0x13, 0xe7, 0xfc };
// {AFF243CF-B95B-4E3B-9D75-CD8A4F350B41}
const IID IID_ISum =
{ 0xaff243cf, 0xb95b, 0x4e3b, 0x9d, 0x75, 0xcd, 0x8a, 0x4f, 0x35, 0xb, 0x41 };
// {08DD46FB-02FC-4292-99CE-F7E9009C6DF9}
const IID IID_ISubstract =
{ 0x8dd46fb, 0x2fc, 0x4292, 0x99, 0xce, 0xf7, 0xe9, 0x0, 0x9c, 0x6d, 0xf9 };