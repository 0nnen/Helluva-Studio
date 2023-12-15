#include "Components/Entity/Enemy/ProtectionBall.h"
#include "Components/Entity/Enemy/Hades.h"

ProtectionBall::ProtectionBall() : Entity() {}
ProtectionBall::ProtectionBall(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range) {}

void ProtectionBall::Die()
{
	Entity::Die();
	hades->GetComponent<Hades>()->RemoveBall(GetOwner());
}