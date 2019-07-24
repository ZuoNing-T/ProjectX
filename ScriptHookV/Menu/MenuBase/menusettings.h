#pragma once
#include <vector>
#include <string>
#include "menucontrols.h"
namespace NativeMenu {
class MenuControls;
class Menu;

class MenuSettings
{
public:
	MenuSettings();
	~MenuSettings();
	void ReadSettings(MenuControls *control, Menu *menuOpts);
	void SaveSettings(MenuControls *control, Menu *menuOpts);
	void SetFiles(const std::string &menu);
	void CustomKeys(std::string keyname, MenuControls::ControlType type, MenuControls *control);
private:
	std::string settingsMenuFile;
};
}
