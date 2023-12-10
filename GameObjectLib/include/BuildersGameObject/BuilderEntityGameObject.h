#pragma once
#include "GameObject.h"
#include "Components/ComponentsGame/Weapon.h"
class BuilderEntityGameObject
{
public:
	static GameObject* CreateBulletGameObject(const std::string& _name, sf::Texture* _textureBullet, const float& _scalex, const float& _scaley, GameObject* _player);
	static GameObject* CreateWeaponGameObject(const std::string& _name, GameObject* _player, const Weapon::TypeWeapon& _typeWeapon, const float& _damage, const float& _range, const float& _attackSpeed);
	static GameObject* CreateCharacterGameObject(const std::string& _name, const float& _x, const float& _y, sf::Texture* texture, const float& scalex, const float& scaley);
	static GameObject* CreatePlateformGameObject(const std::string& _name, const float& _positionX, const float& _positionY, const float& scalex, const float& scaley);
};

