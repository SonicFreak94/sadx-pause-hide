#include <SADXModLoader.h>
#include "PauseOptions.h"

extern "C"
{
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };

	PointerInfo jumps[] = {
		{ (void*)0x004582E0, SetPauseDisplayOptions }
	};

	__declspec(dllexport) PointerList Jumps[] = { { arrayptrandlength(jumps) } };
}