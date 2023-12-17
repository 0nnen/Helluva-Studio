#pragma once

#include "Components/Entity.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/AssetManager.h"

class Hades final : public Entity
{
public:
	enum Step {Step1, Step2, Step3};
	enum State { Idle, Attack, Move, Roar };
	Hades();
	Hades(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range);
	
	void SetProtection(const float& _delta);
	void SetDirection();

	void AttackFeu();
	void AttackCheval(int _randomAttackCheval, const float& _delta);
	void AllerRetourCheval(bool _nightmareArrive, const float& _delta, int& _countAllerRetour, int& _countAllerRetour2, int& _countAllerRetour3);

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
	std::vector<GameObject*> balls;
	float timeSpawnBalls = 10.f;
	float actualTime = 10.f;
	float cooldown = 10.0f;
	int randomAttackCheval = 0;
	int newRandomAttackCheval;
	int randomAttackFeu = 0;
	bool stateSwitch;
	int countAllerRetour = 0;
	int countAllerRetour2 = 0;
	int countAllerRetour3 = 0;
	bool nightmareArrive;
	const float speed = 350.0f;
	//GameObject* platformFeu;
};

