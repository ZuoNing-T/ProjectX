#include "Veh_Setting.h"

Veh_Settings::Veh_Settings() { }

Veh_Settings::~Veh_Settings() { }

void Veh_Settings::SetFiles(const std::string &general) {
	settingsGeneralFile = general;
}

void Veh_Settings::ReadSettings() {

	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());

	SpawnInside = settingsGeneral.GetBoolValue("OPTIONS", "SpawnInside", false);
	SpawnInplace = settingsGeneral.GetBoolValue("OPTIONS", "SpawnInplace", false);
	SpawnByName = settingsGeneral.GetBoolValue("OPTIONS", "SpawnByName", false);
	ListAllDLCs = settingsGeneral.GetBoolValue("OPTIONS", "ListAllDLCs", false);
	MergeDLCs = settingsGeneral.GetBoolValue("OPTIONS", "MergeDLCs", false);
	SearchMenu = settingsGeneral.GetBoolValue("OPTIONS", "SearchMenu", false);
	Persistent = settingsGeneral.GetBoolValue("OPTIONS", "Persistent", false);
	CategorizeMake = settingsGeneral.GetBoolValue("OPTIONS", "CategorizeMake", false);
	SearchCategory = settingsGeneral.GetLongValue("OPTIONS", "SearchCategory", 0);
}


void Veh_Settings::SaveSettings() {
	CSimpleIniA settings;
	settings.SetUnicode();
	settings.LoadFile(settingsGeneralFile.c_str());

	settings.SetBoolValue("OPTIONS", "SpawnInside", SpawnInside);
	settings.SetBoolValue("OPTIONS", "SpawnInplace", SpawnInplace);
	settings.SetBoolValue("OPTIONS", "SpawnByName", SpawnByName);
	settings.SetBoolValue("OPTIONS", "ListAllDLCs", ListAllDLCs);
	settings.SetBoolValue("OPTIONS", "MergeDLCs", MergeDLCs);
	settings.SetBoolValue("OPTIONS", "SearchMenu", SearchMenu);
	settings.SetBoolValue("OPTIONS", "Persistent", Persistent);
	settings.SetBoolValue("OPTIONS", "CategorizeMake", CategorizeMake);
	settings.SetLongValue("OPTIONS", "SearchCategory", SearchCategory);

	settings.SaveFile(settingsGeneralFile.c_str());
}
