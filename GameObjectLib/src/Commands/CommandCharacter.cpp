#include "Commands/CommandCharacter.h"
#include "BuilderGameObject.h"
#include "Components/Entity/Character.h"
#include "Components/Animation.h"
#include "Components/SquareCollider.h"
#include "Components/ComponentsGame/WeaponsContainer.h"
#include "Components/ComponentsGame/Weapon.h"
#include "Components/ComponentsGame/Gun.h"
#include "Managers/SceneManager.h"
#include "Managers/CameraManager.h"


void MoveCharacterRight::Execute(const float& _delta)
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	RigidBody2D* rigidBody2D = player->GetComponent<RigidBody2D>();
	

	if (character->GetDirection() == Character::Right) 
	{
		rigidBody2D->SetMaxVelocity(Maths::Vector2f(character->GetMaxSpeed(), rigidBody2D->GetMaxVelocity().y));
		rigidBody2D->AddForces(Maths::Vector2f::Right * _delta * character->GetSpeed());
	}
	else 
	{
		rigidBody2D->SetMaxVelocity(Maths::Vector2f(character->GetMaxSpeed() / 3, rigidBody2D->GetMaxVelocity().y));
		rigidBody2D->AddForces(Maths::Vector2f::Right * _delta * character->GetSpeed() / 3);
	}
}
MoveCharacterRight::MoveCharacterRight() {}

void MoveCharacterLeft::Execute(const float& _delta)
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	RigidBody2D* rigidBody2D = player->GetComponent<RigidBody2D>();
	float fireKnockback = 1.f;
	if (character->GetFiring()) fireKnockback = 10.f;
	if (character->GetDirection() == Character::Left)
	{
		rigidBody2D->SetMaxVelocity(Maths::Vector2f(character->GetMaxSpeed(), rigidBody2D->GetMaxVelocity().y));
		rigidBody2D->AddForces(Maths::Vector2f::Left * _delta * character->GetSpeed());
	}
	else 
	{
		rigidBody2D->SetMaxVelocity(Maths::Vector2f(character->GetMaxSpeed() / 3, rigidBody2D->GetMaxVelocity().y));
		rigidBody2D->AddForces(Maths::Vector2f::Left * _delta * character->GetSpeed() / 3);
	}
}
MoveCharacterLeft::MoveCharacterLeft() {}

JumpCharacter::JumpCharacter() {}

void JumpCharacter::Execute(const float& _delta)
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	RigidBody2D* rigidBody2D = player->GetComponent<RigidBody2D>();

	SquareCollider* squareCollider = player->GetComponentsByType<SquareCollider>()[0];
	SquareCollider* squareColliderGround = player->GetComponentsByType<SquareCollider>()[1];
	squareColliderGround->SetActiveCollider(false);
	squareCollider->SetActiveCollider(true);
	rigidBody2D->AddForces(Maths::Vector2f(0, -1400));

}

ShootCharacter::ShootCharacter() {}

void ShootCharacter::Execute(const float& _delta)
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	WeaponsContainer* weaponsContainer = player->GetComponent<WeaponsContainer>();
	weaponsContainer->GetArme()->GetComponent<Weapon>()->Attack(); //Attack!!
}

ChangeWeaponCharacter::ChangeWeaponCharacter(const int& _numberWeapon) : numberWeapon(_numberWeapon) {}

void ChangeWeaponCharacter::Execute(const float& _delta)
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	WeaponsContainer* weaponsContainer = player->GetComponent<WeaponsContainer>();

	if (numberWeapon == 0) weaponsContainer->ChangeWeapon();
	else weaponsContainer->ChangeWeaponByIndex(numberWeapon);
}

