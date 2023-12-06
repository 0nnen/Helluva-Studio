#pragma once
#include "GameObject.h"
#include "Components/Inputs/InputCharacter.h"

class BuilderGameObject
{
public:
	static GameObject* CreateButtonGameObject(const std::string& _name, const float& _x, const float& _y, const unsigned int& _fontSize);

	static GameObject* CreateBackgroundGameObject(const std::string& _name, const float& _x, const float& _y, const sf::Texture& _texture);
	static GameObject* CreateInputGameObject(const std::string& _name, const float& _x, const float& _y);

	static GameObject* CreateSliderGameObject(const std::string& _name, const float& _x, const float& _y, const float& _widthBar, const float& _heightBar, const float& _widthCursor, const float& _heightCursor, const unsigned int& _fontSize, const float& _data, const float& _maxData);
	static GameObject* CreateSliderGameObject(const std::string& _name, const float& _x, const float& _y, const float& _widthBar, const float& _heightBar, const float& _widthCursor, const float& _heightCursor, const unsigned int& _fontSize, const float& _data, const float& _minData, const float& _maxData);
	static GameObject* CreateCharacterGameObject(const std::string& name, float positionx, float positiony, const sf::Texture texture, float scalex, float scaley);
};

