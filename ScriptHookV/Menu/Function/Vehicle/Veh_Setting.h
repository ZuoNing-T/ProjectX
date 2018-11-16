#pragma once
#include <string>
#include "../../3rd/simpleini/SimpleIni.h"
#include <vector>

class Veh_Settings
{
public:
	Veh_Settings();
	~Veh_Settings();
	void ReadSettings();
	void SaveSettings();
	void SetFiles(const std::string &general);

	bool SpawnInside = false;
	bool SpawnByName = false;
	bool ListAllDLCs = false;
	bool MergeDLCs = false;
	bool Persistent = false;
	bool CategorizeMake = false;
	bool SpawnInplace = false;
	bool SpawnMaxed = false;
	bool SearchMenu = false;
	int SearchCategory = 0;

private:
	std::string settingsGeneralFile;
	std::string settingsMenuFile;
};
