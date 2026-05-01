#pragma once
#include "HookFunctions.h"
#include <Windows.h>
#include <string>

class BHD_Hacks
{
	struct SettingsOverrideStr
	{
	public:
		int Width;
		int Height;
		float FOV;
		float HorPlusFOV;
		float FOVMultiplier;
	};

public:
	BHD_Hacks();
	void Hook();
	static void WriteFOV();
	static SettingsOverrideStr Settings;
};

