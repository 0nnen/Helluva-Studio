#include "Commands/CommandCharacter.h"
#include "BuilderGameObject.h"
#include "Components/Entity/Character.h"
#include "Components/Animation.h"
#include "Components/ComponentsGame/WeaponsContainer.h"
#include "Components/ComponentsGame/Weapon.h"
#include "Components/ComponentsGame/Gun.h"
#include "Managers/SceneManager.h"
#include "Managers/CameraManager.h"


void MoveCharacterRight::Execute(const float& _delta) 
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	player->SetPosition(player->GetPosition() + Maths::Vector2f::Right + Maths::Vector2f(30, 0) * _delta * character->GetSpeed());
	character->SetDirection(Character::Direction::Right);
}
MoveCharacterRight::MoveCharacterRight() {}

void MoveCharacterLeft::Execute(const float& _delta)
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	player->SetPosition(player->GetPosition() + Maths::Vector2f::Left + Maths::Vector2f(30, 0) * _delta * character->GetSpeed());
	character->SetDirection(Character::Direction::Left);
}
MoveCharacterLeft::MoveCharacterLeft() {}

JumpCharacter::JumpCharacter(){}

void JumpCharacter::Execute(const float& _delta)
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	RigidBody2D* rigidBody2D = player->GetComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(true);
	rigidBody2D->AddForces(Maths::Vector2f(0, -3000));
}

ShootCharacter::ShootCharacter() {}

void ShootCharacter::Execute(const float& _delta)
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	WeaponsContainer* weaponsContainer = player->GetComponent<WeaponsContainer>();
	weaponsContainer->GetArme()->GetComponent<Weapon>()->Attack(); //Attack!!
}