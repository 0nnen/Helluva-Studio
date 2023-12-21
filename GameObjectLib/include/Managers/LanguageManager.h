#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

class LanguageManager
{
public:

	static LanguageManager* GetInstance();
	void RecoverLanguages(const std::string& _fileName);

	void GetButton()
	{
		// Lire le fichier JSON de la TileMap
		std::ifstream file("Assets/Texts/"+language+"/buttons.json");
		if (!file.is_open()) {
			std::cerr << "Impossible d'ouvrir le fichier JSON." << std::endl;
		}

		json buttonJson;
		file >> buttonJson;
		// Parcourir le JSON et stocker les données dans la map
		for (auto it = buttonJson.begin(); it != buttonJson.end(); ++it) {
			buttons[it.key()] = it.value();
		}
		
		file.close();
	}

	std::string GetButtonsByKey(const std::string& _key)
	{
		if (buttons.find(_key) != buttons.end())
		{
			return buttons.at(_key);
		}
		return "";
	}

	inline std::string GetLanguage() const { 
		std::cout << language << std::endl;
		return language;
	}
	inline void SetLanguage(const std::string& _language)
	{
		std::cout << "Langue entrée : " << _language << std::endl;
		for (const std::string& language_ : languages)
		{
			std::cout << "Langue comparée : " << language_ << std::endl;
			if (_language == language_) language = _language;
		}
	}

private:
	static LanguageManager* instance;
	std::string language;
	std::vector<std::string> languages;
	std::map<std::string, std::string> buttons;
};

