#pragma once

#include "Command.h"
#include "Component.h"
#include "Managers/SceneManager.h"
#include "Components/RigidBody2D.h"

class InputCharacter : public Component
{
public:
	InputCharacter();

	void Update(const float& _delta) override;
	Command* HandleInput();
	Command* JumpInput();
	Command* ShootInput();

	//Command* PauseInput();
	//void MoveRight(sf::Time _delta);
	//void MoveRightBullet();
	//void GamePauseMenu();
	//void MoveLeft(sf::Time _delta);
	//void Jump(sf::Time _delta);
	//float GetSpeed() { return speed; }
	//float AddSpeed(float _speed);
	~InputCharacter();

private:
	Command* KeyZ_;

	Command* KeyD_;
	Command* KeyQ_;
	//Command* KeySpace_;
	//GameObject* player;
	//Command* KeyEscape_;
	Command* LeftMouse_;
};