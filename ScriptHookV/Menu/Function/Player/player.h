#pragma once

namespace PlayerOption
{
	void fixplayer();

	extern bool betiny;
	void TinyPlayer(bool toggle);

	void SetPedMovementClipset(char* clipset);

	extern bool GodModeBool;
	void GodMode();

	extern bool visiblebool;

	extern bool supermanbool;
	void superman();

	extern 	bool freecambool;
	void freecam();

	extern bool ragdollbool;
	void ragdoll();

	extern 	bool mobileRadio;
	void toggleMobileRadio();

	void randomoutfit();

	void cleanplayer();

	void killself();

	extern bool superjumpbool;
	void superjump();

	extern bool explodeMeleebool;
	void explodeMelee();

	void setwantedlevel(int wantedlevel);
}
