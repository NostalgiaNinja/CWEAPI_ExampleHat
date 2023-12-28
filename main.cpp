#include "pch.h"
#include "cwe_api.h"
#include "ModelInfo.h"

extern "C"
{
	//registering data functions.
	void (*RegisterDataFunc)(void* ptr);

	//NJS Type texture name and texture list. As is for old documentation.
	NJS_TEXNAME ExampleTex[10];
	NJS_TEXLIST example_texlist = { arrayptrandlength(ExampleTex) };

	//Define models
	ModelInfo* MDLExampleHat;

	//create a UID for your accessory
	int ExampleAccessoryID;

	//Black Market Item Attributes
	BlackMarketItemAttributes BMExampleHat = { 1000, 500, 0, -1, -1, 0 };

	void CWELoad(CWE_REGAPI* cwe_api)
	{
		//register your textures here (by filename.pak)
		cwe_api->RegisterChaoTexlistLoad("ExampleTex", &example_texlist);
		//register your hat here
		cwe_api->AddChaoHat(MDLExampleHat->getmodel(), &example_texlist, &BMExampleHat, "Example Hat", "Example Hat Description");
		
	}

	__declspec(dllexport) void Init(const char* path)
	{
		HMODULE h = GetModuleHandle(L"CWE");

		std::string pathStr = std::string(path) + "\\";

		//Tell what models need to be associated to their variables here.
		MDLExampleHat = new ModelInfo(pathStr + "ExampleHat.sa2mdl");

		RegisterDataFunc = (void (*)(void* ptr))GetProcAddress(h, "RegisterDataFunc");
		RegisterDataFunc(CWELoad);
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}