#pragma once
#include "Components/Entity.h"

class EnemyA : public Entity
{
public:
	EnemyA();
	void Update(const float& _delta);
	void Attack(const float& _delta) override;
	void CreateBullet(float _x, float _y);


private:
	float cooldown;
	float fireRate;
	bool bulletShoot;
	GameObject* bulletEnemy;
	GameObject* player;
	float speed;
	bool flip;

};

