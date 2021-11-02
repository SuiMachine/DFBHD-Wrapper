#include "BHD_Hacks.h"
#include "../externals/inireader/IniReader.h"



BHD_Hacks::BHD_Hacks()
{
	CIniReader iniReader = CIniReader("");
	this->Settings = new settingsOverrideStr();
	this->Settings->Width = iniReader.ReadInteger("MAIN", "Width", 1920);
	this->Settings->Height = iniReader.ReadInteger("MAIN", "Height", 1080);

	//MessageBox(NULL, iniReader.GetIniPath().c_str(), "Test", 0);

	this->Settings->FOV = iniReader.ReadInteger("MAIN", "FOV", 80);
	this->Settings->FOV = (int)GetHorPlusFOV((float)this->Settings->FOV, this->Settings->Width * 1.0f / this->Settings->Height);
}

void BHD_Hacks::Hook()
{
	HMODULE baseModule = GetModuleHandle(NULL);
	UnprotectModule(baseModule);
	*(int*)(((DWORD)baseModule) + 0x6AA74) = this->Settings->Width;
	*(int*)(((DWORD)baseModule) + 0x6AA79) = this->Settings->Height;
	*(byte*)((DWORD)baseModule + 0xF44AD + 0x8) = this->Settings->FOV;
}
