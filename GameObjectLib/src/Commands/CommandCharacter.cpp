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
	RigidBody2D* rigidBody2D = player->GetComponent<RigidBody2D>();
		if (rigidBody2D->GetVelocity().GetX() < character->GetMaxSpeed())
		{
			if (SceneManager::GetActiveGameScene()->GetName() != "SceneGameBossRoom") {
				rigidBody2D->AddForces(Maths::Vector2f::Right * _delta * character->GetSpeed());
			}
			else
			{
				if (player->GetPosition().GetX() < 1900.f) rigidBody2D->AddForces(Maths::Vector2f::Right * _delta * character->GetSpeed());
			}
			
		}
}
MoveCharacterRight::MoveCharacterRight() {}

void MoveCharacterLeft::Execute(const float& _delta)
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	RigidBody2D* rigidBody2D = player->GetComponent<RigidBody2D>();
	if (rigidBody2D->GetVelocity().GetX() > -character->GetMaxSpeed())
	{
		if (SceneManager::GetActiveGameScene()->GetName() != "SceneGameBossRoom") {
			rigidBody2D->AddForces(Maths::Vector2f::Left * _delta * character->GetSpeed());
		}
		else
		{
			if (player->GetPosition().GetX() > 20.f) rigidBody2D->AddForces(Maths::Vector2f::Left * _delta * character->GetSpeed());
		}
	}
	
}
MoveCharacterLeft::MoveCharacterLeft() {}

JumpCharacter::JumpCharacter(){}

void JumpCharacter::Execute(const float& _delta)
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	RigidBody2D* rigidBody2D = player->GetComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(true);
	rigidBody2D->AddForces(Maths::Vector2f(0, -1200));
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
	std::cout << numberWeapon << std::endl;
	if (numberWeapon == 0) weaponsContainer->ChangeWeapon();
	else weaponsContainer->ChangeWeaponByIndex(numberWeapon);
}

