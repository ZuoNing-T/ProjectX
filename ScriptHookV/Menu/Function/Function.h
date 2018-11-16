#pragma once
#include <vector>
//http://stackoverflow.com/questions/36789380/how-to-store-a-const-char-to-a-char
class CharAdapter
{
public:
	explicit CharAdapter(const char* s) : m_s(::_strdup(s)) { }
	CharAdapter(const CharAdapter& other) = delete; // non construction-copyable
	CharAdapter& operator=(const CharAdapter&) = delete; // non copyable

	~CharAdapter() /*free memory on destruction*/
	{
		::free(m_s); /*use free to release strdup memory*/
	}
	operator char*() /*implicit cast to char* */
	{
		return m_s;
	}

private:
	char* m_s;
};
std::string show_keyboard();
void showNotification(const char* message, char * picname = "CHAR_SOCIAL_CLUB", int *prevNotification = nullptr);

Hash $(std::string str);
void changemodel(std::string newmodel);//Change Player Model


float degToRad(float degs);

Vector3 GET_AIM_COORDS();
void GET_CAMERA_DIRECTION(float *dirX, float *dirY, float *dirZ);


void teleport_to_marker();

Vector3 RotationToDirection(Vector3 rot);
Vector3 rot_to_direction(Vector3* rot);
float get_distance(Vector3*pointA, Vector3*pointB);
void RequestControl(Entity input);
void RequestControlOfEnt(Entity entity);
float FloatKeyboard();

void find(char* lpPath, std::vector<std::string> &fileList);
void DrawBigMsg(std::string functionname, std::string msg, std::string msg2 = "");
bool EndsWith(const std::string &str, const std::string &suffix);
bool String2Bool(std::string text);