#pragma once

#include "Components/Entity.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/AssetManager.h"
#include "Components/Entity/Enemy/ProtectionBall.h"

class Hades final : public Entity
{
public:
	enum Step {Step1, Step2, Step3};
	enum State { Idle, Attack, Move, Roar };
	Hades();
	Hades(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range);
	
	void SetProtection();
	void SetDirection();
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
	std::vector<GameObject*> balls;
	float timeSpawnBalls = 10.f;
	float actualTime = 10.f;
	int randomNumber;
	float randX;
	float randY;
};

