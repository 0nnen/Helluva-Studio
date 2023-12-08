#include "Commands/CommandCharacter.h"
#include "BuilderGameObject.h"
#include "Components/Entity/Character.h"
#include "Components/Animation.h"
#include "Managers/SceneManager.h"
#include "Managers/CameraManager.h"


void MouveCharacterRight::Execute(const float& _delta) 
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	player->SetPosition(player->GetPosition() + Maths::Vector2f::Right + Maths::Vector2f(25, 0) * _delta * character->GetSpeed());
	character->SetDirection(Character::Direction::Right);
}
MouveCharacterRight::MouveCharacterRight() {}

void MouveCharacterLeft::Execute(const float& _delta)
{

	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	player->SetPosition(player->GetPosition() + Maths::Vector2f::Left + Maths::Vector2f(25, 0) * _delta * character->GetSpeed());
	character->SetDirection(Character::Direction::Left);
}
MouveCharacterLeft::MouveCharacterLeft() {}

JumpCharacter::JumpCharacter(){}

void JumpCharacter::Execute(const float& _delta)
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	player->SetPosition(player->GetPosition() + Maths::Vector2f::Down + Maths::Vector2f(0, -800) * _delta * character->GetSpeed());
	player->GetComponent<RigidBody2D>()->SetIsGravity(true);
}
