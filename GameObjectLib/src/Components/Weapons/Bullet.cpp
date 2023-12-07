#include "Components/Weapons/Bullet.h"
#include <cmath>

float Bullet::GetDamageReduced() const
{
	Maths::Vector2f currentPosition = GetOwner()->GetPosition();
	const float distance = (currentPosition - initialPosition).Magnitude();

	return damage / (1.f + reductionFactor * pow(distance, 2));
}


float Bullet::GetDamageReduced(Maths::Vector2f& _currentPosition) const
{
	Maths::Vector2f currentPosition = GetOwner()->GetPosition();
	const float distance = (_currentPosition - initialPosition).Magnitude();

	return damage / (1.f + reductionFactor * pow(distance, 2));
}