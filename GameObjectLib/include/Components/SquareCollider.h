#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
class SquareCollider : public Component
{
public:
	static bool IsColliding(const SquareCollider& _rigidBody2DA, const SquareCollider& _rigidBody2DB);

	static bool IsAbove(const SquareCollider& _rigidBody2DA, const SquareCollider& _rigidBody2DB);
	static bool IsLeft(const SquareCollider& _rigidBody2DA, const SquareCollider& _rigidBody2DB);
	static bool IsRight(const SquareCollider& _rigidBody2DA, const SquareCollider& _rigidBody2DB);
	static bool IsBelow(const SquareCollider& _rigidBody2DA, const SquareCollider& _rigidBody2DB);

	float GetWidthCollider() const { return widthCollider; }
	float GetHeightCollider() const { return heightCollider; }
	void SetHeightCollider(const float& _heightCollider) {  heightCollider = _heightCollider; }
	void SetWidthCollider(const float& _widthCollider) { widthCollider = _widthCollider; }

	Maths::Vector2f GetPosition() const { return position; }
	void SetPosition(const Maths::Vector2f& _position)  { position = _position; }

	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;
private:
	float widthCollider = 0.f;
	float heightCollider = 0.f;
	Maths::Vector2f position = Maths::Vector2f::Zero;
};

