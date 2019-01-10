#include "../../ScriptHookV.h"
#include "../internal_native.h"
#include "Function.h"

Hash $(std::string str) {
	return GAMEPLAY::GET_HASH_KEY(&str[0u]);
}

std::string show_keyboard()
{
	DWORD time = GetTickCount() + 400;
	while (GetTickCount() < time)
	{
		WAIT(0);
	}

	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "FMMC_KEY_TIP8", "", "", "", "", "", 64);

	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0)
	{
		WAIT(0);
	}

	std::stringstream ss;
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
	{
		return std::string("");
	}
	else
	{
		return std::string(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
	}
}

float FloatKeyboard()
{
	DWORD time = GetTickCount() + 400;
	while (GetTickCount() < time)
	{
		WAIT(0);
	}

	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "FMMC_KEY_TIP8", "", "", "", "", "", 64);

	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0)
	{
		WAIT(0);
	}

	std::stringstream ss;
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
	{
		return 0;
	}
	else
	{
		return std::atof(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
	}
}

void showNotification(const char* message, char * picname, int *prevNotification) {
	if (prevNotification != nullptr && *prevNotification != 0) {
		UI::_REMOVE_NOTIFICATION(*prevNotification);
	}
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(CharAdapter(message));
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG(picname, picname, false, 2, "Project X", "NOOOOOOOOOOB", 0.5, "___Dev");
	//"CHAR_ABIGAIL", "CHAR_ALL_PLAYERS_CONF", "CHAR_AMANDA", "CHAR_AMMUNATION", "CHAR_ANDREAS",
	//	"CHAR_ANTONIA", "CHAR_ARTHUR", "CHAR_ASHLEY", "CHAR_BANK_BOL", "CHAR_BANK_FLEECA", "CHAR_BANK_MAZE",
	//	"CHAR_BARRY", "CHAR_BEVERLY", "CHAR_BIKESITE", "CHAR_BLANK_ENTRY", "CHAR_BLIMP", "CHAR_BLOCKED", "CHAR_BOATSITE",
	//	"CHAR_BROKEN_DOWN_GIRL", "CHAR_BUGSTARS", "CHAR_CALL911", "CHAR_CARSITE", "CHAR_CARSITE2", "CHAR_CASTRO",
	//	"CHAR_CHAT_CALL", "CHAR_CHEF", "CHAR_CHENG", "CHAR_CHENGSR", "CHAR_CHOP",//  "CHAR_CREATOR_PORTRAITS",
	//	"CHAR_CRIS", "CHAR_DAVE", "CHAR_DEFAULT", "CHAR_DENISE", "CHAR_DETONATEBOMB", "CHAR_DETONATEPHONE",
	//	"CHAR_DEVIN", "CHAR_DIAL_A_SUB", "CHAR_DOM", "CHAR_DOMESTIC_GIRL", "CHAR_DREYFUSS", "CHAR_DR_FRIEDLANDER",
	//	"CHAR_EPSILON", "CHAR_ESTATE_AGENT", "CHAR_FACEBOOK", "CHAR_FILMNOIR", "CHAR_FLOYD", "CHAR_FRANKLIN",
	//	"CHAR_FRANK_TREV_CONF", "CHAR_GAYMILITARY", "CHAR_HAO", "CHAR_HITCHER_GIRL", "CHAR_HUMANDEFAULT",
	//	"CHAR_HUNTER", "CHAR_JIMMY", "CHAR_JIMMY_BOSTON", "CHAR_JOE", "CHAR_JOSEF", "CHAR_JOSH", "CHAR_LAMAR",
	//	"CHAR_LAZLOW", "CHAR_LESTER", "CHAR_LESTER_DEATHWISH", "CHAR_LEST_FRANK_CONF", "CHAR_LEST_MIKE_CONF",
	//	"CHAR_LIFEINVADER", "CHAR_LS_CUSTOMS", "CHAR_LS_TOURIST_BOARD", "CHAR_MANUEL", "CHAR_MARNIE",
	//	"CHAR_MARTIN", "CHAR_MARY_ANN", "CHAR_MAUDE", "CHAR_MECHANIC", "CHAR_MICHAEL", "CHAR_MIKE_FRANK_CONF",
	//	"CHAR_MIKE_TREV_CONF", "CHAR_MILSITE", "CHAR_MINOTAUR", "CHAR_MOLLY", "CHAR_MP_ARMY_CONTACT",
	//	"CHAR_MP_BIKER_BOSS", "CHAR_MP_BIKER_MECHANIC", "CHAR_MP_BRUCIE", "CHAR_MP_DETONATEPHONE",
	//	"CHAR_MP_FAM_BOSS", "CHAR_MP_FIB_CONTACT", "CHAR_MP_FM_CONTACT", "CHAR_MP_GERALD", "CHAR_MP_JULIO",
	//	"CHAR_MP_MECHANIC", "CHAR_MP_MERRYWEATHER", "CHAR_MP_MEX_BOSS", "CHAR_MP_MEX_DOCKS", "CHAR_MP_MEX_LT",
	//	"CHAR_MP_MORS_MUTUAL", "CHAR_MP_PROF_BOSS", "CHAR_MP_RAY_LAVOY", "CHAR_MP_ROBERTO", "CHAR_MP_SNITCH",
	//	"CHAR_MP_STRETCH", "CHAR_MP_STRIPCLUB_PR", "CHAR_MRS_THORNHILL", "CHAR_MULTIPLAYER", "CHAR_NIGEL",
	//	"CHAR_OMEGA", "CHAR_ONEIL", "CHAR_ORTEGA", "CHAR_OSCAR", "CHAR_PATRICIA", "CHAR_PEGASUS_DELIVERY", "CHAR_PLANESITE",
	//	"CHAR_PROPERTY_ARMS_TRAFFICKING", "CHAR_PROPERTY_BAR_AIRPORT", "CHAR_PROPERTY_BAR_BAYVIEW",
	//	"CHAR_PROPERTY_BAR_CAFE_ROJO", "CHAR_PROPERTY_BAR_COCKOTOOS", "CHAR_PROPERTY_BAR_ECLIPSE", "CHAR_PROPERTY_BAR_FES",
	//	"CHAR_PROPERTY_BAR_HEN_HOUSE", "CHAR_PROPERTY_BAR_HI_MEN", "CHAR_PROPERTY_BAR_HOOKIES", "CHAR_PROPERTY_BAR_IRISH",
	//	"CHAR_PROPERTY_BAR_LES_BIANCO", "CHAR_PROPERTY_BAR_MIRROR_PARK", "CHAR_PROPERTY_BAR_PITCHERS", "CHAR_PROPERTY_BAR_SINGLETONS",
	//	"CHAR_PROPERTY_BAR_TEQUILALA", "CHAR_PROPERTY_BAR_UNBRANDED", "CHAR_PROPERTY_CAR_MOD_SHOP", "CHAR_PROPERTY_CAR_SCRAP_YARD",
	//	"CHAR_PROPERTY_CINEMA_DOWNTOWN", "CHAR_PROPERTY_CINEMA_MORNINGWOOD",
	//	"CHAR_PROPERTY_CINEMA_VINEWOOD", "CHAR_PROPERTY_GOLF_CLUB", "CHAR_PROPERTY_PLANE_SCRAP_YARD",
	//	"CHAR_PROPERTY_SONAR_COLLECTIONS", "CHAR_PROPERTY_TAXI_LOT", "CHAR_PROPERTY_TOWING_IMPOUND",
	//	"CHAR_PROPERTY_WEED_SHOP", "CHAR_RON", "CHAR_SAEEDA", "CHAR_SASQUATCH", "CHAR_SIMEON",
	//	"CHAR_SOCIAL_CLUB", "CHAR_SOLOMON", "CHAR_STEVE", "CHAR_STEVE_MIKE_CONF", "CHAR_STEVE_TREV_CONF",
	//	"CHAR_STRETCH", "CHAR_STRIPPER_CHASTITY", "CHAR_STRIPPER_CHEETAH", "CHAR_STRIPPER_FUFU",
	//	"CHAR_STRIPPER_INFERNUS", "CHAR_STRIPPER_JULIET", "CHAR_STRIPPER_NIKKI", "CHAR_STRIPPER_PEACH",
	//	"CHAR_STRIPPER_SAPPHIRE", "CHAR_TANISHA", "CHAR_TAXI", "CHAR_TAXI_LIZ", "CHAR_TENNIS_COACH",
	//	"CHAR_TOW_TONYA", "CHAR_TRACEY", "CHAR_TREVOR", "CHAR_WADE", "CHAR_YOUTUBE", "CHAR_CREATOR_PORTRAITS",
	int id = UI::_DRAW_NOTIFICATION(false, false);
	if (prevNotification != nullptr) {
		*prevNotification = id;
	}
}


void changemodel(std::string newmodel)
{
	Hash model = $(newmodel);
	if (STREAMING::IS_MODEL_VALID(model) && STREAMING::IS_MODEL_IN_CDIMAGE(model) && !STREAMING::IS_MODEL_A_VEHICLE(model))
	{
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
		PLAYER::SET_PLAYER_MODEL(PLAYER::NETWORK_PLAYER_ID_TO_INT(), model);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	}
	else
	{
		showNotification(
			FMT("%s is invalid",(char*)newmodel.c_str()).c_str()
		);
	}
}


Vector3 get_blip_marker()
{
	static Vector3 zero;
	Vector3 coords;

	bool blipFound = false;
	// search for marker blip
	int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
	for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
	{
		if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
		{
			coords = UI::GET_BLIP_INFO_ID_COORD(i);
			blipFound = true;
			break;
		}
	}
	if (blipFound)
	{
		return coords;
	}

	return zero;
}

void teleport_to_coords(Entity e, Vector3 coords)
{
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
	WAIT(0);
}

void teleport_to_marker()
{
	Vector3 coords = get_blip_marker();

	if (coords.x == 0 && coords.y == 0)
	{
		return;
	}
	/*Cam mycam = CAM::CREATE_CAMERA(GAMEPLAY::GET_HASH_KEY("DEFAULT_SCRIPTED_CAMERA"), true);
	CAM::SET_CAM_ACTIVE(mycam, true);*/
	CAM::RENDER_SCRIPT_CAMS(true, true, 3000, 0, 0);
	// get entity to teleport
	Entity e = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
	{
		e = PED::GET_VEHICLE_PED_IS_USING(e);
	}

	// load needed map region and check height levels for ground existence
	bool groundFound = false;
	static float groundCheckHeight[] =
	{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
	for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
	{
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
		WAIT(100);
		if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0))
		{
			groundFound = true;
			coords.z += 3.0;
			break;
		}
	}
	// if ground not found then set Z in air and give player a parachute
	if (!groundFound)
	{
		coords.z = 1000.0;
		//WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
	}
	//do it
	teleport_to_coords(e, coords);
	CAM::RENDER_SCRIPT_CAMS(false, true, 3000, 0, 0);
	/*CAM::SET_CAM_ACTIVE(mycam, false);
	CAM::DESTROY_CAM(mycam, false);*/
}

float degToRad(float degs)
{
	return degs * 3.141592653589793f / 180.f;
}

double DegreeToRadian(double n) {
	return n * 0.017453292519943295;
}
Vector3 RotationToDirection(Vector3 rot) {
	double num = DegreeToRadian(rot.z);
	double num2 = DegreeToRadian(rot.x);
	double val = cos(num2);
	double num3 = abs(val);
	rot.x = (float)(-(float)sin(num) * num3);
	rot.y = (float)(cos(num) * num3);
	rot.z = (float)sin(num2);
	return rot;

}
Vector3 rot_to_direction(Vector3* rot)//scripthookdotnet source
{
	float radiansZ = rot->z * 0.0174532924f;
	float radiansX = rot->x * 0.0174532924f;
	float num = std::abs((float)std::cos((double)radiansX));
	Vector3 dir;
	dir.x = (float)((double)((float)(-(float)std::sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)std::cos((double)radiansZ)) * (double)num);
	dir.z = (float)std::sin((double)radiansX);
	return dir;
}

float get_distance(Vector3*pointA, Vector3*pointB) {
	float a_x = pointA->x;
	float a_y = pointA->y;
	float a_z = pointA->z;
	float b_x = pointB->x;
	float b_y = pointB->y;
	float b_z = pointB->z;
	double x_ba = (double)(b_x - a_x);
	double y_ba = (double)(b_y - a_y);
	double z_ba = (double)(b_z - a_z);
	double y_2 = y_ba * y_ba;
	double x_2 = x_ba * x_ba;
	double sum_2 = y_2 + x_2;
	return(float)sqrt(sum_2 + z_ba);
}



Vector3 GET_AIM_COORDS()
{

	Vector3 camPosition = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 dir = rot_to_direction(&rot);
	float distance = 10.0f;
	Vector3 lengthVector = dir * distance;
	Vector3 posLookAt = camPosition + lengthVector;
	float targetz = 0.0f;

	while (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(posLookAt.x, posLookAt.y, posLookAt.z, &targetz, 0))
	{
		distance += 0.1f;
		lengthVector = dir * distance;
		posLookAt = camPosition + lengthVector;
		if (distance - 100.0f > 0.0f)
		{
			break;
		}
	}
	//LOG_PRINT("distance Z:%f", distance);
	return posLookAt;
}

void GET_CAMERA_DIRECTION(float *dirX, float *dirY, float *dirZ)
{
	float tX, tZ, num;
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);

	tZ = rot.z * 0.0174532924f;
	tX = rot.x * 0.0174532924f;
	num = abs(cos(tX));

	*dirX = (-sin(tZ)) * num;
	*dirY = (cos(tZ)) * num;
	*dirZ = sin(tX);
}

void RequestControl(Entity input)
{
	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(input);

	int tick = 0;
	while (tick <= 50)
	{
		if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(input))
			WAIT(0);
		else
			return;
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(input);
		tick++;
	}
}
void RequestControlOfid(Entity netid)
{
	int tick = 0;

	while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
		tick++;
	}
}
void RequestControlOfEnt(Entity entity)
{
	int tick = 0;
	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		RequestControlOfid(netID);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
	}
}

void find(char* lpPath, std::vector<std::string> &fileList)
{
	char szFind[MAX_PATH];
	WIN32_FIND_DATA FindFileData;

	strcpy_s(szFind, lpPath);
	strcat_s(szFind, "\\*.*");

	HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)    return;

	while (true)
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (FindFileData.cFileName[0] != '.')
			{
				char szFile[MAX_PATH];
				strcpy(szFile, lpPath);
				strcat(szFile, "\\");
				strcat(szFile, (char*)(FindFileData.cFileName));
				find(szFile, fileList);
			}
		}
		else
		{
			//std::cout << FindFileData.cFileName << std::endl;  
			fileList.push_back(FindFileData.cFileName);
		}
		if (!FindNextFile(hFind, &FindFileData))    break;
	}
	FindClose(hFind);
}

bool EndsWith(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

void DrawBigMsg(std::string functionname, std::string msg, std::string msg2 )
{
	int Handle;
	int tick = timeGetTime();
	while (timeGetTime() - tick < 3000)
	{
		Handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_BIG_MESSAGE_FREEMODE");
		// Open Data Slot Function
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(Handle, (char*)functionname.c_str());
		// Set Data Slot Value/Parameter
		GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)msg.c_str());
		GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

		GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)msg2.c_str());
		GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(100);
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_BOOL(true);
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(100);
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_BOOL(true);
		// Close Data Slot Function
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(Handle, 255, 255, 255, 255, 0);
		GRAPHICS::_SCREEN_DRAW_POSITION_END();
		WAIT(0);
	}
}

bool String2Bool(std::string text)
{
	return !strcmp(text.c_str(), "true") ? true : false;
}