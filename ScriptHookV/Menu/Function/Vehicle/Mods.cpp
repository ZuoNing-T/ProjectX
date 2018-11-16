#include "Mods.h"
#include "../../internal_native.h"
#include "../Function.h"
#include "Veh_Setting.h"
#include "VehHash.h"
#include "Vehicle.h"
#include "../../ScriptHookV.h"
#include "../../MenuBase/menu.h"
#include "../../MenuBase/menuutils.h"
#include "../../Menu/UI/Script.h"
#include "../keyboard.h"
#include "../../3rd/tinystr.h"
#include "../../3rd/tinyxml.h"
#include "../../3rd/json.hpp"
extern std::string settingsMenuFile;
#pragma region Basic Function Needs
Object AttachObjectToVehicleByHash(Hash hash, float x, float y, float z, float rotx, float roty, float rotz, Vehicle veh) {

	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash)) {
		STREAMING::REQUEST_MODEL(hash);
		while (!STREAMING::HAS_MODEL_LOADED(hash)) WAIT(0);
		Vector3 co = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		Object obj = OBJECT::CREATE_OBJECT_NO_OFFSET(hash, co.x, co.y, co.z, 1, 0, 0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(obj);
		ENTITY::FREEZE_ENTITY_POSITION(obj, 1);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(obj, veh, 0, x, y, z, rotx, roty, rotz, 1, 0, 1, 0, 2, 1);
		return obj;
	}
	else {
		LOG_PRINT("Invaild Model %d", hash);
		return -1;
	}
}
Vehicle SpawnVehicleH(DWORD model, Vector3 coords, bool tpinto = 0, float heading = 0.0f) {
	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model)) {
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
		Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, 1, 1);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
		if (tpinto) {
			ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
		}
		//VEHICLE::SET_VEHICLE_IS_STOLEN(veh, 0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		return veh;

	}
	return -1;
}


#pragma endregion

#pragma region Ini Section
void LoadIniVeh(std::string name)
{
	std::string path = settingsMenuFile + "\\Mod Vehicle\\Ini Mod\\" + name;
	LOG_PRINT("Start to load %s", name.c_str());
	CSimpleIniA Mod;
	CSimpleIniA::TNamesDepend sections;
	Mod.SetUnicode();
	Mod.LoadFile(path.c_str());
	Mod.GetAllSections(sections);
	CSimpleIni::TNamesDepend::const_iterator iSection = sections.begin();
	const char *pszSection;
	const char *pItem;
	const char *pszVal;
	Vehicle veh;

#pragma region ELUSIVE Section
	if (std::strcmp(Mod.GetValue("0", "Model", "Elusive"), "Elusive"))
	{
		//LOG_PRINT("get Elusive Type");
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		NativeMenu::Color tyre, neon;
		Hash Model = static_cast<DWORD>(atoll(Mod.GetValue("Vehicle", "Model")));
		int primary = atoi(Mod.GetValue("Vehicle", "PrimaryPaint", "255"));
		int secondary = atoi(Mod.GetValue("Vehicle", "SecondaryPaint", "255"));
		tyre.R = atoi(Mod.GetValue("Vehicle", "SmokeR", "255"));
		tyre.G = atoi(Mod.GetValue("Vehicle", "SmokeG", "255"));
		tyre.B = atoi(Mod.GetValue("Vehicle", "SmokeB", "255"));
		int whelltype = atoi(Mod.GetValue("Vehicle", "WheelsType", "0"));
		neon.R = atoi(Mod.GetValue("Vehicle", "NeonR", "255"));
		neon.G = atoi(Mod.GetValue("Vehicle", "NeonG", "255"));
		neon.B = atoi(Mod.GetValue("Vehicle", "NeonB", "255"));
		std::string text = Mod.GetValue("Vehicle", "PlateText", "PRJ");
		float dirlvl = atof(Mod.GetValue("Vehicle", "dirt level", "0"));
		veh = (Model, ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, 5, 0), 1);
		RequestControlOfEnt(veh);
		VEHICLE::SET_VEHICLE_COLOURS(veh, primary, secondary);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, tyre.R, tyre.G, tyre.B);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, neon.R, neon.G, neon.B);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, (char*)text.c_str());
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, dirlvl);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, whelltype);
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, 0);
		WAIT(10);

		for (; iSection != sections.end(); ++iSection)
		{
			pszSection = iSection->pItem;
			if (!std::strcmp(pszSection, "Vehicle"))
			{
				continue;
			}
			Hash ObjModel = static_cast<DWORD>(atoll(Mod.GetValue(pszSection, "model")));
			float xoffset = atof(Mod.GetValue(pszSection, "X"));
			float yoffset = atof(Mod.GetValue(pszSection, "Y"));
			float zoffset = atof(Mod.GetValue(pszSection, "Z"));
			float pitch = atof(Mod.GetValue(pszSection, "RotX"));
			float roll = atof(Mod.GetValue(pszSection, "RotY"));
			float yaw = atof(Mod.GetValue(pszSection, "RotZ"));
			int collision = atoi(Mod.GetValue(pszSection, "collision", "0"));
			//LOG_DEBUG(Mod.GetValue(pszSection, "Model"));
			AttachObjectToVehicleByHash(ObjModel, xoffset, yoffset, zoffset, pitch, roll, yaw, veh);
		}
	}
#pragma endregion
#pragma region Jordan D3SK1NG NIGGER Type
	else
	{
		//	LOG_PRINT("Jordan Type");

		NativeMenu::Color tyre, neon;
		Hash Model = static_cast<DWORD>(atoll(Mod.GetValue("Vehicle", "model")));
		int primary = atoi(Mod.GetValue("Vehicle", "primary paint", "255"));
		int secondary = atoi(Mod.GetValue("Vehicle", "secondary paint", "255"));
		tyre.R = atoi(Mod.GetValue("Vehicle", "tyre smoke red", "255"));
		tyre.G = atoi(Mod.GetValue("Vehicle", "tyre smoke green", "255"));
		tyre.B = atoi(Mod.GetValue("Vehicle", "tyre smoke blue", "255"));
		int whelltype = atoi(Mod.GetValue("Vehicle", "wheel colour", "0"));
		neon.R = atoi(Mod.GetValue("Vehicle", "neon red", "255"));
		neon.G = atoi(Mod.GetValue("Vehicle", "neon grenn", "255"));
		neon.B = atoi(Mod.GetValue("Vehicle", "neon blue", "255"));
		std::string text = Mod.GetValue("Vehicle", "plate text", "PRJ");
		float dirlvl = atof(Mod.GetValue("Vehicle", "dirt level"));
		veh = SpawnVehicleH(Model, ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, 5, 0), 1);
		RequestControlOfEnt(veh);
		VEHICLE::SET_VEHICLE_COLOURS(veh, primary, secondary);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, tyre.R, tyre.G, tyre.B);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, neon.R, neon.G, neon.B);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, (char*)text.c_str());
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, dirlvl);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, whelltype);
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, 0);
		WAIT(10);
		for (; iSection != sections.end(); ++iSection)
		{
			pszSection = iSection->pItem;
			std::string sec = pszSection;
			if (!std::strcmp(pszSection, "Vehicle"))
			{
				continue;
			}
			if (sec.find("Attached Object") != -1)
			{
				Hash ObjModel = static_cast<DWORD>(atoll(Mod.GetValue(pszSection, "model")));
				//	LOG_DEBUG("Object Modle %lld", ObjModel);
				float xoffset = atof(Mod.GetValue(pszSection, "x offset"));
				float yoffset = atof(Mod.GetValue(pszSection, "y offset"));
				float zoffset = atof(Mod.GetValue(pszSection, "z offset"));
				float pitch = atof(Mod.GetValue(pszSection, "pitch"));
				float roll = atof(Mod.GetValue(pszSection, "roll"));
				float yaw = atof(Mod.GetValue(pszSection, "yaw"));
				int collision = atoi(Mod.GetValue(pszSection, "collision"));
				//LOG_PRINT(Mod.GetValue(pszSection, "model name"));
				AttachObjectToVehicleByHash(ObjModel, xoffset, yoffset, zoffset, pitch, roll, yaw, veh);
			}
			WAIT(0);

		}

	}
#pragma endregion
}
#pragma endregion


#pragma region XML Section
TiXmlDocument XMLMod;
TiXmlElement * rootElement;
TiXmlElement * firstElement;
Hash ModelHash;
char *endptr;
Vector3 VehBonePos;
Vehicle veh;
Hash ObjModel;
int modeltype = 0;
int BoneIndex = 0;
int InitHandle;
std::map <int, Object> ObjectPool;

void LoadXmlVeh(std::string name)
{
	std::string xmlPath = settingsMenuFile + "\\Mod Vehicle\\Xml Mod\\" + name;
	LOG_PRINT("Load File Path:%s", xmlPath);
	LOG_PRINT("Start to load XML MOD Vehicle \t FileName: %s", (char*)name.c_str());

	if (XMLMod.LoadFile((char*)xmlPath.c_str()))
	{
		ObjectPool.clear();//Clean up Create Object Pool
						   //指向 <Vehicle>
		rootElement = XMLMod.RootElement();
		//LOG_PRINT("Root Value:%s", rootElement->Value());

		//指向 <Model Hash>
		firstElement = rootElement->FirstChild("ModelHash")->ToElement();
		//LOG_DEBUG("Get Mod Hash:%s", firstElement->GetText());
		ModelHash = atoi(firstElement->GetText());
		LOG_DEBUG("Model Dec Hash:%d", ModelHash);
		//static_cast<DWORD>(atoll());//获取 ModelHash 载具用
		veh = SpawnVehicleH(ModelHash, ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, 5, 0), 1);
		LOG_DEBUG("is Visible :%s", rootElement->FirstChild("IsVisible")->ToElement()->GetText());
		if (!strcmp(rootElement->FirstChild("IsVisible")->ToElement()->GetText(), "true"))
			ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
		else
			ENTITY::SET_ENTITY_VISIBLE(veh, false, 0);
		ENTITY::SET_ENTITY_ALPHA(veh, atoi(rootElement->FirstChild("OpacityLevel")->ToElement()->GetText()), 0);//设置隐形
																												//IsVisible
		if (rootElement->Attribute("menyoo_ver") != nullptr)
		{
			InitHandle = atoi(rootElement->FirstChild("InitialHandle")->ToElement()->GetText());
		}
		else
		{
			InitHandle = veh;
		}

		ObjectPool.insert(std::pair<int, Object>(InitHandle, veh));
		RequestControlOfEnt(veh);
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, 0);
		WAIT(10);
		TiXmlHandle XmlHandle(&XMLMod);
		TiXmlElement *AttachObj = XmlHandle.FirstChild("Vehicle").FirstChild("SpoonerAttachments").FirstChild("Attachment").ToElement();
		while (AttachObj != NULL)//Start Attach Object
		{

			ObjModel = atoi(AttachObj->FirstChild("ModelHash")->ToElement()->GetText());//?

			BoneIndex = atoi(AttachObj->FirstChild("Attachment")->FirstChild("BoneIndex")->ToElement()->GetText());

			VehBonePos = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(veh, BoneIndex); //获取到世界坐标

			int ObjHandle = atoi(AttachObj->FirstChild("InitialHandle")->ToElement()->GetText());

			//ObjModel = $(AttachObj->FirstChild("HashName")->ToElement()->GetText());
			float xoffset = atof(AttachObj->FirstChild("Attachment")->FirstChild("X")->ToElement()->GetText());
			float yoffset = atof(AttachObj->FirstChild("Attachment")->FirstChild("Y")->ToElement()->GetText());
			float zoffset = atof(AttachObj->FirstChild("Attachment")->FirstChild("Z")->ToElement()->GetText());
			float pitch = atof(AttachObj->FirstChild("Attachment")->FirstChild("Pitch")->ToElement()->GetText());
			float roll = atof(AttachObj->FirstChild("Attachment")->FirstChild("Roll")->ToElement()->GetText());
			float yaw = atof(AttachObj->FirstChild("Attachment")->FirstChild("Yaw")->ToElement()->GetText());
			int collision = 0;
			modeltype = atoi(AttachObj->FirstChild("Type")->ToElement()->GetText());
			Object obj;
			//TODO:something wrong with request Model
			if (STREAMING::IS_MODEL_IN_CDIMAGE(ObjModel)) {
				if (STREAMING::IS_MODEL_VALID(ObjModel))
				{
					LOG_PRINT("Model is vaild, %s", AttachObj->FirstChild("HashName")->ToElement()->GetText());
				}
				else
				{
					ObjModel = $(AttachObj->FirstChild("HashName")->ToElement()->GetText());
				}
				STREAMING::REQUEST_MODEL(ObjModel);
				while (!STREAMING::HAS_MODEL_LOADED(ObjModel)) WAIT(0);
				switch (modeltype)
				{
				case 1:
					obj = PED::CREATE_PED(26, ObjModel, VehBonePos.x, VehBonePos.y, VehBonePos.z, 0.0f, false, false);
					LOG_DEBUG("Create Ped");
					break;
				case 2:
					obj = VEHICLE::CREATE_VEHICLE(ObjModel, VehBonePos.x, VehBonePos.y, VehBonePos.z, 0.0f, false, false);
					LOG_DEBUG("Create Vehicle");
					break;
				case 3:
					LOG_DEBUG("Create Object");
					obj = OBJECT::CREATE_OBJECT_NO_OFFSET(ObjModel, VehBonePos.x, VehBonePos.y, VehBonePos.z, 0, 0, 0);//通过载具骨骼创建
					break;
				default:
					LOG_DEBUG("Unknown Entities");
					break;
				}
				ENTITY::SET_ENTITY_VISIBLE(obj, String2Bool(AttachObj->FirstChild("IsVisible")->ToElement()->GetText()), 0);
				ENTITY::SET_ENTITY_ALPHA(obj, atoi(AttachObj->FirstChild("OpacityLevel")->ToElement()->GetText()), 0);//设置隐形
				LOG_DEBUG("Alpha:%s", AttachObj->FirstChild("OpacityLevel")->ToElement()->GetText());
			}
			else {
				LOG_PRINT("Invaild Model %s", ObjModel);
			}
			ObjectPool.insert(std::pair<int, Object>(ObjHandle, obj));
			if (AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence") != nullptr)
			{
				Vector3 RelativePosition, RelativeRotation;
				NativeMenu::Color FxCol;
				std::string AssetName = AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("AssetName")->ToElement()->GetText();
				std::string EffectName = AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("EffectName")->ToElement()->GetText();
				float Scale = atof(AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("Scale")->ToElement()->GetText());
				FxCol.R = (float)atoi(AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("Colour")->ToElement()->Attribute("R"));
				FxCol.G = (float)atoi(AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("Colour")->ToElement()->Attribute("G"));
				FxCol.B = (float)atoi(AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("Colour")->ToElement()->Attribute("B"));
				FxCol.A = (float)atoi(AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("Colour")->ToElement()->Attribute("A"));

				RelativePosition.x = (float)atoi(AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("RelativePosition")->ToElement()->Attribute("X"));
				RelativePosition.y = (float)atoi(AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("RelativePosition")->ToElement()->Attribute("Y"));
				RelativePosition.z = (float)atoi(AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("RelativePosition")->ToElement()->Attribute("Z"));

				RelativeRotation.x = (float)atoi(AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("RelativeRotation")->ToElement()->Attribute("X"));
				RelativeRotation.y = (float)atoi(AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("RelativeRotation")->ToElement()->Attribute("Y"));
				RelativeRotation.z = (float)atoi(AttachObj->FirstChild("Attachment")->FirstChild("TaskSequence")->FirstChild("Task")->FirstChild("RelativeRotation")->ToElement()->Attribute("Z"));


				STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)AssetName.c_str());
				STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)EffectName.c_str());
				while (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED((char*)EffectName.c_str()))
				{
					WAIT(0);
				}
				GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)EffectName.c_str());
				int ptfxHandle = GRAPHICS::_START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE((char*)EffectName.c_str(), obj, 0, 0, 0, 0, 0, 0, BoneIndex, Scale, 0, 0, 0);
				GRAPHICS::SET_PARTICLE_FX_LOOPED_COLOUR(ptfxHandle, FxCol.R, FxCol.G, FxCol.B, true);
			}
			int AttachTo;
			if (rootElement->Attribute("menyoo_ver") != nullptr)
			{
				AttachTo = atoi(AttachObj->FirstChild("Attachment")->FirstChild("AttachedTo")->ToElement()->GetText());
			}
			else
			{
				AttachTo = veh;
			}


			std::map <int, Object>::iterator it_find;
			it_find = ObjectPool.find(AttachTo);
			if (it_find != ObjectPool.end())
			{
				veh = it_find->second;
			}
			else
			{
				LOG_DEBUG("Invaild Handle!");
			}
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(obj);
			ENTITY::FREEZE_ENTITY_POSITION(obj, 1);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(obj, veh, BoneIndex, xoffset, yoffset, zoffset, pitch, roll, yaw, 1, 0, 0, 2, 0, 1);


			/*STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheist");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL("scr_agencyheist");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_fbi_dd_breach_smoke", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, 0.2f, 0, 0, 0);
			GRAPHICS::START_PARTICLE_FX_LOOPED_ON_ENTITY();*/

			//0 = no entity
			//	1 = ped
			//	2 = vehicle
			//	3 = object
			WAIT(0);
			AttachObj = AttachObj->NextSiblingElement();
		}
		//LOG_PRINT("Attach Complete!");
		showNotification((char*)("Load Complete!" + xmlPath).c_str());
	}
	else
	{
		showNotification("XML File is invaild!");
	}
}
#pragma endregion

#pragma region Json Section
//int i = 0;
int EntitiesNum = 0, EntCount = 0;
std::string AutherName;

std::map<int, Object> AttachPool;

void LoadJsonVehilceData(const nlohmann::json &json, std::string entitiesnum, VehilceData * Data)
{
	Data->hash = json[entitiesnum]["Entity Hash"].get<Hash>(); // Get Entities Hash
	Data->initHandle = json[entitiesnum]["Initial Handle"].get<Hash>();//To Get Init Handle
	Data->HasParents = json[entitiesnum]["Attachments"]["Has Parent"].get<bool>();
	if (Data->HasParents)
	{
		Data->AttachTo.Bone = json[entitiesnum]["Attachments"]["Bone"].get<std::string>();
		Data->AttachTo.ParentsId = json[entitiesnum]["Attachments"]["Parent ID"].get<int>();

		Data->AttachTo.Position.x = json[entitiesnum]["Attachments"]["Position"][0].get<float>();
		Data->AttachTo.Position.y = json[entitiesnum]["Attachments"]["Position"][1].get<float>();
		Data->AttachTo.Position.z = json[entitiesnum]["Attachments"]["Position"][2].get<float>();

		Data->AttachTo.Rot.Pitch = json[entitiesnum]["Attachments"]["Rotation"][0].get<float>();
		Data->AttachTo.Rot.Roll = json[entitiesnum]["Attachments"]["Rotation"][1].get<float>();
		Data->AttachTo.Rot.Yaw = json[entitiesnum]["Attachments"]["Rotation"][2].get<float>();
	}
	Data->name = json[entitiesnum]["Display Name"].get<std::string>();
	Data->hash = json[entitiesnum]["Entity Hash"].get<Hash>();
	Data->type = json[entitiesnum]["Entity Type"].get<std::string>();

	Data->initHandle = json[entitiesnum]["Initial Handle"].get<int>();
	Data->BasicProper.Collision = json[entitiesnum]["Properties"]["Collision"].get<bool>();
	Data->BasicProper.Dynamic = json[entitiesnum]["Properties"]["Dynamic"].get<bool>();
	Data->BasicProper.Frozen = json[entitiesnum]["Properties"]["Frozen"].get<bool>();
	Data->BasicProper.OpacityLevel = json[entitiesnum]["Properties"]["Opacity Level"].get<int>();
	Data->BasicProper.Visible = json[entitiesnum]["Properties"]["Visible"].get<bool>();

	Data->VehicleProper.Pearlescent = json[entitiesnum]["Vehicle Properties"]["Colour"]["Pearlescent"].get<int>();
	Data->VehicleProper.Primary = json[entitiesnum]["Vehicle Properties"]["Colour"]["Primary"].get<int>();
	Data->VehicleProper.Secondary = json[entitiesnum]["Vehicle Properties"]["Colour"]["Secondary"].get<int>();
	Data->VehicleProper.WheelCol = json[entitiesnum]["Vehicle Properties"]["Colour"]["Wheel Colour"].get<int>();

	for (int i = 0; i < 48; i++)
	{
		Data->VehicleProper.VehMod[i] = json[entitiesnum]["Vehicle Properties"]["Mods"][i].get<int>();
	}
	Data->VehicleProper.Platename = json[entitiesnum]["Vehicle Properties"]["Plate"]["Text"].get<std::string>();
	Data->VehicleProper.PlateType = json[entitiesnum]["Vehicle Properties"]["Plate"]["Index"].get<int>();

	Data->VehicleProper.tyre.Burst = (bool)json[entitiesnum]["Vehicle Properties"]["Tyre"]["Can Burst"].get<int>();
	Data->VehicleProper.tyre.Smoke.R = json[entitiesnum]["Vehicle Properties"]["Tyre"]["Smoke Colour"]["R"].get<int>();
	Data->VehicleProper.tyre.Smoke.G = json[entitiesnum]["Vehicle Properties"]["Tyre"]["Smoke Colour"]["G"].get<int>();
	Data->VehicleProper.tyre.Smoke.B = json[entitiesnum]["Vehicle Properties"]["Tyre"]["Smoke Colour"]["B"].get<int>();
	Data->VehicleProper.tyre.Type = json[entitiesnum]["Vehicle Properties"]["Tyre"]["Wheel Type"].get<int>();

	Data->VehicleProper.WindowTint = json[entitiesnum]["Vehicle Properties"]["Window Tint"].get<int>();
}
bool SpawnVehicle(VehilceData Data, Vehicle * target)
{

	if (STREAMING::IS_MODEL_VALID(Data.hash))
	{
		STREAMING::REQUEST_MODEL(Data.hash);
		while (!STREAMING::HAS_MODEL_LOADED(Data.hash))WAIT(0);//Fuck 
		Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		float forward = 5.f;
		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		float xVector = forward * sin(degToRad(heading)) * -1.f;
		float yVector = forward * cos(degToRad(heading));
		*target = VEHICLE::CREATE_VEHICLE(Data.hash, ourCoords.x + xVector, ourCoords.y + yVector, ourCoords.z, heading, true, true);
		RequestControlOfEnt(*target);
		VEHICLE::SET_VEHICLE_ENGINE_ON(*target, true, true, true);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(*target);
		auto networkId = NETWORK::VEH_TO_NET(*target);
		ENTITY::_SET_ENTITY_SOMETHING(*target, true);
		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(*target))
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
		WAIT(150);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Data.hash);
		return true;
	}
	else
	{
		LOG_PRINT("%u is not a vaild model", Data.hash);
		*target = -1;
		return false;
	}
	return true;
}
void DecorateVehicle(VehilceData Data)
{
	Vehicle  targetVeh;
	if (SpawnVehicle(Data, &targetVeh))
		if (targetVeh != -1)
		{
			AttachPool.insert(std::pair<int, Object>(Data.initHandle, targetVeh));//To Load Attach Vehilce
			ENTITY::SET_ENTITY_COLLISION(targetVeh, Data.BasicProper.Collision, false);
			VEHICLE::SET_VEHICLE_IS_STOLEN(targetVeh, !Data.BasicProper.Driveable);
			ENTITY::SET_ENTITY_DYNAMIC(targetVeh, Data.BasicProper.Dynamic);
			ENTITY::FREEZE_ENTITY_POSITION(targetVeh, Data.BasicProper.Frozen);
			ENTITY::SET_ENTITY_ALPHA(targetVeh, Data.BasicProper.OpacityLevel, false);
			ENTITY::SET_ENTITY_VISIBLE(targetVeh, Data.BasicProper.Visible, false);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(targetVeh, Data.VehicleProper.Pearlescent, Data.VehicleProper.WheelCol);
			VEHICLE::SET_VEHICLE_COLOURS(targetVeh, Data.VehicleProper.Primary, Data.VehicleProper.Secondary);
			for (int i = 0; i < 48; i++)
			{
				VEHICLE::SET_VEHICLE_MOD_KIT(targetVeh, Data.VehicleProper.VehMod[i]);
			}
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(targetVeh, (char*)Data.VehicleProper.Platename.c_str());//What????
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(targetVeh, Data.VehicleProper.PlateType);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(targetVeh, Data.VehicleProper.tyre.Burst);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(targetVeh, Data.VehicleProper.tyre.Smoke.R, Data.VehicleProper.tyre.Smoke.G, Data.VehicleProper.tyre.Smoke.B);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(targetVeh, Data.VehicleProper.tyre.Type);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(targetVeh, Data.VehicleProper.WindowTint);
			LOG_PRINT("Load Complete!");
		}
}
void LoadJsonObjectData(const nlohmann::json & json, std::string entitiesnum, ObjectData * Data)
{
	Data->hash = json[entitiesnum]["Entity Hash"].get<Hash>(); // Get Entities Hash

	Data->initHandle = json[entitiesnum]["Initial Handle"].get<int>();//To Get Init Handle

	if (json[entitiesnum]["Attachments"]["Has Parent"].get<bool>())
	{
		Data->AttachTo.Bone = json[entitiesnum]["Attachments"]["Bone"].get<std::string>();
		Data->AttachTo.ParentsId = json[entitiesnum]["Attachments"]["Parent ID"].get<int>();
		Data->AttachTo.Position.x = json[entitiesnum]["Attachments"]["Position"][0].get<float>();
		Data->AttachTo.Position.y = json[entitiesnum]["Attachments"]["Position"][1].get<float>();
		Data->AttachTo.Position.z = json[entitiesnum]["Attachments"]["Position"][2].get<float>();
		Data->AttachTo.Rot.Pitch = json[entitiesnum]["Attachments"]["Rotation"][0].get<float>();
		Data->AttachTo.Rot.Roll = json[entitiesnum]["Attachments"]["Rotation"][1].get<float>();
		Data->AttachTo.Rot.Yaw = json[entitiesnum]["Attachments"]["Rotation"][2].get<float>();
	}
	Data->name = json[entitiesnum]["Display Name"].get<std::string>();
	Data->Propname = json[entitiesnum]["Prop Name"].get<std::string>();

	Data->type = json[entitiesnum]["Entity Type"].get<std::string>();

	Data->initHandle = json[entitiesnum]["Initial Handle"].get<int>();
	Data->BasicProper.Collision = json[entitiesnum]["Properties"]["Collision"].get<bool>();
	Data->BasicProper.Dynamic = json[entitiesnum]["Properties"]["Dynamic"].get<bool>();
	Data->BasicProper.Frozen = json[entitiesnum]["Properties"]["Frozen"].get<bool>();
	Data->BasicProper.OpacityLevel = json[entitiesnum]["Properties"]["Opacity Level"].get<int>();
	Data->BasicProper.Visible = json[entitiesnum]["Properties"]["Visible"].get<bool>();

}

bool SpawnObject(ObjectData Data, Object * Obj)
{
	*Obj = -1;
	if (STREAMING::IS_MODEL_IN_CDIMAGE(Data.hash)) {
		STREAMING::REQUEST_MODEL(Data.hash);
		while (!STREAMING::HAS_MODEL_LOADED(Data.hash)) WAIT(0);
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(0), 1);
		*Obj = OBJECT::CREATE_OBJECT(Data.hash, pos.x + 5.0f, pos.y + 5.0f, pos.z, true, 1, 0);
		return true;
	}
	return false;
}

void DecorateObject(ObjectData Data)
{
	Object tarObj;
	if (SpawnObject(Data, &tarObj))
	{
		if (tarObj != -1)
		{
			ENTITY::SET_ENTITY_COLLISION(tarObj, Data.BasicProper.Collision, false);
			VEHICLE::SET_VEHICLE_IS_STOLEN(tarObj, !Data.BasicProper.Driveable);
			ENTITY::SET_ENTITY_DYNAMIC(tarObj, Data.BasicProper.Dynamic);
			ENTITY::FREEZE_ENTITY_POSITION(tarObj, Data.BasicProper.Frozen);
			ENTITY::SET_ENTITY_ALPHA(tarObj, Data.BasicProper.OpacityLevel, false);
			ENTITY::SET_ENTITY_VISIBLE(tarObj, Data.BasicProper.Visible, false);
			AttachPool.insert(std::pair<int, Object>(Data.initHandle, tarObj));
		}
	}
	else
	{
		LOG_PRINT("Object Load Failed");
	}
}

int FindObject(int Handle)
{
	std::map <int, Object>::iterator it_find;
	it_find = AttachPool.find(Handle);
	if (it_find != AttachPool.end())
	{
		return it_find->second;
	}
	else
	{
		LOG_DEBUG("Invaild Handle!");
		return -1;
	}
}

template <typename T>
void AttachEntity(T Objectdata)
{

	if (Objectdata.HasParents)
	{
		Vehicle ToAttached = -1;
		Object Attach = -1337;
		ToAttached = FindObject(Objectdata.AttachTo.ParentsId);

		Attach = FindObject(Objectdata.initHandle);

		//AttachPool.find(data.AttachTo.ParentsId)->second;//Current Object
		if (ToAttached != -1 && Attach != -1)
		{
			int Boneindex = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(
				ToAttached,
				(char*)Objectdata.AttachTo.Bone.c_str());

			ENTITY::ATTACH_ENTITY_TO_ENTITY(
				Attach,//Object
				ToAttached,//Vehicle
				Boneindex,
				Objectdata.AttachTo.Position.x,
				Objectdata.AttachTo.Position.y,
				Objectdata.AttachTo.Position.z,
				Objectdata.AttachTo.Rot.Pitch,
				Objectdata.AttachTo.Rot.Roll,
				Objectdata.AttachTo.Rot.Yaw,
				1, 0, 0, 2, 1, 1);
		}
		else
		{
			LOG_PRINT("something Wrong with initHandle Veh:%d Object %d", ToAttached, Attach);
		}
	}
}

EntType JsonGetType(std::string type)
{
	if ("vehicle" == type)
		return vehicle;
	if ("ped" == type)
		return ped;
	if ("object" == type)
		return object;

	return no_entity;
}

void LoadJsonVeh(std::string name)
{
	nlohmann::json JsonVehicle;
	std::string JsonVehFile = settingsMenuFile + "\\Mod Vehicle\\Json Mod" + name;
	std::ifstream in(JsonVehFile);
	in >> JsonVehicle;
	EntCount = JsonVehicle["Other"]["Entity Count"].get<int>();
	AutherName = JsonVehicle["Headers"]["Author"].get<std::string>();
	EntType PropType;
#pragma region Basic Show notifycation
	showNotification(
		("Auther:" + AutherName + "\n Entities count: " + std::to_string(EntCount)).c_str()
	);
#pragma endregion
#pragma region Load Basic Proper

	AttachPool.clear();
	EntitiesNum = 0;
	for (int i = 0;
		i < 1000
		; i++)
	{
		VehilceData MyVehilce;
		ObjectData toSpawn;

		if (!JsonVehicle["entity_" + std::to_string(i)].is_null())//To Judge entity is exist
		{

			LOG_PRINT(("\n entity_" + std::to_string(i) + ":\n" + JsonVehicle["entity_" + std::to_string(i)]["Display Name"].get<std::string>()).c_str());
			JsonVehicle["entity_" + std::to_string(i)]["Attachments"]["Has Parent"].get<bool>();
			std::string entityname = "entity_" + std::to_string(i);
			switch (JsonGetType(JsonVehicle[entityname]["Entity Type"].get<std::string>()))
			{
			case vehicle:

				LoadJsonVehilceData(JsonVehicle, entityname, &MyVehilce);

				DecorateVehicle(MyVehilce);

				AttachEntity(MyVehilce);
				break;
			case object:

				LoadJsonObjectData(JsonVehicle, entityname, &toSpawn);

				DecorateObject(toSpawn);

				AttachEntity(toSpawn);
				//if (!toSpawn.HasParents)
				//{
				//	AttachPool.find(MyVehilce.AttachTo.ParentsId)->second;//Parents Object
				//	ENTITY::ATTACH_ENTITY_TO_ENTITY(
				//		AttachPool.find(toSpawn.initHandle)->second,//Obejct Handle
				//		AttachPool.find(MyVehilce.AttachTo.ParentsId)->second,//Vehilce Handle
				//		ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(AttachPool.find(MyVehilce.AttachTo.ParentsId)->second, (char*)toSpawn.AttachTo.Bone.c_str()),
				//		MyVehilce.AttachTo.Position.x,
				//		MyVehilce.AttachTo.Position.y,
				//		MyVehilce.AttachTo.Position.z,
				//		MyVehilce.AttachTo.Rot.Pitch,
				//		MyVehilce.AttachTo.Rot.Roll,
				//		MyVehilce.AttachTo.Rot.Yaw, 1, 0, 0, 2, 1, 1);
				//}
				break;
			case ped:
				LOG_PRINT("I didn't found about ped data, if you found, please contact me XP");
				break;
			default:
				LOG_PRINT("Unkown Type");
				break;
			}
			EntitiesNum++;
		}
		WAIT(0);
		if (EntCount <= EntitiesNum)
			break;

	}
#pragma endregion
}
#pragma endregion




void LoadModsVehicle(Mods_Veh type, std::string name)
{
	switch (type)
	{
	case ini:
		LoadIniVeh(name);
		break;
	case xml:
		LoadXmlVeh(name);
		break;
	case json:
		LoadJsonVeh(name);
		break;
	case unknown:
		break;
	default:
		break;
	}
}




