#pragma once
#include <Windows.h>
struct RenderWin32Platform
{
	int recHeight;
	int recWidth;
	void* memory;
	BITMAPINFO bmi;
};