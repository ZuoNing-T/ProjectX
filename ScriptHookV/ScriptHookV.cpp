#include "Scripting\ScriptEngine.h"
#include "Scripting\ScriptManager.h"
#include "Input\InputHook.h"
#include "Hooking\Hooking.h"
#include "DirectX\D3d11Hook.h"
#include "Utility\Versioning.h"
#include "..\SDK\inc\enums.h"

using namespace Utility;

std::uint32_t g_ThreadHash = "shop_controller"_joaat;//"shop_controller"_joaat;//TODO: I still need to change it to another one 

BOOL APIENTRY DllMain( HINSTANCE hModule, DWORD dwReason, LPVOID /*lpvReserved*/ ) 
{
	switch ( dwReason ) 
	{
		case DLL_PROCESS_ATTACH: 
		{
			SetOurModuleHandle(hModule);
			Utility::GetLog()->Clean();

			static auto& versionTool = GTAVersion::GetInstance();
			g_GameVersion = versionTool.GameVersion();
			auto gta5directory = versionTool.GameDirectory();
			auto versionString = versionTool.VersionString();
			
			if (g_GameVersion == -1)
			{
				exit(0);
				//auto file = GetOurModuleFolder() + "\\Native_Registration.txt";
				//if (DoesFileExist(file.c_str())) remove(file.c_str());
				//LOG_FILE("Native_Registration", "%s", versionString.c_str());
				//CreateElevatedThread([](LPVOID)->DWORD
				//{ 
				//	Hooking::HookFunctions();
				//	while (true)
				//	{
				//		static eGameState* gameState = "83 3D ? ? ? ? ? 8A D9 74 0A"_Scan.add(2).rip(5).as<decltype(gameState)>();
				//		if (*gameState == GameStateMainMenu)
				//		{
				//			Hooking::UnHookFunctions();
				//			MessageBoxA(NULL, FMT("New Game Version %s", versionTool.VersionString().c_str()).c_str(), "Project X Incompatible", MB_OK | MB_TOPMOST);
				//			FreeLibraryAndExitThread(Utility::GetOurModuleHandle(), ERROR_SUCCESS);
				//			break;
				//		}
				//	}
				//	return TRUE;
				//});
			}
			else
			{
				if (g_IsRetail = !DoesFileExist((gta5directory + "\\steam_api64.dll").c_str())) g_GameVersion += 1;
				LOG_DEBUG("found GTA5 directory %s", gta5directory.c_str());
				LOG_DEBUG("detected GTA5 %s Version %s", g_IsRetail ? "Retail" : "Steam", versionString.c_str());

				//// incompatible with versions prior to 1.0.1493.0 with current hashmap.
				//if (g_GameVersion < VER_1_0_1493_1_STEAM)
				//{
				//	MessageBoxA(NULL, "Update to Version 1.0.1493.0", "Game Version Incompatible!",  MB_OK | MB_TOPMOST);
				//	FreeLibraryAndExitThread(hModule, 0);
				//	return TRUE;
				//}

				CreateElevatedThread([](LPVOID)->DWORD
				{
					if (!ScriptEngine::Initialize())
					{
						LOG_ERROR("Failed to initialize ScriptEngine");
						return FALSE;
					}	return TRUE;
				});
				
			}
			break;
		}
		case DLL_PROCESS_DETACH: 
		{
			g_HookState = HookStateExiting;
			break;
		}
	}

	return TRUE;
}
