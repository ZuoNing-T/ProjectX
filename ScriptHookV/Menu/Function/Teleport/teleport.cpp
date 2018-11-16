#include "../../internal_native.h"
#include "teleport.h"
#include "../Function.h"
#include "../../ScriptHookV.h"
#include "../../MenuBase/menu.h"
#include "../../MenuBase/menuutils.h"
#include "../../Menu/UI/Script.h"
#include "../keyboard.h"


std::vector<teleportList> targetPlace;
std::string place;

std::vector<IPLScoords> v_SpecialLocations;
std::vector<IPLScoords> v_ClubhouseWarehouses;
std::vector<IPLScoords> v_MazeBankWest;
std::vector<IPLScoords> v_LomBank;
std::vector<IPLScoords> v_MazeBank;
std::vector<IPLScoords> v_BusinessCentre;
std::vector<IPLScoords> v_Apartment;
std::vector<IPLScoords> v_Bunker;


inline std::vector<IPLScoords> Build_Bunker()
{
	return {
		IPLScoords("ZancudoBunker","gr_case10_bunkerclosed",{ -3058.714f, 3329.19f, 12.5844f }),
		IPLScoords("Route68Bunker","gr_case9_bunkerclosed",{ 24.43542f, 2959.705f, 58.35517f }),
		IPLScoords("OilfieldsBunker","gr_case3_bunkerclosed",{ 481.0465f, 2995.135f, 43.96672f }),
		IPLScoords("DesertBunker","gr_case0_bunkerclosed",{ 848.6175f, 2996.567f, 45.81612f }),
		IPLScoords("SmokeTreeBunker","gr_case1_bunkerclosed",{ 2126.785f, 3335.04f, 48.21422f }),
		IPLScoords("ScrapyardBunker","gr_case2_bunkerclosed",{ 2493.654f, 3140.399f, 51.28789f }),
		IPLScoords("GrapeseedBunker","gr_case5_bunkerclosed",{ 1823.961f, 4708.14f, 42.4991f }),
		IPLScoords("PalletoBunker","gr_case7_bunkerclosed",{ -783.0755f, 5934.686f, 24.31475f }),
		IPLScoords("Route1Bunker","gr_case11_bunkerclosed",{ -3180.466f, 1374.192f, 19.9597f }),
		IPLScoords("FarmhouseBunker","gr_case6_bunkerclosed",{ 1570.372f, 2254.549f, 78.89397f }),
		IPLScoords("RatonCanyonBunker","gr_case4_bunkerclosed",{ -391.3216f, 4363.728f, 58.65862f })
	};
}

inline std::vector<IPLScoords> Build_Apartment()
{
	return{

		IPLScoords("Modern 1 Apartment","apa_v_mp_h_01_a",{ -786.8663f, 315.7642f, 217.6385f }),
		IPLScoords("Modern 2 Apartment","apa_v_mp_h_01_c",{ -786.9563f, 315.6229f, 187.9136f }),
		IPLScoords("Modern 3 Apartment","apa_v_mp_h_01_b",{ -774.0126f, 342.0428f, 196.6864f }),
		IPLScoords("Mody 1 Apartment","apa_v_mp_h_02_a",{ -787.0749f, 315.8198f, 217.6386f }),
		IPLScoords("Mody 2 Apartment","apa_v_mp_h_02_c",{ -786.8195f, 315.5634f, 187.9137f }),
		IPLScoords("Mody 3 Apartment","apa_v_mp_h_02_b",{ -774.1382f, 342.0316f, 196.6864f }),
		IPLScoords("Vibrant 1 Apartment","apa_v_mp_h_03_a",{ -786.6245f, 315.6175f, 217.6385f }),
		IPLScoords("Vibrant 2 Apartment","apa_v_mp_h_03_c",{ -786.9584f, 315.7974f, 187.9135f }),
		IPLScoords("Vibrant 3 Apartment","apa_v_mp_h_03_b",{ -774.0223f, 342.1718f, 196.6863f }),
		IPLScoords("Sharp 1 Apartment","apa_v_mp_h_04_a",{ -787.0902f, 315.7039f, 217.6384f }),
		IPLScoords("Sharp 2 Apartment","apa_v_mp_h_04_c",{ -787.0155f, 315.7071f, 187.9135f }),
		IPLScoords("Sharp 3 Apartment","apa_v_mp_h_04_b",{ -773.8976f, 342.1525f, 196.6863f }),
		IPLScoords("Monochrome 1 Apartment","apa_v_mp_h_05_a",{ -786.9887f, 315.7393f, 217.6386f }),
		IPLScoords("Monochrome 2 Apartment","apa_v_mp_h_05_c",{ -786.8809f, 315.6634f, 187.9136f }),
		IPLScoords("Monochrome 3 Apartment","apa_v_mp_h_05_b",{ -774.0675f, 342.0773f, 196.6864f }),
		IPLScoords("Seductive 1 Apartment","apa_v_mp_h_06_a",{ -787.1423f, 315.6943f, 217.6384f }),
		IPLScoords("Seductive 2 Apartment","apa_v_mp_h_06_c",{ -787.0961f, 315.815f, 187.9135f }),
		IPLScoords("Seductive 3 Apartment","apa_v_mp_h_06_b",{ -773.9552f, 341.9892f, 196.6862f }),
		IPLScoords("Regal 1 Apartment","apa_v_mp_h_07_a",{ -787.029f, 315.7113f, 217.6385f }),
		IPLScoords("Regal 2 Apartment","apa_v_mp_h_07_c",{ -787.0574f, 315.6567f, 187.9135f }),
		IPLScoords("Regal 3 Apartment","apa_v_mp_h_07_b",{ -774.0109f, 342.0965f, 196.6863f }),
		IPLScoords("Aqua 1 Apartment","apa_v_mp_h_08_a",{ -786.9469f, 315.5655f, 217.6383f }),
		IPLScoords("Aqua 2 Apartment","apa_v_mp_h_08_c",{ -786.9756f, 315.723f, 187.9134f }),
		IPLScoords("Aqua 3 Apartment","apa_v_mp_h_08_b",{ -774.0349f, 342.0296f, 196.6862f })
	};
}
//BusinessCentre

inline std::vector<IPLScoords> Build_BusinessCentre()
{
	return{
		IPLScoords("Executive Rich",				"ex_dt1_02_office_02b",{ -141.1987f, -620.913f, 168.8205f }),
		IPLScoords("Executive Cool",				"ex_dt1_02_office_02c",{ -141.5429f, -620.9524f, 168.8204f }),
		IPLScoords("Executive Contrast",         "ex_dt1_02_office_02a",{ -141.2896f, -620.9618f, 168.8204f }),
		IPLScoords("Old Spice Warm",				"ex_dt1_02_office_01a",{ -141.4966f, -620.8292f, 168.8204f }),
		IPLScoords("Old Spice Classical",        "ex_dt1_02_office_01b",{ -141.3997f, -620.9006f, 168.8204f }),
		IPLScoords("Old Spice Vintage",			"ex_dt1_02_office_01c",{ -141.5361f, -620.9186f, 168.8204f }),
		IPLScoords("Power Broker Ice",			"ex_dt1_02_office_03a",{ -141.392f, -621.0451f, 168.8204f }),
		IPLScoords("Power Broker Conservative",  "ex_dt1_02_office_03b",{ -141.1945f, -620.8729f, 168.8204f }),
		IPLScoords("Power Broker Polished",      "ex_dt1_02_office_03c",{ -141.4924f, -621.0035f, 168.8205f }),
		IPLScoords("Garage 1",					"imp_dt1_02_cargarage_a",{ -191.0133f, -579.1428f, 135.0000f }),
		IPLScoords("Garage 2",					"imp_dt1_02_cargarage_b",{ -117.4989f, -568.1132f, 135.0000f }),
		IPLScoords("Garage 3",					"imp_dt1_02_cargarage_c",{ -136.0780f, -630.1852f, 135.0000f }),
		IPLScoords("Mod Shop",					"imp_dt1_02_modgarage",{ -146.6166f, -596.6301f, 166.0000f }),
	};
}

inline std::vector<IPLScoords> Build_MazeBank()
{
	return {
		IPLScoords("Executive Rich","ex_dt1_11_office_02b",{ -75.8466f, -826.9893f, 243.3859f }),
		IPLScoords("Executive Cool","ex_dt1_11_office_02c",{ -75.49945f, -827.05f, 243.386f }),
		IPLScoords("Executive Contrast","ex_dt1_11_office_02a",{ -75.49827f, -827.1889f, 243.386f }),
		IPLScoords("Old Spice Warm","ex_dt1_11_office_01a",{ -75.44054f, -827.1487f, 243.3859f }),
		IPLScoords("Old Spice Classical","ex_dt1_11_office_01b",{ -75.63942f, -827.1022f, 243.3859f }),
		IPLScoords("Old Spice Vintage","ex_dt1_11_office_01c",{ -75.47446f, -827.2621f, 243.386f }),
		IPLScoords("Power Broker Ice","ex_dt1_11_office_03a",{ -75.56978f, -827.1152f, 243.3859f }),
		IPLScoords("Power Broker Conservative","ex_dt1_11_office_03b",{ -75.51953f, -827.0786f, 243.3859f }),
		IPLScoords("Power Broker Polished","ex_dt1_11_office_03c",{ -75.41915f, -827.1118f, 243.3858f }),
		IPLScoords("Garage 1","imp_dt1_11_cargarage_a",{ -84.2193f, -823.0851f, 221.0000f }),
		IPLScoords("Garage 2","imp_dt1_11_cargarage_b",{ -69.8627f, -824.7498f, 221.0000f }),
		IPLScoords("Garage 3","imp_dt1_11_cargarage_c",{ -80.4318f, -813.2536f, 221.0000f }),
		IPLScoords("Mod Shop","imp_dt1_11_modgarage",{ -73.9039f, -821.6204f, 284.0000f })
	};
}

inline std::vector<IPLScoords> Build_LomBank() {
	return {
		IPLScoords("Executive Rich","ex_sm_13_office_02b",{ -1579.756f, -565.0661f, 108.523f }),
		IPLScoords("Executive Cool","ex_sm_13_office_02c",{ -1579.678f, -565.0034f, 108.5229f }),
		IPLScoords("Executive Contrast","ex_sm_13_office_02a",{ -1579.583f, -565.0399f, 108.5229f }),
		IPLScoords("Old Spice Warm","ex_sm_13_office_01a",{ -1579.702f, -565.0366f, 108.5229f }),
		IPLScoords("Old Spice Classical","ex_sm_13_office_01b",{ -1579.643f, -564.9685f, 108.5229f }),
		IPLScoords("Old Spice Vintage","ex_sm_13_office_01c",{ -1579.681f, -565.0003f, 108.523f }),
		IPLScoords("Power Broker Ice","ex_sm_13_office_03a",{ -1579.677f, -565.0689f, 108.5229f }),
		IPLScoords("Power Broker Conservative","ex_sm_13_office_03b",{ -1579.708f, -564.9634f, 108.5229f }),
		IPLScoords("Power Broker Polished","ex_sm_13_office_03c",{ -1579.693f, -564.8981f, 108.5229f }),
		IPLScoords("Garage 1","imp_sm_13_cargarage_a",{ -1581.1120f, -567.2450f, 85.5000f }),
		IPLScoords("Garage 2","imp_sm_13_cargarage_b",{ -1568.7390f, -562.0455f, 85.5000f }),
		IPLScoords("Garage 3","imp_sm_13_cargarage_c",{ -1563.5570f, -574.4314f, 85.5000f }),
		IPLScoords("Mod Shop","imp_sm_13_modgarage",{ -1578.0230f, -576.4251f, 104.2000f })
	};
}

inline std::vector<IPLScoords> Build_MazeBankWest()
{
	return {
		IPLScoords("Executive Rich","ex_sm_15_office_02b",{ -1392.667f, -480.4736f, 72.04217f }),
		IPLScoords("Executive Cool","ex_sm_15_office_02c",{ -1392.542f, -480.4011f, 72.04211f }),
		IPLScoords("Executive Contrast","ex_sm_15_office_02a",{ -1392.626f, -480.4856f, 72.04212f }),
		IPLScoords("Old Spice Warm","ex_sm_15_office_01a",{ -1392.617f, -480.6363f, 72.04208f }),
		IPLScoords("Old Spice Classical","ex_sm_15_office_01b",{ -1392.532f, -480.7649f, 72.04207f }),
		IPLScoords("Old Spice Vintage","ex_sm_15_office_01c",{ -1392.611f, -480.5562f, 72.04214f }),
		IPLScoords("Power Broker Ice","ex_sm_15_office_03a",{ -1392.563f, -480.549f, 72.0421f }),
		IPLScoords("Power Broker Convservative","ex_sm_15_office_03b",{ -1392.528f, -480.475f, 72.04206f }),
		IPLScoords("Power Broker Polished","ex_sm_15_office_03c",{ -1392.416f, -480.7485f, 72.04207f }),
		IPLScoords("Garage 1","imp_sm_15_cargarage_a",{ -1388.8400f, -478.7402f, 56.1000f }),
		IPLScoords("Garage 2","imp_sm_15_cargarage_b",{ -1388.8600f, -478.7574f, 48.1000f }),
		IPLScoords("Garage 3","imp_sm_15_cargarage_c",{ -1374.6820f, -474.3586f, 56.1000f }),
		IPLScoords("Mod Shop","imp_sm_15_modgarage",{ -1391.2450f, -473.9638f, 77.2000f })
	};
}

inline std::vector<IPLScoords> Build_ClubhouseWarehouses()
{
	return
	{
		IPLScoords("Clubhouse 1","bkr_biker_interior_placement_interior_0_biker_dlc_int_01_milo",{ 1107.04f, -3157.399f, -37.51859f }),
		IPLScoords("Clubhouse 2","bkr_biker_interior_placement_interior_1_biker_dlc_int_02_milo",{ 998.4809f, -3164.711f, -38.90733f }),
		IPLScoords("Meth Lab","bkr_biker_interior_placement_interior_2_biker_dlc_int_ware01_milo",{ 1009.5f, -3196.6f, -38.99682f }),
		IPLScoords("Weed Farm","bkr_biker_interior_placement_interior_3_biker_dlc_int_ware02_milo",{ 1051.491f, -3196.536f, -39.14842f }),
		IPLScoords("Cocaine Lockup","bkr_biker_interior_placement_interior_4_biker_dlc_int_ware03_milo",{ 1093.6f, -3196.6f, -38.99841f }),
		IPLScoords("Counterfeit Cash Factory","bkr_biker_interior_placement_interior_5_biker_dlc_int_ware04_milo",{ 1121.897f, -3195.338f, -40.4025f }),
		IPLScoords("Document Forgery Office","bkr_biker_interior_placement_interior_6_biker_dlc_int_ware05_milo",{ 1165.0f, -3196.6f, -39.01306f }),
		IPLScoords("Warehouse Small","ex_exec_warehouse_placement_interior_1_int_warehouse_s_dlc_milo",{ 1094.988f, -3101.776f, -39.00363f }),
		IPLScoords("Warehouse Medium","ex_exec_warehouse_placement_interior_0_int_warehouse_m_dlc_milo",{ 1056.486f, -3105.724f, -39.00439f }),
		IPLScoords("Warehouse Large","ex_exec_warehouse_placement_interior_2_int_warehouse_l_dlc_milo",{ 1006.967f, -3102.079f, -39.0035f }),
		IPLScoords("Vehicle Warehouse","imp_impexp_interior_placement_interior_1_impexp_intwaremed_milo_",{ 994.5925f, -3002.594f, -39.64699f }),
		IPLScoords("Lost MC Clubhouse","bkr_bi_hw1_13_int",{ 982.0083f, -100.8747f, 74.84512f })
	};
}

inline std::vector<IPLScoords> Build_SpecialLocations()

{
	return {
		IPLScoords("Normal Cargo Ship","cargoship",{ -163.3628f, -2385.161f, 5.999994f }),
		IPLScoords("Sunken Cargo Ship","sunkcargoship",{ -163.3628f, -2385.161f, 5.999994f }),
		IPLScoords("Burning Cargo Ship","SUNK_SHIP_FIRE",{ -163.3628f, -2385.161f, 5.999994f }),
		IPLScoords("Red Carpet","redCarpet",{ 300.5927f, 300.5927f, 104.3776f }),
		IPLScoords("Rekt Stilthouse Destroyed","DES_StiltHouse_imapend",{ -1020.518f, 663.27f, 153.5167f }),
		IPLScoords("Rekt Stilthouse Rebuild","DES_stilthouse_rebuild",{ -1020.518f, 663.27f, 153.5167f }),
		IPLScoords("Union Depository","FINBANK",{ 2.6968f, -667.0166f, 16.13061f }),
		IPLScoords("Trevors Trailer Dirty","TrevorsMP",{ 1975.552f, 3820.538f, 33.44833f }),
		IPLScoords("Trevors Trailer Clean","TrevorsTrailerTidy",{ 1975.552f, 3820.538f, 33.44833f }),
		IPLScoords("Stadium","SP1_10_real_interior",{ -248.6731f, -2010.603f, 30.14562f }),
		IPLScoords("Max Renda Shop","refit_unload",{ -585.8247f, -282.72f, 35.45475f }),
		IPLScoords("Jewel Store","post_hiest_unload",{ -630.07f, -236.332f, 38.05704f }),
		IPLScoords("FIB Lobby","FIBlobby",{ 110.4f, -744.2f, 45.7496f })
	};
}

void TPto(Vector3 Coords)
{
	int Handle = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
	{
		ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
	}
	else
		ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
}

bool BuildTeleport()
{
	v_SpecialLocations = Build_SpecialLocations();
	v_ClubhouseWarehouses = Build_ClubhouseWarehouses();
	v_MazeBankWest = Build_MazeBankWest();
	v_LomBank = Build_LomBank();
	v_MazeBank = Build_MazeBank();
	v_BusinessCentre = Build_BusinessCentre();
	v_Apartment = Build_Apartment();
	v_Bunker = Build_Bunker();
	return true &&
		(
			!v_SpecialLocations.empty() ||
			!v_ClubhouseWarehouses.empty() ||
			!v_MazeBankWest.empty() ||
			!v_LomBank.empty() ||
			!v_MazeBank.empty() ||
			!v_BusinessCentre.empty() ||
			!v_Apartment.empty() ||
			!v_Bunker.empty()
			);

}

void Garage()
{
	addTitle("Garage");
	if (menu.Option("2 Car"))TPto({ 173.2903f, -1003.6f, -99.65707f });
	if (menu.Option("6 Car"))TPto({ 197.8153f, -1002.293f, -99.65749f });
	if (menu.Option("10 Car"))TPto({ 229.9559f, -981.7928f, -99.66071f });
}
int teleportPos = 0;

void update_IPLs()
{
	addTitle("Special");
	if (menu.Option("North Yankton")) {
		STREAMING::REQUEST_IPL("prologue01");
		STREAMING::REQUEST_IPL("Prologue01c");
		STREAMING::REQUEST_IPL("Prologue01d");
		STREAMING::REQUEST_IPL("Prologue01e");
		STREAMING::REQUEST_IPL("Prologue01f");
		STREAMING::REQUEST_IPL("Prologue01g");
		STREAMING::REQUEST_IPL("prologue01h");
		STREAMING::REQUEST_IPL("prologue01i");
		STREAMING::REQUEST_IPL("prologue01j");
		STREAMING::REQUEST_IPL("prologue01k");
		STREAMING::REQUEST_IPL("prologue01z");
		STREAMING::REQUEST_IPL("prologue02");
		STREAMING::REQUEST_IPL("prologue03");
		STREAMING::REQUEST_IPL("prologue03b");
		STREAMING::REQUEST_IPL("prologue03_grv_cov");
		STREAMING::REQUEST_IPL("prologue03_grv_dug");
		STREAMING::REQUEST_IPL("prologue03_grv_fun");
		STREAMING::REQUEST_IPL("prologue04");
		STREAMING::REQUEST_IPL("prologue04b");
		STREAMING::REQUEST_IPL("prologue04_cover");
		STREAMING::REQUEST_IPL("prologue05");
		STREAMING::REQUEST_IPL("prologue05b");
		STREAMING::REQUEST_IPL("prologue06");
		STREAMING::REQUEST_IPL("prologue06b");
		STREAMING::REQUEST_IPL("prologue06_int");
		STREAMING::REQUEST_IPL("prologuerd");
		STREAMING::REQUEST_IPL("prologuerdb");
		STREAMING::REQUEST_IPL("prologue_DistantLights");
		STREAMING::REQUEST_IPL("prologue_grv_torch");
		STREAMING::REQUEST_IPL("prologue_m2_door");
		STREAMING::REQUEST_IPL("prologue_LODLights");
		STREAMING::REQUEST_IPL("DES_ProTree_start");
		Vector3 Coords;
		Coords.x = 3595.39673f; Coords.y = -4893.727f; Coords.z = 115.838394f;
		TPto(Coords);
	}
	if (menu.Option("Porn Yacht")) {
		STREAMING::REQUEST_IPL("smboat");
		Vector3 Coords;
		Coords.x = -2045.8f; Coords.y = -1031.2f; Coords.z = 11.9f;
		TPto(Coords);
	}
	if (menu.Option("Gunrunning Heist Yacht")) {
		STREAMING::REQUEST_IPL("gr_heist_yacht2");
		STREAMING::REQUEST_IPL("gr_heist_yacht2_bar");
		STREAMING::REQUEST_IPL("gr_heist_yacht2_bedrm");
		STREAMING::REQUEST_IPL("gr_heist_yacht2_bridge");
		STREAMING::REQUEST_IPL("gr_heist_yacht2_enginrm");
		STREAMING::REQUEST_IPL("gr_heist_yacht2_lounge");
		Vector3 Coords = { 1373.828f, 6737.393f, 6.707596f };
		TPto(Coords);
	}
	if (menu.Option("Dignity Heist Yacht")) {
		STREAMING::REQUEST_IPL("hei_yacht_heist");
		STREAMING::REQUEST_IPL("hei_yacht_heist_enginrm");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Lounge");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bridge");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bar");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bedrm");
		STREAMING::REQUEST_IPL("hei_yacht_heist_DistantLights");
		STREAMING::REQUEST_IPL("hei_yacht_heist_LODLights");
		Vector3 Coords = { -2027.946f, -1036.695f, 6.707587f };
		TPto(Coords);
	}
	if (menu.Option("Dignity Party Yacht")) {
		STREAMING::REQUEST_IPL("smboat");
		STREAMING::REQUEST_IPL("smboat_lod");
		Vector3 Coords = { -2023.643f, -1038.119f, 5.576781f };
		TPto(Coords);
	}
	if (menu.Option("Bridge Train Crash")) {
		STREAMING::REQUEST_IPL("canyonriver01_traincrash");
		STREAMING::REQUEST_IPL("railing_end");
		Vector3 Coords = { 532.1309f, 4526.187f, 89.79387f };
		TPto(Coords);
	}
	if (menu.Option("Bridge Train Crash")) {
		STREAMING::REQUEST_IPL("canyonriver01");
		STREAMING::REQUEST_IPL("railing_start");
		Vector3 Coords = { 532.1309f, 4526.187f, 89.79387f };
		TPto(Coords);
	}

	if (menu.Option("Aircraft Carrier")) {
		STREAMING::REQUEST_IPL("hei_carrier");
		STREAMING::REQUEST_IPL("hei_carrier_DistantLights");
		STREAMING::REQUEST_IPL("hei_Carrier_int1");
		STREAMING::REQUEST_IPL("hei_Carrier_int2");
		STREAMING::REQUEST_IPL("hei_Carrier_int3");
		STREAMING::REQUEST_IPL("hei_Carrier_int4");
		STREAMING::REQUEST_IPL("hei_Carrier_int5");
		STREAMING::REQUEST_IPL("hei_Carrier_int6");
		STREAMING::REQUEST_IPL("hei_carrier_LODLights");
		Vector3 Coords;
		Coords.x = 3069.330f; Coords.y = -4632.4f; Coords.z = 15.043f;
		TPto(Coords);
	}
	if (menu.Option("Sunken Cargoship")) {
		STREAMING::REQUEST_IPL("sunkcargoship");
		Vector3 Coords;
		Coords.x = -162.8918f; Coords.y = -2365.769f; Coords.z = 0.0f;
		TPto(Coords);
	}
	if (menu.Option("Hospital")) {
		STREAMING::REQUEST_IPL("RC12B_HospitalInterior");
		STREAMING::REQUEST_IPL("RC12B_Destroyed");
		Vector3 Coords;
		Coords.x = 356.8f; Coords.y = -590.1f; Coords.z = 43.3f;
		TPto(Coords);
	}
	if (menu.Option("Oneil Farm")) {
		STREAMING::REMOVE_IPL("farm_burnt");
		STREAMING::REMOVE_IPL("farm_burnt_props");
		STREAMING::REQUEST_IPL("farm");
		STREAMING::REQUEST_IPL("farm_props");
		STREAMING::REQUEST_IPL("farmint");
		STREAMING::REQUEST_IPL("farmint_cap");
		Vector3 Coords;
		Coords.x = 2441.2f; Coords.y = 4968.5f; Coords.z = 51.7f;
		TPto(Coords);
	}
	if (menu.Option("Life Invader Office")) {
		STREAMING::REQUEST_IPL("facelobby");
		STREAMING::REQUEST_IPL("facelobbyfake");
		Vector3 Coords;
		Coords.x = -1047.9f; Coords.y = -233.0f; Coords.z = 39.0f;
		TPto(Coords);
	}
	if (menu.Option("Cargoship")) {
		STREAMING::REQUEST_IPL("cargoship");
		Vector3 Coords;
		Coords.x = -162.8918f; Coords.y = -2365.769f; Coords.z = 9.3192f;
		TPto(Coords);
	}
	if (menu.Option("Jewelry Store")) {
		STREAMING::REQUEST_IPL("jewel2fake");
		STREAMING::REQUEST_IPL("post_hiest_unload");
		STREAMING::REQUEST_IPL("bh1_16_refurb");
		Vector3 Coords;
		Coords.x = -630.4f; Coords.y = -236.7f; Coords.z = 40.0f;
		TPto(Coords);
	}
	if (menu.Option("Morgue")) {
		STREAMING::REQUEST_IPL("Coroner_Int_on");
		STREAMING::REQUEST_IPL("coronertrash");
		Vector3 Coords;
		Coords.x = 244.9f; Coords.y = -1374.7f; Coords.z = 39.5f;
		TPto(Coords);
	}
}

void speciallocations()
{
	addTitle("Special Location");
	for (auto id : v_SpecialLocations)
	{
		std::string temp = id.name;
		if (menu.Option(temp))
		{
			STREAMING::REQUEST_IPL((char*)id.ipls.c_str());
			TPto(id.coords);
		}
	}
}

void ApartmentsNOIPL()
{
	addTitle("ApartMent");
	for (auto id : apartmentsnoipl)
	{
		if (menu.Option(id.name))
		{
			TPto({ id.x,id.y,id.z });
		}
	}
}

void ClubhouseWarehouses()
{
	addTitle("Club house Ware houses");
	for (auto id : v_ClubhouseWarehouses)
	{
		std::string temp = id.name;
		if (menu.Option(temp))
		{
			STREAMING::REQUEST_IPL((char*)id.ipls.c_str());
			TPto(id.coords);
		}
	}
}

void MazeBankWest()
{
	addTitle("Maze Bank");
	for (auto id : v_MazeBankWest)
	{
		std::string temp = id.name;
		if (menu.Option(temp))
		{
			STREAMING::REQUEST_IPL((char*)id.ipls.c_str());
			TPto(id.coords);
		}
	}
}

void LomBank()
{
	addTitle("Lom Bank");
	for (auto id : v_LomBank)
	{
		std::string temp = id.name;
		if (menu.Option(temp))
		{
			STREAMING::REQUEST_IPL((char*)id.ipls.c_str());
			TPto(id.coords);
		}
	}
}
//MazeBank
void MazeBank()
{
	addTitle("Maze Bank");
	for (auto id : v_MazeBank)
	{
		std::string temp = id.name;
		if (menu.Option(temp))
		{
			STREAMING::REQUEST_IPL((char*)id.ipls.c_str());
			TPto(id.coords);
		}
	}
}

void BusinessCentre()
{
	addTitle("Business Centre");
	for (auto id : v_BusinessCentre)
	{
		std::string temp = id.name;
		if (menu.Option(temp))
		{
			STREAMING::REQUEST_IPL((char*)id.ipls.c_str());
			TPto(id.coords);
		}
	}
}

void Apartment()
{
	addTitle("Apartment");
	for (auto id : v_Apartment)
	{
		std::string temp = id.name;
		if (menu.Option(temp))
		{
			STREAMING::REQUEST_IPL((char*)id.ipls.c_str());
			TPto(id.coords);
		}
	}
}

void Bunker()
{
	addTitle("Bunker");
	for (auto id : v_Bunker)
	{
		std::string temp = id.name;
		if (menu.Option(temp))
		{
			STREAMING::REQUEST_IPL((char*)id.ipls.c_str());
			TPto(id.coords);
		}
	}
}

void commonplace()
{
	addTitle(place);
	for (auto mark : targetPlace)
	{
		if (menu.Option(mark.name))
		{

			TPto({ mark.x, mark.y, mark.z });
		}
	}
}
void tel_main_menu()
{
	addTitle("Teleport");
	//menu.MenuOption("Menyoo Map Mods", "mapmod"); //Still Can't use, didn't Bypass Object Limit
	if (menu.Option("teleport to marker"))
	{
		teleport_to_marker();
	}
	if (menu.MenuOption("Common", "commonplace")) {
		place = "common";
		targetPlace.clear();
		targetPlace = commonCoords;
	}
	if (menu.MenuOption("Common", "commonplace")) {
		place = "Apartment";
		targetPlace.clear();
		targetPlace = apartmentsnoipl;
	}
	if (menu.MenuOption("Common", "commonplace")) {
		place = "Misc";
		targetPlace.clear();
		targetPlace = Miscs;
	}
	menu.MenuOption("Special Loc", "IPLs");
	menu.MenuOption("Special Location V2", "speciallocations");
	menu.MenuOption("Club house Ware houses", "ClubhouseWarehouses");
	menu.MenuOption("Maze Bank West", "MazeBankWest");
	menu.MenuOption("Maze Bank", "MazeBank");
	menu.MenuOption("Lom Bank", "LomBank");
	menu.MenuOption("Business Centre", "BusinessCentre");
	menu.MenuOption("Apartment", "Apartment");
	menu.MenuOption("Bunker", "Bunker");
	menu.MenuOption("ApartMent", "ApartmentsNOIPL");
	menu.MenuOption("Garage", "Garage");
}


void update_tel_menu()
{
	if (menu.CurrentMenu("teleport"))tel_main_menu();
	if (menu.CurrentMenu("commonplace"))commonplace();
	if (menu.CurrentMenu("IPLs"))update_IPLs();
	if (menu.CurrentMenu("speciallocations"))speciallocations();
	if (menu.CurrentMenu("ClubhouseWarehouses"))ClubhouseWarehouses();
	if (menu.CurrentMenu("MazeBankWest"))MazeBankWest();
	if (menu.CurrentMenu("MazeBank"))MazeBank();
	if (menu.CurrentMenu("LomBank"))LomBank();
	if (menu.CurrentMenu("BusinessCentre"))BusinessCentre();
	if (menu.CurrentMenu("Apartment"))Apartment();
	if (menu.CurrentMenu("Bunker"))Bunker();
	if (menu.CurrentMenu("ApartmentsNOIPL"))ApartmentsNOIPL();
	if (menu.CurrentMenu("Garage"))Garage();
}

void update_tel_game()
{

}