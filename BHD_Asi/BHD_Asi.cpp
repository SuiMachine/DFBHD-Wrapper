#include <Windows.h>
#include "HookFunctions.h"
#include "BHD_Hacks.h"
#include <detours.h>

BHD_Hacks* mainHack;


static HWND(_stdcall* TrueCreateWindowExA)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName,	DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,	HINSTANCE hInstance, LPVOID lpParam) = CreateWindowExA;
HWND _stdcall DetourCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	if (mainHack != NULL)
	{
		mainHack->Hook();
	}
	auto library = TrueCreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

	return library;
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		HMODULE baseModule = GetModuleHandle(NULL);
		char baseModuleName[MAX_PATH];
		GetModuleFileName(baseModule, baseModuleName, sizeof(baseModuleName));
		int indexOfLastPathNode = StrEndsWith(baseModuleName, sizeof(baseModuleName), '\\') + 1;
		char exeName[MAX_PATH];
		strcpy_s(exeName, baseModuleName + indexOfLastPathNode);
		StrToLower(exeName, sizeof(exeName));

		if (std::strstr((const char*)& exeName, "dfbhd.exe"))
		{
			mainHack = new BHD_Hacks();
		}

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)TrueCreateWindowExA, DetourCreateWindowExA);
		DetourTransactionCommit();

	}
	else if (reason == DLL_PROCESS_DETACH) {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)TrueCreateWindowExA, DetourCreateWindowExA);
		DetourTransactionCommit();
	}
	return TRUE;
}


