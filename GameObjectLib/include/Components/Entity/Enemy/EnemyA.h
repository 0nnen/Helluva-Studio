#pragma once
#include "Components/Entity.h"

class EnemyA : public Entity
{
public:
	EnemyA();
	void Update(const float& _delta);
	static void Attack(float _x, float _y);
	static GameObject* GetBulletEnemy() { return bulletEnemy; }
	static bool GetBulletShoot() { return bulletShoot; }


private:
	static float cooldown;
	static float fireRate;
	static bool bulletShoot;
	static GameObject* bulletEnemy;
	static float speed;

};

