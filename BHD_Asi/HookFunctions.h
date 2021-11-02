#pragma once
#include <Windows.h>
#include <math.h>

static void UnprotectModule(HMODULE p_Module)
{
	//This function was provided by Orfeasz
	PIMAGE_DOS_HEADER s_Header = (PIMAGE_DOS_HEADER)p_Module;
	PIMAGE_NT_HEADERS s_NTHeader = (PIMAGE_NT_HEADERS)((DWORD)p_Module + s_Header->e_lfanew);

	SIZE_T s_ImageSize = s_NTHeader->OptionalHeader.SizeOfImage;

	DWORD s_OldProtect;
	VirtualProtect((LPVOID)p_Module, s_ImageSize, PAGE_EXECUTE_READWRITE, &s_OldProtect);
}

static float GetHorPlusFOV(float OriginalFOV, float AspectRatio)
{
	float PI = 3.14f;
	return (2 * atanf(tanf((2 * atanf(tanf((PI * OriginalFOV / 180.0f) / 2) * 0.75f)) / 2) * AspectRatio) * (180.0f / PI));
}