#pragma once
#include <set>
#include <tuple>
#include <string>
#include <vector>
#include "../../../SDK/inc/types.h"
#include "VehHash.h"
enum VehType
{
	Arena,
	Afterhours,
	Gunrunning,
	DLC,
	Boats,
	Commercial,
	Compacts,
	Coupes,
	Cycles,
	Emergency,
	Helicopters,
	Industrial,
	Military,
	Motorcycles,
	Muscle,
	OffRoad,
	Planes,
	Sedans,
	Service,
	Sports,
	SportsClassics,
	Super,
	SUVs,
	Trailer,
	Trains,
	Utilitys,
	Vans,
	FavVehicles,
};
enum Mods_Veh
{
	ini,
	xml,
	json,
	unknown
};
void update_veh_menu();
void update_veh_game();
void SpawnVehicle(std::string model);