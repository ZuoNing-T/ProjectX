#pragma once
#include <set>
#include <tuple>
#include <string>
#include <vector>
#include "../../../SDK/inc/types.h"
typedef struct
{
	char* name;
	float x, y, z;
} teleportList;


class IPLScoords		//TODO::
{
public:
	IPLScoords() :name(""), ipls(""), coords({ 0.0f,0.0f,0.0f }) {}
	IPLScoords(std::string displayname, std::string ipls, Vector3 coords) :name(displayname), ipls(ipls), coords(coords) {}
	std::string name;
	std::string ipls;
	Vector3 coords;
};

extern std::vector<IPLScoords> v_SpecialLocations;
extern std::vector<IPLScoords> v_ClubhouseWarehouses;
extern std::vector<IPLScoords> v_MazeBankWest;
extern std::vector<IPLScoords> v_LomBank;
extern std::vector<IPLScoords> v_MazeBank;
extern std::vector<IPLScoords> v_BusinessCentre;
extern std::vector<IPLScoords> v_Apartment;
extern std::vector<IPLScoords> v_Bunker;


static  std::vector<teleportList> commonCoords = {
	{ "Strip Club DJ Booth", 126.135f,-1278.583f,29.270f },
{ "Blaine County Savings Bank", -109.299f,6464.035f,31.627f },
{ "Police Station", 436.491f, -982.172f,30.699f },
{ "Burnt FIB Building", 160.868f,-745.831f,250.063f },
{ "Humane Labs Tunnel", 3525.495f,3705.301f,20.992f },
{ "Ammunation Office", 12.494f,-1110.130f, 29.797f },
{ "Ammunation Gun Range",  22.153f,-1072.854f,29.797f },
{ "Trevor's Meth Lab", 1391.773f,3608.716f,38.942f },
{ "Pacific Standard Bank Vault", 255.851f, 217.030f,101.683f },
{ "Lester's House", 1273.898f,-1719.304f,54.771f },
{ "Floyd's Apartment", -1150.703f,-1520.713f,10.633f },
{ "FIB Top Floor", 135.733f,-749.216f,258.152f },
{ "IAA Office", 117.220f,-620.938f,206.047f },
{ "Pacific Standard Bank", 235.046f,216.434f,106.287f },
{ "Fort Zancudo ATC entrance", -2344.373f,3267.498f,32.811f },
{ "Fort Zancudo ATC top floor", -2358.132f,3249.754f,101.451f },
{ "Torture Room",  147.170f,-2201.804f,4.688f },
{ "Main LS Customs", -365.425f,-131.809f,37.873f },
{ "Very High Up", -129.964f,8130.873f,6705.307f },
{ "IAA Roof", 134.085f,-637.859f,262.851f },
{ "FIB Roof", 150.126f,-754.591f,262.865f },
{ "Maze Bank Roof", -75.015f,-818.215f,326.176f },
{ "Top of the Mt Chilad", 450.718f,5566.614f,806.183f },
{ "Most Northerly Point", 24.775f,7644.102f,19.055f },
{ "Vinewood Bowl Stage", 686.245f,577.950f,130.461f },
{ "Sisyphus Theater Stage", 205.316f,1167.378f,227.005f },
{ "Galileo Observatory Roof", -438.804f,1076.097f,352.411f },
{ "Kortz Center", -2243.810f,264.048f,174.615f },
{ "Chumash Historic Family Pier", -3426.683f,967.738f,8.347f },
{ "Paleto Bay Pier", -275.522f,6635.835f,7.425f },
{ "God's thumb", -1006.402f,6272.383f,1.503f },
{ "Calafia Train Bridge", -517.869f,4425.284f,89.795f },
{ "Altruist Cult Camp", -1170.841f,4926.646f,224.295f },
{ "Maze Bank Arena Roof", -324.300f,-1968.545f,67.002f },
{ "Marlowe Vineyards", -1868.971f,2095.674f,139.115f },
{ "Hippy Camp", 2476.712f,3789.645f,41.226f },
{ "Devin Weston's House", -2639.872f,1866.812f,160.135f },
{ "Abandon Mine", -595.342f, 2086.008f,131.412f },
{ "Weed Farm", 2208.777f,5578.235f,53.735f },
{ "Stab City",  126.975f,3714.419f,46.827f },
{ "Airplane Graveyard Airplane", 2395.096f,3049.616f,60.053f },
{ "Satellite Dish Antenna", 2034.988f,2953.105f,74.602f },
{ "Satellite Dishes",  2062.123f,2942.055f,47.431f },
{ "Windmill Top", 2026.677f,1842.684f,133.313f },
{ "Sandy Shores Building Crane", 1051.209f,2280.452f,89.727f },
{ "Rebel Radio", 736.153f,2583.143f,79.634f },
{ "Quarry", 2954.196f,2783.410f,41.004f },
{ "Palmer Power Station Chimney",  2732.931f, 1577.540f,83.671f },
{ "Merryweather Dock",  486.417f,-3339.692f,6.070f },
{ "Cargo Ship", 899.678f,-2882.191f,19.013f },
{ "Del Perro Pier", -1850.127f,-1231.751f,13.017f },
{ "Jolene Cranley-Evans Ghost", 3059.620f,5564.246f,197.091f },
{ "NOOSE Headquarters", 2535.243f,-383.799f,92.993f },
{ "Snowman",  971.245f,-1620.993f,30.111f },
{ "Oriental Theater", 293.089f,180.466f,104.301f },
{ "Beach Skatepark", -1374.881f,-1398.835f,6.141f },
{ "Underpass Skatepark", 718.341f,-1218.714f, 26.014f },
{ "Casino", 925.329f,46.152f,80.908f },
{ "University of San Andreas", -1696.866f,142.747f,64.372f },
{ "La Puerta Freeway Bridge",  -543.932f,-2225.543f,122.366f },
{ "Land Act Dam",  1660.369f,-12.013f,170.020f },
{ "Mount Gordo",  2877.633f,5911.078f,369.624f },
{ "Little Seoul", -889.655f,-853.499f,20.566f },
{ "Epsilon Building", -695.025f,82.955f,55.855f },
{ "The Richman Hotel", -1330.911f,340.871f,64.078f },
{ "Vinewood sign", 711.362f,1198.134f,348.526f },
{ "Los Santos Golf Club", -1336.715f,59.051f,55.246f },
{ "Chicken", -31.010f,6316.830f,40.083f },
{ "Little Portola", -635.463f,-242.402f,38.175f },
{ "Pacific Bluffs Country Club", -3022.222f,39.968f,13.611f },
{ "Vinewood Cemetery ", -1659.993f,-128.399f,59.954f },
{ "Paleto Sawmill Chimney", -549.467f,5308.221f,114.146f },
{ "Mirror Park", 1070.206f,-711.958f,58.483f },
{ "Rocket", 1608.698f,6438.096f,37.637f },
{ "El Gordo Lighthouse", 3430.155f,5174.196f,41.280f },
{ "Mile High Club", -144.274f,-946.813f,269.135f },
{ "Sunken Body", -3161.078f,3001.998f,-37.974f },
{ "Underwater WW2 Tank", 4201.633f,3643.821f,-39.016f },
{ "Dead Sea Monster", -3373.726f,504.714f,-24.656f },
{ "Underwater UFO",  762.426f,7380.371f,-111.377f },
{ "Underwater Hatch",  4273.950f, 2975.714f,-170.746f },
{ "Sunken Plane",  -942.350f,6608.752f,-20.912f },
{ "Sunken Cargo Ship", 3199.748f,-379.018f,-22.500f },
{ "High in the Sky!!", -129.9f, 8130.8f, 6705.6f },
{ "Mount Chilliad", 496.0635f, 5584.5142f, 793.9454f },
{ "Mine Shaft", -596.93f, 2094.12f, 132.00f },
{ "military Base", -2138.234f, 3250.8606f, 34.00f },
{ "Airport", -1135.1100f, -2885.2030f, 15.00f },
{ "Trevers Airfield", 1590.6788f, 3267.6698f, 43.0000f },
{ "Out To Sea", 1845.673f, -13787.4884f, 0.0000f },
{ "Island", -2159.147f, 5196.89f, 20.00f },
{ "Under Water UFO", 760.461f, 7392.8032f, -110.0774f },
{ "Under Water Plane Crash", 1846.0f, -2946.855f, -33.32f },
{ "Water Fall", -552.0047f, 4439.4487f, 35.123f },
{ "Humane Labs Level 1", 3617.3726f, 3738.2727f, 30.6901f },
{ "Humane Labs Level 2", 3525.6133f, 3709.2998f, 22.9918f },
{ "Inside FIB Building", 136.3807f, -749.0196f, 258.1517f },
{ "Inside Fire FIB", 137.8378f, -747.39f, 253.152f },
{ "Inside FIB Lift", 133.1019f, -735.7224f, 235.63f },
{ "Inside IAA Building", 127.49f, -618.26f, 207.04f },
{ "Maze Bank ", -75.5003f, -819.0528f, 327.00f },
{ "Del Perro Pier", -1838.834f, -1223.333f, 15.00f },
{ "Vinewood Sign", 729.909f, 1204.37f, 326.0209f },
{ "Beeker's Garage", 139.67f, 6595.94f, 33.00f },
{ "400k/500k Apartment", -793.36f, 296.86f, 87.84f },
{ "Appartment", -778.34f, 339.97f, 208.62f },
{ "Mors Mutual Insurance", -232.74f, -1163.556f, 24.95f },
{ "Impound Lot", 408.923f, -1633.860f, 30.29f },
{ "Inside 10 Car Garage", 228.71f, -989.98f, -96.00f },
{ "Under The Map", 132.1470f, -739.5430f, 39.00f },
{ "Strip Club", 125.428f, -1290.40f, 30.00f },
{ "Prison", 1696.3642f, 2561.377f, 47.56f },
{ "Maze", -2311.01f, 234.33f, 170.63f },
{ "Ammunation", 233.3912f, -41.08f, 69.67f },
{ "Race Track", 1201.36f, 95.65f, 82.03f },
{ "parachute Jump", -521.35f, 4422.00f, 89.00f },
{ "michael's House", -827.13f, 175.47f, 70.82f },
{ "michael's House Inside", -814.38f, 178.92f, 73.00f },
{ "Franklins's House Old", -14.31f, -1437.00f, 30.00f },
{ "Franklins's House New", 7.05f, 524.33f, 174.97f },
{ "Helicopter Pad", -741.54f, -1456.00f, 3.00f },
{ "LS Customs", -363.9027f, -132.71f, 39.00f },
{ "Random", 2861.426f, 5927.89f, 361.29f },
{ "Trevers Meth Lab", 1390.28f, 3608.60f, 39.00f },
{ "Dam 1", 1663.123f, 24.18f, 169.00f },
{ "Dam 2", 115.28f, 785.81f, 212.00f },
{ "Cave", -1911.3f, 1389.29f, 219.00f },
{ "Farest Island North", 32.51f, 7688.99f, 4.00f },
{ "Farest Island South", 1799.90f, -2823.90f, 5.00f },
{ "Flight School", -1153.10f, -2713.39f, 20.00f },
{ "Tram Station", 104.50f, -1718.30f, 31.00f },
{ "Golf", -1079.71f, 10.04f, 51.00f },
{ "Stage", 684.97f, 574.32f, 131.00f },
{ "Drift Mountain", 860.32f, 1316.65f, 356.00f },
{ "Consturction Building", -161.26f, -937.87f, 268.52f }
};

static  std::vector<teleportList> apartmentsnoipl = {

	{ "Low End Apartment",			261.4586f, -998.8196f, -99.00863f },
{ "Medium End Apartment",		347.2686f, -999.2955f, -99.19622f },
{ "4 Integrity Way, Apt 28",	-18.07856f, -583.6725f, 79.46569f },
{ "4 Integrity Way, Apt 30",	-35.31277f, -580.4199f, 88.71221f },
{ "Dell Perro Heights, Apt 4",  -1468.14f, -541.815f, 73.4442f },
{ "Dell Perro Heights, Apt 7",  -1477.14f, -538.7499f, 55.5264f },
{ "Richard Majestic, Apt 2",	-915.811f, -379.432f, 113.6748f },
{ "Tinsel Towers, Apt 42",		 -614.86f, 40.6783f, 97.60007f },
{ "Eclipse Towers, Apt 3",		-773.407f, 341.766f, 211.397f },
{ "3655 Wild Oats Drive",			-169.286f, 486.4938f, 137.4436f },
{ "2044 North Conker Avenue",		340.9412f, 437.1798f, 149.3925f },
{ "2045 North Conker Avenue",		 373.023f, 416.105f, 145.7006f },
{ "2862 Hillcrest Avenue",			-676.127f, 588.612f, 145.1698f },
{ "2868 Hillcrest Avenue",		-763.107f, 615.906f, 144.1401f },
{ "2874 Hillcrest Avenue",			 -857.798f, 682.563f, 152.6529f },
{ "2677 Whispymound Drive",			120.5f, 549.952f, 184.097f },
{ "2133 Mad Wayne Thunder",			-1288.0f, 440.748f, 97.69459f },
};

static  std::vector<teleportList> Miscs = {
	{ "Bunker Interior",899.5518f,-3246.038f, -98.04907f },
{ "CharCreator",402.5164f, -1002.847f, -99.2587f },
{ "Mission Carpark",405.9228f, -954.1149f, -99.6627f },
{ "Torture Room",136.5146f, -2203.149f, 7.30914f },
{ "Solomon's Office",-1005.84f, -478.92f, 50.02733f },
{ "Psychiatrist's Office",-1908.024f, -573.4244f, 19.09722f },
{ "Omega's Garage",2331.344f, 2574.073f, 46.68137f },
{ "Movie Theatre",-1427.299f, -245.1012f, 16.8039f },
{ "Motel",152.2605f, -1004.471f, -98.99999f },
{ "Mandrazos Ranch",152.2605f, 1146.954f, 114.337f },
{ "Life Invader Office",-1044.193f, -236.9535f, 37.96496f },
{ "Lester's House",1273.9f, -1719.305f, 54.77141f },
{ "FBI Top Floor",134.5835f, -749.339f, 258.152f },
{ "FBI Floor 47",134.5835f, -766.486f, 234.152f },
{ "FBI Floor 49",134.635f, -765.831f, 242.152f },
{ "IAA Office",117.22f, -620.938f, 206.1398f },
{ "Smuggler's Run Hangar",-1266.802f, -3014.837f, -49.000f },
{ "Avenger Interior",520.0f, 4750.0f, -70.0f },
{ "Facility",345.0041f, 4842.001f, -59.9997f },
{ "Server Farm",2168.0f, 2920.0f, -84.0f },
{ "Submarine",514.33f, 4886.18f, -62.59f },
{ "IAA Facility",2147.91f, 2921.0f, -61.9f },
{ "Nightclub",-1604.664f, -3012.583f, -78.000f },
{ "Nightclub Warehouse",-1505.783f, -3012.587f, -80.000f },
{ "Terrorbyte Interior",-1421.015f, -3012.587f, -80.000f },
};

inline std::vector<IPLScoords> Build_SpecialLocations();
inline std::vector<IPLScoords> Build_ClubhouseWarehouses();
inline std::vector<IPLScoords> Build_MazeBankWest();
inline std::vector<IPLScoords> Build_LomBank();
inline std::vector<IPLScoords> Build_MazeBank();
inline std::vector<IPLScoords> Build_BusinessCentre();
inline std::vector<IPLScoords> Build_Apartment();
inline std::vector<IPLScoords> Build_Bunker();


bool BuildTeleport();
void update_tel_menu();