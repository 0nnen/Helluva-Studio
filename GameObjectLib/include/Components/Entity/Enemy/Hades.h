#pragma once

#include "Components/Entity.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/AssetManager.h"

#include <SFML/Graphics.hpp>

#include "Components/Entity/Enemy/ProtectionBall.h"


class Hades final : public Entity
{
public:
	enum Step { Step1, Step2, Step3 };
	enum State { Idle, Attack, Move, Roar };
	Hades();
	Hades(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range);

	void SetProtection(const float& _delta);
	void SetDirection();


	void AttackFire(const float& _delta);
	void AttackHorse(int _randomAttackCheval, const float& _delta);
	void ManageHorseAllerRetour(const float& _delta);
	void ManageAttack(const float& _delta);
	void AllerRetourHorse(bool _nightmareArrive, const float& _delta);
	void DamageZoneHades(const float& _delta);

	void Update(const float& _delta) override;

	void RemoveBall(GameObject* _objectToRemove) {
		balls.erase(std::remove_if(balls.begin(), balls.end(),
			[_objectToRemove](GameObject* obj)
			{
				return obj == _objectToRemove;
			}), balls.end());
	}

	std::vector<GameObject*> GetProtectionBalls() { return balls; }

private:
	State state = Idle;
	Step step = Step1;
	GameObject* protection = nullptr;
	GameObject* nightmare = nullptr;
	GameObject* attackFire;
	GameObject* damageZone;
	GameObject* player = nullptr;;
	std::vector<GameObject*> balls;
	float timeSpawnBalls = 10.f;
	float actualTime = 10.f;

	float cooldown = 10.0f;
	float randX;
	float randY;
	float cooldownAttackFeu = 1.0f;
	float cooldownDamageZone = 2.0f;
	float cooldownAttackHorse = 0.15f;
	float cooldoawnRoar = 3.0f;
	float cooldoawnAttack = 5.0f;
	const float speed = 350.0f;
	int randomAttackCheval = 0;
	int newRandomAttackCheval;
	int randomAttackFeu = 0;
	int countAllerRetour = 0;
	int countAllerRetour2 = 0;
	int countAllerRetour3 = 0;
	int randomNumber;
	bool nightmareArrive;
	bool hitHorse;

};
