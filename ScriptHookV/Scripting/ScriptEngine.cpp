#include "ScriptEngine.h"
#include "ScriptManager.h"
#include "NativeInvoker.h"
#include "Pools.h"

#include "..\ASI Loader\ASILoader.h"
#include "..\Input\InputHook.h"
#include "..\DirectX\D3d11Hook.h"
#include "..\Hooking\Hooking.h"

#include "..\..\SDK\inc\enums.h"
#include "../Menu/UI/Script.h"







GlobalTable		globalTable;
eGameState *	gameState;
eHookState		g_HookState;
int				g_GameVersion;
bool			g_IsRetail;

static uint64_t												m_worldPtr;
static BlipList*											m_blipList;
const int EVENT_COUNT = 83;
static std::vector<void*> EventPtr;
static char EventRestore[EVENT_COUNT] = {};





bool ScriptEngine::Initialize()
{
	LOG_PRINT("Initializing...");

	// init Direct3d hook
	if (!g_D3DHook.InitializeHooks())
	{
		LOG_ERROR("Failed to Initialize Direct3d Hooks");
		return false;
	}

	//// kill this data snoop ( must  be done after D3D )
	//if (Utility::GetProcessID("GTAVLauncher.exe"))
	//{
	//	Utility::killProcessByName("GTAVLauncher.exe");
	//	LOG_DEBUG("Killed %s", "GTAVLauncher.exe");
	//}

	LOG_DEBUG("Base Address \t\t 0x%012llx", mem::module::main().base().as<uint64_t>());
	LOG_DEBUG("end Address \t\t 0x%012llx", mem::module::main().end().as<uint64_t>());

	// init Winproc hook
	if (!InputHook::Initialize())
	{
		LOG_ERROR("Failed to Initialize InputHook");
		return false;
	}

	// Get game state
	if (auto gameStatePattern = "83 3D ? ? ? ? ? 8A D9 74 0A"_Scan)
	{
		gameState = gameStatePattern.add(2).rip(5).as<decltype(gameState)>();
		LOG_ADDRESS("gameState", gameState);
	}
	else
	{
		LOG_ERROR("Unable to find gameState");
		return false;
	}

	// Get global table
	if (auto globalTablePattern = "4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11"_Scan)
	{
		globalTable.GlobalBasePtr = globalTablePattern.add(3).rip(4).as<PINT64*>();
		while (!globalTable.IsInitialised()) Sleep(100);
		LOG_ADDRESS("globalTable", globalTable.GlobalBasePtr);
	}
	else
	{
		LOG_ERROR("Unable to find globalTable");
		return false;
	}

	while (GetGameState() != GameStatePlaying) Sleep(100);

	//Bypass Mode Check For online 
	//Done 
	if (auto modelCheckPattern = "48 85 C0 0F 84 ? ? ? ? 8B 48 50"_Scan)
	{
		LOG_ADDRESS("modelCheckPattern", modelCheckPattern.as<char*>());
		modelCheckPattern.nop(24);
	}
	else if (auto tmodelCheckPattern = "48 8B F8 90 90 90 90 90 90 90"_Scan)//Model Check has been Bypassed 
	{
		LOG_ADDRESS("model Check has been Bypassed", tmodelCheckPattern.add(3).as<char*>());
	}
	else
	{
		LOG_ERROR("Fail to Find modelCheckPattern");
	}

	//Bypass Model Spawn Check
	if (auto modelSpawnPattern = "48 8B C8 FF 52 30 84 C0 74 05 48"_Scan)
	{
		LOG_ADDRESS("model Spawn Check", modelSpawnPattern.as<char*>());
		modelSpawnPattern.add(8).nop(2);
	}
	else if (auto tmodelSpawnPattern = "48 8B C8 FF 52 30 84 C0 90 90 48"_Scan)
	{
		LOG_ADDRESS("Model spawn check has been bypassed", tmodelSpawnPattern.as<char*>());
	}
	else
	{
		LOG_ERROR("Fail to Find modelSpawnPattern");
	}
	//Get World Base Ptr
	if (auto p_worldPtr = "48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07"_Scan)
	{
		globalTable.WorldBasePtr = p_worldPtr.add(3).rip(4).as<uintptr_t>();
		LOG_ADDRESS("WorldBasePtr", &globalTable.WorldBasePtr);
	}
	//Get Blip List
	if (auto p_bliplist = "4C 8D 05 ? ? ? ? 0F B7 C1"_Scan)
	{
		m_blipList = p_bliplist.add(3).rip(4).as<BlipList*>();
		LOG_ADDRESS("Blip List", m_blipList);
	}
	else
	{
		LOG_ERROR("unable to find blip_list");
	}

	//if (auto p_playerinfo = "48 8B 05 ? ? ? ? 48 8B 48 08 33 C0 48 85 C9 74 07"_Scan)
	//{
	//	LOG_ADDRESS("PlayerInfo", p_playerinfo.as<void*>());
	//}
	/*if (auto p_eventHook = "48 83 EC 28 E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? BA 03"_Scan)
	{
		char * w_eventHook = p_eventHook.as<char*>();
		LOG_ADDRESS("p_eventHook", w_eventHook);
		char* c_location = p_eventHook.as<char*>();
		int i = 0, j = 0, matches = 0, found = 0;
		char* pattern = "\x4C\x8D\x05";
		while (found != EVENT_COUNT)
		{
			if (c_location[i] == pattern[j])
			{
				if (++matches == 3)
				{
					EventPtr.push_back((void*)(reinterpret_cast<uint64_t>(c_location + i - j) + *reinterpret_cast<int*>(c_location + i + 1) + 7));
					found++;
					j = matches = 0;
				}
				j++;
			}
			else
			{
				matches = j = 0;
			}
			i++;
		}
	}*/

	LOG_PRINT("Performing function hooking...");

	if (Hooking::HookFunctions())
	{
		//LOG_PRINT("Init ASI Loader");
		//ASILoader::Initialize();
		LOG_PRINT("Initializated Main Menu");
		g_MenuThread.AddScript(Utility::GetOurModuleHandle(), ScriptMain);
		//g_AdditionalThread.AddScript(Utility::GetOurModuleHandle(), Auther);
		LOG_PRINT("Initialization finished");

		g_HookState = HookStateRunning;

		return true;
	}

	g_HookState = HookStateExiting;

	return false;
}

eGameState ScriptEngine::GetGameState()
{
	return *gameState;
}

PUINT64 ScriptEngine::getGlobal(int globalId)
{
	return reinterpret_cast<PUINT64>(globalTable.AddressOf(globalId));
}

int ScriptEngine::RegisterFile(const std::string& fullPath, const std::string& fileName)
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
