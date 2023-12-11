#pragma once
#include "GameObject.h"
class BuilderEntityGameObject
{
public:
	static GameObject* CreateBulletGameObject(const std::string& _name, sf::Texture* _textureBullet, const float& _scalex, const float& _scaley, GameObject* _player);
	static GameObject* CreateCharacterGameObject(const std::string& _name, const float& _x, const float& _y, sf::Texture* texture, const float& scalex, const float& scaley);
	static GameObject* CreatePlatformCollisionGameObject(const std::string& _name, const float& _positionX, const float& _positionY, const float& scalex, const float& scaley);
	static GameObject* CreatePlatformTriangleCollisionGameObject(const std::string& _name, const float& _base, const float& _height, const float& _widthPos, const float& _heightPos, const float& _rotation);
};

