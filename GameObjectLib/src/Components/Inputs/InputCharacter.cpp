#include "Components/Inputs/InputCharacter.h"

#include "Components/Inputs/InputCharacter.h"
#include "Commands/CommandsGame.h"
//#include "Components/Armes.h"
#include "Components/SpriteRenderer.h"
#include "Managers/SceneManager.h"
#include "Components/Entity/Character.h"

InputCharacter::InputCharacter() {
	this->player = nullptr;
	this->KeyD_ = new RightCommand();
	this->KeyQ_ = new LeftCommand();
	//this->KeySpace_ = new RightBulletCommand(this);
	this->KeyEscape_ = new PauseCommand();
	this->KeyZ_ = new UpCommand();
}

void InputCharacter::Update(const float& _delta) {
	Component::Update(_delta);

	Command* commandMoves = this->HandleInput();
	if (commandMoves) {
		commandMoves->Execute(_delta);
	}
	Command* commandJump = this->JumpInput();
	if (commandJump) {
		commandJump->Execute(_delta);
	}
	/*Command* fireBullet = this->FireInput();
	if (fireBullet) {
		fireBullet->Execute(_delta);
	}*/

}

Command* InputCharacter::HandleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return KeyQ_;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return KeyD_;

	return nullptr;

}

Command* InputCharacter::JumpInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return KeyZ_;
	return nullptr;
}

Command* InputCharacter::FireInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return KeySpace_;
	return nullptr;
}

Command* InputCharacter::PauseInput() {
	static bool isPressedEscape = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !isPressedEscape) {
		isPressedEscape = true;
		return KeyEscape_;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		isPressedEscape = false;
	}

	return nullptr;
}

void InputCharacter::MoveRight(sf::Time _delta)
{
	GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Right + Maths::Vector2f(25, 0) * _delta.asSeconds() * speed);
	GetOwner()->GetComponent<Character>()->setDirection(Character::Direction::Right);
	//GetOwner()->GetComponent<Sprite>()->PlayerPlayAnimationRun();
}

void InputCharacter::MoveLeft(sf::Time _delta)
{
	GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Left + Maths::Vector2f(-25, 0) * _delta.asSeconds() * speed);
	GetOwner()->GetComponent<Character>()->setDirection(Character::Direction::Left);
	//GetOwner()->GetComponent<Sprite>()->PlayerPlayAnimationRun();
}

float InputCharacter::AddSpeed(float _addSpeed) {
	speed = +_addSpeed;
	return speed;
}

void InputCharacter::Jump(sf::Time _delta)
{
	GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Down + Maths::Vector2f(0, -130) * _delta.asSeconds() * speed);
}

//void InputPlayer::MoveRightBullet()
//{
//	player = SceneManager::GetActiveScene()->GetGameObject("Player");
//	player->GetComponent<Armes>()->Shoot();
//}

void InputCharacter::GamePauseMenu()
{
}

InputCharacter::~InputCharacter() {
	delete 	this->KeyD_;
	delete 	this->KeyQ_;
	delete 	this->KeySpace_;
	delete 	this->KeyEscape_;
	delete 	this->KeyZ_;
}
