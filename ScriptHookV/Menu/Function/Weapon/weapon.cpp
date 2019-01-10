#include "../../internal_native.h"
#include "weapon.h"
#include "../Function.h"
#include "../Vehicle/VehHash.h"
#include "../../ScriptHookV.h"
#include "../../MenuBase/menu.h"
#include "../../MenuBase/menuutils.h"
#include "../../Menu/UI/Script.h"
#include "../keyboard.h"



bool Gravity = false;
void GravityGun()
{
	Entity EntityTarget;
	DWORD equippedWeapon;
	WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &equippedWeapon, 1);
	
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 dir = rot_to_direction(&rot);
	Vector3 camPosition = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	float spawnDistance = get_distance(&camPosition, &playerPosition);
	spawnDistance += 5;
	Vector3 spawnPosition = (camPosition + (dir* spawnDistance));


	Player tempPed = PLAYER::PLAYER_ID();
	if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget) && GetAsyncKeyState(VK_RBUTTON))
	{
		Vector3 EntityTargetPos = ENTITY::GET_ENTITY_COORDS(EntityTarget, 0);
		PLAYER::DISABLE_PLAYER_FIRING(tempPed, true);
		if (ENTITY::IS_ENTITY_A_PED(EntityTarget) && PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1))
		{
			EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
		}

		RequestControl(EntityTarget);

		if (ENTITY::IS_ENTITY_A_VEHICLE(EntityTarget)) ENTITY::SET_ENTITY_HEADING(EntityTarget, ENTITY::GET_ENTITY_HEADING(tempPed));

		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(EntityTarget, spawnPosition.x, spawnPosition.y, spawnPosition.z, 0, 0, 0);

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "Foot_Swish", EntityTarget, "docks_heist_finale_2a_sounds", 0, 0);
			ENTITY::SET_ENTITY_HEADING(EntityTarget, ENTITY::GET_ENTITY_HEADING(tempPed));
			ENTITY::APPLY_FORCE_TO_ENTITY(EntityTarget, 1, dir.x * 10000.0f, dir.y * 10000.0f, dir.z * 10000.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
			//Gravity = false;
			PLAYER::DISABLE_PLAYER_FIRING(tempPed, false);
		}
	}
	if (!PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
	{
		//Gravity = true;
		PLAYER::DISABLE_PLAYER_FIRING(tempPed, false);
	}

}

bool infammobool = false;
void infammo()
{
	for (auto id : weaponNames)
	{
		WEAPON::SET_PED_INFINITE_AMMO(PLAYER::PLAYER_PED_ID(), infammobool, $(id));
	}
}

bool ObjectGunbool  = false;
void ObjGun(std::string object)
{
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	FLOAT heading = ENTITY::GET_ENTITY_HEADING(playerPed);
	STREAMING::REQUEST_MODEL($(object));
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 dir = rot_to_direction(&rot);
	Vector3 camPosition = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	float spawnDistance = get_distance(&camPosition, &playerPosition);
	spawnDistance += 5;
	Vector3 spawnPosition = (camPosition + (dir* spawnDistance));

	if (bPlayerExists)
	{
		if (PED::IS_PED_SHOOTING(playerPed))
		{
			Vector3 playerOffset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0, 5, 0);
			if (PED::IS_PED_ON_FOOT(playerPed))
			{
				STREAMING::REQUEST_MODEL($(object));
				while (!STREAMING::HAS_MODEL_LOADED($(object))) WAIT(0);
				{
					Vehicle veh = VEHICLE::CREATE_VEHICLE($(object), spawnPosition.x, spawnPosition.y, spawnPosition.z, heading, 1, 1);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 120.0);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED($(object));
					ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
				}

			}
		}
	}
}

#pragma region Weapon
bool CartoonBool = false;
bool AirStrikebool = false;
bool oneshotkillbool = false;
int weapontint = 0;
Hash WeaponHash;
std::string weaponName;
WeaponInfo selectWeapon;

bool rapidfirer = false;
void rapidmaker() {
	Player playerPed = PLAYER::PLAYER_PED_ID();
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 1);
		Vector3 gameplayCam = CAM::_GET_GAMEPLAY_CAM_COORDS();
		Vector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
		Vector3 gameplayCamDirection = RotationToDirection(gameplayCamRot);
		Vector3 startCoords = (gameplayCam + (gameplayCamDirection*1.0f));
		Vector3 endCoords = (startCoords + (gameplayCamDirection*500.0f));
		Hash weaponhash;
		WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &weaponhash, 1);
		if (CONTROLS::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000)) {
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(startCoords.x, startCoords.y, startCoords.z, endCoords.x, endCoords.y, endCoords.z, 50, 1, weaponhash, playerPed, 1, 1, 0xbf800000);
		}
	}
}
void AirStrike()
{
	if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
	{
		Vector3 aimPos = GET_AIM_COORDS();
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(aimPos.x, aimPos.y, aimPos.z + 900.0f, aimPos.x, aimPos.y, aimPos.z, 200, true, 0x13579279, PLAYER::GET_PLAYER_PED(0), true, false, 0.612837E+09f);
	}
}

void weapon()
{
	addTitle("Weapon");
	//menu.MenuOption("Bullet Menu", "bullet");
	menu.MenuOption("Update Compment", "compment");
	menu.MenuOption("bullet", "bullet");
	if (menu.Option("Get ALL Weapon"))
	{
		for (auto id : weaponNames)
		{
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), $(id), 9999, false, false);
		}
	}
	if (menu.Option("Remove All Weapon"))PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 0);
	if (WEAPON::IS_PED_ARMED(PLAYER::PLAYER_PED_ID(), 7))
	{
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &WeaponHash, 1);
		if (menu.IntOption("Tint", weapontint, 0, WEAPON::GET_WEAPON_TINT_COUNT(WeaponHash)))
		{
			WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WeaponHash, weapontint);
		}
	}
	/*menu.BoolOption("Explode Ammo", WeaponOptions::explosiveammobool);
	menu.BoolOption("rainbow Gun", WeaponOptions::RainbowWeapon);*/
	menu.BoolOption("Air Strike", AirStrikebool);
	menu.BoolOption("INF Ammo", infammobool);
	menu.BoolOption("Rapid Fire", rapidfirer);
	//if(menu.Option("Upgrade All weapon"))
	if (menu.BoolOption("one shot kill", oneshotkillbool))
	{
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_PED_ID(), 999999);
		PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_PED_ID(), 999999);
	}
	/*menu.BoolOption("Explosive Ammo", WeaponOptions::explosiveammobool);
	menu.BoolOption("Fire Ammo", WeaponOptions::fireammobool);*/
	if (menu.BoolOption("Cartoon Gun", CartoonBool))
	{
		if (CartoonBool)
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
		}
		GRAPHICS::ENABLE_CLOWN_BLOOD_VFX(CartoonBool);
	}
	menu.BoolOption("gravity Gun", Gravity);
	

}
void compment()
{
	addTitle("CompMent");
	for (auto name : Info)
	{
		std::string display = UI::_GET_LABEL_TEXT((char*)name.Hash.c_str());
		if (display == "NULL")
			display = name.Hash;
		if (WeaponHash == $(name.Hash))
			if (menu.MenuOption(display, "weaponupgrade"))
			{
				selectWeapon = name;
			}
	}
}
int compmentpos[10];
void weaponupgrade()
{
	std::string display = UI::_GET_LABEL_TEXT((char*)selectWeapon.Hash.c_str());
	if (display == "NULL")
		display = selectWeapon.Hash;
	addTitle(display);
	for (int i = 0; i < selectWeapon.Compment.size(); i++)
	{
		if (
			menu.StringArray(std::to_string(i), selectWeapon.Compment[i], compmentpos[i])
			//menu.IntOption(std::to_string(i), compmentpos[i], 0, selectWeapon.Compment[i].size(), 1, { selectWeapon.Compment[i] })
			)
		{
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), $(selectWeapon.Hash), $(selectWeapon.Compment[i][compmentpos[i]]));
		}
	}
}

int afterAhours;
void bullet()//bullet
{
	addTitle("Bullet");
	menu.MenuOption("Bullet Setting", "bulletSetting");
	menu.StringArray("shoot Vehcile", v_Afterhours, afterAhours);
	menu.BoolOption("Start to shoot", ObjectGunbool);
}
#pragma endregion
void bulletSetting()
{
	addTitle("Bullet Setting");

}

void update_weapon_menu()
{
	if (menu.CurrentMenu("weapon"))weapon();
	if (menu.CurrentMenu("compment"))compment();
	if (menu.CurrentMenu("weaponupgrade"))weaponupgrade();
	if (menu.CurrentMenu("bullet"))bullet();
	if (menu.CurrentMenu("bulletSetting"))bulletSetting();
}

void update_weapon_game()
{
	infammobool ? infammo() : NULL;
	Gravity ? GravityGun() : NULL;
	AirStrikebool ? AirStrike() : NULL;
	ObjectGunbool ? ObjGun(v_Afterhours[afterAhours]) : NULL;
}