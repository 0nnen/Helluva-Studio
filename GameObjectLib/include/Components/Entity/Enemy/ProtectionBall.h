#pragma once

#include "Components/Entity.h"

class ProtectionBall : public Entity
{
public:

	ProtectionBall();
	ProtectionBall(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range);

	void SetHades(GameObject* _hades) { hades = _hades; }
	void Die() override;
	void Update(const float& _delta);
	void SetSpawn(int _spawn) { spawn = _spawn; }
	int GetSpawn() { return spawn; }
	void SetHealth();
	void SetPower(const float& _delta);


private:
	GameObject* hades = nullptr;
	GameObject* player = nullptr;
	int spawn = 0;
	float randX;
	float randY;
	bool ballDamage;
	float tp;
};