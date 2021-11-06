#include "BHD_Hacks.h"
#include "../externals/inireader/IniReader.h"

DWORD returnIncreaseFOVAddy;

float fovMultiplier;
__declspec(naked) void IncreaseFOV()
{
	__asm
	{
		mov eax, [eax + 0x3C]
		mov [ebx + 0x3C], eax
		fild word ptr ss:[ebx + 0x3E]
		fmul [fovMultiplier]
		fistp word ptr ss:[ebx + 0x3E]
		jmp returnIncreaseFOVAddy
	}
}


BHD_Hacks::BHD_Hacks()
{
	CIniReader iniReader = CIniReader("");
	this->Settings = new settingsOverrideStr();
	this->Settings->Width = iniReader.ReadInteger("MAIN", "Width", 1920);
	this->Settings->Height = iniReader.ReadInteger("MAIN", "Height", 1080);

	this->Settings->FOV = iniReader.ReadFloat("MAIN", "FOV", 80);
	this->Settings->FOV = GetHorPlusFOV((float)this->Settings->FOV, this->Settings->Width * 1.0f / this->Settings->Height);
	fovMultiplier = this->Settings->FOV / 80.0f;

}

void BHD_Hacks::Hook()
{
	HMODULE baseModule = GetModuleHandle(NULL);
	UnprotectModule(baseModule);
	*(int*)(((DWORD)baseModule) + 0x6AA74) = this->Settings->Width;
	*(int*)(((DWORD)baseModule) + 0x6AA79) = this->Settings->Height;
	HookInsideFunction((DWORD)baseModule + 0x0001836C, IncreaseFOV, &returnIncreaseFOVAddy, 0x6);
}
