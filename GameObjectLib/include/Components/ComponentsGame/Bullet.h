#pragma once

#include "Component.h"
class Bullet : public Component
{
public:
	void Update(const float& _delta) override;
	inline void SetDamage(const float& _damage) { damage = _damage; }
	inline float GetDamage() const { return damage; }

	inline void SetReductionFactor(const float& _reductionFactor) { reductionFactor = _reductionFactor; }
	inline float GetReductionFactor() const { return reductionFactor; }

	inline void SetSpeed(const float& _speed) { speed = _speed; }
	inline float GetSpeed() const { return speed; }

	inline void SetInitialPosition(const Maths::Vector2f& _initialPosition) { initialPosition = _initialPosition; }

	float GetDamageReduced() const;
	float GetDamageReduced(Maths::Vector2f& _currentPosition) const;

private:
	float damage = 20.f;
	float reductionFactor = 0.000001f;
	float speed = 330.f;
	Maths::Vector2f initialPosition = Maths::Vector2f::Zero;
};

