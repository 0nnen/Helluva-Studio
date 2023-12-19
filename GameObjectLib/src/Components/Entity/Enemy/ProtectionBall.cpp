#include "Components/Entity/Enemy/ProtectionBall.h"
#include "Components/Entity/Character.h"
#include "Components/Entity/Enemy/Hades.h"
#include "Managers/SceneManager.h"

bool ProtectionBall::alive;

ProtectionBall::ProtectionBall() : Entity() 
{
	player = SceneManager::GetActiveGameScene()->GetPlayer();
	hades = SceneManager::GetActiveGameScene()->GetHades();
	alive = true;
}
ProtectionBall::ProtectionBall(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range) {}

void ProtectionBall::Update(const float& _delta)
{
	Entity::Update(_delta);
	SetPower();
}

void ProtectionBall::SetHealth()
{
	switch (spawn)
	{
	case 0:
		break;
	case 1:
		SetHealthPoint(100.f);
		SetMaxHealthPoint(100.f);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		SetHealthPoint(50.f);
		SetMaxHealthPoint(50.f);
		break;
	case 5:
		SetHealthPoint(150.f);
		SetMaxHealthPoint(150.f);
		break;
	case 6:
		SetHealthPoint(175.f);
		SetMaxHealthPoint(175.f);
		break;
	default:
		break;
	}
}

void ProtectionBall::SetPower()
{
	Hades* balls = hades->GetComponent<Hades>();
	switch (spawn)
	{
	case 0:
		break;
	case 1:
		if (!alive)
		{
			player->GetComponent<Character>()->TakeHealt(10);
			alive = true;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		if (balls)
		{
			randX = rand() % 1300 + 500;
			randY = rand() % 400 + 200;
			for (GameObject* ball : balls->GetProtectionBalls())
			{
				ball->GetComponent<GameObject>()->SetPosition(Maths::Vector2f(randX, randY));
			}
		}
		break;
	case 5:
		break;
	case 6:
		if (!alive)
		{
			std::cout << "okk"; 
			hades->GetComponent<Hades>()->SetIncible(false);
			hades->GetComponent<Hades>()->TakeDamage(50);
			alive = true;
		}
		hades->GetComponent<Hades>()->SetIncible(true);
		break;
	case 7:
		break;
	default:
		break;
	}
}

void ProtectionBall::Die()
{
	Entity::Die();
	hades->GetComponent<Hades>()->RemoveBall(GetOwner());
}