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
	Command* ChangeWeaponInput();
	~InputCharacter();

private:
	float timeSinceLastFootstep = 0.0f;
	int currentFootstepSound = 1;

	Command* KeyZ_;

	Command* KeyD_;
	Command* KeyQ_;
	Command* LeftMouse_;
	Command* Num1_;
	Command* Num2_;
	Command* WheelMouse_;
};