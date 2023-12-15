#include "Components/Inputs/InputCharacter.h"
#include "Commands/CommandCharacter.h"
#include "Components/SpriteRenderer.h"
#include "Managers/SceneManager.h"
#include "Components/Entity/Character.h"
#include "Components/Animation.h"
#include "Scenes/ScenesGame/ScenesTest.h"

InputCharacter::InputCharacter() {
	this->KeyD_ = new MoveCharacterRight();
	this->KeyQ_ = new MoveCharacterLeft();
	this->KeyZ_ = new JumpCharacter();
	this->LeftMouse_ = new ShootCharacter();
	this->Num1_ = new ChangeWeaponCharacter(1);
	this->Num2_ = new ChangeWeaponCharacter(2);
	this->WheelMouse_ = new ChangeWeaponCharacter(0);
}

void InputCharacter::Update(const float& _delta) {
	Component::Update(_delta);

	Character* character = GetOwner()->GetComponent<Character>();

	Command* commandMoves = this->HandleInput();
	if (commandMoves)
	{
		if (!character->GetAnimation("run")->GetIsPlaying()) {
			if (character->GetActualAnimation()) character->GetActualAnimation()->Stop();
			if (character->GetAnimation("jump")) character->GetAnimation("jump")->Stop();
			if (character->GetAnimation("idle")) character->GetAnimation("idle")->Stop();
			character->GetAndSetAnimation("run")->Play();
		}
		commandMoves->Execute(_delta);
	}
	else
	{
		if (character->GetAnimation("run")->GetIsPlaying()) {
			character->GetAnimation("run")->Stop();
			if (character->GetAnimation("jump")) character->GetAnimation("jump")->Stop();
			if (!character->GetAnimation("idle")) character->GetAnimation("idle")->Play();
		}
	}

	Command* commandJump = this->JumpInput();

	if (commandJump && !GetOwner()->GetComponent<RigidBody2D>()->GetIsGravity())
	{
		if (!character->GetAnimation("jump")->GetIsPlaying()) {
			if (character->GetActualAnimation()) character->GetActualAnimation()->Stop();
			if (character->GetAndSetAnimation("idle")) character->GetAndSetAnimation("idle")->Stop();
			if (!character->GetAnimation("shootArm")->GetIsPlaying() && !character->GetAnimation("shootBody")->GetIsPlaying())
				character->GetAndSetAnimation("jump")->Play();
		}
		commandJump->Execute(_delta);
	}

	Command* shootBullet = this->ShootInput();

	if (shootBullet)
	{
		shootBullet->Execute(_delta);
	}

	Command* changeWeapon = this->ChangeWeaponInput();

	if (changeWeapon)
	{
		changeWeapon->Execute(_delta);
	}

	if (!commandJump && !commandMoves && !shootBullet)
	{
		if (character->GetOnFloor() && character->GetAnimation("jump")->GetIsPlaying())
		{
			character->GetAnimation("jump")->Stop();
		}
		if (!character->GetOnFloor() && !character->GetAnimation("jump")->GetIsPlaying())
		{
			if (character->GetAnimation("idle")->GetIsPlaying()) {

				character->GetAndSetAnimation("idle")->Stop();
			}
			character->GetAnimation("jump")->Play();
		}
		if (!character->GetAnimation("jump")->GetIsPlaying())
			if (!character->GetAnimation("shootArm")->GetIsPlaying() && !character->GetAnimation("shootBody")->GetIsPlaying())
				if (!character->GetAnimation("run")->GetIsPlaying())

					if (!character->GetAnimation("idle")->GetIsPlaying()) {

						character->GetAndSetAnimation("idle")->Play();
					}
	}

	if (!commandMoves) {
		RigidBody2D* rigidBody = GetOwner()->GetComponent<RigidBody2D>();
		Maths::Vector2f velocity = rigidBody->GetVelocity();

		//Slide Effect
		if (velocity.GetX() != 0.f) {
			if (velocity.GetX() - 10.f > 0.f) {
				rigidBody->AddForces(Maths::Vector2f(-10.f, 0.f));
			}
			else if (velocity.GetX() + 10.f < 0.f) {
				rigidBody->AddForces(Maths::Vector2f(10.f, 0.f));
			}
			else {
				velocity.SetX(0.f);
				rigidBody->SetVelocity(velocity);
			}
		}
	}
}

Command* InputCharacter::HandleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) return KeyQ_;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) return KeyD_;
	return nullptr;
}

Command* InputCharacter::JumpInput() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return KeyZ_;

	return nullptr;
}

Command* InputCharacter::ShootInput() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return LeftMouse_;
	return nullptr;
}

Command* InputCharacter::ChangeWeaponInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) return Num1_;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) return Num2_;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) return WheelMouse_;
	return nullptr;
}

InputCharacter::~InputCharacter() {
	delete this->KeyD_;
	delete this->KeyQ_;
	delete this->KeyZ_;
	delete this->LeftMouse_;
	delete this->Num1_;
	delete this->Num2_;
	delete this->WheelMouse_;
}
