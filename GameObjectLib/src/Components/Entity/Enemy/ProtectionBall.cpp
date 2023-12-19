#include "Components/Entity/Enemy/ProtectionBall.h"
#include "Components/Entity/Character.h"
#include "Components/Entity/Enemy/Hades.h"
#include "Managers/SceneManager.h"
#include <Components/RigidBody2D.h>

ProtectionBall::ProtectionBall() : Entity()
{
	player = SceneManager::GetActiveGameScene()->GetPlayer();
}
ProtectionBall::ProtectionBall(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range) {}

void ProtectionBall::Update(const float& _delta)
{
	Entity::Update(_delta);
}

void ProtectionBall::Die()
{
	Entity::Die();
	hades->GetComponent<Hades>()->RemoveBall(GetOwner());
}

//void ProtectionBall::DieFireCirlce()
//{
//	Entity::DieFireCirlce();
//}