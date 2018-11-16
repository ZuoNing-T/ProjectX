#include "../../ScriptHookV.h"
#include "../../internal_native.h"
#include "../Function.h"
#include "../../../SDK/inc/enums.h"
#include "../keyboard.h"
#include "../../Utility/Pattern.h"
#include "../../Scripting/ScriptEngine.h"

namespace PlayerOption
{
	void fixplayer()
	{
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		PED::CLEAR_PED_BLOOD_DAMAGE(playerPed);
		ENTITY::SET_ENTITY_HEALTH(playerPed, ENTITY::GET_ENTITY_MAX_HEALTH(playerPed));
		PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_PED_ID() - PED::GET_PED_ARMOUR(playerPed)));
	}

	bool betiny = false;
	void TinyPlayer(bool toggle)
	{
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, toggle);
	}

	void SetPedMovementClipset(char* clipset) {
		STREAMING::REQUEST_ANIM_SET(clipset);
		DWORD startTime = GetTickCount();
		DWORD timeout = 3000; // in millis
		while (!STREAMING::HAS_ANIM_SET_LOADED(clipset)) {
			WAIT(0);
			if (GetTickCount() > startTime + timeout) {
				showNotification("Couldn't load movement");
				WAIT(0);
				return;
			}
		}
		PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), clipset, 1.0f);
	}

	bool GodModeBool = false;
	void GodMode()
	{

		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), GodModeBool);
		ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), GodModeBool, GodModeBool, GodModeBool, GodModeBool, GodModeBool, GodModeBool, GodModeBool, GodModeBool);
	}

	bool ragdollbool = false;
	void ragdoll()
	{
		mem::set_value<DWORD>(globalTable.WorldBasePtr, { OFFSET_PLAYER, OFFSET_PLAYER_INFO, OFFSET_PLAYER_RAGDOLL }, ragdollbool ? 0x01 : 0x20);
		PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), ragdollbool);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), ragdollbool);
		PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), ragdollbool);
	}

	bool superjumpbool = false;
	void superjump()
	{
		mem::set_value<DWORD>(globalTable.WorldBasePtr,{ OFFSET_PLAYER,OFFSET_PLAYER_INFO,OFFSET_PLAYER_INFO_FRAMEFLAGS }, 1 << 14);
	}

	bool explodeMeleebool = false;
	void explodeMelee()
	{
		mem::set_value<DWORD>(globalTable.WorldBasePtr, { OFFSET_PLAYER,OFFSET_PLAYER_INFO,OFFSET_PLAYER_INFO_FRAMEFLAGS }, 1 << 13);
	}

	void setwantedlevel(int wantedlevel)
	{
		mem::set_value<int>(globalTable.WorldBasePtr, { 0x08, 0x10B8, 0x818 }, wantedlevel);
	}

	bool visiblebool = true;

	bool freecambool = false;
	void freecam()
	{
		Ped local_ped = PLAYER::PLAYER_PED_ID();
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(local_ped, false);
		Vector3 pos2 = GET_AIM_COORDS();
		float heading = GAMEPLAY::GET_HEADING_FROM_VECTOR_2D((pos.x - pos2.x), (pos.y - pos2.y));
		ENTITY::SET_ENTITY_HEADING(local_ped, heading);
		//ENTITY::SET_ENTITY_VISIBLE(local_ped, !freecambool, !freecambool);
		ENTITY::SET_ENTITY_COLLISION(local_ped, !freecambool, true);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(local_ped, pos.x, pos.y, pos.z, false, false, false);
		//可用	
		float fivef = .5f;
		if (GetAsyncKeyState(0x11) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268))
		{
			fivef = 1.5f;
		}
		if (GetAsyncKeyState(VK_KEY_W) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) {
			//float heading = ENTITY::GET_ENTITY_HEADING(local_ped);//可用
			float xVec = fivef * sin(degToRad(heading)) * -1.0f;
			float yVec = fivef * cos(degToRad(heading));
			//ENTITY::SET_ENTITY_HEADING(local_ped, heading);
			pos.x -= xVec, pos.y -= yVec;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(local_ped, pos.x, pos.y, pos.z, false, false, false);
		}
		//可用
		if (GetAsyncKeyState(VK_KEY_S) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) {
			float xVec = fivef * sin(degToRad(heading)) * -1.0f;
			float yVec = fivef * cos(degToRad(heading));
			pos.x += xVec, pos.y += yVec;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(local_ped, pos.x, pos.y, pos.z, false, false, false);
		}

		if (GetAsyncKeyState(VK_KEY_D) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 266)) {
			float xVec = fivef * sin(degToRad(heading - 90.0f)) * -1.0f;
			float yVec = fivef * cos(degToRad(heading - 90.0f));
			pos.x -= xVec, pos.y -= yVec;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(local_ped, pos.x, pos.y, pos.z, false, false, false);
		}
		if (GetAsyncKeyState(VK_KEY_A) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 271)) {
			float xVec = fivef * sin(degToRad(heading + 90.0f)) * -1.0f;
			float yVec = fivef * cos(degToRad(heading + 90.0f));
			pos.x -= xVec, pos.y -= yVec;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(local_ped, pos.x, pos.y, pos.z, false, false, false);
		}
		if (GetAsyncKeyState(VK_SHIFT) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, ControlFrontendRb)) {

			pos.z -= 0.5*fivef;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(local_ped, pos.x, pos.y, pos.z, false, false, false);
		}
		if (GetAsyncKeyState(VK_SPACE) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, ControlFrontendLb)) {

			pos.z += 0.5*fivef;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(local_ped, pos.x, pos.y, pos.z, false, false, false);
		}
	}

	bool supermanbool = false;
	void superman()
	{
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		if (GetAsyncKeyState(VK_SPACE) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(2, ControlFrontendAccept))
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, 3, 0.f, 0.f, 2.5f, 0.f, 0.f, 0.f, 0, true, false, true, false, false);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, 0xFBAB5776, 0, true);
			WEAPON::SET_CURRENT_PED_WEAPON(playerPed, 0xFBAB5776, true);
		}
		if (PED::IS_PED_RUNNING_RAGDOLL_TASK(playerPed) && PED::IS_PED_FALLING(playerPed) && PED::IS_PED_IN_PARACHUTE_FREE_FALL(playerPed))
		{
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, 0xFBAB5776, 0, true);
			WEAPON::SET_CURRENT_PED_WEAPON(playerPed, 0xFBAB5776, true);
			if (GetAsyncKeyState(VK_KEY_W))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, 3, 0.f, 2.5f, 0.f, 0.f, 0.f, 0.f, 0, true, false, true, false, false);
			}
			if (GetAsyncKeyState(VK_KEY_S))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, 3, 0.f, -2.5f, 0.f, 0.f, 0.f, 0.f, 0, true, false, true, false, false);
			}
			if (GetAsyncKeyState(VK_SHIFT))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, 3, 0.f, 0.f, -2.5f, 0.f, 0.f, 0.f, 0, true, false, true, false, false);
			}
		}
	}

	bool mobileRadio = false;
	void toggleMobileRadio()
	{
		int station = AUDIO::GET_PLAYER_RADIO_STATION_INDEX();
		if (mobileRadio)
		{
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(false);
			mobileRadio = false;
		}
		else
		{
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(true);
			AUDIO::SET_RADIO_TO_STATION_INDEX(station);
			mobileRadio = true;
		}
	}

	void randomoutfit()
	{
		PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), true);
	}

	void cleanplayer()
	{
		PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
		PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID());
		PED::CLEAR_PED_WETNESS(PLAYER::PLAYER_PED_ID());
		PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
		PED::_CLEAR_PED_FACIAL_DECORATIONS(PLAYER::PLAYER_PED_ID());
	}

	void killself()
	{
		ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), false, false, false, false, false, false, false, false);
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
		ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0);
		Vector3 myPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		FIRE::ADD_EXPLOSION(myPosition.x, myPosition.y, myPosition.z, 4, 100.f, true, false, 0.f);

	}
}
