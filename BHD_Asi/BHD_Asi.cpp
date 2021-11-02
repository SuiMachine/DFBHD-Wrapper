#include "BHD_Asi.h"

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
#if _DEBUG
		//MessageBox(NULL, "Stop", "Stop", 0);
#endif
		HMODULE baseModule = GetModuleHandle(NULL);
		char baseModuleName[MAX_PATH];
		GetModuleFileName(baseModule, baseModuleName, sizeof(baseModuleName));

		auto pathCheck = std::regex(".+\\\\(dfbhd.exe|dfbhdlc.exe)", std::regex_constants::icase);
		if (std::regex_match(baseModuleName, pathCheck))
		{
			MessageBox(NULL, "About to...", "Test", 0);
			mainHack = new BHD_Hacks();
			mainHack->Hook();
		}
	}
	return TRUE;
}


