#pragma once
#include "HookFunctions.h"
#include <Windows.h>
#include <string>

class BHD_Hacks
{
	struct settingsOverrideStr
	{
		int Width;
		int Height;
		float FOV;
	};

public:
	BHD_Hacks();
	void Hook();
	settingsOverrideStr* Settings;
};

