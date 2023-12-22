#include "Components/ComponentsGame/Weapon.h"
#include "Managers/SceneManager.h"
#include "Components/Entity/Character.h"

void Weapon::Update(const float& _delta)
{
	Component::Update(_delta);
}

void Weapon::Attack() {}