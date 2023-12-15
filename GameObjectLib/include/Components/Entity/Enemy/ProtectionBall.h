#pragma once

#include "Components/Entity.h"

class ProtectionBall : public Entity
{
public:

	ProtectionBall();
	ProtectionBall(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range);
	
	void SetHades(GameObject* _hades) { hades = _hades; }
	void Die() override;
		
private:
	GameObject* hades = nullptr;
};

