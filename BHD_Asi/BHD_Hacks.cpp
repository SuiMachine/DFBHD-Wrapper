#include "BHD_Hacks.h"
#include "../externals/inireader/IniReader.h"

int og_Value_initializer()
{
	*(int*)0xB63410 = *(int*)0xB6341C;
	*(int*)0xB63440 = *(int*)0xB6344C;
	*(int*)0xB63470 = *(int*)0xB6347C;
	*(int*)0xB634A0 = *(int*)0xB634AC;
	*(int*)0xB634D0 = *(int*)0xB634DC;
	*(int*)0xB63380 = *(int*)0xB6338C;
	*(int*)0xB633B0 = *(int*)0xB633BC;
	*(int*)0xB63500 = *(int*)0xB6350C;
	*(int*)0xB63530 = *(int*)0xB6353C;
	*(int*)0xB633E0 = *(int*)0xB633EC;
	*(int*)0xB63594 = *(int*)0xB6359C;
	*(int*)0xB635A4 = *(int*)0xB63DE0;
	*(int*)0xB63588 = *(int*)0xB63DDC;
	*(int*)0xB635AC = *(int*)0xB63DE4;
	*(int*)0xB635B4 = *(int*)0xB63DE8;
	*(int*)0xB635BC = 0;
	*(int*)0xB635C8 = 0;
	*(int*)0xB635CC = 0;
	*(int*)0xB635C4 = 0;
	*(int*)0xB635C0 = 0;
	*(int*)0xB635D4 = 305345331;
	BHD_Hacks::WriteFOV();
	return 0;
}

void __cdecl og_SomeSaveLoad(const void* a1)
{
	memcpy((byte*)0x00B63320, a1, 2764);
	BHD_Hacks::WriteFOV();
}

BHD_Hacks::SettingsOverrideStr BHD_Hacks::Settings;
BHD_Hacks::BHD_Hacks()
{
	CIniReader iniReader = CIniReader("");
	Settings.Width = iniReader.ReadInteger("MAIN", "Width", 1920);
	Settings.Height = iniReader.ReadInteger("MAIN", "Height", 1080);

	Settings.FOV = iniReader.ReadFloat("MAIN", "FOV", 80);
	Settings.HorPlusFOV = GetHorPlusFOV((float)Settings.FOV, Settings.Width * 1.0f / Settings.Height);
	Settings.FOVMultiplier = Settings.FOV / 80.0f;
}

void BHD_Hacks::Hook()
{
	HMODULE baseModule = GetModuleHandle(NULL);
	UnprotectModule(baseModule);
	*(int*)(((DWORD)baseModule) + 0x6AA74) = Settings.Width;
	*(int*)(((DWORD)baseModule) + 0x6AA79) = Settings.Height;
	HookJmpTrampoline((DWORD)baseModule + 0xF4FF0, og_Value_initializer, 0xCF);
	HookJmpTrampoline((DWORD)baseModule + 0xF6110, og_SomeSaveLoad, 0x17);
}

void BHD_Hacks::WriteFOV()
{
	*(short*)0xB635A6 = (short)Settings.HorPlusFOV;
}
