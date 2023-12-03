#pragma once
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

class FontManager
{
public:
	//Add a new font to the assets list
	static void AddFont(const std::string& _key, const std::string& _fileName);

	//Get an font by its key
	static sf::Font* GetFont(const std::string& _key);

private:
	static std::map<std::string, sf::Font*> fonts;
};



