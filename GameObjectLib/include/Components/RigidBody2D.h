#pragma once

#include "Component.h"
class RigidBody2D final : public Component
{
public:

	RigidBody2D();
	void Update(const float& _delta) override;
	void Gravity();
	inline void AddForces(const Maths::Vector2f& _force) { velocity += _force; }

	inline float GetMass() const { return mass; }
	inline void SetMass(const float& _mass) { mass = _mass; }

	inline float GetGravityScale() const { return gravityScale; }
	inline void SetGravityScale(const float& _newGravityScale) { gravityScale = _newGravityScale; }

	inline Maths::Vector2f GetVelocity() { return velocity; }
	inline void SetVelocity(const Maths::Vector2f& _newVelocity) { velocity = _newVelocity; }

	inline Maths::Vector2f GetGravity() { return gravity; }
	inline void SetGravity(const Maths::Vector2f& _newGravity) { gravity = _newGravity; }

	inline bool GetIsGravity() const { return isAffectedByGravity; }
	inline void SetIsGravity(const bool& _state) { isAffectedByGravity = _state; }

	inline float GetWidthCollider() const { return widthSquareCollider; }
	inline float GetHeightCollider() const { return heightSquareCollider; }

	inline void SetSize(const float& _width, const float& _height)
	{
		widthSquareCollider = _width;
		heightSquareCollider = _height;
	}
	inline void SetScale(const float& _scaleX, const float& _scaleY)
	{
		scaleSquareColliderX = _scaleX;
		widthSquareCollider *= _scaleX;
		heightSquareCollider *= _scaleY;
		scaleSquareColliderY = _scaleY;
	}

	static bool IsColliding(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB);

	static bool IsAbove(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB);
	static bool IsLeft(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB);
	static bool IsRight(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB);
	static bool IsBelow(const RigidBody2D& _rigidBody2DA, const RigidBody2D& _rigidBody2DB);

private:
	float mass = 1.0f;
	float gravityScale = 1.f;
	Maths::Vector2f velocity;
	Maths::Vector2f gravity;
	bool isAffectedByGravity;

	float widthSquareCollider = 1.0f;
	float heightSquareCollider = 1.0f;
	float scaleSquareColliderX = 1.0f;
	float scaleSquareColliderY = 1.0f;
};

