#include "../../Scripting/Pools.h"
#include "../../internal_native.h"
#include "../../Menu/UI/Script.h"
#include "../../Function/Animation/Animation.h"
#include "../keyboard.h"


extern int nothing;

#pragma region Vehicles
DWORD	vehUpdateTime;
const int ARR_SIZE = 1024;
bool AllVehRandomColorbool = false;
void AllVehRandomColor()
{
	int count;
	Vehicle Veh[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypeVehicle, ARR_SIZE, Veh);
	for (int i = 0; i < count; i++)
	{
		int primary = 0, secondary = 0;
		VEHICLE::GET_VEHICLE_COLOURS(Veh[i], &primary, &secondary);
		if (rand() % 2)
			VEHICLE::SET_VEHICLE_COLOURS(Veh[i], rand() % (VehicleColorBrushedGold + 1), secondary);
		else
			VEHICLE::SET_VEHICLE_COLOURS(Veh[i], primary, rand() % (VehicleColorBrushedGold + 1));
	}
}

bool AllVehDeletebool = false;
void AllVehDelete()
{
	int count;
	Vehicle vehicles[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypeVehicle, ARR_SIZE, vehicles);
	for (int i = 0; i < count; i++)
	{
		if (!ENTITY::IS_ENTITY_A_MISSION_ENTITY(vehicles[i]))
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicles[i], TRUE, TRUE);
		VEHICLE::DELETE_VEHICLE(&vehicles[i]);
	}
}

float VehSpeed = 30.0f;
void SetAllVehicleSpeed(float speed)
{
	int count;
	Vehicle vehicles[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypeVehicle, ARR_SIZE, vehicles);
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	for (int i = 0; i < count; i++)
		if (vehicles[i] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicles[i], speed);
}

bool AllVehjumpbool = false;
void AllVehicleJump()
{
	int count;
	Vehicle vehicles[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypeVehicle, ARR_SIZE, vehicles);
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	for (int i = 0; i < count; i++)
	{
		if (!ENTITY::IS_ENTITY_IN_AIR(vehicles[i]) && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehicles[i]))
		{
			int bone[4];
			bone[0] = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicles[i], "wheel_lf");
			bone[1] = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicles[i], "wheel_lr");
			bone[2] = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicles[i], "wheel_rf");
			bone[3] = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicles[i], "wheel_rr");
			ENTITY::APPLY_FORCE_TO_ENTITY(vehicles[i], 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(vehicles[i]), 0 + ENTITY::GET_ENTITY_FORWARD_Y(vehicles[i]), 0.587, 0, 0, 0, bone[0], 0, 1, 1, 1, 1);
			ENTITY::APPLY_FORCE_TO_ENTITY(vehicles[i], 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(vehicles[i]), 0 + ENTITY::GET_ENTITY_FORWARD_Y(vehicles[i]), 0.587, 0, 0, 0, bone[1], 0, 1, 1, 1, 1);
			ENTITY::APPLY_FORCE_TO_ENTITY(vehicles[i], 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(vehicles[i]), 0 + ENTITY::GET_ENTITY_FORWARD_Y(vehicles[i]), 0.587, 0, 0, 0, bone[2], 0, 1, 1, 1, 1);
			ENTITY::APPLY_FORCE_TO_ENTITY(vehicles[i], 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(vehicles[i]), 0 + ENTITY::GET_ENTITY_FORWARD_Y(vehicles[i]), 0.587, 0, 0, 0, bone[3], 0, 1, 1, 1, 1);
		}
	}

}

NativeMenu::Color AllVehiclecolor = { 0,0,0,0 };
NativeMenu::Color AllVehiclecolor2 = { 0,0,0,0 };
bool rainbowall = false;
void AllVehRainbowColor()
{
	int count;
	Vehicle Veh[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypeVehicle, ARR_SIZE, Veh);
	for (int i = 0; i < count; i++)
	{
		if (AllVehiclecolor.R > 0 && AllVehiclecolor.B == 0, AllVehiclecolor.R > 0 && AllVehiclecolor2.B == 0)
		{
			AllVehiclecolor.R--;
			AllVehiclecolor.G++;
			AllVehiclecolor2.R--;
			AllVehiclecolor2.G++;
		}
		if (AllVehiclecolor.G > 0 && AllVehiclecolor.R == 0, AllVehiclecolor2.G > 0 && AllVehiclecolor2.R == 0)
		{

			AllVehiclecolor.G--;
			AllVehiclecolor.B++;
			AllVehiclecolor2.G--;
			AllVehiclecolor2.B++;
		}
		if (AllVehiclecolor.B > 0 && AllVehiclecolor.G == 0, AllVehiclecolor2.B > 0 && AllVehiclecolor2.G == 0)
		{
			AllVehiclecolor.R++;
			AllVehiclecolor.B--;
			AllVehiclecolor2.R++;
			AllVehiclecolor2.B--;
		}
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Veh[i], AllVehiclecolor.R, AllVehiclecolor.G, AllVehiclecolor.B);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Veh[i], AllVehiclecolor2.R, AllVehiclecolor2.G, AllVehiclecolor2.B);
	}
}
std::string PlateText = "ProejctX";
void SetVehIndex(std::string name)
{
	int count;
	Vehicle objects[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypeVehicle, ARR_SIZE, objects);
	for (int i = 0; i < count; i++)
	{

		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(objects[i], (char*)name.c_str());
	}
	//VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT
}

void AllVehAlarm()
{
	int count;
	Vehicle veh[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypeVehicle, ARR_SIZE, veh);
	for (int i = 0; i < count; i++)
	{

		VEHICLE::SET_VEHICLE_ALARM(veh[i], true);
		VEHICLE::START_VEHICLE_ALARM(veh[i]);
	}
}

float dirtylevl = 0.0f;
void AllVehDirty(float level)
{
	int count;
	Vehicle veh[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypeVehicle, ARR_SIZE, veh);
	for (int i = 0; i < count; i++)
	{

		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh[i], level);
	}

}

bool Allvehburnoutbool = false;
void Allvehburnout()
{
	int count;
	Vehicle veh[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypeVehicle, ARR_SIZE, veh);
	for (int i = 0; i < count; i++)
	{

		VEHICLE::SET_VEHICLE_BURNOUT(veh[i], Allvehburnoutbool);
	}
}

float limitSpeed = 0.0f;
void speedLimited(float speed)
{
	int count;
	Vehicle veh[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypeVehicle, ARR_SIZE, veh);
	for (int i = 0; i < count; i++)
	{

		ENTITY::SET_ENTITY_MAX_SPEED(veh[i], speed);
	}
	//SET_ENTITY_MAX_SPEED
}

#pragma endregion
#pragma region Peds
void StopAllAnimation()
{
	int count;
	Ped objects[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypePed, ARR_SIZE, objects);
	for (int i = 0; i < count; i++)
	{
		RequestControlOfEnt(objects[i]);
		if (objects[i] != PLAYER::PLAYER_PED_ID())
			AI::CLEAR_PED_TASKS_IMMEDIATELY(objects[i]);
	}
}
void ForceAnimation(std::string Scenarios)
{
	int count;
	Ped objects[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypePed, ARR_SIZE, objects);
	for (int i = 0; i < count; i++)
	{
		if (objects[i] != PLAYER::PLAYER_PED_ID())
		{
			RequestControlOfEnt(objects[i]);
			AI::CLEAR_PED_TASKS_IMMEDIATELY(objects[i]);
			AI::TASK_START_SCENARIO_IN_PLACE(objects[i], (char*)Scenarios.c_str(), 0, false);//Try this
		}
	}
}
bool setPedjumpbool = false;
void SetPedJump()
{
	int count;
	Vehicle vehicles[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypePed, ARR_SIZE, vehicles);
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	for (int i = 0; i < count; i++)
	{
		if (!ENTITY::IS_ENTITY_IN_AIR(vehicles[i]) && playerPed != vehicles[i])
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(vehicles[i], 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(vehicles[i]), 0 + ENTITY::GET_ENTITY_FORWARD_Y(vehicles[i]), 3, 0, 0, 0, 1, 0, 1, 1, 1, 1);
		}
	}
}
float heading = 0.0f;
void setPedDesireHeading(float heading)
{
	int count;
	Ped Peds[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypePed, ARR_SIZE, Peds);
	for (int i = 0; i < count; i++)
	{
		PED::SET_PED_DESIRED_HEADING(Peds[i], heading);
	}
}

bool handcuff = false;
void SetPedhandcuff()
{
	int count;
	Ped Peds[ARR_SIZE];
	count = rage::GetAllWorld(PoolTypePed, ARR_SIZE, Peds);
	for (int i = 0; i < count; i++)
	{
		PED::SET_ENABLE_HANDCUFFS(Peds[i], handcuff);
	}
}
#pragma endregion




std::string plate;
int ScenPos;

void AllPeds()
{
	addTitle("All Peds");
	if (
		menu.StringArray("Animation", Scenarios, ScenPos, { "Press * to recovery" })
		)
	{
		if (TogglePress())
		{
			ForceAnimation(Scenarios[ScenPos]);
		}

		if (IsKeyDown(str2key("*")))
		{
			StopAllAnimation();
		}
	}
	menu.BoolOption("All Jump", setPedjumpbool);
	if (menu.FloatOption("DESIRED Heading", heading,0.0f,360.f))setPedDesireHeading(heading);
	if (menu.BoolOption("Hand Cuffed", handcuff))SetPedhandcuff();

}

void AllVehicles()
{
	addTitle("Vehicles");
	menu.BoolOption("Rainbow Vehicle", rainbowall);
	menu.BoolOption("Random Vehicle Color", AllVehRandomColorbool);
	menu.BoolOption("Delete All", AllVehDeletebool);
	menu.BoolOption("Jump All", AllVehjumpbool);
	if (menu.BoolOption("Burn Out", Allvehburnoutbool))Allvehburnout();
	if (menu.FloatOption("Set Vehicle Speed", VehSpeed, 0.0f, 200.0f))
	{
			SetAllVehicleSpeed(VehSpeed);
	}
	if (menu.StringArray("Vehicle Plate", { PlateText }, nothing))
	{
		PlateText = show_keyboard();
		SetVehIndex(PlateText);
	}
	if (menu.Option("Alarm"))AllVehAlarm();
	if (menu.FloatOption("Dirty Level", dirtylevl, 0.0f, 1.0f))
	{
		AllVehDirty(dirtylevl);
	}
	if (menu.FloatOption("Speed Limit", limitSpeed, 0.0f, 1000.0f))speedLimited(limitSpeed);


}
void PoolsMenu()
{
	addTitle("All Objects");
	menu.MenuOption("All Vehicles", "AllVehicles");
	menu.MenuOption("All Peds", "AllPeds");
}

void update_Pool_menu()
{
	if (menu.CurrentMenu("PoolsMenu"))PoolsMenu();
	if (menu.CurrentMenu("AllVehicles"))AllVehicles();
	if (menu.CurrentMenu("AllPeds"))AllPeds();
}

void update_Pool_game()
{
	rainbowall ? AllVehRainbowColor() : NULL;
	AllVehRandomColorbool ? AllVehRandomColor() : NULL;
	AllVehDeletebool ? AllVehDelete() : NULL;
	AllVehjumpbool ? AllVehicleJump() : NULL;
	setPedjumpbool ? SetPedJump() : NULL;
	handcuff ? SetPedhandcuff() : NULL;

}