#include "BHD_Asi.h"

BHD_Hacks* mainHack;

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

		auto pathCheck = std::regex(".+\\\\(dfbhd.exe|dfbhdlc.exe|dfbhd.exe.unpacked.exe)", std::regex_constants::icase);
		if (std::regex_match(baseModuleName, pathCheck))
		{
			mainHack = new BHD_Hacks();
			mainHack->Hook();
		}
	}
	return TRUE;
}


