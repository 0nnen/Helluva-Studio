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
	
	void SetProtection() {
		isInvicible = true;
		int randomNumber;
		Maths::Vector2f positionHades = GetOwner()->GetPosition();
		switch (step)
		{
		case Hades::Step3:
			std::cout << "Step3" << std::endl;
			randomNumber = rand() % 8;
			balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection4", 500, 500, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber));
		case Hades::Step2:
			std::cout << "Step2" << std::endl;
			randomNumber = rand() % 8;
			balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection3", 1500, 800, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber));
		case Hades::Step1:
			std::cout << "Step1" << std::endl;
			randomNumber = rand() % 8;
			std::cout << "Random 2: " << randomNumber << std::endl;
			balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection2", 1250, 400, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber));
			randomNumber = rand() % 8;
			std::cout << "Random 1: " << randomNumber << std::endl;
			balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection1", 1000, 200, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber));
			break;
		default:
			break;
		}
	}

	void Update(const float& _delta) override;

private:
	State state = Idle;
	Step step = Step1;
	GameObject* protection = nullptr;
	std::vector<GameObject*> balls;
};

