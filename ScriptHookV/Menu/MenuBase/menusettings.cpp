#include "menusettings.h"
#include "../3rd/simpleini/SimpleIni.h"
#include "menucontrols.h"
#include "menukeyboard.h"
#include "menu.h"
#include "../../Utility/Log.h"

namespace NativeMenu {


	MenuSettings::MenuSettings() { }


	MenuSettings::~MenuSettings() { }

	void MenuSettings::SetFiles(const std::string &menu) {
		settingsMenuFile = menu;
	}

	void MenuSettings::ReadSettings(MenuControls *control, Menu *menuOpts) {
		CSimpleIniA settingsMenu;
		settingsMenu.SetUnicode();
		settingsMenu.LoadFile(settingsMenuFile.c_str());
		control->ControlKeys[MenuControls::ControlType::MenuKey] = str2key(settingsMenu.GetValue("Config", "MenuKey", "VK_F4"));
		control->ControlKeys[MenuControls::ControlType::MenuUp] = str2key(settingsMenu.GetValue("Config", "MenuUp", "NUM8"));
		control->ControlKeys[MenuControls::ControlType::MenuDown] = str2key(settingsMenu.GetValue("Config", "MenuDown", "NUM2"));
		control->ControlKeys[MenuControls::ControlType::MenuLeft] = str2key(settingsMenu.GetValue("Config", "MenuLeft", "NUM4"));
		control->ControlKeys[MenuControls::ControlType::MenuRight] = str2key(settingsMenu.GetValue("Config", "MenuRight", "NUM6"));
		control->ControlKeys[MenuControls::ControlType::MenuSelect] = str2key(settingsMenu.GetValue("Config", "MenuSelect", "NUM5"));
		control->ControlKeys[MenuControls::ControlType::MenuCancel] = str2key(settingsMenu.GetValue("Config", "MenuCancel", "NUM0"));
		menuOpts->toggle = settingsMenu.GetValue("Config", "MenuKey", "VK_F4");
		menuOpts->up = settingsMenu.GetValue("Config", "MenuUp", "NUM8");
		menuOpts->down = settingsMenu.GetValue("Config", "MenuDown", "NUM2");
		menuOpts->left = settingsMenu.GetValue("Config", "MenuLeft", "NUM4");
		menuOpts->right = settingsMenu.GetValue("Config", "MenuRight", "NUM6");
		menuOpts->select = settingsMenu.GetValue("Config", "MenuSelect", "NUM5");
		menuOpts->cancle = settingsMenu.GetValue("Config", "MenuCancel", "NUM0");
		control->ControllerButton1 = settingsMenu.GetLongValue("Project X", "ControllerButton1", -1);
		control->ControllerButton2 = settingsMenu.GetLongValue("Project X", "ControllerButton2", -1);
		menuOpts->cheatString = settingsMenu.GetValue("Project X", "CheatString", "");
		menuOpts->titlename = settingsMenu.GetValue("Project X", "TitleName", "Project X");
		menuOpts->Language = settingsMenu.GetLongValue("Project X", "Language", 0);
		menuOpts->titleTextureIndex = settingsMenu.GetLongValue("Menu", "TitleTexture", 2);
#pragma warning(push)
#pragma warning(disable: 4244)
		menuOpts->menuX = settingsMenu.GetDoubleValue("Project X", "MenuX", 0.13f);
		menuOpts->menuY = settingsMenu.GetDoubleValue("Project X", "MenuY", 0.01f);
		menuOpts->glareBool = settingsMenu.GetBoolValue("Project X", "GloableIcon", true);
#pragma warning(pop)

		// Title Text
		menuOpts->titleTextColor.R = settingsMenu.GetLongValue("Title Text", "Red", 255);
		menuOpts->titleTextColor.G = settingsMenu.GetLongValue("Title Text", "Green", 255);
		menuOpts->titleTextColor.B = settingsMenu.GetLongValue("Title Text", "Blue", 255);
		menuOpts->titleTextColor.A = settingsMenu.GetLongValue("Title Text", "Alpha", 255);
		menuOpts->titleFont = settingsMenu.GetLongValue("Title Text", "Font", 1);

		menuOpts->titleBackgroundColor.R = settingsMenu.GetLongValue("Title Rect", "Red", 255);
		menuOpts->titleBackgroundColor.G = settingsMenu.GetLongValue("Title Rect", "Green", 255);
		menuOpts->titleBackgroundColor.B = settingsMenu.GetLongValue("Title Rect", "Blue", 255);
		menuOpts->titleBackgroundColor.A = settingsMenu.GetLongValue("Title Rect", "Alpha", 255);

		menuOpts->optionsBackgroundSelectColor.R = settingsMenu.GetLongValue("Scroller", "Red", 255);
		menuOpts->optionsBackgroundSelectColor.G = settingsMenu.GetLongValue("Scroller", "Green", 255);
		menuOpts->optionsBackgroundSelectColor.B = settingsMenu.GetLongValue("Scroller", "Blue", 255);
		menuOpts->optionsBackgroundSelectColor.A = settingsMenu.GetLongValue("Scroller", "Alpha", 255);

		menuOpts->optionsTextColor.R = settingsMenu.GetLongValue("Options Text", "Red", 255);
		menuOpts->optionsTextColor.G = settingsMenu.GetLongValue("Options Text", "Green", 255);
		menuOpts->optionsTextColor.B = settingsMenu.GetLongValue("Options Text", "Blue", 255);
		menuOpts->optionsTextColor.A = settingsMenu.GetLongValue("Options Text", "Alpha", 255);
		menuOpts->optionsFont = settingsMenu.GetLongValue("Options Text", "Font", 0);

		menuOpts->optionsBackgroundColor.R = settingsMenu.GetLongValue("Options Rect", "Red", 0);
		menuOpts->optionsBackgroundColor.G = settingsMenu.GetLongValue("Options Rect", "Green", 0);
		menuOpts->optionsBackgroundColor.B = settingsMenu.GetLongValue("Options Rect", "Blue", 0);
		menuOpts->optionsBackgroundColor.A = settingsMenu.GetLongValue("Options Rect", "Alpha", 255);

		menuOpts->optionsTextSelectColor.R = settingsMenu.GetLongValue("Select Text", "Red", 0);
		menuOpts->optionsTextSelectColor.G = settingsMenu.GetLongValue("Select Text", "Green", 0);
		menuOpts->optionsTextSelectColor.B = settingsMenu.GetLongValue("Select Text", "Blue", 0);
		menuOpts->optionsTextSelectColor.A = settingsMenu.GetLongValue("Select Text", "Alpha", 0);

		menuOpts->optionsTextSelectColor.R = settingsMenu.GetLongValue("Select Rect", "Red", 255);
		menuOpts->optionsTextSelectColor.G = settingsMenu.GetLongValue("Select Rect", "Green", 255);
		menuOpts->optionsTextSelectColor.B = settingsMenu.GetLongValue("Select Rect", "Blue", 255);
		menuOpts->optionsTextSelectColor.A = settingsMenu.GetLongValue("Select Rect", "Alpha", 255);


		/*
		int markerType;
		float markerOffset;
		Vector3 mDir, mRot, mScale;
		Color mRgb;
		bool bobUpAndDown, faceCamera, rotate;
		*/
		menuOpts->markerType = settingsMenu.GetLongValue("Marker", "Type", 21);
		menuOpts->markerOffset = settingsMenu.GetDoubleValue("Marker", "Offset", 1.5f);

		menuOpts->mDir.x = settingsMenu.GetDoubleValue("Marker", "DirX", 0.0f);
		menuOpts->mDir.y = settingsMenu.GetDoubleValue("Marker", "DirY", 0.0f);
		menuOpts->mDir.z = settingsMenu.GetDoubleValue("Marker", "DirZ", 0.0f);

		menuOpts->mScale.x = settingsMenu.GetDoubleValue("Marker", "ScaleX", 1.0f);
		menuOpts->mScale.y = settingsMenu.GetDoubleValue("Marker", "ScaleY", 1.0f);
		menuOpts->mScale.z = settingsMenu.GetDoubleValue("Marker", "ScaleZ", 1.0f);

		menuOpts->mRot.x = settingsMenu.GetDoubleValue("Marker", "RotX", 180.0f);
		menuOpts->mRot.y = settingsMenu.GetDoubleValue("Marker", "RotY", 0.0f);
		menuOpts->mRot.z = settingsMenu.GetDoubleValue("Marker", "RotZ", 0.0f);

		menuOpts->mRgb.R = settingsMenu.GetLongValue("Marker", "R", 255);
		menuOpts->mRgb.G = settingsMenu.GetLongValue("Marker", "G", 255);
		menuOpts->mRgb.B = settingsMenu.GetLongValue("Marker", "B", 255);
		menuOpts->mRgb.A = settingsMenu.GetLongValue("Marker", "A", 255);

		menuOpts->bobUpAndDown = settingsMenu.GetBoolValue("Marker", "updown", true);
		menuOpts->faceCamera = settingsMenu.GetBoolValue("Marker", "faceCamera", true);
		menuOpts->rotate = settingsMenu.GetBoolValue("Marker", "rotate", true);
	}

	void MenuSettings::SaveSettings(MenuControls *control, Menu *menuOpts) {
		CSimpleIniA settingsMenu;
		SI_Error rc = settingsMenu.LoadFile(settingsMenuFile.c_str());
		if (rc < 0) LOG_MENU("Load Failed");
		settingsMenu.SetDoubleValue("Project X", "MenuX", menuOpts->menuX);
		settingsMenu.SetDoubleValue("Project X", "MenuY", menuOpts->menuY);
		settingsMenu.SetValue("Project X", "TitleName", (char*)menuOpts->titlename.c_str());
		settingsMenu.SetBoolValue("Project X", "GloableIcon", menuOpts->glareBool);
		rc = settingsMenu.SetLongValue("Project X", "TitleTexture", menuOpts->titleTextureIndex);
		settingsMenu.SetLongValue("Project X", "Language", menuOpts->Language);

		rc = settingsMenu.SetLongValue("Title Text", "Red", menuOpts->titleTextColor.R);
		rc = settingsMenu.SetLongValue("Title Text", "Green", menuOpts->titleTextColor.G);
		rc = settingsMenu.SetLongValue("Title Text", "Blue", menuOpts->titleTextColor.B);
		rc = settingsMenu.SetLongValue("Title Text", "Alpha", menuOpts->titleTextColor.A);
		rc = settingsMenu.SetLongValue("Title Text", "Font", menuOpts->titleFont);

		rc = settingsMenu.SetLongValue("Title Rect", "Red", menuOpts->titleBackgroundColor.R);
		rc = settingsMenu.SetLongValue("Title Rect", "Green", menuOpts->titleBackgroundColor.G);
		rc = settingsMenu.SetLongValue("Title Rect", "Blue", menuOpts->titleBackgroundColor.B);
		rc = settingsMenu.SetLongValue("Title Rect", "Alpha", menuOpts->titleBackgroundColor.A);
		if (rc < 0) LOG_MENU("Title Rect Load Failed");
		rc = settingsMenu.SetLongValue("Scroller", "Red", menuOpts->optionsBackgroundSelectColor.R);
		rc = settingsMenu.SetLongValue("Scroller", "Green", menuOpts->optionsBackgroundSelectColor.G);
		rc = settingsMenu.SetLongValue("Scroller", "Blue", menuOpts->optionsBackgroundSelectColor.B);
		rc = settingsMenu.SetLongValue("Scroller", "Alpha", menuOpts->optionsBackgroundSelectColor.A);
		if (rc < 0) LOG_MENU("Scroller Load Failed");
		rc = settingsMenu.SetLongValue("Options Text", "Red", menuOpts->optionsTextColor.R);
		rc = settingsMenu.SetLongValue("Options Text", "Green", menuOpts->optionsTextColor.G);
		rc = settingsMenu.SetLongValue("Options Text", "Blue", menuOpts->optionsTextColor.B);
		rc = settingsMenu.SetLongValue("Options Text", "Alpha", menuOpts->optionsTextColor.A);
		rc = settingsMenu.SetLongValue("Options Text", "Font", menuOpts->optionsFont);

		rc = settingsMenu.SetLongValue("Options Rect", "Red", menuOpts->optionsBackgroundColor.R);
		rc = settingsMenu.SetLongValue("Options Rect", "Green", menuOpts->optionsBackgroundColor.G);
		rc = settingsMenu.SetLongValue("Options Rect", "Blue", menuOpts->optionsBackgroundColor.B);
		rc = settingsMenu.SetLongValue("Options Rect", "Alpha", menuOpts->optionsBackgroundColor.A);

		rc = settingsMenu.SetLongValue("Select Rect", "Red", menuOpts->optionsTextSelectColor.R);
		rc = settingsMenu.SetLongValue("Select Rect", "Green", menuOpts->optionsTextSelectColor.G);
		rc = settingsMenu.SetLongValue("Select Rect", "Blue", menuOpts->optionsTextSelectColor.B);
		rc = settingsMenu.SetLongValue("Select Rect", "Alpha", menuOpts->optionsTextSelectColor.A);

		rc = settingsMenu.SetLongValue("Select Text", "Red", menuOpts->optionsTextSelectColor.R);
		rc = settingsMenu.SetLongValue("Select Text", "Green", menuOpts->optionsTextSelectColor.G);
		rc = settingsMenu.SetLongValue("Select Text", "Blue", menuOpts->optionsTextSelectColor.B);
		rc = settingsMenu.SetLongValue("Select Text", "Alpha", menuOpts->optionsTextSelectColor.A);

		//optionbackground
		//°´¼üÉè¶¨
		settingsMenu.SetValue("Config", "MenuKey", (char*)key2str(control->ControlKeys[MenuControls::ControlType::MenuKey]).c_str());
		settingsMenu.SetValue("Config", "MenuUp", (char*)key2str(control->ControlKeys[MenuControls::ControlType::MenuUp]).c_str());
		settingsMenu.SetValue("Config", "MenuDown", (char*)key2str(control->ControlKeys[MenuControls::ControlType::MenuDown]).c_str());
		settingsMenu.SetValue("Config", "MenuLeft", (char*)key2str(control->ControlKeys[MenuControls::ControlType::MenuLeft]).c_str());
		settingsMenu.SetValue("Config", "MenuRight", (char*)key2str(control->ControlKeys[MenuControls::ControlType::MenuRight]).c_str());
		settingsMenu.SetValue("Config", "MenuSelect", (char*)key2str(control->ControlKeys[MenuControls::ControlType::MenuSelect]).c_str());
		settingsMenu.SetValue("Config", "MenuCancel", (char*)key2str(control->ControlKeys[MenuControls::ControlType::MenuCancel]).c_str());

		settingsMenu.SetLongValue("Marker", "Type", menuOpts->markerType);
		settingsMenu.SetDoubleValue("Marker", "Offset", menuOpts->markerOffset);

		settingsMenu.SetDoubleValue("Marker", "DirX", menuOpts->mDir.x);
		settingsMenu.SetDoubleValue("Marker", "DirY", menuOpts->mDir.y);
		settingsMenu.SetDoubleValue("Marker", "DirZ", menuOpts->mDir.z);

		settingsMenu.SetDoubleValue("Marker", "ScaleX", menuOpts->mScale.x);
		settingsMenu.SetDoubleValue("Marker", "ScaleY", menuOpts->mScale.y);
		settingsMenu.SetDoubleValue("Marker", "ScaleZ", menuOpts->mScale.z);

		settingsMenu.SetDoubleValue("Marker", "RotX", menuOpts->mRot.x);
		settingsMenu.SetDoubleValue("Marker", "RotY", menuOpts->mRot.y);
		settingsMenu.SetDoubleValue("Marker", "RotZ", menuOpts->mRot.z);

		settingsMenu.SetLongValue("Marker", "R", menuOpts->mRgb.R);
		settingsMenu.SetLongValue("Marker", "G", menuOpts->mRgb.G);
		settingsMenu.SetLongValue("Marker", "B", menuOpts->mRgb.B);
		settingsMenu.SetLongValue("Marker", "A", menuOpts->mRgb.A);

		settingsMenu.SetBoolValue("Marker", "updown", menuOpts->bobUpAndDown);
		settingsMenu.SetBoolValue("Marker", "faceCamera", menuOpts->faceCamera);
		settingsMenu.SetBoolValue("Marker", "rotate", menuOpts->rotate);

		rc = settingsMenu.SaveFile(settingsMenuFile.c_str());
		if (rc < 0) LOG_MENU("file saved Failed");
		//LOG_PRINT("");
	}
	//TODO:Need to rework on it 
	//void MenuSettings::CustomKeys(std::string keyname, MenuControls::ControlType type, MenuControls *control)
	//{
	//	control->ControlKeys[type] = str2key(keyname);
	//}

	void MenuSettings::CustomKeys(std::string keyname, MenuControls::ControlType type, MenuControls *control)
	{
		control->ControlKeys[type] = str2key(keyname);
	}
}