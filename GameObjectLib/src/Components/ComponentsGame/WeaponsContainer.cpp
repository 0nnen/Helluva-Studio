#include "Components/ComponentsGame/WeaponsContainer.h"
#include "Components/ComponentsGame/Weapon.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"

WeaponsContainer::WeaponsContainer()
{
}

void WeaponsContainer::AddNewWeapon(GameObject* _weapon)
{
	if (std::find(weapons.begin(), weapons.end(), _weapon) == weapons.end())
	{
		weapons.push_back(_weapon);
		weapon = _weapon;
		actualWeaponIndex = weapons.size() - 1;
	}
}

GameObject* WeaponsContainer::GetWeaponByIndex(const unsigned int& _index) const
{
	if (_index < weapons.size())
	{
		return weapons[_index];
	}
	return nullptr;
}

void WeaponsContainer::ChangeWeapon()
{
	if (actualWeaponIndex + 1 < weapons.size())
	{
		actualWeaponIndex++;
	}
	else
	{
		actualWeaponIndex = 0;
	}
	weapon = weapons[actualWeaponIndex];
}

GameObject* WeaponsContainer::GetWeaponByName(const std::string& _name) const
{
	for (GameObject* weapon : weapons)
	{
		if (weapon->GetName() == _name) return weapon;
	}
	return nullptr;
}

void WeaponsContainer::ChangeWeaponByIndex(const size_t& _index)
{
	if (_index < weapons.size())
	{
		weapon = weapons[_index];
	}
}
void WeaponsContainer::ChangeWeaponByName(const std::string& _name)
{
	for (GameObject* _weapon : weapons)
	{
		if (weapon->GetName() == _name) weapon = _weapon;
	}
}