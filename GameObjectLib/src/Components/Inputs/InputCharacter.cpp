#include "Components/Inputs/InputCharacter.h"

#include "Components/Inputs/InputCharacter.h"
#include "Commands/CommandCharacter.h"
//#include "Components/Armes.h"
#include "Components/SpriteRenderer.h"
#include "Managers/SceneManager.h"
#include "Components/Entity/Character.h"
#include "Components/Animation.h"
#include "Scenes/ScenesGame/ScenesTest.h"

InputCharacter::InputCharacter() {
	//this->player = nullptr;Th
	this->KeyD_ = new MoveCharacterRight();
	this->KeyQ_ = new MoveCharacterLeft();
	//this->KeySpace_ = new RightBulletCommand(this);
	//this->KeyEscape_ = new PauseCommand();
	this->KeyZ_ = new JumpCharacter();
	this->LeftMouse_ = new ShootCharacter();
}

void InputCharacter::Update(const float& _delta) {
	Component::Update(_delta);

	Character* character = GetOwner()->GetComponent<Character>();

	Command* commandMoves = this->HandleInput();
	if (commandMoves)
	{
		if (!character->GetAnimation("run")->GetIsPlaying()) {
			if (character->GetActualAnimation()) character->GetActualAnimation()->Stop();
			if (character->GetAndSetAnimation("idle")) character->GetAndSetAnimation("idle")->Stop();
			character->GetAndSetAnimation("run")->Play();
		}
		commandMoves->Execute(_delta);
	}
	else
	{
		if (character->GetAnimation("run")->GetIsPlaying()) {
			character->GetAnimation("run")->Stop();
		}
	}

	Command* commandJump = this->JumpInput();

	if (commandJump && !GetOwner()->GetComponent<RigidBody2D>()->GetIsGravity())
	{
		if (!character->GetAnimation("jump")->GetIsPlaying()) {
			if (character->GetActualAnimation()) character->GetActualAnimation()->Stop();
			if (character->GetAndSetAnimation("idle")) character->GetAndSetAnimation("idle")->Stop();
			if(!character->GetAnimation("shootArm")->GetIsPlaying() && !character->GetAnimation("shootBody")->GetIsPlaying())
			character->GetAndSetAnimation("jump")->Play();
		}
		commandJump->Execute(_delta);
	}

	Command* shootBullet = this->ShootInput();

	if (shootBullet)
	{
		shootBullet->Execute(_delta);
	}

	if (!commandJump && !commandMoves && !shootBullet)
	{
		if (!character->GetAnimation("jump")->GetIsPlaying())
			if (!character->GetAnimation("shootArm")->GetIsPlaying() && !character->GetAnimation("shootBody")->GetIsPlaying())
				if (!character->GetAnimation("run")->GetIsPlaying())
					if (!character->GetAnimation("idle")->GetIsPlaying()) {
						if (character->GetOnFloor())
						{
							character->GetAnimation("jump")->Stop();
						}
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

//Command* InputCharacter::PauseInput() {
//	static bool isPressedEscape = false;
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !isPressedEscape) {
//		isPressedEscape = true;
//		return KeyEscape_;
//	}
//
//	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
//		isPressedEscape = false;
//	}
//
//	return nullptr;
//}

//void InputCharacter::MoveRight(sf::Time _delta)
//{
//	GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Right + Maths::Vector2f(25, 0) * _delta.asSeconds() * speed);
//	GetOwner()->GetComponent<Character>()->setDirection(Character::Direction::Right);
//	GetOwner()->GetComponent<Sprite>()->PlayerPlayAnimationRun();
//}

//void InputCharacter::MoveLeft(sf::Time _delta)
//{
//	GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Left + Maths::Vector2f(-25, 0) * _delta.asSeconds() * speed);
//	GetOwner()->GetComponent<Character>()->setDirection(Character::Direction::Left);
//	GetOwner()->GetComponent<Sprite>()->PlayerPlayAnimationRun();
//}

//float InputCharacter::AddSpeed(float _addSpeed) {
//	speed = +_addSpeed;
//	return speed;
//}

//void InputCharacter::Jump(sf::Time _delta)
//{
//	GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Down + Maths::Vector2f(0, -130) * _delta.asSeconds() * speed);
//}

//void InputPlayer::MoveRightBullet()
//{
//	player = SceneManager::GetActiveScene()->GetGameObject("Player");
//	player->GetComponent<Armes>()->Shoot();
//}

//void InputCharacter::GamePauseMenu()
//{
//}

InputCharacter::~InputCharacter() {
	delete 	this->KeyD_;
	delete 	this->KeyQ_;
	//delete 	this->KeySpace_;
	/*delete 	this->KeyEscape_;
	delete 	this->KeyZ_;*/
}
