#include "Components/Entity.h"
#include "Managers/SceneManager.h"
#include "Managers/AudioManager.h"
#include "Managers/WindowManager.h"
#include "Managers/AudioManager.h"


Entity::Entity() : healthPoint(100), maxHealthPoint(100), damage(10), attackSpeed(1.0f), range(1), speed(20.f) {}
Entity::Entity(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : healthPoint(_hp), maxHealthPoint(_hp), damage(_damage), speed(_speed), attackSpeed(_attackSpeed), range(_range) {}

void Entity::TakeDamage(const int& _damage)
{
	if (healthPoint > damage)
	{
		healthPoint -= _damage;
	}
	else {
		healthPoint = 0;
	}

	if (healthPoint <= 0)
	{
		this->Die();
	}
}

void Entity::Die()
{
	healthPoint = 0;
	//AudioManager::PlaySound("dead");
	SceneManager::GetActiveGameScene()->RemoveGameObject(GetOwner());
}

void Entity::Update(const float& _delta) 
{
	Component::Update(_delta);

	if (count < attackSpeed * 500) 
	{
		count++;
	}

	if (GetOwner()->GetPosition().GetX() > WindowManager::GetWindowWidth()
		|| GetOwner()->GetPosition().GetY() > WindowManager::GetWindowHeight()
		|| GetOwner()->GetPosition().GetY() < 0
		|| GetOwner()->GetPosition().GetX() < 0
		)
	{
		this->Die();
	}
}