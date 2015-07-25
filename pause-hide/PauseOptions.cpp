#include <SADXModLoader.h>
#include "PauseOptions.h"

FunctionPointer(int, GetCameraThing, (void), 0x004348E0);
FunctionPointer(bool, LevelHasMap, (void), 0x00458720);

uint8_t hax = PauseOptions_Unknown;

char __cdecl SetPauseDisplayOptions(uint8_t* a1)
{
	uint8_t options;
	uint8_t count;

	if (ControllersRaw[0].HeldButtons & (Buttons_X | Buttons_Y))
	{
		options = 0;
		return 0;
	}
	else
	{
		options = PauseOptions_Quit | PauseOptions_Controls | PauseOptions_Continue;
		count = 3;
	}
	
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