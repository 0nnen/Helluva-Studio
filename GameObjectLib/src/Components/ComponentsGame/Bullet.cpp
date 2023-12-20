#include "Components/ComponentsGame/Bullet.h"
#include "Managers/SceneManager.h"
#include <cmath>

void Bullet::Update(const float& _delta)
{	
	Component::Update(_delta);
	Maths::Vector2f currentPosition = GetOwner()->GetPosition();
	const float distance = initialPosition.Distance(currentPosition);
	if (distance > 1920.f) SceneManager::GetActiveGameScene()->RemoveGameObject(GetOwner());
}


float Bullet::GetDamageReduced() const
{
	Maths::Vector2f currentPosition = GetOwner()->GetPosition();
	const float distance = initialPosition.Distance(currentPosition);
	return damage / (1.f + reductionFactor * pow(distance, 2));
}


float Bullet::GetDamageReduced(Maths::Vector2f& _currentPosition) const
{
	const float distance = initialPosition.Distance(_currentPosition);
	return damage / (1.f + reductionFactor * pow(distance, 2));
}