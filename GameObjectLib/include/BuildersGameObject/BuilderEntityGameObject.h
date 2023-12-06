#pragma once
#include "GameObject.h"
class BuilderEntityGameObject
{
public:
	static GameObject* CreateBulletGameObject(const std::string& _name, const sf::Texture& _textureBullet, const float& _scalex, const float& _scaley, GameObject* _player);
	static GameObject* CreateCharacterGameObject(const std::string& _name, float _x, float _y, const sf::Texture texture, float scalex, float scaley);
};

