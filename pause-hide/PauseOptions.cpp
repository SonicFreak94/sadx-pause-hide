#include <SADXModLoader.h>
#include "PauseOptions.h"

FunctionPointer(int, GetCameraThing, (void), 0x004348E0);
FunctionPointer(bool, LevelHasMap, (void), 0x00458720);

char __cdecl SetPauseDisplayOptions(uint8_t* a1)
{
	if ((ControllerPointers[0]->HeldButtons & (Buttons_X | Buttons_Y)) == (Buttons_X | Buttons_Y))
	{
		*a1 = 0;
		return 0;
	}

	uint8_t options = PauseOptions_Quit | PauseOptions_Controls | PauseOptions_Continue;
	uint8_t count = 3;
	
	// If not Chao Garden
	if (GetCameraThing() && CurrentLevel < (signed int)LevelIDs_SSGarden)
	{
		options = PauseOptions_Camera | PauseOptions_Quit | PauseOptions_Controls | PauseOptions_Continue;
		count = 4;
	}
	
	// If in Action Stage
	if ((CurrentLevel < (signed int)LevelIDs_StationSquare || CurrentLevel >(signed int)LevelIDs_Past)
		&& (CurrentLevel < (signed int)LevelIDs_SSGarden || CurrentLevel >(signed int)LevelIDs_MRGarden)
		&& Lives > 0)
	{
		options |= PauseOptions_Restart;
		++count;
	}

	// If the current stage has a map
	if (LevelHasMap())
	{
		options |= PauseOptions_Map;
		++count;
	}

	// Pretty straight forward
	if (GameMode == GameModes_Mission)
	{
		options |= PauseOptions_Missions;
		++count;
	}

	*a1 = options;
	return count;
}