#pragma once

#include <string>
#include "../MenuBase/menu.h"


void WINAPI  ScriptMain();


extern NativeMenu::Menu menu;
extern NativeMenu::MenuControls controls;

bool TogglePress();

inline void addTitle(std::string titlename)
{
	menu.Title(menu.Custom ? "" : "Project X V2");
	menu.Subtitle(titlename);
}