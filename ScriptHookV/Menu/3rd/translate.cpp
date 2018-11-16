
#include "../../../SDK/inc/enums.h"
#include "../../ScriptHookV.h"
#include "../3rd/simpleini/SimpleIni.h"


//
//LanguageType lan;
//std::string LanguagePath = "";
//std::string Path = "";
//void getLanguagePath(std::string Path)
//{
//	lan = american;
//	LanguagePath = Path;
//}
//static CSimpleIniA Language;
//
//void SetLanguage(LanguageType language)
//{
//	lan = language;
//	CreateDirectory((LanguagePath).c_str(), NULL);
//	switch (lan)
//	{
//	case french:
//		Path = LanguagePath + "\\french.ini";
//		break;
//	case chinese:
//		Path = LanguagePath + "\\chinese.ini";
//		break;
//	case chinese_simp:
//		Path = LanguagePath + "\\chinese_simp.ini";
//		break;
//	case german:
//		Path = LanguagePath + "\\german.ini";
//		break;
//	case italian:
//		Path = LanguagePath + "\\italian.ini";
//		break;
//	case spanish:
//		Path = LanguagePath + "\\spanish.ini";
//		break;
//	case portuguese:
//		Path = LanguagePath + "\\portuguese.ini";
//		break;
//	case russian:
//		Path = LanguagePath + "\\russian.ini";
//		break;
//	case korean:
//		Path = LanguagePath + "\\korean.ini";
//		break;
//	case japanese:
//		Path = LanguagePath + "\\japanese.ini";
//		break;
//	case mexican:
//		Path = LanguagePath + "\\mexican.ini";
//		break;
//	case american:
//	default:
//		return;
//		break;
//	}
//	if (fileExists(Path.c_str()))
//	{
//		Language.LoadFile(Path.c_str());
//		Language.SetUnicode();
//	}
//	else
//	{
//		std::ofstream fout(Path.c_str());
//		if (fout)
//		{
//			Language.LoadFile(Path.c_str());
//			Language.SetUnicode();
//		}
//		else
//		{
//			showNotification("could not create file");
//			LOG_PRINT("could not create file at %s", Path);
//		}
//	}
//	//	LOG_PRINT("Language Set to %d", lan);
//}
//
//std::string getTranslateion(std::string Origin)
//{
//	/*	american = 0,
//	french = 1,
//	german = 2,
//	italian = 3,
//	spanish = 4,
//	portuguese = 5,
//	polish = 6,
//	russian = 7,
//	korean = 8,
//	chinese = 9,
//	japanese = 10,
//	mexican = 11
//	*/
//	std::string DestLanguage = Language.GetValue("Language", (char*)Origin.c_str(), (char*)Origin.c_str());
//	if ((DestLanguage == Origin) && lan != american)
//	{
//		Language.SetValue("LANGUAGE", (char*)Origin.c_str(), "");
//		Language.SaveFile(Path.c_str());
//	}
//	if (DestLanguage == "")
//	{
//		return Origin;
//	}
//	return DestLanguage;
//}
//std::vector<std::string> getDetailTransla(std::vector<std::string> Origin)
//{
//	std::vector<std::string> Result;
//	for (auto toTrans : Origin)
//	{
//		std::string DestLanguage = Language.GetValue("HELP", (char*)toTrans.c_str(), (char*)toTrans.c_str());//To get Translate from the files
//		if ((DestLanguage == toTrans) && lan != american)//if translation doesn't exist, make it 
//		{
//			Language.SetValue("HELP", (char*)toTrans.c_str(), "");
//			Language.SaveFile(Path.c_str());
//		}
//		if (DestLanguage == "")//if files exist and haven't translate
//		{
//			DestLanguage = toTrans;
//		}
//		Result.push_back(DestLanguage);
//	}
//	return Result;
//
//}






//uint64_t g_fwTxdStore;
//uint32_t g_txdCollectionItemSize;
//void some_init_func()
//{
//	uint64_t patternAddr = Pattern::Scan("48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 45 EC");
//	g_fwTxdStore = patternAddr + *(int*)(patternAddr + 3) + 7;
//	patternAddr = Pattern::Scan("48 03 0D ?? ?? ?? ?? 48 85 D1 75 04 44 89 4D F0");
//	g_txdCollectionItemSize = *(uint32_t*)((patternAddr + *(int*)(patternAddr + 3) + 7) + 0x14);
//}
//std::vector<std::string> get_textures_from_txd(Hash txdHash)
//{
//	std::vector<std::string> vecTextures;
//	if (g_fwTxdStore && g_fwTxdStore != 7)
//	{
//		uint64_t txds = *(uint64_t*)(g_fwTxdStore + 0x70);
//		if (txds)
//		{
//			uint16_t size = *(uint16_t*)(g_fwTxdStore + 0x82);
//			for (uint16_t i = txdHash % (size - 1); i < size - 1; i++)
//			{
//				Hash hash = *(Hash*)(txds + i * 8);
//				if (hash != txdHash) continue;
//				uint16_t index = *(uint16_t*)(txds + i * 8 + 4);
//				if (index == -1) break;
//				uint64_t pgDictionaryCollection = *(uint64_t*)(g_fwTxdStore + 0x38);
//				if (pgDictionaryCollection)
//				{
//					rage::pgDictionary* dictionary = *(rage::pgDictionary**)(pgDictionaryCollection + index * g_txdCollectionItemSize);
//					if (dictionary)
//					{
//						rage::grcTexture** textures = dictionary->textures;
//						if (textures)
//						{
//							uint16_t count = dictionary->textureCount;
//							for (uint16_t j = 0; j < count; j++)
//							{
//								if (textures[j] == nullptr) continue;
//								vecTextures.push_back(textures[j]->name);
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	return vecTextures;
//}