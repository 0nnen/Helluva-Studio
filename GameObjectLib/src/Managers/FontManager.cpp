#include "Managers/FontManager.h"

std::map<std::string, sf::Font*> FontManager::fonts;

void FontManager::AddFont(const std::string& _key, const std::string& _fileName)
{
	sf::Font* font = new sf::Font();
	if (FontManager::fonts.find(_key) == FontManager::fonts.end()) 
	{
		FontManager::fonts.insert(std::make_pair(_key, font));
		if (!FontManager::fonts.at(_key)->loadFromFile(_fileName)) 
		{
			std::cout << "font introuvable" << std::endl;
		}
	}
}

sf::Font* FontManager::GetFont(const std::string& _key)
{
	if (FontManager::fonts.find(_key) != FontManager::fonts.end()) 
	{
		return FontManager::fonts.at(_key);
	}
	return nullptr;
}