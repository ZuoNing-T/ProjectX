#include "../../Utility/Pattern.h"
#include "../../../SDK/inc/types.h"

namespace patched
{
	static uint32_t*(*trigger_script_event)(int eventGroup, Any* args, int argCount, int bit) = "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 45 8B F0 41 8B F9"_Scan.as<decltype(trigger_script_event)>();
	static uint32_t*(*get_event_data)(int eventGroup, int eventIndex, int* argStruct, int argStructSize) = " 48 89 5C 24 ? 57 48 83 EC 20 49 8B F8 4C 8D 05 ? ? ? ?"_Scan.as<decltype(get_event_data)>(); //Get event data
	static uint32_t*(*STAT_SET_INT)(Hash statName, int value, BOOL save) = " 48 89 5C 24 ? 48 89 74 24 ? 89 54 24 10 55 57 41 57"_Scan.as<decltype(STAT_SET_INT)>();
	static uint32_t*(*STAT_SET_FLOAT)(Hash statName, float value, BOOL save) = " 48 89 5C 24 ? F3 0F 11 4C 24 ? 57 48 83 EC 40"_Scan.as<decltype(STAT_SET_FLOAT)>();
	static uint32_t*(*STAT_SET_BOOL)(Hash statName, bool value, BOOL save) = " 48 89 5C 24 ? 88 54 24 10 57 48 83 EC 40"_Scan.as<decltype(STAT_SET_BOOL)>();
	static uint32_t*(*GET_PED_LAST_WEAPON_IMPACT_COORD)(Ped ped, Vector3* coords) = "4C 63 0A 48 8B 41 10"_Scan.as<decltype(GET_PED_LAST_WEAPON_IMPACT_COORD)>();
	static Player(*PLAYER_ID)() = "E9 ? ? ? ? 58 5B C3 E9 ? ? ? ? 33"_Scan.as<decltype(PLAYER_ID)>();
}