#pragma once

#include "Command.h"
#include "Component.h"


class InputCharacter : public Component
{
public:
	InputCharacter();

	void Update(const float& _delta) override;
	Command* HandleInput();
	Command* JumpInput();
	Command* FireInput();
	Command* PauseInput();
	void MoveRight(sf::Time _delta);
	//void MoveRightBullet();
	void GamePauseMenu();
	void MoveLeft(sf::Time _delta);
	void Jump(sf::Time _delta);
	float GetSpeed() { return speed; }
	float AddSpeed(float _speed);
	~InputCharacter();

private:
	float speed = 15.f;
	float JumpVelocity = 0.f;


	Command* KeyZ_;

	Command* KeyD_;
	Command* KeyQ_;
	Command* KeySpace_;
	GameObject* player;
	Command* KeyEscape_;
};

