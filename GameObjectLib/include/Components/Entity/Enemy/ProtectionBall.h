#pragma once

#include "Components/Entity.h"

class ProtectionBall : public Entity
{
public:

	ProtectionBall();
	ProtectionBall(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range);

	void SetHades(GameObject* _hades) { hades = _hades; }
	void Die() override;
	//void DieFireCirlce() override;
	void Update(const float& _delta);


private:
	GameObject* hades = nullptr;
	GameObject* player = nullptr;
	int randX;
	int randY;
	bool alive;
	bool ballDamage;
};