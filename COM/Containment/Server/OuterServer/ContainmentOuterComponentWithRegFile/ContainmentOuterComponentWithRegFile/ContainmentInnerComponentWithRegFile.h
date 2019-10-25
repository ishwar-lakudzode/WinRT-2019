#pragma once
#include<Windows.h>

class IMultiplication :public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision :public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

//CLSID of MultiplicationDivision component
// {8D3B800D-202A-42C0-9EC4-E6C207F7ACFD}
const CLSID CLSID_MultiplicationDivision = { 0x8d3b800d, 0x202a, 0x42c0, 0x9e, 0xc4, 0xe6, 0xc2, 0x7, 0xf7, 0xac, 0xfd};

//IID of IMultiplication Interface
// {CC5024FB-6EE5-4265-8FEF-5FED6ED7B90C}
const IID IID_Multiplication = { 0xcc5024fb, 0x6ee5, 0x4265, 0x8f, 0xef, 0x5f, 0xed, 0x6e, 0xd7, 0xb9, 0xc};

//IID of IDivision Interface
// {D1E8FA11-B37E-4FA1-827E-F54AEEAE5006}
const IID IID_Division = { 0xd1e8fa11, 0xb37e, 0x4fa1, 0x82, 0x7e, 0xf5, 0x4a, 0xee, 0xae, 0x50, 0x6};