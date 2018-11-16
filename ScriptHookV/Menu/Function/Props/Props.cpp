
#include "../../internal_native.h"
#include "../Function.h"
#include "../../ScriptHookV.h"
#include "../../MenuBase/menu.h"
#include "../../MenuBase/menuutils.h"
#include "../../Menu/UI/Script.h"
#include "../keyboard.h"
#include "Props.h"


int proppos, modelpos;

Object SpawnObject(char* name)
{
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	//	Object obj = CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY(name), coords.x, coords.y, coords.z, 1, 0, 0);
	Object obj = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY(name), pos.x, pos.y, pos.z, true, 1, 0);
	return obj;
}
Object SpawnPed(char* name, int selectplayer)
{
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	if (STREAMING::IS_MODEL_IN_CDIMAGE($(name))) {
		STREAMING::REQUEST_MODEL($(name));
		while (!STREAMING::HAS_MODEL_LOADED($(name))) WAIT(0);
		//	Object obj = CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY(name), coords.x, coords.y, coords.z, 1, 0, 0);
		Object obj = PED::CREATE_PED(PED_TYPE_MISSION, $(name), pos.x, pos.y, pos.z, true, 1, 0);
		return obj;
	}
	else
	{
		return -1;
	}

}

ObjectSetting *Target;
int handle;

void PropsMenu()
{
	addTitle("Props");
	menu.StringArray("Props Name", ObjectName, proppos, {}, true, false);
	if (menu.Option("Spawn Prop"))
	{
		ObjectSetting spawnedObj;
		Vector3 Pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		spawnedObj.Pos.X = Pos.x;
		spawnedObj.Pos.Y = Pos.y;
		spawnedObj.Pos.Z = Pos.z;
		spawnedObj.spawned = SpawnObject((char*)ObjectName[proppos].c_str());
		spawnedObj.propname = ObjectName[proppos];
		spawnedObj.Handle = rand() % 50001;//Genrate a random Handle
		ObjectDataBase.push_back(spawnedObj);
		ENTITY::FREEZE_ENTITY_POSITION(spawnedObj.spawned, 1);
	}
	menu.StringArray("Ped list", spmodel, modelpos, {}, true, false);
	if (menu.Option("Spawn Ped"))
	{
		//LOG_DEBUG("Spawn %s", (char*)modellist[modelpos].c_str());
		ObjectSetting spawnedObj;
		Vector3 Pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);

		spawnedObj.Pos.X = Pos.x;
		spawnedObj.Pos.Y = Pos.y;
		spawnedObj.Pos.Z = Pos.z;
		spawnedObj.spawned = SpawnPed((char*)spmodel[modelpos].c_str(), 0);
		spawnedObj.propname = spmodel[modelpos];

		spawnedObj.Handle = rand() % 50001;//Genrate a random Handle
		ObjectDataBase.push_back(spawnedObj);
		ENTITY::FREEZE_ENTITY_POSITION(spawnedObj.spawned, 1);
	}
	if (!ObjectDataBase.empty())
	{
		for (int id = 0; id < ObjectDataBase.size(); id++)
		{
			if (menu.MenuOption(ObjectDataBase[id].propname, "select_Props"))
			{
				handle = id;
				Target = &ObjectDataBase[id];
			}
		}
	}
}

/*

bool IsOnlyDamagedByPlayer = true;
Position Pos;
*/
void select_Props()
{
	addTitle(Target->propname);
	if (menu.Option("Delete"))//TODO:need to find another way to delete this //Maybe I can use the old shit
	{
		ENTITY::DELETE_ENTITY(&(Entity)Target->spawned);//Delete what you prepare to
		ObjectDataBase.erase(ObjectDataBase.begin() + handle);
	}
	menu.IntOption("Object Hanle", Target->Handle, INT_MIN, INT_MAX);
	if (menu.FloatOption("X", Target->Pos.X, -10000.0f, 1000.0f, 0.01f)||
		menu.FloatOption("Y", Target->Pos.Y, -10000.0f, 1000.0f, 0.01f)||
		menu.FloatOption("Z", Target->Pos.Z, -10000.0f, 1000.0f, 0.01f)
		)
	{
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Target->spawned, Target->Pos.X, Target->Pos.Y, Target->Pos.Z, 0, 0, 0);
	}
	if (menu.FloatOption("Pitch", Target->Pos.Pitch, -10000.0f, 1000.0f, 0.01f))
	{
		ENTITY::SET_ENTITY_ROTATION(Target->spawned, Target->Pos.Pitch, Target->Pos.Roll, Target->Pos.Yaw, 1, 0);
	}
	if (menu.FloatOption("Roll", Target->Pos.Roll, -10000.0f, 1000.0f, 0.01f))
	{
		ENTITY::SET_ENTITY_ROTATION(Target->spawned, Target->Pos.Pitch, Target->Pos.Roll, Target->Pos.Yaw, 1, 0);
	}
	if (menu.FloatOption("Yaw", Target->Pos.Yaw, -10000.0f, 1000.0f, 0.01f))
	{
		ENTITY::SET_ENTITY_ROTATION(Target->spawned, Target->Pos.Pitch, Target->Pos.Roll, Target->Pos.Yaw, 1, 0);
	}
	if (menu.BoolOption("Dynamic", Target->Dynamic))	ENTITY::SET_ENTITY_DYNAMIC(Target->spawned, Target->Dynamic);
	if (menu.IntOption("ALPHA", Target->OpacityLevel,0,255))	ENTITY::SET_ENTITY_ALPHA(Target->spawned, Target->OpacityLevel,false);
	if (menu.IntOption("LOD distance", Target->LodDistance,0, 0xFFFF))	ENTITY::SET_ENTITY_LOD_DIST(Target->spawned, Target->LodDistance);
	if (menu.BoolOption("Visible", Target->IsVisible))ENTITY::SET_ENTITY_VISIBLE(Target->spawned, Target->IsVisible,true);
	if (menu.IntOption("Entiy MAX Health", Target->MaxHealth, 0, INT_MAX))ENTITY::SET_ENTITY_MAX_HEALTH(Target->spawned, Target->MaxHealth);
	if (menu.IntOption("Entiy  Health", Target->Health, 0, INT_MAX))ENTITY::SET_ENTITY_HEALTH(Target->spawned, Target->Health);
	if (menu.BoolOption("Invincible", Target->IsInvincible))ENTITY::SET_ENTITY_INVINCIBLE(Target->spawned, Target->IsInvincible);
	if (menu.BoolOption("Bullet Proof", Target->IsBulletProof))ENTITY::SET_ENTITY_PROOFS(Target->spawned, Target->IsBulletProof, Target->IsFireProof, Target->IsExplosionProof, Target->IsCollisionProof, Target->IsMeleeProof, true, true, false);
	if (menu.BoolOption("Fire Proof", Target->IsFireProof))ENTITY::SET_ENTITY_PROOFS(Target->spawned, Target->IsBulletProof, Target->IsFireProof, Target->IsExplosionProof, Target->IsCollisionProof, Target->IsMeleeProof, true, true, false);
	if (menu.BoolOption("Explosion Proof", Target->IsExplosionProof))ENTITY::SET_ENTITY_PROOFS(Target->spawned, Target->IsBulletProof, Target->IsFireProof, Target->IsExplosionProof, Target->IsCollisionProof, Target->IsMeleeProof, true, true, false);
	if (menu.BoolOption("Collision Proof", Target->IsCollisionProof))ENTITY::SET_ENTITY_PROOFS(Target->spawned, Target->IsBulletProof, Target->IsFireProof, Target->IsExplosionProof, Target->IsCollisionProof, Target->IsMeleeProof, true, true, false);
	if (menu.BoolOption("Melee Proof", Target->IsMeleeProof))ENTITY::SET_ENTITY_PROOFS(Target->spawned, Target->IsBulletProof, Target->IsFireProof, Target->IsExplosionProof, Target->IsCollisionProof, Target->IsMeleeProof, true, true, false);
	if (menu.BoolOption("is Only Damage By Player", Target->IsOnlyDamagedByPlayer))ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(Target->spawned, Target->IsOnlyDamagedByPlayer);
	
	menu.DrawMarker({ Target->Pos.X , Target->Pos.Y,Target->Pos.Z });
}

void update_Props_menu()
{
	if (menu.CurrentMenu("Props"))PropsMenu();
	if (menu.CurrentMenu("select_Props"))select_Props();
}

void update_Props_game()
{

}