#include "Components/Entity/Enemy/ProtectionBall.h"
#include "Components/Entity/Character.h"
#include "Components/Entity/Enemy/Hades.h"
#include "Managers/SceneManager.h"
#include <Components/RigidBody2D.h>

ProtectionBall::ProtectionBall() : Entity() 
{
	player = SceneManager::GetActiveGameScene()->GetPlayer();
	hades = SceneManager::GetActiveGameScene()->GetHades();
}
  
ProtectionBall::ProtectionBall(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range) {}

void ProtectionBall::Update(const float& _delta)
{
	Entity::Update(_delta);
	SetPower(_delta);
}

void ProtectionBall::CreateBouleFeu()
{
	circle = BuilderEntityGameObject::CreateSphereFeuGameObject("FireCircle", 500, 1000, 100);
}

void ProtectionBall::CollisionFireBall()
{
	if (player, circle) {
		std::cout << "debug\n";
		if (RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(circle->GetComponent<RigidBody2D>())))
		{
			// enelver des PV au joueur;
			std::cout << "Cirlce en collision\n";
		}
	}
}


void ProtectionBall::SetHealth()
{
	switch (spawn)
	{
	case 0:
		SetHealthPoint(175.f);
		SetMaxHealthPoint(175.f);
		break;
	case 1:

		SetHealthPoint(50.f);
		SetMaxHealthPoint(50.f);
		break;
	case 2:
		SetHealthPoint(50.f);
		SetMaxHealthPoint(50.f);
		break;
	case 3:
		SetHealthPoint(250.f);
		SetMaxHealthPoint(250.f);
		break;
	case 4:
		break;
	case 5:
		SetHealthPoint(100.f);
		SetMaxHealthPoint(100.f);
		break;
	case 6:
		break;
	default:
		break;
	}
}

void ProtectionBall::SetPower(const float& _delta)
{
	switch (spawn)
	{
	case 1:
		positionFireCircle.x = GetOwner()->GetPosition().x;
		positionFireCircle.y = GetOwner()->GetPosition().y;

	case 2: 

		if (tp >= 5)
		{
			randX = rand() % 1300 + 500;
			randY = rand() % 400 + 200;
			GetOwner()->SetPosition(Maths::Vector2f(randX, randY));
			tp = 0;
		}
		tp += _delta;
		break;
	default:
		break;
	}
}

void ProtectionBall::Die()
{
	Entity::Die();
	switch (spawn)
	{

	case 0:

		hades->GetComponent<Hades>()->SetIncible(false);
		hades->GetComponent<Hades>()->TakeDamage(50);
		hades->GetComponent<Hades>()->SetIncible(true);
		break;

	case 1:
		CreateBouleFeu();
		circle->SetPosition(Maths::Vector2f(positionFireCircle.x, positionFireCircle.y));
		break;

	case 5:
		player->GetComponent<Character>()->TakeHealt(10);
		break;
	case 6:
		break;
	}
	hades->GetComponent<Hades>()->RemoveBall(GetOwner());
}