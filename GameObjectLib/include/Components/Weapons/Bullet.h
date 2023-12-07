#pragma once

#include "Component.h"
class Bullet : public Component
{
public:
	inline void SetDamage(const float& _damage) { damage = _damage; }
	inline float GetDamage() const { return damage; }

	inline void SetReductionFactor(const float& _reductionFactor) { reductionFactor = _reductionFactor; }
	inline float GetReductionFactor() const { return reductionFactor; }

	inline void SetPosition(const Maths::Vector2f& _initialPosition) { initialPosition = _initialPosition; }

	float GetDamageReduced() const;
	float GetDamageReduced(Maths::Vector2f& _currentPosition) const;

private:
	float damage = 0.f;
	float reductionFactor = 0.01f;
	Maths::Vector2f initialPosition;
};

