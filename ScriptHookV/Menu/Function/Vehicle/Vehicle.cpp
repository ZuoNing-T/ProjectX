#include "../../internal_native.h"
#include "Vehicle.h"
#include "../Function.h"
#include "Veh_Setting.h"
#include "VehHash.h"
#include "../../ScriptHookV.h"
#include "../../MenuBase/menu.h"
#include "../../MenuBase/menuutils.h"
#include "../../Menu/UI/Script.h"
#include "../keyboard.h"
#include "Mods.h"

extern NativeMenu::Menu menu;
extern NativeMenu::MenuControls concontrols;
extern std::string settingsMenuFile;
extern Veh_Settings settings;
std::vector<std::string> IniPath;
std::vector<std::string>XmlPath;
std::vector<std::string> JsonPath;
VehType Vcat;
NativeMenu::Color VehPrmCol = { 0,200,0,0 };
NativeMenu::Color VehSecCol = { 0,200,0,0 };
Vehicle pre_veh;


void SpawnVehicle(std::string model)
{
	Hash hash = $(model);
	Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
	float forward = 5.f;
	float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
	float xVector = forward * sin(degToRad(heading)) * -1.f;
	float yVector = forward * cos(degToRad(heading));

	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_A_VEHICLE(hash))
	{
		STREAMING::REQUEST_MODEL(hash);
	}
	DWORD startTime = GetTickCount();
	DWORD timeout = 3000; // in millis
	while (!STREAMING::HAS_MODEL_LOADED(hash)) {
		WAIT(0);
		if (GetTickCount() > startTime + timeout) {
			showNotification("Couldn't load model");
			WAIT(0);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
			return;
		}
	}
	bool spawnInside = settings.SpawnInside;
	Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, ourCoords.x, ourCoords.y, ourCoords.z, heading, 1, 1);
	if (spawnInside)
	{
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
	}

	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 1, 1);
	DWORD id = NETWORK::NET_TO_VEH(veh);
	NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(id, 1);
	DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
	ENTITY::_SET_ENTITY_SOMETHING(veh, true);

	VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
	ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
	PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
	if (settings.SpawnMaxed)
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		for (int i = 0; i < 50; i++)
		{
			VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false);
		}
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "Project X");
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, VehPrmCol.R, VehPrmCol.G, VehPrmCol.B);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, VehSecCol.R, VehSecCol.G, VehSecCol.B);
	}
	//VEHICLE::SET_VEHICLE_IS_STOLEN(veh, 0);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
}

void fix()
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		VEHICLE::SET_VEHICLE_FIXED(vehicle);
		VEHICLE::SET_VEHICLE_DAMAGE(vehicle, 0.f, 0.f, 0.f, 0.f, 200.f, true);
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(vehicle);
		VEHICLE::SET_VEHICLE_ENVEFF_SCALE(vehicle, 0.f);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.f);
		VEHICLE::SET_VEHICLE_BODY_HEALTH(vehicle, 1000.f);
		VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, 1000.f);
		VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(vehicle, 1000.f);
		if (VEHICLE::_IS_VEHICLE_DAMAGED(vehicle))
		{
			VEHICLE::SET_VEHICLE_FIXED(vehicle);
			for (int i = 0; i < 10; i++)
			{
				try {
					VEHICLE::SET_VEHICLE_TYRE_FIXED(vehicle, i);
				}
				catch (...) {
					return;
				}
			}
		}
	}
}

bool randomcolbool = false;
void randomcol()
{
	int ped = PLAYER::PLAYER_PED_ID();

	if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(ped, 0);
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(VehID, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(VehID, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
	}
}
int VehicleIndexstage2 = 0;
int VehicleIndexstage = 0;
NativeMenu::Color Vehiclecolor;
NativeMenu::Color Vehiclecolor2;
bool RainbowVehicleBool = false;
void RainbowVehicle()
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
	{
		VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), &Vehiclecolor.R, &Vehiclecolor.G, &Vehiclecolor.B);
		VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), &Vehiclecolor2.R, &Vehiclecolor2.G, &Vehiclecolor2.B);
		if (Vehiclecolor.R > 0 && Vehiclecolor.B == 0, Vehiclecolor2.R > 0 && Vehiclecolor2.B == 0)
		{
			Vehiclecolor.R--;
			Vehiclecolor.G++;
			Vehiclecolor2.R--;
			Vehiclecolor2.G++;
		}
		if (Vehiclecolor.G > 0 && Vehiclecolor.R == 0, Vehiclecolor2.G > 0 && Vehiclecolor2.R == 0)
		{
			Vehiclecolor.G--;
			Vehiclecolor.B++;
			Vehiclecolor2.G--;
			Vehiclecolor2.B++;
		}
		if (Vehiclecolor.B > 0 && Vehiclecolor.G == 0, Vehiclecolor2.B > 0 && Vehiclecolor2.G == 0)
		{
			Vehiclecolor.R++;
			Vehiclecolor.B--;
			Vehiclecolor2.R++;
			Vehiclecolor2.B--;
		}
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), Vehiclecolor.R, Vehiclecolor.G, Vehiclecolor.B);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), Vehiclecolor2.R, Vehiclecolor2.G, Vehiclecolor2.B);
	}
}

bool openAllDoors = false;


bool randommodsbool = false;
void randommods()
{
	Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
	for (int i = 0; i < 50; i++)
	{
		VEHICLE::SET_VEHICLE_MOD(vehicle, i, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i)), false);
	}
}

bool hornboostbool = false;
void hornboost()
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
	if (AUDIO::IS_HORN_ACTIVE(veh))
	{
		VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 50.f);
	}
}
bool carjumpbool = false;
void carjump()
{
	if (IsKeyJustUp(VK_SPACE) && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(veh), 0 + ENTITY::GET_ENTITY_FORWARD_Y(veh), 7, 0, 0, 0, 1, 0, 1, 1, 1, 1);
	}
}

bool bulletprooftiresbool = false;
void bulletprooftires()
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, !bulletprooftiresbool);
	}
}



void vehsetting()
{
	addTitle("Spawn Setting");
	menu.BoolOption("spawn Maxupgrade", settings.SpawnMaxed);
	menu.BoolOption("spawn in Vehicle", settings.SpawnInside);



	//menu.BoolOption("replace old vehicle", settings.SpawnInplace);
}
bool carVisible = true;
void vehicle_menu()
{
	addTitle("Vehicle");
	menu.MenuOption("Spawn Setting", "vehsetting");
	menu.MenuOption("spawn Vehicle", "spawnvehicle");
	menu.MenuOption("Mod Vehicles", "ModVehilce");
	menu.MenuOption("Vehicle Mods", "vehupdate");
	if (menu.BoolOption("Open All Doors", openAllDoors))
	{
		if (openAllDoors)
			for (int i = -1; i <= 7; i++)
			{
				VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), i, false, true);
			}
		else
			VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 0);
	}
	if (menu.Option("Fix Vehicle"))fix();
	menu.BoolOption("random upgrade", randommodsbool);
	menu.BoolOption("Horn Boost", hornboostbool);
	menu.BoolOption("Car Jump", carjumpbool);
	menu.BoolOption("Rainbow Vehicle", RainbowVehicleBool);
	menu.BoolOption("Bullet Proof", bulletprooftiresbool);
	if (menu.BoolOption("Visible", carVisible))ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true), carVisible, false);
	if (menu.Option("Flip"))VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));

}

Mods_Veh type;
void ModVehilce()
{
	addTitle("Mod Vehicle");
	if (menu.Option("~HUD_COLOUR_DEGEN_RED~Reloading~"))
	{
		IniPath.clear();
		XmlPath.clear();
		find((char*)(settingsMenuFile + "\\Mod Vehicle\\Ini Mod").c_str(), IniPath);
		find((char*)(settingsMenuFile + "\\Mod Vehicle\\Xml Mod").c_str(), XmlPath);
		LOG_PRINT("Found Ini Files:%zd\t Found Xml File:%zd", IniPath.size(), XmlPath.size());
	}
	if (!IniPath.empty() && menu.MenuOption("Ini Mod", "listMod", {}))
	{
		type = ini;
	}
	if (!XmlPath.empty() && menu.MenuOption("Xml Mod", "listMod", {}))
	{
		type = xml;
	}
	if (!JsonPath.empty() && menu.MenuOption("Xml Mod", "listMod", {}))
	{
		type = json;
	}
	if (XmlPath.empty() && IniPath.empty() && JsonPath.empty())
	{
		menu.Option("I don't found any vehicle");
	}
}

void listMods(Mods_Veh name, std::vector<std::string> list)
{
	switch (name)
	{
	case ini:
		addTitle("INI MODS");
		break;
	case xml:
		addTitle("XML MODS");
		break;
	case json:
		addTitle("JSON MODS");
		break;
	case unknown:
	default:
		addTitle("UNKNOWN MODS");
		break;
	}

	for (int i = 0; i < list.size(); i++)
	{
		if (menu.Option(list[i], {}, false))
		{
			LoadModsVehicle(name, list[i]);
		}
	}
}

int
horns,
Armor_,
Brakes_,
Transmission_,
Bumpers_,
Hoods_,
Suspension_,
Spoilers_,
Skirts_,
Exhaust_,
Grill_,
Interior_,
Tint_ = 0;
bool hasTurbo = false;
void vehupdate()
{
	addTitle("update");
	if (menu.IntOption("Armor", Armor_, 0, 6, 1))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);//this is for armor
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Armor_);
		VEHICLE::SET_VEHICLE_MOD(VehID, 16, Armor_, 0);
	}
	if (menu.IntOption("Brakes", Brakes_, 0, 4))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Brakes_);
		VEHICLE::SET_VEHICLE_MOD(VehID, 12, Brakes_, 0);
	}
	if (menu.IntOption("Transmission", Transmission_, 0, 4))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Transmission_);
		VEHICLE::SET_VEHICLE_MOD(VehID, 13, Transmission_, 0);
	}
	if (menu.IntOption("Bumpers", Bumpers_, 0, 3))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Bumpers_);
		VEHICLE::SET_VEHICLE_MOD(VehID, 2, Bumpers_, 0);
	}
	if (menu.IntOption("Hoods", Hoods_, 0, 5))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Hoods_);
		VEHICLE::SET_VEHICLE_MOD(VehID, 7, Hoods_, 0);
	}
	if (menu.IntOption("Suspension", Suspension_, 0, 5))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Suspension_);
		VEHICLE::SET_VEHICLE_MOD(VehID, 15, Suspension_, 0);
	}
	if (menu.IntOption("Spoiler", Spoilers_, 0, 6))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Spoilers_);
		VEHICLE::SET_VEHICLE_MOD(VehID, 0, Spoilers_, 0);
	}
	if (menu.IntOption("SideSkirts", Skirts_, 0, 6))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Skirts_);
		VEHICLE::SET_VEHICLE_MOD(VehID, 3, Skirts_, 0);
	}
	if (menu.IntOption("Exhaust", Exhaust_, 0, 6))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Exhaust_);
		VEHICLE::SET_VEHICLE_MOD(VehID, 4, Exhaust_, 0);
	}
	if (menu.IntOption("Grill", Grill_, 0, 3))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Grill_);
		VEHICLE::SET_VEHICLE_MOD(VehID, 6, Grill_, 0);
	}
	if (menu.IntOption("Interior", Interior_, 0, 1))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Interior_);
		VEHICLE::REMOVE_VEHICLE_MOD(VehID, Interior_);
	}
	if (menu.IntOption("Window Tint", Tint_, 0, 5))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, Tint_);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(VehID, Tint_);
	}
	if (menu.IntOption("Horns", horns, 1, 32))
	{
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_MOD_KIT(VehID, horns);
		VEHICLE::SET_VEHICLE_MOD(VehID, 14, horns, 0);
	}
	if (menu.Option("Turbo"))
	{
		if (hasTurbo)
		{
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD_KIT(VehID, 0);
			VEHICLE::TOGGLE_VEHICLE_MOD(VehID, 18, 0);
			hasTurbo = false;
		}
		else
		{
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD_KIT(VehID, 0);
			VEHICLE::TOGGLE_VEHICLE_MOD(VehID, 18, 1);
			hasTurbo = true;
		}
	}
}



void spawnvehicle()
{
	addTitle("Vehicle");
	if (menu.MenuOption("~HUD_COLOUR_DEGEN_RED~Arena", "vehiclelist", { "1.46 Only" })) Vcat = Arena;
	if (menu.MenuOption("After Hours", "vehiclelist", { "1.44 Only" })) Vcat = Afterhours;
	if (menu.MenuOption("1.43Vehicle", "vehiclelist", { "1.43 Only" })) Vcat = DLC;
	if (menu.MenuOption("Gunrunning", "vehiclelist", { "1.42 Only" }))Vcat = Gunrunning;
	if (menu.MenuOption("Super", "vehiclelist", { "Supaer Vehicle" })) Vcat = Super;
	if (menu.MenuOption("Sports", "vehiclelist", { "Sports Vehcile" }))Vcat = Sports;
	if (menu.MenuOption("Sport Classic", "vehiclelist", { "Sports Vehcile" }))Vcat = SportsClassics;
	if (menu.MenuOption("Offroad", "vehiclelist", { "Off Road!!!" }))Vcat = OffRoad;
	if (menu.MenuOption("Muscle", "vehiclelist"))Vcat = Muscle;
	if (menu.MenuOption("Planes", "vehiclelist"))Vcat = Planes;
	if (menu.MenuOption("Sedans", "vehiclelist"))Vcat = Sedans;
	if (menu.MenuOption("Service", "vehiclelist"))Vcat = Service;
	if (menu.MenuOption("SUV", "vehiclelist"))Vcat = SUVs;
	if (menu.MenuOption("Trailer", "vehiclelist"))Vcat = Trailer;
	if (menu.MenuOption("Trains", "vehiclelist"))Vcat = Trains;
	if (menu.MenuOption("Utility", "vehiclelist"))Vcat = Utilitys;
	if (menu.MenuOption("Vans", "vehiclelist"))Vcat = Vans;
	if (menu.MenuOption("My Favorite", "vehiclelist"))Vcat = FavVehicles;
}

std::string GetVehTranslation(std::string option)
{
	char *name = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL($(option));
	std::string vehiclename = UI::_GET_LABEL_TEXT(name);
	if (vehiclename != "NULL")
		return vehiclename;
	else
		return option;
}
std::vector<std::string> currentlist;
void vehiclelist(VehType cat)
{
	addTitle("Vehicle List");
	switch (cat)
	{
	case Arena:
		currentlist = v_Arena;
		break;
	case Afterhours:
		currentlist = v_Afterhours;
		break;
	case Gunrunning:
		currentlist = v_Gunrunning;
		break;
	case DLC:
		currentlist = v_DLC;
		break;
	case Boats:
		currentlist = v_Boats;
		break;
	case Commercial:
		currentlist = v_Commercial;
		break;
	case Compacts:
		currentlist = v_Compacts;
		break;
	case Coupes:
		currentlist = v_Coupes;
		break;
	case Cycles:
		currentlist = v_Cycles;
		break;
	case Emergency:
		currentlist = v_Emergency;
		break;
	case Helicopters:
		currentlist = v_Helicopters;
		break;
	case Industrial:
		currentlist = v_Industrial;
		break;
	case Military:
		currentlist = v_Military;
		break;
	case Motorcycles:
		currentlist = v_Motorcycles;
		break;
	case Muscle:
		currentlist = v_Muscle;
		break;
	case OffRoad:
		currentlist = v_OffRoad;
		break;
	case Planes:
		currentlist = v_Planes;
		break;
	case Sedans:
		currentlist = v_Sedans;
		break;
	case Service:
		currentlist = v_Service;
		break;
	case Sports:
		currentlist = v_Sports;
		break;
	case SportsClassics:
		currentlist = v_SportsClassics;
		break;
	case Super:
		currentlist = v_Super;
		break;
	case SUVs:
		currentlist = v_SUVs;
		break;
	case Trailer:
		currentlist = v_Trailer;
		break;
	case Trains:
		currentlist = v_Trains;
		break;
	case Utilitys:
		currentlist = v_Utilitys;
		break;
	case Vans:
		currentlist = v_Vans;
		break;
	case FavVehicles:
		currentlist = v_FavVehicles;
		break;
	default:
		currentlist = v_Afterhours;
		break;
	}
	for (auto id : currentlist)
	{
		if (menu.Option(GetVehTranslation(id), {}, false))
		{
			SpawnVehicle(id);
		}
	}
}



void update_veh_menu()
{
	if (menu.CurrentMenu("vehiclemenu"))vehicle_menu();
	if (menu.CurrentMenu("vehsetting"))vehsetting();
	if (menu.CurrentMenu("spawnvehicle"))spawnvehicle();
	if (menu.CurrentMenu("vehiclelist"))vehiclelist(Vcat);
	if (menu.CurrentMenu("vehupdate"))vehupdate();
	if (menu.CurrentMenu("ModVehilce"))ModVehilce();
}
void update_veh_game()
{
	randomcolbool ? randomcol() : NULL;
	randommodsbool ? randommods() : NULL;
	hornboostbool ? hornboost() : NULL;
	carjumpbool ? carjump() : NULL;
	RainbowVehicleBool ? RainbowVehicle() : NULL;
	bulletprooftiresbool ? bulletprooftires() : NULL;
}