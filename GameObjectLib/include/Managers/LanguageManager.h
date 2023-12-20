#pragma once

#include <string>
#include <vector>
class LanguageManager
{
public:

	static LanguageManager* GetInstance();
	void RecoverLanguages(const std::string& _fileName);

	inline std::string GetLanguage() const { return language; }
	inline void SetLanguage(const std::string& _language)
	{
		for (const std::string& language_ : languages)
		{
			if (_language == language_) language = _language;
		}
	}

private:
	static LanguageManager* instance;
	std::string language;
	std::vector<std::string> languages;
};

