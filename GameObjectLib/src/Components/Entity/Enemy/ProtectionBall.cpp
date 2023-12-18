#include "Components/Entity/Enemy/ProtectionBall.h"
#include "Components/Entity/Character.h"
#include "Components/Entity/Enemy/Hades.h"
#include "Managers/SceneManager.h"

bool ProtectionBall::alive;

ProtectionBall::ProtectionBall() : Entity() 
{
	player = SceneManager::GetActiveGameScene()->GetPlayer();
	hades = SceneManager::GetActiveGameScene()->GetHades();
}
ProtectionBall::ProtectionBall(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range) {}

void ProtectionBall::Update(const float& _delta)
{
	Entity::Update(_delta);
	Spawn();
}

void ProtectionBall::Spawn()
{
	switch (spawn)
	{
	case 0:
		break;
	case 1:
		//std::cout << "ok";
		/*SetHealthPoint(100.f);
		SetMaxHealthPoint(100.f);*/
		if (!alive)
		{
			player->GetComponent<Character>()->TakeHealt(10);
			std::cout << player->GetComponent<Character>()->GetHealthPoint();
			alive = true;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		SetHealthPoint(50.f);
		SetMaxHealthPoint(50.f);
		randX = rand() % 1500 + 500;
		randY = rand() % 400 + 200;
		hades->GetComponent<Hades>()->setPositionX(randX);
		hades->GetComponent<Hades>()->setPositionY(randY);
		break;
	case 5:
		SetHealthPoint(150.f);
		SetMaxHealthPoint(150.f);
		break;
	case 6:
		/*SetHealthPoint(175.f);
		SetMaxHealthPoint(175.f);*/
		if (!alive)
		{
			hades->GetComponent<Hades>()->SetIncible(false);
			hades->GetComponent<Hades>()->TakeDamage(50);
			alive = true;
		}
		hades->GetComponent<Hades>()->SetIncible(true);

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