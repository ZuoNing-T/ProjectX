#pragma once

#include "../internal_native.h"
#include "menu.h"
#include "menucontrols.h"
#include "menuutils.h"
#include "menusettings.h"
#include "../Function/Function.h"

#include <string>
#include <windows.h>
#include <vector>
#include <functional>
#include <array>
#include <unordered_map>
#include <map>


namespace NativeMenu {
	class Menu {
	public:
		/*
		 * c'tor and d'tor. As of current they don't do a lot.
		 */
		Menu();
		~Menu();

		/*
		 * Specify settings file name/location. If not set, it will use default settings.
		 * Calling this is pretty much mandatory. It's advised to call this just once after
		 * figuring out the directory structure.
		 */
		void SetFiles(const std::string & fileName);

		/*
		 * Read settings file. If no specified settings file, it'll use default settings.
		 * Calling this is pretty much mandatory. It's advised to call this whenever new settings
		 * need to be parsed, for example, on re-opening the menu or something.
		 */
		void ReadSettings();

		void SaveSettings();

		/*
		 * Registers a function that will be called when the menu is opened.
		 */
		void RegisterOnMain(std::function<void() > onMain);

		/*
		 * Registers a function that will be called when the menu is closed.
		 */
		void RegisterOnExit(std::function<void() > onExit);

		/*
		 * Main menu is always called "mainmenu".
		 * Otherwise menuname is a submenu name.
		 * Returns true when inside the submenu menuname.
		 */
		bool CurrentMenu(std::string menuname);

		/*
		 * Always assign a title to a submenu!
		 */
		void Title(std::string title);
		void Title(std::string title, float customSize);
		void Title(std::string title, std::string dict, std::string texture);
		void Title(std::string title, std::string dict, std::string texture, float customSize);

		/*
		 * Custom title textures have a resolution of 512x128, but any other
		 * resolution with the same aspect ratio should work (4:1)
		 */
		void Title(std::string title, int textureHandle);
		void Title(std::string title, int textureHandle, float customSize);

		/*
		 * A menu subtitle. This is optional. If added, this must be added directly
		 * below the title, before any options are specified.
		 */
		void Subtitle(std::string subtitle);

		/*
		 * Optional: Specify a different background texture for the footer.
		 * If not used, solid black is used by default.
		 */
		void Footer(Color color);
		void Footer(std::string dict = "ProjectX", std::string texture = "Footer");

		/*
		 * Normal option.
		 * Shows nothing special.
		 * Returns true on accept.
		 */

		bool Option(std::string option, std::vector<std::string> details = {}, bool isTranslate = true,  bool isprivate = false);
		bool Option(std::string option, Color highlight, std::vector<std::string> details = {},  bool isprivate = false);

		/*
		 * Submenu option.
		 * Shows option with menu sign.
		 * Switches menu on action.
		 * Returns true on accept.
		 */
		bool MenuOption(std::string option, std::string menu, std::vector<std::string> details = {}, bool isTranslate = true, bool isprivate = false);

		/*
		 * Option that shows an extra pane to the right.
		 * Shows text with extra's specifyable in the detail pane.
		 * Function pointers can be passed and are called on right, left press.
		 * Custom pane title can be specified.
		 * Extra draws external image if a line is "!IMG:<file handle>W<height>H<width>".
		 * Extra draws sprite if a line is "!SPR:D<dict>N<name>W<height>H<width>".
		 * Extra can be left empty.
		 * "highlighted" indicates the highlight status of the option. It can be a nullptr.
		 * Returns true on accept.
		 */
		bool OptionPlus(std::string option, std::vector<std::string> &extra, bool *highlighted = nullptr,
			std::function<void()> onRight = nullptr, std::function<void()> onLeft = nullptr,
			std::string title = "Info", std::vector<std::string> details = {});

		/*
		 * Can be used to draw the OptionPlus extras separately. Useful when generating
		 * the extra text is costful or if no other things are needed. Running this when
		 * OptionPlus is highlighted can improve performance.
		 */
		void OptionPlusPlus(std::vector<std::string> &extra, std::string title = "Info");

		/*
		 * Option that changes an int value with optional custom-sized steps.
		 * Shows option with the value inside < > brackets.
		 * Returns true on accept, left and right.
		 */
		bool IntOption(std::string option, int &var, int min, int max, int step = 1, std::vector<std::string> details = {},  bool isTranslate = true, bool isprivate = false);

		/*
		 * Option that changes a float value with optional custom-sized steps.
		 * Shows option with the value inside < > brackets.
		 * Returns true on accept, left and right.
		 */
		bool FloatOption(std::string option, float &var, float min, float max, float step = 0.1f, std::vector<std::string> details = {}, bool isTranslate = true, bool isprivate = false);

		/*
		 * Option that toggles a boolean.
		 * Shows option with a checkbox, which is checked when the passed var is "true".
		 * Returns true on accept.
		 */
		bool BoolOption(std::string option, bool &var, std::vector<std::string> details = {}, bool isTranslate = true, bool isprivate = false);

		/*
		 * Option that displays a boolean with a specifyable texture.
		 * Shows option with a checkbox, which is checked when the passed var is "true".
		 * Returns true on accept.
		 */
		bool BoolSpriteOption(std::string option, bool var, std::string category, std::string spriteOn, std::string spriteOff, std::vector<std::string> details = {});

		/*
		 * Option that shows a scrollable list of supplied ints.
		 * Shows option with the current value inside < > brackets.
		 * Value shown is display[iterator].
		 * On left or right press, iterator's value is incremented or decremented.
		 * Returns true on accept, left and right.
		 */
		bool IntArray(std::string option, std::vector<int> display, int &iterator, std::vector<std::string> details = {}, bool isTranslate = true, bool isprivate = false);

		/*
		 * Option that shows a scrollable list of supplied floats.
		 * Shows option with the current value inside < > brackets.
		 * Value shown is display[iterator].
		 * On left or right press, iterator's value is incremented or decremented.
		 * Returns true on accept, left and right.
		 */
		bool FloatArray(std::string option, std::vector<float> display, int &iterator, std::vector<std::string> details = {}, bool isTranslate = true, bool isprivate = false);

		/*
		 * Option that shows a scrollable list of supplied strings.
		 * Shows option with the current value inside < > brackets.
		 * Value shown is display[iterator].
		 * On left or right press, iterator's value is incremented or decremented.
		 * Returns true on accept, left and right.
		 */
		bool StringArray(std::string option, std::vector<std::string> display, int &iterator, std::vector<std::string> details = {}, bool isTranslate = true, bool isprivate = false);
		void drawInstructionalButtons();
		void drawMenuDetails();

		/*
		 * Draws the menu backgrounds and processes menu navigation key inputs.
		 * Must be called at the end of the menu processing block.
		 */
		void EndMenu();

		/*
		 * Must be used at the beginning of the menu update loop!
		 * Checks input keys and processes them for navigation in the menu with MenuControls
		 */
		void CheckKeys();

		/*
		 * Opens the menu programmatically and calls onMain.
		 * Does nothing if the menu is already open.
		 */
		void OpenMenu();


		/*
		 * Closes the menu and calls onExit.
		 */
		void CloseMenu();

		/*
		 * Returns the filled in menu controls. This can be used for display or
		 * input verification purposes.
		 */
		const MenuControls &GetControls();

		/*
		 * Returns true if this instance of the menu is open
		 */
		bool IsThisOpen();

		/*
		Marker Setting
		*/
		int markerType;
		float markerOffset;
		Vector3 mDir, mRot, mScale;
		Color mRgb;
		bool bobUpAndDown, faceCamera, rotate;
		void DrawMarker(Vector3 Pos);
		/*
		 * Image prefix string for if you want to show an image in an OptionPlus.
		 */
		const std::string ImagePrefix = "!IMG:";
		const std::string SpritePrefix = "!SPR:";

		/*
		 * These should be filled in by MenuSettings.ReadSettings().
		 */

		float menuX = 0.0f;
		float menuY = 0.01f;
		std::string cheatString = "";
		//◊‘∂®“Â≈‰÷√
		std::string username = "";
		std::string Role = "";

		Color titleTextColor = { 0,0,255,255 };
		Color titleBackgroundColor = solidWhite;
		Color menuOption = { 255,255,255,255 };
		Color subtitlecolor = { 255,	255, 255, 150 };
		Color menuOptionSelect = solidBlack;
		int titleFont = 1;

		Color optionsTextColor = solidWhite;
		Color optionsBackgroundColor = solidBlack;

		Color optionsTextSelectColor = solidBlack;
		Color optionsBackgroundSelectColor = solidWhite;
		float glareX = 0.0f;
		float glareY = 0.0f;
		float glareWidth = 0.0f;
		float glareHeight = 0.0f;
		int optionsFont = 0;
		int titleTextureIndex = 3;
		int specialcolor = 0;
		int Language = 0;
		bool glareBool = true;
		std::string titlename = "Project X";
		std::string toggle, up, down, left, right, cancle, select;
		void Setkeys(std::string keyname, MenuControls::ControlType type);
		float Customwidth = 0;
		float Customheight = 0;
		float CustomX = 0;
		float CustomY = 0;
		int optionselectnum = 1;
		bool Custom = false;
		std::vector <std::string> strHudColor =
		{
			"HUD_COLOUR_PURE_WHITE",
			"HUD_COLOUR_WHITE",
			"HUD_COLOUR_BLACK",
			"HUD_COLOUR_GREY",
			"HUD_COLOUR_GREYLIGHT",
			"HUD_COLOUR_GREYDARK",
			"HUD_COLOUR_RED",
			"HUD_COLOUR_REDLIGHT",
			"HUD_COLOUR_REDDARK",
			"HUD_COLOUR_BLUE",
			"HUD_COLOUR_BLUELIGHT",
			"HUD_COLOUR_BLUEDARK",
			"HUD_COLOUR_YELLOW",
			"HUD_COLOUR_YELLOWLIGHT",
			"HUD_COLOUR_YELLOWDARK",
			"HUD_COLOUR_ORANGE",
			"HUD_COLOUR_ORANGELIGHT",
			"HUD_COLOUR_ORANGEDARK",
			"HUD_COLOUR_GREEN",
			"HUD_COLOUR_GREENLIGHT",
			"HUD_COLOUR_GREENDARK",
			"HUD_COLOUR_PURPLE",
			"HUD_COLOUR_PURPLELIGHT",
			"HUD_COLOUR_PURPLEDARK",
			"HUD_COLOUR_PINK",
			"HUD_COLOUR_RADAR_HEALTH",
			"HUD_COLOUR_RADAR_ARMOUR",
			"HUD_COLOUR_RADAR_DAMAGE",
			"HUD_COLOUR_NET_PLAYER1",
			"HUD_COLOUR_NET_PLAYER2",
			"HUD_COLOUR_NET_PLAYER3",
			"HUD_COLOUR_NET_PLAYER4",
			"HUD_COLOUR_NET_PLAYER5",
			"HUD_COLOUR_NET_PLAYER6",
			"HUD_COLOUR_NET_PLAYER7",
			"HUD_COLOUR_NET_PLAYER8",
			"HUD_COLOUR_NET_PLAYER9",
			"HUD_COLOUR_NET_PLAYER10",
			"HUD_COLOUR_NET_PLAYER11",
			"HUD_COLOUR_NET_PLAYER12",
			"HUD_COLOUR_NET_PLAYER13",
			"HUD_COLOUR_NET_PLAYER14",
			"HUD_COLOUR_NET_PLAYER15",
			"HUD_COLOUR_NET_PLAYER16",
			"HUD_COLOUR_NET_PLAYER17",
			"HUD_COLOUR_NET_PLAYER18",
			"HUD_COLOUR_NET_PLAYER19",
			"HUD_COLOUR_NET_PLAYER20",
			"HUD_COLOUR_NET_PLAYER21",
			"HUD_COLOUR_NET_PLAYER22",
			"HUD_COLOUR_NET_PLAYER23",
			"HUD_COLOUR_NET_PLAYER24",
			"HUD_COLOUR_NET_PLAYER25",
			"HUD_COLOUR_NET_PLAYER26",
			"HUD_COLOUR_NET_PLAYER27",
			"HUD_COLOUR_NET_PLAYER28",
			"HUD_COLOUR_NET_PLAYER29",
			"HUD_COLOUR_NET_PLAYER30",
			"HUD_COLOUR_NET_PLAYER31",
			"HUD_COLOUR_NET_PLAYER32",
			"HUD_COLOUR_SIMPLEBLIP_DEFAULT",
			"HUD_COLOUR_MENU_BLUE",
			"HUD_COLOUR_MENU_GREY_LIGHT",
			"HUD_COLOUR_MENU_BLUE_EXTRA_DARK",
			"HUD_COLOUR_MENU_YELLOW",
			"HUD_COLOUR_MENU_YELLOW_DARK",
			"HUD_COLOUR_MENU_GREEN",
			"HUD_COLOUR_MENU_GREY",
			"HUD_COLOUR_MENU_GREY_DARK",
			"HUD_COLOUR_MENU_HIGHLIGHT",
			"HUD_COLOUR_MENU_STANDARD",
			"HUD_COLOUR_MENU_DIMMED",
			"HUD_COLOUR_MENU_EXTRA_DIMMED",
			"HUD_COLOUR_BRIEF_TITLE",
			"HUD_COLOUR_MID_GREY_MP",
			"HUD_COLOUR_NET_PLAYER1_DARK",
			"HUD_COLOUR_NET_PLAYER2_DARK",
			"HUD_COLOUR_NET_PLAYER3_DARK",
			"HUD_COLOUR_NET_PLAYER4_DARK",
			"HUD_COLOUR_NET_PLAYER5_DARK",
			"HUD_COLOUR_NET_PLAYER6_DARK",
			"HUD_COLOUR_NET_PLAYER7_DARK",
			"HUD_COLOUR_NET_PLAYER8_DARK",
			"HUD_COLOUR_NET_PLAYER9_DARK",
			"HUD_COLOUR_NET_PLAYER10_DARK",
			"HUD_COLOUR_NET_PLAYER11_DARK",
			"HUD_COLOUR_NET_PLAYER12_DARK",
			"HUD_COLOUR_NET_PLAYER13_DARK",
			"HUD_COLOUR_NET_PLAYER14_DARK",
			"HUD_COLOUR_NET_PLAYER15_DARK",
			"HUD_COLOUR_NET_PLAYER16_DARK",
			"HUD_COLOUR_NET_PLAYER17_DARK",
			"HUD_COLOUR_NET_PLAYER18_DARK",
			"HUD_COLOUR_NET_PLAYER19_DARK",
			"HUD_COLOUR_NET_PLAYER20_DARK",
			"HUD_COLOUR_NET_PLAYER21_DARK",
			"HUD_COLOUR_NET_PLAYER22_DARK",
			"HUD_COLOUR_NET_PLAYER23_DARK",
			"HUD_COLOUR_NET_PLAYER24_DARK",
			"HUD_COLOUR_NET_PLAYER25_DARK",
			"HUD_COLOUR_NET_PLAYER26_DARK",
			"HUD_COLOUR_NET_PLAYER27_DARK",
			"HUD_COLOUR_NET_PLAYER28_DARK",
			"HUD_COLOUR_NET_PLAYER29_DARK",
			"HUD_COLOUR_NET_PLAYER30_DARK",
			"HUD_COLOUR_NET_PLAYER31_DARK",
			"HUD_COLOUR_NET_PLAYER32_DARK",
			"HUD_COLOUR_BRONZE",
			"HUD_COLOUR_SILVER",
			"HUD_COLOUR_GOLD",
			"HUD_COLOUR_PLATINUM",
			"HUD_COLOUR_GANG1",
			"HUD_COLOUR_GANG2",
			"HUD_COLOUR_GANG3",
			"HUD_COLOUR_GANG4",
			"HUD_COLOUR_SAME_CREW",
			"HUD_COLOUR_FREEMODE",
			"HUD_COLOUR_PAUSE_BG",
			"HUD_COLOUR_FRIENDLY",
			"HUD_COLOUR_ENEMY",
			"HUD_COLOUR_LOCATION",
			"HUD_COLOUR_PICKUP",
			"HUD_COLOUR_PAUSE_SINGLEPLAYER",
			"HUD_COLOUR_FREEMODE_DARK",
			"HUD_COLOUR_INACTIVE_MISSION",
			"HUD_COLOUR_DAMAGE",
			"HUD_COLOUR_PINKLIGHT",
			"HUD_COLOUR_PM_MITEM_HIGHLIGHT",
			"HUD_COLOUR_SCRIPT_VARIABLE",
			"HUD_COLOUR_YOGA",
			"HUD_COLOUR_TENNIS",
			"HUD_COLOUR_GOLF",
			"HUD_COLOUR_SHOOTING_RANGE",
			"HUD_COLOUR_FLIGHT_SCHOOL",
			"HUD_COLOUR_NORTH_BLUE",
			"HUD_COLOUR_SOCIAL_CLUB",
			"HUD_COLOUR_PLATFORM_BLUE",
			"HUD_COLOUR_PLATFORM_GREEN",
			"HUD_COLOUR_PLATFORM_GREY",
			"HUD_COLOUR_FACEBOOK_BLUE",
			"HUD_COLOUR_INGAME_BG",
			"HUD_COLOUR_DARTS",
			"HUD_COLOUR_WAYPOINT",
			"HUD_COLOUR_MICHAEL",
			"HUD_COLOUR_FRANKLIN",
			"HUD_COLOUR_TREVOR",
			"HUD_COLOUR_GOLF_P1",
			"HUD_COLOUR_GOLF_P2",
			"HUD_COLOUR_GOLF_P3",
			"HUD_COLOUR_GOLF_P4",
			"HUD_COLOUR_WAYPOINTLIGHT",
			"HUD_COLOUR_WAYPOINTDARK",
			"HUD_COLOUR_PANEL_LIGHT",
			"HUD_COLOUR_MICHAEL_DARK",
			"HUD_COLOUR_FRANKLIN_DARK",
			"HUD_COLOUR_TREVOR_DARK",
			"HUD_COLOUR_OBJECTIVE_ROUTE",
			"HUD_COLOUR_PAUSEMAP_TINT",
			"HUD_COLOUR_PAUSE_DESELECT",
			"HUD_COLOUR_PM_WEAPONS_PURCHASABLE",
			"HUD_COLOUR_PM_WEAPONS_LOCKED",
			"HUD_COLOUR_END_SCREEN_BG",
			"HUD_COLOUR_CHOP",
			"HUD_COLOUR_PAUSEMAP_TINT_HALF",
			"HUD_COLOUR_NORTH_BLUE_OFFICIAL",
			"HUD_COLOUR_SCRIPT_VARIABLE_2",
			"HUD_COLOUR_H",
			"HUD_COLOUR_HDARK",
			"HUD_COLOUR_T",
			"HUD_COLOUR_TDARK",
			"HUD_COLOUR_HSHARD",
			"HUD_COLOUR_CONTROLLER_MICHAEL",
			"HUD_COLOUR_CONTROLLER_FRANKLIN",
			"HUD_COLOUR_CONTROLLER_TREVOR",
			"HUD_COLOUR_CONTROLLER_CHOP",
			"HUD_COLOUR_VIDEO_EDITOR_VIDEO",
			"HUD_COLOUR_VIDEO_EDITOR_AUDIO",
			"HUD_COLOUR_VIDEO_EDITOR_TEXT",
			"HUD_COLOUR_HB_BLUE",
			"HUD_COLOUR_HB_YELLOW",
			"HUD_COLOUR_VIDEO_EDITOR_SCORE",
			"HUD_COLOUR_VIDEO_EDITOR_AUDIO_FADEOUT",
			"HUD_COLOUR_VIDEO_EDITOR_TEXT_FADEOUT",
			"HUD_COLOUR_VIDEO_EDITOR_SCORE_FADEOUT",
			"HUD_COLOUR_HEIST_BACKGROUND",
			"HUD_COLOUR_VIDEO_EDITOR_AMBIENT",
			"HUD_COLOUR_VIDEO_EDITOR_AMBIENT_FADEOUT",
			"HUD_COLOUR_GB",
			"HUD_COLOUR_G",
			"HUD_COLOUR_B",
			"HUD_COLOUR_LOW_FLOW",
			"HUD_COLOUR_LOW_FLOW_DARK",
			"HUD_COLOUR_G1",
			"HUD_COLOUR_G2",
			"HUD_COLOUR_G3",
			"HUD_COLOUR_G4",
			"HUD_COLOUR_G5",
			"HUD_COLOUR_G6",
			"HUD_COLOUR_G7",
			"HUD_COLOUR_G8",
			"HUD_COLOUR_G9",
			"HUD_COLOUR_G10",
			"HUD_COLOUR_G11",
			"HUD_COLOUR_G12",
			"HUD_COLOUR_G13",
			"HUD_COLOUR_G14",
			"HUD_COLOUR_G15",
			"HUD_COLOUR_ADVERSARY",
			"HUD_COLOUR_DEGEN_RED",
			"HUD_COLOUR_DEGEN_YELLOW",
			"HUD_COLOUR_DEGEN_GREEN",
			"HUD_COLOUR_DEGEN_CYAN",
			"HUD_COLOUR_DEGEN_BLUE",
			"HUD_COLOUR_DEGEN_MAGENTA",
			"HUD_COLOUR_STUNT_1",
			"HUD_COLOUR_STUNT_2"
		};

	private:
		const std::vector<std::string> textureNames = {
			"",
			"gradient_nav",
			"interaction_bgd",
			"gradient_bgd",
			"gradient_nav",
			"shopui_title_barber",
			"shopui_title_barber2",
			"shopui_title_barber3",
			"shopui_title_barber4",
			"shopui_title_carmod",
			"shopui_title_carmod2",
			"shopui_title_clubhousemod",
			"shopui_title_conveniencestore",
			"shopui_title_tennisstore",
			"shopui_title_darts",
			"shopui_title_exec_vechupgrade",
			"shopui_title_gasstation",
			"shopui_title_golfshop",
			"shopui_title_gr_gunmod",
			"shopui_title_graphics_franklin",
			"shopui_title_graphics_michael",
			"shopui_title_graphics_trevor",
			"shopui_title_gunclub",
			"shopui_title_highendfashion",
			"shopui_title_highendsalon",
			"shopui_title_ie_modgarage",
			"shopui_title_liquorstore",
			"shopui_title_liquorstore2",
			"shopui_title_liquorstore3",
			"shopui_title_lowendfashion",
			"shopui_title_lowendfashion2",
			"shopui_title_midfashion",
			"shopui_title_movie_masks",
			"shopui_title_sm_hangar",
			"shopui_title_supermod",
			"shopui_title_tattoos",
			"shopui_title_tattoos2",
			"shopui_title_tattoos3",
			"shopui_title_tattoos4",
			"shopui_title_tattoos5",
			"shopui_title_tennis",
			"suemurry_background_left"
		};
		const std::vector<std::string> textureDicts = {
			"",
			"commonmenu",
			"commonmenu",
			"commonmenu",
			"commonmenu",
			"shopui_title_barber",
			"shopui_title_barber2",
			"shopui_title_barber3",
			"shopui_title_barber4",
			"shopui_title_carmod",
			"shopui_title_carmod2",
			"shopui_title_clubhousemod",
			"shopui_title_conveniencestore",
			"shopui_title_conveniencestore",
			"shopui_title_darts",
			"shopui_title_exec_vechupgrade",
			"shopui_title_gasstation",
			"shopui_title_golfshop",
			"shopui_title_gr_gunmod",
			"shopui_title_graphics_franklin",
			"shopui_title_graphics_michael",
			"shopui_title_graphics_trevor",
			"shopui_title_gunclub",
			"shopui_title_highendfashion",
			"shopui_title_highendsalon",
			"shopui_title_ie_modgarage",
			"shopui_title_liquorstore",
			"shopui_title_liquorstore2",
			"shopui_title_liquorstore3",
			"shopui_title_lowendfashion",
			"shopui_title_lowendfashion2",
			"shopui_title_midfashion",
			"shopui_title_movie_masks",
			"shopui_title_sm_hangar",
			"shopui_title_supermod",
			"shopui_title_tattoos",
			"shopui_title_tattoos2",
			"shopui_title_tattoos3",
			"shopui_title_tattoos4",
			"shopui_title_tattoos5",
			"shopui_title_tennis"
		};

		static const unsigned maxMenus = 255;
		enum class FooterType {
			Default,
			Color,
			Sprite
		};

		MenuControls controls;
		MenuSettings settings;

		std::function<void() > onMain = nullptr;
		std::function<void() > onExit = nullptr;

		/*
		 * Due to how this menu was designed initially, it's expected that
		 * Menu.End() would be called at the end of the menu tick. At Menu.End(),
		 * all menu options and option counts are known. This information is needed
		 * by the background drawing tasks, so we will store the functions until
		 * the information we need is known. Since we're storing draw calls anyway,
		 * we can split them to draw them in specific "layers". This wasn't a
		 * problem when the backgrounds were just rects, but with sprites this is
		 * important.
		 */
		typedef std::vector<std::function<void(void)>> functionList;
		functionList backgroundglareDraws;
		functionList GlareDraws;
		functionList backgroundSpriteDraws;		// drawSprite
		functionList backgroundRectDraws;		// drawRect
		functionList highlightsSpriteDraws;		// drawSprite
		functionList foregroundSpriteCalls;		// drawSprite
		functionList spriteDraws;
		functionList textDraws;					// drawText


		/*
		 * Detail text also needs to know Y-coordinate to start drawing properly.
		 */
		std::vector<std::string> details;

		/*
		 * These members aren't as modifyable, as they depend on one another. I
		 * wasn't able to find relations between them, so these should not be changed
		 * runtime. They're set to resemble NativeUI / GTA V's UI as much as possible.
		 */
		float menuTextMargin = 0.005f;
		float optionRightMargin = 0.015f;

		float menuWidth = 0.225f;
		float menuWidthOriginal = menuWidth;

		float optionHeight = 0.035f;
		float optionTextSize = 0.45f;
		float optionTextureOffset = optionHeight / 2.0f;

		float titleHeight = 0.1f;
		float titleTextSize = 1.15f;
		float titleTextOffset = 0.015f;
		float titleTextureOffset = titleHeight / 2.0f;

		float subtitleHeight = optionHeight;
		float subtitleTextureOffset = subtitleHeight / 2.0f;
		float subtitleTextSize = 0.45f;

		float detailLineHeight = 0.025f;

		/*
		 * Max items to display. Can be higher or lower, but 10 is a nice
		 * number so the radar doesn't get covered while the description is
		 * readable.
		 */
		int maxDisplay = 10;

		/*
		 * Members for menu state.
		 */
		float totalHeight = 0.0f;
		int optioncount = 0;
		int currentoption = 0;
		bool optionpress = false;
		bool leftpress = false;
		bool rightpress = false;
		bool uppress = false;
		bool downpress = false;
		std::array<std::string, maxMenus> currentmenu;
		std::string actualmenu;
		//std::array<int, 100> lastoption;
		std::unordered_map<std::string, int> lastoption; // lastoption is now per unique submenu
		int menulevel = 0;
		float headerHeight = 0.0f;

		FooterType footerType = FooterType::Sprite;
		Color footerColor = { 255,255,255,255};
		Sprite footerSprite;
		float aspectR = 16.0f / 9.0f;

		/*
		 * Navigation-related members.
		 */
		unsigned int delay = GetTickCount();
		std::vector<int> menuTimeDelays = {
			240,
			120,
			75,
			40,
			20,
			10,
		};

		const unsigned int menuTimeRepeat = menuTimeDelays[0];

		unsigned int menuTime = menuTimeRepeat;
		bool useNative = true;



		int backgTextureIndex = 3;
		int highlTextureIndex = 4;

		const std::map<int, int, std::greater<int>> recordGlobals{
			{ 0, 0 },
			{ 10, 0x42CA + 0x09 },
			{ 14, 0x42DE + 0x09 },
			{ 26, 0x42FF + 0x09 },
			{ 28, 0x42FF + 0x82 },
			{ 38, 0x430A + 0X82 }
		};

		/*
		 * Functions! Should be self-explanatory.
		 */
		float getStringWidth(std::string text, float scale, int font);
		std::vector<std::string> splitString(float maxWidth, std::string &details, float scale, int font);
		void drawText(const std::string text, int font, float x, float y, float pUnknown, float scale, Color color, int justify);
		void drawRect(float x, float y, float width, float height, Color color);
		void drawSprite(std::string textureDict, std::string textureName, float x, float y, float width, float height, float rotation, Color color);
		void DrawGlare(float posX, float posY, float sizeX, float sizeY, Color color);
		void drawOptionPlusTitle(std::string title);
		void drawOptionPlusImage(std::string &extra, float &finalHeight);
		void drawOptionPlusSprite(std::string &extra, float &finalHeight);
		void drawOptionPlusText(std::string &extra, float &finalHeight);
		void drawOptionPlusExtras(std::vector<std::string> &extra, std::string title = "Info");
		void drawMenuDetails(std::vector<std::string> details, float y);
		void drawOptionValue(std::string printVar, bool highlighted, int max = 0);

		void changeMenu(std::string menuname);
		void nextOption();
		void previousOption();
		void backMenu();
		void menuBeep();
		void resetButtonStates();
		void disableKeysOnce();
		void enableKeysOnce();
		void hideHUDComponents();
		void disableKeys();
		void processMenuNav(std::function<void()> onMain, std::function<void()> onExit);
		void updateScreenSize();
		void fitTitle(std::string &title, float &newSize, float titleSize);

		template <typename T>
		bool processOptionItemControls(T &var, T min, T max, T step,bool isprivate=false) {
			if (!isprivate&&currentoption == optioncount) {
				if (optionpress)
					var = (T)FloatKeyboard();
				if (leftpress) {
					if (var <= min) var = max;
					else var -= step;
					leftpress = false;
					return true;
				}
				if (var < min) var = max;
				if (rightpress) {
					if (var >= max) var = min;
					else var += step;
					rightpress = false;
					return true;
				}
				if (var > max) var = min;
			}

			if (optionpress && currentoption == optioncount)
				return true;
			return false;
		}

		// https://stackoverflow.com/questions/2333728/stdmap-default-value
		template <template<class, class, class...> class C, typename K, typename V, typename... Args>
		V getWithDef(const C<K, V, Args...>& m, K const& key, const V & defval) {
			typename C<K, V, Args...>::const_iterator it = m.find(key);
			if (it == m.end())
				return defval;
			return it->second;
		}
	};

}
