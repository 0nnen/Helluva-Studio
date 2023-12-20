#pragma once

#include <string>
#include <vector>
#include <iostream>
class LanguageManager
{
public:

	static LanguageManager* GetInstance();
	void RecoverLanguages(const std::string& _fileName);

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
};

