#include "Hooking.h"

#include "..\Input\InputHook.h"

#include "..\DirectX\D3d11Hook.h"

#include "..\Scripting\ScriptEngine.h"
#include "..\Scripting\NativeInvoker.h"
#include "..\Scripting\ScriptThread.h"
#include "..\Scripting\ScriptManager.h"

using namespace Hooking;

// Gta Natives

// system::wait

//static bool IS_DLC_PRESENT(Hash dlcHash) { return invoke<bool>(0x812595A0644CE1DE, dlcHash); }
//DetourHook<bool __fastcall(__int64)> Detour_Is_Dlc_Present;
DetourHook<NativeHandler> Detour_Is_Dlc_Present;
void __fastcall Hk_Is_Dlc_Present(scrNativeCallContext* context)
{

	switch (g_HookState)
	{
	case HookStateRunning:
	{

		ScriptManager::MainFiber();
	} break;

	case HookStateExiting:
	{
		LOG_MENU("Unloading Menu");
		ScriptManager::UnloadHook();
	} break;

	default:
		break;
	}

	return Detour_Is_Dlc_Present(context);
}

//void TRIGGER_SCRIPT_EVENT(int eventGroup, Any* args, int argCount, int bit) { invoke<Void>(0x5AE99C571D5BBE5D, eventGroup, args, argCount, bit); }
DetourHook<void __fastcall(int, Any*, int, int)>Detour_Trigger_Script_event;
void __fastcall Hk_Trigger_Script_event(int eventGroup, Any* args, int argCount, int bit)
{
	LOG_DEBUG("args Count %d", argCount);
	for (int i = 0; i < argCount; i++)
	{
		LOG_DEBUG("args Count[%d]:%d", i, args[i]);
	}

	return Detour_Trigger_Script_event(eventGroup, args, argCount, bit);
}

DetourHook<NativeHandler> Detour_System_Wait;
void __fastcall System_Wait(scrNativeCallContext* context)
{
	switch (g_HookState)
	{
	case HookStateRunning:
	{
		ScriptManager::MainFiber();
	} break;

	case HookStateExiting:
	{
		ScriptManager::UnloadHook();
	} break;

	default:
		break;
	}

	return Detour_System_Wait(context);
}

DetourHook<NativeHandler> Detour_Trigger;
void __fastcall Sytem_Trigger(scrNativeCallContext* context)
{
	LOG_MENU("Trigger count:%d", context->getArgCount());
	Any* args = context->GetArg<Any*>(1);
	auto counts = context->GetArg<int>(2);
	for (int i = 0; i < counts; i++)
	{
		LOG_MENU("args[%d]:%d", i, args[i]);
	}
	return Detour_Trigger(context);
}

// Gta Functions

// NativeRegistration
DetourHook<__int64 __fastcall(__int64, __int64, __int64)> Detour_NativeRegistration;
__int64 __fastcall NativeRegistration(__int64 a1, __int64 hash, __int64 address)
{
	LOG_FILE("Native_Registration", "0x%016llx, 0x%08llx", hash, normalise_base(address, 0));

	return Detour_NativeRegistration(a1, hash, address);
}

// Hooking - Functions

std::uintptr_t Hooking::normalise_base(mem::handle address, const std::uintptr_t& offset)
{
	auto module = mem::module::main();

	if (module.contains(address))
	{
		address = address.translate(module.base(), offset);
	}

	return address.as<std::uintptr_t>();
};

bool Hooking::HookFunctions()
{
	if (g_GameVersion == -1)
	{
		LOG_ERROR("couldn't detected current version");
		exit(0);
		/*return true
			&& Detour_NativeRegistration.Hook("48 8B C4 48 89 58 08 48 89 68 18 48 89 70 20 48 89 50 10 57 48 83 EC 20 0F B6 C2"_Scan.as<decltype(&NativeRegistration)>(), &NativeRegistration, "NativeRegistration")
			;*/
	}
	else
	{

		//"48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 45 8B F0 41 8B F9"_Scan
		return true
			//&& Detour_System_Wait.Hook(0x4EDE34FBADD967A6_handler, System_Wait, "System_Wait")
			//&& Detour_Is_Dlc_Present.Hook(0x812595A0644CE1DE_handler, Hk_Is_Dlc_Present, "IS_DLC_PRESENT")//HK_IS_DLC_PRESENT
			//&& Detour_Is_Dlc_Present.Hook("48 89 5C 24 ? 57 48 83 EC 20 81 F9 ? ? ? ?"_Scan.as<decltype(&Hk_Is_Dlc_Present)>(), &Hk_Is_Dlc_Present, "Is DLC PRESENT");
			&& Detour_Is_Dlc_Present.Hook(" 48 83 EC 28 E8 ? ? ? ? 8A 80 ? ? ? ? 48 83 C4 28 C3 48 83 EC 28"_Scan.add(0x2C).as<decltype(&Hk_Is_Dlc_Present)>(), &Hk_Is_Dlc_Present, "Is DLC PRESENT Test")
			//&& Detour_Trigger_Script_event.Hook("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 45 8B F0 41 8B F9"_Scan.as<decltype(&Hk_Trigger_Script_event)>(), &Hk_Trigger_Script_event, "TRIGGER")
			;
	}
}

bool Hooking::UnHookFunctions()
{
	if (g_GameVersion == -1)
	{
		return true
			&& Detour_NativeRegistration.UnHook()
			&& Detour_Trigger_Script_event.UnHook();
		;
	}
	else
	{
		return true
			//&& Detour_System_Wait.UnHook()
			&& Detour_Is_Dlc_Present.UnHook();
		;
	}
}

