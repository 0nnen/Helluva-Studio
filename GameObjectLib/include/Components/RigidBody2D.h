#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"
#include <iostream>
class RigidBody2D final : public Component
{
public:

	RigidBody2D();

	void Physics(const float& _delta) override;
	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;

	void Gravity();
	inline void AddForces(const Maths::Vector2f& _force)
	{
		velocity += _force;
		if (velocity.x > maxVelocity.x) velocity.x = maxVelocity.x;
		if (velocity.x < -maxVelocity.x) velocity.x = -maxVelocity.x;
		if (velocity.y > maxVelocity.y) velocity.y = maxVelocity.y;
		if (velocity.y < -maxVelocity.y) velocity.y = -maxVelocity.y;
	}

	inline float GetMass() const { return mass; }
	inline void SetMass(const float& _mass) { mass = _mass; }

	inline float GetGravityScale() const { return gravityScale; }
	inline void SetGravityScale(const float& _newGravityScale) { gravityScale = _newGravityScale; }

	inline Maths::Vector2f GetVelocity() { return velocity; }
	inline void SetVelocity(const Maths::Vector2f& _newVelocity)
	{
		if (_newVelocity.x >= 0) velocity.x = _newVelocity.x > maxVelocity.x ? maxVelocity.x : _newVelocity.x;
		else velocity.x = _newVelocity.x < -maxVelocity.x ? -maxVelocity.x : _newVelocity.x;

		if (_newVelocity.y <= 0) velocity.y = _newVelocity.y < -maxVelocity.y ? -maxVelocity.y : _newVelocity.y;
		else velocity.y = _newVelocity.y > maxVelocity.y ? maxVelocity.y : _newVelocity.y;
	}

	inline Maths::Vector2f GetMaxVelocity() { return maxVelocity; }
	inline void SetMaxVelocity(const Maths::Vector2f& _newMaxVelocity) {
		maxVelocity = _newMaxVelocity;
	}

	inline Maths::Vector2f GetGravity() { return gravity; }
	inline void SetGravity(const Maths::Vector2f& _newGravity) { gravity = _newGravity; }

	inline bool GetIsGravity() const { return isAffectedByGravity; }
	inline void SetIsGravity(const bool& _state) {
		isAffectedByGravity = _state;
		if (!isAffectedByGravity)
		{
			velocity.SetY(0.f);
		}
	}

	inline Maths::Vector2f GetKillImperfection() const { return killImperfection; }
	inline void SetKillImperfection(const Maths::Vector2f& _killImperfection) { killImperfection = _killImperfection; }

	inline float GetWidthCollider() const { return widthSquareCollider; }
	inline float GetHeightCollider() const { return heightSquareCollider; }

	inline void SetSize(const float& _width, const float& _height)
	{
		widthSquareCollider = (_width - killImperfection.GetX()) * GetOwner()->GetScale().x;
		heightSquareCollider = (_height - killImperfection.GetY()) * GetOwner()->GetScale().y;
	}
	inline void SetSize(const Maths::Vector2f& _size)
	{
		widthSquareCollider = (_size.x - killImperfection.GetX()) * GetOwner()->GetScale().x;
		heightSquareCollider = (_size.y - killImperfection.GetY()) * GetOwner()->GetScale().y;
	}


	static bool IsColliding(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB);

	static bool IsAbove(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB);
	static bool IsLeft(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB);
	static bool IsRight(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB);
	static bool IsBelow(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB);

private:
	float mass = 1.0f;
	float gravityScale = 1.f;
	Maths::Vector2f maxVelocity;
	Maths::Vector2f velocity;
	Maths::Vector2f gravity;
	bool isAffectedByGravity;

	Maths::Vector2f killImperfection = Maths::Vector2f::Zero;
	float widthSquareCollider = 1.0f;
	float heightSquareCollider = 1.0f;

	sf::RectangleShape rectangle;
};

