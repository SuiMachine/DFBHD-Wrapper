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

		auto pathCheck = std::regex(".+\\\\(dfbhd.exe|dfbhdlc.exe|dfbhd.exe.unpacked.exe|dfbhdts.exe)", std::regex_constants::icase);
		
		bool tryAndHook = false;
		if (std::regex_match(baseModuleName, pathCheck))
			tryAndHook = true;
		else
		{
			if (MessageBox(NULL, "You may be trying to load an ASI file with invalid exe. Are you sure, you want to continue?", "Warning", MB_ICONWARNING | MB_YESNO) == IDYES)
				tryAndHook = true;
			else
				tryAndHook = false;
		}

		if (!tryAndHook)
			return TRUE;

		MODULEINFO moduleInfo = { 0 };
		GetModuleInformation(GetCurrentProcess(), baseModule, &moduleInfo, sizeof(moduleInfo));

		switch (moduleInfo.SizeOfImage)
		{
		case 12001280:
		case 12353536:
			mainHack = new BHD_Hacks();
			mainHack->Hook();
			break;
		default:

			char buffer[255];
			sprintf_s(buffer, 255, "Unknown module size %d! Do you still want to hook into it?", moduleInfo.SizeOfImage);
			if (MessageBox(NULL, buffer, "Error", MB_YESNO | MB_ICONWARNING) == IDYES)
			{
				mainHack = new BHD_Hacks();
				mainHack->Hook();
			}

			break;
		}
	}
	return TRUE;
}


