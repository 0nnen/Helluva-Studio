#include "Components/Entity.h"
#include "Managers/SceneManager.h"
#include "Managers/AudioManager.h"
#include "Managers/WindowManager.h"
#include "Managers/AudioManager.h"
#include "Components/RigidBody2D.h"

#include <Components/Entity/Enemy/Hades.h>

#include "Components/Entity/Enemy/ProtectionBall.h"



Entity::Entity() : healthPoint(100), maxHealthPoint(100), damage(10), attackSpeed(1.0f), maxSpeed(300.f), range(1), speed(300.f) {}
Entity::Entity(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : healthPoint(_hp), maxHealthPoint(_hp), damage(_damage), speed(_speed), maxSpeed(_speed + 100.f), attackSpeed(_attackSpeed), range(_range) {}

void Entity::TakeDamage(const float& _damage)
{
	if (!isInvicible) {
	
		if (healthPoint > _damage)
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

}

void Entity::Attack( const float& _delta){}


void Entity::Die()
{
	healthPoint = 0;
	GetOwner()->SetActiveAndVisible(false);
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
}

void Entity::AddAnimation(const std::string& _name, Animation* animation)
{
	sf::Texture* texture = new sf::Texture();
	if (animations.find(_name) == animations.end())
	{
		animations.insert(std::make_pair(_name, animation));
	}
}

Animation* Entity::GetAnimation(const std::string& _name)
{
	if (animations.find(_name) != animations.end())
	{
		return animations.at(_name);
	}
	return nullptr;
}
Animation* Entity::GetAndSetAnimation(const std::string& _name)
{
	if (animations.find(_name) != animations.end())
	{
		actualAnimation = animations.at(_name);
		return actualAnimation;
	}
	return nullptr;
}

void Entity::SetDirection(Direction _newDirection) {

	direction = _newDirection;
	if (direction == Direction::Left)
	{
		GetOwner()->SetScale(Maths::Vector2f(-std::abs(GetOwner()->GetScale().x), GetOwner()->GetScale().y));
	}
	else if (direction == Direction::Right)
	{
		GetOwner()->SetScale(Maths::Vector2f(std::abs(GetOwner()->GetScale().x), GetOwner()->GetScale().y));
	}
}