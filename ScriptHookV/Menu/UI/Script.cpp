#include "../../ScriptHookV.h"
#include "..\..\Scripting\ScriptEngine.h"
#include "..\..\globalHandle.h"
//#include "../../Scripting/ScriptManager.h"
#include "../../ASI Loader/ASILoader.h"
#include "../internal_native.h"
#include "../Function/Player/player.h"

#include "../Function/ObjectList.h"
#include "../Function/Function.h"
#include "../Function/list.h"
#include "../Function/keyboard.h"
#include "../Function/Vehicle/Vehicle.h"
#include "../Function/Teleport/teleport.h"
#include "../Function/Vehicle/Veh_Setting.h"
#include "../Function/Animation/Animation.h"
#include "../Function/online/online.h"
#include "../Function/Weapon/weapon.h"
#include "../Function/Pools/PoolsFunc.h"
#include "../Function/Props/Props.h"
#include "Script.h"

NativeMenu::Menu menu;
NativeMenu::MenuControls controls;

namespace fs = std::experimental::filesystem;
int nothing = 0;
HMODULE _hmodule;
std::string settingsMenuFile;

Veh_Settings settings;

int locpos = 0;
std::vector<std::string> locationstr =
{
	"Left",
	"right"
};

std::vector<std::string> AsiMods;

bool TogglePress()
{
	return IsKeyDown(str2key(menu.select));
}
#pragma region Need to Move

int Register(std::string fullPath, std::string fileName)
{
	int textureID = -1;
	if (rage::FileRegister(&textureID, fullPath.c_str(), true, fileName.c_str(), false))
	{
		LOG_DEBUG("Registered File %s with ID:%i", fullPath.c_str(), textureID);
		return textureID;
	}

	LOG_ERROR("Failed to register %s", fullPath.c_str());
	return 0;
}



#pragma endregion

void onMain() {
	menu.ReadSettings();
}
void onExit() {
	menu.SaveSettings();
}




#pragma region Player Option
int playeralpha = 255;
bool godmodbool = false;
bool disablephone = false;
bool nocops = false;
int wantedlevel = 0;
int clothes[12];
int cltexture[12];

bool developuser = false;

//PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID()); Default outfit
//PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), true); //Random Outfit
void playermenu()
{
	addTitle("player Option");
	if (menu.MenuOption("Character Customizer", "customchracter"))
	{
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		for (int i = 0; i < 12; i++)
		{
			clothes[i] = PED::GET_PED_DRAWABLE_VARIATION(playerPed, i);
			cltexture[i] = PED::GET_PED_TEXTURE_VARIATION(playerPed, i);
		}
	}
	menu.MenuOption("movement", "movement", {},true , developuser);
	menu.MenuOption("Change Model", "playermodel");
	if (menu.BoolOption("God Mod", godmodbool))
	{
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), godmodbool);
		ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), godmodbool, godmodbool, godmodbool, godmodbool, godmodbool, godmodbool, godmodbool, godmodbool);
	}
	if (menu.IntOption("Alpha", playeralpha, 0, 255, 20))
	{
		ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), playeralpha, 0);
	}
	if (menu.Option("fix Player"))PlayerOption::fixplayer();
	if (menu.Option("New Look")) { PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), developuser); }
	if (menu.Option("Max Health")) PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(PLAYER::PLAYER_PED_ID(), 400);
	if (menu.Option("Clear Model")) PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID());
	if (menu.IntOption("Wanted Level", wantedlevel, 0, 5))PlayerOption::setwantedlevel(wantedlevel);
	menu.BoolOption("No cops", nocops);
	if (menu.BoolOption("Invincible", PlayerOption::GodModeBool))PlayerOption::GodMode();
	if (menu.BoolOption("Super Jump", PlayerOption::superjumpbool))PlayerOption::superjump();
	if (menu.BoolOption("ragdol", PlayerOption::ragdollbool))PlayerOption::ragdoll();
	if (menu.BoolOption("visible", PlayerOption::visiblebool)) { ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), PlayerOption::visiblebool, PlayerOption::visiblebool); }
	if (menu.BoolOption("Freecam", PlayerOption::freecambool))PlayerOption::freecam();
	if (menu.BoolOption("Super Man", PlayerOption::supermanbool))PlayerOption::superman();
	if (menu.BoolOption("Tiny Player", PlayerOption::betiny))PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, PlayerOption::betiny);
	menu.BoolOption("Disable Phone", disablephone);

}
void playermodel()
{
	addTitle("ChangeModel");
	for (std::string id : player_model)
	{
		std::string display = id;//Prevent User translate it 
		if (menu.Option(display))
		{
			changemodel(id);//to change player model 
		}
	}
}

void movement()
{
	addTitle("Movement");
	if (menu.Option("Reset"))
	{
		PED::RESET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), 1.0f);
	}
	for (auto name : movementname)
	{
		std::string display = name;
		if (menu.Option(display, {}, false))PlayerOption::SetPedMovementClipset((char*)name.c_str());
	}
}


void customchracter()//customchracter
{
	addTitle("Customizer");

	menu.Option("~HUD_COLOUR_CONTROLLER_TREVOR~need to fix");
	if (menu.IntOption("Face", clothes[0], 0, 81))PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, clothes[0], 0, true);
	if (menu.IntOption("Mask", clothes[1], 0, 81))PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, clothes[1], 0, true);
	if (menu.IntOption("Hair", clothes[2], 0, 81))PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, clothes[2], 0, true);
	if (menu.IntOption("Torso", clothes[3], 0, 81))PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 3, clothes[3], 0, true);
	if (menu.IntOption("Legs", clothes[4], 0, 81))PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 4, clothes[4], 0, true);
	if (menu.IntOption("Hands", clothes[5], 0, 81))PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 5, clothes[5], 0, true);
	if (menu.IntOption("Shoes", clothes[6], 0, 81))PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 6, clothes[6], 0, true);
	if (menu.IntOption("Special 1", clothes[8], 0, 81))PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 8, clothes[8], 0, true);
	if (menu.IntOption("Special 2", clothes[9], 0, 81))PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 9, clothes[9], 0, true);
	if (menu.IntOption("Special 3", clothes[10], 0, 81))PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 10, clothes[10], 0, true);
	if (menu.IntOption("Emblem", clothes[11], 0, 81))PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 11, clothes[11], 0, true);
}


#pragma endregion


#pragma region Setting Menu
void MarkerTest()
{
	addTitle("Marker Setting");
	menu.IntOption("Marker Type", menu.markerType, 0, 31);
	menu.FloatOption("Marker Offset", menu.markerOffset, 0, 10.0f, 0.01f);
	//menu.FloatOption("dirX", dir.x, -1000, 1000, 0.01f);
	//menu.FloatOption("dirY", dir.y, -1000, 1000, 0.01f);
	//menu.FloatOption("dirZ", dir.z, -1000, 1000, 0.01f);

	menu.FloatOption("RotX", menu.mRot.x, -1000, 1000, 0.01f);
	menu.FloatOption("RotY", menu.mRot.y, -1000, 1000, 0.01f);
	menu.FloatOption("RotZ", menu.mRot.z, -1000, 1000, 0.01f);

	menu.FloatOption("scaleX", menu.mScale.x, -100, 100, 0.01f);
	menu.FloatOption("scaleY", menu.mScale.y, -100, 100, 0.01f);
	menu.FloatOption("scaleZ", menu.mScale.z, -100, 100, 0.01f);

	menu.IntOption("RGB.R", menu.mRgb.R, 0, 255, 1);
	menu.IntOption("RGB.G", menu.mRgb.G, 0, 255, 1);
	menu.IntOption("RGB.B", menu.mRgb.B, 0, 255, 1);
	menu.IntOption("RGB.A", menu.mRgb.A, 0, 255, 1);

	menu.BoolOption("bobUpAndDown", menu.bobUpAndDown);
	menu.BoolOption("faceCamera", menu.faceCamera);
	menu.BoolOption("rotate", menu.rotate);

	menu.DrawMarker(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1));//Test on your self
}
void setting_menu()
{
	addTitle("setting");
	menu.MenuOption("Language", "Setting_Language");
	menu.MenuOption("Menu Text Font", "menutext");
	menu.MenuOption("Menu Title Rect", "menurect");
	menu.MenuOption("Option Font", "optionstext");
	menu.MenuOption("Option Rect", "optionrect");
	menu.MenuOption("Selected Text", "selecttext");
	menu.MenuOption("Selected Rect", "selectRect");
	menu.MenuOption("Custom your Keys", "menukey");
	menu.IntOption("Menu Texture", menu.titleTextureIndex, 0, 48);
	menu.FloatOption("Menu X Pos", menu.menuX, 0.0f, 1.0f, 0.01f);
	menu.FloatOption("Menu Y Pos", menu.menuY, 0.0f, 1.0f, 0.01f);
	menu.IntOption("Menu Title", menu.titleFont, 0, 7);
	if (menu.StringArray("Menu Location", locationstr, locpos))	menu.menuX = locpos ? 0.12f : 0.85f;
	menu.BoolOption("Hide Gloable Icon", menu.glareBool);
	//if (menu.Custom&&menu.Option("Custom Title"))
	//{
	//	menu.titlename = show_keyboard();
	//	
	//}
	menu.MenuOption("Marker Setting", "MarkerTest");
	if (menu.Option("Save Setting"))
	{
		showNotification("Save Complete");
		menu.SaveSettings();
	}
	if (menu.Option("Developer : Thenecromance"))
	{
		showNotification("if you have any problem");
		showNotification("Contact me on discord:Thenecromance#7382");
	}
}
void update_settingmenuMenuText()
{
	addTitle("Menu Text");
	menu.IntOption("Red", menu.titleTextColor.R, 0, 255);
	menu.IntOption("Green", menu.titleTextColor.G, 0, 255);
	menu.IntOption("Blue", menu.titleTextColor.B, 0, 255);
	menu.IntOption("Alpha", menu.titleTextColor.A, 0, 255);

}
void update_settingmenuMenuRect()
{
	addTitle("Menu Rect");
	menu.IntOption("Red", menu.titleBackgroundColor.R, 0, 255);
	menu.IntOption("Green", menu.titleBackgroundColor.G, 0, 255);
	menu.IntOption("Blue", menu.titleBackgroundColor.B, 0, 255);
	menu.IntOption("Alpha", menu.titleBackgroundColor.A, 0, 255);
}
void update_settingmenuOptionText()
{
	addTitle("Options Text");
	menu.IntOption("Red", menu.optionsTextColor.R, 0, 255);
	menu.IntOption("Green", menu.optionsTextColor.G, 0, 255);
	menu.IntOption("Blue", menu.optionsTextColor.B, 0, 255);
	menu.IntOption("Alpha", menu.optionsTextColor.A, 0, 255);
}
void update_settingmenuOptionRect()
{
	addTitle("Options Rect");
	menu.IntOption("Red", menu.optionsBackgroundColor.R, 0, 255);
	menu.IntOption("Green", menu.optionsBackgroundColor.G, 0, 255);
	menu.IntOption("Blue", menu.optionsBackgroundColor.B, 0, 255);
	menu.IntOption("Alpha", menu.optionsBackgroundColor.A, 0, 255);
}
void update_settingmenuSelectText()
{
	addTitle("Options Rect");
	//menu.StringArray("特殊颜色", menu.strHudColor, menu.specialcolor);
	menu.IntOption("Red", menu.optionsTextSelectColor.R, 0, 255);
	menu.IntOption("Green", menu.optionsTextSelectColor.G, 0, 255);
	menu.IntOption("Blue", menu.optionsTextSelectColor.B, 0, 255);
	menu.IntOption("Alpha", menu.optionsTextSelectColor.A, 0, 255);
}
void update_settingmenuSelectRect()
{
	addTitle("Options Rect");
	menu.IntOption("Red", menu.optionsBackgroundSelectColor.R, 0, 255);
	menu.IntOption("Green", menu.optionsBackgroundSelectColor.G, 0, 255);
	menu.IntOption("Blue", menu.optionsBackgroundSelectColor.B, 0, 255);
	menu.IntOption("Alpha", menu.optionsBackgroundSelectColor.A, 0, 255);
}
void update_menukey()
{
	addTitle("Key Setting");

	if (menu.StringArray("Toggle Key", { menu.toggle }, nothing))
	{
		menu.toggle = show_keyboard();
		if (menu.toggle != "")
			menu.Setkeys(menu.toggle, NativeMenu::MenuControls::ControlType::MenuKey);
		else
		{
			showNotification("无效按键~");
		}
	}
	if (menu.StringArray("Select", { menu.select }, nothing))
	{
		menu.select = show_keyboard();
		if (menu.select != "")
			menu.Setkeys(menu.select, NativeMenu::MenuControls::ControlType::MenuSelect);
		else
		{
			showNotification("无效按键~");
		}
	}
	if (menu.StringArray("Cancle", { menu.cancle }, nothing))
	{
		menu.cancle = show_keyboard();
		if (menu.cancle != "")
			menu.Setkeys(menu.cancle, NativeMenu::MenuControls::ControlType::MenuCancel);
		else
		{
			showNotification("无效按键~");
		}
	}
	if (menu.StringArray("Left", { menu.left }, nothing))
	{
		menu.left = show_keyboard();
		if (menu.left != "")
			menu.Setkeys(menu.left, NativeMenu::MenuControls::ControlType::MenuLeft);
		else
		{
			showNotification("无效按键~");
		}
	}
	if (menu.StringArray("Right", { menu.right }, nothing))
	{
		menu.right = show_keyboard();
		if (menu.right != "")
			menu.Setkeys(menu.right, NativeMenu::MenuControls::ControlType::MenuRight);
		else
		{
			showNotification("无效按键~");
		}
	}
	if (menu.StringArray("Up", { menu.up }, nothing))
	{
		menu.up = show_keyboard();
		if (menu.up != "")
			menu.Setkeys(menu.up, NativeMenu::MenuControls::ControlType::MenuUp);
		else
		{
			showNotification("无效按键~");
		}
	}
	if (menu.StringArray("Down", { menu.down }, nothing))
	{
		menu.down = show_keyboard();
		if (menu.down != "")
			menu.Setkeys(menu.down, NativeMenu::MenuControls::ControlType::MenuDown);
		else
		{
			showNotification("无效按键~");
		}
	}
	//menu.Option("可用按键~");
	//for (auto k : NativeMenu::KeyMap)
	//{
	//	menu.Option(k.first);
	//}
}
#pragma endregion

#pragma region Vision

bool PTFX_bodyBool = false;
void PTFX_body(char* fxName, char* effect)
{
	/*STREAMING::REQUEST_NAMED_PTFX_ASSET(call1);
	GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(call2);
	GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(name, PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);*/

	STREAMING::REQUEST_NAMED_PTFX_ASSET(fxName);
	DWORD startTime = GetTickCount();
	DWORD timeout = 3000; // in millis
	while (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(fxName))
	{
		if (GetTickCount() > startTime + timeout) {
			showNotification("Couldn't load model");
			WAIT(0);
			return;
		}
		WAIT(0);
	}
	GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(fxName);
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(effect, PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, 0.2f, 0, 0, 0);
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(effect, PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, 0.1f, 0, 0, 0);
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(effect, PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, 0.1f, 0, 0, 0);
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(effect, PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 65245, 0.2f, 0, 0, 0);
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(effect, PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 35502, 0.2f, 0, 0, 0);
}

void visionEffect(char* fxName, char* effect)
{

	STREAMING::REQUEST_NAMED_PTFX_ASSET(fxName);
	DWORD startTime = GetTickCount();
	DWORD timeout = 3000; // in millis
	while (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(fxName))
	{
		if (GetTickCount() > startTime + timeout) {
			showNotification("Couldn't load model");
			WAIT(0);
			return;
		}
		WAIT(0);
	}
	GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(fxName);
	GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(effect, PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
}
VisionEffect loop= effectname[0];
void visonmenu()
{
	addTitle("Vision");
	menu.BoolOption("PTFX On body Loop", PTFX_bodyBool);//This is a Hurge BUGS should I need to let the loops goes to another thread.... maybe 
	for (VisionEffect id : effectname)
	{
		if (menu.Option(id.VisionName, {}, false))
		{
			PTFX_bodyBool ? loop = id : visionEffect((char*)id.fxname.c_str(), (char*)id.ptfx.c_str());
		}
	}
	for (auto name : Scenarios)
	{
		if (menu.Option(name))
		{
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)name.c_str(), 0, false);//Try this

		}
	
	}

}

void screenEffect()
{
	addTitle("Screen Effect");
	for (auto id : screenEffectName)
	{
		std::string display = id;
		if (menu.Option(display))
		{
			GRAPHICS::_STOP_ALL_SCREEN_EFFECTS();
			GRAPHICS::_START_SCREEN_EFFECT((char*)id.c_str(), 0, false);

			if (IsKeyDown(str2key("*")))
			{
				GRAPHICS::_STOP_ALL_SCREEN_EFFECTS();
			}
		}
	}
	for (auto name : Vison)
	{
		std::string display = name;
		if (menu.Option(display))
		{
			GRAPHICS::SET_TIMECYCLE_MODIFIER((char*)name.c_str());
		}
	}
}
#pragma endregion

#pragma region World
int h, m, s, fakelevel;
float timeScale, gravity, windspeed, rainlevel;
void world()
{
	addTitle("World");
	menu.MenuOption("Cloud", "cloud");
	menu.MenuOption("Weather", "weather");
	if (menu.Option("mid Night"))NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(0, 0, 0);
	if (menu.Option("mid Day"))NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(12, 0, 0);
	if (
		menu.IntOption("Hour", h, 0, 23) ||
		menu.IntOption("Minute", m, 0, 60) ||
		menu.IntOption("Second", s, 0, 60)
		)NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(h, m, s);
	if (menu.FloatOption("Time", timeScale, 0, 1.0f))GAMEPLAY::SET_TIME_SCALE(timeScale);
	if (menu.FloatOption("Gravity", gravity, 0, 3))GAMEPLAY::SET_GRAVITY_LEVEL(gravity);
	if (menu.IntOption("Fake Wanted Level", fakelevel, 0, 6))GAMEPLAY::SET_FAKE_WANTED_LEVEL(fakelevel);
	if (menu.Option("Lighting"))GAMEPLAY::_CREATE_LIGHTNING_THUNDER();
	if (menu.FloatOption("Set Wind Speed", windspeed, 0.0f, 10.0f, 0.01f, { "Current Wind SPeed:" + std::to_string(GAMEPLAY::GET_WIND_SPEED()) }))GAMEPLAY::SET_WIND(windspeed);
	if (menu.FloatOption("Set Rain", rainlevel, 0.0f, 20.f))GAMEPLAY::_SET_RAIN_FX_INTENSITY(rainlevel);
	if (menu.Option("Fake Money"))	UI::_SET_PLAYER_CASH_CHANGE(GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, INT_MAX), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, INT_MAX));

	//NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(h, m, s);
}
void cloud()
{
	addTitle("Cloud");
	if (menu.Option("Cloudy")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Cloudy 01", 0.5f); }
	if (menu.Option("Snowy 1")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Snowy 01", 0.5f); }
	if (menu.Option("Rain")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("RAIN", 0.5f); }
	if (menu.Option("Horizon Band 1")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("horizonband1", 0.5f); }
	if (menu.Option("Horizon Band 2")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("horizonband2", 0.5f); }
	if (menu.Option("Horizon Band 3")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("horizonband3", 0.5f); }
	if (menu.Option("Puffs")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Puffs", 0.5f); }
	if (menu.Option("Wispy")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Wispy", 0.5f); }
	if (menu.Option("Horizon")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Horizon", 0.5f); }
	if (menu.Option("Stormy")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.5f); }
	if (menu.Option("Clear")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Clear 01", 0.5f); }
	if (menu.Option("Snowy")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Snowy 01", 0.5f); }
	if (menu.Option("Contrails")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Contrails", 0.5f); }
	if (menu.Option("Altostratus")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("altostratus", 0.5f); }
	if (menu.Option("Nimbus")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Nimbus", 0.5f); }
	if (menu.Option("Cirrus")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Cirrus", 0.5f); }
	if (menu.Option("Cirrocumulus")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("cirrocumulus", 0.5f); }
	if (menu.Option("Stratoscumulus")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("stratoscumulus", 0.5f); }
	if (menu.Option("Stripey")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("Stripey", 0.5f); }
	if (menu.Option("Horsey")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("horsey", 0.5f); }
	if (menu.Option("Shower")) { GAMEPLAY::_SET_CLOUD_HAT_TRANSITION("shower", 0.5f); }
}
void weather()
{
	addTitle("Weather");
	if (menu.Option("Sun")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Clear"); }
	if (menu.Option("ExtraSunny")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("EXTRASUNNY"); }
	if (menu.Option("BLIZZARD")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("BLIZZARD"); }
	if (menu.Option("NEUTRAL")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("NEUTRAL"); }
	if (menu.Option("SNOW")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("SNOW"); }
	if (menu.Option("Rain")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Clearing"); }
	if (menu.Option("Snow")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Snowlight"); }
	if (menu.Option("Thunder")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Thunder"); }
	if (menu.Option("Blizzard")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Blizzard"); }
	if (menu.Option("Overcast")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Overcast"); }
	if (menu.Option("Foggy")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Foggy"); }
	if (menu.Option("Smog")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Smog"); }
	if (menu.Option("Clouds")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Clouds"); }
	if (menu.Option("XMAS")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("XMAS"); }
	if (menu.Option("HALLOWEEN")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("HALLOWEEN"); }
}
#pragma endregion


void test()
{
	addTitle("test");
	if (menu.Option("Reload All Asi Mods"))
	{
		ASILoader::Initialize();
	}
	if (menu.Option("Dump All"))
	{
		NativeInvoker::DumpNativeList();
	}
}

void asiloader()
{
	addTitle("AsiLoader");
	if (menu.Option("re-check"))
	{
		find((char*)(settingsMenuFile + "\\Mods").c_str(), AsiMods);
	}
	for (auto name : AsiMods)
	{
		std::string display = name;
		if (EndsWith(display, ".asi") && menu.Option(display, {},false,true))
			LoadTargetPlugins(settingsMenuFile + "\\Mods\\" + name);


	}
		
}

void mainmenu()
{
	addTitle("Project X");
	//menu.MenuOption("Test Options", "test", {"Still in developing"},false, developuser);
	menu.MenuOption("Player", "playermenu");
	menu.MenuOption("Vehicle", "vehiclemenu");
	menu.MenuOption("Pools", "PoolsMenu");
	menu.MenuOption("Online", "online");
	menu.MenuOption("weapon", "weapon");
	menu.MenuOption("Teleport", "teleport");
	menu.MenuOption("Animation", "MainAnimation");
	menu.MenuOption("ASI Loader", "asiloader");
	menu.MenuOption("Vision", "visonmenu");
	menu.MenuOption("Screen Effect", "screenEffect");
	menu.MenuOption("world", "world");
	menu.MenuOption("Prop Option", "Props");
	menu.MenuOption("Settings", "setting_menu");//Done
	if(menu.Option("Unload Menu"))g_HookState = HookStateExiting;
}

void update_game()
{
#pragma region Player Options
	//TinyPlayer(betiny);
	disablephone ? MOBILE::DESTROY_MOBILE_PHONE() : NULL;
	PlayerOption::freecambool ? PlayerOption::freecam() : NULL;
	PlayerOption::supermanbool ? PlayerOption::superman() : NULL;
	PTFX_body?((char*)loop.fxname.c_str(), (char*)loop.ptfx.c_str()) : NULL;
	PlayerOption::superjumpbool ? PlayerOption::superjump() : NULL;
	nocops ? PlayerOption::setwantedlevel(0) : NULL;
#pragma endregion

	update_veh_game();

	update_weapon_game();

	update_online_game();

	update_Pool_game();

	update_Props_game();
}

void update_menu()
{
	menu.CheckKeys();
	if (menu.CurrentMenu("mainmenu")) mainmenu();
	if (menu.CurrentMenu("test")) test();
	if (menu.CurrentMenu("visonmenu")) visonmenu();
	if (menu.CurrentMenu("screenEffect")) screenEffect();
	if (menu.CurrentMenu("world")) world();
	if (menu.CurrentMenu("cloud")) cloud();
	if (menu.CurrentMenu("weather")) weather();
	if (menu.CurrentMenu("asiloader")) asiloader();

#pragma region Player Options
	if (menu.CurrentMenu("playermenu")) playermenu();
	if (menu.CurrentMenu("playermodel"))playermodel();
	if (menu.CurrentMenu("customchracter"))customchracter();
	if (menu.CurrentMenu("movement"))movement();
#pragma endregion
#pragma region Online Options

#pragma endregion

#pragma region Setting
	if (menu.CurrentMenu("setting_menu"))setting_menu();
	if (menu.CurrentMenu("MarkerTest"))MarkerTest();
	if (menu.CurrentMenu("menutext"))update_settingmenuMenuText();
	if (menu.CurrentMenu("menurect"))update_settingmenuMenuRect();
	if (menu.CurrentMenu("optionstext"))update_settingmenuOptionText();
	if (menu.CurrentMenu("optionrect"))update_settingmenuOptionRect();
	if (menu.CurrentMenu("selecttext"))update_settingmenuSelectText();
	if (menu.CurrentMenu("selectRect"))update_settingmenuSelectRect();
	if (menu.CurrentMenu("menukey"))update_menukey();
#pragma endregion
#pragma region Vehicle Menu
	update_veh_menu();
#pragma endregion
	update_tel_menu();

	update_ani_menu();

	update_weapon_menu();

	update_online_menu();

	update_Pool_menu();

	update_Props_menu();

	menu.EndMenu();
}


void mainInit()
{
	Build_Anim();
	BuildTeleport();
	AsiMods.clear();
	find((char*)(settingsMenuFile + "\\Mods").c_str(), AsiMods);
}



void main()
{
	settingsMenuFile = Utility::GetModuleFolder(Utility::GetOurModuleHandle()) + "\\ProjectX";
	if (CreateDirectoryA(settingsMenuFile.c_str(), NULL))	LOG_PRINT("MoD Vehicle Directory Craete Successfully");
	LOG_MENU(("Config paths:" + settingsMenuFile + "\\Config.ini").c_str());
	menu.SetFiles(settingsMenuFile + "\\Config.ini");

	menu.RegisterOnMain(std::bind(onMain));
	menu.RegisterOnExit(std::bind(onExit));

	menu.ReadSettings();
	int textureid = 0;
	if (Register((settingsMenuFile + "\\ProjectX.ytd").c_str(), "ProjectX.ytd") > 0)menu.Custom = true;

#pragma region Mod Vehicle
	CreateDirectoryA((settingsMenuFile + "\\Mod Vehicle").c_str(), 0);
	CreateDirectoryA((settingsMenuFile + "\\Mod Vehicle\\Ini Mod").c_str(), 0);
	CreateDirectoryA((settingsMenuFile + "\\Mod Vehicle\\Xml Mod").c_str(), 0);
	CreateDirectoryA((settingsMenuFile + "\\Mod Vehicle\\Json Mod").c_str(), 0);
	CreateDirectoryA((settingsMenuFile + "\\Mods").c_str(), 0);
#pragma endregion


	mainInit();
	//TODO:need to change to another way
	DrawBigMsg("SHOW_MISSION_PASSED_MESSAGE", "Project X Loaded");
	showNotification("This menu is total Free");
	while (true)
	{
		update_menu();
		update_game();
		WAIT(0);
		//g_MenuThread
	}
}

void WINAPI  ScriptMain() {
	globalHandle(0x41183A).As<BOOL>() = 1;
	srand(GetTickCount());
	main();
}

bool iscracked = false;//To check this Auth is cracked
void WINAPI Auther()//This might not indeed
{
	while (true)
	{
	//	std::string username = std::to_string(SOCIALCLUB::_SC_GET_NICKNAME());
		time_t t;
		struct tm * lt;
		time(&t);//获取Unix时间戳。
		lt = localtime(&t);//转为时间结构。
		if (lt->tm_mday > 12)
		{
			showNotification("This version has been Outdate");
			if (false)return;
			g_HookState = HookStateExiting;
			iscracked = false;
		
		}
		else
		{
			iscracked = true;
		}
		if (false)return;

		Sleep(100);
		//if this game is cracked this Thread will call some detected Function to make this menu as Detected
		if (NETWORK::NETWORK_IS_SESSION_ACTIVE() && !iscracked)
		{
			if (NETWORK::NETWORK_IS_SESSION_STARTED())
			{
				PLAYER::PLAYER_ID();
			}
		}

		iscracked = false;
	}
}